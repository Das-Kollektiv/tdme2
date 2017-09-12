// Generated from /tdme/src/tdme/math/Vector4.java

#pragma once

#include <array>

#include <fwd-tdme.h>
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
	 * @param x
	 * @param y
	 * @param z
	 * @param w
	 * @return this vector
	 */
	inline Vector4* set(float x, float y, float z, float w) {
		data[0] = x;
		data[1] = y;
		data[2] = z;
		data[3] = w;
		return this;
	}

	/** 
	 * Set up vector
	 * @param float array containing x,y,z,w values
	 * @return this vector
	 */
	inline Vector4* set(array<float, 4>* v) {
		data = *v;
		return this;
	}

	/**
	 * Set up vector
	 * @param v
	 * @return this vector
	 */
	inline Vector4* set(Vector4* v) {
		data[0] = v->data[0];
		data[1] = v->data[1];
		data[2] = v->data[2];
		data[3] = v->data[3];
		return this;
	}

	/** 
	 * Set up vector
	 * @param vector 3
	 * @param w 
	 * @return this vector
	 */
	inline Vector4* set(Vector3* v, float w) {
		data[0] = v->data[0];
		data[1] = v->data[1];
		data[2] = v->data[2];
		data[3] = w;
		return this;
	}

	/** 
	 * @return x
	 */
	inline float getX() {
		return data[0];
	}

	/** 
	 * set X
	 * @param x
	 */
	inline void setX(float x) {
		data[0] = x;
	}

	/** 
	 * @return y
	 */
	inline float getY() {
		return data[1];
	}

	/** 
	 * set Y
	 * @param y
	 */
	inline void setY(float y) {
		data[1] = y;
	}

	/** 
	 * @return z
	 */
	inline float getZ() {
		return data[2];
	}

	/** 
	 * Set Z
	 * @param z
	 */
	inline void setZ(float z) {
		data[2] = z;
	}

	/** 
	 * @return w
	 */
	inline float getW() {
		return data[3];
	}

	/** 
	 * Set W
	 * @param w
	 */
	inline void setW(float w) {
		data[3] = w;
	}

	/** 
	 * Scale this vector
	 * @param scale
	 * @return this vector 
	 */
	inline Vector4* scale(float scale) {
		data[0] *= scale;
		data[1] *= scale;
		data[2] *= scale;
		data[3] *= scale;
		return this;
	}

	/** 
	 * Scale this vector
	 * @param scale
	 * @return this vector 
	 */
	inline Vector4* scale(Vector4* scale) {
		data[0] *= scale->data[0];
		data[1] *= scale->data[1];
		data[2] *= scale->data[2];
		data[3] *= scale->data[3];
		return this;
	}

	/** 
	 * @return vector as array
	 */
	inline array<float, 4>* getArray() {
		return &data;
	}

	/** 
	 * Clones the vector
	 * @return new cloned vector
	 */
	inline Vector4* clone() {
		return new Vector4(this);
	}

	/**
	 * Public constructor
	 */
	inline Vector4() {
		data.fill(0.0f);
	}

	/**
	 * Public constructor
	 * @param vector
	 */
	inline Vector4(Vector4* v) {
		data = v->data;
	}

	/**
	 * Public constructor
	 * @param vector
	 * @param w
	 */
	inline Vector4(Vector3* v, float w) {
		data[0] = v->data[0];
		data[1] = v->data[1];
		data[2] = v->data[2];
		data[3] = w;
	}

	/**
	 * Public constructor
	 * @param x
	 * @param y
	 * @param z
	 * @param w
	 */
	inline Vector4(float x, float y, float z, float w) {
		data[0] = x;
		data[1] = y;
		data[2] = z;
		data[3] = w;
	}

	/**
	 * Public constructor
	 * @param v
	 */
	inline Vector4(array<float, 4>* v) {
		data = *v;
	}

};
