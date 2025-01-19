#pragma once

#if defined(_MSC_VER)
	// this suppresses a warning redefinition of APIENTRY macro
	#define NOMINMAX
	#include <windows.h>
#endif
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <ext/vulkan/spirv/GlslangToSpv.h>
#include <ext/vulkan/svs/thsvs_simpler_vulkan_synchronization.h>
#include <ext/vulkan/vma/src/VmaUsage.h>

#include <array>
#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <variant>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/EntityShaderParameters.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/os/threading/ReadWriteLock.h>
#include <tdme/os/threading/SpinLock.h>
#include <tdme/utilities/fwd-tdme.h>

using std::array;
using std::get;
using std::list;
using std::string;
using std::tuple;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using tdme::engine::Texture;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Engine;
using tdme::engine::EntityShaderParameters;
using tdme::engine::FrameBuffer;
using tdme::math::Matrix3x3;
using tdme::math::Matrix4x4;
using tdme::os::threading::Mutex;
using tdme::os::threading::ReadWriteLock;
using tdme::os::threading::SpinLock;
using tdme::utilities::ByteBuffer;
using tdme::utilities::FloatBuffer;
using tdme::utilities::IntBuffer;
using tdme::utilities::ShortBuffer;

#define TEXTUREDESCRIPTORSET_MAX_TEXTURES 8
struct TextureDescriptorSet_Hash {
	std::size_t operator()(const tuple<uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t>& k) const {
		std::hash<uint64_t> hashVal;
		return hashVal(
			static_cast<uint64_t>(get<0>(k)) ^ (static_cast<uint64_t>(get<1>(k)) << 16) ^ (static_cast<uint64_t>(get<2>(k)) << 32) ^ (static_cast<uint64_t>(get<3>(k)) << 48) ^
			static_cast<uint64_t>(get<4>(k)) ^ (static_cast<uint64_t>(get<5>(k)) << 16) ^ (static_cast<uint64_t>(get<6>(k)) << 32) ^ (static_cast<uint64_t>(get<7>(k)) << 48)
		);
	}
};

/**
 * Vulkan rendererBackend
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::renderer::VKRenderer
	: public RendererBackend
{
	friend class VKGL3CoreShaderProgram;
private:
	static constexpr bool VERBOSE { false };
	static constexpr int DRAW_COMMANDBUFFER_MAX { 3 };
	static constexpr int SHADERSSTAGES_MAX { 2 };
	static constexpr int TEXTUREUNITS_MAX { 16 };
	static constexpr int SHADERS_MAX { 100 };
	static constexpr int SHADERS_COMPUTE_MAX { 1 };
	static constexpr int COMMANDS_MAX { 16 };
	static constexpr int COMMANDS_MAX_GRAPHICS { 16 };
	static constexpr int COMMANDS_MAX_COMPUTE { 5 };
	static constexpr int DESC_MAX_UNCACHED { COMMANDS_MAX };
	static constexpr int DESC_MAX_CACHED { 512 }; // TODO: make this dynamic
	static constexpr int OBJECTS_VERTEX_BUFFER_COUNT { 10 };
	static constexpr int GUI_VERTEX_BUFFER_COUNT { 4 };
	static constexpr int POINTS_VERTEX_BUFFER_COUNT { 9 };
	static constexpr int LINES_VERTEX_BUFFER_COUNT { 4 };
	static constexpr int COMPUTE_STORAGE_BUFFER_COUNT { 8 };
	static constexpr int BUFFERS_MAX { 65535 };
	static constexpr int TEXTURES_MAX { 65535 };
	static constexpr int PROGRAMS_MAX { 128 };

	static constexpr int CUBEMAPTEXTUREINDEX_MIN { 1 };

	struct delete_buffer_type {
		delete_buffer_type(
			VkBuffer buffer,
			VmaAllocation allocation
		):
			buffer(buffer),
			allocation(allocation)
		{}
		VkBuffer buffer;
		VmaAllocation allocation;
	};

	struct delete_image_type {
		delete_image_type(
			VkImage image,
			VmaAllocation allocation,
			VkImageView imageView,
			VkSampler sampler
		):
			image(image),
			allocation(allocation),
			imageView(imageView),
			sampler(sampler)
		{}
		VkImage image;
		VmaAllocation allocation;
		VkImageView imageView;
		VkSampler sampler;
	};

	struct buffer_object_type {
		struct reusable_buffer {
			bool memoryMappable { false };
			int64_t frameUsedLast { -1 };
			VkBuffer buffer { VK_NULL_HANDLE };
			VmaAllocation allocation { VK_NULL_HANDLE };
			uint32_t size { 0 };
		};
		int32_t id { 0 };
		bool useGPUMemory { false };
		bool shared { false };
		list<reusable_buffer> buffers;
		vector<reusable_buffer*> frameFreeBuffers;
		uint32_t bufferCount { 0 };
		int64_t frameUsedLast { -1LL };
		int64_t frameCleanedLast { -1LL };
		reusable_buffer* currentBuffer { nullptr };
		reusable_buffer* bindBuffer { nullptr };
		volatile bool uploading { false };
	};

	struct uniform_buffer_type {
		struct uniform_buffer_type_buffer {
			VkBuffer buffer { VK_NULL_HANDLE };
			VmaAllocation allocation { VK_NULL_HANDLE };
		};
		int bufferIdx { 0 };
		int size { -1 };
		vector<uint8_t> uniformBufferData;
		// TODO: make them a growing list
		array<uniform_buffer_type_buffer, COMMANDS_MAX_GRAPHICS * DRAW_COMMANDBUFFER_MAX * 5> buffers;
	};

	struct shader_type {
		struct attribute_layout {
			attribute_layout(
				const string& name,
				const string& type,
				const uint8_t location
			):
				name(name),
				type(type),
				location(location)
			{}
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
			int32_t textureUnit;
		};
		vector<attribute_layout> attributeLayouts;
		unordered_map<string, uniform_type*> uniforms;
		vector<uniform_type*> uniformList;
		vector<uniform_type*> samplerUniformList;
		uint32_t uboSize { 0 };
		uint32_t samplers { 0 };
		int32_t maxBindings { -1 };
		vector<uniform_buffer_type> uniformBuffers;
		int32_t uboBindingIdx { -1 };
		string definitions;
 		string source;
 		string file;
 		string cacheId;
 		string hash;
		vector<uint32_t> spirv;
		bool valid;
		int32_t id { 0 };
		VkShaderStageFlagBits type;
		VkShaderModule module { VK_NULL_HANDLE };
	};

	struct framebuffer_pipelines_type {
		uint64_t id { 0 };
		uint32_t width { 0 };
		uint32_t height { 0 };
		uint32_t frameBufferId { 0 };
		array<VkPipeline, 32768> pipelines;
	};

	struct program_type {
		struct command_buffer {
			uint32_t uboDescriptorSetsIdx;
			uint32_t texturesDescriptorSetsIdxUncached;
			array<VkDescriptorSet, DESC_MAX_UNCACHED> uboDescriptorSets;
			array<VkDescriptorSet, DESC_MAX_UNCACHED> texturesDescriptorSetsUncached;
		};
		struct context {
			uint32_t descriptorSets2Idx;
			array<VkDescriptorSet, DESC_MAX_CACHED> descriptorSets2; // TODO: rename those fuckers
			unordered_map<tuple<uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t>, int, TextureDescriptorSet_Hash> texturesDescriptorSetsCache;
			unordered_map<int32_t, unordered_set<tuple<uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t>, TextureDescriptorSet_Hash>> texturesDescriptorSetsCacheTextureIds;
			vector<uint32_t> freeTextureDescriptorSetsIds;
			array<command_buffer, DRAW_COMMANDBUFFER_MAX> commandBuffers;
		};
		int type { 0 };
		// TODO: clear on viewport dimension change
		vector<int32_t> shaderIds;
		vector<shader_type*> shaders;
		unordered_map<int32_t, string> uniformLocations;
		uint32_t layoutBindings { 0 };
		VkPipelineLayout pipelineLayout { VK_NULL_HANDLE };
		VkDescriptorSetLayout uboDescriptorSetLayout { VK_NULL_HANDLE };
		VkDescriptorSetLayout texturesDescriptorSetLayout { VK_NULL_HANDLE };
		int32_t id { 0 };
		vector<context> contexts;
	};

	struct image_layout_change {
		bool valid { false };
		VkPipelineStageFlags srcStages { 0 };
		VkPipelineStageFlags dstStages { 0 };
		VkImageMemoryBarrier vkImageMemoryBarrier {};
		array<ThsvsAccessType, 2> accessTypes { THSVS_ACCESS_NONE, THSVS_ACCESS_NONE };
		ThsvsImageLayout svsLayout { THSVS_IMAGE_LAYOUT_GENERAL };
		VkImageLayout vkLayout { VK_IMAGE_LAYOUT_UNDEFINED };
	};

	struct texture_type {
		enum type { TYPE_NONE, TYPE_TEXTURE, TYPE_CUBEMAP_TEXTURE, TYPE_COLORBUFFER, TYPE_DEPTHBUFFER, TYPE_CUBEMAPBUFFER };
		volatile bool uploaded { false };
		type type { TYPE_NONE };
		int32_t id { 0 };
		uint32_t width { 0 };
		uint32_t height { 0 };
		VkFormat format { VK_FORMAT_UNDEFINED };
		VkSampler sampler { VK_NULL_HANDLE };
		VkImage image { VK_NULL_HANDLE };
		VkImageAspectFlags aspectMask { 0 };
		array<array<ThsvsAccessType, 2>, 6> accessTypes
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
		// this texture points to a cube map color buffer/depth buffer
		// 	as cube map frame buffer color buffer and cube map frame buffer depth buffer are pseudo textures
		// 	only providing views and samplers, but not image itself
		texture_type* cubemapBufferTexture { nullptr };
		int32_t cubemapTextureIndex { 0 };
		// the cube map itself has a attached color buffer and depth buffer
		texture_type* cubemapColorBuffer { nullptr };
		texture_type* cubemapDepthBuffer { nullptr };
		//
		int32_t frameBufferObjectId { 0 };
		image_layout_change frameBufferBindImageLayoutChange {};
		image_layout_change frameBufferUnbindImageLayoutChange {};
		//
		texture_type* bindTexture { nullptr };
	};

	struct framebuffer_object_type {
		enum type { TYPE_NONE, TYPE_COLORBUFFER, TYPE_GEOMETRYBUFFER };
		int32_t id { 0 };
		type type { TYPE_NONE };
		int32_t depthTextureId { 0 };
		int32_t colorTextureId { 0 };
		int32_t cubemapTextureId { 0 };
		int32_t cubemapTextureIndex { 0 };
		int32_t depthBufferTextureId { 0 };
		int32_t gbufferGeometryBufferTextureId1 { 0 };
		int32_t gbufferGeometryBufferTextureId2 { 0 };
		int32_t gbufferGeometryBufferTextureId3 { 0 };
		int32_t gbufferColorBufferTextureId1 { 0 };
		int32_t gbufferColorBufferTextureId2 { 0 };
		int32_t gbufferColorBufferTextureId3 { 0 };
		int32_t gbufferColorBufferTextureId4 { 0 };
		int32_t gbufferColorBufferTextureId5 { 0 };
		VkFramebuffer frameBuffer { VK_NULL_HANDLE };
		VkRenderPass renderPass { VK_NULL_HANDLE };
	};

	struct window_frambuffer_buffer_type {
		array<ThsvsAccessType, 2> accessTypes { THSVS_ACCESS_NONE, THSVS_ACCESS_NONE };
		ThsvsImageLayout svsLayout { THSVS_IMAGE_LAYOUT_OPTIMAL };
		VkImage image { VK_NULL_HANDLE };
		VkImageView view { VK_NULL_HANDLE };
		VkFramebuffer framebuffer { VK_NULL_HANDLE };
		int width { -1 };
		int height { -1 };
	};

	struct context_type {
		struct command_buffer {
			VkCommandBuffer drawCommand;
			VkFence drawFence;
			bool drawCmdStarted;
		};

		int32_t idx { 0 };

		VkCommandPool setupCommandPool;
		VkCommandBuffer setupCommandInUse;
		VkCommandBuffer setupCommand;
		VkFence setupFence;

		bool renderPassStarted;

		VkCommandPool drawCommandPool;
		uint32_t currentCommandBuffer;
		program_type* program { nullptr };

		//
		uint16_t pipelineIdx;
		VkPipeline pipeline { VK_NULL_HANDLE };

		//
		array<command_buffer, DRAW_COMMANDBUFFER_MAX> commandBuffers;

		//
		array<VkDescriptorBufferInfo, TEXTUREUNITS_MAX + SHADERSSTAGES_MAX> descriptorBufferInfos;
		array<VkWriteDescriptorSet, TEXTUREUNITS_MAX + SHADERSSTAGES_MAX> descriptorWriteSets;
		array<VkDescriptorImageInfo, TEXTUREUNITS_MAX + SHADERSSTAGES_MAX> descriptorImageInfos;

		//
		VkBuffer boundIndicesBuffer { VK_NULL_HANDLE };
		array<VkBuffer, 10> boundBuffers {
			VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE,
			VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE,
			VK_NULL_HANDLE, VK_NULL_HANDLE
		};
		array<VkDeviceSize, 10> boundBufferOffsets {
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0
		};
		array<uint32_t, 10> boundBufferSizes { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		int32_t activeTextureUnit { 0 };
		struct bound_texture {
			int32_t id { 0 };
			VkSampler sampler { VK_NULL_HANDLE };
			VkImageView view { VK_NULL_HANDLE };
			VkImageLayout layout { VK_IMAGE_LAYOUT_UNDEFINED };
		};
		array<bound_texture, TEXTUREUNITS_MAX> boundTextures;

		vector<VkBuffer> computeRenderBarrierBuffers;

		uint32_t commandCount { 0 };

		bool cullingEnabled { true };
		int frontFace { VK_FRONT_FACE_COUNTER_CLOCKWISE + 1 };
		int frontFaceIndex { VK_FRONT_FACE_COUNTER_CLOCKWISE + 1 };

		unordered_set<int32_t> uploadedTextureIds;
	};

	VkSurfaceKHR surface { VK_NULL_HANDLE };

	VkInstance instance { VK_NULL_HANDLE };
	VkPhysicalDevice physicalDevice { VK_NULL_HANDLE };
	VkDevice device { VK_NULL_HANDLE };
	SpinLock queueSpinlock;
	VkQueue queue { VK_NULL_HANDLE };
	VkPhysicalDeviceProperties gpuProperties;
	VkPhysicalDeviceFeatures gpuFeatures;
	VkQueueFamilyProperties *queueProperties { nullptr };
	VkPhysicalDeviceMemoryProperties memoryProperties;
	uint32_t graphicsQueueNodeIndex { 0 };

	PFN_vkGetPhysicalDeviceSurfaceSupportKHR fpGetPhysicalDeviceSurfaceSupportKHR { nullptr };
	PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR fpGetPhysicalDeviceSurfaceCapabilitiesKHR { nullptr };
	PFN_vkGetPhysicalDeviceSurfaceFormatsKHR fpGetPhysicalDeviceSurfaceFormatsKHR { nullptr };
	PFN_vkGetPhysicalDeviceSurfacePresentModesKHR fpGetPhysicalDeviceSurfacePresentModesKHR { nullptr };
	PFN_vkCreateSwapchainKHR fpCreateSwapchainKHR { nullptr };
	PFN_vkDestroySwapchainKHR fpDestroySwapchainKHR { nullptr };
	PFN_vkGetSwapchainImagesKHR fpGetSwapchainImagesKHR { nullptr };
	PFN_vkAcquireNextImageKHR fpAcquireNextImageKHR { nullptr };
	PFN_vkQueuePresentKHR fpQueuePresentKHR { nullptr };

	uint32_t windowSwapchainImageCount { 0 };
	VkSwapchainKHR windowSwapchain { VK_NULL_HANDLE };
	vector<window_frambuffer_buffer_type> windowFramebufferBuffers;
	uint32_t lastWindowFramebufferIdx { 0 };
	uint32_t currentWindowFramebufferIdx { 0 };

	SpinLock pipelinesSpinLock;
	uint64_t framebufferPipelinesId { 0 };
	framebuffer_pipelines_type* framebufferPipelinesCache { nullptr };
	vector<framebuffer_pipelines_type*> framebuffersPipelines;

	VkRenderPass renderPass { VK_NULL_HANDLE };

	int32_t shaderIdx { 1 };
	int32_t bufferIdx { 1 };
	int32_t textureIdx { 1 };
	vector<program_type*> programVector { nullptr };
	unordered_map<int32_t, shader_type*> shaders;
	array<buffer_object_type*, BUFFERS_MAX + 1> buffers;
	array<texture_type*, TEXTURES_MAX + 1> textures;
	vector<int32_t> freeTextureIds;
	vector<int32_t> freeBufferIds;
	vector<framebuffer_object_type*> framebuffers { nullptr };

	Mutex buffersMutex;
	Mutex texturesMutex;

	uint32_t windowWidth { 0 };
	uint32_t windowHeight { 0 };
	VkFormat windowFormat { VK_FORMAT_UNDEFINED };
	VkColorSpaceKHR windowColorSpace { VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };

	buffer_object_type* emptyVertexBuffer { nullptr };
	int emptyVertexBufferId { 0 };
	int depthBufferDefault { 0 };
	int whiteTextureSampler2dDefaultId { 0 };
	texture_type* whiteTextureSampler2dDefault { nullptr };
	int whiteTextureSamplerCubeDefaultId { 0 };
	texture_type* whiteTextureSamplerCubeDefault { nullptr };

	VkDescriptorPool descriptorPool1 { VK_NULL_HANDLE };
	VkDescriptorPool descriptorPool2 { VK_NULL_HANDLE };

	uint32_t queueCount { 0 };

	VkSemaphore imageAcquiredSemaphore { VK_NULL_HANDLE };
	VkSemaphore drawCompleteSemaphore { VK_NULL_HANDLE };

	float clearRed { 0.0f };
	float clearGreen { 0.0f };
	float clearBlue { 0.0f };
	float clearAlpha { 1.0f };

	VkViewport viewport;
	VkRect2D scissor;

	int32_t boundFrameBufferId { 0 };

	enum BlendingMode {BLENDING_NONE, BLENDING_NORMAL, BLENDING_ADDITIVE };
	BlendingMode blendingMode { BLENDING_NONE };
	VkCullModeFlagBits cullMode { VK_CULL_MODE_FRONT_BIT};
	bool depthBufferWriting { true };
	bool depthBufferTesting { true };
	int depthFunction { VK_COMPARE_OP_LESS_OR_EQUAL };
	float lineWidth { 1.0f };
	int64_t frame { 0 };

	Mutex deleteMutex;
	vector<delete_buffer_type> deleteBuffers;
	vector<delete_image_type> deleteImages;

	Mutex disposeMutex;
	vector<int32_t> disposeTextures;
	vector<int32_t> disposeBuffers;
	vector<VkPipeline> disposePipelines;

	VmaAllocator vmaAllocator { VK_NULL_HANDLE };
	SpinLock vmaSpinlock;

	vector<context_type> contexts;
	vector<VkFence> contextsDrawFences;

	string deviceName;

	VkPresentModeKHR swapchainPresentMode { VK_PRESENT_MODE_IMMEDIATE_KHR };
	VkPresentModeKHR lastSwapchainPresentMode { VK_PRESENT_MODE_IMMEDIATE_KHR };
	bool vSync { false };

	bool deferredShadingAvailable;
	bool textureCompressionAvailable;

	//
	VkBool32 checkLayers(uint32_t checkCount, const char **checkNames, const vector<VkLayerProperties>& instanceLayers);
	void setImageLayout(int contextIdx, texture_type* textureObject, const array<ThsvsAccessType,2>& nextAccessTypes, ThsvsImageLayout nextLayout, bool discardContent, uint32_t baseMipLevel = 0, uint32_t levelCount = 1, bool submit = true);
	void getImageLayoutChange(
		image_layout_change& imageLayoutChange,
		texture_type* textureObject,
		const array<ThsvsAccessType,2>& prevAccessTypes,
		const array<ThsvsAccessType,2>& nextAccessTypes,
		ThsvsImageLayout prevLayout,
		ThsvsImageLayout nextLayout,
		bool discardContent,
		uint32_t baseMipLevel = 0,
		uint32_t levelCount = 1
	);
	void applyImageLayoutChange(int contextIdx, const image_layout_change& imageLayoutChange, texture_type* textureObject, bool submit = true);
	void applyImageLayoutChanges(int contextIdx, const array<image_layout_change, 8> imageLayoutChanges, array<texture_type*, 8> textureObjects, bool submit = true);
	void setImageLayout2(int contextIdx, texture_type* textureObject, const array<ThsvsAccessType,2>& accessTypes, const array<ThsvsAccessType,2>& nextAccessTypes, ThsvsImageLayout layout, ThsvsImageLayout nextLayout, bool discardContent, uint32_t baseMipLevel, uint32_t levelCount, uint32_t baseArrayLayer, uint32_t layerCount, bool updateTextureObject);
	void setImageLayout3(int contextIdx, VkImage image, VkImageAspectFlags aspectMask, const array<ThsvsAccessType,2>& accessTypes, const array<ThsvsAccessType,2>& nextAccessTypes, ThsvsImageLayout layout, ThsvsImageLayout nextLayout);
	void prepareTextureImage(int contextIdx, struct texture_type* textureObject, VkImageTiling tiling, VkImageUsageFlags usage, VkFlags requiredFlags, Texture* texture, const array<ThsvsAccessType,2>& nextAccesses, ThsvsImageLayout imageLayout, bool disableMipMaps = true, uint32_t baseLevel = 0, uint32_t levelCount = 1);
	void prepareMipMapTextureImage(int contextIdx, struct texture_type* textureObject, VkImageTiling tiling, VkImageUsageFlags usage, VkFlags requiredFlags, Texture* texture, const Texture::MipMapTexture& mipMapTexture, const array<ThsvsAccessType,2>& nextAccesses, ThsvsImageLayout imageLayout);
	VkBuffer getBindBufferObjectInternal(int32_t bufferObjectId, uint32_t& size);
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VmaAllocation& allocation, VmaAllocationInfo& allocationInfo);
	buffer_object_type* getBufferObjectInternal(int32_t bufferObjectId);
	void vmaMemCpy(VmaAllocation allocationDst, const uint8_t* src, uint32_t size, uint32_t offset = 0);
	void uploadBufferObjectInternal(int contextIdx,  buffer_object_type* buffer, int32_t size, const uint8_t* data, VkBufferUsageFlagBits usage);
	void uploadBufferObjectInternal(int contextIdx, int32_t bufferObjectId, int32_t size, const uint8_t* data, VkBufferUsageFlagBits usage);
	texture_type* getTextureInternal(int32_t textureId);
	texture_type* getBindTextureInternal(int32_t textureId);
	framebuffer_pipelines_type* getFramebufferPipelines(uint64_t framebufferPipelinesId);
	framebuffer_pipelines_type* createFramebufferPipelines(uint64_t framebufferPipelinesId);
	VkPipeline getPipelineInternal(int contextIdx, program_type* programm, uint64_t framebuffePipelineId, uint32_t pipelineIdx);
	void setProgramUniformInternal(int contextIdx, int32_t uniformId, uint8_t* data, int32_t size);
	void initializeSwapChain();
	void initializeFrameBuffers();
	void endDrawCommandsAllContexts();
	void requestSubmitDrawBuffers(int contextIdx);
	void initializeRenderPass();
	void startRenderPass(int contextIdx);
	void endRenderPass(int contextIdx);
	void createRenderProgram(program_type* program);
	void createGUIRenderingPipeline(int contextIdx, program_type* program);
	void setupGUIRenderingPipeline(int contextIdx, program_type* program);
	void createObjectsRenderingPipeline(int contextIdx, program_type* program);
	void setupObjectsRenderingPipeline(int contextIdx, program_type* program);
	void createPointsRenderingPipeline(int contextIdx, program_type* program);
	void setupPointsRenderingPipeline(int contextIdx, program_type* program);
	void createLinesRenderingPipeline(int contextIdx, program_type* program);
	void setupLinesRenderingPipeline(int contextIdx, program_type* program);
	void createSkinningComputingProgram(program_type* program);
	void setupSkinningComputingPipeline(int contextIdx, program_type* program);
	void unsetPipeline(int contextIdx);
	void prepareSetupCommandBuffer(int contextIdx);
	void finishSetupCommandBuffer(int contextIdx);
	void finishSetupCommandBuffers();
	void reshape();
	void createRasterizationStateCreateInfo(int contextIdx, VkPipelineRasterizationStateCreateInfo& rasterizationStateCreateInfo);
	void createColorBlendAttachmentState(VkPipelineColorBlendAttachmentState& blendAttachmentState);
	void createDepthStencilStateCreateInfo(VkPipelineDepthStencilStateCreateInfo& depthStencilStateCreateInfo);
	uint64_t createPipelineFramebufferId();
	uint16_t createPipelineIndex(program_type* program, int contextIdx);
	void createDepthBufferTexture(int32_t textureId, int32_t width, int32_t height, int32_t cubeMapTextureId, int32_t cubeMapTextureIndex);
	void createBufferTexture(int32_t textureId, int32_t width, int32_t height, int32_t cubeMapTextureId, int32_t cubeMapTextureIndex, VkFormat format);
	void drawInstancedTrianglesFromBufferObjects(int contextIdx, int32_t triangles, int32_t trianglesOffset, VkBuffer indicesBuffer, int32_t instances);
	void createFramebufferObject(int32_t frameBufferId);
	bool beginDrawCommandBuffer(int contextIdx, int bufferId = -1);
	VkCommandBuffer endDrawCommandBuffer(int contextIdx, int bufferId = -1, bool cycleBuffers = true);
	void submitDrawCommandBuffers(int commandBufferCount, VkCommandBuffer* commandBuffers, VkFence& fence);
	void uploadCubeMapSingleTexture(int contextIdx, texture_type* cubemapTextureType, Texture* texture, uint32_t baseArrayLayer);
	void finishRendering();
	void invalidateTextureDescriptorCaches(int textureId);
	void invalidatePipelines();

protected:
	// forbid class copy
	FORBID_CLASS_COPY(VKRenderer)

	/**
	 * Protected constructor
	 */
	VKRenderer();

public:
	const string getVendor() override;
	const string getRenderer() override;
	const string getShaderVersion() override;
	void initialize() override;
	void initializeFrame() override;
	void finishFrame() override;
	bool isSupportingMultithreadedRendering() override;
	bool isTextureCompressionAvailable() override;
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
	void useProgram(int contextIdx, int32_t programId) override;
	int32_t createProgram(int type) override;
	void attachShaderToProgram(int32_t programId, int32_t shaderId) override;
	bool linkProgram(int32_t programId) override;
	int32_t getProgramUniformLocation(int32_t programId, const string& name) override;
	void setProgramUniformInteger(int contextIdx, int32_t uniformId, int32_t value) override;
	void setProgramUniformFloat(int contextIdx, int32_t uniformId, float value) override;
	void setProgramUniformFloatMatrix3x3(int contextIdx, int32_t uniformId, const array<float, 9>& data) override;
	void setProgramUniformFloatMatrix4x4(int contextIdx, int32_t uniformId, const array<float, 16>& data) override;
	void setProgramUniformFloatMatrices4x4(int contextIdx, int32_t uniformId, int32_t count, FloatBuffer* data) override;
	void setProgramUniformFloatVec4(int contextIdx, int32_t uniformId, const array<float, 4>& data) override;
	void setProgramUniformFloatVec3(int contextIdx, int32_t uniformId, const array<float, 3>& data) override;
	void setProgramUniformFloatVec2(int contextIdx, int32_t uniformId, const array<float, 2>& data) override;
	void setProgramAttributeLocation(int32_t programId, int32_t location, const string& name) override;
	void setViewPort(int32_t width, int32_t height) override;
	void updateViewPort() override;
	void setClearColor(float red, float green, float blue, float alpha) override;
	void enableCulling(int contextIdx) override;
	void disableCulling(int contextIdx) override;
	void setFrontFace(int contextIdx, int32_t frontFace) override;
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
	void uploadTexture(int contextIdx, Texture* texture) override;
	void uploadCubeMapTexture(int contextIdx, Texture* textureLeft, Texture* textureRight, Texture* textureTop, Texture* textureBottom, Texture* textureFront, Texture* textureBack) override;
	int32_t createCubeMapTexture(int contextIdx, int32_t width, int32_t height) override;
	void resizeDepthBufferTexture(int32_t textureId, int32_t width, int32_t height) override;
	void resizeColorBufferTexture(int32_t textureId, int32_t width, int32_t height) override;
	void resizeGBufferGeometryTexture(int32_t textureId, int32_t width, int32_t height) override;
	void resizeGBufferColorTexture(int32_t textureId, int32_t width, int32_t height) override;
	void bindTexture(int contextIdx, int32_t textureId) override;
	void bindCubeMapTexture(int contextIdx, int32_t textureId) override;
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
	void uploadBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, FloatBuffer* data) override;
	void uploadBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, ShortBuffer* data) override;
	void uploadBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, IntBuffer* data) override;
	void uploadIndicesBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, ShortBuffer* data) override;
	void uploadIndicesBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, IntBuffer* data) override;
	void bindIndicesBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindSolidColorsBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindTextureCoordinatesBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindVerticesBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindVertices2BufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindNormalsBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindColorsBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindTangentsBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindBitangentsBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindModelMatricesBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindEffectColorMulsBufferObject(int contextIdx, int32_t bufferObjectId, int32_t divisor) override;
	void bindEffectColorAddsBufferObject(int contextIdx, int32_t bufferObjectIdd, int32_t divisor) override;
	void bindOriginsBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindTextureSpriteIndicesBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindPointSizesBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindSpriteSheetDimensionBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void drawInstancedIndexedTrianglesFromBufferObjects(int contextIdx, int32_t triangles, int32_t trianglesOffset, int32_t instances) override;
	void drawIndexedTrianglesFromBufferObjects(int contextIdx, int32_t triangles, int32_t trianglesOffset) override;
	void drawInstancedTrianglesFromBufferObjects(int contextIdx, int32_t triangles, int32_t trianglesOffset, int32_t instances) override;
	void drawTrianglesFromBufferObjects(int contextIdx, int32_t triangles, int32_t trianglesOffset) override;
	void drawPointsFromBufferObjects(int contextIdx, int32_t points, int32_t pointsOffset) override;
	void setLineWidth(float lineWidth) override;
	void drawLinesFromBufferObjects(int contextIdx, int32_t points, int32_t pointsOffset) override;
	void unbindBufferObjects(int contextIdx) override;
	void disposeBufferObjects(vector<int32_t>& bufferObjectIds) override;
	float readPixelDepth(int32_t x, int32_t y) override;
	ByteBuffer* readPixels(int32_t x, int32_t y, int32_t width, int32_t height) override;
	void initGUIMode() override;
	void doneGUIMode() override;

	// overridden methods for skinning on GPU via compute shader
	void dispatchCompute(int contextIdx, int32_t numNodesX, int32_t numNodesY, int32_t numNodesZ) override;
	void memoryBarrier() override;
	void uploadSkinningBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, FloatBuffer* data) override;
	void uploadSkinningBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, IntBuffer* data) override;
	void bindSkinningVerticesBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindSkinningNormalsBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindSkinningVertexJointsBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindSkinningVertexJointIdxsBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindSkinningVertexJointWeightsBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindSkinningVerticesResultBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindSkinningNormalsResultBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindSkinningMatricesBufferObject(int contextIdx, int32_t bufferObjectId) override;

	//
	int32_t getTextureUnit(int contextIdx) override;
	void setTextureUnit(int contextIdx, int32_t textureUnit) override;
	const Renderer_Statistics getStatistics() override;

	//
	void setVSync(bool vSync) override;

};
