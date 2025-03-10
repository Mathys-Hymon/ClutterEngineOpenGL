#pragma once
#include <Core/ActorComponent/Component.h>
#include <Core/ActorComponent/Components/Collisions/HitResult.h>

namespace clt
{
	class CLUTTER_API ColliderComponent : public Component
	{
	public:
		enum class Type {Null, OBB, Sphere, AABB, Circle };

	protected:

		virtual void SetOwner(Actor* pOwner) override;
		bool mTrigger = false; ///< Indicates if the collider is a trigger.
		Type mType; ///< The type of the collider.

	public:

		float mFriction;
		float mBounciness;

		ColliderComponent() : Component(), mFriction(2.5f), mBounciness(0.3f), mType(Type::Null) {};
		~ColliderComponent() = default;

		virtual bool CheckCollision(ColliderComponent* pOther, hitResult& outResult) const = 0;
		const Type GetType() const { return mType; };

		bool IsTrigger() const { return mTrigger; };
	};
}