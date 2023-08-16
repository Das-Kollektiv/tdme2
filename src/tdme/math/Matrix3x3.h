#pragma once

#include <array>

#include <tdme/tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector2.h>

using std::array;

using tdme::math::Math;
using tdme::math::Vector2;

/**
 * Matrix3x3 class representing matrix3x3 mathematical structure and operations for 2d space
 * @author Andreas Drewke
 */
class tdme::math::Matrix3x3 final
{
	// see: http://learnwebgl.brown37.net/10_surface_properties/texture_mapping_transforms.html
private:
	array<float, 9> data {
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f
	};

public:
	/**
	 * Public constructor
	 */
	inline Matrix3x3() {
	}

	/**
	 * Public constructor
	 * @param r0c0 row 0, column 0
	 * @param r0c1 row 0, column 1
	 * @param r0c2 row 0, column 2
	 * @param r1c0 row 1, column 0
	 * @param r1c1 row 1, column 1
	 * @param r1c2 row 1, column 2
	 * @param r2c0 row 2, column 0
	 * @param r2c1 row 2, column 1
	 * @param r2c2 row 2, column 2
	 */
	inline Matrix3x3(
		float r0c0, float r0c1, float r0c2,
		float r1c0, float r1c1, float r1c2,
		float r2c0, float r2c1, float r2c2) {
		set(
			r0c0, r0c1, r0c2,
			r1c0, r1c1, r1c2,
			r2c0, r2c1, r2c2
		);
	}

	/**
	 * Public constructor
	 * @param matrix matrix as array
	 */
	inline Matrix3x3(const array<float, 9>& matrix) {
		data = matrix;
	}

	/**
	 * Public constructor
	 * @param matrix matrix
	 */
	inline Matrix3x3(const Matrix3x3& matrix) {
		data = matrix.data;
	}

	/**
	 * Sets this matrix by its components
	 * @param r0c0 row 0, column 0
	 * @param r0c1 row 0, column 1
	 * @param r0c2 row 0, column 2
	 * @param r1c0 row 1, column 0
	 * @param r1c1 row 1, column 1
	 * @param r1c2 row 1, column 2
	 * @param r2c0 row 2, column 0
	 * @param r2c1 row 2, column 1
	 * @param r2c2 row 2, column 2
	 * @return this matrix
	 */
	inline Matrix3x3& set(
		float r0c0, float r0c1, float r0c2,
		float r1c0, float r1c1, float r1c2,
		float r2c0, float r2c1, float r2c2) {
		data[0] = r0c0;
		data[1] = r0c1;
		data[2] = r0c2;
		data[3] = r1c0;
		data[4] = r1c1;
		data[5] = r1c2;
		data[6] = r2c0;
		data[7] = r2c1;
		data[8] = r2c2;
		return *this;
	}

	/**
	 * Sets this matrix by array
	 * @param matrix matrix as array
	 * @return this matrix
	 */
	inline Matrix3x3& set(const array<float, 9>& matrix) {
		data = matrix;
		return *this;
	}

	/**
	 * Sets this matrix by given matrix
	 * @param matrix matrix
	 * @return this matrix
	 */
	inline Matrix3x3& set(const Matrix3x3& matrix) {
		data = matrix.data;
		return *this;
	}

	/**
	 * Creates identity matrix
	 * @return this matrix
	 */
	inline Matrix3x3& identity() {
		data[0] = 1.0f;
		data[1] = 0.0f;
		data[2] = 0.0f;
		data[3] = 0.0f;
		data[4] = 1.0f;
		data[5] = 0.0f;
		data[6] = 0.0f;
		data[7] = 0.0f;
		data[8] = 1.0f;
		return *this;
	}

	/**
	 * Scales by scalar
	 * @param scalar scalar
	 * @returns this matrix
	 */
	inline Matrix3x3& scale(float scalar) {
		data[0] *= scalar;
		data[1] *= scalar;
		data[2] *= scalar;
		data[3] *= scalar;
		data[4] *= scalar;
		data[5] *= scalar;
		return *this;
	}

	/**
	 * Scales by vector2
	 * @param vector2 vector2
	 * @return this matrix
	 */
	inline Matrix3x3& scale(const Vector2& vector2) {
		data[0] *= vector2.data[0];
		data[1] *= vector2.data[0];
		data[2] *= vector2.data[0];
		data[3] *= vector2.data[1];
		data[4] *= vector2.data[1];
		data[5] *= vector2.data[1];
		return *this;
	}

	/**
	 * Multiplies this matrix with given matrix
	 * @param matrix matrix
	 * @return this matrix
	 */
	inline Matrix3x3& multiply(const Matrix3x3& matrix) {
		array<float, 9> _data;
		_data[0] = data[0] * matrix.data[0]  + data[3] * matrix.data[1]  + data[6] * matrix.data[2];
		_data[1] = data[1] * matrix.data[0]  + data[4] * matrix.data[1]  + data[7] * matrix.data[2];
		_data[2] = data[2] * matrix.data[0]  + data[5] * matrix.data[1]  + data[8] * matrix.data[2];
		_data[3] = data[0] * matrix.data[3]  + data[3] * matrix.data[4]  + data[6] * matrix.data[5];
		_data[4] = data[1] * matrix.data[3]  + data[4] * matrix.data[4]  + data[7] * matrix.data[5];
		_data[5] = data[2] * matrix.data[3]  + data[5] * matrix.data[4]  + data[8] * matrix.data[5];
		_data[6] = data[0] * matrix.data[6]  + data[3] * matrix.data[7]  + data[6] * matrix.data[8];
		_data[7] = data[1] * matrix.data[6]  + data[4] * matrix.data[7]  + data[7] * matrix.data[8];
		_data[8] = data[2] * matrix.data[6]  + data[5] * matrix.data[7]  + data[8] * matrix.data[8];
		data = _data;
		return *this;
	}

	/**
	 * Multiplies this matrix with vector2
	 * @param vector2 vector2
	 * @return vector2
	 */
	inline Vector2 multiply(const Vector2& vector2) const {
		return Vector2(
			data[0] * vector2.data[0] + data[3] * vector2.data[1] + data[6],
			data[1] * vector2.data[0] + data[4] * vector2.data[1] + data[7]
		);
	}

	/**
	 * Compares this matrix with given matrix
	 * @param matrix matrix
	 * @return equality
	 */
	inline bool equals(const Matrix3x3& matrix) const {
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
				Math::abs(data[8] - matrix.data[8]) < Math::EPSILON
			);
	}

	/**
	 * Get coordinate system axes
	 * @param xAxis x axis
	 * @param yAxis y axis
	 */
	inline void getAxes(Vector2& xAxis, Vector2& yAxis) const {
		xAxis.set(data[0], data[1]);
		yAxis.set(data[3], data[4]);
	}

	/**
	 * Set coordinate system axes
	 * @param xAxis x axis
	 * @param yAxis y axis
	 * @return this matrix
	 */
	inline Matrix3x3& setAxes(const Vector2& xAxis, const Vector2& yAxis) {
		data[0] = xAxis.data[0];
		data[1] = xAxis.data[1];
		data[2] = 0.0f;
		data[3] = yAxis.data[0];
		data[4] = yAxis.data[1];
		data[5] = 0.0f;
		return *this;
	}

	/**
	 * Set coordinate system axis by rotation
	 * @param angle angle
	 * @return this matrix
	 */
	inline Matrix3x3& setAxes(float angle) {
		auto r = angle * 3.1415927f / 180.0f;
		float c = Math::cos(r);
		float s = Math::sin(r);
		data[0] = c;
		data[1] = s;
		data[2] = 0.0f;
		data[3] = -s;
		data[4] = c;
		data[5] = 0.0f;
		return *this;
	}

	/**
	 * Get translation
	 * @param vector2 vector2
	 */
	inline void getTranslation(Vector2& vector2) const {
		vector2.set(data[6], data[7]);
	}

	/**
	 * Sets translation in matrix
	 * @param vector2 vector2
	 * @return this matrix
	 */
	inline Matrix3x3& setTranslation(const Vector2& vector2) {
		data[6] = vector2.data[0];
		data[7] = vector2.data[1];
		return *this;
	}

	/**
	 * Creates rotation matrix that rotates around texture center by given angle
	 * @param angle angle
	 * @return new rotation matrix
	 */
	static inline Matrix3x3 rotateAroundTextureCenter(float angle) {
		return rotateAroundPoint(Vector2(0.5f, 0.5f), angle);
	}

	/**
	 * Creates rotation matrix that rotates around given point by given angle
	 * @param point point
	 * @param angle angle
	 * @return new rotation matrix
	 */
	static inline Matrix3x3 rotateAroundPoint(const Vector2& point, float angle) {
		Matrix3x3 matrix;
		matrix.identity();
		matrix.setTranslation(point);
		matrix.multiply((Matrix3x3()).identity().setAxes(-angle));
		matrix.multiply((Matrix3x3()).identity().setTranslation(point.clone().scale(-1.0f)));
		return matrix;
	}

	/**
	 * Interpolates between matrix 1 and matrix 2 by 0f<=t<=1f linearly
	 * @param a matrix a
	 * @param b matrix b
	 * @param t t
	 * @return interpolated matrix
	 */
	inline static Matrix3x3 interpolateLinear(const Matrix3x3& a, const Matrix3x3& b, float t) {
		return Matrix3x3(
			(b.data[0] * t) + ((1.0f - t) * a.data[0]),
			(b.data[1] * t) + ((1.0f - t) * a.data[1]),
			(b.data[2] * t) + ((1.0f - t) * a.data[2]),
			(b.data[3] * t) + ((1.0f - t) * a.data[3]),
			(b.data[4] * t) + ((1.0f - t) * a.data[4]),
			(b.data[5] * t) + ((1.0f - t) * a.data[5]),
			(b.data[6] * t) + ((1.0f - t) * a.data[6]),
			(b.data[7] * t) + ((1.0f - t) * a.data[7]),
			(b.data[8] * t) + ((1.0f - t) * a.data[8])
		);
	}

	/**
	 * @return matrix as array
	 */
	inline const array<float, 9>& getArray() const {
		return data;
	}

	/**
	 * Clones this matrix
	 * @return cloned matrix
	 */
	inline Matrix3x3 clone() const {
		Matrix3x3 clonedMatrix(*this);
		return clonedMatrix;
	}

	/**
	 * Array access operator
	 * @param i index
	 * @return matrix3x3 component
	 */
	inline float& operator[](int i) {
		return data[i];
	}

	/**
	 * Const array access operator
	 * @param i index
	 * @return matrix3x3 component
	 */
	inline const float& operator[](int i) const {
		return data[i];
	}

	/**
	 * Operator * scalar
	 * @param scalar scalar
	 * @return new matrix (this * scalar)
	 */
	inline Matrix3x3 operator *(const float scalar) const {
		auto r = this->clone().scale(scalar);
		return r;
	}

	/**
	 * Operator * matrix
	 * @param matrix matrix
	 * @return new matrix (this * matrix)
	 */
	inline Matrix3x3 operator *(const Matrix3x3& matrix) const {
		auto r = this->clone().multiply(matrix);
		return r;
	}

	/*
	 * Operator * vector2
	 * @param vector2 vector2
	 * @return new vector (this * vector2)
	 */
	inline Vector2 operator *(const Vector2& vector2) const {
		return this->multiply(vector2);
	}

	/**
	 * Operator *= matrix
	 * @param matrix matrix
	 * @return new matrix (this * matrix)
	 */
	inline Matrix3x3& operator *=(const Matrix3x3& matrix) {
		return this->multiply(matrix);
	}

	/**
	 * Equality comparison operator
	 * @param matrix matrix to compare to
	 * @return equality
	 */

	inline bool operator ==(const Matrix3x3& matrix) const {
		return this->equals(matrix);
	}

	/**
	 * Non equality comparison operator
	 * @param matrix matrix to compare to
	 * @return non equality
	 */

	inline bool operator !=(const Matrix3x3& matrix) const {
		return this->equals(matrix) == false;
	}

};
