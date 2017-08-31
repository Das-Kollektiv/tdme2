// Generated from /tdme/src/tdme/gui/elements/GUIScrollAreaVertical.java
#include <tdme/gui/elements/GUIScrollAreaVertical.h>

#include <java/lang/String.h>
#include <tdme/gui/elements/GUIScrollAreaVerticalController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemException.h>
#include <tdme/os/_FileSystemInterface.h>

using tdme::gui::elements::GUIScrollAreaVertical;
using java::lang::String;
using tdme::gui::elements::GUIScrollAreaVerticalController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemException;
using tdme::os::_FileSystemInterface;

GUIScrollAreaVertical::GUIScrollAreaVertical(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIScrollAreaVertical::GUIScrollAreaVertical() throw (_FileSystemException)
	: GUIScrollAreaVertical(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

String* GUIScrollAreaVertical::NAME;

void GUIScrollAreaVertical::ctor() throw (_FileSystemException)
{
	super::ctor();
	template_ = new String(_FileSystem::getInstance()->getContent(u"resources/gui/definitions/elements"_j, u"scrollarea-vertical.xml"_j));
}

String* GUIScrollAreaVertical::getName()
{
	return NAME;
}

String* GUIScrollAreaVertical::getTemplate()
{
	return template_;
}

map<wstring, String*>* GUIScrollAreaVertical::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	attributes[L"width"] = u"100%"_j;
	attributes[L"height"] = u"100%"_j;
	attributes[L"horizontal-align"] = u"left"_j;
	attributes[L"vertical-align"] = u"top"_j;
	attributes[L"alignment"] = u"vertical"_j;
	attributes[L"background-color"] = u"transparent"_j;
	attributes[L"border"] = u"0"_j;
	attributes[L"border-color"] = u"transparent"_j;
	attributes[L"padding"] = u"0"_j;
	attributes[L"show-on"] = u""_j;
	attributes[L"hide-on"] = u""_j;
	return &attributes;
}

GUINodeController* GUIScrollAreaVertical::createController(GUINode* node)
{
	return new GUIScrollAreaVerticalController(node);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIScrollAreaVertical::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUIScrollAreaVertical", 39);
    return c;
}

void GUIScrollAreaVertical::clinit()
{
struct string_init_ {
	string_init_() {
	NAME = u"scrollarea-vertical"_j;
	}
};

	static string_init_ string_init_instance;

	super::clinit();
}

java::lang::Class* GUIScrollAreaVertical::getClass0()
{
	return class_();
}

