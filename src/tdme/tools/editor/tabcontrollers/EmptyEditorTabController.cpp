#include <tdme/tools/editor/tabcontrollers/EmptyEditorTabController.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
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
#include <tdme/utilities/MutableString.h>

using std::string;

using tdme::tools::editor::tabcontrollers::EmptyEditorTabController;

using tdme::engine::prototype::Prototype;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::GUIParser;
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
using tdme::utilities::MutableString;

EmptyEditorTabController::EmptyEditorTabController(EmptyEditorTabView* view)
{
	this->view = view;
	this->popUps = view->getPopUps();
	this->basePropertiesSubController = new BasePropertiesSubController(view->getEditorView(), "prototype");
	this->prototypeScriptSubController = new PrototypeScriptSubController(view->getEditorView());
}

EmptyEditorTabController::~EmptyEditorTabController() {
	delete prototypeScriptSubController;
	delete basePropertiesSubController;
}

EmptyEditorTabView* EmptyEditorTabController::getView() {
	return view;
}

GUIScreenNode* EmptyEditorTabController::getScreenNode()
{
	return screenNode;
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

void EmptyEditorTabController::executeCommand(TabControllerCommand command)
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
					showErrorPopUp("Warning", (string(exception.what())));
				}
			}
			break;
		case COMMAND_SAVEAS:
			{
				class OnEmptySave: public virtual Action
				{
				public:
					void performAction() override {
						try {
							emptyEditorTabController->view->saveFile(
								emptyEditorTabController->popUps->getFileDialogScreenController()->getPathName(),
								emptyEditorTabController->popUps->getFileDialogScreenController()->getFileName()
							);
						} catch (Exception& exception) {
							emptyEditorTabController->showErrorPopUp("Warning", (string(exception.what())));
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
			showErrorPopUp("Warning", "This command is not supported yet");
			break;
	}
}

void EmptyEditorTabController::onChange(GUIElementNode* node)
{
	basePropertiesSubController->onChange(node, view->getPrototype());
	prototypeScriptSubController->onChange(node, view->getPrototype());
}

void EmptyEditorTabController::onFocus(GUIElementNode* node) {
	basePropertiesSubController->onFocus(node, view->getPrototype());
}

void EmptyEditorTabController::onUnfocus(GUIElementNode* node) {
	basePropertiesSubController->onUnfocus(node, view->getPrototype());
}

void EmptyEditorTabController::onContextMenuRequest(GUIElementNode* node, int mouseX, int mouseY) {
	basePropertiesSubController->onContextMenuRequest(node, mouseX, mouseY, view->getPrototype());
}

void EmptyEditorTabController::onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) {
	int left, top;
	view->getEditorView()->getViewPortUnscaledOffset(left, top);
	popUps->getTooltipScreenController()->show(left + mouseX, top + mouseY, node->getToolTip());
}

void EmptyEditorTabController::onTooltipCloseRequest() {
	popUps->getTooltipScreenController()->close();
}

void EmptyEditorTabController::onAction(GUIActionListenerType type, GUIElementNode* node)
{
	auto prototype = view->getPrototype();
	basePropertiesSubController->onAction(type, node, prototype);
	prototypeScriptSubController->onAction(type, node, prototype);
}

void EmptyEditorTabController::setOutlinerContent() {
	string xml;
	xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Prototype") + "\" value=\"" + GUIParser::escapeQuotes("prototype") + "\">\n";
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

void EmptyEditorTabController::showErrorPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}
