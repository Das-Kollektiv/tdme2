#include <tdme/engine/subsystems/rendering/BatchRendererPoints.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderPoint.h>
#include <tdme/engine/Engine.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/FloatBuffer.h>
#include <tdme/utilities/ShortBuffer.h>

using std::string;
using std::to_string;

using tdme::engine::subsystems::rendering::BatchRendererPoints;

using tdme::engine::Color4;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::rendering::TransparentRenderPoint;
using tdme::engine::Engine;
using tdme::math::Vector3;
using tdme::utilities::ByteBuffer;
using tdme::utilities::FloatBuffer;

constexpr int32_t BatchRendererPoints::POINT_COUNT;

BatchRendererPoints::BatchRendererPoints(Renderer* renderer, int32_t id)
{
	this->id = id;
	this->renderer = renderer;
	this->acquired = false;
	fbVertices = (fbVerticesByteBuffer = unique_ptr<ByteBuffer>(ByteBuffer::allocate(POINT_COUNT * 3 * sizeof(float))))->asFloatBuffer();
	fbColors = (fbColorsByteBuffer = unique_ptr<ByteBuffer>(ByteBuffer::allocate(POINT_COUNT * 4 * sizeof(float))))->asFloatBuffer();
	fbPointSizes = (fbPointSizesByteBuffer = unique_ptr<ByteBuffer>(ByteBuffer::allocate(POINT_COUNT * sizeof(float))))->asFloatBuffer();
	fbEffectColorMul = (fbEffectColorMulByteBuffer = unique_ptr<ByteBuffer>(ByteBuffer::allocate(POINT_COUNT * 4 * sizeof(float))))->asFloatBuffer();
	fbEffectColorAdd = (fbEffectColorAddByteBuffer = unique_ptr<ByteBuffer>(ByteBuffer::allocate(POINT_COUNT * 4 * sizeof(float))))->asFloatBuffer();
	if (renderer->isSupportingIntegerProgramAttributes() == true) {
		sbTextureSpriteIndices = (sbTextureSpriteIndicesByteBuffer = unique_ptr<ByteBuffer>(ByteBuffer::allocate(POINT_COUNT * 2 * sizeof(uint16_t))))->asShortBuffer();
		sbSpriteSheetDimension = (sbSpriteSheetDimensionByteBuffer = unique_ptr<ByteBuffer>(ByteBuffer::allocate(POINT_COUNT * 2 * sizeof(uint16_t))))->asShortBuffer();
	} else {
		fbTextureSpriteIndices = (fbTextureSpriteIndicesByteBuffer = unique_ptr<ByteBuffer>(ByteBuffer::allocate(POINT_COUNT * 2 * sizeof(float))))->asFloatBuffer();
		fbSpriteSheetDimension = (fbSpriteSheetDimensionByteBuffer = unique_ptr<ByteBuffer>(ByteBuffer::allocate(POINT_COUNT * 2 * sizeof(float))))->asFloatBuffer();
	}
}

BatchRendererPoints::~BatchRendererPoints()
{
}

void BatchRendererPoints::initialize()
{
	// initialize if not yet done
	if (vboIds == nullptr) {
		auto created = false;
		auto vboManaged = Engine::getInstance()->getVBOManager()->addVBO("tdme.batchvborendererpoints." + to_string(id), 7, false, false, created);
		vboIds = vboManaged->getVBOIds();
	}
}

void BatchRendererPoints::render(int contextIdx)
{
	// skip if no vertex data exists
	if (fbVertices.getPosition() == 0)
		return;

	// determine point count
	auto points = fbVertices.getPosition() / 3;
	// upload
	renderer->uploadBufferObject(contextIdx, (*vboIds)[0], fbVertices.getPosition() * sizeof(float), &fbVertices);
	renderer->uploadBufferObject(contextIdx, (*vboIds)[2], fbColors.getPosition() * sizeof(float), &fbColors);
	renderer->uploadBufferObject(contextIdx, (*vboIds)[4], fbPointSizes.getPosition() * sizeof(float), &fbPointSizes);
	renderer->uploadBufferObject(contextIdx, (*vboIds)[5], fbEffectColorMul.getPosition() * sizeof(float), &fbEffectColorMul);
	renderer->uploadBufferObject(contextIdx, (*vboIds)[6], fbEffectColorAdd.getPosition() * sizeof(float), &fbEffectColorAdd);
	if (renderer->isSupportingIntegerProgramAttributes() == true) {
		renderer->uploadBufferObject(contextIdx, (*vboIds)[1], sbTextureSpriteIndices.getPosition() * sizeof(uint16_t), &sbTextureSpriteIndices);
		renderer->uploadBufferObject(contextIdx, (*vboIds)[3], sbSpriteSheetDimension.getPosition() * sizeof(uint16_t), &sbSpriteSheetDimension);
	} else {
		renderer->uploadBufferObject(contextIdx, (*vboIds)[1], fbTextureSpriteIndices.getPosition() * sizeof(float), &fbTextureSpriteIndices);
		renderer->uploadBufferObject(contextIdx, (*vboIds)[3], fbSpriteSheetDimension.getPosition() * sizeof(float), &fbSpriteSheetDimension);
	}
	// bind vertices
	renderer->bindVerticesBufferObject(contextIdx, (*vboIds)[0]);
	// bind texture and sprite indices
	renderer->bindTextureSpriteIndicesBufferObject(contextIdx, (*vboIds)[1]);
	// bind colors
	renderer->bindColorsBufferObject(contextIdx, (*vboIds)[2]);
	// bind sprite sheet dimension
	renderer->bindSpriteSheetDimensionBufferObject(contextIdx, (*vboIds)[3]);
	// bind point sizes
	renderer->bindPointSizesBufferObject(contextIdx, (*vboIds)[4]);
	// bind effect color mul
	renderer->bindEffectColorMulsBufferObject(contextIdx, (*vboIds)[5], 0);
	// bind effect color add
	renderer->bindEffectColorAddsBufferObject(contextIdx, (*vboIds)[6], 0);
	// draw
	renderer->drawPointsFromBufferObjects(contextIdx, points, 0);
}

void BatchRendererPoints::dispose()
{
	if (vboIds != nullptr) {
		Engine::getInstance()->getVBOManager()->removeVBO("tdme.batchvborendererpoints." + to_string(id));
		vboIds = nullptr;
	}
}

void BatchRendererPoints::clear()
{
	fbVertices.clear();
	fbColors.clear();
	fbPointSizes.clear();
	fbEffectColorMul.clear();
	fbEffectColorAdd.clear();
	if (renderer->isSupportingIntegerProgramAttributes() == true) {
		sbTextureSpriteIndices.clear();
		sbSpriteSheetDimension.clear();
	} else {
		fbTextureSpriteIndices.clear();
		fbSpriteSheetDimension.clear();
	}
}
