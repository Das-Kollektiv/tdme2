#include <tdme/tools/shared/controller/ModelViewerScreenController.h>

#include <string>
#include <vector>


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
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/shared/views/SharedModelViewerView.h>
#include <tdme/tools/viewer/TDMEViewer.h>
#include <tdme/utils/Float.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/StringUtils.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/_Exception.h>

using std::vector;
using std::wstring;

using tdme::tools::shared::controller::ModelViewerScreenController;


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
using tdme::utils::StringConverter;
using tdme::utils::StringUtils;
using tdme::utils::_Console;
using tdme::utils::_Exception;

MutableString* ModelViewerScreenController::TEXT_EMPTY = new MutableString(L"");

ModelViewerScreenController::ModelViewerScreenController(SharedModelViewerView* view) 
{
	this->modelPath = new FileDialogPath(L".");
	this->view = view;
	auto const finalView = view;
	this->entityBaseSubScreenController = new EntityBaseSubScreenController(view->getPopUpsViews(), new ModelViewerScreenController_ModelViewerScreenController_1(this, finalView));
	this->entityDisplaySubScreenController = new EntityDisplaySubScreenController();
	this->entityBoundingVolumeSubScreenController = new EntityBoundingVolumeSubScreenController(view->getPopUpsViews(), modelPath);
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
		screenNode = GUIParser::parse(L"resources/tools/viewer/gui", L"screen_modelviewer.xml");
		screenNode->addActionListener(this);
		screenNode->addChangeListener(this);
		screenCaption = dynamic_cast< GUITextNode* >(screenNode->getNodeById(L"screen_caption"));
		modelReload = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"button_model_reload"));
		modelSave = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"button_model_save"));
		pivotX = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"pivot_x"));
		pivotY = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"pivot_y"));
		pivotZ = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"pivot_z"));
		pivotApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"button_pivot_apply"));
		statsOpaqueFaces = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"stats_opaque_faces"));
		statsTransparentFaces = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"stats_transparent_faces"));
		statsMaterialCount = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"stats_material_count"));
		statsOpaqueFaces->getController()->setDisabled(true);
		statsTransparentFaces->getController()->setDisabled(true);
		statsMaterialCount->getController()->setDisabled(true);
	} catch (_Exception& exception) {
		_Console::print(string("ModelViewerScreenController::initialize(): An error occurred: "));
		_Console::println(string(exception.what()));
	}
	entityBaseSubScreenController->initialize(screenNode);
	entityDisplaySubScreenController->initialize(screenNode);
	entityBoundingVolumeSubScreenController->initialize(screenNode);
	value = new MutableString();
}

void ModelViewerScreenController::dispose()
{
}

void ModelViewerScreenController::setScreenCaption(const wstring& text)
{
	screenCaption->getText()->set(text);
	screenNode->layout(screenCaption);
}

void ModelViewerScreenController::setEntityData(const wstring& name, const wstring& description)
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

void ModelViewerScreenController::setEntityProperties(const wstring& presetId, LevelEditorEntity* entity, const wstring& selectedName)
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
	pivotX->getController()->getValue()->set(Tools::formatFloat(pivot.getX()));
	pivotY->getController()->setDisabled(false);
	pivotY->getController()->getValue()->set(Tools::formatFloat(pivot.getY()));
	pivotZ->getController()->setDisabled(false);
	pivotZ->getController()->getValue()->set(Tools::formatFloat(pivot.getZ()));
	pivotApply->getController()->setDisabled(false);
}

void ModelViewerScreenController::unsetPivot()
{
	pivotX->getController()->setDisabled(true);
	pivotX->getController()->getValue()->set(TEXT_EMPTY);
	pivotY->getController()->setDisabled(true);
	pivotY->getController()->getValue()->set(TEXT_EMPTY);
	pivotZ->getController()->setDisabled(true);
	pivotZ->getController()->getValue()->set(TEXT_EMPTY);
	pivotApply->getController()->setDisabled(true);
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
	auto fileName = view->getEntity() != nullptr?view->getEntity()->getEntityFileName():L"";
	if (fileName.length() == 0) {
		fileName = view->getFileName();
	}
	fileName = Tools::getFileName(fileName);
	vector<wstring> extensions = {
		L"tmm",
		L"dae",
		L"tm"
	};
	view->getPopUpsViews()->getFileDialogScreenController()->show(
		modelPath->getPath(),
		L"Load from: ",
		&extensions,
		view->getFileName(),
		new ModelViewerScreenController_onModelLoad_2(this)
	);
}

void ModelViewerScreenController::onModelSave()
{
	auto fileName = view->getEntity() != nullptr?view->getEntity()->getEntityFileName():L"";
	if (fileName.length() == 0) {
		fileName = view->getFileName();
		if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), L".tmm") == false) {
			fileName = fileName + L".tmm";
		}
	}
	vector<wstring> extensions = {
		L"tmm"
	};
	fileName = Tools::getFileName(fileName);
	view->getPopUpsViews()->getFileDialogScreenController()->show(
		modelPath->getPath(),
		L"Save from: ",
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
		auto x = Float::parseFloat(pivotX->getController()->getValue()->toWString());
		auto y = Float::parseFloat(pivotY->getController()->getValue()->toWString());
		auto z = Float::parseFloat(pivotZ->getController()->getValue()->toWString());
		view->pivotApply(x, y, z);
	} catch (_Exception& exception) {
		showErrorPopUp(L"Warning", StringConverter::toWideString(string(exception.what())));
	}
}

void ModelViewerScreenController::saveFile(const wstring& pathName, const wstring& fileName) /* throws(Exception) */
{
	view->saveFile(pathName, fileName);
}

void ModelViewerScreenController::loadFile(const wstring& pathName, const wstring& fileName) /* throws(Exception) */
{
	view->loadFile(pathName, fileName);
}

void ModelViewerScreenController::showErrorPopUp(const wstring& caption, const wstring& message)
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
				if (node->getId().compare(L"button_model_load") == 0) {
					onModelLoad();
				} else if (node->getId().compare(L"button_model_reload") == 0) {
					onModelReload();
				} else if (node->getId().compare(L"button_model_save") == 0) {
					onModelSave();
				} else if (node->getId().compare(L"button_pivot_apply") == 0) {
					onPivotApply();
				} else {
					_Console::println(
						wstring(
							L"ModelViewerScreenController::onActionPerformed()::unknown, type='" +
							type->getName() +
							L"', id = '" +
							node->getId() +
							L"'" +
							L", name = '" +
							node->getName() +
							L"'"
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
