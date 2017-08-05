// Generated from /tdme/src/tdme/engine/model/Color4Base.java

#pragma once

#include <array>

#include <fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>

using std::array;

/** 
 * Color 4 base definition
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::model::Color4Base
{

public: /* protected */
	array<float, 4> data {  };

public:
	/**
	 * Set up color
	 * @param color float array
	 */
	virtual void set(array<float, 4>* color);

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
	virtual array<float, 4>* getArray();

	/** 
	 * Compares this color with given color
	 * @return equality
	 */
	virtual bool equals(Color4Base* c);

	/**
	 * Public constructor
	 */
	Color4Base();

	/**
	 * Public constructor
	 * @param color
	 */
	Color4Base(Color4Base* color);

	/**
	 * Public constructor
	 * @param color
	 */
	Color4Base(array<float, 4>* color);

	/**
	 * Public constructor
	 * @param color
	 */
	Color4Base(floatArray* color);

	/**
	 * Public constructor
	 * @param red
	 * @param green
	 * @param blue
	 * @param alpha
	 */
	Color4Base(float r, float g, float b, float a);


};
