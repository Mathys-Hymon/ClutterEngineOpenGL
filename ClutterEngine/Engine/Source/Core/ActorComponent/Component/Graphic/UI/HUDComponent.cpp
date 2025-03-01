#include "pch.h"
#include <Core/ActorComponent/Components/Graphics/UI/HUDComponent.h>

using namespace clt;

void HUDComponent::Draw(RendererGL& pRenderer)
{
	if (mCurrentWidget) mCurrentWidget->Draw();
}
