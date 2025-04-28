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
	
	clt::SpriteElement* mSprite;

public:
	BowlingController();
	~BowlingController() = default;

	void Start() override;
		 
	void Move(float movement);
	void ChangeMod();

	void ChargeShoot();
	void Shoot();


	virtual void Update() override;
};