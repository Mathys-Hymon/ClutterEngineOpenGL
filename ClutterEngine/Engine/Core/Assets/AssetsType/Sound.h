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
    class CLUTTER_API Sound
    {
        FMOD::Sound* mSound;
        AudioCategory mCategory;

        bool mSpatialized;
        bool mStream;

    public:
        Sound(AudioCategory category, FMOD::Sound* sound, bool isSpatialized = true, bool isStream = false);
        ~Sound();

        FMOD::Sound* GetHandle() const { return mSound; }
        AudioCategory GetCategory() const { return mCategory; }

        bool IsSpatialized() const { return mSpatialized; }
        bool IsStream() { return mStream; }
    };

    
}