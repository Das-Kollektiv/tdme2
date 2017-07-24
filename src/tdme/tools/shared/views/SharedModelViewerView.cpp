// Generated from /tdme/src/tdme/tools/shared/views/SharedModelViewerView.java
#include <tdme/tools/shared/views/SharedModelViewerView.h>

#include <java/lang/CharSequence.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Properties.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/ModelUtilities.h>
#include <tdme/engine/PartitionNone.h>
#include <tdme/engine/fileio/models/DAEReader.h>
#include <tdme/engine/fileio/models/TMReader.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/subsystems/object/ModelUtilitiesInternal_ModelStatistics.h>
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
#include <tdme/tools/shared/controller/ModelViewerScreenController.h>
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
#include <tdme/utils/_Console.h>
#include <tdme/utils/_Exception.h>

using tdme::tools::shared::views::SharedModelViewerView;
using java::lang::CharSequence;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Properties;
using tdme::engine::Engine;
using tdme::engine::ModelUtilities;
using tdme::engine::PartitionNone;
using tdme::engine::fileio::models::DAEReader;
using tdme::engine::fileio::models::TMReader;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::object::ModelUtilitiesInternal_ModelStatistics;
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
using tdme::tools::shared::controller::ModelViewerScreenController;
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
using tdme::utils::_Console;
using tdme::utils::_Exception;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

SharedModelViewerView::SharedModelViewerView(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

SharedModelViewerView::SharedModelViewerView(PopUps* popUps) 
	: SharedModelViewerView(*static_cast< ::default_init_tag* >(0))
{
	ctor(popUps);
}

void SharedModelViewerView::ctor(PopUps* popUps)
{
	super::ctor();
	this->popUps = popUps;
	engine = Engine::getInstance();
	modelViewerScreenController = nullptr;
	entityDisplayView = nullptr;
	loadModelRequested = false;
	initModelRequested = false;
	entity = nullptr;
	modelFile = nullptr;
	cameraRotationInputHandler = new CameraRotationInputHandler(engine);
}

PopUps* SharedModelViewerView::getPopUpsViews()
{
	return popUps;
}

LevelEditorEntity* SharedModelViewerView::getEntity()
{
	return entity;
}

void SharedModelViewerView::setEntity(LevelEditorEntity* entity)
{
	this->entity = entity;
	initModelRequested = true;
}

void SharedModelViewerView::initModel()
{
	if (entity == nullptr)
		return;

	modelFile = entity->getEntityFileName() != nullptr ? entity->getEntityFileName() : entity->getFileName();
	Tools::setupEntity(entity, engine, cameraRotationInputHandler->getLookFromRotations(), cameraRotationInputHandler->getScale());
	Tools::oseThumbnail(entity);
	cameraRotationInputHandler->setMaxAxisDimension(Tools::computeMaxAxisDimension(entity->getModel()->getBoundingBox()));
	auto stats = ModelUtilities::computeModelStatistics(entity->getModel());
	modelViewerScreenController->setStatistics(stats->getOpaqueFaceCount(), stats->getTransparentFaceCount(), stats->getMaterialCount());
	updateGUIElements();
}

String* SharedModelViewerView::getFileName()
{
	if (modelFile == nullptr)
		return u""_j;

	return modelFile;
}

void SharedModelViewerView::loadFile(String* pathName, String* fileName)
{
	loadModelRequested = true;
	modelFile = _FileSystem::getInstance()->getFileName(pathName, fileName);
}

void SharedModelViewerView::saveFile(String* pathName, String* fileName) /* throws(Exception) */
{
	ModelMetaDataFileExport::export_(pathName, fileName, entity);
}

void SharedModelViewerView::reloadFile()
{
	loadModelRequested = true;
}

void SharedModelViewerView::pivotApply(float x, float y, float z)
{
	if (entity == nullptr)
		return;

	entity->getPivot()->set(x, y, z);
}

void SharedModelViewerView::handleInputEvents()
{
	cameraRotationInputHandler->handleInputEvents();
}

void SharedModelViewerView::display()
{
	if (loadModelRequested == true) {
		initModelRequested = true;
		loadModelRequested = false;
		loadModel();
		cameraRotationInputHandler->reset();
	}
	if (initModelRequested == true) {
		engine->reset();
		initModel();
		initModelRequested = false;
	}
	entityDisplayView->display(entity);
	engine->getGUI()->render();
	engine->getGUI()->handleEvents();
}

void SharedModelViewerView::updateGUIElements()
{
	if (entity != nullptr) {
		modelViewerScreenController->setScreenCaption(::java::lang::StringBuilder().append(u"Model Viewer - "_j)->append((entity->getEntityFileName() != nullptr ? Tools::getFileName(entity->getEntityFileName()) : Tools::getFileName(entity->getFileName())))->toString());
		auto preset = entity->getProperty(u"preset"_j);
		modelViewerScreenController->setEntityProperties(preset != nullptr ? preset->getValue() : static_cast< String* >(nullptr), entity, nullptr);
		modelViewerScreenController->setEntityData(entity->getName(), entity->getDescription());
		modelViewerScreenController->setPivot(entity->getPivot());
		entityBoundingVolumeView->setBoundingVolumes(entity);
	} else {
		modelViewerScreenController->setScreenCaption(u"Model Viewer - no entity loaded"_j);
		modelViewerScreenController->unsetEntityProperties();
		modelViewerScreenController->unsetEntityData();
		modelViewerScreenController->unsetPivot();
		entityBoundingVolumeView->unsetBoundingVolumes();
	}
}

void SharedModelViewerView::onInitAdditionalScreens()
{
}

void SharedModelViewerView::loadSettings()
{
	try {
		Object* tmp;
		auto settings = new Properties();
		settings->load(_FileSystem::getInstance()->getContentAsStringArray(u"settings"_j, u"modelviewer.properties"_j));
		entityDisplayView->setDisplayBoundingVolume((tmp = java_cast< Object* >(settings->get(u"display.boundingvolumes"_j))) != nullptr ? tmp->equals(u"true"_j) == true : false);
		entityDisplayView->setDisplayGroundPlate((tmp = java_cast< Object* >(settings->get(u"display.groundplate"_j))) != nullptr ? tmp->equals(u"true"_j) == true : false);
		entityDisplayView->setDisplayShadowing((tmp = java_cast< Object* >(settings->get(u"display.shadowing"_j))) != nullptr ? tmp->equals(u"true"_j) == true : false);
		modelViewerScreenController->getModelPath()->setPath((tmp = java_cast< Object* >(settings->get(u"model.path"_j))) != nullptr ? tmp->toString() : u"."_j);
	} catch (_Exception& exception) {
		_Console::print(string("SharedModelViewerView::loadSettings(): An error occurred: "));
		_Console::println(string(exception.what()));
	}
}

void SharedModelViewerView::initialize()
{
	try {
		modelViewerScreenController = new ModelViewerScreenController(this);
		modelViewerScreenController->initialize();
		entityDisplayView = modelViewerScreenController->getEntityDisplaySubScreenController()->getView();
		entityBoundingVolumeView = modelViewerScreenController->getEntityBoundingVolumeSubScreenController()->getView();
		engine->getGUI()->addScreen(modelViewerScreenController->getScreenNode()->getId(), modelViewerScreenController->getScreenNode());
		modelViewerScreenController->getScreenNode()->setInputEventHandler(this);
	} catch (_Exception& exception) {
		_Console::print(string("SharedModelViewerView::initialize(): An error occurred: "));
		_Console::println(string(exception.what()));
	}
	loadSettings();
	modelViewerScreenController->getEntityDisplaySubScreenController()->setupDisplay();
	entityBoundingVolumeView->initialize();
	updateGUIElements();
}

void SharedModelViewerView::activate()
{
	engine->reset();
	engine->setPartition(new PartitionNone());
	engine->getGUI()->resetRenderScreens();
	engine->getGUI()->addRenderScreen(modelViewerScreenController->getScreenNode()->getId());
	onInitAdditionalScreens();
	engine->getGUI()->addRenderScreen(popUps->getFileDialogScreenController()->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(popUps->getInfoDialogScreenController()->getScreenNode()->getId());
}

void SharedModelViewerView::storeSettings()
{
	try {
		auto settings = new Properties();
		settings->put(u"display.boundingvolumes"_j, entityDisplayView->isDisplayBoundingVolume() == true ? u"true"_j : u"false"_j);
		settings->put(u"display.groundplate"_j, entityDisplayView->isDisplayGroundPlate() == true ? u"true"_j : u"false"_j);
		settings->put(u"display.shadowing"_j, entityDisplayView->isDisplayShadowing() == true ? u"true"_j : u"false"_j);
		settings->put(u"model.path"_j, modelViewerScreenController->getModelPath()->getPath());
		StringArray* settingsStringArray = settings->storeToStringArray();
		_FileSystem::getInstance()->setContentFromStringArray(u"settings"_j, u"modelviewer.properties"_j, settingsStringArray);
	} catch (_Exception& exception) {
		_Console::print(string("SharedModelViewerView::storeSettings(): An error occurred: "));
		_Console::println(string(exception.what()));
	}
}

void SharedModelViewerView::deactivate()
{
}

void SharedModelViewerView::dispose()
{
	storeSettings();
	Engine::getInstance()->reset();
}

void SharedModelViewerView::onLoadModel(LevelEditorEntity* oldModel, LevelEditorEntity* model)
{
}

void SharedModelViewerView::loadModel()
{
	_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Model file: "_j)->append(static_cast< Object* >(modelFile))->toString()));
	try {
		auto oldModel = entity;
		entity = loadModel(
			_FileSystem::getInstance()->getFileName(modelFile),
			u""_j,
			_FileSystem::getInstance()->getPathName(modelFile),
			_FileSystem::getInstance()->getFileName(modelFile),
			new Vector3());
		onLoadModel(oldModel, entity);
	} catch (_Exception& exception) {
		popUps->getInfoDialogScreenController()->show(u"Warning"_j, new String(StringConverter::toWideString(exception.what())));
	}
}

LevelEditorEntity* SharedModelViewerView::loadModel(String* name, String* description, String* pathName, String* fileName, Vector3* pivot) /* throws(Exception) */
{
	if (fileName->toLowerCase()->endsWith(u".dae"_j)) {
		auto model = DAEReader::read(
			pathName,
			fileName
		);
		auto levelEditorEntity = new LevelEditorEntity(
			LevelEditorEntity::ID_NONE,
			LevelEditorEntity_EntityType::MODEL,
			name,
			description,
			nullptr,
			::java::lang::StringBuilder().
				append(pathName)->
				append(new String(wstring(L"/")))->
				append(fileName)->
				toString(),
			::java::lang::StringBuilder().
				append(
			  		(new String(model->getId()))->
						replace(static_cast< CharSequence* >(u"\\"_j), static_cast< CharSequence* >(u"_"_j))->
						replace(static_cast< CharSequence* >(u"/"_j), static_cast< CharSequence* >(u"_"_j))->
						replace(static_cast< CharSequence* >(u":"_j), static_cast< CharSequence* >(u"_"_j))
				)->
					append(u".png"_j)->
					toString(),
					model,
					pivot
			);
		levelEditorEntity->setDefaultBoundingVolumes();
		return levelEditorEntity;
	} else
	if (fileName->toLowerCase()->endsWith(u".tm"_j)) {
		auto model = TMReader::read(
			pathName,
			fileName
		);
		auto levelEditorEntity = new LevelEditorEntity(
			LevelEditorEntity::ID_NONE,
			LevelEditorEntity_EntityType::MODEL,
			name,
			description,
			nullptr,
			::java::lang::StringBuilder().
				append(pathName)->
				append(L'/')->
				append(fileName)->toString(),
			::java::lang::StringBuilder().
			 	 append(
					(new String(model->getId()))->
						replace(static_cast< CharSequence* >(u"\\"_j), static_cast< CharSequence* >(u"_"_j))->
						replace(static_cast< CharSequence* >(u"/"_j), static_cast< CharSequence* >(u"_"_j))->
						replace(static_cast< CharSequence* >(u":"_j), static_cast< CharSequence* >(u"_"_j))
				)->
					append(u".png"_j)->
					toString(),
				model,
				pivot
		);
		levelEditorEntity->setDefaultBoundingVolumes();
		return levelEditorEntity;
	} else
	if (fileName->toLowerCase()->endsWith(u".tmm"_j)) {
		auto levelEditorEntity = ModelMetaDataFileImport::doImport(
			LevelEditorEntity::ID_NONE,
			pathName,
			fileName
		);
		levelEditorEntity->setDefaultBoundingVolumes();
		return levelEditorEntity;
	}
	return nullptr;
}

void SharedModelViewerView::onSetEntityData()
{
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* SharedModelViewerView::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.views.SharedModelViewerView", 45);
    return c;
}

java::lang::Class* SharedModelViewerView::getClass0()
{
	return class_();
}

