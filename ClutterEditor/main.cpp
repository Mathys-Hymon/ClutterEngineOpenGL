#include "Application.h"
#include <string>
#include <iostream>


int main()
{
    std::cout << "Clutter Editor" << std::endl;
	Application app; // Create an instance of the application
    app.Run(); // Run the application loop for the editor
    return 0;
    
}
