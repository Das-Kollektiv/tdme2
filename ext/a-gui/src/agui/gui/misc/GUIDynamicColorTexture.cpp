#include <agui/gui/misc/GUIDynamicColorTexture.h>

#include <string>

#include <agui/agui.h>
#include <agui/gui/textures/GUITexture.h>
#include <agui/gui/renderer/GUIRendererBackend.h>
#include <agui/gui/GUI.h>
#include <agui/utilities/ByteBuffer.h>

using agui::gui::misc::GUIDynamicColorTexture;

using agui::gui::textures::GUITexture;
using agui::gui::renderer::GUIRendererBackend;

using agui::utilities::ByteBuffer;

uint32_t GUIDynamicColorTexture::counter = 0;

void GUIDynamicColorTexture::initialize()
{
	textureId = GUI::getRendererBackend()->createColorBufferTexture(
		width,
		height,
		GUI::getRendererBackend()->ID_NONE,
		GUI::getRendererBackend()->ID_NONE
	);
	texture = new GUITexture(
		"dynamic-color-texture:" + to_string(GUIDynamicColorTexture::counter++),
		GUITexture::TEXTUREDEPTH_RGBA,
		GUITexture::TEXTUREFORMAT_RGBA,
		width, height,
		width, height,
		GUITexture::TEXTUREFORMAT_RGBA,
		ByteBuffer(width * height * 4)
	);
	texture->acquireReference();
	texture->setUseCompression(false);
	texture->setUseMipMap(false);
	texture->setRepeat(false);
}

void GUIDynamicColorTexture::reshape(int32_t width, int32_t height)
{
	texture->releaseReference();
	texture = new GUITexture(
		"dynamic-color-texture:" + to_string(GUIDynamicColorTexture::counter++),
		GUITexture::TEXTUREDEPTH_RGBA,
		GUITexture::TEXTUREFORMAT_RGBA,
		width, height,
		width, height,
		GUITexture::TEXTUREFORMAT_RGBA,
		ByteBuffer(width * height * 4)
	);
	texture->acquireReference();
	texture->setUseCompression(false);
	texture->setUseMipMap(false);
	texture->setRepeat(false);
	GUI::getRendererBackend()->resizeColorBufferTexture(textureId, width, height);
	this->width = width;
	this->height = height;
}

void GUIDynamicColorTexture::dispose()
{
	GUI::getRendererBackend()->disposeTexture(textureId);
	texture->releaseReference();
}

void GUIDynamicColorTexture::update()
{
	GUI::getRendererBackend()->bindTexture(GUI::getRendererBackend()->CONTEXTINDEX_DEFAULT, textureId);
	GUI::getRendererBackend()->uploadTexture(GUI::getRendererBackend()->CONTEXTINDEX_DEFAULT, texture);
	GUI::getRendererBackend()->bindTexture(GUI::getRendererBackend()->CONTEXTINDEX_DEFAULT, GUI::getRendererBackend()->ID_NONE);
}
