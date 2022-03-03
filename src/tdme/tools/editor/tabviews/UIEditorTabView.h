#pragma once

#include <array>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/tools/editor/misc/CameraRotationInputHandlerEventHandler.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/tabcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabcontrollers/UIEditorTabController.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/fwd-tdme.h>
#include <tdme/utilities/Float.h>

using std::array;
using std::string;

using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::engine::prototype::Prototype;
using tdme::gui::nodes::GUIScreenNode;
using tdme::math::Matrix4x4;
using tdme::tools::editor::misc::CameraRotationInputHandler;
using tdme::tools::editor::misc::CameraRotationInputHandlerEventHandler;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabcontrollers::UIEditorTabController;
using tdme::tools::editor::tabviews::TabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Float;

/**
 * UI editor tab view
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::editor::tabviews::UIEditorTabView final: public TabView, protected CameraRotationInputHandlerEventHandler
{
protected:
	Engine* guiEngine { nullptr };
	Engine* engine { nullptr };
	bool projectedUi { false };
	Prototype* prototype { nullptr };
	string modelMeshNode;
	float projectedUiMinX { Float::MAX_VALUE };
	float projectedUiMinZ { Float::MAX_VALUE };
	float projectedUiMaxX { Float::MIN_VALUE };
	float projectedUiMaxZ { Float::MIN_VALUE };

private:
	EditorView* editorView { nullptr };
	string tabId;
	PopUps* popUps { nullptr };
	UIEditorTabController* uiTabController { nullptr };
	TabView::OutlinerState outlinerState;
	vector<GUIScreenNode*> screenNodes;
	vector<array<int, 2>> screenDimensions;
	CameraRotationInputHandler* cameraRotationInputHandler { nullptr };

	// overridden methods
	void onCameraRotation() override;
	void onCameraScale() override;

public:
	/**
	 * Public constructor
	 * @param editorView editor view
	 * @param tabId tab id
	 * @param screenNode screenNode
	 */
	UIEditorTabView(EditorView* editorView, const string& tabId, GUIScreenNode* screenNode);

	/**
	 * Destructor
	 */
	~UIEditorTabView();

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
		return uiTabController;
	}

	/**
	 * @return pop up views
	 */
	inline PopUps* getPopUps() {
		return popUps;
	}

	/**
	 * @return screen nodes
	 */
	inline const vector<GUIScreenNode*>& getScreenNodes() {
		return screenNodes;
	}

	/**
	 * Add screen
	 */
	void addScreen();

	/**
	 * Set screen
	 * @param screenIdx screen index
	 * @param screenNode screen node
	 */
	void setScreen(int screenIdx, GUIScreenNode* screenNode);

	/**
	 * Unset screen
	 * @param screenIdx screen index
	 */
	void unsetScreen(int screenIdx);

	/**
	 * Remove screen
	 * @param screenIdx screen index
	 */
	void removeScreen(int screenIdx);

	/**
	 * Readd screens
	 */
	void reAddScreens();

	/**
	 * @return prototype
	 */
	Prototype* getPrototype();

	/**
	 * Load prototype
	 * @param pathName path name
	 * @param fileName file name
	 * @param modelMeshNode model mesh node
	 * @param modelMeshAnimation model mesh animation
	 * @return model
	 */
	Prototype* loadPrototype(const string& pathName, const string& fileName, const string& modelMeshNode, const string& modelMeshAnimation);

	/**
	 * Set model mesh node
	 * @param modelMeshNode model mesh node
	 */
	void setModelMeshNode(const string& modelMeshNode);

	/**
	 * Set model mesh animation
	 * @param modelMeshAnimation model mesh animation
	 */
	void setModelMeshAnimation(const string& modelMeshAnimation);

	/**
	 * Remove model
	 */
	void removePrototype();

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
	inline bool hasFixedSize() override;
	void updateRendering() override;

};
