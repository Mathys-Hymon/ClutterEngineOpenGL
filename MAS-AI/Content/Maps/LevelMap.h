#pragma once
#include <Core/Levels/Level.h>
#include <string>

class LevelMap : public clt::Level
{
	float tempTime;
public:
	LevelMap(std::string pName = "Level");
	~LevelMap();

	void Load() override;
	void Update() override;
	void Close() override;
};