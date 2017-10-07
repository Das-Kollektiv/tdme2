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
#include <tdme/utils/_Exception.h>

using std::map;
using std::wstring;

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
using tdme::utils::_Exception;

GUITest_init_1::GUITest_init_1(GUITest* guiTest)
	: guiTest(guiTest)
{
}

void GUITest_init_1::onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node)
{
	if (type == GUIActionListener_Type::PERFORMED && node->getName().compare(L"button") == 0) {
		Console::println(node->getId() + L".actionPerformed()");
		map<wstring, MutableString*> values;
		node->getScreenNode()->getValues(&values);
		values.clear();
		values.emplace(L"select", new MutableString(L"8"));
		values.emplace(L"input", new MutableString(L"Enter some more text here!"));
		values.emplace(L"checkbox1", new MutableString(L"1"));
		values.emplace(L"checkbox2", new MutableString(L"1"));
		values.emplace(L"checkbox3", new MutableString(L"1"));
		values.emplace(L"dropdown", new MutableString(L"11"));
		values.emplace(L"radio", new MutableString(L"3"));
		values.emplace(L"selectmultiple", new MutableString(L"|1|2|3|15|16|17|"));
		node->getScreenNode()->setValues(&values);
		(dynamic_cast< GUITabController* >(node->getScreenNode()->getNodeById(L"tab1")->getController()))->selectTab();
	} else
	if (type == GUIActionListener_Type::PERFORMED && node->getName().compare(L"button2") == 0) {
		try {
			{
				auto parentNode = dynamic_cast< GUIParentNode* >((node->getScreenNode()->getNodeById(L"sadd_inner")));
				parentNode->replaceSubNodes(wstring(L"<dropdown-option text=\"Option 1\" value=\"1\" />") +
					L"<dropdown-option text=\"Option 2\" value=\"2\" />" +
					L"<dropdown-option text=\"Option 3\" value=\"3\" />" +
					L"<dropdown-option text=\"Option 4\" value=\"4\" />" +
					L"<dropdown-option text=\"Option 5\" value=\"5\" />" +
					L"<dropdown-option text=\"Option 6\" value=\"6\" />" +
					L"<dropdown-option text=\"Option 7\" value=\"7\" />" +
					L"<dropdown-option text=\"Option 8\" value=\"8\" selected=\"true\" />" +
					L"<dropdown-option text=\"Option 9\" value=\"9\" />" +
					L"<dropdown-option text=\"Option 10\" value=\"10\" />", true);
			}
			{
				auto parentNode = dynamic_cast< GUIParentNode* >((node->getScreenNode()->getNodeById(L"sasb_inner")));
				parentNode->replaceSubNodes(wstring(L"<selectbox-option text=\"Option 1\" value=\"1\" />") +
					L"<selectbox-option text=\"Option 2\" value=\"2\" />" +
					L"<selectbox-option text=\"Option 3\" value=\"3\" />" +
					L"<selectbox-option text=\"Option 4\" value=\"4\" selected=\"true\" />" +
					L"<selectbox-option text=\"Option 5\" value=\"5\" />" +
					L"<selectbox-option text=\"Option 6\" value=\"6\" />" +
					L"<selectbox-option text=\"Option 7\" value=\"7\" />" +
					L"<selectbox-option text=\"Option 8\" value=\"8\" />" +
					L"<selectbox-option text=\"Option 9\" value=\"9\" />" +
					L"<selectbox-option text=\"Option 10\" value=\"10\" />", true);
			}
		} catch (_Exception& exception) {
			Console::print(string("GUITest_init_1::onActionPerformed(): An error occurred: "));
			Console::println(string(exception.what()));
			exit(0);
		}
		(dynamic_cast< GUITabController* >(node->getScreenNode()->getNodeById(L"tab2")->getController()))->selectTab();
	}
}
