#pragma once

#include <memory>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIElementController.h>
#include <tdme/utilities/MutableString.h>

using std::make_unique;
using std::string;
using std::unique_ptr;
using std::vector;

using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementController;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::utilities::MutableString;

/**
 * GUI selector horizontal controller
 * @author Andreas Drewke
 */
class tdme::gui::elements::GUISelectorHController final
	: public GUIElementController
{
	friend class GUISelectorH;
	friend class GUISelectorHOptionController;

private:
	STATIC_DLL_IMPEXT static string CONDITION_DISABLED;
	STATIC_DLL_IMPEXT static string CONDITION_ENABLED;
	vector<GUISelectorHOptionController*> selectorHOptionControllers;
	bool disabled;
	MutableString value;
	string search;
	int selectedHOptionControllerIdx { -1 };
	unique_ptr<GUIActionListener> actionListener;
	GUIParentNode* innerNode { nullptr };

private:
	// forbid class copy
	FORBID_CLASS_COPY(GUISelectorHController)

	/**
	 * Private constructor
	 * @param node node
	 */
	GUISelectorHController(GUINode* node);

	/**
	 * Unselect
	 */
	void unselect();

	/**
	 * Select by index
	 * @param idx index
	 */
	void select(int idx);

	/**
	 * Select by option element node
	 * @param selectedSelectorHOptionElementNode selected selector horizontal option element node
	 */
	void select(GUIElementNode* selectedSelectorHOptionElementNode);

	/**
	 * Determine drop down option controllers
	 */
	void determineSelectorHOptionControllers();

	/**
	 * Select next node
	 */
	void selectNext();

	/**
	 * Select previous
	 */
	void selectPrevious();

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
