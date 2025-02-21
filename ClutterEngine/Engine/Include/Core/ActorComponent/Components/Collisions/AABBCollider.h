#pragma once
#include <Core/CCommon.h>
#include <Core/ActorComponent/Components/Collisions/Collider2DComponent.h>

namespace clt
{
	class CLUTTER_API AABBCollider : public Collider2DComponent
	{
		Vector2 mBoxExtend;

	public:
		 AABBCollider(Vector2 pBoxExtend = {32,32});
		~AABBCollider() = default;

		virtual bool CheckCollision(Collider2DComponent* pOther) override;
	};
}