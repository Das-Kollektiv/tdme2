#include <tdme/gui/elements/GUITabContent.h>

#include <map>
#include <string>

#include <tdme/gui/elements/GUITabContentController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::map;
using std::wstring;

using tdme::gui::elements::GUITabContent;
using tdme::gui::elements::GUITabContentController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

GUITabContent::GUITabContent() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"tab-content.xml");
}

wstring GUITabContent::NAME = L"tab-content";

const wstring& GUITabContent::getName()
{
	return NAME;
}

const wstring& GUITabContent::getTemplate()
{
	return template_;
}

map<wstring, wstring>* GUITabContent::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	attributes[L"horizontal-align"] = L"center";
	attributes[L"vertical-align"] = L"center";
	return &attributes;
}

GUINodeController* GUITabContent::createController(GUINode* node)
{
	return new GUITabContentController(node);
}

