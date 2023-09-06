#include <tdme/engine/subsystems/manager/MeshManager_MeshManaged.h>

#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/manager/MeshManager.h>
#include <tdme/engine/subsystems/rendering/ObjectNodeMesh.h>

using std::string;
using std::unique_ptr;

using tdme::engine::subsystems::manager::MeshManager;
using tdme::engine::subsystems::manager::MeshManager_MeshManaged;
using tdme::engine::subsystems::rendering::ObjectNodeMesh;

MeshManager_MeshManaged::MeshManager_MeshManaged(const string& id, ObjectNodeMesh* mesh)
{
	this->id = id;
	this->mesh = unique_ptr<ObjectNodeMesh>(mesh);
}

MeshManager_MeshManaged::~MeshManager_MeshManaged() {
}
