#include "PinManager.h"

PinManager::PinManager(clt::Level* pLevel, std::string pName) : clt::Actor(pLevel, pName)
{
	GetLevel()->AddActor<clt::Actor>("pin");
}

PinManager::~PinManager()
{
	pin.clear();
}

void PinManager::RespawnPins()
{

}
