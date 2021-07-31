#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/scene/fwd-tdme.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/misc/CameraInputHandlerEventHandler.h>
#include <tdme/tools/editor/misc/Gizmo.h>
#include <tdme/tools/editor/tabcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/fwd-tdme.h>

using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using tdme::engine::Engine;
using tdme::engine::EntityPickingFilter;
using tdme::engine::FrameBuffer;
using tdme::engine::prototype::Prototype;
using tdme::engine::scene::Scene;
using tdme::engine::scene::SceneEntity;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::CameraInputHandler;
using tdme::tools::editor::misc::CameraInputHandlerEventHandler;
using tdme::tools::editor::misc::Gizmo;
using tdme::tools::editor::tabcontrollers::SceneEditorTabController;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::TabView;
using tdme::tools::editor::views::EditorView;

/**
 * Scene editor tab view
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::editor::tabviews::SceneEditorTabView final: public TabView, protected CameraInputHandlerEventHandler, protected Gizmo
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
	string sceneFileName;
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
	EditorView* getEditorView();

	/**
	 * @return pop up views
	 */
	PopUps* getPopUps();

	/**
	 * @return current scene file name
	 */
	const string& getFileName();

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
	TabController* getTabController() override;
	void reloadOutliner() override;
	void onCameraTranslation() override;
	void onCameraRotation() override;
	void onCameraScale() override;
	void updateRendering() override;

	/**
	 * Update sky
	 */
	void updateSky();

	/**
	 * Update sky position
	 */
	void updateSkyPosition();

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
	 * Copy current selected entities
	 */
	void copyEntities();

	/**
	 * Initialize place entity mode
	 */
	void setPlaceEntityMode();

	/**
	 * Finish place entity mode
	 */
	void unsetPlaceEntityMode();

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
	 * Update gizmo
	 */
	void updateGizmo();

};
