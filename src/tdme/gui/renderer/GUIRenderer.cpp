#include <tdme/gui/renderer/GUIRenderer.h>

#include <array>
#include <memory>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/manager/VBOManager_VBOManaged.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/renderer/GUIShader.h>
#include <tdme/gui/GUI.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix3x3.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/FloatBuffer.h>
#include <tdme/utilities/IntBuffer.h>
#include <tdme/utilities/ShortBuffer.h>
#include <tdme/utilities/Time.h>

using std::array;
using std::unique_ptr;

using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::manager::VBOManager_VBOManaged;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::renderer::GUIRenderer;
using tdme::gui::renderer::GUIShader;
using tdme::gui::GUI;
using tdme::math::Math;
using tdme::math::Matrix3x3;
using tdme::utilities::ByteBuffer;
using tdme::utilities::Console;
using tdme::utilities::FloatBuffer;
using tdme::utilities::IntBuffer;
using tdme::utilities::ShortBuffer;
using tdme::utilities::Time;

GUIRenderer::GUIRenderer(Renderer* renderer)
{
	this->renderer = renderer;
	sbIndicesByteBuffer = unique_ptr<ByteBuffer>(ByteBuffer::allocate(QUAD_COUNT * 6 * (renderer->isUsingShortIndices() == true?sizeof(uint16_t):sizeof(uint32_t))));
	fbVertices = (fbVerticesByteBuffer = unique_ptr<ByteBuffer>(ByteBuffer::allocate(QUAD_COUNT * 6 * 3 * sizeof(float))))->asFloatBuffer();
	fbColors = (fbColorsByteBuffer = unique_ptr<ByteBuffer>(ByteBuffer::allocate(QUAD_COUNT * 6 * 4 * sizeof(float))))->asFloatBuffer();
	fbSolidColors = (fbSolidColorsByteBuffer = unique_ptr<ByteBuffer>(ByteBuffer::allocate(QUAD_COUNT * 6 * 1 * sizeof(float))))->asFloatBuffer();
	fbTextureCoordinates = (fbTextureCoordinatesByteBuffer = unique_ptr<ByteBuffer>(ByteBuffer::allocate(QUAD_COUNT * 6 * 2 * sizeof(float))))->asFloatBuffer();
	renderAreaLeft = 0.0f;
	renderAreaTop = 0.0f;
	renderAreaRight = 0.0f;
	renderAreaBottom = 0.0f;
	renderOffsetX = 0.0f;
	renderOffsetY = 0.0f;
	guiEffectOffsetX = 0.0f;
	guiEffectOffsetY = 0.0f;
}

GUIRenderer::~GUIRenderer() {
}

void GUIRenderer::initialize()
{
	if (vboIds == nullptr) {
		auto created = false;
		auto vboManaged = Engine::getInstance()->getVBOManager()->addVBO("tdme.guirenderer", 5, false, false, created);
		vboIds = vboManaged->getVBOIds();
		if (renderer->isUsingShortIndices() == true) {
			auto sbIndices = sbIndicesByteBuffer->asShortBuffer();
			for (auto i = 0; i < QUAD_COUNT; i++) {
				sbIndices.put(static_cast<uint16_t>((i * 4 + 0)));
				sbIndices.put(static_cast<uint16_t>((i * 4 + 1)));
				sbIndices.put(static_cast<uint16_t>((i * 4 + 2)));
				sbIndices.put(static_cast<uint16_t>((i * 4 + 2)));
				sbIndices.put(static_cast<uint16_t>((i * 4 + 3)));
				sbIndices.put(static_cast<uint16_t>((i * 4 + 0)));
			}
			renderer->uploadIndicesBufferObject(renderer->CONTEXTINDEX_DEFAULT, (*vboIds)[0], sbIndices.getPosition() * sizeof(uint16_t), &sbIndices);
		} else {
			auto ibIndices = sbIndicesByteBuffer->asIntBuffer();
			for (auto i = 0; i < QUAD_COUNT; i++) {
				ibIndices.put(i * 4 + 0);
				ibIndices.put(i * 4 + 1);
				ibIndices.put(i * 4 + 2);
				ibIndices.put(i * 4 + 2);
				ibIndices.put(i * 4 + 3);
				ibIndices.put(i * 4 + 0);
			}
			renderer->uploadIndicesBufferObject(renderer->CONTEXTINDEX_DEFAULT, (*vboIds)[0], ibIndices.getPosition() * sizeof(uint32_t), &ibIndices);
		}
	}
}

void GUIRenderer::dispose()
{
	if (vboIds != nullptr) {
		Engine::getInstance()->getVBOManager()->removeVBO("tdme.guirenderer");
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
	renderer->getTextureMatrix(renderer->CONTEXTINDEX_DEFAULT).identity();
}

void GUIRenderer::doneRendering()
{
	renderer->unbindBufferObjects(renderer->CONTEXTINDEX_DEFAULT);
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
	guiEffectColorMul = GUIColor::GUICOLOR_WHITE;
	guiEffectColorAdd = GUIColor::GUICOLOR_BLACK;
}

void GUIRenderer::setGUIEffectOffsetX(float guiEffectOffsetX)
{
	this->guiEffectOffsetX = guiEffectOffsetX;
	screenNode->setGUIEffectOffsetX(static_cast<int>((guiEffectOffsetX * screenNode->getScreenWidth() / 2.0f)));
}

void GUIRenderer::setGUIEffectOffsetY(float guiEffectOffsetY)
{
	this->guiEffectOffsetY = guiEffectOffsetY;
	screenNode->setGUIEffectOffsetY(static_cast<int>((guiEffectOffsetY * screenNode->getScreenHeight() / 2.0f)));
}

void GUIRenderer::setTexureMatrix(const Matrix3x3& textureMatrix) {
	renderer->getTextureMatrix(renderer->CONTEXTINDEX_DEFAULT).set(textureMatrix);
}

void GUIRenderer::bindTexture(int32_t textureId)
{
	renderer->bindTexture(renderer->CONTEXTINDEX_DEFAULT, textureId);
}

void GUIRenderer::bindMask(int32_t textureId)
{
	renderer->setTextureUnit(renderer->CONTEXTINDEX_DEFAULT, 1);
	renderer->bindTexture(renderer->CONTEXTINDEX_DEFAULT, textureId);
	renderer->setTextureUnit(renderer->CONTEXTINDEX_DEFAULT, 0);
}

void GUIRenderer::setMaskMaxValue(float maskMaxValue) {
	renderer->setMaskMaxValue(renderer->CONTEXTINDEX_DEFAULT, maskMaxValue);
}

void GUIRenderer::setGradient(int count, array<GUIColor, 10>& colors, array<float, 10>& colorStarts, float rotationAngle) {
	Engine::guiShader->setGradient(count, colors, colorStarts, rotationAngle);
}

void GUIRenderer::unsetGradient() {
	Engine::guiShader->unsetGradient();
}

void GUIRenderer::render()
{
	if (quadCount == 0) {
		fontColor = GUIColor::GUICOLOR_WHITE.getArray();
		effectColorMul = GUIColor::GUICOLOR_WHITE.getArray();
		effectColorAdd = GUIColor::GUICOLOR_BLACK.getArray();
		return;
	}
	// use default context
	auto contextIdx = renderer->CONTEXTINDEX_DEFAULT;
	renderer->uploadBufferObject(contextIdx, (*vboIds)[1], fbVertices.getPosition() * sizeof(float), &fbVertices);
	renderer->uploadBufferObject(contextIdx, (*vboIds)[2], fbSolidColors.getPosition() * sizeof(float), &fbSolidColors);
	renderer->uploadBufferObject(contextIdx, (*vboIds)[3], fbTextureCoordinates.getPosition() * sizeof(float), &fbTextureCoordinates);
	renderer->uploadBufferObject(contextIdx, (*vboIds)[4], fbColors.getPosition() * sizeof(float), &fbColors);
	renderer->bindIndicesBufferObject(contextIdx, (*vboIds)[0]);
	renderer->bindVertices2BufferObject(contextIdx, (*vboIds)[1]);
	renderer->bindSolidColorsBufferObject(contextIdx, (*vboIds)[2]);
	renderer->bindTextureCoordinatesBufferObject(contextIdx, (*vboIds)[3]);
	renderer->bindColorsBufferObject(contextIdx, (*vboIds)[4]);
	effectColorMulFinal[0] = guiEffectColorMul[0] * effectColorMul[0] * fontColor[0];
	effectColorMulFinal[1] = guiEffectColorMul[1] * effectColorMul[1] * fontColor[1];
	effectColorMulFinal[2] = guiEffectColorMul[2] * effectColorMul[2] * fontColor[2];
	effectColorMulFinal[3] = guiEffectColorMul[3] * effectColorMul[3] * fontColor[3];
	effectColorAddFinal[0] = guiEffectColorAdd[0] + effectColorAdd[0];
	effectColorAddFinal[1] = guiEffectColorAdd[1] + effectColorAdd[1];
	effectColorAddFinal[2] = guiEffectColorAdd[2] + effectColorAdd[2];
	effectColorAddFinal[3] = 0.0f;
	renderer->getEffectColorMul(contextIdx) = effectColorMulFinal;
	renderer->getEffectColorAdd(contextIdx) = effectColorAddFinal;
	renderer->onUpdateEffect(contextIdx);
	renderer->onUpdateTextureMatrix(contextIdx);
	renderer->drawIndexedTrianglesFromBufferObjects(contextIdx, quadCount * 2, 0);
	quadCount = 0;
	fbVertices.clear();
	fbSolidColors.clear();
	fbTextureCoordinates.clear();
	fbColors.clear();
	fontColor = GUIColor::GUICOLOR_WHITE.getArray();
	effectColorMul = GUIColor::GUICOLOR_WHITE.getArray();
	effectColorAdd = GUIColor::GUICOLOR_BLACK.getArray();
	effectColorAdd[3] = 0.0f;
	guiEffectColorAdd[3] = 0.0f;
}

