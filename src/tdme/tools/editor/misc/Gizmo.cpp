#include <tdme/tools/editor/misc/Gizmo.h>

#include <array>

#include <tdme/tdme.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/primitives/LineSegment.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/Frustum.h>
#include <tdme/engine/Object.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/StringTools.h>

using tdme::tools::editor::misc::Gizmo;

using std::array;

using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::primitives::LineSegment;
using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::Frustum;
using tdme::engine::Object;
using tdme::engine::Transform;
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
	gizmoTranslationHandleDiffAvailable[0] = false;
	gizmoTranslationHandleDiffAvailable[1] = false;
	gizmoTranslationHandleDiffAvailable[2] = false;
	gizmoTranslationLastResultAvailable[0] = false;
	gizmoTranslationLastResultAvailable[1] = false;
	gizmoTranslationLastResultAvailable[2] = false;
	gizmoRotationLastResultAvailable = false;
}

Gizmo::~Gizmo() {
}

void Gizmo::updateGizmo(const Vector3& gizmoTranslation, const Transform& transform) {
	this->gizmoTranslation = gizmoTranslation;
	orthogonalGizmoTranslation = computeOrthogonalGizmoCoordinate(gizmoTranslation);
	Object* gizmoEntity = nullptr;
	switch (getGizmoType()) {
		case GIZMOTYPE_ALL:
			{
				if ((gizmoTypeMask & GIZMOTYPE_TRANSLATE) == GIZMOTYPE_TRANSLATE &&
					(gizmoTypeMask & GIZMOTYPE_ROTATE) == GIZMOTYPE_ROTATE &&
					(gizmoTypeMask & GIZMOTYPE_SCALE) == GIZMOTYPE_SCALE) {
					engine->removeEntity(id + ".tdme.gizmo.translation");
					engine->removeEntity(id + ".tdme.gizmo.scale");
					gizmoEntity = dynamic_cast<Object*>(engine->getEntity(id + ".tdme.gizmo.all"));
					if (gizmoEntity == nullptr) engine->addEntity(gizmoEntity = new Object(id + ".tdme.gizmo.all", Tools::getGizmoAll()));
					gizmoEntity->setPickable(true);
					gizmoEntity->setFrustumCulling(false);
					gizmoEntity->setRenderPass(Entity::RENDERPASS_GIZMO);
					gizmoEntity->setTranslation(orthogonalGizmoTranslation);
					gizmoEntity->setScale(Vector3(GIZMO_ORTHO_DEFAULT_SCALE, GIZMO_ORTHO_DEFAULT_SCALE, GIZMO_ORTHO_DEFAULT_SCALE));
					gizmoEntity->update();
					gizmoEntity = dynamic_cast<Object*>(engine->getEntity(id + ".tdme.gizmo.rotations"));
					if (gizmoEntity == nullptr) engine->addEntity(gizmoEntity = new Object(id + ".tdme.gizmo.rotations", Tools::getGizmoRotations()));
					gizmoEntity->setPickable(true);
					gizmoEntity->setFrustumCulling(false);
					gizmoEntity->setRenderPass(Entity::RENDERPASS_GIZMO);
					gizmoEntity->setTranslation(orthogonalGizmoTranslation);
					gizmoEntity->setScale(Vector3(GIZMO_ORTHO_DEFAULT_SCALE, GIZMO_ORTHO_DEFAULT_SCALE, GIZMO_ORTHO_DEFAULT_SCALE));
					gizmoEntity->update();
				} else
				if ((gizmoTypeMask & GIZMOTYPE_TRANSLATE) == GIZMOTYPE_TRANSLATE &&
					(gizmoTypeMask & GIZMOTYPE_SCALE) == GIZMOTYPE_SCALE) {
					engine->removeEntity(id + ".tdme.gizmo.translation");
					engine->removeEntity(id + ".tdme.gizmo.rotations");
					engine->removeEntity(id + ".tdme.gizmo.scale");
					gizmoEntity = dynamic_cast<Object*>(engine->getEntity(id + ".tdme.gizmo.all"));
					if (gizmoEntity == nullptr) engine->addEntity(gizmoEntity = new Object(id + ".tdme.gizmo.all", Tools::getGizmoTranslationScale()));
					gizmoEntity->setPickable(true);
					gizmoEntity->setFrustumCulling(false);
					gizmoEntity->setRenderPass(Entity::RENDERPASS_GIZMO);
					gizmoEntity->setTranslation(orthogonalGizmoTranslation);
					gizmoEntity->setScale(Vector3(GIZMO_ORTHO_DEFAULT_SCALE, GIZMO_ORTHO_DEFAULT_SCALE, GIZMO_ORTHO_DEFAULT_SCALE));
					gizmoEntity->update();
				} else {
					if ((gizmoTypeMask & GIZMOTYPE_TRANSLATE) == GIZMOTYPE_TRANSLATE) {
						engine->removeEntity(id + ".tdme.gizmo.all");
						engine->removeEntity(id + ".tdme.gizmo.rotations");
						engine->removeEntity(id + ".tdme.gizmo.scale");
						gizmoEntity = dynamic_cast<Object*>(engine->getEntity(id + ".tdme.gizmo.translation"));
						if (gizmoEntity == nullptr) engine->addEntity(gizmoEntity = new Object(id + ".tdme.gizmo.translation", Tools::getGizmoTranslation()));
						gizmoEntity->setPickable(true);
						gizmoEntity->setFrustumCulling(false);
						gizmoEntity->setRenderPass(Entity::RENDERPASS_GIZMO);
						gizmoEntity->setTranslation(orthogonalGizmoTranslation);
						gizmoEntity->setScale(Vector3(GIZMO_ORTHO_DEFAULT_SCALE, GIZMO_ORTHO_DEFAULT_SCALE, GIZMO_ORTHO_DEFAULT_SCALE));
						gizmoEntity->update();
					}
					if ((gizmoTypeMask & GIZMOTYPE_ROTATE) == GIZMOTYPE_ROTATE) {
						engine->removeEntity(id + ".tdme.gizmo.all");
						engine->removeEntity(id + ".tdme.gizmo.translation");
						engine->removeEntity(id + ".tdme.gizmo.scale");
						gizmoEntity = dynamic_cast<Object*>(engine->getEntity(id + ".tdme.gizmo.rotations"));
						if (gizmoEntity == nullptr) engine->addEntity(gizmoEntity = new Object(id + ".tdme.gizmo.rotations", Tools::getGizmoRotations()));
						gizmoEntity->setPickable(true);
						gizmoEntity->setRenderPass(Entity::RENDERPASS_GIZMO);
						gizmoEntity->setTranslation(orthogonalGizmoTranslation);
						gizmoEntity->setScale(Vector3(GIZMO_ORTHO_DEFAULT_SCALE, GIZMO_ORTHO_DEFAULT_SCALE, GIZMO_ORTHO_DEFAULT_SCALE));
						gizmoEntity->update();
					}
					if ((gizmoTypeMask & GIZMOTYPE_SCALE) == GIZMOTYPE_SCALE) {
						engine->removeEntity(id + ".tdme.gizmo.all");
						engine->removeEntity(id + ".tdme.gizmo.translation");
						engine->removeEntity(id + ".tdme.gizmo.rotations");
						gizmoEntity = dynamic_cast<Object*>(engine->getEntity(id + ".tdme.gizmo.scale"));
						if (gizmoEntity == nullptr) engine->addEntity(gizmoEntity = new Object(id + ".tdme.gizmo.scale", Tools::getGizmoScale()));
						gizmoEntity->setPickable(true);
						gizmoEntity->setFrustumCulling(false);
						gizmoEntity->setRenderPass(Entity::RENDERPASS_GIZMO);
						gizmoEntity->setTranslation(orthogonalGizmoTranslation);
						gizmoEntity->setScale(Vector3(GIZMO_ORTHO_DEFAULT_SCALE, GIZMO_ORTHO_DEFAULT_SCALE, GIZMO_ORTHO_DEFAULT_SCALE));
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
				gizmoEntity = dynamic_cast<Object*>(engine->getEntity(id + ".tdme.gizmo.translation"));
				if (gizmoEntity == nullptr) engine->addEntity(gizmoEntity = new Object(id + ".tdme.gizmo.translation", Tools::getGizmoTranslation()));
				gizmoEntity->setPickable(true);
				gizmoEntity->setFrustumCulling(false);
				gizmoEntity->setRenderPass(Entity::RENDERPASS_GIZMO);
				gizmoEntity->setTranslation(orthogonalGizmoTranslation);
				gizmoEntity->setScale(Vector3(GIZMO_ORTHO_DEFAULT_SCALE, GIZMO_ORTHO_DEFAULT_SCALE, GIZMO_ORTHO_DEFAULT_SCALE));
				gizmoEntity->update();
				break;
			}
		case GIZMOTYPE_ROTATE:
			{
				engine->removeEntity(id + ".tdme.gizmo.all");
				engine->removeEntity(id + ".tdme.gizmo.translation");
				engine->removeEntity(id + ".tdme.gizmo.scale");
				gizmoEntity = dynamic_cast<Object*>(engine->getEntity(id + ".tdme.gizmo.rotations"));
				if (gizmoEntity == nullptr) engine->addEntity(gizmoEntity = new Object(id + ".tdme.gizmo.rotations", Tools::getGizmoRotations()));
				gizmoEntity->setPickable(true);
				gizmoEntity->setFrustumCulling(false);
				gizmoEntity->setRenderPass(Entity::RENDERPASS_GIZMO);
				gizmoEntity->setTranslation(orthogonalGizmoTranslation);
				gizmoEntity->setScale(Vector3(GIZMO_ORTHO_DEFAULT_SCALE, GIZMO_ORTHO_DEFAULT_SCALE, GIZMO_ORTHO_DEFAULT_SCALE));
				gizmoEntity->update();
				break;
			}
		case GIZMOTYPE_SCALE:
			{
				engine->removeEntity(id + ".tdme.gizmo.all");
				engine->removeEntity(id + ".tdme.gizmo.translation");
				engine->removeEntity(id + ".tdme.gizmo.rotations");
				gizmoEntity = dynamic_cast<Object*>(engine->getEntity(id + ".tdme.gizmo.scale"));
				if (gizmoEntity == nullptr) engine->addEntity(gizmoEntity = new Object(id + ".tdme.gizmo.scale", Tools::getGizmoScale()));
				gizmoEntity->setPickable(true);
				gizmoEntity->setFrustumCulling(false);
				gizmoEntity->setRenderPass(Entity::RENDERPASS_GIZMO);
				gizmoEntity->setTranslation(orthogonalGizmoTranslation);
				gizmoEntity->setScale(Vector3(GIZMO_ORTHO_DEFAULT_SCALE, GIZMO_ORTHO_DEFAULT_SCALE, GIZMO_ORTHO_DEFAULT_SCALE));
				gizmoEntity->update();
				break;
			}
		case GIZMOTYPE_NONE:
			break;
	}
	setGizmoRotation(transform);
}

Object* Gizmo::getGizmoObject() {
	auto gizmoEntity = dynamic_cast<Object*>(engine->getEntity(id + ".tdme.gizmo.all"));
	if (gizmoEntity == nullptr) gizmoEntity = dynamic_cast<Object*>(engine->getEntity(id + ".tdme.gizmo.translation"));
	if (gizmoEntity == nullptr) gizmoEntity = dynamic_cast<Object*>(engine->getEntity(id + ".tdme.gizmo.rotations"));
	if (gizmoEntity == nullptr) gizmoEntity = dynamic_cast<Object*>(engine->getEntity(id + ".tdme.gizmo.scale"));
	return gizmoEntity;
}

void Gizmo::removeGizmo() {
	engine->removeEntity(id + ".tdme.gizmo.all");
	engine->removeEntity(id + ".tdme.gizmo.translation");
	engine->removeEntity(id + ".tdme.gizmo.scale");
	engine->removeEntity(id + ".tdme.gizmo.rotations");
	setGizmoMode(GIZMOMODE_NONE);
}

bool Gizmo::determineGizmoMovement(int mouseX, int mouseY, int axisIdx, const Vector3& axis, Vector3& deltaMovement) {
	// engine mouse position for near, far
	auto nearPlaneWorldCoordinate = engine->computeWorldCoordinateByMousePosition(mouseX, mouseY, 0.0f);
	auto farPlaneWorldCoordinate = engine->computeWorldCoordinateByMousePosition(mouseX, mouseY, 1.0f);

	//
	Vector3 axisMin = axis.clone().scale(-5000.0f);
	Vector3 axisMax = axis.clone().scale(5000.0f);

	//
	axisMin.add(gizmoTranslation);
	axisMax.add(gizmoTranslation);

	// compute closest points on near, far mouse positions line segment and axis
	Vector3 gizmoTranslationOnAxis;
	Vector3 gizmoTranslationOnAxisTmp;
	LineSegment::computeClosestPointsOnLineSegments(axisMin, axisMax, nearPlaneWorldCoordinate, farPlaneWorldCoordinate, gizmoTranslationOnAxis, gizmoTranslationOnAxisTmp);

	//
	if (gizmoTranslationHandleDiffAvailable[axisIdx] == false) {
		gizmoTranslationHandleDiff[axisIdx] = gizmoTranslationOnAxis.clone().sub(gizmoTranslation);
		gizmoTranslationHandleDiffAvailable[axisIdx] = true;
	}

	// do we already have a old result
	auto success = gizmoTranslationLastResultAvailable[axisIdx] == true;
	if (success == true) {
		deltaMovement[axisIdx] = gizmoTranslationOnAxis.clone().sub(gizmoTranslationLastResult[axisIdx])[axisIdx];
		auto movementLength = gizmoTranslation.clone().sub(gizmoTranslationOnAxis.clone().sub(gizmoTranslationHandleDiff[axisIdx])).computeLength();
		if (deltaMovement[axisIdx] < Math::EPSILON) {
			deltaMovement[axisIdx] = -1.0f;
			deltaMovement[axisIdx]*= movementLength;
		} else
		if (deltaMovement[axisIdx] > Math::EPSILON) {
			deltaMovement[axisIdx] = 1.0f;
			deltaMovement[axisIdx]*= movementLength;
		} else {
			deltaMovement[axisIdx] = 0.0f;
		}
	}

	// what ever, we have a new one
	gizmoTranslationLastResult[axisIdx] = gizmoTranslationOnAxis;
	gizmoTranslationLastResultAvailable[axisIdx] = true;

	//
	return success;
}

bool Gizmo::determineGizmoScale(int mouseX, int mouseY, int axisIdx, const Vector3& axis, Vector3& deltaScale) {
	auto nearPlaneWorldCoordinate = engine->computeWorldCoordinateByMousePosition(mouseX, mouseY, 0.0f);
	auto farPlaneWorldCoordinate = engine->computeWorldCoordinateByMousePosition(mouseX, mouseY, 1.0f);

	//
	Vector3 axisMin = axis.clone().scale(-5000.0f);
	Vector3 axisMax = axis.clone().scale(5000.0f);

	//
	axisMin.add(gizmoTranslation);
	axisMax.add(gizmoTranslation);

	//
	Vector3 contactOnAxis;
	Vector3 contactOnAxisTmp;
	LineSegment::computeClosestPointsOnLineSegments(axisMin, axisMax, nearPlaneWorldCoordinate, farPlaneWorldCoordinate, contactOnAxis, contactOnAxisTmp);
	auto success = gizmoTranslationLastResultAvailable[axisIdx] == true;
	if (success == true) {
		auto direction = 1.0f;
		if (gizmoTranslationLastResult[axisIdx].clone().sub(gizmoTranslation).computeLengthSquared() > contactOnAxis.clone().sub(gizmoTranslation).computeLengthSquared()) direction = -1.0f;
		deltaScale[axisIdx] = contactOnAxis.clone().sub(gizmoTranslationLastResult[axisIdx]).computeLength() * direction;
	}
	gizmoTranslationLastResult[axisIdx] = contactOnAxis;
	gizmoTranslationLastResultAvailable[axisIdx] = true;
	return success;
}

bool Gizmo::determineGizmoRotation(int mouseX, int mouseY, const array<Vector3, 4>& vertices, const Vector3& planeNormal, float& deltaRotation) {
	auto nearPlaneWorldCoordinate = engine->computeWorldCoordinateByMousePosition(mouseX, mouseY, 0.0f);
	auto farPlaneWorldCoordinate = engine->computeWorldCoordinateByMousePosition(mouseX, mouseY, 1.0f);
	Vector3 lineTriangleContact;
	auto transformedVertices = vertices;
	for (auto& vertex: transformedVertices) {
		vertex.add(gizmoTranslation);
	}
	if (LineSegment::doesLineSegmentCollideWithTriangle(
		transformedVertices[0],
		transformedVertices[1],
		transformedVertices[2],
		nearPlaneWorldCoordinate,
		farPlaneWorldCoordinate,
		lineTriangleContact) == true ||
		LineSegment::doesLineSegmentCollideWithTriangle(
		transformedVertices[2],
		transformedVertices[3],
		transformedVertices[0],
		nearPlaneWorldCoordinate,
		farPlaneWorldCoordinate,
		lineTriangleContact) == true
	) {
		auto success = gizmoRotationLastResultAvailable == true;
		if (success == true) {
			auto a = lineTriangleContact.clone().sub(gizmoTranslation).normalize();
			auto b = gizmoRotationLastResult.clone().sub(gizmoTranslation).normalize();
			deltaRotation = Vector3::computeAngle(a, b, planeNormal);
			if (deltaRotation > 180.0f) deltaRotation = deltaRotation - 360.0f;
		}
		gizmoRotationLastResult = lineTriangleContact;
		gizmoRotationLastResultAvailable = true;
		return success;
	}
	return false;
}

bool Gizmo::determineGizmoDeltaTransformations(int mouseX, int mouseY, Vector3& deltaTranslation, Vector3& deltaRotation, Vector3& deltaScale) {
	if (getGizmoMode() == GIZMOMODE_NONE) return false;

	//
	deltaTranslation.set(0.0f, 0.0f, 0.0f);
	deltaRotation.set(0.0f, 0.0f, 0.0f);
	deltaScale.set(1.0f, 1.0f, 1.0f);
	Vector3 gizmoMovement;

	//
	const Vector3 planeXYNormal(0.0f, 0.0f, -1.0f);
	const array<Vector3, 4> planeXY = {
		Vector3(-5000.0f, -5000.0f, 0.0f),
		Vector3(-5000.0f, 5000.0f, 0.0f),
		Vector3(5000.0f, 5000.0f, 0.0f),
		Vector3(5000.0f, -5000.0f, 0.0f)
	};

	//
	const Vector3 planeXZNormal(0.0f, -1.0f, 0.0f);
	const array<Vector3, 4> planeXZ = {
		Vector3(-5000.0f, 0.0f, -5000.0f),
		Vector3(-5000.0f, 0.0f, 5000.0f),
		Vector3(5000.0f, 0.0f, 5000.0f),
		Vector3(5000.0f, 0.0f, -5000.0f)
	};

	//
	const Vector3 planeYZNormal(-1.0f, 0.0f, 0.0f);
	const array<Vector3, 4> planeYZ = {
		Vector3(0.0f, -5000.0f, -5000.0f),
		Vector3(0.0f, -5000.0f, 5000.0f),
		Vector3(0.0f, 5000.0f, 5000.0f),
		Vector3(0.0f, 5000.0f, -5000.0f)
	};

	//
	switch (getGizmoMode()) {
		case GIZMOMODE_TRANSLATE_X:
			{
				if (determineGizmoMovement(mouseX, mouseY, GizmoAxisIdx::GIZMOAXISIDX_X, Vector3(1.0f, 0.0, 0.0f), gizmoMovement) == true) {
					deltaTranslation.setX(gizmoMovement.getX());
				}
				break;
			}
		case GIZMOMODE_TRANSLATE_Y:
			{
				if (determineGizmoMovement(mouseX, mouseY, GizmoAxisIdx::GIZMOAXISIDX_Y, Vector3(0.0f, 1.0, 0.0f), gizmoMovement) == true) {
					deltaTranslation.setY(gizmoMovement.getY());
				}
				break;
			}
		case GIZMOMODE_TRANSLATE_Z:
			{
				if (determineGizmoMovement(mouseX, mouseY, GizmoAxisIdx::GIZMOAXISIDX_Z, Vector3(0.0f, 0.0, 1.0f), gizmoMovement) == true) {
					deltaTranslation.setZ(gizmoMovement.getZ());
				}
				break;
			}
		case GIZMOMODE_TRANSLATEPLANE_X:
			{
				if (determineGizmoMovement(mouseX, mouseY, GizmoAxisIdx::GIZMOAXISIDX_Y, Vector3(0.0f, 1.0, 0.0f), gizmoMovement) == true &&
					determineGizmoMovement(mouseX, mouseY, GizmoAxisIdx::GIZMOAXISIDX_Z, Vector3(0.0f, 0.0, 1.0f), gizmoMovement) == true) {
					deltaTranslation.setY(gizmoMovement.getY());
					deltaTranslation.setZ(gizmoMovement.getZ());
				}
				break;
			}
		case GIZMOMODE_TRANSLATEPLANE_Y:
			{
				if (determineGizmoMovement(mouseX, mouseY, GizmoAxisIdx::GIZMOAXISIDX_X, Vector3(1.0f, 0.0, 0.0f), gizmoMovement) == true &&
					determineGizmoMovement(mouseX, mouseY, GizmoAxisIdx::GIZMOAXISIDX_Z, Vector3(0.0f, 0.0, 1.0f), gizmoMovement) == true) {
					deltaTranslation.setX(gizmoMovement.getX());
					deltaTranslation.setZ(gizmoMovement.getZ());
				}
				break;
			}
		case GIZMOMODE_TRANSLATEPLANE_Z:
			{
				if (determineGizmoMovement(mouseX, mouseY, GizmoAxisIdx::GIZMOAXISIDX_X, Vector3(1.0f, 0.0, 0.0f), gizmoMovement) == true &&
					determineGizmoMovement(mouseX, mouseY, GizmoAxisIdx::GIZMOAXISIDX_Y, Vector3(0.0f, 1.0, 0.0f), gizmoMovement) == true) {
					deltaTranslation.setX(gizmoMovement.getX());
					deltaTranslation.setY(gizmoMovement.getY());
				}
				break;
			}
		case GIZMOMODE_SCALE_X:
			{
				if (determineGizmoScale(mouseX, mouseY, GizmoAxisIdx::GIZMOAXISIDX_X, rotationsMatrix.multiply(Vector3(1.0f, 0.0, 0.0f)).normalize(), gizmoMovement) == true) {
					deltaScale.add(gizmoMovement);
				}
				break;
			}
		case GIZMOMODE_SCALE_Y:
			{
				if (determineGizmoScale(mouseX, mouseY, GizmoAxisIdx::GIZMOAXISIDX_Y, rotationsMatrix.multiply(Vector3(0.0f, 1.0, 0.0f)).normalize(), gizmoMovement) == true) {
					deltaScale.add(gizmoMovement);
				}
				break;
			}
		case GIZMOMODE_SCALE_Z:
			{
				if (determineGizmoScale(mouseX, mouseY, GizmoAxisIdx::GIZMOAXISIDX_Z, rotationsMatrix.multiply(Vector3(0.0f, 0.0, 1.0f)).normalize(), gizmoMovement) == true) {
					deltaScale.add(gizmoMovement);
				}
				break;
			}
		case GIZMOMODE_SCALEPLANE_X:
			{
				if (determineGizmoScale(mouseX, mouseY, GizmoAxisIdx::GIZMOAXISIDX_Y, Vector3(0.0f, 1.0, 0.0f), gizmoMovement) == true &&
					determineGizmoScale(mouseX, mouseY, GizmoAxisIdx::GIZMOAXISIDX_Z, Vector3(0.0f, 0.0, 1.0f), gizmoMovement) == true) {
					deltaScale.add(gizmoMovement);
				}
				break;
			}
		case GIZMOMODE_SCALEPLANE_Y:
			{
				if (determineGizmoScale(mouseX, mouseY, GizmoAxisIdx::GIZMOAXISIDX_X, Vector3(1.0f, 0.0, 0.0f), gizmoMovement) == true &&
					determineGizmoScale(mouseX, mouseY, GizmoAxisIdx::GIZMOAXISIDX_Z, Vector3(0.0f, 0.0, 1.0f), gizmoMovement) == true) {
					deltaScale.add(gizmoMovement);
				}
				break;
			}
		case GIZMOMODE_SCALEPLANE_Z:
			{
				if (determineGizmoScale(mouseX, mouseY, GizmoAxisIdx::GIZMOAXISIDX_X, Vector3(1.0f, 0.0, 0.0f), gizmoMovement) == true &&
					determineGizmoScale(mouseX, mouseY, GizmoAxisIdx::GIZMOAXISIDX_Y, Vector3(0.0f, 1.0, 0.0f), gizmoMovement) == true) {
					deltaScale.add(gizmoMovement);
				}
				break;
			}
		case GIZMOMODE_ROTATE_X:
			{
				const auto& planeVertices = planeYZ;
				const auto& planeNormal = planeYZNormal;
				float gizmoDeltaRotation = 0.0f;
				auto vertices = planeVertices;
				for (auto& vertex: vertices) {
					vertex = rotationsMatrix.multiply(vertex);
				}
				auto planeNormalTransformed = rotationsMatrix.multiply(planeNormal).normalize();
				if (determineGizmoRotation(mouseX, mouseY, vertices, planeNormalTransformed, gizmoDeltaRotation) == true) {
					deltaRotation.setX(gizmoDeltaRotation);
					break;
				}
			}
			break;
		case GIZMOMODE_ROTATE_Y:
			{
				const auto& planeVertices = planeXZ;
				const auto& planeNormal = planeXZNormal;
				float gizmoDeltaRotation = 0.0f;
				auto vertices = planeVertices;
				for (auto& vertex: vertices) {
					vertex = rotationsMatrix.multiply(vertex);
				}
				auto planeNormalTransformed = rotationsMatrix.multiply(planeNormal).normalize();
				if (determineGizmoRotation(mouseX, mouseY, vertices, planeNormalTransformed, gizmoDeltaRotation) == true) {
					deltaRotation.setY(gizmoDeltaRotation);
					break;
				}
			}
			break;
		case GIZMOMODE_ROTATE_Z:
			{
				const auto& planeVertices = planeXY;
				const auto& planeNormal = planeXYNormal;
				float gizmoDeltaRotation = 0.0f;
				auto vertices = planeVertices;
				for (auto& vertex: vertices) {
					vertex = rotationsMatrix.multiply(vertex);
				}
				auto planeNormalTransformed = rotationsMatrix.multiply(planeNormal).normalize();
				if (determineGizmoRotation(mouseX, mouseY, vertices, planeNormalTransformed, gizmoDeltaRotation) == true) {
					deltaRotation.setZ(gizmoDeltaRotation);
					break;
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
		//
		return true;
	}
	return false;
}

void Gizmo::setGizmoRotation(const Transform& transform) {
	auto cameraMatrixEuler = engine->getCamera()->getCameraMatrix().computeEulerAngles();
	Transform cameraRotationTransformations;
	cameraRotationTransformations.addRotation(Vector3(0.0f, 0.0f, 1.0f), cameraMatrixEuler.getZ());
	cameraRotationTransformations.addRotation(Vector3(0.0f, 1.0f, 0.0f), cameraMatrixEuler.getY());
	cameraRotationTransformations.addRotation(Vector3(1.0f, 0.0f, 0.0f), cameraMatrixEuler.getX());
	cameraRotationTransformations.update();
	//
	rotationsMatrix = transform.getRotationsQuaternion().computeMatrix();
	{
		auto gizmoEntity = dynamic_cast<Object*>(engine->getEntity(id + ".tdme.gizmo.translation"));
		if (gizmoEntity != nullptr) {
			cameraRotationTransformations.setTranslation(gizmoEntity->getTranslation());
			cameraRotationTransformations.setScale(gizmoEntity->getScale());
			cameraRotationTransformations.update();
			gizmoEntity->setTransform(cameraRotationTransformations);
			gizmoEntity->update();
		}
	}
	{
		auto gizmoEntity = dynamic_cast<Object*>(engine->getEntity(id + ".tdme.gizmo.rotations"));
		if (gizmoEntity != nullptr) {
			cameraRotationTransformations.setTranslation(gizmoEntity->getTranslation());
			cameraRotationTransformations.setScale(gizmoEntity->getScale());
			cameraRotationTransformations.update();
			gizmoEntity->setTransform(cameraRotationTransformations);
			gizmoEntity->setNodeTransformMatrix("rotate_x", rotationsMatrix);
			gizmoEntity->setNodeTransformMatrix("rotate_y", rotationsMatrix);
			gizmoEntity->setNodeTransformMatrix("rotate_z", rotationsMatrix);
			gizmoEntity->update();
		}
	}
	{
		auto gizmoEntity = dynamic_cast<Object*>(engine->getEntity(id + ".tdme.gizmo.scale"));
		if (gizmoEntity != nullptr) {
			cameraRotationTransformations.setTranslation(gizmoEntity->getTranslation());
			cameraRotationTransformations.setScale(gizmoEntity->getScale());
			cameraRotationTransformations.update();
			gizmoEntity->setTransform(cameraRotationTransformations);
			gizmoEntity->setNodeTransformMatrix("scale_x", rotationsMatrix);
			gizmoEntity->setNodeTransformMatrix("scale_y", rotationsMatrix);
			gizmoEntity->setNodeTransformMatrix("scale_z", rotationsMatrix);
			gizmoEntity->setNodeTransformMatrix("scale_x_plane", rotationsMatrix);
			gizmoEntity->setNodeTransformMatrix("scale_y_plane", rotationsMatrix);
			gizmoEntity->setNodeTransformMatrix("scale_z_plane", rotationsMatrix);
			gizmoEntity->update();
		}
	}
	{
		auto gizmoEntity = dynamic_cast<Object*>(engine->getEntity(id + ".tdme.gizmo.all"));
		if (gizmoEntity != nullptr) {
			cameraRotationTransformations.setTranslation(gizmoEntity->getTranslation());
			cameraRotationTransformations.setScale(gizmoEntity->getScale());
			cameraRotationTransformations.update();
			gizmoEntity->setTransform(cameraRotationTransformations);
			gizmoEntity->setNodeTransformMatrix("all_scale_x", rotationsMatrix);
			gizmoEntity->setNodeTransformMatrix("all_scale_y", rotationsMatrix);
			gizmoEntity->setNodeTransformMatrix("all_scale_z", rotationsMatrix);
			gizmoEntity->setNodeTransformMatrix("scale_x_plane", rotationsMatrix);
			gizmoEntity->setNodeTransformMatrix("scale_y_plane", rotationsMatrix);
			gizmoEntity->setNodeTransformMatrix("scale_z_plane", rotationsMatrix);
			gizmoEntity->update();
		}
	}
}
