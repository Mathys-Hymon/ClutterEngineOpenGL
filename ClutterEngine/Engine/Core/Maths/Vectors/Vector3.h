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

	inline Vector2 xz()
	{
		return { x, z };
	}

	inline Vector2 yz()
	{
		return { y, z };
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


    /**
     * @brief Clamps the vector components to the given range.
     * @param vec The vector to clamp.
     * @param minValue The minimum value.
     * @param maxValue The maximum value.
     * @return The clamped vector.
     */
    static Vector3 Clamp(const Vector3& vec, float minValue, float maxValue)
    {
        Vector3 result = vec;
        if (result.x < minValue) result.x = minValue;
        if (result.x > maxValue) result.x = maxValue;

        if (result.y < minValue) result.y = minValue;
        if (result.y > maxValue) result.y = maxValue;

        if (result.z < minValue) result.z = minValue;
        if (result.z > maxValue) result.z = maxValue;

        return result;
    }
};
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
    /**
     * @brief The X component of the vector.
     */
    float x = 0;
    /**
     * @brief The Y component of the vector.
     */
    float y = 0;
    /**
     * @brief The Z component of the vector.
     */
    float z = 0;

    /**
     * @brief A vector with all components set to zero.
     */
    static const Vector3 Zero;
    /**
     * @brief A vector with all components set to one.
     */
    static const Vector3 One;
    /**
     * @brief A unit vector pointing up (0, 1, 0).
     */
    static const Vector3 Up;
    /**
     * @brief A unit vector pointing down (0, -1, 0).
     */
    static const Vector3 Down;
    /**
     * @brief A unit vector pointing left (-1, 0, 0).
     */
    static const Vector3 Left;
    /**
     * @brief A unit vector pointing right (1, 0, 0).
     */
    static const Vector3 Right;
    /**
     * @brief A unit vector pointing forward (0, 0, 1).
     */
    static const Vector3 Forward;
    /**
     * @brief A unit vector pointing backward (0, 0, -1).
     */
    static const Vector3 Backward;
    /**
     * @brief A vector with all components set to positive infinity.
     */
    static const Vector3 Infinity;
    /**
     * @brief A vector with all components set to negative infinity.
     */
    static const Vector3 NegInfinity;

    /**
     * @brief Default constructor. Initializes all components to zero.
     */
    Vector3();

    /**
     * @brief Constructs a vector with all components set to the same value.
     * @param pXYZ The value to set for x, y, and z.
     */
    Vector3(float pXYZ);

    /**
     * @brief Constructs a vector from a Vector2, z is set to 0.
     * @param pXY The Vector2 to use for x and y.
     */
    Vector3(Vector2 pXY);

    /**
     * @brief Constructs a vector with specified x, y, and z values.
     * @param xP The x component.
     * @param yP The y component.
     * @param zP The z component.
     */
    Vector3(float xP, float yP, float zP);

    /**
     * @brief Sets the vector components.
     * @param xP The x component.
     * @param yP The y component.
     * @param zP The z component.
     */
    void Set(float xP, float yP, float zP);

    /**
     * @brief Returns the squared length of the vector.
     * @return The squared length.
     */
    float LengthSq() const;

    /**
     * @brief Returns the length (magnitude) of the vector.
     * @return The length.
     */
    float Length() const;

    /**
     * @brief Normalizes the vector in place.
     */
    void Normalize();

    /**
     * @brief Returns a pointer to the vector's data as a float array.
     * @return Pointer to the float array.
     */
    const float* GetAsFloatPtr() const
    {
        return reinterpret_cast<const float*>(&x);
    }

    /**
     * @brief Accesses a component by index.
     * @param index The index (0=x, 1=y, 2=z).
     * @return Reference to the component.
     * @throws std::out_of_range if index is not 0, 1, or 2.
     */
    inline float& operator[](int index)
    {
        if (index == 0) return x;
        if (index == 1) return y;
        if (index == 2) return z;
        throw std::out_of_range("Index out of range for Vector3");
    }

    /**
     * @brief Accesses a component by index (const).
     * @param index The index (0=x, 1=y, 2=z).
     * @return Const reference to the component.
     * @throws std::out_of_range if index is not 0, 1, or 2.
     */
    inline const float& operator[](int index) const
    {
        if (index == 0) return x;
        if (index == 1) return y;
        if (index == 2) return z;
        throw std::out_of_range("Index out of range for Vector3");
    }

    /**
     * @brief Adds two vectors.
     * @param a The first vector.
     * @param b The second vector.
     * @return The sum of the vectors.
     */
    friend Vector3 operator+(const Vector3& a, const Vector3& b)
    {
        return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
    }

    /**
     * @brief Divides a vector by a scalar.
     * @param vec The vector.
     * @param scalar The scalar value.
     * @return The scaled vector.
     */
    friend Vector3 operator/(const Vector3& vec, float scalar)
    {
        return Vector3(vec.x / scalar, vec.y / scalar, vec.z / scalar);
    }

    /**
     * @brief Divides two vectors component-wise.
     * @param a The numerator vector.
     * @param b The denominator vector.
     * @return The component-wise division result.
     */
    friend Vector3 operator/(const Vector3& a, const Vector3& b)
    {
        return Vector3(a.x / b.x, a.y / b.y, a.z / b.z);
    }

    /**
     * @brief Divides the vector by a scalar in place.
     * @param scalar The scalar value.
     * @return Reference to this vector.
     */
    Vector3& operator/=(float scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    /**
     * @brief Subtracts two vectors.
     * @param a The first vector.
     * @param b The second vector.
     * @return The difference of the vectors.
     */
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

    /**
     * @brief Multiplies two vectors component-wise.
     * @param left The first vector.
     * @param right The second vector.
     * @return The component-wise product.
     */
    friend Vector3 operator*(const Vector3& left, const Vector3& right)
    {
        return Vector3(left.x * right.x, left.y * right.y, left.z * right.z);
    }

    /**
     * @brief Multiplies a vector by a scalar.
     * @param vec The vector.
     * @param scalar The scalar value.
     * @return The scaled vector.
     */
    friend Vector3 operator*(const Vector3& vec, float scalar)
    {
        return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
    }

    /**
     * @brief Multiplies a scalar by a vector.
     * @param scalar The scalar value.
     * @param vec The vector.
     * @return The scaled vector.
     */
    friend Vector3 operator*(float scalar, const Vector3& vec)
    {
        return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
    }

    /**
     * @brief Multiplies the vector by a scalar in place.
     * @param scalar The scalar value.
     * @return Reference to this vector.
     */
    Vector3& operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    /**
     * @brief Adds another vector to this vector in place.
     * @param right The vector to add.
     * @return Reference to this vector.
     */
    Vector3& operator+=(const Vector3& right)
    {
        x += right.x;
        y += right.y;
        z += right.z;
        return *this;
    }

    /**
     * @brief Subtracts another vector from this vector in place.
     * @param right The vector to subtract.
     * @return Reference to this vector.
     */
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

    /**
     * @brief Returns a normalized copy of the provided vector.
     * @param vec The vector to normalize.
     * @return The normalized vector.
     */
    static Vector3 Normalize(const Vector3& vec)
    {
        Vector3 temp = vec;
        temp.Normalize();
        return temp;
    }

    /**
     * @brief Returns a normalized copy of this vector.
     * @return The normalized vector.
     */
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

    /**
     * @brief Computes the dot product of two vectors.
     * @param a The first vector.
     * @param b The second vector.
     * @return The dot product.
     */
    static float Dot(const Vector3& a, const Vector3& b)
    {
        return (a.x * b.x + a.y * b.y + a.z * b.z);
    }

    /**
     * @brief Computes the cross product of two vectors.
     * @param a The first vector.
     * @param b The second vector.
     * @return The cross product.
     */
    static Vector3 Cross(const Vector3& a, const Vector3& b)
    {
        Vector3 temp;
        temp.x = a.y * b.z - a.z * b.y;
        temp.y = a.z * b.x - a.x * b.z;
        temp.z = a.x * b.y - a.y * b.x;
        return temp;
    }

    /**
     * @brief Linearly interpolates between two vectors.
     * @param a The start vector.
     * @param b The end vector.
     * @param f The interpolation factor [0, 1].
     * @return The interpolated vector.
     */
    static Vector3 Lerp(const Vector3& a, const Vector3& b, float f)
    {
        return Vector3(a + f * (b - a));
    }

    /**
     * @brief Linearly interpolates between two vectors with speed and delta time.
     * @param current The current vector.
     * @param target The target vector.
     * @param interpSpeed The interpolation speed.
     * @param deltaTime The time step (optional).
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

    /**
     * @brief Reflects a vector about a normal.
     * @param v The incident vector.
     * @param n The normal vector (should be normalized).
     * @return The reflected vector.
     */
    static Vector3 Reflect(const Vector3& v, const Vector3& n)
    {
        return v - 2.0f * Vector3::Dot(v, n) * n;
    }

    /**
     * @brief Transforms a vector by a 4x4 matrix.
     * @param vec The vector to transform.
     * @param mat The transformation matrix.
     * @param w The w component (default 1.0f).
     * @return The transformed vector.
     */
    static Vector3 Transform(Vector3& vec, class Matrix4& mat, float w = 1.0f);

    /**
     * @brief Transforms a vector by a 4x4 matrix and performs perspective division.
     * @param vec The vector to transform.
     * @param mat The transformation matrix.
     * @param w The w component (default 1.0f).
     * @return The transformed vector.
     */
    static Vector3 TransformWithPerspDiv(Vector3& vec, class Matrix4& mat, float w = 1.0f);

    /**
     * @brief Transforms a vector by a quaternion.
     * @param v The vector to transform.
     * @param q The quaternion.
     * @return The transformed vector.
     */
    static Vector3 Transform(const Vector3& v, const class Quaternion& q);

    /**
     * @brief Returns a string representation of the vector.
     * @return The string representation.
     */
    inline std::string ToString()
    {
        return " (" + std::to_string(x) + " , " + std::to_string(y) + " , " + std::to_string(z) + ") ";
    }

    /**
     * @brief Returns the (x, y) components as a Vector2.
     * @return The Vector2 (x, y).
     */
    inline Vector2 xy()
    {
        return {x, y};
    }

    /**
     * @brief Returns the (x, z) components as a Vector2.
     * @return The Vector2 (x, z).
     */
    inline Vector2 xz()
    {
        return { x, z };
    }

    /**
     * @brief Returns the (y, z) components as a Vector2.
     * @return The Vector2 (y, z).
     */
    inline Vector2 yz()
    {
        return { y, z };
    }

    /**
     * @brief Clamps the vector components to the given range in place.
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

    /**
     * @brief Clamps the vector components to the given range.
     * @param vec The vector to clamp.
     * @param minValue The minimum value.
     * @param maxValue The maximum value.
     * @return The clamped vector.
     */
    static Vector3 Clamp(const Vector3& vec, float minValue, float maxValue)
    {
        Vector3 result = vec;
        if (result.x < minValue) result.x = minValue;
        if (result.x > maxValue) result.x = maxValue;

        if (result.y < minValue) result.y = minValue;
        if (result.y > maxValue) result.y = maxValue;

        if (result.z < minValue) result.z = minValue;
        if (result.z > maxValue) result.z = maxValue;

        return result;
    }
};
