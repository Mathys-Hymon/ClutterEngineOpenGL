#pragma once
/**
 * @brief Linearly interpolates between two vectors.
 * @param current The current vector.
 * @param target The target vector.
 * @param deltaTime The time step.
 * @param interpSpeed The interpolation speed.
 * @return The interpolated vector.
 */
#include <algorithm>
#include "cmath"
#include <glm/glm.hpp>
#include "string"
#include <glad/glad.h>

/**
 * @brief A 2D vector structure.
 */
struct Vector2
{
    float x = 0; ///< The x-coordinate of the vector.
    float y = 0; ///< The y-coordinate of the vector.

    static const Vector2 Zero; ///< A vector with both coordinates set to zero.
    static const Vector2 One;  ///< A vector with both coordinates set to one.

    /**
     * @brief Default constructor initializing the vector to (0,0).
     */
    Vector2() : x(0), y(0) {}

    /**
     * @brief Constructor initializing the vector to (pX, pY).
     * @param pX The x-coordinate.
     * @param pY The y-coordinate.
     */
    Vector2(float pX, float pY) : x(pX), y(pY) {}

    Vector2(int pX, int pY) : x(pX), y(pY) {}

    Vector2(GLuint pX, GLuint pY) : x(pX), y(pY) {}

    Vector2(float pXY) : x(pXY), y(pXY) {}

    /**
     * @brief Adds the components of another vector to this vector.
     * @param right The vector to add.
     */
    inline void operator+=(Vector2 right)
    {
        x += right.x;
        y += right.y;
    }

    /**
     * @brief Adds a scalar to both components of the vector.
     * @param length The scalar to add.
     */
    inline void operator+=(float length)
    {
        x += length;
        y += length;
    }

    /**
     * @brief Subtracts the components of another vector from this vector.
     * @param right The vector to subtract.
     */
    inline void operator-=(Vector2 right)
    {
        x -= right.x;
        y -= right.y;
    }

    /**
     * @brief Subtracts a scalar from both components of the vector.
     * @param length The scalar to subtract.
     */
    inline void operator-=(float length)
    {
        x -= length;
        y -= length;
    }

    /**
     * @brief Multiplies the components of this vector by another vector.
     * @param multiplier The vector to multiply by.
     */
    inline void operator*=(Vector2 multiplyer)
    {
        x *= multiplyer.x;
        y *= multiplyer.y;
    }

    /**
     * @brief Multiplies both components of the vector by a scalar.
     * @param length The scalar to multiply by.
     */
    inline void operator*=(float length)
    {
        x *= length;
        y *= length;
    }

    /**
     * @brief Divides the components of this vector by another vector.
     * @param divider The vector to divide by.
     */
    inline void operator/=(Vector2 divider)
    {
        x /= divider.x;
        y /= divider.y;
    }

    /**
     * @brief Divides both components of the vector by a scalar.
     * @param length The scalar to divide by.
     */
    inline void operator/=(float length)
    {
        x /= length;
        y /= length;
    }

    /**
     * @brief Assigns the components of another vector to this vector.
     * @param newVec The vector to assign.
     */
    inline void operator=(Vector2 newVec)
    {
        x = newVec.x;
        y = newVec.y;
    }

    /**
 * @brief Negates the vector.
 * @return The negated vector.
 */
    inline Vector2 operator-() const
    {
        return { -x, -y };
    }

    /**
     * @brief Checks if two vectors are equal.
     * @param left The left vector.
     * @param right The right vector.
     * @return True if the vectors are equal, false otherwise.
     */
    friend bool operator==(Vector2 left, Vector2 right)
    {
        return (left.x == right.x && left.y == right.y);
    }

    /**
     * @brief Checks if two vectors are not equal.
     * @param left The left vector.
     * @param right The right vector.
     * @return True if the vectors are not equal, false otherwise.
     */
    friend bool operator!=(Vector2 left, Vector2 right)
    {
        return (left.x != right.x && left.y != right.y);
    }


    /**
     * @brief Subtracts two vectors.
     * @param left The left vector.
     * @param right The right vector.
     * @return The result of the subtraction.
     */
    friend Vector2 operator-(Vector2 left, Vector2 right)
    {
        return { left.x - right.x, left.y - right.y };
    }

    /**
     * @brief Subtracts a scalar from a vector.
     * @param left The vector.
     * @param right The scalar.
     * @return The result of the subtraction.
     */
    friend Vector2 operator-(Vector2 left, float right)
    {
        return { left.x - right, left.y - right };
    }

    /**
     * @brief Adds two vectors.
     * @param left The left vector.
     * @param right The right vector.
     * @return The result of the addition.
     */
    friend Vector2 operator+(Vector2 left, Vector2 right)
    {
        return { left.x + right.x, left.y + right.y };
    }

    /**
     * @brief Adds a scalar to a vector.
     * @param left The vector.
     * @param right The scalar.
     * @return The result of the addition.
     */
    friend Vector2 operator+(Vector2 left, float right)
    {
        return { left.x + right, left.y + right };
    }

    /**
     * @brief Multiplies a vector by a scalar.
     * @param scalar The scalar.
     * @param right The vector.
     * @return The result of the multiplication.
     */
    friend Vector2 operator*(float scalar, Vector2 right)
    {
        return { scalar * right.x, scalar * right.y };
    }

    /**
     * @brief Multiplies a vector by a scalar.
     * @param left The vector.
     * @param scalar The scalar.
     * @return The result of the multiplication.
     */
    friend Vector2 operator*(Vector2 left, float scalar)
    {
        return { left.x * scalar, left.y * scalar };
    }

    /**
     * @brief Multiplies two vectors component-wise.
     * @param left The left vector.
     * @param right The right vector.
     * @return The result of the multiplication.
     */
    friend Vector2 operator*(Vector2 left, Vector2 right)
    {
        return { left.x * right.x, left.y * right.y };
    }

    /**
     * @brief Divides a scalar by a vector.
     * @param scalar The scalar.
     * @param right The vector.
     * @return The result of the division.
     */
    friend Vector2 operator/(float scalar, Vector2 right)
    {
        return { scalar / right.x, scalar / right.y };
    }

    /**
     * @brief Divides a vector by a scalar.
     * @param left The vector.
     * @param scalar The scalar.
     * @return The result of the division.
     */
    friend Vector2 operator/(Vector2 left, float scalar)
    {
        return { left.x / scalar, left.y / scalar };
    }

    /**
     * @brief Divides two vectors component-wise.
     * @param left The left vector.
     * @param right The right vector.
     * @return The result of the division.
     */
    friend Vector2 operator/(Vector2 left, Vector2 right)
    {
        return { left.x / right.x, left.y / right.y };
    }

    /**
     * @brief Calculates the length of the vector.
     * @return The length of the vector.
     */
    inline float Length() const
    {
        return sqrt(x * x + y * y);
    }

    /**
     * @brief Checks if two vectors are equal within an acceptance range.
     * @param right The vector to compare to.
     * @param acceptance The acceptance range.
     * @return True if the vectors are equal within the acceptance range, false otherwise.
     */
    inline bool Equal(Vector2 right, double acceptance) const
    {
        if (x < right.x - acceptance || x > right.x + acceptance || y < right.y - acceptance || y > right.y + acceptance) return false;
        else return true;
    }

    /**
     * @brief Normalizes the vector to a unit vector.
     * @return The normalized vector.
     */
    inline Vector2 Normalized()
    {
        float length = Length();
        if (length == 0) return Vector2(0, 0); // Handle division by zero
        Vector2 temp = *this;
        temp /= length;
        return temp;
    }

    /**
 * @brief Calculates the squared distance between two vectors.
 * @param left The left vector.
 * @param right The right vector.
 * @return The squared distance between the two vectors.
 */
    static float DistanceSquared(const Vector2& left, const Vector2& right)
    {
        float dx = left.x - right.x;
        float dy = left.y - right.y;
        return dx * dx + dy * dy;
    }

    /**
        * @brief Linearly interpolates between two vectors.
        * @param start The start vector.
        * @param end The end vector.
        * @param t The interpolation factor (0.0 to 1.0).
        * @return The interpolated vector.
        */
    static Vector2 Lerp(const Vector2& start, const Vector2& end, float t)
    {
        return start + t * (end - start);
    }

    /**
 * @brief Calculates the squared length of the vector.
 * @return The squared length of the vector.
 */
    inline float LengthSquared() const
    {
        return x * x + y * y;
    }
    /**

    /**
 * @brief Calculates the cross product of two vectors.
 * @param other The other vector.
 * @return The cross product of the two vectors.
 */
    inline float Cross(const Vector2& other) const
    {
        return x * other.y - y * other.x;
    }

    /**
* @brief Calculates the dot product of two vectors.
* @param left The left vector.
* @param right The right vector.
* @return The dot product of the two vectors.
*/
    static float Dot(const Vector2& left, const Vector2& right)
    {
        return left.x * right.x + left.y * right.y;
    }
    /**
     * @brief Clamps the vector components to the given range.
     * @param minValue The minimum value.
     * @param maxValue The maximum value.
     */
    inline void Clamp(float minValue, float maxValue)
    {
        if ((*this).x < minValue)  (*this).x = minValue;
        if ((*this).x > maxValue) (*this).x = maxValue;

        if ((*this).y < minValue)  (*this).y = minValue;
        if ((*this).y > maxValue)  (*this).y = maxValue;
    }

    /**
     * @brief Linearly interpolates between two vectors.
     * @param current The current vector.
     * @param target The target vector.
     * @param deltaTime The time step.
     * @param interpSpeed The interpolation speed.
     * @return The interpolated vector.
     */
    static Vector2 VInterp(const Vector2& current, const Vector2& target, float deltaTime, float interpSpeed)
    {
        if (interpSpeed <= 0.0f)
        {
            return target;
        }
        Vector2 result = current + (target - current) * std::clamp(deltaTime * interpSpeed, 0.0f, 1.0f);
        return result;
    }

    /**
     * @brief Clamps the vector components to the given range.
     * @param temp The vector to clamp.
     * @param minValue The minimum value.
     * @param maxValue The maximum value.
     * @return The clamped vector.
     */
    friend Vector2 Clamp(Vector2 temp, float minValue, float maxValue)
    {
        if (temp.x < minValue)  temp.x = minValue;
        if (temp.x > maxValue)  temp.x = maxValue;

        if (temp.y < minValue)  temp.y = minValue;
        if (temp.y > maxValue)  temp.y = maxValue;

        return temp;
    }

    /**
     * @brief Converts the vector to a string representation.
     * @return A string representing the vector in the format " (x , y) ".
     */
    inline std::string ToString()
    {
        return " (" + std::to_string(x) + " , " + std::to_string(y) + ") ";
    }


    /**
     * @brief Converts the vector to a glm::vec2.
     * @return A glm::vec2 representing the vector.
     */
    inline glm::vec2 ToGlm()
    {
        return glm::vec2(x, y);
    }
};