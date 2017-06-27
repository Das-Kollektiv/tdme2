// Generated from /tdme/src/tdme/engine/subsystems/object/BatchVBORendererTriangles.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using java::nio::FloatBuffer;
using tdme::engine::model::TextureCoordinate;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Vector3;


struct default_init_tag;

/** 
 * Batch VBO renderer
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::subsystems::object::BatchVBORendererTriangles final
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
	int32_t vertices {  };
	FloatBuffer* fbVertices {  };
	FloatBuffer* fbNormals {  };
	FloatBuffer* fbTextureCoordinates {  };
	static floatArray* TEXTURECOORDINATE_NONE;
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
	 * Adds a vertex to this transparent render faces group
	 * @param vertex
	 * @param normal
	 * @param texture coordinate
	 * @return success
	 */
	bool addVertex(Vector3* vertex, Vector3* normal, TextureCoordinate* textureCoordinate);

public:
	String* toString() override;

	// Generated
	BatchVBORendererTriangles(GLRenderer* renderer, int32_t id);
protected:
	BatchVBORendererTriangles(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static void clinit();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
