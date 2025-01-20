#include <tdme/tools/editor/controllers/EditorScreenController.h>

#include <algorithm>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

#include <agui/agui.h>
#include <agui/gui/elements/GUIScrollAreaController.h>
#include <agui/gui/elements/GUISelectBoxController.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUIImageNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUINode_Padding.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIParentNode.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/nodes/GUIStyledTextNode.h>
#include <agui/gui/nodes/GUITextNode.h>
#include <agui/gui/GUI.h>
#include <agui/gui/GUIParser.h>
#include <agui/utilities/MutableString.h>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/audio/VorbisAudioStream.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/fileio/prototypes/PrototypeWriter.h>
#include <tdme/engine/fileio/scenes/SceneReader.h>
#include <tdme/engine/fileio/scenes/SceneWriter.h>
#include <tdme/engine/fileio/textures/PNGTextureReader.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/Prototype_Type.h>
#include <tdme/engine/prototype/PrototypeBoundingVolume.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/engine/subsystems/lighting/LightingShader.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShader.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapCreationShader.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapRenderShader.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Texture.h>
#include <tdme/math/Matrix3x3.h>
#include <tdme/math/Vector2.h>
#include <tdme/os/filesystem/FileNameFilter.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/tools/editor/controllers/AboutDialogScreenController.h>
#include <tdme/tools/editor/controllers/ContextMenuScreenController.h>
#include <tdme/tools/editor/controllers/DraggingScreenController.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/ImportDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/controllers/InputDialogScreenController.h>
#include <tdme/tools/editor/controllers/ProgressBarScreenController.h>
#include <tdme/tools/editor/controllers/TooltipScreenController.h>
#include <tdme/tools/editor/misc/Markdown.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/TextFormatter.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabviews/DecalEditorTabView.h>
#include <tdme/tools/editor/tabviews/EmptyEditorTabView.h>
#include <tdme/tools/editor/tabviews/EnvMapEditorTabView.h>
#include <tdme/tools/editor/tabviews/FontTabView.h>
#include <tdme/tools/editor/tabviews/MarkdownTabView.h>
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
#include <tdme/tools/editor/Editor.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/Properties.h>
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/Time.h>

using std::make_unique;
using std::move;
using std::remove;
using std::string;
using std::string_view;
using std::unique_ptr;
using std::unordered_set;
using std::vector;

using agui::gui::elements::GUIScrollAreaController;
using agui::gui::elements::GUISelectBoxController;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUIImageNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINode_Padding;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIParentNode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::nodes::GUIStyledTextNode;
using agui::gui::nodes::GUITextNode;
using agui::gui::GUIParser;
using agui::utilities::MutableString;

using tdme::application::Application;
using tdme::audio::VorbisAudioStream;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::fileio::prototypes::PrototypeWriter;
using tdme::engine::fileio::scenes::SceneReader;
using tdme::engine::fileio::scenes::SceneWriter;
using tdme::engine::fileio::textures::PNGTextureReader;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::Prototype_Type;
using tdme::engine::prototype::PrototypeBoundingVolume;
using tdme::engine::scene::Scene;
using tdme::engine::subsystems::lighting::LightingShader;
using tdme::engine::subsystems::postprocessing::PostProcessingShader;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::subsystems::shadowmapping::ShadowMapCreationShader;
using tdme::engine::subsystems::shadowmapping::ShadowMapRenderShader;
using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::engine::Texture;
using tdme::math::Matrix3x3;
using tdme::math::Vector2;
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
using tdme::tools::editor::controllers::ImportDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::controllers::InputDialogScreenController;
using tdme::tools::editor::controllers::ProgressBarScreenController;
using tdme::tools::editor::controllers::TooltipScreenController;
using tdme::tools::editor::misc::Markdown;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::TextFormatter;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::DecalEditorTabView;
using tdme::tools::editor::tabviews::EmptyEditorTabView;
using tdme::tools::editor::tabviews::EnvMapEditorTabView;
using tdme::tools::editor::tabviews::FontTabView;
using tdme::tools::editor::tabviews::MarkdownTabView;
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
using tdme::tools::editor::Editor;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Integer;
using tdme::utilities::Properties;
using tdme::utilities::StringTools;
using tdme::utilities::Time;

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
		logStyledTextNode = required_dynamic_cast<GUIStyledTextNode*>(screenNode->getInnerNodeById("log"));
		logScrollarea = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("log_scrollarea"));

		//
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("projectlibrary_import"))->getController()->setDisabled(true);
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("projectpathfiles_search"))->getController()->setDisabled(true);
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("projectpaths_search"))->getController()->setDisabled(true);
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("dropdown_projectlibrary_add"))->getController()->setDisabled(true);
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("dropdown_outliner_add"))->getController()->setDisabled(true);
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("outliner_search"))->getController()->setDisabled(true);

		//
		updateFullScreenMenuEntry();
		updateTabsMenuEntries();
		disableSceneMenuEntry();
	} catch (Exception& exception) {
		Console::printLine("EditorScreenController::initialize(): An error occurred: " + string(exception.what()));
	}
	//
	class EditorLogger: public Console::Logger {
		public:
			EditorLogger(EditorScreenController* editorScreenController): editorScreenController(editorScreenController) {
			}
			void printLine(const string_view& str) {
				auto& messages = editorScreenController->logMessages;
				if (messages.empty() == true || newline == true) messages.push_back(string());
				messages[messages.size() - 1]+= str;
				if (messages.size() == Console::HISTORY_LINECOUNT) messages.erase(messages.begin());
				newline = true;
				editorScreenController->logUpdateRequired = true;
			}
			void print(const string_view& str) {
				auto& messages = editorScreenController->logMessages;
				if (messages.empty() == true || newline == true) messages.push_back(string());
				messages[messages.size() - 1]+= str;
				if (messages.size() == Console::HISTORY_LINECOUNT) messages.erase(messages.begin());
				newline = false;
				editorScreenController->logUpdateRequired = true;
			}
			void printLine() {
				auto& messages = editorScreenController->logMessages;
				messages.push_back(string());
				if (messages.size() == Console::HISTORY_LINECOUNT) messages.erase(messages.begin());
				newline = true;
				editorScreenController->logUpdateRequired = true;
			}
		private:
			EditorScreenController* editorScreenController { nullptr };
			bool newline { false };
	};
	//
	Console::setLogger(new EditorLogger(this));
	//
	onOpenProject();
}

void EditorScreenController::dispose()
{
	stopScanFiles();
	closeProject();
}

void EditorScreenController::setScreenCaption(const string& text)
{
}

void EditorScreenController::onQuit()
{
	Editor::getInstance()->quit();
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
			for (auto tab: tabViewVector) {
				tab->getTabView()->getTabController()->onCommand(TabController::COMMAND_SAVE);
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
		if (node->getId() == "menu_help_guixml_documentation") {
			openFile(FileSystem::getInstance()->getCurrentWorkingPathName() + "/README-GUI-XML.md");
		} else
		if (node->getId() == "menu_help_miniscript_documentation") {
			openFile(FileSystem::getInstance()->getCurrentWorkingPathName() + "/README-MiniScript.md");
		} else
		if (node->getId() == "menu_help_about") {
			view->getPopUps()->getAboutDialogScreenController()->show();
		} else
		if (StringTools::startsWith(node->getId(), "projectpathfiles_file_") == true) {
			onOpenFile(required_dynamic_cast<GUIElementNode*>(node)->getValue());
		} else
		if (StringTools::startsWith(node->getId(), "menu_view_tab_") == true) {
			selectTabAt(Integer::parse(StringTools::substring(node->getId(), string("menu_view_tab_").size())));
		} else
		if (StringTools::startsWith(node->getId(), "tab_") == true) {
			string tabIdToClose;
			for (auto tab: tabViewVector) {
				if (StringTools::startsWith(node->getId(), tab->getId() + "_close") == true) {
					tabIdToClose = tab->getId();
				}
			}
			if (tabIdToClose.empty() == false) closeTab(tabIdToClose);
		} else
		if (node->getId() == "menu_file_quit") {
			Editor::getInstance()->quit();
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
		//
		auto absoluteFileName = required_dynamic_cast<GUIElementNode*>(node)->getValue();
		// check if file is a path
		auto path = false;
		try {
			path = FileSystem::getInstance()->isPath(absoluteFileName);
		} catch (Exception& exception) {
			// no op
		}
		// clear context menu
		view->getPopUps()->getContextMenuScreenController()->clear();
		{
			// open
			class OnOpenAction: public virtual Action
			{
			public:
				OnOpenAction(EditorScreenController* editorScreenController, const string& absoluteFileName): editorScreenController(editorScreenController), absoluteFileName(absoluteFileName) {
				}
				void performAction() override {
					editorScreenController->openFile(absoluteFileName);
				}
			private:
				EditorScreenController* editorScreenController;
				string absoluteFileName;
			};
			view->getPopUps()->getContextMenuScreenController()->addMenuItem("Open", "contextmenu_file_open", new OnOpenAction(this, absoluteFileName));
		}
		//
		view->getPopUps()->getContextMenuScreenController()->addMenuSeparator();
		//
		{
			// copy path
			class OnCopyPathAction: public virtual Action
			{
			public:
				OnCopyPathAction(EditorScreenController* editorScreenController, const string& absoluteFileName): editorScreenController(editorScreenController), absoluteFileName(absoluteFileName) {
				}
				void performAction() override {
					Application::getApplication()->setClipboardContent(absoluteFileName);
				}
			private:
				EditorScreenController* editorScreenController;
				string absoluteFileName;
			};
			view->getPopUps()->getContextMenuScreenController()->addMenuItem("Copy Path", "contextmenu_file_copypath", new OnCopyPathAction(this, absoluteFileName));
		}
		//
		if (path == false) {
			// duplicate
			class OnDuplicateAction: public virtual Action
			{
			public:
				OnDuplicateAction(EditorScreenController* editorScreenController, const string& absoluteFileName): editorScreenController(editorScreenController), absoluteFileName(absoluteFileName) {
				}
				void performAction() override {
					class DuplicateFileAction: public virtual Action
					{
					public:
						DuplicateFileAction(EditorScreenController* editorScreenController, const string& absoluteFileName): editorScreenController(editorScreenController), absoluteFileName(absoluteFileName) {
						}
						// overridden methods
						void performAction() override {
							try {
								// get duplicate file name and extension
								string duplicateFileName = editorScreenController->view->getPopUps()->getInputDialogScreenController()->getInputText();
								string extension;
								if (FileSystem::getInstance()->isPath(absoluteFileName) == false) {
									extension = Tools::getFileExtension(absoluteFileName);
								}
								// read file
								vector<uint8_t> fileContent;
								FileSystem::getInstance()->getContent(
									Tools::getPathName(absoluteFileName),
									Tools::getFileName(absoluteFileName),
									fileContent
								);
								// write file
								FileSystem::getInstance()->setContent(
									Tools::getPathName(absoluteFileName),
									(extension.empty() == true?
										duplicateFileName:
										Tools::ensureFileExtension(duplicateFileName, extension)
									),
									fileContent
								);
								// reload file view
								editorScreenController->reload();
							} catch (Exception& exception) {
								editorScreenController->showInfoPopUp("Warning", exception.what());
							}
							editorScreenController->view->getPopUps()->getInputDialogScreenController()->close();
						}
					private:
						EditorScreenController* editorScreenController;
						string absoluteFileName;
					};
					//
					editorScreenController->view->getPopUps()->getInputDialogScreenController()->show(
						"Duplicate",
						Tools::removeFileExtension(Tools::getFileName(absoluteFileName)),
						new DuplicateFileAction(editorScreenController, absoluteFileName)
					);
				}
			private:
				EditorScreenController* editorScreenController;
				string absoluteFileName;
			};
			view->getPopUps()->getContextMenuScreenController()->addMenuItem("Duplicate", "contextmenu_file_duplicate", new OnDuplicateAction(this, absoluteFileName));
		}
		//
		{
			// rename
			class OnRenameAction: public virtual Action
			{
			public:
				OnRenameAction(EditorScreenController* editorScreenController, const string& absoluteFileName): editorScreenController(editorScreenController), absoluteFileName(absoluteFileName) {
				}
				void performAction() override {
					class RenameFileAction: public virtual Action
					{
					public:
						RenameFileAction(EditorScreenController* editorScreenController, const string& absoluteFileName): editorScreenController(editorScreenController), absoluteFileName(absoluteFileName) {
						}
						// overridden methods
						void performAction() override {
							try {
								// get duplicate file name and extension
								string renameFileName = editorScreenController->view->getPopUps()->getInputDialogScreenController()->getInputText();
								string extension;
								if (FileSystem::getInstance()->isPath(absoluteFileName) == false) {
									extension = Tools::getFileExtension(absoluteFileName);
								}
								// rename file
								FileSystem::getInstance()->rename(
									absoluteFileName,
									Tools::getPathName(absoluteFileName) + "/" +
										(extension.empty() == true?
											renameFileName:
											Tools::ensureFileExtension(renameFileName, extension)
										)
								);
								// reload file view
								editorScreenController->reload();
							} catch (Exception& exception) {
								editorScreenController->showInfoPopUp("Warning", exception.what());
							}
							editorScreenController->view->getPopUps()->getInputDialogScreenController()->close();
						}
					private:
						EditorScreenController* editorScreenController;
						string absoluteFileName;
					};
					//
					editorScreenController->view->getPopUps()->getInputDialogScreenController()->show(
						"Rename",
						Tools::removeFileExtension(Tools::getFileName(absoluteFileName)),
						new RenameFileAction(editorScreenController, absoluteFileName)
					);
				}
			private:
				EditorScreenController* editorScreenController;
				string absoluteFileName;
			};
			view->getPopUps()->getContextMenuScreenController()->addMenuItem("Rename", "contextmenu_file_rename", new OnRenameAction(this, absoluteFileName));
		}
		//
		{
			// move
			class OnMoveAction: public virtual Action
			{
			public:
				OnMoveAction(EditorScreenController* editorScreenController, const string& absoluteFileName): editorScreenController(editorScreenController), absoluteFileName(absoluteFileName) {
				}
				void performAction() override {
					class FileMoveAction: public virtual Action
					{
					public:
						/**
						 * Public constructor
						 * @param editorScreenController editor screen controller
						 */
						FileMoveAction(EditorScreenController* editorScreenController, const string& absoluteFileName): editorScreenController(editorScreenController), absoluteFileName(absoluteFileName) {
						}
						// overridden methods
						void performAction() override {
							auto moveToPath = editorScreenController->view->getPopUps()->getFileDialogScreenController()->getPathName();
							try {
								// move file
								FileSystem::getInstance()->rename(
									absoluteFileName,
									moveToPath + "/" + Tools::getFileName(absoluteFileName)
								);
								// reload file view
								editorScreenController->reload();
							} catch (Exception& exception) {
								editorScreenController->showInfoPopUp("Warning", exception.what());
							}
							//
							editorScreenController->view->getPopUps()->getFileDialogScreenController()->close();
						}
					private:
						EditorScreenController* editorScreenController;
						string absoluteFileName;
					};

					//
					editorScreenController->view->getPopUps()->getFileDialogScreenController()->show(
						editorScreenController->projectPath + "/" + editorScreenController->relativeProjectPath,
						"Move to folder: ",
						{},
						string(),
						true,
						new FileMoveAction(editorScreenController, absoluteFileName)
					);
				}
			private:
				EditorScreenController* editorScreenController;
				string absoluteFileName;
			};
			view->getPopUps()->getContextMenuScreenController()->addMenuItem("Move", "contextmenu_file_move", new OnMoveAction(this, absoluteFileName));
		}
		{
			// delete
			class OnDeleteAction: public virtual Action
			{
			public:
				OnDeleteAction(EditorScreenController* editorScreenController, const string& absoluteFileName): editorScreenController(editorScreenController), absoluteFileName(absoluteFileName) {
				}
				void performAction() override {
					try {
						if (FileSystem::getInstance()->isPath(absoluteFileName) == true) {
							FileSystem::getInstance()->removePath(absoluteFileName, true);
						} else {
							FileSystem::getInstance()->removeFile(Tools::getPathName(absoluteFileName), Tools::getFileName(absoluteFileName));
						}
						//
						editorScreenController->reload();
					} catch (Exception& exception) {
						Console::printLine("OnDeleteAction::performAction(): An error occurred: " + string(exception.what()));
					}
				}
			private:
				EditorScreenController* editorScreenController;
				string absoluteFileName;
			};
			view->getPopUps()->getContextMenuScreenController()->addMenuItem("Delete", "contextmenu_file_delete", new OnDeleteAction(this, absoluteFileName));
		}

		{
			//
			auto selectedTab = getSelectedTab();
			if (selectedTab != nullptr) {
				switch (selectedTab->getType()) {
					case EditorTabView::TABTYPE_SCENEEDITOR:
						{

							// add to scene
							class OnAddToSceneAction: public virtual Action
							{
							public:
								OnAddToSceneAction(EditorScreenController* editorScreenController, const string& absoluteFileName): editorScreenController(editorScreenController), absoluteFileName(absoluteFileName) {
								}
								void performAction() override {
									auto currentTab = editorScreenController->getSelectedTab();
									if (currentTab == nullptr) return;
									SceneEditorTabView* sceneEditorTabView = dynamic_cast<SceneEditorTabView*>(currentTab->getTabView());
									if (sceneEditorTabView == nullptr) return;
									try {
										// load prototype
										auto prototype = PrototypeReader::read(
											Tools::getPathName(absoluteFileName),
											Tools::getFileName(absoluteFileName)
										);
										// mark as non embedded
										prototype->setEmbedded(false);
										// add to library
										sceneEditorTabView->addPrototype(prototype);
									} catch (Exception& exception) {
										Console::printLine("OnOpenAction::performAction(): An error occurred: " + string(exception.what()));
										editorScreenController->showInfoPopUp("Warning", exception.what());
									}
								}
							private:
								EditorScreenController* editorScreenController;
								string absoluteFileName;
							};
							view->getPopUps()->getContextMenuScreenController()->addMenuSeparator();
							view->getPopUps()->getContextMenuScreenController()->addMenuItem("Add to scene", "contextmenu_file_addtoscene", new OnAddToSceneAction(this, absoluteFileName));

							//
						}
						break;
					default: break;
				}
			}
		}
		//
		view->getPopUps()->getContextMenuScreenController()->addMenuSeparator();
		//
		{
			// show in file browser
			class OnShowInFileBrowserAction: public virtual Action
			{
			public:
				OnShowInFileBrowserAction(EditorScreenController* editorScreenController, const string& absoluteFileName): editorScreenController(editorScreenController), absoluteFileName(absoluteFileName) {
				}
				void performAction() override {
					try {
						if (FileSystem::getInstance()->isPath(absoluteFileName) == true) {
							Application::openBrowser(absoluteFileName);
						} else {
							Application::openBrowser(Tools::getPathName(absoluteFileName));
						}
					} catch (Exception& exception) {
						Console::printLine("OnShowInFileBrowserAction::performAction(): An error occurred: " + string(exception.what()));
					}
				}
			private:
				EditorScreenController* editorScreenController;
				string absoluteFileName;
			};
			view->getPopUps()->getContextMenuScreenController()->addMenuItem("Show in File Browser", "contextmenu_file_showinfilebrowser", new OnShowInFileBrowserAction(this, absoluteFileName));
		}
		//
		view->getPopUps()->getContextMenuScreenController()->show(mouseX, mouseY);
	} else {
		// forward onContextMenuRequest to active tab tab controller
		auto selectedTab = getSelectedTab();
		if (selectedTab != nullptr) selectedTab->getTabView()->getTabController()->onContextMenuRequest(node, mouseX, mouseY);
	}
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
		auto absoluteFileName = node->getValue();
		auto imageSource = GUIParser::getEngineThemeProperties()->get("icon.type_" + FileDialogScreenController::getFileImageName(absoluteFileName) + "_big", "resources/engine/images/tdme_big.png");
		auto xml = "<image width=\"auto\" height=\"auto\" src=\"" + imageSource + "\" />";
		view->getPopUps()->getDraggingScreenController()->start(mouseX, mouseY, xml, "file:" + absoluteFileName, new OnDragReleaseAction(this));
	}
}

void EditorScreenController::openProject(const string& pathName) {
	projectPath = pathName;
	if (StringTools::endsWith(projectPath, "/") == true) {
		projectPath = StringTools::substring(projectPath, 0, projectPath.size() - 1);
	}
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
	Engine::getInstance()->loadTextures(pathName);
	//
	GUIParser::loadProjectThemeProperties(projectPath);
}

void EditorScreenController::onOpenProject() {
	class OnOpenProject: public virtual Action
	{
	public:
		/**
		 * Public constructor
		 * @param editorScreenController editor screen controller
		 */
		OnOpenProject(EditorScreenController* editorScreenController): editorScreenController(editorScreenController) {
		}
		// overridden methods
		void performAction() override {
			auto projectPath = editorScreenController->view->getPopUps()->getFileDialogScreenController()->getPathName();
			editorScreenController->openProject(projectPath);
			editorScreenController->view->getPopUps()->getFileDialogScreenController()->close();
		}
	private:
		EditorScreenController* editorScreenController;
	};

	view->getPopUps()->getFileDialogScreenController()->show(
		".",
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
	xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escape("resources") + "\" value=\"" + GUIParser::escape("resources") + "\">\n";
	scanProjectPaths(projectPath + "/resources", xml);
	xml+= "</selectbox-parent-option>\n";
	xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escape("shader") + "\" value=\"" + GUIParser::escape("shader") + "\">\n";
	scanProjectPaths(projectPath + "/shader", xml);
	xml+= "</selectbox-parent-option>\n";
	xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escape("src") + "\" value=\"" + GUIParser::escape("src") + "\">\n";
	scanProjectPaths(projectPath + "/src", xml);
	xml+= "</selectbox-parent-option>\n";
	try {
		required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(projectPathsScrollArea->getId()))->replaceSubNodes(xml, true);
	} catch (Exception& exception) {
		Console::print("EditorScreenController::scanProjectPaths(): An error occurred: " + string(exception.what()));
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

	if (FileSystem::getInstance()->exists(path) == false) {
		Console::printLine("EditorScreenController::scanProject(): Error: file does not exist: " + path);
	} else
	if (FileSystem::getInstance()->isPath(path) == false) {
		if (listFilter.accept(".", path) == true) {
			Console::printLine("EditorScreenController::scanProject(): Error: path is file" + path);
		} else {
			Console::printLine("EditorScreenController::scanProject(): Error: file exist, but does not match filter: " + path);
		}
	} else {
		FileSystem::getInstance()->list(path, files, &listFilter);
		for (const auto& fileName: files) {
			auto relativePath = path + "/" + fileName;
			if (StringTools::startsWith(relativePath, projectPath)) relativePath = StringTools::substring(relativePath, projectPath.size() + 1, relativePath.size());
			if (FileSystem::getInstance()->isPath(path + "/" + fileName) == false) {
				// no op for now
			} else {
				string innerXml;
				scanProjectPaths(path + "/" + fileName, innerXml);
				if (innerXml.empty() == false) {
					xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escape(fileName) + "\" value=\"" + GUIParser::escape(relativePath) + "\">\n";
					xml+= innerXml;
					xml+= "</selectbox-parent-option>\n";
				} else {
					xml+= "<selectbox-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escape(fileName) + "\" value=\"" + GUIParser::escape(relativePath) + "\" />\n";
				}
			}
		}
	}
}

void EditorScreenController::closeTab(const string& tabId) {
	screenNode->removeNodeById(tabId, false);
	screenNode->removeNodeById(tabId + "-content", false);
	auto tabIt = tabViews.find(tabId);
	if (tabIt != tabViews.end()) {
		auto& tab = tabIt->second;
		tab.getTabView()->dispose();
		//
		auto tabIdx = 0;
		for (auto tab: tabViewVector) {
			if (tab->getId() == tabId) break;
			tabIdx++;
		}
		//
		tabViews.erase(tabIt);
		tabViewVector.erase(tabViewVector.begin() + tabIdx);
	}
	setDetailsContent(string());
	setOutlinerContent(string());
	//
	updateFullScreenMenuEntry();
	updateTabsMenuEntries();
}

void EditorScreenController::closeTabs() {
	for (auto& [tabId, tab]: tabViews) {
		screenNode->removeNodeById(tab.getId(), false);
		screenNode->removeNodeById(tab.getId() + "-content", false);
		tab.getTabView()->dispose();
	}
	tabViews.clear();
	tabViewVector.clear();
	setDetailsContent(string());
	setOutlinerContent(string());
	//
	updateFullScreenMenuEntry();
	updateTabsMenuEntries();
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
		Console::printLine("EditorScreenController::startScanFiles(): An error occurred: " + string(exception.what()));
	}
	scanFilesThread = make_unique<ScanFilesThread>(this, projectPath + "/" + relativeProjectPath, StringTools::toLowerCase(fileNameSearchTerm));
	scanFilesThread->start();
}

void EditorScreenController::addPendingFileEntities() {
	string scrollToNodeId;
	string xml;
	xml+= "<layout alignment=\"horizontal\">\n";
	for (const auto& pendingFileEntity: pendingFileEntities) {
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
		Console::printLine("EditorScreenController::addPendingFileEntities(): An error occurred: " + string(exception.what()));
	}
	//
	for (const auto& pendingFileEntity: pendingFileEntities) {
		if (pendingFileEntity->thumbnailTexture == nullptr) continue;
		if (screenNode->getNodeById(pendingFileEntity->id + "_texture_normal") == nullptr) continue;
		try {
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById(pendingFileEntity->id + "_texture_normal"))->setTexture(pendingFileEntity->thumbnailTexture->toGUITexture());
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById(pendingFileEntity->id + "_texture_mouseover"))->setTexture(pendingFileEntity->thumbnailTexture->toGUITexture());
			required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById(pendingFileEntity->id + "_texture_clicked"))->setTexture(pendingFileEntity->thumbnailTexture->toGUITexture());
		} catch (Exception& exception) {
			Console::printLine("EditorScreenController::addPendingFileEntities(): An error occurred: " + string(exception.what()));
		}
		if (pendingFileEntity->thumbnailTexture != nullptr) pendingFileEntity->thumbnailTexture->releaseReference();
	}
	pendingFileEntities.clear();
}

void EditorScreenController::setRelativeProjectPath(const string& relativeProjectPath) {
	this->relativeProjectPath = relativeProjectPath;
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("selectbox_projectpaths"))->getController()->setValue(MutableString(relativeProjectPath));
}

void EditorScreenController::stopScanFiles() {
	if (scanFilesThread != nullptr) {
		scanFilesThread->stop();
		scanFilesThread->join();
		lockFileEntities();
		for (const auto& fileEntity: getFileEntities()) {
			if (fileEntity->thumbnailTexture != nullptr) fileEntity->thumbnailTexture->releaseReference();
		}
		getFileEntities().clear();
		unlockFileEntities();
		scanFilesThread = nullptr;
	}
}

void EditorScreenController::resetScanFiles() {
	fileNameSearchTerm.clear();
	browseToFileName.clear();
	timeFileNameSearchTerm = -1LL;
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("projectpathfiles_search"))->getController()->setValue(MutableString());
}

void EditorScreenController::reload() {
	stopScanFiles();
	resetScanFiles();
	browseToFileName.clear();
	setRelativeProjectPath(relativeProjectPath);
	startScanFiles();
}

void EditorScreenController::browseTo(const string& fileName) {
	stopScanFiles();
	resetScanFiles();
	auto newRelativeProjectPath = Tools::getPathName(fileName);
	if (StringTools::startsWith(newRelativeProjectPath, projectPath) == true) newRelativeProjectPath = StringTools::substring(newRelativeProjectPath, projectPath.size() + 1);
	browseToFileName = projectPath + "/" + newRelativeProjectPath + "/" + Tools::getFileName(fileName);
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
				// nmake files
				if (StringTools::endsWith(fileNameLowerCase, ".nmake") == true) return true;
				if (StringTools::endsWith(fileNameLowerCase, ".nmake.main") == true) return true;
				// batch files
				if (StringTools::endsWith(fileNameLowerCase, ".bat") == true) return true;
				// bash files
				if (StringTools::endsWith(fileNameLowerCase, ".sh") == true) return true;
				if (StringTools::endsWith(fileNameLowerCase, ".bash") == true) return true;
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

	if (FileSystem::getInstance()->exists(pathName) == false) {
		Console::printLine("EditorScreenController::ScanFilesThread::run(): Error: file does not exist: " + pathName);
	} else
	if (FileSystem::getInstance()->isPath(pathName) == false) {
		if (listFilter.accept(".", pathName) == true) {
			Console::printLine("EditorScreenController::ScanFilesThread::run(): Error: path is file: " + pathName);
		} else {
			Console::printLine("EditorScreenController::ScanFilesThread::run(): Error: file exist, but does not match filter: " + pathName);
		}
	} else {
		FileSystem::getInstance()->list(pathName, files, &listFilter);
		// parent folder
		auto parentPathName = FileSystem::getInstance()->getPathName(pathName);
		if (editorScreenController->getProjectPath() != parentPathName) {
			string fileName = "..";

			//
			string templateSource = "button_template_thumbnail_nobackground.xml";
			string icon = "";
			string iconBig = "{$icon.type_folder_big}";

			//
			auto fileEntity = make_unique<FileEntity>();
			fileEntity->id = "projectpathfiles_file_" + GUIParser::escape(StringTools::replace(Tools::getFileName(fileName), '.', '_'));
			fileEntity->buttonXML =
				string() +
				"<button " +
				"id=\"" + fileEntity->id + "\" " +
				"value=\"" + GUIParser::escape(parentPathName) + "\" " +
				"template=\"" + templateSource + "\" " +
				"size=\"75\" " +
				"icon=\"" + GUIParser::escape(icon) + "\" " +
				"icon-big=\"" + GUIParser::escape(iconBig) + "\" " +
				"filename=\"" + GUIParser::escape(fileName) + "\" " +
				"/>\n";
			editorScreenController->lockFileEntities();
			editorScreenController->getFileEntities().push_back(move(fileEntity));
			editorScreenController->unlockFileEntities();
		}
		for (const auto& fileName: files) {
			if (isStopRequested() == true) break;

			//
			auto absolutePath = pathName + "/" + fileName;
			if (FileSystem::getInstance()->isPath(pathName + "/" + fileName) == false) continue;

			string templateSource = "button_template_thumbnail_nobackground.xml";
			string icon = "";
			string iconBig = "{$icon.type_folder_big}";

			//
			auto fileEntity = make_unique<FileEntity>();
			fileEntity->id = "projectpathfiles_file_" + GUIParser::escape(StringTools::replace(Tools::getFileName(fileName), '.', '_'));

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
				"value=\"" + GUIParser::escape(absolutePath) + "\" " +
				"template=\"" + templateSource + "\" " +
				"size=\"75\" " +
				"icon=\"" + GUIParser::escape(icon) + "\" " +
				"icon-big=\"" + GUIParser::escape(iconBig) + "\" " +
				"filename=\"" + GUIParser::escape(fileName) + "\" " +
				buttonOnInitialize +
				"/>\n";
			editorScreenController->lockFileEntities();
			editorScreenController->getFileEntities().push_back(move(fileEntity));
			editorScreenController->unlockFileEntities();
		}
		for (const auto& fileName: files) {
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
						thumbnailTexture = thumbnailTextureScaled;
					}
					iconBig.clear();
				}
				if (iconBig.empty() == false) icon.clear();

				//
				auto fileEntity = make_unique<FileEntity>();
				fileEntity->id = "projectpathfiles_file_" + GUIParser::escape(StringTools::replace(Tools::getFileName(fileName), '.', '_'));

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
					"value=\"" + GUIParser::escape(absolutePath) + "\" " +
					"template=\"" + templateSource + "\" " +
					"size=\"75\" " +
					"icon=\"" + GUIParser::escape(icon) + "\" " +
					"icon-big=\"" + GUIParser::escape(iconBig) + "\" " +
					"filename=\"" + GUIParser::escape(fileName) + "\" " +
					"type-color=\"" + GUIParser::escape(typeColor) + "\" " +
					buttonOnInitialize +
					"/>\n";

				fileEntity->thumbnailTexture = thumbnailTexture;
				editorScreenController->lockFileEntities();
				editorScreenController->getFileEntities().push_back(move(fileEntity));
				editorScreenController->unlockFileEntities();
				Thread::sleep(1LL);
			} catch (Exception& exception) {
				errorMessage = exception.what();
				error = true;
				Console::printLine("EditorScreenController::ScanFilesThread::run(): Error: " + errorMessage);
			}
		}
	}
	finished = true;
}

void EditorScreenController::onAddFile(const string& type) {
	class OnAddFile: public virtual Action
	{
	public:
		OnAddFile(EditorScreenController* editorScreenController, const string& type, const string& extension): editorScreenController(editorScreenController), type(type), extension(extension) {
		}
		// overridden methods
		void performAction() override {
			editorScreenController->addFile(
				editorScreenController->projectPath + "/" + editorScreenController->relativeProjectPath,
				(extension.empty() == true?
					editorScreenController->view->getPopUps()->getInputDialogScreenController()->getInputText():
					Tools::ensureFileExtension(editorScreenController->view->getPopUps()->getInputDialogScreenController()->getInputText(), extension)),
				type
			);
			editorScreenController->view->getPopUps()->getInputDialogScreenController()->close();
		}
	private:
		EditorScreenController* editorScreenController;
		string type;
		string extension;
	};

	//
	string extension;
	if (type != "folder") {
		if (type == "logic_script") extension = "tscript"; else
		if (type == "gui_script") extension = "tscript"; else
		if (type == "screen" || type == "template") extension = "xml"; else
			extension = "t" + type;
	}

	//
	view->getPopUps()->getInputDialogScreenController()->show(
		string("Add ") + type + " to project: ",
		string("Untitled"),
		new OnAddFile(this, type, extension)
	);
}

void EditorScreenController::addFile(const string& pathName, const string& fileName, const string& type) {
	if (type == "folder") {
		try {
			FileSystem::getInstance()->createPath(pathName + "/" + fileName);
			browseTo(pathName + "/" + fileName);
		} catch (Exception& exception) {
			showInfoPopUp("Error", string() + "An error occurred: file type: " + type + ": " + exception.what());
		}
	} else
	if (type == "screen") {
		try {
			FileSystem::getInstance()->setContentFromString(
				pathName,
				fileName,
				StringTools::replace(
					FileSystem::getInstance()->getContentAsString("resources/engine/templates/gui", "screen.xml"),
					"{$screen-id}",
					Tools::removeFileExtension(fileName)
				)
			);
			browseTo(pathName + "/" + fileName);
			openFile(pathName + "/" + fileName);
		} catch (Exception& exception) {
			showInfoPopUp("Error", string() + "An error occurred: file type: " + type + ": " + exception.what());
		}
	} else
	if (type == "template") {
		try {
			FileSystem::getInstance()->setContentFromString(pathName, fileName, FileSystem::getInstance()->getContentAsString("resources/engine/templates/gui", "template.xml"));
			browseTo(pathName + "/" + fileName);
			openFile(pathName + "/" + fileName);
		} catch (Exception& exception) {
			showInfoPopUp("Error", string() + "An error occurred: file type: " + type + ": " + exception.what());
		}
	} else
	if (type == "logic_script") {
		try {
			FileSystem::getInstance()->setContentFromString(pathName, fileName, FileSystem::getInstance()->getContentAsString("resources/engine/templates/tscript", "logic_script_template.tscript"));
			browseTo(pathName + "/" + fileName);
			openFile(pathName + "/" + fileName);
		} catch (Exception& exception) {
			showInfoPopUp("Error", string() + "An error occurred: file type: " + type + ": " + exception.what());
		}
	} else
	if (type == "gui_script") {
		try {
			FileSystem::getInstance()->setContentFromString(pathName, fileName, FileSystem::getInstance()->getContentAsString("resources/engine/templates/tscript", "gui_script_template.tscript"));
			browseTo(pathName + "/" + fileName);
			openFile(pathName + "/" + fileName);
		} catch (Exception& exception) {
			showInfoPopUp("Error", string() + "An error occurred: file type: " + type + ": " + exception.what());
		}
	} else {
		unique_ptr<Prototype> prototype;
		unique_ptr<Scene> scene;
		if (type == "empty") {
			prototype = make_unique<Prototype>(
				Prototype::ID_NONE,
				Prototype_Type::EMPTY,
				Tools::removeFileExtension(fileName),
				Tools::removeFileExtension(fileName),
				pathName + "/" + fileName,
				"resources/engine/models/empty.tm",
				string(),
				ModelReader::read("resources/engine/models", "empty.tm") // TODO: exception
			);
		} else
		if (type == "trigger") {
			auto width = 1.0f;
			auto height = 1.0f;
			auto depth = 1.0f;
			auto boundingBox = BoundingBox(Vector3(-width / 2.0f, 0.0f, -depth / 2.0f), Vector3(+width / 2.0f, height, +depth / 2.0f));
			prototype = make_unique<Prototype>(
				Prototype::ID_NONE,
				Prototype_Type::TRIGGER,
				Tools::removeFileExtension(fileName),
				Tools::removeFileExtension(fileName),
				pathName + "/" + fileName,
				string(),
				string(),
				nullptr
			);
			prototype->addBoundingVolume(new PrototypeBoundingVolume(prototype.get()));
			prototype->getBoundingVolume(0)->setupAabb(boundingBox.getMin(), boundingBox.getMax());
		} else
		if (type == "envmap") {
			auto width = 1.0f;
			auto height = 1.0f;
			auto depth = 1.0f;
			auto boundingBox = BoundingBox(Vector3(-width / 2.0f, 0.0f, -depth / 2.0f), Vector3(+width / 2.0f, height, +depth / 2.0f));
			prototype = make_unique<Prototype>(
				Prototype::ID_NONE,
				Prototype_Type::ENVIRONMENTMAPPING,
				Tools::removeFileExtension(fileName),
				Tools::removeFileExtension(fileName),
				pathName + "/" + fileName,
				string(),
				string(),
				nullptr
			);
			prototype->addBoundingVolume(new PrototypeBoundingVolume(prototype.get()));
			prototype->getBoundingVolume(0)->setupAabb(boundingBox.getMin(), boundingBox.getMax());
		} else
		if (type == "decal") {
			auto width = 1.0f;
			auto height = 1.0f;
			auto depth = 1.0f;
			auto boundingBox = BoundingBox(Vector3(-width / 2.0f, 0.0f, -depth / 2.0f), Vector3(+width / 2.0f, height, +depth / 2.0f));
			prototype = make_unique<Prototype>(
				Prototype::ID_NONE,
				Prototype_Type::DECAL,
				Tools::removeFileExtension(fileName),
				Tools::removeFileExtension(fileName),
				pathName + "/" + fileName,
				string(),
				string(),
				nullptr
			);
			prototype->addBoundingVolume(new PrototypeBoundingVolume(prototype.get()));
			prototype->getBoundingVolume(0)->setupAabb(boundingBox.getMin(), boundingBox.getMax());
		} else
		if (type == "model") {
			prototype = make_unique<Prototype>(
				Prototype::ID_NONE,
				Prototype_Type::MODEL,
				Tools::removeFileExtension(fileName),
				Tools::removeFileExtension(fileName),
				pathName + "/" + fileName,
				"resources/engine/models/empty.tm",
				string(),
				ModelReader::read("resources/engine/models", "empty.tm") // TODO: exception
			);
		} else
		if (type == "terrain") {
			prototype = make_unique<Prototype>(
				Prototype::ID_NONE,
				Prototype_Type::TERRAIN,
				Tools::removeFileExtension(fileName),
				Tools::removeFileExtension(fileName),
				pathName + "/" + fileName,
				string(),
				string(),
				nullptr
			);
		} else
		if (type == "particle") {
			prototype = make_unique<Prototype>(
				Prototype::ID_NONE,
				Prototype_Type::PARTICLESYSTEM,
				Tools::removeFileExtension(fileName),
				Tools::removeFileExtension(fileName),
				pathName + "/" + fileName,
				string(),
				string(),
				nullptr
			);
		} else
		if (type == "scene") {
			scene = make_unique<Scene>(
				Tools::removeFileExtension(fileName),
				Tools::removeFileExtension(fileName)
			);
		}
		if (prototype != nullptr) {
			try {
				PrototypeWriter::write(pathName, fileName, prototype.get());
				browseTo(pathName + "/" + fileName);
				openFile(pathName + "/" + fileName);
			} catch (Exception& exception) {
				Console::printLine("EditorScreenController::addFile(): An error occurred: " + string(exception.what()));
				showInfoPopUp("Error", string() + "An error occurred: " + exception.what());
			}
		} else
		if (scene != nullptr) {
			try {
				SceneWriter::write(pathName, fileName, scene.get());
				browseTo(pathName + "/" + fileName);
				openFile(pathName + "/" + fileName);
			} catch (Exception& exception) {
				Console::printLine("EditorScreenController::addFile(): An error occurred: " + string(exception.what()));
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
					prototype = make_unique<Prototype>(
						Prototype::ID_NONE,
						Prototype_Type::MODEL,
						Tools::removeFileExtension(fileName),
						Tools::removeFileExtension(fileName),
						FileSystem::getInstance()->getPathName(absoluteFileName) + "/" + Tools::removeFileExtension(fileName) + ".tmodel",
						absoluteFileName,
						string(),
						model
					);
					break;
				}
			case FILETYPE_EMPTYPROTOTYPE:
				{
					prototype = unique_ptr<Prototype>(
						PrototypeReader::read(
							FileSystem::getInstance()->getPathName(absoluteFileName),
							FileSystem::getInstance()->getFileName(absoluteFileName)
						)
					);
					break;
				}
			case FILETYPE_TRIGGERPROTOTYPE:
				{
					prototype = unique_ptr<Prototype>(
						PrototypeReader::read(
							FileSystem::getInstance()->getPathName(absoluteFileName),
							FileSystem::getInstance()->getFileName(absoluteFileName)
						)
					);
					break;
				}
			case FILETYPE_ENVMAPPROTOTYPE:
				{
					scene = unique_ptr<Scene>(
						SceneReader::read(
							"resources/engine/scenes/envmap",
							"envmap.tscene"
						)
					);
					prototype = unique_ptr<Prototype>(
						PrototypeReader::read(
							FileSystem::getInstance()->getPathName(absoluteFileName),
							FileSystem::getInstance()->getFileName(absoluteFileName)
						)
					);
					break;
				}
			case FILETYPE_DECALPROTOTYPE:
				{
					prototype = unique_ptr<Prototype>(
						PrototypeReader::read(
							FileSystem::getInstance()->getPathName(absoluteFileName),
							FileSystem::getInstance()->getFileName(absoluteFileName)
						)
					);
					break;
				}
			case FILETYPE_MODELPROTOTYPE:
				{
					prototype = unique_ptr<Prototype>(
						PrototypeReader::read(
							FileSystem::getInstance()->getPathName(absoluteFileName),
							FileSystem::getInstance()->getFileName(absoluteFileName)
						)
					);
					break;
				}
			case FILETYPE_TERRAINPROTOTYPE:
				{
					prototype = unique_ptr<Prototype>(
						PrototypeReader::read(
							FileSystem::getInstance()->getPathName(absoluteFileName),
							FileSystem::getInstance()->getFileName(absoluteFileName)
						)
					);
					break;
				}
			case FILETYPE_PARTICLESYSTEMPROTOTYPE:
				{
					prototype = unique_ptr<Prototype>(
						PrototypeReader::read(
							FileSystem::getInstance()->getPathName(absoluteFileName),
							FileSystem::getInstance()->getFileName(absoluteFileName)
						)
					);
					break;
				}
			case FILETYPE_SCENE:
				{
					scene = unique_ptr<Scene>(
						SceneReader::read(
							FileSystem::getInstance()->getPathName(absoluteFileName),
							FileSystem::getInstance()->getFileName(absoluteFileName)
						)
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
		errorMessage = string(exception.what());
		Console::printLine("EditorScreenController::FileOpenThread::run(): An error occurred: " + errorMessage);
		error = true;
	}

	//
	finished = true;
}

int EditorScreenController::getSelectedTabIdx() {
	auto selectedTabId = getSelectedTabId();
	auto idx = 0;
	for (auto tab: tabViewVector) {
		if (selectedTabId == tab->getId()) return idx;
		idx++;
	}
	return -1;
}

bool EditorScreenController::selectTabAt(int idx) {
	auto tab = getTabAt(idx);
	if (tab != nullptr && screenNode->getNodeById(tab->getId()) != nullptr) {
		tabs->getController()->setValue(MutableString(tab->getId()));
		return true;
	}
	return false;
}

bool EditorScreenController::selectTab(const string& tabId) {
	auto tab = getTab(tabId);
	if (tab != nullptr && screenNode->getNodeById(tab->getId()) != nullptr) {
		tabs->getController()->setValue(MutableString(tab->getId()));
		return true;
	}
	return false;
}

void EditorScreenController::openFile(const string& absoluteFileName) {
	// should never happen but still ...
	if (fileOpenThread != nullptr) {
		Console::printLine("EditorScreenController::openFile(): " + absoluteFileName + ": file open thread is already busy with opening a file");
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
	auto tabId = "tab_" + StringTools::replace(absoluteFileName, ".", "_");
	if (selectTab(tabId) == true) return;
	tabId = GUIParser::escape(tabId);

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
	if (StringTools::endsWith(fileNameLowerCase, ".md") == true) {
		fileType = FILETYPE_MARKDOWN;
	} else
	if (fileNameLowerCase == "license" ||
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
		StringTools::endsWith(fileNameLowerCase, ".nmake") == true ||
		StringTools::endsWith(fileNameLowerCase, ".nmake.main") == true ||
		StringTools::endsWith(fileNameLowerCase, ".bat") == true ||
		StringTools::endsWith(fileNameLowerCase, ".sh") == true ||
		StringTools::endsWith(fileNameLowerCase, ".bash") == true ||
		(fileName.rfind(".") == string::npos || (fileName.rfind("/") != string::npos && fileName.rfind(".") < fileName.rfind("/")))) {
		fileType = FILETYPE_TEXT;
	} else {
		for (const auto& extension: ModelReader::getModelExtensions()) {
			if (StringTools::endsWith(fileNameLowerCase, "." + extension) == true) {
				fileType = FILETYPE_MODEL;
				break;
			}
		}
		for (const auto& extension: TextureReader::getTextureExtensions()) {
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
					fileOpenThread = make_unique<FileOpenThread>(tabId, fileType, absoluteFileName);
					fileOpenThread->start();
					break;
				}
			case FILETYPE_EMPTYPROTOTYPE:
				{
					view->getPopUps()->getProgressBarScreenController()->show("Opening empty prototype ...", false);
					fileOpenThread = make_unique<FileOpenThread>(tabId, fileType, absoluteFileName);
					fileOpenThread->start();
					break;
				}
			case FILETYPE_TRIGGERPROTOTYPE:
				{
					view->getPopUps()->getProgressBarScreenController()->show("Opening trigger prototype ...", false);
					fileOpenThread = make_unique<FileOpenThread>(tabId, fileType, absoluteFileName);
					fileOpenThread->start();
					break;
				}
			case FILETYPE_ENVMAPPROTOTYPE:
				{
					view->getPopUps()->getProgressBarScreenController()->show("Opening environment map prototype ...", false);
					fileOpenThread = make_unique<FileOpenThread>(tabId, fileType, absoluteFileName);
					fileOpenThread->start();
					break;
				}
			case FILETYPE_DECALPROTOTYPE:
				{
					view->getPopUps()->getProgressBarScreenController()->show("Opening decal prototype ...", false);
					fileOpenThread = make_unique<FileOpenThread>(tabId, fileType, absoluteFileName);
					fileOpenThread->start();
					break;
				}
			case FILETYPE_MODELPROTOTYPE:
				{
					view->getPopUps()->getProgressBarScreenController()->show("Opening model prototype...", false);
					fileOpenThread = make_unique<FileOpenThread>(tabId, fileType, absoluteFileName);
					fileOpenThread->start();
					break;
				}
			case FILETYPE_TERRAINPROTOTYPE:
				{
					view->getPopUps()->getProgressBarScreenController()->show("Opening terrain prototype ...", false);
					fileOpenThread = make_unique<FileOpenThread>(tabId, fileType, absoluteFileName);
					fileOpenThread->start();
					break;
				}
			case FILETYPE_PARTICLESYSTEMPROTOTYPE:
				{
					view->getPopUps()->getProgressBarScreenController()->show("Opening particle system prototype ...", false);
					fileOpenThread = make_unique<FileOpenThread>(tabId, fileType, absoluteFileName);
					fileOpenThread->start();
					break;
				}
			case FILETYPE_SCENE:
				{
					view->getPopUps()->getProgressBarScreenController()->show("Opening scene ...", false);
					fileOpenThread = make_unique<FileOpenThread>(tabId, fileType, absoluteFileName);
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
			case FILETYPE_MARKDOWN:
				{
					onOpenFileFinish(tabId, fileType, absoluteFileName, nullptr, nullptr);
					break;
				}
			default:
				throw ExceptionBase("Unknown file type.");
		}
	} catch (Exception& exception) {
		Console::printLine("EditorScreenController::openFile(): An error occurred: " + string(exception.what()));
		view->getPopUps()->getProgressBarScreenController()->close();
		view->getPopUps()->getInfoDialogScreenController()->close();
		showInfoPopUp("Error", "An error occurred: " + string(exception.what()));
	}
}

void EditorScreenController::onOpenFileFinish(const string& tabId, FileType fileType, const string& absoluteFileName, unique_ptr<Prototype> prototype, unique_ptr<Scene> scene) {
	auto fileName = FileSystem::getInstance()->getFileName(absoluteFileName);
	auto fileNameLowerCase = StringTools::toLowerCase(fileName);

	//
	try {
		string icon;
		string colorType;
		EditorTabView::TabType tabType = EditorTabView::TABTYPE_UNKNOWN;
		unique_ptr<TabView> tabView;
		string viewPortTemplate;
		switch (fileType) {
			case FILETYPE_MODEL:
				{
					icon = "{$icon.type_mesh}";
					colorType = "{$color.type_mesh}";
					tabType = EditorTabView::TABTYPE_MODELEDITOR;
					tabView = make_unique<ModelEditorTabView>(view, tabId, prototype.release());
					viewPortTemplate = "template_viewport_scene.xml";
					break;
				}
			case FILETYPE_EMPTYPROTOTYPE:
				{
					icon = "{$icon.type_prototype}";
					colorType = "{$color.type_prototype}";
					tabType = EditorTabView::TABTYPE_EMPTYEDITOR;
					tabView = make_unique<EmptyEditorTabView>(view, tabId, prototype.release());
					viewPortTemplate = "template_viewport_scene.xml";
					break;
				}
			case FILETYPE_TRIGGERPROTOTYPE:
				{
					icon = "{$icon.type_prototype}";
					colorType = "{$color.type_prototype}";
					tabType = EditorTabView::TABTYPE_TRIGGEREDITOR;
					tabView = make_unique<TriggerEditorTabView>(view, tabId, prototype.release());
					viewPortTemplate = "template_viewport_scene.xml";
					break;
				}
			case FILETYPE_ENVMAPPROTOTYPE:
				{
					icon = "{$icon.type_scene}";
					colorType = "{$color.type_scene}";
					tabType = EditorTabView::TABTYPE_ENVMAPEDITOR;
					tabView = make_unique<EnvMapEditorTabView>(view, tabId, scene.release(), prototype.release());
					viewPortTemplate = "template_viewport_scene.xml";
					break;
				}
			case FILETYPE_DECALPROTOTYPE:
				{
					icon = "{$icon.type_decal}";
					colorType = "{$color.type_prototype}";
					tabType = EditorTabView::TABTYPE_DECALEDITOR;
					tabView = make_unique<DecalEditorTabView>(view, tabId, prototype.release());
					viewPortTemplate = "template_viewport_scene.xml";
					break;
				}
			case FILETYPE_MODELPROTOTYPE:
				{
					icon = "{$icon.type_prototype}";
					colorType = "{$color.type_prototype}";
					tabType = EditorTabView::TABTYPE_MODELEDITOR;
					tabView = make_unique<ModelEditorTabView>(view, tabId, prototype.release());
					viewPortTemplate = "template_viewport_scene.xml";
					break;
				}
			case FILETYPE_TERRAINPROTOTYPE:
				{
					icon = "{$icon.type_terrain}";
					colorType = "{$color.type_terrain}";
					tabType = EditorTabView::TABTYPE_TERRAINEDITOR;
					tabView = make_unique<TerrainEditorTabView>(view, tabId, prototype.release());
					viewPortTemplate = "template_viewport_terrain.xml";
					break;
				}
			case FILETYPE_PARTICLESYSTEMPROTOTYPE:
				{
					icon = "{$icon.type_particle}";
					colorType = "{$color.type_particle}";
					tabType = EditorTabView::TABTYPE_PARTICLESYSTEMEDITOR;
					tabView = make_unique<ParticleSystemEditorTabView>(view, tabId, prototype.release());
					viewPortTemplate = "template_viewport_scene.xml";
					break;
				}
			case FILETYPE_SCENE:
				{
					icon = "{$icon.type_scene}";
					colorType = "{$color.type_scene}";
					tabType = EditorTabView::TABTYPE_SCENEEDITOR;
					tabView = make_unique<SceneEditorTabView>(view, tabId, scene.release());
					viewPortTemplate = "template_viewport_scene.xml";
					break;
				}
			case FILETYPE_SCREEN_TEXT:
				{
					string xmlRootNode;
					// try to read XML root node tag name
					try {
						xmlRootNode = GUIParser::getRootNode(
							FileSystem::getInstance()->getPathName(absoluteFileName),
							FileSystem::getInstance()->getFileName(absoluteFileName)
						);
					} catch (Exception& exception) {
						Console::printLine("EditorScreenController::openFile(): " + absoluteFileName + ": " + string(exception.what()));
					}
					// gui?
					if (xmlRootNode == "screen" || xmlRootNode == "template") {
						icon = "{$icon.type_gui}";
						colorType = "{$color.type_gui}";
						tabType = EditorTabView::TABTYPE_UIEDITOR;
						tabView = make_unique<UIEditorTabView>(view, tabId, screenNode, absoluteFileName);
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
						auto screenNode = unique_ptr<GUIScreenNode>(
							GUIParser::parse(
								"resources/engine/gui/",
								"tab_text.xml",
								{{ "text", StringTools::replace(StringTools::replace(text, "[", "\\["), "]", "\\]") }}
							)
						);
						tabType = EditorTabView::TABTYPE_TEXT;
						tabView = make_unique<TextEditorTabView>(view, tabId, screenNode.release(), absoluteFileName);
						viewPortTemplate = "template_viewport_plain.xml";
					}
					break;
				}
			case FILETYPE_SOUND:
				{
					icon = "{$icon.type_sound}";
					colorType = "{$color.type_sound}";
					auto audioStream = make_unique<VorbisAudioStream>(
						tabId,
						FileSystem::getInstance()->getPathName(absoluteFileName),
						FileSystem::getInstance()->getFileName(absoluteFileName)
					);
					auto screenNode = unique_ptr<GUIScreenNode>(
						GUIParser::parse(
							"resources/engine/gui/",
							"tab_sound.xml"
						)
					);
					tabType = EditorTabView::TABTYPE_SOUND;
					tabView = make_unique<SoundTabView>(view, tabId, screenNode.release(), audioStream.release());
					viewPortTemplate = "template_viewport_plain.xml";
					break;
				}
			case FILETYPE_TEXTURE:
				{
					icon = "{$icon.type_texture}";
					colorType = "{$color.type_texture}";
					auto screenNode = unique_ptr<GUIScreenNode>(
						GUIParser::parse(
							"resources/engine/gui/",
							"tab_texture.xml",
							{{ "texture", absoluteFileName}}
						)
					);
					tabType = EditorTabView::TABTYPE_TEXTURE;
					tabView = make_unique<TextureTabView>(view, tabId, screenNode.release());
					viewPortTemplate = "template_viewport_plain.xml";
					break;
				}
			case FILETYPE_VIDEO:
				{
					icon = "{$icon.type_texture}";
					colorType = "{$color.type_texture}";
					auto screenNode = unique_ptr<GUIScreenNode>(
						GUIParser::parse(
							"resources/engine/gui/",
							"tab_video.xml",
							{{ "video", absoluteFileName}}
						)
					);
					tabType = EditorTabView::TABTYPE_VIDEO;
					tabView = make_unique<VideoTabView>(view, tabId, screenNode.release());
					viewPortTemplate = "template_viewport_plain.xml";
					break;
				}
			case FILETYPE_FONT:
				{
					icon = "{$icon.type_font}";
					colorType = "{$color.type_font}";
					auto screenNode = unique_ptr<GUIScreenNode>(
						GUIParser::parse(
							"resources/engine/gui/",
							"tab_font.xml",
							{
								{ "font", absoluteFileName },
								{ "size", "20" }
							}
						)
					);
					tabType = EditorTabView::TABTYPE_FONT;
					tabView = make_unique<FontTabView>(view, tabId, screenNode.release());
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
					auto screenNode = unique_ptr<GUIScreenNode>(
						GUIParser::parse(
							"resources/engine/gui/",
							hasVisualCode == true?"tab_visualcode.xml":"tab_text.xml",
							{{ "text", StringTools::replace(StringTools::replace(text, "[", "\\["), "]", "\\]") }}
						)
					);
					tabType = EditorTabView::TABTYPE_TEXT;
					tabView = make_unique<TextEditorTabView>(view, tabId, screenNode.release(), absoluteFileName);
					viewPortTemplate = hasVisualCode == true?"template_viewport_visualcode.xml":"template_viewport_plain.xml";
					break;
				}
			case FILETYPE_MARKDOWN:
				{
					icon = "{$icon.type_script}";
					colorType = "{$color.type_script}";
					vector<Markdown::TOCEntry> toc;
					auto screenNode = unique_ptr<GUIScreenNode>(
						GUIParser::parse(
							Markdown::createGUIXML(
								FileSystem::getInstance()->getPathName(absoluteFileName),
								FileSystem::getInstance()->getFileName(absoluteFileName),
								toc
							)
						)
					);
					tabType = EditorTabView::TABTYPE_MARKDOWN;
					tabView = make_unique<MarkdownTabView>(view, tabId, screenNode.release(), toc);
					viewPortTemplate = "template_viewport_plain.xml";
					break;
				}
			default:
				throw ExceptionBase("Unknown file type.");
		}
		//
		{
			string tabsHeaderXML = "<tab id=\"" + tabId + "\" image=\"" + GUIParser::escape(icon) + "\" type-color=\"" + GUIParser::escape(colorType) + "\" value=\"" + GUIParser::escape(absoluteFileName) + "\" text=\"" + GUIParser::escape(fileName) + "\" closeable=\"true\" />\n";
			try {
				required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(tabsHeader->getId()))->addSubNodes(tabsHeaderXML, true);
			} catch (Exception& exception) {
				Console::printLine("EditorScreenController::onOpenFile(): An error occurred: " + string(exception.what()));
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
				Console::printLine("EditorScreenController::onOpenFile(): An error occurred: " + string(exception.what()));
			}
		}
		//
		tabView->initialize();
		//
		// TODO: move me into GUIFrameBufferNode
		if (Engine::getInstance()->getGraphicsRendererBackendType() != RendererBackend::RENDERERTYPE_VULKAN) {
			auto tabFrameBuffer = dynamic_cast<GUIImageNode*>(screenNode->getNodeById(tabId + "_tab_framebuffer"));
			if (tabFrameBuffer != nullptr) tabFrameBuffer->setTextureMatrix(Matrix3x3().identity().scale(Vector2(1.0f, -1.0f)).getArray());
		}
		tabViews[tabId] = EditorTabView(tabId, Tools::getFileName(absoluteFileName), tabType, tabView.release(), required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById(tabId + "_tab_framebuffer")));
		tabViewVector.push_back(&tabViews[tabId]);
		tabs->getController()->setValue(MutableString(tabId));
	} catch (Exception& exception) {
		Console::printLine("EditorScreenController::onOpenFileFinish(): An error occurred: " + string(exception.what()));
		view->getPopUps()->getProgressBarScreenController()->close();
		view->getPopUps()->getInfoDialogScreenController()->close();
		showInfoPopUp("Error", "An error occurred: " + string(exception.what()));
	}

	//
	view->getPopUps()->getProgressBarScreenController()->close();

	//
	updateFullScreenMenuEntry();
	updateTabsMenuEntries();
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
		Console::printLine("EditorScreenController::setOutlinerContent(): An error occurred: " + string(exception.what()));
	}
	setOutlinerSelection(outlinerSelection);
}

void EditorScreenController::setOutlinerAddDropDownContent(const string& xml) {
	try {
		required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(outlinerAddDropDown->getId()))->replaceSubNodes(xml, true);
	} catch (Exception& exception) {
		Console::printLine("EditorScreenController::setOutlinerAddDropDownContent(): An error occurred: " + string(exception.what()));
	}
}

void EditorScreenController::setDetailsContent(const string& xml) {
	try {
		required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(detailsScrollarea->getId()))->replaceSubNodes(xml, true);
	} catch (Exception& exception) {
		Console::printLine("EditorScreenController::setDetailsContent(): An error occurred: " + string(exception.what()));
	}
}

bool EditorScreenController::isFullScreen() {
	return required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("screen_editor_screen"))->getActiveConditions().has("fullscreen");
}

void EditorScreenController::updateFullScreenMenuEntry() {
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("menu_view_fullscreen"))->getController()->setDisabled(tabViews.empty() == true);
}

void EditorScreenController::updateTabsMenuEntries() {
	required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("menu_view_tabs"))->clearSubNodes();
	//
	if (tabViewVector.empty() == true) return;
	auto tabIdx = 0;
	string xml = "<menu-separator />\n";
	for (auto tab: tabViewVector) {
		auto imageSource = GUIParser::getEngineThemeProperties()->get("icon.type_" + FileDialogScreenController::getFileImageName(tab->getName()), "resources/engine/images/tdme.png");
		xml+= "<menu-item image='" + imageSource + "' text='" + GUIParser::escape(tab->getName()) + "' id='menu_view_tab_" + to_string(tabIdx) + "' shortcut='Ctrl+" + to_string(tabIdx + 1) + "' />\n";
		tabIdx++;
	}
	try {
		required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("menu_view_tabs"))->addSubNodes(xml, true);
	} catch (Exception& exception) {
		Console::printLine("EditorScreenController::updateTabsMenuEntries(): An error occurred: " + string(exception.what()));
	}
}

void EditorScreenController::setFullScreen(bool fullScreen) {
	if (fullScreen == true) {
		auto selectedTab = getSelectedTab();
		if (selectedTab != nullptr) {
			Application::getApplication()->setFullScreen(true);
			fullScreenTabId = selectedTab->getId();
			required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("fullscreen-content"))->moveSubNodes(
				required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById(fullScreenTabId + "-content"))
			);
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("screen_editor_screen"))->getActiveConditions().add("fullscreen");
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(fullScreenTabId + "_tab_toolbar"))->getActiveConditions().add("fullscreen");
			//
			auto selectedTabNode = screenNode->getNodeById(fullScreenTabId + "_tab");
			fullScreenTabPadding = selectedTabNode->getPadding();
			selectedTabNode->getPadding().left = 0;
			selectedTabNode->getPadding().top = 0;
			selectedTabNode->getPadding().right = 0;
			selectedTabNode->getPadding().bottom = 0;
		}
	} else
	if (fullScreenTabId.empty() == false) {
		Application::getApplication()->setFullScreen(false);
		required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById(fullScreenTabId + "-content"))->moveSubNodes(
			required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("fullscreen-content"))
		);
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(fullScreenTabId + "_tab_toolbar"))->getActiveConditions().remove("fullscreen");
		auto selectedTabNode = screenNode->getNodeById(fullScreenTabId + "_tab");
		selectedTabNode->getPadding() = fullScreenTabPadding;
		fullScreenTabId.clear();
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("screen_editor_screen"))->getActiveConditions().remove("fullscreen");
	}
}

void EditorScreenController::enableSceneMenuEntry() {
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("menu_view_scene_run"))->getController()->setDisabled(false);
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("menu_view_scene_stop"))->getController()->setDisabled(false);
}

void EditorScreenController::disableSceneMenuEntry() {
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("menu_view_scene_run"))->getController()->setDisabled(true);
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("menu_view_scene_stop"))->getController()->setDisabled(true);
}

void EditorScreenController::getViewPort(GUINode* viewPortNode, int& left, int& top, int& width, int& height) {
	const auto& constraints = viewPortNode->getComputedConstraints();
	const auto& padding = viewPortNode->getPadding();
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
		for (auto& fileEntity: getFileEntities()) {
			pendingFileEntities.push_back(move(fileEntity));
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
			scanFilesThread = nullptr;
		}
		unlockFileEntities();
	}
	if (fileOpenThread != nullptr) {
		if (fileOpenThread->isFinished() == true) {
			fileOpenThread->join();
			if (fileOpenThread->isError() == true) {
				view->getPopUps()->getProgressBarScreenController()->close();
				view->getPopUps()->getInfoDialogScreenController()->close();
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
					move(fileOpenThread->getPrototype()),
					move(fileOpenThread->getScene())
				);
			}
			fileOpenThread = nullptr;
		} else {
			view->getPopUps()->getProgressBarScreenController()->progress2(fileOpenThread->getProgress());
		}
	}
	//
	if (logUpdateRequired == true) {
		logUpdateRequired = false;
		//
		MutableString log;
		for (const auto& logMessage: logMessages) {
			log.append(StringTools::replace(StringTools::replace(logMessage, "[", "\\["), "]", "\\]"));
			log.append("\n");
		}
		logStyledTextNode->setText(log);
		//
		auto logScrollareaController = required_dynamic_cast<GUIScrollAreaController*>(logScrollarea->getController());
		if (logScrollareaController->isAtBottom() == true) logScrollareaController->scrollToBottom();
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
		).getArray()
	);
}

void EditorScreenController::onDrop(const vector<string>& paths) {
	// WIP
	view->getPopUps()->getImportDialogScreenController()->show(paths[0]);
}
