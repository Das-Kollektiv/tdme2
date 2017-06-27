// Generated from /tdme/src/tdme/engine/model/Color4.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4Base.h>

using tdme::engine::model::Color4Base;


struct default_init_tag;

/** 
 * Color 4 definition
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::model::Color4 final
	: public Color4Base
{

public:
	typedef Color4Base super;
protected:

	/** 
	 * Public constructor
	 */
	void ctor();

	/** 
	 * Public constructor
	 * @param color
	 */
	void ctor(Color4* color);

	/** 
	 * Public constructor
	 * @param red
	 * @param green
	 * @param blue
	 * @param alpha
	 */
	void ctor(float r, float g, float b, float a);

	/** 
	 * Public constructor
	 * @param color
	 */
	void ctor(floatArray* color);

	// Generated

public:
	Color4();
	Color4(Color4* color);
	Color4(float r, float g, float b, float a);
	Color4(floatArray* color);
protected:
	Color4(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
