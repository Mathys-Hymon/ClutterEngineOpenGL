#include "PinManager.h"

PinManager::PinManager(std::string pName) : clt::Actor(pName)
{
	GetLevel()->AddActor<clt::Actor>();
}

PinManager::~PinManager()
{
	pin.clear();
}

void PinManager::RespawnPins()
{

}
