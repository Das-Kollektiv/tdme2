// Generated from /tdme/src/tdme/tools/shared/model/LevelEditorLight.java
#include <tdme/tools/shared/model/LevelEditorLight.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>

using tdme::tools::shared::model::LevelEditorLight;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::model::Color4;
using tdme::math::Vector3;
using tdme::math::Vector4;

LevelEditorLight::LevelEditorLight(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

LevelEditorLight::LevelEditorLight(int32_t id) 
	: LevelEditorLight(*static_cast< ::default_init_tag* >(0))
{
	ctor(id);
}

void LevelEditorLight::init()
{
	enabled = false;
	ambient = new Color4(0.0f, 0.0f, 0.0f, 1.0f);
	diffuse = new Color4(1.0f, 1.0f, 1.0f, 1.0f);
	specular = new Color4(1.0f, 1.0f, 1.0f, 1.0f);
	position = new Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	spotTo = new Vector3(0.0f, 0.0f, -1.0f);
	spotDirection = new Vector3(0.0f, 0.0f, -1.0f);
	spotExponent = 0.0f;
	spotCutOff = 180.0f;
	constantAttenuation = 1.0f;
	linearAttenuation = 0.0f;
	quadraticAttenuation = 0.0f;
}

void LevelEditorLight::ctor(int32_t id)
{
	super::ctor();
	init();
	this->id = id;
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
	return ambient;
}

Color4* LevelEditorLight::getDiffuse()
{
	return diffuse;
}

Color4* LevelEditorLight::getSpecular()
{
	return specular;
}

Vector4* LevelEditorLight::getPosition()
{
	return position;
}

Vector3* LevelEditorLight::getSpotTo()
{
	return spotTo;
}

Vector3* LevelEditorLight::getSpotDirection()
{
	return spotDirection;
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

String* LevelEditorLight::toString()
{
	return ::java::lang::StringBuilder().append(u"LevelEditorLight [id="_j)->append(id)
		->append(u", enabled="_j)
		->append(enabled)
		/*
		// TODO: Implement me!
		->append(u", ambient="_j)
		->append(static_cast< Object* >(ambient))
		->append(u", diffuse="_j)
		->append(static_cast< Object* >(diffuse))
		->append(u", specular="_j)
		->append(static_cast< Object* >(specular))
		*/
		->append(u", position="_j)
		->append(static_cast< Object* >(position))
		->append(u", spotDirection="_j)
		->append(static_cast< Object* >(spotDirection))
		->append(u", spotExponent="_j)
		->append(spotExponent)
		->append(u", spotCutOff="_j)
		->append(spotCutOff)
		->append(u", constantAttenuation="_j)
		->append(constantAttenuation)
		->append(u", linearAttenuation="_j)
		->append(linearAttenuation)
		->append(u", quadraticAttenuation="_j)
		->append(quadraticAttenuation)
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* LevelEditorLight::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.model.LevelEditorLight", 40);
    return c;
}

java::lang::Class* LevelEditorLight::getClass0()
{
	return class_();
}

