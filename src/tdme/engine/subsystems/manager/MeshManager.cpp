#include <tdme/engine/subsystems/manager/MeshManager.h>

#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/manager/MeshManager_MeshManaged.h>
#include <tdme/engine/subsystems/rendering/ObjectNodeMesh.h>
#include <tdme/utilities/Console.h>

using std::string;
using std::unordered_map;

using tdme::engine::subsystems::manager::MeshManager;
using tdme::engine::subsystems::manager::MeshManager_MeshManaged;
using tdme::engine::subsystems::rendering::ObjectNodeMesh;
using tdme::utilities::Console;

MeshManager::MeshManager()
{
}

MeshManager::~MeshManager() {
	for (const auto& [meshManagedId, meshManaged]: meshes) delete meshManaged;
}

ObjectNodeMesh* MeshManager::getMesh(const string& meshId)
{
	// check if we already manage this mesh
	auto meshManagedIt = meshes.find(meshId);
	if (meshManagedIt != meshes.end()) {
		auto meshManaged = meshManagedIt->second;
		meshManaged->incrementReferenceCounter();
		return meshManaged->getMesh();
	}
	// otherwise no mesh
	return nullptr;
}

void MeshManager::addMesh(const string& meshId, ObjectNodeMesh* mesh)
{
	// create managed texture
	auto meshManaged = new MeshManager_MeshManaged(meshId, mesh);
	meshManaged->incrementReferenceCounter();
	// add it to our textures
	meshes[meshManaged->getId()] = meshManaged;
}

void MeshManager::removeMesh(const string& meshId)
{
	auto meshManagedIt = meshes.find(meshId);
	if (meshManagedIt != meshes.end()) {
		auto meshManaged = meshManagedIt->second;
		if (meshManaged->decrementReferenceCounter()) {
			// remove from our list
			meshes.erase(meshManagedIt);
			delete meshManaged;
		}
		return;
	}
	Console::println(string("Warning: mesh not managed by mesh manager: " + meshId));
}
