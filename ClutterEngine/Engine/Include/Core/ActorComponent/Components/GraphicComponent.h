#pragma once
#include <Core/ActorComponent/Component.h>
#include <Core/Levels/CLevel.h>
#include <Graphics/Renderer.h>
#include <Core/ActorComponent/Actor.h>

namespace clt
{
	class GraphicComponent : public Component
	{
	protected:
		int mDrawOrder;

	public:
		GraphicComponent(Actor* pOwner, int pDrawOrder = 0) : mDrawOrder(pDrawOrder), Component(pOwner, pDrawOrder) 
		{ 
			pOwner->GetLevel().GetRenderer().AddGraphicComponent(this);
		};
		virtual ~GraphicComponent() = default;

		int GetDrawOrder() const { return mDrawOrder; };
	};
}