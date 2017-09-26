// Generated from /tdme/src/tdme/gui/elements/GUISelectBoxMultiple.java
#include <tdme/gui/elements/GUISelectBoxMultiple.h>

#include <tdme/gui/elements/GUISelectBoxMultipleController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemException.h>
#include <tdme/os/_FileSystemInterface.h>

using tdme::gui::elements::GUISelectBoxMultiple;
using tdme::gui::elements::GUISelectBoxMultipleController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemException;
using tdme::os::_FileSystemInterface;

GUISelectBoxMultiple::GUISelectBoxMultiple(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUISelectBoxMultiple::GUISelectBoxMultiple() throw (_FileSystemException)
	: GUISelectBoxMultiple(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

wstring GUISelectBoxMultiple::NAME = L"selectbox-multiple";

void GUISelectBoxMultiple::ctor() throw (_FileSystemException)
{
	super::ctor();
	template_ = _FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"selectbox-multiple.xml");
}

const wstring& GUISelectBoxMultiple::getName()
{
	return NAME;
}

const wstring& GUISelectBoxMultiple::getTemplate()
{
	return template_;
}

map<wstring, wstring>* GUISelectBoxMultiple::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	attributes[L"width"] = L"100%";
	attributes[L"height"] = L"auto";
	return &attributes;
}

GUINodeController* GUISelectBoxMultiple::createController(GUINode* node)
{
	return new GUISelectBoxMultipleController(node);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUISelectBoxMultiple::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUISelectBoxMultiple", 38);
    return c;
}

java::lang::Class* GUISelectBoxMultiple::getClass0()
{
	return class_();
}

