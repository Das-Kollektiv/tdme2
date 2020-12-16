#include <tdme/tools/leveleditor/views/LevelEditorView.h>

#include <algorithm>
#include <string>
#include <vector>

#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/EntityPickingFilter.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/PartitionOctTree.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/SceneConnector.h>
#include <tdme/engine/Timing.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/utilities/ModelTools.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>
#include <tdme/engine/model/TextureCoordinate.h>
#include <tdme/engine/model/UpVector.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/LineSegment.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/math/Math.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/leveleditor/TDMESceneEditor.h>
#include <tdme/tools/leveleditor/controller/SceneEditorLibraryScreenController.h>
#include <tdme/tools/leveleditor/controller/SceneEditorScreenController.h>
#include <tdme/engine/SceneConnector.h>
#include <tdme/tools/leveleditor/views/LevelEditorView_ObjectColor.h>
#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/tools/shared/controller/ProgressBarScreenController.h>
#include <tdme/engine/fileio/scenes/SceneWriter.h>
#include <tdme/engine/fileio/scenes/SceneReader.h>
#include <tdme/engine/fileio/ProgressCallback.h>
#include <tdme/engine/prototype/Prototype_Type.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/scene/SceneLibrary.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/engine/scene/SceneLight.h>
#include <tdme/engine/scene/SceneEntity.h>
#include <tdme/engine/scene/ScenePropertyPresets.h>
#include <tdme/engine/prototype/PrototypeProperty.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/tools/shared/views/Gizmo.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/utilities/Character.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/Properties.h>
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Console.h>

using std::find;
using std::remove;
using std::vector;
using std::to_string;
using std::string;

using tdme::tools::leveleditor::views::LevelEditorView;

using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::EntityPickingFilter;
using tdme::engine::Light;
using tdme::engine::Object3D;
using tdme::engine::PartitionOctTree;
using tdme::engine::Rotation;
using tdme::engine::SceneConnector;
using tdme::engine::Timing;
using tdme::engine::Transformations;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::model::Color4;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Node;
using tdme::engine::model::Material;
using tdme::engine::model::UpVector;
using tdme::engine::model::Model;
using tdme::utilities::ModelTools;
using tdme::engine::model::RotationOrder;
using tdme::engine::model::SpecularMaterialProperties;
using tdme::engine::model::TextureCoordinate;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::LineSegment;
using tdme::gui::GUI;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIScreenNode;
using tdme::math::Math;
using tdme::math::Quaternion;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::leveleditor::TDMESceneEditor;
using tdme::tools::leveleditor::controller::SceneEditorLibraryScreenController;
using tdme::tools::leveleditor::controller::SceneEditorScreenController;
using tdme::engine::SceneConnector;
using tdme::tools::leveleditor::views::LevelEditorView_ObjectColor;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::controller::ProgressBarScreenController;
using tdme::engine::fileio::scenes::SceneWriter;
using tdme::engine::fileio::scenes::SceneReader;
using tdme::engine::fileio::ProgressCallback;
using tdme::engine::prototype::Prototype_Type;
using tdme::engine::prototype::Prototype;
using tdme::engine::scene::Scene;
using tdme::engine::scene::SceneLibrary;
using tdme::engine::scene::SceneLight;
using tdme::engine::scene::SceneEntity;
using tdme::engine::scene::ScenePropertyPresets;
using tdme::engine::prototype::PrototypeProperty;
using tdme::tools::shared::tools::Tools;
using tdme::tools::shared::views::Gizmo;
using tdme::tools::shared::views::PopUps;
using tdme::utilities::Character;
using tdme::utilities::Float;
using tdme::utilities::Properties;
using tdme::utilities::StringTools;
using tdme::utilities::Exception;
using tdme::utilities::Console;

vector<string> LevelEditorView::OBJECTCOLOR_NAMES = {
	"blue",
	"yellow",
	"magenta",
	"cyan",
	"none"
};

LevelEditorView::LevelEditorView(PopUps* popUps): Gizmo(Engine::getInstance(), "le")
{
	this->popUps = popUps;
	snappingX = 1.0f;
	snappingZ = 1.0f;
	snappingEnabled = false;
	camLookRotationX = new Rotation(Vector3(1.0f, 0.0f, 0.0f), -45.0f);
	camLookRotationY = new Rotation(Vector3(0.0f, 1.0f, 0.0f), 0.0f);
	camScaleMax = 15.0f;
	camScaleMin = 0.05f;
	mouseDownLastX = LevelEditorView::MOUSE_DOWN_LAST_POSITION_NONE;
	mouseDownLastY = LevelEditorView::MOUSE_DOWN_LAST_POSITION_NONE;
	mousePanningSide = LevelEditorView::MOUSE_PANNING_NONE;
	mousePanningForward = LevelEditorView::MOUSE_PANNING_NONE;
	mouseRotationX = LevelEditorView::MOUSE_ROTATION_NONE;
	mouseRotationY = LevelEditorView::MOUSE_ROTATION_NONE;
	reloadEntityLibrary = false;
	selectedPrototype = nullptr;
	keyLeft = false;
	keyRight = false;
	keyUp = false;
	keyDown = false;
	keyA = false;
	keyD = false;
	keyW = false;
	keyS = false;
	keyPlus = false;
	keyMinus = false;
	keyR = false;
	keyControl = false;
	keyEscape = false;
	placeEntityMode = false;
	placeEntityValid = false;
	placeEntityYRotation = 0;
	pasteMode = false;
	pasteModeValid = false;
	mouseDownLastX = MOUSE_DOWN_LAST_POSITION_NONE;
	mouseDownLastY = MOUSE_DOWN_LAST_POSITION_NONE;
	mouseDragging = false;
	mouseDraggingLastObject = nullptr;
	gridEnabled = false;
	gridY = 0.0f;
	objectColors["red"] = new LevelEditorView_ObjectColor(this, 1.5f, 0.8f, 0.8f, 0.5f, 0.0f, 0.0f);
	objectColors["green"] = new LevelEditorView_ObjectColor(this, 0.8f, 1.5f, 0.8f, 0.0f, 0.5f, 0.0f);
	objectColors["blue"] = new LevelEditorView_ObjectColor(this, 0.8f, 0.8f, 1.5f, 0.0f, 0.0f, 0.5f);
	objectColors["yellow"] = new LevelEditorView_ObjectColor(this, 1.5f, 1.5f, 0.8f, 0.5f, 0.5f, 0.0f);
	objectColors["magenta"] = new LevelEditorView_ObjectColor(this, 1.5f, 0.8f, 1.5f, 0.5f, 0.0f, 0.5f);
	objectColors["cyan"] = new LevelEditorView_ObjectColor(this, 0.8f, 1.5f, 1.5f, 0.0f, 0.5f, 0.5f);
	objectColors["none"] = new LevelEditorView_ObjectColor(this, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	camScale = 1.0f;
	camLookRotationX->update();
	camLookRotationY->update();
	levelEditorGround = createLevelEditorGroundPlateModel();
	engine = Engine::getInstance();

	{
		// entity picking filter for no grid
		class PrototypePickingFilterNoGrid: public virtual EntityPickingFilter
		{
		public:
			bool filterEntity(Entity* entity) override {
				return entity->getId() != "tdme.leveleditor.grid";
			}

			/**
			 * Public constructor
			 * @param levelEditorView scene editor view
			 */
			PrototypePickingFilterNoGrid(LevelEditorView* levelEditorView): levelEditorView(levelEditorView) {
			}

		private:
			LevelEditorView* levelEditorView;
		};
		entityPickingFilterNoGrid = new PrototypePickingFilterNoGrid(this);
	}

	{
		// entity picking filter for no placing object
		class PrototypePickingFilterPlacing: public virtual EntityPickingFilter
		{
		public:
			bool filterEntity(Entity* entity) override {
				return
						entity->getId() != "tdme.leveleditor.placeentity" &&
						StringTools::startsWith(entity->getId(), "tdme.leveleditor.paste.") == false &&
						StringTools::startsWith(entity->getId(), "le.tdme.leveleditor.gizmo.") == false;
			}

			/**
			 * Public constructor
			 * @param levelEditorView scene editor view
			 */
			PrototypePickingFilterPlacing(LevelEditorView* levelEditorView): levelEditorView(levelEditorView) {
			}

		private:
			LevelEditorView* levelEditorView;
		};
		entityPickingFilterPlacing = new PrototypePickingFilterPlacing(this);
	}
}

LevelEditorView::~LevelEditorView() {
	delete camLookRotationX;
	delete camLookRotationY;
	delete objectColors["red"];
	delete objectColors["green"];
	delete objectColors["blue"];
	delete objectColors["yellow"];
	delete objectColors["magenta"];
	delete objectColors["cyan"];
	delete objectColors["none"];
	delete levelEditorGround;
	delete entityPickingFilterNoGrid;
	delete entityPickingFilterPlacing;
	delete sceneEditorScreenController;
}

PopUps* LevelEditorView::getPopUps()
{
	return popUps;
}

const string LevelEditorView::getFileName()
{
	return FileSystem::getInstance()->getFileName(scene.getFileName());
}

Scene* LevelEditorView::getScene()
{
	return &scene;
}

Prototype* LevelEditorView::getSelectedPrototype()
{
	return selectedPrototype;
}

SceneEntity* LevelEditorView::getSelectedSceneEntity()
{
	if (selectedEntityIds.size() != 1) return nullptr;

	auto selectedObject = scene.getEntity(selectedEntityIds[0]);
	return selectedObject != nullptr && StringTools::startsWith(selectedObject->getId(), "tdme.leveleditor.") == false ? scene.getEntity(selectedObject->getId()) : static_cast< SceneEntity* >(nullptr);
}

bool LevelEditorView::isGridEnabled()
{
	return gridEnabled;
}

void LevelEditorView::setGridEnabled(bool gridEnabled)
{
	this->gridEnabled = gridEnabled;
	if (gridEnabled) {
		updateGrid();
	} else {
		removeGrid();
	}
}

float LevelEditorView::getGridY()
{
	return gridY;
}

void LevelEditorView::setGridY(float gridY)
{
	if (gridEnabled)
		removeGrid();

	this->gridY = gridY;
	if (gridEnabled)
		updateGrid();

}

void LevelEditorView::getSnapping(bool& snappingEnabled, float& snappingX, float& snappingZ) {
	snappingEnabled = this->snappingEnabled;
	snappingX = this->snappingX;
	snappingZ = this->snappingZ;
}

void LevelEditorView::setSnapping(bool snappingEnabled, float snappingX, float snappingZ) {
	this->snappingEnabled = snappingEnabled;
	this->snappingX = snappingX;
	this->snappingZ = snappingZ;
}

void LevelEditorView::selectPrototypeFromLibrary(int id)
{
	selectedPrototype = TDMESceneEditor::getInstance()->getSceneLibrary()->getPrototype(id);
}

void LevelEditorView::handleInputEvents()
{
	#if !defined(GLFW3) && !defined(VUKAN)
		keyControl = false;
		keyShift = false;
	#endif
	auto keyControlX = false;
	auto keyControlC = false;
	auto keyControlV = false;
	auto keyDelete = false;
	mousePanningSide = MOUSE_PANNING_NONE;
	mousePanningForward = MOUSE_PANNING_NONE;
	for (auto i = 0; i < engine->getGUI()->getKeyboardEvents().size(); i++) {
		auto& event = engine->getGUI()->getKeyboardEvents()[i];
		if (event.isProcessed() == true) continue;
		if (event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_TYPED) continue;
		auto isKeyDown = event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED;
		#if defined(GLFW3) || defined(VUKAN)
			if (event.getKeyCode() == KEYBOARD_KEYCODE_LEFT_SHIFT) keyShift = isKeyDown;
			if (event.getKeyCode() == KEYBOARD_KEYCODE_LEFT_CTRL) keyControl = isKeyDown;
		#else
			keyControl = event.isControlDown();
			keyShift = event.isShiftDown();
		#endif
		if (event.getKeyCode() == GUIKeyboardEvent::KEYCODE_ESCAPE) keyEscape = isKeyDown;
		if (event.getKeyCode() == GUIKeyboardEvent::KEYCODE_LEFT) keyLeft = isKeyDown;
		if (event.getKeyCode() == GUIKeyboardEvent::KEYCODE_RIGHT) keyRight = isKeyDown;
		if (event.getKeyCode() == GUIKeyboardEvent::KEYCODE_UP) keyUp = isKeyDown;
		if (event.getKeyCode() == GUIKeyboardEvent::KEYCODE_DOWN) keyDown = isKeyDown;
		if (event.getKeyCode() == GUIKeyboardEvent::KEYCODE_BACKSPACE) keyDelete = isKeyDown;
		if (Character::toLowerCase(event.getKeyChar()) == 24) keyControlX = isKeyDown;
		if (Character::toLowerCase(event.getKeyChar()) == 3) keyControlC = isKeyDown;
		if (Character::toLowerCase(event.getKeyChar()) == 22) keyControlV = isKeyDown;
		if (Character::toLowerCase(event.getKeyChar()) == 'x' && keyControl == true) keyControlX = isKeyDown;
		if (Character::toLowerCase(event.getKeyChar()) == 'c' && keyControl == true) keyControlC = isKeyDown;
		if (Character::toLowerCase(event.getKeyChar()) == 'v' && keyControl == true) keyControlV = isKeyDown;
		if (Character::toLowerCase(event.getKeyChar()) == 'a') keyA = isKeyDown;
		if (Character::toLowerCase(event.getKeyChar()) == 'd') keyD = isKeyDown;
		if (Character::toLowerCase(event.getKeyChar()) == 'w') keyW = isKeyDown;
		if (Character::toLowerCase(event.getKeyChar()) == 's') keyS = isKeyDown;
		if (Character::toLowerCase(event.getKeyChar()) == '+') keyPlus = isKeyDown;
		if (Character::toLowerCase(event.getKeyChar()) == '-') keyMinus = isKeyDown;
		if (Character::toLowerCase(event.getKeyChar()) == 'r') keyR = isKeyDown;
		if (Character::toLowerCase(event.getKeyChar()) == '.' && !isKeyDown == false) placeEntityYRotation = (placeEntityYRotation + 1) % 4;
		if (Character::toLowerCase(event.getKeyChar()) == ',' && !isKeyDown == false) placeEntityYRotation = (placeEntityYRotation + 3) % 4;
		if (Character::toLowerCase(event.getKeyChar()) == '1' && isKeyDown == true) { setGizmoType(GIZMOTYPE_ALL); updateGizmo(); }
		if (Character::toLowerCase(event.getKeyChar()) == '2' && isKeyDown == true) { setGizmoType(GIZMOTYPE_TRANSLATE); updateGizmo(); }
		if (Character::toLowerCase(event.getKeyChar()) == '3' && isKeyDown == true) { setGizmoType(GIZMOTYPE_ROTATE); updateGizmo(); }
		if (Character::toLowerCase(event.getKeyChar()) == '4' && isKeyDown == true) { setGizmoType(GIZMOTYPE_SCALE); updateGizmo(); }
	}
	for (auto i = 0; i < engine->getGUI()->getMouseEvents().size(); i++) {
		auto& event = engine->getGUI()->getMouseEvents()[i];

		if ((event.getType() == GUIMouseEvent::MOUSEEVENT_MOVED ||
			event.getType() == GUIMouseEvent::MOUSEEVENT_DRAGGED) &&
			event.getXUnscaled() >= 0 &&
			event.getYUnscaled() >= 0) {
			placeEntityMouseX = event.getXUnscaled();
			placeEntityMouseY = event.getYUnscaled();
		}

		if (event.isProcessed() == true) continue;

		if (event.getType() == GUIMouseEvent::MOUSEEVENT_DRAGGED) {
			if (mouseDragging == false) {
				mouseDragging = true;
				mouseDownLastX = event.getXUnscaled();
				mouseDownLastY = event.getYUnscaled();
				mouseDraggingLastObject = nullptr;
			}
		} else {
			if (mouseDragging == true) {
				mouseDownLastX = MOUSE_DOWN_LAST_POSITION_NONE;
				mouseDownLastY = MOUSE_DOWN_LAST_POSITION_NONE;
				mouseDragging = false;
				mouseDraggingLastObject = nullptr;
			}
		}
		if (event.getButton() == MOUSE_BUTTON_LEFT) {
			if (event.getType() == GUIMouseEvent::MOUSEEVENT_RELEASED) {
				if (pasteMode == true && pasteModeValid == true) {
					pasteEntities(false);
					if (keyShift == false) unsetPasteMode();
				} else
				if (placeEntityMode == true && placeEntityValid == true) {
					placeEntity();
					if (keyShift == false) unsetPlaceEntityMode();
				} else {
					setGizmoMode(GIZMOMODE_NONE);
				}
			} else {
				Node* selectedEntityNode = nullptr;
				Entity* selectedEntity = nullptr;
				if (getGizmoMode() == GIZMOMODE_NONE) selectedEntity = engine->getEntityByMousePosition(event.getXUnscaled(), event.getYUnscaled(), entityPickingFilterNoGrid, &selectedEntityNode);
				if (mouseDragging == true) {
					Vector3 deltaTranslation;
					Vector3 deltaRotation;
					Vector3 deltaScale;
					if (determineGizmoDeltaTransformations(mouseDownLastX, mouseDownLastY, event.getXUnscaled(), event.getYUnscaled(), deltaTranslation, deltaRotation, deltaScale) == true) {
						auto gizmoEntity = getGizmoObject3D();
						if (gizmoEntity != nullptr) {
							Transformations rotations;
							rotations.addRotation(scene.getRotationOrder()->getAxis0(), deltaRotation[scene.getRotationOrder()->getAxis0VectorIndex()]);
							rotations.addRotation(scene.getRotationOrder()->getAxis1(), deltaRotation[scene.getRotationOrder()->getAxis1VectorIndex()]);
							rotations.addRotation(scene.getRotationOrder()->getAxis2(), deltaRotation[scene.getRotationOrder()->getAxis2VectorIndex()]);
							rotations.update();
							for (auto selectedEntityId: selectedEntityIds) {
								auto _selectedEntity = engine->getEntity(selectedEntityId);
								if (_selectedEntity != nullptr && StringTools::startsWith(_selectedEntity->getId(), "tdme.leveleditor.") == false) {
									auto sceneEntity = scene.getEntity(_selectedEntity->getId());
									if (sceneEntity == nullptr) continue;
									auto translation = sceneEntity->getTransformations().getTranslation();
									auto translationRelative = translation.clone().sub(gizmoEntity->getTranslation());
									translation = gizmoEntity->getTranslation().clone().add(rotations.getRotationsQuaternion().multiply(translationRelative, translationRelative));
									sceneEntity->getTransformations().setTranslation(translation.clone().add(deltaTranslation));
									auto scale = sceneEntity->getTransformations().getScale().clone().scale(deltaScale);
									if (Math::abs(scale.getX()) < 0.01f) scale.setX(Math::sign(scale.getX()) * 0.01f);
									if (Math::abs(scale.getY()) < 0.01f) scale.setY(Math::sign(scale.getY()) * 0.01f);
									if (Math::abs(scale.getZ()) < 0.01f) scale.setZ(Math::sign(scale.getZ()) * 0.01f);
									if (Math::abs(scale.getX()) > 100.0f) scale.setX(Math::sign(scale.getX()) * 100.0f);
									if (Math::abs(scale.getY()) > 100.0f) scale.setY(Math::sign(scale.getY()) * 100.0f);
									if (Math::abs(scale.getZ()) > 100.0f) scale.setZ(Math::sign(scale.getZ()) * 100.0f);
									sceneEntity->getTransformations().setScale(scale);
									if ((sceneEntity->getPrototype()->getType()->getGizmoTypeMask() & Gizmo::GIZMOTYPE_ROTATE) == Gizmo::GIZMOTYPE_ROTATE) {
										sceneEntity->getTransformations().setRotationAngle(scene.getRotationOrder()->getAxisXIndex(), sceneEntity->getTransformations().getRotationAngle(scene.getRotationOrder()->getAxisXIndex()) + deltaRotation[0]);
										sceneEntity->getTransformations().setRotationAngle(scene.getRotationOrder()->getAxisYIndex(), sceneEntity->getTransformations().getRotationAngle(scene.getRotationOrder()->getAxisYIndex()) + deltaRotation[1]);
										sceneEntity->getTransformations().setRotationAngle(scene.getRotationOrder()->getAxisZIndex(), sceneEntity->getTransformations().getRotationAngle(scene.getRotationOrder()->getAxisZIndex()) + deltaRotation[2]);
									}
									sceneEntity->getTransformations().update();
									_selectedEntity->fromTransformations(sceneEntity->getTransformations());
								}
							}
							if (selectedEntityIds.size() == 1) {
								auto _selectedEntity = engine->getEntity(selectedEntityIds[0]);
								auto sceneEntity = scene.getEntity(_selectedEntity->getId());
								sceneEditorScreenController->setEntityTransformations(
									_selectedEntity->getTranslation(),
									_selectedEntity->getScale(),
									_selectedEntity->getRotationAngle(scene.getRotationOrder()->getAxisXIndex()),
									_selectedEntity->getRotationAngle(scene.getRotationOrder()->getAxisYIndex()),
									_selectedEntity->getRotationAngle(scene.getRotationOrder()->getAxisZIndex()),
									(sceneEntity->getPrototype()->getType()->getGizmoTypeMask() & Gizmo::GIZMOTYPE_ROTATE) == 0
								);
								setGizmoRotation(_selectedEntity->getTransformations());
							}
						}
						if (Math::abs(deltaTranslation.getX()) > Math::EPSILON ||
							Math::abs(deltaTranslation.getY()) > Math::EPSILON ||
							Math::abs(deltaTranslation.getZ()) > Math::EPSILON) {
							updateGizmo();
						}
						updateGUITransformationsElements();
					}
				} else
				if (determineGizmoMode(selectedEntity, selectedEntityNode) == true) {
					// no op
					if (selectedEntityIds.size() == 1) {
						for (auto selectedEntityId: selectedEntityIds) {
							auto _selectedEntity = engine->getEntity(selectedEntityId);
							if (_selectedEntity != nullptr && StringTools::startsWith(_selectedEntity->getId(), "tdme.leveleditor.") == false) {
								setGizmoRotation(_selectedEntity->getTransformations());
							}
						}
					} else
					if (selectedEntityIds.size() > 1) {
						setGizmoRotation(Transformations());
					}
					updateGUITransformationsElements();
				} else {
					if (keyControl == false) {
						vector<Entity*> entitiesToRemove;
						for (auto selectedEntityId: selectedEntityIds) {
							auto selectedEntity = engine->getEntity(selectedEntityId);
							if (mouseDragging == true && mouseDraggingLastObject == selectedEntity) {
								// no op
							} else {
								if (selectedEntity != nullptr) entitiesToRemove.push_back(selectedEntity);
							}
						}
						for (auto entityToRemove: entitiesToRemove) {
							selectedEntityIds.erase(remove(selectedEntityIds.begin(), selectedEntityIds.end(), entityToRemove->getId()), selectedEntityIds.end());
							auto selectedEntitiyIdByIdIt = selectedEntityIdsById.find(entityToRemove->getId());
							if (selectedEntitiyIdByIdIt != selectedEntityIdsById.end()) {
								selectedEntityIdsById.erase(selectedEntitiyIdByIdIt);
							}
							sceneEditorScreenController->unselectEntitiesInEntityListBox(entityToRemove->getId());
							resetEntity(entityToRemove);
						}
					}
					if (selectedEntity != nullptr) {
						if (selectedEntityIdsById.find(selectedEntity->getId()) == selectedEntityIdsById.end()) {
							setStandardEntityColorEffect(selectedEntity);
							setHighlightEntityColorEffect(selectedEntity);
							selectedEntityIds.push_back(selectedEntity->getId());
							selectedEntityIdsById.insert(selectedEntity->getId());
							sceneEditorScreenController->selectEntityInEntityListbox(selectedEntity->getId());
							auto sceneEntity = scene.getEntity(selectedEntity->getId());
							if (sceneEntity != nullptr) {
								TDMESceneEditor::getInstance()->getSceneEditorLibraryScreenController()->selectPrototype(sceneEntity->getPrototype()->getId());
							}
						} else {
							resetEntity(selectedEntity);
							selectedEntityIds.erase(remove(selectedEntityIds.begin(), selectedEntityIds.end(), selectedEntity->getId()), selectedEntityIds.end());
							auto selectedEntityIdsByIdIt = selectedEntityIdsById.find(selectedEntity->getId());
							if (selectedEntityIdsByIdIt != selectedEntityIdsById.end()) {
								selectedEntityIdsById.erase(selectedEntityIdsByIdIt);
							}
							sceneEditorScreenController->unselectEntitiesInEntityListBox(selectedEntity->getId());
						}
						if (selectedEntityIds.size() == 1) {
							auto sceneEntity = scene.getEntity(selectedEntity->getId());
							if (sceneEntity != nullptr && sceneEntity->getPrototype()->getType()->hasNonEditScaleDownMode() == true) {
								selectedEntity->fromTransformations(sceneEntity->getTransformations());
							}
							setGizmoRotation(selectedEntity->getTransformations());
						}
						if (selectedEntityIds.size() > 1) setGizmoRotation(Transformations());
					}
					mouseDraggingLastObject = selectedEntity;
					updateGizmo();
					updateGUIElements();
				}
			}
		} else
		if (event.getButton() == MOUSE_BUTTON_RIGHT && mouseDragging == true) {
			if (mouseDownLastX != MOUSE_DOWN_LAST_POSITION_NONE && mouseDownLastY != MOUSE_DOWN_LAST_POSITION_NONE) {
				mousePanningSide = event.getXUnscaled() - mouseDownLastX;
				mousePanningForward = event.getYUnscaled() - mouseDownLastY;
			}
		} else
		if (event.getButton() == MOUSE_BUTTON_MIDDLE) {
			centerEntity();
			if (mouseDownLastX != MOUSE_DOWN_LAST_POSITION_NONE && mouseDownLastY != MOUSE_DOWN_LAST_POSITION_NONE) {
				mouseRotationX = event.getXUnscaled() - mouseDownLastX;
				mouseRotationY = event.getYUnscaled() - mouseDownLastY;
			}
		}
		if (event.getButton() != MOUSE_BUTTON_NONE) {
			mouseDownLastX = event.getXUnscaled();
			mouseDownLastY = event.getYUnscaled();
		}
		auto mouseWheel = event.getWheelY();
		if (mouseWheel != 0) {
			camScale += -mouseWheel * 0.1f;
			if (camScale < camScaleMin) camScale = camScaleMin;
			if (camScale > camScaleMax) camScale = camScaleMax;
			needGizmoUpdate = true;
		}
	}
	if (keyDelete == true) {
		Console::println("LevelEditorView::handleInputEvents(): Backspace");
		removeGizmo();
		removeEntities();
	}
	if (keyControlX == true) {
		Console::println("LevelEditorView::handleInputEvents(): CTRL-X");
		removeGizmo();
		copyEntities();
		removeEntities();
	}
	if (keyControlC == true) {
		Console::println("LevelEditorView::handleInputEvents(): CTRL-C");
		copyEntities();
	}
	if (keyControlV == true) {
		Console::println("LevelEditorView::handleInputEvents(): CTRL-V");
		removeGizmo();
		setPasteMode();
	}
}

void LevelEditorView::display()
{
	if (needGizmoUpdate == true) {
		updateGizmo();
		needGizmoUpdate = false;
	}

	auto cam = engine->getCamera();
	if (reloadEntityLibrary == true) {
		auto sceneLibrary = TDMESceneEditor::getInstance()->getSceneLibrary();
		for (auto i = 0; i < sceneLibrary->getPrototypeCount(); i++) {
			selectedPrototype = sceneLibrary->getPrototypeAt(i);
			Tools::oseThumbnail(selectedPrototype);
		}
		reloadEntityLibrary = false;
		TDMESceneEditor::getInstance()->getSceneEditorLibraryScreenController()->setPrototypeLibrary();
	}

	if ((placeEntityMode == true || pasteMode == true) && keyEscape == true) {
		unsetPlaceEntityMode();
		unsetPasteMode();
		keyEscape = false;
	}

	{
		auto selectedEngineEntity = engine->getEntity("tdme.leveleditor.placeentity");
		Vector3 worldCoordinate;
		placeEntityValid = false;
		pasteModeValid = false;
		if ((placeEntityMode == true || pasteMode == true) && engine->getEntityByMousePosition(placeEntityMouseX, placeEntityMouseY, worldCoordinate, entityPickingFilterPlacing) != nullptr) {
			if (placeEntityMode == true) {
				Transformations transformations;
				transformations.setTranslation(worldCoordinate);
				transformations.addRotation(scene.getRotationOrder()->getAxis0(), 0.0f);
				transformations.addRotation(scene.getRotationOrder()->getAxis1(), 0.0f);
				transformations.addRotation(scene.getRotationOrder()->getAxis2(), 0.0f);
				transformations.update();
				if (selectedEngineEntity == nullptr && selectedPrototype != nullptr) {
					selectedEngineEntity = SceneConnector::createEntity(selectedPrototype, "tdme.leveleditor.placeentity", transformations);
					if (selectedEngineEntity != nullptr) engine->addEntity(selectedEngineEntity);
				}
				if (selectedEngineEntity != nullptr) {
					if (snappingEnabled == true && (snappingX > Math::EPSILON || snappingZ > Math::EPSILON)) {
						if (snappingX > Math::EPSILON) worldCoordinate.setX(static_cast<int>(worldCoordinate.getX() / snappingX) * snappingX);
						if (snappingZ > Math::EPSILON) worldCoordinate.setZ(static_cast<int>(worldCoordinate.getZ() / snappingZ) * snappingZ);
						Vector3 snappedWorldCoordinate;
						if (engine->doRayCasting(worldCoordinate.clone().setY(10000.0f), worldCoordinate.clone().setY(-10000.0f), snappedWorldCoordinate, entityPickingFilterPlacing) != nullptr) {
							worldCoordinate = snappedWorldCoordinate;
						}
					}
					worldCoordinate.sub(Vector3(0.0f, selectedEngineEntity->getBoundingBox()->getMin().getY(), 0.0f));
					transformations.setTranslation(worldCoordinate);
					transformations.setRotationAngle(scene.getRotationOrder()->getAxisYIndex(), static_cast<float>(placeEntityYRotation) * 90.0f);
					transformations.update();
					selectedEngineEntity->fromTransformations(transformations);
					placeEntityTranslation = transformations.getTranslation();
					placeEntityValid = true;
				}
			} else
			if (pasteMode == true) {
				if (snappingEnabled == true && (snappingX > Math::EPSILON || snappingZ > Math::EPSILON)) {
					if (snappingX > Math::EPSILON) worldCoordinate.setX(static_cast<int>(worldCoordinate.getX() / snappingX) * snappingX);
					if (snappingZ > Math::EPSILON) worldCoordinate.setZ(static_cast<int>(worldCoordinate.getZ() / snappingZ) * snappingZ);
					Vector3 snappedWorldCoordinate;
					if (engine->doRayCasting(worldCoordinate.clone().setY(10000.0f), worldCoordinate.clone().setY(-10000.0f), snappedWorldCoordinate, entityPickingFilterPlacing) != nullptr) {
						worldCoordinate = snappedWorldCoordinate;
					}
				}
				placeEntityTranslation = worldCoordinate;
				pasteModeValid = true;
				pasteEntities(true);
			}
		}
	}

	if (mouseRotationX != MOUSE_ROTATION_NONE) {
		camLookRotationY->setAngle(camLookRotationY->getAngle() + mouseRotationX);
		camLookRotationY->update();
		mouseRotationX = 0;
		needGizmoUpdate = true;
	}
	if (mouseRotationY != MOUSE_ROTATION_NONE) {
		camLookRotationX->setAngle(camLookRotationX->getAngle() + mouseRotationY);
		camLookRotationX->update();
		mouseRotationY = 0;
		needGizmoUpdate = true;
	}
	if (keyA == true) camLookRotationY->setAngle(camLookRotationY->getAngle() + 1.0f);
	if (keyD == true) camLookRotationY->setAngle(camLookRotationY->getAngle() - 1.0f);
	if (keyW == true) camLookRotationX->setAngle(camLookRotationX->getAngle() + 1.0f);
	if (keyS == true) camLookRotationX->setAngle(camLookRotationX->getAngle() - 1.0f);
	if (keyMinus == true || keyPlus == true) {
		if (keyMinus == true) camScale += 0.05f;
		if (keyPlus == true) camScale -= 0.05f;
		if (camScale < camScaleMin) camScale = camScaleMin;
		if (camScale > camScaleMax) camScale = camScaleMax;
		needGizmoUpdate = true;
	}

	if (keyR == true) {
		camLookRotationX->setAngle(-45.0f);
		camLookRotationX->update();
		camLookRotationY->setAngle(0.0f);
		camLookRotationY->update();
		cam->setLookAt(scene.getCenter());
		camScale = 1.0f;
		needGizmoUpdate = true;
	}
	if (keyA == true|| keyD == true) {
		camLookRotationY->update();
		needGizmoUpdate = true;
	}

	if (keyW == true || keyS == true) {
		if (camLookRotationX->getAngle() > 89.99f) camLookRotationX->setAngle(89.99f);
		if (camLookRotationX->getAngle() < -89.99f) camLookRotationX->setAngle(-89.99f);
		camLookRotationX->update();
		needGizmoUpdate = true;
	}

	Vector3 tmpVector3;
	Vector3 FORWARD_VECTOR(0.0f, 0.0f, 1.0f);
	Vector3 SIDE_VECTOR(1.0f, 0.0f, 0.0f);
	Vector3 camLookAtToFromVector;
	Vector3 camForwardVector;
	Vector3 camSideVector;
	camLookRotationX->getQuaternion().multiply(FORWARD_VECTOR, tmpVector3);
	camLookRotationY->getQuaternion().multiply(tmpVector3, tmpVector3);
	camLookAtToFromVector.set(tmpVector3).scale(camScale * 10.0f);
	auto timing = engine->getTiming();
	camLookRotationY->getQuaternion().multiply(FORWARD_VECTOR, camForwardVector).scale(timing->getDeltaTime() / 1000.0f * 60.0f);
	camLookRotationY->getQuaternion().multiply(SIDE_VECTOR, camSideVector).scale(timing->getDeltaTime() / 1000.0f * 60.0f);

	auto camLookAt = cam->getLookAt();
	if (keyUp == true) camLookAt.sub(tmpVector3.set(camForwardVector).scale(0.1f));
	if (keyDown == true) camLookAt.add(tmpVector3.set(camForwardVector).scale(0.1f));
	if (keyLeft == true) camLookAt.sub(tmpVector3.set(camSideVector).scale(0.1f));
	if (keyRight == true) camLookAt.add(tmpVector3.set(camSideVector).scale(0.1f));
	if (mousePanningForward != MOUSE_PANNING_NONE) {
		camLookAt.sub(tmpVector3.set(camForwardVector).scale(mousePanningForward / 30.0f * camScale));
		mousePanningForward = MOUSE_PANNING_NONE;
		needGizmoUpdate = true;
	}
	if (mousePanningSide != MOUSE_PANNING_NONE) {
		camLookAt.sub(tmpVector3.set(camSideVector).scale(mousePanningSide / 30.0f * camScale));
		mousePanningSide = MOUSE_PANNING_NONE;
		needGizmoUpdate = true;
	}
	cam->setLookAt(camLookAt);
	cam->setLookFrom(cam->getLookAt().clone().add(camLookAtToFromVector));
	cam->setUpVector(cam->computeUpVector(cam->getLookFrom(), cam->getLookAt()));
	gridCenter.set(cam->getLookAt());
	updateGrid();

	// viewport
	auto xScale = (float)engine->getWidth() / (float)sceneEditorScreenController->getScreenNode()->getScreenWidth();
	auto yScale = (float)engine->getHeight() / (float)sceneEditorScreenController->getScreenNode()->getScreenHeight();
	auto viewPortLeft = 0;
	auto viewPortTop = 0;
	auto viewPortWidth = 0;
	auto viewPortHeight = 0;
	sceneEditorScreenController->getViewPort(viewPortLeft, viewPortTop, viewPortWidth, viewPortHeight);
	viewPortLeft = (int)((float)viewPortLeft * xScale);
	viewPortTop = (int)((float)viewPortTop * yScale);
	viewPortWidth = (int)((float)viewPortWidth * xScale);
	viewPortHeight = (int)((float)viewPortHeight * yScale);
	engine->getCamera()->enableViewPort(viewPortLeft, viewPortTop, viewPortWidth, viewPortHeight);

	//
	updateSkyPosition();

	// rendering
	engine->getGUI()->handleEvents();
	engine->getGUI()->render();
}

void LevelEditorView::selectEntities(const vector<string>& entityIds)
{
	removeGizmo();
	for (auto entityIdToRemove: selectedEntityIds) {
		auto entityToRemove = engine->getEntity(entityIdToRemove);
		if (entityToRemove != nullptr) setStandardEntityColorEffect(entityToRemove);
	}
	selectedEntityIds.clear();
	selectedEntityIdsById.clear();
	for (auto entityId: entityIds) {
		auto selectedEntity = engine->getEntity(entityId);
		if (selectedEntity == nullptr) continue;
		setStandardEntityColorEffect(selectedEntity);
		setHighlightEntityColorEffect(selectedEntity);
		selectedEntityIds.push_back(entityId);
		selectedEntityIdsById.insert(entityId);
	}
	updateGUIElements();
	updateGizmo();
}

void LevelEditorView::unselectEntities()
{
	removeGizmo();
	for (auto entityIdToRemove: selectedEntityIds) {
		auto entityToRemove = engine->getEntity(entityIdToRemove);
		if (entityToRemove == nullptr) continue;
		resetEntity(entityToRemove);
	}
	selectedEntityIds.clear();
	selectedEntityIdsById.clear();
	sceneEditorScreenController->unselectEntitiesInEntityListBox();
	updateGUIElements();
	removeGizmo();
}

void LevelEditorView::updateGUIElements()
{
	sceneEditorScreenController->setScreenCaption("Level Editor - " + Tools::getFileName(scene.getFileName()));
	sceneEditorScreenController->setSceneSize(scene.getDimension().getX(), scene.getDimension().getZ(), scene.getDimension().getY());
	if (selectedEntityIds.size() == 1) {
		auto selectedEntity = engine->getEntity(selectedEntityIds[0]);
		if (selectedEntity != nullptr && StringTools::startsWith(selectedEntity->getId(), "tdme.leveleditor.") == false) {
			auto sceneEntity = scene.getEntity(selectedEntity->getId());
			auto preset = sceneEntity->getProperty("preset");
			sceneEditorScreenController->setEntityProperties(preset != nullptr ? preset->getValue() : "", sceneEntity, "");
			sceneEditorScreenController->setEntityReflectionsEnvironmentMappings(scene, sceneEntity->getReflectionEnvironmentMappingId());
		} else {
			sceneEditorScreenController->unsetEntityData();
			sceneEditorScreenController->unsetEntityTransformations();
			sceneEditorScreenController->unsetEntityProperties();
			sceneEditorScreenController->unsetEntityReflectionsEnvironmentMappings();
		}
	} else
	if (selectedEntityIds.size() > 1) {
		sceneEditorScreenController->unsetEntityData();
		sceneEditorScreenController->unsetEntityProperties();
		sceneEditorScreenController->unsetEntityReflectionsEnvironmentMappings();
	} else
	if (selectedEntityIds.size() == 0) {
		sceneEditorScreenController->unsetEntityTransformations();
		sceneEditorScreenController->unsetEntityData();
		sceneEditorScreenController->unsetEntityProperties();
		sceneEditorScreenController->unsetEntityReflectionsEnvironmentMappings();
	}
	for (auto i = 0; i < 4; i++) {
		sceneEditorScreenController->setLight(i, scene.getLightAt(i)->getAmbient(), scene.getLightAt(i)->getDiffuse(), scene.getLightAt(i)->getSpecular(), scene.getLightAt(i)->getPosition(), scene.getLightAt(i)->getConstantAttenuation(), scene.getLightAt(i)->getLinearAttenuation(), scene.getLightAt(i)->getQuadraticAttenuation(), scene.getLightAt(i)->getSpotTo(), scene.getLightAt(i)->getSpotDirection(), scene.getLightAt(i)->getSpotExponent(), scene.getLightAt(i)->getSpotCutOff(), scene.getLightAt(i)->isEnabled());
	}
	updateGUITransformationsElements();
}

void LevelEditorView::updateGUITransformationsElements() {
	if (selectedEntityIds.size() == 1) {
		auto selectedEntity = engine->getEntity(selectedEntityIds[0]);
		if (selectedEntity != nullptr && StringTools::startsWith(selectedEntity->getId(), "tdme.leveleditor.") == false) {
			auto sceneEntity = scene.getEntity(selectedEntity->getId());
			sceneEditorScreenController->setEntityTransformations(
				selectedEntity->getTranslation(),
				selectedEntity->getScale(),
				selectedEntity->getRotationAngle(scene.getRotationOrder()->getAxisXIndex()),
				selectedEntity->getRotationAngle(scene.getRotationOrder()->getAxisYIndex()),
				selectedEntity->getRotationAngle(scene.getRotationOrder()->getAxisZIndex()),
				(sceneEntity->getPrototype()->getType()->getGizmoTypeMask() & Gizmo::GIZMOTYPE_ROTATE) == 0
			);
			Vector3 objectCenter;
			if (sceneEntity->getPrototype()->getModel() != nullptr) {
				BoundingBox bv;
				bv.fromBoundingVolumeWithTransformations(sceneEntity->getPrototype()->getModel()->getBoundingBox(), sceneEntity->getTransformations());
				objectCenter = bv.getCenter();
			} else {
				objectCenter = sceneEntity->getTransformations().getTranslation();
			}
			sceneEditorScreenController->setEntityData(sceneEntity->getId(), sceneEntity->getDescription(), sceneEntity->getPrototype()->getName(), objectCenter);
		}
	} else
	if (selectedEntityIds.size() > 1) {
		sceneEditorScreenController->setEntityTransformations(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), 0.0f, 0.0f, 0.0f, false);
	}
}

void LevelEditorView::setEntityListBox()
{
	sceneEditorScreenController->setEntityListbox(scene);
}

void LevelEditorView::unselectLightPresets()
{
	sceneEditorScreenController->unselectLightPresets();
}

void LevelEditorView::loadSettings()
{
	try {
		Properties settings;
		settings.load("settings", "leveleditor.properties");
		gridEnabled = settings.get("grid.enabled", "false") == "true";
		gridY = Float::parseFloat(settings.get("grid.y", "0.0"));
		snappingEnabled = settings.get("snapping.enabled", "false") == "true";
		snappingX = Float::parseFloat(settings.get("snapping.x", "1.0"));
		snappingZ = Float::parseFloat(settings.get("snapping.z", "1.0"));
		sceneEditorScreenController->getMapPath()->setPath(settings.get("map.path", "."));
		TDMESceneEditor::getInstance()->getSceneEditorLibraryScreenController()->setModelPath(settings.get("model.path", "."));
	} catch (Exception& exception) {
		Console::print(string("LevelEditorView::loadSettings(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void LevelEditorView::initialize()
{
	try {
		sceneEditorScreenController = new SceneEditorScreenController(this);
		sceneEditorScreenController->initialize();
		sceneEditorScreenController->getScreenNode()->setInputEventHandler(this);
		engine->getGUI()->addScreen(sceneEditorScreenController->getScreenNode()->getId(), sceneEditorScreenController->getScreenNode());
	} catch (Exception& exception) {
		Console::print(string("LevelEditorView::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	loadSettings();
	sceneEditorScreenController->setGrid(gridEnabled, gridY);
	sceneEditorScreenController->setSnapping(snappingEnabled, snappingX, snappingZ);
	sceneEditorScreenController->setSceneProperties(scene, "");
	sceneEditorScreenController->setEntityPresetIds(ScenePropertyPresets::getInstance()->getEntityPropertiesPresets());
	sceneEditorScreenController->setLightPresetsIds(ScenePropertyPresets::getInstance()->getLightPresets());
	updateGUIElements();
	auto light0 = engine->getLightAt(0);
	light0->setAmbient(Color4(0.7f, 0.7f, 0.7f, 1.0f));
	light0->setDiffuse(Color4(0.3f, 0.3f, 0.3f, 1.0f));
	light0->setSpecular(Color4(1.0f, 1.0f, 1.0f, 1.0f));
	light0->setPosition(Vector4(0.0f, 20000.0f, 0.0f, 1.0f));
	light0->setSpotDirection(Vector3(0.0f, 0.0f, 0.0f).sub(Vector3(light0->getPosition().getX(), light0->getPosition().getY(), light0->getPosition().getZ())).normalize());
	light0->setConstantAttenuation(0.5f);
	light0->setLinearAttenuation(0.0f);
	light0->setQuadraticAttenuation(0.0f);
	light0->setSpotExponent(0.0f);
	light0->setSpotCutOff(180.0f);
	light0->setEnabled(true);
	auto cam = engine->getCamera();
	cam->setZNear(0.1f);
	cam->setZFar(150.0f);
	cam->setLookAt(scene.getCenter());
	gridCenter.set(cam->getLookAt());
	camLookAt.set(engine->getCamera()->getLookAt());
}

void LevelEditorView::activate()
{
	engine->reset();
	engine->setPartition(new PartitionOctTree());
	engine->setShadowMapLightEyeDistanceScale(1.0f);
	engine->getGUI()->resetRenderScreens();
	engine->getGUI()->addRenderScreen(sceneEditorScreenController->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(TDMESceneEditor::getInstance()->getSceneEditorLibraryScreenController()->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(popUps->getFileDialogScreenController()->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(popUps->getInfoDialogScreenController()->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(popUps->getProgressBarScreenController()->getScreenNode()->getId());
	TDMESceneEditor::getInstance()->getSceneEditorLibraryScreenController()->setPrototypeLibrary();
	auto light0 = engine->getLightAt(0);
	light0->setAmbient(Color4(0.7f, 0.7f, 0.7f, 1.0f));
	light0->setDiffuse(Color4(0.3f, 0.3f, 0.3f, 1.0f));
	light0->setSpecular(Color4(1.0f, 1.0f, 1.0f, 1.0f));
	light0->setPosition(Vector4(0.0f, 20000.0f, 0.0f, 1.0f));
	light0->setSpotDirection(Vector3(0.0f, 0.0f, 0.0f).sub(Vector3(light0->getPosition().getX(), light0->getPosition().getY(), light0->getPosition().getZ())).normalize());
	light0->setConstantAttenuation(0.5f);
	light0->setLinearAttenuation(0.0f);
	light0->setQuadraticAttenuation(0.0f);
	light0->setSpotExponent(0.0f);
	light0->setSpotCutOff(180.0f);
	light0->setEnabled(true);
	auto cam = engine->getCamera();
	cam->setZNear(0.1f);
	cam->setZFar(150.0f);
	loadScene();
}

void LevelEditorView::deactivate()
{
	camLookAt.set(engine->getCamera()->getLookAt());
}

void LevelEditorView::storeSettings()
{
	try {
		Properties settings;
		settings.put("grid.enabled", gridEnabled == true ? "true" : "false");
		settings.put("grid.y", to_string(gridY));
		settings.put("snapping.enabled", snappingEnabled == true ? "true" : "false");
		settings.put("snapping.x", to_string(snappingX));
		settings.put("snapping.z", to_string(snappingZ));
		settings.put("map.path", sceneEditorScreenController->getMapPath()->getPath());
		settings.put("model.path", TDMESceneEditor::getInstance()->getSceneEditorLibraryScreenController()->getModelPath());
		settings.store("settings", "leveleditor.properties");
	} catch (Exception& exception) {
		Console::print(string("LevelEditorView::storeSettings(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void LevelEditorView::dispose()
{
	Engine::getInstance()->reset();
	storeSettings();
}

void LevelEditorView::setHighlightEntityColorEffect(Entity* object)
{
	auto red = objectColors["red"];
	object->setEffectColorAdd(Color4(red->colorAddR, red->colorAddG, red->colorAddB, 0.0f));
	object->setEffectColorMul(Color4(red->colorMulR, red->colorMulG, red->colorMulB, 1.0f));
}

void LevelEditorView::setStandardEntityColorEffect(Entity* object)
{
	auto color = objectColors["none"];
	object->setEffectColorAdd(Color4(color->colorAddR, color->colorAddG, color->colorAddB, 0.0f));
	object->setEffectColorMul(Color4(color->colorMulR, color->colorMulG, color->colorMulB, 1.0f));
	auto sceneEntity = scene.getEntity(object->getId());
	if (sceneEntity == nullptr) return;
	auto colorProperty = sceneEntity->getProperty("object.color");
	if (colorProperty == nullptr) colorProperty = sceneEntity->getPrototype()->getProperty("object.color");
	if (colorProperty != nullptr) {
		auto objectColorIt = objectColors.find(colorProperty->getValue());
		auto objectColor = objectColorIt != objectColors.end() ? objectColorIt->second : nullptr;
		if (objectColor != nullptr) {
			object->setEffectColorAdd(Color4(object->getEffectColorAdd().getRed() + objectColor->colorAddR, object->getEffectColorAdd().getGreen() + objectColor->colorAddG, object->getEffectColorAdd().getBlue() + objectColor->colorAddB, 0.0f));
			object->setEffectColorMul(Color4(object->getEffectColorMul().getRed() * objectColor->colorMulR, object->getEffectColorMul().getGreen() * objectColor->colorMulG, object->getEffectColorMul().getBlue() * objectColor->colorMulB, 1.0f));
		}
	}
}

void LevelEditorView::resetEntity(Entity* entity) {
	if (entity == nullptr) return;
	setStandardEntityColorEffect(entity);
	auto sceneEntity = scene.getEntity(entity->getId());
	if (sceneEntity == nullptr) return;
	if (sceneEntity->getPrototype()->getType()->hasNonEditScaleDownMode() == false) return;
	entity->fromTransformations(sceneEntity->getTransformations());
	entity->setScale(
		sceneEntity->getPrototype()->getType()->getNonEditScaleDownModeDimension().
		clone().
		scale(
			Vector3(
				1.0f / (sceneEntity->getTransformations().getScale().getX() * entity->getBoundingBox()->getDimensions().getX()),
				1.0f / (sceneEntity->getTransformations().getScale().getY() * entity->getBoundingBox()->getDimensions().getY()),
				1.0f / (sceneEntity->getTransformations().getScale().getZ() * entity->getBoundingBox()->getDimensions().getZ())
			)
		)
	);
	entity->update();
}

void LevelEditorView::loadScene()
{
	removeGizmo();
	removeGrid();
	engine->reset();
	selectedEntityIds.clear();
	selectedEntityIdsById.clear();
	SceneConnector::setLights(engine, scene, Vector3());
	SceneConnector::addScene(engine, scene, true, true, true, true);
	setEntityListBox();
	unselectLightPresets();
	updateGrid();
	updateSky();
}

void LevelEditorView::updateGrid()
{
	if (gridEnabled == false) return;

	string entityId = "tdme.leveleditor.grid";
	auto entity = engine->getEntity(entityId);
	if (entity == nullptr) {
		entity = new Object3D(entityId, levelEditorGround);
		entity->setFrustumCulling(false);
		entity->addRotation(scene.getRotationOrder()->getAxis0(), 0.0f);
		entity->addRotation(scene.getRotationOrder()->getAxis1(), 0.0f);
		entity->addRotation(scene.getRotationOrder()->getAxis2(), 0.0f);
		entity->setTranslation(
			Vector3(
				-5000.0f,
				gridY - 0.05f,
				-5000.0f
			)
		);
		entity->setEnabled(true);
		entity->setPickable(true);
		entity->update();
		auto selectedEntityIdsByIdIt = selectedEntityIdsById.find(entity->getId());
		if (selectedEntityIdsByIdIt != selectedEntityIdsById.end()) {
			setHighlightEntityColorEffect(entity);
		} else {
			setStandardEntityColorEffect(entity);
		}
		engine->addEntity(entity);
	}
}

void LevelEditorView::removeGrid()
{
	engine->removeEntity("tdme.leveleditor.grid");
}

Model* LevelEditorView::createLevelEditorGroundPlateModel()
{
	auto groundPlate = new Model("tdme.leveleditor.grid", "tdme.leveleditor.grid", UpVector::Y_UP, RotationOrder::XYZ, new BoundingBox(Vector3(0.0f, -0.01f, 0.0f), Vector3(10000.0f, +0.01f, 10000.0f)));
	auto groundPlateMaterial = new Material("ground");
	groundPlateMaterial->setSpecularMaterialProperties(new SpecularMaterialProperties());
	groundPlateMaterial->getSpecularMaterialProperties()->setDiffuseColor(
		Color4(
			groundPlateMaterial->getSpecularMaterialProperties()->getDiffuseColor().getRed(),
			groundPlateMaterial->getSpecularMaterialProperties()->getDiffuseColor().getGreen(),
			groundPlateMaterial->getSpecularMaterialProperties()->getDiffuseColor().getBlue(),
			0.75f
		)
	);
	groundPlateMaterial->getSpecularMaterialProperties()->setDiffuseTexture("resources/engine/tools/leveleditor/textures", "groundplate.png");
	groundPlateMaterial->getSpecularMaterialProperties()->setSpecularColor(Color4(0.0f, 0.0f, 0.0f, 1.0f));
	groundPlate->getMaterials()["ground"] = groundPlateMaterial;
	auto groundNode = new Node(groundPlate, nullptr, "ground", "ground");
	vector<Vector3> groundVertices;
	groundVertices.push_back(Vector3(0.0f, 0.0f, 0.0f));
	groundVertices.push_back(Vector3(0.0f, 0.0f, 10000.0f));
	groundVertices.push_back(Vector3(10000.0f, 0.0f, 10000.0f));
	groundVertices.push_back(Vector3(10000.0f, 0.0f, 0.0f));
	vector<Vector3> groundNormals;
	groundNormals.push_back(Vector3(0.0f, 1.0f, 0.0f));
	vector<TextureCoordinate> groundTextureCoordinates;
	groundTextureCoordinates.push_back(TextureCoordinate(0.0f, 10000.0f));
	groundTextureCoordinates.push_back(TextureCoordinate(0.0f, 0.0f));
	groundTextureCoordinates.push_back(TextureCoordinate(10000.0f, 0.0f));
	groundTextureCoordinates.push_back(TextureCoordinate(10000.0f, 10000.0f));
	vector<Face> groundFacesGround;
	groundFacesGround.push_back(Face(groundNode, 0, 1, 2, 0, 0, 0, 0, 1, 2));
	groundFacesGround.push_back(Face(groundNode, 2, 3, 0, 0, 0, 0, 2, 3, 0));
	FacesEntity nodeFacesEntityGround(groundNode, "tdme.leveleditor.grid.facesentity");
	nodeFacesEntityGround.setMaterial(groundPlateMaterial);
	nodeFacesEntityGround.setFaces(groundFacesGround);
	vector<FacesEntity> nodeFacesEntities;
	nodeFacesEntities.push_back(nodeFacesEntityGround);
	groundNode->setVertices(groundVertices);
	groundNode->setNormals(groundNormals);
	groundNode->setTextureCoordinates(groundTextureCoordinates);
	groundNode->setFacesEntities(nodeFacesEntities);
	groundPlate->getNodes()[groundNode->getId()] = groundNode;
	groundPlate->getSubNodes()[groundNode->getId()] = groundNode;
	ModelTools::prepareForIndexedRendering(groundPlate);
	return groundPlate;
}

bool LevelEditorView::entityDataApply(const string& name, const string& description)
{
	if (selectedEntityIds.size() != 1) return false;

	auto selectedEntity = engine->getEntity(selectedEntityIds[0]);
	if (selectedEntity == nullptr || StringTools::startsWith(selectedEntity->getId(), "tdme.leveleditor.")) return false;

	auto sceneEntity = scene.getEntity(selectedEntity->getId());
	if (sceneEntity == nullptr) return false;

	sceneEntity->setDescription(description);
	if (sceneEntity->getId() != name) {
		if (engine->getEntity(name) != nullptr) return false;
		auto oldId = sceneEntity->getId();
		scene.removeEntity(sceneEntity->getId());
		engine->removeEntity(sceneEntity->getId());
		selectedEntityIds.clear();
		selectedEntityIdsById.clear();
		sceneEntity->setId(name);
		scene.addEntity(sceneEntity);
		auto entity = SceneConnector::createEntity(sceneEntity);
		if (entity != nullptr) {
			setHighlightEntityColorEffect(entity);
			selectedEntityIds.push_back(entity->getId());
			selectedEntityIdsById.insert(entity->getId());
			sceneEditorScreenController->setEntityListbox(scene);
			entity->setPickable(true);
			engine->addEntity(entity);
		}
	}
	sceneEntity->setDescription(description);
	return true;
}

void LevelEditorView::setPlaceEntityMode() {
	placeEntityMode = true;
	placeEntityValid = false;
}

void LevelEditorView::unsetPlaceEntityMode() {
	placeEntityMode = false;
	placeEntityValid = false;
	engine->removeEntity("tdme.leveleditor.placeentity");
}

void LevelEditorView::placeEntity()
{
	Transformations sceneEntityTransformations;
	sceneEntityTransformations.setTranslation(placeEntityTranslation);
	sceneEntityTransformations.setScale(Vector3(1.0f, 1.0f, 1.0f));
	sceneEntityTransformations.setPivot(selectedPrototype->getPivot());
	sceneEntityTransformations.addRotation(scene.getRotationOrder()->getAxis0(), 0.0f);
	sceneEntityTransformations.addRotation(scene.getRotationOrder()->getAxis1(), 0.0f);
	sceneEntityTransformations.addRotation(scene.getRotationOrder()->getAxis2(), 0.0f);
	sceneEntityTransformations.setRotationAngle(scene.getRotationOrder()->getAxisYIndex(), placeEntityYRotation * 90.0f);
	sceneEntityTransformations.update();
	for (auto i = 0; i < scene.getEntityCount(); i++) {
		auto sceneEntity = scene.getEntityAt(i);
		if (sceneEntity->getPrototype() == selectedPrototype && sceneEntity->getTransformations().getTranslation().equals(sceneEntityTransformations.getTranslation())) {
			return;
		}
	}
	auto sceneEntity = new SceneEntity(
		selectedPrototype->getName() + "_" + to_string(scene.allocateEntityId()),
		"",
		sceneEntityTransformations,
		selectedPrototype
	);
	scene.addEntity(sceneEntity);
	auto entity = SceneConnector::createEntity(sceneEntity);
	if (entity != nullptr) {
		resetEntity(entity);
		entity->setPickable(true);
		engine->addEntity(entity);
	}
	sceneEditorScreenController->setEntityListbox(scene);
	scene.update();
	updateGUIElements();
}

void LevelEditorView::removeEntities()
{
	removeGizmo();
	vector<Entity*> entitiesToRemove;
	for (auto selectedEntityId: selectedEntityIds) {
		Entity* selectedEntity = engine->getEntity(selectedEntityId);
		if (selectedEntity != nullptr && StringTools::startsWith(selectedEntity->getId(), "tdme.leveleditor.") == false) {
			scene.removeEntity(selectedEntity->getId());
			engine->removeEntity(selectedEntity->getId());
			entitiesToRemove.push_back(selectedEntity);
		}
	}
	for (auto entityToRemove: entitiesToRemove) {
		selectedEntityIds.erase(remove(selectedEntityIds.begin(), selectedEntityIds.end(), entityToRemove->getId()), selectedEntityIds.end());
		auto selectedEntityIdsByIdIt = selectedEntityIdsById.find(entityToRemove->getId());
		if (selectedEntityIdsByIdIt != selectedEntityIdsById.end()) {
			selectedEntityIdsById.erase(selectedEntityIdsByIdIt);
		}
	}
	scene.update();
	sceneEditorScreenController->setEntityListbox(scene);
	updateGUIElements();
}

void LevelEditorView::colorEntities()
{
	if (selectedEntityIds.size() == 0)
		return;

	for (auto selectedEntityId: selectedEntityIds) {
		auto selectedEntity = engine->getEntity(selectedEntityId);
		auto sceneEntity = scene.getEntity(selectedEntityId);
		if (sceneEntity == nullptr) continue;
		auto color = OBJECTCOLOR_NAMES[0];
		auto colorProperty = sceneEntity->getProperty("object.color");
		if (colorProperty == nullptr) {
			sceneEntity->addProperty("object.color", color);
		} else {
			color = colorProperty->getValue();
			for (auto i = 0; i < OBJECTCOLOR_NAMES.size(); i++) {
				if (StringTools::equalsIgnoreCase(color, OBJECTCOLOR_NAMES[i]) == true) {
					color = OBJECTCOLOR_NAMES[(i + 1) % OBJECTCOLOR_NAMES.size()];
					break;
				}
			}
			if (color == "none") {
				sceneEntity->removeProperty("object.color");
			} else {
				sceneEntity->updateProperty(colorProperty->getName(), "object.color", color);
			}
		}
		setStandardEntityColorEffect(selectedEntity);
		setHighlightEntityColorEffect(selectedEntity);
	}

	if (selectedEntityIds.size() == 1) {
		auto selectedEntity = engine->getEntity(selectedEntityIds[0]);
		if (selectedEntity != nullptr && StringTools::startsWith(selectedEntity->getId(), "tdme.leveleditor.") == false) {
			auto sceneEntity = scene.getEntity(selectedEntity->getId());
			auto preset = sceneEntity->getProperty("preset");
			sceneEditorScreenController->setEntityProperties(preset != nullptr ? preset->getValue() : "", sceneEntity, "");
		} else {
			sceneEditorScreenController->unsetEntityProperties();
		}
	} else
	if (selectedEntityIds.size() > 1) {
		sceneEditorScreenController->unsetEntityProperties();
	}
}

void LevelEditorView::centerEntity()
{
	if (selectedEntityIds.size() == 0) {
		return;
	}
	Vector3 center;
	for (auto selectedEntityId: selectedEntityIds) {
		auto selectedEntity = engine->getEntity(selectedEntityId);
		if (selectedEntity == nullptr) continue;
		center.add(selectedEntity->getBoundingBoxTransformed()->getMin().clone().add(selectedEntity->getBoundingBoxTransformed()->getMax()).scale(0.5f));
	}
	engine->getCamera()->setLookAt(center.scale(1.0f / selectedEntityIds.size()));
}

void LevelEditorView::entityTranslationApply(float x, float y, float z)
{
	if (selectedEntityIds.size() == 0)
		return;

	if (selectedEntityIds.size() == 1) {
		auto selectedEntity = engine->getEntity(selectedEntityIds[0]);
		if (selectedEntity == nullptr) return;
		auto sceneEntity = scene.getEntity(selectedEntity->getId());
		if (sceneEntity == nullptr) return;

		sceneEntity->getTransformations().setTranslation(Vector3(x, y, z));
		sceneEntity->getTransformations().update();
		selectedEntity->fromTransformations(sceneEntity->getTransformations());
	} else
	if (selectedEntityIds.size() > 1) {
		for (auto selectedEntityId: selectedEntityIds) {
			auto selectedEntity = engine->getEntity(selectedEntityId);
			if (selectedEntity == nullptr) continue;
			auto sceneEntity = scene.getEntity(selectedEntity->getId());
			if (sceneEntity == nullptr) continue;
			sceneEntity->getTransformations().setTranslation(
				sceneEntity->getTransformations().getTranslation().clone().add(Vector3(x, y, z))
			);
			sceneEntity->getTransformations().update();
			selectedEntity->fromTransformations(sceneEntity->getTransformations());
		}
		sceneEditorScreenController->setEntityTransformations(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), 0.0f, 0.0f, 0.0f, false);
	}
	scene.update();
	updateGizmo();
	updateGUIElements();
}

void LevelEditorView::entityScaleApply(float x, float y, float z)
{
	if (selectedEntityIds.size() == 0)
		return;

	if (selectedEntityIds.size() == 1) {
		auto selectedEntity = engine->getEntity(selectedEntityIds[0]);
		if (selectedEntity == nullptr) return;
		auto sceneEntity = scene.getEntity(selectedEntity->getId());
		if (sceneEntity == nullptr) return;

		sceneEntity->getTransformations().setScale(Vector3(x, y, z));
		sceneEntity->getTransformations().update();
		selectedEntity->fromTransformations(sceneEntity->getTransformations());
	} else
	if (selectedEntityIds.size() > 1) {
		for (auto selectedEntityId: selectedEntityIds) {
			auto selectedEntity = engine->getEntity(selectedEntityId);
			if (selectedEntity == nullptr) continue;
			auto sceneEntity = scene.getEntity(selectedEntity->getId());
			if (sceneEntity == nullptr) continue;

			sceneEntity->getTransformations().setScale(sceneEntity->getTransformations().getScale().clone().scale(Vector3(x, y, z)));
			sceneEntity->getTransformations().update();
			selectedEntity->fromTransformations(sceneEntity->getTransformations());
		}
		sceneEditorScreenController->setEntityTransformations(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), 0.0f, 0.0f, 0.0f, false);
	}
	scene.update();
	updateGizmo();
	updateGUIElements();
}

void LevelEditorView::entityRotationsApply(float x, float y, float z)
{
	if (selectedEntityIds.size() == 0)
		return;

	if (selectedEntityIds.size() == 1) {
		auto selectedEntity = engine->getEntity(selectedEntityIds[0]);
		if (selectedEntity == nullptr) return;
		auto sceneEntity = scene.getEntity(selectedEntity->getId());
		if (sceneEntity == nullptr) return;
		sceneEntity->getTransformations().getRotation(scene.getRotationOrder()->getAxisXIndex()).setAngle(x);
		sceneEntity->getTransformations().getRotation(scene.getRotationOrder()->getAxisYIndex()).setAngle(y);
		sceneEntity->getTransformations().getRotation(scene.getRotationOrder()->getAxisZIndex()).setAngle(z);
		sceneEntity->getTransformations().update();
		selectedEntity->fromTransformations(sceneEntity->getTransformations());
	} else
	if (selectedEntityIds.size() > 1) {
		for (auto selectedEntityId: selectedEntityIds) {
			auto selectedEntity = engine->getEntity(selectedEntityId);
			if (selectedEntity == nullptr) continue;
			auto sceneEntity = scene.getEntity(selectedEntity->getId());
			if (sceneEntity == nullptr) continue;
			if ((sceneEntity->getPrototype()->getType()->getGizmoTypeMask() & Gizmo::GIZMOTYPE_ROTATE) == Gizmo::GIZMOTYPE_ROTATE) {
				sceneEntity->getTransformations().getRotation(scene.getRotationOrder()->getAxisXIndex()).setAngle(sceneEntity->getTransformations().getRotation(scene.getRotationOrder()->getAxisXIndex()).getAngle() + x);
				sceneEntity->getTransformations().getRotation(scene.getRotationOrder()->getAxisYIndex()).setAngle(sceneEntity->getTransformations().getRotation(scene.getRotationOrder()->getAxisYIndex()).getAngle() + y);
				sceneEntity->getTransformations().getRotation(scene.getRotationOrder()->getAxisZIndex()).setAngle(sceneEntity->getTransformations().getRotation(scene.getRotationOrder()->getAxisZIndex()).getAngle() + z);
			}
			sceneEntity->getTransformations().update();
			selectedEntity->fromTransformations(sceneEntity->getTransformations());
		}
		sceneEditorScreenController->setEntityTransformations(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), 0.0f, 0.0f, 0.0f, false);
	}
	scene.update();
	updateGizmo();
	updateGUIElements();
}

bool LevelEditorView::scenePropertySave(const string& oldName, const string& name, const string& value)
{
	if (scene.updateProperty(oldName, name, value) == true) {
		sceneEditorScreenController->setSceneProperties(scene, name);
		return true;
	}
	return false;
}

bool LevelEditorView::scenePropertyAdd()
{
	if (scene.addProperty("new.property", "new.value")) {
		sceneEditorScreenController->setSceneProperties(scene, "new.property");
		return true;
	}
	return false;
}

bool LevelEditorView::scenePropertyRemove(const string& name)
{
	auto idx = scene.getPropertyIndex(name);
	if (idx != -1 && scene.removeProperty(name) == true) {
		auto property = scene.getPropertyByIndex(idx);
		if (property == nullptr) {
			property = scene.getPropertyByIndex(idx - 1);
		}
		sceneEditorScreenController->setSceneProperties(scene, property == nullptr ? "" : property->getName());
		return true;
	}
	return false;
}

bool LevelEditorView::entityPropertyRemove(const string& name)
{
	if (selectedEntityIds.size() != 1) return false;

	auto selectedEntity = engine->getEntity(selectedEntityIds[0]);
	if (selectedEntity == nullptr) return false;
	auto sceneEntity = scene.getEntity(selectedEntity->getId());
	if (sceneEntity == nullptr) return false;

	auto idx = sceneEntity->getPropertyIndex(name);
	if (idx != -1 && sceneEntity->removeProperty(name) == true) {
		auto property = sceneEntity->getPropertyByIndex(idx);
		if (property == nullptr) {
			property = sceneEntity->getPropertyByIndex(idx - 1);
		}
		sceneEditorScreenController->setEntityProperties("", sceneEntity, property == nullptr ? "" : property->getName());
		return true;
	}
	return false;
}

void LevelEditorView::entityPropertiesPreset(const string& presetId)
{
	if (selectedEntityIds.size() != 1) return;

	auto selectedEntity = engine->getEntity(selectedEntityIds[0]);
	if (selectedEntity == nullptr) return;
	auto sceneEntity = scene.getEntity(selectedEntity->getId());
	if (sceneEntity == nullptr) return;

	sceneEntity->clearProperties();
	auto& objectPropertiesPresets = ScenePropertyPresets::getInstance()->getEntityPropertiesPresets();
	const vector<PrototypeProperty*>* objectPropertyPresetVector = nullptr;
	auto objectPropertyPresetVectorIt = objectPropertiesPresets.find(presetId);
	if (objectPropertyPresetVectorIt != objectPropertiesPresets.end()) {
		objectPropertyPresetVector = &objectPropertyPresetVectorIt->second;
	}
	if (objectPropertyPresetVector != nullptr) {
		for (auto objectPropertyPreset: *objectPropertyPresetVector) {
			sceneEntity->addProperty(objectPropertyPreset->getName(), objectPropertyPreset->getValue());
		}
	}
	sceneEditorScreenController->setEntityProperties(presetId, sceneEntity, "");
}

bool LevelEditorView::entityPropertySave(const string& oldName, const string& name, const string& value)
{
	if (selectedEntityIds.size() != 1) return false;

	auto selectedEntity = engine->getEntity(selectedEntityIds[0]);
	if (selectedEntity == nullptr) return false;
	auto sceneEntity = scene.getEntity(selectedEntity->getId());
	if (sceneEntity == nullptr) return false;

	if (sceneEntity->updateProperty(oldName, name, value) == true) {
		sceneEditorScreenController->setEntityProperties("", sceneEntity, name);
		return true;
	}
	return false;
}

bool LevelEditorView::entityPropertyAdd()
{
	if (selectedEntityIds.size() != 1) return false;

	auto selectedEntity = engine->getEntity(selectedEntityIds[0]);
	if (selectedEntity == nullptr) return false;
	auto sceneEntity = scene.getEntity(selectedEntity->getId());
	if (sceneEntity == nullptr) return false;

	if (sceneEntity->addProperty("new.property", "new.value")) {
		sceneEditorScreenController->setEntityProperties("", sceneEntity, "new.property");
		return true;
	}
	return false;
}

void LevelEditorView::loadScene(const string& path, const string& file)
{
	engine->reset();
	selectedPrototype = nullptr;
	try {
		bool haveModelFile = false;
		for (auto &modelExtension: ModelReader::getModelExtensions()) {
			if (StringTools::endsWith(StringTools::toLowerCase(file), "." + modelExtension) == true) {
				haveModelFile = true;
				break;
			}
		}

		// progress call back
		class ImportProgressCallback: public ProgressCallback {
		private:
			ProgressBarScreenController* progressBarScreenController;
		public:
			ImportProgressCallback(ProgressBarScreenController* progressBarScreenController): progressBarScreenController(progressBarScreenController) {
			}
			virtual void progress(float value) {
				progressBarScreenController->progress(value);
			}
		};
		popUps->getProgressBarScreenController()->show();
		if (haveModelFile == true) {
			SceneReader::readFromModel(path, file, scene, new ImportProgressCallback(popUps->getProgressBarScreenController()));
		} else {
			SceneReader::read(path, file, scene, new ImportProgressCallback(popUps->getProgressBarScreenController()));
		}
		popUps->getProgressBarScreenController()->close();
		for (auto i = 0; i < scene.getLibrary()->getPrototypeCount(); i++) {
			auto prototype = scene.getLibrary()->getPrototypeAt(i);
			if (prototype->getType()->getBoundingVolumeCount() != 0) prototype->setDefaultBoundingVolumes(prototype->getType()->getBoundingVolumeCount());
		}
		sceneEditorScreenController->setSky(scene);
		sceneEditorScreenController->setSceneProperties(scene, "");
		sceneEditorScreenController->unsetEntityProperties();
		sceneEditorScreenController->unsetEntityTransformations();
		loadScene();
		engine->getCamera()->setLookAt(scene.getCenter());
		camLookRotationX->setAngle(-45.0f);
		camLookRotationX->update();
		camLookRotationY->setAngle(0.0f);
		camLookRotationY->update();
		camScale = 1.0f;
		gridCenter.set(engine->getCamera()->getLookAt());
		reloadEntityLibrary = true;
		updateGUIElements();
	} catch (Exception& exception) {
		sceneEditorScreenController->showErrorPopUp(
			"Warning: Could not load scene file",
			(string(exception.what()))
		);
	}
}

void LevelEditorView::saveScene(const string& pathName, const string& fileName)
{
	try {
		SceneWriter::write(pathName, fileName, scene);
	} catch (Exception& exception) {
		sceneEditorScreenController->showErrorPopUp(
			"Warning: Could not save scene file",
			(string(exception.what()))
		);
	}
	updateGUIElements();
}

void LevelEditorView::copyEntities()
{
	pasteObjects_.clear();
	for (auto selectedEntityId: selectedEntityIds) {
		auto selectedEntity = engine->getEntity(selectedEntityId);
		if (selectedEntity != nullptr && StringTools::startsWith(selectedEntity->getId(), "tdme.leveleditor.") == false) {
			auto sceneEntity = scene.getEntity(selectedEntity->getId());
			if (sceneEntity == nullptr) continue;
			pasteObjects_.push_back(sceneEntity);
		}
	}
}

void LevelEditorView::setPasteMode() {
	pasteMode = true;
	pasteModeValid = false;
}

void LevelEditorView::unsetPasteMode() {
	auto pasteObjectIdx = 0;
	for (auto pasteObject: pasteObjects_) {
		auto pasteModel = pasteObject->getPrototype();
		auto entityId = "tdme.leveleditor.paste." + pasteModel->getName() + "." + to_string(pasteObjectIdx);
		engine->removeEntity(entityId);
		pasteObjectIdx++;
	}
	pasteMode = false;
	pasteModeValid = false;
}

void LevelEditorView::pasteEntities(bool displayOnly)
{
	auto pasteObjectsMinX = Float::MAX_VALUE;
	auto pasteObjectsMinZ = Float::MAX_VALUE;
	auto pasteObjectsMinY = Float::MAX_VALUE;
	for (auto object: pasteObjects_) {
		auto entity = engine->getEntity(object->getId());
		if (entity == nullptr) continue;
		BoundingBox cbv;
		cbv.fromBoundingVolumeWithTransformations(entity->getBoundingBox(), object->getTransformations());
		auto& objectBBMinXYZ = cbv.getMin().getArray();
		if (objectBBMinXYZ[0] < pasteObjectsMinX) pasteObjectsMinX = objectBBMinXYZ[0];
		if (objectBBMinXYZ[1] < pasteObjectsMinY) pasteObjectsMinY = objectBBMinXYZ[1];
		if (objectBBMinXYZ[2] < pasteObjectsMinZ) pasteObjectsMinZ = objectBBMinXYZ[2];
	}
	auto pasteObjectIdx = 0;
	for (auto pasteObject: pasteObjects_) {
		auto pasteModel = pasteObject->getPrototype();
		Transformations sceneEntityTransformations;
		sceneEntityTransformations.fromTransformations(pasteObject->getTransformations());
		auto objectDiffX = pasteObject->getTransformations().getTranslation().getX() - pasteObjectsMinX;
		auto objectDiffY = pasteObject->getTransformations().getTranslation().getY() - pasteObjectsMinY;
		auto objectDiffZ = pasteObject->getTransformations().getTranslation().getZ() - pasteObjectsMinZ;
		sceneEntityTransformations.setTranslation(
			Vector3(
				placeEntityTranslation.getX() + objectDiffX,
				placeEntityTranslation.getY() + objectDiffY,
				placeEntityTranslation.getZ() + objectDiffZ
			)
		);
		sceneEntityTransformations.update();
		if (displayOnly == false) {
			for (auto i = 0; i < scene.getEntityCount(); i++) {
				auto sceneEntity = scene.getEntityAt(i);
				if (sceneEntity->getPrototype() == pasteModel && sceneEntity->getTransformations().getTranslation().equals(sceneEntityTransformations.getTranslation())) {
					continue;
				}
			}
		}
		if (displayOnly == false) {
			//
			auto sceneEntityId = pasteModel->getName() + "_" + to_string(scene.allocateEntityId());
			auto sceneEntity = new SceneEntity(
				sceneEntityId,
				"",
				sceneEntityTransformations,
				pasteModel
			 );
			PrototypeProperties* properties = pasteObject;
			for (int i = 0; i < properties->getPropertyCount(); i++) {
				PrototypeProperty* property = properties->getPropertyByIndex(i);
				sceneEntity->addProperty(property->getName(), property->getValue());
			}
			scene.addEntity(sceneEntity);
			auto entity = SceneConnector::createEntity(pasteModel, sceneEntityId, sceneEntityTransformations);
			if (entity != nullptr) {
				resetEntity(entity);
				entity->setPickable(true);
				engine->addEntity(entity);
			}
		} else {
			auto entityId = "tdme.leveleditor.paste." + pasteModel->getName() + "." + to_string(pasteObjectIdx);
			auto entity = engine->getEntity(entityId);
			if (entity != nullptr) {
				entity->fromTransformations(sceneEntityTransformations);
			} else {
				entity = SceneConnector::createEntity(pasteModel, entityId, sceneEntityTransformations);
				if (entity != nullptr) {
					setStandardEntityColorEffect(entity);
					entity->setPickable(true);
					engine->addEntity(entity);
				}
			}
		}
		pasteObjectIdx++;
	}
	if (displayOnly == false) sceneEditorScreenController->setEntityListbox(scene);
}

void LevelEditorView::computeSpotDirection(int i, const Vector4& position, const Vector3& spotTo)
{
	auto _from = Vector3(position.getX(), position.getY(), position.getZ());
	auto spotDirection = spotTo.clone().sub(_from);
	scene.getLightAt(i)->getPosition().set(position.getX(), position.getY(), position.getZ(), position.getW());
	scene.getLightAt(i)->getSpotTo().set(spotTo.getX(), spotTo.getY(), spotTo.getZ());
	scene.getLightAt(i)->getSpotDirection().set(spotDirection.getX(), spotDirection.getY(), spotDirection.getZ());
	engine->getLightAt(i)->setPosition(Vector4(position.getX(), position.getY(), position.getZ(), position.getW()));
	engine->getLightAt(i)->setSpotDirection(Vector3(spotDirection.getX(), spotDirection.getY(), spotDirection.getZ()));
	sceneEditorScreenController->setLight(i, scene.getLightAt(i)->getAmbient(), scene.getLightAt(i)->getDiffuse(), scene.getLightAt(i)->getSpecular(), scene.getLightAt(i)->getPosition(), scene.getLightAt(i)->getConstantAttenuation(), scene.getLightAt(i)->getLinearAttenuation(), scene.getLightAt(i)->getQuadraticAttenuation(), scene.getLightAt(i)->getSpotTo(), scene.getLightAt(i)->getSpotDirection(), scene.getLightAt(i)->getSpotExponent(), scene.getLightAt(i)->getSpotCutOff(), scene.getLightAt(i)->isEnabled());
}

void LevelEditorView::applyLight(int i, const Color4& ambient, const Color4& diffuse, const Color4& specular, const Vector4& position, float constantAttenuation, float linearAttenuation, float quadraticAttenuation, const Vector3& spotTo, const Vector3& spotDirection, float spotExponent, float spotCutoff, bool enabled)
{
	scene.getLightAt(i)->getAmbient().set(ambient);
	scene.getLightAt(i)->getDiffuse().set(diffuse);
	scene.getLightAt(i)->getSpecular().set(specular);
	scene.getLightAt(i)->getPosition().set(position);
	scene.getLightAt(i)->setConstantAttenuation(constantAttenuation);
	scene.getLightAt(i)->setLinearAttenuation(linearAttenuation);
	scene.getLightAt(i)->setQuadraticAttenuation(quadraticAttenuation);
	scene.getLightAt(i)->getSpotTo().set(spotTo.getX(), spotTo.getY(), spotTo.getZ());
	scene.getLightAt(i)->getSpotDirection().set(spotDirection);
	scene.getLightAt(i)->setSpotExponent(spotExponent);
	scene.getLightAt(i)->setSpotCutOff(spotCutoff);
	scene.getLightAt(i)->setEnabled(enabled);
	engine->getLightAt(i)->setAmbient(Color4(ambient));
	engine->getLightAt(i)->setDiffuse(Color4(diffuse));
	engine->getLightAt(i)->setSpecular(Color4(specular));
	engine->getLightAt(i)->setPosition(Vector4(position));
	engine->getLightAt(i)->setConstantAttenuation(constantAttenuation);
	engine->getLightAt(i)->setLinearAttenuation(linearAttenuation);
	engine->getLightAt(i)->setQuadraticAttenuation(quadraticAttenuation);
	engine->getLightAt(i)->setSpotDirection(spotDirection);
	engine->getLightAt(i)->setSpotExponent(spotExponent);
	engine->getLightAt(i)->setSpotCutOff(spotCutoff);
	engine->getLightAt(i)->setEnabled(enabled);
	sceneEditorScreenController->setLight(i, scene.getLightAt(i)->getAmbient(), scene.getLightAt(i)->getDiffuse(), scene.getLightAt(i)->getSpecular(), scene.getLightAt(i)->getPosition(), scene.getLightAt(i)->getConstantAttenuation(), scene.getLightAt(i)->getLinearAttenuation(), scene.getLightAt(i)->getQuadraticAttenuation(), scene.getLightAt(i)->getSpotTo(), scene.getLightAt(i)->getSpotDirection(), scene.getLightAt(i)->getSpotExponent(), scene.getLightAt(i)->getSpotCutOff(), scene.getLightAt(i)->isEnabled());
}

void LevelEditorView::updateSky() {
	engine->removeEntity("tdme.sky");
	if (scene.getSkyModel() == nullptr) return;
	auto sky = new Object3D("tdme.sky", scene.getSkyModel());
	sky->setRenderPass(Entity::RENDERPASS_NOFRUSTUMCULLING);
	sky->setShader("sky");
	sky->setFrustumCulling(false);
	sky->setTranslation(Vector3(0.0f, 0.0f, 0.0f));
	sky->setScale(scene.getSkyModelScale());
	sky->update();
	sky->setContributesShadows(false);
	sky->setReceivesShadows(false);
	sky->setExcludeEffectPass(Engine::EFFECTPASS_LIGHTSCATTERING);
	engine->addEntity(sky);
}

void LevelEditorView::updateSkyPosition() {
	auto sky = engine->getEntity("tdme.sky");
	if (sky == nullptr) return;
	sky->setTranslation(engine->getCamera()->getLookAt());
	sky->update();
}

void LevelEditorView::applyReflectionEnvironmentMappingId(const string& reflectionEnvironmentMappingId) {
	for (auto& selectedEntityId: selectedEntityIds) {
		auto sceneEntity = scene.getEntity(selectedEntityId);
		if (sceneEntity == nullptr) continue;
		sceneEntity->setReflectionEnvironmentMappingId(reflectionEnvironmentMappingId);
	}
}

void LevelEditorView::updateGizmo() {
	if (selectedEntityIds.size() == 0) {
		removeGizmo();
		return;
	}

	// rotation for gizmo
	Transformations transformations;

	//
	Vector3 gizmoCenter;
	auto objectCount = 0;
	for (auto selectedEntityId: selectedEntityIds) {
		auto selectedEntity = engine->getEntity(selectedEntityId);
		if (selectedEntity != nullptr && StringTools::startsWith(selectedEntity->getId(), "tdme.leveleditor.") == false) {
			auto sceneEntity = scene.getEntity(selectedEntity->getId());
			if (sceneEntity == nullptr) continue;
			gizmoCenter.add(sceneEntity->getTransformations().getTranslation());
			objectCount++;
		}
	}
	if (objectCount == 0) {
		removeGizmo();
		return;
	} else
	if (objectCount == 1) {
		auto selectedSceneEntity = scene.getEntity(selectedEntityIds[0]);
		auto selectedPrototype = selectedSceneEntity != nullptr?selectedSceneEntity->getPrototype():nullptr;
		if (selectedSceneEntity != nullptr) transformations.fromTransformations(selectedSceneEntity->getTransformations());
		setGizmoTypeMask(selectedPrototype->getType()->getGizmoTypeMask());
	} else {
		gizmoCenter.scale(1.0f / objectCount);
	}

	//
	Gizmo::updateGizmo(gizmoCenter, transformations);
}
