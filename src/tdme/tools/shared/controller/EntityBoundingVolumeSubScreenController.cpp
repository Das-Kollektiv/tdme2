#include <tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController.h>

#include <string>

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
#include <tdme/utils/StringUtils.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/_Exception.h>

using std::wstring;
using std::to_wstring;

using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController;

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
using tdme::utils::StringUtils;
using tdme::utils::Console;
using tdme::utils::_Exception;

constexpr int32_t EntityBoundingVolumeSubScreenController::MODEL_BOUNDINGVOLUME_COUNT;

vector<wstring> EntityBoundingVolumeSubScreenController::MODEL_BOUNDINGVOLUME_IDS = {
	L"model_bv.0",
	L"model_bv.1",
	L"model_bv.2",
	L"model_bv.3",
	L"model_bv.4",
	L"model_bv.5",
	L"model_bv.6",
	L"model_bv.7"
};

EntityBoundingVolumeSubScreenController::EntityBoundingVolumeSubScreenController(PopUps* popUps, FileDialogPath* modelPath) 
{
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
		for (auto i = 0; i < 8; i++) {
			boundingVolumeTypeDropDown[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"boundingvolume_type_" + to_wstring(i)));
			boundingVolumeNoneApply[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"button_boundingvolume_apply_" + to_wstring(i)));
			boundingVolume[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"boundingvolume_" + to_wstring(i)));
			boundingvolumeSphereCenter[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"boundingvolume_sphere_center_" + to_wstring(i)));
			boundingvolumeSphereRadius[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"boundingvolume_sphere_radius_" + to_wstring(i)));
			boundingvolumeCapsuleA[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"boundingvolume_capsule_a_" + to_wstring(i)));
			boundingvolumeCapsuleB[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"boundingvolume_capsule_b_" + to_wstring(i)));
			boundingvolumeCapsuleRadius[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"boundingvolume_capsule_radius_" + to_wstring(i)));
			boundingvolumeBoundingBoxMin[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"boundingvolume_aabb_min_" + to_wstring(i)));
			boundingvolumeBoundingBoxMax[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"boundingvolume_aabb_max_" + to_wstring(i)));
			boundingvolumeObbCenter[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"boundingvolume_obb_center_" + to_wstring(i)));
			boundingvolumeObbCenter[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"boundingvolume_obb_center_" + to_wstring(i)));
			boundingvolumeObbHalfextension[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"boundingvolume_obb_halfextension_" + to_wstring(i)));
			boundingvolumeObbRotationX[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"boundingvolume_obb_rotation_x_" + to_wstring(i)));
			boundingvolumeObbRotationY[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"boundingvolume_obb_rotation_y_" + to_wstring(i)));
			boundingvolumeObbRotationZ[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"boundingvolume_obb_rotation_z_" + to_wstring(i)));
			boundingvolumeConvexMeshFile[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById(L"boundingvolume_convexmesh_file_" + to_wstring(i)));
		}
	} catch (_Exception& exception) {
		Console::print(string("EntityBoundingVolumeSubScreenController::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void EntityBoundingVolumeSubScreenController::disableBoundingVolume(int32_t idx)
{
	view->selectBoundingVolumeType(idx, 0);
	boundingVolumeTypeDropDown[idx]->getController()->setDisabled(true);
	boundingVolumeNoneApply[idx]->getController()->setDisabled(true);
}

void EntityBoundingVolumeSubScreenController::enableBoundingVolume(int32_t idx)
{
	boundingVolumeTypeDropDown[idx]->getController()->setDisabled(false);
	boundingVolumeNoneApply[idx]->getController()->setDisabled(false);
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
			Console::println(wstring(L"ModelViewerScreenController::onTabSelected(): invalid bounding volume@" + to_wstring(idx)));
		}
	}
}

void EntityBoundingVolumeSubScreenController::setupBoundingVolumeTypes(int32_t idx, vector<wstring>* boundingVolumeTypes)
{
	auto boundingVolumeTypeDropDownInnerNode = dynamic_cast< GUIParentNode* >((boundingVolumeTypeDropDown[idx]->getScreenNode()->getNodeById(boundingVolumeTypeDropDown[idx]->getId() + L"_inner")));
	auto bvIdx = 0;
	wstring boundingVolumeTypeDropDownSubNodesXML = L"";
	boundingVolumeTypeDropDownSubNodesXML =
		boundingVolumeTypeDropDownSubNodesXML +
		L"<scrollarea-vertical width=\"100%\" height=\"80\">";
	for (auto& bvType : *boundingVolumeTypes) {
		boundingVolumeTypeDropDownSubNodesXML =
			boundingVolumeTypeDropDownSubNodesXML +
			L"<dropdown-option text=\"" +
			GUIParser::escapeQuotes(bvType) +
			L"\" value=\"" +
			to_wstring(bvIdx++) +
			L"\" />\n";
	}
	boundingVolumeTypeDropDownSubNodesXML =
		boundingVolumeTypeDropDownSubNodesXML +
		L"</scrollarea-vertical>";
	try {
		boundingVolumeTypeDropDownInnerNode->replaceSubNodes(boundingVolumeTypeDropDownSubNodesXML, true);
	} catch (_Exception& exception) {
		Console::print(string("EntityBoundingVolumeSubScreenController::setupBoundingVolumeTypes(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void EntityBoundingVolumeSubScreenController::selectBoundingVolume(int32_t idx, EntityBoundingVolumeSubScreenController_BoundingVolumeType* bvType)
{
	boundingVolume[idx]->getActiveConditions()->remove(L"sphere");
	boundingVolume[idx]->getActiveConditions()->remove(L"capsule");
	boundingVolume[idx]->getActiveConditions()->remove(L"aabb");
	boundingVolume[idx]->getActiveConditions()->remove(L"obb");
	boundingVolume[idx]->getActiveConditions()->remove(L"convexmesh");
	{
		auto v = bvType;
		if ((v == EntityBoundingVolumeSubScreenController_BoundingVolumeType::NONE)) {
			boundingVolumeTypeDropDown[idx]->getController()->setValue(value->set(L"0"));
			goto end_switch0;;
		}
		if ((v == EntityBoundingVolumeSubScreenController_BoundingVolumeType::SPHERE)) {
			boundingVolumeTypeDropDown[idx]->getController()->setValue(value->set(L"1"));
			boundingVolume[idx]->getActiveConditions()->add(L"sphere");
			goto end_switch0;;
		}
		if ((v == EntityBoundingVolumeSubScreenController_BoundingVolumeType::CAPSULE)) {
			boundingVolumeTypeDropDown[idx]->getController()->setValue(value->set(L"2"));
			boundingVolume[idx]->getActiveConditions()->add(L"capsule");
			goto end_switch0;;
		}
		if ((v == EntityBoundingVolumeSubScreenController_BoundingVolumeType::BOUNDINGBOX)) {
			boundingVolumeTypeDropDown[idx]->getController()->setValue(value->set(L"3"));
			boundingVolume[idx]->getActiveConditions()->add(L"aabb");
			goto end_switch0;;
		}
		if ((v == EntityBoundingVolumeSubScreenController_BoundingVolumeType::ORIENTEDBOUNDINGBOX)) {
			boundingVolumeTypeDropDown[idx]->getController()->setValue(value->set(L"4"));
			boundingVolume[idx]->getActiveConditions()->add(L"obb");
			goto end_switch0;;
		}
		if ((v == EntityBoundingVolumeSubScreenController_BoundingVolumeType::CONVEXMESH)) {
			boundingVolumeTypeDropDown[idx]->getController()->setValue(value->set(L"5"));
			boundingVolume[idx]->getActiveConditions()->add(L"convexmesh");
			goto end_switch0;;
		}
		end_switch0:;
	}

}

void EntityBoundingVolumeSubScreenController::setupSphere(int32_t idx, const Vector3& center, float radius)
{
	selectBoundingVolume(idx, EntityBoundingVolumeSubScreenController_BoundingVolumeType::SPHERE);
	boundingvolumeSphereCenter[idx]->getController()->setValue(value->reset()->append(Tools::formatFloat(center.getX()))->append(L", ")->append(Tools::formatFloat(center.getY()))->append(L", ")->append(Tools::formatFloat(center.getZ())));
	boundingvolumeSphereRadius[idx]->getController()->setValue(value->set(Tools::formatFloat(radius)));
}

void EntityBoundingVolumeSubScreenController::setupCapsule(int32_t idx, const Vector3& a, const Vector3& b, float radius)
{
	selectBoundingVolume(idx, EntityBoundingVolumeSubScreenController_BoundingVolumeType::CAPSULE);
	boundingvolumeCapsuleA[idx]->getController()->setValue(value->reset()->append(Tools::formatFloat(a.getX()))->append(L", ")->append(Tools::formatFloat(a.getY()))->append(L", ")->append(Tools::formatFloat(a.getZ())));
	boundingvolumeCapsuleB[idx]->getController()->setValue(value->reset()->append(Tools::formatFloat(b.getX()))->append(L", ")->append(Tools::formatFloat(b.getY()))->append(L", ")->append(Tools::formatFloat(b.getZ())));
	boundingvolumeCapsuleRadius[idx]->getController()->setValue(value->set(Tools::formatFloat(radius)));
}

void EntityBoundingVolumeSubScreenController::setupBoundingBox(int32_t idx, const Vector3& min, const Vector3& max)
{
	selectBoundingVolume(idx, EntityBoundingVolumeSubScreenController_BoundingVolumeType::BOUNDINGBOX);
	boundingvolumeBoundingBoxMin[idx]->getController()->setValue(value->reset()->append(Tools::formatFloat(min.getX()))->append(L", ")->append(Tools::formatFloat(min.getY()))->append(L", ")->append(Tools::formatFloat(min.getZ())));
	boundingvolumeBoundingBoxMax[idx]->getController()->setValue(value->reset()->append(Tools::formatFloat(max.getX()))->append(L", ")->append(Tools::formatFloat(max.getY()))->append(L", ")->append(Tools::formatFloat(max.getZ())));
}

void EntityBoundingVolumeSubScreenController::setupOrientedBoundingBox(int32_t idx, const Vector3& center, const Vector3& axis0, const Vector3& axis1, const Vector3& axis2, const Vector3& halfExtension)
{
	Vector3 rotation;
	Matrix4x4 rotationMatrix;
	rotationMatrix.identity();
	rotationMatrix.setAxes(axis0, axis1, axis2);
	rotationMatrix.computeEulerAngles(rotation);
	selectBoundingVolume(idx, EntityBoundingVolumeSubScreenController_BoundingVolumeType::ORIENTEDBOUNDINGBOX);
	boundingvolumeObbCenter[idx]->getController()->setValue(value->reset()->append(Tools::formatFloat(center.getX()))->append(L", ")->append(Tools::formatFloat(center.getY()))->append(L", ")->append(Tools::formatFloat(center.getZ())));
	boundingvolumeObbHalfextension[idx]->getController()->setValue(value->reset()->append(Tools::formatFloat(halfExtension.getX()))->append(L", ")->append(Tools::formatFloat(halfExtension.getY()))->append(L", ")->append(Tools::formatFloat(halfExtension.getZ())));
	boundingvolumeObbRotationX[idx]->getController()->setValue(value->set(Tools::formatFloat(rotation.getX())));
	boundingvolumeObbRotationY[idx]->getController()->setValue(value->set(Tools::formatFloat(rotation.getY())));
	boundingvolumeObbRotationZ[idx]->getController()->setValue(value->set(Tools::formatFloat(rotation.getZ())));
}

void EntityBoundingVolumeSubScreenController::setupConvexMesh(int32_t idx, const wstring& file)
{
	selectBoundingVolume(idx, EntityBoundingVolumeSubScreenController_BoundingVolumeType::CONVEXMESH);
	boundingvolumeConvexMeshFile[idx]->getController()->setValue(value->set(file));
}

void EntityBoundingVolumeSubScreenController::onBoundingVolumeTypeApply(LevelEditorEntity* entity, int32_t idx)
{
	auto boundingVolumeTypeId = Tools::convertToIntSilent(boundingVolumeTypeDropDown[idx]->getController()->getValue()->toWString());
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
		view->applyBoundingVolumeSphere(
			entity,
			idx,
			Tools::convertToVector3(boundingvolumeSphereCenter[idx]->getController()->getValue()->toWString()),
			Tools::convertToFloat(boundingvolumeSphereRadius[idx]->getController()->getValue()->toWString())
		);
	} catch (_Exception& exception) {
		showErrorPopUp(L"Warning", StringConverter::toWideString(string(exception.what())));
	}
}

void EntityBoundingVolumeSubScreenController::onBoundingVolumeCapsuleApply(LevelEditorEntity* entity, int32_t idx)
{
	try {
		view->applyBoundingVolumeCapsule(
			entity,
			idx,
			Tools::convertToVector3(boundingvolumeCapsuleA[idx]->getController()->getValue()->toWString()),
			Tools::convertToVector3(boundingvolumeCapsuleB[idx]->getController()->getValue()->toWString()),
			Tools::convertToFloat(boundingvolumeCapsuleRadius[idx]->getController()->getValue()->toWString())
		);
	} catch (_Exception& exception) {
		showErrorPopUp(L"Warning", StringConverter::toWideString(string(exception.what())));
	}
}

void EntityBoundingVolumeSubScreenController::onBoundingVolumeAabbApply(LevelEditorEntity* entity, int32_t idx)
{
	try {
		view->applyBoundingVolumeAabb(
			entity,
			idx,
			Tools::convertToVector3(boundingvolumeBoundingBoxMin[idx]->getController()->getValue()->toWString()),
			Tools::convertToVector3(boundingvolumeBoundingBoxMax[idx]->getController()->getValue()->toWString())
		);
	} catch (_Exception& exception) {
		showErrorPopUp(L"Warning", StringConverter::toWideString(string(exception.what())));
	}
}

void EntityBoundingVolumeSubScreenController::onBoundingVolumeObbApply(LevelEditorEntity* entity, int32_t idx)
{
	try {
		auto rotations = new Transformations();
		rotations->getRotations()->add(new Rotation(Tools::convertToFloat(boundingvolumeObbRotationZ[idx]->getController()->getValue()->toWString()), OrientedBoundingBox::AABB_AXIS_Z));
		rotations->getRotations()->add(new Rotation(Tools::convertToFloat(boundingvolumeObbRotationY[idx]->getController()->getValue()->toWString()), OrientedBoundingBox::AABB_AXIS_Y));
		rotations->getRotations()->add(new Rotation(Tools::convertToFloat(boundingvolumeObbRotationX[idx]->getController()->getValue()->toWString()), OrientedBoundingBox::AABB_AXIS_X));
		rotations->update();
		Vector3 xAxis;
		Vector3 yAxis;
		Vector3 zAxis;
		rotations->getTransformationsMatrix().getAxes(xAxis, yAxis, zAxis);
		view->applyBoundingVolumeObb(
			entity,
			idx,
			Tools::convertToVector3(boundingvolumeObbCenter[idx]->getController()->getValue()->toWString()),
			xAxis,
			yAxis,
			zAxis,
			Tools::convertToVector3(boundingvolumeObbHalfextension[idx]->getController()->getValue()->toWString())
		);
	} catch (_Exception& exception) {
		showErrorPopUp(L"Warning", StringConverter::toWideString(string(exception.what())));
	}
}

void EntityBoundingVolumeSubScreenController::onBoundingVolumeConvexMeshApply(LevelEditorEntity* entity, int32_t idx)
{
	view->applyBoundingVolumeConvexMesh(
		entity,
		idx,
		boundingvolumeConvexMeshFile[idx]->getController()->getValue()->toWString()
	);
}

void EntityBoundingVolumeSubScreenController::onBoundingVolumeConvexMeshFile(LevelEditorEntity* entity, int32_t idx)
{
	auto const idxFinal = idx;
	auto const entityFinal = entity;
	vector<wstring> extensions = {
		L"dae",
		L"tm"
	};
	view->getPopUpsViews()->getFileDialogScreenController()->show(
		modelPath->getPath(),
		L"Load from: ",
		&extensions,
		entity->getBoundingVolumeAt(idx)->getModelMeshFile().length() > 0 ? entity->getBoundingVolumeAt(idx)->getModelMeshFile() : entity->getFileName(),
		new EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshFile_1(this, idxFinal, entityFinal)
	);
}

void EntityBoundingVolumeSubScreenController::showErrorPopUp(const wstring& caption, const wstring& message)
{
	view->getPopUpsViews()->getInfoDialogScreenController()->show(caption, message);
}

void EntityBoundingVolumeSubScreenController::onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node, LevelEditorEntity* entity)
{
	{
		auto v = type;
		if ((v == GUIActionListener_Type::PERFORMED)) {
			{
				if (StringUtils::startsWith(node->getId(), L"button_boundingvolume_apply_")) {
					onBoundingVolumeTypeApply(entity, Tools::convertToIntSilent(node->getId().substr(StringUtils::lastIndexOf(node->getId(), static_cast< int32_t >(u'_')) + 1)));
				} else if (StringUtils::startsWith(node->getId(), L"button_boundingvolume_sphere_apply_")) {
					onBoundingVolumeSphereApply(entity, Tools::convertToIntSilent(node->getId().substr(StringUtils::lastIndexOf(node->getId(), static_cast< int32_t >(u'_')) + 1)));
				} else if (StringUtils::startsWith(node->getId(), L"button_boundingvolume_capsule_apply_")) {
					onBoundingVolumeCapsuleApply(entity, Tools::convertToIntSilent(node->getId().substr(StringUtils::lastIndexOf(node->getId(), static_cast< int32_t >(u'_')) + 1)));
				} else if (StringUtils::startsWith(node->getId(), L"button_boundingvolume_obb_apply_")) {
					onBoundingVolumeObbApply(entity, Tools::convertToIntSilent(node->getId().substr(StringUtils::lastIndexOf(node->getId(), static_cast< int32_t >(u'_')) + 1)));
				} else if (StringUtils::startsWith(node->getId(), L"button_boundingvolume_aabb_apply_")) {
					onBoundingVolumeAabbApply(entity, Tools::convertToIntSilent(node->getId().substr(StringUtils::lastIndexOf(node->getId(), static_cast< int32_t >(u'_')) + 1)));
				} else if (StringUtils::startsWith(node->getId(), L"button_boundingvolume_convexmesh_apply_")) {
					onBoundingVolumeConvexMeshApply(entity, Tools::convertToIntSilent(node->getId().substr(StringUtils::lastIndexOf(node->getId(), static_cast< int32_t >(u'_')) + 1)));
				}
				if (StringUtils::startsWith(node->getId(), L"button_boundingvolume_convexmesh_file_")) {
					onBoundingVolumeConvexMeshFile(entity, Tools::convertToIntSilent(node->getId().substr(StringUtils::lastIndexOf(node->getId(), static_cast< int32_t >(u'_')) + 1)));
				} else {
					Console::println(
						wstring(
							L"ModelViewerScreenController::onActionPerformed()::unknown, type='" +
							type->getName() +
							L"', id = '" +
							node->getId() +
							L"'" +
							L", name = '" +
							node->getName() +
							L"'"
						)
					);
				}
				goto end_switch1;;
			}
		}
		if ((v == GUIActionListener_Type::PERFORMED) || (v == GUIActionListener_Type::PERFORMING)) {
			{
				goto end_switch1;;
			}
		}
		end_switch1:;
	}

}
