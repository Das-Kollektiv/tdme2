
#pragma once

#include <vector>

#include <tdme/tdme.h>
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
 * Shadow map
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::shadowmapping::ShadowMap final
{
	friend class ShadowMapping;

private:
	vector<Object3D*> visibleObjects {  };
	ShadowMapping* shadowMapping {  };
	Camera* lightCamera {  };
	FrameBuffer* frameBuffer {  };
	Matrix4x4 biasMatrix {  };
	Matrix4x4 depthBiasMVPMatrix {  };

	/** 
	 * Init frame buffer
	 */
	void initialize();

	/** 
	 * Reshape frame buffer
	 * @param width width
	 * @param height height
	 */
	void reshape(int32_t width, int32_t height);

	/** 
	 * Disposes this shadow mapping
	 */
	void dispose();

	/** 
	 * Binds frame buffer depth texture
	 * @param context context
	 */
	void bindDepthBufferTexture(void* context);

	/** 
	 * @return lightCamera
	 */
	Camera* getCamera();

	/** 
	 * Renders given objects to shadow map
	 * @param light light
	 */
	void render(Light* light);

	/** 
	 * Computes shadow texture matrix and stores it
	 */
	void computeDepthBiasMVPMatrix();

	/** 
	 * Set up shadow texture matrix computed and stored before
	 * @param context context
	 */
	void updateDepthBiasMVPMatrix(void* context);

public:
	static constexpr int32_t TEXTUREUNIT { 8 };

	/**
	 * @return width
	 */
	int32_t getWidth();

	/**
	 * @return height
	 */
	int32_t getHeight();

	/** 
	 * Public constructor
	 * @param shadowMapping shadow mapping
	 * @param width width
	 * @param height height
	 */
	ShadowMap(ShadowMapping* shadowMapping, int32_t width, int32_t height);

	/**
	 * Destructor
	 */
	~ShadowMap();

	/**
	 * @return frame buffer
	 */
	FrameBuffer* getFrameBuffer();
};
