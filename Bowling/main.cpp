#include <Application/Application.h>
#include <Maps/MainMenuMap.h>
#include <Maps/LevelMap.h>

int main()
{
    clt::Application app(1280.0f, 720.0f, "Bowling Game", { new LevelMap()});

    return 0;
}