#pragma once
#include <Core/CCommon.h>
#include <unordered_map>
#include <glad/glad.h>

namespace clt
{
	struct CLUTTER_API Character
	{
		GLuint TextureID;
		Vector2 Size;
		Vector2 Bearing;
		GLuint Advance;
	};

	class CLUTTER_API Font
	{
	public:
		std::unordered_map<char, Character> mCharacters;

		Font() {};
		~Font() = default;
	};
}