#include <tdme/tools/editor/tabviews/TextEditorTabView.h>

#include <algorithm>
#include <cctype>
#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/ColorTextureCanvas.h>
#include <tdme/engine/DynamicColorTexture.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/events/GUIMoveListener.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIImageNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUIStyledTextNode.h>
#include <tdme/gui/nodes/GUIStyledTextNodeController.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector2.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/controllers/ContextMenuScreenController.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/misc/TextFormatter.h>
#include <tdme/tools/editor/misc/TextTools.h>
#include <tdme/tools/editor/tabcontrollers/TextEditorTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Character.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/Properties.h>
#include <tdme/utilities/StringTools.h>

using std::sort;
using std::string;
using std::unordered_map;

using tdme::tools::editor::tabviews::TextEditorTabView;

using tdme::engine::model::Color4;
using tdme::engine::ColorTextureCanvas;
using tdme::engine::DynamicColorTexture;
using tdme::engine::Engine;
using tdme::gui::events::GUIMoveListener;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIImageNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUIStyledTextNode;
using tdme::gui::GUI;
using tdme::gui::GUIParser;
using tdme::math::Math;
using tdme::math::Vector2;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::controllers::ContextMenuScreenController;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::misc::TextFormatter;
using tdme::tools::editor::misc::TextTools;
using tdme::tools::editor::tabcontrollers::TextEditorTabController;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Character;
using tdme::utilities::Integer;
using tdme::utilities::Properties;
using tdme::utilities::StringTools;

TextEditorTabView::TextEditorTabView(EditorView* editorView, const string& tabId, GUIScreenNode* screenNode, const string& fileName)
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->screenNode = screenNode;
	this->popUps = editorView->getPopUps();
	this->textNode = required_dynamic_cast<GUIStyledTextNode*>(screenNode->getInnerNodeById("text"));
	this->fileName = fileName;
	auto fileNameLowerCase = StringTools::toLowerCase(fileName);
	this->extension =
		fileNameLowerCase == "makefile" || StringTools::endsWith(fileNameLowerCase, "/makefile")?"makefile":
		StringTools::substring(fileNameLowerCase, fileNameLowerCase.rfind('.') + 1, fileNameLowerCase.size());
	engine = Engine::createOffScreenInstance(512, 512, false, false, false);
	engine->setSceneColor(Color4(39.0f / 255.0f, 39.0f / 255.0f, 39.0f / 255.0f, 1.0f));
	engine->getGUI()->addScreen(screenNode->getId(), screenNode);
	engine->getGUI()->addRenderScreen(screenNode->getId());

	//
	visualCodingEnabled = extension == "tscript";
	if (visualCodingEnabled == true) {
		//
		visualisationNode = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("visualization_canvas"));
		//
		linesTexture = new DynamicColorTexture(engine->getWidth(), engine->getHeight());
		linesTexture->initialize();
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("visualization_texture"))->setTexture(linesTexture);
		// add node move listener
		class NodeMoveListener: public GUIMoveListener {
		public:
			NodeMoveListener(TextEditorTabView* textEditorTabView): textEditorTabView(textEditorTabView) {
			}
			void onMove(GUINode* node) {
				auto visualisationNode = textEditorTabView->visualisationNode;
				auto& nodeComputedConstraints = node->getComputedConstraints();
				auto xMax = nodeComputedConstraints.left + nodeComputedConstraints.width;
				auto yMax = nodeComputedConstraints.top + nodeComputedConstraints.height;
				visualisationNode->getComputedConstraints().width = Math::max(visualisationNode->getComputedConstraints().width, xMax);
				visualisationNode->getComputedConstraints().height = Math::max(visualisationNode->getComputedConstraints().height, yMax);
				visualisationNode->getRequestsConstraints().width = Math::max(visualisationNode->getRequestsConstraints().width, xMax);
				visualisationNode->getRequestsConstraints().height = Math::max(visualisationNode->getRequestsConstraints().height, yMax);
				textEditorTabView->createConnectionsPasses = 3;
			}
			void onRelease(GUINode* node, int mouseX, int mouseY) {
				// no op
			}
		private:
			TextEditorTabView* textEditorTabView;
		};
		screenNode->addMoveListener(new NodeMoveListener(this));
		// enable code mode
		setCodeEditor();
	}

	// initial text format
	TextFormatter::getInstance()->format(extension, textNode);
	// load code completion
	codeCompletion = TextFormatter::getInstance()->loadCodeCompletion(extension);

	//
	{
		// add text node change listener
		class TextChangeListener: public GUIStyledTextNodeController::ChangeListener {
		public:
			TextChangeListener(TextEditorTabView* textEditorTabView): textEditorTabView(textEditorTabView) {
			}

			virtual ~TextChangeListener() {
			}

			virtual void onRemoveText(int idx, int count) override {
				if (textEditorTabView->countEnabled == true) {
					TextFormatter::getInstance()->format(textEditorTabView->extension, textEditorTabView->textNode, 0, textEditorTabView->textNode->getText().size());
					textEditorTabView->countEnabled = false;
				} else {
					TextFormatter::getInstance()->format(textEditorTabView->extension, textEditorTabView->textNode, idx, idx + count);
				}
			}
			virtual void onInsertText(int idx, int count) override {
				if (textEditorTabView->countEnabled == true) {
					TextFormatter::getInstance()->format(textEditorTabView->extension, textEditorTabView->textNode, 0, textEditorTabView->textNode->getText().size());
					textEditorTabView->countEnabled = false;
				} else {
					TextFormatter::getInstance()->format(textEditorTabView->extension, textEditorTabView->textNode, idx, idx + count);
				}
			}
		private:
			TextEditorTabView* textEditorTabView;
		};
		required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController())->addChangeListener(textNodeChangeListener = new TextChangeListener(this));
	}

	//
	{
		// add code completion listener
		class TextCodeCompletionListener: public GUIStyledTextNodeController::CodeCompletionListener {
		public:
			TextCodeCompletionListener(TextEditorTabView* textEditorTabView): textEditorTabView(textEditorTabView) {
			}

			virtual ~TextCodeCompletionListener() {
			}

			virtual void onCodeCompletion(int idx) override {
				auto codeCompletion = textEditorTabView->codeCompletion;
				if (codeCompletion == nullptr) return;
				if (codeCompletion->delimiters.find(textEditorTabView->textNode->getText().getCharAt(idx)) != string::npos) {
					if (idx > 0) idx--;
				}
				auto previousDelimiterPos = textEditorTabView->textNode->getPreviousDelimiter(idx, codeCompletion->delimiters);
				string search = StringTools::substring(textEditorTabView->textNode->getText().getString(), previousDelimiterPos == 0?0:previousDelimiterPos + 1, idx);
				vector<CodeCompletionSymbol> codeCompletionSymbolCandidates;
				#define MAX_ENTRIES	40
				for (auto& symbol: codeCompletion->symbols) {
					if (StringTools::startsWith(symbol.name, search) == true) {
						if (symbol.overloadList.empty() == true) {
							if (codeCompletionSymbolCandidates.size() == MAX_ENTRIES) {
								codeCompletionSymbolCandidates.push_back(
									{
										.type = CodeCompletionSymbol::TYPE_NONE,
										.display = "...",
										.name = {},
										.parameters = {},
										.returnValue = {}
									}
								);
								break;
							} else {
								codeCompletionSymbolCandidates.push_back(
									{
										.type = CodeCompletionSymbol::TYPE_SYMBOL,
										.display = symbol.name,
										.name = symbol.name,
										.parameters = {},
										.returnValue = {}
									}
								);
							}
						} else {
							for (auto& overload: symbol.overloadList) {
								if (codeCompletionSymbolCandidates.size() == MAX_ENTRIES) {
									codeCompletionSymbolCandidates.push_back(
										{
											.type = CodeCompletionSymbol::TYPE_NONE,
											.display = "...",
											.name = {},
											.parameters = {},
											.returnValue = {}
										}
									);
									break;
								} else {
									string parameters;
									for (auto& parameter: overload.parameters) {
										if (parameters.empty() == false) parameters+= ", ";
										parameters+= parameter;
									}
									codeCompletionSymbolCandidates.push_back(
										{
											.type = CodeCompletionSymbol::TYPE_FUNCTION,
											.display = symbol.name + "(" + parameters + ") = " + overload.returnValue,
											.name = symbol.name,
											.parameters = overload.parameters,
											.returnValue = overload.returnValue
										}
									);
								}
							}
							if (codeCompletionSymbolCandidates.size() == MAX_ENTRIES + 1) break;
						}
					}
				}
				auto popUps = textEditorTabView->getPopUps();
				// clear
				popUps->getContextMenuScreenController()->clear();
				//
				sort(codeCompletionSymbolCandidates.begin(), codeCompletionSymbolCandidates.begin() + (Math::min(codeCompletionSymbolCandidates.size(), MAX_ENTRIES)), compareCodeCompletionStruct);
				//
				{
					auto i = 0;
					for (auto& codeCompletionSymbolCandidate: codeCompletionSymbolCandidates) {
						// add light
						class OnCodeCompletionAction: public virtual Action
						{
						public:
							OnCodeCompletionAction(TextEditorTabView* textEditorTabView, int idx, const CodeCompletionSymbol& symbol): textEditorTabView(textEditorTabView), idx(idx), symbol(symbol) {}
							void performAction() override {
								if (symbol.name.empty() == true) return;
								auto codeCompletion = textEditorTabView->codeCompletion;
								if (codeCompletion == nullptr) return;
								auto previousDelimiterPos = textEditorTabView->textNode->getPreviousDelimiter(idx, codeCompletion->delimiters);
								auto nextDelimiterPos = textEditorTabView->textNode->getNextDelimiter(idx, codeCompletion->delimiters);
								auto withoutWhiteSpaceDelimiters = codeCompletion->delimiters;
								if (withoutWhiteSpaceDelimiters.find(' ') != string::npos) withoutWhiteSpaceDelimiters.erase(withoutWhiteSpaceDelimiters.find(' '), 1);
								if (withoutWhiteSpaceDelimiters.find('\t') != string::npos) withoutWhiteSpaceDelimiters.erase(withoutWhiteSpaceDelimiters.find('\t'), 1);
								if (withoutWhiteSpaceDelimiters.find('\n') != string::npos) withoutWhiteSpaceDelimiters.erase(withoutWhiteSpaceDelimiters.find('\n'), 1);
								auto nextDelimiterPos2 = textEditorTabView->textNode->getNextDelimiter(idx, withoutWhiteSpaceDelimiters);
								auto idxToDelimiterString = StringTools::trim(StringTools::substring(textEditorTabView->textNode->getText().getString(), idx + 1 < textEditorTabView->textNode->getTextLength()?idx + 1:idx, nextDelimiterPos2));
								string parameterString;
								if (symbol.type == CodeCompletionSymbol::TYPE_FUNCTION && textEditorTabView->textNode->getText().getCharAt(nextDelimiterPos2) != '(') {
									for (auto parameter: symbol.parameters) {
										auto parameterTokenized = StringTools::tokenize(parameter, " \t\n");
										if (parameterString.empty() == false) parameterString+= ", ";
										parameterString+= parameterTokenized[parameterTokenized.size() - 1];
									}
									parameterString = "(" + parameterString + ")"/* + codeCompletion->statementDelimiter*/;
								}
								textEditorTabView->textNode->removeText(previousDelimiterPos == 0?0:previousDelimiterPos + 1, nextDelimiterPos - (previousDelimiterPos == 0?0:previousDelimiterPos + 1));
								textEditorTabView->textNode->insertText(previousDelimiterPos == 0?0:previousDelimiterPos + 1, symbol.name + parameterString);
								TextFormatter::getInstance()->format(textEditorTabView->extension, textEditorTabView->textNode, previousDelimiterPos == 0?0:previousDelimiterPos + 1, (previousDelimiterPos == 0?0:previousDelimiterPos + 1) + symbol.name.size() + parameterString.size());
							}
						private:
							TextEditorTabView* textEditorTabView;
							int idx;
							CodeCompletionSymbol symbol;
						};
						popUps->getContextMenuScreenController()->addMenuItem(codeCompletionSymbolCandidate.display, "contextmenu_codecompletion_" + to_string(i), new OnCodeCompletionAction(textEditorTabView, idx, codeCompletionSymbolCandidate));
						//
						i++;
					}
				}
				if (codeCompletionSymbolCandidates.empty() == false) {
					//
					int left, top, width, height, offsetX, offsetY;
					auto selectedTab = textEditorTabView->getEditorView()->getScreenController()->getSelectedTab();
					if (selectedTab != nullptr) {
						textEditorTabView->getEditorView()->getViewPort(selectedTab->getFrameBufferNode(), left, top, width, height, offsetX, offsetY);
						popUps->getContextMenuScreenController()->show(
							left + textEditorTabView->textNode->getIndexPositionX() - textEditorTabView->textNode->computeParentChildrenRenderOffsetXTotal(),
							top + textEditorTabView->textNode->getIndexPositionY() - textEditorTabView->textNode->computeParentChildrenRenderOffsetYTotal()
						);
					}
				}
			}
		private:
			TextEditorTabView* textEditorTabView;
		};
		required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController())->addCodeCompletionListener(textNodeCodeCompletionListener = new TextCodeCompletionListener(this));
	}
}

TextEditorTabView::~TextEditorTabView() {
	delete textEditorTabController;
	delete engine;
	delete textNodeChangeListener;
	delete textNodeCodeCompletionListener;
	if (codeCompletion != nullptr) delete codeCompletion;
}

void TextEditorTabView::saveFile(const string& pathName, const string& fileName) {
	auto text = textNode->getText().getString();
	FileSystem::getStandardFileSystem()->setContentFromString(
		pathName,
		fileName,
		text
	);
}

void TextEditorTabView::handleInputEvents()
{
	engine->getGUI()->handleEvents();
}



void TextEditorTabView::display()
{
	//
	if (visualCodingEnabled == true) {
		//
		setupContextMenu();

		//
		auto visualizationNode = required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("visualization"));

		auto scrolled = false;
		auto scrollXNew = visualizationNode->getChildrenRenderOffsetX();
		auto scrollYNew = visualizationNode->getChildrenRenderOffsetY();

		if (Float::equals(scrollXNew, scrollX) == false ||
			Float::equals(scrollYNew, scrollY) == false) {
			scrollX = scrollXNew;
			scrollY = scrollYNew;
			scrolled = true;
		}

		// resize?
		if (scrolled == true ||
			linesTexture->getWidth() != engine->getWidth() ||
			linesTexture->getHeight() != engine->getHeight()) {
			linesTexture->reshape(engine->getWidth(), engine->getHeight());
			auto visualizationTextureNode = dynamic_cast<GUIImageNode*>(screenNode->getNodeById("visualization_texture"));
			if (visualizationTextureNode != nullptr) visualizationTextureNode->setTexture(linesTexture);
			createConnectionsPasses = 3;
		}
		// we have a layouting issue here, we cant get dimensions of nodes right after adding them, so defer this for now
		if (createConnectionsPasses > 0) {
			auto visualizationScrollArea = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("visualization"));
			auto visualizationWidth = visualizationScrollArea->getComputedConstraints().width;
			auto visualizationHeight = visualizationScrollArea->getComputedConstraints().height;
			auto visualizationScrollX = static_cast<int>(scrollX);
			auto visualizationScrollY = static_cast<int>(scrollY);
			createMiniScriptConnections();
			// create lines
			ColorTextureCanvas canvas(linesTexture->getTexture());
			canvas.clear(0, 0, 0, 0);
			// grid dots
			for (auto y = 0; y < linesTexture->getHeight(); y+= 10) {
				for (auto x = 0; x < linesTexture->getWidth(); x+= 10) {
					canvas.drawPixel(Math::absmod(x - visualizationScrollX, linesTexture->getWidth()), Math::absmod(y - visualizationScrollY, linesTexture->getHeight()), 125, 125, 125, 50);
				}
			}
			// connections
			for (auto& connection: connections) {
				auto x1 = connection.x1 - visualizationScrollX;
				auto y1 = connection.y1 - visualizationScrollY;
				auto x2 = connection.x2 - visualizationScrollX;
				auto y2 = connection.y2 - visualizationScrollY;

				if ((x1 < 0 && x2 < 0) ||
					(x1 > visualizationWidth && x2 > visualizationWidth) ||
					(y1 < 0 && y2 < 0) ||
					(y1 > visualizationHeight && y2 > visualizationHeight)) continue;

				auto straightLineLength = Math::min(static_cast<float>(Math::abs(y2 - y1)), 50.0f);
				Vector2 srcVector1(x1, y1);
				Vector2 srcVector2(x1 + (x2 < x1?-straightLineLength:straightLineLength), y1);
				Vector2 dstVector1(x1 + (x2 < x1?-straightLineLength:straightLineLength), y2 - (y2 < y1?-straightLineLength:straightLineLength));
				Vector2 dstVector2(x2, y2);
				vector<Vector2> controlPoints;
				controlPoints.push_back(srcVector1);
				controlPoints.push_back(srcVector2);
				controlPoints.push_back(dstVector1);
				controlPoints.push_back(dstVector2);
				canvas.drawBezier(controlPoints, connection.red, connection.green, connection.blue, connection.alpha);
			}
			linesTexture->update();
			createConnectionsPasses--;
		}
	}

	//
	engine->display();
	engine->getGUI()->render();
}

void TextEditorTabView::initialize()
{
	try {
		textEditorTabController = new TextEditorTabController(this);
		textEditorTabController->initialize(editorView->getScreenController()->getScreenNode());
		screenNode->addContextMenuRequestListener(textEditorTabController);
		screenNode->addTooltipRequestListener(textEditorTabController);
	} catch (Exception& exception) {
		Console::println("TextEditorTabView::initialize(): An error occurred: " + string(exception.what()));
	}
	// TODO: load settings
}

void TextEditorTabView::dispose()
{
	required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController())->removeChangeListener(textNodeChangeListener);
	textEditorTabController->closeFindReplaceWindow();
	engine->dispose();
}

void TextEditorTabView::updateRendering() {
}

void TextEditorTabView::onMethodSelection(const string& methodName) {
	createMiniScriptNode(methodName, textEditorTabController->getAddNodeX(), textEditorTabController->getAddNodeY());
}

Engine* TextEditorTabView::getEngine() {
	return engine;
}

void TextEditorTabView::activate() {
	textEditorTabController->setOutlinerAddDropDownContent();
	textEditorTabController->setOutlinerContent();
	editorView->getScreenController()->restoreOutlinerState(outlinerState);
	editorView->getScreenController()->setDetailsContent(string());
}

void TextEditorTabView::deactivate() {
	editorView->getScreenController()->storeOutlinerState(outlinerState);
	textEditorTabController->closeFindReplaceWindow();
}

void TextEditorTabView::reloadOutliner() {
	textEditorTabController->setOutlinerContent();
	editorView->getScreenController()->setDetailsContent(string());
}

void TextEditorTabView::setVisualEditor() {
	textEditorTabController->closeFindReplaceWindow();
	auto editorNode = dynamic_cast<GUIElementNode*>(engine->getGUI()->getScreen(screenNode->getId())->getNodeById("editor"));
	if (editorNode != nullptr) editorNode->getActiveConditions().set("visualization");
	visualEditor = true;
}

void TextEditorTabView::setCodeEditor() {
	// dump nodes for now
	{
		auto i = 0;
		for (auto& nodeIt: nodes) {
			auto& node = nodeIt.second;
			string nodeType;
			switch (node.type) {
				case Node::NODETYPE_NONE: nodeType = "None"; break;
				case Node::NODETYPE_FLOW: nodeType = "Flow"; break;
				case Node::NODETYPE_ARGUMENT: nodeType = "Argument"; break;
			}
			Console::println("Node[" + to_string(i++) + "]: " + node.id + ": " + node.value + "(" + nodeType + ")");
		}
	}
	// dump connections for now
	{
		auto i = 0;
		for (auto& connection: connections) {
			Console::println("Connection[" + to_string(i++) + "]");
			string connectionType;
			switch (connection.type) {
				case Connection::CONNECTIONTYPE_NONE: connectionType = "None"; break;
				case Connection::CONNECTIONTYPE_FLOW: connectionType = "Flow"; break;
				case Connection::CONNECTIONTYPE_ARGUMENT: connectionType = "Argument"; break;
			}
			Console::println("\t" + connection.srcNodeId + " --> " + connection.dstNodeId + "(" + connectionType + ")");
		}
	}
	//
	string sourceCode;
	auto startNode = getNodeById(getStartNodeId());
	createSourceCodeFromNodes(sourceCode, startNode);
	Console::println(
		"Generated Source Code:\n\n" +
		sourceCode
	);
	auto editorNode = dynamic_cast<GUIElementNode*>(engine->getGUI()->getScreen(screenNode->getId())->getNodeById("editor"));
	if (editorNode != nullptr) editorNode->getActiveConditions().set("text");
	visualEditor = false;
}

void TextEditorTabView::createMiniScriptNode(const string& methodName, int x, int y) {
	auto flattenedId = to_string(nodeIdx++);
	auto method = textEditorTabController->getMiniScript()->getMethod(methodName);

	//
	nodes[flattenedId] = {
		.id = flattenedId,
		.type = Node::NODETYPE_FLOW,
		.value = methodName,
		.returnValueType = method->getReturnValueType(),
		.left = x,
		.top = y
	};
	//
	auto nodeName = methodName;
	auto nodeTypeColor = string("color.nodetype_method");
	auto methodOperatorMapIt = methodOperatorMap.find(nodeName);
	if (methodOperatorMapIt != methodOperatorMap.end()) {
		nodeName = methodOperatorMapIt->second;
		nodeTypeColor = "color.nodetype_math";
	}

	if (method == nullptr) {
		nodeTypeColor = "color.nodetype_function";
	} else {
		for (auto& flowControlNode: flowControlNodes) {
			if (nodeName == flowControlNode) {
				nodeTypeColor = "color.nodetype_flowcontrol";
				break;
			}
		}
		for (auto& mathNode: mathNodes) {
			if (nodeName == mathNode || StringTools::startsWith(nodeName, mathNode + ".")) {
				nodeTypeColor = "color.nodetype_math";
				break;
			}
		}
	}
	//
	{
		string xml = "<template src='resources/engine/gui/template_visualcode_node.xml' id='" + flattenedId + "' left='" + to_string(x) + "' top='" + to_string(y) + "' node-name='" + GUIParser::escapeQuotes(nodeName + "(" + flattenedId + ")") + "' node-type-color='{$" + GUIParser::escapeQuotes(nodeTypeColor) + "}' />";
		try {
			GUIParser::parse(visualisationNode, xml);
		} catch (Exception& exception) {
			Console::println("TextEditorTabView::createMiniScriptNodes(): method/function: " + string(exception.what()));
		}
	}
	//
	auto nodeInputContainer = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById(flattenedId + "_input_container"));
	auto nodeOutputContainer = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById(flattenedId + "_output_container"));
	// pin input aka flow input
	{
		string xml;
		//
		xml+=
			string() +
			"<template " +
			"	id='" + flattenedId + "_fi' " +
			"	src='resources/engine/gui/template_visualcode_input.xml' " +
			"	pin_type_connected='resources/engine/images/visualcode_flow_connected.png' " +
			"	pin_type_unconnected='resources/engine/images/visualcode_flow_unconnected.png' " +
			"/>";
		//
		try {
			GUIParser::parse(nodeInputContainer, xml);
			// update to be connected
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(flattenedId + "_fi_pin_type_panel"))->getActiveConditions().add("connected");
		} catch (Exception& exception) {
			Console::println("TextEditorTabView::createMiniScriptNodes(): method/function: " + string(exception.what()));
		}
	}
	// inputs aka arguments
	{
		//
		auto argumentIdx = 0;
		if (method != nullptr) {
			auto& argumentTypes = method->getArgumentTypes();
			for (argumentIdx = 0; argumentIdx < argumentTypes.size(); argumentIdx++) {
				//
				auto isLiteral = true;
				auto literal = string("");
				auto argumentName = argumentTypes[argumentIdx].name;
				if (argumentName.empty() == false) argumentName[0] = Character::toUpperCase(argumentName[0]);
				//
				string xml =
					string() +
					"<template " +
					"	id='" + flattenedId + "_a" + to_string(argumentIdx) + "' " +
					"	src='resources/engine/gui/template_visualcode_input.xml' " +
					"	pin_type_connected='resources/engine/images/visualcode_value_connected.png' " +
					"	pin_type_unconnected='resources/engine/images/visualcode_value_unconnected.png' " +
					"	pin_color='{$" + GUIParser::escapeQuotes(getScriptVariableTypePinColor(argumentTypes[argumentIdx].type)) + "}' " +
					"	text='" + GUIParser::escapeQuotes(argumentName) + "' ";
				if (isLiteral == true) {
					xml+= "	input_text='" + GUIParser::escapeQuotes(literal) + "' ";
				}
				xml+= "/>";
				//
				try {
					GUIParser::parse(nodeInputContainer, xml);
					//
					if (isLiteral == true) {
						// update to be a literal
						required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(flattenedId + "_a" + to_string(argumentIdx) + "_input_type_panel"))->getActiveConditions().add("input");
					} else {
						// update to be connected
						required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(flattenedId + "_a" + to_string(argumentIdx) + "_pin_type_panel"))->getActiveConditions().add("connected");
					}

				} catch (Exception& exception) {
					Console::println("TextEditorTabView::createMiniScriptNodes(): method/function: " + string(exception.what()));
				}
			}
		}
	}
	// pin output aka flow output
	{
		string xml;
		//
		xml+=
			string() +
			"<template " +
			"	id='" + flattenedId + "_fo' " +
			"	src='resources/engine/gui/template_visualcode_output.xml' " +
			"	pin_type_connected='resources/engine/images/visualcode_flow_connected.png' " +
			"	pin_type_unconnected='resources/engine/images/visualcode_flow_unconnected.png' " +
			"/>";
		//
		try {
			GUIParser::parse(nodeOutputContainer, xml);
			// update to be connected
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(flattenedId + "_fo_pin_type_panel"))->getActiveConditions().add("connected");
		} catch (Exception& exception) {
			Console::println("TextEditorTabView::createMiniScriptNodes(): method/function: " + string(exception.what()));
		}
	}
	// return value
	if (method != nullptr && method->getReturnValueType() != MiniScript::ScriptVariableType::TYPE_NULL) {
		string xml;
		//
		xml+=
			string() +
			"<template " +
			"	id='" + flattenedId + "_r' " +
			"	src='resources/engine/gui/template_visualcode_output.xml' " +
			"	pin_type_connected='resources/engine/images/visualcode_value_connected.png' " +
			"	pin_type_unconnected='resources/engine/images/visualcode_value_unconnected.png' " +
			"	pin_color='{$" + GUIParser::escapeQuotes(getScriptVariableTypePinColor(method->getReturnValueType())) + "}' " +
			"	text='Return' " +
			"/>";

		//
		try {
			GUIParser::parse(nodeOutputContainer, xml);
			// update to be connected
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(flattenedId + "_r_pin_type_panel"))->getActiveConditions().add("connected");
		} catch (Exception& exception) {
			Console::println("TextEditorTabView::createMiniScriptNodes(): method/function: " + string(exception.what()));
		}
	} else
	// functions have a return value pin by default for now
	//	TODO: MiniScript user functions need also formal return values a) to find out if we have a return value at all and to know the type
	if (method == nullptr) {
		string xml;
		//
		xml+=
			string() +
			"<template " +
			"	id='" + flattenedId + "_r' " +
			"	src='resources/engine/gui/template_visualcode_output.xml' " +
			"	pin_type_connected='resources/engine/images/visualcode_value_connected.png' " +
			"	pin_type_unconnected='resources/engine/images/visualcode_value_unconnected.png' " +
			"	pin_color='{$color.pintype_undefined}' " +
			"	text='Return Value' " +
			"/>";

		//
		try {
			GUIParser::parse(nodeOutputContainer, xml);
			// update to be connected
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(flattenedId + "_r_pin_type_panel"))->getActiveConditions().add("connected");
		} catch (Exception& exception) {
			Console::println("TextEditorTabView::createMiniScriptNodes(): method/function: " + string(exception.what()));
		}
	}

	// Bug: Work around! Sometimes layouting is not issued! Need to check!
	screenNode->forceInvalidateLayout(screenNode);
}

void TextEditorTabView::addMiniScriptNodeDeltaX(unordered_map<string, string>& idMapping, const string& id, const MiniScript::ScriptSyntaxTreeNode& syntaxTreeNode, int deltaX) {
	auto node = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById(getMiniScriptNodeFlattenedId(idMapping, id)));
	node->getRequestsConstraints().left+= deltaX;
	for (auto argumentIdx = 0; argumentIdx < syntaxTreeNode.arguments.size(); argumentIdx++) {
		//
		auto isLiteral = syntaxTreeNode.arguments[argumentIdx].type == MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL;
		if (isLiteral == true) continue;

		addMiniScriptNodeDeltaX(idMapping, id + "." + to_string(argumentIdx), syntaxTreeNode.arguments[argumentIdx], deltaX);
	}
}

void TextEditorTabView::createMiniScriptScriptNode(unordered_map<string, string>& idMapping, const string& id, MiniScript::Script::ScriptType scriptType, const string& condition, const string& readableName, const MiniScript::ScriptSyntaxTreeNode* conditionSyntaxTreeNode, int x, int y, int& width, int& height) {
	// create input nodes
	auto yInitial = y;

	//
	if (conditionSyntaxTreeNode->type != MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_NONE) {
		y+= 200;
		{
			auto childWidth = 0;
			auto childHeight = 0;
			vector<string> leftNodeIds;
			createMiniScriptNodes(idMapping, id + ".c", 0, 1, conditionSyntaxTreeNode, Node::NODETYPE_ARGUMENT, x, y, childWidth, childHeight, leftNodeIds, 1);
			x+= childWidth;
			width+= childWidth;
			height+= childHeight;
		}

		//
		y = yInitial;
	}

	//
	auto flattenedId = getMiniScriptNodeFlattenedId(idMapping, id);

	//
	{
		//
		nodes[flattenedId] = {
			.id = flattenedId,
			.type = Node::NODETYPE_ARGUMENT,
			.value = conditionSyntaxTreeNode->value.getValueString(),
			.returnValueType = MiniScript::ScriptVariableType::TYPE_NULL,
			.left = x,
			.top = y
		};

		//
		auto nodeName = readableName;
		string nodeTypeColor = string("color.nodetype_condition");
		//
		{
			string xml = "<template src='resources/engine/gui/template_visualcode_node.xml' id='" + flattenedId + "' left='" + to_string(x) + "' top='" + to_string(y) + "' node-name='" + GUIParser::escapeQuotes(nodeName + "(" + flattenedId + ")") + "' node-type-color='{$" + GUIParser::escapeQuotes(nodeTypeColor) + "}' />";
			try {
				GUIParser::parse(visualisationNode, xml);
			} catch (Exception& exception) {
				Console::println("TextEditorTabView::createMiniScriptScriptNode(): method/function: " + string(exception.what()));
			}
		}
		//
		auto nodeInputContainer = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById(id + "_input_container"));
		// condition input
		{
			//
			auto isLiteral = conditionSyntaxTreeNode->type == MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_NONE;
			auto literal = isLiteral == true?condition:string();
			//
			string xml =
				string() +
				"<template " +
				"	id='" + flattenedId + "_c' " +
				"	src='resources/engine/gui/template_visualcode_input.xml' " +
				"	pin_type_connected='resources/engine/images/visualcode_value_connected.png' " +
				"	pin_type_unconnected='resources/engine/images/visualcode_value_unconnected.png' " +
				"	pin_color='{$" + GUIParser::escapeQuotes(getScriptVariableTypePinColor(MiniScript::ScriptVariableType::TYPE_BOOLEAN)) + "}' " +
				"	text='" + GUIParser::escapeQuotes("Cond") + "' ";
			if (isLiteral == true) {
				xml+= "	input_text='" + GUIParser::escapeQuotes(literal) + "' ";
			}
			xml+= "/>";
			//
			try {
				GUIParser::parse(nodeInputContainer, xml);
				//
				if (isLiteral == true) {
					// update to be a literal
					required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(flattenedId + "_c_input_type_panel"))->getActiveConditions().add("input");
				} else {
					// update to be connected
					required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(flattenedId + "_c_pin_type_panel"))->getActiveConditions().add("connected");
				}
			} catch (Exception& exception) {
				Console::println("TextEditorTabView::createMiniScriptScriptNode(): method/function: " + string(exception.what()));
			}
		}
	}

	// create connection to condition node return to node cond node
	if (conditionSyntaxTreeNode->type != MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_NONE) {
		//
		string argumentInputNodeId = flattenedId + "_c";
		string argumentOutputNodeId = getMiniScriptNodeFlattenedId(idMapping, id + ".c_r");
		auto argumentInputNode = dynamic_cast<GUINode*>(screenNode->getNodeById(argumentInputNodeId));
		auto argumentOutputNode = dynamic_cast<GUINode*>(screenNode->getNodeById(argumentOutputNodeId));
		if (argumentInputNode == nullptr) {
			Console::println("TextEditorTabView::createMiniScriptNodes(): missing argument input node: " + argumentInputNodeId);
		} else
		if (argumentOutputNode == nullptr) {
			Console::println("TextEditorTabView::createMiniScriptNodes(): missing argument output node: " + argumentOutputNodeId);
		} else {

			//
			auto pinColor = string("color.pintype_boolean");
			GUIColor color(GUIParser::getEngineThemeProperties()->get(pinColor, "#ffffff"));

			//
			auto& argumentInputNodeComputedConstraints = argumentInputNode->getComputedConstraints();
			auto& argumentOutputNodeComputedConstraints = argumentOutputNode->getComputedConstraints();
			connections.push_back(
				{
					.type = Connection::CONNECTIONTYPE_ARGUMENT,
					.srcNodeId = argumentInputNodeId,
					.dstNodeId = argumentOutputNodeId,
					.red = static_cast<uint8_t>(color.getRed() * 255.0f),
					.green = static_cast<uint8_t>(color.getGreen() * 255.0f),
					.blue = static_cast<uint8_t>(color.getBlue() * 255.0f),
					.alpha = static_cast<uint8_t>(color.getAlpha() * 255.0f),
					.x1 = argumentInputNodeComputedConstraints.left,
					.y1 = argumentInputNodeComputedConstraints.top + argumentInputNodeComputedConstraints.height / 2,
					.x2 = argumentOutputNodeComputedConstraints.left + argumentOutputNodeComputedConstraints.width,
					.y2 = argumentOutputNodeComputedConstraints.top + argumentOutputNodeComputedConstraints.height / 2,
				}
			);
		}
	}

	//
	width+= 400;
	height = Math::max(height, 200);
}

void TextEditorTabView::createMiniScriptNodes(unordered_map<string, string>& idMapping, const string& id, int syntaxTreeNodeIdx, int syntaxTreeNodeCount, const MiniScript::ScriptSyntaxTreeNode* syntaxTreeNode, Node::NodeType nodeType, int x, int y, int& width, int& height, vector<string>& createdNodeIds, int depth) {
	// create input nodes
	int childMaxWidth = 0;
	auto yInitial = y;

	//
	y+= 200;
	vector<string> leftNodeIds;
	for (auto argumentIdx = 0; argumentIdx < syntaxTreeNode->arguments.size(); argumentIdx++) {
		//
		auto isLiteral = syntaxTreeNode->arguments[argumentIdx].type == MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL;
		if (isLiteral == true) continue;
		//
		auto childWidth = 0;
		auto childHeight = 0;
		createMiniScriptNodes(idMapping, id + "." + to_string(argumentIdx), argumentIdx, syntaxTreeNode->arguments.size(), &syntaxTreeNode->arguments[argumentIdx], Node::NODETYPE_ARGUMENT, x, y, childWidth, childHeight, leftNodeIds, depth + 1);
		if (childWidth > childMaxWidth) childMaxWidth = childWidth;
		y+= childHeight;
		height+= childHeight;
	}

	//
	y = yInitial;
	x+= childMaxWidth;
	width+= childMaxWidth;

	//
	for (auto& nodeId: leftNodeIds) createdNodeIds.push_back(nodeId);

	//
	auto flattenedId = getMiniScriptNodeFlattenedId(idMapping, id);

	//
	switch (syntaxTreeNode->type) {
		case MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD:
		case MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:
			{
				//
				createdNodeIds.push_back(flattenedId);
				//
				nodes[flattenedId] = {
					.id = flattenedId,
					.type = nodeType,
					.value = syntaxTreeNode->value.getValueString(),
					.returnValueType = syntaxTreeNode->method != nullptr?syntaxTreeNode->method->getReturnValueType():MiniScript::ScriptVariableType::TYPE_NULL,
					.left = x,
					.top = y
				};
				//
				auto nodeName = syntaxTreeNode->value.getValueString();
				auto nodeTypeColor = string("color.nodetype_method");
				auto methodOperatorMapIt = methodOperatorMap.find(nodeName);
				if (methodOperatorMapIt != methodOperatorMap.end()) {
					nodeName = methodOperatorMapIt->second;
					nodeTypeColor = "color.nodetype_math";
				}

				if (syntaxTreeNode->method == nullptr) {
					nodeTypeColor = "color.nodetype_function";
				} else {
					for (auto& flowControlNode: flowControlNodes) {
						if (nodeName == flowControlNode) {
							nodeTypeColor = "color.nodetype_flowcontrol";
							break;
						}
					}
					for (auto& mathNode: mathNodes) {
						if (nodeName == mathNode || StringTools::startsWith(nodeName, mathNode + ".")) {
							nodeTypeColor = "color.nodetype_math";
							break;
						}
					}
				}
				//
				{
					string xml = "<template src='resources/engine/gui/template_visualcode_node.xml' id='" + flattenedId + "' left='" + to_string(x) + "' top='" + to_string(y) + "' node-name='" + GUIParser::escapeQuotes(nodeName + "(" + flattenedId + ")") + "' node-type-color='{$" + GUIParser::escapeQuotes(nodeTypeColor) + "}' />";
					try {
						GUIParser::parse(visualisationNode, xml);
					} catch (Exception& exception) {
						Console::println("TextEditorTabView::createMiniScriptNodes(): method/function: " + string(exception.what()));
					}
				}
				//
				auto nodeInputContainer = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById(flattenedId + "_input_container"));
				auto nodeOutputContainer = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById(flattenedId + "_output_container"));
				// pin input aka flow input
				{
					string xml;
					//
					xml+=
						string() +
						"<template " +
						"	id='" + flattenedId + "_fi' " +
						"	src='resources/engine/gui/template_visualcode_input.xml' " +
						"	pin_type_connected='resources/engine/images/visualcode_flow_connected.png' " +
						"	pin_type_unconnected='resources/engine/images/visualcode_flow_unconnected.png' " +
						"/>";
					//
					try {
						GUIParser::parse(nodeInputContainer, xml);
						// update to be connected
						required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(flattenedId + "_fi_pin_type_panel"))->getActiveConditions().add("connected");
					} catch (Exception& exception) {
						Console::println("TextEditorTabView::createMiniScriptNodes(): method/function: " + string(exception.what()));
					}
				}
				// inputs aka arguments
				{
					//
					auto argumentIdx = 0;
					if (syntaxTreeNode->method != nullptr) {
						auto& argumentTypes = syntaxTreeNode->method->getArgumentTypes();
						for (argumentIdx = 0; argumentIdx < argumentTypes.size(); argumentIdx++) {
							//
							auto isLiteral = argumentIdx < syntaxTreeNode->arguments.size()?syntaxTreeNode->arguments[argumentIdx].type == MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL:false;
							auto literal = isLiteral == true?syntaxTreeNode->arguments[argumentIdx].value.getValueString():string();
							auto argumentName = argumentTypes[argumentIdx].name;
							if (argumentName.empty() == false) argumentName[0] = Character::toUpperCase(argumentName[0]);
							//
							string xml =
								string() +
								"<template " +
								"	id='" + flattenedId + "_a" + to_string(argumentIdx) + "' " +
								"	src='resources/engine/gui/template_visualcode_input.xml' " +
								"	pin_type_connected='resources/engine/images/visualcode_value_connected.png' " +
								"	pin_type_unconnected='resources/engine/images/visualcode_value_unconnected.png' " +
								"	pin_color='{$" + GUIParser::escapeQuotes(getScriptVariableTypePinColor(argumentTypes[argumentIdx].type)) + "}' " +
								"	text='" + GUIParser::escapeQuotes(argumentName) + "' ";
							if (isLiteral == true) {
								xml+= "	input_text='" + GUIParser::escapeQuotes(literal) + "' ";
							}
							xml+= "/>";
							//
							try {
								GUIParser::parse(nodeInputContainer, xml);
								//
								if (isLiteral == true) {
									// update to be a literal
									required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(flattenedId + "_a" + to_string(argumentIdx) + "_input_type_panel"))->getActiveConditions().add("input");
								} else {
									// update to be connected
									required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(flattenedId + "_a" + to_string(argumentIdx) + "_pin_type_panel"))->getActiveConditions().add("connected");
								}

							} catch (Exception& exception) {
								Console::println("TextEditorTabView::createMiniScriptNodes(): method/function: " + string(exception.what()));
							}
						}
					}
					for (; argumentIdx < syntaxTreeNode->arguments.size(); argumentIdx++) {
						//
						auto isLiteral = syntaxTreeNode->arguments[argumentIdx].type == MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL;
						auto literal = isLiteral == true?syntaxTreeNode->arguments[argumentIdx].value.getValueString():string();
						//
						string xml =
							string() +
							"<template " +
							"	id='" + flattenedId + "_a" + to_string(argumentIdx) + "' " +
							"	src='resources/engine/gui/template_visualcode_input.xml' " +
							"	pin_type_connected='resources/engine/images/visualcode_value_connected.png' " +
							"	pin_type_unconnected='resources/engine/images/visualcode_value_unconnected.png' " +
							"	pin_color='{$color.pintype_undefined}' " +
							"	text='Arg " + to_string(argumentIdx) + "' ";
						if (isLiteral == true) {
							xml+= "	input_text='" + GUIParser::escapeQuotes(literal) + "' ";
						}
						xml+= "/>";
						//
						try {
							GUIParser::parse(nodeInputContainer, xml);
							//
							if (isLiteral == true) {
								// update to be a literal
								required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(flattenedId + "_a" + to_string(argumentIdx) + "_input_type_panel"))->getActiveConditions().add("input");
							} else {
								// update to be connected
								required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(flattenedId + "_a" + to_string(argumentIdx) + "_pin_type_panel"))->getActiveConditions().add("connected");
							}
						} catch (Exception& exception) {
							Console::println("TextEditorTabView::createMiniScriptNodes(): method/function: " + string(exception.what()));
						}
					}
				}
				// pin output aka flow output
				if (depth == 0) {
					string xml;
					//
					xml+=
						string() +
						"<template " +
						"	id='" + flattenedId + "_fo' " +
						"	src='resources/engine/gui/template_visualcode_output.xml' " +
						"	pin_type_connected='resources/engine/images/visualcode_flow_connected.png' " +
						"	pin_type_unconnected='resources/engine/images/visualcode_flow_unconnected.png' " +
						"/>";
					//
					try {
						GUIParser::parse(nodeOutputContainer, xml);
						// update to be connected
						required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(flattenedId + "_fo_pin_type_panel"))->getActiveConditions().add("connected");
					} catch (Exception& exception) {
						Console::println("TextEditorTabView::createMiniScriptNodes(): method/function: " + string(exception.what()));
					}
				}
				// return value
				if (syntaxTreeNode->method != nullptr && syntaxTreeNode->method->getReturnValueType() != MiniScript::ScriptVariableType::TYPE_NULL) {
					string xml;
					//
					xml+=
						string() +
						"<template " +
						"	id='" + flattenedId + "_r' " +
						"	src='resources/engine/gui/template_visualcode_output.xml' " +
						"	pin_type_connected='resources/engine/images/visualcode_value_connected.png' " +
						"	pin_type_unconnected='resources/engine/images/visualcode_value_unconnected.png' " +
						"	pin_color='{$" + GUIParser::escapeQuotes(getScriptVariableTypePinColor(syntaxTreeNode->method->getReturnValueType())) + "}' " +
						"	text='Return' " +
						"/>";

					//
					try {
						GUIParser::parse(nodeOutputContainer, xml);
						// update to be connected
						required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(flattenedId + "_r_pin_type_panel"))->getActiveConditions().add("connected");
					} catch (Exception& exception) {
						Console::println("TextEditorTabView::createMiniScriptNodes(): method/function: " + string(exception.what()));
					}
				} else
				// functions have a return value pin by default for now
				//	TODO: MiniScript user functions need also formal return values a) to find out if we have a return value at all and to know the type
				if (syntaxTreeNode->method == nullptr) {
					string xml;
					//
					xml+=
						string() +
						"<template " +
						"	id='" + flattenedId + "_r' " +
						"	src='resources/engine/gui/template_visualcode_output.xml' " +
						"	pin_type_connected='resources/engine/images/visualcode_value_connected.png' " +
						"	pin_type_unconnected='resources/engine/images/visualcode_value_unconnected.png' " +
						"	pin_color='{$color.pintype_undefined}' " +
						"	text='Return Value' " +
						"/>";

					//
					try {
						GUIParser::parse(nodeOutputContainer, xml);
						// update to be connected
						required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(flattenedId + "_r_pin_type_panel"))->getActiveConditions().add("connected");
					} catch (Exception& exception) {
						Console::println("TextEditorTabView::createMiniScriptNodes(): method/function: " + string(exception.what()));
					}
				}
				break;
			}
		case MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL:
			break;
	}

	//
	width+= 400; //node->getContentWidth();
	height+= 200; //node->getContentHeight();

	// post layout of input nodes, move first level child argument nodes from from left to right according to the closest one
	auto rootDistanceMax = Integer::MAX_VALUE;
	auto nextLevelXBestFit = -1;
	for (auto argumentIdx = 0; argumentIdx < syntaxTreeNode->arguments.size(); argumentIdx++) {
		//
		auto isLiteral = syntaxTreeNode->arguments[argumentIdx].type == MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL;
		if (isLiteral == true) continue;
		//
		auto nextLevelNode = required_dynamic_cast<GUINode*>(screenNode->getNodeById(getMiniScriptNodeFlattenedId(idMapping, id + "." + to_string(argumentIdx))));
		auto nodeXPosition = nextLevelNode->getRequestsConstraints().left;
		auto rootDistance = Math::abs(x - nodeXPosition);
		if (rootDistance < rootDistanceMax) {
			rootDistanceMax = rootDistance;
			nextLevelXBestFit = nodeXPosition;
		}
	}
	for (auto argumentIdx = 0; argumentIdx < syntaxTreeNode->arguments.size(); argumentIdx++) {
		//
		auto isLiteral = syntaxTreeNode->arguments[argumentIdx].type == MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL;
		if (isLiteral == true) continue;
		//
		auto nextLevelNode = required_dynamic_cast<GUINode*>(screenNode->getNodeById(getMiniScriptNodeFlattenedId(idMapping, id + "." + to_string(argumentIdx))));
		auto nodeXPosition = nextLevelNode->getRequestsConstraints().left;
		auto deltaX = nextLevelXBestFit - nodeXPosition;
		if (deltaX == 0) continue;
		addMiniScriptNodeDeltaX(idMapping, id + "." + to_string(argumentIdx), syntaxTreeNode->arguments[argumentIdx], deltaX);
	}

	// create connections to input nodes
	for (auto argumentIdx = 0; argumentIdx < syntaxTreeNode->arguments.size(); argumentIdx++) {
		//
		auto isLiteral = syntaxTreeNode->arguments[argumentIdx].type == MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL;
		if (isLiteral == true) continue;
		//
		string argumentInputNodeId = flattenedId + "_a" + to_string(argumentIdx);
		string argumentOutputNodeId = getMiniScriptNodeFlattenedId(idMapping, id + "." + to_string(argumentIdx)) + "_r";
		auto argumentInputNode = dynamic_cast<GUINode*>(screenNode->getNodeById(argumentInputNodeId));
		auto argumentOutputNode = dynamic_cast<GUINode*>(screenNode->getNodeById(argumentOutputNodeId));
		if (argumentInputNode == nullptr) {
			Console::println("TextEditorTabView::createMiniScriptNodes(): missing argument input node: " + argumentInputNodeId);
			continue;
		}
		if (argumentOutputNode == nullptr) {
			Console::println("TextEditorTabView::createMiniScriptNodes(): missing argument output node: " + argumentOutputNodeId);
			continue;
		}

		//
		auto pinColor = string("color.pintype_undefined");
		if (syntaxTreeNode->method != nullptr) {
			auto& argumentTypes = syntaxTreeNode->method->getArgumentTypes();
			// first guess from argument type
			if (argumentIdx < argumentTypes.size()) {
				pinColor = getScriptVariableTypePinColor(argumentTypes[argumentIdx].type);
			}
			// no color?, try return value
			if (pinColor == "color.pintype_undefined") {
				auto nodeIt = nodes.find(flattenedId + "." + to_string(argumentIdx));
				if (nodeIt != nodes.end()) {
					auto& node = nodeIt->second;
					if (node.returnValueType != MiniScript::ScriptVariableType::TYPE_NULL) {
						pinColor = getScriptVariableTypePinColor(node.returnValueType);
					}
				}
			}
		}
		GUIColor color(GUIParser::getEngineThemeProperties()->get(pinColor, "#ffffff"));

		//
		auto& argumentInputNodeComputedConstraints = argumentInputNode->getComputedConstraints();
		auto& argumentOutputNodeComputedConstraints = argumentOutputNode->getComputedConstraints();
		connections.push_back(
			{
				.type = Connection::CONNECTIONTYPE_ARGUMENT,
				.srcNodeId = argumentInputNodeId,
				.dstNodeId = argumentOutputNodeId,
				.red = static_cast<uint8_t>(color.getRed() * 255.0f),
				.green = static_cast<uint8_t>(color.getGreen() * 255.0f),
				.blue = static_cast<uint8_t>(color.getBlue() * 255.0f),
				.alpha = static_cast<uint8_t>(color.getAlpha() * 255.0f),
				.x1 = argumentInputNodeComputedConstraints.left,
				.y1 = argumentInputNodeComputedConstraints.top + argumentInputNodeComputedConstraints.height / 2,
				.x2 = argumentOutputNodeComputedConstraints.left + argumentOutputNodeComputedConstraints.width,
				.y2 = argumentOutputNodeComputedConstraints.top + argumentOutputNodeComputedConstraints.height / 2,
			}
		);
	}
}

void TextEditorTabView::createMiniScriptBranchNodes(unordered_map<string, string>& idMapping, const string& id, int syntaxTreeNodeIdx, int syntaxTreeNodeCount, const MiniScript::ScriptSyntaxTreeNode* syntaxTreeNode, Node::NodeType nodeType, const vector<MiniScriptBranch>& branches, int x, int y, int& width, int& height, vector<string>& createdNodeIds, int depth) {
	//
	auto xInitial = x;
	auto yInitial = y;

	//
	y+= 200;

	//
	vector<string> leftNodeIds;
	auto childMaxWidth = 0;
	for (auto branchIdx = 0; branchIdx < branches.size(); branchIdx++) {
		// note: else has no condition
		if (branches[branchIdx].conditionSyntaxTree == nullptr) break;
		//
		if (branches[branchIdx].conditionSyntaxTree->type == MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL) continue;

		//
		auto childWidth = 0;
		auto childHeight = 0;
		createMiniScriptNodes(idMapping, id + "." + to_string(branchIdx), branchIdx, branches.size(), branches[branchIdx].conditionSyntaxTree, Node::NODETYPE_ARGUMENT, x, y, childWidth, childHeight, leftNodeIds, depth + 1);
		if (childWidth > childMaxWidth) childMaxWidth = childWidth;
		y+= childHeight;
		height+= childHeight;
	}
	//
	x+= childMaxWidth;
	width+= childMaxWidth;
	y = yInitial;

	//
	for (auto& nodeId: leftNodeIds) createdNodeIds.push_back(nodeId);
	//
	auto flattenedId = getMiniScriptNodeFlattenedId(idMapping, id);

	//
	{
		//
		createdNodeIds.push_back(flattenedId);
		//
		nodes[flattenedId] = {
			.id = flattenedId,
			.type = nodeType,
			.value = syntaxTreeNode->value.getValueString(),
			.returnValueType = MiniScript::ScriptVariableType::TYPE_NULL,
			.left = x,
			.top = y
		};
		//
		string nodeName = syntaxTreeNode->value.getValueString();
		string nodeTypeColor = string("color.nodetype_flowcontrol");
		//
		{
			string xml = "<template src='resources/engine/gui/template_visualcode_node.xml' id='" + flattenedId + "' left='" + to_string(x) + "' top='" + to_string(y) + "' node-name='" + GUIParser::escapeQuotes(nodeName + "(" + flattenedId + ")") + "' node-type-color='{$" + GUIParser::escapeQuotes(nodeTypeColor) + "}' />";
			try {
				GUIParser::parse(visualisationNode, xml);
			} catch (Exception& exception) {
				Console::println("TextEditorTabView::createMiniScriptIfBranchNodes(): method/function: " + string(exception.what()));
			}
		}
		//
		auto nodeInputContainer = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById(flattenedId + "_input_container"));
		auto nodeOutputContainer = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById(flattenedId + "_output_container"));
		// pin input aka flow input
		{
			string xml;
			//
			xml+=
				string() +
				"<template " +
				"	id='" + flattenedId + "_fi' " +
				"	src='resources/engine/gui/template_visualcode_input.xml' " +
				"	pin_type_connected='resources/engine/images/visualcode_flow_connected.png' " +
				"	pin_type_unconnected='resources/engine/images/visualcode_flow_unconnected.png' " +
				"/>";
			//
			try {
				GUIParser::parse(nodeInputContainer, xml);
				// update to be connected
				required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(flattenedId + "_fi_pin_type_panel"))->getActiveConditions().add("connected");
			} catch (Exception& exception) {
				Console::println("TextEditorTabView::createMiniScriptIfBranchNodes(): method/function: " + string(exception.what()));
			}
		}
		// pin output aka flow output
		{
			string xml;
			//
			xml+=
				string() +
				"<template " +
				"	id='" + flattenedId + "_fo' " +
				"	src='resources/engine/gui/template_visualcode_output.xml' " +
				"	pin_type_connected='resources/engine/images/visualcode_flow_connected.png' " +
				"	pin_type_unconnected='resources/engine/images/visualcode_flow_unconnected.png' " +
				"/>";
			//
			try {
				GUIParser::parse(nodeOutputContainer, xml);
				// update to be connected
				required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(flattenedId + "_fo_pin_type_panel"))->getActiveConditions().add("connected");
			} catch (Exception& exception) {
				Console::println("TextEditorTabView::createMiniScriptIfBranchNodes(): method/function: " + string(exception.what()));
			}
		}
		// inputs aka arguments
		for (auto branchIdx = 0; branchIdx < branches.size(); branchIdx++) {
			// condition inputs
			//	note: else has no condition syntax tree
			if (branches[branchIdx].conditionSyntaxTree != nullptr) {
				//
				auto isLiteral = branches[branchIdx].conditionSyntaxTree->type == MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL;
				auto literal = isLiteral == true?branches[branchIdx].conditionSyntaxTree->value.getValueString():string();
				//
				string xml =
					string() +
					"<template " +
					"	id='" + flattenedId + "_c" + to_string(branchIdx) + "' " +
					"	src='resources/engine/gui/template_visualcode_input.xml' " +
					"	pin_type_connected='resources/engine/images/visualcode_value_connected.png' " +
					"	pin_type_unconnected='resources/engine/images/visualcode_value_unconnected.png' " +
					"	pin_color='{$" + GUIParser::escapeQuotes(getScriptVariableTypePinColor(nodeName == "forTime"?MiniScript::ScriptVariableType::TYPE_INTEGER:MiniScript::ScriptVariableType::TYPE_BOOLEAN)) + "}' " +
					"	text='" + GUIParser::escapeQuotes(nodeName == "forTime"?"time":"Cond " + to_string(branchIdx)) + "' ";
				if (isLiteral == true) {
					xml+= "	input_text='" + GUIParser::escapeQuotes(literal) + "' ";
				}
				xml+= "/>";
				//
				try {
					GUIParser::parse(nodeInputContainer, xml);
					//
					if (isLiteral == true) {
						// update to be a literal
						required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(flattenedId + "_c" + to_string(branchIdx) + "_input_type_panel"))->getActiveConditions().add("input");
					} else {
						// update to be connected
						required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(flattenedId + "_c" + to_string(branchIdx) + "_pin_type_panel"))->getActiveConditions().add("connected");
					}
				} catch (Exception& exception) {
					Console::println("TextEditorTabView::createMiniScriptIfBranchNodes(): method/function: " + string(exception.what()));
				}
			}
			// flow outputs
			{
				string xml;
				//
				xml+=
					string() +
					"<template " +
					"	id='" + flattenedId + "_b" + to_string(branchIdx) + "' " +
					"	src='resources/engine/gui/template_visualcode_output.xml' " +
					"	pin_type_connected='resources/engine/images/visualcode_flow_connected.png' " +
					"	pin_type_unconnected='resources/engine/images/visualcode_flow_unconnected.png' " +
					"	text='Flow " + to_string(branchIdx) + "' " +
					"/>";
				//
				try {
					GUIParser::parse(nodeOutputContainer, xml);
					// update to be connected
					required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(flattenedId + "_b" + to_string(branchIdx) + "_pin_type_panel"))->getActiveConditions().add("connected");
				} catch (Exception& exception) {
					Console::println("TextEditorTabView::createMiniScriptIfBranchNodes(): method/function: " + string(exception.what()));
				}
			}
		}
	}

	//
	width+= 400; //node->getContentWidth();
	height+= 200; //node->getContentHeight();

	// post layout of conditions, move first level child argument nodes from from left to right according to the closest one
	auto rootDistanceMax = Integer::MAX_VALUE;
	auto nextLevelXBestFit = -1;
	for (auto branchIdx = 0; branchIdx < branches.size(); branchIdx++) {
		// note: else has no condition
		if (branches[branchIdx].conditionSyntaxTree == nullptr) break;
		//
		if (branches[branchIdx].conditionSyntaxTree->type == MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL) continue;
		//
		auto nextLevelNode = required_dynamic_cast<GUINode*>(screenNode->getNodeById(getMiniScriptNodeFlattenedId(idMapping, id + "." + to_string(branchIdx))));
		auto nodeXPosition = nextLevelNode->getRequestsConstraints().left;
		auto rootDistance = Math::abs(x - nodeXPosition);
		if (rootDistance < rootDistanceMax) {
			rootDistanceMax = rootDistance;
			nextLevelXBestFit = nodeXPosition;
		}
	}
	for (auto branchIdx = 0; branchIdx < branches.size(); branchIdx++) {
		// note: else has no condition
		if (branches[branchIdx].conditionSyntaxTree == nullptr) break;
		//
		if (branches[branchIdx].conditionSyntaxTree->type == MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL) continue;
		//
		auto nextLevelNode = required_dynamic_cast<GUINode*>(screenNode->getNodeById(getMiniScriptNodeFlattenedId(idMapping, id + "." + to_string(branchIdx))));
		auto nodeXPosition = nextLevelNode->getRequestsConstraints().left;
		auto deltaX = nextLevelXBestFit - nodeXPosition;
		if (deltaX == 0) continue;
		addMiniScriptNodeDeltaX(idMapping, id + "." + to_string(branchIdx), *branches[branchIdx].conditionSyntaxTree, deltaX);
	}

	// create condition connections
	for (auto branchIdx = 0; branchIdx < branches.size(); branchIdx++) {
		//
		if (branches[branchIdx].conditionSyntaxTree == nullptr ||
			(branches[branchIdx].conditionSyntaxTree != nullptr && branches[branchIdx].conditionSyntaxTree->type == MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL)) continue;
		//
		string conditionInputNodeId = flattenedId + "_c" + to_string(branchIdx);
		string conditionOutputNodeId = getMiniScriptNodeFlattenedId(idMapping, id + "." + to_string(branchIdx));
		auto conditionInputNode = dynamic_cast<GUINode*>(screenNode->getNodeById(conditionInputNodeId));
		auto conditionOutputNode = dynamic_cast<GUINode*>(screenNode->getNodeById(conditionOutputNodeId));
		if (conditionInputNode == nullptr) {
			Console::println("TextEditorTabView::createMiniScriptIfBranchNodes(): missing condition input node: " + conditionInputNodeId);
			continue;
		}
		if (conditionOutputNode == nullptr) {
			Console::println("TextEditorTabView::createMiniScriptIfBranchNodes(): missing condition output node: " + conditionOutputNodeId);
			continue;
		}

		//
		auto pinColor = string("color.pintype_boolean");
		GUIColor color(GUIParser::getEngineThemeProperties()->get(pinColor, "#ffffff"));

		//
		auto& conditionInputNodeComputedConstraints = conditionInputNode->getComputedConstraints();
		auto& conditionOutputNodeComputedConstraints = conditionOutputNode->getComputedConstraints();
		connections.push_back(
			{
				.type = Connection::CONNECTIONTYPE_ARGUMENT,
				.srcNodeId = conditionInputNodeId,
				.dstNodeId = conditionOutputNodeId,
				.red = static_cast<uint8_t>(color.getRed() * 255.0f),
				.green = static_cast<uint8_t>(color.getGreen() * 255.0f),
				.blue = static_cast<uint8_t>(color.getBlue() * 255.0f),
				.alpha = static_cast<uint8_t>(color.getAlpha() * 255.0f),
				.x1 = conditionInputNodeComputedConstraints.left,
				.y1 = conditionInputNodeComputedConstraints.top + conditionInputNodeComputedConstraints.height / 2,
				.x2 = conditionOutputNodeComputedConstraints.left + conditionOutputNodeComputedConstraints.width,
				.y2 = conditionOutputNodeComputedConstraints.top + conditionOutputNodeComputedConstraints.height / 2,
			}
		);
	}

	// create branch flows
	vector<string> rightNodeIds;
	auto branchWidthMax = 0;
	y = yInitial;
	for (auto branchIdx = 0; branchIdx < branches.size(); branchIdx++) {
		// for each branch
		auto branchSyntaxTreeNodes = branches[branchIdx].syntaxTreeNodes;
		//
		GUINode* previousNodeFlowNode = dynamic_cast<GUINode*>(screenNode->getNodeById(flattenedId + "_b" + to_string(branchIdx)));
		//
		x = xInitial + width;
		auto branchHeightMax = 0;
		auto branchWidth = 0;
		auto branchNodesWidth = 0;
		auto branchNodesHeight = 0;
		for (auto i = 0; i < branchSyntaxTreeNodes.size(); i++) {
			auto branchSyntaxTreeNode = branchSyntaxTreeNodes[i];

			//
			auto branchNodeIdx = i;
			branchNodesWidth = 0;
			branchNodesHeight = 0;
			while (handleMiniScriptBranch(idMapping, id + ".b." + to_string(branchIdx) + ".", branchSyntaxTreeNodes, i, x, y, branchNodesWidth, branchNodesHeight, rightNodeIds) == true) {
				// advance x
				x+= branchNodesWidth + 100;
				// store max
				branchWidth += branchNodesWidth + 100;
				branchHeightMax = Math::max(branchHeightMax, branchNodesHeight);
				//
				auto nodeFlowInId = getMiniScriptNodeFlattenedId(idMapping, id + ".b." + to_string(branchIdx) + "." + to_string(branchNodeIdx)) + "_fi";
				auto nodeFlowOutId = getMiniScriptNodeFlattenedId(idMapping, id + ".b." + to_string(branchIdx) + "." + to_string(branchNodeIdx)) + "_fo";
				auto nodeFlowIn = dynamic_cast<GUINode*>(screenNode->getNodeById(nodeFlowInId));
				auto nodeFlowOut = dynamic_cast<GUINode*>(screenNode->getNodeById(nodeFlowOutId));
				if (previousNodeFlowNode != nullptr && nodeFlowIn != nullptr) {
					auto& previousNodeComputedConstraints = previousNodeFlowNode->getComputedConstraints();
					auto& nodeComputedConstraints = nodeFlowIn->getComputedConstraints();
					connections.push_back(
						{
							.type = Connection::CONNECTIONTYPE_FLOW,
							.srcNodeId = previousNodeFlowNode->getId(),
							.dstNodeId = nodeFlowInId,
							.red = 255,
							.green = 255,
							.blue = 255,
							.alpha = 255,
							.x1 = previousNodeComputedConstraints.left + previousNodeComputedConstraints.width,
							.y1 = previousNodeComputedConstraints.top + previousNodeComputedConstraints.height / 2,
							.x2 = nodeComputedConstraints.left,
							.y2 = nodeComputedConstraints.top + nodeComputedConstraints.height / 2,
						}
					);
				}
				//
				if (i >= branchSyntaxTreeNodes.size()) break;
				//
				previousNodeFlowNode = nodeFlowOut;
				//
				branchNodeIdx = i;
				branchNodesWidth = 0;
				branchNodesHeight = 0;
			}

			//
			if (i >= branchSyntaxTreeNodes.size()) break;
			branchSyntaxTreeNode = branchSyntaxTreeNodes[i];

			//
			branchNodesWidth = 0;
			branchNodesHeight = 0;
			createMiniScriptNodes(idMapping, id + ".b." + to_string(branchIdx) + "." + to_string(i), i + 1, branchSyntaxTreeNodes.size() + 1, branchSyntaxTreeNode, Node::NODETYPE_FLOW, x, y, branchNodesWidth, branchNodesHeight, rightNodeIds);

			// advance x
			x+= branchNodesWidth + 100;
			// store max
			branchWidth += branchNodesWidth + 100;
			branchHeightMax = Math::max(branchHeightMax, branchNodesHeight);

			// connections
			auto nodeFlowInId = getMiniScriptNodeFlattenedId(idMapping, id + ".b." + to_string(branchIdx) + "." + to_string(i)) + "_fi";
			auto nodeFlowOutId = getMiniScriptNodeFlattenedId(idMapping, id + ".b." + to_string(branchIdx) + "." + to_string(i)) + "_fo";
			auto nodeFlowIn = dynamic_cast<GUINode*>(screenNode->getNodeById(nodeFlowInId));
			auto nodeFlowOut = dynamic_cast<GUINode*>(screenNode->getNodeById(nodeFlowOutId));
			if (previousNodeFlowNode != nullptr && nodeFlowIn != nullptr) {
				auto& previousNodeComputedConstraints = previousNodeFlowNode->getComputedConstraints();
				auto& nodeComputedConstraints = nodeFlowIn->getComputedConstraints();
				connections.push_back(
					{
						.type = Connection::CONNECTIONTYPE_FLOW,
						.srcNodeId = previousNodeFlowNode->getId(),
						.dstNodeId = nodeFlowInId,
						.red = 255,
						.green = 255,
						.blue = 255,
						.alpha = 255,
						.x1 = previousNodeComputedConstraints.left + previousNodeComputedConstraints.width,
						.y1 = previousNodeComputedConstraints.top + previousNodeComputedConstraints.height / 2,
						.x2 = nodeComputedConstraints.left,
						.y2 = nodeComputedConstraints.top + nodeComputedConstraints.height / 2,
					}
				);
			}
			//
			previousNodeFlowNode = nodeFlowOut;
		}
		//
		if (branchSyntaxTreeNodes.empty() == false) branchWidth-= 100;
		branchWidthMax = Math::max(branchWidthMax, branchWidth);
		y+= branchHeightMax;
	}
	//
	width+= branchWidthMax;
	height = Math::max(height, y - yInitial);
	//
	for (auto& nodeId: rightNodeIds) createdNodeIds.push_back(nodeId);

	// determine bounding box left and right
	auto leftTop = Integer::MAX_VALUE;
	auto leftBottom = Integer::MIN_VALUE;
	for (auto& leftNodeId: leftNodeIds) {
		auto node = required_dynamic_cast<GUINode*>(screenNode->getNodeById(leftNodeId));
		auto nodeTop = node->getRequestsConstraints().top;
		auto nodeBottom = node->getRequestsConstraints().top + 200;
		leftTop = Math::min(leftTop, nodeTop);
		leftBottom = Math::max(leftBottom, nodeBottom);
	}

	//
	auto rightTop = Integer::MAX_VALUE;
	auto rightBottom = Integer::MIN_VALUE;
	for (auto& rightNodeId: rightNodeIds) {
		auto node = required_dynamic_cast<GUINode*>(screenNode->getNodeById(rightNodeId));
		auto nodeTop = node->getRequestsConstraints().top;
		auto nodeBottom = node->getRequestsConstraints().top + 200;
		rightTop = Math::min(rightTop, nodeTop);
		rightBottom = Math::max(rightBottom, nodeBottom);
	}

	//
	auto leftHeight = leftBottom - leftTop;
	auto rightHeight = rightBottom - rightTop;
	if (leftNodeIds.empty() == false && rightNodeIds.empty() == false) {
		if (leftHeight == rightHeight) {
			// no op
		} else
		if (leftHeight > rightHeight) {
			auto deltaY = (leftHeight - rightHeight) / 2;
			for (auto& rightNodeId: rightNodeIds) {
				auto node = required_dynamic_cast<GUINode*>(screenNode->getNodeById(rightNodeId));
				node->getRequestsConstraints().top+= deltaY;
			}
			{
				auto node = required_dynamic_cast<GUINode*>(screenNode->getNodeById(flattenedId));
				node->getRequestsConstraints().top = yInitial + (leftHeight - 200) / 2;
			}
		} else {
			auto deltaY = (rightHeight - leftHeight) / 2;
			for (auto& leftNodeId: leftNodeIds) {
				auto node = required_dynamic_cast<GUINode*>(screenNode->getNodeById(leftNodeId));
				node->getRequestsConstraints().top+= deltaY;
			}
			{
				auto node = required_dynamic_cast<GUINode*>(screenNode->getNodeById(flattenedId));
				node->getRequestsConstraints().top = yInitial + (rightHeight - 200) / 2;
			}
		}
	}
}


bool TextEditorTabView::handleMiniScriptBranch(unordered_map<string, string>& idMapping, const string& idPrefix, const vector<MiniScript::ScriptSyntaxTreeNode*>& syntaxTree, int& i, int x, int y, int& width, int& height, vector<string>& createdNodeIds) {
	//
	auto syntaxTreeNode = syntaxTree[i];
	auto syntaxTreeNodeIdx = i;
	// handle if
	if (syntaxTreeNode->type == MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD &&
		(syntaxTreeNode->value.getValueString() == "if" ||
		syntaxTreeNode->value.getValueString() == "forCondition" ||
		syntaxTreeNode->value.getValueString() == "forTime")) {
		// support if depth
		auto ifStatement = syntaxTreeNode->value.getValueString() == "if";
		auto stackDepth = 1;
		vector<MiniScriptBranch> branches;
		branches.push_back(
			{
				.name = syntaxTreeNode->value.getValueString(),
				.conditionSyntaxTree = syntaxTreeNode->arguments.empty() == false?&syntaxTreeNode->arguments[0]:nullptr,
				.syntaxTreeNodes = {}
			}
		);
		for (i++; i < syntaxTree.size(); i++) {
			auto branchSyntaxTreeNode = syntaxTree[i];
			if (branchSyntaxTreeNode->type == MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD &&
				(branchSyntaxTreeNode->value.getValueString() == "if" ||
				branchSyntaxTreeNode->value.getValueString() == "forCondition" ||
				branchSyntaxTreeNode->value.getValueString() == "forTime")) {
				stackDepth++;
				branches[branches.size() - 1].syntaxTreeNodes.push_back(branchSyntaxTreeNode);
			} else
			if (ifStatement == true && stackDepth == 1 && branchSyntaxTreeNode->type == MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD && branchSyntaxTreeNode->value.getValueString() == "elseif") {
				branches.push_back(
					{
						.name = branchSyntaxTreeNode->value.getValueString(),
						.conditionSyntaxTree = branchSyntaxTreeNode->arguments.empty() == false?&branchSyntaxTreeNode->arguments[0]:nullptr,
						.syntaxTreeNodes = {}
					}
				);
			} else
			if (ifStatement == true && stackDepth == 1 && branchSyntaxTreeNode->type == MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD && branchSyntaxTreeNode->value.getValueString() == "else") {
				branches.push_back(
					{
						.name = branchSyntaxTreeNode->value.getValueString(),
						.conditionSyntaxTree = nullptr,
						.syntaxTreeNodes = {}
					}
				);
			} else
			if (branchSyntaxTreeNode->type == MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD && branchSyntaxTreeNode->value.getValueString() == "end") {
				//
				stackDepth--;
				// done?
				if (stackDepth == 0) {
					//
					createMiniScriptBranchNodes(idMapping, idPrefix + to_string(syntaxTreeNodeIdx), syntaxTreeNodeIdx, syntaxTree.size(), syntaxTreeNode, Node::NODETYPE_FLOW, branches, x, y, width, height, createdNodeIds);
					//
					i++;
					//
					return true;
				} else {
					// a end that does not belong to our initial if, yarr
					branches[branches.size() - 1].syntaxTreeNodes.push_back(branchSyntaxTreeNode);
				}
			} else {
				branches[branches.size() - 1].syntaxTreeNodes.push_back(branchSyntaxTreeNode);
			}
		}
	}
	//
	return false;
}

void TextEditorTabView::updateMiniScriptSyntaxTree(int miniScriptScriptIdx) {
	visualisationNode->clearSubNodes();
	this->connections.clear();
	this->nodes.clear();
	this->miniScriptScriptIdx = miniScriptScriptIdx;
	//
	unordered_map<string, string> idMapping;
	// structure
	if (miniScriptScriptIdx == MINISCRIPT_SCRIPTIDX_STRUCTURE) {
		auto syntaxTrees = textEditorTabController->getMiniScriptSyntaxTrees();

		//
		auto width = 0;
		auto height = 0;
		auto y = 200;
		auto yMax = y;
		auto xMax = 200;
		for (auto i = 0; i < syntaxTrees.size(); i++) {
			//
			auto x = 200;
			width = 0;
			height = 0;
			createMiniScriptScriptNode(idMapping, to_string(i), syntaxTrees[i].type, syntaxTrees[i].condition, syntaxTrees[i].name, &syntaxTrees[i].conditionSyntaxTree, x, y, width, height);

			//
			y+= height + 100;
			yMax = Math::max(y + height, yMax);
			xMax = Math::max(x + width, xMax);
		}

		// TODO: with absolute align of nodes content width/height is not yet computed in UI
		visualisationNode->getComputedConstraints().width = xMax;
		visualisationNode->getComputedConstraints().height = yMax;
		visualisationNode->getRequestsConstraints().width = xMax;
		visualisationNode->getRequestsConstraints().height = yMax;
	} else {
		// script
		// 	copy syntax tree
		auto syntaxTree = textEditorTabController->getMiniScriptSyntaxTrees()[miniScriptScriptIdx].syntaxTree;
		// 	construct syntax tree as vector of pointers to the nodes
		vector<MiniScript::ScriptSyntaxTreeNode*> syntaxTreeNodes;
		for (auto& syntaxTreeNode: syntaxTree) syntaxTreeNodes.push_back(&syntaxTreeNode);
		// 	remove end node if we have any
		if (syntaxTreeNodes.empty() == false &&
			syntaxTreeNodes[syntaxTreeNodes.size() - 1]->type == MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD &&
			syntaxTreeNodes[syntaxTreeNodes.size() - 1]->value.getValueString() == "end") {
			syntaxTreeNodes.erase(syntaxTreeNodes.begin() + syntaxTreeNodes.size() - 1);
		}
		//
		auto width = 0;
		auto height = 0;
		auto x = 200;
		auto y = 200;
		auto yMax = y;
		vector<string> createdNodeIds;
		GUINode* previousNodeFlowNode = nullptr;
		for (auto i = 0; i < syntaxTreeNodes.size(); i++) {
			auto syntaxTreeNode = syntaxTreeNodes[i];

			//
			width = 0;
			height = 0;
			auto branchNodeIdx = i;
			while (handleMiniScriptBranch(idMapping, string(), syntaxTreeNodes, i, x, y, width, height, createdNodeIds) == true) {
				//
				x+= width + 100;
				yMax = Math::max(y + height, yMax);
				//
				auto nodeFlowInId = getMiniScriptNodeFlattenedId(idMapping, to_string(branchNodeIdx)) + "_fi";
				auto nodeFlowOutId = getMiniScriptNodeFlattenedId(idMapping, to_string(branchNodeIdx)) + "_fo";
				auto nodeFlowIn = dynamic_cast<GUINode*>(screenNode->getNodeById(nodeFlowInId));
				auto nodeFlowOut = dynamic_cast<GUINode*>(screenNode->getNodeById(nodeFlowOutId));
				if (previousNodeFlowNode != nullptr && nodeFlowIn != nullptr) {
					auto& previousNodeComputedConstraints = previousNodeFlowNode->getComputedConstraints();
					auto& nodeComputedConstraints = nodeFlowIn->getComputedConstraints();
					connections.push_back(
						{
							.type = Connection::CONNECTIONTYPE_FLOW,
							.srcNodeId = previousNodeFlowNode->getId(),
							.dstNodeId = nodeFlowInId,
							.red = 255,
							.green = 255,
							.blue = 255,
							.alpha = 255,
							.x1 = previousNodeComputedConstraints.left + previousNodeComputedConstraints.width,
							.y1 = previousNodeComputedConstraints.top + previousNodeComputedConstraints.height / 2,
							.x2 = nodeComputedConstraints.left,
							.y2 = nodeComputedConstraints.top + nodeComputedConstraints.height / 2,
						}
					);
				}
				//
				if (i >= syntaxTreeNodes.size()) break;
				//
				previousNodeFlowNode = nodeFlowOut;
				//
				branchNodeIdx = i;
				width = 0;
				height = 0;
			}

			//
			if (i >= syntaxTreeNodes.size()) break;
			syntaxTreeNode = syntaxTreeNodes[i];

			//
			width = 0;
			height = 0;
			createMiniScriptNodes(idMapping, to_string(i), i, syntaxTreeNodes.size(), syntaxTreeNode, Node::NODETYPE_FLOW, x, y, width, height, createdNodeIds);

			//
			x+= width + 100;
			yMax = Math::max(y + height, yMax);

			// connections
			auto nodeFlowInId = getMiniScriptNodeFlattenedId(idMapping, to_string(i)) + "_fi";
			auto nodeFlowOutId = getMiniScriptNodeFlattenedId(idMapping, to_string(i)) + "_fo";
			auto nodeFlowIn = dynamic_cast<GUINode*>(screenNode->getNodeById(nodeFlowInId));
			auto nodeFlowOut = dynamic_cast<GUINode*>(screenNode->getNodeById(nodeFlowOutId));
			if (previousNodeFlowNode != nullptr && nodeFlowIn != nullptr) {
				auto& previousNodeComputedConstraints = previousNodeFlowNode->getComputedConstraints();
				auto& nodeComputedConstraints = nodeFlowIn->getComputedConstraints();
				connections.push_back(
					{
						.type = Connection::CONNECTIONTYPE_FLOW,
						.srcNodeId = previousNodeFlowNode->getId(),
						.dstNodeId = nodeFlowInId,
						.red = 255,
						.green = 255,
						.blue = 255,
						.alpha = 255,
						.x1 = previousNodeComputedConstraints.left + previousNodeComputedConstraints.width,
						.y1 = previousNodeComputedConstraints.top + previousNodeComputedConstraints.height / 2,
						.x2 = nodeComputedConstraints.left,
						.y2 = nodeComputedConstraints.top + nodeComputedConstraints.height / 2,
					}
				);
			}
			//
			previousNodeFlowNode = nodeFlowOut;
		}

		// TODO: with absolute align of nodes content width/height is not yet computed in UI
		visualisationNode->getComputedConstraints().width = x;
		visualisationNode->getComputedConstraints().height = yMax;
		visualisationNode->getRequestsConstraints().width = x;
		visualisationNode->getRequestsConstraints().height = yMax;
	}

	// Bug: Work around! Sometimes layouting is not issued! Need to check!
	screenNode->forceInvalidateLayout(screenNode);

	//
	nodeIdx = idMapping.size();

	//
	createConnectionsPasses = 3;
}

void TextEditorTabView::createMiniScriptConnections() {
	for (auto& connection: connections) {
		auto srcNode = dynamic_cast<GUINode*>(screenNode->getNodeById(connection.srcNodeId));
		auto dstNode = dynamic_cast<GUINode*>(screenNode->getNodeById(connection.dstNodeId));
		if (srcNode == nullptr) {
			Console::println("TextEditorTabView::createMiniScriptConnections(): could not find src node with id: " + connection.srcNodeId);
			continue;
		} else
		if (dstNode == nullptr) {
			Console::println("TextEditorTabView::createMiniScriptConnections(): could not find dst node with id: " + connection.dstNodeId);
			continue;
		}
		auto& srcNodeComputedConstraints = srcNode->getComputedConstraints();
		auto& dstNodeComputedConstraints = dstNode->getComputedConstraints();
		switch (connection.type) {
			case Connection::CONNECTIONTYPE_FLOW:
				connection.x1 = srcNodeComputedConstraints.left + srcNodeComputedConstraints.width;
				connection.y1 = srcNodeComputedConstraints.top + srcNodeComputedConstraints.height / 2;
				connection.x2 = dstNodeComputedConstraints.left;
				connection.y2 = dstNodeComputedConstraints.top + dstNodeComputedConstraints.height / 2;
				break;
			case Connection::CONNECTIONTYPE_ARGUMENT:
				connection.x1 = srcNodeComputedConstraints.left;
				connection.y1 = srcNodeComputedConstraints.top + srcNodeComputedConstraints.height / 2;
				connection.x2 = dstNodeComputedConstraints.left + dstNodeComputedConstraints.width;
				connection.y2 = dstNodeComputedConstraints.top + dstNodeComputedConstraints.height / 2;
				break;
			default: break;
		}
	}
}

int TextEditorTabView::getTextIndex() {
	auto textNodeController = required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController());
	return textNodeController->getIndex();
}

bool TextEditorTabView::find(const string& findString, bool matchCase, bool wholeWord, bool selection, bool firstSearch, int& index) {
	cancelFind();
	return TextTools::find(textNode, findString, matchCase, wholeWord, selection, firstSearch, index);
}

int TextEditorTabView::count(const string& findString, bool matchCase, bool wholeWord, bool selection) {
	cancelFind();
	countEnabled = true;
	return TextTools::count(textNode, findString, matchCase, wholeWord, selection);
}

bool TextEditorTabView::replace(const string& findString, const string& replaceString, bool matchCase, bool wholeWord, bool selection, int& index) {
	cancelFind();
	auto success = TextTools::replace(textNode, findString, replaceString, matchCase, wholeWord, selection, index);
	TextFormatter::getInstance()->format(extension, textNode, 0, textNode->getText().size());
	return success;
}

bool TextEditorTabView::replaceAll(const string& findString, const string& replaceString, bool matchCase, bool wholeWord, bool selection) {
	auto success = TextTools::replaceAll(textNode, findString, replaceString, matchCase, wholeWord, selection);
	cancelFind();
	return success;
}

void TextEditorTabView::cancelFind() {
	TextFormatter::getInstance()->format(extension, textNode, 0, textNode->getText().size());
	countEnabled = false;
}

void TextEditorTabView::redo() {
	if (visualEditor == false) {
		required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController())->redo();
	}
}

void TextEditorTabView::undo() {
	if (visualEditor == false) {
		required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController())->undo();
	}
}

void TextEditorTabView::selectAll() {
	if (visualEditor == false) {
		required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController())->selectAll();
	}
}

void TextEditorTabView::cut() {
	if (visualEditor == false) {
		required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController())->cut();
	}
}

void TextEditorTabView::copy() {
	if (visualEditor == false) {
		required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController())->copy();
	}
}

void TextEditorTabView::paste() {
	if (visualEditor == false) {
		required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController())->paste();
	}
}

void TextEditorTabView::delete_() {
	if (visualEditor == false) {
		required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController())->delete_();
	}
}

void TextEditorTabView::createSourceCodeFromNodes(string& sourceCode, const Node* node, int depth) {
	while (node != nullptr) {
		createSourceCodeFromNode(sourceCode, node, depth);
		sourceCode+= "\n";
		auto nextNodeId = getNextNodeId(node->id);
		if (nextNodeId.empty() == true) break;
		node = getNodeById(nextNodeId);
	}
}

void TextEditorTabView::createSourceCodeFromNode(string& sourceCode, const Node* node, int depth) {
	//
	string spacePrefix;
	for (auto i = 0; i < depth; i++) spacePrefix+= "\t";
	if (node->value == "if") {
		//
		for (auto conditionIdx = 0; conditionIdx < 100; conditionIdx++) {
			auto branchNodeId = getConnectedBranchNodeId(node->id, conditionIdx);
			auto branchNode = getNodeById(branchNodeId);
			//
			auto conditionNodeId = getConnectedConditionNodeId(node->id, conditionIdx);
			auto conditionNode = getNodeById(conditionNodeId);
			if (conditionNode != nullptr) {
				sourceCode+= spacePrefix;
				if (conditionIdx == 0) {
					sourceCode+= "if ";
				} else {
					sourceCode+= "elseif ";
				}
				sourceCode+= "(";
				createSourceCodeFromNode(sourceCode, conditionNode, 0);
				sourceCode+= ")";
				sourceCode+= "\n";
			}
			if (branchNode != nullptr) {
				if (conditionNode == nullptr) {
					sourceCode+= spacePrefix;
					sourceCode+= "else";
					sourceCode+= "\n";
				}
				createSourceCodeFromNodes(sourceCode, branchNode, depth + 1);
				if (conditionNode == nullptr) {
					sourceCode+= spacePrefix;
					sourceCode+= "end";
					break;
				}
			}
			if (conditionNode == nullptr && branchNode == nullptr) {
				sourceCode+= spacePrefix;
				sourceCode+= "end";
				break;
			}
		}
	} else {
		sourceCode+= spacePrefix;
		sourceCode+= node->value + "(";
		// arguments
		string argumentsSourceCode;
		for (auto argumentIdx = 0; argumentIdx < 100; argumentIdx++) {
			auto argumentNodeId = getConnectedArgumentNodeId(node->id, argumentIdx);
			if (argumentNodeId.empty() == true) {
				// check for literal
				auto argumentNodeId = getArgumentNodeId(node->id, argumentIdx);
				auto literalInput = dynamic_cast<GUINode*>(screenNode->getNodeById(argumentNodeId + "_input"));
				if (literalInput != nullptr) {
					auto literalInputValue = literalInput->getController()->getValue().getString();
					if (argumentsSourceCode.empty() == false) argumentsSourceCode+= ", ";
					// implicitely literal
					//	TODO: first version, improve me
					MiniScript::ScriptVariable value;
					value.setImplicitTypedValueFromStringView(literalInputValue);
					if (value.getType() == MiniScript::TYPE_STRING) {
						argumentsSourceCode+= "\"" + StringTools::replace(literalInputValue, "\"", "\\\"") + "\"";
					} else {
						argumentsSourceCode+= literalInputValue;
					}
				}
			} else {
				// check for connected argument
				auto argumentNode = getNodeById(argumentNodeId);
				if (argumentNode == nullptr) continue;
				//
				if (argumentsSourceCode.empty() == false) argumentsSourceCode+= ", ";
				createSourceCodeFromNode(argumentsSourceCode, argumentNode, 0);
			}
		}
		sourceCode+= argumentsSourceCode + ")";
	}
}

void TextEditorTabView::deleteNode(const string& nodeId) {
	auto nodeIt = nodes.find(nodeId);
	if (nodeIt == nodes.end()) return;
	nodes.erase(nodeIt);
	screenNode->removeNodeById(nodeId, false);
	for (auto i = 0; i < connections.size(); i++) {
		auto& connection = connections[i];
		if (connection.srcNodeId == nodeId || StringTools::startsWith(connection.srcNodeId, nodeId + "_") == true ||
			connection.dstNodeId == nodeId || StringTools::startsWith(connection.dstNodeId, nodeId + "_") == true) {
			connections.erase(connections.begin() + i);
			i--;
		}
	}

	// Bug: Work around! Sometimes layouting is not issued! Need to check!
	screenNode->forceInvalidateLayout(screenNode);

	//
	createConnectionsPasses = 3;
}

void TextEditorTabView::setupContextMenu() {
	switch (textEditorTabController->getContextMenuType()) {
		case TextEditorTabController::CONTEXTMENUTYPE_NODE:
			{
				// clear
				popUps->getContextMenuScreenController()->clear();

				// delete
				class OnNodeDeleteAction: public virtual Action
				{
				public:
					void performAction() override {
						textEditorTabView->deleteNode(nodeId);
					}
					OnNodeDeleteAction(TextEditorTabView* textEditorTabView, const string& nodeId): textEditorTabView(textEditorTabView), nodeId(nodeId) {
					}
				private:
					TextEditorTabView* textEditorTabView;
					string nodeId;
				};
				popUps->getContextMenuScreenController()->addMenuItem("Delete Node", "contextmenu_delete", new OnNodeDeleteAction(this, textEditorTabController->getContextMenuNodeId()));

				//
				popUps->getContextMenuScreenController()->show(textEditorTabController->getContextMenuX(), textEditorTabController->getContextMenuY());

				//
				break;
			}
		case TextEditorTabController::CONTEXTMENUTYPE_CANVAS:
			{
				// clear
				popUps->getContextMenuScreenController()->clear();
				popUps->getContextMenuScreenController()->setMiniScriptMethodSelectionListener(this);
				popUps->getContextMenuScreenController()->setupVisualCodeAddNodeContextMenu();

				//
				popUps->getContextMenuScreenController()->show(textEditorTabController->getContextMenuX(), textEditorTabController->getContextMenuY());

				//
				break;
			}
		default:
			break;
	}

	//
	textEditorTabController->resetContextMenu();
}
