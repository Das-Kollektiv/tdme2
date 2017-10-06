#include <tdme/tools/shared/controller/InfoDialogScreenController.h>

#include <string>

#include <tdme/gui/GUIParser.h>
#include <tdme/gui/events/GUIActionListener_Type.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/_Exception.h>

using std::wstring;

using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::gui::GUIParser;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::utils::_Console;
using tdme::utils::_Exception;
using tdme::utils::MutableString;

InfoDialogScreenController::InfoDialogScreenController() 
{
	this->value = new MutableString();
}

GUIScreenNode* InfoDialogScreenController::getScreenNode()
{
	return screenNode;
}

void InfoDialogScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse(L"resources/tools/shared/gui", L"infodialog.xml");
		screenNode->setVisible(false);
		screenNode->addActionListener(this);
		captionNode = dynamic_cast< GUITextNode* >(screenNode->getNodeById(L"infodialog_caption"));
		messageNode = dynamic_cast< GUITextNode* >(screenNode->getNodeById(L"infodialog_message"));
	} catch (_Exception& exception) {
		_Console::print(string("InfoDialogScreenController::initialize(): An error occurred: "));
		_Console::println(string(exception.what()));
	}
}

void InfoDialogScreenController::dispose()
{
}

void InfoDialogScreenController::show(const wstring& caption, const wstring& message)
{
	screenNode->setVisible(true);
	captionNode->getText()->set(value->set(caption));
	messageNode->getText()->set(value->set(message));
	screenNode->layout();
}

void InfoDialogScreenController::close()
{
	screenNode->setVisible(false);
}

void InfoDialogScreenController::onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node)
{
	{
		auto v = type;
		if ((v == GUIActionListener_Type::PERFORMED)) {
			{
				if (node->getId().compare(L"infodialog_ok") == 0) {
					close();
				}
				goto end_switch0;;
			}
		}
		if (((v == GUIActionListener_Type::PERFORMED) || ((v != GUIActionListener_Type::PERFORMED)))) {
			{
				goto end_switch0;;
			}
		}
		end_switch0:;
	}
}
