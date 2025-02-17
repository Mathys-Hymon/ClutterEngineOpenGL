#pragma once
#include <Core/CCommon.h>
#include <string>

namespace clt
{
	/**
  * @class Texture
  * @brief Represents a texture in the engine.
  */
	class CLUTTER_API Texture
	{
		u32 mID; ///< OpenGL texture ID
		int mWidth; ///< Width of the texture
		int mHeight; ///< Height of the texture
		int mChannels; ///< Number of color channels in the texture

		/**
   * @brief Constructs a Texture object.
   * @param pID OpenGL texture ID
   * @param pWidth Width of the texture
   * @param pHeight Height of the texture
   * @param pChannels Number of color channels in the texture
   */
		Texture(u32 pID, int pWidth, int pHeight, int pChannels);

		friend class Assets;

	public:
		/**
   * @brief Destroys the Texture object.
   */
		~Texture();

		/**
   * @brief Binds the texture to a specified slot.
   * @param slot The slot to bind the texture to (default is 0).
   */
		void Bind(u32 slot = 0) const;

		/**
   * @brief Unbinds the texture.
   */
		void UnBind() const;

		/**
   * @brief Gets the width of the texture.
   * @return The width of the texture.
   */
		inline int GetWidth() const { return mWidth; };

		/**
   * @brief Gets the height of the texture.
   * @return The height of the texture.
   */
		inline int GetHeight() const { return mHeight; };

		/**
   * @brief Gets the OpenGL texture ID.
   * @return The OpenGL texture ID.
   */
		inline u32 GetID() const { return mID; };
	};
}