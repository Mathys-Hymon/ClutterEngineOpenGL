#include "pch.h"
#include "InspectorPanel.h"
#include "imgui.h"

clt::editor::InspectorPanel::InspectorPanel(EditorContext* context) : EditorPanel(context)
{
}

const char* clt::editor::InspectorPanel::GetName() const
{
    return "Inspector";
}

clt::editor::DockPosition clt::editor::InspectorPanel::GetDockingPos() const
{
    return DockPosition::right;
}

void clt::editor::InspectorPanel::Draw()
{
}
