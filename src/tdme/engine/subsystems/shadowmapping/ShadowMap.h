// Generated from /tdme/src/tdme/engine/subsystems/shadowmapping/ShadowMap.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::engine::Camera;
using tdme::engine::FrameBuffer;
using tdme::engine::Light;
using tdme::engine::subsystems::shadowmapping::ShadowMapping;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utils::_ArrayList;


struct default_init_tag;

/** 
 * Shadow map class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::shadowmapping::ShadowMap final
	: public Object
{

public:
	typedef Object super;

public: /* protected */
	static constexpr int32_t TEXTUREUNIT { 4 };

private:
	_ArrayList* visibleObjects {  };
	ShadowMapping* shadowMapping {  };
	Camera* lightCamera {  };
	Vector3* lightDirection {  };
	Vector3* lightLookAt {  };
	Vector3* lightLookFrom {  };
	FrameBuffer* frameBuffer {  };
	Matrix4x4* biasMatrix {  };
	Matrix4x4* depthBiasMVPMatrix {  };
protected:

	/** 
	 * Public constructor
	 * @param width
	 * @param height
	 */
	void ctor(ShadowMapping* shadowMapping, int32_t width, int32_t height);

public:

	/** 
	 * @return width
	 */
	int32_t getWidth();

	/** 
	 * @return height
	 */
	int32_t getHeight();

public: /* protected */

	/** 
	 * Init frame buffer
	 * @param gl
	 */
	void initialize();

	/** 
	 * Reshape frame buffer
	 * @param gl
	 * @param width
	 * @param height
	 */
	void reshape(int32_t width, int32_t height);

	/** 
	 * Disposes this shadow mapping
	 * @param gl
	 */
	void dispose();

	/** 
	 * Binds frame buffer depth texture
	 * @param gl
	 */
	void bindDepthBufferTexture();

	/** 
	 * @return lightCamera
	 */
	Camera* getCamera();

	/** 
	 * Renders given objects to shadow map
	 * @param gl
	 * @param objects
	 */
	void render(Light* light, _ArrayList* objects);

	/** 
	 * Computes shadow texture matrix and stores it
	 * @param gl
	 */
	void computeDepthBiasMVPMatrix();

	/** 
	 * Set up shadow texture matrix computed and stored before
	 */
	void updateDepthBiasMVPMatrix();

public:

	/** 
	 * @return string representation
	 */
	String* toString() override;

	// Generated

public: /* protected */
	ShadowMap(ShadowMapping* shadowMapping, int32_t width, int32_t height);
protected:
	ShadowMap(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
