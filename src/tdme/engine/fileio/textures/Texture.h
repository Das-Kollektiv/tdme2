// Generated from /tdme/src/tdme/engine/fileio/textures/Texture.java

#pragma once

#include <string>

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <java/lang/Object.h>

using std::wstring;

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
	 * Public constructor
	 * @param id
	 * @param depth
	 * @param width
	 * @param height
	 * @param texture width
	 * @param texture height
	 * @param texture data
	 */
	Texture(
		const wstring& id,
		int32_t depth,
		int32_t width,
		int32_t height,
		int32_t textureWidth,
		int32_t textureHeight,
		ByteBuffer* textureData
	);

	/** 
	 * @return id
	 */
	const wstring& getId();

	/** 
	 * @return depth in bits per pixel
	 */
	int32_t getDepth();

	/** 
	 * @return image width
	 */
	int32_t getWidth();

	/** 
	 * @return image height
	 */
	int32_t getHeight();

	/** 
	 * @return texture height
	 */
	int32_t getTextureHeight();

	/** 
	 * @return texture width
	 */
	int32_t getTextureWidth();

	/** 
	 * @return texture data wrapped in a byte buffer
	 */
	ByteBuffer* getTextureData();

	/**
	 * @return string representation
	 */
	String* toString() override;

	// Generated
	static ::java::lang::Class *class_();

private:
	wstring id;
	int32_t depth;
	int32_t width;
	int32_t height;
	int32_t textureHeight;
	int32_t textureWidth;
	ByteBuffer* textureData;
};
