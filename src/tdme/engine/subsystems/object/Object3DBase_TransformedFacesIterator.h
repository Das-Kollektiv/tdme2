
#pragma once

#include <array>

#include <fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Matrix4x4.h>

using std::array;

using tdme::engine::subsystems::object::Object3DBase;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/** 
 * Transformed faces iterator
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::object::Object3DBase_TransformedFacesIterator
{
private:
	Object3DBase* object3DBase {  };
	array<Vector3, 3> vertices {  };
	Matrix4x4 matrix {  };
	int32_t faceCount {  };
	int32_t faceIdxTotal {  };
	int32_t faceIdx {  };
	int32_t object3DGroupIdx {  };
	int32_t facesEntityIdx {  };
private:

	/** 
	 * Reset
	 */
	void reset();
public:
	/**
	 * Return iterator ready to iterate
	 */
	Object3DBase_TransformedFacesIterator* iterator();

	/**
	 * Has next
	 */
	bool hasNext();

	/**
	 * Retrieve next triangle
	 * @return next 3 triangle vectors
	 */
	array<Vector3, 3>* next();

	/**
	 * Public constructor
	 */
	Object3DBase_TransformedFacesIterator(Object3DBase* object3DBase);
};
