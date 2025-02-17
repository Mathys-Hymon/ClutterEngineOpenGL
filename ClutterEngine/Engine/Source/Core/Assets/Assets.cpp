#include "pch.h"
#include <Core/CCommon.h>
#include <Core/Assets/Assets.h>
#include <Graphics/Renderer.h>
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

using namespace clt;

Assets* Assets::sInstance = nullptr;

Assets::~Assets()
{
}

Assets& Assets::Get()
{
    if (!sInstance)  sInstance = new Assets();
    return *sInstance;
}

void Assets::LoadTexture(const std::string& path, const std::string& name)
{
    if (mTextures.find(name) != mTextures.end()) return;

    stbi_set_flip_vertically_on_load(true);
    int width, height, channels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (!data) CLUTTER_ERROR("Failed to load texture " + path)
    else
    {
        CLUTTER_LOG(("Texture " + path + " loaded sucessfully ").c_str());
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    GLenum format = channels == 4 ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    mTextures[name] = new Texture(textureID, width, height, channels);
}

Texture* Assets::GetTexture(const std::string& name)
{
    auto it = mTextures.find(name);
    if (it == mTextures.end())
    {
        CLUTTER_WARNING(("Unable to find Texture: " + name).c_str());
        return nullptr;
    }
    mRenderer->RegisterTextureUsage(it->second);
    return it->second;
}

void Assets::ClearTextures()
{
    for (auto& pair : mTextures)
    {
        delete pair.second;
    }
    mTextures.clear();
    delete sInstance;
}
