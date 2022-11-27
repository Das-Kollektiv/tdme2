#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/utilities/MutableString.h>

using std::string;
using std::vector;

using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::GUIParser;
using tdme::utilities::MutableString;

/**
 * GUI styled text node controller
 * @author Andreas Drewke
 */
class tdme::gui::nodes::GUIStyledTextNodeController
	: public GUINodeController
{
	friend class tdme::gui::GUIParser;
	friend class GUIStyledTextNode;

public:

	/**
	 * Change listener interface
	 * @author Andreas Drewke
	 */
	struct ChangeListener {

		/**
		 * Destructor
		 */
		virtual ~ChangeListener() {}

		/**
		 * On remove text
		 * @param idx index
		 * @param count count
		 */
		virtual void onRemoveText(int idx, int count) = 0;

		/**
		 * On remove text
		 * @param idx index
		 * @param count count
		 */
		virtual void onInsertText(int idx, int count) = 0;
	};

	/**
	 * Code completion listener
	 * @author Andreas Drewke
	 */
	struct CodeCompletionListener {

		/**
		 * Destructor
		 */
		virtual ~CodeCompletionListener() {}

		/**
		 * On code completion requested
		 * @param idx index
		 */
		virtual void onCodeCompletion(int idx) = 0;

	};

private:
	static constexpr int64_t TIME_DOUBLECLICK { 250LL };
	static constexpr int64_t CURSOR_MODE_DURATION { 500LL };
	int64_t cursorModeStarted { -1LL };
	enum CursorMode { CURSORMODE_HIDE, CURSORMODE_SHOW};
	CursorMode cursorMode { CURSORMODE_SHOW };
	int index { 0 };
	int selectionIndex { -1 };
	int lineIndex { 0 };
	vector<ChangeListener*> changeListeners;
	vector<CodeCompletionListener*> codeCompletionListeners;
	enum ScrollMode { SCROLLMODE_NONE, SCROLLMODE_UP, SCROLLMODE_DOWN };
	ScrollMode scrollMode { SCROLLMODE_NONE };
	bool dragging { false };
	bool input { false };
	int64_t timeLastClick { -1LL };
	bool doubleClick { false };


	/**
	 * @return must show cursor
	 */
	inline bool isShowCursor() {
		return true;
	}

	/**
	 * Reset cursor mode
	 */
	void resetCursorMode();

	/**
	 * @return cursor mode
	 */
	CursorMode getCursorMode();

	/**
	 * Forward remove text
	 * @param idx index
	 * @param count count
	 */
	void forwardRemoveText(int idx, int count);

	/**
	 * Forward insert text
	 * @param idx index
	 * @param count count
	 */
	void forwardInsertText(int idx, int count);

	/**
	 * Forward code completion
	 * @param idx index
	 */
	void forwardCodeCompletion(int idx);

protected:
	/**
	 * Constructor
	 * @param node node
	 */
	GUIStyledTextNodeController(GUINode* node);

public:
	/**
	 * @return index
	 */
	inline int getIndex() {
		return index;
	}

	/**
	 * Set index
	 * @param index index
	 */
	inline void setIndex(int index) {
		this->index = index;
	}

	/**
	 * @return selection index
	 */
	inline int getSelectionIndex() {
		return selectionIndex;
	}

	/**
	 * Set selection index
	 * @param selectionIndex selection index
	 */
	inline void setSelectionIndex(int selectionIndex) {
		this->selectionIndex = selectionIndex;
	}

	// overridden methods
	bool isDisabled() override;
	void setDisabled(bool disabled) override;
	void initialize() override;
	void dispose() override;
	void postLayout() override;
	void handleMouseEvent(GUINode* node, GUIMouseEvent* event) override;
	void handleKeyboardEvent(GUIKeyboardEvent* event) override;
	void tick() override;
	void onFocusGained() override;
	void onFocusLost() override;
	bool hasValue() override;
	const MutableString& getValue() override;
	void setValue(const MutableString& value) override;
	void onSubTreeChange() override;

	/**
	 * Add change listener
	 * @param listener listener
	 */
	void addChangeListener(ChangeListener* listener);

	/**
	 * Remove change listener
	 * @param listener listener
	 */
	void removeChangeListener(ChangeListener* listener);

	/**
	 * Add code completion listener
	 * @param listener listener
	 */
	void addCodeCompletionListener(CodeCompletionListener* listener);

	/**
	 * Remove code completion listener
	 * @param listener listener
	 */
	void removeCodeCompletionListener(CodeCompletionListener* listener);

};
