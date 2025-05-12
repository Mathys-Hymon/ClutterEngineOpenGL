#include <Application/Application.h>
#include <Maps/DefaultMap.h>
#include <iostream>

int main()
{
    clt::Application app({ new DefaultMap() });

    return 0;
}