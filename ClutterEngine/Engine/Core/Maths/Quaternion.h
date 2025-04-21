#pragma once
#include <Core/CCommon.h>
#include <Core/Maths/Maths.h>
#include <Core/Maths/Vectors/Vector3.h>

struct CLUTTER_API Quaternion
{
	float x;
	float y;
	float z;
	float w;

	Quaternion()
	{
		*this = Quaternion::Identity;
	}

	// This directly sets the quaternion components --
	// don't use for axis/angle
	Quaternion(float inX, float inY, float inZ, float inW);

	// Construct the quaternion from an axis and angle
	// It is assumed that axis is already normalized,
	// and the angle is in radians
	Quaternion(const Vector3& axis, float angle);

	Quaternion(float inAll);

	void Set(float inX, float inY, float inZ, float inW);
	void Conjugate();
	void Normalize();

	float LengthSqr() const
	{
		return (x * x + y * y + z * z + w * w);
	}

	float Length() const
	{
		return Maths::Sqrt(LengthSqr());
	}

	Quaternion Normalized() const
	{
		float length = sqrt(x * x + y * y + z * z + w * w);
		return { x / length, y / length, z / length, w / length };
	}

	// Normalize the provided quaternion
	static Quaternion Normalize(const Quaternion& q)
	{
		Quaternion retVal = q;
		retVal.Normalize();
		return retVal;
	}

	// Linear interpolation
	static Quaternion Lerp(const Quaternion& a, const Quaternion& b, float f)
	{
		Quaternion retVal;
		retVal.x = Maths::Lerp(a.x, b.x, f);
		retVal.y = Maths::Lerp(a.y, b.y, f);
		retVal.z = Maths::Lerp(a.z, b.z, f);
		retVal.w = Maths::Lerp(a.w, b.w, f);
		retVal.Normalize();
		return retVal;
	}

	static float Dot(const Quaternion& a, const Quaternion& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}


	// Spherical Linear Interpolation
	static Quaternion Slerp(const Quaternion& a, const Quaternion& b, float f)
	{
		float rawCosm = Quaternion::Dot(a, b);

		float cosom = -rawCosm;
		if (rawCosm >= 0.0f)
		{
			cosom = rawCosm;
		}

		float scale0, scale1;

		if (cosom < 0.9999f)
		{
			const float omega = Maths::ACos(cosom);
			const float invSin = 1.f / Maths::Sin(omega);
			scale0 = Maths::Sin((1.f - f) * omega) * invSin;
			scale1 = Maths::Sin(f * omega) * invSin;
		}
		else
		{
			// Use linear interpolation if the quaternions
			// are collinear
			scale0 = 1.0f - f;
			scale1 = f;
		}

		if (rawCosm < 0.0f)
		{
			scale1 = -scale1;
		}

		Quaternion retVal;
		retVal.x = scale0 * a.x + scale1 * b.x;
		retVal.y = scale0 * a.y + scale1 * b.y;
		retVal.z = scale0 * a.z + scale1 * b.z;
		retVal.w = scale0 * a.w + scale1 * b.w;
		retVal.Normalize();
		return retVal;
	}

	// Concatenate
	// Rotate by q FOLLOWED BY p
	static Quaternion Concatenate(const Quaternion& q, const Quaternion& p)
	{
		Quaternion retVal;

		// Vector component is:
		// ps * qv + qs * pv + pv x qv
		Vector3 qv(q.x, q.y, q.z);
		Vector3 pv(p.x, p.y, p.z);
		Vector3 newVec = p.w * qv + q.w * pv + Vector3::Cross(pv, qv);
		retVal.x = newVec.x;
		retVal.y = newVec.y;
		retVal.z = newVec.z;

		// Scalar component is:
		// ps * qs - pv . qv
		retVal.w = p.w * q.w - Vector3::Dot(pv, qv);

		return retVal;
	}

    static Quaternion FromEuler(const Vector3& axis) {

        float angleRadiansX = 0.0f;
        float halfAngleX = 0.0f;
        float sinHalfAngleX = 0.0f;

        float angleRadiansY = 0.0f;
        float halfAngleY = 0.0f;
        float sinHalfAngleY = 0.0f;

        float angleRadiansZ = 0.0f;
        float halfAngleZ = 0.0f;
        float sinHalfAngleZ = 0.0f;

        if (axis.x != 0)
        {
            angleRadiansX = Maths::ToRad(axis.x);
            halfAngleX = angleRadiansX * 0.5f;
            sinHalfAngleX = sinf(halfAngleX);
        }

        if (axis.y != 0)
        {
            angleRadiansY = Maths::ToRad(axis.y);
            halfAngleY = angleRadiansY * 0.5f;
            sinHalfAngleY = sinf(halfAngleY);
        }

        if (axis.z != 0)
        {
            angleRadiansZ = Maths::ToRad(axis.z);
            halfAngleZ = angleRadiansZ * 0.5f;
            sinHalfAngleZ = sinf(halfAngleZ);
        }

		if (axis.Length() > 0)
		{
			Vector3 normalizedAxis = Vector3::Normalize(axis);
			return Quaternion(
				normalizedAxis.x * sinHalfAngleX,
				normalizedAxis.y * sinHalfAngleY,
				normalizedAxis.z * sinHalfAngleZ,
				cosf(halfAngleX + halfAngleY + halfAngleZ)
			);
		}
		else
		{
			return Quaternion::Identity;
		}

    }

	inline std::string ToString()
	{
		return "Rotation: ("
			+ std::to_string(x) + ", "
			+ std::to_string(y) + ", "
			+ std::to_string(z) + ", "
			+ std::to_string(w) + ")";
	}

	class Matrix4 AsMatrix() const;

	class Matrix4Row AsMatrixRow() const;

	static const Quaternion Identity;
};