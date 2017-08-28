// Generated from /tdme/src/tdme/math/Vector3.java

#pragma once

#include <array>

#include <fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>

using std::array;

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
	Vector3* set(float x, float y, float z);

	/** 
	 * Set up vector
	 * @param float array containing x,y,z values
	 * @return this vector
	 */
	Vector3* set(array<float, 3>* v);

	/** 
	 * Set up vector
	 * @param v
	 * @return this vector
	 */
	Vector3* set(Vector3* v);

	/** 
	 * Set up vector
	 * @param v
	 * @return this vector
	 */
	Vector3* set(Vector4* v);

	/**
	 * @return x
	 */
	float getX();

	/** 
	 * Set X
	 * @param x
	 */
	void setX(float x);

	/** 
	 * add to x component
	 * @param x
	 * @return this vector
	 */
	Vector3* addX(float x);

	/** 
	 * sub from x component
	 * @param x
	 * @return this vector
	 */
	Vector3* subX(float x);

	/** 
	 * @return y
	 */
	float getY();

	/** 
	 * Set Y
	 * @param y
	 * @return this vector
	 */
	Vector3* setY(float y);

	/** 
	 * add to y component
	 * @param y
	 * @return this vector
	 */
	Vector3* addY(float y);

	/** 
	 * sub from y component
	 * @param y
	 * @return this vector
	 */
	Vector3* subY(float y);

	/** 
	 * @return z
	 */
	float getZ();

	/** 
	 * Set Z
	 * @param z
	 * @return this vector
	 */
	Vector3* setZ(float z);

	/** 
	 * add to z component
	 * @param z
	 * @return this vector
	 */
	Vector3* addZ(float z);

	/** 
	 * sub from z component
	 * @param z
	 * @return this vector
	 */
	Vector3* subZ(float z);

	/** 
	 * @return vector as array
	 */
	array<float,3>* getArray();

	/** 
	 * Compute the cross product of vector v1 and v2
	 * @param v1
	 * @param v2
	 * @return cross product vector of v1 and v2
	 */
	static Vector3* computeCrossProduct(Vector3* v1, Vector3* v2);

	/** 
	 * Compute the cross product of vector v1 and v2
	 * @param v1
	 * @param v2
	 * @param destination vector
	 * @return destination vector
	 */
	static Vector3* computeCrossProduct(Vector3* v1, Vector3* v2, Vector3* dest);

	/** 
	 * Compute the dot product of vector v1 and v2
	 * @param v1
	 * @param v2
	 * @return Vector3
	 */
	static float computeDotProduct(Vector3* v1, Vector3* v2);

	/** 
	 * @return the vectors length
	 */
	float computeLength();

	/** 
	 * @return the vectors volume if it would span a box
	 */
	float computeVolume();

	/** 
	 * @return the vectors length squared
	 */
	float computeLengthSquared();

	/** 
	 * Computes angle between a and b from 0..180
	 * @param vector a, must be normalized
	 * @param vector b, must be normalized
	 * @return
	 */
	static float computeAngle(Vector3* a, Vector3* b);

	/** 
	 * Computes angle between a and b 
	 * @param vector a, must be normalized
	 * @param vector b, must be normalized
	 * @param plane normal n where a and b live in, must be normalized
	 * @return
	 */
	static float computeAngle(Vector3* a, Vector3* b, Vector3* n);

	/** 
	 * Normalize the vector
	 * @return this vector
	 */
	Vector3* normalize();

	/** 
	 * Computes a orthogonal vector from this vector
	 * @param destination vector
	 * @return destination vector
	 */
	Vector3* computeOrthogonalVector(Vector3* dest);

	/** 
	 * Adds a vector
	 * @param v
	 * @return this vector
	 */
	Vector3* add(Vector3* v);

	/** 
	 * Adds a float to each vector component
	 * @param v
	 * @return this vector
	 */
	Vector3* add(float value);

	/** 
	 * Adds a vector
	 * @param v
	 * @return this vector 
	 */
	Vector3* sub(Vector3* v);

	/** 
	 * Subtracts a float from each vector component
	 * @param v
	 * @return this vector
	 */
	Vector3* sub(float value);

	/** 
	 * Scale this vector
	 * @param scale
	 * @return this vector 
	 */
	Vector3* scale(float scale);

	/** 
	 * Scale this vector
	 * @param scale
	 * @return this vector 
	 */
	Vector3* scale(Vector3* scale);

	/** 
	 * Clones the vector
	 * @return new cloned vector
	 */
	Vector3* clone();

	/** 
	 * Clones the vector
	 * @return new cloned vector
	 */
	Vector3 clone2();

	/**
	 * Compares this vector with given vector
	 * @param vector v
	 * @return equality
	 */
	bool equals(Vector3* v);

	/** 
	 * Compares this vector with given vector
	 * @param vector v
	 * @param tolerance
	 * @return equality
	 */
	bool equals(Vector3* v, float tolerance);

	/**
	 * Public constructor
	 */
	Vector3();

	/**
	 * Public constructor
	 * @param x
	 * @param y
	 * @param z
	 */
	Vector3(float x, float y, float z);

	/**
	 * Public constructor
	 * @param values
	 */
	Vector3(array<float,3>* v);

	/**
	 * Public constructor
	 * @param vector
	 */
	Vector3(Vector3* v);

	/**
	 * Public constructor
	 * @param vector
	 */
	Vector3(Vector4* v);
};
