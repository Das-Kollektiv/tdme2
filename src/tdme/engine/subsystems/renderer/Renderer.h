#pragma once

#if defined(_MSC_VER)
	// this suppresses a warning redefinition of APIENTRY macro
	#define NOMINMAX
	#include <windows.h>
#endif
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <array>
#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/EntityShaderParameters.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Matrix2D3x3.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utilities/fwd-tdme.h>

using std::array;
using std::map;
using std::string;
using std::vector;

using tdme::engine::Texture;
using tdme::engine::EntityShaderParameters;
using tdme::math::Matrix2D3x3;
using tdme::math::Matrix4x4;
using tdme::utilities::ByteBuffer;
using tdme::utilities::FloatBuffer;
using tdme::utilities::IntBuffer;
using tdme::utilities::ShortBuffer;

/**
 * Renderer interface
 * @author Andreas Drewke
 * @ersion $Id$
 */
class tdme::engine::subsystems::renderer::Renderer
{
public:

	enum RendererType { RENDERERTYPE_NONE, RENDERERTYPE_OPENGLES, RENDERERTYPE_OPENGL, RENDERERTYPE_VULKAN };

	/**
	 * Bean holding light properties
	 */
	struct Renderer_Light
	{
		int32_t enabled { 0 };
		array<float, 4> ambient {{ 0.0f, 0.0f, 0.0f, 1.0f }};
		array<float, 4> diffuse {{ 1.0f, 1.0f, 1.0f, 1.0f }};
		array<float, 4> specular {{ 1.0f, 1.0f, 1.0f, 1.0f }};
		array<float, 4> position {{ 0.0f, 0.0f, 0.0f, 0.0f }};
		array<float, 3> spotDirection {{ 0.0f, 0.0f, -1.0f }};
		float spotExponent { 0.0f };
		float spotCosCutoff { 0.0f };
		float constantAttenuation { 1.0f };
		float linearAttenuation { 0.0f };
		float quadraticAttenuation { 0.0f };
		float radius { 0.0f };
	};

	/**
	 * Bean holding PBR material properties
	 */
	struct Renderer_PBRMaterial
	{
		array<float, 4> baseColorFactor {{ 1.0f, 1.0f, 1.0f, 1.0f }};
		float metallicFactor { 1.0f };
		float roughnessFactor { 1.0f };
		float normalScale { 1.0f };
		array<float, 3> emissiveFactor {{ 1.0f, 1.0f, 1.0f }};
		float exposure { 1.0f };
		int baseColorTextureMaskedTransparency { 0 };
		float baseColorTextureMaskedTransparencyThreshold { 0.0f };
	};

	/**
	 *  Bean holding specular material properties
	 */
	struct Renderer_SpecularMaterial
	{
		array<float, 4> ambient {{ 0.2f, 0.2f, 0.2f, 1.0f }};
		array<float, 4> diffuse {{ 0.8f, 0.8f, 0.8f, 1.0f }};
		array<float, 4> specular {{ 0.0f, 0.0f, 0.0f, 1.0f }};
		array<float, 4> emission {{ 0.0f, 0.0f, 0.0f, 1.0f }};
		float shininess { 0.0f };
		float reflection { 0.0f };
		int diffuseTextureMaskedTransparency { 0 };
		float diffuseTextureMaskedTransparencyThreshold { 0.0f };
		int textureAtlasSize { 1 };
		array<float, 2>  textureAtlasPixelDimension { 0.0f, 0.0f };
	};

	struct Renderer_Context {
		array<float, 4> effectColorMul {{ 1.0f, 1.0f, 1.0f, 1.0f }};
		array<float, 4> effectColorAdd {{ 0.0f, 0.0f, 0.0f, 0.0f }};
		Renderer_SpecularMaterial specularMaterial {};
		Renderer_PBRMaterial pbrMaterial {};
		array<Renderer_Light, 8> lights {}; // TODO: we need this dynamically
		Matrix2D3x3 textureMatrix {};
		float maskMaxValue { 1.0f };
		int32_t lighting { 0 };
		array<float, 3> environmentMappingCubeMapPosition;
		string shader;
		EntityShaderParameters shaderParameters;
	};

	/**
	 * Bean holding light properties
	 */
	struct Renderer_Statistics
	{
		int64_t time { -1LL };
		int64_t memoryUsageGPU { -1LL };
		int64_t memoryUsageShared { -1LL };
		uint32_t clearCalls { 0 };
		uint32_t renderCalls { 0 };
		uint32_t computeCalls { 0 };
		uint32_t instances { 0 };
		uint32_t triangles { 0 };
		uint32_t points { 0 };
		uint32_t linePoints { 0 };
		uint32_t bufferUploads { 0 };
		uint32_t textureUploads { 0 };
		uint32_t renderPasses { 0 };
		uint32_t drawCommands { 0 };
		uint32_t submits { 0 };
		uint32_t disposedTextures { 0 };
		uint32_t disposedBuffers { 0 };
	};

	RendererType rendererType { RENDERERTYPE_NONE };

	int32_t CONTEXTINDEX_DEFAULT;

	int32_t ID_NONE;
	int32_t CLEAR_DEPTH_BUFFER_BIT;
	int32_t CLEAR_COLOR_BUFFER_BIT;
	int32_t CULLFACE_FRONT;
	int32_t CULLFACE_BACK;
	int32_t TEXTUREUNITS_MAX;
	int32_t PROGRAM_GUI;
	int32_t PROGRAM_OBJECTS;
	int32_t PROGRAM_POINTS;
	int32_t PROGRAM_LINES;
	int32_t PROGRAM_COMPUTE;
	int32_t SHADER_FRAGMENT_SHADER;
	int32_t SHADER_VERTEX_SHADER;
	int32_t SHADER_COMPUTE_SHADER;
	int32_t DEPTHFUNCTION_ALWAYS;
	int32_t DEPTHFUNCTION_EQUAL;
	int32_t DEPTHFUNCTION_LESSEQUAL;
	int32_t DEPTHFUNCTION_GREATEREQUAL;
	int32_t FRAMEBUFFER_DEFAULT;
	int32_t FRONTFACE_CW;
	int32_t FRONTFACE_CCW;
	int32_t CUBEMAPTEXTUREINDEX_NEGATIVE_X;
	int32_t CUBEMAPTEXTUREINDEX_POSITIVE_X;
	int32_t CUBEMAPTEXTUREINDEX_POSITIVE_Y;
	int32_t CUBEMAPTEXTUREINDEX_NEGATIVE_Y;
	int32_t CUBEMAPTEXTUREINDEX_POSITIVE_Z;
	int32_t CUBEMAPTEXTUREINDEX_NEGATIVE_Z;

	int32_t LIGHTING_NONE;
	int32_t LIGHTING_SPECULAR;
	int32_t LIGHTING_PBR;

	int32_t UNIFORM_CL_SKINNING_VERTEX_COUNT;
	int32_t UNIFORM_CL_SKINNING_MATRIX_COUNT;
	int32_t UNIFORM_CL_SKINNING_INSTANCE_COUNT;

protected:
	int32_t viewPortWidth;
	int32_t viewPortHeight;
	Renderer_Statistics statistics;
	Vector3 cameraPosition;
	Matrix4x4 projectionMatrix;
	Matrix4x4 cameraMatrix;
	Matrix4x4 modelViewMatrix;
	Matrix4x4 viewportMatrix;
	int32_t effectPass;
	string shaderPrefix;

	vector<Renderer_Context> rendererContexts;

public:
	// forbid class copy
	FORBID_CLASS_COPY(Renderer)

	/**
	 * Public constructor
	 */
	Renderer();

	/**
	 * Destructor
	 */
	virtual ~Renderer();

	/**
	 * @return renderer type
	 */
	inline RendererType getRendererType() {
		return rendererType;
	}

	/**
	 * Prepare window system renderer context
	 * @param tryIdx try index
	 */
	virtual bool prepareWindowSystemRendererContext(int tryIdx) = 0;

	/**
	 * Initialize window system renderer context
	 * @param glfwWindow GLFL window
	 */
	virtual bool initializeWindowSystemRendererContext(GLFWwindow* glfwWindow) = 0;

	/**
	 * Initialize renderer
	 */
	virtual void initialize() = 0;

	/**
	 * Pre Frame Initialization
	 */
	virtual void initializeFrame() = 0;

	/**
	 * Finish frame
	 */
	virtual void finishFrame() = 0;

	/**
	 * @return vendor
	 */
	virtual const string getVendor() = 0;

	/**
	 * @return renderer
	 */
	virtual const string getRenderer() = 0;

	/**
	 * @return shader version e.g. gl2, gl3 or gles2
	 */
	virtual const string getShaderVersion() = 0;

	/**
	 * @return if renderer is supporting multi threaded rendering
	 */
	virtual bool isSupportingMultithreadedRendering() = 0;

	/**
	 * @return returns if texture compression is available
	 */
	virtual bool isTextureCompressionAvailable() = 0;

	/**
	 * @return requires program attribute location
	 */
	virtual bool isUsingProgramAttributeLocation() = 0;

	/**
	 * @return is supporting integer program attributes
	 */
	virtual bool isSupportingIntegerProgramAttributes() = 0;

	/**
	 * @return if specular mapping is supported
	 */
	virtual bool isSpecularMappingAvailable() = 0;

	/**
	 * @return if normal mapping is supported
	 */
	virtual bool isNormalMappingAvailable() = 0;

	/**
	 * Checks if instanced rendering is available
	 * @return instance rendering availability
	 */
	virtual bool isInstancedRenderingAvailable() = 0;

	/**
	 * @return if PBR lighting is supported
	 */
	virtual bool isPBRAvailable() = 0;

	/**
	 * @return if compute shaders are available
	 */
	virtual bool isComputeShaderAvailable() = 0;

	/**
	 * @return if OpenGL+CL is available
	 */
	virtual bool isGLCLAvailable() = 0;

	/**
	 * @return Returns if renderer is using short indices, otherwise it uses int indices
	 */
	virtual bool isUsingShortIndices() = 0;

	/**
	 * @return If deferred shading is available
	 */
	virtual bool isDeferredShadingAvailable() = 0;

	/**
	 * @return number of texture units
	 */
	virtual int32_t getTextureUnits() = 0;

	/**
	 * @return viewport width
	 */
	inline int32_t getViewPortWidth() {
		return viewPortWidth;
	}

	/**
	 * @return viewport height
	 */
	inline int32_t getViewPortHeight() {
		return viewPortHeight;
	}

	/**
	 * Loads a shader
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
	 * @param contextIdx context index
	 * @param programId programId
	 */
	virtual void useProgram(int contextIdx, int32_t programId) = 0;

	/**
	 * Creates a shader program
	 * @param type type
	 * @return int
	 */
	virtual int32_t createProgram(int type) = 0;

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
	 * @param contextIdx context index
	 * @param uniformId uniform id
	 * @param value value
	 */
	virtual void setProgramUniformInteger(int contextIdx, int32_t uniformId, int32_t value) = 0;

	/**
	 * Set up a float uniform value
	 * @param contextIdx context index
	 * @param uniformId uniform id
	 * @param value value
	 */
	virtual void setProgramUniformFloat(int contextIdx, int32_t uniformId, float value) = 0;

	/**
	 * Set up a float matrix 3x3 uniform value
	 * @param contextIdx context index
	 * @param uniformId uniform id
	 * @param value value
	 */
	virtual void setProgramUniformFloatMatrix3x3(int contextIdx, int32_t uniformId, const array<float, 9>& value) = 0;

	/**
	 * Set up a float matrix 4x4 uniform value
	 * @param contextIdx context index
	 * @param uniformId uniform id
	 * @param value value
	 */
	virtual void setProgramUniformFloatMatrix4x4(int contextIdx, int32_t uniformId, const array<float, 16>& value) = 0;

	/**
	 * Set up a float matrices 4x4 uniform values
	 * @param contextIdx context index
	 * @param uniformId uniform id
	 * @param count count
	 * @param data data
	 */
	virtual void setProgramUniformFloatMatrices4x4(int contextIdx, int32_t uniformId, int32_t count, FloatBuffer* data) = 0;

	/**
	 * Set up a float vec4 uniform value
	 * @param contextIdx context index
	 * @param uniformId uniform id
	 * @param data data
	 */
	virtual void setProgramUniformFloatVec4(int contextIdx, int32_t uniformId, const array<float, 4>& data) = 0;

	/**
	 * Set up a float vec3 uniform value
	 * @param contextIdx context index
	 * @param uniformId uniform id
	 * @param data data
	 */
	virtual void setProgramUniformFloatVec3(int contextIdx, int32_t uniformId, const array<float, 3>& data) = 0;

	/**
	 * Set up a float vec2 uniform value
	 * @param contextIdx context index
	 * @param uniformId uniform id
	 * @param data data
	 */
	virtual void setProgramUniformFloatVec2(int contextIdx, int32_t uniformId, const array<float, 2>& data) = 0;

	/**
	 * Bind attribute to a input location
	 * @param programId program id
	 * @param location location
	 * @param name attribute name
	 */
	virtual void setProgramAttributeLocation(int32_t programId, int32_t location, const string& name) = 0;

	/**
	 * Get effect pass
	 * @return effect pass
	 */
	inline int32_t getEffectPass() {
		return effectPass;
	}

	/**
	 * Set effect pass
	 * @param effectPass effect pass
	 */
	inline void setEffectPass(int32_t effectPass) {
		this->effectPass = effectPass;
	}

	/**
	 * Get shader prefix
	 * @return shader prefix
	 */
	inline const string& getShaderPrefix() {
		return shaderPrefix;
	}

	/**
	 * Set shader prefix
	 * @param shaderPrefix shader prefix
	 */
	inline void setShaderPrefix(const string& shaderPrefix) {
		this->shaderPrefix = shaderPrefix;
	}

	/**
	 * Get current lighting model
	 * @param contextIdx context index
	 * @return lighting, see LIGHTING_*
	 */
	inline int32_t getLighting(int contextIdx) {
		auto& rendererContext = rendererContexts[contextIdx];
		return rendererContext.lighting;
	}

	/**
	 * Set current lighting model
	 * @param contextIdx context index
	 * @param lighting lighting, see LIGHTING_*
	 */
	inline void setLighting(int contextIdx, int32_t lighting) {
		auto& rendererContext = rendererContexts[contextIdx];
		rendererContext.lighting = lighting;
	}

	/**
	 * @return camera position
	 */
	inline Vector3& getCameraPosition() {
		return cameraPosition;
	}

	/**
	 * Set up viewport parameter
	 * @param width width
	 * @param height height
	 */
	virtual void setViewPort(int32_t width, int32_t height) = 0;

	/**
	 * Update viewport
	 */
	virtual void updateViewPort() = 0;

	/**
	 * @return projection matrix
	 */
	inline Matrix4x4& getProjectionMatrix() {
		return projectionMatrix;
	}

	/**
	 * Update projection matrix event
	 * @param contextIdx context index
	 */
	virtual void onUpdateProjectionMatrix(int contextIdx) = 0;

	/**
	 * @return camera matrix
	 */
	inline Matrix4x4& getCameraMatrix() {
		return cameraMatrix;
	}

	/**
	 * Update camera matrix event
	 * @param contextIdx context index
	 */
	virtual void onUpdateCameraMatrix(int contextIdx) = 0;

	/**
	 * @return model view matrix or in some cases the model matrix
	 */
	inline Matrix4x4& getModelViewMatrix() {
		return modelViewMatrix;
	}

	/**
	 * Update model view matrix event
	 * @param contextIdx context index
	 */
	virtual void onUpdateModelViewMatrix(int contextIdx) = 0;

	/**
	 * @return view port matrix
	 */
	inline Matrix4x4& getViewportMatrix() {
		return viewportMatrix;
	}

	/**
	 * Get texture matrix
	 * @param contextIdx context index
	 * @return texture matrix
	 */
	inline Matrix2D3x3& getTextureMatrix(int contextIdx) {
		auto& rendererContext = rendererContexts[contextIdx];
		return rendererContext.textureMatrix;
	}

	/**
	 * Update texture matrix for active texture unit event
	 * @param contextIdx context index
	 */
	virtual void onUpdateTextureMatrix(int contextIdx) = 0;

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
	 * @param contextIdx context index
	 */
	virtual void enableCulling(int contextIdx) = 0;

	/**
	 * Disable culling
	 * @param contextIdx context index
	 */
	virtual void disableCulling(int contextIdx) = 0;

	/**
	 * Set up clock wise or counter clock wise faces as front face
	 * @param contextIdx context index
	 * @param frontFace frontFace
	 */
	virtual void setFrontFace(int contextIdx, int32_t frontFace) = 0;

	/**
	 * Sets up which face will be culled
	 * @param cullFace cull face
	 */
	virtual void setCullFace(int32_t cullFace) = 0;

	/**
	 * Enables blending
	 */
	virtual void enableBlending() = 0;

	/**
	 * Enable blending with c = a + b
	 */
	virtual void enableAdditionBlending() = 0;

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
	 * Creates a texture
	 * @return texture id
	 */
	virtual int32_t createTexture() = 0;

	/**
	 * Creates a depth buffer texture
	 * @param width width
	 * @param height height
	 * @oaram cubeMapTextureId cube map texture id
	 * @param cubeMapTextureIndex cube map texture index
	 * @return depth texture id
	 */
	virtual int32_t createDepthBufferTexture(int32_t width, int32_t height, int32_t cubeMapTextureId, int32_t cubeMapTextureIndex) = 0;

	/**
	 * Creates a color buffer texture
	 * @param width width
	 * @param height height
	 * @oaram cubeMapTextureId cube map texture id
	 * @param cubeMapTextureIndex cube map texture index
	 * @return color buffer texture id
	 */
	virtual int32_t createColorBufferTexture(int32_t width, int32_t height, int32_t cubeMapTextureId, int32_t cubeMapTextureIndex) = 0;

	/**
	 * Creates a geometry buffer geometry texture
	 * @param width width
	 * @param height height
	 * @return geometry buffer geometry texture id
	 */
	virtual int32_t createGBufferGeometryTexture(int32_t width, int32_t height) = 0;

	/**
	 * Creates a geometry buffer color RGBA texture
	 * @param width width
	 * @param height height
	 * @return geometry buffer color RGBA texture id
	 */
	virtual int32_t createGBufferColorTexture(int32_t width, int32_t height) = 0;

	/**
	 * Uploads texture data to current bound texture
	 * @param contextIdx context index
	 * @param texture texture
	 */
	virtual void uploadTexture(int contextIdx, Texture* texture) = 0;

	/**
	 * Uploads cube map texture data to current bound texture
	 * @param contextIdx context index
	 * @param textureLeft texture left
	 * @param textureRight texture right
	 * @param textureTop texture top
	 * @param textureBottom texture bottom
	 * @param textureFront texture front
	 * @param textureBack texture back
	 */
	virtual void uploadCubeMapTexture(int contextIdx, Texture* textureLeft, Texture* textureRight, Texture* textureTop, Texture* textureBottom, Texture* textureFront, Texture* textureBack) = 0;

	/**
	 * Create cube map texture from frame buffers
	 * @param contextIdx context index
	 * @param width width
	 * @param height height
	 * @return texture id
	 */
	virtual int32_t createCubeMapTexture(int contextIdx, int32_t width, int32_t height) = 0;

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
	 * Resizes a geometry buffer geometry texture
	 * @param textureId texture id
	 * @param width width
	 * @param height height
	 * @return geometry buffer geometry texture id
	 */
	virtual void resizeGBufferGeometryTexture(int32_t textureId, int32_t width, int32_t height) = 0;

	/**
	 * Resizes a geometry buffer color RGBA texture
	 * @param textureId texture id
	 * @param width width
	 * @param height height
	 * @return geometry buffer color RGBA texture id
	 */
	virtual void resizeGBufferColorTexture(int32_t textureId, int32_t width, int32_t height) = 0;

	/**
	 * Binds a texture with given id or unbinds when using ID_NONE
	 * @param contextIdx context index
	 * @param textureId textureId
	 */
	virtual void bindTexture(int contextIdx, int32_t textureId) = 0;

	/**
	 * Binds a cube map texture with given id or unbinds when using ID_NONE
	 * @param contextIdx context index
	 * @param textureId textureId
	 */
	virtual void bindCubeMapTexture(int contextIdx, int32_t textureId) = 0;

	/**
	 * On bind texture event
	 * @param contextIdx context index
	 * @param textureId textureId
	 */
	virtual void onBindTexture(int contextIdx, int32_t textureId) = 0;

	/**
	 * Dispose a texture
	 * @param textureId texture id
	 */
	virtual void disposeTexture(int32_t textureId) = 0;

	/**
	 * Creates a frame buffer object with depth texture attached
	 * @param depthBufferTextureId depth buffer texture id
	 * @param colorBufferTextureId color buffer texture id
	 * @param cubeMapTextureId cube map texture id
	 * @param cubeMapTextureIndex cube map texture index
	 * @return frame buffer object id
	 */
	virtual int32_t createFramebufferObject(int32_t depthBufferTextureId, int32_t colorBufferTextureId, int32_t cubeMapTextureId = 0, int32_t cubeMapTextureIndex = 0) = 0;

	/**
	 * Creates a geometry frame buffer object
	 * @param depthBufferTextureId depth buffer texture id
	 * @param geometryBufferTextureId1 geometry texture id 1
	 * @param geometryBufferTextureId2 geometry texture id 2
	 * @param geometryBufferTextureId3 geometry texture id 3
	 * @param colorBufferTextureId1 color buffer texture id 1
	 * @param colorBufferTextureId2 color buffer texture id 2
	 * @param colorBufferTextureId3 color buffer texture id 3
	 * @param colorBufferTextureId4 color buffer texture id 4
	 * @param colorBufferTextureId5 color buffer texture id 5
	 * @return frame buffer object id
	 */
	virtual int32_t createGeometryBufferObject(
		int32_t depthBufferTextureId,
		int32_t geometryBufferTextureId1,
		int32_t geometryBufferTextureId2,
		int32_t geometryBufferTextureId3,
		int32_t colorBufferTextureId1,
		int32_t colorBufferTextureId2,
		int32_t colorBufferTextureId3,
		int32_t colorBufferTextureId4,
		int32_t colorBufferTextureId5
	) = 0;

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
	 * @param useGPUMemory use GPU memory
	 * @param shared shared between different threads
	 * @return ids
	 */
	virtual vector<int32_t> createBufferObjects(int32_t buffers, bool useGPUMemory, bool shared) = 0;

	/**
	 * Uploads buffer data to buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 * @param size size
	 * @param data data
	 */
	virtual void uploadBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, FloatBuffer* data) = 0;

	/**
	 * Uploads buffer data to buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 * @param size size
	 * @param data data
	 */
	virtual void uploadBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, IntBuffer* data) = 0;

	/**
	 * Uploads buffer data to buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 * @param size size
	 * @param data data
	 */
	virtual void uploadBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, ShortBuffer* data) = 0;

	/**
	 * Uploads buffer data to buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 * @param size size
	 * @param data data
	 */
	virtual void uploadIndicesBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, ShortBuffer* data) = 0;

	/**
	 * Uploads buffer data to buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 * @param size size
	 * @param data data
	 */
	virtual void uploadIndicesBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, IntBuffer* data) = 0;

	/**
	 * Bind indices buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindIndicesBufferObject(int contextIdx, int32_t bufferObjectId) = 0;

	/**
	 * Bind solid colors buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindSolidColorsBufferObject(int contextIdx, int32_t bufferObjectId) = 0;

	/**
	 * Bind texture coordinates buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindTextureCoordinatesBufferObject(int contextIdx, int32_t bufferObjectId) = 0;

	/**
	 * Bind vertices buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindVerticesBufferObject(int contextIdx, int32_t bufferObjectId) = 0;

	/**
	 * Bind vertices 2 buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindVertices2BufferObject(int contextIdx, int32_t bufferObjectId) = 0;

	/**
	 * Bind normals buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindNormalsBufferObject(int contextIdx, int32_t bufferObjectId) = 0;

	/**
	 * Bind colors buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindColorsBufferObject(int contextIdx, int32_t bufferObjectId) = 0;

	/**
	 * Bind tangents buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindTangentsBufferObject(int contextIdx, int32_t bufferObjectId) = 0;

	/**
	 * Bind bitangents buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindBitangentsBufferObject(int contextIdx, int32_t bufferObjectId) = 0;

	/**
	 * Bind model matrices buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindModelMatricesBufferObject(int contextIdx, int32_t bufferObjectId) = 0;

	/**
	 * Bind effect color muls buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 * @param divisor divisor
	 */
	virtual void bindEffectColorMulsBufferObject(int contextIdx, int32_t bufferObjectId, int32_t divisor) = 0;

	/**
	 * Bind effect color adds buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 * @param divisor divisor
	 */
	virtual void bindEffectColorAddsBufferObject(int contextIdx, int32_t bufferObjectId, int32_t divisor) = 0;

	/**
	 * Bind origins buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindOriginsBufferObject(int contextIdx, int32_t bufferObjectId) = 0;

	/**
	 * Bind texture and sprite indices buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindTextureSpriteIndicesBufferObject(int contextIdx, int32_t bufferObjectId) = 0;

	/**
	 * Bind point sizes buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindPointSizesBufferObject(int contextIdx, int32_t bufferObjectId) = 0;

	/**
	 * Bind sprite sheet dimension buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindSpriteSheetDimensionBufferObject(int contextIdx, int32_t bufferObjectId) = 0;

	/**
	 * Draw instanced indexed triangles from buffer objects
	 * @param contextIdx context index
	 * @param triangles triangles
	 * @param trianglesOffset triangles offset
	 * @param instances instances
	 */
	virtual void drawInstancedIndexedTrianglesFromBufferObjects(int contextIdx, int32_t triangles, int32_t trianglesOffset, int32_t instances) = 0;

	/**
	 * Draw indexed triangles from buffer objects
	 * @param contextIdx context index
	 * @param triangles triangles
	 * @param trianglesOffset triangles offset
	 */
	virtual void drawIndexedTrianglesFromBufferObjects(int contextIdx, int32_t triangles, int32_t trianglesOffset) = 0;

	/**
	 * Draw instanced triangles from buffer objects
	 * @param contextIdx context index
	 * @param triangles triangles
	 * @param trianglesOffset triangles offset
	 * @param instances instances
	 */
	virtual void drawInstancedTrianglesFromBufferObjects(int contextIdx, int32_t triangles, int32_t trianglesOffset, int32_t instances) = 0;

	/**
	 * Draw triangles from buffer objects
	 * @param contextIdx context index
	 * @param triangles triangles
	 * @param trianglesOffset triangles offset
	 */
	virtual void drawTrianglesFromBufferObjects(int contextIdx, int32_t triangles, int32_t trianglesOffset) = 0;

	/**
	 * Draw points from buffer objects
	 * @param contextIdx context index
	 * @param points points
	 * @param pointsOffset points offset
	 */
	virtual void drawPointsFromBufferObjects(int contextIdx, int32_t points, int32_t pointsOffset) = 0;

	/**
	 * Set line width
	 * @param lineWidth line width
	 */
	virtual void setLineWidth(float lineWidth) = 0;

	/**
	 * Draw lines from buffer objects
	 * @param contextIdx context index
	 * @param points points
	 * @param pointsOffset points offset
	 */
	virtual void drawLinesFromBufferObjects(int contextIdx, int32_t points, int32_t pointsOffset) = 0;

	/**
	 * Unbind buffer objects
	 * @param contextIdx context index
	 */
	virtual void unbindBufferObjects(int contextIdx) = 0;

	/**
	 * Disposes a frame buffer object
	 * @param bufferObjectIds frame buffer id
	 */
	virtual void disposeBufferObjects(vector<int32_t>& bufferObjectIds) = 0;

	/**
	 * Get texture unit
	 * @param contextIdx context index
	 * @return active texture unit
	 */
	virtual int32_t getTextureUnit(int contextIdx) = 0;

	/**
	 * Sets up texture unit
	 * @param contextIdx context index
	 * @param textureUnit texture unit
	 */
	virtual void setTextureUnit(int contextIdx, int32_t textureUnit) = 0;

	/**
	 * Get light
	 * @param contextIdx context index
	 * @param lightId light id
	 * @return light
	 */
	inline Renderer_Light& getLight(int contextIdx, int32_t lightIdx) {
		auto& rendererContext = rendererContexts[contextIdx];
		return rendererContext.lights[lightIdx];
	}

	/**
	 * Update light
	 * @param contextIdx context index
	 * @param lightId light id
	 */
	virtual void onUpdateLight(int contextIdx, int32_t lightId) = 0;

	/**
	 * Get effect color mul
	 * @param context
	 * @return effect color mul
	 */
	inline array<float, 4>& getEffectColorMul(int contextIdx) {
		auto& rendererContext = rendererContexts[contextIdx];
		return rendererContext.effectColorMul;
	}

	/**
	 * Get effect color add
	 * @param context
	 * @return effect color add
	 */
	inline array<float, 4>& getEffectColorAdd(int contextIdx) {
		auto& rendererContext = rendererContexts[contextIdx];
		return rendererContext.effectColorAdd;
	}

	/**
	 * Update material
	 * @param contextIdx context index
	 */
	virtual void onUpdateEffect(int contextIdx) = 0;

	/**
	 * Get specular material
	 * @param contextIdx context index
	 * @return material
	 */
	inline Renderer_SpecularMaterial& getSpecularMaterial(int contextIdx) {
		auto& rendererContext = rendererContexts[contextIdx];
		return rendererContext.specularMaterial;
	}

	/**
	 * Get PBR material
	 * @param contextIdx context index
	 * @return material
	 */
	inline Renderer_PBRMaterial& getPBRMaterial(int contextIdx) {
		auto& rendererContext = rendererContexts[contextIdx];
		return rendererContext.pbrMaterial;
	}

	/**
	 * On update material
	 * @param contextIdx context index
	 */
	virtual void onUpdateMaterial(int contextIdx) = 0;

	/**
	 * Get shader
	 * @param contextIdx context index
	 */
	inline const string& getShader(int contextIdx) {
		auto& rendererContext = rendererContexts[contextIdx];
		return rendererContext.shader;
	}

	/**
	 * Set shader
	 * @param contextIdx context index
	 * @param id shader id
	 * @param parameters parameters
	 */
	inline void setShader(int contextIdx, const string& id) {
		auto& rendererContext = rendererContexts[contextIdx];
		rendererContext.shader = id;
	}

	/**
	 * On update shader
	 * @param contextIdx context index
	 */
	virtual void onUpdateShader(int contextIdx) = 0;

	/**
	 * Get shader parameters
	 * @param contextIdx context index
	 * @return shader parameters
	 */
	inline const EntityShaderParameters& getShaderParameters(int contextIdx) {
		auto& rendererContext = rendererContexts[contextIdx];
		return rendererContext.shaderParameters;
	}

	/**
	 * Set shader parameters
	 * @param contextIdx context index
	 * @param parameters shader parameters
	 */
	inline void setShaderParameters(int contextIdx, const EntityShaderParameters& parameters) {
		auto& rendererContext = rendererContexts[contextIdx];
		rendererContext.shaderParameters = parameters;
	}

	/**
	 * On update shader parameters
	 * @param contextIdx context index
	 */
	virtual void onUpdateShaderParameters(int contextIdx) = 0;

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
	 * @param contextIdx context index
	 * @param numGroupsX num groups x
	 * @param numGroupsY num groups y
	 * @param numGroupsZ num groups z
	 */
	virtual void dispatchCompute(int contextIdx, int32_t numGroupsX, int32_t numGroupsY, int32_t numGroupsZ) = 0;

	/**
	 * Memory barrier
	 */
	virtual void memoryBarrier() = 0;

	/**
	 * Upload skinning buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 * @param size size
	 * @param data data
	 */
	virtual void uploadSkinningBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, FloatBuffer* data) = 0;

	/**
	 * Upload skinning buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 * @param size size
	 * @param data data
	 */
	virtual void uploadSkinningBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, IntBuffer* data) = 0;

	/**
	 * Bind skinning vertices buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindSkinningVerticesBufferObject(int contextIdx, int32_t bufferObjectId) = 0;

	/**
	 * Bind skinning normal buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindSkinningNormalsBufferObject(int contextIdx, int32_t bufferObjectId) = 0;

	/**
	 * Bind skinning vertex joints buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindSkinningVertexJointsBufferObject(int contextIdx, int32_t bufferObjectId) = 0;

	/**
	 * Bind skinning vertex joint indices buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindSkinningVertexJointIdxsBufferObject(int contextIdx, int32_t bufferObjectId) = 0;

	/**
	 * Bind skinning vertex joint weights buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindSkinningVertexJointWeightsBufferObject(int contextIdx, int32_t bufferObjectId) = 0;

	/**
	 * Bind skinning vertices result buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindSkinningVerticesResultBufferObject(int contextIdx, int32_t bufferObjectId) = 0;

	/**
	 * Bind skinning normals result buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindSkinningNormalsResultBufferObject(int contextIdx, int32_t bufferObjectId) = 0;

	/**
	 * Bind skinning matrices result buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindSkinningMatricesBufferObject(int contextIdx, int32_t bufferObjectId) = 0;

	/**
	 * Get mask max value
	 * @return mask max value
	 */
	inline float getMaskMaxValue(int contextIdx) {
		auto& rendererContext = rendererContexts[contextIdx];
		return rendererContext.maskMaxValue;
	}

	/**
	 * Set mask max value
	 * @param contextIdx context index
	 * @param maskMinValue mask mask value
	 */
	inline void setMaskMaxValue(int contextIdx, float maskMaxValue) {
		auto& rendererContext = rendererContexts[contextIdx];
		rendererContext.maskMaxValue = maskMaxValue;
	}

	/**
	 * Get environment mapping cube map position
	 * @param contextIdx context index
	 * @return environment mapping position
	 */
	inline array<float, 3>& getEnvironmentMappingCubeMapPosition(int contextIdx) {
		auto& rendererContext = rendererContexts[contextIdx];
		return rendererContext.environmentMappingCubeMapPosition;
	}

	/**
	 * Set environment mapping cube map position
	 * @param contextIdx context index
	 * @param position position
	 */
	inline void setEnvironmentMappingCubeMapPosition(int contextIdx, const array<float, 3>& position) {
		auto& rendererContext = rendererContexts[contextIdx];
		rendererContext.environmentMappingCubeMapPosition = position;
	}

	/**
	 * Set up renderer for GUI rendering
	 */
	virtual void initGuiMode() = 0;

	/**
	 * Set up renderer for 3d rendering
	 */
	virtual void doneGuiMode() = 0;

	/**
	 * Enable/Disable v-sync
	 * @param vSync V-sync enabled
	 */
	virtual void setVSync(bool vSync) = 0;

	/**
	 * @return renderer statistics
	 */
	virtual const Renderer_Statistics getStatistics() = 0;

};
