#pragma once

#include <algorithm>
#include <array>
#include <list>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/application/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
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
#include <tdme/engine/ParticleSystem.h>
#include <tdme/engine/ShaderParameter.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix3x3.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/os/threading/Queue.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Pool.h>
#include <tdme/utilities/TextureAtlas.h>
#include <tdme/utilities/UniquePtrSequenceIterator.h>

using std::array;
using std::list;
using std::make_unique;
using std::remove;
using std::sort;
using std::string;
using std::to_string;
using std::unique_ptr;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using tdme::engine::Color4;
using tdme::engine::model::Material;
using tdme::engine::model::Model;
using tdme::engine::model::Node;
using tdme::engine::subsystems::framebuffer::BRDFLUTShader;
using tdme::engine::subsystems::framebuffer::DeferredLightingRenderShader;
using tdme::engine::subsystems::framebuffer::FrameBufferRenderShader;
using tdme::engine::subsystems::framebuffer::SkyRenderShader;
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
using tdme::engine::Decal;
using tdme::engine::DynamicColorTexture;
using tdme::engine::Entity;
using tdme::engine::EntityHierarchy;
using tdme::engine::EntityPickingFilter;
using tdme::engine::EnvironmentMapping;
using tdme::engine::FogParticleSystem;
using tdme::engine::FrameBuffer;
using tdme::engine::GeometryBuffer;
using tdme::engine::Light;
using tdme::engine::Lines;
using tdme::engine::LODObject;
using tdme::engine::LODObjectImposter;
using tdme::engine::Object;
using tdme::engine::ObjectParticleSystem;
using tdme::engine::ObjectRenderGroup;
using tdme::engine::ParticleSystem;
using tdme::engine::ParticleSystemGroup;
using tdme::engine::Partition;
using tdme::engine::PointsParticleSystem;
using tdme::engine::ShaderParameter;
using tdme::engine::Timing;
using tdme::gui::renderer::GUIRenderer;
using tdme::gui::renderer::GUIShader;
using tdme::gui::GUI;
using tdme::math::Matrix3x3;
using tdme::math::Matrix4x4;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::os::threading::Queue;
using tdme::os::threading::Thread;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Pool;
using tdme::utilities::TextureAtlas;
using tdme::utilities::UniquePtrSequenceIterator;

/**
 * Engine main class
 * @author Andreas Drewke
 */
class tdme::engine::Engine final
{
	friend class tdme::engine::subsystems::renderer::EngineGL3Renderer;
	friend class tdme::engine::subsystems::renderer::EngineGL2Renderer;
	friend class tdme::engine::subsystems::renderer::EngineGLES2Renderer;
	friend class tdme::engine::subsystems::renderer::EngineVKRenderer;
	friend class Decal;
	friend class DynamicColorTexture;
	friend class EntityHierarchy;
	friend class EnvironmentMapping;
	friend class FogParticleSystem;
	friend class FrameBuffer;
	friend class GeometryBuffer;
	friend class ImposterObject;
	friend class Lines;
	friend class LODObject;
	friend class LODObjectImposter;
	friend class Object;
	friend class ObjectRenderGroup;
	friend class ParticleSystemGroup;
	friend class ObjectParticleSystem;
	friend class PointsParticleSystem;
	friend class tdme::application::Application;
	friend class tdme::engine::subsystems::environmentmapping::EnvironmentMappingRenderer;
	friend class tdme::engine::subsystems::framebuffer::BRDFLUTShader;
	friend class tdme::engine::subsystems::framebuffer::DeferredLightingRenderShader;
	friend class tdme::engine::subsystems::framebuffer::FrameBufferRenderShader;
	friend class tdme::engine::subsystems::framebuffer::SkyRenderShader;
	friend class tdme::engine::subsystems::lighting::LightingShaderPBRBaseImplementation;
	friend class tdme::engine::subsystems::lines::LinesInternal;
	friend class tdme::engine::subsystems::rendering::BatchRendererPoints;
	friend class tdme::engine::subsystems::rendering::BatchRendererTriangles;
	friend class tdme::engine::subsystems::rendering::ObjectBase;
	friend class tdme::engine::subsystems::rendering::ObjectNode;
	friend class tdme::engine::subsystems::rendering::ObjectNodeRenderer;
	friend class tdme::engine::subsystems::rendering::EntityRenderer;
	friend class tdme::engine::subsystems::rendering::ObjectInternal;
	friend class tdme::engine::subsystems::rendering::ObjectNodeMesh;
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
	enum ShaderType { SHADERTYPE_OBJECT, SHADERTYPE_POSTPROCESSING, SHADERTYPE_SKY, SHADERTYPE_MAX };
	enum EffectPass { EFFECTPASS_NONE, EFFECTPASS_LIGHTSCATTERING, EFFECTPASS_COUNT };

	// TODO: make sure one can set up this parameter also
	static constexpr int ENGINETHREADSQUEUE_RENDER_DISPATCH_COUNT { 200 };
	static constexpr int ENGINETHREADSQUEUE_PRERENDER_DISPATCH_COUNT { 5 };
	static constexpr int ENGINETHREADSQUEUE_COMPUTE_DISPATCH_COUNT { 5 };

	enum LightIdx {
		LIGHTIDX_SUN,
		LIGHTIDX_MOON,
		LIGHTIDX_OTHERS,
		LIGHTS_MAX = 8
	};

protected:
	STATIC_DLL_IMPEXT static Engine* currentEngine;

private:
	STATIC_DLL_IMPEXT static Engine* instance;
	STATIC_DLL_IMPEXT static Renderer* renderer;

	STATIC_DLL_IMPEXT static unique_ptr<TextureManager> textureManager;
	STATIC_DLL_IMPEXT static unique_ptr<VBOManager> vboManager;
	STATIC_DLL_IMPEXT static unique_ptr<MeshManager> meshManager;
	STATIC_DLL_IMPEXT static unique_ptr<GUIRenderer> guiRenderer;

	STATIC_DLL_IMPEXT static AnimationProcessingTarget animationProcessingTarget;

	STATIC_DLL_IMPEXT static unique_ptr<ShadowMapCreationShader> shadowMappingShaderPre;
	STATIC_DLL_IMPEXT static unique_ptr<ShadowMapRenderShader> shadowMappingShaderRender;
	STATIC_DLL_IMPEXT static unique_ptr<LightingShader> lightingShader;
	STATIC_DLL_IMPEXT static unique_ptr<ParticlesShader> particlesShader;
	STATIC_DLL_IMPEXT static unique_ptr<LinesShader> linesShader;
	STATIC_DLL_IMPEXT static unique_ptr<SkinningShader> skinningShader;
	STATIC_DLL_IMPEXT static unique_ptr<GUIShader> guiShader;
	STATIC_DLL_IMPEXT static unique_ptr<BRDFLUTShader> brdfLUTShader;
	STATIC_DLL_IMPEXT static unique_ptr<FrameBufferRenderShader> frameBufferRenderShader;
	STATIC_DLL_IMPEXT static unique_ptr<DeferredLightingRenderShader> deferredLightingRenderShader;
	STATIC_DLL_IMPEXT static unique_ptr<SkyRenderShader> skyRenderShader;
	STATIC_DLL_IMPEXT static unique_ptr<PostProcessing> postProcessing;
	STATIC_DLL_IMPEXT static unique_ptr<PostProcessingShader> postProcessingShader;
	STATIC_DLL_IMPEXT static unique_ptr<Texture2DRenderShader> texture2DRenderShader;
	STATIC_DLL_IMPEXT static int threadCount;
	STATIC_DLL_IMPEXT static bool have4K;
	STATIC_DLL_IMPEXT static float animationBlendingTime;
	STATIC_DLL_IMPEXT static int32_t shadowMapWidth;
	STATIC_DLL_IMPEXT static int32_t shadowMapHeight;
	STATIC_DLL_IMPEXT static int32_t shadowMapRenderLookUps;
	STATIC_DLL_IMPEXT static int32_t environmentMappingWidth;
	STATIC_DLL_IMPEXT static int32_t environmentMappingHeight;
	STATIC_DLL_IMPEXT static float animationComputationReduction1Distance;
	STATIC_DLL_IMPEXT static float animationComputationReduction2Distance;

	struct Shader {
		struct ParameterDefaults {
			const string name;
			const ShaderParameter value;
			const ShaderParameter min;
			const ShaderParameter max;
			const ShaderParameter step;
		};
		const bool internal;
		const ShaderType type;
		const string id;
		const vector<ParameterDefaults> parameterDefaults;
		unordered_map<string, const ParameterDefaults*> parameterDefaultsByName;
	};

	STATIC_DLL_IMPEXT static list<Shader> shaders;
	STATIC_DLL_IMPEXT static unordered_map<string, Shader*> shadersById;

	struct DecomposedEntities {
		vector<Entity*> noFrustumCullingEntities;
		vector<Object*> objects;
		vector<Object*> objectsForwardShading;
		vector<Object*> objectsPostPostProcessing;
		vector<Object*> objectsNoDepthTest;
		vector<Object*> objectsGizmo;
		vector<LODObject*> lodObjects;
		vector<LODObjectImposter*> lodObjectsImposter;
		vector<ObjectParticleSystem*> opses;
		vector<Entity*> ppses;
		vector<ParticleSystemGroup*> psgs;
		vector<Lines*> linesEntities;
		vector<Decal*> decalEntities;
		vector<ObjectRenderGroup*> objectRenderGroups;
		vector<EntityHierarchy*> entityHierarchies;
		vector<EnvironmentMapping*> environmentMappingEntities;
		vector<Object*> requirePreRenderEntities;
		vector<Object*> requireComputeAnimationEntities;
	};

	STATIC_DLL_IMPEXT static unordered_map<string, uint8_t> uniqueShaderIds;

	int32_t width { -1 };
	int32_t height { -1 };
	int32_t scaledWidth { -1 };
	int32_t scaledHeight { -1 };
	unique_ptr<GUI> gui;
	unique_ptr<Timing> timing;
	unique_ptr<Camera> camera;
	unique_ptr<Camera> gizmoCamera;

	unique_ptr<Partition> partition;

	array<unique_ptr<Light>, LIGHTS_MAX> lights;
	Color4 sceneColor;
	unique_ptr<GeometryBuffer> geometryBuffer;
	unique_ptr<FrameBuffer> frameBuffer;
	unique_ptr<FrameBuffer> gizmoFrameBuffer;
	unique_ptr<FrameBuffer> postProcessingFrameBuffer1;
	unique_ptr<FrameBuffer> postProcessingFrameBuffer2;
	unique_ptr<FrameBuffer> postProcessingTemporaryFrameBuffer;
	array<unique_ptr<FrameBuffer>, EFFECTPASS_COUNT - 1> effectPassFrameBuffers;
	array<bool, EFFECTPASS_COUNT - 1> effectPassSkip;
	unique_ptr<ShadowMapping> shadowMapping;
	float shadowMapLightEyeDistanceScale { 1.0f };

	unordered_map<string, Entity*> entitiesById;

	unordered_set<Entity*> autoEmitParticleSystemEntities;
	unordered_set<Entity*> noFrustumCullingEntities;
	unordered_set<Entity*> requirePreRenderEntities;
	unordered_set<Entity*> requireComputeAnimationEntities;

	DecomposedEntities visibleDecomposedEntities;

	unique_ptr<EntityRenderer> entityRenderer;

	STATIC_DLL_IMPEXT static bool skinningShaderEnabled;

	bool shadowMappingEnabled;
	bool skyShaderEnabled;

	vector<string> postProcessingPrograms;

	bool initialized;

	bool isUsingPostProcessingTemporaryFrameBuffer;

	unordered_map<string, unordered_map<string, ShaderParameter>> shaderParameters;

	TextureAtlas ppsTextureAtlas {"tdme.pps.atlas"};
	TextureAtlas decalsTextureAtlas {"tdme.decals.atlas"};

	vector<unique_ptr<Action>> actions;

	// TODO: put those limits into tdme.h or use dynamic arrays here
	static constexpr int UNIQUEMODELID_MAX { 2048 };
	static constexpr int UNIQUEMODELID_NONE { -1 };
	struct UniqueModelId {
		int id;
		int count;
	};
	unordered_map<Model*, UniqueModelId> objectUniqueModelIdMapping;
	vector<int> freeObjectUniqueModelIdIds;

	struct EngineThreadQueueElement {
		enum Type { TYPE_NONE, TYPE_PRERENDER, TYPE_ANIMATIONS, TYPE_RENDERING };

		Type type { TYPE_NONE };

		Engine* engine { nullptr };

		struct {
			bool computeAnimations { false };
		} animations;

		struct {
			Entity::RenderPass renderPass;
			uint32_t renderTypes;
			bool collectTransparentFaces;
		} rendering;

		vector<Object*> objects;
	};

	class EngineThread: public Thread {
		friend class Engine;
		friend class tdme::engine::subsystems::rendering::EntityRenderer;
	private:
		int idx;
		Queue<EngineThreadQueueElement>* queue { nullptr };
		unique_ptr<TransparentRenderFacesPool> transparentRenderFacesPool;
		array<vector<Object*>, Engine::UNIQUEMODELID_MAX> objectsByModels;
		volatile int elementsProcessed { 0 };

	public:
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
			return transparentRenderFacesPool.get();
		}

		/**
		 * @return processed elements
		 */
		inline int getProcessedElements() {
			return elementsProcessed;
		}

		/**
		 * Reset processed element count
		 */
		inline void resetProcessedElements() {
			elementsProcessed = 0;
		}

	};

	class EngineThreadQueueElementPool: public Pool<EngineThreadQueueElement> {
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

	STATIC_DLL_IMPEXT static vector<unique_ptr<EngineThread>> engineThreads;
	STATIC_DLL_IMPEXT static unique_ptr<Queue<EngineThreadQueueElement>> engineThreadsQueue;
	STATIC_DLL_IMPEXT static EngineThreadQueueElementPool engineThreadQueueElementPool;

	/**
	 * @return engine
	 */
	inline static Renderer* getRenderer() {
		return renderer;
	}

	/**
	 * @return mesh manager
	 */
	inline static MeshManager* getMeshManager() {
		return meshManager.get();
	}

	/**
	 * @return shadow mapping or nullptr if disabled
	 */
	inline ShadowMapping* getShadowMapping() {
		return shadowMapping.get();
	}

	/**
	 * @return particles shader
	 */
	inline static ParticlesShader* getParticlesShader() {
		return particlesShader.get();
	}

	/**
	 * @return lines shader
	 */
	inline static LinesShader* getLinesShader() {
		return linesShader.get();
	}

	/**
	 * @return skinning shader
	 */
	inline static SkinningShader* getSkinningShader() {
		return skinningShader.get();
	}

	/**
	 * @return GUI shader
	 */
	inline static GUIShader* getGUIShader() {
		return guiShader.get();
	}

	/**
	 * @return BRDF LUT shader
	 */
	inline static BRDFLUTShader* getBRDFLUTShader() {
		return brdfLUTShader.get();
	}

	/**
	 * @return frame buffer render shader
	 */
	inline static FrameBufferRenderShader* getFrameBufferRenderShader() {
		return frameBufferRenderShader.get();
	}

	/**
	 * @return deferred lighting render shader
	 */
	inline static DeferredLightingRenderShader* getDeferredLightingRenderShader() {
		return deferredLightingRenderShader.get();
	}

	/**
	 * @return sky shader
	 */
	inline static SkyRenderShader* getSkyRenderShader() {
		return skyRenderShader.get();
	}

	/**
	 * @return entity renderer
	 */
	inline EntityRenderer* getEntityRenderer() {
		return entityRenderer.get();;
	}

	/**
	 * @return point particle system texture atlas
	 */
	inline TextureAtlas& getPointParticleSystemTextureAtlas() {
		return ppsTextureAtlas;
	}

	/**
	 * @return decals texture atlas
	 */
	inline TextureAtlas& getDecalsTextureAtlas() {
		return decalsTextureAtlas;
	}

	// forbid class copy
	FORBID_CLASS_COPY(Engine)

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
	void preRenderFunction(vector<Object*>& objects, int threadIdx);

	/**
	 * Computes animations
	 * @param objects objects
	 * @param threadIdx thread index
	 */
	void computeAnimationsFunction(vector<Object*>& objects, int threadIdx);

	/**
	 * Computes visibility and animations and other pre render steps
	 * @param camera camera
	 * @param decomposedEntities decomposed entities
	 * @param autoEmit auto emit particle systems
	 * @param computeAnimations compute animations
	 */
	void preRender(Camera* camera, DecomposedEntities& decomposedEntites, bool autoEmit, bool computeAnimations);

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
	 * @return engine instance
	 */
	inline static Engine* getInstance() {
		if (instance == nullptr) {
			instance = new Engine();
		}
		return instance;
	}

	/**
	 * Shuts down main engine
	 */
	static void shutdown();

	/**
	 * @return texture manager
	 */
	inline static TextureManager* getTextureManager() {
		return Engine::textureManager.get();
	}


	/**
	 * @return vertex buffer object manager
	 */
	inline static VBOManager* getVBOManager() {
		return vboManager.get();
	}

	/**
	 * @return lighting shader
	 */
	inline static LightingShader* getLightingShader() {
		return lightingShader.get();
	}

	/**
	 * @return post processing shader
	 */
	inline static PostProcessingShader* getPostProcessingShader() {
		return postProcessingShader.get();
	}

	/**
	 * @return shadow mapping shader
	 */
	inline static ShadowMapCreationShader* getShadowMapCreationShader() {
		return shadowMappingShaderPre.get();
	}

	/**
	 * @return shadow mapping shader
	 */
	inline static ShadowMapRenderShader* getShadowMapRenderShader() {
		return shadowMappingShaderRender.get();
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
	 * @return distance of animated object including skinned objects from which animation computing will be computed only every second frame
	 */
	inline static float getAnimationComputationReduction1Distance() {
		return Engine::animationComputationReduction1Distance;
	}

	/**
	 * Set distance of animated object including skinned objects from camera which animation computation will be computed only every second frame
	 * @param animationComputationReduction1Distance distance
	 */
	inline static void setAnimationComputationReduction1Distance(float animationComputationReduction1Distance) {
		Engine::animationComputationReduction1Distance = animationComputationReduction1Distance;
	}

	/**
	 * @return distance of animated object including skinned objects from which animation computation will be computed only every forth frame
	 */
	inline static float getAnimationComputationReduction2Distance() {
		return Engine::animationComputationReduction2Distance;
	}

	/**
	 * Set distance of animated object including skinned objects from camera which animation computation will be computed only every forth frame
	 * @param animationComputationReduction2Distance distance
	 */
	inline static void setAnimationComputationReduction2Distance(float animationComputationReduction2Distance) {
		Engine::animationComputationReduction2Distance = animationComputationReduction2Distance;
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
	inline static const vector<string> getRegisteredShader(ShaderType type) {
		vector<string> result;
		for (const auto& shader: shaders) {
			if (shader.internal == true) continue;
			if (shader.type == type) {
				result.push_back(shader.id);
			}
		}
		sort(result.begin(), result.end());
		return result;
	}

	/**
	 * Register shader
	 * @param type shader type
	 * @param shaderId shader id
	 * @param parameterDefaults parameter defaults
	 * @param internal internal usage only
	 */
	inline static void registerShader(ShaderType type, const string& shaderId, const vector<Shader::ParameterDefaults>& parameterDefaults = {}, bool internal = false) {
		if (shadersById.find(shaderId) != shadersById.end()) {
			Console::println("Engine::registerShader(): Shader already registered: " + shaderId);
			return;
		}
		shaders.push_back(
			{
				.internal = internal,
				.type = type,
				.id = shaderId,
				.parameterDefaults = parameterDefaults,
				.parameterDefaultsByName = {}
			}
		);
		for (const auto& shaderParameterDefaults: shaders.back().parameterDefaults) {
			shaders.back().parameterDefaultsByName[shaderParameterDefaults.name] = &shaderParameterDefaults;
		}
		//
		shadersById[shaders.back().id] = &shaders.back();
	}

	/**
	 * Returns parameter defaults of shader with given id
	 * @param shaderId shader id
	 * @return shader parameter defaults
	 */
	inline static const vector<Shader::ParameterDefaults>* getShaderParameterDefaults(const string& shaderId) {
		auto shaderIt = shadersById.find(shaderId);
		if (shaderIt == shadersById.end()) {
			Console::println("Engine::getShaderParameterDefaults(): No registered shader: " + shaderId);
			return nullptr;
		}
		return &shaderIt->second->parameterDefaults;
	}

	/**
	 * Returns shader parameter names of shader with given id
	 * @param shaderId shader id
	 * @return shader parameter names
	 */
	inline static const vector<string> getShaderParameterNames(const string& shaderId) {
		vector<string> shaderParameterNames;
		auto shaderIt = shadersById.find(shaderId);
		if (shaderIt == shadersById.end()) {
			Console::println("Engine::getShaderParameterNames(): No registered shader: " + shaderId);
			return shaderParameterNames;
		}
		for (const auto& shaderParameterName: shaderIt->second->parameterDefaults) {
			shaderParameterNames.push_back(shaderParameterName.name);
		}
		return shaderParameterNames;
	}

	/**
	 * Returns shader parameter default value for given shader id and parameter name
	 * @param shaderId shader id
	 * @param parameterName parameter name
	 * @return shader parameter
	 */
	inline static const Shader::ParameterDefaults* getDefaultShaderParameter(const string& shaderId, const string& parameterName) {
		// try to find registered shader
		auto shaderIt = shadersById.find(shaderId);
		if (shaderIt == shadersById.end()) {
			// not found, return empty shader parameter
			Console::println("Engine::getDefaultShaderParameter(): no shader registered with id: " + shaderId);
			return nullptr;
		}
		// fetch from defaults
		const auto shader = shaderIt->second;
		auto shaderParameterIt = shader->parameterDefaultsByName.find(parameterName);
		if (shaderParameterIt == shader->parameterDefaultsByName.end()) {
			// not found
			Console::println("Engine::getDefaultShaderParameter(): no default for shader registered with id: " + shaderId + ", and parameter name: " + parameterName);
			return nullptr;
		}
		// done
		return shaderParameterIt->second;
	}

	/**
	 * Returns shader parameter for given shader id and parameter name, if the value does not exist, the default will be returned
	 * @param shaderId shader id
	 * @param parameterName parameter name
	 * @return shader parameter
	 */
	inline const ShaderParameter getShaderParameter(const string& shaderId, const string& parameterName) {
		// try to find shader in engine shader parameters
		auto shaderParameterIt = shaderParameters.find(shaderId);
		if (shaderParameterIt == shaderParameters.end()) {
			// not found, use default shader parameter
			auto defaultShaderParameter = getDefaultShaderParameter(shaderId, parameterName);
			if (defaultShaderParameter == nullptr) return ShaderParameter();
			return defaultShaderParameter->value;
		}
		//
		const auto& shaderParameterMap = shaderParameterIt->second;
		//
		auto shaderParameterParameterIt = shaderParameterMap.find(parameterName);
		if (shaderParameterParameterIt == shaderParameterMap.end()) {
			// not found, use default shader parameter
			auto defaultShaderParameter = getDefaultShaderParameter(shaderId, parameterName);
			if (defaultShaderParameter == nullptr) return ShaderParameter();
			return defaultShaderParameter->value;
		}
		// done
		return shaderParameterParameterIt->second;
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
	 * Load textures
	 * @param pathName path name
	 */
	void loadTextures(const string& pathName);

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
		return gui.get();
	}

	/**
	 * @return Timing
	 */
	inline Timing* getTiming() {
		return timing.get();
	}

	/**
	 * @return Camera
	 */
	inline Camera* getCamera() {
		return camera.get();
	}

	/**
	 * @return GIZMO Camera
	 */
	inline Camera* getGizmoCamera() {
		return gizmoCamera.get();
	}

	/**
	 * @return partition
	 */
	inline Partition* getPartition() {
		return partition.get();
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
		return frameBuffer.get();;
	}

	/**
	 * @return geometry buffer or nullptr
	 */
	inline GeometryBuffer* getGeometryBuffer() {
		return geometryBuffer.get();;
	}

	/**
	 * @return sky shader enabled
	 */
	inline bool isSkyShaderEnabled() {
		return skyShaderEnabled;
	}

	/**
	 * Set sky shader enabled
	 * @param skyShaderEnabled sky shader enabled
	 */
	inline void setSkyShaderEnabled(bool skyShaderEnabled) {
		this->skyShaderEnabled = skyShaderEnabled;
	}

	/**
	 * @return lights iterator
	 */
	inline UniquePtrSequenceIterator<Light> getLights() {
		return UniquePtrSequenceIterator<Light>(&(*lights.begin()), &(*lights.end()));
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
		if (idx < 0 || idx >= lights.size()) return nullptr;
		return lights[idx].get();
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
	 * Compute gizmo coordinate from mouse position and z value
	 * @param mouseX mouse x
	 * @param mouseY mouse y
	 * @param z z
	 * @return gizmo coordinate
	 */
	inline Vector3 computeGizmoCoordinateByMousePosition(int32_t mouseX, int32_t mouseY, float z) {
		return computeWorldCoordinateByMousePosition(mouseX, mouseY, z, gizmoCamera.get());
	}

	/**
	 * Compute world coordinate from mouse position and z value
	 * @param mouseX mouse x
	 * @param mouseY mouse y
	 * @param z z
	 * @return world coordinate
	 */
	inline Vector3 computeWorldCoordinateByMousePosition(int32_t mouseX, int32_t mouseY, float z) {
		return computeWorldCoordinateByMousePosition(mouseX, mouseY, z, camera.get());
	}

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
	 * @param objectNode pointer to store node of object to if appliable
	 * @param particleSystemEntity pointer to store sub particle system entity if having a particle system group
	 * @return entity or nullptr
	 */
	inline Entity* getEntityByMousePosition(int32_t mouseX, int32_t mouseY, EntityPickingFilter* filter = nullptr, Node** objectNode = nullptr, ParticleSystem** particleSystemEntity = nullptr) {
		return
			getEntityByMousePosition(
				visibleDecomposedEntities,
				false,
				mouseX,
				mouseY,
				filter,
				objectNode,
				particleSystemEntity
			);
	}

	/**
	 * Retrieves entity by mouse position with contact point
	 * @param mouseX mouse x
	 * @param mouseY mouse y
	 * @param contactPoint world coordinate of contact point
	 * @param filter filter
	 * @param objectNode pointer to store node of object to if appliable
	 * @param particleSystemEntity pointer to store sub particle system entity if having a particle system group
	 * @return entity or nullptr
	 */
	Entity* getEntityByMousePosition(int32_t mouseX, int32_t mouseY, Vector3& contactPoint, EntityPickingFilter* filter = nullptr, Node** objectNode = nullptr, ParticleSystem** particleSystemEntity = nullptr);

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
	 * Dump entities
	 */
	void dumpEntities();

	/**
	 * Add action to action queue to be executed before next engine update
	 * @param action action
	 */
	inline void enqueueAction(Action* action) {
		actions.push_back(unique_ptr<Action>(action));
	}

private:

	/**
	 * Dump entity hierarchy
	 * @param entityHierarchy entity hierarchy
	 * @param indent indent
	 * @param parentNodeId parent node id
	 */
	void dumpEntityHierarchy(EntityHierarchy* entityHierarchy, int indent, const string& parentNodeId);

	/**
	 * Compute world coordinate from mouse position and z value
	 * @param mouseX mouse x
	 * @param mouseY mouse y
	 * @param z z
	 * @param camera camera or engine camera
	 * @return world coordinate
	 */
	Vector3 computeWorldCoordinateByMousePosition(int32_t mouseX, int32_t mouseY, float z, Camera* camera);

	/**
	 * Compute world coordinate from mouse position
	 * TODO: this does not work with GLES2
	 * @param mouseX mouse x
	 * @param mouseY mouse y
	 * @param camera camera or engine camera
	 * @return world coordinate
	 */
	Vector3 computeWorldCoordinateByMousePosition(int32_t mouseX, int32_t mouseY, Camera* camera);

	/**
	 * Retrieves entity by mouse position
	 * @param decomposedEntities decomposed entities
	 * @param forcePicking override picking to be always enabled
	 * @param mouseX mouse x
	 * @param mouseY mouse y
	 * @param filter filter
	 * @param objectNode pointer to store node of Object to if appliable
	 * @param particleSystemEntity pointer to store sub particle system entity if having a particle system group
	 * @return entity or nullptr
	 */
	Entity* getEntityByMousePosition(
		DecomposedEntities& decomposedEntities,
		bool forcePicking,
		int32_t mouseX,
		int32_t mouseY,
		EntityPickingFilter* filter = nullptr,
		Node** objectNode = nullptr,
		ParticleSystem** particleSystemEntity = nullptr
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
	 * Updates registration of engine by performing deregisterEntity() and registerEntity()
	 * @param entity entity
	 */
	inline void updateEntityRegistration(Entity* entity) {
		deregisterEntity(entity);
		registerEntity(entity);
	}

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
	 * @param rendererCamera renderer camera
	 * @param visibleDecomposedEntities visible decomposed entities
	 * @param effectPass effect pass
	 * @param renderPassMask render pass mask
	 * @param shaderPrefix shader prefix
	 * @param applyShadowMapping if to apply shadow mapping
	 * @param applyPostProcessing if to apply post processing
	 * @param doRenderLightSource do render light source
	 * @param doRenderParticleSystems if to render particle systems
	 * @param renderTypes render types
	 * @param skyShaderEnabled sky shader enabled
	 */
	void render(FrameBuffer* renderFrameBuffer, GeometryBuffer* renderGeometryBuffer, Camera* rendererCamera, DecomposedEntities& visibleDecomposedEntities, int32_t effectPass, int32_t renderPassMask, const string& shaderPrefix, bool applyShadowMapping, bool applyPostProcessing, bool doRenderLightSource, bool doRenderParticleSystems, int32_t renderTypes, bool skyShaderEnabled);

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

	/**
	 * Register model
	 * @param model model
	 */
	int registerModel(Model* model) {
		auto objectUniqueModelIdMappingIt = objectUniqueModelIdMapping.find(model);
		if (objectUniqueModelIdMappingIt == objectUniqueModelIdMapping.end()) {
			// reset
			auto uniqueModelId = UNIQUEMODELID_NONE;
			// reuse a unique partition id from freeObjectUniqueModelIdIds
			if (freeObjectUniqueModelIdIds.empty() == false) {
				// yet
				uniqueModelId = freeObjectUniqueModelIdIds[freeObjectUniqueModelIdIds.size() - 1];
				freeObjectUniqueModelIdIds.erase(freeObjectUniqueModelIdIds.begin() + freeObjectUniqueModelIdIds.size() - 1);
			} else {
				// otherwise create a id
				uniqueModelId = objectUniqueModelIdMapping.size() + 1;
				if (uniqueModelId >= UNIQUEMODELID_MAX) {
					Console::println("Engine::registerModel(): too many models: " + to_string(uniqueModelId) + " >= " + to_string(UNIQUEMODELID_MAX));
					return -1;
				}
			}
			objectUniqueModelIdMapping[model] = {
				.id = uniqueModelId,
				.count = 1
			};
			return uniqueModelId;
		} else {
			auto& uniqueModel = objectUniqueModelIdMappingIt->second;
			uniqueModel.count++;
			return uniqueModel.id;
		}
	}

	/**
	 * Deregister model
	 * @param model model
	 * @param uniqueModelId unique model id
	 */
	void deregisterModel(Model* model) {
		auto objectUniqueModelIdMappingIt = objectUniqueModelIdMapping.find(model);
		if (objectUniqueModelIdMappingIt != objectUniqueModelIdMapping.end()) {
			auto& uniqueModel = objectUniqueModelIdMappingIt->second;
			uniqueModel.count--;
			if (uniqueModel.count == 0) {
				freeObjectUniqueModelIdIds.push_back(uniqueModel.id);
				objectUniqueModelIdMapping.erase(objectUniqueModelIdMappingIt);
			}
		}
	}

};
