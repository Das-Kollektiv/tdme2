#include <tdme/gui/elements/GUISelectBoxMultipleOption.h>

#include <tdme/gui/elements/GUISelectBoxMultipleOptionController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::map;
using std::wstring;

using tdme::gui::elements::GUISelectBoxMultipleOption;
using tdme::gui::elements::GUISelectBoxMultipleOptionController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

GUISelectBoxMultipleOption::GUISelectBoxMultipleOption(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
}

GUISelectBoxMultipleOption::GUISelectBoxMultipleOption() throw (FileSystemException)
	: GUISelectBoxMultipleOption(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

wstring GUISelectBoxMultipleOption::NAME = L"selectbox-multiple-option";

void GUISelectBoxMultipleOption::ctor() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"selectbox-multiple-option.xml");
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

