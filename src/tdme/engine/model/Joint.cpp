// Generated from /tdme/src/tdme/engine/model/Joint.java
#include <tdme/engine/model/Joint.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/math/Matrix4x4.h>

using tdme::engine::model::Joint;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::math::Matrix4x4;

Joint::Joint(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Joint::Joint(const wstring& groupId)
	: Joint(*static_cast< ::default_init_tag* >(0))
{
	ctor(groupId);
}

void Joint::ctor(const wstring& groupId)
{
	super::ctor();
	this->groupId = groupId;
	this->bindMatrix = (new Matrix4x4())->identity();
}

const wstring& Joint::getGroupId()
{
	return groupId;
}

Matrix4x4* Joint::getBindMatrix()
{
	return bindMatrix;
}

String* Joint::toString()
{
	return ::java::lang::StringBuilder().append(u"Joint [groupId="_j)->append(groupId)
		->append(u", bindMatrix="_j)
		->append(static_cast< Object* >(bindMatrix))
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Joint::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.model.Joint", 23);
    return c;
}

java::lang::Class* Joint::getClass0()
{
	return class_();
}

