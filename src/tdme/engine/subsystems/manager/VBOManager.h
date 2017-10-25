
#pragma once

#include <map>
#include <string>

#include <tdme.h>
#include <tdme/engine/subsystems/manager/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::map;
using std::string;

using tdme::engine::subsystems::manager::VBOManager_VBOManaged;
using tdme::engine::subsystems::renderer::GLRenderer;

/** 
 * VBO manager
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::manager::VBOManager final
{
	friend class VBOManager_VBOManaged;

private:
	GLRenderer* renderer {  };
	map<string, VBOManager_VBOManaged*> vbos {  };

public:

	/** 
	 * Adds a vbo to manager / open gl stack
	 * @param gl
	 * @param texture
	 * @param vbo id count
	 */
	VBOManager_VBOManaged* addVBO(const string& vboId, int32_t ids);

	/** 
	 * Removes a vbo from manager / open gl stack
	 * @param gl
	 * @param texture
	 */
	void removeVBO(const string& vboId);

	/**
	 * Public constructor
	 */
	VBOManager(GLRenderer* renderer);

	/**
	 * Destructor
	 */
	~VBOManager();
};
