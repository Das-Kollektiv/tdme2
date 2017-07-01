// Generated from /tdme/src/tdme/gui/renderer/GUIRenderer.java
#include <tdme/gui/renderer/GUIRenderer.h>

#include <java/lang/Byte.h>
#include <java/lang/Float.h>
#include <java/lang/Math.h>
#include <java/lang/Object.h>
#include <java/lang/Short.h>
#include <java/lang/String.h>
#include <java/lang/System.h>
#include <java/nio/ByteBuffer.h>
#include <java/nio/ByteOrder.h>
#include <java/nio/FloatBuffer.h>
#include <java/nio/ShortBuffer.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/subsystems/manager/VBOManager_VBOManaged.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/renderer/GUIShader.h>
#include <tdme/utils/_Console.h>
#include <Array.h>

using tdme::gui::renderer::GUIRenderer;
using java::lang::Byte;
using java::lang::Float;
using java::lang::Math;
using java::lang::Object;
using java::lang::Short;
using java::lang::String;
using java::lang::System;
using java::nio::ByteBuffer;
using java::nio::ByteOrder;
using java::nio::FloatBuffer;
using java::nio::ShortBuffer;
using tdme::engine::Engine;
using tdme::engine::subsystems::manager::VBOManager_VBOManaged;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::gui::GUI;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::renderer::GUIShader;
using tdme::utils::_Console;

GUIRenderer::GUIRenderer(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIRenderer::GUIRenderer(GLRenderer* renderer) 
	: GUIRenderer(*static_cast< ::default_init_tag* >(0))
{
	ctor(renderer);
}

void GUIRenderer::init()
{
	sbIndices = ByteBuffer::allocateDirect(QUAD_COUNT * 6 * Short::SIZE / Byte::SIZE)->asShortBuffer();
	fbVertices = ByteBuffer::allocateDirect(QUAD_COUNT * 6 * 3* Float::SIZE / Byte::SIZE)->asFloatBuffer();
	fbColors = ByteBuffer::allocateDirect(QUAD_COUNT * 6 * 4* Float::SIZE / Byte::SIZE)->asFloatBuffer();
	fbTextureCoordinates = ByteBuffer::allocateDirect(QUAD_COUNT * 6 * 2* Float::SIZE / Byte::SIZE)->asFloatBuffer();
	renderAreaLeft = 0.0f;
	renderAreaTop = 0.0f;
	renderAreaRight = 0.0f;
	renderAreaBottom = 0.0f;
	renderOffsetX = 0.0f;
	renderOffsetY = 0.0f;
	quadVertices = (new floatArray({
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f
	}));
	quadColors = (new floatArray({
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f
	}));
	quadTextureCoordinates = (new floatArray({
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f
	}));
	fontColor = new floatArray({
		1.0f,
		1.0f,
		1.0f,
		1.0f
	});
	effectColorMul = new floatArray({
		1.0f,
		1.0f,
		1.0f,
		1.0f
	});
	effectColorAdd = new floatArray({
		0.0f,
		0.0f,
		0.0f,
		0.0f
	});
	guiEffectColorMul = new floatArray({
		1.0f,
		1.0f,
		1.0f,
		1.0f
	});
	guiEffectColorAdd = new floatArray({
		0.0f,
		0.0f,
		0.0f,
		0.0f
	});
	effectColorMulFinal = new floatArray({
		1.0f,
		1.0f,
		1.0f,
		1.0f
	});
	effectColorAddFinal = new floatArray({
		0.0f,
		0.0f,
		0.0f,
		0.0f
	});
	guiEffectOffsetX = 0.0f;
	guiEffectOffsetY = 0.0f;
}

constexpr int32_t GUIRenderer::QUAD_COUNT;

constexpr float GUIRenderer::SCREEN_LEFT;

constexpr float GUIRenderer::SCREEN_TOP;

constexpr float GUIRenderer::SCREEN_RIGHT;

constexpr float GUIRenderer::SCREEN_BOTTOM;

void GUIRenderer::ctor(GLRenderer* renderer)
{
	super::ctor();
	init();
	this->renderer = renderer;
}

void GUIRenderer::setGUI(GUI* gui)
{
	this->gui = gui;
}

GUI* GUIRenderer::getGUI()
{
	return gui;
}

void GUIRenderer::initialize()
{
	if (vboIds == nullptr) {
		auto vboManaged = Engine::getInstance()->getVBOManager()->addVBO(u"tdme.guirenderer"_j, 4);
		vboIds = vboManaged->getVBOGlIds();
		for (auto i = 0; i < QUAD_COUNT; i++) {
			sbIndices->put(static_cast< int16_t >((i * 4 + 0)));
			sbIndices->put(static_cast< int16_t >((i * 4 + 1)));
			sbIndices->put(static_cast< int16_t >((i * 4 + 2)));
			sbIndices->put(static_cast< int16_t >((i * 4 + 2)));
			sbIndices->put(static_cast< int16_t >((i * 4 + 3)));
			sbIndices->put(static_cast< int16_t >((i * 4 + 0)));
		}
		// sbIndices->flip();
		renderer->uploadIndicesBufferObject((*vboIds)[0], sbIndices->limit() * Short::SIZE / Byte::SIZE, sbIndices);
	}
}

void GUIRenderer::dispose()
{
	if (vboIds != nullptr) {
		Engine::getInstance()->getVBOManager()->removeVBO(u"tdme.guirenderer"_j);
		vboIds = nullptr;
	}
}

void GUIRenderer::initRendering()
{
	setRenderAreaLeft(SCREEN_LEFT);
	setRenderAreaTop(SCREEN_TOP);
	setRenderAreaRight(SCREEN_RIGHT);
	setRenderAreaBottom(SCREEN_BOTTOM);
	Engine::getGUIShader()->useProgram();
	renderer->enableClientState(renderer->CLIENTSTATE_VERTEX_ARRAY);
	renderer->enableClientState(renderer->CLIENTSTATE_TEXTURECOORD_ARRAY);
	renderer->enableClientState(renderer->CLIENTSTATE_COLOR_ARRAY);
	renderer->bindIndicesBufferObject((*vboIds)[0]);
	renderer->bindVerticesBufferObject((*vboIds)[1]);
	renderer->bindColorsBufferObject((*vboIds)[2]);
	renderer->bindTextureCoordinatesBufferObject((*vboIds)[3]);
}

void GUIRenderer::doneRendering()
{
	renderer->unbindBufferObjects();
	renderer->disableClientState(renderer->CLIENTSTATE_VERTEX_ARRAY);
	renderer->disableClientState(renderer->CLIENTSTATE_TEXTURECOORD_ARRAY);
	renderer->disableClientState(renderer->CLIENTSTATE_COLOR_ARRAY);
	Engine::getGUIShader()->unUseProgram();
}

void GUIRenderer::initScreen(GUIScreenNode* screenNode)
{
	this->screenNode = screenNode;
	guiEffectOffsetX = 0.0f;
	guiEffectOffsetY = 0.0f;
	screenNode->setGUIEffectOffsetX(0);
	screenNode->setGUIEffectOffsetY(0);
}

void GUIRenderer::doneScreen()
{
	this->screenNode = nullptr;
	System::arraycopy(GUIColor::WHITE->getArray(), 0, guiEffectColorMul, 0, 4);
	System::arraycopy(GUIColor::BLACK->getArray(), 0, guiEffectColorAdd, 0, 4);
}

void GUIRenderer::setFontColor(GUIColor* color)
{
	System::arraycopy(color->getArray(), 0, fontColor, 0, 4);
}

void GUIRenderer::setEffectColorMul(GUIColor* color)
{
	System::arraycopy(color->getArray(), 0, effectColorMul, 0, 4);
}

void GUIRenderer::setEffectColorAdd(GUIColor* color)
{
	System::arraycopy(color->getArray(), 0, effectColorAdd, 0, 4);
}

void GUIRenderer::setGUIEffectColorMul(GUIColor* color)
{
	System::arraycopy(color->getArray(), 0, guiEffectColorMul, 0, 4);
}

void GUIRenderer::setGUIEffectColorAdd(GUIColor* color)
{
	System::arraycopy(color->getArray(), 0, guiEffectColorAdd, 0, 4);
}

float GUIRenderer::getGuiEffectOffsetX()
{
	return guiEffectOffsetX;
}

void GUIRenderer::setGUIEffectOffsetX(float guiEffectOffsetX)
{
	this->guiEffectOffsetX = guiEffectOffsetX;
	screenNode->setGUIEffectOffsetX(static_cast< int32_t >((guiEffectOffsetX * screenNode->getScreenWidth() / 2.0f)));
}

float GUIRenderer::getGuiEffectOffsetY()
{
	return guiEffectOffsetY;
}

void GUIRenderer::setGUIEffectOffsetY(float guiEffectOffsetY)
{
	this->guiEffectOffsetY = guiEffectOffsetY;
	screenNode->setGUIEffectOffsetY(static_cast< int32_t >((guiEffectOffsetY * screenNode->getScreenHeight() / 2.0f)));
}

float GUIRenderer::getRenderAreaLeft()
{
	return renderAreaLeft;
}

void GUIRenderer::setRenderAreaLeft(float renderAreaLeft)
{
	this->renderAreaLeft = renderAreaLeft;
}

void GUIRenderer::setSubRenderAreaLeft(float renderAreaLeft)
{
	this->renderAreaLeft = renderAreaLeft > this->renderAreaLeft ? renderAreaLeft : this->renderAreaLeft;
}

float GUIRenderer::getRenderAreaTop()
{
	return renderAreaTop;
}

void GUIRenderer::setRenderAreaTop(float renderAreaTop)
{
	this->renderAreaTop = renderAreaTop;
}

void GUIRenderer::setSubRenderAreaTop(float renderAreaTop)
{
	this->renderAreaTop = renderAreaTop < this->renderAreaTop ? renderAreaTop : this->renderAreaTop;
}

float GUIRenderer::getRenderAreaRight()
{
	return renderAreaRight;
}

void GUIRenderer::setRenderAreaRight(float renderAreaRight)
{
	this->renderAreaRight = renderAreaRight;
}

void GUIRenderer::setSubRenderAreaRight(float renderAreaRight)
{
	this->renderAreaRight = renderAreaRight < this->renderAreaRight ? renderAreaRight : this->renderAreaRight;
}

float GUIRenderer::getRenderAreaBottom()
{
	return renderAreaBottom;
}

void GUIRenderer::setRenderAreaBottom(float renderAreaBottom)
{
	this->renderAreaBottom = renderAreaBottom;
}

void GUIRenderer::setSubRenderAreaBottom(float renderAreaBottom)
{
	this->renderAreaBottom = renderAreaBottom > this->renderAreaBottom ? renderAreaBottom : this->renderAreaBottom;
}

float GUIRenderer::getRenderOffsetX()
{
	return renderOffsetX;
}

void GUIRenderer::setRenderOffsetX(float renderOffsetX)
{
	this->renderOffsetX = renderOffsetX;
}

float GUIRenderer::getRenderOffsetY()
{
	return renderOffsetY;
}

void GUIRenderer::setRenderOffsetY(float renderOffsetY)
{
	this->renderOffsetY = renderOffsetY;
}

void GUIRenderer::addQuad(float x1, float y1, float colorR1, float colorG1, float colorB1, float colorA1, float tu1, float tv1, float x2, float y2, float colorR2, float colorG2, float colorB2, float colorA2, float tu2, float tv2, float x3, float y3, float colorR3, float colorG3, float colorB3, float colorA3, float tu3, float tv3, float x4, float y4, float colorR4, float colorG4, float colorB4, float colorA4, float tu4, float tv4)
{
	if (quadCount > QUAD_COUNT) {
		_Console::println(static_cast< Object* >(u"GUIRenderer::addQuad()::too many quads"_j));
		return;
	}
	x1 -= renderOffsetX;
	x2 -= renderOffsetX;
	x3 -= renderOffsetX;
	x4 -= renderOffsetX;
	y1 += renderOffsetY;
	y2 += renderOffsetY;
	y3 += renderOffsetY;
	y4 += renderOffsetY;
	x1 -= guiEffectOffsetX;
	x2 -= guiEffectOffsetX;
	x3 -= guiEffectOffsetX;
	x4 -= guiEffectOffsetX;
	y1 += guiEffectOffsetY;
	y2 += guiEffectOffsetY;
	y3 += guiEffectOffsetY;
	y4 += guiEffectOffsetY;
	auto renderAreaTop = this->renderAreaTop;
	auto renderAreaBottom = this->renderAreaBottom;
	auto renderAreaRight = this->renderAreaRight;
	auto renderAreaLeft = this->renderAreaLeft;
	renderAreaTop = Math::min(renderAreaTop + guiEffectOffsetY, SCREEN_TOP);
	renderAreaBottom = Math::max(renderAreaBottom + guiEffectOffsetY, SCREEN_BOTTOM);
	renderAreaRight = Math::min(renderAreaRight - guiEffectOffsetX, SCREEN_RIGHT);
	renderAreaLeft = Math::max(renderAreaLeft - guiEffectOffsetX, SCREEN_LEFT);
	auto quadBottom = y3;
	if (quadBottom > renderAreaTop) {
		return;
	}
	auto quadTop = y1;
	if (quadTop < renderAreaBottom) {
		return;
	}
	auto quadLeft = x1;
	if (quadLeft > renderAreaRight) {
		return;
	}
	auto quadRight = x2;
	if (quadRight < renderAreaLeft) {
		return;
	}
	if (quadBottom < renderAreaBottom) {
		tv3 = tv1 + ((tv3 - tv1) * ((y1 - renderAreaBottom) / (y1 - y3)));
		tv4 = tv2 + ((tv4 - tv2) * ((y2 - renderAreaBottom) / (y1 - y4)));
		y3 = renderAreaBottom;
		y4 = renderAreaBottom;
	}
	if (quadTop > renderAreaTop) {
		tv1 = tv1 + ((tv3 - tv1) * ((y1 - renderAreaTop) / (y1 - y3)));
		tv2 = tv2 + ((tv4 - tv2) * ((y2 - renderAreaTop) / (y1 - y4)));
		y1 = renderAreaTop;
		y2 = renderAreaTop;
	}
	if (quadLeft < renderAreaLeft) {
		tu1 = tu1 + ((tu2 - tu1) * ((renderAreaLeft - x1) / (x2 - x1)));
		tu4 = tu4 + ((tu3 - tu4) * ((renderAreaLeft - x4) / (x3 - x4)));
		x1 = renderAreaLeft;
		x4 = renderAreaLeft;
	}
	if (quadRight > renderAreaRight) {
		tu2 = tu2 - ((tu2 - tu1) * ((x2 - renderAreaRight) / (x2 - x1)));
		tu3 = tu3 - ((tu3 - tu4) * ((x3 - renderAreaRight) / (x3 - x4)));
		x2 = renderAreaRight;
		x3 = renderAreaRight;
	}
	auto quad = 0;
	(*quadVertices)[quad * 3 + 0] = x1;
	(*quadVertices)[quad * 3 + 1] = y1;
	(*quadVertices)[quad * 3 + 2] = 0.0f;
	(*quadColors)[quad * 4 + 0] = colorR1;
	(*quadColors)[quad * 4 + 1] = colorG1;
	(*quadColors)[quad * 4 + 2] = colorB1;
	(*quadColors)[quad * 4 + 3] = colorA1;
	(*quadTextureCoordinates)[quad * 2 + 0] = tu1;
	(*quadTextureCoordinates)[quad * 2 + 1] = tv1;
	quad++;
	(*quadVertices)[quad * 3 + 0] = x2;
	(*quadVertices)[quad * 3 + 1] = y2;
	(*quadVertices)[quad * 3 + 2] = 0.0f;
	(*quadColors)[quad * 4 + 0] = colorR2;
	(*quadColors)[quad * 4 + 1] = colorG2;
	(*quadColors)[quad * 4 + 2] = colorB2;
	(*quadColors)[quad * 4 + 3] = colorA2;
	(*quadTextureCoordinates)[quad * 2 + 0] = tu2;
	(*quadTextureCoordinates)[quad * 2 + 1] = tv2;
	quad++;
	(*quadVertices)[quad * 3 + 0] = x3;
	(*quadVertices)[quad * 3 + 1] = y3;
	(*quadVertices)[quad * 3 + 2] = 0.0f;
	(*quadColors)[quad * 4 + 0] = colorR3;
	(*quadColors)[quad * 4 + 1] = colorG3;
	(*quadColors)[quad * 4 + 2] = colorB3;
	(*quadColors)[quad * 4 + 3] = colorA3;
	(*quadTextureCoordinates)[quad * 2 + 0] = tu3;
	(*quadTextureCoordinates)[quad * 2 + 1] = tv3;
	quad++;
	(*quadVertices)[quad * 3 + 0] = x4;
	(*quadVertices)[quad * 3 + 1] = y4;
	(*quadVertices)[quad * 3 + 2] = 0.0f;
	(*quadColors)[quad * 4 + 0] = colorR4;
	(*quadColors)[quad * 4 + 1] = colorG4;
	(*quadColors)[quad * 4 + 2] = colorB4;
	(*quadColors)[quad * 4 + 3] = colorA4;
	(*quadTextureCoordinates)[quad * 2 + 0] = tu4;
	(*quadTextureCoordinates)[quad * 2 + 1] = tv4;
	fbVertices->put(quadVertices);
	fbColors->put(quadColors);
	fbTextureCoordinates->put(quadTextureCoordinates);
	quadCount++;
}

void GUIRenderer::bindTexture(int32_t textureId)
{
	renderer->bindTexture(textureId);
}

void GUIRenderer::render()
{
	if (quadCount == 0) {
		System::arraycopy(GUIColor::WHITE->getArray(), 0, fontColor, 0, 4);
		System::arraycopy(GUIColor::WHITE->getArray(), 0, effectColorMul, 0, 4);
		System::arraycopy(GUIColor::BLACK->getArray(), 0, effectColorAdd, 0, 4);
		return;
	}
	/*
	fbVertices->flip();
	fbColors->flip();
	fbTextureCoordinates->flip();
	*/
	renderer->uploadBufferObject((*vboIds)[1], fbVertices->limit() * Float::SIZE / Byte::SIZE, fbVertices);
	renderer->uploadBufferObject((*vboIds)[2], fbColors->limit() * Float::SIZE / Byte::SIZE, fbColors);
	renderer->uploadBufferObject((*vboIds)[3], fbTextureCoordinates->limit() * Float::SIZE / Byte::SIZE, fbTextureCoordinates);
	(*effectColorMulFinal)[0] = (*guiEffectColorMul)[0] * (*effectColorMul)[0] * (*fontColor)[0];
	(*effectColorMulFinal)[1] = (*guiEffectColorMul)[1] * (*effectColorMul)[1] * (*fontColor)[1];
	(*effectColorMulFinal)[2] = (*guiEffectColorMul)[2] * (*effectColorMul)[2] * (*fontColor)[2];
	(*effectColorMulFinal)[3] = (*guiEffectColorMul)[3] * (*effectColorMul)[3] * (*fontColor)[3];
	(*effectColorAddFinal)[0] = (*guiEffectColorAdd)[0] + (*effectColorAdd)[0];
	(*effectColorAddFinal)[1] = (*guiEffectColorAdd)[1] + (*effectColorAdd)[1];
	(*effectColorAddFinal)[2] = (*guiEffectColorAdd)[2] + (*effectColorAdd)[2];
	(*effectColorAddFinal)[3] = 0.0f;
	renderer->setEffectColorMul(effectColorMulFinal);
	renderer->setEffectColorAdd(effectColorAddFinal);
	renderer->onUpdateEffect();
	renderer->drawIndexedTrianglesFromBufferObjects(quadCount * 2, 0);
	quadCount = 0;
	fbVertices->clear();
	fbColors->clear();
	fbTextureCoordinates->clear();
	System::arraycopy(GUIColor::WHITE->getArray(), 0, fontColor, 0, 4);
	System::arraycopy(GUIColor::WHITE->getArray(), 0, effectColorMul, 0, 4);
	System::arraycopy(GUIColor::BLACK->getArray(), 0, effectColorAdd, 0, 4);
	(*effectColorAdd)[3] = 0.0f;
	(*guiEffectColorAdd)[3] = 0.0f;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIRenderer::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.renderer.GUIRenderer", 29);
    return c;
}

java::lang::Class* GUIRenderer::getClass0()
{
	return class_();
}

