#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/engine/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tools/editor/controllers/fwd-tdme.h>
#include <tdme/tools/editor/controllers/fwd-tdme.h>
#include <tdme/tools/editor/controllers/ScreenController.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <tdme/tools/editor/views/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;
using std::unordered_map;
using std::vector;

using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIFrameBufferNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::tools::editor::controllers::ScreenController;
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
{
public:
	/**
	 * Editor tab view
	 */
	class EditorTabView {
	private:
		string id;
		TabView* tabView { nullptr };
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
		 * @param tabView tab view
		 * @param engine engine
		 * @param frameBufferNode frame buffer node
		 */
		EditorTabView(
			string id,
			TabView* tabView,
			Engine* engine,
			GUIFrameBufferNode* frameBufferNode
		):
			id(id),
			tabView(tabView),
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
		 * @return tab view
		 */
		inline TabView* getTabView() {
			return tabView;
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
	GUINode* viewPort { nullptr };
	string projectPath;
	unordered_map<string, EditorTabView> tabViews;
	string selectedTabId;

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
	 * Scan project path files
	 * @param relativeProjectPath relative project path
	 * @param xml xml
	 */
	void scanProjectPathFiles(const string& relativeProjectPath, string& xml);

	/**
	 * On open file
	 * @param relativeProjectFileName relative project file name
	 */
	void onOpenFile(const string& relativeProjectFileName);

	/**
	 * Shows the error pop up
	 * @param caption caption
	 * @param message message
	 */
	void showErrorPopUp(const string& caption, const string& message);

	/**
	 * Get engine viewport constraints
	 * @param left left
	 * @param top top
	 * @param width width
	 * @param height height
	 */
	void getViewPort(int& left, int& top, int& width, int& height);

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
	 * On quit
	 */
	void onQuit();
};
