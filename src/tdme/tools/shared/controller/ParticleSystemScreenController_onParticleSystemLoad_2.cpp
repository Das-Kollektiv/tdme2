// Generated from /tdme/src/tdme/tools/shared/controller/ParticleSystemScreenController.java
#include <tdme/tools/shared/controller/ParticleSystemScreenController_onParticleSystemLoad_2.h>

#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/ParticleSystemScreenController.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/shared/views/SharedParticleSystemView.h>

using tdme::tools::shared::controller::ParticleSystemScreenController_onParticleSystemLoad_2;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::ParticleSystemScreenController;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::SharedParticleSystemView;

ParticleSystemScreenController_onParticleSystemLoad_2::ParticleSystemScreenController_onParticleSystemLoad_2(ParticleSystemScreenController *ParticleSystemScreenController_this)
	: super(*static_cast< ::default_init_tag* >(0))
	, ParticleSystemScreenController_this(ParticleSystemScreenController_this)
{
	clinit();
	ctor();
}

void ParticleSystemScreenController_onParticleSystemLoad_2::performAction()
{
	ParticleSystemScreenController_this->view->loadFile(ParticleSystemScreenController_this->view->getPopUpsViews()->getFileDialogScreenController()->getPathName(), ParticleSystemScreenController_this->view->getPopUpsViews()->getFileDialogScreenController()->getFileName());
	ParticleSystemScreenController_this->particleSystemPath->setPath(ParticleSystemScreenController_this->view->getPopUpsViews()->getFileDialogScreenController()->getPathName());
	ParticleSystemScreenController_this->view->getPopUpsViews()->getFileDialogScreenController()->close();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ParticleSystemScreenController_onParticleSystemLoad_2::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* ParticleSystemScreenController_onParticleSystemLoad_2::getClass0()
{
	return class_();
}

