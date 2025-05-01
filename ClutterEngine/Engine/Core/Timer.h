#pragma once
#include <Core/CCommon.h>

namespace clt
{
	class CLUTTER_API Timer
	{
		static std::chrono::steady_clock::time_point mStartTime;
		static std::chrono::steady_clock::time_point mLastTime;

	public:
		Timer() = default;
		Timer(const Timer&) = delete;
		Timer& operator=(const Timer&) = delete;

		static void Initialize();
		static f32 ComputeDeltaTime();
		static void DelayTime(f32 seconds);
		static f32 GetTimeSinceLoad();

		static f32 deltaTime;
		static f32 clampedDeltaTime;
	};

}