#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <ext/vulkan/spirv/GlslangToSpv.h>
#include <ext/vulkan/svs/thsvs_simpler_vulkan_synchronization.h>
#include <ext/vulkan/vma/src/VmaUsage.h>

#include <array>
#include <list>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/EntityShaderParameters.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/os/threading/ReadWriteLock.h>
#include <tdme/os/threading/SpinLock.h>
#include <tdme/utilities/fwd-tdme.h>

using std::array;
using std::list;
using std::map;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using tdme::engine::fileio::textures::Texture;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;
using tdme::engine::EntityShaderParameters;
using tdme::engine::FrameBuffer;
using tdme::math::Matrix2D3x3;
using tdme::math::Matrix4x4;
using tdme::os::threading::Mutex;
using tdme::os::threading::ReadWriteLock;
using tdme::os::threading::SpinLock;
using tdme::utilities::ByteBuffer;
using tdme::utilities::FloatBuffer;
using tdme::utilities::IntBuffer;
using tdme::utilities::ShortBuffer;

#if defined(CPU_64BIT)
	#define SAMPLER_HASH_MAX	8
	#define SAMPLER_HASH_TYPE __int128
#else
	#define SAMPLER_HASH_MAX 4
	#define SAMPLER_HASH_TYPE __uint64_t
#endif

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
	static constexpr int DRAW_COMMANDBUFFER_MAX { 3 };
	static constexpr int SHADERS_MAX { 100 };
	static constexpr int SHADERS_COMPUTE_MAX { 1 };
	static constexpr int COMMANDS_MAX { 16 };
	static constexpr int COMMANDS_MAX_GRAPHICS { 16 };
	static constexpr int COMMANDS_MAX_COMPUTE { 5 };
	static constexpr int DESC_MAX_UNCACHED { COMMANDS_MAX };
	static constexpr int DESC_MAX_CACHED { 512 };
	static constexpr int OBJECTS_VERTEX_BUFFER_COUNT { 10 };
	static constexpr int POINTS_VERTEX_BUFFER_COUNT { 9 };
	static constexpr int LINES_VERTEX_BUFFER_COUNT { 4 };
	static constexpr int COMPUTE_STORAGE_BUFFER_COUNT { 8 };

	static constexpr int CUBEMAPTEXTUREINDEX_MIN { 1 };

	struct delete_buffer_type {
		VkBuffer buffer;
		VmaAllocation allocation;
	};

	struct delete_image_type {
		VkImage image;
		VmaAllocation allocation;
		VkImageView image_view;
		VkSampler sampler;
	};

	struct buffer_object_type {
		struct reusable_buffer {
			bool memoryMappable { false };
			int64_t frame_used_last { -1 };
			VkBuffer buf { VK_NULL_HANDLE };
			VmaAllocation allocation { VK_NULL_HANDLE };
			uint32_t size { 0 };
			void* data { nullptr };
		};
		int32_t id { 0 };
		bool useGPUMemory { false };
		bool shared { false };
		list<reusable_buffer> buffers;
		uint32_t buffer_count { 0 };
		int64_t frame_cleaned_last { 0 };
		reusable_buffer* current_buffer { nullptr };
		volatile bool uploading { false };
	};

	struct uniform_buffer_type {
		int bufferIdx { 0 };
		int size { -1 };
		// TODO: make them a growing list
		array<VkBuffer, COMMANDS_MAX_GRAPHICS * 5 * 3> buffers;
		array<VmaAllocation, COMMANDS_MAX_GRAPHICS * 5 * 3> allocations;
		array<uint8_t*, COMMANDS_MAX_GRAPHICS * 5 * 3> data;
	};

	struct shader_type {
		struct attribute_layout {
			string name;
			string type;
			uint8_t location;
		};
		struct uniform_type {
			enum uniform_type_enum { TYPE_NONE, TYPE_UNIFORM, TYPE_SAMPLER2D, TYPE_SAMPLERCUBE };
			string name;
			string newName;
			uniform_type_enum type;
			int32_t position;
			uint32_t size;
			int32_t texture_unit;
		};
		vector<attribute_layout> attributeLayouts;
		unordered_map<string, uniform_type*> uniforms;
		vector<uniform_type*> uniformList;
		vector<uniform_type*> samplerUniformList;
		uint32_t ubo_size { 0 };
		uint32_t samplers { 0 };
		int32_t binding_max { -1 };
		vector<uniform_buffer_type> uniform_buffers;
		int32_t ubo_binding_idx { -1 };
		string definitions;
 		string source;
 		string file;
		vector<unsigned int> spirv;
		int32_t id { 0 };
		VkShaderStageFlagBits type;
		VkShaderModule module { VK_NULL_HANDLE };
	};

	struct pipeline_type {
		uint32_t id;
		VkPipeline pipeline { VK_NULL_HANDLE };
	};

	struct program_type {
		struct command_buffer {
			uint32_t desc_idxs1;
			uint32_t desc_idxs2_uncached;
			array<VkDescriptorSet, DESC_MAX_UNCACHED> desc_sets1;
			array<VkDescriptorSet, DESC_MAX_UNCACHED> desc_sets2_uncached;
		};
		struct context {
			uint32_t desc_idxs2;
			array<VkDescriptorSet, DESC_MAX_CACHED> desc_sets2;
			unordered_map<SAMPLER_HASH_TYPE, int> desc_sets2_cache;
			unordered_map<int32_t, unordered_set<SAMPLER_HASH_TYPE>> desc_sets2_cache_textureids;
			array<command_buffer, DRAW_COMMANDBUFFER_MAX> command_buffers;
		};
		int type { 0 };
		unordered_map<uint32_t, pipeline_type*> pipelines;
		vector<int32_t> shader_ids;
		vector<shader_type*> shaders;
		unordered_map<int32_t, string> uniforms;
		uint32_t layout_bindings { 0 };
		VkPipelineLayout pipeline_layout { VK_NULL_HANDLE };
		VkDescriptorSetLayout desc_layout1 { VK_NULL_HANDLE };
		VkDescriptorSetLayout desc_layout2 { VK_NULL_HANDLE };
		int32_t id { 0 };
		vector<context> contexts;
	};

	struct texture_type {
		enum type { TYPE_NONE, TYPE_TEXTURE, TYPE_COLORBUFFER, TYPE_DEPTHBUFFER, TYPE_CUBEMAP };
		volatile bool uploaded { false };
		type type { TYPE_NONE };
		int32_t id { 0 };
		int32_t frame_buffer_object_id { 0 };
		uint32_t width { 0 };
		uint32_t height { 0 };
		VkFormat format { VK_FORMAT_UNDEFINED };
		VkSampler sampler { VK_NULL_HANDLE };
		VkImage image { VK_NULL_HANDLE };
		VkImageAspectFlags aspect_mask { 0 };
		array<array<ThsvsAccessType, 2>, 6> access_types
			{{
				{ THSVS_ACCESS_NONE, THSVS_ACCESS_NONE },
				{ THSVS_ACCESS_NONE, THSVS_ACCESS_NONE },
				{ THSVS_ACCESS_NONE, THSVS_ACCESS_NONE },
				{ THSVS_ACCESS_NONE, THSVS_ACCESS_NONE },
				{ THSVS_ACCESS_NONE, THSVS_ACCESS_NONE },
				{ THSVS_ACCESS_NONE, THSVS_ACCESS_NONE }
			}};
		ThsvsImageLayout svsLayout { THSVS_IMAGE_LAYOUT_OPTIMAL };
		VkImageLayout vkLayout { VK_IMAGE_LAYOUT_UNDEFINED };
		VmaAllocation allocation { VK_NULL_HANDLE };
		VkImageView view { VK_NULL_HANDLE };
		// this texture points to a cube map color buffer/depth buffer texture
		texture_type* cubemap_buffer_texture { nullptr };
		int32_t cubemap_texture_index { 0 };
		// the cube map itself has a attached color buffer and depth buffer
		texture_type* cubemap_colorbuffer { nullptr };
		texture_type* cubemap_depthbuffer { nullptr };
	};

	struct framebuffer_object_type {
		enum type { TYPE_NONE, TYPE_COLORBUFFER, TYPE_GEOMETRYBUFFER };
		int32_t id { 0 };
		type type { TYPE_NONE };
		int32_t depth_texture_id { 0 };
		int32_t color_texture_id { 0 };
		int32_t cubemap_texture_id { 0 };
		int32_t cubemap_texture_index { 0 };
		int32_t depthBufferTextureId { 0 };
		int32_t gbuffer_geometry_buffer_texture_id1 { 0 };
		int32_t gbuffer_geometry_buffer_texture_id2 { 0 };
		int32_t gbuffer_geometry_buffer_texture_id3 { 0 };
		int32_t gbuffer_color_buffer_texture_id1 { 0 };
		int32_t gbuffer_color_buffer_texture_id2 { 0 };
		int32_t gbuffer_color_buffer_texture_id3 { 0 };
		int32_t gbuffer_color_buffer_texture_id4 { 0 };
		int32_t gbuffer_color_buffer_texture_id5 { 0 };
		VkFramebuffer frame_buffer { VK_NULL_HANDLE };
		VkRenderPass render_pass { VK_NULL_HANDLE };
	};

	struct swapchain_buffer_type {
		array<ThsvsAccessType, 2> access_types { THSVS_ACCESS_NONE, THSVS_ACCESS_NONE };
		ThsvsImageLayout svsLayout { THSVS_IMAGE_LAYOUT_OPTIMAL };
		VkImage image { VK_NULL_HANDLE };
		VkImageView view { VK_NULL_HANDLE };
	};

	struct context_type {
		struct command_buffer {
			VkCommandBuffer draw_cmd;
			VkFence draw_fence;
			bool draw_cmd_started;
		};

		int32_t idx { 0 };

		vector<pipeline_type*> pipeline_vector;
		vector<buffer_object_type*> buffer_vector;
		vector<texture_type*> texture_vector;

		VkCommandPool cmd_setup_pool;
		VkCommandBuffer setup_cmd_inuse;
		VkCommandBuffer setup_cmd;
		VkFence setup_fence;

		bool render_pass_started;

		VkCommandPool cmd_draw_pool;
		uint32_t command_buffer_current;
		VkFence draw_fence { VK_NULL_HANDLE };
		program_type* program { nullptr };

		uint32_t pipeline_id;
		VkPipeline pipeline { VK_NULL_HANDLE };

		//
		array<command_buffer, DRAW_COMMANDBUFFER_MAX> command_buffers;

		//
		array<VkDescriptorBufferInfo, 16 + 4> descriptor_buffer_infos;
		array<VkWriteDescriptorSet, 16 + 4> descriptor_write_set;
		array<VkDescriptorImageInfo, 16 + 4> descriptor_image_info;

		//
		VkBuffer bound_indices_buffer { VK_NULL_HANDLE };
		array<VkBuffer, 10> bound_buffers {
			VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE,
			VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE,
			VK_NULL_HANDLE, VK_NULL_HANDLE
		};
		array<VkDeviceSize, 10> bound_buffer_offsets {
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0
		};
		array<uint32_t, 10> bound_buffer_sizes { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		array<uniform_buffer_type*, 4> uniform_buffers;
		int32_t texture_unit_active { 0 };
		struct bound_texture {
			int32_t id { 0 };
			VkSampler sampler { VK_NULL_HANDLE };
			VkImageView view { VK_NULL_HANDLE };
			VkImageLayout layout { VK_IMAGE_LAYOUT_UNDEFINED };
		};
		array<bound_texture, 16> bound_textures;

		int32_t compute_render_barrier_buffer_count { 0 };
		array<VkBuffer, 1024> compute_render_barrier_buffers;

		uint32_t command_count { 0 };

		string shader;
		EntityShaderParameters shaderParameters;
		array<float, 4> effect_color_mul { 1.0f, 1.0f, 1.0f, 1.0f };
		array<float, 4> effect_color_add { 0.0f, 0.0f, 0.0f, 0.0f };
		Renderer_PBRMaterial pbrMaterial;
		Renderer_SpecularMaterial specularMaterial;
		array<Renderer_Light, 8> lights;
		Matrix2D3x3 texture_matrix;

		bool culling_enabled { true };
		int front_face { VK_FRONT_FACE_COUNTER_CLOCKWISE + 1 };
		int front_face_index { VK_FRONT_FACE_COUNTER_CLOCKWISE + 1 };

		int32_t program_id { 0 };

		float maskMaxValue { 1.0f };
		array<float, 3> environmentMappingCubeMapPosition;

		int32_t lighting { 0 };
	};

	VkSurfaceKHR surface { VK_NULL_HANDLE };

	VkInstance inst { VK_NULL_HANDLE };
	VkPhysicalDevice gpu { VK_NULL_HANDLE };
	VkDevice device { VK_NULL_HANDLE };
	SpinLock queue_spinlock;
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
	vector<swapchain_buffer_type> swapchain_buffers;
	vector<VkFramebuffer> window_framebuffers;

	VkFence memorybarrier_fence { VK_NULL_HANDLE };

	ReadWriteLock pipeline_rwlock;

	VkRenderPass render_pass { VK_NULL_HANDLE };

	int32_t shader_idx { 1 };
	int32_t buffer_idx { 1 };
	int32_t texture_idx { 1 };
	vector<program_type*> programList { nullptr };
	unordered_map<int32_t, shader_type*> shaders;
	unordered_map<int32_t, buffer_object_type*> buffers;
	unordered_map<int32_t, texture_type*> textures;
	vector<int32_t> free_texture_ids;
	vector<int32_t> free_buffer_ids;
	vector<framebuffer_object_type*> framebuffers { nullptr };

	ReadWriteLock buffers_rwlock;
	ReadWriteLock textures_rwlock;

	uint32_t width { 0 };
	uint32_t height { 0 };
	VkFormat format { VK_FORMAT_UNDEFINED };
	VkColorSpaceKHR color_space { VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };

	buffer_object_type* empty_vertex_buffer { nullptr };
	int empty_vertex_buffer_id { 0 };
	int depth_buffer_default { 0 };
	int white_texture_sampler2d_default_id { 0 };
	texture_type* white_texture_sampler2d_default { nullptr };
	int white_texture_samplercube_default_id { 0 };
	texture_type* white_texture_samplercube_default { nullptr };

	VkDescriptorPool desc_pool1 { VK_NULL_HANDLE };
	VkDescriptorPool desc_pool2{ VK_NULL_HANDLE };

	// enable/disable validation layers
	bool validate { true };

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

	enum BlendingMode {BLENDING_NONE, BLENDING_NORMAL, BLENDING_ADDITIVE };
	BlendingMode blending_mode { BLENDING_NONE };
	VkCullModeFlagBits cull_mode { VK_CULL_MODE_FRONT_BIT};
	bool depth_buffer_writing { true };
	bool depth_buffer_testing { true };
	int depth_function { VK_COMPARE_OP_LESS_OR_EQUAL };
	float line_width { 1.0f };
	int64_t frame { 0 };

	Mutex delete_mutex;
	vector<delete_buffer_type> delete_buffers;
	vector<delete_image_type> delete_images;

	Mutex dispose_mutex;
	vector<int32_t> dispose_textures;
	vector<int32_t> dispose_buffers;

	vector<context_type> contexts;
	VmaAllocator allocator { VK_NULL_HANDLE };

	VkPresentModeKHR swapchainPresentMode = { VK_PRESENT_MODE_IMMEDIATE_KHR };

	//
	VkBool32 checkLayers(uint32_t check_count, const char **check_names, uint32_t layer_count, VkLayerProperties *layers);
	void setImageLayout(int contextIdx, texture_type* textureObject, const array<ThsvsAccessType,2>& nextAccessTypes, ThsvsImageLayout nextLayout, bool discardContent, uint32_t baseMipLevel = 0, uint32_t levelCount = 1, bool submit = true);
	void setImageLayout2(int contextIdx, texture_type* textureObject, const array<ThsvsAccessType,2>& accessTypes, const array<ThsvsAccessType,2>& nextAccessTypes, ThsvsImageLayout layout, ThsvsImageLayout nextLayout, bool discardContent, uint32_t baseMipLevel, uint32_t levelCount, uint32_t baseArrayLayer, uint32_t layerCount);
	uint32_t getMipLevels(Texture* texture);
	void prepareTextureImage(int contextIdx, struct texture_type* textureObject, VkImageTiling tiling, VkImageUsageFlags usage, VkFlags requiredFlags, Texture* texture, const array<ThsvsAccessType,2>& nextAccesses, ThsvsImageLayout imageLayout, bool disableMipMaps = true, uint32_t baseLevel = 0, uint32_t levelCount = 1);
	VkBuffer getBufferObjectInternal(int contextIdx,  int32_t bufferObjectId, uint32_t& size);
	VkBuffer getBufferObjectInternal(buffer_object_type* bufferObject, uint32_t& size);
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VmaAllocation& allocation, VmaAllocationInfo& allocationInfo);
	buffer_object_type* getBufferObjectInternal(int contextIdx,  int32_t bufferObjectId);
	void uploadBufferObjectInternal(int contextIdx,  buffer_object_type* buffer, int32_t size, const uint8_t* data, VkBufferUsageFlagBits usage);
	void uploadBufferObjectInternal(int contextIdx, int32_t bufferObjectId, int32_t size, const uint8_t* data, VkBufferUsageFlagBits usage);
	texture_type* getTextureInternal(int contextIdx, int32_t textureId);
	pipeline_type* getPipelineInternal(int contextIdx, program_type* program, uint32_t pipelineId);
	void setProgramUniformInternal(void* context, int32_t uniformId, uint8_t* data, int32_t size);
	void shaderInitResources(TBuiltInResource &resources);
	EShLanguage shaderFindLanguage(const VkShaderStageFlagBits shaderType);
	void initializeSwapChain();
	void initializeFrameBuffers();
	void endDrawCommandsAllContexts();
	void requestSubmitDrawBuffers(int contextIdx);
	void initializeRenderPass();
	void startRenderPass(int contextIdx);
	void endRenderPass(int contextIdx);
	void finishPipeline(int contextIdx);
	void createRenderProgram(program_type* program);
	pipeline_type* createObjectsRenderingPipeline(int contextIdx, program_type* program);
	void setupObjectsRenderingPipeline(int contextIdx, program_type* program);
	pipeline_type* createPointsRenderingPipeline(int contextIdx, program_type* program);
	void setupPointsRenderingPipeline(int contextIdx, program_type* program);
	pipeline_type* createLinesRenderingPipeline(int contextIdx, program_type* program);
	void setupLinesRenderingPipeline(int contextIdx, program_type* program);
	void createSkinningComputingProgram(program_type* program);
	pipeline_type* createSkinningComputingPipeline(int contextIdx, program_type* program);
	void setupSkinningComputingPipeline(int contextIdx, program_type* program);
	void unsetPipeline(int contextIdx);
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
		unordered_set<string>& uniformStructsArrays,
		string& uniformsBlock
	);
	void createRasterizationStateCreateInfo(int contextIdx, VkPipelineRasterizationStateCreateInfo& rs);
	void createColorBlendAttachmentState(VkPipelineColorBlendAttachmentState& blend_att_state);
	void createDepthStencilStateCreateInfo(VkPipelineDepthStencilStateCreateInfo& ds);
	uint32_t createPipelineId(program_type* program, int contextIdx);
	void createDepthBufferTexture(int32_t textureId, int32_t width, int32_t height, int32_t cubeMapTextureId, int32_t cubeMapTextureIndex);
	void createBufferTexture(int32_t textureId, int32_t width, int32_t height, int32_t cubeMapTextureId, int32_t cubeMapTextureIndex, VkFormat format);
	void drawInstancedTrianglesFromBufferObjects(void* context, int32_t triangles, int32_t trianglesOffset, VkBuffer indicesBuffer, int32_t instances);
	void createFramebufferObject(int32_t frameBufferId);
	bool beginDrawCommandBuffer(int contextIdx, int bufferId = -1);
	VkCommandBuffer endDrawCommandBuffer(int contextIdx, int bufferId = -1, bool cycleBuffers = true);
	void submitDrawCommandBuffers(int commandBufferCount, VkCommandBuffer* commandBuffers, VkFence& fence, bool waitUntilSubmitted = false, bool resetFence = true);
	void recreateContextFences(int contextIdx);
	void uploadCubeMapSingleTexture(void* context, texture_type* cubemapTextureType, Texture* texture, uint32_t baseArrayLayer);
	void finishRendering();

protected:
	/**
	 * Protected constructor
	 */
	VKRenderer();

public:
	const string getVendor() override;
	const string getRenderer() override;
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
	bool isSupportingIntegerProgramAttributes() override;
	bool isSpecularMappingAvailable() override;
	bool isNormalMappingAvailable() override;
	bool isInstancedRenderingAvailable() override;
	bool isPBRAvailable() override;
	bool isComputeShaderAvailable() override;
	bool isGLCLAvailable() override;
	bool isUsingShortIndices() override;
	bool isDeferredShadingAvailable() override;
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
	int32_t getLighting(void* context) override;
	void setLighting(void* context, int32_t lighting) override;
	void setViewPort(int32_t x, int32_t y, int32_t width, int32_t height) override;
	void updateViewPort() override;
	void setClearColor(float red, float green, float blue, float alpha) override;
	void enableCulling(void* context) override;
	void disableCulling(void* context) override;
	void setFrontFace(void* context, int32_t frontFace) override;
	void setCullFace(int32_t cullFace) override;
	void enableBlending() override;
	void enableAdditionBlending() override;
	void disableBlending() override;
	void enableDepthBufferWriting() override;
	void disableDepthBufferWriting() override;
	void disableDepthBufferTest() override;
	void enableDepthBufferTest() override;
	void setDepthFunction(int32_t depthFunction) override;
	void setColorMask(bool red, bool green, bool blue, bool alpha) override;
	void clear(int32_t mask) override;
	int32_t createTexture() override;
	int32_t createDepthBufferTexture(int32_t width, int32_t height, int32_t cubeMapTextureId, int32_t cubeMapTextureIndex) override;
	int32_t createColorBufferTexture(int32_t width, int32_t height, int32_t cubeMapTextureId, int32_t cubeMapTextureIndex) override;
	int32_t createGBufferGeometryTexture(int32_t width, int32_t height) override;
	int32_t createGBufferColorTexture(int32_t width, int32_t height) override;
	void uploadTexture(void* context, Texture* texture) override;
	void uploadCubeMapTexture(void* context, Texture* textureLeft, Texture* textureRight, Texture* textureTop, Texture* textureBottom, Texture* textureFront, Texture* textureBack) override;
	int32_t createCubeMapTexture(void* context, int32_t width, int32_t height) override;
	void resizeDepthBufferTexture(int32_t textureId, int32_t width, int32_t height) override;
	void resizeColorBufferTexture(int32_t textureId, int32_t width, int32_t height) override;
	void resizeGBufferGeometryTexture(int32_t textureId, int32_t width, int32_t height) override;
	void resizeGBufferColorTexture(int32_t textureId, int32_t width, int32_t height) override;
	void bindTexture(void* context, int32_t textureId) override;
	void bindCubeMapTexture(void* context, int32_t textureId) override;
	void disposeTexture(int32_t textureId) override;
	int32_t createFramebufferObject(int32_t depthBufferTextureId, int32_t colorBufferTextureId, int32_t cubeMapTextureId = 0, int32_t cubeMapTextureIndex = 0) override;
	int32_t createGeometryBufferObject(
		int32_t depthBufferTextureId,
		int32_t geometryBufferTextureId1,
		int32_t geometryBufferTextureId2,
		int32_t geometryBufferTextureId3,
		int32_t colorBufferTextureId1,
		int32_t colorBufferTextureId2,
		int32_t colorBufferTextureId3,
		int32_t colorBufferTextureId4,
		int32_t colorBufferTextureId5
	) override;
	void bindFrameBuffer(int32_t frameBufferId) override;
	void disposeFrameBufferObject(int32_t frameBufferId) override;
	vector<int32_t> createBufferObjects(int32_t bufferCount, bool useGPUMemory, bool shared) override;
	void uploadBufferObject(void* context, int32_t bufferObjectId, int32_t size, FloatBuffer* data) override;
	void uploadBufferObject(void* context, int32_t bufferObjectId, int32_t size, ShortBuffer* data) override;
	void uploadBufferObject(void* context, int32_t bufferObjectId, int32_t size, IntBuffer* data) override;
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
	void bindEffectColorMulsBufferObject(void* context, int32_t bufferObjectId, int32_t divisor) override;
	void bindEffectColorAddsBufferObject(void* context, int32_t bufferObjectIdd, int32_t divisor) override;
	void bindOriginsBufferObject(void* context, int32_t bufferObjectId) override;
	void bindTextureSpriteIndicesBufferObject(void* context, int32_t bufferObjectId) override;
	void bindPointSizesBufferObject(void* context, int32_t bufferObjectId) override;
	void bindSpriteSheetDimensionBufferObject(void* context, int32_t bufferObjectId) override;
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

	// overridden methods for skinning on GPU via compute shader
	void dispatchCompute(void* context, int32_t numNodesX, int32_t numNodesY, int32_t numNodesZ) override;
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
	Matrix2D3x3& getTextureMatrix(void* context) override;
	Renderer_Light& getLight(void* context, int32_t lightId) override;
	array<float, 4>& getEffectColorMul(void* context) override;
	array<float, 4>& getEffectColorAdd(void* context) override;
	Renderer_SpecularMaterial& getSpecularMaterial(void* context) override;
	Renderer_PBRMaterial& getPBRMaterial(void* context) override;
	const string& getShader(void* context) override;
	void setShader(void* context, const string& id) override;
	const EntityShaderParameters& getShaderParameters(void* context) override;
	void setShaderParameters(void* context, const EntityShaderParameters& parameters) override;
	float getMaskMaxValue(void* context) override;
	void setMaskMaxValue(void* context, float maskMaxValue) override;
	array<float, 3>& getEnvironmentMappingCubeMapPosition(void* context) override;
	void setEnvironmentMappingCubeMapPosition(void* context, array<float, 3>& position) override;
	const Renderer_Statistics getStatistics() override;

	/**
	 * Enable/Disable v-sync
	 * @param vSync V-sync enabled
	 */
	void setVSyncEnabled(bool vSync);

};
