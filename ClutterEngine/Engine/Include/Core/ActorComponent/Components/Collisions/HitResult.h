#pragma once
#include <Core/CCommon.h>

struct CLUTTER_API hitResult
{
	bool Hit;
	class Actor* HitActor;
	class Component* HitComponent;

	Vector2 hitLocation;
	Vector2 hitNormal;
};