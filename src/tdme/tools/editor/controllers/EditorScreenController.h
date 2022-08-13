#pragma once

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/scene/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/events/GUIContextMenuRequestListener.h>
#include <tdme/gui/events/GUIFocusListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/tools/editor/controllers/fwd-tdme.h>
#include <tdme/tools/editor/controllers/ScreenController.h>
#include <tdme/tools/editor/tabcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::map;
using std::string;
using std::unordered_map;
using std::vector;

using tdme::engine::fileio::textures::Texture;
using tdme::engine::prototype::Prototype;
using tdme::engine::scene::Scene;
using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::events::GUIContextMenuRequestListener;
using tdme::gui::events::GUIFocusListener;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIFrameBufferNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::os::threading::Mutex;
using tdme::os::threading::Thread;
using tdme::tools::editor::controllers::ScreenController;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::TabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::MutableString;

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
		FILETYPE_TEXT
	};

	/**
	 * Editor tab view
	 */
	class EditorTabView {
	public:
		enum TabType { TABTYPE_UNKNOWN, TABTYPE_EMPTYEDITOR, TABTYPE_TRIGGEREDITOR, TABTYPE_ENVMAPEDITOR, TABTYPE_DECALEDITOR, TABTYPE_MODELEDITOR, TABTYPE_TERRAINEDITOR, TABTYPE_PARTICLESYSTEMEDITOR, TABTYPE_SCENEEDITOR, TABTYPE_TEXTURE, TABTYPE_FONT, TABTYPE_UIEDITOR, TABTYPE_SOUND, TABTYPE_VIDEO, TABTYPE_TEXT };

	private:
		string id;
		TabType type { TABTYPE_UNKNOWN };
		TabView* tabView { nullptr };
		GUIFrameBufferNode* frameBufferNode { nullptr };

	public:
		/**
		 * Public default constructor
		 */
		EditorTabView() {}

		/**
		 * Public constructor
		 * @param id id
		 * @param type type
		 * @param tabView tab view
		 * @param frameBufferNode frame buffer node
		 */
		EditorTabView(
			string id,
			TabType type,
			TabView* tabView,
			GUIFrameBufferNode* frameBufferNode
		):
			id(id),
			type(type),
			tabView(tabView),
			frameBufferNode(frameBufferNode)
		{}

		/**
		 * @return id
		 */
		inline const string& getId() {
			return id;
		}

		/**
		 * @return tab type
		 */
		inline TabType getType() {
			return type;
		}

		/**
		 * @return tab view
		 */
		inline TabView* getTabView() {
			return tabView;
		}

		/**
		 * @return frame buffer GUI node
		 */
		inline GUIFrameBufferNode* getFrameBufferNode() {
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
	string fileNameSearchTerm;
	int64_t timeFileNameSearchTerm { -1LL };

	//
	class FileOpenThread: public Thread {
	public:
		/**
		 * Constructor
		 * @param tabId tab id
		 * @param fileType file type
		 * @param absoluteFileName absolute file name
		 */
		FileOpenThread(const string& tabId, FileType fileType, const string& absoluteFileName): Thread("FileOpenThread"), tabId(tabId), fileType(fileType), absoluteFileName(absoluteFileName) {}

		/**
		 * @return tab id
		 */
		inline const string& getTabId() {
			return tabId;
		}

		/**
		 * @return file type
		 */
		inline FileType getFileType() {
			return fileType;
		}

		/**
		 * @return absolute filename
		 */
		inline const string& getAbsoluteFileName() {
			return absoluteFileName;
		}

		/**
		 * @return error message
		 */
		inline const string& getErrorMessage() {
			return errorMessage;
		}

		/**
		 * @return progress
		 */
		inline float getProgress() {
			return progress;
		}

		/**
		 * @return prototype
		 */
		inline Prototype* getPrototype() {
			return prototype;
		}

		/**
		 * @return scene
		 */
		inline Scene* getScene() {
			return scene;
		}

		/**
		 * @return if error occurred during opening files
		 */
		inline bool isError() {
			return error;
		}

		/**
		 * @return if thread has finished
		 */
		inline volatile bool isFinished() {
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

		Prototype* prototype { nullptr };
		Scene* scene { nullptr };
		bool error { false };
		volatile bool finished { false };
	};

	FileOpenThread* fileOpenThread { nullptr };

	struct FileEntity {
		string id;
		string buttonXML;
		Texture* thumbnailTexture { nullptr };
	};

	//
	class ScanFilesThread: public Thread {
	public:
		/**
		 * Constructor
		 * @param pathName path name
		 */
		ScanFilesThread(EditorScreenController* editorScreenController, const string& pathName, const string& searchTerm): Thread("ScanFilesThread"), editorScreenController(editorScreenController), pathName(pathName), searchTerm(searchTerm) {}

		/**
		 * @return path name
		 */
		inline const string& getPathName() {
			return pathName;
		}

		/**
		 * @return error message
		 */
		inline const string& getErrorMessage() {
			return errorMessage;
		}

		/**
		 * @return progress
		 */
		inline float getProgress() {
			return progress;
		}

		/**
		 * @return if error occurred during opening files
		 */
		inline bool isError() {
			return error;
		}

		/**
		 * @return if thread has finished
		 */
		inline volatile bool isFinished() {
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
	vector<FileEntity*> fileEntities;

	string fullScreenTabId;

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
	 * @return file entities
	 */
	inline vector<FileEntity*>& getFileEntities() {
		return fileEntities;
	}

	ScanFilesThread* scanFilesThread { nullptr };
	vector<FileEntity*> pendingFileEntities;

public:

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
	void onValueChanged(GUIElementNode* node) override;
	void onActionPerformed(GUIActionListenerType type, GUIElementNode* node) override;
	void onFocus(GUIElementNode* node) override;
	void onUnfocus(GUIElementNode* node) override;
	void onContextMenuRequested(GUIElementNode* node, int mouseX, int mouseY) override;

	/**
	 * @return project path
	 */
	const string& getProjectPath() {
		return projectPath;
	}

	/**
	 * Open project
	 * @param path path
	 */
	void openProject(const string& path);

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
	void onOpenFileFinish(const string& tabId, FileType fileType, const string& absoluteFileName, Prototype* prototype, Scene* scene);

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
	 * @return outliner selection
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
	 * @return is full screen
	 */
	bool isFullScreen();

	/**
	 * Update full screen menu entry
	 */
	void updateFullScreenMenuEntry();

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
	 * On save current tab
	 */
	void onSaveCurrentTab();

	/**
	 * On save as current tab
	 */
	void onSaveAsCurrentTab();

	/**
	 * On save all tabs
	 */
	void onSaveAllTabs();

	/**
	 * Shows the error pop up
	 * @param caption caption
	 * @param message message
	 */
	void showErrorPopUp(const string& caption, const string& message);

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
	 * @return selected tab id
	 */
	const string getSelectedTabId();

	/**
	 * @return tabs views
	 */
	inline unordered_map<string, EditorTabView>& getTabViews() {
		return tabViews;
	}

	/**
	 * Returns editor tab view by given tab id
	 * @param tabId editor tab id
	 * @return tab
	 */
	inline EditorTabView* getTab(const string& tabId) {
		auto tabViewIt = tabViews.find(tabId);
		if (tabViewIt != tabViews.end()){
			return &tabViewIt->second;
		}
		return nullptr;
	}

	/**
	 * @return selected tab
	 */
	inline EditorTabView* getSelectedTab() {
		return getTab(getSelectedTabId());
	}

	/**
	 * Tick
	 */
	void tick();

	/**
	 * On quit
	 */
	void onQuit();
};
