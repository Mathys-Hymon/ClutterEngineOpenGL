#include "pch.h"
#include "PluginsPanel.h"

clt::editor::PluginsPanel::PluginsPanel(EditorContext* context) : EditorPanel(context)
{
    Close();
}

const char* clt::editor::PluginsPanel::GetName() const
{
    return "Plugins Manager";
}

void clt::editor::PluginsPanel::Draw()
{
}
