#pragma once
#include <Core/All.h>

class BowlingController : public clt::PlayerController
{
	enum class mode
	{
		movement,
		rotation,
		shoot,
	};

	mode mMode;
	float mShootForce;

	float mRotation;

public:
	BowlingController();
	~BowlingController() = default;

	void Move(float movement);
	void ChangeMod();

	virtual void Update() override;
};