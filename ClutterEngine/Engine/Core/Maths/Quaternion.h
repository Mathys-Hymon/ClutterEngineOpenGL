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


	static Quaternion LookAt(const Vector3& sourcePoint, const Vector3& targetPoint, const Vector3& up = Vector3::Up)
	{
		Vector3 forward = Vector3::Normalize(targetPoint - sourcePoint);
		Vector3 right = Vector3::Normalize(Vector3::Cross(up, forward));
		Vector3 newUp = Vector3::Cross(forward, right);

		float m00 = right.x, m01 = right.y, m02 = right.z;
		float m10 = newUp.x, m11 = newUp.y, m12 = newUp.z;
		float m20 = forward.x, m21 = forward.y, m22 = forward.z;

		float trace = m00 + m11 + m22;
		float qw, qx, qy, qz;

		if (trace > 0.0f) {
			float s = sqrtf(trace + 1.0f) * 2.0f;
			qw = 0.25f * s;
			qx = (m21 - m12) / s;
			qy = (m02 - m20) / s;
			qz = (m10 - m01) / s;
		}
		else if ((m00 > m11) && (m00 > m22)) {
			float s = sqrtf(1.0f + m00 - m11 - m22) * 2.0f;
			qw = (m21 - m12) / s;
			qx = 0.25f * s;
			qy = (m01 + m10) / s;
			qz = (m02 + m20) / s;
		}
		else if (m11 > m22) {
			float s = sqrtf(1.0f + m11 - m00 - m22) * 2.0f;
			qw = (m02 - m20) / s;
			qx = (m01 + m10) / s;
			qy = 0.25f * s;
			qz = (m12 + m21) / s;
		}
		else {
			float s = sqrtf(1.0f + m22 - m00 - m11) * 2.0f;
			qw = (m10 - m01) / s;
			qx = (m02 + m20) / s;
			qy = (m12 + m21) / s;
			qz = 0.25f * s;
		}

		return Quaternion(qx, qy, qz, qw).Normalized();
	}

	// Convert quaternion to Euler angles (pitch, yaw, roll)
	Vector3 QuaternionToEuler() const
	{
		// Convert quaternion to Euler angles (pitch, yaw, roll)
		float pitch = std::atan2(2.0f * (w * x + y * z),
			1.0f - 2.0f * (x * x + y * y));
		float yaw = std::asin(2.0f * (w * y - z * x));
		float roll = std::atan2(2.0f * (w * z + x * y),
			1.0f - 2.0f * ( y * y + z * z));

		return Vector3(pitch, yaw, roll);
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