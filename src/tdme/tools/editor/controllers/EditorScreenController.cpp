#include <tdme/tools/editor/controllers/EditorScreenController.h>

#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>

#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/gui/events/Action.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIFrameBufferNode.h>
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
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/ModelEditorTabView.h>
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

using tdme::engine::FrameBuffer;
using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::gui::events::Action;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIFrameBufferNode;
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
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypeBaseSubController;
using tdme::tools::editor::tabviews::ModelEditorTabView;
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
		projectPathsScrollArea = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("selectbox_projectpaths_scrollarea"));
		projectPathFilesScrollArea = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("selectbox_projectpathfiles_scrollarea"));
		tabs = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("tabs"));
		tabsHeader = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("tabs-header"));
		tabsContent = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("tabs-content"));
		outlinerScrollarea = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("selectbox_outliner_scrollarea"));
		detailsScrollarea = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("selectbox_details_scrollarea"));
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
		scanProjectPathFiles(node->getController()->getValue().getString(), xml);
		try {
			required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(projectPathFilesScrollArea->getId()))->replaceSubNodes(xml, true);
		} catch (Exception& exception) {
			Console::print(string("EditorScreenController::onValueChanged(): An error occurred: "));
			Console::println(string(exception.what()));
		}
	} else {
		Console::println("EditorScreenController::onValueChanged(): " + node->getId());
	}
	// forward onValueChanged to active tab tab controller
	auto selectedTabId = getSelectedTabId();
	auto tabViewIt = tabViews.find(selectedTabId);
	if (tabViewIt != tabViews.end()){
		auto& tab = tabViewIt->second;
		tab.getTabController()->onValueChanged(node);
	}
}

void EditorScreenController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
	if (type == GUIActionListenerType::PERFORMED) {
		if (node->getId() == "menu_file_open") {
			onOpenProject();
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
				screenNode->removeNodeById(tabIdToClose, false);
				screenNode->removeNodeById(tabIdToClose + "-content", false);
				auto tabIt = tabViews.find(tabIdToClose);
				if (tabIt == tabViews.end()) {
					Console::println("EditorScreenController::onActionPerformed(): close tab: " + tabIdToClose + ": not found");
				} else {
					auto& tab = tabIt->second;
					tab.getTabView()->dispose();
					delete tab.getTabView();
					tabViews.erase(tabIt);
				}
				setDetailsContent(string());
				setOutlinerContent(string());
			}
		} else {
			Console::println("EditorScreenController::onActionPerformed(): " + node->getId());
		}
	}
	// forward onActionPerformed to active tab tab controller
	auto selectedTabId = getSelectedTabId();
	auto tabViewIt = tabViews.find(selectedTabId);
	if (tabViewIt != tabViews.end()){
		auto& tab = tabViewIt->second;
		tab.getTabController()->onActionPerformed(type, node);
	}
}

void EditorScreenController::onFocus(GUIElementNode* node) {
	// forward onFocus to active tab tab controller
	auto selectedTabId = getSelectedTabId();
	auto tabViewIt = tabViews.find(selectedTabId);
	if (tabViewIt != tabViews.end()){
		auto& tab = tabViewIt->second;
		tab.getTabController()->onFocus(node);
	}
}

void EditorScreenController::onUnfocus(GUIElementNode* node) {
	// forward onFocus to active tab tab controller
	auto selectedTabId = getSelectedTabId();
	auto tabViewIt = tabViews.find(selectedTabId);
	if (tabViewIt != tabViews.end()){
		auto& tab = tabViewIt->second;
		tab.getTabController()->onUnfocus(node);
	}
}

void EditorScreenController::onOpenProject() {
	class OnOpenProject: public virtual Action
	{
	public:
		// overriden methods
		void performAction() override {
			editorScreenController->projectPath = editorScreenController->view->getPopUps()->getFileDialogScreenController()->getPathName();
			editorScreenController->view->getPopUps()->getFileDialogScreenController()->close();
			Console::println("OnOpenProject::performAction(): " + editorScreenController->projectPath);
			editorScreenController->scanProjectPaths();
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

void EditorScreenController::scanProjectPathFiles(const string& relativeProjectPath, string& xml) {
	auto path = projectPath + "/" + relativeProjectPath;
	Console::println("EditorScreenController::scanProjectPathFiles(): " + path);
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
				return false;			}
	};

	ListFilter listFilter;
	vector<string> files;

	if (FileSystem::getInstance()->fileExists(path) == false) {
		Console::println("EditorScreenController::scanProjectPathFiles(): Error: file does not exist: " + path);
	} else
	if (FileSystem::getInstance()->isPath(path) == false) {
		if (listFilter.accept(".", path) == true) {
			Console::println("EditorScreenController::scanProjectPathFiles(): Error: path is file" + path);
		} else {
			Console::println("EditorScreenController::scanProjectPathFiles(): Error: file exist, but does not match filter: " + path);
		}
	} else {
		FileSystem::getInstance()->list(path, files, &listFilter);
		auto idx = 0;
		for (auto fileName: files) {
			auto relativePath = path + "/" + fileName;
			if (StringTools::startsWith(relativePath, projectPath)) relativePath = StringTools::substring(relativePath, projectPath.size() + 1, relativePath.size());
			if (FileSystem::getInstance()->isPath(path + "/" + fileName) == true) {
				// no op for now
			} else {
				if (idx % 2 == 0) {
					if (xml.empty() == false) {
						xml+= "</layout>\n";
					}
					xml+= "<layout alignment=\"horizontal\">\n";
				}
				// TODO: how to associate button with file name
				xml+= "<button id=\"projectpathfiles_file_" + GUIParser::escapeQuotes(fileName) + "\" value=\"" + GUIParser::escapeQuotes(relativePath) + "\" template=\"button_template_thumbnail.xml\" size=\"75\" thumbnail=\"resources/engine/textures/terrain_dirt.png\" icon=\"resources/engine/images/folder.png\" filename=\"" + GUIParser::escapeQuotes(fileName) + "\" />\n";
				idx++;
			}
		}
	}
	if (xml.empty() == false) {
		xml+= "</layout>\n";
	}
}

void EditorScreenController::onOpenFile(const string& relativeProjectFileName) {
	auto absoluteFileName = projectPath + "/" + relativeProjectFileName;
	Console::println("EditorScreenController::onOpenFile(): " + absoluteFileName);
	auto fileName = FileSystem::getInstance()->getFileName(relativeProjectFileName);
	auto tabId = "tab_viewport_" + StringTools::replace(relativeProjectFileName, ".", "_");
	tabId = StringTools::replace(tabId, "/", "_");
	tabId = GUIParser::escapeQuotes(tabId);
	//
	{
		string tabsHeaderXML = "<tab id=\"" + tabId + "\" value=\"" + GUIParser::escapeQuotes(relativeProjectFileName) + "\" text=\"" + GUIParser::escapeQuotes(fileName) + "\" closeable=\"true\" />\n";
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
			"	<template id=\"" + tabId + "_tab\" src=\"resources/engine/gui/template_viewport_scene.xml\" />\n" +
			"</tab-content>\n";
		try {
			required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(tabsContent->getId()))->addSubNodes(tabsContentXML, true);
		} catch (Exception& exception) {
			Console::print(string("EditorScreenController::onOpenFile(): An error occurred: "));
			Console::println(string(exception.what()));
		}
	}
	// try {
		auto prototype = PrototypeReader::read(
			FileSystem::getInstance()->getPathName(absoluteFileName),
			FileSystem::getInstance()->getFileName(absoluteFileName)
		);
		auto tabView = new ModelEditorTabView(view, tabId, prototype);
		tabView->initialize();
		required_dynamic_cast<GUIFrameBufferNode*>(screenNode->getNodeById(tabId + "_tab_framebuffer"))->setTextureMatrix(Matrix2D3x3::rotateAroundTextureCenter(180.0f));
		tabViews[tabId] = EditorTabView(tabId, tabView, tabView->getTabController(), tabView->getEngine(), required_dynamic_cast<GUIFrameBufferNode*>(screenNode->getNodeById(tabId + "_tab_framebuffer")));
	/*
	} catch (Exception& exception) {
		Console::print(string("EditorScreenController::onOpenFile(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	*/
}

const string EditorScreenController::getOutlinerSelection() {
	try {
		return required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("selectbox_outliner"))->getController()->getValue().getString();
	} catch (Exception& exception) {
		Console::print(string("EditorScreenController::getOutlinerSelection(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	return string();
}

void EditorScreenController::setOutlinerContent(const string& xml) {
	try {
		required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(outlinerScrollarea->getId()))->replaceSubNodes(xml, true);
	} catch (Exception& exception) {
		Console::print(string("EditorScreenController::setOutlinerContent(): An error occurred: "));
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
