#pragma once

#include <array>
#include <memory>
#include <string>
#include <vector>

#include <agui/agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/nodes/GUIStyledTextNodeController.h>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/tools/editor/misc/CameraRotationInputHandlerEventHandler.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/TextFormatter.h>
#include <tdme/tools/editor/tabcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabcontrollers/UIEditorTabController.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/fwd-tdme.h>
#include <tdme/utilities/Float.h>

using std::array;
using std::string;
using std::unique_ptr;

using agui::gui::nodes::GUIScreenNode;
using agui::gui::nodes::GUIStyledTextNode;
using agui::gui::nodes::GUIStyledTextNodeController;

using tdme::engine::prototype::Prototype;
using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::math::Matrix4x4;
using tdme::tools::editor::misc::CameraRotationInputHandler;
using tdme::tools::editor::misc::CameraRotationInputHandlerEventHandler;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::TextFormatter;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabcontrollers::UIEditorTabController;
using tdme::tools::editor::tabviews::TabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Float;

/**
 * UI editor tab view
 * @author Andreas Drewke
 */
class tdme::tools::editor::tabviews::UIEditorTabView final: public TabView, public CameraRotationInputHandlerEventHandler
{
public:
	struct UIScreenNode {
		string fileName;
		string xml;
		// TODO: remove that here, rather store a flag if UI had been parsed and added to GUI or not
		GUIScreenNode* screenNode { nullptr };
		int width { -1 };
		int height { -1 };
	};

protected:
	unique_ptr<Engine> guiEngine;
	unique_ptr<Engine> engine;
	bool projectedUi { false };
	unique_ptr<Prototype> prototype;
	string modelMeshNode;
	float projectedUiMinX { Float::MAX_VALUE };
	float projectedUiMinZ { Float::MAX_VALUE };
	float projectedUiMaxX { Float::MIN_VALUE };
	float projectedUiMaxZ { Float::MIN_VALUE };

private:
	EditorView* editorView { nullptr };
	string tabId;
	GUIScreenNode* screenNode { nullptr };
	PopUps* popUps { nullptr };
	unique_ptr<UIEditorTabController> uiTabController;
	TabView::OutlinerState outlinerState;
	string screenFileName;
	vector<UIScreenNode> uiScreenNodes;
	unique_ptr<CameraRotationInputHandler> cameraRotationInputHandler;

	int screenIdx { 0 };
	bool visualEditor { false };

	GUIStyledTextNode* textNode { nullptr };
	unique_ptr<GUIStyledTextNodeController::ChangeListener> textNodeChangeListener;
	unique_ptr<GUIStyledTextNodeController::CodeCompletionListener> textNodeCodeCompletionListener;
	const TextFormatter::CodeCompletion* codeCompletion { nullptr };

	struct CodeCompletionSymbol {
		enum Type { TYPE_NONE, TYPE_SYMBOL, TYPE_FUNCTION };
		Type type;
		string display;
		string name;
		vector<string> parameters;
		string returnValue;
	};

	bool countEnabled { false };

	// overridden methods
	void onCameraRotation() override;
	void onCameraScale() override;

public:
	// forbid class copy
	FORBID_CLASS_COPY(UIEditorTabView)

	/**
	 * Public constructor
	 * @param editorView editor view
	 * @param tabId tab id
	 * @param screenNode screenNode
	 * @param fileName screen XML file name
	 */
	UIEditorTabView(EditorView* editorView, const string& tabId, GUIScreenNode* screenNode, const string& fileName);

	/**
	 * Destructor
	 */
	~UIEditorTabView();

	/**
	 * @returns filename of opened file
	 */
	inline const string& getFileName() {
		return screenFileName;
	}

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
		return uiTabController.get();
	}

	/**
	 * @returns pop up views
	 */
	inline PopUps* getPopUps() {
		return popUps;
	}

	/**
	 * @returns UI screen nodes
	 */
	inline vector<UIScreenNode>& getUIScreenNodes() {
		return uiScreenNodes;
	}

	/**
	 * Add screen
	 */
	void addScreen();

	/**
	 * Set screen
	 * @param screenIdx screen index
	 * @param fileName file name
	 */
	void setScreen(int screenIdx, const string& fileName);

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
	 * Remove screens
	 */
	void removeScreens();

	/**
	 * Readd screens
	 */
	void reAddScreens();

	/**
	 * @returns prototype
	 */
	Prototype* getPrototype();

	/**
	 * Load prototype
	 * @param pathName path name
	 * @param fileName file name
	 * @param modelMeshNode model mesh node
	 * @param modelMeshAnimation model mesh animation
	 * @returns model
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

	/**
	 * @returns current screen index
	 */
	inline int getScreenIdx() {
		return screenIdx;
	}

	/**
	 * Set screen index
	 * @param screenIdx screen index
	 */
	void setScreenIdx(int screenIdx);

	/**
	 * Store UI XML
	 */
	void storeUIXML();

	/**
	 * Set visual mode
	 */
	void setVisualEditor();

	/**
	 * Set text mode
	 */
	void setCodeEditor();

	/**
	 * Update code editor
	 */
	void updateCodeEditor();

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

	/**
	 * @returns text index
	 */
	int getTextIndex();

	/**
	 * Find string
	 * @param findString find string
	 * @param matchCase only find string that also matches case in find string
	 * @param wholeWord only find whole worlds
	 * @param selection only find in selection
	 * @param firstSearch first search
	 * @param index index
	 * @returns success
	 */
	bool find(const string& findString, bool matchCase, bool wholeWord, bool selection, bool firstSearch, int& index);

	/**
	 * Count string
	 * @param findString find string
	 * @param matchCase only find string that also matches case in find string
	 * @param wholeWord only find whole worlds
	 * @param selection only find in selection
	 */
	int count(const string& findString, bool matchCase, bool wholeWord, bool selection);

	/**
	 * Replace string
	 * @param findString find string
	 * @param replaceString replace string
	 * @param matchCase only find string that also matches case in find string
	 * @param wholeWord only find whole worlds
	 * @param selection only find in selection
	 * @param index index
	 * @returns success
	 */
	bool replace(const string& findString, const string& replaceString, bool matchCase, bool wholeWord, bool selection, int& index);

	/**
	 * Replace all string
	 * @param findString find string
	 * @param replaceString replace string
	 * @param matchCase only find string that also matches case in find string
	 * @param wholeWord only find whole worlds
	 * @param selection only find in selection
	 * @returns success
	 */
	bool replaceAll(const string& findString, const string& replaceString, bool matchCase, bool wholeWord, bool selection);

	/**
	 * Cancel find
	 */
	void cancelFind();

	/**
	 * Redo
	 */
	void redo();

	/**
	 * Redo
	 */
	void undo();

	/**
	 * Select all
	 */
	void selectAll();

	/**
	 * Cut
	 */
	void cut();

	/**
	 * Copy
	 */
	void copy();

	/**
	 * Paste
	 */
	void paste();

	/**
	 * Delete
	 */
	void delete_();

};
