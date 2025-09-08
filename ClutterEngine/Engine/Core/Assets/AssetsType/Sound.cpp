#include "pch.h"
#include "Sound.h"
#include <Sound/Audio.h>

using namespace clt;

Sound::Sound(AudioCategory category, FMOD::Sound* sound, bool isSpatialized, bool isStream) :
	mSpatialized(isSpatialized), mStream(isStream), mCategory(category), mSound(sound)
{}

Sound::~Sound()
{
	mSound = nullptr;
}
