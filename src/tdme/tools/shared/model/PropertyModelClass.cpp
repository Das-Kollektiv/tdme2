// Generated from /tdme/src/tdme/tools/shared/model/PropertyModelClass.java
#include <tdme/tools/shared/model/PropertyModelClass.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>

using tdme::tools::shared::model::PropertyModelClass;
using java::lang::String;
using java::lang::StringBuilder;

PropertyModelClass::PropertyModelClass(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

PropertyModelClass::PropertyModelClass(String* name, String* value) 
	: PropertyModelClass(*static_cast< ::default_init_tag* >(0))
{
	ctor(name,value);
}

void PropertyModelClass::ctor(String* name, String* value)
{
	super::ctor();
	this->name = name;
	this->value = value;
}

String* PropertyModelClass::getName()
{
	return name;
}

void PropertyModelClass::setName(String* name)
{
	this->name = name;
}

String* PropertyModelClass::getValue()
{
	return value;
}

void PropertyModelClass::setValue(String* value)
{
	this->value = value;
}

PropertyModelClass* PropertyModelClass::clone()
{
	return new PropertyModelClass(new String(name), new String(value));
}

String* PropertyModelClass::toString()
{
	return ::java::lang::StringBuilder().append(name)->append(u": "_j)
		->append(value)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* PropertyModelClass::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.model.PropertyModelClass", 42);
    return c;
}

java::lang::Class* PropertyModelClass::getClass0()
{
	return class_();
}

