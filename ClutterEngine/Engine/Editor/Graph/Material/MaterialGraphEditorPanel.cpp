#include <pch.h>
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <unordered_set>
#include <deque>

#include "MaterialGraphEditorPanel.h"
#include <Core/JsonUtility.h>
#include "GraphEditor.h"
#include "imgui.h"
#include "imgui_internal.h"

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
const GraphEditor::Template MaterialGraphEditorPanel::mTemplates[] =
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
MaterialGraphEditorPanel::MaterialGraphEditorPanel()
{
    AddNode(NodeTemplates[0], { 1200,450 });
}

// --- Delegate overrides ---
bool MaterialGraphEditorPanel::AllowedLink(GraphEditor::NodeIndex senderNodeIndex, GraphEditor::SlotIndex senderSlotIndex, GraphEditor::NodeIndex recieverNodeIndex, GraphEditor::SlotIndex recieverSlotIndex)
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

void MaterialGraphEditorPanel::SelectNode(GraphEditor::NodeIndex nodeIndex, bool selected)
{
    mNodes[nodeIndex].mSelected = selected;
    mSelectedNode = nodeIndex;
}

void MaterialGraphEditorPanel::MoveSelectedNodes(const ImVec2 delta)
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

void MaterialGraphEditorPanel::RightClick(GraphEditor::NodeIndex n, GraphEditor::SlotIndex si_a, GraphEditor::SlotIndex si_b)
{
    mOpenContextMenu = true;
}

void MaterialGraphEditorPanel::AddLink(GraphEditor::NodeIndex senderNodeIndex, GraphEditor::SlotIndex senderSlotIndex,
    GraphEditor::NodeIndex receiverNodeIndex, GraphEditor::SlotIndex receiverSlotIndex, ImU32 nodeColor)
{
    mLinks.push_back({ senderNodeIndex, senderSlotIndex, receiverNodeIndex, receiverSlotIndex, nodeColor });

    Node& senderNode = mNodes[senderNodeIndex];
    Node& receiverNode = mNodes[receiverNodeIndex];

    if (senderSlotIndex >= 0 && senderSlotIndex < (GraphEditor::SlotIndex)senderNode.outputs.size())
    {
        senderNode.outputs[senderSlotIndex].connectedNode = receiverNodeIndex;
        senderNode.outputs[senderSlotIndex].connectedSlot = receiverSlotIndex;
    }

    if (receiverSlotIndex >= 0 && receiverSlotIndex < (GraphEditor::SlotIndex)receiverNode.inputs.size())
    {
        receiverNode.inputs[receiverSlotIndex].connectedNode = senderNodeIndex;
        receiverNode.inputs[receiverSlotIndex].connectedSlot = senderSlotIndex;
    }

    PropagateNodeType(senderNodeIndex);
}

GraphEditor::LinkIndex clt::MaterialGraphEditorPanel::GetLinkConnectedToInput(GraphEditor::NodeIndex nodeIndex, GraphEditor::SlotIndex inputSlotIndex)
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

ImU32 MaterialGraphEditorPanel::GetLinkColor(GraphEditor::NodeIndex outputNodeIndex, GraphEditor::SlotIndex outputSlotIndex)
{
    static GraphEditor::Options options;

    if (outputNodeIndex < 0 || outputNodeIndex >= (GraphEditor::NodeIndex)mNodes.size())
        return options.mDefaultSlotColor;

    const Node& node = mNodes[outputNodeIndex];
    const GraphEditor::Template nodeTemplate = GetTemplate(node.templateIndex);

    const ImU32* outputColors = nodeTemplate.mOutputColors;
    if (outputColors && outputSlotIndex >= 0 && outputSlotIndex < (int)nodeTemplate.mOutputCount)
        return outputColors[outputSlotIndex];

    return options.mDefaultSlotColor;
}

void MaterialGraphEditorPanel::PropagateNodeType(GraphEditor::NodeIndex startNodeIndex)
{
    if (startNodeIndex >= mNodes.size()) return;

    std::unordered_set<GraphEditor::NodeIndex> visited;
    std::deque<GraphEditor::NodeIndex> queue;

    bool isConnectedToValue{ false };

    queue.push_back(startNodeIndex);
    visited.insert(startNodeIndex);

    while (!queue.empty())
    {
        GraphEditor::NodeIndex currentIndex = queue.front();
        queue.pop_front();

        Node& currentNode = mNodes[currentIndex];
        NodeType finalType = NodeType::Any;
        bool isConnected{ false };

        for (int i = 0; i < currentNode.inputs.size(); i++)
        {
            Slot& in = currentNode.inputs[i];
            NodeType initialType = NodeTemplates[currentNode.templateIndex].inputs[i].type;

            if (in.connectedNode > -1)
            {
                Node& connectedNode = mNodes[in.connectedNode];
                Slot& connectedSlot = connectedNode.outputs[in.connectedSlot];
                const NodeType& connectedSlotInitialType = NodeTemplates[connectedNode.templateIndex].outputs[in.connectedSlot].type;

                if (connectedSlot.type == NodeType::Any && in.type != NodeType::Any)
                {
                    connectedSlot.type = in.type;
                }

                else if (in.type == NodeType::Any && connectedSlot.type != NodeType::Any)
                {
                    in.type = connectedSlot.type;
                    finalType = connectedSlot.type;
                }

                else if (in.type == NodeType::Any && connectedSlot.type == NodeType::Any)
                {
                    in.type = initialType;
                    connectedSlot.type = connectedSlotInitialType;
                }

                if (in.type != initialType)
                {
                    finalType = in.type;
                    isConnected = true;
                }
            }
            else
            {
                in.type = initialType;
            }
        }

        for (int i = 0; i < currentNode.outputs.size(); i++)
        {
            Slot& out = currentNode.outputs[i];
            NodeType initialType = NodeTemplates[currentNode.templateIndex].outputs[i].type;

            if (out.connectedNode > -1)
            {
                Node& connectedNode = mNodes[out.connectedNode];
                Slot& connectedSlot = connectedNode.inputs[out.connectedSlot];
                const NodeType& connectedSlotInitialType = NodeTemplates[connectedNode.templateIndex].inputs[out.connectedSlot].type;

                if (connectedSlot.type == NodeType::Any && out.type != NodeType::Any)
                {
                    connectedSlot.type = out.type;
                }

                else if (out.type == NodeType::Any && connectedSlot.type != NodeType::Any)
                {
                    out.type = connectedSlot.type;
                }

                else if (out.type == NodeType::Any && connectedSlot.type == NodeType::Any)
                {
                    out.type = initialType;
                    connectedSlot.type = connectedSlotInitialType;
                }

                if (out.type != initialType)
                {
                    finalType = out.type;
                    isConnected = true;
                }
            }
            else
            {
                out.type = initialType;
            }
        }

        if (isConnected)
        {
            isConnectedToValue = true;
            for (auto& in : currentNode.inputs) if (in.type == NodeType::Any) in.type = finalType;
            for (auto& out : currentNode.outputs) if (out.type == NodeType::Any) out.type = finalType;
        }
        for (const Slot& s : currentNode.inputs)
        {
            if (s.connectedNode > -1 && visited.find(s.connectedNode) == visited.end())
            {
                queue.push_back(s.connectedNode);
                visited.insert(s.connectedNode);
            }
        }
        for (const Slot& s : currentNode.outputs)
        {
            if (s.connectedNode > -1 && visited.find(s.connectedNode) == visited.end())
            {
                queue.push_back(s.connectedNode);
                visited.insert(s.connectedNode);
            }
        }
    }

    if (!isConnectedToValue)
    {
        for (auto& index : visited)
        {
            Node& currentNode = mNodes[index];

            for (int i = 0; i < currentNode.inputs.size(); i++)
            {
                NodeType initialType = NodeTemplates[currentNode.templateIndex].inputs[i].type;
                
                currentNode.inputs[i].type = initialType;
            }

            for (int i = 0; i < currentNode.outputs.size(); i++)
            {
                NodeType initialType = NodeTemplates[currentNode.templateIndex].outputs[i].type;

                currentNode.outputs[i].type = initialType;
            }
        }
    }
}

void MaterialGraphEditorPanel::AddNode(const NodeTemplate& node, const Vector2& pos)
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

void MaterialGraphEditorPanel::DelLink(GraphEditor::LinkIndex linkIndex)
{
    if (linkIndex >= mLinks.size())     return;

    GraphEditor::Link link = mLinks[linkIndex];

    if (link.mInputNodeIndex >= 0 && link.mInputNodeIndex < (GraphEditor::NodeIndex)mNodes.size() &&
        link.mOutputNodeIndex >= 0 && link.mOutputNodeIndex < (GraphEditor::NodeIndex)mNodes.size())
    {
        Node& inputNode = mNodes[link.mInputNodeIndex];   // sender
        Node& outputNode = mNodes[link.mOutputNodeIndex]; // receiver

        if (link.mInputSlotIndex >= 0 && link.mInputSlotIndex < (GraphEditor::SlotIndex)inputNode.outputs.size())
        {
            inputNode.outputs[link.mInputSlotIndex].connectedNode = -1;
            inputNode.outputs[link.mInputSlotIndex].connectedSlot = -1;
        }

        if (link.mOutputSlotIndex >= 0 && link.mOutputSlotIndex < (GraphEditor::SlotIndex)outputNode.inputs.size())
        {
            outputNode.inputs[link.mOutputSlotIndex].connectedNode = -1;
            outputNode.inputs[link.mOutputSlotIndex].connectedSlot = -1;
        }
    }

    mLinks.erase(mLinks.begin() + linkIndex);

    PropagateNodeType(link.mInputNodeIndex);
    PropagateNodeType(link.mOutputNodeIndex);
}

void MaterialGraphEditorPanel::CustomDraw(ImDrawList* drawList, ImRect rect, GraphEditor::NodeIndex nodeIndex)
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

const size_t MaterialGraphEditorPanel::GetTemplateCount()
{
    return sizeof(mTemplates) / sizeof(GraphEditor::Template);
}

const GraphEditor::Template MaterialGraphEditorPanel::GetTemplate(GraphEditor::NodeIndex index)
{
    return mTemplates[index];
}

const size_t MaterialGraphEditorPanel::GetNodeCount()
{
    return mNodes.size();
}

const GraphEditor::Node MaterialGraphEditorPanel::GetNode(GraphEditor::NodeIndex index)
{
    const auto& n = mNodes[index];
    return GraphEditor::Node{
        n.name,
        n.templateIndex,
        ImRect(ImVec2(n.pos.x - n.size.x * 0.5 , n.pos.y - n.size.y * 0.5), ImVec2(n.pos.x + n.size.x * 0.5, n.pos.y + n.size.y * 0.5)),
        n.mSelected
    };
}

const size_t MaterialGraphEditorPanel::GetLinkCount()
{
    return mLinks.size();
}

const GraphEditor::Link MaterialGraphEditorPanel::GetLink(GraphEditor::LinkIndex index)
{
    return mLinks[index];
}

void MaterialGraphEditorPanel::HandleInputs()
{
    ImGuiIO& io = ImGui::GetIO();

    if (mSelectedNode != -1 && !ImGui::IsAnyItemActive() && mSelectedNode != 0)
    {
        if (ImGui::IsKeyPressed(ImGuiKey_Delete) || ImGui::IsKeyPressed(ImGuiKey_Backspace))
        {
            int nodeToDelete = mSelectedNode;

            for (int i = (int)mLinks.size() - 1; i >= 0; --i)
            {
                const auto& link = mLinks[i];
                if (link.mInputNodeIndex == nodeToDelete || link.mOutputNodeIndex == nodeToDelete)
                {
                    DelLink(i);
                }
            }

            mNodes.erase(mNodes.begin() + nodeToDelete);
            mSelectedNode = -1;

            for (auto& link : mLinks)
            {
                if (link.mInputNodeIndex > nodeToDelete) --link.mInputNodeIndex;
                if (link.mOutputNodeIndex > nodeToDelete) --link.mOutputNodeIndex;
            }

            for (auto& node : mNodes)
            {
                for (auto& slot : node.inputs)
                {
                    if (slot.connectedNode > nodeToDelete)
                    {
                        --slot.connectedNode;
                    }

                    else if (slot.connectedNode == nodeToDelete)
                    {
                        slot.connectedNode = -1;
                    }
                }
                    
                for (auto& slot : node.outputs)
                {
                    if (slot.connectedNode > nodeToDelete)
                    {
                        --slot.connectedNode;
                    }

                    else if (slot.connectedNode == nodeToDelete)
                    {
                        slot.connectedNode = -1;
                    }
                }
            }

            for (int i = 0; i < (int)mNodes.size(); ++i) PropagateNodeType(i);
        }
    }
}

void MaterialGraphEditorPanel::SaveGraphToFile(const std::string filePath)
{
    nlohmann::json data;
    data["nodes"] = nlohmann::json::array();

    for (int i = 0; i < mNodes.size(); ++i)
    {
        const Node& node = mNodes[i];
        nlohmann::json nodeJson;

        nodeJson["templateIndex"] = node.templateIndex;
        nodeJson["pos"] = { node.pos.x, node.pos.y };

        // Inputs
        nodeJson["inputs"] = nlohmann::json::array();
        for (const auto& input : node.inputs)
        {
            nodeJson["inputs"].push_back({
                { "connectedNode", input.connectedNode },
                { "connectedSlot", input.connectedSlot },
                { "type", (int)input.type }
                });
        }

        // Outputs
        nodeJson["outputs"] = nlohmann::json::array();
        for (const auto& output : node.outputs)
        {
            nodeJson["outputs"].push_back({
                { "connectedNode", output.connectedNode },
                { "connectedSlot", output.connectedSlot },
                { "type", (int)output.type }
                });
        }

        data["nodes"].push_back(nodeJson);
    }

    clt::JsonUtility::SaveToFile(filePath, data);
}

void MaterialGraphEditorPanel::LoadGraphFromFile(const std::string filePath)
{
    nlohmann::json data;
    if (!clt::JsonUtility::LoadFromFile(filePath, data))
        return;

    mNodes.clear();
    mLinks.clear();

    struct PendingLink
    {
        GraphEditor::NodeIndex fromNode;
        GraphEditor::SlotIndex fromSlot;
        GraphEditor::NodeIndex toNode;
        GraphEditor::SlotIndex toSlot;
        ImU32 color;
    };
    std::vector<PendingLink> pendingLinks;

    if (!data.contains("nodes"))
        return;

    for (const auto& nodeJson : data["nodes"])
    {
        int templateIndex = nodeJson.value("templateIndex", -1);
        if (templateIndex < 0 || templateIndex >= (int)GetTemplateCount())
            continue;

        Vector2 pos(0.0f, 0.0f);
        if (nodeJson.contains("pos") && nodeJson["pos"].is_array() && nodeJson["pos"].size() == 2)
            pos = Vector2((float)nodeJson["pos"][0], (float)nodeJson["pos"][1]);

        const NodeTemplate& tmpl = NodeTemplates[templateIndex];
        AddNode(tmpl, pos);

        int nodeIndex = (int)mNodes.size() - 1;

        if (nodeJson.contains("inputs"))
        {
            for (int i = 0; i < nodeJson["inputs"].size(); ++i)
            {
                const auto& inSlot = nodeJson["inputs"][i];
                int connectedNode = inSlot.value("connectedNode", -1);
                int connectedSlot = inSlot.value("connectedSlot", -1);

                if (connectedNode != -1 && connectedSlot != -1)
                {
                    ImU32 linkColor = GetLinkColor(connectedNode, connectedSlot);

                    PendingLink link;
                    link.fromNode = connectedNode;
                    link.fromSlot = connectedSlot;
                    link.toNode = nodeIndex;
                    link.toSlot = i;
                    link.color = linkColor;
                    pendingLinks.push_back(link);
                }
            }
        }
    }

    for (const auto& link : pendingLinks)
    {
        if (link.fromNode >= 0 && link.fromNode < (GraphEditor::NodeIndex)mNodes.size() &&
            link.toNode >= 0 && link.toNode < (GraphEditor::NodeIndex)mNodes.size())
        {
            AddLink(link.fromNode, link.fromSlot, link.toNode, link.toSlot, link.color);
        }
    }
}
