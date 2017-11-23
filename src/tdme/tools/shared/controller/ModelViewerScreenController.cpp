#include <tdme/tools/shared/controller/ModelViewerScreenController.h>

#include <string>
#include <vector>

#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/gui/events/GUIActionListener_Type.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/shared/controller/EntityBaseSubScreenController.h>
#include <tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController.h>
#include <tdme/tools/shared/controller/EntityDisplaySubScreenController.h>
#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/tools/shared/controller/ModelViewerScreenController_ModelViewerScreenController_1.h>
#include <tdme/tools/shared/controller/ModelViewerScreenController_onModelLoad_2.h>
#include <tdme/tools/shared/controller/ModelViewerScreenController_onModelSave_3.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityModel.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/shared/views/SharedModelViewerView.h>
#include <tdme/tools/viewer/TDMEViewer.h>
#include <tdme/utils/Float.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/StringUtils.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>

using std::vector;
using std::string;

using tdme::tools::shared::controller::ModelViewerScreenController;

using tdme::engine::fileio::models::ModelReader;
using tdme::gui::GUIParser;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::math::Vector3;
using tdme::tools::shared::controller::EntityBaseSubScreenController;
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController;
using tdme::tools::shared::controller::EntityDisplaySubScreenController;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::controller::ModelViewerScreenController_ModelViewerScreenController_1;
using tdme::tools::shared::controller::ModelViewerScreenController_onModelLoad_2;
using tdme::tools::shared::controller::ModelViewerScreenController_onModelSave_3;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::tools::Tools;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::SharedModelViewerView;
using tdme::tools::viewer::TDMEViewer;
using tdme::utils::Float;
using tdme::utils::MutableString;
using tdme::utils::StringUtils;
using tdme::utils::Console;
using tdme::utils::Exception;

MutableString* ModelViewerScreenController::TEXT_EMPTY = new MutableString("");

ModelViewerScreenController::ModelViewerScreenController(SharedModelViewerView* view) 
{
	this->modelPath = new FileDialogPath(".");
	this->view = view;
	auto const finalView = view;
	this->entityBaseSubScreenController = new EntityBaseSubScreenController(view->getPopUpsViews(), new ModelViewerScreenController_ModelViewerScreenController_1(this, finalView));
	this->entityDisplaySubScreenController = new EntityDisplaySubScreenController();
	this->entityBoundingVolumeSubScreenController = new EntityBoundingVolumeSubScreenController(view->getPopUpsViews(), modelPath, true);
}

ModelViewerScreenController::~ModelViewerScreenController() {
	delete modelPath;
	delete entityBaseSubScreenController;
	delete entityDisplaySubScreenController;
	delete entityBoundingVolumeSubScreenController;
}

EntityDisplaySubScreenController* ModelViewerScreenController::getEntityDisplaySubScreenController()
{
	return entityDisplaySubScreenController;
}

EntityBoundingVolumeSubScreenController* ModelViewerScreenController::getEntityBoundingVolumeSubScreenController()
{
	return entityBoundingVolumeSubScreenController;
}

GUIScreenNode* ModelViewerScreenController::getScreenNode()
{
	return screenNode;
}

FileDialogPath* ModelViewerScreenController::getModelPath()
{
	return modelPath;
}

void ModelViewerScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse("resources/tools/viewer/gui", "screen_modelviewer.xml");
		screenNode->addActionListener(this);
		screenNode->addChangeListener(this);
		screenCaption = dynamic_cast< GUITextNode* >(screenNode->getNodeById("screen_caption"));
		modelReload = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_model_reload"));
		modelSave = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_model_save"));
		pivotX = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("pivot_x"));
		pivotY = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("pivot_y"));
		pivotZ = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("pivot_z"));
		pivotApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_pivot_apply"));
		statsOpaqueFaces = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("stats_opaque_faces"));
		statsTransparentFaces = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("stats_transparent_faces"));
		statsMaterialCount = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("stats_material_count"));
		statsOpaqueFaces->getController()->setDisabled(true);
		statsTransparentFaces->getController()->setDisabled(true);
		statsMaterialCount->getController()->setDisabled(true);
		renderingMaskedTransparency = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("rendering_masked_transparency"));
		renderingDynamicShadowing = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("rendering_dynamic_shadowing"));
		renderingApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_rendering_apply"));
	} catch (Exception& exception) {
		Console::print(string("ModelViewerScreenController::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	entityBaseSubScreenController->initialize(screenNode);
	entityDisplaySubScreenController->initialize(screenNode);
	entityBoundingVolumeSubScreenController->initialize(screenNode);
	value = new MutableString();
}

void ModelViewerScreenController::dispose()
{
}

void ModelViewerScreenController::setScreenCaption(const string& text)
{
	screenCaption->getText()->set(text);
	screenNode->layout(screenCaption);
}

void ModelViewerScreenController::setEntityData(const string& name, const string& description)
{
	entityBaseSubScreenController->setEntityData(name, description);
	modelReload->getController()->setDisabled(false);
	modelSave->getController()->setDisabled(false);
}

void ModelViewerScreenController::unsetEntityData()
{
	entityBaseSubScreenController->unsetEntityData();
	modelReload->getController()->setDisabled(true);
	modelSave->getController()->setDisabled(true);
}

void ModelViewerScreenController::setEntityProperties(const string& presetId, LevelEditorEntity* entity, const string& selectedName)
{
	entityBaseSubScreenController->setEntityProperties(view->getEntity(), presetId, selectedName);
}

void ModelViewerScreenController::unsetEntityProperties()
{
	entityBaseSubScreenController->unsetEntityProperties();
}

void ModelViewerScreenController::setPivot(const Vector3& pivot)
{
	pivotX->getController()->setDisabled(false);
	pivotX->getController()->setValue(value->set(Tools::formatFloat(pivot.getX())));
	pivotY->getController()->setDisabled(false);
	pivotY->getController()->setValue(value->set(Tools::formatFloat(pivot.getY())));
	pivotZ->getController()->setDisabled(false);
	pivotZ->getController()->setValue(value->set(Tools::formatFloat(pivot.getZ())));
	pivotApply->getController()->setDisabled(false);
}

void ModelViewerScreenController::unsetPivot()
{
	pivotX->getController()->setDisabled(true);
	pivotX->getController()->setValue(value->set(TEXT_EMPTY));
	pivotY->getController()->setDisabled(true);
	pivotY->getController()->setValue(value->set(TEXT_EMPTY));
	pivotZ->getController()->setDisabled(true);
	pivotZ->getController()->setValue(value->set(TEXT_EMPTY));
	pivotApply->getController()->setDisabled(true);
}

void ModelViewerScreenController::setRendering(LevelEditorEntity* entity)
{
	renderingMaskedTransparency->getController()->setDisabled(false);
	renderingMaskedTransparency->getController()->setValue(value->set(entity->getModelSettings()->isMaskedTransparency() == true?"1":""));
	renderingDynamicShadowing->getController()->setDisabled(false);
	renderingDynamicShadowing->getController()->setValue(value->set(entity->isDynamicShadowing() == true?"1":""));
	renderingApply->getController()->setDisabled(false);
}

void ModelViewerScreenController::unsetRendering()
{
	renderingMaskedTransparency->getController()->setDisabled(true);
	renderingMaskedTransparency->getController()->setValue(value->set(TEXT_EMPTY));
	renderingDynamicShadowing->getController()->setDisabled(true);
	renderingDynamicShadowing->getController()->setValue(value->set("1"));
	renderingApply->getController()->setDisabled(true);
}

void ModelViewerScreenController::setStatistics(int32_t statsOpaqueFaces, int32_t statsTransparentFaces, int32_t statsMaterialCount)
{
	this->statsOpaqueFaces->getController()->setValue(value->set(statsOpaqueFaces));
	this->statsTransparentFaces->getController()->setValue(value->set(statsTransparentFaces));
	this->statsMaterialCount->getController()->setValue(value->set(statsMaterialCount));
}

void ModelViewerScreenController::onQuit()
{
	TDMEViewer::getInstance()->quit();
}

void ModelViewerScreenController::onModelLoad()
{
	auto fileName = view->getEntity() != nullptr?view->getEntity()->getEntityFileName():"";
	if (fileName.length() == 0) {
		fileName = view->getFileName();
	}
	fileName = Tools::getFileName(fileName);
	vector<string> extensions = ModelReader::getModelExtensions();
	extensions.push_back("tmm");
	view->getPopUpsViews()->getFileDialogScreenController()->show(
		modelPath->getPath(),
		"Load from: ",
		&extensions,
		view->getFileName(),
		new ModelViewerScreenController_onModelLoad_2(this)
	);
}

void ModelViewerScreenController::onModelSave()
{
	auto fileName = view->getEntity() != nullptr?view->getEntity()->getEntityFileName():"";
	if (fileName.length() == 0) {
		fileName = view->getFileName();
		if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".tmm") == false) {
			fileName = fileName + ".tmm";
		}
	}
	vector<string> extensions = {
		"tmm"
	};
	fileName = Tools::getFileName(fileName);
	view->getPopUpsViews()->getFileDialogScreenController()->show(
		modelPath->getPath(),
		"Save from: ",
		&extensions,
		fileName,
		new ModelViewerScreenController_onModelSave_3(this)
	);
}

void ModelViewerScreenController::onModelReload()
{
	view->reloadFile();
}

void ModelViewerScreenController::onPivotApply()
{
	try {
		auto x = Float::parseFloat(pivotX->getController()->getValue()->getString());
		auto y = Float::parseFloat(pivotY->getController()->getValue()->getString());
		auto z = Float::parseFloat(pivotZ->getController()->getValue()->getString());
		view->pivotApply(x, y, z);
	} catch (Exception& exception) {
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void ModelViewerScreenController::onRenderingApply()
{
	if (view->getEntity() == nullptr) return;
	view->getEntity()->getModelSettings()->setMaskedTransparency(renderingMaskedTransparency->getController()->getValue()->equals("1"));
	view->getEntity()->setDynamicShadowing(renderingMaskedTransparency->getController()->getValue()->equals("1"));
}

void ModelViewerScreenController::saveFile(const string& pathName, const string& fileName) /* throws(Exception) */
{
	view->saveFile(pathName, fileName);
}

void ModelViewerScreenController::loadFile(const string& pathName, const string& fileName) /* throws(Exception) */
{
	view->loadFile(pathName, fileName);
}

void ModelViewerScreenController::showErrorPopUp(const string& caption, const string& message)
{
	view->getPopUpsViews()->getInfoDialogScreenController()->show(caption, message);
}

void ModelViewerScreenController::onValueChanged(GUIElementNode* node)
{
	entityBaseSubScreenController->onValueChanged(node, view->getEntity());
}

void ModelViewerScreenController::onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node)
{
	entityBaseSubScreenController->onActionPerformed(type, node, view->getEntity());
	entityDisplaySubScreenController->onActionPerformed(type, node);
	entityBoundingVolumeSubScreenController->onActionPerformed(type, node, view->getEntity());
	{
		auto v = type;
		if ((v == GUIActionListener_Type::PERFORMED)) {
			{
				if (node->getId().compare("button_model_load") == 0) {
					onModelLoad();
				} else
				if (node->getId().compare("button_model_reload") == 0) {
					onModelReload();
				} else
				if (node->getId().compare("button_model_save") == 0) {
					onModelSave();
				} else
				if (node->getId().compare("button_pivot_apply") == 0) {
					onPivotApply();
				} else
				if (node->getId().compare("button_rendering_apply") == 0) {
					onRenderingApply();
				} else {
					Console::println(
						string(
							"ModelViewerScreenController::onActionPerformed()::unknown, type='" +
							type->getName() +
							"', id = '" +
							node->getId() +
							"'" +
							", name = '" +
							node->getName() +
							"'"
						)
					);
				}
				goto end_switch0;;
			}
		}
		if ((v == GUIActionListener_Type::PERFORMED) || (v == GUIActionListener_Type::PERFORMING)) {
			{
				goto end_switch0;;
			}
		}
		end_switch0:;
	}

}
