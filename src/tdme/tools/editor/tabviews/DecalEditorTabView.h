#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/misc/CameraRotationInputHandlerEventHandler.h>
#include <tdme/tools/editor/tabcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/DecalEditorTabController.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/subviews/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/fwd-tdme.h>

using std::string;

using tdme::engine::prototype::Prototype;
using tdme::engine::scene::Scene;
using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::tools::editor::misc::CameraRotationInputHandler;
using tdme::tools::editor::misc::CameraRotationInputHandlerEventHandler;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::DecalEditorTabController;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::subviews::PrototypeDisplaySubView;
using tdme::tools::editor::tabviews::subviews::PrototypePhysicsSubView;
using tdme::tools::editor::tabviews::TabView;
using tdme::tools::editor::views::EditorView;

/**
 * Decal editor tab view
 * @author Andreas Drewke
 */
class tdme::tools::editor::tabviews::DecalEditorTabView final
	: public TabView
	, protected CameraRotationInputHandlerEventHandler
{
protected:
	Engine* engine { nullptr };

private:
	EditorView* editorView { nullptr };
	string tabId;
	PopUps* popUps { nullptr };
	DecalEditorTabController* decalEditorTabController { nullptr };
	TabView::OutlinerState outlinerState;

	Prototype* prototype { nullptr };
	CameraRotationInputHandler* cameraRotationInputHandler { nullptr };
	PrototypeDisplaySubView* prototypeDisplayView { nullptr };
	PrototypePhysicsSubView* prototypePhysicsView { nullptr };
	Vector3 objectScale;

	/**
	 * On rotation event to be overloaded
	 */
	void onCameraRotation() override;

	/**
	 * On scale event to be overloaded
	 */
	void onCameraScale() override;

public:
	// forbid class copy
	FORBID_CLASS_COPY(DecalEditorTabView)

	/**
	 * Public constructor
	 * @param editorView editor view
	 * @param tabId tab id
	 * @param prototype prototype
	 */
	DecalEditorTabView(EditorView* editorView, const string& tabId, Prototype* prototype);

	/**
	 * Destructor
	 */
	~DecalEditorTabView();

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
		return decalEditorTabController;
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
	inline bool hasFixedSize() override{ return false; };
	void updateRendering() override;

	/**
	 * Saving prototype as tempty prototype
	 * @param pathName path name
	 * @param fileName file name
	 */
	void saveFile(const string& pathName, const string& fileName);

};
