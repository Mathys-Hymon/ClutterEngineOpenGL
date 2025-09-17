#pragma once
#include <Core/ActorComponent/Components/Physics/ICollider.h>
#include <Bullet/bullet/btBulletDynamicsCommon.h>

namespace clt
{
	class CLUTTER_API BulletCollider :public ICollider
	{
		ColliderShapeType mType;
		btCollisionShape* mShape;
		bool mIsTrigger;

	public:
		BulletCollider();
		~BulletCollider();

		void Start() override;

		void SetShape(ColliderShapeType type, const Vector3& size) override;
		ColliderShapeType GetShapeType() const override;

		void SetIsTrigger(bool trigger) override;
		bool IsTrigger() const override;

		virtual void SetFriction(float friction) override;
		virtual float GetFriction() const override;

		virtual void SetBounciness(float bounciness) override;
		virtual float GetBounciness() const override;

		btCollisionShape* GetShape() { return mShape; }

		void Subscribe(class ICollisionListener* listener) override;
	};
}