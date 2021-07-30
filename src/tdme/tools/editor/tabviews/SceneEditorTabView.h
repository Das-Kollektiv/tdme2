#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/scene/fwd-tdme.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/misc/CameraInputHandlerEventHandler.h>
#include <tdme/tools/editor/tabcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/fwd-tdme.h>

using std::string;

using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::engine::scene::Scene;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::CameraInputHandler;
using tdme::tools::editor::misc::CameraInputHandlerEventHandler;
using tdme::tools::editor::tabcontrollers::SceneEditorTabController;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::TabView;
using tdme::tools::editor::views::EditorView;

/**
 * Scene editor tab view
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::editor::tabviews::SceneEditorTabView final: public TabView, protected CameraInputHandlerEventHandler
{
private:
	Engine* engine { nullptr };
	CameraInputHandler* cameraInputHandler { nullptr };
	EditorView* editorView { nullptr };
	string tabId;
	PopUps* popUps { nullptr };
	SceneEditorTabController* sceneEditorTabController { nullptr };
	TabView::OutlinerState outlinerState;
	string sceneFileName;
	Scene* scene { nullptr };

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

};
