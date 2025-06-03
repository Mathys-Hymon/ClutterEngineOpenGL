#pragma once
#include <Core/CCommon.h>
#include "cmath"
#include "string"

/**
 * @brief Represents a color with red, green, blue, and alpha components.
 */
struct CLUTTER_API Color
{
	/**
  * @brief The red component of the color.
  */
	float r = 0;

	/**
  * @brief The green component of the color.
  */
	float g = 0;

	/**
  * @brief The blue component of the color.
  */
	float b = 0;

	/**
  * @brief The alpha component of the color.
  */
	float a = 0;

	/**
  * @brief A color with all components set to zero.
  */
	static const Color Black;

	/**
  * @brief A color with all components set to one.
  */
	static const Color White;

	/**
  * @brief A color with the red component set to one.
  */
	static const Color Red;

	/**
  * @brief A color with the green component set to one.
  */
	static const Color Green;

	/**
  * @brief A color with the blue component set to one.
  */
	static const Color Blue;

	/**
  * @brief A color with the red and green components set to one.
  */
	static const Color Yellow;

	/**
  * @brief A color with the green and blue components set to one.
  */
	static const Color Cyan;

	/**
  * @brief A color with the red and blue components set to one.
  */
	static const Color Magenta;

	/**
  * @brief A color with the red and green components set to one and the blue component set to zero.
  */
	static const Color Orange;

	/**
  * @brief A color with the red and blue components set to one and the green component set to zero.
  */
	static const Color Purple;

	/**
  * @brief A color with the red and blue components set to one and the green component set to zero.
  */
	static const Color Pink;

	/**
  * @brief A color with the red and green components set to one and the blue component set to zero.
  */
	static const Color Brown;

	/**
  * @brief A color with all components set to 0.5.
  */
	static const Color Grey;

	/**
  * @brief A color with all components set to 0.25.
  */
	static const Color Dark_grey;

	/**
  * @brief A color with all components set to 0.75.
  */
	static const Color Light_grey;

	/**
  * @brief A color with the green and blue components set to 0.5 and the red component set to zero.
  */
	static const Color Teal;

	/**
  * @brief A color with the red and green components set to 0.5 and the blue component set to zero.
  */
	static const Color Lime;

	/**
  * @brief A color with the red component set to 0.5 and the green and blue components set to zero.
  */
	static const Color Maroon;

	/**
  * @brief A color with the blue component set to 0.5 and the red and green components set to zero.
  */
	static const Color Navy;

	/**
  * @brief A color with the red and green components set to 0.5 and the blue component set to zero.
  */
	static const Color Olive;

	/**
  * @brief A color with all components set to 0.75.
  */
	static const Color Silver;

	/**
  * @brief A color with the red component set to 1 and the green and blue components set to 0.85.
  */
	static const Color Gold;

	/**
  * @brief Default constructor. Initializes all components to zero.
  */
	Color() : r(0), g(0), b(0), a(0) {}

	/**
  * @brief Constructs a color with the specified components.
  * @param pR Red component.
  * @param pG Green component.
  * @param pB Blue component.
  * @param pA Alpha component (default is 0).
  */
	Color(float pR, float pG, float pB, float pA = 0) : r(pR), g(pG), b(pB), a(pA) {}

	/**
  * @brief Adds the right color to the left color.
  * @param right The color to add.
  */
	inline void operator+=(Color right)
	{
		r += right.r;
		g += right.g;
		b += right.b;
		a += right.a;

		(*this).clamp(0, 255);
	}

	/**
  * @brief Subtracts the right color from the left color.
  * @param right The color to subtract.
  */
	inline void operator-=(Color right)
	{
		r -= right.r;
		g -= right.g;
		b -= right.b;
		a -= right.a;

		(*this).clamp(0, 255);
	}

	/**
  * @brief Multiplies the left color by the right color.
  * @param right The color to multiply by.
  */
	inline void operator*=(Color right)
	{
		r *= right.r;
		g *= right.g;
		b *= right.b;
		a *= right.a;

		(*this).clamp(0, 255);
	}

	/**
  * @brief Divides the left color by the right color.
  * @param right The color to divide by.
  */
	inline void operator/=(Color right)
	{
		r /= right.r;
		g /= right.g;
		b /= right.b;
		a /= right.a;

		(*this).clamp(0, 255);
	}

	/**
  * @brief Assigns the right color to the left color.
  * @param right The color to assign.
  */
	inline void operator=(Color right)
	{
		r = right.r;
		g = right.g;
		b = right.b;
		a = right.a;

		(*this).clamp(0, 255);
	}

	/**
  * @brief Clamps the color values between the min and max values.
  * @param minValue The minimum value.
  * @param maxValue The maximum value.
  */
	inline void clamp(float minValue, float maxValue)
	{
		if ((*this).r < minValue) (*this).r = minValue;
		if ((*this).r > maxValue) (*this).r = maxValue;
		if ((*this).g < minValue) (*this).g = minValue;
		if ((*this).g > maxValue) (*this).g = maxValue;
		if ((*this).b < minValue) (*this).b = minValue;
		if ((*this).b > maxValue) (*this).b = maxValue;
		if ((*this).a < minValue) (*this).a = minValue;
		if ((*this).a > maxValue) (*this).a = maxValue;
	}

	/**
  * @brief Returns the RGB components as a Vector3.
  * @return Vector3 containing the r, g, b components.
  */
	inline Vector3 rbg()
	{
		return Vector3(r, g, b);
	}

	/**
  * @brief Returns a string representation of the color.
  * @return String in the format " R : <r> , G : <g> , B : <b> , A : <a> ) "
  */
	inline std::string ToString()
	{
		return " R : " + std::to_string(r) + " , G : " + std::to_string(g) + " , B : " + std::to_string(b) + " , A : " + std::to_string(a) + ") ";
	}
};
