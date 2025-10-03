#include <pch.h>
#include "MaterialGraphEditor.h"
#include "GraphEditor.h"
#include "imgui.h"
#include "imgui_internal.h"

using namespace clt;

// --- Templates statiques ---
static const char* inputs_add[] = { "A", "B" };
static const char* outputs_add[] = { "Result" };

static const char* inputs_return[] = { "Base Color", "Metallic", "Specular", "Roughness", "Emissive Color", "Opacity", "Normal", "World Position Offset", "Ambiant Occlusion", "Pixel Depth Offset"};

static const char* inputs_math[] = { "A", "B" };
static const char* outputs_math[] = { "Result" };

static const char* outputs_float[] = { "Value" };
static const char* outputs_vec2[] = { "Value" };
static const char* outputs_vec3[] = { "Value" };


static const char* inputs_texture[] = { "UV" };
static const char* outputs_texture[] = { "Texture" };

static ImU32 template1_colors_in[] = { IM_COL32(200,100,100,255), IM_COL32(100,200,100,255), IM_COL32(100,100,200,255) };
static const char* template1_outputs[] = { "MyOutput0" };
static ImU32 template1_colors_out[] = { IM_COL32(200,200,200,255) };

const GraphEditor::Template MaterialGraphEditor::mTemplates[] = 
{
    { IM_COL32(80,80,100,255), IM_COL32(100,100,140,255), IM_COL32(90,90,120,255), 10, inputs_return, nullptr, 0, nullptr, nullptr }, // OutResult
    { IM_COL32(80,80,100,255), IM_COL32(100,100,140,255), IM_COL32(90,90,120,255), 2, inputs_math, nullptr, 1, outputs_math, nullptr }, // ADD
    { IM_COL32(80,80,100,255), IM_COL32(100,100,140,255), IM_COL32(90,90,120,255), 2, inputs_math, nullptr, 1, outputs_math, nullptr }, // MULTIPLY
    { IM_COL32(80,80,100,255), IM_COL32(100,100,140,255), IM_COL32(90,90,120,255), 2, inputs_math, nullptr, 1, outputs_math, nullptr }, // DIVIDE
    { IM_COL32(80,80,100,255), IM_COL32(100,100,140,255), IM_COL32(90,90,120,255), 0, nullptr, nullptr, 1, outputs_float, nullptr },
    { IM_COL32(80,80,100,255), IM_COL32(100,100,140,255), IM_COL32(90,90,120,255), 0, nullptr, nullptr, 1, outputs_vec2, nullptr },
    { IM_COL32(80,80,100,255), IM_COL32(100,100,140,255), IM_COL32(90,90,120,255), 0, nullptr, nullptr, 1, outputs_vec3, nullptr },
    { IM_COL32(80,80,100,255), IM_COL32(100,100,140,255), IM_COL32(90,90,120,255), 1, inputs_texture, nullptr, 1, outputs_texture, nullptr }
};

// --- Constructeur ---
MaterialGraphEditor::MaterialGraphEditor()
{
    mNodes = {
        {"OutResult", 0, Vector2{100,100}, Vector2{100,400}, false},
    };
}

// --- Delegate overrides ---
bool MaterialGraphEditor::AllowedLink(GraphEditor::NodeIndex a, GraphEditor::NodeIndex b)
{
    if (a == b) return false;

    return true;
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
    GraphEditor::NodeIndex outputNodeIndex, GraphEditor::SlotIndex outputSlotIndex)
{
    mLinks.push_back({ inputNodeIndex, inputSlotIndex, outputNodeIndex, outputSlotIndex });
}

void MaterialGraphEditor::AddNode(const char* name, size_t templateIndex, const Vector2& pos, const Vector2& size)
{
    mNodes.push_back({ name, templateIndex, pos, size , false });
}

void MaterialGraphEditor::DelLink(GraphEditor::LinkIndex linkIndex)
{
    mLinks.erase(mLinks.begin() + linkIndex);
}

void MaterialGraphEditor::CustomDraw(ImDrawList* drawList, ImRect rect, GraphEditor::NodeIndex)
{
    drawList->AddLine(rect.Min, rect.Max, IM_COL32(0, 0, 0, 255));
    drawList->AddText(rect.Min, IM_COL32(255, 128, 64, 255), "Draw");
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
