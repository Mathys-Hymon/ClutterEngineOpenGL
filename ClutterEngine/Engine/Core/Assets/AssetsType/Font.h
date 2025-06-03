#pragma once
#include <Core/CCommon.h>
#include <map>
#include <glad/glad.h>

namespace clt
{
	/**
  * @brief Represents a single character's font data, including texture and metrics.
  */
	struct CLUTTER_API Character
	{
		/**
   * @brief OpenGL texture ID for the glyph.
   */
		GLuint TextureID = 0;

		/**
   * @brief Size of the glyph in pixels.
   */
		Vector2 Size = Vector2::Zero;

		/**
   * @brief Offset from baseline to left/top of glyph.
   */
		Vector2 Bearing = Vector2::Zero;

		/**
   * @brief Horizontal offset to advance to next glyph.
   */
		GLuint Advance = 0;
	};

	/**
  * @brief Represents a font, containing a map of characters and their metrics.
  */
	class CLUTTER_API Font
	{
	public:
		/**
   * @brief Map of character codes to their corresponding Character data.
   */
		std::map<GLchar, Character> mCharacters;

		/**
   * @brief Default constructor for Font.
   */
		Font() {};

		/**
   * @brief Default destructor for Font.
   */
		~Font() = default;
	};
}