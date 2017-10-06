
#pragma once

#include <array>

#include <fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Math.h>
#include <tdme/math/MathTools.h>
#include <tdme/utils/Float.h>

using std::array;

using tdme::math::Math;
using tdme::math::Vector3;
using tdme::math::MathTools;
using tdme::utils::Float;

/** 
 * Vector3 class
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::math::Vector3 final
{
	friend class Matrix4x4;
	friend class Quaternion;
	friend class Vector4;

private:
	array<float, 3> data {  };

public:

	/** 
	 * Set up vector
	 * @param x
	 * @return this vector
	 */
	inline Vector3& set(float x, float y, float z) {
		data[0] = x;
		data[1] = y;
		data[2] = z;
		return *this;
	}

	/** 
	 * Set up vector
	 * @param float array containing x,y,z values
	 * @return this vector
	 */
	inline Vector3& set(const array<float, 3>& v) {
		data = v;
		return *this;
	}

	/** 
	 * Set up vector
	 * @param v
	 * @return this vector
	 */
	inline Vector3& set(const Vector3& v) {
		data = v.data;
		return *this;
	}

	/**
	 * @return x
	 */
	inline float getX() const {
		return data[0];
	}

	/** 
	 * Set X
	 * @param x
	 */
	inline Vector3& setX(float x) {
		data[0] = x;
		return *this;
	}

	/** 
	 * add to x component
	 * @param x
	 * @return this vector
	 */
	inline Vector3& addX(float x) {
		data[0]+= x;
		return *this;
	}

	/** 
	 * sub from x component
	 * @param x
	 * @return this vector
	 */
	inline Vector3& subX(float x) {
		data[0]-= x;
		return *this;
	}

	/** 
	 * @return y
	 */
	inline float getY() const {
		return data[1];
	}

	/** 
	 * Set Y
	 * @param y
	 * @return this vector
	 */
	inline Vector3& setY(float y) {
		data[1] = y;
		return *this;
	}

	/** 
	 * add to y component
	 * @param y
	 * @return this vector
	 */
	inline Vector3& addY(float y) {
		data[1]+= y;
		return *this;
	}

	/** 
	 * sub from y component
	 * @param y
	 * @return this vector
	 */
	inline Vector3& subY(float y) {
		data[1]-= y;
		return *this;
	}

	/** 
	 * @return z
	 */
	inline float getZ() const {
		return data[2];
	}

	/** 
	 * Set Z
	 * @param z
	 * @return this vector
	 */
	inline Vector3& setZ(float z) {
		data[2] = z;
		return *this;
	}

	/** 
	 * add to z component
	 * @param z
	 * @return this vector
	 */
	inline Vector3& addZ(float z) {
		data[2]+= z;
		return *this;
	}

	/** 
	 * sub from z component
	 * @param z
	 * @return this vector
	 */
	inline Vector3& subZ(float z) {
		data[2]-= z;
		return *this;
	}

	/** 
	 * @return vector as array
	 */
	inline array<float,3>& getArray() const {
		return (array<float,3>&)data;
	}

	/** 
	 * Compute the cross product of vector v1 and v2
	 * @param v1
	 * @param v2
	 * @param destination vector
	 * @return destination vector
	 */
	inline static Vector3& computeCrossProduct(const Vector3& v1, const Vector3& v2, Vector3& dest) {
		dest.set(
			(v1.data[1] * v2.data[2]) - (v1.data[2] * v2.data[1]),
			(v1.data[2] * v2.data[0]) - (v1.data[0] * v2.data[2]),
			(v1.data[0] * v2.data[1]) - (v1.data[1] * v2.data[0]));
		return dest;
	}

	/** 
	 * Compute the dot product of vector v1 and v2
	 * @param v1
	 * @param v2
	 * @return Vector3
	 */
	inline static float computeDotProduct(const Vector3& v1, const Vector3& v2) {
		return (v1.data[0] * v2.data[0]) + (v1.data[1] * v2.data[1]) + (v1.data[2] * v2.data[2]);
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
	 * Computes angle between a and b from 0..180
	 * @param vector a, must be normalized
	 * @param vector b, must be normalized
	 * @return
	 */
	inline static float computeAngle(const Vector3& a, const Vector3& b) {
		return 180.0 / Math::PI * Math::acos(Vector3::computeDotProduct(a, b));
	}

	/** 
	 * Computes angle between a and b 
	 * @param vector a, must be normalized
	 * @param vector b, must be normalized
	 * @param plane normal n where a and b live in, must be normalized
	 * @return
	 */
	inline static float computeAngle(const Vector3& a, const Vector3& b, const Vector3& n) {
		Vector3 c;
		auto angle = Vector3::computeAngle(a, b);
		auto sign = MathTools::sign(Vector3::computeDotProduct(n, Vector3::computeCrossProduct(a, b, c)));
		if (Float::isNaN(sign) == true) sign = 1.0f;
		return std::fmod(((angle * sign) + 360.0f), 360.0f);
	}

	/** 
	 * Normalize the vector
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
	 * Computes a orthogonal vector from this vector
	 * @param destination vector
	 * @return destination vector
	 */
	inline Vector3& computeOrthogonalVector(Vector3& dest) {
		if (Math::abs(data[0]) > MathTools::EPSILON) {
			dest.data[1] = data[0];
			dest.data[2] = ((-2 * data[0] * data[1]* data[2] + 2 * data[0] * data[2]) / (2 * (data[2] * data[2] + data[0] * data[0])));
			dest.data[0] = ((-data[0] * data[1] - data[2] * dest.data[2]) / data[0]);
		} else
		if (Math::abs(data[1]) > MathTools::EPSILON) {
			dest.data[2] = data[1];
			dest.data[0] = ((-2 * data[0] * data[1]* data[2] + 2 * data[0] * data[1]) / (2 * (data[1] * data[1] + data[0] * data[0])));
			dest.data[1] = ((-data[2] * data[1] - data[0] * dest.data[0]) / data[1]);
		} else
		if (Math::abs(data[2]) > MathTools::EPSILON) {
			dest.data[0] = data[2];
			dest.data[1] = ((-2 * data[0] * data[1]* data[2] + 2 * data[1] * data[2]) / (2 * (data[2] * data[2] + data[1] * data[1])));
			dest.data[2] = ((-data[0] * data[2] - data[1] * dest.data[1]) / data[2]);
		}
		return dest;
	}

	/** 
	 * Adds a vector
	 * @param v
	 * @return this vector
	 */
	inline Vector3& add(const Vector3& v) {
		data[0] += v.data[0];
		data[1] += v.data[1];
		data[2] += v.data[2];
		return *this;
	}

	/** 
	 * Adds a float to each vector component
	 * @param v
	 * @return this vector
	 */
	inline Vector3& add(float value) {
		data[0] += value;
		data[1] += value;
		data[2] += value;
		return *this;
	}

	/** 
	 * Adds a vector
	 * @param v
	 * @return this vector 
	 */
	inline Vector3& sub(const Vector3& v) {
		data[0] -= v.data[0];
		data[1] -= v.data[1];
		data[2] -= v.data[2];
		return *this;
	}

	/** 
	 * Subtracts a float from each vector component
	 * @param v
	 * @return this vector
	 */
	inline Vector3& sub(float value) {
		data[0] -= value;
		data[1] -= value;
		data[2] -= value;
		return *this;
	}

	/** 
	 * Scale this vector
	 * @param scale
	 * @return this vector 
	 */
	inline Vector3& scale(float scale) {
		data[0] *= scale;
		data[1] *= scale;
		data[2] *= scale;
		return *this;
	}

	/** 
	 * Scale this vector
	 * @param scale
	 * @return this vector 
	 */
	inline Vector3& scale(const Vector3& scale) {
		data[0] *= scale.data[0];
		data[1] *= scale.data[1];
		data[2] *= scale.data[2];
		return *this;
	}

	/**
	 * Clones the vector
	 * @return new cloned vector
	 */
	inline Vector3 clone() const {
		return Vector3(data);
	}

	/**
	 * Compares this vector with given vector
	 * @param vector v
	 * @return equality
	 */
	inline bool equals(const Vector3& v) const {
		return equals(v, MathTools::EPSILON);
	}

	/** 
	 * Compares this vector with given vector
	 * @param vector v
	 * @param tolerance
	 * @return equality
	 */
	inline bool equals(const Vector3& v, float tolerance) const {
		return (this == &v) ||
			(
				Math::abs(data[0] - v.data[0]) < tolerance &&
				Math::abs(data[1] - v.data[1]) < tolerance &&
				Math::abs(data[2] - v.data[2]) < tolerance
			);
	}

	/**
	 * Public constructor
	 */
	inline Vector3() {
		data.fill(0.0f);
	}

	/**
	 * Public constructor
	 * @param x
	 * @param y
	 * @param z
	 */
	inline Vector3(float x, float y, float z) {
		data[0] = x;
		data[1] = y;
		data[2] = z;
	}

	/**
	 * Public constructor
	 * @param values
	 */
	inline Vector3(const array<float,3>& v) {
		data = v;
	}

	/**
	 * Public constructor
	 * @param vector
	 */
	inline Vector3(const Vector3& v) {
		data = v.data;
	}

};
