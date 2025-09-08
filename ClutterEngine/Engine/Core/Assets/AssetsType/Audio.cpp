#include "pch.h"
#include "Audio.h"
#include <Sound/AudioManager.h>

using namespace clt;

Audio::Audio(const std::string& path, AudioCategory category, bool isSpatialized, bool isStream) :
	mSpatialized(isSpatialized), mStream(isStream), mCategory(category), mPath(path), mSound(nullptr)
{
	FMOD_MODE mode = FMOD_DEFAULT;
	mode += isSpatialized ? FMOD_3D : FMOD_2D;
	mode += isStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;

	FMOD::System& coreSystem = AudioManager::Get().GetCoreSystem();

		coreSystem.createSound(path.c_str(), mode, nullptr, &mSound);
}

Audio::~Audio()
{
	if(mSound) delete mSound;
	mSound = nullptr;
}
