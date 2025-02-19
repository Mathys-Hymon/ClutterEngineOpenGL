#include "pch.h"
#include <Core/Timer.h>
#include <algorithm>
#include <chrono>
#include <thread> 

using namespace clt;

f32 Timer::deltaTime = 0;
static std::chrono::time_point<std::chrono::system_clock> mLastTime;

f32 Timer::ComputeDeltaTime()
{
	auto currentTime = std::chrono::system_clock::now();
	auto elapsedTime = std::chrono::duration<double>();

	if (mLastTime.time_since_epoch().count()) elapsedTime = currentTime - mLastTime;
	mLastTime = currentTime;

	deltaTime = (f32)elapsedTime.count();

	return deltaTime;
}

void Timer::DelayTime()
{

}
