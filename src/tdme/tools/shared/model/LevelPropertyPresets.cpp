// Generated from /tdme/src/tdme/tools/shared/model/LevelPropertyPresets.java
#include <tdme/tools/shared/model/LevelPropertyPresets.h>

#include <java/lang/ClassCastException.h>
#include <java/lang/Exception.h>
#include <java/lang/NullPointerException.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/HashMap.h>
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
#include <tdme/utils/_Console.h>

using tdme::tools::shared::model::LevelPropertyPresets;
using java::lang::ClassCastException;
using java::lang::Exception;
using java::lang::NullPointerException;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::HashMap;
using java::util::Iterator;
using javax::xml::parsers::DocumentBuilder;
using javax::xml::parsers::DocumentBuilderFactory;
using org::w3c::dom::Document;
using org::w3c::dom::Element;
using org::w3c::dom::Node;
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
using tdme::utils::_Console;

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
	objectPropertiesPresets = new HashMap();
	lightPresets = new HashMap();
	auto builder = DocumentBuilderFactory::newInstance()->newDocumentBuilder();
	auto document = builder->parse(_FileSystem::getInstance()->getInputStream(pathName, fileName));
	auto xmlRoot = document->getDocumentElement();
	for (auto _i = getChildrenByTagName(xmlRoot, u"map"_j)->iterator(); _i->hasNext(); ) {
		Element* xmlMap = java_cast< Element* >(_i->next());
		
						for (auto _i = getChildrenByTagName(xmlMap, u"property"_j)->iterator(); _i->hasNext(); ) {
				Element* xmlProperty = java_cast< Element* >(_i->next());
				{
					mapPropertiesPreset->add(new PropertyModelClass(xmlProperty->getAttribute(u"name"_j), xmlProperty->getAttribute(u"value"_j)));
				}
			}

	}
	for (auto _i = getChildrenByTagName(xmlRoot, u"object"_j)->iterator(); _i->hasNext(); ) {
		Element* xmlObject = java_cast< Element* >(_i->next());
		
						for (auto _i = getChildrenByTagName(xmlObject, u"type"_j)->iterator(); _i->hasNext(); ) {
				Element* xmlType = java_cast< Element* >(_i->next());
				{
					auto typeId = xmlType->getAttribute(u"id"_j);
					auto objectPropertiesPreset = new _ArrayList();
					objectPropertiesPresets->put(typeId, objectPropertiesPreset);
					objectPropertiesPreset->add(new PropertyModelClass(u"preset"_j, typeId));
					for (auto _i = getChildrenByTagName(xmlType, u"property"_j)->iterator(); _i->hasNext(); ) {
						Element* xmlProperty = java_cast< Element* >(_i->next());
						{
							objectPropertiesPreset->add(new PropertyModelClass(xmlProperty->getAttribute(u"name"_j), xmlProperty->getAttribute(u"value"_j)));
						}
					}
				}
			}

	}
	auto lightId = 0;
	for (auto _i = getChildrenByTagName(xmlRoot, u"lights"_j)->iterator(); _i->hasNext(); ) {
		Element* xmlLights = java_cast< Element* >(_i->next());
		
						for (auto _i = getChildrenByTagName(xmlLights, u"type"_j)->iterator(); _i->hasNext(); ) {
				Element* xmlType = java_cast< Element* >(_i->next());
				{
					auto typeId = xmlType->getAttribute(u"id"_j);
					auto light = new LevelEditorLight(lightId++);
					light->getAmbient()->set(static_cast< Color4Base* >(Tools::convertToColor4(java_cast< Element* >(getChildrenByTagName(xmlType, u"ambient"_j)->get(0))->getTextContent())));
					light->getDiffuse()->set(static_cast< Color4Base* >(Tools::convertToColor4(java_cast< Element* >(getChildrenByTagName(xmlType, u"diffuse"_j)->get(0))->getTextContent())));
					light->getSpecular()->set(static_cast< Color4Base* >(Tools::convertToColor4(java_cast< Element* >(getChildrenByTagName(xmlType, u"specular"_j)->get(0))->getTextContent())));
					light->getPosition()->set(Tools::convertToVector4(java_cast< Element* >(getChildrenByTagName(xmlType, u"position"_j)->get(0))->getTextContent()));
					light->setConstantAttenuation(Tools::convertToFloat(java_cast< Element* >(getChildrenByTagName(xmlType, u"constant_attenuation"_j)->get(0))->getTextContent()));
					light->setLinearAttenuation(Tools::convertToFloat(java_cast< Element* >(getChildrenByTagName(xmlType, u"linear_attenuation"_j)->get(0))->getTextContent()));
					light->setQuadraticAttenuation(Tools::convertToFloat(java_cast< Element* >(getChildrenByTagName(xmlType, u"quadratic_attenuation"_j)->get(0))->getTextContent()));
					light->getSpotTo()->set(Tools::convertToVector3(java_cast< Element* >(getChildrenByTagName(xmlType, u"spot_to"_j)->get(0))->getTextContent()));
					light->getSpotDirection()->set(Tools::convertToVector3(java_cast< Element* >(getChildrenByTagName(xmlType, u"spot_direction"_j)->get(0))->getTextContent()));
					light->setSpotExponent(Tools::convertToFloat(java_cast< Element* >(getChildrenByTagName(xmlType, u"spot_exponent"_j)->get(0))->getTextContent()));
					light->setSpotCutOff(Tools::convertToFloat(java_cast< Element* >(getChildrenByTagName(xmlType, u"spot_cutoff"_j)->get(0))->getTextContent()));
					light->setEnabled(true);
					lightPresets->put(typeId, light);
				}
			}

	}
	_Console::println(static_cast< Object* >(lightPresets));
}

_ArrayList* LevelPropertyPresets::getMapPropertiesPreset()
{
	return mapPropertiesPreset;
}

HashMap* LevelPropertyPresets::getObjectPropertiesPresets()
{
	return objectPropertiesPresets;
}

HashMap* LevelPropertyPresets::getLightPresets()
{
	return lightPresets;
}

_ArrayList* LevelPropertyPresets::getChildrenByTagName(Element* parent, String* name)
{
	clinit();
	auto nodeList = new _ArrayList();
	for (auto *child = parent->getFirstChild(); child != nullptr; child = child->getNextSibling()) {
		if (child->getNodeType() == Node::ELEMENT_NODE && name->equals(child->getNodeName())) {
			nodeList->add(java_cast< Element* >(child));
		}
	}
	return nodeList;
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

