#pragma once

#include <limits>
#include <cmath>
#include "Core/Timer.h"

/**
 * @namespace Maths
 * @brief Provides common mathematical constants and utility functions.
 */
namespace Maths
{
    /**
     * @brief The value of PI (π).
     */
    const float PI = 3.1415926535f;

    /**
     * @brief The value of 2 * PI (2π).
     */
    const float TWO_PI = PI * 2.0f;

    /**
     * @brief The value of PI divided by 2 (π/2).
     */
    const float PI_HALVED = PI / 2.0f;

    /**
     * @brief Positive infinity for float.
     */
    const float INFINITY_POS = std::numeric_limits<float>::infinity();

    /**
     * @brief Negative infinity for float.
     */
    const float INFINITY_NEG = -INFINITY_POS;

    /**
     * @brief Converts degrees to radians.
     * @param degrees Angle in degrees.
     * @return Angle in radians.
     */
    inline float ToRad(float degrees) { return degrees * PI / 180.0f; }

    /**
     * @brief Converts radians to degrees.
     * @param radians Angle in radians.
     * @return Angle in degrees.
     */
    inline float ToDeg(float radians) { return radians * 180.0f / PI; }

    /**
     * @brief Checks if a value is near zero within a given epsilon.
     * @param val Value to check.
     * @param epsilon Tolerance value.
     * @return True if value is near zero, false otherwise.
     */
    inline bool NearZero(float val, float epsilon = 0.001f) { return fabs(val) <= epsilon; }

    /**
     * @brief Returns the maximum of two values.
     * @tparam T Type of the values.
     * @param a First value.
     * @param b Second value.
     * @return The greater of a and b.
     */
    template<typename T>
    T Max(const T& a, const T& b) { return a < b ? b : a; }

    /**
     * @brief Returns the minimum of two values.
     * @tparam T Type of the values.
     * @param a First value.
     * @param b Second value.
     * @return The lesser of a and b.
     */
    template<typename T>
    T Min(const T& a, const T& b) { return a < b ? a : b; }

    /**
     * @brief Clamps a value between a lower and upper bound.
     * @tparam T Type of the value.
     * @param val Value to clamp.
     * @param lower Lower bound.
     * @param upper Upper bound.
     * @return Clamped value.
     */
    template<typename T>
    T Clamp(const T& val, const T& lower, const T& upper) { return Min(upper, Max(val, lower)); }

    /**
     * @brief Returns the absolute value.
     * @param val Value to get absolute of.
     * @return Absolute value.
     */
    inline float Abs(float val) { return fabs(val); }

    /**
     * @brief Returns the cosine of an angle (in radians).
     * @param angle Angle in radians.
     * @return Cosine of the angle.
     */
    inline float Cos(float angle) { return cosf(angle); }

    /**
     * @brief Returns the sine of an angle (in radians).
     * @param angle Angle in radians.
     * @return Sine of the angle.
     */
    inline float Sin(float angle) { return sinf(angle); }

    /**
     * @brief Returns the tangent of an angle (in radians).
     * @param angle Angle in radians.
     * @return Tangent of the angle.
     */
    inline float Tan(float angle) { return tanf(angle); }

    /**
     * @brief Returns the arc cosine of a value.
     * @param angle Value whose arc cosine is computed.
     * @return Arc cosine in radians.
     */
    inline float ACos(float angle) { return acosf(angle); }

    /**
     * @brief Returns the arc tangent of two variables (y, x).
     * @param opposite Opposite side value.
     * @param adjacent Adjacent side value.
     * @return Arc tangent in radians.
     */
    inline float ATan2(float opposite, float adjacent) { return atan2f(opposite, adjacent); }

    /**
     * @brief Returns the cotangent of an angle (in radians).
     * @param angle Angle in radians.
     * @return Cotangent of the angle.
     */
    inline float Cot(float angle) { return 1.0f / Tan(angle); }

    /**
     * @brief Linearly interpolates between two values.
     * @param a Start value.
     * @param b End value.
     * @param t Interpolation factor (0.0 to 1.0).
     * @return Interpolated value.
     */
    inline float Lerp(float a, float b, float t) { return a + t * (b - a); }

    /**
     * @brief Interpolates between two values over a duration using delta time.
     * @param a Start value.
     * @param b End value.
     * @param duration Duration of interpolation.
     * @return Interpolated value.
     */
    inline float Finterp(float a, float b, float duration) { return a + (b - a) * Clamp(clt::Timer::deltaTime / Max(duration, 0.0001f), 0.0f, 1.0f); }

    /**
     * @brief Returns the square root of a value.
     * @param val Value to compute square root of.
     * @return Square root.
     */
    inline float Sqrt(float val) { return sqrtf(val); }

    /**
     * @brief Returns the floating-point remainder of division.
     * @param numer Numerator.
     * @param denom Denominator.
     * @return Remainder after division.
     */
    inline float Fmod(float numer, float denom) { return std::fmod(numer, denom); }

    /**
     * @brief Rounds a floating-point value to the nearest integer.
     * @param val Value to round.
     * @return Rounded integer.
     */
    inline int Round(float val) { return static_cast<int>(val); }
}
