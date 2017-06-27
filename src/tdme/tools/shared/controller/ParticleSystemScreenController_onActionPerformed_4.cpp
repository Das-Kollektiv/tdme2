// Generated from /tdme/src/tdme/tools/shared/controller/ParticleSystemScreenController.java
#include <tdme/tools/shared/controller/ParticleSystemScreenController_onActionPerformed_4.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/ParticleSystemScreenController.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/tools/shared/views/SharedParticleSystemView.h>
#include <tdme/utils/MutableString.h>

using tdme::tools::shared::controller::ParticleSystemScreenController_onActionPerformed_4;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINodeController;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::ParticleSystemScreenController;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::SharedParticleSystemView;
using tdme::utils::MutableString;

ParticleSystemScreenController_onActionPerformed_4::ParticleSystemScreenController_onActionPerformed_4(ParticleSystemScreenController *ParticleSystemScreenController_this)
	: super(*static_cast< ::default_init_tag* >(0))
	, ParticleSystemScreenController_this(ParticleSystemScreenController_this)
{
	clinit();
	ctor();
}

void ParticleSystemScreenController_onActionPerformed_4::performAction()
{
	ParticleSystemScreenController_this->opsModel->getController()->setValue(ParticleSystemScreenController_this->value->set(::java::lang::StringBuilder().append(ParticleSystemScreenController_this->view->getPopUpsViews()->getFileDialogScreenController()->getPathName())->append(u"/"_j)
		->append(ParticleSystemScreenController_this->view->getPopUpsViews()->getFileDialogScreenController()->getFileName())->toString()));
	ParticleSystemScreenController_this->modelPath->setPath(ParticleSystemScreenController_this->view->getPopUpsViews()->getFileDialogScreenController()->getPathName());
	ParticleSystemScreenController_this->view->getPopUpsViews()->getFileDialogScreenController()->close();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ParticleSystemScreenController_onActionPerformed_4::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* ParticleSystemScreenController_onActionPerformed_4::getClass0()
{
	return class_();
}

