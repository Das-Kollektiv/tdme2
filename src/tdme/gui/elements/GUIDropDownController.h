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
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::utils::MutableString;


struct default_init_tag;

/** 
 * GUI drop down controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::elements::GUIDropDownController final
	: public GUINodeController
{

public:
	typedef GUINodeController super;

private:
	static wstring CONDITION_DISABLED;
	static wstring CONDITION_ENABLED;
	static wstring CONDITION_OPENED;
	static wstring CONDITION_CLOSED;
	vector<GUINode*> childControllerNodes {  };
	vector<GUIDropDownOptionController*> dropDownOptionControllers {  };
	bool isOpen_ {  };
	bool disabled {  };
	GUIParentNode* dropDownNode {  };
	GUIElementNode* arrowNode {  };
	GUIElementNode* textElementNode {  };
	MutableString* value {  };
protected:

	/** 
	 * Constructor
	 * @param node
	 */
	void ctor(GUINode* node);

public:
	bool isDisabled() override;
	void setDisabled(bool disabled) override;
	void initialize() override;
	void dispose() override;
	void postLayout() override;

public: /* protected */

	/** 
	 * @return drop down open state
	 */
	bool isOpen();

	/** 
	 * Unselect all nodes
	 */
	void unselect();

	/** 
	 * Toggle open state
	 */
	void toggleOpenState();

private:

	/** 
	 * Determine drop down option controllers
	 */
	void determineDropDownOptionControllers();

	/** 
	 * Get selected option idx
	 */
	int32_t getSelectedOptionIdx();

	/** 
	 * Select next node
	 */
	void selectNext();

	/** 
	 * Select previous
	 */
	void selectPrevious();

public:
	void handleMouseEvent(GUINode* node, GUIMouseEvent* event) override;
	void handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event) override;
	void tick() override;
	void onFocusGained() override;
	void onFocusLost() override;
	bool hasValue() override;
	MutableString* getValue() override;
	void setValue(MutableString* value) override;

	// Generated

public: /* protected */
	GUIDropDownController(GUINode* node);
protected:
	GUIDropDownController(const ::default_init_tag&);

private:
	void init();
};
