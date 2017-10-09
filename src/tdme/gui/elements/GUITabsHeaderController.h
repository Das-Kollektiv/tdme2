#pragma once

#include <vector>

#include <tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/gui/nodes/GUINodeController.h>

using std::vector;

using tdme::gui::nodes::GUINodeController;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUINode;
using tdme::utils::MutableString;

/** 
 * GUI tabs header controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::elements::GUITabsHeaderController final
	: public GUINodeController
{

private:
	GUINode* tabsNode {  };
	vector<GUINode*> childControllerNodes {  };
	vector<GUITabController*> tabControllers {  };
	bool hasFocus_ {  };

public:
	bool isDisabled() override;
	void setDisabled(bool disabled) override;
	void initialize() override;
	void dispose() override;
	void postLayout() override;

public: /* protected */

	/** 
	 * @return has focus
	 */
	bool hasFocus();

	/** 
	 * Unselect all nodes
	 */
	void unselect();

private:

	/** 
	 * Determine select box option controllers
	 */
	void determineTabControllers();

	/** 
	 * Get selected tab idx
	 */
	int32_t getSelectedTabIdx();

	/** 
	 * Select next node
	 */
	void selectNext();

	/** 
	 * Select previous
	 */
	void selectPrevious();

	/** 
	 * Select current
	 */
	void selectCurrent();

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
	GUITabsHeaderController(GUINode* node);
};
