#include "pch.h"
#include "OutlinerPanel.h"
#include "imgui.h"

clt::editor::OutlinerPanel::OutlinerPanel(EditorContext* context) : EditorPanel(context)
{
}

const char* clt::editor::OutlinerPanel::GetName() const
{
    return "Outliner";
}

clt::editor::DockPosition clt::editor::OutlinerPanel::GetDockingPos() const
{
    return DockPosition::left;
}

void clt::editor::OutlinerPanel::Draw()
{
}
