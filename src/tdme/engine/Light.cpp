#include <tdme/engine/Light.h>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Texture.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>

using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Color4;
using tdme::engine::Engine;
using tdme::engine::Light;
using tdme::engine::Texture;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::math::Vector4;

Light::Light()
{
	this->rendererBackend = nullptr;
	this->id = -1;
	enabled = false;
	ambient.set(0.0f, 0.0f, 0.0f, 1.0f);
	diffuse.set(1.0f, 1.0f, 1.0f, 1.0f);
	specular.set(1.0f, 1.0f, 1.0f, 1.0f);
	position.set(0.0f, 0.0f, 0.0f, 0.0f);
	spotDirection.set(0.0f, 0.0f, -1.0f);
	spotExponent = 0.0f;
	spotCutOff = 180.0f;
	constantAttenuation = 0.5f;
	linearAttenuation = 0.0f;
	quadraticAttenuation = 0.0f;
	renderSource = false;
	sourceSize = 0.25f;
	lightSourceTextureId = 0;
}

Light::Light(RendererBackend* rendererBackend, int32_t id)
{
	this->rendererBackend = rendererBackend;
	this->id = id;
	enabled = false;
	ambient.set(0.0f, 0.0f, 0.0f, 1.0f);
	diffuse.set(1.0f, 1.0f, 1.0f, 1.0f);
	specular.set(1.0f, 1.0f, 1.0f, 1.0f);
	position.set(0.0f, 0.0f, 0.0f, 0.0f);
	spotDirection.set(0.0f, 0.0f, -1.0f);
	spotExponent = 0.0f;
	spotCutOff = 180.0f;
	constantAttenuation = 0.5f;
	linearAttenuation = 0.0f;
	quadraticAttenuation = 0.0f;
	renderSource = false;
	sourceSize = 0.25f;
	lightSourceTextureId = rendererBackend->ID_NONE;
}

void Light::setSourceTexture(Texture* texture) {
	if (lightSourceTexture == texture) return;
	if (lightSourceTexture != nullptr) {
		Engine::getInstance()->getTextureManager()->removeTexture(lightSourceTexture);
		lightSourceTexture->releaseReference();
		lightSourceTextureId = rendererBackend->ID_NONE;
	}
	lightSourceTexture = texture;
	lightSourceTextureId = texture == nullptr?rendererBackend->ID_NONE:Engine::getInstance()->getTextureManager()->addTexture(lightSourceTexture);
}

void Light::dispose() {
	if (lightSourceTexture == nullptr) return;
	Engine::getInstance()->getTextureManager()->removeTexture(lightSourceTexture);
	lightSourceTexture->releaseReference();
}

void Light::update(int contextIdx) {
	if (enabled == true) {
		auto& light = rendererBackend->getLight(contextIdx, id);
		light.enabled = 1;
		light.ambient = ambient.getArray();
		light.diffuse = diffuse.getArray();
		light.position = position.getArray();
		light.spotDirection = spotDirection.getArray();
		light.spotExponent = spotExponent;
		light.spotCosCutoff = static_cast<float>(Math::cos(Math::PI / 180.0f * spotCutOff));
		light.constantAttenuation = constantAttenuation;
		light.linearAttenuation = linearAttenuation;
		light.quadraticAttenuation = quadraticAttenuation;
		light.radius = getRadius();
		rendererBackend->onUpdateLight(contextIdx, id);
	} else {
		auto& light = rendererBackend->getLight(contextIdx, id);
		light.enabled = 0;
		rendererBackend->onUpdateLight(contextIdx, id);
	}
}
