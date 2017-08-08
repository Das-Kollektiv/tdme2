// Generated from /tdme/src/tdme/engine/subsystems/object/BatchVBORendererPoints.java

#pragma once

#include <fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>

#include <Array.h>

using java::nio::FloatBuffer;
using tdme::engine::subsystems::object::TransparentRenderPoint;
using tdme::engine::subsystems::renderer::GLRenderer;

/** 
 * Batch VBO renderer
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::subsystems::object::BatchVBORendererPoints final
{
private:
	static constexpr int32_t VERTEX_COUNT { 32768 };
	GLRenderer* renderer {  };
	int32_tArray * vboIds {  };
	int32_t id {  };
	bool acquired {  };
	FloatBuffer* fbVertices {  };
	FloatBuffer* fbColors {  };

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

public: /* protected */

	/** 
	 * Render 
	 */
	void render();

public:

	/** 
	 * Dispose
	 */
	void dispose();

public: /* protected */

	/** 
	 * Clears this batch vbo renderer
	 */
	void clear();

	/** 
	 * Adds a transparent render point to this transparent render points
	 * @param transparent render point
	 */
	void addPoint(TransparentRenderPoint* point);

	/**
	 * Public constructor
	 */
	BatchVBORendererPoints(GLRenderer* renderer, int32_t id);
};
