#pragma once
#include <Core/ActorComponent/Actor.h>
#include <Core/Assets/Assets.h>

namespace clt
{
	class CLUTTER_API Cube : public Actor
	{

	public:
		 Cube(const char* name);
		 Cube(std::string name);
		 Cube(std::string name, std::string texture);
		 Cube(std::string name, Texture* texture);

		~Cube() = default;
	};
}