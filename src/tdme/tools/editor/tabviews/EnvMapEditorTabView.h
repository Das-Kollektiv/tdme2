#pragma once

#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/scene/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/tabcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/EnvMapEditorTabController.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/fwd-tdme.h>

using std::string;
using std::unique_ptr;

using tdme::engine::prototype::Prototype;
using tdme::engine::scene::Scene;
using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::math::Vector3;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::EnvMapEditorTabController;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::TabView;
using tdme::tools::editor::views::EditorView;

/**
 * Environmap editor tab view
 * @author Andreas Drewke
 */
class tdme::tools::editor::tabviews::EnvMapEditorTabView final
	: public TabView
{
protected:
	unique_ptr<Engine> engine;

private:
	EditorView* editorView { nullptr };
	string tabId;
	PopUps* popUps { nullptr };
	unique_ptr<EnvMapEditorTabController> envMapEditorTabController;
	TabView::OutlinerState outlinerState;
	unique_ptr<Scene> scene;
	float skyDomeTranslation { 0.0f };
	unique_ptr<Prototype> skySpherePrototype;
	unique_ptr<Prototype> skyDomePrototype;
	unique_ptr<Prototype> skyPanoramaPrototype;
	unique_ptr<Prototype> prototype;

public:
	// forbid class copy
	FORBID_CLASS_COPY(EnvMapEditorTabView)

	/**
	 * Public constructor
	 * @param editorView editor view
	 * @param tabId tab id
	 * @param scene scene
	 * @param prototype prototype
	 */
	EnvMapEditorTabView(EditorView* editorView, const string& tabId, Scene* scene, Prototype* prototype);

	/**
	 * Destructor
	 */
	~EnvMapEditorTabView();

	/**
	 * @return prototype
	 */
	inline Prototype* getPrototype() {
		return prototype.get();
	}

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
		return envMapEditorTabController.get();
	}

	/**
	 * @return pop up views
	 */
	inline PopUps* getPopUps() {
		return popUps;
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
	 * Initialize sky
	 */
	void initSky();

	/**
	 * Update sky
	 */
	void updateSky();

	/**
	 * @return environment map translation
	 */
	const Vector3& getEnvironmentMapTranslation();

	/**
	 * Set environment map translation
	 * @param translation translation
	 */
	void setEnvironmentMapTranslation(const Vector3& translation);

	/**
	 * @return environment map render passes
	 */
	int32_t getEnvironmentMapRenderPassMask();

	/**
	 * Set environment map render passes
	 * @param renderPassMask render pass mask
	 */
	void setEnvironmentMapRenderPassMask(int32_t renderPassMask);

	/**
	 * @return environment map frequency
	 */
	int64_t getEnvironmentMapFrequency();

	/**
	 * Set environment map frequency
	 * @param frequency frequency
	 */
	void setEnvironmentMapFrequency(int64_t frequency);

	/**
	 * Saving prototype as tenvmap prototype
	 * @param pathName path name
	 * @param fileName file name
	 */
	void saveFile(const string& pathName, const string& fileName);

};
