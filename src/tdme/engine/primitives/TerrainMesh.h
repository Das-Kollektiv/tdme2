#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Triangle.h>

using std::vector;

using tdme::engine::primitives::TerrainMesh;
using tdme::engine::primitives::Triangle;
using tdme::engine::Object3DModel;

/** 
 * Terrain mesh collision object
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::primitives::TerrainMesh final
	: public BoundingVolume
{
private:
	vector<Vector3> vertices;
	vector<int32_t> indices;
public:
	/**
	 * Public constructor
	 */
	TerrainMesh();

	/**
	 * Public constructor
	 * @param model
	 */
	TerrainMesh(Object3DModel* model);

};
