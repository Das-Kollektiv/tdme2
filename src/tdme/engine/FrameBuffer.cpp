// Generated from /tdme/src/tdme/engine/FrameBuffer.java
#include <tdme/engine/FrameBuffer.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>

using tdme::engine::FrameBuffer;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::Engine;
using tdme::engine::subsystems::renderer::GLRenderer;

FrameBuffer::FrameBuffer(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

FrameBuffer::FrameBuffer(int32_t width, int32_t height, int32_t buffers) 
	: FrameBuffer(*static_cast< ::default_init_tag* >(0))
{
	ctor(width,height,buffers);
}

constexpr int32_t FrameBuffer::FRAMEBUFFER_DEPTHBUFFER;

constexpr int32_t FrameBuffer::FRAMEBUFFER_COLORBUFFER;

void FrameBuffer::ctor(int32_t width, int32_t height, int32_t buffers)
{
	super::ctor();
	this->width = width;
	this->height = height;
	this->buffers = buffers;
	frameBufferId = -1;
	depthBufferTextureId = Engine::renderer->ID_NONE;
	colorBufferTextureId = Engine::renderer->ID_NONE;
}

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
	clinit();
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

String* FrameBuffer::toString()
{
	return ::java::lang::StringBuilder().append(u"FrameBuffer [width="_j)->append(width)
		->append(u", height="_j)
		->append(height)
		->append(u", frameBufferId="_j)
		->append(frameBufferId)
		->append(u", depthBufferTextureId="_j)
		->append(depthBufferTextureId)
		->append(u", colorBufferTextureId="_j)
		->append(colorBufferTextureId)
		->append(u", buffers="_j)
		->append(buffers)
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* FrameBuffer::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.FrameBuffer", 23);
    return c;
}

java::lang::Class* FrameBuffer::getClass0()
{
	return class_();
}

