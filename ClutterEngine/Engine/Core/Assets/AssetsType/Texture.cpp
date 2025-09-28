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
	glActiveTexture(GL_TEXTURE0);
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

unsigned char* Texture::GetPixels()
{
    if (!mPixels.empty())
        return mPixels.data();

    if (mID == 0) return nullptr;

    glBindTexture(GL_TEXTURE_2D, mID);

    mPixels.resize(mWidth * mHeight * 4);

    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, mPixels.data());

    glBindTexture(GL_TEXTURE_2D, 0);
    return mPixels.data();
}
