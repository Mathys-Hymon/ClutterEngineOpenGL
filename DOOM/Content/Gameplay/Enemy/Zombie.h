#pragma once
#include "Core/All.h"

class Zombie : public clt::Actor
{
	int mLife;
	bool mSpriteFlip, mHit;
	int mAnimIndex, mOldAnimIndex;

    clt::AnimatorComponent* mAnimator;

    void GetDirection();

public:
	Zombie(clt::Level* pLevel, std::string pName = "zombie");
	~Zombie();

	void Start() override;
	void Update() override;

	void GetHit();
};