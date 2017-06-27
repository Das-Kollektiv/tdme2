// Generated from /tdme/src/tdme/engine/Rotation.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::math::Quaternion;
using tdme::math::Vector3;


struct default_init_tag;

/** 
 * Rotation
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::Rotation final
	: public Object
{

public:
	typedef Object super;
	static Vector3* X_AXIS;
	static Vector3* Y_AXIS;
	static Vector3* Z_AXIS;

private:
	float angle {  };
	Vector3* axis {  };
	Quaternion* quaternion {  };
protected:

	/** 
	 * Public default constructor
	 */
	void ctor();

	/** 
	 * Public constructor
	 * @param angle
	 * @param axis
	 */
	void ctor(float angle, Vector3* axis);

public:

	/** 
	 * @return angle
	 */
	float getAngle();

	/** 
	 * @param angle
	 */
	void setAngle(float angle);

	/** 
	 * @return axis
	 */
	Vector3* getAxix();

	/** 
	 * @return quaternion
	 */
	Quaternion* getQuaternion();

	/** 
	 * Sets up this rotation from another rotation
	 * @param rotation
	 */
	void fromRotation(Rotation* rotation);

	/** 
	 * Sets up this rotation from quaternion, current quaternion will be lost, needs to get updated
	 * @param q
	 */
	void fromQuaternion(Quaternion* q);

	/** 
	 * Computes rotation matrix
	 */
	void update();
	String* toString() override;

	// Generated
	Rotation();
	Rotation(float angle, Vector3* axis);
protected:
	Rotation(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static void clinit();

private:
	virtual ::java::lang::Class* getClass0();
};
