#include <tdme/engine/primitives/TerrainMesh.h>

#include <vector>

//#include <ext/reactphysics3d/src/collision/shapes/TerrainMeshShape.h>

#include <tdme/engine/Object3DModel.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Triangle.h>

using std::vector;

using tdme::engine::primitives::TerrainMesh;
using tdme::engine::Object3DModel;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Triangle;

TerrainMesh::TerrainMesh()
{
}

TerrainMesh::TerrainMesh(Object3DModel* model)
{
	vector<Triangle> triangles;
	model->getFaceTriangles(&triangles);
}
