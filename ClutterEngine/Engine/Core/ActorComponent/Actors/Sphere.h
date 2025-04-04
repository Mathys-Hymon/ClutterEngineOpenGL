#pragma once
#include <Core/ActorComponent/Actor.h>
#include <Core/Assets/Assets.h>

namespace clt
{
	class CLUTTER_API Sphere : public Actor
	{
	public:
		Sphere(Level* pLevel, const char* name, Vector2 mTiling = { 4,4 });
		Sphere(Level* pLevel, std::string name, Vector2 mTiling = { 4,4 });
		Sphere(Level* pLevel, std::string name, std::string texture, Vector2 mTiling = { 4,4 });
		Sphere(Level* pLevel, std::string name, Texture* texture, Vector2 mTiling = { 4,4 });

		~Sphere() = default;
	};
}