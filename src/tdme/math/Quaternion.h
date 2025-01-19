#pragma once

#include <array>

#include <tdme/tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Float.h>

using std::array;

using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utilities::Float;

/**
 * Quaternion class representing quaternion mathematical structure and operations with x, y, z, w components
 * @author Andreas Drewke
 */
class tdme::math::Quaternion final
{
	// see http://db-in.com/blog/2011/04/cameras-on-opengl-es-2-x/
private:
	array<float, 4> data { 0.0f, 0.0f, 0.0f, 0.0f };

public:
	/**
	 * Public constructor
	 */
	inline Quaternion() {
	}

	/**
	 * Public constructor
	 * @param x x component
	 * @param y y component
	 * @param z z component
	 * @param w w component
	 */
	inline Quaternion(float x, float y, float z, float w) {
		data[0] = x;
		data[1] = y;
		data[2] = z;
		data[3] = w;
	}

	/**
	 * Public constructor
	 * @param vector3 vector3 as array
	 * @param w w component
	 */
	inline Quaternion(const array<float, 3>& vector3, float w) {
		data[0] = vector3[0];
		data[1] = vector3[1];
		data[2] = vector3[2];
		data[3] = w;
	}

	/**
	 * Public constructor
	 * @param vector3 vector3
	 * @param w w component
	 */
	inline Quaternion(const Vector3& vector3, float w) {
		data[0] = vector3.data[0];
		data[1] = vector3.data[1];
		data[2] = vector3.data[2];
		data[3] = w;
	}

	/**
	 * Public constructor
	 * @param quaternion quaternion as array
	 */
	inline Quaternion(const array<float, 4>& quaternion) {
		data = quaternion;
	}

	/**
	 * Public constructor
	 * @param quaternion Quaternion
	 */
	inline Quaternion(const Quaternion& quaternion) {
		data = quaternion.data;
	}

	/**
	 * Sets this quaternion by its components
	 * @param x x component
	 * @param y y component
	 * @param z z component
	 * @param w w component
	 * @returns this quaternion
	 */
	inline Quaternion& set(float x, float y, float z, float w) {
		data[0] = x;
		data[1] = y;
		data[2] = z;
		data[3] = w;
		return *this;
	}

	/**
	 * Sets this quaternion by vector3 by array and w component
	 * @param vector3 vector3 as array
	 * @param w w component
	 * @returns this quaternion
	 */
	inline Quaternion& set(const array<float, 3>& vector3, float w) {
		data[0] = vector3[0];
		data[1] = vector3[1];
		data[2] = vector3[2];
		data[3] = w;
		return *this;
	}

	/**
	 * Sets this quaternion by vector3 and w component
	 * @param vector3 vector3
	 * @param w w component
	 * @returns this quaternion
	 */
	inline Quaternion& set(const Vector3& vector3, float w) {
		data[0] = vector3.data[0];
		data[1] = vector3.data[1];
		data[2] = vector3.data[2];
		data[3] = w;
		return *this;
	}

	/**
	 * Sets this quaternion by array
	 * @param quaternion quaternion as array
	 * @returns this quaternion
	 */
	inline Quaternion& set(const array<float, 4>& quaternion) {
		data = quaternion;
		return *this;
	}

	/**
	 * Sets this quaternion by given quaternion
	 * @param quaternion quaternion
	 * @returns this quaternion
	 */
	inline Quaternion& set(const Quaternion& quaternion) {
		data = quaternion.data;
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
	 * @returns this quaternion
	 */
	inline Quaternion& setX(float x) {
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
	 * @returns this quaternion
	 */
	inline Quaternion& setY(float y) {
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
	 * @returns this quaternion
	 */
	inline Quaternion& setZ(float z) {
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
	 * @returns this quaternion
	 */
	inline Quaternion& setW(float w) {
		data[3] = w;
		return *this;
	}

	/**
	 * Creates identity quaternion
	 * @returns this quaternion
	 */
	inline Quaternion& identity() {
		data[0] = 0.0f;
		data[1] = 0.0f;
		data[2] = 0.0f;
		data[3] = 1.0f;
		return *this;
	}

	/**
	 * Adds quaternion
	 * @param quaternion quaternion
	 * @returns this quaternion
	 */
	inline Quaternion& add(const Quaternion& quaternion) {
		data[0] += quaternion.data[0];
		data[1] += quaternion.data[1];
		data[2] += quaternion.data[2];
		data[3] += quaternion.data[3];
		return *this;
	}

	/**
	 * Subtracts quaternion
	 * @param quaternion quaternion
	 * @returns this quaternion
	 */
	inline Quaternion& sub(const Quaternion& quaternion) {
		data[0] -= quaternion.data[0];
		data[1] -= quaternion.data[1];
		data[2] -= quaternion.data[2];
		data[3] -= quaternion.data[3];
		return *this;
	}

	/**
	 * Scales by scalar
	 * @param scalar scalar
	 * @returns this quaternion
	 */
	inline Quaternion& scale(float scalar) {
		data[0] *= scalar;
		data[1] *= scalar;
		data[2] *= scalar;
		data[3] *= scalar;
		return *this;
	}

	/**
	 * Multiplies this quaternion with given quaternion
	 * @param quaternion quaternion
	 * @returns this quaternion
	 */
	inline Quaternion& multiply(const Quaternion quaternion) {
		array<float, 4> _data;
		_data[0] = data[3] * quaternion.data[0] + data[0] * quaternion.data[3] + data[1] * quaternion.data[2] - data[2] * quaternion.data[1];
		_data[1] = data[3] * quaternion.data[1] - data[0] * quaternion.data[2] + data[1] * quaternion.data[3] + data[2] * quaternion.data[0];
		_data[2] = data[3] * quaternion.data[2] + data[0] * quaternion.data[1] - data[1] * quaternion.data[0] + data[2] * quaternion.data[3];
		_data[3] = data[3] * quaternion.data[3] - data[0] * quaternion.data[0] - data[1] * quaternion.data[1] - data[2] * quaternion.data[2];
		data = _data;
		return *this;
	}

	/**
	 * Multiplies this quaternion with vector3
	 * @param vector3 vector3
	 * @returns vector3
	 */
	inline Vector3 multiply(const Vector3& vector3) const {
		// t = 2 * cross(quaternion.xyz, vector3)
		Vector3 quaternion(data[0], data[1], data[2]);
		auto t = Vector3::computeCrossProduct(quaternion, vector3).scale(2.0f);
		// vector3' = vector3 + quaternion.w * t + cross(quaternion.xyz, t)
		auto qxt = Vector3::computeCrossProduct(quaternion, t);
		//
		Vector3 result;
		result.set(vector3);
		result.add(qxt);
		result.add(t.scale(data[3]));
		return result;
	}

	/**
	 * Compares this quaternion with given quaternion
	 * @param quaternion quaternion
	 * @returns equality
	 */
	inline bool equals(const Quaternion& quaternion) const {
		return equals(quaternion, Math::EPSILON);
	}

	/**
	 * Compares this quaternion with given quaternion
	 * @param quaternion quaternion
	 * @param tolerance tolerance per component(x, y, z, w)
	 * @returns equality
	 */
	inline bool equals(const Quaternion& quaternion, float tolerance) const {
		return (this == &quaternion) ||
			(
				Math::abs(data[0] - quaternion.data[0]) < tolerance &&
				Math::abs(data[1] - quaternion.data[1]) < tolerance &&
				Math::abs(data[2] - quaternion.data[2]) < tolerance &&
				Math::abs(data[3] - quaternion.data[3]) < tolerance
			);
	}

	/**
	 * Inverts this quaternion
	 * @returns this quaternion
	 */
	inline Quaternion& invert() {
		data[0] *= -1.0f;
		data[1] *= -1.0f;
		data[2] *= -1.0f;
		return *this;
	}

	/**
	 * Normalizes this quaternion
	 */
	inline Quaternion& normalize() {
		auto magnitude = Math::sqrt(data[0] * data[0] + data[1] * data[1] + data[2] * data[2] + data[3] * data[3]);
		data[0] = data[0] / magnitude;
		data[1] = data[1] / magnitude;
		data[2] = data[2] / magnitude;
		data[3] = data[3] / magnitude;
		return *this;
	}

	/**
	 * Creates rotation quaternion
	 * @param axis axis
	 * @param angle angle
	 * @returns this quaternion
	 */
	inline Quaternion& rotate(const Vector3& axis, float angle) {
		// converts the angle in degrees to radians
		auto radians = angle * Math::PI / 180.0f;
		// finds the sin and cosin for the half angle
		auto sin = Math::sin(radians * 0.5);
		auto cos = Math::cos(radians * 0.5);
		// formula to construct a new Quaternion based on direction and angle
		data[0] = axis.data[0] * sin;
		data[1] = axis.data[1] * sin;
		data[2] = axis.data[2] * sin;
		data[3] = cos;
		return *this;
	}

	/**
	 * Computes a rotation matrix4x4 from this quaternion
	 * @returns rotation matrix
	 */
	inline Matrix4x4 computeMatrix() const {
		return Matrix4x4(
			1.0f - 2.0f * (data[1] * data[1] + data[2] * data[2]),
			2.0f * (data[0] * data[1] + data[2] * data[3]),
			2.0f * (data[0] * data[2] - data[1] * data[3]),
			0.0f,
			2.0f * (data[0] * data[1] - data[2] * data[3]),
			1.0f - 2.0f * (data[0] * data[0] + data[2] * data[2]),
			2.0f * (data[2] * data[1] + data[0] * data[3]),
			0.0f,
			2.0f * (data[0] * data[2] + data[1] * data[3]),
			2.0f * (data[1] * data[2] - data[0] * data[3]),
			1.0f - 2.0f * (data[0] * data[0] + data[1] * data[1]),
			0.0f,
			0.0f,
			0.0f,
			0.0f,
			1.0f
		);
	}

	/**
	 * Compute Euler angles
	 * @returns Euler angles
	 */
	inline Vector3 computeEulerAngles() const {
		// https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
		// https://math.stackexchange.com/questions/2975109/how-to-convert-euler-angles-to-quaternions-and-get-the-same-euler-angles-back-fr
		Vector3 euler;
		// roll (x-axis rotation)
		auto t0 = 2.0f * (data[3] * data[0] + data[1] * data[2]);
		auto t1 = 1.0f - 2.0f * (data[0] * data[0] + data[1] * data[1]);
		euler[0] = Math::atan2(t0, t1) / Math::DEG2RAD;
		// pitch (y-axis rotation)
		auto t2 = Math::clamp(2.0f * (data[3] * data[1] - data[2] * data[0]), -1.0f, 1.0f);
		euler[1] = Math::asin(t2) / Math::DEG2RAD;
		// yaw (z-axis rotation)
		auto t3 = 2.0f * (data[3] * data[2] + data[0] * data[1]);
		auto t4 = 1.0f - 2.0f * (data[1] * data[1] + data[2] * data[2]);
		euler[2] = Math::atan2(t3, t4) / Math::DEG2RAD;
		//
		return euler;
	}

	/**
	 * Clones this quaternion
	 * @returns new cloned quaternion
	 */
	inline Quaternion clone() const {
		return Quaternion(*this);
	}

	/**
	 * @returns quaternion as array
	 */
	inline const array<float, 4>& getArray() const {
		return data;
	}

	/**
	 * Array access operator
	 * @param i index
	 * @returns quaternion component
	 */
	inline float& operator[](int i) {
		return data[i];
	}

	/**
	 * Const array access operator
	 * @param i index
	 * @returns quaternion component
	 */
	inline const float& operator[](int i) const {
		return data[i];
	}

	/**
	 * Operator + quaternion
	 * @param quaternion quaternion
	 * @returns new quaternion (this + quaternion)
	 */
	inline Quaternion operator +(const Quaternion& quaternion) const {
		auto r = this->clone().add(quaternion);
		return r;
	}

	/**
	 * Operator - quaternion
	 * @param quaternion quaternion
	 * @returns new quaternion (this - quaternion)
	 */
	inline Quaternion operator -(const Quaternion& quaternion) const {
		auto r = this->clone().sub(quaternion);
		return r;
	}

	/**
	 * Operator * scalar
	 * @param scalar scalar
	 * @returns new quaternion (this * scalar)
	 */
	inline Quaternion operator *(const float scalar) const {
		auto r = this->clone().scale(scalar);
		return r;
	}

	/**
	 * Operator * quaternion
	 * @param scalar scalar
	 * @returns new quaternion (this * quaternion)
	 */
	inline Quaternion operator *(const Quaternion& quaternion) const {
		auto r = this->clone().multiply(quaternion);
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
	 * Operator / scalar
	 * @param scalar scalar
	 * @returns new quaternion (this / scalar)
	 */
	inline Quaternion operator /(const float scalar) const {
		auto r = this->clone().scale(1.0f / scalar);
		return r;
	}

	/**
	 * Operator / quaternion
	 * @param quaternion quaternion
	 * @returns new quaternion (this / quaternion)
	 */
	inline Quaternion operator /(const Quaternion& quaternion) const {
		auto qInverted = Quaternion(1.0f / quaternion[0], 1.0f / quaternion[1], 1.0f / quaternion[2], 1.0f / quaternion[3]);
		auto r = this->clone().multiply(qInverted);
		return r;
	}

	/**
	 * Operator += quaternion
	 * @param quaternion quaternion
	 * @returns this quaternion
	 */
	inline Quaternion& operator +=(const Quaternion& quaternion) {
		return this->add(quaternion);
	}

	/**
	 * Operator -= quaternion
	 * @param quaternion quaternion
	 * @returns this quaternion
	 */
	inline Quaternion& operator -=(const Quaternion& quaternion) {
		return this->sub(quaternion);
	}

	/**
	 * Operator *= quaternion
	 * @param quaternion quaternion
	 * @returns this quaternion
	 */
	inline Quaternion& operator *=(const Quaternion& quaternion) {
		return this->multiply(quaternion);
	}

	/**
	 * Operator /= quaternion
	 * @param quaternion quaternion
	 * @returns this quaternion
	 */
	inline Quaternion& operator /=(const Quaternion& quaternion) {
		auto qInverted = Quaternion(1.0f / quaternion[0], 1.0f / quaternion[1], 1.0f / quaternion[2], 1.0f / quaternion[3]);
		return this->multiply(qInverted);
	}

	/**
	 * Equality comparison operator
	 * @param quaternion quaternion
	 * @returns equality
	 */
	inline bool operator ==(const Quaternion& quaternion) const {
		return this->equals(quaternion);
	}

	/**
	 * Non equality comparison operator
	 * @param quaternion quaternion
	 * @returns non equality
	 */
	inline bool operator !=(const Quaternion& quaternion) const {
		return this->equals(quaternion) == false;
	}

};
