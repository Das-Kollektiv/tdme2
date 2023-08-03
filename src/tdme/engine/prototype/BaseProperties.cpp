#include <tdme/engine/prototype/BaseProperties.h>

#include <algorithm>
#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/BaseProperty.h>

using std::remove;
using std::string;
using std::unique_ptr;

using tdme::engine::prototype::BaseProperties;
using tdme::engine::prototype::BaseProperty;

BaseProperties::BaseProperties(const string& name, const string& description)
{
	this->name = name;
	this->description = description;
}

BaseProperties::~BaseProperties() {
}

void BaseProperties::clearProperties()
{
	properties.clear();
	propertiesByName.clear();
}

const BaseProperty* BaseProperties::getProperty(const string& name) const
{
	auto propertyByNameIt = propertiesByName.find(name);
	if (propertyByNameIt != propertiesByName.end()) {
		return propertyByNameIt->second;
	}
	return nullptr;
}

BaseProperty* BaseProperties::getProperty(const string& name)
{
	auto propertyByNameIt = propertiesByName.find(name);
	if (propertyByNameIt != propertiesByName.end()) {
		return propertyByNameIt->second;
	}
	return nullptr;
}

const int BaseProperties::getPropertyIndex(const string& name) const
{
	for (auto i = 0; i < properties.size(); i++) {
		if (properties[i]->getName() == name) {
			return i;
		}
	}
	return -1;
}

int BaseProperties::getPropertyIndex(const string& name)
{
	for (auto i = 0; i < properties.size(); i++) {
		if (properties[i]->getName() == name) {
			return i;
		}
	}
	return -1;
}

bool BaseProperties::addProperty(const string& name, const string& value)
{
	if (getProperty(name) != nullptr)
		return false;

	auto property = new BaseProperty(name, value);
	propertiesByName[name] = property;
	properties.push_back(unique_ptr<BaseProperty>(property));
	return true;
}

bool BaseProperties::renameProperty(const string& oldName, const string& name) {
	auto propertyByNameIt = propertiesByName.find(oldName);
	if (propertyByNameIt == propertiesByName.end())
		return false;

	if (oldName != name && getProperty(name) != nullptr) {
		return false;
	}

	BaseProperty* property = propertyByNameIt->second;
	property->setName(name);

	propertiesByName.erase(propertyByNameIt);
	propertiesByName[property->getName()] = property;

	return true;
}

bool BaseProperties::updateProperty(const string& oldName, const string& name, const string& value)
{
	auto propertyByNameIt = propertiesByName.find(oldName);
	if (propertyByNameIt == propertiesByName.end())
		return false;

	if (oldName != name && getProperty(name) != nullptr) {
		return false;
	}

	BaseProperty* property = propertyByNameIt->second;
	property->setName(name);
	property->setValue(value);

	propertiesByName.erase(propertyByNameIt);
	propertiesByName[property->getName()] = property;

	return true;
}

bool BaseProperties::removeProperty(const string& name)
{
	auto propertyByNameIt = propertiesByName.find(name);
	if (propertyByNameIt != propertiesByName.end()) {
		auto property = propertyByNameIt->second;
		for (auto i = 0; i < properties.size(); i++) {
			if (properties[i].get() == property) {
				properties.erase(properties.begin() + i);
				break;
			}
		}
		propertiesByName.erase(propertyByNameIt);
		return true;
	}

	return false;
}
