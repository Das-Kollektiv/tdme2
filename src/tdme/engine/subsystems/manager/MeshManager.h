#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/manager/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;
using std::unordered_map;
using std::unique_ptr;

using tdme::engine::subsystems::rendering::ObjectNodeMesh;

/**
 * Mesh manager
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::manager::MeshManager final
{
public:
	/**
	 * Managed mesh
	 */
	class ManagedMesh final
	{
		friend class MeshManager;

	private:
		string id;
		unique_ptr<ObjectNodeMesh> mesh;
		int32_t referenceCounter { 0 };

	private:
		// forbid class copy
		FORBID_CLASS_COPY(ManagedMesh)

		/**
		 * Protected constructor
		 * @param id id
		 * @param mesh mesh
		 */
		ManagedMesh(const string& id, ObjectNodeMesh* mesh): id(id), mesh(mesh) {
			//
		}

	public:
		/**
		 * @returns mesh id
		 */
		inline const string& getId() {
			return id;
		}

		/**
		 * @returns object node mesh
		 */
		inline ObjectNodeMesh* getMesh() {
			return mesh.get();
		}

		/**
		 * @returns reference counter
		 */
		inline int32_t getReferenceCounter() {
			return referenceCounter;
		}

	private:
		/**
		 * decrement reference counter
		 * @returns if reference counter = 0
		 */
		inline bool decrementReferenceCounter() {
			referenceCounter--;
			return referenceCounter == 0;
		}

		/**
		 * increment reference counter
		 */
		inline void incrementReferenceCounter() {
			referenceCounter++;
		}

	};

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
	 * @returns object node mesh or null
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

private:
	unordered_map<string, ManagedMesh*> meshes;

};
