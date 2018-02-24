#pragma once

#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Rotations.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Matrix4x4.h>

using tdme::engine::Rotations;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/** 
 * Transformations
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::Transformations {
private:
	Vector3 translation {  };
	Vector3 scale {  };
	Vector3 pivot {  };
	Rotations rotations {  };
	Matrix4x4 transformationsMatrix {  };

public:

	/** 
	 * @return object translation
	 */
	virtual Vector3& getTranslation();

	/** 
	 * @return object scale
	 */
	virtual Vector3& getScale();

	/** 
	 * @return pivot or center of rotations
	 */
	virtual Vector3& getPivot();

	/** 
	 * @return object rotations
	 */
	virtual Rotations* getRotations();

	/** 
	 * @return this transformations matrix
	 */
	virtual const Matrix4x4& getTransformationsMatrix() const;

	/** 
	 * Set up this transformations from given transformations
	 * @param transformations
	 */
	virtual void fromTransformations(const Transformations& transformations);

	/** 
	 * Computes transformation matrix
	 */
	virtual void update();

	/**
	 * Invert this transformations
	 */
	virtual void invert();

	/**
	 * Public constructor
	 */
	Transformations();

	/**
	 * Destructor
	 */
	virtual ~Transformations();
};
