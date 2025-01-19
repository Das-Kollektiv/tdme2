#include <tdme/tools/editor/controllers/FileDialogScreenController.h>

#include <algorithm>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/Engine.h>
#include <agui/gui/events/GUIActionListener.h>
#include <agui/gui/events/GUIChangeListener.h>
#include <agui/gui/events/GUITooltipRequestListener.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIParentNode.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/nodes/GUITextNode.h>
#include <agui/gui/GUI.h>
#include <agui/gui/GUIParser.h>
#include <tdme/os/filesystem/FileNameFilter.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/controllers/TooltipScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <agui/utilities/MutableString.h>
#include <tdme/utilities/Properties.h>
#include <tdme/utilities/StringTools.h>

using std::remove;
using std::reverse;
using std::string;
using std::unique_ptr;
using std::unordered_map;
using std::vector;

using tdme::tools::editor::controllers::FileDialogScreenController;

using tdme::engine::Engine;
using agui::gui::events::GUIActionListener;
using agui::gui::events::GUIActionListenerType;
using agui::gui::events::GUITooltipRequestListener;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIParentNode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::nodes::GUITextNode;
using agui::gui::GUI;
using agui::gui::GUIParser;
using tdme::os::filesystem::FileNameFilter;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::controllers::TooltipScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using agui::utilities::MutableString;
using tdme::utilities::Properties;
using tdme::utilities::StringTools;

FileDialogScreenController::FileDialogScreenController(PopUps* popUps)
{
	this->popUps = popUps;
	this->cwd = FileSystem::getStandardFileSystem()->getCurrentWorkingPathName();
}

FileDialogScreenController::~FileDialogScreenController() {
}

const string FileDialogScreenController::getFileName()
{
	return fileNameNode->getController()->getValue().getString();
}

void FileDialogScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse("resources/engine/gui", "popup_filedialog.xml");
		screenNode->setEnabled(false);
		screenNode->addActionListener(this);
		screenNode->addChangeListener(this);
		screenNode->addFocusListener(this);
		screenNode->addTooltipRequestListener(this);
		tabsHeaderNode = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("filedialog_tabs-header"));
		pathNode = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("filedialog_path"));
		filesNode = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("filedialog_files"));
		favoritesNode = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("filedialog_favorites"));
		recentsNode = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("filedialog_recent"));
		drivesNode = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("filedialog_drives"));
		fileNameNode = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("filedialog_filename"));
		typeDropDownNode = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("filedialog_typedropdown"));
	} catch (Exception& exception) {
		Console::printLine("FileDialogScreenController::initialize(): An error occurred: " + string(exception.what()));
	}
}

void FileDialogScreenController::dispose()
{
	screenNode = nullptr;
}

bool FileDialogScreenController::setupFiles()
{
	class ExtensionFilter: public virtual FileNameFilter
	{
	public:
		bool accept(const string& pathName, const string& fileName) override {
			if (FileSystem::getStandardFileSystem()->isPath(pathName + "/" + fileName) == true) return true;
			if (extension.empty() == false) {
				if (StringTools::endsWith(StringTools::toLowerCase(fileName), "." + extension) == true) return true;
			} else {
				for (const auto& extension : fileDialogScreenController->extensions) {
					if (StringTools::endsWith(StringTools::toLowerCase(fileName), "." + extension) == true) return true;
				}
			}
			return false;
		}

		/**
		 * Public constructor
		 * @param fileDialogScreenController file dialog screen controller
		 */
		ExtensionFilter(FileDialogScreenController* fileDialogScreenController, const string& extension): fileDialogScreenController(fileDialogScreenController), extension(extension) {
		}

	private:
		FileDialogScreenController* fileDialogScreenController;
		string extension;
	};

	//
	required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(tabsHeaderNode->getId()))->replaceSubNodes("<tab id=\"filedialog_caption\" image=\"resources/engine/images/attention.png\" text=\"" + GUIParser::escape(captionText)+ "\" closeable=\"true\"/>", true);
	pathNode->getController()->setValue(MutableString(cwd));

	//
	fileList.clear();
	auto success = true;
	try {
		auto directory = cwd;
		ExtensionFilter extensionsFilter(this, typeDropDownNode->getController()->getValue().getString());
		FileSystem::getStandardFileSystem()->list(directory, fileList, &extensionsFilter);
	} catch (Exception& exception) {
		Console::printLine("FileDialogScreenController::setupFileDialogListBox(): An error occurred: " + string(exception.what()));
		success = false;
	}
	setupFiles(fileList);
	if (enableFilter == true) fileNameNode->getController()->setValue(MutableString("Type a string to filter the list..."));

	//
	filtered = false;

	//
	return success;
}

void FileDialogScreenController::setupFiles(const vector<string>& fileNameList, const string& selectedFileName) {
	auto filesInnerNode = required_dynamic_cast<GUIParentNode*>(filesNode->getScreenNode()->getInnerNodeById(filesNode->getId()));
	auto idx = 1;
	string filesInnerNodeSubNodesXML;
	filesInnerNodeSubNodesXML+=
		"<scrollarea width=\"100%\" height=\"100%\" background-color=\"{$color.element_midground}\">\n";
	for (const auto& fileName : fileNameList) {
		auto fileImageName = getFileImageName(fileName);
		try {
			if (FileSystem::getStandardFileSystem()->isPath(cwd + "/" + fileName) == true) fileImageName = "folder";
		} catch (Exception& exception) {
			Console::printLine("FileDialogScreenController::setupFileDialogListBox(): An error occurred: " + string(exception.what()));
		}
		filesInnerNodeSubNodesXML+=
			"<selectbox-option text=\"" +
			GUIParser::escape(fileName) +
			"\" value=\"" +
			GUIParser::escape(fileName) +
			"\"" +
			(selectedFileName == fileName?" selected=\"true\"":"") + " " +
			"image=\"{$icon.type_" + fileImageName + "}\" " +
			"/>\n";
	}
	filesInnerNodeSubNodesXML+= "</scrollarea>\n";
	try {
		filesInnerNode->replaceSubNodes(filesInnerNodeSubNodesXML, false);
	} catch (Exception& exception) {
		Console::printLine("FileDialogScreenController::setupFileDialogListBox(): An error occurred: " + string(exception.what()));
	}
}

void FileDialogScreenController::setupFavorites() {
	auto favoritesInnerNode = required_dynamic_cast<GUIParentNode*>(favoritesNode->getScreenNode()->getInnerNodeById(favoritesNode->getId()));
	auto idx = 1;
	string favoritesInnerNodeSubNodesXML;
	favoritesInnerNodeSubNodesXML+=
		"<scrollarea width=\"100%\" height=\"100%\" background-color=\"{$color.element_midground}\">\n";
	for (const auto& favorite: favorites) {
		auto fileImageName = "folder";
		favoritesInnerNodeSubNodesXML+=
			"<selectbox-option text=\"" +
			GUIParser::escape(FileSystem::getStandardFileSystem()->getFileName(StringTools::endsWith(favorite, "/") == true?StringTools::substring(favorite, 0, favorite.size() - 1):favorite)) +
			"\" value=\"" +
			GUIParser::escape(favorite) +
			"\" " +
			"image=\"{$icon.type_folder}\" " +
			"/>\n";
	}
	favoritesInnerNodeSubNodesXML+= "</scrollarea>\n";
	try {
		favoritesInnerNode->replaceSubNodes(favoritesInnerNodeSubNodesXML, false);
	} catch (Exception& exception) {
		Console::printLine("FileDialogScreenController::setupFavorites(): An error occurred: " + string(exception.what()));
	}
}

void FileDialogScreenController::setupRecents() {
	auto recentsInnerNode = required_dynamic_cast<GUIParentNode*>(recentsNode->getScreenNode()->getInnerNodeById(recentsNode->getId()));
	auto idx = 1;
	string recentsInnerNodeSubNodesXML;
	recentsInnerNodeSubNodesXML+=
		"<scrollarea width=\"100%\" height=\"100%\" background-color=\"{$color.element_midground}\">\n";
	auto recentsReversed = recents;
	reverse(recentsReversed.begin(), recentsReversed.end());
	for (const auto& recent: recentsReversed) {
		auto fileImageName = "folder";
		recentsInnerNodeSubNodesXML+=
			"<selectbox-option text=\"" +
			GUIParser::escape(FileSystem::getStandardFileSystem()->getFileName(StringTools::endsWith(recent, "/") == true?StringTools::substring(recent, 0, recent.size() - 1):recent)) +
			"\" value=\"" +
			GUIParser::escape(recent) +
			"\" " +
			"image=\"{$icon.type_folder}\" " +
			"/>\n";
	}
	recentsInnerNodeSubNodesXML+= "</scrollarea>\n";
	try {
		recentsInnerNode->replaceSubNodes(recentsInnerNodeSubNodesXML, false);
	} catch (Exception& exception) {
		Console::printLine("FileDialogScreenController::setupRecents(): An error occurred: " + string(exception.what()));
	}
}

void FileDialogScreenController::setupDrives() {
	vector<string> drives;
	#if defined(_WIN32)
		for (char drive = 'A'; drive <= 'Z'; drive++) {
			string fileName;
			fileName+= drive;
			fileName+= ":";
			try {
				if (FileSystem::getStandardFileSystem()->exists(fileName + "/") == true) drives.push_back(fileName);
			} catch (Exception& exception) {
				Console::printLine("FileDialogScreenController::setupDrives(): " + string(exception.what()));
			}
		}
	#else
		drives.push_back("/");
	#endif
	auto drivesInnerNode = required_dynamic_cast<GUIParentNode*>(drivesNode->getScreenNode()->getInnerNodeById(drivesNode->getId()));
	auto idx = 1;
	string drivesInnerNodeSubNodesXML;
	drivesInnerNodeSubNodesXML+=
		"<scrollarea width=\"100%\" height=\"100%\" background-color=\"{$color.element_midground}\">\n";
	for (const auto& drive: drives) {
		drivesInnerNodeSubNodesXML+=
			"<selectbox-option text=\"" +
			GUIParser::escape(drive) +
			"\" value=\"" +
			GUIParser::escape(drive) +
			"\" " +
			"image=\"{$icon.type_drive}\" " +
			"/>\n";
	}
	drivesInnerNodeSubNodesXML+= "</scrollarea>\n";
	try {
		drivesInnerNode->replaceSubNodes(drivesInnerNodeSubNodesXML, false);
	} catch (Exception& exception) {
		Console::printLine("FileDialogScreenController::setupDrives(): An error occurred: " + string(exception.what()));
	}
}

void FileDialogScreenController::show(const string& cwd, const string& captionText, const vector<string>& extensions, const string& fileName, bool enableFilter, Action* applyAction, Action* cancelAction, const string& settingsFileName, const string& settingsPathName)
{
	this->settingsPathName = settingsPathName;
	this->settingsFileName = settingsFileName;
	loadSettings();
	this->captionText = captionText;
	this->extensions = extensions;
	this->fileNameNode->getController()->setValue(fileName);
	this->enableFilter = enableFilter;
	auto _cwd = cwd;
	if (cwd.empty() == true) {
		auto defaultCwdByExtensionsIt = defaultCwdByExtensions.find(getExtensionHash());
		if (defaultCwdByExtensionsIt != defaultCwdByExtensions.end()) {
			_cwd = defaultCwdByExtensionsIt->second;
		} else {
			_cwd = defaultCwd;
		}
	}
	try {
		this->cwd = FileSystem::getStandardFileSystem()->getCanonicalURI(_cwd, "");
		if (this->cwd.empty() == true || FileSystem::getStandardFileSystem()->isPath(this->cwd) == false) {
			this->cwd = FileSystem::getStandardFileSystem()->getCurrentWorkingPathName();
		}
	} catch (Exception& exception) {
		Console::printLine("FileDialogScreenController::show(): An error occurred: " + string(exception.what()));
		this->cwd = FileSystem::getStandardFileSystem()->getCurrentWorkingPathName();
	}
	setupFiles();
	this->applyAction = unique_ptr<Action>(applyAction);
	this->cancelAction = unique_ptr<Action>(cancelAction);
	{
		string extensionsDropDownOptionsXML = "<dropdown-option text=\"All supported extensions\" value=\"\" selected=\"true\"/>\n";
		for (const auto& extension: extensions) {
			extensionsDropDownOptionsXML+= "<dropdown-option text=\"" + StringTools::toUpperCase(extension) + " Files\" value=\"" + StringTools::toLowerCase(extension) + "\" selected=\"false\" />\n";
		}
		required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(typeDropDownNode->getId()))->replaceSubNodes(extensionsDropDownOptionsXML, true);
	}
	setupDrives();
	setupFavorites();
	setupRecents();
	//
	screenNode->setEnabled(true);
	Engine::getInstance()->getGUI()->setFoccussedNode(fileNameNode);
}

void FileDialogScreenController::close()
{
	screenNode->setEnabled(false);
	applyAction = nullptr;
	cancelAction = nullptr;
}

void FileDialogScreenController::onChange(GUIElementNode* node)
{
	if (node->getId() == typeDropDownNode->getId()) {
		setupFiles();
	} else
	if (node->getId() == fileNameNode->getId()) {
		try {
			if (enableFilter == true) {
				auto filterString = StringTools::toLowerCase(node->getController()->getValue().getString());
				if (FileSystem::getStandardFileSystem()->exists(cwd + "/" + filterString) == true) {
					auto selectedFile = node->getController()->getValue().getString();
					setupFiles(fileList, selectedFile);
				} else
				if (filterString.empty() == true) {
					setupFiles(fileList);
				} else {
					vector<string> fileListFiltered;
					for (const auto& file: fileList) {
						if (filterString.empty() == true || StringTools::toLowerCase(file).find(filterString) != -1) fileListFiltered.push_back(file);
					}
					setupFiles(fileListFiltered);
					filtered = true;
				}
			}
		} catch (Exception& exception) {
			Console::printLine("FileDialogScreenController::onChange(): An error occurred: " + string(exception.what()));
			fileNameNode->getController()->setValue(MutableString());
		}
	}
}

void FileDialogScreenController::onAction(GUIActionListenerType type, GUIElementNode* node)
{
	if (type == GUIActionListenerType::PERFORMED) {
		if (node->getId() == filesNode->getId()) {
			try {
				auto selectedFile = node->getController()->getValue().getString();
				if (FileSystem::getStandardFileSystem()->isDrive(selectedFile) == true) {
					auto lastCwd = cwd;
					cwd = selectedFile;
					if (setupFiles() == false) {
						cwd = lastCwd;
						setupFiles();
					}
				} else
				if (FileSystem::getStandardFileSystem()->isPath(cwd + "/" + selectedFile) == true) {
					auto lastCwd = cwd;
					try {
						cwd = FileSystem::getStandardFileSystem()->getCanonicalURI(cwd, selectedFile);
					} catch (Exception& exception) {
						Console::printLine("FileDialogScreenController::onAction(): An error occurred: " + string(exception.what()));
					}
					if (setupFiles() == false) {
						cwd = lastCwd;
						setupFiles();
					}
				} else {
					if (filtered == true) {
						setupFiles(fileList, selectedFile);
						filtered = false;
					}
					fileNameNode->getController()->setValue(selectedFile);
				}
			} catch (Exception& exception) {
				Console::printLine("FileDialogScreenController::onAction(): An error occurred: " + string(exception.what()));
				fileNameNode->getController()->setValue(MutableString());
			}
		} else
		if (node->getId() == pathNode->getId()) {
			if (StringTools::endsWith(cwd, "/") == true) cwd = StringTools::substring(cwd, 0, cwd.size() - 1);
			auto lastCwd = cwd;
			cwd = pathNode->getController()->getValue().getString();
			if (setupFiles() == true) {
				recents.erase(remove(recents.begin(), recents.end(), cwd), recents.end());
				recents.push_back(cwd);
				setupRecents();
				saveSettings();
			} else {
				cwd = lastCwd;
				setupFiles();
			}
		} else
		if (node->getId() == "filedialog_apply") {
			if (StringTools::endsWith(cwd, "/") == true) cwd = StringTools::substring(cwd, 0, cwd.size() - 1);
			defaultCwdByExtensions[getExtensionHash()] = cwd;
			recents.erase(remove(recents.begin(), recents.end(), cwd), recents.end());
			recents.push_back(cwd);
			setupRecents();
			saveSettings();
			if (applyAction != nullptr) {
				applyAction->performAction();
				applyAction = nullptr;
			}
		} else
		if (node->getId() == "filedialog_abort" ||
			StringTools::startsWith(node->getId(), "filedialog_caption_close_") == true) { // TODO: a.drewke, check with DH
			if (defaultCwd.empty() == false) {
				defaultCwdByExtensions[getExtensionHash()] = cwd;
				saveSettings();
			}
			if (cancelAction != nullptr) {
				cancelAction->performAction();
				cancelAction = nullptr;
			}
			close();
		} else
		if (node->getId() == "filedialog_favorites_add") {
			if (StringTools::endsWith(cwd, "/") == true) cwd = StringTools::substring(cwd, 0, cwd.size() - 1);
			favorites.erase(remove(favorites.begin(), favorites.end(), cwd), favorites.end());
			favorites.push_back(cwd);
			setupFavorites();
		} else
		if (node->getId() == "filedialog_favorites_remove") {
			auto favorite = favoritesNode->getController()->getValue().getString();
			favorites.erase(remove(favorites.begin(), favorites.end(), favorite), favorites.end());
			setupFavorites();
		} else
		if (node->getId() == "filedialog_recent_delete") {
			recents.clear();
			setupRecents();
			saveSettings();
		} else
		if (node == favoritesNode) {
			auto _cwd = favoritesNode->getController()->getValue().getString();
			if (_cwd.empty() == false) {
				cwd = _cwd;
				setupFiles();
			}
		} else
		if (node == drivesNode) {
			auto _cwd = drivesNode->getController()->getValue().getString();
			if (_cwd.empty() == false) {
				cwd = _cwd;
				setupFiles();
			}
		} else
		if (node == recentsNode) {
			auto _cwd = recentsNode->getController()->getValue().getString();
			if (_cwd.empty() == false) {
				cwd = _cwd;
				setupFiles();
			}
		}
	}
}

void FileDialogScreenController::onFocus(GUIElementNode* node) {
	GUI::setDisableTabFocusControl(node->getScreenNode() != screenNode);
	if (node->getId() == "filedialog_filename") {
		if (enableFilter == true) node->getController()->setValue(MutableString(""));
	}
}

void FileDialogScreenController::onUnfocus(GUIElementNode* node) {
}

void FileDialogScreenController::loadSettings() {
	// TODO: load relative paths
	defaultCwdByExtensions.clear();
	favorites.clear();
	recents.clear();
	defaultCwdByExtensions.clear();
	try {
		Properties settings;
		settings.load(settingsPathName.empty() == false?settingsPathName:defaultCwd, settingsFileName, FileSystem::getStandardFileSystem());
		{
			auto i = 0;
			string favorite;
			while ((favorite = settings.get("favorite_" + to_string(i++), "")).empty() == false) {
				favorites.push_back(favorite);
			}
		}
		{
			auto i = 0;
			string recent;
			while ((recent = settings.get("recent_" + to_string(i++), "")).empty() == false) {
				recents.push_back(recent);
			}
		}
		{
			auto i = 0;
			string defaultCwdString;
			while ((defaultCwdString = settings.get("default_cwd_" + to_string(i++), "")).empty() == false) {
				auto defaultCwdComponents = StringTools::tokenize(defaultCwdString, ":");
				if (defaultCwdComponents.size() == 2) {
					defaultCwdByExtensions[defaultCwdComponents[0]] = defaultCwdComponents[1];
				}
			}
		}
	} catch (Exception& exception) {
		Console::printLine("FileDialogScreenController::setDefaultCWD(): An error occurred: " + string(exception.what()));
	}

}

void FileDialogScreenController::saveSettings() {
	// TODO: store relative paths
	try {
		Properties settings;
		{
			auto i = 0;
			for (const auto& favorite: favorites) {
				settings.put("favorite_" + to_string(i++), favorite);
			}
		}
		{
			auto i = 0;
			for (const auto& recent: recents) {
				settings.put("recent_" + to_string(i++), recent);
			}
		}
		{
			auto i = 0;
			for (const auto& [extension, defaultCwd]: defaultCwdByExtensions) {
				settings.put("default_cwd_" + to_string(i++), extension + ":" + defaultCwd);
			}
		}
		settings.store(settingsPathName.empty() == false?settingsPathName:defaultCwd, settingsFileName, FileSystem::getStandardFileSystem());
	} catch (Exception& exception) {
		Console::printLine("FileDialogScreenController::setDefaultCWD(): An error occurred: " + string(exception.what()));
	}
}

const string FileDialogScreenController::getFileImageName(const string& fileName) {
	auto fileNameLowerCase = StringTools::toLowerCase(fileName);
	if (StringTools::endsWith(fileNameLowerCase, ".ogg") == true) {
		return "sound";
	} else
	// markdown
	if (StringTools::endsWith(fileNameLowerCase, ".md") == true) {
		return "script";
	} else
	// license
	if (fileNameLowerCase == "license") {
		return "script";
	} else
	// C++/C code
	if (StringTools::endsWith(fileNameLowerCase, ".h") == true) {
		return "script";
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".cpp") == true) {
		return "script";
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".c") == true) {
		return "script";
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".tscript") == true) {
		return "script";
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".ttf") == true) {
		return "font";
	} else
	// images
	if (StringTools::endsWith(fileNameLowerCase, ".icns") == true) {
		return "texture";
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".ico") == true) {
		return "texture";
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".png") == true) {
		return "texture";
	} else
	// videos
	if (StringTools::endsWith(fileNameLowerCase, ".mpg") == true) {
		return "texture";
	} else
	// models
	if (StringTools::endsWith(fileNameLowerCase, ".dae") == true) {
		return "mesh";
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".fbx") == true) {
		return "mesh";
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".glb") == true) {
		return "mesh";
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".gltf") == true) {
		return "mesh";
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".tm") == true) {
		return "mesh";
	} else
	// property files
	if (StringTools::endsWith(fileNameLowerCase, ".properties") == true) {
		return "script";
	} else
	// shader
	if (StringTools::endsWith(fileNameLowerCase, ".cl") == true) {
		return "script";
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".frag") == true) {
		return "script";
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".glsl") == true) {
		return "script";
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".vert") == true) {
		return "script";
	} else
	// tdme empty
	if (StringTools::endsWith(fileNameLowerCase, ".tempty") == true) {
		return "prototype";
	} else
	// tdme trigger
	if (StringTools::endsWith(fileNameLowerCase, ".ttrigger") == true) {
		return "prototype";
	} else
	// tdme envmap
	if (StringTools::endsWith(fileNameLowerCase, ".tenvmap") == true) {
		return "prototype";
	} else
	// tdme model
	if (StringTools::endsWith(fileNameLowerCase, ".tmodel") == true) {
		return "prototype";
	} else
	// tdme scene
	if (StringTools::endsWith(fileNameLowerCase, ".tscene") == true) {
		return "scene";
	} else
	// tdme particle system
	if (StringTools::endsWith(fileNameLowerCase, ".tparticle") == true) {
		return "particle";
	} else
	// tdme decal
	if (StringTools::endsWith(fileNameLowerCase, ".tdecal") == true) {
		return "prototype";
	} else
	// tdme terrain
	if (StringTools::endsWith(fileNameLowerCase, ".tterrain") == true) {
		return "terrain";
	} else
	// tdme script
	if (StringTools::endsWith(fileNameLowerCase, ".tscript") == true) {
		return "script";
	} else
	// xml
	if (StringTools::endsWith(fileNameLowerCase, ".xml") == true) {
		return "gui";
	} else
	// nmake
	if (StringTools::endsWith(fileNameLowerCase, ".nmake") == true) {
		return "script";
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".nmake.main") == true) {
		return "script";
	} else
	// bat
	if (StringTools::endsWith(fileNameLowerCase, ".bat") == true) {
		return "script";
	} else
	// bash
	if (StringTools::endsWith(fileNameLowerCase, ".sh") == true) {
		return "script";
	} else
	if (StringTools::endsWith(fileNameLowerCase, ".bash") == true) {
		return "script";
	} else
	// files without ending
	if (fileName.rfind(".") == string::npos ||
		(fileName.rfind("/") != string::npos &&
		fileName.rfind(".") < fileName.rfind("/"))) {
		return "script";
	}
	return string();
}

void FileDialogScreenController::onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) {
	popUps->getTooltipScreenController()->show(mouseX, mouseY, node->getToolTip());
}

void FileDialogScreenController::onTooltipCloseRequest() {
	popUps->getTooltipScreenController()->close();
}
