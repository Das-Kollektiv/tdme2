#include <tdme/engine/FrameBuffer.h>

#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/subsystems/framebuffer/FrameBufferRenderShader.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShader.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>

using tdme::engine::FrameBuffer;
using tdme::engine::Engine;
using tdme::engine::subsystems::framebuffer::FrameBufferRenderShader;
using tdme::engine::subsystems::postprocessing::PostProcessingShader;
using tdme::engine::subsystems::renderer::Renderer;

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

void FrameBuffer::bindDepthBufferTexture(void* context)
{
	Engine::renderer->bindTexture(context, depthBufferTextureId);
}

void FrameBuffer::bindColorBufferTexture(void* context)
{
	Engine::renderer->bindTexture(context, colorBufferTextureId);
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

	// use default context
	auto context = renderer->getDefaultContext();

	//
	renderer->disableCulling();

	// clear
	renderer->clear(renderer->CLEAR_COLOR_BUFFER_BIT | renderer->CLEAR_DEPTH_BUFFER_BIT);

	// use frame buffer render shader
	auto frameBufferRenderShader = Engine::getFrameBufferRenderShader();
	frameBufferRenderShader->useProgram();

	// bind color buffer texture
	renderer->setTextureUnit(context, 0);
	renderer->bindTexture(context, colorBufferTextureId);

	// bind depth buffer texture
	renderer->setTextureUnit(context, 1);
	renderer->bindTexture(context, depthBufferTextureId);

	//
	renderer->bindVerticesBufferObject(context, frameBufferRenderShader->getVBOVertices());
	renderer->bindTextureCoordinatesBufferObject(context, frameBufferRenderShader->getVBOTextureCoordinates());

	// unuse frame buffer render shader
	renderer->drawTrianglesFromBufferObjects(context, 2, 0);

	// unbind buffers
	renderer->unbindBufferObjects(context);

	// unbind color buffer texture
	renderer->setTextureUnit(context, 0);
	renderer->bindTexture(context, renderer->ID_NONE);

	// unbind depth buffer texture
	renderer->setTextureUnit(context, 1);
	renderer->bindTexture(context, renderer->ID_NONE);

	// switch back to diffuse texture unit
	renderer->setTextureUnit(context, 0);

	//
	frameBufferRenderShader->unUseProgram();

	// unset
	renderer->enableCulling();
}

void FrameBuffer::doPostProcessing(FrameBuffer* target, FrameBuffer* source, const string& shaderId, FrameBuffer* temporary)
{
	if (target != nullptr) {
		target->enableFrameBuffer();
	} else {
		disableFrameBuffer();
	}

	//
	auto renderer = Engine::renderer;

	// use default context
	auto context = renderer->getDefaultContext();

	//
	renderer->disableCulling();

	// clear
	renderer->clear(renderer->CLEAR_COLOR_BUFFER_BIT | renderer->CLEAR_DEPTH_BUFFER_BIT);

	// use frame buffer render shader
	auto frameBufferRenderShader = Engine::getFrameBufferRenderShader();

	// use post processing shader
	auto postProcessingShader = Engine::getInstance()->getPostProcessingShader();
	postProcessingShader->useProgram();
	postProcessingShader->setShader(context, shaderId);
	postProcessingShader->setBufferPixelWidth(context, 1.0f / static_cast<float>(source->getWidth()));
	postProcessingShader->setBufferPixelHeight(context, 1.0f / static_cast<float>(source->getHeight()));

	// bind color buffer texture
	renderer->setTextureUnit(context, 0);
	renderer->bindTexture(context, source->colorBufferTextureId);

	// bind depth buffer texture
	renderer->setTextureUnit(context, 1);
	renderer->bindTexture(context, source->depthBufferTextureId);

	// bind temporary if any given
	if (temporary != nullptr) {
		renderer->setTextureUnit(context, 2);
		renderer->bindTexture(context, temporary->colorBufferTextureId);

		renderer->setTextureUnit(context, 3);
		renderer->bindTexture(context, temporary->depthBufferTextureId);
	}

	//
	renderer->bindVerticesBufferObject(context, frameBufferRenderShader->getVBOVertices());
	renderer->bindTextureCoordinatesBufferObject(context, frameBufferRenderShader->getVBOTextureCoordinates());

	// unuse frame buffer render shader
	renderer->drawTrianglesFromBufferObjects(context, 2, 0);

	// unbind buffers
	renderer->unbindBufferObjects(context);

	// unbind color buffer texture
	renderer->setTextureUnit(context, 0);
	renderer->bindTexture(context, renderer->ID_NONE);

	// unbind depth buffer texture
	renderer->setTextureUnit(context, 1);
	renderer->bindTexture(context, renderer->ID_NONE);

	// unbind temporary if any given
	if (temporary != nullptr) {
		renderer->setTextureUnit(context, 2);
		renderer->bindTexture(context, renderer->ID_NONE);

		renderer->setTextureUnit(context, 3);
		renderer->bindTexture(context, renderer->ID_NONE);
	}

	// switch back to diffuse texture unit
	renderer->setTextureUnit(context, 0);

	//
	postProcessingShader->unUseProgram();

	// unset
	renderer->enableCulling();

	//
	if (target != nullptr) {
		disableFrameBuffer();
	}
}

