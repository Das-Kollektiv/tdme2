#pragma once

#include <algorithm>
#include <array>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/application/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/earlyzrejection/fwd-tdme.h>
#include <tdme/engine/subsystems/environmentmapping/fwd-tdme.h>
#include <tdme/engine/subsystems/framebuffer/fwd-tdme.h>
#include <tdme/engine/subsystems/lighting/fwd-tdme.h>
#include <tdme/engine/subsystems/lines/fwd-tdme.h>
#include <tdme/engine/subsystems/manager/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingProgram.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/EntityRenderer_InstancedRenderFunctionParameters.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/engine/subsystems/skinning/fwd-tdme.h>
#include <tdme/engine/subsystems/texture2D/fwd-tdme.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/ParticleSystemEntity.h>
#include <tdme/engine/ShaderParameter.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix2D3x3.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/os/threading/Queue.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Pool.h>
#include <tdme/utilities/TextureAtlas.h>

using std::array;
using std::map;
using std::remove;
using std::string;
using std::to_string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using tdme::engine::model::Color4;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::subsystems::earlyzrejection::EZRShader;
using tdme::engine::subsystems::framebuffer::BRDFLUTShader;
using tdme::engine::subsystems::framebuffer::DeferredLightingRenderShader;
using tdme::engine::subsystems::framebuffer::FrameBufferRenderShader;
using tdme::engine::subsystems::lighting::LightingShader;
using tdme::engine::subsystems::lines::LinesShader;
using tdme::engine::subsystems::manager::MeshManager;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::particlesystem::ParticlesShader;
using tdme::engine::subsystems::postprocessing::PostProcessing;
using tdme::engine::subsystems::postprocessing::PostProcessingProgram;
using tdme::engine::subsystems::postprocessing::PostProcessingShader;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::rendering::EntityRenderer;
using tdme::engine::subsystems::rendering::EntityRenderer_InstancedRenderFunctionParameters;
using tdme::engine::subsystems::rendering::TransparentRenderFacesPool;
using tdme::engine::subsystems::shadowmapping::ShadowMapping;
using tdme::engine::subsystems::shadowmapping::ShadowMapCreationShader;
using tdme::engine::subsystems::shadowmapping::ShadowMapRenderShader;
using tdme::engine::subsystems::skinning::SkinningShader;
using tdme::engine::subsystems::texture2D::Texture2DRenderShader;
using tdme::engine::Camera;
using tdme::engine::DecalObject;
using tdme::engine::DynamicColorTexture;
using tdme::engine::Entity;
using tdme::engine::EntityHierarchy;
using tdme::engine::EntityPickingFilter;
using tdme::engine::EnvironmentMapping;
using tdme::engine::FogParticleSystem;
using tdme::engine::FrameBuffer;
using tdme::engine::GeometryBuffer;
using tdme::engine::Light;
using tdme::engine::LinesObject3D;
using tdme::engine::LODObject3D;
using tdme::engine::LODObject3DImposter;
using tdme::engine::Object3D;
using tdme::engine::Object3DRenderGroup;
using tdme::engine::ObjectParticleSystem;
using tdme::engine::ParticleSystemEntity;
using tdme::engine::ParticleSystemGroup;
using tdme::engine::Partition;
using tdme::engine::PointsParticleSystem;
using tdme::engine::ShaderParameter;
using tdme::engine::Timing;
using tdme::gui::renderer::GUIRenderer;
using tdme::gui::renderer::GUIShader;
using tdme::gui::GUI;
using tdme::math::Matrix2D3x3;
using tdme::math::Matrix4x4;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::os::threading::Queue;
using tdme::os::threading::Thread;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Pool;
using tdme::utilities::TextureAtlas;

/**
 * Engine main class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::Engine final
{
	friend class tdme::engine::subsystems::renderer::EngineGL3Renderer;
	friend class tdme::engine::subsystems::renderer::EngineGL2Renderer;
	friend class tdme::engine::subsystems::renderer::EngineGLES2Renderer;
	friend class tdme::engine::subsystems::renderer::EngineVKRenderer;
	friend class DecalObject;
	friend class DynamicColorTexture;
	friend class EntityHierarchy;
	friend class EnvironmentMapping;
	friend class FogParticleSystem;
	friend class FrameBuffer;
	friend class GeometryBuffer;
	friend class ImposterObject3D;
	friend class LinesObject3D;
	friend class LODObject3D;
	friend class LODObject3DImposter;
	friend class Object3D;
	friend class Object3DRenderGroup;
	friend class ParticleSystemGroup;
	friend class ObjectParticleSystem;
	friend class PointsParticleSystem;
	friend class tdme::application::Application;
	friend class tdme::engine::subsystems::environmentmapping::EnvironmentMappingRenderer;
	friend class tdme::engine::subsystems::framebuffer::BRDFLUTShader;
	friend class tdme::engine::subsystems::framebuffer::DeferredLightingRenderShader;
	friend class tdme::engine::subsystems::framebuffer::FrameBufferRenderShader;
	friend class tdme::engine::subsystems::lighting::LightingShaderPBRBaseImplementation;
	friend class tdme::engine::subsystems::lines::LinesObject3DInternal;
	friend class tdme::engine::subsystems::rendering::BatchRendererPoints;
	friend class tdme::engine::subsystems::rendering::BatchRendererTriangles;
	friend class tdme::engine::subsystems::rendering::Object3DBase;
	friend class tdme::engine::subsystems::rendering::Object3DNode;
	friend class tdme::engine::subsystems::rendering::Object3DNodeRenderer;
	friend class tdme::engine::subsystems::rendering::EntityRenderer;
	friend class tdme::engine::subsystems::rendering::Object3DInternal;
	friend class tdme::engine::subsystems::rendering::Object3DNodeMesh;
	friend class tdme::engine::subsystems::rendering::ObjectBuffer;
	friend class tdme::engine::subsystems::rendering::TransparentRenderFacesGroup;
	friend class tdme::engine::subsystems::particlesystem::FogParticleSystemInternal;
	friend class tdme::engine::subsystems::particlesystem::ParticlesShader;
	friend class tdme::engine::subsystems::particlesystem::PointsParticleSystemInternal;
	friend class tdme::engine::subsystems::postprocessing::PostProcessingProgram;
	friend class tdme::engine::subsystems::shadowmapping::ShadowMapping;
	friend class tdme::engine::subsystems::skinning::SkinningShader;
	friend class tdme::engine::subsystems::texture2D::Texture2DRenderShader;
	friend class tdme::gui::GUI;
	friend class tdme::gui::nodes::GUIImageNode;
	friend class tdme::gui::nodes::GUINode;
	friend class tdme::gui::renderer::GUIRenderer;
	friend class tdme::gui::renderer::GUIFont;

public:
	enum AnimationProcessingTarget { NONE, CPU, CPU_NORENDERING, GPU };
	enum ShaderType { SHADERTYPE_OBJECT3D, SHADERTYPE_POSTPROCESSING, SHADERTYPE_MAX };
	enum EffectPass { EFFECTPASS_NONE, EFFECTPASS_LIGHTSCATTERING, EFFECTPASS_COUNT };
	static constexpr int LIGHTS_MAX { 8 };
	// TODO: make sure one can set up this parameter also
	static constexpr int ENGINETHREADSQUEUE_RENDER_DISPATCH_COUNT { 200 };
	static constexpr int ENGINETHREADSQUEUE_PRERENDER_DISPATCH_COUNT { 5 };
	static constexpr int ENGINETHREADSQUEUE_COMPUTE_DISPATCH_COUNT { 5 };

protected:
	STATIC_DLL_IMPEXT static Engine* currentEngine;

private:
	STATIC_DLL_IMPEXT static Engine* instance;
	STATIC_DLL_IMPEXT static Renderer* renderer;

	STATIC_DLL_IMPEXT static TextureManager* textureManager;
	STATIC_DLL_IMPEXT static VBOManager* vboManager;
	STATIC_DLL_IMPEXT static MeshManager* meshManager;
	STATIC_DLL_IMPEXT static GUIRenderer* guiRenderer;

	STATIC_DLL_IMPEXT static AnimationProcessingTarget animationProcessingTarget;

	STATIC_DLL_IMPEXT static EZRShader* ezrShader;
	STATIC_DLL_IMPEXT static ShadowMapCreationShader* shadowMappingShaderPre;
	STATIC_DLL_IMPEXT static ShadowMapRenderShader* shadowMappingShaderRender;
	STATIC_DLL_IMPEXT static LightingShader* lightingShader;
	STATIC_DLL_IMPEXT static ParticlesShader* particlesShader;
	STATIC_DLL_IMPEXT static LinesShader* linesShader;
	STATIC_DLL_IMPEXT static SkinningShader* skinningShader;
	STATIC_DLL_IMPEXT static GUIShader* guiShader;
	STATIC_DLL_IMPEXT static BRDFLUTShader* brdfLUTShader;
	STATIC_DLL_IMPEXT static FrameBufferRenderShader* frameBufferRenderShader;
	STATIC_DLL_IMPEXT static DeferredLightingRenderShader* deferredLightingRenderShader;
	STATIC_DLL_IMPEXT static PostProcessing* postProcessing;
	STATIC_DLL_IMPEXT static PostProcessingShader* postProcessingShader;
	STATIC_DLL_IMPEXT static Texture2DRenderShader* texture2DRenderShader;
	STATIC_DLL_IMPEXT static int threadCount;
	STATIC_DLL_IMPEXT static bool have4K;
	STATIC_DLL_IMPEXT static float animationBlendingTime;
	STATIC_DLL_IMPEXT static int32_t shadowMapWidth;
	STATIC_DLL_IMPEXT static int32_t shadowMapHeight;
	STATIC_DLL_IMPEXT static int32_t shadowMapRenderLookUps;
	STATIC_DLL_IMPEXT static int32_t environmentMappingWidth;
	STATIC_DLL_IMPEXT static int32_t environmentMappingHeight;
	STATIC_DLL_IMPEXT static float transformationsComputingReduction1Distance;
	STATIC_DLL_IMPEXT static float transformationsComputingReduction2Distance;

	struct Shader {
		ShaderType type;
		string id;
		map<string, ShaderParameter> parameterDefaults;
	};

	STATIC_DLL_IMPEXT static map<string, Shader> shaders;

	struct DecomposedEntities {
		vector<Entity*> noFrustumCullingEntities;
		vector<Object3D*> objects;
		vector<Object3D*> objectsForwardShading;
		vector<Object3D*> objectsPostPostProcessing;
		vector<Object3D*> objectsNoDepthTest;
		vector<LODObject3D*> lodObjects;
		vector<LODObject3DImposter*> lodObjectsImposter;
		vector<ObjectParticleSystem*> opses;
		vector<Entity*> ppses;
		vector<ParticleSystemGroup*> psgs;
		vector<LinesObject3D*> linesObjects;
		vector<DecalObject*> decalObjects;
		vector<Object3DRenderGroup*> objectRenderGroups;
		vector<EntityHierarchy*> entityHierarchies;
		vector<EnvironmentMapping*> environmentMappingEntities;
		vector<Object3D*> ezrObjects;
		vector<Object3D*> needsPreRenderEntities;
		vector<Object3D*> needsComputeTransformationsEntities;
	};

	STATIC_DLL_IMPEXT static unordered_map<string, uint8_t> uniqueShaderIds;

	int32_t width { -1 };
	int32_t height { -1 };
	int32_t scaledWidth { -1 };
	int32_t scaledHeight { -1 };
	GUI* gui { nullptr };
	Timing* timing { nullptr };
	Camera* camera { nullptr };

	Partition* partition { nullptr };

	array<Light, LIGHTS_MAX> lights;
	Color4 sceneColor;
	GeometryBuffer* geometryBuffer { nullptr };
	FrameBuffer* frameBuffer { nullptr };
	FrameBuffer* postProcessingFrameBuffer1 { nullptr };
	FrameBuffer* postProcessingFrameBuffer2{ nullptr };
	FrameBuffer* postProcessingTemporaryFrameBuffer { nullptr };
	array<FrameBuffer*, EFFECTPASS_COUNT - 1> effectPassFrameBuffers;
	array<bool, EFFECTPASS_COUNT - 1> effectPassSkip;
	ShadowMapping* shadowMapping { nullptr };
	float shadowMapLightEyeDistanceScale { 1.0f };

	unordered_map<string, Entity*> entitiesById;

	unordered_set<Entity*> autoEmitParticleSystemEntities;
	unordered_set<Entity*> noFrustumCullingEntities;
	unordered_set<Entity*> needsPreRenderEntities;
	unordered_set<Entity*> needsComputeTransformationsEntities;

	DecomposedEntities visibleDecomposedEntities;

	EntityRenderer* entityRenderer { nullptr };

	STATIC_DLL_IMPEXT static bool skinningShaderEnabled;
	bool shadowMappingEnabled;
	bool renderingInitiated;
	bool renderingComputedTransformations;

	vector<string> postProcessingPrograms;

	bool initialized;

	bool isUsingPostProcessingTemporaryFrameBuffer;

	map<string, map<string, ShaderParameter>> shaderParameters;

	TextureAtlas decalsTextureAtlas {"tdme.decals.atlas"};

	vector<Action*> actions;

	struct EngineThreadQueueElement {
		enum Type { TYPE_NONE, TYPE_PRERENDER, TYPE_TRANSFORMATIONS, TYPE_RENDERING };

		Type type { TYPE_NONE };

		Engine* engine { nullptr };

		struct {
			bool computeTransformations { false };
		} transformations;

		struct {
			Entity::RenderPass renderPass;
			uint32_t renderTypes;
			bool collectTransparentFaces;
		} rendering;

		vector<Object3D*> objects;
	};

	class EngineThread: public Thread {
		friend class Engine;
		friend class tdme::engine::subsystems::rendering::EntityRenderer;
	private:
		int idx;
		Queue<EngineThreadQueueElement>* queue { nullptr };
		TransparentRenderFacesPool* transparentRenderFacesPool { nullptr };
		unordered_map<uint8_t, unordered_map<Model*, vector<Object3D*>>> objectsByShadersAndModels;
		volatile int elementsProcessed { 0 };

	private:
		/**
		 * Constructor
		 * @param idx thread index
		 * @param queue queue
		 */
		EngineThread(int idx, Queue<EngineThreadQueueElement>* queue);

		/**
		 * Run
		 */
		virtual void run();

		/**
		 * @return transparent render faces pool
		 */
		inline TransparentRenderFacesPool* getTransparentRenderFacesPool() {
			return transparentRenderFacesPool;
		}

		/**
		 * @return processed elements
		 */
		volatile inline int getProcessedElements() {
			return elementsProcessed;
		}

		/**
		 * Reset processed element count
		 */
		inline void resetProcessedElements() {
			elementsProcessed = 0;
		}

	};

	class EngineThreadQueueElementPool: public Pool<EngineThreadQueueElement*> {
	public:
		/**
		 * Public constructor
		 */
		inline EngineThreadQueueElementPool() {
		}

	protected:
		/**
		 * Instantiate a transparent render face
		 */
		inline EngineThreadQueueElement* instantiate() override {
			return new EngineThreadQueueElement();
		}

	};

	STATIC_DLL_IMPEXT static vector<EngineThread*> engineThreads;
	STATIC_DLL_IMPEXT static Queue<EngineThreadQueueElement>* engineThreadsQueue;
	STATIC_DLL_IMPEXT static EngineThreadQueueElementPool engineThreadQueueElementPool;

	/**
	 * @return mesh manager
	 */
	inline static MeshManager* getMeshManager() {
		return meshManager;
	}

	/**
	 * @return shadow mapping or nullptr if disabled
	 */
	inline ShadowMapping* getShadowMapping() {
		return shadowMapping;
	}

	/**
	 * @return shadow mapping shader
	 */
	inline static ShadowMapCreationShader* getShadowMapCreationShader() {
		return shadowMappingShaderPre;
	}

	/**
	 * @return shadow mapping shader
	 */
	inline static ShadowMapRenderShader* getShadowMapRenderShader() {
		return shadowMappingShaderRender;
	}

	/**
	 * @return lighting shader
	 */
	inline static LightingShader* getLightingShader() {
		return lightingShader;
	}

	/**
	 * @return particles shader
	 */
	inline static ParticlesShader* getParticlesShader() {
		return particlesShader;
	}

	/**
	 * @return lines shader
	 */
	inline static LinesShader* getLinesShader() {
		return linesShader;
	}

	/**
	 * @return skinning shader
	 */
	inline static SkinningShader* getSkinningShader() {
		return skinningShader;
	}

	/**
	 * @return GUI shader
	 */
	inline static GUIShader* getGUIShader() {
		return guiShader;
	}

	/**
	 * @return BRDF LUT shader
	 */
	inline static BRDFLUTShader* getBRDFLUTShader() {
		return brdfLUTShader;
	}

	/**
	 * @return frame buffer render shader
	 */
	inline static FrameBufferRenderShader* getFrameBufferRenderShader() {
		return frameBufferRenderShader;
	}

	/**
	 * @return deferred lighting render shader
	 */
	inline static DeferredLightingRenderShader* getDeferredLightingRenderShader() {
		return deferredLightingRenderShader;
	}

	/**
	 * @return post processing shader
	 */
	inline static PostProcessingShader* getPostProcessingShader() {
		return postProcessingShader;
	}

	/**
	 * @return object 3d renderer
	 */
	inline EntityRenderer* getEntityRenderer() {
		return entityRenderer;
	}

	/**
	 * @return decals texture atlas
	 */
	inline TextureAtlas& getDecalsTextureAtlas() {
		return decalsTextureAtlas;
	}

	/**
	 * Private constructor
	 */
	Engine();

	/**
	 * Decompose entity type
	 * @param entity entity to decompose
	 * @param decomposedEntities decomposed entities
	 * @param decomposeAllEntities decompose all entities, also those who are not rendered right now
	 */
	void decomposeEntityType(Entity* entity, DecomposedEntities& decomposedEntities, bool decomposeAllEntities = false);

	/**
	 * Decompose entity types
	 * @param entities given entities to decompose
	 * @param decomposedEntities decomposed entities
	 * @param decomposeAllEntities decompose all entities, also those who are not rendered right now
	 */
	void decomposeEntityTypes(
		const vector<Entity*>& entities,
		DecomposedEntities& decomposedEntities,
		bool decomposeAllEntities = false
	);

	/**
	 * Update vertex buffers and such before rendering
	 * @param objects objects
	 * @param threadIdx thread index
	 */
	void preRenderFunction(vector<Object3D*>& objects, int threadIdx);

	/**
	 * Computes visibility and transformations
	 * @param objects objects
	 * @param threadIdx thread index
	 */
	void computeTransformationsFunction(vector<Object3D*>& objects, int threadIdx);

	/**
	 * Computes visibility and transformations
	 * @param camera camera
	 * @param decomposedEntities decomposed entities
	 * @param autoEmit auto emit particle systems
	 * @param computeTransformations compute transformations
	 */
	void computeTransformations(Camera* camera, DecomposedEntities& decomposedEntites, bool autoEmit, bool computeTransformations);

	/**
	 * Set up GUI mode rendering
	 */
	void initGUIMode();

	/**
	 * Set up GUI mode rendering
	 */
	void doneGUIMode();

	/**
	 * Reset lists
	 * @param decomposedEntities decomposed entities
	 */
	void resetLists(DecomposedEntities& decomposedEntites);

	/**
	 * Initiates the rendering process
	 * updates timing, updates camera
	 */
	void initRendering();

public:
	/**
	 * Destructor
	 */
	~Engine();

	/**
	 * Returns engine instance
	 * @return
	 */
	inline static Engine* getInstance() {
		if (instance == nullptr) {
			instance = new Engine();
		}
		return instance;
	}

	/**
	 * @return texture manager
	 */
	inline static TextureManager* getTextureManager() {
		return Engine::textureManager;
	}


	/**
	 * @return vertex buffer object manager
	 */
	inline static VBOManager* getVBOManager() {
		return vboManager;
	}

	/**
	 * @return engine thread count
	 */
	inline static int getThreadCount() {
		return Engine::threadCount;
	}

	/**
	 * Set engine thread count
	 * @param threadCount engine thread count
	 */
	inline static void setThreadCount(int threadCount) {
		Engine::threadCount = threadCount;
	}

	/**
	 * @return if having 4k
	 */
	inline static bool is4K() {
		return Engine::have4K;
	}

	/**
	 * Set if having 4k
	 * @param have4K have 4k
	 */
	inline static void set4K(bool have4K) {
		Engine::have4K = have4K;
	}

	/**
	 * @return animation blending time
	 */
	inline static float getAnimationBlendingTime() {
		return Engine::animationBlendingTime;
	}

	/**
	 * Set animation blending time
	 * @param animationBlendingTime animation blending time
	 */
	inline static void setAnimationBlendingTime(float animationBlendingTime) {
		Engine::animationBlendingTime = animationBlendingTime;
	}

	/**
	 * @return shadow map light eye distance scale
	 */
	inline float getShadowMapLightEyeDistanceScale() {
		return shadowMapLightEyeDistanceScale;
	}

	/**
	 * Set shadow map light eye distance scale
	 * @param shadowMapLightEyeDistanceScale shadow map light eye distance scale
	 */
	inline void setShadowMapLightEyeDistanceScale(float shadowMapLightEyeDistanceScale) {
		this->shadowMapLightEyeDistanceScale = shadowMapLightEyeDistanceScale;
	}

	/**
	 * @return shadow map width
	 */
	inline static int32_t getShadowMapWidth() {
		return Engine::shadowMapWidth;
	}

	/**
	 * @return shadow map height
	 */
	inline static int32_t getShadowMapHeight() {
		return Engine::shadowMapHeight;
	}

	/**
	 * @return shadow map render look ups
	 */
	inline static int32_t getShadowMapRenderLookUps() {
		return Engine::shadowMapRenderLookUps;
	}

	/**
	 * Set shadow map size
	 * @param width width
	 * @param height height
	 */
	inline static void setShadowMapSize(int32_t width, int32_t height) {
		Engine::shadowMapWidth = width;
		Engine::shadowMapHeight = height;
	}

	/**
	 * Set shadowmap look ups for each pixel when rendering
	 * @param shadow map render look ups
	 */
	inline static void setShadowMapRenderLookUps(int32_t shadowMapRenderLookUps) {
		Engine::shadowMapRenderLookUps = shadowMapRenderLookUps;
	}

	/**
	 * @return environment mapping width
	 */
	inline static int32_t getEnvironmentMappingWidth() {
		return Engine::environmentMappingWidth;
	}

	/**
	 * @return environment mapping height
	 */
	inline static int32_t getEnvironmentMappingHeight() {
		return Engine::environmentMappingHeight;
	}

	/**
	 * Set environment mapping size
	 * @param width width
	 * @param height height
	 */
	inline static void setEnvironmentMappingSize(int32_t width, int32_t height) {
		Engine::environmentMappingWidth = width;
		Engine::environmentMappingHeight = height;
	}

	/**
	 * @return distance of animated object including skinned objects from which animation computation will be computed only every second frame
	 */
	inline static float getTransformationsComputingReduction1Distance() {
		return Engine::transformationsComputingReduction1Distance;
	}

	/**
	 * Set distance of animated object including skinned objects from camera which animation computation will be computed only every second frame
	 * @param skinningComputingReduction1Distance distance
	 */
	inline static void setTransformationsComputingReduction1Distance(float transformationsComputingReduction1Distance) {
		Engine::transformationsComputingReduction1Distance = transformationsComputingReduction1Distance;
	}

	/**
	 * @return distance of animated object including skinned objects from which animation computation will be computed only every forth frame
	 */
	inline static float getTransformationsComputingReduction2Distance() {
		return Engine::transformationsComputingReduction2Distance;
	}

	/**
	 * Set distance of animated object including skinned objects from camera which animation computation will be computed only every forth frame
	 * @param skinningComputingReduction2Distance distance
	 */
	inline static void setTransformationsComputingReduction2Distance(float transformationsComputingReduction2Distance) {
		Engine::transformationsComputingReduction2Distance = transformationsComputingReduction2Distance;
	}

	/**
	 * @return unique shader id
	 */
	static uint8_t getUniqueShaderId(const string& shaderId) {
		auto uniqueShaderIdIt = uniqueShaderIds.find(shaderId);
		if (uniqueShaderIdIt == uniqueShaderIds.end()) {
			auto uniqueShaderId = uniqueShaderIds.size() + 1;
			uniqueShaderIds[shaderId] = uniqueShaderId;
			return uniqueShaderId;
		}
		return uniqueShaderIdIt->second;
	}

	/**
	 * Returns registered shaders for given type
	 * @param type type
	 */
	static const vector<string> getRegisteredShader(ShaderType type);

	/**
	 * Register shader
	 * @param type shader type
	 * @param shaderId shader id
	 * @param parameterTypes parameter types
	 * @param parameterDefault parameter defaults
	 */
	static void registerShader(ShaderType type, const string& shaderId, const map<string, ShaderParameter>& parameterDefaults = {});

	/**
	 * Returns parameter defaults of shader with given id
	 * @param shaderId shader id
	 * @return shader parameter defaults
	 */
	static const map<string, ShaderParameter> getShaderParameterDefaults(const string& shaderId);

	/**
	 * Returns shader parameter default value for given shader id and parameter name
	 * @param shaderId shader id
	 * @param parameterName parameter name
	 * @return shader parameter
	 */
	static inline const ShaderParameter getDefaultShaderParameter(const string& shaderId, const string& parameterName) {
		auto shaderIt = shaders.find(shaderId);
		if (shaderIt == shaders.end()) {
			Console::println("Engine::getDefaultShaderParameter(): no shader registered with id: " + shaderId);
			return ShaderParameter();
		}
		auto& shader = shaderIt->second;
		auto shaderParameterIt = shader.parameterDefaults.find(parameterName);
		if (shaderParameterIt == shader.parameterDefaults.end()) {
			Console::println("Engine::getDefaultShaderParameter(): no default for shader registered with id: " + shaderId + ", and parameter name: " + parameterName);
			return ShaderParameter();
		}
		auto& shaderParameter = shaderParameterIt->second;
		return shaderParameter;
	}

	/**
	 * Returns shader parameter for given shader id and parameter name, if the value does not exist, the default will be returned
	 * @param shaderId shader id
	 * @param parameterName parameter name
	 * @return shader parameter
	 */
	inline const ShaderParameter getShaderParameter(const string& shaderId, const string& parameterName) {
		auto shaderParameterIt = shaderParameters.find(shaderId);
		if (shaderParameterIt == shaderParameters.end()) {
			return getDefaultShaderParameter(shaderId, parameterName);
		}
		auto& shaderParameterMap = shaderParameterIt->second;
		auto shaderParameterParameterIt = shaderParameterMap.find(parameterName);
		if (shaderParameterParameterIt == shaderParameterMap.end()) {
			return getDefaultShaderParameter(shaderId, parameterName);
		}
		auto& shaderParameter = shaderParameterParameterIt->second;
		return shaderParameter;
	}

	/**
	 * Set shader parameter for given shader id and parameter name
	 * @param shaderId shader id
	 * @param parameterName parameter name
	 * @param paraemterValue parameter value
	 */
	inline void setShaderParameter(const string& shaderId, const string& parameterName, const ShaderParameter& parameterValue) {
		auto currentShaderParameter = getShaderParameter(shaderId, parameterName);
		if (currentShaderParameter.getType() == ShaderParameter::TYPE_NONE) {
			Console::println("Engine::setShaderParameter(): no parameter for shader registered with id: " + shaderId + ", and parameter name: " + parameterName);
			return;
		}
		if (currentShaderParameter.getType() != parameterValue.getType()) {
			Console::println("Engine::setShaderParameter(): parameter type mismatch for shader registered with id: " + shaderId + ", and parameter name: " + parameterName);
		}
		shaderParameters[shaderId][parameterName] = parameterValue;
	}

	/**
	 * Creates an offscreen rendering instance
	 * Note:
	 * - the root engine must have been initialized before
	 * - the created offscreen engine must not be initialized
	 * @param width width
	 * @param height height
	 * @param enableShadowMapping enable shadow mapping
	 * @param enableDepthBuffer enable depth buffer
	 * @param enableDepthBuffer enable geometry buffer
	 * @return off screen engine
	 */
	static Engine* createOffScreenInstance(int32_t width, int32_t height, bool enableShadowMapping, bool enableDepthBuffer, bool enableGeometryBuffer);

	/**
	 * @return graphics vendor
	 */
	const string getGraphicsVendor();

	/**
	 * @return graphics renderer
	 */
	const string getGraphicsRenderer();

	/**
	 * @return graphics renderer type
	 */
	inline Renderer::RendererType getGraphicsRendererType() {
		return renderer->getRendererType();
	}

	/**
	 * @return if initialized and ready to be used
	 */
	inline bool isInitialized() {
		return initialized;
	}

	/**
	 * @return width
	 */
	inline int32_t getWidth() {
		return width;
	}

	/**
	 * @return height
	 */
	inline int32_t getHeight() {
		return height;
	}

	/**
	 * @return scaled width or -1 if not in use
	 */
	inline int32_t getScaledWidth() {
		return scaledWidth;
	}

	/**
	 * @return scaled height -1 if not in use
	 */
	inline int32_t getScaledHeight() {
		return scaledHeight;
	}

	/**
	 * @return GUI
	 */
	inline GUI* getGUI() {
		return gui;
	}

	/**
	 * @return Timing
	 */
	inline Timing* getTiming() {
		return timing;
	}

	/**
	 * @return Camera
	 */
	inline Camera* getCamera() {
		return camera;
	}

	/**
	 * @return partition
	 */
	inline Partition* getPartition() {
		return partition;
	}

	/**
	 * Set partition
	 * @param partition partition
	 */
	void setPartition(Partition* partition);

	/**
	 * @return frame buffer or nullptr
	 */
	inline FrameBuffer* getFrameBuffer() {
		return frameBuffer;
	}

	/**
	 * @return geometry buffer or nullptr
	 */
	inline GeometryBuffer* getGeometryBuffer() {
		return geometryBuffer;
	}

	/**
	 * @return count of lights
	 */
	inline int32_t getLightCount() {
		return lights.size();
	}

	/**
	 * Returns light at idx (0 <= idx < 8)
	 * @param idx idx
	 * @return Light
	 */
	inline Light* getLightAt(int32_t idx) {
		return &lights[idx];
	}

	/**
	 * @return scene / background color
	 */
	inline const Color4& getSceneColor() const {
		return sceneColor;
	}

	/**
	 * Set scene color
	 * @param sceneColor scene color
	 */
	inline void setSceneColor(const Color4& sceneColor) {
		this->sceneColor = sceneColor;
	}

	/**
	 * @return entity count
	 */
	inline int32_t getEntityCount() {
		return entitiesById.size();
	}

	/**
	 * Returns a entity by given id
	 * @param id id
	 * @return entity or nullptr
	 */
	inline Entity* getEntity(const string& id) {
		auto entityByIdIt = entitiesById.find(id);
		if (entityByIdIt != entitiesById.end()) {
			return entityByIdIt->second;
		}
		return nullptr;
	}

	/**
	 * Adds an entity by id
	 * @param entity object
	 */
	void addEntity(Entity* entity);

	/**
	 * Removes an entity
	 * @param id id
	 * @return if entity was found and removed
	 */
	bool removeEntity(const string& id);

	/**
	 * Removes all entities and caches
	 */
	void reset();

	/**
	 * Initialize render engine
	 */
	void initialize();

	/**
	 * Reshape
	 * @param width width
	 * @param height height
	 */
	void reshape(int32_t width, int32_t height);

	/**
	 * Scale which applies to main engine only
	 * @param width width
	 * @param height height
	 */
	void scale(int32_t width, int32_t height);

	/**
	 * Disable scaling, which applies to main engine only
	 */
	void unscale();

	/**
	 * Render scaled main engine to screen
	 */
	void renderToScreen();

	/**
	 * Renders the scene
	 */
	void display();

	/**
	 * Compute world coordinate from mouse position and z value
	 * @param mouseX mouse x
	 * @param mouseY mouse y
	 * @param z z
	 * @return world coordinate
	 */
	Vector3 computeWorldCoordinateByMousePosition(int32_t mouseX, int32_t mouseY, float z);

	/**
	 * Compute world coordinate from mouse position
	 * Note: this does not work with GLES2 as reading from depth buffer is not available
	 * @param mouseX mouse x
	 * @param mouseY mouse y
	 * @return coordinate
	 */
	Vector3 computeWorldCoordinateByMousePosition(int32_t mouseX, int32_t mouseY);

	/**
	 * Retrieves entity by mouse position
	 * @param mouseX mouse x
	 * @param mouseY mouse y
	 * @param filter filter
	 * @param object3DNode pointer to store node of Object3D to if appliable
	 * @param particleSystemEntity pointer to store sub particle system entity if having a particle system group
	 * @return entity or nullptr
	 */
	inline Entity* getEntityByMousePosition(int32_t mouseX, int32_t mouseY, EntityPickingFilter* filter = nullptr, Node** object3DNode = nullptr, ParticleSystemEntity** particleSystemEntity = nullptr) {
		return
			getEntityByMousePosition(
				visibleDecomposedEntities,
				false,
				mouseX,
				mouseY,
				filter,
				object3DNode,
				particleSystemEntity
			);
	}

	/**
	 * Retrieves entity by mouse position with contact point
	 * @param mouseX mouse x
	 * @param mouseY mouse y
	 * @param contactPoint world coordinate of contact point
	 * @param filter filter
	 * @param object3DNode pointer to store node of Object3D to if appliable
	 * @param particleSystemEntity pointer to store sub particle system entity if having a particle system group
	 * @return entity or nullptr
	 */
	Entity* getEntityByMousePosition(int32_t mouseX, int32_t mouseY, Vector3& contactPoint, EntityPickingFilter* filter = nullptr, Node** object3DNode = nullptr, ParticleSystemEntity** particleSystemEntity = nullptr);

	/**
	 * Does a ray casting of visible 3d object based entities
	 * @param startPoint start point
	 * @param endPoint end point
	 * @param contactPoint world coordinate of contact point
	 * @param filter filter
	 * @return entity or nullptr
	 */
	inline Entity* doRayCasting(
		const Vector3& startPoint,
		const Vector3& endPoint,
		Vector3& contactPoint,
		EntityPickingFilter* filter = nullptr
	) {
		return
			doRayCasting(
				visibleDecomposedEntities,
				false,
				startPoint,
				endPoint,
				contactPoint,
				filter
			);
	}

	/**
	 * Retrieves object by mouse position
	 * @param mouseX mouse x
	 * @param mouseY mouse y
	 * @param filter filter
	 * @return entity or nullptr
	 */
	Entity* getEntityContactPointByMousePosition(int32_t mouseX, int32_t mouseY, EntityPickingFilter* filter);

	/**
	 * Convert screen coordinate by world coordinate
	 * @param worldCoordinate world woordinate
	 * @param screenCoordinate screen coordinate
	 * @param width optional render target width
	 * @param height optional render target height
	 * @returns if world coordinate is within frustum
	 */
	bool computeScreenCoordinateByWorldCoordinate(const Vector3& worldCoordinate, Vector2& screenCoordinate, int width = -1, int height = -1);

	/**
	 * Shutdown the engine
	 */
	void dispose();

	/**
	 * Creates a PNG file from current screen(
	 * 	This does not seem to work with GLES2 and offscreen engines
	 * @param pathName path name
	 * @param fileName file name
	 * @param removeAlphaChannel remove alpha channel
	 * @return success
	 */
	bool makeScreenshot(const string& pathName, const string& fileName, bool removeAlphaChannel = true);

	/**
	 * Creates a PNG file from current screen into a data vector
	 * 	This does not seem to work with GLES2 and offscreen engines
	 * @param pngData png data
	 * @return success
	 */
	bool makeScreenshot(vector<uint8_t>& pngData);

	/**
	 * Clear post processing programs
	 */
	void resetPostProcessingPrograms();

	/**
	 * Add post processing program
	 * @param programId program id
	 */
	void addPostProcessingProgram(const string& programId);

	/**
	 * @return renderer statistics
	 */
	inline Renderer::Renderer_Statistics getRendererStatistics() {
		return renderer->getStatistics();
	}

	/**
	 * Print registered shaders and it default parameters to console
	 */
	void dumpShaders();

	/**
	 * Add action to action queue to be executed before next engine update
	 * @param action action
	 */
	inline void enqueueAction(Action* action) {
		actions.push_back(action);
	}

private:
	/**
	 * Retrieves entity by mouse position
	 * @param decomposedEntities decomposed entities
	 * @param forcePicking override picking to be always enabled
	 * @param mouseX mouse x
	 * @param mouseY mouse y
	 * @param filter filter
	 * @param object3DNode pointer to store node of Object3D to if appliable
	 * @param particleSystemEntity pointer to store sub particle system entity if having a particle system group
	 * @return entity or nullptr
	 */
	Entity* getEntityByMousePosition(
		DecomposedEntities& decomposedEntities,
		bool forcePicking,
		int32_t mouseX,
		int32_t mouseY,
		EntityPickingFilter* filter = nullptr,
		Node** object3DNode = nullptr,
		ParticleSystemEntity** particleSystemEntity = nullptr
	);

	/**
	 * Does a ray casting of visible 3d object based entities
	 * @param decomposedEntities decomposed entities
	 * @param forcePicking override picking to be always enabled
	 * @param startPoint start point
	 * @param endPoint end point
	 * @param contactPoint world coordinate of contact point
	 * @param filter filter
	 * @return entity or nullptr
	 */
	Entity* doRayCasting(
		DecomposedEntities& decomposedEntities,
		bool forcePicking,
		const Vector3& startPoint,
		const Vector3& endPoint,
		Vector3& contactPoint,
		EntityPickingFilter* filter = nullptr
	);

	/**
	 * Removes a entity from internal lists, those entities can also be sub entities from entity hierarchy or particle system groups and such
	 * @param entity entity
	 */
	void deregisterEntity(Entity* entity);

	/**
	 * Adds a entity to internal lists, those entities can also be sub entities from entity hierarchy or particle system groups and such
	 * @param entity entity
	 */
	void registerEntity(Entity* entity);

	/**
	 * Do post processing
	 * @param renderPass render pass
	 * @param postProcessingFrameBuffers frame buffers to swap, input needs to live in postProcessingFrameBuffers[0]
	 * @param targetFrameBuffer target frame buffer
	 */
	void doPostProcessing(PostProcessingProgram::RenderPass renderPass, const array<FrameBuffer*, 2> postProcessingFrameBuffers, FrameBuffer* targetFrameBuffer);

	/**
	 * Do a render/effect pass
	 * @param renderFrameBuffer render frame buffer
	 * @param renderGeometryBuffer render geometry buffer
	 * @param visibleDecomposedEntities visible decomposed entities
	 * @param effectPass effect pass
	 * @param renderPassMask render pass mask
	 * @param shaderPrefix shader prefix
	 * @param useEZR if to use early Z rejection
	 * @param applyShadowMapping if to apply shadow mapping
	 * @param applyPostProcessing if to apply post processing
	 * @param doRenderLightSource do render light source
	 * @param doRenderParticleSystems if to render particle systems
	 * @param renderTypes render types
	 */
	void render(FrameBuffer* renderFrameBuffer, GeometryBuffer* renderGeometryBuffer, DecomposedEntities& visibleDecomposedEntities, int32_t effectPass, int32_t renderPassMask, const string& shaderPrefix, bool useEZR, bool applyShadowMapping, bool applyPostProcessing, bool doRenderLightSource, bool doRenderParticleSystems, int32_t renderTypes);

	/**
	 * Render light sources
	 * @param width render target width
	 * @param height render target height
	 * @return if light source is visible
	 */
	bool renderLightSources(int width, int height);

	/**
	 * Remove entity from decomposed entities
	 * @param decomposedEntities decomposed entities
	 * @param entity entity
	 */
	void removeFromDecomposedEntities(DecomposedEntities& decomposedEntities, Entity* entity);

	/**
	 * Remove entity
	 * @param entity entity
	 */
	void removeEntityFromLists(Entity* entity);

};
