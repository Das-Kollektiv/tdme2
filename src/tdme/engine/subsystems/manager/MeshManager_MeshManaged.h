
#pragma once

#include <string>

#include <fwd-tdme.h>
#include <tdme/engine/subsystems/manager/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>

using std::wstring;

using tdme::engine::subsystems::manager::MeshManager;
using tdme::engine::subsystems::object::Object3DGroupMesh;

/** 
 * Managed Mesh entity
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::manager::MeshManager_MeshManaged
{
	friend class MeshManager;

private:
	wstring id {  };
	Object3DGroupMesh* mesh {  };
	int32_t referenceCounter {  };
private:

	/** 
	 * @return mesh id
	 */
	const wstring& getId();

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
	 * @param id
	 * @param mesh
	 */
	MeshManager_MeshManaged(const wstring& id, Object3DGroupMesh* mesh);
};
