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
using tdme::engine::subsystems::renderer::GLRenderer;

/** 
 * Batch VBO renderer for points
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::subsystems::rendering::BatchVBORendererPoints final
{
	friend class Object3DVBORenderer;

private:
	static constexpr int32_t POINT_COUNT { 65535 };
	GLRenderer* renderer {  };
	vector<int32_t>* vboIds {  };
	int32_t id {  };
	bool acquired {  };
	ByteBuffer* fbVerticesByteBuffer;
	FloatBuffer fbVertices {  };
	ByteBuffer* fbColorsByteBuffer;
	FloatBuffer fbColors {  };

	/**
	 * Render
	 */
	void render();

	/**
	 * Clears this batch vbo renderer
	 */
	void clear();

	/**
	 * Adds a transparent render point to this transparent render points
	 * @param point transparent render point
	 */
	inline void addPoint(const TransparentRenderPoint& point) {
		fbVertices.put(point.point.getArray());
		fbColors.put(point.color.getArray());
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
	BatchVBORendererPoints(GLRenderer* renderer, int32_t id);

	/**
	 * Destructor
	 */
	~BatchVBORendererPoints();

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
