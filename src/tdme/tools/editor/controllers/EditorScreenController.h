#pragma once

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/events/GUIContextMenuRequestListener.h>
#include <tdme/gui/events/GUIFocusListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
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

using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::engine::fileio::textures::Texture;
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
using tdme::tools::editor::controllers::ScreenController;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabviews::TabView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::MutableString;

/**
 * Editor screen controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::editor::controllers::EditorScreenController final
	: public ScreenController
	, public GUIActionListener
	, public GUIChangeListener
	, public GUIFocusListener
	, public GUIContextMenuRequestListener
{
public:
	/**
	 * Editor tab view
	 */
	class EditorTabView {
	public:
		enum TabType { TABTYPE_UNKNOWN, TABTYPE_EMPTYEDITOR, TABTYPE_MODELEDITOR, TABTYPE_TERRAINEDITOR, TABTYPE_PARTICLESYSTEMEDITOR, TABTYPE_SCENEEDITOR, TABTYPE_TEXTURE, TABTYPE_FONT, TABTYPE_UIEDITOR, TABTYPE_SOUND, TABTYPE_TEXT };

	private:
		string id;
		TabType type { TABTYPE_UNKNOWN };
		TabView* tabView { nullptr };
		TabController* tabController { nullptr };
		Engine* engine { nullptr };
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
		 * @param tabController tab controller
		 * @param engine engine
		 * @param frameBufferNode frame buffer node
		 */
		EditorTabView(
			string id,
			TabType type,
			TabView* tabView,
			TabController* tabController,
			Engine* engine,
			GUIFrameBufferNode* frameBufferNode
		):
			id(id),
			type(type),
			tabView(tabView),
			tabController(tabController),
			engine(engine),
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
		 * @return tab controller
		 */
		inline TabController* getTabController() {
			return tabController;
		}

		/**
		 * @return engine
		 */
		inline Engine* getEngine() {
			return engine;
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
	unordered_map<string, EditorTabView> tabViews;
	string selectedTabId;
	unordered_map<string, Texture*> fileNameTextureMapping;
	map<string, string> fileNameButtonXMLMapping;
	int thumbnailIdx { 0 };
	string fileNameSearchTerm;
	int64_t timeFileNameSearchTerm { -1LL };

public:

	/**
	 * Public constructor
	 * @param view view
	 */
	EditorScreenController(EditorView* view);

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
	 * @param relativeProjectPath relative project path
	 * @param xml xml
	 */
	void scanProjectPathFiles(const string& relativeProjectPath);

	/**
	 * List project path files
	 * @param xml xml
	 * @param searchTerm search term
	 */
	void listProjectPathFiles(string& xml, const string& searchTerm = string());

	/**
	 * Update project path thumbnails
	 */
	void updateProjectPathThumbnails();

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
	 * @return selected tab
	 */
	inline EditorTabView* getSelectedTab() {
		auto selectedTabId = getSelectedTabId();
		auto tabViewIt = tabViews.find(selectedTabId);
		if (tabViewIt != tabViews.end()){
			return &tabViewIt->second;
		}
		return nullptr;
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
