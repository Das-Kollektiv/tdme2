// Generated from /tdme/src/tdme/math/MathTools.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;


struct default_init_tag;

/** 
 * Additional mathematical functions
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::math::MathTools final
	: public Object
{

public:
	typedef Object super;
	static constexpr float EPSILON { 1.0E-5f };
	static constexpr float DEG2RAD { 0.017453294f };
	static constexpr float g { 9.80665f };

	/** 
	 * Clamps a float value to min or max value
	 * @param value
	 * @param min value
	 * @param max value
	 * @return clamped value
	 */
	static float clamp(float value, float min, float max);

	/** 
	 * Returns sign of value
	 * @param value
	 * @return -1 if value is negative or +1 if positive
	 */
	static float sign(float value);

	/** 
	 * Do the square product
	 * @param value
	 * @return
	 */
	static float square(float value);

	// Generated
	MathTools();
protected:
	MathTools(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
