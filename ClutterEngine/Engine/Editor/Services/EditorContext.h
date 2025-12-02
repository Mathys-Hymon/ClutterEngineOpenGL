#pragma once
#include "Editor/UI/ThemeManager.h"

namespace clt
{
    class Engine;
    class Assets;
    class ThemeManager;
    class FrameBuffer;
    class EditorApplication;
    
    
    namespace editor
    {
        class EventBus;
        class SelectionService;
        class PanelManager;
        
        struct EditorContext
        {
            CEngine* engine = nullptr;
            Assets* assets = nullptr;
            FrameBuffer* sceneFrameBuffer = nullptr;
            
            EventBus* events = nullptr;
            SelectionService* selection = nullptr;
            
            PanelManager* panels = nullptr;  
            ThemeManager* themes = nullptr;
            EditorApplication* app = nullptr;
        };
    }
}
