#include "pch.h"
#include "ViewportToolBarPanel.h"
#include "imgui.h"

clt::editor::ViewportToolBarPanel::ViewportToolBarPanel(EditorContext* context) : EditorPanel(context)
{
}

const char* clt::editor::ViewportToolBarPanel::GetName() const
{
    return "Viewport ToolBar";
}

clt::editor::DockPosition clt::editor::ViewportToolBarPanel::GetDockingPos() const
{
    return DockPosition::top;
}

void clt::editor::ViewportToolBarPanel::Draw()
{
}
