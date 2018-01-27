#pragma once

#include <array>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/ConvexMeshBoundingVolume.h>
#include <tdme/engine/primitives/Triangle.h>

using std::array;
using std::vector;

using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::ConvexMeshBoundingVolume;
using tdme::engine::Object3DModel;
using tdme::math::Vector3;

/** 
 * Terrain convex mesh collision object
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::primitives::TerrainConvexMesh final
	: public ConvexMeshBoundingVolume
{
private:
	Vector3 positionTransformed;
	Triangle triangle;
	Triangle triangleTransformed;
	float height;

	/**
	 * Create convex mesh
	 */
	void createConvexMesh();

public:
	/**
	 * Copy assignment operator
	 */
	TerrainConvexMesh& operator=(const TerrainConvexMesh& other);

	/**
	 * Create terrain convex meshes
	 * @param model
	 * @param convex meshes
	 * @param height
	 */
	static void createTerrainConvexMeshes(Object3DModel* model, vector<TerrainConvexMesh>* convexMeshes, float height = 0.75f);

	/**
	 * @return position transformed
	 */
	const Vector3& getPositionTransformed() const;

	/**
	 * Apply transformations, needs to be used if having any transform for the convex terrain mesh
	 * @param transformations
	 */
	void applyTransformations(Transformations* transformations);

	// overrides
	void fromTransformations(Transformations* transformations) override;
	BoundingVolume* clone() const override;

	/**
	 * Public constructor
	 */
	TerrainConvexMesh(const TerrainConvexMesh& other);

	/**
	 * Public constructor
	 */
	TerrainConvexMesh();

	/**
	 * Public constructor
	 * @param triangle
	 */
	TerrainConvexMesh(const Triangle& triangle, float height = 0.75f);

};
