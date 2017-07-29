// Generated from /tdme/src/tdme/math/Matrix4x4Negative.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>

using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/** 
 * Class to check if matrix is negative
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::math::Matrix4x4Negative
{
public: /* protected */
	Vector3 xAxis {  };
	Vector3 yAxis {  };
	Vector3 zAxis {  };
	Vector3 tmpAxis {  };
public:

	/** 
	 * Check if matrix is negative
	 * @param matrix
	 * @return negative
	 */
	virtual bool isNegative(Matrix4x4* matrix);

	/**
	 * Public constructor
	 */
	Matrix4x4Negative();
};
