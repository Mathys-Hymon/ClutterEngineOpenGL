#include "pch.h"
#include <Core/Assets/AssetsType/Texture.h>

using namespace clt;

Texture::Texture(GLuint pID, int pWidth, int pHeight, int pChannels) : mID(pID), mWidth(pWidth), mHeight(pHeight), mChannels(pChannels)
{
}

Texture::~Texture()
{
	glDeleteTextures(1, &mID);
}

void Texture::Bind(GLuint slot) const
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
