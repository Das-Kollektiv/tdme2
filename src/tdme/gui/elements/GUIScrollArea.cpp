// Generated from /tdme/src/tdme/gui/elements/GUIScrollArea.java
#include <tdme/gui/elements/GUIScrollArea.h>

#include <java/lang/String.h>
#include <tdme/gui/elements/GUIScrollAreaController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/utils/_HashMap.h>

using tdme::gui::elements::GUIScrollArea;
using java::lang::String;
using tdme::gui::elements::GUIScrollAreaController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
using tdme::utils::_HashMap;

GUIScrollArea::GUIScrollArea(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIScrollArea::GUIScrollArea()  /* throws(IOException) */
	: GUIScrollArea(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

String* GUIScrollArea::NAME;

void GUIScrollArea::ctor() /* throws(IOException) */
{
	super::ctor();
	attributes = new _HashMap();
	template_ = _FileSystem::getInstance()->getContent(u"resources/gui/definitions/elements"_j, u"scrollarea.xml"_j);
}

String* GUIScrollArea::getName()
{
	return NAME;
}

String* GUIScrollArea::getTemplate()
{
	return template_;
}

_HashMap* GUIScrollArea::getAttributes(GUIScreenNode* screenNode)
{
	attributes->clear();
	attributes->put(u"id"_j, screenNode->allocateNodeId());
	attributes->put(u"width"_j, u"100%"_j);
	attributes->put(u"height"_j, u"100%"_j);
	attributes->put(u"horizontal-align"_j, u"left"_j);
	attributes->put(u"vertical-align"_j, u"top"_j);
	attributes->put(u"alignment"_j, u"vertical"_j);
	attributes->put(u"background-color"_j, u"transparent"_j);
	attributes->put(u"show-on"_j, u""_j);
	attributes->put(u"hide-on"_j, u""_j);
	return attributes;
}

GUINodeController* GUIScrollArea::createController(GUINode* node)
{
	return new GUIScrollAreaController(node);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIScrollArea::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUIScrollArea", 31);
    return c;
}

void GUIScrollArea::clinit()
{
struct string_init_ {
	string_init_() {
	NAME = u"scrollarea"_j;
	}
};

	static string_init_ string_init_instance;

	super::clinit();
}

java::lang::Class* GUIScrollArea::getClass0()
{
	return class_();
}

