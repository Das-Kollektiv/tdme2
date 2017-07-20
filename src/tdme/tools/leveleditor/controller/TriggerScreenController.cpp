// Generated from /tdme/src/tdme/tools/leveleditor/controller/TriggerScreenController.java
#include <tdme/tools/leveleditor/controller/TriggerScreenController.h>

#include <java/lang/Float.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/gui/events/GUIActionListener_Type.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/tools/leveleditor/controller/TriggerScreenController_TriggerScreenController_1.h>
#include <tdme/tools/leveleditor/views/TriggerView.h>
#include <tdme/tools/shared/controller/EntityBaseSubScreenController.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/viewer/TDMEViewer.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/_Exception.h>

using tdme::tools::leveleditor::controller::TriggerScreenController;
using java::lang::Float;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::gui::GUIParser;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::tools::leveleditor::controller::TriggerScreenController_TriggerScreenController_1;
using tdme::tools::leveleditor::views::TriggerView;
using tdme::tools::shared::controller::EntityBaseSubScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::tools::Tools;
using tdme::tools::shared::views::PopUps;
using tdme::tools::viewer::TDMEViewer;
using tdme::utils::MutableString;
using tdme::utils::StringConverter;
using tdme::utils::_Console;
using tdme::utils::_Exception;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

TriggerScreenController::TriggerScreenController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

TriggerScreenController::TriggerScreenController(TriggerView* view) 
	: TriggerScreenController(*static_cast< ::default_init_tag* >(0))
{
	ctor(view);
}

MutableString* TriggerScreenController::TEXT_EMPTY;

void TriggerScreenController::ctor(TriggerView* view)
{
	super::ctor();
	this->view = view;
	auto const finalView = view;
	this->entityBaseSubScreenController = new EntityBaseSubScreenController(view->getPopUpsViews(), new TriggerScreenController_TriggerScreenController_1(this, finalView));
}

GUIScreenNode* TriggerScreenController::getScreenNode()
{
	return screenNode;
}

void TriggerScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse(u"resources/tools/leveleditor/gui"_j, u"screen_trigger.xml"_j);
		screenNode->addActionListener(this);
		screenNode->addChangeListener(this);
		screenCaption = java_cast< GUITextNode* >(screenNode->getNodeById(u"screen_caption"_j));
		triggerWidth = java_cast< GUIElementNode* >(screenNode->getNodeById(u"trigger_width"_j));
		triggerHeight = java_cast< GUIElementNode* >(screenNode->getNodeById(u"trigger_height"_j));
		triggerDepth = java_cast< GUIElementNode* >(screenNode->getNodeById(u"trigger_depth"_j));
		triggerApply = java_cast< GUIElementNode* >(screenNode->getNodeById(u"button_trigger_apply"_j));
	} catch (_Exception& exception) {
		_Console::print(string("TriggerScreenController::initialize(): An error occurred: "));
		_Console::println(string(exception.what()));
	}
	entityBaseSubScreenController->initialize(screenNode);
}

void TriggerScreenController::dispose()
{
}

void TriggerScreenController::setScreenCaption(String* text)
{
	screenCaption->getText()->set(text);
	screenNode->layout(screenCaption);
}

void TriggerScreenController::setEntityData(String* name, String* description)
{
	entityBaseSubScreenController->setEntityData(name, description);
}

void TriggerScreenController::unsetEntityData()
{
	entityBaseSubScreenController->unsetEntityData();
}

void TriggerScreenController::setEntityProperties(String* presetId, String* selectedName)
{
	entityBaseSubScreenController->setEntityProperties(view->getEntity(), presetId, selectedName);
}

void TriggerScreenController::unsetEntityProperties()
{
	entityBaseSubScreenController->unsetEntityProperties();
}

void TriggerScreenController::setTrigger(float width, float height, float depth)
{
	triggerWidth->getController()->setDisabled(false);
	triggerWidth->getController()->getValue()->set(Tools::formatFloat(width));
	triggerHeight->getController()->setDisabled(false);
	triggerHeight->getController()->getValue()->set(Tools::formatFloat(height));
	triggerDepth->getController()->setDisabled(false);
	triggerDepth->getController()->getValue()->set(Tools::formatFloat(depth));
	triggerApply->getController()->setDisabled(false);
}

void TriggerScreenController::unsetTrigger()
{
	triggerWidth->getController()->setDisabled(true);
	triggerWidth->getController()->getValue()->set(TEXT_EMPTY);
	triggerHeight->getController()->setDisabled(true);
	triggerHeight->getController()->getValue()->set(TEXT_EMPTY);
	triggerDepth->getController()->setDisabled(true);
	triggerDepth->getController()->getValue()->set(TEXT_EMPTY);
	triggerApply->getController()->setDisabled(true);
}

void TriggerScreenController::onQuit()
{
	TDMEViewer::getInstance()->quit();
}

void TriggerScreenController::onTriggerApply()
{
	try {
		auto width = Float::parseFloat(triggerWidth->getController()->getValue()->toString());
		auto height = Float::parseFloat(triggerHeight->getController()->getValue()->toString());
		auto depth = Float::parseFloat(triggerDepth->getController()->getValue()->toString());
		view->triggerApply(width, height, depth);
	} catch (_Exception& exception) {
		showErrorPopUp(u"Warning"_j, new String(StringConverter::toWideString(string(exception.what()))));
	}
}

void TriggerScreenController::showErrorPopUp(String* caption, String* message)
{
	view->getPopUpsViews()->getInfoDialogScreenController()->show(caption, message);
}

void TriggerScreenController::onValueChanged(GUIElementNode* node)
{
	entityBaseSubScreenController->onValueChanged(node, view->getEntity());
}

void TriggerScreenController::onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node)
{
	entityBaseSubScreenController->onActionPerformed(type, node, view->getEntity());
	{
		auto v = type;
		if ((v == GUIActionListener_Type::PERFORMED)) {
{
				if (node->getId()->equals(u"button_trigger_apply"_j)) {
					onTriggerApply();
				} else {
					_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"TriggerScreenController::onActionPerformed()::unknown, type='"_j)->append(static_cast< Object* >(type))
						->append(u"', id = '"_j)
						->append(node->getId())
						->append(u"'"_j)
						->append(u", name = '"_j)
						->append(node->getName())
						->append(u"'"_j)->toString()));
				}
				goto end_switch0;;
			}		}
		if ((v == GUIActionListener_Type::PERFORMED) || (v == GUIActionListener_Type::PERFORMING)) {
{
				goto end_switch0;;
			}		}
end_switch0:;
	}

}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* TriggerScreenController::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.leveleditor.controller.TriggerScreenController", 57);
    return c;
}

void TriggerScreenController::clinit()
{
	super::clinit();
	static bool in_cl_init = false;
	struct clinit_ {
		clinit_() {
			in_cl_init = true;
		TEXT_EMPTY = new MutableString(u""_j);
		}
	};

	if (!in_cl_init) {
		static clinit_ clinit_instance;
	}
}

java::lang::Class* TriggerScreenController::getClass0()
{
	return class_();
}

