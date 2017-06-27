// Generated from /tdme/src/tdme/gui/elements/GUIScrollAreaHorizontal.java
#include <tdme/gui/elements/GUIScrollAreaHorizontal.h>

#include <java/lang/String.h>
#include <tdme/gui/elements/GUIScrollAreaHorizontalController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/utils/_HashMap.h>

using tdme::gui::elements::GUIScrollAreaHorizontal;
using java::lang::String;
using tdme::gui::elements::GUIScrollAreaHorizontalController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
using tdme::utils::_HashMap;

GUIScrollAreaHorizontal::GUIScrollAreaHorizontal(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIScrollAreaHorizontal::GUIScrollAreaHorizontal()  /* throws(IOException) */
	: GUIScrollAreaHorizontal(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

String* GUIScrollAreaHorizontal::NAME;

void GUIScrollAreaHorizontal::ctor() /* throws(IOException) */
{
	super::ctor();
	attributes = new _HashMap();
	template_ = _FileSystem::getInstance()->getContent(u"resources/gui/definitions/elements"_j, u"scrollarea-horizontal.xml"_j);
}

String* GUIScrollAreaHorizontal::getName()
{
	return NAME;
}

String* GUIScrollAreaHorizontal::getTemplate()
{
	return template_;
}

_HashMap* GUIScrollAreaHorizontal::getAttributes(GUIScreenNode* screenNode)
{
	attributes->clear();
	attributes->put(u"id"_j, screenNode->allocateNodeId());
	attributes->put(u"width"_j, u"100%"_j);
	attributes->put(u"height"_j, u"100%"_j);
	attributes->put(u"horizontal-align"_j, u"left"_j);
	attributes->put(u"vertical-align"_j, u"top"_j);
	attributes->put(u"alignment"_j, u"vertical"_j);
	attributes->put(u"background-color"_j, u"transparent"_j);
	attributes->put(u"border"_j, u"0"_j);
	attributes->put(u"border-color"_j, u"transparent"_j);
	attributes->put(u"padding"_j, u"0"_j);
	attributes->put(u"show-on"_j, u""_j);
	attributes->put(u"hide-on"_j, u""_j);
	return attributes;
}

GUINodeController* GUIScrollAreaHorizontal::createController(GUINode* node)
{
	return new GUIScrollAreaHorizontalController(node);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIScrollAreaHorizontal::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUIScrollAreaHorizontal", 41);
    return c;
}

void GUIScrollAreaHorizontal::clinit()
{
struct string_init_ {
	string_init_() {
	NAME = u"scrollarea-horizontal"_j;
	}
};

	static string_init_ string_init_instance;

	super::clinit();
}

java::lang::Class* GUIScrollAreaHorizontal::getClass0()
{
	return class_();
}

