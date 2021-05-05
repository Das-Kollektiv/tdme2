#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypePhysicsSubController.h>

#include <string>

#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Capsule.h>
#include <tdme/engine/primitives/ConvexMesh.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/primitives/Sphere.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/PrototypeBoundingVolume.h>
#include <tdme/engine/prototype/PrototypePhysics.h>
#include <tdme/engine/prototype/PrototypePhysics_BodyType.h>
#include <tdme/engine/Transformations.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/events/Action.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/misc/FileDialogPath.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypePhysicsSubController_BoundingVolumeType.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypePhysicsSubController_GenerateConvexMeshes.h>
#include <tdme/tools/editor/tabviews/subviews/PrototypePhysicsSubView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using std::string;
using std::to_string;

using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController;

using tdme::engine::fileio::models::ModelReader;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Capsule;
using tdme::engine::primitives::ConvexMesh;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::Sphere;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::PrototypeBoundingVolume;
using tdme::engine::prototype::PrototypePhysics;
using tdme::engine::prototype::PrototypePhysics_BodyType;
using tdme::engine::Transformations;
using tdme::gui::events::Action;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUIParser;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::misc::FileDialogPath;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController_BoundingVolumeType;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController_GenerateConvexMeshes;
using tdme::tools::editor::tabviews::subviews::PrototypePhysicsSubView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Float;
using tdme::utilities::Integer;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

PrototypePhysicsSubController::PrototypePhysicsSubController(EditorView* editorView, Engine* engine, PopUps* popUps, FileDialogPath* modelPath, bool isModelBoundingVolumes, int maxBoundingVolumeCount, int32_t boundingVolumeTypeMask)
{
	this->editorView = editorView;
	this->modelPath = modelPath;
	this->view = new PrototypePhysicsSubView(engine, this, popUps, maxBoundingVolumeCount, boundingVolumeTypeMask);
	this->maxBoundingVolumeCount = maxBoundingVolumeCount == -1?Prototype::MODEL_BOUNDINGVOLUME_COUNT:maxBoundingVolumeCount;
	this->isModelBoundingVolumes = isModelBoundingVolumes;
	this->boundingVolumeTabActivated = false;
	this->boundingVolumeIdxActivated = 0;
	this->boundingVolumeTypeCount = 0;
}

PrototypePhysicsSubController::~PrototypePhysicsSubController() {
	delete view;
}

PrototypePhysicsSubView* PrototypePhysicsSubController::getView()
{
	return view;
}

GUIScreenNode* PrototypePhysicsSubController::getScreenNode() {
	return screenNode;
}

void PrototypePhysicsSubController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
	try {
		for (auto i = 0; i < maxBoundingVolumeCount; i++) {
			boundingVolumeTypeDropDown[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("boundingvolume_type_" + to_string(i)));
			boundingVolumeApply[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_boundingvolume_apply_" + to_string(i)));
			boundingVolume[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("boundingvolume_" + to_string(i)));
			boundingvolumeSphereCenter[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("boundingvolume_sphere_center_" + to_string(i)));
			boundingvolumeSphereRadius[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("boundingvolume_sphere_radius_" + to_string(i)));
			boundingvolumeCapsuleA[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("boundingvolume_capsule_a_" + to_string(i)));
			boundingvolumeCapsuleB[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("boundingvolume_capsule_b_" + to_string(i)));
			boundingvolumeCapsuleRadius[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("boundingvolume_capsule_radius_" + to_string(i)));
			boundingvolumeBoundingBoxMin[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("boundingvolume_aabb_min_" + to_string(i)));
			boundingvolumeBoundingBoxMax[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("boundingvolume_aabb_max_" + to_string(i)));
			boundingvolumeObbCenter[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("boundingvolume_obb_center_" + to_string(i)));
			boundingvolumeObbCenter[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("boundingvolume_obb_center_" + to_string(i)));
			boundingvolumeObbHalfextension[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("boundingvolume_obb_halfextension_" + to_string(i)));
			boundingvolumeObbRotationX[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("boundingvolume_obb_rotation_x_" + to_string(i)));
			boundingvolumeObbRotationY[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("boundingvolume_obb_rotation_y_" + to_string(i)));
			boundingvolumeObbRotationZ[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("boundingvolume_obb_rotation_z_" + to_string(i)));
			boundingvolumeConvexMeshFile[i] = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("boundingvolume_convexmesh_file_" + to_string(i)));
		}
		bodyTypeDropdown = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("physics_bodytype_dropdown"));
		bodyTypeDropdownApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("physics_bodytype_dropdown_apply"));
		bodyMass = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("physics_body_mass"));
		bodyBounciness = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("physics_body_bounciness"));
		bodyFriction = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("physics_body_friction"));
		bodyInertiaTensor = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("physics_body_inertiatensor"));
		bodyApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("physics_body_apply"));
		if (isModelBoundingVolumes == true) {
			terrainMesh = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("terrain_mesh"));
			terrainMeshApply = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_terrain_mesh_apply"));
			convexmeshesModeGenerate = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("boundingvolume_convexmeshes_mode_generate"));
			convexmeshesModeModel = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("boundingvolume_convexmeshes_mode_model"));
			convexMeshesFile = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("boundingvolume_convexmeshes_file"));
			convexMeshesLoad = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_boundingvolume_convexmeshes_file"));
			convexMeshesResolution = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("boundingvolume_convexmeshes_resolution"));
			convexMeshesDepth = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("boundingvolume_convexmeshes_depth"));
			convexMeshesConcavity = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("boundingvolume_convexmeshes_concavity"));
			convexMeshesPlaneDownSampling = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("boundingvolume_convexmeshes_planedownsampling"));
			convexMeshesConvexHullDownSampling = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("boundingvolume_convexmeshes_convexhullownsampling"));
			convexMeshesAlpha = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("boundingvolume_convexmeshes_alpha"));
			convexMeshesBeta = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("boundingvolume_convexmeshes_beta"));
			convexMeshesMaxVerticesPerConvexHull = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("boundingvolume_convexmeshes_maxverticesperch"));
			convexMeshesMinVolumePerConvexHull = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("boundingvolume_convexmeshes_minvolumeperch"));
			convexMeshesPCA = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("boundingvolume_convexmeshes_pca"));
			convexMeshesRemove = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_boundingvolume_convexmeshes_remove"));
			convexMeshesGenerate = dynamic_cast< GUIElementNode* >(screenNode->getNodeById("button_boundingvolume_convexmeshes_generate"));
		}
	} catch (Exception& exception) {
		Console::print(string("PrototypePhysicsSubController::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void PrototypePhysicsSubController::disableBoundingVolume(int idx)
{
	view->selectBoundingVolumeType(idx, 0);
	boundingVolumeTypeDropDown[idx]->getController()->setDisabled(true);
	boundingVolumeApply[idx]->getController()->setDisabled(true);
}

void PrototypePhysicsSubController::enableBoundingVolume(int idx)
{
	boundingVolumeTypeDropDown[idx]->getController()->setDisabled(boundingVolumeTypeCount <= 1);
	boundingVolumeApply[idx]->getController()->setDisabled(boundingVolumeTypeCount <= 1);
}

void PrototypePhysicsSubController::setupModelBoundingVolumeType(Prototype* prototype, int idx)
{
	if (prototype == nullptr) {
		view->selectBoundingVolumeType(idx, 0);
		return;
	}
	auto prototypeBoundingVolume = prototype->getBoundingVolume(idx);
	if (prototypeBoundingVolume == nullptr) {
		view->selectBoundingVolumeType(idx, 0);
	} else {
		auto bv = prototypeBoundingVolume->getBoundingVolume();
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
			Console::println(string("ModelEditorScreenController::onTabSelected(): invalid bounding volume@" + to_string(idx)));
		}
	}
}

void PrototypePhysicsSubController::setupBoundingVolumeTypes(int idx, int boundingVolumeTypeMask)
{
	auto boundingVolumeTypeDropDownInnerNode = dynamic_cast<GUIParentNode*>((boundingVolumeTypeDropDown[idx]->getScreenNode()->getNodeById(boundingVolumeTypeDropDown[idx]->getId() + "_inner")));
	auto bvIdx = 0;
	string boundingVolumeTypeDropDownSubNodesXML = "";
	boundingVolumeTypeDropDownSubNodesXML = boundingVolumeTypeDropDownSubNodesXML + "<scrollarea width=\"100%\" height=\"80\">";
	boundingVolumeTypeCount = 0;
	if ((boundingVolumeTypeMask & BOUNDINGVOLUMETYPE_NONE) == BOUNDINGVOLUMETYPE_NONE) {
		boundingVolumeTypeDropDownSubNodesXML = boundingVolumeTypeDropDownSubNodesXML + "<dropdown-option text=\"" + GUIParser::escapeQuotes("None") + "\" value=\"" + to_string(0) + "\" />\n";
		boundingVolumeTypeCount++;
	}
	if ((boundingVolumeTypeMask & BOUNDINGVOLUMETYPE_SPHERE) == BOUNDINGVOLUMETYPE_SPHERE) {
		boundingVolumeTypeDropDownSubNodesXML = boundingVolumeTypeDropDownSubNodesXML + "<dropdown-option text=\"" + GUIParser::escapeQuotes("Sphere") + "\" value=\"" + to_string(1) + "\" />\n";
		boundingVolumeTypeCount++;
	}
	if ((boundingVolumeTypeMask & BOUNDINGVOLUMETYPE_CAPSULE) == BOUNDINGVOLUMETYPE_CAPSULE) {
		boundingVolumeTypeDropDownSubNodesXML = boundingVolumeTypeDropDownSubNodesXML + "<dropdown-option text=\"" + GUIParser::escapeQuotes("Capsule") + "\" value=\"" + to_string(2) + "\" />\n";
		boundingVolumeTypeCount++;
	}
	if ((boundingVolumeTypeMask & BOUNDINGVOLUMETYPE_BOUNDINGBOX) == BOUNDINGVOLUMETYPE_BOUNDINGBOX) {
		boundingVolumeTypeDropDownSubNodesXML = boundingVolumeTypeDropDownSubNodesXML + "<dropdown-option text=\"" + GUIParser::escapeQuotes("Bounding Box") + "\" value=\"" + to_string(3) + "\" />\n";
		boundingVolumeTypeCount++;
	}
	if ((boundingVolumeTypeMask & BOUNDINGVOLUMETYPE_ORIENTEDBOUNDINGBOX) == BOUNDINGVOLUMETYPE_ORIENTEDBOUNDINGBOX) {
		boundingVolumeTypeDropDownSubNodesXML = boundingVolumeTypeDropDownSubNodesXML + "<dropdown-option text=\"" + GUIParser::escapeQuotes("Oriented Bounding Box") + "\" value=\"" + to_string(4) + "\" />\n";
		boundingVolumeTypeCount++;
	}
	if ((boundingVolumeTypeMask & BOUNDINGVOLUMETYPE_CONVEXMESH) == BOUNDINGVOLUMETYPE_CONVEXMESH) {
		boundingVolumeTypeDropDownSubNodesXML = boundingVolumeTypeDropDownSubNodesXML + "<dropdown-option text=\"" + GUIParser::escapeQuotes("Convex Mesh") + "\" value=\"" + to_string(5) + "\" />\n";
		boundingVolumeTypeCount++;
	}
	boundingVolumeTypeDropDownSubNodesXML = boundingVolumeTypeDropDownSubNodesXML + "</scrollarea>";
	try {
		boundingVolumeTypeDropDownInnerNode->replaceSubNodes(boundingVolumeTypeDropDownSubNodesXML, true);
	} catch (Exception& exception) {
		Console::print(string("PrototypePhysicsSubController::setupBoundingVolumeTypes(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	boundingVolumeTypeDropDown[idx]->getController()->setDisabled(boundingVolumeTypeCount <= 1);
}

void PrototypePhysicsSubController::selectBoundingVolume(int idx, PrototypePhysicsSubController_BoundingVolumeType* bvType)
{
	boundingVolume[idx]->getActiveConditions().remove("sphere");
	boundingVolume[idx]->getActiveConditions().remove("capsule");
	boundingVolume[idx]->getActiveConditions().remove("aabb");
	boundingVolume[idx]->getActiveConditions().remove("obb");
	boundingVolume[idx]->getActiveConditions().remove("convexmesh");
	{
		auto v = bvType;
		if (v == PrototypePhysicsSubController_BoundingVolumeType::NONE) {
			boundingVolumeTypeDropDown[idx]->getController()->setValue(MutableString("0"));
		} else
		if (v == PrototypePhysicsSubController_BoundingVolumeType::SPHERE) {
			boundingVolumeTypeDropDown[idx]->getController()->setValue(MutableString("1"));
			boundingVolume[idx]->getActiveConditions().add("sphere");
		} else
		if (v == PrototypePhysicsSubController_BoundingVolumeType::CAPSULE) {
			boundingVolumeTypeDropDown[idx]->getController()->setValue(MutableString("2"));
			boundingVolume[idx]->getActiveConditions().add("capsule");
		} else
		if (v == PrototypePhysicsSubController_BoundingVolumeType::BOUNDINGBOX) {
			boundingVolumeTypeDropDown[idx]->getController()->setValue(MutableString("3"));
			boundingVolume[idx]->getActiveConditions().add("aabb");
		} else
		if (v == PrototypePhysicsSubController_BoundingVolumeType::ORIENTEDBOUNDINGBOX) {
			boundingVolumeTypeDropDown[idx]->getController()->setValue(MutableString("4"));
			boundingVolume[idx]->getActiveConditions().add("obb");
		} else
		if (v == PrototypePhysicsSubController_BoundingVolumeType::CONVEXMESH) {
			boundingVolumeTypeDropDown[idx]->getController()->setValue(MutableString("5"));
			boundingVolume[idx]->getActiveConditions().add("convexmesh");
		}
	}

}

void PrototypePhysicsSubController::setupSphere(int idx, const Vector3& center, float radius)
{
	selectBoundingVolume(idx, PrototypePhysicsSubController_BoundingVolumeType::SPHERE);
	boundingvolumeSphereCenter[idx]->getController()->setValue(MutableString(Tools::formatFloat(center.getX())).append(", ").append(Tools::formatFloat(center.getY())).append(", ").append(Tools::formatFloat(center.getZ())));
	boundingvolumeSphereRadius[idx]->getController()->setValue(MutableString(Tools::formatFloat(radius)));
}

void PrototypePhysicsSubController::setupCapsule(int idx, const Vector3& a, const Vector3& b, float radius)
{
	selectBoundingVolume(idx, PrototypePhysicsSubController_BoundingVolumeType::CAPSULE);
	boundingvolumeCapsuleA[idx]->getController()->setValue(MutableString(Tools::formatFloat(a.getX())).append(", ").append(Tools::formatFloat(a.getY())).append(", ").append(Tools::formatFloat(a.getZ())));
	boundingvolumeCapsuleB[idx]->getController()->setValue(MutableString(Tools::formatFloat(b.getX())).append(", ").append(Tools::formatFloat(b.getY())).append(", ").append(Tools::formatFloat(b.getZ())));
	boundingvolumeCapsuleRadius[idx]->getController()->setValue(MutableString(Tools::formatFloat(radius)));
}

void PrototypePhysicsSubController::setupBoundingBox(int idx, const Vector3& min, const Vector3& max)
{
	selectBoundingVolume(idx, PrototypePhysicsSubController_BoundingVolumeType::BOUNDINGBOX);
	boundingvolumeBoundingBoxMin[idx]->getController()->setValue(MutableString(Tools::formatFloat(min.getX())).append(", ").append(Tools::formatFloat(min.getY())).append(", ").append(Tools::formatFloat(min.getZ())));
	boundingvolumeBoundingBoxMax[idx]->getController()->setValue(MutableString(Tools::formatFloat(max.getX())).append(", ").append(Tools::formatFloat(max.getY())).append(", ").append(Tools::formatFloat(max.getZ())));
}

void PrototypePhysicsSubController::setupOrientedBoundingBox(int idx, const Vector3& center, const Vector3& axis0, const Vector3& axis1, const Vector3& axis2, const Vector3& halfExtension)
{
	Matrix4x4 rotationMatrix;
	rotationMatrix.identity();
	rotationMatrix.setAxes(axis0, axis1, axis2);
	auto rotation = rotationMatrix.computeEulerAngles();
	selectBoundingVolume(idx, PrototypePhysicsSubController_BoundingVolumeType::ORIENTEDBOUNDINGBOX);
	boundingvolumeObbCenter[idx]->getController()->setValue(MutableString(Tools::formatFloat(center.getX())).append(", ").append(Tools::formatFloat(center.getY())).append(", ").append(Tools::formatFloat(center.getZ())));
	boundingvolumeObbHalfextension[idx]->getController()->setValue(MutableString(Tools::formatFloat(halfExtension.getX())).append(", ").append(Tools::formatFloat(halfExtension.getY())).append(", ").append(Tools::formatFloat(halfExtension.getZ())));
	boundingvolumeObbRotationX[idx]->getController()->setValue(MutableString(Tools::formatFloat(rotation.getX())));
	boundingvolumeObbRotationY[idx]->getController()->setValue(MutableString(Tools::formatFloat(rotation.getY())));
	boundingvolumeObbRotationZ[idx]->getController()->setValue(MutableString(Tools::formatFloat(rotation.getZ())));
}

void PrototypePhysicsSubController::setupConvexMesh(int idx, const string& file)
{
	selectBoundingVolume(idx, PrototypePhysicsSubController_BoundingVolumeType::CONVEXMESH);
	boundingvolumeConvexMeshFile[idx]->getController()->setValue(MutableString(file));
}

void PrototypePhysicsSubController::onBoundingVolumeTypeApply(Prototype* prototype, int idx)
{
	auto boundingVolumeTypeId = Tools::convertToIntSilent(boundingVolumeTypeDropDown[idx]->getController()->getValue().getString());
	view->selectBoundingVolumeType(idx, boundingVolumeTypeId);
	switch (boundingVolumeTypeId) {
	case (0):
		view->resetBoundingVolume(prototype, idx, 0);
		onBoundingVolumeNoneApply(prototype, idx);
		break;
	case (1):
		view->resetBoundingVolume(prototype, idx, 1);
		onBoundingVolumeSphereApply(prototype, idx);
		break;
	case (2):
		view->resetBoundingVolume(prototype, idx, 2);
		onBoundingVolumeCapsuleApply(prototype, idx);
		break;
	case (3):
		view->resetBoundingVolume(prototype, idx, 3);
		onBoundingVolumeAabbApply(prototype, idx);
		break;
	case (4):
		view->resetBoundingVolume(prototype, idx, 4);
		onBoundingVolumeObbApply(prototype, idx);
		break;
	case (5):
		view->resetBoundingVolume(prototype, idx, 5);
		onBoundingVolumeConvexMeshApply(prototype, idx);
		break;
	}
}

void PrototypePhysicsSubController::onBoundingVolumeNoneApply(Prototype* prototype, int idx)
{
	view->applyBoundingVolumeNone(prototype, idx);
	view->resetBoundingVolume(prototype, idx, 0);
}

void PrototypePhysicsSubController::onBoundingVolumeSphereApply(Prototype* prototype, int idx)
{
	try {
		view->applyBoundingVolumeSphere(
			prototype,
			idx,
			Tools::convertToVector3(boundingvolumeSphereCenter[idx]->getController()->getValue().getString()),
			Tools::convertToFloat(boundingvolumeSphereRadius[idx]->getController()->getValue().getString())
		);
	} catch (Exception& exception) {
		showErrorPopUp("Warning", (string(exception.what())));
	}
	view->updateGizmo(prototype);
}

void PrototypePhysicsSubController::onBoundingVolumeCapsuleApply(Prototype* prototype, int idx)
{
	try {
		view->applyBoundingVolumeCapsule(
			prototype,
			idx,
			Tools::convertToVector3(boundingvolumeCapsuleA[idx]->getController()->getValue().getString()),
			Tools::convertToVector3(boundingvolumeCapsuleB[idx]->getController()->getValue().getString()),
			Tools::convertToFloat(boundingvolumeCapsuleRadius[idx]->getController()->getValue().getString())
		);
	} catch (Exception& exception) {
		showErrorPopUp("Warning", (string(exception.what())));
	}
	view->updateGizmo(prototype);
}

void PrototypePhysicsSubController::onBoundingVolumeAabbApply(Prototype* prototype, int idx)
{
	try {
		view->applyBoundingVolumeAabb(
			prototype,
			idx,
			Tools::convertToVector3(boundingvolumeBoundingBoxMin[idx]->getController()->getValue().getString()),
			Tools::convertToVector3(boundingvolumeBoundingBoxMax[idx]->getController()->getValue().getString())
		);
	} catch (Exception& exception) {
		showErrorPopUp("Warning", (string(exception.what())));
	}
	view->updateGizmo(prototype);
}

void PrototypePhysicsSubController::onBoundingVolumeObbApply(Prototype* prototype, int idx)
{
	try {
		Transformations rotations;
		rotations.addRotation(OrientedBoundingBox::AABB_AXIS_Z, Tools::convertToFloat(boundingvolumeObbRotationZ[idx]->getController()->getValue().getString()));
		rotations.addRotation(OrientedBoundingBox::AABB_AXIS_Y, Tools::convertToFloat(boundingvolumeObbRotationY[idx]->getController()->getValue().getString()));
		rotations.addRotation(OrientedBoundingBox::AABB_AXIS_X, Tools::convertToFloat(boundingvolumeObbRotationX[idx]->getController()->getValue().getString()));
		rotations.update();
		Vector3 xAxis;
		Vector3 yAxis;
		Vector3 zAxis;
		rotations.getTransformationsMatrix().clone().getAxes(xAxis, yAxis, zAxis);
		view->applyBoundingVolumeObb(
			prototype,
			idx,
			Tools::convertToVector3(boundingvolumeObbCenter[idx]->getController()->getValue().getString()),
			xAxis,
			yAxis,
			zAxis,
			Tools::convertToVector3(boundingvolumeObbHalfextension[idx]->getController()->getValue().getString())
		);
	} catch (Exception& exception) {
		showErrorPopUp("Warning", (string(exception.what())));
	}
	view->updateGizmo(prototype);
}

void PrototypePhysicsSubController::onBoundingVolumeConvexMeshApply(Prototype* prototype, int idx)
{
	view->applyBoundingVolumeConvexMesh(
		prototype,
		idx,
		boundingvolumeConvexMeshFile[idx]->getController()->getValue().getString()
	);
	view->updateGizmo(prototype);
}

void PrototypePhysicsSubController::onBoundingVolumeConvexMeshFile(Prototype* prototype, int idx)
{
	class OnBoundingVolumeConvexMeshFileAction: public virtual Action
	{
	public:
		void performAction() override {
			prototypePhysicsSubController->boundingvolumeConvexMeshFile[idxFinal]->getController()->setValue(
				MutableString(
					prototypePhysicsSubController->view->getPopUps()->getFileDialogScreenController()->getPathName() +
					"/" +
					prototypePhysicsSubController->view->getPopUps()->getFileDialogScreenController()->getFileName()
				)
			);
			prototypePhysicsSubController->onBoundingVolumeConvexMeshApply(prototypeFinal, idxFinal);
			prototypePhysicsSubController->modelPath->setPath(prototypePhysicsSubController->view->getPopUps()->getFileDialogScreenController()->getPathName());
			prototypePhysicsSubController->view->getPopUps()->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param prototypePhysicsSubController prototype physics sub screen controller
		 * @param idxFinal idx final
		 * @param prototypeFinal prototype final
		 */
		OnBoundingVolumeConvexMeshFileAction(PrototypePhysicsSubController* prototypePhysicsSubController, int idxFinal, Prototype* prototypeFinal)
			: prototypePhysicsSubController(prototypePhysicsSubController)
			, idxFinal(idxFinal)
			, prototypeFinal(prototypeFinal) {
		}

	private:
		PrototypePhysicsSubController* prototypePhysicsSubController;
		int idxFinal;
		Prototype* prototypeFinal;
	};


	auto const idxFinal = idx;
	auto const prototypeFinal = prototype;
	vector<string> extensions = ModelReader::getModelExtensions();
	view->getPopUps()->getFileDialogScreenController()->show(
		modelPath->getPath(),
		"Load from: ",
		extensions,
		prototype->getBoundingVolume(idx)->getModelMeshFile().length() > 0 ? prototype->getBoundingVolume(idx)->getModelMeshFile() : prototype->getModelFileName(),
		true,
		new OnBoundingVolumeConvexMeshFileAction(this, idxFinal, prototypeFinal)
	);
}

void PrototypePhysicsSubController::onBoundingVolumeConvexMeshesFile(Prototype* prototype)
{
	class OnBoundingVolumeConvexMeshesFileAction: public virtual Action
	{
	public:
		void performAction() override {
			prototypePhysicsSubController->convexMeshesFile->getController()->setValue(
				MutableString(
					prototypePhysicsSubController->view->getPopUps()->getFileDialogScreenController()->getPathName() +
					"/" +
					prototypePhysicsSubController->view->getPopUps()->getFileDialogScreenController()->getFileName()
				)
			);
			prototypePhysicsSubController->modelPath->setPath(prototypePhysicsSubController->view->getPopUps()->getFileDialogScreenController()->getPathName());
			prototypePhysicsSubController->view->getPopUps()->getFileDialogScreenController()->close();
		}

		/**
		 * Public constructor
		 * @param prototypePhysicsSubController prototype physics sub screen controller
		 * @param prototypeFinal prototype final
		 */
		OnBoundingVolumeConvexMeshesFileAction(PrototypePhysicsSubController* prototypePhysicsSubController, Prototype* prototypeFinal)
			: prototypePhysicsSubController(prototypePhysicsSubController)
			, prototypeFinal(prototypeFinal) {
		}

	private:
		PrototypePhysicsSubController* prototypePhysicsSubController;
		Prototype* prototypeFinal;
	};

	auto const prototypeFinal = prototype;
	vector<string> extensions = ModelReader::getModelExtensions();
	view->getPopUps()->getFileDialogScreenController()->show(
		Tools::getPathName(convexMeshesFile->getController()->getValue().getString()),
		"Load from: ",
		extensions,
		Tools::getFileName(convexMeshesFile->getController()->getValue().getString()),
		true,
		new OnBoundingVolumeConvexMeshesFileAction(this, prototypeFinal)
	);
}

void PrototypePhysicsSubController::onBoundingVolumeConvexMeshesRemove(Prototype* prototype)
{
	PrototypePhysicsSubController_GenerateConvexMeshes::removeConvexMeshes(
		this,
		prototype
	);
}

void PrototypePhysicsSubController::onBoundingVolumeConvexMeshesGenerate(Prototype* prototype)
{
	PrototypePhysicsSubController_GenerateConvexMeshes::generateConvexMeshes(
		this,
		prototype
	);
}

void PrototypePhysicsSubController::setTerrainMesh(Prototype* prototype) {
	terrainMesh->getController()->setValue(MutableString(prototype->isTerrainMesh() == true?"1":""));
	terrainMesh->getController()->setDisabled(false);
	terrainMeshApply->getController()->setDisabled(false);
}

void PrototypePhysicsSubController::onSetTerrainMesh(Prototype* prototype) {
	prototype->setTerrainMesh(terrainMesh->getController()->getValue().equals("1"));
}

void PrototypePhysicsSubController::unsetTerrainMesh() {
	terrainMesh->getController()->setValue(MutableString(""));
	terrainMesh->getController()->setDisabled(true);
	terrainMeshApply->getController()->setDisabled(true);
}

void PrototypePhysicsSubController::unsetConvexMeshes() {
	convexMeshesFile->getController()->setValue(MutableString("model.tm"));
	convexMeshesFile->getController()->setDisabled(true);
	convexMeshesLoad->getController()->setDisabled(true);
	convexmeshesModeGenerate->getController()->setDisabled(true);
	convexmeshesModeModel->getController()->setDisabled(true);
	convexMeshesRemove->getController()->setDisabled(true);
	convexMeshesGenerate->getController()->setDisabled(true);
	onConvexMeshModeChanged(true);
}

void PrototypePhysicsSubController::setConvexMeshes(Prototype* prototype) {
	convexMeshesFile->getController()->setValue(MutableString(prototype->getModelFileName()));
	convexMeshesFile->getController()->setDisabled(false);
	convexMeshesLoad->getController()->setDisabled(false);
	convexmeshesModeGenerate->getController()->setDisabled(false);
	convexmeshesModeModel->getController()->setDisabled(false);
	convexMeshesRemove->getController()->setDisabled(false);
	convexMeshesGenerate->getController()->setDisabled(false);
	onConvexMeshModeChanged(false);
}

void PrototypePhysicsSubController::unsetPhysics() {
	bodyTypeDropdown->getController()->setValue(MutableString("none"));
	bodyTypeDropdown->getController()->setDisabled(true);
	bodyTypeDropdownApply->getController()->setDisabled(true);
	bodyMass->getController()->setValue(Tools::formatFloat(0.0f));
	bodyMass->getController()->setDisabled(true);
	bodyBounciness->getController()->setValue(Tools::formatFloat(0.0f));
	bodyBounciness->getController()->setDisabled(true);
	bodyFriction->getController()->setValue(Tools::formatFloat(0.0f));
	bodyFriction->getController()->setDisabled(true);
	bodyInertiaTensor->getController()->setValue(Tools::formatVector3(Vector3()));
	bodyInertiaTensor->getController()->setDisabled(true);
	bodyApply->getController()->setDisabled(true);
}

void PrototypePhysicsSubController::setPhysics(Prototype* prototype) {
	auto physics = prototype->getPhysics();
	if (physics == nullptr) return;
	if (physics->getType() == PrototypePhysics_BodyType::COLLISION_BODY) {
		bodyTypeDropdown->getController()->setValue(MutableString("collisionbody"));
	} else
	if (physics->getType() == PrototypePhysics_BodyType::DYNAMIC_RIGIDBODY) {
		bodyTypeDropdown->getController()->setValue(MutableString("dynamicrigidbody"));
	} else
	if (physics->getType() == PrototypePhysics_BodyType::STATIC_RIGIDBODY) {
		bodyTypeDropdown->getController()->setValue(MutableString("staticrigidbody"));
	} else {
		bodyTypeDropdown->getController()->setValue(MutableString("none"));
	}
	bodyTypeDropdown->getController()->setDisabled(false);
	bodyTypeDropdownApply->getController()->setDisabled(false);
	bodyMass->getController()->setValue(
		physics->getType() == PrototypePhysics_BodyType::NONE ||
		physics->getType() == PrototypePhysics_BodyType::COLLISION_BODY ||
		physics->getType() == PrototypePhysics_BodyType::STATIC_RIGIDBODY?
			Tools::formatFloat(0.0f):
			Tools::formatFloat(physics->getMass())
	);
	bodyMass->getController()->setDisabled(
		physics->getType() == PrototypePhysics_BodyType::NONE ||
		physics->getType() == PrototypePhysics_BodyType::COLLISION_BODY ||
		physics->getType() == PrototypePhysics_BodyType::STATIC_RIGIDBODY
	);
	bodyBounciness->getController()->setValue(
		physics->getType() == PrototypePhysics_BodyType::NONE ||
		physics->getType() == PrototypePhysics_BodyType::COLLISION_BODY ||
		physics->getType() == PrototypePhysics_BodyType::STATIC_RIGIDBODY?
			Tools::formatFloat(0.0f):
			Tools::formatFloat(physics->getRestitution())
	);
	bodyBounciness->getController()->setDisabled(
		physics->getType() == PrototypePhysics_BodyType::NONE ||
		physics->getType() == PrototypePhysics_BodyType::COLLISION_BODY ||
		physics->getType() == PrototypePhysics_BodyType::STATIC_RIGIDBODY
	);
	bodyFriction->getController()->setValue(
		physics->getType() == PrototypePhysics_BodyType::NONE ||
		physics->getType() == PrototypePhysics_BodyType::COLLISION_BODY?
			Tools::formatFloat(0.0f):
			Tools::formatFloat(physics->getFriction())
	);
	bodyFriction->getController()->setDisabled(
		physics->getType() == PrototypePhysics_BodyType::NONE ||
		physics->getType() == PrototypePhysics_BodyType::COLLISION_BODY
	);
	bodyInertiaTensor->getController()->setValue(
		physics->getType() != PrototypePhysics_BodyType::DYNAMIC_RIGIDBODY?
			Tools::formatVector3(Vector3()):
			Tools::formatVector3(physics->getInertiaTensor())
	);
	bodyInertiaTensor->getController()->setDisabled(
		physics->getType() != PrototypePhysics_BodyType::DYNAMIC_RIGIDBODY
	);
	bodyApply->getController()->setDisabled(
		physics->getType() == PrototypePhysics_BodyType::NONE ||
		physics->getType() == PrototypePhysics_BodyType::COLLISION_BODY
	);
}

void PrototypePhysicsSubController::onPhysicsBodyTypeApply(Prototype* prototype) {
	auto physics = prototype->getPhysics();
	auto type = bodyTypeDropdown->getController()->getValue().getString();
	if (type == "collisionbody") {
		physics->setType(PrototypePhysics_BodyType::COLLISION_BODY);
	} else
	if (type == "dynamicrigidbody") {
		physics->setType(PrototypePhysics_BodyType::DYNAMIC_RIGIDBODY);
	} else
	if (type == "staticrigidbody") {
		physics->setType(PrototypePhysics_BodyType::STATIC_RIGIDBODY);
	} else {
		physics->setType(PrototypePhysics_BodyType::NONE);
	}
	setPhysics(prototype);
}

void PrototypePhysicsSubController::onPhysicsBodyApply(Prototype* prototype) {
	auto physics = prototype->getPhysics();
	try {
		auto mass = Float::parseFloat(bodyMass->getController()->getValue().getString());
		auto bounciness = Float::parseFloat(bodyBounciness->getController()->getValue().getString());
		auto friction = Float::parseFloat(bodyFriction->getController()->getValue().getString());
		auto inertiaTensor = Tools::convertToVector3(bodyInertiaTensor->getController()->getValue().getString());
		if (mass < 0.0f || mass > 1000000000.0f) throw ExceptionBase("mass must be within 0 .. 1,000,000,000");
		if (bounciness < 0.0f || bounciness > 1.0f) throw ExceptionBase("bounciness must be within 0 .. 1");
		if (friction < 0.0f || friction > 1.0f) throw ExceptionBase("friction must be within 0 .. 1");
		physics->setMass(mass);
		physics->setRestitution(bounciness);
		physics->setFriction(friction);
		physics->setInertiaTensor(inertiaTensor);
	} catch (Exception& exception) {
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void PrototypePhysicsSubController::onConvexMeshModeChanged(bool disabled) {
	map<string, MutableString> values;
	screenNode->getValues(values);
	auto convexMeshMode = values["boundingvolume_convexmeshes_mode"].getString();
	auto disableVHACDSettings = disabled == true || convexMeshMode != "vhacd";
	convexMeshesResolution->getController()->setDisabled(disableVHACDSettings);
	convexMeshesResolution->getController()->setValue(MutableString("1000000"));
	convexMeshesDepth->getController()->setDisabled(disableVHACDSettings);
	convexMeshesDepth->getController()->setValue(MutableString("20"));
	convexMeshesConcavity->getController()->setDisabled(disableVHACDSettings);
	convexMeshesConcavity->getController()->setValue(MutableString("0.0025"));
	convexMeshesPlaneDownSampling->getController()->setDisabled(disableVHACDSettings);
	convexMeshesPlaneDownSampling->getController()->setValue(MutableString("4"));
	convexMeshesConvexHullDownSampling->getController()->setDisabled(disableVHACDSettings);
	convexMeshesConvexHullDownSampling->getController()->setValue(MutableString("4"));
	convexMeshesAlpha->getController()->setDisabled(disableVHACDSettings);
	convexMeshesAlpha->getController()->setValue(MutableString("0.05"));
	convexMeshesBeta->getController()->setDisabled(disableVHACDSettings);
	convexMeshesBeta->getController()->setValue(MutableString("0.05"));
	convexMeshesMaxVerticesPerConvexHull->getController()->setDisabled(disableVHACDSettings);
	convexMeshesMaxVerticesPerConvexHull->getController()->setValue(MutableString("256"));
	convexMeshesMinVolumePerConvexHull->getController()->setDisabled(disableVHACDSettings);
	convexMeshesMinVolumePerConvexHull->getController()->setValue(MutableString("0.0001"));
	convexMeshesPCA->getController()->setDisabled(disableVHACDSettings);
	convexMeshesPCA->getController()->setValue(MutableString("0"));
}

void PrototypePhysicsSubController::showErrorPopUp(const string& caption, const string& message)
{
	view->getPopUps()->getInfoDialogScreenController()->show(caption, message);
}

void PrototypePhysicsSubController::createOutlinerPhysicsXML(Prototype* prototype, string& xml) {
	if (prototype->getBoundingVolumeCount() > 0) {
		xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escapeQuotes("Physics") + "\" value=\"" + GUIParser::escapeQuotes("physics") + "\">\n";
		for (auto i = 0; i < prototype->getBoundingVolumeCount(); i++) {
			auto boundingVolumeId = to_string(i);
			xml+= "	<selectbox-option text=\"" + GUIParser::escapeQuotes("Bounding Volume " + boundingVolumeId) + "\" value=\"" + GUIParser::escapeQuotes("physics.boundingvolume." + boundingVolumeId) + "\" />\n";
		}
		xml+= "</selectbox-parent-option>\n";
	}
}

void PrototypePhysicsSubController::setPhysicsDetails(Prototype* prototype) {
	auto physics = prototype->getPhysics();

	editorView->setDetailsContent(
		"<template id=\"details_physics\" src=\"resources/engine/gui/template_details_physics.xml\" />\n"
	);

	try {
		// physics
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_physics"))->getActiveConditions().add("open");

		if (physics->getType() == PrototypePhysics_BodyType::COLLISION_BODY) {
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_bodytype"))->getController()->setValue(MutableString("collisionbody"));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_bodytype_details"))->getActiveConditions().add("open");
		} else
		if (physics->getType() == PrototypePhysics_BodyType::DYNAMIC_RIGIDBODY) {
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_bodytype"))->getController()->setValue(MutableString("dynamicrigidbody"));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_bodytype_details"))->getActiveConditions().add("dynamic");
		} else
		if (physics->getType() == PrototypePhysics_BodyType::STATIC_RIGIDBODY) {
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_bodytype"))->getController()->setValue(MutableString("staticrigidbody"));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_bodytype_details"))->getActiveConditions().add("static");
		} else {
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_bodytype"))->getController()->setValue(MutableString("none"));
		}
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_dynamic_mass"))->getController()->setValue(MutableString(physics->getMass()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_dynamic_bounciness"))->getController()->setValue(MutableString(physics->getRestitution()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_dynamic_friction"))->getController()->setValue(MutableString(physics->getFriction()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_dynamic_inertiatensor_x"))->getController()->setValue(physics->getInertiaTensor().getX());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_dynamic_inertiatensor_y"))->getController()->setValue(physics->getInertiaTensor().getY());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_dynamic_inertiatensor_z"))->getController()->setValue(physics->getInertiaTensor().getZ());

	} catch (Exception& exception) {
		Console::println(string("PrototypePhysicsSubController::setPhysicsDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void PrototypePhysicsSubController::applyPhysicsDetails(Prototype* prototype) {
	try {
		auto physics = prototype->getPhysics();
		auto bodyType = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_bodytype"))->getController()->getValue().getString();
		if (bodyType == "collisionbody") physics->setType(PrototypePhysics_BodyType::COLLISION_BODY); else
		if (bodyType == "dynamicrigidbody") physics->setType(PrototypePhysics_BodyType::DYNAMIC_RIGIDBODY); else
		if (bodyType == "staticrigidbody") physics->setType(PrototypePhysics_BodyType::STATIC_RIGIDBODY);
		physics->setMass(Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_dynamic_mass"))->getController()->getValue().getString()));
		physics->setRestitution(Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_dynamic_bounciness"))->getController()->getValue().getString()));
		physics->setFriction(Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_dynamic_friction"))->getController()->getValue().getString()));
		physics->setInertiaTensor(
			Vector3(
				Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_dynamic_inertiatensor_x"))->getController()->getValue().getString()),
				Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_dynamic_inertiatensor_y"))->getController()->getValue().getString()),
				Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_dynamic_inertiatensor_z"))->getController()->getValue().getString())
			)
		);
	} catch (Exception& exception) {
		Console::println(string("PrototypePhysicsSubController::applyPhysicsDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void PrototypePhysicsSubController::setBoundingVolumeSphereDetails(const Vector3& center, float radius) {
	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_sphere_x"))->getController()->setValue(MutableString(center.getX()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_sphere_y"))->getController()->setValue(MutableString(center.getY()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_sphere_z"))->getController()->setValue(MutableString(center.getZ()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_sphere_radius"))->getController()->setValue(MutableString(radius));
	} catch (Exception& exception) {
		Console::println(string("PrototypePhysicsSubController::setBoundingVolumeSphereDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void PrototypePhysicsSubController::setBoundingVolumeCapsuleDetails(const Vector3& a, const Vector3& b, float radius) {
	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_capsule_a_x"))->getController()->setValue(MutableString(a.getX()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_capsule_a_y"))->getController()->setValue(MutableString(a.getY()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_capsule_a_z"))->getController()->setValue(MutableString(a.getZ()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_capsule_b_x"))->getController()->setValue(MutableString(b.getX()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_capsule_b_y"))->getController()->setValue(MutableString(b.getY()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_capsule_b_z"))->getController()->setValue(MutableString(b.getZ()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_capsule_radius"))->getController()->setValue(MutableString(radius));
	} catch (Exception& exception) {
		Console::println(string("PrototypePhysicsSubController::setBoundingVolumeCapsuleDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void PrototypePhysicsSubController::setBoundingVolumeOBBDetails(const Vector3& center, const Vector3& axis0, const Vector3& axis1, const Vector3& axis2, const Vector3& halfExtension) {
	try {
		Matrix4x4 rotationMatrix;
		rotationMatrix.identity();
		rotationMatrix.setAxes(axis0, axis1, axis2);
		auto rotation = rotationMatrix.computeEulerAngles();
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_obb_x"))->getController()->setValue(MutableString(center.getX()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_obb_y"))->getController()->setValue(MutableString(center.getY()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_obb_z"))->getController()->setValue(MutableString(center.getZ()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_obb_rotation_x"))->getController()->setValue(MutableString(rotation.getX()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_obb_rotation_y"))->getController()->setValue(MutableString(rotation.getY()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_obb_rotation_z"))->getController()->setValue(MutableString(rotation.getZ()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_obb_width"))->getController()->setValue(MutableString(halfExtension.getX() * 2.0f));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_obb_height"))->getController()->setValue(MutableString(halfExtension.getY() * 2.0f));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_obb_depth"))->getController()->setValue(MutableString(halfExtension.getZ() * 2.0f));
	} catch (Exception& exception) {
		Console::println(string("PrototypePhysicsSubController::setBoundingVolumeOBBDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void PrototypePhysicsSubController::setBoundingVolumeDetails(Prototype* prototype, int boundingVolumeIdx) {
	auto physics = prototype->getPhysics();
	auto boundingVolume = prototype->getBoundingVolume(boundingVolumeIdx);

	editorView->setDetailsContent(
		string("<template id=\"details_physics\" src=\"resources/engine/gui/template_details_physics.xml\" />\n") +
		string("<template id=\"details_boundingvolume\" src=\"resources/engine/gui/template_details_boundingvolume.xml\" />\n")
	);

	BoundingBox aabb;
	if (prototype->getModel() != nullptr) {
		aabb = *prototype->getModel()->getBoundingBox();
	} else {
		aabb = BoundingBox(Vector3(-0.5f, 0.0f, -0.5f), Vector3(0.5f, 3.0f, 0.5f));
	}
	auto obb = OrientedBoundingBox(&aabb);

	// set default sphere
	{
		setBoundingVolumeSphereDetails(obb.getCenter(), obb.getHalfExtension().computeLength());
	}
	// set default capsule
	{
		Vector3 a;
		Vector3 b;
		auto radius = 0.0f;
		auto& halfExtensionXYZ = obb.getHalfExtension().getArray();
		if (halfExtensionXYZ[0] > halfExtensionXYZ[1] && halfExtensionXYZ[0] > halfExtensionXYZ[2]) {
			radius = Math::sqrt(halfExtensionXYZ[1] * halfExtensionXYZ[1] + halfExtensionXYZ[2] * halfExtensionXYZ[2]);
			a.set(obb.getAxes()[0]);
			a.scale(-(halfExtensionXYZ[0] - radius));
			a.add(obb.getCenter());
			b.set(obb.getAxes()[0]);
			b.scale(+(halfExtensionXYZ[0] - radius));
			b.add(obb.getCenter());
		} else
		if (halfExtensionXYZ[1] > halfExtensionXYZ[0] && halfExtensionXYZ[1] > halfExtensionXYZ[2]) {
			radius = Math::sqrt(halfExtensionXYZ[0] * halfExtensionXYZ[0] + halfExtensionXYZ[2] * halfExtensionXYZ[2]);
			a.set(obb.getAxes()[1]);
			a.scale(-(halfExtensionXYZ[1] - radius));
			a.add(obb.getCenter());
			b.set(obb.getAxes()[1]);
			b.scale(+(halfExtensionXYZ[1] - radius));
			b.add(obb.getCenter());
		} else {
			radius = Math::sqrt(halfExtensionXYZ[0] * halfExtensionXYZ[0] + halfExtensionXYZ[1] * halfExtensionXYZ[1]);
			a.set(obb.getAxes()[2]);
			a.scale(-(halfExtensionXYZ[2] - radius));
			a.add(obb.getCenter());
			b.set(obb.getAxes()[2]);
			b.scale(+(halfExtensionXYZ[2] - radius));
			b.add(obb.getCenter());
		}
		setBoundingVolumeCapsuleDetails(a, b, radius);
	}
	// set default obb
	{
		setBoundingVolumeOBBDetails(obb.getCenter(), OrientedBoundingBox::AABB_AXIS_X, OrientedBoundingBox::AABB_AXIS_Y, OrientedBoundingBox::AABB_AXIS_Z, obb.getHalfExtension());
	}

	try {
		// physics
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_physics"))->getActiveConditions().add("open");

		if (physics->getType() == PrototypePhysics_BodyType::COLLISION_BODY) {
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_bodytype"))->getController()->setValue(MutableString("collisionbody"));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_bodytype_details"))->getActiveConditions().add("open");
		} else
		if (physics->getType() == PrototypePhysics_BodyType::DYNAMIC_RIGIDBODY) {
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_bodytype"))->getController()->setValue(MutableString("dynamicrigidbody"));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_bodytype_details"))->getActiveConditions().add("dynamic");
		} else
		if (physics->getType() == PrototypePhysics_BodyType::STATIC_RIGIDBODY) {
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_bodytype"))->getController()->setValue(MutableString("staticrigidbody"));
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_bodytype_details"))->getActiveConditions().add("static");
		} else {
			required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_bodytype"))->getController()->setValue(MutableString("none"));
		}
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_dynamic_mass"))->getController()->setValue(MutableString(physics->getMass()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_dynamic_bounciness"))->getController()->setValue(MutableString(physics->getRestitution()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_dynamic_friction"))->getController()->setValue(MutableString(physics->getFriction()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_dynamic_inertiatensor_x"))->getController()->setValue(physics->getInertiaTensor().getX());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_dynamic_inertiatensor_y"))->getController()->setValue(physics->getInertiaTensor().getY());
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_dynamic_inertiatensor_z"))->getController()->setValue(physics->getInertiaTensor().getZ());

		// bounding volume
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_boundingvolume"))->getActiveConditions().add("open");

		{
			auto bv = boundingVolume->getBoundingVolume();
			if (bv == nullptr) {
			} else
			if (dynamic_cast<Sphere*>(bv) != nullptr) {
				required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_type_details"))->getActiveConditions().add("sphere");
				required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_type"))->getController()->setValue(MutableString("sphere"));
				auto sphere = dynamic_cast<Sphere*>(bv);
				setBoundingVolumeSphereDetails(sphere->getCenter(), sphere->getRadius());
			} else
			if (dynamic_cast<Capsule*>(bv) != nullptr) {
				required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_type_details"))->getActiveConditions().add("capsule");
				required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_type"))->getController()->setValue(MutableString("capsule"));
				auto capsule = dynamic_cast<Capsule*>(bv);
				setBoundingVolumeCapsuleDetails(capsule->getA(), capsule->getB(), capsule->getRadius());
			} else
			if (dynamic_cast<OrientedBoundingBox*>(bv) != nullptr) {
				required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_type_details"))->getActiveConditions().add("obb");
				required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_type"))->getController()->setValue(MutableString("obb"));
				auto orientedBoundingBox = dynamic_cast<OrientedBoundingBox*>(bv);
				setBoundingVolumeOBBDetails(
					orientedBoundingBox->getCenter(),
					orientedBoundingBox->getAxes()[0],
					orientedBoundingBox->getAxes()[1],
					orientedBoundingBox->getAxes()[2],
					orientedBoundingBox->getHalfExtension()
				);
			} else
			if (dynamic_cast<ConvexMesh*>(bv) != nullptr) {
				required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_type"))->getController()->setValue(MutableString("convexmesh"));
			} else {
				Console::println(string("PrototypePhysicsSubController::setBoundingVolumeDetails(): invalid bounding volume@" + to_string(boundingVolumeIdx)));
			}
		}
	} catch (Exception& exception) {
		Console::println(string("PrototypePhysicsSubController::setBoundingVolumeDetails(): An error occurred: ") + exception.what());;
		showErrorPopUp("Warning", (string(exception.what())));
	}
}

void PrototypePhysicsSubController::applyBoundingVolumeSphereDetails(Prototype* prototype, int idx)
{
	try {
		view->applyBoundingVolumeSphere(
			prototype,
			idx,
			Vector3(
				Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_sphere_x"))->getController()->getValue().getString()),
				Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_sphere_y"))->getController()->getValue().getString()),
				Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_sphere_z"))->getController()->getValue().getString())
			),
			Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_sphere_radius"))->getController()->getValue().getString())
		);
	} catch (Exception& exception) {
		showErrorPopUp("Warning", (string(exception.what())));
	}
	view->updateGizmo(prototype);
}

void PrototypePhysicsSubController::applyBoundingVolumeCapsuleDetails(Prototype* prototype, int idx)
{
	try {
		view->applyBoundingVolumeCapsule(
			prototype,
			idx,
			Vector3(
				Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_capsule_a_x"))->getController()->getValue().getString()),
				Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_capsule_a_y"))->getController()->getValue().getString()),
				Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_capsule_a_z"))->getController()->getValue().getString())
			),
			Vector3(
				Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_capsule_b_x"))->getController()->getValue().getString()),
				Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_capsule_b_y"))->getController()->getValue().getString()),
				Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_capsule_b_z"))->getController()->getValue().getString())
			),
			Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_capsule_radius"))->getController()->getValue().getString())
		);
	} catch (Exception& exception) {
		showErrorPopUp("Warning", (string(exception.what())));
	}
	view->updateGizmo(prototype);
}

void PrototypePhysicsSubController::applyBoundingVolumeObbDetails(Prototype* prototype, int idx)
{
	try {
		Transformations rotations;
		rotations.addRotation(OrientedBoundingBox::AABB_AXIS_Z, Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_obb_rotation_x"))->getController()->getValue().getString()));
		rotations.addRotation(OrientedBoundingBox::AABB_AXIS_Y, Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_obb_rotation_y"))->getController()->getValue().getString()));
		rotations.addRotation(OrientedBoundingBox::AABB_AXIS_X, Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_obb_rotation_z"))->getController()->getValue().getString()));
		rotations.update();
		Vector3 xAxis;
		Vector3 yAxis;
		Vector3 zAxis;
		rotations.getTransformationsMatrix().clone().getAxes(xAxis, yAxis, zAxis);
		view->applyBoundingVolumeObb(
			prototype,
			idx,
			Vector3(
				Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_obb_x"))->getController()->getValue().getString()),
				Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_obb_y"))->getController()->getValue().getString()),
				Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_obb_z"))->getController()->getValue().getString())
			),
			xAxis,
			yAxis,
			zAxis,
			Vector3(
				0.5f * Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_obb_width"))->getController()->getValue().getString()),
				0.5f * Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_obb_height"))->getController()->getValue().getString()),
				0.5f * Float::parseFloat(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_obb_depth"))->getController()->getValue().getString())
			)
		);
	} catch (Exception& exception) {
		showErrorPopUp("Warning", (string(exception.what())));
	}
	view->updateGizmo(prototype);
}

void PrototypePhysicsSubController::onValueChanged(GUIElementNode* node, Prototype* prototype) {
	for (auto& applyPhysicsNode: applyPhysicsNodes) {
		if (node->getId() == applyPhysicsNode) {
			applyPhysicsDetails(prototype);
			break;
		}
	}
	auto outlinerNode = editorView->getScreenController()->getOutlinerSelection();
	if (StringTools::startsWith(outlinerNode, "physics.boundingvolume.") == true) {
		auto boundingVolumeIdx = Integer::parseInt(StringTools::substring(outlinerNode, string("physics.boundingvolume.").size(), outlinerNode.size()));
		for (auto& applyBoundingVolumeSphereNode: applyBoundingVolumSphereNodes) {
			if (node->getId() == applyBoundingVolumeSphereNode) {
				applyBoundingVolumeSphereDetails(prototype, boundingVolumeIdx);
				break;
			}
		}
		for (auto& applyBoundingVolumeCapsuleNode: applyBoundingVolumCapsuleNodes) {
			if (node->getId() == applyBoundingVolumeCapsuleNode) {
				applyBoundingVolumeCapsuleDetails(prototype, boundingVolumeIdx);
				break;
			}
		}
		for (auto& applyBoundingVolumeOBBNode: applyBoundingVolumOBBNodes) {
			if (node->getId() == applyBoundingVolumeOBBNode) {
				applyBoundingVolumeObbDetails(prototype, boundingVolumeIdx);
				break;
			}
		}
	}
	if (node->getId() == "selectbox_outliner") {
		auto outlinerNode = editorView->getScreenController()->getOutlinerSelection();
		if (outlinerNode == "physics") {
			setPhysicsDetails(prototype);
			view->setDisplayBoundingVolumeIdx(PrototypePhysicsSubView::DISPLAY_BOUNDINGVOLUMEIDX_ALL);
			view->setDisplayBoundingVolume(true);
		} else
		if (StringTools::startsWith(outlinerNode, "physics.boundingvolume.") == true) {
			auto boundingVolumeIdx = Integer::parseInt(StringTools::substring(outlinerNode, string("physics.boundingvolume.").size(), outlinerNode.size()));
			setBoundingVolumeDetails(prototype, boundingVolumeIdx);
			view->setDisplayBoundingVolumeIdx(boundingVolumeIdx);
			view->startEditingBoundingVolume(prototype);
			view->setDisplayBoundingVolume(true);
		} else {
			view->setDisplayBoundingVolumeIdx(PrototypePhysicsSubView::DISPLAY_BOUNDINGVOLUMEIDX_ALL);
			view->endEditingBoundingVolume(prototype);
			view->setDisplayBoundingVolume(false);
		}
	}
	if (StringTools::startsWith(node->getId(), "boundingvolume_convexmeshes_mode") == true) {
		onConvexMeshModeChanged(false);
	}
}

void PrototypePhysicsSubController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node, Prototype* prototype)
{
	if (type == GUIActionListenerType::PERFORMED) {
		if (StringTools::startsWith(node->getId(), "button_boundingvolume_apply_")) {
			onBoundingVolumeTypeApply(prototype, Tools::convertToIntSilent(node->getId().substr(StringTools::lastIndexOf(node->getId(), '_') + 1)));
		} else
		if (StringTools::startsWith(node->getId(), "button_boundingvolume_sphere_apply_")) {
			onBoundingVolumeSphereApply(prototype, Tools::convertToIntSilent(node->getId().substr(StringTools::lastIndexOf(node->getId(), '_') + 1)));
		} else
		if (StringTools::startsWith(node->getId(), "button_boundingvolume_capsule_apply_")) {
			onBoundingVolumeCapsuleApply(prototype, Tools::convertToIntSilent(node->getId().substr(StringTools::lastIndexOf(node->getId(), '_') + 1)));
		} else
		if (StringTools::startsWith(node->getId(), "button_boundingvolume_obb_apply_")) {
			onBoundingVolumeObbApply(prototype, Tools::convertToIntSilent(node->getId().substr(StringTools::lastIndexOf(node->getId(), '_') + 1)));
		} else
		if (StringTools::startsWith(node->getId(), "button_boundingvolume_aabb_apply_")) {
			onBoundingVolumeAabbApply(prototype, Tools::convertToIntSilent(node->getId().substr(StringTools::lastIndexOf(node->getId(), '_') + 1)));
		} else
		if (StringTools::startsWith(node->getId(), "button_boundingvolume_convexmesh_apply_")) {
			onBoundingVolumeConvexMeshApply(prototype, Tools::convertToIntSilent(node->getId().substr(StringTools::lastIndexOf(node->getId(), '_') + 1)));
		} else
		if (StringTools::startsWith(node->getId(), "button_boundingvolume_convexmesh_file_")) {
			onBoundingVolumeConvexMeshFile(prototype, Tools::convertToIntSilent(node->getId().substr(StringTools::lastIndexOf(node->getId(), '_') + 1)));
		} else
		if (node->getId() == "button_terrain_mesh_apply") {
			onSetTerrainMesh(prototype);
		} else
		if (node->getId() == "button_boundingvolume_convexmeshes_file") {
			onBoundingVolumeConvexMeshesFile(prototype);
		} else
		if (node->getId() == "button_boundingvolume_convexmeshes_remove") {
			onBoundingVolumeConvexMeshesRemove(prototype);
		} else
		if (node->getId() == "button_boundingvolume_convexmeshes_generate") {
			onBoundingVolumeConvexMeshesGenerate(prototype);
		} else
		if (node->getId() == "physics_bodytype_dropdown_apply") {
			onPhysicsBodyTypeApply(prototype);
		} else
		if (node->getId() == "physics_body_apply") {
			onPhysicsBodyApply(prototype);
		} else
		if (StringTools::startsWith(node->getId(), "tab_properties_boundingvolume_") == true) {
			if (prototype != nullptr) {
				boundingVolumeIdxActivated = Integer::parseInt(StringTools::substring(node->getId(), string("tab_properties_boundingvolume_").size()));
				view->setDisplayBoundingVolumeIdx(boundingVolumeIdxActivated);
				view->startEditingBoundingVolume(prototype);
			}
		} else
		if (node->getId() == "tab_properties_boundingvolume") {
			if (prototype != nullptr) {
				view->setDisplayBoundingVolumeIdx(boundingVolumeIdxActivated);
				if (boundingVolumeIdxActivated != PrototypePhysicsSubView::DISPLAY_BOUNDINGVOLUMEIDX_ALL) view->startEditingBoundingVolume(prototype);
			}
		} else
		if (StringTools::startsWith(node->getId(), "tab_properties_convexmeshes") == true) {
			if (prototype != nullptr) {
				boundingVolumeIdxActivated = PrototypePhysicsSubView::DISPLAY_BOUNDINGVOLUMEIDX_ALL;
				view->setDisplayBoundingVolumeIdx(boundingVolumeIdxActivated);
				view->endEditingBoundingVolume(prototype);
			}
		} else
		if (StringTools::startsWith(node->getId(), "tab_properties_terrain") == true) {
			if (prototype != nullptr) {
				boundingVolumeIdxActivated = PrototypePhysicsSubView::DISPLAY_BOUNDINGVOLUMEIDX_ALL;
				view->setDisplayBoundingVolumeIdx(boundingVolumeIdxActivated);
				view->endEditingBoundingVolume(prototype);
			}
		} else
		if (StringTools::startsWith(node->getId(), "tab_") == true) {
			if (prototype != nullptr) {
				view->setDisplayBoundingVolumeIdx(PrototypePhysicsSubView::DISPLAY_BOUNDINGVOLUMEIDX_ALL);
				view->endEditingBoundingVolume(prototype);
			}
		}
	}
}
