
#pragma once

#include <array>

#include <tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Math.h>

using std::array;

using tdme::math::Math;

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
	inline Vector2& set(float x, float y) {
		data[0] = x;
		data[1] = y;
		return *this;
	}

	/** 
	 * Set up vector
	 * @param float array containing x,y values
	 * @return this vector
	 */
	inline Vector2& set(const array<float, 2>& v) {
		data = v;
		return *this;
	}

	/** 
	 * Set up vector
	 * @param v
	 * @return this vector
	 */
	inline Vector2& set(const Vector2& v) {
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
	 * set X
	 * @param x
	 * @return this vector
	 */
	inline Vector2& setX(float x) {
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
	 * @param y
	 */
	inline Vector2& setY(float y) {
		data[1] = y;
		return *this;
	}

	/** 
	 * Adds a vector
	 * @param v
	 * @return this vector
	 */
	inline Vector2& add(Vector2& v) {
		data[0] += v.data[0];
		data[1] += v.data[1];
		return *this;
	}

	/** 
	 * Subtracts a vector
	 * @param v
	 * @return this vector
	 */
	inline Vector2& sub(Vector2& v) {
		data[0] -= v.data[0];
		data[1] -= v.data[1];
		return *this;
	}

	/** 
	 * Scale this vector
	 * @param scale
	 * @return this vector 
	 */
	inline Vector2& scale(float scale) {
		data[0] *= scale;
		data[1] *= scale;
		return *this;
	}

	/** 
	 * Scale this vector
	 * @param scale
	 * @return this vector 
	 */
	inline Vector2& scale(Vector2& scale) {
		data[0] *= scale.data[0];
		data[1] *= scale.data[1];
		return *this;
	}

	/** 
	 * @return the vectors length
	 */
	inline float computeLength() const {
		return Math::sqrt((data[0] * data[0]) + (data[1] * data[1]));
	}

	/** 
	 * @return vector as array
	 */
	inline array<float, 2>& getArray() const {
		return (array<float, 2>&)data;
	}

	/**
	 * Public constructor
	 */
	inline Vector2() {
		data.fill(0.0f);
	}

	/**
	 * Public constructor
	 * @param x
	 * @param y
	 */
	inline Vector2(float x, float y) {
		data[0] = x;
		data[1] = y;
	}

	/**
	 * Public constructor
	 * @param float values
	 */
	inline Vector2(const array<float, 2>& v) {
		data = v;
	}

	/**
	 * Public constructor
	 * @param v
	 */
	inline Vector2(const Vector2& v) {
		data = v.data;
	}
};
