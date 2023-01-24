#include <tdme/tools/editor/controllers/EditorScreenController.h>

#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/audio/VorbisAudioStream.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/fileio/prototypes/PrototypeWriter.h>
#include <tdme/engine/fileio/scenes/SceneReader.h>
#include <tdme/engine/fileio/scenes/SceneWriter.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/fileio/textures/PNGTextureReader.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/Prototype_Type.h>
#include <tdme/engine/prototype/PrototypeBoundingVolume.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/elements/GUISelectBoxController.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIImageNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/math/Matrix2D3x3.h>
#include <tdme/os/filesystem/FileNameFilter.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/tools/editor/controllers/AboutDialogScreenController.h>
#include <tdme/tools/editor/controllers/ContextMenuScreenController.h>
#include <tdme/tools/editor/controllers/DraggingScreenController.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/controllers/ProgressBarScreenController.h>
#include <tdme/tools/editor/controllers/TooltipScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabviews/DecalEditorTabView.h>
#include <tdme/tools/editor/tabviews/EmptyEditorTabView.h>
#include <tdme/tools/editor/tabviews/EnvMapEditorTabView.h>
#include <tdme/tools/editor/tabviews/FontTabView.h>
#include <tdme/tools/editor/tabviews/ModelEditorTabView.h>
#include <tdme/tools/editor/tabviews/ParticleSystemEditorTabView.h>
#include <tdme/tools/editor/tabviews/SceneEditorTabView.h>
#include <tdme/tools/editor/tabviews/SoundTabView.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/tabviews/TerrainEditorTabView.h>
#include <tdme/tools/editor/tabviews/TextureTabView.h>
#include <tdme/tools/editor/tabviews/TextEditorTabView.h>
#include <tdme/tools/editor/tabviews/TriggerEditorTabView.h>
#include <tdme/tools/editor/tabviews/UIEditorTabView.h>
#include <tdme/tools/editor/tabviews/VideoTabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/TDMEEditor.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/Properties.h>
#include <tdme/utilities/StringTools.h>

using std::remove;
using std::string;
using std::unordered_set;
using std::vector;

using tdme::audio::VorbisAudioStream;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::fileio::prototypes::PrototypeWriter;
using tdme::engine::fileio::scenes::SceneReader;
using tdme::engine::fileio::scenes::SceneWriter;
using tdme::engine::Texture;
using tdme::engine::fileio::textures::PNGTextureReader;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::Prototype_Type;
using tdme::engine::prototype::PrototypeBoundingVolume;
using tdme::engine::scene::Scene;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::gui::elements::GUISelectBoxController;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIImageNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::GUIParser;
using tdme::math::Matrix2D3x3;
using tdme::os::filesystem::FileNameFilter;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::os::threading::Mutex;
using tdme::os::threading::Thread;
using tdme::tools::editor::controllers::AboutDialogScreenController;
using tdme::tools::editor::controllers::ContextMenuScreenController;
using tdme::tools::editor::controllers::DraggingScreenController;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::controllers::ProgressBarScreenController;
using tdme::tools::editor::controllers::TooltipScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::DecalEditorTabView;
using tdme::tools::editor::tabviews::EmptyEditorTabView;
using tdme::tools::editor::tabviews::EnvMapEditorTabView;
using tdme::tools::editor::tabviews::FontTabView;
using tdme::tools::editor::tabviews::ModelEditorTabView;
using tdme::tools::editor::tabviews::ParticleSystemEditorTabView;
using tdme::tools::editor::tabviews::SceneEditorTabView;
using tdme::tools::editor::tabviews::SoundTabView;
using tdme::tools::editor::tabviews::TabView;
using tdme::tools::editor::tabviews::TerrainEditorTabView;
using tdme::tools::editor::tabviews::TextureTabView;
using tdme::tools::editor::tabviews::TextEditorTabView;
using tdme::tools::editor::tabviews::TriggerEditorTabView;
using tdme::tools::editor::tabviews::UIEditorTabView;
using tdme::tools::editor::tabviews::VideoTabView;
using tdme::tools::editor::views::EditorView;
using tdme::tools::editor::TDMEEditor;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::MutableString;
using tdme::utilities::Properties;
using tdme::utilities::StringTools;

EditorScreenController::EditorScreenController(EditorView* view): fileEntitiesMutex("fileentities-mutex")
{
	this->view = view;
}

EditorScreenController::~EditorScreenController()
{
	// TODO
}

GUIScreenNode* EditorScreenController::getScreenNode()
{
	return screenNode;
}

void EditorScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse("resources/engine/gui", "screen_editor.xml");
		screenNode->addActionListener(this);
		screenNode->addChangeListener(this);
		screenNode->addFocusListener(this);
		screenNode->addContextMenuRequestListener(this);
		screenNode->addTooltipRequestListener(this);
		screenNode->addDragRequestListener(this);
		projectPathsScrollArea = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("selectbox_projectpaths_scrollarea"));
		projectPathFilesScrollArea = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("selectbox_projectpathfiles_scrollarea"));
		tabs = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("tabs"));
		tabsHeader = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("tabs-header"));
		tabsContent = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("tabs-content"));
		outliner = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("selectbox_outliner"));
		outlinerScrollarea = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("selectbox_outliner_scrollarea"));
		detailsScrollarea = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("selectbox_details_scrollarea"));
		outlinerAddDropDown = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("dropdown_outliner_add"));

		//
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("projectlibrary_import"))->getController()->setDisabled(true);
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("projectpathfiles_search"))->getController()->setDisabled(true);
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("projectpaths_search"))->getController()->setDisabled(true);
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("dropdown_projectlibrary_add"))->getController()->setDisabled(true);
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("dropdown_outliner_add"))->getController()->setDisabled(true);
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("outliner_search"))->getController()->setDisabled(true);

		//
		updateFullScreenMenuEntry();
		disableSceneMenuEntry();
	} catch (Exception& exception) {
		Console::print(string("EditorScreenController::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void EditorScreenController::dispose()
{
	stopScanFiles();
}

void EditorScreenController::setScreenCaption(const string& text)
{
}

void EditorScreenController::onQuit()
{
	TDMEEditor::getInstance()->quit();
}

void EditorScreenController::showInfoPopUp(const string& caption, const string& message)
{
	view->getPopUps()->getInfoDialogScreenController()->show(caption, message);
}

void EditorScreenController::onChange(GUIElementNode* node)
{
	if (node->getId() == "projectpathfiles_search") {
		fileNameSearchTerm = node->getController()->getValue().getString();
		timeFileNameSearchTerm = Time::getCurrentMillis();
	} else
	if (node->getId() == "selectbox_projectpaths") {
		stopScanFiles();
		resetScanFiles();
		relativeProjectPath = node->getController()->getValue().getString();
		startScanFiles();
	} else
	if (node->getId() == "dropdown_projectlibrary_add") {
		onAddFile(node->getController()->getValue().getString());
	}
	// forward onChange to active tab tab controller
	auto selectedTab = getSelectedTab();
	if (selectedTab != nullptr) selectedTab->getTabView()->getTabController()->onChange(node);
}

void EditorScreenController::onAction(GUIActionListenerType type, GUIElementNode* node)
{
	if (type == GUIActionListenerType::PERFORMED) {
		if (node->getId() == "menu_file_open") {
			onOpenProject();
		} else
		if (node->getId() == "menu_file_save") {
			auto selectedTab = getSelectedTab();
			if (selectedTab != nullptr) selectedTab->getTabView()->getTabController()->onCommand(TabController::COMMAND_SAVE);
		} else
		if (node->getId() == "menu_file_saveas") {
			auto selectedTab = getSelectedTab();
			if (selectedTab != nullptr) selectedTab->getTabView()->getTabController()->onCommand(TabController::COMMAND_SAVEAS);
		} else
		if (node->getId() == "menu_file_saveall") {
			// forward saveAs to active tab tab controller
			for (auto& tabViewIt: tabViews) {
				auto& tab = tabViewIt.second;
				tab.getTabView()->getTabController()->onCommand(TabController::COMMAND_SAVE);
			}
		} else
		if (node->getId() == "menu_edit_undo") {
			auto selectedTab = getSelectedTab();
			if (selectedTab != nullptr) selectedTab->getTabView()->getTabController()->onCommand(TabController::COMMAND_UNDO);
		} else
		if (node->getId() == "menu_edit_redo") {
			auto selectedTab = getSelectedTab();
			if (selectedTab != nullptr) selectedTab->getTabView()->getTabController()->onCommand(TabController::COMMAND_REDO);
		} else
		if (node->getId() == "menu_edit_cut") {
			auto selectedTab = getSelectedTab();
			if (selectedTab != nullptr) selectedTab->getTabView()->getTabController()->onCommand(TabController::COMMAND_CUT);
		} else
		if (node->getId() == "menu_edit_copy") {
			auto selectedTab = getSelectedTab();
			if (selectedTab != nullptr) selectedTab->getTabView()->getTabController()->onCommand(TabController::COMMAND_COPY);
		} else
		if (node->getId() == "menu_edit_paste") {
			auto selectedTab = getSelectedTab();
			if (selectedTab != nullptr) selectedTab->getTabView()->getTabController()->onCommand(TabController::COMMAND_PASTE);
		} else
		if (node->getId() == "menu_edit_delete") {
			auto selectedTab = getSelectedTab();
			if (selectedTab != nullptr) selectedTab->getTabView()->getTabController()->onCommand(TabController::COMMAND_DELETE);
		} else
		if (node->getId() == "menu_edit_selectall") {
			auto selectedTab = getSelectedTab();
			if (selectedTab != nullptr) selectedTab->getTabView()->getTabController()->onCommand(TabController::COMMAND_SELECTALL);
		} else
		if (node->getId() == "menu_edit_findreplace") {
			auto selectedTab = getSelectedTab();
			if (selectedTab != nullptr) selectedTab->getTabView()->getTabController()->onCommand(TabController::COMMAND_FINDREPLACE);
		} else
		if (node->getId() == "menu_view_fullscreen") {
			setFullScreen(isFullScreen() == false?true:false);
		} else
		if (node->getId() == "menu_help_about") {
			view->getPopUps()->getAboutDialogScreenController()->show();
		} else
		if (StringTools::startsWith(node->getId(), "projectpathfiles_file_") == true) {
			onOpenFile(required_dynamic_cast<GUIElementNode*>(node)->getValue());
		} else
		if (StringTools::startsWith(node->getId(), "tab_viewport_") == true) {
			string tabIdToClose;
			for (auto& tabsIt: tabViews) {
				auto& tab = tabsIt.second;
				if (StringTools::startsWith(node->getId(), tab.getId() + "_close") == true) {
					tabIdToClose = tab.getId();
					Console::println("EditorScreenController::onAction(): close tab: " + tab.getId());
				}
			}
			if (tabIdToClose.empty() == false) {
				//
				class CloseTabAction: public Action {
				private:
					EditorScreenController* editorScreenController;
					string tabIdToClose;
				public:
					CloseTabAction(EditorScreenController* editorScreenController, const string& tabIdToClose): editorScreenController(editorScreenController), tabIdToClose(tabIdToClose) {}
					virtual void performAction() {
						editorScreenController->screenNode->removeNodeById(tabIdToClose, false);
						editorScreenController->screenNode->removeNodeById(tabIdToClose + "-content", false);
						auto tabIt = editorScreenController->tabViews.find(tabIdToClose);
						if (tabIt == editorScreenController->tabViews.end()) {
							Console::println("CloseTabAction::performAction(): close tab: " + tabIdToClose + ": not found");
						} else {
							auto& tab = tabIt->second;
							tab.getTabView()->dispose();
							delete tab.getTabView();
							editorScreenController->tabViews.erase(tabIt);
						}
						editorScreenController->setDetailsContent(string());
						editorScreenController->setOutlinerContent(string());
						//
						editorScreenController->updateFullScreenMenuEntry();
					}
				};
				Engine::getInstance()->enqueueAction(new CloseTabAction(this, tabIdToClose));
			}
		} else
		if (node->getId() == "menu_file_quit") {
			TDMEEditor::getInstance()->quit();
		}
	}
	// forward onAction to active tab tab controller
	auto selectedTab = getSelectedTab();
	if (selectedTab != nullptr) selectedTab->getTabView()->getTabController()->onAction(type, node);
}

void EditorScreenController::onFocus(GUIElementNode* node) {
	// forward onFocus to active tab tab controller
	auto selectedTab = getSelectedTab();
	if (selectedTab != nullptr) selectedTab->getTabView()->getTabController()->onFocus(node);
}

void EditorScreenController::onUnfocus(GUIElementNode* node) {
	// forward onFocus to active tab tab controller
	auto selectedTab = getSelectedTab();
	if (selectedTab != nullptr) selectedTab->getTabView()->getTabController()->onUnfocus(node);
}

void EditorScreenController::onContextMenuRequest(GUIElementNode* node, int mouseX, int mouseY) {
	if (StringTools::startsWith(node->getId(), "projectpathfiles_file_") == true) {
		auto absoluteFileName = required_dynamic_cast<GUIElementNode*>(node)->getValue();
		auto selectedTab = getSelectedTab();
		if (selectedTab == nullptr) return;
		switch (selectedTab->getType()) {
			case EditorTabView::TABTYPE_MODELEDITOR:
				break;
			case EditorTabView::TABTYPE_SCENEEDITOR:
				{
					// clear
					view->getPopUps()->getContextMenuScreenController()->clear();

					// load
					class OnAddToSceneAction: public virtual Action
					{
					public:
						void performAction() override {
							auto currentTab = editorScreenController->getSelectedTab();
							if (currentTab == nullptr) return;
							SceneEditorTabView* sceneEditorTabView = dynamic_cast<SceneEditorTabView*>(currentTab->getTabView());
							if (sceneEditorTabView == nullptr) return;
							try {
								auto prototype = PrototypeReader::read(
									Tools::getPathName(absoluteFileName),
									Tools::getFileName(absoluteFileName)
								);
								sceneEditorTabView->addPrototype(prototype);
							} catch (Exception& exception) {
								Console::println(string("OnAddToSceneAction::performAction(): An error occurred: ") + exception.what());;
								editorScreenController->showInfoPopUp("Warning", (string(exception.what())));
							}
						}
						OnAddToSceneAction(EditorScreenController* editorScreenController, const string& absoluteFileName): editorScreenController(editorScreenController), absoluteFileName(absoluteFileName) {
						}
					private:
						EditorScreenController* editorScreenController;
						string absoluteFileName;
					};
					view->getPopUps()->getContextMenuScreenController()->addMenuItem("Add to scene", "contextmenu_addtoscene", new OnAddToSceneAction(this, absoluteFileName));

					//
					view->getPopUps()->getContextMenuScreenController()->show(mouseX, mouseY);
				}
				break;
			case EditorTabView::TABTYPE_TEXTURE:
				break;
			case EditorTabView::TABTYPE_FONT:
				break;
			case EditorTabView::TABTYPE_UIEDITOR:
				break;
			default: break;
		}
	}
	// forward onContextMenuRequest to active tab tab controller
	auto selectedTab = getSelectedTab();
	if (selectedTab != nullptr) selectedTab->getTabView()->getTabController()->onContextMenuRequest(node, mouseX, mouseY);
}

void EditorScreenController::onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) {
	//
	view->getPopUps()->getTooltipScreenController()->show(mouseX, mouseY, node->getToolTip());
}

void EditorScreenController::onTooltipCloseRequest() {
	view->getPopUps()->getTooltipScreenController()->close();
}

void EditorScreenController::onDragRequest(GUIElementNode* node, int mouseX, int mouseY) {
	if (StringTools::startsWith(node->getId(), "projectpathfiles_file_") == true) {
		//
		class OnDragReleaseAction: public Action {
		private:
			EditorScreenController* editorScreenController;
		public:
			OnDragReleaseAction(EditorScreenController* editorScreenController): editorScreenController(editorScreenController) {}
			virtual void performAction() {
				auto draggingScreenController = editorScreenController->view->getPopUps()->getDraggingScreenController();
				Console::println(
					"OnDragReleaseAction::performAction(): payload: " +
					draggingScreenController->getPayload() + " @ " +
					to_string(draggingScreenController->getDragReleaseMouseX()) + ", " +
					to_string(draggingScreenController->getDragReleaseMouseY())
				);
				auto selectedTab = editorScreenController->getSelectedTab();
				if (selectedTab == nullptr) {
					editorScreenController->showInfoPopUp("Warning", "No tab opened to drop files into");
				} else {
					selectedTab->getTabView()->getTabController()->onDrop(
						draggingScreenController->getPayload(),
						draggingScreenController->getDragReleaseMouseX(),
						draggingScreenController->getDragReleaseMouseY()
					);
				}
			}
		};
		//
		auto relativeFileName = getRelativePath(node->getValue());
		auto imageSource = GUIParser::getEngineThemeProperties()->get("icon.type_" + FileDialogScreenController::getFileImageName(relativeFileName) + "_big", "resources/engine/images/tdme_big.png");
		auto xml = "<image width=\"auto\" height=\"auto\" src=\"" + imageSource + "\" />";
		view->getPopUps()->getDraggingScreenController()->start(mouseX, mouseY, xml, "file:" + relativeFileName, new OnDragReleaseAction(this));
	}
}

void EditorScreenController::openProject(const string& path) {
	projectPath = path;
	if (StringTools::endsWith(projectPath, "/") == true) {
		projectPath = StringTools::substring(projectPath, 0, projectPath.size() - 1);
	}
	Console::println("EditorScreenController::openProject(): " + projectPath);
	closeProject();
	view->getPopUps()->getFileDialogScreenController()->setDefaultCWD(projectPath);
	scanProjectPaths();
	setRelativeProjectPath("resources");
	startScanFiles();
	//
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("projectlibrary_import"))->getController()->setDisabled(false);
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("projectpathfiles_search"))->getController()->setDisabled(false);
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("projectpaths_search"))->getController()->setDisabled(false);
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("dropdown_projectlibrary_add"))->getController()->setDisabled(false);
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("dropdown_outliner_add"))->getController()->setDisabled(false);
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("outliner_search"))->getController()->setDisabled(false);
	//
	GUIParser::loadProjectThemeProperties(projectPath);
}

void EditorScreenController::onOpenProject() {
	class OnOpenProject: public virtual Action
	{
	public:
		// overridden methods
		void performAction() override {
			auto projectPath = editorScreenController->view->getPopUps()->getFileDialogScreenController()->getPathName();
			editorScreenController->openProject(projectPath);
			editorScreenController->view->getPopUps()->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param editorScreenController editor screen controller
		 */
		OnOpenProject(EditorScreenController* editorScreenController): editorScreenController(editorScreenController) {
		}

	private:
		EditorScreenController* editorScreenController;
	};

	view->getPopUps()->getFileDialogScreenController()->show(
		string(),
		"Open project from folder: ",
		{},
		string(),
		true,
		new OnOpenProject(this),
		nullptr,
		".projects.filedialog.properties",
		"."
	);
}

void EditorScreenController::scanProjectPaths() {
	string xml;
	xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("resources") + "\" value=\"" + GUIParser::escapeQuotes("resources") + "\">\n";
	scanProjectPaths(projectPath + "/resources", xml);
	xml+= "</selectbox-parent-option>\n";
	xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("shader") + "\" value=\"" + GUIParser::escapeQuotes("shader") + "\">\n";
	scanProjectPaths(projectPath + "/shader", xml);
	xml+= "</selectbox-parent-option>\n";
	xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("src") + "\" value=\"" + GUIParser::escapeQuotes("src") + "\">\n";
	scanProjectPaths(projectPath + "/src", xml);
	xml+= "</selectbox-parent-option>\n";
	try {
		required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(projectPathsScrollArea->getId()))->replaceSubNodes(xml, true);
	} catch (Exception& exception) {
		Console::print(string("EditorScreenController::scanProjectPaths(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void EditorScreenController::scanProjectPaths(const string& path, string& xml) {
	class ListFilter : public virtual FileNameFilter {
		public:
			virtual ~ListFilter() {}

			bool accept(const string& pathName, const string& fileName) override {
				if (fileName == ".") return false;
				if (fileName == "..") return false;
				if (FileSystem::getInstance()->isPath(pathName + "/" + fileName) == true) return true;
				//
				return false;
			}
	};

	ListFilter listFilter;
	vector<string> files;

	if (FileSystem::getInstance()->fileExists(path) == false) {
		Console::println("EditorScreenController::scanProject(): Error: file does not exist: " + path);
	} else
	if (FileSystem::getInstance()->isPath(path) == false) {
		if (listFilter.accept(".", path) == true) {
			Console::println("EditorScreenController::scanProject(): Error: path is file" + path);
		} else {
			Console::println("EditorScreenController::scanProject(): Error: file exist, but does not match filter: " + path);
		}
	} else {
		FileSystem::getInstance()->list(path, files, &listFilter);
		for (auto fileName: files) {
			auto relativePath = path + "/" + fileName;
			if (StringTools::startsWith(relativePath, projectPath)) relativePath = StringTools::substring(relativePath, projectPath.size() + 1, relativePath.size());
			if (FileSystem::getInstance()->isPath(path + "/" + fileName) == false) {
				// no op for now
			} else {
				string innerXml;
				scanProjectPaths(path + "/" + fileName, innerXml);
				if (innerXml.empty() == false) {
					xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes(fileName) + "\" value=\"" + GUIParser::escapeQuotes(relativePath) + "\">\n";
					xml+= innerXml;
					xml+= "</selectbox-parent-option>\n";
				} else {
					xml+= "<selectbox-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes(fileName) + "\" value=\"" + GUIParser::escapeQuotes(relativePath) + "\" />\n";
				}
			}
		}
	}
}

void EditorScreenController::closeTabs() {
	for (auto& tabsIt: tabViews) {
		auto& tab = tabsIt.second;
		screenNode->removeNodeById(tab.getId(), false);
		screenNode->removeNodeById(tab.getId() + "-content", false);
		tab.getTabView()->dispose();
		delete tab.getTabView();
	}
	tabViews.clear();
	setDetailsContent(string());
	setOutlinerContent(string());
	//
	updateFullScreenMenuEntry();
}

void EditorScreenController::closeProject() {
	stopScanFiles();
	resetScanFiles();
	view->getPopUps()->getFileDialogScreenController()->setDefaultCWD(string());
	closeTabs();
	clearProjectPathFiles();
	//
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("projectlibrary_import"))->getController()->setDisabled(true);
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("projectpathfiles_search"))->getController()->setDisabled(true);
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("projectpaths_search"))->getController()->setDisabled(true);
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("dropdown_projectlibrary_add"))->getController()->setDisabled(true);
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("dropdown_outliner_add"))->getController()->setDisabled(true);
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("outliner_search"))->getController()->setDisabled(true);
}

void EditorScreenController::clearProjectPathFiles() {
	required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(projectPathFilesScrollArea->getId()))->clearSubNodes();
}

void EditorScreenController::startScanFiles() {
	stopScanFiles();
	try {
		required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(projectPathFilesScrollArea->getId()))->clearSubNodes();
	} catch (Exception& exception) {
		Console::print(string("EditorScreenController::startScanFiles(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	Console::println("EditorScreenController::startScanFiles()");
	scanFilesThread = new ScanFilesThread(this, projectPath + "/" + relativeProjectPath, StringTools::toLowerCase(fileNameSearchTerm));
	scanFilesThread->start();
}

void EditorScreenController::addPendingFileEntities() {
	string scrollToNodeId;
	string xml;
	xml+= "<layout alignment=\"horizontal\">\n";
	for (auto pendingFileEntity: pendingFileEntities) {
		xml+= pendingFileEntity->buttonXML;
		if (pendingFileEntity->scrollTo == true) scrollToNodeId = pendingFileEntity->id;
	}
	xml+= "</layout>\n";
	//
	try {
		required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(projectPathFilesScrollArea->getId()))->addSubNodes(xml, false);
		if (scrollToNodeId.empty() == false) {
			required_dynamic_cast<GUINode*>(screenNode->getNodeById(scrollToNodeId))->scrollToNodeX();
			required_dynamic_cast<GUINode*>(screenNode->getNodeById(scrollToNodeId))->scrollToNodeY();
		}
	} catch (Exception& exception) {
		Console::print(string("EditorScreenController::addPendingFileEntities(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	//
	for (auto pendingFileEntity: pendingFileEntities) {
		if (pendingFileEntity->thumbnailTexture == nullptr) continue;
		if (screenNode->getNodeById(pendingFileEntity->id + "_texture_normal") == nullptr) continue;
		try {
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById(pendingFileEntity->id + "_texture_normal"))->setTexture(pendingFileEntity->thumbnailTexture);
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById(pendingFileEntity->id + "_texture_mouseover"))->setTexture(pendingFileEntity->thumbnailTexture);
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById(pendingFileEntity->id + "_texture_clicked"))->setTexture(pendingFileEntity->thumbnailTexture);
		} catch (Exception& exception) {
			Console::print(string("EditorScreenController::addPendingFileEntities(): An error occurred: "));
			Console::println(string(exception.what()));
		}
		if (pendingFileEntity->thumbnailTexture != nullptr) pendingFileEntity->thumbnailTexture->releaseReference();
		delete pendingFileEntity;
	}
	pendingFileEntities.clear();
}

void EditorScreenController::setRelativeProjectPath(const string& relativeProjectPath) {
	this->relativeProjectPath = relativeProjectPath;
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("selectbox_projectpaths"))->getController()->setValue(MutableString(relativeProjectPath));
}

void EditorScreenController::stopScanFiles() {
	Console::println("EditorScreenController::stopScanFiles()");
	if (scanFilesThread != nullptr) {
		scanFilesThread->stop();
		scanFilesThread->join();
		lockFileEntities();
		for (auto fileEntity: getFileEntities()) {
			if (fileEntity->thumbnailTexture != nullptr) fileEntity->thumbnailTexture->releaseReference();
			delete fileEntity;
		}
		getFileEntities().clear();
		unlockFileEntities();
		delete scanFilesThread;
		scanFilesThread = nullptr;
	}
}

void EditorScreenController::resetScanFiles() {
	Console::println("EditorScreenController::resetScanFiles()");
	fileNameSearchTerm.clear();
	browseToFileName.clear();
	timeFileNameSearchTerm = -1LL;
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("projectpathfiles_search"))->getController()->setValue(MutableString());
}

void EditorScreenController::browseTo(const string& fileName) {
	Console::println("EditorScreenController::browseTo(): " + fileName);
	stopScanFiles();
	resetScanFiles();
	auto newRelativeProjectPath = Tools::getPathName(fileName);
	if (StringTools::startsWith(newRelativeProjectPath, projectPath) == true) newRelativeProjectPath = StringTools::substring(newRelativeProjectPath, projectPath.size() + 1);
	browseToFileName = projectPath + "/" + newRelativeProjectPath + "/" + Tools::getFileName(fileName);
	Console::println("EditorScreenController::browseTo(): relative project path: " + newRelativeProjectPath + ", filename = " + browseToFileName);
	setRelativeProjectPath(newRelativeProjectPath);
	startScanFiles();
}

void EditorScreenController::ScanFilesThread::run() {
	class ListFilter : public virtual FileNameFilter {
		public:
			ListFilter(const string& searchTerm): searchTerm(searchTerm) {}
			virtual ~ListFilter() {}

			bool accept(const string& pathName, const string& fileName) override {
				if (fileName == ".") return false;
				if (fileName == "..") return false;
				//
				auto fileNameLowerCase = StringTools::toLowerCase(fileName);
				//
				if (searchTerm.empty() == false && fileNameLowerCase.find(searchTerm) == string::npos) return false;

				// folders
				if (FileSystem::getInstance()->isPath(pathName + "/" + fileName) == true) return true;
				// audio
				if (StringTools::endsWith(fileNameLowerCase, ".ogg") == true) return true;
				// markdown
				if (StringTools::endsWith(fileNameLowerCase, ".md") == true) return true;
				// license
				if (fileNameLowerCase == "license") return true;
				// code
				if (StringTools::endsWith(fileNameLowerCase, ".h") == true) return true;
				if (StringTools::endsWith(fileNameLowerCase, ".cpp") == true) return true;
				if (StringTools::endsWith(fileNameLowerCase, ".c") == true) return true;
				if (StringTools::endsWith(fileNameLowerCase, ".tscript") == true) return true;
				// fonts
				if (StringTools::endsWith(fileNameLowerCase, ".ttf") == true) return true;
				// images
				if (StringTools::endsWith(fileNameLowerCase, ".icns") == true) return true;
				if (StringTools::endsWith(fileNameLowerCase, ".ico") == true) return true;
				if (StringTools::endsWith(fileNameLowerCase, ".png") == true) return true;
				// video
				if (StringTools::endsWith(fileNameLowerCase, ".mpg") == true) return true;
				// models
				if (StringTools::endsWith(fileNameLowerCase, ".dae") == true) return true;
				if (StringTools::endsWith(fileNameLowerCase, ".fbx") == true) return true;
				if (StringTools::endsWith(fileNameLowerCase, ".glb") == true) return true;
				if (StringTools::endsWith(fileNameLowerCase, ".gltf") == true) return true;
				if (StringTools::endsWith(fileNameLowerCase, ".tm") == true) return true;
				// property files
				if (StringTools::endsWith(fileNameLowerCase, ".properties") == true) return true;
				// shader
				if (StringTools::endsWith(fileNameLowerCase, ".cl") == true) return true;
				if (StringTools::endsWith(fileNameLowerCase, ".frag") == true) return true;
				if (StringTools::endsWith(fileNameLowerCase, ".glsl") == true) return true;
				if (StringTools::endsWith(fileNameLowerCase, ".vert") == true) return true;
				// tdme empty
				if (StringTools::endsWith(fileNameLowerCase, ".tempty") == true) return true;
				// tdme trigger
				if (StringTools::endsWith(fileNameLowerCase, ".ttrigger") == true) return true;
				// tdme envmap
				if (StringTools::endsWith(fileNameLowerCase, ".tenvmap") == true) return true;
				// tdme decal
				if (StringTools::endsWith(fileNameLowerCase, ".tdecal") == true) return true;
				// tdme model
				if (StringTools::endsWith(fileNameLowerCase, ".tmodel") == true) return true;
				// tdme scene
				if (StringTools::endsWith(fileNameLowerCase, ".tscene") == true) return true;
				// tdme particle system
				if (StringTools::endsWith(fileNameLowerCase, ".tparticle") == true) return true;
				// tdme terrain
				if (StringTools::endsWith(fileNameLowerCase, ".tterrain") == true) return true;
				// xml
				if (StringTools::endsWith(fileNameLowerCase, ".xml") == true) return true;
				// files without ending
				if (fileName.rfind(".") == string::npos ||
					(fileName.rfind("/") != string::npos &&
					fileName.rfind(".") < fileName.rfind("/"))) {
					return true;
				}
				//
				return false;
			}
		private:
			string searchTerm;
	};

	ListFilter listFilter(searchTerm);
	vector<string> files;

	if (FileSystem::getInstance()->fileExists(pathName) == false) {
		Console::println("EditorScreenController::ScanFilesThread::run(): Error: file does not exist: " + pathName);
	} else
	if (FileSystem::getInstance()->isPath(pathName) == false) {
		if (listFilter.accept(".", pathName) == true) {
			Console::println("EditorScreenController::ScanFilesThread::run(): Error: path is file: " + pathName);
		} else {
			Console::println("EditorScreenController::ScanFilesThread::run(): Error: file exist, but does not match filter: " + pathName);
		}
	} else {
		FileSystem::getInstance()->list(pathName, files, &listFilter);
		// parent folder
		Console::println("'" + editorScreenController->getProjectPath() + "' vs '" + pathName + "'");
		auto parentPathName = FileSystem::getInstance()->getPathName(pathName);
		if (editorScreenController->getProjectPath() != parentPathName) {
			string fileName = "..";

			//
			string templateSource = "button_template_thumbnail_nobackground.xml";
			string icon = "";
			string iconBig = "{$icon.type_folder_big}";

			//
			auto fileEntity = new FileEntity();
			fileEntity->id = "projectpathfiles_file_" + GUIParser::escapeQuotes(StringTools::replace(Tools::getFileName(fileName), '.', '_'));
			fileEntity->buttonXML =
				string() +
				"<button " +
				"id=\"" + fileEntity->id + "\" " +
				"value=\"" + GUIParser::escapeQuotes(parentPathName) + "\" " +
				"template=\"" + templateSource + "\" " +
				"size=\"75\" " +
				"icon=\"" + GUIParser::escapeQuotes(icon) + "\" " +
				"icon-big=\"" + GUIParser::escapeQuotes(iconBig) + "\" " +
				"filename=\"" + GUIParser::escapeQuotes(fileName) + "\" " +
				"/>\n";
			editorScreenController->lockFileEntities();
			editorScreenController->getFileEntities().push_back(fileEntity);
			editorScreenController->unlockFileEntities();
			Thread::sleep(1LL);
		}
		for (auto fileName: files) {
			if (isStopRequested() == true) break;

			//
			auto absolutePath = pathName + "/" + fileName;
			if (FileSystem::getInstance()->isPath(pathName + "/" + fileName) == false) continue;

			string templateSource = "button_template_thumbnail_nobackground.xml";
			string icon = "";
			string iconBig = "{$icon.type_folder_big}";

			//
			auto fileEntity = new FileEntity();
			fileEntity->id = "projectpathfiles_file_" + GUIParser::escapeQuotes(StringTools::replace(Tools::getFileName(fileName), '.', '_'));

			//
			string buttonOnInitialize;
			if (editorScreenController->browseToFileName.empty() == false && editorScreenController->browseToFileName == absolutePath) {
				fileEntity->scrollTo = true;
				buttonOnInitialize = "on-initialize=\"" + fileEntity->id + ".condition+=selected\" ";
			}

			fileEntity->buttonXML =
				string() +
				"<button " +
				"id=\"" + fileEntity->id + "\" " +
				"value=\"" + GUIParser::escapeQuotes(absolutePath) + "\" " +
				"template=\"" + templateSource + "\" " +
				"size=\"75\" " +
				"icon=\"" + GUIParser::escapeQuotes(icon) + "\" " +
				"icon-big=\"" + GUIParser::escapeQuotes(iconBig) + "\" " +
				"filename=\"" + GUIParser::escapeQuotes(fileName) + "\" " +
				buttonOnInitialize +
				"/>\n";
			editorScreenController->lockFileEntities();
			editorScreenController->getFileEntities().push_back(fileEntity);
			editorScreenController->unlockFileEntities();
			Thread::sleep(1LL);
		}
		for (auto fileName: files) {
			if (isStopRequested() == true) break;

			auto absolutePath = pathName + "/" + fileName;
			if (FileSystem::getInstance()->isPath(pathName + "/" + fileName) == true) continue;

			//
			try {
				//
				auto image = FileDialogScreenController::getFileImageName(fileName);
				string icon = "{$icon.type_" + image + "}";
				string iconBig = "{$icon.type_" + image + "_big}";
				string typeColor = "{$color.type_" + image + "}";

				//
				auto fileNameLowerCase = StringTools::toLowerCase(fileName);

				//
				string templateSource = "button_template_thumbnail.xml";
				Texture* thumbnailTexture = nullptr;
				vector<uint8_t> thumbnailPNGData;
				if (StringTools::endsWith(fileNameLowerCase, ".png") == true) {
					thumbnailTexture = TextureReader::read(pathName, fileName, false);
				} else
				if ((((StringTools::endsWith(fileNameLowerCase, ".tmodel") == true || StringTools::endsWith(fileNameLowerCase, ".tdecal") == true) && PrototypeReader::readThumbnail(pathName, fileName, thumbnailPNGData) == true) ||
					(StringTools::endsWith(fileNameLowerCase, ".tm") == true && FileSystem::getInstance()->getThumbnailAttachment(pathName, fileName, thumbnailPNGData) == true)) &&
					thumbnailPNGData.empty() == false) {
					static int thumbnailIdx = 0; // TODO: improve me
					thumbnailTexture = PNGTextureReader::read("tdme.editor.projectpathfiles." + to_string(thumbnailIdx++), thumbnailPNGData, false);
				}
				if (thumbnailTexture != nullptr) {
					auto textureWidth = thumbnailTexture->getTextureWidth();
					auto textureHeight = thumbnailTexture->getTextureHeight();
					auto scale = 1.0f;
					if (textureWidth > textureHeight) {
						scale = 128.0f / static_cast<float>(textureWidth);
					} else {
						scale = 128.0f / static_cast<float>(textureHeight);
					}
					auto scaledTextureWidth = static_cast<int>(static_cast<float>(textureWidth) * scale);
					auto scaledTextureHeight = static_cast<int>(static_cast<float>(textureHeight) * scale);
					if (textureWidth != scaledTextureWidth || textureHeight != scaledTextureHeight) {
						auto thumbnailTextureScaled = TextureReader::scale(thumbnailTexture, scaledTextureWidth, scaledTextureHeight);
						thumbnailTexture->releaseReference();
						thumbnailTextureScaled->acquireReference();
						thumbnailTexture = thumbnailTextureScaled;
					}
					iconBig.clear();
				}
				if (iconBig.empty() == false) icon.clear();

				//
				auto fileEntity = new FileEntity();
				fileEntity->id = "projectpathfiles_file_" + GUIParser::escapeQuotes(StringTools::replace(Tools::getFileName(fileName), '.', '_'));

				//
				string buttonOnInitialize;
				if (editorScreenController->browseToFileName.empty() == false && editorScreenController->browseToFileName == absolutePath) {
					fileEntity->scrollTo = true;
					buttonOnInitialize = "on-initialize=\"" + fileEntity->id + ".condition+=selected\" ";
				}

				fileEntity->buttonXML =
					string() +
					"<button " +
					"id=\"" + fileEntity->id + "\" " +
					"value=\"" + GUIParser::escapeQuotes(absolutePath) + "\" " +
					"template=\"" + templateSource + "\" " +
					"size=\"75\" " +
					"icon=\"" + GUIParser::escapeQuotes(icon) + "\" " +
					"icon-big=\"" + GUIParser::escapeQuotes(iconBig) + "\" " +
					"filename=\"" + GUIParser::escapeQuotes(fileName) + "\" " +
					"type-color=\"" + GUIParser::escapeQuotes(typeColor) + "\" " +
					buttonOnInitialize +
					"/>\n";

				fileEntity->thumbnailTexture = thumbnailTexture;
				editorScreenController->lockFileEntities();
				editorScreenController->getFileEntities().push_back(fileEntity);
				editorScreenController->unlockFileEntities();
				Thread::sleep(1LL);
			} catch (Exception& exception) {
				errorMessage = exception.what();
				error = true;
				Console::println("EditorScreenController::ScanFilesThread::run(): Error: " + errorMessage);
			}
		}
	}
	finished = true;
}

void EditorScreenController::onAddFile(const string& type) {
	class OnAddFile: public virtual Action
	{
	public:
		// overridden methods
		void performAction() override {
			editorScreenController->addFile(
				editorScreenController->view->getPopUps()->getFileDialogScreenController()->getPathName(),
				Tools::ensureFileEnding(editorScreenController->view->getPopUps()->getFileDialogScreenController()->getFileName(), string("t") + type),
				type
			);
			editorScreenController->view->getPopUps()->getFileDialogScreenController()->close();
		}
		OnAddFile(EditorScreenController* editorScreenController, const string& type): editorScreenController(editorScreenController), type(type) {
		}
	private:
		EditorScreenController* editorScreenController;
		string type;
	};

	view->getPopUps()->getFileDialogScreenController()->show(
		projectPath + "/" + relativeProjectPath,
		string("Add ") + type + " to project: ",
		{ string("t") + type },
		string("Untitled") + "." + "t" + type,
		true,
		new OnAddFile(this, type)
	);

}

void EditorScreenController::addFile(const string& pathName, const string& fileName, const string& type) {
	if (type == "script") {
		try {
			FileSystem::getInstance()->setContentFromString(pathName, fileName, FileSystem::getInstance()->getContentAsString("resources/engine/templates/tscript", "template.tscript"));
			browseTo(pathName + "/" + fileName);
			openFile(pathName + "/" + fileName);
		} catch (Exception& exception) {
			showInfoPopUp("Error", string() + "An error occurred: file type: " + type + ": " + exception.what());
		}
	} else {
		Prototype* prototype = nullptr;
		Scene* scene = nullptr;
		if (type == "empty") {
			prototype = new Prototype(
				Prototype::ID_NONE,
				Prototype_Type::EMPTY,
				Tools::removeFileEnding(fileName),
				Tools::removeFileEnding(fileName),
				pathName + "/" + fileName,
				"resources/engine/models/empty.tm",
				string(),
				ModelReader::read("resources/engine/models", "empty.tm"), // TODO: exception
				Vector3(0.0f, 0.0f, 0.0f)
			);
		} else
		if (type == "trigger") {
			auto width = 1.0f;
			auto height = 1.0f;
			auto depth = 1.0f;
			auto boundingBox = BoundingBox(Vector3(-width / 2.0f, 0.0f, -depth / 2.0f), Vector3(+width / 2.0f, height, +depth / 2.0f));
			prototype = new Prototype(
				Prototype::ID_NONE,
				Prototype_Type::TRIGGER,
				Tools::removeFileEnding(fileName),
				Tools::removeFileEnding(fileName),
				pathName + "/" + fileName,
				string(),
				string(),
				nullptr,
				Vector3()
			);
			prototype->addBoundingVolume(0, new PrototypeBoundingVolume(0, prototype));
			prototype->getBoundingVolume(0)->setupAabb(boundingBox.getMin(), boundingBox.getMax());
		} else
		if (type == "envmap") {
			auto width = 1.0f;
			auto height = 1.0f;
			auto depth = 1.0f;
			auto boundingBox = BoundingBox(Vector3(-width / 2.0f, 0.0f, -depth / 2.0f), Vector3(+width / 2.0f, height, +depth / 2.0f));
			prototype = new Prototype(
				Prototype::ID_NONE,
				Prototype_Type::ENVIRONMENTMAPPING,
				Tools::removeFileEnding(fileName),
				Tools::removeFileEnding(fileName),
				pathName + "/" + fileName,
				string(),
				string(),
				nullptr,
				Vector3()
			);
			prototype->addBoundingVolume(0, new PrototypeBoundingVolume(0, prototype));
			prototype->getBoundingVolume(0)->setupAabb(boundingBox.getMin(), boundingBox.getMax());
		} else
		if (type == "decal") {
			auto width = 1.0f;
			auto height = 1.0f;
			auto depth = 1.0f;
			auto boundingBox = BoundingBox(Vector3(-width / 2.0f, 0.0f, -depth / 2.0f), Vector3(+width / 2.0f, height, +depth / 2.0f));
			prototype = new Prototype(
				Prototype::ID_NONE,
				Prototype_Type::DECAL,
				Tools::removeFileEnding(fileName),
				Tools::removeFileEnding(fileName),
				pathName + "/" + fileName,
				string(),
				string(),
				nullptr,
				Vector3()
			);
			prototype->addBoundingVolume(0, new PrototypeBoundingVolume(0, prototype));
			prototype->getBoundingVolume(0)->setupAabb(boundingBox.getMin(), boundingBox.getMax());
		} else
		if (type == "model") {
			prototype = new Prototype(
				Prototype::ID_NONE,
				Prototype_Type::MODEL,
				Tools::removeFileEnding(fileName),
				Tools::removeFileEnding(fileName),
				pathName + "/" + fileName,
				"resources/engine/models/empty.tm",
				string(),
				ModelReader::read("resources/engine/models", "empty.tm"), // TODO: exception
				Vector3(0.0f, 0.0f, 0.0f)
			);
		} else
		if (type == "terrain") {
			prototype = new Prototype(
				Prototype::ID_NONE,
				Prototype_Type::TERRAIN,
				Tools::removeFileEnding(fileName),
				Tools::removeFileEnding(fileName),
				pathName + "/" + fileName,
				string(),
				string(),
				nullptr,
				Vector3()
			);
		} else
		if (type == "particle") {
			prototype = new Prototype(
				Prototype::ID_NONE,
				Prototype_Type::PARTICLESYSTEM,
				Tools::removeFileEnding(fileName),
				Tools::removeFileEnding(fileName),
				pathName + "/" + fileName,
				string(),
				string(),
				nullptr,
				Vector3()
			);
		} else
		if (type == "scene") {
			scene = new Scene(
				Tools::removeFileEnding(fileName),
				Tools::removeFileEnding(fileName)
			);
		}
		if (prototype != nullptr) {
			try {
				PrototypeWriter::write(pathName, fileName, prototype);
				browseTo(pathName + "/" + fileName);
				openFile(pathName + "/" + fileName);
			} catch (Exception& exception) {
				Console::print(string("EditorScreenController::addFile(): An error occurred: "));
				Console::println(string(exception.what()));
				showInfoPopUp("Error", string() + "An error occurred: " + exception.what());
			}
		} else
		if (scene != nullptr) {
			try {
				SceneWriter::write(pathName, fileName, scene);
				browseTo(pathName + "/" + fileName);
				openFile(pathName + "/" + fileName);
			} catch (Exception& exception) {
				Console::print(string("EditorScreenController::addFile(): An error occurred: "));
				Console::println(string(exception.what()));
				showInfoPopUp("Error", string() + "An error occurred: " + exception.what());
			}
		} else {
			showInfoPopUp("Error", string() + "Unknown file type: " + type);
		}
	}
}

void EditorScreenController::FileOpenThread::run() {
	auto fileName = FileSystem::getInstance()->getFileName(absoluteFileName);

	//
	try {
		switch (fileType) {
			case FILETYPE_MODEL:
				{
					auto model = ModelReader::read(Tools::getPathName(absoluteFileName), Tools::getFileName(absoluteFileName));
					prototype = new Prototype(
						Prototype::ID_NONE,
						Prototype_Type::MODEL,
						Tools::removeFileEnding(fileName),
						Tools::removeFileEnding(fileName),
						FileSystem::getInstance()->getPathName(absoluteFileName) + "/" + Tools::removeFileEnding(fileName) + ".tmodel",
						absoluteFileName,
						string(),
						model,
						Vector3(0.0f, 0.0f, 0.0f)
					);
					break;
				}
			case FILETYPE_EMPTYPROTOTYPE:
				{
					prototype = PrototypeReader::read(
						FileSystem::getInstance()->getPathName(absoluteFileName),
						FileSystem::getInstance()->getFileName(absoluteFileName)
					);
					break;
				}
			case FILETYPE_TRIGGERPROTOTYPE:
				{
					prototype = PrototypeReader::read(
						FileSystem::getInstance()->getPathName(absoluteFileName),
						FileSystem::getInstance()->getFileName(absoluteFileName)
					);
					break;
				}
			case FILETYPE_ENVMAPPROTOTYPE:
				{
					scene = SceneReader::read(
						"resources/engine/scenes/envmap",
						"envmap.tscene"
					);
					prototype = PrototypeReader::read(
						FileSystem::getInstance()->getPathName(absoluteFileName),
						FileSystem::getInstance()->getFileName(absoluteFileName)
					);
					break;
				}
			case FILETYPE_DECALPROTOTYPE:
				{
					prototype = PrototypeReader::read(
						FileSystem::getInstance()->getPathName(absoluteFileName),
						FileSystem::getInstance()->getFileName(absoluteFileName)
					);
					break;
				}
			case FILETYPE_MODELPROTOTYPE:
				{
					prototype = PrototypeReader::read(
						FileSystem::getInstance()->getPathName(absoluteFileName),
						FileSystem::getInstance()->getFileName(absoluteFileName)
					);
					break;
				}
			case FILETYPE_TERRAINPROTOTYPE:
				{
					prototype = PrototypeReader::read(
						FileSystem::getInstance()->getPathName(absoluteFileName),
						FileSystem::getInstance()->getFileName(absoluteFileName)
					);
					break;
				}
			case FILETYPE_PARTICLESYSTEMPROTOTYPE:
				{
					prototype = PrototypeReader::read(
						FileSystem::getInstance()->getPathName(absoluteFileName),
						FileSystem::getInstance()->getFileName(absoluteFileName)
					);
					break;
				}
			case FILETYPE_SCENE:
				{
					scene = SceneReader::read(
						FileSystem::getInstance()->getPathName(absoluteFileName),
						FileSystem::getInstance()->getFileName(absoluteFileName)
					);
					break;
				}
			case FILETYPE_SCREEN_TEXT:
				{
					throw ExceptionBase("File type not supported by EditorScreenController::FileOpenThread");
				}
			case FILETYPE_SOUND:
				{
					throw ExceptionBase("File type not supported by EditorScreenController::FileOpenThread");
				}
			case FILETYPE_TEXTURE:
				{
					throw ExceptionBase("File type not supported by EditorScreenController::FileOpenThread");
				}
			case FILETYPE_FONT:
				{
					throw ExceptionBase("File type not supported by EditorScreenController::FileOpenThread");
				}
			case FILETYPE_TEXT:
				{
					throw ExceptionBase("File type not supported by EditorScreenController::FileOpenThread");
				}
			default:
				throw ExceptionBase("Unknown file type.");
		}
	} catch (Exception& exception) {
		Console::print(string("EditorScreenController::FileOpenThread::run(): An error occurred: "));
		Console::println(string(exception.what()));
		errorMessage = string(exception.what());
		error = true;
	}

	//
	finished = true;
}

void EditorScreenController::openFile(const string& absoluteFileName) {
	Console::println("EditorScreenController::openFile(): " + absoluteFileName);

	// should never happen but still ...
	if (fileOpenThread != nullptr) {
		Console::println("EditorScreenController::openFile(): " + absoluteFileName + ": file open thread is already busy with opening a file");
		showInfoPopUp("Error", string() + "File open thread is already busy with opening a file");
		return;
	}

	// path
	if (FileSystem::getInstance()->isPath(absoluteFileName)) {
		stopScanFiles();
		resetScanFiles();
		setRelativeProjectPath(getRelativePath(absoluteFileName));
		startScanFiles();
		return;
	}

	//
	auto fileName = FileSystem::getInstance()->getFileName(absoluteFileName);
	auto fileNameLowerCase = StringTools::toLowerCase(fileName);
	FileType fileType = FILETYPE_UNKNOWN;
	if (StringTools::endsWith(fileNameLowerCase, ".xml") == true) {
		fileType = FILETYPE_SCREEN_TEXT;
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".tempty") == true) {
		fileType = FILETYPE_EMPTYPROTOTYPE;
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".ttrigger") == true) {
		fileType = FILETYPE_TRIGGERPROTOTYPE;
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".tenvmap") == true) {
		fileType = FILETYPE_ENVMAPPROTOTYPE;
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".tdecal") == true) {
		fileType = FILETYPE_DECALPROTOTYPE;
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".tscene") == true) {
		fileType = FILETYPE_SCENE;
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".tmodel") == true) {
		fileType = FILETYPE_MODELPROTOTYPE;
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".tparticle") == true) {
		fileType = FILETYPE_PARTICLESYSTEMPROTOTYPE;
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".tterrain") == true) {
		fileType = FILETYPE_TERRAINPROTOTYPE;
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".ttf") == true) {
		fileType = FILETYPE_FONT;
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".ogg") == true) {
		fileType = FILETYPE_SOUND;
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".mpg") == true) {
		fileType = FILETYPE_VIDEO;
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".md") == true ||
		fileNameLowerCase == "license" ||
		StringTools::endsWith(fileNameLowerCase, ".h") == true ||
		StringTools::endsWith(fileNameLowerCase, ".cpp") == true ||
		StringTools::endsWith(fileNameLowerCase, ".c") == true ||
		StringTools::endsWith(fileNameLowerCase, ".tscript") == true ||
		StringTools::endsWith(fileNameLowerCase, ".properties") == true ||
		StringTools::endsWith(fileNameLowerCase, ".cl") == true ||
		StringTools::endsWith(fileNameLowerCase, ".frag") == true ||
		StringTools::endsWith(fileNameLowerCase, ".glsl") == true ||
		StringTools::endsWith(fileNameLowerCase, ".vert") == true ||
		StringTools::endsWith(fileNameLowerCase, ".xml") == true ||
		(fileName.rfind(".") == string::npos || (fileName.rfind("/") != string::npos && fileName.rfind(".") < fileName.rfind("/")))) {
		fileType = FILETYPE_TEXT;
	} else {
		for (auto& extension: ModelReader::getModelExtensions()) {
			if (StringTools::endsWith(fileNameLowerCase, "." + extension) == true) {
				fileType = FILETYPE_MODEL;
				break;
			}
		}
		for (auto& extension: TextureReader::getTextureExtensions()) {
			if (StringTools::endsWith(fileNameLowerCase, "." + extension) == true) {
				fileType = FILETYPE_TEXTURE;
				break;
			}
		}
	}
	if (fileType == FILETYPE_UNKNOWN) {
		showInfoPopUp("Error", "File format not yet supported");
		return;
	}

	//
	auto tabId = "tab_viewport_" + StringTools::replace(absoluteFileName, ".", "_");
	tabId = StringTools::replace(tabId, "/", "_");
	if (screenNode->getNodeById(tabId) != nullptr) {
		tabs->getController()->setValue(MutableString(tabId));
		return;
	}
	tabId = GUIParser::escapeQuotes(tabId);

	//
	try {
		string icon;
		string colorType;
		EditorTabView::TabType tabType = EditorTabView::TABTYPE_UNKNOWN;
		TabView* tabView = nullptr;
		string viewPortTemplate;
		switch (fileType) {
			case FILETYPE_MODEL:
				{
					view->getPopUps()->getProgressBarScreenController()->show("Opening model as prototype ...", false);
					fileOpenThread = new FileOpenThread(tabId, fileType, absoluteFileName);
					fileOpenThread->start();
					break;
				}
			case FILETYPE_EMPTYPROTOTYPE:
				{
					view->getPopUps()->getProgressBarScreenController()->show("Opening empty prototype ...", false);
					fileOpenThread = new FileOpenThread(tabId, fileType, absoluteFileName);
					fileOpenThread->start();
					break;
				}
			case FILETYPE_TRIGGERPROTOTYPE:
				{
					view->getPopUps()->getProgressBarScreenController()->show("Opening trigger prototype ...", false);
					fileOpenThread = new FileOpenThread(tabId, fileType, absoluteFileName);
					fileOpenThread->start();
					break;
				}
			case FILETYPE_ENVMAPPROTOTYPE:
				{
					view->getPopUps()->getProgressBarScreenController()->show("Opening environment map prototype ...", false);
					fileOpenThread = new FileOpenThread(tabId, fileType, absoluteFileName);
					fileOpenThread->start();
					break;
				}
			case FILETYPE_DECALPROTOTYPE:
				{
					view->getPopUps()->getProgressBarScreenController()->show("Opening decal prototype ...", false);
					fileOpenThread = new FileOpenThread(tabId, fileType, absoluteFileName);
					fileOpenThread->start();
					break;
				}
			case FILETYPE_MODELPROTOTYPE:
				{
					view->getPopUps()->getProgressBarScreenController()->show("Opening model prototype...", false);
					fileOpenThread = new FileOpenThread(tabId, fileType, absoluteFileName);
					fileOpenThread->start();
					break;
				}
			case FILETYPE_TERRAINPROTOTYPE:
				{
					view->getPopUps()->getProgressBarScreenController()->show("Opening terrain prototype ...", false);
					fileOpenThread = new FileOpenThread(tabId, fileType, absoluteFileName);
					fileOpenThread->start();
					break;
				}
			case FILETYPE_PARTICLESYSTEMPROTOTYPE:
				{
					view->getPopUps()->getProgressBarScreenController()->show("Opening particle system prototype ...", false);
					fileOpenThread = new FileOpenThread(tabId, fileType, absoluteFileName);
					fileOpenThread->start();
					break;
				}
			case FILETYPE_SCENE:
				{
					view->getPopUps()->getProgressBarScreenController()->show("Opening scene ...", false);
					fileOpenThread = new FileOpenThread(tabId, fileType, absoluteFileName);
					fileOpenThread->start();
					break;
				}
			case FILETYPE_SCREEN_TEXT:
				{
					onOpenFileFinish(tabId, fileType, absoluteFileName, nullptr, nullptr);
					break;
				}
			case FILETYPE_SOUND:
				{
					onOpenFileFinish(tabId, fileType, absoluteFileName, nullptr, nullptr);
					break;
				}
			case FILETYPE_TEXTURE:
				{
					onOpenFileFinish(tabId, fileType, absoluteFileName, nullptr, nullptr);
					break;
				}
			case FILETYPE_VIDEO:
				{
					onOpenFileFinish(tabId, fileType, absoluteFileName, nullptr, nullptr);
					break;
				}
			case FILETYPE_FONT:
				{
					onOpenFileFinish(tabId, fileType, absoluteFileName, nullptr, nullptr);
					break;
				}
			case FILETYPE_TEXT:
				{
					onOpenFileFinish(tabId, fileType, absoluteFileName, nullptr, nullptr);
					break;
				}
			default:
				throw ExceptionBase("Unknown file type.");
		}
	} catch (Exception& exception) {
		Console::print(string("EditorScreenController::openFile(): An error occurred: "));
		Console::println(string(exception.what()));
		showInfoPopUp("Error", string() + "An error occurred: " + exception.what());
	}
}

void EditorScreenController::onOpenFileFinish(const string& tabId, FileType fileType, const string& absoluteFileName, Prototype* prototype, Scene* scene) {
	Console::println(string("EditorScreenController::onOpenFileFinish(): absoluteFileName: " + absoluteFileName));

	auto fileName = FileSystem::getInstance()->getFileName(absoluteFileName);
	auto fileNameLowerCase = StringTools::toLowerCase(fileName);

	//
	try {
		string icon;
		string colorType;
		EditorTabView::TabType tabType = EditorTabView::TABTYPE_UNKNOWN;
		TabView* tabView = nullptr;
		string viewPortTemplate;
		switch (fileType) {
			case FILETYPE_MODEL:
				{
					icon = "{$icon.type_mesh}";
					colorType = "{$color.type_mesh}";
					tabType = EditorTabView::TABTYPE_MODELEDITOR;
					tabView = new ModelEditorTabView(view, tabId, prototype);
					viewPortTemplate = "template_viewport_scene.xml";
					break;
				}
			case FILETYPE_EMPTYPROTOTYPE:
				{
					icon = "{$icon.type_prototype}";
					colorType = "{$color.type_prototype}";
					tabType = EditorTabView::TABTYPE_EMPTYEDITOR;
					tabView = new EmptyEditorTabView(view, tabId, prototype);
					viewPortTemplate = "template_viewport_scene.xml";
					break;
				}
			case FILETYPE_TRIGGERPROTOTYPE:
				{
					icon = "{$icon.type_prototype}";
					colorType = "{$color.type_prototype}";
					tabType = EditorTabView::TABTYPE_TRIGGEREDITOR;
					tabView = new TriggerEditorTabView(view, tabId, prototype);
					viewPortTemplate = "template_viewport_scene.xml";
					break;
				}
			case FILETYPE_ENVMAPPROTOTYPE:
				{
					icon = "{$icon.type_scene}";
					colorType = "{$color.type_scene}";
					tabType = EditorTabView::TABTYPE_ENVMAPEDITOR;
					tabView = new EnvMapEditorTabView(view, tabId, scene, prototype);
					viewPortTemplate = "template_viewport_scene.xml";
					break;
				}
			case FILETYPE_DECALPROTOTYPE:
				{
					icon = "{$icon.type_decal}";
					colorType = "{$color.type_prototype}";
					tabType = EditorTabView::TABTYPE_DECALEDITOR;
					tabView = new DecalEditorTabView(view, tabId, prototype);
					viewPortTemplate = "template_viewport_scene.xml";
					break;
				}
			case FILETYPE_MODELPROTOTYPE:
				{
					icon = "{$icon.type_prototype}";
					colorType = "{$color.type_prototype}";
					tabType = EditorTabView::TABTYPE_MODELEDITOR;
					tabView = new ModelEditorTabView(view, tabId, prototype);
					viewPortTemplate = "template_viewport_scene.xml";
					break;
				}
			case FILETYPE_TERRAINPROTOTYPE:
				{
					icon = "{$icon.type_terrain}";
					colorType = "{$color.type_terrain}";
					tabType = EditorTabView::TABTYPE_TERRAINEDITOR;
					tabView = new TerrainEditorTabView(view, tabId, prototype);
					viewPortTemplate = "template_viewport_terrain.xml";
					break;
				}
			case FILETYPE_PARTICLESYSTEMPROTOTYPE:
				{
					icon = "{$icon.type_particle}";
					colorType = "{$color.type_particle}";
					tabType = EditorTabView::TABTYPE_PARTICLESYSTEMEDITOR;
					tabView = new ParticleSystemEditorTabView(view, tabId, prototype);
					viewPortTemplate = "template_viewport_scene.xml";
					break;
				}
			case FILETYPE_SCENE:
				{
					icon = "{$icon.type_scene}";
					colorType = "{$color.type_scene}";
					tabType = EditorTabView::TABTYPE_SCENEEDITOR;
					tabView = new SceneEditorTabView(view, tabId, scene);
					viewPortTemplate = "template_viewport_scene.xml";
					break;
				}
			case FILETYPE_SCREEN_TEXT:
				{
					auto relativeFileName = getRelativePath(absoluteFileName);
					string xmlRootNode;
					// try to read XML root node tag name
					try {
						xmlRootNode = GUIParser::getRootNode(
							FileSystem::getInstance()->getPathName(relativeFileName),
							FileSystem::getInstance()->getFileName(relativeFileName)
						);
					} catch (Exception& exception) {
						Console::println("EditorScreenController::openFile(): " + relativeFileName + ": " + exception.what());
					}
					// gui?
					if (xmlRootNode == "screen" || xmlRootNode == "template") {
						icon = "{$icon.type_gui}";
						colorType = "{$color.type_gui}";
						tabType = EditorTabView::TABTYPE_UIEDITOR;
						tabView = new UIEditorTabView(view, tabId, screenNode, relativeFileName);
						viewPortTemplate = "template_viewport_ui.xml";
					} else {
						// nope, xml
						icon = "{$icon.type_script}";
						colorType = "{$color.type_script}";
						auto text =
							FileSystem::getInstance()->getContentAsString(
								FileSystem::getInstance()->getPathName(absoluteFileName),
								FileSystem::getInstance()->getFileName(absoluteFileName)
							);
						auto screenNode = GUIParser::parse(
							"resources/engine/gui/",
							"tab_text.xml",
							{{ "text", StringTools::replace(StringTools::replace(text, "[", "\\["), "]", "\\]") }}
						);
						tabType = EditorTabView::TABTYPE_TEXT;
						tabView = new TextEditorTabView(view, tabId, screenNode, absoluteFileName);
						viewPortTemplate = "template_viewport_plain.xml";
					}
					break;
				}
			case FILETYPE_SOUND:
				{
					icon = "{$icon.type_sound}";
					colorType = "{$color.type_sound}";
					auto audioStream = new VorbisAudioStream(
						tabId,
						FileSystem::getInstance()->getPathName(absoluteFileName),
						FileSystem::getInstance()->getFileName(absoluteFileName)
					);
					auto screenNode = GUIParser::parse(
						"resources/engine/gui/",
						"tab_sound.xml"
					);
					tabType = EditorTabView::TABTYPE_SOUND;
					tabView = new SoundTabView(view, tabId, screenNode, audioStream);
					viewPortTemplate = "template_viewport_plain.xml";
					break;
				}
			case FILETYPE_TEXTURE:
				{
					icon = "{$icon.type_texture}";
					colorType = "{$color.type_texture}";
					auto screenNode = GUIParser::parse(
						"resources/engine/gui/",
						"tab_texture.xml",
						{{ "texture", absoluteFileName}}

					);
					tabType = EditorTabView::TABTYPE_TEXTURE;
					tabView = new TextureTabView(view, tabId, screenNode);
					viewPortTemplate = "template_viewport_plain.xml";
					break;
				}
			case FILETYPE_VIDEO:
				{
					icon = "{$icon.type_texture}";
					colorType = "{$color.type_texture}";
					auto screenNode = GUIParser::parse(
						"resources/engine/gui/",
						"tab_video.xml",
						{{ "video", absoluteFileName}}

					);
					tabType = EditorTabView::TABTYPE_VIDEO;
					tabView = new VideoTabView(view, tabId, screenNode);
					viewPortTemplate = "template_viewport_plain.xml";
					break;
				}
			case FILETYPE_FONT:
				{
					icon = "{$icon.type_font}";
					colorType = "{$color.type_font}";
					auto screenNode = GUIParser::parse(
						"resources/engine/gui/",
						"tab_font.xml",
						{
							{ "font", absoluteFileName },
							{ "size", "20" }
						}
					);
					tabType = EditorTabView::TABTYPE_FONT;
					tabView = new FontTabView(view, tabId, screenNode);
					viewPortTemplate = "template_viewport_plain.xml";
					break;
				}
			case FILETYPE_TEXT:
				{
					auto hasVisualCode = StringTools::endsWith(fileNameLowerCase, ".tscript");
					icon = "{$icon.type_script}";
					colorType = "{$color.type_script}";
					auto text =
						FileSystem::getInstance()->getContentAsString(
							FileSystem::getInstance()->getPathName(absoluteFileName),
							FileSystem::getInstance()->getFileName(absoluteFileName)
						);
					auto screenNode = GUIParser::parse(
						"resources/engine/gui/",
						hasVisualCode == true?"tab_visualcode.xml":"tab_text.xml",
						{{ "text", StringTools::replace(StringTools::replace(text, "[", "\\["), "]", "\\]") }}
					);
					tabType = EditorTabView::TABTYPE_TEXT;
					tabView = new TextEditorTabView(view, tabId, screenNode, absoluteFileName);
					viewPortTemplate = hasVisualCode == true?"template_viewport_visualcode.xml":"template_viewport_plain.xml";
					break;
				}
			default:
				throw ExceptionBase("Unknown file type.");
		}
		//
		{
			string tabsHeaderXML = "<tab id=\"" + tabId + "\" image=\"" + GUIParser::escapeQuotes(icon) + "\" type-color=\"" + GUIParser::escapeQuotes(colorType) + "\" value=\"" + GUIParser::escapeQuotes(absoluteFileName) + "\" text=\"" + GUIParser::escapeQuotes(fileName) + "\" closeable=\"true\" />\n";
			try {
				required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(tabsHeader->getId()))->addSubNodes(tabsHeaderXML, true);
			} catch (Exception& exception) {
				Console::print(string("EditorScreenController::onOpenFile(): An error occurred: "));
				Console::println(string(exception.what()));
			}
		}
		{
			string tabsContentXML =
				"<tab-content tab-id=\"" + tabId + "\">\n" +
				"	<template id=\"" + tabId + "_tab\" src=\"resources/engine/gui/" + viewPortTemplate + "\" />\n" +
				"</tab-content>\n";
			try {
				required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(tabsContent->getId()))->addSubNodes(tabsContentXML, true);
			} catch (Exception& exception) {
				Console::print(string("EditorScreenController::onOpenFile(): An error occurred: "));
				Console::println(string(exception.what()));
			}
		}
		//
		tabView->initialize();
		//
		// TODO: move me into GUIFrameBufferNode
		if (Engine::getInstance()->getGraphicsRendererType() != Renderer::RENDERERTYPE_VULKAN) {
			auto tabFrameBuffer = dynamic_cast<GUIImageNode*>(screenNode->getNodeById(tabId + "_tab_framebuffer"));
			if (tabFrameBuffer != nullptr) tabFrameBuffer->setTextureMatrix((new Matrix2D3x3())->identity().scale(Vector2(1.0f, -1.0f)));
		}
		tabViews[tabId] = EditorTabView(tabId, tabType, tabView, required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById(tabId + "_tab_framebuffer")));
		tabs->getController()->setValue(MutableString(tabId));
	} catch (Exception& exception) {
		Console::print(string("EditorScreenController::onOpenFileFinish(): An error occurred: "));
		Console::println(string(exception.what()));
		showInfoPopUp("Error", string() + "An error occurred: " + exception.what());
	}

	//
	view->getPopUps()->getProgressBarScreenController()->close();

	//
	updateFullScreenMenuEntry();
}

void EditorScreenController::storeOutlinerState(TabView::OutlinerState& outlinerState) {
	required_dynamic_cast<GUISelectBoxController*>(outliner->getController())->determineExpandedParentOptionValues(outlinerState.expandedOutlinerParentOptionValues);
	outlinerState.value = required_dynamic_cast<GUISelectBoxController*>(outliner->getController())->getValue();
	outlinerState.renderOffsetX = required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(outlinerScrollarea->getId()))->getChildrenRenderOffsetX();
	outlinerState.renderOffsetY = required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(outlinerScrollarea->getId()))->getChildrenRenderOffsetY();
}

void EditorScreenController::restoreOutlinerState(const TabView::OutlinerState& outlinerState) {
	required_dynamic_cast<GUISelectBoxController*>(outliner->getController())->expandParentOptionsByValues(outlinerState.expandedOutlinerParentOptionValues);
	required_dynamic_cast<GUISelectBoxController*>(outliner->getController())->setValue(outlinerState.value);
	required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(outlinerScrollarea->getId()))->setChildrenRenderOffsetX(outlinerState.renderOffsetX);
	required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(outlinerScrollarea->getId()))->setChildrenRenderOffsetY(outlinerState.renderOffsetY);
}

const string EditorScreenController::getOutlinerSelection() {
	return outliner->getController()->getValue().getString();
}

void EditorScreenController::setOutlinerSelection(const string& newSelectionValue) {
	outliner->getController()->setValue(MutableString(newSelectionValue));
}

void EditorScreenController::setOutlinerContent(const string& xml) {
	auto outlinerSelection = getOutlinerSelection();
	try {
		required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(outlinerScrollarea->getId()))->replaceSubNodes(xml, true);
	} catch (Exception& exception) {
		Console::print(string("EditorScreenController::setOutlinerContent(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	setOutlinerSelection(outlinerSelection);
}

void EditorScreenController::setOutlinerAddDropDownContent(const string& xml) {
	try {
		required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(outlinerAddDropDown->getId()))->replaceSubNodes(xml, true);
	} catch (Exception& exception) {
		Console::print(string("EditorScreenController::setOutlinerAddDropDownContent(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void EditorScreenController::setDetailsContent(const string& xml) {
	try {
		required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(detailsScrollarea->getId()))->replaceSubNodes(xml, true);
	} catch (Exception& exception) {
		Console::print(string("EditorScreenController::setDetailsContent(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

bool EditorScreenController::isFullScreen() {
	return required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("screen_editor_screen"))->getActiveConditions().has("fullscreen");
}

void EditorScreenController::updateFullScreenMenuEntry() {
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("menu_view_fullscreen"))->getController()->setDisabled(tabViews.empty() == true);
}

void EditorScreenController::setFullScreen(bool fullScreen) {
	if (fullScreen == true) {
		auto selectedTab = getSelectedTab();
		if (selectedTab != nullptr) {
			Application::getApplication()->setFullScreen(true);
			fullScreenTabId = selectedTab->getId();
			required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("fullscreen-content"))->moveNodes(
				required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById(fullScreenTabId + "-content"))
			);
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("screen_editor_screen"))->getActiveConditions().add("fullscreen");
		}
	} else
	if (fullScreenTabId.empty() == false) {
		Application::getApplication()->setFullScreen(false);
		required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById(fullScreenTabId + "-content"))->moveNodes(
			required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("fullscreen-content"))
		);
		fullScreenTabId.clear();
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("screen_editor_screen"))->getActiveConditions().remove("fullscreen");
	}
}

void EditorScreenController::enableSceneMenuEntry() {
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("menu_project_scene_run"))->getController()->setDisabled(false);
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("menu_project_scene_stop"))->getController()->setDisabled(false);
}

void EditorScreenController::disableSceneMenuEntry() {
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("menu_project_scene_run"))->getController()->setDisabled(true);
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("menu_project_scene_stop"))->getController()->setDisabled(true);
}

void EditorScreenController::getViewPort(GUINode* viewPortNode, int& left, int& top, int& width, int& height) {
	auto& constraints = viewPortNode->getComputedConstraints();
	auto& padding = viewPortNode->getPadding();
	left = constraints.left + constraints.alignmentLeft + constraints.contentAlignmentLeft;
	top = constraints.top + constraints.alignmentTop + constraints.contentAlignmentTop;
	width = constraints.width - (padding.left + padding.right);
	height = constraints.height - (padding.top + padding.bottom);
}

const string EditorScreenController::getSelectedTabId() {
	return tabs->getController()->getValue().getString();
}

void EditorScreenController::tick() {
	auto now = Time::getCurrentMillis();
	if (timeFileNameSearchTerm != -1LL && now - timeFileNameSearchTerm >= 1000LL) {
		timeFileNameSearchTerm = -1LL;
		startScanFiles();
	}
	if (scanFilesThread != nullptr) {
		lockFileEntities();
		for (auto fileEntity: getFileEntities()) {
			pendingFileEntities.push_back(fileEntity);
			if (pendingFileEntities.size() == 2) addPendingFileEntities();
		}
		getFileEntities().clear();
		if (scanFilesThread->isFinished() == true) {
			scanFilesThread->join();
			addPendingFileEntities();
			if (scanFilesThread->isError() == true) {
				if (scanFilesThread->getErrorMessage().empty() == true) {
					showInfoPopUp("Error", string() + "An error occurred: Unknown error");
				} else {
					showInfoPopUp("Error", string() + "An error occurred: " + scanFilesThread->getErrorMessage());
				}
			}
			delete scanFilesThread;
			scanFilesThread = nullptr;
		}
		unlockFileEntities();
	}
	if (fileOpenThread != nullptr) {
		if (fileOpenThread->isFinished() == true) {
			fileOpenThread->join();
			if (fileOpenThread->isError() == true) {
				if (fileOpenThread->getErrorMessage().empty() == true) {
					showInfoPopUp("Error", string() + "An error occurred: Unknown error");
				} else {
					showInfoPopUp("Error", string() + "An error occurred: " + fileOpenThread->getErrorMessage());
				}
			} else {
				onOpenFileFinish(
					fileOpenThread->getTabId(),
					fileOpenThread->getFileType(),
					fileOpenThread->getAbsoluteFileName(),
					fileOpenThread->getPrototype(),
					fileOpenThread->getScene()
				);
			}
			delete fileOpenThread;
			fileOpenThread = nullptr;
		} else {
			view->getPopUps()->getProgressBarScreenController()->progress2(fileOpenThread->getProgress());
		}
	}
}

bool EditorScreenController::isDropOnNode(int dropX, int dropY, const string& nodeId) {
	auto node = screenNode->getNodeById(nodeId);
	if (node == nullptr) return false;
	auto _node = node;
	while (_node != nullptr) {
		if (_node->isConditionsMet() == false || _node->isLayouted() == false) {
			return false;
		}
		_node = _node->getParentNode();
	}
	//
	auto gui = Engine::getInstance()->getGUI();
	// TODO: node->isCoordinateBelongingToNode() could check if layouted and conditions met
	return node->isCoordinateBelongingToNode(
		Vector2(
			gui->getScaledX(screenNode, dropX),
			gui->getScaledY(screenNode, dropY)
		)
	);
}
