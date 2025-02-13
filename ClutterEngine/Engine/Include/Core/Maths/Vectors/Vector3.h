#pragma once
#include "cmath"
#include "Vector2.h"
#include "string"
#include "../../DebugClass/Log.h"

/**
 * @brief A 3D vector structure.
 */
struct Vector3
{
    float x = 0; ///< The x-coordinate of the vector.
    float y = 0; ///< The y-coordinate of the vector.
    float z = 0; ///< The z-coordinate of the vector.

    static const Vector3 Zero; ///< A vector with all coordinates set to zero.
    static const Vector3 One;  ///< A vector with all coordinates set to one.

    /**
     * @brief Default constructor initializing the vector to (0,0,0).
     */
    Vector3() : x(0), y(0), z(0) {}

    /**
     * @brief Constructor initializing the vector to (pX, pY, pZ).
     * @param pX The x-coordinate.
     * @param pY The y-coordinate.
     * @param pZ The z-coordinate, default is 0.
     */
    Vector3(float pX, float pY, float pZ = 0) : x(pX), y(pY), z(pZ) {}

    /**
     * @brief Adds the components of another vector to this vector.
     * @param right The vector to add.
     */
    inline void operator+=(Vector3& right)
    {
        x += right.x;
        y += right.y;
        z += right.z;
    }

    /**
     * @brief Adds the components of a 2D vector to this vector.
     * @param right The 2D vector to add.
     */
    inline void operator+=(Vector2& right)
    {
        x += right.x;
        y += right.y;
    }

    /**
     * @brief Adds a scalar to all components of the vector.
     * @param length The scalar to add.
     */
    inline void operator+=(float length)
    {
        x += length;
        y += length;
        z += length;
    }

    /**
     * @brief Subtracts the components of another vector from this vector.
     * @param right The vector to subtract.
     */
    inline void operator-=(Vector3& right)
    {
        x -= right.x;
        y -= right.y;
        z -= right.z;
    }

    /**
     * @brief Subtracts the components of a 2D vector from this vector.
     * @param right The 2D vector to subtract.
     */
    inline void operator-=(Vector2& right)
    {
        x -= right.x;
        y -= right.y;
    }

    /**
     * @brief Subtracts a scalar from all components of the vector.
     * @param length The scalar to subtract.
     */
    inline void operator-=(float length)
    {
        x -= length;
        y -= length;
        z -= length;
    }

    /**
     * @brief Multiplies the components of this vector by another vector.
     * @param multiplyer The vector to multiply by.
     */
    inline void operator*=(Vector3& multiplyer)
    {
        x *= multiplyer.x;
        y *= multiplyer.y;
        z *= multiplyer.z;
    }

    /**
     * @brief Multiplies the components of this vector by a 2D vector.
     * @param multiplyer The 2D vector to multiply by.
     */
    inline void operator*=(Vector2& multiplyer)
    {
        x *= multiplyer.x;
        y *= multiplyer.y;
    }

    /**
     * @brief Multiplies all components of the vector by a scalar.
     * @param length The scalar to multiply by.
     */
    inline void operator*=(float length)
    {
        x *= length;
        y *= length;
        z *= length;
    }

    /**
     * @brief Divides the components of this vector by another vector.
     * @param divider The vector to divide by.
     */
    inline void operator/=(Vector3& divider)
    {
        x /= divider.x;
        y /= divider.y;
        z /= divider.z;
    }

    /**
     * @brief Divides the components of this vector by a 2D vector.
     * @param divider The 2D vector to divide by.
     */
    inline void operator/=(Vector2& divider)
    {
        x /= divider.x;
        y /= divider.y;
    }

    /**
     * @brief Divides all components of the vector by a scalar.
     * @param length The scalar to divide by.
     */
    inline void operator/=(float length)
    {
        x /= length;
        y /= length;
        z /= length;
    }

    /**
     * @brief Assigns a scalar value to all components of the vector.
     * @param scalar The scalar to assign.
     */
    inline void operator=(float scalar)
    {
        x = scalar;
        y = scalar;
        z = scalar;
    }

    // Subtraction

    /**
     * @brief Subtracts two vectors.
     * @param left The left vector.
     * @param right The right vector.
     * @return The result of the subtraction.
     */
    friend Vector3 operator-(Vector3& left, Vector3 right)
    {
        return { left.x - right.x, left.y - right.y, left.z - right.z };
    }

    /**
     * @brief Subtracts two vectors.
     * @param left The left vector.
     * @param right The right vector.
     * @return The result of the subtraction.
     */
    friend Vector3 operator-(Vector3 left, Vector3& right)
    {
        return { left.x - right.x, left.y - right.y, left.z - right.z };
    }

    /**
     * @brief Subtracts two vectors.
     * @param left The left vector.
     * @param right The right vector.
     * @return The result of the subtraction.
     */
    friend Vector3 operator-(Vector3& left, Vector3& right)
    {
        return { left.x - right.x, left.y - right.y, left.z - right.z };
    }

    // Vector 3 with Vector 2

    /**
     * @brief Subtracts a 2D vector from a 3D vector.
     * @param left The left vector.
     * @param right The right 2D vector.
     * @return The result of the subtraction.
     */
    friend Vector3 operator-(Vector3& left, Vector2 right)
    {
        return { left.x - right.x, left.y - right.y, left.z };
    }

    /**
     * @brief Subtracts a 3D vector from a 2D vector.
     * @param left The left 2D vector.
     * @param right The right 3D vector.
     * @return The result of the subtraction.
     */
    friend Vector3 operator-(Vector2 left, Vector3& right)
    {
        return { left.x - right.x, left.y - right.y, right.z };
    }

    /**
     * @brief Subtracts a 2D vector from a 3D vector.
     * @param left The left vector.
     * @param right The right 2D vector.
     * @return The result of the subtraction.
     */
    friend Vector3 operator-(Vector3& left, Vector2& right)
    {
        return { left.x - right.x, left.y - right.y, left.z };
    }

    /**
     * @brief Subtracts a 3D vector from a 2D vector.
     * @param left The left 2D vector.
     * @param right The right 3D vector.
     * @return The result of the subtraction.
     */
    friend Vector3 operator-(Vector2& left, Vector3& right)
    {
        return { left.x - right.x, left.y - right.y, right.z };
    }

    /**
     * @brief Subtracts a scalar from a 3D vector.
     * @param left The vector.
     * @param right The scalar.
     * @return The result of the subtraction.
     */
    friend Vector3 operator-(Vector3& left, float right)
    {
        return { left.x - right, left.y - right, left.z - right };
    }

    // Addition

    // Vector 3 with Vector 3

    /**
     * @brief Adds two vectors.
     * @param left The left vector.
     * @param right The right vector.
     * @return The result of the addition.
     */
    friend Vector3 operator+(Vector3& left, Vector3 right)
    {
        return { left.x + right.x, left.y + right.y, left.z + right.z };
    }

    /**
     * @brief Adds two vectors.
     * @param left The left vector.
     * @param right The right vector.
     * @return The result of the addition.
     */
    friend Vector3 operator+(Vector3 left, Vector3& right)
    {
        return { left.x + right.x, left.y + right.y, left.z + right.z };
    }

    /**
     * @brief Adds two vectors.
     * @param left The left vector.
     * @param right The right vector.
     * @return The result of the addition.
     */
    friend Vector3 operator+(Vector3& left, Vector3& right)
    {
        return { left.x + right.x, left.y + right.y, left.z + right.z };
    }

    // Vector 3 with Vector 2

    /**
     * @brief Adds a 2D vector to a 3D vector.
     * @param left The left vector.
     * @param right The right 2D vector.
     * @return The result of the addition.
     */
    friend Vector3 operator+(Vector3& left, Vector2 right)
    {
        return { left.x + right.x, left.y + right.y, left.z };
    }

    /**
     * @brief Adds a 3D vector to a 2D vector.
     * @param left The left 2D vector.
     * @param right The right 3D vector.
     * @return The result of the addition.
     */
    friend Vector3 operator+(Vector2 left, Vector3& right)
    {
        return { left.x + right.x, left.y + right.y, right.z };
    }

    /**
     * @brief Adds a 2D vector to a 3D vector.
     * @param left The left vector.
     * @param right The right 2D vector.
     * @return The result of the addition.
     */
    friend Vector3 operator+(Vector2& left, Vector3& right)
    {
        return { left.x + right.x, left.y + right.y, right.z };
    }

    /**
     * @brief Adds a 3D vector to a 2D vector.
     * @param left The left vector.
     * @param right The right 2D vector.
     * @return The result of the addition.
     */
    friend Vector3 operator+(Vector3& left, Vector2& right)
    {
        return { left.x + right.x, left.y + right.y, left.z };
    }

    /**
     * @brief Adds a scalar to a 3D vector.
     * @param left The vector.
     * @param right The scalar.
     * @return The result of the addition.
     */
    friend Vector3 operator+(Vector3& left, float right)
    {
        return { left.x + right, left.y + right, left.z + right };
    }

    // Multiplication

    // Vector 3 with Vector 3

    /**
     * @brief Multiplies a vector by a scalar.
     * @param scalar The scalar.
     * @param right The vector.
     * @return The result of the multiplication.
     */
    friend Vector3 operator*(float scalar, Vector3& right)
    {
        return { scalar * right.x, scalar * right.y, scalar * right.z };
    }

    /**
     * @brief Multiplies a vector by a scalar.
     * @param left The vector.
     * @param scalar The scalar.
     * @return The result of the multiplication.
     */
    friend Vector3 operator*(Vector3& left, float scalar)
    {
        return { left.x * scalar, left.y * scalar, left.z * scalar };
    }

    /**
     * @brief Multiplies two vectors.
     * @param left The left vector.
     * @param right The right vector.
     * @return The result of the multiplication.
     */
    friend Vector3 operator*(Vector3& left, Vector3& right)
    {
        return { left.x * right.x, left.y * right.y, left.z * right.z };
    }

    // Vector 3 with Vector 2

    /**
     * @brief Multiplies a 3D vector by a 2D vector.
     * @param left The left vector.
     * @param right The right 2D vector.
     * @return The result of the multiplication.
     */
    friend Vector3 operator*(Vector3& left, Vector2& right)
    {
        return { left.x * right.x, left.y * right.y, left.z };
    }

    /**
     * @brief Multiplies a 2D vector by a 3D vector.
     * @param left The left 2D vector.
     * @param right The right 3D vector.
     * @return The result of the multiplication.
     */
    friend Vector3 operator*(Vector2& left, Vector3& right)
    {
        return { left.x * right.x, left.y * right.y, right.z };
    }

    // Division

    // Vector 3 with Vector 3

    /**
     * @brief Divides a scalar by a vector.
     * @param scalar The scalar.
     * @param right The vector.
     * @return The result of the division.
     */
    friend Vector3 operator/(float scalar, Vector3& right)
    {
        return { right.x / scalar, right.y / scalar, right.z / scalar };
    }

    /**
     * @brief Divides a vector by a scalar.
     * @param left The vector.
     * @param scalar The scalar.
     * @return The result of the division.
     */
    friend Vector3 operator/(Vector3& left, float scalar)
    {
        return { left.x / scalar, left.y / scalar, left.z / scalar };
    }

    /**
     * @brief Divides two vectors.
     * @param left The left vector.
     * @param right The right vector.
     * @return The result of the division.
     */
    friend Vector3 operator/(Vector3& left, Vector3& right)
    {
        return { left.x / right.x, left.y / right.y, left.z / right.z };
    }

    // Vector 3 with Vector 2

    /**
     * @brief Divides a 3D vector by a 2D vector.
     * @param left The left vector.
     * @param right The right 2D vector.
     * @return The result of the division.
     */
    friend Vector3 operator/(Vector3& left, Vector2& right)
    {
        return { left.x / right.x, left.y / right.y, left.z };
    }

    /**
     * @brief Divides a 2D vector by a 3D vector.
     * @param left The left 2D vector.
     * @param right The right 3D vector.
     * @return The result of the division.
     */
    friend Vector3 operator/(Vector2& left, Vector3& right)
    {
        return { left.x / right.x, left.y / right.y, right.z };
    }

    // Equality

    /**
     * @brief Checks if two vectors are equal.
     * @param left The left vector.
     * @param right The right vector.
     * @return True if the vectors are equal, false otherwise.
     */
    friend bool operator==(Vector3& left, Vector3& right)
    {
        return left.x == right.x && left.y == right.y && left.z == right.z;
    }

    /**
     * @brief Checks if a vector is equal to a scalar.
     * @param left The vector.
     * @param right The scalar.
     * @return True if the vector is equal to the scalar, false otherwise.
     */
    friend bool operator==(Vector3& left, float right)
    {
        return left.x == right && left.y == right && left.z == right;
    }

    /**
     * @brief Checks if two vectors are not equal.
     * @param left The left vector.
     * @param right The right vector.
     * @return True if the vectors are not equal, false otherwise.
     */
    friend bool operator!=(Vector3& left, Vector3& right)
    {
        return !(left == right);
    }

    /**
     * @brief Checks if a vector is not equal to a scalar.
     * @param left The vector.
     * @param right The scalar.
     * @return True if the vector is not equal to the scalar, false otherwise.
     */
    friend bool operator!=(Vector3& left, float right)
    {
        return !(left == right);
    }

    /**
     * @brief Calculates the length of the vector.
     * @return The length of the vector.
     */
    inline float Length() const
    {
        return sqrt(x * x + y * y + z * z);
    }

    /**
     * @brief Checks if two vectors are equal within an acceptance range.
     * @param right The vector to compare to.
     * @param acceptance The acceptance range.
     * @return True if the vectors are equal within the acceptance range, false otherwise.
     */
    inline bool Equal(Vector3 right, double acceptance) const
    {
        return (x >= right.x - acceptance && x <= right.x + acceptance &&
            y >= right.y - acceptance && y <= right.y + acceptance &&
            z >= right.z - acceptance && z <= right.z + acceptance);
    }

    /**
     * @brief Normalizes the vector to a unit vector.
     */
    inline void Normalize()
    {
        (*this) /= Length();
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
         * @brief Clamps the components of the vector to specified minimum and maximum values.
         * @param temp The vector to clamp.
         * @param minValue The minimum value to clamp to.
         * @param maxValue The maximum value to clamp to.
         * @return A clamped vector.
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
     * @brief Calculates the cross product of this vector and another vector.
     * @param right The vector to calculate the cross product with.
     * @return The cross product vector.
     */
    inline Vector3 Cross(Vector3 right) const
    {
        Vector3 temp;
        temp.x = y * right.z - z * right.y;
        temp.y = z * right.x - x * right.z;
        temp.z = x * right.y - y * right.x;

        return temp;
    }

    /**
     * @brief Returns a normalized version of the vector.
     * @param temp The vector to normalize.
     * @return A normalized vector.
     */
    friend Vector3 Normalized(Vector3 temp)
    {
        return temp / temp.Length();
    }

    /**
     * @brief Calculates the dot product of two vectors.
     * @param left The left vector.
     * @param right The right vector.
     * @return The dot product of the two vectors.
     */
    friend float Dot(Vector3& left, Vector3& right)
    {
        return left.x * right.x + left.y * right.y + left.z * right.z;
    }

    /**
     * @brief Converts the vector to a string representation.
     * @return A string representing the vector in the format " (x , y , z) ".
     */
    inline std::string ToString()
    {
        return " (" + std::to_string(x) + " , " + std::to_string(y) + " , " + std::to_string(z) + ") ";
    }
};