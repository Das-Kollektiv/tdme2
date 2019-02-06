#pragma once

#include <vector>

#include <ext/reactphysics3d/src/collision/PolyhedronMesh.h>
#include <ext/reactphysics3d/src/collision/PolygonVertexArray.h>

#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/FloatBuffer.h>
#include <tdme/utils/IntBuffer.h>

using std::vector;

using tdme::math::Vector3;
using tdme::utils::ByteBuffer;
using tdme::utils::FloatBuffer;
using tdme::utils::IntBuffer;

/** 
 * Convex mesh physics primitive base class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::primitives::ConvexMeshBoundingVolume: public BoundingVolume
{
private:
	vector<reactphysics3d::PolygonVertexArray::PolygonFace> faces;
	reactphysics3d::PolygonVertexArray* polygonVertexArray {  };
	reactphysics3d::PolyhedronMesh* polyhedronMesh {  };
	ByteBuffer* verticesByteBuffer {  };
	ByteBuffer* indicesByteBuffer {  };

protected:

	/**
	 * Create convex mesh
	 * 	Note: it also translates center into origin
	 * @param vertices vertices
	 * @param facesVerticesCount faces vertices count
	 * @param indices indices
	 * @param scale scale
	 */
	void createConvexMesh(const vector<Vector3>& vertices, const vector<int>& facesVerticesCount, const vector<int>& indices, const Vector3& scale);

	/**
	 * Destructor
	 */
	virtual ~ConvexMeshBoundingVolume();

};
