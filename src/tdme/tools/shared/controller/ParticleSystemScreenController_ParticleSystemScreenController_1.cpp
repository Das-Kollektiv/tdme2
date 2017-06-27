// Generated from /tdme/src/tdme/tools/shared/controller/ParticleSystemScreenController.java
#include <tdme/tools/shared/controller/ParticleSystemScreenController_ParticleSystemScreenController_1.h>

#include <tdme/tools/shared/controller/ParticleSystemScreenController.h>
#include <tdme/tools/shared/views/SharedParticleSystemView.h>

using tdme::tools::shared::controller::ParticleSystemScreenController_ParticleSystemScreenController_1;
using tdme::tools::shared::controller::ParticleSystemScreenController;
using tdme::tools::shared::views::SharedParticleSystemView;

ParticleSystemScreenController_ParticleSystemScreenController_1::ParticleSystemScreenController_ParticleSystemScreenController_1(ParticleSystemScreenController *ParticleSystemScreenController_this, SharedParticleSystemView* finalView)
	: super(*static_cast< ::default_init_tag* >(0))
	, ParticleSystemScreenController_this(ParticleSystemScreenController_this)
	, finalView(finalView)
{
	clinit();
	ctor();
}

void ParticleSystemScreenController_ParticleSystemScreenController_1::performAction()
{
	finalView->updateGUIElements();
	finalView->onSetEntityData();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ParticleSystemScreenController_ParticleSystemScreenController_1::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* ParticleSystemScreenController_ParticleSystemScreenController_1::getClass0()
{
	return class_();
}

