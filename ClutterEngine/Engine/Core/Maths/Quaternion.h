#pragma once
#include <Core/CCommon.h>
#include <Core/Maths/Maths.h>
#include <glm/gtx/quaternion.hpp> 
#include <Core/Maths/Vectors/Vector3.h>

class Matrix4Row;
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

	Quaternion(glm::quat quat);

	// Construct the quaternion from an axis and angle
	// It is assumed that axis is already normalized,
	// and the angle is in radians
	Quaternion(const Vector3& axis, float angle);

	Quaternion(const Vector3& euler);

	Quaternion(float inAll);

	void Set(float inX, float inY, float inZ, float inW);
	void Conjugate();
	void Normalize();

	bool operator==(const Quaternion& other) const
	{
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}

	bool operator==(Quaternion& other)
	{
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}

	bool operator!=(const Quaternion& other) const
	{
		return x != other.x || y != other.y || z != other.z || w != other.w;
	}

	bool operator!=(Quaternion& other)
	{
		return x != other.x || y != other.y || z != other.z || w != other.w;
	}


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

	Quaternion Inverse() const
	{
		float normSq = x * x + y * y + z * z + w * w;
		if (normSq == 0.0f) return Quaternion(0, 0, 0, 1);

		return Quaternion(-x / normSq, -y / normSq, -z / normSq, w / normSq);
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


	static Quaternion LookAt(const Vector3& sourcePoint, const Vector3& targetPoint, const Vector3& up = Vector3::Up)
	{
		Vector3 forward = sourcePoint - targetPoint;

		if (forward.LengthSq() < 0.0001f)
		{
			return Quaternion::Identity;
		}

		forward = Vector3::Normalize(forward);

		float dot = Vector3::Dot(forward, up);
		if (abs(abs(dot) - 1.0f) < 0.000001f)
		{
			Vector3 altUp = (abs(forward.z) < 0.9f) ? Vector3::Forward : Vector3::Right;
			return LookAt(sourcePoint, targetPoint, altUp);
		}

		Vector3 right = Vector3::Normalize(Vector3::Cross(up, forward));

		Vector3 orthogonalUp = Vector3::Cross(forward, right);

		float m[9] = {
			right.x, right.y, right.z,
			orthogonalUp.x, orthogonalUp.y, orthogonalUp.z,
			forward.x, forward.y, forward.z
		};

		float trace = m[0] + m[4] + m[8];
		Quaternion result;

		if (trace > 0.0f)
		{
			float s = 0.5f / Maths::Sqrt(trace + 1.0f);
			result.w = 0.25f / s;
			result.x = (m[5] - m[7]) * s;
			result.y = (m[6] - m[2]) * s;
			result.z = (m[1] - m[3]) * s;
		}
		else if (m[0] > m[4] && m[0] > m[8])
		{
			float s = 2.0f * Maths::Sqrt(1.0f + m[0] - m[4] - m[8]);
			result.w = (m[5] - m[7]) / s;
			result.x = 0.25f * s;
			result.y = (m[1] + m[3]) / s;
			result.z = (m[6] + m[2]) / s;
		}
		else if (m[4] > m[8])
		{
			float s = 2.0f * Maths::Sqrt(1.0f + m[4] - m[0] - m[8]);
			result.w = (m[6] - m[2]) / s;
			result.x = (m[1] + m[3]) / s;
			result.y = 0.25f * s;
			result.z = (m[5] + m[7]) / s;
		}
		else
		{
			float s = 2.0f * Maths::Sqrt(1.0f + m[8] - m[0] - m[4]);
			result.w = (m[1] - m[3]) / s;
			result.x = (m[6] + m[2]) / s;
			result.y = (m[5] + m[7]) / s;
			result.z = 0.25f * s;
		}

		return result.Normalized();
	}

	static Quaternion FromMatrix(const Matrix4Row& m);

	Vector3 ToEuler() const
	{
		Vector3 euler;
		
		euler.y = std::atan2(2.0f * (w * y + z * x),
			1.0f - 2.0f * (y * y + x * x));

		float sinp = 2.0f * (w * x - y * z);
		if (std::abs(sinp) >= 1)
			euler.x = std::copysign(Maths::PI_OVER2, sinp);
		else
			euler.x = std::asin(sinp);

		euler.z = std::atan2(2.0f * (w * z + x * y),
			1.0f - 2.0f * (z * z + x * x));

		return euler;
	}

	inline std::string ToString()
	{
		return "Rotation: ("
			+ std::to_string(x) + ", "
			+ std::to_string(y) + ", "
			+ std::to_string(z) + ", "
			+ std::to_string(w) + ")";
	}

	inline glm::quat ToGLM()
	{
		return { x, y, z, w };
	}

	class Matrix4 AsMatrix() const;

	class Matrix4Row AsMatrixRow() const;

	static const Quaternion Identity;
};