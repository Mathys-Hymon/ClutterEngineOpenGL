#pragma once
#include <Core/ActorComponent/Actor.h>
#include <Core/Assets/Assets.h>

namespace clt
{
	class CLUTTER_API Cube : public Actor
	{

	public:
		 Cube(Level* pLevel, const char* name);
		 Cube(Level* pLevel, std::string name);
		 Cube(Level* pLevel, std::string name, std::string texture);
		 Cube(Level* pLevel, std::string name, Texture* texture);

		~Cube() = default;
	};
}