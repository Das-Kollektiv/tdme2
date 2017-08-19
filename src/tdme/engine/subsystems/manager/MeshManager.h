// Generated from /tdme/src/tdme/engine/subsystems/manager/MeshManager.java

#pragma once

#include <map>
#include <string>

#include <tdme/engine/subsystems/manager/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::map;
using std::wstring;

using tdme::engine::subsystems::manager::MeshManager_MeshManaged;
using tdme::engine::subsystems::object::Object3DGroupMesh;

/** 
 * Mesh manager
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::manager::MeshManager final
{
private:
	map<wstring, MeshManager_MeshManaged*> meshes {  };

public:

	/** 
	 * Get mesh from managed meshes
	 * @param meshId
	 * @return object 3d group mesh or null
	 */
	Object3DGroupMesh* getMesh(const wstring& meshId);

	/** 
	 * Adds a mesh to manager
	 * @param mesh id
	 * @param mesh
	 */
	void addMesh(const wstring& meshId, Object3DGroupMesh* mesh);

	/** 
	 * Removes a mesh from manager
	 * @param gl
	 * @param texture
	 */
	void removeMesh(const wstring& meshId);

	/**
	 * Public constructor
	 */
	MeshManager();
};
