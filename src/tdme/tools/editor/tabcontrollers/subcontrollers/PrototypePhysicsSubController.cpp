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
#include <tdme/utilities/Action.h>
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
using tdme::utilities::Action;
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

PrototypePhysicsSubController::PrototypePhysicsSubController(EditorView* editorView, Engine* engine, FileDialogPath* modelPath, bool isModelBoundingVolumes, int maxBoundingVolumeCount, int32_t boundingVolumeTypeMask)
{
	this->editorView = editorView;
	this->modelPath = modelPath;
	this->view = new PrototypePhysicsSubView(engine, this, editorView->getPopUps(), maxBoundingVolumeCount, boundingVolumeTypeMask);
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

void PrototypePhysicsSubController::updateDetails(Prototype* prototype, const string& outlinerNode) {
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
		if (node->getId() == "boundingvolume_type") {
			auto boundingVolumeType = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("boundingvolume_type"))->getController()->getValue().getString();
			if (boundingVolumeType == "sphere") applyBoundingVolumeSphereDetails(prototype, boundingVolumeIdx); else
			if (boundingVolumeType == "capsule") applyBoundingVolumeCapsuleDetails(prototype, boundingVolumeIdx); else
			if (boundingVolumeType == "obb") applyBoundingVolumeObbDetails(prototype, boundingVolumeIdx); else
				view->applyBoundingVolumeNone(prototype, boundingVolumeIdx);
		} else {
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
	}
}

void PrototypePhysicsSubController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node, Prototype* prototype)
{
	if (type == GUIActionListenerType::PERFORMED) {
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

void PrototypePhysicsSubController::onContextMenuRequested(GUIElementNode* node, int mouseX, int mouseY, Prototype* prototype) {
	Console::println("PrototypePhysicsSubController::onContextMenuRequested(): " + node->getId());
}
