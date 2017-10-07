#include <tdme/engine/subsystems/manager/MeshManager.h>

#include <map>
#include <string>

#include <tdme/engine/subsystems/manager/MeshManager_MeshManaged.h>
#include <tdme/engine/subsystems/object/Object3DGroupMesh.h>
#include <tdme/utils/Console.h>

using std::map;
using std::wstring;

using tdme::engine::subsystems::manager::MeshManager;
using tdme::engine::subsystems::manager::MeshManager_MeshManaged;
using tdme::engine::subsystems::object::Object3DGroupMesh;
using tdme::utils::Console;

MeshManager::MeshManager() 
{
}

Object3DGroupMesh* MeshManager::getMesh(const wstring& meshId)
{
	auto meshManagedIt = meshes.find(meshId);
	if (meshManagedIt != meshes.end()) {
		auto meshManaged = meshManagedIt->second;
		meshManaged->incrementReferenceCounter();
		return meshManaged->getMesh();
	}
	return nullptr;
}

void MeshManager::addMesh(const wstring& meshId, Object3DGroupMesh* mesh)
{
	auto meshManaged = new MeshManager_MeshManaged(meshId, mesh);
	meshManaged->incrementReferenceCounter();
	meshes[meshManaged->getId()] = meshManaged;
}

void MeshManager::removeMesh(const wstring& meshId)
{
	auto meshManagedIt = meshes.find(meshId);
	if (meshManagedIt != meshes.end()) {
		auto meshManaged = meshManagedIt->second;
		if (meshManaged->decrementReferenceCounter()) {
			meshes.erase(meshManagedIt);
		}
		return;
	}
	Console::println(wstring(L"Warning: mesh not managed by mesh manager: " + meshId));
}
