#include <tdme/tools/editor/tabcontrollers/ParticleSystemEditorTabController.h>

#include <string>

#include <tdme/gui/GUI.h>
#include <tdme/utilities/Action.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/BasePropertiesSubController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypePhysicsSubController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeSoundsSubController.h>
#include <tdme/tools/editor/tabviews/ParticleSystemEditorTabView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>

using std::string;

using tdme::tools::editor::tabcontrollers::ParticleSystemEditorTabController;

using tdme::utilities::Action;
using tdme::gui::GUIParser;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabcontrollers::subcontrollers::BasePropertiesSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeSoundsSubController;
using tdme::tools::editor::tabviews::ParticleSystemEditorTabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;

ParticleSystemEditorTabController::ParticleSystemEditorTabController(ParticleSystemEditorTabView* view)
{
	this->view = view;
	this->popUps = view->getPopUps();
	this->basePropertiesSubController = new BasePropertiesSubController(view->getEditorView(), "prototype");
	this->prototypePhysicsSubController = new PrototypePhysicsSubController(view->getEditorView(), view, &modelPath, false);
	this->prototypeSoundsSubController = new PrototypeSoundsSubController(view->getEditorView(), view, &audioPath);
}

ParticleSystemEditorTabController::~ParticleSystemEditorTabController() {
	delete basePropertiesSubController;
	delete prototypePhysicsSubController;
	delete prototypeSoundsSubController;
}

ParticleSystemEditorTabView* ParticleSystemEditorTabController::getView() {
	return view;
}

GUIScreenNode* ParticleSystemEditorTabController::getScreenNode()
{
	return screenNode;
}

void ParticleSystemEditorTabController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
	basePropertiesSubController->initialize(screenNode);
	prototypePhysicsSubController->initialize(screenNode);
	prototypeSoundsSubController->initialize(screenNode);
	setOutlinerContent();
}

void ParticleSystemEditorTabController::dispose()
{
}

void ParticleSystemEditorTabController::save()
{
}

void ParticleSystemEditorTabController::saveAs()
{
}

void ParticleSystemEditorTabController::showErrorPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}

void ParticleSystemEditorTabController::onValueChanged(GUIElementNode* node)
{
	if (node->getId() == "selectbox_outliner") {
		auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
		updateDetails(outlinerNode);
	}
	basePropertiesSubController->onValueChanged(node, view->getPrototype());
	prototypePhysicsSubController->onValueChanged(node, view->getPrototype());
	prototypeSoundsSubController->onValueChanged(node, view->getPrototype(), nullptr);
}

void ParticleSystemEditorTabController::onFocus(GUIElementNode* node) {
	basePropertiesSubController->onFocus(node, view->getPrototype());
	prototypeSoundsSubController->onFocus(node, view->getPrototype());
}

void ParticleSystemEditorTabController::onUnfocus(GUIElementNode* node) {
	basePropertiesSubController->onUnfocus(node, view->getPrototype());
	prototypeSoundsSubController->onUnfocus(node, view->getPrototype());
}

void ParticleSystemEditorTabController::onContextMenuRequested(GUIElementNode* node, int mouseX, int mouseY) {
	basePropertiesSubController->onContextMenuRequested(node, mouseX, mouseY, view->getPrototype());
	prototypePhysicsSubController->onContextMenuRequested(node, mouseX, mouseY, view->getPrototype());
	prototypeSoundsSubController->onContextMenuRequested(node, mouseX, mouseY, view->getPrototype());
}

void ParticleSystemEditorTabController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
	auto prototype = view->getPrototype();
	basePropertiesSubController->onActionPerformed(type, node, prototype);
	prototypePhysicsSubController->onActionPerformed(type, node, prototype);
	prototypeSoundsSubController->onActionPerformed(type, node, prototype);
}

void ParticleSystemEditorTabController::setOutlinerContent() {
	string xml;
	xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Prototype") + "\" value=\"" + GUIParser::escapeQuotes("prototype") + "\">\n";
	auto prototype = view->getPrototype();
	if (prototype != nullptr) {
		basePropertiesSubController->createBasePropertiesXML(prototype, xml);
		prototypePhysicsSubController->createOutlinerPhysicsXML(prototype, xml);
		prototypeSoundsSubController->createOutlinerSoundsXML(prototype, xml);
		//
		xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Particle Systems") + "\" value=\"" + GUIParser::escapeQuotes("particlesystems") + "\">\n";
		for (auto i = 0; i < prototype->getParticleSystemsCount(); i++) {
			auto particleSystem = prototype->getParticleSystemAt(i);
			xml+= "	<selectbox-option image=\"resources/engine/images/particle.png\" text=\"" + GUIParser::escapeQuotes("Particle System " + to_string(i)) + "\" id=\"" + GUIParser::escapeQuotes("particlesystems." + to_string(i)) + "\" value=\"" + GUIParser::escapeQuotes("particlesystems." + to_string(i)) + "\" />\n";
		}
		xml+= "</selectbox-parent-option>\n";
	}
	xml+= "</selectbox-parent-option>\n";
	view->getEditorView()->setOutlinerContent(xml);
}

void ParticleSystemEditorTabController::updateDetails(const string& outlinerNode) {
	prototypePhysicsSubController->updateDetails(view->getPrototype(), outlinerNode);
	prototypeSoundsSubController->updateDetails(view->getPrototype(), nullptr, outlinerNode);
}
