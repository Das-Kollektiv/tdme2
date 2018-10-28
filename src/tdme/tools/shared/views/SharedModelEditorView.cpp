#include <tdme/tools/shared/views/SharedModelEditorView.h>

#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/ModelUtilities.h>
#include <tdme/engine/PartitionNone.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/shared/controller/EntityPhysicsSubScreenController.h>
#include <tdme/tools/shared/controller/EntityDisplaySubScreenController.h>
#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/tools/shared/controller/ModelEditorScreenController.h>
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
#include <tdme/utils/StringUtils.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>
#include <tdme/utils/Properties.h>
#include <tdme/engine/subsystems/rendering/ModelStatistics.h>

using std::string;

using tdme::tools::shared::views::SharedModelEditorView;
using tdme::engine::Engine;
using tdme::engine::ModelUtilities;
using tdme::engine::Object3D;
using tdme::engine::PartitionNone;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::rendering::ModelStatistics;
using tdme::gui::GUI;
using tdme::gui::nodes::GUIScreenNode;
using tdme::math::Vector3;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::shared::controller::EntityPhysicsSubScreenController;
using tdme::tools::shared::controller::EntityDisplaySubScreenController;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::controller::ModelEditorScreenController;
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
using tdme::utils::StringUtils;
using tdme::utils::Console;
using tdme::utils::Exception;

SharedModelEditorView::SharedModelEditorView(PopUps* popUps) 
{
	this->popUps = popUps;
	engine = Engine::getInstance();
	modelEditorScreenController = nullptr;
	entityDisplayView = nullptr;
	loadModelRequested = false;
	initModelRequested = false;
	initModelRequestedReset = false;
	entity = nullptr;
	modelFile = "";
	lodLevel = 1;
	cameraRotationInputHandler = new CameraRotationInputHandler(engine);
}

SharedModelEditorView::~SharedModelEditorView() {
	delete modelEditorScreenController;
	delete cameraRotationInputHandler;
}

PopUps* SharedModelEditorView::getPopUpsViews()
{
	return popUps;
}

LevelEditorEntity* SharedModelEditorView::getEntity()
{
	return entity;
}

void SharedModelEditorView::setEntity(LevelEditorEntity* entity)
{
	engine->reset();
	this->entity = entity;
	lodLevel = 1;
	initModelRequested = true;
	initModelRequestedReset = false;
}

void SharedModelEditorView::resetEntity()
{
	engine->reset();
	initModelRequested = true;
	initModelRequestedReset = true;
}

void SharedModelEditorView::initModel()
{
	if (entity == nullptr) return;

	modelFile = entity->getEntityFileName().length() > 0 ? entity->getEntityFileName() : entity->getFileName();
	Tools::setupEntity(entity, engine, cameraRotationInputHandler->getLookFromRotations(), cameraRotationInputHandler->getScale(), lodLevel);
	Tools::oseThumbnail(entity);
	cameraRotationInputHandler->setMaxAxisDimension(Tools::computeMaxAxisDimension(entity->getModel()->getBoundingBox()));
	auto currentModelObject = dynamic_cast<Object3D*>(engine->getEntity("model"));
	if (currentModelObject != nullptr) {
		ModelStatistics modelStatistics;
		ModelUtilities::computeModelStatistics(currentModelObject->getModel(), &modelStatistics);
		modelEditorScreenController->setStatistics(modelStatistics.opaqueFaceCount, modelStatistics.transparentFaceCount, modelStatistics.materialCount);
	} else {
		modelEditorScreenController->unsetStatistics();
	}
	if (initModelRequestedReset == false) updateGUIElements();
}

const string& SharedModelEditorView::getFileName()
{
	return modelFile;
}

int SharedModelEditorView::getLodLevel() const {
	return lodLevel;
}

void SharedModelEditorView::setLodLevel(int lodLevel) {
	if (this->lodLevel != lodLevel) {
		this->lodLevel = lodLevel;
		engine->reset();
		initModelRequested = true;
		modelEditorScreenController->setMaterials(entity);
		modelEditorScreenController->setAnimations(entity);
	}
}

void SharedModelEditorView::loadFile(const string& pathName, const string& fileName)
{
	loadModelRequested = true;
	modelFile = FileSystem::getInstance()->getFileName(pathName, fileName);
}

void SharedModelEditorView::saveFile(const string& pathName, const string& fileName) /* throws(Exception) */
{
	ModelMetaDataFileExport::export_(pathName, fileName, entity);
}

void SharedModelEditorView::reloadFile()
{
	loadModelRequested = true;
}

void SharedModelEditorView::pivotApply(float x, float y, float z)
{
	if (entity == nullptr)
		return;

	entity->getPivot().set(x, y, z);
}

void SharedModelEditorView::handleInputEvents()
{
	cameraRotationInputHandler->handleInputEvents();
}

void SharedModelEditorView::display()
{
	if (loadModelRequested == true) {
		initModelRequested = true;
		initModelRequestedReset = false;
		loadModelRequested = false;
		loadModel();
		cameraRotationInputHandler->reset();
	}
	if (initModelRequested == true) {
		initModel();
		initModelRequested = false;
		initModelRequestedReset = false;
	}
	entityDisplayView->display(entity);
	engine->getGUI()->handleEvents();
	engine->getGUI()->render();
}

void SharedModelEditorView::updateGUIElements()
{
	if (entity != nullptr) {
		modelEditorScreenController->setScreenCaption("Model Editor - " + (entity->getEntityFileName().length() > 0 ? Tools::getFileName(entity->getEntityFileName()) : Tools::getFileName(entity->getFileName())));
		auto preset = entity->getProperty("preset");
		modelEditorScreenController->setEntityProperties(preset != nullptr ? preset->getValue() : "", entity, "");
		modelEditorScreenController->setEntityData(entity->getName(), entity->getDescription());
		modelEditorScreenController->setPivot(entity->getPivot());
		entityBoundingVolumeView->setBoundingVolumes(entity);
		entityBoundingVolumeView->setPhysics(entity);
		entityBoundingVolumeView->setTerrainMesh(entity);
		entityBoundingVolumeView->setConvexMeshes(entity);
		modelEditorScreenController->setRendering(entity);
		modelEditorScreenController->setLODLevel(entity, lodLevel);
		modelEditorScreenController->setMaterials(entity);
		modelEditorScreenController->setAnimations(entity);
	} else {
		modelEditorScreenController->setScreenCaption("Model Editor - no entity loaded");
		modelEditorScreenController->unsetEntityProperties();
		modelEditorScreenController->unsetEntityData();
		modelEditorScreenController->unsetPivot();
		entityBoundingVolumeView->unsetBoundingVolumes();
		entityBoundingVolumeView->unsetPhysics();
		entityBoundingVolumeView->unsetTerrainMesh();
		entityBoundingVolumeView->unsetConvexMeshes();
		modelEditorScreenController->unsetRendering();
		modelEditorScreenController->unsetLODLevel();
		modelEditorScreenController->unsetMaterials();
		modelEditorScreenController->unsetAnimations();
	}
}

void SharedModelEditorView::onInitAdditionalScreens()
{
}

void SharedModelEditorView::loadSettings()
{
	try {
		Properties settings;
		settings.load("settings", "modeleditor.properties");
		entityDisplayView->setDisplayBoundingVolume(settings.get("display.boundingvolumes", "false") == "true");
		entityDisplayView->setDisplayGroundPlate(settings.get("display.groundplate", "false") == "true");
		entityDisplayView->setDisplayShadowing(settings.get("display.shadowing", "false") == "true");
		modelEditorScreenController->getModelPath()->setPath(settings.get("model.path", "."));
		modelEditorScreenController->getAudioPath()->setPath(settings.get("audio.path", "."));
	} catch (Exception& exception) {
		Console::print(string("SharedModelEditorView::loadSettings(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void SharedModelEditorView::initialize()
{
	try {
		modelEditorScreenController = new ModelEditorScreenController(this);
		modelEditorScreenController->initialize();
		entityDisplayView = modelEditorScreenController->getEntityDisplaySubScreenController()->getView();
		entityBoundingVolumeView = modelEditorScreenController->getEntityPhysicsSubScreenController()->getView();
		engine->getGUI()->addScreen(modelEditorScreenController->getScreenNode()->getId(), modelEditorScreenController->getScreenNode());
		modelEditorScreenController->getScreenNode()->setInputEventHandler(this);
	} catch (Exception& exception) {
		Console::print(string("SharedModelEditorView::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	loadSettings();
	modelEditorScreenController->getEntityDisplaySubScreenController()->setupDisplay();
	entityBoundingVolumeView->initialize();
	updateGUIElements();
}

void SharedModelEditorView::activate()
{
	engine->reset();
	engine->setPartition(new PartitionNone());
	engine->getGUI()->resetRenderScreens();
	engine->getGUI()->addRenderScreen(modelEditorScreenController->getScreenNode()->getId());
	onInitAdditionalScreens();
	engine->getGUI()->addRenderScreen(popUps->getFileDialogScreenController()->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(popUps->getInfoDialogScreenController()->getScreenNode()->getId());
}

void SharedModelEditorView::storeSettings()
{
	try {
		Properties settings;
		settings.put("display.boundingvolumes", entityDisplayView->isDisplayBoundingVolume() == true ? "true" : "false");
		settings.put("display.groundplate", entityDisplayView->isDisplayGroundPlate() == true ? "true" : "false");
		settings.put("display.shadowing", entityDisplayView->isDisplayShadowing() == true ? "true" : "false");
		settings.put("model.path", modelEditorScreenController->getModelPath()->getPath());
		settings.put("audio.path", modelEditorScreenController->getAudioPath()->getPath());
		settings.store("settings", "modeleditor.properties");
	} catch (Exception& exception) {
		Console::print(string("SharedModelEditorView::storeSettings(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void SharedModelEditorView::deactivate()
{
}

void SharedModelEditorView::dispose()
{
	storeSettings();
	Engine::getInstance()->reset();
}

void SharedModelEditorView::onLoadModel(LevelEditorEntity* oldEntity, LevelEditorEntity* entity)
{
	delete oldEntity;
}

void SharedModelEditorView::loadModel()
{
	Console::println(string("Model file: " + modelFile));
	try {
		auto oldEntity = entity;
		setEntity(
			loadModel(
				FileSystem::getInstance()->getFileName(modelFile),
				"",
				FileSystem::getInstance()->getPathName(modelFile),
				FileSystem::getInstance()->getFileName(modelFile),
				Vector3()
			)
		);
		onLoadModel(oldEntity, entity);
	} catch (Exception& exception) {
		popUps->getInfoDialogScreenController()->show("Warning", (exception.what()));
	}
}

LevelEditorEntity* SharedModelEditorView::loadModel(const string& name, const string& description, const string& pathName, const string& fileName, const Vector3& pivot) /* throws(Exception) */
{
	if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".tmm") == true) {
		auto levelEditorEntity = ModelMetaDataFileImport::doImport(
			LevelEditorEntity::ID_NONE,
			pathName,
			fileName
		);
		levelEditorEntity->setDefaultBoundingVolumes();
		return levelEditorEntity;
	} else {
		auto model = ModelReader::read(
			pathName,
			fileName
		);
		auto levelEditorEntity = new LevelEditorEntity(
			LevelEditorEntity::ID_NONE,
			LevelEditorEntity_EntityType::MODEL,
			name,
			description,
			"",
			pathName + "/" + fileName,
			StringUtils::replace(StringUtils::replace(StringUtils::replace(model->getId(), "\\", "_"), "/", "_"), ":", "_") + ".png",
			model,
			pivot
			);
		levelEditorEntity->setDefaultBoundingVolumes();
		return levelEditorEntity;

	}
	return nullptr;
}

void SharedModelEditorView::playAnimation(const string& animationId) {
	auto object = dynamic_cast<Object3D*>(engine->getEntity("model"));
	if (object != nullptr) {
		object->setAnimation(animationId);
	}
}

void SharedModelEditorView::onSetEntityData()
{
}

