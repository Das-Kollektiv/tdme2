// Generated from /tdme/src/tdme/gui/elements/GUIScrollAreaHorizontal.java
#include <tdme/gui/elements/GUIScrollAreaHorizontal.h>

#include <java/lang/String.h>
#include <tdme/gui/elements/GUIScrollAreaHorizontalController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemException.h>
#include <tdme/os/_FileSystemInterface.h>

using tdme::gui::elements::GUIScrollAreaHorizontal;
using java::lang::String;
using tdme::gui::elements::GUIScrollAreaHorizontalController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemException;
using tdme::os::_FileSystemInterface;

GUIScrollAreaHorizontal::GUIScrollAreaHorizontal(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIScrollAreaHorizontal::GUIScrollAreaHorizontal() throw (_FileSystemException)
	: GUIScrollAreaHorizontal(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

String* GUIScrollAreaHorizontal::NAME;

void GUIScrollAreaHorizontal::ctor() throw (_FileSystemException)
{
	super::ctor();
	template_ = new String(_FileSystem::getInstance()->getContent(u"resources/gui/definitions/elements"_j, u"scrollarea-horizontal.xml"_j));
}

String* GUIScrollAreaHorizontal::getName()
{
	return NAME;
}

String* GUIScrollAreaHorizontal::getTemplate()
{
	return template_;
}

map<wstring, String*>* GUIScrollAreaHorizontal::getAttributes(GUIScreenNode* screenNode)
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

