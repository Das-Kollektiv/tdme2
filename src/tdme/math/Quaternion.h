
#pragma once

#include <array>

#include <tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Matrix4x4.h>

using std::array;

using tdme::math::Math;
using tdme::math::Vector3;
using tdme::math::Matrix4x4;

/** 
 * Quaternion
 * @author Andreas Drewke
 * @see http://db-in.com/blog/2011/04/cameras-on-opengl-es-2-x/
 */
class tdme::math::Quaternion final
{
private:
	array<float, 4> data {  };

public:

	/** 
	 * Set up this quaternion by components
	 * @param x
	 * @param y
	 * @param z
	 * @param w
	 */
	inline Quaternion& set(float x, float y, float z, float w) {
		data[0] = x;
		data[1] = y;
		data[2] = z;
		data[3] = w;
		return *this;
	}

	/** 
	 * Sets up this quaternion by quaternion q
	 * @param q
	 * @return
	 */
	inline Quaternion& set(const Quaternion& q) {
		data = q.data;
		return *this;
	}

	/** 
	 * Set quaternion
	 * @param x
	 * @param y
	 * @param z
	 * @param w
	 */
	inline Quaternion& set(const Vector3& v, float w) {
		data[0] = v.data[0];
		data[1] = v.data[1];
		data[2] = v.data[2];
		data[3] = w;
		return *this;
	}

	/** 
	 * Set up quaternion identity
	 * @return this quaternion
	 */
	inline Quaternion& identity() {
		data[0] = 0.0f;
		data[1] = 0.0f;
		data[2] = 0.0f;
		data[3] = 1.0f;
		return *this;
	}

	/** 
	 * Inverts this quaternion
	 * @return this quaternion
	 */
	inline Quaternion& invert() {
		data[0] *= -1.0f;
		data[1] *= -1.0f;
		data[2] *= -1.0f;
		return *this;
	}

	/** 
	 * Creates a rotation quaternion
	 * @param angle
	 * @param axis
	 * @return this quaternion
	 */
	inline Quaternion& rotate(float angle, const Vector3& v) {
		auto radians = angle * 3.1415927f / 180.0f;
		auto sin = Math::sin(radians * 0.5);
		auto cos = Math::cos(radians * 0.5);
		data[0] = v.data[0] * sin;
		data[1] = v.data[1] * sin;
		data[2] = v.data[2] * sin;
		data[3] = cos;
		return *this;
	}

	/** 
	 * Normalize quaternion
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
	 * Multiplies this quaternion with quaternion q
	 * @param quaterion q
	 * @return this quaternion
	 */
	inline Quaternion& multiply(const Quaternion q) {
		array<float, 4> _data;
		_data[0] = data[3] * q.data[0] + data[0] * q.data[3] + data[1] * q.data[2] - data[2] * q.data[1];
		_data[1] = data[3] * q.data[1] - data[0] * q.data[2] + data[1] * q.data[3] + data[2] * q.data[0];
		_data[2] = data[3] * q.data[2] + data[0] * q.data[1] - data[1] * q.data[0] + data[2] * q.data[3];
		_data[3] = data[3] * q.data[3] - data[0] * q.data[0] - data[1] * q.data[1] - data[2] * q.data[2];
		data = _data;
		return *this;
	}

	/** 
	 * Multiplies this quaternion with quaternion q
	 * @param quaterion q
	 * @return this quaternion
	 */
	inline Quaternion& add(const Quaternion& q) {
		data[0] += q.data[0];
		data[1] += q.data[1];
		data[2] += q.data[2];
		data[3] += q.data[3];
		return *this;
	}

	/** 
	 * Scales this quaternion with given value
	 * @param value
	 * @return this quaternion
	 */
	inline Quaternion& scale(float value) {
		data[0] *= value;
		data[1] *= value;
		data[2] *= value;
		data[3] *= value;
		return *this;
	}

	/** 
	 * Multiplies a quaternion with given vector v
	 * @param vector v
	 * @param dest
	 * @return dest
	 */
	inline Vector3& multiply(const Vector3& v, Vector3& dest) const {
		Vector3 q;
		Vector3 t;
		Vector3 qxt;
		q.set(data[0], data[1], data[2]);
		Vector3::computeCrossProduct(q, v, t).scale(2.0f);
		Vector3::computeCrossProduct(q, t, qxt);
		dest.set(v);
		dest.add(qxt);
		dest.add(t.scale(data[3]));
		return dest;
	}

	/** 
	 * Computes a matrix from given
	 * @param destination matrix
	 * @return destination matrix  
	 */
	inline Matrix4x4& computeMatrix(Matrix4x4& matrix) const {
		matrix.set(
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
		return matrix;
	}

	/** 
	 * Returns array data
	 * @return array data
	 */
	inline array<float, 4>& getArray() const {
		return (array<float, 4>&)data;
	}

	/**
	 * Public constructor
	 */
	inline Quaternion() {
		data.fill(0.0f);
	}

	/**
	 * Public constructor
	 * @param quaternion
	 */
	inline Quaternion(const Quaternion& q) {
		data = q.data;
	}

	/**
	 * Public constructor
	 * @param x
	 * @param y
	 * @param z
	 * @param w
	 */
	inline Quaternion(float x, float y, float z, float w) {
		data[0] = x;
		data[1] = y;
		data[2] = z;
		data[3] = w;
	}

	/**
	 * Public constructor
	 * @param vector
	 * @param w
	 */
	inline Quaternion(const Vector3& v, float w) {
		data[0] = v.data[0];
		data[1] = v.data[1];
		data[2] = v.data[2];
		data[3] = w;
	}
};
