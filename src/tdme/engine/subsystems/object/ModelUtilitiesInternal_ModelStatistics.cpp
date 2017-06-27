// Generated from /tdme/src/tdme/engine/subsystems/object/ModelUtilitiesInternal.java
#include <tdme/engine/subsystems/object/ModelUtilitiesInternal_ModelStatistics.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>

using tdme::engine::subsystems::object::ModelUtilitiesInternal_ModelStatistics;
using java::lang::String;
using java::lang::StringBuilder;

ModelUtilitiesInternal_ModelStatistics::ModelUtilitiesInternal_ModelStatistics(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

ModelUtilitiesInternal_ModelStatistics::ModelUtilitiesInternal_ModelStatistics(int32_t opaqueFaceCount, int32_t transparentFaceCount, int32_t materialCount) 
	: ModelUtilitiesInternal_ModelStatistics(*static_cast< ::default_init_tag* >(0))
{
	ctor(opaqueFaceCount,transparentFaceCount,materialCount);
}

void ModelUtilitiesInternal_ModelStatistics::ctor(int32_t opaqueFaceCount, int32_t transparentFaceCount, int32_t materialCount)
{
	super::ctor();
	this->opaqueFaceCount = opaqueFaceCount;
	this->transparentFaceCount = transparentFaceCount;
	this->materialCount = materialCount;
}

int32_t ModelUtilitiesInternal_ModelStatistics::getOpaqueFaceCount()
{
	return opaqueFaceCount;
}

int32_t ModelUtilitiesInternal_ModelStatistics::getTransparentFaceCount()
{
	return transparentFaceCount;
}

int32_t ModelUtilitiesInternal_ModelStatistics::getMaterialCount()
{
	return materialCount;
}

String* ModelUtilitiesInternal_ModelStatistics::toString()
{
	return ::java::lang::StringBuilder().append(u"ModelStatistics [opaqueFaceCount="_j)->append(opaqueFaceCount)
		->append(u", transparentFaceCount="_j)
		->append(transparentFaceCount)
		->append(u", materialCount="_j)
		->append(materialCount)
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ModelUtilitiesInternal_ModelStatistics::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.object.ModelUtilitiesInternal.ModelStatistics", 68);
    return c;
}

java::lang::Class* ModelUtilitiesInternal_ModelStatistics::getClass0()
{
	return class_();
}

