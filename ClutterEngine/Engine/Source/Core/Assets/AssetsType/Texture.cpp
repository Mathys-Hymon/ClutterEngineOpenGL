#include "pch.h"
#include <glad/glad.h>
#include <Core/Assets/AssetsType/Texture.h>

using namespace clt;

Texture::Texture(u32 pID, int pWidth, int pHeight, int pChannels) : mID(pID), mWidth(pWidth), mHeight(pHeight), mChannels(pChannels)
{
}

Texture::~Texture()
{
	glDeleteTextures(1, &mID);
}

void Texture::Bind(u32 slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, mID);
}

void Texture::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::UpdateInfo(int& rWidth, int& rHeight)
{
	rWidth = mWidth;
	rHeight = mHeight;
}
