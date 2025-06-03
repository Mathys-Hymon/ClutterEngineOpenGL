#include <Core/All.h>

class Water : public clt::Actor
{
public:
	Water(clt::Level* pLevel, std::string pName = "Water");
	~Water() = default;
};