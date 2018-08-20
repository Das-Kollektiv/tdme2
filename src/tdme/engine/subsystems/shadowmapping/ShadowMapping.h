#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utils/fwd-tdme.h>

using std::vector;

using tdme::engine::Engine;
using tdme::engine::subsystems::rendering::Object3DVBORenderer;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::engine::subsystems::shadowmapping::ShadowMap;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::math::Vector4;

/** 
 * Shadow mapping
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::shadowmapping::ShadowMapping final
{
	friend class ShadowMap;

private:
	enum ShadowMapping_RunState {NONE, PRE, RENDER};

	static int32_t shadowMapWidth;
	static int32_t shadowMapHeight;

	GLRenderer* renderer {  };
	Object3DVBORenderer* object3DVBORenderer {  };
	float lightEyeDistanceScale {  };

	Matrix4x4 shadowTransformationsMatrix {  };
	Matrix4x4 depthBiasMVPMatrix {  };
	Matrix4x4 mvMatrix {  };
	Matrix4x4 mvpMatrix {  };
	Matrix4x4 normalMatrix {  };

	Engine* engine {  };

	vector<ShadowMap*> shadowMaps {  };
	int32_t width {  };
	int32_t height {  };
	ShadowMapping_RunState runState {  };

public:
	/**
	 * @return shadow map width
	 */
	inline static int32_t getShadowMapWidth() {
		return shadowMapWidth;
	}

	/**
	 * @return shadow map width
	 */
	inline static int32_t getShadowMapHeight() {
		return shadowMapHeight;
	}

	/** 
	 * Set shadow map size
	 * @param width width
	 * @param height height
	 */
	static void setShadowMapSize(int32_t width, int32_t height);

	/** 
	 * @return engine
	 */
	Engine* getEngine();

	/** 
	 * @return light eye distance scale
	 */
	float getLightEyeDistanceScale();

	/** 
	 * Set light eye distance scale
	 * @param lightEyeDistanceScale light eye distance scale
	 */
	void setLightEyeDistanceScale(float lightEyeDistanceScale);

	/** 
	 * Reshape shadow maps
	 * @param width width
	 * @param height height
	 */
	void reshape(int32_t width, int32_t height);

	/** 
	 * Create shadow maps
	 */
	void createShadowMaps();

	/** 
	 * Render shadow maps
	 * @param visibleObjects visible objects
	 */
	void renderShadowMaps(const vector<Object3D*>& visibleObjects);

	/** 
	 * Dispose shadow maps
	 */
	void dispose();

	/** 
	 * Start object transformations
	 * @param transformationsMatrix transformations matrix
	 */
	void startObjectTransformations(Matrix4x4& transformationsMatrix);

	/** 
	 * End object transformations
	 */
	void endObjectTransformations();

	/** 
	 * Update model view and projection matrix
	 */
	void updateMatrices(GLRenderer* renderer);

	/**
	 * Update texture matrix
	 */
	void updateTextureMatrix(GLRenderer* renderer);

	/**
	 * Update material
	 * @param renderer renderer
	 */
	void updateMaterial(GLRenderer* renderer);

	/**
	 * Set shader
	 * @param id shader id
	 */
	void setShader(const string& id);

	/**
	 * Upload light
	 * @param renderer renderer
	 * @param lightId light id
	 */
	void updateLight(GLRenderer* renderer, int32_t lightId);

	/**
	 * Bind texture
	 * @param renderer renderer
	 * @param textureId texture id
	 */
	void bindTexture(GLRenderer* renderer, int32_t textureId);

	/** 
	 * Update depth bias mvp matrix with given matrix
	 */
	void updateDepthBiasMVPMatrix(Matrix4x4& depthBiasMVPMatrix);

	/** 
	 * Update depth bias mvp matrix / upload only
	 */
	void updateDepthBiasMVPMatrix();

	/**
	 * Constructor
	 * @param engine engine
	 * @param renderer renderer
	 * @param object3DVBORenderer object 3d vbo renderer
	 */
	ShadowMapping(Engine* engine, GLRenderer* renderer, Object3DVBORenderer* object3DVBORenderer);

	/**
	 * Destructor
	 */
	~ShadowMapping();
};
