#include <tdme/tools/leveleditor/views/EnvironmentMappingView.h>

#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/PartitionNone.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/leveleditor/TDMELevelEditor.h>
#include <tdme/tools/leveleditor/controller/LevelEditorEntityLibraryScreenController.h>
#include <tdme/tools/leveleditor/controller/EnvironmentMappingScreenController.h>
#include <tdme/tools/shared/controller/EntityPhysicsSubScreenController.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityLibrary.h>
#include <tdme/tools/shared/model/LevelEditorLevel.h>
#include <tdme/tools/shared/model/PropertyModelClass.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/tools/shared/views/CameraRotationInputHandler.h>
#include <tdme/tools/shared/views/CameraRotationInputHandlerEventHandler.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using tdme::tools::leveleditor::views::EnvironmentMappingView;
using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::PartitionNone;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::gui::GUI;
using tdme::gui::nodes::GUIScreenNode;
using tdme::math::Vector3;
using tdme::tools::leveleditor::TDMELevelEditor;
using tdme::tools::leveleditor::controller::LevelEditorEntityLibraryScreenController;
using tdme::tools::leveleditor::controller::EnvironmentMappingScreenController;
using tdme::tools::shared::controller::EntityPhysicsSubScreenController;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityLibrary;
using tdme::tools::shared::model::LevelEditorLevel;
using tdme::tools::shared::model::PropertyModelClass;
using tdme::tools::shared::tools::Tools;
using tdme::tools::shared::views::CameraRotationInputHandler;
using tdme::tools::shared::views::CameraRotationInputHandlerEventHandler;
using tdme::tools::shared::views::PopUps;
using tdme::utilities::Console;
using tdme::utilities::Exception;

EnvironmentMappingView::EnvironmentMappingView(PopUps* popUps)
{
	this->popUps = popUps;
	environmentMappingScreenController = nullptr;
	entity = nullptr;
	engine = Engine::getInstance();
	cameraRotationInputHandler = new CameraRotationInputHandler(engine, this);
}

EnvironmentMappingView::~EnvironmentMappingView() {
	delete cameraRotationInputHandler;
	delete environmentMappingScreenController;
}

PopUps* EnvironmentMappingView::getPopUpsViews()
{
	return popUps;
}

LevelEditorEntity* EnvironmentMappingView::getEntity()
{
	return entity;
}

void EnvironmentMappingView::setEntity(LevelEditorEntity* entity)
{
	engine->reset();
	this->entity = entity;
	Tools::setupEntity(entity, engine, cameraRotationInputHandler->getLookFromRotations(), cameraRotationInputHandler->getScale(), 1, objectScale);
	Tools::oseThumbnail(entity);
	cameraRotationInputHandler->setMaxAxisDimension(Tools::computeMaxAxisDimension(engine->getEntity(LevelEditorEntity::MODEL_BOUNDINGVOLUMES_ID)->getBoundingBox()));
	updateGUIElements();
}

void EnvironmentMappingView::handleInputEvents()
{
	cameraRotationInputHandler->handleInputEvents();
}

void EnvironmentMappingView::display()
{
	// viewport
	auto xScale = (float)engine->getWidth() / (float)environmentMappingScreenController->getScreenNode()->getScreenWidth();
	auto yScale = (float)engine->getHeight() / (float)environmentMappingScreenController->getScreenNode()->getScreenHeight();
	auto viewPortLeft = 0;
	auto viewPortTop = 0;
	auto viewPortWidth = 0;
	auto viewPortHeight = 0;
	environmentMappingScreenController->getViewPort(viewPortLeft, viewPortTop, viewPortWidth, viewPortHeight);
	viewPortLeft = (int)((float)viewPortLeft * xScale);
	viewPortTop = (int)((float)viewPortTop * yScale);
	viewPortWidth = (int)((float)viewPortWidth * xScale);
	viewPortHeight = (int)((float)viewPortHeight * yScale);
	engine->getCamera()->enableViewPort(viewPortLeft, viewPortTop, viewPortWidth, viewPortHeight);

	// rendering
	engine->getGUI()->handleEvents();
	engine->getGUI()->render();
}

void EnvironmentMappingView::updateGUIElements()
{
	if (entity != nullptr) {
		environmentMappingScreenController->setScreenCaption("Environment Mapping - " + entity->getName());
		auto preset = entity->getProperty("preset");
		environmentMappingScreenController->setEntityProperties(preset != nullptr ? preset->getValue() : "", "");
		environmentMappingScreenController->setEntityData(entity->getName(), entity->getDescription());
		Vector3 dimension;
		dimension.set(entity->getModel()->getBoundingBox()->getMax());
		dimension.sub(entity->getModel()->getBoundingBox()->getMin());
		environmentMappingScreenController->setDimension(dimension.getX(), dimension.getY(), dimension.getZ());
		environmentMappingScreenController->setGeneration();
	} else {
		environmentMappingScreenController->setScreenCaption("Environment Mapping - no environment mapping loaded");
		environmentMappingScreenController->unsetEntityProperties();
		environmentMappingScreenController->unsetEntityData();
		environmentMappingScreenController->unsetDimension();
		environmentMappingScreenController->unsetGeneration();
	}
}


void EnvironmentMappingView::setDimension(float width, float height, float depth) {
	if (entity == nullptr)
		return;

	//
	engine->reset();

	//
	try {
		auto oldModel = entity;
		entity = TDMELevelEditor::getInstance()->getEntityLibrary()->addEnvironmentMapping(LevelEditorEntityLibrary::ID_ALLOCATE, oldModel->getName(), oldModel->getDescription(), width, height, depth);
		for (auto i = 0; i < oldModel->getPropertyCount(); i++) {
			auto property = oldModel->getPropertyByIndex(i);
			entity->addProperty(property->getName(), property->getValue());
		}
		TDMELevelEditor::getInstance()->getLevel()->replaceEntity(oldModel->getId(), entity->getId());
		TDMELevelEditor::getInstance()->getEntityLibrary()->removeEntity(oldModel->getId());
		TDMELevelEditor::getInstance()->getLevelEditorEntityLibraryScreenController()->setEntityLibrary();
		setEntity(entity);
		updateGUIElements();
	} catch (Exception &exception) {
		popUps->getInfoDialogScreenController()->show("Error", "An error occurred: " + (string(exception.what())));
		environmentMappingScreenController->unsetGeneration();
	}
}

void EnvironmentMappingView::initialize()
{
	try {
		environmentMappingScreenController = new EnvironmentMappingScreenController(this);
		environmentMappingScreenController->initialize();
		engine->getGUI()->addScreen(environmentMappingScreenController->getScreenNode()->getId(), environmentMappingScreenController->getScreenNode());
		environmentMappingScreenController->getScreenNode()->setInputEventHandler(this);
	} catch (Exception& exception) {
		Console::print(string("EnvironmentMappingView::initialize(): An error occurred: "));
		Console::println(exception.what());
	}
}

void EnvironmentMappingView::activate()
{
	engine->reset();
	engine->setPartition(new PartitionNone());
	engine->setShadowMapLightEyeDistanceScale(0.1f);
	engine->getGUI()->resetRenderScreens();
	engine->getGUI()->addRenderScreen(environmentMappingScreenController->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(TDMELevelEditor::getInstance()->getLevelEditorEntityLibraryScreenController()->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(popUps->getFileDialogScreenController()->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(popUps->getInfoDialogScreenController()->getScreenNode()->getId());
}

void EnvironmentMappingView::deactivate()
{
}

void EnvironmentMappingView::dispose()
{
	Engine::getInstance()->reset();
}

void EnvironmentMappingView::onRotation() {
}

void EnvironmentMappingView::onScale() {
}
