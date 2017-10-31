
#pragma once

#include <vector>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/manager/fwd-tdme.h>

using std::string;
using std::vector;

using tdme::engine::subsystems::manager::VBOManager;

/** 
 * Managed VBO entity
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::manager::VBOManager_VBOManaged
{
	friend class VBOManager;

private:
	string id {  };
	vector<int32_t> vboGlIds {  };
	int32_t referenceCounter {  };
	bool uploaded {  };

public:

	/** 
	 * @return vbo id
	 */
	virtual const string& getId();

	/** 
	 * @return vbo gl ids
	 */
	virtual vector<int32_t>* getVBOGlIds();

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
	VBOManager_VBOManaged(const string& id, vector<int32_t>* vboGlIds);
};
