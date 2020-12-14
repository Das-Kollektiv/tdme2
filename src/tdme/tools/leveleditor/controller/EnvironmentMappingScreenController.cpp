#include <tdme/tools/leveleditor/controller/EnvironmentMappingScreenController.h>

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
#include <tdme/tools/leveleditor/controller/LevelEditorEntityLibraryScreenController.h>
#include <tdme/tools/leveleditor/views/EnvironmentMappingView.h>
#include <tdme/tools/shared/controller/EntityBaseSubScreenController.h>
#include <tdme/tools/shared/controller/EntityPhysicsSubScreenController.h>
#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/tools/shared/views/EntityPhysicsView.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/leveleditor/TDMELevelEditor.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using std::string;
using std::to_string;

using tdme::tools::leveleditor::controller::EnvironmentMappingScreenController;
using tdme::gui::GUIParser;
using tdme::gui::events::Action;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::tools::leveleditor::controller::LevelEditorEntityLibraryScreenController;
using tdme::tools::leveleditor::views::EnvironmentMappingView;
using tdme::tools::shared::controller::EntityBaseSubScreenController;
using tdme::tools::shared::controller::EntityPhysicsSubScreenController;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::tools::Tools;
using tdme::tools::shared::views::EntityPhysicsView;
using tdme::tools::shared::views::PopUps;
using tdme::tools::leveleditor::TDMELevelEditor;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Float;
using tdme::utilities::Integer;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

MutableString EnvironmentMappingScreenController::TEXT_EMPTY = MutableString("");

EnvironmentMappingScreenController::EnvironmentMappingScreenController(EnvironmentMappingView* view)
{
	class OnSetEntityDataAction: public virtual Action
	{
	public:
		void performAction() override {
			finalView->updateGUIElements();
			TDMELevelEditor::getInstance()->getLevelEditorEntityLibraryScreenController()->setEntityLibrary();
		}

		/**
		 * Public constructor
		 * @param EnvironmentMappingScreenController environment mapping screen controller
		 * @param finalView final view
		 */
		OnSetEntityDataAction(EnvironmentMappingScreenController* environmentMappingScreenController, EnvironmentMappingView* finalView): environmentMappingScreenController(environmentMappingScreenController), finalView(finalView) {
		}


	private:
		EnvironmentMappingScreenController* environmentMappingScreenController;
		EnvironmentMappingView* finalView;

	};

	this->view = view;
	auto const finalView = view;
	this->modelPath = new FileDialogPath(".");
	this->entityBaseSubScreenController = new EntityBaseSubScreenController(view->getPopUpsViews(), new OnSetEntityDataAction(this, finalView));
	this->entityPhysicsSubScreenController = new EntityPhysicsSubScreenController(view->getPopUpsViews(), modelPath, false, 1, EntityPhysicsSubScreenController::BOUNDINGVOLUMETYPE_BOUNDINGBOX);
}

EntityPhysicsSubScreenController* EnvironmentMappingScreenController::getEntityPhysicsSubScreenController()
{
	return entityPhysicsSubScreenController;
}

GUIScreenNode* EnvironmentMappingScreenController::getScreenNode()
{
	return screenNode;
}

void EnvironmentMappingScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse("resources/engine/tools/leveleditor/gui", "screen_environmentmapping.xml");
		screenNode->addActionListener(this);
		screenNode->addChangeListener(this);
		screenCaption = dynamic_cast<GUITextNode*>(screenNode->getNodeById("screen_caption"));
		viewPort = dynamic_cast<GUIElementNode*>(screenNode->getNodeById("viewport"));
		generationRenderPasses = dynamic_cast<GUIElementNode*>(screenNode->getNodeById("generation_renderpass"));
		generationFrequency = dynamic_cast<GUIElementNode*>(screenNode->getNodeById("generation_frequency"));
		generationApply = dynamic_cast<GUIElementNode*>(screenNode->getNodeById("button_generation_apply"));
	} catch (Exception& exception) {
		Console::print(string("EnvironmentMappingScreenController::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	entityBaseSubScreenController->initialize(screenNode);
	entityPhysicsSubScreenController->initialize(screenNode);
}

void EnvironmentMappingScreenController::dispose()
{
}

void EnvironmentMappingScreenController::setScreenCaption(const string& text)
{
	screenCaption->setText(text);
}

void EnvironmentMappingScreenController::setEntityData(const string& name, const string& description)
{
	entityBaseSubScreenController->setEntityData(name, description);
}

void EnvironmentMappingScreenController::unsetEntityData()
{
	entityBaseSubScreenController->unsetEntityData();
}

void EnvironmentMappingScreenController::setEntityProperties(const string& presetId, const string& selectedName)
{
	entityBaseSubScreenController->setEntityProperties(view->getEntity(), presetId, selectedName);
}

void EnvironmentMappingScreenController::unsetEntityProperties()
{
	entityBaseSubScreenController->unsetEntityProperties();
}

void EnvironmentMappingScreenController::setGeneration() {
	int renderPassMask = view->getEntity()->getEnvironmentMapRenderPassMask();
	int64_t frequency = view->getEntity()->getEnvironmentMapTimeRenderUpdateFrequency();
	string renderPassMaskString;
	auto renderPass = 1;
	for (auto i = 0; i < 31; i++) {
		if ((renderPassMask & renderPass) == renderPass) {
			renderPassMaskString+= (renderPassMaskString.empty() == true?"|":"") + to_string(renderPass) + "|";
		}
		renderPass = renderPass << 1;
	}
	generationRenderPasses->getController()->setDisabled(false);
	generationRenderPasses->getController()->setValue(renderPassMaskString);
	generationFrequency->getController()->setDisabled(false);
	generationFrequency->getController()->setValue(frequency == -1LL?"":to_string(frequency));
	generationApply->getController()->setDisabled(false);
}

void EnvironmentMappingScreenController::unsetGeneration() {
	generationRenderPasses->getController()->setDisabled(true);
	generationRenderPasses->getController()->setValue(TEXT_EMPTY);
	generationFrequency->getController()->setDisabled(true);
	generationFrequency->getController()->setValue(TEXT_EMPTY);
	generationApply->getController()->setDisabled(true);
}

void EnvironmentMappingScreenController::onGenerationApply() {
	try {
		int renderPassMask = 0;
		for (auto renderPass: StringTools::tokenize(generationRenderPasses->getController()->getValue().getString(), "|")) renderPassMask|= Integer::parseInt(renderPass);
		auto frequencyString = generationFrequency->getController()->getValue().getString();
		auto frequency = frequencyString.empty() == true?-1LL:Integer::parseInt(frequencyString);
		view->getEntity()->setEnvironmentMapTimeRenderUpdateFrequency(frequency);
		view->getEntity()->setEnvironmentMapRenderPassMask(renderPassMask);
	} catch (Exception& exception) {
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void EnvironmentMappingScreenController::onQuit()
{
	TDMELevelEditor::getInstance()->quit();
}

void EnvironmentMappingScreenController::showErrorPopUp(const string& caption, const string& message)
{
	view->getPopUpsViews()->getInfoDialogScreenController()->show(caption, message);
}

void EnvironmentMappingScreenController::onValueChanged(GUIElementNode* node)
{
	entityBaseSubScreenController->onValueChanged(node, view->getEntity());
	entityPhysicsSubScreenController->onValueChanged(node, view->getEntity());
}

void EnvironmentMappingScreenController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
	entityBaseSubScreenController->onActionPerformed(type, node, view->getEntity());
	entityPhysicsSubScreenController->onActionPerformed(type, node, view->getEntity());
	if (type == GUIActionListenerType::PERFORMED) {
		if (node->getId().compare("button_generation_apply") == 0) {
			onGenerationApply();
		}
	}
	entityPhysicsSubScreenController->getView()->setDisplayBoundingVolumeIdx(0);
}

void EnvironmentMappingScreenController::getViewPort(int& left, int& top, int& width, int& height) {
	auto& constraints = viewPort->getComputedConstraints();
	left = constraints.left + constraints.alignmentLeft + constraints.contentAlignmentLeft;
	top = constraints.top + constraints.alignmentTop + constraints.contentAlignmentTop;
	width = constraints.width;
	height = constraints.height;
}
