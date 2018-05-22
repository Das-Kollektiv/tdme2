#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/primitives/ConvexMeshBoundingVolume.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/math/Vector3.h>

using std::vector;

using tdme::engine::primitives::ConvexMeshBoundingVolume;
using tdme::engine::primitives::Triangle;
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
	vector<int> facesVerticesCount;
	vector<int> indices;

	/**
	 * Public constructor
	 * @param vertices
	 * @param faces vertices count
	 * @param indices
	 */
	ConvexMesh(const vector<Vector3>& vertices, const vector<int>& facesVerticesCount, const vector<int>& indices);

	/**
	 * Checks if vertex lives on triangle plane
	 * @param triangle
	 * @param vertex
	 * @return if vertex lives on triangle plane
	 */
	bool isVertexOnTrianglePlane(Triangle& triangle, const Vector3& vertex);

public:
	// overriden methods
	bool setScale(const Vector3& scale) override;
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
