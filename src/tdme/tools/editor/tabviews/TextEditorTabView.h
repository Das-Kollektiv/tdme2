#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIStyledTextNodeController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/TextFormatter.h>
#include <tdme/tools/editor/tabcontrollers/TabController.h>
#include <tdme/tools/editor/tabcontrollers/TextEditorTabController.h>
#include <tdme/tools/editor/tabviews/TabView.h>
#include <tdme/tools/editor/views/fwd-tdme.h>

using std::string;

using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUIStyledTextNode;
using tdme::gui::nodes::GUIStyledTextNodeController;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::TextFormatter;
using tdme::tools::editor::tabcontrollers::TabController;
using tdme::tools::editor::tabcontrollers::TextEditorTabController;
using tdme::tools::editor::tabviews::TabView;
using tdme::tools::editor::views::EditorView;

/**
 * Text editor tab view
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::editor::tabviews::TextEditorTabView final
	: public TabView
{
protected:
	Engine* engine { nullptr };

private:
	EditorView* editorView { nullptr };
	string tabId;
	PopUps* popUps { nullptr };
	TextEditorTabController* textEditorTabController { nullptr };
	TabView::OutlinerState outlinerState;
	GUIScreenNode* tabScreenNode { nullptr };
	string extension;
	GUIStyledTextNode* textNode { nullptr };
	GUIStyledTextNodeController::ChangeListener* textNodeChangeListener { nullptr };
	GUIStyledTextNodeController::CodeCompletionListener* textNodeCodeCompletionListener { nullptr };
	const TextFormatter::CodeCompletion* codeCompletion { nullptr };

	struct CodeCompletionSymbol {
		string display;
		string name;
		vector<string> parameters;
		string returnValue;
	};

	/**
	 * Compare CodeCompletionSymbol structs
	 * @return lhs < rhs
	 */
	static bool compareCodeCompletionStruct(const CodeCompletionSymbol& lhs, const CodeCompletionSymbol& rhs) {
		return lhs.display < rhs.display;
	}

public:
	/**
	 * Public constructor
	 * @param editorView editor view
	 * @param tabId tab id
	 * @param screenNode screenNode
	 * @param extension extension
	 */
	TextEditorTabView(EditorView* editorView, const string& tabId, GUIScreenNode* screenNode, const string& extension);

	/**
	 * Destructor
	 */
	~TextEditorTabView();

	/**
	 * @return code completion
	 * TODO: maybe move me into controller
	 */
	const TextFormatter::CodeCompletion* getCodeCompletion() {
		return codeCompletion;
	}

	/**
	 * @return editor view
	 */
	inline EditorView* getEditorView() {
		return editorView;
	}

	/**
	 * @return tab screen node
	 */
	inline GUIScreenNode* getTabScreenNode() {
		return tabScreenNode;
	}

	/**
	 * @return associated tab controller
	 */
	inline TabController* getTabController() override {
		return textEditorTabController;
	}

	/**
	 * @return pop up views
	 */
	inline PopUps* getPopUps() {
		return popUps;
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
	inline bool hasFixedSize() override{ return false; };
	void updateRendering() override;

};
