#pragma once
#include <Core/All.h>

class BowlingBall : public clt::Actor, public clt::ICollisionListener
{

public:
	BowlingBall(clt::Level* pLevel, std::string pName = "Actor");
	~BowlingBall() = default;

	virtual void OnCollisionEnter(clt::ColliderComponent* collider, const hitResult& result) override;
};