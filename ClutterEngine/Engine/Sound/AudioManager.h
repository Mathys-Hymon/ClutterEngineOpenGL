#pragma once
#include <Core/CCommon.h>
#ifndef SOUNDS_H
#define SOUNDS_H
#include <Core/Assets/AssetsType/Audio.h>
#include <FMOD/Studio/fmod_studio.hpp>


namespace clt
{
	class CLUTTER_API AudioManager
	{
	public:
		AudioManager() = default;
		~AudioManager();
	};
}

#endif // SOUNDS_H