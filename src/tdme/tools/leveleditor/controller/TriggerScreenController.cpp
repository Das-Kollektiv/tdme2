#include <tdme/tools/leveleditor/controller/TriggerScreenController.h>

#include <string>

#include <tdme/gui/GUIParser.h>
#include <tdme/gui/events/Action.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/tools/leveleditor/controller/SceneEditorLibraryScreenController.h>
#include <tdme/tools/leveleditor/views/TriggerView.h>
#include <tdme/tools/shared/controller/PrototypeBaseSubScreenController.h>
#include <tdme/tools/shared/controller/PrototypePhysicsSubScreenController.h>
#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/leveleditor/TDMELevelEditor.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::string;

using tdme::tools::leveleditor::controller::TriggerScreenController;
using tdme::gui::GUIParser;
using tdme::gui::events::Action;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::tools::leveleditor::controller::SceneEditorLibraryScreenController;
using tdme::tools::leveleditor::views::TriggerView;
using tdme::tools::shared::controller::PrototypeBaseSubScreenController;
using tdme::tools::shared::controller::PrototypePhysicsSubScreenController;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::tools::Tools;
using tdme::tools::shared::views::PopUps;
using tdme::tools::leveleditor::TDMELevelEditor;
using tdme::utilities::Float;
using tdme::utilities::MutableString;
using tdme::utilities::Console;
using tdme::utilities::Exception;

MutableString TriggerScreenController::TEXT_EMPTY = MutableString("");

TriggerScreenController::TriggerScreenController(TriggerView* view)
{
	class OnSetEntityDataAction: public virtual Action
	{
	public:
		void performAction() override {
			finalView->updateGUIElements();
			TDMELevelEditor::getInstance()->getSceneEditorLibraryScreenController()->setPrototypeLibrary();
		}

		/**
		 * Public constructor
		 * @param triggerScreenController trigger screen controller
		 * @param finalView final view
		 */
		OnSetEntityDataAction(TriggerScreenController* triggerScreenController, TriggerView* finalView): triggerScreenController(triggerScreenController), finalView(finalView) {
		}


	private:
		TriggerScreenController* triggerScreenController;
		TriggerView* finalView;

	};

	this->view = view;
	auto const finalView = view;
	this->modelPath = new FileDialogPath(".");
	this->prototypeBaseSubScreenController = new PrototypeBaseSubScreenController(view->getPopUpsViews(), new OnSetEntityDataAction(this, finalView));
	this->prototypePhysicsSubScreenController = new PrototypePhysicsSubScreenController(view->getPopUpsViews(), modelPath, false);
}

PrototypePhysicsSubScreenController* TriggerScreenController::getPrototypePhysicsSubScreenController()
{
	return prototypePhysicsSubScreenController;
}

GUIScreenNode* TriggerScreenController::getScreenNode()
{
	return screenNode;
}

void TriggerScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse("resources/engine/tools/leveleditor/gui", "screen_trigger.xml");
		screenNode->addActionListener(this);
		screenNode->addChangeListener(this);
		screenCaption = dynamic_cast< GUITextNode* >(screenNode->getNodeById("screen_caption"));
		viewPort = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("viewport"));
	} catch (Exception& exception) {
		Console::print(string("TriggerScreenController::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	prototypeBaseSubScreenController->initialize(screenNode);
	prototypePhysicsSubScreenController->initialize(screenNode);
}

void TriggerScreenController::dispose()
{
}

void TriggerScreenController::setScreenCaption(const string& text)
{
	screenCaption->setText(text);
}

void TriggerScreenController::setPrototypeData(const string& name, const string& description)
{
	prototypeBaseSubScreenController->setPrototypeData(name, description);
}

void TriggerScreenController::unsetPrototypeData()
{
	prototypeBaseSubScreenController->unsetPrototypeData();
}

void TriggerScreenController::setPrototypeProperties(const string& presetId, const string& selectedName)
{
	prototypeBaseSubScreenController->setPrototypeProperties(view->getPrototype(), presetId, selectedName);
}

void TriggerScreenController::unsetPrototypeProperties()
{
	prototypeBaseSubScreenController->unsetPrototypeProperties();
}

void TriggerScreenController::onQuit()
{
	TDMELevelEditor::getInstance()->quit();
}

void TriggerScreenController::showErrorPopUp(const string& caption, const string& message)
{
	view->getPopUpsViews()->getInfoDialogScreenController()->show(caption, message);
}

void TriggerScreenController::onValueChanged(GUIElementNode* node)
{
	prototypeBaseSubScreenController->onValueChanged(node, view->getPrototype());
	prototypePhysicsSubScreenController->onValueChanged(node, view->getPrototype());
}

void TriggerScreenController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
	prototypeBaseSubScreenController->onActionPerformed(type, node, view->getPrototype());
	prototypePhysicsSubScreenController->onActionPerformed(type, node, view->getPrototype());
}

void TriggerScreenController::getViewPort(int& left, int& top, int& width, int& height) {
	auto& constraints = viewPort->getComputedConstraints();
	left = constraints.left + constraints.alignmentLeft + constraints.contentAlignmentLeft;
	top = constraints.top + constraints.alignmentTop + constraints.contentAlignmentTop;
	width = constraints.width;
	height = constraints.height;
}
