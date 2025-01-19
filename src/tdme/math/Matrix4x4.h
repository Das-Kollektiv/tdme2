#pragma once

#include <array>

#include <tdme/tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>

using std::array;

using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::math::Vector4;

/**
 * Matrix4x4 class representing matrix4x4 mathematical structure and operations for 3d space
 * @author Andreas Drewke, Song Ho Ahn <song.ahn@gmail.com>
 */
class tdme::math::Matrix4x4 final
{
private:
	array<float, 16> data {
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	};

public:
	/**
	 * Public constructor
	 */
	inline Matrix4x4() {
	}

	/**
	 * Public constructor
	 * @param r0c0 row 0, column 0
	 * @param r0c1 row 0, column 1
	 * @param r0c2 row 0, column 2
	 * @param r0c3 row 0, column 3
	 * @param r1c0 row 1, column 0
	 * @param r1c1 row 1, column 1
	 * @param r1c2 row 1, column 2
	 * @param r1c3 row 1, column 3
	 * @param r2c0 row 2, column 0
	 * @param r2c1 row 2, column 1
	 * @param r2c2 row 2, column 2
	 * @param r2c3 row 2, column 3
	 * @param r3c0 row 3, column 0
	 * @param r3c1 row 3, column 1
	 * @param r3c2 row 3, column 2
	 * @param r3c3 row 3, column 3
	 */
	inline Matrix4x4(
		float r0c0, float r0c1, float r0c2, float r0c3,
		float r1c0, float r1c1, float r1c2, float r1c3,
		float r2c0, float r2c1, float r2c2, float r2c3,
		float r3c0, float r3c1, float r3c2, float r3c3
	) {
		set(
			r0c0, r0c1, r0c2, r0c3,
			r1c0, r1c1, r1c2, r1c3,
			r2c0, r2c1, r2c2, r2c3,
			r3c0, r3c1, r3c2, r3c3
		);
	}

	/**
	 * Public constructor
	 * @param matrix matrix as array
	 */
	inline Matrix4x4(const array<float, 16>& matrix) {
		data = matrix;
	}

	/**
	 * Public constructor
	 * @param matrix matrix
	 */
	inline Matrix4x4(const Matrix4x4& matrix) {
		data = matrix.data;
	}

	/**
	 * Sets this matrix by its components
	 * @param r0c0 row 0, column 0
	 * @param r0c1 row 0, column 1
	 * @param r0c2 row 0, column 2
	 * @param r0c3 row 0, column 3
	 * @param r1c0 row 1, column 0
	 * @param r1c1 row 1, column 1
	 * @param r1c2 row 1, column 2
	 * @param r1c3 row 1, column 3
	 * @param r2c0 row 2, column 0
	 * @param r2c1 row 2, column 1
	 * @param r2c2 row 2, column 2
	 * @param r2c3 row 2, column 3
	 * @param r3c0 row 3, column 0
	 * @param r3c1 row 3, column 1
	 * @param r3c2 row 3, column 2
	 * @param r3c3 row 3, column 3
	 * @returns this matrix
	 */
	inline Matrix4x4& set(
		float r0c0, float r0c1, float r0c2, float r0c3,
		float r1c0, float r1c1, float r1c2, float r1c3,
		float r2c0, float r2c1, float r2c2, float r2c3,
		float r3c0, float r3c1, float r3c2, float r3c3
		) {
		//
		data[0] = r0c0;
		data[1] = r0c1;
		data[2] = r0c2;
		data[3] = r0c3;
		data[4] = r1c0;
		data[5] = r1c1;
		data[6] = r1c2;
		data[7] = r1c3;
		data[8] = r2c0;
		data[9] = r2c1;
		data[10] = r2c2;
		data[11] = r2c3;
		data[12] = r3c0;
		data[13] = r3c1;
		data[14] = r3c2;
		data[15] = r3c3;
		return *this;
	}

	/**
	 * Sets this matrix by array
	 * @param matrix matrix as array
	 * @returns this matrix
	 */
	inline Matrix4x4& set(const array<float, 16>& matrix) {
		data = matrix;
		return *this;
	}

	/**
	 * Sets this matrix by given matrix
	 * @param matrix matrix
	 * @returns
	 */
	inline Matrix4x4& set(const Matrix4x4& matrix) {
		data = matrix.data;
		return *this;
	}

	/**
	 * Creates identity matrix
	 * @returns this matrix
	 */
	inline Matrix4x4& identity() {
		data[0] = 1.0f;
		data[1] = 0.0f;
		data[2] = 0.0f;
		data[3] = 0.0f;
		data[4] = 0.0f;
		data[5] = 1.0f;
		data[6] = 0.0f;
		data[7] = 0.0f;
		data[8] = 0.0f;
		data[9] = 0.0f;
		data[10] = 1.0f;
		data[11] = 0.0f;
		data[12] = 0.0f;
		data[13] = 0.0f;
		data[14] = 0.0f;
		data[15] = 1.0f;
		return *this;
	}

	/**
	 * Scales by scalar
	 * @param scalar scalar
	 * @returns this matrix
	 */
	inline Matrix4x4& scale(float scalar) {
		data[0] *= scalar;
		data[1] *= scalar;
		data[2] *= scalar;
		data[3] *= scalar;
		data[4] *= scalar;
		data[5] *= scalar;
		data[6] *= scalar;
		data[7] *= scalar;
		data[8] *= scalar;
		data[9] *= scalar;
		data[10] *= scalar;
		data[11] *= scalar;
		return *this;
	}

	/**
	 * Scales by vector3
	 * @param vector3 vector3
	 * @returns this matrix
	 */
	inline Matrix4x4& scale(const Vector3& vector3) {
		data[0] *= vector3.data[0];
		data[1] *= vector3.data[0];
		data[2] *= vector3.data[0];
		data[3] *= vector3.data[0];
		data[4] *= vector3.data[1];
		data[5] *= vector3.data[1];
		data[6] *= vector3.data[1];
		data[7] *= vector3.data[1];
		data[8] *= vector3.data[2];
		data[9] *= vector3.data[2];
		data[10] *= vector3.data[2];
		data[11] *= vector3.data[2];
		return *this;
	}

	/**
	 * Multiplies this matrix with vector3
	 * @param vector3 vector3
	 * @returns vector3
	 */
	inline Vector3 multiply(const Vector3& vector3) const {
		return Vector3(
			vector3.data[0] * data[0] + vector3.data[1] * data[4] + vector3.data[2] * data[8] + data[12],
			vector3.data[0] * data[1] + vector3.data[1] * data[5] + vector3.data[2] * data[9] + data[13],
			vector3.data[0] * data[2] + vector3.data[1] * data[6] + vector3.data[2] * data[10] + data[14]
		);
	}

	/**
	 * Multiplies this matrix with vector3 while ignoring translation
	 * @param vector3 Vector3
	 * @returns vector3
	 */
	inline Vector3 multiplyNoTranslation(const Vector3& vector3) const {
		return Vector3(
			vector3.data[0] * data[0] + vector3.data[1] * data[4] + vector3.data[2] * data[8],
			vector3.data[0] * data[1] + vector3.data[1] * data[5] + vector3.data[2] * data[9],
			vector3.data[0] * data[2] + vector3.data[1] * data[6] + vector3.data[2] * data[10]
		);
	}

	/**
	 * Multiplies this matrix with vector4
	 * @param vector4 vector4
	 * @returns vector4
	 */
	inline Vector4 multiply(const Vector4& vector4) const {
		return Vector4(
			vector4.data[0] * data[0] + vector4.data[1] * data[4] + vector4.data[2] * data[8] + vector4.data[3] * data[12],
			vector4.data[0] * data[1] + vector4.data[1] * data[5] + vector4.data[2] * data[9] + vector4.data[3] * data[13],
			vector4.data[0] * data[2] + vector4.data[1] * data[6] + vector4.data[2] * data[10] + vector4.data[3] * data[14],
			vector4.data[0] * data[3] + vector4.data[1] * data[7] + vector4.data[2] * data[11] + vector4.data[3] * data[15]
		);
	}

	/**
	 * Multiplies this matrix with given matrix
	 * @param matrix matrix
	 * @returns this matrix
	 */
	inline Matrix4x4& multiply(const Matrix4x4& matrix) {
		array<float, 16> _data;
		_data[0] = data[0] * matrix.data[0] + data[1] * matrix.data[4] + data[2] * matrix.data[8] + data[3] * matrix.data[12];
		_data[1] = data[0] * matrix.data[1] + data[1] * matrix.data[5] + data[2] * matrix.data[9] + data[3] * matrix.data[13];
		_data[2] = data[0] * matrix.data[2] + data[1] * matrix.data[6] + data[2] * matrix.data[10] + data[3] * matrix.data[14];
		_data[3] = data[0] * matrix.data[3] + data[1] * matrix.data[7] + data[2] * matrix.data[11] + data[3] * matrix.data[15];
		_data[4] = data[4] * matrix.data[0] + data[5] * matrix.data[4] + data[6] * matrix.data[8] + data[7] * matrix.data[12];
		_data[5] = data[4] * matrix.data[1] + data[5] * matrix.data[5] + data[6] * matrix.data[9] + data[7] * matrix.data[13];
		_data[6] = data[4] * matrix.data[2] + data[5] * matrix.data[6] + data[6] * matrix.data[10] + data[7] * matrix.data[14];
		_data[7] = data[4] * matrix.data[3] + data[5] * matrix.data[7] + data[6] * matrix.data[11] + data[7] * matrix.data[15];
		_data[8] = data[8] * matrix.data[0] + data[9] * matrix.data[4] + data[10] * matrix.data[8] + data[11] * matrix.data[12];
		_data[9] = data[8] * matrix.data[1] + data[9] * matrix.data[5] + data[10] * matrix.data[9] + data[11] * matrix.data[13];
		_data[10] = data[8] * matrix.data[2] + data[9] * matrix.data[6] + data[10] * matrix.data[10] + data[11] * matrix.data[14];
		_data[11] = data[8] * matrix.data[3] + data[9] * matrix.data[7] + data[10] * matrix.data[11] + data[11] * matrix.data[15];
		_data[12] = data[12] * matrix.data[0] + data[13] * matrix.data[4] + data[14] * matrix.data[8] + data[15] * matrix.data[12];
		_data[13] = data[12] * matrix.data[1] + data[13] * matrix.data[5] + data[14] * matrix.data[9] + data[15] * matrix.data[13];
		_data[14] = data[12] * matrix.data[2] + data[13] * matrix.data[6] + data[14] * matrix.data[10] + data[15] * matrix.data[14];
		_data[15] = data[12] * matrix.data[3] + data[13] * matrix.data[7] + data[14] * matrix.data[11] + data[15] * matrix.data[15];
		data = _data;
		return *this;
	}

	/**
	 * Compares this matrix with given matrix
	 * @param matrix matrix
	 * @returns equality
	 */
	inline bool equals(const Matrix4x4& matrix) const {
		return
			(this == &matrix) ||
			(
				Math::abs(data[0] - matrix.data[0]) < Math::EPSILON &&
				Math::abs(data[1] - matrix.data[1]) < Math::EPSILON &&
				Math::abs(data[2] - matrix.data[2]) < Math::EPSILON &&
				Math::abs(data[3] - matrix.data[3]) < Math::EPSILON &&
				Math::abs(data[4] - matrix.data[4]) < Math::EPSILON &&
				Math::abs(data[5] - matrix.data[5]) < Math::EPSILON &&
				Math::abs(data[6] - matrix.data[6]) < Math::EPSILON &&
				Math::abs(data[7] - matrix.data[7]) < Math::EPSILON &&
				Math::abs(data[8] - matrix.data[8]) < Math::EPSILON &&
				Math::abs(data[9] - matrix.data[9]) < Math::EPSILON &&
				Math::abs(data[10] - matrix.data[10]) < Math::EPSILON &&
				Math::abs(data[11] - matrix.data[11]) < Math::EPSILON &&
				Math::abs(data[12] - matrix.data[12]) < Math::EPSILON &&
				Math::abs(data[13] - matrix.data[13]) < Math::EPSILON &&
				Math::abs(data[14] - matrix.data[14]) < Math::EPSILON &&
				Math::abs(data[15] - matrix.data[15]) < Math::EPSILON
			);
	}

	/**
	 * Get coordinate system axes
	 * @param xAxis x axis
	 * @param yAxis y axis
	 * @param zAxis z axis
	 */
	inline void getAxes(Vector3& xAxis, Vector3& yAxis, Vector3& zAxis) const {
		xAxis.set(data[0], data[1], data[2]);
		yAxis.set(data[4], data[5], data[6]);
		zAxis.set(data[8], data[9], data[10]);
	}

	/**
	 * Set coordinate system axes
	 * @param xAxis x axis
	 * @param yAxis y axis
	 * @param zAxis z axis
	 * @returns this matrix
	 */
	inline Matrix4x4& setAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis) {
		data[0] = xAxis.data[0];
		data[1] = xAxis.data[1];
		data[2] = xAxis.data[2];
		data[3] = 0.0f;
		data[4] = yAxis.data[0];
		data[5] = yAxis.data[1];
		data[6] = yAxis.data[2];
		data[7] = 0.0f;
		data[8] = zAxis.data[0];
		data[9] = zAxis.data[1];
		data[10] = zAxis.data[2];
		data[11] = 0.0f;
		return *this;
	}

	/**
	 * Set coordinate system axes by rotation around axis by angle
	 * @param axis axis
	 * @param angle angle
	 * @returns this matrix
	 */
	inline Matrix4x4& setAxes(const Vector3& axis, float angle) {
		// see: http://www.songho.ca/opengl/gl_matrix.html
		// see: https://en.wikipedia.org/wiki/Rotation_matrix
		auto c = Math::cos(angle * Math::DEG2RAD); // cosine
		auto scalar = Math::sin(angle * Math::DEG2RAD); // sine
		auto c1 = 1.0f - c;
		auto uX = axis[0];
		auto uY = axis[1];
		auto uZ = axis[2];
		auto uX2 = Math::square(axis[0]);
		auto uY2 = Math::square(axis[1]);
		auto uZ2 = Math::square(axis[2]);
		//
		data[0] = c + uX2 * c1;
		data[1] = uX * uY * c1 + uZ * scalar;
		data[2] = uX * uZ * c1 - uY * scalar;
		//
		data[4] = uY * uX * c1 - uZ * scalar;
		data[5] = c + uY2 * c1;
		data[6] = uY * uZ * c1 + uX * scalar;
		//
		data[8] = uZ * uX * c1 + uY * scalar;
		data[9] = uZ * uY * c1 - uX * scalar;
		data[10] = c + uZ2 * c1;
		//
		return *this;
	}

	/**
	 * Get scale
	 * @param scale scale
	 */
	inline void getScale(Vector3& scale) const {
		// x axis
		scale.data[0] = Vector3(data[0], data[1], data[2]).computeLength();
		// y axis
		scale.data[1] = Vector3(data[4], data[5], data[6]).computeLength();
		// z axis
		scale.data[2] = Vector3(data[8], data[9], data[10]).computeLength();
	}

	/**
	 * Set scale
	 * @param scale scale
	 * @returns this matrix
	 */
	inline Matrix4x4& setScale(const Vector3& scale) {
		Vector3 axisVector;
		// x axis
		axisVector.set(data[0], data[1], data[2]);
		axisVector.normalize();
		axisVector.scale(scale.data[0]);
		data[0] = axisVector.data[0];
		data[1] = axisVector.data[1];
		data[2] = axisVector.data[2];
		// y axis
		axisVector.set(data[4], data[5], data[6]);
		axisVector.normalize();
		axisVector.scale(scale.data[1]);
		data[4] = axisVector.data[0];
		data[5] = axisVector.data[1];
		data[6] = axisVector.data[2];
		// z axis
		axisVector.set(data[8], data[9], data[10]);
		axisVector.normalize();
		axisVector.scale(scale.data[2]);
		data[8] = axisVector.data[0];
		data[9] = axisVector.data[1];
		data[10] = axisVector.data[2];
		//
		return *this;
	}

	/**
	 * Get translation
	 * @param translation translation
	 */
	inline void getTranslation(Vector3& translation) const {
		translation.set(data[12], data[13], data[14]);
	}

	/**
	 * Set translation
	 * @param translation translation
	 * @returns this matrix
	 */
	inline Matrix4x4& setTranslation(const Vector3& translation) {
		data[12] = translation.data[0];
		data[13] = translation.data[1];
		data[14] = translation.data[2];
		return *this;
	}

	/**
	 * Transposes this matrix
	 * @returns this matrix
	 */
	inline Matrix4x4& transpose() {
		array <float, 16> _data;
		_data[0] = data[0];
		_data[1] = data[4];
		_data[2] = data[8];
		_data[3] = data[12];
		_data[4] = data[1];
		_data[5] = data[5];
		_data[6] = data[9];
		_data[7] = data[13];
		_data[8] = data[2];
		_data[9] = data[6];
		_data[10] = data[10];
		_data[11] = data[14];
		_data[12] = data[3];
		_data[13] = data[7];
		_data[14] = data[11];
		_data[15] = data[15];
		data = _data;
		return *this;
	}

	/**
	 * Inverts this matrix
	 * @returns this matrix
	 */
	inline Matrix4x4& invert() {
		/*
		 Taken from MESA GLU implementation
		 Copyright (C) 1999-2007  Brian Paul   All Rights Reserved.
		 Permission is hereby granted, free of charge, to any person obtaining a
		 copy of this software and associated documentation files (the "Software"),
		 to 	deal in the Software without restriction, including without limitation
		 the rights to use, copy, modify, merge, publish, distribute, sublicense,
		 and/or sell copies of the Software, and to permit persons to whom the
		 Software is furnished to do so, subject to the following conditions:
		 The above copyright notice and this permission notice shall be included
		 in all copies or substantial portions of the Software.
		 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
		 OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
		 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
		 BRIAN PAUL BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
		 AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
		 CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
		*/
		array <float, 16> _data;
		_data[0] = data[5] * data[10] * data[15] - data[5] * data[11] * data[14] - data[9] * data[6] * data[15] + data[9] * data[7] * data[14] + data[13] * data[6] * data[11] - data[13] * data[7] * data[10];
		_data[4] = -data[4] * data[10] * data[15] + data[4] * data[11] * data[14] + data[8] * data[6] * data[15] - data[8] * data[7] * data[14] - data[12] * data[6] * data[11] + data[12] * data[7] * data[10];
		_data[8] = data[4] * data[9] * data[15] - data[4] * data[11] * data[13] - data[8] * data[5] * data[15] + data[8] * data[7] * data[13] + data[12] * data[5] * data[11] - data[12] * data[7] * data[9];
		_data[12] = -data[4] * data[9] * data[14] + data[4] * data[10] * data[13] + data[8] * data[5] * data[14] - data[8] * data[6] * data[13] - data[12] * data[5] * data[10] + data[12] * data[6] * data[9];
		_data[1] = -data[1] * data[10] * data[15] + data[1] * data[11] * data[14] + data[9] * data[2] * data[15] - data[9] * data[3] * data[14] - data[13] * data[2] * data[11] + data[13] * data[3] * data[10];
		_data[5] = data[0] * data[10] * data[15] - data[0] * data[11] * data[14] - data[8] * data[2] * data[15] + data[8] * data[3] * data[14] + data[12] * data[2] * data[11] - data[12] * data[3] * data[10];
		_data[9] = -data[0] * data[9] * data[15] + data[0] * data[11] * data[13] + data[8] * data[1] * data[15] - data[8] * data[3] * data[13] - data[12] * data[1] * data[11] + data[12] * data[3] * data[9];
		_data[13] = data[0] * data[9] * data[14] - data[0] * data[10] * data[13] - data[8] * data[1] * data[14] + data[8] * data[2] * data[13] + data[12] * data[1] * data[10] - data[12] * data[2] * data[9];
		_data[2] = data[1] * data[6] * data[15] - data[1] * data[7] * data[14] - data[5] * data[2] * data[15] + data[5] * data[3] * data[14] + data[13] * data[2] * data[7] - data[13] * data[3] * data[6];
		_data[6] = -data[0] * data[6] * data[15] + data[0] * data[7] * data[14] + data[4] * data[2] * data[15] - data[4] * data[3] * data[14] - data[12] * data[2] * data[7] + data[12] * data[3] * data[6];
		_data[10] = data[0] * data[5] * data[15] - data[0] * data[7] * data[13] - data[4] * data[1] * data[15] + data[4] * data[3] * data[13] + data[12] * data[1] * data[7] - data[12] * data[3] * data[5];
		_data[14] = -data[0] * data[5] * data[14] + data[0] * data[6] * data[13] + data[4] * data[1] * data[14] - data[4] * data[2] * data[13] - data[12] * data[1] * data[6] + data[12] * data[2] * data[5];
		_data[3] = -data[1] * data[6] * data[11] + data[1] * data[7] * data[10] + data[5] * data[2] * data[11] - data[5] * data[3] * data[10] - data[9] * data[2] * data[7] + data[9] * data[3] * data[6];
		_data[7] = data[0] * data[6] * data[11] - data[0] * data[7] * data[10] - data[4] * data[2] * data[11] + data[4] * data[3] * data[10] + data[8] * data[2] * data[7] - data[8] * data[3] * data[6];
		_data[11] = -data[0] * data[5] * data[11] + data[0] * data[7] * data[9] + data[4] * data[1] * data[11] - data[4] * data[3] * data[9] - data[8] * data[1] * data[7] + data[8] * data[3] * data[5];
		_data[15] = data[0] * data[5] * data[10] - data[0] * data[6] * data[9] - data[4] * data[1] * data[10] + data[4] * data[2] * data[9] + data[8] * data[1] * data[6] - data[8] * data[2] * data[5];
		auto determinant = data[0] * _data[0] + data[1] * _data[4] + data[2] * _data[8] + data[3] * _data[12];
		if (determinant == 0.0f) {
			identity();
			return *this;
		}
		determinant = 1.0f / determinant;
		for (auto i = 0; i < _data.size(); i++)
			_data[i] = _data[i] * determinant;
		data = _data;
		return *this;
	}

	/**
	 * Compute Euler angles (rotation around x, y, z axes)
	 * @returns Vector3 containing euler angles
	 */
	inline Vector3 computeEulerAngles() const {
		/*
		see https://github.com/erich666/GraphicsGems/tree/master/gemsiv/euler_angle

			This code repository predates the concept of Open Source, and predates most licenses along such lines.
			As such, the official license truly is:
			EULA: The Graphics Gems code is copyright-protected.
			In other words, you cannot claim the text of the code as your own and resell it.
			Using the code is permitted in any program, product, or library, non-commercial or commercial.
			Giving credit is not required, though is a nice gesture.
			The code comes as-is, and if there are any flaws or problems with any Gems code,
			nobody involved with Gems - authors, editors, publishers, or webmasters - are to be held responsible.
			Basically, don't be a jerk, and remember that anything free comes with no guarantee.
		*/
		// TODO: the next step might be a candidate for some optimizations
		// copy Matrix4x4 data
		auto _data = data;
		// normalize all 3 axes in Matrix4x4 coordinate system
		auto axisALength = Math::sqrt((_data[0] * _data[0]) + (_data[1] * _data[1]) + (_data[2] * _data[2]));
		_data[0]*= axisALength;
		_data[1]*= axisALength;
		_data[2]*= axisALength;
		auto axisBLength = Math::sqrt((_data[4] * _data[4]) + (_data[5] * _data[5]) + (_data[6] * _data[6]));
		_data[4]*= axisBLength;
		_data[5]*= axisBLength;
		_data[6]*= axisBLength;
		auto axisCLength = Math::sqrt((_data[8] * _data[8]) + (_data[9] * _data[9]) + (_data[10] * _data[10]));
		_data[8]*= axisCLength;
		_data[9]*= axisCLength;
		_data[10]*= axisCLength;
		// compute euler angles
		Vector3 euler;
		auto axis0 = 0;
		auto axis1 = 1;
		auto axis2 = 2;
		auto cy = static_cast<float>(Math::sqrt(_data[axis0 + 4 * axis0] * _data[axis0 + 4 * axis0] + _data[axis1 + 4 * axis0] * _data[axis1 + 4 * axis0]));
		if (cy > 16.0f * Math::EPSILON) {
			euler[0] = static_cast<float>((Math::atan2(_data[axis2 + 4 * axis1], _data[axis2 + 4 * axis2])));
			euler[1] = static_cast<float>((Math::atan2(-_data[axis2 + 4 * axis0], cy)));
			euler[2] = static_cast<float>((Math::atan2(_data[axis1 + 4 * axis0], _data[axis0 + 4 * axis0])));
		} else {
			euler[0] = static_cast<float>((Math::atan2(-_data[axis1 + 4 * axis2], _data[axis1 + 4 * axis1])));
			euler[1] = static_cast<float>((Math::atan2(-_data[axis2 + 4 * axis0], cy)));
			euler[2] = 0.0f;
		}
		euler.scale(static_cast<float>((180.0 / Math::PI)));
		return euler;
	}

	/**
	 * Interpolates between a and b by 0f<=t<=1f linearly
	 * @param a matrix a
	 * @param a matrix b
	 * @param t t
	 * @returns interpolated matrix
	 */
	inline static Matrix4x4 interpolateLinear(const Matrix4x4& a, const Matrix4x4& b, float t) {
		return Matrix4x4(
			(b.data[0] * t) + ((1.0f - t) * a.data[0]),
			(b.data[1] * t) + ((1.0f - t) * a.data[1]),
			(b.data[2] * t) + ((1.0f - t) * a.data[2]),
			(b.data[3] * t) + ((1.0f - t) * a.data[3]),
			(b.data[4] * t) + ((1.0f - t) * a.data[4]),
			(b.data[5] * t) + ((1.0f - t) * a.data[5]),
			(b.data[6] * t) + ((1.0f - t) * a.data[6]),
			(b.data[7] * t) + ((1.0f - t) * a.data[7]),
			(b.data[8] * t) + ((1.0f - t) * a.data[8]),
			(b.data[9] * t) + ((1.0f - t) * a.data[9]),
			(b.data[10] * t) + ((1.0f - t) * a.data[10]),
			(b.data[11] * t) + ((1.0f - t) * a.data[11]),
			(b.data[12] * t) + ((1.0f - t) * a.data[12]),
			(b.data[13] * t) + ((1.0f - t) * a.data[13]),
			(b.data[14] * t) + ((1.0f - t) * a.data[14]),
			(b.data[15] * t) + ((1.0f - t) * a.data[15])
		);
	}

	/**
	 * @returns matrix as array
	 */
	inline const array<float, 16>& getArray() const {
		return data;
	}

	/**
	 * Clones this matrix
	 * @returns cloned matrix
	 */
	inline Matrix4x4 clone() const {
		Matrix4x4 clonedMatrix(*this);
		return clonedMatrix;
	}

	/**
	 * Array access operator
	 * @param i index
	 * @returns matrix component
	 */
	inline float& operator[](int i) {
		return data[i];
	}

	/**
	 * Const array access operator
	 * @param i index
	 * @returns matrix component
	 */
	inline const float& operator[](int i) const {
		return data[i];
	}

	/**
	 * Operator * scalar
	 * @param scalar scalar
	 * @returns new matrix (this * scalar)
	 */
	inline Matrix4x4 operator *(const float scalar) const {
		auto r = this->clone().scale(scalar);
		return r;
	}

	/**
	 * Operator * matrix
	 * @param matrix matrix
	 * @returns new matrix (this * matrix)
	 */
	inline Matrix4x4 operator *(const Matrix4x4& matrix) const {
		auto r = this->clone().multiply(matrix);
		return r;
	}

	/**
	 * Operator * vector3
	 * @param vector3 vector3
	 * @returns new vector3 (this * vector3)
	 */
	inline Vector3 operator *(const Vector3& vector3) const {
		return this->multiply(vector3);
	}

	/**
	 * Operator * vector4
	 * @param vector4 vector4
	 * @returns new vector4 (this * vector4)
	 */
	inline Vector4 operator *(const Vector4& vector4) const {
		return this->multiply(vector4);
	}

	/*
	 * Operator *= matrix
	 * @param matrix matrix
	 * @returns this matrix
	 */
	inline Matrix4x4& operator *=(const Matrix4x4 matrix) {
		return this->multiply(matrix);
	}

	/**
	 * Equality comparison operator
	 * @param matrix Matrix4x4 to compare to
	 * @returns equality
	 */
	inline bool operator ==(const Matrix4x4& matrix) const {
		return this->equals(matrix);
	}

	/**
	 * Non equality comparison operator
	 * @param matrix Matrix4x4 to compare to
	 * @returns non equality
	 */
	inline bool operator !=(const Matrix4x4& matrix) const {
		return this->equals(matrix) == false;
	}

};
