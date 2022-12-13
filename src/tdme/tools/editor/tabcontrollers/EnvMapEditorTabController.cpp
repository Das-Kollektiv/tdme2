#include <tdme/tools/editor/tabcontrollers/EnvMapEditorTabController.h>

#include <array>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/Entity.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/controllers/TooltipScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabviews/EnvMapEditorTabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/MutableString.h>

using std::array;
using std::string;

using tdme::tools::editor::tabcontrollers::EnvMapEditorTabController;

using tdme::engine::prototype::Prototype;
using tdme::engine::Entity;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::GUIParser;
using tdme::math::Vector3;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::controllers::TooltipScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::EnvMapEditorTabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;
using tdme::utilities::Float;
using tdme::utilities::Integer;
using tdme::utilities::MutableString;

EnvMapEditorTabController::EnvMapEditorTabController(EnvMapEditorTabView* view)
{
	this->view = view;
	this->popUps = view->getPopUps();
}

EnvMapEditorTabController::~EnvMapEditorTabController() {
}

EnvMapEditorTabView* EnvMapEditorTabController::getView() {
	return view;
}

GUIScreenNode* EnvMapEditorTabController::getScreenNode()
{
	return screenNode;
}

void EnvMapEditorTabController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
}

void EnvMapEditorTabController::dispose()
{
}

void EnvMapEditorTabController::onCommand(TabControllerCommand command)
{
	switch (command) {
		case COMMAND_SAVE:
			{
				auto fileName = view->getPrototype() != nullptr?view->getPrototype()->getFileName():"";
				try {
					if (fileName.empty() == true) throw ExceptionBase("Could not save file. No filename known");
					view->saveFile(
						Tools::getPathName(fileName),
						Tools::getFileName(fileName)
					);
				} catch (Exception& exception) {
					showInfoPopUp("Warning", (string(exception.what())));
				}
			}
			break;
		case COMMAND_SAVEAS:
			{
				class OnEnvMapSave: public virtual Action
				{
				public:
					void performAction() override {
						try {
							envMapEditorTabController->view->saveFile(
								envMapEditorTabController->popUps->getFileDialogScreenController()->getPathName(),
								envMapEditorTabController->popUps->getFileDialogScreenController()->getFileName()
							);
						} catch (Exception& exception) {
							envMapEditorTabController->showInfoPopUp("Warning", (string(exception.what())));
						}
						envMapEditorTabController->popUps->getFileDialogScreenController()->close();
					}
					OnEnvMapSave(EnvMapEditorTabController* envMapEditorTabController): envMapEditorTabController(envMapEditorTabController) {
					}
				private:
					EnvMapEditorTabController* envMapEditorTabController;
				};

				auto fileName = view->getPrototype() != nullptr?view->getPrototype()->getFileName():"";
				vector<string> extensions = {
					"tenvmap"
				};
				popUps->getFileDialogScreenController()->show(
					fileName.empty() == false?Tools::getPathName(fileName):string(),
					"Save to: ",
					extensions,
					Tools::getFileName(fileName),
					false,
					new OnEnvMapSave(this)
				);
			}
			break;
		default:
			showInfoPopUp("Warning", "This command is not supported yet");
			break;
	}
}

void EnvMapEditorTabController::onDrop(const string& payload, int mouseX, int mouseY) {
	Console::println("EnvMapEditorTabController::onDrop(): " + payload + " @ " + to_string(mouseX) + ", " + to_string(mouseY));
	showInfoPopUp("Warning", "You can not drop a file here");
}

void EnvMapEditorTabController::showInfoPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}

void EnvMapEditorTabController::onChange(GUIElementNode* node)
{
	for (auto& applyNode: applyNodesRenderPasses) {
		if (node->getId() == applyNode) {
			applyRenderPasses();
			break;
		}
	}
	for (auto& applyNode: applyNodesLocation) {
		if (node->getId() == applyNode) {
			applyLocation();
			break;
		}
	}
}

void EnvMapEditorTabController::onFocus(GUIElementNode* node) {
}

void EnvMapEditorTabController::onUnfocus(GUIElementNode* node) {
}

void EnvMapEditorTabController::onContextMenuRequest(GUIElementNode* node, int mouseX, int mouseY) {
}

void EnvMapEditorTabController::onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) {
	int tooltipLeft, tooltipTop;
	if (view->getEditorView()->getCurrentTabTooltipPosition(screenNode, mouseX, mouseY, tooltipLeft, tooltipTop) == false) return;
	//
	popUps->getTooltipScreenController()->show(tooltipLeft, tooltipTop, node->getToolTip());
}

void EnvMapEditorTabController::onTooltipCloseRequest() {
	popUps->getTooltipScreenController()->close();
}

void EnvMapEditorTabController::onAction(GUIActionListenerType type, GUIElementNode* node)
{
}

void EnvMapEditorTabController::setOutlinerContent() {
	string xml;
	xml+= "<selectbox-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Prototype") + "\" value=\"" + GUIParser::escapeQuotes("prototype") + "\" />\n";
	view->getEditorView()->setOutlinerContent(xml);}

void EnvMapEditorTabController::setOutlinerAddDropDownContent() {
	view->getEditorView()->setOutlinerAddDropDownContent(
		string("<dropdown-option text=\"Property\" value=\"property\" />\n")
	);
}

void EnvMapEditorTabController::updateDetails(const string& outlinerNode) {
	Console::println("EnvMapEditorTabController::updateDetails(): ");

	view->getEditorView()->setDetailsContent(
		string("<template id=\"details_environmentmapping\" src=\"resources/engine/gui/template_details_environmentmapping.xml\" />\n") +
		string("<template id=\"details_location\" src=\"resources/engine/gui/template_details_location.xml\" />\n")
	);

	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_environmentmapping"))->getActiveConditions().add("open");
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_location"))->getActiveConditions().add("open");

		auto frequency = view->getEnvironmentMapFrequency();
		switch (frequency) {
			case 60LL * 60LL * 24LL * 1000LL:
				required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendersettings_frequency_details"))->getActiveConditions().removeAll();
				required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendersettings_frequency"))->getController()->setValue(MutableString(1));
				break;
			case 0LL:
				required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendersettings_frequency_details"))->getActiveConditions().removeAll();
				required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendersettings_frequency"))->getController()->setValue(MutableString(2));
				break;
			default:
				required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendersettings_frequency"))->getController()->setValue(MutableString(3));
				required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendersettings_frequency_details"))->getActiveConditions().set("custom");
				required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendersettings_frequency_value"))->getController()->setValue(MutableString(static_cast<int32_t>(frequency)));
		}

		auto renderPassMask = view->getEnvironmentMapRenderPassMask();
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendersettings_renderpass_standard"))->getController()->setValue(MutableString((renderPassMask & Entity::RENDERPASS_STANDARD) == Entity::RENDERPASS_STANDARD?"1":""));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendersettings_renderpass_sky"))->getController()->setValue(MutableString((renderPassMask & Entity::RENDERPASS_SKY) == Entity::RENDERPASS_SKY?"1":""));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendersettings_renderpass_terrain"))->getController()->setValue(MutableString((renderPassMask & Entity::RENDERPASS_TERRAIN) == Entity::RENDERPASS_TERRAIN?"1":""));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendersettings_renderpass_water"))->getController()->setValue(MutableString((renderPassMask & Entity::RENDERPASS_WATER) == Entity::RENDERPASS_WATER?"1":""));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendersettings_renderpass_postprocessing"))->getController()->setValue(MutableString((renderPassMask & Entity::RENDERPASS_POST_POSTPROCESSING) == Entity::RENDERPASS_POST_POSTPROCESSING?"1":""));

		auto environmentMapTranslation = view->getEnvironmentMapTranslation();
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("location_translation_x"))->getController()->setValue(MutableString(environmentMapTranslation.getX()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("location_translation_y"))->getController()->setValue(MutableString(environmentMapTranslation.getY()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("location_translation_z"))->getController()->setValue(MutableString(environmentMapTranslation.getZ()));
	} catch (Exception& exception) {
		Console::println(string("EnvMapEditorTabController::updateDetails(): An error occurred: ") + exception.what());;
		showInfoPopUp("Warning", (string(exception.what())));
	}
}

void EnvMapEditorTabController::applyRenderPasses() {
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;

	//
	try {
		//
		int64_t frequency = -1LL;
		switch (Integer::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendersettings_frequency"))->getController()->getValue().getString())) {
			case 1:
				frequency = 60LL * 60LL * 24LL * 1000LL;
				break;
			case 2:
				frequency = 0LL;
				break;
			case 3:
				frequency = Integer::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendersettings_frequency_value"))->getController()->getValue().getString());
				break;
		}
		view->setEnvironmentMapFrequency(frequency);
		prototype->setEnvironmentMapTimeRenderUpdateFrequency(frequency);

		//
		int32_t renderPassMask = 0;
		renderPassMask+= required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendersettings_renderpass_standard"))->getController()->getValue().equals("1") == true?Entity::RENDERPASS_STANDARD:0;
		renderPassMask+= required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendersettings_renderpass_sky"))->getController()->getValue().equals("1") == true?Entity::RENDERPASS_SKY:0;
		renderPassMask+= required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendersettings_renderpass_terrain"))->getController()->getValue().equals("1") == true?Entity::RENDERPASS_TERRAIN:0;
		renderPassMask+= required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendersettings_renderpass_water"))->getController()->getValue().equals("1") == true?Entity::RENDERPASS_WATER:0;
		renderPassMask+= required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("rendersettings_renderpass_postprocessing"))->getController()->getValue().equals("1") == true?Entity::RENDERPASS_POST_POSTPROCESSING:0;
		view->setEnvironmentMapRenderPassMask(renderPassMask);
		prototype->setEnvironmentMapRenderPassMask(renderPassMask);
	} catch (Exception& exception) {
		Console::println(string("EnvMapEditorTabController::applyRenderPasses(): An error occurred: ") + exception.what());;
		showInfoPopUp("Warning", (string(exception.what())));
	}
}

void EnvMapEditorTabController::applyLocation() {
	try {
		Vector3 environmentMapTranslation(
			Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("location_translation_x"))->getController()->getValue().getString()),
			Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("location_translation_y"))->getController()->getValue().getString()),
			Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("location_translation_z"))->getController()->getValue().getString())
		);
		view->setEnvironmentMapTranslation(environmentMapTranslation);
	} catch (Exception& exception) {
		Console::println(string("EnvMapEditorTabController::applyLocation(): An error occurred: ") + exception.what());;
		showInfoPopUp("Warning", (string(exception.what())));
	}
}

void EnvMapEditorTabController::updateInfoText(const MutableString& text) {
	required_dynamic_cast<GUITextNode*>(screenNode->getNodeById(view->getTabId() + "_tab_text_info"))->setText(text);
}
