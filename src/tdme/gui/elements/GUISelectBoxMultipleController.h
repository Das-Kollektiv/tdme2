#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/MutableString.h>
#include <tdme/gui/nodes/GUINodeController.h>

using std::vector;
using std::string;

using tdme::gui::nodes::GUINodeController;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUINode;
using tdme::utils::MutableString;

/** 
 * GUI select box multiple controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::elements::GUISelectBoxMultipleController final
	: public GUINodeController
{
	friend class GUISelectBoxMultiple;
	friend class GUISelectBoxMultipleOptionController;

private:
	static string CONDITION_DISABLED;
	static string CONDITION_ENABLED;
	static constexpr char VALUE_DELIMITER { L'|' };
	vector<GUINode*> childControllerNodes {  };
	vector<GUISelectBoxMultipleOptionController*> selectBoxMultipleOptionControllers {  };
	bool disabled {  };
	MutableString value {  };

public:
	bool isDisabled() override;

	/** 
	 * Set disabled
	 * @param disabled disabled
	 */
	void setDisabled(bool disabled) override;
	void initialize() override;
	void dispose() override;
	void postLayout() override;

private:
	/** 
	 * Unselect all nodes
	 */
	void unselect();

	/** 
	 * Unfocus all nodes
	 */
	void unfocus();

	/** 
	 * Determine select box option controllers
	 */
	void determineSelectBoxMultipleOptionControllers();

	/** 
	 * Get focussed option idx
	 */
	int32_t getFocussedOptionIdx();

	/** 
	 * Select current options
	 */
	void selectCurrent();

	/** 
	 * Focus next node
	 */
	void focusNext();

	/** 
	 * Focus previous
	 */
	void focusPrevious();

	/** 
	 * Toggle selected node
	 */
	void toggle();

public:
	void handleMouseEvent(GUINode* node, GUIMouseEvent* event) override;
	void handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event) override;
	void tick() override;
	void onFocusGained() override;
	void onFocusLost() override;
	bool hasValue() override;
	const MutableString& getValue() override;
	void setValue(const MutableString& value) override;

private:
	/**
	 * Private constructor
	 * @param node node
	 */
	GUISelectBoxMultipleController(GUINode* node);

	/**
	 * Init
	 */
	void init();
};
