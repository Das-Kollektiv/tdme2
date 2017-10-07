#include <tdme/gui/elements/GUIRadioButton.h>

#include <map>
#include <string>

#include <tdme/gui/elements/GUIRadioButtonController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/_FileSystem.h>
#include <tdme/os/filesystem/_FileSystemException.h>
#include <tdme/os/filesystem/_FileSystemInterface.h>

using std::map;
using std::wstring;

using tdme::gui::elements::GUIRadioButton;
using tdme::gui::elements::GUIRadioButtonController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::_FileSystem;
using tdme::os::filesystem::_FileSystemException;
using tdme::os::filesystem::_FileSystemInterface;

GUIRadioButton::GUIRadioButton(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
}

GUIRadioButton::GUIRadioButton() throw (_FileSystemException)
	: GUIRadioButton(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

wstring GUIRadioButton::NAME = L"radiobutton";

void GUIRadioButton::ctor() throw (_FileSystemException)
{
	template_ = _FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"radiobutton.xml");
}

const wstring& GUIRadioButton::getName()
{
	return NAME;
}

const wstring& GUIRadioButton::getTemplate()
{
	return template_;
}

map<wstring, wstring>* GUIRadioButton::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	attributes[L"name"] = L"";
	return &attributes;
}

GUINodeController* GUIRadioButton::createController(GUINode* node)
{
	return new GUIRadioButtonController(node);
}

