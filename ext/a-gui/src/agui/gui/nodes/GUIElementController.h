#pragma once

#include <string>

#include <agui/agui.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/utilities/MutableString.h>

using std::string;

// namespaces
namespace agui {
namespace gui {
namespace nodes {
	using ::agui::gui::events::GUIKeyboardEvent;
	using ::agui::gui::events::GUIMouseEvent;
	using ::agui::utilities::MutableString;
}
}
}

/**
 * GUI element controller
 * @author Andreas Drewke
 */
class agui::gui::nodes::GUIElementController
	: public GUINodeController
{
	friend class GUIElementNode;

private:
	static constexpr int64_t TIME_DOUBLECLICK { 250LL };

	bool disabled;
	bool isActionPerforming;
	bool initialized;
	MutableString value;
	int64_t timeLastClicked { -1LL };

	int mouseLastX { -1 };
	int mouseLastY { -1 };

protected:
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_DISABLED;
	AGUI_STATIC_DLL_IMPEXT static string CONDITION_ENABLED;

	// forbid class copy
	FORBID_CLASS_COPY(GUIElementController)

	/**
	 * Constructor
	 * @param node node
	 */
	GUIElementController(GUINode* node);

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
