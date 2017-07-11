// Generated from /tdme/src/tdme/tools/shared/views/EntityBoundingVolumeView.java
#include <tdme/tools/shared/views/EntityBoundingVolumeView.h>

#include <java/io/Serializable.h>
#include <java/lang/ArrayStoreException.h>
#include <java/lang/CharSequence.h>
#include <java/lang/ClassCastException.h>
#include <java/lang/Comparable.h>
#include <java/lang/Math.h>
#include <java/lang/String.h>
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
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController_BoundingVolumeType.h>
#include <tdme/tools/shared/controller/EntityBoundingVolumeSubScreenController.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityBoundingVolume.h>
#include <tdme/tools/shared/views/PopUps.h>
#include <Array.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::tools::shared::views::EntityBoundingVolumeView;
using java::io::Serializable;
using java::lang::ArrayStoreException;
using java::lang::CharSequence;
using java::lang::ClassCastException;
using java::lang::Comparable;
using java::lang::Math;
using java::lang::String;
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
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_BoundingVolumeType;
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityBoundingVolume;
using tdme::tools::shared::views::PopUps;

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
namespace math {
typedef ::SubArray< ::tdme::math::Vector3, ::java::lang::ObjectArray > Vector3Array;
}  // namespace math
}  // namespace tdme

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

EntityBoundingVolumeView::EntityBoundingVolumeView(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

EntityBoundingVolumeView::EntityBoundingVolumeView(EntityBoundingVolumeSubScreenController* modelViewerScreenController, PopUps* popUps) 
	: EntityBoundingVolumeView(*static_cast< ::default_init_tag* >(0))
{
	ctor(modelViewerScreenController,popUps);
}

void EntityBoundingVolumeView::ctor(EntityBoundingVolumeSubScreenController* modelViewerScreenController, PopUps* popUps)
{
	super::ctor();
	this->engine = Engine::getInstance();
	this->popUps = popUps;
	this->modelViewerScreenController = modelViewerScreenController;
}

PopUps* EntityBoundingVolumeView::getPopUpsViews()
{
	return popUps;
}

void EntityBoundingVolumeView::initialize()
{
	for (auto i = 0; i < EntityBoundingVolumeSubScreenController::MODEL_BOUNDINGVOLUME_COUNT; i++) {
		modelViewerScreenController->setupBoundingVolumeTypes(i, new StringArray({
			u"None"_j,
			u"Sphere"_j,
			u"Capsule"_j,
			u"Bounding Box"_j,
			u"Oriented Bounding Box"_j,
			u"Convex Mesh"_j
		}));
		modelViewerScreenController->selectBoundingVolume(i, EntityBoundingVolumeSubScreenController_BoundingVolumeType::NONE);
	}
}

void EntityBoundingVolumeView::resetBoundingVolume(LevelEditorEntity* entity, int32_t idx)
{
	BoundingBox* aabb = nullptr;
	if (entity->getModel() != nullptr) {
		aabb = entity->getModel()->getBoundingBox();
	} else {
		aabb = new BoundingBox(new Vector3(-0.5f, 0.0f, -0.5f), new Vector3(0.5f, 3.0f, 0.5f));
	}
	auto obb = new OrientedBoundingBox(aabb);
	modelViewerScreenController->setupSphere(idx, obb->getCenter(), obb->getHalfExtension()->computeLength());
{
		auto a = new Vector3();
		auto b = new Vector3();
		auto radius = 0.0f;
		auto halfExtensionXYZ = obb->getHalfExtension()->getArray();
		if ((*halfExtensionXYZ)[0] > (*halfExtensionXYZ)[1] && (*halfExtensionXYZ)[0] > (*halfExtensionXYZ)[2]) {
			radius = static_cast< float >(Math::sqrt((*halfExtensionXYZ)[1] * (*halfExtensionXYZ)[1] + (*halfExtensionXYZ)[2] * (*halfExtensionXYZ)[2]));
			a->set((*obb->getAxes())[0]);
			a->scale(-((*halfExtensionXYZ)[0] - radius));
			a->add(obb->getCenter());
			b->set((*obb->getAxes())[0]);
			b->scale(+((*halfExtensionXYZ)[0] - radius));
			b->add(obb->getCenter());
		} else if ((*halfExtensionXYZ)[1] > (*halfExtensionXYZ)[0] && (*halfExtensionXYZ)[1] > (*halfExtensionXYZ)[2]) {
			radius = static_cast< float >(Math::sqrt((*halfExtensionXYZ)[0] * (*halfExtensionXYZ)[0] + (*halfExtensionXYZ)[2] * (*halfExtensionXYZ)[2]));
			a->set((*obb->getAxes())[1]);
			a->scale(-((*halfExtensionXYZ)[1] - radius));
			a->add(obb->getCenter());
			b->set((*obb->getAxes())[1]);
			b->scale(+((*halfExtensionXYZ)[1] - radius));
			b->add(obb->getCenter());
		} else {
			radius = static_cast< float >(Math::sqrt((*halfExtensionXYZ)[0] * (*halfExtensionXYZ)[0] + (*halfExtensionXYZ)[1] * (*halfExtensionXYZ)[1]));
			a->set((*obb->getAxes())[2]);
			a->scale(-((*halfExtensionXYZ)[2] - radius));
			a->add(obb->getCenter());
			b->set((*obb->getAxes())[2]);
			b->scale(+((*halfExtensionXYZ)[2] - radius));
			b->add(obb->getCenter());
		}
		modelViewerScreenController->setupCapsule(idx, a, b, radius);
	}

	modelViewerScreenController->setupBoundingBox(idx, aabb->getMin(), aabb->getMax());
	modelViewerScreenController->setupOrientedBoundingBox(idx, obb->getCenter(), (*obb->getAxes())[0], (*obb->getAxes())[1], (*obb->getAxes())[2], obb->getHalfExtension());
	modelViewerScreenController->selectBoundingVolume(idx, EntityBoundingVolumeSubScreenController_BoundingVolumeType::NONE);
}

void EntityBoundingVolumeView::setBoundingVolumes(LevelEditorEntity* entity)
{
	for (auto i = 0; i < EntityBoundingVolumeSubScreenController::MODEL_BOUNDINGVOLUME_COUNT; i++) {
		resetBoundingVolume(entity, i);
	}
	for (auto i = 0; i < entity->getBoundingVolumeCount(); i++) {
		auto bv = entity->getBoundingVolumeAt(i);
		if (bv == nullptr) {
			modelViewerScreenController->selectBoundingVolume(i, EntityBoundingVolumeSubScreenController_BoundingVolumeType::NONE);
			continue;
		} else if (dynamic_cast< Sphere* >(bv->getBoundingVolume()) != nullptr) {
			auto sphere = java_cast< Sphere* >(bv->getBoundingVolume());
			modelViewerScreenController->setupSphere(i, sphere->getCenter(), sphere->getRadius());
			modelViewerScreenController->selectBoundingVolume(i, EntityBoundingVolumeSubScreenController_BoundingVolumeType::SPHERE);
		} else if (dynamic_cast< Capsule* >(bv->getBoundingVolume()) != nullptr) {
			auto capsule = java_cast< Capsule* >(bv->getBoundingVolume());
			modelViewerScreenController->setupCapsule(i, capsule->getA(), capsule->getB(), capsule->getRadius());
			modelViewerScreenController->selectBoundingVolume(i, EntityBoundingVolumeSubScreenController_BoundingVolumeType::CAPSULE);
		} else if (dynamic_cast< BoundingBox* >(bv->getBoundingVolume()) != nullptr) {
			auto aabb = java_cast< BoundingBox* >(bv->getBoundingVolume());
			modelViewerScreenController->setupBoundingBox(i, aabb->getMin(), aabb->getMax());
			modelViewerScreenController->selectBoundingVolume(i, EntityBoundingVolumeSubScreenController_BoundingVolumeType::BOUNDINGBOX);
		} else if (dynamic_cast< OrientedBoundingBox* >(bv->getBoundingVolume()) != nullptr) {
			auto obb = java_cast< OrientedBoundingBox* >(bv->getBoundingVolume());
			modelViewerScreenController->setupOrientedBoundingBox(i, obb->getCenter(), (*obb->getAxes())[0], (*obb->getAxes())[1], (*obb->getAxes())[2], obb->getHalfExtension());
			modelViewerScreenController->selectBoundingVolume(i, EntityBoundingVolumeSubScreenController_BoundingVolumeType::ORIENTEDBOUNDINGBOX);
		} else if (dynamic_cast< ConvexMesh* >(bv->getBoundingVolume()) != nullptr) {
			modelViewerScreenController->setupConvexMesh(i, bv->getModelMeshFile());
			modelViewerScreenController->selectBoundingVolume(i, EntityBoundingVolumeSubScreenController_BoundingVolumeType::CONVEXMESH);
		}
		modelViewerScreenController->enableBoundingVolume(i);
		modelViewerScreenController->setupModelBoundingVolumeType(entity, i);
	}
}

void EntityBoundingVolumeView::unsetBoundingVolumes()
{
	for (auto i = 0; i < EntityBoundingVolumeSubScreenController::MODEL_BOUNDINGVOLUME_COUNT; i++) {
		modelViewerScreenController->disableBoundingVolume(i);
	}
}

void EntityBoundingVolumeView::selectBoundingVolumeType(int32_t idx, int32_t bvTypeId)
{
	switch (bvTypeId) {
	case 0:
		modelViewerScreenController->selectBoundingVolume(idx, EntityBoundingVolumeSubScreenController_BoundingVolumeType::NONE);
		break;
	case 1:
		modelViewerScreenController->selectBoundingVolume(idx, EntityBoundingVolumeSubScreenController_BoundingVolumeType::SPHERE);
		break;
	case 2:
		modelViewerScreenController->selectBoundingVolume(idx, EntityBoundingVolumeSubScreenController_BoundingVolumeType::CAPSULE);
		break;
	case 3:
		modelViewerScreenController->selectBoundingVolume(idx, EntityBoundingVolumeSubScreenController_BoundingVolumeType::BOUNDINGBOX);
		break;
	case 4:
		modelViewerScreenController->selectBoundingVolume(idx, EntityBoundingVolumeSubScreenController_BoundingVolumeType::ORIENTEDBOUNDINGBOX);
		break;
	case 5:
		modelViewerScreenController->selectBoundingVolume(idx, EntityBoundingVolumeSubScreenController_BoundingVolumeType::CONVEXMESH);
		break;
	}

}

void EntityBoundingVolumeView::updateModelBoundingVolume(LevelEditorEntity* entity, int32_t idx)
{
	auto entityBoundingVolume = entity->getBoundingVolumeAt(idx);
	auto id = (*EntityBoundingVolumeSubScreenController::MODEL_BOUNDINGVOLUME_IDS)[idx];
	auto modelBoundingVolumeObject = engine->getEntity(id);
	if (modelBoundingVolumeObject != nullptr) {
		engine->removeEntity(id);
	}
	if (entityBoundingVolume->getModel() == nullptr)
		return;

	modelBoundingVolumeObject = new Object3D(id, entityBoundingVolume->getModel());
	modelBoundingVolumeObject->setEnabled(false);
	engine->addEntity(modelBoundingVolumeObject);
}

void EntityBoundingVolumeView::applyBoundingVolumeNone(LevelEditorEntity* entity, int32_t idx)
{
	if (entity == nullptr)
		return;

	auto entityBoundingVolume = entity->getBoundingVolumeAt(idx);
	entityBoundingVolume->setupNone();
	updateModelBoundingVolume(entity, idx);
}

void EntityBoundingVolumeView::applyBoundingVolumeSphere(LevelEditorEntity* entity, int32_t idx, Vector3* center, float radius)
{
	if (entity == nullptr)
		return;

	auto entityBoundingVolume = entity->getBoundingVolumeAt(idx);
	entityBoundingVolume->setupSphere(center, radius);
	updateModelBoundingVolume(entity, idx);
}

void EntityBoundingVolumeView::applyBoundingVolumeCapsule(LevelEditorEntity* entity, int32_t idx, Vector3* a, Vector3* b, float radius)
{
	if (entity == nullptr)
		return;

	auto entityBoundingVolume = entity->getBoundingVolumeAt(idx);
	entityBoundingVolume->setupCapsule(a, b, radius);
	updateModelBoundingVolume(entity, idx);
}

void EntityBoundingVolumeView::applyBoundingVolumeAabb(LevelEditorEntity* entity, int32_t idx, Vector3* min, Vector3* max)
{
	if (entity == nullptr)
		return;

	auto entityBoundingVolume = entity->getBoundingVolumeAt(idx);
	entityBoundingVolume->setupAabb(min, max);
	updateModelBoundingVolume(entity, idx);
}

void EntityBoundingVolumeView::applyBoundingVolumeObb(LevelEditorEntity* entity, int32_t idx, Vector3* center, Vector3* axis0, Vector3* axis1, Vector3* axis2, Vector3* halfExtension)
{
	if (entity == nullptr)
		return;

	auto entityBoundingVolume = entity->getBoundingVolumeAt(idx);
	entityBoundingVolume->setupObb(center, axis0, axis1, axis2, halfExtension);
	updateModelBoundingVolume(entity, idx);
}

void EntityBoundingVolumeView::applyBoundingVolumeConvexMesh(LevelEditorEntity* entity, int32_t idx, String* fileName)
{
	if (entity == nullptr)
		return;

	auto entityBoundingVolume = entity->getBoundingVolumeAt(idx);
	entityBoundingVolume->setupConvexMesh(
		_FileSystem::getInstance()->getPathName(fileName),
		_FileSystem::getInstance()->getFileName(fileName)
	);
	updateModelBoundingVolume(entity, idx);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* EntityBoundingVolumeView::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.tools.shared.views.EntityBoundingVolumeView", 48);
    return c;
}

java::lang::Class* EntityBoundingVolumeView::getClass0()
{
	return class_();
}

