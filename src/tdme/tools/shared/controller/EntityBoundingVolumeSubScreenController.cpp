// Generated from /tdme/src/tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController.java
#include <tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController.h>

#include <java/io/Serializable.h>
#include <java/lang/CharSequence.h>
#include <java/lang/Comparable.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/Rotations.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Capsule.h>
#include <tdme/engine/primitives/ConvexMesh.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/primitives/Sphere.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/gui/events/GUIActionListener_Type.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshFile_1.h>
#include <tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController_BoundingVolumeType.h>
#include <tdme/tools/shared/controller/FileDialogPath.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityBoundingVolume.h>
#include <tdme/tools/shared/tools/Tools.h>
#include <tdme/tools/shared/views/EntityBoundingVolumeView.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/_Console.h>
#include <tdme/utils/_Exception.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController;
using java::io::Serializable;
using java::lang::CharSequence;
using java::lang::Comparable;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::Rotation;
using tdme::engine::Rotations;
using tdme::engine::Transformations;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Capsule;
using tdme::engine::primitives::ConvexMesh;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::Sphere;
using tdme::gui::GUIParser;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshFile_1;
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_BoundingVolumeType;
using tdme::tools::shared::controller::FileDialogPath;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityBoundingVolume;
using tdme::tools::shared::tools::Tools;
using tdme::tools::shared::views::EntityBoundingVolumeView;
using tdme::tools::shared::views::PopUps;
using tdme::utils::MutableString;
using tdme::utils::StringConverter;
using tdme::utils::_Console;
using tdme::utils::_Exception;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::CharSequence, ObjectArray > CharSequenceArray;
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::String, ObjectArray, ::java::io::SerializableArray, ComparableArray, CharSequenceArray > StringArray;
}  // namespace lang
}  // namespace java

namespace tdme {
namespace gui {
namespace nodes {
typedef ::SubArray< ::tdme::gui::nodes::GUINode, ::java::lang::ObjectArray > GUINodeArray;
typedef ::SubArray< ::tdme::gui::nodes::GUIParentNode, GUINodeArray > GUIParentNodeArray;
typedef ::SubArray< ::tdme::gui::nodes::GUIElementNode, GUIParentNodeArray > GUIElementNodeArray;
}  // namespace nodes
}  // namespace gui
}  // namespace tdme

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

EntityBoundingVolumeSubScreenController::EntityBoundingVolumeSubScreenController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

EntityBoundingVolumeSubScreenController::EntityBoundingVolumeSubScreenController(PopUps* popUps, FileDialogPath* modelPath) 
	: EntityBoundingVolumeSubScreenController(*static_cast< ::default_init_tag* >(0))
{
	ctor(popUps,modelPath);
}

constexpr int32_t EntityBoundingVolumeSubScreenController::MODEL_BOUNDINGVOLUME_COUNT;

StringArray* EntityBoundingVolumeSubScreenController::MODEL_BOUNDINGVOLUME_IDS;

void EntityBoundingVolumeSubScreenController::ctor(PopUps* popUps, FileDialogPath* modelPath)
{
	super::ctor();
	this->modelPath = modelPath;
	this->view = new EntityBoundingVolumeView(this, popUps);
}

EntityBoundingVolumeView* EntityBoundingVolumeSubScreenController::getView()
{
	return view;
}

void EntityBoundingVolumeSubScreenController::initialize(GUIScreenNode* screenNode)
{
	value = new MutableString();
	try {
		boundingVolumeTypeDropDown = new GUIElementNodeArray(8);
		boundingVolumeNoneApply = new GUIElementNodeArray(8);
		boundingVolume = new GUIElementNodeArray(8);
		boundingvolumeSphereCenter = new GUIElementNodeArray(8);
		boundingvolumeSphereRadius = new GUIElementNodeArray(8);
		boundingvolumeCapsuleA = new GUIElementNodeArray(8);
		boundingvolumeCapsuleB = new GUIElementNodeArray(8);
		boundingvolumeCapsuleRadius = new GUIElementNodeArray(8);
		boundingvolumeBoundingBoxMin = new GUIElementNodeArray(8);
		boundingvolumeBoundingBoxMax = new GUIElementNodeArray(8);
		boundingvolumeObbCenter = new GUIElementNodeArray(8);
		boundingvolumeObbCenter = new GUIElementNodeArray(8);
		boundingvolumeObbHalfextension = new GUIElementNodeArray(8);
		boundingvolumeObbRotationX = new GUIElementNodeArray(8);
		boundingvolumeObbRotationY = new GUIElementNodeArray(8);
		boundingvolumeObbRotationZ = new GUIElementNodeArray(8);
		boundingvolumeConvexMeshFile = new GUIElementNodeArray(8);
		for (auto i = 0; i < 8; i++) {
			boundingVolumeTypeDropDown->set(i, java_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"boundingvolume_type_"_j)->append(i)->toString())));
			boundingVolumeNoneApply->set(i, java_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"button_boundingvolume_apply_"_j)->append(i)->toString())));
			boundingVolume->set(i, java_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"boundingvolume_"_j)->append(i)->toString())));
			boundingvolumeSphereCenter->set(i, java_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"boundingvolume_sphere_center_"_j)->append(i)->toString())));
			boundingvolumeSphereRadius->set(i, java_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"boundingvolume_sphere_radius_"_j)->append(i)->toString())));
			boundingvolumeCapsuleA->set(i, java_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"boundingvolume_capsule_a_"_j)->append(i)->toString())));
			boundingvolumeCapsuleB->set(i, java_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"boundingvolume_capsule_b_"_j)->append(i)->toString())));
			boundingvolumeCapsuleRadius->set(i, java_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"boundingvolume_capsule_radius_"_j)->append(i)->toString())));
			boundingvolumeBoundingBoxMin->set(i, java_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"boundingvolume_aabb_min_"_j)->append(i)->toString())));
			boundingvolumeBoundingBoxMax->set(i, java_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"boundingvolume_aabb_max_"_j)->append(i)->toString())));
			boundingvolumeObbCenter->set(i, java_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"boundingvolume_obb_center_"_j)->append(i)->toString())));
			boundingvolumeObbCenter->set(i, java_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"boundingvolume_obb_center_"_j)->append(i)->toString())));
			boundingvolumeObbHalfextension->set(i, java_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"boundingvolume_obb_halfextension_"_j)->append(i)->toString())));
			boundingvolumeObbRotationX->set(i, java_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"boundingvolume_obb_rotation_x_"_j)->append(i)->toString())));
			boundingvolumeObbRotationY->set(i, java_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"boundingvolume_obb_rotation_y_"_j)->append(i)->toString())));
			boundingvolumeObbRotationZ->set(i, java_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"boundingvolume_obb_rotation_z_"_j)->append(i)->toString())));
			boundingvolumeConvexMeshFile->set(i, java_cast< GUIElementNode* >(screenNode->getNodeById(::java::lang::StringBuilder().append(u"boundingvolume_convexmesh_file_"_j)->append(i)->toString())));
		}
	} catch (_Exception& exception) {
		_Console::print(string("EntityBoundingVolumeSubScreenController::initialize(): An error occurred: "));
		_Console::println(string(exception.what()));
	}
}

void EntityBoundingVolumeSubScreenController::disableBoundingVolume(int32_t idx)
{
	view->selectBoundingVolumeType(idx, 0);
	(*boundingVolumeTypeDropDown)[idx]->getController()->setDisabled(true);
	(*boundingVolumeNoneApply)[idx]->getController()->setDisabled(true);
}

void EntityBoundingVolumeSubScreenController::enableBoundingVolume(int32_t idx)
{
	(*boundingVolumeTypeDropDown)[idx]->getController()->setDisabled(false);
	(*boundingVolumeNoneApply)[idx]->getController()->setDisabled(false);
}

void EntityBoundingVolumeSubScreenController::setupModelBoundingVolumeType(LevelEditorEntity* entity, int32_t idx)
{
	if (entity == nullptr) {
		view->selectBoundingVolumeType(idx, 0);
		return;
	}
	auto entityBoundingVolume = entity->getBoundingVolumeAt(idx);
	if (entityBoundingVolume == nullptr) {
		view->selectBoundingVolumeType(idx, 0);
	} else {
		auto bv = entityBoundingVolume->getBoundingVolume();
		if (bv == nullptr) {
			view->selectBoundingVolumeType(idx, 0);
		} else
		if (dynamic_cast< Sphere* >(bv) != nullptr) {
			view->selectBoundingVolumeType(idx, 1);
		} else
		if (dynamic_cast< Capsule* >(bv) != nullptr) {
			view->selectBoundingVolumeType(idx, 2);
		} else
		if (dynamic_cast< BoundingBox* >(bv) != nullptr) {
			view->selectBoundingVolumeType(idx, 3);
		} else
		if (dynamic_cast< OrientedBoundingBox* >(bv) != nullptr) {
			view->selectBoundingVolumeType(idx, 4);
		} else
		if (dynamic_cast< ConvexMesh* >(bv) != nullptr) {
			view->selectBoundingVolumeType(idx, 5);
		} else {
			_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"ModelViewerScreenController::onTabSelected(): invalid bounding volume@"_j)->append(idx)
				->append(u": "_j)
				->append(static_cast< Object* >(bv))->toString()));
		}
	}
}

void EntityBoundingVolumeSubScreenController::setupBoundingVolumeTypes(int32_t idx, StringArray* boundingVolumeTypes)
{
	auto boundingVolumeTypeDropDownInnerNode = java_cast< GUIParentNode* >(((*boundingVolumeTypeDropDown)[idx]->getScreenNode()->getNodeById(::java::lang::StringBuilder().append((*boundingVolumeTypeDropDown)[idx]->getId())->append(u"_inner"_j)->toString())));
	auto bvIdx = 0;
	auto boundingVolumeTypeDropDownSubNodesXML = u""_j;
	boundingVolumeTypeDropDownSubNodesXML = ::java::lang::StringBuilder(boundingVolumeTypeDropDownSubNodesXML).append(u"<scrollarea-vertical width=\"100%\" height=\"80\">"_j)->toString();
	for (auto bvType : *boundingVolumeTypes) {
		boundingVolumeTypeDropDownSubNodesXML = ::java::lang::StringBuilder(boundingVolumeTypeDropDownSubNodesXML).append(::java::lang::StringBuilder().append(u"<dropdown-option text=\""_j)->append(GUIParser::escapeQuotes(bvType))
			->append(u"\" value=\""_j)
			->append(+(bvIdx++))
			->append(u"\" />\n"_j)->toString())->toString();
	}
	boundingVolumeTypeDropDownSubNodesXML = ::java::lang::StringBuilder(boundingVolumeTypeDropDownSubNodesXML).append(u"</scrollarea-vertical>"_j)->toString();
	try {
		boundingVolumeTypeDropDownInnerNode->replaceSubNodes(boundingVolumeTypeDropDownSubNodesXML, true);
	} catch (_Exception& exception) {
		_Console::print(string("EntityBoundingVolumeSubScreenController::setupBoundingVolumeTypes(): An error occurred: "));
		_Console::println(string(exception.what()));
	}
}

void EntityBoundingVolumeSubScreenController::selectBoundingVolume(int32_t idx, EntityBoundingVolumeSubScreenController_BoundingVolumeType* bvType)
{
	(*boundingVolume)[idx]->getActiveConditions()->remove(u"sphere"_j);
	(*boundingVolume)[idx]->getActiveConditions()->remove(u"capsule"_j);
	(*boundingVolume)[idx]->getActiveConditions()->remove(u"aabb"_j);
	(*boundingVolume)[idx]->getActiveConditions()->remove(u"obb"_j);
	(*boundingVolume)[idx]->getActiveConditions()->remove(u"convexmesh"_j);
	{
		auto v = bvType;
		if ((v == EntityBoundingVolumeSubScreenController_BoundingVolumeType::NONE)) {
			(*boundingVolumeTypeDropDown)[idx]->getController()->setValue(value->set(u"0"_j));
			goto end_switch0;;
		}
		if ((v == EntityBoundingVolumeSubScreenController_BoundingVolumeType::SPHERE)) {
			(*boundingVolumeTypeDropDown)[idx]->getController()->setValue(value->set(u"1"_j));
			(*boundingVolume)[idx]->getActiveConditions()->add(u"sphere"_j);
			goto end_switch0;;
		}
		if ((v == EntityBoundingVolumeSubScreenController_BoundingVolumeType::CAPSULE)) {
			(*boundingVolumeTypeDropDown)[idx]->getController()->setValue(value->set(u"2"_j));
			(*boundingVolume)[idx]->getActiveConditions()->add(u"capsule"_j);
			goto end_switch0;;
		}
		if ((v == EntityBoundingVolumeSubScreenController_BoundingVolumeType::BOUNDINGBOX)) {
			(*boundingVolumeTypeDropDown)[idx]->getController()->setValue(value->set(u"3"_j));
			(*boundingVolume)[idx]->getActiveConditions()->add(u"aabb"_j);
			goto end_switch0;;
		}
		if ((v == EntityBoundingVolumeSubScreenController_BoundingVolumeType::ORIENTEDBOUNDINGBOX)) {
			(*boundingVolumeTypeDropDown)[idx]->getController()->setValue(value->set(u"4"_j));
			(*boundingVolume)[idx]->getActiveConditions()->add(u"obb"_j);
			goto end_switch0;;
		}
		if ((v == EntityBoundingVolumeSubScreenController_BoundingVolumeType::CONVEXMESH)) {
			(*boundingVolumeTypeDropDown)[idx]->getController()->setValue(value->set(u"5"_j));
			(*boundingVolume)[idx]->getActiveConditions()->add(u"convexmesh"_j);
			goto end_switch0;;
		}
end_switch0:;
	}

}

void EntityBoundingVolumeSubScreenController::setupSphere(int32_t idx, Vector3* center, float radius)
{
	selectBoundingVolume(idx, EntityBoundingVolumeSubScreenController_BoundingVolumeType::SPHERE);
	(*boundingvolumeSphereCenter)[idx]->getController()->setValue(value->reset()->append(Tools::formatFloat(center->getX()))->append(u", "_j)->append(Tools::formatFloat(center->getY()))->append(u", "_j)->append(Tools::formatFloat(center->getZ())));
	(*boundingvolumeSphereRadius)[idx]->getController()->setValue(value->set(Tools::formatFloat(radius)));
}

void EntityBoundingVolumeSubScreenController::setupCapsule(int32_t idx, Vector3* a, Vector3* b, float radius)
{
	selectBoundingVolume(idx, EntityBoundingVolumeSubScreenController_BoundingVolumeType::CAPSULE);
	(*boundingvolumeCapsuleA)[idx]->getController()->setValue(value->reset()->append(Tools::formatFloat(a->getX()))->append(u", "_j)->append(Tools::formatFloat(a->getY()))->append(u", "_j)->append(Tools::formatFloat(a->getZ())));
	(*boundingvolumeCapsuleB)[idx]->getController()->setValue(value->reset()->append(Tools::formatFloat(b->getX()))->append(u", "_j)->append(Tools::formatFloat(b->getY()))->append(u", "_j)->append(Tools::formatFloat(b->getZ())));
	(*boundingvolumeCapsuleRadius)[idx]->getController()->setValue(value->set(Tools::formatFloat(radius)));
}

void EntityBoundingVolumeSubScreenController::setupBoundingBox(int32_t idx, Vector3* min, Vector3* max)
{
	selectBoundingVolume(idx, EntityBoundingVolumeSubScreenController_BoundingVolumeType::BOUNDINGBOX);
	(*boundingvolumeBoundingBoxMin)[idx]->getController()->setValue(value->reset()->append(Tools::formatFloat(min->getX()))->append(u", "_j)->append(Tools::formatFloat(min->getY()))->append(u", "_j)->append(Tools::formatFloat(min->getZ())));
	(*boundingvolumeBoundingBoxMax)[idx]->getController()->setValue(value->reset()->append(Tools::formatFloat(max->getX()))->append(u", "_j)->append(Tools::formatFloat(max->getY()))->append(u", "_j)->append(Tools::formatFloat(max->getZ())));
}

void EntityBoundingVolumeSubScreenController::setupOrientedBoundingBox(int32_t idx, Vector3* center, Vector3* axis0, Vector3* axis1, Vector3* axis2, Vector3* halfExtension)
{
	auto rotation = new Vector3();
	auto rotationMatrix = (new Matrix4x4())->identity();
	rotationMatrix->setAxes(axis0, axis1, axis2);
	rotationMatrix->computeEulerAngles(rotation);
	selectBoundingVolume(idx, EntityBoundingVolumeSubScreenController_BoundingVolumeType::ORIENTEDBOUNDINGBOX);
	(*boundingvolumeObbCenter)[idx]->getController()->setValue(value->reset()->append(Tools::formatFloat(center->getX()))->append(u", "_j)->append(Tools::formatFloat(center->getY()))->append(u", "_j)->append(Tools::formatFloat(center->getZ())));
	(*boundingvolumeObbHalfextension)[idx]->getController()->setValue(value->reset()->append(Tools::formatFloat(halfExtension->getX()))->append(u", "_j)->append(Tools::formatFloat(halfExtension->getY()))->append(u", "_j)->append(Tools::formatFloat(halfExtension->getZ())));
	(*boundingvolumeObbRotationX)[idx]->getController()->setValue(value->set(Tools::formatFloat(rotation->getX())));
	(*boundingvolumeObbRotationY)[idx]->getController()->setValue(value->set(Tools::formatFloat(rotation->getY())));
	(*boundingvolumeObbRotationZ)[idx]->getController()->setValue(value->set(Tools::formatFloat(rotation->getZ())));
}

void EntityBoundingVolumeSubScreenController::setupConvexMesh(int32_t idx, String* file)
{
	selectBoundingVolume(idx, EntityBoundingVolumeSubScreenController_BoundingVolumeType::CONVEXMESH);
	(*boundingvolumeConvexMeshFile)[idx]->getController()->setValue(value->set(file));
}

void EntityBoundingVolumeSubScreenController::onBoundingVolumeTypeApply(LevelEditorEntity* entity, int32_t idx)
{
	auto boundingVolumeTypeId = Tools::convertToIntSilent((*boundingVolumeTypeDropDown)[idx]->getController()->getValue()->toString());
	view->selectBoundingVolumeType(idx, boundingVolumeTypeId);
	switch (boundingVolumeTypeId) {
	case (0):
		onBoundingVolumeNoneApply(entity, idx);
		break;
	case (1):
		onBoundingVolumeSphereApply(entity, idx);
		break;
	case (2):
		onBoundingVolumeCapsuleApply(entity, idx);
		break;
	case (3):
		onBoundingVolumeAabbApply(entity, idx);
		break;
	case (4):
		onBoundingVolumeObbApply(entity, idx);
		break;
	case (5):
		onBoundingVolumeConvexMeshApply(entity, idx);
		break;
	}

}

void EntityBoundingVolumeSubScreenController::onBoundingVolumeNoneApply(LevelEditorEntity* entity, int32_t idx)
{
	view->applyBoundingVolumeNone(entity, idx);
	view->resetBoundingVolume(entity, idx);
}

void EntityBoundingVolumeSubScreenController::onBoundingVolumeSphereApply(LevelEditorEntity* entity, int32_t idx)
{
	try {
		view->applyBoundingVolumeSphere(entity, idx, Tools::convertToVector3((*boundingvolumeSphereCenter)[idx]->getController()->getValue()->toString()), Tools::convertToFloat((*boundingvolumeSphereRadius)[idx]->getController()->getValue()->toString()));
	} catch (_Exception& exception) {
		showErrorPopUp(u"Warning"_j, new String(StringConverter::toWideString(string(exception.what()))));
	}
}

void EntityBoundingVolumeSubScreenController::onBoundingVolumeCapsuleApply(LevelEditorEntity* entity, int32_t idx)
{
	try {
		view->applyBoundingVolumeCapsule(entity, idx, Tools::convertToVector3((*boundingvolumeCapsuleA)[idx]->getController()->getValue()->toString()), Tools::convertToVector3((*boundingvolumeCapsuleB)[idx]->getController()->getValue()->toString()), Tools::convertToFloat((*boundingvolumeCapsuleRadius)[idx]->getController()->getValue()->toString()));
	} catch (_Exception& exception) {
		showErrorPopUp(u"Warning"_j, new String(StringConverter::toWideString(string(exception.what()))));
	}
}

void EntityBoundingVolumeSubScreenController::onBoundingVolumeAabbApply(LevelEditorEntity* entity, int32_t idx)
{
	try {
		view->applyBoundingVolumeAabb(entity, idx, Tools::convertToVector3((*boundingvolumeBoundingBoxMin)[idx]->getController()->getValue()->toString()), Tools::convertToVector3((*boundingvolumeBoundingBoxMax)[idx]->getController()->getValue()->toString()));
	} catch (_Exception& exception) {
		showErrorPopUp(u"Warning"_j, new String(StringConverter::toWideString(string(exception.what()))));
	}
}

void EntityBoundingVolumeSubScreenController::onBoundingVolumeObbApply(LevelEditorEntity* entity, int32_t idx)
{
	try {
		auto rotations = new Transformations();
		rotations->getRotations()->add(new Rotation(Tools::convertToFloat((*boundingvolumeObbRotationZ)[idx]->getController()->getValue()->toString()), OrientedBoundingBox::AABB_AXIS_Z));
		rotations->getRotations()->add(new Rotation(Tools::convertToFloat((*boundingvolumeObbRotationY)[idx]->getController()->getValue()->toString()), OrientedBoundingBox::AABB_AXIS_Y));
		rotations->getRotations()->add(new Rotation(Tools::convertToFloat((*boundingvolumeObbRotationX)[idx]->getController()->getValue()->toString()), OrientedBoundingBox::AABB_AXIS_X));
		rotations->update();
		auto xAxis = new Vector3();
		auto yAxis = new Vector3();
		auto zAxis = new Vector3();
		rotations->getTransformationsMatrix()->getAxes(xAxis, yAxis, zAxis);
		view->applyBoundingVolumeObb(entity, idx, Tools::convertToVector3((*boundingvolumeObbCenter)[idx]->getController()->getValue()->toString()), xAxis, yAxis, zAxis, Tools::convertToVector3((*boundingvolumeObbHalfextension)[idx]->getController()->getValue()->toString()));
	} catch (_Exception& exception) {
		showErrorPopUp(u"Warning"_j, new String(StringConverter::toWideString(string(exception.what()))));
	}
}

void EntityBoundingVolumeSubScreenController::onBoundingVolumeConvexMeshApply(LevelEditorEntity* entity, int32_t idx)
{
	view->applyBoundingVolumeConvexMesh(entity, idx, (*boundingvolumeConvexMeshFile)[idx]->getController()->getValue()->toString());
}

void EntityBoundingVolumeSubScreenController::onBoundingVolumeConvexMeshFile(LevelEditorEntity* entity, int32_t idx)
{
	auto const idxFinal = idx;
	auto const entityFinal = entity;
	view->getPopUpsViews()->getFileDialogScreenController()->show(modelPath->getPath(), u"Load from: "_j, new StringArray({
		u"dae"_j,
		u"tm"_j
	}), entity->getBoundingVolumeAt(idx)->getModelMeshFile() != nullptr ? entity->getBoundingVolumeAt(idx)->getModelMeshFile() : entity->getFileName(), new EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshFile_1(this, idxFinal, entityFinal));
}

void EntityBoundingVolumeSubScreenController::showErrorPopUp(String* caption, String* message)
{
	view->getPopUpsViews()->getInfoDialogScreenController()->show(caption, message);
}

void EntityBoundingVolumeSubScreenController::onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node, LevelEditorEntity* entity)
{
	{
		auto v = type;
		if ((v == GUIActionListener_Type::PERFORMED)) {
{
				if (node->getId()->startsWith(u"button_boundingvolume_apply_"_j)) {
					onBoundingVolumeTypeApply(entity, Tools::convertToIntSilent(node->getId()->substring(node->getId()->lastIndexOf(static_cast< int32_t >(u'_')) + 1)));
				} else if (node->getId()->startsWith(u"button_boundingvolume_sphere_apply_"_j)) {
					onBoundingVolumeSphereApply(entity, Tools::convertToIntSilent(node->getId()->substring(node->getId()->lastIndexOf(static_cast< int32_t >(u'_')) + 1)));
				} else if (node->getId()->startsWith(u"button_boundingvolume_capsule_apply_"_j)) {
					onBoundingVolumeCapsuleApply(entity, Tools::convertToIntSilent(node->getId()->substring(node->getId()->lastIndexOf(static_cast< int32_t >(u'_')) + 1)));
				} else if (node->getId()->startsWith(u"button_boundingvolume_obb_apply_"_j)) {
					onBoundingVolumeObbApply(entity, Tools::convertToIntSilent(node->getId()->substring(node->getId()->lastIndexOf(static_cast< int32_t >(u'_')) + 1)));
				} else if (node->getId()->startsWith(u"button_boundingvolume_aabb_apply_"_j)) {
					onBoundingVolumeAabbApply(entity, Tools::convertToIntSilent(node->getId()->substring(node->getId()->lastIndexOf(static_cast< int32_t >(u'_')) + 1)));
				} else if (node->getId()->startsWith(u"button_boundingvolume_convexmesh_apply_"_j)) {
					onBoundingVolumeConvexMeshApply(entity, Tools::convertToIntSilent(node->getId()->substring(node->getId()->lastIndexOf(static_cast< int32_t >(u'_')) + 1)));
				}
				if (node->getId()->startsWith(u"button_boundingvolume_convexmesh_file_"_j)) {
					onBoundingVolumeConvexMeshFile(entity, Tools::convertToIntSilent(node->getId()->substring(node->getId()->lastIndexOf(static_cast< int32_t >(u'_')) + 1)));
				} else {
					_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"ModelViewerScreenController::onActionPerformed()::unknown, type='"_j)->append(static_cast< Object* >(type))
						->append(u"', id = '"_j)
						->append(node->getId())
						->append(u"'"_j)
						->append(u", name = '"_j)
						->append(node->getName())
						->append(u"'"_j)->toString()));
				}
				goto end_switch1;;
			}		}
		if ((v == GUIActionListener_Type::PERFORMED) || (v == GUIActionListener_Type::PERFORMING)) {
{
				goto end_switch1;;
			}		}
end_switch1:;
	}

}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* EntityBoundingVolumeSubScreenController::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.controller.EntityBoundingVolumeSubScreenController", 68);
    return c;
}

void EntityBoundingVolumeSubScreenController::clinit()
{
	super::clinit();
	static bool in_cl_init = false;
	struct clinit_ {
		clinit_() {
			in_cl_init = true;
		MODEL_BOUNDINGVOLUME_IDS = (new StringArray({
			u"model_bv.0"_j,
			u"model_bv.1"_j,
			u"model_bv.2"_j,
			u"model_bv.3"_j,
			u"model_bv.4"_j,
			u"model_bv.5"_j,
			u"model_bv.6"_j,
			u"model_bv.7"_j
		}));
		}
	};

	if (!in_cl_init) {
		static clinit_ clinit_instance;
	}
}

java::lang::Class* EntityBoundingVolumeSubScreenController::getClass0()
{
	return class_();
}

