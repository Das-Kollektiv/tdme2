#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/misc/CameraRotationInputHandlerEventHandler.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/tabcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/fwd-tdme.h>

using std::string;

using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::engine::prototype::Prototype;
using tdme::math::Vector3;
using tdme::tools::editor::misc::CameraRotationInputHandler;
using tdme::tools::editor::misc::CameraRotationInputHandlerEventHandler;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::ParticleSystemEditorTabController;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::TabView;
using tdme::tools::editor::views::EditorView;

/**
 * Particle system editor tab view
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::editor::tabviews::ParticleSystemEditorTabView final
	: public TabView
	, protected CameraRotationInputHandlerEventHandler
{
protected:
	Engine* engine { nullptr };

private:
	EditorView* editorView { nullptr };
	string tabId;
	PopUps* popUps { nullptr };
	Prototype* prototype { nullptr };
	CameraRotationInputHandler* cameraRotationInputHandler { nullptr };
	ParticleSystemEditorTabController* particleSystemEditorTabController { nullptr };
	TabView::OutlinerState outlinerState;

	Vector3 objectScale;

protected:
	/**
	 * On rotation event to be overloaded
	 */
	void onCameraRotation() override;

	/**
	 * On scale event to be overloaded
	 */
	void onCameraScale() override;

public:
	/**
	 * Public constructor
	 * @param editorView editor view
	 * @param tabId tab id
	 */
	ParticleSystemEditorTabView(EditorView* editorView, const string& tabId, Prototype* prototype);

	/**
	 * Destructor
	 */
	~ParticleSystemEditorTabView();

	/**
	 * @return editor view
	 */
	EditorView* getEditorView();

	/**
	 * @return associated tab controller
	 */
	TabController* getTabController();

	/**
	 * @return pop up views
	 */
	PopUps* getPopUps();

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

};
