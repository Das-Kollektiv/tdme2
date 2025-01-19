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
 * Vector3 class representing vector3 mathematical structure and operations with x, y, z components
 * @author andreas.drewke
 */
class tdme::math::Vector3 final
{
	friend class Matrix4x4;
	friend class Quaternion;
	friend class Vector4;

private:
	array<float, 3> data { 0.0f, 0.0f, 0.0f };

public:
	/**
	 * Public constructor
	 */
	inline Vector3() {
	}

	/**
	 * Public constructor
	 * @param x x component
	 * @param y y component
	 * @param z z component
	 */
	inline Vector3(float x, float y, float z) {
		data[0] = x;
		data[1] = y;
		data[2] = z;
	}

	/**
	 * Public constructor
	 * @param vector3 vector3 as array
	 */
	inline Vector3(const array<float,3>& vector3) {
		data = vector3;
	}

	/**
	 * Public constructor
	 * @param vector3 vector3
	 */
	inline Vector3(const Vector3& vector3) {
		data = vector3.data;
	}

	/**
	 * Sets this vector3 by its components
	 * @param x x component
	 * @param y y component
	 * @param z z component
	 * @returns this vector3
	 */
	inline Vector3& set(float x, float y, float z) {
		data[0] = x;
		data[1] = y;
		data[2] = z;
		return *this;
	}

	/**
	 * Sets this vector3 by array
	 * @param vector3 vector3 as array
	 * @returns this vector3
	 */
	inline Vector3& set(const array<float, 3>& vector3) {
		data = vector3;
		return *this;
	}

	/**
	 * Sets this vector3 by given vector3
	 * @param vector3 vector3
	 * @returns this vector3
	 */
	inline Vector3& set(const Vector3& vector3) {
		data = vector3.data;
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
	 * @returns this vector3
	 */
	inline Vector3& setX(float x) {
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
	 * @returns this vector3
	 */
	inline Vector3& setY(float y) {
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
	 * @returns this vector3
	 */
	inline Vector3& setZ(float z) {
		data[2] = z;
		return *this;
	}

	/**
	 * Adds a scalar
	 * @param scalar scalar
	 * @returns this vector3
	 */
	inline Vector3& add(float scalar) {
		data[0] += scalar;
		data[1] += scalar;
		data[2] += scalar;
		return *this;
	}

	/**
	 * Adds a vector3
	 * @param vector3 vector3
	 * @returns this vector3
	 */
	inline Vector3& add(const Vector3& vector3) {
		data[0] += vector3.data[0];
		data[1] += vector3.data[1];
		data[2] += vector3.data[2];
		return *this;
	}

	/**
	 * Subtracts a scalar
	 * @param scalar scalar
	 * @returns this vector3
	 */
	inline Vector3& sub(float scalar) {
		data[0] -= scalar;
		data[1] -= scalar;
		data[2] -= scalar;
		return *this;
	}

	/**
	 * Subtracts a vector3
	 * @param vector3 vector3
	 * @returns this vector3
	 */
	inline Vector3& sub(const Vector3& vector3) {
		data[0] -= vector3.data[0];
		data[1] -= vector3.data[1];
		data[2] -= vector3.data[2];
		return *this;
	}

	/**
	 * Scales by scalar
	 * @param scalar scalar
	 * @returns this vector3
	 */
	inline Vector3& scale(float scalar) {
		data[0] *= scalar;
		data[1] *= scalar;
		data[2] *= scalar;
		return *this;
	}

	/**
	 * Scales by vector3
	 * @param vector3 vector3
	 * @returns this vector3
	 */
	inline Vector3& scale(const Vector3& vector3) {
		data[0] *= vector3.data[0];
		data[1] *= vector3.data[1];
		data[2] *= vector3.data[2];
		return *this;
	}

	/**
	 * Compares this vector3 with given vector3
	 * @param vector3 vector3
	 * @param tolerance tolerance per vector3 component
	 * @returns equality
	 */
	inline bool equals(const Vector3& vector3, float tolerance = Math::EPSILON) const {
		return (this == &vector3) ||
			(
				Math::abs(data[0] - vector3.data[0]) < tolerance &&
				Math::abs(data[1] - vector3.data[1]) < tolerance &&
				Math::abs(data[2] - vector3.data[2]) < tolerance
			);
	}

	/**
	 * Normalizes this vector3
	 * @returns this vector3
	 */
	inline Vector3& normalize() {
		auto length = computeLength();
		data[0] /= length;
		data[1] /= length;
		data[2] /= length;
		return *this;
	}

	/**
	 * Computes the dot product of a and b
	 * @param a vector3 a
	 * @param b vector3 b
	 * @returns dot product
	 */
	inline static float computeDotProduct(const Vector3& a, const Vector3& b) {
		return (a.data[0] * b.data[0]) + (a.data[1] * b.data[1]) + (a.data[2] * b.data[2]);
	}

	/**
	 * Computes the cross product of a and b
	 * @param a vector3 a
	 * @param b vector3 b
	 * @returns cross product
	 */
	inline static Vector3 computeCrossProduct(const Vector3& a, const Vector3& b) {
		return Vector3(
			(a.data[1] * b.data[2]) - (a.data[2] * b.data[1]),
			(a.data[2] * b.data[0]) - (a.data[0] * b.data[2]),
			(a.data[0] * b.data[1]) - (a.data[1] * b.data[0])
		);
	}

	/**
	 * @returns the vectors length
	 */
	inline float computeLength() const {
		return Math::sqrt((data[0] * data[0]) + (data[1] * data[1]) + (data[2] * data[2]));
	}

	/**
	 * @returns the vectors length squared
	 */
	inline float computeLengthSquared() const {
		return (data[0] * data[0]) + (data[1] * data[1]) + (data[2] * data[2]);
	}

	/**
	 * Computes angle between a and b from 0.0 <= angle < 180.0
	 * @param a vector3 a, vector3 to test, must be normalized
	 * @param b vector3 b, vector3 to test against, must be normalized
	 * @returns angle
	 */
	inline static float computeAngle(const Vector3& a, const Vector3& b) {
		auto result = 180.0 / Math::PI * Math::acos(Math::clamp(Vector3::computeDotProduct(a, b), -1.0f, 1.0f));
		return result;
	}

	/**
	 * Computes angle between a and b from, where 0.0 <= angle < 360.0
	 * @param a vector3 a, vector3 to test, must be normalized
	 * @param b vector3 b, vector3 to test against, must be normalized
	 * @param n plane normal n where a and b live in, must be normalized
	 * @returns angle
	 */
	inline static float computeAngle(const Vector3& a, const Vector3& b, const Vector3& n) {
		auto angle = Vector3::computeAngle(a, b);
		auto sign = Math::sign(Vector3::computeDotProduct(n, Vector3::computeCrossProduct(a, b)));
		if (Float::isNaN(sign) == true) sign = 1.0f;
		return Math::mod(((angle * sign) + 360.0f), 360.0f);
	}

	/**
	 * Computes Euler angles
	 * @returns Euler angles
	 */
	inline Vector3 computeEulerAngles() const {
		if (computeLength() < Math::EPSILON) Vector3();
		//
		// TODO: check me, improve me
		//
		Vector3 euler;
		//
		Vector3 a(*this);
		a.normalize();
		// test around x axis
		{
			auto b = Vector3(0.0f, 1.0f, 0.0f);
			auto n = Vector3(1.0f, 0.0f, 0.0f);
			auto angle = Vector3::computeAngle(a, b, n);
			euler.setX(angle);
		}
		// test around y axis
		{
			auto b = Vector3(0.0f, 0.0f, -1.0f);
			auto n = Vector3(0.0f, 1.0f, 0.0f);
			auto angle = Vector3::computeAngle(a, b, n);
			euler.setY(angle);
		}
		// test around z axis
		{
			auto b = Vector3(0.0f, 1.0f, 0.0f);
			auto n = Vector3(0.0f, 0.0f, 1.0f);
			auto angle = Vector3::computeAngle(a, b, n);
			euler.setZ(angle);
		}
		//
		return euler;
	}

	/**
	 * Interpolates between a and b by 0f<=t<=1f linearly
	 * @param a vector3 b
	 * @param b vector3 b
	 * @param t t
	 * @returns interpolated vector3
	 */
	inline static Vector3 interpolateLinear(const Vector3& a, const Vector3& b, float t) {
		return Vector3(
			(b.data[0] * t) + ((1.0f - t) * a.data[0]),
			(b.data[1] * t) + ((1.0f - t) * a.data[1]),
			(b.data[2] * t) + ((1.0f - t) * a.data[2])
		);
	}

	/**
	 * @returns vector3 as array
	 */
	inline const array<float,3>& getArray() const {
		return (array<float,3>&)data;
	}

	/**
	 * Clones this vector3
	 * @returns cloned vector3
	 */
	inline Vector3 clone() const {
		return Vector3(data);
	}

	/**
	 * Array access operator
	 * @param i index
	 * @returns vector3 component
	 */
	inline float& operator[](int i) {
		return data[i];
	}

	/**
	 * Const array access operator
	 * @param i index
	 * @returns vector3 component
	 */
	inline const float& operator[](int i) const {
		return data[i];
	}

	/**
	 * Operator + scalar
	 * @param scalar scalar
	 * @returns new vector3 (this + scalar)
	 */
	inline Vector3 operator +(const float scalar) const {
		auto r = this->clone().add(scalar);
		return r;
	}

	/**
	 * Operator + vector3
	 * @param vector3 vector3
	 * @returns new vector3 (this + vector3)
	 */
	inline Vector3 operator +(const Vector3& vector3) const {
		auto r = this->clone().add(vector3);
		return r;
	}

	/**
	 * Operator - scalar
	 * @param scalar scalar
	 * @returns new vector3 (this - scalar)
	 */
	inline Vector3 operator -(const float scalar) const {
		auto r = this->clone().sub(scalar);
		return r;
	}

	/**
	 * Operator - vector3
	 * @param vector3 vector3
	 * @returns new vector3 (this - vector3)
	 */
	inline Vector3 operator -(const Vector3& vector3) const {
		auto r = this->clone().sub(vector3);
		return r;
	}

	/**
	 * Operator * scalar
	 * @param scalar scalar
	 * @returns new vector3 (this * scalar)
	 */
	inline Vector3 operator *(const float scalar) const {
		auto r = this->clone().scale(scalar);
		return r;
	}

	/**
	 * Operator * vector3
	 * @param vector3 vector3
	 * @returns new vector3 (this * vector3)
	 */
	inline Vector3 operator *(const Vector3& vector3) const {
		auto r = this->clone().scale(vector3);
		return r;
	}

	/**
	 * Operator / scalar
	 * @param scalar scalar
	 * @returns new vector3 (this / scalar)
	 */
	inline Vector3 operator /(const float scalar) const {
		auto r = this->clone().scale(1.0f / scalar);
		return r;
	}

	/**
	 * Operator / vector3
	 * @param vector3 vector3
	 * @returns new vector3 (this / vector3)
	 */
	inline Vector3 operator /(const Vector3& vector3) const {
		auto vInverted = Vector3(1.0f / vector3[0], 1.0f / vector3[1], 1.0f / vector3[2]);
		auto r = this->clone().scale(vInverted);
		return r;
	}

	/**
	 * Operator += scalar
	 * @param scalar scalar
	 * @returns this vector3
	 */
	inline Vector3& operator +=(const float scalar) {
		return this->add(scalar);
	}

	/**
	 * Operator += vector3
	 * @param vector3 vector3
	 * @returns this vector3
	 */
	inline Vector3& operator +=(const Vector3& vector3) {
		return this->add(vector3);
	}

	/**
	 * Operator -= scalar
	 * @param scalar scalar
	 * @returns this vector3
	 */
	inline Vector3& operator -=(const float scalar) {
		return this->sub(scalar);
	}

	/**
	 * Operator -= vector3
	 * @param vector3 vector3
	 * @returns this vector3
	 */
	inline Vector3& operator -=(const Vector3& vector3) {
		return this->sub(vector3);
	}

	/**
	 * Operator *= scalar
	 * @param scalar scalar
	 * @returns this vector3
	 */
	inline Vector3& operator *=(const float scalar) {
		return this->scale(scalar);
	}

	/**
	 * Operator *= vector3
	 * @param vector3 vector3
	 * @returns this vector3
	 */
	inline Vector3& operator *=(const Vector3& vector3) {
		return this->scale(vector3);
	}

	/**
	 * Operator /= scalar
	 * @param scalar scalar
	 * @returns this vector3
	 */
	inline Vector3& operator /=(const float scalar) {
		return this->scale(1.0f / scalar);
	}

	/**
	 * Operator /= vector3
	 * @param vector3 vector3
	 * @returns this vector3
	 */
	inline Vector3& operator /=(const Vector3& vector3) {
		auto vInverted = Vector3(1.0f / vector3[0], 1.0f / vector3[1], 1.0f / vector3[2]);
		return this->scale(vInverted);
	}

	/**
	 * Equality comparison operator
	 * @param vector3 vector3
	 * @returns equality
	 */
	inline bool operator ==(const Vector3& vector3) const {
		return this->equals(vector3);
	}

	/**
	 * Non equality comparison operator
	 * @param vector3 vector3
	 * @returns non equality
	 */
	inline bool operator !=(const Vector3& vector3) const {
		return this->equals(vector3) == false;
	}

};
