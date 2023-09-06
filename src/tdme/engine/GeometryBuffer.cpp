#include <tdme/engine/GeometryBuffer.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/framebuffer/DeferredLightingRenderShader.h>
#include <tdme/engine/subsystems/framebuffer/FrameBufferRenderShader.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShader.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/Decal.h>
#include <tdme/engine/Engine.h>
#include <tdme/math/Math.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Float.h>

using tdme::engine::GeometryBuffer;

using std::string;
using std::to_string;

using tdme::engine::subsystems::framebuffer::DeferredLightingRenderShader;
using tdme::engine::subsystems::framebuffer::FrameBufferRenderShader;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Decal;
using tdme::engine::Engine;
using tdme::math::Math;
using tdme::utilities::Console;
using tdme::utilities::Float;

GeometryBuffer::GeometryBuffer(int32_t width, int32_t height)
{
	this->width = width;
	this->height = height;
	this->frameBufferId = -1;
	this->depthBufferTextureId = Engine::getRenderer()->ID_NONE;
	this->geometryBufferTextureId1 = Engine::getRenderer()->ID_NONE;
	this->geometryBufferTextureId2 = Engine::getRenderer()->ID_NONE;
	this->geometryBufferTextureId3 = Engine::getRenderer()->ID_NONE;
	this->colorBufferTextureId1 = Engine::getRenderer()->ID_NONE;
	this->colorBufferTextureId2 = Engine::getRenderer()->ID_NONE;
	this->colorBufferTextureId3 = Engine::getRenderer()->ID_NONE;
	this->colorBufferTextureId4 = Engine::getRenderer()->ID_NONE;
	this->colorBufferTextureId5 = Engine::getRenderer()->ID_NONE;
}

void GeometryBuffer::initialize()
{
	depthBufferTextureId = Engine::getRenderer()->createDepthBufferTexture(width, height, 0, 0);
	geometryBufferTextureId1 = Engine::getRenderer()->createGBufferGeometryTexture(width, height);
	geometryBufferTextureId2 = Engine::getRenderer()->createGBufferGeometryTexture(width, height);
	geometryBufferTextureId3 = Engine::getRenderer()->createGBufferGeometryTexture(width, height);
	colorBufferTextureId1 = Engine::getRenderer()->createGBufferColorTexture(width, height);
	colorBufferTextureId2 = Engine::getRenderer()->createGBufferColorTexture(width, height);
	colorBufferTextureId3 = Engine::getRenderer()->createGBufferColorTexture(width, height);
	colorBufferTextureId4 = Engine::getRenderer()->createGBufferColorTexture(width, height);
	colorBufferTextureId5 = Engine::getRenderer()->createGBufferColorTexture(width, height);
	frameBufferId = Engine::getRenderer()->createGeometryBufferObject(
		depthBufferTextureId,
		geometryBufferTextureId1,
		geometryBufferTextureId2,
		geometryBufferTextureId3,
		colorBufferTextureId1,
		colorBufferTextureId2,
		colorBufferTextureId3,
		colorBufferTextureId4,
		colorBufferTextureId5
	);
}

void GeometryBuffer::reshape(int32_t width, int32_t height)
{
	this->width = width;
	this->height = height;
	Engine::getRenderer()->resizeDepthBufferTexture(depthBufferTextureId, width, height);
	Engine::getRenderer()->resizeGBufferGeometryTexture(geometryBufferTextureId1, width, height);
	Engine::getRenderer()->resizeGBufferGeometryTexture(geometryBufferTextureId2, width, height);
	Engine::getRenderer()->resizeGBufferGeometryTexture(geometryBufferTextureId3, width, height);
	Engine::getRenderer()->resizeGBufferColorTexture(colorBufferTextureId1, width, height);
	Engine::getRenderer()->resizeGBufferColorTexture(colorBufferTextureId2, width, height);
	Engine::getRenderer()->resizeGBufferColorTexture(colorBufferTextureId3, width, height);
	Engine::getRenderer()->resizeGBufferColorTexture(colorBufferTextureId4, width, height);
	Engine::getRenderer()->resizeGBufferColorTexture(colorBufferTextureId5, width, height);
}

void GeometryBuffer::dispose()
{
	Engine::getRenderer()->disposeTexture(depthBufferTextureId);
	Engine::getRenderer()->disposeTexture(geometryBufferTextureId1);
	Engine::getRenderer()->disposeTexture(geometryBufferTextureId2);
	Engine::getRenderer()->disposeTexture(geometryBufferTextureId3);
	Engine::getRenderer()->disposeTexture(colorBufferTextureId1);
	Engine::getRenderer()->disposeTexture(colorBufferTextureId2);
	Engine::getRenderer()->disposeTexture(colorBufferTextureId3);
	Engine::getRenderer()->disposeTexture(colorBufferTextureId4);
	Engine::getRenderer()->disposeTexture(colorBufferTextureId5);
	// TODO: Vulkan might need a extra method here
	Engine::getRenderer()->disposeFrameBufferObject(frameBufferId);
}

void GeometryBuffer::enableGeometryBuffer()
{
	Engine::getRenderer()->bindFrameBuffer(frameBufferId);
	Engine::getRenderer()->setViewPort(width, height);
	Engine::getRenderer()->updateViewPort();
}

void GeometryBuffer::disableGeometryBuffer()
{
	Engine::getRenderer()->bindFrameBuffer(Engine::getRenderer()->FRAMEBUFFER_DEFAULT);
	Engine::getRenderer()->setViewPort(Engine::instance->width, Engine::instance->height);
	Engine::getRenderer()->updateViewPort();
}

void GeometryBuffer::renderToScreen(Engine* engine, vector<Decal*>& decalEntities)
{
	auto renderer = Engine::getRenderer();

	// use default context
	auto contextIdx = renderer->CONTEXTINDEX_DEFAULT;

	//
	renderer->disableCulling(contextIdx);

	// clear
	renderer->setClearColor(engine->sceneColor.getRed(), engine->sceneColor.getGreen(), engine->sceneColor.getBlue(), engine->sceneColor.getAlpha());
	renderer->clear(renderer->CLEAR_COLOR_BUFFER_BIT | renderer->CLEAR_DEPTH_BUFFER_BIT);

	// use deferred lighting render shader
	auto frameBufferRenderShader = Engine::getFrameBufferRenderShader();
	auto deferredLightingRenderShader = Engine::getDeferredLightingRenderShader();
	deferredLightingRenderShader->useProgram(engine, decalEntities);

	// bind geometry buffer textures
	renderer->setTextureUnit(contextIdx, 0);
	renderer->bindTexture(contextIdx, geometryBufferTextureId1);
	renderer->setTextureUnit(contextIdx, 1);
	renderer->bindTexture(contextIdx, geometryBufferTextureId2);
	renderer->setTextureUnit(contextIdx, 2);
	renderer->bindTexture(contextIdx, geometryBufferTextureId3);

	// bind color buffer textures
	renderer->setTextureUnit(contextIdx, 3);
	renderer->bindTexture(contextIdx, colorBufferTextureId1);
	renderer->setTextureUnit(contextIdx, 4);
	renderer->bindTexture(contextIdx, colorBufferTextureId2);
	renderer->setTextureUnit(contextIdx, 5);
	renderer->bindTexture(contextIdx, colorBufferTextureId3);
	renderer->setTextureUnit(contextIdx, 6);
	renderer->bindTexture(contextIdx, colorBufferTextureId4);
	renderer->setTextureUnit(contextIdx, 7);
	renderer->bindTexture(contextIdx, colorBufferTextureId5);

	// bind depth buffer texture
	renderer->setTextureUnit(contextIdx, 8);
	renderer->bindTexture(contextIdx, depthBufferTextureId);

	//
	renderer->bindVerticesBufferObject(contextIdx, frameBufferRenderShader->getVBOVertices());
	renderer->bindTextureCoordinatesBufferObject(contextIdx, frameBufferRenderShader->getVBOTextureCoordinates());

	// draw
	renderer->drawTrianglesFromBufferObjects(contextIdx, 2, 0);

	// unbind buffers
	renderer->unbindBufferObjects(contextIdx);

	// unbind geometry buffer textures
	renderer->setTextureUnit(contextIdx, 0);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);
	renderer->setTextureUnit(contextIdx, 1);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);
	renderer->setTextureUnit(contextIdx, 2);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);

	// unbind color buffer textures
	renderer->setTextureUnit(contextIdx, 3);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);
	renderer->setTextureUnit(contextIdx, 4);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);
	renderer->setTextureUnit(contextIdx, 5);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);
	renderer->setTextureUnit(contextIdx, 6);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);
	renderer->setTextureUnit(contextIdx, 7);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);

	// unbind depth buffer texture
	renderer->setTextureUnit(contextIdx, 8);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);

	// switch back to diffuse texture unit
	renderer->setTextureUnit(contextIdx, 0);

	//
	deferredLightingRenderShader->unUseProgram();

	// unset
	renderer->enableCulling(contextIdx);
}

