#include <tdme/engine/Engine.h>

#if ((defined(__linux__) || defined(__FreeBSD__) || defined(__NetBSD__)) && !defined(__arm__) && !defined(__aarch64__)) || defined(_WIN32) || defined(__HAIKU__)
	#define GLEW_NO_GLU
	#include <GL/glew.h>
#endif

#include <string>

#include <tdme/utils/ByteBuffer.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/EngineGL2Renderer.h>
#include <tdme/engine/EngineGL3Renderer.h>
#include <tdme/engine/EngineGLES2Renderer.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/EntityPickingFilter.h>
#include <tdme/engine/FrameBuffer.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/Object3DRenderGroup.h>
#include <tdme/engine/LODObject3D.h>
#include <tdme/engine/ObjectParticleSystemEntity.h>
#include <tdme/engine/Partition.h>
#include <tdme/engine/PartitionOctTree.h>
#include <tdme/engine/PointsParticleSystemEntity.h>
#include <tdme/engine/Timing.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/physics/CollisionDetection.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/LineSegment.h>
#include <tdme/engine/subsystems/lighting/LightingShader.h>
#include <tdme/engine/subsystems/manager/MeshManager.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/rendering/Object3DBase_TransformedFacesIterator.h>
#include <tdme/engine/subsystems/rendering/Object3DGroupMesh.h>
#include <tdme/engine/subsystems/rendering/Object3DVBORenderer.h>
#include <tdme/engine/subsystems/particlesystem/ParticleSystemEntity.h>
#include <tdme/engine/subsystems/particlesystem/ParticlesShader.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapping.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderPre.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderRender.h>
#include <tdme/engine/subsystems/skinning/SkinningShader.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/gui/renderer/GUIRenderer.h>
#include <tdme/gui/renderer/GUIShader.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utils/VectorIteratorMultiple.h>
#include <tdme/utils/Float.h>
#include <tdme/utils/Console.h>

using std::string;
using std::to_string;

using tdme::engine::Engine;
using tdme::utils::ByteBuffer;
using tdme::engine::Camera;
using tdme::engine::EngineGL3Renderer;
using tdme::engine::EngineGL2Renderer;
using tdme::engine::EngineGLES2Renderer;
using tdme::engine::Entity;
using tdme::engine::EntityPickingFilter;
using tdme::engine::Object3DRenderGroup;
using tdme::engine::FrameBuffer;
using tdme::engine::Light;
using tdme::engine::Object3D;
using tdme::engine::LODObject3D;
using tdme::engine::ObjectParticleSystemEntity;
using tdme::engine::Partition;
using tdme::engine::PartitionOctTree;
using tdme::engine::PointsParticleSystemEntity;
using tdme::engine::Timing;
using tdme::engine::model::Color4;
using tdme::engine::physics::CollisionDetection;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::LineSegment;
using tdme::engine::subsystems::lighting::LightingShader;
using tdme::engine::subsystems::manager::MeshManager;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::rendering::Object3DBase_TransformedFacesIterator;
using tdme::engine::subsystems::rendering::Object3DVBORenderer;
using tdme::engine::subsystems::particlesystem::ParticleSystemEntity;
using tdme::engine::subsystems::particlesystem::ParticlesShader;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::engine::subsystems::shadowmapping::ShadowMapping;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPre;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRender;
using tdme::engine::subsystems::skinning::SkinningShader;
using tdme::gui::GUI;
using tdme::gui::GUIParser;
using tdme::gui::renderer::GUIRenderer;
using tdme::gui::renderer::GUIShader;
using tdme::math::Matrix4x4;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utils::Float;
using tdme::utils::Console;

Engine* Engine::instance = nullptr;
GLRenderer* Engine::renderer = nullptr;
TextureManager* Engine::textureManager = nullptr;
VBOManager* Engine::vboManager = nullptr;
MeshManager* Engine::meshManager = nullptr;
GUIRenderer* Engine::guiRenderer = nullptr;
Engine::AnimationProcessingTarget Engine::animationProcessingTarget = Engine::AnimationProcessingTarget::CPU;
ShadowMappingShaderPre* Engine::shadowMappingShaderPre = nullptr;
ShadowMappingShaderRender* Engine::shadowMappingShaderRender = nullptr;
LightingShader* Engine::lightingShader = nullptr;
ParticlesShader* Engine::particlesShader = nullptr;
SkinningShader* Engine::skinningShader = nullptr;
GUIShader* Engine::guiShader = nullptr;
Engine* Engine::currentEngine = nullptr;

Engine::Engine() 
{
	width = 0;
	height = 0;
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
}

Engine::~Engine() {
	delete timing;
	delete camera;
	delete gui;
	delete frameBuffer;
	delete partition;
	if (shadowMappingEnabled == true) {
		delete shadowMapping;
	}
	delete object3DVBORenderer;
	if (instance == this) {
		delete renderer;
		delete textureManager;
		delete vboManager;
		delete meshManager;
		delete guiRenderer;
		delete lightingShader;
		delete particlesShader;
		delete guiShader;
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
	offScreenEngine->object3DVBORenderer = new Object3DVBORenderer(offScreenEngine, renderer);
	offScreenEngine->object3DVBORenderer->initialize();
	// create framebuffer
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
		offScreenEngine->shadowMapping = new ShadowMapping(offScreenEngine, renderer, offScreenEngine->object3DVBORenderer);
	}
	offScreenEngine->reshape(0, 0, width, height);
	return offScreenEngine;
}

bool Engine::isInitialized()
{
	return initialized;
}

int32_t Engine::getWidth()
{
	return width;
}

int32_t Engine::getHeight()
{
	return height;
}

ShadowMapping* Engine::getShadowMapping()
{
	return shadowMapping;
}

GUI* Engine::getGUI()
{
	return gui;
}

Timing* Engine::getTiming()
{
	return timing;
}

Camera* Engine::getCamera()
{
	return camera;
}

Partition* Engine::getPartition()
{
	return partition;
}

void Engine::setPartition(Partition* partition)
{
	if (this->partition != nullptr) delete this->partition;
	this->partition = partition;
}

FrameBuffer* Engine::getFrameBuffer()
{
	return frameBuffer;
}

int32_t Engine::getLightCount() {
	return lights.size();
}

Light* Engine::getLightAt(int32_t idx)
{
	return &lights[idx];
}

TextureManager* Engine::getTextureManager()
{
	return textureManager;
}

VBOManager* Engine::getVBOManager()
{
	return vboManager;
}

MeshManager* Engine::getMeshManager()
{
	return meshManager;
}

ShadowMappingShaderPre* Engine::getShadowMappingShaderPre()
{
	return shadowMappingShaderPre;
}

ShadowMappingShaderRender* Engine::getShadowMappingShaderRender()
{
	return shadowMappingShaderRender;
}

LightingShader* Engine::getLightingShader()
{
	return lightingShader;
}

ParticlesShader* Engine::getParticlesShader()
{
	return particlesShader;
}

SkinningShader* Engine::getSkinningShader() {
	return skinningShader;
}

GUIShader* Engine::getGUIShader()
{
	return guiShader;
}

Object3DVBORenderer* Engine::getObject3DVBORenderer()
{
	return object3DVBORenderer;
}

Color4& Engine::getSceneColor()
{
	return sceneColor;
}

int32_t Engine::getEntityCount()
{
	return entitiesById.size();
}

Entity* Engine::getEntity(const string& id)
{
	auto entityByIdIt = entitiesById.find(id);
	if (entityByIdIt != entitiesById.end()) {
		return entityByIdIt->second;
	}
	return nullptr;
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
	updateEntity(entity);
}

void Engine::updateEntity(Entity* entity) {
	noFrustumCullingEntities.erase(entity->getId());
	autoEmitParticleSystemEntities.erase(entity->getId());

	// add to no frustum culling
	if (entity->isFrustumCulling() == false) {
		// otherwise add to no frustum culling entities
		noFrustumCullingEntities[entity->getId()] = entity;
	}

	// add to auto emit particle system entities
	auto particleSystemEntity = dynamic_cast<ParticleSystemEntity*>(entity);
	if (particleSystemEntity != nullptr && particleSystemEntity->isAutoEmit() == true) {
		autoEmitParticleSystemEntities[particleSystemEntity->getId()] = particleSystemEntity;
	}
}

void Engine::removeEntity(const string& id)
{
	// get entity and remove if we have any
	Entity* entity = nullptr;
	auto entityByIdIt = entitiesById.find(id);
	if (entityByIdIt != entitiesById.end()) {
		entity = entityByIdIt->second;
		entitiesById.erase(entityByIdIt);
		autoEmitParticleSystemEntities.erase(entity->getId());
		noFrustumCullingEntities.erase(entity->getId());
	}
	if (entity != nullptr) {
		// remove from partition if enabled and frustum culling requested
		if (entity->isFrustumCulling() == true && entity->isEnabled() == true) partition->removeEntity(entity);
		// dispose entity
		entity->dispose();
		entity->setEngine(nullptr);
		entity->setRenderer(nullptr);
		delete entity;
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
	object3DVBORenderer->reset();
	if (skinningShaderEnabled == true) skinningShader->reset();
}

void Engine::initialize()
{
	initialize(false);
}

void Engine::initialize(bool debug)
{
	// set current engine
	currentEngine = this;

	// exit if already initialized like a offscreen engine instance
	if (initialized == true)
		return;

	// MacOSX, currently GL3 only
	#if defined(__APPLE__)
	{
		renderer = new EngineGL3Renderer(this);
		Console::println(string("TDME::Using GL3+/CORE"));
		// Console::println(string("TDME::Extensions: ") + gl->glGetString(GL::GL_EXTENSIONS));
		shadowMappingEnabled = true;
		ShadowMapping::setShadowMapSize(2048, 2048);
		skinningShaderEnabled = false;
		animationProcessingTarget = Engine::AnimationProcessingTarget::CPU;
	}
	// Linux/FreeBSD/NetBSD/Win32, GL2 or GL3 via GLEW
	#elif defined(_WIN32) || ((defined(__FreeBSD__) || defined(__NetBSD__) || defined(__linux__)) && !defined(__arm__) && !defined(__aarch64__)) || defined(__HAIKU__)
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
		ShadowMapping::setShadowMapSize(2048, 2048);
		animationProcessingTarget = skinningShaderEnabled == true?Engine::AnimationProcessingTarget::GPU:Engine::AnimationProcessingTarget::CPU;
	}
	// GLES2 on Linux
	#elif (defined(__linux__) || defined(__FreeBSD__) || defined(__NetBSD__)) && (defined(__arm__) || defined(__aarch64__))
	{
		renderer = new EngineGLES2Renderer(this);
		Console::println(string("TDME::Using GLES2"));
		// Console::println(string("TDME::Extensions: ") + gl->glGetString(GL::GL_EXTENSIONS));
		if (renderer->isBufferObjectsAvailable() == true && renderer->isDepthTextureAvailable() == true) {
			shadowMappingEnabled = true;
			animationProcessingTarget = Engine::AnimationProcessingTarget::CPU;
			ShadowMapping::setShadowMapSize(512, 512);
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

	// init
	initialized = true;
	renderer->initialize();

	// create manager
	textureManager = new TextureManager(renderer);
	vboManager = new VBOManager(renderer);
	meshManager = new MeshManager();

	// create object 3d vbo renderer
	object3DVBORenderer = new Object3DVBORenderer(this, renderer);
	object3DVBORenderer->initialize();
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

	// create gui shader
	guiShader = new GUIShader(renderer);
	guiShader->initialize();

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

	// initialize shadow mapping
	if (shadowMappingEnabled == true) {
		Console::println(string("TDME::Using shadow mapping"));
		shadowMappingShaderPre = new ShadowMappingShaderPre(renderer);
		shadowMappingShaderPre->initialize();
		shadowMappingShaderRender = new ShadowMappingShaderRender(renderer);
		shadowMappingShaderRender->initialize();
		shadowMapping = new ShadowMapping(this, renderer, object3DVBORenderer);
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

	// check if initialized
	initialized &= shadowMappingShaderPre == nullptr ? true : shadowMappingShaderPre->isInitialized();
	initialized &= shadowMappingShaderRender == nullptr ? true : shadowMappingShaderRender->isInitialized();
	initialized &= lightingShader->isInitialized();
	initialized &= particlesShader->isInitialized();
	initialized &= guiShader->isInitialized();

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
	if (frameBuffer != nullptr) {
		frameBuffer->reshape(width, height);
	}

	// update shadow mapping
	if (shadowMapping != nullptr) {
		shadowMapping->reshape(width, height);
	}

	// update GUI system
	gui->reshape(width, height);
}

void Engine::initRendering()
{
	// update timing
	timing->updateTiming();

	// update camera
	camera->update(width, height);

	// clear lists of visible objects
	visibleObjects.clear();
	visibleLODObjects.clear();
	visibleOpses.clear();
	visiblePpses.clear();
	visibleObjectRenderGroups.clear();

	//
	renderingInitiated = true;
}

void Engine::computeTransformations()
{
	// init rendering if not yet done
	if (renderingInitiated == false) initRendering();

	Object3D* object = nullptr;
	LODObject3D* lodObject = nullptr;
	ObjectParticleSystemEntity* opse = nullptr;
	PointsParticleSystemEntity* ppse = nullptr;
	ParticleSystemEntity* pse = nullptr;
	Object3DRenderGroup* org = nullptr;

	#define COMPUTE_ENTITY_TRANSFORMATIONS(_entity) \
	{ \
		if ((object = dynamic_cast< Object3D* >(_entity)) != nullptr) { \
			object->preRender(); \
			object->computeTransformations(); \
			visibleObjects.push_back(object); \
		} else \
		if ((lodObject = dynamic_cast< LODObject3D* >(_entity)) != nullptr) { \
			auto object = lodObject->determineLODObject(camera); \
			if (object != nullptr) { \
				visibleLODObjects.push_back(lodObject); \
				visibleObjects.push_back(object); \
				object->preRender(); \
				object->computeTransformations(); \
			} \
		} else \
		if ((opse = dynamic_cast< ObjectParticleSystemEntity* >(_entity)) != nullptr) { \
			for (auto object: *opse->getEnabledObjects()) { \
				object->preRender(); \
				object->computeTransformations(); \
				visibleObjects.push_back(object); \
			} \
			visibleOpses.push_back(opse); \
		} else \
		if ((ppse = dynamic_cast< PointsParticleSystemEntity* >(_entity)) != nullptr) { \
			visiblePpses.push_back(ppse); \
		} \
	}

	// collect entities that do not have frustum culling enabled
	for (auto it: noFrustumCullingEntities) {
		auto entity = it.second;

		// skip on disabled entities
		if (entity->isEnabled() == false) continue;

		// compute transformations and add to lists
		if ((org = dynamic_cast< Object3DRenderGroup* >(entity)) != nullptr) {
			if ((object = org->getObject()) != nullptr) COMPUTE_ENTITY_TRANSFORMATIONS(object);
		} else {
			COMPUTE_ENTITY_TRANSFORMATIONS(entity);
		}
	}

	// do particle systems auto emit
	for (auto it: autoEmitParticleSystemEntities) {
		auto entity = it.second;

		// skip on disabled entities
		if (entity->isEnabled() == false) continue;

		// do auto emit
		if ((pse = dynamic_cast< ParticleSystemEntity* >(entity)) != nullptr) {
			pse->emitParticles();
			pse->updateParticles();
		}
	}

	// add visible entities to related lists by querying frustum
	for (auto entity: *partition->getVisibleEntities(camera->getFrustum())) {
		// compute transformations and add to lists
		if ((org = dynamic_cast< Object3DRenderGroup* >(entity)) != nullptr) {
			visibleObjectRenderGroups.push_back(org);
			if ((object = org->getObject()) != nullptr) COMPUTE_ENTITY_TRANSFORMATIONS(object);
		} else {
			COMPUTE_ENTITY_TRANSFORMATIONS(entity);
		}
	}

	// TODO: improve met
	if (skinningShaderEnabled == true) {
		skinningShader->unUseProgram();
	}

	//
	renderingComputedTransformations = true;
}

void Engine::display()
{
	// set current engine
	currentEngine = this;

	// do pre rendering steps
	if (renderingInitiated == false) initRendering();
	if (renderingComputedTransformations == false) computeTransformations();

	// init frame
	Engine::renderer->initializeFrame();

	// update camera
	camera->update(width, height);

	// create shadow maps
	if (shadowMapping != nullptr)
		shadowMapping->createShadowMaps();

	// switch back to framebuffer if we have one
	if (frameBuffer != nullptr) {
		frameBuffer->enableFrameBuffer();
	} else {
		FrameBuffer::disableFrameBuffer();
	}

	// restore camera from shadow map rendering
	camera->update(width, height);

	// set up clear color
	Engine::renderer->setClearColor(sceneColor.getRed(), sceneColor.getGreen(), sceneColor.getBlue(), sceneColor.getAlpha());

	// clear previous frame values
	renderer->clear(renderer->CLEAR_DEPTH_BUFFER_BIT | renderer->CLEAR_COLOR_BUFFER_BIT);

	// enable materials
	renderer->setMaterialEnabled();

	// use lighting shader
	if (lightingShader != nullptr) {
		lightingShader->useProgram();
	}

	// render objects
	object3DVBORenderer->render(
		visibleObjects,
		true,
		Object3DVBORenderer::RENDERTYPE_NORMALS |
		Object3DVBORenderer::RENDERTYPE_TEXTUREARRAYS |
		Object3DVBORenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY |
		Object3DVBORenderer::RENDERTYPE_EFFECTCOLORS |
		Object3DVBORenderer::RENDERTYPE_MATERIALS |
		Object3DVBORenderer::RENDERTYPE_MATERIALS_DIFFUSEMASKEDTRANSPARENCY |
		Object3DVBORenderer::RENDERTYPE_TEXTURES |
		Object3DVBORenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY |
		Object3DVBORenderer::RENDERTYPE_LIGHTS
	);

	// unuse lighting shader
	if (lightingShader != nullptr) {
		lightingShader->unUseProgram();
	}

	// render shadows if required
	if (shadowMapping != nullptr)
		shadowMapping->renderShadowMaps(visibleObjects);

	// disable materials
	renderer->setMaterialDisabled();

	// use particle shader
	if (particlesShader != nullptr) {
		particlesShader->useProgram();
	}

	// render points based particle systems
	object3DVBORenderer->render(visiblePpses);

	// unuse particle shader
	if (particlesShader != nullptr) {
		particlesShader->unUseProgram();
	}

	// clear pre render states
	renderingInitiated = false;
	renderingComputedTransformations = false;

	// store matrices
	modelViewMatrix.set(renderer->getModelViewMatrix());
	projectionMatrix.set(renderer->getProjectionMatrix());

	// unuse framebuffer if we have one
	if (frameBuffer != nullptr)
		FrameBuffer::disableFrameBuffer();
}

void Engine::computeWorldCoordinateByMousePosition(int32_t mouseX, int32_t mouseY, float z, Vector3& worldCoordinate)
{
	// http://stackoverflow.com/questions/7692988/opengl-math-projecting-screen-space-to-world-space-coords-solved
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

	// http://stackoverflow.com/questions/7692988/opengl-math-projecting-screen-space-to-world-space-coords-solved
	auto z = renderer->readPixelDepth(mouseX, height - mouseY);

	// unuse framebuffer if we have one
	if (frameBuffer != nullptr)
		FrameBuffer::disableFrameBuffer();

	//
	computeWorldCoordinateByMousePosition(mouseX, mouseY, z, worldCoordinate);
}

Entity* Engine::getEntityByMousePosition(int32_t mouseX, int32_t mouseY)
{
	return getEntityByMousePosition(mouseX, mouseY, nullptr);
}

Entity* Engine::getEntityByMousePosition(int32_t mouseX, int32_t mouseY, EntityPickingFilter* filter)
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

	// iterate visible objects, check if ray with given mouse position from near plane to far plane collides with each object's triangles
	for (auto entity: visibleObjects) {
		// skip if not pickable or ignored by filter
		if (entity->isPickable() == false) continue;
		if (filter != nullptr && filter->filterEntity(entity) == false) continue;
		// do the collision test
		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getBoundingBoxTransformed(), tmpVector3a, tmpVector3b, tmpVector3c, tmpVector3d) == true) {
			for (auto _i = entity->getTransformedFacesIterator()->iterator(); _i->hasNext(); ) {
				auto vertices = _i->next();
				{
					if (LineSegment::doesLineSegmentCollideWithTriangle((*vertices)[0], (*vertices)[1], (*vertices)[2], tmpVector3a, tmpVector3b, tmpVector3e) == true) {
						auto entityDistance = tmpVector3e.sub(tmpVector3a).computeLength();
						// check if match or better match
						if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
							selectedEntity = entity;
							selectedEntityDistance = entityDistance;
						}
					}
				}
			}
		}
	}

	// iterate visible LOD objects, check if ray with given mouse position from near plane to far plane collides with each object's triangles
	for (auto entity: visibleLODObjects) {
		// skip if not pickable or ignored by filter
		if (entity->isPickable() == false) continue;
		if (filter != nullptr && filter->filterEntity(entity) == false) continue;
		// do the collision test
		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getBoundingBoxTransformed(), tmpVector3a, tmpVector3b, tmpVector3c, tmpVector3d) == true) {
			auto object = entity->getLODObject();
			if (object != nullptr) {
				for (auto _i = object->getTransformedFacesIterator()->iterator(); _i->hasNext(); ) {
					auto vertices = _i->next();
					{
						if (LineSegment::doesLineSegmentCollideWithTriangle((*vertices)[0], (*vertices)[1], (*vertices)[2], tmpVector3a, tmpVector3b, tmpVector3e) == true) {
							auto entityDistance = tmpVector3e.sub(tmpVector3a).computeLength();
							// check if match or better match
							if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
								selectedEntity = entity;
								selectedEntityDistance = entityDistance;
							}
						}
					}
				}
			}
		}
	}

	// iterate visible object partition systems, check if ray with given mouse position from near plane to far plane collides with bounding volume
	for (auto entity: visibleOpses) {
		// skip if not pickable or ignored by filter
		if (entity->isPickable() == false) continue;
		if (filter != nullptr && filter->filterEntity(entity) == false) continue;
		// do the collision test
		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getBoundingBoxTransformed(), tmpVector3a, tmpVector3b, tmpVector3c, tmpVector3d) == true) {
			auto entityDistance = tmpVector3e.set(entity->getBoundingBoxTransformed()->getCenter()).sub(tmpVector3a).computeLength();
			// check if match or better match
			if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
				selectedEntity = entity;
				selectedEntityDistance = entityDistance;
			}
		}
	}
	// iterate visible point partition systems, check if ray with given mouse position from near plane to far plane collides with bounding volume
	for (auto entity: visiblePpses) {
		// skip if not pickable or ignored by filter
		if (entity->isPickable() == false) continue;
		if (filter != nullptr && filter->filterEntity(entity) == false) continue;
		// do the collision test
		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getBoundingBoxTransformed(), tmpVector3a, tmpVector3b, tmpVector3c, tmpVector3d) == true) {
			auto entityDistance = tmpVector3e.set(entity->getBoundingBoxTransformed()->getCenter()).sub(tmpVector3a).computeLength();
			// check if match or better match
			if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
				selectedEntity = entity;
				selectedEntityDistance = entityDistance;
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
	if (shadowMapping != nullptr) {
		shadowMapping->dispose();
		shadowMapping = nullptr;
	}

	// dispose frame buffer
	if (frameBuffer != nullptr) {
		frameBuffer->dispose();
		frameBuffer = nullptr;
	}

	// dispose GUI
	gui->dispose();
	if (this == Engine::instance) {
		guiRenderer->dispose();
	}

	// dispose object 3d VBO renderer
	object3DVBORenderer->dispose();
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
	if (frameBuffer != nullptr)
		frameBuffer->enableFrameBuffer();

	// fetch pixel, TODO: implement me
	auto pixels = renderer->readPixels(0, 0, width, height);
	if (pixels == nullptr)
		return false;

	// TODO: save to PNG

	// unuse framebuffer if we have one
	if (frameBuffer != nullptr)
		FrameBuffer::disableFrameBuffer();

	//
	return true;
}
