#include <tdme/engine/subsystems/manager/MeshManager_MeshManaged.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/manager/MeshManager.h>
#include <tdme/engine/subsystems/rendering/ObjectNodeMesh.h>

using std::string;

using tdme::engine::subsystems::manager::MeshManager;
using tdme::engine::subsystems::manager::MeshManager_MeshManaged;
using tdme::engine::subsystems::rendering::ObjectNodeMesh;

MeshManager_MeshManaged::MeshManager_MeshManaged(const string& id, ObjectNodeMesh* mesh)
{
	this->id = id;
	this->mesh = mesh;
}

MeshManager_MeshManaged::~MeshManager_MeshManaged() {
	delete mesh;
}
