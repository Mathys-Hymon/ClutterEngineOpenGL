#pragma once
#include <Core/CCommon.h>
#include <map>
#include <glad/glad.h>

namespace clt
{
	struct CLUTTER_API Character
	{
		GLuint TextureID = 0;
		Vector2 Size = Vector2::Zero;
		Vector2 Bearing = Vector2::Zero;
		GLuint Advance = 0;
	};

	class CLUTTER_API Font
	{
	public:
		std::map<GLchar, Character> mCharacters;

		Font() {};
		~Font() = default;
	};
}