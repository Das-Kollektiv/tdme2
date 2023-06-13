#include <tdme/tools/editor/tabcontrollers/TriggerEditorTabController.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/controllers/TooltipScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/BasePropertiesSubController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeDisplaySubController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypePhysicsSubController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeScriptSubController.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabviews/subviews/PrototypePhysicsSubView.h>
#include <tdme/tools/editor/tabviews/TriggerEditorTabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>
#include <tdme/utilities/MutableString.h>

using std::string;

using tdme::tools::editor::tabcontrollers::TriggerEditorTabController;

using tdme::engine::prototype::Prototype;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::GUIParser;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::controllers::TooltipScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::subcontrollers::BasePropertiesSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeDisplaySubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeScriptSubController;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::subviews::PrototypePhysicsSubView;
using tdme::tools::editor::tabviews::TriggerEditorTabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;
using tdme::utilities::MutableString;

TriggerEditorTabController::TriggerEditorTabController(TriggerEditorTabView* view)
{
	this->view = view;
	this->popUps = view->getPopUps();
	this->basePropertiesSubController = new BasePropertiesSubController(view->getEditorView(), "prototype");
	this->prototypePhysicsSubController = new PrototypePhysicsSubController(view->getEditorView(), view, false);
	this->prototypeDisplaySubController = new PrototypeDisplaySubController(view->getEditorView(), view, this->prototypePhysicsSubController->getView());
	this->prototypeScriptSubController = new PrototypeScriptSubController(view->getEditorView());
}

TriggerEditorTabController::~TriggerEditorTabController() {
	delete prototypeScriptSubController;
	delete prototypeDisplaySubController;
	delete prototypePhysicsSubController;
	delete basePropertiesSubController;
}

TriggerEditorTabView* TriggerEditorTabController::getView() {
	return view;
}

GUIScreenNode* TriggerEditorTabController::getScreenNode()
{
	return screenNode;
}

void TriggerEditorTabController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
	basePropertiesSubController->initialize(screenNode);
	prototypeDisplaySubController->initialize(screenNode);
	prototypePhysicsSubController->initialize(screenNode);
	prototypeScriptSubController->initialize(screenNode);
}

void TriggerEditorTabController::dispose()
{
}

void TriggerEditorTabController::onCommand(TabControllerCommand command)
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
				class OnTriggerSave: public virtual Action
				{
				public:
					void performAction() override {
						try {
							triggerEditorTabController->view->saveFile(
								triggerEditorTabController->popUps->getFileDialogScreenController()->getPathName(),
								triggerEditorTabController->popUps->getFileDialogScreenController()->getFileName()
							);
						} catch (Exception& exception) {
							triggerEditorTabController->showInfoPopUp("Warning", string(exception.what()));
						}
						triggerEditorTabController->popUps->getFileDialogScreenController()->close();
					}
					OnTriggerSave(TriggerEditorTabController* triggerEditorTabController): triggerEditorTabController(triggerEditorTabController) {
					}
				private:
					TriggerEditorTabController* triggerEditorTabController;
				};

				auto fileName = view->getPrototype() != nullptr?view->getPrototype()->getFileName():"";
				vector<string> extensions = {
					"ttrigger"
				};
				popUps->getFileDialogScreenController()->show(
					fileName.empty() == false?Tools::getPathName(fileName):string(),
					"Save to: ",
					extensions,
					Tools::getFileName(fileName),
					false,
					new OnTriggerSave(this)
				);
			}
			break;
		default:
			showInfoPopUp("Warning", "This command is not supported yet");
			break;
	}
}

void TriggerEditorTabController::onDrop(const string& payload, int mouseX, int mouseY) {
	if (prototypePhysicsSubController->onDrop(payload, mouseX, mouseY, view->getPrototype()) == true) return;
	if (prototypeScriptSubController->onDrop(payload, mouseX, mouseY, view->getPrototype()) == true) return;
	showInfoPopUp("Warning", "You can not drop a file here");
}

void TriggerEditorTabController::onChange(GUIElementNode* node)
{
	if (basePropertiesSubController->onChange(node, view->getPrototype(), view->getPrototype()) == true) return;
	if (prototypeDisplaySubController->onChange(node, view->getPrototype()) == true) return;
	if (prototypePhysicsSubController->onChange(node, view->getPrototype()) == true) return;
	if (prototypeScriptSubController->onChange(node, view->getPrototype()) == true) return;
	//
	if (node->getId() == "selectbox_outliner") {
		auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
		updateDetails(outlinerNode);
	}
}

void TriggerEditorTabController::onFocus(GUIElementNode* node) {
	if (basePropertiesSubController->onFocus(node, view->getPrototype()) == true) return;
}

void TriggerEditorTabController::onUnfocus(GUIElementNode* node) {
	if (basePropertiesSubController->onUnfocus(node, view->getPrototype()) == true) return;
}

void TriggerEditorTabController::onContextMenuRequest(GUIElementNode* node, int mouseX, int mouseY) {
	basePropertiesSubController->onContextMenuRequest(node, mouseX, mouseY, view->getPrototype());
	prototypePhysicsSubController->onContextMenuRequest(node, mouseX, mouseY, view->getPrototype());
}

void TriggerEditorTabController::onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) {
	int tooltipLeft, tooltipTop;
	if (view->getEditorView()->getCurrentTabTooltipPosition(screenNode, mouseX, mouseY, tooltipLeft, tooltipTop) == false) return;
	//
	popUps->getTooltipScreenController()->show(tooltipLeft, tooltipTop, node->getToolTip());
}

void TriggerEditorTabController::onTooltipCloseRequest() {
	popUps->getTooltipScreenController()->close();
}

void TriggerEditorTabController::onAction(GUIActionListenerType type, GUIElementNode* node)
{
	if (basePropertiesSubController->onAction(type, node, view->getPrototype()) == true) return;
	if (prototypePhysicsSubController->onAction(type, node, view->getPrototype()) == true) return;
	if (prototypeScriptSubController->onAction(type, node, view->getPrototype()) == true) return;
}

void TriggerEditorTabController::setOutlinerContent() {
	string xml;
	xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Prototype") + "\" value=\"" + GUIParser::escapeQuotes("prototype") + "\">\n";
	auto prototype = view->getPrototype();
	if (prototype != nullptr) {
		basePropertiesSubController->createBasePropertiesXML(prototype, xml);
		prototypeScriptSubController->createScriptXML(prototype, xml);
		prototypePhysicsSubController->createOutlinerPhysicsXML(prototype, xml);
	}
	xml+= "</selectbox-parent-option>\n";
	view->getEditorView()->setOutlinerContent(xml);}

void TriggerEditorTabController::setOutlinerAddDropDownContent() {
	view->getEditorView()->setOutlinerAddDropDownContent(
		string("<dropdown-option text=\"Property\" value=\"property\" />\n") +
		string("<dropdown-option text=\"BV\" value=\"boundingvolume\" />\n")
	);
}

void TriggerEditorTabController::updateDetails(const string& outlinerNode) {
	view->getEditorView()->setDetailsContent(string());
	basePropertiesSubController->updateDetails(view->getPrototype(), outlinerNode);
	prototypeDisplaySubController->updateDetails(view->getPrototype(), outlinerNode);
	prototypePhysicsSubController->updateDetails(view->getPrototype(), outlinerNode);
	prototypePhysicsSubController->getView()->setDisplayBoundingVolume(true);
	prototypeScriptSubController->updateDetails(view->getPrototype(), outlinerNode);
}

void TriggerEditorTabController::updateInfoText(const MutableString& text) {
	required_dynamic_cast<GUITextNode*>(screenNode->getNodeById(view->getTabId() + "_tab_text_info"))->setText(text);
}

void TriggerEditorTabController::showInfoPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}
