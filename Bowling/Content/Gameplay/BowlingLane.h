#pragma once
#include "Core/All.h"

class BowlingLane : public clt::Actor
{
	std::vector<clt::Actor*> mPinsLeft;
	std::vector<clt::Actor*> mPinsRight;

public:

	BowlingLane(clt::Level* pLevel, std::string pName, bool isStatic, Vector3 location = {0,0,0});
	~BowlingLane();

	void RespawnPins(bool leftLane = true, bool isStatic = false);

	void Update() override;
};