#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/FloatBuffer.h>
#include <tdme/utilities/ShortBuffer.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderPoint.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using std::to_string;
using std::vector;

using tdme::engine::model::Color4;
using tdme::utilities::ByteBuffer;
using tdme::utilities::FloatBuffer;
using tdme::utilities::ShortBuffer;
using tdme::engine::subsystems::rendering::TransparentRenderPoint;
using tdme::engine::subsystems::renderer::Renderer;

/** 
 * Batch renderer for points
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::subsystems::rendering::BatchRendererPoints final
{
	friend class EntityRenderer;

private:
	static constexpr int32_t POINT_COUNT { 65535 };
	Renderer* renderer { nullptr };
	vector<int32_t>* vboIds { nullptr };
	int32_t id;
	bool acquired;
	ByteBuffer* fbVerticesByteBuffer { nullptr };
	FloatBuffer fbVertices;
	ByteBuffer* sbTexureIndicesByteBuffer { nullptr };
	ShortBuffer sbTextureIndices;
	ByteBuffer* sbSpriteIndicesByteBuffer { nullptr };
	ShortBuffer sbSpriteIndices;
	ByteBuffer* fbColorsByteBuffer { nullptr };
	FloatBuffer fbColors;
	ByteBuffer* fbPointSizesByteBuffer { nullptr };
	FloatBuffer fbPointSizes;
	ByteBuffer* sbSpriteSheetDimensionByteBuffer { nullptr };
	ShortBuffer sbSpriteSheetDimension;
	ByteBuffer* fbEffectColorMulByteBuffer { nullptr };
	FloatBuffer fbEffectColorMul;
	ByteBuffer* fbEffectColorAddByteBuffer { nullptr };
	FloatBuffer fbEffectColorAdd;

	/**
	 * Render
	 * @param context context
	 */
	void render(void* context);

	/**
	 * Clears this batch vbo renderer
	 */
	void clear();

	/**
	 * Adds a transparent render point to this transparent render points
	 * @param point transparent render point
	 */
	inline void addPoint(const TransparentRenderPoint* point, int textureIndex, float pointSize, const Color4& effectColorMul, const Color4& effectColorAdd, int textureHorizontalSprites, int textureVerticalSprites) {
		fbVertices.put(point->point.getArray());
		sbTextureIndices.put(textureIndex);
		sbSpriteIndices.put(point->spriteIndex);
		fbColors.put(point->color.getArray());
		fbPointSizes.put(pointSize);
		sbSpriteSheetDimension.put(textureHorizontalSprites);
		sbSpriteSheetDimension.put(textureVerticalSprites);
		fbEffectColorMul.put(effectColorMul.getArray());
		fbEffectColorAdd.put(effectColorAdd.getArray());
	}

	/**
	 * @return has points
	 */
	inline bool hasPoints() {
		return fbVertices.getPosition() > 0;
	}

	inline int getPointCount() {
		return fbVertices.getPosition() / 3;
	}

	/**
	 * Public constructor
	 */
	BatchRendererPoints(Renderer* renderer, int32_t id);

	/**
	 * Destructor
	 */
	~BatchRendererPoints();

public:

	/** 
	 * @return acquired
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
