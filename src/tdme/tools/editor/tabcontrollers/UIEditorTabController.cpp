#include <tdme/tools/editor/tabcontrollers/UIEditorTabController.h>

#include <string>

#include <tdme/tdme.h>
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
	showInfoPopUp("Warning", "This command is not supported yet");
}

void UIEditorTabController::onDrop(const string& payload, int mouseX, int mouseY) {
	/*
	 * uiEditorTabController->setPrototype(pathName, fileName, uiEditorTabController->prototypeMeshNode, uiEditorTabController->prototypeMeshAnimation);
	 */
	Console::println("UIEditorTabController::onDrop(): " + payload + " @ " + to_string(mouseX) + ", " + to_string(mouseY));
	if (StringTools::startsWith(payload, "file:") == false) {
		showInfoPopUp("Warning", "Unknown payload in drop");
	} else
	if (view->getEditorView()->getScreenController()->isDropOnNode(mouseX, mouseY, "screen") == true) {
		auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
		auto screenIdx = Integer::parse(StringTools::substring(outlinerNode, 0, outlinerNode.find(".")));
		setScreen(screenIdx, StringTools::substring(payload, string("file:").size()));
	} else
	if (view->getEditorView()->getScreenController()->isDropOnNode(mouseX, mouseY, "projectedui_prototype") == true) {
		auto modelFileName = StringTools::substring(payload, string("file:").size());
		setPrototype(
			Tools::getPathName(modelFileName),
			Tools::getFileName(modelFileName),
			prototypeMeshNode,
			prototypeMeshAnimation
		);
	} else {
		showInfoPopUp("Warning", "You can not drop a file here");
	}
}

void UIEditorTabController::showInfoPopUp(const string& caption, const string& message)
{
	popUps->getInfoDialogScreenController()->show(caption, message);
}

void UIEditorTabController::onChange(GUIElementNode* node)
{
	Console::println("UIEditorTabController::onChange(): " + node->getId() + " = " + node->getController()->getValue().getString());
	if (node->getId() == "selectbox_outliner") {
		updateDetails(node->getController()->getValue().getString());
	} else
	if (node->getId() == "dropdown_outliner_add") {
		auto addOutlinerType = node->getController()->getValue().getString();
		if (addOutlinerType == "screen") {
			view->addScreen();
			view->getEditorView()->reloadTabOutliner(to_string(view->getScreenNodes().size() - 1) + ".0");
		}
	} else
	if (node->getId() == "projectedui_meshnode") {
		prototypeMeshNode = node->getController()->getValue().getString();
		view->setModelMeshNode(prototypeMeshNode);
	} else
	if (node->getId() == "projectedui_animation") {
		prototypeMeshAnimation = node->getController()->getValue().getString();
		view->setModelMeshAnimation(prototypeMeshAnimation);
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

void UIEditorTabController::onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) {
	int left, top;
	view->getEditorView()->getViewPortUnscaledOffset(left, top);
	popUps->getTooltipScreenController()->show(left + mouseX, top + mouseY, node->getToolTip());
}

void UIEditorTabController::onTooltipCloseRequest() {
	popUps->getTooltipScreenController()->close();
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
			showInfoPopUp("Warning", (string(exception.what())));
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
			screenIdx < view->getScreenNodes().size() &&
			view->getScreenNodes()[screenIdx] != nullptr &&
			view->getScreenNodes()[screenIdx]->getFileName().empty() == false) {
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("screen"))->setSource("resources/engine/images/gui_big.png");
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("screen"))->setTooltip(view->getScreenNodes()[screenIdx]->getFileName());
		}
	} catch (Exception& exception) {
		Console::println(string("UIEditorTabController::updateScreenDetails(): An error occurred: ") + exception.what());;
		showInfoPopUp("Warning", (string(exception.what())));
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
		Console::println(string("UIEditorTabController::updateScreensDetails(): An error occurred: ") + exception.what());;
		showInfoPopUp("Warning", (string(exception.what())));
	}

	//
	auto model = view->getPrototype() != nullptr?view->getPrototype()->getModel():nullptr;

	{
		string modelMeshNodesXML;
		modelMeshNodesXML =
			modelMeshNodesXML +
			"<dropdown-option text=\"<None>\" value=\"\" " + (modelMeshNodesXML.empty() == true?"selected=\"true\" ":"") + " />\n";
		if (model != nullptr) {
			for (auto& it: model->getNodes()) {
				auto& nodeId = it.second->getId();
				modelMeshNodesXML+=
					"<dropdown-option text=\"" +
					GUIParser::escapeQuotes(nodeId) +
					"\" value=\"" +
					GUIParser::escapeQuotes(nodeId) +
					"\" " +
					(modelMeshNodesXML == nodeId?"selected=\"true\" ":"") +
					" />\n";
			}
		}
		try {
			required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("projectedui_meshnode_scrollarea"))->replaceSubNodes(modelMeshNodesXML, true);
		} catch (Exception& exception) {
			Console::print(string("UIEditorTabController::updateScreensDetails(): An error occurred: "));
			Console::println(string(exception.what()));
		}
	}

	{
		string animationsXML;
		animationsXML = animationsXML + "<dropdown-option text=\"<No animation>\" value=\"\" selected=\"true\" />";
		if (model != nullptr) {
			for (auto it: model->getAnimationSetups()) {
				auto animationSetup = it.second;
				if (animationSetup->isOverlayAnimationSetup() == true) continue;
				animationsXML =
					animationsXML + "<dropdown-option text=\"" +
					GUIParser::escapeQuotes(animationSetup->getId()) +
					"\" value=\"" +
					GUIParser::escapeQuotes(animationSetup->getId()) +
					"\" " +
					" />\n";
			}
		}
		try {
			required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("projectedui_animation_scrollarea"))->replaceSubNodes(animationsXML, true);
		} catch (Exception& exception) {
			Console::print(string("ModelEditorTabController::setAnimationPreviewDetails(): An error occurred: "));
			Console::println(string(exception.what()));
		}
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
					uiEditorTabController->setScreen(
						screenIdx,
						pathName + "/" + fileName
					);
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
	class UnsetScreenAction: public Action {
	private:
		UIEditorTabController* uiEditorTabController;
		int screenIdx;
	public:
		UnsetScreenAction(UIEditorTabController* uiEditorTabController, int screenIdx):
			uiEditorTabController(uiEditorTabController),
			screenIdx(screenIdx) {
		}
		virtual void performAction() {
			auto view = uiEditorTabController->getView();
			view->unsetScreen(screenIdx);
			view->reAddScreens();
			view->getEditorView()->reloadTabOutliner(to_string(screenIdx) + ".0");
		}
	};
	auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
	auto screenIdx = Integer::parse(StringTools::substring(outlinerNode, 0, outlinerNode.find(".")));
	if (screenIdx < 0 || screenIdx >= view->getScreenNodes().size()) return;
	Engine::getInstance()->enqueueAction(
		new UnsetScreenAction(
			this,
			screenIdx
		)
	);
}

void UIEditorTabController::onBrowseToScreen() {
	auto outlinerNode = view->getEditorView()->getScreenController()->getOutlinerSelection();
	auto screenIdx = Integer::parse(StringTools::substring(outlinerNode, 0, outlinerNode.find(".")));
	if (screenIdx < 0 || screenIdx >= view->getScreenNodes().size()) {
		showInfoPopUp("Browse To", "Nothing to browse to");
	} else {
		view->getEditorView()->getScreenController()->browseTo(view->getScreenNodes()[screenIdx]->getFileName());
	}
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
					view->setScreen(
						screenIdx,
						GUIParser::parse(
							Tools::getPathName(fileName),
							Tools::getFileName(fileName)
						)
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

void UIEditorTabController::onLoadPrototype() {
	Console::println("UIEditorTabController::onLoadPrototype()");
	class OnLoadPrototype: public virtual Action
	{
	public:
		void performAction() override {
			//
			class LoadPrototypeAction: public Action {
			private:
				UIEditorTabController* uiEditorTabController;
				string pathName;
				string fileName;
			public:
				LoadPrototypeAction(UIEditorTabController* uiEditorTabController, const string& pathName, const string& fileName):
					uiEditorTabController(uiEditorTabController),
					pathName(pathName),
					fileName(fileName) {
				}
				virtual void performAction() {
					uiEditorTabController->setPrototype(pathName, fileName, uiEditorTabController->prototypeMeshNode, uiEditorTabController->prototypeMeshAnimation);
				}
			};
			Engine::getInstance()->enqueueAction(
				new LoadPrototypeAction(
					uiEditorTabController,
					uiEditorTabController->popUps->getFileDialogScreenController()->getPathName(),
					uiEditorTabController->popUps->getFileDialogScreenController()->getFileName()
				)
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
		{ "tmodel" },
		fileName,
		true,
		new OnLoadPrototype(this)
	);
}

void UIEditorTabController::onRemovePrototype() {
	Console::println("UIEditorTabController::onRemoveModel()");
	//
	class RemovePrototypeAction: public Action {
	private:
		UIEditorTabController* uiEditorTabController;
	public:
		RemovePrototypeAction(UIEditorTabController* uiEditorTabController): uiEditorTabController(uiEditorTabController) {
		}
		virtual void performAction() {
			auto view = uiEditorTabController->getView();
			uiEditorTabController->prototypeFileName.clear();
			view->removePrototype();
			view->reAddScreens();
			view->getEditorView()->reloadTabOutliner("screens");
		}
	};
	Engine::getInstance()->enqueueAction(new RemovePrototypeAction(this));
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
	Console::println("UIEditorTabController::onAction(): " + node->getId());
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
		view->setScreen(screenIdx, GUIParser::parse(Tools::getPathName(fileName), Tools::getFileName(fileName)));
	} catch (Exception& exception) {
		Console::println(
			string() +
			"UIEditorTabController::setScreen(): An error occurred: " + exception.what()
		);
		showInfoPopUp("Error", string() + "An error occurred: " + exception.what());
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
