// Generated from /tdme/src/tdme/tools/leveleditor/controller/LevelEditorEntityLibraryScreenController.java
#include <tdme/tools/leveleditor/controller/LevelEditorEntityLibraryScreenController_onValueChanged_1.h>

#include <java/lang/Exception.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/leveleditor/controller/LevelEditorEntityLibraryScreenController.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityLibrary.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/_Exception.h>

using tdme::tools::leveleditor::controller::LevelEditorEntityLibraryScreenController_onValueChanged_1;
using java::lang::Exception;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINodeController;
using tdme::math::Vector3;
using tdme::tools::leveleditor::controller::LevelEditorEntityLibraryScreenController;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityLibrary;
using tdme::tools::shared::views::PopUps;
using tdme::utils::MutableString;
using tdme::utils::StringConverter;
using tdme::utils::_Exception;

LevelEditorEntityLibraryScreenController_onValueChanged_1::LevelEditorEntityLibraryScreenController_onValueChanged_1(LevelEditorEntityLibraryScreenController *LevelEditorEntityLibraryScreenController_this, LevelEditorEntityLibrary* entityLibrary)
	: super(*static_cast< ::default_init_tag* >(0))
	, LevelEditorEntityLibraryScreenController_this(LevelEditorEntityLibraryScreenController_this)
	, entityLibrary(entityLibrary)
{
	clinit();
	ctor();
}

void LevelEditorEntityLibraryScreenController_onValueChanged_1::performAction()
{
	try {
		auto entity = entityLibrary->addModel(LevelEditorEntityLibrary::ID_ALLOCATE, LevelEditorEntityLibraryScreenController_this->popUps->getFileDialogScreenController()->getFileName(), u""_j, LevelEditorEntityLibraryScreenController_this->popUps->getFileDialogScreenController()->getPathName(), LevelEditorEntityLibraryScreenController_this->popUps->getFileDialogScreenController()->getFileName(), new Vector3(0.0f, 0.0f, 0.0f));
		entity->setDefaultBoundingVolumes();
		LevelEditorEntityLibraryScreenController_this->setEntityLibrary();
		LevelEditorEntityLibraryScreenController_this->entityLibraryListBox->getController()->setValue(LevelEditorEntityLibraryScreenController_this->entityLibraryListBoxSelection->set(entity->getId()));
		LevelEditorEntityLibraryScreenController_this->onEditEntity();
	} catch (_Exception& exception) {
		LevelEditorEntityLibraryScreenController_this->popUps->getInfoDialogScreenController()->show(
			u"Error"_j,
			::java::lang::StringBuilder().append(u"An error occurred: "_j)->append(new String(StringConverter::toWideString(exception.what())))->toString()
		);
	}
	LevelEditorEntityLibraryScreenController_this->modelPath = LevelEditorEntityLibraryScreenController_this->popUps->getFileDialogScreenController()->getPathName();
	LevelEditorEntityLibraryScreenController_this->popUps->getFileDialogScreenController()->close();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* LevelEditorEntityLibraryScreenController_onValueChanged_1::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* LevelEditorEntityLibraryScreenController_onValueChanged_1::getClass0()
{
	return class_();
}

