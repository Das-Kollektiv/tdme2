#pragma once

#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/EmptyEditorTabController.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/fwd-tdme.h>

using std::string;
using std::unique_ptr;

using tdme::engine::prototype::Prototype;
using tdme::engine::scene::Scene;
using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::tools::editor::misc::CameraRotationInputHandler;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::EmptyEditorTabController;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::TabView;
using tdme::tools::editor::views::EditorView;

/**
 * Empty editor tab view
 * @author Andreas Drewke
 */
class tdme::tools::editor::tabviews::EmptyEditorTabView final
	: public TabView
{
protected:
	unique_ptr<Engine> engine;

private:
	EditorView* editorView { nullptr };
	string tabId;
	PopUps* popUps { nullptr };
	unique_ptr<EmptyEditorTabController> emptyEditorTabController;
	TabView::OutlinerState outlinerState;

	unique_ptr<Prototype> prototype;
	unique_ptr<CameraRotationInputHandler> cameraRotationInputHandler;

public:
	// forbid class copy
	FORBID_CLASS_COPY(EmptyEditorTabView)

	/**
	 * Public constructor
	 * @param editorView editor view
	 * @param tabId tab id
	 * @param prototype prototype
	 */
	EmptyEditorTabView(EditorView* editorView, const string& tabId, Prototype* prototype);

	/**
	 * Destructor
	 */
	~EmptyEditorTabView();

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
		return emptyEditorTabController.get();
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
	void updateRendering() override;
	inline bool hasFixedSize() override{ return false; };
	/**
	 * Saving prototype as tempty prototype
	 * @param pathName path name
	 * @param fileName file name
	 */
	void saveFile(const string& pathName, const string& fileName);

};
