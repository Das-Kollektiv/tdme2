
#pragma once

#include <tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>

using tdme::engine::model::Color4;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Vector3;
using tdme::math::Vector4;

/** 
 * Light 
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::Light final
{
private:
	int32_t id {  };
	bool enabled {  };
	Color4 ambient {  };
	Color4 diffuse {  };
	Color4 specular {  };
	Vector4 position {  };
	Vector3 spotDirection {  };
	float spotExponent {  };
	float spotCutOff {  };
	float constantAttenuation {  };
	float linearAttenuation {  };
	float quadraticAttenuation {  };
	GLRenderer* renderer {  };
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
	Color4& getAmbient();

	/** 
	 * Diffuse light 
	 * @return diffuse light
	 */
	Color4& getDiffuse();

	/** 
	 * @return specular light
	 */
	Color4& getSpecular();

	/** 
	 * @return position of light
	 */
	Vector4& getPosition();

	/** 
	 * @return spot direction
	 */
	Vector3& getSpotDirection();

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


	/**
	 * Public default constructor
	 */
	Light();

	/**
	 * Public default constructor
	 * @param renderer
	 * @param id
	 */
	Light(GLRenderer* renderer, int32_t id);
};
