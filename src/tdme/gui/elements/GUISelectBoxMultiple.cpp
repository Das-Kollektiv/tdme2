#include <tdme/gui/elements/GUISelectBoxMultiple.h>

#include <tdme/gui/elements/GUISelectBoxMultipleController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using tdme::gui::elements::GUISelectBoxMultiple;
using tdme::gui::elements::GUISelectBoxMultipleController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

GUISelectBoxMultiple::GUISelectBoxMultiple() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"selectbox-multiple.xml");
}

wstring GUISelectBoxMultiple::NAME = L"selectbox-multiple";

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

