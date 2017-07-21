// Generated from /tdme/src/tdme/engine/subsystems/manager/TextureManager.java

#pragma once

#include <map>
#include <string>

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/subsystems/manager/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using std::map;
using std::wstring;

using java::lang::Object;
using java::lang::String;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::subsystems::manager::TextureManager_TextureManaged;
using tdme::engine::subsystems::renderer::GLRenderer;


struct default_init_tag;

/** 
 * Texture manager
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::manager::TextureManager final
	: public Object
{

public:
	typedef Object super;

private:
	GLRenderer* renderer {  };
	map<wstring, TextureManager_TextureManaged*> textures {  };
protected:

	/** 
	 * Public constructor
	 * @param renderer
	 */
	void ctor(GLRenderer* renderer);

public:

	/** 
	 * Adds a texture to manager / open gl stack
	 * @param texture
	 * @returns gl texture id
	 */
	int32_t addTexture(Texture* texture);

	/** 
	 * Removes a texture from manager / open gl stack
	 * @param texture id
	 */
	void removeTexture(String* textureId);

	// Generated
	TextureManager(GLRenderer* renderer);
protected:
	TextureManager(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
	friend class TextureManager_TextureManaged;
};
