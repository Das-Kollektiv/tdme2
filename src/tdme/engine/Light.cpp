#include <tdme/engine/Light.h>

#include <tdme/engine/model/Color4.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>

using tdme::engine::Light;
using tdme::engine::model::Color4;
using tdme::engine::subsystems::renderer::GLRenderer;
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

Light::Light(GLRenderer* renderer, int32_t id) 
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

int32_t Light::getId()
{
	return id;
}

bool Light::isEnabled()
{
	return enabled;
}

void Light::setEnabled(bool enabled)
{
	this->enabled = enabled;
}

Color4* Light::getAmbient()
{
	return &ambient;
}

Color4* Light::getDiffuse()
{
	return &diffuse;
}

Color4* Light::getSpecular()
{
	return &specular;
}

Vector4* Light::getPosition()
{
	return &position;
}

Vector3* Light::getSpotDirection()
{
	return &spotDirection;
}

float Light::getSpotExponent()
{
	return spotExponent;
}

void Light::setSpotExponent(float spotExponent)
{
	this->spotExponent = spotExponent;
}

float Light::getSpotCutOff()
{
	return spotCutOff;
}

void Light::setSpotCutOff(float spotCutOff)
{
	this->spotCutOff = spotCutOff;
}

float Light::getConstantAttenuation()
{
	return constantAttenuation;
}

void Light::setConstantAttenuation(float constantAttenuation)
{
	this->constantAttenuation = constantAttenuation;
}

float Light::getLinearAttenuation()
{
	return linearAttenuation;
}

void Light::setLinearAttenuation(float linarAttenuation)
{
	this->linearAttenuation = linarAttenuation;
}

float Light::getQuadraticAttenuation()
{
	return quadraticAttenuation;
}

void Light::setQuadraticAttenuation(float quadraticAttenuation)
{
	this->quadraticAttenuation = quadraticAttenuation;
}

void Light::update()
{
	if (enabled) {
		Vector4 lightPositionTransformed;
		Vector3 tmpVector3;
		Vector4 spotDirection4;
		Vector4 spotDirection4Transformed;
		renderer->setLightEnabled(id);
		renderer->setLightAmbient(id, ambient.getArray());
		renderer->setLightDiffuse(id, diffuse.getArray());
		renderer->setLightPosition(id, &renderer->getCameraMatrix().multiply(position, lightPositionTransformed).scale(1.0f / lightPositionTransformed.getW()).getArray());
		renderer->getCameraMatrix().multiply(spotDirection4.set(spotDirection, 0.0f), spotDirection4Transformed);
		renderer->setLightSpotDirection(id, tmpVector3.set(spotDirection4Transformed.getX(), spotDirection4Transformed.getY(), spotDirection4Transformed.getZ())->getArray());
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
