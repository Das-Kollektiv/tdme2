#include <tdme/engine/Engine.h>

#if defined(VULKAN)
	#define GLFW_INCLUDE_VULKAN
	#include <GLFW/glfw3.h>
#else
	#if ((defined(__linux__) || defined(__FreeBSD__) || defined(__NetBSD__)) && !defined(GLES2)) || defined(_WIN32) || defined(__HAIKU__)
		#define GLEW_NO_GLU
		#include <GL/glew.h>
	#endif
#endif

#include <algorithm>
#include <string>

#include <tdme/application/Application.h>
#include <tdme/engine/Camera.h>
#if defined(VULKAN)
	#include <tdme/engine/EngineVKRenderer.h>
#else
	#include <tdme/engine/EngineGL2Renderer.h>
	#include <tdme/engine/EngineGL3Renderer.h>
	#include <tdme/engine/EngineGLES2Renderer.h>
#endif
#include <tdme/engine/Entity.h>
#include <tdme/engine/EntityHierarchy.h>
#include <tdme/engine/EntityPickingFilter.h>
#include <tdme/engine/FogParticleSystem.h>
#include <tdme/engine/FrameBuffer.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/LinesObject3D.h>
#include <tdme/engine/LODObject3D.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/Object3DRenderGroup.h>
#include <tdme/engine/ObjectParticleSystem.h>
#include <tdme/engine/ParticleSystemEntity.h>
#include <tdme/engine/ParticleSystemGroup.h>
#include <tdme/engine/Partition.h>
#include <tdme/engine/PartitionOctTree.h>
#include <tdme/engine/PointsParticleSystem.h>
#include <tdme/engine/Timing.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Group.h>
#include <tdme/engine/physics/CollisionDetection.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/LineSegment.h>
#include <tdme/engine/subsystems/earlyzrejection/EZRShaderPre.h>
#include <tdme/engine/subsystems/framebuffer/FrameBufferRenderShader.h>
#include <tdme/engine/subsystems/lighting/LightingShader.h>
#include <tdme/engine/subsystems/lines/LinesShader.h>
#include <tdme/engine/subsystems/manager/MeshManager.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/rendering/ObjectBuffer.h>
#include <tdme/engine/subsystems/rendering/Object3DBase_TransformedFacesIterator.h>
#include <tdme/engine/subsystems/rendering/Object3DGroupMesh.h>
#include <tdme/engine/subsystems/rendering/Object3DRenderer.h>
#include <tdme/engine/subsystems/rendering/Object3DRenderer_InstancedRenderFunctionParameters.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderFacesPool.h>
#include <tdme/engine/subsystems/particlesystem/ParticlesShader.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessing.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingProgram.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShader.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMap.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapping.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderPre.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderRender.h>
#include <tdme/engine/subsystems/skinning/SkinningShader.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/gui/renderer/GUIRenderer.h>
#include <tdme/gui/renderer/GUIShader.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utils/ByteBuffer.h>
#include <tdme/utils/VectorIteratorMultiple.h>
#include <tdme/utils/Float.h>
#include <tdme/utils/Console.h>

#include <ext/libpng/png.h>

using std::remove;
using std::string;
using std::to_string;

using tdme::application::Application;
using tdme::engine::Engine;
using tdme::engine::Camera;
using tdme::engine::EngineGL3Renderer;
using tdme::engine::EngineGL2Renderer;
using tdme::engine::EngineGLES2Renderer;
using tdme::engine::EngineVKRenderer;
using tdme::engine::Entity;
using tdme::engine::EntityHierarchy;
using tdme::engine::EntityPickingFilter;
using tdme::engine::FogParticleSystem;
using tdme::engine::FrameBuffer;
using tdme::engine::Light;
using tdme::engine::LinesObject3D;
using tdme::engine::Object3D;
using tdme::engine::LODObject3D;
using tdme::engine::Object3DRenderGroup;
using tdme::engine::ObjectParticleSystem;
using tdme::engine::ParticleSystemEntity;
using tdme::engine::ParticleSystemGroup;
using tdme::engine::Partition;
using tdme::engine::PartitionOctTree;
using tdme::engine::PointsParticleSystem;
using tdme::engine::Timing;
using tdme::engine::model::Color4;
using tdme::engine::model::Group;
using tdme::engine::physics::CollisionDetection;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::LineSegment;
using tdme::engine::subsystems::earlyzrejection::EZRShaderPre;
using tdme::engine::subsystems::lighting::LightingShader;
using tdme::engine::subsystems::lines::LinesShader;
using tdme::engine::subsystems::manager::MeshManager;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::rendering::Object3DBase_TransformedFacesIterator;
using tdme::engine::subsystems::rendering::Object3DRenderer;
using tdme::engine::subsystems::rendering::Object3DRenderer_InstancedRenderFunctionParameters;
using tdme::engine::subsystems::rendering::ObjectBuffer;
using tdme::engine::subsystems::rendering::TransparentRenderFacesPool;
using tdme::engine::subsystems::particlesystem::ParticlesShader;
using tdme::engine::subsystems::postprocessing::PostProcessing;
using tdme::engine::subsystems::postprocessing::PostProcessingProgram;
using tdme::engine::subsystems::postprocessing::PostProcessingShader;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::shadowmapping::ShadowMap;
using tdme::engine::subsystems::shadowmapping::ShadowMapping;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPre;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRender;
using tdme::engine::subsystems::skinning::SkinningShader;
using tdme::gui::GUI;
using tdme::gui::GUIParser;
using tdme::gui::renderer::GUIRenderer;
using tdme::gui::renderer::GUIShader;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utils::ByteBuffer;
using tdme::utils::Float;
using tdme::utils::Console;

Engine* Engine::instance = nullptr;
Renderer* Engine::renderer = nullptr;
TextureManager* Engine::textureManager = nullptr;
VBOManager* Engine::vboManager = nullptr;
MeshManager* Engine::meshManager = nullptr;
GUIRenderer* Engine::guiRenderer = nullptr;
FrameBufferRenderShader* Engine::frameBufferRenderShader = nullptr;
PostProcessing* Engine::postProcessing = nullptr;
PostProcessingShader* Engine::postProcessingShader = nullptr;
Engine::AnimationProcessingTarget Engine::animationProcessingTarget = Engine::AnimationProcessingTarget::CPU;
EZRShaderPre* Engine::ezrShaderPre = nullptr;
ShadowMappingShaderPre* Engine::shadowMappingShaderPre = nullptr;
ShadowMappingShaderRender* Engine::shadowMappingShaderRender = nullptr;
LightingShader* Engine::lightingShader = nullptr;
ParticlesShader* Engine::particlesShader = nullptr;
LinesShader* Engine::linesShader = nullptr;
SkinningShader* Engine::skinningShader = nullptr;
GUIShader* Engine::guiShader = nullptr;
Engine* Engine::currentEngine = nullptr;
bool Engine::skinningShaderEnabled = false;
int Engine::threadCount = 0;
bool Engine::have4K = false;
float Engine::animationBlendingTime = 250.0f;
int32_t Engine::shadowMapWidth = 2048;
int32_t Engine::shadowMapHeight = 2048;
float Engine::shadowMaplightEyeDistanceScale = 4.0f;
float Engine::transformationsComputingReduction1Distance = 25.0f;
float Engine::transformationsComputingReduction2Distance = 50.0f;

vector<Engine::EngineThread*> Engine::engineThreads;

Engine::EngineThread::EngineThread(int idx, void* context):
	Thread("enginethread"),
	idx(idx),
	engine(nullptr),
	context(context) {
	//
	rendering.transparentRenderFacesPool = new TransparentRenderFacesPool();
}

void Engine::EngineThread::run() {
	Console::println("EngineThread::" + string(__FUNCTION__) + "()[" + to_string(idx) + "]: INIT");
	while (isStopRequested() == false) {
		switch(state) {
			case STATE_WAITING:
				while (state == STATE_WAITING) Thread::nanoSleep(10000LL);
				break;
			case STATE_TRANSFORMATIONS:
				engine->computeTransformationsFunction(threadCount, idx);
				state = STATE_SPINNING;
				break;
			case STATE_RENDERING:
				rendering.transparentRenderFacesPool->reset();
				engine->object3DRenderer->renderFunction(threadCount, idx, rendering.parameters.objects, rendering.objectsByShadersAndModels, rendering.parameters.collectTransparentFaces, rendering.parameters.renderTypes, rendering.transparentRenderFacesPool);
				rendering.objectsByShadersAndModels.clear();
				state = STATE_SPINNING;
				break;
			case STATE_SPINNING:
				while (state == STATE_SPINNING) Thread::nanoSleep(100LL);
				break;
		}
	}
	Console::println("EngineThread::" + string(__FUNCTION__) + "()[" + to_string(idx) + "]: DONE");
}

Engine::Engine() {
	timing = new Timing();
	camera = nullptr;
	sceneColor.set(0.0f, 0.0f, 0.0f, 1.0f);
	frameBuffer = nullptr;
	// shadow mapping
	shadowMappingEnabled = false;
	shadowMapping = nullptr;
	// render process state
	renderingInitiated = false;
	renderingComputedTransformations = false;
	//
	initialized = false;
	// post processing frame buffers
	postProcessingFrameBuffer1 = nullptr;
	postProcessingFrameBuffer2 = nullptr;
	postProcessingTemporaryFrameBuffer = nullptr;
	//
	isUsingPostProcessingTemporaryFrameBuffer = false;
}

Engine::~Engine() {
	delete timing;
	delete camera;
	delete gui;
	delete partition;
	if (frameBuffer != nullptr) delete frameBuffer;
	if (postProcessingFrameBuffer1 != nullptr) delete postProcessingFrameBuffer1;
	if (postProcessingFrameBuffer2 != nullptr) delete postProcessingFrameBuffer2;
	if (postProcessingTemporaryFrameBuffer != nullptr) delete postProcessingTemporaryFrameBuffer;
	if (shadowMappingEnabled == true) {
		delete shadowMapping;
	}
	delete object3DRenderer;
	if (instance == this) {
		delete renderer;
		delete textureManager;
		delete vboManager;
		delete meshManager;
		delete guiRenderer;
		delete lightingShader;
		delete particlesShader;
		delete linesShader;
		delete postProcessing;
		delete postProcessingShader;
		delete guiShader;
		delete frameBufferRenderShader;
		delete ezrShaderPre;
		delete shadowMappingShaderPre;
		delete shadowMappingShaderRender;
	}
	// set current engine
	if (currentEngine == this) currentEngine = nullptr;
}

Engine* Engine::getInstance()
{
	if (instance == nullptr) {
		instance = new Engine();
	}
	return instance;
}

Engine* Engine::createOffScreenInstance(int32_t width, int32_t height)
{
	if (instance == nullptr || instance->initialized == false) {
		Console::println(string("Engine::createOffScreenInstance(): Engine not created or not initialized."));
		return nullptr;
	}
	// create off screen engine
	auto offScreenEngine = new Engine();
	offScreenEngine->initialized = true;
	// create GUI
	offScreenEngine->gui = new GUI(offScreenEngine, guiRenderer);
	// create object 3d vbo renderer
	offScreenEngine->object3DRenderer = new Object3DRenderer(offScreenEngine, renderer);
	offScreenEngine->object3DRenderer->initialize();
	// create framebuffers
	offScreenEngine->frameBuffer = new FrameBuffer(width, height, FrameBuffer::FRAMEBUFFER_DEPTHBUFFER | FrameBuffer::FRAMEBUFFER_COLORBUFFER);
	offScreenEngine->frameBuffer->initialize();
	// create camera, frustum partition
	offScreenEngine->camera = new Camera(renderer);
	offScreenEngine->partition = new PartitionOctTree();
	// create lights
	for (auto i = 0; i < offScreenEngine->lights.size(); i++)
		offScreenEngine->lights[i] = Light(renderer, i);
	// create shadow mapping
	if (instance->shadowMappingEnabled == true) {
		offScreenEngine->shadowMapping = new ShadowMapping(offScreenEngine, renderer, offScreenEngine->object3DRenderer);
	}
	//
	offScreenEngine->reshape(0, 0, width, height);
	return offScreenEngine;
}

void Engine::setPartition(Partition* partition)
{
	if (this->partition != nullptr) delete this->partition;
	this->partition = partition;
}

void Engine::addEntity(Entity* entity)
{
	// dispose old entity if any did exist in engine with same id
	removeEntity(entity->getId());

	// init entity
	entity->setEngine(this);
	entity->setRenderer(renderer);
	entity->initialize();
	entitiesById[entity->getId()] = entity;

	// add to partition if enabled and frustum culling requested
	if (entity->isFrustumCulling() == true && entity->isEnabled() == true) partition->addEntity(entity);

	// update
	registerEntity(entity);
}

void Engine::deregisterEntity(Entity* entity) {
	auto hierarchicalId = entity->getId();
	for (auto _entity = entity->getParentEntity(); _entity != nullptr; _entity = _entity->getParentEntity()) hierarchicalId = _entity->getId() + "." + hierarchicalId;

	//
	noFrustumCullingEntitiesById.erase(hierarchicalId);
	noFrustumCullingEntities.erase(remove(noFrustumCullingEntities.begin(), noFrustumCullingEntities.end(), entity), noFrustumCullingEntities.end());
	autoEmitParticleSystemEntities.erase(hierarchicalId);
}

void Engine::registerEntity(Entity* entity) {
	auto hierarchicalId = entity->getId();
	for (auto _entity = entity->getParentEntity(); _entity != nullptr; _entity = _entity->getParentEntity()) hierarchicalId = _entity->getId() + "." + hierarchicalId;

	//
	noFrustumCullingEntitiesById.erase(hierarchicalId);
	noFrustumCullingEntities.erase(remove(noFrustumCullingEntities.begin(), noFrustumCullingEntities.end(), entity), noFrustumCullingEntities.end());
	autoEmitParticleSystemEntities.erase(hierarchicalId);

	// add to no frustum culling
	if (entity->isFrustumCulling() == false && entity->getParentEntity() == nullptr) {
		// otherwise add to no frustum culling entities
		noFrustumCullingEntitiesById[hierarchicalId] = entity;
		noFrustumCullingEntities.push_back(entity);
	}

	// add to auto emit particle system entities
	auto particleSystemEntity = dynamic_cast<ParticleSystemEntity*>(entity);
	if (particleSystemEntity != nullptr && particleSystemEntity->isAutoEmit() == true) {
		autoEmitParticleSystemEntities[hierarchicalId] = particleSystemEntity;
	}
}

void Engine::removeEntity(const string& id)
{
	// get entity and remove if we have any
	auto entityByIdIt = entitiesById.find(id);
	if (entityByIdIt != entitiesById.end()) {
		//
		auto entity = entityByIdIt->second;

		//
		auto hierarchicalId = entity->getId();
		for (auto _entity = entity->getParentEntity(); _entity != nullptr; _entity = _entity->getParentEntity()) hierarchicalId = _entity->getId() + "." + hierarchicalId;

		//
		entitiesById.erase(entityByIdIt);
		autoEmitParticleSystemEntities.erase(hierarchicalId);
		noFrustumCullingEntitiesById.erase(hierarchicalId);

		// remove from partition if enabled and frustum culling requested
		if (entity->isFrustumCulling() == true && entity->isEnabled() == true) partition->removeEntity(entity);
		// dispose entity
		entity->setEngine(nullptr);
		entity->setRenderer(nullptr);
		entity->dispose();
		delete entity;

		// delete from lists
		visibleObjects.erase(remove(visibleObjects.begin(), visibleObjects.end(), entity), visibleObjects.end());
		visibleObjectsPostPostProcessing.erase(remove(visibleObjectsPostPostProcessing.begin(), visibleObjectsPostPostProcessing.end(), entity), visibleObjectsPostPostProcessing.end());
		visibleObjectsNoDepthTest.erase(remove(visibleObjectsNoDepthTest.begin(), visibleObjectsNoDepthTest.end(), entity), visibleObjectsNoDepthTest.end());
		visibleLODObjects.erase(remove(visibleLODObjects.begin(), visibleLODObjects.end(), entity), visibleLODObjects.end());
		visibleOpses.erase(remove(visibleOpses.begin(), visibleOpses.end(), entity), visibleOpses.end());
		visiblePpses.erase(remove(visiblePpses.begin(), visiblePpses.end(), entity), visiblePpses.end());
		visiblePsgs.erase(remove(visiblePsgs.begin(), visiblePsgs.end(), entity), visiblePsgs.end());
		visibleLinesObjects.erase(remove(visibleLinesObjects.begin(), visibleLinesObjects.end(), entity), visibleLinesObjects.end());
		visibleObjectRenderGroups.erase(remove(visibleObjectRenderGroups.begin(), visibleObjectRenderGroups.end(), entity), visibleObjectRenderGroups.end());
		visibleObjectEntityHierarchies.erase(remove(visibleObjectEntityHierarchies.begin(), visibleObjectEntityHierarchies.end(), entity), visibleObjectEntityHierarchies.end());
		visibleEZRObjects.erase(remove(visibleEZRObjects.begin(), visibleEZRObjects.end(), entity), visibleEZRObjects.end());
		noFrustumCullingEntities.erase(remove(noFrustumCullingEntities.begin(), noFrustumCullingEntities.end(), entity), noFrustumCullingEntities.end());
	}
}

void Engine::reset()
{
	vector<string> entitiesToRemove;
	for (auto it: entitiesById) {
		auto entityKey = it.first;
		entitiesToRemove.push_back(entityKey);
	}
	for (auto entityKey: entitiesToRemove) {
		removeEntity(entityKey);
	}
	partition->reset();
	object3DRenderer->reset();
	if (skinningShaderEnabled == true) skinningShader->reset();
}

void Engine::initialize()
{
	// set current engine
	currentEngine = this;

	// exit if already initialized like a offscreen engine instance
	if (initialized == true)
		return;

	#if defined(VULKAN)
		renderer = new EngineVKRenderer(this);
		Console::println(string("TDME::Using Vulkan"));
		// Console::println(string("TDME::Extensions: ") + gl->glGetString(GL::GL_EXTENSIONS));
		shadowMappingEnabled = true;
		setShadowMapSize(2048, 2048);
		skinningShaderEnabled = true;
		animationProcessingTarget = Engine::AnimationProcessingTarget::GPU;
	#else
		// MacOSX, currently GL3 only
		#if defined(__APPLE__)
		{
			renderer = new EngineGL3Renderer(this);
			Console::println(string("TDME::Using GL3+/CORE"));
			// Console::println(string("TDME::Extensions: ") + gl->glGetString(GL::GL_EXTENSIONS));
			shadowMappingEnabled = true;
			setShadowMapSize(1024, 1024);
			skinningShaderEnabled = false;
			animationProcessingTarget = Engine::AnimationProcessingTarget::CPU;
		}
		// Linux/FreeBSD/NetBSD/Win32, GL2 or GL3 via GLEW
		#elif defined(_WIN32) || ((defined(__FreeBSD__) || defined(__NetBSD__) || defined(__linux__)) && !defined(GLES2)) || defined(__HAIKU__)
		{
			int glMajorVersion;
			int glMinorVersion;
			glGetIntegerv(GL_MAJOR_VERSION, &glMajorVersion);
			glGetIntegerv(GL_MINOR_VERSION, &glMinorVersion);
			if ((glMajorVersion == 3 && glMinorVersion >= 2) || glMajorVersion > 3) {
				Console::println(string("TDME::Using GL3+/CORE(" + to_string(glMajorVersion) + "." + to_string(glMinorVersion) + ")"));
				renderer = new EngineGL3Renderer(this);
			} else {
				Console::println(string("TDME::Using GL2(" + to_string(glMajorVersion) + "." + to_string(glMinorVersion) + ")"));
				renderer = new EngineGL2Renderer(this);
			}
			skinningShaderEnabled = (glMajorVersion == 4 && glMinorVersion >= 3) || glMajorVersion > 4;
			// Console::println(string("TDME::Extensions: ") + gl->glGetString(GL::GL_EXTENSIONS));
			shadowMappingEnabled = true;
			setShadowMapSize(2048, 2048);
			animationProcessingTarget = skinningShaderEnabled == true?Engine::AnimationProcessingTarget::GPU:Engine::AnimationProcessingTarget::CPU;
		}
		// GLES2 on Linux
		#elif (defined(__linux__) || defined(__FreeBSD__) || defined(__NetBSD__)) && defined(GLES2)
		{
			renderer = new EngineGLES2Renderer(this);
			Console::println(string("TDME::Using GLES2"));
			// Console::println(string("TDME::Extensions: ") + gl->glGetString(GL::GL_EXTENSIONS));
			if (renderer->isBufferObjectsAvailable() == true && renderer->isDepthTextureAvailable() == true) {
				shadowMappingEnabled = true;
				animationProcessingTarget = Engine::AnimationProcessingTarget::CPU;
				setShadowMapSize(1024, 1024);
			} else {
				shadowMappingEnabled = false;
				animationProcessingTarget = Engine::AnimationProcessingTarget::CPU;
			}
			skinningShaderEnabled = false;
		}
		#else
			Console::println("Engine::initialize(): unsupported GL!");
			return;
		#endif
	#endif

	// engine thread count
	if (renderer->isSupportingMultithreadedRendering() == true) {
		if (threadCount == 0) threadCount = Math::clamp(Thread::getHardwareThreadCount() == 0?2:Thread::getHardwareThreadCount() / 2, 2, 4);
	} else {
		threadCount = 1;
	}
	Console::println(string("TDME::Thread count: ") + to_string(threadCount));

	// initialize object buffers
	ObjectBuffer::initialize();

	// create manager
	textureManager = new TextureManager(renderer);
	vboManager = new VBOManager(renderer);
	meshManager = new MeshManager();

	// init
	initialized = true;
	renderer->initialize();
	renderer->initializeFrame();

	// create object 3d renderer
	object3DRenderer = new Object3DRenderer(this, renderer);
	object3DRenderer->initialize();
	GUIParser::initialize();

	// create GUI
	guiRenderer = new GUIRenderer(renderer);
	guiRenderer->initialize();
	gui = new GUI(this, guiRenderer);
	gui->initialize();

	// create camera
	camera = new Camera(renderer);

	// create lights
	for (auto i = 0; i < lights.size(); i++) lights[i] = Light(renderer, i);

	// create partition
	partition = new PartitionOctTree();

	// create lighting shader
	lightingShader = new LightingShader(renderer);
	lightingShader->initialize();

	// create particles shader
	particlesShader = new ParticlesShader(this, renderer);
	particlesShader->initialize();

	// create particles shader
	linesShader = new LinesShader(this, renderer);
	linesShader->initialize();

	// create gui shader
	guiShader = new GUIShader(renderer);
	guiShader->initialize();

	// create frame buffer render shader
	frameBufferRenderShader = new FrameBufferRenderShader(renderer);
	frameBufferRenderShader->initialize();

	// create post processing shader
	postProcessingShader = new PostProcessingShader(renderer);
	postProcessingShader->initialize();

	// create post processing
	postProcessing = new PostProcessing();

	// check if VBOs are available
	if (renderer->isBufferObjectsAvailable()) {
		Console::println(string("TDME::VBOs are available."));
	} else {
		Console::println(string("TDME::VBOs are not available! Engine will not work!"));
		initialized = false;
	}

	// check FBO support
	if (true == false/*glContext->hasBasicFBOSupport() == false*/) {
		Console::println(string("TDME::Basic FBOs are not available!"));
		shadowMappingEnabled = false;
	} else {
		Console::println(string("TDME::Basic FBOs are available."));
	}

	// TODO: make this configurable
	ezrShaderPre = new EZRShaderPre(renderer);
	ezrShaderPre->initialize();

	// initialize shadow mapping
	if (shadowMappingEnabled == true) {
		Console::println(string("TDME::Using shadow mapping"));
		shadowMappingShaderPre = new ShadowMappingShaderPre(renderer);
		shadowMappingShaderPre->initialize();
		shadowMappingShaderRender = new ShadowMappingShaderRender(renderer);
		shadowMappingShaderRender->initialize();
		shadowMapping = new ShadowMapping(this, renderer, object3DRenderer);
	} else {
		Console::println(string("TDME::Not using shadow mapping"));
	}

	// initialize skinning shader
	if (skinningShaderEnabled == true) {
		Console::println(string("TDME::Using skinning compute shader"));
		skinningShader = new SkinningShader(renderer);
		skinningShader->initialize();
	} else {
		Console::println(string("TDME::Not using skinning compute shader"));
	}

	#define CHECK_INITIALIZED(NAME, SHADER) if (SHADER != nullptr && SHADER->isInitialized() == false) Console::println(string("TDME: ") + NAME + ": Not initialized")

	CHECK_INITIALIZED("EZRShader", ezrShaderPre);
	CHECK_INITIALIZED("ShadowMappingShaderPre", shadowMappingShaderPre);
	CHECK_INITIALIZED("ShadowMappingShader", shadowMappingShaderRender);
	CHECK_INITIALIZED("LightingShader", lightingShader);
	CHECK_INITIALIZED("ParticlesShader", particlesShader);
	CHECK_INITIALIZED("LinesShader", linesShader);
	CHECK_INITIALIZED("GUIShader", guiShader);
	CHECK_INITIALIZED("FrameBufferRenderShader", frameBufferRenderShader);
	CHECK_INITIALIZED("PostProcessingShader", postProcessingShader);

	// check if initialized
	// initialized &= objectsFrameBuffer->isInitialized();
	initialized &= ezrShaderPre == nullptr ? true : ezrShaderPre->isInitialized();
	initialized &= shadowMappingShaderPre == nullptr ? true : shadowMappingShaderPre->isInitialized();
	initialized &= shadowMappingShaderRender == nullptr ? true : shadowMappingShaderRender->isInitialized();
	initialized &= lightingShader->isInitialized();
	initialized &= particlesShader->isInitialized();
	initialized &= linesShader->isInitialized();
	initialized &= guiShader->isInitialized();
	initialized &= frameBufferRenderShader->isInitialized();
	initialized &= postProcessingShader->isInitialized();

	//
	if (renderer->isSupportingMultithreadedRendering() == true) {
		engineThreads.resize(threadCount - 1);
		for (auto i = 0; i < threadCount - 1; i++) {
			engineThreads[i] = new EngineThread(
				i + 1,
				renderer->getContext(i + 1)
			);
			engineThreads[i]->start();
		}
	}

	//
	Console::println(string("TDME::initialized & ready: ") + to_string(initialized));
}

void Engine::reshape(int32_t x, int32_t y, int32_t width, int32_t height)
{
	// set current engine
	currentEngine = this;

	// update our width and height
	this->width = width;
	this->height = height;

	// update frame buffer if we have one
	if (frameBuffer != nullptr) frameBuffer->reshape(width, height);

	// update post processing frame buffer if we have one
	if (postProcessingFrameBuffer1 != nullptr) postProcessingFrameBuffer1->reshape(width, height);
	if (postProcessingFrameBuffer2 != nullptr) postProcessingFrameBuffer2->reshape(width, height);
	if (postProcessingTemporaryFrameBuffer != nullptr) postProcessingTemporaryFrameBuffer->reshape(width, height);

	// update shadow mapping
	if (shadowMapping != nullptr) shadowMapping->reshape(width, height);

	// update GUI system
	gui->reshape(width, height);
}

void Engine::initRendering()
{
	// update timing
	timing->updateTiming();

	// clear lists of visible objects
	visibleObjects.clear();
	visibleObjectsPostPostProcessing.clear();
	visibleObjectsNoDepthTest.clear();
	visibleLODObjects.clear();
	visibleOpses.clear();
	visiblePpses.clear();
	visiblePsgs.clear();
	visibleLinesObjects.clear();
	visibleObjectRenderGroups.clear();
	visibleObjectEntityHierarchies.clear();
	visibleEZRObjects.clear();
	noFrustumCullingEntities.clear();

	//
	renderingInitiated = true;
}

void Engine::computeTransformationsFunction(int threadCount, int threadIdx) {
	auto context = renderer->getContext(threadIdx);
	auto objectIdx = 0;
	for (auto object: visibleObjects) {
		if (threadCount > 1 && objectIdx % threadCount != threadIdx) {
			objectIdx++;
			continue;
		}
		object->preRender(context);
		object->computeTransformations(context);
		objectIdx++;
	}
	for (auto object: visibleObjectsPostPostProcessing) {
		if (threadCount > 1 && objectIdx % threadCount != threadIdx) {
			objectIdx++;
			continue;
		}
		object->preRender(context);
		object->computeTransformations(context);
		objectIdx++;
	}
	for (auto object: visibleObjectsNoDepthTest) {
		if (threadCount > 1 && objectIdx % threadCount != threadIdx) {
			objectIdx++;
			continue;
		}
		object->preRender(context);
		object->computeTransformations(context);
		objectIdx++;
	}
}

void Engine::determineEntityTypes(
	const vector<Entity*>& entities,
	vector<Object3D*>& objects,
	vector<Object3D*>& objectsPostPostProcessing,
	vector<Object3D*>& objectsNoDepthTest,
	vector<LODObject3D*>& lodObjects,
	vector<ObjectParticleSystem*>& opses,
	vector<Entity*>& ppses,
	vector<ParticleSystemGroup*>& psgs,
	vector<LinesObject3D*>& linesObjects,
	vector<Object3DRenderGroup*>& objectRenderGroups,
	vector<EntityHierarchy*>& entityHierarchies
	) {
	Object3D* object = nullptr;
	LODObject3D* lodObject = nullptr;
	ParticleSystemGroup* psg = nullptr;
	ObjectParticleSystem* opse = nullptr;
	PointsParticleSystem* ppse = nullptr;
	FogParticleSystem* fpse = nullptr;
	Object3DRenderGroup* org = nullptr;
	LinesObject3D* lo = nullptr;
	Entity* subEntity = nullptr;
	EntityHierarchy* eh = nullptr;

	#define COMPUTE_ENTITY_TRANSFORMATIONS(_entity) \
	{ \
		if ((object = dynamic_cast<Object3D*>(_entity)) != nullptr) { \
			if (object->isDisableDepthTest() == true) { \
				objectsNoDepthTest.push_back(object); \
			} else \
			if (object->getRenderPass() == Object3D::RENDERPASS_POST_POSTPROCESSING) { \
				objectsPostPostProcessing.push_back(object); \
			} else { \
				objects.push_back(object); \
			} \
			if (object->isEnableEarlyZRejection() == true) { \
				visibleEZRObjects.push_back(object); \
			}; \
		} else \
		if ((lodObject = dynamic_cast<LODObject3D*>(_entity)) != nullptr) { \
			auto object = lodObject->determineLODObject(camera); \
			if (object != nullptr) { \
				lodObjects.push_back(lodObject); \
				if (object->isDisableDepthTest() == true) { \
					objectsNoDepthTest.push_back(object); \
				} else \
				if (object->getRenderPass() == Object3D::RENDERPASS_POST_POSTPROCESSING) { \
					objectsPostPostProcessing.push_back(object); \
				} else { \
					objects.push_back(object); \
				} \
				if (object->isEnableEarlyZRejection() == true) { \
					visibleEZRObjects.push_back(object); \
				}; \
			} \
		} else \
		if ((opse = dynamic_cast<ObjectParticleSystem*>(_entity)) != nullptr) { \
			for (auto object: opse->getEnabledObjects()) { \
				if (object->isDisableDepthTest() == true) { \
					objectsNoDepthTest.push_back(object); \
				} else \
				if (object->getRenderPass() == Object3D::RENDERPASS_POST_POSTPROCESSING) { \
					objectsPostPostProcessing.push_back(object); \
				} else { \
					objects.push_back(object); \
				} \
			} \
			opses.push_back(opse); \
		} else \
		if ((ppse = dynamic_cast<PointsParticleSystem*>(_entity)) != nullptr) { \
			ppses.push_back(ppse); \
		} else \
		if ((fpse = dynamic_cast<FogParticleSystem*>(_entity)) != nullptr) { \
			ppses.push_back(fpse); \
		} else \
		if ((lo = dynamic_cast<LinesObject3D*>(_entity)) != nullptr) { \
			linesObjects.push_back(lo); \
		} \
	}

	// add visible entities to related lists by querying frustum
	for (auto entity: entities) {
		// compute transformations and add to lists
		if ((org = dynamic_cast<Object3DRenderGroup*>(entity)) != nullptr) {
			objectRenderGroups.push_back(org);
			if ((subEntity = org->getEntity()) != nullptr) COMPUTE_ENTITY_TRANSFORMATIONS(subEntity);
		} else
		if ((psg = dynamic_cast<ParticleSystemGroup*>(entity)) != nullptr) {
			psgs.push_back(psg); \
			for (auto ps: psg->getParticleSystems()) COMPUTE_ENTITY_TRANSFORMATIONS(ps);
		} else
		if ((eh = dynamic_cast<EntityHierarchy*>(entity)) != nullptr) {
			entityHierarchies.push_back(eh);
			for (auto entityEh: eh->getEntities()) {
				if (entityEh->isEnabled() == false) continue;
				// compute transformations and add to lists
				if ((org = dynamic_cast<Object3DRenderGroup*>(entityEh)) != nullptr) {
					objectRenderGroups.push_back(org);
					if ((subEntity = org->getEntity()) != nullptr) COMPUTE_ENTITY_TRANSFORMATIONS(subEntity);
				} else
				if ((psg = dynamic_cast<ParticleSystemGroup*>(entityEh)) != nullptr) {
					psgs.push_back(psg); \
					for (auto ps: psg->getParticleSystems()) COMPUTE_ENTITY_TRANSFORMATIONS(ps);
				} else {
					COMPUTE_ENTITY_TRANSFORMATIONS(entityEh);
				}
			}
		} else {
			COMPUTE_ENTITY_TRANSFORMATIONS(entity);
		}
	}
}

void Engine::computeTransformations()
{
	// init rendering if not yet done
	if (renderingInitiated == false) initRendering();

	ParticleSystemEntity* pse = nullptr;

	// do particle systems auto emit
	for (auto it: autoEmitParticleSystemEntities) {
		auto entity = it.second;

		// skip on disabled entities
		if (entity->isEnabled() == false) continue;

		// do auto emit
		if ((pse = dynamic_cast<ParticleSystemEntity*>(entity)) != nullptr) {
			pse->emitParticles();
			pse->updateParticles();
		}
	}

	// determine entity types and store them
	determineEntityTypes(
		partition->getVisibleEntities(camera->getFrustum()),
		visibleObjects,
		visibleObjectsPostPostProcessing,
		visibleObjectsNoDepthTest,
		visibleLODObjects,
		visibleOpses,
		visiblePpses,
		visiblePsgs,
		visibleLinesObjects,
		visibleObjectRenderGroups,
		visibleObjectEntityHierarchies
	);

	// collect entities that do not have frustum culling enabled
	for (auto it: noFrustumCullingEntitiesById) {
		auto entity = it.second;

		// skip on disabled entities
		if (entity->isEnabled() == false) continue;

		//
		noFrustumCullingEntities.push_back(entity);
	}

	// determine additional entity types for objects without frustum culling
	determineEntityTypes(
		noFrustumCullingEntities,
		visibleObjects,
		visibleObjectsPostPostProcessing,
		visibleObjectsNoDepthTest,
		visibleLODObjects,
		visibleOpses,
		visiblePpses,
		visiblePsgs,
		visibleLinesObjects,
		visibleObjectRenderGroups,
		visibleObjectEntityHierarchies
	);

	//
	if (skinningShaderEnabled == true) skinningShader->useProgram();
	if (renderer->isSupportingMultithreadedRendering() == false) {
		computeTransformationsFunction(1, 0);
	} else {
		for (auto engineThread: engineThreads) engineThread->engine = this;
		for (auto engineThread: engineThreads) engineThread->state = EngineThread::STATE_TRANSFORMATIONS;
		computeTransformationsFunction(threadCount, 0);
		for (auto engineThread: engineThreads) while (engineThread->state == EngineThread::STATE_TRANSFORMATIONS);
		for (auto engineThread: engineThreads) engineThread->state = EngineThread::STATE_SPINNING;
	}
	if (skinningShaderEnabled == true) {
		skinningShader->unUseProgram();
	}

	//
	renderingComputedTransformations = true;
}

void Engine::display()
{
	// finish last frame
	if (this == Engine::instance) Engine::renderer->finishFrame();

	// set current engine
	currentEngine = this;

	// do pre rendering steps
	if (renderingInitiated == false) initRendering();
	if (renderingComputedTransformations == false) computeTransformations();

	// init frame
	if (this == Engine::instance) Engine::renderer->initializeFrame();

	// default context
	auto context = Engine::renderer->getDefaultContext();

	// create shadow maps
	if (shadowMapping != nullptr) shadowMapping->createShadowMaps();

	// create post processing frame buffers if having post processing
	if (postProcessingPrograms.size() > 0) {
		if (postProcessingFrameBuffer1 == nullptr) {
			postProcessingFrameBuffer1 = new FrameBuffer(width, height, FrameBuffer::FRAMEBUFFER_DEPTHBUFFER | FrameBuffer::FRAMEBUFFER_COLORBUFFER);
			postProcessingFrameBuffer1->initialize();
		}
		if (postProcessingFrameBuffer2 == nullptr) {
			postProcessingFrameBuffer2 = new FrameBuffer(width, height, FrameBuffer::FRAMEBUFFER_DEPTHBUFFER | FrameBuffer::FRAMEBUFFER_COLORBUFFER);
			postProcessingFrameBuffer2->initialize();
		}
		postProcessingFrameBuffer1->enableFrameBuffer();
	} else {
		if (postProcessingFrameBuffer1 != nullptr) {
			postProcessingFrameBuffer1->dispose();
			delete postProcessingFrameBuffer1;
			postProcessingFrameBuffer1 = nullptr;
		}
		if (postProcessingFrameBuffer2 != nullptr) {
			postProcessingFrameBuffer2->dispose();
			delete postProcessingFrameBuffer2;
			postProcessingFrameBuffer2 = nullptr;
		}
		// render objects to target frame buffer or screen
		if (frameBuffer != nullptr) {
			frameBuffer->enableFrameBuffer();
		} else {
			FrameBuffer::disableFrameBuffer();
		}
	}

	// set up clear color
	Engine::renderer->setClearColor(sceneColor.getRed(), sceneColor.getGreen(), sceneColor.getBlue(), sceneColor.getAlpha());

	// clear previous frame values
	renderer->clear(renderer->CLEAR_DEPTH_BUFFER_BIT | renderer->CLEAR_COLOR_BUFFER_BIT);

	// restore camera from shadow map rendering
	camera->update(context, width, height);

	// store matrices
	modelViewMatrix.set(renderer->getModelViewMatrix());
	projectionMatrix.set(renderer->getProjectionMatrix());
	cameraMatrix.set(renderer->getCameraMatrix());

	// render lines objects
	if (visibleLinesObjects.size() > 0) {
		// use particle shader
		if (linesShader != nullptr) linesShader->useProgram(context);

		// render points based particle systems
		object3DRenderer->render(visibleLinesObjects);

		// unuse particle shader
		if (linesShader != nullptr) linesShader->unUseProgram(context);
	}

	// do depth buffer writing aka early z rejection
	if (ezrShaderPre != nullptr && visibleEZRObjects.size() > 0) {
		// disable color rendering, we only want to write to the Z-Buffer
		renderer->setColorMask(false, false, false, false);
		// render
		ezrShaderPre->useProgram(this);
		// only draw opaque face entities of objects marked as EZR objects
		object3DRenderer->render(
			visibleEZRObjects,
			false,
			Object3DRenderer::RENDERTYPE_NORMALS | // TODO: actually this is not required, but GL2 currently needs this
			Object3DRenderer::RENDERTYPE_TEXTUREARRAYS | // TODO: actually this is not required, but GL2 currently needs this
			Object3DRenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY |
			Object3DRenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY
		);
		// done
		ezrShaderPre->unUseProgram();
		// restore disable color rendering
		renderer->setColorMask(true, true, true, true);
	}

	// use lighting shader
	if (visibleObjects.size() > 0) {
		//
		if (lightingShader != nullptr) lightingShader->useProgram(this);

		// render objects
		object3DRenderer->render(
			visibleObjects,
			true,
			Object3DRenderer::RENDERTYPE_NORMALS |
			Object3DRenderer::RENDERTYPE_TEXTUREARRAYS |
			Object3DRenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY |
			Object3DRenderer::RENDERTYPE_EFFECTCOLORS |
			Object3DRenderer::RENDERTYPE_MATERIALS |
			Object3DRenderer::RENDERTYPE_MATERIALS_DIFFUSEMASKEDTRANSPARENCY |
			Object3DRenderer::RENDERTYPE_TEXTURES |
			Object3DRenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY |
			Object3DRenderer::RENDERTYPE_LIGHTS
		);

		// unuse lighting shader
		if (lightingShader != nullptr) lightingShader->unUseProgram();

		// render shadows if required
		if (shadowMapping != nullptr) shadowMapping->renderShadowMaps(visibleObjects);
	}

	// do post processing
	isUsingPostProcessingTemporaryFrameBuffer = false;
	if (postProcessingPrograms.size() > 0) {
		doPostProcessing(PostProcessingProgram::RENDERPASS_OBJECTS, {{postProcessingFrameBuffer1, postProcessingFrameBuffer2 }}, postProcessingFrameBuffer1);
		postProcessingFrameBuffer1->enableFrameBuffer();
	}

	// render point particle systems
	if (visiblePpses.size() > 0) {
		// use particle shader
		if (particlesShader != nullptr) particlesShader->useProgram(context);

		// render points based particle systems
		if (visiblePpses.size() > 0) object3DRenderer->render(visiblePpses);

		// unuse particle shader
		if (particlesShader != nullptr) particlesShader->unUseProgram(context);
	}

	// render objects and particles together
	if (postProcessingPrograms.size() > 0) {
		doPostProcessing(PostProcessingProgram::RENDERPASS_FINAL, {{postProcessingFrameBuffer1, postProcessingFrameBuffer2 }}, frameBuffer);
	}

	// render objects to target frame buffer or screen
	if (frameBuffer != nullptr) FrameBuffer::disableFrameBuffer();

	// render objects that are have post post processing render pass
	if (visibleObjectsPostPostProcessing.size() > 0) {
		// use lighting shader
		if (lightingShader != nullptr) {
			lightingShader->useProgram(this);
		}

		// render post processing objects
		object3DRenderer->render(
			visibleObjectsPostPostProcessing,
			true,
			Object3DRenderer::RENDERTYPE_NORMALS |
			Object3DRenderer::RENDERTYPE_TEXTUREARRAYS |
			Object3DRenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY |
			Object3DRenderer::RENDERTYPE_EFFECTCOLORS |
			Object3DRenderer::RENDERTYPE_MATERIALS |
			Object3DRenderer::RENDERTYPE_MATERIALS_DIFFUSEMASKEDTRANSPARENCY |
			Object3DRenderer::RENDERTYPE_TEXTURES |
			Object3DRenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY |
			Object3DRenderer::RENDERTYPE_LIGHTS
		);

		// unuse lighting shader
		if (lightingShader != nullptr) lightingShader->unUseProgram();

		// render shadows if required
		if (shadowMapping != nullptr) shadowMapping->renderShadowMaps(visibleObjectsPostPostProcessing);
	}

	// render objects that are have post post processing render pass
	if (visibleObjectsNoDepthTest.size() > 0) {
		// use lighting shader
		if (lightingShader != nullptr) {
			lightingShader->useProgram(this);
		}

		//
		renderer->disableDepthBufferTest();

		// render post processing objects
		object3DRenderer->render(
			visibleObjectsNoDepthTest,
			true,
			Object3DRenderer::RENDERTYPE_NORMALS |
			Object3DRenderer::RENDERTYPE_TEXTUREARRAYS |
			Object3DRenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY |
			Object3DRenderer::RENDERTYPE_EFFECTCOLORS |
			Object3DRenderer::RENDERTYPE_MATERIALS |
			Object3DRenderer::RENDERTYPE_MATERIALS_DIFFUSEMASKEDTRANSPARENCY |
			Object3DRenderer::RENDERTYPE_TEXTURES |
			Object3DRenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY |
			Object3DRenderer::RENDERTYPE_LIGHTS
		);

		//
		renderer->enableDepthBufferTest();

		// unuse lighting shader
		if (lightingShader != nullptr) lightingShader->unUseProgram();

		// render shadows if required
		if (shadowMapping != nullptr) shadowMapping->renderShadowMaps(visibleObjectsNoDepthTest);
	}

	// delete post processing termporary buffer if not required anymore
	if (isUsingPostProcessingTemporaryFrameBuffer == false && postProcessingTemporaryFrameBuffer != nullptr) {
		postProcessingTemporaryFrameBuffer->dispose();
		delete postProcessingTemporaryFrameBuffer;
		postProcessingTemporaryFrameBuffer = nullptr;
	}

	// clear pre render states
	renderingInitiated = false;
	renderingComputedTransformations = false;

	//
	for (auto engineThread: engineThreads) engineThread->state = EngineThread::STATE_WAITING;

	// restore matrices
	renderer->getModelViewMatrix().set(modelViewMatrix);
	renderer->getProjectionMatrix().set(projectionMatrix);
	renderer->getCameraMatrix().set(cameraMatrix);
}

void Engine::computeWorldCoordinateByMousePosition(int32_t mouseX, int32_t mouseY, float z, Vector3& worldCoordinate)
{
	// see: http://stackoverflow.com/questions/7692988/opengl-math-projecting-screen-space-to-world-space-coords-solved
	Matrix4x4 tmpMatrix4x4;
	Vector4 tmpVector4a;
	Vector4 tmpVector4b;
	tmpMatrix4x4.set(modelViewMatrix).multiply(projectionMatrix).invert();
	tmpMatrix4x4.multiply(
		tmpVector4a.set(
			(2.0f * mouseX / width) - 1.0f,
			1.0f - (2.0f * mouseY / height),
			2.0f * z - 1.0f, 1.0f
		),
		tmpVector4b
	);
	tmpVector4b.scale(1.0f / tmpVector4b.getW());
	worldCoordinate.set(
		tmpVector4b.getX(),
		tmpVector4b.getY(),
		tmpVector4b.getZ()
	);
}

void Engine::computeWorldCoordinateByMousePosition(int32_t mouseX, int32_t mouseY, Vector3& worldCoordinate)
{
	// use framebuffer if we have one
	if (frameBuffer != nullptr)
		frameBuffer->enableFrameBuffer();

	// see: http://stackoverflow.com/questions/7692988/opengl-math-projecting-screen-space-to-world-space-coords-solved
	auto z = renderer->readPixelDepth(mouseX, height - mouseY);

	// unuse framebuffer if we have one
	if (frameBuffer != nullptr)
		FrameBuffer::disableFrameBuffer();

	//
	computeWorldCoordinateByMousePosition(mouseX, mouseY, z, worldCoordinate);
}

Entity* Engine::getEntityByMousePosition(
	bool forcePicking,
	int32_t mouseX,
	int32_t mouseY,
	const vector<Object3D*>& objects,
	const vector<Object3D*>& objectsPostPostProcessing,
	const vector<Object3D*>& objectsNoDepthTest,
	const vector<LODObject3D*>& lodObjects,
	const vector<ObjectParticleSystem*>& opses,
	const vector<Entity*>& ppses,
	const vector<ParticleSystemGroup*>& psgs,
	const vector<LinesObject3D*>& linesObjects,
	const vector<EntityHierarchy*>& entityHierarchies,
	EntityPickingFilter* filter,
	Group** object3DGroup
)
{
	// get world position of mouse position at near and far plane
	Vector3 tmpVector3a;
	Vector3 tmpVector3b;
	Vector3 tmpVector3c;
	Vector3 tmpVector3d;
	Vector3 tmpVector3e;
	computeWorldCoordinateByMousePosition(mouseX, mouseY, 0.0f, tmpVector3a);
	computeWorldCoordinateByMousePosition(mouseX, mouseY, 1.0f, tmpVector3b);

	// selected entity
	auto selectedEntityDistance = Float::MAX_VALUE;
	Entity* selectedEntity = nullptr;
	Group* selectedObject3DGroup = nullptr;

	// iterate visible objects that have no depth test, check if ray with given mouse position from near plane to far plane collides with each object's triangles
	for (auto entity: objectsNoDepthTest) {
		// skip if not pickable or ignored by filter
		if (forcePicking == false && entity->isPickable() == false) continue;
		if (filter != nullptr && filter->filterEntity(entity) == false) continue;
		// do the collision test
		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getBoundingBoxTransformed(), tmpVector3a, tmpVector3b, tmpVector3c, tmpVector3d) == true) {
			for (auto it = entity->getTransformedFacesIterator()->iterator(); it->hasNext();) {
				auto& vertices = it->next();
				if (LineSegment::doesLineSegmentCollideWithTriangle(vertices[0], vertices[1], vertices[2], tmpVector3a, tmpVector3b, tmpVector3e) == true) {
					auto entityDistance = tmpVector3e.sub(tmpVector3a).computeLengthSquared();
					// check if match or better match
					if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
						selectedEntity = entity;
						selectedEntityDistance = entityDistance;
						selectedObject3DGroup = it->getGroup();
					}
				}
			}
		}
	}
	// they have first priority right now
	if (selectedEntity != nullptr) {
		if (object3DGroup != nullptr) *object3DGroup = selectedObject3DGroup;
		for (auto _entity = selectedEntity; _entity != nullptr; _entity = _entity->getParentEntity()) {
			if (_entity->getParentEntity() == nullptr) return _entity;
		}
		return nullptr;
	}

	// iterate visible object partition systems, check if ray with given mouse position from near plane to far plane collides with bounding volume
	for (auto entity: opses) {
		// skip if not pickable or ignored by filter
		if (forcePicking == false && entity->isPickable() == false) continue;
		if (filter != nullptr && filter->filterEntity(entity) == false) continue;
		// do the collision test
		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getBoundingBoxTransformed(), tmpVector3a, tmpVector3b, tmpVector3c, tmpVector3d) == true) {
			auto entityDistance = tmpVector3e.set(entity->getBoundingBoxTransformed()->getCenter()).sub(tmpVector3a).computeLengthSquared();
			// check if match or better match
			if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
				selectedEntity = entity;
				selectedEntityDistance = entityDistance;
				selectedObject3DGroup = nullptr;
			}
		}
	}

	// iterate visible point partition systems, check if ray with given mouse position from near plane to far plane collides with bounding volume
	for (auto entity: ppses) {
		// skip if not pickable or ignored by filter
		if (forcePicking == false && entity->isPickable() == false) continue;
		if (filter != nullptr && filter->filterEntity(entity) == false) continue;
		// do the collision test
		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getBoundingBoxTransformed(), tmpVector3a, tmpVector3b, tmpVector3c, tmpVector3d) == true) {
			auto entityDistance = tmpVector3e.set(entity->getBoundingBoxTransformed()->getCenter()).sub(tmpVector3a).computeLengthSquared();
			// check if match or better match
			if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
				selectedEntity = entity;
				selectedEntityDistance = entityDistance;
				selectedObject3DGroup = nullptr;
			}
		}
	}

	// iterate visible particle system groups, check if ray with given mouse position from near plane to far plane collides with bounding volume
	for (auto entity: psgs) {
		// skip if not pickable or ignored by filter
		if (forcePicking == false && entity->isPickable() == false) continue;
		if (filter != nullptr && filter->filterEntity(entity) == false) continue;
		// do the collision test
		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getBoundingBoxTransformed(), tmpVector3a, tmpVector3b, tmpVector3c, tmpVector3d) == true) {
			auto entityDistance = tmpVector3e.set(entity->getBoundingBoxTransformed()->getCenter()).sub(tmpVector3a).computeLengthSquared();
			// check if match or better match
			if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
				selectedEntity = entity;
				selectedEntityDistance = entityDistance;
				selectedObject3DGroup = nullptr;
			}
		}
	}

	// iterate visible line objects, check if ray with given mouse position from near plane to far plane collides with each object's triangles
	for (auto entity: linesObjects) {
		// skip if not pickable or ignored by filter
		if (forcePicking == false && entity->isPickable() == false) continue;
		if (filter != nullptr && filter->filterEntity(entity) == false) continue;
		// do the collision test
		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getBoundingBoxTransformed(), tmpVector3a, tmpVector3b, tmpVector3c, tmpVector3d) == true) {
			auto entityDistance = tmpVector3e.set(entity->getBoundingBoxTransformed()->getCenter()).sub(tmpVector3a).computeLengthSquared();
			// check if match or better match
			if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
				selectedEntity = entity;
				selectedEntityDistance = entityDistance;
				selectedObject3DGroup = nullptr;
			}
		}
	}

	// iterate visible objects, check if ray with given mouse position from near plane to far plane collides with each object's triangles
	for (auto entity: objects) {
		// skip if not pickable or ignored by filter
		if (forcePicking == false && entity->isPickable() == false) continue;
		if (filter != nullptr && filter->filterEntity(entity) == false) continue;
		// do the collision test
		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getBoundingBoxTransformed(), tmpVector3a, tmpVector3b, tmpVector3c, tmpVector3d) == true) {
			for (auto it = entity->getTransformedFacesIterator()->iterator(); it->hasNext();) {
				auto& vertices = it->next();
				if (LineSegment::doesLineSegmentCollideWithTriangle(vertices[0], vertices[1], vertices[2], tmpVector3a, tmpVector3b, tmpVector3e) == true) {
					auto entityDistance = tmpVector3e.sub(tmpVector3a).computeLengthSquared();
					// check if match or better match
					if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
						selectedEntity = entity;
						selectedEntityDistance = entityDistance;
						selectedObject3DGroup = it->getGroup();
					}
				}
			}
		}
	}

	// iterate visible objects that have post post processing renderpass, check if ray with given mouse position from near plane to far plane collides with each object's triangles
	for (auto entity: objectsPostPostProcessing) {
		// skip if not pickable or ignored by filter
		if (forcePicking == false && entity->isPickable() == false) continue;
		if (filter != nullptr && filter->filterEntity(entity) == false) continue;
		// do the collision test
		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getBoundingBoxTransformed(), tmpVector3a, tmpVector3b, tmpVector3c, tmpVector3d) == true) {
			for (auto it = entity->getTransformedFacesIterator()->iterator(); it->hasNext();) {
				auto& vertices = it->next();
				if (LineSegment::doesLineSegmentCollideWithTriangle(vertices[0], vertices[1], vertices[2], tmpVector3a, tmpVector3b, tmpVector3e) == true) {
					auto entityDistance = tmpVector3e.sub(tmpVector3a).computeLengthSquared();
					// check if match or better match
					if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
						selectedEntity = entity;
						selectedEntityDistance = entityDistance;
						selectedObject3DGroup = it->getGroup();
					}
				}
			}
		}
	}

	// iterate visible LOD objects, check if ray with given mouse position from near plane to far plane collides with each object's triangles
	for (auto entity: lodObjects) {
		// skip if not pickable or ignored by filter
		if (forcePicking == false && entity->isPickable() == false) continue;
		if (filter != nullptr && filter->filterEntity(entity) == false) continue;
		// do the collision test
		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getBoundingBoxTransformed(), tmpVector3a, tmpVector3b, tmpVector3c, tmpVector3d) == true) {
			auto object = entity->getLODObject();
			if (object != nullptr) {
				for (auto it = object->getTransformedFacesIterator()->iterator(); it->hasNext();) {
					auto& vertices = it->next();
					if (LineSegment::doesLineSegmentCollideWithTriangle(vertices[0], vertices[1], vertices[2], tmpVector3a, tmpVector3b, tmpVector3e) == true) {
						auto entityDistance = tmpVector3e.sub(tmpVector3a).computeLengthSquared();
						// check if match or better match
						if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
							selectedEntity = entity;
							selectedEntityDistance = entityDistance;
						}
					}
					selectedObject3DGroup = it->getGroup();
				}
			}
		}
	}

	// iterate visible entity hierarches, check if ray with given mouse position from near plane to far plane collides with bounding volume
	for (auto entity: entityHierarchies) {
		// skip if not pickable or ignored by filter
		if (forcePicking == false && entity->isPickable() == false) continue;
		if (filter != nullptr && filter->filterEntity(entity) == false) continue;
		// do the collision test
		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getBoundingBoxTransformed(), tmpVector3a, tmpVector3b, tmpVector3c, tmpVector3d) == true) {
			vector<Object3D*> objectsEH;
			vector<Object3D*> objectsPostPostProcessingEH;
			vector<Object3D*> objectsNoDepthTestEH;
			vector<LODObject3D*> lodObjectsEH;
			vector<ObjectParticleSystem*> opsesEH;
			vector<Entity*> ppsesEH;
			vector<ParticleSystemGroup*> psgsEH;
			vector<LinesObject3D*> linesObjectsEH;
			vector<Object3DRenderGroup*> objectRenderGroupsEH;
			vector<EntityHierarchy*> entityHierarchiesEH;
			Group* object3DGroupEH = nullptr;
			determineEntityTypes(
				entity->getEntities(),
				objectsEH,
				objectsPostPostProcessingEH,
				objectsNoDepthTestEH,
				lodObjectsEH,
				opsesEH,
				ppsesEH,
				psgsEH,
				linesObjectsEH,
				objectRenderGroupsEH,
				entityHierarchiesEH
			);
			auto subEntity = getEntityByMousePosition(
				true,
				mouseX,
				mouseY,
				objectsEH,
				objectsPostPostProcessingEH,
				objectsNoDepthTestEH,
				lodObjectsEH,
				opsesEH,
				ppsesEH,
				psgsEH,
				linesObjectsEH,
				entityHierarchiesEH,
				filter,
				&object3DGroupEH
			);
			if (subEntity != nullptr) {
				auto entityDistance = tmpVector3e.set(subEntity->getBoundingBoxTransformed()->getCenter()).sub(tmpVector3a).computeLengthSquared();
				// check if match or better match
				if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
					selectedEntity = entity;
					selectedEntityDistance = entityDistance;
					selectedObject3DGroup = object3DGroupEH;
				}
			}
		}
	}

	// store group
	if (object3DGroup != nullptr) *object3DGroup = selectedObject3DGroup;

	//
	if (selectedEntity != nullptr) {
		for (auto _entity = selectedEntity; _entity != nullptr; _entity = _entity->getParentEntity()) {
			if (_entity->getParentEntity() == nullptr) return _entity;
		}
		return nullptr;
	} else {
		return nullptr;
	}
}

Entity* Engine::getEntityByMousePosition(int32_t mouseX, int32_t mouseY, Vector3& contactPoint, EntityPickingFilter* filter, Group** object3DGroup) {
	// get world position of mouse position at near and far plane
	Vector3 startPoint;
	Vector3 endPoint;
	computeWorldCoordinateByMousePosition(mouseX, mouseY, 0.0f, startPoint);
	computeWorldCoordinateByMousePosition(mouseX, mouseY, 1.0f, endPoint);

	//
	return doRayCasting(startPoint, endPoint, contactPoint, filter);// TODO: object 3d group
}

Entity* Engine::doRayCasting(
	bool forcePicking,
	const vector<Object3D*>& objects,
	const vector<Object3D*>& objectsPostPostProcessing,
	const vector<Object3D*>& objectsNoDepthTest,
	const vector<LODObject3D*>& lodObjects,
	const vector<EntityHierarchy*>& entityHierarchies,
	const Vector3& startPoint,
	const Vector3& endPoint,
	Vector3& contactPoint,
	EntityPickingFilter* filter) {
	Vector3 tmpVector3c;
	Vector3 tmpVector3d;
	Vector3 tmpVector3e;

	// selected entity
	auto selectedEntityDistance = Float::MAX_VALUE;
	Entity* selectedEntity = nullptr;

	// iterate visible objects with no depth writing, check if ray with given mouse position from near plane to far plane collides with each object's triangles
	for (auto entity: objectsNoDepthTest) {
		// skip if not pickable or ignored by filter
		if (forcePicking == false && entity->isPickable() == false) continue;
		if (filter != nullptr && filter->filterEntity(entity) == false) continue;
		// do the collision test
		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getBoundingBoxTransformed(), startPoint, endPoint, tmpVector3c, tmpVector3d) == true) {
			for (auto it = entity->getTransformedFacesIterator()->iterator(); it->hasNext();) {
				auto& vertices = it->next();
				if (LineSegment::doesLineSegmentCollideWithTriangle(vertices[0], vertices[1], vertices[2], startPoint, endPoint, tmpVector3e) == true) {
					auto entityDistance = tmpVector3e.clone().sub(startPoint).computeLengthSquared();
					// check if match or better match
					if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
						selectedEntity = entity;
						selectedEntityDistance = entityDistance;
						contactPoint = tmpVector3e;
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
	for (auto entity: objects) {
		// skip if not pickable or ignored by filter
		if (forcePicking == false && entity->isPickable() == false) continue;
		if (filter != nullptr && filter->filterEntity(entity) == false) continue;
		// do the collision test
		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getBoundingBoxTransformed(), startPoint, endPoint, tmpVector3c, tmpVector3d) == true) {
			for (auto it = entity->getTransformedFacesIterator()->iterator(); it->hasNext();) {
				auto& vertices = it->next();
				if (LineSegment::doesLineSegmentCollideWithTriangle(vertices[0], vertices[1], vertices[2], startPoint, endPoint, tmpVector3e) == true) {
					auto entityDistance = tmpVector3e.clone().sub(startPoint).computeLengthSquared();
					// check if match or better match
					if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
						selectedEntity = entity;
						selectedEntityDistance = entityDistance;
						contactPoint = tmpVector3e;
					}
				}
			}
		}
	}

	// iterate visible objects that have post post processing renderpass, check if ray with given mouse position from near plane to far plane collides with each object's triangles
	for (auto entity: objectsPostPostProcessing) {
		// skip if not pickable or ignored by filter
		if (forcePicking == false && entity->isPickable() == false) continue;
		if (filter != nullptr && filter->filterEntity(entity) == false) continue;
		// do the collision test
		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getBoundingBoxTransformed(), startPoint, endPoint, tmpVector3c, tmpVector3d) == true) {
			for (auto it = entity->getTransformedFacesIterator()->iterator(); it->hasNext();) {
				auto& vertices = it->next();
				if (LineSegment::doesLineSegmentCollideWithTriangle(vertices[0], vertices[1], vertices[2], startPoint, endPoint, tmpVector3e) == true) {
					auto entityDistance = tmpVector3e.clone().sub(startPoint).computeLengthSquared();
					// check if match or better match
					if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
						selectedEntity = entity;
						selectedEntityDistance = entityDistance;
						contactPoint = tmpVector3e;
					}
				}
			}
		}
	}

	// iterate visible LOD objects, check if ray with given mouse position from near plane to far plane collides with each object's triangles
	for (auto entity: lodObjects) {
		// skip if not pickable or ignored by filter
		if (forcePicking == false && entity->isPickable() == false) continue;
		if (filter != nullptr && filter->filterEntity(entity) == false) continue;
		// do the collision test
		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getBoundingBoxTransformed(), startPoint, endPoint, tmpVector3c, tmpVector3d) == true) {
			auto object = entity->getLODObject();
			if (object != nullptr) {
				for (auto it = object->getTransformedFacesIterator()->iterator(); it->hasNext();) {
					auto& vertices = it->next();
					if (LineSegment::doesLineSegmentCollideWithTriangle(vertices[0], vertices[1], vertices[2], startPoint, endPoint, tmpVector3e) == true) {
						auto entityDistance = tmpVector3e.sub(startPoint).computeLengthSquared();
						// check if match or better match
						if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
							selectedEntity = entity;
							selectedEntityDistance = entityDistance;
							contactPoint = tmpVector3e;
						}
					}
				}
			}
		}
	}

	// iterate visible entity hierarches, check if ray with given mouse position from near plane to far plane collides with bounding volume
	for (auto entity: entityHierarchies) {
		// skip if not pickable or ignored by filter
		if (forcePicking == false && entity->isPickable() == false) continue;
		if (filter != nullptr && filter->filterEntity(entity) == false) continue;
		// do the collision test
		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getBoundingBoxTransformed(), startPoint, endPoint, tmpVector3c, tmpVector3d) == true) {
			vector<Object3D*> objectsEH;
			vector<Object3D*> objectsPostPostProcessingEH;
			vector<Object3D*> objectsNoDepthTestEH;
			vector<LODObject3D*> lodObjectsEH;
			vector<ObjectParticleSystem*> opsesEH;
			vector<Entity*> ppsesEH;
			vector<ParticleSystemGroup*> psgsEH;
			vector<LinesObject3D*> linesObjectsEH;
			vector<Object3DRenderGroup*> objectRenderGroupsEH;
			vector<EntityHierarchy*> entityHierarchiesEH;
			determineEntityTypes(
				entity->getEntities(),
				objectsEH,
				objectsPostPostProcessingEH,
				objectsNoDepthTestEH,
				lodObjectsEH,
				opsesEH,
				ppsesEH,
				psgsEH,
				linesObjectsEH,
				objectRenderGroupsEH,
				entityHierarchiesEH
			);
			Vector3 contactPointEH;
			auto entity = doRayCasting(
				true,
				objectsEH,
				objectsPostPostProcessingEH,
				objectsNoDepthTestEH,
				lodObjectsEH,
				entityHierarchiesEH,
				startPoint,
				endPoint,
				contactPointEH,
				filter
			);
			if (entity != nullptr) {
				auto entityDistance = tmpVector3e.sub(startPoint).computeLengthSquared();
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

void Engine::computeScreenCoordinateByWorldCoordinate(const Vector3& worldCoordinate, Vector2& screenCoordinate)
{
	Matrix4x4 tmpMatrix4x4;
	Vector4 tmpVector4a;
	Vector4 tmpVector4b;
	// convert to normalized device coordinates
	tmpMatrix4x4.set(modelViewMatrix).multiply(projectionMatrix);
	tmpMatrix4x4.multiply(tmpVector4b.set(worldCoordinate, 1.0f), tmpVector4a);
	tmpVector4a.scale(1.0f / tmpVector4a.getW());
	auto screenCoordinateXYZW = tmpVector4a.getArray();
	// convert to screen coordinate
	screenCoordinate.setX((screenCoordinateXYZW[0] + 1.0f) * width / 2.0f);
	screenCoordinate.setY(height - ((screenCoordinateXYZW[1] + 1.0f) * height / 2.0f));
}

void Engine::dispose()
{
	// finish last frame
	if (this == Engine::instance) Engine::renderer->finishFrame();

	// remove entities
	vector<string> entitiesToRemove;
	for (auto it: entitiesById) {
		auto entityKey = it.first;
		entitiesToRemove.push_back(entityKey);
	}
	for (auto entityKey: entitiesToRemove) {
		removeEntity(entityKey);
	}

	// dispose shadow mapping
	if (shadowMapping != nullptr) shadowMapping->dispose();

	// dispose frame buffers
	if (frameBuffer != nullptr) frameBuffer->dispose();
	if (postProcessingFrameBuffer1 != nullptr) postProcessingFrameBuffer1->dispose();
	if (postProcessingFrameBuffer2 != nullptr) postProcessingFrameBuffer2->dispose();
	if (postProcessingTemporaryFrameBuffer != nullptr) postProcessingTemporaryFrameBuffer->dispose();

	// dispose GUI
	gui->dispose();
	if (this == Engine::instance) {
		guiRenderer->dispose();
	}

	// dispose object 3d VBO renderer
	object3DRenderer->dispose();
	if (instance == this) {
		guiRenderer->dispose();
	}

	// set current engine
	if (currentEngine == this) currentEngine = nullptr;
}

void Engine::initGUIMode()
{
	// use framebuffer if we have one
	if (frameBuffer != nullptr)
		frameBuffer->enableFrameBuffer();

	renderer->initGuiMode();
}

void Engine::doneGUIMode()
{
	renderer->doneGuiMode();

	// unuse framebuffer if we have one
	if (frameBuffer != nullptr)
		FrameBuffer::disableFrameBuffer();
}

bool Engine::makeScreenshot(const string& pathName, const string& fileName)
{
	// use framebuffer if we have one
	if (frameBuffer != nullptr) frameBuffer->enableFrameBuffer();

	// fetch pixel
	auto pixels = renderer->readPixels(0, 0, width, height);
	if (pixels == nullptr) {
		Console::println("Engine::makeScreenshot(): Failed to read pixels");
		return false;
	}

	//
	{
		// see: https://gist.github.com/niw/5963798
		FILE *fp = fopen((pathName + "/" + fileName).c_str(), "wb");
		if (!fp) {
			Console::println("Engine::makeScreenshot(): Failed to create file: " + pathName + "/" + fileName);
			return false;
		}

		png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if (!png) {
			fclose(fp);
			return false;
		}

		png_infop info = png_create_info_struct(png);
		if (!info) {
			fclose(fp);
			return false;
		}

		if (setjmp(png_jmpbuf(png))) {
			fclose(fp);
			return false;
		}

		png_init_io(png, fp);

		// output is 8bit depth, RGBA format.
		png_set_IHDR(
			png,
			info,
			width,
			height,
			8,
			PNG_COLOR_TYPE_RGBA,
			PNG_INTERLACE_NONE,
			PNG_COMPRESSION_TYPE_DEFAULT,
			PNG_FILTER_TYPE_DEFAULT
		);
		png_write_info(png, info);

		// Remove the alpha channel for PNG_COLOR_TYPE_RGB format
		// png_set_filler(png, 0, PNG_FILLER_AFTER);

		png_bytep* row_pointers = new png_bytep[height];
		for (auto y = 0; y < height; y++) row_pointers[y] = pixels->getBuffer() + width * 4 * (height - 1 - y);

		png_write_image(png, row_pointers);
		png_write_end(png, NULL);

		free (row_pointers);

		fclose(fp);

		png_destroy_write_struct(&png, &info);
	}


	//
	delete pixels;

	// unuse framebuffer if we have one
	if (frameBuffer != nullptr) FrameBuffer::disableFrameBuffer();

	//
	return true;
}

void Engine::resetPostProcessingPrograms() {
	postProcessingPrograms.clear();
}

void Engine::addPostProcessingProgram(const string& programId) {
	if (postProcessing->getPostProcessingProgram(programId) != nullptr) postProcessingPrograms.push_back(programId);
}

void Engine::doPostProcessing(PostProcessingProgram::RenderPass renderPass, array<FrameBuffer*, 2> postProcessingFrameBuffers, FrameBuffer* targetFrameBuffer) {
	auto postProcessingFrameBufferIdx = 0;
	for (auto programId: postProcessingPrograms) {
		auto program = postProcessing->getPostProcessingProgram(programId);

		if (program == nullptr) continue;

		if (program->getRenderPass() != renderPass) continue;

		for (auto& step: program->getPostProcessingSteps()) {
			auto shaderId = step.shaderId;
			FrameBuffer* source = postProcessingFrameBuffers[postProcessingFrameBufferIdx];
			FrameBuffer* target = nullptr;
			switch(step.target) {
				case PostProcessingProgram::FRAMEBUFFERTARGET_SCREEN:
					target = postProcessingFrameBuffers[(postProcessingFrameBufferIdx + 1) % 2];
					break;
				case PostProcessingProgram::FRAMEBUFFERTARGET_TEMPORARY:
					isUsingPostProcessingTemporaryFrameBuffer = true;
					if (postProcessingTemporaryFrameBuffer == nullptr) {
						postProcessingTemporaryFrameBuffer = new FrameBuffer(width, height, FrameBuffer::FRAMEBUFFER_COLORBUFFER | FrameBuffer::FRAMEBUFFER_DEPTHBUFFER);
						postProcessingTemporaryFrameBuffer->initialize();
					}
					target = postProcessingTemporaryFrameBuffer;
					break;
			}
			FrameBuffer::doPostProcessing(target, source, shaderId, step.bindTemporary == true?postProcessingTemporaryFrameBuffer:nullptr);
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
		postProcessingFrameBuffers[postProcessingFrameBufferIdx]->renderToScreen();
	}
}
