#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/math/Math.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/utilities/Console.h>

using std::to_string;

using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Color4;
using tdme::engine::Texture;
using tdme::math::Math;
using tdme::math::Quaternion;
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
	RendererBackend* rendererBackend { nullptr };

public:
	// forbid class copy
	FORBID_CLASS_COPY(Light)

	/**
	 * Public default constructor
	 */
	Light();

	/**
	 * Public default constructor
	 * @param rendererBackend renderer backend
	 * @param id id
	 */
	Light(RendererBackend* rendererBackend, int32_t id);

	/**
	 * @returns light id
	 */
	inline int32_t getId() const {
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

	/**
	 * @returns radius
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
	 * @returns rendering light source is enabled
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
	 * @returns light source size (moon, sun)
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
	 * @returns light source texture
	 */
	inline Texture* getSourceTexture() const {
		return lightSourceTexture;
	}

	/**
	 * Returns light source texture
	 * @returns light source texture
	 */
	void setSourceTexture(Texture* texture);

	/**
	 * Returns light source texture id
	 * @returns light source texture id
	 */
	inline int32_t getSourceTextureId() const {
		return lightSourceTextureId;
	}

	/**
	 * Returns if light is directional light like sun, moon lights
	 * @returns directional light like sun, moon lights
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

	/**
	 * Set up sun
	 * @param t time, while 0.0 <= t <= 1.0
	 */
	inline void setupSun(float t) {
		Quaternion lightRotationXQuaternion;
		lightRotationXQuaternion.rotate(Vector3(0.0f, 0.0f, 1.0f), (1.0f - t) * 360.0f);
		auto lightPosition = lightRotationXQuaternion * Vector3(1000000.0f, 0.0f, 1.0f);
		setPosition(Vector4(lightPosition.getX(), lightPosition.getY(), lightPosition.getZ(), 0.0f));
		setSpotDirection(Vector3(getPosition().getX(), getPosition().getY(), getPosition().getZ()).scale(-1.0f).normalize());
	}

	/**
	 * Set up moon
	 * @param t time, while 0.0 <= t <= 1.0
	 */
	inline void setupMoon(float t) {
		Quaternion lightRotationXQuaternion;
		lightRotationXQuaternion.rotate(Vector3(0.0f, 0.0f, 1.0f), (1.0f - t) * 360.0f);
		auto lightPosition = lightRotationXQuaternion * Vector3(-1000000.0f, 0.0f, 1.0f);
		setPosition(Vector4(lightPosition.getX(), lightPosition.getY(), lightPosition.getZ(), 0.0f));
		setSpotDirection(Vector3(getPosition().getX(), getPosition().getY(), getPosition().getZ()).scale(-1.0f).normalize());
	}

};
