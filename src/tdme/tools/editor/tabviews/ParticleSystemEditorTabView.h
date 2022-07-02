#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/audio/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/misc/CameraRotationInputHandlerEventHandler.h>
#include <tdme/tools/editor/misc/Gizmo.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/tabcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/ParticleSystemEditorTabController.h>
#include <tdme/tools/editor/tabviews/subviews/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/fwd-tdme.h>
#include <tdme/tools/editor/views/PlayableSoundView.h>

using std::string;

using tdme::audio::Audio;
using tdme::engine::prototype::Prototype;
using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::engine::ParticleSystemEntity;
using tdme::math::Vector3;
using tdme::tools::editor::misc::CameraRotationInputHandler;
using tdme::tools::editor::misc::CameraRotationInputHandlerEventHandler;
using tdme::tools::editor::misc::Gizmo;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::ParticleSystemEditorTabController;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::subviews::PrototypeDisplaySubView;
using tdme::tools::editor::tabviews::subviews::PrototypePhysicsSubView;
using tdme::tools::editor::tabviews::subviews::PrototypeSoundsSubView;
using tdme::tools::editor::tabviews::TabView;
using tdme::tools::editor::views::EditorView;
using tdme::tools::editor::views::PlayableSoundView;

/**
 * Particle system editor tab view
 * @author Andreas Drewke
 */
class tdme::tools::editor::tabviews::ParticleSystemEditorTabView final
	: public TabView
	, public PlayableSoundView
	, protected CameraRotationInputHandlerEventHandler
	, protected Gizmo
{
protected:
	Audio* audio { nullptr };
	Engine* engine { nullptr };

private:
	EditorView* editorView { nullptr };
	string tabId;
	PopUps* popUps { nullptr };
	Prototype* prototype { nullptr };
	CameraRotationInputHandler* cameraRotationInputHandler { nullptr };
	ParticleSystemEditorTabController* particleSystemEditorTabController { nullptr };
	PrototypeDisplaySubView* prototypeDisplayView { nullptr };
	PrototypePhysicsSubView* prototypePhysicsView { nullptr };
	PrototypeSoundsSubView* prototypeSoundsView { nullptr };
	TabView::OutlinerState outlinerState;

	Vector3 objectScale;

	int64_t audioStarted;
	int64_t audioOffset;

	int particleSystemIdx { -1 };
	Vector3 totalDeltaScale;

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
	inline EditorView* getEditorView() {
		return editorView;
	}

	/**
	 * @return associated tab controller
	 */
	inline TabController* getTabController() override {
		return particleSystemEditorTabController;
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

	// overridden methods
	void playSound(const string& soundId) override;
	void stopSound() override;

	/**
	 * Init particle system
	 */
	void initParticleSystem();

	/**
	 * Uninit particle system
	 */
	void uninitParticleSystem();

	/**
	 * @return particle system index
	 */
	int getParticleSystemIndex();

	/**
	 * Set particle system index, the particle system to edit
	 * @param idx index
	 * @param changeOutlinerSelection change outliner selection
	 */
	void setParticleSystemIndex(int idx, bool changeOutlinerSelection = true);

	/**
	 * Update GIZMO
	 */
	void updateGizmo();

	/**
	 * Set GIZMO rotation
	 * @param transformations transformations
	 */
	void setGizmoRotation(const Transformations& transformations);

	/**
	 * Apply particle system transformations
	 * @param particleSystemEntity particle system entity
	 * @param guiOnly GUI only
	 */
	void applyParticleSystemTransformations(ParticleSystemEntity* particleSystemEntity, bool guiOnly);

	/**
	 * Saving prototype as tempty prototype
	 * @param pathName path name
	 * @param fileName file name
	 */
	void saveFile(const string& pathName, const string& fileName);

};
