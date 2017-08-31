// Generated from /tdme/src/tdme/gui/elements/GUITab.java
#include <tdme/gui/elements/GUITab.h>

#include <map>
#include <string>

#include <java/lang/String.h>
#include <tdme/gui/elements/GUITabController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemException.h>
#include <tdme/os/_FileSystemInterface.h>

using std::map;
using std::wstring;

using tdme::gui::elements::GUITab;
using java::lang::String;
using tdme::gui::elements::GUITabController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemException;
using tdme::os::_FileSystemInterface;

GUITab::GUITab(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUITab::GUITab() throw (_FileSystemException)
	: GUITab(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

String* GUITab::NAME;

void GUITab::ctor() throw (_FileSystemException)
{
	super::ctor();
	template_ = new String(_FileSystem::getInstance()->getContent(u"resources/gui/definitions/elements"_j, u"tab.xml"_j));
}

String* GUITab::getName()
{
	return NAME;
}

String* GUITab::getTemplate()
{
	return template_;
}

map<wstring, String*>* GUITab::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	return &attributes;
}

GUINodeController* GUITab::createController(GUINode* node)
{
	return new GUITabController(node);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUITab::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUITab", 24);
    return c;
}

void GUITab::clinit()
{
struct string_init_ {
	string_init_() {
	NAME = u"tab"_j;
	}
};

	static string_init_ string_init_instance;

	super::clinit();
}

java::lang::Class* GUITab::getClass0()
{
	return class_();
}

