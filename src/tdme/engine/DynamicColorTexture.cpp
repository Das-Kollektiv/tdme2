#include <tdme/engine/DynamicColorTexture.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/Engine.h>
#include <tdme/utilities/ByteBuffer.h>

using tdme::engine::Texture;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::DynamicColorTexture;
using tdme::engine::Engine;
using tdme::utilities::ByteBuffer;

uint32_t DynamicColorTexture::counter = 0;

void DynamicColorTexture::initialize()
{
	colorBufferTextureId = Engine::getRenderer()->createColorBufferTexture(width, height, Engine::getRenderer()->ID_NONE, Engine::getRenderer()->ID_NONE);
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
	Engine::getRenderer()->resizeColorBufferTexture(colorBufferTextureId, width, height);
	this->width = width;
	this->height = height;
}

void DynamicColorTexture::dispose()
{
	Engine::getRenderer()->disposeTexture(colorBufferTextureId);
	texture->releaseReference();
}

void DynamicColorTexture::update()
{
	Engine::getRenderer()->bindTexture(Engine::getRenderer()->CONTEXTINDEX_DEFAULT, colorBufferTextureId);
	Engine::getRenderer()->uploadTexture(Engine::getRenderer()->CONTEXTINDEX_DEFAULT, texture);
	Engine::getRenderer()->bindTexture(Engine::getRenderer()->CONTEXTINDEX_DEFAULT, Engine::getRenderer()->ID_NONE);
}
