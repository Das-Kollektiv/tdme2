#pragma once

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
	friend class VKGL3CoreShaderProgram;
private:
	static constexpr bool VERBOSE { false };
	static constexpr int DRAW_COMMANDBUFFER_MAX { 3 };
	static constexpr int SHADERS_MAX { 100 };
	static constexpr int SHADERS_COMPUTE_MAX { 1 };
	static constexpr int COMMANDS_MAX { 16 };
	static constexpr int COMMANDS_MAX_GRAPHICS { 16 };
	static constexpr int COMMANDS_MAX_COMPUTE { 5 };
	static constexpr int DESC_MAX_UNCACHED { COMMANDS_MAX };
	static constexpr int DESC_MAX_CACHED { 512 }; // TODO: make this dynamic
	static constexpr int OBJECTS_VERTEX_BUFFER_COUNT { 10 };
	static constexpr int POINTS_VERTEX_BUFFER_COUNT { 9 };
	static constexpr int LINES_VERTEX_BUFFER_COUNT { 4 };
	static constexpr int COMPUTE_STORAGE_BUFFER_COUNT { 8 };
	static constexpr int BUFFERS_MAX { 65535 };
	static constexpr int TEXTURES_MAX { 65535 };

	static constexpr int CUBEMAPTEXTUREINDEX_MIN { 1 };

	struct delete_buffer_type {
		VkBuffer buffer;
		VmaAllocation allocation;
	};

	struct delete_image_type {
		VkImage image;
		VmaAllocation allocation;
		VkImageView imageView;
		VkSampler sampler;
	};

	struct buffer_object_type {
		struct reusable_buffer {
			bool memoryMappable { false };
			int64_t frameUsedLast { -1 };
			VkBuffer buf { VK_NULL_HANDLE };
			VmaAllocation allocation { VK_NULL_HANDLE };
			uint32_t size { 0 };
		};
		int32_t id { 0 };
		bool useGPUMemory { false };
		bool shared { false };
		list<reusable_buffer> buffers;
		uint32_t bufferCount { 0 };
		int64_t frameCleanedLast { 0 };
		reusable_buffer* currentBuffer { nullptr };
		volatile bool uploading { false };
	};

	struct uniform_buffer_type {
		struct buffer {
			VkBuffer buffer { VK_NULL_HANDLE };
			VmaAllocation allocation { VK_NULL_HANDLE };
		};
		int bufferIdx { 0 };
		int size { -1 };
		// TODO: make them a growing list
		array<buffer, COMMANDS_MAX_GRAPHICS * DRAW_COMMANDBUFFER_MAX * 5> buffers;
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

	struct pipeline_type {
		uint32_t id;
		VkPipeline pipeline { VK_NULL_HANDLE };
	};

	struct pipelines_parent_type {
		uint32_t id;
		unordered_map<uint32_t, pipeline_type*> pipelines;
	};

	struct program_type {
		struct command_buffer {
			uint32_t descriptorSets1Idx;
			uint32_t descriptorSets2IdxUncached;
			array<VkDescriptorSet, DESC_MAX_UNCACHED> descriptorSets1;
			array<VkDescriptorSet, DESC_MAX_UNCACHED> descriptorSets2Uncached;
		};
		struct context {
			uint32_t descriptorSets2Idx;
			array<VkDescriptorSet, DESC_MAX_CACHED> descriptorSets2;
			unordered_map<SAMPLER_HASH_TYPE, int> descriptorSets2Cache;
			unordered_map<int32_t, unordered_set<SAMPLER_HASH_TYPE>> descriptorSets2CacheTextureIds;
			vector<uint32_t> freeDescriptorSets2Ids;
			array<command_buffer, DRAW_COMMANDBUFFER_MAX> commandBuffers;
		};
		int type { 0 };
		unordered_map<uint32_t, pipelines_parent_type*> pipelinesParents;
		// TODO: clear on viewport dimension change
		vector<int32_t> shaderIds;
		vector<shader_type*> shaders;
		unordered_map<int32_t, string> uniforms;
		uint32_t layoutBindings { 0 };
		VkPipelineLayout pipelineLayout { VK_NULL_HANDLE };
		VkDescriptorSetLayout descriptorSetLayout1 { VK_NULL_HANDLE };
		VkDescriptorSetLayout descriptorSetLayout2 { VK_NULL_HANDLE };
		int32_t id { 0 };
		vector<context> contexts;
	};

	struct texture_type {
		enum type { TYPE_NONE, TYPE_TEXTURE, TYPE_COLORBUFFER, TYPE_DEPTHBUFFER, TYPE_CUBEMAP };
		volatile bool uploaded { false };
		type type { TYPE_NONE };
		int32_t id { 0 };
		int32_t frameBufferObjectId { 0 };
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
		// this texture points to a cube map color buffer/depth buffer texture
		texture_type* cubemapBufferTexture { nullptr };
		int32_t cubemapTextureIndex { 0 };
		// the cube map itself has a attached color buffer and depth buffer
		texture_type* cubemapColorBuffer { nullptr };
		texture_type* cubemapDepthBuffer { nullptr };
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

	struct swapchain_buffer_type {
		array<ThsvsAccessType, 2> accessTypes { THSVS_ACCESS_NONE, THSVS_ACCESS_NONE };
		ThsvsImageLayout svsLayout { THSVS_IMAGE_LAYOUT_OPTIMAL };
		VkImage image { VK_NULL_HANDLE };
		VkImageView view { VK_NULL_HANDLE };
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

		unordered_map<uint64_t, pipeline_type*> pipelines;
		vector<buffer_object_type*> bufferVector;
		vector<texture_type*> textureVector;

		VkCommandPool setupCommandPool;
		VkCommandBuffer setupCommandInUse;
		VkCommandBuffer setupCommand;
		VkFence setupFence;

		bool renderPassStarted;

		VkCommandPool drawCommandPool;
		uint32_t currentCommandBuffer;
		VkFence draw_fence { VK_NULL_HANDLE };
		program_type* program { nullptr };
		vector<program_type*> lastUnsubmittedPrograms;

		uint32_t pipelineId;
		VkPipeline pipeline { VK_NULL_HANDLE };

		//
		array<command_buffer, DRAW_COMMANDBUFFER_MAX> commandBuffers;

		//
		array<VkDescriptorBufferInfo, 16 + 4> descriptorBufferInfos;
		array<VkWriteDescriptorSet, 16 + 4> descriptorWriteSets;
		array<VkDescriptorImageInfo, 16 + 4> descriptorImageInfos;

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
		array<uniform_buffer_type*, 4> uniformBuffers;
		array<vector<uint8_t>, 4> uniformBufferData;
		int32_t activeTextureUnit { 0 };
		struct bound_texture {
			int32_t id { 0 };
			VkSampler sampler { VK_NULL_HANDLE };
			VkImageView view { VK_NULL_HANDLE };
			VkImageLayout layout { VK_IMAGE_LAYOUT_UNDEFINED };
		};
		array<bound_texture, 16> boundTextures;

		vector<VkBuffer> computeRenderBarrierBuffers;

		uint32_t commandCount { 0 };

		string shader;
		EntityShaderParameters shaderParameters;
		array<float, 4> effectColorMul { 1.0f, 1.0f, 1.0f, 1.0f };
		array<float, 4> effectColorAdd { 0.0f, 0.0f, 0.0f, 0.0f };
		Renderer_PBRMaterial pbrMaterial;
		Renderer_SpecularMaterial specularMaterial;
		array<Renderer_Light, 8> lights;
		Matrix2D3x3 textureMatrix;

		bool cullingEnabled { true };
		int frontFace { VK_FRONT_FACE_COUNTER_CLOCKWISE + 1 };
		int frontFaceIndex { VK_FRONT_FACE_COUNTER_CLOCKWISE + 1 };

		int32_t programId { 0 };

		float maskMaxValue { 1.0f };
		array<float, 3> environmentMappingCubeMapPosition;

		int32_t lighting { 0 };
	};

	VkSurfaceKHR surface { VK_NULL_HANDLE };

	VkInstance inst { VK_NULL_HANDLE };
	VkPhysicalDevice gpu { VK_NULL_HANDLE };
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

	uint32_t swapchainImageCount { 0 };
	VkSwapchainKHR swapchain { VK_NULL_HANDLE };
	vector<swapchain_buffer_type> swapchainBuffers;
	vector<VkFramebuffer> windowFramebuffers;

	VkFence memoryBarrierFence { VK_NULL_HANDLE };

	ReadWriteLock pipelineRWlock;
	uint32_t pipelineDimensionId { 0 };

	VkRenderPass renderPass { VK_NULL_HANDLE };

	int32_t shaderIdx { 1 };
	int32_t bufferIdx { 1 };
	int32_t textureIdx { 1 };
	vector<program_type*> programVector { nullptr };
	unordered_map<int32_t, shader_type*> shaders;
	unordered_map<int32_t, buffer_object_type*> buffers;
	unordered_map<int32_t, texture_type*> textures;
	vector<int32_t> freeTextureIds;
	vector<int32_t> freeBufferIds;
	vector<framebuffer_object_type*> framebuffers { nullptr };

	ReadWriteLock buffersRWlock;
	ReadWriteLock texturesRWlock;

	uint32_t width { 0 };
	uint32_t height { 0 };
	VkFormat format { VK_FORMAT_UNDEFINED };
	VkColorSpaceKHR colorSpace { VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };

	buffer_object_type* emptyVertexBuffer { nullptr };
	int emptyVertexBufferId { 0 };
	int depthBufferDefault { 0 };
	int whiteTextureSampler2dDefaultId { 0 };
	texture_type* whiteTextureSampler2dDefault { nullptr };
	int whiteTextureSamplerCubeDefaultId { 0 };
	texture_type* whiteTextureSamplerCubeDefault { nullptr };

	VkDescriptorPool descriptorPool1 { VK_NULL_HANDLE };
	VkDescriptorPool descriptorPool2 { VK_NULL_HANDLE };

	// enable/disable validation layers
	bool validate { true };

	uint32_t lastFrameBuffer { 0 };
	uint32_t currentFrameBuffer { 0 };
	uint32_t queueCount { 0 };

	VkSemaphore imageAcquiredSemaphore { VK_NULL_HANDLE };
	VkSemaphore drawCompleteSemaphore { VK_NULL_HANDLE };

	float clearRed { 0.0f };
	float clearGreen { 0.0f };
	float clearBlue { 0.0f };
	float clearAlpha { 1.0f };

	VkViewport viewport;
	VkRect2D scissor;

	int32_t boundFrameBuffer { 0 };

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

	vector<context_type> contexts;
	VmaAllocator allocator { VK_NULL_HANDLE };
	SpinLock vmaSpinlock;

	string deviceName;

	VkPresentModeKHR swapchainPresentMode { VK_PRESENT_MODE_IMMEDIATE_KHR };

	//
	VkBool32 checkLayers(uint32_t checkCount, const char **checkNames, const vector<VkLayerProperties>& instanceLayers);
	void setImageLayout(int contextIdx, texture_type* textureObject, const array<ThsvsAccessType,2>& nextAccessTypes, ThsvsImageLayout nextLayout, bool discardContent, uint32_t baseMipLevel = 0, uint32_t levelCount = 1, bool submit = true);
	void setImageLayout2(int contextIdx, texture_type* textureObject, const array<ThsvsAccessType,2>& accessTypes, const array<ThsvsAccessType,2>& nextAccessTypes, ThsvsImageLayout layout, ThsvsImageLayout nextLayout, bool discardContent, uint32_t baseMipLevel, uint32_t levelCount, uint32_t baseArrayLayer, uint32_t layerCount);
	void setImageLayout3(int contextIdx, VkImage image, VkImageAspectFlags aspectMask, const array<ThsvsAccessType,2>& accessTypes, const array<ThsvsAccessType,2>& nextAccessTypes, ThsvsImageLayout layout, ThsvsImageLayout nextLayout);
	uint32_t getMipLevels(Texture* texture);
	void prepareTextureImage(int contextIdx, struct texture_type* textureObject, VkImageTiling tiling, VkImageUsageFlags usage, VkFlags requiredFlags, Texture* texture, const array<ThsvsAccessType,2>& nextAccesses, ThsvsImageLayout imageLayout, bool disableMipMaps = true, uint32_t baseLevel = 0, uint32_t levelCount = 1);
	VkBuffer getBufferObjectInternal(int contextIdx,  int32_t bufferObjectId, uint32_t& size);
	VkBuffer getBufferObjectInternal(buffer_object_type* bufferObject, uint32_t& size);
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VmaAllocation& allocation, VmaAllocationInfo& allocationInfo);
	buffer_object_type* getBufferObjectInternal(int contextIdx,  int32_t bufferObjectId);
	void vmaMemCpy(VmaAllocation allocationDst, const uint8_t* src, uint32_t size, uint32_t offset = 0);
	void uploadBufferObjectInternal(int contextIdx,  buffer_object_type* buffer, int32_t size, const uint8_t* data, VkBufferUsageFlagBits usage);
	void uploadBufferObjectInternal(int contextIdx, int32_t bufferObjectId, int32_t size, const uint8_t* data, VkBufferUsageFlagBits usage);
	texture_type* getTextureInternal(int contextIdx, int32_t textureId);
	pipeline_type* getPipelineInternal(int contextIdx, program_type* programm, uint32_t pipelineDimensionId, uint32_t pipelineId);
	void setProgramUniformInternal(int contextIdx, int32_t uniformId, uint8_t* data, int32_t size);
	void initializeSwapChain();
	void initializeFrameBuffers();
	void endDrawCommandsAllContexts(bool waitUntilSubmitted = false);
	void requestSubmitDrawBuffers(int contextIdx);
	void initializeRenderPass();
	void startRenderPass(int contextIdx);
	void endRenderPass(int contextIdx);
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
	void createRasterizationStateCreateInfo(int contextIdx, VkPipelineRasterizationStateCreateInfo& rasterizationStateCreateInfo);
	void createColorBlendAttachmentState(VkPipelineColorBlendAttachmentState& blendAttachmentState);
	void createDepthStencilStateCreateInfo(VkPipelineDepthStencilStateCreateInfo& depthStencilStateCreateInfo);
	uint32_t createPipelineDimensionId();
	uint32_t createPipelineId(program_type* program, int contextIdx);
	void createDepthBufferTexture(int32_t textureId, int32_t width, int32_t height, int32_t cubeMapTextureId, int32_t cubeMapTextureIndex);
	void createBufferTexture(int32_t textureId, int32_t width, int32_t height, int32_t cubeMapTextureId, int32_t cubeMapTextureIndex, VkFormat format);
	void drawInstancedTrianglesFromBufferObjects(int contextIdx, int32_t triangles, int32_t trianglesOffset, VkBuffer indicesBuffer, int32_t instances);
	void createFramebufferObject(int32_t frameBufferId);
	bool beginDrawCommandBuffer(int contextIdx, int bufferId = -1);
	VkCommandBuffer endDrawCommandBuffer(int contextIdx, int bufferId = -1, bool cycleBuffers = true);
	void submitDrawCommandBuffers(int commandBufferCount, VkCommandBuffer* commandBuffers, VkFence& fence, bool waitUntilSubmitted = false, bool resetFence = true);
	void recreateContextFences(int contextIdx);
	void uploadCubeMapSingleTexture(int contextIdx, texture_type* cubemapTextureType, Texture* texture, uint32_t baseArrayLayer);
	void finishRendering();
	void removeTextureFromDescriptorCaches(int textureId);
	void invalidatePipelines();

protected:
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
	int32_t getLighting(int contextIdx) override;
	void setLighting(int contextIdx, int32_t lighting) override;
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
	void bindTextureCoordinatesBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindVerticesBufferObject(int contextIdx, int32_t bufferObjectId) override;
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
	void initGuiMode() override;
	void doneGuiMode() override;

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
	int32_t createVertexArrayObject() override;
	void disposeVertexArrayObject(int32_t vertexArrayObjectId) override;
	void bindVertexArrayObject(int32_t vertexArrayObjectId) override;

	//
	int32_t getTextureUnit(int contextIdx) override;
	void setTextureUnit(int contextIdx, int32_t textureUnit) override;
	Matrix2D3x3& getTextureMatrix(int contextIdx) override;
	Renderer_Light& getLight(int contextIdx, int32_t lightId) override;
	array<float, 4>& getEffectColorMul(int contextIdx) override;
	array<float, 4>& getEffectColorAdd(int contextIdx) override;
	Renderer_SpecularMaterial& getSpecularMaterial(int contextIdx) override;
	Renderer_PBRMaterial& getPBRMaterial(int contextIdx) override;
	const string& getShader(int contextIdx) override;
	void setShader(int contextIdx, const string& id) override;
	const EntityShaderParameters& getShaderParameters(int contextIdx) override;
	void setShaderParameters(int contextIdx, const EntityShaderParameters& parameters) override;
	float getMaskMaxValue(int contextIdx) override;
	void setMaskMaxValue(int contextIdx, float maskMaxValue) override;
	array<float, 3>& getEnvironmentMappingCubeMapPosition(int contextIdx) override;
	void setEnvironmentMappingCubeMapPosition(int contextIdx, array<float, 3>& position) override;
	const Renderer_Statistics getStatistics() override;

	/**
	 * Enable/Disable v-sync
	 * @param vSync V-sync enabled
	 */
	void setVSyncEnabled(bool vSync);

};
