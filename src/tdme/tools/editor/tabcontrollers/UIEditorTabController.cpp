#include <tdme/tools/editor/tabcontrollers/UIEditorTabController.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
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
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
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

using tdme::engine::Engine;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
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
using tdme::tools::editor::controllers::InfoDialogScreenController;
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

void UIEditorTabController::save()
{
}

void UIEditorTabController::saveAs()
{
}

void UIEditorTabController::showErrorPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}

void UIEditorTabController::onValueChanged(GUIElementNode* node)
{
	if (node->getId() == "selectbox_outliner") {
		updateDetails(node->getController()->getValue().getString());
	} else
	if (node->getId() == "dropdown_outliner_add") {
		auto addOutlinerType = node->getController()->getValue().getString();
		if (addOutlinerType == "screen") {
			view->addScreen();
			view->getEditorView()->reloadTabOutliner(to_string(view->getScreenNodes().size() - 1) + ".0");
		}
	}
}

void UIEditorTabController::onFocus(GUIElementNode* node) {
}

void UIEditorTabController::onUnfocus(GUIElementNode* node) {
}

void UIEditorTabController::onContextMenuRequested(GUIElementNode* node, int mouseX, int mouseY) {
	if (node->getId() == "selectbox_outliner") {
		auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
		if (outlinerNode == "screens") {
			// clear
			popUps->getContextMenuScreenController()->clear();

			// add screen
			class OnAddScreenAction: public virtual Action
			{
			public:
				void performAction() override {
					//
					class AddScreenAction: public Action {
					private:
						UIEditorTabController* uiEditorTabController;
					public:
						AddScreenAction(UIEditorTabController* uiEditorTabController):
							uiEditorTabController(uiEditorTabController) {
						}
						virtual void performAction() {
							auto view = uiEditorTabController->getView();
							view->addScreen();
							view->getEditorView()->reloadTabOutliner(to_string(view->getScreenNodes().size() - 1) + ".0");
						}
					};
					Engine::getInstance()->enqueueAction(
						new AddScreenAction(uiEditorTabController)
					);
				}
				OnAddScreenAction(UIEditorTabController* uiEditorTabController): uiEditorTabController(uiEditorTabController) {
				}
			private:
				UIEditorTabController* uiEditorTabController;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Add Screen", "contextmenu_add", new OnAddScreenAction(this));

			// reload screens
			class OnScreensReloadAction: public virtual Action
			{
			public:
				void performAction() override {
					//
					class ReloadScreensAction: public Action {
					private:
						UIEditorTabController* uiEditorTabController;
					public:
						ReloadScreensAction(UIEditorTabController* uiEditorTabController):
							uiEditorTabController(uiEditorTabController) {
						}
						virtual void performAction() {
							uiEditorTabController->reloadScreens();
						}
					};
					Engine::getInstance()->enqueueAction(
						new ReloadScreensAction(uiEditorTabController)
					);
				}
				OnScreensReloadAction(UIEditorTabController* uiEditorTabController): uiEditorTabController(uiEditorTabController) {
				}
			private:
				UIEditorTabController* uiEditorTabController;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Reload", "contextmenu_reload", new OnScreensReloadAction(this));

			// show
			popUps->getContextMenuScreenController()->show(mouseX, mouseY);
		} else
		if (StringTools::endsWith(outlinerNode, ".0") == true) {
			auto screenIdx = Integer::parse(StringTools::substring(outlinerNode, 0, outlinerNode.find(".")));

			// clear
			popUps->getContextMenuScreenController()->clear();

			// remove screen
			class OnScreenRemoveAction: public virtual Action
			{
			public:
				void performAction() override {
					//
					class AddScreenAction: public Action {
					private:
						UIEditorTabController* uiEditorTabController;
						int screenIdx;
					public:
						AddScreenAction(UIEditorTabController* uiEditorTabController, int screenIdx):
							uiEditorTabController(uiEditorTabController),
							screenIdx(screenIdx) {
						}
						virtual void performAction() {
							auto view = uiEditorTabController->getView();
							view->removeScreen(screenIdx);
							view->getEditorView()->reloadTabOutliner(to_string(view->getScreenNodes().size() - 1) + ".0");
						}
					};
					Engine::getInstance()->enqueueAction(
						new AddScreenAction(uiEditorTabController, screenIdx)
					);
				}
				OnScreenRemoveAction(UIEditorTabController* uiEditorTabController, int screenIdx): uiEditorTabController(uiEditorTabController), screenIdx(screenIdx) {
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

void UIEditorTabController::createOutlinerParentNodeNodesXML(TiXmlElement* xmlParentNode, string& xml, int screenIdx, int& nodeIdx) {
	if (xmlParentNode->FirstChildElement() == nullptr) {
		auto nodeId = string(AVOID_NULLPTR_STRING(xmlParentNode->Attribute("id")));
		xml+= "<selectbox-option text=\"<" + GUIParser::escapeQuotes(xmlParentNode->Value()) + ">" + (nodeId.empty() == false?string(" (") + nodeId + ")":"") + "\" value=\"" + to_string(screenIdx) + "." + GUIParser::escapeQuotes(to_string(nodeIdx++)) + "\" />\n";
	} else {
		auto nodeId = string(AVOID_NULLPTR_STRING(xmlParentNode->Attribute("id")));
		xml+= "<selectbox-parent-option text=\"<" + GUIParser::escapeQuotes(xmlParentNode->Value()) + ">" + (nodeId.empty() == false?string(" (") + nodeId + ")":"") + "\" value=\"" + to_string(screenIdx) + "." + GUIParser::escapeQuotes(to_string(nodeIdx++)) + "\" >\n";
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
	for (auto screenNode: view->getScreenNodes()) {
		if (screenNode == nullptr) {
			xml+= "<selectbox-option text=\"<screen>\" value=\"" + to_string(screenIdx) + ".0\" />\n";
			screenIdx++;
			continue;
		}
		try {
			auto screenXML = FileSystem::getInstance()->getContentAsString(
				Tools::getPathName(screenNode->getFileName()),
				Tools::getFileName(screenNode->getFileName())
			);
			TiXmlDocument xmlDocument;
			xmlDocument.Parse(screenXML.c_str());
			if (xmlDocument.Error() == true) {
				auto message = string("UIEditorTabController::setOutlinerContent(): Could not parse XML. Error='") + string(xmlDocument.ErrorDesc()) + "':\n\n" + screenXML;
				Console::println(message);
				throw GUIParserException(message);
			}
			TiXmlElement* xmlRoot = xmlDocument.RootElement();
			int nodeIdx = 0;
			createOutlinerParentNodeNodesXML(xmlRoot, xml, screenIdx, nodeIdx);
		} catch (Exception& exception) {
			showErrorPopUp("Warning", (string(exception.what())));
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
	if (StringTools::endsWith(outlinerNode, ".0") == true) {
		updateScreenDetails();
	} else {
		view->getEditorView()->setDetailsContent(string());
	}
}

void UIEditorTabController::updateScreenDetails() {
	view->getEditorView()->setDetailsContent(
		string("<template id=\"details_screen\" src=\"resources/engine/gui/template_details_screen.xml\" />\n")
	);

	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_screen"))->getActiveConditions().add("open");
	} catch (Exception& exception) {
		Console::println(string("UIEditorTabController::updateDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void UIEditorTabController::onLoadScreen() {

	class OnLoadScreen: public virtual Action
	{
	public:
		void performAction() override {
			//
			class LoadScreenAction: public Action {
			private:
				UIEditorTabController* uiEditorTabController;
				int screenIdx;
				string pathName;
				string fileName;
			public:
				LoadScreenAction(UIEditorTabController* uiEditorTabController, int screenIdx, const string& pathName, const string& fileName):
					uiEditorTabController(uiEditorTabController),
					screenIdx(screenIdx),
					pathName(pathName),
					fileName(fileName) {
				}
				virtual void performAction() {
					auto view = uiEditorTabController->getView();
					uiEditorTabController->getView()->unsetScreen(screenIdx);
					try {
						view->getScreenNodes()[screenIdx] = GUIParser::parse(pathName, fileName);
					} catch (Exception& exception) {
						Console::println(
							string() +
							"UIEditorTabController::onLoadScreen(): ReloadScreensAction::performAction(): An error occurred: " + exception.what()
						);
					}
					uiEditorTabController->getView()->reAddScreens();
					uiEditorTabController->getView()->getEditorView()->reloadTabOutliner(to_string(screenIdx) + ".0");
				}
			};
			Engine::getInstance()->enqueueAction(
				new LoadScreenAction(
					uiEditorTabController,
					screenIdx,
					uiEditorTabController->popUps->getFileDialogScreenController()->getPathName(),
					uiEditorTabController->popUps->getFileDialogScreenController()->getFileName()
				)
			);
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
	if (screenIdx < 0 || screenIdx >= view->getScreenNodes().size()) return;
	auto screenNode = view->getScreenNodes()[screenIdx];
	auto pathName = screenNode != nullptr?Tools::getPathName(screenNode->getFileName()):string();
	auto fileName = screenNode != nullptr?Tools::getFileName(screenNode->getFileName()):string();
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
	//
	class LoadScreenAction: public Action {
	private:
		UIEditorTabController* uiEditorTabController;
		int screenIdx;
	public:
		LoadScreenAction(UIEditorTabController* uiEditorTabController, int screenIdx):
			uiEditorTabController(uiEditorTabController),
			screenIdx(screenIdx) {
		}
		virtual void performAction() {
			auto view = uiEditorTabController->getView();
			uiEditorTabController->getView()->unsetScreen(screenIdx);
			uiEditorTabController->getView()->reAddScreens();
			uiEditorTabController->getView()->getEditorView()->reloadTabOutliner(to_string(screenIdx) + ".0");
		}
	};
	auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
	auto screenIdx = Integer::parse(StringTools::substring(outlinerNode, 0, outlinerNode.find(".")));
	if (screenIdx < 0 || screenIdx >= view->getScreenNodes().size()) return;
	Engine::getInstance()->enqueueAction(
		new LoadScreenAction(
			this,
			screenIdx
		)
	);
}

void UIEditorTabController::reloadScreens() {
	//
	class ReloadScreensAction: public Action {
	private:
		UIEditorTabController* uiEditorTabController;
	public:
		ReloadScreensAction(UIEditorTabController* uiEditorTabController):
			uiEditorTabController(uiEditorTabController) {
			//
		}
		virtual void performAction() {
			auto view = uiEditorTabController->getView();
			for (auto screenIdx = 0; screenIdx < view->getScreenNodes().size(); screenIdx++) {
				auto screenNode = view->getScreenNodes()[screenIdx];
				if (screenNode == nullptr) continue;
				auto fileName = screenNode->getFileName();
				view->unsetScreen(screenIdx);
				try {
					view->getScreenNodes()[screenIdx] = GUIParser::parse(
						Tools::getPathName(fileName),
						Tools::getFileName(fileName)
					);
				} catch (Exception& exception) {
					Console::println(
						string() +
						"UIEditorTabController::onLoadScreen(): ReloadScreensAction::performAction(): An error occurred: " + exception.what()
					);
				}
			}
			view->reAddScreens();
			view->getEditorView()->reloadTabOutliner("screens");
		}
	};
	Engine::getInstance()->enqueueAction(new ReloadScreensAction(this));
}

void UIEditorTabController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
	if (type != GUIActionListenerType::PERFORMED) return;
	Console::println("UIEditorTabController::onActionPerformed(): " + node->getId());
	if (node->getId() == "screen_open") {
		onLoadScreen();
	} else
	if (node->getId() == "screen_remove") {
		onUnsetScreen();
	} else
	if (node->getId() == "screen_browseto") {
	}
}
