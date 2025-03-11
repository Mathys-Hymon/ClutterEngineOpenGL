#include "pch.h"
#include <Graphics/UI/UIPanel.h>
#include <Graphics/UI/WidgetElement.h>

using namespace clt;

void UIPanel::UpdateWidgetOrder(WidgetElement* mElement)
{
    auto it = std::find(mElementsByZOrder.begin(), mElementsByZOrder.end(), mElement);

    if (it != mElementsByZOrder.end()) 
    {
        auto widgetPtr = std::move(*it);
        mElementsByZOrder.erase(it);
    }
}

clt::UIPanel::~UIPanel()
{
    for (WidgetElement* element : mElementsByZOrder)
    {
        delete element;

        element = nullptr;
    }

    mElementsByName.clear();
    mElementsByZOrder.clear();
}

void UIPanel::RemoveElement(const std::string& pName)
{
}

void UIPanel::Update()
{
    for (WidgetElement* element : mElementsByZOrder)        element->Update();
}
