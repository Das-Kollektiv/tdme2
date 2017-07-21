// Generated from /tdme/src/tdme/engine/subsystems/manager/VBOManager.java

#pragma once

#include <map>
#include <string>

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/subsystems/manager/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using std::map;
using std::wstring;

using java::lang::Object;
using java::lang::String;
using tdme::engine::subsystems::manager::VBOManager_VBOManaged;
using tdme::engine::subsystems::renderer::GLRenderer;


struct default_init_tag;

/** 
 * VBO manager
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::manager::VBOManager final
	: public Object
{

public:
	typedef Object super;

private:
	GLRenderer* renderer {  };
	map<wstring, VBOManager_VBOManaged*> vbos {  };
protected:

	/** 
	 * Public constructor
	 * @param renderer
	 */
	void ctor(GLRenderer* renderer);

public:

	/** 
	 * Adds a vbo to manager / open gl stack
	 * @param gl
	 * @param texture
	 * @param vbo id count
	 */
	VBOManager_VBOManaged* addVBO(String* vboId, int32_t ids);

	/** 
	 * Removes a vbo from manager / open gl stack
	 * @param gl
	 * @param texture
	 */
	void removeVBO(String* vboId);

	// Generated
	VBOManager(GLRenderer* renderer);
protected:
	VBOManager(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
	friend class VBOManager_VBOManaged;
};
