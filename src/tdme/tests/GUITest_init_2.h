
#pragma once

#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/tests/fwd-tdme.h>
#include <tdme/gui/events/GUIChangeListener.h>

using tdme::gui::events::GUIChangeListener;
using tdme::gui::nodes::GUIElementNode;
using tdme::tests::GUITest;

class tdme::tests::GUITest_init_2
	: public virtual GUIChangeListener
{
	friend class GUITest;
	friend class GUITest_init_1;

public:
	void onValueChanged(GUIElementNode* node) override;
	GUITest_init_2(GUITest* guiTest);

private:
	GUITest* guiTest;

};
