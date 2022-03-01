#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/tabcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabcontrollers/UIEditorTabController.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/fwd-tdme.h>

using std::string;

using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::engine::model::Model;;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabcontrollers::UIEditorTabController;
using tdme::tools::editor::tabviews::TabView;
using tdme::tools::editor::views::EditorView;

/**
 * UI editor tab view
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::editor::tabviews::UIEditorTabView final
	: public TabView
{
protected:
	Engine* guiEngine { nullptr };
	Engine* engine { nullptr };
	bool projectedUi { false };
	Model* model { nullptr };

private:
	EditorView* editorView { nullptr };
	string tabId;
	PopUps* popUps { nullptr };
	UIEditorTabController* uiTabController { nullptr };
	TabView::OutlinerState outlinerState;
	vector<GUIScreenNode*> screenNodes;

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
	inline vector<GUIScreenNode*>& getScreenNodes() {
		return screenNodes;
	}

	/**
	 * Add screen
	 */
	void addScreen();

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
	 * @return model
	 */
	Model* getModel();

	/**
	 * Load model
	 * @param pathName path name
	 * @param fileName file name
	 * @param modelMeshNode model mesh node
	 * @return model
	 */
	Model* loadModel(const string& pathName, const string& fileName, const string& modelMeshNode);

	/**
	 * Set model mesh node
	 * @param modelMeshNode model mesh node
	 */
	void setModelMeshNode(const string& modelMeshNode);

	/**
	 * Remove model
	 */
	void removeModel();

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
