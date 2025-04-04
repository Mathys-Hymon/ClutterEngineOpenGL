#pragma once
#include <Core/ActorComponent/Actor.h>
#include <Core/Assets/Assets.h>

namespace clt
{
	class CLUTTER_API Cube : public Actor
	{

	public:
		 Cube(Level* pLevel, const char* name, Vector2 mTiling = {4,4});
		 Cube(Level* pLevel, std::string name, Vector2 mTiling = { 4,4 });
		 Cube(Level* pLevel, std::string name, std::string texture, Vector2 mTiling = { 4,4 });
		 Cube(Level* pLevel, std::string name, Texture* texture, Vector2 mTiling = { 4,4 });

		~Cube() = default;
	};
}