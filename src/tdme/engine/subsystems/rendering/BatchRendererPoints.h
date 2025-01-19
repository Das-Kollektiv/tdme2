#pragma once

#include <memory>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderPoint.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/FloatBuffer.h>
#include <tdme/utilities/ShortBuffer.h>

using std::unique_ptr;
using std::to_string;
using std::vector;

using tdme::engine::Color4;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::subsystems::rendering::TransparentRenderPoint;
using tdme::utilities::ByteBuffer;
using tdme::utilities::FloatBuffer;
using tdme::utilities::ShortBuffer;

/**
 * Batch renderer for points
 * @author andreas.drewke
 */
class tdme::engine::subsystems::rendering::BatchRendererPoints final
{
	friend class EntityRenderer;

private:
	static constexpr int32_t POINT_COUNT { 65535 };
	RendererBackend* rendererBackend { nullptr };
	vector<int32_t>* vboIds { nullptr };
	int32_t id;
	bool acquired;
	unique_ptr<ByteBuffer> fbVerticesByteBuffer;
	FloatBuffer fbVertices;
	unique_ptr<ByteBuffer> sbTextureSpriteIndicesByteBuffer;
	ShortBuffer sbTextureSpriteIndices;
	unique_ptr<ByteBuffer> fbColorsByteBuffer;
	FloatBuffer fbColors;
	unique_ptr<ByteBuffer> fbPointSizesByteBuffer;
	FloatBuffer fbPointSizes;
	unique_ptr<ByteBuffer> sbSpriteSheetDimensionByteBuffer;
	ShortBuffer sbSpriteSheetDimension;
	unique_ptr<ByteBuffer> fbEffectColorMulByteBuffer;
	FloatBuffer fbEffectColorMul;
	unique_ptr<ByteBuffer> fbEffectColorAddByteBuffer;
	FloatBuffer fbEffectColorAdd;

	unique_ptr<ByteBuffer> fbTextureSpriteIndicesByteBuffer;
	FloatBuffer fbTextureSpriteIndices;
	unique_ptr<ByteBuffer> fbSpriteSheetDimensionByteBuffer;
	FloatBuffer fbSpriteSheetDimension;

public:
	// forbid class copy
	FORBID_CLASS_COPY(BatchRendererPoints)

	/**
	 * Public constructor
	 * @param rendererBackend renderer backend
	 * @param id id
	 */
	BatchRendererPoints(RendererBackend* rendererBackend, int32_t id);

	/**
	 * Destructor
	 */
	~BatchRendererPoints();

	/**
	 * Render
	 * @param contextIdx context index
	 */
	void render(int contextIdx);

	/**
	 * Clears this batch vbo rendererBackend
	 */
	void clear();

	/**
	 * Adds a transparent render point to this transparent render points
	 * @param point transparent render point
	 * @param atlasTextureIndex atlas texture index
	 * @param pointSize point size
	 * @param effectColorMul effect color mul
	 * @param effectColorAdd effect color add
	 * @param textureHorizontalSprites texture horizontal sprites
	 * @param textureVerticalSprites texture vertical sprites
	 */
	inline void addPoint(const TransparentRenderPoint* point, int atlasTextureIndex, float pointSize, const Color4& effectColorMul, const Color4& effectColorAdd, int textureHorizontalSprites, int textureVerticalSprites) {
		fbVertices.put(point->point.getArray());
		sbTextureSpriteIndices.put(atlasTextureIndex);
		sbTextureSpriteIndices.put(point->spriteIndex);
		fbColors.put(point->color.getArray());
		fbPointSizes.put(pointSize);
		sbSpriteSheetDimension.put(textureHorizontalSprites);
		sbSpriteSheetDimension.put(textureVerticalSprites);
		fbEffectColorMul.put(effectColorMul.getArray());
		fbEffectColorAdd.put(effectColorAdd.getArray());
	}

	/**
	 * Adds a transparent render point to this transparent render points
	 * @param point transparent render point
	 * @param atlasTextureIndex atlas texture index
	 * @param pointSize point size
	 * @param effectColorMul effect color mul
	 * @param effectColorAdd effect color add
	 * @param textureHorizontalSprites texture horizontal sprites
	 * @param textureVerticalSprites texture vertical sprites
	 */
	inline void addPointNoInteger(const TransparentRenderPoint* point, int atlasTextureIndex, float pointSize, const Color4& effectColorMul, const Color4& effectColorAdd, int textureHorizontalSprites, int textureVerticalSprites) {
		fbVertices.put(point->point.getArray());
		fbTextureSpriteIndices.put(static_cast<float>(atlasTextureIndex + 0.1f));
		fbTextureSpriteIndices.put(static_cast<float>(point->spriteIndex + 0.1f));
		fbColors.put(point->color.getArray());
		fbPointSizes.put(pointSize);
		fbSpriteSheetDimension.put(static_cast<float>(textureHorizontalSprites + 0.1f));
		fbSpriteSheetDimension.put(static_cast<float>(textureVerticalSprites + 0.1f));
		fbEffectColorMul.put(effectColorMul.getArray());
		fbEffectColorAdd.put(effectColorAdd.getArray());
	}

	/**
	 * @returns has points
	 */
	inline bool hasPoints() {
		return fbVertices.getPosition() > 0;
	}

	inline int getPointCount() {
		return fbVertices.getPosition() / 3;
	}

	/**
	 * @returns acquired
	 */
	inline bool isAcquired() {
		return acquired;
	}

	/**
	 * Acquire
	 */
	inline bool acquire() {
		if (acquired == true) return false;
		acquired = true;
		return true;
	}

	/**
	 * Release
	 */
	inline void release() {
		acquired = false;
	}

	/**
	 * Init
	 */
	void initialize();

	/**
	 * Dispose
	 */
	void dispose();
};
