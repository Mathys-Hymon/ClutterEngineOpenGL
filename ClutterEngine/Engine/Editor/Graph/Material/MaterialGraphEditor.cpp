#include <pch.h>
#include "MaterialGraphEditor.h"
#include "GraphEditor.h"
#include "imgui.h"
#include "imgui_internal.h"
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>

using namespace clt;

// --- Static colors for easy tweaking ---
static const ImU32 COLOR_HEADER_CALC = IM_COL32(210, 174, 43, 255); // jaune pour nodes calcul
static const ImU32 COLOR_HEADER_BOOL = IM_COL32(180, 40, 40, 255);  // rouge pour bool
static const ImU32 COLOR_HEADER_VALUE = IM_COL32(50, 100, 200, 255); // bleu pour constants/value
static const ImU32 COLOR_BG = IM_COL32(20, 20, 20, 255);   // fond gris
static const ImU32 COLOR_BG_OVER = IM_COL32(50, 50, 50, 255);   // fond gris hover

// --- Inputs / outputs arrays ---
static const char* inputs_return[] = { "Base Color", "Metallic", "Specular", "Roughness", "Emissive Color", "Opacity", "Normal", "World Position Offset", "Ambiant Occlusion", "Pixel Depth Offset" };
static const char* inputs_add[] = { "A", "B" };
static const char* inputs_math[] = { "A", "B" };
static const char* inputs_select[] = { "A", "B", "is A" };
static const char* inputs_texture[] = { "UV" };

static const char* outputs_add[] = { "Result" };
static const char* outputs_math[] = { "Result" };
static const char* outputs_value[] = { "Value" };
static const char* outputs_vec2[] = { "X", "Y" };
static const char* outputs_vec3[] = { "X", "Y", "Z" };
static const char* outputs_color[] = { "R", "G", "B", "A" };

static ImU32 outputs_vec3Color[] = { IM_COL32(200,100,100,255), IM_COL32(100,200,100,255), IM_COL32(100,100,200,255) };
static ImU32 outputs_vec2Color[] = { IM_COL32(200,100,100,255), IM_COL32(100,200,100,255) };

// --- Template array ---
const GraphEditor::Template MaterialGraphEditor::mTemplates[] =
{
    // OutResult
    { COLOR_HEADER_CALC, COLOR_BG, COLOR_BG_OVER, 10, inputs_return, nullptr, 0, nullptr, nullptr },

    // Math operations
    { COLOR_HEADER_CALC, COLOR_BG, COLOR_BG_OVER, 2, inputs_add, nullptr, 1, outputs_add, nullptr },   // Add
    { COLOR_HEADER_CALC, COLOR_BG, COLOR_BG_OVER, 2, inputs_math, nullptr, 1, outputs_math, nullptr }, // Subtract
    { COLOR_HEADER_CALC, COLOR_BG, COLOR_BG_OVER, 2, inputs_math, nullptr, 1, outputs_math, nullptr }, // Multiply
    { COLOR_HEADER_CALC, COLOR_BG, COLOR_BG_OVER, 2, inputs_math, nullptr, 1, outputs_math, nullptr }, // Divide
    { COLOR_HEADER_BOOL, COLOR_BG, COLOR_BG_OVER, 2, inputs_math, nullptr, 1, outputs_value, nullptr }, // Equal
    { COLOR_HEADER_BOOL, COLOR_BG, COLOR_BG_OVER, 3, inputs_select, nullptr, 1, outputs_value, nullptr }, // Select

    // Break nodes
    { COLOR_HEADER_CALC, COLOR_BG, COLOR_BG_OVER, 1, outputs_value, nullptr, 2, outputs_vec2, outputs_vec2Color }, // Break Vector2
    { COLOR_HEADER_CALC, COLOR_BG, COLOR_BG_OVER, 1, outputs_value, nullptr, 3, outputs_vec3, outputs_vec3Color }, // Break Vector3
    { COLOR_HEADER_CALC, COLOR_BG, COLOR_BG_OVER, 1, outputs_value, nullptr, 4, outputs_color, nullptr },           // Break Color

    // Make nodes
    { COLOR_HEADER_CALC, COLOR_BG, COLOR_BG_OVER, 2, outputs_vec2, nullptr, 1, outputs_value, nullptr }, // Make Vector2
    { COLOR_HEADER_CALC, COLOR_BG, COLOR_BG_OVER, 3, outputs_vec3, nullptr, 1, outputs_value, nullptr }, // Make Vector3
    { COLOR_HEADER_CALC, COLOR_BG, COLOR_BG_OVER, 4, outputs_color, nullptr, 1, outputs_value, nullptr }, // Make Color

    // Constants / Values
    { COLOR_HEADER_VALUE, COLOR_BG, COLOR_BG_OVER, 0, nullptr, nullptr, 1, outputs_value, nullptr }, // Float
    { COLOR_HEADER_VALUE, COLOR_BG, COLOR_BG_OVER, 0, nullptr, nullptr, 1, outputs_value, nullptr }, // Int
    { COLOR_HEADER_BOOL,  COLOR_BG, COLOR_BG_OVER, 0, nullptr, nullptr, 1, outputs_value, nullptr }, // Bool
    { COLOR_HEADER_VALUE, COLOR_BG, COLOR_BG_OVER, 0, nullptr, nullptr, 1, outputs_vec2, nullptr }, // Vector2
    { COLOR_HEADER_VALUE, COLOR_BG, COLOR_BG_OVER, 0, nullptr, nullptr, 1, outputs_vec3, nullptr }, // Vector3
    { COLOR_HEADER_VALUE, COLOR_BG, COLOR_BG_OVER, 0, nullptr, nullptr, 1, outputs_color, nullptr }, // Color
    { COLOR_HEADER_VALUE, COLOR_BG, COLOR_BG_OVER, 0, nullptr, nullptr, 1, outputs_value, nullptr }, // Texture

    // Entry nodes
    { COLOR_HEADER_CALC, COLOR_BG, COLOR_BG_OVER, 0, nullptr, nullptr, 1, outputs_value, nullptr }, // Time
    { COLOR_HEADER_CALC, COLOR_BG, COLOR_BG_OVER, 0, nullptr, nullptr, 1, outputs_vec2, nullptr }, // TexCoord

    // Extras
    { COLOR_HEADER_CALC, COLOR_BG, COLOR_BG_OVER, 1, outputs_vec2, nullptr, 1, outputs_value, nullptr } // VectorLength
};

// --- Constructeur ---
MaterialGraphEditor::MaterialGraphEditor()
{
    AddNode(NodeTemplates[0], { 1200,450 });
}

// --- Delegate overrides ---
bool MaterialGraphEditor::AllowedLink(GraphEditor::NodeIndex senderNodeIndex, GraphEditor::SlotIndex senderSlotIndex, GraphEditor::NodeIndex recieverNodeIndex, GraphEditor::SlotIndex recieverSlotIndex)
{
    if (senderNodeIndex >= mNodes.size() || recieverNodeIndex >= mNodes.size() || senderNodeIndex == recieverNodeIndex) return false;

    Node& senderNode = mNodes[senderNodeIndex];
    Node& recieverNode = mNodes[recieverNodeIndex];

    Slot& senderSlot = senderNode.outputs[senderSlotIndex];
    Slot& recieverSlot = recieverNode.inputs[recieverSlotIndex];

    if (recieverSlot.connectedNode != -1) return false;

    if (recieverSlot.type == NodeType::Any)
    {
        recieverSlot.type = senderSlot.type;

        Node& node = mNodes[recieverNodeIndex];
        for (Slot& s : node.inputs)  s.type = senderSlot.type;
        for (Slot& s : node.outputs) s.type = senderSlot.type;
        return true;
    }

    else if (senderSlot.type == NodeType::Any)
    {
        senderSlot.type = recieverSlot.type;

        Node& node = mNodes[senderNodeIndex];
        for (Slot& s : node.inputs)  s.type = recieverSlot.type;
        for (Slot& s : node.outputs) s.type = recieverSlot.type;
        return true;
    }

    bool compatible = senderSlot.type == recieverSlot.type;
    if (!compatible)
    {
        mInvalidLink.active = true;
        mInvalidLink.message =
            "Type mismatch: expected " + NodeTypeToString(recieverSlot.type) +
            ", got " + NodeTypeToString(senderSlot.type);
        mInvalidLink.position = ImGui::GetMousePos();
        mInvalidLink.timer = 5;
        mInvalidLink.totalTimer = mInvalidLink.timer;
    }

    return senderSlot.type == recieverSlot.type;
}

void MaterialGraphEditor::SelectNode(GraphEditor::NodeIndex nodeIndex, bool selected)
{
    mNodes[nodeIndex].mSelected = selected;
}

void MaterialGraphEditor::MoveSelectedNodes(const ImVec2 delta)
{
    for (auto& node : mNodes)
    {
        if (node.mSelected)
        {
            node.pos.x += delta.x;
            node.pos.y += delta.y;
        }
    }
}

void MaterialGraphEditor::RightClick(GraphEditor::NodeIndex n, GraphEditor::SlotIndex si_a, GraphEditor::SlotIndex si_b)
{
    mOpenContextMenu = true;
}

void MaterialGraphEditor::AddLink(GraphEditor::NodeIndex inputNodeIndex, GraphEditor::SlotIndex inputSlotIndex,
    GraphEditor::NodeIndex outputNodeIndex, GraphEditor::SlotIndex outputSlotIndex, ImU32 nodeColor)
{
    mLinks.push_back({ inputNodeIndex, inputSlotIndex, outputNodeIndex, outputSlotIndex, nodeColor });
}

GraphEditor::LinkIndex clt::MaterialGraphEditor::GetLinkConnectedToInput(GraphEditor::NodeIndex nodeIndex, GraphEditor::SlotIndex inputSlotIndex)
{
    const size_t linkCount = GetLinkCount();
    for (GraphEditor::LinkIndex i = 0; i < linkCount; ++i)
    {
        const GraphEditor::Link& link = GetLink(i);
        if (link.mOutputNodeIndex == nodeIndex && link.mOutputSlotIndex == inputSlotIndex)
            return i;
    }
    return static_cast<GraphEditor::LinkIndex>(-1);
}

void MaterialGraphEditor::AddNode(const NodeTemplate& node, const Vector2& pos)
{
    Node n;
    n.name = node.name;
    n.kind = node.kind;
    n.pos = pos;
    n.size = node.defaultSize;
    n.mSelected = false;
    n.templateIndex = node.templateIndex;

    n.inputs = node.inputs;
    n.outputs = node.outputs;

    for (Slot& s : n.inputs) { s.connectedNode = -1; s.connectedSlot = -1; }
    for (Slot& s : n.outputs) { s.connectedNode = -1; s.connectedSlot = -1; }

    mNodes.push_back(n);
}

void MaterialGraphEditor::DelLink(GraphEditor::LinkIndex linkIndex)
{
    if (linkIndex >= mLinks.size())     return;

    GraphEditor::Link link = mLinks[linkIndex];

    Node& receiverNode = mNodes[link.mOutputNodeIndex];
    Node& senderNode = mNodes[link.mInputNodeIndex];

    Slot& senderSlot = senderNode.outputs[link.mInputSlotIndex];
    Slot& receiverSlot = receiverNode.inputs[link.mOutputSlotIndex];

    senderSlot.connectedNode = -1;
    senderSlot.connectedSlot = -1;
    receiverSlot.connectedNode = -1;
    receiverSlot.connectedSlot = -1;

    mLinks.erase(mLinks.begin() + linkIndex);

    if (receiverNode.kind == NodeKind::Add ||
        receiverNode.kind == NodeKind::Subtract ||
        receiverNode.kind == NodeKind::Multiply ||
        receiverNode.kind == NodeKind::Divide)
    {
        bool hasConnections = false;
        for (const Slot& s : receiverNode.inputs)
        {
            if (s.connectedNode != -1)
            {
                hasConnections = true;
                break;
            }
        }

        if (!hasConnections)
        {
            for (Slot& s : receiverNode.inputs)  s.type = NodeType::Any;
            for (Slot& s : receiverNode.outputs) s.type = NodeType::Any;
        }
    }

    if (senderNode.kind == NodeKind::Add ||
        senderNode.kind == NodeKind::Subtract ||
        senderNode.kind == NodeKind::Multiply ||
        senderNode.kind == NodeKind::Divide)
    {
        bool hasConnections = false;
        for (const Slot& s : senderNode.outputs)
        {
            if (s.connectedNode != -1)
            {
                hasConnections = true;
                break;
            }
        }

        if (!hasConnections)
        {
            for (Slot& s : senderNode.inputs)  s.type = NodeType::Any;
            for (Slot& s : senderNode.outputs) s.type = NodeType::Any;
        }
    }
}

void MaterialGraphEditor::CustomDraw(ImDrawList* drawList, ImRect rect, GraphEditor::NodeIndex nodeIndex)
{
    if (!mInvalidLink.active)
        return;

    float t = Maths::Clamp(mInvalidLink.timer / (mInvalidLink.totalTimer * 0.7f), 0.f, 1.f);
    int alpha = static_cast<int>(255 * t);

    const ImVec2 mousePos = ImGui::GetMousePos();
    const std::string& message = mInvalidLink.message;

    ImVec2 textSize = ImGui::CalcTextSize(message.c_str());
    float padding = 8.0f;

    ImVec2 rectMin(mousePos.x + 16, mousePos.y - 16);
    ImVec2 rectMax(rectMin.x + textSize.x + padding * 2, rectMin.y + textSize.y + padding * 2);

    ImDrawList* fg = ImGui::GetForegroundDrawList();

    fg->AddRectFilled(rectMin, rectMax, IM_COL32(30, 30, 30, (int)(alpha * 0.8f)), 6.0f);
    fg->AddRect(rectMin, rectMax, IM_COL32(255, 0, 0, alpha), 6.0f, 0, 1.5f);

    ImVec2 textPos(rectMin.x + padding, rectMin.y + padding);
    fg->AddText(ImGui::GetFont(), ImGui::GetFontSize(), textPos, IM_COL32(255, 255, 255, alpha), message.c_str());

    mInvalidLink.timer -= ImGui::GetIO().DeltaTime;
    if (mInvalidLink.timer <= 0.0f)
    {
        mInvalidLink.active = false;
        mInvalidLink.timer = 0.0f;
    }
}

const size_t MaterialGraphEditor::GetTemplateCount()
{
    return sizeof(mTemplates) / sizeof(GraphEditor::Template);
}

const GraphEditor::Template MaterialGraphEditor::GetTemplate(GraphEditor::NodeIndex index)
{
    return mTemplates[index];
}

const size_t MaterialGraphEditor::GetNodeCount()
{
    return mNodes.size();
}

const GraphEditor::Node MaterialGraphEditor::GetNode(GraphEditor::NodeIndex index)
{
    const auto& n = mNodes[index];
    return GraphEditor::Node{
        n.name,
        n.templateIndex,
        ImRect(ImVec2(n.pos.x - n.size.x * 0.5 , n.pos.y - n.size.y * 0.5), ImVec2(n.pos.x + n.size.x * 0.5, n.pos.y + n.size.y * 0.5)),
        n.mSelected
    };
}

const size_t MaterialGraphEditor::GetLinkCount()
{
    return mLinks.size();
}

const GraphEditor::Link MaterialGraphEditor::GetLink(GraphEditor::LinkIndex index)
{
    return mLinks[index];
}