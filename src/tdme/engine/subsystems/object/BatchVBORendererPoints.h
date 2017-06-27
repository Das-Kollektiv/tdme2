// Generated from /tdme/src/tdme/engine/subsystems/object/BatchVBORendererPoints.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using java::nio::FloatBuffer;
using tdme::engine::subsystems::object::TransparentRenderPoint;
using tdme::engine::subsystems::renderer::GLRenderer;


struct default_init_tag;

/** 
 * Batch VBO renderer
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::subsystems::object::BatchVBORendererPoints final
	: public Object
{

public:
	typedef Object super;

private:
	static int32_t VERTEX_COUNT;
	GLRenderer* renderer {  };
	int32_tArray* vboIds {  };
	int32_t id {  };
	bool acquired {  };
	FloatBuffer* fbVertices {  };
	FloatBuffer* fbColors {  };
protected:

	/** 
	 * Public constructor
	 * @param renderer
	 */
	void ctor(GLRenderer* renderer, int32_t id);

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

public:
	String* toString() override;

	// Generated
	BatchVBORendererPoints(GLRenderer* renderer, int32_t id);
protected:
	BatchVBORendererPoints(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static void clinit();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
