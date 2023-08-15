#pragma once

#include <array>

#include <tdme/tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Math.h>
#include <tdme/utilities/Float.h>

using std::array;

using tdme::math::Math;
using tdme::utilities::Float;

/**
 * 2D vector class
 * @author Andreas Drewke
 */
class tdme::math::Vector2 final
{
	friend class Matrix2D3x3;

private:
	array<float, 2> data { 0.0f, 0.0f };

public:
	/**
	 * Public constructor
	 */
	inline Vector2() {
	}

	/**
	 * Public constructor
	 * @param x x
	 * @param y y
	 */
	inline Vector2(float x, float y) {
		data[0] = x;
		data[1] = y;
	}

	/**
	 * Public constructor
	 * @param vector vector as array
	 */
	inline Vector2(const array<float, 2>& vector) {
		data = vector;
	}

	/**
	 * Public constructor
	 * @param vector vector
	 */
	inline Vector2(const Vector2& vector) {
		data = vector.data;
	}

	/**
	 * Sets up this vector by it components
	 * @param x x
	 * @param y y
	 * @return this vector
	 */
	inline Vector2& set(float x, float y) {
		data[0] = x;
		data[1] = y;
		return *this;
	}

	/**
	 * Sets up this vector by array
	 * @param vector vector as array
	 * @return this vector
	 */
	inline Vector2& set(const array<float, 2>& vector) {
		data = vector;
		return *this;
	}

	/**
	 * Sets up this vector by given vector
	 * @param vector vector
	 * @return this vector
	 */
	inline Vector2& set(const Vector2& vector) {
		data = vector.data;
		return *this;
	}

	/**
	 * @return x
	 */
	inline float getX() const {
		return data[0];
	}

	/**
	 * Sets x
	 * @param x x
	 * @return this vector
	 */
	inline Vector2& setX(float x) {
		data[0] = x;
		return *this;
	}

	/**
	 * @return y
	 */
	inline float getY() const {
		return data[1];
	}

	/**
	 * Sets y
	 * @param y y
	 * @return this vector
	 */
	inline Vector2& setY(float y) {
		data[1] = y;
		return *this;
	}

	/**
	 * Adds a scalar
	 * @param scalar scalar
	 * @return this vector
	 */
	inline Vector2& add(float scalar) {
		data[0] += scalar;
		data[1] += scalar;
		return *this;
	}

	/**
	 * Adds a vector
	 * @param vector vector
	 * @return this vector
	 */
	inline Vector2& add(const Vector2& vector) {
		data[0] += vector.data[0];
		data[1] += vector.data[1];
		return *this;
	}

	/**
	 * Subtracts a scalar
	 * @param scalar scalar
	 * @return this vector
	 */
	inline Vector2& sub(float scalar) {
		data[0] -= scalar;
		data[1] -= scalar;
		return *this;
	}

	/**
	 * Subtracts a vector
	 * @param vector vector
	 * @return this vector
	 */
	inline Vector2& sub(const Vector2& vector) {
		data[0] -= vector.data[0];
		data[1] -= vector.data[1];
		return *this;
	}

	/**
	 * Scales by scalar
	 * @param scalar scalar
	 * @return this vector
	 */
	inline Vector2& scale(const float scalar) {
		data[0] *= scalar;
		data[1] *= scalar;
		return *this;
	}

	/**
	 * Scales by vector
	 * @param scale scale vector
	 * @return this vector
	 */
	inline Vector2& scale(const Vector2& scale) {
		data[0] *= scale.data[0];
		data[1] *= scale.data[1];
		return *this;
	}

	/**
	 * Compares this vector with given vector
	 * @param vector vector
	 * @param tolerance tolerance per vector component
	 * @return equality
	 */
	inline bool equals(const Vector2& vector, float tolerance = Math::EPSILON) const {
		return (this == &vector) ||
			(
				Math::abs(data[0] - vector.data[0]) < tolerance &&
				Math::abs(data[1] - vector.data[1]) < tolerance
			);
	}

	/**
	 * Normalizes this vector
	 * @return this vector
	 */
	inline Vector2& normalize() {
		auto length = computeLength();
		data[0] /= length;
		data[1] /= length;
		return *this;
	}

	/**
	 * Computes the dot product of vector a and b
	 * @param a vector a
	 * @param b vector b
	 * @return dot product
	 */
	inline static float computeDotProduct(const Vector2& a, const Vector2& b) {
		return (a.data[0] * b.data[0]) + (a.data[1] * b.data[1]);
	}

	/**
	 * @return the vectors length
	 */
	inline float computeLength() const {
		return Math::sqrt((data[0] * data[0]) + (data[1] * data[1]));
	}

	/**
	 * @return the vectors length squared
	 */
	inline float computeLengthSquared() const {
		return (data[0] * data[0]) + (data[1] * data[1]);
	}

	/**
	 * Interpolates between vector v1 and v2 by 0f<=t<=1f linearly
	 * @param a vector a
	 * @param b vector b
	 * @param t t
	 * @return interpolated vector
	 */
	inline static Vector2 interpolateLinear(const Vector2& a, const Vector2& b, float t) {
		return Vector2(
			(b.data[0] * t) + ((1.0f - t) * a.data[0]),
			(b.data[1] * t) + ((1.0f - t) * a.data[1])
		);
	}

	/**
	 * @return vector as array
	 */
	inline const array<float, 2>& getArray() const {
		return data;
	}

	/**
	 * Clones this vector
	 * @return cloned vector
	 */
	inline Vector2 clone() const {
		return Vector2(*this);
	}

	/**
	 * Array access operator
	 * @param i index
	 * @return vector component
	 */
	inline float& operator[](int i) {
		return data[i];
	}

	/**
	 * Const array access operator
	 * @param i index
	 * @return vector component
	 */
	inline const float& operator[](int i) const {
		return data[i];
	}

	/**
	 * Operator + scalar
	 * @param scalar scalar
	 * @return new vector (this + scalar)
	 */
	inline Vector2 operator +(const float scalar) const {
		auto r = this->clone().add(scalar);
		return r;
	}

	/**
	 * Operator + vector
	 * @param vector vector
	 * @return new vector (this + vector)
	 */
	inline Vector2 operator +(const Vector2& vector) const {
		auto r = this->clone().add(vector);
		return r;
	}

	/**
	 * Operator - scalar
	 * @param scalar scalar
	 * @return new vector (this - scalar)
	 */
	inline Vector2 operator -(const float scalar) const {
		auto r = this->clone().sub(scalar);
		return r;
	}

	/**
	 * Operator - vector
	 * @param vector vector
	 * @return new vector (this - vector)
	 */
	inline Vector2 operator -(const Vector2& vector) const {
		auto r = this->clone().sub(vector);
		return r;
	}

	/**
	 * Operator * scalar
	 * @param scalar scalar
	 * @return new vector (this * scalar)
	 */
	inline Vector2 operator *(const float scalar) const {
		auto r = this->clone().scale(scalar);
		return r;
	}

	/**
	 * Operator * vector
	 * @param vector vector
	 * @return new vector (this * vector)
	 */
	inline Vector2 operator *(const Vector2& vector) const {
		auto r = this->clone().scale(vector);
		return r;
	}

	/**
	 * Operator / scalar
	 * @param scalar scalar
	 * @return new vector (this / scalar)
	 */
	inline Vector2 operator /(const float scalar) const {
		auto r = this->clone().scale(1.0f / scalar);
		return r;
	}

	/**
	 * Operator / vector
	 * @param vector vector
	 * @return new vector (this / vector)
	 */
	inline Vector2 operator /(const Vector2& vector) const {
		auto vInverted = Vector2(1.0f / vector[0], 1.0f / vector[1]);
		auto r = this->clone().scale(vInverted);
		return r;
	}

	/**
	 * Operator += scalar
	 * @param scalar scalar
	 * @return this vector
	 */
	inline Vector2& operator +=(const float scalar) {
		return this->add(scalar);
	}

	/**
	 * Operator += vector
	 * @param vector vector
	 * @return this vector
	 */
	inline Vector2& operator +=(const Vector2& vector) {
		return this->add(vector);
	}

	/**
	 * Operator -= scalar
	 * @param scalar scalar
	 * @return this vector
	 */
	inline Vector2& operator -=(const float scalar) {
		return this->sub(scalar);
	}

	/**
	 * Operator -= vector
	 * @param vector vector
	 * @return this vector
	 */
	inline Vector2& operator -=(const Vector2& vector) {
		return this->sub(vector);
	}

	/**
	 * Operator *= scalar
	 * @param scalar scalar
	 * @return this vector
	 */
	inline Vector2& operator *=(const float scalar) {
		return this->scale(scalar);
	}

	/**
	 * Operator *= vector
	 * @param vector vector
	 * @return this vector
	 */
	inline Vector2& operator *=(const Vector2& vector) {
		return this->scale(vector);
	}

	/**
	 * Operator /= scalar
	 * @param scalar scalar
	 * @return this vector
	 */
	inline Vector2& operator /=(const float scalar) {
		auto vInverted = Vector2(1.0f / scalar, 1.0f / scalar);
		return this->scale(vInverted);
	}

	/**
	 * Operator /= vector
	 * @param vector vector
	 * @return this vector
	 */
	inline Vector2& operator /=(const Vector2& vector) {
		auto vInverted = Vector2(1.0f / vector[0], 1.0f / vector[1]);
		return this->scale(vInverted);
	}

	/**
	 * Equality comparison operator
	 * @param vector vector
	 * @return equality
	 */
	inline bool operator ==(const Vector2& vector) const {
		return this->equals(vector);
	}

	/**
	 * Non equality comparison operator
	 * @param vector vector
	 * @return non equality
	 */
	inline bool operator !=(const Vector2& vector) const {
		return this->equals(vector) == false;
	}

};
