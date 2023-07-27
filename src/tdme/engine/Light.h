#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/utilities/Console.h>

using std::to_string;

using tdme::engine::Texture;
using tdme::engine::Color4;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::math::Math;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::utilities::Console;

/**
 * Light representation
 * @author Andreas Drewke
 */
class tdme::engine::Light final
{
private:
	int32_t id;
	bool enabled;
	Color4 ambient;
	Color4 diffuse;
	Color4 specular;
	Vector4 position;
	Vector3 spotDirection;
	float spotExponent;
	float spotCutOff;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
	bool renderSource;
	float sourceSize;
	Texture* lightSourceTexture { nullptr };
	int32_t lightSourceTextureId;
	Renderer* renderer { nullptr };

public:
	// forbid class copy
	FORBID_CLASS_COPY(Light)

	/**
	 * Public default constructor
	 */
	Light();

	/**
	 * Public default constructor
	 * @param renderer renderer
	 * @param id id
	 */
	Light(Renderer* renderer, int32_t id);

	/**
	 * @return light id
	 */
	inline int32_t getId() const {
		return id;
	}

	/**
	 * @return enabled
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
	 * @return ambient light component
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
	 * @return diffuse light component
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
	 * @return specular light component
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
	 * @return position of light
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
	 * @return spot direction
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
	 * @return spot exponent
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
	 * @return spot cutoff
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
	 * @return constant attenuation
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
	 * @return linear attenuation
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
	 * @return quadratic attenuation
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

	/**
	 * @return radius
	 */
	inline float getRadius() {
		// see: https://learnopengl.com/Advanced-Lighting/Deferred-Shading
		float ambientLightMax = Math::max(Math::max(ambient.getRed(), ambient.getGreen()), ambient.getBlue());
		if (ambientLightMax > Math::EPSILON) return 0.0f;
		auto diffuseLightMax = Math::max(Math::max(diffuse.getRed(), diffuse.getGreen()), diffuse.getBlue());
		if (diffuseLightMax < Math::EPSILON) return 0.0f;
		if (linearAttenuation > Math::EPSILON || quadraticAttenuation > Math::EPSILON)
			return (-linearAttenuation + Math::sqrt(linearAttenuation * linearAttenuation - 4.0f * quadraticAttenuation * (constantAttenuation - (256.0f / 5.0f) * diffuseLightMax))) / (quadraticAttenuation < Math::EPSILON?1.0f:2.0f * quadraticAttenuation);
		return 0.0f;
	}

	/**
	 * Returns if rendering light source is enabled
	 * @return rendering light source is enabled
	 */
	inline bool isRenderSource() const {
		return renderSource;
	}

	/**
	 * Set rendering light source enabled/disabled
	 * @param renderLightSource render light source enabled
	 */
	inline void setRenderSource(bool renderSource) {
		this->renderSource = renderSource;
	}

	/**
	 * Returns light source size
	 * @return light source size (moon, sun)
	 */
	inline float getSourceSize() const {
		return sourceSize;
	}

	/**
	 * Set light source size (moon, sun)
	 * @param lightSourceSize light source size
	 */
	inline void setLightSourceSize(float sourceSize) {
		this->sourceSize = sourceSize;
	}

	/**
	 * Returns light source texture
	 * @return light source texture
	 */
	inline Texture* getSourceTexture() const {
		return lightSourceTexture;
	}

	/**
	 * Returns light source texture
	 * @return light source texture
	 */
	void setSourceTexture(Texture* texture);

	/**
	 * Returns light source texture id
	 * @return light source texture id
	 */
	inline int32_t getSourceTextureId() const {
		return lightSourceTextureId;
	}

	/**
	 * Returns if light is directional light like sun, moon lights
	 * @return directional light like sun, moon lights
	 */
	inline bool isDirectional() const {
		return position.getW() < Math::EPSILON;
	}

	/**
	 * Dispose
	 */
	void dispose();

	/**
	 * Update light
	 * @param contextIdx context index
	 */
	void update(int contextIdx);


};
