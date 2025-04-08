#pragma once
#include <Core/CCommon.h>
#include <Core/ActorComponent/Actor.h>

namespace clt
{
	class CLUTTER_API CubeActor : public Actor
	{
	public:
		CubeActor(Level* pLevel, std::string pName, Vector2 pTiling = {4,4}, bool pTesselate = false);
		CubeActor(Level* pLevel, std::string pName, bool pTesselate, Vector2 pTiling = { 4,4 });

		~CubeActor() = default;
	};
}

