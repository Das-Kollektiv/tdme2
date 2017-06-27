// Generated from /tdme/src/tdme/engine/subsystems/manager/MeshManager.java

#pragma once

#include <java/lang/fwd-tdme.h>
#include <tdme/engine/subsystems/manager/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::engine::subsystems::manager::MeshManager_MeshManaged;
using tdme::engine::subsystems::object::Object3DGroupMesh;
using tdme::utils::_HashMap;


struct default_init_tag;

/** 
 * Mesh manager
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::manager::MeshManager final
	: public Object
{

public:
	typedef Object super;

private:
	_HashMap* meshes {  };
protected:

	/** 
	 * Public constructor
	 */
	void ctor();

public:

	/** 
	 * Get mesh from managed meshes
	 * @param meshId
	 * @return object 3d group mesh or null
	 */
	Object3DGroupMesh* getMesh(String* meshId);

	/** 
	 * Adds a mesh to manager
	 * @param mesh id
	 * @param mesh
	 */
	void addMesh(String* meshId, Object3DGroupMesh* mesh);

	/** 
	 * Removes a mesh from manager
	 * @param gl
	 * @param texture
	 */
	void removeMesh(String* meshId);

	// Generated
	MeshManager();
protected:
	MeshManager(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
	friend class MeshManager_MeshManaged;
};
