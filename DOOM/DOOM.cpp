#include <Application/EditorApplication.h>
#include <Maps/MainMenuMap.h>
#include <Maps/LevelMap.h>

int main()
{

    clt::EditorApplication app({"Maps/LevelMap.h"}, { new LevelMap} );

    return 0;
}