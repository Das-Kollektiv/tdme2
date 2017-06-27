// Generated from /tdme/src/tdme/engine/fileio/textures/Texture.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using java::nio::ByteBuffer;



/** 
 * Taken from Nifty-GUI 1.3.2 http://nifty-gui.lessvoid.com
 * This has been slightly modified by me
 * @version $Id$
 * @author Nifty GUI authors, Andreas Drewke
 */
struct tdme::engine::fileio::textures::Texture
	: public virtual Object
{

	/** 
	 * @return id
	 */
	virtual String* getId() = 0;

	/** 
	 * @return depth in bits per pixel
	 */
	virtual int32_t getDepth() = 0;

	/** 
	 * @return image width
	 */
	virtual int32_t getWidth() = 0;

	/** 
	 * @return image height
	 */
	virtual int32_t getHeight() = 0;

	/** 
	 * @return texture height
	 */
	virtual int32_t getTextureHeight() = 0;

	/** 
	 * @return texture width
	 */
	virtual int32_t getTextureWidth() = 0;

	/** 
	 * @return texture data wrapped in a byte buffer
	 */
	virtual ByteBuffer* getTextureData() = 0;

	// Generated
	static ::java::lang::Class *class_();
};
