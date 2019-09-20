#pragma once

#include <array>
#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/ParticleSystemEntity.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/model/Color4.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/earlyzrejection/fwd-tdme.h>
#include <tdme/engine/subsystems/framebuffer/fwd-tdme.h>
#include <tdme/engine/subsystems/lighting/fwd-tdme.h>
#include <tdme/engine/subsystems/lines/fwd-tdme.h>
#include <tdme/engine/subsystems/manager/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/fwd-tdme.h>
#include <tdme/engine/subsystems/rendering/Object3DRenderer_InstancedRenderFunctionParameters.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingProgram.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/engine/subsystems/skinning/fwd-tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix2D3x3.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/os/threading/Semaphore.h>

using std::array;
using std::map;
using std::vector;
using std::string;
using std::to_string;

using tdme::engine::Camera;
using tdme::engine::Entity;
using tdme::engine::EntityPickingFilter;
using tdme::engine::FrameBuffer;
using tdme::engine::Light;
using tdme::engine::ParticleSystemEntity;
using tdme::engine::Partition;
using tdme::engine::Timing;
using tdme::engine::model::Color4;
using tdme::engine::model::Material;
using tdme::engine::subsystems::earlyzrejection::EZRShaderPre;
using tdme::engine::subsystems::framebuffer::FrameBufferRenderShader;
using tdme::engine::subsystems::lighting::LightingShader;
using tdme::engine::subsystems::lines::LinesShader;
using tdme::engine::subsystems::manager::MeshManager;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::rendering::Object3DRenderer;
using tdme::engine::subsystems::rendering::Object3DRenderer_InstancedRenderFunctionParameters;
using tdme::engine::subsystems::rendering::TransparentRenderFacesPool;
using tdme::engine::subsystems::particlesystem::ParticlesShader;
using tdme::engine::subsystems::postprocessing::PostProcessing;
using tdme::engine::subsystems::postprocessing::PostProcessingProgram;
using tdme::engine::subsystems::postprocessing::PostProcessingShader;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::shadowmapping::ShadowMapping;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPre;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRender;
using tdme::engine::subsystems::skinning::SkinningShader;
using tdme::gui::GUI;
using tdme::gui::renderer::GUIRenderer;
using tdme::gui::renderer::GUIShader;
using tdme::math::Matrix2D3x3;
using tdme::math::Matrix4x4;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::os::threading::Thread;
using tdme::os::threading::Semaphore;

/** 
 * Engine main class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::Engine final
{
	friend class EngineGL3Renderer;
	friend class EngineGL2Renderer;
	friend class EngineGLES2Renderer;
	friend class EngineVKRenderer;
	friend class FogParticleSystem;
	friend class FrameBuffer;
	friend class Object3D;
	friend class Object3DRenderGroup;
	friend class LinesObject3D;
	friend class LODObject3D;
	friend class ParticleSystemGroup;
	friend class ObjectParticleSystem;
	friend class PointsParticleSystem;
	friend class tdme::engine::subsystems::framebuffer::FrameBufferRenderShader;
	friend class tdme::engine::subsystems::lines::LinesObject3DInternal;
	friend class tdme::engine::subsystems::rendering::BatchRendererPoints;
	friend class tdme::engine::subsystems::rendering::BatchRendererTriangles;
	friend class tdme::engine::subsystems::rendering::Object3DBase;
	friend class tdme::engine::subsystems::rendering::Object3DGroup;
	friend class tdme::engine::subsystems::rendering::Object3DGroupRenderer;
	friend class tdme::engine::subsystems::rendering::Object3DRenderer;
	friend class tdme::engine::subsystems::rendering::Object3DInternal;
	friend class tdme::engine::subsystems::rendering::Object3DGroupMesh;
	friend class tdme::engine::subsystems::rendering::ObjectBuffer;
	friend class tdme::engine::subsystems::rendering::TransparentRenderFacesGroup;
	friend class tdme::engine::subsystems::particlesystem::FogParticleSystemInternal;
	friend class tdme::engine::subsystems::particlesystem::ParticlesShader;
	friend class tdme::engine::subsystems::particlesystem::PointsParticleSystemInternal;
	friend class tdme::engine::subsystems::postprocessing::PostProcessingProgram;
	friend class tdme::engine::subsystems::shadowmapping::ShadowMapping;
	friend class tdme::engine::subsystems::skinning::SkinningShader;
	friend class tdme::gui::GUI;
	friend class tdme::gui::nodes::GUIImageNode;
	friend class tdme::gui::nodes::GUINode;
	friend class tdme::gui::renderer::GUIRenderer;
	friend class tdme::gui::renderer::GUIFont;

public:
	enum AnimationProcessingTarget {CPU, CPU_NORENDERING, GPU};
	static constexpr int LIGHTS_MAX { 8 };

protected:
	static Engine* currentEngine;

private:
	static Engine* instance;
	static Renderer* renderer;

	static TextureManager* textureManager;
	static VBOManager* vboManager;
	static MeshManager* meshManager;
	static GUIRenderer* guiRenderer;

	static AnimationProcessingTarget animationProcessingTarget;

	static EZRShaderPre* ezrShaderPre;
	static ShadowMappingShaderPre* shadowMappingShaderPre;
	static ShadowMappingShaderRender* shadowMappingShaderRender;
	static LightingShader* lightingShader;
	static ParticlesShader* particlesShader;
	static LinesShader* linesShader;
	static SkinningShader* skinningShader;
	static GUIShader* guiShader;
	static FrameBufferRenderShader* frameBufferRenderShader;
	static PostProcessing* postProcessing;
	static PostProcessingShader* postProcessingShader;
	static int threadCount;
	static bool have4K;
	static float animationBlendingTime;
	static int32_t shadowMapWidth;
	static int32_t shadowMapHeight;
	static float shadowMaplightEyeDistanceScale;


	int32_t width;
	int32_t height;
	GUI* gui { nullptr };
	Timing* timing { nullptr };
	Camera* camera { nullptr };

	Partition* partition { nullptr };

	array<Light, LIGHTS_MAX> lights;
	Color4 sceneColor;
	FrameBuffer* frameBuffer { nullptr };
	FrameBuffer* postProcessingFrameBuffer1 { nullptr };
	FrameBuffer* postProcessingFrameBuffer2{ nullptr };
	FrameBuffer* postProcessingTemporaryFrameBuffer { nullptr };
	ShadowMapping* shadowMapping { nullptr };

	map<string, Entity*> entitiesById;
	map<string, ParticleSystemEntity*> autoEmitParticleSystemEntities;
	map<string, Entity*> noFrustumCullingEntities;

	vector<Object3D*> visibleObjects;
	vector<Object3D*> visibleObjectsPostPostProcessing;
	vector<LODObject3D*> visibleLODObjects;
	vector<ObjectParticleSystem*> visibleOpses;
	vector<Entity*> visiblePpses;
	vector<ParticleSystemGroup*> visiblePsgs;
	vector<LinesObject3D*> visibleLinesObjects;
	vector<Object3DRenderGroup*> visibleObjectRenderGroups;

	vector<Object3D*> visibleEZRObjects;

	Object3DRenderer* object3DRenderer { nullptr };

	static bool skinningShaderEnabled;
	bool shadowMappingEnabled;
	bool renderingInitiated;
	bool renderingComputedTransformations;
	Matrix4x4 modelViewMatrix;
	Matrix4x4 projectionMatrix;
	Matrix4x4 cameraMatrix;

	vector<string> postProcessingPrograms;

	bool initialized;

	bool isUsingPostProcessingTemporaryFrameBuffer;

	class EngineThread: public Thread {
		friend class Engine;
	private:
		int idx;
		Semaphore* engineThreadWaitSemaphore;
		void* context;
	public:
		enum State { STATE_WAITING, STATE_TRANSFORMATIONS, STATE_RENDERING, STATE_SPINNING };

		Engine* engine;

		struct {
			Object3DRenderer_InstancedRenderFunctionParameters parameters;
			vector<Object3D*> objectsNotRendered;
			TransparentRenderFacesPool* transparentRenderFacesPool;
		} rendering;

		volatile State state { STATE_WAITING };

	private:
		/**
		 * Constructor
		 * @param idx thread index
		 * @param engineThreadWaitSemaphore engine thread wait semaphore
		 * @param context context
		 */
		EngineThread(int idx, Semaphore* engineThreadWaitSemaphore, void* context);

		/**
		 * Run
		 */
		virtual void run();
	};

	static Semaphore engineThreadWaitSemaphore;
	static vector<EngineThread*> engineThreads;

	/**
	 * @return mesh manager
	 */
	inline static MeshManager* getMeshManager() {
		return meshManager;
	}

	/**
	 * @return vertex buffer object manager
	 */
	inline static VBOManager* getVBOManager() {
		return vboManager;
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
	inline static ShadowMappingShaderPre* getShadowMappingShaderPre() {
		return shadowMappingShaderPre;
	}

	/**
	 * @return shadow mapping shader
	 */
	inline static ShadowMappingShaderRender* getShadowMappingShaderRender() {
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
	 * @return frame buffer render shader
	 */
	inline static FrameBufferRenderShader* getFrameBufferRenderShader() {
		return frameBufferRenderShader;
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
	inline Object3DRenderer* getObject3DRenderer() {
		return object3DRenderer;
	}

	/**
	 * Computes visibility and transformations
	 * @param threadCount thread count
	 * @param threadIdx thread idx
	 */
	void computeTransformationsFunction(int threadCount, int threadIdx);

	/**
	 * Computes visibility and transformations
	 */
	void computeTransformations();

	/**
	 * Set up GUI mode rendering
	 */
	void initGUIMode();

	/**
	 * Set up GUI mode rendering
	 */
	void doneGUIMode();

	/**
	 * Initiates the rendering process
	 * updates timing, updates camera
	 */
	void initRendering();

	/**
	 * Private constructor
	 */
	Engine();
public:
	/**
	 * @return texture manager
	 */
	inline static TextureManager* getTextureManager() {
		return textureManager;
	}

	/**
	 * @return engine thread count
	 */
	inline static int getThreadCount() {
		return threadCount;
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
		return have4K;
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
	inline static float getShadowMapLightEyeDistanceScale() {
		return Engine::shadowMaplightEyeDistanceScale;
	}

	/**
	 * Set shadow map light eye distance scale
	 * @param shadowMaplightEyeDistanceScale shadow map light eye distance scale
	 */
	inline static void setShadowMapLightEyeDistanceScale(float shadowMaplightEyeDistanceScale) {
		Engine::shadowMaplightEyeDistanceScale = shadowMaplightEyeDistanceScale;
	}

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
	inline static void setShadowMapSize(int32_t width, int32_t height) {
		Engine::shadowMapWidth = width;
		Engine::shadowMapHeight = height;
	}

	/**
	 * Returns engine instance
	 * @return
	 */
	static Engine* getInstance();

	/** 
	 * Creates an offscreen rendering instance
	 * Note:
	 * - the root engine must have been initialized before
	 * - the created offscreen engine must not be initialized
	 * @param width width
	 * @param height height
	 * @return off screen engine
	 */
	static Engine* createOffScreenInstance(int32_t width, int32_t height);

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
	 */
	void removeEntity(const string& id);

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
	 * @param x x
	 * @param y y
	 * @param width width
	 * @param height height
	 */
	void reshape(int32_t x, int32_t y, int32_t width, int32_t height);

	/** 
	 * Renders the scene
	 */
	void display();

	/** 
	 * Compute world coordinate from mouse position and z value
	 * @param mouseX mouse x
	 * @param mouseY mouse y
	 * @param z z
	 * @param worldCoordinate world coordinate
	 */
	void computeWorldCoordinateByMousePosition(int32_t mouseX, int32_t mouseY, float z, Vector3& worldCoordinate);

	/** 
	 * Compute world coordinate from mouse position
	 * TODO:
	 * this does not work with GLES2
	 * @param mouseX mouse x
	 * @param mouseY mouse y
	 * @param worldCoordinate world coordinate
	 */
	void computeWorldCoordinateByMousePosition(int32_t mouseX, int32_t mouseY, Vector3& worldCoordinate);

	/** 
	 * Retrieves entity by mouse position
	 * @param mouseX mouse x
	 * @param mouseY mouse y
	 * @param filter filter
	 * @return entity or nullptr
	 */
	Entity* getEntityByMousePosition(int32_t mouseX, int32_t mouseY, EntityPickingFilter* filter = nullptr);

	/**
	 * Retrieves entity by mouse position with contact point
	 * @param mouseX mouse x
	 * @param mouseY mouse y
	 * @param contactPoint world coordinate of contact point
	 * @param filter filter
	 * @return entity or nullptr
	 */
	Entity* getEntityByMousePosition(int32_t mouseX, int32_t mouseY, Vector3& contactPoint, EntityPickingFilter* filter = nullptr);

	/**
	 * Does a ray casting of visible 3d object based entities
	 * @param startPoint start point
	 * @param endPoint end point
	 * @param contactPoint world coordinate of contact point
	 * @param filter filter
	 * @return entity or nullptr
	 */
	Entity* doRayCasting(const Vector3& startPoint, const Vector3& endPoint, Vector3& contactPoint, EntityPickingFilter* filter = nullptr);

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
	 */
	void computeScreenCoordinateByWorldCoordinate(const Vector3& worldCoordinate, Vector2& screenCoordinate);

	/** 
	 * Shutdown the engine
	 */
	void dispose();

	/** 
	 * Creates a PNG file from current screen
	 * TODO:
	 * this does not seem to work with GLES2 and offscreen engines
	 * @param pathName path name 
	 * @param fileName file name
	 * @return success
	 */
	bool makeScreenshot(const string& pathName, const string& fileName);

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
	 * Destructor
	 */
	~Engine();

private:

	/**
	 * Updates an entity regarding internal lists
	 * @param entity entity
	 */
	void updateEntity(Entity* entity);

	/**
	 * Do post processing
	 * @param renderPass render pass
	 * @param postProcessingFrameBuffers frame buffers to swap, input needs to live in postProcessingFrameBuffers[0]
	 * @param targetFrameBuffer target frame buffer
	 */
	void doPostProcessing(PostProcessingProgram::RenderPass renderPass, const array<FrameBuffer*, 2> postProcessingFrameBuffers, FrameBuffer* targetFrameBuffer);
};
