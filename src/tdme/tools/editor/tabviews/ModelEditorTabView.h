#pragma once

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
using tdme::tools::editor::tabviews::subviews::PrototypeDisplaySubView;
using tdme::tools::editor::tabviews::subviews::PrototypePhysicsSubView;
using tdme::tools::editor::tabviews::subviews::PrototypeSoundsSubView;
using tdme::tools::editor::tabviews::TabView;
using tdme::tools::editor::views::EditorView;
using tdme::tools::editor::views::PlayableSoundView;

/**
 * TDME model editor tab view
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::editor::tabviews::ModelEditorTabView final
	: public TabView
	, public PlayableSoundView
	, public GUIInputEventHandler
	, protected CameraRotationInputHandlerEventHandler
{
protected:
	Engine* engine { nullptr };
	Audio* audio { nullptr };

private:
	EditorView* editorView { nullptr };
	string tabId;
	PopUps* popUps { nullptr };
	ModelEditorTabController* modelEditorScreenController { nullptr };
	PrototypeDisplaySubView* prototypeDisplayView { nullptr };
	PrototypePhysicsSubView* prototypePhysicsView { nullptr };
	PrototypeSoundsSubView* prototypeSoundsView { nullptr };
	Prototype* prototype { nullptr };
	bool loadModelRequested;
	bool initModelRequested;
	bool initModelRequestedReset;
	string modelFile;
	int lodLevel;
	CameraRotationInputHandler* cameraRotationInputHandler { nullptr };
	int64_t audioStarted;
	int64_t audioOffset;
	Vector3 objectScale;
	string attachment1Bone;
	Model* attachment1Model { nullptr };

	/**
	 * Init model
	 */
	void initModel();

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
	 * @param pivot pivot
	 * @return prototype
	 * @throws tdme::utilities::Exception
	 */
	virtual Prototype* loadModelPrototype(const string& name, const string& description, const string& pathName, const string& fileName, const Vector3& pivot);

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
	ModelEditorTabView(EditorView* editorView, const string& tabId);

	/**
	 * Destructor
	 */
	~ModelEditorTabView();

	/**
	 * @return engine
	 */
	Engine* getEngine();

	/**
	 * @return pop up views
	 */
	PopUps* getPopUps();

	/**
	 * @return prototype
	 */
	Prototype* getPrototype();

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
	 * Reimport prototype
	 */
	void reimportPrototype();

	/**
	 * @return current model file name
	 */
	const string& getFileName();

	/**
	 * @return LOD level
	 */
	int getLodLevel() const;

	/**
	 * Set lod level to display
	 * @param lodLevel lod level
	 */
	void setLodLevel(int lodLevel);

	/**
	 * Issue file loading
	 * @param pathName path name
	 * @param fileName file name
	 */
	void loadFile(const string& pathName, const string& fileName);

	/**
	 * Issue reimport model file
	 * @param pathName path name
	 * @param fileName file name
	 */
	void reimportModel(const string& pathName, const string& fileName);

	/**
	 * Triggers saving a map
	 * @param pathName path name
	 * @param fileName file name
	 */
	void saveFile(const string& pathName, const string& fileName);

	/**
	 * Issue file reloading
	 */
	void reloadFile();

	/**
	 * Apply pivot
	 * @param x x
	 * @param y y
	 * @param z z
	 */
	void pivotApply(float x, float y, float z);

	/**
	 * Compute normals
	 */
	void computeNormals();

	/**
	 * Optimize model
	 */
	void optimizeModel();

	/**
	 * Init GUI elements
	 */
	void updateGUIElements();

	// overridden methods
	void handleInputEvents() override;
	void display() override;
	void initialize() override;
	void dispose() override;
	FrameBuffer* getFrameBuffer() override;
	void playSound(const string& soundId) override;

	/**
	 * On init additional screens
	 */
	virtual void onInitAdditionalScreens();

	/**
	 * On load model
	 * @param oldEntity old entity
	 * @param entity entity
	 */
	virtual void onLoadModel(Prototype* oldEntity, Prototype* entity);

	/**
	 * On set prototype data hook
	 */
	virtual void onSetPrototypeData();

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
	 * Update rendering options
	 */
	void updateRendering();

	/**
	 * Update shader parameters
	 */
	void updateShaderParemeters();

};
