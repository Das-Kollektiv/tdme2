#include <tdme/tests/GUITest_init_1.h>

#include <stdlib.h>

#include <map>
#include <string>

#include <tdme/gui/elements/GUITabController.h>
#include <tdme/gui/events/GUIActionListener_Type.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tests/GUITest.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>

using std::map;
using std::string;

using tdme::tests::GUITest_init_1;
using tdme::gui::elements::GUITabController;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tests::GUITest;
using tdme::utils::MutableString;
using tdme::utils::Console;
using tdme::utils::Exception;

GUITest_init_1::GUITest_init_1(GUITest* guiTest)
	: guiTest(guiTest)
{
}

void GUITest_init_1::onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node)
{
	if (type == GUIActionListener_Type::PERFORMED && node->getName().compare("button") == 0) {
		Console::println(node->getId() + ".actionPerformed()");
		map<string, MutableString> values;
		node->getScreenNode()->getValues(values);
		values.clear();
		values["select"] = MutableString("8");
		values["input"] = MutableString("Enter some more text here!");
		values["checkbox1"] = MutableString("1");
		values["checkbox2"] = MutableString("1");
		values["checkbox3"] = MutableString("1");
		values["dropdown"] = MutableString("11");
		values["radio"] = MutableString("3");
		values["selectmultiple"] = MutableString("|1|2|3|15|16|17|");
		node->getScreenNode()->setValues(values);
		(dynamic_cast< GUITabController* >(node->getScreenNode()->getNodeById("tab1")->getController()))->selectTab();
	} else
	if (type == GUIActionListener_Type::PERFORMED && node->getName().compare("button2") == 0) {
		try {
			{
				auto parentNode = dynamic_cast< GUIParentNode* >((node->getScreenNode()->getNodeById("sadd_inner")));
				parentNode->replaceSubNodes(string("<dropdown-option text=\"Option 1\" value=\"1\" />") +
					"<dropdown-option text=\"Option 2\" value=\"2\" />" +
					"<dropdown-option text=\"Option 3\" value=\"3\" />" +
					"<dropdown-option text=\"Option 4\" value=\"4\" />" +
					"<dropdown-option text=\"Option 5\" value=\"5\" />" +
					"<dropdown-option text=\"Option 6\" value=\"6\" />" +
					"<dropdown-option text=\"Option 7\" value=\"7\" />" +
					"<dropdown-option text=\"Option 8\" value=\"8\" selected=\"true\" />" +
					"<dropdown-option text=\"Option 9\" value=\"9\" />" +
					"<dropdown-option text=\"Option 10\" value=\"10\" />", true);
			}
			{
				auto parentNode = dynamic_cast< GUIParentNode* >((node->getScreenNode()->getNodeById("sasb_inner")));
				parentNode->replaceSubNodes(string("<selectbox-option text=\"Option 1\" value=\"1\" />") +
					"<selectbox-option text=\"Option 2\" value=\"2\" />" +
					"<selectbox-option text=\"Option 3\" value=\"3\" />" +
					"<selectbox-option text=\"Option 4\" value=\"4\" selected=\"true\" />" +
					"<selectbox-option text=\"Option 5\" value=\"5\" />" +
					"<selectbox-option text=\"Option 6\" value=\"6\" />" +
					"<selectbox-option text=\"Option 7\" value=\"7\" />" +
					"<selectbox-option text=\"Option 8\" value=\"8\" />" +
					"<selectbox-option text=\"Option 9\" value=\"9\" />" +
					"<selectbox-option text=\"Option 10\" value=\"10\" />", true);
			}
		} catch (Exception& exception) {
			Console::print(string("GUITest_init_1::onActionPerformed(): An error occurred: "));
			Console::println(string(exception.what()));
			exit(0);
		}
		(dynamic_cast< GUITabController* >(node->getScreenNode()->getNodeById("tab2")->getController()))->selectTab();
	}
}
