#pragma once
#include "Core/CCommon.h"
#include <Core/Debug/CLog/CLog.h>
#include <Core/Maths/Vectors/Vector2.h>
#include <algorithm>
/**
 * @brief A 3D vector structure.
 */
struct CLUTTER_API Vector3
{
	float x = 0;
	float y = 0;
	float z = 0;

	static const Vector3 Zero;
	static const Vector3 One;
	static const Vector3 Up;
	static const Vector3 Down;
	static const Vector3 Left;
	static const Vector3 Right;
	static const Vector3 Forward;
	static const Vector3 Backward;
	static const Vector3 Infinity;
	static const Vector3 NegInfinity;

	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}

	Vector3(float pXYZ) : x(pXYZ), y(pXYZ), z(pXYZ) {}

	Vector3(Vector2 pXY) : x(pXY.x), y(pXY.y), z(0) {}

	Vector3(float xP, float yP, float zP)
		:x(xP), y(yP), z(zP) {
	}

	void Set(float xP, float yP, float zP);
	float LengthSq() const;
	float Length() const;
	void Normalize();

	const float* GetAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&x);
	}

	inline float& operator[](int index)
	{
		if (index == 0) return x;
		if (index == 1) return y;
		if (index == 2) return z;
		throw std::out_of_range("Index out of range for Vector3");
	}

	inline const float& operator[](int index) const
	{
		if (index == 0) return x;
		if (index == 1) return y;
		if (index == 2) return z;
		throw std::out_of_range("Index out of range for Vector3");
	}


	// Vector addition (a + b)
	friend Vector3 operator+(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	friend Vector3 operator/(const Vector3& vec, float scalar)
	{
		return Vector3(vec.x / scalar, vec.y / scalar, vec.z / scalar);
	}

	friend Vector3 operator/(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x / b.x, a.y / b.y, a.z / b.z);
	}

	// Scalar /=  
	Vector3& operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}

	// Vector subtraction (a - b)
	friend Vector3 operator-(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	/**
 * @brief Negates the vector.
 * @return The negated vector.
 */
	inline Vector3 operator-() const
	{
		return { -x, -y, -z };
	}

	// Component-wise multiplication
	friend Vector3 operator*(const Vector3& left, const Vector3& right)
	{
		return Vector3(left.x * right.x, left.y * right.y, left.z * right.z);
	}

	// Scalar multiplication
	friend Vector3 operator*(const Vector3& vec, float scalar)
	{
		return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
	}

	// Scalar multiplication
	friend Vector3 operator*(float scalar, const Vector3& vec)
	{
		return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
	}


	// Scalar *=
	Vector3& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	// Vector +=
	Vector3& operator+=(const Vector3& right)
	{
		x += right.x;
		y += right.y;
		z += right.z;
		return *this;
	}

	// Vector -=
	Vector3& operator-=(const Vector3& right)
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;
		return *this;
	}

	/**
 * @brief Clamps the vector components to the given range.
 * @param temp The vector to clamp.
 * @param minValue The minimum value.
 * @param maxValue The maximum value.
 * @return The clamped vector.
 */
	friend Vector3 Clamp(Vector3 temp, float minValue, float maxValue)
	{
		if (temp.x < minValue)  temp.x = minValue;
		if (temp.x > maxValue)  temp.x = maxValue;

		if (temp.y < minValue)  temp.y = minValue;
		if (temp.y > maxValue)  temp.y = maxValue;

		if (temp.z < minValue)  temp.z = minValue;
		if (temp.z > maxValue)  temp.z = maxValue;

		return temp;
	}


	// Normalize the provided vector
	static Vector3 Normalize(const Vector3& vec)
	{
		Vector3 temp = vec;
		temp.Normalize();
		return temp;
	}

	inline Vector3 Normalized() const
	{
		Vector3 temp = *this;
		temp.Normalize();
		return temp;
	}

	/**
 * @brief Returns a vector with the absolute values of each component.
 * @return The vector with absolute values.
 */
	inline Vector3 Abs() const
	{
		return Vector3(std::abs(x), std::abs(y), std::abs(z));
	}

	// Dot product between two vectors (a dot b)
	static float Dot(const Vector3& a, const Vector3& b)
	{
		return (a.x * b.x + a.y * b.y + a.z * b.z);
	}

	// Cross product between two vectors (a cross b)
	static Vector3 Cross(const Vector3& a, const Vector3& b)
	{
		Vector3 temp;
		temp.x = a.y * b.z - a.z * b.y;
		temp.y = a.z * b.x - a.x * b.z;
		temp.z = a.x * b.y - a.y * b.x;
		return temp;
	}

	// Lerp from A to B by f
	static Vector3 Lerp(const Vector3& a, const Vector3& b, float f)
	{
		return Vector3(a + f * (b - a));
	}

	/**
 * @brief Linearly interpolates between two vectors.
 * @param current The current vector.
 * @param target The target vector.
 * @param deltaTime The time step.
 * @param interpSpeed The interpolation speed.
 * @return The interpolated vector.
 */
	static Vector3 VInterp(const Vector3& current, const Vector3& target, float interpSpeed, float deltaTime = -1)
	{
		float dt = deltaTime;
		if (dt == -1)
		{
			dt = clt::Timer::deltaTime;
		}
		if (interpSpeed <= 0.0f)
		{
			return target;
		}
		Vector3 result = current + (target - current) * std::clamp(dt * interpSpeed, 0.0f, 1.0f);

		return result;
	}

	// Reflect V about (normalized) N
	static Vector3 Reflect(const Vector3& v, const Vector3& n)
	{
		return v - 2.0f * Vector3::Dot(v, n) * n;
	}

	static Vector3 Transform(Vector3& vec, class Matrix4& mat, float w = 1.0f);

	// This will transform the vector and renormalize the w component
	static Vector3 TransformWithPerspDiv(Vector3& vec, class Matrix4& mat, float w = 1.0f);

	// Transform a Vector3 by a quaternion
	static Vector3 Transform(const Vector3& v, const class Quaternion& q);

	inline std::string ToString()
	{
		return " (" + std::to_string(x) + " , " + std::to_string(y) + " , " + std::to_string(z) + ") ";
	}

	inline Vector2 xy()
	{
		return {x, y};
	}



	/**
 * @brief Clamps the vector components to the given range.
 * @param minValue The minimum value.
 * @param maxValue The maximum value.
 */
	inline void Clamp(float minValue, float maxValue)
	{
		if (x < minValue) x = minValue;
		if (x > maxValue) x = maxValue;

		if (y < minValue) y = minValue;
		if (y > maxValue) y = maxValue;

		if (z < minValue) z = minValue;
		if (z > maxValue) z = maxValue;
	}
};