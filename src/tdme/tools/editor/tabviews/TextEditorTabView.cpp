#include <tdme/tools/editor/tabviews/TextEditorTabView.h>

#include <algorithm>
#include <cctype>
#include <memory>
#include <string>
#include <unordered_map>

#include <agui/agui.h>
#include <agui/gui/events/GUIMouseEvent.h>
#include <agui/gui/events/GUIMoveListener.h>
#include <agui/gui/nodes/GUIColor.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUIImageNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUIParentNode.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/nodes/GUIStyledTextNode.h>
#include <agui/gui/nodes/GUIStyledTextNodeController.h>
#include <agui/gui/GUI.h>
#include <agui/gui/GUIParser.h>

#include <tdme/tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/ColorTextureCanvas.h>
#include <tdme/engine/DynamicColorTexture.h>
#include <tdme/engine/Engine.h>
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
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/Properties.h>
#include <tdme/utilities/StringTools.h>

using std::make_unique;
using std::sort;
using std::string;
using std::unique_ptr;
using std::unordered_map;

using tdme::tools::editor::tabviews::TextEditorTabView;

using agui::gui::events::GUIMouseEvent;
using agui::gui::events::GUIMoveListener;
using agui::gui::nodes::GUIColor;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUIImageNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUIParentNode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::nodes::GUIStyledTextNode;
using agui::gui::GUI;
using agui::gui::GUIParser;

using tdme::engine::Color4;
using tdme::engine::ColorTextureCanvas;
using tdme::engine::DynamicColorTexture;
using tdme::engine::Engine;
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
using tdme::utilities::Exception;
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
	engine = unique_ptr<Engine>(Engine::createOffScreenInstance(512, 512, false, false, false));
	engine->setSceneColor(Color4(39.0f / 255.0f, 39.0f / 255.0f, 39.0f / 255.0f, 1.0f));
	engine->getGUI()->addScreen(screenNode->getId(), screenNode);
	engine->getGUI()->addRenderScreen(screenNode->getId());

	//
	visualCodingEnabled = extension == "tscript";
	if (visualCodingEnabled == true) {
		//
		visualisationNode = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("visualization_canvas"));
		//
		linesTexture = make_unique<DynamicColorTexture>(engine->getWidth(), engine->getHeight());
		linesTexture->initialize();
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("visualization_texture"))->setTexture(linesTexture.get()->toGUIRendererTexture());
		// add node move listener
		class NodeMoveListener: public GUIMoveListener {
		public:
			NodeMoveListener(TextEditorTabView* textEditorTabView): textEditorTabView(textEditorTabView) {
			}
			bool accept(GUINode* node) {
				if (node->getId().find("_") != string::npos) {
					textEditorTabView->createConnection(node->getId());
					return false;
				} else {
					return textEditorTabView->isCreatingConnection() == false;
				}
			}
			void onMove(GUINode* node) {
				auto visualisationNode = textEditorTabView->visualisationNode;
				const auto& nodeComputedConstraints = node->getComputedConstraints();
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
		//
		screenNode->addMoveListener((guiMoveListener = make_unique<NodeMoveListener>(this)).get());
		// enable code mode
		setCodeEditor();
	}

	// initial text format
	TextFormatter::getInstance()->format(extension, textNode);
	// load code completion
	codeCompletion = unique_ptr<const TextFormatter::CodeCompletion>(TextFormatter::getInstance()->loadCodeCompletion(extension));

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
		//
		required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController())->addChangeListener((textNodeChangeListener = make_unique<TextChangeListener>(this)).get());
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
				auto codeCompletion = textEditorTabView->codeCompletion.get();
				if (codeCompletion == nullptr) return;
				if (codeCompletion->delimiters.find(textEditorTabView->textNode->getText().getCharAt(idx)) != string::npos) {
					if (idx > 0) idx--;
				}
				auto previousDelimiterPos = textEditorTabView->textNode->getPreviousDelimiter(idx, codeCompletion->delimiters);
				string search = StringTools::substring(textEditorTabView->textNode->getText().getString(), previousDelimiterPos == 0?0:previousDelimiterPos + 1, idx);
				vector<CodeCompletionSymbol> codeCompletionSymbolCandidates;
				#define MAX_ENTRIES	40
				for (const auto& symbol: codeCompletion->symbols) {
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
							for (const auto& overload: symbol.overloadList) {
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
									for (const auto& parameter: overload.parameters) {
										if (parameters.empty() == false) parameters+= ", ";
										parameters+= parameter;
									}
									codeCompletionSymbolCandidates.push_back(
										{
											.type = CodeCompletionSymbol::TYPE_FUNCTION,
											.display = symbol.name + "(" + parameters + "): " + overload.returnValue,
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
				sort(
					codeCompletionSymbolCandidates.begin(),
					codeCompletionSymbolCandidates.begin() + (Math::min(codeCompletionSymbolCandidates.size(), MAX_ENTRIES)),
					[](const CodeCompletionSymbol& lhs, const CodeCompletionSymbol& rhs) {
						return lhs.display < rhs.display;
					}
				);
				//
				{
					auto i = 0;
					for (const auto& codeCompletionSymbolCandidate: codeCompletionSymbolCandidates) {
						// add light
						class OnCodeCompletionAction: public Action
						{
						public:
							OnCodeCompletionAction(TextEditorTabView* textEditorTabView, int idx, const CodeCompletionSymbol& symbol): textEditorTabView(textEditorTabView), idx(idx), symbol(symbol) {}
							void performAction() override {
								if (symbol.name.empty() == true) return;
								auto codeCompletion = textEditorTabView->codeCompletion.get();
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
									for (const auto& parameter: symbol.parameters) {
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
		//
		required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController())->addCodeCompletionListener((textNodeCodeCompletionListener = make_unique<TextCodeCompletionListener>(this)).get());
	}
}

TextEditorTabView::~TextEditorTabView() {
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
	if (isCreatingConnection() == true) {
		auto visualizationNode = required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("visualization"));
		auto scrollX = visualizationNode->getChildrenRenderOffsetX();
		auto scrollY = visualizationNode->getChildrenRenderOffsetY();
		for (auto& event: engine->getGUI()->getMouseEvents()) {
			if (event.getButton() != GUIMouseEvent::MOUSEEVENT_BUTTON_LEFT) continue;
			if (event.getType() == GUIMouseEvent::MOUSEEVENT_RELEASED) {
				//
				finishCreateConnection(event.getX(), event.getY());
				//
				event.setProcessed(true);
				//
				break;
			} else
			if (event.getType() == GUIMouseEvent::MOUSEEVENT_DRAGGED) {
				auto& connection = connections[createConnectionIdx];
				if (connection.srcNodeId.empty() == true) {
					connection.x1 = scrollX + event.getX();
					connection.y1 = scrollY + event.getY();
				} else
				if (connection.dstNodeId.empty() == true) {
					connection.x2 = scrollX + event.getX();
					connection.y2 = scrollY + event.getY();
				}
				//
				createConnectionsPasses = 3;
				//
				event.setProcessed(true);
			}
		}
	}
	//
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
			if (visualizationTextureNode != nullptr) visualizationTextureNode->setTexture(linesTexture.get()->toGUIRendererTexture());
			createConnectionsPasses = 3;
		}
		// we have a layouting issue here, we cant get dimensions of nodes right after adding them, so defer this for now
		if (createConnectionsPasses > 0) {
			auto visualizationScrollArea = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("visualization"));
			auto visualizationWidth = visualizationScrollArea->getComputedConstraints().width;
			auto visualizationHeight = visualizationScrollArea->getComputedConstraints().height;
			auto visualizationScrollX = static_cast<int>(scrollX);
			auto visualizationScrollY = static_cast<int>(scrollY);
			createMinitScriptConnections();
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
			for (const auto& connection: connections) {
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
		textEditorTabController = make_unique<TextEditorTabController>(this);
		textEditorTabController->initialize(editorView->getScreenController()->getScreenNode());
		screenNode->addContextMenuRequestListener(textEditorTabController.get());
		screenNode->addTooltipRequestListener(textEditorTabController.get());
	} catch (Exception& exception) {
		Console::printLine("TextEditorTabView::initialize(): An error occurred: " + string(exception.what()));
	}
	// TODO: load settings
}

void TextEditorTabView::dispose()
{
	textEditorTabController->closeFindReplaceWindow();
	engine->dispose();
}

void TextEditorTabView::updateRendering() {
}

void TextEditorTabView::onMethodSelection(const string& methodName) {
	auto visualizationNode = required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("visualization"));
	auto scrollX = visualizationNode->getChildrenRenderOffsetX();
	auto scrollY = visualizationNode->getChildrenRenderOffsetY();
	createMinitScriptNode(methodName, scrollX + textEditorTabController->getAddNodeX(), scrollY + textEditorTabController->getAddNodeY());
}

Engine* TextEditorTabView::getEngine() {
	return engine.get();
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
		for (const auto& [nodeId, node]: nodes) {
			string nodeType;
			switch (node.type) {
				case Node::NODETYPE_NONE: nodeType = "None"; break;
				case Node::NODETYPE_FLOW: nodeType = "Flow"; break;
				case Node::NODETYPE_ARGUMENT: nodeType = "Argument"; break;
			}
			Console::printLine("Node[" + to_string(i++) + "]: " + node.id + ": " + node.value + "(" + nodeType + ")");
		}
	}
	// dump connections for now
	{
		auto i = 0;
		for (const auto& connection: connections) {
			Console::printLine("Connection[" + to_string(i++) + "]");
			string connectionType;
			switch (connection.type) {
				case Connection::CONNECTIONTYPE_NONE: connectionType = "None"; break;
				case Connection::CONNECTIONTYPE_FLOW: connectionType = "Flow"; break;
				case Connection::CONNECTIONTYPE_ARGUMENT: connectionType = "Argument"; break;
			}
			Console::printLine("\t" + connection.srcNodeId + " --> " + connection.dstNodeId + "(" + connectionType + ")");
		}
	}
	//
	string sourceCode;
	auto startNode = getNodeById(getStartNodeId());
	createSourceCodeFromNodes(sourceCode, startNode);
	Console::printLine(
		"Generated Source Code:\n\n" +
		sourceCode
	);
	auto editorNode = dynamic_cast<GUIElementNode*>(engine->getGUI()->getScreen(screenNode->getId())->getNodeById("editor"));
	if (editorNode != nullptr) editorNode->getActiveConditions().set("text");
	visualEditor = false;
}

void TextEditorTabView::createMinitScriptNode(const string& methodName, int x, int y) {
	auto flattenedId = to_string(nodeIdx++);
	auto method = textEditorTabController->getMinitScript()->getMethod(methodName);

	//
	nodes[flattenedId] = {
		.id = flattenedId,
		.type = Node::NODETYPE_NONE,
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
		for (const auto& flowControlNode: flowControlNodes) {
			if (nodeName == flowControlNode) {
				nodeTypeColor = "color.nodetype_flowcontrol";
				break;
			}
		}
		for (const auto& mathNode: mathNodes) {
			if (nodeName == mathNode || StringTools::startsWith(nodeName, mathNode + ".")) {
				nodeTypeColor = "color.nodetype_math";
				break;
			}
		}
	}
	//
	{
		string xml = "<template src='resources/engine/gui/template_visualcode_node.xml' id='" + flattenedId + "' left='" + to_string(x) + "' top='" + to_string(y) + "' node-name='" + GUIParser::escape(nodeName + "(" + flattenedId + ")") + "' node-type-color='{$" + GUIParser::escape(nodeTypeColor) + "}' />";
		try {
			GUIParser::parse(visualisationNode, xml);
		} catch (Exception& exception) {
			Console::printLine("TextEditorTabView::createMinitScriptNodes(): method/function: " + string(exception.what()));
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
			Console::printLine("TextEditorTabView::createMinitScriptNodes(): method/function: " + string(exception.what()));
		}
	}
	// inputs aka arguments
	{
		//
		auto argumentIdx = 0;
		if (method != nullptr) {
			const auto& argumentTypes = method->getArgumentTypes();
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
					"	pin_color='{$" + GUIParser::escape(getVariableTypePinColor(argumentTypes[argumentIdx].type)) + "}' " +
					"	text='" + GUIParser::escape(argumentName) + "' ";
				if (isLiteral == true) {
					xml+= "	input_text='" + GUIParser::escape(literal) + "' ";
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
					Console::printLine("TextEditorTabView::createMinitScriptNodes(): method/function: " + string(exception.what()));
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
			Console::printLine("TextEditorTabView::createMinitScriptNodes(): method/function: " + string(exception.what()));
		}
	}
	// return value
	if (method != nullptr && method->getReturnValueType() != MinitScript::VariableType::TYPE_NULL) {
		string xml;
		//
		xml+=
			string() +
			"<template " +
			"	id='" + flattenedId + "_r' " +
			"	src='resources/engine/gui/template_visualcode_output.xml' " +
			"	pin_type_connected='resources/engine/images/visualcode_value_connected.png' " +
			"	pin_type_unconnected='resources/engine/images/visualcode_value_unconnected.png' " +
			"	pin_color='{$" + GUIParser::escape(getVariableTypePinColor(method->getReturnValueType())) + "}' " +
			"	text='Return' " +
			"/>";

		//
		try {
			GUIParser::parse(nodeOutputContainer, xml);
			// update to be connected
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(flattenedId + "_r_pin_type_panel"))->getActiveConditions().add("connected");
		} catch (Exception& exception) {
			Console::printLine("TextEditorTabView::createMinitScriptNodes(): method/function: " + string(exception.what()));
		}
	} else
	// functions have a return value pin by default for now
	//	TODO: MinitScript user functions need also formal return values a) to find out if we have a return value at all and to know the type
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
			Console::printLine("TextEditorTabView::createMinitScriptNodes(): method/function: " + string(exception.what()));
		}
	}

	// Bug: Work around! Sometimes layouting is not issued! Need to check!
	screenNode->forceInvalidateLayout(screenNode);
}

void TextEditorTabView::addMinitScriptNodeDeltaX(unordered_map<string, string>& idMapping, const string& id, const MinitScript::SyntaxTreeNode& syntaxTreeNode, int deltaX) {
	auto node = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById(getMinitScriptNodeFlattenedId(idMapping, id)));
	node->getRequestsConstraints().left+= deltaX;
	for (auto argumentIdx = 0; argumentIdx < syntaxTreeNode.arguments.size(); argumentIdx++) {
		//
		auto isLiteral = syntaxTreeNode.arguments[argumentIdx].type == MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL;
		if (isLiteral == true) continue;

		addMinitScriptNodeDeltaX(idMapping, id + "." + to_string(argumentIdx), syntaxTreeNode.arguments[argumentIdx], deltaX);
	}
}

void TextEditorTabView::createMinitScriptScriptNode(unordered_map<string, string>& idMapping, const string& id, MinitScript::Script::Type scriptType, const string& condition, const string& readableName, const MinitScript::SyntaxTreeNode* conditionSyntaxTreeNode, int x, int y, int& width, int& height) {
	// create input nodes
	auto yInitial = y;

	//
	if (conditionSyntaxTreeNode->type != MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_NONE) {
		y+= 200;
		{
			auto childWidth = 0;
			auto childHeight = 0;
			vector<string> leftNodeIds;
			createMinitScriptNodes(idMapping, id + ".c", 0, 1, conditionSyntaxTreeNode, Node::NODETYPE_ARGUMENT, x, y, childWidth, childHeight, leftNodeIds, 1);
			x+= childWidth;
			width+= childWidth;
			height+= childHeight;
		}

		//
		y = yInitial;
	}

	//
	auto flattenedId = getMinitScriptNodeFlattenedId(idMapping, id);

	//
	{
		//
		nodes[flattenedId] = {
			.id = flattenedId,
			.type = Node::NODETYPE_ARGUMENT,
			.value = conditionSyntaxTreeNode->value.getValueAsString(),
			.returnValueType = MinitScript::VariableType::TYPE_NULL,
			.left = x,
			.top = y
		};

		//
		auto nodeName = readableName;
		string nodeTypeColor = string("color.nodetype_condition");
		//
		{
			string xml = "<template src='resources/engine/gui/template_visualcode_node.xml' id='" + flattenedId + "' left='" + to_string(x) + "' top='" + to_string(y) + "' node-name='" + GUIParser::escape(nodeName + "(" + flattenedId + ")") + "' node-type-color='{$" + GUIParser::escape(nodeTypeColor) + "}' />";
			try {
				GUIParser::parse(visualisationNode, xml);
			} catch (Exception& exception) {
				Console::printLine("TextEditorTabView::createMinitScriptScriptNode(): method/function: " + string(exception.what()));
			}
		}
		//
		auto nodeInputContainer = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById(id + "_input_container"));
		// condition input
		{
			//
			auto isLiteral = conditionSyntaxTreeNode->type == MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_NONE;
			auto literal = isLiteral == true?condition:string();
			//
			string xml =
				string() +
				"<template " +
				"	id='" + flattenedId + "_c' " +
				"	src='resources/engine/gui/template_visualcode_input.xml' " +
				"	pin_type_connected='resources/engine/images/visualcode_value_connected.png' " +
				"	pin_type_unconnected='resources/engine/images/visualcode_value_unconnected.png' " +
				"	pin_color='{$" + GUIParser::escape(getVariableTypePinColor(MinitScript::VariableType::TYPE_BOOLEAN)) + "}' " +
				"	text='" + GUIParser::escape("Cond") + "' ";
			if (isLiteral == true) {
				xml+= "	input_text='" + GUIParser::escape(literal) + "' ";
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
				Console::printLine("TextEditorTabView::createMinitScriptScriptNode(): method/function: " + string(exception.what()));
			}
		}
	}

	// create connection to condition node return to node cond node
	if (conditionSyntaxTreeNode->type != MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_NONE) {
		//
		string argumentInputNodeId = flattenedId + "_c";
		string argumentOutputNodeId = getMinitScriptNodeFlattenedId(idMapping, id + ".c_r");
		auto argumentInputNode = dynamic_cast<GUINode*>(screenNode->getNodeById(argumentInputNodeId));
		auto argumentOutputNode = dynamic_cast<GUINode*>(screenNode->getNodeById(argumentOutputNodeId));
		if (argumentInputNode == nullptr) {
			Console::printLine("TextEditorTabView::createMinitScriptNodes(): missing argument input node: " + argumentInputNodeId);
		} else
		if (argumentOutputNode == nullptr) {
			Console::printLine("TextEditorTabView::createMinitScriptNodes(): missing argument output node: " + argumentOutputNodeId);
		} else {

			//
			auto pinColor = string("color.pintype_boolean");
			GUIColor color(GUIParser::getEngineThemeProperties()->get(pinColor, "#ffffff"));

			//
			const auto& argumentInputNodeComputedConstraints = argumentInputNode->getComputedConstraints();
			const auto& argumentOutputNodeComputedConstraints = argumentOutputNode->getComputedConstraints();
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

void TextEditorTabView::createMinitScriptNodes(unordered_map<string, string>& idMapping, const string& id, int syntaxTreeNodeIdx, int syntaxTreeNodeCount, const MinitScript::SyntaxTreeNode* syntaxTreeNode, Node::NodeType nodeType, int x, int y, int& width, int& height, vector<string>& createdNodeIds, int depth) {
	// create input nodes
	int childMaxWidth = 0;
	auto yInitial = y;

	//
	y+= 200;
	vector<string> leftNodeIds;
	for (auto argumentIdx = 0; argumentIdx < syntaxTreeNode->arguments.size(); argumentIdx++) {
		//
		auto isLiteral = syntaxTreeNode->arguments[argumentIdx].type == MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL;
		if (isLiteral == true) continue;
		//
		auto childWidth = 0;
		auto childHeight = 0;
		createMinitScriptNodes(idMapping, id + "." + to_string(argumentIdx), argumentIdx, syntaxTreeNode->arguments.size(), &syntaxTreeNode->arguments[argumentIdx], Node::NODETYPE_ARGUMENT, x, y, childWidth, childHeight, leftNodeIds, depth + 1);
		if (childWidth > childMaxWidth) childMaxWidth = childWidth;
		y+= childHeight;
		height+= childHeight;
	}

	//
	y = yInitial;
	x+= childMaxWidth;
	width+= childMaxWidth;

	//
	for (const auto& nodeId: leftNodeIds) createdNodeIds.push_back(nodeId);

	//
	auto flattenedId = getMinitScriptNodeFlattenedId(idMapping, id);

	//
	switch (syntaxTreeNode->type) {
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD:
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:
			{
				//
				createdNodeIds.push_back(flattenedId);
				//
				nodes[flattenedId] = {
					.id = flattenedId,
					.type = nodeType,
					.value = syntaxTreeNode->value.getValueAsString(),
					.returnValueType = syntaxTreeNode->getMethod() != nullptr?syntaxTreeNode->getMethod()->getReturnValueType():MinitScript::VariableType::TYPE_NULL,
					.left = x,
					.top = y
				};
				//
				auto nodeName = syntaxTreeNode->value.getValueAsString();
				auto nodeTypeColor = string("color.nodetype_method");
				auto methodOperatorMapIt = methodOperatorMap.find(nodeName);
				if (methodOperatorMapIt != methodOperatorMap.end()) {
					nodeName = methodOperatorMapIt->second;
					nodeTypeColor = "color.nodetype_math";
				}

				if (syntaxTreeNode->getMethod() == nullptr) {
					nodeTypeColor = "color.nodetype_function";
				} else {
					for (const auto& flowControlNode: flowControlNodes) {
						if (nodeName == flowControlNode) {
							nodeTypeColor = "color.nodetype_flowcontrol";
							break;
						}
					}
					for (const auto& mathNode: mathNodes) {
						if (nodeName == mathNode || StringTools::startsWith(nodeName, mathNode + ".")) {
							nodeTypeColor = "color.nodetype_math";
							break;
						}
					}
				}
				//
				{
					string xml = "<template src='resources/engine/gui/template_visualcode_node.xml' id='" + flattenedId + "' left='" + to_string(x) + "' top='" + to_string(y) + "' node-name='" + GUIParser::escape(nodeName + "(" + flattenedId + ")") + "' node-type-color='{$" + GUIParser::escape(nodeTypeColor) + "}' />";
					try {
						GUIParser::parse(visualisationNode, xml);
					} catch (Exception& exception) {
						Console::printLine("TextEditorTabView::createMinitScriptNodes(): method/function: " + string(exception.what()));
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
						Console::printLine("TextEditorTabView::createMinitScriptNodes(): method/function: " + string(exception.what()));
					}
				}
				// inputs aka arguments
				{
					//
					auto argumentIdx = 0;
					if (syntaxTreeNode->getMethod() != nullptr) {
						const auto& argumentTypes = syntaxTreeNode->getMethod()->getArgumentTypes();
						for (argumentIdx = 0; argumentIdx < argumentTypes.size(); argumentIdx++) {
							//
							auto isLiteral = argumentIdx < syntaxTreeNode->arguments.size()?syntaxTreeNode->arguments[argumentIdx].type == MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL:false;
							auto literal = isLiteral == true?syntaxTreeNode->arguments[argumentIdx].value.getValueAsString():string();
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
								"	pin_color='{$" + GUIParser::escape(getVariableTypePinColor(argumentTypes[argumentIdx].type)) + "}' " +
								"	text='" + GUIParser::escape(argumentName) + "' ";
							if (isLiteral == true) {
								xml+= "	input_text='" + GUIParser::escape(literal) + "' ";
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
								Console::printLine("TextEditorTabView::createMinitScriptNodes(): method/function: " + string(exception.what()));
							}
						}
					}
					for (; argumentIdx < syntaxTreeNode->arguments.size(); argumentIdx++) {
						//
						auto isLiteral = syntaxTreeNode->arguments[argumentIdx].type == MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL;
						auto literal = isLiteral == true?syntaxTreeNode->arguments[argumentIdx].value.getValueAsString():string();
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
							xml+= "	input_text='" + GUIParser::escape(literal) + "' ";
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
							Console::printLine("TextEditorTabView::createMinitScriptNodes(): method/function: " + string(exception.what()));
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
						Console::printLine("TextEditorTabView::createMinitScriptNodes(): method/function: " + string(exception.what()));
					}
				}
				// return value
				if (syntaxTreeNode->getMethod() != nullptr && syntaxTreeNode->getMethod()->getReturnValueType() != MinitScript::VariableType::TYPE_NULL) {
					string xml;
					//
					xml+=
						string() +
						"<template " +
						"	id='" + flattenedId + "_r' " +
						"	src='resources/engine/gui/template_visualcode_output.xml' " +
						"	pin_type_connected='resources/engine/images/visualcode_value_connected.png' " +
						"	pin_type_unconnected='resources/engine/images/visualcode_value_unconnected.png' " +
						"	pin_color='{$" + GUIParser::escape(getVariableTypePinColor(syntaxTreeNode->getMethod()->getReturnValueType())) + "}' " +
						"	text='Return' " +
						"/>";

					//
					try {
						GUIParser::parse(nodeOutputContainer, xml);
						// update to be connected
						required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(flattenedId + "_r_pin_type_panel"))->getActiveConditions().add("connected");
					} catch (Exception& exception) {
						Console::printLine("TextEditorTabView::createMinitScriptNodes(): method/function: " + string(exception.what()));
					}
				} else
				// functions have a return value pin by default for now
				//	TODO: MinitScript user functions need also formal return values a) to find out if we have a return value at all and to know the type
				if (syntaxTreeNode->getMethod() == nullptr) {
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
						Console::printLine("TextEditorTabView::createMinitScriptNodes(): method/function: " + string(exception.what()));
					}
				}
				break;
			}
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL:
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
		auto isLiteral = syntaxTreeNode->arguments[argumentIdx].type == MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL;
		if (isLiteral == true) continue;
		//
		auto nextLevelNode = required_dynamic_cast<GUINode*>(screenNode->getNodeById(getMinitScriptNodeFlattenedId(idMapping, id + "." + to_string(argumentIdx))));
		auto nodeXPosition = nextLevelNode->getRequestsConstraints().left;
		auto rootDistance = Math::abs(x - nodeXPosition);
		if (rootDistance < rootDistanceMax) {
			rootDistanceMax = rootDistance;
			nextLevelXBestFit = nodeXPosition;
		}
	}
	for (auto argumentIdx = 0; argumentIdx < syntaxTreeNode->arguments.size(); argumentIdx++) {
		//
		auto isLiteral = syntaxTreeNode->arguments[argumentIdx].type == MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL;
		if (isLiteral == true) continue;
		//
		auto nextLevelNode = required_dynamic_cast<GUINode*>(screenNode->getNodeById(getMinitScriptNodeFlattenedId(idMapping, id + "." + to_string(argumentIdx))));
		auto nodeXPosition = nextLevelNode->getRequestsConstraints().left;
		auto deltaX = nextLevelXBestFit - nodeXPosition;
		if (deltaX == 0) continue;
		addMinitScriptNodeDeltaX(idMapping, id + "." + to_string(argumentIdx), syntaxTreeNode->arguments[argumentIdx], deltaX);
	}

	// create connections to input nodes
	for (auto argumentIdx = 0; argumentIdx < syntaxTreeNode->arguments.size(); argumentIdx++) {
		//
		auto isLiteral = syntaxTreeNode->arguments[argumentIdx].type == MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL;
		if (isLiteral == true) continue;
		//
		string argumentInputNodeId = flattenedId + "_a" + to_string(argumentIdx);
		string argumentOutputNodeId = getMinitScriptNodeFlattenedId(idMapping, id + "." + to_string(argumentIdx)) + "_r";
		auto argumentInputNode = dynamic_cast<GUINode*>(screenNode->getNodeById(argumentInputNodeId));
		auto argumentOutputNode = dynamic_cast<GUINode*>(screenNode->getNodeById(argumentOutputNodeId));
		if (argumentInputNode == nullptr) {
			Console::printLine("TextEditorTabView::createMinitScriptNodes(): missing argument input node: " + argumentInputNodeId);
			continue;
		}
		if (argumentOutputNode == nullptr) {
			Console::printLine("TextEditorTabView::createMinitScriptNodes(): missing argument output node: " + argumentOutputNodeId);
			continue;
		}

		//
		auto pinColor = string("color.pintype_undefined");
		if (syntaxTreeNode->getMethod() != nullptr) {
			const auto& argumentTypes = syntaxTreeNode->getMethod()->getArgumentTypes();
			// first guess from argument type
			if (argumentIdx < argumentTypes.size()) {
				pinColor = getVariableTypePinColor(argumentTypes[argumentIdx].type);
			}
			// no color?, try return value
			if (pinColor == "color.pintype_undefined") {
				auto node = getNodeById(flattenedId + "." + to_string(argumentIdx));
				if (node != nullptr) {
					if (node->returnValueType != MinitScript::VariableType::TYPE_NULL) {
						pinColor = getVariableTypePinColor(node->returnValueType);
					}
				}
			}
		}
		GUIColor color(GUIParser::getEngineThemeProperties()->get(pinColor, "#ffffff"));

		//
		const auto& argumentInputNodeComputedConstraints = argumentInputNode->getComputedConstraints();
		const auto& argumentOutputNodeComputedConstraints = argumentOutputNode->getComputedConstraints();
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

void TextEditorTabView::createMinitScriptBranchNodes(unordered_map<string, string>& idMapping, const string& id, int syntaxTreeNodeIdx, int syntaxTreeNodeCount, const MinitScript::SyntaxTreeNode* syntaxTreeNode, Node::NodeType nodeType, const vector<MinitScriptBranch>& branches, int x, int y, int& width, int& height, vector<string>& createdNodeIds, int depth) {
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
		if (branches[branchIdx].conditionSyntaxTree->type == MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL) continue;

		//
		auto childWidth = 0;
		auto childHeight = 0;
		createMinitScriptNodes(idMapping, id + "." + to_string(branchIdx), branchIdx, branches.size(), branches[branchIdx].conditionSyntaxTree, Node::NODETYPE_ARGUMENT, x, y, childWidth, childHeight, leftNodeIds, depth + 1);
		if (childWidth > childMaxWidth) childMaxWidth = childWidth;
		y+= childHeight;
		height+= childHeight;
	}
	//
	x+= childMaxWidth;
	width+= childMaxWidth;
	y = yInitial;

	//
	for (const auto& nodeId: leftNodeIds) createdNodeIds.push_back(nodeId);
	//
	auto flattenedId = getMinitScriptNodeFlattenedId(idMapping, id);

	//
	{
		//
		createdNodeIds.push_back(flattenedId);
		//
		nodes[flattenedId] = {
			.id = flattenedId,
			.type = nodeType,
			.value = syntaxTreeNode->value.getValueAsString(),
			.returnValueType = MinitScript::VariableType::TYPE_NULL,
			.left = x,
			.top = y
		};
		//
		string nodeName = syntaxTreeNode->value.getValueAsString();
		string nodeTypeColor = string("color.nodetype_flowcontrol");
		//
		{
			string xml = "<template src='resources/engine/gui/template_visualcode_node.xml' id='" + flattenedId + "' left='" + to_string(x) + "' top='" + to_string(y) + "' node-name='" + GUIParser::escape(nodeName + "(" + flattenedId + ")") + "' node-type-color='{$" + GUIParser::escape(nodeTypeColor) + "}' />";
			try {
				GUIParser::parse(visualisationNode, xml);
			} catch (Exception& exception) {
				Console::printLine("TextEditorTabView::createMinitScriptIfBranchNodes(): method/function: " + string(exception.what()));
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
				Console::printLine("TextEditorTabView::createMinitScriptIfBranchNodes(): method/function: " + string(exception.what()));
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
				Console::printLine("TextEditorTabView::createMinitScriptIfBranchNodes(): method/function: " + string(exception.what()));
			}
		}
		// inputs aka arguments
		for (auto branchIdx = 0; branchIdx < branches.size(); branchIdx++) {
			// condition inputs
			//	note: else has no condition syntax tree
			if (branches[branchIdx].conditionSyntaxTree != nullptr) {
				//
				auto isLiteral = branches[branchIdx].conditionSyntaxTree->type == MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL;
				auto literal = isLiteral == true?branches[branchIdx].conditionSyntaxTree->value.getValueAsString():string();
				//
				string xml =
					string() +
					"<template " +
					"	id='" + flattenedId + "_c" + to_string(branchIdx) + "' " +
					"	src='resources/engine/gui/template_visualcode_input.xml' " +
					"	pin_type_connected='resources/engine/images/visualcode_value_connected.png' " +
					"	pin_type_unconnected='resources/engine/images/visualcode_value_unconnected.png' " +
					"	pin_color='{$" + GUIParser::escape(getVariableTypePinColor(nodeName == "forTime"?MinitScript::VariableType::TYPE_INTEGER:MinitScript::VariableType::TYPE_BOOLEAN)) + "}' " +
					"	text='" + GUIParser::escape(nodeName == "forTime"?"time":"Cond " + to_string(branchIdx)) + "' ";
				if (isLiteral == true) {
					xml+= "	input_text='" + GUIParser::escape(literal) + "' ";
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
					Console::printLine("TextEditorTabView::createMinitScriptIfBranchNodes(): method/function: " + string(exception.what()));
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
					Console::printLine("TextEditorTabView::createMinitScriptIfBranchNodes(): method/function: " + string(exception.what()));
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
		if (branches[branchIdx].conditionSyntaxTree->type == MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL) continue;
		//
		auto nextLevelNode = required_dynamic_cast<GUINode*>(screenNode->getNodeById(getMinitScriptNodeFlattenedId(idMapping, id + "." + to_string(branchIdx))));
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
		if (branches[branchIdx].conditionSyntaxTree->type == MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL) continue;
		//
		auto nextLevelNode = required_dynamic_cast<GUINode*>(screenNode->getNodeById(getMinitScriptNodeFlattenedId(idMapping, id + "." + to_string(branchIdx))));
		auto nodeXPosition = nextLevelNode->getRequestsConstraints().left;
		auto deltaX = nextLevelXBestFit - nodeXPosition;
		if (deltaX == 0) continue;
		addMinitScriptNodeDeltaX(idMapping, id + "." + to_string(branchIdx), *branches[branchIdx].conditionSyntaxTree, deltaX);
	}

	// create condition connections
	for (auto branchIdx = 0; branchIdx < branches.size(); branchIdx++) {
		//
		if (branches[branchIdx].conditionSyntaxTree == nullptr ||
			(branches[branchIdx].conditionSyntaxTree != nullptr && branches[branchIdx].conditionSyntaxTree->type == MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL)) continue;
		//
		string conditionInputNodeId = flattenedId + "_c" + to_string(branchIdx);
		string conditionOutputNodeId = getMinitScriptNodeFlattenedId(idMapping, id + "." + to_string(branchIdx));
		auto conditionInputNode = dynamic_cast<GUINode*>(screenNode->getNodeById(conditionInputNodeId));
		auto conditionOutputNode = dynamic_cast<GUINode*>(screenNode->getNodeById(conditionOutputNodeId));
		if (conditionInputNode == nullptr) {
			Console::printLine("TextEditorTabView::createMinitScriptIfBranchNodes(): missing condition input node: " + conditionInputNodeId);
			continue;
		}
		if (conditionOutputNode == nullptr) {
			Console::printLine("TextEditorTabView::createMinitScriptIfBranchNodes(): missing condition output node: " + conditionOutputNodeId);
			continue;
		}

		//
		auto pinColor = string("color.pintype_boolean");
		GUIColor color(GUIParser::getEngineThemeProperties()->get(pinColor, "#ffffff"));

		//
		const auto& conditionInputNodeComputedConstraints = conditionInputNode->getComputedConstraints();
		const auto& conditionOutputNodeComputedConstraints = conditionOutputNode->getComputedConstraints();
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
			while (handleMinitScriptBranch(idMapping, id + ".b." + to_string(branchIdx) + ".", branchSyntaxTreeNodes, i, x, y, branchNodesWidth, branchNodesHeight, rightNodeIds) == true) {
				// advance x
				x+= branchNodesWidth + 100;
				// store max
				branchWidth += branchNodesWidth + 100;
				branchHeightMax = Math::max(branchHeightMax, branchNodesHeight);
				//
				auto nodeFlowInId = getMinitScriptNodeFlattenedId(idMapping, id + ".b." + to_string(branchIdx) + "." + to_string(branchNodeIdx)) + "_fi";
				auto nodeFlowOutId = getMinitScriptNodeFlattenedId(idMapping, id + ".b." + to_string(branchIdx) + "." + to_string(branchNodeIdx)) + "_fo";
				auto nodeFlowIn = dynamic_cast<GUINode*>(screenNode->getNodeById(nodeFlowInId));
				auto nodeFlowOut = dynamic_cast<GUINode*>(screenNode->getNodeById(nodeFlowOutId));
				if (previousNodeFlowNode != nullptr && nodeFlowIn != nullptr) {
					const auto& previousNodeComputedConstraints = previousNodeFlowNode->getComputedConstraints();
					const auto& nodeComputedConstraints = nodeFlowIn->getComputedConstraints();
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
			createMinitScriptNodes(idMapping, id + ".b." + to_string(branchIdx) + "." + to_string(i), i + 1, branchSyntaxTreeNodes.size() + 1, branchSyntaxTreeNode, Node::NODETYPE_FLOW, x, y, branchNodesWidth, branchNodesHeight, rightNodeIds);

			// advance x
			x+= branchNodesWidth + 100;
			// store max
			branchWidth += branchNodesWidth + 100;
			branchHeightMax = Math::max(branchHeightMax, branchNodesHeight);

			// connections
			auto nodeFlowInId = getMinitScriptNodeFlattenedId(idMapping, id + ".b." + to_string(branchIdx) + "." + to_string(i)) + "_fi";
			auto nodeFlowOutId = getMinitScriptNodeFlattenedId(idMapping, id + ".b." + to_string(branchIdx) + "." + to_string(i)) + "_fo";
			auto nodeFlowIn = dynamic_cast<GUINode*>(screenNode->getNodeById(nodeFlowInId));
			auto nodeFlowOut = dynamic_cast<GUINode*>(screenNode->getNodeById(nodeFlowOutId));
			if (previousNodeFlowNode != nullptr && nodeFlowIn != nullptr) {
				const auto& previousNodeComputedConstraints = previousNodeFlowNode->getComputedConstraints();
				const auto& nodeComputedConstraints = nodeFlowIn->getComputedConstraints();
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
	for (const auto& nodeId: rightNodeIds) createdNodeIds.push_back(nodeId);

	// determine bounding box left and right
	auto leftTop = Integer::MAX_VALUE;
	auto leftBottom = Integer::MIN_VALUE;
	for (const auto& leftNodeId: leftNodeIds) {
		auto node = required_dynamic_cast<GUINode*>(screenNode->getNodeById(leftNodeId));
		auto nodeTop = node->getRequestsConstraints().top;
		auto nodeBottom = node->getRequestsConstraints().top + 200;
		leftTop = Math::min(leftTop, nodeTop);
		leftBottom = Math::max(leftBottom, nodeBottom);
	}

	//
	auto rightTop = Integer::MAX_VALUE;
	auto rightBottom = Integer::MIN_VALUE;
	for (const auto& rightNodeId: rightNodeIds) {
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
			for (const auto& rightNodeId: rightNodeIds) {
				auto node = required_dynamic_cast<GUINode*>(screenNode->getNodeById(rightNodeId));
				node->getRequestsConstraints().top+= deltaY;
			}
			{
				auto node = required_dynamic_cast<GUINode*>(screenNode->getNodeById(flattenedId));
				node->getRequestsConstraints().top = yInitial + (leftHeight - 200) / 2;
			}
		} else {
			auto deltaY = (rightHeight - leftHeight) / 2;
			for (const auto& leftNodeId: leftNodeIds) {
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


bool TextEditorTabView::handleMinitScriptBranch(unordered_map<string, string>& idMapping, const string& idPrefix, const vector<MinitScript::SyntaxTreeNode*>& syntaxTree, int& i, int x, int y, int& width, int& height, vector<string>& createdNodeIds) {
	//
	auto syntaxTreeNode = syntaxTree[i];
	auto syntaxTreeNodeIdx = i;
	// handle if
	if (syntaxTreeNode->type == MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD &&
		(syntaxTreeNode->value.getValueAsString() == "if" ||
		syntaxTreeNode->value.getValueAsString() == "forCondition" ||
		syntaxTreeNode->value.getValueAsString() == "forTime")) {
		// support if depth
		auto ifStatement = syntaxTreeNode->value.getValueAsString() == "if";
		auto stackDepth = 1;
		vector<MinitScriptBranch> branches;
		branches.push_back(
			{
				.name = syntaxTreeNode->value.getValueAsString(),
				.conditionSyntaxTree = syntaxTreeNode->arguments.empty() == false?&syntaxTreeNode->arguments[0]:nullptr,
				.syntaxTreeNodes = {}
			}
		);
		for (i++; i < syntaxTree.size(); i++) {
			auto branchSyntaxTreeNode = syntaxTree[i];
			if (branchSyntaxTreeNode->type == MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD &&
				(branchSyntaxTreeNode->value.getValueAsString() == "if" ||
				branchSyntaxTreeNode->value.getValueAsString() == "forCondition" ||
				branchSyntaxTreeNode->value.getValueAsString() == "forTime")) {
				stackDepth++;
				branches[branches.size() - 1].syntaxTreeNodes.push_back(branchSyntaxTreeNode);
			} else
			if (ifStatement == true && stackDepth == 1 && branchSyntaxTreeNode->type == MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD && branchSyntaxTreeNode->value.getValueAsString() == "elseif") {
				branches.push_back(
					{
						.name = branchSyntaxTreeNode->value.getValueAsString(),
						.conditionSyntaxTree = branchSyntaxTreeNode->arguments.empty() == false?&branchSyntaxTreeNode->arguments[0]:nullptr,
						.syntaxTreeNodes = {}
					}
				);
			} else
			if (ifStatement == true && stackDepth == 1 && branchSyntaxTreeNode->type == MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD && branchSyntaxTreeNode->value.getValueAsString() == "else") {
				branches.push_back(
					{
						.name = branchSyntaxTreeNode->value.getValueAsString(),
						.conditionSyntaxTree = nullptr,
						.syntaxTreeNodes = {}
					}
				);
			} else
			if (branchSyntaxTreeNode->type == MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD && branchSyntaxTreeNode->value.getValueAsString() == "end") {
				//
				stackDepth--;
				// done?
				if (stackDepth == 0) {
					//
					createMinitScriptBranchNodes(idMapping, idPrefix + to_string(syntaxTreeNodeIdx), syntaxTreeNodeIdx, syntaxTree.size(), syntaxTreeNode, Node::NODETYPE_FLOW, branches, x, y, width, height, createdNodeIds);
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

void TextEditorTabView::updateMinitScriptSyntaxTree(int minitScriptScriptIdx) {
	visualisationNode->clearSubNodes();
	this->connections.clear();
	this->nodes.clear();
	this->minitScriptScriptIdx = minitScriptScriptIdx;
	//
	unordered_map<string, string> idMapping;
	// structure
	if (minitScriptScriptIdx == MINISCRIPT_SCRIPTIDX_STRUCTURE) {
		auto syntaxTrees = textEditorTabController->getMinitScriptSyntaxTrees();

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
			createMinitScriptScriptNode(idMapping, to_string(i), syntaxTrees[i].type, syntaxTrees[i].condition, syntaxTrees[i].name, &syntaxTrees[i].conditionSyntaxTree, x, y, width, height);

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
		auto syntaxTree = textEditorTabController->getMinitScriptSyntaxTrees()[minitScriptScriptIdx].syntaxTree;
		// 	construct syntax tree as vector of pointers to the nodes
		vector<MinitScript::SyntaxTreeNode*> syntaxTreeNodes;
		for (auto& syntaxTreeNode: syntaxTree) syntaxTreeNodes.push_back(&syntaxTreeNode);
		// 	remove end node if we have any
		if (syntaxTreeNodes.empty() == false &&
			syntaxTreeNodes[syntaxTreeNodes.size() - 1]->type == MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD &&
			syntaxTreeNodes[syntaxTreeNodes.size() - 1]->value.getValueAsString() == "end") {
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
			while (handleMinitScriptBranch(idMapping, string(), syntaxTreeNodes, i, x, y, width, height, createdNodeIds) == true) {
				//
				x+= width + 100;
				yMax = Math::max(y + height, yMax);
				//
				auto nodeFlowInId = getMinitScriptNodeFlattenedId(idMapping, to_string(branchNodeIdx)) + "_fi";
				auto nodeFlowOutId = getMinitScriptNodeFlattenedId(idMapping, to_string(branchNodeIdx)) + "_fo";
				auto nodeFlowIn = dynamic_cast<GUINode*>(screenNode->getNodeById(nodeFlowInId));
				auto nodeFlowOut = dynamic_cast<GUINode*>(screenNode->getNodeById(nodeFlowOutId));
				if (previousNodeFlowNode != nullptr && nodeFlowIn != nullptr) {
					const auto& previousNodeComputedConstraints = previousNodeFlowNode->getComputedConstraints();
					const auto& nodeComputedConstraints = nodeFlowIn->getComputedConstraints();
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
			createMinitScriptNodes(idMapping, to_string(i), i, syntaxTreeNodes.size(), syntaxTreeNode, Node::NODETYPE_FLOW, x, y, width, height, createdNodeIds);

			//
			x+= width + 100;
			yMax = Math::max(y + height, yMax);

			// connections
			auto nodeFlowInId = getMinitScriptNodeFlattenedId(idMapping, to_string(i)) + "_fi";
			auto nodeFlowOutId = getMinitScriptNodeFlattenedId(idMapping, to_string(i)) + "_fo";
			auto nodeFlowIn = dynamic_cast<GUINode*>(screenNode->getNodeById(nodeFlowInId));
			auto nodeFlowOut = dynamic_cast<GUINode*>(screenNode->getNodeById(nodeFlowOutId));
			if (previousNodeFlowNode != nullptr && nodeFlowIn != nullptr) {
				const auto& previousNodeComputedConstraints = previousNodeFlowNode->getComputedConstraints();
				const auto& nodeComputedConstraints = nodeFlowIn->getComputedConstraints();
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

void TextEditorTabView::createMinitScriptConnections() {
	for (auto& connection: connections) {
		auto srcNode = dynamic_cast<GUINode*>(screenNode->getNodeById(connection.srcNodeId));
		auto dstNode = dynamic_cast<GUINode*>(screenNode->getNodeById(connection.dstNodeId));
		if (srcNode == nullptr) {
			continue;
		} else
		if (dstNode == nullptr) {
			continue;
		}
		const auto& srcNodeComputedConstraints = srcNode->getComputedConstraints();
		const auto& dstNodeComputedConstraints = dstNode->getComputedConstraints();
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
					MinitScript::Variable value;
					MinitScript::Statement scriptStatement(
						"texteditortabview",
						MinitScript::LINE_NONE,
						MinitScript::STATEMENTIDX_NONE,
						string(),
						string(),
						MinitScript::STATEMENTIDX_NONE
					);
					value.setImplicitTypedValueFromStringView("texteditortabview", literalInputValue, textEditorTabController->getMinitScript(), MinitScript::SCRIPTIDX_NONE, scriptStatement);
					if (value.getType() == MinitScript::TYPE_STRING) {
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

void TextEditorTabView::deleteConnection(const string& nodeId) {
	for (auto i = 0; i < connections.size(); i++) {
		const auto& connection = connections[i];
		auto srcNodeMatch = connection.srcNodeId == nodeId || StringTools::startsWith(connection.srcNodeId, nodeId + "_") == true;
		auto dstNodeMatch = connection.dstNodeId == nodeId || StringTools::startsWith(connection.dstNodeId, nodeId + "_") == true;
		if (srcNodeMatch == true || dstNodeMatch == true) {
			connections.erase(connections.begin() + i);
			i--;
		}
	}
}

void TextEditorTabView::deleteNode(const string& nodeId) {
	auto nodeIt = nodes.find(nodeId);
	if (nodeIt == nodes.end()) return;
	nodes.erase(nodeIt);
	deleteConnection(nodeId);
	screenNode->removeNodeById(nodeId, false);

	// Bug: Work around! Sometimes layouting is not issued! Need to check!
	screenNode->forceInvalidateLayout(screenNode);

	//
	createConnectionsPasses = 3;
}

void TextEditorTabView::createConnection(const string& guiNodeId) {
	Console::printLine("TextEditorTabView::createConnection(): " + guiNodeId);
	// return value as argument
	if (guiNodeId.find("_r_") != string::npos) {
		auto connectionNodeId = StringTools::substring(guiNodeId, 0, guiNodeId.find("_r_") + 2);
		auto nodeId = StringTools::substring(guiNodeId, 0, guiNodeId.find("_r_"));
		auto argumentOutputNode = dynamic_cast<GUINode*>(screenNode->getNodeById(connectionNodeId));
		if (argumentOutputNode != nullptr) {
			deleteConnection(connectionNodeId);
			const auto& argumentOutputNodeComputedConstraints = argumentOutputNode->getComputedConstraints();
			auto pinColor = string("color.pintype_undefined");
			GUIColor color(GUIParser::getEngineThemeProperties()->get(pinColor, "#ffffff"));
			connections.push_back(
				{
					.type = Connection::CONNECTIONTYPE_ARGUMENT,
					.srcNodeId = string(),
					.dstNodeId = connectionNodeId,
					.red = static_cast<uint8_t>(color.getRed() * 255.0f),
					.green = static_cast<uint8_t>(color.getGreen() * 255.0f),
					.blue = static_cast<uint8_t>(color.getBlue() * 255.0f),
					.alpha = static_cast<uint8_t>(color.getAlpha() * 255.0f),
					.x1 = argumentOutputNodeComputedConstraints.left + argumentOutputNodeComputedConstraints.width,
					.y1 = argumentOutputNodeComputedConstraints.top + argumentOutputNodeComputedConstraints.height / 2,
					.x2 = argumentOutputNodeComputedConstraints.left + argumentOutputNodeComputedConstraints.width,
					.y2 = argumentOutputNodeComputedConstraints.top + argumentOutputNodeComputedConstraints.height / 2,
				}
			);
			//
			createConnectionIdx = connections.size() - 1;
			createConnectionMode = CREATECONNECTIONMODE_ARGUMENT_OUT;
		}
	} else
	// flow output
	if (guiNodeId.find("_fo_") != string::npos) {
		auto connectionNodeId = StringTools::substring(guiNodeId, 0, guiNodeId.find("_fo_") + 3);
		auto flowOutputFlowNode = dynamic_cast<GUINode*>(screenNode->getNodeById(connectionNodeId));
		if (flowOutputFlowNode != nullptr) {
			deleteConnection(connectionNodeId);
			const auto& flowOutputNodeComputedConstraints = flowOutputFlowNode->getComputedConstraints();
			auto pinColor = string("color.pintype_undefined");
			GUIColor color(GUIParser::getEngineThemeProperties()->get(pinColor, "#ffffff"));
			connections.push_back(
				{
					.type = Connection::CONNECTIONTYPE_FLOW,
					.srcNodeId = connectionNodeId,
					.dstNodeId = string(),
					.red = 255,
					.green = 255,
					.blue = 255,
					.alpha = 255,
					.x1 = flowOutputNodeComputedConstraints.left + flowOutputNodeComputedConstraints.width,
					.y1 = flowOutputNodeComputedConstraints.top + flowOutputNodeComputedConstraints.height / 2,
					.x2 = flowOutputNodeComputedConstraints.left + flowOutputNodeComputedConstraints.width,
					.y2 = flowOutputNodeComputedConstraints.top + flowOutputNodeComputedConstraints.height / 2,
				}
			);
			//
			createConnectionIdx = connections.size() - 1;
			createConnectionMode = CREATECONNECTIONMODE_FLOW_OUT;
		}
	} else
	// flow input
	if (guiNodeId.find("_fi_") != string::npos) {
		auto connectionNodeId = StringTools::substring(guiNodeId, 0, guiNodeId.find("_fi_") + 3);
		auto flowInputNode = dynamic_cast<GUINode*>(screenNode->getNodeById(connectionNodeId));
		if (flowInputNode != nullptr) {
			deleteConnection(connectionNodeId);
			const auto& flowInputNodeComputedConstraints = flowInputNode->getComputedConstraints();
			auto pinColor = string("color.pintype_undefined");
			GUIColor color(GUIParser::getEngineThemeProperties()->get(pinColor, "#ffffff"));
			connections.push_back(
				{
					.type = Connection::CONNECTIONTYPE_FLOW,
					.srcNodeId = string(),
					.dstNodeId = connectionNodeId,
					.red = 255,
					.green = 255,
					.blue = 255,
					.alpha = 255,
					.x1 = flowInputNodeComputedConstraints.left,
					.y1 = flowInputNodeComputedConstraints.top + flowInputNodeComputedConstraints.height / 2,
					.x2 = flowInputNodeComputedConstraints.left,
					.y2 = flowInputNodeComputedConstraints.top + flowInputNodeComputedConstraints.height / 2,
				}
			);
			//
			createConnectionIdx = connections.size() - 1;
			createConnectionMode = CREATECONNECTIONMODE_FLOW_IN;
		}
	} else
	// argument
	if (guiNodeId.find("_a") != string::npos) {
		auto connectionNodeId = StringTools::substring(guiNodeId, 0, guiNodeId.find("_", guiNodeId.find("_a") + 2));
		auto argumentInputNode = dynamic_cast<GUINode*>(screenNode->getNodeById(connectionNodeId));
		if (argumentInputNode != nullptr) {
			deleteConnection(connectionNodeId);
			const auto& argumentInputNodeComputedConstraints = argumentInputNode->getComputedConstraints();
			auto pinColor = string("color.pintype_undefined");
			GUIColor color(GUIParser::getEngineThemeProperties()->get(pinColor, "#ffffff"));
			connections.push_back(
				{
					.type = Connection::CONNECTIONTYPE_ARGUMENT,
					.srcNodeId = guiNodeId,
					.dstNodeId = string(),
					.red = static_cast<uint8_t>(color.getRed() * 255.0f),
					.green = static_cast<uint8_t>(color.getGreen() * 255.0f),
					.blue = static_cast<uint8_t>(color.getBlue() * 255.0f),
					.alpha = static_cast<uint8_t>(color.getAlpha() * 255.0f),
					.x1 = argumentInputNodeComputedConstraints.left,
					.y1 = argumentInputNodeComputedConstraints.top + argumentInputNodeComputedConstraints.height / 2,
					.x2 = argumentInputNodeComputedConstraints.left,
					.y2 = argumentInputNodeComputedConstraints.top + argumentInputNodeComputedConstraints.height / 2,
				}
			);
			//
			createConnectionIdx = connections.size() - 1;
			createConnectionMode = CREATECONNECTIONMODE_ARGUMENT_IN;
		}
	}
}

void TextEditorTabView::finishCreateConnection(int mouseX, int mouseY) {
	if (isCreatingConnection() == false) return;

	//
	unordered_set<string> nodeIds;
	screenNode->determineNodesByCoordinate(Vector2(mouseX, mouseY).getArray(), nodeIds);
	for (const auto& nodeId: nodeIds) {
		// return value as argument
		if (nodeId.find("_r_") != string::npos) {
			if (createConnectionMode != CREATECONNECTIONMODE_ARGUMENT_IN) {
				textEditorTabController->showInfoPopUp("Warning", "You can not connect a Argument Input with a " + getCreateConnectionModeName(createConnectionMode));
			} else {
				auto connectionNodeId = StringTools::substring(nodeId, 0, nodeId.find("_r_") + 2);
				auto argumentNode = dynamic_cast<GUINode*>(screenNode->getNodeById(connectionNodeId));
				if (argumentNode != nullptr) {
					// TODO: set node type
					auto connection = connections[createConnectionIdx];
					connections.erase(connections.begin() + createConnectionIdx);
					createConnectionIdx = -1;
					deleteConnection(connectionNodeId);
					const auto& argumentNodeComputedConstraints = argumentNode->getComputedConstraints();
					connection.dstNodeId = connectionNodeId;
					connection.x2 = argumentNodeComputedConstraints.left + argumentNodeComputedConstraints.width;
					connection.y2 = argumentNodeComputedConstraints.top + argumentNodeComputedConstraints.height / 2;
					connections.push_back(connection);
					//
					break;
				}
			}
		} else
		// flow output
		if (nodeId.find("_fo_") != string::npos) {
			auto connectionNodeId = StringTools::substring(nodeId, 0, nodeId.find("_fo_") + 3);
			if (createConnectionMode != CREATECONNECTIONMODE_FLOW_IN) {
				textEditorTabController->showInfoPopUp("Warning", "You can not connect a Flow Input with a " + getCreateConnectionModeName(createConnectionMode));
			} else {
				auto flowNode = dynamic_cast<GUINode*>(screenNode->getNodeById(connectionNodeId));
				if (flowNode != nullptr) {
					// TODO: set node type
					auto connection = connections[createConnectionIdx];
					connections.erase(connections.begin() + createConnectionIdx);
					createConnectionIdx = -1;
					deleteConnection(connectionNodeId);
					const auto& flowNodeComputedConstraints = flowNode->getComputedConstraints();
					connection.srcNodeId = connectionNodeId;
					connection.x1 = flowNodeComputedConstraints.left;
					connection.y1 = flowNodeComputedConstraints.top + flowNodeComputedConstraints.height / 2;
					connections.push_back(connection);
					//
					break;
				}
			}
		} else
		// flow input
		if (nodeId.find("_fi_") != string::npos) {
			auto connectionNodeId = StringTools::substring(nodeId, 0, nodeId.find("_fi_") + 3);
			if (createConnectionMode != CREATECONNECTIONMODE_FLOW_OUT) {
				textEditorTabController->showInfoPopUp("Warning", "You can not connect a Flow Output with a " + getCreateConnectionModeName(createConnectionMode));
			} else {
				auto flowNode = dynamic_cast<GUINode*>(screenNode->getNodeById(connectionNodeId));
				if (flowNode != nullptr) {
					// TODO: set node type
					auto connection = connections[createConnectionIdx];
					connections.erase(connections.begin() + createConnectionIdx);
					createConnectionIdx = -1;
					deleteConnection(connectionNodeId);
					const auto& flowNodeComputedConstraints = flowNode->getComputedConstraints();
					connection.dstNodeId = connectionNodeId;
					connection.x2 = flowNodeComputedConstraints.left + flowNodeComputedConstraints.width;
					connection.y2 = flowNodeComputedConstraints.top + flowNodeComputedConstraints.height / 2;
					connections.push_back(connection);
					//
					break;
				}
			}
		} else
		// argument
		if (nodeId.find("_a") != string::npos) {
			auto connectionNodeId = StringTools::substring(nodeId, 0, nodeId.find("_", nodeId.find("_a") + 2));
			if (createConnectionMode != CREATECONNECTIONMODE_ARGUMENT_OUT) {
				textEditorTabController->showInfoPopUp("Warning", "You can not connect a Argument Output with a " + getCreateConnectionModeName(createConnectionMode));
			} else {
				auto argumentNode = dynamic_cast<GUINode*>(screenNode->getNodeById(connectionNodeId));
				if (argumentNode != nullptr) {
					// TODO: set node type
					auto connection = connections[createConnectionIdx];
					connections.erase(connections.begin() + createConnectionIdx);
					createConnectionIdx = -1;
					deleteConnection(connectionNodeId);
					const auto& argumentNodeComputedConstraints = argumentNode->getComputedConstraints();
					connection.srcNodeId = connectionNodeId;
					connection.x1 = argumentNodeComputedConstraints.left;
					connection.y1 = argumentNodeComputedConstraints.top + argumentNodeComputedConstraints.height / 2;
					connections.push_back(connection);
					//
					break;
				}
			}
		}
	}

	//
	if (createConnectionIdx != -1) connections.erase(connections.begin() + createConnectionIdx);
	createConnectionMode = CREATECONNECTIONMODE_NONE;
	createConnectionIdx = -1;

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
				class OnNodeDeleteAction: public Action
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
				popUps->getContextMenuScreenController()->setMinitScriptMethodSelectionListener(this);
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
