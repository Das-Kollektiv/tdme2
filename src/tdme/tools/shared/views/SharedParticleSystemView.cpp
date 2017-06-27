// Generated from /tdme/src/tdme/tools/shared/views/SharedParticleSystemView.java
#include <tdme/tools/shared/views/SharedParticleSystemView.h>

#include <java/io/File.h>
#include <java/io/FileInputStream.h>
#include <java/io/FileOutputStream.h>
#include <java/io/IOException.h>
#include <java/io/InputStream.h>
#include <java/io/OutputStream.h>
#include <java/lang/ClassCastException.h>
#include <java/lang/Exception.h>
#include <java/lang/Object.h>
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
#include <tdme/utils/_ArrayList.h>
#include <tdme/utils/_Console.h>

using tdme::tools::shared::views::SharedParticleSystemView;
using java::io::File;
using java::io::FileInputStream;
using java::io::FileOutputStream;
using java::io::IOException;
using java::io::InputStream;
using java::io::OutputStream;
using java::lang::ClassCastException;
using java::lang::Exception;
using java::lang::Object;
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
using tdme::utils::_ArrayList;
using tdme::utils::_Console;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

SharedParticleSystemView::SharedParticleSystemView(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

SharedParticleSystemView::SharedParticleSystemView(PopUps* popUps) 
	: SharedParticleSystemView(*static_cast< ::default_init_tag* >(0))
{
	ctor(popUps);
}

void SharedParticleSystemView::ctor(PopUps* popUps)
{
	super::ctor();
	this->popUps = popUps;
	engine = Engine::getInstance();
	particleSystemScreenController = nullptr;
	entityDisplayView = nullptr;
	loadParticleSystemRequested = false;
	initParticleSystemRequested = false;
	particleSystemFile = nullptr;
	cameraRotationInputHandler = new CameraRotationInputHandler(engine);
	entity = new LevelEditorEntity(-1, LevelEditorEntity_EntityType::PARTICLESYSTEM, u"Untitled"_j, u""_j, u"Untitled.tps"_j, nullptr, nullptr, nullptr, new Vector3());
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

void SharedParticleSystemView::initParticleSystem()
{
	initParticleSystemRequested = true;
}

void SharedParticleSystemView::initParticleSystem(GLAutoDrawable* drawable)
{
	if (entity == nullptr)
		return;

	particleSystemFile = entity->getEntityFileName() != nullptr ? new File(entity->getEntityFileName()) : static_cast< File* >(nullptr);
	Tools::setupEntity(entity, engine, cameraRotationInputHandler->getLookFromRotations(), cameraRotationInputHandler->getScale());
	Tools::oseThumbnail(drawable, entity);
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

	return particleSystemFile->getName();
}

void SharedParticleSystemView::loadFile(String* pathName, String* fileName)
{
	loadParticleSystemRequested = true;
	particleSystemFile = new File(pathName, fileName);
}

void SharedParticleSystemView::saveFile(String* pathName, String* fileName) /* throws(Exception) */
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

void SharedParticleSystemView::display(GLAutoDrawable* drawable)
{
	if (loadParticleSystemRequested == true) {
		initParticleSystemRequested = true;
		loadParticleSystemRequested = false;
		loadParticleSystem();
		cameraRotationInputHandler->reset();
	}
	if (initParticleSystemRequested == true) {
		engine->reset();
		initParticleSystem(drawable);
		particleSystemScreenController->setParticleSystemType();
		particleSystemScreenController->setParticleSystemEmitter();
		initParticleSystemRequested = false;
	}
	auto particleSystemEntity = java_cast< ParticleSystemEntity* >(engine->getEntity(u"model"_j));
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
		particleSystemScreenController->setScreenCaption(::java::lang::StringBuilder().append(u"Particle System - "_j)->append((entity->getEntityFileName() != nullptr ? Tools::getFileName(entity->getEntityFileName()) : entity->getName()))->toString());
		auto preset = entity->getProperty(u"preset"_j);
		particleSystemScreenController->setEntityProperties(preset != nullptr ? preset->getValue() : static_cast< String* >(nullptr), entity->getProperties(), nullptr);
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
	FileInputStream* fis = nullptr;
	Object* tmp;
	try {
		fis = new FileInputStream(u"./settings/particlesystem.properties"_j);
		auto settings = new Properties();
		settings->load(static_cast< InputStream* >(fis));
		entityDisplayView->setDisplayBoundingVolume((tmp = java_cast< Object* >(settings->get(u"display.boundingvolumes"_j))) != nullptr ? tmp->equals(u"true"_j) == true : false);
		entityDisplayView->setDisplayGroundPlate((tmp = java_cast< Object* >(settings->get(u"display.groundplate"_j))) != nullptr ? tmp->equals(u"true"_j) == true : false);
		entityDisplayView->setDisplayShadowing((tmp = java_cast< Object* >(settings->get(u"display.shadowing"_j))) != nullptr ? tmp->equals(u"true"_j) == true : false);
		particleSystemScreenController->getParticleSystemPath()->setPath((tmp = java_cast< Object* >(settings->get(u"particlesystem.path"_j))) != nullptr ? tmp->toString() : u""_j);
		particleSystemScreenController->getModelPath()->setPath((tmp = java_cast< Object* >(settings->get(u"model.path"_j))) != nullptr ? tmp->toString() : u""_j);
		fis->close();
	} catch (Exception* ioe) {
		if (fis != nullptr)
			try {
				fis->close();
			} catch (IOException* ioeInner) {
			}

		ioe->printStackTrace();
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
	} catch (Exception* e) {
		e->printStackTrace();
	}
	loadSettings();
	entityBoundingVolumeView->initialize();
	auto particleSystemTypes = new _ArrayList();
	particleSystemTypes->add(u"None"_j);
	particleSystemTypes->add(u"Object Particle System"_j);
	particleSystemTypes->add(u"Points Particle System"_j);
	particleSystemScreenController->setParticleSystemTypes(particleSystemTypes);
	auto particleSystemEmitters = new _ArrayList();
	particleSystemEmitters->add(u"None"_j);
	particleSystemEmitters->add(u"Point Particle Emitter"_j);
	particleSystemEmitters->add(u"BoundingBox Particle Emitter"_j);
	particleSystemEmitters->add(u"Circle Particle Emitter"_j);
	particleSystemEmitters->add(u"Circle Particle Emitter Plane Velocity"_j);
	particleSystemEmitters->add(u"Sphere Particle Emitter"_j);
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
	FileOutputStream* fos = nullptr;
	try {
		fos = new FileOutputStream(u"./settings/particlesystem.properties"_j);
		auto settings = new Properties();
		settings->put(u"display.boundingvolumes"_j, entityDisplayView->isDisplayBoundingVolume() == true ? u"true"_j : u"false"_j);
		settings->put(u"display.groundplate"_j, entityDisplayView->isDisplayGroundPlate() == true ? u"true"_j : u"false"_j);
		settings->put(u"display.shadowing"_j, entityDisplayView->isDisplayShadowing() == true ? u"true"_j : u"false"_j);
		settings->put(u"particlesystem.path"_j, particleSystemScreenController->getParticleSystemPath()->getPath());
		settings->put(u"model.path"_j, particleSystemScreenController->getModelPath()->getPath());
		settings->store(static_cast< OutputStream* >(fos), static_cast< String* >(nullptr));
		fos->close();
	} catch (Exception* ioe) {
		if (fos != nullptr)
			try {
				fos->close();
			} catch (IOException* ioeInner) {
			}

		ioe->printStackTrace();
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
		entity = loadParticleSystem(particleSystemFile->getName(), u""_j, particleSystemFile->getParentFile()->getAbsolutePath(), particleSystemFile->getName());
		onLoadParticleSystem(oldEntity, entity);
	} catch (Exception* exception) {
		exception->printStackTrace();
		popUps->getInfoDialogScreenController()->show(u"Warning"_j, exception->getMessage());
	}
}

LevelEditorEntity* SharedParticleSystemView::loadParticleSystem(String* name, String* description, String* pathName, String* fileName) /* throws(Exception) */
{
	if (fileName->toLowerCase()->endsWith(u".tps"_j)) {
		auto levelEditorEntity = ModelMetaDataFileImport::doImport(LevelEditorEntity::ID_NONE, pathName, fileName);
		levelEditorEntity->setDefaultBoundingVolumes();
		return levelEditorEntity;
	}
	return nullptr;
}

void SharedParticleSystemView::onSetEntityData()
{
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* SharedParticleSystemView::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.views.SharedParticleSystemView", 48);
    return c;
}

java::lang::Class* SharedParticleSystemView::getClass0()
{
	return class_();
}

