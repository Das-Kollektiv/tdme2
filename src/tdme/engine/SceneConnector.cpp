#include <tdme/engine/SceneConnector.h>

#if defined(_WIN32) && defined(_MSC_VER)
	#pragma warning(disable:4503)
#endif

#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/audio/Audio.h>
#include <tdme/audio/Sound.h>
#include <tdme/engine/fileio/models/ModelReader.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/fileio/ProgressCallback.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/physics/Body.h>
#include <tdme/engine/physics/BodyHierarchy.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/primitives/ConvexMesh.h>
#include <tdme/engine/primitives/HeightMap.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/primitives/Sphere.h>
#include <tdme/engine/primitives/TerrainMesh.h>
#include <tdme/engine/prototype/BaseProperties.h>
#include <tdme/engine/prototype/BaseProperty.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/prototype/Prototype_Type.h>
#include <tdme/engine/prototype/PrototypeAudio.h>
#include <tdme/engine/prototype/PrototypeBoundingVolume.h>
#include <tdme/engine/prototype/PrototypeDecal.h>
#include <tdme/engine/prototype/PrototypeImposterLOD.h>
#include <tdme/engine/prototype/PrototypeLODLevel.h>
#include <tdme/engine/prototype/PrototypeParticleSystem.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_BoundingBoxParticleEmitter.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_CircleParticleEmitter.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_CircleParticleEmitterPlaneVelocity.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_Emitter.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_FogParticleSystem.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_ObjectParticleSystem.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_PointParticleEmitter.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_PointParticleSystem.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_SphereParticleEmitter.h>
#include <tdme/engine/prototype/PrototypeParticleSystem_Type.h>
#include <tdme/engine/prototype/PrototypePhysics.h>
#include <tdme/engine/prototype/PrototypePhysics_BodyType.h>
#include <tdme/engine/prototype/PrototypeTerrain.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/engine/scene/SceneEntity.h>
#include <tdme/engine/scene/SceneLibrary.h>
#include <tdme/engine/scene/SceneLight.h>
#include <tdme/engine/subsystems/particlesystem/BoundingBoxParticleEmitter.h>
#include <tdme/engine/subsystems/particlesystem/CircleParticleEmitter.h>
#include <tdme/engine/subsystems/particlesystem/CircleParticleEmitterPlaneVelocity.h>
#include <tdme/engine/subsystems/particlesystem/PointParticleEmitter.h>
#include <tdme/engine/subsystems/particlesystem/SphereParticleEmitter.h>
#include <tdme/engine/Decal.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/EntityHierarchy.h>
#include <tdme/engine/EnvironmentMapping.h>
#include <tdme/engine/FogParticleSystem.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/LODObject.h>
#include <tdme/engine/LODObjectImposter.h>
#include <tdme/engine/Object.h>
#include <tdme/engine/ObjectModel.h>
#include <tdme/engine/ObjectParticleSystem.h>
#include <tdme/engine/ObjectRenderGroup.h>
#include <tdme/engine/ParticleSystem.h>
#include <tdme/engine/ParticleSystemGroup.h>
#include <tdme/engine/PointsParticleSystem.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/ModelTools.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/Primitives.h>
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/Terrain.h>

using std::string;
using std::to_string;
using std::unordered_map;
using std::vector;

using tdme::engine::SceneConnector;

using tdme::audio::Audio;
using tdme::audio::Sound;
using tdme::engine::fileio::models::ModelReader;
using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::fileio::ProgressCallback;
using tdme::engine::Color4;
using tdme::engine::model::Model;
using tdme::engine::physics::Body;
using tdme::engine::physics::BodyHierarchy;
using tdme::engine::physics::World;
using tdme::engine::primitives::ConvexMesh;
using tdme::engine::primitives::HeightMap;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::Sphere;
using tdme::engine::primitives::TerrainMesh;
using tdme::engine::prototype::BaseProperties;
using tdme::engine::prototype::BaseProperty;
using tdme::engine::prototype::Prototype;
using tdme::engine::prototype::Prototype_Type;
using tdme::engine::prototype::PrototypeAudio;
using tdme::engine::prototype::PrototypeBoundingVolume;
using tdme::engine::prototype::PrototypeImposterLOD;
using tdme::engine::prototype::PrototypeLODLevel;
using tdme::engine::prototype::PrototypeParticleSystem;
using tdme::engine::prototype::PrototypeParticleSystem_BoundingBoxParticleEmitter;
using tdme::engine::prototype::PrototypeParticleSystem_CircleParticleEmitter;
using tdme::engine::prototype::PrototypeParticleSystem_CircleParticleEmitterPlaneVelocity;
using tdme::engine::prototype::PrototypeParticleSystem_Emitter;
using tdme::engine::prototype::PrototypeParticleSystem_FogParticleSystem;
using tdme::engine::prototype::PrototypeParticleSystem_ObjectParticleSystem;
using tdme::engine::prototype::PrototypeParticleSystem_PointParticleEmitter;
using tdme::engine::prototype::PrototypeParticleSystem_PointParticleSystem;
using tdme::engine::prototype::PrototypeParticleSystem_SphereParticleEmitter;
using tdme::engine::prototype::PrototypeParticleSystem_Type;
using tdme::engine::prototype::PrototypePhysics;
using tdme::engine::prototype::PrototypePhysics_BodyType;
using tdme::engine::prototype::PrototypeTerrain;
using tdme::engine::scene::Scene;
using tdme::engine::scene::SceneEntity;
using tdme::engine::scene::SceneLibrary;
using tdme::engine::scene::SceneLight;
using tdme::engine::subsystems::particlesystem::BoundingBoxParticleEmitter;
using tdme::engine::subsystems::particlesystem::CircleParticleEmitter;
using tdme::engine::subsystems::particlesystem::CircleParticleEmitterPlaneVelocity;
using tdme::engine::subsystems::particlesystem::PointParticleEmitter;
using tdme::engine::subsystems::particlesystem::SphereParticleEmitter;
using tdme::engine::Decal;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::EntityHierarchy;
using tdme::engine::EnvironmentMapping;
using tdme::engine::FogParticleSystem;
using tdme::engine::Light;
using tdme::engine::LODObject;
using tdme::engine::LODObjectImposter;
using tdme::engine::Object;
using tdme::engine::ObjectModel;
using tdme::engine::ObjectParticleSystem;
using tdme::engine::ObjectRenderGroup;
using tdme::engine::ParticleSystem;
using tdme::engine::ParticleSystemGroup;
using tdme::engine::PointsParticleSystem;
using tdme::engine::Transform;
using tdme::math::Math;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::tools::editor::misc::Tools;
using tdme::utilities::Console;
using tdme::utilities::ModelTools;
using tdme::utilities::MutableString;
using tdme::utilities::Primitives;
using tdme::utilities::StringTools;
using tdme::utilities::Terrain;

Model* SceneConnector::emptyModel = nullptr;
float SceneConnector::renderGroupsPartitionWidth = 64.0f;
float SceneConnector::renderGroupsPartitionHeight = 64.0f;
float SceneConnector::renderGroupsPartitionDepth = 64.0f;
int SceneConnector::renderGroupsReduceBy = 1;
int SceneConnector::renderGroupsLODLevels = 3;
float SceneConnector::renderGroupsLOD2MinDistance = 25.0;
float SceneConnector::renderGroupsLOD3MinDistance = 50.0;
int SceneConnector::renderGroupsLOD2ReduceBy = 4;
int SceneConnector::renderGroupsLOD3ReduceBy = 16;

void SceneConnector::setLights(Engine* engine, Scene* scene, const Vector3& translation)
{
	for (auto i = 0; i < Engine::LIGHTS_MAX; i++) {
		if (i >= scene->getLightCount()) {
			engine->getLightAt(i)->setEnabled(false);
			continue;
		}
		engine->getLightAt(i)->setAmbient(Color4(scene->getLightAt(i)->getAmbient()));
		engine->getLightAt(i)->setDiffuse(Color4(scene->getLightAt(i)->getDiffuse()));
		engine->getLightAt(i)->setSpecular(Color4(scene->getLightAt(i)->getSpecular()));
		engine->getLightAt(i)->setSpotDirection(scene->getLightAt(i)->getSpotDirection());
		engine->getLightAt(i)->setSpotExponent(scene->getLightAt(i)->getSpotExponent());
		engine->getLightAt(i)->setSpotCutOff(scene->getLightAt(i)->getSpotCutOff());
		engine->getLightAt(i)->setConstantAttenuation(scene->getLightAt(i)->getConstantAttenuation());
		engine->getLightAt(i)->setLinearAttenuation(scene->getLightAt(i)->getLinearAttenuation());
		engine->getLightAt(i)->setQuadraticAttenuation(scene->getLightAt(i)->getQuadraticAttenuation());
		engine->getLightAt(i)->setEnabled(scene->getLightAt(i)->isEnabled());
		engine->getLightAt(i)->setPosition(
			Vector4(
				scene->getLightAt(i)->getPosition().getX() + translation.getX(),
				scene->getLightAt(i)->getPosition().getY() + translation.getY(),
				scene->getLightAt(i)->getPosition().getZ() + translation.getZ(),
				scene->getLightAt(i)->getPosition().getW()
			)
		);
	}
}

Entity* SceneConnector::createParticleSystem(PrototypeParticleSystem* particleSystem, const string& id, bool enableDynamicShadows)
{
	ParticleEmitter* engineEmitter = nullptr;
	{
		auto emitterType = particleSystem->getEmitter();
		if (emitterType == PrototypeParticleSystem_Emitter::NONE) {
			return nullptr;
		} else
		if (emitterType == PrototypeParticleSystem_Emitter::POINT_PARTICLE_EMITTER) {
			auto emitter = particleSystem->getPointParticleEmitter();
			engineEmitter = new PointParticleEmitter(emitter->getCount(), emitter->getLifeTime(), emitter->getLifeTimeRnd(), emitter->getMass(), emitter->getMassRnd(), emitter->getPosition(), emitter->getVelocity(), emitter->getVelocityRnd(), emitter->getColorStart(), emitter->getColorEnd());
		} else
		if (emitterType == PrototypeParticleSystem_Emitter::BOUNDINGBOX_PARTICLE_EMITTER) {
			auto emitter = particleSystem->getBoundingBoxParticleEmitters();
			engineEmitter = new BoundingBoxParticleEmitter(emitter->getCount(), emitter->getLifeTime(), emitter->getLifeTimeRnd(), emitter->getMass(), emitter->getMassRnd(), new OrientedBoundingBox(emitter->getObbCenter(), emitter->getObbAxis0(), emitter->getObbAxis1(), emitter->getObbAxis2(), emitter->getObbHalfextension()), emitter->getVelocity(), emitter->getVelocityRnd(), emitter->getColorStart(), emitter->getColorEnd());
		} else
		if (emitterType == PrototypeParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER) {
			auto emitter = particleSystem->getCircleParticleEmitter();
			engineEmitter = new CircleParticleEmitter(emitter->getCount(), emitter->getLifeTime(), emitter->getLifeTimeRnd(), emitter->getAxis0(), emitter->getAxis1(), emitter->getCenter(), emitter->getRadius(), emitter->getMass(), emitter->getMassRnd(), emitter->getVelocity(), emitter->getVelocityRnd(), emitter->getColorStart(), emitter->getColorEnd());
		} else
		if (emitterType == PrototypeParticleSystem_Emitter::CIRCLE_PARTICLE_EMITTER_PLANE_VELOCITY) {
			auto emitter = particleSystem->getCircleParticleEmitterPlaneVelocity();
			engineEmitter = new CircleParticleEmitterPlaneVelocity(emitter->getCount(), emitter->getLifeTime(), emitter->getLifeTimeRnd(), emitter->getAxis0(), emitter->getAxis1(), emitter->getCenter(), emitter->getRadius(), emitter->getMass(), emitter->getMassRnd(), emitter->getVelocity(), emitter->getVelocityRnd(), emitter->getColorStart(), emitter->getColorEnd());
		} else
		if (emitterType == PrototypeParticleSystem_Emitter::SPHERE_PARTICLE_EMITTER) {
			auto emitter = particleSystem->getSphereParticleEmitter();
			engineEmitter = new SphereParticleEmitter(emitter->getCount(), emitter->getLifeTime(), emitter->getLifeTimeRnd(), emitter->getMass(), emitter->getMassRnd(), new Sphere(emitter->getCenter(), emitter->getRadius()), emitter->getVelocity(), emitter->getVelocityRnd(), emitter->getColorStart(), emitter->getColorEnd());
		} else {
			Console::println(
				string(
					"SceneConnector::createParticleSystem(): unknown particle system emitter '" +
					particleSystem->getEmitter()->getName() +
					"'"
				)
			);
			return nullptr;
		}
	}

	{
		auto particleSystemType = particleSystem->getType();
		if (particleSystemType == PrototypeParticleSystem_Type::NONE) {
			return nullptr;
		} else
		if (particleSystemType == PrototypeParticleSystem_Type::OBJECT_PARTICLE_SYSTEM) {
			auto objectParticleSystem = particleSystem->getObjectParticleSystem();
			if (objectParticleSystem->getModel() == nullptr) return nullptr;

			return new ObjectParticleSystem(
				id,
				objectParticleSystem->getModel(),
				objectParticleSystem->getScale(),
				objectParticleSystem->isAutoEmit(),
				enableDynamicShadows,
				enableDynamicShadows,
				objectParticleSystem->getMaxCount(),
				engineEmitter
			);
		} else
		if (particleSystemType == PrototypeParticleSystem_Type::POINT_PARTICLE_SYSTEM) {
			auto pointParticleSystem = particleSystem->getPointParticleSystem();
			return new PointsParticleSystem(
				id,
				engineEmitter,
				pointParticleSystem->getMaxPoints(),
				pointParticleSystem->getPointSize(),
				pointParticleSystem->isAutoEmit(),
				pointParticleSystem->getTexture(),
				pointParticleSystem->getTextureHorizontalSprites(),
				pointParticleSystem->getTextureVerticalSprites(),
				pointParticleSystem->getTextureSpritesFPS()
			);
		} else
		if (particleSystemType == PrototypeParticleSystem_Type::FOG_PARTICLE_SYSTEM) {
			auto fogParticleSystem = particleSystem->getFogParticleSystem();
			return new FogParticleSystem(
				id,
				engineEmitter,
				fogParticleSystem->getMaxPoints(),
				fogParticleSystem->getPointSize(),
				fogParticleSystem->getTexture(),
				fogParticleSystem->getTextureHorizontalSprites(),
				fogParticleSystem->getTextureVerticalSprites(),
				fogParticleSystem->getTextureSpritesFPS()
			);
		} else {
			Console::println(
				string(
					"SceneConnector::createParticleSystem(): unknown particle system type '" +
					particleSystem->getType()->getName() +
					"'"
				)
			);
			return nullptr;
		}
	}
}

Entity* SceneConnector::createEmpty(const string& id, const Transform& transform) {
	if (emptyModel == nullptr) {
		emptyModel = ModelReader::read("resources/engine/models", "empty.tm");
	}
	auto entity = new Object(
		id,
		SceneConnector::emptyModel
	);
	entity->setTransform(transform);
	return entity;
}

Entity* SceneConnector::createEditorDecalEntity(Prototype* prototype, const string& id, const Transform& transform, int instances) {
	// decals only here :D
	if (prototype->getType() != Prototype_Type::DECAL) return nullptr;

	//
	Entity* entity = nullptr;

	// add decal OBB
	auto entityHierarchy = new EntityHierarchy(id);
	for (auto i = 0; i < prototype->getBoundingVolumeCount(); i++) {
		auto entityBoundingVolume = prototype->getBoundingVolume(i);
		if (entityBoundingVolume->getModel() != nullptr) {
			auto bvObject = new Object("tdme.prototype.bv." + to_string(i), entityBoundingVolume->getModel());
			bvObject->setRenderPass(Entity::RENDERPASS_POST_POSTPROCESSING);
			entityHierarchy->addEntity(bvObject);
		}
	}
	// add decal itself
	if (prototype->getBoundingVolumeCount() == 1 &&
		dynamic_cast<OrientedBoundingBox*>(prototype->getBoundingVolume(0)->getBoundingVolume()) != nullptr) {
		entityHierarchy->addEntity(
			new Decal(
				"decal",
				dynamic_cast<OrientedBoundingBox*>(prototype->getBoundingVolume(0)->getBoundingVolume()),
				prototype->getDecal()->getTexture(),
				prototype->getDecal()->getTextureHorizontalSprites(),
				prototype->getDecal()->getTextureVerticalSprites(),
				prototype->getDecal()->getTextureSpritesFPS()
			)
		);
	}

	//
	entityHierarchy->setTransform(transform);
	entityHierarchy->update();
	if (entityHierarchy->getEntities().size() == 0) {
		entityHierarchy->dispose();
		delete entityHierarchy;
	} else {
		entity = entityHierarchy;
	}

	// done
	return entity;
}

Entity* SceneConnector::createEntity(Prototype* prototype, const string& id, const Transform& transform, int instances, bool noEntityHierarchy) {
	Entity* entity = nullptr;

	// objects
	if (prototype->getModel() != nullptr) {
		auto imposterLOD = prototype->getImposterLOD();
		auto lodLevel2 = prototype->getLODLevel2();
		auto lodLevel3 = prototype->getLODLevel3();
		// with LOD
		if (imposterLOD != nullptr) {
			entity = new LODObjectImposter(
				id,
				prototype->getModel(),
				imposterLOD->getModels(),
				imposterLOD->getMinDistance()
			);
			auto imposterLodObject = dynamic_cast<LODObjectImposter*>(entity);
			imposterLodObject->setEffectColorAddLOD2(imposterLOD->getColorAdd());
			imposterLodObject->setEffectColorMulLOD2(imposterLOD->getColorMul());
			if (prototype->getShader() == "water" || prototype->getShader() == "pbr-water") imposterLodObject->setRenderPass(Entity::RENDERPASS_WATER);
			imposterLodObject->setShader(prototype->getShader());
			auto shaderParametersDefault = Engine::getShaderParameterDefaults(prototype->getShader());
			for (const auto& [parameterName, defaultParameterValue]: shaderParametersDefault) {
				auto parameterValue = prototype->getShaderParameters().getShaderParameter(parameterName);
				imposterLodObject->setShaderParameter(parameterName, parameterValue);
			}
		} else
		if (lodLevel2 != nullptr) {
			entity = new LODObject(
				id,
				prototype->getModel(),
				lodLevel2->getType(),
				lodLevel2->getMinDistance(),
				lodLevel2->getModel(),
				lodLevel3 != nullptr?lodLevel3->getType():LODObject::LODLEVELTYPE_NONE,
				lodLevel3 != nullptr?lodLevel3->getMinDistance():0.0f,
				lodLevel3 != nullptr?lodLevel3->getModel():nullptr
			);
			auto lodObject = dynamic_cast<LODObject*>(entity);
			lodObject->setEffectColorAddLOD2(lodLevel2->getColorAdd());
			lodObject->setEffectColorMulLOD2(lodLevel2->getColorMul());
			if (lodLevel3 != nullptr) {
				lodObject->setEffectColorAddLOD3(lodLevel3->getColorAdd());
				lodObject->setEffectColorMulLOD3(lodLevel3->getColorMul());
			}
			if (prototype->getShader() == "water" || prototype->getShader() == "pbr-water") lodObject->setRenderPass(Entity::RENDERPASS_WATER);
			lodObject->setShader(prototype->getShader());
			auto shaderParametersDefault = Engine::getShaderParameterDefaults(prototype->getShader());
			for (const auto& [parameterName, defaultParameterValue]: shaderParametersDefault) {
				auto parameterValue = prototype->getShaderParameters().getShaderParameter(parameterName);
				lodObject->setShaderParameter(parameterName, parameterValue);
			}
		} else {
			// single
			entity = new Object(
				id,
				prototype->getModel(),
				instances
			);
			auto object = dynamic_cast<Object*>(entity);
			object->setAnimationComputationLODEnabled(true);
			if (prototype->getShader() == "water" || prototype->getShader() == "pbr-water") object->setRenderPass(Entity::RENDERPASS_WATER);
			object->setShader(prototype->getShader());
			auto shaderParametersDefault = Engine::getShaderParameterDefaults(prototype->getShader());
			for (const auto& [parameterName, defaultParameterValue]: shaderParametersDefault) {
				auto parameterValue = prototype->getShaderParameters().getShaderParameter(parameterName);
				object->setShaderParameter(parameterName, parameterValue);
			}
		}
	} else
	// particle system
	if (prototype->getType() == Prototype_Type::PARTICLESYSTEM) {
		vector<ParticleSystem*> particleSystems;
		for (auto i = 0; i < prototype->getParticleSystemsCount(); i++) {
			auto particleSystem = createParticleSystem(
				prototype->getParticleSystemAt(i),
				id + (i == 0?"":"." + to_string(i)),
				true
			);
			if (particleSystem != nullptr) {
				particleSystems.push_back(dynamic_cast<ParticleSystem*>(particleSystem));
			}
		}
		if (particleSystems.size() == 1) {
			entity = dynamic_cast<Entity*>(particleSystems[0]);
		} else
		if (particleSystems.size() > 1) {
			entity = new ParticleSystemGroup(
				id,
				true,
				true,
				true,
				particleSystems
			);
		}
	} else
	// decal
	if (prototype->getType() == Prototype_Type::DECAL) {
		entity =
			new Decal(
				id,
				dynamic_cast<OrientedBoundingBox*>(prototype->getBoundingVolume(0)->getBoundingVolume()),
				prototype->getDecal()->getTexture(),
				prototype->getDecal()->getTextureHorizontalSprites(),
				prototype->getDecal()->getTextureVerticalSprites(),
				prototype->getDecal()->getTextureSpritesFPS()
			);
	} else
	// trigger/environment mapping
	if (prototype->getType() == Prototype_Type::TRIGGER ||
		prototype->getType() == Prototype_Type::ENVIRONMENTMAPPING) {
		// bounding volumes
		auto entityHierarchy = new EntityHierarchy(id);
		for (auto i = 0; i < prototype->getBoundingVolumeCount(); i++) {
			auto entityBoundingVolume = prototype->getBoundingVolume(i);
			if (entityBoundingVolume->getModel() != nullptr) {
				auto bvObject = new Object("tdme.prototype.bv." + to_string(i), entityBoundingVolume->getModel());
				bvObject->setRenderPass(Entity::RENDERPASS_POST_POSTPROCESSING);
				entityHierarchy->addEntity(bvObject);
			}
		}
		if (prototype->getType() == Prototype_Type::ENVIRONMENTMAPPING &&
			prototype->getBoundingVolumeCount() == 1 &&
			dynamic_cast<OrientedBoundingBox*>(prototype->getBoundingVolume(0)->getBoundingVolume()) != nullptr) {
			BoundingBox aabb(dynamic_cast<OrientedBoundingBox*>(prototype->getBoundingVolume(0)->getBoundingVolume()));
			auto environmentMapping = new EnvironmentMapping("environmentmapping", Engine::getEnvironmentMappingWidth(), Engine::getEnvironmentMappingHeight(), aabb);
			environmentMapping->setRenderPassMask(prototype->getEnvironmentMapRenderPassMask());
			environmentMapping->setTimeRenderUpdateFrequency(prototype->getEnvironmentMapTimeRenderUpdateFrequency());
			entityHierarchy->addEntity(environmentMapping);
		}
		entityHierarchy->update();
		if (entityHierarchy->getEntities().size() == 0) {
			entityHierarchy->dispose();
			delete entityHierarchy;
		} else {
			entity = entityHierarchy;
		}
	}

	//
	if (noEntityHierarchy == false && prototype->isEntityHierarchy() == true && dynamic_cast<EntityHierarchy*>(entity) == nullptr) {
		auto entityHierarchy = new EntityHierarchy(id);
		entityHierarchy->addEntity(entity);
		// pass on entity hierarchy as entity
		entity = entityHierarchy;
	}

	//
	if (entity != nullptr) {
		if (prototype->isTerrainMesh() == true) entity->setRenderPass(Entity::RENDERPASS_TERRAIN);
		entity->setContributesShadows(prototype->isContributesShadows());
		entity->setReceivesShadows(prototype->isReceivesShadows());
		entity->setTransform(transform);
	}

	// done
	return entity;
}

Entity* SceneConnector::createEditorDecalEntity(SceneEntity* sceneEntity, const Vector3& translation, int instances) {
	Transform transform;
	transform.setTransform(sceneEntity->getTransform());
	if (translation.equals(Vector3()) == false) {
		transform.setTranslation(transform.getTranslation().clone().add(translation));
		transform.update();
	}
	return createEditorDecalEntity(sceneEntity->getPrototype(), sceneEntity->getId(), transform, instances);
}

Entity* SceneConnector::createEntity(SceneEntity* sceneEntity, const Vector3& translation, int instances, bool noEntityHierarchy) {
	Transform transform;
	transform.setTransform(sceneEntity->getTransform());
	if (translation.equals(Vector3()) == false) {
		transform.setTranslation(transform.getTranslation().clone().add(translation));
		transform.update();
	}
	return createEntity(sceneEntity->getPrototype(), sceneEntity->getId(), transform, instances, noEntityHierarchy);
}

void SceneConnector::addScene(Engine* engine, Scene* scene, bool addEmpties, bool addTrigger, bool addEnvironmentMapping, bool useEditorDecals, bool pickable, bool enable, const Vector3& translation, ProgressCallback* progressCallback)
{
	if (progressCallback != nullptr) progressCallback->progress(0.0f);
	// TODO: progress callbacks for terrain

	// scene library
	auto sceneLibrary = scene->getLibrary();

	// terrain
	{
		auto prototype = sceneLibrary->getTerrainPrototype();
		if (prototype != nullptr) {
			//
			auto terrain = prototype->getTerrain();
			auto width = terrain->getWidth();
			auto depth = terrain->getDepth();
			// terrain
			BoundingBox terrainBoundingBox;
			vector<Model*> terrainModels;
			Terrain::createTerrainModels(width, depth, 0.0f, terrain->getHeightVector(), terrainBoundingBox, terrainModels/*, true*/); // TODO: finish LOD
			if (terrainModels.empty() == false) {
				auto idx = 0;
				for (auto terrainModel: terrainModels) {
					auto terrainObject = new Object("tdme.terrain." + to_string(idx++), terrainModel);
					terrainObject->setRenderPass(Entity::RENDERPASS_TERRAIN);
					terrainObject->setShader("terrain");
					terrainObject->setContributesShadows(true);
					terrainObject->setReceivesShadows(true);
					terrainObject->setPickable(pickable);
					terrainObject->setEnabled(enable);
					terrainObject->setTranslation(translation);
					terrainObject->update();
					engine->addEntity(terrainObject);
				}
			}
			// water
			{
				auto idx = 0;
				auto waterPositionMapsIndices = terrain->getWaterPositionMapsIndices();
				for (auto waterPositionMapIdx: waterPositionMapsIndices) {
					vector<Model*> waterModels;
					Terrain::createWaterModels(
						terrainBoundingBox,
						prototype->getTerrain()->getWaterPositionMap(waterPositionMapIdx),
						prototype->getTerrain()->getWaterPositionMapHeight(waterPositionMapIdx),
						waterPositionMapIdx,
						waterModels
					);
					for (auto waterModel: waterModels) {
						auto waterObject = new Object("tdme.water." + to_string(idx++), waterModel);
						waterObject->setRenderPass(Entity::RENDERPASS_WATER);
						waterObject->setShader("water");

						waterObject->setContributesShadows(false);
						waterObject->setReceivesShadows(false);
						waterObject->setReflectionEnvironmentMappingId("sky_environment_mapping");
						waterObject->setReflectionEnvironmentMappingPosition(
							Terrain::computeWaterReflectionEnvironmentMappingPosition(
								terrain->getWaterPositionMap(waterPositionMapIdx),
								terrain->getWaterPositionMapHeight(waterPositionMapIdx)
							)
						);
						waterObject->setPickable(pickable);
						waterObject->setEnabled(enable);
						waterObject->setTranslation(translation);
						waterObject->update();
						engine->addEntity(waterObject);
					}
				}
			}
			// foliage
			{
				//
				const auto& foliageMaps = terrain->getFoliageMaps();

				//
				auto foliageRenderGroupIdx = 0;
				auto partitionIdx = 0;
				unordered_map<int, int> prototypeEntityIdx;
				for (auto& foliageMapPartition: foliageMaps) {
					auto partitionPrototypeInstanceCount = 0;
					for (const auto& [prototypeIdx, transformVector]: foliageMapPartition) {
						partitionPrototypeInstanceCount+= transformVector.size();
					}
					if (partitionPrototypeInstanceCount > 0) {
						unordered_map<string, ObjectRenderGroup*> objectRenderGroupByShaderParameters;
						for (const auto& [prototypeIdx, transformVector]: foliageMapPartition) {
							if (transformVector.empty() == true) continue;
							auto foliagePrototype = prototype->getTerrain()->getFoliagePrototype(prototypeIdx);
							if (foliagePrototype->isRenderGroups() == false) {
								for (auto& transform: transformVector) {
									auto entity = createEntity(foliagePrototype, "tdme.foliage." + to_string(prototypeIdx) + "." + to_string(prototypeEntityIdx[prototypeIdx]++), transform);
									if (entity == nullptr) continue;
									entity->setTranslation(entity->getTranslation().clone().add(translation));
									entity->setPickable(pickable);
									entity->setEnabled(enable);
									entity->update();
									engine->addEntity(entity);
								}
							} else {
								ObjectRenderGroup* foliagePartitionObjectRenderGroup = nullptr;
								auto contributesShadows = foliagePrototype->isContributesShadows();
								auto receivesShadows = foliagePrototype->isReceivesShadows();
								auto hash = foliagePrototype->getShaderParameters().getShaderParametersHash() + "|" + to_string(contributesShadows) + "|" + to_string(receivesShadows);
								auto foliagePartitionObjectRenderGroupIt = objectRenderGroupByShaderParameters.find(hash);
								if (foliagePartitionObjectRenderGroupIt != objectRenderGroupByShaderParameters.end()) {
									foliagePartitionObjectRenderGroup = foliagePartitionObjectRenderGroupIt->second;
								}
								if (foliagePartitionObjectRenderGroup == nullptr) {
									foliagePartitionObjectRenderGroup =
										new ObjectRenderGroup(
											"tdme.fo3rg." + to_string(foliageRenderGroupIdx++),
											renderGroupsLODLevels,
											renderGroupsLOD2MinDistance,
											renderGroupsLOD3MinDistance,
											renderGroupsLOD2ReduceBy,
											renderGroupsLOD3ReduceBy
										);
									foliagePartitionObjectRenderGroup->setContributesShadows(contributesShadows);
									foliagePartitionObjectRenderGroup->setReceivesShadows(receivesShadows);
									foliagePartitionObjectRenderGroup->setShader(foliagePrototype->getShader());
									auto shaderParametersDefault = Engine::getShaderParameterDefaults(foliagePrototype->getShader());
									for (const auto& [parameterName, defaultParameterValue]: shaderParametersDefault) {
										auto parameterValue = foliagePrototype->getShaderParameters().getShaderParameter(parameterName);
										foliagePartitionObjectRenderGroup->setShaderParameter(parameterName, parameterValue);
									}
									foliagePartitionObjectRenderGroup->setPickable(false);
									foliagePartitionObjectRenderGroup->setEnabled(enable);
									objectRenderGroupByShaderParameters[hash] = foliagePartitionObjectRenderGroup;
								}

								//
								auto objectIdx = -1;
								for (auto& transform: transformVector) {
									objectIdx++;
									if (objectIdx % renderGroupsReduceBy != 0) continue;
									foliagePartitionObjectRenderGroup->addObject(foliagePrototype->getModel(), transform);
								}
							}
						}
						for (const auto& [shaderHashId, foliagePartitionObjectRenderGroup]: objectRenderGroupByShaderParameters) {
							foliagePartitionObjectRenderGroup->updateRenderGroup();
							foliagePartitionObjectRenderGroup->setTranslation(translation);
							foliagePartitionObjectRenderGroup->update();
							engine->addEntity(foliagePartitionObjectRenderGroup);
						}
					}
					partitionIdx++;
				}
			}
		}
	}

	// scene entities
	unordered_map<string, unordered_map<string, unordered_map<Model*, vector<Transform*>>>> renderGroupEntitiesByShaderPartitionModel;
	unordered_map<Model*, Prototype*> renderGroupSceneEditorEntities;
	auto progressStepCurrent = 0;
	for (auto i = 0; i < scene->getEntityCount(); i++) {
		auto sceneEntity = scene->getEntityAt(i);

		if (progressCallback != nullptr && progressStepCurrent % 1000 == 0) progressCallback->progress(0.0f + static_cast<float>(progressStepCurrent) / static_cast<float>(scene->getEntityCount()) * 0.5f);
		progressStepCurrent++;

		if (addEmpties == false && sceneEntity->getPrototype()->getType() == Prototype_Type::EMPTY) continue;
		if (addTrigger == false && sceneEntity->getPrototype()->getType() == Prototype_Type::TRIGGER) continue;

		if (sceneEntity->getPrototype()->isRenderGroups() == true) {
			auto minX = sceneEntity->getTransform().getTranslation().getX();
			auto minY = sceneEntity->getTransform().getTranslation().getY();
			auto minZ = sceneEntity->getTransform().getTranslation().getZ();
			auto partitionX = (int)(minX / renderGroupsPartitionWidth);
			auto partitionY = (int)(minY / renderGroupsPartitionHeight);
			auto partitionZ = (int)(minZ / renderGroupsPartitionDepth);
			renderGroupSceneEditorEntities[sceneEntity->getPrototype()->getModel()] = sceneEntity->getPrototype();
			renderGroupEntitiesByShaderPartitionModel[sceneEntity->getPrototype()->getShader()][to_string(partitionX) + "," + to_string(partitionY) + "," + to_string(partitionZ)][sceneEntity->getPrototype()->getModel()].push_back(&sceneEntity->getTransform());
		} else {
			auto entity = sceneEntity->getPrototype()->getType() == Prototype_Type::DECAL && useEditorDecals == true?createEditorDecalEntity(sceneEntity):createEntity(sceneEntity);
			if (entity == nullptr) continue;

			entity->setTranslation(entity->getTranslation().clone().add(translation));
			entity->setPickable(pickable);
			entity->setContributesShadows(sceneEntity->getPrototype()->isContributesShadows());
			entity->setReceivesShadows(sceneEntity->getPrototype()->isReceivesShadows());
			if (sceneEntity->getPrototype()->getType() == Prototype_Type::EMPTY) {
				entity->setScale(Vector3(Math::sign(entity->getScale().getX()), Math::sign(entity->getScale().getY()), Math::sign(entity->getScale().getZ())));
			}
			if (sceneEntity->getPrototype()->getType()->hasNonEditScaleDownMode() == true) {
				entity->setScale(
					sceneEntity->getPrototype()->getType()->getNonEditScaleDownModeDimension().
					clone().
					scale(
						Vector3(
							1.0f / (sceneEntity->getTransform().getScale().getX() * entity->getBoundingBox()->getDimensions().getX()),
							1.0f / (sceneEntity->getTransform().getScale().getY() * entity->getBoundingBox()->getDimensions().getY()),
							1.0f / (sceneEntity->getTransform().getScale().getZ() * entity->getBoundingBox()->getDimensions().getZ())
						)
					)
				);
			}
			entity->update();
			entity->setEnabled(enable);

			auto object = dynamic_cast<Object*>(entity);
			if (object != nullptr) object->setReflectionEnvironmentMappingId(sceneEntity->getReflectionEnvironmentMappingId());

			engine->addEntity(entity);
		}
	}

	// do render groups
	{
		auto idx = 0;
		progressStepCurrent = 0;
		auto progressStepMax = 0;
		if (progressCallback != nullptr) {
			for (const auto& [shaderId, shaderPartitionModelTranformsMap]: renderGroupEntitiesByShaderPartitionModel) {
				for (const auto& [partitionId, modelTranformsMap]: shaderPartitionModelTranformsMap) {
					for (const auto& [model, transformVector]: modelTranformsMap) {
						progressStepMax++;
					}
				}
			}
		}
		for (const auto& [shaderId, shaderPartitionModelTranformsMap]: renderGroupEntitiesByShaderPartitionModel) {
			for (const auto& [partitionId, modelTranformsMap]: shaderPartitionModelTranformsMap) {
				unordered_map<string, ObjectRenderGroup*> objectRenderGroupsByShaderParameters;
				for (const auto& [model, transformVector]: modelTranformsMap) {
					if (progressCallback != nullptr) {
						progressCallback->progress(0.5f + static_cast<float>(progressStepCurrent) / static_cast<float>(progressStepMax) * 0.5f);
					}
					progressStepCurrent++;
					auto prototype = renderGroupSceneEditorEntities[model];
					auto contributesShadows = prototype->isContributesShadows();
					auto receivesShadows = prototype->isReceivesShadows();
					auto hash = prototype->getShaderParameters().getShaderParametersHash() + "|" + to_string(contributesShadows) + "|" + to_string(receivesShadows);
					if (objectRenderGroupsByShaderParameters.find(hash) == objectRenderGroupsByShaderParameters.end()) {
						auto objectRenderNode =
							new ObjectRenderGroup(
								"tdme.o3rg." + to_string(idx++),
								renderGroupsLODLevels,
								renderGroupsLOD2MinDistance,
								renderGroupsLOD3MinDistance,
								renderGroupsLOD2ReduceBy,
								renderGroupsLOD3ReduceBy
							);
						objectRenderNode->setContributesShadows(contributesShadows);
						objectRenderNode->setReceivesShadows(receivesShadows);
						objectRenderNode->setShader(prototype->getShader());
						auto shaderParametersDefault = Engine::getShaderParameterDefaults(prototype->getShader());
						for (const auto& [parameterName, defaultParameterValue]: shaderParametersDefault) {
							auto parameterValue = prototype->getShaderParameters().getShaderParameter(parameterName);
							objectRenderNode->setShaderParameter(parameterName, parameterValue);
						}
						objectRenderGroupsByShaderParameters[hash] = objectRenderNode;
					}
					auto objectRenderNode = objectRenderGroupsByShaderParameters[hash];
					auto objectIdx = -1;
					for (const auto& transform: transformVector) {
						objectIdx++;
						if (objectIdx % renderGroupsReduceBy != 0) continue;
						objectRenderNode->addObject(prototype->getModel(), *transform);
					}
				}
				for (const auto& [hash, objectRenderNode]: objectRenderGroupsByShaderParameters) {
					objectRenderNode->updateRenderGroup();
					engine->addEntity(objectRenderNode);
				}
			}
		}
	}

	//
	if (progressCallback != nullptr) {
		progressCallback->progress(1.0f);
		delete progressCallback;
	}
}

Body* SceneConnector::createBody(World* world, Prototype* prototype, const string& id, const Transform& transform, uint16_t collisionTypeId, bool hierarchy, int index, PrototypePhysics_BodyType* overrideType) {
	//
	if (prototype->getType() == Prototype_Type::EMPTY) return nullptr;
	// no physics, no fun with bodies
	if (prototype->getPhysics() == nullptr) return nullptr;
	//
	auto physicsType = overrideType != nullptr?overrideType:prototype->getPhysics()->getType();
	// trigger
	if (prototype->getType() == Prototype_Type::TRIGGER) {
		vector<BoundingVolume*> boundingVolumes;
		for (auto j = 0; j < prototype->getBoundingVolumeCount(); j++) {
			auto entityBv = prototype->getBoundingVolume(j);
			if (index == -1 || index == j) boundingVolumes.push_back(entityBv->getBoundingVolume());
		}
		if (boundingVolumes.size() == 0) return nullptr;
		return world->addStaticCollisionBody(
			id,
			collisionTypeId == 0?BODY_TYPEID_TRIGGER:collisionTypeId,
			true,
			transform,
			boundingVolumes,
			hierarchy == true || prototype->isEntityHierarchy() == true
		);
	} else
	// model as terrain mesh
	if (prototype->getType() == Prototype_Type::MODEL &&
		prototype->isTerrainMesh() == true) {
		ObjectModel terrainModel(prototype->getModel());
		auto terrainMesh = new TerrainMesh(&terrainModel, transform);
		if (physicsType == PrototypePhysics_BodyType::COLLISION_BODY) {
			return world->addStaticCollisionBody(
				id,
				collisionTypeId == 0?BODY_TYPEID_COLLISION:collisionTypeId,
				true,
				Transform(),
				{terrainMesh},
				hierarchy == true || prototype->isEntityHierarchy() == true
			);
		} else
		if (physicsType == PrototypePhysics_BodyType::STATIC_RIGIDBODY) {
			return world->addStaticRigidBody(
				id,
				collisionTypeId == 0?BODY_TYPEID_STATIC:collisionTypeId,
				true,
				Transform(),
				prototype->getPhysics()->getFriction(),
				{terrainMesh},
				hierarchy == true || prototype->isEntityHierarchy() == true
			);
		} else
		if (physicsType == PrototypePhysics_BodyType::DYNAMIC_RIGIDBODY) {
			return world->addRigidBody(
				id,
				collisionTypeId == 0?BODY_TYPEID_DYNAMIC:collisionTypeId,
				true,
				Transform(),
				prototype->getPhysics()->getRestitution(),
				prototype->getPhysics()->getFriction(),
				prototype->getPhysics()->getMass(),
				prototype->getPhysics()->getInertiaTensor(),
				{terrainMesh},
				hierarchy == true || prototype->isEntityHierarchy() == true
			);
		}
	} else {
		// normal body
		vector<BoundingVolume*> boundingVolumes;
		for (auto j = 0; j < prototype->getBoundingVolumeCount(); j++) {
			auto entityBv = prototype->getBoundingVolume(j);
			if (index == -1 || index == j) boundingVolumes.push_back(entityBv->getBoundingVolume());
		}
		if (boundingVolumes.size() == 0) return nullptr;
		if (physicsType == PrototypePhysics_BodyType::COLLISION_BODY) {
			return world->addStaticCollisionBody(
				id,
				collisionTypeId == 0?BODY_TYPEID_COLLISION:collisionTypeId,
				true,
				transform,
				boundingVolumes,
				hierarchy == true || prototype->isEntityHierarchy() == true
			);
		} else
		if (physicsType == PrototypePhysics_BodyType::STATIC_RIGIDBODY) {
			return world->addStaticRigidBody(
				id,
				true,
				collisionTypeId == 0?BODY_TYPEID_STATIC:collisionTypeId,
				transform,
				prototype->getPhysics()->getFriction(),
				boundingVolumes,
				hierarchy == true || prototype->isEntityHierarchy() == true
			);
		} else
		if (physicsType == PrototypePhysics_BodyType::DYNAMIC_RIGIDBODY) {
			return world->addRigidBody(
				id,
				collisionTypeId == 0?BODY_TYPEID_DYNAMIC:collisionTypeId,
				true,
				transform,
				prototype->getPhysics()->getRestitution(),
				prototype->getPhysics()->getFriction(),
				prototype->getPhysics()->getMass(),
				prototype->getPhysics()->getInertiaTensor(),
				boundingVolumes,
				hierarchy == true || prototype->isEntityHierarchy() == true
			);
		}
	}
	return nullptr;
}

Body* SceneConnector::createBody(World* world, SceneEntity* sceneEntity, const Vector3& translation, uint16_t collisionTypeId, bool hierarchy, int index, PrototypePhysics_BodyType* overrideType) {
	auto transform = sceneEntity->getTransform();
	if (translation.equals(Vector3()) == false) {
		transform.setTranslation(transform.getTranslation().clone().add(translation));
		transform.update();
	}
	return createBody(world, sceneEntity->getPrototype(), sceneEntity->getId(), transform, collisionTypeId, hierarchy, index, overrideType);
}

BodyHierarchy* SceneConnector::createSubBody(World* world, Prototype* prototype, const string& id, const Transform& transform, const string& bodyHierarchyId, const string& bodyHierarchyParentId) {
	auto bodyHierarchy = world->getBodyHierarchy(bodyHierarchyId);
	if (bodyHierarchy == nullptr) {
		Console::println("SceneConnector::createSubBody(): body hierarchy not found: " + bodyHierarchyId);
		return nullptr;
	}
	bodyHierarchy->addBody(id, transform, prototype->getBoundingVolumePrimitives(), bodyHierarchyParentId);
	bodyHierarchy->update();
	return bodyHierarchy;
}

void SceneConnector::addScene(World* world, Scene* scene, bool enable, const Vector3& translation, ProgressCallback* progressCallback)
{
	if (progressCallback != nullptr) progressCallback->progress(0.0f);
	auto progressStepCurrent = 0;

	// scene library
	auto sceneLibrary = scene->getLibrary();

	// terrain + foliage
	{
		auto prototype = sceneLibrary->getTerrainPrototype();
		if (prototype != nullptr) {
			//
			auto terrain = prototype->getTerrain();
			auto width = terrain->getWidth();
			auto depth = terrain->getDepth();
			auto terrainHeightVectorVerticesPerX = static_cast<int>(Math::ceil(width / Terrain::STEP_SIZE));
			auto terreinHeightVectorVerticesPerZ = static_cast<int>(Math::ceil(depth / Terrain::STEP_SIZE));
			// terrain
			auto minHeight = terrain->getHeightVector()[0];
			auto maxHeight = terrain->getHeightVector()[0];
			for (auto heightValue: terrain->getHeightVector()) {
				if (heightValue < minHeight) minHeight = heightValue;
				if (heightValue > maxHeight) maxHeight = heightValue;
			}
			{
				Transform transform;
				transform.setTranslation(Vector3(width / 2.0f, (minHeight + maxHeight) / 2.0f, depth / 2.0f));
				transform.update();
				auto rigidBody = world->addStaticRigidBody(
					"tdme.terrain",
					BODY_TYPEID_STATIC,
					true,
					transform,
					0.5f,
					{
						new HeightMap(
							terrainHeightVectorVerticesPerX,
							terreinHeightVectorVerticesPerZ,
							minHeight,
							maxHeight,
							terrain->getHeightVector().data()
						)
					}
				);
				rigidBody->setEnabled(enable);
			}
			// single foliage
			{
				//
				const auto& foliageMaps = terrain->getFoliageMaps();

				//
				unordered_map<int, int> prototypeBodyIdx;
				for (const auto& foliageMapPartition: foliageMaps) {
					for (const auto& [prototypeIdx, transformVector]: foliageMapPartition) {
						if (transformVector.empty() == true) continue;
						auto foliagePrototype = prototype->getTerrain()->getFoliagePrototype(prototypeIdx);
						if (foliagePrototype->isRenderGroups() == true) continue;
						for (const auto& foliageTransform: transformVector) {
							auto body = createBody(world, foliagePrototype, "tdme.foliage." + to_string(prototypeIdx) + "." + to_string(prototypeBodyIdx[prototypeIdx]++), foliageTransform);
							if (body == nullptr) continue;
							if (translation.equals(Vector3()) == false) {
								auto transform = foliageTransform;
								transform.setTranslation(transform.getTranslation().clone().add(translation));
								transform.update();
								body->setTransform(transform);
							}
							body->setEnabled(enable);
						}
					}
				}
			}
		}
	}

	//
	for (auto i = 0; i < scene->getEntityCount(); i++) {
		auto sceneEntity = scene->getEntityAt(i);

		//
		if (progressCallback != nullptr && progressStepCurrent % 1000 == 0) progressCallback->progress(0.0f + static_cast<float>(progressStepCurrent) / static_cast<float>(scene->getEntityCount()) * 1.0f);
		progressStepCurrent++;

		//
		auto rigidBody = createBody(world, sceneEntity);
		if (rigidBody == nullptr) continue;
		if (translation.equals(Vector3()) == false) {
			auto transform = sceneEntity->getTransform();
			transform.setTranslation(transform.getTranslation().clone().add(translation));
			transform.update();
			rigidBody->setTransform(transform);
		}
		rigidBody->setEnabled(enable);
	}

	//
	if (progressCallback != nullptr) {
		progressCallback->progress(1.0f);
		delete progressCallback;
	}
}

void SceneConnector::disableScene(Engine* engine, Scene* scene)
{
	// terrain + water + foliage render groups + render groups
	{
		auto idx = 0;
		Entity* entity = nullptr;
		while ((entity = engine->getEntity("tdme.terrain." + to_string(idx++))) != nullptr) {
			entity->setEnabled(false);
		}
	}
	{
		auto idx = 0;
		Entity* entity = nullptr;
		while ((entity = engine->getEntity("tdme.water." + to_string(idx++))) != nullptr) {
			entity->setEnabled(false);
		}
	}
	{
		auto idx = 0;
		Entity* entity = nullptr;
		while ((entity = engine->getEntity("tdme.fo3rg." + to_string(idx++))) != nullptr) {
			entity->setEnabled(false);
		}
	}
	{
		auto idx = 0;
		Entity* entity = nullptr;
		while ((entity = engine->getEntity("tdme.o3rg." + to_string(idx++))) != nullptr) {
			entity->setEnabled(false);
		}
	}

	// scene library
	auto sceneLibrary = scene->getLibrary();

	// single foliage
	{
		auto prototype = sceneLibrary->getTerrainPrototype();
		if (prototype != nullptr) {
			//
			auto terrain = prototype->getTerrain();
			//
			for (auto prototypeIdx: terrain->getFoliagePrototypeIndices()) {
				auto foliagePrototype = prototype->getTerrain()->getFoliagePrototype(prototypeIdx);
				if (foliagePrototype->isRenderGroups() == true) continue;
				for (auto& entityId: terrain->getFoliagePrototypeEntityIds(prototypeIdx)) {
					auto entity = engine->getEntity(entityId);
					if (entity != nullptr) entity->setEnabled(false);
				}
			}
		}
	}

	// scene entities
	for (auto i = 0; i < scene->getEntityCount(); i++) {
		auto sceneEntity = scene->getEntityAt(i);
		auto entity = engine->getEntity(sceneEntity->getId());
		if (entity == nullptr)
			continue;

		entity->setEnabled(false);
	}
}

void SceneConnector::disableScene(World* world, Scene* scene)
{
	// terrain
	{
		auto body = world->getBody("tdme.terrain");
		if (body != nullptr) body->setEnabled(false);
	}

	// scene library
	auto sceneLibrary = scene->getLibrary();

	// single foliage
	{
		auto prototype = sceneLibrary->getTerrainPrototype();
		if (prototype != nullptr) {
			//
			auto terrain = prototype->getTerrain();
			//
			for (auto prototypeIdx: terrain->getFoliagePrototypeIndices()) {
				auto foliagePrototype = prototype->getTerrain()->getFoliagePrototype(prototypeIdx);
				if (foliagePrototype->isRenderGroups() == true) continue;
				for (auto& bodyId: terrain->getFoliagePrototypeEntityIds(prototypeIdx)) {
					auto body = world->getBody(bodyId);
					if (body != nullptr) body->setEnabled(false);
				}
			}
		}
	}

	// scene entities
	for (auto i = 0; i < scene->getEntityCount(); i++) {
		auto sceneEntity = scene->getEntityAt(i);
		auto body = world->getBody(sceneEntity->getId());
		if (body == nullptr) continue;
		body->setEnabled(false);
	}
}

void SceneConnector::enableScene(Engine* engine, Scene* scene, const Vector3& translation)
{
	// terrain + water + foliage render groups + render groups
	{
		auto idx = 0;
		Entity* entity = nullptr;
		while ((entity = engine->getEntity("tdme.terrain." + to_string(idx++))) != nullptr) {
			entity->setEnabled(true);
		}
	}
	{
		auto idx = 0;
		Entity* entity = nullptr;
		while ((entity = engine->getEntity("tdme.water." + to_string(idx++))) != nullptr) {
			entity->setEnabled(true);
		}
	}
	{
		auto idx = 0;
		Entity* entity = nullptr;
		while ((entity = engine->getEntity("tdme.fo3rg." + to_string(idx++))) != nullptr) {
			entity->setEnabled(true);
		}
	}
	{
		auto idx = 0;
		Entity* entity = nullptr;
		while ((entity = engine->getEntity("tdme.o3rg." + to_string(idx++))) != nullptr) {
			entity->setEnabled(true);
		}
	}

	// scene library
	auto sceneLibrary = scene->getLibrary();

	// single foliage
	{
		auto prototype = sceneLibrary->getTerrainPrototype();
		if (prototype != nullptr) {
			//
			auto terrain = prototype->getTerrain();
			//
			for (auto prototypeIdx: terrain->getFoliagePrototypeIndices()) {
				auto foliagePrototype = prototype->getTerrain()->getFoliagePrototype(prototypeIdx);
				if (foliagePrototype->isRenderGroups() == true) continue;
				for (auto& entityId: terrain->getFoliagePrototypeEntityIds(prototypeIdx)) {
					auto entity = engine->getEntity(entityId);
					if (entity != nullptr) entity->setEnabled(true);
				}
			}
		}
	}

	// scene entities
	for (auto i = 0; i < scene->getEntityCount(); i++) {
		auto sceneEntity = scene->getEntityAt(i);
		auto entity = engine->getEntity(sceneEntity->getId());
		if (entity == nullptr)
			continue;

		entity->setTransform(sceneEntity->getTransform());
		entity->setTranslation(entity->getTranslation().clone().add(translation));
		if (sceneEntity->getPrototype()->getType() == Prototype_Type::EMPTY) {
			entity->setScale(Vector3(Math::sign(entity->getScale().getX()), Math::sign(entity->getScale().getY()), Math::sign(entity->getScale().getZ())));
		}
		entity->update();
		entity->setEnabled(true);
	}
}

void SceneConnector::enableScene(World* world, Scene* scene, const Vector3& translation)
{
	// terrain
	{
		auto body = world->getBody("tdme.terrain");
		if (body != nullptr) {
			body->setEnabled(true);
			// TODO: translate
		}
	}

	// scene library
	auto sceneLibrary = scene->getLibrary();

	// single foliage
	{
		auto prototype = sceneLibrary->getTerrainPrototype();
		if (prototype != nullptr) {
			//
			auto terrain = prototype->getTerrain();
			//
			for (auto prototypeIdx: terrain->getFoliagePrototypeIndices()) {
				auto foliagePrototype = prototype->getTerrain()->getFoliagePrototype(prototypeIdx);
				if (foliagePrototype->isRenderGroups() == true) continue;
				for (auto& bodyId: terrain->getFoliagePrototypeEntityIds(prototypeIdx)) {
					auto body = world->getBody(bodyId);
					if (body != nullptr) body->setEnabled(true);
				}
			}
		}
	}

	// scene entities
	Transform transform;
	for (auto i = 0; i < scene->getEntityCount(); i++) {
		auto sceneEntity = scene->getEntityAt(i);
		auto rigidBody = world->getBody(sceneEntity->getId());
		if (rigidBody == nullptr) continue;
		transform.setTransform(sceneEntity->getTransform());
		transform.setTranslation(transform.getTranslation().clone().add(translation));
		transform.update();
		rigidBody->setTransform(transform);
		rigidBody->setEnabled(true);
	}
}

void SceneConnector::resetEngine(Engine* engine, Scene* scene) {
	{
		auto idx = 0;
		Entity* entity = nullptr;
		while ((entity = engine->getEntity("tdme.terrain." + to_string(idx++))) != nullptr) {
			Model* model = nullptr;
			if (entity->getEntityType() == Entity::ENTITYTYPE_OBJECT) model = static_cast<Object*>(entity)->getModel();
			engine->removeEntity(entity->getId());
			if (model != nullptr) delete model;
		}
	}
	{
		auto idx = 0;
		Entity* entity = nullptr;
		while ((entity = engine->getEntity("tdme.water." + to_string(idx++))) != nullptr) {
			Model* model = nullptr;
			if (entity->getEntityType() == Entity::ENTITYTYPE_OBJECT) model = static_cast<Object*>(entity)->getModel();
			engine->removeEntity(entity->getId());
			if (model != nullptr) delete model;
		}
	}
	//
	engine->reset();
}

void SceneConnector::addSounds(Audio* audio, Prototype* prototype, const string& id, int poolSize) {
	for (auto soundDefinition: prototype->getSounds()) {
		if (soundDefinition->getFileName().length() > 0) {
			for (auto poolIdx = 0; poolIdx < poolSize; poolIdx++) {
				string pathName = PrototypeReader::getResourcePathName(
					Tools::getPathName(prototype->getFileName()),
					soundDefinition->getFileName()
				);
				string fileName = Tools::getFileName(soundDefinition->getFileName());
				auto sound = new Sound(
					id + "." + soundDefinition->getId() + (poolSize > 1?"." + to_string(poolIdx):""),
					pathName,
					fileName
				);
				sound->setGain(soundDefinition->getGain());
				sound->setPitch(soundDefinition->getPitch());
				sound->setLooping(soundDefinition->isLooping());
				sound->setFixed(soundDefinition->isFixed());
				audio->addEntity(sound);
			}
		}
	}
}

