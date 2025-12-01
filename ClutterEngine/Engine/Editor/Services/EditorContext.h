#pragma once

namespace clt
{
    class Engine;
    class Assets;
    class FrameBuffer;
    class Actor;
    
    
    namespace editor
    {
    class EventBus;
    class SelectionService;
        
        struct EditorContext
        {
            CEngine* engine = nullptr;
            Assets* assets = nullptr;
            FrameBuffer* sceneFrameBuffer = nullptr;
            EventBus* events = nullptr;
            SelectionService* selection = nullptr;
        };
    }
}