#include <tdme/tools/shared/model/PropertyModelClass.h>

#include <string>

using tdme::tools::shared::model::PropertyModelClass;

using std::string;

PropertyModelClass::PropertyModelClass(const string& name, const string& value)
{
	this->name = name;
	this->value = value;
}

const string& PropertyModelClass::getName()
{
	return name;
}

void PropertyModelClass::setName(const string& name)
{
	this->name = name;
}

const string& PropertyModelClass::getValue()
{
	return value;
}

void PropertyModelClass::setValue(const string& value)
{
	this->value = value;
}

PropertyModelClass* PropertyModelClass::clone()
{
	return new PropertyModelClass(name, value);
}
