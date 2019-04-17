#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <spirv/GlslangToSpv.h>

#include <array>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>

using std::array;
using std::map;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::utils::ByteBuffer;
using tdme::utils::FloatBuffer;
using tdme::utils::IntBuffer;
using tdme::utils::ShortBuffer;
using tdme::engine::fileio::textures::Texture;
using tdme::math::Matrix4x4;

/** 
 * Vulkan renderer
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::renderer::VKRenderer
	: public GLRenderer
{
private:
	static constexpr bool VERBOSE { false };
	static constexpr int DESC_MAX { 1024 };

	struct shader_type {
		struct uniform_type {
			enum uniform_type_enum { NONE, UNIFORM, SAMPLER2D };
			string name;
			uniform_type_enum type;
			int32_t position;
			uint32_t size;
			int32_t texture_unit;
		};
		map<string, uniform_type> uniforms;
		uint32_t ubo_size { 0 };
		uint32_t samplers { 0 };
		int32_t ubo { 0 };
		int32_t ubo_binding_idx { -1 };
		string source;
		vector<unsigned int> spirv;
		int32_t id { 0 };
		VkShaderStageFlagBits type;
		VkShaderModule module { VK_NULL_HANDLE };
	};

	struct program_type {
		int32_t desc_max { DESC_MAX };
		vector<int32_t> shader_ids;
		map<int32_t, string> uniforms;
		vector<int32_t> uniformBuffers;
		int32_t layout_bindings { 0 };
		bool created_pipeline { false };
		VkPipelineLayout pipeline_layout { VK_NULL_HANDLE };
		VkDescriptorSet desc_set[DESC_MAX] { VK_NULL_HANDLE };
		VkDescriptorSetLayout desc_layout { VK_NULL_HANDLE };
		VkPipelineCache pipelineCache { VK_NULL_HANDLE };
		VkPipeline pipeline { VK_NULL_HANDLE };
		int32_t id { 0 };
	};

	struct buffer_object {
		VkBuffer buf { VK_NULL_HANDLE };
		VkDeviceMemory mem { VK_NULL_HANDLE };
		int32_t id { 0 };
		uint32_t alloc_size { 0 };
		uint32_t size { 0 };
	};

	struct texture_object {
		bool uploaded { false };
		int32_t id { 0 };
		VkFormat format { VK_FORMAT_UNDEFINED };
		VkSampler sampler { VK_NULL_HANDLE };
		VkImage image { VK_NULL_HANDLE };
		VkImageLayout image_layout { VK_IMAGE_LAYOUT_UNDEFINED };
		VkDeviceMemory mem { VK_NULL_HANDLE };
		VkImageView view { VK_NULL_HANDLE };
	};

	struct swapchain_buffer_type {
		VkImage image { VK_NULL_HANDLE };
		VkCommandBuffer cmd { VK_NULL_HANDLE };
		VkImageView view { VK_NULL_HANDLE };
	};

	struct context_type {
		VkSurfaceKHR surface { VK_NULL_HANDLE };

		VkInstance inst { VK_NULL_HANDLE };
		VkPhysicalDevice gpu { VK_NULL_HANDLE };
		VkDevice device { VK_NULL_HANDLE };
		VkQueue queue { VK_NULL_HANDLE };
		VkPhysicalDeviceProperties gpu_props;
		VkPhysicalDeviceFeatures gpu_features;
		VkQueueFamilyProperties *queue_props { nullptr };
		uint32_t graphics_queue_node_index { 0 };

		int width { -1 };
		int height { -1 };
		VkFormat format { VK_FORMAT_UNDEFINED };
		VkColorSpaceKHR color_space;

		PFN_vkGetPhysicalDeviceSurfaceSupportKHR fpGetPhysicalDeviceSurfaceSupportKHR { nullptr };
		PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR fpGetPhysicalDeviceSurfaceCapabilitiesKHR { nullptr };
		PFN_vkGetPhysicalDeviceSurfaceFormatsKHR fpGetPhysicalDeviceSurfaceFormatsKHR { nullptr };
		PFN_vkGetPhysicalDeviceSurfacePresentModesKHR fpGetPhysicalDeviceSurfacePresentModesKHR { nullptr };
		PFN_vkCreateSwapchainKHR fpCreateSwapchainKHR { nullptr };
		PFN_vkDestroySwapchainKHR fpDestroySwapchainKHR { nullptr };
		PFN_vkGetSwapchainImagesKHR fpGetSwapchainImagesKHR { nullptr };
		PFN_vkAcquireNextImageKHR fpAcquireNextImageKHR { nullptr };
		PFN_vkQueuePresentKHR fpQueuePresentKHR { nullptr };

		uint32_t swapchain_image_count { 0 };
		VkSwapchainKHR swapchain { VK_NULL_HANDLE };
		swapchain_buffer_type* swapchain_buffers { nullptr };

		VkCommandPool cmd_pool { VK_NULL_HANDLE };

		int32_t shader_idx { 1 };
		int32_t program_idx { 1 };
		int32_t buffer_idx { 1 };
		int32_t texture_idx { 1 };
		struct map<int32_t, program_type> programs;
		struct map<int32_t, shader_type> shaders;
		struct map<int32_t, buffer_object> buffers;
		struct map<int32_t, texture_object> textures;

		int empty_vertex_buffer { 0 };
		int depth_buffer_default { 0 };
		int white_texture_default { 0 };

		VkCommandBuffer setup_cmd { VK_NULL_HANDLE }; // Command Buffer for initialization commands
		VkCommandBuffer draw_cmd { VK_NULL_HANDLE };  // Command Buffer for drawing commands
		VkRenderPass render_pass { VK_NULL_HANDLE };

		VkDescriptorPool desc_pool { VK_NULL_HANDLE };

		VkFramebuffer* framebuffers;

		VkPhysicalDeviceMemoryProperties memory_properties;

		bool validate { true };

		uint32_t current_buffer { 0 };
		uint32_t queue_count { 0 };

		VkSemaphore image_acquired_semaphore, draw_complete_semaphore;

		float clear_red { 0.0f };
		float clear_green { 0.0f };
		float clear_blue { 0.0f };
		float clear_alpha { 1.0f };

		int32_t program_id { 0 };
		int32_t bound_indices_buffer { 0 };
		array<int32_t, 9> bound_buffers { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		array<vector<uint8_t>, 4> uniform_buffers;
		array<int32_t, 16> bound_textures { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

		vector<VkDeviceMemory> memory_delete;
		vector<VkBuffer> buffers_delete;
		vector<VkImage> images_delete;

		struct render_command {
			struct texture {
				VkSampler sampler;
				VkImageView view;
				VkImageLayout image_layout;
			};
			VkBuffer indices_buffer { VK_NULL_HANDLE };
			array<VkBuffer, 9> vertex_buffers = {
				VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE,
				VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE,
				VK_NULL_HANDLE
			};
			array<VkBuffer, 4> ubo_buffers = {
				VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE
			};

			unordered_map<uint8_t, texture> textures;
			int32_t count { 0 };
			int32_t offset { 0 };
			int32_t instances { 0 };
		};

		vector<render_command> render_commands;

		VkViewport viewport;
		VkRect2D scissor;
	} context;

	bool memoryTypeFromProperties(uint32_t typeBits, VkFlags requirements_mask, uint32_t *typeIndex);
	VkBool32 checkLayers(uint32_t check_count, const char **check_names, uint32_t layer_count, VkLayerProperties *layers);
	void setImageLayout(bool setup, VkImage image, VkImageAspectFlags aspectMask, VkImageLayout old_image_layout, VkImageLayout new_image_layout, VkAccessFlagBits srcAccessMask);
	void prepareTextureImage(struct texture_object *tex_obj, VkImageTiling tiling, VkImageUsageFlags usage, VkFlags required_props, Texture* texture);
	VkBuffer getBufferObjectInternal(int32_t bufferObjectId);
	void uploadBufferObjectInternal(int32_t bufferObjectId, int32_t size, const uint8_t* data, VkBufferUsageFlagBits usage);
	void setProgramUniformInternal(int32_t uniformId, uint8_t* data, int32_t size);
	void shaderInitResources(TBuiltInResource &resources);
	EShLanguage shaderFindLanguage(const VkShaderStageFlagBits shaderType);
	void initializeSwapChain();
	void initializeFrameBuffers();
	void flushCommands();
	void initializeRenderPass();
	void preparePipeline(program_type& program);
	void createPipeline(program_type& program);
	void finishPipeline();
	void prepareSetupCommandBuffer();
	void finishSetupCommandBuffer();
	void reshape();
	int determineAlignment(const unordered_map<string, vector<string>>& structs, const vector<string>& uniforms);
	int align(int alignment, int offset);
	bool addToShaderUniformBufferObject(
		shader_type& shader,
		const unordered_map<string, string>& definitionValues,
		const unordered_map<string, vector<string>>& structs,
		const vector<string>& uniforms,
		const string& prefix,
		unordered_set<string>& uniformArrays,
		string& uniformsBlock
	);

public:
	const string getGLVersion() override;
	void initialize() override;
	void initializeFrame() override;
	void finishFrame() override;
	bool isBufferObjectsAvailable() override;
	bool isDepthTextureAvailable() override;
	bool isUsingProgramAttributeLocation() override;
	bool isSpecularMappingAvailable() override;
	bool isNormalMappingAvailable() override;
	bool isDisplacementMappingAvailable() override;
	bool isInstancedRenderingAvailable() override;
	bool isUsingShortIndices() override;
	bool isGeometryShaderAvailable() override;
	int32_t getTextureUnits() override;
	int32_t loadShader(int32_t type, const string& pathName, const string& fileName, const string& definitions = string(), const string& functions = string()) override;
	void useProgram(int32_t programId) override;
	int32_t createProgram() override;
	void attachShaderToProgram(int32_t programId, int32_t shaderId) override;
	bool linkProgram(int32_t programId) override;
	int32_t getProgramUniformLocation(int32_t programId, const string& name) override;
	void setProgramUniformInteger(int32_t uniformId, int32_t value) override;
	void setProgramUniformFloat(int32_t uniformId, float value) override;
	void setProgramUniformFloatMatrix3x3(int32_t uniformId, const array<float, 9>& data) override;
	void setProgramUniformFloatMatrix4x4(int32_t uniformId, const array<float, 16>& data) override;
	void setProgramUniformFloatMatrices4x4(int32_t uniformId, int32_t count, FloatBuffer* data) override;
	void setProgramUniformFloatVec4(int32_t uniformId, const array<float, 4>& data) override;
	void setProgramUniformFloatVec3(int32_t uniformId, const array<float, 3>& data) override;
	void setProgramAttributeLocation(int32_t programId, int32_t location, const string& name) override;
	void setViewPort(int32_t x, int32_t y, int32_t width, int32_t height) override;
	void updateViewPort() override;
	void setClearColor(float red, float green, float blue, float alpha) override;
	void enableCulling() override;
	void disableCulling() override;
	void enableBlending() override;
	void disableBlending() override;
	void enableDepthBufferWriting() override;
	void disableDepthBufferWriting() override;
	void disableDepthBufferTest() override;
	void enableDepthBufferTest() override;
	void setDepthFunction(int32_t depthFunction) override;
	void setColorMask(bool red, bool green, bool blue, bool alpha) override;
	void clear(int32_t mask) override;
	void setCullFace(int32_t cullFace) override;
	void setFrontFace(int32_t frontFace) override;
	int32_t createTexture() override;
	int32_t createDepthBufferTexture(int32_t width, int32_t height) override;
	int32_t createColorBufferTexture(int32_t width, int32_t height) override;
	void uploadTexture(Texture* texture) override;
	void resizeDepthBufferTexture(int32_t textureId, int32_t width, int32_t height) override;
	void resizeColorBufferTexture(int32_t textureId, int32_t width, int32_t height) override;
	void bindTexture(int32_t textureId) override;
	void disposeTexture(int32_t textureId) override;
	int32_t createFramebufferObject(int32_t depthBufferTextureGlId, int32_t colorBufferTextureGlId) override;
	void bindFrameBuffer(int32_t frameBufferId) override;
	void disposeFrameBufferObject(int32_t frameBufferId) override;
	vector<int32_t> createBufferObjects(int32_t buffers) override;
	void uploadBufferObject(int32_t bufferObjectId, int32_t size, FloatBuffer* data) override;
	void uploadIndicesBufferObject(int32_t bufferObjectId, int32_t size, ShortBuffer* data) override;
	void uploadIndicesBufferObject(int32_t bufferObjectId, int32_t size, IntBuffer* data) override;
	void bindIndicesBufferObject(int32_t bufferObjectId) override;
	void bindTextureCoordinatesBufferObject(int32_t bufferObjectId) override;
	void bindVerticesBufferObject(int32_t bufferObjectId) override;
	void bindNormalsBufferObject(int32_t bufferObjectId) override;
	void bindColorsBufferObject(int32_t bufferObjectId) override;
	void bindTangentsBufferObject(int32_t bufferObjectId) override;
	void bindBitangentsBufferObject(int32_t bufferObjectId) override;
	void bindModelMatricesBufferObject(int32_t bufferObjectId) override;
	void bindEffectColorMulsBufferObject(int32_t bufferObjectId) override;
	void bindEffectColorAddsBufferObject(int32_t bufferObjectId) override;
	void drawInstancedIndexedTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset, int32_t instances) override;
	void drawIndexedTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset) override;
	void drawInstancedTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset, int32_t instances) override;
	void drawTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset) override;
	void drawPointsFromBufferObjects(int32_t points, int32_t pointsOffset) override;
	void unbindBufferObjects() override;
	void disposeBufferObjects(vector<int32_t>& bufferObjectIds) override;
	int32_t getTextureUnit() override;

	/** 
	 * Set up current texture unit
	 * @param textureUnit texture unit
	 */
	void setTextureUnit(int32_t textureUnit) override;
	float readPixelDepth(int32_t x, int32_t y) override;
	ByteBuffer* readPixels(int32_t x, int32_t y, int32_t width, int32_t height) override;
	void initGuiMode() override;
	void doneGuiMode() override;

	// overriden methods for skinning on GPU via compute shader
	void dispatchCompute(int32_t numGroupsX, int32_t numGroupsY, int32_t numGroupsZ) override;
	void memoryBarrier() override;
	void uploadSkinningBufferObject(int32_t bufferObjectId, int32_t size, FloatBuffer* data) override;
	void uploadSkinningBufferObject(int32_t bufferObjectId, int32_t size, IntBuffer* data) override;
	void bindSkinningVerticesBufferObject(int32_t bufferObjectId) override;
	void bindSkinningNormalsBufferObject(int32_t bufferObjectId) override;
	void bindSkinningVertexJointsBufferObject(int32_t bufferObjectId) override;
	void bindSkinningVertexJointIdxsBufferObject(int32_t bufferObjectId) override;
	void bindSkinningVertexJointWeightsBufferObject(int32_t bufferObjectId) override;
	void bindSkinningVerticesResultBufferObject(int32_t bufferObjectId) override;
	void bindSkinningNormalsResultBufferObject(int32_t bufferObjectId) override;
	void bindSkinningMatricesBufferObject(int32_t bufferObjectId) override;

private:

	/** 
	 * Checks if GL error did occour 
	 */
	void checkGLError(int line);

	// Generated

public:
	/**
	 * Public constructor
	 */
	VKRenderer();
};
