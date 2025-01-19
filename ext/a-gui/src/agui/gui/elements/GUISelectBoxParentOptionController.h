#pragma once

#include <memory>
#include <string>

#include <agui/agui.h>
#include <agui/gui/elements/GUISelectBoxOptionController.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/events/GUIActionListener.h>
#include <agui/gui/nodes/fwd-agui.h>

using std::string;

using std::unique_ptr;

// namespaces
namespace agui {
namespace gui {
namespace elements {
	using ::agui::gui::events::GUIActionListener;
	using ::agui::gui::nodes::GUIElementNode;
	using ::agui::gui::nodes::GUIParentNode;
	using ::agui::utilities::MutableString;
}
}
}

/**
 * GUI select box parent option controller
 * @author Andreas Drewke
 */
class agui::gui::elements::GUISelectBoxParentOptionController final: public GUISelectBoxOptionController
{
	friend class GUISelectBoxController;
	friend class GUISelectBoxOptionController;
	friend class GUISelectBoxParentOption;

private:
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_EXPANDED;
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_COLLAPSED;

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
	 * @return is expanded
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
