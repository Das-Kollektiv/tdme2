#pragma once

#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/audio/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/gui/events/GUIInputEventHandler.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/editor/misc/CameraRotationInputHandlerEventHandler.h>
#include <tdme/tools/editor/tabcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/subviews/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/fwd-tdme.h>
#include <tdme/tools/editor/views/PlayableSoundView.h>

using std::string;
using std::unique_ptr;

using tdme::audio::Audio;
using tdme::engine::model::Model;
using tdme::engine::prototype::Prototype;
using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::gui::events::GUIInputEventHandler;
using tdme::math::Vector3;
using tdme::tools::editor::misc::CameraRotationInputHandler;
using tdme::tools::editor::misc::CameraRotationInputHandlerEventHandler;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::ModelEditorTabController;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::subviews::PrototypeDisplaySubView;
using tdme::tools::editor::tabviews::subviews::PrototypePhysicsSubView;
using tdme::tools::editor::tabviews::subviews::PrototypeSoundsSubView;
using tdme::tools::editor::tabviews::TabView;
using tdme::tools::editor::views::EditorView;
using tdme::tools::editor::views::PlayableSoundView;

/**
 * Model editor tab view
 * @author Andreas Drewke
 */
class tdme::tools::editor::tabviews::ModelEditorTabView final
	: public TabView
	, public PlayableSoundView
	, public CameraRotationInputHandlerEventHandler
{
protected:
	unique_ptr<Engine> engine { nullptr };
	Audio* audio { nullptr };

private:
	EditorView* editorView { nullptr };
	string tabId;
	PopUps* popUps { nullptr };
	unique_ptr<ModelEditorTabController> modelEditorTabController;
	PrototypeDisplaySubView* prototypeDisplayView { nullptr };
	PrototypePhysicsSubView* prototypePhysicsView { nullptr };
	PrototypeSoundsSubView* prototypeSoundsView { nullptr };
	unique_ptr<Prototype> prototype { nullptr };
	string prototypeFileName;
	int lodLevel;
	unique_ptr<CameraRotationInputHandler> cameraRotationInputHandler;
	int64_t audioStarted;
	int64_t audioOffset;
	Vector3 objectScale;
	string attachment1Bone;
	unique_ptr<Model> attachment1Model;
	TabView::OutlinerState outlinerState;

	/**
	 * Init model
	 * @param resetup resetup flag which would mean to leave camera and lighting as is
	 */
	void initModel(bool resetup);

	/**
	 * Load settings
	 */
	void loadSettings();

	/**
	 * Store settings
	 */
	void storeSettings();

	/**
	 * Load a model
	 */
	void loadModel();

	/**
	 * Load model prototype
	 * @param name name
	 * @param description description
	 * @param pathName path name
	 * @param fileName file name
	 * @returns prototype
	 * @throws tdme::utilities::Exception
	 */
	virtual Prototype* loadModelPrototype(const string& name, const string& description, const string& pathName, const string& fileName);

	// overridden methods
	void onCameraRotation() override;
	void onCameraScale() override;

public:
	// forbid class copy
	FORBID_CLASS_COPY(ModelEditorTabView)

	/**
	 * Public constructor
	 * @param editorView editor view
	 * @param tabId tab id
	 * @param prototype prototype
	 */
	ModelEditorTabView(EditorView* editorView, const string& tabId, Prototype* prototype);

	/**
	 * Destructor
	 */
	~ModelEditorTabView();

	/**
	 * @returns editor view
	 */
	inline EditorView* getEditorView() {
		return editorView;
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

	/**
	 * Set prototype
	 * @param prototype prototype
	 */
	void setPrototype(Prototype* prototype);

	/**
	 * Reset prototype
	 */
	void resetPrototype();

	/**
	 * Reload prototype
	 */
	void reloadPrototype();

	/**
	 * Reimport prototype
	 */
	void reimportPrototype();

	/**
	 * @returns current model file name
	 */
	const string& getFileName();

	/**
	 * @returns LOD level
	 */
	int getLODLevel() const;

	/**
	 * Set LOD level to display
	 * @param lodLevel lod level
	 */
	void setLODLevel(int lodLevel);

	/**
	 * Update LOD level
	 */
	void updateLODLevel();

	/**
	 * Issue file loading
	 * @param pathName path name
	 * @param fileName file name
	 */
	void loadModel(const string& pathName, const string& fileName);

	/**
	 * Issue reimport model file
	 * @param pathName path name
	 * @param fileName file name
	 */
	void reimportModel(const string& pathName, const string& fileName);

	/**
	 * Saving prototype as tmodel prototype
	 * @param pathName path name
	 * @param fileName file name
	 */
	void saveFile(const string& pathName, const string& fileName);

	/**
	 * Issue file reloading
	 */
	void reloadFile();

	/**
	 * Compute normals
	 */
	void computeNormals();

	/**
	 * Optimize model
	 */
	void optimizeModel();

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
	void playSound(const string& soundId) override;
	void stopSound() override;
	void updateRendering() override;
	inline bool hasFixedSize() override { return false; };

	/**
	 * Play animation
	 * @param baseAnimationId base animation id
	 * @param overlay1AnimationId overlay 1 animation id
	 * @param overlay2AnimationId overlay 2 animation id
	 * @param overlay3AnimationId overlay 3 animation id
	 */
	void playAnimation(const string& baseAnimationId, const string& overlay1AnimationId = string(), const string& overlay2AnimationId = string(), const string& overlay3AnimationId = string());

	/**
	 * Add attachment 1
	 * @param nodeId node id to attach model to
	 * @param attachmentModelFile attachment model mile
	 */
	void addAttachment1(const string& nodeId, const string& attachmentModelFile);

	/**
	 * Set attachment 1 node id
	 * @param nodeId node id to attach model to
	 */
	void setAttachment1NodeId(const string& nodeId);

	/**
	 * Update shader parameters
	 */
	void updateShaderParemeters();

};
