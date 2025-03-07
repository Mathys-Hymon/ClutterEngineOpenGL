#pragma once
#include <Core/CCommon.h>
#include "cmath"
#include "string"

struct CLUTTER_API Color
{
	float r = 0; ///< The red component of the color.
	float g = 0; ///< The green component of the color.
	float b = 0; ///< The blue component of the color.
	float a = 0; ///< The alpha component of the color.

	static const Color black; ///< A color with all components set to zero.
	static const Color white; ///< A color with all components set to one.
	static const Color red;   ///< A color with the red component set to one.
	static const Color green; ///< A color with the green component set to one.
	static const Color blue;  ///< A color with the blue component set to one.
	static const Color yellow;///< A color with the red and green components set to one.
	static const Color cyan;  ///< A color with the green and blue components set to one.
	static const Color magenta;///< A color with the red and blue components set to one.
	static const Color orange;///< A color with the red and green components set to one and the blue component set to zero.
	static const Color purple;///< A color with the red and blue components set to one and the green component set to zero.
	static const Color pink;  ///< A color with the red and blue components set to one and the green component set to zero.
	static const Color brown;///< A color with the red and green components set to one and the blue component set to zero.
	static const Color grey; ///< A color with all components set to 0.5.
	static const Color dark_grey;///< A color with all components set to 0.25.
	static const Color light_grey;///< A color with all components set to 0.75.
	static const Color teal; ///< A color with the green and blue components set to 0.5 and the red component set to zero.
	static const Color lime; ///< A color with the red and green components set to 0.5 and the blue component set to zero.
	static const Color maroon;///< A color with the red component set to 0.5 and the green and blue components set to zero.
	static const Color navy; ///< A color with the blue component set to 0.5 and the red and green components set to zero.
	static const Color olive;///< A color with the red and green components set to 0.5 and the blue component set to zero.
	static const Color silver;///< A color with all components set to 0.75.
	static const Color gold; ///< A color with the red component set to 1 and the green and blue components set to 0.85.



	Color() : r(0), g(0), b(0), a(0) {}
	Color(float pR, float pG, float pB, float pA = 0) : r(pR), g(pG), b(pB), a(pA) {}

	inline void operator+=(Color right) // Adds the right color to the left color.
	{
		r += right.r;
		g += right.g;
		b += right.b;
		a += right.a;

		(*this).clamp(0, 255);
	}

	inline void operator-=(Color right) // Subtracts the right color from the left color.
	{
		r -= right.r;
		g -= right.g;
		b -= right.b;
		a -= right.a;

		(*this).clamp(0, 255);
	}

	inline void operator*=(Color right) // Multiplies the left color by the right color.
	{
		r *= right.r;
		g *= right.g;
		b *= right.b;
		a *= right.a;

		(*this).clamp(0, 255);
	}

	inline void operator/=(Color right) // Divides the left color by the right color.
	{
		r /= right.r;
		g /= right.g;
		b /= right.b;
		a /= right.a;

		(*this).clamp(0, 255);
	}

	inline void operator=(Color right) // Assigns the right color to the left color.
	{
		r = right.r;
		g = right.g;
		b = right.b;
		a = right.a;

		(*this).clamp(0, 255);
	}

	inline void clamp(float minValue, float maxValue) // Clamps the color values between the min and max values.
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

	inline std::string ToString() // Returns a string representation of the color.
	{
		return " R : " + std::to_string(r) + " , G : " + std::to_string(g) + " , B : " + std::to_string(b) + " , A : " + std::to_string(a) + ") ";
	}
};