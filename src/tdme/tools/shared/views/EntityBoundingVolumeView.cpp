#include <tdme/tools/shared/views/EntityBoundingVolumeView.h>

#include <tdme/math/Math.h>

#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Capsule.h>
#include <tdme/engine/primitives/ConvexMesh.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/primitives/Sphere.h>
#include <tdme/math/Vector3.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/shared/controller/EntityPhysicsSubScreenController_BoundingVolumeType.h>
#include <tdme/tools/shared/controller/EntityPhysicsSubScreenController.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityBoundingVolume.h>
#include <tdme/tools/shared/views/PopUps.h>

using tdme::tools::shared::views::EntityBoundingVolumeView;

using tdme::math::Math;

using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::Object3D;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Capsule;
using tdme::engine::primitives::ConvexMesh;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::Sphere;
using tdme::math::Vector3;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::shared::controller::EntityPhysicsSubScreenController_BoundingVolumeType;
using tdme::tools::shared::controller::EntityPhysicsSubScreenController;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityBoundingVolume;
using tdme::tools::shared::views::PopUps;

EntityBoundingVolumeView::EntityBoundingVolumeView(EntityPhysicsSubScreenController* entityPhysicsSubScreenController, PopUps* popUps)
{
	this->engine = Engine::getInstance();
	this->popUps = popUps;
	this->entityPhysicsSubScreenController = entityPhysicsSubScreenController;
}

PopUps* EntityBoundingVolumeView::getPopUpsViews()
{
	return popUps;
}

void EntityBoundingVolumeView::initialize()
{
	vector<string> boundingVolumeTypes = {
		"None",
		"Sphere",
		"Capsule",
		"Bounding Box",
		"Oriented Bounding Box",
		"Convex Mesh"
	};
	for (auto i = 0; i < EntityPhysicsSubScreenController::MODEL_BOUNDINGVOLUME_COUNT; i++) {
		entityPhysicsSubScreenController->setupBoundingVolumeTypes(i, boundingVolumeTypes);
		entityPhysicsSubScreenController->selectBoundingVolume(i, EntityPhysicsSubScreenController_BoundingVolumeType::NONE);
	}
}

void EntityBoundingVolumeView::resetBoundingVolume(LevelEditorEntity* entity, int32_t idx)
{
	BoundingBox* aabb = nullptr;
	if (entity->getModel() != nullptr) {
		aabb = entity->getModel()->getBoundingBox();
	} else {
		aabb = new BoundingBox(Vector3(-0.5f, 0.0f, -0.5f), Vector3(0.5f, 3.0f, 0.5f));
	}
	auto obb = new OrientedBoundingBox(aabb);
	entityPhysicsSubScreenController->setupSphere(idx, obb->getCenter(), obb->getHalfExtension().computeLength());
{
		Vector3 a;
		Vector3 b;
		auto radius = 0.0f;
		auto& halfExtensionXYZ = obb->getHalfExtension().getArray();
		if (halfExtensionXYZ[0] > halfExtensionXYZ[1] && halfExtensionXYZ[0] > halfExtensionXYZ[2]) {
			radius = Math::sqrt(halfExtensionXYZ[1] * halfExtensionXYZ[1] + halfExtensionXYZ[2] * halfExtensionXYZ[2]);
			a.set((*obb->getAxes())[0]);
			a.scale(-(halfExtensionXYZ[0] - radius));
			a.add(obb->getCenter());
			b.set((*obb->getAxes())[0]);
			b.scale(+(halfExtensionXYZ[0] - radius));
			b.add(obb->getCenter());
		} else
		if (halfExtensionXYZ[1] > halfExtensionXYZ[0] && halfExtensionXYZ[1] > halfExtensionXYZ[2]) {
			radius = Math::sqrt(halfExtensionXYZ[0] * halfExtensionXYZ[0] + halfExtensionXYZ[2] * halfExtensionXYZ[2]);
			a.set((*obb->getAxes())[1]);
			a.scale(-(halfExtensionXYZ[1] - radius));
			a.add(obb->getCenter());
			b.set((*obb->getAxes())[1]);
			b.scale(+(halfExtensionXYZ[1] - radius));
			b.add(obb->getCenter());
		} else {
			radius = Math::sqrt(halfExtensionXYZ[0] * halfExtensionXYZ[0] + halfExtensionXYZ[1] * halfExtensionXYZ[1]);
			a.set((*obb->getAxes())[2]);
			a.scale(-(halfExtensionXYZ[2] - radius));
			a.add(obb->getCenter());
			b.set((*obb->getAxes())[2]);
			b.scale(+(halfExtensionXYZ[2] - radius));
			b.add(obb->getCenter());
		}
		entityPhysicsSubScreenController->setupCapsule(idx, a, b, radius);
	}

	entityPhysicsSubScreenController->setupBoundingBox(idx, aabb->getMin(), aabb->getMax());
	entityPhysicsSubScreenController->setupOrientedBoundingBox(idx, obb->getCenter(), (*obb->getAxes())[0], (*obb->getAxes())[1], (*obb->getAxes())[2], obb->getHalfExtension());
	entityPhysicsSubScreenController->selectBoundingVolume(idx, EntityPhysicsSubScreenController_BoundingVolumeType::NONE);
}

void EntityBoundingVolumeView::setBoundingVolumes(LevelEditorEntity* entity)
{
	for (auto i = 0; i < EntityPhysicsSubScreenController::MODEL_BOUNDINGVOLUME_COUNT; i++) {
		resetBoundingVolume(entity, i);
	}
	for (auto i = 0; i < entity->getBoundingVolumeCount(); i++) {
		auto bv = entity->getBoundingVolumeAt(i);
		if (bv == nullptr) {
			entityPhysicsSubScreenController->selectBoundingVolume(i, EntityPhysicsSubScreenController_BoundingVolumeType::NONE);
			continue;
		} else
		if (dynamic_cast< Sphere* >(bv->getBoundingVolume()) != nullptr) {
			auto sphere = dynamic_cast< Sphere* >(bv->getBoundingVolume());
			entityPhysicsSubScreenController->setupSphere(i, sphere->getCenter(), sphere->getRadius());
			entityPhysicsSubScreenController->selectBoundingVolume(i, EntityPhysicsSubScreenController_BoundingVolumeType::SPHERE);
		} else
		if (dynamic_cast< Capsule* >(bv->getBoundingVolume()) != nullptr) {
			auto capsule = dynamic_cast< Capsule* >(bv->getBoundingVolume());
			entityPhysicsSubScreenController->setupCapsule(i, capsule->getA(), capsule->getB(), capsule->getRadius());
			entityPhysicsSubScreenController->selectBoundingVolume(i, EntityPhysicsSubScreenController_BoundingVolumeType::CAPSULE);
		} else
		if (dynamic_cast< BoundingBox* >(bv->getBoundingVolume()) != nullptr) {
			auto aabb = dynamic_cast< BoundingBox* >(bv->getBoundingVolume());
			entityPhysicsSubScreenController->setupBoundingBox(i, aabb->getMin(), aabb->getMax());
			entityPhysicsSubScreenController->selectBoundingVolume(i, EntityPhysicsSubScreenController_BoundingVolumeType::BOUNDINGBOX);
		} else
		if (dynamic_cast< OrientedBoundingBox* >(bv->getBoundingVolume()) != nullptr) {
			auto obb = dynamic_cast< OrientedBoundingBox* >(bv->getBoundingVolume());
			entityPhysicsSubScreenController->setupOrientedBoundingBox(i, obb->getCenter(), (*obb->getAxes())[0], (*obb->getAxes())[1], (*obb->getAxes())[2], obb->getHalfExtension());
			entityPhysicsSubScreenController->selectBoundingVolume(i, EntityPhysicsSubScreenController_BoundingVolumeType::ORIENTEDBOUNDINGBOX);
		} else
		if (dynamic_cast< ConvexMesh* >(bv->getBoundingVolume()) != nullptr) {
			entityPhysicsSubScreenController->setupConvexMesh(i, bv->getModelMeshFile());
			entityPhysicsSubScreenController->selectBoundingVolume(i, EntityPhysicsSubScreenController_BoundingVolumeType::CONVEXMESH);
		}
		entityPhysicsSubScreenController->enableBoundingVolume(i);
		entityPhysicsSubScreenController->setupModelBoundingVolumeType(entity, i);
	}
}

void EntityBoundingVolumeView::unsetBoundingVolumes()
{
	for (auto i = 0; i < EntityPhysicsSubScreenController::MODEL_BOUNDINGVOLUME_COUNT; i++) {
		entityPhysicsSubScreenController->disableBoundingVolume(i);
	}
}

void EntityBoundingVolumeView::selectBoundingVolumeType(int32_t idx, int32_t bvTypeId)
{
	switch (bvTypeId) {
	case 0:
		entityPhysicsSubScreenController->selectBoundingVolume(idx, EntityPhysicsSubScreenController_BoundingVolumeType::NONE);
		break;
	case 1:
		entityPhysicsSubScreenController->selectBoundingVolume(idx, EntityPhysicsSubScreenController_BoundingVolumeType::SPHERE);
		break;
	case 2:
		entityPhysicsSubScreenController->selectBoundingVolume(idx, EntityPhysicsSubScreenController_BoundingVolumeType::CAPSULE);
		break;
	case 3:
		entityPhysicsSubScreenController->selectBoundingVolume(idx, EntityPhysicsSubScreenController_BoundingVolumeType::BOUNDINGBOX);
		break;
	case 4:
		entityPhysicsSubScreenController->selectBoundingVolume(idx, EntityPhysicsSubScreenController_BoundingVolumeType::ORIENTEDBOUNDINGBOX);
		break;
	case 5:
		entityPhysicsSubScreenController->selectBoundingVolume(idx, EntityPhysicsSubScreenController_BoundingVolumeType::CONVEXMESH);
		break;
	}

}

void EntityBoundingVolumeView::clearModelBoundingVolume(int32_t idx) {
	auto modelBoundingVolumeEntityId = EntityPhysicsSubScreenController::MODEL_BOUNDINGVOLUME_IDS[idx];
	auto modelBoundingVolumeEntity = engine->getEntity(modelBoundingVolumeEntityId);
	if (modelBoundingVolumeEntity != nullptr) {
		engine->removeEntity(modelBoundingVolumeEntityId);
	}
}

void EntityBoundingVolumeView::setupModelBoundingVolume(LevelEditorEntity* entity, int32_t idx)
{
	auto entityBoundingVolume = entity->getBoundingVolumeAt(idx);
	auto modelBoundingVolumeEntityId = EntityPhysicsSubScreenController::MODEL_BOUNDINGVOLUME_IDS[idx];
	auto modelEntity = engine->getEntity("model");
	if (entityBoundingVolume->getModel() == nullptr) return;

	auto modelBoundingVolumeEntity = new Object3D(modelBoundingVolumeEntityId, entityBoundingVolume->getModel());
	modelBoundingVolumeEntity->setEnabled(false);
	if (modelEntity != nullptr) {
		modelBoundingVolumeEntity->setScale(modelEntity->getScale());
		modelBoundingVolumeEntity->update();
	}
	modelBoundingVolumeEntity->setScale(
		modelBoundingVolumeEntity->getScale().clone().scale(1.1f)
	);
	engine->addEntity(modelBoundingVolumeEntity);
}

void EntityBoundingVolumeView::applyBoundingVolumeNone(LevelEditorEntity* entity, int32_t idx)
{
	if (entity == nullptr)
		return;

	clearModelBoundingVolume(idx);
	auto entityBoundingVolume = entity->getBoundingVolumeAt(idx);
	entityBoundingVolume->setupNone();
	setupModelBoundingVolume(entity, idx);
}

void EntityBoundingVolumeView::applyBoundingVolumeSphere(LevelEditorEntity* entity, int32_t idx, const Vector3& center, float radius)
{
	if (entity == nullptr)
		return;

	clearModelBoundingVolume(idx);
	auto entityBoundingVolume = entity->getBoundingVolumeAt(idx);
	entityBoundingVolume->setupSphere(center, radius);
	setupModelBoundingVolume(entity, idx);
}

void EntityBoundingVolumeView::applyBoundingVolumeCapsule(LevelEditorEntity* entity, int32_t idx, const Vector3& a, const Vector3& b, float radius)
{
	if (entity == nullptr)
		return;

	clearModelBoundingVolume(idx);
	auto entityBoundingVolume = entity->getBoundingVolumeAt(idx);
	entityBoundingVolume->setupCapsule(a, b, radius);
	setupModelBoundingVolume(entity, idx);
}

void EntityBoundingVolumeView::applyBoundingVolumeAabb(LevelEditorEntity* entity, int32_t idx, const Vector3& min, const Vector3& max)
{
	if (entity == nullptr)
		return;

	clearModelBoundingVolume(idx);
	auto entityBoundingVolume = entity->getBoundingVolumeAt(idx);
	entityBoundingVolume->setupAabb(min, max);
	setupModelBoundingVolume(entity, idx);
}

void EntityBoundingVolumeView::applyBoundingVolumeObb(LevelEditorEntity* entity, int32_t idx, const Vector3& center, const Vector3& axis0, const Vector3& axis1, const Vector3& axis2, const Vector3& halfExtension)
{
	if (entity == nullptr)
		return;

	clearModelBoundingVolume(idx);
	auto entityBoundingVolume = entity->getBoundingVolumeAt(idx);
	entityBoundingVolume->setupObb(center, axis0, axis1, axis2, halfExtension);
	setupModelBoundingVolume(entity, idx);
}

void EntityBoundingVolumeView::applyBoundingVolumeConvexMesh(LevelEditorEntity* entity, int32_t idx, const string& fileName)
{
	if (entity == nullptr)
		return;

	clearModelBoundingVolume(idx);
	auto entityBoundingVolume = entity->getBoundingVolumeAt(idx);
	entityBoundingVolume->setupConvexMesh(
		FileSystem::getInstance()->getPathName(fileName),
		FileSystem::getInstance()->getFileName(fileName)
	);
	setupModelBoundingVolume(entity, idx);
}

void EntityBoundingVolumeView::setTerrainMesh(LevelEditorEntity* entity) {
	if (entity == nullptr)
		return;

	entityPhysicsSubScreenController->setTerrainMesh(entity);
}

void EntityBoundingVolumeView::unsetTerrainMesh() {
	entityPhysicsSubScreenController->unsetTerrainMesh();
}

void EntityBoundingVolumeView::unsetConvexMeshes() {
	entityPhysicsSubScreenController->unsetConvexMeshes();
}

void EntityBoundingVolumeView::setConvexMeshes(LevelEditorEntity* entity) {
	entityPhysicsSubScreenController->setConvexMeshes(entity);
}

void EntityBoundingVolumeView::unsetPhysics() {
	entityPhysicsSubScreenController->unsetPhysics();
}

void EntityBoundingVolumeView::setPhysics(LevelEditorEntity* entity) {
	entityPhysicsSubScreenController->setPhysics(entity);
}
