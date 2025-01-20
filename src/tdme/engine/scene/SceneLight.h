#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/scene/fwd-tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>

using tdme::engine::Color4;
using tdme::math::Vector3;
using tdme::math::Vector4;

/**
 * Scene light definition
 * @author Andreas Drewke
 */
class tdme::engine::scene::SceneLight final
{
private:
	int id;
	bool enabled;
	Color4 ambient;
	Color4 diffuse;
	Color4 specular;
	Vector4 position;
	Vector3 spotTo;
	Vector3 spotDirection;
	float spotExponent;
	float spotCutOff;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;

public:
	// forbid class copy
	FORBID_CLASS_COPY(SceneLight)

	/**
	 * Public default constructor
	 * @param id id
	 */
	SceneLight(int id);

	/**
	 * @returns light id
	 */
	inline int getId() {
		return id;
	}

	/**
	 * @returns enabled
	 */
	inline bool isEnabled() const {
		return enabled;
	}

	/**
	 * Set enabled
	 * @param enabled enabled
	 */
	inline void setEnabled(bool enabled) {
		this->enabled = enabled;
	}

	/**
	 * @returns ambient light component
	 */
	inline const Color4& getAmbient() const {
		return ambient;
	}

	/**
	 * Set ambient light component
	 * @param ambient ambient light component
	 */
	inline void setAmbient(const Color4& ambient) {
		this->ambient = ambient;
	}

	/**
	 * @returns diffuse light component
	 */
	inline const Color4& getDiffuse() const {
		return diffuse;
	}

	/**
	 * Set diffuse light component
	 * @param diffuse diffuse light
	 */
	inline void setDiffuse(const Color4& diffuse) {
		this->diffuse = diffuse;
	}

	/**
	 * @returns specular light component
	 */
	inline const Color4& getSpecular() const {
		return specular;
	}

	/**
	 * Set specular light component
	 * @param specular specular light
	 */
	inline void setSpecular(const Color4& specular) {
		this->specular = specular;
	}

	/**
	 * @returns position of light
	 */
	inline const Vector4& getPosition() const {
		return position;
	}

	/**
	 * Set light position
	 * @param position position of light
	 */
	inline void setPosition(const Vector4& position) {
		this->position = position;
	}

	/**
	 * @returns spot direction
	 */
	inline const Vector3& getSpotDirection() const {
		return spotDirection;
	}

	/**
	 * Set spot direction
	 * @param spotDirection spot direction
	 */
	inline void setSpotDirection(const Vector3& spotDirection) {
		this->spotDirection = spotDirection;
	}

	/**
	 * @returns spot exponent
	 */
	inline float getSpotExponent() const {
		return spotExponent;
	}

	/**
	 * Set up spot exponent
	 * @param spotExponent spot exponent
	 */
	inline void setSpotExponent(float spotExponent) {
		this->spotExponent = spotExponent;
	}

	/**
	 * @returns spot cutoff
	 */
	inline float getSpotCutOff() const {
		return spotCutOff;
	}

	/**
	 * Set spot cut off
	 * @param spotCutOff spot cut off
	 */
	inline void setSpotCutOff(float spotCutOff) {
		this->spotCutOff = spotCutOff;
	}

	/**
	 * @returns constant attenuation
	 */
	inline float getConstantAttenuation() const {
		return constantAttenuation;
	}

	/**
	 * Set up constant attenuation
	 * @param constantAttenuation constant attenuation
	 */
	inline void setConstantAttenuation(float constantAttenuation) {
		this->constantAttenuation = constantAttenuation;
	}

	/**
	 * @returns linear attenuation
	 */
	inline float getLinearAttenuation() const {
		return linearAttenuation;
	}

	/**
	 * Set up linear attenuation
	 * @param linearAttenuation linear attenuation
	 */
	inline void setLinearAttenuation(float linearAttenuation) {
		this->linearAttenuation = linearAttenuation;
	}

	/**
	 * @returns quadratic attenuation
	 */
	inline float getQuadraticAttenuation() const {
		return quadraticAttenuation;
	}

	/**
	 * Set up quadratic attenuation
	 * @param quadraticAttenuation quadraticAttenuation
	 */
	inline void setQuadraticAttenuation(float quadraticAttenuation) {
		this->quadraticAttenuation = quadraticAttenuation;
	}

};
