#include <Application/Application.h>
#include <Maps/TestLevel.h>

int main()
{
    clt::Application app(1280.0f, 720.0f, "Doors and Buttons", {new TestLevel()});

    return 0;
}