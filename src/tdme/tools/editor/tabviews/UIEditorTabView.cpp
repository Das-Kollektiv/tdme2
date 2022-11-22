#include <tdme/tools/editor/tabviews/UIEditorTabView.h>

#include <string>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/model/PBRMaterialProperties.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/FrameBuffer.h>
#include <tdme/engine/Object.h>
#include <tdme/engine/SimplePartition.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent.h>
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
using std::unordered_set;
using std::vector;

using tdme::tools::editor::tabviews::UIEditorTabView;

using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::model::Color4;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::model::PBRMaterialProperties;
using tdme::engine::model::SpecularMaterialProperties;
using tdme::engine::prototype::Prototype;
using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::engine::Object;
using tdme::engine::SimplePartition;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
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
	this->screenNode = screenNode;
	this->popUps = editorView->getPopUps();
	screenNodes.push_back(screenNode);
	screenDimensions.push_back({ screenNode->getSizeConstraints().maxWidth, screenNode->getSizeConstraints().maxHeight });
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
		//
		// mouse wheel events that happened to route to GUI engine
		vector<int> checkedGUIEngineMouseEventIndices;
		vector<int> checkedEngineMouseEventIndices;
		vector<int> unusedEngineMouseEventIndices;
		//
		auto modelEntity = dynamic_cast<Object*>(engine->getEntity("model"));
		if (modelEntity != nullptr && modelMeshNode.empty() == false && modelEntity->getModel()->getNodeById(modelMeshNode) != nullptr) {
			auto modelEntityWorldMatrix = modelEntity->getNodeTransformMatrix(modelMeshNode);
			auto modelEntityModelImportMatrixInverted = modelEntity->getModel()->getImportTransformMatrix().clone().invert();
			auto modelEntityWorldMatrixInverted = modelEntityWorldMatrix.clone().multiply(modelEntity->getTransformMatrix()).multiply(modelEntityModelImportMatrixInverted).invert();
			// handle mouse events
			auto& engineMouseEvents = engine->getGUI()->getMouseEvents();
			auto& guiEngineMouseEvents = guiEngine->getGUI()->getMouseEvents();
			auto mouseEventIdx = 0;
			for (auto& event: engineMouseEvents) {
				if (event.isProcessed() == true) {
					mouseEventIdx++;
					continue;
				}
				// try to push event to gui engine if in book space
				Vector3 mouseWorldCoordinate = engine->computeWorldCoordinateByMousePosition(event.getXUnscaled(), event.getYUnscaled());
				auto bookLocalCoordinate = modelEntityWorldMatrixInverted.multiply(mouseWorldCoordinate);
				auto clonedEvent = event;
				clonedEvent.setX((bookLocalCoordinate.getX() - projectedUiMinX) * (guiEngine->getWidth() / (projectedUiMaxX - projectedUiMinX)));
				clonedEvent.setY((bookLocalCoordinate.getZ() - projectedUiMinZ) * (guiEngine->getHeight() / (projectedUiMaxZ - projectedUiMinZ)));
				clonedEvent.setXUnscaled(clonedEvent.getX());
				clonedEvent.setYUnscaled(clonedEvent.getY());
				if (clonedEvent.getX() >= 0 && clonedEvent.getX() < guiEngine->getWidth() &&
					clonedEvent.getY() >= 0 && clonedEvent.getY() < guiEngine->getHeight()) {
					checkedGUIEngineMouseEventIndices.push_back(guiEngineMouseEvents.size());
					guiEngineMouseEvents.push_back(clonedEvent);
					// ok we add this mouse event to our checked mouse event indices list
					checkedEngineMouseEventIndices.push_back(mouseEventIdx);
				} else {
					// ok add this to unused mouse event indices list
					unusedEngineMouseEventIndices.push_back(mouseEventIdx);
				}
				mouseEventIdx++;
			}
		} else {
			// just add all events into unused mouse event indices
			auto& engineMouseEvents = engine->getGUI()->getMouseEvents();
			for (auto i = 0; i < engineMouseEvents.size(); i++) unusedEngineMouseEventIndices.push_back(i);
		}
		// handle GUI engine events
		guiEngine->getGUI()->handleEvents(false);
		// clear mouse events of main engine
		auto engineMouseEvents = engine->getGUI()->getMouseEvents();
		auto& guiEngineMouseEvents = guiEngine->getGUI()->getMouseEvents();
		engine->getGUI()->getMouseEvents().clear();
		// TODO: we might want to sort the events by creation time or id
		// restore mouse events of main engine from GUI engine events
		for (auto i = 0; i < checkedEngineMouseEventIndices.size(); i++) {
			if (guiEngineMouseEvents[checkedGUIEngineMouseEventIndices[i]].isProcessed() == false) engine->getGUI()->getMouseEvents().push_back(engineMouseEvents[checkedEngineMouseEventIndices[i]]);
		}
		for (auto i = 0; i < unusedEngineMouseEventIndices.size(); i++) {
			engine->getGUI()->getMouseEvents().push_back(engineMouseEvents[unusedEngineMouseEventIndices[i]]);
		}
		// clear GUI engine events, as we did not do this before after handing events
		guiEngine->getGUI()->getKeyboardEvents().clear();
		guiEngine->getGUI()->getMouseEvents().clear();
		// camera rotation input handler, which uses main engine events
		cameraRotationInputHandler->handleInputEvents();
		// clear main engine events
		engine->getGUI()->getMouseEvents().clear();
		engine->getGUI()->getKeyboardEvents().clear();
	} else {
		// just handle events from GUI engine
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
		screenNode->addTooltipRequestListener(uiTabController);
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
	screenDimensions.push_back({ -1, -1});
}

void UIEditorTabView::setScreen(int screenIdx, GUIScreenNode* screenNode) {
	if (screenIdx < 0 || screenIdx >= screenNodes.size()) return;
	screenNodes[screenIdx] = screenNode;
	screenDimensions[screenIdx] = { screenNode->getSizeConstraints().maxWidth, screenNode->getSizeConstraints().maxHeight };
}

void UIEditorTabView::unsetScreen(int screenIdx) {
	if (screenIdx < 0 || screenIdx >= screenNodes.size()) return;
	auto screenNode = screenNodes[screenIdx];
	if (screenNode != nullptr) {
		guiEngine->getGUI()->removeScreen(screenNode->getId());
		screenNodes[screenIdx] = nullptr;
		screenDimensions[screenIdx] = { -1, -1 };
	}
}

void UIEditorTabView::removeScreen(int screenIdx) {
	if (screenIdx < 0 || screenIdx >= screenNodes.size()) return;
	auto screenNode = screenNodes[screenIdx];
	if (screenNode != nullptr) {
		guiEngine->getGUI()->removeScreen(screenNode->getId());
		screenNodes.erase(screenNodes.begin() + screenIdx);
		screenDimensions.erase(screenDimensions.begin() + screenIdx);
	}
}

void UIEditorTabView::reAddScreens() {
	guiEngine->getGUI()->resetRenderScreens();
	auto screensMaxWidth = -1;
	auto screensMaxHeight = -1;
	for (auto i = 0; i < screenNodes.size(); i++) {
		auto screenNode = screenNodes[i];
		auto& screenDimensionsEntity = screenDimensions[i];
		if (screenNode == nullptr) continue;
		auto screenMaxWidth = screenDimensionsEntity[0];
		auto screenMaxHeight = screenDimensionsEntity[1];
		if (screenMaxWidth > screensMaxWidth) screensMaxWidth = screenMaxWidth;
		if (screenMaxHeight > screensMaxHeight) screensMaxHeight = screenMaxHeight;
		screenNode->getSizeConstraints().minWidth = -1;
		screenNode->getSizeConstraints().minHeight = -1;
		screenNode->getSizeConstraints().maxWidth = -1;
		screenNode->getSizeConstraints().maxHeight = -1;
		guiEngine->getGUI()->addScreen(screenNode->getId(), screenNode);
		guiEngine->getGUI()->addRenderScreen(screenNode->getId());
	}
	if (screensMaxWidth == -1) screensMaxWidth = 1920;
	if (screensMaxHeight == -1) screensMaxHeight = 1080;
	if (guiEngine->getWidth() != screensMaxWidth || guiEngine->getHeight() != screensMaxHeight) {
		guiEngine->reshape(screensMaxWidth, screensMaxHeight);
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
		//
		return nullptr;
	}

	//
	auto projectedUiLast = projectedUi;
	if (projectedUi == false) {
		engine = Engine::createOffScreenInstance(512, 512, true, true, false);
		engine->setPartition(new SimplePartition());
		engine->setShadowMapLightEyeDistanceScale(0.1f);
		engine->setSceneColor(Color4(125.0f / 255.0f, 125.0f / 255.0f, 125.0f / 255.0f, 1.0f));
		guiEngine->setSceneColor(Color4(0.0f, 0.0f, 0.0f, 0.0f));
		cameraRotationInputHandler = new CameraRotationInputHandler(engine, this);
		projectedUi = true;
	}
	Vector3 objectScale;
	Tools::setupPrototype(prototype, engine, cameraRotationInputHandler->getLookFromRotations(), 1, objectScale, cameraRotationInputHandler, 1.5f, projectedUiLast == true);

	// scale model, ground * 2
	auto modelEntity = engine->getEntity("model");
	if (modelEntity != nullptr) {
		modelEntity->setScale(modelEntity->getScale() * 2.0f);
		modelEntity->update();
		static_cast<Object*>(modelEntity)->bindDiffuseTexture(guiEngine->getFrameBuffer(), modelMeshNode);
		static_cast<Object*>(modelEntity)->setAnimation(modelMeshAnimation);
	}
	auto groundEntity = engine->getEntity("ground");
	if (groundEntity != nullptr) {
		groundEntity->setScale(groundEntity->getScale() * 2.0f);
		groundEntity->update();
	}

	//
	setModelMeshNode(modelMeshNode);

	//
	return prototype;
}

void UIEditorTabView::setModelMeshNode(const string& modelMeshNode) {
	if (projectedUi == false) return;
	//
	auto modelEntity = dynamic_cast<Object*>(engine->getEntity("model"));
	if (modelEntity != nullptr) {
		modelEntity->unbindDiffuseTexture();
		if (modelMeshNode.empty() == false) modelEntity->bindDiffuseTexture(guiEngine->getFrameBuffer(), modelMeshNode);
	}

	this->modelMeshNode = modelMeshNode;
	projectedUiMinX = Float::MAX_VALUE;
	projectedUiMinZ = Float::MAX_VALUE;
	projectedUiMaxX = Float::MIN_VALUE;
	projectedUiMaxZ = Float::MIN_VALUE;

	auto model = prototype->getModel();
	if (model == nullptr || model->getNodeById(modelMeshNode) == nullptr) return;

	//
	auto& modelMeshNodeFacesEntities = model->getNodeById(modelMeshNode)->getFacesEntities();
	unordered_set<string> materialIds;
	for (auto& facesEntity: modelMeshNodeFacesEntities) {
		if (facesEntity.getMaterial() != nullptr) materialIds.insert(facesEntity.getMaterial()->getId());
		for (auto& face: facesEntity.getFaces()) {
			for (auto i = 0; i < 3; i++) {
				projectedUiMinZ = Math::min(projectedUiMinZ, face.getNode()->getVertices()[face.getVertexIndices()[i]].getZ());
				projectedUiMinX = Math::min(projectedUiMinX, face.getNode()->getVertices()[face.getVertexIndices()[i]].getX());
				projectedUiMaxZ = Math::max(projectedUiMaxZ, face.getNode()->getVertices()[face.getVertexIndices()[i]].getZ());
				projectedUiMaxX = Math::max(projectedUiMaxX, face.getNode()->getVertices()[face.getVertexIndices()[i]].getX());
			}
		}
	}

	//
	for (auto& materialId: materialIds) {
		auto materialIt = model->getMaterials().find(materialId);
		auto material = materialIt != model->getMaterials().end()?materialIt->second:nullptr;
		if (material == nullptr) continue;
		material->getSpecularMaterialProperties()->setDiffuseColor(Color4(0.8f, 0.8f, 0.8f, 0.9999f));
		if (material->getPBRMaterialProperties() != nullptr) material->getPBRMaterialProperties()->setBaseColorFactor(Color4(1.0f, 1.0f, 1.0f, 0.9999f));
	}
}

void UIEditorTabView::setModelMeshAnimation(const string& modelMeshAnimation) {
	if (projectedUi == false) return;
	//
	auto modelEntity = dynamic_cast<Object*>(engine->getEntity("model"));
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

	//
	guiEngine->setSceneColor(Color4(125.0f / 255.0f, 125.0f / 255.0f, 125.0f / 255.0f, 1.0f));
}
