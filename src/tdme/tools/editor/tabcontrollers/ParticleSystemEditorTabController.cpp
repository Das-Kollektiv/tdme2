#include <tdme/tools/editor/tabcontrollers/ParticleSystemEditorTabController.h>

#include <string>

#include <tdme/gui/GUI.h>
#include <tdme/utilities/Action.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/tabviews/ParticleSystemEditorTabView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>

using std::string;

using tdme::tools::editor::tabcontrollers::ParticleSystemEditorTabController;

using tdme::utilities::Action;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::ParticleSystemEditorTabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;

ParticleSystemEditorTabController::ParticleSystemEditorTabController(ParticleSystemEditorTabView* view)
{
	this->view = view;
	this->popUps = view->getPopUps();
}

ParticleSystemEditorTabController::~ParticleSystemEditorTabController() {
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
}

void ParticleSystemEditorTabController::onFocus(GUIElementNode* node) {
}

void ParticleSystemEditorTabController::onUnfocus(GUIElementNode* node) {
}

void ParticleSystemEditorTabController::onContextMenuRequested(GUIElementNode* node, int mouseX, int mouseY) {
}

void ParticleSystemEditorTabController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
}
