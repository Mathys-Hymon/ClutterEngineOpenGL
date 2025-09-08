#include "pch.h"
#include "AudioManager.h"

using namespace clt;

AudioManager::~AudioManager()
{
}

FMOD::System& AudioManager::GetCoreSystem() const
{
	if (coreSystem) return *coreSystem;
	else
	{
		const_cast<AudioManager*>(this)->Init();
		return *coreSystem;
	}
}

void AudioManager::Init()
{

}