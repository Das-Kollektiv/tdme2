#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/utilities/MutableString.h>

using std::string;

using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::GUIParser;
using tdme::utilities::MutableString;

/**
 * GUI styled text node controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::nodes::GUIStyledTextNodeController
	: public GUINodeController
{
	friend class tdme::gui::GUIParser;
	friend class GUIStyledTextNode;
private:
	static constexpr int64_t CURSOR_MODE_DURATION { 500LL };
	int64_t cursorModeStarted { -1LL };
	enum CursorMode { CURSORMODE_HIDE, CURSORMODE_SHOW};
	CursorMode cursorMode { CURSORMODE_SHOW };
	int index { 0 };
	int selectionIndex { -1 };

	/**
	 * @return index
	 */
	inline int getIndex() {
		return index;
	}

	/**
	 * @return selection index
	 */
	inline int getSelectionIndex() {
		return selectionIndex;
	}

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

protected:
	/**
	 * Constructor
	 * @param node node
	 */
	GUIStyledTextNodeController(GUINode* node);

public:
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
};
