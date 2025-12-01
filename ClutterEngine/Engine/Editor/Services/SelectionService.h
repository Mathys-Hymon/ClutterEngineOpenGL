#pragma once
#include <Core/CCommon.h>
#include <functional>

namespace clt
{
    namespace editor
    {
        class CLUTTER_API SelectionService
        {
        public:
            using SelectionChangedCallback  = std::function<void()>;
            
        private:
            void Notify();
            
            std::vector<void*> mSelection;
            std::vector<SelectionChangedCallback> mCallbacks;
            
        public:
            void Selected(void* object);
            
            void AddToSelection(void* object);
            
            void RemoveFromSelection(void* object);
            
            void ClearSelection();
            
            const std::vector<void*>& GetSelection() const { return mSelection; }
            bool IsEmpty() const { return mSelection.empty(); }
            void* GetFirst() const { return mSelection.empty() ? nullptr : mSelection.front(); }
            
            void RegisterCallback(const SelectionChangedCallback& callback);
        };
    }
}

