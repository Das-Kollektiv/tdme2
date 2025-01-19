#include <tdme/engine/Engine.h>

#include <algorithm>
#include <list>
#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/fileio/textures/PNGTextureWriter.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/model/Node.h>
#include <tdme/engine/physics/CollisionDetection.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/LineSegment.h>
#include <tdme/engine/subsystems/environmentmapping/EnvironmentMappingRenderer.h>
#include <tdme/engine/subsystems/framebuffer/BRDFLUTShader.h>
#include <tdme/engine/subsystems/framebuffer/DeferredLightingRenderShader.h>
#include <tdme/engine/subsystems/framebuffer/FrameBufferRenderShader.h>
#include <tdme/engine/subsystems/framebuffer/SkyRenderShader.h>
#include <tdme/engine/subsystems/lighting/LightingShader.h>
#include <tdme/engine/subsystems/lines/LinesShader.h>
#include <tdme/engine/subsystems/manager/MeshManager.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/particlesystem/ParticlesShader.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessing.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingProgram.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShader.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/subsystems/rendering/EntityRenderer.h>
#include <tdme/engine/subsystems/rendering/EntityRenderer_InstancedRenderFunctionParameters.h>
#include <tdme/engine/subsystems/rendering/ObjectBase_TransformedFacesIterator.h>
#include <tdme/engine/subsystems/rendering/ObjectBuffer.h>
#include <tdme/engine/subsystems/rendering/ObjectNodeMesh.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderFacesPool.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMap.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapping.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapCreationShader.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapRenderShader.h>
#include <tdme/engine/subsystems/skinning/SkinningShader.h>
#include <tdme/engine/subsystems/texture2D/Texture2DRenderShader.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Decal.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/EntityHierarchy.h>
#include <tdme/engine/EntityPickingFilter.h>
#include <tdme/engine/EnvironmentMapping.h>
#include <tdme/engine/FogParticleSystem.h>
#include <tdme/engine/FrameBuffer.h>
#include <tdme/engine/GeometryBuffer.h>
#include <tdme/engine/ImposterObject.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/Lines.h>
#include <tdme/engine/LODObject.h>
#include <tdme/engine/LODObjectImposter.h>
#include <tdme/engine/Object.h>
#include <tdme/engine/ObjectParticleSystem.h>
#include <tdme/engine/ObjectRenderGroup.h>
#include <tdme/engine/OctTreePartition.h>
#include <tdme/engine/ParticleSystem.h>
#include <tdme/engine/ParticleSystemGroup.h>
#include <tdme/engine/Partition.h>
#include <tdme/engine/PointsParticleSystem.h>
#include <tdme/engine/ShaderParameter.h>
#include <tdme/engine/Timing.h>
#include <agui/gui/renderer/GUIRenderer.h>
#include <agui/gui/renderer/GUIShader.h>
#include <agui/gui/GUI.h>
#include <agui/gui/GUIParser.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/os/threading/Queue.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/TextureAtlas.h>

using std::list;
using std::make_unique;
using std::move;
using std::remove;
using std::sort;
using std::string;
using std::to_string;
using std::unique_ptr;

using tdme::application::Application;
using tdme::engine::fileio::textures::PNGTextureWriter;
using tdme::engine::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::Color4;
using tdme::engine::model::Node;
using tdme::engine::physics::CollisionDetection;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::LineSegment;
using tdme::engine::subsystems::environmentmapping::EnvironmentMappingRenderer;
using tdme::engine::subsystems::framebuffer::BRDFLUTShader;
using tdme::engine::subsystems::framebuffer::DeferredLightingRenderShader;
using tdme::engine::subsystems::framebuffer::FrameBufferRenderShader;
using tdme::engine::subsystems::framebuffer::SkyRenderShader;
using tdme::engine::subsystems::lighting::LightingShader;
using tdme::engine::subsystems::lines::LinesShader;
using tdme::engine::subsystems::manager::MeshManager;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::particlesystem::ParticlesShader;
using tdme::engine::subsystems::postprocessing::PostProcessing;
using tdme::engine::subsystems::postprocessing::PostProcessingProgram;
using tdme::engine::subsystems::postprocessing::PostProcessingShader;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::subsystems::rendering::EntityRenderer;
using tdme::engine::subsystems::rendering::EntityRenderer_InstancedRenderFunctionParameters;
using tdme::engine::subsystems::rendering::ObjectBase_TransformedFacesIterator;
using tdme::engine::subsystems::rendering::ObjectBuffer;
using tdme::engine::subsystems::rendering::TransparentRenderFacesPool;
using tdme::engine::subsystems::shadowmapping::ShadowMap;
using tdme::engine::subsystems::shadowmapping::ShadowMapping;
using tdme::engine::subsystems::shadowmapping::ShadowMapCreationShader;
using tdme::engine::subsystems::shadowmapping::ShadowMapRenderShader;
using tdme::engine::subsystems::skinning::SkinningShader;
using tdme::engine::subsystems::texture2D::Texture2DRenderShader;
using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::EntityHierarchy;
using tdme::engine::EntityPickingFilter;
using tdme::engine::FogParticleSystem;
using tdme::engine::FrameBuffer;
using tdme::engine::GeometryBuffer;
using tdme::engine::ImposterObject;
using tdme::engine::Light;
using tdme::engine::Lines;
using tdme::engine::LODObject;
using tdme::engine::LODObjectImposter;
using tdme::engine::Object;
using tdme::engine::ObjectParticleSystem;
using tdme::engine::ObjectRenderGroup;
using tdme::engine::OctTreePartition;
using tdme::engine::ParticleSystem;
using tdme::engine::ParticleSystemGroup;
using tdme::engine::Partition;
using tdme::engine::PointsParticleSystem;
using tdme::engine::ShaderParameter;
using tdme::engine::Timing;
using agui::gui::renderer::GUIRenderer;
using agui::gui::renderer::GUIShader;
using agui::gui::GUI;
using agui::gui::GUIParser;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::os::threading::Queue;
using tdme::os::threading::Thread;
using tdme::utilities::ByteBuffer;
using tdme::utilities::Console;
using tdme::utilities::Float;
using tdme::utilities::TextureAtlas;

Engine* Engine::instance = nullptr;
RendererBackend* Engine::rendererBackend = nullptr;
unique_ptr<TextureManager> Engine::textureManager;
unique_ptr<VBOManager> Engine::vboManager;
unique_ptr<MeshManager> Engine::meshManager;
unique_ptr<GUIRenderer> Engine::guiRenderer;
unique_ptr<BRDFLUTShader> Engine::brdfLUTShader;
unique_ptr<FrameBufferRenderShader> Engine::frameBufferRenderShader;
unique_ptr<DeferredLightingRenderShader> Engine::deferredLightingRenderShader;
unique_ptr<SkyRenderShader> Engine::skyRenderShader;
unique_ptr<PostProcessing> Engine::postProcessing;
unique_ptr<PostProcessingShader> Engine::postProcessingShader;
unique_ptr<Texture2DRenderShader> Engine::texture2DRenderShader;
Engine::AnimationProcessingTarget Engine::animationProcessingTarget = Engine::AnimationProcessingTarget::CPU;
unique_ptr<ShadowMapCreationShader> Engine::shadowMappingShaderPre;
unique_ptr<ShadowMapRenderShader> Engine::shadowMappingShaderRender;
unique_ptr<LightingShader> Engine::lightingShader;
unique_ptr<ParticlesShader> Engine::particlesShader;
unique_ptr<LinesShader> Engine::linesShader;
unique_ptr<SkinningShader> Engine::skinningShader;
unique_ptr<GUIShader> Engine::guiShader;
Engine* Engine::currentEngine = nullptr;
bool Engine::skinningShaderEnabled = false;
int Engine::threadCount = 0;
bool Engine::have4K = false;
float Engine::animationBlendingTime = 250.0f;
int32_t Engine::shadowMapWidth = 0;
int32_t Engine::shadowMapHeight = 0;
int32_t Engine::shadowMapRenderLookUps = 0;
int32_t Engine::environmentMappingWidth = 1024;
int32_t Engine::environmentMappingHeight = 1024;
float Engine::animationComputationReduction1Distance = 25.0f;
float Engine::animationComputationReduction2Distance = 50.0f;
list<Engine::Shader> Engine::shaders;
unordered_map<string, Engine::Shader*> Engine::shadersById;
unordered_map<string, uint8_t> Engine::uniqueShaderIds;

vector<unique_ptr<Engine::EngineThread>> Engine::engineThreads;
unique_ptr<Queue<Engine::EngineThreadQueueElement>> Engine::engineThreadsQueue;
Engine::EngineThreadQueueElementPool Engine::engineThreadQueueElementPool;

Engine::EngineThread::EngineThread(int idx, Queue<EngineThreadQueueElement>* queue):
	Thread("enginethread"),
	idx(idx),
	queue(queue) {
	//
	transparentRenderFacesPool = make_unique<TransparentRenderFacesPool>();
}

void Engine::EngineThread::run() {
	Console::printLine("EngineThread::" + string(__FUNCTION__) + "()[" + to_string(idx) + "]: INIT");
	while (isStopRequested() == false) {
		auto element = queue->getElement();
		if (element == nullptr) break;
		switch(element->type) {
			case EngineThreadQueueElement::TYPE_NONE:
				break;
			case EngineThreadQueueElement::TYPE_PRERENDER:
				element->engine->preRenderFunction(
					element->objects,
					idx
				);
				element->objects.clear();
				elementsProcessed++;
				break;
			case EngineThreadQueueElement::TYPE_ANIMATIONS:
				element->engine->computeAnimationsFunction(
					element->objects,
					idx
				);
				element->objects.clear();
				elementsProcessed++;
				break;
			case EngineThreadQueueElement::TYPE_RENDERING:
				element->engine->entityRenderer->renderFunction(
					idx,
					element->rendering.renderPass,
					element->objects,
					objectsByModels,
					element->rendering.collectTransparentFaces,
					element->rendering.renderTypes,
					transparentRenderFacesPool.get()
				);
				element->objects.clear();
				elementsProcessed++;
				break;
		}
	}
	Console::printLine("EngineThread::" + string(__FUNCTION__) + "()[" + to_string(idx) + "]: DONE");
}

void Engine::shutdown() {
	if (instance == nullptr) return;
	delete instance;
	instance = nullptr;
}

Engine::Engine() {
	timing = make_unique<Timing>();
	sceneColor.set(0.0f, 0.0f, 0.0f, 1.0f);
	// shadow mapping
	shadowMappingEnabled = false;
	skyShaderEnabled = false;
	//
	initialized = false;
	// post processing frame buffers
	//
	isUsingPostProcessingTemporaryFrameBuffer = false;
	//
	effectPassSkip.fill(false);
}

Engine::~Engine() {
	// set current engine
	if (currentEngine == this) currentEngine = nullptr;
}

void Engine::loadTextures(const string& pathName) {
	lightingShader->loadTextures(pathName);
	postProcessingShader->loadTextures(pathName);
	skyRenderShader->loadTextures(pathName);
	if (shadowMappingShaderPre != nullptr) shadowMappingShaderPre->loadTextures(pathName);
	if (shadowMappingShaderRender != nullptr) shadowMappingShaderRender->loadTextures(pathName);
}

Engine* Engine::createOffScreenInstance(int32_t width, int32_t height, bool enableShadowMapping, bool enableDepthBuffer, bool enableGeometryBuffer)
{
	if (instance == nullptr || instance->initialized == false) {
		Console::printLine(string("Engine::createOffScreenInstance(): Engine not created or not initialized."));
		return nullptr;
	}
	// create off screen engine
	auto offScreenEngine = new Engine();
	offScreenEngine->initialized = true;
	// create GUI
	//	TODO: GUIApplication: xxx
	//	TODO: rendererBackend: xxx
	offScreenEngine->gui = make_unique<GUI>(nullptr, nullptr, width, height);
	// create entity renderer
	offScreenEngine->entityRenderer = make_unique<EntityRenderer>(offScreenEngine, rendererBackend);
	offScreenEngine->entityRenderer->initialize();
	// create framebuffers
	offScreenEngine->frameBuffer = make_unique<FrameBuffer>(width, height, (enableDepthBuffer == true?FrameBuffer::FRAMEBUFFER_DEPTHBUFFER:0) | FrameBuffer::FRAMEBUFFER_COLORBUFFER);
	offScreenEngine->frameBuffer->initialize();
	// create camera, frustum partition
	offScreenEngine->camera = make_unique<Camera>(rendererBackend);
	offScreenEngine->gizmoCamera = make_unique<Camera>(rendererBackend);
	offScreenEngine->gizmoCamera->setFrustumMode(Camera::FRUSTUMMODE_ORTHOGRAPHIC);
	offScreenEngine->gizmoCamera->setCameraMode(Camera::CAMERAMODE_NONE);
	offScreenEngine->gizmoCamera->setForwardVector(Vector3(0.0f, 0.0f, -1.0f));
	offScreenEngine->gizmoCamera->setSideVector(Vector3(1.0f, 0.0f, 0.0f));
	offScreenEngine->gizmoCamera->setUpVector(Vector3(0.0f, 1.0f, 0.0f));
	offScreenEngine->gizmoCamera->setZNear(1.0f);
	offScreenEngine->gizmoCamera->setZFar(400.0f);
	offScreenEngine->partition = make_unique<OctTreePartition>();
	// create lights
	for (auto i = 0; i < offScreenEngine->lights.size(); i++) {
		offScreenEngine->lights[i] = make_unique<Light>(rendererBackend, i);
		offScreenEngine->lights[i]->setSourceTexture(TextureReader::read("resources/engine/textures", "sun.png"));
	}
	// create shadow mapping
	if (instance->shadowMappingEnabled == true && enableShadowMapping == true) {
		offScreenEngine->shadowMapping = make_unique<ShadowMapping>(offScreenEngine, rendererBackend, offScreenEngine->entityRenderer.get());
	}
	// geometry buffer
	if (rendererBackend->isDeferredShadingAvailable() == true && enableGeometryBuffer == true) {
		offScreenEngine->geometryBuffer = make_unique<GeometryBuffer>(width, height);
		offScreenEngine->geometryBuffer->initialize();
	}
	//
	offScreenEngine->reshape(width, height);
	return offScreenEngine;
}

const string Engine::getGraphicsVendor() {
	return rendererBackend->getVendor();
}

const string Engine::getGraphicsRenderer() {
	return rendererBackend->getRenderer();
}

void Engine::setPartition(Partition* partition)
{
	this->partition = unique_ptr<Partition>(partition);
}

void Engine::addEntity(Entity* entity)
{
	{
		auto entityByIdIt = entitiesById.find(entity->getId());
		if (entityByIdIt != entitiesById.end()) {
			// check if we want to add this entity a second time
			if (entity == entityByIdIt->second) {
				Console::printLine("Engine::addEntity(): " + entity->getId() + ": entity already added!");
				return;
			}
			// dispose old entity if any did exist in engine with same id
			removeEntity(entity->getId());
		}
	}

	// init entity
	entity->setEngine(this);
	entity->setRenderer(rendererBackend);
	entity->initialize();
	entitiesById[entity->getId()] = entity;

	// add to partition if enabled and frustum culling requested
	if (entity->isFrustumCulling() == true && entity->isEnabled() == true) partition->addEntity(entity);
}

void Engine::deregisterEntity(Entity* entity) {
	//
	noFrustumCullingEntities.erase(entity);
	visibleDecomposedEntities.noFrustumCullingEntities.erase(
		remove(
			visibleDecomposedEntities.noFrustumCullingEntities.begin(),
			visibleDecomposedEntities.noFrustumCullingEntities.end(),
			entity
		),
		visibleDecomposedEntities.noFrustumCullingEntities.end());
	autoEmitParticleSystemEntities.erase(entity);
	requireComputeAnimationEntities.erase(entity);
	requirePreRenderEntities.erase(entity);

	// decompose and deregister decal and pps textures
	DecomposedEntities decomposedEntities;
	decomposeEntityType(entity, decomposedEntities, true);
	// objects
	array<vector<Object*>*, 5> objectsArray = {
		&decomposedEntities.objects,
		&decomposedEntities.objectsForwardShading,
		&decomposedEntities.objectsNoDepthTest,
		&decomposedEntities.objectsPostPostProcessing,
		&decomposedEntities.objectsGizmo,
	};
	for (auto& objects: objectsArray) {
		for (auto object: *objects) {
			if (object->getUniqueModelId() != UNIQUEMODELID_NONE) {
				deregisterModel(object->getModel());
				object->setUniqueModelId(UNIQUEMODELID_NONE);
			}
		}
	}
	// decal textures
	for (auto decalEntity: decomposedEntities.decalEntities) {
		decalsTextureAtlas.removeTexture(decalEntity->getDecalTexture());
	}
	// remove pps/fps textures
	for (auto ppsEntity: decomposedEntities.ppses) {
		auto entityType = ppsEntity->getEntityType();
		switch (entityType) {
			case Entity::ENTITYTYPE_FOGPARTICLESYSTEM:
				ppsTextureAtlas.removeTexture(static_cast<FogParticleSystem*>(ppsEntity)->getTexture());
				break;
			case Entity::ENTITYTYPE_POINTSPARTICLESYSTEM:
				ppsTextureAtlas.removeTexture(static_cast<PointsParticleSystem*>(ppsEntity)->getTexture());
				break;
			default:
				break;
		}
	}
	//
	removeEntityFromLists(entity);
}

void Engine::registerEntity(Entity* entity) {
	//
	noFrustumCullingEntities.erase(entity);
	visibleDecomposedEntities.noFrustumCullingEntities.erase(
		remove(
			visibleDecomposedEntities.noFrustumCullingEntities.begin(),
			visibleDecomposedEntities.noFrustumCullingEntities.end(),
			entity
		),
		visibleDecomposedEntities.noFrustumCullingEntities.end()
	);
	autoEmitParticleSystemEntities.erase(entity);

	// add to no frustum culling
	if (entity->isFrustumCulling() == false && entity->getParentEntity() == nullptr) {
		// otherwise add to no frustum culling entities
		noFrustumCullingEntities.insert(entity);
		visibleDecomposedEntities.noFrustumCullingEntities.push_back(entity);
	}

	// add to auto emit particle system entities
	auto particleSystemEntity = dynamic_cast<ParticleSystem*>(entity);
	if (particleSystemEntity != nullptr && particleSystemEntity->isAutoEmit() == true) {
		autoEmitParticleSystemEntities.insert(particleSystemEntity);
	}

	// decompose to engine instances to do pre render
	DecomposedEntities decomposedEntities;
	decomposeEntityType(entity, decomposedEntities, true);
	// objects
	array<vector<Object*>*, 5> objectsArray = {
		&decomposedEntities.objects,
		&decomposedEntities.objectsForwardShading,
		&decomposedEntities.objectsNoDepthTest,
		&decomposedEntities.objectsPostPostProcessing,
		&decomposedEntities.objectsGizmo,
	};
	for (auto& objects: objectsArray) {
		for (auto object: *objects) {
			object->preRender(rendererBackend->CONTEXTINDEX_DEFAULT);
			if (object->isRequiringPreRender() == true) requirePreRenderEntities.insert(object);
			if (object->isRequiringAnimationComputation() == true) requireComputeAnimationEntities.insert(object);
			if (object->getUniqueModelId() == UNIQUEMODELID_NONE) object->setUniqueModelId(registerModel(object->getModel()));
		}
	}
	// decal textures
	for (auto decalEntity: decomposedEntities.decalEntities) {
		decalsTextureAtlas.addTexture(decalEntity->getDecalTexture());
	}
	// // remove pps/fps textures
	for (auto ppsEntity: decomposedEntities.ppses) {
		auto entityType = ppsEntity->getEntityType();
		switch (entityType) {
			case Entity::ENTITYTYPE_FOGPARTICLESYSTEM:
				ppsTextureAtlas.addTexture(static_cast<FogParticleSystem*>(ppsEntity)->getTexture());
				break;
			case Entity::ENTITYTYPE_POINTSPARTICLESYSTEM:
				ppsTextureAtlas.addTexture(static_cast<PointsParticleSystem*>(ppsEntity)->getTexture());
				break;
			default:
				break;
		}
	}
}

bool Engine::removeEntity(const string& id)
{
	// get entity and remove if we have any
	auto entityByIdIt = entitiesById.find(id);
	if (entityByIdIt == entitiesById.end()) return false;

	//
	auto entity = entityByIdIt->second;

	//
	entitiesById.erase(entityByIdIt);
	autoEmitParticleSystemEntities.erase(entity);
	noFrustumCullingEntities.erase(entity);
	requirePreRenderEntities.erase(entity);
	requireComputeAnimationEntities.erase(entity);

	// remove from partition if enabled and frustum culling requested
	if (entity->isFrustumCulling() == true && entity->isEnabled() == true) partition->removeEntity(entity);

	//
	removeEntityFromLists(entity);

	// dispose entity
	entity->dispose();
	entity->setEngine(nullptr);
	entity->setRenderer(nullptr);
	delete entity;

	//
	return true;
}

inline void Engine::removeFromDecomposedEntities(DecomposedEntities& decomposedEntities, Entity* entity) {
	// delete from lists
	decomposedEntities.objects.erase(
		remove(
			decomposedEntities.objects.begin(),
			decomposedEntities.objects.end(),
			entity
		),
		decomposedEntities.objects.end()
	);
	decomposedEntities.objectsForwardShading.erase(
		remove(
			decomposedEntities.objectsForwardShading.begin(),
			decomposedEntities.objectsForwardShading.end(),
			entity
		),
		decomposedEntities.objectsForwardShading.end()
	);
	decomposedEntities.objectsPostPostProcessing.erase(
		remove(
			decomposedEntities.objectsPostPostProcessing.begin(),
			decomposedEntities.objectsPostPostProcessing.end(),
			entity
		),
		decomposedEntities.objectsPostPostProcessing.end()
	);
	decomposedEntities.objectsNoDepthTest.erase(
		remove(
			decomposedEntities.objectsNoDepthTest.begin(),
			decomposedEntities.objectsNoDepthTest.end(),
			entity
		),
		decomposedEntities.objectsNoDepthTest.end()
	);
	decomposedEntities.objectsGizmo.erase(
		remove(
			decomposedEntities.objectsGizmo.begin(),
			decomposedEntities.objectsGizmo.end(),
			entity
		),
		decomposedEntities.objectsGizmo.end()
	);
	decomposedEntities.lodObjects.erase(
		remove(
			decomposedEntities.lodObjects.begin(),
			decomposedEntities.lodObjects.end(),
			entity
		),
		decomposedEntities.lodObjects.end()
	);
	decomposedEntities.opses.erase(
		remove(
			decomposedEntities.opses.begin(),
			decomposedEntities.opses.end(),
			entity
		),
		decomposedEntities.opses.end()
	);
	decomposedEntities.ppses.erase(
		remove(
			decomposedEntities.ppses.begin(),
			decomposedEntities.ppses.end(),
			entity
		),
		decomposedEntities.ppses.end()
	);
	decomposedEntities.psgs.erase(
		remove(
			decomposedEntities.psgs.begin(),
			decomposedEntities.psgs.end(),
			entity
		),
		decomposedEntities.psgs.end()
	);
	decomposedEntities.linesEntities.erase(
		remove(
			decomposedEntities.linesEntities.begin(),
			decomposedEntities.linesEntities.end(),
			entity
		),
		decomposedEntities.linesEntities.end()
	);
	decomposedEntities.decalEntities.erase(
		remove(
			decomposedEntities.decalEntities.begin(),
			decomposedEntities.decalEntities.end(),
			entity
		),
		decomposedEntities.decalEntities.end()
	);
	decomposedEntities.objectRenderGroups.erase(
		remove(
			decomposedEntities.objectRenderGroups.begin(),
			decomposedEntities.objectRenderGroups.end(),
			entity
		),
		decomposedEntities.objectRenderGroups.end()
	);
	decomposedEntities.entityHierarchies.erase(
		remove(
			decomposedEntities.entityHierarchies.begin(),
			decomposedEntities.entityHierarchies.end(),
			entity
		),
		decomposedEntities.entityHierarchies.end()
	);
	decomposedEntities.noFrustumCullingEntities.erase(
		remove(
			decomposedEntities.noFrustumCullingEntities.begin(),
			decomposedEntities.noFrustumCullingEntities.end(),
			entity
		),
		decomposedEntities.noFrustumCullingEntities.end()
	);
	decomposedEntities.environmentMappingEntities.erase(
		remove(
			decomposedEntities.environmentMappingEntities.begin(),
			decomposedEntities.environmentMappingEntities.end(),
			entity
		),
		decomposedEntities.environmentMappingEntities.end()
	);
	decomposedEntities.requirePreRenderEntities.erase(
		remove(
			decomposedEntities.requirePreRenderEntities.begin(),
			decomposedEntities.requirePreRenderEntities.end(),
			entity
		),
		decomposedEntities.requirePreRenderEntities.end()
	);
	decomposedEntities.requireComputeAnimationEntities.erase(
		remove(
			decomposedEntities.requireComputeAnimationEntities.begin(),
			decomposedEntities.requireComputeAnimationEntities.end(),
			entity
		),
		decomposedEntities.requireComputeAnimationEntities.end()
	);
}

void Engine::removeEntityFromLists(Entity* entity)
{
	if (entity == nullptr) return;
	//
	removeFromDecomposedEntities(visibleDecomposedEntities, entity);
	//
	if (entity->getEntityType() == Entity::ENTITYTYPE_OBJECTRENDERGROUP) {
		removeEntityFromLists(static_cast<ObjectRenderGroup*>(entity)->getEntity());
	} else
	if (entity->getEntityType() == Entity::ENTITYTYPE_OBJECTPARTICLESYSTEM) {
		auto ops = static_cast<ObjectParticleSystem*>(entity);
		for (auto subEntity: ops->getObjects()) {
			removeEntityFromLists(subEntity);
		}
	} else
	if (entity->getEntityType() == Entity::ENTITYTYPE_ENTITYHIERARCHY) {
		auto eh = static_cast<EntityHierarchy*>(entity);
		for (auto subEntity: eh->getEntities()) {
			removeEntityFromLists(subEntity);
		}
	} else
	if (entity->getEntityType() == Entity::ENTITYTYPE_LODOBJECT) {
		auto lo = static_cast<LODObject*>(entity);
		removeEntityFromLists(lo->getLOD1Object());
		removeEntityFromLists(lo->getLOD2Object());
		removeEntityFromLists(lo->getLOD3Object());
	} else
	if (entity->getEntityType() == Entity::ENTITYTYPE_IMPOSTEROBJECT) {
		auto io = static_cast<ImposterObject*>(entity);
		for (auto subEntity: io->getBillboardObjects()) removeEntityFromLists(subEntity);
	} else
	if (entity->getEntityType() == Entity::ENTITYTYPE_LODOBJECTIMPOSTER) {
		auto loi = static_cast<LODObjectImposter*>(entity);
		removeEntityFromLists(loi->getLOD1Object());
		for (auto subEntity: loi->getLOD2Object()->getBillboardObjects()) removeEntityFromLists(subEntity);
	} else
	if (entity->getEntityType() == Entity::ENTITYTYPE_PARTICLESYSTEMGROUP) {
		auto psg = static_cast<ParticleSystemGroup*>(entity);
		for (auto subEntity: psg->getParticleSystems()) removeEntityFromLists(subEntity);
	}
}

void Engine::reset()
{
	vector<string> entitiesToRemove;
	for (const auto& [entityId, entity]: entitiesById) {
		entitiesToRemove.push_back(entityId);
	}
	for (const auto& entityKey: entitiesToRemove) {
		removeEntity(entityKey);
	}
	partition->reset();
	entityRenderer->reset();
	if (skinningShaderEnabled == true) skinningShader->reset();
	objectUniqueModelIdMapping.clear();
	freeObjectUniqueModelIdIds.clear();
	// TODO: reset engine thread queue element pool
}

void Engine::initialize()
{
	// set current engine
	currentEngine = this;

	// exit if already initialized like a offscreen engine instance
	if (initialized == true)
		return;

	//
	rendererBackend = Application::getRendererBackend();
	if (rendererBackend == nullptr) {
		initialized = false;
		Console::printLine("No renderer backend: Exiting!");
		Application::exit(0);
		return;
	}

	//
	shadowMappingEnabled = true;
	if (shadowMappingEnabled == true) {
		if (getShadowMapWidth() == 0 || getShadowMapHeight() == 0) setShadowMapSize(2048, 2048);
		if (getShadowMapRenderLookUps() == 0) setShadowMapRenderLookUps(8);
	}
	animationProcessingTarget = rendererBackend->isGLCLAvailable() == true || rendererBackend->isComputeShaderAvailable() == true?Engine::AnimationProcessingTarget::GPU:Engine::AnimationProcessingTarget::CPU;

	// determine if we have the skinning compute shader or OpenCL program
	skinningShaderEnabled = rendererBackend->isComputeShaderAvailable() == true || rendererBackend->isGLCLAvailable() == true;
	animationProcessingTarget = skinningShaderEnabled == true?Engine::AnimationProcessingTarget::GPU:Engine::AnimationProcessingTarget::CPU;

	// engine thread count
	if (rendererBackend->isSupportingMultithreadedRendering() == true) {
		if (threadCount == 0) threadCount = Math::clamp(Thread::getHardwareThreadCount() == 0?3:Thread::getHardwareThreadCount() / 2, 2, 3);
	} else {
		threadCount = 1;
	}

	Console::printLine(string("TDME2::Thread count: ") + to_string(threadCount));

	// initialize object buffers
	ObjectBuffer::initialize();

	// create manager
	textureManager = make_unique<TextureManager>(rendererBackend);
	vboManager = make_unique<VBOManager>(rendererBackend);
	meshManager = make_unique<MeshManager>();

	// init
	initialized = true;
	rendererBackend->initialize();
	rendererBackend->initializeFrame();

	// graphics device
	Console::printLine(string("TDME2::Renderer::Graphics Vendor: ") + rendererBackend->getVendor());
	Console::printLine(string("TDME2::Renderer::Graphics Renderer: ") + rendererBackend->getRenderer());

	// create entity renderer
	entityRenderer = make_unique<EntityRenderer>(this, rendererBackend);
	entityRenderer->initialize();
	GUIParser::initialize();

	// create GUI
	//	TODO: rendererBackend: xxx
	guiRenderer = make_unique<GUIRenderer>(nullptr);
	guiRenderer->initialize();
	//	TODO: guiApplication: xxx
	//	TODO: rendererBackend: xxx
	gui = make_unique<GUI>(nullptr, nullptr, width, height);
	gui->initialize();

	// create camera
	camera = make_unique<Camera>(rendererBackend);
	gizmoCamera = make_unique<Camera>(rendererBackend);
	gizmoCamera->setFrustumMode(Camera::FRUSTUMMODE_ORTHOGRAPHIC);
	gizmoCamera->setCameraMode(Camera::CAMERAMODE_NONE);
	gizmoCamera->setForwardVector(Vector3(0.0f, 0.0f, -1.0f));
	gizmoCamera->setSideVector(Vector3(1.0f, 0.0f, 0.0f));
	gizmoCamera->setUpVector(Vector3(0.0f, 1.0f, 0.0f));
	gizmoCamera->setZNear(1.0f);
	gizmoCamera->setZFar(400.0f);

	// create lights
	for (auto i = 0; i < lights.size(); i++) {
		lights[i] = make_unique<Light>(rendererBackend, i);
		lights[i]->setSourceTexture(TextureReader::read("resources/engine/textures", "sun.png"));
	}

	// create partition
	partition = make_unique<OctTreePartition>();

	// create frame buffer render shader
	frameBufferRenderShader = make_unique<FrameBufferRenderShader>(rendererBackend);
	frameBufferRenderShader->initialize();

	// pbr brdf lut
	if (rendererBackend->isPBRAvailable() == true) {
		// brdf lut render shader
		brdfLUTShader = make_unique<BRDFLUTShader>(rendererBackend);
		brdfLUTShader->initialize();
	}

	// deferred lighting render shader
	if (rendererBackend->isDeferredShadingAvailable() == true) {
		deferredLightingRenderShader = make_unique<DeferredLightingRenderShader>(rendererBackend);
		deferredLightingRenderShader->initialize();
	}

	// create frame buffer render shader
	skyRenderShader = make_unique<SkyRenderShader>(rendererBackend);
	skyRenderShader->initialize();

	// create lighting shader
	lightingShader = make_unique<LightingShader>(rendererBackend);
	lightingShader->initialize();

	// create particles shader
	particlesShader = make_unique<ParticlesShader>(this, rendererBackend);
	particlesShader->initialize();

	// create particles shader
	linesShader = make_unique<LinesShader>(this, rendererBackend);
	linesShader->initialize();

	// create gui shader
	//	TODO: xxx: rendererBackend
	guiShader = make_unique<GUIShader>(nullptr);
	guiShader->initialize();

	// create post processing shader
	postProcessingShader = make_unique<PostProcessingShader>(rendererBackend);
	postProcessingShader->initialize();

	// create post processing
	postProcessing = make_unique<PostProcessing>();

	// create post processing shader
	texture2DRenderShader = make_unique<Texture2DRenderShader>(rendererBackend);
	texture2DRenderShader->initialize();

	// check if texture compression is available
	if (rendererBackend->isTextureCompressionAvailable() == true) {
		Console::printLine("TDME2::BC7 texture compression is available.");
	} else {
		Console::printLine("TDME2::BC7 texture compression is not available.");
	}

	// initialize shadow mapping
	if (shadowMappingEnabled == true) {
		Console::printLine("TDME2::Using shadow mapping");
		shadowMappingShaderPre = make_unique<ShadowMapCreationShader>(rendererBackend);
		shadowMappingShaderPre->initialize();
		shadowMappingShaderRender = make_unique<ShadowMapRenderShader>(rendererBackend);
		shadowMappingShaderRender->initialize();
		shadowMapping = make_unique<ShadowMapping>(this, rendererBackend, entityRenderer.get());
	} else {
		Console::printLine("TDME2::Not using shadow mapping");
	}

	// initialize skinning shader
	if (skinningShaderEnabled == true) {
		Console::printLine("TDME2::Using skinning compute shader");
		skinningShader = make_unique<SkinningShader>(rendererBackend);
		skinningShader->initialize();
	} else {
		Console::printLine("TDME2::Not using skinning compute shader");
	}

	#define CHECK_INITIALIZED(NAME, SHADER) if (SHADER != nullptr && SHADER->isInitialized() == false) Console::printLine(string("TDME: ") + NAME + ": Not initialized")

	CHECK_INITIALIZED("ShadowMapCreationShader", shadowMappingShaderPre);
	CHECK_INITIALIZED("ShadowMappingShader", shadowMappingShaderRender);
	CHECK_INITIALIZED("LightingShader", lightingShader);
	CHECK_INITIALIZED("ParticlesShader", particlesShader);
	CHECK_INITIALIZED("LinesShader", linesShader);
	CHECK_INITIALIZED("GUIShader", guiShader);
	CHECK_INITIALIZED("FrameBufferRenderShader", frameBufferRenderShader);
	if (brdfLUTShader != nullptr) {
		CHECK_INITIALIZED("BRDFLUTShader", brdfLUTShader);
	}
	CHECK_INITIALIZED("DeferredLightingRenderShader", deferredLightingRenderShader);
	CHECK_INITIALIZED("SkyRenderShader", skyRenderShader);
	CHECK_INITIALIZED("PostProcessingShader", postProcessingShader);
	CHECK_INITIALIZED("Texture2DRenderShader", texture2DRenderShader);

	// check if initialized
	// initialized &= objectsFrameBuffer->isInitialized();
	initialized &= shadowMappingShaderPre == nullptr ? true : shadowMappingShaderPre->isInitialized();
	initialized &= shadowMappingShaderRender == nullptr ? true : shadowMappingShaderRender->isInitialized();
	initialized &= lightingShader->isInitialized();
	initialized &= particlesShader->isInitialized();
	initialized &= linesShader->isInitialized();
	initialized &= guiShader->isInitialized();
	initialized &= frameBufferRenderShader->isInitialized();
	if (brdfLUTShader != nullptr) {
		initialized &= brdfLUTShader->isInitialized();
	}
	initialized &= deferredLightingRenderShader != nullptr?deferredLightingRenderShader->isInitialized():true;
	initialized &= skyRenderShader->isInitialized();
	initialized &= postProcessingShader->isInitialized();
	initialized &= texture2DRenderShader->isInitialized();

	// deferred shading
	if (rendererBackend->isDeferredShadingAvailable() == true) {
		Console::printLine("TDME2::Using deferred shading");
	} else {
		Console::printLine("TDME2::Not using deferred shading");
	}

	//
	Console::printLine(string("TDME2::initialized & ready: ") + to_string(initialized));

	// shut down engine if not initialized
	if (initialized == false) {
		Console::printLine("Engine not initialized: Exiting!");
		Application::exit(0);
		return;
	}

	// pbr
	if (rendererBackend->isPBRAvailable() == true) {
		Console::printLine("TDME2::PBR shaders are enabled");
		Console::printLine("TDME2::Generating brdf LUT texture");
		// brdf lut render shader
		brdfLUTShader->generate();
	}

	//
	if (rendererBackend->isSupportingMultithreadedRendering() == true) {
		engineThreadsQueue = make_unique<Queue<Engine::EngineThreadQueueElement>>(0);
		engineThreads.resize(threadCount - 1);
		for (auto i = 0; i < threadCount - 1; i++) {
			engineThreads[i] = make_unique<EngineThread>(
				i + 1,
				engineThreadsQueue.get()
			);
			engineThreads[i]->start();
		}
	}

	// show registered shaders
	dumpShaders();
}

void Engine::reshape(int32_t width, int32_t height)
{
	// apparently windows sends 0x0 dimension if windows gets minimized
	if (width == 0 && height == 0) return;

	// set current engine
	currentEngine = this;

	// update our width and height
	this->width = width;
	this->height = height;

	//
	int _width = scaledWidth != -1?scaledWidth:width;
	int _height = scaledHeight != -1?scaledHeight:height;

	// update frame buffer if we have one
	if (frameBuffer != nullptr) frameBuffer->reshape(_width, _height);

	// update post processing frame buffer if we have one
	if (postProcessingFrameBuffer1 != nullptr) postProcessingFrameBuffer1->reshape(_width, _height);
	if (postProcessingFrameBuffer2 != nullptr) postProcessingFrameBuffer2->reshape(_width, _height);
	if (postProcessingTemporaryFrameBuffer != nullptr) postProcessingTemporaryFrameBuffer->reshape(_width, _height);
	if (postProcessingTemporaryFrameBuffer != nullptr) postProcessingTemporaryFrameBuffer->reshape(_width, _height);
	if (postProcessingTemporaryFrameBuffer != nullptr) postProcessingTemporaryFrameBuffer->reshape(_width, _height);

	// update shadow mapping
	if (shadowMapping != nullptr) shadowMapping->reshape(width, height);

	// unset scaling frame buffer if width and height matches scaling
	if (this == Engine::instance && scaledWidth != -1 && scaledHeight != -1) {
		if (this->width == scaledWidth && this->height == scaledHeight) {
			if (frameBuffer != nullptr) frameBuffer->dispose();
			frameBuffer = nullptr;
		} else {
			if (frameBuffer == nullptr) {
				frameBuffer = make_unique<FrameBuffer>(_width, _height, FrameBuffer::FRAMEBUFFER_DEPTHBUFFER | FrameBuffer::FRAMEBUFFER_COLORBUFFER);
				frameBuffer->initialize();
			} else {
				frameBuffer->reshape(_width, _height);
			}
		}
	}

	// create geometry buffer if available
	if (rendererBackend->isDeferredShadingAvailable() == true) {
		if (geometryBuffer == nullptr) {
			geometryBuffer = make_unique<GeometryBuffer>(_width, _height);
			geometryBuffer->initialize();
		} else {
			geometryBuffer->reshape(_width, _height);
		}
	}

	// update GUI system
	gui->reshape(width, height);
}

void Engine::scale(int32_t width, int32_t height)
{
	if (this != Engine::instance) return;
	scaledWidth = width;
	scaledHeight = height;
	if (frameBuffer != nullptr) frameBuffer->dispose();
	frameBuffer = nullptr;
	if (scaledWidth != this->width || scaledHeight != this->height) {
		frameBuffer = make_unique<FrameBuffer>(scaledWidth, scaledHeight, FrameBuffer::FRAMEBUFFER_DEPTHBUFFER | FrameBuffer::FRAMEBUFFER_COLORBUFFER);
		frameBuffer->initialize();
	}
	reshape(this->width, this->height);
}

void Engine::unscale()
{
	scaledWidth = -1;
	scaledHeight = -1;
	if (frameBuffer != nullptr) frameBuffer->dispose();
	frameBuffer = nullptr;
	reshape(this->width, this->height);
}

void Engine::renderToScreen() {
	if (this == Engine::instance && frameBuffer != nullptr) frameBuffer->renderToScreen(this);
}

void Engine::resetLists(DecomposedEntities& decomposedEntites) {
	// clear lists of visible objects
	decomposedEntites.objects.clear();
	decomposedEntites.objectsForwardShading.clear();
	decomposedEntites.objectsPostPostProcessing.clear();
	decomposedEntites.objectsNoDepthTest.clear();
	decomposedEntites.objectsGizmo.clear();
	decomposedEntites.lodObjects.clear();
	decomposedEntites.opses.clear();
	decomposedEntites.ppses.clear();
	decomposedEntites.psgs.clear();
	decomposedEntites.linesEntities.clear();
	decomposedEntites.decalEntities.clear();
	decomposedEntites.objectRenderGroups.clear();
	decomposedEntites.entityHierarchies.clear();
	decomposedEntites.noFrustumCullingEntities.clear();
	decomposedEntites.environmentMappingEntities.clear();
	decomposedEntites.requirePreRenderEntities.clear();
	decomposedEntites.requireComputeAnimationEntities.clear();
}

void Engine::initRendering()
{
	// update timing
	timing->updateTiming();

	//
	resetLists(visibleDecomposedEntities);
}

void Engine::preRenderFunction(vector<Object*>& objects, int threadIdx) {
	for (auto object: objects) object->preRender(threadIdx);
}

void Engine::computeAnimationsFunction(vector<Object*>& objects, int threadIdx) {
	for (auto object: objects) object->computeAnimations(threadIdx);
}

inline void Engine::decomposeEntityType(Entity* entity, DecomposedEntities& decomposedEntities, bool decomposeAllEntities) {
	switch (entity->getEntityType()) {
		case Entity::ENTITYTYPE_OBJECT:
			{
				auto object = static_cast<Object*>(entity);
				if (object->isDisableDepthTest() == true) {
					decomposedEntities.objectsNoDepthTest.push_back(object);
				} else
				if (object->getRenderPass() == Entity::RENDERPASS_POST_POSTPROCESSING) {
					decomposedEntities.objectsPostPostProcessing.push_back(object);
				} else
				if (object->isRequiringForwardShading() == true &&
					(object->getRenderPass() == Entity::RENDERPASS_TERRAIN || object->getRenderPass() == Entity::RENDERPASS_STANDARD) &&
					rendererBackend->isDeferredShadingAvailable() == true) {
					decomposedEntities.objectsForwardShading.push_back(object);
				} else
				if (object->getRenderPass() == Entity::RENDERPASS_GIZMO) {
					decomposedEntities.objectsGizmo.push_back(object);
				} else {
					decomposedEntities.objects.push_back(object);
				}
			}
			break;
		case Entity::ENTITYTYPE_LODOBJECT:
			{
				auto lodObject = static_cast<LODObject*>(entity);
				if (decomposeAllEntities == true) {
					auto lod1Object = lodObject->getLOD1Object();
					auto lod2Object = lodObject->getLOD2Object();
					auto lod3Object = lodObject->getLOD3Object();
					if (lod1Object != nullptr) decomposeEntityType(lod1Object, decomposedEntities);
					if (lod2Object != nullptr) decomposeEntityType(lod2Object, decomposedEntities);
					if (lod3Object != nullptr) decomposeEntityType(lod3Object, decomposedEntities);
				} else {
					auto object = lodObject->determineLODObject(camera.get());
					if (object != nullptr) decomposeEntityType(object, decomposedEntities, decomposeAllEntities);
				}
			}
			break;
		case Entity::ENTITYTYPE_IMPOSTEROBJECT:
			{
				auto imposterObject = static_cast<ImposterObject*>(entity);
				if (decomposeAllEntities == true) {
					for (auto subEntity: imposterObject->getBillboardObjects()) decomposeEntityType(subEntity, decomposedEntities);
				} else {
					decomposeEntityType(imposterObject->determineBillboardObject(camera.get()), decomposedEntities, decomposeAllEntities);
				}
			}
			break;
		case Entity::ENTITYTYPE_LODOBJECTIMPOSTER:
			{
				auto lodObjectImposter = static_cast<LODObjectImposter*>(entity);
				if (decomposeAllEntities == true) {
					decomposeEntityType(lodObjectImposter->getLOD1Object(), decomposedEntities);
					for (auto subEntity: lodObjectImposter->getLOD2Object()->getBillboardObjects()) decomposeEntityType(subEntity, decomposedEntities);
				} else {
					auto object = lodObjectImposter->determineLODObject(camera.get());
					if (object != nullptr) decomposeEntityType(object, decomposedEntities, decomposeAllEntities);
				}
			}
			break;
		case Entity::ENTITYTYPE_OBJECTPARTICLESYSTEM:
			{
				auto opse = static_cast<ObjectParticleSystem*>(entity);
				if (decomposeAllEntities == true) {
					for (auto object: opse->getObjects()) decomposeEntityType(object, decomposedEntities, decomposeAllEntities);
				} else {
					for (auto object: opse->getEnabledObjects()) decomposeEntityType(object, decomposedEntities, decomposeAllEntities);
				}
				decomposedEntities.opses.push_back(opse);
			}
			break;
		case Entity::ENTITYTYPE_POINTSPARTICLESYSTEM:
			{
				auto ppse = static_cast<PointsParticleSystem*>(entity);
				decomposedEntities.ppses.push_back(ppse);
			}
			break;
		case Entity::ENTITYTYPE_FOGPARTICLESYSTEM:
			{
				auto fpse = static_cast<FogParticleSystem*>(entity);
				decomposedEntities.ppses.push_back(fpse);
			}
			break;
		case Entity::ENTITYTYPE_LINES:
			{
				auto l = static_cast<Lines*>(entity);
				decomposedEntities.linesEntities.push_back(l);
			}
			break;
		case Entity::ENTITYTYPE_DECAL:
			{
				auto d = static_cast<Decal*>(entity);
				decomposedEntities.decalEntities.push_back(d);
			}
			break;
		case Entity::ENTITYTYPE_ENVIRONMENTMAPPING:
			{
				auto eme = static_cast<EnvironmentMapping*>(entity);
				decomposedEntities.environmentMappingEntities.push_back(eme);
			}
			break;
		case Entity::ENTITYTYPE_OBJECTRENDERGROUP:
			{
				auto org = static_cast<ObjectRenderGroup*>(entity);
				decomposedEntities.objectRenderGroups.push_back(org);
				auto subEntity = org->getEntity();
				if (subEntity != nullptr) decomposeEntityType(subEntity, decomposedEntities, decomposeAllEntities);
			}
			break;
		case Entity::ENTITYTYPE_PARTICLESYSTEMGROUP:
			{
				auto psg = static_cast<ParticleSystemGroup*>(entity);
				decomposedEntities.psgs.push_back(psg); \
				for (auto ps: psg->getParticleSystems()) decomposeEntityType(ps, decomposedEntities, decomposeAllEntities);
			}
			break;
		case Entity::ENTITYTYPE_ENTITYHIERARCHY:
			{
				auto eh = static_cast<EntityHierarchy*>(entity);
				decomposedEntities.entityHierarchies.push_back(eh);
				for (auto entityEh: eh->getEntities()) {
					if (entityEh->isEnabled() == false && decomposeAllEntities == false) continue;
					decomposeEntityType(entityEh, decomposedEntities, decomposeAllEntities);
				}
			}
			break;
		default:
			break;
	}
}

inline void Engine::decomposeEntityTypes(const vector<Entity*>& entities, DecomposedEntities& decomposedEntities, bool decomposeAllEntities) {
	for (auto entity: entities) {
		decomposeEntityType(entity, decomposedEntities, decomposeAllEntities);
	}
}

void Engine::preRender(Camera* camera, DecomposedEntities& decomposedEntities, bool autoEmit, bool computeAnimations)
{
	// do particle systems auto emit
	if (autoEmit == true) {
		for (auto entity: autoEmitParticleSystemEntities) {
			auto pse = static_cast<ParticleSystem*>(entity);

			// skip on disabled entities
			if (pse->isEnabled() == false) continue;

			// do auto emit
			pse->emitParticles();
			pse->updateParticles();
		}
	}

	// determine entity types and store them
	decomposeEntityTypes(
		partition->getVisibleEntities(camera->getFrustum()),
		decomposedEntities
	);

	// pre render
	for (auto entity: requirePreRenderEntities) {
		// skip on disabled entities
		auto parentEntity = entity->getParentEntity();
		if ((parentEntity != nullptr && partition->isVisibleEntity(parentEntity) == false) ||
			(parentEntity == nullptr && partition->isVisibleEntity(entity) == false)) continue;
		//
		decomposedEntities.requirePreRenderEntities.push_back(static_cast<Object*>(entity));
	}

	// compute transform
	if (computeAnimations == true) {
		for (auto entity: requireComputeAnimationEntities) {
			// skip on disabled entities
			auto parentEntity = entity->getParentEntity();
			if ((parentEntity != nullptr && partition->isVisibleEntity(parentEntity) == false) ||
				(parentEntity == nullptr && partition->isVisibleEntity(entity) == false)) continue;
			//
			decomposedEntities.requireComputeAnimationEntities.push_back(static_cast<Object*>(entity));
		}
	}

	// collect entities that do not have frustum culling enabled
	for (auto entity: noFrustumCullingEntities) {
		// skip on disabled entities
		if (entity->isEnabled() == false) continue;

		//
		decomposedEntities.noFrustumCullingEntities.push_back(entity);
	}

	// determine additional entity types for objects without frustum culling
	decomposeEntityTypes(
		decomposedEntities.noFrustumCullingEntities,
		decomposedEntities
	);

	//
	if (skinningShaderEnabled == true) skinningShader->useProgram();
	if (rendererBackend->isSupportingMultithreadedRendering() == false) {
		//
		preRenderFunction(decomposedEntities.requirePreRenderEntities, 0);
		computeAnimationsFunction(decomposedEntities.requireComputeAnimationEntities, 0);
	} else {
		auto elementsIssued = 0;
		auto queueElement = engineThreadQueueElementPool.allocate();
		queueElement->type = Engine::EngineThreadQueueElement::TYPE_PRERENDER;
		queueElement->engine = this;
		queueElement->animations.computeAnimations = computeAnimations;
		for (auto i = 0; i < decomposedEntities.requirePreRenderEntities.size(); i++) {
			queueElement->objects.push_back(decomposedEntities.requirePreRenderEntities[i]);
			if (queueElement->objects.size() == Engine::ENGINETHREADSQUEUE_PRERENDER_DISPATCH_COUNT) {
				auto queueElementToSubmit = queueElement;
				queueElement = engineThreadQueueElementPool.allocate();
				queueElement->type = Engine::EngineThreadQueueElement::TYPE_PRERENDER;
				queueElement->engine = this;
				queueElement->animations.computeAnimations = computeAnimations;
				elementsIssued++;
				engineThreadsQueue->addElement(queueElementToSubmit, false);
			}
		}
		if (queueElement->objects.empty() == false) {
			elementsIssued++;
			engineThreadsQueue->addElement(queueElement, false);
			queueElement = engineThreadQueueElementPool.allocate();
		}
		queueElement->type = Engine::EngineThreadQueueElement::TYPE_ANIMATIONS;
		queueElement->engine = this;
		queueElement->animations.computeAnimations = computeAnimations;
		for (auto i = 0; i < decomposedEntities.requireComputeAnimationEntities.size(); i++) {
			queueElement->objects.push_back(decomposedEntities.requireComputeAnimationEntities[i]);
			if (queueElement->objects.size() == Engine::ENGINETHREADSQUEUE_COMPUTE_DISPATCH_COUNT) {
				auto queueElementToSubmit = queueElement;
				queueElement = engineThreadQueueElementPool.allocate();
				queueElement->type = Engine::EngineThreadQueueElement::TYPE_ANIMATIONS;
				queueElement->engine = this;
				queueElement->animations.computeAnimations = computeAnimations;
				elementsIssued++;
				engineThreadsQueue->addElement(queueElementToSubmit, false);
			}
		}
		if (queueElement->objects.empty() == false) {
			elementsIssued++;
			engineThreadsQueue->addElement(queueElement, false);
			queueElement = nullptr;
		}

		// wait until all elements have been processed
		while (true == true) {
			auto elementsProcessed = 0;
			for (const auto& engineThread: Engine::engineThreads) elementsProcessed+= engineThread->getProcessedElements();
			if (elementsProcessed == elementsIssued) {
				for (const auto& engineThread: Engine::engineThreads) engineThread->resetProcessedElements();
				break;
			}
		}
		// reset pool
		engineThreadQueueElementPool.reset();
	}

	//
	if (skinningShaderEnabled == true) {
		skinningShader->unUseProgram();
	}
}

void Engine::display()
{
	// set current engine
	currentEngine = this;

	// execute enqueued actions
	if (actions.empty() == false) {
		vector<unique_ptr<Action>> currentActions;
		for (auto& action: actions) {
			currentActions.push_back(move(action));
		}
		actions.clear();
		for (const auto& action: currentActions) {
			action->performAction();
		}
	}

	// finish last frame
	if (this == Engine::instance) Engine::getRendererBackend()->finishFrame();

	// init frame
	if (this == Engine::instance) Engine::getRendererBackend()->initializeFrame();

	//
	initRendering();

	// default context
	auto _width = scaledWidth != -1?scaledWidth:width;
	auto _height = scaledHeight != -1?scaledHeight:height;

	// camera
	camera->update(rendererBackend->CONTEXTINDEX_DEFAULT, _width, _height);
	// frustum
	camera->getFrustum()->update();

	// do pre rendering steps
	preRender(camera.get(), visibleDecomposedEntities, true, true);

	// render environment maps
	for (auto environmentMappingEntity: visibleDecomposedEntities.environmentMappingEntities) environmentMappingEntity->render();

	// camera
	camera->update(rendererBackend->CONTEXTINDEX_DEFAULT, _width, _height);

	// create shadow maps
	if (shadowMapping != nullptr) shadowMapping->createShadowMaps();

	// do post processing programs effect passes
	array<bool, EFFECTPASS_COUNT - 1> effectPassFrameBuffersInUse;
	effectPassFrameBuffersInUse.fill(false);
	effectPassSkip.fill(false);
	for (auto programId: postProcessingPrograms) {
		auto program = postProcessing->getPostProcessingProgram(programId);
		if (program == nullptr) continue;
		for (const auto& effectPass: program->getEffectPasses()) {
			auto effectPassIdx = effectPass.effectPassIdx;
			auto frameBufferIdx = effectPass.effectPassIdx - 1;
			auto frameBufferWidth = _width / effectPass.frameBufferWidthDivideFactor;
			auto frameBufferHeight = _height / effectPass.frameBufferHeightDivideFactor;
			if (effectPassFrameBuffers[frameBufferIdx] == nullptr) {
				effectPassFrameBuffers[frameBufferIdx] = make_unique<FrameBuffer>(frameBufferWidth, frameBufferHeight, FrameBuffer::FRAMEBUFFER_COLORBUFFER); // TODO: types of buffers
				effectPassFrameBuffers[frameBufferIdx]->initialize();
			} else
			if (effectPassFrameBuffers[frameBufferIdx]->getWidth() != frameBufferWidth ||
				effectPassFrameBuffers[frameBufferIdx]->getHeight() != frameBufferHeight) {
				effectPassFrameBuffers[frameBufferIdx]->reshape(frameBufferWidth, frameBufferHeight);
			}
			effectPassFrameBuffersInUse[frameBufferIdx] = true;
			// enable
			effectPassFrameBuffers[frameBufferIdx]->enableFrameBuffer();
			// clear
			Engine::getRendererBackend()->setClearColor(
				effectPass.clearColor.getRed(),
				effectPass.clearColor.getGreen(),
				effectPass.clearColor.getBlue(),
				effectPass.clearColor.getAlpha()
			);
			rendererBackend->clear(rendererBackend->CLEAR_COLOR_BUFFER_BIT);
			// camera
			camera->update(rendererBackend->CONTEXTINDEX_DEFAULT, frameBufferWidth, frameBufferHeight);
			//
			auto lightSourceVisible = false;
			if (effectPass.renderLightSources == true) {
				if (skyShaderEnabled == true) skyRenderShader->render(this, true);
				lightSourceVisible = renderLightSources(frameBufferWidth, frameBufferHeight);
				if (skyShaderEnabled == true) lightSourceVisible = true;
			}
			if (effectPass.skipOnLightSourceNotVisible == true && lightSourceVisible == false) {
				effectPassSkip[frameBufferIdx] = true;
			} else {
				// Do the effect render pass
				render(
					effectPassFrameBuffers[frameBufferIdx].get(),
					nullptr, // TODO: we might want to use a deferred shading here for further effects
					camera.get(),
					visibleDecomposedEntities,
					effectPassIdx,
					Entity::RENDERPASS_ALL,
					effectPass.shaderPrefix,
					false,
					false,
					false,
					false,
					EntityRenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY |
					EntityRenderer::RENDERTYPE_MATERIALS_DIFFUSEMASKEDTRANSPARENCY |
					EntityRenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY,
					false
				);
			}
		}
	}

	// dispose effect pass frame buffers that we do not use anymore
	for (auto i = 0; i < effectPassFrameBuffersInUse.size(); i++) {
		if (effectPassFrameBuffersInUse[i] == false && effectPassFrameBuffers[i] != nullptr) {
			effectPassFrameBuffers[i]->dispose();
			effectPassFrameBuffers[i] = nullptr;
		}
	}

	// create post processing frame buffers if having post processing
	FrameBuffer* renderFrameBuffer = nullptr;
	if (postProcessingPrograms.size() > 0) {
		if (postProcessingFrameBuffer1 == nullptr) {
			postProcessingFrameBuffer1 = make_unique<FrameBuffer>(_width, _height, FrameBuffer::FRAMEBUFFER_DEPTHBUFFER | FrameBuffer::FRAMEBUFFER_COLORBUFFER);
			postProcessingFrameBuffer1->initialize();
		}
		if (postProcessingFrameBuffer2 == nullptr) {
			postProcessingFrameBuffer2 = make_unique<FrameBuffer>(_width, _height, FrameBuffer::FRAMEBUFFER_DEPTHBUFFER | FrameBuffer::FRAMEBUFFER_COLORBUFFER);
			postProcessingFrameBuffer2->initialize();
		}
		postProcessingFrameBuffer1->enableFrameBuffer();
		renderFrameBuffer = postProcessingFrameBuffer1.get();
	} else {
		if (postProcessingFrameBuffer1 != nullptr) {
			postProcessingFrameBuffer1->dispose();
			postProcessingFrameBuffer1 = nullptr;
		}
		if (postProcessingFrameBuffer2 != nullptr) {
			postProcessingFrameBuffer2->dispose();
			postProcessingFrameBuffer2 = nullptr;
		}
		// render objects to target frame buffer or screen
		if (frameBuffer != nullptr) {
			frameBuffer->enableFrameBuffer();
			renderFrameBuffer = frameBuffer.get();
		} else {
			FrameBuffer::disableFrameBuffer();
		}
	}

	// camera
	camera->update(rendererBackend->CONTEXTINDEX_DEFAULT, _width, _height);

	// clear previous frame values
	if (skyShaderEnabled == true) {
		rendererBackend->clear(rendererBackend->CLEAR_DEPTH_BUFFER_BIT);
		skyRenderShader->render(this, false);
	} else {
		Engine::getRendererBackend()->setClearColor(sceneColor.getRed(), sceneColor.getGreen(), sceneColor.getBlue(), sceneColor.getAlpha());
		rendererBackend->clear(rendererBackend->CLEAR_DEPTH_BUFFER_BIT | rendererBackend->CLEAR_COLOR_BUFFER_BIT);
	}

	// do rendering
	render(
		renderFrameBuffer,
		geometryBuffer.get(),
		camera.get(),
		visibleDecomposedEntities,
		EFFECTPASS_NONE,
		Entity::RENDERPASS_ALL,
		string(),
		true,
		true,
		true,
		true,
		EntityRenderer::RENDERTYPE_NORMALS |
			EntityRenderer::RENDERTYPE_TEXTUREARRAYS |
			EntityRenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY |
			EntityRenderer::RENDERTYPE_EFFECTCOLORS |
			EntityRenderer::RENDERTYPE_MATERIALS |
			EntityRenderer::RENDERTYPE_MATERIALS_DIFFUSEMASKEDTRANSPARENCY |
			EntityRenderer::RENDERTYPE_TEXTURES |
			EntityRenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY |
			EntityRenderer::RENDERTYPE_LIGHTS,
		skyShaderEnabled
	);

	// delete post processing termporary buffer if not required anymore
	if (isUsingPostProcessingTemporaryFrameBuffer == false && postProcessingTemporaryFrameBuffer != nullptr) {
		postProcessingTemporaryFrameBuffer->dispose();
		postProcessingTemporaryFrameBuffer = nullptr;
	}

	//
	if (frameBuffer != nullptr) {
		FrameBuffer::disableFrameBuffer();
	}

	// camera
	camera->update(rendererBackend->CONTEXTINDEX_DEFAULT, _width, _height);
}

Vector3 Engine::computeWorldCoordinateByMousePosition(int32_t mouseX, int32_t mouseY, float z, Camera* camera)
{
	auto scaleFactorWidth = static_cast<float>(scaledWidth != -1?scaledWidth:width) / static_cast<float>(width);
	auto scaleFactorHeight = static_cast<float>(scaledHeight != -1?scaledHeight:height) / static_cast<float>(height);
	auto _width = scaledWidth != -1?scaledWidth:width;
	auto _height = scaledHeight != -1?scaledHeight:height;
	// see: http://stackoverflow.com/questions/7692988/opengl-math-projecting-screen-space-to-world-space-coords-solved
	auto worldCoordinate4 = camera->getModelViewProjectionInvertedMatrix().multiply(
		Vector4(
			(2.0f * (mouseX * scaleFactorWidth) / _width) - 1.0f,
			1.0f - (2.0f * (mouseY * scaleFactorHeight) / _height),
			2.0f * z - 1.0f,
			1.0f
		)
	);
	worldCoordinate4.scale(1.0f / worldCoordinate4.getW());
	return Vector3(
		worldCoordinate4.getX(),
		worldCoordinate4.getY(),
		worldCoordinate4.getZ()
	);
}

Vector3 Engine::computeWorldCoordinateByMousePosition(int32_t mouseX, int32_t mouseY)
{
	// use framebuffer if we have one
	if (frameBuffer != nullptr)
		frameBuffer->enableFrameBuffer();

	//
	auto scaleFactorWidth = static_cast<float>(scaledWidth != -1?scaledWidth:width) / static_cast<float>(width);
	auto scaleFactorHeight = static_cast<float>(scaledHeight != -1?scaledHeight:height) / static_cast<float>(height);

	// see: http://stackoverflow.com/questions/7692988/opengl-math-projecting-screen-space-to-world-space-coords-solved
	auto z = rendererBackend->readPixelDepth(mouseX * scaleFactorWidth, (height  - mouseY) * scaleFactorHeight);

	// unuse framebuffer if we have one
	if (frameBuffer != nullptr)
		FrameBuffer::disableFrameBuffer();

	//
	return computeWorldCoordinateByMousePosition(mouseX, mouseY, z, camera.get());
}

Entity* Engine::getEntityByMousePosition(
	DecomposedEntities& decomposedEntities,
	bool forcePicking,
	int32_t mouseX,
	int32_t mouseY,
	EntityPickingFilter* filter,
	Node** objectNode,
	ParticleSystem** particleSystemEntity
) {
	//
	Vector3 boundingBoxLineContactMin;
	Vector3 boundingBoxLineContactMax;
	Vector3 lineTriangleContact;

	// selected entity
	auto selectedEntityDistance = Float::MAX_VALUE;
	Entity* selectedEntity = nullptr;
	Node* selectedObjectNode = nullptr;
	ParticleSystem* selectedParticleSystem = nullptr;

	// iterate gizmo objects that have no depth test, check if ray with given mouse position from near plane to far plane collides with each object's triangles
	if (decomposedEntities.objectsGizmo.empty() == false) {
		//
		auto nearPlaneWorldCoordinate = computeGizmoCoordinateByMousePosition(mouseX, mouseY, 0.0f);
		auto farPlaneWorldCoordinate = computeGizmoCoordinateByMousePosition(mouseX, mouseY, 1.0f);

		//
		for (auto entity: decomposedEntities.objectsGizmo) {
			// skip if not pickable or ignored by filter
			if (forcePicking == false && entity->isPickable() == false) continue;
			if (filter != nullptr && filter->filterEntity(entity) == false) continue;
			// do the collision test
			for (auto it = entity->getTransformedFacesIterator()->iterator(); it->hasNext();) {
				const auto& vertices = it->next();
				if (LineSegment::doesLineSegmentCollideWithTriangle(vertices[0], vertices[1], vertices[2], nearPlaneWorldCoordinate, farPlaneWorldCoordinate, lineTriangleContact) == true) {
					auto entityDistance = lineTriangleContact.sub(nearPlaneWorldCoordinate).computeLengthSquared();
					// check if match or better match
					if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
						selectedEntity = entity;
						selectedEntityDistance = entityDistance;
						selectedObjectNode = it->getNode();
						selectedParticleSystem = nullptr;
					}
				}
			}
		}

		// they have first priority right now
		if (selectedEntity != nullptr) {
			if (objectNode != nullptr) *objectNode = selectedObjectNode;
			for (auto _entity = selectedEntity; _entity != nullptr; _entity = _entity->getParentEntity()) {
				if (_entity->getParentEntity() == nullptr) {
					return _entity;
				}
			}
			return nullptr;
		}
	}

	// get world position of mouse position at near and far plane
	auto nearPlaneWorldCoordinate = computeWorldCoordinateByMousePosition(mouseX, mouseY, 0.0f);
	auto farPlaneWorldCoordinate = computeWorldCoordinateByMousePosition(mouseX, mouseY, 1.0f);

	// iterate visible entity decals, check if ray with given mouse position from near plane to far plane collides with bounding volume
	for (auto entity: decomposedEntities.decalEntities) {
		// skip if not pickable or ignored by filter
		if (forcePicking == false && entity->isPickable() == false) continue;
		if (filter != nullptr && filter->filterEntity(entity) == false) continue;
		// do the collision test
		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getWorldBoundingBox(), nearPlaneWorldCoordinate, farPlaneWorldCoordinate, boundingBoxLineContactMin, boundingBoxLineContactMax) == true) {
			auto entityDistance = lineTriangleContact.set(entity->getWorldBoundingBox()->getCenter()).sub(nearPlaneWorldCoordinate).computeLengthSquared();
			// check if match or better match
			if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
				selectedEntity = entity;
				selectedEntityDistance = entityDistance;
				selectedObjectNode = nullptr;
				selectedParticleSystem = nullptr;
			}
		}
	}

	// decals have first priority right now
	if (selectedEntity != nullptr) {
		if (objectNode != nullptr) *objectNode = selectedObjectNode;
		for (auto _entity = selectedEntity; _entity != nullptr; _entity = _entity->getParentEntity()) {
			if (_entity->getParentEntity() == nullptr) return _entity;
		}
		return nullptr;
	}

	// iterate visible objects that have no depth test, check if ray with given mouse position from near plane to far plane collides with each object's triangles
	for (auto entity: decomposedEntities.objectsNoDepthTest) {
		// skip if not pickable or ignored by filter
		if (forcePicking == false && entity->isPickable() == false) continue;
		if (filter != nullptr && filter->filterEntity(entity) == false) continue;
		// do the collision test
		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getWorldBoundingBox(), nearPlaneWorldCoordinate, farPlaneWorldCoordinate, boundingBoxLineContactMin, boundingBoxLineContactMax) == true) {
			for (auto it = entity->getTransformedFacesIterator()->iterator(); it->hasNext();) {
				const auto& vertices = it->next();
				if (LineSegment::doesLineSegmentCollideWithTriangle(vertices[0], vertices[1], vertices[2], nearPlaneWorldCoordinate, farPlaneWorldCoordinate, lineTriangleContact) == true) {
					auto entityDistance = lineTriangleContact.sub(nearPlaneWorldCoordinate).computeLengthSquared();
					// check if match or better match
					if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
						selectedEntity = entity;
						selectedEntityDistance = entityDistance;
						selectedObjectNode = it->getNode();
						selectedParticleSystem = nullptr;
					}
				}
			}
		}
	}

	// objects without depth test have second priority right now
	if (selectedEntity != nullptr) {
		if (objectNode != nullptr) *objectNode = selectedObjectNode;
		for (auto _entity = selectedEntity; _entity != nullptr; _entity = _entity->getParentEntity()) {
			if (_entity->getParentEntity() == nullptr) return _entity;
		}
		return nullptr;
	}

	// iterate visible object partition systems, check if ray with given mouse position from near plane to far plane collides with bounding volume
	for (auto entity: decomposedEntities.opses) {
		// skip if not pickable or ignored by filter
		if (forcePicking == false && entity->isPickable() == false) continue;
		if (filter != nullptr && filter->filterEntity(entity) == false) continue;
		// do the collision test
		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getWorldBoundingBox(), nearPlaneWorldCoordinate, farPlaneWorldCoordinate, boundingBoxLineContactMin, boundingBoxLineContactMax) == true) {
			auto entityDistance = lineTriangleContact.set(entity->getWorldBoundingBox()->getCenter()).sub(nearPlaneWorldCoordinate).computeLengthSquared();
			// check if match or better match
			if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
				selectedEntity = entity;
				selectedEntityDistance = entityDistance;
				selectedObjectNode = nullptr;
				selectedParticleSystem = nullptr;
			}
		}
	}

	// iterate visible point partition systems, check if ray with given mouse position from near plane to far plane collides with bounding volume
	for (auto entity: decomposedEntities.ppses) {
		// skip if not pickable or ignored by filter
		if (forcePicking == false && entity->isPickable() == false) continue;
		if (filter != nullptr && filter->filterEntity(entity) == false) continue;
		// do the collision test
		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getWorldBoundingBox(), nearPlaneWorldCoordinate, farPlaneWorldCoordinate, boundingBoxLineContactMin, boundingBoxLineContactMax) == true) {
			auto entityDistance = lineTriangleContact.set(entity->getWorldBoundingBox()->getCenter()).sub(nearPlaneWorldCoordinate).computeLengthSquared();
			// check if match or better match
			if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
				selectedEntity = entity;
				selectedEntityDistance = entityDistance;
				selectedObjectNode = nullptr;
				selectedParticleSystem = nullptr;
			}
		}
	}

	// iterate visible particle system nodes, check if ray with given mouse position from near plane to far plane collides with bounding volume
	for (auto entity: decomposedEntities.psgs) {
		// skip if not pickable or ignored by filter
		if (forcePicking == false && entity->isPickable() == false) continue;
		if (filter != nullptr && filter->filterEntity(entity) == false) continue;
		// do the collision test
		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getWorldBoundingBox(), nearPlaneWorldCoordinate, farPlaneWorldCoordinate, boundingBoxLineContactMin, boundingBoxLineContactMax) == true) {
			auto entityDistance = lineTriangleContact.set(entity->getWorldBoundingBox()->getCenter()).sub(nearPlaneWorldCoordinate).computeLengthSquared();
			// check if match or better match
			if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
				selectedEntity = entity;
				selectedEntityDistance = entityDistance;
				selectedObjectNode = nullptr;
				selectedParticleSystem = nullptr;
				auto selectedSubEntityDistance = Float::MAX_VALUE;
				// iterate sub partition systems, check if ray with given mouse position from near plane to far plane collides with bounding volume
				for (auto subEntity: entity->getParticleSystems()) {
					if (LineSegment::doesBoundingBoxCollideWithLineSegment(subEntity->getWorldBoundingBox(), nearPlaneWorldCoordinate, farPlaneWorldCoordinate, boundingBoxLineContactMin, boundingBoxLineContactMax) == true) {
						auto subEntityDistance = lineTriangleContact.set(subEntity->getWorldBoundingBox()->getCenter()).sub(nearPlaneWorldCoordinate).computeLengthSquared();
						// check if match or better match
						if (selectedParticleSystem == nullptr || subEntityDistance < selectedSubEntityDistance) {
							selectedSubEntityDistance = subEntityDistance;
							selectedParticleSystem = subEntity;
						}
					}
				}
			}
		}
	}

	// iterate visible line entities, check if ray with given mouse position from near plane to far plane collides with each object's triangles
	for (auto entity: decomposedEntities.linesEntities) {
		// skip if not pickable or ignored by filter
		if (forcePicking == false && entity->isPickable() == false) continue;
		if (filter != nullptr && filter->filterEntity(entity) == false) continue;
		// do the collision test
		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getWorldBoundingBox(), nearPlaneWorldCoordinate, farPlaneWorldCoordinate, boundingBoxLineContactMin, boundingBoxLineContactMax) == true) {
			auto entityDistance = lineTriangleContact.set(entity->getWorldBoundingBox()->getCenter()).sub(nearPlaneWorldCoordinate).computeLengthSquared();
			// check if match or better match
			if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
				selectedEntity = entity;
				selectedEntityDistance = entityDistance;
				selectedObjectNode = nullptr;
				selectedParticleSystem = nullptr;
			}
		}
	}

	// iterate visible objects, check if ray with given mouse position from near plane to far plane collides with each object's triangles
	array<vector<Object*>*, 3> objectsArray { &decomposedEntities.objects, &decomposedEntities.objectsForwardShading, &decomposedEntities.objectsPostPostProcessing,  };
	for (auto& objects: objectsArray) {
		for (auto entity: *objects) {
			// skip if not pickable or ignored by filter
			if (forcePicking == false && entity->isPickable() == false) continue;
			if (filter != nullptr && filter->filterEntity(entity) == false) continue;
			// do the collision test
			if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getWorldBoundingBox(), nearPlaneWorldCoordinate, farPlaneWorldCoordinate, boundingBoxLineContactMin, boundingBoxLineContactMax) == true) {
				for (auto it = entity->getTransformedFacesIterator()->iterator(); it->hasNext();) {
					const auto& vertices = it->next();
					if (LineSegment::doesLineSegmentCollideWithTriangle(vertices[0], vertices[1], vertices[2], nearPlaneWorldCoordinate, farPlaneWorldCoordinate, lineTriangleContact) == true) {
						auto entityDistance = lineTriangleContact.sub(nearPlaneWorldCoordinate).computeLengthSquared();
						// check if match or better match
						if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
							selectedEntity = entity;
							selectedEntityDistance = entityDistance;
							selectedObjectNode = it->getNode();
							selectedParticleSystem = nullptr;
						}
					}
				}
			}
		}
	}

	// iterate visible LOD objects, check if ray with given mouse position from near plane to far plane collides with each object's triangles
	for (auto entity: decomposedEntities.lodObjects) {
		// skip if not pickable or ignored by filter
		if (forcePicking == false && entity->isPickable() == false) continue;
		if (filter != nullptr && filter->filterEntity(entity) == false) continue;
		// do the collision test
		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getWorldBoundingBox(), nearPlaneWorldCoordinate, farPlaneWorldCoordinate, boundingBoxLineContactMin, boundingBoxLineContactMax) == true) {
			auto object = entity->getLODObject();
			if (object != nullptr) {
				for (auto it = object->getTransformedFacesIterator()->iterator(); it->hasNext();) {
					const auto& vertices = it->next();
					if (LineSegment::doesLineSegmentCollideWithTriangle(vertices[0], vertices[1], vertices[2], nearPlaneWorldCoordinate, farPlaneWorldCoordinate, lineTriangleContact) == true) {
						auto entityDistance = lineTriangleContact.sub(nearPlaneWorldCoordinate).computeLengthSquared();
						// check if match or better match
						if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
							selectedEntity = entity;
							selectedEntityDistance = entityDistance;
						}
					}
					selectedObjectNode = it->getNode();
					selectedParticleSystem = nullptr;
				}
			}
		}
	}

	// iterate visible entity hierarchies, check if ray with given mouse position from near plane to far plane collides with bounding volume
	for (auto entity: decomposedEntities.entityHierarchies) {
		// skip if not pickable or ignored by filter
		if (forcePicking == false && entity->isPickable() == false) continue;
		if (filter != nullptr && filter->filterEntity(entity) == false) continue;
		// do the collision test
		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getWorldBoundingBox(), nearPlaneWorldCoordinate, farPlaneWorldCoordinate, boundingBoxLineContactMin, boundingBoxLineContactMax) == true) {
			DecomposedEntities decomposedEntitiesEH;
			Node* objectNodeEH = nullptr;
			ParticleSystem* particleSystemEntityEH = nullptr;
			decomposeEntityTypes(
				entity->getEntities(),
				decomposedEntitiesEH
			);
			auto subEntity = getEntityByMousePosition(
				decomposedEntitiesEH,
				true,
				mouseX,
				mouseY,
				filter,
				&objectNodeEH,
				&particleSystemEntityEH
			);
			if (subEntity != nullptr) {
				auto entityDistance = lineTriangleContact.set(subEntity->getWorldBoundingBox()->getCenter()).sub(nearPlaneWorldCoordinate).computeLengthSquared();
				// check if match or better match
				if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
					selectedEntity = entity;
					selectedEntityDistance = entityDistance;
					selectedObjectNode = objectNodeEH;
					selectedParticleSystem = particleSystemEntityEH;
				}
			}
		}
	}

	// store node
	if (objectNode != nullptr) *objectNode = selectedObjectNode;

	// store particle system entity
	if (particleSystemEntity != nullptr) {
		*particleSystemEntity = selectedParticleSystem;
	}

	// return parent entity if entity is part of a hierarchy
	if (selectedEntity != nullptr) {
		for (auto _entity = selectedEntity; _entity != nullptr; _entity = _entity->getParentEntity()) {
			if (_entity->getParentEntity() == nullptr) return _entity;
		}
		return nullptr;
	} else {
		return nullptr;
	}
}

Entity* Engine::getEntityByMousePosition(int32_t mouseX, int32_t mouseY, Vector3& contactPoint, EntityPickingFilter* filter, Node** objectNode, ParticleSystem** particleSystemEntity) {
	// get world position of mouse position at near and far plane
	auto startPoint = computeWorldCoordinateByMousePosition(mouseX, mouseY, 0.0f);
	auto endPoint = computeWorldCoordinateByMousePosition(mouseX, mouseY, 1.0f);

	//
	return doRayCasting(startPoint, endPoint, contactPoint, filter);// TODO: object node, particle system entity
}

Entity* Engine::doRayCasting(
	DecomposedEntities& decomposedEntities,
	bool forcePicking,
	const Vector3& startPoint,
	const Vector3& endPoint,
	Vector3& contactPoint,
	EntityPickingFilter* filter) {
	Vector3 boundingBoxLineContactMin;
	Vector3 boundingBoxLineContactMax;
	Vector3 lineTriangleContact;

	// selected entity
	auto selectedEntityDistance = Float::MAX_VALUE;
	Entity* selectedEntity = nullptr;

	// iterate visible objects with no depth writing, check if ray with given mouse position from near plane to far plane collides with each object's triangles
	for (auto entity: decomposedEntities.objectsNoDepthTest) {
		// skip if not pickable or ignored by filter
		if (forcePicking == false && entity->isPickable() == false) continue;
		if (filter != nullptr && filter->filterEntity(entity) == false) continue;
		// do the collision test
		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getWorldBoundingBox(), startPoint, endPoint, boundingBoxLineContactMin, boundingBoxLineContactMax) == true) {
			for (auto it = entity->getTransformedFacesIterator()->iterator(); it->hasNext();) {
				const auto& vertices = it->next();
				if (LineSegment::doesLineSegmentCollideWithTriangle(vertices[0], vertices[1], vertices[2], startPoint, endPoint, lineTriangleContact) == true) {
					auto entityDistance = lineTriangleContact.clone().sub(startPoint).computeLengthSquared();
					// check if match or better match
					if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
						selectedEntity = entity;
						selectedEntityDistance = entityDistance;
						contactPoint = lineTriangleContact;
					}
				}
			}
		}
	}
	// they have first priority right now
	if (selectedEntity != nullptr) {
		return selectedEntity;
	}

	// iterate visible objects, check if ray with given mouse position from near plane to far plane collides with each object's triangles
	array<vector<Object*>*, 3> objectsArray { &decomposedEntities.objects, &decomposedEntities.objectsForwardShading, &decomposedEntities.objectsPostPostProcessing,  };
	for (auto& objects: objectsArray) {
		for (auto entity: *objects) {
			// skip if not pickable or ignored by filter
			if (forcePicking == false && entity->isPickable() == false) continue;
			if (filter != nullptr && filter->filterEntity(entity) == false) continue;
			// do the collision test
			if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getWorldBoundingBox(), startPoint, endPoint, boundingBoxLineContactMin, boundingBoxLineContactMax) == true) {
				for (auto it = entity->getTransformedFacesIterator()->iterator(); it->hasNext();) {
					const auto& vertices = it->next();
					if (LineSegment::doesLineSegmentCollideWithTriangle(vertices[0], vertices[1], vertices[2], startPoint, endPoint, lineTriangleContact) == true) {
						auto entityDistance = lineTriangleContact.clone().sub(startPoint).computeLengthSquared();
						// check if match or better match
						if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
							selectedEntity = entity;
							selectedEntityDistance = entityDistance;
							contactPoint = lineTriangleContact;
						}
					}
				}
			}
		}
	}

	// iterate visible LOD objects, check if ray with given mouse position from near plane to far plane collides with each object's triangles
	for (auto entity: decomposedEntities.lodObjects) {
		// skip if not pickable or ignored by filter
		if (forcePicking == false && entity->isPickable() == false) continue;
		if (filter != nullptr && filter->filterEntity(entity) == false) continue;
		// do the collision test
		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getWorldBoundingBox(), startPoint, endPoint, boundingBoxLineContactMin, boundingBoxLineContactMax) == true) {
			auto object = entity->getLODObject();
			if (object != nullptr) {
				for (auto it = object->getTransformedFacesIterator()->iterator(); it->hasNext();) {
					const auto& vertices = it->next();
					if (LineSegment::doesLineSegmentCollideWithTriangle(vertices[0], vertices[1], vertices[2], startPoint, endPoint, lineTriangleContact) == true) {
						auto entityDistance = lineTriangleContact.sub(startPoint).computeLengthSquared();
						// check if match or better match
						if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
							selectedEntity = entity;
							selectedEntityDistance = entityDistance;
							contactPoint = lineTriangleContact;
						}
					}
				}
			}
		}
	}

	// iterate visible entity hierarchies, check if ray with given mouse position from near plane to far plane collides with bounding volume
	for (auto entity: decomposedEntities.entityHierarchies) {
		// skip if not pickable or ignored by filter
		if (forcePicking == false && entity->isPickable() == false) continue;
		if (filter != nullptr && filter->filterEntity(entity) == false) continue;
		// do the collision test
		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getWorldBoundingBox(), startPoint, endPoint, boundingBoxLineContactMin, boundingBoxLineContactMax) == true) {
			DecomposedEntities decomposedEntitiesEH;
			decomposeEntityTypes(
				entity->getEntities(),
				decomposedEntitiesEH
			);
			Vector3 contactPointEH;
			auto entity = doRayCasting(
				decomposedEntitiesEH,
				true,
				startPoint,
				endPoint,
				contactPointEH,
				filter
			);
			if (entity != nullptr) {
				auto entityDistance = lineTriangleContact.sub(startPoint).computeLengthSquared();
				// check if match or better match
				if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
					selectedEntity = entity;
					selectedEntityDistance = entityDistance;
					contactPoint = contactPointEH;
				}
			}
		}
	}

	//
	return selectedEntity;
}

bool Engine::computeScreenCoordinateByWorldCoordinate(const Vector3& worldCoordinate, Vector2& screenCoordinate, int width, int height)
{
	auto _width = width != -1?width:(scaledWidth != -1?scaledWidth:this->width);
	auto _height = height != -1?height:(scaledHeight != -1?scaledHeight:this->height);
	// convert to normalized device coordinates
	auto screenCoordinate4 = camera->getModelViewProjectionMatrix().multiply(Vector4(worldCoordinate, 1.0f));
	screenCoordinate4.scale(1.0f / screenCoordinate4.getW());
	// convert to screen coordinate
	screenCoordinate.setX((screenCoordinate4[0] + 1.0f) * _width / 2.0f);
	screenCoordinate.setY(_height - ((screenCoordinate4[1] + 1.0f) * _height / 2.0f));
	return camera->getCameraMatrix().multiply(worldCoordinate).getZ() <= 0.0f;
}

void Engine::dispose()
{
	// finish last frame
	if (this == Engine::instance) Engine::getRendererBackend()->finishFrame();

	// remove entities
	vector<string> entitiesToRemove;
	for (const auto& [entityId, entity]: entitiesById) {
		entitiesToRemove.push_back(entityId);
	}
	for (const auto& entityKey: entitiesToRemove) {
		removeEntity(entityKey);
	}

	// dispose shadow mapping
	if (shadowMapping != nullptr) shadowMapping->dispose();

	// dispose frame buffers
	if (geometryBuffer != nullptr) geometryBuffer->dispose();
	if (frameBuffer != nullptr) frameBuffer->dispose();
	if (gizmoFrameBuffer != nullptr) gizmoFrameBuffer->dispose();
	if (postProcessingFrameBuffer1 != nullptr) postProcessingFrameBuffer1->dispose();
	if (postProcessingFrameBuffer2 != nullptr) postProcessingFrameBuffer2->dispose();
	if (postProcessingTemporaryFrameBuffer != nullptr) postProcessingTemporaryFrameBuffer->dispose();
	for (const auto& effectPassFrameBuffer: effectPassFrameBuffers) if (effectPassFrameBuffer != nullptr) effectPassFrameBuffer->dispose();

	// dispose lights
	for (const auto& light: lights) light->dispose();

	// dispose GUI
	gui->dispose();
	if (this == Engine::instance) {
		guiRenderer->dispose();
		GUIParser::dispose();
	}

	// dispose entity renderer
	entityRenderer->dispose();

	// dispose object buffer if main engine
	if (this == Engine::instance) {
		if (rendererBackend->isSupportingMultithreadedRendering() == true) {
			engineThreadsQueue->stop();
			for (const auto& engineThread: engineThreads) engineThread->stop();
			for (const auto& engineThread: engineThreads) engineThread->join();
		}
		if (Engine::deferredLightingRenderShader != nullptr) Engine::deferredLightingRenderShader->dispose();
		frameBufferRenderShader->dispose();
		skyRenderShader->dispose();
		texture2DRenderShader->dispose();
		lightingShader->dispose();
		postProcessingShader->dispose();
		ObjectBuffer::dispose();
	}

	// set current engine
	if (currentEngine == this) currentEngine = nullptr;
}

void Engine::initGUIMode()
{
	// use framebuffer if we have one
	if (frameBuffer != nullptr) {
		frameBuffer->enableFrameBuffer();
	} else {
		frameBuffer->disableFrameBuffer();
	}

	rendererBackend->initGUIMode();
}

void Engine::doneGUIMode()
{
	rendererBackend->doneGUIMode();

	// unuse framebuffer if we have one
	if (frameBuffer != nullptr)
		FrameBuffer::disableFrameBuffer();
}

bool Engine::makeScreenshot(const string& pathName, const string& fileName, bool removeAlphaChannel)
{
	// use framebuffer if we have one
	if (frameBuffer != nullptr) frameBuffer->enableFrameBuffer();

	// fetch pixel
	auto pixels = unique_ptr<ByteBuffer>(rendererBackend->readPixels(0, 0, width, height));
	if (pixels == nullptr) {
		Console::printLine("Engine::makeScreenshot(): Failed to read pixels");
		return false;
	}

	// create texture, write and delete
	auto texture =
		unique_ptr<
			Texture,
			decltype([](Texture* texture){ texture->releaseReference(); })
		>(
			new Texture(
				"tdme.engine.makescreenshot",
				Texture::TEXTUREDEPTH_RGBA,
				Texture::TEXTUREFORMAT_RGBA,
				width,
				height,
				width,
				height,
				Texture::TEXTUREFORMAT_RGBA,
				*pixels
			)
		);
	texture->acquireReference();
	PNGTextureWriter::write(texture.get(), pathName, fileName, removeAlphaChannel);

	// unuse framebuffer if we have one
	if (frameBuffer != nullptr) FrameBuffer::disableFrameBuffer();

	//
	return true;
}

bool Engine::makeScreenshot(vector<uint8_t>& pngData)
{
	// use framebuffer if we have one
	if (frameBuffer != nullptr) frameBuffer->enableFrameBuffer();

	// fetch pixel
	auto pixels = unique_ptr<ByteBuffer>(rendererBackend->readPixels(0, 0, width, height));
	if (pixels == nullptr) {
		Console::printLine("Engine::makeScreenshot(): Failed to read pixels");
		return false;
	}

	// create texture, write and delete
	auto texture =
		unique_ptr<
			Texture,
			decltype([](Texture* texture){ texture->releaseReference(); })
		>(
			new Texture(
				"tdme.engine.makescreenshot",
				Texture::TEXTUREDEPTH_RGBA,
				Texture::TEXTUREFORMAT_RGBA,
				width,
				height,
				width,
				height,
				Texture::TEXTUREFORMAT_RGBA,
				*pixels
			)
		);
	texture->acquireReference();
	PNGTextureWriter::write(texture.get(), pngData);

	// unuse framebuffer if we have one
	if (frameBuffer != nullptr) FrameBuffer::disableFrameBuffer();

	//
	return true;
}

void Engine::resetPostProcessingPrograms() {
	postProcessingPrograms.clear();
}

void Engine::addPostProcessingProgram(const string& programId) {
	postProcessingPrograms.erase(remove(postProcessingPrograms.begin(), postProcessingPrograms.end(), programId), postProcessingPrograms.end());
	if (postProcessing->getPostProcessingProgram(programId) != nullptr) postProcessingPrograms.push_back(programId);
}

void Engine::doPostProcessing(PostProcessingProgram::RenderPass renderPass, array<FrameBuffer*, 2> postProcessingFrameBuffers, FrameBuffer* targetFrameBuffer) {
	auto postProcessingFrameBufferIdx = 0;
	for (auto programId: postProcessingPrograms) {
		auto program = postProcessing->getPostProcessingProgram(programId);
		if (program == nullptr) continue;
		if (program->getRenderPass() != renderPass) continue;
		auto effectPassSkipDetected = false;
		for (const auto& effectPass: program->getEffectPasses()) {
			if (effectPassSkip[effectPass.effectPassIdx - 1] == true) effectPassSkipDetected = true;
		}
		if (effectPassSkipDetected == true) continue;
		for (const auto& step: program->getPostProcessingSteps()) {
			auto shaderId = step.shaderId;
			FrameBuffer* blendToSource = nullptr;
			FrameBuffer* source = nullptr;
			FrameBuffer* target = nullptr;
			if (step.blendToSource == PostProcessingProgram::FRAMEBUFFERSOURCE_SCREEN) {
				blendToSource = postProcessingFrameBuffers[postProcessingFrameBufferIdx];
			}
			switch(step.source) {
				case PostProcessingProgram::FRAMEBUFFERSOURCE_NONE:
					break;
				case PostProcessingProgram::FRAMEBUFFERSOURCE_SCREEN:
					source = postProcessingFrameBuffers[postProcessingFrameBufferIdx];
					break;
				default:
					source = effectPassFrameBuffers[step.source - PostProcessingProgram::FRAMEBUFFERSOURCE_EFFECTPASS0].get();
					break;
			}
			switch(step.target) {
				case PostProcessingProgram::FRAMEBUFFERTARGET_SCREEN:
					target = postProcessingFrameBuffers[(postProcessingFrameBufferIdx + 1) % 2];
					break;
				case PostProcessingProgram::FRAMEBUFFERTARGET_TEMPORARY:
					isUsingPostProcessingTemporaryFrameBuffer = true;
					if (postProcessingTemporaryFrameBuffer == nullptr) {
						postProcessingTemporaryFrameBuffer = make_unique<FrameBuffer>(width, height, FrameBuffer::FRAMEBUFFER_COLORBUFFER | FrameBuffer::FRAMEBUFFER_DEPTHBUFFER);
						postProcessingTemporaryFrameBuffer->initialize();
					}
					target = postProcessingTemporaryFrameBuffer.get();
					break;
			}
			FrameBuffer::doPostProcessing(this, target, source, programId, shaderId, step.bindTemporary == true?postProcessingTemporaryFrameBuffer.get():nullptr, blendToSource);
			switch(step.target) {
				case PostProcessingProgram::FRAMEBUFFERTARGET_SCREEN:
					postProcessingFrameBufferIdx = (postProcessingFrameBufferIdx + 1) % 2;
					break;
				case PostProcessingProgram::FRAMEBUFFERTARGET_TEMPORARY:
					break;
			}
		}
	}

	// render back to objects frame buffer
	if (postProcessingFrameBuffers[postProcessingFrameBufferIdx] != targetFrameBuffer) {
		if (targetFrameBuffer != nullptr) {
			targetFrameBuffer->enableFrameBuffer();
		} else {
			FrameBuffer::disableFrameBuffer();
		}
		postProcessingFrameBuffers[postProcessingFrameBufferIdx]->renderToScreen(this);
	}
}

void Engine::render(FrameBuffer* renderFrameBuffer, GeometryBuffer* renderGeometryBuffer, Camera* rendererCamera, DecomposedEntities& visibleDecomposedEntities, int32_t effectPass, int32_t renderPassMask, const string& shaderPrefix, bool applyShadowMapping, bool applyPostProcessing, bool doRenderLightSource, bool doRenderParticleSystems, int32_t renderTypes, bool skyShaderEnabled) {
	//
	Engine::getRendererBackend()->setEffectPass(effectPass);
	Engine::getRendererBackend()->setShaderPrefix(shaderPrefix);

	// use lighting shader
	if (visibleDecomposedEntities.objects.empty() == false || visibleDecomposedEntities.objectsForwardShading.empty() == false) {
		//
		if (lightingShader != nullptr) lightingShader->useProgram(this);

		// render objects
		for (auto i = 0; i < Entity::RENDERPASS_MAX; i++) {
			auto renderPass = static_cast<Entity::RenderPass>(Math::pow(2, i));
			if ((renderPassMask & renderPass) == renderPass) {
				if (renderPass == Entity::RENDERPASS_TERRAIN) {
					if (renderGeometryBuffer != nullptr) {
						if (lightingShader != nullptr) lightingShader->unUseProgram();
						renderGeometryBuffer->enableGeometryBuffer();
						rendererBackend->setClearColor(0.0f, 0.0f, 0.0f, 0.0f);
						rendererBackend->clear(rendererBackend->CLEAR_DEPTH_BUFFER_BIT | rendererBackend->CLEAR_COLOR_BUFFER_BIT);
						Engine::getRendererBackend()->setShaderPrefix("defer_");
						if (lightingShader != nullptr) lightingShader->useProgram(this);
					}
				} else
				if (renderPass == Entity::RENDERPASS_WATER) rendererBackend->enableBlending();
				entityRenderer->render(
					renderPass,
					visibleDecomposedEntities.objects,
					true,
					((renderTypes & EntityRenderer::RENDERTYPE_NORMALS) == EntityRenderer::RENDERTYPE_NORMALS?EntityRenderer::RENDERTYPE_NORMALS:0) |
					((renderTypes & EntityRenderer::RENDERTYPE_TEXTUREARRAYS) == EntityRenderer::RENDERTYPE_TEXTUREARRAYS?EntityRenderer::RENDERTYPE_TEXTUREARRAYS:0) |
					((renderTypes & EntityRenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY) == EntityRenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY?EntityRenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY:0) |
					((renderTypes & EntityRenderer::RENDERTYPE_EFFECTCOLORS) == EntityRenderer::RENDERTYPE_EFFECTCOLORS?EntityRenderer::RENDERTYPE_EFFECTCOLORS:0) |
					((renderTypes & EntityRenderer::RENDERTYPE_MATERIALS) == EntityRenderer::RENDERTYPE_MATERIALS?EntityRenderer::RENDERTYPE_MATERIALS:0) |
					((renderTypes & EntityRenderer::RENDERTYPE_MATERIALS_DIFFUSEMASKEDTRANSPARENCY) == EntityRenderer::RENDERTYPE_MATERIALS_DIFFUSEMASKEDTRANSPARENCY?EntityRenderer::RENDERTYPE_MATERIALS_DIFFUSEMASKEDTRANSPARENCY:0) |
					((renderTypes & EntityRenderer::RENDERTYPE_TEXTURES) == EntityRenderer::RENDERTYPE_TEXTURES?EntityRenderer::RENDERTYPE_TEXTURES:0) |
					((renderTypes & EntityRenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY) == EntityRenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY?EntityRenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY:0)|
					((renderTypes & EntityRenderer::RENDERTYPE_LIGHTS) == EntityRenderer::RENDERTYPE_LIGHTS?EntityRenderer::RENDERTYPE_LIGHTS:0)
				);
				if (renderPass == Entity::RENDERPASS_STANDARD) {
					if (renderGeometryBuffer != nullptr) {
						if (lightingShader != nullptr) lightingShader->unUseProgram();
						renderGeometryBuffer->disableGeometryBuffer();
						Engine::getRendererBackend()->setShaderPrefix(shaderPrefix);
						if (renderFrameBuffer != nullptr) renderFrameBuffer->enableFrameBuffer();
						// clear previous frame values
						if (skyShaderEnabled == true) {
							rendererBackend->clear(rendererBackend->CLEAR_DEPTH_BUFFER_BIT);
							skyRenderShader->render(this, false, rendererCamera);
						} else {
							Engine::getRendererBackend()->setClearColor(sceneColor.getRed(), sceneColor.getGreen(), sceneColor.getBlue(), sceneColor.getAlpha());
							rendererBackend->clear(rendererBackend->CLEAR_DEPTH_BUFFER_BIT | rendererBackend->CLEAR_COLOR_BUFFER_BIT);
						}
						//
						renderGeometryBuffer->renderToScreen(this, visibleDecomposedEntities.decalEntities);
						if (lightingShader != nullptr) lightingShader->useProgram(this);
						if (visibleDecomposedEntities.objectsForwardShading.empty() == false) {
							// TODO: use a loop maybe from TERRAIN to STANDARD, but for now it works this way too :)
							// terrain
							entityRenderer->render(
								Entity::RENDERPASS_TERRAIN,
								visibleDecomposedEntities.objectsForwardShading,
								true,
								((renderTypes & EntityRenderer::RENDERTYPE_NORMALS) == EntityRenderer::RENDERTYPE_NORMALS?EntityRenderer::RENDERTYPE_NORMALS:0) |
								((renderTypes & EntityRenderer::RENDERTYPE_TEXTUREARRAYS) == EntityRenderer::RENDERTYPE_TEXTUREARRAYS?EntityRenderer::RENDERTYPE_TEXTUREARRAYS:0) |
								((renderTypes & EntityRenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY) == EntityRenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY?EntityRenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY:0) |
								((renderTypes & EntityRenderer::RENDERTYPE_EFFECTCOLORS) == EntityRenderer::RENDERTYPE_EFFECTCOLORS?EntityRenderer::RENDERTYPE_EFFECTCOLORS:0) |
								((renderTypes & EntityRenderer::RENDERTYPE_MATERIALS) == EntityRenderer::RENDERTYPE_MATERIALS?EntityRenderer::RENDERTYPE_MATERIALS:0) |
								((renderTypes & EntityRenderer::RENDERTYPE_MATERIALS_DIFFUSEMASKEDTRANSPARENCY) == EntityRenderer::RENDERTYPE_MATERIALS_DIFFUSEMASKEDTRANSPARENCY?EntityRenderer::RENDERTYPE_MATERIALS_DIFFUSEMASKEDTRANSPARENCY:0) |
								((renderTypes & EntityRenderer::RENDERTYPE_TEXTURES) == EntityRenderer::RENDERTYPE_TEXTURES?EntityRenderer::RENDERTYPE_TEXTURES:0) |
								((renderTypes & EntityRenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY) == EntityRenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY?EntityRenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY:0)|
								((renderTypes & EntityRenderer::RENDERTYPE_LIGHTS) == EntityRenderer::RENDERTYPE_LIGHTS?EntityRenderer::RENDERTYPE_LIGHTS:0)
							);
							// standard
							entityRenderer->render(
								Entity::RENDERPASS_STANDARD,
								visibleDecomposedEntities.objectsForwardShading,
								true,
								((renderTypes & EntityRenderer::RENDERTYPE_NORMALS) == EntityRenderer::RENDERTYPE_NORMALS?EntityRenderer::RENDERTYPE_NORMALS:0) |
								((renderTypes & EntityRenderer::RENDERTYPE_TEXTUREARRAYS) == EntityRenderer::RENDERTYPE_TEXTUREARRAYS?EntityRenderer::RENDERTYPE_TEXTUREARRAYS:0) |
								((renderTypes & EntityRenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY) == EntityRenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY?EntityRenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY:0) |
								((renderTypes & EntityRenderer::RENDERTYPE_EFFECTCOLORS) == EntityRenderer::RENDERTYPE_EFFECTCOLORS?EntityRenderer::RENDERTYPE_EFFECTCOLORS:0) |
								((renderTypes & EntityRenderer::RENDERTYPE_MATERIALS) == EntityRenderer::RENDERTYPE_MATERIALS?EntityRenderer::RENDERTYPE_MATERIALS:0) |
								((renderTypes & EntityRenderer::RENDERTYPE_MATERIALS_DIFFUSEMASKEDTRANSPARENCY) == EntityRenderer::RENDERTYPE_MATERIALS_DIFFUSEMASKEDTRANSPARENCY?EntityRenderer::RENDERTYPE_MATERIALS_DIFFUSEMASKEDTRANSPARENCY:0) |
								((renderTypes & EntityRenderer::RENDERTYPE_TEXTURES) == EntityRenderer::RENDERTYPE_TEXTURES?EntityRenderer::RENDERTYPE_TEXTURES:0) |
								((renderTypes & EntityRenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY) == EntityRenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY?EntityRenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY:0)|
								((renderTypes & EntityRenderer::RENDERTYPE_LIGHTS) == EntityRenderer::RENDERTYPE_LIGHTS?EntityRenderer::RENDERTYPE_LIGHTS:0)
							);
						}
					}
				} else
				if (renderPass == Entity::RENDERPASS_WATER) rendererBackend->disableBlending();
			}
		}

		// render transparent faces
		entityRenderer->renderTransparentFaces();

		// unuse lighting shader
		if (lightingShader != nullptr) lightingShader->unUseProgram();

		// render shadows if required
		if (applyShadowMapping == true && shadowMapping != nullptr) {
			if (visibleDecomposedEntities.objects.empty() == false) shadowMapping->renderShadowMaps(visibleDecomposedEntities.objects);
			if (visibleDecomposedEntities.objectsForwardShading.empty() == false) shadowMapping->renderShadowMaps(visibleDecomposedEntities.objectsForwardShading);
		}
	}

	// do post processing
	if (applyPostProcessing == true) {
		isUsingPostProcessingTemporaryFrameBuffer = false;
		if (postProcessingPrograms.size() > 0) {
			doPostProcessing(PostProcessingProgram::RENDERPASS_OBJECTS, {{postProcessingFrameBuffer1.get(), postProcessingFrameBuffer2.get() }}, postProcessingFrameBuffer1.get());
			postProcessingFrameBuffer1->enableFrameBuffer();
		}
	}

	// render lines entities
	if (visibleDecomposedEntities.linesEntities.size() > 0) {
		// use lines shader
		if (linesShader != nullptr) linesShader->useProgram(rendererBackend->CONTEXTINDEX_DEFAULT);

		// render lines entities
		for (auto i = 0; i < Entity::RENDERPASS_MAX; i++) {
			auto renderPass = static_cast<Entity::RenderPass>(Math::pow(2, i));
			if ((renderPassMask & renderPass) == renderPass) entityRenderer->render(renderPass, visibleDecomposedEntities.linesEntities);
		}

		// unuse lines shader
		if (linesShader != nullptr) linesShader->unUseProgram(rendererBackend->CONTEXTINDEX_DEFAULT);
	}

	// render point particle systems
	if (doRenderParticleSystems == true && visibleDecomposedEntities.ppses.size() > 0) {
		// use particle shader
		if (particlesShader != nullptr) particlesShader->useProgram(rendererBackend->CONTEXTINDEX_DEFAULT);

		// render points based particle systems
		if (visibleDecomposedEntities.ppses.size() > 0) {
			for (auto i = 0; i < Entity::RENDERPASS_MAX; i++) {
				auto renderPass = static_cast<Entity::RenderPass>(Math::pow(2, i));
				if ((renderPassMask & renderPass) == renderPass) entityRenderer->render(renderPass, visibleDecomposedEntities.ppses);
			}
		}

		// unuse particle shader
		if (particlesShader != nullptr) particlesShader->unUseProgram(rendererBackend->CONTEXTINDEX_DEFAULT);
	}

	// render objects and particles together
	if (applyPostProcessing == true) {
		if (postProcessingPrograms.size() > 0) {
			doPostProcessing(PostProcessingProgram::RENDERPASS_FINAL, {{postProcessingFrameBuffer1.get(), postProcessingFrameBuffer2.get() }}, frameBuffer.get());
		}
	}

	// render objects that are have post post processing render pass
	if (visibleDecomposedEntities.objectsPostPostProcessing.size() > 0) {
		// use lighting shader
		if (lightingShader != nullptr) {
			lightingShader->useProgram(this);
		}

		// render post processing objects
		for (auto i = 0; i < Entity::RENDERPASS_MAX; i++) {
			auto renderPass = static_cast<Entity::RenderPass>(Math::pow(2, i));
			if ((renderPassMask & renderPass) == renderPass) {
				if (renderPass == Entity::RENDERPASS_WATER) rendererBackend->enableBlending();
				entityRenderer->render(
					renderPass,
					visibleDecomposedEntities.objectsPostPostProcessing,
					true,
					((renderTypes & EntityRenderer::RENDERTYPE_NORMALS) == EntityRenderer::RENDERTYPE_NORMALS?EntityRenderer::RENDERTYPE_NORMALS:0) |
					((renderTypes & EntityRenderer::RENDERTYPE_TEXTUREARRAYS) == EntityRenderer::RENDERTYPE_TEXTUREARRAYS?EntityRenderer::RENDERTYPE_TEXTUREARRAYS:0) |
					((renderTypes & EntityRenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY) == EntityRenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY?EntityRenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY:0) |
					((renderTypes & EntityRenderer::RENDERTYPE_EFFECTCOLORS) == EntityRenderer::RENDERTYPE_EFFECTCOLORS?EntityRenderer::RENDERTYPE_EFFECTCOLORS:0) |
					((renderTypes & EntityRenderer::RENDERTYPE_MATERIALS) == EntityRenderer::RENDERTYPE_MATERIALS?EntityRenderer::RENDERTYPE_MATERIALS:0) |
					((renderTypes & EntityRenderer::RENDERTYPE_MATERIALS_DIFFUSEMASKEDTRANSPARENCY) == EntityRenderer::RENDERTYPE_MATERIALS_DIFFUSEMASKEDTRANSPARENCY?EntityRenderer::RENDERTYPE_MATERIALS_DIFFUSEMASKEDTRANSPARENCY:0) |
					((renderTypes & EntityRenderer::RENDERTYPE_TEXTURES) == EntityRenderer::RENDERTYPE_TEXTURES?EntityRenderer::RENDERTYPE_TEXTURES:0) |
					((renderTypes & EntityRenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY) == EntityRenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY?EntityRenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY:0)|
					((renderTypes & EntityRenderer::RENDERTYPE_LIGHTS) == EntityRenderer::RENDERTYPE_LIGHTS?EntityRenderer::RENDERTYPE_LIGHTS:0)
				);
				if (renderPass == Entity::RENDERPASS_WATER) rendererBackend->disableBlending();
			}
		}

		// render transparent faces
		entityRenderer->renderTransparentFaces();

		// unuse lighting shader
		if (lightingShader != nullptr) lightingShader->unUseProgram();

		// render shadows if required
		if (applyShadowMapping == true && shadowMapping != nullptr) {
			if (visibleDecomposedEntities.objectsPostPostProcessing.empty() == false) shadowMapping->renderShadowMaps(visibleDecomposedEntities.objectsPostPostProcessing);
		}
	}

	// render objects that are have post post processing render pass
	if (visibleDecomposedEntities.objectsNoDepthTest.size() > 0) {
		// use lighting shader
		if (lightingShader != nullptr) {
			lightingShader->useProgram(this);
		}

		//
		rendererBackend->disableDepthBufferTest();

		// render post processing objects
		for (auto i = 0; i < Entity::RENDERPASS_MAX; i++) {
			auto renderPass = static_cast<Entity::RenderPass>(Math::pow(2, i));
			if ((renderPassMask & renderPass) == renderPass) {
				if (renderPass == Entity::RENDERPASS_WATER) rendererBackend->enableBlending();
				entityRenderer->render(
					renderPass,
					visibleDecomposedEntities.objectsNoDepthTest,
					true,
					((renderTypes & EntityRenderer::RENDERTYPE_NORMALS) == EntityRenderer::RENDERTYPE_NORMALS?EntityRenderer::RENDERTYPE_NORMALS:0) |
					((renderTypes & EntityRenderer::RENDERTYPE_TEXTUREARRAYS) == EntityRenderer::RENDERTYPE_TEXTUREARRAYS?EntityRenderer::RENDERTYPE_TEXTUREARRAYS:0) |
					((renderTypes & EntityRenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY) == EntityRenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY?EntityRenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY:0) |
					((renderTypes & EntityRenderer::RENDERTYPE_EFFECTCOLORS) == EntityRenderer::RENDERTYPE_EFFECTCOLORS?EntityRenderer::RENDERTYPE_EFFECTCOLORS:0) |
					((renderTypes & EntityRenderer::RENDERTYPE_MATERIALS) == EntityRenderer::RENDERTYPE_MATERIALS?EntityRenderer::RENDERTYPE_MATERIALS:0) |
					((renderTypes & EntityRenderer::RENDERTYPE_MATERIALS_DIFFUSEMASKEDTRANSPARENCY) == EntityRenderer::RENDERTYPE_MATERIALS_DIFFUSEMASKEDTRANSPARENCY?EntityRenderer::RENDERTYPE_MATERIALS_DIFFUSEMASKEDTRANSPARENCY:0) |
					((renderTypes & EntityRenderer::RENDERTYPE_TEXTURES) == EntityRenderer::RENDERTYPE_TEXTURES?EntityRenderer::RENDERTYPE_TEXTURES:0) |
					((renderTypes & EntityRenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY) == EntityRenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY?EntityRenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY:0)|
					((renderTypes & EntityRenderer::RENDERTYPE_LIGHTS) == EntityRenderer::RENDERTYPE_LIGHTS?EntityRenderer::RENDERTYPE_LIGHTS:0)
				);
				if (renderPass == Entity::RENDERPASS_WATER) rendererBackend->disableBlending();
			}
		}

		// render transparent faces
		entityRenderer->renderTransparentFaces();

		//
		rendererBackend->enableDepthBufferTest();

		// unuse lighting shader
		if (lightingShader != nullptr) lightingShader->unUseProgram();

		// render shadows if required
		if (applyShadowMapping == true && shadowMapping != nullptr) {
			if (visibleDecomposedEntities.objectsNoDepthTest.empty() == false) shadowMapping->renderShadowMaps(visibleDecomposedEntities.objectsNoDepthTest);
		}
	}

	// render gizmo objects
	if (visibleDecomposedEntities.objectsGizmo.size() > 0) {
		// default context
		auto _width = renderFrameBuffer != nullptr?renderFrameBuffer->getWidth():(scaledWidth != -1?scaledWidth:width);
		auto _height = renderFrameBuffer != nullptr?renderFrameBuffer->getHeight():(scaledHeight != -1?scaledHeight:height);

		if (gizmoFrameBuffer == nullptr) {
			gizmoFrameBuffer = make_unique<FrameBuffer>(_width, _height, FrameBuffer::FRAMEBUFFER_DEPTHBUFFER | FrameBuffer::FRAMEBUFFER_COLORBUFFER);
			gizmoFrameBuffer->setColorBufferTextureId(frameBuffer->getColorBufferTextureId());
			gizmoFrameBuffer->initialize();
		} else
		if (gizmoFrameBuffer->getWidth() != _width || gizmoFrameBuffer->getHeight() != _height) {
			gizmoFrameBuffer->reshape(_width, _height);
		}

		//
		gizmoCamera->setLookFrom(rendererCamera->getLookFrom());
		gizmoCamera->update(rendererBackend->CONTEXTINDEX_DEFAULT, _width, _height);

		//
		gizmoFrameBuffer->enableFrameBuffer();
		rendererBackend->clear(rendererBackend->CLEAR_DEPTH_BUFFER_BIT);

		// use lighting shader
		if (lightingShader != nullptr) {
			lightingShader->useProgram(this);
		}

		// render
		entityRenderer->render(
			Entity::RENDERPASS_GIZMO,
			visibleDecomposedEntities.objectsGizmo,
			true,
			((renderTypes & EntityRenderer::RENDERTYPE_NORMALS) == EntityRenderer::RENDERTYPE_NORMALS?EntityRenderer::RENDERTYPE_NORMALS:0) |
			((renderTypes & EntityRenderer::RENDERTYPE_TEXTUREARRAYS) == EntityRenderer::RENDERTYPE_TEXTUREARRAYS?EntityRenderer::RENDERTYPE_TEXTUREARRAYS:0) |
			((renderTypes & EntityRenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY) == EntityRenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY?EntityRenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY:0) |
			((renderTypes & EntityRenderer::RENDERTYPE_EFFECTCOLORS) == EntityRenderer::RENDERTYPE_EFFECTCOLORS?EntityRenderer::RENDERTYPE_EFFECTCOLORS:0) |
			((renderTypes & EntityRenderer::RENDERTYPE_MATERIALS) == EntityRenderer::RENDERTYPE_MATERIALS?EntityRenderer::RENDERTYPE_MATERIALS:0) |
			((renderTypes & EntityRenderer::RENDERTYPE_MATERIALS_DIFFUSEMASKEDTRANSPARENCY) == EntityRenderer::RENDERTYPE_MATERIALS_DIFFUSEMASKEDTRANSPARENCY?EntityRenderer::RENDERTYPE_MATERIALS_DIFFUSEMASKEDTRANSPARENCY:0) |
			((renderTypes & EntityRenderer::RENDERTYPE_TEXTURES) == EntityRenderer::RENDERTYPE_TEXTURES?EntityRenderer::RENDERTYPE_TEXTURES:0) |
			((renderTypes & EntityRenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY) == EntityRenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY?EntityRenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY:0)|
			((renderTypes & EntityRenderer::RENDERTYPE_LIGHTS) == EntityRenderer::RENDERTYPE_LIGHTS?EntityRenderer::RENDERTYPE_LIGHTS:0)
		);

		// render transparent faces
		entityRenderer->renderTransparentFaces();

		//
		if (renderFrameBuffer != nullptr) {
			renderFrameBuffer->enableFrameBuffer();
		} else {
			FrameBuffer::disableFrameBuffer();
		}

		// unuse lighting shader
		if (lightingShader != nullptr) lightingShader->unUseProgram();

		//
		rendererCamera->update(rendererBackend->CONTEXTINDEX_DEFAULT, _width, _height);
	}

	// light sources
	if (doRenderLightSource == true) {
		auto _width = scaledWidth != -1?scaledWidth:width;
		auto _height = scaledHeight != -1?scaledHeight:height;
		//
		renderLightSources(_width, _height);
	}

	//
	Engine::getRendererBackend()->setShaderPrefix(string());
	Engine::getRendererBackend()->setEffectPass(0);
}

bool Engine::renderLightSources(int width, int height) {
	auto lightSourceVisible = false;
	for (const auto& light: lights) {
		if (light->isEnabled() == false || light->isRenderSource() == false) continue;
		auto lightSourceSize = light->getSourceSize();
		auto lightSourcePixelSize = width < height?static_cast<float>(lightSourceSize) * static_cast<float>(width):static_cast<float>(lightSourceSize) * static_cast<float>(height);;
		Vector2 lightSourceDimension2D = Vector2(lightSourcePixelSize, lightSourcePixelSize);
		Vector2 lightSourcePosition2D;
		Vector3 lightSourcePosition = Vector3(light->getPosition().getX(), light->getPosition().getY(), light->getPosition().getZ());
		if (light->getPosition().getW() > Math::EPSILON) lightSourcePosition.scale(1.0f / light->getPosition().getW());
		auto visible = computeScreenCoordinateByWorldCoordinate(lightSourcePosition, lightSourcePosition2D, width, height);
		lightSourcePosition2D.sub(lightSourceDimension2D.clone().scale(0.5f));
		if (visible == true) {
			texture2DRenderShader->renderTexture(this, lightSourcePosition2D, lightSourceDimension2D, light->getSourceTextureId(), width, height);
			lightSourceVisible = true;
		}
	}
	return lightSourceVisible;
}

void Engine::dumpShaders() {
	for (auto shaderType = 0; shaderType < SHADERTYPE_MAX; shaderType++)
	for (const auto& shaderId: getRegisteredShader(static_cast<ShaderType>(shaderType))) {
		string shaderTypeString = "unknown";
		switch (shaderType) {
			case SHADERTYPE_OBJECT: shaderTypeString = "object"; break;
			case SHADERTYPE_POSTPROCESSING: shaderTypeString = "postprocessing"; break;
			case SHADERTYPE_SKY: shaderTypeString = "sky"; break;
			default: break;
		}
		Console::printLine(string("TDME2::registered " + shaderTypeString + " shader: ") + shaderId);
		const auto shaderParametersDefaults = getShaderParameterDefaults(shaderId);
		if (shaderParametersDefaults == nullptr) continue;
		if (shaderParametersDefaults->size() > 0) {
			// TODO
			for (const auto parameterDefaults: *shaderParametersDefaults) {
				const auto& parameterName = parameterDefaults.name;
				Console::print("\t" + parameterName);
				switch(parameterDefaults.value.getType()) {
					case ShaderParameter::TYPE_NONE:
						Console::print(" = none");
						break;
					case ShaderParameter::TYPE_BOOLEAN:
						Console::print(" = boolean(");
						Console::print("value = " + string(getShaderParameter(shaderId, parameterName).getBooleanValue() == true?"true":"false"));
						Console::print(")");
						break;
					case ShaderParameter::TYPE_INTEGER:
						Console::print(" = integer(");
						Console::print("value = " + to_string(getShaderParameter(shaderId, parameterName).getIntegerValue()) + ", ");
						Console::print("min = " + to_string(parameterDefaults.min.getIntegerValue()) + ", ");
						Console::print("max = " + to_string(parameterDefaults.max.getIntegerValue()) + ", ");
						Console::print("step = " + to_string(parameterDefaults.step.getIntegerValue()));
						Console::print(")");
						break;
					case ShaderParameter::TYPE_FLOAT:
						Console::print(" = float(");
						Console::print("value = " + to_string(getShaderParameter(shaderId, parameterName).getFloatValue()) + ", ");
						Console::print("min = " + to_string(parameterDefaults.min.getFloatValue()) + ", ");
						Console::print("max = " + to_string(parameterDefaults.max.getFloatValue()) + ", ");
						Console::print("step = " + to_string(parameterDefaults.step.getFloatValue()));
						Console::print(")");
						break;
					case ShaderParameter::TYPE_VECTOR2:
						{
							Console::print(" = Vector2(");
							{
								Console::print("value = ");
								const auto shaderParameterArray = getShaderParameter(shaderId, parameterName).getVector2ValueArray();
								for (auto i = 0; i < shaderParameterArray.size(); i++) {
									if (i != 0) Console::print(",");
									Console::print(to_string(shaderParameterArray[i]));
								}
							}
							{
								Console::print(", min = ");
								const auto shaderParameterArray = parameterDefaults.min.getVector2ValueArray();
								for (auto i = 0; i < shaderParameterArray.size(); i++) {
									if (i != 0) Console::print(",");
									Console::print(to_string(shaderParameterArray[i]));
								}
							}
							{
								Console::print(", max = ");
								const auto shaderParameterArray = parameterDefaults.max.getVector2ValueArray();
								for (auto i = 0; i < shaderParameterArray.size(); i++) {
									if (i != 0) Console::print(",");
									Console::print(to_string(shaderParameterArray[i]));
								}
							}
							{
								Console::print(", step = ");
								const auto shaderParameterArray = parameterDefaults.step.getVector2ValueArray();
								for (auto i = 0; i < shaderParameterArray.size(); i++) {
									if (i != 0) Console::print(",");
									Console::print(to_string(shaderParameterArray[i]));
								}
							}
							Console::print(")");
						}
						break;
					case ShaderParameter::TYPE_VECTOR3:
						{
							Console::print(" = Vector3(");
							{
								Console::print("value = ");
								const auto shaderParameterArray = getShaderParameter(shaderId, parameterName).getVector3ValueArray();
								for (auto i = 0; i < shaderParameterArray.size(); i++) {
									if (i != 0) Console::print(",");
									Console::print(to_string(shaderParameterArray[i]));
								}
							}
							{
								Console::print(", min = ");
								const auto shaderParameterArray = parameterDefaults.min.getVector3ValueArray();
								for (auto i = 0; i < shaderParameterArray.size(); i++) {
									if (i != 0) Console::print(",");
									Console::print(to_string(shaderParameterArray[i]));
								}
							}
							{
								Console::print(", max = ");
								const auto shaderParameterArray = parameterDefaults.max.getVector3ValueArray();
								for (auto i = 0; i < shaderParameterArray.size(); i++) {
									if (i != 0) Console::print(",");
									Console::print(to_string(shaderParameterArray[i]));
								}
							}
							{
								Console::print(", step = ");
								const auto shaderParameterArray = parameterDefaults.step.getVector3ValueArray();
								for (auto i = 0; i < shaderParameterArray.size(); i++) {
									if (i != 0) Console::print(",");
									Console::print(to_string(shaderParameterArray[i]));
								}
							}
							Console::print(")");
						}
						break;
					case ShaderParameter::TYPE_VECTOR4:
						{
							Console::print(" = Vector4(");
							{
								Console::print("value = ");
								const auto shaderParameterArray = getShaderParameter(shaderId, parameterName).getVector4ValueArray();
								for (auto i = 0; i < shaderParameterArray.size(); i++) {
									if (i != 0) Console::print(",");
									Console::print(to_string(shaderParameterArray[i]));
								}
							}
							{
								Console::print(", min = ");
								const auto shaderParameterArray = parameterDefaults.min.getVector4ValueArray();
								for (auto i = 0; i < shaderParameterArray.size(); i++) {
									if (i != 0) Console::print(",");
									Console::print(to_string(shaderParameterArray[i]));
								}
							}
							{
								Console::print(", max = ");
								const auto shaderParameterArray = parameterDefaults.max.getVector4ValueArray();
								for (auto i = 0; i < shaderParameterArray.size(); i++) {
									if (i != 0) Console::print(",");
									Console::print(to_string(shaderParameterArray[i]));
								}
							}
							{
								Console::print(", step = ");
								const auto shaderParameterArray = parameterDefaults.step.getVector4ValueArray();
								for (auto i = 0; i < shaderParameterArray.size(); i++) {
									if (i != 0) Console::print(",");
									Console::print(to_string(shaderParameterArray[i]));
								}
							}
							Console::print(")");
						}
						break;
					case ShaderParameter::TYPE_COLOR4:
						{
							Console::print(" = Color4(");
							{
								Console::print("value = ");
								const auto shaderParameterArray = getShaderParameter(shaderId, parameterName).getColor4ValueArray();
								for (auto i = 0; i < shaderParameterArray.size(); i++) {
									if (i != 0) Console::print(",");
									Console::print(to_string(shaderParameterArray[i]));
								}
							}
							{
								Console::print(", min = ");
								const auto shaderParameterArray = parameterDefaults.min.getColor4ValueArray();
								for (auto i = 0; i < shaderParameterArray.size(); i++) {
									if (i != 0) Console::print(",");
									Console::print(to_string(shaderParameterArray[i]));
								}
							}
							{
								Console::print(", max = ");
								const auto shaderParameterArray = parameterDefaults.max.getColor4ValueArray();
								for (auto i = 0; i < shaderParameterArray.size(); i++) {
									if (i != 0) Console::print(",");
									Console::print(to_string(shaderParameterArray[i]));
								}
							}
							{
								Console::print(", step = ");
								const auto shaderParameterArray = parameterDefaults.step.getColor4ValueArray();
								for (auto i = 0; i < shaderParameterArray.size(); i++) {
									if (i != 0) Console::print(",");
									Console::print(to_string(shaderParameterArray[i]));
								}
							}
							Console::print(")");
						}
						break;
					default:
						Console::print(" = unknown");
						break;
				}
				//
				Console::printLine();
			}
		}
	}
}

void Engine::dumpEntityHierarchy(EntityHierarchy* entityHierarchy, int indent, const string& parentNodeId) {
	for (auto subEntity: entityHierarchy->query(parentNodeId)) {
		for (auto i = 0; i < indent; i++) Console::print("\t");
		string entityType;
		switch (subEntity->getEntityType()) {
			case Entity::ENTITYTYPE_DECAL:
				entityType = "Decal";
				break;
			case Entity::ENTITYTYPE_ENTITYHIERARCHY:
				entityType = "Entity Hierarchy";
				break;
			case Entity::ENTITYTYPE_ENVIRONMENTMAPPING:
				entityType = "Environment Mapping";
				break;
			case Entity::ENTITYTYPE_IMPOSTEROBJECT:
				entityType = "Imposter Object";
				break;
			case Entity::ENTITYTYPE_LINES:
				entityType = "Lines";
				break;
			case Entity::ENTITYTYPE_LODOBJECT:
				entityType = "LOD Object";
				break;
			case Entity::ENTITYTYPE_LODOBJECTIMPOSTER:
				entityType = "LOD Object Imposter";
				break;
			case Entity::ENTITYTYPE_OBJECT:
				entityType = "Object";
				break;
			case Entity::ENTITYTYPE_OBJECTRENDERGROUP:
				entityType = "Object Render Group";
				break;
			case Entity::ENTITYTYPE_FOGPARTICLESYSTEM:
				entityType = "Fog Particle System";
				break;
			case Entity::ENTITYTYPE_OBJECTPARTICLESYSTEM:
				entityType = "Object Particle System";
				break;
			case Entity::ENTITYTYPE_PARTICLESYSTEMGROUP:
				entityType = "Particle System Group";
				break;
			case Entity::ENTITYTYPE_POINTSPARTICLESYSTEM:
				entityType = "Points Particle System";
				break;
		}
		Console::printLine("\t" + subEntity->getId() + " (" + entityType + ")");
		if (subEntity->getEntityType() == Entity::ENTITYTYPE_ENTITYHIERARCHY) {
			dumpEntityHierarchy(dynamic_cast<EntityHierarchy*>(subEntity), indent + 1, string());
		}
		//
		dumpEntityHierarchy(entityHierarchy, indent + 1, subEntity->getId());
	}
}

void Engine::dumpEntities() {
	Console::printLine("Engine::dumpEntities()");
	Console::printLine();
	Console::printLine("Engine Entities:");
	for (const auto& [entityId, entity]: entitiesById) {
		string entityType;
		switch (entity->getEntityType()) {
			case Entity::ENTITYTYPE_DECAL:
				entityType = "Decal";
				break;
			case Entity::ENTITYTYPE_ENTITYHIERARCHY:
				entityType = "Entity Hierarchy";
				break;
			case Entity::ENTITYTYPE_ENVIRONMENTMAPPING:
				entityType = "Environment Mapping";
				break;
			case Entity::ENTITYTYPE_IMPOSTEROBJECT:
				entityType = "Imposter Object";
				break;
			case Entity::ENTITYTYPE_LINES:
				entityType = "Lines";
				break;
			case Entity::ENTITYTYPE_LODOBJECT:
				entityType = "LOD Object";
				break;
			case Entity::ENTITYTYPE_LODOBJECTIMPOSTER:
				entityType = "LOD Object Imposter";
				break;
			case Entity::ENTITYTYPE_OBJECT:
				entityType = "Object";
				break;
			case Entity::ENTITYTYPE_OBJECTRENDERGROUP:
				entityType = "Object Render Group";
				break;
			case Entity::ENTITYTYPE_FOGPARTICLESYSTEM:
				entityType = "Fog Particle System";
				break;
			case Entity::ENTITYTYPE_OBJECTPARTICLESYSTEM:
				entityType = "Object Particle System";
				break;
			case Entity::ENTITYTYPE_PARTICLESYSTEMGROUP:
				entityType = "Particle System Group";
				break;
			case Entity::ENTITYTYPE_POINTSPARTICLESYSTEM:
				entityType = "Points Particle System";
				break;
		}
		Console::printLine("\t" + entity->getId() + " (" + entityType + ")");
		if (entity->getEntityType() == Entity::ENTITYTYPE_ENTITYHIERARCHY) {
			dumpEntityHierarchy(dynamic_cast<EntityHierarchy*>(entity), 2, string());
		}
	}
}
