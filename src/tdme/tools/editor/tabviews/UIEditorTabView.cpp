#include <tdme/tools/editor/tabviews/UIEditorTabView.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/SimplePartition.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/misc/CameraRotationInputHandler.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/UIEditorTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::string;

using tdme::tools::editor::tabviews::UIEditorTabView;

using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::prototype::Prototype;
using tdme::engine::Engine;
using tdme::engine::Object3D;
using tdme::engine::SimplePartition;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUI;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::misc::CameraInputHandler;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::UIEditorTabController;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;

UIEditorTabView::UIEditorTabView(EditorView* editorView, const string& tabId, GUIScreenNode* screenNode)
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->popUps = editorView->getPopUps();
	screenNodes.push_back(screenNode);
	guiEngine = Engine::createOffScreenInstance(1920, 1080, false, false, false);
	guiEngine->setSceneColor(Color4(125.0f / 255.0f, 125.0f / 255.0f, 125.0f / 255.0f, 1.0f));
	outlinerState.expandedOutlinerParentOptionValues.push_back("0.0");
	reAddScreens();
}

UIEditorTabView::~UIEditorTabView() {
	delete uiTabController;
	delete guiEngine;
	if (projectedUi == true) {
		delete cameraRotationInputHandler;
		delete engine;
	}
}

void UIEditorTabView::onCameraRotation() {
	// no op
}

void UIEditorTabView::onCameraScale() {
	// no op
}

void UIEditorTabView::handleInputEvents()
{
	if (projectedUi == true) {
		cameraRotationInputHandler->handleInputEvents();
		//engine->getGUI()->handleEvents();
	} else {
		guiEngine->getGUI()->handleEvents();
	}
}

void UIEditorTabView::display()
{
	guiEngine->display();
	guiEngine->getGUI()->render();
	if (projectedUi == true) engine->display();
}

void UIEditorTabView::initialize()
{
	try {
		uiTabController = new UIEditorTabController(this);
		uiTabController->initialize(editorView->getScreenController()->getScreenNode());
	} catch (Exception& exception) {
		Console::print(string("UIEditorTabView::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	// TODO: load settings
}

void UIEditorTabView::dispose()
{
	guiEngine->dispose();
	if (projectedUi == true) {
		engine->dispose();
	}
}

void UIEditorTabView::updateRendering() {
}

inline bool UIEditorTabView::hasFixedSize() {
	return projectedUi == false;
}

Engine* UIEditorTabView::getEngine() {
	return projectedUi == true?engine:guiEngine;
}

void UIEditorTabView::activate() {
	uiTabController->setOutlinerAddDropDownContent();
	uiTabController->setOutlinerContent();
	editorView->getScreenController()->restoreOutlinerState(outlinerState);
	editorView->getScreenController()->setDetailsContent(string());
}

void UIEditorTabView::deactivate() {
	editorView->getScreenController()->storeOutlinerState(outlinerState);
}

void UIEditorTabView::reloadOutliner() {
	uiTabController->setOutlinerContent();
	editorView->getScreenController()->setDetailsContent(string());
}

void UIEditorTabView::addScreen() {
	screenNodes.push_back(nullptr);
}

void UIEditorTabView::unsetScreen(int screenIdx) {
	if (screenIdx < 0 || screenIdx >= screenNodes.size()) return;
	auto screenNode = screenNodes[screenIdx];
	if (screenNode != nullptr) {
		guiEngine->getGUI()->removeScreen(screenNode->getId());
		screenNodes[screenIdx] = nullptr;
	}
}

void UIEditorTabView::removeScreen(int screenIdx) {
	if (screenIdx < 0 || screenIdx >= screenNodes.size()) return;
	auto screenNode = screenNodes[screenIdx];
	if (screenNode != nullptr) {
		guiEngine->getGUI()->removeScreen(screenNode->getId());
		screenNodes.erase(screenNodes.begin() + screenIdx);
	}
}

void UIEditorTabView::reAddScreens() {
	guiEngine->getGUI()->resetRenderScreens();
	for (auto screenNode: screenNodes) {
		if (screenNode == nullptr) continue;
		screenNode->getSizeConstraints().minWidth = -1;
		screenNode->getSizeConstraints().minHeight = -1;
		screenNode->getSizeConstraints().maxWidth = -1;
		screenNode->getSizeConstraints().maxHeight = -1;
		guiEngine->getGUI()->addScreen(screenNode->getId(), screenNode);
		guiEngine->getGUI()->addRenderScreen(screenNode->getId());
	}
}

Prototype* UIEditorTabView::getPrototype() {
	return prototype;
}

Prototype* UIEditorTabView::loadPrototype(const string& pathName, const string& fileName, const string& modelMeshNode, const string& modelMeshAnimation) {
	//
	if (projectedUi == true) engine->reset();
	if (prototype != nullptr) delete prototype;
	prototype = nullptr;

	//
	try {
		prototype = PrototypeReader::read(pathName, fileName);
	} catch (Exception& exception) {
		Console::print(string("UIEditorTabView::loadPrototype(): An error occurred: "));
		Console::println(string(exception.what()));
	}

	//
	auto projectedUiLast = projectedUi;
	if (projectedUi == false) {
		engine = Engine::createOffScreenInstance(512, 512, true, true, false);
		engine->setPartition(new SimplePartition());
		engine->setShadowMapLightEyeDistanceScale(0.1f);
		engine->setSceneColor(Color4(125.0f / 255.0f, 125.0f / 255.0f, 125.0f / 255.0f, 1.0f));
		cameraRotationInputHandler = new CameraRotationInputHandler(engine, this);
		projectedUi = true;
	}
	Vector3 objectScale;
	Tools::setupPrototype(prototype, engine, cameraRotationInputHandler->getLookFromRotations(), 1, objectScale, cameraRotationInputHandler, 1.5f, projectedUiLast == true);

	//
	auto modelEntity = dynamic_cast<Object3D*>(engine->getEntity("model"));
	if (modelEntity != nullptr) {
		modelEntity->bindDiffuseTexture(guiEngine->getFrameBuffer(), modelMeshNode);
		modelEntity->setAnimation(modelMeshAnimation);
	}

	//
	return prototype;
}

void UIEditorTabView::setModelMeshNode(const string& modelMeshNode) {
	if (projectedUi == false) return;
	//
	auto modelEntity = dynamic_cast<Object3D*>(engine->getEntity("model"));
	if (modelEntity != nullptr) {
		modelEntity->unbindDiffuseTexture();
		if (modelMeshNode.empty() == false) modelEntity->bindDiffuseTexture(guiEngine->getFrameBuffer(), modelMeshNode);
	}
}

void UIEditorTabView::setModelMeshAnimation(const string& modelMeshAnimation) {
	if (projectedUi == false) return;
	//
	auto modelEntity = dynamic_cast<Object3D*>(engine->getEntity("model"));
	if (modelEntity != nullptr) {
		modelEntity->setAnimation(modelMeshAnimation);
	}
}

void UIEditorTabView::removePrototype() {
	//
	if (projectedUi == true) {
		engine->dispose();
		delete engine;
		delete cameraRotationInputHandler;
		engine = nullptr;
		cameraRotationInputHandler = nullptr;
		projectedUi = false;
	}
	if (prototype != nullptr) delete prototype;
	prototype = nullptr;
}
