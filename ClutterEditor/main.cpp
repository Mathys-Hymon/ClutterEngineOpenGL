#include <Application/Application.h>
#include <Maps/TestLevel.h>
#include <vector>
#include <string>
#include <iostream>

int main()
{
    clt::Application app(800, 800, "Doors and Buttons", {new TestLevel()});

    return 0;
    
}
