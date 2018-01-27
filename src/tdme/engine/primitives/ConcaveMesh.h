#pragma once

#include <ext/reactphysics3d/src/collision/TriangleVertexArray.h>
#include <ext/reactphysics3d/src/collision/TriangleMesh.h>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/ByteBuffer.h>
#include <tdme/utils/FloatBuffer.h>
#include <tdme/utils/IntBuffer.h>

using tdme::engine::primitives::BoundingVolume;
using tdme::math::Vector3;
using tdme::utils::ByteBuffer;
using tdme::utils::FloatBuffer;
using tdme::utils::IntBuffer;

/** 
 * Concave mesh, not yet tested with reactphysics3d-develop
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::primitives::ConcaveMesh final
	: public BoundingVolume
{
private:
	ByteBuffer* verticesByteBuffer;
	ByteBuffer* indicesByteBuffer;
	reactphysics3d::TriangleVertexArray* triangleVertexArray;
	reactphysics3d::TriangleMesh triangleMesh;

public:
	// overrides
	void fromTransformations(Transformations* transformations);
	BoundingVolume* clone() const override;

	/**
	 * Public constructor
	 * @param model
	 * @param transformations
	 */
	ConcaveMesh(Object3DModel* model, Transformations* transformations = nullptr);

	/**
	 * Public destructor
	 */
	~ConcaveMesh();

};
