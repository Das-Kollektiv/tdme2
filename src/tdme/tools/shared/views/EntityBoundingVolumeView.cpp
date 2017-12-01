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
#include <tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController_BoundingVolumeType.h>
#include <tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController.h>
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
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_BoundingVolumeType;
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityBoundingVolume;
using tdme::tools::shared::views::PopUps;

EntityBoundingVolumeView::EntityBoundingVolumeView(EntityBoundingVolumeSubScreenController* modelEditorScreenController, PopUps* popUps) 
{
	this->engine = Engine::getInstance();
	this->popUps = popUps;
	this->modelEditorScreenController = modelEditorScreenController;
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
	for (auto i = 0; i < EntityBoundingVolumeSubScreenController::MODEL_BOUNDINGVOLUME_COUNT; i++) {
		modelEditorScreenController->setupBoundingVolumeTypes(i, &boundingVolumeTypes);
		modelEditorScreenController->selectBoundingVolume(i, EntityBoundingVolumeSubScreenController_BoundingVolumeType::NONE);
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
	modelEditorScreenController->setupSphere(idx, obb->getCenter(), obb->getHalfExtension().computeLength());
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
		modelEditorScreenController->setupCapsule(idx, a, b, radius);
	}

	modelEditorScreenController->setupBoundingBox(idx, aabb->getMin(), aabb->getMax());
	modelEditorScreenController->setupOrientedBoundingBox(idx, obb->getCenter(), (*obb->getAxes())[0], (*obb->getAxes())[1], (*obb->getAxes())[2], obb->getHalfExtension());
	modelEditorScreenController->selectBoundingVolume(idx, EntityBoundingVolumeSubScreenController_BoundingVolumeType::NONE);
}

void EntityBoundingVolumeView::setBoundingVolumes(LevelEditorEntity* entity)
{
	for (auto i = 0; i < EntityBoundingVolumeSubScreenController::MODEL_BOUNDINGVOLUME_COUNT; i++) {
		resetBoundingVolume(entity, i);
	}
	for (auto i = 0; i < entity->getBoundingVolumeCount(); i++) {
		auto bv = entity->getBoundingVolumeAt(i);
		if (bv == nullptr) {
			modelEditorScreenController->selectBoundingVolume(i, EntityBoundingVolumeSubScreenController_BoundingVolumeType::NONE);
			continue;
		} else
		if (dynamic_cast< Sphere* >(bv->getBoundingVolume()) != nullptr) {
			auto sphere = dynamic_cast< Sphere* >(bv->getBoundingVolume());
			modelEditorScreenController->setupSphere(i, sphere->getCenter(), sphere->getRadius());
			modelEditorScreenController->selectBoundingVolume(i, EntityBoundingVolumeSubScreenController_BoundingVolumeType::SPHERE);
		} else
		if (dynamic_cast< Capsule* >(bv->getBoundingVolume()) != nullptr) {
			auto capsule = dynamic_cast< Capsule* >(bv->getBoundingVolume());
			modelEditorScreenController->setupCapsule(i, capsule->getA(), capsule->getB(), capsule->getRadius());
			modelEditorScreenController->selectBoundingVolume(i, EntityBoundingVolumeSubScreenController_BoundingVolumeType::CAPSULE);
		} else
		if (dynamic_cast< BoundingBox* >(bv->getBoundingVolume()) != nullptr) {
			auto aabb = dynamic_cast< BoundingBox* >(bv->getBoundingVolume());
			modelEditorScreenController->setupBoundingBox(i, aabb->getMin(), aabb->getMax());
			modelEditorScreenController->selectBoundingVolume(i, EntityBoundingVolumeSubScreenController_BoundingVolumeType::BOUNDINGBOX);
		} else
		if (dynamic_cast< OrientedBoundingBox* >(bv->getBoundingVolume()) != nullptr) {
			auto obb = dynamic_cast< OrientedBoundingBox* >(bv->getBoundingVolume());
			modelEditorScreenController->setupOrientedBoundingBox(i, obb->getCenter(), (*obb->getAxes())[0], (*obb->getAxes())[1], (*obb->getAxes())[2], obb->getHalfExtension());
			modelEditorScreenController->selectBoundingVolume(i, EntityBoundingVolumeSubScreenController_BoundingVolumeType::ORIENTEDBOUNDINGBOX);
		} else
		if (dynamic_cast< ConvexMesh* >(bv->getBoundingVolume()) != nullptr) {
			modelEditorScreenController->setupConvexMesh(i, bv->getModelMeshFile());
			modelEditorScreenController->selectBoundingVolume(i, EntityBoundingVolumeSubScreenController_BoundingVolumeType::CONVEXMESH);
		}
		modelEditorScreenController->enableBoundingVolume(i);
		modelEditorScreenController->setupModelBoundingVolumeType(entity, i);
	}
}

void EntityBoundingVolumeView::unsetBoundingVolumes()
{
	for (auto i = 0; i < EntityBoundingVolumeSubScreenController::MODEL_BOUNDINGVOLUME_COUNT; i++) {
		modelEditorScreenController->disableBoundingVolume(i);
	}
}

void EntityBoundingVolumeView::selectBoundingVolumeType(int32_t idx, int32_t bvTypeId)
{
	switch (bvTypeId) {
	case 0:
		modelEditorScreenController->selectBoundingVolume(idx, EntityBoundingVolumeSubScreenController_BoundingVolumeType::NONE);
		break;
	case 1:
		modelEditorScreenController->selectBoundingVolume(idx, EntityBoundingVolumeSubScreenController_BoundingVolumeType::SPHERE);
		break;
	case 2:
		modelEditorScreenController->selectBoundingVolume(idx, EntityBoundingVolumeSubScreenController_BoundingVolumeType::CAPSULE);
		break;
	case 3:
		modelEditorScreenController->selectBoundingVolume(idx, EntityBoundingVolumeSubScreenController_BoundingVolumeType::BOUNDINGBOX);
		break;
	case 4:
		modelEditorScreenController->selectBoundingVolume(idx, EntityBoundingVolumeSubScreenController_BoundingVolumeType::ORIENTEDBOUNDINGBOX);
		break;
	case 5:
		modelEditorScreenController->selectBoundingVolume(idx, EntityBoundingVolumeSubScreenController_BoundingVolumeType::CONVEXMESH);
		break;
	}

}

void EntityBoundingVolumeView::updateModelBoundingVolume(LevelEditorEntity* entity, int32_t idx)
{
	auto entityBoundingVolume = entity->getBoundingVolumeAt(idx);
	auto modelBoundingVolumeEntityId = EntityBoundingVolumeSubScreenController::MODEL_BOUNDINGVOLUME_IDS[idx];
	auto modelEntity = engine->getEntity("model");
	auto modelBoundingVolumeEntity = engine->getEntity(modelBoundingVolumeEntityId);
	if (modelBoundingVolumeEntity != nullptr) {
		engine->removeEntity(modelBoundingVolumeEntityId);
	}
	if (entityBoundingVolume->getModel() == nullptr)
		return;

	modelBoundingVolumeEntity = new Object3D(modelBoundingVolumeEntityId, entityBoundingVolume->getModel());
	modelBoundingVolumeEntity->setEnabled(false);
	if (modelEntity != nullptr) {
		modelBoundingVolumeEntity->getScale().set(modelEntity->getScale());
		modelBoundingVolumeEntity->update();
	}
	engine->addEntity(modelBoundingVolumeEntity);
}

void EntityBoundingVolumeView::applyBoundingVolumeNone(LevelEditorEntity* entity, int32_t idx)
{
	if (entity == nullptr)
		return;

	auto entityBoundingVolume = entity->getBoundingVolumeAt(idx);
	entityBoundingVolume->setupNone();
	updateModelBoundingVolume(entity, idx);
}

void EntityBoundingVolumeView::applyBoundingVolumeSphere(LevelEditorEntity* entity, int32_t idx, const Vector3& center, float radius)
{
	if (entity == nullptr)
		return;

	auto entityBoundingVolume = entity->getBoundingVolumeAt(idx);
	entityBoundingVolume->setupSphere(center, radius);
	updateModelBoundingVolume(entity, idx);
}

void EntityBoundingVolumeView::applyBoundingVolumeCapsule(LevelEditorEntity* entity, int32_t idx, const Vector3& a, const Vector3& b, float radius)
{
	if (entity == nullptr)
		return;

	auto entityBoundingVolume = entity->getBoundingVolumeAt(idx);
	entityBoundingVolume->setupCapsule(a, b, radius);
	updateModelBoundingVolume(entity, idx);
}

void EntityBoundingVolumeView::applyBoundingVolumeAabb(LevelEditorEntity* entity, int32_t idx, const Vector3& min, const Vector3& max)
{
	if (entity == nullptr)
		return;

	auto entityBoundingVolume = entity->getBoundingVolumeAt(idx);
	entityBoundingVolume->setupAabb(min, max);
	updateModelBoundingVolume(entity, idx);
}

void EntityBoundingVolumeView::applyBoundingVolumeObb(LevelEditorEntity* entity, int32_t idx, const Vector3& center, const Vector3& axis0, const Vector3& axis1, const Vector3& axis2, const Vector3& halfExtension)
{
	if (entity == nullptr)
		return;

	auto entityBoundingVolume = entity->getBoundingVolumeAt(idx);
	entityBoundingVolume->setupObb(center, axis0, axis1, axis2, halfExtension);
	updateModelBoundingVolume(entity, idx);
}

void EntityBoundingVolumeView::applyBoundingVolumeConvexMesh(LevelEditorEntity* entity, int32_t idx, const string& fileName)
{
	if (entity == nullptr)
		return;

	auto entityBoundingVolume = entity->getBoundingVolumeAt(idx);
	entityBoundingVolume->setupConvexMesh(
		FileSystem::getInstance()->getPathName(fileName),
		FileSystem::getInstance()->getFileName(fileName)
	);
	updateModelBoundingVolume(entity, idx);
}

void EntityBoundingVolumeView::setTerrainMesh(LevelEditorEntity* entity) {
	if (entity == nullptr)
		return;

	modelEditorScreenController->setTerrainMesh(entity);
}

void EntityBoundingVolumeView::unsetTerrainMesh() {
	modelEditorScreenController->unsetTerrainMesh();
}
