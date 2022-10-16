#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/DynamicColorTexture.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIStyledTextNodeController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/TextFormatter.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabcontrollers/TextEditorTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/fwd-tdme.h>
#include <tdme/utilities/MiniScript.h>

using std::string;

using tdme::engine::DynamicColorTexture;
using tdme::engine::Engine;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUIStyledTextNode;
using tdme::gui::nodes::GUIStyledTextNodeController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::TextFormatter;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabcontrollers::TextEditorTabController;
using tdme::tools::editor::tabviews::TabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::MiniScript;

/**
 * Text editor tab view
 * @author Andreas Drewke
 */
class tdme::tools::editor::tabviews::TextEditorTabView final
	: public TabView
{
protected:
	Engine* engine { nullptr };

private:
	EditorView* editorView { nullptr };
	string tabId;
	PopUps* popUps { nullptr };
	TextEditorTabController* textEditorTabController { nullptr };
	TabView::OutlinerState outlinerState;
	GUIScreenNode* tabScreenNode { nullptr };
	string fileName;
	string extension;
	GUIStyledTextNode* textNode { nullptr };
	GUIStyledTextNodeController::ChangeListener* textNodeChangeListener { nullptr };
	GUIStyledTextNodeController::CodeCompletionListener* textNodeCodeCompletionListener { nullptr };
	const TextFormatter::CodeCompletion* codeCompletion { nullptr };
	vector<MiniScript::StatementDescription> description;

	struct CodeCompletionSymbol {
		enum Type { TYPE_NONE, TYPE_SYMBOL, TYPE_FUNCTION };
		Type type;
		string display;
		string name;
		vector<string> parameters;
		string returnValue;
	};

	/**
	 * Compare CodeCompletionSymbol structs
	 * @return lhs < rhs
	 */
	static bool compareCodeCompletionStruct(const CodeCompletionSymbol& lhs, const CodeCompletionSymbol& rhs) {
		return lhs.display < rhs.display;
	}

	DynamicColorTexture* linesTexture { nullptr };
	int linesCreationPasses { -1 };

	struct Node {
		int x1;
		int y1;
		int x2;
		int y2;
	};

	struct Connection {
		int x1;
		int y1;
		int x2;
		int y2;
	};

	vector<Node> nodes;
	vector<Connection> connections;

public:
	/**
	 * Public constructor
	 * @param editorView editor view
	 * @param tabId tab id
	 * @param screenNode screenNode
	 * @param fileName file name
	 */
	TextEditorTabView(EditorView* editorView, const string& tabId, GUIScreenNode* screenNode, const string& fileName);

	/**
	 * Destructor
	 */
	~TextEditorTabView();

	/**
	 * @return file name
	 */
	inline const string& getFileName() {
		return fileName;
	}

	/**
	 * @return lower case extension
	 */
	inline const string& getExtension() {
		return extension;
	}

	/**
	 * Save file
	 * @param pathName path name
	 * @param fileName file name
	 */
	void saveFile(const string& pathName, const string& fileName);

	/**
	 * @return code completion
	 * TODO: maybe move me into controller
	 */
	const TextFormatter::CodeCompletion* getCodeCompletion() {
		return codeCompletion;
	}

	/**
	 * @return editor view
	 */
	inline EditorView* getEditorView() {
		return editorView;
	}

	/**
	 * @return tab screen node
	 */
	inline GUIScreenNode* getTabScreenNode() {
		return tabScreenNode;
	}

	/**
	 * @return associated tab controller
	 */
	inline TabController* getTabController() override {
		return textEditorTabController;
	}

	/**
	 * @return pop up views
	 */
	inline PopUps* getPopUps() {
		return popUps;
	}

	/**
	 * Set visual editor
	 */
	void setVisualEditor();

	/**
	 * Set code editor
	 */
	void setCodeEditor();

	/**
	 * Adds a delta X value to UI node with given id and all nodes down the statement description tree
	 * @param id id
	 * @param description description
	 * @param parentNode parent node
	 * @param deltaX delta X
	 */
	void addNodeDeltaX(const string& id, const MiniScript::StatementDescription& description, GUIParentNode* parentNode, int deltaX);

	/**
	 * Create UI nodes for given statement description, which matches a statement in miniscript
	 * @param id id
	 * @param description description
	 * @param parentNode parent node
	 * @param x x
	 * @param y y
	 * @param width width
	 * @param height height
	 * @param depth depth
	 */
	void createNodes(const string& id, const MiniScript::StatementDescription& description, GUIParentNode* parentNode, int x, int y, int& width, int& height, int depth = 0);

	/**
	 * Set miniscript description
	 * @param description description
	 */
	void setMiniScriptDescription(const vector<MiniScript::StatementDescription>& description);

	/**
	 * Create connections
	 * @param id id
	 * @param description description
	 * @param parentNode parent node
	 */
	void createConnections(const string& id, const MiniScript::StatementDescription& description, GUIParentNode* parentNode);

	/**
	 * Create connections
	 */
	void createConnections();

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

};
