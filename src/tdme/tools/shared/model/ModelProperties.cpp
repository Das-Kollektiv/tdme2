// Generated from /tdme/src/tdme/tools/shared/model/ModelProperties.java
#include <tdme/tools/shared/model/ModelProperties.h>

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include <java/lang/Object.h>
#include <java/lang/StringBuilder.h>
#include <tdme/tools/shared/model/PropertyModelClass.h>

using std::map;
using std::remove;
using std::vector;
using std::wstring;

using tdme::tools::shared::model::ModelProperties;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::tools::shared::model::PropertyModelClass;

ModelProperties::ModelProperties() 
{
}

void ModelProperties::clearProperties()
{
	properties.clear();
	propertiesByName.clear();
}

PropertyModelClass* ModelProperties::getProperty(String* name)
{
	auto propertyByNameIt = propertiesByName.find(name->getCPPWString());
	if (propertyByNameIt != propertiesByName.end()) {
		return propertyByNameIt->second;
	}
	return nullptr;
}

int32_t ModelProperties::getPropertyCount()
{
	return properties.size();
}

int32_t ModelProperties::getPropertyIndex(String* name)
{
	for (auto i = 0; i < properties.size(); i++) {
		if (properties.at(i)->getName()->equals(name) == true) {
			return i;
		}
	}
	return -1;
}

PropertyModelClass* ModelProperties::getPropertyByIndex(int32_t idx)
{
	return idx >= 0 && idx < properties.size() ? properties.at(idx) : nullptr;
}

bool ModelProperties::addProperty(String* name, String* value)
{
	if (getProperty(name) != nullptr)
		return false;

	auto property = new PropertyModelClass(name, value);
	propertiesByName[name->getCPPWString()] = property;
	properties.push_back(property);
	return true;
}

bool ModelProperties::updateProperty(String* oldName, String* name, String* value)
{
	auto propertyByNameIt = propertiesByName.find(name->getCPPWString());
	if (propertyByNameIt == propertiesByName.end())
		return false;

	if (oldName->equals(name) == false && getProperty(name) != nullptr) {
		return false;
	}

	propertiesByName.erase(propertyByNameIt);

	PropertyModelClass* property = propertyByNameIt->second;
	property->setName(name);
	property->setValue(value);

	propertiesByName[property->getName()->getCPPWString()] = property;

	return true;
}

bool ModelProperties::removeProperty(String* name)
{
	auto propertyByNameIt = propertiesByName.find(name->getCPPWString());
	if (propertyByNameIt != propertiesByName.end()) {
		propertiesByName.erase(propertyByNameIt);
		properties.erase(remove(properties.begin(), properties.end(), propertyByNameIt->second), properties.end());
		return true;
	}

	return false;
}
