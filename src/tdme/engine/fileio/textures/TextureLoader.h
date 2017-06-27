// Generated from /tdme/src/tdme/engine/fileio/textures/TextureLoader.java

#pragma once

#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::engine::fileio::textures::Texture;


struct default_init_tag;

/** 
 * ImageLoader loader class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::fileio::textures::TextureLoader final
	: public Object
{

public:
	typedef Object super;

	/** 
	 * Loads a texture
	 * @param path
	 * @param fileName
	 * @return texture data instance or null
	 */
	static Texture* loadTexture(String* path, String* fileName);

	// Generated
	TextureLoader();
protected:
	TextureLoader(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
