#include <tdme/gui/elements/GUITabsContent.h>

#include <map>
#include <string>

#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>

using std::map;
using std::wstring;

using tdme::gui::elements::GUITabsContent;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;

GUITabsContent::GUITabsContent() throw (FileSystemException)
{
	template_ = FileSystem::getInstance()->getContentAsString(L"resources/gui/definitions/elements", L"tabs-content.xml");
}

wstring GUITabsContent::NAME = L"tabs-content";

const wstring& GUITabsContent::getName()
{
	return NAME;
}

const wstring& GUITabsContent::getTemplate()
{
	return template_;
}

map<wstring, wstring>* GUITabsContent::getAttributes(GUIScreenNode* screenNode)
{
	attributes.clear();
	attributes[L"id"] = screenNode->allocateNodeId();
	return &attributes;
}

GUINodeController* GUITabsContent::createController(GUINode* node)
{
	return nullptr;
}

