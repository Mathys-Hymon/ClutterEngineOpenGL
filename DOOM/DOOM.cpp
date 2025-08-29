#include <Application/Application.h>
#include <Maps/MainMenuMap.h>
#include <Maps/LevelMap.h>

int main()
{

    clt::Application app({new MainMenuMap, new LevelMap});

    return 0;
}