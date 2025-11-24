#include <Application/EditorApplication.h>
#include <Maps/LevelMap.h>

int main()
{
    clt::EditorApplication app({new LevelMap});

    return 0;
}