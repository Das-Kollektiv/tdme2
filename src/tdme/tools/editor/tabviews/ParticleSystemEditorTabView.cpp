#include <tdme/tools/editor/tabviews/ParticleSystemEditorTabView.h>

#include <memory>
#include <string>

#include <agui/agui.h>
#include <agui/gui/events/GUIKeyboardEvent.h>
#include <agui/gui/events/GUIMouseEvent.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/GUI.h>

#include <tdme/tdme.h>
#include <tdme/audio/Audio.h>
#include <tdme/audio/Sound.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/fileio/prototypes/PrototypeWriter.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/Prototype_Type.h>
#include <tdme/engine/prototype/PrototypeAudio.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_BoundingBoxParticleEmitter.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_CircleParticleEmitter.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_CircleParticleEmitterPlaneVelocity.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_Emitter.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_PointParticleEmitter.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_SphereParticleEmitter.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/ParticleSystem.h>
#include <tdme/engine/ParticleSystemGroup.h>
#include <tdme/engine/SceneConnector.h>
#include <tdme/engine/Timing.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/engine/tools/CameraRotationInputHandler.h>
#include <tdme/engine/tools/CameraRotationInputHandlerEventHandler.h>
#include <tdme/engine/tools/FileSystemTools.h>
#include <tdme/engine/tools/ThumbnailTool.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeDisplaySubController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypePhysicsSubController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeSoundsSubController.h>
#include <tdme/tools/editor/tabcontrollers/ParticleSystemEditorTabController.h>
#include <tdme/tools/editor/tabviews/subviews/PrototypeDisplaySubView.h>
#include <tdme/tools/editor/tabviews/subviews/PrototypePhysicsSubView.h>
#include <tdme/tools/editor/tabviews/subviews/PrototypeSoundsSubView.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/views/PlayableSoundView.h>
#include <tdme/utilities/Character.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/Time.h>

using std::make_unique;
using std::string;
using std::unique_ptr;

using tdme::tools::editor::tabviews::ParticleSystemEditorTabView;

using agui::gui::events::GUIKeyboardEvent;
using agui::gui::events::GUIMouseEvent;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::GUI;

using tdme::audio::Audio;
using tdme::audio::Sound;
using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::fileio::prototypes::PrototypeWriter;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeAudio;
using tdme::engine::prototype::PrototypeParticleSystem_BoundingBoxParticleEmitter;
using tdme::engine::prototype::PrototypeParticleSystem_CircleParticleEmitter;
using tdme::engine::prototype::PrototypeParticleSystem_CircleParticleEmitterPlaneVelocity;
using tdme::engine::prototype::PrototypeParticleSystem_Emitter;
using tdme::engine::prototype::PrototypeParticleSystem_PointParticleEmitter;
using tdme::engine::prototype::PrototypeParticleSystem_SphereParticleEmitter;
using tdme::engine::Engine;
using tdme::engine::ParticleSystem;
using tdme::engine::ParticleSystemGroup;
using tdme::engine::SceneConnector;
using tdme::engine::Timing;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::engine::tools::CameraRotationInputHandler;
using tdme::engine::tools::CameraRotationInputHandlerEventHandler;
using tdme::engine::tools::FileSystemTools;
using tdme::engine::tools::ThumbnailTool;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeDisplaySubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeSoundsSubController;
using tdme::tools::editor::tabcontrollers::ParticleSystemEditorTabController;
using tdme::tools::editor::tabviews::subviews::PrototypeDisplaySubView;
using tdme::tools::editor::tabviews::subviews::PrototypePhysicsSubView;
using tdme::tools::editor::tabviews::subviews::PrototypeSoundsSubView;
using tdme::tools::editor::tabviews::TabView;
using tdme::tools::editor::views::EditorView;
using tdme::tools::editor::views::PlayableSoundView;
using tdme::utilities::Character;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::StringTools;
using tdme::utilities::Time;

ParticleSystemEditorTabView::ParticleSystemEditorTabView(EditorView* editorView, const string& tabId, Prototype* prototype): Gizmo(nullptr, "spsv")
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->popUps = editorView->getPopUps();
	this->prototype = unique_ptr<Prototype>(prototype);
	this->audio = Audio::getInstance();
	this->engine = unique_ptr<Engine>(Engine::createOffScreenInstance(512, 512, true, true, true));
	this->engine->setShadowMapLightEyeDistanceScale(0.1f);
	this->engine->setSceneColor(Color4(39.0f / 255.0f, 39.0f / 255.0f, 39.0f / 255.0f, 1.0f));
	this->cameraRotationInputHandler = make_unique<CameraRotationInputHandler>(engine.get(), this);
	this->audioStarted = -1LL;
	this->audioOffset = -1LL;
	Gizmo::setEngine(engine.get());
	initParticleSystem();
	outlinerState.expandedOutlinerParentOptionValues.push_back("prototype");
}

ParticleSystemEditorTabView::~ParticleSystemEditorTabView() {
}

void ParticleSystemEditorTabView::handleInputEvents()
{
	if (prototypePhysicsView->isEditingBoundingVolume(prototype.get()) == false) {
		for (auto& event: engine->getGUI()->getKeyboardEvents()) {
			if (event.isProcessed() == true) continue;
			auto isKeyDown = event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED;
			if (Character::toLowerCase(event.getKeyChar()) == '1') { if (isKeyDown == true) setGizmoType(GIZMOTYPE_ALL); updateGizmo(); event.setProcessed(true); }
			if (Character::toLowerCase(event.getKeyChar()) == '2') { if (isKeyDown == true) setGizmoType(GIZMOTYPE_TRANSLATE); updateGizmo(); event.setProcessed(true); }
			if (Character::toLowerCase(event.getKeyChar()) == '3') { if (isKeyDown == true) setGizmoType(GIZMOTYPE_ROTATE); updateGizmo(); event.setProcessed(true); }
			if (Character::toLowerCase(event.getKeyChar()) == '4') { if (isKeyDown == true) setGizmoType(GIZMOTYPE_SCALE); updateGizmo(); event.setProcessed(true); }
		}
		for (auto& event: engine->getGUI()->getMouseEvents()) {
			if (event.isProcessed() == true) continue;

			if (event.getButton() == MOUSE_BUTTON_LEFT) {
				if (event.getType() == GUIMouseEvent::MOUSEEVENT_RELEASED) {
					auto selectedEntity = engine->getEntity("model");
					auto psg = dynamic_cast<ParticleSystemGroup*>(selectedEntity);
					if (psg != nullptr) selectedEntity = psg->getParticleSystems()[particleSystemIdx];
					if (getGizmoMode() != GIZMOMODE_NONE) {
						if (selectedEntity != nullptr) applyParticleSystemTransform(dynamic_cast<ParticleSystem*>(selectedEntity), false);
						setGizmoMode(GIZMOMODE_NONE);
						updateGizmo();
					}
					totalDeltaScale.set(0.0, 0.0f, 0.0f);
					event.setProcessed(true);
				} else
				if (event.getType() == GUIMouseEvent::MOUSEEVENT_PRESSED) {
					Node* selectedEntityNode = nullptr;
					ParticleSystem* selectedSubParticleSystem = nullptr;
					Entity* selectedEntity = nullptr;
					if (getGizmoMode() == GIZMOMODE_NONE) selectedEntity = engine->getEntityByMousePosition(event.getXUnscaled(), event.getYUnscaled(), nullptr, &selectedEntityNode, &selectedSubParticleSystem);
					if (getGizmoMode() == GIZMOMODE_NONE && selectedEntity == nullptr) {
						setParticleSystemIndex(-1);
						event.setProcessed(true);
					} else
					if (determineGizmoMode(selectedEntity, selectedEntityNode) == true) {
						event.setProcessed(true);
					} else
					if (selectedEntity != nullptr) {
						auto psg = dynamic_cast<ParticleSystemGroup*>(selectedEntity);
						if (psg != nullptr && selectedSubParticleSystem != nullptr) {
							auto particleSystemIdx = 0;
							for (auto pse: psg->getParticleSystems()) {
								if (pse == selectedSubParticleSystem) {
									setParticleSystemIndex(particleSystemIdx);
									break;
								}
								particleSystemIdx++;
							}
						} else {
							setParticleSystemIndex(0);
						}
						event.setProcessed(true);
					}
				} else
				if (event.getType() == GUIMouseEvent::MOUSEEVENT_DRAGGED) {
					if (getGizmoMode() != GIZMOMODE_NONE) {
						Vector3 deltaTranslation;
						Vector3 deltaRotation;
						Vector3 deltaScale;
						if (determineGizmoDeltaTransformations(event.getXUnscaled(), event.getYUnscaled(), deltaTranslation, deltaRotation, deltaScale) == true) {
							totalDeltaScale.add(deltaScale.clone().sub(Vector3(1.0f, 1.0f, 1.0f)));
							auto gizmoEntity = getGizmoObject();
							auto selectedEntity = engine->getEntity("model");
							auto psg = dynamic_cast<ParticleSystemGroup*>(selectedEntity);
							if (psg != nullptr) selectedEntity = psg->getParticleSystems()[particleSystemIdx];
							if (gizmoEntity != nullptr && selectedEntity != nullptr) {
								selectedEntity->setTranslation(selectedEntity->getTranslation().clone().add(deltaTranslation));
								selectedEntity->update();
								auto localTransformations = dynamic_cast<ParticleSystem*>(selectedEntity)->getLocalTransform();
								localTransformations.setScale(localTransformations.getScale().clone().scale(deltaScale));
								if (deltaRotation.computeLengthSquared() > Math::square(Math::EPSILON) * 3.0f) {
									if (localTransformations.getRotationCount() == 0) {
										localTransformations.addRotation(Rotation::Z_AXIS, 0.0f);
										localTransformations.addRotation(Rotation::Y_AXIS, 0.0f);
										localTransformations.addRotation(Rotation::X_AXIS, 0.0f);
									}
									localTransformations.setRotationAngle(0, localTransformations.getRotationAngle(0) + deltaRotation[2]);
									localTransformations.setRotationAngle(1, localTransformations.getRotationAngle(1) + deltaRotation[1]);
									localTransformations.setRotationAngle(2, localTransformations.getRotationAngle(2) + deltaRotation[0]);
								}
								localTransformations.update();
								dynamic_cast<ParticleSystem*>(selectedEntity)->setLocalTransform(localTransformations);
								setGizmoRotation(localTransformations);
								applyParticleSystemTransform(dynamic_cast<ParticleSystem*>(selectedEntity), true);
							}
							if (Math::abs(deltaTranslation.getX()) > Math::EPSILON ||
								Math::abs(deltaTranslation.getY()) > Math::EPSILON ||
								Math::abs(deltaTranslation.getZ()) > Math::EPSILON) {
								updateGizmo();
							}
						}
						event.setProcessed(true);
					}
				}
			}
		}
	} else {
		prototypePhysicsView->handleInputEvents(prototype.get());
	}
	cameraRotationInputHandler->handleInputEvents();
}

void ParticleSystemEditorTabView::display()
{
	// audio
	if (audioOffset > 0 && Time::getCurrentMillis() - audioStarted >= audioOffset) {
		auto sound = audio->getEntity("sound");
		if (sound != nullptr) sound->play();
		audioOffset = -1LL;
	}

	//
	particleSystemEditorTabController->updateInfoText(MutableString(engine->getTiming()->getAvarageFPS()).append(" FPS"));

	// rendering
	prototypeDisplayView->display(prototype.get());
	prototypePhysicsView->display(prototype.get());
	engine->display();
}

void ParticleSystemEditorTabView::initialize()
{
	try {
		particleSystemEditorTabController = make_unique<ParticleSystemEditorTabController>(this);
		particleSystemEditorTabController->initialize(editorView->getScreenController()->getScreenNode());
		prototypePhysicsView = particleSystemEditorTabController->getPrototypePhysicsSubController()->getView();
		prototypeDisplayView = particleSystemEditorTabController->getPrototypeDisplaySubController()->getView();
		prototypeSoundsView = particleSystemEditorTabController->getPrototypeSoundsSubController()->getView();
	} catch (Exception& exception) {
		Console::printLine("ParticleSystemEditorTabView::initialize(): An error occurred: " + string(exception.what()));
	}
	// TODO: load settings
	if (prototypePhysicsView != nullptr) prototypePhysicsView->setObjectScale(objectScale);
}

void ParticleSystemEditorTabView::dispose()
{
	engine->dispose();
}

void ParticleSystemEditorTabView::updateRendering() {
}

Engine* ParticleSystemEditorTabView::getEngine() {
	return engine.get();
}

void ParticleSystemEditorTabView::activate() {
	particleSystemEditorTabController->setOutlinerAddDropDownContent();
	particleSystemEditorTabController->setOutlinerContent();
	editorView->getScreenController()->restoreOutlinerState(outlinerState);
	particleSystemEditorTabController->updateDetails(editorView->getScreenController()->getOutlinerSelection());
}

void ParticleSystemEditorTabView::deactivate() {
	editorView->getScreenController()->storeOutlinerState(outlinerState);
}

void ParticleSystemEditorTabView::reloadOutliner() {
	particleSystemEditorTabController->setOutlinerContent();
	particleSystemEditorTabController->updateDetails(editorView->getScreenController()->getOutlinerSelection());
}

void ParticleSystemEditorTabView::onCameraRotation() {
	if (prototypePhysicsView->isEditingBoundingVolume(prototype.get()) == true) prototypePhysicsView->updateGizmo(prototype.get());
	if (getParticleSystemIndex() != -1) updateGizmo();
}

void ParticleSystemEditorTabView::onCameraScale() {
	if (prototypePhysicsView->isEditingBoundingVolume(prototype.get()) == true) prototypePhysicsView->updateGizmo(prototype.get());
	if (getParticleSystemIndex() != -1) updateGizmo();
}

void ParticleSystemEditorTabView::playSound(const string& soundId) {
	audio->removeEntity("sound");
	auto soundDefinition = prototype->getSound(soundId);
	if (soundDefinition != nullptr && soundDefinition->getFileName().length() > 0) {
		auto pathName = PrototypeReader::getResourcePathName(
			FileSystemTools::getPathName(prototype->getFileName()),
			soundDefinition->getFileName()
		);
		auto fileName = FileSystemTools::getFileName(soundDefinition->getFileName());
		auto sound = new Sound(
			"sound",
			pathName,
			fileName
		);
		sound->setGain(soundDefinition->getGain());
		sound->setPitch(soundDefinition->getPitch());
		sound->setLooping(soundDefinition->isLooping());
		sound->setFixed(true);
		audio->addEntity(sound);
		audioStarted = Time::getCurrentMillis();
		audioOffset = -1LL;
		if (soundDefinition->getOffset() <= 0) {
			sound->play();
		} else {
			audioOffset = soundDefinition->getOffset();
		}
	}
}

void ParticleSystemEditorTabView::stopSound() {
	audio->removeEntity("sound");
}

void ParticleSystemEditorTabView::initParticleSystem() {
	ThumbnailTool::setupPrototype(prototype.get(), engine.get(), cameraRotationInputHandler->getLookFromRotations(), 1, objectScale, cameraRotationInputHandler.get());
	if (prototypePhysicsView != nullptr) prototypePhysicsView->setObjectScale(objectScale);
}

void ParticleSystemEditorTabView::uninitParticleSystem() {
	engine->removeEntity("model");
	removeGizmo();
}

int ParticleSystemEditorTabView::getParticleSystemIndex() {
	return particleSystemIdx;
}

void ParticleSystemEditorTabView::setParticleSystemIndex(int idx, bool changeOutlinerSelection) {
	if (particleSystemIdx == idx) return;
	particleSystemIdx = idx;
	totalDeltaScale.set(0.0, 0.0f, 0.0f);
	if (particleSystemIdx == -1) {
		if (changeOutlinerSelection == true) {
			editorView->getScreenController()->setOutlinerSelection("particlesystems");
			editorView->getScreenController()->getScreenNode()->forwardChange(required_dynamic_cast<GUIElementNode*>(editorView->getScreenController()->getScreenNode()->getNodeById("selectbox_outliner")));
		}
		removeGizmo();
	} else {
		if (changeOutlinerSelection == true) {
			editorView->getScreenController()->setOutlinerSelection("particlesystems." + to_string(idx));
			editorView->getScreenController()->getScreenNode()->forwardChange(required_dynamic_cast<GUIElementNode*>(editorView->getScreenController()->getScreenNode()->getNodeById("selectbox_outliner")));
		}
		updateGizmo();
	}
}

void ParticleSystemEditorTabView::updateGizmo() {
	auto selectedEntity = engine->getEntity("model");
	auto psg = dynamic_cast<ParticleSystemGroup*>(selectedEntity);
	if (psg != nullptr) {
		selectedEntity = particleSystemIdx >= psg->getParticleSystems().size()?nullptr:psg->getParticleSystems()[particleSystemIdx];
	} else {
		if (particleSystemIdx > 0) selectedEntity = nullptr;
	}
	auto pse = dynamic_cast<ParticleSystem*>(selectedEntity);
	if (selectedEntity != nullptr) {
		if (pse != nullptr) {
			Gizmo::updateGizmo(pse->getEmitter()->getCenter().clone().scale(objectScale).add(selectedEntity->getTranslation()), selectedEntity->getTransform());
		} else {
			Gizmo::updateGizmo(selectedEntity->getWorldBoundingBox()->getCenter(), selectedEntity->getTransform());
		}
	} else {
		removeGizmo();
	}
}

void ParticleSystemEditorTabView::setGizmoRotation(const Transform& transform) {
	Gizmo::setGizmoRotation(transform);
}

void ParticleSystemEditorTabView::applyParticleSystemTransform(ParticleSystem* particleSystemEntity, bool guiOnly) {
	{
		auto transform = particleSystemEntity->getTransform();
		auto localTransform = particleSystemEntity->getLocalTransform();
		auto objectScaleInverted = Vector3(
			1.0f / objectScale.getX(),
			1.0f / objectScale.getY(),
			1.0f / objectScale.getZ()
		);
		transform.setScale(objectScaleInverted);
		transform.update();
		auto particleSystem = prototype->getParticleSystemAt(particleSystemIdx);
		auto emitterType = particleSystem->getEmitter();
		if (emitterType == PrototypeParticleSystem_Emitter::NONE) {
			// no op
		} else
		if (emitterType == PrototypeParticleSystem_Emitter::POINT_PARTICLE_EMITTER) {
			auto emitter = particleSystem->getPointParticleEmitter();
			auto position = transform.getTranslation().clone().scale(objectScaleInverted).add(emitter->getPosition());
			if (guiOnly == false) {
				emitter->setPosition(position);
			} else {
				particleSystemEditorTabController->updatePointParticleSystemEmitter(position);
			}
		} else
		if (emitterType == PrototypeParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) {
			auto emitter = particleSystem->getBoundingBoxParticleEmitters();
			auto center = transform.getTranslation().clone().scale(objectScaleInverted).add(emitter->getObbCenter());
			auto axis0 = emitter->getObbAxis0().clone().scale(emitter->getObbHalfextension().getX() * 2.0f);
			auto axis1 = emitter->getObbAxis1().clone().scale(emitter->getObbHalfextension().getY() * 2.0f);
			auto axis2 = emitter->getObbAxis2().clone().scale(emitter->getObbHalfextension().getZ() * 2.0f);
			auto halfExtension = emitter->getObbHalfextension();
			axis0 = localTransform.getTransformMatrix().multiplyNoTranslation(axis0);
			axis1 = localTransform.getTransformMatrix().multiplyNoTranslation(axis1);
			axis2 = localTransform.getTransformMatrix().multiplyNoTranslation(axis2);
			halfExtension.set(
				Vector3(
					Math::clamp(axis0.computeLength() / 2.0f, 0.01f, 1000.0f),
					Math::clamp(axis1.computeLength() / 2.0f, 0.01f, 1000.0f),
					Math::clamp(axis2.computeLength() / 2.0f, 0.01f, 1000.0f)
				)
			);
			axis0.normalize();
			axis1.normalize();
			axis2.normalize();
			if (guiOnly == false) {
				emitter->setObbCenter(center);
				emitter->setObbAxis0(axis0);
				emitter->setObbAxis1(axis1);
				emitter->setObbAxis2(axis2);
				emitter->setObbHalfextension(halfExtension);
			} else {
				particleSystemEditorTabController->updateBoundingBoxParticleSystemEmitter(center, axis0, axis1, axis2, halfExtension);
			}
		} else
		if (emitterType == PrototypeParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) {
			auto emitter = particleSystem->getCircleParticleEmitter();
			auto center = transform.getTranslation().clone().scale(objectScaleInverted).add(emitter->getCenter());
			auto axis0 = emitter->getAxis0();
			auto axis1 = emitter->getAxis1();
			axis0 = localTransform.getTransformMatrix().multiplyNoTranslation(axis0).normalize();
			axis1 = localTransform.getTransformMatrix().multiplyNoTranslation(axis1).normalize();
			auto scale = 1.0f;
			if (Math::abs(totalDeltaScale.getX()) > Math::abs(totalDeltaScale.getY()) &&
				Math::abs(totalDeltaScale.getX()) > Math::abs(totalDeltaScale.getZ())) {
				scale+= totalDeltaScale.getX();
			} else
			if (Math::abs(totalDeltaScale.getY()) > Math::abs(totalDeltaScale.getX()) &&
				Math::abs(totalDeltaScale.getY()) > Math::abs(totalDeltaScale.getZ())) {
				scale+= totalDeltaScale.getY();
			} else
			if (Math::abs(totalDeltaScale.getZ()) > Math::abs(totalDeltaScale.getX()) &&
				Math::abs(totalDeltaScale.getZ()) > Math::abs(totalDeltaScale.getY())) {
				scale+= totalDeltaScale.getZ();
			}
			auto radius = Math::clamp(emitter->getRadius() * Math::abs(scale), 0.01f, 1000.0f);
			if (guiOnly == false) {
				emitter->setCenter(center);
				emitter->setAxis0(axis0);
				emitter->setAxis1(axis1);
				emitter->setRadius(radius);
			} else {
				particleSystemEditorTabController->updateCircleParticleSystemEmitter(center, axis0, axis1, radius);
			}
		} else
		if (emitterType == PrototypeParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) {
			auto emitter = particleSystem->getCircleParticleEmitterPlaneVelocity();
			auto center = transform.getTranslation().clone().scale(objectScaleInverted).add(emitter->getCenter());
			auto axis0 = emitter->getAxis0();
			auto axis1 = emitter->getAxis1();
			axis0 = localTransform.getTransformMatrix().multiplyNoTranslation(axis0).normalize();
			axis1 = localTransform.getTransformMatrix().multiplyNoTranslation(axis1).normalize();
			auto scale = 1.0f;
			if (Math::abs(totalDeltaScale.getX()) > Math::abs(totalDeltaScale.getY()) &&
				Math::abs(totalDeltaScale.getX()) > Math::abs(totalDeltaScale.getZ())) {
				scale+= totalDeltaScale.getX();
			} else
			if (Math::abs(totalDeltaScale.getY()) > Math::abs(totalDeltaScale.getX()) &&
				Math::abs(totalDeltaScale.getY()) > Math::abs(totalDeltaScale.getZ())) {
				scale+= totalDeltaScale.getY();
			} else
			if (Math::abs(totalDeltaScale.getZ()) > Math::abs(totalDeltaScale.getX()) &&
				Math::abs(totalDeltaScale.getZ()) > Math::abs(totalDeltaScale.getY())) {
				scale+= totalDeltaScale.getZ();
			}
			auto radius = Math::clamp(emitter->getRadius() * Math::abs(scale), 0.01f, 1000.0f);
			if (guiOnly == false) {
				emitter->setCenter(center);
				emitter->setAxis0(axis0);
				emitter->setAxis1(axis1);
				emitter->setRadius(radius);
			} else {
				particleSystemEditorTabController->updateRadialParticleSystemEmitter(center, axis0, axis1, radius);
			}
		} else
		if (emitterType == PrototypeParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER) {
			auto emitter = particleSystem->getSphereParticleEmitter();
			auto center = transform.getTranslation().clone().scale(objectScaleInverted).add(emitter->getCenter());
			auto scale = 1.0f;
			if (Math::abs(totalDeltaScale.getX()) > Math::abs(totalDeltaScale.getY()) &&
				Math::abs(totalDeltaScale.getX()) > Math::abs(totalDeltaScale.getZ())) {
				scale+= totalDeltaScale.getX();
			} else
			if (Math::abs(totalDeltaScale.getY()) > Math::abs(totalDeltaScale.getX()) &&
				Math::abs(totalDeltaScale.getY()) > Math::abs(totalDeltaScale.getZ())) {
				scale+= totalDeltaScale.getY();
			} else
			if (Math::abs(totalDeltaScale.getZ()) > Math::abs(totalDeltaScale.getX()) &&
				Math::abs(totalDeltaScale.getZ()) > Math::abs(totalDeltaScale.getY())) {
				scale+= totalDeltaScale.getZ();
			}
			auto radius = Math::clamp(emitter->getRadius() * Math::abs(scale), 0.01f, 1000.0f);
			if (guiOnly == false) {
				emitter->setCenter(center);
				emitter->setRadius(radius);
			} else {
				particleSystemEditorTabController->updateSphereParticleSystemEmitter(center, radius);
			}
		} else {
			Console::printLine("SharedParticleSystemView::applyParticleSystemTransform(): unknown particle system emitter '" + particleSystem->getEmitter()->getName() + "'");
		}
	}
	if (guiOnly == false) {
		particleSystemEditorTabController->updateDetails(editorView->getScreenController()->getOutlinerSelection());
		auto modelEntity = engine->getEntity("model");
		if (modelEntity != nullptr) engine->removeEntity("model");
		Transform transform;
		transform.setScale(objectScale);
		transform.update();
		modelEntity = SceneConnector::createEntity(prototype.get(), "model", transform);
		if (modelEntity != nullptr) {
			modelEntity->setPickable(true);
			engine->addEntity(modelEntity);
		}
	}
}

void ParticleSystemEditorTabView::saveFile(const string& pathName, const string& fileName) {
	PrototypeWriter::write(pathName, fileName, prototype.get());
}
