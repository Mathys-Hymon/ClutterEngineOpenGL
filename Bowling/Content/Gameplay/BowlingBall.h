#pragma once
#include <Core/All.h>

class BowlingBall : public clt::Actor
{
public:

	BowlingBall(clt::Level* pLevel, std::string pName = "Actor");
	~BowlingBall() = default;

	void Update() override;
};