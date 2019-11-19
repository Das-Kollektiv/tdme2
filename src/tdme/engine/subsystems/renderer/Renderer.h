#pragma once

#include <array>
#include <vector>
#include <string>

#include <tdme/tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/Renderer_Light.h>
#include <tdme/engine/subsystems/renderer/Renderer_Material.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix2D3x3.h>
#include <tdme/math/Matrix4x4.h>

using std::array;
using std::vector;
using std::string;

using tdme::utils::ByteBuffer;
using tdme::utils::FloatBuffer;
using tdme::utils::IntBuffer;
using tdme::utils::ShortBuffer;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::subsystems::renderer::Renderer_Light;
using tdme::engine::subsystems::renderer::Renderer_Material;
using tdme::math::Matrix2D3x3;
using tdme::math::Matrix4x4;

/** 
 * Renderer interface
 * @author Andreas Drewke
 * @ersion $Id$
 */
class tdme::engine::subsystems::renderer::Renderer
{
public:
	int32_t ID_NONE;
	int32_t CLEAR_DEPTH_BUFFER_BIT;
	int32_t CLEAR_COLOR_BUFFER_BIT;
	int32_t CULLFACE_FRONT;
	int32_t CULLFACE_BACK;
	int32_t TEXTUREUNITS_MAX;
	int32_t SHADER_FRAGMENT_SHADER;
	int32_t SHADER_VERTEX_SHADER;
	int32_t SHADER_GEOMETRY_SHADER;
	int32_t SHADER_COMPUTE_SHADER;
	int32_t DEPTHFUNCTION_ALWAYS;
	int32_t DEPTHFUNCTION_EQUAL;
	int32_t DEPTHFUNCTION_LESSEQUAL;
	int32_t DEPTHFUNCTION_GREATEREQUAL;
	int32_t FRAMEBUFFER_DEFAULT;
	int32_t FRONTFACE_CW;
	int32_t FRONTFACE_CCW;

protected:
	int32_t viewPortX;
	int32_t viewPortY;
	int32_t viewPortWidth;
	int32_t viewPortHeight;

private:
	Matrix4x4 projectionMatrix;
	Matrix4x4 cameraMatrix;
	Matrix4x4 modelViewMatrix;
	Matrix4x4 viewportMatrix;

public:
	float pointSize;

	/**
	 * @return default context
	 */
	virtual void* getDefaultContext();

	/**
	 * @return context by index
	 */
	virtual void* getContext(int contextIdx);

	/**
	 * Retrieve context index from given context
	 * @return context index
	 */
	virtual int getContextIndex(void* context);

	/** 
	 * Initialize renderer
	 */
	virtual void initialize() = 0;

	/** 
	 * Pre Frame Initialization
	 */
	virtual void initializeFrame();

	/** 
	 * Finish frame
	 */
	virtual void finishFrame() = 0;

	/**
	 * @return shader version e.g. gl2, gl3 or gles2
	 */
	virtual const string getShaderVersion() = 0;

	/** 
	 * @return if renderer is supporting multi threaded rendering
	 */
	virtual bool isSupportingMultithreadedRendering() = 0;

	/**
	 * @return if renderer is supporting multiple render queues
	 */
	virtual bool isSupportingMultipleRenderQueues() = 0;

	/**
	 * @return if renderer supports vertex arrays
	 */
	virtual bool isSupportingVertexArrays() = 0;

	/**
	 * Checks if buffer objects is available
	 * @return buffer objects availability
	 */
	virtual bool isBufferObjectsAvailable() = 0;

	/** 
	 * Checks if depth texture is available
	 * @return depth texture is available
	 */
	virtual bool isDepthTextureAvailable() = 0;

	/** 
	 * @return requires program attribute location
	 */
	virtual bool isUsingProgramAttributeLocation() = 0;

	/** 
	 * @return if specular mapping is supported
	 */
	virtual bool isSpecularMappingAvailable() = 0;

	/** 
	 * @return if normal mapping is supported
	 */
	virtual bool isNormalMappingAvailable() = 0;

	/** 
	 * @return if displacement mapping is supported
	 */
	virtual bool isDisplacementMappingAvailable() = 0;

	/** 
	 * Checks if instanced rendering is available
	 * @return instance rendering availability
	 */
	virtual bool isInstancedRenderingAvailable() = 0;

	/**
	 * @return Returns if renderer is using short indices, otherwise it uses int indices
	 */
	virtual bool isUsingShortIndices() = 0;

	/**
	 * @return If geometry shader is available
	 */
	virtual bool isGeometryShaderAvailable() = 0;

	/**
	 * @return number of texture units
	 */
	virtual int32_t getTextureUnits() = 0;

	/** 
	 * Loads a shader into open gl stack
	 * @param type type
	 * @param pathName path name
	 * @param fileName file name
	 * @param definitions preprocessor definitions
	 * @param functions included functions
	 * @return shader handle
	 */
	virtual int32_t loadShader(int32_t type, const string& pathName, const string& fileName, const string& definitions = string(), const string& functions = string()) = 0;

	/** 
	 * Use shader program
	 * @param programId programId
	 */
	virtual void useProgram(int32_t programId) = 0;

	/** 
	 * Creates a shader program
	 * @return int
	 */
	virtual int32_t createProgram() = 0;

	/** 
	 * Attaches a shader to a program
	 * @param programId program id
	 * @param shaderId shader id
	 */
	virtual void attachShaderToProgram(int32_t programId, int32_t shaderId) = 0;

	/** 
	 * Links attached shaders to a program
	 * @param programId program id
	 * @return success
	 */
	virtual bool linkProgram(int32_t programId) = 0;

	/** 
	 * Returns location of given uniform variable
	 * @param programId program id
	 * @param name uniform name
	 * @return
	 */
	virtual int32_t getProgramUniformLocation(int32_t programId, const string& name) = 0;

	/** 
	 * Set up a integer uniform value
	 * @param context context
	 * @param uniformId uniform id
	 * @param value value
	 */
	virtual void setProgramUniformInteger(void* context, int32_t uniformId, int32_t value) = 0;

	/** 
	 * Set up a float uniform value
	 * @param context context
	 * @param uniformId uniform id
	 * @param value value
	 */
	virtual void setProgramUniformFloat(void* context, int32_t uniformId, float value) = 0;

	/** 
	 * Set up a float matrix 3x3 uniform value
	 * @param context context
	 * @param uniformId uniform id
	 * @param value value
	 */
	virtual void setProgramUniformFloatMatrix3x3(void* context, int32_t uniformId, const array<float, 9>& value) = 0;

	/**
	 * Set up a float matrix 4x4 uniform value
	 * @param context context
	 * @param uniformId uniform id
	 * @param value value
	 */
	virtual void setProgramUniformFloatMatrix4x4(void* context, int32_t uniformId, const array<float, 16>& value) = 0;

	/** 
	 * Set up a float matrices 4x4 uniform values
	 * @param context context
	 * @param uniformId uniform id
	 * @param count count
	 * @param data data
	 */
	virtual void setProgramUniformFloatMatrices4x4(void* context, int32_t uniformId, int32_t count, FloatBuffer* data) = 0;

	/** 
	 * Set up a float vec4 uniform value
	 * @param context context
	 * @param uniformId uniform id
	 * @param data data
	 */
	virtual void setProgramUniformFloatVec4(void* context, int32_t uniformId, const array<float, 4>& data) = 0;

	/** 
	 * Set up a float vec3 uniform value
	 * @param context context
	 * @param uniformId uniform id
	 * @param data data
	 */
	virtual void setProgramUniformFloatVec3(void* context, int32_t uniformId, const array<float, 3>& data) = 0;

	/** 
	 * Set up a float vec2 uniform value
	 * @param context context
	 * @param uniformId uniform id
	 * @param data data
	 */
	virtual void setProgramUniformFloatVec2(void* context, int32_t uniformId, const array<float, 2>& data) = 0;

	/**
	 * Bind attribute to a input location
	 * @param programId program id
	 * @param location location
	 * @param name attribute name
	 */
	virtual void setProgramAttributeLocation(int32_t programId, int32_t location, const string& name) = 0;

	/** 
	 * Set up viewport parameter
	 * @param x x
	 * @param y y
	 * @param width width
	 * @param height height
	 */
	virtual void setViewPort(int32_t x, int32_t y, int32_t width, int32_t height) = 0;

	/** 
	 * Update viewport
	 */
	virtual void updateViewPort() = 0;

	/** 
	 * @return projection matrix
	 */
	virtual Matrix4x4& getProjectionMatrix();

	/** 
	 * Update projection matrix event
	 * @param context context
	 */
	virtual void onUpdateProjectionMatrix(void* context) = 0;

	/** 
	 * @return camera matrix
	 */
	virtual Matrix4x4& getCameraMatrix();

	/** 
	 * Update camera matrix event
	 * @param context context
	 */
	virtual void onUpdateCameraMatrix(void* context) = 0;

	/** 
	 * @return model view matrix
	 */
	virtual Matrix4x4& getModelViewMatrix();

	/** 
	 * Update model view matrix event
	 * @param context context
	 */
	virtual void onUpdateModelViewMatrix(void* context) = 0;

	/** 
	 * @return view port matrix
	 */
	virtual Matrix4x4& getViewportMatrix();

	/** 
	 * Get texture matrix
	 * @param context context
	 * @return texture matrix
	 */
	virtual Matrix2D3x3& getTextureMatrix(void* context) = 0;

	/**
	 * Update texture matrix for active texture unit event
	 * @param context context
	 */
	virtual void onUpdateTextureMatrix(void* context) = 0;

	/** 
	 * Set up clear color
	 * @param red red
	 * @param green green
	 * @param blue blue
	 * @param alpha alpha
	 */
	virtual void setClearColor(float red, float green, float blue, float alpha) = 0;

	/** 
	 * Enable culling
	 */
	virtual void enableCulling() = 0;

	/** 
	 * Disable culling
	 */
	virtual void disableCulling() = 0;

	/** 
	 * Enables blending
	 */
	virtual void enableBlending() = 0;

	/** 
	 * Disables blending
	 */
	virtual void disableBlending() = 0;

	/** 
	 * Enable depth buffer writing
	 */
	virtual void enableDepthBufferWriting() = 0;

	/** 
	 * Disable depth buffer writing
	 */
	virtual void disableDepthBufferWriting() = 0;

	/** 
	 * Disable depth buffer test
	 */
	virtual void disableDepthBufferTest() = 0;

	/**
	 * Enable depth buffer test
	 */
	virtual void enableDepthBufferTest() = 0;

	/**
	 * Set up depth function
	 * @param depthFunction depth function
	 */
	virtual void setDepthFunction(int32_t depthFunction) = 0;

	/** 
	 * Set up GL rendering colormask
	 * @param red red
	 * @param green green
	 * @param blue blue
	 * @param alpha alpha
	 */
	virtual void setColorMask(bool red, bool green, bool blue, bool alpha) = 0;

	/** 
	 * Clear render buffer with given mask
	 * @param mask mask
	 */
	virtual void clear(int32_t mask) = 0;

	/**
	 * Sets up which face will be culled
	 * @param cullFace cull face
	 */
	virtual void setCullFace(int32_t cullFace) = 0;

	/** 
	 * Set up clock wise or counter clock wise faces as front face 
	 * @param frontFace frontFace
	 */
	virtual void setFrontFace(int32_t frontFace) = 0;

	/** 
	 * Creates a texture
	 * @return texture id
	 */
	virtual int32_t createTexture() = 0;

	/** 
	 * Creates a depth buffer texture
	 * @param width width
	 * @param height height
	 * @return depth texture id
	 */
	virtual int32_t createDepthBufferTexture(int32_t width, int32_t height) = 0;

	/** 
	 * Creates a color buffer texture
	 * @param width width
	 * @param height height
	 * @return color buffer texture id
	 */
	virtual int32_t createColorBufferTexture(int32_t width, int32_t height) = 0;

	/**
	 * Uploads texture data to current bound texture
	 * @param context context
	 * @param texture texture
	 */
	virtual void uploadTexture(void* context, Texture* texture) = 0;

	/** 
	 * Resizes a depth texture
	 * @param textureId texture id
	 * @param width width
	 * @param height height
	 */
	virtual void resizeDepthBufferTexture(int32_t textureId, int32_t width, int32_t height) = 0;

	/** 
	 * Resize color buffer texture
	 * @param textureId texture id
	 * @param width width
	 * @param height height
	 */
	virtual void resizeColorBufferTexture(int32_t textureId, int32_t width, int32_t height) = 0;

	/** 
	 * Binds a texture with given id or unbinds when using ID_NONE
	 * @param context context
	 * @param textureId textureId
	 */
	virtual void bindTexture(void* context, int32_t textureId) = 0;

	/** 
	 * On bind texture event
	 * @param context context
	 * @param textureId textureId
	 */
	virtual void onBindTexture(void* context, int32_t textureId) = 0;

	/** 
	 * Dispose a texture
	 * @param textureId texture id
	 */
	virtual void disposeTexture(int32_t textureId) = 0;

	/** 
	 * Creates a frame buffer object with depth texture attached
	 * @param depthBufferTextureGlId colorBufferTextureGlId TODO
	 * @param colorBufferTextureGlId depth texture gl id
	 * @return frame buffer object id
	 */
	virtual int32_t createFramebufferObject(int32_t depthBufferTextureGlId, int32_t colorBufferTextureGlId) = 0;

	/** 
	 * Enables a framebuffer to be rendered
	 * @param frameBufferId frameBufferId
	 */
	virtual void bindFrameBuffer(int32_t frameBufferId) = 0;

	/** 
	 * Disposes a frame buffer object
	 * @param frameBufferId frame buffer id
	 */
	virtual void disposeFrameBufferObject(int32_t frameBufferId) = 0;

	/** 
	 * Generate buffer objects for vertex data and such
	 * @param buffers buffers
	 * @param use GPU memory
	 * @return ids
	 */
	virtual vector<int32_t> createBufferObjects(int32_t buffers, bool useGPUMemory) = 0;

	/** 
	 * Uploads buffer data to buffer object
	 * @param context context
	 * @param bufferObjectId buffer object id
	 * @param size size
	 * @param data data
	 */
	virtual void uploadBufferObject(void* context, int32_t bufferObjectId, int32_t size, FloatBuffer* data) = 0;

	/** 
	 * Uploads buffer data to buffer object
	 * @param context context
	 * @param bufferObjectId buffer object id
	 * @param size size
	 * @param data data
	 */
	virtual void uploadIndicesBufferObject(void* context, int32_t bufferObjectId, int32_t size, ShortBuffer* data) = 0;

	/** 
	 * Uploads buffer data to buffer object
	 * @param context context
	 * @param bufferObjectId buffer object id
	 * @param size size
	 * @param data data
	 */
	virtual void uploadIndicesBufferObject(void* context, int32_t bufferObjectId, int32_t size, IntBuffer* data) = 0;

	/** 
	 * Bind indices buffer object
	 * @param context context
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindIndicesBufferObject(void* context, int32_t bufferObjectId) = 0;

	/** 
	 * Bind texture coordinates buffer object
	 * @param context context
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindTextureCoordinatesBufferObject(void* context, int32_t bufferObjectId) = 0;

	/** 
	 * Bind vertices buffer object
	 * @param context context
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindVerticesBufferObject(void* context, int32_t bufferObjectId) = 0;

	/** 
	 * Bind normals buffer object
	 * @param context context
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindNormalsBufferObject(void* context, int32_t bufferObjectId) = 0;

	/** 
	 * Bind colors buffer object
	 * @param context context
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindColorsBufferObject(void* context, int32_t bufferObjectId) = 0;

	/** 
	 * Bind tangents buffer object
	 * @param context context
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindTangentsBufferObject(void* context, int32_t bufferObjectId) = 0;

	/** 
	 * Bind bitangents buffer object
	 * @param context context
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindBitangentsBufferObject(void* context, int32_t bufferObjectId) = 0;

	/** 
	 * Bind model matrices buffer object
	 * @param context context
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindModelMatricesBufferObject(void* context, int32_t bufferObjectId) = 0;

	/**
	 * Bind effect color muls buffer object
	 * @param context context
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindEffectColorMulsBufferObject(void* context, int32_t bufferObjectId) = 0;

	/**
	 * Bind effect color adds buffer object
	 * @param context context
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindEffectColorAddsBufferObject(void* context, int32_t bufferObjectId) = 0;

	/**
	 * Bind origins buffer object
	 * @param context context
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindOrigins(void* context, int32_t bufferObjectId) = 0;

	/**
	 * Draw instanced indexed triangles from buffer objects
	 * @param context context
	 * @param triangles triangles
	 * @param trianglesOffset triangles offset
	 * @param instances instances
	 */
	virtual void drawInstancedIndexedTrianglesFromBufferObjects(void* context, int32_t triangles, int32_t trianglesOffset, int32_t instances) = 0;

	/**
	 * Draw indexed triangles from buffer objects
	 * @param context context
	 * @param triangles triangles
	 * @param trianglesOffset triangles offset
	 */
	virtual void drawIndexedTrianglesFromBufferObjects(void* context, int32_t triangles, int32_t trianglesOffset) = 0;

	/** 
	 * Draw instanced triangles from buffer objects
	 * @param context context
	 * @param triangles triangles
	 * @param trianglesOffset triangles offset
	 * @param instances instances
	 */
	virtual void drawInstancedTrianglesFromBufferObjects(void* context, int32_t triangles, int32_t trianglesOffset, int32_t instances) = 0;

	/** 
	 * Draw triangles from buffer objects
	 * @param context context
	 * @param triangles triangles
	 * @param trianglesOffset triangles offset
	 */
	virtual void drawTrianglesFromBufferObjects(void* context, int32_t triangles, int32_t trianglesOffset) = 0;

	/**
	 * Draw points from buffer objects 
	 * @param context context
	 * @param points points
	 * @param pointsOffset points offset
	 */
	virtual void drawPointsFromBufferObjects(void* context, int32_t points, int32_t pointsOffset) = 0;

	/**
	 * Set line width
	 * @param lineWidth line width
	 */
	virtual void setLineWidth(float lineWidth) = 0;

	/**
	 * Draw lines from buffer objects
	 * @param context context
	 * @param points points
	 * @param pointsOffset points offset
	 */
	virtual void drawLinesFromBufferObjects(void* context, int32_t points, int32_t pointsOffset) = 0;

	/** 
	 * Unbind buffer objects
	 * @param context context
	 */
	virtual void unbindBufferObjects(void* context) = 0;

	/** 
	 * Disposes a frame buffer object
	 * @param bufferObjectIds frame buffer id
	 */
	virtual void disposeBufferObjects(vector<int32_t>& bufferObjectIds) = 0;

	/** 
	 * Get texture unit
	 * @param context context
	 * @return active texture unit
	 */
	virtual int32_t getTextureUnit(void* context) = 0;

	/** 
	 * Sets up texture unit
	 * @param context context
	 * @param textureUnit texture unit
	 */
	virtual void setTextureUnit(void* context, int32_t textureUnit) = 0;

	/**
	 * Get light
	 * @param context context
	 * @param lightId light id
	 * @return light
	 */
	virtual const Renderer_Light& getLight(void* context, int32_t lightId) = 0;

	/**
	 * Set light
	 * @param context context
	 * @param lightId light id
	 * @param light light
	 */
	virtual void setLight(void* context, int32_t lightId, const Renderer_Light& light) = 0;

	/** 
	 * Update light
	 * @param context context
	 * @param lightId light id
	 */
	virtual void onUpdateLight(void* context, int32_t lightId) = 0;

	/**
	 * Get effect color mul
	 * @param context
	 * @return effect color mul
	 */
	virtual const array<float, 4>& getEffectColorMul(void* context) = 0;

	/** 
	 * Set up effect color multiplication
	 * @param context context
	 * @param effectColorMul effect color for multiplication
	 */
	virtual void setEffectColorMul(void* context, const array<float, 4>& effectColorMul) = 0;

	/**
	 * Get effect color add
	 * @param context
	 * @return effect color add
	 */
	virtual const array<float, 4>& getEffectColorAdd(void* context) = 0;

	/** 
	 * Set up effect color addition
	 * @param context context
	 * @param effectColorAdd effect color for addition
	 */
	virtual void setEffectColorAdd(void* context, const array<float, 4>& effectColorAdd) = 0;

	/** 
	 * Update material
	 * @param context context
	 */
	virtual void onUpdateEffect(void* context) = 0;

	/** 
	 * Get material
	 * @param context context
	 * @return material
	 */
	virtual const Renderer_Material& getMaterial(void* context) = 0;

	/** 
	 * Set material
	 * @param context context
	 * @param material material
	 */
	virtual void setMaterial(void* context, const Renderer_Material& material) = 0;

	/** 
	 * On update material
	 * @param context context
	 */
	virtual void onUpdateMaterial(void* context) = 0;

	/**
	 * Set shader
	 * @param context context
	 */
	virtual const string& getShader(void* context) = 0;

	/**
	 * Set shader
	 * @param context context
	 * @param id shader id
	 */
	virtual void setShader(void* context, const string& id) = 0;

	/**
	 * On update shader
	 * @param context context
	 */
	virtual void onUpdateShader(void* context) = 0;

	/** 
	 * Reads a pixel depth
	 * @param x x
	 * @param y y
	 * @return depth 0.0f..1.0f
	 */
	virtual float readPixelDepth(int32_t x, int32_t y) = 0;

	/**
	 * Read pixels
	 * @param x x
	 * @param y y
	 * @param width width
	 * @param height height
	 * @return byte buffer
	 */
	virtual ByteBuffer* readPixels(int32_t x, int32_t y, int32_t width, int32_t height) = 0;

	/**
	 * Dispatch compute
	 * @param context context
	 * @param numGroupsX num groups x
	 * @param numGroupsY num groups y
	 * @param numGroupsZ num groups z
	 */
	virtual void dispatchCompute(void* context, int32_t numGroupsX, int32_t numGroupsY, int32_t numGroupsZ) = 0;

	/**
	 * Memory barrier
	 */
	virtual void memoryBarrier() = 0;

	/**
	 * Upload skinning buffer object
	 * @param context context
	 * @param bufferObjectId buffer object id
	 * @param size size
	 * @param data data
	 */
	virtual void uploadSkinningBufferObject(void* context, int32_t bufferObjectId, int32_t size, FloatBuffer* data) = 0;

	/**
	 * Upload skinning buffer object
	 * @param context context
	 * @param bufferObjectId buffer object id
	 * @param size size
	 * @param data data
	 */
	virtual void uploadSkinningBufferObject(void* context, int32_t bufferObjectId, int32_t size, IntBuffer* data) = 0;

	/**
	 * Bind skinning vertices buffer object
	 * @param context context
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindSkinningVerticesBufferObject(void* context, int32_t bufferObjectId) = 0;

	/**
	 * Bind skinning normal buffer object
	 * @param context context
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindSkinningNormalsBufferObject(void* context, int32_t bufferObjectId) = 0;

	/**
	 * Bind skinning vertex joints buffer object
	 * @param context context
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindSkinningVertexJointsBufferObject(void* context, int32_t bufferObjectId) = 0;

	/**
	 * Bind skinning vertex joint indices buffer object
	 * @param context context
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindSkinningVertexJointIdxsBufferObject(void* context, int32_t bufferObjectId) = 0;

	/**
	 * Bind skinning vertex joint weights buffer object
	 * @param context context
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindSkinningVertexJointWeightsBufferObject(void* context, int32_t bufferObjectId) = 0;

	/**
	 * Bind skinning vertices result buffer object
	 * @param context context
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindSkinningVerticesResultBufferObject(void* context, int32_t bufferObjectId) = 0;

	/**
	 * Bind skinning normals result buffer object
	 * @param context context
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindSkinningNormalsResultBufferObject(void* context, int32_t bufferObjectId) = 0;

	/**
	 * Bind skinning matrices result buffer object
	 * @param context context
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindSkinningMatricesBufferObject(void* context, int32_t bufferObjectId) = 0;

	/**
	 * Create a single vertex array object
	 */
	virtual int32_t createVertexArrayObject() = 0;

	/**
	 * Dispose a single vertex array object
	 * @param vertexArrayObjectId vertex array object id
	 */
	virtual void disposeVertexArrayObject(int32_t vertexArrayObjectId) = 0;

	/**
	 * Bind a single vertex array object
	 * @param vertexArrayObjectId vertex array object id
	 */
	virtual void bindVertexArrayObject(int32_t vertexArrayObjectId) = 0;

	/** 
	 * Set up renderer for GUI rendering
	 */
	virtual void initGuiMode() = 0;

	/** 
	 * Set up renderer for 3d rendering
	 */
	virtual void doneGuiMode() = 0;

	/**
	 * Public constructor
	 */
	Renderer();

	/**
	 * Destructor
	 */
	virtual ~Renderer();
};
