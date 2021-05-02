#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/ShaderParameter.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/tools/editor/misc/FileDialogPath.h>
#include <tdme/tools/editor/misc/FileDialogPath.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::map;
using std::string;
using std::vector;

using tdme::engine::model::Material;
using tdme::engine::model::Node;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeLODLevel;
using tdme::engine::ShaderParameter;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::math::Vector3;
using tdme::tools::editor::misc::FileDialogPath;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeBaseSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeDisplaySubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeSoundsSubController;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::ModelEditorTabView;
using tdme::utilities::MutableString;

/**
 * Model editor screen controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::editor::tabcontrollers::ModelEditorTabController final
	: public TabController
{

private:
	PrototypeBaseSubController* prototypeBaseSubController { nullptr };
	PrototypeDisplaySubController* prototypeDisplaySubController { nullptr };
	PrototypePhysicsSubController* prototypePhysicsSubController { nullptr };
	PrototypeSoundsSubController* prototypeSoundsSubController { nullptr };
	ModelEditorTabView* view { nullptr };
	GUIScreenNode* screenNode { nullptr };
	GUITextNode* screenCaption { nullptr };
	GUIElementNode* modelReload { nullptr };
	GUIElementNode* modelReimport { nullptr };
	GUIElementNode* modelSave { nullptr };
	GUIElementNode* pivotX { nullptr };
	GUIElementNode* pivotY { nullptr };
	GUIElementNode* pivotZ { nullptr };
	GUIElementNode* pivotApply { nullptr };
	GUIElementNode* renderingContributesShadows { nullptr };
	GUIElementNode* renderingReceivesShadows { nullptr };
	GUIElementNode* renderingRenderGroups { nullptr };
	GUIElementNode* renderingShader { nullptr };
	GUIElementNode* renderingDistanceShader { nullptr };
	GUIElementNode* renderingDistanceShaderDistance { nullptr };
	GUIElementNode* renderingApply { nullptr };
	GUIParentNode* shaderParametersContent { nullptr };
	GUIElementNode* lodLevel { nullptr };
	GUIElementNode* lodLevelApply { nullptr };
	GUIElementNode* lodType { nullptr };
	GUIElementNode* lodModelFile { nullptr };
	GUIElementNode* lodModelFileLoad { nullptr };
	GUIElementNode* lodModelFileClear { nullptr };
	GUIElementNode* lodMinDistance { nullptr };
	GUIElementNode* lodColorMul { nullptr };
	GUIElementNode* lodColorAdd { nullptr };
	GUIElementNode* buttonLodApply { nullptr };
	GUIElementNode* materialsDropdown { nullptr };
	GUIElementNode* materialsDropdownApply { nullptr };
	GUIElementNode* materialsMaterialName { nullptr };
	GUIElementNode* materialsMaterialDoubleSided { nullptr };
	GUIElementNode* materialsMaterialAmbient { nullptr };
	GUIElementNode* materialsMaterialDiffuse { nullptr };
	GUIElementNode* materialsMaterialSpecular { nullptr };
	GUIElementNode* materialsMaterialEmission { nullptr };
	GUIElementNode* materialsMaterialShininess { nullptr };
	GUIElementNode* materialsMaterialReflection { nullptr };
	GUIElementNode* materialsMaterialDiffuseTexture { nullptr };
	GUIElementNode* materialsMaterialDiffuseTransparencyTexture { nullptr };
	GUIElementNode* materialsMaterialNormalTexture { nullptr };
	GUIElementNode* materialsMaterialSpecularTexture { nullptr };
	GUIElementNode* materialsMaterialDiffuseTextureLoad { nullptr };
	GUIElementNode* materialsMaterialDiffuseTransparencyTextureLoad { nullptr };
	GUIElementNode* materialsMaterialNormalTextureLoad { nullptr };
	GUIElementNode* materialsMaterialSpecularTextureLoad { nullptr };
	GUIElementNode* materialsMaterialDiffuseTextureClear { nullptr };
	GUIElementNode* materialsMaterialDiffuseTransparencyTextureClear { nullptr };
	GUIElementNode* materialsMaterialNormalTextureClear { nullptr };
	GUIElementNode* materialsMaterialSpecularTextureClear { nullptr };
	GUIElementNode* materialsMaterialPBREnabled { nullptr };
	GUIElementNode* materialsMaterialPBRBaseColorFactor { nullptr };
	GUIElementNode* materialsMaterialPBRBaseColorTexture { nullptr };
	GUIElementNode* materialsMaterialPBRBaseColorTextureLoad { nullptr };
	GUIElementNode* materialsMaterialPBRBaseColorTextureClear { nullptr };
	GUIElementNode* materialsMaterialPBRMetallicFactor { nullptr };
	GUIElementNode* materialsMaterialPBRRoughnessFactor { nullptr };
	GUIElementNode* materialsMaterialPBRMetallicRoughnessTexture { nullptr };
	GUIElementNode* materialsMaterialPBRMetallicRoughnessTextureLoad { nullptr };
	GUIElementNode* materialsMaterialPBRMetallicRoughnessTextureClear { nullptr };
	GUIElementNode* materialsMaterialPBRNormalScale { nullptr };
	GUIElementNode* materialsMaterialPBRNormalTexture { nullptr };
	GUIElementNode* materialsMaterialPBRNormalTextureLoad { nullptr };
	GUIElementNode* materialsMaterialPBRNormalTextureClear { nullptr };
	GUIElementNode* materialsMaterialPBRExposure { nullptr };
	GUIElementNode* materialsMaterialUseMaskedTransparency { nullptr };
	GUIElementNode* materialsMaterialMaskedTransparencyThreshold { nullptr };
	GUIElementNode* materialsMaterialApply { nullptr };
	GUIElementNode* animationsDropDown { nullptr };
	GUIElementNode* animationsDropDownApply { nullptr };
	GUIElementNode* animationsDropDownDelete { nullptr };
	GUIElementNode* animationsAnimationStartFrame { nullptr };
	GUIElementNode* animationsAnimationEndFrame { nullptr };
	GUIElementNode* animationsAnimationOverlayFromNodeIdDropDown { nullptr };
	GUIElementNode* animationsAnimationLoop { nullptr };
	GUIElementNode* animationsAnimationSpeed { nullptr };
	GUIElementNode* animationsAnimationName { nullptr };
	GUIElementNode* animationsAnimationApply { nullptr };
	GUIElementNode* previewAnimationsBaseDropDown { nullptr };
	GUIElementNode* previewAnimationsOverlay1DropDown { nullptr };
	GUIElementNode* previewAnimationsOverlay2DropDown { nullptr };
	GUIElementNode* previewAnimationsOverlay3DropDown { nullptr };
	GUIElementNode* previewAnimationsAttachment1BoneDropdown { nullptr };
	GUIElementNode* previewAnimationsAttachment1ModelModel { nullptr };
	GUIElementNode* previewAnimationsAttachment1ModelLoad { nullptr };
	GUIElementNode* previewAnimationsAttachment1ModelClear { nullptr };
	GUIElementNode* buttonPreviewApply { nullptr };
	GUIElementNode* buttonToolsComputeNormals { nullptr };
	GUIElementNode* buttonToolsOptimizeModel { nullptr };
	GUIElementNode* statsOpaqueFaces { nullptr };
	GUIElementNode* statsTransparentFaces { nullptr };
	GUIElementNode* statsMaterialCount { nullptr };
	GUIElementNode* viewPort { nullptr };

	FileDialogPath modelPath;
	FileDialogPath audioPath;

	/**
	 * @return prototype lod level or nullptr
	 */
	PrototypeLODLevel* getLODLevel(int level);

	/**
	 * @return current selected material
	 */
	Material* getSelectedMaterial();

	/**
	 * Create outliner model nodes xml
	 */
	void createOutlinerModelNodesXML(const map<string, Node*>& subNodes, string& xml);

public:
	/**
	 * Public constructor
	 * @param view view
	 */
	ModelEditorTabController(ModelEditorTabView* view);

	/**
	 * Destructor
	 */
	virtual ~ModelEditorTabController();

	/**
	 * Get view
	 */
	ModelEditorTabView* getView();

	/**
	 * @return prototype display sub screen controller
	 */
	PrototypeDisplaySubController* getPrototypeDisplaySubController();

	/**
	 * @return prototype bounding volume sub screen controller
	 */
	PrototypePhysicsSubController* getPrototypePhysicsSubController();

	/**
	 * @return prototype sounds sub screen controller
	 */
	PrototypeSoundsSubController* getPrototypeSoundsSubController();

	// overridden method
	GUIScreenNode* getScreenNode() override;

	/**
	 * @return model path
	 */
	FileDialogPath* getModelPath();

	/**
	 * @return audio path
	 */
	FileDialogPath* getAudioPath();

	// overridden methods
	void initialize(GUIScreenNode* screenNode) override;
	void dispose() override;

	/**
	 * Set screen caption
	 * @param text text
	 */
	void setScreenCaption(const string& text);

	/**
	 * Set outliner content
	 */
	void setOutlinerContent();

	/**
	 * Set details content
	 */
	void setDetailsContent();

	/**
	 * Set up general prototype data
	 * @param name name
	 * @param description description
	 */
	void setPrototypeData(const string& name, const string& description);

	/**
	 * Unset prototype data
	 */
	void unsetPrototypeData();

	/**
	 * Set up prototype properties
	 * @param presetId preset id
	 * @param selectedName selected name
	 */
	void setPrototypeProperties(const string& presetId, const string& selectedName);

	/**
	 * Unset prototype properties
	 */
	void unsetPrototypeProperties();

	/**
	 * Set pivot tab
	 * @param pivot pivot
	 */
	void setPivot(const Vector3& pivot);

	/**
	 * Unset pivot tab
	 */
	void unsetPivot();

	/**
	 * Set rendering shader
	 * @param shaders shaders
	 */
	void setRenderingShaders(const vector<string>& shaders);

	/**
	 * Set renering options
	 */
	void setRendering();

	/**
	 * Unset rendering
	 */
	void unsetRendering();

	/**
	 * Set shader parameters
	 */
	void setShaderParameters();

	/**
	 * Unset shader parameters
	 */
	void unsetShaderParameters();

	/**
	 * Set lod level
	 * @param level lod level
	 */
	void setLODLevel(int level);

	/**
	 * Unset LOD level
	 */
	void unsetLODLevel();

	/**
	 * On LOD level apply
	 */
	void onLODLevelApply();

	/**
	 * On LOD level load model
	 */
	void onLODLevelLoadModel();

	/**
	 * On LOD level clear model
	 */
	void onLODLevelClearModel();

	/**
	 * On LOD level apply settings
	 */
	void onLODLevelApplySettings();

	/**
	 * Set materials
	 */
	void setMaterials();

	/**
	 * Unset materials
	 */
	void unsetMaterials();

	/**
	 * On material drop down apply
	 */
	void onMaterialDropDownApply();

	Material* getCurrentMaterial();

	/**
	 * On material apply
	 */
	void onMaterialApply();

	/**
	 * On material load diffuse texture
	 */
	void onMaterialLoadDiffuseTexture();

	/**
	 * On material load diffuse transparency texture
	 */
	void onMaterialLoadDiffuseTransparencyTexture();

	/**
	 * On material load normal texture
	 */
	void onMaterialLoadNormalTexture();

	/**
	 * On material load specular texture
	 */
	void onMaterialLoadSpecularTexture();

	/**
	 * On material load PBR base color texture
	 */
	void onMaterialLoadPBRBaseColorTexture();

	/**
	 * On material load PBR metallic roughness texture
	 */
	void onMaterialLoadPBRMetallicRoughnessTexture();

	/**
	 * On material load PBR normal texture
	 */
	void onMaterialLoadPBRNormalTexture();

	/**
	 * On material PBR enabled value changed
	 */
	void onMaterialPBREnabledValueChanged();

	/**
	 * On material clear texture
	 */
	void onMaterialClearTexture(GUIElementNode* guiElementNode);

	/**
	 * Set animations
	 */
	void setAnimations();

	/**
	 * On animation drop down value changed
	 */
	void onAnimationDropDownValueChanged();

	/**
	 * On animation drop down apply
	 */
	void onAnimationDropDownApply();

	/**
	 * On animation drop down delete
	 */
	void onAnimationDropDownDelete();

	/**
	 * On animation apply
	 */
	void onAnimationApply();

	/**
	 * Unset animations
	 */
	void unsetAnimations();

	/**
	 * Set preview
	 */
	void setPreview();

	/**
	 * On preview apply
	 */
	void onPreviewApply();

	/**
	 * On preview animations attachment 1 model load
	 */
	void onPreviewAnimationsAttachment1ModelLoad();

	/**
	 * On preview animations attachment 1 model clear
	 */
	void onPreviewAnimationsAttachment1ModelClear();

	/**
	 * Unset preview
	 */
	void unsetPreview();

	/**
	 * Set up model statistics
	 * @param statsOpaqueFaces stats opaque faces
	 * @param statsTransparentFaces stats transparent faces
	 * @param statsMaterialCount stats material count
	 */
	void setStatistics(int statsOpaqueFaces, int statsTransparentFaces, int statsMaterialCount);

	/**
	 * Unset statistics
	 */
	void unsetStatistics();

	/**
	 * Set up tool
	 */
	void setTools();

	/**
	 * Unset tools
	 */
	void unsetTools();

	/**
	 * On model load
	 */
	void onModelLoad();

	/**
	 * On model save
	 */
	void onModelSave();

	/**
	 * On model reload
	 */
	void onModelReload();

	/**
	 * On model reload
	 */
	void onModelReimport();

	/**
	 * On pivot apply
	 */
	void onPivotApply();

	/**
	 * On rendering apply
	 */
	void onRenderingApply();

	/**
	 * On shader parameters apply
	 */
	void onShaderParametersApply();

	/**
	 * On tools compute normals
	 */
	void onToolsComputeNormal();

	/**
	 * On tools optimize model
	 */
	void onToolsOptimizeModel();

	/**
	 * Save file
	 * @param pathName path name
	 * @param fileName file name
	 */
	void saveFile(const string& pathName, const string& fileName);

	/**
	 * Load file
	 * @param pathName path name
	 * @param fileName file name
	 */
	void loadFile(const string& pathName, const string& fileName);

	/**
	 * Set material details
	 * @param materialId material Id
	 */
	void setMaterialDetails(const string& materialId);

	/**
	 * Set animation details
	 * @param animationId animation Id
	 */
	void setAnimationDetails(const string& animationId);

	/**
	 * Set sound details
	 * @param soundId sound Id
	 */
	void setSoundDetails(const string& soundId);

	/**
	 * Update details panel
	 * @param outlinerNode outliner node
	 */
	void updateDetails(const string& outlinerNode);

	/**
	 * On value changed
	 * @param node node
	 */
	void onValueChanged(GUIElementNode* node) override;

	/**
	 * On action performed
	 * @param type type
	 * @param node node
	 */
	void onActionPerformed(GUIActionListenerType type, GUIElementNode* node) override;

	/**
	 * Shows the error pop up
	 * @param caption caption
	 * @param message message
	 */
	void showErrorPopUp(const string& caption, const string& message);

	/**
	 * On quit
	 */
	void onQuit();

};
