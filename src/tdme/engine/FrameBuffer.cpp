#include <tdme/engine/FrameBuffer.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/framebuffer/FrameBufferRenderShader.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShader.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/Engine.h>
#include <tdme/math/Math.h>
#include <tdme/utilities/Float.h>

using tdme::engine::subsystems::framebuffer::FrameBufferRenderShader;
using tdme::engine::subsystems::postprocessing::PostProcessingShader;
using tdme::engine::subsystems::renderer::RendererBackend;
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
	depthBufferTextureId = Engine::getRendererBackend()->ID_NONE;
	colorBufferTextureId = Engine::getRendererBackend()->ID_NONE;
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
		if (depthBufferTextureId == Engine::getRendererBackend()->ID_NONE) {
			depthBufferTextureId = Engine::getRendererBackend()->createDepthBufferTexture(width, height, cubeMapTextureId, cubeMapTextureIndex);
		} else {
			ownsDepthBufferTexture = false;
		}
	}

	if ((buffers & FRAMEBUFFER_COLORBUFFER) == FRAMEBUFFER_COLORBUFFER && (Engine::getRendererBackend()->getRendererType() == RendererBackend::RENDERERTYPE_VULKAN || cubeMapTextureId == TEXTUREID_NONE)) {
		if (colorBufferTextureId == Engine::getRendererBackend()->ID_NONE) {
			colorBufferTextureId = Engine::getRendererBackend()->createColorBufferTexture(width, height, cubeMapTextureId, cubeMapTextureIndex);
		} else {
			ownsColorBufferTexture = false;
		}
	}

	auto rendererCubeMapTextureIndex = -1;
	switch(cubeMapTextureIndex) {
		case CUBEMAPTEXTUREINDEX_NONE: rendererCubeMapTextureIndex = -1; break;
		case CUBEMAPTEXTUREINDEX_NEGATIVE_X: rendererCubeMapTextureIndex = Engine::getRendererBackend()->CUBEMAPTEXTUREINDEX_NEGATIVE_X; break;
		case CUBEMAPTEXTUREINDEX_POSITIVE_X: rendererCubeMapTextureIndex = Engine::getRendererBackend()->CUBEMAPTEXTUREINDEX_POSITIVE_X; break;
		case CUBEMAPTEXTUREINDEX_POSITIVE_Y: rendererCubeMapTextureIndex = Engine::getRendererBackend()->CUBEMAPTEXTUREINDEX_POSITIVE_Y; break;
		case CUBEMAPTEXTUREINDEX_NEGATIVE_Y: rendererCubeMapTextureIndex = Engine::getRendererBackend()->CUBEMAPTEXTUREINDEX_NEGATIVE_Y; break;
		case CUBEMAPTEXTUREINDEX_POSITIVE_Z: rendererCubeMapTextureIndex = Engine::getRendererBackend()->CUBEMAPTEXTUREINDEX_POSITIVE_Z; break;
		case CUBEMAPTEXTUREINDEX_NEGATIVE_Z: rendererCubeMapTextureIndex = Engine::getRendererBackend()->CUBEMAPTEXTUREINDEX_NEGATIVE_Z; break;
	}

	frameBufferId = Engine::getRendererBackend()->createFramebufferObject(depthBufferTextureId, colorBufferTextureId, cubeMapTextureId, rendererCubeMapTextureIndex);
}

void FrameBuffer::reshape(int32_t width, int32_t height)
{
	if ((buffers & FRAMEBUFFER_DEPTHBUFFER) == FRAMEBUFFER_DEPTHBUFFER && ownsDepthBufferTexture == true)
		Engine::getRendererBackend()->resizeDepthBufferTexture(depthBufferTextureId, width, height);

	if ((buffers & FRAMEBUFFER_COLORBUFFER) == FRAMEBUFFER_COLORBUFFER && cubeMapTextureId == TEXTUREID_NONE && ownsColorBufferTexture == true)
		Engine::getRendererBackend()->resizeColorBufferTexture(colorBufferTextureId, width, height);

	this->width = width;
	this->height = height;
}

void FrameBuffer::dispose()
{
	if ((buffers & FRAMEBUFFER_DEPTHBUFFER) == FRAMEBUFFER_DEPTHBUFFER && ownsDepthBufferTexture == true)
		Engine::getRendererBackend()->disposeTexture(depthBufferTextureId);

	if ((buffers & FRAMEBUFFER_COLORBUFFER) == FRAMEBUFFER_COLORBUFFER && cubeMapTextureId == TEXTUREID_NONE && ownsColorBufferTexture == true)
		Engine::getRendererBackend()->disposeTexture(colorBufferTextureId);

	Engine::getRendererBackend()->disposeFrameBufferObject(frameBufferId);
}

void FrameBuffer::enableFrameBuffer()
{
	Engine::getRendererBackend()->bindFrameBuffer(frameBufferId);
	Engine::getRendererBackend()->setViewPort(width, height);
	Engine::getRendererBackend()->updateViewPort();
}

void FrameBuffer::disableFrameBuffer()
{
	Engine::getRendererBackend()->bindFrameBuffer(Engine::getRendererBackend()->FRAMEBUFFER_DEFAULT);
	Engine::getRendererBackend()->setViewPort(Engine::instance->width, Engine::instance->height);
	Engine::getRendererBackend()->updateViewPort();
}

void FrameBuffer::bindDepthBufferTexture(int contextIdx)
{
	Engine::getRendererBackend()->bindTexture(contextIdx, depthBufferTextureId);
}

void FrameBuffer::bindColorBufferTexture(int contextIdx)
{
	Engine::getRendererBackend()->bindTexture(contextIdx, colorBufferTextureId);
}

void FrameBuffer::renderToScreen(Engine* engine, int32_t depthBufferTextureId, int32_t colorBufferTextureId)
{
	auto rendererBackend = Engine::getRendererBackend();

	// use default context
	auto contextIdx = rendererBackend->CONTEXTINDEX_DEFAULT;

	//
	rendererBackend->disableCulling(contextIdx);

	// clear
	rendererBackend->setClearColor(engine->sceneColor.getRed(), engine->sceneColor.getGreen(), engine->sceneColor.getBlue(), engine->sceneColor.getAlpha());
	rendererBackend->clear(rendererBackend->CLEAR_COLOR_BUFFER_BIT | rendererBackend->CLEAR_DEPTH_BUFFER_BIT);

	// use frame buffer render shader
	auto frameBufferRenderShader = Engine::getFrameBufferRenderShader();
	frameBufferRenderShader->useProgram();

	// bind color buffer texture
	rendererBackend->setTextureUnit(contextIdx, 0);
	rendererBackend->bindTexture(contextIdx, colorBufferTextureId);

	// bind depth buffer texture
	rendererBackend->setTextureUnit(contextIdx, 1);
	rendererBackend->bindTexture(contextIdx, depthBufferTextureId);

	//
	rendererBackend->bindVerticesBufferObject(contextIdx, frameBufferRenderShader->getVBOVertices());
	rendererBackend->bindTextureCoordinatesBufferObject(contextIdx, frameBufferRenderShader->getVBOTextureCoordinates());

	// draw
	rendererBackend->drawTrianglesFromBufferObjects(contextIdx, 2, 0);

	// unbind buffers
	rendererBackend->unbindBufferObjects(contextIdx);

	// unbind color buffer texture
	rendererBackend->setTextureUnit(contextIdx, 0);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);

	// unbind depth buffer texture
	rendererBackend->setTextureUnit(contextIdx, 1);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);

	// switch back to diffuse texture unit
	rendererBackend->setTextureUnit(contextIdx, 0);

	//
	frameBufferRenderShader->unUseProgram();

	// unset
	rendererBackend->enableCulling(contextIdx);
}

void FrameBuffer::doPostProcessing(Engine* engine, FrameBuffer* target, FrameBuffer* source, const string& programId, const string& shaderId, FrameBuffer* temporary, FrameBuffer* blendToSource)
{
	if (target != nullptr) {
		target->enableFrameBuffer();
	} else {
		disableFrameBuffer();
	}

	//
	auto rendererBackend = Engine::getRendererBackend();

	// if we blend source over blend to source?
	if (blendToSource != nullptr) {
		// yup
		blendToSource->renderToScreen(engine);
		rendererBackend->enableAdditionBlending();
		rendererBackend->disableDepthBufferTest();
	} else {
		// otherwise just clear target
		rendererBackend->setClearColor(engine->sceneColor.getRed(), engine->sceneColor.getGreen(), engine->sceneColor.getBlue(), engine->sceneColor.getAlpha());
		rendererBackend->clear(rendererBackend->CLEAR_COLOR_BUFFER_BIT | rendererBackend->CLEAR_DEPTH_BUFFER_BIT);
	}

	// use default context
	auto contextIdx = rendererBackend->CONTEXTINDEX_DEFAULT;

	//
	rendererBackend->disableCulling(contextIdx);

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
	rendererBackend->setTextureUnit(contextIdx, 0);
	rendererBackend->bindTexture(contextIdx, source->colorBufferTextureId);

	// bind depth buffer texture
	rendererBackend->setTextureUnit(contextIdx, 1);
	rendererBackend->bindTexture(contextIdx, source->depthBufferTextureId);

	// bind temporary if any given
	if (temporary != nullptr) {
		rendererBackend->setTextureUnit(contextIdx, 2);
		rendererBackend->bindTexture(contextIdx, temporary->colorBufferTextureId);

		rendererBackend->setTextureUnit(contextIdx, 3);
		rendererBackend->bindTexture(contextIdx, temporary->depthBufferTextureId);
	}

	//
	rendererBackend->bindVerticesBufferObject(contextIdx, frameBufferRenderShader->getVBOVertices());
	rendererBackend->bindTextureCoordinatesBufferObject(contextIdx, frameBufferRenderShader->getVBOTextureCoordinates());

	// unuse frame buffer render shader
	rendererBackend->drawTrianglesFromBufferObjects(contextIdx, 2, 0);

	// unbind buffers
	rendererBackend->unbindBufferObjects(contextIdx);

	// unbind color buffer texture
	rendererBackend->setTextureUnit(contextIdx, 0);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);

	// unbind depth buffer texture
	rendererBackend->setTextureUnit(contextIdx, 1);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);

	// unbind temporary if any given
	if (temporary != nullptr) {
		rendererBackend->setTextureUnit(contextIdx, 2);
		rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);

		rendererBackend->setTextureUnit(contextIdx, 3);
		rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
	}

	// switch back to diffuse texture unit
	rendererBackend->setTextureUnit(contextIdx, 0);

	//
	postProcessingShader->unUseProgram();

	// unset
	rendererBackend->enableCulling(contextIdx);

	// did we blend?
	if (blendToSource != nullptr) {
		rendererBackend->disableBlending();
		rendererBackend->enableDepthBufferTest();
	}

	//
	if (target != nullptr) {
		disableFrameBuffer();
	}
}

