// Generated from /tdme/src/tdme/engine/model/TextureCoordinate.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;


struct default_init_tag;

/** 
 * Class representing a UV data
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::model::TextureCoordinate final
	: public Object
{

public:
	typedef Object super;

private:
	floatArray* data {  };
protected:

	/** 
	 * Public constructor
	 * @param texture coordinate
	 */
	void ctor(TextureCoordinate* textureCoordinate);

	/** 
	 * Public constructor
	 * @param float array containing u, v values
	 */
	void ctor(floatArray* uv);

	/** 
	 * Public constructor
	 * @param u
	 * @param v
	 */
	void ctor(float u, float v);

public:

	/** 
	 * @return U
	 */
	float getU();

	/** 
	 * @return V
	 */
	float getV();

	/** 
	 * @return texture data as array
	 */
	floatArray* getArray();

	/** 
	 * Clones the texture coordinate
	 * @return new texture coordinate
	 */
	TextureCoordinate* clone() override;

	/** 
	 * Compares this texture coordinate with given texture coordinate
	 * @return equality
	 */
	bool equals(TextureCoordinate* textureCoordinate);

	/** 
	 * @return string representation
	 */
	String* toString() override;

	// Generated
	TextureCoordinate(TextureCoordinate* textureCoordinate);
	TextureCoordinate(floatArray* uv);
	TextureCoordinate(float u, float v);
protected:
	TextureCoordinate(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	virtual bool equals(Object* arg0);

private:
	virtual ::java::lang::Class* getClass0();
};
