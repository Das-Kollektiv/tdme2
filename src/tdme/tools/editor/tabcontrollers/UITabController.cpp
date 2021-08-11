#include <tdme/tools/editor/tabcontrollers/UITabController.h>

#include <string>

#include <tdme/gui/GUI.h>
#include <tdme/utilities/Action.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/tabviews/UITabView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>

#include <ext/tinyxml/tinyxml.h>

using tdme::tools::editor::tabcontrollers::UITabController;

using std::string;

using tdme::utilities::Action;
using tdme::gui::GUI;
using tdme::gui::GUIParser;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::UITabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;

using tinyxml::TiXmlAttribute;
using tinyxml::TiXmlDocument;
using tinyxml::TiXmlElement;

#define AVOID_NULLPTR_STRING(arg) (arg == nullptr?"":arg)

UITabController::UITabController(UITabView* view)
{
	this->view = view;
	this->popUps = view->getPopUps();
}

UITabController::~UITabController() {
}

UITabView* UITabController::getView() {
	return view;
}

GUIScreenNode* UITabController::getScreenNode()
{
	return screenNode;
}

void UITabController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;

	//
	auto uiScreenNode = view->getUIScreenNode();
	this->screenXML = FileSystem::getInstance()->getContentAsString(
		Tools::getPathName(uiScreenNode->getFileName()),
		Tools::getFileName(uiScreenNode->getFileName())
	);
}

void UITabController::dispose()
{
}

void UITabController::save()
{
}

void UITabController::saveAs()
{
}

void UITabController::showErrorPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}

void UITabController::onValueChanged(GUIElementNode* node)
{
}

void UITabController::onFocus(GUIElementNode* node) {
}

void UITabController::onUnfocus(GUIElementNode* node) {
}

void UITabController::onContextMenuRequested(GUIElementNode* node, int mouseX, int mouseY) {
}

void UITabController::createOutlinerParentNodeNodesXML(TiXmlElement* xmlParentNode, string& xml, int& nodeIdx) {
	if (xmlParentNode->FirstChildElement() == nullptr) {
		auto nodeId = string(AVOID_NULLPTR_STRING(xmlParentNode->Attribute("id")));
		xml+= "<selectbox-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes(xmlParentNode->Value()) + (nodeId.empty() == false?string(" (") + nodeId + ")":"") + "\" value=\"" + GUIParser::escapeQuotes(to_string(nodeIdx++)) + "\" />\n";
	} else {
		auto nodeId = string(AVOID_NULLPTR_STRING(xmlParentNode->Attribute("id")));
		xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes(xmlParentNode->Value()) + (nodeId.empty() == false?string(" (") + nodeId + ")":"") + "\" value=\"" + GUIParser::escapeQuotes(to_string(nodeIdx++)) + "\" >\n";
		for (auto* childNode = xmlParentNode->FirstChildElement(); childNode != nullptr; childNode = childNode->NextSiblingElement()) {
			createOutlinerParentNodeNodesXML(childNode, xml, nodeIdx);
		}
		xml+= "</selectbox-parent-option>\n";
	}
}

void UITabController::setOutlinerContent() {
	Console::println("UITabController::setOutlinerContent()");
	string xml;
	if (screenXML.empty() == false) {
		try {
			TiXmlDocument xmlDocument;
			xmlDocument.Parse(screenXML.c_str());
			if (xmlDocument.Error() == true) {
				auto message = string("UITabController::setOutlinerContent(): Could not parse XML. Error='") + string(xmlDocument.ErrorDesc()) + "':\n\n" + screenXML;
				Console::println(message);
				throw GUIParserException(message);
			}
			TiXmlElement* xmlRoot = xmlDocument.RootElement();
			int nodeIdx = 0;
			createOutlinerParentNodeNodesXML(xmlRoot, xml, nodeIdx);
		} catch (Exception& exception) {
			showErrorPopUp("Warning", (string(exception.what())));
		}
	}
	view->getEditorView()->setOutlinerContent(xml);
}

void UITabController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
}
