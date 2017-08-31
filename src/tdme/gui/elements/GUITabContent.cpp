// Generated from /tdme/src/tdme/gui/elements/GUITabContent.java
#include <tdme/gui/elements/GUITabContent.h>

#include <map>
#include <string>

#include <java/lang/String.h>
#include <tdme/gui/elements/GUITabContentController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemException.h>
#include <tdme/os/_FileSystemInterface.h>

using std::map;
using std::wstring;

using tdme::gui::elements::GUITabContent;
using java::lang::String;
using tdme::gui::elements::GUITabContentController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemException;
using tdme::os::_FileSystemInterface;

GUITabContent::GUITabContent(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUITabContent::GUITabContent() throw (_FileSystemException)
	: GUITabContent(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

String* GUITabContent::NAME;

void GUITabContent::ctor() throw (_FileSystemException)
{
	super::ctor();
	template_ = new String(_FileSystem::getInstance()->getContent(u"resources/gui/definitions/elements"_j, u"tab-content.xml"_j));
}

String* GUITabContent::getName()
{
	return NAME;
}

String* GUITabContent::getTemplate()
{
	return template_;
}

map<wstring, String*>* GUITabContent::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	attributes[L"horizontal-align"] = u"center"_j;
	attributes[L"vertical-align"] = u"center"_j;
	return &attributes;
}

GUINodeController* GUITabContent::createController(GUINode* node)
{
	return new GUITabContentController(node);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUITabContent::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUITabContent", 31);
    return c;
}

void GUITabContent::clinit()
{
struct string_init_ {
	string_init_() {
	NAME = u"tab-content"_j;
	}
};

	static string_init_ string_init_instance;

	super::clinit();
}

java::lang::Class* GUITabContent::getClass0()
{
	return class_();
}

