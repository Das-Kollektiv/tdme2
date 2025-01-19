#pragma once

#include <memory>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/events/GUIContextMenuRequestListener.h>
#include <tdme/gui/events/GUIFocusListener.h>
#include <tdme/gui/events/GUITooltipRequestListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/minitscript/EngineMinitScript.h>

#include <ext/tinyxml/tinyxml.h>

using std::string;
using std::unique_ptr;
using std::vector;

using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::events::GUIContextMenuRequestListener;
using tdme::gui::events::GUIFocusListener;
using tdme::gui::events::GUITooltipRequestListener;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::TextEditorTabView;
using tdme::minitscript::EngineMinitScript;

using tinyxml::TiXmlAttribute;
using tinyxml::TiXmlDocument;
using tinyxml::TiXmlElement;

/**
 * Text editor tab controller
 * @author Andreas Drewke
 */
class tdme::tools::editor::tabcontrollers::TextEditorTabController final
	: public TabController
{
public:
	struct MinitScriptScriptSyntaxTree {
		EngineMinitScript::Script::Type type;
		string condition;
		string name;
		EngineMinitScript::SyntaxTreeNode conditionSyntaxTree;
		vector<EngineMinitScript::SyntaxTreeNode> syntaxTree;
	};

	enum ContextMenuType { CONTEXTMENUTYPE_NONE, CONTEXTMENUTYPE_NODE, CONTEXTMENUTYPE_CANVAS };
private:
	TextEditorTabView* view { nullptr };
	GUIScreenNode* screenNode { nullptr };
	PopUps* popUps { nullptr };
	vector<MinitScriptScriptSyntaxTree> minitScriptSyntaxTrees;
	bool firstSearch { true };
	int searchIndex { -1 };
	ContextMenuType contextMenuType { CONTEXTMENUTYPE_NONE };
	int contextMenuX { -1 };
	int contextMenuY { -1 };
	string contextMenuNodeId;

	int addNodeX { -1 };
	int addNodeY { -1 };

	unique_ptr<EngineMinitScript> scriptInstance;

public:
	// forbid class copy
	FORBID_CLASS_COPY(TextEditorTabController)

	/**
	 * Public constructor
	 * @param view view
	 */
	TextEditorTabController(TextEditorTabView* view);

	/**
	 * Destructor
	 */
	virtual ~TextEditorTabController();

	/**
	 * Get view
	 * @returns view
	 */
	inline TextEditorTabView* getView() {
		return view;
	}

	// overridden method
	inline GUIScreenNode* getScreenNode() override {
		return screenNode;
	}

	/**
	 * @returns EngineMinitScript
	 */
	inline EngineMinitScript* getMinitScript() {
		return scriptInstance.get();
	}

	/**
	 * Reset context menu
	 */
	inline void resetContextMenu() {
		contextMenuType = CONTEXTMENUTYPE_NONE;
		contextMenuX = -1;
		contextMenuY = -1;
		contextMenuNodeId.clear();
	}

	/**
	 * @returns context menu type
	 */
	inline ContextMenuType getContextMenuType() {
		return contextMenuType;
	}

	/**
	 * @returns context menu x
	 */
	inline int getContextMenuX() {
		return contextMenuX;
	}

	/**
	 * @returns context menu y
	 */
	inline int getContextMenuY() {
		return contextMenuY;
	}

	/**
	 * @returns context menu node id
	 */
	inline const string& getContextMenuNodeId() {
		return contextMenuNodeId;
	}

	/**
	 * @returns add node x
	 */
	inline int getAddNodeX() {
		return addNodeX;
	}

	/**
	 * @returns add node y
	 */
	inline int getAddNodeY() {
		return addNodeY;
	}

	// overridden methods
	void initialize(GUIScreenNode* screenNode) override;
	void dispose() override;
	void onChange(GUIElementNode* node) override;
	void onAction(GUIActionListenerType type, GUIElementNode* node) override;
	void onFocus(GUIElementNode* node) override;
	void onUnfocus(GUIElementNode* node) override;
	void onContextMenuRequest(GUIElementNode* node, int mouseX, int mouseY) override;
	void onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) override;
	void onTooltipCloseRequest() override;
	void onCommand(TabControllerCommand command) override;
	void onDrop(const string& payload, int mouseX, int mouseY) override;

	/**
	 * Set outliner content
	 */
	void setOutlinerContent();

	/**
	 * Set outliner add drop down content
	 */
	void setOutlinerAddDropDownContent();

	/**
	 * @returns minitscript syntax trees
	 */
	inline const vector<MinitScriptScriptSyntaxTree>& getMinitScriptSyntaxTrees() {
		return minitScriptSyntaxTrees;
	}

	/**
	 * Update EngineMinitScript syntax tree
	 * @param minitScriptScriptIdx MinitScript script index
	 */
	void updateMinitScriptSyntaxTree(int minitScriptScriptIdx);

	/**
	 * Close find/replace window
	 */
	void closeFindReplaceWindow();

	/**
	 * Show the information pop up / modal
	 * @param caption caption
	 * @param message message
	 */
	void showInfoPopUp(const string& caption, const string& message);

};
