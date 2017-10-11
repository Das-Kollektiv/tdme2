#include <tdme/tools/shared/views/SharedParticleSystemView.h>

#include <string>

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
#include <tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController.h>
#include <tdme/tools/shared/controller/EntityDisplaySubScreenController.h>
#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/tools/shared/controller/ParticleSystemScreenController.h>
#include <tdme/tools/shared/files/ModelMetaDataFileExport.h>
#include <tdme/tools/shared/files/ModelMetaDataFileImport.h>
#include <tdme/tools/shared/model/LevelEditorEntity_EntityType.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/PropertyModelClass.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/tools/shared/views/CameraRotationInputHandler.h>
#include <tdme/tools/shared/views/EntityBoundingVolumeView.h>
#include <tdme/tools/shared/views/EntityDisplayView.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/utils/Properties.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/StringUtils.h>
#include <tdme/utils/Exception.h>
#include <tdme/utils/Console.h>

using std::wstring;

using tdme::tools::shared::views::SharedParticleSystemView;
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
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController;
using tdme::tools::shared::controller::EntityDisplaySubScreenController;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::controller::ParticleSystemScreenController;
using tdme::tools::shared::files::ModelMetaDataFileExport;
using tdme::tools::shared::files::ModelMetaDataFileImport;
using tdme::tools::shared::model::LevelEditorEntity_EntityType;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::PropertyModelClass;
using tdme::tools::shared::tools::Tools;
using tdme::tools::shared::views::CameraRotationInputHandler;
using tdme::tools::shared::views::EntityBoundingVolumeView;
using tdme::tools::shared::views::EntityDisplayView;
using tdme::tools::shared::views::PopUps;
using tdme::utils::Properties;
using tdme::utils::StringConverter;
using tdme::utils::StringUtils;
using tdme::utils::Exception;
using tdme::utils::Console;

SharedParticleSystemView::SharedParticleSystemView(PopUps* popUps) 
{
	this->popUps = popUps;
	engine = Engine::getInstance();
	particleSystemScreenController = nullptr;
	entityDisplayView = nullptr;
	loadParticleSystemRequested = false;
	initParticleSystemRequested = false;
	particleSystemFile = L"";
	cameraRotationInputHandler = new CameraRotationInputHandler(engine);
	entity = new LevelEditorEntity(
		-1,
		LevelEditorEntity_EntityType::PARTICLESYSTEM,
		L"Untitled",
		L"",
		L"Untitled.tps",
		L"",
		L"",
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

void SharedParticleSystemView::setEntity(LevelEditorEntity* entity)
{
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

const wstring SharedParticleSystemView::getFileName()
{
	if (particleSystemFile.length() == 0) return particleSystemFile;
	return FileSystem::getInstance()->getFileName(particleSystemFile);
}

void SharedParticleSystemView::loadFile(const wstring& pathName, const wstring& fileName)
{
	loadParticleSystemRequested = true;
	particleSystemFile = pathName + L"/" + fileName;
}

void SharedParticleSystemView::saveFile(const wstring& pathName, const wstring& fileName) /* throws(Exception) */
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
	if (loadParticleSystemRequested == true) {
		initParticleSystemRequested = true;
		loadParticleSystemRequested = false;
		loadParticleSystem();
		cameraRotationInputHandler->reset();
	}
	if (initParticleSystemRequested == true) {
		engine->reset();
		initParticleSystem();
		particleSystemScreenController->setParticleSystemType();
		particleSystemScreenController->setParticleSystemEmitter();
		initParticleSystemRequested = false;
	}
	auto particleSystemEntity = dynamic_cast< ParticleSystemEntity* >(engine->getEntity(L"model"));
	if (particleSystemEntity != nullptr && particleSystemEntity->isAutoEmit() == false) {
		particleSystemEntity->emitParticles();
		particleSystemEntity->updateParticles();
	}
	entityDisplayView->display(entity);
	engine->getGUI()->render();
	engine->getGUI()->handleEvents();
}

void SharedParticleSystemView::updateGUIElements()
{
	if (entity != nullptr) {
		particleSystemScreenController->setScreenCaption(L"Particle System - " + (entity->getEntityFileName().length() > 0 ? FileSystem::getInstance()->getFileName(entity->getEntityFileName()) : entity->getName()));
		auto preset = entity->getProperty(L"preset");
		particleSystemScreenController->setEntityProperties(preset != nullptr ? preset->getValue() : L"", entity, L"");
		particleSystemScreenController->setEntityData(entity->getName(), entity->getDescription());
		entityBoundingVolumeView->setBoundingVolumes(entity);
	} else {
		particleSystemScreenController->setScreenCaption(L"Particle System - no entity loaded");
		particleSystemScreenController->unsetEntityProperties();
		particleSystemScreenController->unsetEntityData();
		entityBoundingVolumeView->unsetBoundingVolumes();
	}
}

void SharedParticleSystemView::onInitAdditionalScreens()
{
}

void SharedParticleSystemView::loadSettings()
{
	try {
		Properties settings;
		settings.load(L"settings", L"particlesystem.properties");
		entityDisplayView->setDisplayBoundingVolume(settings.get(L"display.boundingvolumes", L"false") == L"true");
		entityDisplayView->setDisplayGroundPlate(settings.get(L"display.groundplate", L"false") == L"true");
		entityDisplayView->setDisplayShadowing(settings.get(L"display.shadowing", L"false") == L"true");
		particleSystemScreenController->getParticleSystemPath()->setPath(settings.get(L"particlesystem.path", L"."));
		particleSystemScreenController->getModelPath()->setPath(settings.get(L"model.path", L"."));
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
		entityBoundingVolumeView = particleSystemScreenController->getEntityBoundingVolumeSubScreenController()->getView();
		engine->getGUI()->addScreen(particleSystemScreenController->getScreenNode()->getId(), particleSystemScreenController->getScreenNode());
		particleSystemScreenController->getScreenNode()->setInputEventHandler(this);
	} catch (Exception& exception) {
		Console::print(string("SharedParticleSystemView::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}

	loadSettings();
	entityBoundingVolumeView->initialize();
	vector<wstring> particleSystemTypes;
	particleSystemTypes.push_back(L"None");
	particleSystemTypes.push_back(L"Object Particle System");
	particleSystemTypes.push_back(L"Points Particle System");
	particleSystemScreenController->setParticleSystemTypes(&particleSystemTypes);
	vector<wstring> particleSystemEmitters;
	particleSystemEmitters.push_back(L"None");
	particleSystemEmitters.push_back(L"Point Particle Emitter");
	particleSystemEmitters.push_back(L"BoundingBox Particle Emitter");
	particleSystemEmitters.push_back(L"Circle Particle Emitter");
	particleSystemEmitters.push_back(L"Circle Particle Emitter Plane Velocity");
	particleSystemEmitters.push_back(L"Sphere Particle Emitter");
	particleSystemScreenController->setParticleSystemEmitters(&particleSystemEmitters);
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
		settings.put(L"display.boundingvolumes", entityDisplayView->isDisplayBoundingVolume() == true ? L"true" : L"false");
		settings.put(L"display.groundplate", entityDisplayView->isDisplayGroundPlate() == true ? L"true" : L"false");
		settings.put(L"display.shadowing", entityDisplayView->isDisplayShadowing() == true ? L"true" : L"false");
		settings.put(L"particlesystem.path", particleSystemScreenController->getParticleSystemPath()->getPath());
		settings.put(L"model.path", particleSystemScreenController->getModelPath()->getPath());
		settings.store(L"settings", L"particlesystem.properties");
	} catch (Exception& exception) {
		Console::print(string("SharedParticleSystemView::storeSettings(): An error occurred "));
		Console::println(string(exception.what()));
	}
}

void SharedParticleSystemView::dispose()
{
	storeSettings();
	Engine::getInstance()->reset();
}

void SharedParticleSystemView::deactivate()
{
}

void SharedParticleSystemView::onLoadParticleSystem(LevelEditorEntity* oldEntity, LevelEditorEntity* entity)
{
}

void SharedParticleSystemView::loadParticleSystem()
{
	Console::println(wstring(L"Particle system file: " + particleSystemFile));
	try {
		auto oldEntity = entity;
		entity = loadParticleSystem(
			particleSystemFile,
			L"",
			FileSystem::getInstance()->getPathName(particleSystemFile),
			FileSystem::getInstance()->getFileName(particleSystemFile)
		);
		onLoadParticleSystem(oldEntity, entity);
	} catch (Exception& exception) {
		popUps->getInfoDialogScreenController()->show(L"Warning", StringConverter::toWideString(exception.what()));
	}
}

LevelEditorEntity* SharedParticleSystemView::loadParticleSystem(const wstring& name, const wstring& description, const wstring& pathName, const wstring& fileName) /* throws(Exception) */
{
	if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), L".tps") == true) {
		auto levelEditorEntity = ModelMetaDataFileImport::doImport(LevelEditorEntity::ID_NONE, pathName, fileName);
		levelEditorEntity->setDefaultBoundingVolumes();
		return levelEditorEntity;
	}
	return nullptr;
}

void SharedParticleSystemView::onSetEntityData()
{
}
