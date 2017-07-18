// Generated from /tdme/src/tdme/engine/subsystems/shadowmapping/ShadowMapping.java

#pragma once

#include <vector>

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using std::vector;

using java::lang::Object;
using java::lang::String;
using tdme::engine::Engine;
using tdme::engine::subsystems::object::Object3DVBORenderer;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::engine::subsystems::shadowmapping::ShadowMap;
using tdme::engine::subsystems::shadowmapping::ShadowMapping_RunState;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::utils::_ArrayList;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace engine {
namespace subsystems {
namespace shadowmapping {
typedef ::SubArray< ::tdme::engine::subsystems::shadowmapping::ShadowMap, ::java::lang::ObjectArray > ShadowMapArray;
}  // namespace shadowmapping
}  // namespace subsystems
}  // namespace engine
}  // namespace tdme

using java::lang::ObjectArray;
using tdme::engine::subsystems::shadowmapping::ShadowMapArray;

struct default_init_tag;

/** 
 * Shadow mapping
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::shadowmapping::ShadowMapping final
	: public Object
{

public:
	typedef Object super;

private:
	static int32_t shadowMapWidth;
	static int32_t shadowMapHeight;

public: /* protected */
	GLRenderer* renderer {  };
	Object3DVBORenderer* object3DVBORenderer {  };
	float lightEyeDistanceScale {  };

private:
	Matrix4x4* shadowTransformationsMatrix {  };
	Matrix4x4* depthBiasMVPMatrix {  };
	Matrix4x4* tmpMatrix {  };
	Matrix4x4* mvMatrix {  };
	Matrix4x4* mvpMatrix {  };
	Matrix4x4* normalMatrix {  };
	Vector4* lightPosition4Transformed {  };
	Vector3* lightPosition3Transformed {  };
	Vector4* spotDirection4 {  };
	Vector4* spotDirection4Transformed {  };
	Vector3* spotDirection3Transformed {  };

public: /* package */
	Engine* engine {  };

private:
	ShadowMapArray* shadowMaps {  };
	int32_t width {  };
	int32_t height {  };
	ShadowMapping_RunState* runState {  };

public:

	/** 
	 * Set shadow map size
	 * @param width
	 * @param height
	 */
	static void setShadowMapSize(int32_t width, int32_t height);
protected:

	/** 
	 * Constructor
	 * @param engine
	 * @param renderer
	 * @param object 3d vbo renderer
	 */
	void ctor(Engine* engine, GLRenderer* renderer, Object3DVBORenderer* object3DVBORenderer);

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
	void startObjectTransformations(Matrix4x4* transformationsMatrix);

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
	void updateDepthBiasMVPMatrix(Matrix4x4* depthBiasMVPMatrix);

	/** 
	 * Update depth bias mvp matrix / upload only
	 */
	void updateDepthBiasMVPMatrix();

	/** 
	 * @return string representation
	 */
	String* toString() override;

	// Generated
	ShadowMapping(Engine* engine, GLRenderer* renderer, Object3DVBORenderer* object3DVBORenderer);
protected:
	ShadowMapping(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static void clinit();

private:
	virtual ::java::lang::Class* getClass0();
	friend class ShadowMapping_RunState;
};
