#include <tdme/tools/editor/tabviews/SceneEditorTabView.h>

#include <string>
#include <unordered_set>

#include <tdme/tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/prototype/BaseProperty.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/Prototype_Type.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/engine/scene/SceneEntity.h>
#include <tdme/engine/scene/SceneLibrary.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/EntityPickingFilter.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/SceneConnector.h>
#include <tdme/engine/Timing.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
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

using std::string;
using std::to_string;
using std::unordered_set;

using tdme::tools::editor::tabviews::SceneEditorTabView;

using tdme::engine::model::Color4;
using tdme::engine::prototype::BaseProperty;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::Prototype_Type;
using tdme::engine::scene::Scene;
using tdme::engine::scene::SceneEntity;
using tdme::engine::scene::SceneLibrary;
using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::EntityPickingFilter;
using tdme::engine::Light;
using tdme::engine::Object3D;
using tdme::engine::SceneConnector;
using tdme::engine::Timing;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUI;
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
	engine = Engine::createOffScreenInstance(512, 512, true, true, true);
	engine->setSceneColor(Color4(125.0f / 255.0f, 125.0f / 255.0f, 125.0f / 255.0f, 1.0f));
	this->scene = scene;
	this->cameraInputHandler = new CameraInputHandler(engine, this);
	this->keyControl = false;
	this->keyShift = false;
	this->keyEscape = false;
	this->placeEntityYRotation = 0;
	this->placeEntityMouseX = MOUSE_DOWN_LAST_POSITION_NONE;
	this->placeEntityMouseY = MOUSE_DOWN_LAST_POSITION_NONE;
	this->mouseDownLastX = MOUSE_DOWN_LAST_POSITION_NONE;
	this->mouseDownLastY = MOUSE_DOWN_LAST_POSITION_NONE;
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
	this->gridModel = Tools::createGridModel();

	//
	setEngine(engine);

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
		class PrototypePickingFilterNoGrid: public virtual EntityPickingFilter
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
		entityPickingFilterNoGrid = new PrototypePickingFilterNoGrid(this);
	}

	//
	{
		// entity picking filter for no placing object
		class PrototypePickingFilterPlacing: public virtual EntityPickingFilter
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
		entityPickingFilterPlacing = new PrototypePickingFilterPlacing(this);
	}

	//
	outlinerState.expandedOutlinerParentOptionValues.push_back("scene");
}

SceneEditorTabView::~SceneEditorTabView() {
	delete gridModel;
	delete sceneEditorTabController;
	delete engine;
}

void SceneEditorTabView::handleInputEvents()
{
	#if !defined(GLFW3) && !defined(VUKAN)
		keyControl = false;
		keyShift = false;
	#endif
	auto keyControlX = false;
	auto keyControlC = false;
	auto keyControlV = false;
	auto keyDelete = false;
	for (auto i = 0; i < engine->getGUI()->getKeyboardEvents().size(); i++) {
		auto& event = engine->getGUI()->getKeyboardEvents()[i];
		if (event.isProcessed() == true) continue;
		if (event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_TYPED) continue;
		auto isKeyDown = event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED;
		#if defined(GLFW3) || defined(VUKAN)
			if (event.getKeyCode() == KEYBOARD_KEYCODE_LEFT_SHIFT) {
				keyShift = isKeyDown;
				event.setProcessed(true);
			}
			if (event.getKeyCode() == KEYBOARD_KEYCODE_LEFT_CTRL) {
				keyControl = isKeyDown;
				event.setProcessed(true);
			}
		#else
			keyControl = event.isControlDown();
			keyShift = event.isShiftDown();
		#endif
		if (event.getKeyCode() == GUIKeyboardEvent::KEYCODE_ESCAPE) {
			keyEscape = isKeyDown;
			event.setProcessed(true);
		}
		if (event.getKeyCode() == GUIKeyboardEvent::KEYCODE_BACKSPACE ||
			event.getKeyCode() == GUIKeyboardEvent::KEYCODE_DELETE) {
			keyDelete = isKeyDown;
			event.setProcessed(true);
		}
		if (Character::toLowerCase(event.getKeyChar()) == 24) {
			keyControlX = isKeyDown;
			event.setProcessed(true);
		}
		if (Character::toLowerCase(event.getKeyChar()) == 3) {
			keyControlC = isKeyDown;
			event.setProcessed(true);
		}
		if (Character::toLowerCase(event.getKeyChar()) == 22) {
			keyControlV = isKeyDown;
			event.setProcessed(true);
		}
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
			event.setProcessed(true);
			updateGizmo();
		}
		if (Character::toLowerCase(event.getKeyChar()) == '3' && isKeyDown == true) {
			setGizmoType(GIZMOTYPE_ROTATE);
			event.setProcessed(true);
			updateGizmo();
		}
		if (Character::toLowerCase(event.getKeyChar()) == '4' && isKeyDown == true) {
			setGizmoType(GIZMOTYPE_SCALE);
			event.setProcessed(true);
			updateGizmo();
		}
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

		if (event.getButton() == MOUSE_BUTTON_LEFT) {
			if (event.getType() == GUIMouseEvent::MOUSEEVENT_DRAGGED) {
				if (mouseDragging == false) {
					mouseDragging = true;
					mouseDownLastX = event.getXUnscaled();
					mouseDownLastY = event.getYUnscaled();
					mouseDraggingLastEntity = nullptr;
					event.setProcessed(true);
				}
			} else {
				if (mouseDragging == true) {
					mouseDownLastX = MOUSE_DOWN_LAST_POSITION_NONE;
					mouseDownLastY = MOUSE_DOWN_LAST_POSITION_NONE;
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
				} else {
					setGizmoMode(GIZMOMODE_NONE);
				}
				event.setProcessed(true);
			} else
			if (placeEntityMode == false) {
				Node* selectedEntityNode = nullptr;
				Entity* selectedEntity = nullptr;
				if (getGizmoMode() == GIZMOMODE_NONE) selectedEntity = engine->getEntityByMousePosition(event.getXUnscaled(), event.getYUnscaled(), entityPickingFilterNoGrid, &selectedEntityNode);
				if (mouseDragging == true) {
					Vector3 deltaTranslation;
					Vector3 deltaRotation;
					Vector3 absoluteScale;
					if (determineGizmoDeltaTransformations(mouseDownLastX, mouseDownLastY, event.getXUnscaled(), event.getYUnscaled(), deltaTranslation, deltaRotation, absoluteScale) == true) {
						auto gizmoEntity = getGizmoObject3D();
						if (gizmoEntity != nullptr) {
							Transformations rotations;
							rotations.addRotation(scene->getRotationOrder()->getAxis0(), deltaRotation[scene->getRotationOrder()->getAxis0VectorIndex()]);
							rotations.addRotation(scene->getRotationOrder()->getAxis1(), deltaRotation[scene->getRotationOrder()->getAxis1VectorIndex()]);
							rotations.addRotation(scene->getRotationOrder()->getAxis2(), deltaRotation[scene->getRotationOrder()->getAxis2VectorIndex()]);
							rotations.update();
							for (auto selectedEntityId: selectedEntityIds) {
								auto _selectedEntity = engine->getEntity(selectedEntityId);
								if (_selectedEntity != nullptr && StringTools::startsWith(_selectedEntity->getId(), "tdme.sceneeditor.") == false) {
									auto sceneEntity = scene->getEntity(_selectedEntity->getId());
									if (sceneEntity == nullptr) continue;
									auto translation = sceneEntity->getTransformations().getTranslation();
									translation = gizmoEntity->getTranslation().clone().add(rotations.getRotationsQuaternion().multiply(translation.clone().sub(gizmoEntity->getTranslation())));
									sceneEntity->getTransformations().setTranslation(translation.clone().add(deltaTranslation));
									auto scale = sceneEntity->getTransformations().getScale().clone().scale(absoluteScale);
									if (Math::abs(scale.getX()) < 0.01f) scale.setX(Math::sign(scale.getX()) * 0.01f);
									if (Math::abs(scale.getY()) < 0.01f) scale.setY(Math::sign(scale.getY()) * 0.01f);
									if (Math::abs(scale.getZ()) < 0.01f) scale.setZ(Math::sign(scale.getZ()) * 0.01f);
									if (Math::abs(scale.getX()) > 100.0f) scale.setX(Math::sign(scale.getX()) * 100.0f);
									if (Math::abs(scale.getY()) > 100.0f) scale.setY(Math::sign(scale.getY()) * 100.0f);
									if (Math::abs(scale.getZ()) > 100.0f) scale.setZ(Math::sign(scale.getZ()) * 100.0f);
									sceneEntity->getTransformations().setScale(scale);
									if ((sceneEntity->getPrototype()->getType()->getGizmoTypeMask() & Gizmo::GIZMOTYPE_ROTATE) == Gizmo::GIZMOTYPE_ROTATE) {
										sceneEntity->getTransformations().setRotationAngle(scene->getRotationOrder()->getAxisXIndex(), sceneEntity->getTransformations().getRotationAngle(scene->getRotationOrder()->getAxisXIndex()) + deltaRotation[0]);
										sceneEntity->getTransformations().setRotationAngle(scene->getRotationOrder()->getAxisYIndex(), sceneEntity->getTransformations().getRotationAngle(scene->getRotationOrder()->getAxisYIndex()) + deltaRotation[1]);
										sceneEntity->getTransformations().setRotationAngle(scene->getRotationOrder()->getAxisZIndex(), sceneEntity->getTransformations().getRotationAngle(scene->getRotationOrder()->getAxisZIndex()) + deltaRotation[2]);
									}
									sceneEntity->getTransformations().update();
									_selectedEntity->fromTransformations(sceneEntity->getTransformations());
								}
							}
							if (selectedEntityIds.size() == 1) {
								auto _selectedEntity = engine->getEntity(selectedEntityIds[0]);
								if (_selectedEntity != nullptr) {
									sceneEditorTabController->updateEntityDetails(_selectedEntity->getTransformations());
									setGizmoRotation(_selectedEntity->getTransformations());
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
						for (auto selectedEntityId: selectedEntityIds) {
							auto selectedEntity = engine->getEntity(selectedEntityId);
							if (mouseDragging == true && mouseDraggingLastEntity == selectedEntity) {
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
							sceneEditorTabController->unselectEntity(entityToRemove->getId());
							resetEntity(entityToRemove);
						}
					}
					if (selectedEntity != nullptr) {
						if (selectedEntityIdsById.find(selectedEntity->getId()) == selectedEntityIdsById.end()) {
							setStandardEntityColorEffect(selectedEntity);
							setHighlightEntityColorEffect(selectedEntity);
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
								selectedEntity->fromTransformations(sceneEntity->getTransformations());
							}
							setGizmoRotation(selectedEntity->getTransformations());
							sceneEditorTabController->setEntityDetails(selectedEntity->getId());
						} else
						if (selectedEntityIds.size() > 1) {
							setGizmoRotation(Transformations());
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
		if (event.getButton() != MOUSE_BUTTON_NONE) {
			mouseDownLastX = event.getXUnscaled();
			mouseDownLastY = event.getYUnscaled();
		}
	}
	if (keyDelete == true) {
		Console::println("SceneEditorTabView::handleInputEvents(): Backspace");
		removeGizmo();
		removeEntities();
	}
	if (keyControlX == true) {
		Console::println("SceneEditorTabView::handleInputEvents(): CTRL-X");
		removeGizmo();
		copyEntities();
		removeEntities();
	}
	if (keyControlC == true) {
		Console::println("SceneEditorTabView::handleInputEvents(): CTRL-C");
		copyEntities();
	}
	if (keyControlV == true) {
		Console::println("SceneEditorTabView::handleInputEvents(): CTRL-V");
		removeGizmo();
		setPasteMode();
	}

	//
	cameraInputHandler->handleInputEvents();
}

void SceneEditorTabView::display()
{
	if (needGizmoUpdate == true) {
		updateGizmo();
		needGizmoUpdate = false;
	}

	updateSkyPosition();

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
		if ((placeEntityMode == true || pasteMode == true) && engine->getEntityByMousePosition(placeEntityMouseX, placeEntityMouseY, worldCoordinate, entityPickingFilterPlacing) != nullptr) {
			if (placeEntityMode == true) {
				Transformations transformations;
				transformations.setTranslation(worldCoordinate);
				transformations.addRotation(scene->getRotationOrder()->getAxis0(), 0.0f);
				transformations.addRotation(scene->getRotationOrder()->getAxis1(), 0.0f);
				transformations.addRotation(scene->getRotationOrder()->getAxis2(), 0.0f);
				transformations.update();
				if (selectedEngineEntity == nullptr && selectedPrototype != nullptr) {
					selectedEngineEntity = SceneConnector::createEntity(selectedPrototype, "tdme.sceneeditor.placeentity", transformations);
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
					transformations.setTranslation(worldCoordinate);
					transformations.setRotationAngle(scene->getRotationOrder()->getAxisYIndex(), static_cast<float>(placeEntityYRotation) * 90.0f);
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

	//
	updateGrid();

	//
	sceneEditorTabController->updateInfoText(MutableString(engine->getTiming()->getCurrentFPS()).append(" FPS"));

	//
	engine->display();
}

void SceneEditorTabView::initialize()
{
	try {
		sceneEditorTabController = new SceneEditorTabController(this);
		sceneEditorTabController->initialize(editorView->getScreenController()->getScreenNode());
	} catch (Exception& exception) {
		Console::print(string("SceneEditorTabView::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	//
	for (auto i = 1; i < engine->getLightCount(); i++) engine->getLightAt(i)->setEnabled(false);
	auto light0 = engine->getLightAt(0);
	light0->setAmbient(Color4(0.7f, 0.7f, 0.7f, 1.0f));
	light0->setDiffuse(Color4(0.3f, 0.3f, 0.3f, 1.0f));
	light0->setSpecular(Color4(1.0f, 1.0f, 1.0f, 1.0f));
	light0->setPosition(Vector4(0.0f, 20000.0f, 0.0f, 0.0f));
	light0->setSpotDirection(Vector3(0.0f, 0.0f, 0.0f).sub(Vector3(light0->getPosition().getX(), light0->getPosition().getY(), light0->getPosition().getZ())).normalize());
	light0->setConstantAttenuation(0.5f);
	light0->setLinearAttenuation(0.0f);
	light0->setQuadraticAttenuation(0.0f);
	light0->setSpotExponent(0.0f);
	light0->setSpotCutOff(180.0f);
	light0->setEnabled(true);
	auto cam = engine->getCamera();
	SceneConnector::setLights(engine, scene, Vector3());
	SceneConnector::addScene(engine, scene, true, true, true, true);
	updateSky();
	cameraInputHandler->setSceneCenter(scene->getCenter());
	updateGrid();
	// TODO: load settings
}

void SceneEditorTabView::dispose()
{
	engine->dispose();
}

void SceneEditorTabView::updateRendering() {
}

Engine* SceneEditorTabView::getEngine() {
	return engine;
}

void SceneEditorTabView::activate() {
	sceneEditorTabController->setOutlinerAddDropDownContent();
	sceneEditorTabController->setOutlinerContent();
	editorView->getScreenController()->restoreOutlinerState(outlinerState);
	sceneEditorTabController->updateDetails(editorView->getScreenController()->getOutlinerSelection());
}

void SceneEditorTabView::deactivate() {
	editorView->getScreenController()->storeOutlinerState(outlinerState);
}

void SceneEditorTabView::clearScene() {
	SceneConnector::resetEngine(engine, scene);
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
	SceneConnector::addScene(engine, scene, true, true, true, true);
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
	needGizmoUpdate = true;
}

void SceneEditorTabView::onCameraRotation() {
	needGizmoUpdate = true;
}

void SceneEditorTabView::onCameraScale() {
	needGizmoUpdate = true;
}

void SceneEditorTabView::removeSky() {
	engine->removeEntity("tdme.sky");
}

void SceneEditorTabView::updateSky() {
	engine->removeEntity("tdme.sky");
	if (scene->getSkyModel() == nullptr) return;
	auto sky = new Object3D("tdme.sky", scene->getSkyModel());
	sky->setRenderPass(Entity::RENDERPASS_NOFRUSTUMCULLING);
	sky->setShader("sky");
	sky->setFrustumCulling(false);
	sky->setTranslation(Vector3(0.0f, 0.0f, 0.0f));
	sky->setScale(scene->getSkyModelScale());
	sky->update();
	sky->setContributesShadows(false);
	sky->setReceivesShadows(false);
	sky->setExcludeEffectPass(Engine::EFFECTPASS_LIGHTSCATTERING);
	engine->addEntity(sky);
}

void SceneEditorTabView::updateSkyPosition() {
	auto sky = engine->getEntity("tdme.sky");
	if (sky == nullptr) return;
	sky->setTranslation(engine->getCamera()->getLookAt());
	sky->update();
}

void SceneEditorTabView::updateLights() {
	SceneConnector::setLights(engine, scene, Vector3());
}

void SceneEditorTabView::setHighlightEntityColorEffect(Entity* entity)
{
	auto& red = entityColors["red"];
	entity->setEffectColorAdd(Color4(red.colorAddR, red.colorAddG, red.colorAddB, 0.0f));
	entity->setEffectColorMul(Color4(red.colorMulR, red.colorMulG, red.colorMulB, 1.0f));
}

void SceneEditorTabView::setStandardEntityColorEffect(Entity* entity)
{
	auto& color = entityColors["none"];
	entity->setEffectColorAdd(Color4(color.colorAddR, color.colorAddG, color.colorAddB, 0.0f));
	entity->setEffectColorMul(Color4(color.colorMulR, color.colorMulG, color.colorMulB, 1.0f));
	auto sceneEntity = scene->getEntity(entity->getId());
	if (sceneEntity == nullptr) return;
	auto colorProperty = sceneEntity->getProperty("object.color");
	if (colorProperty == nullptr) colorProperty = sceneEntity->getPrototype()->getProperty("object.color");
	if (colorProperty != nullptr) {
		auto entityColorIt = entityColors.find(colorProperty->getValue());
		if (entityColorIt != entityColors.end()) {
			auto& entityColor = entityColorIt->second;
			entity->setEffectColorAdd(Color4(entity->getEffectColorAdd().getRed() + entityColor.colorAddR, entity->getEffectColorAdd().getGreen() + entityColor.colorAddG, entity->getEffectColorAdd().getBlue() + entityColor.colorAddB, 0.0f));
			entity->setEffectColorMul(Color4(entity->getEffectColorMul().getRed() * entityColor.colorMulR, entity->getEffectColorMul().getGreen() * entityColor.colorMulG, entity->getEffectColorMul().getBlue() * entityColor.colorMulB, 1.0f));
		}
	}
}

void SceneEditorTabView::resetEntity(Entity* entity) {
	if (entity == nullptr) return;
	setStandardEntityColorEffect(entity);
	auto sceneEntity = scene->getEntity(entity->getId());
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

void SceneEditorTabView::selectEntities(const vector<string>& entityIds)
{
	removeGizmo();
	for (auto entityIdToRemove: selectedEntityIds) {
		auto entityToRemove = engine->getEntity(entityIdToRemove);
		if (entityToRemove != nullptr) setStandardEntityColorEffect(entityToRemove);
	}
	selectedEntityIds.clear();
	selectedEntityIdsById.clear();
	for (auto entityId: entityIds) {
		Console::println(entityId);
		auto selectedEntity = engine->getEntity(entityId);
		if (selectedEntity == nullptr) continue;
		setStandardEntityColorEffect(selectedEntity);
		setHighlightEntityColorEffect(selectedEntity);
		selectedEntityIds.push_back(entityId);
		selectedEntityIdsById.insert(entityId);
	}

	if (entityIds.size() == 1) {
		auto selectedEntity = engine->getEntity(entityIds[0]);
		if (selectedEntity != nullptr) {
			setGizmoRotation(selectedEntity->getTransformations());
			sceneEditorTabController->setEntityDetails(selectedEntity->getId());
		}
	} else
	if (entityIds.size() > 1) {
		setGizmoRotation(Transformations());
		multipleSelectionTranslation = computeMultipleSelectionPivot();
		sceneEditorTabController->setEntityDetailsMultiple(multipleSelectionTranslation, getSelectedReflectionEnvironmentMappingId());
	}
	updateGizmo();
}

void SceneEditorTabView::unselectEntities()
{
	removeGizmo();
	for (auto entityIdToRemove: selectedEntityIds) {
		auto entityToRemove = engine->getEntity(entityIdToRemove);
		if (entityToRemove == nullptr) continue;
		resetEntity(entityToRemove);
	}
	selectedEntityIds.clear();
	selectedEntityIdsById.clear();
}

void SceneEditorTabView::copyEntities()
{
	copiedEntities.clear();
	for (auto selectedEntityId: selectedEntityIds) {
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
		class ReloadOutlinerWithNewSelectionAction: public Action {
		public:
			void performAction() override {
				sceneEditorTabView->reloadOutliner();
				// select selected entities
				sceneEditorTabView->sceneEditorTabController->unselectEntities();
				for (auto& entityId: entitiesToSelect) {
					sceneEditorTabView->sceneEditorTabController->selectEntity(entityId);
				}
				sceneEditorTabView->selectEntities(entitiesToSelect);
			}
			ReloadOutlinerWithNewSelectionAction(SceneEditorTabView* sceneEditorTabView, const vector<string>& entitiesToSelect): sceneEditorTabView(sceneEditorTabView), entitiesToSelect(entitiesToSelect) {

			}
		private:
			SceneEditorTabView* sceneEditorTabView;
			vector<string> entitiesToSelect;
		};
		Engine::getInstance()->enqueueAction(new ReloadOutlinerWithNewSelectionAction(this, selectedEntityIds));
	}
}

void SceneEditorTabView::placeEntity()
{
	if (selectedPrototype == nullptr) return;

	Transformations sceneEntityTransformations;
	sceneEntityTransformations.setTranslation(placeEntityTranslation);
	sceneEntityTransformations.setScale(Vector3(1.0f, 1.0f, 1.0f));
	sceneEntityTransformations.setPivot(selectedPrototype->getPivot());
	sceneEntityTransformations.addRotation(scene->getRotationOrder()->getAxis0(), 0.0f);
	sceneEntityTransformations.addRotation(scene->getRotationOrder()->getAxis1(), 0.0f);
	sceneEntityTransformations.addRotation(scene->getRotationOrder()->getAxis2(), 0.0f);
	sceneEntityTransformations.setRotationAngle(scene->getRotationOrder()->getAxisYIndex(), placeEntityYRotation * 90.0f);
	sceneEntityTransformations.update();
	for (auto i = 0; i < scene->getEntityCount(); i++) {
		auto sceneEntity = scene->getEntityAt(i);
		if (sceneEntity->getPrototype() == selectedPrototype && sceneEntity->getTransformations().getTranslation().equals(sceneEntityTransformations.getTranslation())) {
			return;
		}
	}
	auto sceneEntity = new SceneEntity(
		selectedPrototype->getName() + "_" + to_string(scene->allocateEntityId()),
		"",
		sceneEntityTransformations,
		selectedPrototype
	);
	scene->addEntity(sceneEntity);
	selectedEntityIds.push_back(sceneEntity->getId());
	auto entity = SceneConnector::createEntity(sceneEntity);
	if (entity != nullptr) {
		resetEntity(entity);
		entity->setPickable(true);
		engine->addEntity(entity);
	}
	scene->update();
	cameraInputHandler->setSceneCenter(Vector3(scene->getCenter().getX(), scene->getBoundingBox()->getMax().getY() + 3.0f, scene->getCenter().getZ()));
}

void SceneEditorTabView::removeEntities()
{
	removeGizmo();
	vector<Entity*> entitiesToRemove;
	for (auto selectedEntityId: selectedEntityIds) {
		Entity* selectedEntity = engine->getEntity(selectedEntityId);
		if (selectedEntity != nullptr && StringTools::startsWith(selectedEntity->getId(), "tdme.sceneeditor.") == false) {
			scene->removeEntity(selectedEntity->getId());
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
	scene->update();
	cameraInputHandler->setSceneCenter(Vector3(scene->getCenter().getX(), scene->getBoundingBox()->getMax().getY() + 3.0f, scene->getCenter().getZ()));

	//
	class ReloadOutlinerAction: public Action {
	public:
		void performAction() override {
			sceneEditorTabView->reloadOutliner(outlinerNode);
		}
		ReloadOutlinerAction(SceneEditorTabView* sceneEditorTabView, const string& outlinerNode): sceneEditorTabView(sceneEditorTabView), outlinerNode(outlinerNode) {

		}
	private:
		SceneEditorTabView* sceneEditorTabView;
		string outlinerNode;
	};
	Engine::getInstance()->enqueueAction(new ReloadOutlinerAction(this, "scene.entities"));
}

void SceneEditorTabView::setPasteMode() {
	unselectEntities();
	sceneEditorTabController->unselectEntities();
	pasteMode = true;
	pasteModeValid = false;
}

void SceneEditorTabView::unsetPasteMode() {
	auto pasteEntityIdx = 0;
	for (auto pasteEntity: copiedEntities) {
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
	for (auto copiedEntity: copiedEntities) {
		auto entity = engine->getEntity(copiedEntity->getId());
		if (entity == nullptr) continue;
		BoundingBox cbv;
		cbv.fromBoundingVolumeWithTransformations(entity->getBoundingBox(), copiedEntity->getTransformations());
		auto& entityBBMinXYZ = cbv.getMin().getArray();
		if (entityBBMinXYZ[0] < pasteEntitiesMinX) pasteEntitiesMinX = entityBBMinXYZ[0];
		if (entityBBMinXYZ[1] < pasteEntitiesMinY) pasteEntitiesMinY = entityBBMinXYZ[1];
		if (entityBBMinXYZ[2] < pasteEntitiesMinZ) pasteEntitiesMinZ = entityBBMinXYZ[2];
		auto& entityBBMaxXYZ = cbv.getMax().getArray();
		if (entityBBMaxXYZ[0] > pasteEntitiesMaxX) pasteEntitiesMaxX = entityBBMaxXYZ[0];
		if (entityBBMaxXYZ[1] > pasteEntitiesMaxY) pasteEntitiesMaxY = entityBBMaxXYZ[1];
		if (entityBBMaxXYZ[2] > pasteEntitiesMaxZ) pasteEntitiesMaxZ = entityBBMaxXYZ[2];
	}
	auto centerX = (pasteEntitiesMaxX - pasteEntitiesMinX) / 2.0f;
	auto centerZ = (pasteEntitiesMaxZ - pasteEntitiesMinZ) / 2.0f;
	auto pasteEntitiesIdx = 0;
	vector<string> entitiesToSelect;
	for (auto copiedEntity: copiedEntities) {
		auto pastePrototype = copiedEntity->getPrototype();
		Transformations sceneEntityTransformations;
		sceneEntityTransformations.fromTransformations(copiedEntity->getTransformations());
		auto entityDiffX = copiedEntity->getTransformations().getTranslation().getX() - pasteEntitiesMinX;
		auto entityDiffY = copiedEntity->getTransformations().getTranslation().getY() - pasteEntitiesMinY;
		auto entityDiffZ = copiedEntity->getTransformations().getTranslation().getZ() - pasteEntitiesMinZ;
		sceneEntityTransformations.setTranslation(
			Vector3(
				placeEntityTranslation.getX() + entityDiffX - centerX,
				placeEntityTranslation.getY() + entityDiffY,
				placeEntityTranslation.getZ() + entityDiffZ - centerZ
			)
		);
		sceneEntityTransformations.update();
		if (displayOnly == false) {
			for (auto i = 0; i < scene->getEntityCount(); i++) {
				auto sceneEntity = scene->getEntityAt(i);
				if (sceneEntity->getPrototype() == pastePrototype && sceneEntity->getTransformations().getTranslation().equals(sceneEntityTransformations.getTranslation())) {
					continue;
				}
			}
		}
		if (displayOnly == false) {
			//
			auto sceneEntityId = pastePrototype->getName() + "_" + to_string(scene->allocateEntityId());
			auto sceneEntity = new SceneEntity(
				sceneEntityId,
				"",
				sceneEntityTransformations,
				pastePrototype
			 );
			BaseProperties* properties = copiedEntity;
			for (int i = 0; i < properties->getPropertyCount(); i++) {
				auto property = properties->getPropertyByIndex(i);
				sceneEntity->addProperty(property->getName(), property->getValue());
			}
			scene->addEntity(sceneEntity);
			auto entity = SceneConnector::createEntity(pastePrototype, sceneEntityId, sceneEntityTransformations);
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
				entity->fromTransformations(sceneEntityTransformations);
			} else {
				entity = SceneConnector::createEntity(pastePrototype, entityId, sceneEntityTransformations);
				if (entity != nullptr) {
					setStandardEntityColorEffect(entity);
					entity->setPickable(true);
					engine->addEntity(entity);
				}
			}
		}
		pasteEntitiesIdx++;
	}

	//
	if (displayOnly == false) {
		//
		class ReloadOutlinerWithNewSelectionAction: public Action {
		public:
			void performAction() override {
				sceneEditorTabView->reloadOutliner();
				// select selected entities
				sceneEditorTabView->sceneEditorTabController->unselectEntities();
				for (auto& entityId: entitiesToSelect) {
					sceneEditorTabView->sceneEditorTabController->selectEntity(entityId);
				}
				sceneEditorTabView->selectEntities(entitiesToSelect);
			}
			ReloadOutlinerWithNewSelectionAction(SceneEditorTabView* sceneEditorTabView, const vector<string>& entitiesToSelect): sceneEditorTabView(sceneEditorTabView), entitiesToSelect(entitiesToSelect) {

			}
		private:
			SceneEditorTabView* sceneEditorTabView;
			vector<string> entitiesToSelect;
		};
		Engine::getInstance()->enqueueAction(new ReloadOutlinerWithNewSelectionAction(this, entitiesToSelect));
	}
}

const Vector3 SceneEditorTabView::computeMultipleSelectionPivot() {
	Vector3 pivot;
	auto entityCount = 0;
	for (auto selectedEntityId: selectedEntityIds) {
		auto selectedEntity = engine->getEntity(selectedEntityId);
		if (selectedEntity != nullptr && StringTools::startsWith(selectedEntity->getId(), "tdme.sceneeditor.") == false) {
			auto sceneEntity = scene->getEntity(selectedEntity->getId());
			if (sceneEntity == nullptr) continue;
			pivot.add(sceneEntity->getTransformations().getTranslation());
			entityCount++;
		}
	}
	if (entityCount > 1) pivot.scale(1.0f / entityCount);
	return pivot;
}

const string SceneEditorTabView::getSelectedReflectionEnvironmentMappingId() {
	string selectedEnvironmentMappingId;
	for (auto selectedEntityId: selectedEntityIds) {
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
	for (auto selectedEntityId: selectedEntityIds) {
		auto selectedEntity = engine->getEntity(selectedEntityId);
		if (selectedEntity == nullptr) continue;
		center.add(selectedEntity->getBoundingBoxTransformed()->getMin().clone().add(selectedEntity->getBoundingBoxTransformed()->getMax()).scale(0.5f));
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
	for (auto i = 0; i < scene->getEntityCount(); i++) {
		auto _sceneEntity = scene->getEntityAt(i);
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
		sceneEditorTabController->showErrorPopUp("Warning", "Prototype is embedded and can not be opened");
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
	Transformations transformations;

	//
	Vector3 gizmoCenter;
	auto entityCount = 0;
	for (auto selectedEntityId: selectedEntityIds) {
		auto selectedEntity = engine->getEntity(selectedEntityId);
		if (selectedEntity != nullptr && StringTools::startsWith(selectedEntity->getId(), "tdme.sceneeditor.") == false) {
			auto sceneEntity = scene->getEntity(selectedEntity->getId());
			if (sceneEntity == nullptr) continue;
			gizmoCenter.add(sceneEntity->getTransformations().getTranslation());
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
		if (selectedSceneEntity != nullptr) transformations.fromTransformations(selectedSceneEntity->getTransformations());
		if (selectedPrototype != nullptr) setGizmoTypeMask(selectedPrototype->getType()->getGizmoTypeMask());
		if (selectedSceneEntity == nullptr || selectedPrototype == nullptr) {
			removeGizmo();
		}
	} else {
		gizmoCenter.scale(1.0f / entityCount);
	}

	//
	Gizmo::updateGizmo(gizmoCenter, transformations);
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
		auto entity = SceneConnector::createEntity(sceneEntity);
		if (entity == nullptr) {
			return false;
		} else {
			setHighlightEntityColorEffect(entity);
			selectedEntityIds.push_back(entity->getId());
			selectedEntityIdsById.insert(entity->getId());
			entity->setPickable(true);
			engine->addEntity(entity);
			//
			class ReloadOutlinerAction: public Action {
			public:
				void performAction() override {
					sceneEditorTabView->reloadOutliner(outlinerNode);
				}
				ReloadOutlinerAction(SceneEditorTabView* sceneEditorTabView, const string& outlinerNode): sceneEditorTabView(sceneEditorTabView), outlinerNode(outlinerNode) {

				}
			private:
				SceneEditorTabView* sceneEditorTabView;
				string outlinerNode;
			};
			Engine::getInstance()->enqueueAction(new ReloadOutlinerAction(this, "scene.entities." + entity->getId()));
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

		sceneEntity->getTransformations().setTranslation(translation);
		sceneEntity->getTransformations().update();
		selectedEntity->fromTransformations(sceneEntity->getTransformations());
	} else
	if (selectedEntityIds.size() > 1) {
		for (auto selectedEntityId: selectedEntityIds) {
			auto selectedEntity = engine->getEntity(selectedEntityId);
			if (selectedEntity == nullptr) continue;
			auto sceneEntity = scene->getEntity(selectedEntity->getId());
			if (sceneEntity == nullptr) continue;

			sceneEntity->getTransformations().setTranslation(
				sceneEntity->getTransformations().getTranslation().clone().add(translation.clone().sub(multipleSelectionTranslation))
			);
			sceneEntity->getTransformations().update();
			selectedEntity->fromTransformations(sceneEntity->getTransformations());
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
		sceneEntity->getTransformations().getRotation(scene->getRotationOrder()->getAxisXIndex()).setAngle(rotation.getX());
		sceneEntity->getTransformations().getRotation(scene->getRotationOrder()->getAxisYIndex()).setAngle(rotation.getY());
		sceneEntity->getTransformations().getRotation(scene->getRotationOrder()->getAxisZIndex()).setAngle(rotation.getZ());
		sceneEntity->getTransformations().update();
		selectedEntity->fromTransformations(sceneEntity->getTransformations());
	} else
	if (selectedEntityIds.size() > 1) {
		for (auto selectedEntityId: selectedEntityIds) {
			auto selectedEntity = engine->getEntity(selectedEntityId);
			if (selectedEntity == nullptr) continue;
			auto sceneEntity = scene->getEntity(selectedEntity->getId());
			if (sceneEntity == nullptr) continue;
			if ((sceneEntity->getPrototype()->getType()->getGizmoTypeMask() & Gizmo::GIZMOTYPE_ROTATE) == Gizmo::GIZMOTYPE_ROTATE) {
				sceneEntity->getTransformations().getRotation(scene->getRotationOrder()->getAxisXIndex()).setAngle(sceneEntity->getTransformations().getRotation(scene->getRotationOrder()->getAxisXIndex()).getAngle() + (rotation.getX() - multipleSelectionRotation.getX()));
				sceneEntity->getTransformations().getRotation(scene->getRotationOrder()->getAxisYIndex()).setAngle(sceneEntity->getTransformations().getRotation(scene->getRotationOrder()->getAxisYIndex()).getAngle() + (rotation.getY() - multipleSelectionRotation.getY()));
				sceneEntity->getTransformations().getRotation(scene->getRotationOrder()->getAxisZIndex()).setAngle(sceneEntity->getTransformations().getRotation(scene->getRotationOrder()->getAxisZIndex()).getAngle() + (rotation.getZ() - multipleSelectionRotation.getZ()));
			}
			sceneEntity->getTransformations().update();
			selectedEntity->fromTransformations(sceneEntity->getTransformations());
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

		sceneEntity->getTransformations().setScale(Vector3(scale));
		sceneEntity->getTransformations().update();
		selectedEntity->fromTransformations(sceneEntity->getTransformations());
	} else
	if (selectedEntityIds.size() > 1) {
		for (auto selectedEntityId: selectedEntityIds) {
			auto selectedEntity = engine->getEntity(selectedEntityId);
			if (selectedEntity == nullptr) continue;
			auto sceneEntity = scene->getEntity(selectedEntity->getId());
			if (sceneEntity == nullptr) continue;

			sceneEntity->getTransformations().setScale(sceneEntity->getTransformations().getScale().clone().scale(scale / multipleSelectionScale));
			sceneEntity->getTransformations().update();
			selectedEntity->fromTransformations(sceneEntity->getTransformations());
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

	for (auto selectedEntityId: selectedEntityIds) {
		auto selectedEntity = engine->getEntity(selectedEntityId);
		if (selectedEntity == nullptr) continue;
		auto sceneEntity = scene->getEntity(selectedEntity->getId());
		if (sceneEntity == nullptr) continue;

		auto object3D = dynamic_cast<Object3D*>(selectedEntity);
		if (object3D != nullptr) object3D->setReflectionEnvironmentMappingId(reflectionEnvironmentMappingId);
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
		entity = new Object3D(entityId, gridModel);
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
			setHighlightEntityColorEffect(entity);
		} else {
			setStandardEntityColorEffect(entity);
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
		sceneLibrary->addPrototype(prototype);
	} catch (Exception& exception) {
		Console::println(string("SceneEditorTabView::addPrototype(): An error occurred: ") + exception.what());;
		sceneEditorTabController->showErrorPopUp("Warning", (string(exception.what())));
	}
	reloadOutliner("scene.prototypes." + to_string(prototype->getId()));
}
