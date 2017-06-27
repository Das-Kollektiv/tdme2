// Generated from /tdme/src/tdme/engine/model/Color4Base.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;


struct default_init_tag;

/** 
 * Color 4 base definition
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::model::Color4Base
	: public virtual Object
{

public:
	typedef Object super;

public: /* protected */
	floatArray* data {  };
protected:

	/** 
	 * Public constructor
	 */
	void ctor();

	/** 
	 * Public constructor
	 * @param color
	 */
	void ctor(Color4Base* color);

	/** 
	 * Public constructor
	 * @param color
	 */
	void ctor(floatArray* color);

	/** 
	 * Public constructor
	 * @param red
	 * @param green
	 * @param blue
	 * @param alpha
	 */
	void ctor(float r, float g, float b, float a);

public:

	/** 
	 * Set up color
	 * @param color float array
	 */
	virtual void set(floatArray* color);

	/** 
	 * Set up color
	 * @param red
	 * @param green
	 * @param blue
	 * @param alpha
	 */
	virtual void set(float r, float g, float b, float a);

	/** 
	 * Sets up this color with given color
	 * @param color
	 */
	virtual void set(Color4Base* color);

	/** 
	 * Add to color
	 * @param red
	 * @param green
	 * @param blue
	 * @param alpha
	 */
	virtual void add(float r, float g, float b, float a);

	/** 
	 * @return red component
	 */
	virtual float getRed();

	/** 
	 * @param red component
	 */
	virtual void setRed(float red);

	/** 
	 * @return green component
	 */
	virtual float getGreen();

	/** 
	 * @param green component
	 */
	virtual void setGreen(float green);

	/** 
	 * @return blue component
	 */
	virtual float getBlue();

	/** 
	 * @param blue component
	 */
	virtual void setBlue(float blue);

	/** 
	 * @return alpha component
	 */
	virtual float getAlpha();

	/** 
	 * @param alpha component
	 */
	virtual void setAlpha(float alpha);

	/** 
	 * @return rgba as float array 
	 */
	virtual floatArray* getArray();

	/** 
	 * Compares this color with given color
	 * @return equality
	 */
	virtual bool equals(Color4Base* c);
	String* toString() override;

	// Generated
	Color4Base();
	Color4Base(Color4Base* color);
	Color4Base(floatArray* color);
	Color4Base(float r, float g, float b, float a);
protected:
	Color4Base(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	virtual bool equals(Object* arg0);

private:
	virtual ::java::lang::Class* getClass0();
};
