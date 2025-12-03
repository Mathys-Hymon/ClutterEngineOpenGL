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

void clt::editor::OutlinerPanel::Draw()
{
}
