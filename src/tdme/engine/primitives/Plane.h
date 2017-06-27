// Generated from /tdme/src/tdme/engine/primitives/Plane.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::math::Vector3;


struct default_init_tag;

/** 
 * Plane
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::primitives::Plane final
	: public Object
{

public:
	typedef Object super;

public: /* protected */
	Vector3* normal {  };
	float distance {  };
protected:

	/** 
	 * Public default constructor
	 */
	void ctor();

	/** 
	 * Public constructor
	 * @param normal
	 * @param distance
	 */
	void ctor(Vector3* normal, float distance);

public:

	/** 
	 * @return float distance from origin
	 */
	float getDistance();

	/** 
	 * Set up distance from origin
	 * @param distance
	 */
	void setDistance(float distance);

	/** 
	 * @return normal
	 */
	Vector3* getNormal();
	String* toString() override;

	// Generated
	Plane();
	Plane(Vector3* normal, float distance);
protected:
	Plane(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
