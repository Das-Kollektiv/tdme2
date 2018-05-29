#include <tdme/tools/leveleditor/logic/Level.h>

#include <vector>
#include <map>
#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/Object3DRenderGroup.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/LODObject3D.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/Object3DModel.h>
#include <tdme/engine/ObjectParticleSystemEntity.h>
#include <tdme/engine/PointsParticleSystemEntity.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Color4Base.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/physics/RigidBody.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/primitives/ConvexMesh.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/primitives/PrimitiveModel.h>
#include <tdme/engine/primitives/Sphere.h>
#include <tdme/engine/primitives/TerrainMesh.h>
#include <tdme/engine/subsystems/particlesystem/BoundingBoxParticleEmitter.h>
#include <tdme/engine/subsystems/particlesystem/CircleParticleEmitter.h>
#include <tdme/engine/subsystems/particlesystem/CircleParticleEmitterPlaneVelocity.h>
#include <tdme/engine/subsystems/particlesystem/PointParticleEmitter.h>
#include <tdme/engine/subsystems/particlesystem/SphereParticleEmitter.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/tools/shared/model/LevelEditorEntity_EntityType.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorEntityBoundingVolume.h>
#include <tdme/tools/shared/model/LevelEditorEntityModel.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_CircleParticleEmitter.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_Emitter.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_ObjectParticleSystem.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_PointParticleEmitter.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_PointParticleSystem.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_SphereParticleEmitter.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem_Type.h>
#include <tdme/tools/shared/model/LevelEditorEntityParticleSystem.h>
#include <tdme/tools/shared/model/LevelEditorEntityPhysics.h>
#include <tdme/tools/shared/model/LevelEditorEntityPhysics_BodyType.h>
#include <tdme/tools/shared/model/LevelEditorLevel.h>
#include <tdme/tools/shared/model/LevelEditorLight.h>
#include <tdme/tools/shared/model/LevelEditorObject.h>
#include <tdme/tools/shared/model/ModelProperties.h>
#include <tdme/tools/shared/model/PropertyModelClass.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/StringUtils.h>
#include <tdme/utils/Console.h>

using std::map;
using std::vector;
using std::string;
using std::to_string;

using tdme::tools::leveleditor::logic::Level;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::Object3DRenderGroup;
using tdme::engine::Light;
using tdme::engine::LODObject3D;
using tdme::engine::Object3D;
using tdme::engine::Object3DModel;
using tdme::engine::ObjectParticleSystemEntity;
using tdme::engine::PointsParticleSystemEntity;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::model::Color4Base;
using tdme::engine::model::Model;
using tdme::engine::physics::RigidBody;
using tdme::engine::physics::World;
using tdme::engine::primitives::ConvexMesh;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::PrimitiveModel;
using tdme::engine::primitives::Sphere;
using tdme::engine::primitives::TerrainMesh;
using tdme::engine::subsystems::particlesystem::BoundingBoxParticleEmitter;
using tdme::engine::subsystems::particlesystem::CircleParticleEmitter;
using tdme::engine::subsystems::particlesystem::CircleParticleEmitterPlaneVelocity;
using tdme::engine::subsystems::particlesystem::PointParticleEmitter;
using tdme::engine::subsystems::particlesystem::SphereParticleEmitter;
using tdme::math::Math;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::tools::shared::model::LevelEditorEntity_EntityType;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorEntityBoundingVolume;
using tdme::tools::shared::model::LevelEditorEntityModel;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_BoundingBoxParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_CircleParticleEmitterPlaneVelocity;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Emitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_ObjectParticleSystem;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_PointParticleSystem;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_SphereParticleEmitter;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem_Type;
using tdme::tools::shared::model::LevelEditorEntityParticleSystem;
using tdme::tools::shared::model::LevelEditorEntityPhysics;
using tdme::tools::shared::model::LevelEditorEntityPhysics_BodyType;
using tdme::tools::shared::model::LevelEditorLevel;
using tdme::tools::shared::model::LevelEditorLight;
using tdme::tools::shared::model::LevelEditorObject;
using tdme::tools::shared::model::ModelProperties;
using tdme::tools::shared::model::PropertyModelClass;
using tdme::utils::MutableString;
using tdme::utils::StringUtils;
using tdme::utils::Console;

void Level::setLight(Engine* engine, LevelEditorLevel* level, const Vector3& translation)
{
	for (auto i = 0; i < level->getLightCount(); i++) {
		engine->getLightAt(i)->setAmbient(Color4(level->getLightAt(i)->getAmbient()));
		engine->getLightAt(i)->setDiffuse(Color4(level->getLightAt(i)->getDiffuse()));
		engine->getLightAt(i)->setSpecular(Color4(level->getLightAt(i)->getSpecular()));
		engine->getLightAt(i)->setSpotDirection(level->getLightAt(i)->getSpotDirection());
		engine->getLightAt(i)->setSpotExponent(level->getLightAt(i)->getSpotExponent());
		engine->getLightAt(i)->setSpotCutOff(level->getLightAt(i)->getSpotCutOff());
		engine->getLightAt(i)->setConstantAttenuation(level->getLightAt(i)->getConstantAttenuation());
		engine->getLightAt(i)->setLinearAttenuation(level->getLightAt(i)->getLinearAttenuation());
		engine->getLightAt(i)->setQuadraticAttenuation(level->getLightAt(i)->getQuadraticAttenuation());
		engine->getLightAt(i)->setEnabled(level->getLightAt(i)->isEnabled());
		engine->getLightAt(i)->setPosition(
			Vector4(
				level->getLightAt(i)->getPosition().getX() + translation.getX(),
				level->getLightAt(i)->getPosition().getY() + translation.getY(),
				level->getLightAt(i)->getPosition().getZ() + translation.getZ(),
				1.0f
			)
		);
	}
}

Entity* Level::createParticleSystem(LevelEditorEntityParticleSystem* particleSystem, const string& id, bool enableDynamicShadows)
{
	ParticleEmitter* engineEmitter = nullptr;
	{
		auto v = particleSystem->getEmitter();
		if (v == LevelEditorEntityParticleSystem_Emitter::NONE) {
			return nullptr;
		} else
		if (v == LevelEditorEntityParticleSystem_Emitter::POINT_PARTICLE_EMITTER) {
			auto emitter = particleSystem->getPointParticleEmitter();
			engineEmitter = new PointParticleEmitter(emitter->getCount(), emitter->getLifeTime(), emitter->getLifeTimeRnd(), emitter->getMass(), emitter->getMassRnd(), emitter->getPosition(), emitter->getVelocity(), emitter->getVelocityRnd(), emitter->getColorStart(), emitter->getColorEnd());
		} else
		if (v == LevelEditorEntityParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) {
			auto emitter = particleSystem->getBoundingBoxParticleEmitters();
			engineEmitter = new BoundingBoxParticleEmitter(emitter->getCount(), emitter->getLifeTime(), emitter->getLifeTimeRnd(), emitter->getMass(), emitter->getMassRnd(), new OrientedBoundingBox(emitter->getObbCenter(), emitter->getObbAxis0(), emitter->getObbAxis1(), emitter->getObbAxis2(), emitter->getObbHalfextension()), emitter->getVelocity(), emitter->getVelocityRnd(), emitter->getColorStart(), emitter->getColorEnd());
		} else
		if (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) {
			auto emitter = particleSystem->getCircleParticleEmitter();
			engineEmitter = new CircleParticleEmitter(emitter->getCount(), emitter->getLifeTime(), emitter->getLifeTimeRnd(), emitter->getAxis0(), emitter->getAxis1(), emitter->getCenter(), emitter->getRadius(), emitter->getMass(), emitter->getMassRnd(), emitter->getVelocity(), emitter->getVelocityRnd(), emitter->getColorStart(), emitter->getColorEnd());
		} else
		if (v == LevelEditorEntityParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) {
			auto emitter = particleSystem->getCircleParticleEmitterPlaneVelocity();
			engineEmitter = new CircleParticleEmitterPlaneVelocity(emitter->getCount(), emitter->getLifeTime(), emitter->getLifeTimeRnd(), emitter->getAxis0(), emitter->getAxis1(), emitter->getCenter(), emitter->getRadius(), emitter->getMass(), emitter->getMassRnd(), emitter->getVelocity(), emitter->getVelocityRnd(), emitter->getColorStart(), emitter->getColorEnd());
		} else
		if (v == LevelEditorEntityParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER) {
			auto emitter = particleSystem->getSphereParticleEmitter();
			engineEmitter = new SphereParticleEmitter(emitter->getCount(), emitter->getLifeTime(), emitter->getLifeTimeRnd(), emitter->getMass(), emitter->getMassRnd(), new Sphere(emitter->getCenter(), emitter->getRadius()), emitter->getVelocity(), emitter->getVelocityRnd(), emitter->getColorStart(), emitter->getColorEnd());
		} else {
			Console::println(
				string(
					"Level::createParticleSystem(): unknown particle system emitter '" +
					particleSystem->getEmitter()->getName() +
					"'"
				)
			);
			return nullptr;
		}
	}

	{
		LevelEditorEntityParticleSystem_ObjectParticleSystem* objectParticleSystem;
		LevelEditorEntityParticleSystem_PointParticleSystem* pointParticleSystem;
		{
			auto v = particleSystem->getType();
			if (v == LevelEditorEntityParticleSystem_Type::NONE) {
				return nullptr;
			} else
			if (v == LevelEditorEntityParticleSystem_Type::OBJECT_PARTICLE_SYSTEM) {
				auto objectParticleSystem = particleSystem->getObjectParticleSystem();
				if (objectParticleSystem->getModel() == nullptr) return nullptr;

				return new ObjectParticleSystemEntity(id, objectParticleSystem->getModel(), objectParticleSystem->getScale(), objectParticleSystem->isAutoEmit(), enableDynamicShadows, objectParticleSystem->getMaxCount(), engineEmitter);
			} else
			if (v == LevelEditorEntityParticleSystem_Type::POINT_PARTICLE_SYSTEM) {
				auto pointParticleSystem = particleSystem->getPointParticleSystem();
				return new PointsParticleSystemEntity(id, false, engineEmitter, pointParticleSystem->getMaxPoints(), pointParticleSystem->isAutoEmit());
			} else {
				Console::println(
					string(
						"Level::createParticleSystem(): unknown particle system type '" +
						particleSystem->getType()->getName() +
						"'"
					)
				);
				return nullptr;
			}
		}
	}

}

Entity* Level::createEntity(LevelEditorObject* levelEditorObject) {
	Entity* entity = nullptr;

	// objects
	if (levelEditorObject->getEntity()->getModel() != nullptr) {
		auto lodLevel2 = levelEditorObject->getEntity()->getLODLevel2();
		auto lodLevel3 = levelEditorObject->getEntity()->getLODLevel3();
		// with LOD
		if (lodLevel2 != nullptr) {
			entity = new LODObject3D(
				levelEditorObject->getId(),
				levelEditorObject->getEntity()->getModel(),
				lodLevel2->getType(),
				lodLevel2->getMinDistance(),
				lodLevel2->getModel(),
				lodLevel3 != nullptr?lodLevel3->getType():LODObject3D::LODLEVELTYPE_NONE,
				lodLevel3 != nullptr?lodLevel3->getMinDistance():0.0f,
				lodLevel3 != nullptr?lodLevel3->getModel():nullptr,
				lodLevel2->getPlaneRotationY(),
				lodLevel3 != nullptr?lodLevel3->getPlaneRotationY():0.0f
			);
			auto lodObject = dynamic_cast<LODObject3D*>(entity);
			lodObject->setEffectColorAddLOD2(lodLevel2->getColorAdd());
			lodObject->setEffectColorMulLOD2(lodLevel2->getColorMul());
			if (lodLevel3 != nullptr) {
				lodObject->setEffectColorAddLOD3(lodLevel3->getColorAdd());
				lodObject->setEffectColorMulLOD3(lodLevel3->getColorMul());
			}
		} else {
			// single
			entity = new Object3D(
				levelEditorObject->getId(),
				levelEditorObject->getEntity()->getModel()
			);
		}
	} else
	// particle system
	if (levelEditorObject->getEntity()->getType() == LevelEditorEntity_EntityType::PARTICLESYSTEM) {
		entity = createParticleSystem(
			levelEditorObject->getEntity()->getParticleSystem(),
			levelEditorObject->getId(),
			false
		);
	}

	//
	if (entity != nullptr) entity->fromTransformations(levelEditorObject->getTransformations());
	return entity;
}

void Level::addLevel(Engine* engine, LevelEditorLevel* level, bool addEmpties, bool addTrigger, bool pickable, bool enable, const Vector3& translation)
{
	map<string, map<string, vector<Object3D*>>> renderGroupEntitiesByModelAndPartition;
	for (auto i = 0; i < level->getObjectCount(); i++) {
		auto object = level->getObjectAt(i);
		auto properties = object->getTotalProperties();

		if (addEmpties == false && object->getEntity()->getType() == LevelEditorEntity_EntityType::EMPTY) continue;
		if (addTrigger == false && object->getEntity()->getType() == LevelEditorEntity_EntityType::TRIGGER) continue;

		Entity* entity = createEntity(object);
		if (entity == nullptr) continue;

		entity->setTranslation(entity->getTranslation().clone().add(translation));
		entity->setPickable(pickable);
		auto shadowingProperty = properties->getProperty("shadowing");
		auto omitShadowing = shadowingProperty != nullptr && StringUtils::equalsIgnoreCase(shadowingProperty->getValue(), "false");
		entity->setDynamicShadowingEnabled(object->getEntity()->isDynamicShadowing());
		if (object->getEntity()->getType() == LevelEditorEntity_EntityType::EMPTY) {
			entity->setScale(Vector3(Math::sign(entity->getScale().getX()), Math::sign(entity->getScale().getY()), Math::sign(entity->getScale().getZ())));
		}
		entity->update();
		entity->setEnabled(enable);

		if (dynamic_cast<Object3D*>(entity) != nullptr &&
			object->getEntity()->isRenderGroups() == true) {
			auto minX = entity->getBoundingBoxTransformed()->getMin().getX();
			auto minY = entity->getBoundingBoxTransformed()->getMin().getY();
			auto minZ = entity->getBoundingBoxTransformed()->getMin().getZ();
			int partitionX = (int)(minX / 32.0f);
			int partitionY = (int)(minY / 32.0f);
			int partitionZ = (int)(minZ / 32.0f);
			renderGroupEntitiesByModelAndPartition[object->getEntity()->getModel()->getId()][to_string(partitionX) + "," + to_string(partitionY) + "," + to_string(partitionZ)].push_back(dynamic_cast<Object3D*>(entity));
		} else {
			engine->addEntity(entity);
		}
	}

	for (auto itModel: renderGroupEntitiesByModelAndPartition) {
		for (auto itPartition: itModel.second) {
			auto object3DRenderGroup = new Object3DRenderGroup("tdme.rendergroup" + itModel.first + "." + itPartition.first);
			for (auto object: itPartition.second) {
				object3DRenderGroup->addObject(object);
			}
			object3DRenderGroup->update();
			engine->addEntity(object3DRenderGroup);
		}
	}
}

RigidBody* Level::createRigidBody(World* world, LevelEditorObject* levelEditorObject) {
	if (levelEditorObject->getEntity()->getType() == LevelEditorEntity_EntityType::EMPTY) return nullptr;

	if (levelEditorObject->getEntity()->getType() == LevelEditorEntity_EntityType::TRIGGER) {
		vector<BoundingVolume*> boundingVolumes;
		for (auto j = 0; j < levelEditorObject->getEntity()->getBoundingVolumeCount(); j++) {
			auto entityBv = levelEditorObject->getEntity()->getBoundingVolumeAt(j);
			boundingVolumes.push_back(entityBv->getBoundingVolume());
		}
		return world->addCollisionBody(
			levelEditorObject->getId(),
			true,
			RIGIDBODY_TYPEID_TRIGGER,
			levelEditorObject->getTransformations(),
			boundingVolumes
		);
	} else
	if (levelEditorObject->getEntity()->getType() == LevelEditorEntity_EntityType::MODEL &&
		levelEditorObject->getEntity()->getModelSettings()->isTerrainMesh() == true) {
		Object3DModel terrainModel(levelEditorObject->getEntity()->getModel());
		auto terrainMesh = new TerrainMesh(&terrainModel, levelEditorObject->getTransformations());
		if (levelEditorObject->getEntity()->getPhysics()->getType() == LevelEditorEntityPhysics_BodyType::COLLISION_BODY) {
			return world->addCollisionBody(
				levelEditorObject->getId(),
				true,
				RIGIDBODY_TYPEID_COLLISION,
				Transformations(),
				{terrainMesh}
			);
		} else
		if (levelEditorObject->getEntity()->getPhysics()->getType() == LevelEditorEntityPhysics_BodyType::STATIC_RIGIDBODY) {
			return world->addStaticRigidBody(
				levelEditorObject->getId(),
				true,
				RIGIDBODY_TYPEID_STATIC,
				Transformations(),
				levelEditorObject->getEntity()->getPhysics()->getFriction(),
				{terrainMesh}
			);
		} else
		if (levelEditorObject->getEntity()->getPhysics()->getType() == LevelEditorEntityPhysics_BodyType::DYNAMIC_RIGIDBODY) {
			return world->addRigidBody(
				levelEditorObject->getId(),
				true,
				RIGIDBODY_TYPEID_DYNAMIC,
				Transformations(),
				levelEditorObject->getEntity()->getPhysics()->getRestitution(),
				levelEditorObject->getEntity()->getPhysics()->getFriction(),
				levelEditorObject->getEntity()->getPhysics()->getMass(),
				levelEditorObject->getEntity()->getPhysics()->getInertiaTensor(),
				{terrainMesh}
			);
		}
	} else {
		vector<BoundingVolume*> boundingVolumes;
		for (auto j = 0; j < levelEditorObject->getEntity()->getBoundingVolumeCount(); j++) {
			auto entityBv = levelEditorObject->getEntity()->getBoundingVolumeAt(j);
			boundingVolumes.push_back(entityBv->getBoundingVolume());
		}
		if (levelEditorObject->getEntity()->getPhysics()->getType() == LevelEditorEntityPhysics_BodyType::COLLISION_BODY) {
			return world->addCollisionBody(
				levelEditorObject->getId(),
				true,
				RIGIDBODY_TYPEID_COLLISION,
				levelEditorObject->getTransformations(),
				boundingVolumes
			);
		} else
		if (levelEditorObject->getEntity()->getPhysics()->getType() == LevelEditorEntityPhysics_BodyType::STATIC_RIGIDBODY) {
			return world->addStaticRigidBody(
				levelEditorObject->getId(),
				true,
				RIGIDBODY_TYPEID_STATIC,
				levelEditorObject->getTransformations(),
				levelEditorObject->getEntity()->getPhysics()->getFriction(),
				boundingVolumes
			);
		} else
		if (levelEditorObject->getEntity()->getPhysics()->getType() == LevelEditorEntityPhysics_BodyType::DYNAMIC_RIGIDBODY) {
			return world->addRigidBody(
				levelEditorObject->getId(),
				true,
				RIGIDBODY_TYPEID_DYNAMIC,
				levelEditorObject->getTransformations(),
				levelEditorObject->getEntity()->getPhysics()->getRestitution(),
				levelEditorObject->getEntity()->getPhysics()->getFriction(),
				levelEditorObject->getEntity()->getPhysics()->getMass(),
				levelEditorObject->getEntity()->getPhysics()->getInertiaTensor(),
				boundingVolumes
			);
		}
	}
	return nullptr;
}

void Level::addLevel(World* world, LevelEditorLevel* level, vector<RigidBody*>& rigidBodies, bool enable, const Vector3& translation)
{
	for (auto i = 0; i < level->getObjectCount(); i++) {
		auto levelEditorObject = level->getObjectAt(i);
		auto rigidBody = createRigidBody(world, levelEditorObject);
		if (rigidBody == nullptr) continue;
		if (translation.equals(Vector3()) == false) {
			auto transformations = levelEditorObject->getTransformations();
			transformations.setTranslation(transformations.getTranslation().clone().add(translation));
			transformations.update();
			rigidBody->fromTransformations(transformations);
		}
		rigidBody->setEnabled(enable);
		rigidBodies.push_back(rigidBody);
	}
}

void Level::disableLevel(Engine* engine, LevelEditorLevel* level)
{
	for (auto i = 0; i < level->getObjectCount(); i++) {
		auto object = level->getObjectAt(i);
		auto entity = engine->getEntity(object->getId());
		if (entity == nullptr)
			continue;

		entity->setEnabled(false);
	}
}

void Level::disableLevel(World* world, vector<RigidBody*>& rigidBodies)
{
	for (auto rigidBody: rigidBodies) {
		rigidBody->setEnabled(false);
	}
}

void Level::enableLevel(Engine* engine, LevelEditorLevel* level, const Vector3& translation)
{
	for (auto i = 0; i < level->getObjectCount(); i++) {
		auto object = level->getObjectAt(i);
		auto entity = engine->getEntity(object->getId());
		if (entity == nullptr)
			continue;

		entity->fromTransformations(object->getTransformations());
		entity->setTranslation(entity->getTranslation().clone().add(translation));
		if (object->getEntity()->getType() == LevelEditorEntity_EntityType::EMPTY) {
			entity->setScale(Vector3(Math::sign(entity->getScale().getX()), Math::sign(entity->getScale().getY()), Math::sign(entity->getScale().getZ())));
		}
		entity->update();
		entity->setEnabled(true);
	}
}

void Level::enableLevel(World* world, LevelEditorLevel* level, vector<RigidBody*>& rigidBodies, const Vector3& translation)
{
	MutableString compareMutableString;
	Transformations transformations;
	for (auto i = 0; i < level->getObjectCount(); i++) {
		auto object = level->getObjectAt(i);
		for (auto j = 0; j < object->getEntity()->getBoundingVolumeCount(); j++) {
			for (auto k = 0; k < rigidBodies.size(); k++) {
				auto rigidBody = rigidBodies[k];
				compareMutableString.set(object->getId());
				compareMutableString.append(".bv.");
				compareMutableString.append(j);
				if (compareMutableString.equals(rigidBody->getId()) == false)
					continue;

				transformations.fromTransformations(object->getTransformations());
				transformations.setTranslation(transformations.getTranslation().clone().add(translation));
				transformations.update();
				rigidBody->fromTransformations(transformations);
				rigidBody->setEnabled(true);
			}
		}
	}
}

