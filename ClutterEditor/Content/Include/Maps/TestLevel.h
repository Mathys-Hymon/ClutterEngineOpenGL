#pragma once
#include <Core/Levels/CLevel.h>
#include <string>

class TestLevel : public clt::CLevel
{
public:
	TestLevel(std::string pName = "TestLevel");
	~TestLevel();
};