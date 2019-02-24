#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/tools/shared/controller/ScreenController.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>

using std::string;

using tdme::engine::model::Material;
using tdme::tools::shared::controller::ScreenController;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::math::Vector3;
using tdme::tools::shared::controller::EntityBaseSubScreenController;
using tdme::tools::shared::controller::EntityDisplaySubScreenController;
using tdme::tools::shared::controller::EntityPhysicsSubScreenController;
using tdme::tools::shared::controller::EntitySoundsSubScreenController;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityLODLevel;
using tdme::tools::shared::views::SharedModelEditorView;
using tdme::utils::MutableString;

/** 
 * Model editor screen controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::controller::ModelEditorScreenController final
	: public ScreenController
	, public GUIActionListener
	, public GUIChangeListener
{

private:
	EntityBaseSubScreenController* entityBaseSubScreenController {  };
	EntityDisplaySubScreenController* entityDisplaySubScreenController {  };
	EntityPhysicsSubScreenController* entityPhysicsSubScreenController {  };
	EntitySoundsSubScreenController* entitySoundsSubScreenController {  };
	SharedModelEditorView* view {  };
	GUIScreenNode* screenNode {  };
	GUITextNode* screenCaption {  };
	GUIElementNode* modelReload {  };
	GUIElementNode* modelSave {  };
	GUIElementNode* pivotX {  };
	GUIElementNode* pivotY {  };
	GUIElementNode* pivotZ {  };
	GUIElementNode* pivotApply {  };
	GUIElementNode* renderingDynamicShadowing {  };
	GUIElementNode* renderingRenderGroups {  };
	GUIElementNode* renderingShader {  };
	GUIElementNode* renderingDistanceShader {  };
	GUIElementNode* renderingDistanceShaderDistance {  };
	GUIElementNode* renderingApply {  };
	GUIElementNode* lodLevel {  };
	GUIElementNode* lodLevelApply {  };
	GUIElementNode* lodType {  };
	GUIElementNode* lodModelFile {  };
	GUIElementNode* lodModelFileLoad {  };
	GUIElementNode* lodModelFileClear {  };
	GUIElementNode* lodMinDistance {  };
	GUIElementNode* lodColorMul {  };
	GUIElementNode* lodColorAdd {  };
	GUIElementNode* buttonLodApply {  };
	GUIElementNode* materialsDropdown {  };
	GUIElementNode* materialsDropdownApply {  };
	GUIElementNode* materialsMaterialName {  };
	GUIElementNode* materialsMaterialAmbient {  };
	GUIElementNode* materialsMaterialDiffuse {  };
	GUIElementNode* materialsMaterialSpecular {  };
	GUIElementNode* materialsMaterialEmission {  };
	GUIElementNode* materialsMaterialShininess {  };
	GUIElementNode* materialsMaterialDiffuseTexture {  };
	GUIElementNode* materialsMaterialDiffuseTransparencyTexture {  };
	GUIElementNode* materialsMaterialNormalTexture {  };
	GUIElementNode* materialsMaterialSpecularTexture {  };
	GUIElementNode* materialsMaterialDiffuseTextureLoad {  };
	GUIElementNode* materialsMaterialDiffuseTransparencyTextureLoad {  };
	GUIElementNode* materialsMaterialNormalTextureLoad {  };
	GUIElementNode* materialsMaterialSpecularTextureLoad {  };
	GUIElementNode* materialsMaterialDiffuseTextureClear {  };
	GUIElementNode* materialsMaterialDiffuseTransparencyTextureClear {  };
	GUIElementNode* materialsMaterialNormalTextureClear {  };
	GUIElementNode* materialsMaterialSpecularTextureClear {  };
	GUIElementNode* materialsMaterialUseMaskedTransparency {  };
	GUIElementNode* materialsMaterialMaskedTransparencyThreshold {  };
	GUIElementNode* materialsMaterialApply {  };
	GUIElementNode* animationsDropDown {  };
	GUIElementNode* animationsDropDownApply {  };
	GUIElementNode* animationsDropDownDelete {  };
	GUIElementNode* animationsAnimationStartFrame {  };
	GUIElementNode* animationsAnimationEndFrame {  };
	GUIElementNode* animationsAnimationOverlayFromGroupIdDropDown {  };
	GUIElementNode* animationsAnimationLoop {  };
	GUIElementNode* animationsAnimationName {  };
	GUIElementNode* animationsAnimationApply {  };
	GUIElementNode* buttonToolsComputeNormals {  };
	GUIElementNode* statsOpaqueFaces {  };
	GUIElementNode* statsTransparentFaces {  };
	GUIElementNode* statsMaterialCount {  };

	FileDialogPath* modelPath {  };
	FileDialogPath* audioPath {  };

	/**
	 * @return level editor entity lod level or nullptr
	 */
	LevelEditorEntityLODLevel* getLODLevel(int level);

	/**
	 * @return current selected material
	 */
	Material* getSelectedMaterial();
public:

	/**
	 * Get view
	 */
	SharedModelEditorView* getView();

	/** 
	 * @return entity display sub screen controller
	 */
	EntityDisplaySubScreenController* getEntityDisplaySubScreenController();

	/** 
	 * @return entity bounding volume sub screen controller
	 */
	EntityPhysicsSubScreenController* getEntityPhysicsSubScreenController();

	/**
	 * @return entity sounds sub screen controller
	 */
	EntitySoundsSubScreenController* getEntitySoundsSubScreenController();

	// overriden method
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
	void initialize() override;
	void dispose() override;

	/** 
	 * Set screen caption
	 * @param text text
	 */
	void setScreenCaption(const string& text);

	/** 
	 * Set up general entity data
	 * @param name name
	 * @param description description
	 */
	void setEntityData(const string& name, const string& description);

	/** 
	 * Unset entity data
	 */
	void unsetEntityData();

	/** 
	 * Set up entity properties
	 * @param presetId preset id
	 * @param entity entity properties
	 * @param selectedName selected name
	 */
	void setEntityProperties(const string& presetId, LevelEditorEntity* entity, const string& selectedName);

	/** 
	 * Unset entity properties
	 */
	void unsetEntityProperties();

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
	 * Set renering options
	 * @param entity entity
	 */
	void setRendering(LevelEditorEntity* entity);

	/**
	 * Unset rendering
	 */
	void unsetRendering();

	/**
	 * Set lod level
	 * @param entity entity
	 * @param level lod level
	 */
	void setLODLevel(LevelEditorEntity* entity, int level);

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
	 * @param entity entity
	 */
	void setMaterials(LevelEditorEntity* entity);

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
	 * On material clear texture
	 */
	void onMaterialClearTexture(GUIElementNode* guiElementNode);

	/**
	 * Set animations
	 */
	void setAnimations(LevelEditorEntity* entity);

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
	 * Set up model statistics
	 * @param statsOpaqueFaces stats opaque faces
	 * @param statsTransparentFaces stats transparent faces
	 * @param statsMaterialCount stats material count
	 */
	void setStatistics(int32_t statsOpaqueFaces, int32_t statsTransparentFaces, int32_t statsMaterialCount);

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
	 * On quit
	 */
	void onQuit();

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
	 * On pivot apply
	 */
	void onPivotApply();

	/**
	 * On rendering apply
	 */
	void onRenderingApply();

	/**
	 * On tools compute normals
	 */
	void onToolsComputeNormal();

	/**
	 * Save file
	 * @param pathName path name
	 * @param fileName file name
	 */
	void saveFile(const string& pathName, const string& fileName) /* throws(Exception) */;

	/**
	 * Load file
	 * @param pathName path name
	 * @param fileName file name
	 */
	void loadFile(const string& pathName, const string& fileName) /* throws(Exception) */;

	/** 
	 * Shows the error pop up
	 */
	void showErrorPopUp(const string& caption, const string& message);

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
	void onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node) override;

	/**
	 * Public constructor
	 * @param view view
	 */
	ModelEditorScreenController(SharedModelEditorView* view);

	/**
	 * Destructor
	 */
	virtual ~ModelEditorScreenController();
};
