#pragma once

namespace clt
{
    class Engine;
    class Assets;
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
            EditorApplication* app = nullptr;
        };
    }
}