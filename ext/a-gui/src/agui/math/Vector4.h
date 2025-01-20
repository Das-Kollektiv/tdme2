#pragma once

#include <array>

#include <agui/agui.h>
#include <agui/math/fwd-agui.h>
#include <agui/math/Vector3.h>
#include <agui/math/Math.h>
#include <agui/utilities/Float.h>

using std::array;

/**
 * Vector4 class representing vector4 mathematical structure and operations with x, y, z, w components
 * @author Andreas Drewke
 */
class agui::math::Vector4 final
{
	friend class Matrix4x4;

private:
	array<float, 4> data { 0.0f, 0.0f, 0.0f, 0.0f };

public:
	/**
	 * Public constructor
	 */
	inline Vector4() {
	}

	/**
	 * Public constructor
	 * @param x x component
	 * @param y y component
	 * @param z z component
	 * @param w w component
	 */
	inline Vector4(float x, float y, float z, float w) {
		data[0] = x;
		data[1] = y;
		data[2] = z;
		data[3] = w;
	}

	/**
	 * Public constructor
	 * @param vector4 vector4 as array
	 */
	inline Vector4(const array<float, 4>& vector4) {
		data = vector4;
	}

	/**
	 * Public constructor
	 * @param vector4 vector4
	 */
	inline Vector4(const Vector4& vector4) {
		data = vector4.data;
	}

	/**
	 * Public constructor
	 * @param vector3 vector3
	 * @param w w component
	 */
	inline Vector4(const Vector3& vector3, float w) {
		data[0] = vector3.data[0];
		data[1] = vector3.data[1];
		data[2] = vector3.data[2];
		data[3] = w;
	}

	/**
	 * Public constructor
	 * @param vector3 vector3 as array
	 * @param w w component
	 */
	inline Vector4(const array<float, 3>& vector3, float w) {
		data[0] = vector3[0];
		data[1] = vector3[1];
		data[2] = vector3[2];
		data[3] = w;
	}

	/**
	 * Sets this vector4 by its components
	 * @param x x component
	 * @param y y component
	 * @param z z component
	 * @param w w component
	 * @returns this vector4
	 */
	inline Vector4& set(float x, float y, float z, float w) {
		data[0] = x;
		data[1] = y;
		data[2] = z;
		data[3] = w;
		return *this;
	}

	/**
	 * Sets this vector4 by array
	 * @param vector4 vector4 as array
	 * @returns this vector4
	 */
	inline Vector4& set(const array<float, 4>& vector4) {
		data = vector4;
		return *this;
	}

	/**
	 * Sets this vector4 by given vector4
	 * @param vector4 vector4
	 * @returns this Vector4
	 */
	inline Vector4& set(const Vector4& vector4) {
		data = vector4.data;
		return *this;
	}

	/**
	 * Sets this vector4 by given vector3 and w
	 * @param vector3 vector3
	 * @param w w component
	 * @returns this vector4
	 */
	inline Vector4& set(const Vector3& vector3, float w) {
		data[0] = vector3.data[0];
		data[1] = vector3.data[1];
		data[2] = vector3.data[2];
		data[3] = w;
		return *this;
	}

	/**
	 * @returns x component
	 */
	inline float getX() const {
		return data[0];
	}

	/**
	 * Sets x component
	 * @param x x component
	 * @returns this vector4
	 */
	inline Vector4& setX(float x) {
		data[0] = x;
		return *this;
	}

	/**
	 * @returns y component
	 */
	inline float getY() const {
		return data[1];
	}

	/**
	 * Sets y component
	 * @param y y component
	 * @returns this vector4
	 */
	inline Vector4& setY(float y) {
		data[1] = y;
		return *this;
	}

	/**
	 * @returns z component
	 */
	inline float getZ() const {
		return data[2];
	}

	/**
	 * Sets z component
	 * @param z z component
	 * @returns this vector4
	 */
	inline Vector4& setZ(float z) {
		data[2] = z;
		return *this;
	}

	/**
	 * @returns w component
	 */
	inline float getW() const {
		return data[3];
	}

	/**
	 * Sets w component
	 * @param w w component
	 * @returns this vector4
	 */
	inline Vector4& setW(float w) {
		data[3] = w;
		return *this;
	}

	/**
	 * Adds a scalar
	 * @param scalar scalar
	 * @returns this vector4
	 */
	inline Vector4& add(float scalar) {
		data[0] += scalar;
		data[1] += scalar;
		data[2] += scalar;
		data[3] += scalar;
		return *this;
	}

	/**
	 * Adds a vector4
	 * @param vector4 vector4
	 * @returns this vector4
	 */
	inline Vector4& add(const Vector4& vector4) {
		data[0] += vector4.data[0];
		data[1] += vector4.data[1];
		data[2] += vector4.data[2];
		data[3] += vector4.data[3];
		return *this;
	}

	/**
	 * Subtracts a scalar
	 * @param scalar scalar
	 * @returns vector4
	 */
	inline Vector4& sub(float scalar) {
		data[0] -= scalar;
		data[1] -= scalar;
		data[2] -= scalar;
		data[3] -= scalar;
		return *this;
	}

	/**
	 * Subtracts a vector4
	 * @param vector4 vector4
	 * @returns vector4
	 */
	inline Vector4& sub(const Vector4& vector4) {
		data[0] -= vector4.data[0];
		data[1] -= vector4.data[1];
		data[2] -= vector4.data[2];
		data[3] -= vector4.data[3];
		return *this;
	}

	/**
	 * Scales this vector4
	 * @param scalar scalar
	 * @returns this vector4
	 */
	inline Vector4& scale(float scalar) {
		data[0] *= scalar;
		data[1] *= scalar;
		data[2] *= scalar;
		data[3] *= scalar;
		return *this;
	}

	/**
	 * Scales this vector4
	 * @param vector4 vector4
	 * @returns this vector4
	 */
	inline Vector4& scale(const Vector4& vector4) {
		data[0] *= vector4.data[0];
		data[1] *= vector4.data[1];
		data[2] *= vector4.data[2];
		data[3] *= vector4.data[3];
		return *this;
	}

	/**
	 * Compares this vector4 with given vector4
	 * @param vector4 vector4
	 * @param tolerance tolerance per vector4 component
	 * @returns equality
	 */
	inline bool equals(const Vector4& vector4, float tolerance = Math::EPSILON) const {
		return (this == &vector4) ||
			(
				Math::abs(data[0] - vector4.data[0]) < tolerance &&
				Math::abs(data[1] - vector4.data[1]) < tolerance &&
				Math::abs(data[2] - vector4.data[2]) < tolerance &&
				Math::abs(data[3] - vector4.data[3]) < tolerance
			);
	}

	/**
	 * Normalizes this vector4
	 * @returns this vector4
	 */
	inline Vector4& normalize() {
		auto length = computeLength();
		data[0] /= length;
		data[1] /= length;
		data[2] /= length;
		data[3] /= length;
		return *this;
	}

	/**
	 * Compute the dot product of a and b
	 * @param a vector4 a
	 * @param b vector4 b
	 * @returns dot product
	 */
	inline static float computeDotProduct(const Vector4& a, const Vector4& b) {
		return (a.data[0] * b.data[0]) + (a.data[1] * b.data[1]) + (a.data[2] * b.data[2]) + (a.data[3] * b.data[3]);
	}

	/**
	 * @returns the vectors length
	 */
	inline float computeLength() const {
		return Math::sqrt((data[0] * data[0]) + (data[1] * data[1]) + (data[2] * data[2]) + (data[3] * data[3]));
	}

	/**
	 * @returns the vectors length squared
	 */
	inline float computeLengthSquared() const {
		return (data[0] * data[0]) + (data[1] * data[1]) + (data[2] * data[2]) + (data[3] * data[3]);
	}

	/**
	 * Interpolates between a and b by 0f<=t<=1f linearly
	 * @param a vector4 a
	 * @param b vector4 b
	 * @param t t
	 * @returns interpolated vector4
	 */
	inline static Vector4 interpolateLinear(const Vector4& a, const Vector4& b, float t) {
		return Vector4(
			(b.data[0] * t) + ((1.0f - t) * a.data[0]),
			(b.data[1] * t) + ((1.0f - t) * a.data[1]),
			(b.data[2] * t) + ((1.0f - t) * a.data[2]),
			(b.data[3] * t) + ((1.0f - t) * a.data[3])
		);
	}

	/**
	 * @returns vector4 as array
	 */
	inline const array<float, 4>& getArray() const {
		return data;
	}

	/**
	 * Clones this vector4
	 * @returns cloned vector4
	 */
	inline Vector4 clone() const {
		return Vector4(*this);
	}

	/**
	 * Array access operator
	 * @param i index
	 * @returns vector4 component
	 */
	inline float& operator[](int i) {
		return data[i];
	}

	/**
	 * Const array access operator
	 * @param i index
	 * @returns vector4 component
	 */
	inline const float& operator[](int i) const {
		return data[i];
	}

	/**
	 * Operator + scalar
	 * @param scalar scalar
	 * @returns new vector4 (this + scalar)
	 */
	inline Vector4 operator +(const float scalar) const {
		auto r = this->clone().add(scalar);
		return r;
	}

	/**
	 * Operator + vector4
	 * @param vector4 vector4
	 * @returns new vector4 (this + vector4)
	 */
	inline Vector4 operator +(const Vector4& vector4) const {
		auto r = this->clone().add(vector4);
		return r;
	}

	/**
	 * Operator - scalar
	 * @param scalar scalar
	 * @returns new vector4 (this - scalar)
	 */
	inline Vector4 operator -(const float scalar) const {
		auto r = this->clone().sub(scalar);
		return r;
	}

	/**
	 * Operator - vector4
	 * @param vector4 vector4
	 * @returns new vector4 (this - vector4)
	 */
	inline Vector4 operator -(const Vector4& vector4) const {
		auto r = this->clone().sub(vector4);
		return r;
	}

	/**
	 * Operator * scalar
	 * @param scalar scalar
	 * @returns new vector4 (this * scalar)
	 */
	inline Vector4 operator *(const float scalar) const {
		auto r = this->clone().scale(scalar);
		return r;
	}

	/**
	 * Operator * vector4
	 * @param vector4 vector4
	 * @returns new vector4 (this * vector4)
	 */
	inline Vector4 operator *(const Vector4& vector4) const {
		auto r = this->clone().scale(vector4);
		return r;
	}

	/**
	 * Operator / scalar
	 * @param scalar scalar
	 * @returns new vector4 (this / scalar)
	 */
	inline Vector4 operator /(const float scalar) const {
		auto vInverted = Vector4(1.0f / scalar, 1.0f / scalar, 1.0f / scalar, 1.0f / scalar);
		auto r = this->clone().scale(vInverted);
		return r;
	}

	/**
	 * Operator / vector4
	 * @param vector4 vector4
	 * @returns new vector4 (this / vector4)
	 */
	inline Vector4 operator /(const Vector4& vector4) const {
		auto vInverted = Vector4(1.0f / vector4[0], 1.0f / vector4[1], 1.0f / vector4[2], 1.0f / vector4[3]);
		auto r = this->clone().scale(vInverted);
		return r;
	}

	/**
	 * Operator += scalar
	 * @param scalar scalar
	 * @returns this vector4
	 */
	inline Vector4& operator +=(const float scalar) {
		return this->add(scalar);
	}

	/**
	 * Operator += vector4
	 * @param vector4 vector4
	 * @returns this vector4
	 */
	inline Vector4& operator +=(const Vector4& vector4) {
		return this->add(vector4);
	}

	/**
	 * Operator -= scalar
	 * @param scalar scalar
	 * @returns this vector4
	 */
	inline Vector4& operator -=(const float scalar) {
		return this->sub(scalar);
	}

	/**
	 * Operator -= vector4
	 * @param vector4 vector4
	 * @returns this vector4
	 */
	inline Vector4& operator -=(const Vector4& vector4) {
		return this->sub(vector4);
	}

	/**
	 * Operator *= scalar
	 * @param scalar scalar
	 * @returns this vector4
	 */
	inline Vector4& operator *=(const float scalar) {
		return this->scale(scalar);
	}

	/**
	 * Operator *= vector4
	 * @param vector4 vector4
	 * @returns this vector4
	 */
	inline Vector4& operator *=(const Vector4& vector4) {
		return this->scale(vector4);
	}

	/**
	 * Operator /= scalar
	 * @param scalar scalar
	 * @returns this vector4
	 */
	inline Vector4& operator /=(const float scalar) {
		auto vInverted = Vector4(1.0f / scalar, 1.0f / scalar, 1.0f / scalar, 1.0f / scalar);
		return this->scale(vInverted);
	}

	/**
	 * Operator /= vector4
	 * @param vector4 vector4
	 * @returns this vector4
	 */
	inline Vector4& operator /=(const Vector4& vector4) {
		auto vInverted = Vector4(1.0f / vector4[0], 1.0f / vector4[1], 1.0f / vector4[2], 1.0f / vector4[3]);
		return this->scale(vInverted);
	}

	/**
	 * Equality comparison operator
	 * @param vector4 vector4
	 * @returns equality
	 */
	inline bool operator ==(const Vector4& vector4) const {
		return this->equals(vector4);
	}

	/**
	 * Non equality comparison operator
	 * @param vector4 vector4
	 * @returns non equality
	 */
	inline bool operator !=(const Vector4& vector4) const {
		return this->equals(vector4) == false;
	}

};
