#include <tdme/tools/shared/model/LevelPropertyPresets.h>

#include <stdlib.h>

#include <map>
#include <string>
#include <vector>

#include <java/lang/String.h>

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
#include <tdme/utils/_Exception.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/StringConverter.h>

#include <ext/tinyxml/tinyxml.h>

using std::map;
using std::string;
using std::vector;

using java::lang::String;

using tdme::tools::shared::model::LevelPropertyPresets;
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
using tdme::utils::StringConverter;
using tdme::utils::_Exception;
using tdme::utils::_Console;
using tdme::ext::tinyxml::TiXmlDocument;
using tdme::ext::tinyxml::TiXmlElement;

LevelPropertyPresets* LevelPropertyPresets::instance = nullptr;

LevelPropertyPresets::LevelPropertyPresets(const wstring& pathName, const wstring& fileName)  /* throws(Exception) */
{
	auto xmlContent = _FileSystem::getInstance()->getContentAsString(pathName, fileName);
	TiXmlDocument xmlDocument;
	xmlDocument.Parse(StringConverter::toString(xmlContent).c_str());
	if (xmlDocument.Error() == true) {
		_Console::println(
			"LevelPropertyPresets::ctor():: Could not parse file '" +
			StringConverter::toString(pathName) + "/" + StringConverter::toString(fileName) +
			"'. Error='" +
			xmlDocument.ErrorDesc() +
			"'. Exiting.\n"
		);
		exit(1);
	}
	TiXmlElement* xmlRoot = xmlDocument.RootElement();

	for (auto xmlMap: getChildrenByTagName(xmlRoot, "map")) {
		for (auto xmlProperty: getChildrenByTagName(xmlMap, "property")) {
			mapPropertiesPreset.push_back(
				new PropertyModelClass(
					StringConverter::toWideString(xmlProperty->Attribute("name")),
					StringConverter::toWideString(xmlProperty->Attribute("value"))
				)
			);
		}
	}

	for (auto xmlObject: getChildrenByTagName(xmlRoot, "object")) {
		for (auto xmlType: getChildrenByTagName(xmlObject, "type")) {
			auto typeId = StringConverter::toWideString(xmlType->Attribute("id"));
			objectPropertiesPresets[typeId].push_back(new PropertyModelClass(L"preset", typeId));
			for (auto xmlProperty: getChildrenByTagName(xmlType, "property")) {
				objectPropertiesPresets[typeId].push_back(
					new PropertyModelClass(
						StringConverter::toWideString(xmlProperty->Attribute("name")),
						StringConverter::toWideString(xmlProperty->Attribute("value"))
					)
				);
			}
		}
	}

	auto lightId = 0;
	for (auto xmlLights: getChildrenByTagName(xmlRoot, "lights")) {
		for (auto xmlType: getChildrenByTagName(xmlLights, "type")) {
			{
				auto typeId = StringConverter::toWideString((xmlType->Attribute("id")));
				auto light = new LevelEditorLight(lightId++);
				light->getAmbient()->set(static_cast< Color4Base* >(Tools::convertToColor4(new String(StringConverter::toWideString(getChildrenByTagName(xmlType, "ambient").at(0)->GetText())))));
				light->getDiffuse()->set(static_cast< Color4Base* >(Tools::convertToColor4(new String(StringConverter::toWideString(getChildrenByTagName(xmlType, "diffuse").at(0)->GetText())))));
				light->getSpecular()->set(static_cast< Color4Base* >(Tools::convertToColor4(new String(StringConverter::toWideString(getChildrenByTagName(xmlType, "specular").at(0)->GetText())))));
				light->getPosition().set(Tools::convertToVector4(new String(StringConverter::toWideString(getChildrenByTagName(xmlType, "position").at(0)->GetText()))));
				light->setConstantAttenuation(Tools::convertToFloat(new String(StringConverter::toWideString(getChildrenByTagName(xmlType, "constant_attenuation").at(0)->GetText()))));
				light->setLinearAttenuation(Tools::convertToFloat(new String(StringConverter::toWideString(getChildrenByTagName(xmlType, "linear_attenuation").at(0)->GetText()))));
				light->setQuadraticAttenuation(Tools::convertToFloat(new String(StringConverter::toWideString(getChildrenByTagName(xmlType, "quadratic_attenuation").at(0)->GetText()))));
				light->getSpotTo().set(Tools::convertToVector3(new String(StringConverter::toWideString(getChildrenByTagName(xmlType, "spot_to").at(0)->GetText()))));
				light->getSpotDirection().set(Tools::convertToVector3(new String(StringConverter::toWideString(getChildrenByTagName(xmlType, "spot_direction").at(0)->GetText()))));
				light->setSpotExponent(Tools::convertToFloat(new String(StringConverter::toWideString(getChildrenByTagName(xmlType, "spot_exponent").at(0)->GetText()))));
				light->setSpotCutOff(Tools::convertToFloat(new String(StringConverter::toWideString(getChildrenByTagName(xmlType, "spot_cutoff").at(0)->GetText()))));
				light->setEnabled(true);
				lightPresets[typeId] = light;
			}
		}
	}
}

LevelPropertyPresets* LevelPropertyPresets::getInstance()
{
	if (instance == nullptr) {
		try {
			instance = new LevelPropertyPresets(L"resources/tools/leveleditor/gd", L"presets.xml");
		} catch (_Exception& exception) {
			_Console::println(string(" LevelPropertyPresets::getInstance(): An error occurred: "));
			_Console::print(string(exception.what()));
			exit(0);
		}
	}
	return instance;
}

void LevelPropertyPresets::setDefaultLevelProperties(LevelEditorLevel* level)
{
	for (auto mapProperty: mapPropertiesPreset) {
		level->addProperty(mapProperty->getName(), mapProperty->getValue());
	}
}

const vector<PropertyModelClass*>* LevelPropertyPresets::getMapPropertiesPreset() const
{
	return &mapPropertiesPreset;
}

const map<wstring, vector<PropertyModelClass*>>* LevelPropertyPresets::getObjectPropertiesPresets() const
{
	return &objectPropertiesPresets;
}

const map<wstring, LevelEditorLight*>* LevelPropertyPresets::getLightPresets() const
{
	return &lightPresets;
}

const vector<TiXmlElement*> LevelPropertyPresets::getChildrenByTagName(TiXmlElement* parent, const char* name)
{
	vector<TiXmlElement*> elementList;
	for (auto *child = parent->FirstChildElement(name); child != nullptr; child = child->NextSiblingElement(name)) {
		elementList.push_back(child);
	}
	return elementList;
}
