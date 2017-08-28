// Generated from /tdme/src/tdme/math/Vector4.java

#pragma once

#include <array>

#include <fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>

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
	Vector4* set(float x, float y, float z, float w);

	/** 
	 * Set up vector
	 * @param float array containing x,y,z,w values
	 * @return this vector
	 */
	Vector4* set(array<float, 4>* v);

	/**
	 * Set up vector
	 * @param v
	 * @return this vector
	 */
	Vector4* set(Vector4* v);

	/** 
	 * Set up vector
	 * @param vector 3
	 * @param w 
	 * @return this vector
	 */
	Vector4* set(Vector3* v, float w);

	/** 
	 * @return x
	 */
	float getX();

	/** 
	 * set X
	 * @param x
	 */
	void setX(float x);

	/** 
	 * @return y
	 */
	float getY();

	/** 
	 * set Y
	 * @param y
	 */
	void setY(float y);

	/** 
	 * @return z
	 */
	float getZ();

	/** 
	 * Set Z
	 * @param z
	 */
	void setZ(float z);

	/** 
	 * @return w
	 */
	float getW();

	/** 
	 * Set W
	 * @param w
	 */
	void setW(float w);

	/** 
	 * Scale this vector
	 * @param scale
	 * @return this vector 
	 */
	Vector4* scale(float scale);

	/** 
	 * Scale this vector
	 * @param scale
	 * @return this vector 
	 */
	Vector4* scale(Vector4* scale);

	/** 
	 * @return vector as array
	 */
	array<float, 4>* getArray();

	/** 
	 * Clones the vector
	 * @return new cloned vector
	 */
	Vector4* clone();

	/**
	 * Public constructor
	 */
	Vector4();

	/**
	 * Public constructor
	 * @param vector
	 */
	Vector4(Vector4* v);

	/**
	 * Public constructor
	 * @param vector
	 * @param w
	 */
	Vector4(Vector3* v, float w);

	/**
	 * Public constructor
	 * @param x
	 * @param y
	 * @param z
	 * @param w
	 */
	Vector4(float x, float y, float z, float w);

	/**
	 * Public constructor
	 * @param v
	 */
	Vector4(array<float, 4>* v);
};
