#include "pch.h"
#include <Core/Assets/AssetsType/Texture.h>

using namespace clt;

Texture::Texture(GLuint pID, int pWidth, int pHeight, int pChannels) : mID(pID), mWidth(pWidth), mHeight(pHeight), mChannels(pChannels)
{
}
