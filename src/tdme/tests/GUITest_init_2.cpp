#include <tdme/tests/GUITest_init_2.h>

#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/tests/GUITest.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/_Console.h>

using tdme::tests::GUITest_init_2;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINodeController;
using tdme::tests::GUITest;
using tdme::utils::MutableString;
using tdme::utils::_Console;

GUITest_init_2::GUITest_init_2(GUITest *GUITest_this)
	: guiTest(guiTest)
{
}

void GUITest_init_2::onValueChanged(GUIElementNode* node)
{
	_Console::println(node->getName() + L":onValueChanged: " + node->getController()->getValue()->toWString());
}
