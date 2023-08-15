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
 * 3D vector class
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
	 * @param x x
	 * @param y y
	 * @param z z
	 */
	inline Vector3(float x, float y, float z) {
		data[0] = x;
		data[1] = y;
		data[2] = z;
	}

	/**
	 * Public constructor
	 * @param vector vector as array
	 */
	inline Vector3(const array<float,3>& vector) {
		data = vector;
	}

	/**
	 * Public constructor
	 * @param vector vector
	 */
	inline Vector3(const Vector3& vector) {
		data = vector.data;
	}

	/**
	 * Sets up this vector by it components
	 * @param x x
	 * @param y y
	 * @param z z
	 * @return this vector
	 */
	inline Vector3& set(float x, float y, float z) {
		data[0] = x;
		data[1] = y;
		data[2] = z;
		return *this;
	}

	/**
	 * Sets up this vector by array
	 * @param vector vector as array
	 * @return this vector
	 */
	inline Vector3& set(const array<float, 3>& vector) {
		data = vector;
		return *this;
	}

	/**
	 * Sets up this vector by given vector
	 * @param vector vector
	 * @return this vector
	 */
	inline Vector3& set(const Vector3& vector) {
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
	inline Vector3& setX(float x) {
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
	inline Vector3& setY(float y) {
		data[1] = y;
		return *this;
	}

	/**
	 * @return z
	 */
	inline float getZ() const {
		return data[2];
	}

	/**
	 * Sets z
	 * @param z z
	 * @return this vector
	 */
	inline Vector3& setZ(float z) {
		data[2] = z;
		return *this;
	}

	/**
	 * Adds a scalar
	 * @param scalar scalar
	 * @return this vector
	 */
	inline Vector3& add(float scalar) {
		data[0] += scalar;
		data[1] += scalar;
		data[2] += scalar;
		return *this;
	}

	/**
	 * Adds a vector
	 * @param vector vector
	 * @return this vector
	 */
	inline Vector3& add(const Vector3& vector) {
		data[0] += vector.data[0];
		data[1] += vector.data[1];
		data[2] += vector.data[2];
		return *this;
	}

	/**
	 * Subtracts a scalar
	 * @param scalar scalar
	 * @return this vector
	 */
	inline Vector3& sub(float scalar) {
		data[0] -= scalar;
		data[1] -= scalar;
		data[2] -= scalar;
		return *this;
	}

	/**
	 * Subtracts a vector
	 * @param vector vector
	 * @return this vector
	 */
	inline Vector3& sub(const Vector3& vector) {
		data[0] -= vector.data[0];
		data[1] -= vector.data[1];
		data[2] -= vector.data[2];
		return *this;
	}

	/**
	 * Scales by scalar
	 * @param scalar scalar
	 * @return this vector
	 */
	inline Vector3& scale(float scalar) {
		data[0] *= scalar;
		data[1] *= scalar;
		data[2] *= scalar;
		return *this;
	}

	/**
	 * Scales by vector
	 * @param vector vector
	 * @return this vector
	 */
	inline Vector3& scale(const Vector3& vector) {
		data[0] *= vector.data[0];
		data[1] *= vector.data[1];
		data[2] *= vector.data[2];
		return *this;
	}

	/**
	 * Compares this vector with given vector
	 * @param vector vector
	 * @param tolerance tolerance per vector component
	 * @return equality
	 */
	inline bool equals(const Vector3& vector, float tolerance = Math::EPSILON) const {
		return (this == &vector) ||
			(
				Math::abs(data[0] - vector.data[0]) < tolerance &&
				Math::abs(data[1] - vector.data[1]) < tolerance &&
				Math::abs(data[2] - vector.data[2]) < tolerance
			);
	}

	/**
	 * Normalizes this vector
	 * @return this vector
	 */
	inline Vector3& normalize() {
		auto length = computeLength();
		data[0] /= length;
		data[1] /= length;
		data[2] /= length;
		return *this;
	}

	/**
	 * Computes the dot product of vector a and b
	 * @param a vector a
	 * @param b vector b
	 * @return dot product
	 */
	inline static float computeDotProduct(const Vector3& a, const Vector3& b) {
		return (a.data[0] * b.data[0]) + (a.data[1] * b.data[1]) + (a.data[2] * b.data[2]);
	}

	/**
	 * Computes the cross product of vector a and b
	 * @param a vector a
	 * @param b vector b
	 * @return cross product
	 */
	inline static Vector3 computeCrossProduct(const Vector3& a, const Vector3& b) {
		return Vector3(
			(a.data[1] * b.data[2]) - (a.data[2] * b.data[1]),
			(a.data[2] * b.data[0]) - (a.data[0] * b.data[2]),
			(a.data[0] * b.data[1]) - (a.data[1] * b.data[0])
		);
	}

	/**
	 * @return the vectors length
	 */
	inline float computeLength() const {
		return Math::sqrt((data[0] * data[0]) + (data[1] * data[1]) + (data[2] * data[2]));
	}

	/**
	 * @return the vectors length squared
	 */
	inline float computeLengthSquared() const {
		return (data[0] * data[0]) + (data[1] * data[1]) + (data[2] * data[2]);
	}

	/**
	 * Computes angle between a and b from 0.0 <= angle < 180.0
	 * @param a vector a, vector to test, must be normalized
	 * @param b vector b, vector to test against, must be normalized
	 * @return angle
	 */
	inline static float computeAngle(const Vector3& a, const Vector3& b) {
		auto result = 180.0 / Math::PI * Math::acos(Math::clamp(Vector3::computeDotProduct(a, b), -1.0f, 1.0f));
		return result;
	}

	/**
	 * Computes angle between a and b from, where 0.0 <= angle < 360.0
	 * @param a vector a, vector to test, must be normalized
	 * @param b vector b, vector to test against, must be normalized
	 * @param n plane normal n where a and b live in, must be normalized
	 * @return angle
	 */
	inline static float computeAngle(const Vector3& a, const Vector3& b, const Vector3& n) {
		auto angle = Vector3::computeAngle(a, b);
		auto sign = Math::sign(Vector3::computeDotProduct(n, Vector3::computeCrossProduct(a, b)));
		if (Float::isNaN(sign) == true) sign = 1.0f;
		return Math::mod(((angle * sign) + 360.0f), 360.0f);
	}

	/**
	 * Computes Euler angles
	 * @return Euler angles
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
	 * Interpolates between vector a and b by 0f<=t<=1f linearly
	 * @param a vector b
	 * @param b vector b
	 * @param t t
	 * @return interpolated vector
	 */
	inline static Vector3 interpolateLinear(const Vector3& a, const Vector3& b, float t) {
		return Vector3(
			(b.data[0] * t) + ((1.0f - t) * a.data[0]),
			(b.data[1] * t) + ((1.0f - t) * a.data[1]),
			(b.data[2] * t) + ((1.0f - t) * a.data[2])
		);
	}

	/**
	 * @return vector as array
	 */
	inline const array<float,3>& getArray() const {
		return (array<float,3>&)data;
	}

	/**
	 * Clones this vector
	 * @return cloned vector
	 */
	inline Vector3 clone() const {
		return Vector3(data);
	}

	/**
	 * Array access operator
	 * @param i index
	 * @return vector3 component
	 */
	inline float& operator[](int i) {
		return data[i];
	}

	/**
	 * Const array access operator
	 * @param i index
	 * @return vector3 component
	 */
	inline const float& operator[](int i) const {
		return data[i];
	}

	/**
	 * Operator + scalar
	 * @param scalar scalar
	 * @return new vector (this + scalar)
	 */
	inline Vector3 operator +(const float scalar) const {
		auto r = this->clone().add(scalar);
		return r;
	}

	/**
	 * Operator + vector
	 * @param vector vector
	 * @return new vector (this + vector)
	 */
	inline Vector3 operator +(const Vector3& vector) const {
		auto r = this->clone().add(vector);
		return r;
	}

	/**
	 * Operator - scalar
	 * @param scalar scalar
	 * @return new vector (this - scalar)
	 */
	inline Vector3 operator -(const float scalar) const {
		auto r = this->clone().sub(scalar);
		return r;
	}

	/**
	 * Operator - vector
	 * @param vector vector
	 * @return new vector (this - vector)
	 */
	inline Vector3 operator -(const Vector3& vector) const {
		auto r = this->clone().sub(vector);
		return r;
	}

	/**
	 * Operator * scalar
	 * @param scalar scalar
	 * @return new vector (this * scalar)
	 */
	inline Vector3 operator *(const float scalar) const {
		auto r = this->clone().scale(scalar);
		return r;
	}

	/**
	 * Operator * vector
	 * @param vector vector
	 * @return new vector (this * vector)
	 */
	inline Vector3 operator *(const Vector3& vector) const {
		auto r = this->clone().scale(vector);
		return r;
	}

	/**
	 * Operator / scalar
	 * @param scalar scalar
	 * @return new vector (this / scalar)
	 */
	inline Vector3 operator /(const float scalar) const {
		auto r = this->clone().scale(1.0f / scalar);
		return r;
	}

	/**
	 * Operator / vector
	 * @param vector vector
	 * @return new vector (this / vector)
	 */
	inline Vector3 operator /(const Vector3& vector) const {
		auto vInverted = Vector3(1.0f / vector[0], 1.0f / vector[1], 1.0f / vector[2]);
		auto r = this->clone().scale(vInverted);
		return r;
	}

	/**
	 * Operator += scalar
	 * @param scalar scalar
	 * @return this vector
	 */
	inline Vector3& operator +=(const float scalar) {
		return this->add(scalar);
	}

	/**
	 * Operator += vector
	 * @param vector vector
	 * @return this vector
	 */
	inline Vector3& operator +=(const Vector3& vector) {
		return this->add(vector);
	}

	/**
	 * Operator -= scalar
	 * @param scalar scalar
	 * @return this vector
	 */
	inline Vector3& operator -=(const float scalar) {
		return this->sub(scalar);
	}

	/**
	 * Operator -= vector
	 * @param vector vector
	 * @return this vector
	 */
	inline Vector3& operator -=(const Vector3& vector) {
		return this->sub(vector);
	}

	/**
	 * Operator *= scalar
	 * @param scalar scalar
	 * @return this vector
	 */
	inline Vector3& operator *=(const float scalar) {
		return this->scale(scalar);
	}

	/**
	 * Operator *= vector
	 * @param vector vector
	 * @return this vector
	 */
	inline Vector3& operator *=(const Vector3& vector) {
		return this->scale(vector);
	}

	/**
	 * Operator /= scalar
	 * @param scalar scalar
	 * @return this vector
	 */
	inline Vector3& operator /=(const float scalar) {
		return this->scale(1.0f / scalar);
	}

	/**
	 * Operator /= vector
	 * @param vector vector
	 * @return this vector
	 */
	inline Vector3& operator /=(const Vector3& vector) {
		auto vInverted = Vector3(1.0f / vector[0], 1.0f / vector[1], 1.0f / vector[2]);
		return this->scale(vInverted);
	}

	/**
	 * Equality comparison operator
	 * @param vector vector
	 * @return equality
	 */
	inline bool operator ==(const Vector3& vector) const {
		return this->equals(vector);
	}

	/**
	 * Non equality comparison operator
	 * @param vector vector
	 * @return non equality
	 */
	inline bool operator !=(const Vector3& vector) const {
		return this->equals(vector) == false;
	}

};
