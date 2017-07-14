// Generated from /tdme/src/tdme/engine/fileio/textures/TextureLoader.java

#pragma once

#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/os/fwd-tdme.h>
#include <java/lang/Object.h>

#include <tdme/os/_FileSystemException.h>

using java::lang::Object;
using java::lang::String;
using tdme::engine::fileio::textures::Texture;
using tdme::os::_FileSystemException;

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
	 * @throws _FileSystemException
	 * @return texture data instance or null
	 */
	static Texture* loadTexture(String* path, String* fileName) throw (_FileSystemException);

	// Generated
	TextureLoader();
protected:
	TextureLoader(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	/**
	 * Load PNG
	 * @param path name
	 * @param file name
	 */
	static Texture* loadPNG(String* path, String* fileName) throw (_FileSystemException);

	//
	virtual ::java::lang::Class* getClass0();
};
