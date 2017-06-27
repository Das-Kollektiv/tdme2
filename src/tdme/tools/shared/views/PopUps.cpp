// Generated from /tdme/src/tdme/tools/shared/views/PopUps.java
#include <tdme/tools/shared/views/PopUps.h>

#include <tdme/engine/Engine.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>

using tdme::tools::shared::views::PopUps;
using tdme::engine::Engine;
using tdme::gui::GUI;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;

PopUps::PopUps(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

PopUps::PopUps() 
	: PopUps(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void PopUps::ctor()
{
	super::ctor();
}

FileDialogScreenController* PopUps::getFileDialogScreenController()
{
	return fileDialogScreenController;
}

InfoDialogScreenController* PopUps::getInfoDialogScreenController()
{
	return infoDialogScreenController;
}

void PopUps::initialize()
{
	fileDialogScreenController = new FileDialogScreenController();
	fileDialogScreenController->initialize();
	infoDialogScreenController = new InfoDialogScreenController();
	infoDialogScreenController->initialize();
	Engine::getInstance()->getGUI()->addScreen(fileDialogScreenController->getScreenNode()->getId(), fileDialogScreenController->getScreenNode());
	Engine::getInstance()->getGUI()->addScreen(infoDialogScreenController->getScreenNode()->getId(), infoDialogScreenController->getScreenNode());
}

void PopUps::dispose()
{
	fileDialogScreenController->dispose();
	infoDialogScreenController->dispose();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* PopUps::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.views.PopUps", 30);
    return c;
}

java::lang::Class* PopUps::getClass0()
{
	return class_();
}

