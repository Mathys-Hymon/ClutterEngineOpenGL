#pragma once

#include <limits>
#include <cmath>
#include "Core/Timer.h"
#include <random>

namespace Maths
{
    const float PI = 3.1415926535f;
    const float TWO_PI = PI * 2.0f;
    const float PI_OVER2 = PI * 0.5f;
    const float INFINITY_POS = std::numeric_limits<float>::infinity();
    const float INFINITY_NEG = -INFINITY_POS;

    inline float ToRad(float degrees) { return degrees * PI / 180.0f; }
    inline float ToDeg(float radians) { return radians * 180.0f / PI; }

    inline bool NearZero(float val, float epsilon = 0.001f) { return fabs(val) <= epsilon; }

    template<typename T>
    T Max(const T& a, const T& b) { return a < b ? b : a; }
    template<typename T>
    T Min(const T& a, const T& b) { return a < b ? a : b; }
    template<typename T>
    T Clamp(const T& val, const T& lower, const T& upper) { return Min(upper, Max(val, lower)); }
    inline float Abs(float val) { return fabs(val); }
    inline float Cos(float angle) { return cosf(angle); }
    inline float Sin(float angle) { return sinf(angle); }
    inline float Tan(float angle) { return tanf(angle); }
    inline float ACos(float angle) { return acosf(angle); }
    inline float ATan2(float opposite, float adjacent) { return atan2f(opposite, adjacent); }
    inline float Cot(float angle) { return 1.0f / Tan(angle); }
    inline float Lerp(float a, float b, float t) { return a + t * (b - a); }
    inline float Finterp(float a, float b, float duration) { return a + (b - a) * Clamp(clt::Timer::deltaTime / Max(duration, 0.0001f), 0.0f, 1.0f); }
    inline float Sqrt(float val) { return sqrtf(val); }
    inline float Fmod(float numer, float denom) { return std::fmod(numer, denom); }
    inline int Round(float val) { return static_cast<int>(val); }

    // ---------------------------
   // RANDOM UTILS
   // ---------------------------
    inline std::mt19937& GetRNG()
    {
        static thread_local std::mt19937 rng{ std::random_device{}() };
        return rng;
    }

    // int
    inline int Rand(int min, int max)
    {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(GetRNG());
    }

    // float
    inline float Rand(float min, float max)
    {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(GetRNG());
    }
}