// Generated from /tdme/src/tdme/gui/elements/GUITab.java
#include <tdme/gui/elements/GUITab.h>

#include <java/lang/String.h>
#include <tdme/gui/elements/GUITabController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/utils/_HashMap.h>

using tdme::gui::elements::GUITab;
using java::lang::String;
using tdme::gui::elements::GUITabController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
using tdme::utils::_HashMap;

GUITab::GUITab(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUITab::GUITab()  /* throws(IOException) */
	: GUITab(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

String* GUITab::NAME;

void GUITab::ctor() /* throws(IOException) */
{
	super::ctor();
	attributes = new _HashMap();
	template_ = _FileSystem::getInstance()->getContent(u"resources/gui/definitions/elements"_j, u"tab.xml"_j);
}

String* GUITab::getName()
{
	return NAME;
}

String* GUITab::getTemplate()
{
	return template_;
}

_HashMap* GUITab::getAttributes(GUIScreenNode* screenNode)
{
	attributes->clear();
	attributes->put(u"id"_j, screenNode->allocateNodeId());
	return attributes;
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

