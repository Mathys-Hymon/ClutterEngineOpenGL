#pragma once
#include <Core/Levels/Level.h>
#include <string>

class MainMap : public clt::Level
{
public:
	MainMap(std::string pName = "MainMap");
	~MainMap();

	void Load() override;
	void Update() override;
	void Close() override;
};