#pragma once
#include <Core/CPrerequisites.h>

#ifdef CLUTTERENGINE_EXPORTS
#define CLUTTER_API __declspec(dllexport)
#else
#define CLUTTER_API __declspec(dllimport)
#endif

#include <string>