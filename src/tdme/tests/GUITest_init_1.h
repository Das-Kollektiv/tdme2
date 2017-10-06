
#pragma once

#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tests/fwd-tdme.h>
#include <tdme/gui/events/GUIActionListener.h>

using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::tests::GUITest;

class tdme::tests::GUITest_init_1
	: public virtual GUIActionListener
{
	friend class GUITest;
	friend class GUITest_init_2;

public:
	void onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node) override;

	// Generated
	GUITest_init_1(GUITest* guiTest);
	GUITest* guiTest;
};
