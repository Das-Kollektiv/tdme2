#include <tdme/tools/editor/controllers/ImportDialogScreenController.h>

#include <string>

#include <agui/agui.h>
#include <agui/gui/events/GUIActionListener.h>
#include <agui/gui/events/GUIFocusListener.h>
#include <agui/gui/events/GUITooltipRequestListener.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/nodes/GUIStyledTextNode.h>
#include <agui/gui/nodes/GUITextNode.h>
#include <agui/gui/GUI.h>
#include <agui/gui/GUIParser.h>
#include <agui/utilities/MutableString.h>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Version.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/SelectorDialogScreenController.h>
#include <tdme/tools/editor/controllers/TooltipScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/StringTools.h>

using tdme::tools::editor::controllers::ImportDialogScreenController;

using std::string;

using agui::gui::events::GUIActionListener;
using agui::gui::events::GUIActionListenerType;
using agui::gui::events::GUIFocusListener;
using agui::gui::events::GUITooltipRequestListener;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::nodes::GUIStyledTextNode;
using agui::gui::nodes::GUITextNode;
using agui::gui::GUI;
using agui::gui::GUIParser;
using agui::utilities::MutableString;

using tdme::application::Application;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::Engine;
using tdme::engine::Version;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::SelectorDialogScreenController;
using tdme::tools::editor::controllers::TooltipScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::StringTools;

ImportDialogScreenController::ImportDialogScreenController(PopUps* popUps): popUps(popUps)
{
}

ImportDialogScreenController::~ImportDialogScreenController()
{
	screenNode = nullptr;
}

GUIScreenNode* ImportDialogScreenController::getScreenNode()
{
	return screenNode;
}

void ImportDialogScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse("resources/engine/gui", "popup_modelimport.xml");
		screenNode->setEnabled(false);
		screenNode->addActionListener(this);
		screenNode->addTooltipRequestListener(this);
		screenNode->invalidateLayouts();
	} catch (Exception& exception) {
		Console::printLine("ImportDialogScreenController::initialize(): An error occurred: " + string(exception.what()));
	}
}

void ImportDialogScreenController::dispose()
{
}

void ImportDialogScreenController::show(const string& fileName)
{
	screenNode->getNodeById("modelimport_path")->getController()->setValue(MutableString(fileName));
	screenNode->setEnabled(true);
}

void ImportDialogScreenController::close()
{
	screenNode->setEnabled(false);
}

void ImportDialogScreenController::onAction(GUIActionListenerType type, GUIElementNode* node)
{
	if (type == GUIActionListenerType::PERFORMED) {
		if (node->getId() == "modelimport_boundingvolume_node") {
			popUps->getSelectorDialogScreenController()->show();
		} else
		if (node->getId() == "modelimport_lod1_node") {
			popUps->getSelectorDialogScreenController()->show();
		} else
		if (node->getId() == "modelimport_lod2_node") {
			popUps->getSelectorDialogScreenController()->show();
		} else
		if (node->getId() == "modelimport_boundingvolume_open") {
			popUps->getFileDialogScreenController()->show(
				string(),
				"Load bounding volume model from: ",
				ModelReader::getModelExtensions(),
				string(),
				true,
				nullptr
			);
		} else
		if (node->getId() == "modelimport_lod1_open") {
			popUps->getFileDialogScreenController()->show(
				string(),
				"Load LOD1 model from: ",
				ModelReader::getModelExtensions(),
				string(),
				true,
				nullptr
			);
		} else
		if (node->getId() == "modelimport_lod2_open") {
			popUps->getFileDialogScreenController()->show(
				string(),
				"Load LOD2 model from: ",
				ModelReader::getModelExtensions(),
				string(),
				true,
				nullptr
			);
		} else
		if (StringTools::startsWith(node->getId(), "modelimport_caption_close_") == true) { // TODO: a.drewke, check with DH) {
			close();
		}
	}
}

void ImportDialogScreenController::onFocus(GUIElementNode* node) {
	GUI::setDisableTabFocusControl(node->getScreenNode() != screenNode);
}

void ImportDialogScreenController::onUnfocus(GUIElementNode* node) {
}

void ImportDialogScreenController::onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) {
	popUps->getTooltipScreenController()->show(mouseX, mouseY, node->getToolTip());
}

void ImportDialogScreenController::onTooltipCloseRequest() {
	popUps->getTooltipScreenController()->close();
}
