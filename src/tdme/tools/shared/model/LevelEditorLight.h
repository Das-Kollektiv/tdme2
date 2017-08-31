// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorLight.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>

using java::lang::String;
using tdme::engine::model::Color4;
using tdme::math::Vector3;
using tdme::math::Vector4;

/** 
 * Light 
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::model::LevelEditorLight final
{
private:
	int32_t id {  };
	bool enabled {  };
	Color4* ambient {  };
	Color4* diffuse {  };
	Color4* specular {  };
	Vector4* position {  };
	Vector3* spotTo {  };
	Vector3* spotDirection {  };
	float spotExponent {  };
	float spotCutOff {  };
	float constantAttenuation {  };
	float linearAttenuation {  };
	float quadraticAttenuation {  };

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
	 * @return spot to
	 */
	Vector3* getSpotTo();

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
	 * Public default constructor
	 * @param id
	 */
	LevelEditorLight(int32_t id);
};
