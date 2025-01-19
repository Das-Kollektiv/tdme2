#include <tdme/engine/GeometryBuffer.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/framebuffer/DeferredLightingRenderShader.h>
#include <tdme/engine/subsystems/framebuffer/FrameBufferRenderShader.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShader.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
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
using tdme::engine::subsystems::renderer::RendererBackend;
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
	this->depthBufferTextureId = Engine::getRendererBackend()->ID_NONE;
	this->geometryBufferTextureId1 = Engine::getRendererBackend()->ID_NONE;
	this->geometryBufferTextureId2 = Engine::getRendererBackend()->ID_NONE;
	this->geometryBufferTextureId3 = Engine::getRendererBackend()->ID_NONE;
	this->colorBufferTextureId1 = Engine::getRendererBackend()->ID_NONE;
	this->colorBufferTextureId2 = Engine::getRendererBackend()->ID_NONE;
	this->colorBufferTextureId3 = Engine::getRendererBackend()->ID_NONE;
	this->colorBufferTextureId4 = Engine::getRendererBackend()->ID_NONE;
	this->colorBufferTextureId5 = Engine::getRendererBackend()->ID_NONE;
}

void GeometryBuffer::initialize()
{
	depthBufferTextureId = Engine::getRendererBackend()->createDepthBufferTexture(width, height, 0, 0);
	geometryBufferTextureId1 = Engine::getRendererBackend()->createGBufferGeometryTexture(width, height);
	geometryBufferTextureId2 = Engine::getRendererBackend()->createGBufferGeometryTexture(width, height);
	geometryBufferTextureId3 = Engine::getRendererBackend()->createGBufferGeometryTexture(width, height);
	colorBufferTextureId1 = Engine::getRendererBackend()->createGBufferColorTexture(width, height);
	colorBufferTextureId2 = Engine::getRendererBackend()->createGBufferColorTexture(width, height);
	colorBufferTextureId3 = Engine::getRendererBackend()->createGBufferColorTexture(width, height);
	colorBufferTextureId4 = Engine::getRendererBackend()->createGBufferColorTexture(width, height);
	colorBufferTextureId5 = Engine::getRendererBackend()->createGBufferColorTexture(width, height);
	frameBufferId = Engine::getRendererBackend()->createGeometryBufferObject(
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
	Engine::getRendererBackend()->resizeDepthBufferTexture(depthBufferTextureId, width, height);
	Engine::getRendererBackend()->resizeGBufferGeometryTexture(geometryBufferTextureId1, width, height);
	Engine::getRendererBackend()->resizeGBufferGeometryTexture(geometryBufferTextureId2, width, height);
	Engine::getRendererBackend()->resizeGBufferGeometryTexture(geometryBufferTextureId3, width, height);
	Engine::getRendererBackend()->resizeGBufferColorTexture(colorBufferTextureId1, width, height);
	Engine::getRendererBackend()->resizeGBufferColorTexture(colorBufferTextureId2, width, height);
	Engine::getRendererBackend()->resizeGBufferColorTexture(colorBufferTextureId3, width, height);
	Engine::getRendererBackend()->resizeGBufferColorTexture(colorBufferTextureId4, width, height);
	Engine::getRendererBackend()->resizeGBufferColorTexture(colorBufferTextureId5, width, height);
}

void GeometryBuffer::dispose()
{
	Engine::getRendererBackend()->disposeTexture(depthBufferTextureId);
	Engine::getRendererBackend()->disposeTexture(geometryBufferTextureId1);
	Engine::getRendererBackend()->disposeTexture(geometryBufferTextureId2);
	Engine::getRendererBackend()->disposeTexture(geometryBufferTextureId3);
	Engine::getRendererBackend()->disposeTexture(colorBufferTextureId1);
	Engine::getRendererBackend()->disposeTexture(colorBufferTextureId2);
	Engine::getRendererBackend()->disposeTexture(colorBufferTextureId3);
	Engine::getRendererBackend()->disposeTexture(colorBufferTextureId4);
	Engine::getRendererBackend()->disposeTexture(colorBufferTextureId5);
	// TODO: Vulkan might need a extra method here
	Engine::getRendererBackend()->disposeFrameBufferObject(frameBufferId);
}

void GeometryBuffer::enableGeometryBuffer()
{
	Engine::getRendererBackend()->bindFrameBuffer(frameBufferId);
	Engine::getRendererBackend()->setViewPort(width, height);
	Engine::getRendererBackend()->updateViewPort();
}

void GeometryBuffer::disableGeometryBuffer()
{
	Engine::getRendererBackend()->bindFrameBuffer(Engine::getRendererBackend()->FRAMEBUFFER_DEFAULT);
	Engine::getRendererBackend()->setViewPort(Engine::instance->width, Engine::instance->height);
	Engine::getRendererBackend()->updateViewPort();
}

void GeometryBuffer::renderToScreen(Engine* engine, vector<Decal*>& decalEntities)
{
	auto rendererBackend = Engine::getRendererBackend();

	// use default context
	auto contextIdx = rendererBackend->CONTEXTINDEX_DEFAULT;

	//
	rendererBackend->disableCulling(contextIdx);

	// use deferred lighting render shader
	auto frameBufferRenderShader = Engine::getFrameBufferRenderShader();
	auto deferredLightingRenderShader = Engine::getDeferredLightingRenderShader();
	deferredLightingRenderShader->useProgram(engine, decalEntities);

	// bind geometry buffer textures
	rendererBackend->setTextureUnit(contextIdx, 0);
	rendererBackend->bindTexture(contextIdx, geometryBufferTextureId1);
	rendererBackend->setTextureUnit(contextIdx, 1);
	rendererBackend->bindTexture(contextIdx, geometryBufferTextureId2);
	rendererBackend->setTextureUnit(contextIdx, 2);
	rendererBackend->bindTexture(contextIdx, geometryBufferTextureId3);

	// bind color buffer textures
	rendererBackend->setTextureUnit(contextIdx, 3);
	rendererBackend->bindTexture(contextIdx, colorBufferTextureId1);
	rendererBackend->setTextureUnit(contextIdx, 4);
	rendererBackend->bindTexture(contextIdx, colorBufferTextureId2);
	rendererBackend->setTextureUnit(contextIdx, 5);
	rendererBackend->bindTexture(contextIdx, colorBufferTextureId3);
	rendererBackend->setTextureUnit(contextIdx, 6);
	rendererBackend->bindTexture(contextIdx, colorBufferTextureId4);
	rendererBackend->setTextureUnit(contextIdx, 7);
	rendererBackend->bindTexture(contextIdx, colorBufferTextureId5);

	// bind depth buffer texture
	rendererBackend->setTextureUnit(contextIdx, 8);
	rendererBackend->bindTexture(contextIdx, depthBufferTextureId);

	//
	rendererBackend->bindVerticesBufferObject(contextIdx, frameBufferRenderShader->getVBOVertices());
	rendererBackend->bindTextureCoordinatesBufferObject(contextIdx, frameBufferRenderShader->getVBOTextureCoordinates());

	// draw
	rendererBackend->drawTrianglesFromBufferObjects(contextIdx, 2, 0);

	// unbind buffers
	rendererBackend->unbindBufferObjects(contextIdx);

	// unbind geometry buffer textures
	rendererBackend->setTextureUnit(contextIdx, 0);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
	rendererBackend->setTextureUnit(contextIdx, 1);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
	rendererBackend->setTextureUnit(contextIdx, 2);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);

	// unbind color buffer textures
	rendererBackend->setTextureUnit(contextIdx, 3);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
	rendererBackend->setTextureUnit(contextIdx, 4);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
	rendererBackend->setTextureUnit(contextIdx, 5);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
	rendererBackend->setTextureUnit(contextIdx, 6);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
	rendererBackend->setTextureUnit(contextIdx, 7);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);

	// unbind depth buffer texture
	rendererBackend->setTextureUnit(contextIdx, 8);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);

	// switch back to diffuse texture unit
	rendererBackend->setTextureUnit(contextIdx, 0);

	//
	deferredLightingRenderShader->unUseProgram();

	// unset
	rendererBackend->enableCulling(contextIdx);
}

