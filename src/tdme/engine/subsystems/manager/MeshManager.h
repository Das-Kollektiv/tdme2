#pragma once

#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/manager/MeshManager_MeshManaged.h>
#include <tdme/engine/subsystems/manager/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;
using std::unordered_map;

using tdme::engine::subsystems::manager::MeshManager_MeshManaged;
using tdme::engine::subsystems::rendering::ObjectNodeMesh;

/**
 * Mesh manager
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::manager::MeshManager final
{
private:
	unordered_map<string, MeshManager_MeshManaged*> meshes;

public:
	// forbid class copy
	FORBID_CLASS_COPY(MeshManager)

	/**
	 * Public constructor
	 */
	MeshManager();

	/**
	 * Destructor
	 */
	~MeshManager();

	/**
	 * Get mesh from managed meshes
	 * @param meshId mesh id
	 * @return object node mesh or null
	 */
	inline ObjectNodeMesh* getMesh(const string& meshId) {
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

	/**
	 * Adds a mesh to manager
	 * @param meshId mesh id
	 * @param mesh mesh
	 */
	void addMesh(const string& meshId, ObjectNodeMesh* mesh);

	/**
	 * Removes a mesh from manager
	 * @param meshId mesh id
	 */
	void removeMesh(const string& meshId);

};
