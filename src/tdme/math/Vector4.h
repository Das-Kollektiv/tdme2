// Generated from /tdme/src/tdme/math/Vector4.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::math::Vector3;


struct default_init_tag;

/** 
 * Vector 4 class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::math::Vector4 final
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
	 * @param vector v
	 * @param weight
	 */
	void ctor(Vector3* v, float w);

	/** 
	 * Public constructor
	 * @param x
	 * @param y
	 * @param z
	 * @param w
	 */
	void ctor(float x, float y, float z, float w);

	/** 
	 * Public constructor
	 * @param float array containing x,y,z,w values
	 */
	void ctor(floatArray* v);

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
	Vector4* set(floatArray* v);

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
	floatArray* getArray();

	/** 
	 * Clones the vector
	 * @return new cloned vector
	 */
	Vector4* clone() override;

	/** 
	 * @return string representation
	 */
	String* toString() override;

	// Generated
	Vector4();
	Vector4(Vector3* v, float w);
	Vector4(float x, float y, float z, float w);
	Vector4(floatArray* v);
protected:
	Vector4(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
