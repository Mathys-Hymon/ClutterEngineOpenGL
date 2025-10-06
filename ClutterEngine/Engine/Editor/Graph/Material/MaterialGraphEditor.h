#pragma once
#include <vector>
#include <string>
#include <Editor/Graph/Material/NodeTemplate.h>


namespace clt
{
    struct CLUTTER_API InvalidLinkFeedback
    {
        bool active = false;
        std::string message;
        ImVec2 position;
        float timer = 0.0f;
        float totalTimer = 0.0f;
    };

    class CLUTTER_API MaterialGraphEditor : public GraphEditor::Delegate
    {
        std::vector<Node> mNodes;
        std::vector<GraphEditor::Link> mLinks;
        static const GraphEditor::Template mTemplates[];

        int mSelectedNode{ -1 };
        InvalidLinkFeedback mInvalidLink;

    public:

        bool mOpenContextMenu{ false };
        ImVec2 mContextMenuPos;

        MaterialGraphEditor();

        bool AllowedLink(GraphEditor::NodeIndex inputNodeIndex, GraphEditor::SlotIndex inputSlotIndex, GraphEditor::NodeIndex outputNodeIndex, GraphEditor::SlotIndex outputSlotIndex) override;
        void SelectNode(GraphEditor::NodeIndex nodeIndex, bool selected) override;
        void MoveSelectedNodes(const ImVec2 delta) override;
        void RightClick(GraphEditor::NodeIndex nodeIndex,
            GraphEditor::SlotIndex slotIndexInput,
            GraphEditor::SlotIndex slotIndexOutput) override;
        void AddLink(GraphEditor::NodeIndex inputNodeIndex, GraphEditor::SlotIndex inputSlotIndex,
            GraphEditor::NodeIndex outputNodeIndex, GraphEditor::SlotIndex outputSlotIndex, ImU32 nodeColor) override;
        GraphEditor::LinkIndex GetLinkConnectedToInput(GraphEditor::NodeIndex nodeIndex, GraphEditor::SlotIndex inputSlotIndex) override;
        ImU32 GetLinkColor(GraphEditor::NodeIndex outputNodeIndex, GraphEditor::SlotIndex outputSlotIndex);

        void PropagateNodeType(GraphEditor::NodeIndex startNodeIndex);
        void AddNode(const NodeTemplate& node, const Vector2& pos);
        void DelLink(GraphEditor::LinkIndex linkIndex) override;
        void CustomDraw(ImDrawList* drawList, ImRect rectangle, GraphEditor::NodeIndex nodeIndex) override;

        const size_t GetTemplateCount() override;
        const GraphEditor::Template GetTemplate(GraphEditor::NodeIndex index) override;
        const size_t GetNodeCount() override;
        const GraphEditor::Node GetNode(GraphEditor::NodeIndex index) override;
        const size_t GetLinkCount() override;
        const GraphEditor::Link GetLink(GraphEditor::LinkIndex index) override;

        void SaveGraphToFile(const std::string filePath);
        void LoadGraphFromFile(const std::string filePath);
    };

}
