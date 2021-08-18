#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
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
using std::unordered_map;
using std::unordered_set;
using std::vector;

using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::engine::model::Model;
using tdme::engine::prototype::Prototype;
using tdme::engine::primitives::BoundingBox;
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
 * @version $Id$
 */
class tdme::tools::editor::tabviews::TerrainEditorTabView final
	: public TabView
{
protected:
	Engine* engine { nullptr };

private:
	EditorView* editorView { nullptr };
	string tabId;
	PopUps* popUps { nullptr };
	TerrainEditorTabController* terrainEditorTabController { nullptr };
	TabView::OutlinerState outlinerState;

	CameraInputHandler* cameraInputHandler { nullptr };

	Prototype* prototype { nullptr };

	float skyDomeTranslation { 0.0f };

	Prototype* skySpherePrototype { nullptr };
	Prototype* skyDomePrototype { nullptr };
	Prototype* skyPanoramaPrototype { nullptr };

	BoundingBox terrainBoundingBox;
	vector<Model*> terrainModels;

	struct Water {
		Vector3 waterReflectionEnvironmentMappingPosition;
		vector<Model*> waterModels;
	};
	unordered_map<int, Water> waters;

	vector<int> partitionFoliageIdx;
	unordered_set<int> temporaryPartitionIdxs;


public:
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
	 * @return editor view
	 */
	inline EditorView* getEditorView() {
		return editorView;
	}

	/**
	 * @return associated tab controller
	 */
	inline TabController* getTabController() override {
		return terrainEditorTabController;
	}

	/**
	 * @return pop up views
	 */
	inline PopUps* getPopUps() {
		return popUps;
	}

	/**
	 * @return prototype
	 */
	inline Prototype* getPrototype() {
		return prototype;
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

	// overridden methods
	void updateRendering() override;

	/**
	 * Initialize sky
	 */
	void initSky();

	/**
	 * Update sky
	 */
	void updateSky();

	/**
	 * Initialize terrain
	 */
	void initializeTerrain();

	/**
	 * Set terrain models
	 * @param terrainBoundingBox terrain bounding box
	 * @param terrainModels terrain models
	 */
	void setTerrain(BoundingBox& terrainBoundingBox, vector<Model*> terrainModels);

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

};
