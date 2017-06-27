// Generated from /tdme/src/tdme/math/Vector2.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;


struct default_init_tag;

/** 
 * Vector 2 class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::math::Vector2 final
	: public Object
{

public:
	typedef Object super;

public: /* protected */
	floatArray* data {  };
protected:

	/** 
	 * Public constructor
	 */
	void ctor();

	/** 
	 * Public constructor
	 * @param x
	 * @param y
	 */
	void ctor(float x, float y);

	/** 
	 * Public constructor
	 * @param float array containing x,y values
	 */
	void ctor(floatArray* v);

	/** 
	 * Public constructor
	 * @param vector 2
	 */
	void ctor(Vector2* v);

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
	floatArray* getArray();

	/** 
	 * @return string representation
	 */
	String* toString() override;

	// Generated
	Vector2();
	Vector2(float x, float y);
	Vector2(floatArray* v);
	Vector2(Vector2* v);
protected:
	Vector2(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
