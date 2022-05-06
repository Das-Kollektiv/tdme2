#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/ObjectNode.h>
#include <tdme/engine/subsystems/rendering/TransparentRenderFacesPool.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/Object.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix2D3x3.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Matrix4x4Negative.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/Pool.h>

using std::string;
using std::to_string;
using std::unordered_map;
using std::vector;

using tdme::engine::model::Color4;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::rendering::BatchRendererPoints;
using tdme::engine::subsystems::rendering::BatchRendererTriangles;
using tdme::engine::subsystems::rendering::ObjectNode;
using tdme::engine::subsystems::rendering::TransparentRenderFacesPool;
using tdme::engine::subsystems::rendering::TransparentRenderPointsPool;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::FogParticleSystem;
using tdme::engine::LinesObject;
using tdme::engine::Object;
using tdme::engine::PointsParticleSystem;
using tdme::math::Matrix2D3x3;
using tdme::math::Matrix4x4;
using tdme::math::Matrix4x4Negative;
using tdme::math::Vector3;
using tdme::utilities::ByteBuffer;
using tdme::utilities::Pool;

/**
 * Rendering class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::rendering::EntityRenderer final {
	friend class ObjectNodeRenderer;
	friend class TransparentRenderFacesGroup;
	friend class tdme::engine::Engine;

private:
	static constexpr int32_t BATCHRENDERER_MAX { 256 };
	static constexpr int32_t INSTANCEDRENDERING_OBJECTS_MAX { 16384 };

	struct ObjectRenderContext {
		vector<int32_t>* vboInstancedRenderingIds { nullptr };
		ByteBuffer* bbEffectColorMuls { nullptr };
		ByteBuffer* bbEffectColorAdds { nullptr };
		ByteBuffer* bbMvMatrices { nullptr };
		Matrix4x4Negative matrix4x4Negative;
		vector<Object*> objectsToRender;
		vector<Object*> objectsNotRendered;
		vector<Object*> objectsByModelToRender;
		vector<Object*> objectsByModelNotRendered;
	};

	Engine* engine { nullptr };
	Renderer* renderer { nullptr };

	vector<BatchRendererTriangles*> trianglesBatchRenderers;
	unordered_map<uint8_t, unordered_map<Model*, vector<Object*>>> objectsByShadersAndModels;
	vector<TransparentRenderFace*> nodeTransparentRenderFaces;
	EntityRenderer_TransparentRenderFacesGroupPool* transparentRenderFacesGroupPool { nullptr };
	TransparentRenderFacesPool* transparentRenderFacesPool { nullptr };
	unordered_map<string, TransparentRenderFacesGroup*> transparentRenderFacesGroups;
	RenderTransparentRenderPointsPool* renderTransparentRenderPointsPool { nullptr };
	BatchRendererPoints* psePointBatchRenderer { nullptr };
	int threadCount;
	vector<ObjectRenderContext> contexts;

	/**
	 * Renders transparent faces
	 * TODO:	guess this should be optimized regarding GL commands
	 * skinned mesh is not supported when using GPU
	 * @param transparentRenderFaces transparent render faces
	 */
	void prepareTransparentFaces(const vector<TransparentRenderFace*>& transparentRenderFaces);

	/**
	 * Render transparent faces groups
	 * @param contextIdx context index
	 */
	void renderTransparentFacesGroups(int contextIdx);

	/**
	 * Release transparent faces groups
	 */
	void releaseTransparentFacesGroups();

	/**
	 * Renders multiple objects of same type(with same model)
	 * @param threadIdx thread idx
	 * @param objects objects of same type/ with same models
	 * @param collectTransparentFaces collect render faces
	 * @param renderTypes render types
	 * @param transparentRenderFacesPool transparent render faces pool
	 */
	inline void renderObjectsOfSameType(int threadIdx, const vector<Object*>& objects, bool collectTransparentFaces, int32_t renderTypes, TransparentRenderFacesPool* transparentRenderFacesPool) {
		if (renderer->isInstancedRenderingAvailable() == true) {
			renderObjectsOfSameTypeInstanced(threadIdx, objects, collectTransparentFaces, renderTypes, transparentRenderFacesPool);
		} else {
			renderObjectsOfSameTypeNonInstanced(objects, collectTransparentFaces, renderTypes);
		}
	}

	/**
	 * Renders multiple objects of same type(with same model) not using instancing
	 * @param objects objects of same type/ with same models
	 * @param collectTransparentFaces collect render faces
	 * @param renderTypes render types
	 */
	void renderObjectsOfSameTypeNonInstanced(const vector<Object*>& objects, bool collectTransparentFaces, int32_t renderTypes);

	/**
	 * Renders multiple objects of same type(with same model) using instancing
	 * @param threadIdx thread idx
	 * @param objects objects of same type/ with same models
	 * @param collectTransparentFaces collect render faces
	 * @param renderTypes render types
	 */
	void renderObjectsOfSameTypeInstanced(int threadIdx, const vector<Object*>& objects, bool collectTransparentFaces, int32_t renderTypes, TransparentRenderFacesPool* transparentRenderFacesPool);

	/**
	 * Checks if a material could change when having multiple objects but same model
	 * @param objectNode object node
	 * @param facesEntityIdx faces entity idx
	 * @param renderTypes render types
	 */
	inline bool checkMaterialChangable(ObjectNode* objectNode, int32_t facesEntityIdx, int32_t renderTypes) {
		return objectNode->specularMaterialDynamicDiffuseTextureIdsByEntities[facesEntityIdx] != ObjectNode::TEXTUREID_NONE;
	}

	/**
	 * Set ups a material for rendering
	 * @param contextIdx context index
	 * @param objectNode object node
	 * @param facesEntityIdx faces entity idx
	 * @param renderTypes render types
	 * @param updateOnly update only, means material has been set up already, only do changes
	 * @param materialKey material key
	 * @param currentMaterialKey current material key or empty
	 */
	void setupMaterial(int contextIdx, ObjectNode* objectNode, int32_t facesEntityIdx, int32_t renderTypes, bool updateOnly, string& materialKey, const string& currentMaterialKey = string());

	/**
	 * Clear material for rendering
	 * @param contextIdx context index
	 */
	void clearMaterial(int contextIdx);

	/**
	 * Render function
	 * @param threadIdx thread index
	 * @param objects objects
	 * @param visibleObjectsByModels objects by models storage
	 * @param renderTransparentFaces render transparent faces
	 * @param renderTypes render types
	 */
	inline void renderFunction(
		int threadIdx,
		Entity::RenderPass renderPass,
		const vector<Object*>& objects,
		unordered_map<uint8_t, unordered_map<Model*, vector<Object*>>>& objectsByShadersAndModels,
		bool renderTransparentFaces,
		int renderTypes,
		TransparentRenderFacesPool* transparentRenderFacesPool) {
		// reset shader
		renderer->setShader(threadIdx, string());
		auto effectPass = renderer->getEffectPass();
		// sort objects by model
		Vector3 objectCamFromAxis;
		auto camera = engine->getCamera();
		for (auto objectIdx = 0; objectIdx < objects.size(); objectIdx++) {
			auto object = objects[objectIdx];
			if (object->enabledInstances == 0) continue;
			if (effectPass != 0 && object->excludeFromEffectPass == effectPass) continue;
			if (object->renderPass != renderPass) continue;
			auto objectUniqueShaderId = object->getDistanceShader().empty() == true?
				object->getUniqueShaderId():
				objectCamFromAxis.set(object->getBoundingBoxTransformed()->getCenter()).sub(camera->getLookFrom()).computeLengthSquared() < Math::square(object->getDistanceShaderDistance())?
					object->getUniqueShaderId():
					object->getUniqueDistanceShaderId();
			auto& objectsByShaders = objectsByShadersAndModels[objectUniqueShaderId];
			auto& objectsByModel = objectsByShaders[object->getModel()];
			objectsByModel.push_back(object);
		}

		// render objects
		auto& context = contexts[threadIdx];
		for (auto& objectsByShaderAndModelIt: objectsByShadersAndModels) {
			auto& objectsByModels = objectsByShaderAndModelIt.second;
			for (auto& objectsByModelIt: objectsByModels) {
				auto& objectsByModel = objectsByModelIt.second;
				if (objectsByModel.size() == 0) {
					continue;
				} else
				if (objectsByModel.size() > 0) {
					do {
						for (auto object: objectsByModel) {
							if (context.objectsByModelToRender.size() == 0 ||
								(object->instances == context.objectsByModelToRender[0]->instances &&
								object->enabledInstances == context.objectsByModelToRender[0]->enabledInstances)) {
								context.objectsByModelToRender.push_back(object);
							} else {
								context.objectsByModelNotRendered.push_back(object);
							}
						}
						renderObjectsOfSameType(threadIdx, context.objectsByModelToRender, renderTransparentFaces, renderTypes, transparentRenderFacesPool);
						objectsByModel = context.objectsByModelNotRendered;
						context.objectsByModelToRender.clear();
						context.objectsByModelNotRendered.clear();
					} while (objectsByModel.size() > 0);
				}
				objectsByModel.clear();
			}
		}
	}

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
	static constexpr int32_t RENDERTYPE_RENDERGROUP_OBJECTORIGIN { 1024 };
	static constexpr int32_t RENDERTYPE_ALL { 2047 };

	/**
	 * Public constructor
	 * @param engine engine
	 * @param renderer renderer
	 */
	EntityRenderer(Engine* engine, Renderer* renderer);

	/**
	 * Destructor
	 */
	~EntityRenderer();

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
	 * Resets the object renderer
	 */
	void reset();

	/**
	 * Renders all given objects
	 * @param renderPass render pass
	 * @param objects objects
	 * @param renderTransparentFaces render transparent faces
	 * @param renderTypes render types
	 */
	void render(Entity::RenderPass renderPass, const vector<Object*>& objects, bool renderTransparentFaces, int32_t renderTypes);

	/**
	 * Renders collected transparent faces
	 */
	void renderTransparentFaces();

	/**
	 * Render points particle system entities
	 * @param renderPass render pass
	 * @param pses points particle system entities
	 */
	void render(Entity::RenderPass renderPass, const vector<Entity*>& pses);

	/**
	 * Renders all given lines objects
	 * @param renderPass render pass
	 * @param objects lines objects
	 */
	void render(Entity::RenderPass renderPass, const vector<LinesObject*>& objects);

};
