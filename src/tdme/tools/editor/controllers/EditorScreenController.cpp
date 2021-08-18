#include <tdme/tools/editor/controllers/EditorScreenController.h>

#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>

#include <tdme/audio/VorbisAudioStream.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/fileio/scenes/SceneReader.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/Prototype_Type.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/gui/elements/GUISelectBoxController.h>
#include <tdme/utilities/Action.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIFrameBufferNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/nodes/GUITextureNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/math/Matrix2D3x3.h>
#include <tdme/os/filesystem/FileNameFilter.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/controllers/ContextMenuScreenController.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/FontTabView.h>
#include <tdme/tools/editor/tabviews/ModelEditorTabView.h>
#include <tdme/tools/editor/tabviews/SceneEditorTabView.h>
#include <tdme/tools/editor/tabviews/SoundTabView.h>
#include <tdme/tools/editor/tabviews/TerrainEditorTabView.h>
#include <tdme/tools/editor/tabviews/TextureTabView.h>
#include <tdme/tools/editor/tabviews/TextEditorTabView.h>
#include <tdme/tools/editor/tabviews/UIEditorTabView.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/tools/editor/TDMEEditor.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using std::remove;
using std::string;
using std::unordered_set;
using std::vector;

using tdme::audio::VorbisAudioStream;
using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::fileio::scenes::SceneReader;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::Prototype_Type;
using tdme::gui::elements::GUISelectBoxController;
using tdme::utilities::Action;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIFrameBufferNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::nodes::GUITextureNode;
using tdme::gui::GUIParser;
using tdme::math::Matrix2D3x3;
using tdme::os::filesystem::FileNameFilter;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::controllers::ContextMenuScreenController;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabcontrollers::subcontrollers::BasePropertiesSubController;
using tdme::tools::editor::tabviews::FontTabView;
using tdme::tools::editor::tabviews::ModelEditorTabView;
using tdme::tools::editor::tabviews::SceneEditorTabView;
using tdme::tools::editor::tabviews::SoundTabView;
using tdme::tools::editor::tabviews::TerrainEditorTabView;
using tdme::tools::editor::tabviews::TextureTabView;
using tdme::tools::editor::tabviews::TextEditorTabView;
using tdme::tools::editor::tabviews::UIEditorTabView;
using tdme::tools::editor::tabviews::TabView;
using tdme::tools::editor::views::EditorView;
using tdme::tools::editor::TDMEEditor;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

EditorScreenController::EditorScreenController(EditorView* view)
{
	this->view = view;
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
		projectPathsScrollArea = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("selectbox_projectpaths_scrollarea"));
		projectPathFilesScrollArea = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("selectbox_projectpathfiles_scrollarea"));
		tabs = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("tabs"));
		tabsHeader = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("tabs-header"));
		tabsContent = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("tabs-content"));
		outliner = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("selectbox_outliner"));
		outlinerScrollarea = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("selectbox_outliner_scrollarea"));
		detailsScrollarea = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("selectbox_details_scrollarea"));
		outlinerAddDropDown = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("dropdown_outliner_add"));
	} catch (Exception& exception) {
		Console::print(string("EditorScreenController::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void EditorScreenController::dispose()
{
}

void EditorScreenController::setScreenCaption(const string& text)
{
}

void EditorScreenController::onQuit()
{
	TDMEEditor::getInstance()->quit();
}

void EditorScreenController::showErrorPopUp(const string& caption, const string& message)
{
	view->getPopUps()->getInfoDialogScreenController()->show(caption, message);
}

void EditorScreenController::onValueChanged(GUIElementNode* node)
{
	if (node->getId() == "selectbox_projectpaths") {
		string xml;
		unordered_map<string, Texture*> fileNameTextureMapping;
		scanProjectPathFiles(node->getController()->getValue().getString(), xml, fileNameTextureMapping);
		try {
			required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(projectPathFilesScrollArea->getId()))->replaceSubNodes(xml, true);
		} catch (Exception& exception) {
			Console::print(string("EditorScreenController::onValueChanged(): An error occurred: "));
			Console::println(string(exception.what()));
		}
		for (auto& fileNameTextureMappingIt: fileNameTextureMapping) {
			auto& fileName = fileNameTextureMappingIt.first;
			auto texture = fileNameTextureMappingIt.second;
			try {
				required_dynamic_cast<GUITextureNode*>(screenNode->getNodeById("projectpathfiles_file_" + GUIParser::escapeQuotes(fileName) + "_texture_normal"))->setTexture(texture);
				required_dynamic_cast<GUITextureNode*>(screenNode->getNodeById("projectpathfiles_file_" + GUIParser::escapeQuotes(fileName) + "_texture_mouseover"))->setTexture(texture);
				required_dynamic_cast<GUITextureNode*>(screenNode->getNodeById("projectpathfiles_file_" + GUIParser::escapeQuotes(fileName) + "_texture_clicked"))->setTexture(texture);
			} catch (Exception& exception) {
				Console::print(string("EditorScreenController::onValueChanged(): An error occurred: "));
				Console::println(string(exception.what()));
			}
			texture->releaseReference();
		}
	} else {
		Console::println("EditorScreenController::onValueChanged(): " + node->getId());
	}
	// forward onValueChanged to active tab tab controller
	auto selectedTab = getSelectedTab();
	if (selectedTab != nullptr) selectedTab->getTabController()->onValueChanged(node);
}

void EditorScreenController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
	if (type == GUIActionListenerType::PERFORMED) {
		if (node->getId() == "menu_file_open") {
			onOpenProject();
		} else
		if (node->getId() == "menu_file_save") {
			onSaveCurrentTab();
		} else
		if (node->getId() == "menu_file_saveas") {
			onSaveAsCurrentTab();
		} else
		if (node->getId() == "menu_file_saveall") {
			onSaveAllTabs();
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
					Console::println("EditorScreenController::onActionPerformed(): close tab: " + tab.getId());
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
					}
				};
				Engine::getInstance()->enqueueAction(new CloseTabAction(this, tabIdToClose));
			}
		} else
		if (node->getId() == "menu_file_quit") {
			TDMEEditor::getInstance()->quit();
		} else {
			Console::println("EditorScreenController::onActionPerformed(): " + node->getId());
		}
	}
	// forward onActionPerformed to active tab tab controller
	auto selectedTab = getSelectedTab();
	if (selectedTab != nullptr) selectedTab->getTabController()->onActionPerformed(type, node);
}

void EditorScreenController::onFocus(GUIElementNode* node) {
	// forward onFocus to active tab tab controller
	auto selectedTab = getSelectedTab();
	if (selectedTab != nullptr) selectedTab->getTabController()->onFocus(node);
}

void EditorScreenController::onUnfocus(GUIElementNode* node) {
	// forward onFocus to active tab tab controller
	auto selectedTab = getSelectedTab();
	if (selectedTab != nullptr) selectedTab->getTabController()->onUnfocus(node);
}

void EditorScreenController::onContextMenuRequested(GUIElementNode* node, int mouseX, int mouseY) {
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
								editorScreenController->showErrorPopUp("Warning", (string(exception.what())));
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
	// forward onContextMenuRequested to active tab tab controller
	auto selectedTab = getSelectedTab();
	if (selectedTab != nullptr) selectedTab->getTabController()->onContextMenuRequested(node, mouseX, mouseY);
}

void EditorScreenController::onOpenProject() {
	class OnOpenProject: public virtual Action
	{
	public:
		// overriden methods
		void performAction() override {
			editorScreenController->projectPath = editorScreenController->view->getPopUps()->getFileDialogScreenController()->getPathName();
			if (StringTools::endsWith(editorScreenController->projectPath, "/") == true) {
				editorScreenController->projectPath = StringTools::substring(editorScreenController->projectPath, 0, editorScreenController->projectPath.size() - 1);
			}
			Console::println("OnOpenProject::performAction(): " + editorScreenController->projectPath);
			editorScreenController->closeTabs();
			editorScreenController->clearProjectPathFiles();
			editorScreenController->scanProjectPaths();
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
		new OnOpenProject(this)
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
}

void EditorScreenController::clearProjectPathFiles() {
	required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(projectPathFilesScrollArea->getId()))->clearSubNodes();
}

void EditorScreenController::scanProjectPathFiles(const string& relativeProjectPath, string& xml, unordered_map<string, Texture*>& fileNameTextureMapping) {
	auto pathName = projectPath + "/" + relativeProjectPath;
	class ListFilter : public virtual FileNameFilter {
		public:
			virtual ~ListFilter() {}

			bool accept(const string& pathName, const string& fileName) override {
				if (fileName == ".") return false;
				if (fileName == "..") return false;
				if (FileSystem::getInstance()->isPath(pathName + "/" + fileName) == true) return false;
				auto fileNameLowerCase = StringTools::toLowerCase(fileName);
				// audio
				if (StringTools::endsWith(fileNameLowerCase, ".ogg") == true) return true;
				// code
				if (StringTools::endsWith(fileNameLowerCase, ".h") == true) return true;
				if (StringTools::endsWith(fileNameLowerCase, ".cpp") == true) return true;
				// fonts
				if (StringTools::endsWith(fileNameLowerCase, ".fnt") == true) return true;
				// images
				if (StringTools::endsWith(fileNameLowerCase, ".ico") == true) return true;
				if (StringTools::endsWith(fileNameLowerCase, ".png") == true) return true;
				// models
				if (StringTools::endsWith(fileNameLowerCase, ".dae") == true) return true;
				if (StringTools::endsWith(fileNameLowerCase, ".fbx") == true) return true;
				if (StringTools::endsWith(fileNameLowerCase, ".glb") == true) return true;
				if (StringTools::endsWith(fileNameLowerCase, ".tm") == true) return true;
				// property files
				if (StringTools::endsWith(fileNameLowerCase, ".properties") == true) return true;
				// shader
				if (StringTools::endsWith(fileNameLowerCase, ".cl") == true) return true;
				if (StringTools::endsWith(fileNameLowerCase, ".frag") == true) return true;
				if (StringTools::endsWith(fileNameLowerCase, ".glsl") == true) return true;
				if (StringTools::endsWith(fileNameLowerCase, ".vert") == true) return true;
				// tdme model
				if (StringTools::endsWith(fileNameLowerCase, ".tmodel") == true) return true;
				// tdme scene
				if (StringTools::endsWith(fileNameLowerCase, ".tscene") == true) return true;
				// tdme particle system
				if (StringTools::endsWith(fileNameLowerCase, ".tparticle") == true) return true;
				// tdme terrain
				if (StringTools::endsWith(fileNameLowerCase, ".tterrain") == true) return true;
				// tdme script
				if (StringTools::endsWith(fileNameLowerCase, ".tscript") == true) return true;
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
	};

	ListFilter listFilter;
	vector<string> files;

	if (FileSystem::getInstance()->fileExists(pathName) == false) {
		Console::println("EditorScreenController::scanProjectPathFiles(): Error: file does not exist: " + pathName);
	} else
	if (FileSystem::getInstance()->isPath(pathName) == false) {
		if (listFilter.accept(".", pathName) == true) {
			Console::println("EditorScreenController::scanProjectPathFiles(): Error: path is file: " + pathName);
		} else {
			Console::println("EditorScreenController::scanProjectPathFiles(): Error: file exist, but does not match filter: " + pathName);
		}
	} else {
		FileSystem::getInstance()->list(pathName, files, &listFilter);
		auto idx = 0;
		for (auto fileName: files) {
			auto absolutePath = pathName + "/" + fileName;
			if (FileSystem::getInstance()->isPath(pathName + "/" + fileName) == true) {
				// no op for now
			} else {
				if (idx % 2 == 0) {
					if (xml.empty() == false) {
						xml+= "</layout>\n";
					}
					xml+= "<layout alignment=\"horizontal\">\n";
				}
				// TODO: how to associate button with file name
				auto fileNameLowerCase = StringTools::toLowerCase(fileName);
				//
				string icon = "resources/engine/images/folder.png";
				string iconBig;
				string typeColor;
				if (StringTools::endsWith(fileNameLowerCase, ".ogg") == true) {
					icon = "{$icon.type_sound}";
					iconBig = "{$icon.type_sound_big}";
					typeColor = "{$color.type_sound}";
				}
				// C++/C code
				if (StringTools::endsWith(fileNameLowerCase, ".h") == true) {
					icon = "{$icon.type_script}";
					iconBig = "{$icon.type_script_big}";
					typeColor = "{$color.type_script}";
				}
				if (StringTools::endsWith(fileNameLowerCase, ".cpp") == true) {
					icon = "{$icon.type_script}";
					iconBig = "{$icon.type_script_big}";
					typeColor = "{$color.type_script}";
				}
				if (StringTools::endsWith(fileNameLowerCase, ".c") == true) {
					icon = "{$icon.type_script}";
					iconBig = "{$icon.type_script_big}";
					typeColor = "{$color.type_script}";
				}
				// fonts
				if (StringTools::endsWith(fileNameLowerCase, ".fnt") == true) {
					icon = "resources/engine/images/font.png";
					iconBig = "resources/engine/images/font_big.png";
					typeColor = "{$color.type_font}";
				}
				// images
				if (StringTools::endsWith(fileNameLowerCase, ".ico") == true) {
					icon = "{$icon.type_texture}";
					iconBig = "{$icon.type_texture_big}";
					typeColor = "{$color.type_texture}";
				}
				if (StringTools::endsWith(fileNameLowerCase, ".png") == true) {
					icon = "{$icon.type_texture}";
					iconBig = "{$icon.type_texture_big}";
					typeColor = "{$color.type_texture}";
				}
				// models
				if (StringTools::endsWith(fileNameLowerCase, ".dae") == true) {
					icon = "{$icon.type_mesh}";
					iconBig = "{$icon.type_mesh_big}";
					typeColor = "{$color.type_mesh}";
				}
				if (StringTools::endsWith(fileNameLowerCase, ".fbx") == true) {
					icon = "{$icon.type_mesh}";
					iconBig = "{$icon.type_mesh_big}";
					typeColor = "{$color.type_mesh}";
				}
				if (StringTools::endsWith(fileNameLowerCase, ".glb") == true) {
					icon = "{$icon.type_mesh}";
					iconBig = "{$icon.type_mesh_big}";
					typeColor = "{$color.type_mesh}";
				}
				if (StringTools::endsWith(fileNameLowerCase, ".tm") == true) {
					icon = "{$icon.type_mesh}";
					iconBig = "{$icon.type_mesh_big}";
					typeColor = "{$color.type_mesh}";
				}
				// property files
				if (StringTools::endsWith(fileNameLowerCase, ".properties") == true) {
					icon = "{$icon.type_script}";
					iconBig = "{$icon.type_script_big}";
					typeColor = "{$color.type_script}";
				}
				// shader
				if (StringTools::endsWith(fileNameLowerCase, ".cl") == true) {
					icon = "{$icon.type_script}";
					iconBig = "{$icon.type_script_big}";
					typeColor = "{$color.type_script}";
				}
				if (StringTools::endsWith(fileNameLowerCase, ".frag") == true) {
					icon = "{$icon.type_script}";
					iconBig = "{$icon.type_script_big}";
					typeColor = "{$color.type_script}";
				}
				if (StringTools::endsWith(fileNameLowerCase, ".glsl") == true) {
					icon = "{$icon.type_script}";
					iconBig = "{$icon.type_script_big}";
					typeColor = "{$color.type_script}";
				}
				if (StringTools::endsWith(fileNameLowerCase, ".vert") == true) {
					icon = "{$icon.type_script}";
					iconBig = "{$icon.type_script_big}";
					typeColor = "{$color.type_script}";
				}
				// tdme model
				if (StringTools::endsWith(fileNameLowerCase, ".tmodel") == true) {
					icon = "{$icon.type_prototype}";
					iconBig = "{$icon.type_prototype_big}";
					typeColor = "{$color.type_prototype}";
				}
				// tdme scene
				if (StringTools::endsWith(fileNameLowerCase, ".tscene") == true) {
					icon = "{$icon.type_scene}";
					iconBig = "{$icon.type_scene_big}";
					typeColor = "{$color.type_scene}";
				}
				// tdme particle system
				if (StringTools::endsWith(fileNameLowerCase, ".tparticle") == true) {
					icon = "{$icon.type_particle}";
					iconBig = "{$icon.type_particle_big}";
					typeColor = "{$color.type_particle}";
				}
				// tdme terrain
				if (StringTools::endsWith(fileNameLowerCase, ".tterrain") == true) {
					icon = "{$icon.type_terrain}";
					iconBig = "{$icon.type_terrain_big}";
					typeColor = "{$color.type_terrain}";
				}
				// tdme script
				if (StringTools::endsWith(fileNameLowerCase, ".tscript") == true) {
					icon = "{$icon.type_script}";
					iconBig = "{$icon.type_script_big}";
					typeColor = "{$color.type_script}";
				}
				// xml
				if (StringTools::endsWith(fileNameLowerCase, ".xml") == true) {
					icon = "{$icon.type_gui}";
					iconBig = "{$icon.type_gui_big}";
					typeColor = "{$color.type_gui}";
				}
				// files without ending
				if (fileName.rfind(".") == string::npos ||
					(fileName.rfind("/") != string::npos &&
					fileName.rfind(".") < fileName.rfind("/"))) {
					icon = "{$icon.type_script}";
					iconBig = "{$icon.type_script_big}";
					typeColor = "{$color.type_script}";
				}

				string thumbNail;
				if (StringTools::endsWith(fileNameLowerCase, ".png") == true) thumbNail = absolutePath;
				string templateSource =
					StringTools::endsWith(fileNameLowerCase, ".tmodel") == true || StringTools::endsWith(fileNameLowerCase, ".tm") == true?
						"button_template_thumbnail_texture.xml":
						"button_template_thumbnail.xml";
				vector<uint8_t> thumbnailPNGData;
				if (((StringTools::endsWith(fileNameLowerCase, ".tmodel") == true && PrototypeReader::readThumbnail(pathName, fileName, thumbnailPNGData) == true) ||
					(StringTools::endsWith(fileNameLowerCase, ".tm") == true && FileSystem::getInstance()->getThumbnailAttachment(pathName, fileName, thumbnailPNGData) == true)) &&
					thumbnailPNGData.empty() == false) {
					auto thumbnailTexture = TextureReader::readPNG("tdme.editor.projectpathfiles." + to_string(idx), thumbnailPNGData, true);
					if (thumbnailTexture != nullptr) {
						thumbnailTexture->acquireReference();
						fileNameTextureMapping[fileName] = thumbnailTexture;
						iconBig.clear();
					} else {
						// no valid thumbnail texture
						templateSource = "button_template_thumbnail.xml";
					}
				} else {
					// no valid thumbnail texture
					templateSource = "button_template_thumbnail.xml";
				}
				if (thumbNail.empty() == false) iconBig.clear();
				if (iconBig.empty() == false) icon.clear();
				xml+=
					string() +
					"<button " +
					"id=\"projectpathfiles_file_" + GUIParser::escapeQuotes(fileName) + "\" " +
					"value=\"" + GUIParser::escapeQuotes(absolutePath) + "\" " +
					"template=\"" + templateSource + "\" " +
					"size=\"75\" " +
					"thumbnail=\"" + GUIParser::escapeQuotes(thumbNail) + "\" " +
					"icon=\"" + GUIParser::escapeQuotes(icon) + "\" " +
					"icon-big=\"" + GUIParser::escapeQuotes(iconBig) + "\" " +
					"filename=\"" + GUIParser::escapeQuotes(fileName) + "\" " +
					"type-color=\"" + GUIParser::escapeQuotes(typeColor) + "\" " +
					"/>\n";
				idx++;
			}
		}
	}
	if (xml.empty() == false) {
		xml+= "</layout>\n";
	}
}

void EditorScreenController::onOpenFile(const string& absoluteFileName) {
	Console::println("EditorScreenController::onOpenFile(): " + absoluteFileName);
	// TODO: error handling
	auto fileName = FileSystem::getInstance()->getFileName(absoluteFileName);
	auto fileNameLowerCase = StringTools::toLowerCase(fileName);
	enum FileType { FILETYPE_UNKNOWN, FILETYPE_MODEL, FILETYPE_MODELPROTOTYPE, FILETYPE_TERRAINPROTOTYPE, FILETYPE_SCENE, FILETYPE_SCREEN_TEXT, FILETYPE_SOUND, FILETYPE_TEXTURE, FILETYPE_FONT, FILETYPE_TEXT };
	FileType fileType = FILETYPE_UNKNOWN;
	if (StringTools::endsWith(fileNameLowerCase, ".xml") == true) {
		fileType = FILETYPE_SCREEN_TEXT;
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".tscene") == true) {
		fileType = FILETYPE_SCENE;
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".tmodel") == true) {
		fileType = FILETYPE_MODELPROTOTYPE;
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".tterrain") == true) {
		fileType = FILETYPE_TERRAINPROTOTYPE;
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".fnt") == true) {
		fileType = FILETYPE_FONT;
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".ogg") == true) {
		fileType = FILETYPE_SOUND;
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".h") == true ||
		StringTools::endsWith(fileNameLowerCase, ".cpp") == true ||
		StringTools::endsWith(fileNameLowerCase, ".c") == true ||
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
		showErrorPopUp("Error", "File format not yet supported");
		return;
	}

	//
	auto tabId = "tab_viewport_" + StringTools::replace(absoluteFileName, ".", "_");
	tabId = StringTools::replace(tabId, "/", "_");
	if (screenNode->getNodeById(tabId) != nullptr) return;
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
					icon = "{$icon.type_mesh}";
					colorType = "{$color.type_mesh}";
					auto model = ModelReader::read(Tools::getPathName(absoluteFileName), Tools::getFileName(absoluteFileName));
					auto prototype = new Prototype(
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
					tabType = EditorTabView::TABTYPE_MODELEDITOR;
					tabView = new ModelEditorTabView(view, tabId, prototype);
					viewPortTemplate = "template_viewport_scene.xml";
					break;
				}
			case FILETYPE_MODELPROTOTYPE:
				{
					icon = "{$icon.type_prototype}";
					colorType = "{$color.type_prototype}";
					auto prototype = PrototypeReader::read(
						FileSystem::getInstance()->getPathName(absoluteFileName),
						FileSystem::getInstance()->getFileName(absoluteFileName)
					);
					tabType = EditorTabView::TABTYPE_MODELEDITOR;
					tabView = new ModelEditorTabView(view, tabId, prototype);
					viewPortTemplate = "template_viewport_scene.xml";
					break;
				}
			case FILETYPE_TERRAINPROTOTYPE:
				{
					icon = "{$icon.type_terrain}";
					colorType = "{$color.type_terrain}";
					auto prototype = PrototypeReader::read(
						FileSystem::getInstance()->getPathName(absoluteFileName),
						FileSystem::getInstance()->getFileName(absoluteFileName)
					);
					tabType = EditorTabView::TABTYPE_TERRAINEDITOR;
					tabView = new TerrainEditorTabView(view, tabId, prototype);
					viewPortTemplate = "template_viewport_terrain.xml";
					break;
				}
			case FILETYPE_SCENE:
				{
					icon = "{$icon.type_scene}";
					colorType = "{$color.type_scene}";
					auto scene = SceneReader::read(
						FileSystem::getInstance()->getPathName(absoluteFileName),
						FileSystem::getInstance()->getFileName(absoluteFileName)
					);
					tabType = EditorTabView::TABTYPE_SCENEEDITOR;
					tabView = new SceneEditorTabView(view, tabId, scene);
					viewPortTemplate = "template_viewport_scene.xml";
					break;
				}
			case FILETYPE_SCREEN_TEXT:
				{
					try {
						icon = "{$icon.type_gui}";
						colorType = "{$color.type_gui}";
						auto screenNode = GUIParser::parse(
							FileSystem::getInstance()->getPathName(absoluteFileName),
							FileSystem::getInstance()->getFileName(absoluteFileName)
						);
						tabType = EditorTabView::TABTYPE_UIEDITOR;
						tabView = new UIEditorTabView(view, tabId, screenNode);
					} catch (Exception &exception) {
						icon = "{$icon.type_script}";
						colorType = "{$color.type_script}";
						auto text = StringTools::replace(
							FileSystem::getInstance()->getContentAsString(
								FileSystem::getInstance()->getPathName(absoluteFileName),
								FileSystem::getInstance()->getFileName(absoluteFileName)
							),
							"\t",
							"    "
						);
						auto screenNode = GUIParser::parse(
							"resources/engine/gui/",
							"tab_text.xml",
							{{ "text", text }}
						);
						tabType = EditorTabView::TABTYPE_TEXT;
						tabView = new TextEditorTabView(view, tabId, screenNode);
					}
					viewPortTemplate = "template_viewport_plain.xml";
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
			case FILETYPE_FONT:
				{
					icon = "{$icon.type_font}";
					colorType = "{$color.type_font}";
					auto screenNode = GUIParser::parse(
						"resources/engine/gui/",
						"tab_font.xml",
						{{ "font", absoluteFileName }}
					);
					tabType = EditorTabView::TABTYPE_FONT;
					tabView = new FontTabView(view, tabId, screenNode);
					viewPortTemplate = "template_viewport_plain.xml";
					break;
				}
			case FILETYPE_TEXT:
				{
					icon = "{$icon.type_script}";
					colorType = "{$color.type_script}";
					auto text = StringTools::replace(
						FileSystem::getInstance()->getContentAsString(
							FileSystem::getInstance()->getPathName(absoluteFileName),
							FileSystem::getInstance()->getFileName(absoluteFileName)
						),
						"\t",
						"    "
					);
					auto screenNode = GUIParser::parse(
						"resources/engine/gui/",
						"tab_text.xml",
						{{ "text", text }}
					);
					tabType = EditorTabView::TABTYPE_TEXT;
					tabView = new TextEditorTabView(view, tabId, screenNode);
					viewPortTemplate = "template_viewport_plain.xml";
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
		required_dynamic_cast<GUIFrameBufferNode*>(screenNode->getNodeById(tabId + "_tab_framebuffer"))->setTextureMatrix((new Matrix2D3x3())->identity().scale(Vector2(1.0f, -1.0f)));
		tabViews[tabId] = EditorTabView(tabId, tabType, tabView, tabView->getTabController(), tabView->getEngine(), required_dynamic_cast<GUIFrameBufferNode*>(screenNode->getNodeById(tabId + "_tab_framebuffer")));
	} catch (Exception& exception) {
		Console::print(string("EditorScreenController::onOpenFile(): An error occurred: "));
		Console::println(string(exception.what()));
		showErrorPopUp("Error", string() + "An error occurred: " + exception.what());
	}
}

void EditorScreenController::storeOutlinerState(TabView::OutlinerState& outlinerState) {
	required_dynamic_cast<GUISelectBoxController*>(outliner->getController())->determineExpandedParentOptionValues(outlinerState.expandedOutlinerParentOptionValues);
	outlinerState.value = required_dynamic_cast<GUISelectBoxController*>(screenNode->getNodeById("selectbox_outliner")->getController())->getValue();
	outlinerState.renderOffsetX = required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("selectbox_outliner_scrollarea"))->getChildrenRenderOffsetX();
	outlinerState.renderOffsetY = required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("selectbox_outliner_scrollarea"))->getChildrenRenderOffsetY();
}

void EditorScreenController::restoreOutlinerState(const TabView::OutlinerState& outlinerState) {
	required_dynamic_cast<GUISelectBoxController*>(outliner->getController())->setValue(outlinerState.value);
	required_dynamic_cast<GUISelectBoxController*>(outliner->getController())->expandParentOptionsByValues(outlinerState.expandedOutlinerParentOptionValues);
	required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(outlinerScrollarea->getId()))->setChildrenRenderOffsetX(outlinerState.renderOffsetX);
	required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(outlinerScrollarea->getId()))->setChildrenRenderOffsetY(outlinerState.renderOffsetY);
}

const string EditorScreenController::getOutlinerSelection() {
	try {
		return outliner->getController()->getValue().getString();
	} catch (Exception& exception) {
		Console::print(string("EditorScreenController::getOutlinerSelection(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	return string();
}

void EditorScreenController::setOutlinerSelection(const string& newSelectionValue) {
	try {
		outliner->getController()->setValue(MutableString(newSelectionValue));
	} catch (Exception& exception) {
		Console::print(string("EditorScreenController::setOutlinerSelection(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void EditorScreenController::setOutlinerContent(const string& xml) {
	try {
		required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(outlinerScrollarea->getId()))->replaceSubNodes(xml, true);
	} catch (Exception& exception) {
		Console::print(string("EditorScreenController::setOutlinerContent(): An error occurred: "));
		Console::println(string(exception.what()));
	}
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

void EditorScreenController::onSaveCurrentTab() {
	// forward save to active tab tab controller
	auto selectedTab = getSelectedTab();
	if (selectedTab != nullptr) selectedTab->getTabController()->save();
}

void EditorScreenController::onSaveAsCurrentTab() {
	// forward saveAs to active tab tab controller
	auto selectedTab = getSelectedTab();
	if (selectedTab != nullptr) selectedTab->getTabController()->saveAs();
}

void EditorScreenController::onSaveAllTabs() {
	// forward saveAs to active tab tab controller
	for (auto& tabViewIt: tabViews) {
		auto& tab = tabViewIt.second;
		tab.getTabController()->save();
	}
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
