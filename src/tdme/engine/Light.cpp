// Generated from /tdme/src/tdme/engine/Light.java
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

Light::Light(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Light::Light(GLRenderer* renderer, int32_t id) 
	: Light(*static_cast< ::default_init_tag* >(0))
{
	ctor(renderer,id);
}

void Light::init()
{
	enabled = false;
	ambient = new Color4(0.0f, 0.0f, 0.0f, 1.0f);
	diffuse = new Color4(1.0f, 1.0f, 1.0f, 1.0f);
	specular = new Color4(1.0f, 1.0f, 1.0f, 1.0f);
	position = new Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	spotDirection = new Vector3(0.0f, 0.0f, -1.0f);
	spotExponent = 0.0f;
	spotCutOff = 180.0f;
	constantAttenuation = 1.0f;
	linearAttenuation = 0.0f;
	quadraticAttenuation = 0.0f;
}

void Light::ctor(GLRenderer* renderer, int32_t id)
{
	super::ctor();
	init();
	this->renderer = renderer;
	this->id = id;
	this->lightPositionTransformed = new Vector4();
	this->spotDirection4 = new Vector4();
	this->spotDirection4Transformed = new Vector4();
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
	return ambient;
}

Color4* Light::getDiffuse()
{
	return diffuse;
}

Color4* Light::getSpecular()
{
	return specular;
}

Vector4* Light::getPosition()
{
	return position;
}

Vector3* Light::getSpotDirection()
{
	return spotDirection;
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
		renderer->setLightEnabled(id);
		renderer->setLightAmbient(id, ambient->getArray());
		renderer->setLightDiffuse(id, diffuse->getArray());
		renderer->setLightPosition(id, renderer->getCameraMatrix()->multiply(position, lightPositionTransformed)->scale(1.0f / lightPositionTransformed->getW())->getArray());
		renderer->setLightSpotDirection(id, renderer->getCameraMatrix()->multiply(spotDirection4->set(spotDirection, 0.0f), spotDirection4Transformed)->getArray());
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

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Light::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.Light", 17);
    return c;
}

java::lang::Class* Light::getClass0()
{
	return class_();
}

