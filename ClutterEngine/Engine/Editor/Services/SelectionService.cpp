#include "pch.h"
#include "SelectionService.h"

void clt::editor::SelectionService::Notify()
{
    for (auto& cb : mCallbacks)
    {
        cb();
    }
}

void clt::editor::SelectionService::Selected(void* object)
{
    mSelection.clear();
    if (object) mSelection.push_back(object);
    Notify();
}

void clt::editor::SelectionService::AddToSelection(void* object)
{
    if (!object) return;
    mSelection.push_back(object);
    Notify();
}

void clt::editor::SelectionService::RemoveFromSelection(void* object)
{
    auto it = std::find(mSelection.begin(), mSelection.end(), object);
    if (it != mSelection.end())
    {
        mSelection.erase(it);
        Notify();
    }
}

void clt::editor::SelectionService::ClearSelection()
{
    mSelection.clear();
    Notify();
}

void clt::editor::SelectionService::RegisterCallback(const SelectionChangedCallback& callback)
{
    mCallbacks.push_back(callback);
}
