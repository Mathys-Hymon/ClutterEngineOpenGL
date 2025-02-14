#include "DoorsAndButtonsApp.h"

DoorsAndButtonsApp::DoorsAndButtonsApp(int pWidth, int pHeight, std::string pName) : clt::Application(pWidth, pHeight, pName)
{
}

DoorsAndButtonsApp::~DoorsAndButtonsApp()
{
}

void DoorsAndButtonsApp::Update()
{
	std::cout << "update";
}

void DoorsAndButtonsApp::Render()
{
}
