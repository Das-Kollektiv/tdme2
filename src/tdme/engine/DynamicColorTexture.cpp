#include <tdme/engine/DynamicColorTexture.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/Engine.h>
#include <tdme/utilities/ByteBuffer.h>

using tdme::engine::Texture;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::DynamicColorTexture;
using tdme::engine::Engine;
using tdme::utilities::ByteBuffer;

uint32_t DynamicColorTexture::counter = 0;

void DynamicColorTexture::initialize()
{
	colorBufferTextureId = Engine::getRendererBackend()->createColorBufferTexture(width, height, Engine::getRendererBackend()->ID_NONE, Engine::getRendererBackend()->ID_NONE);
	texture = new Texture(
		"dynamic-color-texture:" + to_string(DynamicColorTexture::counter++),
		Texture::TEXTUREDEPTH_RGBA,
		Texture::TEXTUREFORMAT_RGBA,
		width, height,
		width, height,
		Texture::TEXTUREFORMAT_RGBA,
		ByteBuffer(width * height * 4)
	);
	texture->acquireReference();
	texture->setUseCompression(false);
	texture->setUseMipMap(false);
	texture->setRepeat(false);
}

void DynamicColorTexture::reshape(int32_t width, int32_t height)
{
	texture->releaseReference();
	texture = new Texture(
		"dynamic-color-texture:" + to_string(DynamicColorTexture::counter++),
		Texture::TEXTUREDEPTH_RGBA,
		Texture::TEXTUREFORMAT_RGBA,
		width, height,
		width, height,
		Texture::TEXTUREFORMAT_RGBA,
		ByteBuffer(width * height * 4)
	);
	texture->acquireReference();
	texture->setUseCompression(false);
	texture->setUseMipMap(false);
	texture->setRepeat(false);
	Engine::getRendererBackend()->resizeColorBufferTexture(colorBufferTextureId, width, height);
	this->width = width;
	this->height = height;
}

void DynamicColorTexture::dispose()
{
	Engine::getRendererBackend()->disposeTexture(colorBufferTextureId);
	texture->releaseReference();
}

void DynamicColorTexture::update()
{
	Engine::getRendererBackend()->bindTexture(Engine::getRendererBackend()->CONTEXTINDEX_DEFAULT, colorBufferTextureId);
	Engine::getRendererBackend()->uploadTexture(Engine::getRendererBackend()->CONTEXTINDEX_DEFAULT, texture);
	Engine::getRendererBackend()->bindTexture(Engine::getRendererBackend()->CONTEXTINDEX_DEFAULT, Engine::getRendererBackend()->ID_NONE);
}
