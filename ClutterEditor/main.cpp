#include <Application/Application.h>
#include <string>
#include <iostream>

int main()
{
    std::cout << "Clutter Editor" << std::endl;
    clt::Application app(800, 800, "Editor Window");

    app.Run();

    return 0;
    
}
