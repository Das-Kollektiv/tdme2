#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/tabcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabcontrollers/TerrainEditorTabController.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/fwd-tdme.h>

using std::string;
using std::unique_ptr;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::prototype::Prototype;
using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::math::Vector3;
using tdme::tools::editor::misc::CameraInputHandler;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabcontrollers::TerrainEditorTabController;
using tdme::tools::editor::tabviews::TabView;
using tdme::tools::editor::views::EditorView;

/**
 * Terrain editor tab view
 * @author Andreas Drewke
 */
class tdme::tools::editor::tabviews::TerrainEditorTabView final
	: public TabView
{
protected:
	unique_ptr<Engine> engine;

private:
	EditorView* editorView { nullptr };
	string tabId;
	PopUps* popUps { nullptr };
	unique_ptr<TerrainEditorTabController> terrainEditorTabController;
	TabView::OutlinerState outlinerState;

	unique_ptr<CameraInputHandler> cameraInputHandler;

	unique_ptr<Prototype> prototype;

	BoundingBox terrainBoundingBox;
	vector<Model*> terrainModels;

	struct Water {
		Vector3 waterReflectionEnvironmentMappingPosition;
		vector<Model*> waterModels;
	};
	unordered_map<int, Water> waters;

	vector<int> partitionFoliageIdx;
	unordered_set<int> temporaryPartitionIdxs;

	bool brushingEnabled { false };
	bool brushMoved { false };
	Vector3 brushCenterPosition;
	Texture* brushTexture { nullptr };
	float brushScale { 1.0f };
	float brushDensityStrength { 1.0f };
	int rampMode { -1 };
	array<Vector3, 2> rampVertices;
	array<float, 2> rampHeight;

public:
	// forbid class copy
	FORBID_CLASS_COPY(TerrainEditorTabView)

	/**
	 * Public constructor
	 * @param editorView editor view
	 * @param tabId tab id
	 * @param prototype prototype
	 */
	TerrainEditorTabView(EditorView* editorView, const string& tabId, Prototype* prototype);

	/**
	 * Destructor
	 */
	~TerrainEditorTabView();

	/**
	 * @returns editor view
	 */
	inline EditorView* getEditorView() {
		return editorView;
	}

	/**
	 * @returns associated tab controller
	 */
	inline TabController* getTabController() override {
		return terrainEditorTabController.get();
	}

	/**
	 * @returns pop up views
	 */
	inline PopUps* getPopUps() {
		return popUps;
	}

	/**
	 * @returns prototype
	 */
	inline Prototype* getPrototype() {
		return prototype.get();
	}

	// overridden methods
	void handleInputEvents() override;
	void display() override;
	inline const string& getTabId() override {
		return tabId;
	}
	void initialize() override;
	void dispose() override;
	Engine* getEngine() override;
	void activate() override;
	void deactivate() override;
	void reloadOutliner() override;
	inline bool hasFixedSize() override{ return false; };
	void updateRendering() override;

	/**
	 * Saving prototype as tmodel prototype
	 * @param pathName path name
	 * @param fileName file name
	 */
	void saveFile(const string& pathName, const string& fileName);

	/**
	 * Reset engine
	 */
	void reset();

	/**
	 * Initialize terrain
	 */
	void initializeTerrain();

	/**
	 * Unset terrain
	 */
	void unsetTerrain();

	/**
	 * Set terrain models
	 * @param terrainBoundingBox terrain bounding box
	 * @param terrainModels terrain models
	 */
	void setTerrain(BoundingBox& terrainBoundingBox, vector<Model*> terrainModels);

	/**
	 * Set brush
	 * @param texture brush texture
	 * @param scale scale
	 * @param densityStrength density strength
	 */
	void setBrush(Texture* texture, float scale, float densityStrength);

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
	 * Unset brush
	 */
	void unsetBrush();

	/**
	 * Unset water
	 */
	void unsetWater();

	/**
	 * Remove water
	 * @param waterIdx water index
	 */
	void removeWater(int waterIdx);

	/**
	 * Add water
	 * @param waterIdx water index
	 * @param waterModels water models
	 * @param waterReflectionEnvironmentMappingPosition water reflection environment mapping position
	 */
	void addWater(int waterIdx, vector<Model*> waterModels, const Vector3& waterReflectionEnvironmentMappingPosition);

	/**
	 * Add foliage using render groups at given partition indices
	 */
	void addFoliage();

	/**
	 * Add temporary foliage
	 * @param newFoliageMaps new foliage maps
	 */
	void addTemporaryFoliage(const vector<unordered_map<int, vector<Transform>>>& newFoliageMaps);

	/**
	 * Update temporary foliage
	 */
	void updateTemporaryFoliage(const unordered_set<int>& partitionIdxSet);

	/**
	 * Recreate temporary foliage at given partition indices
	 * @param partitionIdxSet partition indices set
	 */
	inline void recreateTemporaryFoliage(const unordered_set<int>& partitionIdxSet) {
		for (auto partitionIdx: partitionIdxSet) recreateTemporaryFoliage(partitionIdx);
	}

	/**
	 * Recreate temporary foliage at given partition index
	 * @param partitionIdx partition index
	 */
	void recreateTemporaryFoliage(int partitionIdx);

	/**
	 * Recreate foliage using render groups at given partition indices that has been transformed to temporary foliage
	 * @param partitionIdxSet partition index set
	 */
	void recreateFoliage(const unordered_set<int>& partitionIdxSet);

};
