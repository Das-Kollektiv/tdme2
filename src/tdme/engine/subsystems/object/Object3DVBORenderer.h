#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4Negative.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/Pool.h>

using std::map;
using std::vector;
using std::string;

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
	map<string, vector<Object3D*>> visibleObjectsByModels {  };
	vector<TransparentRenderFace*> groupTransparentRenderFaces {  };
	Object3DVBORenderer_TransparentRenderFacesGroupPool* transparentRenderFacesGroupPool {  };
	TransparentRenderFacesPool* transparentRenderFacesPool {  };
	map<string, TransparentRenderFacesGroup*> transparentRenderFacesGroups {  };
	TransparentRenderPointsPool* pseTransparentRenderPointsPool {  };
	BatchVBORendererPoints* psePointBatchVBORenderer {  };
	Matrix4x4Negative matrix4x4Negative {  };
public:
	static constexpr int32_t RENDERTYPE_NORMALS { 1 };
	static constexpr int32_t RENDERTYPE_TEXTUREARRAYS { 2 };
	static constexpr int32_t RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY { 4 };
	static constexpr int32_t RENDERTYPE_EFFECTCOLORS { 8 };
	static constexpr int32_t RENDERTYPE_MATERIALS { 16 };
	static constexpr int32_t RENDERTYPE_MATERIALS_DIFFUSEMASKEDTRANSPARENCY { 32 };
	static constexpr int32_t RENDERTYPE_TEXTURES { 64 };
	static constexpr int32_t RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY { 128 };
	static constexpr int32_t RENDERTYPE_LIGHTS { 256 };
	static constexpr int32_t RENDERTYPE_SHADOWMAPPING { 512 };
	static constexpr int32_t RENDERTYPE_ALL { 1023 };

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
	 * @param render types
	 */
	void render(const vector<Object3D*>& objects, bool renderTransparentFaces, int32_t renderTypes);

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
	 * @param render types
	 */
	void renderObjectsOfSameType(const vector<Object3D*>& objects, bool collectTransparentFaces, int32_t renderTypes);

	/** 
	 * Set ups a material for rendering
	 * @param object 3d group
	 * @param faces entity idx
	 * @param render types
	 */
	void setupMaterial(Object3DGroup* object3DGroup, int32_t facesEntityIdx, int32_t renderTypes);

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
	static const string createPseKey(Color4& effectColorAdd, Color4& effectColorMul, bool depthBuffer, bool sort);

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

	/**
	 * Destructor
	 */
	~Object3DVBORenderer();
};
