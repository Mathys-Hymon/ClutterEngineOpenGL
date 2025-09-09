#pragma once
#include <Core/CCommon.h>
#include <Core/Assets/AssetsType/Sound.h>
#include <Core/Maths/Vectors/Vector3.h>

namespace clt
{
	class CLUTTER_API SoundInstance
	{
		FMOD::Channel* mChannel;
		AudioCategory mCategory;

		SoundInstance() = default;
	public:
		SoundInstance(FMOD::Channel* channel, AudioCategory category);

		void SetVolume(float volumeDB);
		void SetPitch(float pitch);
		void Set3DAttributes(const Vector3& pos, const Vector3& vel = {0,0,0});
		void Stop();
		void Pause() const;
		void Play() const;
		void SetPaused(bool paused) const;
		void SetLooping(bool loop) const;

		bool IsPlaying() const;

		friend class Audio;
	};
}