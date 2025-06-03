#pragma once
#include <Core/CCommon.h>

/**
 * @brief 4D vector structure for mathematical operations.
 */
struct CLUTTER_API Vector4
{
	/// X component
	float x;
	/// Y component
	float y;
	/// Z component
	float z;
	/// W component
	float w;

	/**
  * @brief Default constructor. Initializes all components to 0.0f.
  */
	Vector4()
		:x(0.0f)
		, y(0.0f)
		, z(0.0f)
		, w(0.0f)
	{
	}

	/**
  * @brief Constructs a Vector4 with specified components.
  * @param inX X component
  * @param inY Y component
  * @param inZ Z component
  * @param inW W component
  */
	Vector4(float inX, float inY, float inZ, float inW)
		:x(inX)
		, y(inY)
		, z(inZ)
		, w(inW)
	{
	}

	/**
  * @brief Returns the squared length of the vector.
  * @return Squared length (x^2 + y^2 + z^2 + w^2)
  */
	float LengthSqr() const;

	/**
  * @brief Returns the length (magnitude) of the vector.
  * @return Length of the vector
  */
	float Length() const;

	/**
  * @brief Normalizes the vector in place.
  */
	void Normalize();

	/**
  * @brief Returns a pointer to the first component as a float array.
  * @return Pointer to the float array of components
  */
	const float* GetAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&x);
	}

	/**
  * @brief Sets all four components of the vector.
  * @param inX X component
  * @param inY Y component
  * @param inZ Z component
  * @param inW W component
  */
	void Set(float inX, float inY, float inZ, float inW)
	{
		x = inX;
		y = inY;
		z = inZ;
		w = inW;
	}

	/**
  * @brief Accesses a component by index.
  * @param i Index (0 = x, 1 = y, 2 = z, 3 = w)
  * @return Reference to the component
  */
	float& operator[](int i)
	{
		return *(reinterpret_cast<float*>(&x) + i);
	}

	/**
  * @brief Adds two vectors component-wise.
  * @param a First vector
  * @param b Second vector
  * @return Resulting vector
  */
	friend Vector4 operator+(const Vector4& a, const Vector4& b)
	{
		return Vector4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
	}

	/**
  * @brief Subtracts two vectors component-wise.
  * @param a First vector
  * @param b Second vector
  * @return Resulting vector
  */
	friend Vector4 operator-(const Vector4& a, const Vector4& b)
	{
		return Vector4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
	}

	/**
  * @brief Multiplies two vectors component-wise.
  * @param left First vector
  * @param right Second vector
  * @return Resulting vector
  */
	friend Vector4 operator*(const Vector4& left, const Vector4& right)
	{
		return Vector4(left.x * right.x, left.y * right.y, left.z * right.z, left.w * right.w);
	}

	/**
  * @brief Multiplies a vector by a scalar.
  * @param vec Vector
  * @param scalar Scalar value
  * @return Resulting vector
  */
	friend Vector4 operator*(const Vector4& vec, float scalar)
	{
		return Vector4(vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar);
	}

	/**
  * @brief Multiplies a vector by a scalar.
  * @param scalar Scalar value
  * @param vec Vector
  * @return Resulting vector
  */
	friend Vector4 operator*(float scalar, const Vector4& vec)
	{
		return Vector4(vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar);
	}

	/**
  * @brief Multiplies this vector by a scalar in place.
  * @param scalar Scalar value
  * @return Reference to this vector
  */
	Vector4& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;
		return *this;
	}

	/**
  * @brief Adds another vector to this vector in place.
  * @param right Vector to add
  * @return Reference to this vector
  */
	Vector4& operator+=(const Vector4& right)
	{
		x += right.x;
		y += right.y;
		z += right.z;
		w += right.w;
		return *this;
	}

	/**
  * @brief Subtracts another vector from this vector in place.
  * @param right Vector to subtract
  * @return Reference to this vector
  */
	Vector4& operator-=(const Vector4& right)
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;
		w -= right.w;
		return *this;
	}

	/**
  * @brief Returns a normalized copy of the given vector.
  * @param vec Vector to normalize
  * @return Normalized vector
  */
	static Vector4 Normalize(const Vector4& vec)
	{
		Vector4 temp = vec;
		temp.Normalize();
		return temp;
	}

	/**
  * @brief Computes the dot product of two vectors.
  * @param a First vector
  * @param b Second vector
  * @return Dot product
  */
	static float Dot(const Vector4& a, const Vector4& b)
	{
		return (a.x * b.x + a.y * b.y + a.z * b.z);
	}

	/**
  * @brief Computes the cross product of two vectors (ignores w component).
  * @param a First vector
  * @param b Second vector
  * @return Cross product vector
  */
	static Vector4 Cross(const Vector4& a, const Vector4& b)
	{
		Vector4 temp;
		temp.x = a.y * b.z - a.z * b.y;
		temp.y = a.z * b.x - a.x * b.z;
		temp.z = a.x * b.y - a.y * b.x;
		return temp;
	}

	/**
  * @brief Linearly interpolates between two vectors.
  * @param a Start vector
  * @param b End vector
  * @param f Interpolation factor [0, 1]
  * @return Interpolated vector
  */
	static Vector4 Lerp(const Vector4& a, const Vector4& b, float f)
	{
		return Vector4(a + f * (b - a));
	}

	/**
  * @brief Reflects a vector about a normal.
  * @param v Incident vector
  * @param n Normal vector (should be normalized)
  * @return Reflected vector
  */
	static Vector4 Reflect(const Vector4& v, const Vector4& n)
	{
		return v - 2.0f * Vector4::Dot(v, n) * n;
	}

};
