#pragma once
#include <Core/CCommon.h>

namespace clt
{
	struct CLUTTER_API Character
	{
		unsigned int TextureID;
		glm::ivec2 Size;
		glm::ivec2 Bearing;
		unsigned int Advance;
	};

	class CLUTTER_API Font
	{

	};
}