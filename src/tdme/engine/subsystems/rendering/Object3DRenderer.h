#pragma once

#if defined(_WIN32) && defined(_MSC_VER)
	#include <windows.h>
#endif

#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/Object3DGroup.h>
#include <tdme/engine/subsystems/rendering/Object3DRenderer_InstancedRenderFunctionParameters.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderFacesPool.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix2D3x3.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Matrix4x4Negative.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/ByteBuffer.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Pool.h>

using std::unordered_map;
using std::string;
using std::to_string;
using std::vector;

using tdme::engine::Engine;
using tdme::engine::model::Color4;
using tdme::engine::model::Material;
using tdme::engine::subsystems::rendering::BatchRendererPoints;
using tdme::engine::subsystems::rendering::BatchRendererTriangles;
using tdme::engine::subsystems::rendering::Object3DGroup;
using tdme::engine::subsystems::rendering::TransparentRenderFacesPool;
using tdme::engine::subsystems::rendering::TransparentRenderPointsPool;
using tdme::engine::subsystems::rendering::Object3DRenderer_InstancedRenderFunctionParameters;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::math::Matrix2D3x3;
using tdme::math::Matrix4x4;
using tdme::math::Matrix4x4Negative;
using tdme::math::Vector3;
using tdme::utils::ByteBuffer;
using tdme::utils::Console;
using tdme::utils::Pool;

/** 
 * Rendering class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::rendering::Object3DRenderer final {
	friend class Object3DGroupRenderer;
	friend class TransparentRenderFacesGroup;
	friend class tdme::engine::Engine;

private:
	static constexpr int32_t BATCHRENDERER_MAX { 256 };
	static constexpr int32_t INSTANCEDRENDERING_OBJECTS_MAX { 16384 };

	Engine* engine {  };
	Renderer* renderer {  };
	vector<vector<int32_t>*> vboInstancedRenderingIds {  };
	vector<BatchRendererTriangles*> trianglesBatchRenderers {  };
	unordered_map<string, vector<Object3D*>> visibleObjectsByModels {  };
	vector<TransparentRenderFace*> groupTransparentRenderFaces {  };
	Object3DRenderer_TransparentRenderFacesGroupPool* transparentRenderFacesGroupPool {  };
	TransparentRenderFacesPool* transparentRenderFacesPool {  };
	unordered_map<string, TransparentRenderFacesGroup*> transparentRenderFacesGroups {  };
	TransparentRenderPointsPool* pseTransparentRenderPointsPool {  };
	BatchRendererPoints* psePointBatchRenderer {  };
	Matrix4x4Negative matrix4x4Negative {  };
	vector<Object3D*> objectsToRender;
	vector<Object3D*> objectsNotRendered;
	vector<Object3D*> singleObjectsToRender;
	vector<Object3D*> singleObjectsNotRendered;
	int threadCount;
	vector<ByteBuffer*> bbEffectColorMuls;
	vector<ByteBuffer*> bbEffectColorAdds;
	vector<ByteBuffer*> bbMvMatrices;

	/** 
	 * Renders transparent faces
	 * TODO:	guess this should be optimized regarding GL commands
	 * skinned mesh is not supported when using GPU
	 * @param transparentRenderFaces transparent render faces
	 */
	void prepareTransparentFaces(const vector<TransparentRenderFace*>& transparentRenderFaces);

	/** 
	 * Render transparent faces groups
	 * @param context context
	 */
	void renderTransparentFacesGroups(void* context);

	/** 
	 * Release transparent faces groups
	 */
	void releaseTransparentFacesGroups();

	/** 
	 * Renders multiple objects of same type(with same model)
	 * @param objects objects of same type/ with same models
	 * @param collectTransparentFaces collect render faces
	 * @param renderTypes render types
	 */
	void renderObjectsOfSameType(const vector<Object3D*>& objects, bool collectTransparentFaces, int32_t renderTypes);

	/** 
	 * Renders multiple objects of same type(with same model) not using instancing
	 * @param objects objects of same type/ with same models
	 * @param collectTransparentFaces collect render faces
	 * @param renderTypes render types
	 */
	void renderObjectsOfSameTypeNonInstanced(const vector<Object3D*>& objects, bool collectTransparentFaces, int32_t renderTypes);

	/**
	 * Render thread function
	 * @param threadIdx thread idx
	 * @param context context
	 * @param parameters parameters
	 * @param objectsNotRendered objects not rendered
	 * @param transparentRenderFacesPool transparent render faces pool
	 */
	void instancedRenderFunction(int threadIdx, void* context, const Object3DRenderer_InstancedRenderFunctionParameters& parameters, vector<Object3D*>& objectsNotRendered, TransparentRenderFacesPool* transparentRenderFacesPool);

	/**
	 * Renders multiple objects of same type(with same model) using instancing
	 * @param objects objects of same type/ with same models
	 * @param collectTransparentFaces collect render faces
	 * @param renderTypes render types
	 */
	void renderObjectsOfSameTypeInstanced(const vector<Object3D*>& objects, bool collectTransparentFaces, int32_t renderTypes);

	/**
	 * Checks if a material could change when having multiple objects but same model
	 * @param object3DGroup object 3d group
	 * @param facesEntityIdx faces entity idx
	 * @param renderTypes render types
	 */
	inline bool checkMaterialChangable(Object3DGroup* object3DGroup, int32_t facesEntityIdx, int32_t renderTypes) {
		return object3DGroup->dynamicDiffuseTextureIdsByEntities[facesEntityIdx] != Object3DGroup::TEXTUREID_NONE;
	}

	/**
	 * Set ups a material for rendering
	 * @param context context
	 * @param object3DGroup object 3d group
	 * @param facesEntityIdx faces entity idx
	 * @param renderTypes render types
	 * @param updateOnly update only, means material has been set up already, only do changes
	 * @param materialKey material key
	 * @param currentMaterialKey current material key or empty
	 */
	void setupMaterial(void* context, Object3DGroup* object3DGroup, int32_t facesEntityIdx, int32_t renderTypes, bool updateOnly, string& materialKey, const string& currentMaterialKey = string());

	/** 
	 * Clear material for rendering
	 * @param context context
	 */
	void clearMaterial(void* context);

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
	 * @return batch renderer for triangles
	 */
	BatchRendererTriangles* acquireTrianglesBatchRenderer();

	/**
	 * Resets the object 3d renderer
	 */
	void reset();

	/**
	 * Renders all given objects
	 * @param objects objects
	 * @param renderTransparentFaces render transparent faces
	 * @param renderTypes render types
	 */
	void render(const vector<Object3D*>& objects, bool renderTransparentFaces, int32_t renderTypes);

	/** 
	 * Render batch renderer points entities
	 * @param visiblePses points batch renderer points
	 */
	void render(const vector<PointsParticleSystem*>& visiblePses);

	/**
	 * Public constructor
	 * @param engine engine
	 * @param renderer renderer
	 */
	Object3DRenderer(Engine* engine, Renderer* renderer);

	/**
	 * Destructor
	 */
	~Object3DRenderer();
};
