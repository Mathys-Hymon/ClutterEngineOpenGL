#include "pch.h"
#include <Core/ActorComponent/Components/Graphics/UI/HUDComponent.h>
#include <Graphics/RendererGL.h>
#include <Core/Levels/Level.h>

using namespace clt;

HUDComponent::~HUDComponent()
{
	mOwner->GetLevel()->GetRenderer().RemoveHUDComponent(this);
}

void HUDComponent::SetOwner(Actor* pOwner)
{
	Component::SetOwner(pOwner);
	mOwner->GetLevel()->GetRenderer().AddHUDComponent(this);
}

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
	if (mCurrentWidget) mCurrentWidget->Update();
}
