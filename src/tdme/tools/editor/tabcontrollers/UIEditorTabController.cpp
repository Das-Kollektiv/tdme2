#include <tdme/tools/editor/tabcontrollers/UIEditorTabController.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIImageNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/controllers/ContextMenuScreenController.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/FindReplaceDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/controllers/TooltipScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabviews/UIEditorTabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

#include <ext/tinyxml/tinyxml.h>

using tdme::tools::editor::tabcontrollers::UIEditorTabController;

using std::string;

using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::Engine;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIImageNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUI;
using tdme::gui::GUIParser;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::controllers::ContextMenuScreenController;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::FindReplaceDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::controllers::TooltipScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::UIEditorTabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;
using tdme::utilities::Integer;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

using tinyxml::TiXmlAttribute;
using tinyxml::TiXmlDocument;
using tinyxml::TiXmlElement;

#define AVOID_NULLPTR_STRING(arg) (arg == nullptr?"":arg)

UIEditorTabController::UIEditorTabController(UIEditorTabView* view)
{
	this->view = view;
	this->popUps = view->getPopUps();
}

UIEditorTabController::~UIEditorTabController() {
}

UIEditorTabView* UIEditorTabController::getView() {
	return view;
}

GUIScreenNode* UIEditorTabController::getScreenNode()
{
	return screenNode;
}

void UIEditorTabController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
}

void UIEditorTabController::dispose()
{
}

void UIEditorTabController::onCommand(TabControllerCommand command)
{
	switch (command) {
		case COMMAND_REDO:
			view->redo();
			break;
		case COMMAND_UNDO:
			view->undo();
			break;
		case COMMAND_CUT:
			view->cut();
			break;
		case COMMAND_COPY:
			view->copy();
			break;
		case COMMAND_PASTE:
			view->paste();
			break;
		case COMMAND_DELETE:
			view->delete_();
			break;
		case COMMAND_SELECTALL:
			view->selectAll();
			break;
		case COMMAND_SAVE:
			save();
			break;
		case COMMAND_SAVEAS:
			saveAs();
			break;
		case COMMAND_FINDREPLACE:
			{
				//
				firstSearch = true;
				searchIndex = view->getTextIndex();

				//
				class FindAction: public virtual Action
				{
				public:
					void performAction() override {
						if (uiEditorTabController->popUps->getFindReplaceDialogScreenController()->getFindText().empty() == true) {
							uiEditorTabController->showInfoPopUp("Find", "No find string given.");
						} else {
							if (uiEditorTabController->view->find(
								uiEditorTabController->popUps->getFindReplaceDialogScreenController()->getFindText(),
								uiEditorTabController->popUps->getFindReplaceDialogScreenController()->isMatchCase(),
								uiEditorTabController->popUps->getFindReplaceDialogScreenController()->isWholeWordOnly(),
								uiEditorTabController->popUps->getFindReplaceDialogScreenController()->isInSelectionOnly(),
								uiEditorTabController->firstSearch,
								uiEditorTabController->searchIndex
							) == false) {
								uiEditorTabController->showInfoPopUp("Find", "Text not found.");
							}
							uiEditorTabController->firstSearch = false;
						}
					}
					FindAction(UIEditorTabController* uiEditorTabController): uiEditorTabController(uiEditorTabController) {
					}
				private:
					UIEditorTabController* uiEditorTabController;
				};
				//
				class CountAction: public virtual Action
				{
				public:
					void performAction() override {
						if (uiEditorTabController->popUps->getFindReplaceDialogScreenController()->getFindText().empty() == true) {
							uiEditorTabController->showInfoPopUp("Count", "No find string given.");
						} else {
							auto count = uiEditorTabController->view->count(
								uiEditorTabController->popUps->getFindReplaceDialogScreenController()->getFindText(),
								uiEditorTabController->popUps->getFindReplaceDialogScreenController()->isMatchCase(),
								uiEditorTabController->popUps->getFindReplaceDialogScreenController()->isWholeWordOnly(),
								uiEditorTabController->popUps->getFindReplaceDialogScreenController()->isInSelectionOnly()
							);
							uiEditorTabController->showInfoPopUp("Count", "The text occurred " + to_string(count) + " times.");
						}
					}
					CountAction(UIEditorTabController* uiEditorTabController): uiEditorTabController(uiEditorTabController) {
					}
				private:
					UIEditorTabController* uiEditorTabController;
				};
				//
				class ReplaceAction: public virtual Action
				{
				public:
					void performAction() override {
						if (uiEditorTabController->popUps->getFindReplaceDialogScreenController()->getFindText().empty() == true) {
							uiEditorTabController->showInfoPopUp("Replace", "No find string given.");
						} else {
							if (uiEditorTabController->view->replace(
								uiEditorTabController->popUps->getFindReplaceDialogScreenController()->getFindText(),
								uiEditorTabController->popUps->getFindReplaceDialogScreenController()->getReplaceText(),
								uiEditorTabController->popUps->getFindReplaceDialogScreenController()->isMatchCase(),
								uiEditorTabController->popUps->getFindReplaceDialogScreenController()->isWholeWordOnly(),
								uiEditorTabController->popUps->getFindReplaceDialogScreenController()->isInSelectionOnly(),
								uiEditorTabController->searchIndex
							) == false) {
								uiEditorTabController->showInfoPopUp("Replace", "Text not found.");
							}
						}
					}
					ReplaceAction(UIEditorTabController* uiEditorTabController): uiEditorTabController(uiEditorTabController) {
					}
				private:
					UIEditorTabController* uiEditorTabController;
				};
				//
				class ReplaceAllAction: public virtual Action
				{
				public:
					void performAction() override {
						if (uiEditorTabController->popUps->getFindReplaceDialogScreenController()->getFindText().empty() == true) {
							uiEditorTabController->showInfoPopUp("Replace All", "No find string given.");
						} else {
							if (uiEditorTabController->view->replaceAll(
								uiEditorTabController->popUps->getFindReplaceDialogScreenController()->getFindText(),
								uiEditorTabController->popUps->getFindReplaceDialogScreenController()->getReplaceText(),
								uiEditorTabController->popUps->getFindReplaceDialogScreenController()->isMatchCase(),
								uiEditorTabController->popUps->getFindReplaceDialogScreenController()->isWholeWordOnly(),
								uiEditorTabController->popUps->getFindReplaceDialogScreenController()->isInSelectionOnly()
							) == false) {
								uiEditorTabController->showInfoPopUp("Replace All", "Text not found.");
							}
						}
					}
					ReplaceAllAction(UIEditorTabController* uiEditorTabController): uiEditorTabController(uiEditorTabController) {
					}
				private:
					UIEditorTabController* uiEditorTabController;
				};
				//
				class CompleteAction: public virtual Action
				{
				public:
					void performAction() override {
						uiEditorTabController->view->cancelFind();
						uiEditorTabController->popUps->getFindReplaceDialogScreenController()->close();
					}
					CompleteAction(UIEditorTabController* uiEditorTabController): uiEditorTabController(uiEditorTabController) {
					}
				private:
					UIEditorTabController* uiEditorTabController;
				};
				//
				popUps->getFindReplaceDialogScreenController()->show(
					new FindAction(this),
					new CountAction(this),
					new ReplaceAction(this),
					new ReplaceAllAction(this),
					new CompleteAction(this)
				);
			}
			break;
		default:
			showInfoPopUp("Warning", "This command is not supported yet");
			break;
	}
}

void UIEditorTabController::onDrop(const string& payload, int mouseX, int mouseY) {
	if (StringTools::startsWith(payload, "file:") == false) {
		showInfoPopUp("Warning", "Unknown payload in drop");
	} else {
		auto fileName = StringTools::substring(payload, string("file:").size());
		if (view->getEditorView()->getScreenController()->isDropOnNode(mouseX, mouseY, "screen") == true) {
			if (Tools::hasFileExtension(fileName, {{ "xml" }}) == false) {
				showInfoPopUp("Warning", "You can not drop this file here. Allowed file extensions are " + Tools::enumerateFileExtensions({{ "xml" }}));
			} else {
				auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
				auto screenIdx = Integer::parse(StringTools::substring(outlinerNode, 0, outlinerNode.find(".")));
				setScreen(screenIdx, fileName);
			}
		} else
		if (view->getEditorView()->getScreenController()->isDropOnNode(mouseX, mouseY, "projectedui_prototype") == true) {
			if (Tools::hasFileExtension(fileName, PrototypeReader::getModelExtensions()) == false) {
				showInfoPopUp("Warning", "You can not drop this file here. Allowed file extensions are " + Tools::enumerateFileExtensions(PrototypeReader::getModelExtensions()));
			} else {
				setPrototype(
					Tools::getPathName(fileName),
					Tools::getFileName(fileName),
					prototypeMeshNode,
					prototypeMeshAnimation
				);
			}
		} else {
			showInfoPopUp("Warning", "You can not drop a file here");
		}
	}
}

void UIEditorTabController::showInfoPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}

void UIEditorTabController::onChange(GUIElementNode* node)
{
	if (node->getId() == "selectbox_outliner") {
		updateDetails(node->getController()->getValue().getString());
		auto outlinerNode = node->getController()->getValue().getString();
		view->setScreenIdx(outlinerNode == "screens"?0:Integer::parse(StringTools::substring(outlinerNode, 0, outlinerNode.find("."))));
	} else
	if (node->getId() == "dropdown_outliner_add") {
		auto addOutlinerType = node->getController()->getValue().getString();;
		if (addOutlinerType == "screen") {
			view->addScreen();
			view->getEditorView()->reloadTabOutliner(to_string(view->getUIScreenNodes().size() - 1) + ".0");
		}
	} else
	if (node->getId() == "projectedui_meshnode") {
		prototypeMeshNode = node->getController()->getValue().getString();
		view->setModelMeshNode(prototypeMeshNode);
	} else
	if (node->getId() == "projectedui_animation") {
		prototypeMeshAnimation = node->getController()->getValue().getString();
		view->setModelMeshAnimation(prototypeMeshAnimation);
	} else
	if (node->getId() == view->getTabId() + "_tab_checkbox_visualui" == true) {
		auto visual = node->getController()->getValue().equals("1");
		if (visual == true) {
			view->storeUIXML();
			view->setVisualEditor();
		} else {
			view->setCodeEditor();
		}
	}
}

void UIEditorTabController::onFocus(GUIElementNode* node) {
}

void UIEditorTabController::onUnfocus(GUIElementNode* node) {
}

void UIEditorTabController::onContextMenuRequest(GUIElementNode* node, int mouseX, int mouseY) {
	if (node->getId() == "selectbox_outliner") {
		auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
		if (outlinerNode == "screens") {
			// clear
			popUps->getContextMenuScreenController()->clear();

			// add screen
			class OnAddScreenAction: public virtual Action
			{
			public:
				OnAddScreenAction(UIEditorTabController* uiEditorTabController): uiEditorTabController(uiEditorTabController) {
				}
				void performAction() override {
					auto view = uiEditorTabController->getView();
					view->addScreen();
					view->getEditorView()->reloadTabOutliner(to_string(view->getUIScreenNodes().size() - 1) + ".0");
				}
			private:
				UIEditorTabController* uiEditorTabController;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Add Screen", "contextmenu_add", new OnAddScreenAction(this));

			// reload screens
			class OnScreensReloadAction: public virtual Action
			{
			public:
				OnScreensReloadAction(UIEditorTabController* uiEditorTabController): uiEditorTabController(uiEditorTabController) {
				}
				void performAction() override {
					uiEditorTabController->reloadScreens();
				}
			private:
				UIEditorTabController* uiEditorTabController;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Reload", "contextmenu_reload", new OnScreensReloadAction(this));

			// show
			popUps->getContextMenuScreenController()->show(mouseX, mouseY);
		} else
		if (StringTools::endsWith(outlinerNode, ".0") == true && StringTools::startsWith(outlinerNode, "0.") == false) {
			auto screenIdx = Integer::parse(StringTools::substring(outlinerNode, 0, outlinerNode.find(".")));

			// clear
			popUps->getContextMenuScreenController()->clear();

			// remove screen
			class OnScreenRemoveAction: public virtual Action
			{
			public:
				OnScreenRemoveAction(UIEditorTabController* uiEditorTabController, int screenIdx): uiEditorTabController(uiEditorTabController), screenIdx(screenIdx) {
				}
				void performAction() override {
					auto view = uiEditorTabController->getView();
					view->removeScreen(screenIdx);
					view->getEditorView()->reloadTabOutliner(to_string(view->getUIScreenNodes().size() - 1) + ".0");
				}
			private:
				UIEditorTabController* uiEditorTabController;
				int screenIdx;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Remove", "contextmenu_remove", new OnScreenRemoveAction(this, screenIdx));

			// show
			popUps->getContextMenuScreenController()->show(mouseX, mouseY);
		}
	}
}

void UIEditorTabController::onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) {
	int tooltipLeft, tooltipTop;
	if (view->getEditorView()->getCurrentTabTooltipPosition(screenNode, mouseX, mouseY, tooltipLeft, tooltipTop) == false) return;
	//
	popUps->getTooltipScreenController()->show(tooltipLeft, tooltipTop, node->getToolTip());
}

void UIEditorTabController::onTooltipCloseRequest() {
	popUps->getTooltipScreenController()->close();
}

void UIEditorTabController::createOutlinerParentNodeNodesXML(TiXmlElement* xmlParentNode, string& xml, int screenIdx, int& nodeIdx) {
	if (xmlParentNode->FirstChildElement() == nullptr) {
		auto nodeId = string(AVOID_NULLPTR_STRING(xmlParentNode->Attribute("id")));
		xml+= "<selectbox-option text=\"<" + GUIParser::escape(xmlParentNode->Value()) + ">" + (nodeId.empty() == false?string(" (") + nodeId + ")":"") + "\" value=\"" + to_string(screenIdx) + "." + GUIParser::escape(to_string(nodeIdx++)) + "\" />\n";
	} else {
		auto nodeId = string(AVOID_NULLPTR_STRING(xmlParentNode->Attribute("id")));
		xml+= "<selectbox-parent-option text=\"<" + GUIParser::escape(xmlParentNode->Value()) + ">" + (nodeId.empty() == false?string(" (") + nodeId + ")":"") + "\" value=\"" + to_string(screenIdx) + "." + GUIParser::escape(to_string(nodeIdx++)) + "\" >\n";
		for (auto* childNode = xmlParentNode->FirstChildElement(); childNode != nullptr; childNode = childNode->NextSiblingElement()) {
			createOutlinerParentNodeNodesXML(childNode, xml, screenIdx, nodeIdx);
		}
		xml+= "</selectbox-parent-option>\n";
	}
}

void UIEditorTabController::setOutlinerContent() {
	string xml;
	xml+= "<selectbox-parent-option text=\"Screens\" value=\"screens\">\n";
	auto screenIdx = 0;
	for (auto& uiScreenNode: view->getUIScreenNodes()) {
		auto screenNode = uiScreenNode.screenNode;
		if (screenNode == nullptr) {
			xml+= "<selectbox-option text=\"<screen>\" value=\"" + to_string(screenIdx) + ".0\" />\n";
			screenIdx++;
			continue;
		}
		if (uiScreenNode.xml.empty() == false) {
			try {
				TiXmlDocument xmlDocument;
				xmlDocument.Parse(uiScreenNode.xml.c_str());
				if (xmlDocument.Error() == true) {
					auto message = "UIEditorTabController::setOutlinerContent(): Could not parse XML. Error='" + string(xmlDocument.ErrorDesc()) + "':\n\n" + uiScreenNode.xml;
					Console::println(message);
					throw GUIParserException(message);
				}
				TiXmlElement* xmlRoot = xmlDocument.RootElement();
				int nodeIdx = 0;
				createOutlinerParentNodeNodesXML(xmlRoot, xml, screenIdx, nodeIdx);
			} catch (Exception& exception) {
				showInfoPopUp("Warning", string(exception.what()));
			}
		}
		screenIdx++;
	}
	xml+= "</selectbox-parent-option>\n";
	view->getEditorView()->setOutlinerContent(xml);
}

void UIEditorTabController::setOutlinerAddDropDownContent() {
	view->getEditorView()->setOutlinerAddDropDownContent(
		string("<dropdown-option text=\"Screen\" value=\"screen\" />\n")
	);
}

void UIEditorTabController::updateDetails(const string& outlinerNode) {
	if (outlinerNode == "screens") {
		updateScreensDetails();
	} else
	if (StringTools::endsWith(outlinerNode, ".0") == true) {
		updateScreenDetails();
		view->setScreenIdx(outlinerNode == "screens"?0:Integer::parse(StringTools::substring(outlinerNode, 0, outlinerNode.find("."))));
	} else {
		view->getEditorView()->setDetailsContent(string());
	}
}

void UIEditorTabController::updateScreenDetails() {
	view->getEditorView()->setDetailsContent(
		string("<template id=\"details_screen\" src=\"resources/engine/gui/template_details_screen.xml\" />\n")
	);

	//
	auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
	auto screenIdx = Integer::parse(StringTools::substring(outlinerNode, 0, outlinerNode.find(".")));

	//
	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_screen"))->getActiveConditions().add("open");
		if (screenIdx >= 0 &&
			screenIdx < view->getUIScreenNodes().size() &&
			view->getUIScreenNodes()[screenIdx].screenNode != nullptr &&
			view->getUIScreenNodes()[screenIdx].fileName.empty() == false) {
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("screen"))->setSource("resources/engine/images/gui_big.png");
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("screen"))->setTooltip(view->getUIScreenNodes()[screenIdx].fileName);
		}
	} catch (Exception& exception) {
		Console::println("UIEditorTabController::updateScreenDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
}

void UIEditorTabController::updateScreensDetails() {
	view->getEditorView()->setDetailsContent(
		string("<template id=\"details_screens\" src=\"resources/engine/gui/template_details_projectedui.xml\" />\n")
	);

	//
	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_screens"))->getActiveConditions().add("open");
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("projectedui_prototype"))->setSource(prototypeFileName);
		required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("projectedui_prototype"))->setTooltip(prototypeFileName);
	} catch (Exception& exception) {
		Console::println("UIEditorTabController::updateScreensDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}

	//
	auto model = view->getPrototype() != nullptr?view->getPrototype()->getModel():nullptr;

	{
		string modelMeshNodesXML;
		modelMeshNodesXML =
			modelMeshNodesXML +
			"<dropdown-option text=\"<None>\" value=\"\" " + (modelMeshNodesXML.empty() == true?"selected=\"true\" ":"") + " />\n";
		if (model != nullptr) {
			for (const auto& [nodeId, node]: model->getNodes()) {
				modelMeshNodesXML+=
					"<dropdown-option text=\"" +
					GUIParser::escape(nodeId) +
					"\" value=\"" +
					GUIParser::escape(nodeId) +
					"\" " +
					(modelMeshNodesXML == nodeId?"selected=\"true\" ":"") +
					" />\n";
			}
		}
		try {
			required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("projectedui_meshnode_scrollarea"))->replaceSubNodes(modelMeshNodesXML, true);
		} catch (Exception& exception) {
			Console::print("UIEditorTabController::updateScreensDetails(): An error occurred: " + string(exception.what()));
		}
	}

	{
		string animationsXML;
		animationsXML = animationsXML + "<dropdown-option text=\"<No animation>\" value=\"\" selected=\"true\" />";
		if (model != nullptr) {
			for (const auto& [animationSetupId, animationSetup]: model->getAnimationSetups()) {
				if (animationSetup->isOverlayAnimationSetup() == true) continue;
				animationsXML =
					animationsXML + "<dropdown-option text=\"" +
					GUIParser::escape(animationSetup->getId()) +
					"\" value=\"" +
					GUIParser::escape(animationSetup->getId()) +
					"\" " +
					" />\n";
			}
		}
		try {
			required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("projectedui_animation_scrollarea"))->replaceSubNodes(animationsXML, true);
		} catch (Exception& exception) {
			Console::println("ModelEditorTabController::setAnimationPreviewDetails(): An error occurred: " + string(exception.what()));
		}
	}
}

void UIEditorTabController::onLoadScreen() {
	class OnLoadScreen: public virtual Action
	{
	public:
		void performAction() override {
			//
			uiEditorTabController->setScreen(
				screenIdx,
				uiEditorTabController->popUps->getFileDialogScreenController()->getPathName() + "/" + uiEditorTabController->popUps->getFileDialogScreenController()->getFileName()
			);
			//
			uiEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param uiEditorTabController UI editor tab controller
		 * @param screenIdx screen index
		 */
		OnLoadScreen(UIEditorTabController* uiEditorTabController, int screenIdx)
			: uiEditorTabController(uiEditorTabController), screenIdx(screenIdx) {
		}

	private:
		UIEditorTabController* uiEditorTabController;
		int screenIdx;
	};

	auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
	auto screenIdx = Integer::parse(StringTools::substring(outlinerNode, 0, outlinerNode.find(".")));
	if (screenIdx < 0 || screenIdx >= view->getUIScreenNodes().size()) return;
	auto screenNode = view->getUIScreenNodes()[screenIdx].screenNode;
	auto pathName = screenNode != nullptr?Tools::getPathName(view->getUIScreenNodes()[screenIdx].fileName):string();
	auto fileName = screenNode != nullptr?Tools::getFileName(view->getUIScreenNodes()[screenIdx].fileName):string();
	popUps->getFileDialogScreenController()->show(
		pathName,
		"Load screen from: ",
		{ { "xml" } },
		fileName,
		true,
		new OnLoadScreen(this, screenIdx)
	);
}

void UIEditorTabController::onUnsetScreen() {
	auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
	auto screenIdx = Integer::parse(StringTools::substring(outlinerNode, 0, outlinerNode.find(".")));
	if (screenIdx < 0 || screenIdx >= view->getUIScreenNodes().size()) return;
	view->unsetScreen(screenIdx);
	view->reAddScreens();
	view->getEditorView()->reloadTabOutliner(to_string(screenIdx) + ".0");
}

void UIEditorTabController::onBrowseToScreen() {
	auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
	auto screenIdx = Integer::parse(StringTools::substring(outlinerNode, 0, outlinerNode.find(".")));
	if (screenIdx < 0 || screenIdx >= view->getUIScreenNodes().size() || view->getUIScreenNodes()[screenIdx].fileName.empty() == true) {
		showInfoPopUp("Browse To", "Nothing to browse to");
	} else {
		view->getEditorView()->getScreenController()->browseTo(view->getUIScreenNodes()[screenIdx].fileName);
	}
}

void UIEditorTabController::reloadScreens() {
	for (auto i = 0; i < view->getUIScreenNodes().size(); i++) {
		auto fileName = view->getUIScreenNodes()[i].fileName;
		view->unsetScreen(i);
		try {
			view->setScreen(
				i,
				fileName
			);
		} catch (Exception& exception) {
			Console::println("UIEditorTabController::reloadScreens(): An error occurred: " + string(exception.what()));
		}
	}
	view->reAddScreens();
	view->getEditorView()->reloadTabOutliner("screens");
}

void UIEditorTabController::onLoadPrototype() {
	class OnLoadPrototype: public virtual Action
	{
	public:
		void performAction() override {
			uiEditorTabController->setPrototype(
				uiEditorTabController->popUps->getFileDialogScreenController()->getPathName(),
				uiEditorTabController->popUps->getFileDialogScreenController()->getFileName(),
				uiEditorTabController->prototypeMeshNode,
				uiEditorTabController->prototypeMeshAnimation
			);
			uiEditorTabController->view->getPopUps()->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param uiEditorTabController UI editor tab controller
		 */
		OnLoadPrototype(UIEditorTabController* uiEditorTabController): uiEditorTabController(uiEditorTabController) {
		}

	private:
		UIEditorTabController* uiEditorTabController;
	};

	//
	auto pathName = screenNode != nullptr?Tools::getPathName(prototypeFileName):string();
	auto fileName = screenNode != nullptr?Tools::getFileName(prototypeFileName):string();
	popUps->getFileDialogScreenController()->show(
		pathName,
		"Load prototype from: ",
		PrototypeReader::getPrototypeExtensions(),
		fileName,
		true,
		new OnLoadPrototype(this)
	);
}

void UIEditorTabController::onRemovePrototype() {
	prototypeFileName.clear();
	view->removePrototype();
	view->reAddScreens();
	view->getEditorView()->reloadTabOutliner("screens");
}

void UIEditorTabController::onBrowseToPrototype() {
	if (prototypeFileName.empty() == true) {
		showInfoPopUp("Browse To", "Nothing to browse to");
	} else {
		view->getEditorView()->getScreenController()->browseTo(prototypeFileName);
	}
}

void UIEditorTabController::onAction(GUIActionListenerType type, GUIElementNode* node)
{
	if (type != GUIActionListenerType::PERFORMED) return;
	if (node->getId() == "screen_open") {
		onLoadScreen();
	} else
	if (node->getId() == "screen_remove") {
		onUnsetScreen();
	} else
	if (node->getId() == "screen_browseto") {
		onBrowseToScreen();
	} else
	if (node->getId() == "projectedui_prototype_open") {
		onLoadPrototype();
	} else
	if (node->getId() == "projectedui_prototype_remove") {
		onRemovePrototype();
	} else
	if (node->getId() == "projectedui_prototype_browseto") {
		onBrowseToPrototype();
	}
}

void UIEditorTabController::setScreen(int screenIdx, const string& fileName) {
	view->unsetScreen(screenIdx);
	try {
		view->setScreen(screenIdx, fileName);
	} catch (Exception& exception) {
		Console::println("UIEditorTabController::setScreen(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Error", "An error occurred: " + string(exception.what()));
	}
	view->reAddScreens();
	view->getEditorView()->reloadTabOutliner(to_string(screenIdx) + ".0");
}

void UIEditorTabController::setPrototype(const string& pathName, const string& fileName, const string& modelMeshNode, const string& modelMeshAnimation) {
	if (view->loadPrototype(pathName, fileName, prototypeMeshNode, prototypeMeshAnimation) != nullptr) {
		prototypeFileName = pathName + "/" + fileName;
		view->reAddScreens();
		view->getEditorView()->reloadTabOutliner("screens");
	} else {
		showInfoPopUp("Error", string() + "Could not load prototype");
	}
}

void UIEditorTabController::closeFindReplaceWindow() {
	popUps->getFindReplaceDialogScreenController()->close();
}

void UIEditorTabController::save() {
	//
	view->storeUIXML();

	//
	class OnUISave: public virtual Action
	{
	public:
		void performAction() override {
			// skip if wrong screen index
			if (screenIdx < 0 || screenIdx >= uiEditorTabController->view->getUIScreenNodes().size()) {
				uiEditorTabController->popUps->getFileDialogScreenController()->close();
				return;
			}

			// get new path and file name
			auto pathName = uiEditorTabController->popUps->getFileDialogScreenController()->getPathName();
			auto fileName = Tools::ensureFileExtension(uiEditorTabController->popUps->getFileDialogScreenController()->getFileName(), "xml");
			uiEditorTabController->view->getUIScreenNodes()[screenIdx].fileName = pathName + "/" + fileName;

			// save
			try {
				FileSystem::getInstance()->setContentFromString(
					pathName,
					fileName,
					uiEditorTabController->view->getUIScreenNodes()[screenIdx].xml
				);
				// refresh outliner if required
				if (uiEditorTabController->view->getScreenIdx() == screenIdx) {
					uiEditorTabController->view->getEditorView()->reloadTabOutliner(to_string(screenIdx) + ".0");
				}
			} catch (Exception& exception) {
				uiEditorTabController->showInfoPopUp("Warning", string(exception.what()));
			}

			// iterate to next screen that we want to save
			screenIdx++;
			for (; screenIdx < uiEditorTabController->view->getUIScreenNodes().size(); screenIdx++) {
				// skip on empty xml
				if (uiEditorTabController->view->getUIScreenNodes()[screenIdx].xml.empty() == true) continue;
				// skip on existin filename as we saved this before
				if (uiEditorTabController->view->getUIScreenNodes()[screenIdx].fileName.empty() == false) continue;
				//
				break;
			}

			// issue SAVE AS for next screen
			if (screenIdx >= 0 && screenIdx < uiEditorTabController->view->getUIScreenNodes().size()) {
				auto fileName = Tools::getPathName(uiEditorTabController->view->getFileName()) + "/Untitled.xml";
				uiEditorTabController->popUps->getFileDialogScreenController()->show(
					Tools::getPathName(fileName),
					"Save to: ",
					{ { "xml" } },
					Tools::getFileName(fileName),
					false,
					new OnUISave(uiEditorTabController, screenIdx)
				);
			}
			// close this file dialog
			uiEditorTabController->popUps->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param uiEditorTabController ui editor tab controller
		 */
		OnUISave(UIEditorTabController* uiEditorTabController, int screenIdx): uiEditorTabController(uiEditorTabController), screenIdx(screenIdx) {
		}

	private:
		UIEditorTabController* uiEditorTabController;
		int screenIdx;
	};

	// save files with file name
	auto& uiScreenNodes = view->getUIScreenNodes();
	auto emptyFileNameIdx = -1;
	for (auto screenIdx = 0; screenIdx < uiScreenNodes.size(); screenIdx++) {
		// skip on empty xml
		if (uiScreenNodes[screenIdx].xml.empty() == true) continue;
		// empty filename?
		if (uiScreenNodes[screenIdx].fileName.empty() == true) {
			emptyFileNameIdx = screenIdx;
			continue;
		}

		//
		auto& uiScreenNode = uiScreenNodes[screenIdx];
		try {
			FileSystem::getInstance()->setContentFromString(
				Tools::getPathName(uiScreenNode.fileName),
				Tools::getFileName(uiScreenNode.fileName),
				uiScreenNode.xml
			);
		} catch (Exception& exception) {
			Console::println("UIEditorTabController::save(): An error occurred: " + string(exception.what()));
			showInfoPopUp("Warning", string(exception.what()));
		}
	}

	//
	if (emptyFileNameIdx != -1) {
		auto& uiScreenNode = uiScreenNodes[emptyFileNameIdx];
		//
		auto fileName = Tools::getPathName(view->getFileName()) + "/Untitled.xml";
		popUps->getFileDialogScreenController()->show(
			Tools::getPathName(fileName),
			"Save to: ",
			{ { "xml" } },
			Tools::getFileName(fileName),
			false,
			new OnUISave(this, emptyFileNameIdx)
		);
	}
}

void UIEditorTabController::saveAs() {
	//
	view->storeUIXML();

	//
	class OnUISaveAs: public virtual Action
	{
	public:
		/**
		 * Public constructor
		 * @param uiEditorTabController ui editor tab controller
		 */
		OnUISaveAs(UIEditorTabController* uiEditorTabController, int screenIdx): uiEditorTabController(uiEditorTabController), screenIdx(screenIdx) {
		}

		void performAction() override {
			// skip if wrong screen index
			if (screenIdx < 0 || screenIdx >= uiEditorTabController->view->getUIScreenNodes().size()) {
				uiEditorTabController->popUps->getFileDialogScreenController()->close();
				return;
			}

			// get new path and file name
			auto pathName = uiEditorTabController->popUps->getFileDialogScreenController()->getPathName();
			auto fileName = Tools::ensureFileExtension(uiEditorTabController->popUps->getFileDialogScreenController()->getFileName(), "xml");
			uiEditorTabController->view->getUIScreenNodes()[screenIdx].fileName = pathName + "/" + fileName;

			// save
			try {
				FileSystem::getInstance()->setContentFromString(
					pathName,
					fileName,
					uiEditorTabController->view->getUIScreenNodes()[screenIdx].xml
				);
				// refresh outliner if required
				if (uiEditorTabController->view->getScreenIdx() == screenIdx) {
					uiEditorTabController->view->getEditorView()->reloadTabOutliner(to_string(screenIdx) + ".0");
				}
			} catch (Exception& exception) {
				uiEditorTabController->showInfoPopUp("Warning", string(exception.what()));
			}

			// iterate to next screen that we want to save
			screenIdx++;
			for (; screenIdx < uiEditorTabController->view->getUIScreenNodes().size(); screenIdx++) {
				//
				if (uiEditorTabController->view->getUIScreenNodes()[screenIdx].xml.empty() == true) continue;
				//
				break;
			}

			// issue SAVE AS for next screen
			if (screenIdx >= 0 && screenIdx < uiEditorTabController->view->getUIScreenNodes().size()) {
				auto fileName = uiEditorTabController->view->getUIScreenNodes()[screenIdx].fileName;
				if (fileName.empty() == true) fileName = Tools::getPathName(uiEditorTabController->view->getFileName()) + "/Untitled.xml";
				uiEditorTabController->popUps->getFileDialogScreenController()->show(
					Tools::getPathName(fileName),
					"Save to: ",
					{ { "xml" } },
					Tools::getFileName(fileName),
					false,
					new OnUISaveAs(uiEditorTabController, screenIdx)
				);
			}
			// close this file dialog
			uiEditorTabController->popUps->getFileDialogScreenController()->close();
		}

	private:
		UIEditorTabController* uiEditorTabController;
		int screenIdx;
	};

	// find first screen to be saved
	auto& uiScreenNodes = view->getUIScreenNodes();
	for (auto screenIdx = 0; screenIdx < uiScreenNodes.size(); screenIdx++) {
		//
		if (uiScreenNodes[screenIdx].xml.empty() == true) continue;

		//
		auto fileName = uiScreenNodes[screenIdx].fileName;
		if (fileName.empty() == true) fileName = Tools::getPathName(view->getFileName()) + "/Untitled.xml";
		popUps->getFileDialogScreenController()->show(
			Tools::getPathName(fileName),
			"Save to: ",
			{ { "xml" } },
			Tools::getFileName(fileName),
			false,
			new OnUISaveAs(this, screenIdx)
		);

		//
		break;
	}
}
