#include <tdme/tools/editor/tabcontrollers/ModelEditorTabController.h>

#include <string>
#include <vector>

#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/model/AnimationSetup.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/model/PBRMaterialProperties.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/PrototypeLODLevel.h>
#include <tdme/engine/prototype/PrototypeProperty.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/events/Action.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIImageNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/nodes/GUITextureNode.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/misc/FileDialogPath.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeBaseSubController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeDisplaySubController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypePhysicsSubController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypeSoundsSubController.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/tabviews/ModelEditorTabView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using std::string;
using std::vector;

using tdme::tools::editor::tabcontrollers::ModelEditorTabController;

using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::model::AnimationSetup;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::model::PBRMaterialProperties;
using tdme::engine::model::SpecularMaterialProperties;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeLODLevel;
using tdme::engine::prototype::PrototypeProperty;
using tdme::gui::events::Action;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIImageNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::nodes::GUITextureNode;
using tdme::gui::GUIParser;
using tdme::math::Vector3;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::misc::FileDialogPath;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeBaseSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeDisplaySubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeSoundsSubController;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::ModelEditorTabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;
using tdme::utilities::Float;
using tdme::utilities::Integer;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

ModelEditorTabController::ModelEditorTabController(ModelEditorTabView* view)
{
	class OnSetPrototypeDataAction: public virtual Action
	{
	public:
		void performAction() override {
			finalView->updateGUIElements();
			finalView->onSetPrototypeData();
		}

		/**
		 * Public constructor
		 * @param ModelEditorTabController model editor tab controller
		 * @param finalView final view
		 */
		OnSetPrototypeDataAction(ModelEditorTabController* modelEditorTabController, ModelEditorTabView* finalView)
			: modelEditorTabController(modelEditorTabController)
			, finalView(finalView) {
		}


	private:
		ModelEditorTabController* modelEditorTabController;
		ModelEditorTabView* finalView;
	};

	this->view = view;
	auto const finalView = view;
	this->prototypeBaseSubController = new PrototypeBaseSubController(view->getEditorView(), new OnSetPrototypeDataAction(this, finalView));
	this->prototypePhysicsSubController = new PrototypePhysicsSubController(view->getEditorView(), view->getEngine(), &modelPath, true);
	this->prototypeSoundsSubController = new PrototypeSoundsSubController(view->getEditorView(), view, &audioPath);
	this->prototypeDisplaySubController = new PrototypeDisplaySubController(view->getEditorView(), view, view->getEngine(), this->prototypePhysicsSubController->getView());
}

ModelEditorTabController::~ModelEditorTabController() {
	delete prototypeBaseSubController;
	delete prototypeDisplaySubController;
	delete prototypePhysicsSubController;
}

ModelEditorTabView* ModelEditorTabController::getView() {
	return view;
}

PrototypeDisplaySubController* ModelEditorTabController::getPrototypeDisplaySubController()
{
	return prototypeDisplaySubController;
}

PrototypePhysicsSubController* ModelEditorTabController::getPrototypePhysicsSubController()
{
	return prototypePhysicsSubController;
}

PrototypeSoundsSubController* ModelEditorTabController::getPrototypeSoundsSubController()
{
	return prototypeSoundsSubController;
}

GUIScreenNode* ModelEditorTabController::getScreenNode()
{
	return screenNode;
}

FileDialogPath* ModelEditorTabController::getModelPath()
{
	return &modelPath;
}

FileDialogPath* ModelEditorTabController::getAudioPath()
{
	return &audioPath;
}

void ModelEditorTabController::initialize(GUIScreenNode* screenNode)
{
	try {
		screenNode = GUIParser::parse("resources/engine/gui", "screen_modeleditor.xml");
		screenNode->addActionListener(this);
		screenNode->addChangeListener(this);
		screenCaption = dynamic_cast< GUITextNode* >(screenNode->getNodeById("screen_caption"));
		modelReload = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_model_reload"));
		modelReimport = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_model_reimport"));
		modelSave = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_model_save"));
		pivotX = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("pivot_x"));
		pivotY = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("pivot_y"));
		pivotZ = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("pivot_z"));
		pivotApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_pivot_apply"));
		renderingContributesShadows = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("rendering_contributes_shadows"));
		renderingReceivesShadows = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("rendering_receives_shadows"));
		renderingRenderGroups = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("rendering_render_groups"));
		renderingShader = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("rendering_shader"));
		renderingDistanceShader = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("rendering_distance_shader"));
		renderingDistanceShaderDistance = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("rendering_distance_shader_distance"));
		renderingApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_rendering_apply"));
		shaderParametersContent = dynamic_cast< GUIParentNode* >(screenNode->getNodeById("shaderparameters_content"));
		lodLevel = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("lod_level"));
		lodLevelApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("lod_level_apply"));
		lodType = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("lod_type"));
		lodModelFile = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("lod_model_file"));
		lodModelFileLoad = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("lod_model_file_load"));
		lodModelFileClear = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("lod_model_file_clear"));
		lodMinDistance = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("lod_min_distance"));
		lodColorMul = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("lod_color_mul"));
		lodColorAdd = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("lod_color_add"));
		buttonLodApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_lod_apply"));
		materialsDropdown = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_dropdown"));
		materialsDropdownApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_materials_dropdown_apply"));
		materialsMaterialName = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_name"));
		materialsMaterialDoubleSided = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_double_sided"));
		materialsMaterialAmbient = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_ambient"));
		materialsMaterialDiffuse = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_diffuse"));
		materialsMaterialSpecular= dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_specular"));
		materialsMaterialEmission = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_emission"));
		materialsMaterialShininess = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_shininess"));
		materialsMaterialReflection = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_reflection"));
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
		materialsMaterialPBREnabled = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_pbr_enabled"));
		materialsMaterialPBRBaseColorFactor = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_pbr_base_color_factor"));
		materialsMaterialPBRBaseColorTexture = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_pbr_base_color_texture"));
		materialsMaterialPBRBaseColorTextureLoad = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_materials_material_pbr_base_color_texture_load"));
		materialsMaterialPBRBaseColorTextureClear = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_materials_material_pbr_base_color_texture_clear"));
		materialsMaterialPBRMetallicFactor = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_pbr_metallic_factor"));
		materialsMaterialPBRRoughnessFactor = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_pbr_roughness_factor"));
		materialsMaterialPBRMetallicRoughnessTexture = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_pbr_metallic_roughness_texture"));
		materialsMaterialPBRMetallicRoughnessTextureLoad = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_materials_material_pbr_metallic_roughness_texture_load"));
		materialsMaterialPBRMetallicRoughnessTextureClear = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_materials_material_pbr_metallic_roughness_texture_clear"));
		materialsMaterialPBRNormalScale = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_pbr_normal_scale"));
		materialsMaterialPBRNormalTexture = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_pbr_normal_texture"));
		materialsMaterialPBRNormalTextureLoad = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_materials_material_pbr_normal_texture_load"));
		materialsMaterialPBRNormalTextureClear = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_materials_material_pbr_normal_texture_clear"));
		materialsMaterialPBRExposure = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_pbr_exposure"));
		materialsMaterialUseMaskedTransparency = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_use_masked_transparency"));;
		materialsMaterialMaskedTransparencyThreshold = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("materials_material_masked_transparency_threshold"));;
		materialsMaterialApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_materials_material_apply"));
		animationsDropDown = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("animations_dropdown"));
		animationsDropDownApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("animations_dropdown_apply"));
		animationsDropDownDelete = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("animations_dropdown_delete"));
		animationsAnimationStartFrame = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("animations_animation_startframe"));
		animationsAnimationEndFrame = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("animations_animation_endframe"));
		animationsAnimationOverlayFromNodeIdDropDown = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("animations_animation_overlayfromnodeidanimations_dropdown"));
		animationsAnimationLoop = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("animations_animation_loop"));
		animationsAnimationSpeed = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("animations_animation_speed"));
		animationsAnimationName = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("animations_animation_name"));
		animationsAnimationApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_animations_animation_apply"));
		previewAnimationsBaseDropDown = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("preview_animations_base_dropdown"));
		previewAnimationsOverlay1DropDown = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("preview_animations_overlay1_dropdown"));
		previewAnimationsOverlay2DropDown = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("preview_animations_overlay2_dropdown"));
		previewAnimationsOverlay3DropDown = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("preview_animations_overlay3_dropdown"));
		previewAnimationsAttachment1BoneDropdown = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("preview_animations_attachment1_bone_dropdown"));
		previewAnimationsAttachment1ModelModel = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("preview_animations_attachment1_model_model"));
		previewAnimationsAttachment1ModelLoad = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("preview_animations_attachment1_model_load"));
		previewAnimationsAttachment1ModelClear = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("preview_animations_attachment1_model_clear"));
		buttonPreviewApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_preview_apply"));
		statsOpaqueFaces = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("stats_opaque_faces"));
		buttonToolsComputeNormals = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_tools_computenormals"));
		buttonToolsOptimizeModel = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_tools_optimizemodel"));
		statsTransparentFaces = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("stats_transparent_faces"));
		statsMaterialCount = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("stats_material_count"));
		viewPort = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("viewport"));
		statsOpaqueFaces->getController()->setDisabled(true);
		statsTransparentFaces->getController()->setDisabled(true);
		statsMaterialCount->getController()->setDisabled(true);
	} catch (Exception& exception) {
		Console::print(string("ModelEditorTabController::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	prototypeBaseSubController->initialize(screenNode);
	prototypeDisplaySubController->initialize(screenNode);
	prototypePhysicsSubController->initialize(screenNode);
	prototypeSoundsSubController->initialize(screenNode);
}

void ModelEditorTabController::dispose()
{
}

void ModelEditorTabController::setScreenCaption(const string& text)
{
	screenCaption->setText(text);
}

void ModelEditorTabController::createOutlinerModelNodesXML(const map<string, Node*>& subNodes, string& xml) {
	for (auto nodeIt: subNodes) {
		auto node = nodeIt.second;
		if (node->getSubNodes().empty() == false) {
			xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes(node->getId()) + "\" value=\"" + GUIParser::escapeQuotes("model.nodes." + node->getId()) + "\">\n";
			createOutlinerModelNodesXML(node->getSubNodes(), xml);
			xml+= "</selectbox-parent-option>\n";
		} else {
			xml+= "	<selectbox-option text=\"" + GUIParser::escapeQuotes(node->getId()) + "\" value=\"" + GUIParser::escapeQuotes("model.nodes." + node->getId()) + "\" />\n";
		}
	}
}

void ModelEditorTabController::setOutlinerContent() {

	string xml;
	xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Prototype") + "\" value=\"" + GUIParser::escapeQuotes("prototype") + "\">\n";
	auto prototype = view->getPrototype();
	if (prototype != nullptr) {
		prototypeBaseSubController->createPrototypePropertiesXML(prototype, xml);
		prototypeDisplaySubController->createDisplayPropertiesXML(prototype, xml);
		prototypePhysicsSubController->createOutlinerPhysicsXML(prototype, xml);
		prototypeSoundsSubController->createOutlinerSoundsXML(prototype, xml);
		Model* model = view->getLodLevel() == 1?prototype->getModel():getLODLevel(view->getLodLevel())->getModel();
		xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Model") + "\" value=\"" + GUIParser::escapeQuotes("model") + "\">\n";
		if (model != nullptr) {
			xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Materials") + "\" value=\"" + GUIParser::escapeQuotes("model.materials") + "\">\n";
			for (auto it: model->getMaterials()) {
				auto materialId = it.second->getId();
				xml+= "	<selectbox-option text=\"" + GUIParser::escapeQuotes(materialId) + "\" value=\"" + GUIParser::escapeQuotes("model.material." + materialId) + "\" />\n";
			}
			xml+= "</selectbox-parent-option>\n";
		}
		if (model != nullptr && model->getSubNodes().empty() == false) {
			xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Nodes") + "\" value=\"" + GUIParser::escapeQuotes("model.nodes") + "\">\n";
			createOutlinerModelNodesXML(model->getSubNodes(), xml);
			xml+= "</selectbox-parent-option>\n";
		}
		if (model != nullptr &&
			(model->getAnimationSetups().size() > 1 || model->getAnimationSetup(Model::ANIMATIONSETUP_DEFAULT) == nullptr)) {
			xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Animations") + "\" value=\"" + GUIParser::escapeQuotes("model.animations") + "\">\n";
			for (auto it: model->getAnimationSetups()) {
				auto animationSetupId = it.second->getId();
				if (animationSetupId == Model::ANIMATIONSETUP_DEFAULT) continue;
				xml+= "	<selectbox-option text=\"" + GUIParser::escapeQuotes(animationSetupId) + "\" value=\"" + GUIParser::escapeQuotes("model.animations." + animationSetupId) + "\" />\n";
			}
			xml+= "</selectbox-parent-option>\n";
		}
		xml+= "</selectbox-parent-option>\n";
	}
	xml+= "</selectbox-parent-option>\n";
	view->getEditorView()->setOutlinerContent(xml);
}

void ModelEditorTabController::setDetailsContent() {
	view->getEditorView()->setDetailsContent(string());
}

void ModelEditorTabController::setPrototypeData(const string& name, const string& description)
{
	prototypeBaseSubController->setPrototypeData(name, description);
	modelReload->getController()->setDisabled(false);
	modelReimport->getController()->setDisabled(false);
	modelSave->getController()->setDisabled(false);
}

void ModelEditorTabController::unsetPrototypeData()
{
	prototypeBaseSubController->unsetPrototypeData();
	modelReload->getController()->setDisabled(true);
	modelReimport->getController()->setDisabled(true);
	modelSave->getController()->setDisabled(true);
}

void ModelEditorTabController::setPivot(const Vector3& pivot)
{
	pivotX->getController()->setDisabled(false);
	pivotX->getController()->setValue(MutableString(Tools::formatFloat(pivot.getX())));
	pivotY->getController()->setDisabled(false);
	pivotY->getController()->setValue(MutableString(Tools::formatFloat(pivot.getY())));
	pivotZ->getController()->setDisabled(false);
	pivotZ->getController()->setValue(MutableString(Tools::formatFloat(pivot.getZ())));
	pivotApply->getController()->setDisabled(false);
}

void ModelEditorTabController::unsetPivot()
{
	pivotX->getController()->setDisabled(true);
	pivotX->getController()->setValue(MutableString());
	pivotY->getController()->setDisabled(true);
	pivotY->getController()->setValue(MutableString());
	pivotZ->getController()->setDisabled(true);
	pivotZ->getController()->setValue(MutableString());
	pivotApply->getController()->setDisabled(true);
}

void ModelEditorTabController::setRenderingShaders(const vector<string>& shaders) {
	auto idx = 1;
	string renderingShadersDropDownSubNodesXML = "";
	for (auto shader: shaders) {
		renderingShadersDropDownSubNodesXML =
			renderingShadersDropDownSubNodesXML +
			"<dropdown-option text=\"" +
			GUIParser::escapeQuotes(shader) +
			"\" value=\"" +
			GUIParser::escapeQuotes(shader) +
			"\" " +
			(shader == "default"?"selected=\"true\" " : "") +
			"/>\n";
	}
	try {
		dynamic_cast< GUIParentNode* >((renderingShader->getScreenNode()->getNodeById(renderingShader->getId() + "_inner")))->replaceSubNodes(
			"<scrollarea id=\"" +
				renderingShader->getId() +
				"_inner_scrollarea\" width=\"100%\" height=\"150\">\n" +
				renderingShadersDropDownSubNodesXML +
				"</scrollarea>\n",
			false
		);
		dynamic_cast< GUIParentNode* >((renderingShader->getScreenNode()->getNodeById(renderingDistanceShader->getId() + "_inner")))->replaceSubNodes(
			"<scrollarea id=\"" +
				renderingDistanceShader->getId() +
				"_inner_scrollarea\" width=\"100%\" height=\"150\">\n" +
				renderingShadersDropDownSubNodesXML +
				"</scrollarea>\n",
			false
		);
	} catch (Exception& exception) {
		Console::print(string("ModelEditorTabController::setRenderingShaders(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void ModelEditorTabController::setRendering()
{
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;
	renderingContributesShadows->getController()->setDisabled(false);
	renderingContributesShadows->getController()->setValue(MutableString(prototype->isContributesShadows() == true?"1":""));
	renderingReceivesShadows->getController()->setDisabled(false);
	renderingReceivesShadows->getController()->setValue(MutableString(prototype->isReceivesShadows() == true?"1":""));
	renderingRenderGroups->getController()->setDisabled(false);
	renderingRenderGroups->getController()->setValue(MutableString(prototype->isRenderGroups() == true?"1":""));
	renderingShader->getController()->setDisabled(false);
	renderingShader->getController()->setValue(MutableString(prototype->getShader()));
	renderingDistanceShader->getController()->setDisabled(false);
	renderingDistanceShader->getController()->setValue(MutableString(prototype->getDistanceShader()));
	renderingDistanceShaderDistance->getController()->setDisabled(false);
	renderingDistanceShaderDistance->getController()->setValue(MutableString(prototype->getDistanceShaderDistance(), 4));
	renderingApply->getController()->setDisabled(false);

	// shader parameters
	setShaderParameters();
}

void ModelEditorTabController::unsetRendering()
{
	renderingContributesShadows->getController()->setDisabled(true);
	renderingContributesShadows->getController()->setValue(MutableString("1"));
	renderingReceivesShadows->getController()->setDisabled(true);
	renderingReceivesShadows->getController()->setValue(MutableString("1"));
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

void ModelEditorTabController::setShaderParameters() {
	unsetShaderParameters();

	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;

	auto shaderParameters = Engine::getShaderParameterDefaults(view->getPrototype()->getShader());
	auto distanceShaderParameters = Engine::getShaderParameterDefaults(view->getPrototype()->getDistanceShader());
	string shadersParametersContentSubNodesXML = "";
	if (shaderParameters.empty() == false) {
		shadersParametersContentSubNodesXML+= string("<space height=\"20\" />");
		shadersParametersContentSubNodesXML+= string("<text font=\"{$font.default}\" text=\"'" + prototype->getShader() + "' - Shader\" width=\"auto\" height=\"auto\"/>\n");
		shadersParametersContentSubNodesXML+= string("<space height=\"10\" />");
		for (auto& parameterIt: shaderParameters) {
			auto& parameterName = parameterIt.first;
			auto parameterValue = prototype->getShaderParameters().getShaderParameter(parameterName).toString();
			shadersParametersContentSubNodesXML+=
				string("<layout alignment=\"horizontal\" width=\"auto\" height=\"auto\">\n") +
				string("	<layout width=\"auto\" height=\"auto\" alignment=\"horizontal\" vertical-align=\"center\">\n") +
				string("		<text font=\"{$font.default}\" text=\"'" + GUIParser::escapeQuotes(parameterName) + "'\" width=\"145\" height=\"auto\"/>\n") +
				string("		<space width=\"5\" />\n") +
				string("		<input id=\"shaderparameters_" + GUIParser::escapeQuotes(parameterName) + "\" name=\"shaderparameters_" + GUIParser::escapeQuotes(parameterName) + "\" width=\"450\" height=\"auto\" text=\"" + GUIParser::escapeQuotes(parameterValue) + "\" disabled=\"false\" />\n") +
				string("	</layout>\n") +
				string("</layout>\n");
		}
	}

	if (distanceShaderParameters.empty() == false) {
		shadersParametersContentSubNodesXML+= string("<space height=\"20\" />");
		shadersParametersContentSubNodesXML+= string("<text font=\"{$font.default}\" text=\"'" + prototype->getDistanceShader() + "' - Distance Shader\" width=\"auto\" height=\"auto\"/>\n");
		shadersParametersContentSubNodesXML+= string("<space height=\"10\" />");
		for (auto& parameterIt: distanceShaderParameters) {
			auto& parameterName = parameterIt.first;
			auto parameterValue = prototype->getDistanceShaderParameters().getShaderParameter(parameterName).toString();
			shadersParametersContentSubNodesXML+=
				string("<layout alignment=\"horizontal\" width=\"auto\" height=\"auto\">\n") +
				string("	<layout width=\"auto\" height=\"auto\" alignment=\"horizontal\" vertical-align=\"center\">\n") +
				string("		<text font=\"{$font.default}\" text=\"'" + GUIParser::escapeQuotes(parameterName) + "'\" width=\"145\" height=\"auto\"/>\n") +
				string("		<space width=\"5\" />\n") +
				string("		<input id=\"shaderparameters_distance_" + GUIParser::escapeQuotes(parameterName) + "\" name=\"shaderparameters_distance_" + GUIParser::escapeQuotes(parameterName) + "\" width=\"450\" height=\"auto\" text=\"" + GUIParser::escapeQuotes(parameterValue) + "\" disabled=\"false\" />\n") +
				string("	</layout>\n") +
				string("</layout>\n");
		}
	}

	if (shaderParameters.empty() == false || distanceShaderParameters.empty() == false) {
		shadersParametersContentSubNodesXML+=
			string("<space height=\"20\" />\n") +
			string("<layout width=\"100%\" height=\"auto\" alignment=\"none\" horizontal-align=\"center\">\n") +
			string("	<button id=\"button_shaderparameters_apply\" name=\"button_shaderparameters_apply\" text=\"Apply\" width=\"auto\" height=\"auto\" />\n") +
			string("</layout>\n") +
			string("<space height=\"20\" />\n");
	}

	if (shadersParametersContentSubNodesXML.empty() == true) {
		shadersParametersContentSubNodesXML+=
			string("<space height=\"20\" />\n") +
			string("<text font=\"{$font.default}\" text=\"No shader parameters available\" width=\"auto\" height=\"auto\"/>\n") +
			string("<space height=\"20\" />\n");
	}

	try {
		shaderParametersContent->replaceSubNodes(
			shadersParametersContentSubNodesXML,
			false
		);
	} catch (Exception& exception) {
		Console::print(string("ModelEditorTabController::setRenderingShaders(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void ModelEditorTabController::unsetShaderParameters() {
	shaderParametersContent->clearSubNodes();
}

PrototypeLODLevel* ModelEditorTabController::getLODLevel(int level) {
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return nullptr;
	switch(level) {
		case 2:
			{
				auto prototypeLodLevel = prototype->getLODLevel2();
				if (prototypeLodLevel == nullptr) {
					prototypeLodLevel = new PrototypeLODLevel(
						LODObject3D::LODLEVELTYPE_NONE,
						"",
						nullptr,
						0.0f
					);
					prototype->setLODLevel2(prototypeLodLevel);
				}
				return prototypeLodLevel;
			}
		case 3:
			{
				auto prototypeLodLevel = prototype->getLODLevel3();
				if (prototypeLodLevel == nullptr) {
					prototypeLodLevel = new PrototypeLODLevel(
						LODObject3D::LODLEVELTYPE_NONE,
						"",
						nullptr,
						0.0f
					);
					prototype->setLODLevel3(prototypeLodLevel);
				}
				return prototypeLodLevel;
			}
		default:
			{
				return nullptr;
			}
	}
}

void ModelEditorTabController::setLODLevel(int level) {
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;

	auto prototypeLodLevel = getLODLevel(level);
	if (prototypeLodLevel == nullptr) {
		lodLevel->getController()->setValue(MutableString(to_string(level)));
		lodLevel->getController()->setDisabled(false);
		lodLevelApply->getController()->setDisabled(false);
		lodType->getController()->setValue(MutableString("1"));
		lodType->getController()->setDisabled(true);
		lodModelFile->getController()->setValue(MutableString(prototype->getModelFileName()));
		lodModelFile->getController()->setDisabled(true);
		lodModelFileLoad->getController()->setDisabled(true);
		lodModelFileClear->getController()->setDisabled(true);
		lodMinDistance->getController()->setValue(MutableString("0.0"));
		lodMinDistance->getController()->setDisabled(true);
		lodColorMul->getController()->setValue(MutableString("1.0, 1.0, 1.0, 1.0"));
		lodColorMul->getController()->setDisabled(true);
		lodColorAdd->getController()->setValue(MutableString("0.0, 0.0, 0.0, 0.0"));
		lodColorAdd->getController()->setDisabled(true);
		buttonLodApply->getController()->setDisabled(true);
	} else {
		lodLevel->getController()->setValue(MutableString(to_string(level)));
		lodLevel->getController()->setDisabled(false);
		lodLevelApply->getController()->setDisabled(false);
		lodType->getController()->setValue(MutableString(to_string(prototypeLodLevel->getType())));
		lodType->getController()->setDisabled(false);
		lodModelFile->getController()->setValue(MutableString(prototypeLodLevel->getFileName()));
		lodModelFile->getController()->setDisabled(false);
		lodModelFileLoad->getController()->setDisabled(false);
		lodModelFileClear->getController()->setDisabled(false);
		lodMinDistance->getController()->setValue(MutableString(prototypeLodLevel->getMinDistance()));
		lodMinDistance->getController()->setDisabled(false);
		lodColorMul->getController()->setValue(MutableString(Tools::formatColor4(prototypeLodLevel->getColorMul())));
		lodColorMul->getController()->setDisabled(false);
		lodColorAdd->getController()->setValue(MutableString(Tools::formatColor4(prototypeLodLevel->getColorAdd())));
		lodColorAdd->getController()->setDisabled(false);
		buttonLodApply->getController()->setDisabled(false);
	}
	view->setLodLevel(level);
}

void ModelEditorTabController::unsetLODLevel() {
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
	lodColorMul->getController()->setValue(MutableString("1.0, 1.0, 1.0, 1.0"));
	lodColorMul->getController()->setDisabled(true);
	lodColorAdd->getController()->setValue(MutableString("0.0, 0.0, 0.0, 0.0"));
	lodColorAdd->getController()->setDisabled(true);
	buttonLodApply->getController()->setDisabled(true);
}

void ModelEditorTabController::onLODLevelApply() {
	auto prototype = view->getPrototype();
	auto lodLevelInt = Tools::convertToIntSilent(lodLevel->getController()->getValue().getString());
	setLODLevel(lodLevelInt);
}

void ModelEditorTabController::onLODLevelLoadModel() {
	class OnLODModelLoad: public virtual Action
	{
	public:
		void performAction() override {
			modelEditorTabController->lodModelFile->getController()->setValue(
				MutableString(
					modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName() +
					"/" +
					modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
				)
			);
			modelEditorTabController->modelPath.setPath(
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName()
			);
			modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param modelEditorTabController model editor tab controller
		 */
		OnLODModelLoad(ModelEditorTabController* modelEditorTabController): modelEditorTabController(modelEditorTabController) {
		}

	private:
		ModelEditorTabController* modelEditorTabController;
	};

	auto lodLevelInt = Tools::convertToIntSilent(lodLevel->getController()->getValue().getString());
	auto prototypeLodLevel = getLODLevel(lodLevelInt);
	if (prototypeLodLevel == nullptr) return;
	auto extensions = ModelReader::getModelExtensions();
	view->getPopUps()->getFileDialogScreenController()->show(
		prototypeLodLevel->getFileName() != ""?Tools::getPathName(prototypeLodLevel->getFileName()):modelPath.getPath(),
		"Load from: ",
		extensions,
		Tools::getFileName(prototypeLodLevel->getFileName()),
		true,
		new OnLODModelLoad(this)
	);
}

void ModelEditorTabController::onLODLevelClearModel() {
	lodModelFile->getController()->setValue(MutableString());
}

void ModelEditorTabController::onLODLevelApplySettings() {
	view->resetPrototype();
	auto lodLevelInt = Tools::convertToIntSilent(lodLevel->getController()->getValue().getString());
	PrototypeLODLevel* prototypeLodLevel = getLODLevel(lodLevelInt);
	try {
		prototypeLodLevel->setType(static_cast<LODObject3D::LODLevelType>(Tools::convertToIntSilent(lodType->getController()->getValue().getString())));
		prototypeLodLevel->setFileName(
			prototypeLodLevel->getType() == LODObject3D::LODLEVELTYPE_MODEL?
				lodModelFile->getController()->getValue().getString():
				""
			);
		prototypeLodLevel->setMinDistance(Tools::convertToFloat(lodMinDistance->getController()->getValue().getString()));
		prototypeLodLevel->setColorMul(Tools::convertToColor4(lodColorMul->getController()->getValue().getString()));
		prototypeLodLevel->setColorAdd(Tools::convertToColor4(lodColorAdd->getController()->getValue().getString()));
		prototypeLodLevel->setModel(
			prototypeLodLevel->getType() == LODObject3D::LODLEVELTYPE_MODEL?
				ModelReader::read(
					Tools::getPathName(prototypeLodLevel->getFileName()),
					Tools::getFileName(prototypeLodLevel->getFileName())
				):
				nullptr
		);
	} catch (Exception& exception) {
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void ModelEditorTabController::setMaterials() {
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;

	Model* model = view->getLodLevel() == 1?prototype->getModel():getLODLevel(view->getLodLevel())->getModel();
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
			"<scrollarea id=\"" +
			materialsDropdown->getId() +
			"_inner_scrollarea\" width=\"100%\" height=\"100\">\n";
		// materialsDropDownInnerNodeSubNodesXML = materialsDropDownInnerNodeSubNodesXML + "<dropdown-option text=\"<New animation>\" value=\"<New animation>\" />";
		for (auto it: model->getMaterials()) {
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
		materialsDropDownInnerNodeSubNodesXML = materialsDropDownInnerNodeSubNodesXML + "</scrollarea>";
		try {
			materialsDropDownInnerNode->replaceSubNodes(materialsDropDownInnerNodeSubNodesXML, true);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorTabController::setMaterials(): An error occurred: "));
			Console::println(string(exception.what()));
		}
	}

	//
	materialsDropdown->getController()->setDisabled(false);
	materialsDropdownApply->getController()->setDisabled(false);
	materialsMaterialDoubleSided->getController()->setDisabled(false);
	materialsMaterialAmbient->getController()->setDisabled(false);
	materialsMaterialDiffuse->getController()->setDisabled(false);
	materialsMaterialSpecular->getController()->setDisabled(false);
	materialsMaterialEmission->getController()->setDisabled(false);
	materialsMaterialShininess->getController()->setDisabled(false);
	materialsMaterialReflection->getController()->setDisabled(false);
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

void ModelEditorTabController::unsetMaterials() {
	{
		auto materialsDropDownInnerNode = dynamic_cast< GUIParentNode* >((materialsDropdown->getScreenNode()->getNodeById(materialsDropdown->getId() + "_inner")));
		auto idx = 0;
		string materialsDropDownInnerNodeSubNodesXML = "";
		materialsDropDownInnerNodeSubNodesXML =
				materialsDropDownInnerNodeSubNodesXML +
			"<scrollarea id=\"" +
			materialsDropdown->getId() +
			"_inner_scrollarea\" width=\"100%\" height=\"100\">\n";
		materialsDropDownInnerNodeSubNodesXML = materialsDropDownInnerNodeSubNodesXML + "<dropdown-option text=\"None\" value=\"\" />";
		materialsDropDownInnerNodeSubNodesXML = materialsDropDownInnerNodeSubNodesXML + "</scrollarea>";
		try {
			materialsDropDownInnerNode->replaceSubNodes(materialsDropDownInnerNodeSubNodesXML, true);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorTabController::setMaterials(): An error occurred: "));
			Console::println(string(exception.what()));
		}
	}

	materialsDropdown->getController()->setValue(MutableString());
	materialsDropdown->getController()->setDisabled(true);
	materialsDropdownApply->getController()->setDisabled(true);
	materialsMaterialName->getController()->setValue(MutableString(""));
	materialsMaterialDoubleSided->getController()->setDisabled(true);
	materialsMaterialDoubleSided->getController()->setValue(MutableString(""));
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
	materialsMaterialReflection->getController()->setDisabled(true);
	materialsMaterialReflection->getController()->setValue(MutableString());
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
	materialsMaterialPBREnabled->getController()->setDisabled(true);
	materialsMaterialPBREnabled->getController()->setValue(MutableString());
	materialsMaterialPBRBaseColorFactor->getController()->setDisabled(true);
	materialsMaterialPBRBaseColorFactor->getController()->setValue(MutableString());
	materialsMaterialPBRBaseColorTexture->getController()->setDisabled(true);
	materialsMaterialPBRBaseColorTexture->getController()->setValue(MutableString());
	materialsMaterialPBRBaseColorTextureLoad->getController()->setDisabled(true);
	materialsMaterialPBRBaseColorTextureClear->getController()->setDisabled(true);
	materialsMaterialPBRMetallicFactor->getController()->setDisabled(true);
	materialsMaterialPBRMetallicFactor->getController()->setValue(MutableString());
	materialsMaterialPBRRoughnessFactor->getController()->setDisabled(true);
	materialsMaterialPBRRoughnessFactor->getController()->setValue(MutableString());
	materialsMaterialPBRMetallicRoughnessTexture->getController()->setDisabled(true);
	materialsMaterialPBRMetallicRoughnessTexture->getController()->setValue(MutableString());
	materialsMaterialPBRMetallicRoughnessTextureLoad->getController()->setDisabled(true);
	materialsMaterialPBRMetallicRoughnessTextureClear->getController()->setDisabled(true);
	materialsMaterialPBRNormalScale->getController()->setDisabled(true);
	materialsMaterialPBRNormalScale->getController()->setValue(MutableString());
	materialsMaterialPBRNormalTexture->getController()->setDisabled(true);
	materialsMaterialPBRNormalTexture->getController()->setValue(MutableString());
	materialsMaterialPBRNormalTextureLoad->getController()->setDisabled(true);
	materialsMaterialPBRNormalTextureClear->getController()->setDisabled(true);
	materialsMaterialPBRExposure->getController()->setDisabled(true);
	materialsMaterialPBRExposure->getController()->setValue(MutableString());
	materialsMaterialUseMaskedTransparency->getController()->setValue(MutableString());
	materialsMaterialUseMaskedTransparency->getController()->setDisabled(true);
	materialsMaterialMaskedTransparencyThreshold->getController()->setValue(MutableString());
	materialsMaterialMaskedTransparencyThreshold->getController()->setDisabled(true);
}

void ModelEditorTabController::onMaterialDropDownApply() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	SpecularMaterialProperties defaultSpecularMaterialProperties;
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties == nullptr) specularMaterialProperties = &defaultSpecularMaterialProperties;
	auto pbrMaterialProperties = material->getPBRMaterialProperties();

	// specular
	materialsMaterialName->getController()->setValue(MutableString(material->getId()));
	materialsMaterialDoubleSided->getController()->setValue(MutableString(material->isDoubleSided() == true?"1":""));
	materialsMaterialAmbient->getController()->setValue(MutableString(Tools::formatColor4(specularMaterialProperties->getAmbientColor())));
	materialsMaterialDiffuse->getController()->setValue(MutableString(Tools::formatColor4(specularMaterialProperties->getDiffuseColor())));
	materialsMaterialSpecular->getController()->setValue(MutableString(Tools::formatColor4(specularMaterialProperties->getSpecularColor())));
	materialsMaterialEmission->getController()->setValue(MutableString(Tools::formatColor4(specularMaterialProperties->getEmissionColor())));
	materialsMaterialShininess->getController()->setValue(MutableString(Tools::formatFloat(specularMaterialProperties->getShininess())));
	materialsMaterialReflection->getController()->setValue(MutableString(Tools::formatFloat(specularMaterialProperties->getReflection())));
	materialsMaterialDiffuseTexture->getController()->setValue(
		MutableString(specularMaterialProperties->getDiffuseTexturePathName()).append(specularMaterialProperties->getDiffuseTexturePathName() == ""?"":"/").append(specularMaterialProperties->getDiffuseTextureFileName())
	);
	materialsMaterialDiffuseTransparencyTexture->getController()->setValue(
		MutableString(specularMaterialProperties->getDiffuseTransparencyTexturePathName()).append(specularMaterialProperties->getDiffuseTransparencyTexturePathName() == ""?"":"/").append(specularMaterialProperties->getDiffuseTransparencyTextureFileName())
	);
	materialsMaterialNormalTexture->getController()->setValue(
		MutableString(specularMaterialProperties->getNormalTexturePathName()).append(specularMaterialProperties->getNormalTexturePathName() == ""?"":"/").append(specularMaterialProperties->getNormalTextureFileName())
	);
	materialsMaterialSpecularTexture->getController()->setValue(
		MutableString(specularMaterialProperties->getSpecularTexturePathName()).append(specularMaterialProperties->getSpecularTexturePathName() == ""?"":"/").append(specularMaterialProperties->getSpecularTextureFileName())
	);

	// pbr
	materialsMaterialPBREnabled->getController()->setDisabled(false);
	materialsMaterialPBREnabled->getController()->setValue(MutableString(pbrMaterialProperties != nullptr?"1":""));
	if (pbrMaterialProperties != nullptr) {
		materialsMaterialPBRBaseColorFactor->getController()->setDisabled(false);
		materialsMaterialPBRBaseColorFactor->getController()->setValue(MutableString(Tools::formatColor4(pbrMaterialProperties->getBaseColorFactor())));
		materialsMaterialPBRBaseColorTexture->getController()->setDisabled(false);
		materialsMaterialPBRBaseColorTexture->getController()->setValue(
			MutableString(
				pbrMaterialProperties->getBaseColorTexturePathName()).append(pbrMaterialProperties->getBaseColorTexturePathName() == ""?"":"/").append(pbrMaterialProperties->getBaseColorTextureFileName()
			)
		);
		materialsMaterialPBRBaseColorTextureLoad->getController()->setDisabled(false);
		materialsMaterialPBRBaseColorTextureClear->getController()->setDisabled(false);
		materialsMaterialPBRMetallicFactor->getController()->setDisabled(false);
		materialsMaterialPBRMetallicFactor->getController()->setValue(MutableString(Tools::formatFloat(pbrMaterialProperties->getMetallicFactor())));
		materialsMaterialPBRRoughnessFactor->getController()->setDisabled(false);
		materialsMaterialPBRRoughnessFactor->getController()->setValue(MutableString(Tools::formatFloat(pbrMaterialProperties->getRoughnessFactor())));
		materialsMaterialPBRMetallicRoughnessTexture->getController()->setDisabled(false);
		materialsMaterialPBRMetallicRoughnessTexture->getController()->setValue(
			MutableString(
				pbrMaterialProperties->getMetallicRoughnessTexturePathName()).append(pbrMaterialProperties->getMetallicRoughnessTexturePathName() == ""?"":"/").append(pbrMaterialProperties->getMetallicRoughnessTextureFileName()
			)
		);
		materialsMaterialPBRMetallicRoughnessTextureLoad->getController()->setDisabled(false);
		materialsMaterialPBRMetallicRoughnessTextureClear->getController()->setDisabled(false);
		materialsMaterialPBRNormalScale->getController()->setDisabled(false);
		materialsMaterialPBRNormalScale->getController()->setValue(MutableString(Tools::formatFloat(pbrMaterialProperties->getNormalScale())));
		materialsMaterialPBRNormalTexture->getController()->setDisabled(false);
		materialsMaterialPBRNormalTexture->getController()->setValue(
			MutableString(
				pbrMaterialProperties->getNormalTexturePathName()).append(pbrMaterialProperties->getNormalTexturePathName() == ""?"":"/").append(pbrMaterialProperties->getNormalTextureFileName()
			)
		);
		materialsMaterialPBRNormalTextureLoad->getController()->setDisabled(false);
		materialsMaterialPBRNormalTextureClear->getController()->setDisabled(false);
		materialsMaterialPBRExposure->getController()->setDisabled(false);
		materialsMaterialPBRExposure->getController()->setValue(MutableString(Tools::formatFloat(pbrMaterialProperties->getExposure())));
	} else {
		materialsMaterialPBRBaseColorFactor->getController()->setDisabled(true);
		materialsMaterialPBRBaseColorFactor->getController()->setValue(MutableString());
		materialsMaterialPBRBaseColorTexture->getController()->setDisabled(true);
		materialsMaterialPBRBaseColorTexture->getController()->setValue(MutableString());
		materialsMaterialPBRBaseColorTextureLoad->getController()->setDisabled(true);
		materialsMaterialPBRBaseColorTextureClear->getController()->setDisabled(true);
		materialsMaterialPBRMetallicFactor->getController()->setDisabled(true);
		materialsMaterialPBRMetallicFactor->getController()->setValue(MutableString());
		materialsMaterialPBRRoughnessFactor->getController()->setDisabled(true);
		materialsMaterialPBRRoughnessFactor->getController()->setValue(MutableString());
		materialsMaterialPBRMetallicRoughnessTexture->getController()->setDisabled(true);
		materialsMaterialPBRMetallicRoughnessTexture->getController()->setValue(MutableString());
		materialsMaterialPBRMetallicRoughnessTextureLoad->getController()->setDisabled(true);
		materialsMaterialPBRMetallicRoughnessTextureClear->getController()->setDisabled(true);
		materialsMaterialPBRNormalScale->getController()->setDisabled(true);
		materialsMaterialPBRNormalScale->getController()->setValue(MutableString());
		materialsMaterialPBRNormalTexture->getController()->setDisabled(true);
		materialsMaterialPBRNormalTexture->getController()->setValue(MutableString());
		materialsMaterialPBRNormalTextureLoad->getController()->setDisabled(true);
		materialsMaterialPBRNormalTextureClear->getController()->setDisabled(true);
		materialsMaterialPBRExposure->getController()->setDisabled(false);
		materialsMaterialPBRExposure->getController()->setValue(MutableString());
	}

	//
	materialsMaterialUseMaskedTransparency->getController()->setValue(MutableString(specularMaterialProperties->hasDiffuseTextureMaskedTransparency() == true || (pbrMaterialProperties != nullptr && pbrMaterialProperties->hasBaseColorTextureMaskedTransparency() == true)?"1":""));
	materialsMaterialMaskedTransparencyThreshold->getController()->setValue(MutableString(Tools::formatFloat(specularMaterialProperties->getDiffuseTextureMaskedTransparencyThreshold())));
}

Material* ModelEditorTabController::getSelectedMaterial() {
	string materialId;
	auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
	if (StringTools::startsWith(outlinerNode, "model.material.") == true) {
		materialId = StringTools::substring(outlinerNode, string("model.material.").size(), outlinerNode.size());
	} else {
		return nullptr;
	}
	Model* model = view->getLodLevel() == 1?view->getPrototype()->getModel():getLODLevel(view->getLodLevel())->getModel();
	if (model == nullptr) return nullptr;
	auto materialIt = model->getMaterials().find(materialId);
	return materialIt != model->getMaterials().end()?materialIt->second:nullptr;
}

void ModelEditorTabController::onMaterialApply() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties == nullptr) {
		specularMaterialProperties = new SpecularMaterialProperties();
		material->setSpecularMaterialProperties(specularMaterialProperties);
	}
	auto pbrMaterialProperties =
		materialsMaterialPBREnabled->getController()->getValue().getString() == "1"?
			(material->getPBRMaterialProperties() != nullptr?material->getPBRMaterialProperties():new PBRMaterialProperties()):
			nullptr;
	material->setPBRMaterialProperties(pbrMaterialProperties);
	try {
		view->resetPrototype();
		// specular
		material->setDoubleSided(materialsMaterialDoubleSided->getController()->getValue().getString() == "1");
		specularMaterialProperties->setAmbientColor(Tools::convertToColor4(materialsMaterialAmbient->getController()->getValue().getString()));
		specularMaterialProperties->setDiffuseColor(Tools::convertToColor4(materialsMaterialDiffuse->getController()->getValue().getString()));
		specularMaterialProperties->setSpecularColor(Tools::convertToColor4(materialsMaterialSpecular->getController()->getValue().getString()));
		specularMaterialProperties->setEmissionColor(Tools::convertToColor4(materialsMaterialEmission->getController()->getValue().getString()));
		specularMaterialProperties->setShininess(Tools::convertToFloat(materialsMaterialShininess->getController()->getValue().getString()));
		specularMaterialProperties->setReflection(Tools::convertToFloat(materialsMaterialReflection->getController()->getValue().getString()));
		specularMaterialProperties->setDiffuseTexture(
			Tools::getPathName(materialsMaterialDiffuseTexture->getController()->getValue().getString()),
			Tools::getFileName(materialsMaterialDiffuseTexture->getController()->getValue().getString()),
			Tools::getPathName(materialsMaterialDiffuseTransparencyTexture->getController()->getValue().getString()),
			Tools::getFileName(materialsMaterialDiffuseTransparencyTexture->getController()->getValue().getString())
		);
		specularMaterialProperties->setNormalTexture(
			Tools::getPathName(materialsMaterialNormalTexture->getController()->getValue().getString()),
			Tools::getFileName(materialsMaterialNormalTexture->getController()->getValue().getString())
		);
		specularMaterialProperties->setSpecularTexture(
			Tools::getPathName(materialsMaterialSpecularTexture->getController()->getValue().getString()),
			Tools::getFileName(materialsMaterialSpecularTexture->getController()->getValue().getString())
		);
		specularMaterialProperties->setDiffuseTextureMaskedTransparency(materialsMaterialUseMaskedTransparency->getController()->getValue().getString() == "1"?true:false);
		specularMaterialProperties->setDiffuseTextureMaskedTransparencyThreshold(Tools::convertToFloat(materialsMaterialMaskedTransparencyThreshold->getController()->getValue().getString()));
		// pbr
		if (pbrMaterialProperties != nullptr) {
			pbrMaterialProperties->setBaseColorFactor(Tools::convertToColor4(materialsMaterialPBRBaseColorFactor->getController()->getValue().getString()));
			pbrMaterialProperties->setBaseColorTexture(
				Tools::getPathName(materialsMaterialPBRBaseColorTexture->getController()->getValue().getString()),
				Tools::getFileName(materialsMaterialPBRBaseColorTexture->getController()->getValue().getString())
			);
			pbrMaterialProperties->setMetallicFactor(Tools::convertToFloat(materialsMaterialPBRMetallicFactor->getController()->getValue().getString()));
			pbrMaterialProperties->setRoughnessFactor(Tools::convertToFloat(materialsMaterialPBRRoughnessFactor->getController()->getValue().getString()));
			pbrMaterialProperties->setMetallicRoughnessTexture(
				Tools::getPathName(materialsMaterialPBRMetallicRoughnessTexture->getController()->getValue().getString()),
				Tools::getFileName(materialsMaterialPBRMetallicRoughnessTexture->getController()->getValue().getString())
			);
			pbrMaterialProperties->setNormalScale(Tools::convertToFloat(materialsMaterialPBRNormalScale->getController()->getValue().getString()));
			pbrMaterialProperties->setNormalTexture(
				Tools::getPathName(materialsMaterialPBRNormalTexture->getController()->getValue().getString()),
				Tools::getFileName(materialsMaterialPBRNormalTexture->getController()->getValue().getString())
			);
			pbrMaterialProperties->setExposure(Tools::convertToFloat(materialsMaterialPBRExposure->getController()->getValue().getString()));
			pbrMaterialProperties->setBaseColorTextureMaskedTransparency(materialsMaterialUseMaskedTransparency->getController()->getValue().getString() == "1"?true:false);
			pbrMaterialProperties->setBaseColorTextureMaskedTransparencyThreshold(Tools::convertToFloat(materialsMaterialMaskedTransparencyThreshold->getController()->getValue().getString()));
		} else {
			onMaterialDropDownApply();
		}
	} catch (Exception& exception) {
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void ModelEditorTabController::setAnimations() {
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;

	Model* model = view->getLodLevel() == 1?view->getPrototype()->getModel():getLODLevel(view->getLodLevel())->getModel();
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
			"<scrollarea id=\"" +
			animationsDropDown->getId() +
			"_inner_scrollarea\" width=\"100%\" height=\"100\">\n";
		animationsDropDownInnerNodeSubNodesXML = animationsDropDownInnerNodeSubNodesXML + "<dropdown-option text=\"<New animation>\" value=\"<New animation>\" />";
		for (auto it: model->getAnimationSetups()) {
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
		animationsDropDownInnerNodeSubNodesXML = animationsDropDownInnerNodeSubNodesXML + "</scrollarea>";
		try {
			animationsDropDownInnerNode->replaceSubNodes(animationsDropDownInnerNodeSubNodesXML, true);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorTabController::setAnimations(): An error occurred: "));
			Console::println(string(exception.what()));
		}
		// TODO: this usually works most of the time out of the box, so custom layouting is not required, but in this case not, need to find out whats going wrong there
		// animationsDropDown->getScreenNode()->layout(animationsDropDown);
	}

	{
		auto animationsAnimationOverlayFromNodeIdDropDownInnerNode = dynamic_cast< GUIParentNode* >((animationsAnimationOverlayFromNodeIdDropDown->getScreenNode()->getNodeById(animationsAnimationOverlayFromNodeIdDropDown->getId() + "_inner")));
		auto idx = 0;
		string animationsAnimationOverlayFromNodeIdDropDownInnerNodeSubNodesXML = "";
		animationsAnimationOverlayFromNodeIdDropDownInnerNodeSubNodesXML =
			animationsAnimationOverlayFromNodeIdDropDownInnerNodeSubNodesXML +
			"<scrollarea id=\"" +
			animationsAnimationOverlayFromNodeIdDropDown->getId() +
			"_inner_scrollarea\" width=\"100%\" height=\"70\">\n";
		animationsAnimationOverlayFromNodeIdDropDownInnerNodeSubNodesXML =
			animationsAnimationOverlayFromNodeIdDropDownInnerNodeSubNodesXML +
			"<dropdown-option text=\"\" value=\"\"" +
			(idx == 0 ? "selected=\"true\" " : "") +
			" />\n";
		for (auto it: model->getNodes()) {
			auto nodeId = it.second->getId();
			animationsAnimationOverlayFromNodeIdDropDownInnerNodeSubNodesXML =
				animationsAnimationOverlayFromNodeIdDropDownInnerNodeSubNodesXML +
				"<dropdown-option text=\"" +
				GUIParser::escapeQuotes(nodeId) +
				"\" value=\"" +
				GUIParser::escapeQuotes(nodeId) +
				"\" " +
				(idx == 0 ? "selected=\"true\" " : "") +
				" />\n";
			idx++;
		}
		animationsAnimationOverlayFromNodeIdDropDownInnerNodeSubNodesXML = animationsAnimationOverlayFromNodeIdDropDownInnerNodeSubNodesXML + "</scrollarea>";
		try {
			animationsAnimationOverlayFromNodeIdDropDownInnerNode->replaceSubNodes(animationsAnimationOverlayFromNodeIdDropDownInnerNodeSubNodesXML, true);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorTabController::setAnimations(): An error occurred: "));
			Console::println(string(exception.what()));
		}
		// TODO: this usually works most of the time out of the box, so custom layouting is not required, but in this case not, need to find out whats going wrong there
		// animationsAnimationOverlayFromNodeIdDropDown->getScreenNode()->layout(animationsAnimationOverlayFromNodeIdDropDown);
	}

	// select default animation
	animationsDropDown->getController()->setValue(MutableString(Model::ANIMATIONSETUP_DEFAULT));

	// apply
	onAnimationDropDownApply();
}

void ModelEditorTabController::onAnimationDropDownValueChanged() {
	Model* model = view->getLodLevel() == 1?view->getPrototype()->getModel():getLODLevel(view->getLodLevel())->getModel();
	if (model == nullptr) return;

	auto animationSetup = model->getAnimationSetup(animationsDropDown->getController()->getValue().getString());
	auto defaultAnimation = animationSetup != nullptr && animationSetup->getId() == Model::ANIMATIONSETUP_DEFAULT;
	animationsDropDownDelete->getController()->setDisabled(defaultAnimation || animationSetup == nullptr);
}

void ModelEditorTabController::onAnimationDropDownApply() {
	Model* model = view->getLodLevel() == 1?view->getPrototype()->getModel():getLODLevel(view->getLodLevel())->getModel();
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
	animationsAnimationOverlayFromNodeIdDropDown->getController()->setValue(MutableString(animationSetup->getOverlayFromNodeId()));
	animationsAnimationOverlayFromNodeIdDropDown->getController()->setDisabled(defaultAnimation);
	animationsAnimationLoop->getController()->setValue(MutableString(animationSetup->isLoop() == true?"1":""));
	animationsAnimationLoop->getController()->setDisabled(defaultAnimation);
	animationsAnimationSpeed->getController()->setValue(MutableString(animationSetup->getSpeed(), 4));
	animationsAnimationSpeed->getController()->setDisabled(defaultAnimation);
	animationsAnimationName->getController()->setValue(MutableString(animationSetup->getId()));
	animationsAnimationName->getController()->setDisabled(defaultAnimation);
	animationsAnimationApply->getController()->setDisabled(defaultAnimation);
	if (animationSetup != &newAnimationSetup) view->playAnimation(animationSetup->getId());
}

void ModelEditorTabController::onAnimationDropDownDelete() {
	Model* model = view->getLodLevel() == 1?view->getPrototype()->getModel():getLODLevel(view->getLodLevel())->getModel();
	if (model == nullptr) return;

	auto animationName = animationsDropDown->getController()->getValue().getString();
	auto animationSetup = model->getAnimationSetup(animationName);
	auto it = model->getAnimationSetups().find(animationSetup->getId());
	it = model->getAnimationSetups().erase(it);
	delete animationSetup;

	setAnimations();
	animationsDropDown->getController()->setValue(MutableString(it->second->getId()));
	onAnimationDropDownApply();
}

void ModelEditorTabController::onAnimationApply() {
	Model* model = view->getLodLevel() == 1?view->getPrototype()->getModel():getLODLevel(view->getLodLevel())->getModel();
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
			model->getAnimationSetups().erase(animationSetup->getId());
			animationSetup = model->addAnimationSetup(
				animationsAnimationName->getController()->getValue().getString(),
				0,
				0,
				false
			);
		}
		animationSetup->setStartFrame(Integer::parseInt(animationsAnimationStartFrame->getController()->getValue().getString()));
		animationSetup->setEndFrame(Integer::parseInt(animationsAnimationEndFrame->getController()->getValue().getString()));
		animationSetup->setOverlayFromNodeId(animationsAnimationOverlayFromNodeIdDropDown->getController()->getValue().getString());
		animationSetup->setLoop(animationsAnimationLoop->getController()->getValue().getString() == "1");
		animationSetup->setSpeed(Float::parseFloat(animationsAnimationSpeed->getController()->getValue().getString()));
		setAnimations();
		animationsDropDown->getController()->setValue(MutableString(animationSetup->getId()));
		onAnimationDropDownApply();
		setPreview();
		view->playAnimation(animationSetup->getId());
	} catch (Exception& exception) {
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void ModelEditorTabController::unsetAnimations() {

	dynamic_cast<GUIParentNode*>(animationsDropDown->getScreenNode()->getNodeById(animationsDropDown->getId() + "_inner"))->clearSubNodes();
	animationsDropDown->getController()->setValue(MutableString(""));
	animationsDropDown->getController()->setDisabled(true);
	animationsDropDownApply->getController()->setDisabled(true);
	animationsDropDownDelete->getController()->setDisabled(true);
	animationsAnimationStartFrame->getController()->setValue(MutableString(""));
	animationsAnimationStartFrame->getController()->setDisabled(true);
	animationsAnimationEndFrame->getController()->setValue(MutableString(""));
	animationsAnimationEndFrame->getController()->setDisabled(true);
	animationsAnimationOverlayFromNodeIdDropDown->getController()->setValue(MutableString(""));
	animationsAnimationOverlayFromNodeIdDropDown->getController()->setDisabled(true);
	animationsAnimationLoop->getController()->setValue(MutableString(""));
	animationsAnimationLoop->getController()->setDisabled(true);
	animationsAnimationSpeed->getController()->setValue(MutableString(""));
	animationsAnimationSpeed->getController()->setDisabled(true);
	animationsAnimationName->getController()->setValue(MutableString(""));
	animationsAnimationName->getController()->setDisabled(true);
	animationsAnimationApply->getController()->setDisabled(true);
}

void ModelEditorTabController::setPreview() {
	previewAnimationsBaseDropDown->getController()->setDisabled(false);
	previewAnimationsOverlay1DropDown->getController()->setDisabled(false);
	previewAnimationsOverlay2DropDown->getController()->setDisabled(false);
	previewAnimationsOverlay3DropDown->getController()->setDisabled(false);
	previewAnimationsAttachment1BoneDropdown->getController()->setDisabled(false);
	previewAnimationsAttachment1ModelModel->getController()->setDisabled(false);
	previewAnimationsAttachment1ModelLoad->getController()->setDisabled(false);
	previewAnimationsAttachment1ModelClear->getController()->setDisabled(false);
	buttonPreviewApply->getController()->setDisabled(false);

	Model* model = view->getLodLevel() == 1?view->getPrototype()->getModel():getLODLevel(view->getLodLevel())->getModel();
	if (model == nullptr) {
		unsetPreview();
		return;
	}

	{
		auto animationsDropDownInnerNode = dynamic_cast< GUIParentNode* >((previewAnimationsBaseDropDown->getScreenNode()->getNodeById(previewAnimationsBaseDropDown->getId() + "_inner")));
		string animationsDropDownInnerNodeSubNodesXML = "";
		animationsDropDownInnerNodeSubNodesXML =
			animationsDropDownInnerNodeSubNodesXML +
			"<scrollarea id=\"" +
			previewAnimationsBaseDropDown->getId() +
			"_inner_scrollarea\" width=\"100%\" height=\"100\">\n";
		animationsDropDownInnerNodeSubNodesXML = animationsDropDownInnerNodeSubNodesXML + "<dropdown-option text=\"<No animation>\" value=\"\" selected=\"true\" />";
		for (auto it: model->getAnimationSetups()) {
			auto animationSetup = it.second;
			if (animationSetup->isOverlayAnimationSetup() == true) continue;
			animationsDropDownInnerNodeSubNodesXML =
				animationsDropDownInnerNodeSubNodesXML + "<dropdown-option text=\"" +
				GUIParser::escapeQuotes(animationSetup->getId()) +
				"\" value=\"" +
				GUIParser::escapeQuotes(animationSetup->getId()) +
				"\" " +
				" />\n";
		}
		animationsDropDownInnerNodeSubNodesXML = animationsDropDownInnerNodeSubNodesXML + "</scrollarea>";
		try {
			animationsDropDownInnerNode->replaceSubNodes(animationsDropDownInnerNodeSubNodesXML, true);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorTabController::setPreview(): An error occurred: "));
			Console::println(string(exception.what()));
		}
	}

	{
		auto animationsDropDownInnerNode1 = dynamic_cast< GUIParentNode* >((previewAnimationsOverlay1DropDown->getScreenNode()->getNodeById(previewAnimationsOverlay1DropDown->getId() + "_inner")));
		auto animationsDropDownInnerNode2 = dynamic_cast< GUIParentNode* >((previewAnimationsOverlay2DropDown->getScreenNode()->getNodeById(previewAnimationsOverlay2DropDown->getId() + "_inner")));
		auto animationsDropDownInnerNode3 = dynamic_cast< GUIParentNode* >((previewAnimationsOverlay3DropDown->getScreenNode()->getNodeById(previewAnimationsOverlay3DropDown->getId() + "_inner")));
		string animationsDropDownInnerNodeSubNodesXML = "";
		animationsDropDownInnerNodeSubNodesXML = animationsDropDownInnerNodeSubNodesXML + "<dropdown-option text=\"<No animation>\" value=\"\" selected=\"true\" />";
		for (auto it: model->getAnimationSetups()) {
			auto animationSetup = it.second;
			if (animationSetup->isOverlayAnimationSetup() == false) continue;
			animationsDropDownInnerNodeSubNodesXML =
				animationsDropDownInnerNodeSubNodesXML + "<dropdown-option text=\"" +
				GUIParser::escapeQuotes(animationSetup->getId()) +
				"\" value=\"" +
				GUIParser::escapeQuotes(animationSetup->getId()) +
				"\" " +
				" />\n";
		}
		try {
			animationsDropDownInnerNode1->replaceSubNodes(
				"<scrollarea id=\"" +
				previewAnimationsOverlay1DropDown->getId() +
				"_inner_scrollarea\" width=\"100%\" height=\"100\">\n" +
				animationsDropDownInnerNodeSubNodesXML +
				"</scrollarea>",
				true
			);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorTabController::setPreview(): An error occurred: "));
			Console::println(string(exception.what()));
		}
		try {
			animationsDropDownInnerNode2->replaceSubNodes(
				"<scrollarea id=\"" +
				previewAnimationsOverlay2DropDown->getId() +
				"_inner_scrollarea\" width=\"100%\" height=\"100\">\n" +
				animationsDropDownInnerNodeSubNodesXML +
				"</scrollarea>",
				true
			);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorTabController::setPreview(): An error occurred: "));
			Console::println(string(exception.what()));
		}
		try {
			animationsDropDownInnerNode3->replaceSubNodes(
				"<scrollarea id=\"" +
				previewAnimationsOverlay3DropDown->getId() +
				"_inner_scrollarea\" width=\"100%\" height=\"100\">\n" +
				animationsDropDownInnerNodeSubNodesXML +
				"</scrollarea>",
				true
			);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorTabController::setPreview(): An error occurred: "));
			Console::println(string(exception.what()));
		}
	}

	{
		auto animationsAttachment1BoneDropDownInnerNode = dynamic_cast< GUIParentNode* >((previewAnimationsAttachment1BoneDropdown->getScreenNode()->getNodeById(previewAnimationsAttachment1BoneDropdown->getId() + "_inner")));
		string animationsAttachment1BoneDropDownInnerNodeSubNodesXML = "";
		animationsAttachment1BoneDropDownInnerNodeSubNodesXML =
			animationsAttachment1BoneDropDownInnerNodeSubNodesXML +
			"<scrollarea id=\"" +
			previewAnimationsAttachment1BoneDropdown->getId() +
			"_inner_scrollarea\" width=\"100%\" height=\"100\">\n";
		animationsAttachment1BoneDropDownInnerNodeSubNodesXML = animationsAttachment1BoneDropDownInnerNodeSubNodesXML + "<dropdown-option text=\"<No bone>\" value=\"\" selected=\"true\" />";
		for (auto it: model->getNodes()) {
			auto node = it.second;
			animationsAttachment1BoneDropDownInnerNodeSubNodesXML =
				animationsAttachment1BoneDropDownInnerNodeSubNodesXML + "<dropdown-option text=\"" +
				GUIParser::escapeQuotes(node->getId()) +
				"\" value=\"" +
				GUIParser::escapeQuotes(node->getId()) +
				"\" " +
				" />\n";
		}
		animationsAttachment1BoneDropDownInnerNodeSubNodesXML = animationsAttachment1BoneDropDownInnerNodeSubNodesXML + "</scrollarea>";
		try {
			animationsAttachment1BoneDropDownInnerNode->replaceSubNodes(animationsAttachment1BoneDropDownInnerNodeSubNodesXML, true);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorTabController::setPreview(): An error occurred: "));
			Console::println(string(exception.what()));
		}
	}

}

void ModelEditorTabController::onPreviewAnimationsAttachment1ModelLoad() {
	class OnPreviewAnimationsAttachment1ModelLoad: public virtual Action
	{

	public:
		void performAction() override {
			modelEditorTabController->previewAnimationsAttachment1ModelModel->getController()->setValue(
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName() +
				"/" +
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->modelPath.setPath(
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName()
			);
			modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param modelEditorTabController model editor tab controller
		 */
		OnPreviewAnimationsAttachment1ModelLoad(ModelEditorTabController* modelEditorTabController): modelEditorTabController(modelEditorTabController) {
		}

	private:
		ModelEditorTabController* modelEditorTabController;
	};

	vector<string> extensions = ModelReader::getModelExtensions();
	view->getPopUps()->getFileDialogScreenController()->show(
		previewAnimationsAttachment1ModelModel->getController()->getValue().getString().empty() == true?modelPath.getPath():Tools::getPathName(previewAnimationsAttachment1ModelModel->getController()->getValue().getString()),
		"Load from: ",
		extensions,
		Tools::getFileName(previewAnimationsAttachment1ModelModel->getController()->getValue().getString()),
		true,
		new OnPreviewAnimationsAttachment1ModelLoad(this)
	);
}

void ModelEditorTabController::onPreviewAnimationsAttachment1ModelClear() {
	previewAnimationsAttachment1ModelModel->getController()->setValue(MutableString());
}

void ModelEditorTabController::onPreviewApply() {
	Model* model = view->getLodLevel() == 1?view->getPrototype()->getModel():getLODLevel(view->getLodLevel())->getModel();
	if (model == nullptr) return;

	auto baseAnimationName = previewAnimationsBaseDropDown->getController()->getValue().getString();
	auto overlay1AnimationName = previewAnimationsOverlay1DropDown->getController()->getValue().getString();
	auto overlay2AnimationName = previewAnimationsOverlay2DropDown->getController()->getValue().getString();
	auto overlay3AnimationName = previewAnimationsOverlay3DropDown->getController()->getValue().getString();
	try {
		view->playAnimation(baseAnimationName, overlay1AnimationName, overlay2AnimationName, overlay3AnimationName);
		view->addAttachment1(previewAnimationsAttachment1BoneDropdown->getController()->getValue().getString(), previewAnimationsAttachment1ModelModel->getController()->getValue().getString());
	} catch (Exception& exception) {
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void ModelEditorTabController::unsetPreview() {
	previewAnimationsBaseDropDown->getController()->setDisabled(true);
	previewAnimationsOverlay1DropDown->getController()->setDisabled(true);
	previewAnimationsOverlay2DropDown->getController()->setDisabled(true);
	previewAnimationsOverlay3DropDown->getController()->setDisabled(true);
	previewAnimationsAttachment1BoneDropdown->getController()->setDisabled(true);
	previewAnimationsAttachment1BoneDropdown->getController()->setValue(MutableString());
	previewAnimationsAttachment1ModelModel->getController()->setDisabled(true);
	previewAnimationsAttachment1ModelModel->getController()->setValue(MutableString());
	previewAnimationsAttachment1ModelLoad->getController()->setDisabled(true);
	previewAnimationsAttachment1ModelClear->getController()->setDisabled(true);
	buttonPreviewApply->getController()->setDisabled(true);
}


void ModelEditorTabController::setStatistics(int statsOpaqueFaces, int statsTransparentFaces, int statsMaterialCount)
{
	this->statsOpaqueFaces->getController()->setValue(MutableString(statsOpaqueFaces));
	this->statsTransparentFaces->getController()->setValue(MutableString(statsTransparentFaces));
	this->statsMaterialCount->getController()->setValue(MutableString(statsMaterialCount));
}

void ModelEditorTabController::unsetStatistics()
{
	this->statsOpaqueFaces->getController()->setValue(MutableString());
	this->statsTransparentFaces->getController()->setValue(MutableString());
	this->statsMaterialCount->getController()->setValue(MutableString());
}

void ModelEditorTabController::setTools() {
	buttonToolsComputeNormals->getController()->setDisabled(false);
	buttonToolsOptimizeModel->getController()->setDisabled(false);
}

void ModelEditorTabController::unsetTools() {
	buttonToolsComputeNormals->getController()->setDisabled(true);
	buttonToolsOptimizeModel->getController()->setDisabled(true);
}

void ModelEditorTabController::onToolsComputeNormal() {
	view->computeNormals();
}

void ModelEditorTabController::onToolsOptimizeModel() {
	view->optimizeModel();
}

void ModelEditorTabController::onQuit()
{
}

void ModelEditorTabController::onModelLoad()
{
	class OnModelLoad: public virtual Action
	{

	public:
		void performAction() override {
			modelEditorTabController->view->loadFile(
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName(),
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->modelPath.setPath(
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName()
			);
			modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param modelEditorTabController model editor tab controller
		 */
		OnModelLoad(ModelEditorTabController* modelEditorTabController): modelEditorTabController(modelEditorTabController) {
		}

	private:
		ModelEditorTabController* modelEditorTabController;
	};

	auto fileName = view->getPrototype() != nullptr?view->getPrototype()->getFileName():"";
	if (fileName.length() == 0) {
		fileName = view->getFileName();
	}
	fileName = Tools::getFileName(fileName);
	vector<string> extensions = ModelReader::getModelExtensions();
	extensions.push_back("tmodel");
	view->getPopUps()->getFileDialogScreenController()->show(
		modelPath.getPath(),
		"Load from: ",
		extensions,
		view->getFileName(),
		true,
		new OnModelLoad(this)
	);
}

void ModelEditorTabController::onModelSave()
{
	class OnModelSave: public virtual Action
	{
	public:
		void performAction() override {
			try {
				modelEditorTabController->view->saveFile(
					modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName(),
					modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
				);
				modelEditorTabController->modelPath.setPath(
					modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName()
				);
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
			} catch (Exception& exception) {
				modelEditorTabController->showErrorPopUp("Warning", (string(exception.what())));
			}
		}

		/**
		 * Public constructor
		 * @param modelEditorTabController model editor tab controller
		 */
		OnModelSave(ModelEditorTabController* modelEditorTabController): modelEditorTabController(modelEditorTabController) {
		}

	private:
		ModelEditorTabController* modelEditorTabController;
	};

	auto fileName = view->getPrototype() != nullptr?view->getPrototype()->getFileName():"";
	if (fileName.length() == 0) {
		fileName = view->getFileName();
		if (StringTools::endsWith(StringTools::toLowerCase(fileName), ".tmodel") == false) {
			fileName = Tools::removeFileEnding(fileName) + ".tmodel";
		}
	}
	vector<string> extensions = {
		"tmm"
	};
	fileName = Tools::getFileName(fileName);
	view->getPopUps()->getFileDialogScreenController()->show(
		modelPath.getPath(),
		"Save to: ",
		extensions,
		fileName,
		false,
		new OnModelSave(this)
	);
}

void ModelEditorTabController::onModelReload()
{
	view->reloadFile();
}

void ModelEditorTabController::onModelReimport()
{
	class OnModelLoad: public virtual Action
	{

	public:
		void performAction() override {
			modelEditorTabController->view->reimportModel(
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName(),
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->modelPath.setPath(
				modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->getPathName()
			);
			modelEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param modelEditorTabController model editor tab controller
		 */
		OnModelLoad(ModelEditorTabController* modelEditorTabController): modelEditorTabController(modelEditorTabController) {
		}

	private:
		ModelEditorTabController* modelEditorTabController;
	};

	vector<string> extensions = ModelReader::getModelExtensions();
	view->getPopUps()->getFileDialogScreenController()->show(
		modelPath.getPath(),
		"Reimport model: ",
		ModelReader::getModelExtensions(),
		view->getFileName(),
		true,
		new OnModelLoad(this)
	);
}

void ModelEditorTabController::onPivotApply()
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

void ModelEditorTabController::onRenderingApply()
{
	if (view->getPrototype() == nullptr) return;
	try {
		view->getPrototype()->setContributesShadows(renderingContributesShadows->getController()->getValue().equals("1"));
		view->getPrototype()->setReceivesShadows(renderingReceivesShadows->getController()->getValue().equals("1"));
		view->getPrototype()->setRenderGroups(renderingRenderGroups->getController()->getValue().equals("1"));
		view->getPrototype()->setShader(renderingShader->getController()->getValue().getString());
		view->getPrototype()->setDistanceShader(renderingDistanceShader->getController()->getValue().getString());
		view->getPrototype()->setDistanceShaderDistance(Float::parseFloat(renderingDistanceShaderDistance->getController()->getValue().getString()));
	} catch (Exception& exception) {
		showErrorPopUp("Warning", (string(exception.what())));
	}
	view->updateRendering();

	// shader parameters
	setShaderParameters();
}

void ModelEditorTabController::onShaderParametersApply() {
	auto prototype = view->getPrototype();
	if (prototype == nullptr) return;

	auto shaderParametersDefault = Engine::getShaderParameterDefaults(view->getPrototype()->getShader());
	auto distanceShaderParametersDefault = Engine::getShaderParameterDefaults(view->getPrototype()->getDistanceShader());
	auto shaderParameters = prototype->getShaderParameters();
	auto distanceShaderParameters = prototype->getDistanceShaderParameters();
	if (shaderParametersDefault.empty() == false) {
		for (auto& parameterIt: shaderParametersDefault) {
			auto& parameterName = parameterIt.first;
			auto parameterValueElement = dynamic_cast<GUIElementNode*>(shaderParametersContent->getScreenNode()->getNodeById("shaderparameters_" + GUIParser::unescapeQuotes(parameterName)));
			if (parameterValueElement == nullptr) continue;
			auto parameterValue = parameterValueElement->getController()->getValue().getString();
			shaderParameters.setShaderParameter(parameterName, parameterValue);
		}
	}

	if (distanceShaderParametersDefault.empty() == false) {
		for (auto& parameterIt: distanceShaderParametersDefault) {
			auto& parameterName = parameterIt.first;
			auto parameterValueElement = dynamic_cast<GUIElementNode*>(shaderParametersContent->getScreenNode()->getNodeById("shaderparameters_distance_" + GUIParser::unescapeQuotes(parameterName)));
			if (parameterValueElement == nullptr) continue;
			auto parameterValue = parameterValueElement->getController()->getValue().getString();
			distanceShaderParameters.setShaderParameter(parameterName, parameterValue);
		}
	}

	//
	prototype->setShaderParameters(shaderParameters);
	prototype->setDistanceShaderParameters(distanceShaderParameters);

	//
	view->updateShaderParemeters();
}

void ModelEditorTabController::onMaterialPBREnabledValueChanged() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	auto disabled = materialsMaterialPBREnabled->getController()->getValue().getString() != "1";
	materialsMaterialPBRBaseColorFactor->getController()->setDisabled(disabled);
	materialsMaterialPBRBaseColorTexture->getController()->setDisabled(disabled);
	materialsMaterialPBRBaseColorTextureLoad->getController()->setDisabled(disabled);
	materialsMaterialPBRBaseColorTextureClear->getController()->setDisabled(disabled);
	materialsMaterialPBRMetallicFactor->getController()->setDisabled(disabled);
	materialsMaterialPBRRoughnessFactor->getController()->setDisabled(disabled);
	materialsMaterialPBRMetallicRoughnessTexture->getController()->setDisabled(disabled);
	materialsMaterialPBRMetallicRoughnessTextureLoad->getController()->setDisabled(disabled);
	materialsMaterialPBRMetallicRoughnessTextureClear->getController()->setDisabled(disabled);
	materialsMaterialPBRNormalScale->getController()->setDisabled(disabled);
	materialsMaterialPBRNormalTexture->getController()->setDisabled(disabled);
	materialsMaterialPBRNormalTextureLoad->getController()->setDisabled(disabled);
	materialsMaterialPBRNormalTextureClear->getController()->setDisabled(disabled);
	materialsMaterialPBRExposure->getController()->setDisabled(disabled);
	if (disabled == false && pbrMaterialProperties == nullptr) {
		materialsMaterialPBRBaseColorFactor->getController()->setValue(MutableString(Tools::formatColor4(Color4(1.0f, 1.0f, 1.0f, 1.0f))));
		materialsMaterialPBRBaseColorTexture->getController()->setValue(MutableString());
		materialsMaterialPBRMetallicFactor->getController()->setValue(MutableString(Tools::formatFloat(1.0f)));
		materialsMaterialPBRRoughnessFactor->getController()->setValue(MutableString(Tools::formatFloat(1.0f)));
		materialsMaterialPBRMetallicRoughnessTexture->getController()->setValue(MutableString());
		materialsMaterialPBRNormalScale->getController()->setValue(MutableString(Tools::formatFloat(1.0f)));
		materialsMaterialPBRNormalTexture->getController()->setValue(MutableString());
		materialsMaterialPBRExposure->getController()->setValue(MutableString(Tools::formatFloat(1.0f)));
	}
}

void ModelEditorTabController::saveFile(const string& pathName, const string& fileName)
{
	view->saveFile(pathName, fileName);
}

void ModelEditorTabController::loadFile(const string& pathName, const string& fileName)
{
	view->loadFile(pathName, fileName);
}

void ModelEditorTabController::showErrorPopUp(const string& caption, const string& message)
{
	view->getPopUps()->getInfoDialogScreenController()->show(caption, message);
}

void ModelEditorTabController::setMaterialDetails() {
	Material* material = getSelectedMaterial();
	if (material == nullptr) return;

	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	auto pbrMaterialProperties = material->getPBRMaterialProperties();

	view->getEditorView()->setDetailsContent(
		"<template id=\"details_material_spec\" src=\"resources/engine/gui/template_details_specularmaterial.xml\" />\n"
		"<template id=\"details_material_pbr\" src=\"resources/engine/gui/template_details_pbrmaterial.xml\" />\n"
	);

	auto screenNode = view->getEditorView()->getScreenController()->getScreenNode();

	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_material_spec"))->getActiveConditions().add("open");
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_material_pbr"))->getActiveConditions().add("open");

		if (pbrMaterialProperties != nullptr) {
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_details"))->getActiveConditions().add("pbr");
		} else {
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_details"))->getActiveConditions().remove("pbr");
		}
	} catch (Exception& exception) {
		Console::println(string("ModelEditorTabController::setMaterialDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}

	//
	updateMaterialDetails();
}

void ModelEditorTabController::updateMaterialDetails() {
	Material* material = getSelectedMaterial();
	if (material == nullptr) return;

	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	auto pbrMaterialProperties = material->getPBRMaterialProperties();

	auto screenNode = view->getEditorView()->getScreenController()->getScreenNode();

	try {
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("specularmaterial_diffuse_texture"))->setSource(
			PrototypeReader::getResourcePathName(
				view->getEditorView()->getScreenController()->getProjectPath(),
				specularMaterialProperties->getDiffuseTexturePathName() + "/" + specularMaterialProperties->getDiffuseTextureFileName()
			) +
			"/" +
			specularMaterialProperties->getDiffuseTextureFileName()
		);
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("specularmaterial_transparency_texture"))->setSource(
			PrototypeReader::getResourcePathName(
				view->getEditorView()->getScreenController()->getProjectPath(),
				specularMaterialProperties->getDiffuseTransparencyTexturePathName() + "/" + specularMaterialProperties->getDiffuseTransparencyTextureFileName()
			) +
			"/" +
			specularMaterialProperties->getDiffuseTextureFileName()
		);
		required_dynamic_cast<GUITextureNode*>(screenNode->getNodeById("specularmaterial_normal_texture"))->setTexture(specularMaterialProperties->getNormalTexture());
		required_dynamic_cast<GUITextureNode*>(screenNode->getNodeById("specularmaterial_specular_texture"))->setTexture(specularMaterialProperties->getSpecularTexture());
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("specularmaterial_ambient"))->setEffectColorMul(Color4(specularMaterialProperties->getAmbientColor()));
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("specularmaterial_diffuse"))->setEffectColorMul(Color4(specularMaterialProperties->getDiffuseColor()));
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("specularmaterial_emission"))->setEffectColorMul(Color4(specularMaterialProperties->getEmissionColor()));
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("specularmaterial_specular"))->setEffectColorMul(Color4(specularMaterialProperties->getSpecularColor()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("specularmaterial_shininess"))->getController()->setValue(specularMaterialProperties->getShininess());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("specularmaterial_reflection"))->getController()->setValue(specularMaterialProperties->getReflection());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("specularmaterial_maskedtransparency"))->getController()->setValue(MutableString(specularMaterialProperties->hasDiffuseTextureMaskedTransparency() == true?"1":""));

		if (pbrMaterialProperties != nullptr) {
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_enabled"))->getController()->setValue(MutableString("1"));
			required_dynamic_cast<GUITextureNode*>(screenNode->getNodeById("pbrmaterial_basecolor_texture"))->setTexture(pbrMaterialProperties->getBaseColorTexture());
			required_dynamic_cast<GUITextureNode*>(screenNode->getNodeById("pbrmaterial_metallic_roughness_texture"))->setTexture(pbrMaterialProperties->getMetallicRoughnessTexture());
			required_dynamic_cast<GUITextureNode*>(screenNode->getNodeById("pbrmaterial_normal_texture"))->setTexture(pbrMaterialProperties->getNormalTexture());
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("pbrmaterial_basecolor"))->setEffectColorMul(Color4(pbrMaterialProperties->getBaseColorFactor()));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_metallic_factor"))->getController()->setValue(pbrMaterialProperties->getMetallicFactor());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_roughness_factor"))->getController()->setValue(pbrMaterialProperties->getRoughnessFactor());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_normal_scale"))->getController()->setValue(pbrMaterialProperties->getNormalScale());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_exposure"))->getController()->setValue(pbrMaterialProperties->getExposure());
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_maskedtransparency"))->getController()->setValue(MutableString(pbrMaterialProperties->hasBaseColorTextureMaskedTransparency() == true?"1":""));
		} else {
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_enabled"))->getController()->setValue(MutableString());
		}
	} catch (Exception& exception) {
		Console::println(string("ModelEditorTabController::updateMaterialDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void ModelEditorTabController::applySpecularMaterialDetails() {
	Material* material = getSelectedMaterial();
	if (material == nullptr) return;

	auto specularMaterialProperties = material->getSpecularMaterialProperties();

	auto screenNode = view->getEditorView()->getScreenController()->getScreenNode();

	try {
		specularMaterialProperties->setShininess(Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("specularmaterial_shininess"))->getController()->getValue().getString()));
		specularMaterialProperties->setReflection(Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("specularmaterial_reflection"))->getController()->getValue().getString()));
		specularMaterialProperties->setDiffuseTextureMaskedTransparency(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("specularmaterial_maskedtransparency"))->getController()->getValue().getString() == "1");
	} catch (Exception& exception) {
		Console::println(string("ModelEditorTabController::applySpecularMaterialDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void ModelEditorTabController::applyPBRMaterialDetails() {
	Material* material = getSelectedMaterial();
	if (material == nullptr) return;

	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	if (pbrMaterialProperties == nullptr) return;

	auto screenNode = view->getEditorView()->getScreenController()->getScreenNode();

	try {
		pbrMaterialProperties->setMetallicFactor(Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_metallic_factor"))->getController()->getValue().getString()));
		pbrMaterialProperties->setRoughnessFactor(Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_roughness_factor"))->getController()->getValue().getString()));
		pbrMaterialProperties->setNormalScale(Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_normal_scale"))->getController()->getValue().getString()));
		pbrMaterialProperties->setExposure(Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_exposure"))->getController()->getValue().getString()));
		pbrMaterialProperties->setBaseColorTextureMaskedTransparency(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("pbrmaterial_maskedtransparency"))->getController()->getValue().getString() == "1");
	} catch (Exception& exception) {
		Console::println(string("ModelEditorTabController::applyPBRMaterialDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void ModelEditorTabController::setAnimationDetails(const string& animationId) {
	Console::println("ModelEditorTabController::setAnimationDetails(): " + animationId);

	Model* model = view->getLodLevel() == 1?view->getPrototype()->getModel():getLODLevel(view->getLodLevel())->getModel();
	if (model == nullptr) return;

	auto animationSetup = model->getAnimationSetup(animationId);
	auto defaultAnimation = animationSetup != nullptr && animationSetup->getId() == Model::ANIMATIONSETUP_DEFAULT;

	if (animationSetup == nullptr) return;

	auto defaultAnimationSetup = model->getAnimationSetup(Model::ANIMATIONSETUP_DEFAULT);

	view->getEditorView()->setDetailsContent(
		string("<template id=\"details_animation\" src=\"resources/engine/gui/template_details_animation.xml\" max-frames=\"") +
		to_string(defaultAnimationSetup != nullptr?defaultAnimationSetup->getEndFrame():0) +
		string("\" />\n")
	);

	auto screenNode = view->getEditorView()->getScreenController()->getScreenNode();

	{
		auto idx = 0;
		string animationsXML;
		animationsXML =
			animationsXML +
			"<dropdown-option text=\"<None>\" value=\"\" " + (idx == 0 ? "selected=\"true\" " : "") + " />\n";
		idx++;
		for (auto it: model->getNodes()) {
			auto nodeId = it.second->getId();
			animationsXML+=
				"<dropdown-option text=\"" +
				GUIParser::escapeQuotes(nodeId) +
				"\" value=\"" +
				GUIParser::escapeQuotes(nodeId) +
				"\" " +
				(idx == 0 ? "selected=\"true\" " : "") +
				" />\n";
			idx++;
		}
		try {
			required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("animation_overlaybone_scrollarea"))->replaceSubNodes(animationsXML, true);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorTabController::setAnimationDetails(): An error occurred: "));
			Console::println(string(exception.what()));
		}
	}

	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_animation"))->getActiveConditions().add("open");
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_startframe"))->getController()->setValue(animationSetup->getStartFrame());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_startframe"))->getController()->setDisabled(defaultAnimation == true);
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_endframe"))->getController()->setValue(animationSetup->getEndFrame());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_endframe"))->getController()->setDisabled(defaultAnimation == true);
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_speed"))->getController()->setValue(animationSetup->getSpeed());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_speed"))->getController()->setDisabled(defaultAnimation == true);
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_loop"))->getController()->setValue(MutableString(animationSetup->isLoop() == true?"1":""));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_loop"))->getController()->setDisabled(defaultAnimation == true);
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_overlaybone"))->getController()->setValue(animationSetup->getOverlayFromNodeId());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_overlaybone"))->getController()->setDisabled(defaultAnimation == true);
	} catch (Exception& exception) {
		Console::println(string("ModelEditorTabController::setAnimationDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void ModelEditorTabController::applyAnimationDetails(const string& animationId) {
	Console::println("ModelEditorTabController::applyAnimationDetails(): " + animationId);

	view->playAnimation(Model::ANIMATIONSETUP_DEFAULT);

	Model* model = view->getLodLevel() == 1?view->getPrototype()->getModel():getLODLevel(view->getLodLevel())->getModel();
	if (model == nullptr) return;

	auto animationSetup = model->getAnimationSetup(animationId);
	auto defaultAnimation = animationSetup != nullptr && animationSetup->getId() == Model::ANIMATIONSETUP_DEFAULT;

	if (animationSetup == nullptr) return;

	auto screenNode = view->getEditorView()->getScreenController()->getScreenNode();

	try {
		auto startFrame = Integer::parseInt(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_startframe"))->getController()->getValue().getString());
		auto endFrame = Integer::parseInt(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_endframe"))->getController()->getValue().getString());
		auto speed = Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_speed"))->getController()->getValue().getString());
		auto loop = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_loop"))->getController()->getValue().getString() == "1";
		auto overlayFromNodeId = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("animation_overlaybone"))->getController()->getValue().getString();

		animationSetup->setStartFrame(startFrame < endFrame?startFrame:endFrame);
		animationSetup->setEndFrame(endFrame > startFrame?endFrame:startFrame);
		animationSetup->setSpeed(speed);
		animationSetup->setLoop(loop);
		animationSetup->setOverlayFromNodeId(overlayFromNodeId);

		view->playAnimation(animationId);
	} catch (Exception& exception) {
		Console::println(string("ModelEditorTabController::setAnimationDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}

}

void ModelEditorTabController::setAnimationPreviewDetails() {
	Console::println("ModelEditorTabController::setAnimationPreviewDetails(): ");

	Model* model = view->getLodLevel() == 1?view->getPrototype()->getModel():getLODLevel(view->getLodLevel())->getModel();
	if (model == nullptr) {
		unsetPreview();
		return;
	}

	auto defaultAnimationSetup = model->getAnimationSetup(Model::ANIMATIONSETUP_DEFAULT);

	view->getEditorView()->setDetailsContent(
		string("<template id=\"details_animationpreview\" src=\"resources/engine/gui/template_details_animationpreview.xml\" />\n")
	);

	auto screenNode = view->getEditorView()->getScreenController()->getScreenNode();

	{
		string animationsXML;
		animationsXML = animationsXML + "<dropdown-option text=\"<No animation>\" value=\"\" selected=\"true\" />";
		for (auto it: model->getAnimationSetups()) {
			auto animationSetup = it.second;
			if (animationSetup->isOverlayAnimationSetup() == true) continue;
			animationsXML =
				animationsXML + "<dropdown-option text=\"" +
				GUIParser::escapeQuotes(animationSetup->getId()) +
				"\" value=\"" +
				GUIParser::escapeQuotes(animationSetup->getId()) +
				"\" " +
				" />\n";
		}
		try {
			required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("animationpreview_base_scrollarea"))->replaceSubNodes(animationsXML, true);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorTabController::setAnimationPreviewDetails(): An error occurred: "));
			Console::println(string(exception.what()));
		}
	}

	{
		string overlayAnimationsXML;
		overlayAnimationsXML = overlayAnimationsXML + "<dropdown-option text=\"<No animation>\" value=\"\" selected=\"true\" />";
		for (auto it: model->getAnimationSetups()) {
			auto animationSetup = it.second;
			if (animationSetup->isOverlayAnimationSetup() == false) continue;
			overlayAnimationsXML =
				overlayAnimationsXML + "<dropdown-option text=\"" +
				GUIParser::escapeQuotes(animationSetup->getId()) +
				"\" value=\"" +
				GUIParser::escapeQuotes(animationSetup->getId()) +
				"\" " +
				" />\n";
		}
		try {
			required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("animationpreview_overlay1_scrollarea"))->replaceSubNodes(overlayAnimationsXML, true);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorTabController::setAnimationPreviewDetails(): An error occurred: "));
			Console::println(string(exception.what()));
		}
		try {
			required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("animationpreview_overlay2_scrollarea"))->replaceSubNodes(overlayAnimationsXML, true);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorTabController::setAnimationPreviewDetails(): An error occurred: "));
			Console::println(string(exception.what()));
		}
		try {
			required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("animationpreview_overlay3_scrollarea"))->replaceSubNodes(overlayAnimationsXML, true);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorTabController::setAnimationPreviewDetails(): An error occurred: "));
			Console::println(string(exception.what()));
		}
	}

	{
		string bonesXML;
		bonesXML = bonesXML + "<dropdown-option text=\"<No bone>\" value=\"\" selected=\"true\" />";
		for (auto it: model->getNodes()) {
			auto node = it.second;
			bonesXML =
				bonesXML + "<dropdown-option text=\"" +
				GUIParser::escapeQuotes(node->getId()) +
				"\" value=\"" +
				GUIParser::escapeQuotes(node->getId()) +
				"\" " +
				" />\n";
		}
		try {
			required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("animationpreview_attachment1_bone_scrollarea"))->replaceSubNodes(bonesXML, true);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorTabController::setAnimationPreviewDetails(): An error occurred: "));
			Console::println(string(exception.what()));
		}
	}

	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_animationpreview"))->getActiveConditions().add("open");
	} catch (Exception& exception) {
		Console::println(string("ModelEditorTabController::setAnimationPreviewDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void ModelEditorTabController::setSoundDetails(const string& soundId) {
	Console::println("ModelEditorTabController::setSoundDetails(): " + soundId);

	Model* model = view->getLodLevel() == 1?view->getPrototype()->getModel():getLODLevel(view->getLodLevel())->getModel();
	if (model == nullptr) return;

	prototypeSoundsSubController->setSoundDetails(view->getPrototype(), model, soundId);
}

void ModelEditorTabController::updateDetails(const string& outlinerNode) {
	view->getEditorView()->setDetailsContent(string());
	if (StringTools::startsWith(outlinerNode, "model.material.") == true) {
		setMaterialDetails();
	} else
	if (outlinerNode == "model.animations") {
		setAnimationPreviewDetails();
	} else
	if (StringTools::startsWith(outlinerNode, "model.animations.") == true) {
		auto animationId = StringTools::substring(outlinerNode, string("model.animations.").size(), outlinerNode.size());
		view->playAnimation(animationId);
		setAnimationDetails(animationId);
	}
}

void ModelEditorTabController::onMaterialLoadDiffuseTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties == nullptr) {
		specularMaterialProperties = new SpecularMaterialProperties();
		material->setSpecularMaterialProperties(specularMaterialProperties);
	}

	class OnLoadTexture: public virtual Action
	{
	public:
		void performAction() override {
			MutableString value;
			modelEditorTabController->view->reloadPrototype();
			specularMaterialProperties->setDiffuseTexture(
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getPathName(),
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getFileName(),
				specularMaterialProperties->getDiffuseTransparencyTexturePathName(),
				specularMaterialProperties->getDiffuseTransparencyTextureFileName()
			);
			modelEditorTabController->updateMaterialDetails();
			modelEditorTabController->getModelPath()->setPath(
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getPathName()
			);
			modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param modelEditorTabController model editor tab controller
		 * @param specularMaterialProperties specular material properties
		 */
		OnLoadTexture(ModelEditorTabController* modelEditorTabController, SpecularMaterialProperties* specularMaterialProperties)
			: modelEditorTabController(modelEditorTabController)
			, specularMaterialProperties(specularMaterialProperties) {
		}


	private:
		ModelEditorTabController* modelEditorTabController;
		SpecularMaterialProperties* specularMaterialProperties;
	};

	auto extensions = TextureReader::getTextureExtensions();
	view->getPopUps()->getFileDialogScreenController()->show(
		specularMaterialProperties->getDiffuseTextureFileName().empty() == false?specularMaterialProperties->getDiffuseTexturePathName():modelPath.getPath(),
		"Load specular diffuse texture from: ",
		extensions,
		specularMaterialProperties->getDiffuseTextureFileName(),
		true,
		new OnLoadTexture(this, specularMaterialProperties)
	);
}

void ModelEditorTabController::onMaterialClearDiffuseTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties == nullptr) {
		specularMaterialProperties = new SpecularMaterialProperties();
		material->setSpecularMaterialProperties(specularMaterialProperties);
	}
	view->reloadPrototype();
	specularMaterialProperties->setDiffuseTexture(
		string(),
		string(),
		specularMaterialProperties->getDiffuseTransparencyTexturePathName(),
		specularMaterialProperties->getDiffuseTransparencyTextureFileName()
	);
	updateMaterialDetails();
}

void ModelEditorTabController::onMaterialLoadDiffuseTransparencyTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties == nullptr) {
		specularMaterialProperties = new SpecularMaterialProperties();
		material->setSpecularMaterialProperties(specularMaterialProperties);
	}

	class OnLoadTexture: public virtual Action
	{
	public:
		void performAction() override {
			MutableString value;
			modelEditorTabController->view->reloadPrototype();
			specularMaterialProperties->setDiffuseTexture(
				specularMaterialProperties->getDiffuseTexturePathName(),
				specularMaterialProperties->getDiffuseTextureFileName(),
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getPathName(),
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->updateMaterialDetails();
			modelEditorTabController->getModelPath()->setPath(
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getPathName()
			);
			modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param modelEditorTabController model editor tab controller
		 * @param specularMaterialProperties specular material properties
		 */
		OnLoadTexture(ModelEditorTabController* modelEditorTabController, SpecularMaterialProperties* specularMaterialProperties)
			: modelEditorTabController(modelEditorTabController)
			, specularMaterialProperties(specularMaterialProperties) {
		}


	private:
		ModelEditorTabController* modelEditorTabController;
		SpecularMaterialProperties* specularMaterialProperties;
	};

	auto extensions = TextureReader::getTextureExtensions();
	view->getPopUps()->getFileDialogScreenController()->show(
		specularMaterialProperties->getDiffuseTransparencyTextureFileName().empty() == false?specularMaterialProperties->getDiffuseTransparencyTexturePathName():modelPath.getPath(),
		"Load specular diffuse transparency texture from: ",
		extensions,
		specularMaterialProperties->getDiffuseTransparencyTextureFileName(),
		true,
		new OnLoadTexture(this, specularMaterialProperties)
	);
}

void ModelEditorTabController::onMaterialClearDiffuseTransparencyTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties == nullptr) {
		specularMaterialProperties = new SpecularMaterialProperties();
		material->setSpecularMaterialProperties(specularMaterialProperties);
	}
	view->reloadPrototype();
	specularMaterialProperties->setDiffuseTexture(
		specularMaterialProperties->getDiffuseTexturePathName(),
		specularMaterialProperties->getDiffuseTextureFileName(),
		string(),
		string()
	);
	updateMaterialDetails();
}

void ModelEditorTabController::onMaterialLoadNormalTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties == nullptr) {
		specularMaterialProperties = new SpecularMaterialProperties();
		material->setSpecularMaterialProperties(specularMaterialProperties);
	}

	class OnLoadTexture: public virtual Action
	{
	public:
		void performAction() override {
			MutableString value;
			modelEditorTabController->view->reloadPrototype();
			specularMaterialProperties->setNormalTexture(
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getPathName(),
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->updateMaterialDetails();
			modelEditorTabController->getModelPath()->setPath(
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getPathName()
			);
			modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param modelEditorTabController model editor tab controller
		 * @param specularMaterialProperties specular material properties
		 */
		OnLoadTexture(ModelEditorTabController* modelEditorTabController, SpecularMaterialProperties* specularMaterialProperties)
			: modelEditorTabController(modelEditorTabController)
			, specularMaterialProperties(specularMaterialProperties) {
		}


	private:
		ModelEditorTabController* modelEditorTabController;
		SpecularMaterialProperties* specularMaterialProperties;
	};

	auto extensions = TextureReader::getTextureExtensions();
	view->getPopUps()->getFileDialogScreenController()->show(
		specularMaterialProperties->getNormalTextureFileName().empty() == false?specularMaterialProperties->getNormalTexturePathName():modelPath.getPath(),
		"Load specular normal texture from: ",
		extensions,
		specularMaterialProperties->getNormalTextureFileName(),
		true,
		new OnLoadTexture(this, specularMaterialProperties)
	);
}

void ModelEditorTabController::onMaterialClearNormalTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties == nullptr) {
		specularMaterialProperties = new SpecularMaterialProperties();
		material->setSpecularMaterialProperties(specularMaterialProperties);
	}
	view->reloadPrototype();
	specularMaterialProperties->setNormalTexture(
		string(),
		string()
	);
	updateMaterialDetails();
}

void ModelEditorTabController::onMaterialLoadSpecularTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties == nullptr) {
		specularMaterialProperties = new SpecularMaterialProperties();
		material->setSpecularMaterialProperties(specularMaterialProperties);
	}

	class OnLoadTexture: public virtual Action
	{
	public:
		void performAction() override {
			MutableString value;
			modelEditorTabController->view->reloadPrototype();
			specularMaterialProperties->setSpecularTexture(
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getPathName(),
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->updateMaterialDetails();
			modelEditorTabController->getModelPath()->setPath(
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getPathName()
			);
			modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param modelEditorTabController model editor tab controller
		 * @param specularMaterialProperties specular material properties
		 */
		OnLoadTexture(ModelEditorTabController* modelEditorTabController, SpecularMaterialProperties* specularMaterialProperties)
			: modelEditorTabController(modelEditorTabController)
			, specularMaterialProperties(specularMaterialProperties) {
		}


	private:
		ModelEditorTabController* modelEditorTabController;
		SpecularMaterialProperties* specularMaterialProperties;
	};

	auto extensions = TextureReader::getTextureExtensions();
	view->getPopUps()->getFileDialogScreenController()->show(
		specularMaterialProperties->getSpecularTextureFileName().empty() == false?specularMaterialProperties->getSpecularTexturePathName():modelPath.getPath(),
		"Load specular specular texture from: ",
		extensions,
		specularMaterialProperties->getSpecularTextureFileName(),
		true,
		new OnLoadTexture(this, specularMaterialProperties)
	);
}

void ModelEditorTabController::onMaterialClearSpecularTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto specularMaterialProperties = material->getSpecularMaterialProperties();
	if (specularMaterialProperties == nullptr) {
		specularMaterialProperties = new SpecularMaterialProperties();
		material->setSpecularMaterialProperties(specularMaterialProperties);
	}
	view->reloadPrototype();
	specularMaterialProperties->setSpecularTexture(
		string(),
		string()
	);
	updateMaterialDetails();
}

void ModelEditorTabController::onMaterialLoadPBRBaseColorTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	if (pbrMaterialProperties == nullptr) return;

	class OnLoadTexture: public virtual Action
	{
	public:
		void performAction() override {
			MutableString value;
			modelEditorTabController->view->reloadPrototype();
			pbrMaterialProperties->setBaseColorTexture(
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getPathName(),
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->updateMaterialDetails();
			modelEditorTabController->getModelPath()->setPath(
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getPathName()
			);
			modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param modelEditorTabController model editor tab controller
		 * @param specularMaterialProperties specular material properties
		 */
		OnLoadTexture(ModelEditorTabController* modelEditorTabController, PBRMaterialProperties* pbrMaterialProperties)
			: modelEditorTabController(modelEditorTabController)
			, pbrMaterialProperties(pbrMaterialProperties) {
		}


	private:
		ModelEditorTabController* modelEditorTabController;
		PBRMaterialProperties* pbrMaterialProperties;
	};

	auto extensions = TextureReader::getTextureExtensions();
	view->getPopUps()->getFileDialogScreenController()->show(
		pbrMaterialProperties->getBaseColorTextureFileName().empty() == false?pbrMaterialProperties->getBaseColorTexturePathName():modelPath.getPath(),
		"Load PBR base color texture from: ",
		extensions,
		pbrMaterialProperties->getBaseColorTextureFileName(),
		true,
		new OnLoadTexture(this, pbrMaterialProperties)
	);
}

void ModelEditorTabController::onMaterialClearPBRBaseColorTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	if (pbrMaterialProperties == nullptr) return;
	view->reloadPrototype();
	pbrMaterialProperties->setBaseColorTexture(
		string(),
		string()
	);
	updateMaterialDetails();
}

void ModelEditorTabController::onMaterialLoadPBRMetallicRoughnessTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	if (pbrMaterialProperties == nullptr) return;

	class OnLoadTexture: public virtual Action
	{
	public:
		void performAction() override {
			MutableString value;
			modelEditorTabController->view->reloadPrototype();
			pbrMaterialProperties->setMetallicRoughnessTexture(
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getPathName(),
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->updateMaterialDetails();
			modelEditorTabController->getModelPath()->setPath(
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getPathName()
			);
			modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param modelEditorTabController model editor tab controller
		 * @param specularMaterialProperties specular material properties
		 */
		OnLoadTexture(ModelEditorTabController* modelEditorTabController, PBRMaterialProperties* pbrMaterialProperties)
			: modelEditorTabController(modelEditorTabController)
			, pbrMaterialProperties(pbrMaterialProperties) {
		}


	private:
		ModelEditorTabController* modelEditorTabController;
		PBRMaterialProperties* pbrMaterialProperties;
	};

	auto extensions = TextureReader::getTextureExtensions();
	view->getPopUps()->getFileDialogScreenController()->show(
		pbrMaterialProperties->getMetallicRoughnessTextureFileName().empty() == false?pbrMaterialProperties->getMetallicRoughnessTexturePathName():modelPath.getPath(),
		"Load PBR metallic/roughness texture from: ",
		extensions,
		pbrMaterialProperties->getMetallicRoughnessTextureFileName(),
		true,
		new OnLoadTexture(this, pbrMaterialProperties)
	);
}

void ModelEditorTabController::onMaterialClearPBRMetallicRoughnessTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	if (pbrMaterialProperties == nullptr) return;
	view->reloadPrototype();
	pbrMaterialProperties->setMetallicRoughnessTexture(
		string(),
		string()
	);
	updateMaterialDetails();
}

void ModelEditorTabController::onMaterialLoadPBRNormalTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	if (pbrMaterialProperties == nullptr) return;

	class OnLoadTexture: public virtual Action
	{
	public:
		void performAction() override {
			MutableString value;
			modelEditorTabController->view->reloadPrototype();
			pbrMaterialProperties->setNormalTexture(
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getPathName(),
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getFileName()
			);
			modelEditorTabController->updateMaterialDetails();
			modelEditorTabController->getModelPath()->setPath(
				modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->getPathName()
			);
			modelEditorTabController->getView()->getPopUps()->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param modelEditorTabController model editor tab controller
		 * @param specularMaterialProperties specular material properties
		 */
		OnLoadTexture(ModelEditorTabController* modelEditorTabController, PBRMaterialProperties* pbrMaterialProperties)
			: modelEditorTabController(modelEditorTabController)
			, pbrMaterialProperties(pbrMaterialProperties) {
		}


	private:
		ModelEditorTabController* modelEditorTabController;
		PBRMaterialProperties* pbrMaterialProperties;
	};

	auto extensions = TextureReader::getTextureExtensions();
	view->getPopUps()->getFileDialogScreenController()->show(
		pbrMaterialProperties->getNormalTextureFileName().empty() == false?pbrMaterialProperties->getNormalTexturePathName():modelPath.getPath(),
		"Load PBR normal texture from: ",
		extensions,
		pbrMaterialProperties->getNormalTextureFileName(),
		true,
		new OnLoadTexture(this, pbrMaterialProperties)
	);
}

void ModelEditorTabController::onMaterialClearPBRNormalTexture() {
	auto material = getSelectedMaterial();
	if (material == nullptr) return;
	auto pbrMaterialProperties = material->getPBRMaterialProperties();
	if (pbrMaterialProperties == nullptr) return;
	view->reloadPrototype();
	pbrMaterialProperties->setNormalTexture(
		string(),
		string()
	);
	updateMaterialDetails();
}

void ModelEditorTabController::onValueChanged(GUIElementNode* node)
{
	auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
	if (node->getId() == "selectbox_outliner") {
		updateDetails(outlinerNode);
	}
	for (auto& applyAnimationNode: applyAnimationNodes) {
		if (node->getId() == applyAnimationNode) {
			auto animationId = StringTools::substring(outlinerNode, string("model.animations.").size(), outlinerNode.size());
			applyAnimationDetails(animationId);
		}
	}
	for (auto& applySpecularMaterialNode: applySpecularMaterialNodes) {
		if (node->getId() == applySpecularMaterialNode) {
			applySpecularMaterialDetails();
			break;
		}
	}
	for (auto& applyPBRMaterialNode: applyPBRMaterialNodes) {
		if (node->getId() == applyPBRMaterialNode) {
			applyPBRMaterialDetails();
			break;
		}
	}
	prototypeBaseSubController->onValueChanged(node, view->getPrototype());
	prototypeDisplaySubController->onValueChanged(node, view->getPrototype());
	prototypePhysicsSubController->onValueChanged(node, view->getPrototype());
	{
		Model* model = view->getLodLevel() == 1?view->getPrototype()->getModel():getLODLevel(view->getLodLevel())->getModel();
		if (model != nullptr) prototypeSoundsSubController->onValueChanged(node, view->getPrototype(), model);
	}
}

void ModelEditorTabController::onFocus(GUIElementNode* node) {
	prototypeBaseSubController->onFocus(node, view->getPrototype());
	prototypeSoundsSubController->onFocus(node, view->getPrototype());
}

void ModelEditorTabController::onUnfocus(GUIElementNode* node) {
	prototypeBaseSubController->onUnfocus(node, view->getPrototype());
	prototypeSoundsSubController->onUnfocus(node, view->getPrototype());
}

void ModelEditorTabController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
	auto prototype = view->getPrototype();
	prototypeBaseSubController->onActionPerformed(type, node, prototype);
	prototypeDisplaySubController->onActionPerformed(type, node, prototype);
	prototypePhysicsSubController->onActionPerformed(type, node, prototype);
	prototypeSoundsSubController->onActionPerformed(type, node, prototype);
	if (type == GUIActionListenerType::PERFORMED) {
		if (node->getId().compare("specularmaterial_diffuse_texture_open") == 0) {
			onMaterialLoadDiffuseTexture();
		} else
		if (node->getId().compare("specularmaterial_diffuse_texture_remove") == 0) {
			onMaterialClearDiffuseTexture();
		} else
		if (node->getId().compare("specularmaterial_transparency_texture_open") == 0) {
			onMaterialLoadDiffuseTransparencyTexture();
		} else
		if (node->getId().compare("specularmaterial_transparency_texture_remove") == 0) {
			onMaterialClearDiffuseTransparencyTexture();
		} else
		if (node->getId().compare("specularmaterial_normal_texture_open") == 0) {
			onMaterialLoadNormalTexture();
		} else
		if (node->getId().compare("specularmaterial_normal_texture_remove") == 0) {
			onMaterialClearNormalTexture();
		} else
		if (node->getId().compare("specularmaterial_specular_texture_open") == 0) {
			onMaterialLoadSpecularTexture();
		} else
		if (node->getId().compare("specularmaterial_specular_texture_remove") == 0) {
			onMaterialClearSpecularTexture();
		} else
		if (node->getId().compare("pbrmaterial_basecolor_texture_open") == 0) {
			onMaterialLoadPBRBaseColorTexture();
		} else
		if (node->getId().compare("pbrmaterial_basecolor_texture_remove") == 0) {
			onMaterialClearPBRBaseColorTexture();
		} else
		if (node->getId().compare("pbrmaterial_metallic_roughness_texture_open") == 0) {
			onMaterialLoadPBRMetallicRoughnessTexture();
		} else
		if (node->getId().compare("pbrmaterial_metallic_roughness_texture_remove") == 0) {
			onMaterialClearPBRMetallicRoughnessTexture();
		} else
		if (node->getId().compare("pbrmaterial_normal_texture_open") == 0) {
			onMaterialLoadPBRNormalTexture();
		} else
		if (node->getId().compare("pbrmaterial_normal_texture_remove") == 0) {
			onMaterialClearPBRNormalTexture();
		}
		/*
		if (node->getId().compare("button_model_load") == 0) {
			onModelLoad();
		} else
		if (node->getId().compare("button_model_reload") == 0) {
			onModelReload();
		} else
		if (node->getId().compare("button_model_reimport") == 0) {
			onModelReimport();
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
		if (node->getId().compare("button_shaderparameters_apply") == 0) {
			onShaderParametersApply();
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
		if (node->getId().compare("button_materials_material_pbr_base_color_texture_load") == 0) {
			onMaterialLoadPBRBaseColorTexture();
		} else
		if (node->getId().compare("button_materials_material_pbr_base_color_texture_clear") == 0) {
			onMaterialClearTexture(materialsMaterialPBRBaseColorTexture);
		} else
		if (node->getId().compare("button_materials_material_pbr_metallic_roughness_texture_load") == 0) {
			onMaterialLoadPBRMetallicRoughnessTexture();
		} else
		if (node->getId().compare("button_materials_material_pbr_metallic_roughness_texture_clear") == 0) {
			onMaterialClearTexture(materialsMaterialPBRMetallicRoughnessTexture);
		} else
		if (node->getId().compare("button_materials_material_pbr_normal_texture_load") == 0) {
			onMaterialLoadPBRNormalTexture();
		} else
		if (node->getId().compare("button_materials_material_pbr_normal_texture_clear") == 0) {
			onMaterialClearTexture(materialsMaterialPBRNormalTexture);
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
		if (node->getId().compare("preview_animations_attachment1_model_load") == 0) {
			onPreviewAnimationsAttachment1ModelLoad();
		} else
		if (node->getId().compare("preview_animations_attachment1_model_clear") == 0) {
			onPreviewAnimationsAttachment1ModelClear();
		} else
		if (node->getId().compare("button_preview_apply") == 0) {
			onPreviewApply();
		} else
		if (node->getId().compare("button_tools_computenormals") == 0) {
			onToolsComputeNormal();
		} else
		if (node->getId().compare("button_tools_optimizemodel") == 0) {
			onToolsOptimizeModel();
		}
		*/
	}
}
