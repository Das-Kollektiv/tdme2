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

#include <agui/agui.h>
#include <agui/gui/textures/fwd-agui.h>
#include <agui/gui/renderer/GUIShaderParameters.h>
#include <agui/math/fwd-agui.h>
#include <agui/math/Matrix3x3.h>
#include <agui/math/Matrix4x4.h>
#include <agui/utilities/fwd-agui.h>

using std::array;
using std::map;
using std::string;
using std::vector;

// namespaces
namespace agui {
namespace gui {
namespace renderer {
	using ::agui::gui::textures::GUITexture;
	using ::agui::math::Matrix3x3;
	using ::agui::math::Matrix4x4;
	using ::agui::utilities::ByteBuffer;
	using ::agui::utilities::FloatBuffer;
	using ::agui::utilities::IntBuffer;
	using ::agui::utilities::ShortBuffer;
}
}
}

/**
 * Renderer interface
 * @author Andreas Drewke
 * @ersion $Id$
 */
class agui::gui::renderer::GUIRendererBackend
{
public:

	enum RendererType { RENDERERTYPE_NONE, RENDERERTYPE_OPENGLES, RENDERERTYPE_OPENGL, RENDERERTYPE_VULKAN };

	struct Renderer_Context {
		array<float, 4> effectColorMul {{ 1.0f, 1.0f, 1.0f, 1.0f }};
		array<float, 4> effectColorAdd {{ 0.0f, 0.0f, 0.0f, 0.0f }};
		Matrix3x3 textureMatrix {};
		float maskMaxValue { 1.0f };
		string shader;
		GUIShaderParameters shaderParameters;
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
		uint32_t triangles { 0 };
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
	int32_t TEXTUREUNITS_MAX;
	int32_t PROGRAM_GUI;
	int32_t SHADER_FRAGMENT_SHADER;
	int32_t SHADER_VERTEX_SHADER;
	int32_t SHADER_COMPUTE_SHADER;
	int32_t FRAMEBUFFER_DEFAULT;

protected:
	int32_t viewPortWidth;
	int32_t viewPortHeight;
	Renderer_Statistics statistics;
	Matrix4x4 viewportMatrix;
	string shaderPrefix;

	vector<Renderer_Context> rendererContexts;

public:
	// forbid class copy
	FORBID_CLASS_COPY(GUIRendererBackend)

	/**
	 * Public constructor
	 */
	GUIRendererBackend();

	/**
	 * Destructor
	 */
	virtual ~GUIRendererBackend();

	/**
	 * @returns renderer type
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
	 * @returns vendor
	 */
	virtual const string getVendor() = 0;

	/**
	 * @returns renderer
	 */
	virtual const string getRenderer() = 0;

	/**
	 * @returns shader version e.g. gl2, gl3 or gles2
	 */
	virtual const string getShaderVersion() = 0;

	/**
	 * @returns returns if texture compression is available
	 */
	virtual bool isTextureCompressionAvailable() = 0;

	/**
	 * @returns requires program attribute location
	 */
	virtual bool isUsingProgramAttributeLocation() = 0;

	/**
	 * @returns is supporting integer program attributes
	 */
	virtual bool isSupportingIntegerProgramAttributes() = 0;

	/**
	 * @returns Returns if renderer is using short indices, otherwise it uses int indices
	 */
	virtual bool isUsingShortIndices() = 0;

	/**
	 * @returns number of texture units
	 */
	virtual int32_t getTextureUnits() = 0;

	/**
	 * @returns viewport width
	 */
	inline int32_t getViewPortWidth() {
		return viewPortWidth;
	}

	/**
	 * @returns viewport height
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
	 * @returns shader handle
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
	 * @returns int
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
	 * @returns success
	 */
	virtual bool linkProgram(int32_t programId) = 0;

	/**
	 * Returns location of given uniform variable
	 * @param programId program id
	 * @param name uniform name
	 * @returns
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
	 * Bind attribute to a input location
	 * @param programId program id
	 * @param location location
	 * @param name attribute name
	 */
	virtual void setProgramAttributeLocation(int32_t programId, int32_t location, const string& name) = 0;

	/**
	 * Get shader prefix
	 * @returns shader prefix
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
	 * @returns view port matrix
	 */
	inline Matrix4x4& getViewportMatrix() {
		return viewportMatrix;
	}

	/**
	 * Get texture matrix
	 * @param contextIdx context index
	 * @returns texture matrix
	 */
	inline Matrix3x3& getTextureMatrix(int contextIdx) {
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
	 * Clear render buffer with given mask
	 * @param mask mask
	 */
	virtual void clear(int32_t mask) = 0;

	/**
	 * Creates a texture
	 * @returns texture id
	 */
	virtual int32_t createTexture() = 0;

	/**
	 * Creates a color buffer texture
	 * @param width width
	 * @param height height
	 * @oaram cubeMapTextureId cube map texture id
	 * @param cubeMapTextureIndex cube map texture index
	 * @returns color buffer texture id
	 */
	virtual int32_t createColorBufferTexture(int32_t width, int32_t height, int32_t cubeMapTextureId, int32_t cubeMapTextureIndex) = 0;

	/**
	 * Uploads texture data to current bound texture
	 * @param contextIdx context index
	 * @param texture texture
	 */
	virtual void uploadTexture(int contextIdx, GUITexture* texture) = 0;

	/**
	 * Resize color buffer texture
	 * @param textureId texture id
	 * @param width width
	 * @param height height
	 */
	virtual void resizeColorBufferTexture(int32_t textureId, int32_t width, int32_t height) = 0;

	/**
	 * Binds a texture with given id or unbinds when using ID_NONE
	 * @param contextIdx context index
	 * @param textureId textureId
	 */
	virtual void bindTexture(int contextIdx, int32_t textureId) = 0;

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
	 * Generate buffer objects for vertex data and such
	 * @param buffers buffers
	 * @param useGPUMemory use GPU memory
	 * @param shared shared between different threads
	 * @returns ids
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
	 * Bind vertices 2 buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindVertices2BufferObject(int contextIdx, int32_t bufferObjectId) = 0;

	/**
	 * Bind colors buffer object
	 * @param contextIdx context index
	 * @param bufferObjectId buffer object id
	 */
	virtual void bindColorsBufferObject(int contextIdx, int32_t bufferObjectId) = 0;

	/**
	 * Draw indexed triangles from buffer objects
	 * @param contextIdx context index
	 * @param triangles triangles
	 * @param trianglesOffset triangles offset
	 */
	virtual void drawIndexedTrianglesFromBufferObjects(int contextIdx, int32_t triangles, int32_t trianglesOffset) = 0;

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
	 * @returns active texture unit
	 */
	virtual int32_t getTextureUnit(int contextIdx) = 0;

	/**
	 * Sets up texture unit
	 * @param contextIdx context index
	 * @param textureUnit texture unit
	 */
	virtual void setTextureUnit(int contextIdx, int32_t textureUnit) = 0;

	/**
	 * Get effect color mul
	 * @param context
	 * @returns effect color mul
	 */
	inline array<float, 4>& getEffectColorMul(int contextIdx) {
		auto& rendererContext = rendererContexts[contextIdx];
		return rendererContext.effectColorMul;
	}

	/**
	 * Get effect color add
	 * @param context
	 * @returns effect color add
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
	 * Get shader parameters
	 * @param contextIdx context index
	 * @returns shader parameters
	 */
	inline const GUIShaderParameters& getShaderParameters(int contextIdx) {
		auto& rendererContext = rendererContexts[contextIdx];
		return rendererContext.shaderParameters;
	}

	/**
	 * Set shader parameters
	 * @param contextIdx context index
	 * @param parameters shader parameters
	 */
	inline void setShaderParameters(int contextIdx, const GUIShaderParameters& parameters) {
		auto& rendererContext = rendererContexts[contextIdx];
		rendererContext.shaderParameters = parameters;
	}

	/**
	 * Read pixels
	 * @param x x
	 * @param y y
	 * @param width width
	 * @param height height
	 * @returns byte buffer
	 */
	virtual ByteBuffer* readPixels(int32_t x, int32_t y, int32_t width, int32_t height) = 0;

	/**
	 * Get mask max value
	 * @returns mask max value
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
	 * Set up renderer for GUI rendering
	 */
	virtual void initGUIMode() = 0;

	/**
	 * Set up renderer for 3d rendering
	 */
	virtual void doneGUIMode() = 0;

	/**
	 * Enable/Disable v-sync
	 * @param vSync V-sync enabled
	 */
	virtual void setVSync(bool vSync) = 0;

	/**
	 * @returns renderer statistics
	 */
	virtual const Renderer_Statistics getStatistics() = 0;

};
