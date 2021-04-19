#include <tdme/tools/editor/views/EditorView.h>

#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/PartitionNone.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/editor/controller/EditorScreenController.h>
#include <tdme/tools/editor/TDMEEditor.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::string;

using tdme::engine::Engine;
using tdme::engine::PartitionNone;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUI;
using tdme::math::Vector3;
using tdme::tools::editor::controller::EditorScreenController;
using tdme::tools::editor::views::EditorView;
using tdme::tools::editor::TDMEEditor;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::tools::Tools;
using tdme::tools::shared::views::CameraRotationInputHandler;
using tdme::tools::shared::views::PopUps;
using tdme::utilities::Console;
using tdme::utilities::Exception;

EditorView::EditorView(PopUps* popUps)
{
	this->popUps = popUps;
	editorScreenController = nullptr;
	engine = Engine::getInstance();
}

EditorView::~EditorView() {
	delete editorScreenController;
}

PopUps* EditorView::getPopUps()
{
	return popUps;
}

void EditorView::handleInputEvents()
{
	// no op
}

void EditorView::display()
{
}

void EditorView::updateGUIElements()
{
}

void EditorView::initialize()
{
	try {
		editorScreenController = new EditorScreenController(this);
		editorScreenController->initialize();
		engine->getGUI()->addScreen(editorScreenController->getScreenNode()->getId(), editorScreenController->getScreenNode());
		editorScreenController->getScreenNode()->setInputEventHandler(this);
	} catch (Exception& exception) {
		Console::print(string("EditorView::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	updateGUIElements();
}

void EditorView::activate()
{
	engine->reset();
	engine->setPartition(new PartitionNone());
	engine->setShadowMapLightEyeDistanceScale(0.1f);
	engine->getGUI()->resetRenderScreens();
	engine->getGUI()->addRenderScreen(editorScreenController->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(popUps->getFileDialogScreenController()->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(popUps->getInfoDialogScreenController()->getScreenNode()->getId());
}

void EditorView::deactivate()
{
}

void EditorView::dispose()
{
	Engine::getInstance()->reset();
}
