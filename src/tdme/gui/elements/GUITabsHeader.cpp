// Generated from /tdme/src/tdme/gui/elements/GUITabsHeader.java
#include <tdme/gui/elements/GUITabsHeader.h>

#include <java/lang/String.h>
#include <tdme/gui/elements/GUITabsHeaderController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/utils/_HashMap.h>

using tdme::gui::elements::GUITabsHeader;
using java::lang::String;
using tdme::gui::elements::GUITabsHeaderController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
using tdme::utils::_HashMap;

GUITabsHeader::GUITabsHeader(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUITabsHeader::GUITabsHeader()  /* throws(IOException) */
	: GUITabsHeader(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

String* GUITabsHeader::NAME;

void GUITabsHeader::ctor() /* throws(IOException) */
{
	super::ctor();
	attributes = new _HashMap();
	template_ = new String(_FileSystem::getInstance()->getContent(u"resources/gui/definitions/elements"_j, u"tabs-header.xml"_j));
}

String* GUITabsHeader::getName()
{
	return NAME;
}

String* GUITabsHeader::getTemplate()
{
	return template_;
}

_HashMap* GUITabsHeader::getAttributes(GUIScreenNode* screenNode)
{
	attributes->clear();
	attributes->put(u"id"_j, screenNode->allocateNodeId());
	return attributes;
}

GUINodeController* GUITabsHeader::createController(GUINode* node)
{
	return new GUITabsHeaderController(node);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUITabsHeader::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUITabsHeader", 31);
    return c;
}

void GUITabsHeader::clinit()
{
struct string_init_ {
	string_init_() {
	NAME = u"tabs-header"_j;
	}
};

	static string_init_ string_init_instance;

	super::clinit();
}

java::lang::Class* GUITabsHeader::getClass0()
{
	return class_();
}

