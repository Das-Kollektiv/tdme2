// Generated from /tdme/src/tdme/engine/subsystems/manager/MeshManager.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/subsystems/manager/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::engine::subsystems::manager::MeshManager;
using tdme::engine::subsystems::object::Object3DGroupMesh;


struct default_init_tag;

/** 
 * Managed Mesh entity
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::manager::MeshManager_MeshManaged
	: public virtual Object
{

public:
	typedef Object super;

public: /* package */
	String* id {  };
	Object3DGroupMesh* mesh {  };
	int32_t referenceCounter {  };
protected:

	/** 
	 * Protected constructor
	 * @param id
	 * @param vbo gl id
	 * @param referenceCounter
	 */
	void ctor(String* id, Object3DGroupMesh* mesh);

private:

	/** 
	 * @return mesh id
	 */
	String* getId();

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

public:

	/** 
	 * @return string representation
	 */
	String* toString() override;

	// Generated

private:
	MeshManager_MeshManaged(MeshManager *MeshManager_this, String* id, Object3DGroupMesh* mesh);
protected:
	MeshManager_MeshManaged(MeshManager *MeshManager_this, const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	MeshManager *MeshManager_this;

private:
	virtual ::java::lang::Class* getClass0();
	friend class MeshManager;
};
