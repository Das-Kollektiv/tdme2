#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypePhysicsSubController.h>

#include <memory>
#include <string>

#include <VHACD.h>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/fileio/textures/PNGTextureReader.h>
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
#include <tdme/engine/Transform.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUIImageNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUINodeConditions.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIParentNode.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/GUI.h>
#include <agui/gui/GUIParser.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/controllers/ContextMenuScreenController.h>
#include <tdme/tools/editor/controllers/EditorScreenController.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/misc/GenerateConvexMeshes.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/tabcontrollers/subcontrollers/PrototypePhysicsSubController_BoundingVolumeType.h>
#include <tdme/tools/editor/tabviews/subviews/PrototypePhysicsSubView.h>
#include <tdme/tools/editor/views/EditorView.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/Integer.h>
#include <agui/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using std::make_unique;
using std::string;
using std::to_string;
using std::unique_ptr;

using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController;

using tdme::engine::fileio::models::ModelReader;
using tdme::engine::Texture;
using tdme::engine::fileio::textures::PNGTextureReader;
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
using tdme::engine::Transform;
using agui::gui::events::GUIActionListenerType;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUIImageNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINodeConditions;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIParentNode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::GUIParser;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::controllers::ContextMenuScreenController;
using tdme::tools::editor::controllers::EditorScreenController;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::misc::GenerateConvexMeshes;
using tdme::tools::editor::misc::PopUps;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::tabcontrollers::subcontrollers::PrototypePhysicsSubController_BoundingVolumeType;
using tdme::tools::editor::tabviews::subviews::PrototypePhysicsSubView;
using tdme::tools::editor::views::EditorView;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Float;
using tdme::utilities::Integer;
using agui::utilities::MutableString;
using tdme::utilities::StringTools;

PrototypePhysicsSubController::PrototypePhysicsSubController(EditorView* editorView, TabView* tabView, bool isModelBoundingVolumes, int maxBoundingVolumeCount, int32_t boundingVolumeTypeMask)
{
	this->editorView = editorView;
	this->tabView = tabView;
	this->view = make_unique<PrototypePhysicsSubView>(tabView->getEngine(), this, editorView->getPopUps(), maxBoundingVolumeCount, boundingVolumeTypeMask);
	this->popUps = editorView->getPopUps();
	this->maxBoundingVolumeCount = maxBoundingVolumeCount;
	this->isModelBoundingVolumes = isModelBoundingVolumes;
	this->boundingVolumeTabActivated = false;
	this->boundingVolumeIdxActivated = 0;
	this->boundingVolumeTypeCount = 0;
}

PrototypePhysicsSubController::~PrototypePhysicsSubController() {
}

void PrototypePhysicsSubController::initialize(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
}

void PrototypePhysicsSubController::showInfoPopUp(const string& caption, const string& message)
{
	view->getPopUps()->getInfoDialogScreenController()->show(caption, message);
}

void PrototypePhysicsSubController::createOutlinerPhysicsXML(Prototype* prototype, string& xml) {
	if (prototype->getBoundingVolumeCount() == 0) {
		xml+= "<selectbox-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escape("Physics") + "\" value=\"" + GUIParser::escape("physics") + "\" />\n";
	} else {
		xml+= "<selectbox-parent-option image=\"resources/engine/images/folder.png\" text=\"" + GUIParser::escape("Physics") + "\" value=\"" + GUIParser::escape("physics") + "\">\n";
		for (auto i = 0; i < prototype->getBoundingVolumeCount(); i++) {
			auto boundingVolumeId = to_string(i);
			xml+= "	<selectbox-option image=\"resources/engine/images/bv.png\" text=\"" + GUIParser::escape("Bounding Volume " + boundingVolumeId) + "\" value=\"" + GUIParser::escape("physics.boundingvolumes." + boundingVolumeId) + "\" />\n";
		}
		xml+= "</selectbox-parent-option>\n";
	}
}

void PrototypePhysicsSubController::setPhysicsDetails(Prototype* prototype) {
	auto physics = prototype->getPhysics();
	if (physics == nullptr) return;

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
		Console::printLine("PrototypePhysicsSubController::setPhysicsDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
}

void PrototypePhysicsSubController::applyPhysicsDetails(Prototype* prototype) {
	try {
		auto physics = prototype->getPhysics();
		auto bodyType = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_bodytype"))->getController()->getValue().getString();
		if (bodyType == "collisionbody") physics->setType(PrototypePhysics_BodyType::COLLISION_BODY); else
		if (bodyType == "dynamicrigidbody") physics->setType(PrototypePhysics_BodyType::DYNAMIC_RIGIDBODY); else
		if (bodyType == "staticrigidbody") physics->setType(PrototypePhysics_BodyType::STATIC_RIGIDBODY);
		physics->setMass(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_dynamic_mass"))->getController()->getValue().getString()));
		physics->setRestitution(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_dynamic_bounciness"))->getController()->getValue().getString()));
		physics->setFriction(Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_dynamic_friction"))->getController()->getValue().getString()));
		physics->setInertiaTensor(
			Vector3(
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_dynamic_inertiatensor_x"))->getController()->getValue().getString()),
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_dynamic_inertiatensor_y"))->getController()->getValue().getString()),
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("physics_dynamic_inertiatensor_z"))->getController()->getValue().getString())
			)
		);
	} catch (Exception& exception) {
		Console::printLine("PrototypePhysicsSubController::applyPhysicsDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
}

void PrototypePhysicsSubController::updateDetails(Prototype* prototype, const string& outlinerNode) {
	if (StringTools::startsWith(outlinerNode, "physics.boundingvolumes.") == true) {
		boundingVolumeIdxActivated = Integer::parse(StringTools::substring(outlinerNode, string("physics.boundingvolumes.").size(), outlinerNode.size()));
		setBoundingVolumeDetails(prototype, boundingVolumeIdxActivated);
		view->setDisplayBoundingVolumeIdx(boundingVolumeIdxActivated);
		view->startEditingBoundingVolume(prototype);
		view->setDisplayBoundingVolume(true);
		view->updateGizmo(prototype);
	} else {
		if (outlinerNode == "physics") {
			setPhysicsDetails(prototype);
			view->setDisplayBoundingVolume(true);
		} else {
			view->setDisplayBoundingVolume(false);
		}
		boundingVolumeIdxActivated = PrototypePhysicsSubView::DISPLAY_BOUNDINGVOLUMEIDX_ALL;
		view->setDisplayBoundingVolumeIdx(boundingVolumeIdxActivated);
		view->endEditingBoundingVolume(prototype);
		view->removeGizmo();
	}
}

void PrototypePhysicsSubController::setBoundingVolumeSphereDetails(const Vector3& center, float radius) {
	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_sphere_x"))->getController()->setValue(MutableString(center.getX()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_sphere_y"))->getController()->setValue(MutableString(center.getY()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_sphere_z"))->getController()->setValue(MutableString(center.getZ()));
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_sphere_radius"))->getController()->setValue(MutableString(radius));
	} catch (Exception& exception) {
		Console::printLine("PrototypePhysicsSubController::setBoundingVolumeSphereDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
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
		Console::printLine("PrototypePhysicsSubController::setBoundingVolumeCapsuleDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
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
		Console::printLine("PrototypePhysicsSubController::setBoundingVolumeOBBDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
}

void PrototypePhysicsSubController::setImportConvexMeshFromModelDetails() {
	editorView->setDetailsContent(
		string("<template id=\"details_importconvexmesh\" src=\"resources/engine/gui/template_details_importconvexmesh.xml\" />\n")
	);

	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_importconvexmesh"))->getActiveConditions().add("open");
	} catch (Exception& exception) {
		Console::printLine("PrototypePhysicsSubController::setImportConvexMeshFromModelDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
}

void PrototypePhysicsSubController::setGenerateConvexMeshFromModelDetails() {
	editorView->setDetailsContent(
		string("<template id=\"details_generateconvexmesh\" src=\"resources/engine/gui/template_details_generateconvexmesh.xml\" />\n")
	);

	try {
		required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("details_generateconvexmesh"))->getActiveConditions().add("open");
	} catch (Exception& exception) {
		Console::printLine("PrototypePhysicsSubController::setGenerateConvexMeshFromModelDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
}

void PrototypePhysicsSubController::setBoundingVolumeDetails(Prototype* prototype, int boundingVolumeIdx) {
	auto physics = prototype->getPhysics();
	auto boundingVolume = prototype->getBoundingVolume(boundingVolumeIdx);
	if (boundingVolume == nullptr) return;

	editorView->setDetailsContent(
		(physics != nullptr?string("<template id=\"details_physics\" src=\"resources/engine/gui/template_details_physics.xml\" />\n"):string()) +
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
		const auto& halfExtension = obb.getHalfExtension();
		if (halfExtension[0] > halfExtension[1] && halfExtension[0] > halfExtension[2]) {
			radius = Math::sqrt(halfExtension[1] * halfExtension[1] + halfExtension[2] * halfExtension[2]);
			a.set(obb.getAxes()[0]);
			a.scale(-(halfExtension[0] - radius));
			a.add(obb.getCenter());
			b.set(obb.getAxes()[0]);
			b.scale(+(halfExtension[0] - radius));
			b.add(obb.getCenter());
		} else
		if (halfExtension[1] > halfExtension[0] && halfExtension[1] > halfExtension[2]) {
			radius = Math::sqrt(halfExtension[0] * halfExtension[0] + halfExtension[2] * halfExtension[2]);
			a.set(obb.getAxes()[1]);
			a.scale(-(halfExtension[1] - radius));
			a.add(obb.getCenter());
			b.set(obb.getAxes()[1]);
			b.scale(+(halfExtension[1] - radius));
			b.add(obb.getCenter());
		} else {
			radius = Math::sqrt(halfExtension[0] * halfExtension[0] + halfExtension[1] * halfExtension[1]);
			a.set(obb.getAxes()[2]);
			a.scale(-(halfExtension[2] - radius));
			a.add(obb.getCenter());
			b.set(obb.getAxes()[2]);
			b.scale(+(halfExtension[2] - radius));
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
		if (physics != nullptr) {
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
		}

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
				required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_type_details"))->getActiveConditions().add("convexmesh");
				required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_type"))->getController()->setValue(MutableString("convexmesh"));
				Texture* thumbnailTexture = nullptr;
				string thumbnailTooltip = boundingVolume->hasConvexMeshData() == false?boundingVolume->getConvexMeshFile():"Embedded";
				{
					vector<uint8_t> thumbnailPNGData;
					if (// extern
						(boundingVolume->hasConvexMeshData() == false &&
						StringTools::endsWith(StringTools::toLowerCase(boundingVolume->getConvexMeshFile()), ".tm") == true &&
						FileSystem::getInstance()->getThumbnailAttachment(Tools::getPathName(boundingVolume->getConvexMeshFile()), Tools::getFileName(boundingVolume->getConvexMeshFile()), thumbnailPNGData) == true) ||
						// embedded
						(boundingVolume->hasConvexMeshData() == true &&
						FileSystem::getInstance()->getThumbnailAttachment(boundingVolume->getConvexMeshData(), thumbnailPNGData) == true)
						) {
						thumbnailTexture = PNGTextureReader::read("tdme.editor.physics.convexmeshes." + to_string(thumbnailTextureIdx++), thumbnailPNGData, true);
					}
				}
				required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("boundingvolume_convexmesh_file"))->setTexture(thumbnailTexture);
				required_dynamic_cast<GUIImageNode*>(screenNode->getNodeById("boundingvolume_convexmesh_file"))->setTooltip(thumbnailTooltip);
				if (thumbnailTexture != nullptr) thumbnailTexture->releaseReference();
			} else {
				Console::printLine("PrototypePhysicsSubController::setBoundingVolumeDetails(): invalid bounding volume@" + to_string(boundingVolumeIdx));
			}
		}
	} catch (Exception& exception) {
		Console::printLine("PrototypePhysicsSubController::setBoundingVolumeDetails(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
}

void PrototypePhysicsSubController::applyBoundingVolumeSphereDetails(Prototype* prototype, int idx)
{
	try {
		view->applyBoundingVolumeSphere(
			prototype,
			idx,
			Vector3(
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_sphere_x"))->getController()->getValue().getString()),
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_sphere_y"))->getController()->getValue().getString()),
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_sphere_z"))->getController()->getValue().getString())
			),
			Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_sphere_radius"))->getController()->getValue().getString())
		);
	} catch (Exception& exception) {
		showInfoPopUp("Warning", string(exception.what()));
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
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_capsule_a_x"))->getController()->getValue().getString()),
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_capsule_a_y"))->getController()->getValue().getString()),
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_capsule_a_z"))->getController()->getValue().getString())
			),
			Vector3(
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_capsule_b_x"))->getController()->getValue().getString()),
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_capsule_b_y"))->getController()->getValue().getString()),
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_capsule_b_z"))->getController()->getValue().getString())
			),
			Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_capsule_radius"))->getController()->getValue().getString())
		);
	} catch (Exception& exception) {
		showInfoPopUp("Warning", string(exception.what()));
	}
	view->updateGizmo(prototype);
}

void PrototypePhysicsSubController::applyBoundingVolumeObbDetails(Prototype* prototype, int idx)
{
	try {
		Transform rotations;
		rotations.addRotation(OrientedBoundingBox::AABB_AXIS_Z, Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_obb_rotation_x"))->getController()->getValue().getString()));
		rotations.addRotation(OrientedBoundingBox::AABB_AXIS_Y, Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_obb_rotation_y"))->getController()->getValue().getString()));
		rotations.addRotation(OrientedBoundingBox::AABB_AXIS_X, Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_obb_rotation_z"))->getController()->getValue().getString()));
		rotations.update();
		Vector3 xAxis;
		Vector3 yAxis;
		Vector3 zAxis;
		rotations.getTransformMatrix().clone().getAxes(xAxis, yAxis, zAxis);
		view->applyBoundingVolumeObb(
			prototype,
			idx,
			Vector3(
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_obb_x"))->getController()->getValue().getString()),
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_obb_y"))->getController()->getValue().getString()),
				Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_obb_z"))->getController()->getValue().getString())
			),
			xAxis,
			yAxis,
			zAxis,
			Vector3(
				0.5f * Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_obb_width"))->getController()->getValue().getString()),
				0.5f * Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_obb_height"))->getController()->getValue().getString()),
				0.5f * Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_obb_depth"))->getController()->getValue().getString())
			)
		);
	} catch (Exception& exception) {
		showInfoPopUp("Warning", string(exception.what()));
	}
	view->updateGizmo(prototype);
}

void PrototypePhysicsSubController::applyBoundingVolumeConvexMeshDetails(Prototype* prototype, int idx) {
	try {
		auto boundingVolume = prototype->getBoundingVolume(boundingVolumeIdxActivated);
		view->applyBoundingVolumeConvexMesh(
			prototype,
			idx,
			boundingVolume != nullptr?boundingVolume->getConvexMeshFile():string()
		);
	} catch (Exception& exception) {
		showInfoPopUp("Warning", string(exception.what()));
	}
	view->removeGizmo();
}

void PrototypePhysicsSubController::createBoundingVolume(Prototype* prototype) {
	auto boundingVolumeIdx = prototype->getBoundingVolumeCount();
	prototype->addBoundingVolume(new PrototypeBoundingVolume(prototype));
	setBoundingVolumeDetails(prototype, boundingVolumeIdx);
	editorView->reloadTabOutliner(string() + "physics.boundingvolumes." + to_string(boundingVolumeIdx));
}

bool PrototypePhysicsSubController::onChange(GUIElementNode* node, Prototype* prototype) {
	if (node->getId() == "dropdown_outliner_add") {
		auto addOutlinerType = node->getController()->getValue().getString();
		if (addOutlinerType == "boundingvolume") {
			createBoundingVolume(prototype);
			return true;
		}
	} else {
		for (const auto& applyPhysicsNode: applyPhysicsNodes) {
			if (node->getId() == applyPhysicsNode) {
				applyPhysicsDetails(prototype);
				return true;
			}
		}
		auto outlinerNode = editorView->getScreenController()->getOutlinerSelection();
		if (StringTools::startsWith(outlinerNode, "physics.boundingvolumes.") == true) {
			auto boundingVolumeIdx = Integer::parse(StringTools::substring(outlinerNode, string("physics.boundingvolumes.").size(), outlinerNode.size()));
			if (node->getId() == "boundingvolume_type") {
				auto boundingVolumeType = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_type"))->getController()->getValue().getString();
				if (boundingVolumeType == "sphere") applyBoundingVolumeSphereDetails(prototype, boundingVolumeIdx); else
				if (boundingVolumeType == "capsule") applyBoundingVolumeCapsuleDetails(prototype, boundingVolumeIdx); else
				if (boundingVolumeType == "obb") applyBoundingVolumeObbDetails(prototype, boundingVolumeIdx); else
				if (boundingVolumeType == "convexmesh") applyBoundingVolumeConvexMeshDetails(prototype, boundingVolumeIdx); else
					view->applyBoundingVolumeNone(prototype, boundingVolumeIdx);
				return true;
			} else {
				for (const auto& applyBoundingVolumeSphereNode: applyBoundingVolumSphereNodes) {
					if (node->getId() == applyBoundingVolumeSphereNode) {
						applyBoundingVolumeSphereDetails(prototype, boundingVolumeIdx);
						return true;
					}
				}
				for (const auto& applyBoundingVolumeCapsuleNode: applyBoundingVolumCapsuleNodes) {
					if (node->getId() == applyBoundingVolumeCapsuleNode) {
						applyBoundingVolumeCapsuleDetails(prototype, boundingVolumeIdx);
						return true;
					}
				}
				for (const auto& applyBoundingVolumeOBBNode: applyBoundingVolumOBBNodes) {
					if (node->getId() == applyBoundingVolumeOBBNode) {
						applyBoundingVolumeObbDetails(prototype, boundingVolumeIdx);
						return true;
					}
				}
			}
		}
	}
	if (node->getId() == tabView->getTabId() + "_tab_button_select") {
		// not yet
	} else
	if (node->getId() == tabView->getTabId() + "_tab_button_translate") {
		view->setGizmoType(Gizmo::GIZMOTYPE_TRANSLATE);
		view->updateGizmo(prototype);
		return true;
	} else
	if (node->getId() == tabView->getTabId() + "_tab_button_rotate") {
		view->setGizmoType(Gizmo::GIZMOTYPE_ROTATE);
		view->updateGizmo(prototype);
		return true;
	} else
	if (node->getId() == tabView->getTabId() + "_tab_button_scale") {
		view->setGizmoType(Gizmo::GIZMOTYPE_SCALE);
		view->updateGizmo(prototype);
		return true;
	} else
	if (node->getId() == tabView->getTabId() + "_tab_button_gizmo") {
		view->setGizmoType(Gizmo::GIZMOTYPE_ALL);
		view->updateGizmo(prototype);
		return true;
	}
	//
	return false;
}

bool PrototypePhysicsSubController::onAction(GUIActionListenerType type, GUIElementNode* node, Prototype* prototype)
{
	if (type == GUIActionListenerType::PERFORMED) {
		if (node->getId() == "boundingvolume_convexmesh_file_open") {
			if (prototype != nullptr) {
				class OnConvexMeshFileOpen: public virtual Action
				{
				public:
					void performAction() override {
						prototypePhysicsSubController->setBoundingVolumeConvexMeshFile(
							boundingVolumeIdx,
							prototypePhysicsSubController->popUps->getFileDialogScreenController()->getPathName() + "/" + prototypePhysicsSubController->popUps->getFileDialogScreenController()->getFileName(),
							prototype
						);
						prototypePhysicsSubController->popUps->getFileDialogScreenController()->close();
					}
					OnConvexMeshFileOpen(PrototypePhysicsSubController* prototypePhysicsSubController, Prototype* prototype, int boundingVolumeIdx):
						prototypePhysicsSubController(prototypePhysicsSubController),
						prototype(prototype),
						boundingVolumeIdx(boundingVolumeIdx) {
						//
					}
				private:
					PrototypePhysicsSubController* prototypePhysicsSubController;
					Prototype* prototype;
					int boundingVolumeIdx;
				};

				auto boundingVolume = prototype->getBoundingVolume(boundingVolumeIdxActivated);
				if (boundingVolume != nullptr) {
					auto fileName = boundingVolume->getConvexMeshFile();
					popUps->getFileDialogScreenController()->show(
						fileName.empty() == false?Tools::getPathName(fileName):string(),
						"Load convex mesh from: ",
						ModelReader::getModelExtensions(),
						Tools::getFileName(fileName),
						false,
						new OnConvexMeshFileOpen(this, prototype, boundingVolumeIdxActivated)
					);
				}
			}
			//
			return true;
		} else
		if (node->getId() == "boundingvolume_convexmesh_file_remove") {
			if (prototype != nullptr) {
				auto boundingVolume = prototype->getBoundingVolume(boundingVolumeIdxActivated);
				if (boundingVolume != nullptr) {
					view->applyBoundingVolumeConvexMeshClear(prototype, boundingVolumeIdxActivated);
					view->removeGizmo();
					setBoundingVolumeDetails(prototype, boundingVolumeIdxActivated);
				}
			}
			//
			return true;
		} else
		if (node->getId() == "boundingvolume_convexmesh_file_browseto") {
			if (prototype != nullptr) {
				auto boundingVolume = prototype->getBoundingVolume(boundingVolumeIdxActivated);
				if (boundingVolume != nullptr) {
					if (boundingVolume->hasConvexMeshData() == true) {
						showInfoPopUp("Browse To", "This bounding volume has embedded convex mesh data");
					} else
					if (boundingVolume->getConvexMeshFile().empty() == false) {
						editorView->getScreenController()->browseTo(boundingVolume->getConvexMeshFile());
					} else {
						showInfoPopUp("Browse To", "Nothing to browse to");
					}
				}
			}
			//
			return true;
		} else
		if (node->getId() == "importconvexmesh_file_open") {
			if (prototype != nullptr) {
				class OnConvexMeshesFileImport: public virtual Action
				{
				public:
					void performAction() override {
						//
						prototypePhysicsSubController->importBoundingVolumeConvexMeshFile(
							prototypePhysicsSubController->popUps->getFileDialogScreenController()->getPathName() + "/" + prototypePhysicsSubController->popUps->getFileDialogScreenController()->getFileName(),
							prototype
						);
						prototypePhysicsSubController->popUps->getFileDialogScreenController()->close();
					}
					OnConvexMeshesFileImport(PrototypePhysicsSubController* prototypePhysicsSubController, Prototype* prototype):
						prototypePhysicsSubController(prototypePhysicsSubController),
						prototype(prototype) {
						//
					}
				private:
					PrototypePhysicsSubController* prototypePhysicsSubController;
					Prototype* prototype;
				};

				popUps->getFileDialogScreenController()->show(
					string(),
					"Import convex meshes from: ",
					ModelReader::getModelExtensions(),
					string(),
					false,
					new OnConvexMeshesFileImport(this, prototype)
				);
			}
			//
			return true;
		} else
		if (node->getId() == "generateconvexmesh_file_open") {
			if (prototype != nullptr) {
				class OnConvexMeshesFileOpen: public virtual Action
				{
				public:
					void performAction() override {
						prototypePhysicsSubController->generateBoundingVolumeConvexMeshFiles(
							prototypePhysicsSubController->popUps->getFileDialogScreenController()->getPathName() + "/" + prototypePhysicsSubController->popUps->getFileDialogScreenController()->getFileName(),
							prototype
						);
						prototypePhysicsSubController->popUps->getFileDialogScreenController()->close();
					}
					OnConvexMeshesFileOpen(PrototypePhysicsSubController* prototypePhysicsSubController, Prototype* prototype):
						prototypePhysicsSubController(prototypePhysicsSubController),
						prototype(prototype) {
						//
					}
				private:
					PrototypePhysicsSubController* prototypePhysicsSubController;
					Prototype* prototype;
				};

				popUps->getFileDialogScreenController()->show(
					string(),
					"Import convex meshes from: ",
					ModelReader::getModelExtensions(),
					string(),
					false,
					new OnConvexMeshesFileOpen(this, prototype)
				);
			}
			//
			return true;
		}
	}
	//
	return false;
}

void PrototypePhysicsSubController::onContextMenuRequest(GUIElementNode* node, int mouseX, int mouseY, Prototype* prototype) {
	if (node->getId() == "selectbox_outliner") {
		auto outlinerNode = editorView->getScreenController()->getOutlinerSelection();
		if (StringTools::startsWith(outlinerNode, "physics.boundingvolumes.") == true) {
			// clear
			popUps->getContextMenuScreenController()->clear();

			// delete
			class OnDeleteAction: public virtual Action
			{
			public:
				void performAction() override {
					auto outlinerNode = prototypePhysicsSubController->editorView->getScreenController()->getOutlinerSelection();
					if (StringTools::startsWith(outlinerNode, "physics.boundingvolumes.") == true) {
						auto boundingVolumeIdx = Integer::parse(StringTools::substring(outlinerNode, string("physics.boundingvolumes.").size(), outlinerNode.size()));
						prototypePhysicsSubController->view->clearModelBoundingVolume(-1);
						for (auto i = 0; i < prototype->getBoundingVolumeCount(); i++) {
							prototypePhysicsSubController->view->clearModelBoundingVolume(i);
						}
						prototype->removeBoundingVolume(boundingVolumeIdx);
						for (auto i = 0; i < prototype->getBoundingVolumeCount(); i++) {
							prototypePhysicsSubController->view->setupModelBoundingVolume(prototype, i);
						}
						prototypePhysicsSubController->editorView->reloadTabOutliner("physics");
					}
				}
				OnDeleteAction(PrototypePhysicsSubController* prototypePhysicsSubController, Prototype* prototype): prototypePhysicsSubController(prototypePhysicsSubController), prototype(prototype) {
				}
			private:
				PrototypePhysicsSubController* prototypePhysicsSubController;
				Prototype* prototype;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Delete", "contextmenu_delete", new OnDeleteAction(this, prototype));

			//
			popUps->getContextMenuScreenController()->show(mouseX, mouseY);
		} else
		if (outlinerNode == "physics") {
			// clear
			popUps->getContextMenuScreenController()->clear();

			// add
			class OnAddBoundingVolumeAction: public virtual Action
			{
			public:
				void performAction() override {
					prototypePhysicsSubController->createBoundingVolume(prototype);
				}
				OnAddBoundingVolumeAction(PrototypePhysicsSubController* prototypePhysicsSubController, Prototype* prototype): prototypePhysicsSubController(prototypePhysicsSubController), prototype(prototype) {
				}
			private:
				PrototypePhysicsSubController* prototypePhysicsSubController;
				Prototype* prototype;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Add Bounding Volume", "contextmenu_add", new OnAddBoundingVolumeAction(this, prototype));

			// import convex meshes from model
			class OnImportConvexMeshesFromModel: public virtual Action
			{
			public:
				void performAction() override {
					prototypePhysicsSubController->setImportConvexMeshFromModelDetails();
				}
				OnImportConvexMeshesFromModel(PrototypePhysicsSubController* prototypePhysicsSubController, Prototype* prototype): prototypePhysicsSubController(prototypePhysicsSubController) {
				}
			private:
				PrototypePhysicsSubController* prototypePhysicsSubController;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Import convex meshes", "contextmenu_importconvexmeshfrommodel", new OnImportConvexMeshesFromModel(this, prototype));

			// generate convex meshes from model
			class OnGenerateConvexMeshesFromModel: public virtual Action
			{
			public:
				void performAction() override {
					prototypePhysicsSubController->setGenerateConvexMeshFromModelDetails();
				}
				OnGenerateConvexMeshesFromModel(PrototypePhysicsSubController* prototypePhysicsSubController, Prototype* prototype): prototypePhysicsSubController(prototypePhysicsSubController), prototype(prototype) {
				}
			private:
				PrototypePhysicsSubController* prototypePhysicsSubController;
				Prototype* prototype;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Generate convex meshes", "contextmenu_generateconvexmeshfrommodel", new OnGenerateConvexMeshesFromModel(this, prototype));

			// delete convex meshes
			class OnDeleteConvexMeshesFromModel: public virtual Action
			{
			public:
				void performAction() override {
					for (auto i = 0; i < prototype->getBoundingVolumeCount(); i++) {
						prototypePhysicsSubController->view->clearModelBoundingVolume(i);
					}
					GenerateConvexMeshes::removeConvexMeshes(prototype);
					prototypePhysicsSubController->editorView->reloadTabOutliner("physics");
					prototypePhysicsSubController->updateDetails(prototype, "physics");
					for (auto i = 0; i < prototype->getBoundingVolumeCount(); i++) {
						prototypePhysicsSubController->view->setupModelBoundingVolume(prototype, i);
					}
				}
				OnDeleteConvexMeshesFromModel(PrototypePhysicsSubController* prototypePhysicsSubController, Prototype* prototype): prototypePhysicsSubController(prototypePhysicsSubController), prototype(prototype) {
				}
			private:
				PrototypePhysicsSubController* prototypePhysicsSubController;
				Prototype* prototype;
			};
			popUps->getContextMenuScreenController()->addMenuItem("Delete convex meshes", "contextmenu_deleteconvexmeshes", new OnDeleteConvexMeshesFromModel(this, prototype));

			//
			popUps->getContextMenuScreenController()->show(mouseX, mouseY);
		}
	}
}

void PrototypePhysicsSubController::enableTools() {
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(tabView->getTabId() + "_tab_toolbar"))->getActiveConditions().add("tools");
}

void PrototypePhysicsSubController::disableTools() {
	required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById(tabView->getTabId() + "_tab_toolbar"))->getActiveConditions().remove("tools");
}

void PrototypePhysicsSubController::setBoundingVolumeConvexMeshFile(int boundingVolumeIdx, const string& fileName, Prototype* prototype) {
	try {
		view->applyBoundingVolumeConvexMesh(
			prototype,
			boundingVolumeIdx,
			fileName
		);
	} catch (Exception& exception) {
		Console::printLine("PrototypePhysicsSubController::setBoundingVolumeConvexMeshFile(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
	view->removeGizmo();
	setBoundingVolumeDetails(prototype, boundingVolumeIdx);
}

void PrototypePhysicsSubController::importBoundingVolumeConvexMeshFile(const string& fileName, Prototype* prototype) {
	//
	for (auto i = 0; i < prototype->getBoundingVolumeCount(); i++) {
		view->clearModelBoundingVolume(i);
	}

	//
	try {
		vector<vector<uint8_t>> convexMeshTMsData;
		if (GenerateConvexMeshes::generateConvexMeshes(
				prototype,
				GenerateConvexMeshes::MODE_IMPORT,
				popUps,
				Tools::getPathName(fileName),
				Tools::getFileName(fileName),
				convexMeshTMsData
			) == true) {
			GenerateConvexMeshes::removeConvexMeshes(prototype);
			for (auto& convexMeshTMData: convexMeshTMsData) {
				//
				try {
					auto prototypeBoundingVolume = make_unique<PrototypeBoundingVolume>(prototype);
					prototypeBoundingVolume->setupConvexMesh(convexMeshTMData);
					prototype->addBoundingVolume(prototypeBoundingVolume.release());
				} catch (Exception& exception) {
					Console::printLine("PrototypePhysicsSubController::importBoundingVolumeConvexMeshFile(): An error occurred: " + string(exception.what()));
				}
			}
		}
	} catch (Exception& exception) {
		Console::printLine("PrototypePhysicsSubController::importBoundingVolumeConvexMeshFile(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}
	editorView->reloadTabOutliner("physics");

	//
	for (auto i = 0; i < prototype->getBoundingVolumeCount(); i++) {
		view->setupModelBoundingVolume(prototype, i);
	}
}

void PrototypePhysicsSubController::generateBoundingVolumeConvexMeshFiles(const string& fileName, Prototype* prototype) {
	for (auto i = 0; i < prototype->getBoundingVolumeCount(); i++) {
		view->clearModelBoundingVolume(i);
	}

	//
	try {
		VHACD::IVHACD::Parameters parameters;
		parameters.m_resolution = Integer::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("generateconvexmesh_resolution"))->getController()->getValue().getString());
		parameters.m_minimumVolumePercentErrorAllowed = Float::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("generateconvexmesh_minvolumepercent"))->getController()->getValue().getString());
		parameters.m_maxConvexHulls = Integer::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("generateconvexmesh_maxconvexhulls"))->getController()->getValue().getString());
		parameters.m_maxNumVerticesPerCH = Integer::parse(required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("generateconvexmesh_maxverticesperch"))->getController()->getValue().getString());

		vector<vector<uint8_t>> convexMeshTMsData;
		if (GenerateConvexMeshes::generateConvexMeshes(
				prototype,
				GenerateConvexMeshes::MODE_GENERATE,
				popUps,
				Tools::getPathName(fileName),
				Tools::getFileName(fileName),
				convexMeshTMsData,
				parameters
			) == true) {
			GenerateConvexMeshes::removeConvexMeshes(prototype);
			for (auto& convexMeshTMData: convexMeshTMsData) {
				//
				try {
					auto prototypeBoundingVolume = make_unique<PrototypeBoundingVolume>(prototype);
					prototypeBoundingVolume->setupConvexMesh(convexMeshTMData);
					prototype->addBoundingVolume(prototypeBoundingVolume.release());
				} catch (Exception& exception) {
					Console::printLine("PrototypePhysicsSubController::generateBoundingVolumeConvexMeshFiles(): An error occurred: " + string(exception.what()));
				}
			}
		}
	} catch (Exception& exception) {
		Console::printLine("generateBoundingVolumeConvexMeshFiles::generateBoundingVolumeConvexMeshFiles(): An error occurred: " + string(exception.what()));
		showInfoPopUp("Warning", string(exception.what()));
	}


	editorView->reloadTabOutliner("physics");

	//
	for (auto i = 0; i < prototype->getBoundingVolumeCount(); i++) {
		view->setupModelBoundingVolume(prototype, i);
	}
}

bool PrototypePhysicsSubController::onDrop(const string& payload, int mouseX, int mouseY, Prototype* prototype) {
	if (StringTools::startsWith(payload, "file:") == false) {
		return false;
	} else {
		auto fileName = StringTools::substring(payload, string("file:").size());
		if (editorView->getScreenController()->isDropOnNode(mouseX, mouseY, "boundingvolume_convexmesh_file") == true) {
			if (Tools::hasFileExtension(fileName, ModelReader::getModelExtensions()) == false) {
				showInfoPopUp("Warning", "You can not drop this file here. Allowed file extensions are " + Tools::enumerateFileExtensions(ModelReader::getModelExtensions()));
			} else {
				setBoundingVolumeConvexMeshFile(boundingVolumeIdxActivated, fileName, prototype);
			}
			return true;
		} else
		if (editorView->getScreenController()->isDropOnNode(mouseX, mouseY, "importconvexmesh_file") == true) {
			if (Tools::hasFileExtension(fileName, ModelReader::getModelExtensions()) == false) {
				showInfoPopUp("Warning", "You can not drop this file here. Allowed file extensions are " + Tools::enumerateFileExtensions(ModelReader::getModelExtensions()));
			} else {
				importBoundingVolumeConvexMeshFile(fileName, prototype);
			}
			return true;
		} else
		if (editorView->getScreenController()->isDropOnNode(mouseX, mouseY, "generateconvexmesh_file") == true) {
			if (Tools::hasFileExtension(fileName, ModelReader::getModelExtensions()) == false) {
				showInfoPopUp("Warning", "You can not drop this file here. Allowed file extensions are " + Tools::enumerateFileExtensions(ModelReader::getModelExtensions()));
			} else {
				generateBoundingVolumeConvexMeshFiles(fileName, prototype);
			}
			return true;
		} else {
			return false;
		}
	}
}
