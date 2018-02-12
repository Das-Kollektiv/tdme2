#include <tdme/tests/GUITest_init_2.h>

#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/tests/GUITest.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/Console.h>

using tdme::tests::GUITest_init_2;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINodeController;
using tdme::tests::GUITest;
using tdme::utils::MutableString;
using tdme::utils::Console;

GUITest_init_2::GUITest_init_2(GUITest* guiTest)
	: guiTest(guiTest)
{
}

void GUITest_init_2::onValueChanged(GUIElementNode* node)
{
	Console::println(node->getName() + ":onValueChanged: " + node->getController()->getValue().getString());
}
