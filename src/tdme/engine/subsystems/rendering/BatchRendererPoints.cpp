#include <tdme/engine/subsystems/rendering/BatchRendererPoints.h>

#include <string>

#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/FloatBuffer.h>
#include <tdme/utilities/ShortBuffer.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/subsystems/manager/VBOManager_VBOManaged.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderPoint.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/math/Vector3.h>

using std::string;
using std::to_string;

using tdme::engine::subsystems::rendering::BatchRendererPoints;

using tdme::utilities::ByteBuffer;
using tdme::utilities::FloatBuffer;
using tdme::engine::Engine;
using tdme::engine::model::Color4;
using tdme::engine::subsystems::manager::VBOManager_VBOManaged;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::rendering::TransparentRenderPoint;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::math::Vector3;

constexpr int32_t BatchRendererPoints::POINT_COUNT;

BatchRendererPoints::BatchRendererPoints(Renderer* renderer, int32_t id)
{
	this->id = id;
	this->renderer = renderer;
	this->acquired = false;
	fbVertices = (fbVerticesByteBuffer = ByteBuffer::allocate(POINT_COUNT * 3 * sizeof(float)))->asFloatBuffer();
	sbTextureIndices = (sbTexureIndicesByteBuffer = ByteBuffer::allocate(POINT_COUNT * sizeof(uint16_t)))->asShortBuffer();
	sbSpriteIndices = (sbSpriteIndicesByteBuffer = ByteBuffer::allocate(POINT_COUNT * sizeof(uint16_t)))->asShortBuffer();
	fbColors = (fbColorsByteBuffer = ByteBuffer::allocate(POINT_COUNT * 4 * sizeof(float)))->asFloatBuffer();
	fbPointSizes = (fbPointSizesByteBuffer = ByteBuffer::allocate(POINT_COUNT * sizeof(float)))->asFloatBuffer();
	sbSpriteSheetDimension = (sbSpriteSheetDimensionByteBuffer = ByteBuffer::allocate(POINT_COUNT * 2 * sizeof(uint16_t)))->asShortBuffer();
	fbEffectColorMul = (fbEffectColorMulByteBuffer = ByteBuffer::allocate(POINT_COUNT * 4 * sizeof(float)))->asFloatBuffer();
	fbEffectColorAdd = (fbEffectColorAddByteBuffer = ByteBuffer::allocate(POINT_COUNT * 4 * sizeof(float)))->asFloatBuffer();
}

BatchRendererPoints::~BatchRendererPoints()
{
	delete fbVerticesByteBuffer;
	delete sbTexureIndicesByteBuffer;
	delete sbSpriteIndicesByteBuffer;
	delete fbColorsByteBuffer;
	delete fbPointSizesByteBuffer;
	delete sbSpriteSheetDimensionByteBuffer;
	delete fbEffectColorMulByteBuffer;
	delete fbEffectColorAddByteBuffer;
}

void BatchRendererPoints::initialize()
{
	// initialize if not yet done
	if (vboIds == nullptr) {
		auto created = false;
		auto vboManaged = Engine::getInstance()->getVBOManager()->addVBO("tdme.batchvborendererpoints." + to_string(id), 8, false, false, created);
		vboIds = vboManaged->getVBOIds();
	}
}

void BatchRendererPoints::render(void* context)
{
	// skip if no vertex data exists
	if (fbVertices.getPosition() == 0)
		return;

	// determine point count
	auto points = fbVertices.getPosition() / 3;
	// upload
	renderer->uploadBufferObject(context, (*vboIds)[0], fbVertices.getPosition() * sizeof(float), &fbVertices);
	renderer->uploadBufferObject(context, (*vboIds)[1], sbTextureIndices.getPosition() * sizeof(uint16_t), &sbTextureIndices);
	renderer->uploadBufferObject(context, (*vboIds)[2], sbSpriteIndices.getPosition() * sizeof(uint16_t), &sbSpriteIndices);
	renderer->uploadBufferObject(context, (*vboIds)[3], fbColors.getPosition() * sizeof(float), &fbColors);
	renderer->uploadBufferObject(context, (*vboIds)[4], sbSpriteSheetDimension.getPosition() * sizeof(uint16_t), &sbSpriteSheetDimension);
	renderer->uploadBufferObject(context, (*vboIds)[5], fbPointSizes.getPosition() * sizeof(float), &fbPointSizes);
	renderer->uploadBufferObject(context, (*vboIds)[6], fbEffectColorMul.getPosition() * sizeof(float), &fbEffectColorMul);
	renderer->uploadBufferObject(context, (*vboIds)[7], fbEffectColorAdd.getPosition() * sizeof(float), &fbEffectColorAdd);
	// bind vertices
	renderer->bindVerticesBufferObject(context, (*vboIds)[0]);
	// bind texture indices
	renderer->bindTextureIndicesBufferObject(context, (*vboIds)[1]);
	// bind sprite indices
	renderer->bindSpriteIndicesBufferObject(context, (*vboIds)[2]);
	// bind colors
	renderer->bindColorsBufferObject(context, (*vboIds)[3]);
	// bind sprite sheet dimension
	renderer->bindSpriteSheetDimensionBufferObject(context, (*vboIds)[4]);
	// bind point sizes
	renderer->bindPointSizesBufferObject(context, (*vboIds)[5]);
	// bind effect color mul
	renderer->bindEffectColorMulsBufferObject(context, (*vboIds)[6], 0);
	// bind effect color add
	renderer->bindEffectColorAddsBufferObject(context, (*vboIds)[7], 0);
	// draw
	renderer->drawPointsFromBufferObjects(context, points, 0);
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
	sbTextureIndices.clear();
	sbSpriteIndices.clear();
	fbColors.clear();
	fbPointSizes.clear();
	sbSpriteSheetDimension.clear();
	fbEffectColorMul.clear();
	fbEffectColorAdd.clear();
}
