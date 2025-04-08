#pragma once
#include <Core/CCommon.h>
#include <Core/ActorComponent/Actor.h>

namespace clt
{
	class CLUTTER_API CubeActor : public Actor
	{
	public:
		CubeActor(Level* pLevel, std::string pName);
	};
}

