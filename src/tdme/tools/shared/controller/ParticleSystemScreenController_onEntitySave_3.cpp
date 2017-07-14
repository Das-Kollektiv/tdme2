// Generated from /tdme/src/tdme/tools/shared/controller/ParticleSystemScreenController.java
#include <tdme/tools/shared/controller/ParticleSystemScreenController_onEntitySave_3.h>

#include <java/lang/Exception.h>
#include <java/lang/String.h>
#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/ParticleSystemScreenController.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/shared/views/SharedParticleSystemView.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/_Exception.h>

using tdme::tools::shared::controller::ParticleSystemScreenController_onEntitySave_3;
using java::lang::Exception;
using java::lang::String;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::ParticleSystemScreenController;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::SharedParticleSystemView;
using tdme::utils::StringConverter;
using tdme::utils::_Exception;

ParticleSystemScreenController_onEntitySave_3::ParticleSystemScreenController_onEntitySave_3(ParticleSystemScreenController *ParticleSystemScreenController_this)
	: super(*static_cast< ::default_init_tag* >(0))
	, ParticleSystemScreenController_this(ParticleSystemScreenController_this)
{
	clinit();
	ctor();
}

void ParticleSystemScreenController_onEntitySave_3::performAction()
{
	try {
		ParticleSystemScreenController_this->view->saveFile(ParticleSystemScreenController_this->view->getPopUpsViews()->getFileDialogScreenController()->getPathName(), ParticleSystemScreenController_this->view->getPopUpsViews()->getFileDialogScreenController()->getFileName());
		ParticleSystemScreenController_this->particleSystemPath->setPath(ParticleSystemScreenController_this->view->getPopUpsViews()->getFileDialogScreenController()->getPathName());
		ParticleSystemScreenController_this->view->getPopUpsViews()->getFileDialogScreenController()->close();
	} catch (_Exception& exception) {
		ParticleSystemScreenController_this->showErrorPopUp(u"Warning"_j, new String(StringConverter::toWideString(exception.what())));
	}
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ParticleSystemScreenController_onEntitySave_3::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* ParticleSystemScreenController_onEntitySave_3::getClass0()
{
	return class_();
}

