// Generated from /tdme/src/tdme/gui/elements/GUISelectBoxMultipleOption.java
#include <tdme/gui/elements/GUISelectBoxMultipleOption.h>

#include <tdme/gui/elements/GUISelectBoxMultipleOptionController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemException.h>
#include <tdme/os/_FileSystemInterface.h>

using std::map;
using std::wstring;

using tdme::gui::elements::GUISelectBoxMultipleOption;
using tdme::gui::elements::GUISelectBoxMultipleOptionController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemException;
using tdme::os::_FileSystemInterface;

GUISelectBoxMultipleOption::GUISelectBoxMultipleOption(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
}

GUISelectBoxMultipleOption::GUISelectBoxMultipleOption() throw (_FileSystemException)
	: GUISelectBoxMultipleOption(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

wstring GUISelectBoxMultipleOption::NAME = L"selectbox-multiple-option";

void GUISelectBoxMultipleOption::ctor() throw (_FileSystemException)
{
	super::ctor();
	template_ = _FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"selectbox-multiple-option.xml");
}

const wstring& GUISelectBoxMultipleOption::getName()
{
	return NAME;
}

const wstring& GUISelectBoxMultipleOption::getTemplate()
{
	return template_;
}

map<wstring, wstring>* GUISelectBoxMultipleOption::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	return &attributes;
}

GUINodeController* GUISelectBoxMultipleOption::createController(GUINode* node)
{
	return new GUISelectBoxMultipleOptionController(node);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUISelectBoxMultipleOption::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUISelectBoxMultipleOption", 44);
    return c;
}

java::lang::Class* GUISelectBoxMultipleOption::getClass0()
{
	return class_();
}

