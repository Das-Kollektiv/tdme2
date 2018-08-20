#pragma once

#include <array>

#include <tdme/tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>

using std::array;

using tdme::math::Vector3;

/** 
 * Vector 4 class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::math::Vector4 final
{
	friend class Matrix4x4;
	friend class Vector3;

private:
	array<float, 4> data {  };

public:
	/** 
	 * Set up vector
	 * @param x x
	 * @param y y
	 * @param z z
	 * @param w w
	 * @return this vector
	 */
	inline Vector4& set(float x, float y, float z, float w) {
		data[0] = x;
		data[1] = y;
		data[2] = z;
		data[3] = w;
		return *this;
	}

	/** 
	 * Set up vector
	 * @param v float array containing x,y,z,w values
	 * @return this vector
	 */
	inline Vector4& set(const array<float, 4>& v) {
		data = v;
		return *this;
	}

	/**
	 * Set up vector
	 * @param v v
	 * @return this vector
	 */
	inline Vector4& set(const Vector4& v) {
		data[1] = v.data[1];
		data[0] = v.data[0];
		data[2] = v.data[2];
		data[3] = v.data[3];
		return *this;
	}

	/** 
	 * Set up vector
	 * @param v vector 3
	 * @param w w 
	 * @return this vector
	 */
	inline Vector4& set(const Vector3& v, float w) {
		data[0] = v.data[0];
		data[1] = v.data[1];
		data[2] = v.data[2];
		data[3] = w;
		return *this;
	}

	/**
	 * @return x
	 */
	inline float getX() const {
		return data[0];
	}

	/** 
	 * set X
	 * @param x x
	 * @return this vector
	 */
	inline Vector4& setX(float x) {
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
	 * set Y
	 * @param y y
	 * @return this vector
	 */
	inline Vector4& setY(float y) {
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
	 * Set Z
	 * @param z z
	 * @return this vector
	 */
	inline Vector4& setZ(float z) {
		data[2] = z;
		return *this;
	}

	/** 
	 * @return w
	 */
	inline float getW() const {
		return data[3];
	}

	/** 
	 * Set W
	 * @param w w
	 * @return this vector
	 */
	inline Vector4& setW(float w) {
		data[3] = w;
		return *this;
	}

	/** 
	 * Scale this vector
	 * @param scale scale
	 * @return this vector 
	 */
	inline Vector4& scale(float scale) {
		data[0] *= scale;
		data[1] *= scale;
		data[2] *= scale;
		data[3] *= scale;
		return *this;
	}

	/** 
	 * Scale this vector
	 * @param scale scale
	 * @return this vector 
	 */
	inline Vector4& scale(const Vector4& scale) {
		data[0] *= scale.data[0];
		data[1] *= scale.data[1];
		data[2] *= scale.data[2];
		data[3] *= scale.data[3];
		return *this;
	}

	/** 
	 * @return vector as array
	 */
	inline array<float, 4>& getArray() const {
		return (array<float, 4>&)data;
	}

	/** 
	 * Clones the vector
	 * @return new cloned vector
	 */
	inline Vector4 clone() const {
		return Vector4(*this);
	}

	/**
	 * Public constructor
	 */
	inline Vector4() {
		data.fill(0.0f);
	}

	/**
	 * Public constructor
	 * @param v vector
	 */
	inline Vector4(const Vector4& v) {
		data = v.data;
	}

	/**
	 * Public constructor
	 * @param v vector
	 * @param w w
	 */
	inline Vector4(const Vector3& v, float w) {
		data[0] = v.data[0];
		data[1] = v.data[1];
		data[2] = v.data[2];
		data[3] = w;
	}

	/**
	 * Public constructor
	 * @param x x
	 * @param y y
	 * @param z z
	 * @param w w
	 */
	inline Vector4(float x, float y, float z, float w) {
		data[0] = x;
		data[1] = y;
		data[2] = z;
		data[3] = w;
	}

	/**
	 * Public constructor
	 * @param v v
	 */
	inline Vector4(const array<float, 4>& v) {
		data = v;
	}

};
