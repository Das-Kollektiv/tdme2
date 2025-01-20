#include <tdme/tools/editor/tabviews/SceneEditorTabView.h>

#if defined(_MSC_VER)
	#include <windows.h>
#else
	#include <dlfcn.h>
#endif

#include <memory>
#include <string>
#include <unordered_set>

#include <minitscript/minitscript/Library.h>

#include <agui/agui.h>
#include <agui/gui/events/GUIKeyboardEvent.h>
#include <agui/gui/events/GUIMouseEvent.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/GUI.h>
#include <agui/gui/GUIParser.h>

#include <tdme/tdme.h>
#include <tdme/audio/Audio.h>
#include <tdme/engine/logics/ApplicationClient.h>
#include <tdme/engine/logics/Context.h>
#include <tdme/engine/logics/LogicMinitScript.h>
#include <tdme/engine/logics/MinitScriptLogic.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/prototype/BaseProperty.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/Prototype_Type.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/engine/scene/SceneEntity.h>
#include <tdme/engine/scene/SceneLibrary.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/EntityHierarchy.h>
#include <tdme/engine/EntityPickingFilter.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/Object.h>
#include <tdme/engine/SceneConnector.h>
#include <tdme/engine/Timing.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/misc/CameraInputHandler.h>
#include <tdme/tools/editor/misc/CameraInputHandlerEventHandler.h>
#include <tdme/tools/editor/misc/Gizmo.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/SceneEditorTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Character.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/StringTools.h>

using std::make_unique;
using std::string;
using std::to_string;
using std::unique_ptr;
using std::unordered_set;

using tdme::tools::editor::tabviews::SceneEditorTabView;

using minitscript::minitscript::Library;

using agui::gui::events::GUIKeyboardEvent;
using agui::gui::events::GUIMouseEvent;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::GUI;
using agui::gui::GUIParser;

using tdme::audio::Audio;
using tdme::engine::logics::ApplicationClient;
using tdme::engine::logics::Context;
using tdme::engine::logics::LogicMinitScript;
using tdme::engine::logics::MinitScriptLogic;
using tdme::engine::physics::World;
using tdme::engine::prototype::BaseProperty;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::Prototype_Type;
using tdme::engine::scene::Scene;
using tdme::engine::scene::SceneEntity;
using tdme::engine::scene::SceneLibrary;
using tdme::engine::Camera;
using tdme::engine::Color4;
using tdme::engine::Engine;
using tdme::engine::EntityHierarchy;
using tdme::engine::EntityPickingFilter;
using tdme::engine::Light;
using tdme::engine::Object;
using tdme::engine::SceneConnector;
using tdme::engine::Timing;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::misc::CameraInputHandler;
using tdme::tools::editor::misc::CameraInputHandlerEventHandler;
using tdme::tools::editor::misc::Gizmo;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::SceneEditorTabController;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Action;
using tdme::utilities::Character;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Float;
using tdme::utilities::StringTools;

SceneEditorTabView::SceneEditorTabView(EditorView* editorView, const string& tabId, Scene* scene): Gizmo(nullptr, "le")
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->popUps = editorView->getPopUps();
	engine = unique_ptr<Engine>(Engine::createOffScreenInstance(512, 512, true, true, true));
	engine->setSceneColor(Color4(39.0f / 255.0f, 39.0f / 255.0f, 39.0f / 255.0f, 1.0f));
	engine->setSkyShaderEnabled(true);
	this->scene = unique_ptr<Scene>(scene);
	this->cameraInputHandler = make_unique<CameraInputHandler>(engine.get(), this);
	this->keyControl = false;
	this->keyShift = false;
	this->keyEscape = false;
	this->placeEntityYRotation = 0;
	this->placeEntityMouseX = MOUSE_DOWN_LAST_POSITION_NONE;
	this->placeEntityMouseY = MOUSE_DOWN_LAST_POSITION_NONE;
	this->mouseDragging = false;
	this->pasteMode = false;
	this->pasteModeValid = false;
	this->placeEntityMode = false;
	this->placeEntityValid = false;
	this->snappingX = 0.0f;
	this->snappingZ = 0.0f;
	this->snappingEnabled = false;
	this->gridEnabled = false;
	this->gridY = 0.0f;
	this->gridModel = unique_ptr<Model>(Tools::createGridModel());

	//
	setEngine(engine.get());
	updateLights();

	//
	entityColors["red"] = EntityColor(1.5f, 0.8f, 0.8f, 0.5f, 0.0f, 0.0f);
	entityColors["green"] = EntityColor(0.8f, 1.5f, 0.8f, 0.0f, 0.5f, 0.0f);
	entityColors["blue"] = EntityColor(0.8f, 0.8f, 1.5f, 0.0f, 0.0f, 0.5f);
	entityColors["yellow"] = EntityColor(1.5f, 1.5f, 0.8f, 0.5f, 0.5f, 0.0f);
	entityColors["magenta"] = EntityColor(1.5f, 0.8f, 1.5f, 0.5f, 0.0f, 0.5f);
	entityColors["cyan"] = EntityColor(0.8f, 1.5f, 1.5f, 0.0f, 0.5f, 0.5f);
	entityColors["none"] = EntityColor(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);

	//
	{
		// entity picking filter for no grid
		class PrototypePickingFilterNoGrid: public EntityPickingFilter
		{
		public:
			bool filterEntity(Entity* entity) override {
				return entity->getId() != "tdme.sceneeditor.grid";
			}

			/**
			 * Public constructor
			 * @param SceneEditorTabView scene editor tab view
			 */
			PrototypePickingFilterNoGrid(SceneEditorTabView* sceneEditorTabView): sceneEditorTabView(sceneEditorTabView) {
			}

		private:
			SceneEditorTabView* sceneEditorTabView;
		};
		//
		entityPickingFilterNoGrid = make_unique<PrototypePickingFilterNoGrid>(this);
	}

	//
	{
		// entity picking filter for no placing object
		class PrototypePickingFilterPlacing: public EntityPickingFilter
		{
		public:
			bool filterEntity(Entity* entity) override {
				return
					entity->getId() != "tdme.sceneeditor.placeentity" &&
					StringTools::startsWith(entity->getId(), "tdme.sceneeditor.paste.") == false &&
					StringTools::startsWith(entity->getId(), "le.tdme.gizmo.") == false;
			}

			/**
			 * Public constructor
			 * @param sceneEditorTabView scene editor tab view
			 */
			PrototypePickingFilterPlacing(SceneEditorTabView* sceneEditorTabView): sceneEditorTabView(sceneEditorTabView) {
			}

		private:
			SceneEditorTabView* sceneEditorTabView;
		};
		//
		entityPickingFilterPlacing = make_unique<PrototypePickingFilterPlacing>(this);
	}

	//
	outlinerState.expandedOutlinerParentOptionValues.push_back("scene");
}

SceneEditorTabView::~SceneEditorTabView() {
}

void SceneEditorTabView::handleInputEvents()
{
	// if scene is running, no not do HID input except camera
	if (applicationClient != nullptr) {
		auto gui = engine->getGUI();
		// handle events in GUI
		gui->handleEvents(false);
		// forward HID to logics
		applicationClient->handleHIDEvents(gui->getMouseEvents(), gui->getKeyboardEvents());
		// clear events
		gui->getMouseEvents().clear();
		gui->getKeyboardEvents().clear();
		//
		return;
	}

	//
	auto keyControlX = false;
	auto keyControlC = false;
	auto keyControlV = false;
	auto keyDelete = false;
	for (auto& event: engine->getGUI()->getKeyboardEvents()) {
		if (event.isProcessed() == true) continue;
		if (event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_TYPED) continue;
		auto isKeyDown = event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED;
		if (event.getKeyCode() == KEYBOARD_KEYCODE_LEFT_SHIFT) {
			keyShift = isKeyDown;
			event.setProcessed(true);
		}
		if (event.getKeyCode() == KEYBOARD_KEYCODE_LEFT_CTRL) {
			keyControl = isKeyDown;
			event.setProcessed(true);
		}
		if (event.getKeyCode() == GUIKeyboardEvent::KEYCODE_ESCAPE) {
			keyEscape = isKeyDown;
			event.setProcessed(true);
		}
		if (event.getKeyCode() == GUIKeyboardEvent::KEYCODE_BACKSPACE ||
			event.getKeyCode() == GUIKeyboardEvent::KEYCODE_DELETE) {
			keyDelete = isKeyDown;
			event.setProcessed(true);
		}
		// determine cut, copy, paste
		if (Character::toLowerCase(event.getKeyChar()) == 'x' && keyControl == true) {
			keyControlX = isKeyDown;
			event.setProcessed(true);
		}
		if (Character::toLowerCase(event.getKeyChar()) == 'c' && keyControl == true) {
			keyControlC = isKeyDown;
			event.setProcessed(true);
		}
		if (Character::toLowerCase(event.getKeyChar()) == 'v' && keyControl == true) {
			keyControlV = isKeyDown;
			event.setProcessed(true);
		}
		// handle them
		if (Character::toLowerCase(event.getKeyChar()) == '.' && !isKeyDown == false) {
			placeEntityYRotation = (placeEntityYRotation + 1) % 4;
			event.setProcessed(true);
		}
		if (Character::toLowerCase(event.getKeyChar()) == ',' && !isKeyDown == false) {
			placeEntityYRotation = (placeEntityYRotation + 3) % 4;
			event.setProcessed(true);
		}
		if (Character::toLowerCase(event.getKeyChar()) == '1' && isKeyDown == true) {
			setGizmoType(GIZMOTYPE_ALL);
			updateGizmo();
			event.setProcessed(true);
		}
		if (Character::toLowerCase(event.getKeyChar()) == '2' && isKeyDown == true) {
			setGizmoType(GIZMOTYPE_TRANSLATE);
			updateGizmo();
			event.setProcessed(true);
		}
		if (Character::toLowerCase(event.getKeyChar()) == '3' && isKeyDown == true) {
			setGizmoType(GIZMOTYPE_ROTATE);
			updateGizmo();
			event.setProcessed(true);
		}
		if (Character::toLowerCase(event.getKeyChar()) == '4' && isKeyDown == true) {
			setGizmoType(GIZMOTYPE_SCALE);
			updateGizmo();
			event.setProcessed(true);
		}
	}
	for (auto& event: engine->getGUI()->getMouseEvents()) {
		if ((event.getType() == GUIMouseEvent::MOUSEEVENT_MOVED ||
			event.getType() == GUIMouseEvent::MOUSEEVENT_DRAGGED) &&
			event.getXUnscaled() >= 0 &&
			event.getYUnscaled() >= 0) {
			placeEntityMouseX = event.getXUnscaled();
			placeEntityMouseY = event.getYUnscaled();
		}

		if (event.isProcessed() == true) continue;

		if (event.getButton() == MOUSE_BUTTON_LEFT) {
			if (event.getType() == GUIMouseEvent::MOUSEEVENT_DRAGGED) {
				if (mouseDragging == false) {
					mouseDragging = true;
					mouseDraggingLastEntity = nullptr;
					event.setProcessed(true);
				}
			} else {
				if (mouseDragging == true) {
					mouseDragging = false;
					mouseDraggingLastEntity = nullptr;
					event.setProcessed(true);
				}
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
					if (keyShift == false) unsetPlaceEntityMode(false);
				} else
				if (getGizmoMode() != GIZMOMODE_NONE) {
					for (const auto& selectedEntityId: selectedEntityIds) {
						auto _selectedEntity = engine->getEntity(selectedEntityId);
						if (_selectedEntity == nullptr) continue;
						auto sceneEntity = scene->getEntity(_selectedEntity->getId());
						if (sceneEntity == nullptr) continue;
						auto rotationEuler = _selectedEntity->getRotationsQuaternion().computeMatrix().computeEulerAngles();
						_selectedEntity->setRotationAngle(scene->getRotationOrder()->getAxisXIndex(), rotationEuler[0]);
						_selectedEntity->setRotationAngle(scene->getRotationOrder()->getAxisYIndex(), rotationEuler[1]);
						_selectedEntity->setRotationAngle(scene->getRotationOrder()->getAxisZIndex(), rotationEuler[2]);
						while (_selectedEntity->getRotationCount() > 3) _selectedEntity->removeRotation(_selectedEntity->getRotationCount() - 1);
						_selectedEntity->update();
						sceneEntity->getTransform().setTransform(_selectedEntity->getTransform());
					}
					setGizmoMode(GIZMOMODE_NONE);
					updateGizmo();
				}
				event.setProcessed(true);
			} else
			if (placeEntityMode == false) {
				Node* selectedEntityNode = nullptr;
				Entity* selectedEntity = nullptr;
				if (getGizmoMode() == GIZMOMODE_NONE) selectedEntity = engine->getEntityByMousePosition(event.getXUnscaled(), event.getYUnscaled(), entityPickingFilterNoGrid.get(), &selectedEntityNode);
				if (mouseDragging == true) {
					Vector3 deltaTranslation;
					Vector3 deltaRotation;
					Vector3 absoluteScale;
					if (determineGizmoDeltaTransformations(event.getXUnscaled(), event.getYUnscaled(), deltaTranslation, deltaRotation, absoluteScale) == true) {
						auto gizmoEntity = getGizmoObject();
						if (gizmoEntity != nullptr) {
							for (const auto& selectedEntityId: selectedEntityIds) {
								auto _selectedEntity = engine->getEntity(selectedEntityId);
								if (_selectedEntity != nullptr && StringTools::startsWith(_selectedEntity->getId(), "tdme.sceneeditor.") == false) {
									auto sceneEntity = scene->getEntity(_selectedEntity->getId());
									if (sceneEntity == nullptr) continue;
									_selectedEntity->setTranslation(_selectedEntity->getTransform().getTranslation().clone().add(deltaTranslation));
									auto scale = _selectedEntity->getScale().clone().scale(absoluteScale);
									if (Math::abs(scale.getX()) < 0.01f) scale.setX(Math::sign(scale.getX()) * 0.01f);
									if (Math::abs(scale.getY()) < 0.01f) scale.setY(Math::sign(scale.getY()) * 0.01f);
									if (Math::abs(scale.getZ()) < 0.01f) scale.setZ(Math::sign(scale.getZ()) * 0.01f);
									if (Math::abs(scale.getX()) > 100.0f) scale.setX(Math::sign(scale.getX()) * 100.0f);
									if (Math::abs(scale.getY()) > 100.0f) scale.setY(Math::sign(scale.getY()) * 100.0f);
									if (Math::abs(scale.getZ()) > 100.0f) scale.setZ(Math::sign(scale.getZ()) * 100.0f);
									_selectedEntity->setScale(scale);
									if ((sceneEntity->getPrototype()->getType()->getGizmoTypeMask() & Gizmo::GIZMOTYPE_ROTATE) == Gizmo::GIZMOTYPE_ROTATE &&
										deltaRotation.computeLengthSquared() > Math::square(Math::EPSILON) * 3.0f) {
										if (_selectedEntity->getRotationCount() == 3) {
											_selectedEntity->addRotation(scene->getRotationOrder()->getAxis0(), 0.0f);
											_selectedEntity->addRotation(scene->getRotationOrder()->getAxis1(), 0.0f);
											_selectedEntity->addRotation(scene->getRotationOrder()->getAxis2(), 0.0f);
										}
										_selectedEntity->setRotationAngle(3 + scene->getRotationOrder()->getAxisXIndex(), _selectedEntity->getRotationAngle(3 + scene->getRotationOrder()->getAxisXIndex()) + deltaRotation[0]);
										_selectedEntity->setRotationAngle(3 + scene->getRotationOrder()->getAxisYIndex(), _selectedEntity->getRotationAngle(3 + scene->getRotationOrder()->getAxisYIndex()) + deltaRotation[1]);
										_selectedEntity->setRotationAngle(3 + scene->getRotationOrder()->getAxisZIndex(), _selectedEntity->getRotationAngle(3 + scene->getRotationOrder()->getAxisZIndex()) + deltaRotation[2]);
									}
									_selectedEntity->update();
								}
							}
							if (selectedEntityIds.size() == 1) {
								auto _selectedEntity = engine->getEntity(selectedEntityIds[0]);
								if (_selectedEntity != nullptr) {
									sceneEditorTabController->updateEntityDetails(_selectedEntity->getTransform());
									setGizmoRotation(_selectedEntity->getTransform());
								}
							} else {
								multipleSelectionTranslation+= deltaTranslation;
								multipleSelectionRotation+= deltaRotation;
								multipleSelectionScale = absoluteScale;
								sceneEditorTabController->updateEntityDetails(multipleSelectionTranslation, multipleSelectionRotation, multipleSelectionScale);
							}
						}
						if (Math::abs(deltaTranslation.getX()) > Math::EPSILON ||
							Math::abs(deltaTranslation.getY()) > Math::EPSILON ||
							Math::abs(deltaTranslation.getZ()) > Math::EPSILON) {
							updateGizmo();
						}
					}
				} else
				if (determineGizmoMode(selectedEntity, selectedEntityNode) == true) {
					// no op
				} else {
					if (selectedEntity != nullptr && scene->getEntity(selectedEntity->getId()) == nullptr) selectedEntity = nullptr;
					if (keyControl == false) {
						vector<Entity*> entitiesToRemove;
						for (const auto& selectedEntityId: selectedEntityIds) {
							auto selectedEntity = engine->getEntity(selectedEntityId);
							if (mouseDragging == true && mouseDraggingLastEntity == selectedEntity) {
								// no op
							} else {
								if (selectedEntity != nullptr) entitiesToRemove.push_back(selectedEntity);
							}
						}
						for (const auto& entityToRemove: entitiesToRemove) {
							selectedEntityIds.erase(remove(selectedEntityIds.begin(), selectedEntityIds.end(), entityToRemove->getId()), selectedEntityIds.end());
							auto selectedEntitiyIdByIdIt = selectedEntityIdsById.find(entityToRemove->getId());
							if (selectedEntitiyIdByIdIt != selectedEntityIdsById.end()) {
								selectedEntityIdsById.erase(selectedEntitiyIdByIdIt);
							}
							sceneEditorTabController->unselectEntity(entityToRemove->getId());
							resetEntity(entityToRemove);
						}
					}
					if (selectedEntity != nullptr) {
						if (selectedEntityIdsById.find(selectedEntity->getId()) == selectedEntityIdsById.end()) {
							selectEntityInternal(selectedEntity);
							selectedEntityIds.push_back(selectedEntity->getId());
							selectedEntityIdsById.insert(selectedEntity->getId());
							sceneEditorTabController->selectEntity(selectedEntity->getId());
						} else {
							resetEntity(selectedEntity);
							selectedEntityIds.erase(remove(selectedEntityIds.begin(), selectedEntityIds.end(), selectedEntity->getId()), selectedEntityIds.end());
							auto selectedEntityIdsByIdIt = selectedEntityIdsById.find(selectedEntity->getId());
							if (selectedEntityIdsByIdIt != selectedEntityIdsById.end()) {
								selectedEntityIdsById.erase(selectedEntityIdsByIdIt);
							}
							sceneEditorTabController->unselectEntity(selectedEntity->getId());
						}
						if (selectedEntityIds.size() == 1) {
							auto sceneEntity = scene->getEntity(selectedEntity->getId());
							if (sceneEntity != nullptr && sceneEntity->getPrototype()->getType()->hasNonEditScaleDownMode() == true) {
								selectedEntity->setTransform(sceneEntity->getTransform());
							}
							setGizmoRotation(selectedEntity->getTransform());
							sceneEditorTabController->setEntityDetails(selectedEntity->getId());
						} else
						if (selectedEntityIds.size() > 1) {
							setGizmoRotation(Transform());
							multipleSelectionTranslation = computeMultipleSelectionPivot();
							multipleSelectionRotation.set(0.0f, 0.0f, 0.0f);
							multipleSelectionScale.set(1.0f, 1.0f, 1.0f);
							sceneEditorTabController->setEntityDetailsMultiple(multipleSelectionTranslation, getSelectedReflectionEnvironmentMappingId());
						}
					}
					mouseDraggingLastEntity = selectedEntity;
					updateGizmo();
				}
				event.setProcessed(true);
			}
		}
	}
	if (keyDelete == true) {
		removeGizmo();
		removeEntities();
	}
	if (keyControlX == true) {
		removeGizmo();
		copyEntities();
		removeEntities();
	}
	if (keyControlC == true) {
		copyEntities();
	}
	if (keyControlV == true) {
		removeGizmo();
		setPasteMode();
	}

	//
	cameraInputHandler->handleInputEvents();
}

void SceneEditorTabView::display()
{
	// if scene is running, no not do HID input except camera
	if (applicationClient != nullptr) {
		//
		sceneEditorTabController->updateInfoText(MutableString(engine->getTiming()->getAvarageFPS()).append(" FPS"));
		//
		applicationClient->update();
		engine->display();
		engine->getGUI()->render();
		//
		return;
	}

	//
	if ((placeEntityMode == true || pasteMode == true) && keyEscape == true) {
		unsetPlaceEntityMode(keyEscape == true);
		unsetPasteMode();
		keyEscape = false;
	}

	{
		auto selectedEngineEntity = engine->getEntity("tdme.sceneeditor.placeentity");
		Vector3 worldCoordinate;
		placeEntityValid = false;
		pasteModeValid = false;
		if ((placeEntityMode == true || pasteMode == true) && engine->getEntityByMousePosition(placeEntityMouseX, placeEntityMouseY, worldCoordinate, entityPickingFilterPlacing.get()) != nullptr) {
			if (placeEntityMode == true) {
				Transform transform;
				transform.setTranslation(worldCoordinate);
				transform.addRotation(scene->getRotationOrder()->getAxis0(), 0.0f);
				transform.addRotation(scene->getRotationOrder()->getAxis1(), 0.0f);
				transform.addRotation(scene->getRotationOrder()->getAxis2(), 0.0f);
				transform.update();
				if (selectedEngineEntity == nullptr && selectedPrototype != nullptr) {
					selectedEngineEntity = createEntity(selectedPrototype, "tdme.sceneeditor.placeentity", transform);
					if (selectedEngineEntity != nullptr) engine->addEntity(selectedEngineEntity);
				}
				if (selectedEngineEntity != nullptr) {
					if (snappingEnabled == true && (snappingX > Math::EPSILON || snappingZ > Math::EPSILON)) {
						if (snappingX > Math::EPSILON) worldCoordinate.setX(static_cast<int>(worldCoordinate.getX() / snappingX) * snappingX);
						if (snappingZ > Math::EPSILON) worldCoordinate.setZ(static_cast<int>(worldCoordinate.getZ() / snappingZ) * snappingZ);
						Vector3 snappedWorldCoordinate;
						if (engine->doRayCasting(worldCoordinate.clone().setY(10000.0f), worldCoordinate.clone().setY(-10000.0f), snappedWorldCoordinate, entityPickingFilterPlacing.get()) != nullptr) {
							worldCoordinate = snappedWorldCoordinate;
						}
					}
					transform.setTranslation(worldCoordinate);
					transform.setRotationAngle(scene->getRotationOrder()->getAxisYIndex(), static_cast<float>(placeEntityYRotation) * 90.0f);
					transform.update();
					selectedEngineEntity->setTransform(transform);
					placeEntityTranslation = transform.getTranslation();
					placeEntityValid = true;
				}
			} else
			if (pasteMode == true) {
				if (snappingEnabled == true && (snappingX > Math::EPSILON || snappingZ > Math::EPSILON)) {
					if (snappingX > Math::EPSILON) worldCoordinate.setX(static_cast<int>(worldCoordinate.getX() / snappingX) * snappingX);
					if (snappingZ > Math::EPSILON) worldCoordinate.setZ(static_cast<int>(worldCoordinate.getZ() / snappingZ) * snappingZ);
					Vector3 snappedWorldCoordinate;
					if (engine->doRayCasting(worldCoordinate.clone().setY(10000.0f), worldCoordinate.clone().setY(-10000.0f), snappedWorldCoordinate, entityPickingFilterPlacing.get()) != nullptr) {
						worldCoordinate = snappedWorldCoordinate;
					}
				}
				placeEntityTranslation = worldCoordinate;
				pasteModeValid = true;
				pasteEntities(true);
			}
		}
	}

	//
	updateGrid();

	//
	sceneEditorTabController->updateInfoText(MutableString(engine->getTiming()->getAvarageFPS()).append(" FPS"));

	//
	engine->display();

	//
	if (needsGizmoUpdate == true) {
		updateGizmo();
		needsGizmoUpdate = false;
	}
}

void SceneEditorTabView::initialize()
{
	try {
		sceneEditorTabController = make_unique<SceneEditorTabController>(this);
		sceneEditorTabController->initialize(editorView->getScreenController()->getScreenNode());
	} catch (Exception& exception) {
		Console::printLine("SceneEditorTabView::initialize(): An error occurred: " + string(exception.what()));
	}
	//
	SceneConnector::setLights(engine.get(), scene.get());
	SceneConnector::addScene(engine.get(), scene.get(), true, true, true, true, true);
	cameraInputHandler->setSceneCenter(scene->getCenter());
	applySkyShaderParameters();
	applyPostProcessingShaderParameters();
	updateGrid();
	// TODO: load settings
}

void SceneEditorTabView::dispose()
{
	shutdownScene();
	engine->dispose();
}

void SceneEditorTabView::updateRendering() {
}

Engine* SceneEditorTabView::getEngine() {
	return engine.get();
}

void SceneEditorTabView::activate() {
	editorView->getScreenController()->enableSceneMenuEntry();
	sceneEditorTabController->setOutlinerAddDropDownContent();
	sceneEditorTabController->setOutlinerContent();
	editorView->getScreenController()->restoreOutlinerState(outlinerState);
	sceneEditorTabController->updateDetails(editorView->getScreenController()->getOutlinerSelection());
}

void SceneEditorTabView::deactivate() {
	editorView->getScreenController()->disableSceneMenuEntry();
	editorView->getScreenController()->storeOutlinerState(outlinerState);
}

void SceneEditorTabView::applySkyShaderParameters() {
	const auto& skyShaderParameters = scene->getSkyShaderParameters();
	for (const auto& parameterName: Engine::getShaderParameterNames("sky")) {
		engine->setShaderParameter("sky", parameterName, skyShaderParameters.getShaderParameter(parameterName));
	}
}

void SceneEditorTabView::applyPostProcessingShaderParameters() {
	//
	engine->resetPostProcessingPrograms();
	//
	for (const auto& shaderId: Engine::getRegisteredShader(Engine::SHADERTYPE_POSTPROCESSING, false)) {
		//
		if (scene->isPostProcessingShaderEnabled(shaderId) == true) {
			engine->addPostProcessingProgram(shaderId);
		}
		//
		for (const auto& parameterName: Engine::getShaderParameterNames(shaderId)) {
			//
			auto parameterDefaults = Engine::getDefaultShaderParameter(shaderId, parameterName);
			if (parameterDefaults == nullptr) {
				continue;
			}
			//
			auto shaderParameters = scene->getPostProcessingShaderParameters(shaderId);
			if (shaderParameters == nullptr) {
				continue;
			}
			//
			engine->setShaderParameter(shaderId, parameterName, shaderParameters->getShaderParameter(parameterName));
		}
	}
}

void SceneEditorTabView::clearScene() {
	//
	SceneConnector::resetEngine(engine.get(), scene.get());
	//
	keyControl = false;
	keyShift = false;
	keyEscape = false;

	placeEntityMode = false;
	placeEntityValid = false;
	mouseDragging = false;
	mouseDraggingLastEntity = nullptr;

	pasteMode = false;
	pasteModeValid = false;

	selectedPrototype = nullptr;
	selectedEntityIds.clear();
	selectedEntityIdsById.clear();
	copiedEntities.clear();
}

void SceneEditorTabView::reloadScene() {
	clearScene();
	SceneConnector::addScene(engine.get(), scene.get(), true, true, true, true, true);
}

void SceneEditorTabView::reloadOutliner() {
	sceneEditorTabController->setOutlinerContent();
	sceneEditorTabController->updateDetails(editorView->getScreenController()->getOutlinerSelection());
}

void SceneEditorTabView::reloadOutliner(const string& outlinerNode) {
	sceneEditorTabController->setOutlinerContent();
	editorView->getScreenController()->setOutlinerSelection(outlinerNode);
	sceneEditorTabController->updateDetails(editorView->getScreenController()->getOutlinerSelection());
}

void SceneEditorTabView::onCameraTranslation() {
	needsGizmoUpdate = true;
}

void SceneEditorTabView::onCameraRotation() {
	needsGizmoUpdate = true;
}

void SceneEditorTabView::onCameraScale() {
	needsGizmoUpdate = true;
}

void SceneEditorTabView::updateLights() {
	SceneConnector::setLights(engine.get(), scene.get());
}

void SceneEditorTabView::selectEntityInternal(Entity* entity)
{
	auto sceneEntity = scene->getEntity(entity->getId());
	if (sceneEntity != nullptr && sceneEntity->getPrototype()->getType() == Prototype_Type::DECAL) {
		auto decalEntityHierarchy = dynamic_cast<EntityHierarchy*>(entity);
		auto decalObbEntity = decalEntityHierarchy != nullptr?decalEntityHierarchy->getEntity("tdme.prototype.bv.0"):nullptr;
		if (decalObbEntity != nullptr) decalObbEntity->setEnabled(true);
	}
	const auto& red = entityColors["red"];
	entity->setEffectColorAdd(Color4(red.colorAddR, red.colorAddG, red.colorAddB, 0.0f));
	entity->setEffectColorMul(Color4(red.colorMulR, red.colorMulG, red.colorMulB, 1.0f));
}

void SceneEditorTabView::unselectEntityInternal(Entity* entity)
{
	const auto& color = entityColors["none"];
	entity->setEffectColorAdd(Color4(color.colorAddR, color.colorAddG, color.colorAddB, 0.0f));
	entity->setEffectColorMul(Color4(color.colorMulR, color.colorMulG, color.colorMulB, 1.0f));
	auto sceneEntity = scene->getEntity(entity->getId());
	if (sceneEntity == nullptr) return;
	auto colorProperty = sceneEntity->getProperty("object.color");
	if (colorProperty == nullptr) colorProperty = sceneEntity->getPrototype()->getProperty("object.color");
	if (colorProperty != nullptr) {
		auto entityColorIt = entityColors.find(colorProperty->getValue());
		if (entityColorIt != entityColors.end()) {
			const auto& entityColor = entityColorIt->second;
			entity->setEffectColorAdd(Color4(entity->getEffectColorAdd().getRed() + entityColor.colorAddR, entity->getEffectColorAdd().getGreen() + entityColor.colorAddG, entity->getEffectColorAdd().getBlue() + entityColor.colorAddB, 0.0f));
			entity->setEffectColorMul(Color4(entity->getEffectColorMul().getRed() * entityColor.colorMulR, entity->getEffectColorMul().getGreen() * entityColor.colorMulG, entity->getEffectColorMul().getBlue() * entityColor.colorMulB, 1.0f));
		}
	}
	if (sceneEntity != nullptr && sceneEntity->getPrototype()->getType() == Prototype_Type::DECAL) {
		auto decalEntityHierarchy = dynamic_cast<EntityHierarchy*>(entity);
		auto decalObbEntity = decalEntityHierarchy != nullptr?decalEntityHierarchy->getEntity("tdme.prototype.bv.0"):nullptr;
		if (decalObbEntity != nullptr) decalObbEntity->setEnabled(false);
	}
}

void SceneEditorTabView::resetEntity(Entity* entity) {
	if (entity == nullptr) return;
	unselectEntityInternal(entity);
	auto sceneEntity = scene->getEntity(entity->getId());
	if (sceneEntity == nullptr) return;
	if (sceneEntity->getPrototype()->getType()->hasNonEditScaleDownMode() == false) return;
	entity->setTransform(sceneEntity->getTransform());
	entity->setScale(
		sceneEntity->getPrototype()->getType()->getNonEditScaleDownModeDimension().
		clone().
		scale(
			Vector3(
				1.0f / (sceneEntity->getTransform().getScale().getX() * entity->getBoundingBox()->getDimensions().getX()),
				1.0f / (sceneEntity->getTransform().getScale().getY() * entity->getBoundingBox()->getDimensions().getY()),
				1.0f / (sceneEntity->getTransform().getScale().getZ() * entity->getBoundingBox()->getDimensions().getZ())
			)
		)
	);
	entity->update();
}

void SceneEditorTabView::selectEntities(const vector<string>& entityIds)
{
	removeGizmo();
	for (const auto& entityIdToRemove: selectedEntityIds) {
		auto entityToRemove = engine->getEntity(entityIdToRemove);
		if (entityToRemove != nullptr) unselectEntityInternal(entityToRemove);
	}
	selectedEntityIds.clear();
	selectedEntityIdsById.clear();
	for (const auto& entityId: entityIds) {
		auto selectedEntity = engine->getEntity(entityId);
		if (selectedEntity == nullptr) continue;
		selectEntityInternal(selectedEntity);
		selectedEntityIds.push_back(entityId);
		selectedEntityIdsById.insert(entityId);
	}

	if (entityIds.size() == 1) {
		auto selectedEntity = engine->getEntity(entityIds[0]);
		if (selectedEntity != nullptr) {
			setGizmoRotation(selectedEntity->getTransform());
			sceneEditorTabController->setEntityDetails(selectedEntity->getId());
		}
	} else
	if (entityIds.size() > 1) {
		setGizmoRotation(Transform());
		multipleSelectionTranslation = computeMultipleSelectionPivot();
		sceneEditorTabController->setEntityDetailsMultiple(multipleSelectionTranslation, getSelectedReflectionEnvironmentMappingId());
	}
	updateGizmo();
}

void SceneEditorTabView::unselectEntities()
{
	removeGizmo();
	for (const auto& entityIdToUnselect: selectedEntityIds) {
		auto entityToUnselect = engine->getEntity(entityIdToUnselect);
		if (entityToUnselect == nullptr) continue;
		resetEntity(entityToUnselect);
	}
	selectedEntityIds.clear();
	selectedEntityIdsById.clear();
}

void SceneEditorTabView::copyEntities()
{
	copiedEntities.clear();
	for (const auto& selectedEntityId: selectedEntityIds) {
		auto selectedEntity = engine->getEntity(selectedEntityId);
		if (selectedEntity != nullptr && StringTools::startsWith(selectedEntity->getId(), "tdme.sceneeditor.") == false) {
			auto sceneEntity = scene->getEntity(selectedEntity->getId());
			if (sceneEntity == nullptr) continue;
			copiedEntities.push_back(sceneEntity);
		}
	}
}

void SceneEditorTabView::setPlaceEntityMode(Prototype* prototype) {
	unselectEntities();
	selectedPrototype = prototype;
	placeEntityMode = true;
	placeEntityValid = false;
}

void SceneEditorTabView::unsetPlaceEntityMode(bool cancelled) {
	placeEntityMode = false;
	placeEntityValid = false;
	selectedPrototype = nullptr;
	engine->removeEntity("tdme.sceneeditor.placeentity");
	//
	if (cancelled == false || selectedEntityIds.empty() == false) {
		reloadOutliner();
		// select selected entities
		sceneEditorTabController->unselectEntities();
		for (const auto& entityId: selectedEntityIds) {
			sceneEditorTabController->selectEntity(entityId);
		}
		selectEntities(selectedEntityIds);
	}
}

void SceneEditorTabView::placeEntity()
{
	if (selectedPrototype == nullptr) return;

	Transform sceneEntityTransform;
	sceneEntityTransform.setTranslation(placeEntityTranslation);
	sceneEntityTransform.setScale(Vector3(1.0f, 1.0f, 1.0f));
	sceneEntityTransform.addRotation(scene->getRotationOrder()->getAxis0(), 0.0f);
	sceneEntityTransform.addRotation(scene->getRotationOrder()->getAxis1(), 0.0f);
	sceneEntityTransform.addRotation(scene->getRotationOrder()->getAxis2(), 0.0f);
	sceneEntityTransform.setRotationAngle(scene->getRotationOrder()->getAxisYIndex(), placeEntityYRotation * 90.0f);
	sceneEntityTransform.update();
	for (auto i = 0; i < scene->getEntityCount(); i++) {
		auto sceneEntity = scene->getEntityAt(i);
		if (sceneEntity->getPrototype() == selectedPrototype && sceneEntity->getTransform().getTranslation().equals(sceneEntityTransform.getTranslation())) {
			return;
		}
	}
	auto sceneEntity = new SceneEntity(
		selectedPrototype->getName() + "_" + to_string(scene->allocateEntityId()),
		"",
		sceneEntityTransform,
		selectedPrototype
	);
	scene->addEntity(sceneEntity);
	selectedEntityIds.push_back(sceneEntity->getId());
	auto entity = createEntity(sceneEntity);
	if (entity != nullptr) {
		resetEntity(entity);
		entity->setPickable(true);
		engine->addEntity(entity);
	}
	scene->update();
	cameraInputHandler->setSceneCenter(Vector3(scene->getCenter().getX(), scene->getBoundingBox()->getMax().getY() + 3.0f, scene->getCenter().getZ()));
}

bool SceneEditorTabView::placeEntity(Prototype* prototype, int mouseX, int mouseY) {
	if (engine->getEntityByMousePosition(mouseX, mouseY, placeEntityTranslation, entityPickingFilterPlacing.get()) != nullptr) {
		setPlaceEntityMode(prototype);
		placeEntity();
		unsetPlaceEntityMode(false);
		return true;
	}
	return false;
}

void SceneEditorTabView::removeEntities()
{
	removeGizmo();
	vector<Entity*> entitiesToRemove;
	for (const auto& selectedEntityId: selectedEntityIds) {
		Entity* selectedEntity = engine->getEntity(selectedEntityId);
		if (selectedEntity != nullptr && StringTools::startsWith(selectedEntity->getId(), "tdme.sceneeditor.") == false) {
			scene->removeEntity(selectedEntity->getId());
			engine->removeEntity(selectedEntity->getId());
			entitiesToRemove.push_back(selectedEntity);
		}
	}
	for (const auto& entityToRemove: entitiesToRemove) {
		selectedEntityIds.erase(remove(selectedEntityIds.begin(), selectedEntityIds.end(), entityToRemove->getId()), selectedEntityIds.end());
		auto selectedEntityIdsByIdIt = selectedEntityIdsById.find(entityToRemove->getId());
		if (selectedEntityIdsByIdIt != selectedEntityIdsById.end()) {
			selectedEntityIdsById.erase(selectedEntityIdsByIdIt);
		}
	}
	scene->update();
	cameraInputHandler->setSceneCenter(Vector3(scene->getCenter().getX(), scene->getBoundingBox()->getMax().getY() + 3.0f, scene->getCenter().getZ()));

	//
	reloadOutliner("scene.entities");
}

void SceneEditorTabView::setPasteMode() {
	unselectEntities();
	sceneEditorTabController->unselectEntities();
	pasteMode = true;
	pasteModeValid = false;
}

void SceneEditorTabView::unsetPasteMode() {
	auto pasteEntityIdx = 0;
	for (const auto& pasteEntity: copiedEntities) {
		auto pastePrototype = pasteEntity->getPrototype();
		auto entityId = "tdme.sceneeditor.paste." + pastePrototype->getName() + "." + to_string(pasteEntityIdx);
		engine->removeEntity(entityId);
		pasteEntityIdx++;
	}
	pasteMode = false;
	pasteModeValid = false;
}

void SceneEditorTabView::pasteEntities(bool displayOnly)
{
	auto pasteEntitiesMinX = Float::MAX_VALUE;
	auto pasteEntitiesMinZ = Float::MAX_VALUE;
	auto pasteEntitiesMinY = Float::MAX_VALUE;
	auto pasteEntitiesMaxX = Float::MIN_VALUE;
	auto pasteEntitiesMaxZ = Float::MIN_VALUE;
	auto pasteEntitiesMaxY = Float::MIN_VALUE;
	for (const auto& copiedEntity: copiedEntities) {
		auto entity = engine->getEntity(copiedEntity->getId());
		if (entity == nullptr) continue;
		BoundingBox cbv;
		cbv.fromBoundingVolumeWithTransform(entity->getBoundingBox(), copiedEntity->getTransform());
		const auto& entityBBMin = cbv.getMin();
		if (entityBBMin[0] < pasteEntitiesMinX) pasteEntitiesMinX = entityBBMin[0];
		if (entityBBMin[1] < pasteEntitiesMinY) pasteEntitiesMinY = entityBBMin[1];
		if (entityBBMin[2] < pasteEntitiesMinZ) pasteEntitiesMinZ = entityBBMin[2];
		const auto& entityBBMax = cbv.getMax();
		if (entityBBMax[0] > pasteEntitiesMaxX) pasteEntitiesMaxX = entityBBMax[0];
		if (entityBBMax[1] > pasteEntitiesMaxY) pasteEntitiesMaxY = entityBBMax[1];
		if (entityBBMax[2] > pasteEntitiesMaxZ) pasteEntitiesMaxZ = entityBBMax[2];
	}
	auto centerX = (pasteEntitiesMaxX - pasteEntitiesMinX) / 2.0f;
	auto centerZ = (pasteEntitiesMaxZ - pasteEntitiesMinZ) / 2.0f;
	auto pasteEntitiesIdx = 0;
	vector<string> entitiesToSelect;
	for (const auto& copiedEntity: copiedEntities) {
		auto pastePrototype = copiedEntity->getPrototype();
		Transform sceneEntityTransform;
		sceneEntityTransform.setTransform(copiedEntity->getTransform());
		auto entityDiffX = copiedEntity->getTransform().getTranslation().getX() - pasteEntitiesMinX;
		auto entityDiffY = copiedEntity->getTransform().getTranslation().getY() - pasteEntitiesMinY;
		auto entityDiffZ = copiedEntity->getTransform().getTranslation().getZ() - pasteEntitiesMinZ;
		sceneEntityTransform.setTranslation(
			Vector3(
				placeEntityTranslation.getX() + entityDiffX - centerX,
				placeEntityTranslation.getY() + entityDiffY,
				placeEntityTranslation.getZ() + entityDiffZ - centerZ
			)
		);
		sceneEntityTransform.update();
		if (displayOnly == false) {
			//
			auto sceneEntityId = pastePrototype->getName() + "_" + to_string(scene->allocateEntityId());
			auto sceneEntity = new SceneEntity(
				sceneEntityId,
				"",
				sceneEntityTransform,
				pastePrototype
			 );
			BaseProperties* properties = copiedEntity;
			for (auto property: properties->getProperties()) {
				sceneEntity->addProperty(property->getName(), property->getValue());
			}
			scene->addEntity(sceneEntity);
			auto entity = createEntity(pastePrototype, sceneEntityId, sceneEntityTransform);
			if (entity != nullptr) {
				resetEntity(entity);
				entity->setPickable(true);
				engine->addEntity(entity);
			}
			entitiesToSelect.push_back(sceneEntityId);
		} else {
			auto entityId = "tdme.sceneeditor.paste." + pastePrototype->getName() + "." + to_string(pasteEntitiesIdx);
			auto entity = engine->getEntity(entityId);
			if (entity != nullptr) {
				entity->setTransform(sceneEntityTransform);
			} else {
				entity = createEntity(pastePrototype, entityId, sceneEntityTransform);
				if (entity != nullptr) {
					unselectEntityInternal(entity);
					entity->setPickable(true);
					engine->addEntity(entity);
				}
			}
		}
		pasteEntitiesIdx++;
	}

	//
	if (displayOnly == false) {
		reloadOutliner();
		// select selected entities
		sceneEditorTabController->unselectEntities();
		for (const auto& entityId: entitiesToSelect) {
			sceneEditorTabController->selectEntity(entityId);
		}
		selectEntities(entitiesToSelect);
	}
}

const Vector3 SceneEditorTabView::computeMultipleSelectionPivot() {
	Vector3 pivot;
	auto entityCount = 0;
	for (const auto& selectedEntityId: selectedEntityIds) {
		auto selectedEntity = engine->getEntity(selectedEntityId);
		if (selectedEntity != nullptr && StringTools::startsWith(selectedEntity->getId(), "tdme.sceneeditor.") == false) {
			auto sceneEntity = scene->getEntity(selectedEntity->getId());
			if (sceneEntity == nullptr) continue;
			pivot.add(sceneEntity->getTransform().getTranslation());
			entityCount++;
		}
	}
	if (entityCount > 1) pivot.scale(1.0f / entityCount);
	return pivot;
}

const string SceneEditorTabView::getSelectedReflectionEnvironmentMappingId() {
	string selectedEnvironmentMappingId;
	for (const auto& selectedEntityId: selectedEntityIds) {
		auto selectedEntity = engine->getEntity(selectedEntityId);
		if (selectedEntity != nullptr && StringTools::startsWith(selectedEntity->getId(), "tdme.sceneeditor.") == false) {
			auto sceneEntity = scene->getEntity(selectedEntity->getId());
			if (sceneEntity == nullptr) continue;
			if (selectedEnvironmentMappingId.empty() == true) {
				selectedEnvironmentMappingId = sceneEntity->getReflectionEnvironmentMappingId();
			} else
			if (selectedEnvironmentMappingId != sceneEntity->getReflectionEnvironmentMappingId()) {
				selectedEnvironmentMappingId.clear();
				return selectedEnvironmentMappingId;
			}
		}
	}
	return selectedEnvironmentMappingId;
}

void SceneEditorTabView::centerEntities()
{
	if (selectedEntityIds.size() == 0) {
		return;
	}
	Vector3 center;
	for (const auto& selectedEntityId: selectedEntityIds) {
		auto selectedEntity = engine->getEntity(selectedEntityId);
		if (selectedEntity == nullptr) continue;
		center.add(selectedEntity->getWorldBoundingBox()->getMin().clone().add(selectedEntity->getWorldBoundingBox()->getMax()).scale(0.5f));
	}
	engine->getCamera()->setLookAt(center.scale(1.0f / selectedEntityIds.size()));
}

void SceneEditorTabView::selectSameEntities()
{
	if (selectedEntityIds.size() == 0) {
		return;
	}
	sceneEditorTabController->unselectEntities();

	auto sceneEntity = scene->getEntity(selectedEntityIds[0]);
	auto prototype = sceneEntity != nullptr?sceneEntity->getPrototype():nullptr;
	vector<string> entitiesToSelect;
	for (auto _sceneEntity: scene->getEntities()) {
		if (_sceneEntity->getPrototype() != prototype) continue;
		sceneEditorTabController->selectEntity(_sceneEntity->getId());
		entitiesToSelect.push_back(_sceneEntity->getId());
	}
	selectEntities(entitiesToSelect);
}

void SceneEditorTabView::openPrototype() {
	if (selectedEntityIds.size() == 0) {
		return;
	}

	sceneEditorTabController->unselectEntities();

	auto sceneEntity = scene->getEntity(selectedEntityIds[0]);
	auto prototype = sceneEntity != nullptr?sceneEntity->getPrototype():nullptr;
	if (prototype == nullptr || prototype->getFileName().empty() == true) {
		sceneEditorTabController->showInfoPopUp("Warning", "Prototype is embedded and can not be opened");
	} else {
		editorView->getScreenController()->openFile(prototype->getFileName());
	}
}

void SceneEditorTabView::updateGizmo() {
	if (selectedEntityIds.size() == 0) {
		removeGizmo();
		return;
	}

	// rotation for gizmo
	Transform transform;

	//
	Vector3 gizmoCenter;
	auto entityCount = 0;
	for (const auto& selectedEntityId: selectedEntityIds) {
		auto selectedEntity = engine->getEntity(selectedEntityId);
		if (selectedEntity != nullptr && StringTools::startsWith(selectedEntity->getId(), "tdme.sceneeditor.") == false) {
			auto sceneEntity = scene->getEntity(selectedEntity->getId());
			if (sceneEntity == nullptr) continue;
			gizmoCenter.add(selectedEntity->getTransform().getTranslation());
			entityCount++;
		}
	}
	if (entityCount == 0) {
		removeGizmo();
		return;
	} else
	if (entityCount == 1) {
		auto selectedSceneEntity = scene->getEntity(selectedEntityIds[0]);
		auto selectedPrototype = selectedSceneEntity != nullptr?selectedSceneEntity->getPrototype():nullptr;
		if (selectedSceneEntity != nullptr) transform.setTransform(selectedSceneEntity->getTransform());
		if (selectedPrototype != nullptr) setGizmoTypeMask(selectedPrototype->getType()->getGizmoTypeMask());
		if (selectedSceneEntity == nullptr || selectedPrototype == nullptr) {
			removeGizmo();
		}
	} else {
		gizmoCenter.scale(1.0f / entityCount);
	}

	//
	Gizmo::updateGizmo(gizmoCenter, transform);
}

bool SceneEditorTabView::applyBase(const string& name, const string& description) {
	if (selectedEntityIds.size() != 1) return false;

	auto selectedEntity = engine->getEntity(selectedEntityIds[0]);
	if (selectedEntity == nullptr || StringTools::startsWith(selectedEntity->getId(), "tdme.sceneeditor.")) return false;

	auto sceneEntity = scene->getEntity(selectedEntity->getId());
	if (sceneEntity == nullptr) return false;

	sceneEntity->setDescription(description);
	auto oldName = sceneEntity->getId();
	if (oldName == name) return true;

	if (engine->getEntity(name) != nullptr) return false;
	if (scene->renameEntity(sceneEntity->getId(), name) == true) {
		engine->removeEntity(oldName);
		selectedEntityIds.clear();
		selectedEntityIdsById.clear();
		auto entity = createEntity(sceneEntity);
		if (entity == nullptr) {
			return false;
		} else {
			selectEntityInternal(entity);
			selectedEntityIds.push_back(entity->getId());
			selectedEntityIdsById.insert(entity->getId());
			entity->setPickable(true);
			engine->addEntity(entity);
			//
			reloadOutliner("scene.entities." + entity->getId());
		}
		return true;
	} else {
		return false;
	}
}

void SceneEditorTabView::applyTranslation(const Vector3& translation) {
	if (selectedEntityIds.size() == 0)
		return;

	if (selectedEntityIds.size() == 1) {
		auto selectedEntity = engine->getEntity(selectedEntityIds[0]);
		if (selectedEntity == nullptr) return;
		auto sceneEntity = scene->getEntity(selectedEntity->getId());
		if (sceneEntity == nullptr) return;

		sceneEntity->getTransform().setTranslation(translation);
		sceneEntity->getTransform().update();
		selectedEntity->setTransform(sceneEntity->getTransform());
	} else
	if (selectedEntityIds.size() > 1) {
		for (const auto& selectedEntityId: selectedEntityIds) {
			auto selectedEntity = engine->getEntity(selectedEntityId);
			if (selectedEntity == nullptr) continue;
			auto sceneEntity = scene->getEntity(selectedEntity->getId());
			if (sceneEntity == nullptr) continue;

			sceneEntity->getTransform().setTranslation(
				sceneEntity->getTransform().getTranslation().clone().add(translation.clone().sub(multipleSelectionTranslation))
			);
			sceneEntity->getTransform().update();
			selectedEntity->setTransform(sceneEntity->getTransform());
		}
		multipleSelectionTranslation.add(translation.clone().sub(multipleSelectionTranslation));
	}
	scene->update();
	cameraInputHandler->setSceneCenter(Vector3(scene->getCenter().getX(), scene->getBoundingBox()->getMax().getY() + 3.0f, scene->getCenter().getZ()));
	updateGizmo();
}

void SceneEditorTabView::applyRotation(const Vector3& rotation) {
	if (selectedEntityIds.size() == 0)
			return;

	if (selectedEntityIds.size() == 1) {
		auto selectedEntity = engine->getEntity(selectedEntityIds[0]);
		if (selectedEntity == nullptr) return;
		auto sceneEntity = scene->getEntity(selectedEntity->getId());
		if (sceneEntity == nullptr) return;
		sceneEntity->getTransform().getRotation(scene->getRotationOrder()->getAxisXIndex()).setAngle(rotation.getX());
		sceneEntity->getTransform().getRotation(scene->getRotationOrder()->getAxisYIndex()).setAngle(rotation.getY());
		sceneEntity->getTransform().getRotation(scene->getRotationOrder()->getAxisZIndex()).setAngle(rotation.getZ());
		sceneEntity->getTransform().update();
		selectedEntity->setTransform(sceneEntity->getTransform());
	} else
	if (selectedEntityIds.size() > 1) {
		for (const auto& selectedEntityId: selectedEntityIds) {
			auto selectedEntity = engine->getEntity(selectedEntityId);
			if (selectedEntity == nullptr) continue;
			auto sceneEntity = scene->getEntity(selectedEntity->getId());
			if (sceneEntity == nullptr) continue;
			if ((sceneEntity->getPrototype()->getType()->getGizmoTypeMask() & Gizmo::GIZMOTYPE_ROTATE) == Gizmo::GIZMOTYPE_ROTATE) {
				sceneEntity->getTransform().getRotation(scene->getRotationOrder()->getAxisXIndex()).setAngle(sceneEntity->getTransform().getRotation(scene->getRotationOrder()->getAxisXIndex()).getAngle() + (rotation.getX() - multipleSelectionRotation.getX()));
				sceneEntity->getTransform().getRotation(scene->getRotationOrder()->getAxisYIndex()).setAngle(sceneEntity->getTransform().getRotation(scene->getRotationOrder()->getAxisYIndex()).getAngle() + (rotation.getY() - multipleSelectionRotation.getY()));
				sceneEntity->getTransform().getRotation(scene->getRotationOrder()->getAxisZIndex()).setAngle(sceneEntity->getTransform().getRotation(scene->getRotationOrder()->getAxisZIndex()).getAngle() + (rotation.getZ() - multipleSelectionRotation.getZ()));
			}
			sceneEntity->getTransform().update();
			selectedEntity->setTransform(sceneEntity->getTransform());
		}
		multipleSelectionRotation.add(rotation.clone().sub(multipleSelectionRotation));
	}
	scene->update();
	cameraInputHandler->setSceneCenter(Vector3(scene->getCenter().getX(), scene->getBoundingBox()->getMax().getY() + 3.0f, scene->getCenter().getZ()));
	updateGizmo();
}

void SceneEditorTabView::applyScale(const Vector3& scale) {
	if (selectedEntityIds.size() == 0)
		return;

	if (selectedEntityIds.size() == 1) {
		auto selectedEntity = engine->getEntity(selectedEntityIds[0]);
		if (selectedEntity == nullptr) return;
		auto sceneEntity = scene->getEntity(selectedEntity->getId());
		if (sceneEntity == nullptr) return;

		sceneEntity->getTransform().setScale(Vector3(scale));
		sceneEntity->getTransform().update();
		selectedEntity->setTransform(sceneEntity->getTransform());
	} else
	if (selectedEntityIds.size() > 1) {
		for (const auto& selectedEntityId: selectedEntityIds) {
			auto selectedEntity = engine->getEntity(selectedEntityId);
			if (selectedEntity == nullptr) continue;
			auto sceneEntity = scene->getEntity(selectedEntity->getId());
			if (sceneEntity == nullptr) continue;

			sceneEntity->getTransform().setScale(sceneEntity->getTransform().getScale().clone().scale(scale / multipleSelectionScale));
			sceneEntity->getTransform().update();
			selectedEntity->setTransform(sceneEntity->getTransform());
		}
		multipleSelectionScale*= scale / multipleSelectionScale;
	}
	scene->update();
	cameraInputHandler->setSceneCenter(Vector3(scene->getCenter().getX(), scene->getBoundingBox()->getMax().getY() + 3.0f, scene->getCenter().getZ()));
	updateGizmo();
}

void SceneEditorTabView::applyReflectionEnvironmentMappingId(const string& reflectionEnvironmentMappingId) {
	if (selectedEntityIds.size() == 0)
		return;

	for (const auto& selectedEntityId: selectedEntityIds) {
		auto selectedEntity = engine->getEntity(selectedEntityId);
		if (selectedEntity == nullptr) continue;
		auto sceneEntity = scene->getEntity(selectedEntity->getId());
		if (sceneEntity == nullptr) continue;

		auto object = dynamic_cast<Object*>(selectedEntity);
		if (object != nullptr) object->setReflectionEnvironmentMappingId(reflectionEnvironmentMappingId);
		sceneEntity->setReflectionEnvironmentMappingId(reflectionEnvironmentMappingId);
	}
}

bool SceneEditorTabView::isGridEnabled()
{
	return gridEnabled;
}

void SceneEditorTabView::setGridEnabled(bool gridEnabled)
{
	this->gridEnabled = gridEnabled;
	if (gridEnabled) {
		updateGrid();
	} else {
		removeGrid();
	}
}

float SceneEditorTabView::getGridY()
{
	return gridY;
}

void SceneEditorTabView::setGridY(float gridY)
{
	if (gridEnabled == true) removeGrid();
	this->gridY = gridY;
	if (gridEnabled == true) updateGrid();

}

void SceneEditorTabView::updateGrid()
{
	if (gridEnabled == false) return;

	string entityId = "tdme.sceneeditor.grid";
	auto entity = engine->getEntity(entityId);
	if (entity == nullptr) {
		entity = new Object(entityId, gridModel.get());
		entity->setFrustumCulling(false);
		entity->addRotation(scene->getRotationOrder()->getAxis0(), 0.0f);
		entity->addRotation(scene->getRotationOrder()->getAxis1(), 0.0f);
		entity->addRotation(scene->getRotationOrder()->getAxis2(), 0.0f);
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
			selectEntityInternal(entity);
		} else {
			unselectEntityInternal(entity);
		}
		engine->addEntity(entity);
	}
}

void SceneEditorTabView::removeGrid()
{
	engine->removeEntity("tdme.sceneeditor.grid");
}

void SceneEditorTabView::getSnapping(bool& snappingEnabled, float& snappingX, float& snappingZ) {
	snappingEnabled = this->snappingEnabled;
	snappingX = this->snappingX;
	snappingZ = this->snappingZ;
}

void SceneEditorTabView::setSnapping(bool snappingEnabled, float snappingX, float snappingZ) {
	this->snappingEnabled = snappingEnabled;
	this->snappingX = snappingX;
	this->snappingZ = snappingZ;
}

void SceneEditorTabView::addPrototype(Prototype* prototype) {
	try {
		prototype->setEmbedded(false);
		auto sceneLibrary = scene->getLibrary();
		if (prototype->getType() == Prototype_Type::TERRAIN) {
			while (sceneLibrary->getTerrainPrototype() != nullptr) {
				for (auto prototype: sceneLibrary->getPrototypes()) {
					if (prototype->getType() == Prototype_Type::TERRAIN) {
						sceneLibrary->removePrototype(prototype->getId());
						break;
					}
				}
			}
			sceneLibrary->addPrototype(prototype);
			SceneConnector::resetEngine(engine.get(), scene.get());
			SceneConnector::setLights(engine.get(), scene.get());
			SceneConnector::addScene(engine.get(), scene.get(), true, true, true, true, true);
			scene->update();
			cameraInputHandler->setSceneCenter(scene->getCenter());
			cameraInputHandler->reset();
		} else {
			sceneLibrary->addPrototype(prototype);
		}
	} catch (Exception& exception) {
		Console::printLine("SceneEditorTabView::addPrototype(): An error occurred: " + string(exception.what()));
		sceneEditorTabController->showInfoPopUp("Warning", string(exception.what()));
	}
	reloadOutliner("scene.prototypes." + to_string(prototype->getId()));
}

Entity* SceneEditorTabView::createEntity(Prototype* prototype, const string& id, const Transform& transform, int instances) {
	if (prototype->getType() == Prototype_Type::DECAL) {
		return SceneConnector::createEditorDecalEntity(prototype, id, transform, instances);
	} else {
		return SceneConnector::createEntity(prototype, id, transform, instances);
	}
}

Entity* SceneEditorTabView::createEntity(SceneEntity* sceneEntity, const Vector3& translation, int instances) {
	if (sceneEntity->getPrototype()->getType() == Prototype_Type::DECAL) {
		return SceneConnector::createEditorDecalEntity(sceneEntity, translation, instances);
	} else {
		return SceneConnector::createEntity(sceneEntity, translation, instances);
	}
}

void SceneEditorTabView::runScene() {
	// stop scene
	stopScene();

	//
	removeGizmo();

	// execute scene
	{
		auto world = make_unique<World>("applicationclient-world");
		SceneConnector::addScene(world.get(), scene.get(), true);
		auto applicationContext = make_unique<Context>(false);
		applicationContext->setApplicationRootPathName(editorView->getScreenController()->getProjectPath());
		applicationContext->setScene(scene.get());
		applicationContext->setEngine(engine.get());
		applicationContext->setAudio(Audio::getInstance());
		applicationContext->setWorld(world.release());
		applicationContext->setSoundPoolSize(1);
		applicationClient = make_unique<ApplicationClient>(applicationContext.release());
		applicationClient->getContext()->initialize();
	}

	//
	Library* scriptLibrary = nullptr;

	// load script library from libscriptlibrary.so
	string scriptLibraryURI = editorView->getScreenController()->getProjectPath() + "/libscriptlibrary";
	#if defined(_MSC_VER)
		scriptLibraryURI+= ".dll";
		//
		auto scriptLibraryHandle = LoadLibrary(scriptLibraryURI.c_str());
		if (scriptLibraryHandle == nullptr) {
			Console::printLine("SceneEditorTabView::runScene(): Could not open " + scriptLibraryURI);
		} else {
			//
			Library* (*scriptLibraryCreateInstance)() = (Library*(*)())GetProcAddress(scriptLibraryHandle, "createInstance");
			//
			if (scriptLibraryCreateInstance == nullptr) {
				FreeLibrary(scriptLibraryHandle);
				scriptLibraryHandle = nullptr;
				//
				Console::printLine("SceneEditorTabView::runScene(): Could not find script library createInstance() entry point");
			} else {
				//
				scriptLibrary = (Library*)scriptLibraryCreateInstance();
				if (scriptLibrary == nullptr) {
					FreeLibrary(scriptLibraryHandle);
					scriptLibraryHandle = nullptr;
					//
					Console::printLine("SceneEditorTabView::runScene(): Could not create script library");
				}
			}
		}
	#else
		scriptLibraryURI+= ".so";
		//
		#if defined(__HAIKU__)
			// TODO: fix me!!!
			scriptLibraryHandle = dlopen(("lib/" + scriptLibraryURI).c_str(), RTLD_NOW);
		#else
			scriptLibraryHandle = dlopen(scriptLibraryURI.c_str(), RTLD_NOW);
		#endif
			//
		if (scriptLibraryHandle == nullptr) {
			Console::printLine("SceneEditorTabView::runScene(): Could not open " + scriptLibraryURI);
		} else {
			//
			Library* (*scriptLibraryCreateInstance)() = (Library*(*)())dlsym(scriptLibraryHandle, "createInstance");
			//
			if (scriptLibraryCreateInstance == nullptr) {
				dlclose(scriptLibraryHandle);
				scriptLibraryHandle = nullptr;
				//
				Console::printLine("SceneEditorTabView::runScene(): Could not find script library createInstance() entry point");
			} else {
				//
				scriptLibrary = (Library*)scriptLibraryCreateInstance();
				if (scriptLibrary == nullptr) {
					dlclose(scriptLibraryHandle);
					scriptLibraryHandle = nullptr;
					//
					Console::printLine("SceneEditorTabView::runScene(): Could not create script library");
				}
			}
		}
	#endif

	//
	Console::printLine("SceneEditorTabView::runScene(): native script library @ " + scriptLibraryURI + ": " + string(scriptLibrary != nullptr?"YES":"NO"));

	// add gui
	if (scene->getGUIFileName().empty() == false) {
		try {
			auto screenNode = GUIParser::parse(
				Tools::getPathName(scene->getGUIFileName()),
				Tools::getFileName(scene->getGUIFileName()),
				{},
				scriptLibrary,
				MinitScript::Variable()
				// TODO: implement me
				// applicationClient->getContext()
			);
			engine->getGUI()->addScreen(screenNode->getId(), screenNode);
			engine->getGUI()->addRenderScreen(screenNode->getId());
		} catch (Exception& exception) {
			Console::printLine("SceneEditorTabView::runScene(): an error occurred: " + string(exception.what()));
		}
	}

	// add logics
	// TODO: exception handling
	auto valid = true;
	string invalidScripts;
	for (auto entity: scene->getEntities()) {
		if (entity->getPrototype()->hasScript() == true) {
			//
			unique_ptr<LogicMinitScript> logicMinitScript;
			// try to load from native library
			if (scriptLibrary != nullptr) {
				//
				auto scriptURI = applicationClient->getContext()->getRelativeURI(entity->getPrototype()->getScript());
				// load from library as generic MinitScript
				auto libraryMinitScript = unique_ptr<MinitScript>(
					scriptLibrary->loadScript(
						Tools::getPathName(scriptURI),
						Tools::getFileName(scriptURI),
						applicationClient->getContext()->getApplicationRootPathName()
					)
				);
				// no native script found?
				if (libraryMinitScript == nullptr) {
					// no op
				} else
				// no LogicMinitScript
				if (dynamic_cast<LogicMinitScript*>(libraryMinitScript.get()) == nullptr) {
					Console::printLine("SceneEditorTabView::runScene(): Native library: Native script not of type LogicMinitScript: " + entity->getPrototype()->getScript());
				} else {
					// cast to LogicMinitScript
					logicMinitScript = unique_ptr<LogicMinitScript>(dynamic_cast<LogicMinitScript*>(libraryMinitScript.release()));
				}
			}
			if (logicMinitScript == nullptr) {
				// nope, just parse script into LogicMinitScript
				logicMinitScript = make_unique<LogicMinitScript>();
				logicMinitScript->parseScript(
					Tools::getPathName(entity->getPrototype()->getScript()),
					Tools::getFileName(entity->getPrototype()->getScript())
				);
			}
			//
			if (logicMinitScript->isValid() == false) {
				//
				invalidScripts+=
					Tools::getRelativeResourcesFileName(
						editorView->getScreenController()->getProjectPath(), Tools::getPathName(entity->getPrototype()->getScript()) + "/" + Tools::getFileName(entity->getPrototype()->getScript())
					);
				//
				if (logicMinitScript->getParseErrors().empty() == true) {
					invalidScripts+= "\n";
				} else {
					//
					invalidScripts+= ":\n";
					//
					for (const auto& parseError: logicMinitScript->getParseErrors())
						invalidScripts+= "\t" + parseError + "\n";
					//
					invalidScripts+= "\n";
				}
				//
				valid = false;
				//
				continue;
			}
			//
			applicationClient->getContext()->addLogic(
				make_unique<MinitScriptLogic>(
					applicationClient->getContext(),
					entity->getId(),
					entity->getPrototype()->isScriptHandlingHID(),
					logicMinitScript.release(),
					entity->getPrototype(),
					true
				).release()
			);
		}
	}

	//
	if (valid == false) {
		sceneEditorTabController->setRunButtonMode(false);
		//
		sceneEditorTabController->showInfoPopUp("Error", "Not all scripts are valid to be run:\n\n" + invalidScripts);
		//
		applicationClient->getContext()->unsetEngine();
		applicationClient->getContext()->unsetScene();
		//
		applicationClient = nullptr;
		// reset scene
		engine->getGUI()->reset();
		SceneConnector::resetEngine(engine.get(), scene.get());
		SceneConnector::setLights(engine.get(), scene.get());
		SceneConnector::addScene(engine.get(), scene.get(), true, true, true, true, true);
		scene->update();
		cameraInputHandler->setSceneCenter(scene->getCenter());
		cameraInputHandler->reset();
		//
		return;
	}

	//
	sceneEditorTabController->setRunButtonMode(true);

	// and go
	applicationClient->start();
}

void SceneEditorTabView::stopScene() {
	//
	sceneEditorTabController->setRunButtonMode(false);

	//
	shutdownScene();

	// reset scene
	engine->getGUI()->reset();
	SceneConnector::setLights(engine.get(), scene.get());
	SceneConnector::addScene(engine.get(), scene.get(), true, true, true, true, true);
	scene->update();
	cameraInputHandler->setSceneCenter(scene->getCenter());
	cameraInputHandler->reset();
}

void SceneEditorTabView::shutdownScene() {
	//
	if (applicationClient == nullptr) return;
	// shutdown application client
	applicationClient->stop();
	applicationClient->join();
	//
	SceneConnector::resetEngine(engine.get(), scene.get());
	//
	applicationClient->getContext()->unsetEngine();
	applicationClient->getContext()->unsetScene();
	//
	applicationClient = nullptr;
	//
	if (scriptLibraryHandle != nullptr) {
		#if defined(_MSC_VER)
			FreeLibrary(scriptLibraryHandle);
		#else
			dlclose(scriptLibraryHandle);
		#endif
		scriptLibraryHandle = nullptr;
	}
}
