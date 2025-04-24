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
};