#pragma once

#include <array>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/Transform.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/events/GUIActionListener.h>
#include <agui/gui/events/GUIChangeListener.h>
#include <agui/gui/events/GUIContextMenuRequestListener.h>
#include <agui/gui/events/GUIFocusListener.h>
#include <agui/gui/events/GUITooltipRequestListener.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <agui/utilities/MutableString.h>
#include <tdme/utilities/Terrain.h>

#include <ext/tinyxml/tinyxml.h>

using std::array;
using std::string;
using std::unordered_map;
using std::unique_ptr;
using std::vector;

using tdme::engine::Texture;
using tdme::engine::Transform;
using agui::gui::events::GUIActionListener;
using agui::gui::events::GUIActionListenerType;
using agui::gui::events::GUIChangeListener;
using agui::gui::events::GUIContextMenuRequestListener;
using agui::gui::events::GUIFocusListener;
using agui::gui::events::GUITooltipRequestListener;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUIParentNode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::nodes::GUITextNode;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::subcontrollers::BasePropertiesSubController;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::TerrainEditorTabView;
using agui::utilities::MutableString;
using tdme::utilities::Terrain;

using tinyxml::TiXmlAttribute;
using tinyxml::TiXmlDocument;
using tinyxml::TiXmlElement;

/**
 * Terrain editor tab controller
 * @author Andreas Drewke
 */
class tdme::tools::editor::tabcontrollers::TerrainEditorTabController final
	: public TabController
{

private:
	unique_ptr<BasePropertiesSubController> basePropertiesSubController;
	TerrainEditorTabView* view { nullptr };
	GUIScreenNode* screenNode { nullptr };
	PopUps* popUps { nullptr };

	vector<unordered_map<int, vector<Transform>>> newFoliageMaps;
	unordered_set<int> recreateFoliagePartitions;

	bool haveCurrentTerrainBrushHeight { false };
	float currentTerrainBrushHeight { 0.0f };
	float currentTerrainBrushScale { 1.0f };
	float currentTerrainBrushStrength { 1.0f };
	string currentTerrainBrushTextureFileName;
	Texture* currentTerrainBrushTexture { nullptr };
	Texture* rampTerrainBrushTexture { nullptr };
	Terrain::BrushOperation currentTerrainBrushOperation { Terrain::BRUSHOPERATION_NONE };
	Terrain::BrushOperation currentFoliageBrushOperation { Terrain::BRUSHOPERATION_NONE };

	Terrain::FoliageBrush foliageBrush = {
		.brushTexture = nullptr,
		.brushScale = 1.0f,
		.brushDensity = 1.0f
	};
	vector<Terrain::FoliageBrushPrototype> foliageBrushPrototypes;

	array<string, 2> textureBrushApplyNodes = {
		"terrainbrush_size",
		"terrainbrush_strength"
	};

	array<string, 2> foliageBrushApplyNodes = {
		"foliagebrush_size",
		"foliagebrush_density"
	};

	array<string, 16> foliageBrushPrototypeApplyNodes = {
		"foliagebrush_prototype_object_count",
		"foliagebrush_prototype_normalalign",
		"foliagebrush_prototype_rotationrange_x_min",
		"foliagebrush_prototype_rotationrange_x_max",
		"foliagebrush_prototype_rotationrange_y_min",
		"foliagebrush_prototype_rotationrange_y_max",
		"foliagebrush_prototype_rotationrange_z_min",
		"foliagebrush_prototype_rotationrange_z_max",
		"foliagebrush_prototype_scalerange_min",
		"foliagebrush_prototype_scalerange_max",
		"foliagebrush_prototype_scalerange_max",
		"foliagebrush_prototype_heightrange_max",
		"foliagebrush_prototype_heightrange_min",
		"foliagebrush_prototype_heightrange_max",
		"foliagebrush_prototype_sloperange_max",
		"foliagebrush_prototype_sloperange_max"
	};

public:
	// forbid class copy
	FORBID_CLASS_COPY(TerrainEditorTabController)

	/**
	 * Public constructor
	 * @param view view
	 */
	TerrainEditorTabController(TerrainEditorTabView* view);

	/**
	 * Destructor
	 */
	virtual ~TerrainEditorTabController();

	/**
	 * Get view
	 * @returns view
	 */
	inline TerrainEditorTabView* getView() {
		return view;
	}

	// overridden method
	inline GUIScreenNode* getScreenNode() override {
		return screenNode;
	}

	/**
	 * @returns current terrain brush operation
	 */
	inline Terrain::BrushOperation getTerrainBrushOperation() {
		return currentTerrainBrushOperation;
	}

	/**
	 * @returns current foliage brush operation
	 */
	inline Terrain::BrushOperation getFoliageBrushOperation() {
		return currentFoliageBrushOperation;
	}

	// overridden methods
	void initialize(GUIScreenNode* screenNode) override;
	void dispose() override;
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
	 * Set outliner content
	 */
	void setOutlinerContent();

	/**
	 * Set outliner add drop down content
	 */
	void setOutlinerAddDropDownContent();

	/**
	 * On create terrain
	 */
	void onCreateTerrain();

	/**
	 * Set brush scale
	 * @param scale scale
	 */
	void setBrushScale(float scale);

	/**
	 * Set brush density/strength
	 * @param densityStrength density/strength
	 */
	void setBrushDensityStrength(float densityStrength);

	/**
	 * Set terrain details
	 */
	void setTerrainDetails();

	/**
	 * Set terrain brush details
	 */
	void setTerrainBrushDetails();

	/**
	 * Update terrain brush details
	 */
	void updateTerrainBrushDetails();

	/**
	 * Apply terrain brush details
	 */
	void applyTerrainBrushDetails();

	/**
	 * Set foliage brush details
	 */
	void setFoliageBrushDetails();

	/**
	 * Update foliage brush details
	 */
	void updateFoliageBrushDetails();

	/**
	 * Apply foliage brush details
	 */
	void applyFoliageBrushDetails();

	/**
	 * Set foliage brush details
	 */
	void setFoliageBrushPrototypeDetails();

	/**
	 * Apply foliage brush prototype details
	 */
	void applyFoliageBrushPrototypeDetails();

	/**
	 * Check if outliner selection is foliage brush prototype
	 * @param outlinerNode outliner node
	 * @param foliageBrushIdx foliage brush index
	 * @param foliageBrushPrototypeIdx foliage brush prototype index
	 */
	bool checkOutlinerFoliageBrushPrototype(const string& outlinerNode, int& foliageBrushIdx, int& foliageBrushPrototypeIdx);

	/**
	 * Update details
	 * @param outlinerNode outliner node
	 */
	void updateDetails(const string& outlinerNode);

	/**
	 * Initialize terrain
	 */
	void initializeTerrain();

	/**
	 * Apply current brush to terrain at given brush center position
	 * @param terrainBoundingBox terrain bounding box
	 * @param terrainModels terrain models
	 * @param brushCenterPosition brush center position
	 * @param deltaTime delta time between last frame and this frame
	 */
	void applyTerrainBrush(BoundingBox& terrainBoundingBox, vector<Model*>& terrainModels, const Vector3& brushCenterPosition, int64_t deltaTime);

	/**
	 * Determine current brush flatten height
	 * @param terrainBoundingBox terrain bounding box
	 * @param terrainModels terrain models
	 * @param brushCenterPosition brush center position
	 * @returns success
	 */
	bool determineCurrentBrushHeight(BoundingBox& terrainBoundingBox, vector<Model*> terrainModels, const Vector3& brushCenterPosition);

	/**
	 * Determine ramp height
	 * @param terrainBoundingBox terrain bounding box
	 * @param terrainModels terrain models
	 * @param position position
	 * @param height height
	 * @returns success
	 */
	bool determineRampHeight(BoundingBox& terrainBoundingBox, vector<Model*> terrainModels, const Vector3& position, float& height);

	/**
	 * Unset current brush flatten height
	 */
	void unsetCurrentBrushFlattenHeight();

	/**
	 * Apply current brush to terrain at given brush center position
	 * @param terrainBoundingBox terrain bounding box
	 * @param terrainModels terrain models
	 * @param position position
	 * @param rotation rotation
	 * @param scale scale
	 * @param minHeight min height
	 * @param maxHeigth max heigth
	 */
	void applyRampTerrainBrush(BoundingBox& terrainBoundingBox, vector<Model*>& terrainModels, const Vector3& position, float rotation, const Vector2& scale, float minHeight, float maxHeight);

	/**
	 * Create water using a auto fill like algorithm
	 * @param terrainBoundingBox terrain bounding box
	 * @param brushCenterPosition brush center position
	 * @param waterModels water models
	 * @param waterReflectionEnvironmentMappingPosition water reflection environment mapping position
	 */
	void createWater(BoundingBox& terrainBoundingBox, const Vector3& brushCenterPosition, vector<Model*>& waterModels, Vector3& waterReflectionEnvironmentMappingPosition);

	/**
	 * Delete water models
	 * @param waterPositionMapIdx water position map index
	 */
	void deleteWater(int waterPositionMapIdx);

	/**
	 * Set foliage brush
	 */
	void setFoliageBrush();

	/**
	 * Update foliage brush
	 * @param foliageBrush foliage brush
	 * @param foliageBrushPrototypes foliage brush prototypes
	 */
	void updateFoliageBrush();

	/**
	 * Apply current brush to foliage at given brush center position
	 * @param terrainBoundingBox terrain bounding box
	 * @param brushCenterPosition brush center position
	 * @param deltaTime delta time between last frame and this frame
	 */
	void applyFoliageBrush(BoundingBox& terrainBoundingBox, const Vector3& brushCenterPosition, int64_t deltaTime);

	/**
	 * @returns UI terrain brush operation
	 */
	Terrain::BrushOperation getUITerrainBrushOperation();

	/**
	 * @returns UI water operation
	 */
	Terrain::BrushOperation getUIWaterOperation();

	/**
	 * @returns UI foliage brush operation
	 */
	Terrain::BrushOperation getUIFoliageBrushOperation();

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

	/**
	 * Set terrain brush texture
	 * @param fileName file name
	 */
	void setTerrainBrushTexture(const string& fileName);

	/**
	 * Set foliage brush texture
	 * @param fileName file name
	 */
	void setFoliageBrushTexture(const string& fileName);

	/**
	 * Set foliage brush prototype
	 * @param fileName file name
	 */
	void setFoliageBrushPrototype(const string& fileName);
};
