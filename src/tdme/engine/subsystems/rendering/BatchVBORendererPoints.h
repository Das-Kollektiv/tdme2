#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/FloatBuffer.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

using std::vector;

using tdme::utils::ByteBuffer;
using tdme::utils::FloatBuffer;
using tdme::engine::subsystems::rendering::TransparentRenderPoint;
using tdme::engine::subsystems::renderer::GLRenderer;

/** 
 * Batch VBO renderer
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::subsystems::rendering::BatchVBORendererPoints final
{
	friend class Object3DVBORenderer;

private:
	static constexpr int32_t POINT_COUNT { 32768 };
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
	void addPoint(TransparentRenderPoint* point);

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
	bool isAcquired();

	/** 
	 * Acquire
	 */
	bool acquire();

	/** 
	 * Release
	 */
	void release();

	/** 
	 * Init
	 */
	void initialize();

	/** 
	 * Dispose
	 */
	void dispose();
};
