#pragma once

#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/events/GUIContextMenuRequestListener.h>
#include <tdme/gui/events/GUIDragRequestListener.h>
#include <tdme/gui/events/GUIFocusListener.h>
#include <tdme/gui/events/GUITooltipRequestListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUINode_Padding.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/tools/editor/controllers/fwd-tdme.h>
#include <tdme/tools/editor/controllers/ScreenController.h>
#include <tdme/tools/editor/tabcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/fwd-tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/StringTools.h>

using std::map;
using std::string;
using std::unique_ptr;
using std::unordered_map;
using std::vector;

using tdme::engine::Texture;
using tdme::engine::prototype::Prototype;
using tdme::engine::scene::Scene;
using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::events::GUIContextMenuRequestListener;
using tdme::gui::events::GUIDragRequestListener;
using tdme::gui::events::GUIFocusListener;
using tdme::gui::events::GUITooltipRequestListener;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIImageNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINode_Padding;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUIStyledTextNode;
using tdme::gui::nodes::GUITextNode;
using tdme::os::threading::Mutex;
using tdme::os::threading::Thread;
using tdme::tools::editor::controllers::ScreenController;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::TabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::StringTools;

/**
 * Editor screen controller
 * @author Andreas Drewke
 */
class tdme::tools::editor::controllers::EditorScreenController final
	: public ScreenController
	, public GUIActionListener
	, public GUIChangeListener
	, public GUIFocusListener
	, public GUIContextMenuRequestListener
	, public GUITooltipRequestListener
	, public GUIDragRequestListener
{
public:
	enum FileType {
		FILETYPE_UNKNOWN,
		FILETYPE_MODEL,
		FILETYPE_EMPTYPROTOTYPE,
		FILETYPE_TRIGGERPROTOTYPE,
		FILETYPE_ENVMAPPROTOTYPE,
		FILETYPE_DECALPROTOTYPE,
		FILETYPE_MODELPROTOTYPE,
		FILETYPE_TERRAINPROTOTYPE,
		FILETYPE_PARTICLESYSTEMPROTOTYPE,
		FILETYPE_SCENE,
		FILETYPE_SCREEN_TEXT,
		FILETYPE_SOUND,
		FILETYPE_TEXTURE,
		FILETYPE_VIDEO,
		FILETYPE_FONT,
		FILETYPE_TEXT,
		FILETYPE_MARKDOWN
	};

	/**
	 * Editor tab view
	 */
	class EditorTabView {
	public:
		enum TabType { TABTYPE_UNKNOWN, TABTYPE_EMPTYEDITOR, TABTYPE_TRIGGEREDITOR, TABTYPE_ENVMAPEDITOR, TABTYPE_DECALEDITOR, TABTYPE_MODELEDITOR, TABTYPE_TERRAINEDITOR, TABTYPE_PARTICLESYSTEMEDITOR, TABTYPE_SCENEEDITOR, TABTYPE_TEXTURE, TABTYPE_FONT, TABTYPE_UIEDITOR, TABTYPE_SOUND, TABTYPE_VIDEO, TABTYPE_TEXT, TABTYPE_MARKDOWN };

	private:
		string id;
		string name;
		TabType type { TABTYPE_UNKNOWN };
		unique_ptr<TabView> tabView;
		GUIImageNode* frameBufferNode { nullptr };

	public:
		/**
		 * Public default constructor
		 */
		EditorTabView() {}

		/**
		 * Public constructor
		 * @param id id
		 * @param name name
		 * @param type type
		 * @param tabView tab view
		 * @param frameBufferNode frame buffer node
		 */
		EditorTabView(
			const string& id,
			const string& name,
			TabType type,
			TabView* tabView,
			GUIImageNode* frameBufferNode
		):
			id(id),
			name(name),
			type(type),
			tabView(unique_ptr<TabView>(tabView)),
			frameBufferNode(frameBufferNode)
		{}

		/**
		 * @returns id
		 */
		inline const string& getId() {
			return id;
		}

		/**
		 * @returns id
		 */
		inline const string& getName() {
			return name;
		}

		/**
		 * @returns tab type
		 */
		inline TabType getType() {
			return type;
		}

		/**
		 * @returns tab view
		 */
		inline TabView* getTabView() {
			return tabView.get();
		}

		/**
		 * @returns frame buffer GUI node
		 */
		inline GUIImageNode* getFrameBufferNode() {
			return frameBufferNode;
		}

	};

private:
	EditorView* view { nullptr };
	GUIScreenNode* screenNode { nullptr };
	GUIParentNode* projectPathsScrollArea { nullptr };
	GUIParentNode* projectPathFilesScrollArea { nullptr };
	GUIParentNode* tabs { nullptr };
	GUIParentNode* tabsHeader { nullptr };
	GUIParentNode* tabsContent { nullptr };
	GUIElementNode* outliner { nullptr };
	GUIParentNode* outlinerScrollarea { nullptr };
	GUIParentNode* detailsScrollarea { nullptr };
	GUIElementNode* outlinerAddDropDown { nullptr };
	string projectPath;
	string relativeProjectPath;
	unordered_map<string, EditorTabView> tabViews;
	vector<EditorTabView*> tabViewVector;
	string fileNameSearchTerm;
	int64_t timeFileNameSearchTerm { -1LL };
	string browseToFileName;

	GUIStyledTextNode* logStyledTextNode { nullptr };
	GUIParentNode* logScrollarea { nullptr };
	vector<string> logMessages;
	bool logUpdateRequired { false };

	//
	class FileOpenThread: public Thread {
	public:
		// forbid class copy
		FORBID_CLASS_COPY(FileOpenThread)

		/**
		 * Constructor
		 * @param tabId tab id
		 * @param fileType file type
		 * @param absoluteFileName absolute file name
		 */
		FileOpenThread(const string& tabId, FileType fileType, const string& absoluteFileName): Thread("FileOpenThread"), tabId(tabId), fileType(fileType), absoluteFileName(absoluteFileName) {}

		/**
		 * @returns tab id
		 */
		inline const string& getTabId() {
			return tabId;
		}

		/**
		 * @returns file type
		 */
		inline FileType getFileType() {
			return fileType;
		}

		/**
		 * @returns absolute filename
		 */
		inline const string& getAbsoluteFileName() {
			return absoluteFileName;
		}

		/**
		 * @returns error message
		 */
		inline const string& getErrorMessage() {
			return errorMessage;
		}

		/**
		 * @returns progress
		 */
		inline float getProgress() {
			return progress;
		}

		/**
		 * @returns prototype
		 */
		inline unique_ptr<Prototype>& getPrototype() {
			return prototype;
		}

		/**
		 * @returns scene
		 */
		inline unique_ptr<Scene>& getScene() {
			return scene;
		}

		/**
		 * @returns if error occurred during opening files
		 */
		inline bool isError() {
			return error;
		}

		/**
		 * @returns if thread has finished
		 */
		inline bool isFinished() {
			return finished;
		}

		/**
		 * Run
		 */
		virtual void run();
	private:
		FileType fileType;
		string tabId;
		string absoluteFileName;
		string errorMessage;
		float progress { 0.0f };

		unique_ptr<Prototype> prototype;
		unique_ptr<Scene> scene;
		bool error { false };
		volatile bool finished { false };
	};

	unique_ptr<FileOpenThread> fileOpenThread;

	struct FileEntity {
		string id;
		string buttonXML;
		Texture* thumbnailTexture { nullptr };
		bool scrollTo { false };
	};

	//
	class ScanFilesThread: public Thread {
	public:
		// forbid class copy
		FORBID_CLASS_COPY(ScanFilesThread)

		/**
		 * Constructor
		 * @param pathName path name
		 */
		ScanFilesThread(EditorScreenController* editorScreenController, const string& pathName, const string& searchTerm): Thread("ScanFilesThread"), editorScreenController(editorScreenController), pathName(pathName), searchTerm(searchTerm) {}

		/**
		 * @returns path name
		 */
		inline const string& getPathName() {
			return pathName;
		}

		/**
		 * @returns error message
		 */
		inline const string& getErrorMessage() {
			return errorMessage;
		}

		/**
		 * @returns progress
		 */
		inline float getProgress() {
			return progress;
		}

		/**
		 * @returns if error occurred during opening files
		 */
		inline bool isError() {
			return error;
		}

		/**
		 * @returns if thread has finished
		 */
		inline bool isFinished() {
			return finished;
		}

		/**
		 * Run
		 */
		virtual void run();

	private:
		EditorScreenController* editorScreenController { nullptr };
		string pathName;
		string searchTerm;
		string errorMessage;
		float progress { 0.0f };

		bool error { false };
		volatile bool finished { false };
	};

	Mutex fileEntitiesMutex;
	vector<unique_ptr<FileEntity>> fileEntities;

	string fullScreenTabId;
	GUINode_Padding fullScreenTabPadding;

	/**
	 * Lock file entities mutex
	 */
	inline void lockFileEntities() {
		fileEntitiesMutex.lock();
	}

	/**
	 * Unlock file entities mutex
	 */
	inline void unlockFileEntities() {
		fileEntitiesMutex.unlock();
	}

	/**
	 * @returns file entities
	 */
	inline vector<unique_ptr<FileEntity>>& getFileEntities() {
		return fileEntities;
	}

	unique_ptr<ScanFilesThread> scanFilesThread;
	vector<unique_ptr<FileEntity>> pendingFileEntities;

public:
	// forbid class copy
	FORBID_CLASS_COPY(EditorScreenController)

	/**
	 * Public constructor
	 * @param view view
	 */
	EditorScreenController(EditorView* view);

	/**
	 * Public destructor
	 */
	~EditorScreenController();

	// overridden methods
	GUIScreenNode* getScreenNode() override;
	void initialize() override;
	void dispose() override;

	/**
	 * Set screen caption
	 * @param text text
	 */
	void setScreenCaption(const string& text);

	// overridden methods
	void onChange(GUIElementNode* node) override;
	void onAction(GUIActionListenerType type, GUIElementNode* node) override;
	void onFocus(GUIElementNode* node) override;
	void onUnfocus(GUIElementNode* node) override;
	void onContextMenuRequest(GUIElementNode* node, int mouseX, int mouseY) override;
	void onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) override;
	void onTooltipCloseRequest() override;
	void onDragRequest(GUIElementNode* node, int mouseX, int mouseY) override;

	/**
	 * @returns project path
	 */
	const string& getProjectPath() {
		return projectPath;
	}

	/**
	 * Open project
	 * @param pathName path name
	 */
	void openProject(const string& pathName);

	/**
	 * On open project
	 */
	void onOpenProject();

	/**
	 * Scan project paths
	 */
	void scanProjectPaths();

	/**
	 * Scan project paths
	 * @param path path
	 * @param xml xml
	 */
	void scanProjectPaths(const string& path, string& xml);

	/**
	 * Reload files
	 */
	void reload();

	/**
	 * Browse to file name
	 * @param fileName file name
	 */
	void browseTo(const string& fileName);

	/**
	 * Close tab
	 * @param tabId tab id
	 */
	void closeTab(const string& tabId);

	/**
	 * Close tabs
	 */
	void closeTabs();

	/**
	 * Close project
	 */
	void closeProject();

	/**
	 * Clear project path files
	 */
	void clearProjectPathFiles();

	/**
	 * Scan project path files
	 */
	void scanProjectPathFiles();

	/**
	 * Start scan files
	 */
	void startScanFiles();

	/**
	 * Stop scan files
	 */
	void stopScanFiles();

	/**
	 * Reset scan files
	 */
	void resetScanFiles();

	/**
	 * Add project path files pending file entities
	 */
	void addPendingFileEntities();

	/**
	 * Set relative project path
	 * @param relativeProjectPath relative project path
	 */
	void setRelativeProjectPath(const string& relativeProjectPath);

	/**
	 * On add file
	 * @param type type
	 */
	void onAddFile(const string& type);

	/**
	 * On add file
	 * @param pathName path name
	 * @param fileName file name
	 * @param type type
	 */
	void addFile(const string& pathName, const string& fileName, const string& type);

	/**
	 * On open file
	 * @param absoluteProjectFileName absolute project file name
	 */
	inline void onOpenFile(const string& absoluteFileName) {
		openFile(absoluteFileName);
	}

	/**
	 * Open file
	 * @param absoluteProjectFileName absolute project file name
	 */
	void openFile(const string& absoluteFileName);

	/**
	 * On open file finish
	 * @param tabId tab id
	 * @param fileType file type
	 * @param absoluteFileName absolute file name
	 * @param prototype prototype
	 * @param scene scene
	 */
	void onOpenFileFinish(const string& tabId, FileType fileType, const string& absoluteFileName, unique_ptr<Prototype> prototype, unique_ptr<Scene> scene);

	/**
	 * Store outliner state
	 * @param outlinerState outliner state
	 */
	void storeOutlinerState(TabView::OutlinerState& outlinerState);

	/**
	 * Restore outliner state
	 * @param outlinerState outliner state
	 */
	void restoreOutlinerState(const TabView::OutlinerState& outlinerState);

	/**
	 * @returns outliner selection
	 */
	const string getOutlinerSelection();

	/**
	 * Set outliner selection
	 * @param newSelectionValue new selection value
	 */
	void setOutlinerSelection(const string& newSelectionValue);

	/**
	 * Set outliner content
	 * @param xml xml
	 */
	void setOutlinerContent(const string& xml);

	/**
	 * Set outliner add content
	 * @param xml xml
	 */
	void setOutlinerAddDropDownContent(const string& xml);

	/**
	 * Set details content
	 * @param xml xml
	 */
	void setDetailsContent(const string& xml);

	/**
	 * @returns is full screen
	 */
	bool isFullScreen();

	/**
	 * Update full screen menu entry
	 */
	void updateFullScreenMenuEntry();

	/**
	 * Update tabs menu entries
	 */
	void updateTabsMenuEntries();

	/**
	 * Set fullscreen
	 * @param fullScreen full screen
	 */
	void setFullScreen(bool fullScreen);

	/**
	 * Enable scene screen menu entry
	 */
	void enableSceneMenuEntry();

	/**
	 * Disable scene screen menu entry
	 */
	void disableSceneMenuEntry();

	/**
	 * Show the information pop up / modal
	 * @param caption caption
	 * @param message message
	 */
	void showInfoPopUp(const string& caption, const string& message);

	/**
	 * Get engine viewport constraints
	 * @param viewPortNode view port node
	 * @param left left
	 * @param top top
	 * @param width width
	 * @param height height
	 */
	void getViewPort(GUINode* viewPortNode, int& left, int& top, int& width, int& height);

	/**
	 * @returns selected tab id
	 */
	const string getSelectedTabId();

	/**
	 * Returns editor tabs
	 * @returns tabs
	 */
	inline vector<EditorTabView*>& getTabs() {
		return tabViewVector;
	}

	/**
	 * Returns editor tab view by given tab id
	 * @param tabId editor tab id
	 * @returns tab
	 */
	inline EditorTabView* getTab(const string& tabId) {
		auto tabViewIt = tabViews.find(tabId);
		if (tabViewIt != tabViews.end()){
			return &tabViewIt->second;
		}
		return nullptr;
	}

	/**
	 * @returns selected tab
	 */
	inline EditorTabView* getSelectedTab() {
		return getTab(getSelectedTabId());
	}

	/**
	 * Get tab at given index
	 * @returns tab at given index
	 */
	inline EditorTabView* getTabAt(int idx) {
		if (idx < 0 || idx >= tabViewVector.size()) return nullptr;
		return tabViewVector[idx];
	}

	/**
	 * Select tab with given id
	 * @param tabId tab id
	 */
	bool selectTab(const string& tabId);

	/**
	 * @returns tab count
	 */
	inline int getTabCount() {
		return tabViewVector.size();
	}

	/**
	 * @returns selected tab index
	 */
	int getSelectedTabIdx();

	/**
	 * Select tab at given index
	 * @param idx index
	 */
	bool selectTabAt(int idx);

	/**
	 * Tick
	 */
	void tick();

	/**
	 * On quit
	 */
	void onQuit();

	/**
	 * Is drop on node
	 * @param dropX drop x
	 * @param dropY drop y
	 * @param nodeId node id
	 * @returns drop is on node or not
	 */
	bool isDropOnNode(int dropX, int dropY, const string& nodeId);

	/**
	 * Returns relative path within project path
	 * @param absoluteFileName absolute file name
	 * @returns relative path within project path
	 */
	inline const string getRelativePath(const string& absoluteFileName) {
		auto absoluteFileNameUnix = StringTools::replace(absoluteFileName, "\\", "/");
		auto projectPathUnix = StringTools::replace(projectPath, "\\", "/");
		if (StringTools::startsWith(absoluteFileNameUnix, projectPathUnix + "/") == false) return absoluteFileNameUnix;
		return StringTools::substring(absoluteFileNameUnix, projectPathUnix.size() + 1);
	}

	/**
	 * On drop
	 * @param paths paths of items that were dropped
	 */
	void onDrop(const vector<string>& paths);

	/**
	 * Update log
	 */
	void updateLog();
};
