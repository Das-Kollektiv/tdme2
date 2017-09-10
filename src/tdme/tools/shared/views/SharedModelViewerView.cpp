#include <tdme/tools/shared/views/SharedModelViewerView.h>

#include <string>

#include <java/lang/CharSequence.h>
#include <java/lang/String.h>
#include <java/util/Properties.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/ModelUtilities.h>
#include <tdme/engine/PartitionNone.h>
#include <tdme/engine/fileio/models/DAEReader.h>
#include <tdme/engine/fileio/models/TMReader.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/BoundingBox.h>
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
#include <tdme/utils/StringUtils.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/_Exception.h>
#include "../../../engine/subsystems/object/ModelStatistics.h"

using std::wstring;

using tdme::tools::shared::views::SharedModelViewerView;
using java::lang::CharSequence;
using java::lang::Object;
using java::lang::String;
using java::util::Properties;
using tdme::engine::Engine;
using tdme::engine::ModelUtilities;
using tdme::engine::PartitionNone;
using tdme::engine::fileio::models::DAEReader;
using tdme::engine::fileio::models::TMReader;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::object::ModelStatistics;
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
using tdme::utils::StringUtils;
using tdme::utils::StringConverter;
using tdme::utils::_Console;
using tdme::utils::_Exception;

SharedModelViewerView::SharedModelViewerView(PopUps* popUps) 
{
	this->popUps = popUps;
	engine = Engine::getInstance();
	modelViewerScreenController = nullptr;
	entityDisplayView = nullptr;
	loadModelRequested = false;
	initModelRequested = false;
	entity = nullptr;
	modelFile = L"";
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

	modelFile = entity->getEntityFileName().length() > 0 ? entity->getEntityFileName() : entity->getFileName();
	Tools::setupEntity(entity, engine, cameraRotationInputHandler->getLookFromRotations(), cameraRotationInputHandler->getScale());
	Tools::oseThumbnail(entity);
	cameraRotationInputHandler->setMaxAxisDimension(Tools::computeMaxAxisDimension(entity->getModel()->getBoundingBox()));
	ModelStatistics modelStatistics;
	ModelUtilities::computeModelStatistics(entity->getModel(), &modelStatistics);
	modelViewerScreenController->setStatistics(modelStatistics.opaqueFaceCount, modelStatistics.transparentFaceCount, modelStatistics.materialCount);
	updateGUIElements();
}

const wstring& SharedModelViewerView::getFileName()
{
	return modelFile;
}

void SharedModelViewerView::loadFile(const wstring& pathName, const wstring& fileName)
{
	loadModelRequested = true;
	modelFile = _FileSystem::getInstance()->getFileName(pathName, fileName);
}

void SharedModelViewerView::saveFile(const wstring& pathName, const wstring& fileName) /* throws(Exception) */
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
		modelViewerScreenController->setScreenCaption(L"Model Viewer - " + (entity->getEntityFileName().length() > 0 ? Tools::getFileName(entity->getEntityFileName()) : Tools::getFileName(entity->getFileName())));
		auto preset = entity->getProperty(L"preset");
		modelViewerScreenController->setEntityProperties(preset != nullptr ? preset->getValue() : L"", entity, L"");
		modelViewerScreenController->setEntityData(entity->getName(), entity->getDescription());
		modelViewerScreenController->setPivot(entity->getPivot());
		entityBoundingVolumeView->setBoundingVolumes(entity);
	} else {
		modelViewerScreenController->setScreenCaption(L"Model Viewer - no entity loaded");
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
		settings->load(L"settings", L"modelviewer.properties");
		entityDisplayView->setDisplayBoundingVolume((tmp = dynamic_cast< Object* >(settings->get(u"display.boundingvolumes"_j))) != nullptr ? tmp->equals(u"true"_j) == true : false);
		entityDisplayView->setDisplayGroundPlate((tmp = dynamic_cast< Object* >(settings->get(u"display.groundplate"_j))) != nullptr ? tmp->equals(u"true"_j) == true : false);
		entityDisplayView->setDisplayShadowing((tmp = dynamic_cast< Object* >(settings->get(u"display.shadowing"_j))) != nullptr ? tmp->equals(u"true"_j) == true : false);
		modelViewerScreenController->getModelPath()->setPath(((tmp = dynamic_cast< Object* >(settings->get(u"model.path"_j))) != nullptr ? tmp->toString() : u"."_j)->getCPPWString());
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
		settings->put(u"model.path"_j, new String(modelViewerScreenController->getModelPath()->getPath()));
		settings->store(L"settings", L"modelviewer.properties");
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
	_Console::println(wstring(L"Model file: " + modelFile));
	try {
		auto oldModel = entity;
		entity = loadModel(
			_FileSystem::getInstance()->getFileName(modelFile),
			L"",
			_FileSystem::getInstance()->getPathName(modelFile),
			_FileSystem::getInstance()->getFileName(modelFile),
			new Vector3());
		onLoadModel(oldModel, entity);
	} catch (_Exception& exception) {
		popUps->getInfoDialogScreenController()->show(L"Warning", StringConverter::toWideString(exception.what()));
	}
}

LevelEditorEntity* SharedModelViewerView::loadModel(const wstring& name, const wstring& description, const wstring& pathName, const wstring& fileName, Vector3* pivot) /* throws(Exception) */
{
	if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), L".dae") == true) {
		auto model = DAEReader::read(
			pathName,
			fileName
		);
		auto levelEditorEntity = new LevelEditorEntity(
			LevelEditorEntity::ID_NONE,
			LevelEditorEntity_EntityType::MODEL,
			name,
			description,
			L"",
			pathName + L"/" + fileName,
			StringUtils::replace(StringUtils::replace(StringUtils::replace(model->getId(), L"\\", L"_"), L"/", L"_"), L":", L"_") + L".png",
			model,
			pivot
			);
		levelEditorEntity->setDefaultBoundingVolumes();
		return levelEditorEntity;
	} else
	if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), L".tm") == true) {
		auto model = TMReader::read(
			pathName,
			fileName
		);
		auto levelEditorEntity = new LevelEditorEntity(
			LevelEditorEntity::ID_NONE,
			LevelEditorEntity_EntityType::MODEL,
			name,
			description,
			L"",
			pathName + L"/" + fileName,
			StringUtils::replace(StringUtils::replace(StringUtils::replace(model->getId(), L"\\", L"_"), L"/", L"_"), L":", L"_") + L".png",
			model,
			pivot
		);
		levelEditorEntity->setDefaultBoundingVolumes();
		return levelEditorEntity;
	} else
		if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), L".tmm") == true) {
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

