#include <tdme/engine/GeometryBuffer.h>

#include <tdme/engine/subsystems/framebuffer/DeferredLightingRenderShader.h>
#include <tdme/engine/subsystems/framebuffer/FrameBufferRenderShader.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShader.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/Engine.h>
#include <tdme/math/Math.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Float.h>

using tdme::engine::GeometryBuffer;

using tdme::engine::subsystems::framebuffer::DeferredLightingRenderShader;
using tdme::engine::subsystems::framebuffer::FrameBufferRenderShader;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;
using tdme::math::Math;
using tdme::utilities::Console;
using tdme::utilities::Float;

GeometryBuffer::GeometryBuffer(int32_t width, int32_t height)
{
	Console::println("GeometryBuffer::GeometryBuffer(): " + to_string(width) + " x " + to_string(height));
	this->width = 1024; // width;
	this->height = 768; // height;
	this->frameBufferId = -1;
	this->depthBufferTextureId = Engine::renderer->ID_NONE;
	this->geometryBufferTextureId1 = Engine::renderer->ID_NONE;
	this->geometryBufferTextureId2 = Engine::renderer->ID_NONE;
	this->geometryBufferTextureId3 = Engine::renderer->ID_NONE;
	this->colorBufferTextureId1 = Engine::renderer->ID_NONE;
	this->colorBufferTextureId2 = Engine::renderer->ID_NONE;
	this->colorBufferTextureId3 = Engine::renderer->ID_NONE;
	this->colorBufferTextureId4 = Engine::renderer->ID_NONE;
	this->colorBufferTextureId5 = Engine::renderer->ID_NONE;
}

void GeometryBuffer::initialize()
{
	depthBufferTextureId = Engine::renderer->createDepthBufferTexture(width, height, 0, 0);
	geometryBufferTextureId1 = Engine::renderer->createGBufferGeometryTexture(width, height);
	geometryBufferTextureId2 = Engine::renderer->createGBufferGeometryTexture(width, height);
	geometryBufferTextureId3 = Engine::renderer->createGBufferGeometryTexture(width, height);
	colorBufferTextureId1 = Engine::renderer->createGBufferColorTexture(width, height);
	colorBufferTextureId2 = Engine::renderer->createGBufferColorTexture(width, height);
	colorBufferTextureId3 = Engine::renderer->createGBufferColorTexture(width, height);
	colorBufferTextureId4 = Engine::renderer->createGBufferColorTexture(width, height);
	colorBufferTextureId5 = Engine::renderer->createGBufferColorTexture(width, height);
	frameBufferId = Engine::renderer->createGeometryBufferObject(
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
	Console::println("GeometryBuffer::reshape(): " + to_string(width) + " x " + to_string(height));

	// TODO: resizing
	this->width = width;
	this->height = height;
	//
	Console::println("GeometryBuffer::reshape(): Not yet implemented.");
}

void GeometryBuffer::dispose()
{
	Engine::renderer->disposeTexture(depthBufferTextureId);
	Engine::renderer->disposeTexture(geometryBufferTextureId1);
	Engine::renderer->disposeTexture(geometryBufferTextureId2);
	Engine::renderer->disposeTexture(geometryBufferTextureId3);
	Engine::renderer->disposeTexture(colorBufferTextureId1);
	Engine::renderer->disposeTexture(colorBufferTextureId2);
	Engine::renderer->disposeTexture(colorBufferTextureId3);
	Engine::renderer->disposeTexture(colorBufferTextureId4);
	Engine::renderer->disposeTexture(colorBufferTextureId5);
	Engine::renderer->disposeFrameBufferObject(frameBufferId); // TODO: Vulkan might need a extra method here
}

void GeometryBuffer::enableGeometryBuffer()
{
	Engine::renderer->bindFrameBuffer(frameBufferId);
	Engine::renderer->setViewPort(0, 0, width, height);
	Engine::renderer->updateViewPort();
}

void GeometryBuffer::disableGeometryBuffer()
{
	Engine::renderer->bindFrameBuffer(Engine::renderer->FRAMEBUFFER_DEFAULT);
	Engine::renderer->setViewPort(0, 0, Engine::instance->width, Engine::instance->height);
	Engine::renderer->updateViewPort();
}

void GeometryBuffer::bindDepthBufferTexture(void* context)
{
	Engine::renderer->bindTexture(context, depthBufferTextureId);
}

void GeometryBuffer::bindGeometryBufferTextures(void* context) {
	Console::println("GeometryBuffer::bindGeometryBufferTextures(): Not yet implemented.");
}

void GeometryBuffer::bindColorBufferTextures(void* context) {
	Console::println("GeometryBuffer::bindColorBufferTextures(): Not yet implemented.");
}

void GeometryBuffer::renderToScreen(Engine* engine)
{
	auto renderer = Engine::renderer;

	// use default context
	auto context = renderer->getDefaultContext();

	//
	renderer->disableCulling(context);

	// clear
	renderer->clear(renderer->CLEAR_COLOR_BUFFER_BIT | renderer->CLEAR_DEPTH_BUFFER_BIT);

	// use deferred lighting render shader
	auto frameBufferRenderShader = Engine::getFrameBufferRenderShader();
	auto deferredLightingRenderShader = Engine::getDeferredLightingRenderShader();
	deferredLightingRenderShader->useProgram(engine);

	// bind geometry buffer textures
	renderer->setTextureUnit(context, 0);
	renderer->bindTexture(context, geometryBufferTextureId1);
	renderer->setTextureUnit(context, 1);
	renderer->bindTexture(context, geometryBufferTextureId2);
	renderer->setTextureUnit(context, 2);
	renderer->bindTexture(context, geometryBufferTextureId3);

	// bind color buffer textures
	renderer->setTextureUnit(context, 3);
	renderer->bindTexture(context, colorBufferTextureId1);
	renderer->setTextureUnit(context, 4);
	renderer->bindTexture(context, colorBufferTextureId2);
	renderer->setTextureUnit(context, 5);
	renderer->bindTexture(context, colorBufferTextureId3);
	renderer->setTextureUnit(context, 6);
	renderer->bindTexture(context, colorBufferTextureId4);
	renderer->setTextureUnit(context, 7);
	renderer->bindTexture(context, colorBufferTextureId5);

	// bind depth buffer texture
	renderer->setTextureUnit(context, 8);
	renderer->bindTexture(context, depthBufferTextureId);

	//
	renderer->bindVerticesBufferObject(context, frameBufferRenderShader->getVBOVertices());
	renderer->bindTextureCoordinatesBufferObject(context, frameBufferRenderShader->getVBOTextureCoordinates());

	// draw
	renderer->drawTrianglesFromBufferObjects(context, 2, 0);

	// unbind buffers
	renderer->unbindBufferObjects(context);

	// unbind geometry buffer textures
	renderer->setTextureUnit(context, 0);
	renderer->bindTexture(context, renderer->ID_NONE);
	renderer->setTextureUnit(context, 1);
	renderer->bindTexture(context, renderer->ID_NONE);
	renderer->setTextureUnit(context, 2);
	renderer->bindTexture(context, renderer->ID_NONE);

	// unbind color buffer textures
	renderer->setTextureUnit(context, 3);
	renderer->bindTexture(context, renderer->ID_NONE);
	renderer->setTextureUnit(context, 4);
	renderer->bindTexture(context, renderer->ID_NONE);
	renderer->setTextureUnit(context, 5);
	renderer->bindTexture(context, renderer->ID_NONE);
	renderer->setTextureUnit(context, 6);
	renderer->bindTexture(context, renderer->ID_NONE);
	renderer->setTextureUnit(context, 7);
	renderer->bindTexture(context, renderer->ID_NONE);

	// unbind depth buffer texture
	renderer->setTextureUnit(context, 8);
	renderer->bindTexture(context, renderer->ID_NONE);

	// switch back to diffuse texture unit
	renderer->setTextureUnit(context, 0);

	//
	deferredLightingRenderShader->unUseProgram();

	// unset
	renderer->enableCulling(context);
}

