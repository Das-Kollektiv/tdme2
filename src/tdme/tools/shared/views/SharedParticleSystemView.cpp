// Generated from /tdme/src/tdme/tools/shared/views/SharedParticleSystemView.java
#include <tdme/tools/shared/views/SharedParticleSystemView.h>

#include <string>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Properties.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/PartitionNone.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/subsystems/particlesystem/ParticleSystemEntity.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
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
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/StringUtils.h>
#include <tdme/utils/_Exception.h>
#include <tdme/utils/_Console.h>

using std::wstring;

using tdme::tools::shared::views::SharedParticleSystemView;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Properties;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::PartitionNone;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::particlesystem::ParticleSystemEntity;
using tdme::gui::GUI;
using tdme::gui::nodes::GUIScreenNode;
using tdme::math::Vector3;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
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
using tdme::utils::StringConverter;
using tdme::utils::StringUtils;
using tdme::utils::_Exception;
using tdme::utils::_Console;

SharedParticleSystemView::SharedParticleSystemView(PopUps* popUps) 
{
	this->popUps = popUps;
	engine = Engine::getInstance();
	particleSystemScreenController = nullptr;
	entityDisplayView = nullptr;
	loadParticleSystemRequested = false;
	initParticleSystemRequested = false;
	particleSystemFile = nullptr;
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
		new Vector3()
	);
	entity->setDefaultBoundingVolumes();
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

	particleSystemFile = new String(entity->getEntityFileName());
	Tools::setupEntity(entity, engine, cameraRotationInputHandler->getLookFromRotations(), cameraRotationInputHandler->getScale());
	Tools::oseThumbnail(entity);
	BoundingBox* boundingBox = nullptr;
	if (entity->getModel() == nullptr) {
		boundingBox = new BoundingBox(new Vector3(-0.5f, 0.0f, -0.5f), new Vector3(0.5f, 3.0f, 0.5f));
	} else {
		boundingBox = entity->getModel()->getBoundingBox();
	}
	cameraRotationInputHandler->setMaxAxisDimension(Tools::computeMaxAxisDimension(boundingBox));
	updateGUIElements();
}

String* SharedParticleSystemView::getFileName()
{
	if (particleSystemFile == nullptr)
		return u""_j;

	return new String(_FileSystem::getInstance()->getFileName(particleSystemFile->getCPPWString()));
}

void SharedParticleSystemView::loadFile(String* pathName, String* fileName)
{
	loadParticleSystemRequested = true;
	particleSystemFile = new String(pathName->getCPPWString() + L"/" + fileName->getCPPWString());
}

void SharedParticleSystemView::saveFile(String* pathName, String* fileName) /* throws(Exception) */
{
	ModelMetaDataFileExport::export_(pathName->getCPPWString(), fileName->getCPPWString(), entity);
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
		particleSystemScreenController->setScreenCaption(::java::lang::StringBuilder().append(u"Particle System - "_j)->append((entity->getEntityFileName().length() > 0 ? _FileSystem::getInstance()->getFileName(entity->getEntityFileName()) : entity->getName()))->toString());
		auto preset = entity->getProperty(u"preset"_j);
		particleSystemScreenController->setEntityProperties(preset != nullptr ? new String(preset->getValue()) : static_cast< String* >(nullptr), entity, nullptr);
		particleSystemScreenController->setEntityData(entity->getName(), entity->getDescription());
		entityBoundingVolumeView->setBoundingVolumes(entity);
	} else {
		particleSystemScreenController->setScreenCaption(u"Particle System - no entity loaded"_j);
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
		Object* tmp = nullptr;
		auto settings = new Properties();
		settings->load(L"settings", L"particlesystem.properties");
		entityDisplayView->setDisplayBoundingVolume((tmp = dynamic_cast< Object* >(settings->get(u"display.boundingvolumes"_j))) != nullptr ? tmp->equals(u"true"_j) == true : false);
		entityDisplayView->setDisplayGroundPlate((tmp = dynamic_cast< Object* >(settings->get(u"display.groundplate"_j))) != nullptr ? tmp->equals(u"true"_j) == true : false);
		entityDisplayView->setDisplayShadowing((tmp = dynamic_cast< Object* >(settings->get(u"display.shadowing"_j))) != nullptr ? tmp->equals(u"true"_j) == true : false);
		particleSystemScreenController->getParticleSystemPath()->setPath((tmp = dynamic_cast< Object* >(settings->get(u"particlesystem.path"_j))) != nullptr ? tmp->toString() : u"."_j);
		particleSystemScreenController->getModelPath()->setPath((tmp = dynamic_cast< Object* >(settings->get(u"model.path"_j))) != nullptr ? tmp->toString() : u"."_j);
	} catch (_Exception& exception) {
		_Console::print(string("SharedParticleSystemView::loadSettings(): An error occurred: "));
		_Console::println(string(exception.what()));
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
	} catch (_Exception& exception) {
		_Console::print(string("SharedParticleSystemView::initialize(): An error occurred: "));
		_Console::println(string(exception.what()));
	}

	loadSettings();
	entityBoundingVolumeView->initialize();
	vector<String*> particleSystemTypes;
	particleSystemTypes.push_back(u"None"_j);
	particleSystemTypes.push_back(u"Object Particle System"_j);
	particleSystemTypes.push_back(u"Points Particle System"_j);
	particleSystemScreenController->setParticleSystemTypes(&particleSystemTypes);
	vector<String*> particleSystemEmitters;
	particleSystemEmitters.push_back(u"None"_j);
	particleSystemEmitters.push_back(u"Point Particle Emitter"_j);
	particleSystemEmitters.push_back(u"BoundingBox Particle Emitter"_j);
	particleSystemEmitters.push_back(u"Circle Particle Emitter"_j);
	particleSystemEmitters.push_back(u"Circle Particle Emitter Plane Velocity"_j);
	particleSystemEmitters.push_back(u"Sphere Particle Emitter"_j);
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
		auto settings = new Properties();
		settings->put(u"display.boundingvolumes"_j, entityDisplayView->isDisplayBoundingVolume() == true ? u"true"_j : u"false"_j);
		settings->put(u"display.groundplate"_j, entityDisplayView->isDisplayGroundPlate() == true ? u"true"_j : u"false"_j);
		settings->put(u"display.shadowing"_j, entityDisplayView->isDisplayShadowing() == true ? u"true"_j : u"false"_j);
		settings->put(u"particlesystem.path"_j, particleSystemScreenController->getParticleSystemPath()->getPath());
		settings->put(u"model.path"_j, particleSystemScreenController->getModelPath()->getPath());
		settings->store(L"settings", L"particlesystem.properties");
	} catch (_Exception& exception) {
		_Console::print(string("SharedParticleSystemView::storeSettings(): An error occurred "));
		_Console::println(string(exception.what()));
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
	_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Particle system file: "_j)->append(static_cast< Object* >(particleSystemFile))->toString()));
	try {
		auto oldEntity = entity;
		entity = loadParticleSystem(
			particleSystemFile->getCPPWString(),
			L"",
			_FileSystem::getInstance()->getPathName(particleSystemFile->getCPPWString()),
			_FileSystem::getInstance()->getFileName(particleSystemFile->getCPPWString())
		);
		onLoadParticleSystem(oldEntity, entity);
	} catch (_Exception& exception) {
		popUps->getInfoDialogScreenController()->show(u"Warning"_j, new String(StringConverter::toWideString(exception.what())));
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
