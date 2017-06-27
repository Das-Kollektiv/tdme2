// Generated from /tdme/src/tdme/math/Matrix4x4Negative.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;


struct default_init_tag;

/** 
 * Class to check if matrix is negative
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::math::Matrix4x4Negative
	: public virtual Object
{

public:
	typedef Object super;

public: /* protected */
	Vector3* xAxis {  };
	Vector3* yAxis {  };
	Vector3* zAxis {  };
	Vector3* tmpAxis {  };
protected:

	/** 
	 * Public constructor
	 */
	void ctor();

public:

	/** 
	 * Check if matrix is negative
	 * @param matrix
	 * @return negative
	 */
	virtual bool isNegative(Matrix4x4* matrix);

	// Generated
	Matrix4x4Negative();
protected:
	Matrix4x4Negative(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
