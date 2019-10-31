#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/FloatBuffer.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderPoint.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using std::vector;

using tdme::utils::ByteBuffer;
using tdme::utils::FloatBuffer;
using tdme::engine::subsystems::rendering::TransparentRenderPoint;
using tdme::engine::subsystems::renderer::Renderer;

/** 
 * Batch renderer for points
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::subsystems::rendering::BatchRendererPoints final
{
	friend class Object3DRenderer;

private:
	static constexpr int32_t POINT_COUNT { 65535 };
	Renderer* renderer { nullptr };
	vector<int32_t>* vboIds { nullptr };
	int32_t id;
	bool acquired;
	ByteBuffer* fbVerticesByteBuffer { nullptr };
	FloatBuffer fbVertices;
	ByteBuffer* fbColorsByteBuffer { nullptr };
	FloatBuffer fbColors;

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
	inline void addPoint(const TransparentRenderPoint* point) {
		fbVertices.put(point->point.getArray());
		fbColors.put(point->color.getArray());
	}

	/**
	 * @return has points
	 */
	inline bool hasPoints() {
		return fbVertices.getPosition() > 0;
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
