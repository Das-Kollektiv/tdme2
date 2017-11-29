#include <tdme/tools/shared/controller/ModelEditorScreenController.h>

#include <string>
#include <vector>

#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/textures/TextureLoader.h>
#include <tdme/engine/model/AnimationSetup.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Group.h>
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
#include <tdme/tools/shared/controller/ModelEditorScreenController_ModelEditorScreenController_1.h>
#include <tdme/tools/shared/controller/ModelEditorScreenController_onMaterialLoadTexture.h>
#include <tdme/tools/shared/controller/ModelEditorScreenController_onModelLoad_2.h>
#include <tdme/tools/shared/controller/ModelEditorScreenController_onModelSave_3.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityModel.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/shared/views/SharedModelEditorView.h>
#include <tdme/tools/modeleditor/TDMEModelEditor.h>
#include <tdme/utils/Float.h>
#include <tdme/utils/Integer.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/StringUtils.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>
#include <tdme/utils/ExceptionBase.h>

using std::vector;
using std::string;

using tdme::tools::shared::controller::ModelEditorScreenController;

using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::textures::TextureLoader;
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
using tdme::tools::shared::controller::ModelEditorScreenController_ModelEditorScreenController_1;
using tdme::tools::shared::controller::ModelEditorScreenController_onMaterialLoadTexture;
using tdme::tools::shared::controller::ModelEditorScreenController_onModelLoad_2;
using tdme::tools::shared::controller::ModelEditorScreenController_onModelSave_3;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::tools::Tools;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::SharedModelEditorView;
using tdme::tools::viewer::TDMEModelEditor;
using tdme::utils::Float;
using tdme::utils::Integer;
using tdme::utils::MutableString;
using tdme::utils::StringUtils;
using tdme::utils::Console;
using tdme::utils::Exception;
using tdme::utils::ExceptionBase;

MutableString* ModelEditorScreenController::TEXT_EMPTY = new MutableString("");

ModelEditorScreenController::ModelEditorScreenController(SharedModelEditorView* view) 
{
	this->modelPath = new FileDialogPath(".");
	this->view = view;
	auto const finalView = view;
	this->entityBaseSubScreenController = new EntityBaseSubScreenController(view->getPopUpsViews(), new ModelEditorScreenController_ModelEditorScreenController_1(this, finalView));
	this->entityDisplaySubScreenController = new EntityDisplaySubScreenController();
	this->entityBoundingVolumeSubScreenController = new EntityBoundingVolumeSubScreenController(view->getPopUpsViews(), modelPath, true);
}

ModelEditorScreenController::~ModelEditorScreenController() {
	delete modelPath;
	delete entityBaseSubScreenController;
	delete entityDisplaySubScreenController;
	delete entityBoundingVolumeSubScreenController;
}

SharedModelEditorView* ModelEditorScreenController::getView() {
	return view;
}

EntityDisplaySubScreenController* ModelEditorScreenController::getEntityDisplaySubScreenController()
{
	return entityDisplaySubScreenController;
}

EntityBoundingVolumeSubScreenController* ModelEditorScreenController::getEntityBoundingVolumeSubScreenController()
{
	return entityBoundingVolumeSubScreenController;
}

GUIScreenNode* ModelEditorScreenController::getScreenNode()
{
	return screenNode;
}

FileDialogPath* ModelEditorScreenController::getModelPath()
{
	return modelPath;
}

void ModelEditorScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse("resources/tools/modeleditor/gui", "screen_modeleditor.xml");
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
		renderingDynamicShadowing = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("rendering_dynamic_shadowing"));
		renderingApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_rendering_apply"));
		materialsDropdown = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_dropdown"));
		materialsDropdownApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_materials_dropdown_apply"));
		materialsMaterialName = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_name"));
		materialsMaterialAmbient = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_ambient"));
		materialsMaterialDiffuse = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_diffuse"));
		materialsMaterialSpecular= dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_specular"));
		materialsMaterialEmission = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_emission"));
		materialsMaterialShininess = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_shininess"));
		materialsMaterialDiffuseTexture = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_diffuse_texture"));
		materialsMaterialDiffuseTransparencyTexture = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_diffuse_transparency_texture"));
		materialsMaterialNormalTexture = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_normal_texture"));
		materialsMaterialSpecularTexture = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_specular_texture"));
		materialsMaterialDiffuseTextureLoad = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_materials_material_diffuse_texture_load"));;
		materialsMaterialDiffuseTransparencyTextureLoad = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_materials_material_diffuse_transparency_texture_load"));;
		materialsMaterialNormalTextureLoad = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_materials_material_normal_texture_load"));;
		materialsMaterialSpecularTextureLoad = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_materials_material_specular_texture_load"));;
		materialsMaterialDiffuseTextureClear = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_materials_material_diffuse_texture_clear"));;
		materialsMaterialDiffuseTransparencyTextureClear = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_materials_material_diffuse_transparency_texture_clear"));;
		materialsMaterialNormalTextureClear = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_materials_material_normal_texture_clear"));;
		materialsMaterialSpecularTextureClear = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_materials_material_specular_texture_clear"));;
		materialsMaterialUseMaskedTransparency = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_use_masked_transparency"));;
		materialsMaterialApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_materials_material_apply"));
		animationsDropDown = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("animations_dropdown"));
		animationsDropDownApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("animations_dropdown_apply"));
		animationsDropDownDelete = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("animations_dropdown_delete"));
		animationsAnimationStartFrame = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("animations_animation_startframe"));
		animationsAnimationEndFrame = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("animations_animation_endframe"));
		animationsAnimationOverlayFromGroupIdDropDown = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("animations_animation_overlayfromgroupidanimations_dropdown"));
		animationsAnimationLoop = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("animations_animation_loop"));
		animationsAnimationName = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("animations_animation_name"));
		animationsAnimationApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_animations_animation_apply"));
	} catch (Exception& exception) {
		Console::print(string("ModelEditorScreenController::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	entityBaseSubScreenController->initialize(screenNode);
	entityDisplaySubScreenController->initialize(screenNode);
	entityBoundingVolumeSubScreenController->initialize(screenNode);
	value = new MutableString();
}

void ModelEditorScreenController::dispose()
{
}

void ModelEditorScreenController::setScreenCaption(const string& text)
{
	screenCaption->getText()->set(text);
	screenNode->layout(screenCaption);
}

void ModelEditorScreenController::setEntityData(const string& name, const string& description)
{
	entityBaseSubScreenController->setEntityData(name, description);
	modelReload->getController()->setDisabled(false);
	modelSave->getController()->setDisabled(false);
}

void ModelEditorScreenController::unsetEntityData()
{
	entityBaseSubScreenController->unsetEntityData();
	modelReload->getController()->setDisabled(true);
	modelSave->getController()->setDisabled(true);
}

void ModelEditorScreenController::setEntityProperties(const string& presetId, LevelEditorEntity* entity, const string& selectedName)
{
	entityBaseSubScreenController->setEntityProperties(view->getEntity(), presetId, selectedName);
}

void ModelEditorScreenController::unsetEntityProperties()
{
	entityBaseSubScreenController->unsetEntityProperties();
}

void ModelEditorScreenController::setPivot(const Vector3& pivot)
{
	pivotX->getController()->setDisabled(false);
	pivotX->getController()->setValue(value->set(Tools::formatFloat(pivot.getX())));
	pivotY->getController()->setDisabled(false);
	pivotY->getController()->setValue(value->set(Tools::formatFloat(pivot.getY())));
	pivotZ->getController()->setDisabled(false);
	pivotZ->getController()->setValue(value->set(Tools::formatFloat(pivot.getZ())));
	pivotApply->getController()->setDisabled(false);
}

void ModelEditorScreenController::unsetPivot()
{
	pivotX->getController()->setDisabled(true);
	pivotX->getController()->setValue(value->set(TEXT_EMPTY));
	pivotY->getController()->setDisabled(true);
	pivotY->getController()->setValue(value->set(TEXT_EMPTY));
	pivotZ->getController()->setDisabled(true);
	pivotZ->getController()->setValue(value->set(TEXT_EMPTY));
	pivotApply->getController()->setDisabled(true);
}

void ModelEditorScreenController::setRendering(LevelEditorEntity* entity)
{
	renderingDynamicShadowing->getController()->setDisabled(false);
	renderingDynamicShadowing->getController()->setValue(value->set(entity->isDynamicShadowing() == true?"1":""));
	renderingApply->getController()->setDisabled(false);
}

void ModelEditorScreenController::unsetRendering()
{
	renderingDynamicShadowing->getController()->setDisabled(true);
	renderingDynamicShadowing->getController()->setValue(value->set("1"));
	renderingApply->getController()->setDisabled(true);
}

void ModelEditorScreenController::setMaterials(LevelEditorEntity* entity) {
	auto model = entity->getModel();

	{
		auto materialsDropDownInnerNode = dynamic_cast< GUIParentNode* >((materialsDropdown->getScreenNode()->getNodeById(materialsDropdown->getId() + "_inner")));
		auto idx = 0;
		string materialsDropDownInnerNodeSubNodesXML = "";
		materialsDropDownInnerNodeSubNodesXML =
				materialsDropDownInnerNodeSubNodesXML +
			"<scrollarea-vertical id=\"" +
			materialsDropdown->getId() +
			"_inner_scrollarea\" width=\"100%\" height=\"100\">\n";
		// materialsDropDownInnerNodeSubNodesXML = materialsDropDownInnerNodeSubNodesXML + "<dropdown-option text=\"<New animation>\" value=\"<New animation>\" />";
		for (auto it: *model->getMaterials()) {
			auto materialId = it.second->getId();
			materialsDropDownInnerNodeSubNodesXML =
					materialsDropDownInnerNodeSubNodesXML + "<dropdown-option text=\"" +
				GUIParser::escapeQuotes(materialId) +
				"\" value=\"" +
				GUIParser::escapeQuotes(materialId) +
				"\" " +
				(idx == 0 ? "selected=\"true\" " : "") +
				" />\n";
			idx++;
		}
		materialsDropDownInnerNodeSubNodesXML = materialsDropDownInnerNodeSubNodesXML + "</scrollarea-vertical>";
		try {
			materialsDropDownInnerNode->replaceSubNodes(materialsDropDownInnerNodeSubNodesXML, true);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorScreenController::setMaterials(): An error occurred: "));
			Console::println(string(exception.what()));
		}
	}

	//
	materialsDropdown->getController()->setDisabled(false);
	materialsDropdownApply->getController()->setDisabled(false);
	materialsMaterialAmbient->getController()->setDisabled(false);
	materialsMaterialDiffuse->getController()->setDisabled(false);
	materialsMaterialSpecular->getController()->setDisabled(false);
	materialsMaterialEmission->getController()->setDisabled(false);
	materialsMaterialShininess->getController()->setDisabled(false);
	materialsMaterialDiffuseTexture->getController()->setDisabled(false);
	materialsMaterialDiffuseTextureLoad->getController()->setDisabled(false);
	materialsMaterialDiffuseTextureClear->getController()->setDisabled(false);
	materialsMaterialDiffuseTransparencyTexture->getController()->setDisabled(false);
	materialsMaterialDiffuseTransparencyTextureLoad->getController()->setDisabled(false);
	materialsMaterialDiffuseTransparencyTextureClear->getController()->setDisabled(false);
	materialsMaterialNormalTexture->getController()->setDisabled(false);
	materialsMaterialNormalTextureLoad->getController()->setDisabled(false);
	materialsMaterialNormalTextureClear->getController()->setDisabled(false);
	materialsMaterialSpecularTexture->getController()->setDisabled(false);
	materialsMaterialSpecularTextureLoad->getController()->setDisabled(false);
	materialsMaterialSpecularTextureClear->getController()->setDisabled(false);
	materialsMaterialUseMaskedTransparency->getController()->setDisabled(false);
	materialsMaterialApply->getController()->setDisabled(false);
	onMaterialDropDownApply();
}

void ModelEditorScreenController::unsetMaterials() {
	{
		auto materialsDropDownInnerNode = dynamic_cast< GUIParentNode* >((materialsDropdown->getScreenNode()->getNodeById(materialsDropdown->getId() + "_inner")));
		auto idx = 0;
		string materialsDropDownInnerNodeSubNodesXML = "";
		materialsDropDownInnerNodeSubNodesXML =
				materialsDropDownInnerNodeSubNodesXML +
			"<scrollarea-vertical id=\"" +
			materialsDropdown->getId() +
			"_inner_scrollarea\" width=\"100%\" height=\"100\">\n";
		materialsDropDownInnerNodeSubNodesXML = materialsDropDownInnerNodeSubNodesXML + "<dropdown-option text=\"None\" value=\"\" />";
		materialsDropDownInnerNodeSubNodesXML = materialsDropDownInnerNodeSubNodesXML + "</scrollarea-vertical>";
		try {
			materialsDropDownInnerNode->replaceSubNodes(materialsDropDownInnerNodeSubNodesXML, true);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorScreenController::setMaterials(): An error occurred: "));
			Console::println(string(exception.what()));
		}
	}

	materialsDropdown->getController()->setValue(value->set(""));
	materialsDropdown->getController()->setDisabled(true);
	materialsDropdownApply->getController()->setDisabled(true);
	materialsMaterialName->getController()->setValue(value->set(""));
	materialsMaterialAmbient->getController()->setDisabled(true);
	materialsMaterialAmbient->getController()->setValue(value->set(""));
	materialsMaterialDiffuse->getController()->setDisabled(true);
	materialsMaterialDiffuse->getController()->setValue(value->set(""));
	materialsMaterialSpecular->getController()->setDisabled(true);
	materialsMaterialSpecular->getController()->setValue(value->set(""));
	materialsMaterialEmission->getController()->setDisabled(true);
	materialsMaterialEmission->getController()->setValue(value->set(""));
	materialsMaterialShininess->getController()->setDisabled(true);
	materialsMaterialShininess->getController()->setValue(value->set(""));
	materialsMaterialApply->getController()->setDisabled(true);
	materialsMaterialDiffuseTexture->getController()->setValue(value->set(""));
	materialsMaterialDiffuseTextureLoad->getController()->setDisabled(true);
	materialsMaterialDiffuseTextureClear->getController()->setDisabled(true);
	materialsMaterialDiffuseTransparencyTexture->getController()->setValue(value->set(""));
	materialsMaterialDiffuseTransparencyTextureLoad->getController()->setDisabled(true);
	materialsMaterialDiffuseTransparencyTextureClear->getController()->setDisabled(true);
	materialsMaterialNormalTexture->getController()->setValue(value->set(""));
	materialsMaterialNormalTextureLoad->getController()->setDisabled(true);
	materialsMaterialNormalTextureClear->getController()->setDisabled(true);
	materialsMaterialSpecularTexture->getController()->setValue(value->set(""));
	materialsMaterialSpecularTextureLoad->getController()->setDisabled(true);
	materialsMaterialSpecularTextureClear->getController()->setDisabled(true);
	materialsMaterialShininess->getController()->setValue(value->set(""));
	materialsMaterialUseMaskedTransparency->getController()->setValue(value->set(""));
	materialsMaterialUseMaskedTransparency->getController()->setDisabled(true);

}

void ModelEditorScreenController::onMaterialDropDownApply() {
	auto entity = view->getEntity();
	auto material = (*entity->getModel()->getMaterials())[materialsDropdown->getController()->getValue()->getString()];
	materialsMaterialName->getController()->setValue(value->set(material->getId()));
	materialsMaterialAmbient->getController()->setValue(value->set(Tools::formatColor4(material->getAmbientColor())));
	materialsMaterialDiffuse->getController()->setValue(value->set(Tools::formatColor4(material->getDiffuseColor())));
	materialsMaterialSpecular->getController()->setValue(value->set(Tools::formatColor4(material->getSpecularColor())));
	materialsMaterialEmission->getController()->setValue(value->set(Tools::formatColor4(material->getEmissionColor())));
	materialsMaterialShininess->getController()->setValue(value->set(Tools::formatFloat(material->getShininess())));
	materialsMaterialDiffuseTexture->getController()->setValue(
		value->set(material->getDiffuseTexturePathName())->append(material->getDiffuseTexturePathName() == ""?"":"/")->append(material->getDiffuseTextureFileName())
	);
	materialsMaterialDiffuseTransparencyTexture->getController()->setValue(
		value->set(material->getDiffuseTransparencyTexturePathName())->append(material->getDiffuseTransparencyTexturePathName() == ""?"":"/")->append(material->getDiffuseTransparencyTextureFileName())
	);
	materialsMaterialNormalTexture->getController()->setValue(
		value->set(material->getNormalTexturePathName())->append(material->getNormalTexturePathName() == ""?"":"/")->append(material->getNormalTextureFileName())
	);
	materialsMaterialSpecularTexture->getController()->setValue(
		value->set(material->getSpecularTexturePathName())->append(material->getSpecularTexturePathName() == ""?"":"/")->append(material->getSpecularTextureFileName())
	);
	materialsMaterialUseMaskedTransparency->getController()->setValue(value->set(material->hasDiffuseTextureMaskedTransparency() == true?"1":""));
}

void ModelEditorScreenController::onMaterialApply() {
	auto entity = view->getEntity();
	auto material = (*entity->getModel()->getMaterials())[materialsDropdown->getController()->getValue()->getString()];
	try {
		view->setEntity(entity);
		material->getAmbientColor().set(Tools::convertToColor4(materialsMaterialAmbient->getController()->getValue()->getString()));
		material->getDiffuseColor().set(Tools::convertToColor4(materialsMaterialDiffuse->getController()->getValue()->getString()));
		material->getSpecularColor().set(Tools::convertToColor4(materialsMaterialSpecular->getController()->getValue()->getString()));
		material->getEmissionColor().set(Tools::convertToColor4(materialsMaterialEmission->getController()->getValue()->getString()));
		material->setShininess(Tools::convertToFloat(materialsMaterialShininess->getController()->getValue()->getString()));
		material->setDiffuseTexture(
			Tools::getPath(materialsMaterialDiffuseTexture->getController()->getValue()->getString()),
			Tools::getFileName(materialsMaterialDiffuseTexture->getController()->getValue()->getString()),
			Tools::getPath(materialsMaterialDiffuseTransparencyTexture->getController()->getValue()->getString()),
			Tools::getFileName(materialsMaterialDiffuseTransparencyTexture->getController()->getValue()->getString())
		);
		material->setNormalTexture(
			Tools::getPath(materialsMaterialNormalTexture->getController()->getValue()->getString()),
			Tools::getFileName(materialsMaterialNormalTexture->getController()->getValue()->getString())
		);
		material->setSpecularTexture(
			Tools::getPath(materialsMaterialSpecularTexture->getController()->getValue()->getString()),
			Tools::getFileName(materialsMaterialSpecularTexture->getController()->getValue()->getString())
		);
		material->setDiffuseTextureMaskedTransparency(materialsMaterialUseMaskedTransparency->getController()->getValue()->getString() == "1"?true:false);
	} catch (Exception& exception) {
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void ModelEditorScreenController::onMaterialLoadDiffuseTexture() {
	auto entity = view->getEntity();
	auto extensions = TextureLoader::getTextureExtensions();
	auto material = (*entity->getModel()->getMaterials())[materialsDropdown->getController()->getValue()->getString()];
	view->getPopUpsViews()->getFileDialogScreenController()->show(
		material->getDiffuseTextureFileName() != ""?material->getDiffuseTexturePathName():modelPath->getPath(),
		"Load from: ",
		&extensions,
		material->getDiffuseTextureFileName(),
		new ModelEditorScreenController_onMaterialLoadTexture(this, materialsMaterialDiffuseTexture)
	);
}

void ModelEditorScreenController::onMaterialLoadDiffuseTransparencyTexture() {
	auto entity = view->getEntity();
	auto extensions = TextureLoader::getTextureExtensions();
	auto material = (*entity->getModel()->getMaterials())[materialsDropdown->getController()->getValue()->getString()];
	view->getPopUpsViews()->getFileDialogScreenController()->show(
		material->getDiffuseTextureFileName() != ""?material->getDiffuseTexturePathName():modelPath->getPath(),
		"Load from: ",
		&extensions,
		material->getDiffuseTextureFileName(),
		new ModelEditorScreenController_onMaterialLoadTexture(this, materialsMaterialDiffuseTransparencyTexture)
	);
}

void ModelEditorScreenController::onMaterialLoadNormalTexture() {
	auto entity = view->getEntity();
	auto extensions = TextureLoader::getTextureExtensions();
	auto material = (*entity->getModel()->getMaterials())[materialsDropdown->getController()->getValue()->getString()];
	view->getPopUpsViews()->getFileDialogScreenController()->show(
		material->getDiffuseTextureFileName() != ""?material->getDiffuseTexturePathName():modelPath->getPath(),
		"Load from: ",
		&extensions,
		material->getDiffuseTextureFileName(),
		new ModelEditorScreenController_onMaterialLoadTexture(this, materialsMaterialNormalTexture)
	);
}

void ModelEditorScreenController::onMaterialLoadSpecularTexture() {
	auto entity = view->getEntity();
	auto extensions = TextureLoader::getTextureExtensions();
	auto material = (*entity->getModel()->getMaterials())[materialsDropdown->getController()->getValue()->getString()];
	view->getPopUpsViews()->getFileDialogScreenController()->show(
		material->getDiffuseTextureFileName() != ""?material->getDiffuseTexturePathName():modelPath->getPath(),
		"Load from: ",
		&extensions,
		material->getDiffuseTextureFileName(),
		new ModelEditorScreenController_onMaterialLoadTexture(this, materialsMaterialNormalTexture)
	);
}

void ModelEditorScreenController::onMaterialClearTexture(GUIElementNode* guiElementNode) {
	guiElementNode->getController()->setValue(value->set(""));
}

void ModelEditorScreenController::setAnimations(LevelEditorEntity* entity) {

	auto model = entity->getModel();

	{
		auto animationsDropDownInnerNode = dynamic_cast< GUIParentNode* >((animationsDropDown->getScreenNode()->getNodeById(animationsDropDown->getId() + "_inner")));
		auto idx = 0;
		string animationsDropDownInnerNodeSubNodesXML = "";
		animationsDropDownInnerNodeSubNodesXML =
			animationsDropDownInnerNodeSubNodesXML +
			"<scrollarea-vertical id=\"" +
			animationsDropDown->getId() +
			"_inner_scrollarea\" width=\"100%\" height=\"100\">\n";
		animationsDropDownInnerNodeSubNodesXML = animationsDropDownInnerNodeSubNodesXML + "<dropdown-option text=\"<New animation>\" value=\"<New animation>\" />";
		for (auto it: *model->getAnimationSetups()) {
			auto animationSetupId = it.second->getId();
			animationsDropDownInnerNodeSubNodesXML =
				animationsDropDownInnerNodeSubNodesXML + "<dropdown-option text=\"" +
				GUIParser::escapeQuotes(animationSetupId) +
				"\" value=\"" +
				GUIParser::escapeQuotes(animationSetupId) +
				"\" " +
				(idx == 0 ? "selected=\"true\" " : "") +
				" />\n";
			idx++;
		}
		animationsDropDownInnerNodeSubNodesXML = animationsDropDownInnerNodeSubNodesXML + "</scrollarea-vertical>";
		try {
			animationsDropDownInnerNode->replaceSubNodes(animationsDropDownInnerNodeSubNodesXML, true);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorScreenController::setAnimations(): An error occurred: "));
			Console::println(string(exception.what()));
		}
		// TODO: this usually works most of the time out of the box, so custom layouting is not required, but in this case not, need to find out whats going wrong there
		animationsDropDown->getScreenNode()->layout(animationsDropDown);
	}

	{
		auto animationsAnimationOverlayFromGroupIdDropDownInnerNode = dynamic_cast< GUIParentNode* >((animationsAnimationOverlayFromGroupIdDropDown->getScreenNode()->getNodeById(animationsAnimationOverlayFromGroupIdDropDown->getId() + "_inner")));
		auto idx = 0;
		string animationsAnimationOverlayFromGroupIdDropDownInnerNodeSubNodesXML = "";
		animationsAnimationOverlayFromGroupIdDropDownInnerNodeSubNodesXML =
			animationsAnimationOverlayFromGroupIdDropDownInnerNodeSubNodesXML +
			"<scrollarea-vertical id=\"" +
			animationsAnimationOverlayFromGroupIdDropDown->getId() +
			"_inner_scrollarea\" width=\"100%\" height=\"70\">\n";
		animationsAnimationOverlayFromGroupIdDropDownInnerNodeSubNodesXML =
			animationsAnimationOverlayFromGroupIdDropDownInnerNodeSubNodesXML +
			"<dropdown-option text=\"\" value=\"\"" +
			(idx == 0 ? "selected=\"true\" " : "") +
			" />\n";
		for (auto it: *model->getGroups()) {
			auto groupId = it.second->getId();
			animationsAnimationOverlayFromGroupIdDropDownInnerNodeSubNodesXML =
				animationsAnimationOverlayFromGroupIdDropDownInnerNodeSubNodesXML +
				"<dropdown-option text=\"" +
				GUIParser::escapeQuotes(groupId) +
				"\" value=\"" +
				GUIParser::escapeQuotes(groupId) +
				"\" " +
				(idx == 0 ? "selected=\"true\" " : "") +
				" />\n";
			idx++;
		}
		animationsAnimationOverlayFromGroupIdDropDownInnerNodeSubNodesXML = animationsAnimationOverlayFromGroupIdDropDownInnerNodeSubNodesXML + "</scrollarea-vertical>";
		try {
			animationsAnimationOverlayFromGroupIdDropDownInnerNode->replaceSubNodes(animationsAnimationOverlayFromGroupIdDropDownInnerNodeSubNodesXML, true);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorScreenController::setAnimations(): An error occurred: "));
			Console::println(string(exception.what()));
		}
		// TODO: this usually works most of the time out of the box, so custom layouting is not required, but in this case not, need to find out whats going wrong there
		// animationsAnimationOverlayFromGroupIdDropDown->getScreenNode()->layout(animationsAnimationOverlayFromGroupIdDropDown);
	}

	// select default animation
	animationsDropDown->getController()->setValue(value->set(Model::ANIMATIONSETUP_DEFAULT));

	// apply
	onAnimationDropDownApply();
}

void ModelEditorScreenController::onAnimationDropDownValueChanged() {
	auto entity = view->getEntity();
	auto animationSetup = entity->getModel()->getAnimationSetup(animationsDropDown->getController()->getValue()->getString());
	auto defaultAnimation = animationSetup != nullptr && animationSetup->getId() == Model::ANIMATIONSETUP_DEFAULT;
	animationsDropDownDelete->getController()->setDisabled(defaultAnimation || animationSetup == nullptr);
}

void ModelEditorScreenController::onAnimationDropDownApply() {
	auto entity = view->getEntity();
	auto animationSetup = entity->getModel()->getAnimationSetup(animationsDropDown->getController()->getValue()->getString());
	AnimationSetup newAnimationSetup(
		entity->getModel(),
		"New animation",
		entity->getModel()->getAnimationSetup(Model::ANIMATIONSETUP_DEFAULT)->getStartFrame(),
		entity->getModel()->getAnimationSetup(Model::ANIMATIONSETUP_DEFAULT)->getEndFrame(),
		true,
		""
	);
	if (animationSetup == nullptr) animationSetup = &newAnimationSetup;
	auto defaultAnimation = animationSetup->getId() == Model::ANIMATIONSETUP_DEFAULT;
	animationsDropDown->getController()->setDisabled(false);
	animationsDropDownApply->getController()->setDisabled(false);
	animationsDropDownDelete->getController()->setDisabled(defaultAnimation || animationSetup == &newAnimationSetup);
	animationsAnimationStartFrame->getController()->setValue(value->set(animationSetup->getStartFrame()));
	animationsAnimationStartFrame->getController()->setDisabled(defaultAnimation);
	animationsAnimationEndFrame->getController()->setValue(value->set(animationSetup->getEndFrame()));
	animationsAnimationEndFrame->getController()->setDisabled(defaultAnimation);
	animationsAnimationOverlayFromGroupIdDropDown->getController()->setValue(value->set(animationSetup->getOverlayFromGroupId()));
	animationsAnimationOverlayFromGroupIdDropDown->getController()->setDisabled(defaultAnimation);
	animationsAnimationLoop->getController()->setValue(value->set(animationSetup->isLoop() == true?"1":""));
	animationsAnimationLoop->getController()->setDisabled(defaultAnimation);
	animationsAnimationName->getController()->setValue(value->set(animationSetup->getId()));
	animationsAnimationName->getController()->setDisabled(defaultAnimation);
	animationsAnimationApply->getController()->setDisabled(defaultAnimation);
	if (animationSetup != &newAnimationSetup) view->playAnimation(animationSetup->getId());
}

void ModelEditorScreenController::onAnimationDropDownDelete() {
	auto entity = view->getEntity();
	auto animationSetup = entity->getModel()->getAnimationSetup(animationsDropDown->getController()->getValue()->getString());
	auto it = entity->getModel()->getAnimationSetups()->find(animationSetup->getId());
	it = entity->getModel()->getAnimationSetups()->erase(it);
	setAnimations(entity);
	animationsDropDown->getController()->setValue(value->set(it->second->getId()));
	onAnimationDropDownApply();
}

void ModelEditorScreenController::onAnimationApply() {
	auto entity = view->getEntity();
	auto animationSetup = entity->getModel()->getAnimationSetup(animationsDropDown->getController()->getValue()->getString());
	try {
		if (animationSetup == nullptr) {
			if (entity->getModel()->getAnimationSetup(animationsAnimationName->getController()->getValue()->getString()) != nullptr) {
				throw ExceptionBase("Name '" + animationsAnimationName->getController()->getValue()->getString() + "' already in use");
			}
			animationSetup = entity->getModel()->addAnimationSetup(
				animationsAnimationName->getController()->getValue()->getString(),
				0,
				0,
				false
			);
		} else
		if (animationSetup->getId() != animationsAnimationName->getController()->getValue()->getString()) {
			if (entity->getModel()->getAnimationSetup(animationsAnimationName->getController()->getValue()->getString()) != nullptr) {
				throw ExceptionBase("Name '" + animationsAnimationName->getController()->getValue()->getString() + "' already in use");
			}
			(*entity->getModel()->getAnimationSetups()).erase(animationSetup->getId());
			animationSetup = entity->getModel()->addAnimationSetup(
				animationsAnimationName->getController()->getValue()->getString(),
				0,
				0,
				false
			);
		}
		animationSetup->setStartFrame(Integer::parseInt(animationsAnimationStartFrame->getController()->getValue()->getString()));
		animationSetup->setEndFrame(Integer::parseInt(animationsAnimationEndFrame->getController()->getValue()->getString()));
		animationSetup->setOverlayFromGroupId(animationsAnimationOverlayFromGroupIdDropDown->getController()->getValue()->getString());
		animationSetup->setLoop(animationsAnimationLoop->getController()->getValue()->getString() == "1");
		setAnimations(entity);
		animationsDropDown->getController()->setValue(value->set(animationSetup->getId()));
		onAnimationDropDownApply();
		view->playAnimation(animationSetup->getId());
	} catch (Exception& exception) {
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void ModelEditorScreenController::unsetAnimations() {

	dynamic_cast<GUIParentNode*>(animationsDropDown->getScreenNode()->getNodeById(animationsDropDown->getId() + "_inner"))->clearSubNodes();
	animationsDropDown->getController()->setValue(value->set(""));
	animationsDropDown->getController()->setDisabled(true);
	animationsDropDownApply->getController()->setDisabled(true);
	animationsDropDownDelete->getController()->setDisabled(true);
	animationsAnimationStartFrame->getController()->setValue(value->set(""));
	animationsAnimationStartFrame->getController()->setDisabled(true);
	animationsAnimationEndFrame->getController()->setValue(value->set(""));
	animationsAnimationEndFrame->getController()->setDisabled(true);
	animationsAnimationOverlayFromGroupIdDropDown->getController()->setValue(value->set(""));
	animationsAnimationOverlayFromGroupIdDropDown->getController()->setDisabled(true);
	animationsAnimationLoop->getController()->setValue(value->set(""));
	animationsAnimationLoop->getController()->setDisabled(true);
	animationsAnimationName->getController()->setValue(value->set(""));
	animationsAnimationName->getController()->setDisabled(true);
	animationsAnimationApply->getController()->setDisabled(true);
}

void ModelEditorScreenController::setStatistics(int32_t statsOpaqueFaces, int32_t statsTransparentFaces, int32_t statsMaterialCount)
{
	this->statsOpaqueFaces->getController()->setValue(value->set(statsOpaqueFaces));
	this->statsTransparentFaces->getController()->setValue(value->set(statsTransparentFaces));
	this->statsMaterialCount->getController()->setValue(value->set(statsMaterialCount));
}

void ModelEditorScreenController::onQuit()
{
	TDMEModelEditor::getInstance()->quit();
}

void ModelEditorScreenController::onModelLoad()
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
		new ModelEditorScreenController_onModelLoad_2(this)
	);
}

void ModelEditorScreenController::onModelSave()
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
		new ModelEditorScreenController_onModelSave_3(this)
	);
}

void ModelEditorScreenController::onModelReload()
{
	view->reloadFile();
}

void ModelEditorScreenController::onPivotApply()
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

void ModelEditorScreenController::onRenderingApply()
{
	if (view->getEntity() == nullptr) return;
	view->getEntity()->setDynamicShadowing(renderingDynamicShadowing->getController()->getValue()->equals("1"));
}

void ModelEditorScreenController::saveFile(const string& pathName, const string& fileName) /* throws(Exception) */
{
	view->saveFile(pathName, fileName);
}

void ModelEditorScreenController::loadFile(const string& pathName, const string& fileName) /* throws(Exception) */
{
	view->loadFile(pathName, fileName);
}

void ModelEditorScreenController::showErrorPopUp(const string& caption, const string& message)
{
	view->getPopUpsViews()->getInfoDialogScreenController()->show(caption, message);
}

void ModelEditorScreenController::onValueChanged(GUIElementNode* node)
{
	if (node->getId() == "animations_dropdown") {
		onAnimationDropDownValueChanged();
	} else {
		entityBaseSubScreenController->onValueChanged(node, view->getEntity());
	}
}

void ModelEditorScreenController::onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node)
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
				} else
				if (node->getId().compare("button_materials_dropdown_apply") == 0) {
					onMaterialDropDownApply();
				} else
				if (node->getId().compare("button_materials_material_apply") == 0) {
					onMaterialApply();
				} else
				if (node->getId().compare("button_materials_material_diffuse_texture_load") == 0) {
					onMaterialLoadDiffuseTexture();
				} else
				if (node->getId().compare("button_materials_material_diffuse_transparency_texture_load") == 0) {
					onMaterialLoadDiffuseTransparencyTexture();
				} else
				if (node->getId().compare("button_materials_material_normal_texture_load") == 0) {
					onMaterialLoadNormalTexture();
				} else
				if (node->getId().compare("button_materials_material_specular_texture_load") == 0) {
					onMaterialLoadSpecularTexture();
				} else
				if (node->getId().compare("button_materials_material_diffuse_texture_clear") == 0) {
					onMaterialClearTexture(materialsMaterialDiffuseTexture);
				} else
				if (node->getId().compare("button_materials_material_diffuse_transparency_texture_clear") == 0) {
					onMaterialClearTexture(materialsMaterialDiffuseTransparencyTexture);
				} else
				if (node->getId().compare("button_materials_material_normal_texture_clear") == 0) {
					onMaterialClearTexture(materialsMaterialNormalTexture);
				} else
				if (node->getId().compare("button_materials_material_specular_texture_clear") == 0) {
					onMaterialClearTexture(materialsMaterialSpecularTexture);
				} else
				if (node->getId().compare("animations_dropdown_apply") == 0) {
					onAnimationDropDownApply();
				} else
				if (node->getId().compare("animations_dropdown_delete") == 0) {
					onAnimationDropDownDelete();
				} else
				if (node->getId().compare("button_animations_animation_apply") == 0){
					onAnimationApply();
				} else {
					Console::println(
						string(
							"ModelEditorScreenController::onActionPerformed()::unknown, type='" +
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
