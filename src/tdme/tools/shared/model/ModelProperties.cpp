// Generated from /tdme/src/tdme/tools/shared/model/ModelProperties.java
#include <tdme/tools/shared/model/ModelProperties.h>

#include <java/lang/ClassCastException.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/tools/shared/model/PropertyModelClass.h>
#include <tdme/utils/_ArrayList.h>
#include <tdme/utils/_HashMap.h>

using tdme::tools::shared::model::ModelProperties;
using java::lang::ClassCastException;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::tools::shared::model::PropertyModelClass;
using tdme::utils::_ArrayList;
using tdme::utils::_HashMap;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

ModelProperties::ModelProperties(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

ModelProperties::ModelProperties() 
	: ModelProperties(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void ModelProperties::ctor()
{
	super::ctor();
	this->properties = new _ArrayList();
	this->propertiesByName = new _HashMap();
}

Iterable* ModelProperties::getProperties()
{
	return properties;
}

void ModelProperties::clearProperties()
{
	properties->clear();
	propertiesByName->clear();
}

PropertyModelClass* ModelProperties::getProperty(String* name)
{
	return java_cast< PropertyModelClass* >(propertiesByName->get(name));
}

int32_t ModelProperties::getPropertyCount()
{
	return properties->size();
}

int32_t ModelProperties::getPropertyIndex(String* name)
{
	for (auto i = 0; i < properties->size(); i++) {
		if (java_cast< PropertyModelClass* >(properties->get(i))->getName()->equals(name) == true) {
			return i;
		}
	}
	return -1;
}

PropertyModelClass* ModelProperties::getPropertyByIndex(int32_t idx)
{
	return idx >= 0 && idx < properties->size() ? java_cast< PropertyModelClass* >(properties->get(idx)) : static_cast< PropertyModelClass* >(nullptr);
}

bool ModelProperties::addProperty(String* name, String* value)
{
	if (propertiesByName->get(name) != nullptr)
		return false;

	auto property = new PropertyModelClass(name, value);
	propertiesByName->put(name, property);
	properties->add(property);
	return true;
}

bool ModelProperties::updateProperty(String* oldName, String* name, String* value)
{
	if (propertiesByName->get(oldName) == nullptr)
		return false;

	if (oldName->equals(name) == false && propertiesByName->get(name) != nullptr) {
		return false;
	}
	auto property = java_cast< PropertyModelClass* >(propertiesByName->remove(oldName));
	property->setName(name);
	property->setValue(value);
	propertiesByName->put(property->getName(), property);
	return true;
}

bool ModelProperties::removeProperty(String* name)
{
	if (propertiesByName->get(name) == nullptr)
		return false;

	auto property = java_cast< PropertyModelClass* >(propertiesByName->remove(name));
	properties->remove(static_cast< Object* >(property));
	return true;
}

String* ModelProperties::toString()
{
	return ::java::lang::StringBuilder().append(u"Properties [properties="_j)->append(static_cast< Object* >(properties))
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ModelProperties::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.model.ModelProperties", 39);
    return c;
}

java::lang::Class* ModelProperties::getClass0()
{
	return class_();
}

