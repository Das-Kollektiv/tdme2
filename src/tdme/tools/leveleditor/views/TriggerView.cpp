#include <tdme/tools/leveleditor/views/TriggerView.h>

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
#include <tdme/tools/leveleditor/controller/TriggerScreenController.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityLibrary.h>
#include <tdme/tools/shared/model/LevelEditorLevel.h>
#include <tdme/tools/shared/model/PropertyModelClass.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/tools/shared/views/CameraRotationInputHandler.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>

using tdme::tools::leveleditor::views::TriggerView;
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
using tdme::tools::leveleditor::controller::TriggerScreenController;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityLibrary;
using tdme::tools::shared::model::LevelEditorLevel;
using tdme::tools::shared::model::PropertyModelClass;
using tdme::tools::shared::tools::Tools;
using tdme::tools::shared::views::CameraRotationInputHandler;
using tdme::tools::shared::views::PopUps;
using tdme::utils::StringConverter;
using tdme::utils::Console;
using tdme::utils::Exception;

TriggerView::TriggerView(PopUps* popUps) 
{
	this->popUps = popUps;
	triggerScreenController = nullptr;
	initModelRequested = false;
	entity = nullptr;
	engine = Engine::getInstance();
	cameraRotationInputHandler = new CameraRotationInputHandler(engine);
}

TriggerView::~TriggerView() {
	delete cameraRotationInputHandler;
	delete triggerScreenController;
}

PopUps* TriggerView::getPopUpsViews()
{
	return popUps;
}

LevelEditorEntity* TriggerView::getEntity()
{
	return entity;
}

void TriggerView::setEntity(LevelEditorEntity* entity)
{
	this->entity = entity;
	initModelRequested = true;
}

void TriggerView::initModel()
{
	if (entity == nullptr)
		return;

	Tools::setupEntity(entity, engine, cameraRotationInputHandler->getLookFromRotations(), cameraRotationInputHandler->getScale());
	Tools::oseThumbnail(entity);
	cameraRotationInputHandler->setMaxAxisDimension(Tools::computeMaxAxisDimension(entity->getModel()->getBoundingBox()));
	auto model = engine->getEntity(L"model");
	auto ground = engine->getEntity(L"ground");
	model->setDynamicShadowingEnabled(false);
	ground->setEnabled(false);
	auto modelBoundingVolume = engine->getEntity(L"model_bv");
	if (modelBoundingVolume != nullptr) {
		modelBoundingVolume->setEnabled(false);
	}
	updateGUIElements();
}

void TriggerView::handleInputEvents()
{
	cameraRotationInputHandler->handleInputEvents();
}

void TriggerView::display()
{
	if (initModelRequested == true) {
		initModel();
		cameraRotationInputHandler->reset();
		initModelRequested = false;
	}
	engine->getGUI()->render();
	engine->getGUI()->handleEvents();
}

void TriggerView::updateGUIElements()
{
	if (entity != nullptr) {
		triggerScreenController->setScreenCaption(L"Trigger - " + entity->getName());
		auto preset = entity->getProperty(L"preset");
		triggerScreenController->setEntityProperties(preset != nullptr ? preset->getValue() : L"", L"");
		triggerScreenController->setEntityData(entity->getName(), entity->getDescription());
		Vector3 dimension;
		dimension.set(entity->getModel()->getBoundingBox()->getMax());
		dimension.sub(entity->getModel()->getBoundingBox()->getMin());
		triggerScreenController->setTrigger(dimension.getX(), dimension.getY(), dimension.getZ());
	} else {
		triggerScreenController->setScreenCaption(L"Trigger - no trigger loaded");
		triggerScreenController->unsetEntityProperties();
		triggerScreenController->unsetEntityData();
		triggerScreenController->unsetTrigger();
	}
}

void TriggerView::triggerApply(float width, float height, float depth)
{
	if (entity == nullptr)
		return;

	try {
		auto oldModel = entity;
		entity = TDMELevelEditor::getInstance()->getEntityLibrary()->addTrigger(LevelEditorEntityLibrary::ID_ALLOCATE, oldModel->getName(), oldModel->getDescription(), width, height, depth);
		for (auto i = 0; i < oldModel->getPropertyCount(); i++) {
			auto property = oldModel->getPropertyByIndex(i);
			entity->addProperty(property->getName(), property->getValue());
		}
		TDMELevelEditor::getInstance()->getLevel()->replaceEntity(oldModel->getId(), entity->getId());
		TDMELevelEditor::getInstance()->getEntityLibrary()->removeEntity(oldModel->getId());
		TDMELevelEditor::getInstance()->getLevelEditorEntityLibraryScreenController()->setEntityLibrary();
		initModelRequested = true;
		updateGUIElements();
	} catch (Exception& exception) {
		popUps->getInfoDialogScreenController()->show(
			L"Error",
			L"An error occurred: " + StringConverter::toWideString(string(exception.what()))
		);
	}
}

void TriggerView::initialize()
{
	try {
		triggerScreenController = new TriggerScreenController(this);
		triggerScreenController->initialize();
		engine->getGUI()->addScreen(triggerScreenController->getScreenNode()->getId(), triggerScreenController->getScreenNode());
		triggerScreenController->getScreenNode()->setInputEventHandler(this);
	} catch (Exception& exception) {
		Console::print(string("TriggerView::initialize(): An error occurred: "));
		Console::println(exception.what());
	}
	updateGUIElements();
}

void TriggerView::activate()
{
	engine->reset();
	engine->setPartition(new PartitionNone());
	engine->getGUI()->resetRenderScreens();
	engine->getGUI()->addRenderScreen(triggerScreenController->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(TDMELevelEditor::getInstance()->getLevelEditorEntityLibraryScreenController()->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(popUps->getFileDialogScreenController()->getScreenNode()->getId());
	engine->getGUI()->addRenderScreen(popUps->getInfoDialogScreenController()->getScreenNode()->getId());
}

void TriggerView::deactivate()
{
}

void TriggerView::dispose()
{
	Engine::getInstance()->reset();
}
