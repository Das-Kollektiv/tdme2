// Generated from /tdme/src/tdme/engine/model/JointWeight.java
#include <tdme/engine/model/JointWeight.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>

using tdme::engine::model::JointWeight;
using java::lang::String;
using java::lang::StringBuilder;

JointWeight::JointWeight(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

JointWeight::JointWeight(int32_t jointIndex, int32_t weightIndex) 
	: JointWeight(*static_cast< ::default_init_tag* >(0))
{
	ctor(jointIndex,weightIndex);
}

void JointWeight::ctor(int32_t jointIndex, int32_t weightIndex)
{
	super::ctor();
	this->jointIndex = jointIndex;
	this->weightIndex = weightIndex;
}

int32_t JointWeight::getJointIndex()
{
	return jointIndex;
}

int32_t JointWeight::getWeightIndex()
{
	return weightIndex;
}

String* JointWeight::toString()
{
	return ::java::lang::StringBuilder().append(u"JointWeight [jointIndex="_j)->append(jointIndex)
		->append(u", weightIndex="_j)
		->append(weightIndex)
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* JointWeight::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.model.JointWeight", 29);
    return c;
}

java::lang::Class* JointWeight::getClass0()
{
	return class_();
}

