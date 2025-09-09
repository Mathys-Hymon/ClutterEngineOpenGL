#pragma once
#include <Core/CCommon.h>
#ifndef SOUNDS_H
#define SOUNDS_H
#include <FMOD/Studio/fmod_studio.hpp>
#include <Core/Assets/AssetsType/Sound.h>

namespace clt
{
	class Sound;
	class SoundInstance;
	class CLUTTER_API Audio
	{
		static Audio* sInstance;
		FMOD::Studio::System* mStudioSystem = nullptr;
		FMOD::System* mCoreSystem = nullptr;

		std::map<AudioCategory, FMOD::ChannelGroup*> mCategoryGroups;

		std::vector<std::shared_ptr<SoundInstance>> mActiveSounds;

		void Init();
		void Shutdown();

		Audio() { Init(); };
		~Audio() = default;

		SoundInstance& SpawnSoundComponent(std::weak_ptr<Sound> sound, Vector3 pos);
		SoundInstance& SpawnSoundComponent(const std::string& soundName, Vector3 pos);

	public:

		Audio(const Audio&) = delete;
		Audio& operator=(const Audio&) = delete;

		static Audio& Get();

		void Update();

		void PlaySound(std::weak_ptr<Sound> audio);
		void PlaySoundAtLocation(std::weak_ptr<Sound> audio, Vector3 pos);

		void PlaySound(const std::string& soundName);
		void PlaySoundAtLocation(const std::string& soundName, Vector3 pos);

		void SetAttenuationSettings(float distanceFactor, float rolloffDistance, float dopplerScale = 1.0f);

		SoundInstance& SpawnSound(std::weak_ptr<Sound> sound);
		SoundInstance& SpawnSoundAtLocation(std::weak_ptr<Sound> sound, Vector3 pos);

		SoundInstance& SpawnSound(const std::string& soundName);
		SoundInstance& SpawnSoundAtLocation(const std::string& soundName, Vector3 pos);

		void ClearSpawnedSounds();
		void ClearAllSounds();
		void ClearByCategory(AudioCategory category);

		FMOD::System& GetCoreSystem() const;

		friend class CEngine;
		friend class SoundComponent;
	};
}

#endif // SOUNDS_H