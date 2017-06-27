// Generated from /tdme/src/tdme/math/Quaternion.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;


struct default_init_tag;

/** 
 * Quaternion
 * @author Andreas Drewke
 * @see http://db-in.com/blog/2011/04/cameras-on-opengl-es-2-x/
 */
class tdme::math::Quaternion final
	: public Object
{

public:
	typedef Object super;

public: /* protected */
	floatArray* data {  };
	floatArray* _data {  };

private:
	Vector3* t {  };
	Vector3* q {  };
	Vector3* qxt {  };
protected:

	/** 
	 * Public constructor
	 */
	void ctor();

	/** 
	 * P
	 * @param q
	 * @return
	 */
	void ctor(Quaternion* q);

	/** 
	 * Public constructor
	 * @param x
	 * @param y
	 * @param z
	 * @param w
	 */
	void ctor(float x, float y, float z, float w);

public:

	/** 
	 * Set up this quaternion by components
	 * @param x
	 * @param y
	 * @param z
	 * @param w
	 */
	Quaternion* set(float x, float y, float z, float w);
protected:

	/** 
	 * Public constructor
	 * @param x
	 * @param y
	 * @param z
	 * @param w
	 */
	void ctor(Vector3* v, float w);

public:

	/** 
	 * Sets up this quaternion by quaternion q
	 * @param q
	 * @return
	 */
	Quaternion* set(Quaternion* q);

	/** 
	 * Set quaternion
	 * @param x
	 * @param y
	 * @param z
	 * @param w
	 */
	Quaternion* set(Vector3* v, float w);

	/** 
	 * Set up quaternion identity
	 * @return this quaternion
	 */
	Quaternion* identity();

	/** 
	 * Inverts this quaternion
	 * @return this quaternion
	 */
	Quaternion* invert();

	/** 
	 * Creates a rotation quaternion
	 * @param angle
	 * @param axis
	 * @return this quaternion
	 */
	Quaternion* rotate(float angle, Vector3* v);

	/** 
	 * Normalize quaternion
	 */
	Quaternion* normalize();

	/** 
	 * Multiplies this quaternion with quaternion q
	 * @param quaterion q
	 * @return this quaternion
	 */
	Quaternion* multiply(Quaternion* q);

	/** 
	 * Multiplies this quaternion with quaternion q
	 * @param quaterion q
	 * @return this quaternion
	 */
	Quaternion* add(Quaternion* q);

	/** 
	 * Scales this quaternion with given value
	 * @param value
	 * @return this quaternion
	 */
	Quaternion* scale(float value);

	/** 
	 * Multiplies a quaternion with given vector v
	 * @param vector v
	 * @param dest
	 * @return dest
	 */
	Vector3* multiply(Vector3* v, Vector3* dest);

	/** 
	 * Computes a matrix from given
	 * @param destination matrix
	 * @return destination matrix  
	 */
	Matrix4x4* computeMatrix(Matrix4x4* matrix);

	/** 
	 * Returns array data
	 * @return array data
	 */
	floatArray* getArray();

	/** 
	 * @return string representation
	 */
	String* toString() override;

	// Generated
	Quaternion();
	Quaternion(Quaternion* q);
	Quaternion(float x, float y, float z, float w);
	Quaternion(Vector3* v, float w);
protected:
	Quaternion(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
