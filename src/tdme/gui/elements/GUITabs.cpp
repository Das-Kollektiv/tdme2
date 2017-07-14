// Generated from /tdme/src/tdme/gui/elements/GUITabs.java
#include <tdme/gui/elements/GUITabs.h>

#include <java/lang/String.h>
#include <tdme/gui/elements/GUITabsController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemException.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/utils/_HashMap.h>

using tdme::gui::elements::GUITabs;
using java::lang::String;
using tdme::gui::elements::GUITabsController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemException;
using tdme::os::_FileSystemInterface;
using tdme::utils::_HashMap;

GUITabs::GUITabs(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUITabs::GUITabs() throw (_FileSystemException)
	: GUITabs(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

String* GUITabs::NAME;

void GUITabs::ctor() throw (_FileSystemException)
{
	super::ctor();
	attributes = new _HashMap();
	template_ = new String(_FileSystem::getInstance()->getContent(u"resources/gui/definitions/elements"_j, u"tabs.xml"_j));
}

String* GUITabs::getName()
{
	return NAME;
}

String* GUITabs::getTemplate()
{
	return template_;
}

_HashMap* GUITabs::getAttributes(GUIScreenNode* screenNode)
{
	attributes->clear();
	attributes->put(u"id"_j, screenNode->allocateNodeId());
	attributes->put(u"width"_j, u"100%"_j);
	attributes->put(u"height"_j, u"*"_j);
	return attributes;
}

GUINodeController* GUITabs::createController(GUINode* node)
{
	return new GUITabsController(node);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUITabs::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUITabs", 25);
    return c;
}

void GUITabs::clinit()
{
struct string_init_ {
	string_init_() {
	NAME = u"tabs"_j;
	}
};

	static string_init_ string_init_instance;

	super::clinit();
}

java::lang::Class* GUITabs::getClass0()
{
	return class_();
}

