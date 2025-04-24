#pragma once
#include "Core/All.h"

class BowlingLane : public clt::Actor, public clt::ICollisionListener
{
	std::vector<clt::Actor*> mPinsLeft;
	std::vector<clt::Actor*> mPinsRight;

public:

	BowlingLane(clt::Level* pLevel, std::string pName, bool isStatic, Vector3 location = {0,0,0});
	~BowlingLane();

	void RespawnPins(bool leftLane = true, bool isStatic = false);

	virtual void OnCollisionEnter(clt::ColliderComponent* collider, const hitResult& result) override;
	virtual void OnCollisionStay(clt::ColliderComponent* collider, const hitResult& result) override;
	virtual void OnCollisionExit(clt::ColliderComponent* collider, const hitResult& result) override;

	virtual void OnTriggerEnter(clt::ColliderComponent* collider, const hitResult& result) override;
	virtual void OnTriggerStay(clt::ColliderComponent* collider, const hitResult& result) override;
	virtual void OnTriggerExit(clt::ColliderComponent* collider, const hitResult& result) override;
};