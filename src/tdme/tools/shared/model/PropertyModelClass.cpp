// Generated from /tdme/src/tdme/tools/shared/model/PropertyModelClass.java
#include <tdme/tools/shared/model/PropertyModelClass.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>

using tdme::tools::shared::model::PropertyModelClass;
using java::lang::String;
using java::lang::StringBuilder;

PropertyModelClass::PropertyModelClass(String* name, String* value) 
{
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
