// Generated from /tdme/src/tdme/tools/shared/controller/ScreenController.java
#include <tdme/tools/shared/controller/ScreenController.h>

using tdme::tools::shared::controller::ScreenController;
ScreenController::ScreenController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

ScreenController::ScreenController()
	: ScreenController(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ScreenController::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.controller.ScreenController", 45);
    return c;
}

java::lang::Class* ScreenController::getClass0()
{
	return class_();
}

