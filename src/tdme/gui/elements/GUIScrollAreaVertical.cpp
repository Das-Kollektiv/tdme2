#include <tdme/gui/elements/GUIScrollAreaVertical.h>

#include <tdme/gui/elements/GUIScrollAreaVerticalController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using tdme::gui::elements::GUIScrollAreaVertical;
using tdme::gui::elements::GUIScrollAreaVerticalController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

GUIScrollAreaVertical::GUIScrollAreaVertical() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"scrollarea-vertical.xml");
}

wstring GUIScrollAreaVertical::NAME = L"scrollarea-vertical";

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

