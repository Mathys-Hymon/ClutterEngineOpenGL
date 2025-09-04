#pragma once
#include <Core/CCommon.h>
#include <Core/Assets/AssetsType/Audio.h>
#include <Core/Maths/Vectors/Vector3.h>

namespace clt
{
	class CLUTTER_API SoundInstance
	{
		FMOD::Channel* mChannel;
		AudioCategory mCategory;

	public:
		SoundInstance(FMOD::Channel* channel, AudioCategory category);

		void SetVolume(float volumeDB);
		void SetLocation(const Vector3& pos);
		void Stop();
		void Pause(bool paused);

		bool IsPlaying() const;
	};
}