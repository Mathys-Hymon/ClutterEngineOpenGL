#include <Application/Application.h>
#include <Maps/DefaultMap.h>
#include <iostream>

int main()
{
    clt::Application app(1280.0f, 720.0f, "PlanetGeneration", { new DefaultMap() });

    return 0;
}