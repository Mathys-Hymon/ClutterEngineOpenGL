#pragma once
#include <Core/Levels/Level.h>
#include <string>

class MainMenuMap : public clt::Level
{
public:
	MainMenuMap(std::string pName = "MainMenu");
	~MainMenuMap();

	void Load() override;
	void Update() override;
	void Close() override;
};