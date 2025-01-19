#pragma once

#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/elements/GUISelectBoxOptionController.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/nodes/fwd-tdme.h>

using std::string;

using std::unique_ptr;

using tdme::gui::events::GUIActionListener;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIParentNode;
using tdme::utilities::MutableString;

/**
 * GUI select box parent option controller
 * @author Andreas Drewke
 */
class tdme::gui::elements::GUISelectBoxParentOptionController final: public GUISelectBoxOptionController
{
	friend class GUISelectBoxController;
	friend class GUISelectBoxOptionController;
	friend class GUISelectBoxParentOption;

private:
	STATIC_DLL_IMPEXT static string CONDITION_EXPANDED;
	STATIC_DLL_IMPEXT static string CONDITION_COLLAPSED;

	GUIElementNode* arrowNode { nullptr };
	bool expanded;
	unique_ptr<GUIActionListener> arrowNodeActionListener;

	// forbid class copy
	FORBID_CLASS_COPY(GUISelectBoxParentOptionController)

	/**
	 * Private constructor
	 * @param node node
	 */
	GUISelectBoxParentOptionController(GUINode* node);

	/**
	 * @returns is expanded
	 */
	bool isExpanded();

	/**
	 * Toggle expand state
	 */
	void toggleExpandState();

public:
	// overridden methods
	void initialize() override;
	void dispose() override;
};
