#pragma once
#include <Core/CCommon.h>

namespace clt
{
	/**
  * @brief Timer utility class for measuring elapsed time and frame delta in the engine.
  */
	class CLUTTER_API Timer
	{
		/**
   * @brief The time point when the timer was initialized.
   */
		static std::chrono::steady_clock::time_point mStartTime;

		/**
   * @brief The time point of the last delta time computation.
   */
		static std::chrono::steady_clock::time_point mLastTime;

	public:
		/**
   * @brief Default constructor.
   */
		Timer() = default;

		/**
   * @brief Deleted copy constructor.
   */
		Timer(const Timer&) = delete;

		/**
   * @brief Deleted copy assignment operator.
   */
		Timer& operator=(const Timer&) = delete;

		/**
   * @brief Initializes the timer. Should be called once at application start.
   */
		static void Initialize();

		/**
   * @brief Computes the time elapsed since the last call to this function.
   * @return The delta time in seconds as a floating point value.
   */
		static f32 ComputeDeltaTime();

		/**
   * @brief Delays execution for a specified number of seconds.
   * @param seconds The amount of time to delay, in seconds.
   */
		static void DelayTime(f32 seconds);

		/**
   * @brief Gets the time in seconds since the timer was initialized.
   * @return The elapsed time in seconds as a floating point value.
   */
		static f32 GetTimeSinceLoad();

		/**
   * @brief The most recently computed delta time, in seconds.
   */
		static f32 deltaTime;

		/**
   * @brief The most recently computed delta time, clamped to a maximum value, in seconds.
   */
		static f32 clampedDeltaTime;
	};

}