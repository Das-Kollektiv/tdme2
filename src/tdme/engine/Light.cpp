#include <tdme/engine/Light.h>

#include <string>

#include <tdme/engine/model/Color4.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>

using tdme::engine::Light;
using tdme::engine::model::Color4;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::math::Vector4;

Light::Light()
{
	this->renderer = nullptr;
	this->id = -1;
	enabled = false;
	ambient.set(0.0f, 0.0f, 0.0f, 1.0f);
	diffuse.set(1.0f, 1.0f, 1.0f, 1.0f);
	specular.set(1.0f, 1.0f, 1.0f, 1.0f);
	position.set(0.0f, 0.0f, 0.0f, 0.0f);
	spotDirection.set(0.0f, 0.0f, -1.0f);
	spotExponent = 0.0f;
	spotCutOff = 180.0f;
	constantAttenuation = 1.0f;
	linearAttenuation = 0.0f;
	quadraticAttenuation = 0.0f;
}

Light::Light(Renderer* renderer, int32_t id) 
{
	this->renderer = renderer;
	this->id = id;
	enabled = false;
	ambient.set(0.0f, 0.0f, 0.0f, 1.0f);
	diffuse.set(1.0f, 1.0f, 1.0f, 1.0f);
	specular.set(1.0f, 1.0f, 1.0f, 1.0f);
	position.set(0.0f, 0.0f, 0.0f, 0.0f);
	spotDirection.set(0.0f, 0.0f, -1.0f);
	spotExponent = 0.0f;
	spotCutOff = 180.0f;
	constantAttenuation = 1.0f;
	linearAttenuation = 0.0f;
	quadraticAttenuation = 0.0f;
}

void Light::update()
{
	if (enabled == true) {
		Vector4 lightPositionTransformed;
		Vector3 tmpVector3;
		Vector4 spotDirection4;
		Vector4 spotDirection4Transformed;
		renderer->setLightEnabled(id);
		renderer->setLightAmbient(id, ambient.getArray());
		renderer->setLightDiffuse(id, diffuse.getArray());
		renderer->setLightPosition(id, renderer->getCameraMatrix().multiply(position, lightPositionTransformed).scale(Math::abs(lightPositionTransformed.getW()) < Math::EPSILON?1.0f:1.0f / lightPositionTransformed.getW()).setW(1.0f).getArray());
		renderer->getCameraMatrix().multiply(spotDirection4.set(spotDirection, 0.0f), spotDirection4Transformed);
		renderer->setLightSpotDirection(id, tmpVector3.set(spotDirection4Transformed.getX(), spotDirection4Transformed.getY(), spotDirection4Transformed.getZ()).getArray());
		renderer->setLightSpotExponent(id, spotExponent);
		renderer->setLightSpotCutOff(id, spotCutOff);
		renderer->setLightConstantAttenuation(id, constantAttenuation);
		renderer->setLightLinearAttenuation(id, linearAttenuation);
		renderer->setLightQuadraticAttenuation(id, quadraticAttenuation);
		renderer->onUpdateLight(id);
	} else {
		renderer->setLightDisabled(id);
		renderer->onUpdateLight(id);
	}
}
