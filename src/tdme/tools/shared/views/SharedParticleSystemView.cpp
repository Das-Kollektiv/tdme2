#include <tdme/tools/shared/views/SharedParticleSystemView.h>

#include <string>

#include <tdme/audio/Audio.h>
#include <tdme/audio/Sound.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/ParticleSystemEntity.h>
#include <tdme/engine/ParticleSystemGroup.h>
#include <tdme/engine/PartitionNone.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIKeyboardEvent_Type.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/events/GUIMouseEvent_Type.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/leveleditor/logic/Level.h>
#include <tdme/tools/shared/controller/EntityDisplaySubScreenController.h>
#include <tdme/tools/shared/controller/EntityPhysicsSubScreenController.h>
#include <tdme/tools/shared/controller/EntitySoundsSubScreenController.h>
#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/tools/shared/controller/ParticleSystemScreenController.h>
#include <tdme/tools/shared/files/ModelMetaDataFileExport.h>
#include <tdme/tools/shared/files/ModelMetaDataFileImport.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntity_EntityType.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_CircleParticleEmitter.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_Emitter.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_PointParticleEmitter.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_SphereParticleEmitter.h>
#include <tdme/tools/shared/model/LevelEditorEntityAudio.h>
#include <tdme/tools/shared/model/PropertyModelClass.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/tools/shared/views/CameraRotationInputHandler.h>
#include <tdme/tools/shared/views/EntityPhysicsView.h>
#include <tdme/tools/shared/views/EntityDisplayView.h>
#include <tdme/tools/shared/views/EntitySoundsView.h>
#include <tdme/tools/shared/views/Gizmo.h>
#include <tdme/tools/shared/views/PlayableSoundView.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/shared/views/View.h>
#include <tdme/utils/Character.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>
#include <tdme/utils/Properties.h>
#include <tdme/utils/StringUtils.h>

using std::string;

using tdme::tools::shared::views::SharedParticleSystemView;

using tdme::audio::Audio;
using tdme::audio::Sound;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::ParticleSystemEntity;
using tdme::engine::ParticleSystemGroup;
using tdme::engine::PartitionNone;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::gui::GUI;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIKeyboardEvent_Type;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::events::GUIMouseEvent_Type;
using tdme::math::Vector3;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::leveleditor::logic::Level;
using tdme::tools::shared::controller::EntityDisplaySubScreenController;
using tdme::tools::shared::controller::EntityPhysicsSubScreenController;
using tdme::tools::shared::controller::EntitySoundsSubScreenController;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::controller::ParticleSystemScreenController;
using tdme::tools::shared::files::ModelMetaDataFileExport;
using tdme::tools::shared::files::ModelMetaDataFileImport;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Emitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_SphereParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Emitter;
using tdme::tools::shared::model::LevelEditorEntityAudio;
using tdme::tools::shared::model::PropertyModelClass;
using tdme::tools::shared::tools::Tools;
using tdme::tools::shared::views::CameraRotationInputHandler;
using tdme::tools::shared::views::EntityPhysicsView;
using tdme::tools::shared::views::EntityDisplayView;
using tdme::tools::shared::views::EntitySoundsView;
using tdme::tools::shared::views::Gizmo;
using tdme::tools::shared::views::PlayableSoundView;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::View;
using tdme::utils::Character;
using tdme::utils::Console;
using tdme::utils::Exception;
using tdme::utils::Properties;
using tdme::utils::StringUtils;

SharedParticleSystemView::SharedParticleSystemView(PopUps* popUps): Gizmo(Engine::getInstance())
{
	this->popUps = popUps;
	engine = Engine::getInstance();
	audio = Audio::getInstance();
	particleSystemScreenController = nullptr;
	entityDisplayView = nullptr;
	entityPhysicsView = nullptr;
	entitySoundsView = nullptr;
	loadParticleSystemRequested = false;
	initParticleSystemRequested = false;
	updateParticleSystemRequested = false;
	particleSystemFile = "";
	cameraRotationInputHandler = new CameraRotationInputHandler(engine);
	entity = new LevelEditorEntity(
		-1,
		LevelEditorEntity_EntityType::PARTICLESYSTEM,
		"Untitled",
		"",
		"Untitled.tps",
		"",
		"",
		nullptr,
		Vector3()
	);
	entity->setDefaultBoundingVolumes();
}

SharedParticleSystemView::~SharedParticleSystemView() {
	delete cameraRotationInputHandler;
}

PopUps* SharedParticleSystemView::getPopUpsViews()
{
	return popUps;
}

LevelEditorEntity* SharedParticleSystemView::getEntity()
{
	return entity;
}

void SharedParticleSystemView::reset()
{
	engine->reset();
}

void SharedParticleSystemView::setEntity(LevelEditorEntity* entity)
{
	engine->reset();
	this->entity = entity;
	this->particleSystemIdx = 0;
	initParticleSystemRequested = true;
}

void SharedParticleSystemView::initParticleSystemRequest()
{
	initParticleSystemRequested = true;
}

void SharedParticleSystemView::updateParticleSystemRequest() {
	updateParticleSystemRequested = true;
}

void SharedParticleSystemView::initParticleSystem()
{
	if (entity == nullptr)
		return;

	particleSystemFile = entity->getEntityFileName();
	Tools::setupEntity(entity, engine, cameraRotationInputHandler->getLookFromRotations(), cameraRotationInputHandler->getScale(), 1, objectScale);
	Tools::oseThumbnail(entity);
	updateGUIElements();
}

const string SharedParticleSystemView::getFileName()
{
	if (particleSystemFile.length() == 0) return particleSystemFile;
	return FileSystem::getInstance()->getFileName(particleSystemFile);
}

void SharedParticleSystemView::loadFile(const string& pathName, const string& fileName)
{
	loadParticleSystemRequested = true;
	particleSystemFile = pathName + "/" + fileName;
}

void SharedParticleSystemView::saveFile(const string& pathName, const string& fileName) /* throws(Exception) */
{
	ModelMetaDataFileExport::doExport(pathName, fileName, entity);
}

void SharedParticleSystemView::reloadFile()
{
	loadParticleSystemRequested = true;
}

void SharedParticleSystemView::handleInputEvents()
{
	for (auto i = 0; i < engine->getGUI()->getKeyboardEvents().size(); i++) {
		auto& event = engine->getGUI()->getKeyboardEvents()[i];
		if (event.isProcessed() == true) continue;
		auto isKeyDown = event.getType() == GUIKeyboardEvent_Type::KEYBOARDEVENT_KEY_PRESSED;
		if (Character::toLowerCase(event.getKeyChar()) == '1') { if (isKeyDown == true) setGizmoType(GIZMOTYPE_ALL); updateGizmo(entity); event.setProcessed(true); }
		if (Character::toLowerCase(event.getKeyChar()) == '2') { if (isKeyDown == true) setGizmoType(GIZMOTYPE_TRANSLATE); updateGizmo(entity); event.setProcessed(true); }
		if (Character::toLowerCase(event.getKeyChar()) == '3') { if (isKeyDown == true) setGizmoType(GIZMOTYPE_ROTATE); updateGizmo(entity); event.setProcessed(true); }
		if (Character::toLowerCase(event.getKeyChar()) == '4') { if (isKeyDown == true) setGizmoType(GIZMOTYPE_SCALE); updateGizmo(entity); event.setProcessed(true); }
	}
	for (auto i = 0; i < engine->getGUI()->getMouseEvents().size(); i++) {
		auto& event = engine->getGUI()->getMouseEvents()[i];

		if (event.isProcessed() == true) continue;

		if (event.getButton() == MOUSE_BUTTON_LEFT) {
			if (event.getType() == GUIMouseEvent_Type::MOUSEEVENT_RELEASED) {
				auto selectedEntity = engine->getEntity("model");
				auto psg = dynamic_cast<ParticleSystemGroup*>(selectedEntity);
				if (psg != nullptr) selectedEntity = psg->getParticleSystems()[particleSystemIdx];
				if (selectedEntity != nullptr) applyParticleSystemTransformations(false);
				if (getGizmoMode() != GIZMOMODE_NONE) {
					setGizmoMode(GIZMOMODE_NONE);
					updateGizmo(entity);
				}
				totalDeltaScale.set(0.0, 0.0f, 0.0f);
				event.setProcessed(true);
			} else
			if (event.getType() == GUIMouseEvent_Type::MOUSEEVENT_PRESSED) {
				Group* selectedEntityGroup = nullptr;
				Entity* selectedEntity = nullptr;
				if (getGizmoMode() == GIZMOMODE_NONE) selectedEntity = engine->getEntityByMousePosition(event.getXUnscaled(), event.getYUnscaled(), nullptr, &selectedEntityGroup);
				if (getGizmoMode() == GIZMOMODE_NONE && selectedEntity == nullptr) {
					removeGizmo();
					totalDeltaScale.set(0.0, 0.0f, 0.0f);
					event.setProcessed(true);
				} else
				if (determineGizmoMode(selectedEntity, selectedEntityGroup) == true) {
					mouseDownLastX = event.getXUnscaled();
					mouseDownLastY = event.getYUnscaled();
					event.setProcessed(true);
				} else
				if (selectedEntity != nullptr) {
					updateGizmo(entity);
					totalDeltaScale.set(0.0, 0.0f, 0.0f);
					event.setProcessed(true);
				}
			} else
			if (event.getType() == GUIMouseEvent_Type::MOUSEEVENT_DRAGGED) {
				if (getGizmoMode() != GIZMOMODE_NONE) {
					Vector3 deltaTranslation;
					Vector3 deltaRotation;
					Vector3 deltaScale;
					if (determineGizmoDeltaTransformations(mouseDownLastX, mouseDownLastY, event.getXUnscaled(), event.getYUnscaled(), deltaTranslation, deltaRotation, deltaScale) == true) {
						totalDeltaScale.add(deltaScale.clone().sub(Vector3(1.0f, 1.0f, 1.0f)));
						auto gizmoEntity = getGizmoObject3D();
						auto selectedEntity = engine->getEntity("model");
						auto psg = dynamic_cast<ParticleSystemGroup*>(selectedEntity);
						if (psg != nullptr) selectedEntity = psg->getParticleSystems()[particleSystemIdx];
						if (gizmoEntity != nullptr && selectedEntity != nullptr) {
							selectedEntity->setTranslation(selectedEntity->getTranslation().clone().add(deltaTranslation));
							selectedEntity->update();
							auto localTransformations = dynamic_cast<ParticleSystemEntity*>(selectedEntity)->getLocalTransformations();
							localTransformations.setScale(localTransformations.getScale().clone().scale(deltaScale));
							if (localTransformations.getRotationCount() == 0) {
								localTransformations.addRotation(Rotation::Z_AXIS, 0.0f);
								localTransformations.addRotation(Rotation::Y_AXIS, 0.0f);
								localTransformations.addRotation(Rotation::X_AXIS, 0.0f);
							}
							localTransformations.setRotationAngle(0, localTransformations.getRotationAngle(0) + deltaRotation[2]);
							localTransformations.setRotationAngle(1, localTransformations.getRotationAngle(1) + deltaRotation[1]);
							localTransformations.setRotationAngle(2, localTransformations.getRotationAngle(2) + deltaRotation[0]);
							localTransformations.update();
							dynamic_cast<ParticleSystemEntity*>(selectedEntity)->setLocalTransformations(localTransformations);
							setGizmoRotation(entity, localTransformations);
							applyParticleSystemTransformations(true);
						}
						if (Math::abs(deltaTranslation.getX()) > Math::EPSILON ||
							Math::abs(deltaTranslation.getY()) > Math::EPSILON ||
							Math::abs(deltaTranslation.getZ()) > Math::EPSILON) {
							updateGizmo(entity);
						}
					}
					mouseDownLastX = event.getXUnscaled();
					mouseDownLastY = event.getYUnscaled();
					event.setProcessed(true);
				}
			}
		}
	}
	//entityPhysicsView->handleInputEvents(entity, objectScale);
	//cameraRotationInputHandler->handleInputEvents();
}

void SharedParticleSystemView::display()
{
	if (audioOffset > 0 && Time::getCurrentMillis() - audioStarted >= audioOffset) {
		auto sound = audio->getEntity("sound");
		if (sound != nullptr) sound->play();
		audioOffset = -1LL;
	}
	if (loadParticleSystemRequested == true) {
		initParticleSystemRequested = true;
		loadParticleSystemRequested = false;
		loadParticleSystem();
		cameraRotationInputHandler->reset();
	}
	if (initParticleSystemRequested == true) {
		initParticleSystem();
		initParticleSystemRequested = false;
		cameraRotationInputHandler->reset();
	}
	if (updateParticleSystemRequested == true) {
		initParticleSystem();
		updateParticleSystemRequested = false;
	}
	auto particleSystemEntity = dynamic_cast< ParticleSystemEntity* >(engine->getEntity("model"));
	if (particleSystemEntity != nullptr && particleSystemEntity->isAutoEmit() == false) {
		particleSystemEntity->emitParticles();
		particleSystemEntity->updateParticles();
	}
	entityDisplayView->display(entity);
	entityPhysicsView->display(entity);
	engine->getGUI()->handleEvents();
	engine->getGUI()->render();
}

void SharedParticleSystemView::updateGUIElements()
{
	if (entity != nullptr && entity->getParticleSystemsCount() > 0) {
		particleSystemScreenController->setScreenCaption("Particle System - " + (entity->getEntityFileName().length() > 0 ? FileSystem::getInstance()->getFileName(entity->getEntityFileName()) : entity->getName()));
		auto preset = entity->getProperty("preset");
		particleSystemScreenController->setEntityProperties(preset != nullptr ? preset->getValue() : "", entity, "");
		particleSystemScreenController->setEntityData(entity->getName(), entity->getDescription());
		entityPhysicsView->setBoundingVolumes(entity);
		entityPhysicsView->setPhysics(entity);
		entitySoundsView->setSounds(entity);
		particleSystemScreenController->setParticleSystemType();
		particleSystemScreenController->setParticleSystemEmitter();
		particleSystemScreenController->setParticleSystemListBox(entity->getParticleSystemsCount(), particleSystemIdx);
	} else {
		particleSystemScreenController->setScreenCaption("Particle System - no particle system");
		particleSystemScreenController->unsetEntityProperties();
		particleSystemScreenController->unsetEntityData();
		entityPhysicsView->unsetBoundingVolumes();
		entityPhysicsView->unsetPhysics();
		entitySoundsView->unsetSounds();
		particleSystemScreenController->unsetParticleSystemType();
		particleSystemScreenController->unsetParticleSystemEmitter();
		particleSystemScreenController->setParticleSystemListBox(0, particleSystemIdx);
		particleSystemScreenController->unsetParticleSystemListBox();
	}
}

void SharedParticleSystemView::onInitAdditionalScreens()
{
}

void SharedParticleSystemView::loadSettings()
{
	try {
		Properties settings;
		settings.load("settings", "particlesystem.properties");
		entityPhysicsView->setDisplayBoundingVolume(settings.get("display.boundingvolumes", "false") == "true");
		entityDisplayView->setDisplayGroundPlate(settings.get("display.groundplate", "false") == "true");
		entityDisplayView->setDisplayShadowing(settings.get("display.shadowing", "false") == "true");
		particleSystemScreenController->getParticleSystemPath()->setPath(settings.get("particlesystem.path", "."));
		particleSystemScreenController->getModelPath()->setPath(settings.get("model.path", "."));
	} catch (Exception& exception) {
		Console::print(string("SharedParticleSystemView::loadSettings(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void SharedParticleSystemView::initialize()
{
	try {
		particleSystemScreenController = new ParticleSystemScreenController(this);
		particleSystemScreenController->initialize();
		entityDisplayView = particleSystemScreenController->getEntityDisplaySubScreenController()->getView();
		entityPhysicsView = particleSystemScreenController->getEntityPhysicsSubScreenController()->getView();
		entitySoundsView = particleSystemScreenController->getEntitySoundsSubScreenController()->getView();
		engine->getGUI()->addScreen(particleSystemScreenController->getScreenNode()->getId(), particleSystemScreenController->getScreenNode());
		particleSystemScreenController->getScreenNode()->setInputEventHandler(this);
	} catch (Exception& exception) {
		Console::print(string("SharedParticleSystemView::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}

	loadSettings();
	entityPhysicsView->initialize();
	vector<string> particleSystemTypes;
	particleSystemTypes.push_back("None");
	particleSystemTypes.push_back("Object Particle System");
	particleSystemTypes.push_back("Points Particle System");
	particleSystemTypes.push_back("Fog Particle System");
	particleSystemScreenController->setParticleSystemTypes(particleSystemTypes);
	vector<string> particleSystemEmitters;
	particleSystemEmitters.push_back("None");
	particleSystemEmitters.push_back("Point Particle Emitter");
	particleSystemEmitters.push_back("BoundingBox Particle Emitter");
	particleSystemEmitters.push_back("Circle Particle Emitter");
	particleSystemEmitters.push_back("Circle Particle Emitter Plane Velocity");
	particleSystemEmitters.push_back("Sphere Particle Emitter");
	particleSystemScreenController->setParticleSystemEmitters(particleSystemEmitters);
	particleSystemScreenController->getEntityDisplaySubScreenController()->setupDisplay();
	updateGUIElements();
	initParticleSystemRequested = true;
}

void SharedParticleSystemView::activate()
{
	engine->reset();
	engine->setPartition(new PartitionNone());
	engine->getGUI()->resetRenderScreens();
	engine->getGUI()->addRenderScreen(particleSystemScreenController->getScreenNode()->getId());
	onInitAdditionalScreens();
	engine->getGUI()->addRenderScreen(popUps->getFileDialogScreenController()->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(popUps->getInfoDialogScreenController()->getScreenNode()->getId());
}

void SharedParticleSystemView::storeSettings()
{
	try {
		Properties settings;
		settings.put("display.boundingvolumes", entityPhysicsView->isDisplayBoundingVolume() == true ? "true" : "false");
		settings.put("display.groundplate", entityDisplayView->isDisplayGroundPlate() == true ? "true" : "false");
		settings.put("display.shadowing", entityDisplayView->isDisplayShadowing() == true ? "true" : "false");
		settings.put("particlesystem.path", particleSystemScreenController->getParticleSystemPath()->getPath());
		settings.put("model.path", particleSystemScreenController->getModelPath()->getPath());
		settings.store("settings", "particlesystem.properties");
	} catch (Exception& exception) {
		Console::print(string("SharedParticleSystemView::storeSettings(): An error occurred "));
		Console::println(string(exception.what()));
	}
}

void SharedParticleSystemView::dispose()
{
	storeSettings();
	engine->reset();
	audio->reset();
}

void SharedParticleSystemView::deactivate()
{
	audio->removeEntity("sound");
}

void SharedParticleSystemView::onLoadParticleSystem(LevelEditorEntity* oldEntity, LevelEditorEntity* entity)
{
	delete oldEntity;
}

void SharedParticleSystemView::loadParticleSystem()
{
	Console::println(string("Particle system file: " + particleSystemFile));
	try {
		auto oldEntity = entity;
		setEntity(
			loadParticleSystem(
				particleSystemFile,
				"",
				FileSystem::getInstance()->getPathName(particleSystemFile),
				FileSystem::getInstance()->getFileName(particleSystemFile)
			)
		);
		onLoadParticleSystem(oldEntity, entity);
	} catch (Exception& exception) {
		popUps->getInfoDialogScreenController()->show("Warning", (exception.what()));
	}
}

LevelEditorEntity* SharedParticleSystemView::loadParticleSystem(const string& name, const string& description, const string& pathName, const string& fileName) /* throws(Exception) */
{
	if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".tps") == true) {
		auto levelEditorEntity = ModelMetaDataFileImport::doImport(pathName, fileName);
		levelEditorEntity->setDefaultBoundingVolumes();
		return levelEditorEntity;
	}
	return nullptr;
}

void SharedParticleSystemView::onSetEntityData()
{
}

int SharedParticleSystemView::getParticleSystemIndex() {
	return particleSystemIdx;
}

void SharedParticleSystemView::setParticleSystemIndex(int idx) {
	this->particleSystemIdx = idx;
	updateGUIElements();
}


void SharedParticleSystemView::playSound(const string& soundId) {
	audio->removeEntity("sound");
	auto soundDefinition = entity->getSound(soundId);
	if (soundDefinition != nullptr && soundDefinition->getFileName().length() > 0) {
		string pathName = ModelMetaDataFileImport::getResourcePathName(
			Tools::getPath(entity->getEntityFileName()),
			soundDefinition->getFileName()
		);
		string fileName = Tools::getFileName(soundDefinition->getFileName());
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

void SharedParticleSystemView::updateGizmo(LevelEditorEntity* entity) {
	auto selectedEntity = engine->getEntity("model");
	auto psg = dynamic_cast<ParticleSystemGroup*>(selectedEntity);
	if (psg != nullptr) selectedEntity = psg->getParticleSystems()[particleSystemIdx];
	auto pse = dynamic_cast<ParticleSystemEntity*>(selectedEntity);
	if (selectedEntity != nullptr) {
		if (pse != nullptr) {
			Console::println(
				"emit: " +
				to_string(pse->getEmitter()->getCenter().getX()) + ", " +
				to_string(pse->getEmitter()->getCenter().getY()) + ", " +
				to_string(pse->getEmitter()->getCenter().getZ()) + "; " +
				"trans: " +
				to_string(selectedEntity->getTranslation().getX()) + ", " +
				to_string(selectedEntity->getTranslation().getY()) + ", " +
				to_string(selectedEntity->getTranslation().getZ())
			);
			Gizmo::updateGizmo(pse->getEmitter()->getCenter().clone().scale(objectScale).add(selectedEntity->getTranslation()));
		} else {
			Gizmo::updateGizmo(selectedEntity->getBoundingBoxTransformed()->getCenter());
		}
		setGizmoRotation(entity, selectedEntity->getTransformations());
	} else {
		removeGizmo();
	}
}

void SharedParticleSystemView::setGizmoRotation(LevelEditorEntity* entity, const Transformations& transformations) {
	Gizmo::setGizmoRotation(transformations);
}

void SharedParticleSystemView::applyParticleSystemTransformations(bool guiOnly) {
	if (guiOnly == true) return;
	{
		auto transformations = engine->getEntity("model")->getTransformations();
		auto localTransformations = dynamic_cast<ParticleSystemEntity*>(engine->getEntity("model"))->getLocalTransformations();
		auto objectScaleInverted = Vector3(
			1.0f / objectScale.getX(),
			1.0f / objectScale.getY(),
			1.0f / objectScale.getZ()
		);
		transformations.setScale(objectScaleInverted);
		transformations.update();
		auto particleSystem = entity->getParticleSystemAt(particleSystemIdx);
		auto emitterType = particleSystem->getEmitter();
		if (emitterType == LevelEditorEntityParticleSystem_Emitter::NONE) {
			// no op
		} else
		if (emitterType == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) {
			auto emitter = particleSystem->getPointParticleEmitter();
			emitter->setPosition(transformations.getTranslation().clone().scale(objectScaleInverted).add(emitter->getPosition()));
		} else
		if (emitterType == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) {
			auto emitter = particleSystem->getBoundingBoxParticleEmitters();
		} else
		if (emitterType == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) {
			Vector3 tmpVector3;
			auto emitter = particleSystem->getCircleParticleEmitter();
			emitter->setCenter(transformations.getTransformationsMatrix().multiply(emitter->getCenter(), tmpVector3));
		} else
		if (emitterType == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) {
			auto emitter = particleSystem->getCircleParticleEmitterPlaneVelocity();
		} else
		if (emitterType == LevelEditorEntityParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER) {
			auto emitter = particleSystem->getSphereParticleEmitter();
			emitter->setCenter(transformations.getTranslation().clone().scale(objectScaleInverted).add(emitter->getCenter()));
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
			emitter->setRadius(Math::clamp(emitter->getRadius() * Math::abs(scale), 0.01f, 1000.0f));
		} else {
			Console::println(
				string(
					"SharedParticleSystemView::applyParticleSystemTransformations(): unknown particle system emitter '" +
					particleSystem->getEmitter()->getName() +
					"'"
				)
			);
		}
	}
	{
		auto modelEntity = engine->getEntity("model");
		if (modelEntity != nullptr) engine->removeEntity("model");
		Transformations transformations;
		transformations.setScale(objectScale);
		transformations.update();
		modelEntity = Level::createEntity(entity, "model", transformations);
		if (modelEntity != nullptr) engine->addEntity(modelEntity);

	}
}
