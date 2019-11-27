#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <ext/vulkan/spirv/GlslangToSpv.h>
#include <ext/vulkan/vma/src/VmaUsage.h>

#include <array>
#include <list>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/os/threading/ReadWriteLock.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/utils/fwd-tdme.h>

using std::array;
using std::list;
using std::map;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using tdme::engine::Engine;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::math::Matrix4x4;
using tdme::math::Matrix2D3x3;
using tdme::utils::ByteBuffer;
using tdme::utils::FloatBuffer;
using tdme::utils::IntBuffer;
using tdme::utils::ShortBuffer;
using tdme::os::threading::Mutex;
using tdme::os::threading::ReadWriteLock;

/** 
 * Vulkan renderer
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::renderer::VKRenderer
	: public Renderer
{
private:
	static constexpr bool VERBOSE { false };
	static constexpr int DRAW_COMMANDBUFFER_MAX { 4 };
	static constexpr int COMMANDS_MAX { 8 };
	static constexpr int DESC_MAX { 4096 };

	struct delete_buffer_type {
		VkBuffer buffer;
		VmaAllocation allocation;
	};

	struct delete_image_type {
		VkImage image;
		VmaAllocation allocation;
	};

	struct buffer_object {
		struct reusable_buffer {
			int64_t frame_used_last { -1 };
			VkBuffer buf { VK_NULL_HANDLE };
			VmaAllocation allocation { VK_NULL_HANDLE };
			uint32_t size { 0 };
			void* data { nullptr };
		};
		int32_t id { 0 };
		bool useGPUMemory { false };
		bool shared { false };
		unordered_map<uint32_t, list<reusable_buffer>> buffers;
		uint32_t buffer_count { 0 };
		int64_t frame_cleaned_last { 0 };
		reusable_buffer* current_buffer { nullptr };
	};

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
		int32_t binding_max { -1 };
		vector<int32_t> ubo_ids;
		vector<buffer_object*> ubo;
		int32_t ubo_binding_idx { -1 };
 		string source;
 		string file;
		vector<unsigned int> spirv;
		int32_t id { 0 };
		VkShaderStageFlagBits type;
		VkShaderModule module { VK_NULL_HANDLE };
	};

	struct program_type {
		struct pipeline_struct {
			VkPipelineCache pipelineCache { VK_NULL_HANDLE };
			VkPipeline pipeline { VK_NULL_HANDLE };
		};
		int type { 0 };
		unordered_map<string, pipeline_struct> pipelines;
		vector<int32_t> shader_ids;
		vector<shader_type*> shaders;
		map<int32_t, string> uniforms;
		vector<int32_t> uniform_buffers;
		vector<bool> uniform_buffers_stored;
		vector<array<vector<uint8_t>, 4>> uniform_buffers_last;
		vector<array<bool, 4>> uniform_buffers_changed_last;
		uint32_t layout_bindings { 0 };
		VkPipelineLayout pipeline_layout { VK_NULL_HANDLE };
		vector<array<VkDescriptorSet, DESC_MAX>> desc_sets;
		VkDescriptorSetLayout desc_layout { VK_NULL_HANDLE };
		vector<uint32_t> desc_idxs;
		int32_t id { 0 };
	};

	struct texture_object {
		enum type { TYPE_NONE, TYPE_TEXTURE, TYPE_FRAMEBUFFER_COLORBUFFER, TYPE_FRAMEBUFFER_DEPTHBUFFER };
		bool uploaded { false };
		type type { TYPE_NONE };
		int32_t id { 0 };
		int32_t frame_buffer_object_id { 0 };
		uint32_t width { 0 };
		uint32_t height { 0 };
		VkFormat format { VK_FORMAT_UNDEFINED };
		VkSampler sampler { VK_NULL_HANDLE };
		VkImage image { VK_NULL_HANDLE };
		VkImageLayout image_layout { VK_IMAGE_LAYOUT_UNDEFINED };
		VmaAllocation allocation { VK_NULL_HANDLE };
		VkImageView view { VK_NULL_HANDLE };
	};

	struct framebuffer_object {
		int32_t id { 0 };
		int32_t depth_texture_id { 0 };
		int32_t color_texture_id { 0 };
		VkFramebuffer frame_buffer { VK_NULL_HANDLE };
		VkRenderPass render_pass { VK_NULL_HANDLE };
	};

	struct swapchain_buffer_type {
		VkImage image { VK_NULL_HANDLE };
		VkImageView view { VK_NULL_HANDLE };
	};

	struct context_type {
		int32_t idx { 0 };

		VkCommandPool cmd_setup_pool;
		VkCommandBuffer setup_cmd_inuse;
		VkCommandBuffer setup_cmd;
		VkFence setup_fence;

		bool render_pass_started;

		VkCommandPool cmd_draw_pool;
		array<VkCommandBuffer, DRAW_COMMANDBUFFER_MAX> draw_cmds;
		uint32_t draw_cmd_current;
		array<bool, DRAW_COMMANDBUFFER_MAX> draw_cmd_started;
		array<VkFence, DRAW_COMMANDBUFFER_MAX> draw_fences;

		program_type* program { nullptr };

		string pipeline_id;
		VkPipeline pipeline { VK_NULL_HANDLE };

		int32_t bound_indices_buffer { 0 };
		array<int32_t, 10> bound_buffers { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		array<vector<uint8_t>, 4> uniform_buffers;
		array<bool, 4> uniform_buffers_changed;
		int32_t texture_unit_active { 0 };
		array<int32_t, 16> bound_textures { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

		struct objects_render_command {
			struct texture {
				VkSampler sampler;
				VkImageView view;
				VkImageLayout image_layout;
			};
			VkBuffer indices_buffer { VK_NULL_HANDLE };
			array<VkBuffer, 10> vertex_buffers = {
				VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE,
				VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE,
				VK_NULL_HANDLE, VK_NULL_HANDLE
			};
			array<VkBuffer, 4> ubo_buffers = {
				VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE
			};

			unordered_map<uint8_t, texture> textures;
			int32_t count { 0 };
			int32_t offset { 0 };
			int32_t instances { 0 };
		};

		struct points_render_command {
			struct texture {
				VkSampler sampler;
				VkImageView view;
				VkImageLayout image_layout;
			};
			array<VkBuffer, 4> vertex_buffers = {
				VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE
			};
			array<VkBuffer, 4> ubo_buffers = {
				VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE
			};

			unordered_map<uint8_t, texture> textures;
			int32_t count { 0 };
			int32_t offset { 0 };
		};

		struct lines_render_command {
			struct texture {
				VkSampler sampler;
				VkImageView view;
				VkImageLayout image_layout;
			};
			array<VkBuffer, 4> vertex_buffers = {
				VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE
			};
			array<VkBuffer, 4> ubo_buffers = {
				VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE
			};

			unordered_map<uint8_t, texture> textures;
			int32_t count { 0 };
			int32_t offset { 0 };
		};

		struct compute_command {
			array<VkBuffer, 8> storage_buffers = {
				VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE,
				VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE,
			};
			array<uint32_t, 8> storage_buffer_sizes = {
				0, 0, 0, 0,
				0, 0, 0, 0,
			};
			array<VkBuffer, 4> ubo_buffers = {
				VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE
			};

			int32_t num_groups_x { 0 };
			int32_t num_groups_y { 0 };
			int32_t num_groups_z { 0 };
		};

		enum command_type { COMMAND_NONE, COMMAND_OBJECTS, COMMAND_POINTS, COMMAND_LINES, COMMAND_COMPUTE };
		command_type command_type { COMMAND_NONE };
		objects_render_command objects_render_command;
		points_render_command points_render_command;
		lines_render_command lines_render_command;
		compute_command compute_command;
		uint32_t command_count { 0 };

		string shader;
		array<float, 4> effect_color_mul {{ 1.0f, 1.0f, 1.0f, 1.0f }};
		array<float, 4> effect_color_add {{ 0.0f, 0.0f, 0.0f, 0.0f }};
		Renderer_Material material;
		array<Renderer_Light, 8> lights;
		Matrix2D3x3 texture_matrix;

		bool culling_enabled { true };
		VkFrontFace front_face { VK_FRONT_FACE_COUNTER_CLOCKWISE};

		int32_t program_id { 0 };
	};

	VkSurfaceKHR surface { VK_NULL_HANDLE };

	VkInstance inst { VK_NULL_HANDLE };
	VkPhysicalDevice gpu { VK_NULL_HANDLE };
	VkDevice device { VK_NULL_HANDLE };
	Mutex queue_mutex;
	VkQueue queue { VK_NULL_HANDLE };
	VkPhysicalDeviceProperties gpu_props;
	VkPhysicalDeviceFeatures gpu_features;
	VkQueueFamilyProperties *queue_props { nullptr };
	VkPhysicalDeviceMemoryProperties memory_properties;
	uint32_t graphics_queue_node_index { 0 };

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
	VkFramebuffer* window_framebuffers { nullptr };

	VkFence memorybarrier_fence { VK_NULL_HANDLE };

	ReadWriteLock pipeline_rwlock;

	VkRenderPass render_pass { VK_NULL_HANDLE };

	int32_t shader_idx { 1 };
	int32_t program_idx { 1 };
	int32_t buffer_idx { 1 };
	int32_t texture_idx { 1 };
	int32_t framebuffer_idx { 1 };
	map<int32_t, program_type> programs;
	map<int32_t, shader_type> shaders;
	map<int32_t, buffer_object> buffers;
	map<int32_t, texture_object> textures;
	map<int32_t, framebuffer_object> framebuffers;

	ReadWriteLock buffers_rwlock;
	ReadWriteLock textures_rwlock;

	uint32_t width { 0 };
	uint32_t height { 0 };
	VkFormat format { VK_FORMAT_UNDEFINED };
	VkColorSpaceKHR color_space { VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };

	buffer_object* empty_vertex_buffer { nullptr };
	int empty_vertex_buffer_id { 0 };
	int depth_buffer_default { 0 };
	int white_texture_default_id { 0 };
	texture_object* white_texture_default { nullptr };

	VkDescriptorPool desc_pool { VK_NULL_HANDLE };

	// enable validation layers
	bool validate { false };

	uint32_t current_buffer { 0 };
	uint32_t queue_count { 0 };

	VkSemaphore image_acquired_semaphore { VK_NULL_HANDLE };
	VkSemaphore draw_complete_semaphore { VK_NULL_HANDLE };

	float clear_red { 0.0f };
	float clear_green { 0.0f };
	float clear_blue { 0.0f };
	float clear_alpha { 1.0f };

	VkViewport viewport;
	VkRect2D scissor;

	int32_t bound_frame_buffer { 0 };

	bool blending_enabled { true };
	VkCullModeFlagBits cull_mode { VK_CULL_MODE_BACK_BIT };
	bool depth_buffer_writing { true };
	bool depth_buffer_testing { true };
	int depth_function { VK_COMPARE_OP_LESS_OR_EQUAL };
	float line_width { 1.0f };
	int64_t frame { 0 };

	Mutex delete_mutex;
	vector<delete_buffer_type> delete_buffers;
	vector<delete_image_type> delete_images;

	vector<context_type> contexts;
	VmaAllocator allocator { VK_NULL_HANDLE };

	bool memoryTypeFromProperties(uint32_t typeBits, VkFlags requirements_mask, uint32_t *typeIndex);
	VkBool32 checkLayers(uint32_t check_count, const char **check_names, uint32_t layer_count, VkLayerProperties *layers);
	void setImageLayout(int contextIdx, VkImage image, VkImageAspectFlags aspectMask, VkImageLayout old_image_layout, VkImageLayout new_image_layout, VkAccessFlagBits srcAccessMask, uint32_t baseLevel = 0, uint32_t levelCount = 1);
	uint32_t getMipLevels(int32_t textureWidth, int32_t textureHeight);
	void prepareTextureImage(int contextIdx, struct texture_object *tex_obj, VkImageTiling tiling, VkImageUsageFlags usage, VkFlags required_props, Texture* texture, VkImageLayout image_layout, bool disableMipMaps = true);
	VkBuffer getBufferObjectInternal(int32_t bufferObjectId, uint32_t& size);
	VkBuffer getBufferObjectInternalNoLock(int32_t bufferObjectId, uint32_t& size);
	VkBuffer getBufferObjectInternalNoLock(buffer_object* bufferObject, uint32_t& size);
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VmaAllocation& allocation, VmaAllocationInfo& allocationInfo);
	buffer_object* getBufferObjectInternal(int32_t bufferObjectId);
	void uploadBufferObjectInternal(int contextIdx,  buffer_object* buffer, int32_t size, const uint8_t* data, VkBufferUsageFlagBits usage);
	void uploadBufferObjectInternal(int contextIdx, int32_t bufferObjectId, int32_t size, const uint8_t* data, VkBufferUsageFlagBits usage);
	void setProgramUniformInternal(void* context, int32_t uniformId, uint8_t* data, int32_t size);
	void shaderInitResources(TBuiltInResource &resources);
	EShLanguage shaderFindLanguage(const VkShaderStageFlagBits shaderType);
	void initializeSwapChain();
	void initializeFrameBuffers();
	void endDrawCommands(int contextIdx);
	void endDrawCommandsAllContexts();
	void executeCommand(int contextIdx);
	void initializeRenderPass();
	void startRenderPass(int contextIdx, int line);
	void endRenderPass(int contextIdx, int line);
	void preparePipeline(int contextIdx, program_type* program);
	void createObjectsRenderingProgram(program_type* program);
	void createObjectsRenderingPipeline(int contextIdx, program_type* program);
	void setupObjectsRenderingPipeline(int contextIdx, program_type* program);
	void createPointsRenderingProgram(program_type* program);
	void createPointsRenderingPipeline(int contextIdx, program_type* program);
	void setupPointsRenderingPipeline(int contextIdx, program_type* program);
	void createLinesRenderingProgram(program_type* program);
	void createLinesRenderingPipeline(int contextIdx, program_type* program);
	void setupLinesRenderingPipeline(int contextIdx, program_type* program);
	void createSkinningComputingProgram(program_type* program);
	void createSkinningComputingPipeline(int contextIdx, program_type* program);
	void setupSkinningComputingPipeline(int contextIdx, program_type* program);
	void finishPipeline(int contextIdx);
	void prepareSetupCommandBuffer(int contextIdx);
	void finishSetupCommandBuffer(int contextIdx);
	void finishSetupCommandBuffers();
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
	void createRasterizationStateCreateInfo(int contextIdx, VkPipelineRasterizationStateCreateInfo& rs);
	void createColorBlendAttachmentState(VkPipelineColorBlendAttachmentState& att_state);
	void createDepthStencilStateCreateInfo(VkPipelineDepthStencilStateCreateInfo& ds);
	const string createPipelineId(int contextIdx);
	void createDepthBufferTexture(int32_t textureId, int32_t width, int32_t height);
	void createColorBufferTexture(int32_t textureId, int32_t width, int32_t height);
	void drawInstancedTrianglesFromBufferObjects(void* context, int32_t triangles, int32_t trianglesOffset, uint32_t indicesBuffer, int32_t instances);
	void createFramebufferObject(int32_t frameBufferId);
	bool beginDrawCommandBuffer(int contextIdx, int bufferId = -1);
	bool endDrawCommandBuffer(int contextIdx, int bufferId = -1, bool cycleBuffers = true, bool waitUntilSubmitted = false);
	void submitContext(int contextIdx);

public:
	const string getShaderVersion() override;
	void* getDefaultContext() override;
	void* getContext(int contextIdx) override;
	int getContextIndex(void* context) override;
	void initialize() override;
	void initializeFrame() override;
	void finishFrame() override;
	bool isSupportingMultithreadedRendering() override;
	bool isSupportingMultipleRenderQueues() override;
	bool isSupportingVertexArrays() override;
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
	void useProgram(void* context, int32_t programId) override;
	int32_t createProgram(int type) override;
	void attachShaderToProgram(int32_t programId, int32_t shaderId) override;
	bool linkProgram(int32_t programId) override;
	int32_t getProgramUniformLocation(int32_t programId, const string& name) override;
	void setProgramUniformInteger(void* context, int32_t uniformId, int32_t value) override;
	void setProgramUniformFloat(void* context, int32_t uniformId, float value) override;
	void setProgramUniformFloatMatrix3x3(void* context, int32_t uniformId, const array<float, 9>& data) override;
	void setProgramUniformFloatMatrix4x4(void* context, int32_t uniformId, const array<float, 16>& data) override;
	void setProgramUniformFloatMatrices4x4(void* context, int32_t uniformId, int32_t count, FloatBuffer* data) override;
	void setProgramUniformFloatVec4(void* context, int32_t uniformId, const array<float, 4>& data) override;
	void setProgramUniformFloatVec3(void* context, int32_t uniformId, const array<float, 3>& data) override;
	void setProgramUniformFloatVec2(void* context, int32_t uniformId, const array<float, 2>& data) override;
	void setProgramAttributeLocation(int32_t programId, int32_t location, const string& name) override;
	void setViewPort(int32_t x, int32_t y, int32_t width, int32_t height) override;
	void updateViewPort() override;
	void setClearColor(float red, float green, float blue, float alpha) override;
	void enableCulling(void* context) override;
	void disableCulling(void* context) override;
	void setFrontFace(void* context, int32_t frontFace) override;
	void setCullFace(int32_t cullFace) override;
	void enableBlending() override;
	void disableBlending() override;
	void enableDepthBufferWriting() override;
	void disableDepthBufferWriting() override;
	void disableDepthBufferTest() override;
	void enableDepthBufferTest() override;
	void setDepthFunction(int32_t depthFunction) override;
	void setColorMask(bool red, bool green, bool blue, bool alpha) override;
	void clear(int32_t mask) override;
	int32_t createTexture() override;
	int32_t createDepthBufferTexture(int32_t width, int32_t height) override;
	int32_t createColorBufferTexture(int32_t width, int32_t height) override;
	void uploadTexture(void* context, Texture* texture) override;
	void resizeDepthBufferTexture(int32_t textureId, int32_t width, int32_t height) override;
	void resizeColorBufferTexture(int32_t textureId, int32_t width, int32_t height) override;
	void bindTexture(void* context, int32_t textureId) override;
	void disposeTexture(int32_t textureId) override;
	int32_t createFramebufferObject(int32_t depthBufferTextureGlId, int32_t colorBufferTextureGlId) override;
	void bindFrameBuffer(int32_t frameBufferId) override;
	void disposeFrameBufferObject(int32_t frameBufferId) override;
	vector<int32_t> createBufferObjects(int32_t bufferCount, bool useGPUMemory, bool shared) override;
	void uploadBufferObject(void* context, int32_t bufferObjectId, int32_t size, FloatBuffer* data) override;
	void uploadIndicesBufferObject(void* context, int32_t bufferObjectId, int32_t size, ShortBuffer* data) override;
	void uploadIndicesBufferObject(void* context, int32_t bufferObjectId, int32_t size, IntBuffer* data) override;
	void bindIndicesBufferObject(void* context, int32_t bufferObjectId) override;
	void bindTextureCoordinatesBufferObject(void* context, int32_t bufferObjectId) override;
	void bindVerticesBufferObject(void* context, int32_t bufferObjectId) override;
	void bindNormalsBufferObject(void* context, int32_t bufferObjectId) override;
	void bindColorsBufferObject(void* context, int32_t bufferObjectId) override;
	void bindTangentsBufferObject(void* context, int32_t bufferObjectId) override;
	void bindBitangentsBufferObject(void* context, int32_t bufferObjectId) override;
	void bindModelMatricesBufferObject(void* context, int32_t bufferObjectId) override;
	void bindEffectColorMulsBufferObject(void* context, int32_t bufferObjectId) override;
	void bindEffectColorAddsBufferObject(void* context, int32_t bufferObjectId) override;
	void bindOrigins(void* context, int32_t bufferObjectId) override;
	void drawInstancedIndexedTrianglesFromBufferObjects(void* context, int32_t triangles, int32_t trianglesOffset, int32_t instances) override;
	void drawIndexedTrianglesFromBufferObjects(void* context, int32_t triangles, int32_t trianglesOffset) override;
	void drawInstancedTrianglesFromBufferObjects(void* context, int32_t triangles, int32_t trianglesOffset, int32_t instances) override;
	void drawTrianglesFromBufferObjects(void* context, int32_t triangles, int32_t trianglesOffset) override;
	void drawPointsFromBufferObjects(void* context, int32_t points, int32_t pointsOffset) override;
	void setLineWidth(float lineWidth) override;
	void drawLinesFromBufferObjects(void* context, int32_t points, int32_t pointsOffset) override;
	void unbindBufferObjects(void* context) override;
	void disposeBufferObjects(vector<int32_t>& bufferObjectIds) override;
	float readPixelDepth(int32_t x, int32_t y) override;
	ByteBuffer* readPixels(int32_t x, int32_t y, int32_t width, int32_t height) override;
	void initGuiMode() override;
	void doneGuiMode() override;

	// overriden methods for skinning on GPU via compute shader
	void dispatchCompute(void* context, int32_t numGroupsX, int32_t numGroupsY, int32_t numGroupsZ) override;
	void memoryBarrier() override;
	void uploadSkinningBufferObject(void* context, int32_t bufferObjectId, int32_t size, FloatBuffer* data) override;
	void uploadSkinningBufferObject(void* context, int32_t bufferObjectId, int32_t size, IntBuffer* data) override;
	void bindSkinningVerticesBufferObject(void* context, int32_t bufferObjectId) override;
	void bindSkinningNormalsBufferObject(void* context, int32_t bufferObjectId) override;
	void bindSkinningVertexJointsBufferObject(void* context, int32_t bufferObjectId) override;
	void bindSkinningVertexJointIdxsBufferObject(void* context, int32_t bufferObjectId) override;
	void bindSkinningVertexJointWeightsBufferObject(void* context, int32_t bufferObjectId) override;
	void bindSkinningVerticesResultBufferObject(void* context, int32_t bufferObjectId) override;
	void bindSkinningNormalsResultBufferObject(void* context, int32_t bufferObjectId) override;
	void bindSkinningMatricesBufferObject(void* context, int32_t bufferObjectId) override;

	//
	int32_t createVertexArrayObject() override;
	void disposeVertexArrayObject(int32_t vertexArrayObjectId) override;
	void bindVertexArrayObject(int32_t vertexArrayObjectId) override;

	//
	int32_t getTextureUnit(void* context) override;
	void setTextureUnit(void* context, int32_t textureUnit) override;
	virtual Matrix2D3x3& getTextureMatrix(void* context) override;
	virtual Renderer_Light& getLight(void* context, int32_t lightId) override;
	virtual array<float, 4>& getEffectColorMul(void* context) override;
	virtual array<float, 4>& getEffectColorAdd(void* context) override;
	virtual Renderer_Material& getMaterial(void* context) override;
	virtual const string getShader(void* context) override;
	virtual void setShader(void* context, const string& id) override;

public:
	/**
	 * Public constructor
	 */
	VKRenderer();
};
