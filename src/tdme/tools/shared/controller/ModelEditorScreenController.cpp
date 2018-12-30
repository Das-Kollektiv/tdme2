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
#include <tdme/tools/shared/controller/EntityPhysicsSubScreenController.h>
#include <tdme/tools/shared/controller/EntityDisplaySubScreenController.h>
#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/tools/shared/controller/ModelEditorScreenController_ModelEditorScreenController_1.h>
#include <tdme/tools/shared/controller/ModelEditorScreenController_onMaterialLoadTexture.h>
#include <tdme/tools/shared/controller/ModelEditorScreenController_onModelLoad_2.h>
#include <tdme/tools/shared/controller/ModelEditorScreenController_onModelSave_3.h>
#include <tdme/tools/shared/controller/ModelEditorScreenController_onLODModelLoad.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityAudio.h>
#include <tdme/tools/shared/model/LevelEditorEntityLODLevel.h>
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
using tdme::tools::shared::controller::EntityPhysicsSubScreenController;
using tdme::tools::shared::controller::EntityDisplaySubScreenController;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::controller::ModelEditorScreenController_ModelEditorScreenController_1;
using tdme::tools::shared::controller::ModelEditorScreenController_onMaterialLoadTexture;
using tdme::tools::shared::controller::ModelEditorScreenController_onModelLoad_2;
using tdme::tools::shared::controller::ModelEditorScreenController_onModelSave_3;
using tdme::tools::shared::controller::ModelEditorScreenController_onLODModelLoad;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityAudio;
using tdme::tools::shared::model::LevelEditorEntityLODLevel;
using tdme::tools::shared::model::LevelEditorEntityModel;
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

ModelEditorScreenController::ModelEditorScreenController(SharedModelEditorView* view) 
{
	this->modelPath = new FileDialogPath(".");
	this->audioPath = new FileDialogPath(".");
	this->view = view;
	auto const finalView = view;
	this->entityBaseSubScreenController = new EntityBaseSubScreenController(view->getPopUpsViews(), new ModelEditorScreenController_ModelEditorScreenController_1(this, finalView));
	this->entityDisplaySubScreenController = new EntityDisplaySubScreenController();
	this->entityPhysicsSubScreenController = new EntityPhysicsSubScreenController(view->getPopUpsViews(), modelPath, true);
}

ModelEditorScreenController::~ModelEditorScreenController() {
	delete modelPath;
	delete audioPath;
	delete entityBaseSubScreenController;
	delete entityDisplaySubScreenController;
	delete entityPhysicsSubScreenController;
}

SharedModelEditorView* ModelEditorScreenController::getView() {
	return view;
}

EntityDisplaySubScreenController* ModelEditorScreenController::getEntityDisplaySubScreenController()
{
	return entityDisplaySubScreenController;
}

EntityPhysicsSubScreenController* ModelEditorScreenController::getEntityPhysicsSubScreenController()
{
	return entityPhysicsSubScreenController;
}

GUIScreenNode* ModelEditorScreenController::getScreenNode()
{
	return screenNode;
}

FileDialogPath* ModelEditorScreenController::getModelPath()
{
	return modelPath;
}

FileDialogPath* ModelEditorScreenController::getAudioPath() {
	return audioPath;
}

void ModelEditorScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse("resources/engine/tools/modeleditor/gui", "screen_modeleditor.xml");
		screenNode->addActionListener(this);
		screenNode->addChangeListener(this);
		screenCaption = dynamic_cast< GUITextNode* >(screenNode->getNodeById("screen_caption"));
		modelReload = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_model_reload"));
		modelSave = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_model_save"));
		pivotX = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("pivot_x"));
		pivotY = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("pivot_y"));
		pivotZ = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("pivot_z"));
		pivotApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_pivot_apply"));
		renderingDynamicShadowing = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("rendering_dynamic_shadowing"));
		renderingRenderGroups = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("rendering_render_groups"));
		renderingShader = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("rendering_shader"));
		renderingDistanceShader = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("rendering_distance_shader"));
		renderingDistanceShaderDistance = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("rendering_distance_shader_distance"));
		renderingApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_rendering_apply"));
		lodLevel = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("lod_level"));
		lodLevelApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("lod_level_apply"));
		lodType = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("lod_type"));
		lodModelFile = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("lod_model_file"));
		lodModelFileLoad = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("lod_model_file_load"));
		lodModelFileClear = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("lod_model_file_clear"));
		lodMinDistance = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("lod_min_distance"));
		lodPlaneRotationY = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("lod_plane_rotation_y"));
		lodColorMul = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("lod_color_mul"));
		lodColorAdd = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("lod_color_add"));
		buttonLodApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_lod_apply"));
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
		materialsMaterialMaskedTransparencyThreshold = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_masked_transparency_threshold"));;
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
		statsOpaqueFaces = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("stats_opaque_faces"));
		animationsAnimationSoundFile = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("animations_animation_sound_file"));
		animationsAnimationSoundLoad = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("animations_animation_sound_load"));
		animationsAnimationSoundClear = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("animations_animation_sound_clear"));
		animationsAnimationSoundGain = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("animations_animation_sound_gain"));
		animationsAnimationSoundPitch = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("animations_animation_sound_pitch"));
		animationsAnimationSoundOffset = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("animations_animation_sound_offset"));
		animationsAnimationSoundLooping = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("animations_animation_sound_looping"));
		animationsAnimationSoundFixed = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("animations_animation_sound_fixed"));
		animationsAnimationSoundApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_animations_sound_apply"));
		buttonToolsComputeNormals = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_tools_computenormals"));
		statsTransparentFaces = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("stats_transparent_faces"));
		statsMaterialCount = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("stats_material_count"));
		statsOpaqueFaces->getController()->setDisabled(true);
		statsTransparentFaces->getController()->setDisabled(true);
		statsMaterialCount->getController()->setDisabled(true);
	} catch (Exception& exception) {
		Console::print(string("ModelEditorScreenController::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	entityBaseSubScreenController->initialize(screenNode);
	entityDisplaySubScreenController->initialize(screenNode);
	entityPhysicsSubScreenController->initialize(screenNode);
}

void ModelEditorScreenController::dispose()
{
}

void ModelEditorScreenController::setScreenCaption(const string& text)
{
	screenCaption->setText(text);
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
	pivotX->getController()->setValue(MutableString(Tools::formatFloat(pivot.getX())));
	pivotY->getController()->setDisabled(false);
	pivotY->getController()->setValue(MutableString(Tools::formatFloat(pivot.getY())));
	pivotZ->getController()->setDisabled(false);
	pivotZ->getController()->setValue(MutableString(Tools::formatFloat(pivot.getZ())));
	pivotApply->getController()->setDisabled(false);
}

void ModelEditorScreenController::unsetPivot()
{
	pivotX->getController()->setDisabled(true);
	pivotX->getController()->setValue(MutableString());
	pivotY->getController()->setDisabled(true);
	pivotY->getController()->setValue(MutableString());
	pivotZ->getController()->setDisabled(true);
	pivotZ->getController()->setValue(MutableString());
	pivotApply->getController()->setDisabled(true);
}

void ModelEditorScreenController::setRendering(LevelEditorEntity* entity)
{
	renderingDynamicShadowing->getController()->setDisabled(false);
	renderingDynamicShadowing->getController()->setValue(MutableString(entity->isDynamicShadowing() == true?"1":""));
	renderingRenderGroups->getController()->setDisabled(false);
	renderingRenderGroups->getController()->setValue(MutableString(entity->isRenderGroups() == true?"1":""));
	renderingShader->getController()->setDisabled(false);
	renderingShader->getController()->setValue(MutableString(entity->getShader()));
	renderingDistanceShader->getController()->setDisabled(false);
	renderingDistanceShader->getController()->setValue(MutableString(entity->getDistanceShader()));
	renderingDistanceShaderDistance->getController()->setDisabled(false);
	renderingDistanceShaderDistance->getController()->setValue(MutableString(entity->getDistanceShaderDistance(), 4));
	renderingApply->getController()->setDisabled(false);
}

void ModelEditorScreenController::unsetRendering()
{
	renderingDynamicShadowing->getController()->setDisabled(true);
	renderingDynamicShadowing->getController()->setValue(MutableString("1"));
	renderingRenderGroups->getController()->setDisabled(true);
	renderingRenderGroups->getController()->setValue(MutableString("0"));
	renderingShader->getController()->setDisabled(true);
	renderingShader->getController()->setValue(MutableString("default"));
	renderingDistanceShader->getController()->setDisabled(true);
	renderingDistanceShader->getController()->setValue(MutableString("default"));
	renderingDistanceShaderDistance->getController()->setDisabled(true);
	renderingDistanceShaderDistance->getController()->setValue(MutableString(10000.0f, 4));
	renderingApply->getController()->setDisabled(true);
}

LevelEditorEntityLODLevel* ModelEditorScreenController::getLODLevel(int level) {
	auto entity = view->getEntity();
	switch(level) {
		case 2:
			{
				auto entityLodLevel = entity->getLODLevel2();
				if (entityLodLevel == nullptr) {
					entityLodLevel = new LevelEditorEntityLODLevel(
						LODObject3D::LODLEVELTYPE_NONE,
						"",
						nullptr,
						0.0f,
						0.0f
					);
					entity->setLODLevel2(entityLodLevel);
				}
				return entityLodLevel;
			}
		case 3:
			{
				auto entityLodLevel = entity->getLODLevel3();
				if (entityLodLevel == nullptr) {
					entityLodLevel = new LevelEditorEntityLODLevel(
						LODObject3D::LODLEVELTYPE_NONE,
						"",
						nullptr,
						0.0f,
						0.0f
					);
					entity->setLODLevel3(entityLodLevel);
				}
				return entityLodLevel;
			}
		default:
			{
				return nullptr;
			}
	}
}

void ModelEditorScreenController::setLODLevel(LevelEditorEntity* entity, int level) {
	auto entityLodLevel = getLODLevel(level);
	if (entityLodLevel == nullptr) {
		lodLevel->getController()->setValue(MutableString(to_string(level)));
		lodLevel->getController()->setDisabled(false);
		lodLevelApply->getController()->setDisabled(false);
		lodType->getController()->setValue(MutableString("1"));
		lodType->getController()->setDisabled(true);
		lodModelFile->getController()->setValue(MutableString(entity->getFileName()));
		lodModelFile->getController()->setDisabled(true);
		lodModelFileLoad->getController()->setDisabled(true);
		lodModelFileClear->getController()->setDisabled(true);
		lodMinDistance->getController()->setValue(MutableString("0.0"));
		lodMinDistance->getController()->setDisabled(true);
		lodPlaneRotationY->getController()->setValue(MutableString("0.0"));
		lodPlaneRotationY->getController()->setDisabled(true);
		lodColorMul->getController()->setValue(MutableString("1.0, 1.0, 1.0, 1.0"));
		lodColorMul->getController()->setDisabled(true);
		lodColorAdd->getController()->setValue(MutableString("0.0, 0.0, 0.0, 0.0"));
		lodColorAdd->getController()->setDisabled(true);
		lodPlaneRotationY->getController()->setValue(MutableString("0.0"));
		lodPlaneRotationY->getController()->setDisabled(true);
		buttonLodApply->getController()->setDisabled(true);
	} else {
		lodLevel->getController()->setValue(MutableString(to_string(level)));
		lodLevel->getController()->setDisabled(false);
		lodLevelApply->getController()->setDisabled(false);
		lodType->getController()->setValue(MutableString(to_string(entityLodLevel->getType())));
		lodType->getController()->setDisabled(false);
		lodModelFile->getController()->setValue(MutableString(entityLodLevel->getFileName()));
		lodModelFile->getController()->setDisabled(false);
		lodModelFileLoad->getController()->setDisabled(false);
		lodModelFileClear->getController()->setDisabled(false);
		lodMinDistance->getController()->setValue(MutableString(entityLodLevel->getMinDistance()));
		lodMinDistance->getController()->setDisabled(false);
		lodPlaneRotationY->getController()->setValue(MutableString(entityLodLevel->getPlaneRotationY()));
		lodPlaneRotationY->getController()->setDisabled(false);
		lodColorMul->getController()->setValue(MutableString(Tools::formatColor4(entityLodLevel->getColorMul())));
		lodColorMul->getController()->setDisabled(false);
		lodColorAdd->getController()->setValue(MutableString(Tools::formatColor4(entityLodLevel->getColorAdd())));
		lodColorAdd->getController()->setDisabled(false);
		buttonLodApply->getController()->setDisabled(false);
	}
	view->setLodLevel(level);
}

void ModelEditorScreenController::unsetLODLevel() {
	lodLevel->getController()->setValue(MutableString("1"));
	lodLevel->getController()->setDisabled(true);
	lodLevelApply->getController()->setDisabled(true);
	lodType->getController()->setValue(MutableString("0"));
	lodType->getController()->setDisabled(true);
	lodModelFile->getController()->setValue(MutableString());
	lodModelFile->getController()->setDisabled(true);
	lodModelFileLoad->getController()->setDisabled(true);
	lodModelFileClear->getController()->setDisabled(true);
	lodMinDistance->getController()->setValue(MutableString("0.0"));
	lodMinDistance->getController()->setDisabled(true);
	lodPlaneRotationY->getController()->setValue(MutableString("0.0"));
	lodPlaneRotationY->getController()->setDisabled(true);
	lodColorMul->getController()->setValue(MutableString("1.0, 1.0, 1.0, 1.0"));
	lodColorMul->getController()->setDisabled(true);
	lodColorAdd->getController()->setValue(MutableString("0.0, 0.0, 0.0, 0.0"));
	lodColorAdd->getController()->setDisabled(true);
	buttonLodApply->getController()->setDisabled(true);
}

void ModelEditorScreenController::onLODLevelApply() {
	auto entity = view->getEntity();
	auto lodLevelInt = Tools::convertToIntSilent(lodLevel->getController()->getValue().getString());
	setLODLevel(entity, lodLevelInt);
}

void ModelEditorScreenController::onLODLevelLoadModel() {
	auto entity = view->getEntity();
	auto lodLevelInt = Tools::convertToIntSilent(lodLevel->getController()->getValue().getString());
	auto entityLodLevel = getLODLevel(lodLevelInt);
	if (entityLodLevel == nullptr) return;
	auto extensions = ModelReader::getModelExtensions();
	view->getPopUpsViews()->getFileDialogScreenController()->show(
		entityLodLevel->getFileName() != ""?Tools::getPath(entityLodLevel->getFileName()):modelPath->getPath(),
		"Load from: ",
		extensions,
		Tools::getFileName(entityLodLevel->getFileName()),
		new ModelEditorScreenController_onLODModelLoad(this)
	);
}

void ModelEditorScreenController::onLODLevelClearModel() {
	lodModelFile->getController()->setValue(MutableString());
}

void ModelEditorScreenController::onLODLevelApplySettings() {
	view->resetEntity();
	auto entity = view->getEntity();
	auto lodLevelInt = Tools::convertToIntSilent(lodLevel->getController()->getValue().getString());
	LevelEditorEntityLODLevel* entityLodLevel = getLODLevel(lodLevelInt);
	try {
		entityLodLevel->setType(static_cast<LODObject3D::LODLevelType>(Tools::convertToIntSilent(lodType->getController()->getValue().getString())));
		entityLodLevel->setFileName(
			entityLodLevel->getType() == LODObject3D::LODLEVELTYPE_MODEL ||
			entityLodLevel->getType() == LODObject3D::LODLEVELTYPE_PLANE?
				lodModelFile->getController()->getValue().getString():
				""
			);
		entityLodLevel->setMinDistance(Tools::convertToFloat(lodMinDistance->getController()->getValue().getString()));
		entityLodLevel->setPlaneRotationY(Tools::convertToFloat(lodPlaneRotationY->getController()->getValue().getString()));
		entityLodLevel->setColorMul(Tools::convertToColor4(lodColorMul->getController()->getValue().getString()));
		entityLodLevel->setColorAdd(Tools::convertToColor4(lodColorAdd->getController()->getValue().getString()));
		entityLodLevel->setModel(
			entityLodLevel->getType() == LODObject3D::LODLEVELTYPE_MODEL ||
			entityLodLevel->getType() == LODObject3D::LODLEVELTYPE_PLANE?
				ModelReader::read(
					Tools::getPath(entityLodLevel->getFileName()),
					Tools::getFileName(entityLodLevel->getFileName())
				):
				nullptr
		);
	} catch (Exception& exception) {
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void ModelEditorScreenController::setMaterials(LevelEditorEntity* entity) {
	Model* model = view->getLodLevel() == 1?entity->getModel():getLODLevel(view->getLodLevel())->getModel();
	if (model == nullptr) {
		unsetMaterials();
		return;
	}

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
	materialsMaterialMaskedTransparencyThreshold->getController()->setDisabled(false);
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

	materialsDropdown->getController()->setValue(MutableString());
	materialsDropdown->getController()->setDisabled(true);
	materialsDropdownApply->getController()->setDisabled(true);
	materialsMaterialName->getController()->setValue(MutableString(""));
	materialsMaterialAmbient->getController()->setDisabled(true);
	materialsMaterialAmbient->getController()->setValue(MutableString(""));
	materialsMaterialDiffuse->getController()->setDisabled(true);
	materialsMaterialDiffuse->getController()->setValue(MutableString());
	materialsMaterialSpecular->getController()->setDisabled(true);
	materialsMaterialSpecular->getController()->setValue(MutableString());
	materialsMaterialEmission->getController()->setDisabled(true);
	materialsMaterialEmission->getController()->setValue(MutableString());
	materialsMaterialShininess->getController()->setDisabled(true);
	materialsMaterialShininess->getController()->setValue(MutableString());
	materialsMaterialApply->getController()->setDisabled(true);
	materialsMaterialDiffuseTexture->getController()->setValue(MutableString());
	materialsMaterialDiffuseTextureLoad->getController()->setDisabled(true);
	materialsMaterialDiffuseTextureClear->getController()->setDisabled(true);
	materialsMaterialDiffuseTransparencyTexture->getController()->setValue(MutableString());
	materialsMaterialDiffuseTransparencyTextureLoad->getController()->setDisabled(true);
	materialsMaterialDiffuseTransparencyTextureClear->getController()->setDisabled(true);
	materialsMaterialNormalTexture->getController()->setValue(MutableString());
	materialsMaterialNormalTextureLoad->getController()->setDisabled(true);
	materialsMaterialNormalTextureClear->getController()->setDisabled(true);
	materialsMaterialSpecularTexture->getController()->setValue(MutableString());
	materialsMaterialSpecularTextureLoad->getController()->setDisabled(true);
	materialsMaterialSpecularTextureClear->getController()->setDisabled(true);
	materialsMaterialShininess->getController()->setValue(MutableString());
	materialsMaterialUseMaskedTransparency->getController()->setValue(MutableString());
	materialsMaterialUseMaskedTransparency->getController()->setDisabled(true);
	materialsMaterialMaskedTransparencyThreshold->getController()->setValue(MutableString());
	materialsMaterialMaskedTransparencyThreshold->getController()->setDisabled(true);
}

void ModelEditorScreenController::onMaterialDropDownApply() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;

	materialsMaterialName->getController()->setValue(MutableString(material->getId()));
	materialsMaterialAmbient->getController()->setValue(MutableString(Tools::formatColor4(material->getAmbientColor())));
	materialsMaterialDiffuse->getController()->setValue(MutableString(Tools::formatColor4(material->getDiffuseColor())));
	materialsMaterialSpecular->getController()->setValue(MutableString(Tools::formatColor4(material->getSpecularColor())));
	materialsMaterialEmission->getController()->setValue(MutableString(Tools::formatColor4(material->getEmissionColor())));
	materialsMaterialShininess->getController()->setValue(MutableString(Tools::formatFloat(material->getShininess())));
	materialsMaterialDiffuseTexture->getController()->setValue(
		MutableString(material->getDiffuseTexturePathName()).append(material->getDiffuseTexturePathName() == ""?"":"/").append(material->getDiffuseTextureFileName())
	);
	materialsMaterialDiffuseTransparencyTexture->getController()->setValue(
		MutableString(material->getDiffuseTransparencyTexturePathName()).append(material->getDiffuseTransparencyTexturePathName() == ""?"":"/").append(material->getDiffuseTransparencyTextureFileName())
	);
	materialsMaterialNormalTexture->getController()->setValue(
		MutableString(material->getNormalTexturePathName()).append(material->getNormalTexturePathName() == ""?"":"/").append(material->getNormalTextureFileName())
	);
	materialsMaterialSpecularTexture->getController()->setValue(
		MutableString(material->getSpecularTexturePathName()).append(material->getSpecularTexturePathName() == ""?"":"/").append(material->getSpecularTextureFileName())
	);
	materialsMaterialUseMaskedTransparency->getController()->setValue(MutableString(material->hasDiffuseTextureMaskedTransparency() == true?"1":""));
	materialsMaterialMaskedTransparencyThreshold->getController()->setValue(MutableString(Tools::formatFloat(material->getDiffuseTextureMaskedTransparencyThreshold())));
}

Material* ModelEditorScreenController::getSelectedMaterial() {
	Model* model = view->getLodLevel() == 1?view->getEntity()->getModel():getLODLevel(view->getLodLevel())->getModel();
	if (model == nullptr) return nullptr;
	auto materialIt = model->getMaterials()->find(materialsDropdown->getController()->getValue().getString());
	return materialIt != model->getMaterials()->end()?materialIt->second:nullptr;
}

void ModelEditorScreenController::onMaterialApply() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;

	try {
		view->resetEntity();
		material->setAmbientColor(Tools::convertToColor4(materialsMaterialAmbient->getController()->getValue().getString()));
		material->setDiffuseColor(Tools::convertToColor4(materialsMaterialDiffuse->getController()->getValue().getString()));
		material->setSpecularColor(Tools::convertToColor4(materialsMaterialSpecular->getController()->getValue().getString()));
		material->setEmissionColor(Tools::convertToColor4(materialsMaterialEmission->getController()->getValue().getString()));
		material->setShininess(Tools::convertToFloat(materialsMaterialShininess->getController()->getValue().getString()));
		material->setDiffuseTexture(
			Tools::getPath(materialsMaterialDiffuseTexture->getController()->getValue().getString()),
			Tools::getFileName(materialsMaterialDiffuseTexture->getController()->getValue().getString()),
			Tools::getPath(materialsMaterialDiffuseTransparencyTexture->getController()->getValue().getString()),
			Tools::getFileName(materialsMaterialDiffuseTransparencyTexture->getController()->getValue().getString())
		);
		material->setNormalTexture(
			Tools::getPath(materialsMaterialNormalTexture->getController()->getValue().getString()),
			Tools::getFileName(materialsMaterialNormalTexture->getController()->getValue().getString())
		);
		material->setSpecularTexture(
			Tools::getPath(materialsMaterialSpecularTexture->getController()->getValue().getString()),
			Tools::getFileName(materialsMaterialSpecularTexture->getController()->getValue().getString())
		);
		material->setDiffuseTextureMaskedTransparency(materialsMaterialUseMaskedTransparency->getController()->getValue().getString() == "1"?true:false);
		material->setDiffuseTextureMaskedTransparencyThreshold(Tools::convertToFloat(materialsMaterialMaskedTransparencyThreshold->getController()->getValue().getString()));
	} catch (Exception& exception) {
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void ModelEditorScreenController::onMaterialLoadDiffuseTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;

	auto extensions = TextureLoader::getTextureExtensions();
	view->getPopUpsViews()->getFileDialogScreenController()->show(
		material->getDiffuseTextureFileName() != ""?material->getDiffuseTexturePathName():modelPath->getPath(),
		"Load from: ",
		extensions,
		material->getDiffuseTextureFileName(),
		new ModelEditorScreenController_onMaterialLoadTexture(this, materialsMaterialDiffuseTexture)
	);
}

void ModelEditorScreenController::onMaterialLoadDiffuseTransparencyTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;

	auto extensions = TextureLoader::getTextureExtensions();
	view->getPopUpsViews()->getFileDialogScreenController()->show(
		material->getDiffuseTransparencyTextureFileName() != ""?material->getDiffuseTransparencyTexturePathName():modelPath->getPath(),
		"Load from: ",
		extensions,
		material->getDiffuseTransparencyTextureFileName(),
		new ModelEditorScreenController_onMaterialLoadTexture(this, materialsMaterialDiffuseTransparencyTexture)
	);
}

void ModelEditorScreenController::onMaterialLoadNormalTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;

	auto extensions = TextureLoader::getTextureExtensions();
	view->getPopUpsViews()->getFileDialogScreenController()->show(
		material->getNormalTextureFileName() != ""?material->getNormalTexturePathName():modelPath->getPath(),
		"Load from: ",
		extensions,
		material->getNormalTextureFileName(),
		new ModelEditorScreenController_onMaterialLoadTexture(this, materialsMaterialNormalTexture)
	);
}

void ModelEditorScreenController::onMaterialLoadSpecularTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;

	auto extensions = TextureLoader::getTextureExtensions();
	view->getPopUpsViews()->getFileDialogScreenController()->show(
		material->getSpecularTextureFileName() != ""?material->getSpecularTexturePathName():modelPath->getPath(),
		"Load from: ",
		extensions,
		material->getSpecularTextureFileName(),
		new ModelEditorScreenController_onMaterialLoadTexture(this, materialsMaterialNormalTexture)
	);
}

void ModelEditorScreenController::onMaterialClearTexture(GUIElementNode* guiElementNode) {
	guiElementNode->getController()->setValue(MutableString(""));
}

void ModelEditorScreenController::setAnimations(LevelEditorEntity* entity) {
	Model* model = view->getLodLevel() == 1?view->getEntity()->getModel():getLODLevel(view->getLodLevel())->getModel();
	if (model == nullptr) {
		unsetAnimations();
		return;
	}

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
	animationsDropDown->getController()->setValue(MutableString(Model::ANIMATIONSETUP_DEFAULT));

	// apply
	onAnimationDropDownApply();
}

void ModelEditorScreenController::onAnimationDropDownValueChanged() {
	Model* model = view->getLodLevel() == 1?view->getEntity()->getModel():getLODLevel(view->getLodLevel())->getModel();
	if (model == nullptr) return;

	auto animationSetup = model->getAnimationSetup(animationsDropDown->getController()->getValue().getString());
	auto defaultAnimation = animationSetup != nullptr && animationSetup->getId() == Model::ANIMATIONSETUP_DEFAULT;
	animationsDropDownDelete->getController()->setDisabled(defaultAnimation || animationSetup == nullptr);
}

void ModelEditorScreenController::onAnimationDropDownApply() {
	Model* model = view->getLodLevel() == 1?view->getEntity()->getModel():getLODLevel(view->getLodLevel())->getModel();
	if (model == nullptr) return;

	auto animationName = animationsDropDown->getController()->getValue().getString();

	auto animationSetup = model->getAnimationSetup(animationName);
	AnimationSetup newAnimationSetup(
		model,
		"New animation",
		model->getAnimationSetup(Model::ANIMATIONSETUP_DEFAULT)->getStartFrame(),
		model->getAnimationSetup(Model::ANIMATIONSETUP_DEFAULT)->getEndFrame(),
		true,
		""
	);
	if (animationSetup == nullptr) animationSetup = &newAnimationSetup;
	auto defaultAnimation = animationSetup->getId() == Model::ANIMATIONSETUP_DEFAULT;

	animationsDropDown->getController()->setDisabled(false);
	animationsDropDownApply->getController()->setDisabled(false);
	animationsDropDownDelete->getController()->setDisabled(defaultAnimation || animationSetup == &newAnimationSetup);
	animationsAnimationStartFrame->getController()->setValue(MutableString(animationSetup->getStartFrame()));
	animationsAnimationStartFrame->getController()->setDisabled(defaultAnimation);
	animationsAnimationEndFrame->getController()->setValue(MutableString(animationSetup->getEndFrame()));
	animationsAnimationEndFrame->getController()->setDisabled(defaultAnimation);
	animationsAnimationOverlayFromGroupIdDropDown->getController()->setValue(MutableString(animationSetup->getOverlayFromGroupId()));
	animationsAnimationOverlayFromGroupIdDropDown->getController()->setDisabled(defaultAnimation);
	animationsAnimationLoop->getController()->setValue(MutableString(animationSetup->isLoop() == true?"1":""));
	animationsAnimationLoop->getController()->setDisabled(defaultAnimation);
	animationsAnimationName->getController()->setValue(MutableString(animationSetup->getId()));
	animationsAnimationName->getController()->setDisabled(defaultAnimation);
	animationsAnimationApply->getController()->setDisabled(defaultAnimation);
	if (animationSetup != &newAnimationSetup) {
		auto animationSound = view->getEntity()->getModelSettings()->createAnimationSound(animationName);
		animationsAnimationSoundFile->getController()->setValue(MutableString(animationSound->getFileName()));
		animationsAnimationSoundFile->getController()->setDisabled(defaultAnimation);
		animationsAnimationSoundLoad->getController()->setDisabled(defaultAnimation);
		animationsAnimationSoundClear->getController()->setDisabled(defaultAnimation);
		animationsAnimationSoundGain->getController()->setValue(MutableString(animationSound->getGain(), 4));
		animationsAnimationSoundGain->getController()->setDisabled(defaultAnimation);
		animationsAnimationSoundPitch->getController()->setValue(MutableString(animationSound->getPitch(), 4));
		animationsAnimationSoundPitch->getController()->setDisabled(defaultAnimation);
		animationsAnimationSoundOffset->getController()->setValue(MutableString(animationSound->getOffset()));
		animationsAnimationSoundOffset->getController()->setDisabled(defaultAnimation);
		animationsAnimationSoundLooping->getController()->setValue(MutableString(animationSound->isLooping() == true?"1":""));
		animationsAnimationSoundLooping->getController()->setDisabled(defaultAnimation);
		animationsAnimationSoundFixed->getController()->setValue(MutableString(animationSound->isFixed() == true?"1":""));
		animationsAnimationSoundFixed->getController()->setDisabled(defaultAnimation);
		animationsAnimationSoundApply->getController()->setDisabled(defaultAnimation);
		view->playAnimation(animationSetup->getId());
	} else {
		unsetAnimationSound();
	}
}

void ModelEditorScreenController::onAnimationDropDownDelete() {
	Model* model = view->getLodLevel() == 1?view->getEntity()->getModel():getLODLevel(view->getLodLevel())->getModel();
	if (model == nullptr) return;

	auto animationName = animationsDropDown->getController()->getValue().getString();
	view->getEntity()->getModelSettings()->removeAnimationSound(animationName);
	auto animationSetup = model->getAnimationSetup(animationName);
	auto it = model->getAnimationSetups()->find(animationSetup->getId());
	it = model->getAnimationSetups()->erase(it);
	delete animationSetup;

	setAnimations(view->getEntity());
	animationsDropDown->getController()->setValue(MutableString(it->second->getId()));
	onAnimationDropDownApply();
}

void ModelEditorScreenController::onAnimationApply() {
	Model* model = view->getLodLevel() == 1?view->getEntity()->getModel():getLODLevel(view->getLodLevel())->getModel();
	if (model == nullptr) return;

	auto animationName = animationsDropDown->getController()->getValue().getString();
	auto animationSetup = model->getAnimationSetup(animationName);
	try {
		if (animationSetup == nullptr) {
			if (model->getAnimationSetup(animationsAnimationName->getController()->getValue().getString()) != nullptr) {
				throw ExceptionBase("Name '" + animationsAnimationName->getController()->getValue().getString() + "' already in use");
			}
			animationSetup = model->addAnimationSetup(
				animationsAnimationName->getController()->getValue().getString(),
				0,
				0,
				false
			);
		} else
		if (animationSetup->getId() != animationsAnimationName->getController()->getValue().getString()) {
			if (model->getAnimationSetup(animationsAnimationName->getController()->getValue().getString()) != nullptr) {
				throw ExceptionBase("Name '" + animationsAnimationName->getController()->getValue().getString() + "' already in use");
			}
			view->getEntity()->getModelSettings()->renameAnimationSound(animationSetup->getId(), animationsAnimationName->getController()->getValue().getString());
			(*model->getAnimationSetups()).erase(animationSetup->getId());
			animationSetup = model->addAnimationSetup(
				animationsAnimationName->getController()->getValue().getString(),
				0,
				0,
				false
			);
		}
		animationSetup->setStartFrame(Integer::parseInt(animationsAnimationStartFrame->getController()->getValue().getString()));
		animationSetup->setEndFrame(Integer::parseInt(animationsAnimationEndFrame->getController()->getValue().getString()));
		animationSetup->setOverlayFromGroupId(animationsAnimationOverlayFromGroupIdDropDown->getController()->getValue().getString());
		animationSetup->setLoop(animationsAnimationLoop->getController()->getValue().getString() == "1");
		setAnimations(view->getEntity());
		animationsDropDown->getController()->setValue(MutableString(animationSetup->getId()));
		view->getEntity()->getModelSettings()->createAnimationSound(animationName);
		onAnimationDropDownApply();
		view->playAnimation(animationSetup->getId());
	} catch (Exception& exception) {
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void ModelEditorScreenController::onAnimationSoundClear() {
	animationsAnimationSoundFile->getController()->setValue(MutableString(""));
}

void ModelEditorScreenController::onAnimationSoundLoad() {
	class LoadSoundAction: public virtual Action
	{
	public:
		LoadSoundAction(ModelEditorScreenController* modelEditorScreenController): modelEditorScreenController(modelEditorScreenController) {
		}
		void performAction() override {
			modelEditorScreenController->animationsAnimationSoundFile->getController()->setValue(
				modelEditorScreenController->getView()->getPopUpsViews()->getFileDialogScreenController()->getPathName() +
				"/" +
				modelEditorScreenController->getView()->getPopUpsViews()->getFileDialogScreenController()->getFileName()
			);
			modelEditorScreenController->getView()->getPopUpsViews()->getFileDialogScreenController()->close();
		}
	private:
		ModelEditorScreenController* modelEditorScreenController;
	};

	auto animationName = animationsDropDown->getController()->getValue().getString();
	auto animationSound = view->getEntity()->getModelSettings()->getAnimationSound(animationName);

	vector<string> extensions = {{"ogg"}};
	view->getPopUpsViews()->getFileDialogScreenController()->show(
		animationSound != nullptr && animationSound->getFileName().length() > 0?Tools::getPath(animationSound->getFileName()):audioPath->getPath(),
		"Load from: ",
		extensions,
		animationSound != nullptr && animationSound->getFileName().length() > 0?Tools::getFileName(animationSound->getFileName()):"",
		new LoadSoundAction(this)
	);

}

void ModelEditorScreenController::onAnimationSoundApply() {
	auto animationName = animationsDropDown->getController()->getValue().getString();
	auto animationSound = view->getEntity()->getModelSettings()->getAnimationSound(animationName);
	try {
		animationSound->setFileName(animationsAnimationSoundFile->getController()->getValue().getString());
		animationSound->setGain(Float::parseFloat(animationsAnimationSoundGain->getController()->getValue().getString()));
		animationSound->setPitch(Float::parseFloat(animationsAnimationSoundPitch->getController()->getValue().getString()));
		animationSound->setOffset(Integer::parseInt(animationsAnimationSoundOffset->getController()->getValue().getString()));
		animationSound->setLooping(animationsAnimationSoundLooping->getController()->getValue().getString() == "1");
		animationSound->setFixed(animationsAnimationSoundFixed->getController()->getValue().getString() == "1");
		view->playAnimation(animationSound->getAnimation());
	} catch (Exception& exception) {
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void ModelEditorScreenController::unsetAnimations() {

	dynamic_cast<GUIParentNode*>(animationsDropDown->getScreenNode()->getNodeById(animationsDropDown->getId() + "_inner"))->clearSubNodes();
	animationsDropDown->getController()->setValue(MutableString(""));
	animationsDropDown->getController()->setDisabled(true);
	animationsDropDownApply->getController()->setDisabled(true);
	animationsDropDownDelete->getController()->setDisabled(true);
	animationsAnimationStartFrame->getController()->setValue(MutableString(""));
	animationsAnimationStartFrame->getController()->setDisabled(true);
	animationsAnimationEndFrame->getController()->setValue(MutableString(""));
	animationsAnimationEndFrame->getController()->setDisabled(true);
	animationsAnimationOverlayFromGroupIdDropDown->getController()->setValue(MutableString(""));
	animationsAnimationOverlayFromGroupIdDropDown->getController()->setDisabled(true);
	animationsAnimationLoop->getController()->setValue(MutableString(""));
	animationsAnimationLoop->getController()->setDisabled(true);
	animationsAnimationName->getController()->setValue(MutableString(""));
	animationsAnimationName->getController()->setDisabled(true);
	animationsAnimationApply->getController()->setDisabled(true);
	unsetAnimationSound();
}


void ModelEditorScreenController::unsetAnimationSound() {
	animationsAnimationSoundFile->getController()->setValue(MutableString(""));
	animationsAnimationSoundFile->getController()->setDisabled(true);
	animationsAnimationSoundLoad->getController()->setDisabled(true);
	animationsAnimationSoundClear->getController()->setDisabled(true);
	animationsAnimationSoundGain->getController()->setValue(MutableString(""));
	animationsAnimationSoundGain->getController()->setDisabled(true);
	animationsAnimationSoundPitch->getController()->setValue(MutableString(""));
	animationsAnimationSoundPitch->getController()->setDisabled(true);
	animationsAnimationSoundOffset->getController()->setValue(MutableString(""));
	animationsAnimationSoundOffset->getController()->setDisabled(true);
	animationsAnimationSoundLooping->getController()->setValue(MutableString(""));
	animationsAnimationSoundLooping->getController()->setDisabled(true);
	animationsAnimationSoundFixed->getController()->setValue(MutableString(""));
	animationsAnimationSoundFixed->getController()->setDisabled(true);
	animationsAnimationSoundApply->getController()->setDisabled(true);
}


void ModelEditorScreenController::setStatistics(int32_t statsOpaqueFaces, int32_t statsTransparentFaces, int32_t statsMaterialCount)
{
	this->statsOpaqueFaces->getController()->setValue(MutableString(statsOpaqueFaces));
	this->statsTransparentFaces->getController()->setValue(MutableString(statsTransparentFaces));
	this->statsMaterialCount->getController()->setValue(MutableString(statsMaterialCount));
}

void ModelEditorScreenController::unsetStatistics()
{
	this->statsOpaqueFaces->getController()->setValue(MutableString());
	this->statsTransparentFaces->getController()->setValue(MutableString());
	this->statsMaterialCount->getController()->setValue(MutableString());
}

void ModelEditorScreenController::setTools() {
	buttonToolsComputeNormals->getController()->setDisabled(false);
}

void ModelEditorScreenController::unsetTools() {
	buttonToolsComputeNormals->getController()->setDisabled(true);
}

void ModelEditorScreenController::onToolsComputeNormal() {
	view->computeNormals();
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
		extensions,
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
		extensions,
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
		auto x = Float::parseFloat(pivotX->getController()->getValue().getString());
		auto y = Float::parseFloat(pivotY->getController()->getValue().getString());
		auto z = Float::parseFloat(pivotZ->getController()->getValue().getString());
		view->pivotApply(x, y, z);
	} catch (Exception& exception) {
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void ModelEditorScreenController::onRenderingApply()
{
	if (view->getEntity() == nullptr) return;
	try {
		view->getEntity()->setDynamicShadowing(renderingDynamicShadowing->getController()->getValue().equals("1"));
		view->getEntity()->setRenderGroups(renderingRenderGroups->getController()->getValue().equals("1"));
		view->getEntity()->setShader(renderingShader->getController()->getValue().getString());
		view->getEntity()->setDistanceShader(renderingDistanceShader->getController()->getValue().getString());
		view->getEntity()->setDistanceShaderDistance(Float::parseFloat(renderingDistanceShaderDistance->getController()->getValue().getString()));
	} catch (Exception& exception) {
		showErrorPopUp("Warning", (string(exception.what())));
	}
	view->updateRendering();
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
		entityPhysicsSubScreenController->onValueChanged(node, view->getEntity());
	}
}

void ModelEditorScreenController::onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node)
{
	entityBaseSubScreenController->onActionPerformed(type, node, view->getEntity());
	entityDisplaySubScreenController->onActionPerformed(type, node);
	entityPhysicsSubScreenController->onActionPerformed(type, node, view->getEntity());
	{
		auto v = type;
		if (v == GUIActionListener_Type::PERFORMED) {
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
			if (node->getId().compare("lod_level_apply") == 0) {
				onLODLevelApply();
			} else
			if (node->getId().compare("lod_model_file_load") == 0) {
				onLODLevelLoadModel();
			} else
			if (node->getId().compare("lod_model_file_clear") == 0) {
				onLODLevelClearModel();
			} else
			if (node->getId().compare("button_lod_apply") == 0) {
				onLODLevelApplySettings();
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
			if (node->getId().compare("button_animations_animation_apply") == 0) {
				onAnimationApply();
			} else
			if (node->getId().compare("animations_animation_sound_clear") == 0) {
				onAnimationSoundClear();
			} else
			if (node->getId().compare("animations_animation_sound_load") == 0) {
				onAnimationSoundLoad();
			} else
			if (node->getId().compare("button_animations_sound_apply") == 0) {
				onAnimationSoundApply();
			} else
			if (node->getId().compare("button_tools_computenormals") == 0) {
				onToolsComputeNormal();
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
		}
	}

}
