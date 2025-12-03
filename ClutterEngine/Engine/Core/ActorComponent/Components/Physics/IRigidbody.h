#pragma once
#include <Core/ActorComponent/Component.h>

namespace clt
{
	enum class CLUTTER_API rbState
	{
		Static,
		Dynamic,
		Kinematic
	};

	NLOHMANN_JSON_SERIALIZE_ENUM(rbState, {
		{rbState::Dynamic, "Dynamic"},
		{rbState::Static, "Static"},
		{rbState::Kinematic, "Kinematic"}
	})
	
	class CLUTTER_API IRigidbody : public Component
	{
	public:
		IRigidbody(int drawOrder = 0) : Component(drawOrder) {};
		virtual ~IRigidbody() = default;

		virtual void SetState(rbState state) = 0;
		virtual rbState GetState() = 0;

		virtual void SetMass(float mass) = 0;
		virtual float GetMass() const = 0;

		virtual void SetVelocity(const Vector3& vel) = 0;
		virtual Vector3 GetVelocity() const = 0;

		virtual void AddForce(const Vector3& force) = 0;
		virtual void AddImpulse(const Vector3& impulse) = 0;

		virtual void AddForceAtLocation(const Vector3& force, const Vector3& relativeLoc) = 0;
		virtual void AddImpulseAtLocation(const Vector3& impulse, const Vector3& relativeLoc) = 0;

		virtual void AttachCollider(class ICollider* collider) = 0;
		virtual void RemoveCollider(class ICollider* collider) = 0;

		virtual void SetCustomGravity(const Vector3& gravity) = 0;

		virtual void LockRotation(bool x, bool y, bool z) = 0;
		virtual void LockPosition(bool x, bool y, bool z) = 0;
	};
}