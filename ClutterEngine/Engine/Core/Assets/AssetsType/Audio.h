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
    class AudioSystem;
    class CLUTTER_API Audio
    {
        FMOD::Sound* mSound;
        AudioCategory mCategory;
        std::string mPath;

        bool mSpatialized;
        bool mStream;

    public:
        Audio(const std::string& path, AudioCategory category, bool isSpatialized = true, bool isStream = false);
        ~Audio();

        FMOD::Sound& GetHandle() const { return *mSound; }
        AudioCategory GetCategory() const { return mCategory; }

        bool IsSpatialized() const { return mSpatialized; }
        bool IsStream() { return mStream; };

        friend class AudioManager;
    };

    
}