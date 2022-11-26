#pragma once

#include <array>
#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/ShaderParameter.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/events/GUIContextMenuRequestListener.h>
#include <tdme/gui/events/GUIFocusListener.h>
#include <tdme/gui/events/GUITooltipRequestListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <tdme/utilities/MutableString.h>

using std::array;
using std::map;
using std::string;
using std::vector;

using tdme::engine::model::AnimationSetup;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeLODLevel;
using tdme::engine::ShaderParameter;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::events::GUIContextMenuRequestListener;
using tdme::gui::events::GUIFocusListener;
using tdme::gui::events::GUITooltipRequestListener;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::math::Vector3;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::subcontrollers::BasePropertiesSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeDisplaySubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeScriptSubController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeSoundsSubController;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::ModelEditorTabView;
using tdme::utilities::MutableString;

/**
 * Model editor tab controller
 * @author Andreas Drewke
 */
class tdme::tools::editor::tabcontrollers::ModelEditorTabController final
	: public TabController
{

private:
	BasePropertiesSubController* basePropertiesSubController { nullptr };
	PrototypeDisplaySubController* prototypeDisplaySubController { nullptr };
	PrototypePhysicsSubController* prototypePhysicsSubController { nullptr };
	PrototypeSoundsSubController* prototypeSoundsSubController { nullptr };
	PrototypeScriptSubController* prototypeScriptSubController { nullptr };
	ModelEditorTabView* view { nullptr };
	GUIScreenNode* screenNode { nullptr };
	PopUps* popUps { nullptr };

	array<string, 5> applyAnimationNodes = {
		"animation_startframe",
		"animation_endframe",
		"animation_speed",
		"animation_loop",
		"animation_overlaybone"
	};

	array<string, 3> applyMaterialBaseNodes = {
		"material_specular_embedtextures_enabled",
		"material_pbr_embedtextures_enabled",
		"material_lightningmodel"
	};

	array<string, 3> applySpecularMaterialNodes = {
		"specularmaterial_shininess",
		"specularmaterial_reflection",
		"specularmaterial_maskedtransparency"
	};

	array<string, 6> applyPBRMaterialNodes = {
		"pbrmaterial_metallic_factor",
		"pbrmaterial_roughness_factor",
		"pbrmaterial_normal_scale",
		"pbrmaterial_exposure",
		"pbrmaterial_maskedtransparency"
	};

	array<string, 5> applyAnimationPreviewNodes = {
		"animationpreview_base",
		"animationpreview_overlay1",
		"animationpreview_overlay2",
		"animationpreview_overlay3",
		"animationpreview_attachment1_bone"
	};

	array<string, 4> applyLODNodes = {
		"lod_min_distance",
	};

	string renameAnimationId;
	int renameAnimationLOD { -1 };

	string attachment1ModelFileName;

	/**
	 * Get LOD level
	 * @return created or existing LOD level with given level
	 */
	PrototypeLODLevel* getLODLevel(int level);

	/**
	 * @return prototype lod level or nullptr
	 */
	Model* getLODLevelModel(int level);

	/**
	 * @return current selected model
	 */
	Model* getSelectedModel();

	/**
	 * @return current selected material
	 */
	Material* getSelectedMaterial();

	/**
	 * @return current selected animation setup
	 */
	AnimationSetup* getSelectedAnimationSetup();

	/**
	 * Create outliner model nodes xml
	 * @param prefix prefix
	 * @param subNodes sub nodes
	 * @param xml xml
	 */
	void createOutlinerModelNodesXML(const string& prefix, const map<string, Node*>& subNodes, string& xml);

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
	inline PrototypeDisplaySubController* getPrototypeDisplaySubController() {
		return prototypeDisplaySubController;
	}

	/**
	 * @return prototype bounding volume sub screen controller
	 */
	inline PrototypePhysicsSubController* getPrototypePhysicsSubController() {
		return prototypePhysicsSubController;
	}

	/**
	 * @return prototype sounds sub screen controller
	 */
	inline PrototypeSoundsSubController* getPrototypeSoundsSubController() {
		return prototypeSoundsSubController;
	}

	// overridden method
	GUIScreenNode* getScreenNode() override;

	// overridden methods
	void initialize(GUIScreenNode* screenNode) override;
	void dispose() override;

	/**
	 * Set outliner content
	 */
	void setOutlinerContent();

	/**
	 * Set outliner add drop down content
	 */
	void setOutlinerAddDropDownContent();

	/**
	 * Set details content
	 */
	void setDetailsContent();

	/**
	 * @return current material
	 */
	Material* getCurrentMaterial();

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
	 * On model reload
	 */
	void onModelReload();

	/**
	 * On model load
	 */
	void onModelLoad();

	/**
	 * On model reload
	 */
	void onModelReimport();

	/**
	 * On LOD load
	 */
	void onLODLoad(int lodLevel);

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
	 * Set material base details
	 */
	void setMaterialBaseDetails();

	/**
	 * Update material base details
	 */
	void updateMaterialBaseDetails();

	/**
	 * Apply material base details
	 */
	void applyMaterialBaseDetails();

	/**
	 * Set material details
	 */
	void setMaterialDetails();

	/**
	 * Update material details
	 */
	void updateMaterialDetails();

	/**
	 * Update material color details
	 */
	void updateMaterialColorDetails();

	/**
	 * Apply specular material details
	 */
	void applySpecularMaterialDetails();

	/**
	 * Apply PBR material details
	 */
	void applyPBRMaterialDetails();

	/**
	 * Set animation details
	 */
	void setAnimationDetails();

	/**
	 * Apply animation details
	 */
	void applyAnimationDetails();

	/**
	 * Set animation preview details
	 */
	void setAnimationPreviewDetails();

	/**
	 * Apply animation preview details
	 */
	void applyAnimationPreviewDetails();

	/**
	 * Update details panel
	 * @param outlinerNode outliner node
	 */
	void updateDetails(const string& outlinerNode);

	/**
	 * Set material diffuse texture
	 * @param fileName file name
	 */
	void setMaterialDiffuseTexture(const string& fileName);

	/**
	 * On material load diffuse texture
	 */
	void onMaterialLoadDiffuseTexture();

	/**
	 * On material clear diffuse texture
	 */
	void onMaterialClearDiffuseTexture();

	/**
	 * On material browse to diffuse texture
	 */
	void onMaterialBrowseToDiffuseTexture();

	/**
	 * Set material diffuse transparency texture
	 * @param fileName file name
	 */
	void setMaterialDiffuseTransparencyTexture(const string& fileName);

	/**
	 * On material load diffuse transparency texture
	 */
	void onMaterialLoadDiffuseTransparencyTexture();

	/**
	 * On material clear diffuse transparency texture
	 */
	void onMaterialClearDiffuseTransparencyTexture();

	/**
	 * On material browse to diffuse transparency texture
	 */
	void onMaterialBrowseToDiffuseTransparencyTexture();

	/**
	 * Set material normal texture
	 * @param fileName file name
	 */
	void setMaterialNormalTexture(const string& fileName);

	/**
	 * On material load normal texture
	 */
	void onMaterialLoadNormalTexture();

	/**
	 * On material clear normal texture
	 */
	void onMaterialClearNormalTexture();

	/**
	 * On material browse to normal texture
	 */
	void onMaterialBrowseToNormalTexture();

	/**
	 * Set material specular texture
	 * @param fileName file name
	 */
	void setMaterialSpecularTexture(const string& fileName);

	/**
	 * On material load specular texture
	 */
	void onMaterialLoadSpecularTexture();

	/**
	 * On material clear specular texture
	 */
	void onMaterialClearSpecularTexture();

	/**
	 * On material browse to specular texture
	 */
	void onMaterialBrowseToSpecularTexture();

	/**
	 * Set material PBR base color texture
	 * @param fileName file name
	 */
	void setMaterialPBRBaseColorTexture(const string& fileName);

	/**
	 * On material load PBR base color texture
	 */
	void onMaterialLoadPBRBaseColorTexture();

	/**
	 * On material clear PBR base color texture
	 */
	void onMaterialClearPBRBaseColorTexture();

	/**
	 * On material browse to PBR base color texture
	 */
	void onMaterialBrowseToPBRBaseColorTexture();

	/**
	 * Set material PBR metallic roughness texture
	 * @param fileName file name
	 */
	void setMaterialPBRMetallicRoughnessTexture(const string& fileName);

	/**
	 * On material load PBR metallic roughness texture
	 */
	void onMaterialLoadPBRMetallicRoughnessTexture();

	/**
	 * On material clear PBR metallic roughness texture
	 */
	void onMaterialClearPBRMetallicRoughnessTexture();

	/**
	 * On material browse to PBR metallic roughness texture
	 */
	void onMaterialBrowseToPBRMetallicRoughnessTexture();

	/**
	 * Set material PBR normal texture
	 * @param fileName file name
	 */
	void setMaterialPBRNormalTexture(const string& fileName);

	/**
	 * On material load PBR normal texture
	 */
	void onMaterialLoadPBRNormalTexture();

	/**
	 * On material load PBR normal texture
	 */
	void onMaterialClearPBRNormalTexture();

	/**
	 * On material browse to PBR normal texture
	 */
	void onMaterialBrowseToPBRNormalTexture();

	/**
	 * Set preview animations attachment 1 model
	 * @param fileName file name
	 */
	void setPreviewAnimationsAttachment1Model(const string& fileName);

	/**
	 * On preview animations attachment 1 model load
	 */
	void onPreviewAnimationsAttachment1ModelLoad();

	/**
	 * On preview animations attachment 1 model clear
	 */
	void onPreviewAnimationsAttachment1ModelClear();

	/**
	 * On preview animations attachment 1 model browse to
	 */
	void onPreviewAnimationsAttachment1ModelBrowseTo();

	/**
	 * Start rename animation
	 * @param lodLevel lod level
	 * @param animationId animation id
	 */
	void startRenameAnimation(int lodLevel, const string& animationId);

	/**
	 * Rename animation
	 */
	void renameAnimation();

	/**
	 * Create animation setup
	 * @param lodLevel lod level
	 */
	void createAnimationSetup(int lodLevel);

	/**
	 * Create LOD
	 */
	void createLOD();

	/**
	 * Create LOD none
	 */
	void createLODNone();

	/**
	 * Set LOD details
	 * @param lodLevel lod level
	 */
	void setLODDetails(int lodLevel);

	/**
	 * Set LOD color details
	 * @param lodLevel lod level
	 */
	void updateLODColorDetails(int lodLevel);

	/**
	 * Apply LOD details
	 * @param lodLevel LOD level
	 */
	void applyLODDetails(int lodLevel);

	/**
	 * Get outliner node within model or LOD models
	 * @param outlinerNode outliner node
	 * @param modelOutlinerNode model outliner node
	 * @param model model
	 * @param lodLevel lod level
	 * @return success
	 */
	bool getOutlinerNodeLOD(const string& outlinerNode, string& modelOutlinerNode, Model** model = nullptr, int* lodLevel = nullptr);

	// overridden methods
	void onChange(GUIElementNode* node) override;
	void onAction(GUIActionListenerType type, GUIElementNode* node) override;
	void onFocus(GUIElementNode* node) override;
	void onUnfocus(GUIElementNode* node) override;
	void onContextMenuRequest(GUIElementNode* node, int mouseX, int mouseY) override;
	void onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) override;
	void onTooltipCloseRequest() override;
	void onCommand(TabControllerCommand command) override;
	void onDrop(const string& payload, int mouseX, int mouseY) override;

	/**
	 * Update info text line
	 * @param text text
	 */
	void updateInfoText(const MutableString& text);

	/**
	 * Show the information pop up / modal
	 * @param caption caption
	 * @param message message
	 */
	void showInfoPopUp(const string& caption, const string& message);

};
