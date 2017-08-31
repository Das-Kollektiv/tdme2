// Generated from /tdme/src/tdme/gui/elements/GUIScrollArea.java
#include <tdme/gui/elements/GUIScrollArea.h>

#include <java/lang/String.h>
#include <tdme/gui/elements/GUIScrollAreaController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemException.h>
#include <tdme/os/_FileSystemInterface.h>

using tdme::gui::elements::GUIScrollArea;
using java::lang::String;
using tdme::gui::elements::GUIScrollAreaController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemException;
using tdme::os::_FileSystemInterface;

GUIScrollArea::GUIScrollArea(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIScrollArea::GUIScrollArea() throw (_FileSystemException)
	: GUIScrollArea(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

String* GUIScrollArea::NAME;

void GUIScrollArea::ctor() throw (_FileSystemException)
{
	super::ctor();
	template_ = new String(_FileSystem::getInstance()->getContent(u"resources/gui/definitions/elements"_j, u"scrollarea.xml"_j));
}

String* GUIScrollArea::getName()
{
	return NAME;
}

String* GUIScrollArea::getTemplate()
{
	return template_;
}

map<wstring, String*>* GUIScrollArea::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	attributes[L"width"] = u"100%"_j;
	attributes[L"height"] = u"100%"_j;
	attributes[L"horizontal-align"] = u"left"_j;
	attributes[L"vertical-align"] = u"top"_j;
	attributes[L"alignment"] = u"vertical"_j;
	attributes[L"background-color"] = u"transparent"_j;
	attributes[L"show-on"] = u""_j;
	attributes[L"hide-on"] = u""_j;
	return &attributes;
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

