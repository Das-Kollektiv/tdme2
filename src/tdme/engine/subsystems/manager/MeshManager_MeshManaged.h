#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/manager/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>

using std::string;

using tdme::engine::subsystems::manager::MeshManager;
using tdme::engine::subsystems::rendering::ObjectNodeMesh;

/**
 * Managed mesh entity
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::manager::MeshManager_MeshManaged final
{
	friend class MeshManager;

private:
	string id;
	ObjectNodeMesh* mesh { nullptr };
	int32_t referenceCounter { 0 };

private:
	// forbid class copy
	FORBID_CLASS_COPY(MeshManager_MeshManaged)

	/**
	 * Protected constructor
	 * @param id id
	 * @param mesh mesh
	 */
	MeshManager_MeshManaged(const string& id, ObjectNodeMesh* mesh);

	/**
	 * Protected Denstructor
	 */
	~MeshManager_MeshManaged();

	/**
	 * @return mesh id
	 */
	inline const string& getId() {
		return id;
	}

	/**
	 * @return object node mesh
	 */
	inline ObjectNodeMesh* getMesh() {
		return mesh;
	}

	/**
	 * @return reference counter
	 */
	inline int32_t getReferenceCounter() {
		return referenceCounter;
	}

	/**
	 * decrement reference counter
	 * @return if reference counter = 0
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
