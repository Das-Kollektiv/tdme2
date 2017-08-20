// Generated from /tdme/src/tdme/engine/subsystems/shadowmapping/ShadowMap.java

#pragma once

#include <vector>

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utils/fwd-tdme.h>

using std::vector;

using tdme::engine::Camera;
using tdme::engine::FrameBuffer;
using tdme::engine::Light;
using tdme::engine::subsystems::shadowmapping::ShadowMapping;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/** 
 * Shadow map class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::shadowmapping::ShadowMap final
{
public: /* protected */
	static constexpr int32_t TEXTUREUNIT { 4 };

private:
	vector<Object3D*> visibleObjects {  };
	ShadowMapping* shadowMapping {  };
	Camera* lightCamera {  };
	FrameBuffer* frameBuffer {  };
	Matrix4x4 biasMatrix {  };
	Matrix4x4 depthBiasMVPMatrix {  };
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
	void render(Light* light, const vector<Object3D*>& objects);

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
	 * Public constructor
	 * @param shadow mapping
	 * @param width
	 * @param height
	 */
	ShadowMap(ShadowMapping* shadowMapping, int32_t width, int32_t height);
};
