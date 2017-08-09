// Generated from /tdme/src/tdme/engine/subsystems/object/Object3DVBORenderer.java

#pragma once

#include <map>
#include <string>
#include <vector>

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4Negative.h>
#include <tdme/utils/fwd-tdme.h>

using std::map;
using std::vector;
using std::wstring;

using tdme::engine::Engine;
using tdme::engine::model::Color4;
using tdme::engine::subsystems::object::BatchVBORendererPoints;
using tdme::engine::subsystems::object::BatchVBORendererTriangles;
using tdme::engine::subsystems::object::Object3DGroup;
using tdme::engine::subsystems::object::TransparentRenderFacesPool;
using tdme::engine::subsystems::object::TransparentRenderPointsPool;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Matrix4x4;
using tdme::math::Matrix4x4Negative;
using tdme::math::Vector3;
using tdme::utils::Pool;

struct default_init_tag;

/** 
 * VBO renderer class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::object::Object3DVBORenderer final {
private:
	static constexpr int32_t BATCHVBORENDERER_MAX { 256 };

public: /* protected */
	Engine* engine {  };
	GLRenderer* renderer {  };

private:
	vector<BatchVBORendererTriangles*> trianglesBatchVBORenderers {  };
	map<wstring, vector<Object3D*>> visibleObjectsByModels {  };
	vector<TransparentRenderFace*> groupTransparentRenderFaces {  };
	Object3DVBORenderer_TransparentRenderFacesGroupPool* transparentRenderFacesGroupPool {  };
	TransparentRenderFacesPool* transparentRenderFacesPool {  };
	map<wstring, TransparentRenderFacesGroup*> transparentRenderFacesGroups {  };
	TransparentRenderPointsPool* pseTransparentRenderPointsPool {  };
	BatchVBORendererPoints* psePointBatchVBORenderer {  };
	Matrix4x4Negative matrix4x4Negative {  };
public:

	/** 
	 * Init
	 */
	void initialize();

	/** 
	 * Dispose
	 */
	void dispose();

	/** 
	 * @return batch vbo renderer for triangles
	 */
	BatchVBORendererTriangles* acquireTrianglesBatchVBORenderer();

	/** 
	 * Resets the object 3d vbo renderer
	 */
	void reset();

	/** 
	 * Renders all given objects
	 * @param objects
	 * @param render transparent faces  
	 */
	void render(const vector<Object3D*>& objects, bool renderTransparentFaces);

public: /* protected */

	/** 
	 * Renders transparent faces
	 * TODO:	guess this should be optimized regarding GL commands
	 * skinned mesh is not supported when using GPU
	 * @param transparent render faces
	 */
	void prepareTransparentFaces(const vector<TransparentRenderFace*>& transparentRenderFaces);

	/** 
	 * Render transparent faces groups
	 */
	void renderTransparentFacesGroups();

	/** 
	 * Render transparent faces groups
	 * @param transparent render faces groups
	 * @param depth buffer mode
	 */
	void releaseTransparentFacesGroups();

	/** 
	 * Renders multiple objects of same type(with same model)
	 * @param engine
	 * @param objects of same type/ with same models
	 * @param collect render faces
	 * @param skinning shader
	 */
	void renderObjectsOfSameType(const vector<Object3D*>& objects, bool collectTransparentFaces);

	/** 
	 * Set ups a material for rendering
	 * @param object 3d group
	 * @param faces entity idx
	 */
	void setupMaterial(Object3DGroup* object3DGroup, int32_t facesEntityIdx);

	/** 
	 * Clear material for rendering
	 * @param gl
	 * @param material
	 */
	void clearMaterial();

private:

	/** 
	 * Creates a particle system entity key
	 * @param effect color add
	 * @param effect color mul
	 * @param depthBuffer
	 * @param sort
	 */
	static const wstring createPseKey(Color4* effectColorAdd, Color4* effectColorMul, bool depthBuffer, bool sort);

public:

	/** 
	 * Render batch VBO renderer points entities
	 * @param points batch VBO renderer points
	 */
	void render(const vector<PointsParticleSystemEntity*>& visiblePses);

	/**
	 * Public constructor
	 * @param engine
	 * @param renderer
	 */
	Object3DVBORenderer(Engine* engine, GLRenderer* renderer);
};
