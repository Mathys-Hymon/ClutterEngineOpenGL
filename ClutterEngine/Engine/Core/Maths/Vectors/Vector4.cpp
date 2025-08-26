#include "pch.h"
#include <Core/Maths/Vectors/Vector4.h>
#include <Core/Maths/Matrix/Matrix4Row.h>
#include <Core/Maths/Maths.h>

const Vector4 Vector4::Zero(0.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::One(1.0f, 1.0f, 1.0f, 1.0f);
             
const Vector4 Vector4::Infinity(Maths::INFINITY_POS, Maths::INFINITY_POS, Maths::INFINITY_POS, Maths::INFINITY_POS);
const Vector4 Vector4::NegInfinity(Maths::INFINITY_NEG, Maths::INFINITY_NEG, Maths::INFINITY_NEG, Maths::INFINITY_NEG);

float Vector4::LengthSqr() const
{
    return (x * x + y * y + z * z + w * w);
}

float Vector4::Length() const
{
    return (Maths::Sqrt(LengthSqr()));
}

void Vector4::Normalize()
{
    float len = Length();
    x /= len;
    y /= len;
    z /= len;
    w /= len;
}
