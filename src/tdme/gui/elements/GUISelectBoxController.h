#pragma once

#include <string>
#include <vector>

#include <tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/gui/nodes/GUINodeController.h>

using std::vector;
using std::string;

using tdme::gui::nodes::GUINodeController;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUINode;
using tdme::utils::MutableString;

/** 
 * GUI select box controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::elements::GUISelectBoxController final
	: public GUINodeController
{

private:
	static string CONDITION_DISABLED;
	static string CONDITION_ENABLED;
	vector<GUINode*> childControllerNodes {  };
	vector<GUISelectBoxOptionController*> selectBoxOptionControllers {  };
	bool disabled {  };
	MutableString* value {  };

public:
	bool isDisabled() override;
	void setDisabled(bool disabled) override;
	void initialize() override;
	void dispose() override;
	void postLayout() override;

public: /* protected */

	/** 
	 * Unselect all nodes
	 */
	void unselect();

private:

	/** 
	 * Determine select box option controllers
	 */
	void determineSelectBoxOptionControllers();

	/** 
	 * Get selected option idx
	 */
	int32_t getSelectedOptionIdx();

public: /* protected */

	/** 
	 * Select current option
	 */
	void selectCurrent();

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

public: /* protected */
	GUISelectBoxController(GUINode* node);

private:
	void init();
};
