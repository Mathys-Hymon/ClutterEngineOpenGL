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

void UIPanel::RemoveElement(const std::string& pName)
{
}

void UIPanel::Draw()
{
    for (WidgetElement* element : mElementsByZOrder)
    {
        if(element->mVisibility ) element->Draw();
    }
}

void UIPanel::Update()
{
    for (WidgetElement* element : mElementsByZOrder)
    {
        element->Update();
    }
}
