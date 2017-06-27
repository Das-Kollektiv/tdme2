// Generated from /tdme/src/tdme/tools/shared/controller/InfoDialogScreenController.java
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>

#include <java/lang/ClassCastException.h>
#include <java/lang/Exception.h>
#include <java/lang/String.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/gui/events/GUIActionListener_Type.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/utils/MutableString.h>

using tdme::tools::shared::controller::InfoDialogScreenController;
using java::lang::ClassCastException;
using java::lang::Exception;
using java::lang::String;
using tdme::gui::GUIParser;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::utils::MutableString;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

InfoDialogScreenController::InfoDialogScreenController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

InfoDialogScreenController::InfoDialogScreenController() 
	: InfoDialogScreenController(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void InfoDialogScreenController::ctor()
{
	super::ctor();
	this->value = new MutableString();
}

GUIScreenNode* InfoDialogScreenController::getScreenNode()
{
	return screenNode;
}

void InfoDialogScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse(u"resources/tools/shared/gui"_j, u"infodialog.xml"_j);
		screenNode->setVisible(false);
		screenNode->addActionListener(this);
		captionNode = java_cast< GUITextNode* >(screenNode->getNodeById(u"infodialog_caption"_j));
		messageNode = java_cast< GUITextNode* >(screenNode->getNodeById(u"infodialog_message"_j));
	} catch (Exception* e) {
		e->printStackTrace();
	}
}

void InfoDialogScreenController::dispose()
{
}

void InfoDialogScreenController::show(String* caption, String* message)
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
				if (node->getId()->equals(u"infodialog_ok"_j)) {
					close();
				}
				goto end_switch0;;
			}		}
		if (((v == GUIActionListener_Type::PERFORMED) || ((v != GUIActionListener_Type::PERFORMED)))) {
{
				goto end_switch0;;
			}		}
end_switch0:;
	}

}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* InfoDialogScreenController::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.controller.InfoDialogScreenController", 55);
    return c;
}

java::lang::Class* InfoDialogScreenController::getClass0()
{
	return class_();
}

