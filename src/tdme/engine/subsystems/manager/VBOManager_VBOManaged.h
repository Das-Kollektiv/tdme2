// Generated from /tdme/src/tdme/engine/subsystems/manager/VBOManager.java

#pragma once

#include <string>

#include <fwd-tdme.h>
#include <tdme/engine/subsystems/manager/fwd-tdme.h>
#include <Array.h>

using std::wstring;

using tdme::engine::subsystems::manager::VBOManager;

/** 
 * Managed VBO entity
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::manager::VBOManager_VBOManaged
{
	friend class VBOManager;

private:
	wstring id {  };
	int32_tArray* vboGlIds {  };
	int32_t referenceCounter {  };
	bool uploaded {  };

public:

	/** 
	 * @return vbo id
	 */
	virtual const wstring& getId();

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

private:
	VBOManager_VBOManaged(const wstring& id, int32_tArray* vboGlIds);
};
