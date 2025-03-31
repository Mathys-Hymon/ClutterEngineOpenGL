#pragma once
#include <Core/All.h>

class PinManager : public clt::Actor
{
	std::vector<clt::Actor*> pin;

public :

	PinManager(clt::Level* pLevel, std::string pName);
	~PinManager();

	void RespawnPins();
};