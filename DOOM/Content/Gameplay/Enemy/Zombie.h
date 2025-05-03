#pragma once
#include "Core/All.h"

class Zombie : public clt::Actor
{
	int life;
public:
	Zombie(clt::Level* pLevel, std::string pName = "zombie");
	~Zombie();

	void Start() override;

	void GetHit();
};