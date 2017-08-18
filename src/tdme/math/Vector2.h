// Generated from /tdme/src/tdme/math/Vector2.java

#pragma once

#include <array>

#include <Array.h>
#include <fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>

using std::array;

/** 
 * Vector 2 class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::math::Vector2 final
{
private:
	array<float, 2> data {  };

public:

	/** 
	 * Set up vector
	 * @param x
	 * @param y
	 * @return this vector
	 */
	Vector2* set(float x, float y);

	/** 
	 * Set up vector
	 * @param float array containing x,y values
	 * @return this vector
	 */
	Vector2* set(array<float, 2>* v);

	/**
	 * Set up vector
	 * @param float array containing x,y values
	 * @return this vector
	 */
	Vector2* set(floatArray* v);

	/** 
	 * Set up vector
	 * @param v
	 * @return this vector
	 */
	Vector2* set(Vector2* v);

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
	 * Adds a vector
	 * @param v
	 * @return this vector
	 */
	Vector2* add(Vector2* v);

	/** 
	 * Subtracts a vector
	 * @param v
	 * @return this vector
	 */
	Vector2* sub(Vector2* v);

	/** 
	 * Scale this vector
	 * @param scale
	 * @return this vector 
	 */
	Vector2* scale(float scale);

	/** 
	 * Scale this vector
	 * @param scale
	 * @return this vector 
	 */
	Vector2* scale(Vector2* scale);

	/** 
	 * @return the vectors length
	 */
	float computeLength();

	/** 
	 * @return vector as array
	 */
	array<float, 2>* getArray();

	/**
	 * Public constructor
	 */
	Vector2();

	/**
	 * Public constructor
	 * @param x
	 * @param y
	 */
	Vector2(float x, float y);

	/**
	 * Public constructor
	 * @param float values
	 */
	Vector2(array<float, 2>* v);

	/**
	 * Public constructor
	 * @param float values
	 */
	Vector2(floatArray* v);

	/**
	 * Public constructor
	 * @param v
	 */
	Vector2(Vector2* v);
};
