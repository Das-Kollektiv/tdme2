#include <tdme/gui/elements/GUISelectBox.h>

#include <tdme/gui/elements/GUISelectBoxController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using tdme::gui::elements::GUISelectBox;
using tdme::gui::elements::GUISelectBoxController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

GUISelectBox::GUISelectBox() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"selectbox.xml");
}

wstring GUISelectBox::NAME = L"selectbox";

const wstring& GUISelectBox::getName()
{
	return NAME;
}

const wstring& GUISelectBox::getTemplate()
{
	return template_;
}

map<wstring, wstring>* GUISelectBox::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	attributes[L"width"] = L"100%";
	attributes[L"height"] = L"auto";
	return &attributes;
}

GUINodeController* GUISelectBox::createController(GUINode* node)
{
	return new GUISelectBoxController(node);
}

