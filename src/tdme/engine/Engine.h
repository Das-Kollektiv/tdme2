// Generated from /tdme/src/tdme/engine/Engine.java

#pragma once

#include <map>
#include <string>
#include <vector>

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/subsystems/lighting/fwd-tdme.h>
#include <tdme/engine/subsystems/manager/fwd-tdme.h>
#include <tdme/engine/subsystems/object/fwd-tdme.h>
#include <tdme/engine/subsystems/particlesystem/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/shadowmapping/fwd-tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using std::map;
using std::vector;
using std::wstring;

using tdme::engine::Camera;
using tdme::engine::Entity;
using tdme::engine::EntityPickingFilter;
using tdme::engine::FrameBuffer;
using tdme::engine::Light;
using tdme::engine::Partition;
using tdme::engine::Timing;
using tdme::engine::model::Color4;
using tdme::engine::primitives::LineSegment;
using tdme::engine::subsystems::lighting::LightingShader;
using tdme::engine::subsystems::manager::MeshManager;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::object::Object3DVBORenderer;
using tdme::engine::subsystems::particlesystem::ParticlesShader;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::engine::subsystems::shadowmapping::ShadowMapping;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderPre;
using tdme::engine::subsystems::shadowmapping::ShadowMappingShaderRender;
using tdme::gui::GUI;
using tdme::gui::renderer::GUIRenderer;
using tdme::gui::renderer::GUIShader;
using tdme::math::Matrix4x4;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::math::Vector4;

/** 
 * Engine main class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::Engine final
{

public:
	enum AnimationProcessingTarget {CPU, CPU_NORENDERING};

public: /* protected */
	static Engine* instance;
	static GLRenderer* renderer;

private:
	static TextureManager* textureManager;
	static VBOManager* vboManager;
	static MeshManager* meshManager;
	static GUIRenderer* guiRenderer;

public:
	static AnimationProcessingTarget animationProcessingTarget;

public: /* protected */
	static ShadowMappingShaderPre* shadowMappingShaderPre;
	static ShadowMappingShaderRender* shadowMappingShaderRender;
	static LightingShader* lightingShader;
	static ParticlesShader* particlesShader;
	static GUIShader* guiShader;

private:
	int32_t width {  };
	int32_t height {  };
	GUI* gui {  };
	Timing* timing {  };
	Camera* camera {  };

public: /* protected */
	Partition* partition {  };

private:
	vector<Light*> lights {  };
	Color4* sceneColor {  };
	FrameBuffer* frameBuffer {  };
	ShadowMapping* shadowMapping {  };
	map<wstring, Entity*> entitiesById {  };

public: /* protected */
	vector<Object3D*> objects {  };

private:
	vector<Object3D*> visibleObjects {  };
	vector<ObjectParticleSystemEntity*> visibleOpses {  };

public: /* protected */
	vector<PointsParticleSystemEntity*> ppses {  };

private:
	vector<PointsParticleSystemEntity*> visiblePpses {  };

public: /* protected */
	Object3DVBORenderer* object3DVBORenderer {  };

private:
	bool shadowMappingEnabled {  };
	bool renderingInitiated {  };
	bool renderingComputedTransformations {  };
	Matrix4x4 modelViewMatrix {  };
	Matrix4x4 projectionMatrix {  };
	LineSegment* lineSegment {  };

public: /* protected */
	bool initialized {  };

public:

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
	 * @param width
	 * @param height
	 * @return off screen engine
	 */
	static Engine* createOffScreenInstance(int32_t width, int32_t height);

protected:

	/** 
	 * Default constructor
	 */
	void ctor();

public:

	/** 
	 * @return if initialized and ready to be used
	 */
	bool isInitialized();

	/** 
	 * @return width
	 */
	int32_t getWidth();

	/** 
	 * @return height
	 */
	int32_t getHeight();

	/** 
	 * @return shadow mapping or null if disabled
	 */
	ShadowMapping* getShadowMapping();

	/** 
	 * @return GUI
	 */
	GUI* getGUI();

	/** 
	 * @return Timing
	 */
	Timing* getTiming();

	/** 
	 * @return Camera
	 */
	Camera* getCamera();

	/** 
	 * @return partition
	 */
	Partition* getPartition();

	/** 
	 * Set partition
	 * @param partition
	 */
	void setPartition(Partition* partition);

	/** 
	 * @return lights
	 */
	vector<Light*>* getLights();

	/** 
	 * @return frame buffer or null
	 */
	FrameBuffer* getFrameBuffer();

	/** 
	 * Returns light at idx (0 <= idx < 8)
	 * @param idx
	 * @return Light
	 */
	Light* getLightAt(int32_t idx);

	/** 
	 * @return texture manager
	 */
	TextureManager* getTextureManager();

	/** 
	 * @return vertex buffer object manager
	 */
	VBOManager* getVBOManager();

	/** 
	 * @return mesh manager
	 */
	MeshManager* getMeshManager();

	/** 
	 * @return shadow mapping shader
	 */
	static ShadowMappingShaderPre* getShadowMappingShaderPre();

	/** 
	 * @return shadow mapping shader
	 */
	static ShadowMappingShaderRender* getShadowMappingShaderRender();

	/** 
	 * @return lighting shader
	 */
	static LightingShader* getLightingShader();

	/** 
	 * @return particles shader
	 */
	static ParticlesShader* getParticlesShader();

	/** 
	 * @return GUI shader
	 */
	static GUIShader* getGUIShader();

	/** 
	 * @return object 3d vbo renderer
	 */
	Object3DVBORenderer* getObject3DVBORenderer();

	/** 
	 * @return scene / background color
	 */
	Color4* getSceneColor();

	/** 
	 * @return entity count
	 */
	int32_t getEntityCount();

	/** 
	 * Returns a entity by given id
	 * @param id
	 * @return entity or null
	 */
	Entity* getEntity(const wstring& id);

	/** 
	 * Adds an entity by id
	 * @param object
	 */
	void addEntity(Entity* entity);

	/** 
	 * Removes an entity
	 * @param id
	 */
	void removeEntity(const wstring& id);

	/** 
	 * Removes all entities and caches
	 */
	void reset();

	/** 
	 * Initialize render engine
	 */
	void initialize();

	/** 
	 * Initialize render engine
	 * @param debug
	 */
	void initialize(bool debug);

	/** 
	 * Reshape
	 * @param x
	 * @param y
	 * @param width
	 * @param height
	 */
	void reshape(int32_t x, int32_t y, int32_t width, int32_t height);

private:

	/** 
	 * Initiates the rendering process
	 * updates timing, updates camera
	 */
	void initRendering();

public:

	/** 
	 * Computes visibility and transformations
	 */
	void computeTransformations();

	/** 
	 * Renders the scene
	 */
	void display();

	/** 
	 * Compute world coordinate from mouse position and z value
	 * @param mouse x
	 * @param mouse y
	 * @param z
	 * @param world coordinate
	 */
	void computeWorldCoordinateByMousePosition(int32_t mouseX, int32_t mouseY, float z, Vector3* worldCoordinate);

	/** 
	 * Compute world coordinate from mouse position
	 * TODO:
	 * this does not work with GLES2
	 * @param mouse x
	 * @param mouse y
	 * @param world coordinate
	 */
	void computeWorldCoordinateByMousePosition(int32_t mouseX, int32_t mouseY, Vector3* worldCoordinate);

	/** 
	 * Retrieves object by mouse position
	 * @param mouse x
	 * @param mouse y
	 * @return entity or null
	 */
	Entity* getObjectByMousePosition(int32_t mouseX, int32_t mouseY);

	/** 
	 * Retrieves object by mouse position
	 * @param mouse x
	 * @param mouse y
	 * @param filter
	 * @return entity or null
	 */
	Entity* getObjectByMousePosition(int32_t mouseX, int32_t mouseY, EntityPickingFilter* filter);

	/** 
	 * Convert screen coordinate by world coordinate
	 * @param world woordinate
	 * @param screen coordinate
	 */
	void computeScreenCoordinateByWorldCoordinate(Vector3* worldCoordinate, Vector2* screenCoordinate);

	/** 
	 * Shutdown the engine
	 */
	void dispose();

	/** 
	 * Set up GUI mode rendering
	 * @param drawable
	 */
	void initGUIMode();

	/** 
	 * Set up GUI mode rendering
	 * @param drawable
	 */
	void doneGUIMode();

	/** 
	 * Creates a PNG file from current screen
	 * TODO:
	 * this does not seem to work with GLES2 and offscreen engines
	 * @param path name 
	 * @param file name
	 * @return success
	 */
	bool makeScreenshot(String* pathName, String* fileName);

	// Generated

private:
	Engine();
	static void clinit();

private:
	friend class EngineGL3Renderer;
	friend class EngineGL2Renderer;
	friend class EngineGLES2Renderer;
};
