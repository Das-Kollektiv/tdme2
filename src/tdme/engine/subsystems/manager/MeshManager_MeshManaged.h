
#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/manager/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>

using std::string;

using tdme::engine::subsystems::manager::MeshManager;
using tdme::engine::subsystems::rendering::Object3DGroupMesh;

/** 
 * Managed Mesh entity
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::manager::MeshManager_MeshManaged
{
	friend class MeshManager;

private:
	string id {  };
	Object3DGroupMesh* mesh {  };
	int32_t referenceCounter {  };
private:

	/** 
	 * @return mesh id
	 */
	const string& getId();

	/** 
	 * @return object 3d group mesh
	 */
	Object3DGroupMesh* getMesh();

	/** 
	 * @return reference counter
	 */
	int32_t getReferenceCounter();

	/** 
	 * decrement reference counter
	 * @return if reference counter = 0
	 */
	bool decrementReferenceCounter();

	/** 
	 * increment reference counter
	 */
	void incrementReferenceCounter();

	/** 
	 * Protected constructor
	 * @param id id
	 * @param mesh mesh
	 */
	MeshManager_MeshManaged(const string& id, Object3DGroupMesh* mesh);
};
