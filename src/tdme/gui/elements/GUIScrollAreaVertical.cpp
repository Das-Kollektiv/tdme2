// Generated from /tdme/src/tdme/gui/elements/GUIScrollAreaVertical.java
#include <tdme/gui/elements/GUIScrollAreaVertical.h>

#include <tdme/gui/elements/GUIScrollAreaVerticalController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemException.h>
#include <tdme/os/_FileSystemInterface.h>

using tdme::gui::elements::GUIScrollAreaVertical;
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

wstring GUIScrollAreaVertical::NAME = L"scrollarea-vertical";

void GUIScrollAreaVertical::ctor() throw (_FileSystemException)
{
	super::ctor();
	template_ = _FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"scrollarea-vertical.xml");
}

const wstring& GUIScrollAreaVertical::getName()
{
	return NAME;
}

const wstring& GUIScrollAreaVertical::getTemplate()
{
	return template_;
}

map<wstring, wstring>* GUIScrollAreaVertical::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	attributes[L"width"] = L"100%";
	attributes[L"height"] = L"100%";
	attributes[L"horizontal-align"] = L"left";
	attributes[L"vertical-align"] = L"top";
	attributes[L"alignment"] = L"vertical";
	attributes[L"background-color"] = L"transparent";
	attributes[L"border"] = L"0";
	attributes[L"border-color"] = L"transparent";
	attributes[L"padding"] = L"0";
	attributes[L"show-on"] = L"";
	attributes[L"hide-on"] = L"";
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

java::lang::Class* GUIScrollAreaVertical::getClass0()
{
	return class_();
}

