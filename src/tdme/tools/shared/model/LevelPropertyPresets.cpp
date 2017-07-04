// Generated from /tdme/src/tdme/tools/shared/model/LevelPropertyPresets.java
#include <tdme/tools/shared/model/LevelPropertyPresets.h>

#include <string>
#include <vector>

#include <java/lang/ClassCastException.h>
#include <java/lang/Exception.h>
#include <java/lang/NullPointerException.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Iterator.h>
#include <javax/xml/parsers/DocumentBuilder.h>
#include <javax/xml/parsers/DocumentBuilderFactory.h>
#include <org/w3c/dom/Document.h>
#include <org/w3c/dom/Element.h>
#include <org/w3c/dom/Node.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Color4Base.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/tools/shared/model/LevelEditorLevel.h>
#include <tdme/tools/shared/model/LevelEditorLight.h>
#include <tdme/tools/shared/model/PropertyModelClass.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/utils/_ArrayList.h>
#include <tdme/utils/_HashMap.h>
#include <tdme/utils/_HashMap_ValuesIterator.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/StringConverter.h>

#include <ext/tinyxml/tinyxml.h>

using std::vector;
using std::string;

using tdme::tools::shared::model::LevelPropertyPresets;
using java::lang::ClassCastException;
using java::lang::Exception;
using java::lang::NullPointerException;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::HashMap;
using java::util::Iterator;
using tdme::engine::model::Color4;
using tdme::engine::model::Color4Base;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
using tdme::tools::shared::model::LevelEditorLevel;
using tdme::tools::shared::model::LevelEditorLight;
using tdme::tools::shared::model::PropertyModelClass;
using tdme::tools::shared::tools::Tools;
using tdme::utils::_ArrayList;
using tdme::utils::_HashMap;
using tdme::utils::_HashMap_ValuesIterator;
using tdme::utils::_Console;
using tdme::ext::tinyxml::TiXmlDocument;
using tdme::ext::tinyxml::TiXmlElement;
using tdme::utils::StringConverter;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

LevelPropertyPresets::LevelPropertyPresets(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

LevelPropertyPresets::LevelPropertyPresets(String* pathName, String* fileName)  /* throws(Exception) */
	: LevelPropertyPresets(*static_cast< ::default_init_tag* >(0))
{
	ctor(pathName,fileName);
}

LevelPropertyPresets* LevelPropertyPresets::instance;

LevelPropertyPresets* LevelPropertyPresets::getInstance()
{
	clinit();
	if (instance == nullptr) {
		try {
			instance = new LevelPropertyPresets(u"resources/tools/leveleditor/gd"_j, u"presets.xml"_j);
		} catch (Exception* exception) {
			_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Couldn't load level property presets: "_j)->append(exception->getMessage())->toString()));
		}
	}
	return instance;
}

void LevelPropertyPresets::setDefaultLevelProperties(LevelEditorLevel* level)
{
	for (auto _i = getMapPropertiesPreset()->iterator(); _i->hasNext(); ) {
		PropertyModelClass* mapProperty = java_cast< PropertyModelClass* >(_i->next());
		{
			level->addProperty(mapProperty->getName(), mapProperty->getValue());
		}
	}
}

void LevelPropertyPresets::ctor(String* pathName, String* fileName) /* throws(Exception) */
{
	super::ctor();
	mapPropertiesPreset = new _ArrayList();
	objectPropertiesPresets = new _HashMap();
	lightPresets = new _HashMap();

	string fileNameUtf8 = StringConverter::toString(pathName->getCPPWString() + L"/" + fileName->getCPPWString());
	TiXmlDocument xml;
	if (xml.LoadFile(fileNameUtf8) == false) {
		_Console::println("LevelPropertyPresets::ctor():: Could not load file '" + fileNameUtf8 + "'. Error='" + xml.ErrorDesc() + "'. Exiting.\n");
		exit( 1 );
	}
	TiXmlElement* xmlRoot = xml.RootElement();

	for (auto xmlMap: getChildrenByTagName(xmlRoot, "map")) {
		for (auto xmlProperty: getChildrenByTagName(xmlMap, "property")) {
			mapPropertiesPreset->add(
				new PropertyModelClass(
					new String(StringConverter::toWideString(xmlProperty->Attribute("name"))),
					new String(StringConverter::toWideString(xmlProperty->Attribute("value")))
				)
			);
		}
	}

	for (auto xmlObject: getChildrenByTagName(xmlRoot, "object")) {
		for (auto xmlType: getChildrenByTagName(xmlObject, "type")) {
			auto typeId = new String(StringConverter::toWideString(xmlType->Attribute("id")));
			auto objectPropertiesPreset = new _ArrayList();
			objectPropertiesPresets->put(typeId, objectPropertiesPreset);
			objectPropertiesPreset->add(new PropertyModelClass(u"preset"_j, typeId));
			for (auto xmlProperty: getChildrenByTagName(xmlType, "property")) {
				objectPropertiesPreset->add(
					new PropertyModelClass(
						new String(StringConverter::toWideString(xmlProperty->Attribute("name"))),
						new String(StringConverter::toWideString(xmlProperty->Attribute("value")))
					)
				);
			}
		}
	}

	auto lightId = 0;
	for (auto xmlLights: getChildrenByTagName(xmlRoot, "lights")) {
		for (auto xmlType: getChildrenByTagName(xmlLights, "type")) {
			{
				auto typeId = new String(StringConverter::toWideString((xmlType->Attribute("id"))));
				auto light = new LevelEditorLight(lightId++);
				light->getAmbient()->set(static_cast< Color4Base* >(Tools::convertToColor4(new String(StringConverter::toWideString(getChildrenByTagName(xmlType, "ambient").at(0)->GetText())))));
				light->getDiffuse()->set(static_cast< Color4Base* >(Tools::convertToColor4(new String(StringConverter::toWideString(getChildrenByTagName(xmlType, "diffuse").at(0)->GetText())))));
				light->getSpecular()->set(static_cast< Color4Base* >(Tools::convertToColor4(new String(StringConverter::toWideString(getChildrenByTagName(xmlType, "specular").at(0)->GetText())))));
				light->getPosition()->set(Tools::convertToVector4(new String(StringConverter::toWideString(getChildrenByTagName(xmlType, "position").at(0)->GetText()))));
				light->setConstantAttenuation(Tools::convertToFloat(new String(StringConverter::toWideString(getChildrenByTagName(xmlType, "constant_attenuation").at(0)->GetText()))));
				light->setLinearAttenuation(Tools::convertToFloat(new String(StringConverter::toWideString(getChildrenByTagName(xmlType, "linear_attenuation").at(0)->GetText()))));
				light->setQuadraticAttenuation(Tools::convertToFloat(new String(StringConverter::toWideString(getChildrenByTagName(xmlType, "quadratic_attenuation").at(0)->GetText()))));
				light->getSpotTo()->set(Tools::convertToVector3(new String(StringConverter::toWideString(getChildrenByTagName(xmlType, "spot_to").at(0)->GetText()))));
				light->getSpotDirection()->set(Tools::convertToVector3(new String(StringConverter::toWideString(getChildrenByTagName(xmlType, "spot_direction").at(0)->GetText()))));
				light->setSpotExponent(Tools::convertToFloat(new String(StringConverter::toWideString(getChildrenByTagName(xmlType, "spot_exponent").at(0)->GetText()))));
				light->setSpotCutOff(Tools::convertToFloat(new String(StringConverter::toWideString(getChildrenByTagName(xmlType, "spot_cutoff").at(0)->GetText()))));
				light->setEnabled(true);
				lightPresets->put(typeId, light);
			}
		}
	}
}

_ArrayList* LevelPropertyPresets::getMapPropertiesPreset()
{
	return mapPropertiesPreset;
}

_HashMap* LevelPropertyPresets::getObjectPropertiesPresets()
{
	return objectPropertiesPresets;
}

_HashMap* LevelPropertyPresets::getLightPresets()
{
	return lightPresets;
}

const vector<TiXmlElement*> LevelPropertyPresets::getChildrenByTagName(TiXmlElement* parent, const char* name)
{
	clinit();
	vector<TiXmlElement*> elementList;
	for (auto *child = parent->FirstChildElement(name); child != nullptr; child = child->NextSiblingElement(name)) {
		elementList.push_back(child);
	}
	return elementList;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* LevelPropertyPresets::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.model.LevelPropertyPresets", 44);
    return c;
}

void LevelPropertyPresets::clinit()
{
	super::clinit();
	static bool in_cl_init = false;
	struct clinit_ {
		clinit_() {
			in_cl_init = true;
			instance = nullptr;
		}
	};

	if (!in_cl_init) {
		static clinit_ clinit_instance;
	}
}

java::lang::Class* LevelPropertyPresets::getClass0()
{
	return class_();
}

