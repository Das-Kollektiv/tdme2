#include <tdme/tools/editor/tabcontrollers/EmptyEditorTabController.h>

#include <memory>
#include <string>

#include <agui/agui.h>
#include <agui/gui/events/GUIActionListener.h>
#include <agui/gui/events/GUIChangeListener.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/nodes/GUITextNode.h>
#include <agui/gui/GUI.h>
#include <agui/gui/GUIParser.h>
#include <agui/utilities/MutableString.h>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/controllers/TooltipScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/BasePropertiesSubController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeScriptSubController.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabviews/EmptyEditorTabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>

using std::make_unique;
using std::string;
using std::unique_ptr;

using tdme::tools::editor::tabcontrollers::EmptyEditorTabController;

using agui::gui::events::GUIActionListenerType;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::nodes::GUITextNode;
using agui::gui::GUIParser;
using agui::utilities::MutableString;

using tdme::engine::prototype::Prototype;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::controllers::TooltipScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::subcontrollers::BasePropertiesSubController;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::EmptyEditorTabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;

EmptyEditorTabController::EmptyEditorTabController(EmptyEditorTabView* view)
{
	this->view = view;
	this->popUps = view->getPopUps();
	this->basePropertiesSubController = make_unique<BasePropertiesSubController>(view->getEditorView(), "prototype");
	this->prototypeScriptSubController = make_unique<PrototypeScriptSubController>(view->getEditorView());
}

EmptyEditorTabController::~EmptyEditorTabController() {
}

void EmptyEditorTabController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
	basePropertiesSubController->initialize(screenNode);
	prototypeScriptSubController->initialize(screenNode);
}

void EmptyEditorTabController::dispose()
{
}

void EmptyEditorTabController::onCommand(TabControllerCommand command)
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
					showInfoPopUp("Warning", string(exception.what()));
				}
			}
			break;
		case COMMAND_SAVEAS:
			{
				class OnEmptySave: public Action
				{
				public:
					void performAction() override {
						try {
							emptyEditorTabController->view->saveFile(
								emptyEditorTabController->popUps->getFileDialogScreenController()->getPathName(),
								emptyEditorTabController->popUps->getFileDialogScreenController()->getFileName()
							);
						} catch (Exception& exception) {
							emptyEditorTabController->showInfoPopUp("Warning", string(exception.what()));
						}
						emptyEditorTabController->popUps->getFileDialogScreenController()->close();
					}
					OnEmptySave(EmptyEditorTabController* emptyEditorTabController): emptyEditorTabController(emptyEditorTabController) {
					}
				private:
					EmptyEditorTabController* emptyEditorTabController;
				};

				auto fileName = view->getPrototype() != nullptr?view->getPrototype()->getFileName():"";
				vector<string> extensions = {
					"tempty"
				};
				popUps->getFileDialogScreenController()->show(
					fileName.empty() == false?Tools::getPathName(fileName):string(),
					"Save to: ",
					extensions,
					Tools::getFileName(fileName),
					false,
					new OnEmptySave(this)
				);
			}
			break;
		default:
			showInfoPopUp("Warning", "This command is not supported yet");
			break;
	}
}

void EmptyEditorTabController::onDrop(const string& payload, int mouseX, int mouseY) {
	if (prototypeScriptSubController->onDrop(payload, mouseX, mouseY, view->getPrototype()) == true) return;
	showInfoPopUp("Warning", "You can not drop a file here");
}

void EmptyEditorTabController::onChange(GUIElementNode* node)
{
	if (basePropertiesSubController->onChange(node, view->getPrototype(), view->getPrototype()) == true) return;
	if (prototypeScriptSubController->onChange(node, view->getPrototype()) == true) return;
}

void EmptyEditorTabController::onFocus(GUIElementNode* node) {
	if (basePropertiesSubController->onFocus(node, view->getPrototype()) == true) return;
}

void EmptyEditorTabController::onUnfocus(GUIElementNode* node) {
	if (basePropertiesSubController->onUnfocus(node, view->getPrototype()) == true) return;
}

void EmptyEditorTabController::onContextMenuRequest(GUIElementNode* node, int mouseX, int mouseY) {
	basePropertiesSubController->onContextMenuRequest(node, mouseX, mouseY, view->getPrototype());
}

void EmptyEditorTabController::onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) {
	int tooltipLeft, tooltipTop;
	if (view->getEditorView()->getCurrentTabTooltipPosition(screenNode, mouseX, mouseY, tooltipLeft, tooltipTop) == false) return;
	//
	popUps->getTooltipScreenController()->show(tooltipLeft, tooltipTop, node->getToolTip());
}

void EmptyEditorTabController::onTooltipCloseRequest() {
	popUps->getTooltipScreenController()->close();
}

void EmptyEditorTabController::onAction(GUIActionListenerType type, GUIElementNode* node)
{
	auto prototype = view->getPrototype();
	if (basePropertiesSubController->onAction(type, node, prototype) == true) return;
	if (prototypeScriptSubController->onAction(type, node, prototype) == true) return;
}

void EmptyEditorTabController::setOutlinerContent() {
	string xml;
	xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escape("Prototype") + "\" value=\"" + GUIParser::escape("prototype") + "\">\n";
	auto prototype = view->getPrototype();
	if (prototype != nullptr) {
		basePropertiesSubController->createBasePropertiesXML(prototype, xml);
		prototypeScriptSubController->createScriptXML(prototype, xml);
	}
	xml+= "</selectbox-parent-option>\n";
	view->getEditorView()->setOutlinerContent(xml);}

void EmptyEditorTabController::setOutlinerAddDropDownContent() {
	view->getEditorView()->setOutlinerAddDropDownContent(
		string("<dropdown-option text=\"Property\" value=\"property\" />\n")
	);
}

void EmptyEditorTabController::updateDetails(const string& outlinerNode) {
	view->getEditorView()->setDetailsContent(string());
	basePropertiesSubController->updateDetails(view->getPrototype(), outlinerNode);
	prototypeScriptSubController->updateDetails(view->getPrototype(), outlinerNode);
}

void EmptyEditorTabController::updateInfoText(const MutableString& text) {
	required_dynamic_cast<GUITextNode*>(screenNode->getNodeById(view->getTabId() + "_tab_text_info"))->setText(text);
}

void EmptyEditorTabController::showInfoPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}
