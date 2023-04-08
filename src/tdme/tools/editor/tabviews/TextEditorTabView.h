#pragma once

#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/engine/DynamicColorTexture.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIStyledTextNodeController.h>
#include <tdme/tools/editor/controllers/ContextMenuScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/TextFormatter.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabcontrollers/TextEditorTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/fwd-tdme.h>
#include <tdme/utilities/MiniScript.h>

using std::string;
using std::to_string;
using std::unordered_map;

using tdme::engine::DynamicColorTexture;
using tdme::engine::Engine;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUIStyledTextNode;
using tdme::gui::nodes::GUIStyledTextNodeController;
using tdme::tools::editor::controllers::ContextMenuScreenController;
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
	, public ContextMenuScreenController::MiniScriptMethodSelectionListener
{
protected:
	Engine* engine { nullptr };

private:
	static constexpr int MINISCRIPT_SCRIPTIDX_STRUCTURE { -1 };

	EditorView* editorView { nullptr };
	string tabId;
	PopUps* popUps { nullptr };
	TextEditorTabController* textEditorTabController { nullptr };
	TabView::OutlinerState outlinerState;
	GUIScreenNode* screenNode { nullptr };
	string fileName;
	string extension;
	GUIStyledTextNode* textNode { nullptr };
	GUIStyledTextNodeController::ChangeListener* textNodeChangeListener { nullptr };
	GUIStyledTextNodeController::CodeCompletionListener* textNodeCodeCompletionListener { nullptr };
	const TextFormatter::CodeCompletion* codeCompletion { nullptr };

	struct CodeCompletionSymbol {
		enum Type { TYPE_NONE, TYPE_SYMBOL, TYPE_FUNCTION };
		Type type;
		string display;
		string name;
		vector<string> parameters;
		string returnValue;
	};

	int miniScriptScriptIdx { MINISCRIPT_SCRIPTIDX_STRUCTURE };

	float scrollX { 0.0f };
	float scrollY { 0.0f };

	/**
	 * Compare CodeCompletionSymbol structs
	 * @return lhs < rhs
	 */
	static bool compareCodeCompletionStruct(const CodeCompletionSymbol& lhs, const CodeCompletionSymbol& rhs) {
		return lhs.display < rhs.display;
	}

	DynamicColorTexture* linesTexture { nullptr };
	int createConnectionsPasses { -1 };

	struct Node {
		enum NodeType { NODETYPE_NONE, NODETYPE_FLOW, NODETYPE_ARGUMENT };
		string id;
		NodeType type { NODETYPE_NONE };
		string value;
		MiniScript::ScriptVariableType returnValueType;
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

	struct MiniScriptBranch {
		string name;
		MiniScript::ScriptSyntaxTreeNode* conditionSyntaxTree { nullptr };
		vector<MiniScript::ScriptSyntaxTreeNode*> syntaxTreeNodes;
	};

	unordered_map<string, string> methodOperatorMap;
	unordered_map<string, Node> nodes;
	enum CreateConnectionMode { CREATECONNECTIONMODE_NONE, CREATECONNECTIONMODE_FLOW, CREATECONNECTIONMODE_ARGUMENT };
	CreateConnectionMode createConnectionMode { CREATECONNECTIONMODE_NONE };
	int createConnectionIdx = -1;
	vector<Connection> connections;
	bool visualEditor { false };
	bool visualCodingEnabled { false };

	GUIParentNode* visualisationNode { nullptr };
	bool countEnabled { false };

	int nodeIdx;

	/**
	 * @return start node which is the node with a flow output but no flow input
	 */
	inline const string getStartNodeId() {
		// we only look for flow node ids
		vector<string> flowNodeIds;
		for (auto& nodeIt: nodes) {
			auto& node = nodeIt.second;
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
			for (auto& connection: connections) {
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
	 * @return next node id
	 */
	inline const string getNextNodeId(const string& nodeId) {
		auto flowNodeId = nodeId + "_fo";
		for (auto& connection: connections) {
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
	 * @return argument node id
	 */
	inline const string getArgumentNodeId(const string& nodeId, int argumentIdx) {
		return nodeId + "_a" + to_string(argumentIdx);
	}

	/**
	 * Find argument node id
	 * @param nodeId node id
	 * @param argumentIdx argument index
	 * @return argument node id
	 */
	inline const string getConnectedArgumentNodeId(const string& nodeId, int argumentIdx) {
		auto argumentNodeId = getArgumentNodeId(nodeId, argumentIdx);
		for (auto& connection: connections) {
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
	 * @return condition node id
	 */
	inline const string getConditionNodeId(const string& nodeId, int conditionIdx) {
		return nodeId + "_c" + to_string(conditionIdx);
	}

	/**
	 * Find condition node id
	 * @param nodeId node id
	 * @param conditionIdx condition index
	 * @return condition node id
	 */
	inline const string getConnectedConditionNodeId(const string& nodeId, int conditionIdx) {
		auto conditionNodeId = getConditionNodeId(nodeId, conditionIdx);
		for (auto& connection: connections) {
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
	 * @return branch node id
	 */
	inline const string getBranchNodeId(const string& nodeId, int branchIdx) {
		return nodeId + "_b" + to_string(branchIdx);
	}

	/**
	 * Find branch node id
	 * @param nodeId node id
	 * @param branchIdx branch index
	 * @return branch node id
	 */
	inline const string getConnectedBranchNodeId(const string& nodeId, int branchIdx) {
		auto branchNodeId = getBranchNodeId(nodeId, branchIdx);
		for (auto& connection: connections) {
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
	 * @return node
	 */
	inline Node* getNodeById(const string& nodeId) {
		auto nodeIt = nodes.find(nodeId);
		if (nodeIt != nodes.end()) return &nodeIt->second;
		return nullptr;
	}

	/**
	 * Get script variable type pin color
	 * @param type type
	 * @return string with color property name from theme
	 */
	inline const string getScriptVariableTypePinColor(MiniScript::ScriptVariableType type) {
		switch (type) {
			case MiniScript::ScriptVariableType::TYPE_BOOLEAN:
				return string("color.pintype_boolean");
			case MiniScript::ScriptVariableType::TYPE_INTEGER:
				return string("color.pintype_integer");
			case MiniScript::ScriptVariableType::TYPE_FLOAT:
				return string("color.pintype_float");
			case MiniScript::ScriptVariableType::TYPE_STRING:
				return string("color.pintype_string");
			case MiniScript::ScriptVariableType::TYPE_VECTOR2:
			case MiniScript::ScriptVariableType::TYPE_VECTOR3:
			case MiniScript::ScriptVariableType::TYPE_VECTOR4:
				return string("color.pintype_vector");
			case MiniScript::ScriptVariableType::TYPE_QUATERNION:
			case MiniScript::ScriptVariableType::TYPE_MATRIX3x3:
			case MiniScript::ScriptVariableType::TYPE_MATRIX4x4:
			case MiniScript::ScriptVariableType::TYPE_TRANSFORM:
				return string("color.pintype_transform");
			case MiniScript::ScriptVariableType::TYPE_ARRAY:
			case MiniScript::ScriptVariableType::TYPE_MAP:
			case MiniScript::ScriptVariableType::TYPE_SET:
			case MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED:
			case MiniScript::ScriptVariableType::TYPE_NULL:
				return string("color.pintype_undefined");
			case MiniScript::ScriptVariableType::TYPE_PSEUDO_NUMBER:
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
		return screenNode;
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
	 * @return is showing visual editor
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
	 * Create MiniScript node
	 * @param methodName method name
	 * @param id id
	 * @param x x
	 * @param y y
	 */
	void createMiniScriptNode(const string& methodName, int x, int y);

	/**
	 * Get MiniScript node flattened id from hierarchical id
	 * @param hierarchicalId hierarchical id
	 * @return flattened id
	 */
	inline const string getMiniScriptNodeFlattenedId(unordered_map<string, string>& idMapping, const string& hierarchicalId) {
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
	void addMiniScriptNodeDeltaX(unordered_map<string, string>& idMapping, const string& id, const MiniScript::ScriptSyntaxTreeNode& syntaxTreeNode, int deltaX);

	/**
	 * Create UI nodes for MiniScript script node syntax tree, which matches a event or function in MiniScript
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
	void createMiniScriptScriptNode(unordered_map<string, string>& idMapping, const string& id, MiniScript::Script::ScriptType scriptType, const string& condition, const string& readableName, const MiniScript::ScriptSyntaxTreeNode* conditionSyntaxTreeNode, int x, int y, int& width, int& height);

	/**
	 * Create UI nodes for given statement syntax tree, which matches a statement in miniscript
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
	void createMiniScriptNodes(unordered_map<string, string>& idMapping, const string& id, int syntaxTreeNodeIdx, int syntaxTreeNodeCount, const MiniScript::ScriptSyntaxTreeNode* syntaxTreeNode, Node::NodeType nodeType, int x, int y, int& width, int& height, vector<string>& createdNodeIds, int depth = 0);

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
	void createMiniScriptBranchNodes(unordered_map<string, string>& idMapping, const string& id, int syntaxTreeNodeIdx, int syntaxTreeNodeCount, const MiniScript::ScriptSyntaxTreeNode* syntaxTreeNode, Node::NodeType nodeType, const vector<MiniScriptBranch>& branches, int x, int y, int& width, int& height, vector<string>& createdNodeIds, int depth = 0);

	/**
	 * @return MiniScript script index
	 */
	inline int getMiniScriptScriptIdx() {
		return miniScriptScriptIdx;
	}

	/**
	 * Set method -> operator map
	 * @param methodOperatorMap method operator map
	 */
	inline void setMiniScriptMethodOperatorMap(const unordered_map<string, string>& methodOperatorMap) {
		this->methodOperatorMap = methodOperatorMap;
	}

	/**
	 * Handle MiniScript branch
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
	bool handleMiniScriptBranch(unordered_map<string, string>& idMapping, const string& idPrefix, const vector<MiniScript::ScriptSyntaxTreeNode*>& syntaxTree, int& i, int x, int y, int& width, int& height, vector<string>& createdNodeIds);

	/**
	 * Update miniscript syntax tree
	 * @param miniScriptScriptIdx MiniScript script index
	 */
	void updateMiniScriptSyntaxTree(int miniScriptScriptIdx);

	/**
	 * Create miniscript connections
	 */
	void createMiniScriptConnections();

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
	 * @return text index
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
	 * @return success
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
	 * @return success
	 */
	bool replace(const string& findString, const string& replaceString, bool matchCase, bool wholeWord, bool selection, int& index);

	/**
	 * Replace all string
	 * @param findString find string
	 * @param replaceString replace string
	 * @param matchCase only find string that also matches case in find string
	 * @param wholeWord only find whole worlds
	 * @param selection only find in selection
	 * @return success
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
	 * Delete node
	 * @param nodeId node id
	 */
	void deleteNode(const string& nodeId);

	/**
	 * Returns if creating a connection currently
	 * @return if creating a connection currently
	 */
	inline bool isCreatingConnection() {
		return createConnectionMode != CREATECONNECTIONMODE_NONE;
	}

	/**
	 * Create connection with given start or end node id
	 * @param nodeId node id
	 */
	void createConnection(const string& nodeId);

	/**
	 * Finish creating connection
	 */
	void finishCreateConnection();

	/**
	 * Set up context menu
	 */
	void setupContextMenu();
};
