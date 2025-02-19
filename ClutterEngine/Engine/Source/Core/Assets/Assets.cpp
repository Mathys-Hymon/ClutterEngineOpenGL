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

Texture* Assets::LoadTexture(const std::string& path, const std::string& name, TextureFilter pTexFilter)
{
    if (mTextures.find(name) != mTextures.end()) return GetTexture(name);

    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);

    if (!data)
    {
        CLUTTER_ERROR("Failed to load texture " + path);
        return nullptr;
    }
    else
    {
        CLUTTER_LOG(("Texture " + path + " loaded sucessfully ").c_str());
    }

    GLuint textureID = 0;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if (pTexFilter == TextureFilter::NEAREST)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }


    GLenum format = channels == 4 ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);

    mTextures[name] = new Texture(textureID, width, height, channels);

    return mTextures[name];
}

Texture* Assets::GetTexture(const std::string& name)
{
    auto it = mTextures.find(name);
    if (it == mTextures.end())
    {
        CLUTTER_WARNING(("Unable to find Texture: " + name).c_str());
        return nullptr;
    }
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
