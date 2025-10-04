#pragma once
#include <vector>
#include <string>
#include "Node.h"
#include <GraphEditor.h>


namespace clt
{
    class CLUTTER_API MaterialGraphEditor : public GraphEditor::Delegate
    {
    public:
        MaterialGraphEditor();

        bool mOpenContextMenu{false};
        ImVec2 mContextMenuPos;

        bool AllowedLink(GraphEditor::NodeIndex from, GraphEditor::NodeIndex to) override;
        void SelectNode(GraphEditor::NodeIndex nodeIndex, bool selected) override;
        void MoveSelectedNodes(const ImVec2 delta) override;
        void RightClick(GraphEditor::NodeIndex nodeIndex,
            GraphEditor::SlotIndex slotIndexInput,
            GraphEditor::SlotIndex slotIndexOutput) override;
        void AddLink(GraphEditor::NodeIndex inputNodeIndex, GraphEditor::SlotIndex inputSlotIndex,
            GraphEditor::NodeIndex outputNodeIndex, GraphEditor::SlotIndex outputSlotIndex, ImU32 nodeColor) override;
        GraphEditor::LinkIndex GetLinkConnectedToInput(GraphEditor::NodeIndex nodeIndex, GraphEditor::SlotIndex inputSlotIndex) override;

        void AddNode(NodeType type, const char* name, size_t templateIndex, const Vector2& pos, const Vector2& size);
        void DelLink(GraphEditor::LinkIndex linkIndex) override;
        void CustomDraw(ImDrawList* drawList, ImRect rectangle, GraphEditor::NodeIndex nodeIndex) override;

        const size_t GetTemplateCount() override;
        const GraphEditor::Template GetTemplate(GraphEditor::NodeIndex index) override;
        const size_t GetNodeCount() override;
        const GraphEditor::Node GetNode(GraphEditor::NodeIndex index) override;
        const size_t GetLinkCount() override;
        const GraphEditor::Link GetLink(GraphEditor::LinkIndex index) override;

    private:

        std::vector<Node> mNodes;
        std::vector<GraphEditor::Link> mLinks;
        static const GraphEditor::Template mTemplates[];

        int mSelectedNode{ -1 };
    };

}
