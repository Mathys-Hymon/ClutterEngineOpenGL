
#include "pch.h"
#include <Core/Timer.h>
#include <algorithm>
#include <chrono>
#include <thread> 

using namespace clt;

std::chrono::steady_clock::time_point Timer::mStartTime;
std::chrono::steady_clock::time_point Timer::mLastTime;

f32 Timer::deltaTime = 0;
f32 Timer::clampedDeltaTime = 0;

const float maxDeltaTime = 0.033f; // 33ms ~ 30 FPS

f32 Timer::ComputeDeltaTime()
{
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration<f32>(currentTime - mLastTime);

    deltaTime = elapsedTime.count();

    clampedDeltaTime = std::min(deltaTime, maxDeltaTime);

    mLastTime = currentTime;

    return deltaTime;
}

void Timer::Initialize()
{
    mStartTime = std::chrono::steady_clock::now();
}

void Timer::DelayTime(f32 seconds)
{
    std::this_thread::sleep_for(std::chrono::duration<f32>(seconds));
}

f32 Timer::GetTimeSinceLoad()
{
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<f32> elapsedTime = currentTime - mStartTime;

    return elapsedTime.count();
}
