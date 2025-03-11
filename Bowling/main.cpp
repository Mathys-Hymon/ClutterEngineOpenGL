#include <Application/Application.h>
#include <Maps/MainMap.h>

int main()
{
    clt::Application app(1280.0f, 720.0f, "Bowling Game", { new MainMap() });

    return 0;
}