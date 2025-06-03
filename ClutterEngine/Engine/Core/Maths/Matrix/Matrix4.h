#pragma once
#include <Core/CCommon.h>
#include <array>
#include <Core/Maths/Maths.h>
#include <Core/Maths/Quaternion.h>

using std::array;

struct CLUTTER_API Matrix4
{
	array<float, 16> mat;

	Matrix4()
	{
		*this = Matrix4::Identity;
	}

	Matrix4(const array<float, 16>& that)
	{
		for (int n = 0; n < 16; ++n) {
			mat[n] = that[n];
		}
	}

	const float* GetAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&mat[0]);
	}

	inline float& operator()(const int i, const int j)
	{
		return mat[i * 4 + j];
	}

	inline Matrix4& operator=(const Matrix4& that)
	{
		for (int n = 0; n < 16; ++n) {
			mat[n] = that.mat[n];
		}
		return *this;
	}

	inline Matrix4 operator+(const Matrix4& that) const
	{
		Matrix4 result;
		int n;
		for (n = 0; n < 16; n++)
			result.mat[n] = mat[n] + that.mat[n];
		return result;
	}

	inline Matrix4& operator+=(const Matrix4& that)
	{
		return (*this = *this + that);
	}

	inline Matrix4 operator-(const Matrix4& that) const
	{
		Matrix4 result;
		int n;
		for (n = 0; n < 16; n++)
			result.mat[n] = mat[n] - that.mat[n];
		return result;
	}

	inline Matrix4& operator-=(const Matrix4& that)
	{
		return (*this = *this - that);
	}

	// Matrix multiplication (a * b)
	friend Matrix4 operator*(Matrix4& a, Matrix4& b)
	{
		Matrix4 retVal;

		retVal(0, 0) =
			a(0, 0) * b(0, 0) +
			a(1, 0) * b(0, 1) +
			a(2, 0) * b(0, 2) +
			a(3, 0) * b(0, 3);

		retVal(0, 1) =
			a(0, 1) * b(0, 0) +
			a(1, 1) * b(0, 1) +
			a(2, 1) * b(0, 2) +
			a(3, 1) * b(0, 3);

		retVal(0, 2) =
			a(0, 2) * b(0, 0) +
			a(1, 2) * b(0, 1) +
			a(2, 2) * b(0, 2) +
			a(3, 2) * b(0, 3);

		retVal(0, 3) =
			a(0, 3) * b(0, 0) +
			a(1, 3) * b(0, 1) +
			a(2, 3) * b(0, 2) +
			a(3, 3) * b(0, 3);

		retVal(1, 0) =
			a(0, 0) * b(1, 0) +
			a(1, 0) * b(1, 1) +
			a(2, 0) * b(1, 2) +
			a(3, 0) * b(1, 3);

		retVal(1, 1) =
			a(0, 1) * b(1, 0) +
			a(1, 1) * b(1, 1) +
			a(2, 1) * b(1, 2) +
			a(3, 1) * b(1, 3);

		retVal(1, 2) =
			a(0, 2) * b(1, 0) +
			a(1, 2) * b(1, 1) +
			a(2, 2) * b(1, 2) +
			a(3, 2) * b(1, 3);

		retVal(1, 3) =
			a(0, 3) * b(1, 0) +
			a(1, 3) * b(1, 1) +
			a(2, 3) * b(1, 2) +
			a(3, 3) * b(1, 3);

		retVal(2, 0) =
			a(0, 0) * b(2, 0) +
			a(1, 0) * b(2, 1) +
			a(2, 0) * b(2, 2) +
			a(3, 0) * b(2, 3);

		retVal(2, 1) =
			a(0, 1) * b(2, 0) +
			a(1, 1) * b(2, 1) +
			a(2, 1) * b(2, 2) +
			a(3, 1) * b(2, 3);

		retVal(2, 2) =
			a(0, 2) * b(2, 0) +
			a(1, 2) * b(2, 1) +
			a(2, 2) * b(2, 2) +
			a(3, 2) * b(2, 3);

		retVal(2, 3) =
			a(0, 3) * b(2, 0) +
			a(1, 3) * b(2, 1) +
			a(2, 3) * b(2, 2) +
			a(3, 3) * b(2, 3);

		retVal(3, 0) =
			a(0, 0) * b(3, 0) +
			a(1, 0) * b(3, 1) +
			a(2, 0) * b(3, 2) +
			a(3, 0) * b(3, 3);

		retVal(3, 1) =
			a(0, 1) * b(3, 0) +
			a(1, 1) * b(3, 1) +
			a(2, 1) * b(3, 2) +
			a(3, 1) * b(3, 3);

		retVal(3, 2) =
			a(0, 2) * b(3, 0) +
			a(1, 2) * b(3, 1) +
			a(2, 2) * b(3, 2) +
			a(3, 2) * b(3, 3);

		retVal(3, 3) =
			a(0, 3) * b(3, 0) +
			a(1, 3) * b(3, 1) +
			a(2, 3) * b(3, 2) +
			a(3, 3) * b(3, 3);

		return retVal;
	}

	Matrix4& operator*=(Matrix4& right)
	{
		*this = *this * right;
		return *this;
	}

	// Invert the matrix - super slow
	void Invert();

	Vector3 GetTranslation() const
	{

		return Vector3(mat[12], mat[13], mat[14]);
	}

	Vector3 GetXAxis() const
	{
		return Vector3::Normalize(Vector3(mat[0], mat[1], mat[2]));
	}

	Vector3 GetYAxis() const
	{
		return Vector3::Normalize(Vector3(mat[4], mat[5], mat[6]));
	}

	Vector3 GetZAxis() const
	{
		return Vector3::Normalize(Vector3(mat[8], mat[9], mat[10]));
	}

	Vector3 GetScale() const
	{
		Vector3 retVal;
		retVal.x = Vector3(mat[0], mat[1], mat[2]).Length();
		retVal.y = Vector3(mat[4], mat[5], mat[6]).Length();
		retVal.z = Vector3(mat[8], mat[9], mat[10]).Length();
		return retVal;
	}

	static Matrix4 CreateScale(float xScale, float yScale, float zScale)
	{
		array<float, 16> temp =
		{
			xScale, 0.0f, 0.0f, 0.0f,
			0.0f, yScale, 0.0f, 0.0f,
			0.0f, 0.0f, zScale, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
		return Matrix4(temp);
	}

	static Matrix4 CreateScale(const Vector3& scaleVector)
	{
		return CreateScale(scaleVector.x, scaleVector.y, scaleVector.z);
	}

	static Matrix4 CreateScale(float scale)
	{
		return CreateScale(scale, scale, scale);
	}

	static Matrix4 CreateRotationX(float theta)
	{
		array<float, 16> temp =
		{
			1.0f, 0.0f, 0.0f , 0.0f,
			0.0f, Maths::Cos(theta), -Maths::Sin(theta), 0.0f,
			0.0f, Maths::Sin(theta), Maths::Cos(theta), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f,
		};
		return Matrix4(temp);
	}

	static Matrix4 CreateRotationY(float theta)
	{
		array<float, 16> temp =
		{
			Maths::Cos(theta), 0.0f, Maths::Sin(theta), 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			-Maths::Sin(theta), 0.0f, Maths::Cos(theta), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f,
		};
		return Matrix4(temp);
	}

	static Matrix4 CreateRotationZ(float theta)
	{
		array<float, 16> temp =
		{
			Maths::Cos(theta), -Maths::Sin(theta), 0.0f, 0.0f,
			Maths::Sin(theta), Maths::Cos(theta), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f,
		};
		return Matrix4(temp);
	}

	static Matrix4 CreateTranslation(const Vector3& trans)
	{
		array<float, 16> temp =
		{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			trans.x, trans.y, trans.z, 1.0f
		};
		return Matrix4(temp);
	}

	static Matrix4 CreateSimpleViewProj(float width, float height)
	{
		array<float, 16> temp =
		{
			2.0f / width, 0.0f, 0.0f, 0.0f,
			0.0f, 2.0f / height, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
		return Matrix4(temp);
	}

	static Matrix4 CreateFromQuaternion(const Quaternion& q)
	{
		array<float, 16> temp;
		temp[0] = 1.0f - 2.0f * q.y * q.y - 2.0f * q.z * q.z;
		temp[1] = 2.0f * q.x * q.y - 2.0f * q.w * q.z;
		temp[2] = 2.0f * q.x * q.z + 2.0f * q.w * q.y;
		temp[3] = 0.0f;

		temp[4] = 2.0f * q.x * q.y + 2.0f * q.w * q.z;
		temp[5] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z;
		temp[6] = 2.0f * q.y * q.z - 2.0f * q.w * q.x;
		temp[7] = 0.0f;

		temp[8] = 2.0f * q.x * q.z - 2.0f * q.w * q.y;
		temp[9] = 2.0f * q.y * q.z - 2.0f * q.w * q.x;
		temp[10] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.y * q.y;
		temp[11] = 0.0f;

		temp[12] = 0.0f;
		temp[13] = 0.0f;
		temp[14] = 0.0f;
		temp[15] = 1.0f;

		return Matrix4(temp);
	}

	static Matrix4 CreateLookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
	{
		Vector3 zaxis = Vector3::Normalize(eye - target);
		Vector3 normalizedUp = Vector3::Normalize(up);
		Vector3 xaxis = Vector3::Normalize(Vector3::Cross(normalizedUp, zaxis));
		Vector3 yaxis = Vector3::Normalize(Vector3::Cross(zaxis, xaxis));

		array<float, 16> temp =
		{
			xaxis.x, yaxis.x, zaxis.x, 0.0f,
			xaxis.y, yaxis.y, zaxis.y, 0.0f,
			xaxis.z, yaxis.z, zaxis.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
		Matrix4 t = Matrix4(temp);
		Matrix4 translation = Matrix4::CreateTranslation(Vector3(-eye.x, -eye.y, -eye.z));
		return t * translation;
	}

	static Matrix4 CreateOrtho(float width, float height, float pNear, float pFar)
	{
		array<float, 16> temp =
		{
			2.0f / width, 0.0f, 0.0f, 0.0f,
			0.0f, 2.0f / height, 0.0f, 0.0f,
			0.0f, 0.0f, 2.0f / (pNear - pFar), 0.0f,
			0.0f, 0.0f, (pFar + pNear) / (pFar - pFar), 1.0f
		};
		return Matrix4(temp);
	}

	static Matrix4 CreatePerspectiveFOV(float fovY, float width, float height, float pNear, float pFar)
	{
		float yScale = Maths::Cot(fovY / 2.0f);
		float xScale = yScale * height / width;
		array<float, 16> temp =
		{
			xScale, 0.0f, 0.0f, 0.0f,
			0.0f, yScale, 0.0f, 0.0f,
			0.0f, 0.0f, pNear + pFar / (pNear - pFar), -1.0f,
			0.0f, 0.0f,  2.0f * pNear * pFar / (pNear - pFar), 0.0f
		};
		return Matrix4(temp);
	}

	static Matrix4 CreatePerspective(float left, float right, float bottom, float top, float pNear, float pFar)
	{
		array<float, 16> temp =
		{
			2 * pNear / (right - left), 0.0f, 0.0f, 0.0f,
			0.0f, 2 * pNear / (top - bottom), 0.0f, 0.0f,
			(right + left) / (right - left), (top + bottom) / (top - bottom), (pFar + pNear) / (pNear - pFar), -1.0f,
			0.0f, 0.0f, 2 * pNear * pFar / (pNear - pFar), 0.0f
		};
		return Matrix4(temp);
	}

	static const Matrix4 Identity;
};
#pragma once
#include <Core/CCommon.h>
#include <array>
#include <Core/Maths/Maths.h>
#include <Core/Maths/Quaternion.h>

using std::array;

/**
 * @brief 4x4 column-major matrix for 3D transformations.
 */
struct CLUTTER_API Matrix4
{
    /**
     * @brief Matrix elements in column-major order.
     */
    array<float, 16> mat;

    /**
     * @brief Default constructor. Initializes to identity matrix.
     */
    Matrix4();

    /**
     * @brief Constructs a matrix from an array of 16 floats.
     * @param that Array of 16 floats (column-major order).
     */
    Matrix4(const array<float, 16>& that);

    /**
     * @brief Returns a pointer to the matrix data as a float array.
     * @return Pointer to the first element.
     */
    const float* GetAsFloatPtr() const;

    /**
     * @brief Accesses the element at row i, column j.
     * @param i Row index (0-3).
     * @param j Column index (0-3).
     * @return Reference to the element.
     */
    inline float& operator()(const int i, const int j);

    /**
     * @brief Assignment operator.
     * @param that Matrix to assign from.
     * @return Reference to this matrix.
     */
    inline Matrix4& operator=(const Matrix4& that);

    /**
     * @brief Matrix addition.
     * @param that Matrix to add.
     * @return Sum of matrices.
     */
    inline Matrix4 operator+(const Matrix4& that) const;

    /**
     * @brief Matrix addition assignment.
     * @param that Matrix to add.
     * @return Reference to this matrix.
     */
    inline Matrix4& operator+=(const Matrix4& that);

    /**
     * @brief Matrix subtraction.
     * @param that Matrix to subtract.
     * @return Difference of matrices.
     */
    inline Matrix4 operator-(const Matrix4& that) const;

    /**
     * @brief Matrix subtraction assignment.
     * @param that Matrix to subtract.
     * @return Reference to this matrix.
     */
    inline Matrix4& operator-=(const Matrix4& that);

    /**
     * @brief Matrix multiplication (a * b).
     * @param a Left matrix.
     * @param b Right matrix.
     * @return Product matrix.
     */
    friend Matrix4 operator*(Matrix4& a, Matrix4& b);

    /**
     * @brief Matrix multiplication assignment.
     * @param right Matrix to multiply by.
     * @return Reference to this matrix.
     */
    Matrix4& operator*=(Matrix4& right);

    /**
     * @brief Inverts the matrix in place. (Slow)
     */
    void Invert();

    /**
     * @brief Gets the translation component (last column, except w).
     * @return Translation as a Vector3.
     */
    Vector3 GetTranslation() const;

    /**
     * @brief Gets the normalized X axis (first column).
     * @return X axis as a Vector3.
     */
    Vector3 GetXAxis() const;

    /**
     * @brief Gets the normalized Y axis (second column).
     * @return Y axis as a Vector3.
     */
    Vector3 GetYAxis() const;

    /**
     * @brief Gets the normalized Z axis (third column).
     * @return Z axis as a Vector3.
     */
    Vector3 GetZAxis() const;

    /**
     * @brief Gets the scale factors along each axis.
     * @return Scale as a Vector3.
     */
    Vector3 GetScale() const;

    /**
     * @brief Creates a scale matrix.
     * @param xScale Scale along X.
     * @param yScale Scale along Y.
     * @param zScale Scale along Z.
     * @return Scale matrix.
     */
    static Matrix4 CreateScale(float xScale, float yScale, float zScale);

    /**
     * @brief Creates a scale matrix from a vector.
     * @param scaleVector Scale vector.
     * @return Scale matrix.
     */
    static Matrix4 CreateScale(const Vector3& scaleVector);

    /**
     * @brief Creates a uniform scale matrix.
     * @param scale Uniform scale factor.
     * @return Scale matrix.
     */
    static Matrix4 CreateScale(float scale);

    /**
     * @brief Creates a rotation matrix around the X axis.
     * @param theta Angle in radians.
     * @return Rotation matrix.
     */
    static Matrix4 CreateRotationX(float theta);

    /**
     * @brief Creates a rotation matrix around the Y axis.
     * @param theta Angle in radians.
     * @return Rotation matrix.
     */
    static Matrix4 CreateRotationY(float theta);

    /**
     * @brief Creates a rotation matrix around the Z axis.
     * @param theta Angle in radians.
     * @return Rotation matrix.
     */
    static Matrix4 CreateRotationZ(float theta);

    /**
     * @brief Creates a translation matrix.
     * @param trans Translation vector.
     * @return Translation matrix.
     */
    static Matrix4 CreateTranslation(const Vector3& trans);

    /**
     * @brief Creates a simple orthographic view-projection matrix.
     * @param width Width of the view.
     * @param height Height of the view.
     * @return View-projection matrix.
     */
    static Matrix4 CreateSimpleViewProj(float width, float height);

    /**
     * @brief Creates a rotation matrix from a quaternion.
     * @param q Quaternion.
     * @return Rotation matrix.
     */
    static Matrix4 CreateFromQuaternion(const Quaternion& q);

    /**
     * @brief Creates a look-at view matrix.
     * @param eye Camera position.
     * @param target Target position.
     * @param up Up direction.
     * @return Look-at matrix.
     */
    static Matrix4 CreateLookAt(const Vector3& eye, const Vector3& target, const Vector3& up);

    /**
     * @brief Creates an orthographic projection matrix.
     * @param width Width of the view volume.
     * @param height Height of the view volume.
     * @param pNear Near plane.
     * @param pFar Far plane.
     * @return Orthographic projection matrix.
     */
    static Matrix4 CreateOrtho(float width, float height, float pNear, float pFar);

    /**
     * @brief Creates a perspective projection matrix using field of view.
     * @param fovY Vertical field of view in radians.
     * @param width Width of the view.
     * @param height Height of the view.
     * @param pNear Near plane.
     * @param pFar Far plane.
     * @return Perspective projection matrix.
     */
    static Matrix4 CreatePerspectiveFOV(float fovY, float width, float height, float pNear, float pFar);

    /**
     * @brief Creates a perspective projection matrix.
     * @param left Left plane.
     * @param right Right plane.
     * @param bottom Bottom plane.
     * @param top Top plane.
     * @param pNear Near plane.
     * @param pFar Far plane.
     * @return Perspective projection matrix.
     */
    static Matrix4 CreatePerspective(float left, float right, float bottom, float top, float pNear, float pFar);

    /**
     * @brief The identity matrix.
     */
    static const Matrix4 Identity;
};
