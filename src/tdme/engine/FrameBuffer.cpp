#include <tdme/engine/FrameBuffer.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/framebuffer/FrameBufferRenderShader.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShader.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/Engine.h>
#include <tdme/math/Math.h>
#include <tdme/utilities/Float.h>

using tdme::engine::subsystems::framebuffer::FrameBufferRenderShader;
using tdme::engine::subsystems::postprocessing::PostProcessingShader;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::math::Math;
using tdme::utilities::Float;

FrameBuffer::FrameBuffer(int32_t width, int32_t height, int32_t buffers, int32_t cubeMapTextureId, int32_t cubeMapTextureIndex)
{
	this->width = width;
	this->height = height;
	this->buffers = buffers;
	frameBufferId = -1;
	depthBufferTextureId = Engine::getRenderer()->ID_NONE;
	colorBufferTextureId = Engine::getRenderer()->ID_NONE;
	ownsDepthBufferTexture = true;
	ownsColorBufferTexture = true;
	this->cubeMapTextureId = cubeMapTextureId;
	this->cubeMapTextureIndex = cubeMapTextureIndex;
}

FrameBuffer::~FrameBuffer() {
}

void FrameBuffer::initialize()
{
	if ((buffers & FRAMEBUFFER_DEPTHBUFFER) == FRAMEBUFFER_DEPTHBUFFER) {
		if (depthBufferTextureId == Engine::getRenderer()->ID_NONE) {
			depthBufferTextureId = Engine::getRenderer()->createDepthBufferTexture(width, height, cubeMapTextureId, cubeMapTextureIndex);
		} else {
			ownsDepthBufferTexture = false;
		}
	}

	if ((buffers & FRAMEBUFFER_COLORBUFFER) == FRAMEBUFFER_COLORBUFFER && (Engine::getRenderer()->getRendererType() == Renderer::RENDERERTYPE_VULKAN || cubeMapTextureId == TEXTUREID_NONE)) {
		if (colorBufferTextureId == Engine::getRenderer()->ID_NONE) {
			colorBufferTextureId = Engine::getRenderer()->createColorBufferTexture(width, height, cubeMapTextureId, cubeMapTextureIndex);
		} else {
			ownsColorBufferTexture = false;
		}
	}

	auto rendererCubeMapTextureIndex = -1;
	switch(cubeMapTextureIndex) {
		case CUBEMAPTEXTUREINDEX_NONE: rendererCubeMapTextureIndex = -1; break;
		case CUBEMAPTEXTUREINDEX_NEGATIVE_X: rendererCubeMapTextureIndex = Engine::getRenderer()->CUBEMAPTEXTUREINDEX_NEGATIVE_X; break;
		case CUBEMAPTEXTUREINDEX_POSITIVE_X: rendererCubeMapTextureIndex = Engine::getRenderer()->CUBEMAPTEXTUREINDEX_POSITIVE_X; break;
		case CUBEMAPTEXTUREINDEX_POSITIVE_Y: rendererCubeMapTextureIndex = Engine::getRenderer()->CUBEMAPTEXTUREINDEX_POSITIVE_Y; break;
		case CUBEMAPTEXTUREINDEX_NEGATIVE_Y: rendererCubeMapTextureIndex = Engine::getRenderer()->CUBEMAPTEXTUREINDEX_NEGATIVE_Y; break;
		case CUBEMAPTEXTUREINDEX_POSITIVE_Z: rendererCubeMapTextureIndex = Engine::getRenderer()->CUBEMAPTEXTUREINDEX_POSITIVE_Z; break;
		case CUBEMAPTEXTUREINDEX_NEGATIVE_Z: rendererCubeMapTextureIndex = Engine::getRenderer()->CUBEMAPTEXTUREINDEX_NEGATIVE_Z; break;
	}

	frameBufferId = Engine::getRenderer()->createFramebufferObject(depthBufferTextureId, colorBufferTextureId, cubeMapTextureId, rendererCubeMapTextureIndex);
}

void FrameBuffer::reshape(int32_t width, int32_t height)
{
	if ((buffers & FRAMEBUFFER_DEPTHBUFFER) == FRAMEBUFFER_DEPTHBUFFER && ownsDepthBufferTexture == true)
		Engine::getRenderer()->resizeDepthBufferTexture(depthBufferTextureId, width, height);

	if ((buffers & FRAMEBUFFER_COLORBUFFER) == FRAMEBUFFER_COLORBUFFER && cubeMapTextureId == TEXTUREID_NONE && ownsColorBufferTexture == true)
		Engine::getRenderer()->resizeColorBufferTexture(colorBufferTextureId, width, height);

	this->width = width;
	this->height = height;
}

void FrameBuffer::dispose()
{
	if ((buffers & FRAMEBUFFER_DEPTHBUFFER) == FRAMEBUFFER_DEPTHBUFFER && ownsDepthBufferTexture == true)
		Engine::getRenderer()->disposeTexture(depthBufferTextureId);

	if ((buffers & FRAMEBUFFER_COLORBUFFER) == FRAMEBUFFER_COLORBUFFER && cubeMapTextureId == TEXTUREID_NONE && ownsColorBufferTexture == true)
		Engine::getRenderer()->disposeTexture(colorBufferTextureId);

	Engine::getRenderer()->disposeFrameBufferObject(frameBufferId);
}

void FrameBuffer::enableFrameBuffer()
{
	Engine::getRenderer()->bindFrameBuffer(frameBufferId);
	Engine::getRenderer()->setViewPort(width, height);
	Engine::getRenderer()->updateViewPort();
}

void FrameBuffer::disableFrameBuffer()
{
	Engine::getRenderer()->bindFrameBuffer(Engine::getRenderer()->FRAMEBUFFER_DEFAULT);
	Engine::getRenderer()->setViewPort(Engine::instance->width, Engine::instance->height);
	Engine::getRenderer()->updateViewPort();
}

void FrameBuffer::bindDepthBufferTexture(int contextIdx)
{
	Engine::getRenderer()->bindTexture(contextIdx, depthBufferTextureId);
}

void FrameBuffer::bindColorBufferTexture(int contextIdx)
{
	Engine::getRenderer()->bindTexture(contextIdx, colorBufferTextureId);
}

void FrameBuffer::renderToScreen(Engine* engine, int32_t depthBufferTextureId, int32_t colorBufferTextureId)
{
	auto renderer = Engine::getRenderer();

	// use default context
	auto contextIdx = renderer->CONTEXTINDEX_DEFAULT;

	//
	renderer->disableCulling(contextIdx);

	// clear
	renderer->setClearColor(engine->sceneColor.getRed(), engine->sceneColor.getGreen(), engine->sceneColor.getBlue(), engine->sceneColor.getAlpha());
	renderer->clear(renderer->CLEAR_COLOR_BUFFER_BIT | renderer->CLEAR_DEPTH_BUFFER_BIT);

	// use frame buffer render shader
	auto frameBufferRenderShader = Engine::getFrameBufferRenderShader();
	frameBufferRenderShader->useProgram();

	// bind color buffer texture
	renderer->setTextureUnit(contextIdx, 0);
	renderer->bindTexture(contextIdx, colorBufferTextureId);

	// bind depth buffer texture
	renderer->setTextureUnit(contextIdx, 1);
	renderer->bindTexture(contextIdx, depthBufferTextureId);

	//
	renderer->bindVerticesBufferObject(contextIdx, frameBufferRenderShader->getVBOVertices());
	renderer->bindTextureCoordinatesBufferObject(contextIdx, frameBufferRenderShader->getVBOTextureCoordinates());

	// draw
	renderer->drawTrianglesFromBufferObjects(contextIdx, 2, 0);

	// unbind buffers
	renderer->unbindBufferObjects(contextIdx);

	// unbind color buffer texture
	renderer->setTextureUnit(contextIdx, 0);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);

	// unbind depth buffer texture
	renderer->setTextureUnit(contextIdx, 1);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);

	// switch back to diffuse texture unit
	renderer->setTextureUnit(contextIdx, 0);

	//
	frameBufferRenderShader->unUseProgram();

	// unset
	renderer->enableCulling(contextIdx);
}

void FrameBuffer::doPostProcessing(Engine* engine, FrameBuffer* target, FrameBuffer* source, const string& programId, const string& shaderId, FrameBuffer* temporary, FrameBuffer* blendToSource)
{
	if (target != nullptr) {
		target->enableFrameBuffer();
	} else {
		disableFrameBuffer();
	}

	//
	auto renderer = Engine::getRenderer();

	// if we blend source over blend to source?
	if (blendToSource != nullptr) {
		// yup
		blendToSource->renderToScreen(engine);
		renderer->enableAdditionBlending();
		renderer->disableDepthBufferTest();
	} else {
		// otherwise just clear target
		renderer->setClearColor(engine->sceneColor.getRed(), engine->sceneColor.getGreen(), engine->sceneColor.getBlue(), engine->sceneColor.getAlpha());
		renderer->clear(renderer->CLEAR_COLOR_BUFFER_BIT | renderer->CLEAR_DEPTH_BUFFER_BIT);
	}

	// use default context
	auto contextIdx = renderer->CONTEXTINDEX_DEFAULT;

	//
	renderer->disableCulling(contextIdx);

	// use frame buffer render shader
	auto frameBufferRenderShader = Engine::getFrameBufferRenderShader();

	//
	int _width = engine->getScaledWidth() != -1?engine->getScaledWidth():engine->getWidth();
	int _height = engine->getScaledHeight() != -1?engine->getScaledHeight():engine->getHeight();

	// use post processing shader
	auto postProcessingShader = Engine::getInstance()->getPostProcessingShader();
	postProcessingShader->useProgram();
	postProcessingShader->setShader(contextIdx, shaderId);
	postProcessingShader->setBufferPixelWidth(contextIdx, 1.0f / static_cast<float>(source->getWidth()));
	postProcessingShader->setBufferPixelHeight(contextIdx, 1.0f / static_cast<float>(source->getHeight()));
	postProcessingShader->setShaderParameters(contextIdx, engine);

	// bind color buffer texture
	renderer->setTextureUnit(contextIdx, 0);
	renderer->bindTexture(contextIdx, source->colorBufferTextureId);

	// bind depth buffer texture
	renderer->setTextureUnit(contextIdx, 1);
	renderer->bindTexture(contextIdx, source->depthBufferTextureId);

	// bind temporary if any given
	if (temporary != nullptr) {
		renderer->setTextureUnit(contextIdx, 2);
		renderer->bindTexture(contextIdx, temporary->colorBufferTextureId);

		renderer->setTextureUnit(contextIdx, 3);
		renderer->bindTexture(contextIdx, temporary->depthBufferTextureId);
	}

	//
	renderer->bindVerticesBufferObject(contextIdx, frameBufferRenderShader->getVBOVertices());
	renderer->bindTextureCoordinatesBufferObject(contextIdx, frameBufferRenderShader->getVBOTextureCoordinates());

	// unuse frame buffer render shader
	renderer->drawTrianglesFromBufferObjects(contextIdx, 2, 0);

	// unbind buffers
	renderer->unbindBufferObjects(contextIdx);

	// unbind color buffer texture
	renderer->setTextureUnit(contextIdx, 0);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);

	// unbind depth buffer texture
	renderer->setTextureUnit(contextIdx, 1);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);

	// unbind temporary if any given
	if (temporary != nullptr) {
		renderer->setTextureUnit(contextIdx, 2);
		renderer->bindTexture(contextIdx, renderer->ID_NONE);

		renderer->setTextureUnit(contextIdx, 3);
		renderer->bindTexture(contextIdx, renderer->ID_NONE);
	}

	// switch back to diffuse texture unit
	renderer->setTextureUnit(contextIdx, 0);

	//
	postProcessingShader->unUseProgram();

	// unset
	renderer->enableCulling(contextIdx);

	// did we blend?
	if (blendToSource != nullptr) {
		renderer->disableBlending();
		renderer->enableDepthBufferTest();
	}

	//
	if (target != nullptr) {
		disableFrameBuffer();
	}
}

