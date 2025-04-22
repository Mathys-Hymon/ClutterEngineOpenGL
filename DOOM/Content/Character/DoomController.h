#pragma once
#include <Core/All.h>

enum class Weapons
{
	Hand,
	Pistol,
	ShotGun,
};

class DoomController : public clt::PlayerController
{
	float mRotationVelocity;
	Vector2 mMovementVelocity;

	clt::AnimatorElement* mHand;

	Weapons mWeapon;

public:

	DoomController();
	~DoomController() = default;

	virtual void Start() override;

	void RotateCamera(Vector2 movement);
	void Move(Vector2 movement);

	void Shoot();

	virtual void Update() override;

	virtual void OnCollisionEnter(const hitResult& result) override {};
	virtual void OnCollisionStay(const hitResult& result)  override {};
	virtual void OnCollisionExit(const hitResult& result)  override {};

	virtual void OnTriggerEnter(const hitResult& result) override {};
	virtual void OnTriggerStay(const hitResult& result)  override {};
	virtual void OnTriggerExit(const hitResult& result)  override {};
};