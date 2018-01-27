#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/primitives/ConvexMeshBoundingVolume.h>

using std::vector;

using tdme::engine::primitives::ConvexMeshBoundingVolume;
using tdme::engine::Object3DModel;
using tdme::math::Vector3;

/** 
 * Convex mesh collision object
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::primitives::ConvexMesh final
	: public ConvexMeshBoundingVolume
{
private:
	vector<Vector3> vertices;
	vector<int> indices;

	/**
	 * Public constructor
	 * @param vertices
	 * @param indices
	 */
	ConvexMesh(const vector<Vector3>& vertices, const vector<int>& indices);

public:
	// overriden methods
	BoundingVolume* clone() const override;

	/**
	 * @return vertices
	 */
	const vector<Vector3>& getVertices();

	/**
	 * Public constructor
	 */
	ConvexMesh();

	/**
	 * Public constructor
	 * @param model
	 */
	ConvexMesh(Object3DModel* model);

};
