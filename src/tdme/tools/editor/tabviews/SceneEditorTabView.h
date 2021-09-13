#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/scene/fwd-tdme.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/misc/CameraInputHandlerEventHandler.h>
#include <tdme/tools/editor/misc/Gizmo.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/tabcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/SceneEditorTabController.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/fwd-tdme.h>

using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using tdme::engine::model::Model;
using tdme::engine::prototype::Prototype;
using tdme::engine::scene::Scene;
using tdme::engine::scene::SceneEntity;
using tdme::engine::Engine;
using tdme::engine::EntityPickingFilter;
using tdme::engine::FrameBuffer;
using tdme::tools::editor::misc::CameraInputHandler;
using tdme::tools::editor::misc::CameraInputHandlerEventHandler;
using tdme::tools::editor::misc::Gizmo;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::SceneEditorTabController;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::TabView;
using tdme::tools::editor::views::EditorView;

/**
 * Scene editor tab view
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::editor::tabviews::SceneEditorTabView final: public TabView, protected CameraInputHandlerEventHandler, public Gizmo
{
private:
	/**
	 * Entity color
	 */
	struct EntityColor {
		float colorMulR;
		float colorMulG;
		float colorMulB;
		float colorAddR;
		float colorAddG;
		float colorAddB;

		/**
		 * Public constructor
		 */
		inline EntityColor() {
			this->colorMulR = 1.0f;
			this->colorMulG = 1.0f;
			this->colorMulB = 1.0f;
			this->colorAddR = 0.0f;
			this->colorAddG = 0.0f;
			this->colorAddB = 0.0f;
		}

		/**
		 * Public constructor
		 * @param sceneEditorView scene editor view
		 * @param colorMulR colorMulR
		 * @param colorMulG colorMulG
		 * @param colorMulB colorMulB
		 * @param colorAddR colorAddR
		 * @param colorAddG colorAddG
		 * @param colorAddB colorAddB
		 */
		inline EntityColor(float colorMulR, float colorMulG, float colorMulB, float colorAddR, float colorAddG, float colorAddB) {
			this->colorMulR = colorMulR;
			this->colorMulG = colorMulG;
			this->colorMulB = colorMulB;
			this->colorAddR = colorAddR;
			this->colorAddG = colorAddG;
			this->colorAddB = colorAddB;
		}
	};

	static constexpr int MOUSE_DOWN_LAST_POSITION_NONE { -1 };

	Engine* engine { nullptr };
	CameraInputHandler* cameraInputHandler { nullptr };
	EditorView* editorView { nullptr };
	string tabId;
	PopUps* popUps { nullptr };
	SceneEditorTabController* sceneEditorTabController { nullptr };
	TabView::OutlinerState outlinerState;
	Scene* scene { nullptr };

	static vector<string> ENTITYCOLOR_NAMES;
	unordered_map<string, EntityColor> entityColors;

	bool keyControl;
	bool keyShift;
	bool keyEscape;

	int placeEntityYRotation;

	bool placeEntityMode;
	bool placeEntityValid;
	int placeEntityMouseX;
	int placeEntityMouseY;
	Vector3 placeEntityTranslation;
	int mouseDownLastX;
	int mouseDownLastY;
	bool mouseDragging;
	Entity* mouseDraggingLastEntity { nullptr };

	bool pasteMode;
	bool pasteModeValid;

	Prototype* selectedPrototype { nullptr };
	vector<string> selectedEntityIds;
	unordered_set<string> selectedEntityIdsById;
	vector<SceneEntity*> copiedEntities;
	EntityPickingFilter* entityPickingFilterNoGrid { nullptr };
	EntityPickingFilter* entityPickingFilterPlacing { nullptr };
	bool needGizmoUpdate { false };

	Vector3 multipleSelectionTranslation;
	Vector3 multipleSelectionRotation;
	Vector3 multipleSelectionScale;

	float snappingX;
	float snappingZ;
	bool snappingEnabled;

	bool gridEnabled;
	float gridY;
	Model* gridModel { nullptr };

public:
	/**
	 * Public constructor
	 * @param editorView editor view
	 * @param tabId tab id
	 * @param scene scene
	 */
	SceneEditorTabView(EditorView* editorView, const string& tabId, Scene* scene);

	/**
	 * Destructor
	 */
	~SceneEditorTabView();

	/**
	 * @return editor view
	 */
	inline EditorView* getEditorView() {
		return editorView;
	}

	/**
	 * @return pop up views
	 */
	inline PopUps* getPopUps() {
		return popUps;
	}

	/**
	 * @return scene
	 */
	Scene* getScene() {
		return scene;
	}

	// overridden methods
	void handleInputEvents() override;
	void display() override;
	inline const string& getTabId() override {
		return tabId;
	}
	void initialize() override;
	void dispose() override;
	void activate() override;
	void deactivate() override;
	Engine* getEngine() override;
	inline TabController* getTabController() override {
		return sceneEditorTabController;
	}
	void reloadOutliner() override;
	void onCameraTranslation() override;
	void onCameraRotation() override;
	void onCameraScale() override;
	void updateRendering() override;

	/**
	 * Clear scene
	 */
	void clearScene();

	/**
	 * Reload scene
	 */
	void reloadScene();

	/**
	 * Reload outliner
	 * @param outlinerNode selected outliner node
	 */
	void reloadOutliner(const string& outlinerNode);

	/**
	 * Remove sky
	 */
	void removeSky();

	/**
	 * Update sky
	 */
	void updateSky();

	/**
	 * Update sky position
	 */
	void updateSkyPosition();

	/**
	 * Update lights
	 */
	void updateLights();

	/**
	 * Set highlight entity color effect
	 * @param object object
	 */
	void setHighlightEntityColorEffect(Entity* object);

	/**
	 * Set standard entity color effect
	 * @param object object
	 */
	void setStandardEntityColorEffect(Entity* object);

	/**
	 * Reset scale to scene editor object scale
	 * @param object object
	 */
	void resetEntity(Entity* object);

	/**
	 * Select entities
	 * @param entityIds entity ids
	 */
	void selectEntities(const vector<string>& entityIds);

	/**
	 * Unselect entities
	 */
	void unselectEntities();

	/**
	 * Copy current selected entities
	 */
	void copyEntities();

	/**
	 * Initialize place entity mode
	 * @param prototype prototype
	 */
	void setPlaceEntityMode(Prototype* prototype);

	/**
	 * Finish place entity mode
	 * @param cancelled cancelled place entity mode?
	 */
	void unsetPlaceEntityMode(bool cancelled);

	/**
	 * Places selected entity on selected object
	 */
	void placeEntity();

	/**
	 * Removes selected entities
	 */
	void removeEntities();

	/**
	 * Set paste mode
	 */
	void setPasteMode();

	/**
	 * cancel paste
	 */
	void unsetPasteMode();

	/**
	 * Paste entities
	 * @param displayOnly display only
	 */
	void pasteEntities(bool displayOnly);

	/**
	 * Compute multiple selection pivot
	 */
	const Vector3 computeMultipleSelectionPivot();

	/**
	 * Get selected reflection environment mapping id
	 */
	const string getSelectedReflectionEnvironmentMappingId();

	/**
	 * Center entities
	 */
	void centerEntities();

	/**
	 * Select same entities
	 */
	void selectSameEntities();

	/**
	 * Open prototype
	 */
	void openPrototype();

	/**
	 * Update gizmo
	 */
	void updateGizmo();

	/**
	 * Apply base information
	 * @param name name
	 * @param description description
	 * @return success
	 */
	bool applyBase(const string& name, const string& description);

	/**
	 * Apply translation
	 * @param translation translation
	 */
	void applyTranslation(const Vector3& translation);

	/**
	 * Apply rotation
	 * @param rotation rotation
	 */
	void applyRotation(const Vector3& rotation);

	/**
	 * Apply scale
	 * @param rotation rotation
	 */
	void applyScale(const Vector3& scale);

	/**
	 * Apply reflection environment mapping id
	 * @param environmentMappingId environment mapping id
	 */
	void applyReflectionEnvironmentMappingId(const string& reflectionEnvironmentMappingId);

	/**
	 * Update grid
	 */
	void updateGrid();

	/**
	 * Remove grid
	 */
	void removeGrid();

	/**
	 * @return grid enabled
	 */
	bool isGridEnabled();

	/**
	 * @param gridEnabled grid enabled
	 */
	void setGridEnabled(bool gridEnabled);

	/**
	 * @return grid y
	 */
	float getGridY();

	/**
	 * Set grid y position
	 * @param gridY grid y
	 */
	void setGridY(float gridY);

	/**
	 * Get snapping
	 * @param snappingEnabled snapping enabled
	 * @param snappingX snapping along X axis
	 * @param snappingZ snapping along Z axis
	 */
	void getSnapping(bool& snappingEnabled, float& snappingX, float& snappingZ);

	/**
	 * Set snapping
	 * @param snappingEnabled snapping enabled
	 * @param snappingX snapping along X axis
	 * @param snappingZ snapping along Z axis
	 */
	void setSnapping(bool snappingEnabled, float snappingX, float snappingZ);

	/**
	 * Add prototype to scene
	 * @param prototype prototype
	 */
	void addPrototype(Prototype* prototype);

};
