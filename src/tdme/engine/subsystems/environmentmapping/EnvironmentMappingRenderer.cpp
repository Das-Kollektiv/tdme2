#include <tdme/engine/subsystems/environmentmapping/EnvironmentMappingRenderer.h>

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/subsystems/rendering/EntityRenderer.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/EntityHierarchy.h>
#include <tdme/engine/FrameBuffer.h>
#include <tdme/engine/GeometryBuffer.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/LODObject3D.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/Object3DRenderGroup.h>
#include <tdme/engine/ObjectParticleSystem.h>
#include <tdme/engine/ParticleSystemGroup.h>
#include <tdme/engine/Partition.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Time.h>

using std::vector;

using tdme::engine::subsystems::environmentmapping::EnvironmentMappingRenderer;

using tdme::engine::primitives::BoundingBox;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::rendering::EntityRenderer;
using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::EntityHierarchy;
using tdme::engine::FrameBuffer;
using tdme::engine::Light;
using tdme::engine::LODObject3D;
using tdme::engine::Object3D;
using tdme::engine::Object3DRenderGroup;
using tdme::engine::ObjectParticleSystem;
using tdme::engine::Partition;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utilities::Time;

GeometryBuffer* EnvironmentMappingRenderer::geometryBuffer = nullptr;

EnvironmentMappingRenderer::EnvironmentMappingRenderer(Engine* engine, int32_t width, int32_t height)
{
	this->engine = engine;
	this->width = width;
	this->height = height;
	camera = new Camera(engine->renderer);
	camera->setCameraMode(Camera::CAMERAMODE_NONE);
	if (engine->renderer->getRendererType() == Renderer::RENDERERTYPE_VULKAN) {
		forwardVectors = {{
			{{ 1.0f, 0.0f, 0.0f }}, // left
			{{ -1.0f, 0.0f, 0.0f }}, // right
			{{ 0.0f, -1.0f, 0.0f }}, // top
			{{ 0.0f, 1.0f, 0.0f }}, // bottom
			{{ 0.0f, 0.0f, 1.0f }}, // front
			{{ 0.0f, 0.0f, -1.0f }} // back
		}};
		sideVectors = {{
			{{ 0.0f, 0.0f, -1.0f }}, // left
			{{ 0.0f, 0.0f, 1.0f }}, // right
			{{ 1.0f, 0.0f, 0.0f }}, // top
			{{ 1.0f, 0.0f, 0.0f }}, // bottom
			{{ 1.0f, 0.0f, 0.0f }}, // front
			{{ -1.0f, 0.0f, 0.0f }} // back
		}};
	} else {
		forwardVectors = {{
			{{ -1.0f, 0.0f, 0.0f }}, // left
			{{ 1.0f, 0.0f, 0.0f }}, // right
			{{ 0.0f, 1.0f, 0.0f }}, // top
			{{ 0.0f, -1.0f, 0.0f }}, // bottom
			{{ 0.0f, 0.0f, 1.0f }}, // front
			{{ 0.0f, 0.0f, -1.0f }} // back
		}};
		sideVectors = {{
			{{ 0.0f, 0.0f, 1.0f }}, // left
			{{ 0.0f, 0.0f, -1.0f }}, // right
			{{ 1.0f, 0.0f, 0.0f }}, // top
			{{ 1.0f, 0.0f, 0.0f }}, // bottom
			{{ 1.0f, 0.0f, 0.0f }}, // front
			{{ -1.0f, 0.0f, 0.0f }} // back
		}};
	}
}

EnvironmentMappingRenderer::~EnvironmentMappingRenderer() {
	delete camera;
}

void EnvironmentMappingRenderer::initialize()
{
	//
	for (auto i = 0; i < frameBuffers.size(); i++) {
		cubeMapTextureIds[i] = engine->renderer->createCubeMapTexture(engine->renderer->CONTEXTINDEX_DEFAULT, width, height);
		for (auto j = 0; j < frameBuffers[i].size(); j++) {
			frameBuffers[i][j] = new FrameBuffer(width, height, FrameBuffer::FRAMEBUFFER_COLORBUFFER | FrameBuffer::FRAMEBUFFER_DEPTHBUFFER, cubeMapTextureIds[i], j + 1);
			frameBuffers[i][j]->initialize();
		}
	}
	// deferred shading
	if (engine->renderer->isDeferredShadingAvailable() == true && geometryBuffer == nullptr) {
		geometryBuffer = new GeometryBuffer(width, height);
		geometryBuffer->initialize();
	} else
	if (geometryBuffer != nullptr) {
		// TODO: fix me by using a hash map or something to match static geometry buffers with env maps of given dimension
		if (geometryBuffer->getWidth() != width || geometryBuffer->getHeight() != height) {
			Console::println("EnvironmentMappingRenderer::initialize(): " + to_string(geometryBuffer->getId()) + ": geometry buffer width != width, height != height!");
		}
	}
}

void EnvironmentMappingRenderer::reshape(int32_t width, int32_t height)
{
}

void EnvironmentMappingRenderer::dispose()
{
	for (auto i = 0; i < frameBuffers.size(); i++) {
		for (auto j = 0; j < frameBuffers[i].size(); j++) {
			frameBuffers[i][j]->dispose();
			delete frameBuffers[i][j];
		}
		engine->renderer->disposeTexture(cubeMapTextureIds[i]);
	}
}

void EnvironmentMappingRenderer::render(const Vector3& position)
{
	//
	auto now = Time::getCurrentMillis();
	if (timeRenderLast != -1LL && now - timeRenderLast < timeRenderUpdateFrequency) return;

	//
	auto engineCamera = engine->getCamera();

	//
	for (auto runs = 0; runs < (timeRenderLast == -1LL?2:1); runs++) {
		//
		reflectionCubeMapTextureIdx = renderCubeMapTextureIdx;
		renderCubeMapTextureIdx = (renderCubeMapTextureIdx + 1) % 2;

		//
		for (auto i = 0; i < frameBuffers[renderCubeMapTextureIdx].size(); i++) {
			// bind frame buffer
			frameBuffers[renderCubeMapTextureIdx][i]->enableFrameBuffer();

			// set up camera
			camera->setZNear(engineCamera->getZNear());
			camera->setZFar(engineCamera->getZFar());
			camera->setFovX(90.0f);
			camera->setLookFrom(position);
			camera->setForwardVector(forwardVectors[i]);
			camera->setSideVector(sideVectors[i]);
			camera->setUpVector(Vector3::computeCrossProduct(sideVectors[i], forwardVectors[i]));
			camera->update(engine->renderer->CONTEXTINDEX_DEFAULT, width, height);
			camera->getFrustum()->update();

			// set up clear color
			Engine::renderer->setClearColor(
				engine->sceneColor.getRed(),
				engine->sceneColor.getGreen(),
				engine->sceneColor.getBlue(),
				engine->sceneColor.getAlpha()
			);

			// clear previous frame values
			Engine::renderer->clear(engine->renderer->CLEAR_DEPTH_BUFFER_BIT | engine->renderer->CLEAR_COLOR_BUFFER_BIT);

			//
			engine->computeTransformations(camera, visibleDecomposedEntities, false, false);

			// do a render pass
			engine->render(
				frameBuffers[renderCubeMapTextureIdx][i],
				geometryBuffer,
				camera,
				visibleDecomposedEntities,
				Engine::EFFECTPASS_NONE,
				renderPassMask,
				string(),
				true,
				false,
				false,
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
					EntityRenderer::RENDERTYPE_LIGHTS
			);

			//
			engine->resetLists(visibleDecomposedEntities);
		}
	}

	// unbind frame buffer
	FrameBuffer::disableFrameBuffer();

	//
	timeRenderLast = now;
}
