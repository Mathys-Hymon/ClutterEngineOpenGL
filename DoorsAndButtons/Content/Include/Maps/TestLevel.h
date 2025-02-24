#pragma once
#include <Core/Levels/Level.h>
#include <string>

class TestLevel : public clt::Level
{
public:
	TestLevel(std::string pName = "TestLevel");
	~TestLevel();

	void Load() override;
	void Update() override;
	void Close() override;
};