#include <tdme/tools/editor/misc/Gizmo.h>

#include <tdme/tdme.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/primitives/LineSegment.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/Frustum.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/Transformations.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/StringTools.h>

using tdme::tools::editor::misc::Gizmo;

using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::primitives::LineSegment;
using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::Frustum;
using tdme::engine::Object3D;
using tdme::engine::Transformations;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::tools::editor::misc::Tools;
using tdme::utilities::Console;
using tdme::utilities::StringTools;

Gizmo::Gizmo(Engine* engine, const string& id, int32_t gizmoTypeMask)
{
	this->engine = engine;
	this->id = id;
	this->gizmoTypeMask = gizmoTypeMask;
	setGizmoType(GIZMOTYPE_ALL);
	setGizmoMode(GIZMOMODE_NONE);
	gizmoMovementLastResultAvailable = false;
	gizmoRotationLastResultAvailable = false;
}

Gizmo::~Gizmo() {
}

void Gizmo::updateGizmo(const Vector3& gizmoCenter, const Transformations& transformations) {
	gizmoMovementLastResultAvailable = false;
	gizmoRotationLastResultAvailable = false;
	this->gizmoTranslation = gizmoCenter;
	Object3D* gizmoEntity = nullptr;
	auto scale = 150.0f;
	Vector4 orthogonalGizmoCenterNDC = engine->getCamera()->getModelViewProjectionMatrix().multiply(Vector4(gizmoCenter, 1.0f));
	orthogonalGizmoCenterNDC.scale(1.0f / orthogonalGizmoCenterNDC.getW());
	orthogonalGizmoTranslation.setX(orthogonalGizmoCenterNDC.getX() * (engine->getWidth() * 0.5f));
	orthogonalGizmoTranslation.setY(orthogonalGizmoCenterNDC.getY() * (engine->getHeight() * 0.5f));
	orthogonalGizmoTranslation.setZ(-200.0f);
	switch (getGizmoType()) {
		case GIZMOTYPE_ALL:
			{
				if ((gizmoTypeMask & GIZMOTYPE_TRANSLATE) == GIZMOTYPE_TRANSLATE &&
					(gizmoTypeMask & GIZMOTYPE_ROTATE) == GIZMOTYPE_ROTATE &&
					(gizmoTypeMask & GIZMOTYPE_SCALE) == GIZMOTYPE_SCALE) {
					engine->removeEntity(id + ".tdme.gizmo.translation");
					engine->removeEntity(id + ".tdme.gizmo.scale");
					gizmoEntity = dynamic_cast<Object3D*>(engine->getEntity(id + ".tdme.gizmo.all"));
					if (gizmoEntity == nullptr) engine->addEntity(gizmoEntity = new Object3D(id + ".tdme.gizmo.all", Tools::getGizmoAll()));
					gizmoEntity->setPickable(true);
					gizmoEntity->setFrustumCulling(false);
					gizmoEntity->setRenderPass(Entity::RENDERPASS_GIZMO);
					gizmoEntity->setTranslation(orthogonalGizmoTranslation);
					gizmoEntity->setScale(Vector3(scale, scale, scale));
					gizmoEntity->update();
					gizmoEntity = dynamic_cast<Object3D*>(engine->getEntity(id + ".tdme.gizmo.rotations"));
					if (gizmoEntity == nullptr) engine->addEntity(gizmoEntity = new Object3D(id + ".tdme.gizmo.rotations", Tools::getGizmoRotations()));
					gizmoEntity->setPickable(true);
					gizmoEntity->setFrustumCulling(false);
					gizmoEntity->setRenderPass(Entity::RENDERPASS_GIZMO);
					gizmoEntity->setTranslation(orthogonalGizmoTranslation);
					gizmoEntity->setScale(Vector3(scale, scale, scale));
					gizmoEntity->update();
				} else
				if ((gizmoTypeMask & GIZMOTYPE_TRANSLATE) == GIZMOTYPE_TRANSLATE &&
					(gizmoTypeMask & GIZMOTYPE_SCALE) == GIZMOTYPE_SCALE) {
					engine->removeEntity(id + ".tdme.gizmo.translation");
					engine->removeEntity(id + ".tdme.gizmo.rotations");
					engine->removeEntity(id + ".tdme.gizmo.scale");
					gizmoEntity = dynamic_cast<Object3D*>(engine->getEntity(id + ".tdme.gizmo.all"));
					if (gizmoEntity == nullptr) engine->addEntity(gizmoEntity = new Object3D(id + ".tdme.gizmo.all", Tools::getGizmoTranslationScale()));
					gizmoEntity->setPickable(true);
					gizmoEntity->setFrustumCulling(false);
					gizmoEntity->setRenderPass(Entity::RENDERPASS_GIZMO);
					gizmoEntity->setTranslation(orthogonalGizmoTranslation);
					gizmoEntity->setScale(Vector3(scale, scale, scale));
					gizmoEntity->update();
				} else {
					if ((gizmoTypeMask & GIZMOTYPE_TRANSLATE) == GIZMOTYPE_TRANSLATE) {
						engine->removeEntity(id + ".tdme.gizmo.all");
						engine->removeEntity(id + ".tdme.gizmo.rotations");
						engine->removeEntity(id + ".tdme.gizmo.scale");
						gizmoEntity = dynamic_cast<Object3D*>(engine->getEntity(id + ".tdme.gizmo.translation"));
						if (gizmoEntity == nullptr) engine->addEntity(gizmoEntity = new Object3D(id + ".tdme.gizmo.translation", Tools::getGizmoTranslation()));
						gizmoEntity->setPickable(true);
						gizmoEntity->setFrustumCulling(false);
						gizmoEntity->setRenderPass(Entity::RENDERPASS_GIZMO);
						gizmoEntity->setTranslation(orthogonalGizmoTranslation);
						gizmoEntity->setScale(Vector3(scale, scale, scale));
						gizmoEntity->update();
					}
					if ((gizmoTypeMask & GIZMOTYPE_ROTATE) == GIZMOTYPE_ROTATE) {
						engine->removeEntity(id + ".tdme.gizmo.all");
						engine->removeEntity(id + ".tdme.gizmo.translation");
						engine->removeEntity(id + ".tdme.gizmo.scale");
						gizmoEntity = dynamic_cast<Object3D*>(engine->getEntity(id + ".tdme.gizmo.rotations"));
						if (gizmoEntity == nullptr) engine->addEntity(gizmoEntity = new Object3D(id + ".tdme.gizmo.rotations", Tools::getGizmoRotations()));
						gizmoEntity->setPickable(true);
						gizmoEntity->setRenderPass(Entity::RENDERPASS_GIZMO);
						gizmoEntity->setTranslation(orthogonalGizmoTranslation);
						gizmoEntity->setScale(Vector3(scale, scale, scale));
						gizmoEntity->update();
					}
					if ((gizmoTypeMask & GIZMOTYPE_SCALE) == GIZMOTYPE_SCALE) {
						engine->removeEntity(id + ".tdme.gizmo.all");
						engine->removeEntity(id + ".tdme.gizmo.translation");
						engine->removeEntity(id + ".tdme.gizmo.rotations");
						gizmoEntity = dynamic_cast<Object3D*>(engine->getEntity(id + ".tdme.gizmo.scale"));
						if (gizmoEntity == nullptr) engine->addEntity(gizmoEntity = new Object3D(id + ".tdme.gizmo.scale", Tools::getGizmoScale()));
						gizmoEntity->setPickable(true);
						gizmoEntity->setFrustumCulling(false);
						gizmoEntity->setRenderPass(Entity::RENDERPASS_GIZMO);
						gizmoEntity->setTranslation(orthogonalGizmoTranslation);
						gizmoEntity->setScale(Vector3(scale, scale, scale));
						gizmoEntity->update();
					}
				}
				break;
			}
		case GIZMOTYPE_TRANSLATE:
			{
				engine->removeEntity(id + ".tdme.gizmo.all");
				engine->removeEntity(id + ".tdme.gizmo.scale");
				engine->removeEntity(id + ".tdme.gizmo.rotations");
				gizmoEntity = dynamic_cast<Object3D*>(engine->getEntity(id + ".tdme.gizmo.translation"));
				if (gizmoEntity == nullptr) engine->addEntity(gizmoEntity = new Object3D(id + ".tdme.gizmo.translation", Tools::getGizmoTranslation()));
				gizmoEntity->setPickable(true);
				gizmoEntity->setFrustumCulling(false);
				gizmoEntity->setRenderPass(Entity::RENDERPASS_GIZMO);
				gizmoEntity->setTranslation(orthogonalGizmoTranslation);
				gizmoEntity->setScale(Vector3(scale, scale, scale));
				gizmoEntity->update();
				break;
			}
		case GIZMOTYPE_ROTATE:
			{
				engine->removeEntity(id + ".tdme.gizmo.all");
				engine->removeEntity(id + ".tdme.gizmo.translation");
				engine->removeEntity(id + ".tdme.gizmo.scale");
				gizmoEntity = dynamic_cast<Object3D*>(engine->getEntity(id + ".tdme.gizmo.rotations"));
				if (gizmoEntity == nullptr) engine->addEntity(gizmoEntity = new Object3D(id + ".tdme.gizmo.rotations", Tools::getGizmoRotations()));
				gizmoEntity->setPickable(true);
				gizmoEntity->setFrustumCulling(false);
				gizmoEntity->setRenderPass(Entity::RENDERPASS_GIZMO);
				gizmoEntity->setTranslation(orthogonalGizmoTranslation);
				gizmoEntity->setScale(Vector3(scale, scale, scale));
				gizmoEntity->update();
				break;
			}
		case GIZMOTYPE_SCALE:
			{
				engine->removeEntity(id + ".tdme.gizmo.all");
				engine->removeEntity(id + ".tdme.gizmo.translation");
				engine->removeEntity(id + ".tdme.gizmo.rotations");
				gizmoEntity = dynamic_cast<Object3D*>(engine->getEntity(id + ".tdme.gizmo.scale"));
				if (gizmoEntity == nullptr) engine->addEntity(gizmoEntity = new Object3D(id + ".tdme.gizmo.scale", Tools::getGizmoScale()));
				gizmoEntity->setPickable(true);
				gizmoEntity->setFrustumCulling(false);
				gizmoEntity->setRenderPass(Entity::RENDERPASS_GIZMO);
				gizmoEntity->setTranslation(orthogonalGizmoTranslation);
				gizmoEntity->setScale(Vector3(scale, scale, scale));
				gizmoEntity->update();
				break;
			}
		case GIZMOTYPE_NONE:
			break;
	}
	setGizmoRotation(transformations);
}

Object3D* Gizmo::getGizmoObject3D() {
	auto gizmoEntity = dynamic_cast<Object3D*>(engine->getEntity(id + ".tdme.gizmo.all"));
	if (gizmoEntity == nullptr) gizmoEntity = dynamic_cast<Object3D*>(engine->getEntity(id + ".tdme.gizmo.translation"));
	if (gizmoEntity == nullptr) gizmoEntity = dynamic_cast<Object3D*>(engine->getEntity(id + ".tdme.gizmo.rotations"));
	if (gizmoEntity == nullptr) gizmoEntity = dynamic_cast<Object3D*>(engine->getEntity(id + ".tdme.gizmo.scale"));
	return gizmoEntity;
}

void Gizmo::removeGizmo() {
	engine->removeEntity(id + ".tdme.gizmo.all");
	engine->removeEntity(id + ".tdme.gizmo.translation");
	engine->removeEntity(id + ".tdme.gizmo.scale");
	engine->removeEntity(id + ".tdme.gizmo.rotations");
	setGizmoMode(GIZMOMODE_NONE);
}

bool Gizmo::determineGizmoMovement(int mouseX, int mouseY, vector<Vector3> vertices, Vector3& deltaMovement, float& direction) {
	Vector3 tmpVector3a;
	Vector3 tmpVector3b;
	Vector3 tmpVector3e;
	engine->computeWorldCoordinateByMousePosition(mouseX, mouseY, 0.0f, tmpVector3a);
	engine->computeWorldCoordinateByMousePosition(mouseX, mouseY, 1.0f, tmpVector3b);
	for (auto& vertex: vertices) {
		vertex.add(gizmoTranslation);
	}
	if (LineSegment::doesLineSegmentCollideWithTriangle(
		vertices[0],
		vertices[1],
		vertices[2],
		tmpVector3a,
		tmpVector3b,
		tmpVector3e) == true ||
		LineSegment::doesLineSegmentCollideWithTriangle(
		vertices[2],
		vertices[3],
		vertices[0],
		tmpVector3a,
		tmpVector3b,
		tmpVector3e) == true
	) {
		auto success = gizmoMovementLastResultAvailable == true;
		if (success == true) {
			direction = 1.0f;
			if (gizmoMovementLastResult.clone().sub(gizmoTranslation).computeLengthSquared() > tmpVector3e.clone().sub(gizmoTranslation).computeLengthSquared()) direction = -1.0f;
			deltaMovement = tmpVector3e.clone().sub(gizmoMovementLastResult);
		}
		gizmoMovementLastResult = tmpVector3e;
		gizmoMovementLastResultAvailable = true;
		return success;
	}
	return false;
}

bool Gizmo::determineGizmoRotation(int mouseX, int mouseY, vector<Vector3> vertices, const Vector3& planeNormal, float& deltaRotation) {
	Vector3 tmpVector3a;
	Vector3 tmpVector3b;
	Vector3 tmpVector3e;
	engine->computeWorldCoordinateByMousePosition(mouseX, mouseY, 0.0f, tmpVector3a);
	engine->computeWorldCoordinateByMousePosition(mouseX, mouseY, 1.0f, tmpVector3b);
	for (auto& vertex: vertices) {
		vertex.add(gizmoTranslation);
	}
	if (LineSegment::doesLineSegmentCollideWithTriangle(
		vertices[0],
		vertices[1],
		vertices[2],
		tmpVector3a,
		tmpVector3b,
		tmpVector3e) == true ||
		LineSegment::doesLineSegmentCollideWithTriangle(
		vertices[2],
		vertices[3],
		vertices[0],
		tmpVector3a,
		tmpVector3b,
		tmpVector3e) == true
	) {
		auto success = gizmoRotationLastResultAvailable == true;
		if (success == true) {
			auto a = tmpVector3e.clone().sub(gizmoTranslation).normalize();
			auto b = gizmoRotationLastResult.clone().sub(gizmoTranslation).normalize();
			deltaRotation = Vector3::computeAngle(a, b, planeNormal);
			if (deltaRotation > 180.0f) deltaRotation = deltaRotation - 360.0f;
		}
		gizmoRotationLastResult = tmpVector3e;
		gizmoRotationLastResultAvailable = true;
		return success;
	}
	return false;
}

bool Gizmo::determineGizmoDeltaTransformations(int mouseLastX, int mouseLastY, int mouseX, int mouseY, Vector3& deltaTranslation, Vector3& deltaRotation, Vector3& deltaScale) {
	if (getGizmoMode() == GIZMOMODE_NONE) return false;
	auto deltaX = mouseX - mouseLastX;
	auto deltaY = mouseY - mouseLastY;
	deltaTranslation.set(0.0f, 0.0f, 0.0f);
	deltaRotation.set(0.0f, 0.0f, 0.0f);
	deltaScale.set(1.0f, 1.0f, 1.0f);
	Vector3 gizmoDeltaMovement;
	const vector<Vector3> planeXY =
		{
			Vector3(-5000.0f, -5000.0f, 0.0f),
			Vector3(-5000.0f, 5000.0f, 0.0f),
			Vector3(5000.0f, 5000.0f, 0.0f),
			Vector3(5000.0f, -5000.0f, 0.0f)
		};
	const vector<Vector3> planeXZ =
		{
			Vector3(-5000.0f, 0.0f, -5000.0f),
			Vector3(-5000.0f, 0.0f, 5000.0f),
			Vector3(5000.0f, 0.0f, 5000.0f),
			Vector3(5000.0f, 0.0f, -5000.0f)
		};
	const vector<Vector3> planeYZ =
		{
			Vector3(0.0f, -5000.0f, -5000.0f),
			Vector3(0.0f, -5000.0f, 5000.0f),
			Vector3(0.0f, 5000.0f, 5000.0f),
			Vector3(0.0f, 5000.0f, -5000.0f)
		};
	switch (getGizmoMode()) {
		case GIZMOMODE_TRANSLATE_X:
			{
				// XXX
				vector<Vector3> vertices = planeXZ;
				float direction;
				if (determineGizmoMovement(mouseX, mouseY, vertices, gizmoDeltaMovement, direction) == true) {
					deltaTranslation.setX(gizmoDeltaMovement.getX());
				}
				break;
			}
		case GIZMOMODE_TRANSLATE_Y:
			{
				// XXX
				vector<Vector3> vertices =
					(Math::abs(engine->getCamera()->getForwardVector().getZ()) >= Math::abs(engine->getCamera()->getForwardVector().getX()) || Math::abs(engine->getCamera()->getForwardVector().getZ() - engine->getCamera()->getForwardVector().getX()) < 0.01f) &&
					(Math::abs(engine->getCamera()->getForwardVector().getZ()) >= Math::abs(engine->getCamera()->getForwardVector().getY()) || Math::abs(engine->getCamera()->getForwardVector().getZ() - engine->getCamera()->getForwardVector().getY()) < 0.01f)?
						planeXY:
						planeYZ;
				float direction;
				if (determineGizmoMovement(mouseX, mouseY, vertices, gizmoDeltaMovement, direction) == true) {
					deltaTranslation.setY(gizmoDeltaMovement.getY());
				}
				break;
			}
		case GIZMOMODE_TRANSLATE_Z:
			{
				// XXX
				vector<Vector3> vertices = planeXZ;
				float direction;
				if (determineGizmoMovement(mouseX, mouseY, vertices, gizmoDeltaMovement, direction) == true) {
					deltaTranslation.setZ(gizmoDeltaMovement.getZ());
				}
				break;
			}
		case GIZMOMODE_TRANSLATEPLANE_X:
			{
				vector<Vector3> vertices = planeYZ;
				float direction;
				if (determineGizmoMovement(mouseX, mouseY, vertices, gizmoDeltaMovement, direction) == true) {
					deltaTranslation.setY(gizmoDeltaMovement.getY());
					deltaTranslation.setZ(gizmoDeltaMovement.getZ());
				}
				break;
			}
		case GIZMOMODE_TRANSLATEPLANE_Y:
			{
				vector<Vector3> vertices = planeXZ;
				float direction;
				if (determineGizmoMovement(mouseX, mouseY, vertices, gizmoDeltaMovement, direction) == true) {
					deltaTranslation.setX(gizmoDeltaMovement.getX());
					deltaTranslation.setZ(gizmoDeltaMovement.getZ());
				}
				break;
			}
		case GIZMOMODE_TRANSLATEPLANE_Z:
			{
				vector<Vector3> vertices = planeXY;
				float direction;
				if (determineGizmoMovement(mouseX, mouseY, vertices, gizmoDeltaMovement, direction) == true) {
					deltaTranslation.setX(gizmoDeltaMovement.getX());
					deltaTranslation.setY(gizmoDeltaMovement.getY());
				}
				break;
			}
		case GIZMOMODE_SCALE_X:
			{
				vector<Vector3> vertices = planeXZ;
				float direction;
				if (determineGizmoMovement(mouseX, mouseY, vertices, gizmoDeltaMovement, direction) == true) {
					deltaScale.add(Vector3(direction * (gizmoDeltaMovement.getX() * Math::sign(gizmoDeltaMovement.getX())), 0.0f, 0.0f));
				}
				break;
			}
		case GIZMOMODE_SCALE_Y:
			{
				vector<Vector3> vertices =
					(Math::abs(engine->getCamera()->getForwardVector().getZ()) >= Math::abs(engine->getCamera()->getForwardVector().getX()) || Math::abs(engine->getCamera()->getForwardVector().getZ() - engine->getCamera()->getForwardVector().getX()) < 0.01f) &&
					(Math::abs(engine->getCamera()->getForwardVector().getZ()) >= Math::abs(engine->getCamera()->getForwardVector().getY()) || Math::abs(engine->getCamera()->getForwardVector().getZ() - engine->getCamera()->getForwardVector().getY()) < 0.01f)?
						planeXY:
						planeYZ;
				float direction;
				if (determineGizmoMovement(mouseX, mouseY, vertices, gizmoDeltaMovement, direction) == true) {
					deltaScale.add(Vector3(0.0f, direction * (gizmoDeltaMovement.getY() * Math::sign(gizmoDeltaMovement.getY())), 0.0f));
				}
				break;
			}
		case GIZMOMODE_SCALE_Z:
			{
				vector<Vector3> vertices = planeXZ;
				float direction;
				if (determineGizmoMovement(mouseX, mouseY, vertices, gizmoDeltaMovement, direction) == true) {
					deltaScale.add(Vector3(0.0f, 0.0f, direction * (gizmoDeltaMovement.getZ() * Math::sign(gizmoDeltaMovement.getZ()))));
				}
				break;
			}
		case GIZMOMODE_SCALEPLANE_X:
			{
				vector<Vector3> vertices = planeYZ;
				float direction;
				if (determineGizmoMovement(mouseX, mouseY, vertices, gizmoDeltaMovement, direction) == true) {
					deltaScale.add(Vector3(0.0f, gizmoDeltaMovement.getY(), gizmoDeltaMovement.getZ()));
				}
				break;
			}
		case GIZMOMODE_SCALEPLANE_Y:
			{
				vector<Vector3> vertices = planeXZ;
				float direction;
				if (determineGizmoMovement(mouseX, mouseY, vertices, gizmoDeltaMovement, direction) == true) {
					deltaScale.add(Vector3(gizmoDeltaMovement.getX(), 0.0f, gizmoDeltaMovement.getZ()));
				}
				break;
			}
		case GIZMOMODE_SCALEPLANE_Z:
			{
				vector<Vector3> vertices = planeXY;
				float direction;
				if (determineGizmoMovement(mouseX, mouseY, vertices, gizmoDeltaMovement, direction) == true) {
					deltaScale.add(Vector3(gizmoDeltaMovement.getX(), gizmoDeltaMovement.getY(), 0.0f));
				}
				break;
			}
		case GIZMOMODE_ROTATE_X:
			{
				vector<Vector3> vertices = planeYZ;
				float gizmoDeltaRotation = 0.0f;
				for (auto& vertex: vertices) {
					vertex = rotationsMatrix.multiply(vertex);
				}
				auto planeNormal = rotationsMatrix.multiply(Vector3(-1.0f, 0.0f, 0.0f)).normalize();
				if (determineGizmoRotation(mouseX, mouseY, vertices, planeNormal, gizmoDeltaRotation) == true) {
					deltaRotation.setX(gizmoDeltaRotation);
				}
			}
			break;
		case GIZMOMODE_ROTATE_Y:
			{
				vector<Vector3> vertices = planeXZ;
				float gizmoDeltaRotation = 0.0f;
				for (auto& vertex: vertices) {
					vertex = rotationsMatrix.multiply(vertex);
				}
				auto planeNormal = rotationsMatrix.multiply(Vector3(0.0f, -1.0f, 0.0f)).normalize();
				if (determineGizmoRotation(mouseX, mouseY, vertices, planeNormal, gizmoDeltaRotation) == true) {
					deltaRotation.setY(gizmoDeltaRotation);
				}
			}
			break;
		case GIZMOMODE_ROTATE_Z:
			{
				vector<Vector3> vertices = planeXY;
				float gizmoDeltaRotation = 0.0f;
				for (auto& vertex: vertices) {
					vertex = rotationsMatrix.multiply(vertex);
				}
				auto planeNormal = rotationsMatrix.multiply(Vector3(0.0f, 0.0f, -1.0f)).normalize();
				if (determineGizmoRotation(mouseX, mouseY, vertices, planeNormal, gizmoDeltaRotation) == true) {
					deltaRotation.setZ(gizmoDeltaRotation);
				}
			}
			break;
		case GIZMOMODE_NONE:
			// no op, satisfy the compiler
			break;
	}
	return true;
}

bool Gizmo::determineGizmoMode(Entity* selectedEntity, Node* selectedEntityNode) {
	if (selectedEntity != nullptr &&
		StringTools::startsWith(selectedEntity->getId(), id + ".tdme.gizmo.") == true && selectedEntityNode != nullptr) {
		auto selectedEntityNodeId = selectedEntityNode->getId();
		if (StringTools::startsWith(selectedEntityNodeId, "all_") == true) selectedEntityNodeId = StringTools::substring(selectedEntityNodeId, 4);
		if (selectedEntityNodeId == "translate_x") setGizmoMode(GIZMOMODE_TRANSLATE_X); else
		if (selectedEntityNodeId == "translate_y") setGizmoMode(GIZMOMODE_TRANSLATE_Y); else
		if (selectedEntityNodeId == "translate_z") setGizmoMode(GIZMOMODE_TRANSLATE_Z); else
		if (selectedEntityNodeId == "translate_x_plane") setGizmoMode(GIZMOMODE_TRANSLATEPLANE_X); else
		if (selectedEntityNodeId == "translate_y_plane") setGizmoMode(GIZMOMODE_TRANSLATEPLANE_Z); else
		if (selectedEntityNodeId == "translate_z_plane") setGizmoMode(GIZMOMODE_TRANSLATEPLANE_Y); else
		if (selectedEntityNodeId == "rotate_x") setGizmoMode(GIZMOMODE_ROTATE_X); else
		if (selectedEntityNodeId == "rotate_y") setGizmoMode(GIZMOMODE_ROTATE_Y); else
		if (selectedEntityNodeId == "rotate_z") setGizmoMode(GIZMOMODE_ROTATE_Z); else
		if (selectedEntityNodeId == "scale_x") setGizmoMode(GIZMOMODE_SCALE_X); else
		if (selectedEntityNodeId == "scale_y") setGizmoMode(GIZMOMODE_SCALE_Y); else
		if (selectedEntityNodeId == "scale_z") setGizmoMode(GIZMOMODE_SCALE_Z); else
		if (selectedEntityNodeId == "scale_x_plane") setGizmoMode(GIZMOMODE_SCALEPLANE_X); else
		if (selectedEntityNodeId == "scale_y_plane") setGizmoMode(GIZMOMODE_SCALEPLANE_Y); else
		if (selectedEntityNodeId == "scale_z_plane") setGizmoMode(GIZMOMODE_SCALEPLANE_Z); else
			setGizmoMode(GIZMOMODE_NONE);
		return true;
	}
	return false;
}

void Gizmo::setGizmoRotation(const Transformations& transformations) {
	auto cameraMatrixEuler = engine->getCamera()->getCameraMatrix().computeEulerAngles();
	Transformations cameraRotationTransformations;
	cameraRotationTransformations.addRotation(Vector3(0.0f, 0.0f, 1.0f), cameraMatrixEuler.getZ());
	cameraRotationTransformations.addRotation(Vector3(0.0f, 1.0f, 0.0f), cameraMatrixEuler.getY());
	cameraRotationTransformations.addRotation(Vector3(1.0f, 0.0f, 0.0f), cameraMatrixEuler.getX());
	cameraRotationTransformations.update();
	//
	rotationsMatrix = transformations.getRotationsQuaternion().computeMatrix();
	{
		auto gizmoEntity = dynamic_cast<Object3D*>(engine->getEntity(id + ".tdme.gizmo.translation"));
		if (gizmoEntity != nullptr) {
			cameraRotationTransformations.setTranslation(gizmoEntity->getTranslation());
			cameraRotationTransformations.setScale(gizmoEntity->getScale());
			cameraRotationTransformations.update();
			gizmoEntity->fromTransformations(cameraRotationTransformations);
			gizmoEntity->update();
		}
	}
	{
		auto gizmoEntity = dynamic_cast<Object3D*>(engine->getEntity(id + ".tdme.gizmo.rotations"));
		if (gizmoEntity != nullptr) {
			cameraRotationTransformations.setTranslation(gizmoEntity->getTranslation());
			cameraRotationTransformations.setScale(gizmoEntity->getScale());
			cameraRotationTransformations.update();
			gizmoEntity->fromTransformations(cameraRotationTransformations);
			gizmoEntity->setNodeTransformationsMatrix("rotate_x", rotationsMatrix);
			gizmoEntity->setNodeTransformationsMatrix("rotate_y", rotationsMatrix);
			gizmoEntity->setNodeTransformationsMatrix("rotate_z", rotationsMatrix);
			gizmoEntity->update();
		}
	}
	{
		auto gizmoEntity = dynamic_cast<Object3D*>(engine->getEntity(id + ".tdme.gizmo.scale"));
		if (gizmoEntity != nullptr) {
			cameraRotationTransformations.setTranslation(gizmoEntity->getTranslation());
			cameraRotationTransformations.setScale(gizmoEntity->getScale());
			cameraRotationTransformations.update();
			gizmoEntity->fromTransformations(cameraRotationTransformations);
			gizmoEntity->setNodeTransformationsMatrix("scale_x", rotationsMatrix);
			gizmoEntity->setNodeTransformationsMatrix("scale_y", rotationsMatrix);
			gizmoEntity->setNodeTransformationsMatrix("scale_z", rotationsMatrix);
			gizmoEntity->setNodeTransformationsMatrix("scale_x_plane", rotationsMatrix);
			gizmoEntity->setNodeTransformationsMatrix("scale_y_plane", rotationsMatrix);
			gizmoEntity->setNodeTransformationsMatrix("scale_z_plane", rotationsMatrix);
			gizmoEntity->update();
		}
	}
	{
		auto gizmoEntity = dynamic_cast<Object3D*>(engine->getEntity(id + ".tdme.gizmo.all"));
		if (gizmoEntity != nullptr) {
			cameraRotationTransformations.setTranslation(gizmoEntity->getTranslation());
			cameraRotationTransformations.setScale(gizmoEntity->getScale());
			cameraRotationTransformations.update();
			gizmoEntity->fromTransformations(cameraRotationTransformations);
			gizmoEntity->setNodeTransformationsMatrix("all_scale_x", rotationsMatrix);
			gizmoEntity->setNodeTransformationsMatrix("all_scale_y", rotationsMatrix);
			gizmoEntity->setNodeTransformationsMatrix("all_scale_z", rotationsMatrix);
			gizmoEntity->setNodeTransformationsMatrix("scale_x_plane", rotationsMatrix);
			gizmoEntity->setNodeTransformationsMatrix("scale_y_plane", rotationsMatrix);
			gizmoEntity->setNodeTransformationsMatrix("scale_z_plane", rotationsMatrix);
			gizmoEntity->update();
		}
	}
}
