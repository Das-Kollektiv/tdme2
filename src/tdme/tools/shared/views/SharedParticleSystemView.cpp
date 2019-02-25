#include <tdme/tools/shared/views/SharedParticleSystemView.h>

#include <string>

#include <tdme/audio/Audio.h>
#include <tdme/audio/Sound.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/PartitionNone.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/subsystems/particlesystem/ParticleSystemEntity.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/shared/controller/EntityDisplaySubScreenController.h>
#include <tdme/tools/shared/controller/EntityPhysicsSubScreenController.h>
#include <tdme/tools/shared/controller/EntitySoundsSubScreenController.h>
#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/tools/shared/controller/ParticleSystemScreenController.h>
#include <tdme/tools/shared/files/ModelMetaDataFileExport.h>
#include <tdme/tools/shared/files/ModelMetaDataFileImport.h>
#include <tdme/tools/shared/model/LevelEditorEntity_EntityType.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityAudio.h>
#include <tdme/tools/shared/model/PropertyModelClass.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/tools/shared/views/CameraRotationInputHandler.h>
#include <tdme/tools/shared/views/EntityPhysicsView.h>
#include <tdme/tools/shared/views/EntityDisplayView.h>
#include <tdme/tools/shared/views/EntitySoundsView.h>
#include <tdme/tools/shared/views/PlayableSoundView.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/shared/views/View.h>
#include <tdme/utils/Properties.h>
#include <tdme/utils/StringUtils.h>
#include <tdme/utils/Exception.h>
#include <tdme/utils/Console.h>

using std::string;

using tdme::tools::shared::views::SharedParticleSystemView;

using tdme::audio::Audio;
using tdme::audio::Sound;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::PartitionNone;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::particlesystem::ParticleSystemEntity;
using tdme::gui::GUI;
using tdme::gui::nodes::GUIScreenNode;
using tdme::math::Vector3;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::shared::controller::EntityDisplaySubScreenController;
using tdme::tools::shared::controller::EntityPhysicsSubScreenController;
using tdme::tools::shared::controller::EntitySoundsSubScreenController;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::controller::ParticleSystemScreenController;
using tdme::tools::shared::files::ModelMetaDataFileExport;
using tdme::tools::shared::files::ModelMetaDataFileImport;
using tdme::tools::shared::model::LevelEditorEntity_EntityType;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityAudio;
using tdme::tools::shared::model::PropertyModelClass;
using tdme::tools::shared::tools::Tools;
using tdme::tools::shared::views::CameraRotationInputHandler;
using tdme::tools::shared::views::EntityPhysicsView;
using tdme::tools::shared::views::EntityDisplayView;
using tdme::tools::shared::views::EntitySoundsView;
using tdme::tools::shared::views::PlayableSoundView;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::View;
using tdme::utils::Properties;
using tdme::utils::StringUtils;
using tdme::utils::Exception;
using tdme::utils::Console;

SharedParticleSystemView::SharedParticleSystemView(PopUps* popUps) 
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
	initParticleSystemRequested = true;
}

void SharedParticleSystemView::initParticleSystemRequest()
{
	initParticleSystemRequested = true;
}

void SharedParticleSystemView::initParticleSystem()
{
	if (entity == nullptr)
		return;

	particleSystemFile = entity->getEntityFileName();
	Tools::setupEntity(entity, engine, cameraRotationInputHandler->getLookFromRotations(), cameraRotationInputHandler->getScale());
	Tools::oseThumbnail(entity);
	BoundingBox boundingBox;
	if (entity->getModel() == nullptr) {
		boundingBox.getMin().set(Vector3(-0.5f, 0.0f, -0.5f));
		boundingBox.getMax().set(Vector3(0.5f, 3.0f, 0.5f));
	} else {
		boundingBox.fromBoundingVolume(entity->getModel()->getBoundingBox());
	}
	boundingBox.update();
	cameraRotationInputHandler->setMaxAxisDimension(Tools::computeMaxAxisDimension(&boundingBox));
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
	ModelMetaDataFileExport::export_(pathName, fileName, entity);
}

void SharedParticleSystemView::reloadFile()
{
	loadParticleSystemRequested = true;
}

void SharedParticleSystemView::handleInputEvents()
{
	cameraRotationInputHandler->handleInputEvents();
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
		particleSystemScreenController->setParticleSystemType();
		particleSystemScreenController->setParticleSystemEmitter();
		initParticleSystemRequested = false;
		cameraRotationInputHandler->reset();
	}
	auto particleSystemEntity = dynamic_cast< ParticleSystemEntity* >(engine->getEntity("model"));
	if (particleSystemEntity != nullptr && particleSystemEntity->isAutoEmit() == false) {
		particleSystemEntity->emitParticles();
		particleSystemEntity->updateParticles();
	}
	entityDisplayView->display(entity);
	engine->getGUI()->handleEvents();
	engine->getGUI()->render();
}

void SharedParticleSystemView::updateGUIElements()
{
	if (entity != nullptr) {
		particleSystemScreenController->setScreenCaption("Particle System - " + (entity->getEntityFileName().length() > 0 ? FileSystem::getInstance()->getFileName(entity->getEntityFileName()) : entity->getName()));
		auto preset = entity->getProperty("preset");
		particleSystemScreenController->setEntityProperties(preset != nullptr ? preset->getValue() : "", entity, "");
		particleSystemScreenController->setEntityData(entity->getName(), entity->getDescription());
		entityPhysicsView->setBoundingVolumes(entity);
		entityPhysicsView->setPhysics(entity);
		entitySoundsView->setSounds(entity);
	} else {
		particleSystemScreenController->setScreenCaption("Particle System - no entity loaded");
		particleSystemScreenController->unsetEntityProperties();
		particleSystemScreenController->unsetEntityData();
		entityPhysicsView->unsetBoundingVolumes();
		entityPhysicsView->unsetPhysics();
		entitySoundsView->unsetSounds();
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
		entityDisplayView->setDisplayBoundingVolume(settings.get("display.boundingvolumes", "false") == "true");
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
		settings.put("display.boundingvolumes", entityDisplayView->isDisplayBoundingVolume() == true ? "true" : "false");
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
		auto levelEditorEntity = ModelMetaDataFileImport::doImport(LevelEditorEntity::ID_NONE, pathName, fileName);
		levelEditorEntity->setDefaultBoundingVolumes();
		return levelEditorEntity;
	}
	return nullptr;
}

void SharedParticleSystemView::onSetEntityData()
{
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

