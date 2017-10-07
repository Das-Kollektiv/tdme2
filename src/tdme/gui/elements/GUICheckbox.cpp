#include <tdme/gui/elements/GUICheckbox.h>

#include <map>
#include <string>

#include <tdme/gui/elements/GUICheckboxController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/_FileSystem.h>
#include <tdme/os/filesystem/_FileSystemException.h>
#include <tdme/os/filesystem/_FileSystemInterface.h>

using std::map;
using std::wstring;

using tdme::gui::elements::GUICheckbox;
using tdme::gui::elements::GUICheckboxController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::_FileSystem;
using tdme::os::filesystem::_FileSystemException;
using tdme::os::filesystem::_FileSystemInterface;

GUICheckbox::GUICheckbox(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
}

GUICheckbox::GUICheckbox() throw (_FileSystemException)
	: GUICheckbox(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

wstring GUICheckbox::NAME = L"checkbox";

void GUICheckbox::ctor() throw (_FileSystemException)
{
	template_ = _FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"checkbox.xml");
}

const wstring& GUICheckbox::getName()
{
	return NAME;
}

const wstring& GUICheckbox::getTemplate()
{
	return template_;
}

map<wstring, wstring>* GUICheckbox::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	return &attributes;
}

GUINodeController* GUICheckbox::createController(GUINode* node)
{
	return new GUICheckboxController(node);
}

