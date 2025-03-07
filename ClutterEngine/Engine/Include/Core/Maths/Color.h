#pragma once
#include "cmath"
#include "string"

struct Color
{
	float r = 0; ///< The red component of the color.
	float g = 0; ///< The green component of the color.
	float b = 0; ///< The blue component of the color.
	float a = 0; ///< The alpha component of the color.

	static const Color BLACK; ///< A color with all components set to zero.
	static const Color WHITE; ///< A color with all components set to one.
	static const Color RED;   ///< A color with the red component set to one.
	static const Color GREEN; ///< A color with the green component set to one.
	static const Color BLUE;  ///< A color with the blue component set to one.
	static const Color YELLOW;///< A color with the red and green components set to one.
	static const Color CYAN;  ///< A color with the green and blue components set to one.
	static const Color MAGENTA;///< A color with the red and blue components set to one.
	static const Color ORANGE;///< A color with the red and green components set to one and the blue component set to zero.
	static const Color PURPLE;///< A color with the red and blue components set to one and the green component set to zero.
	static const Color PINK;  ///< A color with the red and blue components set to one and the green component set to zero.
	static const Color BROWN;///< A color with the red and green components set to one and the blue component set to zero.
	static const Color GREY; ///< A color with all components set to 0.5.
	static const Color DARK_GREY;///< A color with all components set to 0.25.
	static const Color LIGHT_GREY;///< A color with all components set to 0.75.
	static const Color TEAL; ///< A color with the green and blue components set to 0.5 and the red component set to zero.
	static const Color LIME; ///< A color with the red and green components set to 0.5 and the blue component set to zero.
	static const Color MAROON;///< A color with the red component set to 0.5 and the green and blue components set to zero.
	static const Color NAVY; ///< A color with the blue component set to 0.5 and the red and green components set to zero.
	static const Color OLIVE;///< A color with the red and green components set to 0.5 and the blue component set to zero.
	static const Color SILVER;///< A color with all components set to 0.75.
	static const Color GOLD; ///< A color with the red component set to 1 and the green and blue components set to 0.85.



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