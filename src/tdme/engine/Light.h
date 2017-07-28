// Generated from /tdme/src/tdme/engine/Light.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using tdme::engine::model::Color4;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Vector3;
using tdme::math::Vector4;


struct default_init_tag;

/** 
 * Light 
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::Light final
	: public Object
{

public:
	typedef Object super;

private:
	int32_t id {  };
	bool enabled {  };
	Color4* ambient {  };
	Color4* diffuse {  };
	Color4* specular {  };
	Vector4* position {  };
	Vector3* spotDirection {  };
	float spotExponent {  };
	float spotCutOff {  };
	float constantAttenuation {  };
	float linearAttenuation {  };
	float quadraticAttenuation {  };
	Vector4* lightPositionTransformed {  };
	Vector4* spotDirection4 {  };
	Vector4* spotDirection4Transformed {  };
	Vector3* tmpVector3 {  };
	GLRenderer* renderer {  };
protected:

	/** 
	 * Public default constructor
	 * @param renderer
	 * @param id
	 */
	void ctor(GLRenderer* renderer, int32_t id);

public:

	/** 
	 * @return light id
	 */
	int32_t getId();

	/** 
	 * @return enabled
	 */
	bool isEnabled();

	/** 
	 * Set enabled
	 * @param enabled
	 */
	void setEnabled(bool enabled);

	/** 
	 * @return ambient light
	 */
	Color4* getAmbient();

	/** 
	 * Diffuse light 
	 * @return diffuse light
	 */
	Color4* getDiffuse();

	/** 
	 * @return specular light
	 */
	Color4* getSpecular();

	/** 
	 * @return position of light
	 */
	Vector4* getPosition();

	/** 
	 * @return spot direction
	 */
	Vector3* getSpotDirection();

	/** 
	 * @return spot exponent
	 */
	float getSpotExponent();

	/** 
	 * set up spot exponent 
	 * @param spot exponent
	 */
	void setSpotExponent(float spotExponent);

	/** 
	 * @return spot cutoff
	 */
	float getSpotCutOff();

	/** 
	 * set spot cut off
	 * @param spot cut off
	 */
	void setSpotCutOff(float spotCutOff);

	/** 
	 * @return constant attenuation
	 */
	float getConstantAttenuation();

	/** 
	 * set up constant attenuation
	 * @param constant attenuation
	 */
	void setConstantAttenuation(float constantAttenuation);

	/** 
	 * @return linear attenuation
	 */
	float getLinearAttenuation();

	/** 
	 * set up linear attenuation
	 * @param linarAttenuation
	 */
	void setLinearAttenuation(float linarAttenuation);

	/** 
	 * @return quadratic attenuation
	 */
	float getQuadraticAttenuation();

	/** 
	 * set up quadratic attenuation
	 * @param quadraticAttenuation
	 */
	void setQuadraticAttenuation(float quadraticAttenuation);

	/** 
	 * Update light
	 */
	void update();

	// Generated
	Light(GLRenderer* renderer, int32_t id);
protected:
	Light(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
