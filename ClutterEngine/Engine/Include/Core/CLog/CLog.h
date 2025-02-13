#pragma once

#include <iostream>
#include <sstream>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[92m"

#define CLUTTER_ERROR(message)\
{\
std::stringstream m;\
m << RED << "CLUTTER ENGINE Error: " << message << RESET << std::endl;\
throw std::runtime_error(m.str());\
}

// Warning handling

#define CLUTTER_WARNING(message)\
std::wclog << YELLOW << "CLUTTER ENGINE Warning: " << message << RESET << std::endl;

// Info handling

#define CLUTTER_INFO(message)\
std::wclog << GREEN << "CLUTTER ENGINE Info: " << message << RESET << std::endl;

// Log handling
#define CLUTTER_LOG(message)\
std::wclog << "CLUTTER ENGINE Log: " << message << std::endl;