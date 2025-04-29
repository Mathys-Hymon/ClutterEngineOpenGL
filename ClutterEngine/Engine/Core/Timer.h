#pragma once
#include <Core/CCommon.h>

namespace clt
{
	class CLUTTER_API Timer
	{
	public:
		Timer() = default;
		Timer(const Timer&) = delete;
		Timer& operator=(const Timer&) = delete;

		static f32 ComputeDeltaTime();
		static void DelayTime();

		static f32 deltaTime;
		static f32 timeSinceLoad;
		static f32 clampedDeltaTime;
	};

}
