#pragma once
#include <Application/Application.h>

class DoorsAndButtonsApp : public clt::Application
{
private:

public:
	DoorsAndButtonsApp(int pWidth, int pHeight, std::string pName);
	~DoorsAndButtonsApp();

	void Update() override;
	void Render() override;
};