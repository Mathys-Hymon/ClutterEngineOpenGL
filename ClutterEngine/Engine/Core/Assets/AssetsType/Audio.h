#pragma once
#include <Core/CCommon.h>
#include <string>
#include <FMOD/Core/fmod.hpp>

enum class CLUTTER_API AudioCategory
{
    SFX,
    Music,
    Voice,
    UI
};

namespace clt
{
    class CLUTTER_API Audio
    {
        std::unique_ptr<FMOD::Sound> mSound;
        AudioCategory mCategory;
        std::string mPath;

    public:
        Audio(const std::string& path, AudioCategory category, bool is3D = true, bool isCompressed = true);
        ~Audio();

        FMOD::Sound& GetHandle() const { return *mSound; }
        AudioCategory GetCategory() const { return mCategory; }
    };
}