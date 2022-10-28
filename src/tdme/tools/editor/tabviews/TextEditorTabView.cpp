#include <tdme/tools/editor/tabviews/TextEditorTabView.h>

#include <algorithm>
#include <cctype>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/ColorTextureCanvas.h>
#include <tdme/engine/DynamicColorTexture.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/events/GUIMoveListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIFrameBufferNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUIStyledTextNode.h>
#include <tdme/gui/nodes/GUIStyledTextNodeController.h>
#include <tdme/gui/nodes/GUITextureNode.h>
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
#include <tdme/tools/editor/tabcontrollers/TextEditorTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/StringTools.h>

using std::sort;
using std::string;

using tdme::tools::editor::tabviews::TextEditorTabView;

using tdme::engine::model::Color4;
using tdme::engine::ColorTextureCanvas;
using tdme::engine::DynamicColorTexture;
using tdme::engine::Engine;
using tdme::gui::events::GUIMoveListener;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIFrameBufferNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUIStyledTextNode;
using tdme::gui::nodes::GUITextureNode;
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
using tdme::tools::editor::tabcontrollers::TextEditorTabController;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::StringTools;

TextEditorTabView::TextEditorTabView(EditorView* editorView, const string& tabId, GUIScreenNode* screenNode, const string& fileName)
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->popUps = editorView->getPopUps();
	this->tabScreenNode = screenNode;
	this->extension = extension;
	this->textNode = required_dynamic_cast<GUIStyledTextNode*>(screenNode->getInnerNodeById("text"));
	this->fileName = fileName;
	auto fileNameLowerCase = StringTools::toLowerCase(fileName);
	this->extension = StringTools::substring(fileNameLowerCase, fileNameLowerCase.rfind('.') + 1, fileNameLowerCase.size());
	engine = Engine::createOffScreenInstance(512, 512, false, false, false);
	engine->setSceneColor(Color4(125.0f / 255.0f, 125.0f / 255.0f, 125.0f / 255.0f, 1.0f));
	engine->getGUI()->addScreen(screenNode->getId(), screenNode);
	engine->getGUI()->addRenderScreen(screenNode->getId());

	//
	visualCodingEnabled = extension == "tscript";
	if (visualCodingEnabled == true) {
		linesTexture = new DynamicColorTexture(engine->getWidth(), engine->getHeight());
		linesTexture->initialize();
		required_dynamic_cast<GUITextureNode*>(tabScreenNode->getNodeById("visualization_texture"))->setTexture(linesTexture);
		// add node move listener
		class NodeMoveListener: public GUIMoveListener {
		public:
			NodeMoveListener(TextEditorTabView* textEditorTabView): textEditorTabView(textEditorTabView) {
			}
			void onMoved(GUINode* node) {
				auto visualisationNode = required_dynamic_cast<GUIParentNode*>(textEditorTabView->tabScreenNode->getNodeById("visualization_canvas"));
				auto& nodeComputedConstraints = node->getComputedConstraints();
				auto xMax = nodeComputedConstraints.left + nodeComputedConstraints.width;
				auto yMax = nodeComputedConstraints.top + nodeComputedConstraints.height;
				visualisationNode->getComputedConstraints().width = Math::max(visualisationNode->getComputedConstraints().width, xMax);
				visualisationNode->getComputedConstraints().height = Math::max(visualisationNode->getComputedConstraints().height, yMax);
				visualisationNode->getRequestsConstraints().width = Math::max(visualisationNode->getRequestsConstraints().width, xMax);
				visualisationNode->getRequestsConstraints().height = Math::max(visualisationNode->getRequestsConstraints().height, yMax);
				textEditorTabView->createConnectionsPasses = 3;
			}

		private:
			TextEditorTabView* textEditorTabView;
		};
		tabScreenNode->addMoveListener(new NodeMoveListener(this));
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
				TextFormatter::getInstance()->format(textEditorTabView->extension, textEditorTabView->textNode, idx, idx + count);
			}
			virtual void onInsertText(int idx, int count) override {
				TextFormatter::getInstance()->format(textEditorTabView->extension, textEditorTabView->textNode, idx, idx + count);
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
					int left, top, width, height;
					auto selectedTab = textEditorTabView->getEditorView()->getScreenController()->getSelectedTab();
					if (selectedTab != nullptr) {
						textEditorTabView->getEditorView()->getViewPort(selectedTab->getFrameBufferNode(), left, top, width, height);
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
		auto visualizationNode = required_dynamic_cast<GUIParentNode*>(tabScreenNode->getInnerNodeById("visualization"));

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
			auto visualizationTextureNode = dynamic_cast<GUITextureNode*>(tabScreenNode->getNodeById("visualization_texture"));
			if (visualizationTextureNode != nullptr) visualizationTextureNode->setTexture(linesTexture);
			createConnectionsPasses = 3;
		}
		// we have a layouting issue here, we cant get dimensions of nodes right after adding them, so defer this for now
		if (createConnectionsPasses > 0) {
			auto visualizationScrollArea = required_dynamic_cast<GUIParentNode*>(tabScreenNode->getNodeById("visualization"));
			auto visualizationWidth = visualizationScrollArea->getComputedConstraints().width;
			auto visualizationHeight = visualizationScrollArea->getComputedConstraints().height;
			auto visualizationScrollX = static_cast<int>(scrollX);
			auto visualizationScrollY = static_cast<int>(scrollY);
			createConnections();
			// create lines
			ColorTextureCanvas canvas(linesTexture->getTexture());
			canvas.clear(0, 0, 0, 0);
			for (auto& connection: connections) {
				auto x1 = connection.x1 - visualizationScrollX;
				auto y1 = connection.y1 - visualizationScrollY;
				auto x2 = connection.x2 - visualizationScrollX;
				auto y2 = connection.y2 - visualizationScrollY;

				if ((x1 < 0 && x2 < 0) ||
					(x1 > visualizationWidth && x2 > visualizationWidth) ||
					(y1 < 0 && y2 < 0) ||
					(y1 > visualizationHeight && y2 > visualizationHeight)) continue;

				auto STRAIGHTLINE_LENGTH = 50.0f;
				Vector2 srcVector1(x1, y1);
				Vector2 srcVector2(x1 + (x2 < x1?-STRAIGHTLINE_LENGTH:STRAIGHTLINE_LENGTH), y1);
				Vector2 dstVector1(x1 + (x2 < x1?-STRAIGHTLINE_LENGTH:STRAIGHTLINE_LENGTH), y2 - (y2 < y1?-STRAIGHTLINE_LENGTH:STRAIGHTLINE_LENGTH));
				Vector2 dstVector2(x2, y2);
				vector<Vector2> controlPoints;
				controlPoints.push_back(srcVector1);
				controlPoints.push_back(srcVector2);
				controlPoints.push_back(dstVector1);
				controlPoints.push_back(dstVector2);
				switch (connection.type) {
					case Connection::CONNECTIONTYPE_FLOW:
						canvas.drawBezier(controlPoints, 255, 255, 255, 255);
						break;
					case Connection::CONNECTIONTYPE_ARGUMENT:
						canvas.drawBezier(controlPoints, 0, 255, 0, 255);
						break;
				}
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
	} catch (Exception& exception) {
		Console::print(string("TextEditorTabView::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	// TODO: load settings
}

void TextEditorTabView::dispose()
{
	required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController())->removeChangeListener(textNodeChangeListener);
	engine->dispose();
}

void TextEditorTabView::updateRendering() {
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
}

void TextEditorTabView::reloadOutliner() {
	textEditorTabController->setOutlinerContent();
	editorView->getScreenController()->setDetailsContent(string());
}

void TextEditorTabView::setVisualEditor() {
	auto editorNode = dynamic_cast<GUIElementNode*>(engine->getGUI()->getScreen(tabScreenNode->getId())->getNodeById("editor"));
	if (editorNode != nullptr) editorNode->getActiveConditions().set("visualization");
	visualEditor = true;
}

void TextEditorTabView::setCodeEditor() {
	auto editorNode = dynamic_cast<GUIElementNode*>(engine->getGUI()->getScreen(tabScreenNode->getId())->getNodeById("editor"));
	if (editorNode != nullptr) editorNode->getActiveConditions().set("text");
	visualEditor = false;
}

void TextEditorTabView::addNodeDeltaX(const string& id, const MiniScript::StatementDescription& description, GUIParentNode* parentNode, int deltaX) {
	auto node = required_dynamic_cast<GUIParentNode*>(tabScreenNode->getNodeById("d" + id));
	node->getRequestsConstraints().left+= deltaX;
	for (auto i = 0; i < description.arguments.size(); i++) {
		addNodeDeltaX(id + "." + to_string(i), description.arguments[i], parentNode, deltaX);
	}
}

void TextEditorTabView::createNodes(const string& id, int descriptionIdx, int descriptionCount, const MiniScript::StatementDescription& description, GUIParentNode* parentNode, int x, int y, int& width, int& height, int depth) {
	//
	int childMaxWidth = 0;
	for (auto argumentIdx = 0; argumentIdx < description.arguments.size(); argumentIdx++) {
		//
		auto isLiteral = description.arguments[argumentIdx].type == MiniScript::StatementDescription::STATEMENTDESCRIPTION_LITERAL;
		if (isLiteral == true) continue;
		//
		auto childWidth = 0;
		auto childHeight = 0;
		createNodes(id + "." + to_string(argumentIdx), argumentIdx, description.arguments.size(), description.arguments[argumentIdx], parentNode, x, y, childWidth, childHeight, depth + 1);
		if (childWidth > childMaxWidth) childMaxWidth = childWidth;
		y+= childHeight;
		height+= childHeight;
	}
	//
	x+= childMaxWidth;
	width+= childMaxWidth;

	//input2_pin_type_panel.condition=connected

	//
	switch (description.type) {
		case MiniScript::StatementDescription::STATEMENTDESCRIPTION_EXECUTE_METHOD:
		case MiniScript::StatementDescription::STATEMENTDESCRIPTION_EXECUTE_FUNCTION:
			{
				{
					string xml = "<template src='resources/engine/gui/template_visualcode_node.xml' id='d" + id + "' left='" + to_string(x) + "' top='" + to_string(y) + "' node-name='" + GUIParser::escapeQuotes(description.value.getValueString()) + "' />";
					try {
						GUIParser::parse(parentNode, xml);
					} catch (Exception& exception) {
						Console::println("TextEditorTabView::visualizeDescription(): method/function: " + string(exception.what()));
					}
				}
				//
				auto nodeInputContainer = required_dynamic_cast<GUIParentNode*>(tabScreenNode->getNodeById("d" + id + "_input_container"));
				auto nodeOutputContainer = required_dynamic_cast<GUIParentNode*>(tabScreenNode->getNodeById("d" + id + "_output_container"));
				// pin input aka flow input
				if (depth == 0 && descriptionIdx > 0) {
					string xml;
					//
					xml+=
						string() +
						"<template " +
						"	id='d" + id + "_flow_in' " +
						"	src='resources/engine/gui/template_visualcode_input.xml' " +
						"	pin_type_connected='resources/engine/images/visualcode_flow_connected.png' " +
						"	pin_type_unconnected='resources/engine/images/visualcode_flow_unconnected.png' " +
						"/>";
					//
					try {
						GUIParser::parse(nodeInputContainer, xml);
						// update to be connected
						required_dynamic_cast<GUIElementNode*>(tabScreenNode->getNodeById("d" + id + "_flow_in_pin_type_panel"))->getActiveConditions().add("connected");
					} catch (Exception& exception) {
						Console::println("TextEditorTabView::visualizeDescription(): method/function: " + string(exception.what()));
					}
				}
				// inputs aka arguments
				{
					//
					auto argumentIdx = 0;
					if (description.method != nullptr) {
						auto& argumentTypes = description.method->getArgumentTypes();
						for (argumentIdx = 0; argumentIdx < argumentTypes.size(); argumentIdx++) {
							//
							auto isLiteral = description.arguments[argumentIdx].type == MiniScript::StatementDescription::STATEMENTDESCRIPTION_LITERAL;
							auto literal = isLiteral == true?description.arguments[argumentIdx].value.getValueString():string();
							//
							string xml =
								string() +
								"<template " +
								"	id='d" + id + "_a" + to_string(argumentIdx) + "' " +
								"	src='resources/engine/gui/template_visualcode_input.xml' " +
								"	pin_type_connected='resources/engine/images/visualcode_value_connected.png' " +
								"	pin_type_unconnected='resources/engine/images/visualcode_value_unconnected.png' " +
								"	pin_color='{$color.pintype_integer}' " +
								"	text='" + GUIParser::escapeQuotes(argumentTypes[argumentIdx].name + ": " + MiniScript::ScriptVariable::getTypeAsString(argumentTypes[argumentIdx].type)) + "' ";
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
									required_dynamic_cast<GUIElementNode*>(tabScreenNode->getNodeById("d" + id + "_a" + to_string(argumentIdx) + "_input_type_panel"))->getActiveConditions().add("input");
								} else {
									// update to be connected
									required_dynamic_cast<GUIElementNode*>(tabScreenNode->getNodeById("d" + id + "_a" + to_string(argumentIdx) + "_pin_type_panel"))->getActiveConditions().add("connected");
								}

							} catch (Exception& exception) {
								Console::println("TextEditorTabView::visualizeDescription(): method/function: " + string(exception.what()));
							}
						}
					}
					for (; argumentIdx < description.arguments.size(); argumentIdx++) {
						//
						auto isLiteral = description.arguments[argumentIdx].type == MiniScript::StatementDescription::STATEMENTDESCRIPTION_LITERAL;
						auto literal = isLiteral == true?description.arguments[argumentIdx].value.getValueString():string();
						//
						string xml =
							string() +
							"<template " +
							"	id='d" + id + "_a" + to_string(argumentIdx) + "' " +
							"	src='resources/engine/gui/template_visualcode_input.xml' " +
							"	pin_type_connected='resources/engine/images/visualcode_value_connected.png' " +
							"	pin_type_unconnected='resources/engine/images/visualcode_value_unconnected.png' " +
							"	pin_color='{$color.pintype_integer}' " +
							"	text='Argument " + to_string(argumentIdx) + "' ";
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
								required_dynamic_cast<GUIElementNode*>(tabScreenNode->getNodeById("d" + id + "_a" + to_string(argumentIdx) + "_input_type_panel"))->getActiveConditions().add("input");
							} else {
								// update to be connected
								required_dynamic_cast<GUIElementNode*>(tabScreenNode->getNodeById("d" + id + "_a" + to_string(argumentIdx) + "_pin_type_panel"))->getActiveConditions().add("connected");
							}
						} catch (Exception& exception) {
							Console::println("TextEditorTabView::visualizeDescription(): method/function: " + string(exception.what()));
						}
					}
				}
				// pin output aka flow output
				if (depth == 0 && descriptionIdx < descriptionCount - 1) {
					string xml;
					//
					xml+=
						string() +
						"<template " +
						"	id='d" + id + "_flow_out' " +
						"	src='resources/engine/gui/template_visualcode_output.xml' " +
						"	pin_type_connected='resources/engine/images/visualcode_flow_connected.png' " +
						"	pin_type_unconnected='resources/engine/images/visualcode_flow_unconnected.png' " +
						"/>";
					//
					try {
						GUIParser::parse(nodeOutputContainer, xml);
						// update to be connected
						required_dynamic_cast<GUIElementNode*>(tabScreenNode->getNodeById("d" + id + "_flow_out_pin_type_panel"))->getActiveConditions().add("connected");
					} catch (Exception& exception) {
						Console::println("TextEditorTabView::visualizeDescription(): method/function: " + string(exception.what()));
					}
				}
				// return value
				if (description.method != nullptr && description.method->getReturnValueType() != MiniScript::ScriptVariableType::TYPE_VOID) {
					string xml;
					//
					xml+=
						string() +
						"<template " +
						"	id='d" + id + "_r' " +
						"	src='resources/engine/gui/template_visualcode_output.xml' " +
						"	pin_type_connected='resources/engine/images/visualcode_value_connected.png' " +
						"	pin_type_unconnected='resources/engine/images/visualcode_value_unconnected.png' " +
						"	pin_color='{$color.pintype_integer}' " +
						"	text='Return Value' " +
						"/>";
					//
					try {
						GUIParser::parse(nodeOutputContainer, xml);
						// update to be connected
						required_dynamic_cast<GUIElementNode*>(tabScreenNode->getNodeById("d" + id + "_r_pin_type_panel"))->getActiveConditions().add("connected");
					} catch (Exception& exception) {
						Console::println("TextEditorTabView::visualizeDescription(): method/function: " + string(exception.what()));
					}
				}
				break;
			}
		case MiniScript::StatementDescription::STATEMENTDESCRIPTION_LITERAL:
			{
				{
					string xml = "<template src='resources/engine/gui/template_visualcode_node.xml' id='d" + id + "' left='" + to_string(x) + "' top='" + to_string(y) + "' node-name='Literal' />";
					try {
						GUIParser::parse(parentNode, xml);
					} catch (Exception& exception) {
						Console::println("TextEditorTabView::visualizeDescription(): literal: " + string(exception.what()));
					}
				}
				{
					string xml =
						string() +
						"<template " +
							"id='d" + id + "_r' " +
							"src='resources/engine/gui/template_visualcode_output.xml' " +
							"pin_type_connected='resources/engine/images/visualcode_value_connected.png' " +
							"pin_type_unconnected='resources/engine/images/visualcode_value_unconnected.png' " +
							"pin_color='{$color.pintype_integer}' " +
							"text='" + GUIParser::escapeQuotes(description.value.getValueString()) + "' " +
						"/>";

					try {
						GUIParser::parse(required_dynamic_cast<GUIParentNode*>(tabScreenNode->getNodeById("d" + id + "_output_container")), xml);
						// update to be connected
						required_dynamic_cast<GUIElementNode*>(tabScreenNode->getNodeById("d" + id + "_r_pin_type_panel"))->getActiveConditions().add("connected");
					} catch (Exception& exception) {
						Console::println("TextEditorTabView::visualizeDescription(): literal: " + string(exception.what()));
					}
				}
				break;
			}
	}

	//
	auto node = required_dynamic_cast<GUINode*>(tabScreenNode->getNodeById("d" + id));
	width+= 400; //node->getContentWidth();
	height+= 200; //node->getContentHeight();

	// post layout, move first level child argument nodes from from left to right according to the closest one
	auto rootDistanceMax = Integer::MAX_VALUE;
	auto nextLevelXBestFit = -1;
	for (auto argumentIdx = 0; argumentIdx < description.arguments.size(); argumentIdx++) {
		//
		auto isLiteral = description.arguments[argumentIdx].type == MiniScript::StatementDescription::STATEMENTDESCRIPTION_LITERAL;
		if (isLiteral == true) continue;
		//
		auto nextLevelNode = required_dynamic_cast<GUINode*>(tabScreenNode->getNodeById("d" + id + "." + to_string(argumentIdx)));
		auto nodeXPosition = nextLevelNode->getRequestsConstraints().left;
		auto rootDistance = Math::abs(x - nodeXPosition);
		if (rootDistance < rootDistanceMax) {
			rootDistanceMax = rootDistance;
			nextLevelXBestFit = nodeXPosition;
		}
	}
	for (auto argumentIdx = 0; argumentIdx < description.arguments.size(); argumentIdx++) {
		//
		auto isLiteral = description.arguments[argumentIdx].type == MiniScript::StatementDescription::STATEMENTDESCRIPTION_LITERAL;
		if (isLiteral == true) continue;
		//
		auto subNodeId = id + "." + to_string(argumentIdx);
		auto nextLevelNode = required_dynamic_cast<GUINode*>(tabScreenNode->getNodeById("d" + id + "." + to_string(argumentIdx)));
		auto nodeXPosition = nextLevelNode->getRequestsConstraints().left;
		auto deltaX = nextLevelXBestFit - nodeXPosition;
		if (deltaX == 0) continue;
		addNodeDeltaX(subNodeId, description.arguments[argumentIdx], parentNode, deltaX);
	}
}

void TextEditorTabView::updateMiniScriptDescription(int miniScriptScriptIdx) {
	required_dynamic_cast<GUIParentNode*>(tabScreenNode->getNodeById("visualization_canvas"))->clearSubNodes();
	//
	this->miniScriptScriptIdx = miniScriptScriptIdx;
	auto& description = textEditorTabController->getMiniScriptDescription()[miniScriptScriptIdx].description;
	auto visualisationNode = required_dynamic_cast<GUIParentNode*>(tabScreenNode->getNodeById("visualization_canvas"));
	auto x = 200;
	auto y = 200;
	auto yMax = y;
	for (auto i = 0; i < description.size(); i++) {
		auto width = 0;
		auto height = 0;
		createNodes(to_string(i), i, description.size(), description[i], visualisationNode, x, y, width, height);
		x+= width + 100;
		yMax = Math::max(y + height, yMax);
	}
	// TODO: with absolute align of nodes content width/height is not yet computed in UI
	visualisationNode->getComputedConstraints().width = x;
	visualisationNode->getComputedConstraints().height = yMax;
	visualisationNode->getRequestsConstraints().width = x;
	visualisationNode->getRequestsConstraints().height = yMax;
	// Bug: Work around! Sometimes layouting is not issued! Need to check!
	tabScreenNode->forceInvalidateLayout(tabScreenNode);

	//
	createConnectionsPasses = 3;
}

void TextEditorTabView::createConnections(const string& id, const MiniScript::StatementDescription& description, GUIParentNode* parentNode) {
	auto node = required_dynamic_cast<GUINode*>(tabScreenNode->getNodeById("d" + id));
	auto& computedConstraints = node->getComputedConstraints();
	nodes.push_back(
		{
			.x1 = computedConstraints.left,
			.y1 = computedConstraints.top,
			.x2 = computedConstraints.left + computedConstraints.width,
			.y2 = computedConstraints.top + computedConstraints.height,
		}
	);
	for (auto argumentIdx = 0; argumentIdx < description.arguments.size(); argumentIdx++) {
		//
		auto isLiteral = description.arguments[argumentIdx].type == MiniScript::StatementDescription::STATEMENTDESCRIPTION_LITERAL;
		if (isLiteral == true) continue;
		//
		auto argumentInputNode = required_dynamic_cast<GUINode*>(tabScreenNode->getNodeById("d" + id + "_a" + to_string(argumentIdx)));
		auto argumentOutputNode = required_dynamic_cast<GUINode*>(tabScreenNode->getNodeById("d" + id + "." + to_string(argumentIdx) + "_r"));
		auto& argumentInputNodeComputedConstraints = argumentInputNode->getComputedConstraints();
		auto& argumentOutputNodeComputedConstraints = argumentOutputNode->getComputedConstraints();
		connections.push_back(
			{
				.type = Connection::CONNECTIONTYPE_ARGUMENT,
				.x1 = argumentInputNodeComputedConstraints.left,
				.y1 = argumentInputNodeComputedConstraints.top + argumentInputNodeComputedConstraints.height / 2,
				.x2 = argumentOutputNodeComputedConstraints.left + argumentOutputNodeComputedConstraints.width,
				.y2 = argumentOutputNodeComputedConstraints.top + argumentOutputNodeComputedConstraints.height / 2,
			}
		);
		createConnections(id + "." + to_string(argumentIdx), description.arguments[argumentIdx], parentNode);
	}
}

void TextEditorTabView::createConnections() {
	// reset
	nodes.clear();
	connections.clear();

	//
	if (miniScriptScriptIdx >= textEditorTabController->getMiniScriptDescription().size()) return;
	auto& description = textEditorTabController->getMiniScriptDescription()[miniScriptScriptIdx].description;
	GUINode* previousNodeFlowNode = nullptr;
	auto visualisationNode = required_dynamic_cast<GUIParentNode*>(tabScreenNode->getNodeById("visualization_canvas"));
	for (auto i = 0; i < description.size(); i++) {
		createConnections(to_string(i), description[i], visualisationNode);
		auto nodeFlowIn = dynamic_cast<GUINode*>(tabScreenNode->getNodeById("d" + to_string(i) + "_flow_in"));
		auto nodeFlowOut = dynamic_cast<GUINode*>(tabScreenNode->getNodeById("d" + to_string(i) + "_flow_out"));
		if (previousNodeFlowNode != nullptr && nodeFlowIn != nullptr) {
			auto& previousNodeComputedConstraints = previousNodeFlowNode->getComputedConstraints();
			auto& nodeComputedConstraints = nodeFlowIn->getComputedConstraints();
			connections.push_back(
				{
					.type = Connection::CONNECTIONTYPE_FLOW,
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
}
