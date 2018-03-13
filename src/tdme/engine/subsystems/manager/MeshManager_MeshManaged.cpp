#include <tdme/engine/subsystems/manager/MeshManager_MeshManaged.h>

#include <string>

#include <tdme/engine/subsystems/manager/MeshManager.h>
#include <tdme/engine/subsystems/rendering/Object3DGroupMesh.h>

using std::string;

using tdme::engine::subsystems::manager::MeshManager_MeshManaged;
using tdme::engine::subsystems::manager::MeshManager;
using tdme::engine::subsystems::rendering::Object3DGroupMesh;

MeshManager_MeshManaged::MeshManager_MeshManaged(const string& id, Object3DGroupMesh* mesh)
{
	this->id = id;
	this->mesh = mesh;
	this->referenceCounter = 0;
}

const string& MeshManager_MeshManaged::getId()
{
	return id;
}

Object3DGroupMesh* MeshManager_MeshManaged::getMesh()
{
	return mesh;
}

int32_t MeshManager_MeshManaged::getReferenceCounter()
{
	return referenceCounter;
}

bool MeshManager_MeshManaged::decrementReferenceCounter()
{
	referenceCounter--;
	return referenceCounter == 0;
}

void MeshManager_MeshManaged::incrementReferenceCounter()
{
	referenceCounter++;
}
