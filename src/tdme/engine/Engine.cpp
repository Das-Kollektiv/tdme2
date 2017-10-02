#include <tdme/engine/Engine.h>

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
#include <tdme/engine/subsystems/object/Object3DBase_TransformedFacesIterator.h>
#include <tdme/engine/subsystems/object/Object3DVBORenderer.h>
#include <tdme/engine/subsystems/particlesystem/ParticleSystemEntity.h>
#include <tdme/engine/subsystems/particlesystem/ParticlesShader.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMapping.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderPre.h>
#include <tdme/engine/subsystems/shadowmapping/ShadowMappingShaderRender.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/renderer/GUIRenderer.h>
#include <tdme/gui/renderer/GUIShader.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/utils/ArrayListIteratorMultiple.h>
#include <tdme/utils/Float.h>
#include <tdme/utils/_Console.h>

using std::wstring;
using std::to_wstring;

using tdme::engine::Engine;
using tdme::utils::ByteBuffer;
using tdme::engine::Camera;
using tdme::engine::EngineGL3Renderer;
using tdme::engine::EngineGL2Renderer;
using tdme::engine::EngineGLES2Renderer;
using tdme::engine::Entity;
using tdme::engine::EntityPickingFilter;
using tdme::engine::FrameBuffer;
using tdme::engine::Light;
using tdme::engine::Object3D;
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
using tdme::engine::subsystems::object::Object3DBase_TransformedFacesIterator;
using tdme::engine::subsystems::object::Object3DVBORenderer;
using tdme::engine::subsystems::particlesystem::ParticleSystemEntity;
using tdme::engine::subsystems::particlesystem::ParticlesShader;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::engine::subsystems::shadowmapping::ShadowMapping;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPre;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRender;
using tdme::gui::GUI;
using tdme::gui::renderer::GUIRenderer;
using tdme::gui::renderer::GUIShader;
using tdme::math::Matrix4x4;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
using tdme::utils::Float;
using tdme::utils::_Console;

namespace
{
template<typename F>
struct finally_
{
    finally_(F f) : f(f), moved(false) { }
    finally_(finally_ &&x) : f(x.f), moved(false) { x.moved = true; }
    ~finally_() { if(!moved) f(); }
private:
    finally_(const finally_&); finally_& operator=(const finally_&);
    F f;
    bool moved;
};

template<typename F> finally_<F> finally(F f) { return finally_<F>(f); }
}

Engine::Engine() 
{
	width = 0;
	height = 0;
	timing = new Timing();
	camera = nullptr;
	sceneColor = new Color4(0.0f, 0.0f, 0.0f, 1.0f);
	frameBuffer = nullptr;
	shadowMappingEnabled = false;
	shadowMapping = nullptr;
	renderingInitiated = false;
	renderingComputedTransformations = false;
	initialized = false;
}

Engine* Engine::instance;

GLRenderer* Engine::renderer;

TextureManager* Engine::textureManager;

VBOManager* Engine::vboManager;

MeshManager* Engine::meshManager;

GUIRenderer* Engine::guiRenderer;

Engine::AnimationProcessingTarget Engine::animationProcessingTarget;

ShadowMappingShaderPre* Engine::shadowMappingShaderPre;

ShadowMappingShaderRender* Engine::shadowMappingShaderRender;

LightingShader* Engine::lightingShader;

ParticlesShader* Engine::particlesShader;

GUIShader* Engine::guiShader;

Engine* Engine::getInstance()
{
	clinit();
	if (instance == nullptr) {
		instance = new Engine();
	}
	return instance;
}

Engine* Engine::createOffScreenInstance(int32_t width, int32_t height)
{
	clinit();
	if (instance == nullptr || instance->initialized == false) {
		_Console::println(wstring(L"Engine::createOffScreenInstance(): Engine not created or not initialized."));
		return nullptr;
	}
	auto offScreenEngine = new Engine();
	offScreenEngine->initialized = true;
	offScreenEngine->gui = new GUI(offScreenEngine, guiRenderer);
	offScreenEngine->object3DVBORenderer = new Object3DVBORenderer(offScreenEngine, renderer);
	offScreenEngine->object3DVBORenderer->initialize();
	offScreenEngine->frameBuffer = new FrameBuffer(width, height, FrameBuffer::FRAMEBUFFER_DEPTHBUFFER | FrameBuffer::FRAMEBUFFER_COLORBUFFER);
	offScreenEngine->frameBuffer->initialize();
	offScreenEngine->camera = new Camera(renderer);
	offScreenEngine->partition = new PartitionOctTree();
	for (auto i = 0; i < offScreenEngine->lights.size(); i++)
		offScreenEngine->lights[i] = Light(renderer, i);

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
	clinit();
	return shadowMappingShaderPre;
}

ShadowMappingShaderRender* Engine::getShadowMappingShaderRender()
{
	clinit();
	return shadowMappingShaderRender;
}

LightingShader* Engine::getLightingShader()
{
	clinit();
	return lightingShader;
}

ParticlesShader* Engine::getParticlesShader()
{
	clinit();
	return particlesShader;
}

GUIShader* Engine::getGUIShader()
{
	clinit();
	return guiShader;
}

Object3DVBORenderer* Engine::getObject3DVBORenderer()
{
	return object3DVBORenderer;
}

Color4* Engine::getSceneColor()
{
	return sceneColor;
}

int32_t Engine::getEntityCount()
{
	return entitiesById.size();
}

Entity* Engine::getEntity(const wstring& id)
{
	auto entityByIdIt = entitiesById.find(id);
	if (entityByIdIt != entitiesById.end()) {
		return entityByIdIt->second;
	}
	return nullptr;
}

void Engine::addEntity(Entity* entity)
{
	auto oldEntity = getEntity(entity->getId());
	if (oldEntity != nullptr) {
		oldEntity->dispose();
		if (oldEntity->isEnabled() == true)
			partition->removeEntity(oldEntity);

	}

	entity->setEngine(this);
	entity->setRenderer(renderer);
	entity->initialize();
	entitiesById[entity->getId()] = entity;
	if (entity->isEnabled() == true) partition->addEntity(entity);
}

void Engine::removeEntity(const wstring& id)
{
	Entity* entity = nullptr;
	auto entityByIdIt = entitiesById.find(id);
	if (entityByIdIt != entitiesById.end()) {
		entity = entityByIdIt->second;
		entitiesById.erase(entityByIdIt);
	}

	if (entity != nullptr) {
		if (entity->isEnabled() == true)
			partition->removeEntity(entity);

		entity->dispose();
		entity->setEngine(nullptr);
		entity->setRenderer(nullptr);
	}
}

void Engine::reset()
{
	vector<wstring> entitiesToRemove;
	for (auto it: entitiesById) {
		auto entityKey = it.first;
		entitiesToRemove.push_back(entityKey);
	}
	for (auto entityKey: entitiesToRemove) {
		removeEntity(entityKey);
	}
	partition->reset();
	object3DVBORenderer->reset();
}

void Engine::initialize()
{
	initialize(false);
}

void Engine::initialize(bool debug)
{
	if (initialized == true)
		return;

	// GL3
	#ifdef __APPLE__
	{
		renderer = new EngineGL3Renderer(this);
		_Console::println(wstring(L"TDME::Using GL3"));
		// _Console::println(wstring(L"TDME::Extensions: ") + gl->glGetString(GL::GL_EXTENSIONS));
		shadowMappingEnabled = true;
		animationProcessingTarget = Engine::AnimationProcessingTarget::CPU;
		ShadowMapping::setShadowMapSize(2048, 2048);
	}
	#elif __linux__
	// GL2
	{
		renderer = new EngineGL2Renderer(this);
		_Console::println(wstring(L"TDME::Using GL2"));
		// _Console::println(wstring(L"TDME::Extensions: ") + gl->glGetString(GL::GL_EXTENSIONS));
		shadowMappingEnabled = true;
		animationProcessingTarget = Engine::AnimationProcessingTarget::CPU;
		ShadowMapping::setShadowMapSize(2048, 2048);
	}
	#endif
	/*
	// GLES2
	if (drawable->getGL()->isGLES2()) {
		auto gl = dynamic_cast< GLES2* >(drawable->getGL()->getGLES2());
		if (debug == true) {
			drawable->setGL(new DebugGLES2(gl));
		}
		renderer = new Engine_initialize_3(this);
		renderer->setGL(gl);
		_Console::println(static_cast< Object* >(u"TDME::Using GLES2"_j));
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"TDME::Extensions: "_j)->append(gl->glGetString(GL::GL_EXTENSIONS))->toString()));
		if (renderer->isBufferObjectsAvailable() == true && renderer->isDepthTextureAvailable() == true) {
			shadowMappingEnabled = true;
			animationProcessingTarget = Engine::AnimationProcessingTarget::CPU;
			ShadowMapping::setShadowMapSize(512, 512);
		} else {
			shadowMappingEnabled = false;
			animationProcessingTarget = Engine::AnimationProcessingTarget::CPU;
		}
	} else {
		_Console::println(static_cast< Object* >(u"Engine::initialize(): unsupported GL!"_j));
		return;
	}
	*/
	initialized = true;
	renderer->initialize();
	renderer->renderingTexturingClientState = false;
	textureManager = new TextureManager(renderer);
	vboManager = new VBOManager(renderer);
	meshManager = new MeshManager();
	object3DVBORenderer = new Object3DVBORenderer(this, renderer);
	object3DVBORenderer->initialize();
	guiRenderer = new GUIRenderer(renderer);
	guiRenderer->initialize();
	gui = new GUI(this, guiRenderer);
	gui->initialize();
	camera = new Camera(renderer);
	for (auto i = 0; i < lights.size(); i++) lights[i] = Light(renderer, i);
	partition = new PartitionOctTree();
	lightingShader = new LightingShader(renderer);
	lightingShader->initialize();
	particlesShader = new ParticlesShader(this, renderer);
	particlesShader->initialize();
	guiShader = new GUIShader(renderer);
	guiShader->initialize();
	if (renderer->isBufferObjectsAvailable()) {
		_Console::println(wstring(L"TDME::VBOs are available."));
	} else {
		_Console::println(wstring(L"TDME::VBOs are not available! Engine will not work!"));
		initialized = false;
	}
	if (true == false/*glContext->hasBasicFBOSupport() == false*/) {
		_Console::println(wstring(L"TDME::Basic FBOs are not available!"));
		shadowMappingEnabled = false;
	} else {
		_Console::println(wstring(L"TDME::Basic FBOs are available."));
	}
	if (shadowMappingEnabled == true) {
		_Console::println(wstring(L"TDME::Using shadow mapping"));
		shadowMappingShaderPre = new ShadowMappingShaderPre(renderer);
		shadowMappingShaderPre->initialize();
		shadowMappingShaderRender = new ShadowMappingShaderRender(renderer);
		shadowMappingShaderRender->initialize();
		shadowMapping = new ShadowMapping(this, renderer, object3DVBORenderer);
	} else {
		_Console::println(wstring(L"TDME::Not using shadow mapping"));
	}
	initialized &= shadowMappingShaderPre == nullptr ? true : shadowMappingShaderPre->isInitialized();
	initialized &= shadowMappingShaderRender == nullptr ? true : shadowMappingShaderRender->isInitialized();
	initialized &= lightingShader->isInitialized();
	initialized &= particlesShader->isInitialized();
	initialized &= guiShader->isInitialized();
	_Console::println(wstring(L"TDME::initialized & ready: ") + to_wstring(initialized));
}

void Engine::reshape(int32_t x, int32_t y, int32_t width, int32_t height)
{
	this->width = width;
	this->height = height;
	if (frameBuffer != nullptr) {
		frameBuffer->reshape(width, height);
	}
	if (shadowMapping != nullptr) {
		shadowMapping->reshape(width, height);
	}
	gui->reshape(width, height);
}

void Engine::initRendering()
{
	timing->updateTiming();
	camera->update(width, height);
	objects.clear();
	ppses.clear();
	visibleObjects.clear();
	visibleOpses.clear();
	visiblePpses.clear();
	renderingInitiated = true;
}

void Engine::computeTransformations()
{
	if (renderingInitiated == false) initRendering();

	for (auto it: entitiesById) {
		Entity* entity = it.second;
		if (entity->isEnabled() == false)
			continue;

		if (dynamic_cast< ParticleSystemEntity* >(entity) != nullptr) {
			auto pse = dynamic_cast< ParticleSystemEntity* >(entity);
			if (pse->isAutoEmit() == true) {
				pse->emitParticles();
				pse->updateParticles();
			}
		}
	}
	for (auto entity: *partition->getVisibleEntities(camera->getFrustum())) {
		if (dynamic_cast< Object3D* >(entity) != nullptr) {
			auto object = dynamic_cast< Object3D* >(entity);
			object->computeTransformations();
			visibleObjects.push_back(object);
		} else
		if (dynamic_cast< ObjectParticleSystemEntity* >(entity) != nullptr) {
			auto opse = dynamic_cast< ObjectParticleSystemEntity* >(entity);
			for (auto object3D: *opse->getEnabledObjects()) {
				visibleObjects.push_back(object3D);
			}
			visibleOpses.push_back(opse);
		} else
		if (dynamic_cast< PointsParticleSystemEntity* >(entity) != nullptr) {
			auto ppse = dynamic_cast< PointsParticleSystemEntity* >(entity);
			visiblePpses.push_back(ppse);
		}
	}
	renderingComputedTransformations = true;
}

void Engine::display()
{
	if (renderingInitiated == false) initRendering();

	if (renderingComputedTransformations == false) computeTransformations();

	Engine::renderer->initializeFrame();
	Engine::renderer->enableClientState(Engine::renderer->CLIENTSTATE_VERTEX_ARRAY);
	Engine::renderer->enableClientState(Engine::renderer->CLIENTSTATE_NORMAL_ARRAY);
	camera->update(width, height);
	if (shadowMapping != nullptr)
		shadowMapping->createShadowMaps(objects);

	if (frameBuffer != nullptr) {
		frameBuffer->enableFrameBuffer();
	} else {
		FrameBuffer::disableFrameBuffer();
	}
	camera->update(width, height);
	Engine::renderer->setClearColor(sceneColor->getRed(), sceneColor->getGreen(), sceneColor->getBlue(), sceneColor->getAlpha());
	renderer->clear(renderer->CLEAR_DEPTH_BUFFER_BIT | renderer->CLEAR_COLOR_BUFFER_BIT);
	renderer->setMaterialEnabled();
	if (lightingShader != nullptr) {
		lightingShader->useProgram();
	}
	for (auto j = 0; j < lights.size(); j++) {
		lights[j].update();
	}
	object3DVBORenderer->render(visibleObjects, true);
	if (lightingShader != nullptr) {
		lightingShader->unUseProgram();
	}
	if (shadowMapping != nullptr)
		shadowMapping->renderShadowMaps(visibleObjects);

	renderer->setMaterialDisabled();
	if (particlesShader != nullptr) {
		particlesShader->useProgram();
	}
	object3DVBORenderer->render(visiblePpses);
	if (particlesShader != nullptr) {
		particlesShader->unUseProgram();
	}
	Engine::renderer->disableClientState(Engine::renderer->CLIENTSTATE_VERTEX_ARRAY);
	Engine::renderer->disableClientState(Engine::renderer->CLIENTSTATE_NORMAL_ARRAY);
	Engine::renderer->disableClientState(Engine::renderer->CLIENTSTATE_TEXTURECOORD_ARRAY);
	renderingInitiated = false;
	renderingComputedTransformations = false;
	renderer->renderingTexturingClientState = false;
	modelViewMatrix.set(renderer->getModelViewMatrix());
	projectionMatrix.set(renderer->getProjectionMatrix());
	if (frameBuffer != nullptr)
		FrameBuffer::disableFrameBuffer();

}

void Engine::computeWorldCoordinateByMousePosition(int32_t mouseX, int32_t mouseY, float z, Vector3& worldCoordinate)
{
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
	if (frameBuffer != nullptr)
		frameBuffer->enableFrameBuffer();

	auto z = renderer->readPixelDepth(mouseX, height - mouseY);
	if (frameBuffer != nullptr)
		FrameBuffer::disableFrameBuffer();

	computeWorldCoordinateByMousePosition(mouseX, mouseY, z, worldCoordinate);
}

Entity* Engine::getObjectByMousePosition(int32_t mouseX, int32_t mouseY)
{
	return getObjectByMousePosition(mouseX, mouseY, nullptr);
}

Entity* Engine::getObjectByMousePosition(int32_t mouseX, int32_t mouseY, EntityPickingFilter* filter)
{
	Vector3 tmpVector3a;
	Vector3 tmpVector3b;
	Vector3 tmpVector3c;
	Vector3 tmpVector3d;
	Vector3 tmpVector3e;
	computeWorldCoordinateByMousePosition(mouseX, mouseY, 0.0f, tmpVector3a);
	computeWorldCoordinateByMousePosition(mouseX, mouseY, 1.0f, tmpVector3b);
	auto selectedEntityDistance = Float::MAX_VALUE;
	Entity* selectedEntity = nullptr;
	for (auto entity: visibleObjects) {
		if (entity->isPickable() == false)
			continue;

		if (filter != nullptr && filter->filterEntity(entity) == false)
			continue;

		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getBoundingBoxTransformed(), tmpVector3a, tmpVector3b, tmpVector3c, tmpVector3d) == true) {
			for (auto _i = entity->getTransformedFacesIterator()->iterator(); _i->hasNext(); ) {
				auto vertices = _i->next();
				{
					if (LineSegment::doesLineSegmentCollideWithTriangle((*vertices)[0], (*vertices)[1], (*vertices)[2], tmpVector3a, tmpVector3b, tmpVector3e) == true) {
						auto entityDistance = tmpVector3e.sub(tmpVector3a).computeLength();
						if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
							selectedEntity = entity;
							selectedEntityDistance = entityDistance;
						}
					}
				}
			}
		}
	}
	for (auto entity: visibleOpses) {
		if (entity->isPickable() == false)
			continue;

		if (filter != nullptr && filter->filterEntity(entity) == false)
			continue;

		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getBoundingBoxTransformed(), tmpVector3a, tmpVector3b, tmpVector3c, tmpVector3d) == true) {
			auto entityDistance = tmpVector3e.set(entity->getBoundingBoxTransformed()->getCenter()).sub(tmpVector3a).computeLength();
			if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
				selectedEntity = entity;
				selectedEntityDistance = entityDistance;
			}
		}
	}
	for (auto entity: visiblePpses) {
		if (entity->isPickable() == false)
			continue;

		if (filter != nullptr && filter->filterEntity(entity) == false)
			continue;

		if (LineSegment::doesBoundingBoxCollideWithLineSegment(entity->getBoundingBoxTransformed(), tmpVector3a, tmpVector3b, tmpVector3c, tmpVector3d) == true) {
			auto entityDistance = tmpVector3e.set(entity->getBoundingBoxTransformed()->getCenter()).sub(tmpVector3a).computeLength();
			if (selectedEntity == nullptr || entityDistance < selectedEntityDistance) {
				selectedEntity = entity;
				selectedEntityDistance = entityDistance;
			}
		}
	}
	return selectedEntity;
}

void Engine::computeScreenCoordinateByWorldCoordinate(const Vector3& worldCoordinate, Vector2& screenCoordinate)
{
	Matrix4x4 tmpMatrix4x4;
	Vector4 tmpVector4a;
	Vector4 tmpVector4b;
	tmpMatrix4x4.set(modelViewMatrix).multiply(projectionMatrix);
	tmpMatrix4x4.multiply(tmpVector4b.set(worldCoordinate, 1.0f), tmpVector4a);
	tmpVector4a.scale(1.0f / tmpVector4a.getW());
	auto screenCoordinateXYZW = tmpVector4a.getArray();
	screenCoordinate.setX((screenCoordinateXYZW[0] + 1.0f) * width / 2.0f);
	screenCoordinate.setY(height - ((screenCoordinateXYZW[1] + 1.0f) * height / 2.0f));
}

void Engine::dispose()
{
	vector<wstring> entitiesToRemove;
	for (auto it: entitiesById) {
		auto entityKey = it.first;
		entitiesToRemove.push_back(entityKey);
	}
	for (auto entityKey: entitiesToRemove) {
		removeEntity(entityKey);
	}
	if (shadowMapping != nullptr) {
		shadowMapping->dispose();
		shadowMapping = nullptr;
	}
	if (frameBuffer != nullptr) {
		frameBuffer->dispose();
		frameBuffer = nullptr;
	}
	gui->dispose();
	if (this == Engine::instance) {
		guiRenderer->dispose();
	}
}

void Engine::initGUIMode()
{
	if (frameBuffer != nullptr)
		frameBuffer->enableFrameBuffer();

	renderer->initGuiMode();
}

void Engine::doneGUIMode()
{
	renderer->doneGuiMode();
	if (frameBuffer != nullptr)
		FrameBuffer::disableFrameBuffer();

}

bool Engine::makeScreenshot(const wstring& pathName, const wstring& fileName)
{
	if (frameBuffer != nullptr)
		frameBuffer->enableFrameBuffer();

	auto pixels = renderer->readPixels(0, 0, width, height);
	if (pixels == nullptr)
		return false;

	// TODO: save to PNG

	if (frameBuffer != nullptr)
		FrameBuffer::disableFrameBuffer();

	return true;
}

void Engine::clinit()
{
	static bool in_cl_init = false;
	struct clinit_ {
		clinit_() {
			in_cl_init = true;
			instance = nullptr;
			textureManager = nullptr;
			vboManager = nullptr;
			meshManager = nullptr;
			guiRenderer = nullptr;
			animationProcessingTarget = Engine::AnimationProcessingTarget::CPU;
			shadowMappingShaderPre = nullptr;
			shadowMappingShaderRender = nullptr;
			lightingShader = nullptr;
			particlesShader = nullptr;
			guiShader = nullptr;
		}
	};

	if (!in_cl_init) {
		static clinit_ clinit_instance;
	}
}

