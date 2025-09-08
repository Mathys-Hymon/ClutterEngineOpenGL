#pragma once
#include <Core/CCommon.h>
#ifndef SOUNDS_H
#define SOUNDS_H
#include <FMOD/Studio/fmod_studio.hpp>


namespace clt
{
	class Audio;
	class SoundInstance;
	class CLUTTER_API AudioManager
	{
		FMOD::Studio::System* studioSystem = nullptr;
		FMOD::System* coreSystem = nullptr;

		 AudioManager() = default;
		~AudioManager() = default;

		AudioManager(const AudioManager&) = delete;
		AudioManager& operator=(const AudioManager&) = delete;

		void Init();
		void Update();
		void Shutdown();


	public:
		static AudioManager& Get();

		void PlaySound(std::weak_ptr<Audio> audio);
		void PlaySoundAtLocation(std::weak_ptr<Audio> audio, Vector3 pos);

		std::weak_ptr<SoundInstance> SpawnSound(std::weak_ptr<Audio> audio);
		std::weak_ptr<SoundInstance> SpawnSoundAtLocation(std::weak_ptr<Audio> audio, Vector3 pos);

		FMOD::System& GetCoreSystem() const;
	};
}

#endif // SOUNDS_H