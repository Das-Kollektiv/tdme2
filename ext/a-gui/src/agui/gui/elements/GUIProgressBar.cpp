#include <agui/gui/elements/GUIProgressBar.h>

#include <agui/agui.h>
#include <string>
#include <agui/gui/elements/GUIProgressBarController.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/os/filesystem/FileSystem.h>
#include <agui/os/filesystem/FileSystemException.h>
#include <agui/os/filesystem/FileSystemInterface.h>
#include <unordered_map>

using std::string;
using std::unordered_map;

using agui::gui::elements::GUIProgressBar;
using agui::gui::elements::GUIProgressBarController;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIScreenNode;
using agui::os::filesystem::FileSystem;
using agui::os::filesystem::FileSystemException;
using agui::os::filesystem::FileSystemInterface;

string GUIProgressBar::NAME = "progress-bar";

GUIProgressBar::GUIProgressBar()
{
}

const string& GUIProgressBar::getName()
{
	return NAME;
}

const string GUIProgressBar::getTemplate(const string& applicationPathName, const string& applicationSubPathName, const string& fileName)
{
	return FileSystem::getInstance()->getContentAsString(applicationPathName + "/resources/" + applicationSubPathName + "/gui/definitions", fileName.empty() == true?"progressbar.xml":fileName);
}

unordered_map<string, string> GUIProgressBar::getAttributes(GUIScreenNode* screenNode)
{
	unordered_map<string, string> attributes;
	attributes["id"] = screenNode->allocateNodeId();
	attributes["disabled"] = "false";
	attributes["value"] = "0.0";
	attributes["width"] = "223"; // TODO: a.drewke
	return attributes;
}

GUINodeController* GUIProgressBar::createController(GUINode* node)
{
	return new GUIProgressBarController(node);
}

