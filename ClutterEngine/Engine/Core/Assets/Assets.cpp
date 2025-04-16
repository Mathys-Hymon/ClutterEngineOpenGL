#include "pch.h"
#include <Core/CCommon.h>
#include <Core/Assets/Assets.h>
#include <Graphics/IRenderer.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyLoader/tiny_obj_loader.h>

#include <ft2build.h>
#include FT_FREETYPE_H

using namespace clt;

Assets* Assets::sInstance = nullptr;
FT_Library mFTLibrary;

Assets& Assets::Get()
{
    if (!sInstance)  sInstance = new Assets();
    return *sInstance;
}

Assets::Assets()
{
    if (FT_Init_FreeType(&mFTLibrary))
    {
       CLUTTER_ERROR("FREETYPE: Could not init FreeType Library");
    }
}

void Assets::LoadTextureGL(TextureFilter pTexFilter, GLuint& textureID, int& width, int& height, int& channels, unsigned char* data, bool generateMipMaps)
{

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if (generateMipMaps) glGenerateMipmap(GL_TEXTURE_2D);

    if (pTexFilter == TextureFilter::NEAREST)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, generateMipMaps ? GL_NEAREST_MIPMAP_LINEAR : GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, generateMipMaps ? GL_NEAREST_MIPMAP_LINEAR : GL_NEAREST);
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, generateMipMaps ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, generateMipMaps ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
    }

    GLenum format = channels == 4 ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

Mesh* Assets::LoadMeshFromFile(const std::string& pFile, bool pTesselate)
{   
    tinyobj::attrib_t attributes;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string errors;

    bool success = tinyobj::LoadObj(&attributes, &shapes, &materials, &errors, +pFile.c_str());

    if(success) CLUTTER_LOG(("Mesh " + pFile + " loaded sucessfully ").c_str())
    else
    {
        CLUTTER_ERROR("Failed to load Mesh. \n " + pFile + " does not exist or is not .obj");
        return nullptr;
    }

    std::vector<Vertex> vertices;

    for (int i = 0; i < shapes.size(); i++)
    {
        tinyobj::shape_t& shape = shapes[i];
        tinyobj::mesh_t& mesh = shape.mesh;
        for (int j = 0; j < mesh.indices.size(); j++)
        {
            tinyobj::index_t i = mesh.indices[j];
            Vector3 position = Vector3{
                attributes.vertices[i.vertex_index * 3],
                attributes.vertices[i.vertex_index * 3 + 1],
                attributes.vertices[i.vertex_index * 3 + 2]
            };
            Vector3 normal = Vector3{
                attributes.normals[i.normal_index * 3],
                attributes.normals[i.normal_index * 3 + 1],
                attributes.normals[i.normal_index * 3 + 2]
            };
            Vector2 texCoord = {
                attributes.texcoords[i.texcoord_index * 2],
                attributes.texcoords[i.texcoord_index * 2 + 1],
            };
            Vertex vert = { position, normal, texCoord };
            vertices.push_back(vert);
        }

    }
    return new Mesh(vertices, pTesselate);
}

Texture* Assets::LoadTexture(const std::string& path, const std::string& name, TextureFilter pTexFilter, bool generateMipMaps)
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
    
    if (mRenderer && mRenderer->GetType() == RendererType::OPENGL)
    {
        LoadTextureGL(pTexFilter, textureID, width, height, channels, data, generateMipMaps);
    }
    stbi_image_free(data);

    mTextures[name] = new Texture(textureID, width, height, channels);

    return mTextures[name];
}

std::vector<Texture*> Assets::BulkLoadTexture(const std::string& pPath, int pLastIndex, const std::string& pFileName, const std::string& pName, TextureFilter pTexFilter)
{
    std::vector<Texture*> tempAnim;

    for (int i = 0; i <= pLastIndex; i++)
    {
        std::string tempPaths = std::to_string(i) + pFileName;
        tempAnim.emplace_back(Assets::Get().LoadTexture(pPath + tempPaths, std::to_string(i) + pName, pTexFilter));
    }

    return tempAnim;
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

Mesh* Assets::GetMesh(const std::string& name, bool tesselate)
{
    std::string tempName = name;
    if (tesselate)  std::string name = name + "_tess";

    auto it = mMeshes.find(tempName);
    if (it == mMeshes.end())
    {
        CLUTTER_WARNING(("Unable to find The mesh: " + tempName).c_str());
        return nullptr;
    }
    return it->second;
}

Font* Assets::GetFont(const std::string& name)
{
    auto it = mFonts.find(name);
    if (it == mFonts.end())
    {
        CLUTTER_WARNING(("Unable to find Font: " + name).c_str());
        return nullptr;
    }
    return it->second;
}

Shader* Assets::GetShader(const std::string& pName, ShaderType pType)
{
    auto it = mShaders.find(pType);

    if (it == mShaders.end())
    {
        CLUTTER_WARNING(("Unable to find the shader type of: " + pName).c_str());
        return nullptr;
    }
    auto shader = it->second.find(pName);

    if (shader == it->second.end())
    {
        CLUTTER_WARNING(("Unable to find Shader: " + pName).c_str());
        return nullptr;
    }
    return shader->second;
}

Mesh* Assets::LoadMesh(const std::string& pPath, const std::string& pName, std::vector<Texture*> pTextures, bool pTesselate)
{
    std::string name = pName;
    if (pTesselate)  std::string name = name + "_tess";

    if (mMeshes.find(name) != mMeshes.end()) return mMeshes[name];

    Mesh* mesh = LoadMeshFromFile(pPath, pTesselate);

    if(mesh) mMeshes[name] = mesh;
    if(!mesh->GetTexture(0) && pTextures.empty()) mesh->AddTexture(GetTexture("default"));

    for (Texture* tex : pTextures)
    {
        mesh->AddTexture(tex);
    }

    return mesh;
}

Mesh* Assets::LoadMesh(const std::string& pPath, const std::string& pName, const std::string& pTexture, bool pTesselate)
{
    std::string name = pName;
    if (pTesselate) name = pName + "_tess";

    if (mMeshes.find(name) != mMeshes.end()) return GetMesh(name);

    Mesh* mesh = LoadMeshFromFile(pPath, pTesselate);

    if (mesh) mMeshes[name] = mesh;
    if (!mesh->GetTexture(0) && pTexture.empty()) mesh->AddTexture(GetTexture("default"));

        mesh->AddTexture(GetTexture(pTexture));

    return mesh;
}

Mesh* Assets::LoadMesh(const std::string& pPath, const std::string& pName, bool pTesselate)
{
    std::string name = pName;
    if(pTesselate) name = pName + "_tess";

    if (mMeshes.find(name) != mMeshes.end()) return mMeshes[name];

    Mesh* mesh = LoadMeshFromFile(pPath, pTesselate);

    if (mesh) mMeshes[name] = mesh;
    if (!mesh->GetTexture(0)) mesh->AddTexture(GetTexture("default"));

    return mesh;
}

Font* Assets::LoadFont(const std::string& pPath, const std::string& pName, GLuint pFontSize)
{
    if (mFonts.find(pName) != mFonts.end()) return mFonts[pName];

    FT_Face face;
    if (FT_New_Face(mFTLibrary, pPath.c_str(), 0, &face))
    {
        CLUTTER_ERROR("FREETYPE: Failed to load font:" + pPath);
    }

    FT_Set_Pixel_Sizes(face, 0, pFontSize);

    glPixelStoref(GL_UNPACK_ALIGNMENT, 1);

    Font* font = new Font();

    for (unsigned char c = 0; c < 128; c++)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            CLUTTER_WARNING("FREETYTPE: Failed to load Glyph n"+ c);
            continue;
        }
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = 
        {
            texture,
            Vector2{ face->glyph->bitmap.width, face->glyph->bitmap.rows },
            Vector2{ face->glyph->bitmap_left, face->glyph->bitmap_top},
            static_cast<unsigned int>(face->glyph->advance.x)
        };

        font->mCharacters.insert(std::pair<GLchar, Character>(c, character));
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    FT_Done_Face(face);
    CLUTTER_LOG(("Font " + pPath + " loaded sucessfully ").c_str());

    mFonts[pName] = font;

    return font;
}

Shader* Assets::LoadShader(const std::string& pPath, const std::string& pName, ShaderType pType)
{
    if (mShaders[pType][pName]) return GetShader(pName, pType);
    Shader* temp = new Shader();
    temp->Load(pPath, pType);

    mShaders[pType][pName] = temp;
    return temp;
}

std::vector<Texture*> Assets::BulkGetTexture(const std::string& pName, int pLastIndex)
{
    std::vector<Texture*> tempAnim;

    for (int i = 0; i <= pLastIndex; i++)
    {
        std::string name = std::to_string(i) + pName;
        tempAnim.push_back(GetTexture(name));
    }

    return tempAnim;
}

void Assets::ClearAssets()
{
    for (auto& pair : mTextures)
    {
        delete pair.second;
    }
    mTextures.clear();

    for (auto& pair : mMeshes)
    {
        delete pair.second;
    }
    mMeshes.clear();

    FT_Done_FreeType(mFTLibrary);

    delete sInstance;
}
