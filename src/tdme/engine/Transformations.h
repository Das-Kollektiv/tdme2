// Generated from /tdme/src/tdme/engine/Transformations.java

#pragma once

#include <tdme/engine/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>

using tdme::engine::Rotations;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/** 
 * Transformations
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::Transformations {
public: /* protected */
	Vector3* translation {  };
	Matrix4x4* translationMatrix {  };
	Vector3* scale {  };
	Matrix4x4* scaleMatrix {  };
	Rotations* rotations {  };
	Matrix4x4* rotationsQuaternionMatrix {  };
	Matrix4x4* rotationsMatrix {  };
	Vector3* rotationsPivot {  };
	Matrix4x4* rotationsTranslationsMatrix {  };
	Vector3* pivot {  };
	Matrix4x4* transformationsMatrix {  };
public:

	/** 
	 * @return object translation
	 */
	virtual Vector3* getTranslation();

	/** 
	 * @return object scale
	 */
	virtual Vector3* getScale();

	/** 
	 * @return pivot or center of rotations
	 */
	virtual Vector3* getPivot();

	/** 
	 * @return object rotations
	 */
	virtual Rotations* getRotations();

	/** 
	 * @return this transformations matrix
	 */
	virtual Matrix4x4* getTransformationsMatrix();

	/** 
	 * Set up this transformations from given transformations
	 * @param transformations
	 */
	virtual void fromTransformations(Transformations* transformations);

	/** 
	 * Computes transformation matrix
	 */
	virtual void update();

	/**
	 * Public constructor
	 */
	Transformations();
};
