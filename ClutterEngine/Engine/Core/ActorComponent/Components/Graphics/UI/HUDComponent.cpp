#include "pch.h"
#include <Core/ActorComponent/Components/Graphics/UI/HUDComponent.h>

using namespace clt;

void HUDComponent::ShowWidget(const std::string pName)
{
	auto it = mWidgets.find(pName);

	if (it != mWidgets.end())
	{
		mCurrentWidget = it->second;
	}
}

void HUDComponent::RemoveWidget(const std::string& pName)
{
	auto it = mWidgets.find(pName);

	if (it != mWidgets.end())
	{
		delete it->second;
	}

	mWidgets.erase(it);
}

void HUDComponent::Update()
{
	if (mCurrentWidget) mCurrentWidget->Draw();
}
