#pragma once
#include <Core/ActorComponent/Components/Physics/ICollider.h>
#include <Bullet/bullet/btBulletDynamicsCommon.h>

namespace clt
{
	class CLUTTER_API BulletCollider :public ICollider
	{
		ColliderShapeType mType;
		Vector3 mbounds;
		btCollisionShape* mShape;
		bool mIsTrigger;

	public:
		CLUTTER_CLASS(BulletCollider);
		
		void SetupProperties() override 
		{
			CPROPERTY(mType, clt::PropMode::ReadWrite);
			CPROPERTY(mbounds, clt::PropMode::ReadWrite);
			RegisterProperty("Bounds", &mBounds, clt::PropMode::ReadWrite);
			CPROPERTY(mIsTrigger, clt::PropMode::ReadWrite);
		}
		
		
		BulletCollider(ColliderShapeType shape = ColliderShapeType::Box, Vector3 bounds = {1,1,1});
		~BulletCollider();

		void Start() override;

		void SetShape(ColliderShapeType shape, Vector3 bounds) override;
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