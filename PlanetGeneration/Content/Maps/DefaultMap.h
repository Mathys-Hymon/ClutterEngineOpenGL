#pragma once
#include <Core/Levels/Level.h>
#include <string>

class DefaultMap : public clt::Level
{
public:
	DefaultMap(std::string pName = "Level");
	~DefaultMap();

	void Load() override;
	void Update() override;
	void Close() override;
};