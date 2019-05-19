#pragma once

#include <map>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/manager/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/utils/fwd-tdme.h>

using std::map;
using std::string;

using tdme::engine::subsystems::manager::VBOManager_VBOManaged;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::os::threading::Mutex;

/** 
 * VBO manager
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::manager::VBOManager final
{
	friend class VBOManager_VBOManaged;

private:
	Renderer* renderer {  };
	map<string, VBOManager_VBOManaged*> vbos {  };
	Mutex mutex;

public:

	/** 
	 * Adds a VBO to manager
	 * @param vboId VBO id
	 * @param ids VBOs to allocate
	 * @param use GPU memory
	 */
	VBOManager_VBOManaged* addVBO(const string& vboId, int32_t ids, bool useGPUMemory);

	/** 
	 * Removes a VBO from manager
	 * @param vboId VBO id
	 */
	void removeVBO(const string& vboId);

	/**
	 * Public constructor
	 */
	VBOManager(Renderer* renderer);

	/**
	 * Destructor
	 */
	~VBOManager();
};
