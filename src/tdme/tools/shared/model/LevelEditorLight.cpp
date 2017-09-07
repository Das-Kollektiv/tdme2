// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorLight.java
#include <tdme/tools/shared/model/LevelEditorLight.h>

#include <java/lang/String.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>

using tdme::tools::shared::model::LevelEditorLight;
using java::lang::String;
using tdme::engine::model::Color4;
using tdme::math::Vector3;
using tdme::math::Vector4;

LevelEditorLight::LevelEditorLight(int32_t id) 
{
	this->id = id;
	enabled = false;
	ambient.set(0.0f, 0.0f, 0.0f, 1.0f);
	diffuse.set(1.0f, 1.0f, 1.0f, 1.0f);
	specular.set(1.0f, 1.0f, 1.0f, 1.0f);
	position.set(0.0f, 0.0f, 0.0f, 0.0f);
	spotTo.set(0.0f, 0.0f, -1.0f);
	spotDirection.set(0.0f, 0.0f, -1.0f);
	spotExponent = 0.0f;
	spotCutOff = 180.0f;
	constantAttenuation = 1.0f;
	linearAttenuation = 0.0f;
	quadraticAttenuation = 0.0f;
}

int32_t LevelEditorLight::getId()
{
	return id;
}

bool LevelEditorLight::isEnabled()
{
	return enabled;
}

void LevelEditorLight::setEnabled(bool enabled)
{
	this->enabled = enabled;
}

Color4* LevelEditorLight::getAmbient()
{
	return &ambient;
}

Color4* LevelEditorLight::getDiffuse()
{
	return &diffuse;
}

Color4* LevelEditorLight::getSpecular()
{
	return &specular;
}

Vector4* LevelEditorLight::getPosition()
{
	return &position;
}

Vector3* LevelEditorLight::getSpotTo()
{
	return &spotTo;
}

Vector3* LevelEditorLight::getSpotDirection()
{
	return &spotDirection;
}

float LevelEditorLight::getSpotExponent()
{
	return spotExponent;
}

void LevelEditorLight::setSpotExponent(float spotExponent)
{
	this->spotExponent = spotExponent;
}

float LevelEditorLight::getSpotCutOff()
{
	return spotCutOff;
}

void LevelEditorLight::setSpotCutOff(float spotCutOff)
{
	this->spotCutOff = spotCutOff;
}

float LevelEditorLight::getConstantAttenuation()
{
	return constantAttenuation;
}

void LevelEditorLight::setConstantAttenuation(float constantAttenuation)
{
	this->constantAttenuation = constantAttenuation;
}

float LevelEditorLight::getLinearAttenuation()
{
	return linearAttenuation;
}

void LevelEditorLight::setLinearAttenuation(float linarAttenuation)
{
	this->linearAttenuation = linarAttenuation;
}

float LevelEditorLight::getQuadraticAttenuation()
{
	return quadraticAttenuation;
}

void LevelEditorLight::setQuadraticAttenuation(float quadraticAttenuation)
{
	this->quadraticAttenuation = quadraticAttenuation;
}

