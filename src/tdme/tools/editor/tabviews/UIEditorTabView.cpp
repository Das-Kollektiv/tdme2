#include <tdme/tools/editor/tabviews/UIEditorTabView.h>

#include <algorithm>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/model/Face.h>
#include <tdme/engine/model/FacesEntity.h>
#include <tdme/engine/model/Material.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/model/PBRMaterialProperties.h>
#include <tdme/engine/model/SpecularMaterialProperties.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/FrameBuffer.h>
#include <tdme/engine/Object.h>
#include <tdme/engine/SimplePartition.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIImageNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUIStyledTextNode.h>
#include <tdme/gui/nodes/GUIStyledTextNodeController.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/ContextMenuScreenController.h>
#include <tdme/tools/editor/misc/CameraRotationInputHandler.h>
#include <tdme/tools/editor/misc/TextFormatter.h>
#include <tdme/tools/editor/misc/TextTools.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/UIEditorTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Character.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/StringTools.h>

using std::make_unique;
using std::sort;
using std::string;
using std::unique_ptr;
using std::unordered_set;
using std::vector;

using tdme::tools::editor::tabviews::UIEditorTabView;

using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::Color4;
using tdme::engine::model::Face;
using tdme::engine::model::FacesEntity;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::model::PBRMaterialProperties;
using tdme::engine::model::SpecularMaterialProperties;
using tdme::engine::prototype::Prototype;
using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::engine::Object;
using tdme::engine::SimplePartition;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIImageNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUIStyledTextNode;
using tdme::gui::nodes::GUIStyledTextNodeController;
using tdme::gui::GUI;
using tdme::gui::GUIParser;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::ContextMenuScreenController;
using tdme::tools::editor::misc::CameraInputHandler;
using tdme::tools::editor::misc::TextFormatter;
using tdme::tools::editor::misc::TextTools;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::UIEditorTabController;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Character;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::StringTools;

UIEditorTabView::UIEditorTabView(EditorView* editorView, const string& tabId, GUIScreenNode* screenNode, const string& fileName)
{
	this->editorView = editorView;
	this->tabId = tabId;
	this->screenNode = screenNode;
	this->popUps = editorView->getPopUps();
	this->screenFileName = fileName;
	guiEngine = unique_ptr<Engine>(Engine::createOffScreenInstance(1920, 1080, false, false, false));
	guiEngine->setSceneColor(Color4(39.0f / 255.0f, 39.0f / 255.0f, 39.0f / 255.0f, 1.0f));
	outlinerState.expandedOutlinerParentOptionValues.push_back("0.0");
}

UIEditorTabView::~UIEditorTabView() {
}

void UIEditorTabView::onCameraRotation() {
	// no op
}

void UIEditorTabView::onCameraScale() {
	// no op
}

void UIEditorTabView::handleInputEvents()
{
	if (visualEditor == false && projectedUi == true) {
		// mouse wheel events that happened to route to GUI engine
		vector<int> checkedGUIEngineMouseEventIndices;
		vector<int> checkedEngineMouseEventIndices;
		vector<int> unusedEngineMouseEventIndices;
		//
		auto modelEntity = dynamic_cast<Object*>(engine->getEntity("model"));
		if (modelEntity != nullptr && modelMeshNode.empty() == false && modelEntity->getModel()->getNodeById(modelMeshNode) != nullptr) {
			auto modelEntityWorldMatrix = modelEntity->getNodeTransformMatrix(modelMeshNode);
			auto modelEntityModelImportMatrixInverted = modelEntity->getModel()->getImportTransformMatrix().clone().invert();
			auto modelEntityWorldMatrixInverted = modelEntityWorldMatrix.clone().multiply(modelEntity->getTransformMatrix()).multiply(modelEntityModelImportMatrixInverted).invert();
			// handle mouse events
			const auto& engineMouseEvents = engine->getGUI()->getMouseEvents();
			auto& guiEngineMouseEvents = guiEngine->getGUI()->getMouseEvents();
			auto mouseEventIdx = 0;
			for (const auto& event: engine->getGUI()->getMouseEvents()) {
				if (event.isProcessed() == true) {
					mouseEventIdx++;
					continue;
				}
				// try to push event to gui engine if in book space
				Vector3 mouseWorldCoordinate = engine->computeWorldCoordinateByMousePosition(event.getXUnscaled(), event.getYUnscaled());
				auto bookLocalCoordinate = modelEntityWorldMatrixInverted.multiply(mouseWorldCoordinate);
				auto clonedEvent = event;
				clonedEvent.setX((bookLocalCoordinate.getX() - projectedUiMinX) * (guiEngine->getWidth() / (projectedUiMaxX - projectedUiMinX)));
				clonedEvent.setY((bookLocalCoordinate.getZ() - projectedUiMinZ) * (guiEngine->getHeight() / (projectedUiMaxZ - projectedUiMinZ)));
				clonedEvent.setXUnscaled(clonedEvent.getX());
				clonedEvent.setYUnscaled(clonedEvent.getY());
				if (clonedEvent.getX() >= 0 && clonedEvent.getX() < guiEngine->getWidth() &&
					clonedEvent.getY() >= 0 && clonedEvent.getY() < guiEngine->getHeight()) {
					checkedGUIEngineMouseEventIndices.push_back(guiEngineMouseEvents.size());
					guiEngineMouseEvents.push_back(clonedEvent);
					// ok we add this mouse event to our checked mouse event indices list
					checkedEngineMouseEventIndices.push_back(mouseEventIdx);
				} else {
					// ok add this to unused mouse event indices list
					unusedEngineMouseEventIndices.push_back(mouseEventIdx);
				}
				mouseEventIdx++;
			}
		} else {
			// just add all events into unused mouse event indices
			const auto& engineMouseEvents = engine->getGUI()->getMouseEvents();
			for (auto i = 0; i < engineMouseEvents.size(); i++) unusedEngineMouseEventIndices.push_back(i);
		}
		// handle GUI engine events
		guiEngine->getGUI()->handleEvents(false);
		// clear mouse events of main engine
		auto engineMouseEvents = engine->getGUI()->getMouseEvents();
		const auto& guiEngineMouseEvents = guiEngine->getGUI()->getMouseEvents();
		engine->getGUI()->getMouseEvents().clear();
		// TODO: we might want to sort the events by creation time or id
		// restore mouse events of main engine from GUI engine events
		for (auto i = 0; i < checkedEngineMouseEventIndices.size(); i++) {
			if (guiEngineMouseEvents[checkedGUIEngineMouseEventIndices[i]].isProcessed() == false) engine->getGUI()->getMouseEvents().push_back(engineMouseEvents[checkedEngineMouseEventIndices[i]]);
		}
		for (auto i = 0; i < unusedEngineMouseEventIndices.size(); i++) {
			engine->getGUI()->getMouseEvents().push_back(engineMouseEvents[unusedEngineMouseEventIndices[i]]);
		}
		// clear GUI engine events, as we did not do this before after handing events
		guiEngine->getGUI()->getKeyboardEvents().clear();
		guiEngine->getGUI()->getMouseEvents().clear();
		// camera rotation input handler, which uses main engine events
		cameraRotationInputHandler->handleInputEvents();
		// clear main engine events
		engine->getGUI()->getMouseEvents().clear();
		engine->getGUI()->getKeyboardEvents().clear();
	} else {
		// just handle events from GUI engine
		guiEngine->getGUI()->handleEvents();
	}
}

void UIEditorTabView::display()
{

	guiEngine->display();
	guiEngine->getGUI()->render();
	if (projectedUi == true) engine->display();
}

void UIEditorTabView::initialize()
{
	try {
		uiTabController = make_unique<UIEditorTabController>(this);
		uiTabController->initialize(editorView->getScreenController()->getScreenNode());
	} catch (Exception& exception) {
		Console::println("UIEditorTabView::initialize(): An error occurred: " + string(exception.what()));
	}
	// TODO: load settings

	//
	textNode = required_dynamic_cast<GUIStyledTextNode*>(screenNode->getInnerNodeById(tabId + "_tab_text"));

	// initial text format
	TextFormatter::getInstance()->format("xml", textNode);
	// load code completion
	codeCompletion = TextFormatter::getInstance()->loadCodeCompletion("xml");

	//
	{
		// add text node change listener
		class TextChangeListener: public GUIStyledTextNodeController::ChangeListener {
		public:
			TextChangeListener(UIEditorTabView* uiEditorTabView): uiEditorTabView(uiEditorTabView) {
			}

			virtual ~TextChangeListener() {
			}

			virtual void onRemoveText(int idx, int count) override {
				if (uiEditorTabView->countEnabled == true) {
					TextFormatter::getInstance()->format("xml", uiEditorTabView->textNode, 0, uiEditorTabView->textNode->getText().size());
					uiEditorTabView->countEnabled = false;
				} else {
					TextFormatter::getInstance()->format("xml", uiEditorTabView->textNode, idx, idx + count);
				}
			}
			virtual void onInsertText(int idx, int count) override {
				if (uiEditorTabView->countEnabled == true) {
					TextFormatter::getInstance()->format("xml", uiEditorTabView->textNode, 0, uiEditorTabView->textNode->getText().size());
					uiEditorTabView->countEnabled = false;
				} else {
					TextFormatter::getInstance()->format("xml", uiEditorTabView->textNode, idx, idx + count);
				}
			}
		private:
			UIEditorTabView* uiEditorTabView;
		};
		//
		required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController())->addChangeListener((textNodeChangeListener = make_unique<TextChangeListener>(this)).get());
	}

	//
	{
		// add code completion listener
		class TextCodeCompletionListener: public GUIStyledTextNodeController::CodeCompletionListener {
		public:
			TextCodeCompletionListener(UIEditorTabView* uiEditorTabView): uiEditorTabView(uiEditorTabView) {
			}

			virtual ~TextCodeCompletionListener() {
			}

			virtual void onCodeCompletion(int idx) override {
				auto codeCompletion = uiEditorTabView->codeCompletion;
				if (codeCompletion == nullptr) return;
				if (codeCompletion->delimiters.find(uiEditorTabView->textNode->getText().getCharAt(idx)) != string::npos) {
					if (idx > 0) idx--;
				}
				auto previousDelimiterPos = uiEditorTabView->textNode->getPreviousDelimiter(idx, codeCompletion->delimiters);
				string search = StringTools::substring(uiEditorTabView->textNode->getText().getString(), previousDelimiterPos == 0?0:previousDelimiterPos + 1, idx);
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
				auto popUps = uiEditorTabView->getPopUps();
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
						class OnCodeCompletionAction: public virtual Action
						{
						public:
							OnCodeCompletionAction(UIEditorTabView* uiEditorTabView, int idx, const CodeCompletionSymbol& symbol): uiEditorTabView(uiEditorTabView), idx(idx), symbol(symbol) {}
							void performAction() override {
								if (symbol.name.empty() == true) return;
								auto codeCompletion = uiEditorTabView->codeCompletion;
								if (codeCompletion == nullptr) return;
								auto previousDelimiterPos = uiEditorTabView->textNode->getPreviousDelimiter(idx, codeCompletion->delimiters);
								auto nextDelimiterPos = uiEditorTabView->textNode->getNextDelimiter(idx, codeCompletion->delimiters);
								auto withoutWhiteSpaceDelimiters = codeCompletion->delimiters;
								if (withoutWhiteSpaceDelimiters.find(' ') != string::npos) withoutWhiteSpaceDelimiters.erase(withoutWhiteSpaceDelimiters.find(' '), 1);
								if (withoutWhiteSpaceDelimiters.find('\t') != string::npos) withoutWhiteSpaceDelimiters.erase(withoutWhiteSpaceDelimiters.find('\t'), 1);
								if (withoutWhiteSpaceDelimiters.find('\n') != string::npos) withoutWhiteSpaceDelimiters.erase(withoutWhiteSpaceDelimiters.find('\n'), 1);
								auto nextDelimiterPos2 = uiEditorTabView->textNode->getNextDelimiter(idx, withoutWhiteSpaceDelimiters);
								auto idxToDelimiterString = StringTools::trim(StringTools::substring(uiEditorTabView->textNode->getText().getString(), idx + 1 < uiEditorTabView->textNode->getTextLength()?idx + 1:idx, nextDelimiterPos2));
								string parameterString;
								if (symbol.type == CodeCompletionSymbol::TYPE_FUNCTION && uiEditorTabView->textNode->getText().getCharAt(nextDelimiterPos2) != '(') {
									for (const auto& parameter: symbol.parameters) {
										auto parameterTokenized = StringTools::tokenize(parameter, " \t\n");
										if (parameterString.empty() == false) parameterString+= ", ";
										parameterString+= parameterTokenized[parameterTokenized.size() - 1];
									}
									parameterString = "(" + parameterString + ")"/* + codeCompletion->statementDelimiter*/;
								}
								uiEditorTabView->textNode->removeText(previousDelimiterPos == 0?0:previousDelimiterPos + 1, nextDelimiterPos - (previousDelimiterPos == 0?0:previousDelimiterPos + 1));
								uiEditorTabView->textNode->insertText(previousDelimiterPos == 0?0:previousDelimiterPos + 1, symbol.name + parameterString);
								TextFormatter::getInstance()->format("xml", uiEditorTabView->textNode, previousDelimiterPos == 0?0:previousDelimiterPos + 1, (previousDelimiterPos == 0?0:previousDelimiterPos + 1) + symbol.name.size() + parameterString.size());
							}
						private:
							UIEditorTabView* uiEditorTabView;
							int idx;
							CodeCompletionSymbol symbol;
						};
						popUps->getContextMenuScreenController()->addMenuItem(codeCompletionSymbolCandidate.display, "contextmenu_codecompletion_" + to_string(i), new OnCodeCompletionAction(uiEditorTabView, idx, codeCompletionSymbolCandidate));
						//
						i++;
					}
				}
				if (codeCompletionSymbolCandidates.empty() == false) {
					//
					int left, top, width, height, offsetX, offsetY;
					auto selectedTab = uiEditorTabView->getEditorView()->getScreenController()->getSelectedTab();
					if (selectedTab != nullptr) {
						uiEditorTabView->getEditorView()->getViewPort(selectedTab->getFrameBufferNode(), left, top, width, height, offsetX, offsetY);
						popUps->getContextMenuScreenController()->show(
							left + uiEditorTabView->textNode->getIndexPositionX() - uiEditorTabView->textNode->computeParentChildrenRenderOffsetXTotal(),
							top + uiEditorTabView->textNode->getIndexPositionY() - uiEditorTabView->textNode->computeParentChildrenRenderOffsetYTotal()
						);
					}
				}
			}
		private:
			UIEditorTabView* uiEditorTabView;
		};
		//
		required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController())->addCodeCompletionListener((textNodeCodeCompletionListener = make_unique<TextCodeCompletionListener>(this)).get());
	}
	//
	addScreen();
	setScreen(0, screenFileName);
	//
	updateCodeEditor();
	//
	setVisualEditor();
}

void UIEditorTabView::dispose()
{
	uiTabController->closeFindReplaceWindow();
	guiEngine->dispose();
	if (engine != nullptr) engine->dispose();
}

void UIEditorTabView::updateRendering() {
}

inline bool UIEditorTabView::hasFixedSize() {
	return projectedUi == false && visualEditor == true;
}

Engine* UIEditorTabView::getEngine() {
	if (visualEditor == false) return nullptr;
	return projectedUi == true?engine.get():guiEngine.get();
}

void UIEditorTabView::activate() {
	uiTabController->setOutlinerAddDropDownContent();
	uiTabController->setOutlinerContent();
	editorView->getScreenController()->restoreOutlinerState(outlinerState);
	editorView->getScreenController()->setDetailsContent(string());
}

void UIEditorTabView::deactivate() {
	editorView->getScreenController()->storeOutlinerState(outlinerState);
	uiTabController->closeFindReplaceWindow();
}

void UIEditorTabView::reloadOutliner() {
	uiTabController->setOutlinerContent();
	editorView->getScreenController()->setDetailsContent(string());
}

void UIEditorTabView::addScreen() {
	uiScreenNodes.push_back(
		{
			.fileName = string(),
			.xml = string(),
			.screenNode = nullptr,
			.width = -1,
			.height = -1
		}
	);
}

void UIEditorTabView::setScreen(int screenIdx, const string& fileName) {
	//
	if (screenIdx < 0 || screenIdx >= uiScreenNodes.size()) return;
	//
	this->screenIdx = screenIdx;
	//
	string xml;
	try {
		// parse XML
		xml = FileSystem::getInstance()->getContentAsString(
			Tools::getPathName(fileName),
			Tools::getFileName(fileName)
		);
	} catch (Exception& exception) {
		Console::println("UIEditorTabView::setScreen(): an error occurred: " + screenNode->getFileName() + ": " + string(exception.what()));
	}
	//
	uiScreenNodes[screenIdx].fileName = fileName;
	uiScreenNodes[screenIdx].xml = xml;
	uiScreenNodes[screenIdx].screenNode = nullptr;
	uiScreenNodes[screenIdx].width = -1;
	uiScreenNodes[screenIdx].height = -1;
	//
	if (visualEditor == true) reAddScreens();
	//
	updateCodeEditor();
}

void UIEditorTabView::unsetScreen(int screenIdx) {
	if (screenIdx < 0 || screenIdx >= uiScreenNodes.size()) return;
	if (uiScreenNodes[screenIdx].screenNode != nullptr) {
		uiScreenNodes[screenIdx].screenNode->removeTooltipRequestListener(uiTabController.get());
		guiEngine->getGUI()->removeScreen(uiScreenNodes[screenIdx].screenNode->getId());
	}
	uiScreenNodes[screenIdx].fileName.clear();
	uiScreenNodes[screenIdx].xml.clear();
	uiScreenNodes[screenIdx].screenNode = nullptr;
	uiScreenNodes[screenIdx].width = -1;
	uiScreenNodes[screenIdx].height = -1;
}

void UIEditorTabView::removeScreen(int screenIdx) {
	if (screenIdx < 0 || screenIdx >= uiScreenNodes.size()) return;
	if (uiScreenNodes[screenIdx].screenNode != nullptr) {
		uiScreenNodes[screenIdx].screenNode->removeTooltipRequestListener(uiTabController.get());
	}
	guiEngine->getGUI()->removeScreen(uiScreenNodes[screenIdx].screenNode->getId());
	uiScreenNodes.erase(uiScreenNodes.begin() + screenIdx);
}

void UIEditorTabView::removeScreens() {
	guiEngine->getGUI()->resetRenderScreens();
}

void UIEditorTabView::reAddScreens() {
	guiEngine->getGUI()->reset();
	auto screensMaxWidth = -1;
	auto screensMaxHeight = -1;
	for (auto i = 0; i < uiScreenNodes.size(); i++) {
		//
		uiScreenNodes[i].screenNode = nullptr;

		//
		if (uiScreenNodes[i].xml.empty() == true) continue;

		// fetch root node
		GUIScreenNode* screenNode = nullptr;
		string xmlRootNode;
		try {
			xmlRootNode = GUIParser::getRootNode(uiScreenNodes[i].xml);
		} catch (Exception& exception) {
			Console::println("UIEditorTabView::reAddScreens(): an error occurred: " + string(exception.what()));
			// error handling
			try {
				screenNode = GUIParser::parse(
					"resources/engine/gui/",
					"screen_text.xml",
					{{ "text", StringTools::replace(StringTools::replace("An error occurred: " + string(exception.what()), "[", "\\["), "]", "\\]") }}
				);
			} catch (Exception& exception2) {
				Console::println("UIEditorTabView::reAddScreens(): an error occurred: " + string(exception2.what()));
			}
		}
		if (xmlRootNode == "screen") {
			//
			try {
				screenNode = GUIParser::parse(
					uiScreenNodes[i].xml,
					{},
					Tools::getPathName(uiScreenNodes[i].fileName),
					Tools::getFileName(uiScreenNodes[i].fileName)
				);
			} catch (Exception& exception) {
				Console::println("UIEditorTabView::reAddScreens(): an error occurred: " + string(exception.what()));
				// error handling
				try {
					screenNode = GUIParser::parse(
						"resources/engine/gui/",
						"screen_text.xml",
						{{ "text", StringTools::replace(StringTools::replace("An error occurred: " + string(exception.what()), "[", "\\["), "]", "\\]") }}
					);
				} catch (Exception& exception2) {
					Console::println("UIEditorTabView::reAddScreens(): an error occurred: " + string(exception2.what()));
				}
			}
		} else
		if (xmlRootNode == "template") {
			/*
				<!-- You can now specify default preview attributes within templates -->
				<defaults>
					<attribute name="preview-id" value="sound-preview" />
					<attribute name="preview-container-width" value="300" />
					<attribute name="preview-container-height" value="400" />
				</defaults>
			 */
			unordered_map<string, string> templateAttributes;
			//
			try {
				templateAttributes = GUIParser::parseTemplateAttributes(uiScreenNodes[i].xml);
			} catch (Exception& exception) {
				Console::println("UIEditorTabView::reAddScreens(): an error occurred: " + string(exception.what()));
			}
			//
			if (templateAttributes.find("preview-id") == templateAttributes.end()) templateAttributes["preview-id"] = "preview-id";
			if (templateAttributes.find("preview-container-width") == templateAttributes.end()) templateAttributes["preview-container-width"] = "100%";
			if (templateAttributes.find("preview-container-height") == templateAttributes.end()) templateAttributes["preview-container-height"] = "100%";
			//
			try {
				screenNode = GUIParser::parse(
					string() +
					"<screen id='screen_template'>\n" +
					"	<layout width='{$preview-container-width}' height='{$preview-container-height}' alignment='none' horizontal-align='center' vertical-align='center'>\n" +
					GUIParser::getInnerXml(StringTools::replace(uiScreenNodes[i].xml, "{$id}", "{$preview-id}")) +
					"	</layout>'>\n" +
					"</screen>>\n",
					templateAttributes,
					Tools::getPathName(uiScreenNodes[i].fileName),
					Tools::getFileName(uiScreenNodes[i].fileName)
				);
			} catch (Exception& exception) {
				Console::println("UIEditorTabView::reAddScreens(): an error occurred: " + string(exception.what()));
				// error handling
				try {
					screenNode = GUIParser::parse(
						"resources/engine/gui/",
						"screen_text.xml",
						{{ "text", StringTools::replace(StringTools::replace("An error occurred: " + string(exception.what()), "[", "\\["), "]", "\\]") }}
					);
				} catch (Exception& exception2) {
					Console::println("UIEditorTabView::reAddScreens(): an error occurred: " + string(exception2.what()));
				}
			}
		}

		//
		uiScreenNodes[i].screenNode = screenNode;
		if (screenNode == nullptr) continue;

		//
		uiScreenNodes[i].width = screenNode == nullptr?-1:screenNode->getSizeConstraints().maxWidth;
		uiScreenNodes[i].height = screenNode == nullptr?-1:screenNode->getSizeConstraints().maxHeight;
		if (uiScreenNodes[i].width > screensMaxWidth) screensMaxWidth = uiScreenNodes[i].width;
		if (uiScreenNodes[i].height > screensMaxHeight) screensMaxHeight = uiScreenNodes[i].height;

		//
		screenNode->getSizeConstraints().minWidth = -1;
		screenNode->getSizeConstraints().minHeight = -1;
		screenNode->getSizeConstraints().maxWidth = -1;
		screenNode->getSizeConstraints().maxHeight = -1;

		//
		screenNode->addTooltipRequestListener(uiTabController.get());
		guiEngine->getGUI()->addScreen(screenNode->getId(), screenNode);
		guiEngine->getGUI()->addRenderScreen(screenNode->getId());
	}
	if (screensMaxWidth == -1) screensMaxWidth = 1920;
	if (screensMaxHeight == -1) screensMaxHeight = 1080;
	if (guiEngine->getWidth() != screensMaxWidth || guiEngine->getHeight() != screensMaxHeight) {
		guiEngine->reshape(screensMaxWidth, screensMaxHeight);
	}
}

Prototype* UIEditorTabView::getPrototype() {
	return prototype.get();
}

Prototype* UIEditorTabView::loadPrototype(const string& pathName, const string& fileName, const string& modelMeshNode, const string& modelMeshAnimation) {
	//
	if (projectedUi == true) engine->reset();
	prototype = nullptr;

	//
	try {
		prototype = unique_ptr<Prototype>(PrototypeReader::read(pathName, fileName));
	} catch (Exception& exception) {
		Console::println("UIEditorTabView::loadPrototype(): An error occurred: " + string(exception.what()));
		//
		return nullptr;
	}

	//
	auto projectedUiLast = projectedUi;
	if (projectedUi == false) {
		engine = unique_ptr<Engine>(Engine::createOffScreenInstance(512, 512, true, true, false));
		engine->setPartition(new SimplePartition());
		engine->setShadowMapLightEyeDistanceScale(0.1f);
		engine->setSceneColor(Color4(39.0f / 255.0f, 39.0f / 255.0f, 39.0f / 255.0f, 1.0f));
		guiEngine->setSceneColor(Color4(0.0f, 0.0f, 0.0f, 0.0f));
		cameraRotationInputHandler = make_unique<CameraRotationInputHandler>(engine.get(), this);
		projectedUi = true;
	}
	Vector3 objectScale;
	Tools::setupPrototype(prototype.get(), engine.get(), cameraRotationInputHandler->getLookFromRotations(), 1, objectScale, cameraRotationInputHandler.get(), 1.5f, projectedUiLast == true);

	// scale model, ground * 2
	auto modelEntity = engine->getEntity("model");
	if (modelEntity != nullptr) {
		modelEntity->setScale(modelEntity->getScale() * 2.0f);
		modelEntity->update();
		static_cast<Object*>(modelEntity)->bindDiffuseTexture(guiEngine->getFrameBuffer(), modelMeshNode);
		static_cast<Object*>(modelEntity)->setAnimation(modelMeshAnimation);
	}
	auto groundEntity = engine->getEntity("ground");
	if (groundEntity != nullptr) {
		groundEntity->setScale(groundEntity->getScale() * 2.0f);
		groundEntity->update();
	}

	//
	setModelMeshNode(modelMeshNode);

	//
	return prototype.get();
}

void UIEditorTabView::setModelMeshNode(const string& modelMeshNode) {
	if (projectedUi == false) return;
	//
	auto modelEntity = dynamic_cast<Object*>(engine->getEntity("model"));
	if (modelEntity != nullptr) {
		modelEntity->unbindDiffuseTexture();
		if (modelMeshNode.empty() == false) modelEntity->bindDiffuseTexture(guiEngine->getFrameBuffer(), modelMeshNode);
	}

	this->modelMeshNode = modelMeshNode;
	projectedUiMinX = Float::MAX_VALUE;
	projectedUiMinZ = Float::MAX_VALUE;
	projectedUiMaxX = Float::MIN_VALUE;
	projectedUiMaxZ = Float::MIN_VALUE;

	auto model = prototype->getModel();
	if (model == nullptr || model->getNodeById(modelMeshNode) == nullptr) return;

	//
	const auto& modelMeshNodeFacesEntities = model->getNodeById(modelMeshNode)->getFacesEntities();
	unordered_set<string> materialIds;
	for (const auto& facesEntity: modelMeshNodeFacesEntities) {
		if (facesEntity.getMaterial() != nullptr) materialIds.insert(facesEntity.getMaterial()->getId());
		for (const auto& face: facesEntity.getFaces()) {
			for (auto i = 0; i < 3; i++) {
				projectedUiMinZ = Math::min(projectedUiMinZ, face.getNode()->getVertices()[face.getVertexIndices()[i]].getZ());
				projectedUiMinX = Math::min(projectedUiMinX, face.getNode()->getVertices()[face.getVertexIndices()[i]].getX());
				projectedUiMaxZ = Math::max(projectedUiMaxZ, face.getNode()->getVertices()[face.getVertexIndices()[i]].getZ());
				projectedUiMaxX = Math::max(projectedUiMaxX, face.getNode()->getVertices()[face.getVertexIndices()[i]].getX());
			}
		}
	}

	//
	for (const auto& materialId: materialIds) {
		auto materialIt = model->getMaterials().find(materialId);
		auto material = materialIt != model->getMaterials().end()?materialIt->second:nullptr;
		if (material == nullptr) continue;
		material->getSpecularMaterialProperties()->setDiffuseColor(Color4(0.8f, 0.8f, 0.8f, 0.9999f));
		if (material->getPBRMaterialProperties() != nullptr) material->getPBRMaterialProperties()->setBaseColorFactor(Color4(1.0f, 1.0f, 1.0f, 0.9999f));
	}
}

void UIEditorTabView::setModelMeshAnimation(const string& modelMeshAnimation) {
	if (projectedUi == false) return;
	//
	auto modelEntity = dynamic_cast<Object*>(engine->getEntity("model"));
	if (modelEntity != nullptr) {
		modelEntity->setAnimation(modelMeshAnimation);
	}
}

void UIEditorTabView::removePrototype() {
	//
	if (projectedUi == true) {
		engine->dispose();
		engine = nullptr;
		cameraRotationInputHandler = nullptr;
		projectedUi = false;
	}
	prototype = nullptr;

	//
	guiEngine->setSceneColor(Color4(39.0f / 255.0f, 39.0f / 255.0f, 39.0f / 255.0f, 1.0f));
}

void UIEditorTabView::setScreenIdx(int screenIdx) {
	//
	storeUIXML();
	//
	this->screenIdx = screenIdx;
	//
	updateCodeEditor();
}

void UIEditorTabView::storeUIXML() {
	if (screenIdx < 0 || screenIdx >= uiScreenNodes.size()) return;
	uiScreenNodes[screenIdx].xml = textNode->getText().getString();
}

void UIEditorTabView::setVisualEditor() {
	if (visualEditor == true) return;
	//
	uiTabController->closeFindReplaceWindow();
	//
	visualEditor = true;
	//
	auto editorNode = dynamic_cast<GUIElementNode*>(screenNode->getNodeById(tabId + "_tab_editor"));
	if (editorNode != nullptr) editorNode->getActiveConditions().set("visualization");
	//
	reAddScreens();
}

void UIEditorTabView::setCodeEditor() {
	if (visualEditor == false) return;
	visualEditor = false;
	//
	removeScreens();
	//
	auto editorNode = dynamic_cast<GUIElementNode*>(screenNode->getNodeById(tabId + "_tab_editor"));
	if (editorNode != nullptr) editorNode->getActiveConditions().set("text");
	//
	updateCodeEditor();
}

void UIEditorTabView::updateCodeEditor() {
	//
	if (screenIdx < 0 || screenIdx >= uiScreenNodes.size()) return;
	//
	textNode->setText(MutableString(StringTools::replace(StringTools::replace(uiScreenNodes[screenIdx].xml, "[", "\\["), "]", "\\]")));
	// initial text format
	TextFormatter::getInstance()->format("xml", textNode);
}

int UIEditorTabView::getTextIndex() {
	auto textNodeController = required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController());
	return textNodeController->getIndex();
}

bool UIEditorTabView::find(const string& findString, bool matchCase, bool wholeWord, bool selection, bool firstSearch, int& index) {
	cancelFind();
	return TextTools::find(textNode, findString, matchCase, wholeWord, selection, firstSearch, index);
}

int UIEditorTabView::count(const string& findString, bool matchCase, bool wholeWord, bool selection) {
	cancelFind();
	countEnabled = true;
	return TextTools::count(textNode, findString, matchCase, wholeWord, selection);
}

bool UIEditorTabView::replace(const string& findString, const string& replaceString, bool matchCase, bool wholeWord, bool selection, int& index) {
	cancelFind();
	auto success = TextTools::replace(textNode, findString, replaceString, matchCase, wholeWord, selection, index);
	TextFormatter::getInstance()->format("xml", textNode, 0, textNode->getText().size());
	return success;
}

bool UIEditorTabView::replaceAll(const string& findString, const string& replaceString, bool matchCase, bool wholeWord, bool selection) {
	auto success = TextTools::replaceAll(textNode, findString, replaceString, matchCase, wholeWord, selection);
	cancelFind();
	return success;
}


void UIEditorTabView::cancelFind() {
	TextFormatter::getInstance()->format("xml", textNode, 0, textNode->getText().size());
	countEnabled = false;
}

void UIEditorTabView::redo() {
	if (visualEditor == false) {
		required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController())->redo();
	}
}

void UIEditorTabView::undo() {
	if (visualEditor == false) {
		required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController())->undo();
	}
}

void UIEditorTabView::selectAll() {
	if (visualEditor == false) {
		required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController())->selectAll();
	}
}

void UIEditorTabView::cut() {
	if (visualEditor == false) {
		required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController())->cut();
	}
}

void UIEditorTabView::copy() {
	if (visualEditor == false) {
		required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController())->copy();
	}
}

void UIEditorTabView::paste() {
	if (visualEditor == false) {
		required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController())->paste();
	}
}

void UIEditorTabView::delete_() {
	if (visualEditor == false) {
		required_dynamic_cast<GUIStyledTextNodeController*>(textNode->getController())->delete_();
	}
}
