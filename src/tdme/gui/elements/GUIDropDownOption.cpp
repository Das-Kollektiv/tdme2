#include <tdme/gui/elements/GUIDropDownOption.h>

#include <tdme/gui/elements/GUIDropDownOptionController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/_FileSystem.h>
#include <tdme/os/filesystem/_FileSystemException.h>
#include <tdme/os/filesystem/_FileSystemInterface.h>

using tdme::gui::elements::GUIDropDownOption;
using tdme::gui::elements::GUIDropDownOptionController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::_FileSystem;
using tdme::os::filesystem::_FileSystemException;
using tdme::os::filesystem::_FileSystemInterface;

GUIDropDownOption::GUIDropDownOption(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
}

GUIDropDownOption::GUIDropDownOption() throw (_FileSystemException)
	: GUIDropDownOption(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

wstring GUIDropDownOption::NAME = L"dropdown-option";

void GUIDropDownOption::ctor() throw (_FileSystemException)
{
	template_ = _FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"dropdown-option.xml");
}

const wstring& GUIDropDownOption::getName()
{
	return NAME;
}

const wstring& GUIDropDownOption::getTemplate()
{
	return template_;
}

map<wstring, wstring>* GUIDropDownOption::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	return &attributes;
}

GUINodeController* GUIDropDownOption::createController(GUINode* node)
{
	return new GUIDropDownOptionController(node);
}
