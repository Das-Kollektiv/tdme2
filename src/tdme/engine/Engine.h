// Generated from /tdme/src/tdme/engine/Engine.java

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/opengl/fwd-tdme.h>
#include <java/io/fwd-tdme.h>
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
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using com::jogamp::opengl::GLAutoDrawable;
using com::jogamp::opengl::GLProfile;
using java::io::InputStream;
using java::lang::String;
using tdme::engine::Camera;
using tdme::engine::Engine_AnimationProcessingTarget;
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
using tdme::utils::_ArrayList;
using tdme::utils::_HashMap;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace engine {
typedef ::SubArray< ::tdme::engine::Light, ::java::lang::ObjectArray > LightArray;
}  // namespace engine
}  // namespace tdme

using java::lang::ObjectArray;
using tdme::engine::LightArray;

struct default_init_tag;

/** 
 * Engine main class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::Engine final
	: public Object
{

public:
	typedef Object super;

public: /* protected */
	static Engine* instance;
	static GLRenderer* renderer;

private:
	static TextureManager* textureManager;
	static VBOManager* vboManager;
	static MeshManager* meshManager;
	static GUIRenderer* guiRenderer;

public:
	static Engine_AnimationProcessingTarget* animationProcessingTarget;

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
	LightArray* lights {  };
	Color4* sceneColor {  };
	FrameBuffer* frameBuffer {  };
	ShadowMapping* shadowMapping {  };
	_HashMap* entitiesById {  };

public: /* protected */
	_ArrayList* objects {  };

private:
	_ArrayList* visibleObjects {  };
	_ArrayList* visibleOpses {  };

public: /* protected */
	_ArrayList* ppses {  };

private:
	_ArrayList* visiblePpses {  };

public: /* protected */
	Object3DVBORenderer* object3DVBORenderer {  };
	_HashMap* particleSystemEntitiesById {  };

private:
	bool shadowMappingEnabled {  };
	bool renderingInitiated {  };
	bool renderingComputedTransformations {  };
	Matrix4x4* modelViewMatrix {  };
	Matrix4x4* projectionMatrix {  };
	Matrix4x4* tmpMatrix4x4 {  };
	Vector3* tmpVector3a {  };
	Vector3* tmpVector3b {  };
	Vector3* tmpVector3c {  };
	Vector3* tmpVector3d {  };
	Vector3* tmpVector3f {  };
	Vector3* tmpVector3e {  };
	Vector4* tmpVector4a {  };
	Vector4* tmpVector4b {  };
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
	 * @return off screen engine
	 */
	static Engine* createOffScreenInstance(GLAutoDrawable* drawable, int32_t width, int32_t height);

	/** 
	 * @return supported GL profile
	 */
	static GLProfile* getProfile();

private:

	/** 
	 * Updates the renderer with given drawable
	 * @param drawable
	 */
	void updateRenderer(GLAutoDrawable* drawable);
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
	LightArray* getLights();

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
	Entity* getEntity(String* id);

	/** 
	 * Adds an entity by id
	 * @param object
	 */
	void addEntity(Entity* entity);

	/** 
	 * Removes an entity
	 * @param id
	 */
	void removeEntity(String* id);

	/** 
	 * Removes all entities and caches
	 */
	void reset();

	/** 
	 * Initialize render engine
	 * @param drawable
	 */
	void initialize(GLAutoDrawable* drawable);

	/** 
	 * Initialize render engine
	 * @param drawable
	 * @param debug
	 */
	void initialize(GLAutoDrawable* drawable, bool debug);

	/** 
	 * Reshape
	 * @param drawable
	 * @param x
	 * @param y
	 * @param width
	 * @param height
	 */
	void reshape(GLAutoDrawable* drawable, int32_t x, int32_t y, int32_t width, int32_t height);

private:

	/** 
	 * Initiates the rendering process
	 * updates timing, updates camera
	 * @param drawable
	 */
	void initRendering(GLAutoDrawable* drawable);

public:

	/** 
	 * Computes visibility and transformations
	 * @param drawable
	 */
	void computeTransformations(GLAutoDrawable* drawable);

	/** 
	 * Renders the scene
	 * @param drawable
	 */
	void display(GLAutoDrawable* drawable);

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
	 * @param drawable
	 */
	void dispose(GLAutoDrawable* drawable);

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

	/** 
	 * Retrieves an input stream for a tdme.jar packaged file or from filesystem 
	 * @param file name
	 * @param path name
	 * @return
	 */
	InputStream* getInputStream(String* pathName, String* fileName) /* throws(IOException) */;

	// Generated

private:
	Engine();
protected:
	Engine(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static void clinit();

private:
	virtual ::java::lang::Class* getClass0();
	friend class Engine_AnimationProcessingTarget;
	friend class Engine_initialize_1;
	friend class Engine_initialize_2;
	friend class Engine_initialize_3;
};
