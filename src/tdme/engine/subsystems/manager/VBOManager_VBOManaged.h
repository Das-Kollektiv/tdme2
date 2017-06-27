// Generated from /tdme/src/tdme/engine/subsystems/manager/VBOManager.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/subsystems/manager/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::engine::subsystems::manager::VBOManager;


struct default_init_tag;

/** 
 * Managed VBO entity
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::manager::VBOManager_VBOManaged
	: public virtual Object
{

public:
	typedef Object super;

private:
	String* id {  };
	int32_tArray* vboGlIds {  };
	int32_t referenceCounter {  };
	bool uploaded {  };
protected:

	/** 
	 * Protected constructor
	 * @param id
	 * @param vbo gl id
	 * @param referenceCounter
	 */
	void ctor(String* id, int32_tArray* vboGlIds);

public:

	/** 
	 * @return vbo id
	 */
	virtual String* getId();

	/** 
	 * @return vbo gl ids
	 */
	virtual int32_tArray* getVBOGlIds();

private:

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
	 * @return if vbo's have been uploaded, will change internal flag to uploaded
	 */
	virtual bool isUploaded();

	/** 
	 * @return string representation
	 */
	String* toString() override;

	// Generated

private:
	VBOManager_VBOManaged(VBOManager *VBOManager_this, String* id, int32_tArray* vboGlIds);
protected:
	VBOManager_VBOManaged(VBOManager *VBOManager_this, const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	VBOManager *VBOManager_this;

private:
	virtual ::java::lang::Class* getClass0();
	friend class VBOManager;
};
