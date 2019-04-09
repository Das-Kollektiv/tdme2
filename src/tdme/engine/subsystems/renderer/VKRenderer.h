#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <spirv/GlslangToSpv.h>

#include <array>
#include <map>
#include <vector>
#include <string>

#include <tdme/tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>

using std::array;
using std::map;
using std::vector;
using std::string;

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
	static constexpr int DESC_MAX { 4096 };

	struct shader_type {
		struct uniform_type {
			string name;
			uint32_t position;
			uint32_t size;
		};
		map<string, uniform_type> uniforms;
		uint32_t ubo_size;
		int32_t uniform_buffer;
		vector<unsigned int> spirv;
		int32_t id;
		VkShaderStageFlagBits type;
		VkShaderModule module;
	};

	struct program_type {
		int32_t desc_max { DESC_MAX };
		vector<int32_t> shader_ids;
		map<int32_t, string> uniforms;
		vector<int32_t> uniformBuffers;
		bool created_pipeline;
		VkPipelineLayout pipeline_layout { VK_NULL_HANDLE };
		VkDescriptorSet desc_set[DESC_MAX] { VK_NULL_HANDLE };
		VkDescriptorSetLayout desc_layout { VK_NULL_HANDLE };
		VkPipelineCache pipelineCache { VK_NULL_HANDLE };
		VkPipeline pipeline { VK_NULL_HANDLE };
		int32_t id;
	};

	struct buffer_object {
		VkBuffer buf;
		VkDeviceMemory mem;
		int32_t id;
		uint32_t alloc_size;
		uint32_t size;
	};

	struct texture_object {
		bool uploaded;
		int32_t id;
		VkSampler sampler;
		VkImage image;
		VkImageLayout image_layout;
		VkDeviceMemory mem;
		VkImageView view;
		int32_t tex_width, tex_height;
	};

	struct depth_buffer {
		VkFormat format;
		VkImage image;
		VkDeviceMemory mem;
		VkImageView view;
		int32_t id;
	};

	struct color_buffer {
		VkImage image;
		VkImageView view;
	};

	struct swapchain_buffer_type {
		VkImage image;
		VkCommandBuffer cmd;
		VkImageView view;
	};

	struct context_type {
		GLFWwindow* window;
		VkSurfaceKHR surface;

		VkInstance inst;
		VkPhysicalDevice gpu;
		VkDevice device;
		VkQueue queue;
		VkPhysicalDeviceProperties gpu_props;
		VkPhysicalDeviceFeatures gpu_features;
		VkQueueFamilyProperties *queue_props;
		uint32_t graphics_queue_node_index;

		uint32_t enabled_extension_count;
		uint32_t enabled_layer_count;
		const char *extension_names[64];
		const char *enabled_layers[64];

		int width, height;
		VkFormat format;
		VkColorSpaceKHR color_space;

		PFN_vkGetPhysicalDeviceSurfaceSupportKHR fpGetPhysicalDeviceSurfaceSupportKHR;
		PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR fpGetPhysicalDeviceSurfaceCapabilitiesKHR;
		PFN_vkGetPhysicalDeviceSurfaceFormatsKHR fpGetPhysicalDeviceSurfaceFormatsKHR;
		PFN_vkGetPhysicalDeviceSurfacePresentModesKHR fpGetPhysicalDeviceSurfacePresentModesKHR;
		PFN_vkCreateSwapchainKHR fpCreateSwapchainKHR;
		PFN_vkDestroySwapchainKHR fpDestroySwapchainKHR;
		PFN_vkGetSwapchainImagesKHR fpGetSwapchainImagesKHR;
		PFN_vkAcquireNextImageKHR fpAcquireNextImageKHR;
		PFN_vkQueuePresentKHR fpQueuePresentKHR;

		uint32_t swapchain_image_count { 0 };
		VkSwapchainKHR swapchain { VK_NULL_HANDLE };
		swapchain_buffer_type* swapchain_buffers { nullptr };

		VkCommandPool cmd_pool { VK_NULL_HANDLE };

		int32_t shader_idx { 1 };
		int32_t program_idx { 1 };
		int32_t depth_buffer_idx { 1 };
		int32_t color_buffer_idx { 1 };
		int32_t buffer_idx { 1 };
		int32_t texture_idx { 1 };
		struct map<int32_t, program_type> programs;
		struct map<int32_t, shader_type> shaders;
		struct map<int32_t, depth_buffer> depth_buffers;
		struct map<int32_t, depth_buffer> color_buffers;
		struct map<int32_t, buffer_object> buffers;
		struct map<int32_t, texture_object> textures;

		int depth_buffer_default;
		int white_texture_default;

		VkCommandBuffer setup_cmd { VK_NULL_HANDLE }; // Command Buffer for initialization commands
		VkCommandBuffer draw_cmd { VK_NULL_HANDLE };  // Command Buffer for drawing commands
		VkRenderPass render_pass { VK_NULL_HANDLE };

		VkDescriptorPool desc_pool { VK_NULL_HANDLE };

		VkFramebuffer* framebuffers;

		VkPhysicalDeviceMemoryProperties memory_properties;

		bool validate { true };

		uint32_t current_buffer;
		uint32_t queue_count;

		VkSemaphore image_acquired_semaphore, draw_complete_semaphore;

		float clear_red { 0.0f };
		float clear_green { 0.0f };
		float clear_blue { 0.0f };
		float clear_alpha { 1.0f };

		int32_t program_id { 0 };
		int32_t bound_indices_buffer { 0 };
		array<int32_t, 12> bound_buffers { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		array<vector<uint8_t>, 4> uniform_buffers;
		int32_t bound_texture_id { 0 };

		vector<VkDeviceMemory> memory_delete;
		vector<VkBuffer> buffers_delete;
		vector<VkImage> images_delete;

		struct render_command {
			struct texture {
				VkSampler sampler { VK_NULL_HANDLE };
				VkImageView view { VK_NULL_HANDLE };
				VkImageLayout image_layout { VK_IMAGE_LAYOUT_UNDEFINED };
			};
			VkBuffer indices_buffer { VK_NULL_HANDLE };
			array<VkBuffer, 12> vertex_buffers = {
				VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE,
				VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE,
				VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE,
			};
			array<VkBuffer, 2> ubo_buffers = {
				VK_NULL_HANDLE, VK_NULL_HANDLE
			};

			array<texture, 1> textures;
			int32_t count { 0 };
			int32_t offset { 0 };
		};

		vector<render_command> render_commands;
	} context;

	bool memoryTypeFromProperties(uint32_t typeBits, VkFlags requirements_mask, uint32_t *typeIndex);
	VkBool32 checkLayers(uint32_t check_count, const char **check_names, uint32_t layer_count, VkLayerProperties *layers);
	void setImageLayout(bool setup, VkImage image, VkImageAspectFlags aspectMask, VkImageLayout old_image_layout, VkImageLayout new_image_layout, VkAccessFlagBits srcAccessMask);
	void prepareTextureImage(struct texture_object *tex_obj, VkImageTiling tiling, VkImageUsageFlags usage, VkFlags required_props, Texture* texture);
	int32_t getUniformBufferObjectBindingIdx(int32_t shaderType);
	VkBuffer getBufferObjectInternal(int32_t bufferObjectId);
	void uploadBufferObjectInternal(int32_t bufferObjectId, int32_t size, const uint8_t* data, VkBufferUsageFlagBits usage);
	void setProgramUniformInternal(int32_t uniformId, uint8_t* data, int32_t size);
	void shaderInitResources(TBuiltInResource &resources);
	EShLanguage shaderFindLanguage(const VkShaderStageFlagBits shaderType);
	void initializeSwapChain();
	void initializeFrameBuffers();
	void flushCommands();
	void preparePipeline(program_type& program);
	void createPipeline(program_type& program);
	void finishPipeline();
	void prepareSetupCommandBuffer();
	void finishSetupCommandBuffer();

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
