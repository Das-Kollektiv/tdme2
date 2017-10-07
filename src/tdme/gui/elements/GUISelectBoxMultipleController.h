#pragma once

#include <string>
#include <vector>

#include <fwd-tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/gui/nodes/GUINodeController.h>

using std::vector;
using std::wstring;

using tdme::gui::nodes::GUINodeController;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUINode;
using tdme::utils::MutableString;


struct default_init_tag;

/** 
 * GUI select box multiple controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::elements::GUISelectBoxMultipleController final
	: public GUINodeController
{

public:
	typedef GUINodeController super;

private:
	static wstring CONDITION_DISABLED;
	static wstring CONDITION_ENABLED;
	static constexpr char16_t VALUE_DELIMITER { u'|' };
	vector<GUINode*> childControllerNodes {  };
	vector<GUISelectBoxMultipleOptionController*> selectBoxMultipleOptionControllers {  };
	bool disabled {  };
	MutableString* value {  };
	MutableString* searchValue {  };
protected:

	/** 
	 * Constructor
	 * @param node
	 */
	void ctor(GUINode* node);

public:
	bool isDisabled() override;

	/** 
	 * Set disabled
	 * @param disabled
	 */
	void setDisabled(bool disabled) override;
	void initialize() override;
	void dispose() override;
	void postLayout() override;

public: /* protected */

	/** 
	 * Unselect all nodes
	 */
	void unselect();

	/** 
	 * Unfocus all nodes
	 */
	void unfocus();

private:

	/** 
	 * Determine select box option controllers
	 */
	void determineSelectBoxMultipleOptionControllers();

	/** 
	 * Get focussed option idx
	 */
	int32_t getFocussedOptionIdx();

public: /* protected */

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
	MutableString* getValue() override;
	void setValue(MutableString* value) override;

public: /* protected */
	GUISelectBoxMultipleController(GUINode* node);
protected:
	GUISelectBoxMultipleController(const ::default_init_tag&);


public:
	static void clinit();

private:
	void init();
};
