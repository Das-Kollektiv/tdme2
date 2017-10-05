// Generated from /tdme/src/tdme/gui/elements/GUIScrollAreaHorizontal.java
#include <tdme/gui/elements/GUIScrollAreaHorizontal.h>

#include <tdme/gui/elements/GUIScrollAreaHorizontalController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/_FileSystem.h>
#include <tdme/os/filesystem/_FileSystemException.h>
#include <tdme/os/filesystem/_FileSystemInterface.h>

using tdme::gui::elements::GUIScrollAreaHorizontal;
using tdme::gui::elements::GUIScrollAreaHorizontalController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::_FileSystem;
using tdme::os::filesystem::_FileSystemException;
using tdme::os::filesystem::_FileSystemInterface;

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

wstring GUIScrollAreaHorizontal::NAME = L"scrollarea-horizontal";

void GUIScrollAreaHorizontal::ctor() throw (_FileSystemException)
{
	super::ctor();
	template_ = _FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"scrollarea-horizontal.xml");
}

const wstring& GUIScrollAreaHorizontal::getName()
{
	return NAME;
}

const wstring& GUIScrollAreaHorizontal::getTemplate()
{
	return template_;
}

map<wstring, wstring>* GUIScrollAreaHorizontal::getAttributes(GUIScreenNode* screenNode)
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

java::lang::Class* GUIScrollAreaHorizontal::getClass0()
{
	return class_();
}

