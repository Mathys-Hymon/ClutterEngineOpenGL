#pragma once
#include <Core/All.h>

class PinManager : public clt::Actor
{
	std::vector<clt::Actor*> pin;

public :

	PinManager(std::string pName);
	~PinManager();

	void RespawnPins();
};