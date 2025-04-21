#pragma once
#include <Core/ActorComponent/Component.h>
#include <Core/ActorComponent/Components/Collisions/HitResult.h>

namespace clt
{
	enum class CLUTTER_API ColliderType { Null, OBB, Sphere, AABB, Circle };

	class CLUTTER_API ColliderComponent : public Component
	{

	protected:

		virtual void SetOwner(Actor* pOwner) override;
		bool mTrigger = false; ///< Indicates if the collider is a trigger.
		ColliderType mType; ///< The type of the collider.

	public:

		float mFriction;
		float mBounciness;

		ColliderComponent() : Component(), mFriction(2.5f), mBounciness(0.3f), mType(ColliderType::Null) {};
		~ColliderComponent();

		virtual bool CheckCollision(ColliderComponent* pOther, hitResult& outResult) const = 0;
		const ColliderType GetType() const { return mType; };

		bool IsTrigger() const { return mTrigger; };
	};
}