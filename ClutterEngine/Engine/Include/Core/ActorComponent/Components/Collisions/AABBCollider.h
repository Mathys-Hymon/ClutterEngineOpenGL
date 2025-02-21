#pragma once
#include <Core/ActorComponent/Components/Collisions/Collider2DComponent.h>

namespace clt
{
	class CLUTTER_API AABBCollider : public Collider2DComponent
	{
		Vector2 mBoxExtend;

		bool CheckBoxCollision(Collider2DComponent* pOther);
		bool CheckBoxSphereCollision(Collider2DComponent* pOther);

	public:
		 AABBCollider(Vector2 pBoxExtend = {64,64});
		~AABBCollider() = default;

		virtual bool CheckCollision(Collider2DComponent* pOther) override;

	};
}