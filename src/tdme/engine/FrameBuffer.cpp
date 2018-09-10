#include <tdme/engine/FrameBuffer.h>

#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/subsystems/framebuffer/FrameBufferRenderShader.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShader.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>

using tdme::engine::FrameBuffer;
using tdme::engine::Engine;
using tdme::engine::subsystems::framebuffer::FrameBufferRenderShader;
using tdme::engine::subsystems::postprocessing::PostProcessingShader;
using tdme::engine::subsystems::renderer::GLRenderer;

FrameBuffer::FrameBuffer(int32_t width, int32_t height, int32_t buffers) 
{
	this->width = width;
	this->height = height;
	this->buffers = buffers;
	frameBufferId = -1;
	depthBufferTextureId = Engine::renderer->ID_NONE;
	colorBufferTextureId = Engine::renderer->ID_NONE;
}

constexpr int32_t FrameBuffer::FRAMEBUFFER_DEPTHBUFFER;

constexpr int32_t FrameBuffer::FRAMEBUFFER_COLORBUFFER;

int32_t FrameBuffer::getWidth()
{
	return width;
}

int32_t FrameBuffer::getHeight()
{
	return height;
}

void FrameBuffer::initialize()
{
	if ((buffers & FRAMEBUFFER_DEPTHBUFFER) == FRAMEBUFFER_DEPTHBUFFER)
		depthBufferTextureId = Engine::renderer->createDepthBufferTexture(width, height);

	if ((buffers & FRAMEBUFFER_COLORBUFFER) == FRAMEBUFFER_COLORBUFFER)
		colorBufferTextureId = Engine::renderer->createColorBufferTexture(width, height);

	frameBufferId = Engine::renderer->createFramebufferObject(depthBufferTextureId, colorBufferTextureId);
}

void FrameBuffer::reshape(int32_t width, int32_t height)
{
	if ((buffers & FRAMEBUFFER_DEPTHBUFFER) == FRAMEBUFFER_DEPTHBUFFER)
		Engine::renderer->resizeDepthBufferTexture(depthBufferTextureId, width, height);

	if ((buffers & FRAMEBUFFER_COLORBUFFER) == FRAMEBUFFER_COLORBUFFER)
		Engine::renderer->resizeColorBufferTexture(colorBufferTextureId, width, height);

	this->width = width;
	this->height = height;
}

void FrameBuffer::dispose()
{
	if ((buffers & FRAMEBUFFER_DEPTHBUFFER) == FRAMEBUFFER_DEPTHBUFFER)
		Engine::renderer->disposeTexture(depthBufferTextureId);

	if ((buffers & FRAMEBUFFER_COLORBUFFER) == FRAMEBUFFER_COLORBUFFER)
		Engine::renderer->disposeTexture(colorBufferTextureId);

	Engine::renderer->disposeFrameBufferObject(frameBufferId);
}

void FrameBuffer::enableFrameBuffer()
{
	Engine::renderer->bindFrameBuffer(frameBufferId);
	Engine::renderer->setViewPort(0, 0, width, height);
	Engine::renderer->updateViewPort();
}

void FrameBuffer::disableFrameBuffer()
{
	Engine::renderer->bindFrameBuffer(Engine::renderer->FRAMEBUFFER_DEFAULT);
	Engine::renderer->setViewPort(0, 0, Engine::instance->getWidth(), Engine::instance->getHeight());
	Engine::renderer->updateViewPort();
}

void FrameBuffer::bindDepthBufferTexture()
{
	Engine::renderer->bindTexture(depthBufferTextureId);
}

int32_t FrameBuffer::getColorBufferTextureId()
{
	return colorBufferTextureId;
}

int32_t FrameBuffer::getDepthBufferTextureId()
{
	return depthBufferTextureId;
}

void FrameBuffer::renderToScreen()
{
	auto renderer = Engine::renderer;

	//
	renderer->disableDepthBufferWriting();
	renderer->disableDepthBufferTest();
	renderer->disableCulling();

	// use frame buffer render shader
	auto frameBufferRenderShader = Engine::getFrameBufferRenderShader();
	frameBufferRenderShader->useProgram();

	// bind color buffer texture
	renderer->setTextureUnit(0);
	renderer->bindTexture(colorBufferTextureId);

	//
	renderer->bindVerticesBufferObject(frameBufferRenderShader->getVBOVertices());
	renderer->bindTextureCoordinatesBufferObject(frameBufferRenderShader->getVBOTextureCoordinates());

	// unuse frame buffer render shader
	renderer->drawTrianglesFromBufferObjects(2, 0);

	// unbind buffers
	renderer->unbindBufferObjects();

	//
	frameBufferRenderShader->unUseProgram();

	// unset
	renderer->enableCulling();
	renderer->enableDepthBufferTest();
	renderer->enableDepthBufferWriting();
}

void FrameBuffer::doPostProcessing(FrameBuffer* source, const string& shaderId)
{
	enableFrameBuffer();

	//
	auto renderer = Engine::renderer;

	//
	renderer->disableDepthBufferTest();
	renderer->disableCulling();

	// use frame buffer render shader
	auto frameBufferRenderShader = Engine::getFrameBufferRenderShader();

	// use post processing shader
	auto postProcessingShader = Engine::getInstance()->getPostProcessingShader();
	postProcessingShader->useProgram();
	postProcessingShader->setShader(shaderId);
	postProcessingShader->setBufferPixelWidth(1.0f / static_cast<float>(source->getWidth()));
	postProcessingShader->setBufferPixelHeight(1.0f / static_cast<float>(source->getHeight()));

	// bind color buffer texture
	renderer->setTextureUnit(0);
	renderer->bindTexture(source->colorBufferTextureId);

	// bind color buffer texture
	renderer->setTextureUnit(1);
	renderer->bindTexture(source->depthBufferTextureId);

	//
	renderer->bindVerticesBufferObject(frameBufferRenderShader->getVBOVertices());
	renderer->bindTextureCoordinatesBufferObject(frameBufferRenderShader->getVBOTextureCoordinates());

	// unuse frame buffer render shader
	renderer->drawTrianglesFromBufferObjects(2, 0);

	// unbind buffers
	renderer->unbindBufferObjects();

	//
	postProcessingShader->unUseProgram();

	// unset
	renderer->enableCulling();
	renderer->enableDepthBufferTest();

	//
	disableFrameBuffer();
}

