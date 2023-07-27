#include <tdme/engine/prototype/BaseProperties.h>

#include <algorithm>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/BaseProperty.h>

using std::remove;
using std::string;

using tdme::engine::prototype::BaseProperties;
using tdme::engine::prototype::BaseProperty;

BaseProperties::BaseProperties(const string& name, const string& description)
{
	this->name = name;
	this->description = description;
}

BaseProperties::~BaseProperties() {
	for (auto property: properties) {
		delete property;
	}
}

void BaseProperties::clearProperties()
{
	for (auto property: properties) {
		delete property;
	}
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
	properties.push_back(property);
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
		propertiesByName.erase(propertyByNameIt);
		properties.erase(remove(properties.begin(), properties.end(), property), properties.end());
		return true;
	}

	return false;
}
