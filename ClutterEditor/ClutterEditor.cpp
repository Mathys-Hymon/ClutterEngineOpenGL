#include <Application/EditorApplication.h>
#include <Maps/MainMenuMap.h>
#include <Maps/LevelMap.h>

int main()
{
    EditorApplication editor({ new LevelMap });
	return 0;
}