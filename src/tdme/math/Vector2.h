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
 * Vector2 class representing vector2 mathematical structure and operations with x, y components
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
	 * @param x x component
	 * @param y y component
	 */
	inline Vector2(float x, float y) {
		data[0] = x;
		data[1] = y;
	}

	/**
	 * Public constructor
	 * @param vector2 vector2 as array
	 */
	inline Vector2(const array<float, 2>& vector2) {
		data = vector2;
	}

	/**
	 * Public constructor
	 * @param vector2 vector2
	 */
	inline Vector2(const Vector2& vector2) {
		data = vector2.data;
	}

	/**
	 * Sets this vector2 by its components
	 * @param x x component
	 * @param y y component
	 * @return this vector2
	 */
	inline Vector2& set(float x, float y) {
		data[0] = x;
		data[1] = y;
		return *this;
	}

	/**
	 * Sets this vector2 by array
	 * @param vector2 vector2 as array
	 * @return this vector2
	 */
	inline Vector2& set(const array<float, 2>& vector2) {
		data = vector2;
		return *this;
	}

	/**
	 * Sets this vector2 by given vector2
	 * @param vector2 vector2
	 * @return this vector2
	 */
	inline Vector2& set(const Vector2& vector2) {
		data = vector2.data;
		return *this;
	}

	/**
	 * @return x component
	 */
	inline float getX() const {
		return data[0];
	}

	/**
	 * Sets x component
	 * @param x x component
	 * @return this vector2
	 */
	inline Vector2& setX(float x) {
		data[0] = x;
		return *this;
	}

	/**
	 * @return y component
	 */
	inline float getY() const {
		return data[1];
	}

	/**
	 * Sets y component
	 * @param y y component
	 * @return this vector2
	 */
	inline Vector2& setY(float y) {
		data[1] = y;
		return *this;
	}

	/**
	 * Adds a scalar
	 * @param scalar scalar
	 * @return this vector2
	 */
	inline Vector2& add(float scalar) {
		data[0] += scalar;
		data[1] += scalar;
		return *this;
	}

	/**
	 * Adds a vector2
	 * @param vector2 vector2
	 * @return this vector2
	 */
	inline Vector2& add(const Vector2& vector2) {
		data[0] += vector2.data[0];
		data[1] += vector2.data[1];
		return *this;
	}

	/**
	 * Subtracts a scalar
	 * @param scalar scalar
	 * @return this vector2
	 */
	inline Vector2& sub(float scalar) {
		data[0] -= scalar;
		data[1] -= scalar;
		return *this;
	}

	/**
	 * Subtracts a vector2
	 * @param vector2 vector2
	 * @return this vector2
	 */
	inline Vector2& sub(const Vector2& vector2) {
		data[0] -= vector2.data[0];
		data[1] -= vector2.data[1];
		return *this;
	}

	/**
	 * Scales by scalar
	 * @param scalar scalar
	 * @return this vector2
	 */
	inline Vector2& scale(const float scalar) {
		data[0] *= scalar;
		data[1] *= scalar;
		return *this;
	}

	/**
	 * Scales by vector2
	 * @param scale scale vector2
	 * @return this vector2
	 */
	inline Vector2& scale(const Vector2& scale) {
		data[0] *= scale.data[0];
		data[1] *= scale.data[1];
		return *this;
	}

	/**
	 * Compares this vector2 with given vector2
	 * @param vector2 vector2
	 * @param tolerance tolerance per vector2 component
	 * @return equality
	 */
	inline bool equals(const Vector2& vector2, float tolerance = Math::EPSILON) const {
		return (this == &vector2) ||
			(
				Math::abs(data[0] - vector2.data[0]) < tolerance &&
				Math::abs(data[1] - vector2.data[1]) < tolerance
			);
	}

	/**
	 * Normalizes this vector2
	 * @return this vector2
	 */
	inline Vector2& normalize() {
		auto length = computeLength();
		data[0] /= length;
		data[1] /= length;
		return *this;
	}

	/**
	 * Computes the dot product of a and b
	 * @param a vector2 a
	 * @param b vector2 b
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
	 * Interpolates between a and b by 0f<=t<=1f linearly
	 * @param a vector2 a
	 * @param b vector2 b
	 * @param t t
	 * @return interpolated vector2
	 */
	inline static Vector2 interpolateLinear(const Vector2& a, const Vector2& b, float t) {
		return Vector2(
			(b.data[0] * t) + ((1.0f - t) * a.data[0]),
			(b.data[1] * t) + ((1.0f - t) * a.data[1])
		);
	}

	/**
	 * @return vector2 as array
	 */
	inline const array<float, 2>& getArray() const {
		return data;
	}

	/**
	 * Clones this vector2
	 * @return cloned vector2
	 */
	inline Vector2 clone() const {
		return Vector2(*this);
	}

	/**
	 * Array access operator
	 * @param i index
	 * @return vector2 component
	 */
	inline float& operator[](int i) {
		return data[i];
	}

	/**
	 * Const array access operator
	 * @param i index
	 * @return vector2 component
	 */
	inline const float& operator[](int i) const {
		return data[i];
	}

	/**
	 * Operator + scalar
	 * @param scalar scalar
	 * @return new vector2 (this + scalar)
	 */
	inline Vector2 operator +(const float scalar) const {
		auto r = this->clone().add(scalar);
		return r;
	}

	/**
	 * Operator + vector2
	 * @param vector2 vector2
	 * @return new vector2 (this + vector2)
	 */
	inline Vector2 operator +(const Vector2& vector2) const {
		auto r = this->clone().add(vector2);
		return r;
	}

	/**
	 * Operator - scalar
	 * @param scalar scalar
	 * @return new vector2 (this - scalar)
	 */
	inline Vector2 operator -(const float scalar) const {
		auto r = this->clone().sub(scalar);
		return r;
	}

	/**
	 * Operator - vector2
	 * @param vector2 vector2
	 * @return new vector2 (this - vector2)
	 */
	inline Vector2 operator -(const Vector2& vector2) const {
		auto r = this->clone().sub(vector2);
		return r;
	}

	/**
	 * Operator * scalar
	 * @param scalar scalar
	 * @return new vector2 (this * scalar)
	 */
	inline Vector2 operator *(const float scalar) const {
		auto r = this->clone().scale(scalar);
		return r;
	}

	/**
	 * Operator * vector2
	 * @param vector2 vector2
	 * @return new vector2 (this * vector2)
	 */
	inline Vector2 operator *(const Vector2& vector2) const {
		auto r = this->clone().scale(vector2);
		return r;
	}

	/**
	 * Operator / scalar
	 * @param scalar scalar
	 * @return new vector2 (this / scalar)
	 */
	inline Vector2 operator /(const float scalar) const {
		auto r = this->clone().scale(1.0f / scalar);
		return r;
	}

	/**
	 * Operator / vector2
	 * @param vector2 vector2
	 * @return new vector2 (this / vector2)
	 */
	inline Vector2 operator /(const Vector2& vector2) const {
		auto vInverted = Vector2(1.0f / vector2[0], 1.0f / vector2[1]);
		auto r = this->clone().scale(vInverted);
		return r;
	}

	/**
	 * Operator += scalar
	 * @param scalar scalar
	 * @return this vector2
	 */
	inline Vector2& operator +=(const float scalar) {
		return this->add(scalar);
	}

	/**
	 * Operator += vector2
	 * @param vector2 vector2
	 * @return this vector2
	 */
	inline Vector2& operator +=(const Vector2& vector2) {
		return this->add(vector2);
	}

	/**
	 * Operator -= scalar
	 * @param scalar scalar
	 * @return this vector2
	 */
	inline Vector2& operator -=(const float scalar) {
		return this->sub(scalar);
	}

	/**
	 * Operator -= vector2
	 * @param vector2 vector2
	 * @return this vector2
	 */
	inline Vector2& operator -=(const Vector2& vector2) {
		return this->sub(vector2);
	}

	/**
	 * Operator *= scalar
	 * @param scalar scalar
	 * @return this vector2
	 */
	inline Vector2& operator *=(const float scalar) {
		return this->scale(scalar);
	}

	/**
	 * Operator *= vector2
	 * @param vector2 vector2
	 * @return this vector2
	 */
	inline Vector2& operator *=(const Vector2& vector2) {
		return this->scale(vector2);
	}

	/**
	 * Operator /= scalar
	 * @param scalar scalar
	 * @return this vector2
	 */
	inline Vector2& operator /=(const float scalar) {
		auto vInverted = Vector2(1.0f / scalar, 1.0f / scalar);
		return this->scale(vInverted);
	}

	/**
	 * Operator /= vector2
	 * @param vector2 vector2
	 * @return this vector2
	 */
	inline Vector2& operator /=(const Vector2& vector2) {
		auto vInverted = Vector2(1.0f / vector2[0], 1.0f / vector2[1]);
		return this->scale(vInverted);
	}

	/**
	 * Equality comparison operator
	 * @param vector2 vector2
	 * @return equality
	 */
	inline bool operator ==(const Vector2& vector2) const {
		return this->equals(vector2);
	}

	/**
	 * Non equality comparison operator
	 * @param vector2 vector2
	 * @return non equality
	 */
	inline bool operator !=(const Vector2& vector2) const {
		return this->equals(vector2) == false;
	}

};
