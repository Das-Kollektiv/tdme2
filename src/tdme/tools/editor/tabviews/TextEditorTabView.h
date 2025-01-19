#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/engine/DynamicColorTexture.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/nodes/GUIStyledTextNodeController.h>
#include <tdme/tools/editor/controllers/ContextMenuScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/TextFormatter.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabcontrollers/TextEditorTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/fwd-tdme.h>
#include <tdme/minitscript/EngineMinitScript.h>
#include <tdme/utilities/StringTools.h>

using std::string;
using std::to_string;
using std::unique_ptr;
using std::unordered_map;

using tdme::engine::DynamicColorTexture;
using tdme::engine::Engine;
using agui::gui::events::GUIMoveListener;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::nodes::GUIStyledTextNode;
using agui::gui::nodes::GUIStyledTextNodeController;
using tdme::tools::editor::controllers::ContextMenuScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::TextFormatter;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabcontrollers::TextEditorTabController;
using tdme::tools::editor::tabviews::TabView;
using tdme::tools::editor::views::EditorView;
using tdme::minitscript::EngineMinitScript;
using tdme::utilities::StringTools;

/**
 * Text editor tab view
 * @author Andreas Drewke
 */
class tdme::tools::editor::tabviews::TextEditorTabView final
	: public TabView
	, public ContextMenuScreenController::MinitScriptMethodSelectionListener
{
protected:
	unique_ptr<Engine> engine;

private:
	static constexpr int MINISCRIPT_SCRIPTIDX_STRUCTURE { -1 };

	EditorView* editorView { nullptr };
	string tabId;
	PopUps* popUps { nullptr };
	unique_ptr<TextEditorTabController> textEditorTabController;
	TabView::OutlinerState outlinerState;
	GUIScreenNode* screenNode { nullptr };
	string fileName;
	string extension;
	GUIStyledTextNode* textNode { nullptr };
	unique_ptr<GUIMoveListener> guiMoveListener;
	unique_ptr<GUIStyledTextNodeController::ChangeListener> textNodeChangeListener;
	unique_ptr<GUIStyledTextNodeController::CodeCompletionListener> textNodeCodeCompletionListener;
	unique_ptr<const TextFormatter::CodeCompletion> codeCompletion;

	struct CodeCompletionSymbol {
		enum Type { TYPE_NONE, TYPE_SYMBOL, TYPE_FUNCTION };
		Type type;
		string display;
		string name;
		vector<string> parameters;
		string returnValue;
	};

	int minitScriptScriptIdx { MINISCRIPT_SCRIPTIDX_STRUCTURE };

	float scrollX { 0.0f };
	float scrollY { 0.0f };

	unique_ptr<DynamicColorTexture> linesTexture;
	int createConnectionsPasses { -1 };

	struct Node {
		enum NodeType { NODETYPE_NONE, NODETYPE_FLOW, NODETYPE_ARGUMENT };
		string id;
		NodeType type { NODETYPE_NONE };
		string value;
		EngineMinitScript::VariableType returnValueType;
		int left;
		int top;
	};

	struct Connection {
		enum ConnectionType { CONNECTIONTYPE_NONE, CONNECTIONTYPE_FLOW, CONNECTIONTYPE_ARGUMENT };
		ConnectionType type { CONNECTIONTYPE_NONE };
		string srcNodeId;
		string dstNodeId;
		uint8_t red;
		uint8_t green;
		uint8_t blue;
		uint8_t alpha;
		int x1;
		int y1;
		int x2;
		int y2;
	};

	struct MinitScriptBranch {
		string name;
		EngineMinitScript::SyntaxTreeNode* conditionSyntaxTree { nullptr };
		vector<EngineMinitScript::SyntaxTreeNode*> syntaxTreeNodes;
	};

	unordered_map<string, string> methodOperatorMap;
	unordered_map<string, Node> nodes;
	enum CreateConnectionMode {
		CREATECONNECTIONMODE_NONE,
		CREATECONNECTIONMODE_FLOW_OUT,
		CREATECONNECTIONMODE_FLOW_IN,
		CREATECONNECTIONMODE_ARGUMENT_OUT,
		CREATECONNECTIONMODE_ARGUMENT_IN
	};
	/**
	 * @returns Returns the create connection mode name
	 */
	inline static const string getCreateConnectionModeName(CreateConnectionMode createConnectionMode) {
		switch (createConnectionMode) {
			case CREATECONNECTIONMODE_FLOW_OUT: return "Flow Output";
			case CREATECONNECTIONMODE_FLOW_IN: return "Flow Input";
			case CREATECONNECTIONMODE_ARGUMENT_OUT: return "Argument Output";
			case CREATECONNECTIONMODE_ARGUMENT_IN: return "Argument Input";
			case CREATECONNECTIONMODE_NONE: return "None";
			default: return "Invalid";
		}
	}
	CreateConnectionMode createConnectionMode { CREATECONNECTIONMODE_NONE };
	int createConnectionIdx = -1;
	vector<Connection> connections;
	bool visualEditor { false };
	bool visualCodingEnabled { false };

	GUIParentNode* visualisationNode { nullptr };
	bool countEnabled { false };

	int nodeIdx;

	/**
	 * @returns start node which is the node with a flow output but no flow input
	 */
	inline const string getStartNodeId() {
		// we only look for flow node ids
		vector<string> flowNodeIds;
		for (const auto& [nodeId, node]: nodes) {
			if (node.type != Node::NODETYPE_FLOW) continue;
			flowNodeIds.push_back(node.id);
		}
		// iterate over node ids
		// iterate over connections
		// check if a flow connection exists from any node to current node id
		// if so its not the start node :D
		for (const auto& nodeId: flowNodeIds) {
			auto flowNodeId = nodeId + "_fi";
			auto foundFlowInput = false;
			for (const auto& connection: connections) {
				if (connection.type != Connection::CONNECTIONTYPE_FLOW) continue;
				if (connection.dstNodeId == flowNodeId) {
					foundFlowInput = true;
				}
			}
			if (foundFlowInput == false) return nodeId;
		}
		return string();
	}

	/**
	 * Find next node
	 * @param nodeId node id to find next node to
	 * @returns next node id
	 */
	inline const string getNextNodeId(const string& nodeId) {
		auto flowNodeId = nodeId + "_fo";
		for (const auto& connection: connections) {
			if (connection.type != Connection::CONNECTIONTYPE_FLOW) continue;
			if (connection.srcNodeId == flowNodeId) {
				//
				auto separatorIdx = connection.dstNodeId.find('_');
				return StringTools::substring(connection.dstNodeId, 0, separatorIdx == string::npos?connection.dstNodeId.size():separatorIdx);
			}
		}
		return string();
	}

	/**
	 * Create argument node id
	 * @param nodeId node id
	 * @param argumentIdx argument index
	 * @returns argument node id
	 */
	inline const string getArgumentNodeId(const string& nodeId, int argumentIdx) {
		return nodeId + "_a" + to_string(argumentIdx);
	}

	/**
	 * Find argument node id
	 * @param nodeId node id
	 * @param argumentIdx argument index
	 * @returns argument node id
	 */
	inline const string getConnectedArgumentNodeId(const string& nodeId, int argumentIdx) {
		auto argumentNodeId = getArgumentNodeId(nodeId, argumentIdx);
		for (const auto& connection: connections) {
			if (connection.type != Connection::CONNECTIONTYPE_ARGUMENT) continue;
			if (connection.srcNodeId == argumentNodeId) {
				//
				auto separatorIdx = connection.dstNodeId.find('_');
				return StringTools::substring(connection.dstNodeId, 0, separatorIdx == string::npos?connection.dstNodeId.size():separatorIdx);
			}
		}
		return string();
	}

	/**
	 * Create condition node id
	 * @param nodeId node id
	 * @param conditionIdx condition index
	 * @returns condition node id
	 */
	inline const string getConditionNodeId(const string& nodeId, int conditionIdx) {
		return nodeId + "_c" + to_string(conditionIdx);
	}

	/**
	 * Find condition node id
	 * @param nodeId node id
	 * @param conditionIdx condition index
	 * @returns condition node id
	 */
	inline const string getConnectedConditionNodeId(const string& nodeId, int conditionIdx) {
		auto conditionNodeId = getConditionNodeId(nodeId, conditionIdx);
		for (const auto& connection: connections) {
			if (connection.type != Connection::CONNECTIONTYPE_ARGUMENT) continue;
			if (connection.srcNodeId == conditionNodeId) {
				//
				auto separatorIdx = connection.dstNodeId.find('_');
				return StringTools::substring(connection.dstNodeId, 0, separatorIdx == string::npos?connection.dstNodeId.size():separatorIdx);
			}
		}
		return string();
	}

	/**
	 * Create branch node id
	 * @param nodeId node id
	 * @param branchIdx branch index
	 * @returns branch node id
	 */
	inline const string getBranchNodeId(const string& nodeId, int branchIdx) {
		return nodeId + "_b" + to_string(branchIdx);
	}

	/**
	 * Find branch node id
	 * @param nodeId node id
	 * @param branchIdx branch index
	 * @returns branch node id
	 */
	inline const string getConnectedBranchNodeId(const string& nodeId, int branchIdx) {
		auto branchNodeId = getBranchNodeId(nodeId, branchIdx);
		for (const auto& connection: connections) {
			if (connection.type != Connection::CONNECTIONTYPE_FLOW) continue;
			if (connection.srcNodeId == branchNodeId) {
				//
				auto separatorIdx = connection.dstNodeId.find('_');
				return StringTools::substring(connection.dstNodeId, 0, separatorIdx == string::npos?connection.dstNodeId.size():separatorIdx);
			}
		}
		return string();
	}

	/**
	 * Get node by id
	 * @param nodeId node id
	 * @returns node
	 */
	inline Node* getNodeById(const string& nodeId) {
		auto nodeIt = nodes.find(nodeId);
		if (nodeIt != nodes.end()) return &nodeIt->second;
		return nullptr;
	}

	/**
	 * Get script variable type pin color
	 * @param type type
	 * @returns string with color property name from theme
	 */
	inline const string getVariableTypePinColor(EngineMinitScript::VariableType type) {
		switch (type) {
			case EngineMinitScript::VariableType::TYPE_BOOLEAN:
				return string("color.pintype_boolean");
			case EngineMinitScript::VariableType::TYPE_INTEGER:
				return string("color.pintype_integer");
			case EngineMinitScript::VariableType::TYPE_FLOAT:
				return string("color.pintype_float");
			case EngineMinitScript::VariableType::TYPE_STRING:
				return string("color.pintype_string");
			case EngineMinitScript::TYPE_VECTOR2:
			case EngineMinitScript::TYPE_VECTOR3:
			case EngineMinitScript::TYPE_VECTOR4:
				return string("color.pintype_vector");
			case EngineMinitScript::TYPE_QUATERNION:
			case EngineMinitScript::TYPE_MATRIX3x3:
			case EngineMinitScript::TYPE_MATRIX4x4:
			case EngineMinitScript::TYPE_TRANSFORM:
				return string("color.pintype_transform");
			case EngineMinitScript::VariableType::TYPE_ARRAY:
			case EngineMinitScript::VariableType::TYPE_MAP:
			case EngineMinitScript::VariableType::TYPE_SET:
			case EngineMinitScript::VariableType::TYPE_PSEUDO_MIXED:
			case EngineMinitScript::VariableType::TYPE_NULL:
				return string("color.pintype_undefined");
			case EngineMinitScript::VariableType::TYPE_PSEUDO_NUMBER:
				return string("color.pintype_float");
		}
		return string("color.pintype_undefined");
	}

	const array<string, 6> flowControlNodes = {
		"if",
		"elseif",
		"else",
		"forTime",
		"forCondition",
		"end",
	};

	const array<string, 12> mathNodes = {
		"int",
		"float",
		"math",
		"vec2",
		"vec3",
		"vec4",
		"mat3",
		"mat4",
		"quaternion",
		"mat3",
		"mat4",
		"transform"
	};

public:
	// forbid class copy
	FORBID_CLASS_COPY(TextEditorTabView)

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
	 * @returns file name
	 */
	inline const string& getFileName() {
		return fileName;
	}

	/**
	 * @returns lower case extension
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
	 * @returns code completion
	 * TODO: maybe move me into controller
	 */
	const TextFormatter::CodeCompletion* getCodeCompletion() {
		return codeCompletion.get();
	}

	/**
	 * @returns editor view
	 */
	inline EditorView* getEditorView() {
		return editorView;
	}

	/**
	 * @returns tab screen node
	 */
	inline GUIScreenNode* getTabScreenNode() {
		return screenNode;
	}

	/**
	 * @returns associated tab controller
	 */
	inline TabController* getTabController() override {
		return textEditorTabController.get();
	}

	/**
	 * @returns pop up views
	 */
	inline PopUps* getPopUps() {
		return popUps;
	}

	/**
	 * @returns is showing visual editor
	 */
	inline bool isVisualEditor() {
		return visualEditor;
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
	 * Create EngineMinitScript node
	 * @param methodName method name
	 * @param id id
	 * @param x x
	 * @param y y
	 */
	void createMinitScriptNode(const string& methodName, int x, int y);

	/**
	 * Get EngineMinitScript node flattened id from hierarchical id
	 * @param hierarchicalId hierarchical id
	 * @returns flattened id
	 */
	inline const string getMinitScriptNodeFlattenedId(unordered_map<string, string>& idMapping, const string& hierarchicalId) {
		auto idMappingIt = idMapping.find(hierarchicalId);
		if (idMappingIt != idMapping.end()) {
			return idMappingIt->second;
		}
		auto flattenedId = to_string(idMapping.size());
		idMapping[hierarchicalId] = flattenedId;
		return flattenedId;
	}

	/**
	 * Adds a delta X value to UI node with given id and all nodes down the statement syntax tree
	 * @param idMapping id mapping
	 * @param id id
	 * @param syntaxTreeNode syntax tree node
	 * @param deltaX delta X
	 */
	void addMinitScriptNodeDeltaX(unordered_map<string, string>& idMapping, const string& id, const EngineMinitScript::SyntaxTreeNode& syntaxTreeNode, int deltaX);

	/**
	 * Create UI nodes for EngineMinitScript script node syntax tree, which matches a event or function in EngineMinitScript
	 * @param idMapping id mapping
	 * @param id id
	 * @param scriptType script type
	 * @param condition condition
	 * @param readableName readableName
	 * @param conditionSyntaxTreeNode condition syntax tree node
	 * @param x x
	 * @param y y
	 * @param width width
	 * @param height height
	 * @param createdNodeIds created node ids
	 */
	void createMinitScriptScriptNode(unordered_map<string, string>& idMapping, const string& id, EngineMinitScript::Script::Type scriptType, const string& condition, const string& readableName, const EngineMinitScript::SyntaxTreeNode* conditionSyntaxTreeNode, int x, int y, int& width, int& height);

	/**
	 * Create UI nodes for given statement syntax tree, which matches a statement in minitscript
	 * @param idMapping id mapping
	 * @param id id
	 * @param syntaxTreeNodeIdx syntax tree node index
	 * @param syntaxTreeNodeCount syntax tree node count
	 * @param syntaxTreeNode syntax tree node
	 * @param nodeType node type
	 * @param x x
	 * @param y y
	 * @param width width
	 * @param height height
	 * @oaram createdNodeIds created node ids
	 * @param depth depth
	 */
	void createMinitScriptNodes(unordered_map<string, string>& idMapping, const string& id, int syntaxTreeNodeIdx, int syntaxTreeNodeCount, const EngineMinitScript::SyntaxTreeNode* syntaxTreeNode, Node::NodeType nodeType, int x, int y, int& width, int& height, vector<string>& createdNodeIds, int depth = 0);

	/**
	 * Create UI nodes for branch nodes like if, elseif, else, end; forTime, end; forCondition, end
	 * @param idMapping id mapping
	 * @param id id
	 * @param syntaxTreeNodeIdx syntax tree node index
	 * @param syntaxTreeNodeCount syntax tree node count
	 * @param syntaxTreeNode syntax tree node
	 * @param nodeType node type
	 * @param branches branches
	 * @param x x
	 * @param y y
	 * @param width width
	 * @param height height
	 * @oaram createdNodeIds created node ids
	 * @param depth depth
	 */
	void createMinitScriptBranchNodes(unordered_map<string, string>& idMapping, const string& id, int syntaxTreeNodeIdx, int syntaxTreeNodeCount, const EngineMinitScript::SyntaxTreeNode* syntaxTreeNode, Node::NodeType nodeType, const vector<MinitScriptBranch>& branches, int x, int y, int& width, int& height, vector<string>& createdNodeIds, int depth = 0);

	/**
	 * @returns MinitScript script index
	 */
	inline int getMinitScriptScriptIdx() {
		return minitScriptScriptIdx;
	}

	/**
	 * Set method -> operator map
	 * @param methodOperatorMap method operator map
	 */
	inline void setMinitScriptMethodOperatorMap(const unordered_map<string, string>& methodOperatorMap) {
		this->methodOperatorMap = methodOperatorMap;
	}

	/**
	 * Handle EngineMinitScript branch
	 * @param idMapping id mapping
	 * @param idPrefix id prefix
	 * @param syntaxTree syntax tree
	 * @param i iterator
	 * @param x x
	 * @param y y
	 * @param width width
	 * @param height height
	 * @oaram createdNodeIds created node ids
	 */
	bool handleMinitScriptBranch(unordered_map<string, string>& idMapping, const string& idPrefix, const vector<EngineMinitScript::SyntaxTreeNode*>& syntaxTree, int& i, int x, int y, int& width, int& height, vector<string>& createdNodeIds);

	/**
	 * Update minitscript syntax tree
	 * @param minitScriptScriptIdx MinitScript script index
	 */
	void updateMinitScriptSyntaxTree(int minitScriptScriptIdx);

	/**
	 * Create minitscript connections
	 */
	void createMinitScriptConnections();

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
	void onMethodSelection(const string& methodName);

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

	/**
	 * Create source code from nodes
	 * @param sourceCode source code
	 * @param node node
	 * @param depth depth
	 */
	void createSourceCodeFromNodes(string& sourceCode, const Node* node, int depth = 0);

	/**
	 * Create source code from node
	 * @param sourceCode source code
	 * @param node node
	 * @param depth depth
	 */
	void createSourceCodeFromNode(string& sourceCode, const Node* node, int depth = 0);

	/**
	 * Delete connection
	 * @param nodeId node id
	 */
	void deleteConnection(const string& nodeId);

	/**
	 * Delete node
	 * @param nodeId node id
	 */
	void deleteNode(const string& nodeId);

	/**
	 * Returns if creating a connection currently
	 * @returns if creating a connection currently
	 */
	inline bool isCreatingConnection() {
		return createConnectionMode != CREATECONNECTIONMODE_NONE;
	}

	/**
	 * Create connection with given start or end node id
	 * @param guiNodeId GUI node id
	 */
	void createConnection(const string& guiNodeId);

	/**
	 * Finish creating connection
	 * @param mouseX mouse X
	 * @param mouseY mouse Y
	 */
	void finishCreateConnection(int mouseX, int mouseY);

	/**
	 * Set up context menu
	 */
	void setupContextMenu();
};
