
#pragma once

#include <vector>

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utils/fwd-tdme.h>

using std::vector;

using tdme::engine::Engine;
using tdme::engine::subsystems::object::Object3DVBORenderer;
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
private:
	enum ShadowMapping_RunState {NONE, PRE, RENDER};

	static int32_t shadowMapWidth;
	static int32_t shadowMapHeight;

public: /* protected */
	GLRenderer* renderer {  };
	Object3DVBORenderer* object3DVBORenderer {  };
	float lightEyeDistanceScale {  };

private:
	Matrix4x4 shadowTransformationsMatrix {  };
	Matrix4x4 depthBiasMVPMatrix {  };
	Matrix4x4 mvMatrix {  };
	Matrix4x4 mvpMatrix {  };
	Matrix4x4 normalMatrix {  };

public: /* package */
	Engine* engine {  };

private:
	vector<ShadowMap*> shadowMaps {  };
	int32_t width {  };
	int32_t height {  };
	ShadowMapping_RunState runState {  };

public:

	/** 
	 * Set shadow map size
	 * @param width
	 * @param height
	 */
	static void setShadowMapSize(int32_t width, int32_t height);
public:

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
	 * @param light eye distance scale
	 */
	void setLightEyeDistanceScale(float lightEyeDistanceScale);

	/** 
	 * Reshape shadow maps
	 * @param width
	 * @param height
	 */
	void reshape(int32_t width, int32_t height);

	/** 
	 * Create shadow maps
	 * @param objects
	 */
	void createShadowMaps(const vector<Object3D*>& objects);

	/** 
	 * Render shadow maps
	 * @param visible objects
	 */
	void renderShadowMaps(const vector<Object3D*>& visibleObjects);

	/** 
	 * Dispose shadow maps
	 */
	void dispose();

	/** 
	 * Start object transformations
	 * @param gl
	 * @param transformations matrix
	 */
	void startObjectTransformations(Matrix4x4& transformationsMatrix);

	/** 
	 * End object transformations
	 * @param gl
	 */
	void endObjectTransformations();

	/** 
	 * Update model view and projection matrix
	 */
	void updateMVPMatrices(GLRenderer* renderer);

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
	 * @param engine
	 * @param renderer
	 * @param object 3d vbo renderer
	 */
	ShadowMapping(Engine* engine, GLRenderer* renderer, Object3DVBORenderer* object3DVBORenderer);
};
