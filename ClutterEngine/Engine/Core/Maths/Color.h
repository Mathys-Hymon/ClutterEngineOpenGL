#pragma once
#include <Core/CCommon.h>
#include "cmath"
#include "string"
#include <Core/Maths/Vectors/Vector3.h>
#include <json/json.hpp>

struct CLUTTER_API Color
{
	float r = 0; ///< The red component of the color.
	float g = 0; ///< The green component of the color.
	float b = 0; ///< The blue component of the color.
	float a = 0; ///< The alpha component of the color.

	static const Color Black; ///< A color with all components set to zero.
	static const Color White; ///< A color with all components set to one.
	static const Color Red;   ///< A color with the red component set to one.
	static const Color Green; ///< A color with the green component set to one.
	static const Color Blue;  ///< A color with the blue component set to one.
	static const Color Yellow;///< A color with the red and green components set to one.
	static const Color Cyan;  ///< A color with the green and blue components set to one.
	static const Color Magenta;///< A color with the red and blue components set to one.
	static const Color Orange;///< A color with the red and green components set to one and the blue component set to zero.
	static const Color Purple;///< A color with the red and blue components set to one and the green component set to zero.
	static const Color Pink;  ///< A color with the red and blue components set to one and the green component set to zero.
	static const Color Brown;///< A color with the red and green components set to one and the blue component set to zero.
	static const Color Grey; ///< A color with all components set to 0.5.
	static const Color Dark_grey;///< A color with all components set to 0.25.
	static const Color Light_grey;///< A color with all components set to 0.75.
	static const Color Teal; ///< A color with the green and blue components set to 0.5 and the red component set to zero.
	static const Color Lime; ///< A color with the red and green components set to 0.5 and the blue component set to zero.
	static const Color Maroon;///< A color with the red component set to 0.5 and the green and blue components set to zero.
	static const Color Navy; ///< A color with the blue component set to 0.5 and the red and green components set to zero.
	static const Color Olive;///< A color with the red and green components set to 0.5 and the blue component set to zero.
	static const Color Silver;///< A color with all components set to 0.75.
	static const Color Gold; ///< A color with the red component set to 1 and the green and blue components set to 0.85.



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
	
	inline void to_json(nlohmann::json& j, const Color& c) 
	{
		j = nlohmann::json{{"r", c.r}, {"g", c.g}, {"b", c.b}, {"a", c.a}};
	}

	inline void from_json(const nlohmann::json& j, Color& c) 
	{
		j.at("r").get_to(c.r);
		j.at("g").get_to(c.g);
		j.at("b").get_to(c.b);
		j.at("a").get_to(c.a);
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

	inline Vector3 rbg()
	{
		return Vector3(r, g, b);
	}

	inline std::string ToString() // Returns a string representation of the color.
	{
		return " R : " + std::to_string(r) + " , G : " + std::to_string(g) + " , B : " + std::to_string(b) + " , A : " + std::to_string(a) + ") ";
	}
};
