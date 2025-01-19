#pragma once

#include <string>
#include <memory>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <tdme/tools/editor/misc/Markdown.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/tabcontrollers/fwd-tdme.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabcontrollers/MarkdownTabController.h>
#include <tdme/tools/editor/tabviews/fwd-tdme.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/fwd-tdme.h>

using std::string;
using std::unique_ptr;
using std::vector;

using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using agui::gui::nodes::GUIScreenNode;
using tdme::tools::editor::misc::Markdown;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabcontrollers::MarkdownTabController;
using tdme::tools::editor::tabviews::TabView;
using tdme::tools::editor::views::EditorView;

/**
 * Markdown tab view
 * @author Andreas Drewke
 */
class tdme::tools::editor::tabviews::MarkdownTabView final
	: public TabView
{
protected:
	unique_ptr<Engine> engine;

private:
	EditorView* editorView { nullptr };
	string tabId;
	GUIScreenNode* screenNode { nullptr };
	PopUps* popUps { nullptr };
	unique_ptr<MarkdownTabController> markdownTabController;
	TabView::OutlinerState outlinerState;

	vector<Markdown::TOCEntry> toc;

public:
	// forbid class copy
	FORBID_CLASS_COPY(MarkdownTabView)

	/**
	 * Public constructor
	 * @param editorView editor view
	 * @param tabId tab id
	 * @param screenNode screenNode
	 * @param toc table of content
	 */
	MarkdownTabView(EditorView* editorView, const string& tabId, GUIScreenNode* screenNode, const vector<Markdown::TOCEntry>& toc);

	/**
	 * Destructor
	 */
	~MarkdownTabView();

	/**
	 * @returns editor view
	 */
	inline EditorView* getEditorView() {
		return editorView;
	}

	/**
	 * @returns associated tab controller
	 */
	inline TabController* getTabController() override {
		return markdownTabController.get();
	}

	/**
	 * @returns markdown screen node
	 */
	inline GUIScreenNode* getScreenNode() {
		return screenNode;
	}

	/**
	 * @returns pop up views
	 */
	inline PopUps* getPopUps() {
		return popUps;
	}

	/**
	 * @returns table of content
	 */
	inline const vector<Markdown::TOCEntry>& getTableOfContent() {
		return toc;
	}

	// overridden methods
	void handleInputEvents() override;
	void display() override;
	inline const string& getTabId() override {
		return tabId;
	}
	void initialize() override;
	void dispose() override;
	Engine* getEngine() override;
	void activate() override;
	void deactivate() override;
	void reloadOutliner() override;
	void updateRendering() override;
	inline bool hasFixedSize() override{ return false; };

};
