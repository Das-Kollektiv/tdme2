// Generated from /tdme/src/tdme/tools/leveleditor/controller/EmptyScreenController.java
#include <tdme/tools/leveleditor/controller/EmptyScreenController.h>

#include <java/lang/String.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/tools/leveleditor/controller/EmptyScreenController_EmptyScreenController_1.h>
#include <tdme/tools/leveleditor/views/EmptyView.h>
#include <tdme/tools/shared/controller/EntityBaseSubScreenController.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/viewer/TDMEViewer.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/_Exception.h>

using tdme::tools::leveleditor::controller::EmptyScreenController;
using java::lang::String;
using tdme::gui::GUIParser;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::tools::leveleditor::controller::EmptyScreenController_EmptyScreenController_1;
using tdme::tools::leveleditor::views::EmptyView;
using tdme::tools::shared::controller::EntityBaseSubScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::views::PopUps;
using tdme::tools::viewer::TDMEViewer;
using tdme::utils::MutableString;
using tdme::utils::_Console;
using tdme::utils::_Exception;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

EmptyScreenController::EmptyScreenController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

EmptyScreenController::EmptyScreenController(EmptyView* view) 
	: EmptyScreenController(*static_cast< ::default_init_tag* >(0))
{
	ctor(view);
}

MutableString* EmptyScreenController::TEXT_EMPTY;

void EmptyScreenController::ctor(EmptyView* view)
{
	super::ctor();
	this->view = view;
	auto const finalView = view;
	this->entityBaseSubScreenController = new EntityBaseSubScreenController(view->getPopUpsViews(), new EmptyScreenController_EmptyScreenController_1(this, finalView));
}

GUIScreenNode* EmptyScreenController::getScreenNode()
{
	return screenNode;
}

void EmptyScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse(u"resources/tools/leveleditor/gui"_j, u"screen_empty.xml"_j);
		screenNode->addActionListener(this);
		screenNode->addChangeListener(this);
		screenCaption = java_cast< GUITextNode* >(screenNode->getNodeById(u"screen_caption"_j));
	} catch (_Exception& exception) {
		_Console::print(string("EmptyScreenController::initialize(): An error occurred: "));
		_Console::println(string(exception.what()));
	}
	entityBaseSubScreenController->initialize(screenNode);
}

void EmptyScreenController::dispose()
{
}

void EmptyScreenController::setScreenCaption(String* text)
{
	screenCaption->getText()->set(text);
	screenNode->layout(screenCaption);
}

void EmptyScreenController::setEntityData(String* name, String* description)
{
	entityBaseSubScreenController->setEntityData(name, description);
}

void EmptyScreenController::unsetEntityData()
{
	entityBaseSubScreenController->unsetEntityData();
}

void EmptyScreenController::setEntityProperties(String* presetId, Iterable* entityProperties, String* selectedName)
{
	entityBaseSubScreenController->setEntityProperties(view->getEntity(), presetId, entityProperties, selectedName);
}

void EmptyScreenController::unsetEntityProperties()
{
	entityBaseSubScreenController->unsetEntityProperties();
}

void EmptyScreenController::onQuit()
{
	TDMEViewer::getInstance()->quit();
}

void EmptyScreenController::showErrorPopUp(String* caption, String* message)
{
	view->getPopUpsViews()->getInfoDialogScreenController()->show(caption, message);
}

void EmptyScreenController::onValueChanged(GUIElementNode* node)
{
	entityBaseSubScreenController->onValueChanged(node, view->getEntity());
}

void EmptyScreenController::onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node)
{
	entityBaseSubScreenController->onActionPerformed(type, node, view->getEntity());
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* EmptyScreenController::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.leveleditor.controller.EmptyScreenController", 55);
    return c;
}

void EmptyScreenController::clinit()
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

java::lang::Class* EmptyScreenController::getClass0()
{
	return class_();
}

