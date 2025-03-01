#include "pch.h"
#include <Graphics/UI/UIPanel.h>

using namespace clt;

void UIPanel::UpdateWidgetOrder(WidgetElement* mElement)
{
    auto it = std::find(mElementsByZOrder.begin(), mElementsByZOrder.end(), mElement);

    if (it != mElementsByZOrder.end()) {
        auto widgetPtr = std::move(*it);
        mElementsByZOrder.erase(it);
}
