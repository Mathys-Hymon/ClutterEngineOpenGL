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

		std::vector<std::shared_ptr<SoundInstance>> mSpawnedSounds;

		void Init();
		void Shutdown();

		Audio() { Init(); };
		~Audio() = default;

	public:

		Audio(const Audio&) = delete;
		Audio& operator=(const Audio&) = delete;

		static Audio& Get();

		void Update();

		void PlaySound(std::weak_ptr<Sound> audio);
		void PlaySoundAtLocation(std::weak_ptr<Sound> audio, Vector3 pos);

		std::weak_ptr<SoundInstance> SpawnSound(std::weak_ptr<Sound> audio);
		std::weak_ptr<SoundInstance> SpawnSoundAtLocation(std::weak_ptr<Sound> audio, Vector3 pos);

		void ClearSpawnedSounds();
		void ClearAllSounds();

		FMOD::System& GetCoreSystem() const;

		friend class CEngine;
	};
}

#endif // SOUNDS_H