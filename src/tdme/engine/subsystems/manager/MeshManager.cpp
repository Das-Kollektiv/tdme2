#include <tdme/engine/subsystems/manager/MeshManager.h>

#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/rendering/ObjectNodeMesh.h>
#include <tdme/utilities/Console.h>

using std::string;
using std::unordered_map;

using tdme::engine::subsystems::manager::MeshManager;
using tdme::engine::subsystems::rendering::ObjectNodeMesh;
using tdme::utilities::Console;

MeshManager::MeshManager()
{
}

MeshManager::~MeshManager() {
	for (const auto& [meshManagedId, meshManaged]: meshes) delete meshManaged;
}

void MeshManager::addMesh(const string& meshId, ObjectNodeMesh* mesh)
{
	// create managed texture
	auto meshManaged = new ManagedMesh(meshId, mesh);
	meshManaged->incrementReferenceCounter();
	// add it to our textures
	meshes[meshManaged->getId()] = meshManaged;
}

void MeshManager::removeMesh(const string& meshId)
{
	auto managedMeshIt = meshes.find(meshId);
	if (managedMeshIt != meshes.end()) {
		auto meshManaged = managedMeshIt->second;
		if (meshManaged->decrementReferenceCounter()) {
			// remove from our list
			meshes.erase(managedMeshIt);
			delete meshManaged;
		}
		return;
	}
	Console::printLine(string("Warning: mesh not managed by mesh manager: " + meshId));
}
