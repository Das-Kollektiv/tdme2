// Generated from /tdme/src/tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController.java
#include <tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshFile_1.h>

#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController.h>
#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/views/EntityBoundingVolumeView.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/utils/MutableString.h>
#include <ObjectArray.h>
#include <SubArray.h>

using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshFile_1;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::views::EntityBoundingVolumeView;
using tdme::tools::shared::views::PopUps;
using tdme::utils::MutableString;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace gui {
namespace nodes {
typedef ::SubArray< ::tdme::gui::nodes::GUINode, ::java::lang::ObjectArray > GUINodeArray;
typedef ::SubArray< ::tdme::gui::nodes::GUIParentNode, GUINodeArray > GUIParentNodeArray;
typedef ::SubArray< ::tdme::gui::nodes::GUIElementNode, GUIParentNodeArray > GUIElementNodeArray;
}  // namespace nodes
}  // namespace gui
}  // namespace tdme

EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshFile_1::EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshFile_1(EntityBoundingVolumeSubScreenController *EntityBoundingVolumeSubScreenController_this, int32_t idxFinal, LevelEditorEntity* entityFinal)
	: super(*static_cast< ::default_init_tag* >(0))
	, EntityBoundingVolumeSubScreenController_this(EntityBoundingVolumeSubScreenController_this)
	, idxFinal(idxFinal)
	, entityFinal(entityFinal)
{
	clinit();
	ctor();
}

void EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshFile_1::performAction()
{
	(*EntityBoundingVolumeSubScreenController_this->boundingvolumeConvexMeshFile)[idxFinal]->getController()->setValue(EntityBoundingVolumeSubScreenController_this->value->set(EntityBoundingVolumeSubScreenController_this->view->getPopUpsViews()->getFileDialogScreenController()->getFileName()));
	EntityBoundingVolumeSubScreenController_this->onBoundingVolumeConvexMeshApply(entityFinal, idxFinal);
	EntityBoundingVolumeSubScreenController_this->modelPath->setPath(EntityBoundingVolumeSubScreenController_this->view->getPopUpsViews()->getFileDialogScreenController()->getPathName());
	EntityBoundingVolumeSubScreenController_this->view->getPopUpsViews()->getFileDialogScreenController()->close();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshFile_1::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshFile_1::getClass0()
{
	return class_();
}

