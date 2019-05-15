/**
 * based on https://github.com/glfw/glfw/blob/master/tests/vulkan.c and util.c from Vulkan samples, https://vulkan-tutorial.com, https://github.com/KhronosGroup/Vulkan-Docs/wiki/Synchronization-Examples
 */

#include <tdme/engine/subsystems/renderer/VKRenderer.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <ext/vulkan/glslang/Public/ShaderLang.h>
#include <ext/vulkan/OGLCompilersDLL/InitializeDll.h>
#include <ext/vulkan/spirv/GlslangToSpv.h>

#include <stdlib.h>
#include <string.h>

#include <array>
#include <cassert>
#include <iterator>
#include <map>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <tdme/application/Application.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Timing.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/os/threading/ReadWriteLock.h>
#include <tdme/utils/Buffer.h>
#include <tdme/utils/ByteBuffer.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/FloatBuffer.h>
#include <tdme/utils/Integer.h>
#include <tdme/utils/IntBuffer.h>
#include <tdme/utils/ShortBuffer.h>
#include <tdme/utils/StringTokenizer.h>
#include <tdme/utils/StringUtils.h>

using std::to_string;

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define ERR_EXIT(err_msg, err_class)                                           \
    do {                                                                       \
        printf(err_msg);                                                       \
        fflush(stdout);                                                        \
        exit(1);                                                               \
    } while (0)

#define GET_INSTANCE_PROC_ADDR(inst, entrypoint)														\
    {																											\
        fp##entrypoint = (PFN_vk##entrypoint)vkGetInstanceProcAddr(inst, "vk" #entrypoint);				\
        if (fp##entrypoint == NULL) {																	\
            ERR_EXIT("vkGetInstanceProcAddr failed to find vk" #entrypoint, "vkGetInstanceProcAddr Failure");	\
        }                                                                      									\
    }

#define GET_DEVICE_PROC_ADDR(dev, entrypoint)																	\
    {																											\
        fp##entrypoint = (PFN_vk##entrypoint)vkGetDeviceProcAddr(dev, "vk" #entrypoint);				\
        if (fp##entrypoint == NULL) {																	\
            ERR_EXIT("vkGetDeviceProcAddr failed to find vk" #entrypoint, "vkGetDeviceProcAddr Failure");		\
        }																										\
    }

using std::array;
using std::iterator;
using std::map;
using std::stack;
using std::string;
using std::to_string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using tdme::engine::subsystems::renderer::VKRenderer;
using tdme::application::Application;
using tdme::engine::Engine;
using tdme::engine::Timing;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::subsystems::manager::TextureManager;

using tdme::engine::Engine;
using tdme::engine::fileio::textures::Texture;
using tdme::math::Matrix4x4;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::os::threading::ReadWriteLock;
using tdme::os::threading::Mutex;
using tdme::utils::ByteBuffer;
using tdme::utils::Buffer;
using tdme::utils::Console;
using tdme::utils::FloatBuffer;
using tdme::utils::Integer;
using tdme::utils::IntBuffer;
using tdme::utils::ShortBuffer;
using tdme::utils::StringTokenizer;
using tdme::utils::StringUtils;

VKRenderer::VKRenderer():
	buffers_rwlock("buffers_rwlock"),
	textures_rwlock("textures_rwlock"),
	draw_cmd_mutex("draw_cmd_mutex"),
	setup_cmd_mutex("setup_cmd_mutex")
{
	// setup consts
	ID_NONE = 0;
	CLEAR_DEPTH_BUFFER_BIT = 2;
	CLEAR_COLOR_BUFFER_BIT = 1;
	CULLFACE_FRONT = VK_CULL_MODE_FRONT_BIT;
	CULLFACE_BACK = VK_CULL_MODE_BACK_BIT;
	FRONTFACE_CW = VK_FRONT_FACE_CLOCKWISE;
	FRONTFACE_CCW = VK_FRONT_FACE_COUNTER_CLOCKWISE;
	SHADER_FRAGMENT_SHADER = VK_SHADER_STAGE_FRAGMENT_BIT;
	SHADER_VERTEX_SHADER = VK_SHADER_STAGE_VERTEX_BIT;
	SHADER_COMPUTE_SHADER = VK_SHADER_STAGE_COMPUTE_BIT;
	SHADER_GEOMETRY_SHADER = VK_SHADER_STAGE_GEOMETRY_BIT;
	DEPTHFUNCTION_ALWAYS = VK_COMPARE_OP_ALWAYS;
	DEPTHFUNCTION_EQUAL = VK_COMPARE_OP_EQUAL;
	DEPTHFUNCTION_LESSEQUAL = VK_COMPARE_OP_LESS_OR_EQUAL;
	DEPTHFUNCTION_GREATEREQUAL = VK_COMPARE_OP_GREATER_OR_EQUAL;
	FRAMEBUFFER_DEFAULT = 0;
	for (auto i = 0; i < contexts.size(); i++) contexts[i].idx = i;
}

inline bool VKRenderer::memoryTypeFromProperties(uint32_t typeBits, VkFlags requirements_mask, uint32_t *typeIndex) {
    uint32_t i;
    // Search memtypes to find first index with those properties
    for (i = 0; i < VK_MAX_MEMORY_TYPES; i++) {
        if ((typeBits & 1) == 1) {
            // Type is available, does it match user properties?
            if ((memory_properties.memoryTypes[i].propertyFlags & requirements_mask) == requirements_mask) {
                *typeIndex = i;
                return true;
            }
        }
        typeBits >>= 1;
    }
    // No memory types matched, return failure
    return false;
}

inline VkBool32 VKRenderer::checkLayers(uint32_t check_count, const char **check_names, uint32_t layer_count, VkLayerProperties *layers) {
	uint32_t i, j;
	for (i = 0; i < check_count; i++) {
		VkBool32 found = 0;
		for (j = 0; j < layer_count; j++) {
			if (!strcmp(check_names[i], layers[j].layerName)) {
				found = 1;
				break;
			}
		}
		if (!found) {
			fprintf(stderr, "Cannot find layer: %s\n", check_names[i]);
			return 0;
		}
	}
	return 1;
}

void VKRenderer::prepareSetupCommandBuffer() {
	setup_cmd_mutex.lock();
	if (setup_cmd == VK_NULL_HANDLE) {
		VkResult err;

		const VkCommandBufferAllocateInfo cmd = {
			.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
			.pNext = NULL,
			.commandPool = cmd_pool,
			.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
			.commandBufferCount = 1
		};

		err = vkAllocateCommandBuffers(device, &cmd, &setup_cmd);
		assert(!err);

		VkCommandBufferBeginInfo cmd_buf_info = {
			.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
			.pNext = NULL,
			.flags = 0,
			.pInheritanceInfo = NULL
		};
		err = vkBeginCommandBuffer(setup_cmd, &cmd_buf_info);
		assert(!err);
	}
	setup_cmd_mutex.unlock();
}

void VKRenderer::finishSetupCommandBuffer() {
	setup_cmd_mutex.lock();
	//
	if (setup_cmd != VK_NULL_HANDLE) {
		VkResult err;

		err = vkEndCommandBuffer(setup_cmd);
		assert(!err);

		const VkCommandBuffer cmd_bufs[] = { setup_cmd };
		VkFence nullFence = { VK_NULL_HANDLE };
		VkSubmitInfo submit_info = {
			.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
			.pNext = NULL,
			.waitSemaphoreCount = 0,
			.pWaitSemaphores = NULL,
			.pWaitDstStageMask = NULL,
			.commandBufferCount = 1,
			.pCommandBuffers = cmd_bufs,
			.signalSemaphoreCount = 0,
			.pSignalSemaphores = NULL
		};

		err = vkQueueSubmit(queue, 1, &submit_info, nullFence);
		assert(!err);

		err = vkQueueWaitIdle(queue);
		assert(!err);

		vkFreeCommandBuffers(device, cmd_pool, 1, cmd_bufs);

		//
		setup_cmd = VK_NULL_HANDLE;
	}
	setup_cmd_mutex.unlock();
}

inline void VKRenderer::setImageLayout(VkImage image, VkImageAspectFlags aspectMask, VkImageLayout old_image_layout, VkImageLayout new_image_layout, VkAccessFlagBits srcAccessMask) {
	VkResult err;

	//
	prepareSetupCommandBuffer();

	VkImageMemoryBarrier image_memory_barrier = {
		.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
		.pNext = NULL,
		.srcAccessMask = srcAccessMask,
		.dstAccessMask = 0,
		.oldLayout = old_image_layout,
		.newLayout = new_image_layout,
	    .srcQueueFamilyIndex = 0,
	    .dstQueueFamilyIndex = 0,
		.image = image,
		.subresourceRange = {
			.aspectMask = aspectMask,
			.baseMipLevel = 0,
			.levelCount = 1,
			.baseArrayLayer = 0,
			.layerCount = 1
		}
	};

	if (new_image_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
		image_memory_barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
	}
	if (new_image_layout == VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL) {
		image_memory_barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	}
	if (new_image_layout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) {
		image_memory_barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
	}
	if (new_image_layout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
		image_memory_barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_INPUT_ATTACHMENT_READ_BIT;
	}
	if (new_image_layout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL) {
		image_memory_barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_INPUT_ATTACHMENT_READ_BIT;
	}

	//
	vkCmdPipelineBarrier(setup_cmd, VK_PIPELINE_STAGE_HOST_BIT | VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, 0, 0, NULL, 0, NULL, 1, &image_memory_barrier);
}

inline void VKRenderer::prepareTextureImage(struct texture_object *tex_obj, VkImageTiling tiling, VkImageUsageFlags usage, VkFlags required_props, Texture* texture, VkImageLayout image_layout) {
	const VkFormat tex_format = texture->getHeight() == 32?VK_FORMAT_R8G8B8A8_UNORM:VK_FORMAT_R8G8B8A8_UNORM;
	VkResult err;
	bool pass;

	auto textureWidth = static_cast<uint32_t>(texture->getTextureWidth());
	auto textureHeight = static_cast<uint32_t>(texture->getTextureHeight());

	const VkImageCreateInfo image_create_info = {
		.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.imageType = VK_IMAGE_TYPE_2D,
		.format = tex_format,
		.extent = {
			.width = textureWidth,
			.height = textureHeight,
			.depth = 1
		},
		.mipLevels =1,
		.arrayLayers = 1,
		.samples = VK_SAMPLE_COUNT_1_BIT,
		.tiling = tiling,
		.usage = usage,
		.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
	    .queueFamilyIndexCount = 0,
	    .pQueueFamilyIndices = 0,
		.initialLayout = VK_IMAGE_LAYOUT_PREINITIALIZED
	};
	VkMemoryAllocateInfo mem_alloc = {
		.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		.pNext = NULL,
		.allocationSize = 0,
		.memoryTypeIndex = 0
	};

	VkMemoryRequirements mem_reqs;

	err = vkCreateImage(device, &image_create_info, NULL, &tex_obj->image);
	assert(!err);

	vkGetImageMemoryRequirements(device, tex_obj->image, &mem_reqs);

	mem_alloc.allocationSize = mem_reqs.size;
	pass = memoryTypeFromProperties(mem_reqs.memoryTypeBits, required_props, &mem_alloc.memoryTypeIndex);
	assert(pass);

	// allocate memory
	err = vkAllocateMemory(device, &mem_alloc, NULL, &tex_obj->mem);
	assert(!err);

	// bind memory
	err = vkBindImageMemory(device, tex_obj->image, tex_obj->mem, 0);
	assert(!err);

	if ((required_props & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) == VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) {
		const VkImageSubresource subres = {
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
			.mipLevel = 0,
			.arrayLayer = 0,
		};
		VkSubresourceLayout layout;
		vkGetImageSubresourceLayout(device, tex_obj->image, &subres, &layout);

		void* data;
		err = vkMapMemory(device, tex_obj->mem, 0, mem_alloc.allocationSize, 0, &data);
		assert(!err);

		auto bytesPerPixel = texture->getDepth() / 8;
		auto textureBuffer = texture->getTextureData();
		for (auto y = 0; y < textureHeight; y++) {
			char* row = (char*)((char*)data + layout.offset + layout.rowPitch * y);
			for (auto x = 0; x < textureWidth; x++) {
				row[x * 4 + 0] = textureBuffer->get((y * textureWidth * bytesPerPixel) + (x * bytesPerPixel) + 0);
				row[x * 4 + 1] = textureBuffer->get((y * textureWidth * bytesPerPixel) + (x * bytesPerPixel) + 1);
				row[x * 4 + 2] = textureBuffer->get((y * textureWidth * bytesPerPixel) + (x * bytesPerPixel) + 2);
				row[x * 4 + 3] = bytesPerPixel == 4?textureBuffer->get((y * textureWidth * bytesPerPixel) + (x * bytesPerPixel) + 3):0xff;
			}
		}

		VkMappedMemoryRange mappedMemoryRange = {
			.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
			.pNext = NULL,
			.memory = tex_obj->mem,
			.offset = 0,
			.size = VK_WHOLE_SIZE
		};
		vkFlushMappedMemoryRanges(device, 1, &mappedMemoryRange);

		vkUnmapMemory(device, tex_obj->mem);
	}

	//
	tex_obj->image_layout = image_layout;
	tex_obj->type = texture_object::TYPE_TEXTURE;
	setImageLayout(
		tex_obj->image,
		VK_IMAGE_ASPECT_COLOR_BIT,
		VK_IMAGE_LAYOUT_PREINITIALIZED,
		tex_obj->image_layout,
		VK_ACCESS_HOST_WRITE_BIT
	);
}

void VKRenderer::shaderInitResources(TBuiltInResource &resources) {
    resources.maxLights = 32;
    resources.maxClipPlanes = 6;
    resources.maxTextureUnits = 32;
    resources.maxTextureCoords = 32;
    resources.maxVertexAttribs = 64;
    resources.maxVertexUniformComponents = 4096;
    resources.maxVaryingFloats = 64;
    resources.maxVertexTextureImageUnits = 32;
    resources.maxCombinedTextureImageUnits = 80;
    resources.maxTextureImageUnits = 32;
    resources.maxFragmentUniformComponents = 4096;
    resources.maxDrawBuffers = 32;
    resources.maxVertexUniformVectors = 128;
    resources.maxVaryingVectors = 8;
    resources.maxFragmentUniformVectors = 16;
    resources.maxVertexOutputVectors = 16;
    resources.maxFragmentInputVectors = 15;
    resources.minProgramTexelOffset = -8;
    resources.maxProgramTexelOffset = 7;
    resources.maxClipDistances = 8;
    resources.maxComputeWorkGroupCountX = 65535;
    resources.maxComputeWorkGroupCountY = 65535;
    resources.maxComputeWorkGroupCountZ = 65535;
    resources.maxComputeWorkGroupSizeX = 1024;
    resources.maxComputeWorkGroupSizeY = 1024;
    resources.maxComputeWorkGroupSizeZ = 64;
    resources.maxComputeUniformComponents = 1024;
    resources.maxComputeTextureImageUnits = 16;
    resources.maxComputeImageUniforms = 8;
    resources.maxComputeAtomicCounters = 8;
    resources.maxComputeAtomicCounterBuffers = 1;
    resources.maxVaryingComponents = 60;
    resources.maxVertexOutputComponents = 64;
    resources.maxGeometryInputComponents = 64;
    resources.maxGeometryOutputComponents = 128;
    resources.maxFragmentInputComponents = 128;
    resources.maxImageUnits = 8;
    resources.maxCombinedImageUnitsAndFragmentOutputs = 8;
    resources.maxCombinedShaderOutputResources = 8;
    resources.maxImageSamples = 0;
    resources.maxVertexImageUniforms = 0;
    resources.maxTessControlImageUniforms = 0;
    resources.maxTessEvaluationImageUniforms = 0;
    resources.maxGeometryImageUniforms = 0;
    resources.maxFragmentImageUniforms = 8;
    resources.maxCombinedImageUniforms = 8;
    resources.maxGeometryTextureImageUnits = 16;
    resources.maxGeometryOutputVertices = 256;
    resources.maxGeometryTotalOutputComponents = 1024;
    resources.maxGeometryUniformComponents = 1024;
    resources.maxGeometryVaryingComponents = 64;
    resources.maxTessControlInputComponents = 128;
    resources.maxTessControlOutputComponents = 128;
    resources.maxTessControlTextureImageUnits = 16;
    resources.maxTessControlUniformComponents = 1024;
    resources.maxTessControlTotalOutputComponents = 4096;
    resources.maxTessEvaluationInputComponents = 128;
    resources.maxTessEvaluationOutputComponents = 128;
    resources.maxTessEvaluationTextureImageUnits = 16;
    resources.maxTessEvaluationUniformComponents = 1024;
    resources.maxTessPatchComponents = 120;
    resources.maxPatchVertices = 32;
    resources.maxTessGenLevel = 64;
    resources.maxViewports = 16;
    resources.maxVertexAtomicCounters = 0;
    resources.maxTessControlAtomicCounters = 0;
    resources.maxTessEvaluationAtomicCounters = 0;
    resources.maxGeometryAtomicCounters = 0;
    resources.maxFragmentAtomicCounters = 8;
    resources.maxCombinedAtomicCounters = 8;
    resources.maxAtomicCounterBindings = 1;
    resources.maxVertexAtomicCounterBuffers = 0;
    resources.maxTessControlAtomicCounterBuffers = 0;
    resources.maxTessEvaluationAtomicCounterBuffers = 0;
    resources.maxGeometryAtomicCounterBuffers = 0;
    resources.maxFragmentAtomicCounterBuffers = 1;
    resources.maxCombinedAtomicCounterBuffers = 1;
    resources.maxAtomicCounterBufferSize = 16384;
    resources.maxTransformFeedbackBuffers = 4;
    resources.maxTransformFeedbackInterleavedComponents = 64;
    resources.maxCullDistances = 8;
    resources.maxCombinedClipAndCullDistances = 8;
    resources.maxSamples = 4;
    resources.maxMeshOutputVerticesNV = 256;
    resources.maxMeshOutputPrimitivesNV = 512;
    resources.maxMeshWorkGroupSizeX_NV = 32;
    resources.maxMeshWorkGroupSizeY_NV = 1;
    resources.maxMeshWorkGroupSizeZ_NV = 1;
    resources.maxTaskWorkGroupSizeX_NV = 32;
    resources.maxTaskWorkGroupSizeY_NV = 1;
    resources.maxTaskWorkGroupSizeZ_NV = 1;
    resources.maxMeshViewCountNV = 4;
    resources.limits.nonInductiveForLoops = 1;
    resources.limits.whileLoops = 1;
    resources.limits.doWhileLoops = 1;
    resources.limits.generalUniformIndexing = 1;
    resources.limits.generalAttributeMatrixVectorIndexing = 1;
    resources.limits.generalVaryingIndexing = 1;
    resources.limits.generalSamplerIndexing = 1;
    resources.limits.generalVariableIndexing = 1;
    resources.limits.generalConstantMatrixVectorIndexing = 1;
}

EShLanguage VKRenderer::shaderFindLanguage(const VkShaderStageFlagBits shaderType) {
    switch (shaderType) {
        case VK_SHADER_STAGE_VERTEX_BIT:
            return EShLangVertex;
        case VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT:
            return EShLangTessControl;
        case VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT:
            return EShLangTessEvaluation;
        case VK_SHADER_STAGE_GEOMETRY_BIT:
            return EShLangGeometry;
        case VK_SHADER_STAGE_FRAGMENT_BIT:
            return EShLangFragment;
        case VK_SHADER_STAGE_COMPUTE_BIT:
            return EShLangCompute;
        default:
            return EShLangVertex;
    }
}

void VKRenderer::initializeSwapChain() {

	VkResult err;
	VkSwapchainKHR oldSwapchain = swapchain;

	// Check the surface capabilities and formats
	VkSurfaceCapabilitiesKHR surfCapabilities;
	err = fpGetPhysicalDeviceSurfaceCapabilitiesKHR(gpu, surface, &surfCapabilities);
	assert(err == VK_SUCCESS);

	uint32_t presentModeCount;
	err = fpGetPhysicalDeviceSurfacePresentModesKHR(gpu, surface, &presentModeCount, NULL);
	assert(err == VK_SUCCESS);
	VkPresentModeKHR *presentModes = (VkPresentModeKHR *) malloc(presentModeCount * sizeof(VkPresentModeKHR));
	assert(presentModes);
	err = fpGetPhysicalDeviceSurfacePresentModesKHR(gpu, surface, &presentModeCount, presentModes);
	assert(err == VK_SUCCESS);

	VkExtent2D swapchainExtent;
	// width and height are either both 0xFFFFFFFF, or both not 0xFFFFFFFF.
	if (surfCapabilities.currentExtent.width == 0xFFFFFFFF) {
		// If the surface size is undefined, the size is set to the size
		// of the images requested, which must fit within the minimum and
		// maximum values.
		swapchainExtent.width = width;
		swapchainExtent.height = height;

		if (swapchainExtent.width < surfCapabilities.minImageExtent.width) {
			swapchainExtent.width = surfCapabilities.minImageExtent.width;
		} else if (swapchainExtent.width > surfCapabilities.maxImageExtent.width) {
			swapchainExtent.width = surfCapabilities.maxImageExtent.width;
		}

		if (swapchainExtent.height < surfCapabilities.minImageExtent.height) {
			swapchainExtent.height = surfCapabilities.minImageExtent.height;
		} else if (swapchainExtent.height > surfCapabilities.maxImageExtent.height) {
			swapchainExtent.height = surfCapabilities.maxImageExtent.height;
		}
	} else {
		// If the surface size is defined, the swap chain size must match
		swapchainExtent = surfCapabilities.currentExtent;
		width = surfCapabilities.currentExtent.width;
		height = surfCapabilities.currentExtent.height;
	}

	VkPresentModeKHR swapchainPresentMode = VK_PRESENT_MODE_FIFO_KHR;

	// Determine the number of VkImage's to use in the swap chain.
	// Application desires to only acquire 1 image at a time (which is
	// "surfCapabilities.minImageCount").
	uint32_t desiredNumOfSwapchainImages = surfCapabilities.minImageCount;
	// If maxImageCount is 0, we can ask for as many images as we want;
	// otherwise we're limited to maxImageCount
	if ((surfCapabilities.maxImageCount > 0) && (desiredNumOfSwapchainImages > surfCapabilities.maxImageCount)) {
		// Application must settle for fewer images than desired:
		desiredNumOfSwapchainImages = surfCapabilities.maxImageCount;
	}

	VkSurfaceTransformFlagsKHR preTransform;
	if (surfCapabilities.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR) {
		preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
	} else {
		preTransform = surfCapabilities.currentTransform;
	}

	const VkSwapchainCreateInfoKHR swapchainCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		.pNext = NULL,
		.flags = 0,
		.surface = surface,
		.minImageCount = desiredNumOfSwapchainImages,
		.imageFormat = format,
		.imageColorSpace = color_space,
		.imageExtent = {
			.width = swapchainExtent.width,
			.height = swapchainExtent.height
		},
		.imageArrayLayers = 1,
		.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
		.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
		.queueFamilyIndexCount = 0,
		.pQueueFamilyIndices = 0,
		.preTransform = (VkSurfaceTransformFlagBitsKHR)preTransform, /// TODO = a.drewke, ???
		.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		.presentMode = swapchainPresentMode,
		.clipped = true,
		.oldSwapchain = oldSwapchain,
	};
	uint32_t i;

	err = fpCreateSwapchainKHR(device, &swapchainCreateInfo, NULL, &swapchain);
	assert(!err);

	// If we just re-created an existing swapchain, we should destroy the old
	// swapchain at this point.
	// Note: destroying the swapchain also cleans up all its associated
	// presentable images once the platform is done with them.
	if (oldSwapchain != VK_NULL_HANDLE) {
		fpDestroySwapchainKHR(device, oldSwapchain, NULL);
	}

	err = fpGetSwapchainImagesKHR(device, swapchain, &swapchain_image_count, NULL);
	assert(err == VK_SUCCESS);

	VkImage* swapchainImages = (VkImage*)malloc(swapchain_image_count * sizeof(VkImage));
	assert(swapchainImages != NULL);
	err = fpGetSwapchainImagesKHR(device, swapchain, &swapchain_image_count, swapchainImages);
	assert(err == VK_SUCCESS);

	swapchain_buffers = (swapchain_buffer_type*)malloc(sizeof(swapchain_buffer_type) * swapchain_image_count);
	assert(swapchain_buffers != NULL);

	for (i = 0; i < swapchain_image_count; i++) {
		VkImageViewCreateInfo color_attachment_view = {
			.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
			.pNext = NULL,
			.flags = 0,
			.image = swapchainImages[i],
			.viewType = VK_IMAGE_VIEW_TYPE_2D,
			.format = format,
			.components = {
				.r = VK_COMPONENT_SWIZZLE_R,
				.g = VK_COMPONENT_SWIZZLE_G,
				.b = VK_COMPONENT_SWIZZLE_B,
				.a = VK_COMPONENT_SWIZZLE_A
			},
			.subresourceRange = {
				.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
				.baseMipLevel = 0,
				.levelCount = 1,
				.baseArrayLayer = 0,
				.layerCount = 1
			}
		};
		swapchain_buffers[i].image = swapchainImages[i];
		err = vkCreateImageView(device, &color_attachment_view, NULL, &swapchain_buffers[i].view);
		assert(err == VK_SUCCESS);
	}

	current_buffer = 0;

	if (NULL != presentModes) free(presentModes);
}

const string VKRenderer::getShaderVersion()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return "gl3";
}

void* VKRenderer::getDefaultContext() {
	return &contexts[0];
}

void* VKRenderer::getContext(int contextIdx) {
	return &contexts[contextIdx];
}

bool VKRenderer::isSupportingMultithreadedRendering() {
	return true;
}

bool VKRenderer::isSupportingMultipleRenderQueues() {
	return false;
}

void VKRenderer::initialize()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");

	//
	glfwGetWindowSize(Application::glfwWindow, (int32_t*)&width, (int32_t*)&height);

	//
	glslang::InitProcess();
	glslang::InitThread();
	ShInitialize();

	VkResult err;
	uint32_t i = 0;
	uint32_t required_extension_count = 0;
	uint32_t instance_extension_count = 0;
	uint32_t instance_layer_count = 0;
	uint32_t validation_layer_count = 0;
	const char **required_extensions = NULL;
	const char **instance_validation_layers = NULL;

	uint32_t enabled_extension_count = 0;
	uint32_t enabled_layer_count = 0;
	const char *extension_names[64];
	const char *enabled_layers[64];

	char* instance_validation_layers_alt1[] = {
		"VK_LAYER_LUNARG_standard_validation"
	};
	char* instance_validation_layers_alt2[] = {
		"VK_LAYER_GOOGLE_threading",
		"VK_LAYER_LUNARG_parameter_validation",
		"VK_LAYER_LUNARG_object_tracker",
		"VK_LAYER_LUNARG_image",
		"VK_LAYER_LUNARG_core_validation",
		"VK_LAYER_LUNARG_swapchain",
		"VK_LAYER_GOOGLE_unique_objects"
	};

	// Look for validation layers
	if (validate == true) {
		VkBool32 validation_found = 0;
		err = vkEnumerateInstanceLayerProperties(&instance_layer_count, NULL);
		assert(!err);

		instance_validation_layers = (const char**) instance_validation_layers_alt1;
		if (instance_layer_count > 0) {
			VkLayerProperties* instance_layers = (VkLayerProperties*)malloc(sizeof(VkLayerProperties) * instance_layer_count);
			err = vkEnumerateInstanceLayerProperties(&instance_layer_count, instance_layers);
			assert(!err);

			validation_found = checkLayers(
				ARRAY_SIZE(instance_validation_layers_alt1),
				instance_validation_layers,
				instance_layer_count,
				instance_layers
			);
			if (validation_found) {
				enabled_layer_count = ARRAY_SIZE(instance_validation_layers_alt1);
				enabled_layers[0] = "VK_LAYER_LUNARG_standard_validation";
				validation_layer_count = 1;
			} else {
				// use alternative set of validation layers
				instance_validation_layers = (const char**) instance_validation_layers_alt2;
				enabled_layer_count = ARRAY_SIZE(instance_validation_layers_alt2);
				validation_found = checkLayers(
					ARRAY_SIZE(instance_validation_layers_alt2),
					instance_validation_layers,
					instance_layer_count,
					instance_layers
				);
				validation_layer_count = ARRAY_SIZE(instance_validation_layers_alt2);
				for (i = 0; i < validation_layer_count; i++) {
					enabled_layers[i] = instance_validation_layers[i];
				}
			}
			free(instance_layers);
		}

		if (!validation_found) {
			ERR_EXIT("vkEnumerateInstanceLayerProperties failed to find "
					"required validation layer.\n\n"
					"Please look at the Getting Started guide for additional "
					"information.\n", "vkCreateInstance Failure");
		}
	}

	// Look for instance extensions
	required_extensions = glfwGetRequiredInstanceExtensions(&required_extension_count);
	if (!required_extensions) {
		ERR_EXIT("glfwGetRequiredInstanceExtensions failed to find the "
			"platform surface extensions.\n\nDo you have a compatible "
			"Vulkan installable client driver (ICD) installed?\nPlease "
			"look at the Getting Started guide for additional "
			"information.\n", "vkCreateInstance Failure"
		);
	}

	for (i = 0; i < required_extension_count; i++) {
		extension_names[enabled_extension_count++] = required_extensions[i];
		assert(enabled_extension_count < 64);
	}

	err = vkEnumerateInstanceExtensionProperties(
	NULL, &instance_extension_count, NULL);
	assert(!err);

	if (instance_extension_count > 0) {
		VkExtensionProperties* instance_extensions = (VkExtensionProperties*)malloc(sizeof(VkExtensionProperties) * instance_extension_count);
		err = vkEnumerateInstanceExtensionProperties(NULL, &instance_extension_count, instance_extensions);
		assert(!err);
		for (i = 0; i < instance_extension_count; i++) {
			if (!strcmp(VK_EXT_DEBUG_REPORT_EXTENSION_NAME, instance_extensions[i].extensionName)) {
				if (validate == true) {
					extension_names[enabled_extension_count++] = VK_EXT_DEBUG_REPORT_EXTENSION_NAME;
				}
			}
			assert(enabled_extension_count < 64);
		}
		free(instance_extensions);
	}

	const VkApplicationInfo app = {
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pNext = NULL,
		.pApplicationName = "TDME2 based application",
		.applicationVersion = 0,
		.pEngineName = "TDME2",
		.engineVersion = 0,
		.apiVersion = VK_API_VERSION_1_0,
	};
	VkInstanceCreateInfo inst_info = {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.pApplicationInfo = &app,
		.enabledLayerCount = enabled_layer_count,
		.ppEnabledLayerNames = (const char * const *)instance_validation_layers,
		.enabledExtensionCount = enabled_extension_count,
		.ppEnabledExtensionNames = (const char * const *)extension_names,
	};
	uint32_t gpu_count;

	err = vkCreateInstance(&inst_info, NULL, &inst);
	if (err == VK_ERROR_INCOMPATIBLE_DRIVER) {
		ERR_EXIT("Cannot find a compatible Vulkan installable client driver "
				"(ICD).\n\nPlease look at the Getting Started guide for "
				"additional information.\n", "vkCreateInstance Failure");
	} else
	if (err == VK_ERROR_EXTENSION_NOT_PRESENT) {
		ERR_EXIT("Cannot find a specified extension library"
				".\nMake sure your layers path is set appropriately\n",
				"vkCreateInstance Failure");
	} else
	if (err) {
		ERR_EXIT("vkCreateInstance failed.\n\nDo you have a compatible Vulkan "
				"installable client driver (ICD) installed?\nPlease look at "
				"the Getting Started guide for additional information.\n",
				"vkCreateInstance Failure");
	}

	// Make initial call to query gpu_count, then second call for gpu info
	err = vkEnumeratePhysicalDevices(inst, &gpu_count, NULL);
	assert(!err && gpu_count > 0);

	if (gpu_count > 0) {
		VkPhysicalDevice* physical_devices = (VkPhysicalDevice*)malloc(sizeof(VkPhysicalDevice) * gpu_count);
		err = vkEnumeratePhysicalDevices(inst, &gpu_count, physical_devices);
		assert(!err);
		// For tri demo we just grab the first physical device
		gpu = physical_devices[0];
		free(physical_devices);
	} else {
		ERR_EXIT(
			"vkEnumeratePhysicalDevices reported zero accessible devices."
			"\n\nDo you have a compatible Vulkan installable client"
			" driver (ICD) installed?\nPlease look at the Getting Started"
			" guide for additional information.\n",
			"vkEnumeratePhysicalDevices Failure"
		);
	}

	// Look for device extensions
	uint32_t device_extension_count = 0;
	VkBool32 swapchainExtFound = 0;
	enabled_extension_count = 0;

	err = vkEnumerateDeviceExtensionProperties(gpu, NULL, &device_extension_count, NULL);
	assert(!err);

	if (device_extension_count > 0) {
		VkExtensionProperties* device_extensions = (VkExtensionProperties*)malloc(sizeof(VkExtensionProperties) * device_extension_count);
		err = vkEnumerateDeviceExtensionProperties(gpu, NULL, &device_extension_count, device_extensions);
		assert(!err);

		for (i = 0; i < device_extension_count; i++) {
			if (!strcmp(VK_KHR_SWAPCHAIN_EXTENSION_NAME, device_extensions[i].extensionName)) {
				swapchainExtFound = 1;
				extension_names[enabled_extension_count++] = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
			}
			assert(enabled_extension_count < 64);
		}

		free(device_extensions);
	}

	if (!swapchainExtFound) {
		ERR_EXIT(
			"vkEnumerateDeviceExtensionProperties failed to find "
			"the " VK_KHR_SWAPCHAIN_EXTENSION_NAME
			" extension.\n\nDo you have a compatible "
			"Vulkan installable client driver (ICD) installed?\nPlease "
			"look at the Getting Started guide for additional "
			"information.\n", "vkCreateInstance Failure"
		);
	}

	// Having these GIPA queries of device extension entry points both
	// BEFORE and AFTER vkCreateDevice is a good test for the loader
	GET_INSTANCE_PROC_ADDR(inst, GetPhysicalDeviceSurfaceCapabilitiesKHR);
	GET_INSTANCE_PROC_ADDR(inst, GetPhysicalDeviceSurfaceFormatsKHR);
	GET_INSTANCE_PROC_ADDR(inst, GetPhysicalDeviceSurfacePresentModesKHR);
	GET_INSTANCE_PROC_ADDR(inst, GetPhysicalDeviceSurfaceSupportKHR);

	vkGetPhysicalDeviceProperties(gpu, &gpu_props);

	// Query with NULL data to get count
	vkGetPhysicalDeviceQueueFamilyProperties(gpu, &queue_count, NULL);

	queue_props = (VkQueueFamilyProperties *) malloc(queue_count * sizeof(VkQueueFamilyProperties));
	vkGetPhysicalDeviceQueueFamilyProperties(gpu, &queue_count, queue_props);
	assert(queue_count >= 1);

	vkGetPhysicalDeviceFeatures(gpu, &gpu_features);

	// Create a WSI surface for the window:
	glfwCreateWindowSurface(inst, Application::glfwWindow, NULL, &surface);

	// Iterate over each queue to learn whether it supports presenting:
	VkBool32 *supportsPresent = (VkBool32 *) malloc(queue_count * sizeof(VkBool32));
	for (i = 0; i < queue_count; i++) {
		fpGetPhysicalDeviceSurfaceSupportKHR(gpu, i, surface, &supportsPresent[i]);
	}

	// Search for a graphics and a present queue in the array of queue
	// families, try to find one that supports both
	uint32_t graphicsQueueNodeIndex = UINT32_MAX;
	uint32_t presentQueueNodeIndex = UINT32_MAX;
	for (i = 0; i < queue_count; i++) {
		if ((queue_props[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0) {
			if (graphicsQueueNodeIndex == UINT32_MAX) {
				graphicsQueueNodeIndex = i;
			}

			if (supportsPresent[i] == VK_TRUE) {
				graphicsQueueNodeIndex = i;
				presentQueueNodeIndex = i;
				break;
			}
		}
	}
	if (presentQueueNodeIndex == UINT32_MAX) {
		// If didn't find a queue that supports both graphics and present, then
		// find a separate present queue.
		for (i = 0; i < queue_count; ++i) {
			if (supportsPresent[i] == VK_TRUE) {
				presentQueueNodeIndex = i;
				break;
			}
		}
	}
	free(supportsPresent);

	// Generate error if could not find both a graphics and a present queue
	if (graphicsQueueNodeIndex == UINT32_MAX || presentQueueNodeIndex == UINT32_MAX) {
		ERR_EXIT(
			"Could not find a graphics and a present queue\n",
			"Swapchain Initialization Failure"
		);
	}

	// TODO: Add support for separate queues, including presentation,
	//       synchronization, and appropriate tracking for QueueSubmit.
	// NOTE: While it is possible for an application to use a separate graphics
	//       and a present queues, this demo program assumes it is only using
	//       one:
	if (graphicsQueueNodeIndex != presentQueueNodeIndex) {
		ERR_EXIT(
			"Could not find a common graphics and a present queue\n",
			"Swapchain Initialization Failure"
		);
	}

	graphics_queue_node_index = graphicsQueueNodeIndex;

	// init_device
	float queue_priorities[1] = { 0.0 };
	const VkDeviceQueueCreateInfo queueCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.queueFamilyIndex = graphics_queue_node_index,
		.queueCount = 1,
		.pQueuePriorities = queue_priorities
	};

	VkPhysicalDeviceFeatures features;
	memset(&features, 0, sizeof(features));
	if (gpu_features.shaderClipDistance) {
		features.shaderClipDistance = VK_TRUE;
	}

	VkDeviceCreateInfo deviceCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.queueCreateInfoCount = 1,
		.pQueueCreateInfos = &queueCreateInfo,
		.enabledLayerCount = 0,
		.ppEnabledLayerNames = NULL,
		.enabledExtensionCount = enabled_extension_count,
		.ppEnabledExtensionNames = (const char * const *) extension_names,
		.pEnabledFeatures = &features
	};

	err = vkCreateDevice(gpu, &deviceCreateInfo, NULL, &device);
	assert(!err);

	GET_DEVICE_PROC_ADDR(device, CreateSwapchainKHR);
	GET_DEVICE_PROC_ADDR(device, DestroySwapchainKHR);
	GET_DEVICE_PROC_ADDR(device, GetSwapchainImagesKHR);
	GET_DEVICE_PROC_ADDR(device, AcquireNextImageKHR);
	GET_DEVICE_PROC_ADDR(device, QueuePresentKHR);

	vkGetDeviceQueue(device, graphics_queue_node_index, 0, &queue);

	// Get the list of VkFormat's that are supported:
	uint32_t formatCount;
	err = fpGetPhysicalDeviceSurfaceFormatsKHR(gpu, surface, &formatCount, NULL);
	assert(!err);
	VkSurfaceFormatKHR *surfFormats = (VkSurfaceFormatKHR *) malloc(formatCount * sizeof(VkSurfaceFormatKHR));
	err = fpGetPhysicalDeviceSurfaceFormatsKHR(gpu, surface, &formatCount, surfFormats);

	assert(!err);
	// If the format list includes just one entry of VK_FORMAT_UNDEFINED,
	// the surface has no preferred format.  Otherwise, at least one
	// supported format will be returned.
	if (formatCount == 1 && surfFormats[0].format == VK_FORMAT_UNDEFINED) {
		format = VK_FORMAT_B8G8R8A8_UNORM;
	} else {
		assert(formatCount >= 1);
		format = surfFormats[0].format;
	}
	color_space = surfFormats[0].colorSpace;

	// Get Memory information and properties
	vkGetPhysicalDeviceMemoryProperties(gpu, &memory_properties);

	// command pool
	const VkCommandPoolCreateInfo cmd_pool_info = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
		.pNext = NULL,
		.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
		.queueFamilyIndex = graphics_queue_node_index
	};
	err = vkCreateCommandPool(device, &cmd_pool_info, NULL, &cmd_pool);
	assert(!err);

	// draw command buffers
	const VkCommandBufferAllocateInfo cmd = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
		.pNext = NULL,
		.commandPool = cmd_pool,
		.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
		.commandBufferCount = 1
	};
	err = vkAllocateCommandBuffers(device, &cmd, &draw_cmd);
	assert(!err);

	// swap chain
	initializeSwapChain();

	// create descriptor pool
	const VkDescriptorPoolSize types_count[3] = {
		[0] = {
			.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
			.descriptorCount = 32 * 4 * DESC_MAX * CONTEXT_COUNT // 32 shader * 4 image sampler
		},
		[1] = {
			.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
			.descriptorCount = 32 * 4 * DESC_MAX * CONTEXT_COUNT // 32 shader * 4 uniform buffer
		},
		[2] = {
			.type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
			.descriptorCount = 32 * 10 * DESC_MAX * CONTEXT_COUNT // 32 shader * 10 storage buffer
		}
	};
	const VkDescriptorPoolCreateInfo descriptor_pool = {
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.maxSets = DESC_MAX * CONTEXT_COUNT * 32, // 32 shader
		.poolSizeCount = 3,
		.pPoolSizes = types_count,
	};

	err = vkCreateDescriptorPool(device, &descriptor_pool, NULL, &desc_pool);
	assert(!err);

	//
	initializeRenderPass();
	initializeFrameBuffers();

	//
	empty_vertex_buffer = createBufferObjects(1, true)[0];
	array<float, 16> bogusVertexBuffer = {{
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
	}};
	uploadBufferObjectInternal(empty_vertex_buffer, bogusVertexBuffer.size() * sizeof(float), (uint8_t*)bogusVertexBuffer.data(), (VkBufferUsageFlagBits)(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT));

	//
	white_texture_default = Engine::getInstance()->getTextureManager()->addTexture(TextureReader::read("resources/engine/textures", "transparent_pixel.png"));
}

void VKRenderer::initializeRenderPass() {
	VkResult err;

	//
	if (render_pass != VK_NULL_HANDLE) vkDestroyRenderPass(device, render_pass, NULL);

	// depth buffer
	if (depth_buffer_default != 0) disposeTexture(depth_buffer_default);
	depth_buffer_default = createDepthBufferTexture(width, height);

	// render pass
	const VkAttachmentDescription attachments[2] = {
		[0] = {
			.flags = 0,
			.format = format,
			.samples = VK_SAMPLE_COUNT_1_BIT,
			.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
			.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
			// TODO: a.drewke, was: VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, check me later, something with changing image layouts is wrong here sometimes
			.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
			.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
		},
		[1] = {
			.flags = 0,
			.format = VK_FORMAT_D32_SFLOAT,
			.samples = VK_SAMPLE_COUNT_1_BIT,
			.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
			.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
			.initialLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
			.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
		},
	};
	const VkAttachmentReference color_reference = {
		.attachment = 0,
		.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
	};
	const VkAttachmentReference depth_reference = {
		.attachment = 1,
		.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
	};
	const VkSubpassDescription subpass = {
		.flags = 0,
		.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
		.inputAttachmentCount = 0,
		.pInputAttachments = NULL,
		.colorAttachmentCount = 1,
		.pColorAttachments = &color_reference,
		.pResolveAttachments = NULL,
		.pDepthStencilAttachment = &depth_reference,
		.preserveAttachmentCount = 0,
		.pPreserveAttachments = NULL
	};
	const VkRenderPassCreateInfo rp_info = {
		.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.attachmentCount = 2,
		.pAttachments = attachments,
		.subpassCount = 1,
		.pSubpasses = &subpass,
		.dependencyCount = 0,
		.pDependencies = NULL
	};
	err = vkCreateRenderPass(device, &rp_info, NULL, &render_pass);
	assert(!err);
}

inline void VKRenderer::startRenderPass() {
	if (render_pass_started == true) return;
	render_pass_started = true;

	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + to_string(bound_frame_buffer));

	auto frameBuffer = window_framebuffers[current_buffer];
	auto renderPass = render_pass;
	if (bound_frame_buffer != 0) {
		auto frameBufferIt = framebuffers.find(bound_frame_buffer);
		if (frameBufferIt == framebuffers.end()) {
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): framebuffer not found: " + to_string(bound_frame_buffer));
		} else {
			frameBuffer = frameBufferIt->second.frame_buffer;
			renderPass = frameBufferIt->second.render_pass;
		}
	}

	const VkRenderPassBeginInfo rp_begin = {
		.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
		.pNext = NULL,
		.renderPass = renderPass,
		.framebuffer = frameBuffer,
		.renderArea = scissor,
		.clearValueCount = 0,
		.pClearValues = NULL
	};
	vkCmdBeginRenderPass(draw_cmd, &rp_begin, VK_SUBPASS_CONTENTS_INLINE);
}

inline void VKRenderer::endRenderPass() {
	if (render_pass_started == false) return;
	render_pass_started = false;
	vkCmdEndRenderPass(draw_cmd);
}

void VKRenderer::initializeFrameBuffers() {
	VkImageView attachments[2];
	auto depthBufferIt = textures.find(depth_buffer_default);
	assert(depthBufferIt != textures.end());
	attachments[1] = depthBufferIt->second.view;

	const VkFramebufferCreateInfo fb_info = {
		.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.renderPass = render_pass,
		.attachmentCount = 2,
		.pAttachments = attachments,
		.width = width,
		.height = height,
		.layers = 1
	};

	VkResult err;
	uint32_t i;

	window_framebuffers = (VkFramebuffer *) malloc(swapchain_image_count * sizeof(VkFramebuffer));
	assert(window_framebuffers);

	for (i = 0; i < swapchain_image_count; i++) {
		attachments[0] = swapchain_buffers[i].view;
		err = vkCreateFramebuffer(device, &fb_info, NULL, &window_framebuffers[i]);
		assert(!err);
	}
}

void VKRenderer::reshape() {
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");

	// new dimensions
	glfwGetWindowSize(Application::glfwWindow, (int32_t*)&width, (int32_t*)&height);

	//
	Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + to_string(width) + " x " + to_string(height));

	//
	auto frame_buffers_last = window_framebuffers;

	// reinit swapchain, renderpass and framebuffers
	initializeSwapChain();
	initializeRenderPass();
	initializeFrameBuffers();
	current_buffer = 0;

	// dispose old frame buffers
	for (auto i = 0; i < swapchain_image_count; i++) vkDestroyFramebuffer(device, frame_buffers_last[i], NULL);
	delete [] frame_buffers_last;

	//
	Engine::getInstance()->reshape(0, 0, width, height);
}

void VKRenderer::initializeFrame()
{
	//
	Renderer::initializeFrame();

	//
	VkResult err;
	VkSemaphoreCreateInfo semaphoreCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
		.pNext = NULL,
		.flags = 0
	};

	err = vkCreateSemaphore(device, &semaphoreCreateInfo, NULL, &image_acquired_semaphore);
	assert(!err);

	err = vkCreateSemaphore(device, &semaphoreCreateInfo, NULL, &draw_complete_semaphore);
	assert(!err);

	// get the index of the next available swapchain image:
	err = fpAcquireNextImageKHR(device, swapchain, UINT64_MAX, image_acquired_semaphore, (VkFence)0, &current_buffer);

	//
	if (err == VK_ERROR_OUT_OF_DATE_KHR) {
		// TODO: a.drewke
		//
		finishSetupCommandBuffer();
		endRenderPass();
		vkDestroySemaphore(device, image_acquired_semaphore, NULL);
		vkDestroySemaphore(device, draw_complete_semaphore, NULL);

		//
		reshape();

		// recreate semaphores
		err = vkCreateSemaphore(device, &semaphoreCreateInfo, NULL, &image_acquired_semaphore);
		assert(!err);

		err = vkCreateSemaphore(device, &semaphoreCreateInfo, NULL, &draw_complete_semaphore);
		assert(!err);
	} else
	if (err == VK_SUBOPTIMAL_KHR) {
		// demo->swapchain is not as optimal as it could be, but the platform's
		// presentation engine will still present the image correctly.
	} else {
		assert(!err);
	}

	const VkCommandBufferBeginInfo cmd_buf_info = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		.pNext = NULL,
		.flags = 0,
		.pInheritanceInfo = NULL
	};

	// start draw command buffer if required
	if (draw_cmd_started == false) {
		draw_cmd_started = true;
		err = vkBeginCommandBuffer(draw_cmd, &cmd_buf_info);
		assert(!err);
	}

	// We can use LAYOUT_UNDEFINED as a wildcard here because we don't care what
	// happens to the previous contents of the image
	VkImageMemoryBarrier image_memory_barrier = {
		.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
		.pNext = NULL,
		.srcAccessMask = 0,
		.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
		.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
		.newLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
		.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
		.image = swapchain_buffers[current_buffer].image,
		.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 }
	};

	vkCmdPipelineBarrier(draw_cmd, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, 0, 0, NULL, 0, NULL, 1, &image_memory_barrier);
}

void VKRenderer::finishFrame()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");

	//
	flushCommandsAllContexts();

	// flush command buffers
	if (program_id != 0) {
		finishPipeline();
		program_id = 0;
	}

	//
	memoryBarrier();

	//
	VkResult err;

	// end render pass
	endRenderPass();

	VkImageMemoryBarrier prePresentBarrier = {
		.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
		.pNext = NULL,
		.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
		.dstAccessMask = 0,
		.oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
		.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
		.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
		.image = swapchain_buffers[current_buffer].image,
		.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 }
	};
	vkCmdPipelineBarrier(draw_cmd, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, 0, 0, NULL, 0, NULL, 1, &prePresentBarrier);

	//
	if (draw_cmd_started == true) {
		draw_cmd_started = false;
		pipeline = VK_NULL_HANDLE;
		err = vkEndCommandBuffer(draw_cmd);
		assert(!err);
	}

	//
	VkFence nullFence = VK_NULL_HANDLE;
	VkPipelineStageFlags pipe_stage_flags = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
	VkSubmitInfo submit_info = {
		.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
		.pNext = NULL,
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = &image_acquired_semaphore,
		.pWaitDstStageMask = &pipe_stage_flags,
		.commandBufferCount = 1,
		.pCommandBuffers = &draw_cmd,
		.signalSemaphoreCount = 1,
		.pSignalSemaphores = &draw_complete_semaphore
	};

	err = vkQueueSubmit(queue, 1, &submit_info, nullFence);
	assert(!err);

	VkPresentInfoKHR present = {
		.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
		.pNext = NULL,
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = &draw_complete_semaphore,
		.swapchainCount = 1,
		.pSwapchains = &swapchain,
		.pImageIndices = &current_buffer
	};

	err = fpQueuePresentKHR(queue, &present);
	auto needsReshape = false;
	if (err == VK_ERROR_OUT_OF_DATE_KHR) {
		needsReshape = true;
	} else
	if (err == VK_SUBOPTIMAL_KHR) {
		// swapchain is not as optimal as it could be, but the platform's
		// presentation engine will still present the image correctly.
		needsReshape = true;
	} else {
		assert(!err);
	}

	err = vkQueueWaitIdle(queue);
	assert(err == VK_SUCCESS);

	vkDestroySemaphore(device, image_acquired_semaphore, NULL);
	vkDestroySemaphore(device, draw_complete_semaphore, NULL);

	//
	vkDeviceWaitIdle(device);

	// remove marked vulkan resources
	for (auto buf: delete_buffers) vkDestroyBuffer(device, buf, NULL);
	for (auto mem: delete_memory) vkFreeMemory(device, mem, NULL);
	for (auto image: delete_images) vkDestroyImage(device, image, NULL);
	delete_buffers.clear();
	delete_memory.clear();
	delete_images.clear();

	// reset desc index
	for (auto& programIt: programs) {
		programIt.second.desc_idxs.fill(0);
	}

	// work around for AMD drivers not telling if window needs to be reshaped
	if (needsReshape == false) {
		int32_t currentWidth;
		int32_t currentHeight;
		glfwGetWindowSize(Application::glfwWindow, &currentWidth, &currentHeight);
		needsReshape = currentWidth != width || currentHeight != height;
	}
	if (needsReshape == true) reshape();

	//
	frame++;
}

bool VKRenderer::isBufferObjectsAvailable()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return true;
}

bool VKRenderer::isDepthTextureAvailable()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return true;
}

bool VKRenderer::isUsingProgramAttributeLocation()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return false;
}

bool VKRenderer::isSpecularMappingAvailable()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return true;
}

bool VKRenderer::isNormalMappingAvailable()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return true;
}

bool VKRenderer::isDisplacementMappingAvailable()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return false;
}

bool VKRenderer::isInstancedRenderingAvailable() {
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return true;
}

bool VKRenderer::isUsingShortIndices() {
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return false;
}

bool VKRenderer::isGeometryShaderAvailable() {
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return false;
}

int32_t VKRenderer::getTextureUnits()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return activeTextureUnit;
}

int VKRenderer::determineAlignment(const unordered_map<string, vector<string>>& structs, const vector<string>& uniforms) {
	StringTokenizer t;
	auto alignmentMax = 0;
	for (auto uniform: uniforms) {
		t.tokenize(uniform, "\t ;");
		string uniformType;
		string uniformName;
		auto isArray = false;
		auto arraySize = 1;
		if (t.hasMoreTokens() == true) uniformType = t.nextToken();
		while (t.hasMoreTokens() == true) uniformName = t.nextToken();
		if (uniformName.find('[') != -1 && uniformName.find(']') != -1) {
			uniformName = StringUtils::substring(uniformName, 0, uniformName.find('['));
		}
		if (uniformType == "int") {
			uint32_t size = sizeof(int32_t);
			alignmentMax = Math::max(alignmentMax, size);
		} else
		if (uniformType == "float") {
			uint32_t size = sizeof(float);
			alignmentMax = Math::max(alignmentMax, size);
		} else
		if (uniformType == "vec3") {
			uint32_t size = sizeof(float) * 3;
			alignmentMax = Math::max(alignmentMax, size);
		} else
		if (uniformType == "vec4") {
			uint32_t size = sizeof(float) * 4;
			alignmentMax = Math::max(alignmentMax, size);
		} else
		if (uniformType == "mat3") {
			uint32_t size = sizeof(float) * 3;
			alignmentMax = Math::max(alignmentMax, size);
		} else
		if (uniformType == "mat4") {
			uint32_t size = sizeof(float) * 4;
			alignmentMax = Math::max(alignmentMax, size);
		} else
		if (uniformType == "sampler2D") {
			// no op
		} else {
			if (structs.find(uniformType) != structs.end()) {
				uint32_t size = determineAlignment(structs, structs.find(uniformType)->second);
				alignmentMax = Math::max(alignmentMax, size);
			} else {
				return false;
			}
		}
	}
	return alignmentMax;
}

int VKRenderer::align(int alignment, int offset) {
	auto alignRemainder = offset % alignment;
	return alignRemainder == 0?offset:offset + (alignment - alignRemainder);
}

bool VKRenderer::addToShaderUniformBufferObject(shader_type& shader, const unordered_map<string, string>& definitionValues, const unordered_map<string, vector<string>>& structs, const vector<string>& uniforms, const string& prefix, unordered_set<string>& uniformArrays, string& uniformsBlock) {
	StringTokenizer t;
	for (auto uniform: uniforms) {
		t.tokenize(uniform, "\t ;");
		string uniformType;
		string uniformName;
		auto isArray = false;
		auto arraySize = 1;
		if (t.hasMoreTokens() == true) uniformType = t.nextToken();
		while (t.hasMoreTokens() == true) uniformName = t.nextToken();
		if (uniformName.find('[') != -1 && uniformName.find(']') != -1) {
			isArray = true;
			auto arraySizeString = StringUtils::substring(uniformName, uniformName.find('[') + 1, uniformName.find(']'));
			for (auto definitionValueIt: definitionValues) arraySizeString = StringUtils::replace(arraySizeString, definitionValueIt.first, definitionValueIt.second);
			arraySize = Integer::parseInt(arraySizeString);
			uniformName = StringUtils::substring(uniformName, 0, uniformName.find('['));
			uniformArrays.insert(uniformName);
		}
		if (uniformType == "int") {
			for (auto i = 0; i < arraySize; i++) {
				auto suffix = isArray == true?"[" + to_string(i) + "]":"";
				uint32_t size = sizeof(int32_t);
				auto position = align(size, shader.ubo_size);
				shader.uniforms[prefix + uniformName + suffix] = {.name = prefix + uniformName + suffix, .type = shader_type::uniform_type::UNIFORM, .position = position, .size = size, .texture_unit = -1};
				shader.ubo_size = position + size;
			}
		} else
		if (uniformType == "float") {
			for (auto i = 0; i < arraySize; i++) {
				auto suffix = isArray == true?"[" + to_string(i) + "]":"";
				uint32_t size = sizeof(float);
				auto position = align(size, shader.ubo_size);
				shader.uniforms[prefix + uniformName + suffix] = {.name = prefix + uniformName + suffix, .type = shader_type::uniform_type::UNIFORM, .position = position, .size = size, .texture_unit = -1};
				shader.ubo_size = position + size;
			}
		} else
		if (uniformType == "vec3") {
			for (auto i = 0; i < arraySize; i++) {
				auto suffix = isArray == true?"[" + to_string(i) + "]":"";
				uint32_t size = sizeof(float) * 3;
				auto position = align(sizeof(float) * 4, shader.ubo_size);
				shader.uniforms[prefix + uniformName + suffix] = {.name = prefix + uniformName + suffix, .type = shader_type::uniform_type::UNIFORM, .position = position, .size = size, .texture_unit = -1};
				shader.ubo_size = position + size;
			}
		} else
		if (uniformType == "vec4") {
			for (auto i = 0; i < arraySize; i++) {
				auto suffix = isArray == true?"[" + to_string(i) + "]":"";
				uint32_t size = sizeof(float) * 4;
				auto position = align(size, shader.ubo_size);
				shader.uniforms[prefix + uniformName + suffix] = {.name = prefix + uniformName + suffix, .type = shader_type::uniform_type::UNIFORM, .position = position, .size = size, .texture_unit = -1};
				shader.ubo_size = position + size;
			}
		} else
		if (uniformType == "mat3") {
			for (auto i = 0; i < arraySize; i++) {
				auto suffix = isArray == true?"[" + to_string(i) + "]":"";
				uint32_t size = sizeof(float) * 12;
				auto position = align(sizeof(float) * 4, shader.ubo_size);
				shader.uniforms[prefix + uniformName + suffix] = {.name = prefix + uniformName + suffix, .type = shader_type::uniform_type::UNIFORM, .position = position, .size = size, .texture_unit = -1};
				shader.ubo_size = position + size;
			}
		} else
		if (uniformType == "mat4") {
			for (auto i = 0; i < arraySize; i++) {
				auto suffix = isArray == true?"[" + to_string(i) + "]":"";
				uint32_t size = sizeof(float) * 16;
				auto position = align(sizeof(float) * 4, shader.ubo_size);
				shader.uniforms[prefix + uniformName + suffix] = {.name = prefix + uniformName + suffix, .type = shader_type::uniform_type::UNIFORM, .position = position, .size = size, .texture_unit = -1};
				shader.ubo_size = position + size;
			}
		} else
		if (uniformType == "sampler2D") {
			shader.uniforms[uniformName] = {.name = uniformName, .type = shader_type::uniform_type::SAMPLER2D, .position = -1, .size = 0, .texture_unit = -1};
			continue;
		} else {
			if (structs.find(uniformType) != structs.end()) {
				for (auto i = 0; i < arraySize; i++) {
					auto structPrefix = prefix + uniformName + (isArray == true?"[" + to_string(i) + "]":"") + ".";
					string uniformsBlockIgnore;
					auto alignment = determineAlignment(structs, structs.find(uniformType)->second);
					shader.ubo_size = align(alignment, shader.ubo_size);
					auto success = addToShaderUniformBufferObject(shader, definitionValues, structs, structs.find(uniformType)->second, structPrefix, uniformArrays, uniformsBlockIgnore);
					shader.ubo_size = align(alignment, shader.ubo_size);
					if (success == false) return false;
				}
			} else {
				Console::println("VKRenderer::" + string(__FUNCTION__) + "(): Unknown uniform type: " + uniformType);
				shaders.erase(shader.id);
				return false;
			}
		}
		uniformsBlock+= uniform + "\n";
	}
	return true;
}

int32_t VKRenderer::loadShader(int32_t type, const string& pathName, const string& fileName, const string& definitions, const string& functions)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): INIT: " + pathName + "/" + fileName + ": " + definitions);

	auto& shaderStruct = shaders[shader_idx];
	shaderStruct.type = (VkShaderStageFlagBits)type;
	shaderStruct.id = shader_idx++;

	// shader source
	auto shaderSource = StringUtils::replace(
		StringUtils::replace(
			FileSystem::getInstance()->getContentAsString(pathName, fileName),
			"{$DEFINITIONS}",
			definitions
		),
		"{$FUNCTIONS}",
		functions
	);

	// do some shader adjustments
	{
		// pre parse shader code
		vector<string> newShaderSourceLines;
		vector<string> uniforms;
		shaderSource = StringUtils::replace(shaderSource, "\r", "");
		shaderSource = StringUtils::replace(shaderSource, "\t", " ");
		shaderSource = StringUtils::replace(shaderSource, "#version 330", "#version 430\n#extension GL_EXT_scalar_block_layout: require\n\n");
		shaderSource = StringUtils::replace(shaderSource, "#version 430 core", "#version 430\n#extension GL_EXT_scalar_block_layout: require\n\n");
		StringTokenizer t;
		t.tokenize(shaderSource, "\n");
		StringTokenizer t2;
		vector<string> definitions;
		unordered_map<string, string> definitionValues;
		unordered_map<string, vector<string>> structs;
		string currentStruct;
		stack<string> testedDefinitions;
		vector<bool> matchedDefinitions;
		auto inLocationCount = 0;
		auto outLocationCount = 0;
		auto uboUniformCount = 0;
		auto multiLineComment = false;
		while (t.hasMoreTokens() == true) {
			auto matchedAllDefinitions = true;
			for (auto matchedDefinition: matchedDefinitions) matchedAllDefinitions&= matchedDefinition;
			auto line = StringUtils::trim(t.nextToken());
			if (StringUtils::startsWith(line, "//") == true) continue;
			auto position = -1;
			if (StringUtils::startsWith(line, "/*") == true) {
				multiLineComment = true;
			} else
			if (multiLineComment == true) {
				if (StringUtils::endsWith(line, "*/") == true) multiLineComment = false;
			} else
			if (StringUtils::startsWith(line, "#if defined(") == true) {
				auto definition = StringUtils::trim(StringUtils::substring(line, string("#if defined(").size(), (position = line.find(")")) != -1?position:line.size()));
				if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): Have preprocessor test begin: " + definition);
				testedDefinitions.push(definition);
				bool matched = false;
				for (auto availableDefinition: definitions) {
					if (definition == availableDefinition) {
						matched = true;
						break;
					}
				}
				if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): Have preprocessor test begin: " + definition + ": " + to_string(matched));
				matchedDefinitions.push_back(matched);
				newShaderSourceLines.push_back("// " + line);
			} else
			if (StringUtils::startsWith(line, "#define ") == true) {
				auto definition = StringUtils::trim(StringUtils::substring(line, string("#define ").size()));
				if (definition.find(' ') != -1 || definition.find('\t') != -1) {
					t2.tokenize(definition, "\t ");
					definition = t2.nextToken();
					string value;
					while (t2.hasMoreTokens() == true) value+= t2.nextToken();
					definitionValues[definition] = value;
					newShaderSourceLines.push_back((matchedAllDefinitions == true?"":"// ") + line);
					if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): Have define with value: " + definition + " --> " + value);
				} else {
					definitions.push_back(definition);
					newShaderSourceLines.push_back((matchedAllDefinitions == true?"":"// ") + line);
					if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): Have define: " + definition);
				}
			} else
			if (StringUtils::startsWith(line, "#else") == true) {
				if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): Have preprocessor else: " + line);
				matchedDefinitions[matchedDefinitions.size() - 1] = !matchedDefinitions[matchedDefinitions.size() - 1];
				newShaderSourceLines.push_back("// " + line);
				matchedAllDefinitions = true;
				for (auto matchedDefinition: matchedDefinitions) matchedAllDefinitions&= matchedDefinition;
			} else
			if (StringUtils::startsWith(line, "#endif") == true) {
				if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): Have preprocessor test end: " + line);
				if (testedDefinitions.size() == 0) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): Have preprocessor test end: invalid depth"); else {
					testedDefinitions.pop();
					matchedDefinitions.pop_back();
				}
				newShaderSourceLines.push_back("// " + line);
			} else
			if (matchedAllDefinitions == true) {
				if (StringUtils::startsWith(line, "struct ") == true) {
					currentStruct = StringUtils::trim(StringUtils::substring(line, string("struct ").size(), line.find('{')));
				} else
				if (currentStruct.size() > 0) {
					if (line == "};") {
						currentStruct.clear();
					} else {
						structs[currentStruct].push_back(line);
					}
				} else
				if (currentStruct.size() > 0) {

				}
				if ((StringUtils::startsWith(line, "uniform ")) == true) {
					string uniform;
					if (line.find("sampler2D") != -1) {
						uniform = StringUtils::substring(line, string("uniform").size() + 1);
						t2.tokenize(uniform, "\t ;");
						string uniformType;
						string uniformName;
						if (t2.hasMoreTokens() == true) uniformType = t2.nextToken();
						while (t2.hasMoreTokens() == true) uniformName = t2.nextToken();
						newShaderSourceLines.push_back("layout(binding = {$SAMPLER2D_BINDING_" + uniformName + "_IDX}) " + line);
						shaderStruct.samplers++;
					} else {
						uniform = StringUtils::substring(line, string("uniform").size() + 1);
						uboUniformCount++;
					}
					uniforms.push_back(uniform);
					newShaderSourceLines.push_back("// " + line);
					if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): Have uniform: " + uniform);
				} else
				if (StringUtils::startsWith(line, "out ") == true) {
					newShaderSourceLines.push_back("layout (location = " + to_string(outLocationCount) + ") " + line);
					if (VERBOSE == true) Console::println("layout (location = " + to_string(outLocationCount) + ") " + line);
					outLocationCount++;
				} else
				if (StringUtils::startsWith(line, "in ") == true) {
					newShaderSourceLines.push_back("layout (location = " + to_string(inLocationCount) + ") " + line);
					if (VERBOSE == true) Console::println("layout (location = " + to_string(inLocationCount) + ") " + line);
					inLocationCount++;
				} else
				if (StringUtils::startsWith(line, "layout") == true && line.find("binding=") != -1) {
					if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): Have layout with binding: " + line);
					t2.tokenize(line, "(,)= \t");
					while (t2.hasMoreTokens() == true) {
						auto token = t2.nextToken();
						if (token == "binding" && t2.hasMoreTokens() == true) {
							auto nextToken = t2.nextToken();
							shaderStruct.binding_max = Math::max(Integer::parseInt(nextToken), shaderStruct.binding_max);
							break;
						}
					}
					newShaderSourceLines.push_back(line);
				} else {
					newShaderSourceLines.push_back(line);
				}
			} else {
				newShaderSourceLines.push_back("// " + line);
			}
		}

		// generate new uniform block
		unordered_set<string> uniformArrays;
		string uniformsBlock = "";

		// replace uniforms to use ubo
		if (uniforms.size() > 0) {
			if (uboUniformCount > 0) {
				uniformsBlock+= "layout(std430, column_major, binding={$UBO_BINDING_IDX}) uniform UniformBufferObject\n";
				uniformsBlock+= "{\n";
			}
			string uniformsBlockIgnore;
			addToShaderUniformBufferObject(shaderStruct, definitionValues, structs, uniforms, "", uniformArrays, uboUniformCount > 0?uniformsBlock:uniformsBlockIgnore);
			if (uboUniformCount > 0) uniformsBlock+= "} ubo_generated;\n";
			if (VERBOSE == true) Console::println("Shader UBO size: " + to_string(shaderStruct.ubo_size));
		}

		// construct new shader from vector and flip y, also inject uniforms
		shaderSource.clear();
		auto injectedUniformsAt = -1;
		auto injectedYFlip = false;
		// inject uniform before first method
		for (auto i = 0; i < newShaderSourceLines.size(); i++) {
			auto line = newShaderSourceLines[i];
			if (line.find('(') != -1 && line.find(')') != -1 && StringUtils::startsWith(line, "layout") == false && line.find("defined(") == -1 && line.find("#define") == -1) {
				injectedUniformsAt = i;
				break;
			}
		}
		for (int i = newShaderSourceLines.size() - 1; i >= 0; i--) {
			auto line = newShaderSourceLines[i] + "\n";
			if (i == injectedUniformsAt) {
				shaderSource = uniformsBlock + line + shaderSource;
			} else
			if (StringUtils::startsWith(line, "//") == true) {
				shaderSource = line + shaderSource;
				// rename uniforms to ubo uniforms
			} else {
				for (auto& uniformIt: shaderStruct.uniforms) {
					if (uniformIt.second.type == shader_type::uniform_type::SAMPLER2D) continue;
					auto uniformName = uniformIt.second.name;
					line = StringUtils::replaceAll(
						line,
						"(\\b)" + uniformName + "(\\b)",
						"$1ubo_generated." + uniformName + "$2"
					);
				}
				// rename arrays to ubo uniforms
				for (auto& uniformName: uniformArrays) {
					line = StringUtils::replaceAll(
						line,
						"(\\b)" + uniformName + "(\\b)",
						"$1ubo_generated." + uniformName + "$2"
					);
				}
				// inject gl_Position flip before last } from main
				if (type == SHADER_VERTEX_SHADER && injectedYFlip == false && StringUtils::startsWith(line, "}") == true) {
					shaderSource =
						"gl_Position.y*= -1.0;\n" +
						line +
						shaderSource;
					injectedYFlip = true;
				} else  {
					shaderSource = line + shaderSource;
				}
			}
		}

		// debug uniforms
		for (auto& uniformIt: shaderStruct.uniforms) {
			if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): Uniform: " + uniformIt.second.name + ": " + to_string(uniformIt.second.position) + " / " + to_string(uniformIt.second.size));
		}
	}

	shaderStruct.source = shaderSource;

    //
	return shaderStruct.id;
}

inline void VKRenderer::preparePipeline(program_type& program) {
	for (auto& context: contexts) {
		auto shaderIdx = 0;
		for (auto shaderId: program.shader_ids) {
			auto shaderIt = shaders.find(shaderId);
			if (shaderIt == shaders.end()) {
				Console::println("VKRenderer::" + string(__FUNCTION__) + "(): shader does not exist: " + to_string(shaderId));
				return;
			}
			auto& shader = shaderIt->second;
			if (shader.ubo_binding_idx == -1) {
				context.uniform_buffers[shaderIdx].resize(0);
				context.uniform_buffers_changed[shaderIdx] = false;
				shaderIdx++;
				continue;
			}
			context.uniform_buffers[shaderIdx].resize(shader.ubo_size);
			context.uniform_buffers_changed[shaderIdx] = true;
			shaderIdx++;
		}
		if (program.created == true) {
			context.uniform_buffers = program.uniform_buffers_last[context.idx];
			context.uniform_buffers_changed = program.uniform_buffers_changed_last[context.idx];
		}
	}
}

inline void VKRenderer::finishPipeline() {
	if (program_id != 0) {
		auto programIt = programs.find(program_id);
		if (programIt == programs.end()) {
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program does not exist: " + to_string(program_id));
			return;
		}
		auto& program = programIt->second;
		for (auto& context: contexts) {
			program.uniform_buffers_last[context.idx] = context.uniform_buffers;
			program.uniform_buffers_changed_last[context.idx] = context.uniform_buffers_changed;
		}
	}

	// clear ubos
	for (auto& context: contexts) {
		for (auto& ubo: context.uniform_buffers) ubo.clear();
	}

	//
	pipeline = VK_NULL_HANDLE;
}

inline void VKRenderer::createRasterizationStateCreateInfo(VkPipelineRasterizationStateCreateInfo& rs) {
	memset(&rs, 0, sizeof(rs));
	rs.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rs.polygonMode = VK_POLYGON_MODE_FILL;
	rs.cullMode = culling_enabled == true?cull_mode:VK_CULL_MODE_NONE;
	rs.frontFace = front_face;
	rs.depthClampEnable = VK_FALSE;
	rs.rasterizerDiscardEnable = VK_FALSE;
	rs.depthBiasEnable = VK_FALSE;
	rs.lineWidth = 1.0f;
}

inline void VKRenderer::createColorBlendAttachmentState(VkPipelineColorBlendAttachmentState& att_state) {
	memset(&att_state, 0, sizeof(att_state));
	att_state.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	att_state.blendEnable = blending_enabled = true?VK_TRUE:VK_FALSE;
	att_state.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
	att_state.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	att_state.colorBlendOp = VK_BLEND_OP_ADD;
	att_state.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
	att_state.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	att_state.alphaBlendOp = VK_BLEND_OP_ADD;
}

inline void VKRenderer::createDepthStencilStateCreateInfo(VkPipelineDepthStencilStateCreateInfo& ds) {
	memset(&ds, 0, sizeof(ds));
	ds.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	ds.depthTestEnable = depth_buffer_testing == true?VK_TRUE:VK_FALSE;
	ds.depthWriteEnable = depth_buffer_writing == true?VK_TRUE:VK_FALSE;
	ds.depthCompareOp = (VkCompareOp)depth_function;
	ds.depthBoundsTestEnable = VK_FALSE;
	ds.back.failOp = VK_STENCIL_OP_KEEP;
	ds.back.passOp = VK_STENCIL_OP_KEEP;
	ds.back.compareOp = VK_COMPARE_OP_ALWAYS;
	ds.stencilTestEnable = VK_FALSE;
	ds.front = ds.back;
}

inline const string VKRenderer::createPipelineId() {
	return
		to_string(culling_enabled) + "," +
		to_string(cull_mode) + "," +
		to_string(front_face) + "," +
		to_string(blending_enabled) + "," +
		to_string(depth_buffer_testing) + "," +
		to_string(depth_buffer_writing) + "," +
		to_string(depth_function) + "," +
		to_string(bound_frame_buffer);
}

void VKRenderer::createObjectsRenderingPipeline(program_type& program) {
	if (program.created == false) {
		VkResult err;

		//
		VkDescriptorSetLayoutBinding layout_bindings[program.layout_bindings];
		memset(layout_bindings, 0, sizeof(layout_bindings));

		// ubos, samplers
		auto shaderIdx = 0;
		for (auto shaderId: program.shader_ids) {
			auto shaderIt = shaders.find(shaderId);
			if (shaderIt == shaders.end()) {
				Console::println("VKRenderer::" + string(__FUNCTION__) + "(): shader does not exist: " + to_string(shaderId));
				return;
			}
			auto& shader = shaderIt->second;
			if (shader.ubo_binding_idx != -1) {
				layout_bindings[shader.ubo_binding_idx] = {
					.binding = static_cast<uint32_t>(shader.ubo_binding_idx),
					.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
					.descriptorCount = 1,
					.stageFlags = shader.type,
					.pImmutableSamplers = NULL
				};
			}
			for (auto uniformIt: shader.uniforms) {
				auto& uniform = uniformIt.second;
				if (uniform.type == shader_type::uniform_type::SAMPLER2D) {
					layout_bindings[uniform.position] = {
						.binding = static_cast<uint32_t>(uniform.position),
						.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
						.descriptorCount = 1,
						.stageFlags = shader.type,
						.pImmutableSamplers = NULL
					};
				}
			}
			shaderIdx++;
		}

		const VkDescriptorSetLayoutCreateInfo descriptor_layout = {
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
			.pNext = NULL,
			.flags = 0,
			.bindingCount = program.layout_bindings,
			.pBindings = layout_bindings,
		};

		err = vkCreateDescriptorSetLayout(device, &descriptor_layout, NULL, &program.desc_layout);
		assert(!err);

		const VkPipelineLayoutCreateInfo pPipelineLayoutCreateInfo = {
			.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
			.pNext = NULL,
			.flags = 0,
			.setLayoutCount = 1,
			.pSetLayouts = &program.desc_layout,
		};

		VkDescriptorSetLayout desc_layouts[DESC_MAX];
		for (auto i = 0; i < DESC_MAX; i++) desc_layouts[i] = program.desc_layout;

		//
		VkDescriptorSetAllocateInfo alloc_info = {
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
			.pNext = NULL,
			.descriptorPool = desc_pool,
			.descriptorSetCount = DESC_MAX,
			.pSetLayouts = desc_layouts
		};
		for (auto& context: contexts) {
			err = vkAllocateDescriptorSets(device, &alloc_info, program.desc_sets[context.idx]);
			assert(!err);
		}

		//
		err = vkCreatePipelineLayout(device, &pPipelineLayoutCreateInfo, NULL, &program.pipeline_layout);
		assert(!err);

		//
		for (auto& context: contexts) context.uniform_buffers_changed.fill(true);

		//
		program.created = true;
	}

	auto pipelineId = createPipelineId();
	auto pipelinesIt = program.pipelines.find(pipelineId);
	if (pipelinesIt == program.pipelines.end()) {
		auto& programPipeline = program.pipelines[pipelineId];

		VkRenderPass renderPass = render_pass;
		auto haveDepthBuffer = true;
		auto haveColorBuffer = true;
		if (bound_frame_buffer != 0) {
			auto frameBufferIt = framebuffers.find(bound_frame_buffer);
			auto& frameBufferStruct = frameBufferIt->second;
			haveDepthBuffer = frameBufferStruct.depth_texture_id != 0;
			haveColorBuffer = frameBufferStruct.color_texture_id != 0;
			renderPass = frameBufferStruct.render_pass;
		}

		//
		VkResult err;

		//
		VkGraphicsPipelineCreateInfo pipeline;
		memset(&pipeline, 0, sizeof(pipeline));

		// create pipepine
		VkPipelineCacheCreateInfo pipelineCache;

		VkPipelineVertexInputStateCreateInfo vi;
		VkPipelineInputAssemblyStateCreateInfo ia;
		VkPipelineRasterizationStateCreateInfo rs;
		VkPipelineColorBlendStateCreateInfo cb;
		VkPipelineDepthStencilStateCreateInfo ds;
		VkPipelineViewportStateCreateInfo vp;
		VkPipelineMultisampleStateCreateInfo ms;
		VkDynamicState dynamicStateEnables[VK_DYNAMIC_STATE_RANGE_SIZE];
		VkPipelineDynamicStateCreateInfo dynamicState;

		createRasterizationStateCreateInfo(rs);
		createDepthStencilStateCreateInfo(ds);

		VkPipelineShaderStageCreateInfo shaderStages[program.shader_ids.size()];
		memset(shaderStages, 0, program.shader_ids.size() * sizeof(VkPipelineShaderStageCreateInfo));

		// shader stages
		auto shaderIdx = 0;
		for (auto shaderId: program.shader_ids) {
			auto shaderIt = shaders.find(shaderId);
			if (shaderIt == shaders.end()) {
				Console::println("VKRenderer::" + string(__FUNCTION__) + "(): shader does not exist: " + to_string(shaderId));
				return;
			}
			auto& shader = shaderIt->second;
			shaderStages[shaderIdx].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			shaderStages[shaderIdx].stage = shader.type;
			shaderStages[shaderIdx].module = shader.module;
			shaderStages[shaderIdx].pName = "main";
			shaderIdx++;
		}

		memset(dynamicStateEnables, 0, sizeof dynamicStateEnables);
		memset(&dynamicState, 0, sizeof dynamicState);
		dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamicState.pDynamicStates = dynamicStateEnables;

		pipeline.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipeline.stageCount = program.shader_ids.size();
		pipeline.layout = program.pipeline_layout;

		memset(&ia, 0, sizeof(ia));
		ia.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		ia.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

		VkPipelineColorBlendAttachmentState att_state;
		createColorBlendAttachmentState(att_state);

		memset(&cb, 0, sizeof(cb));
		cb.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		cb.logicOpEnable = VK_FALSE;
		cb.attachmentCount = haveColorBuffer == true?1:0;
		cb.pAttachments = haveColorBuffer == true?&att_state:NULL;

		memset(&vp, 0, sizeof(vp));
		vp.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		vp.viewportCount = 1;
		dynamicStateEnables[dynamicState.dynamicStateCount++] = VK_DYNAMIC_STATE_VIEWPORT;
		vp.scissorCount = 1;
		dynamicStateEnables[dynamicState.dynamicStateCount++] = VK_DYNAMIC_STATE_SCISSOR;

		memset(&ms, 0, sizeof(ms));
		ms.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		ms.pSampleMask = NULL;
		ms.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

		VkVertexInputBindingDescription vi_bindings[9];
		memset(vi_bindings, 0, sizeof(vi_bindings));
		VkVertexInputAttributeDescription vi_attrs[12];
		memset(vi_attrs, 0, sizeof(vi_attrs));

		// vertices
		vi_bindings[0].binding = 0;
		vi_bindings[0].stride = sizeof(float) * 3;
		vi_bindings[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		vi_attrs[0].binding = 0;
		vi_attrs[0].location = 0;
		vi_attrs[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		vi_attrs[0].offset = 0;

		// normals
		vi_bindings[1].binding = 1;
		vi_bindings[1].stride = sizeof(float) * 3;
		vi_bindings[1].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		vi_attrs[1].binding = 1;
		vi_attrs[1].location = 1;
		vi_attrs[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		vi_attrs[1].offset = 0;

		// texture coordinates
		vi_bindings[2].binding = 2;
		vi_bindings[2].stride = sizeof(float) * 2;
		vi_bindings[2].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		vi_attrs[2].binding = 2;
		vi_attrs[2].location = 2;
		vi_attrs[2].format = VK_FORMAT_R32G32_SFLOAT;
		vi_attrs[2].offset = 0;

		// colors
		vi_bindings[3].binding = 3;
		vi_bindings[3].stride = sizeof(float) * 4;
		vi_bindings[3].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		vi_attrs[3].binding = 3;
		vi_attrs[3].location = 3;
		vi_attrs[3].format = VK_FORMAT_R32G32B32A32_SFLOAT;
		vi_attrs[3].offset = 0;

		// tangents
		vi_bindings[4].binding = 4;
		vi_bindings[4].stride = sizeof(float) * 3;
		vi_bindings[4].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		vi_attrs[4].binding = 4;
		vi_attrs[4].location = 4;
		vi_attrs[4].format = VK_FORMAT_R32G32B32_SFLOAT;
		vi_attrs[4].offset = 0;

		// bitangents
		vi_bindings[5].binding = 5;
		vi_bindings[5].stride = sizeof(float) * 3;
		vi_bindings[5].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		vi_attrs[5].binding = 5;
		vi_attrs[5].location = 5;
		vi_attrs[5].format = VK_FORMAT_R32G32B32_SFLOAT;
		vi_attrs[5].offset = 0;

		// model matrices 1
		vi_bindings[6].binding = 6;
		vi_bindings[6].stride = sizeof(float) * 4 * 4;
		vi_bindings[6].inputRate = VK_VERTEX_INPUT_RATE_INSTANCE;
		vi_attrs[6].binding = 6;
		vi_attrs[6].location = 6;
		vi_attrs[6].format = VK_FORMAT_R32G32B32A32_SFLOAT;
		vi_attrs[6].offset = sizeof(float) * 4 * 0;

		// model matrices 2
		vi_attrs[7].binding = 6;
		vi_attrs[7].location = 7;
		vi_attrs[7].format = VK_FORMAT_R32G32B32A32_SFLOAT;
		vi_attrs[7].offset = sizeof(float) * 4 * 1;

		// model matrices 3
		vi_attrs[8].binding = 6;
		vi_attrs[8].location = 8;
		vi_attrs[8].format = VK_FORMAT_R32G32B32A32_SFLOAT;
		vi_attrs[8].offset = sizeof(float) * 4 * 2;

		// model matrices 4
		vi_attrs[9].binding = 6;
		vi_attrs[9].location = 9;
		vi_attrs[9].format = VK_FORMAT_R32G32B32A32_SFLOAT;
		vi_attrs[9].offset = sizeof(float) * 4 * 3;

		// effect color mul
		vi_bindings[7].binding = 7;
		vi_bindings[7].stride = sizeof(float) * 4;
		vi_bindings[7].inputRate = VK_VERTEX_INPUT_RATE_INSTANCE;
		vi_attrs[10].binding = 7;
		vi_attrs[10].location = 10;
		vi_attrs[10].format = VK_FORMAT_R32G32B32A32_SFLOAT;
		vi_attrs[10].offset = 0;

		// effect color add
		vi_bindings[8].binding = 8;
		vi_bindings[8].stride = sizeof(float) * 4;
		vi_bindings[8].inputRate = VK_VERTEX_INPUT_RATE_INSTANCE;
		vi_attrs[11].binding = 8;
		vi_attrs[11].location = 11;
		vi_attrs[11].format = VK_FORMAT_R32G32B32A32_SFLOAT;
		vi_attrs[11].offset = 0;

		memset(&vi, 0, sizeof(vi));
		vi.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vi.pNext = NULL;
		vi.vertexBindingDescriptionCount = 9;
		vi.pVertexBindingDescriptions = vi_bindings;
		vi.vertexAttributeDescriptionCount = 12;
		vi.pVertexAttributeDescriptions = vi_attrs;

		pipeline.pVertexInputState = &vi;
		pipeline.pInputAssemblyState = &ia;
		pipeline.pRasterizationState = &rs;
		pipeline.pColorBlendState = haveColorBuffer == true?&cb:NULL;
		pipeline.pMultisampleState = &ms;
		pipeline.pViewportState = &vp;
		pipeline.pDepthStencilState = haveDepthBuffer == true?&ds:NULL;
		pipeline.pStages = shaderStages;
		pipeline.renderPass = renderPass;
		pipeline.pDynamicState = &dynamicState;

		memset(&pipelineCache, 0, sizeof(pipelineCache));
		pipelineCache.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;

		err = vkCreatePipelineCache(device, &pipelineCache, NULL, &programPipeline.pipelineCache);
		assert(!err);

		err = vkCreateGraphicsPipelines(device, programPipeline.pipelineCache, 1, &pipeline, NULL, &programPipeline.pipeline);
		assert(!err);

		vkDestroyPipelineCache(device, programPipeline.pipelineCache, NULL);

		//
		pipelinesIt = program.pipelines.find(pipelineId);
	}

}

inline void VKRenderer::setupObjectsRenderingPipeline(program_type& program) {
	auto pipelineId = createPipelineId();
	auto pipelinesIt = program.pipelines.find(pipelineId);
	if (program.created == false || pipelinesIt == program.pipelines.end()) {
		createObjectsRenderingPipeline(program);
	}

	//
	pipelinesIt = program.pipelines.find(pipelineId);
	auto newPipeline = pipelinesIt->second.pipeline;
	if (newPipeline != pipeline) {
		vkCmdBindPipeline(draw_cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, newPipeline);
		pipeline = newPipeline;

		//
		vkCmdSetViewport(draw_cmd, 0, 1, &viewport);
		vkCmdSetScissor(draw_cmd, 0, 1, &scissor);
	}
}

void VKRenderer::createPointsRenderingPipeline(program_type& program) {
	if (program.created == false) {
		VkResult err;

		//
		VkDescriptorSetLayoutBinding layout_bindings[program.layout_bindings];
		memset(layout_bindings, 0, sizeof(layout_bindings));

		// ubos, samplers
		auto shaderIdx = 0;
		for (auto shaderId: program.shader_ids) {
			auto shaderIt = shaders.find(shaderId);
			if (shaderIt == shaders.end()) {
				Console::println("VKRenderer::" + string(__FUNCTION__) + "(): shader does not exist: " + to_string(shaderId));
				return;
			}
			auto& shader = shaderIt->second;
			if (shader.ubo_binding_idx != -1) {
				layout_bindings[shader.ubo_binding_idx] = {
					.binding = static_cast<uint32_t>(shader.ubo_binding_idx),
					.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
					.descriptorCount = 1,
					.stageFlags = shader.type,
					.pImmutableSamplers = NULL
				};
			}
			for (auto uniformIt: shader.uniforms) {
				auto& uniform = uniformIt.second;
				if (uniform.type == shader_type::uniform_type::SAMPLER2D) {
					layout_bindings[uniform.position] = {
						.binding = static_cast<uint32_t>(uniform.position),
						.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
						.descriptorCount = 1,
						.stageFlags = shader.type,
						.pImmutableSamplers = NULL
					};
				}
			}
			shaderIdx++;
		}

		const VkDescriptorSetLayoutCreateInfo descriptor_layout = {
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
			.pNext = NULL,
			.flags = 0,
			.bindingCount = program.layout_bindings,
			.pBindings = layout_bindings,
		};

		err = vkCreateDescriptorSetLayout(device, &descriptor_layout, NULL, &program.desc_layout);
		assert(!err);

		const VkPipelineLayoutCreateInfo pPipelineLayoutCreateInfo = {
			.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
			.pNext = NULL,
			.flags = 0,
			.setLayoutCount = 1,
			.pSetLayouts = &program.desc_layout,
		};

		VkDescriptorSetLayout desc_layouts[DESC_MAX];
		for (auto i = 0; i < DESC_MAX; i++) desc_layouts[i] = program.desc_layout;

		//
		VkDescriptorSetAllocateInfo alloc_info = {
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
			.pNext = NULL,
			.descriptorPool = desc_pool,
			.descriptorSetCount = DESC_MAX,
			.pSetLayouts = desc_layouts
		};
		for (auto& context: contexts) {
			err = vkAllocateDescriptorSets(device, &alloc_info, program.desc_sets[context.idx]);
			assert(!err);
		}

		//
		err = vkCreatePipelineLayout(device, &pPipelineLayoutCreateInfo, NULL, &program.pipeline_layout);
		assert(!err);

		//
		for (auto& context: contexts) context.uniform_buffers_changed.fill(true);

		//
		program.created = true;
	}

	auto pipelineId = createPipelineId();
	auto pipelinesIt = program.pipelines.find(pipelineId);
	if (pipelinesIt == program.pipelines.end()) {
		auto& programPipeline = program.pipelines[pipelineId];

		VkRenderPass renderPass = render_pass;
		auto haveDepthBuffer = true;
		auto haveColorBuffer = true;
		if (bound_frame_buffer != 0) {
			auto frameBufferIt = framebuffers.find(bound_frame_buffer);
			auto& frameBufferStruct = frameBufferIt->second;
			haveDepthBuffer = frameBufferStruct.depth_texture_id != 0;
			haveColorBuffer = frameBufferStruct.color_texture_id != 0;
			renderPass = frameBufferStruct.render_pass;
		}

		//
		VkResult err;

		//
		VkGraphicsPipelineCreateInfo pipeline;
		memset(&pipeline, 0, sizeof(pipeline));

		// Stages
		VkPipelineShaderStageCreateInfo shaderStages[program.shader_ids.size()];
		memset(shaderStages, 0, program.shader_ids.size() * sizeof(VkPipelineShaderStageCreateInfo));

		// shader stages
		auto shaderIdx = 0;
		for (auto shaderId: program.shader_ids) {
			auto shaderIt = shaders.find(shaderId);
			if (shaderIt == shaders.end()) {
				Console::println("VKRenderer::" + string(__FUNCTION__) + "(): shader does not exist: " + to_string(shaderId));
				return;
			}
			auto& shader = shaderIt->second;
			shaderStages[shaderIdx].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			shaderStages[shaderIdx].stage = shader.type;
			shaderStages[shaderIdx].module = shader.module;
			shaderStages[shaderIdx].pName = "main";
			shaderIdx++;
		}

		// create pipepine
		VkPipelineCacheCreateInfo pipelineCache;

		VkPipelineVertexInputStateCreateInfo vi;
		VkPipelineInputAssemblyStateCreateInfo ia;
		VkPipelineRasterizationStateCreateInfo rs;
		VkPipelineColorBlendStateCreateInfo cb;
		VkPipelineDepthStencilStateCreateInfo ds;
		VkPipelineViewportStateCreateInfo vp;
		VkPipelineMultisampleStateCreateInfo ms;
		VkDynamicState dynamicStateEnables[VK_DYNAMIC_STATE_RANGE_SIZE];
		VkPipelineDynamicStateCreateInfo dynamicState;

		createRasterizationStateCreateInfo(rs);
		createDepthStencilStateCreateInfo(ds);

		memset(dynamicStateEnables, 0, sizeof dynamicStateEnables);
		memset(&dynamicState, 0, sizeof dynamicState);
		dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamicState.pDynamicStates = dynamicStateEnables;

		pipeline.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipeline.stageCount = program.shader_ids.size();
		pipeline.layout = program.pipeline_layout;

		memset(&ia, 0, sizeof(ia));
		ia.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		ia.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;

		VkPipelineColorBlendAttachmentState att_state;
		createColorBlendAttachmentState(att_state);

		memset(&cb, 0, sizeof(cb));
		cb.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		cb.logicOpEnable = VK_FALSE;
		cb.attachmentCount = haveColorBuffer == true?1:0;
		cb.pAttachments = haveColorBuffer == true?&att_state:NULL;

		memset(&vp, 0, sizeof(vp));
		vp.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		vp.viewportCount = 1;
		dynamicStateEnables[dynamicState.dynamicStateCount++] = VK_DYNAMIC_STATE_VIEWPORT;
		vp.scissorCount = 1;
		dynamicStateEnables[dynamicState.dynamicStateCount++] = VK_DYNAMIC_STATE_SCISSOR;

		memset(&ms, 0, sizeof(ms));
		ms.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		ms.pSampleMask = NULL;
		ms.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

		VkVertexInputBindingDescription vi_bindings[4];
		memset(vi_bindings, 0, sizeof(vi_bindings));
		VkVertexInputAttributeDescription vi_attrs[4];
		memset(vi_attrs, 0, sizeof(vi_attrs));

		// vertices
		vi_bindings[0].binding = 0;
		vi_bindings[0].stride = sizeof(float) * 3;
		vi_bindings[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		vi_attrs[0].binding = 0;
		vi_attrs[0].location = 0;
		vi_attrs[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		vi_attrs[0].offset = 0;

		// normals
		vi_bindings[1].binding = 1;
		vi_bindings[1].stride = sizeof(float) * 3;
		vi_bindings[1].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		vi_attrs[1].binding = 1;
		vi_attrs[1].location = 1;
		vi_attrs[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		vi_attrs[1].offset = 0;

		// texture coordinates
		vi_bindings[2].binding = 2;
		vi_bindings[2].stride = sizeof(float) * 2;
		vi_bindings[2].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		vi_attrs[2].binding = 2;
		vi_attrs[2].location = 2;
		vi_attrs[2].format = VK_FORMAT_R32G32_SFLOAT;
		vi_attrs[2].offset = 0;

		// colors
		vi_bindings[3].binding = 3;
		vi_bindings[3].stride = sizeof(float) * 4;
		vi_bindings[3].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		vi_attrs[3].binding = 3;
		vi_attrs[3].location = 3;
		vi_attrs[3].format = VK_FORMAT_R32G32B32A32_SFLOAT;
		vi_attrs[3].offset = 0;


		memset(&vi, 0, sizeof(vi));
		vi.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vi.pNext = NULL;
		vi.vertexBindingDescriptionCount = 4;
		vi.pVertexBindingDescriptions = vi_bindings;
		vi.vertexAttributeDescriptionCount = 4;
		vi.pVertexAttributeDescriptions = vi_attrs;

		pipeline.pVertexInputState = &vi;
		pipeline.pInputAssemblyState = &ia;
		pipeline.pRasterizationState = &rs;
		pipeline.pColorBlendState = haveColorBuffer == true?&cb:NULL;
		pipeline.pMultisampleState = &ms;
		pipeline.pViewportState = &vp;
		pipeline.pDepthStencilState = haveDepthBuffer == true?&ds:NULL;
		pipeline.pStages = shaderStages;
		pipeline.renderPass = renderPass;
		pipeline.pDynamicState = &dynamicState;

		memset(&pipelineCache, 0, sizeof(pipelineCache));
		pipelineCache.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;

		err = vkCreatePipelineCache(device, &pipelineCache, NULL, &programPipeline.pipelineCache);
		assert(!err);

		err = vkCreateGraphicsPipelines(device, programPipeline.pipelineCache, 1, &pipeline, NULL, &programPipeline.pipeline);
		assert(!err);

		//
		vkDestroyPipelineCache(device, programPipeline.pipelineCache, NULL);

		//
		pipelinesIt = program.pipelines.find(pipelineId);
	}
}

inline void VKRenderer::setupPointsRenderingPipeline(program_type& program) {
	auto pipelineId = createPipelineId();
	auto pipelinesIt = program.pipelines.find(pipelineId);
	if (program.created == false || pipelinesIt == program.pipelines.end()) {
		createPointsRenderingPipeline(program);
	}

	//
	pipelinesIt = program.pipelines.find(pipelineId);
	auto newPipeline = pipelinesIt->second.pipeline;
	if (newPipeline != pipeline) {
		vkCmdBindPipeline(draw_cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, newPipeline);
		pipeline = newPipeline;

		//
		vkCmdSetViewport(draw_cmd, 0, 1, &viewport);
		vkCmdSetScissor(draw_cmd, 0, 1, &scissor);
	}
}

inline void VKRenderer::createSkinningComputingPipeline(program_type& program) {
	if (program.created == false) {
		VkResult err;

		auto& programPipeline = program.pipelines["default"];

		//
		VkDescriptorSetLayoutBinding layout_bindings[program.layout_bindings];
		memset(layout_bindings, 0, sizeof(layout_bindings));

		// Stages
		VkPipelineShaderStageCreateInfo shaderStages[program.shader_ids.size()];
		memset(shaderStages, 0, program.shader_ids.size() * sizeof(VkPipelineShaderStageCreateInfo));

		auto shaderIdx = 0;
		for (auto shaderId: program.shader_ids) {
			auto shaderIt = shaders.find(shaderId);
			if (shaderIt == shaders.end()) {
				Console::println("VKRenderer::" + string(__FUNCTION__) + "(): shader does not exist: " + to_string(shaderId));
				return;
			}
			auto& shader = shaderIt->second;
			shaderStages[shaderIdx].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			shaderStages[shaderIdx].stage = shader.type;
			shaderStages[shaderIdx].module = shader.module;
			shaderStages[shaderIdx].pName = "main";

			for (int i = 0; i <= shader.binding_max; i++) {
				layout_bindings[i] = {
					.binding = static_cast<uint32_t>(i),
					.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
					.descriptorCount = 1,
					.stageFlags = shader.type,
					.pImmutableSamplers = NULL
				};
			}

			if (shader.ubo_binding_idx != -1) {
				layout_bindings[shader.ubo_binding_idx] = {
					.binding = static_cast<uint32_t>(shader.ubo_binding_idx),
					.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
					.descriptorCount = 1,
					.stageFlags = shader.type,
					.pImmutableSamplers = NULL
				};
			}
			shaderIdx++;
		}
		const VkDescriptorSetLayoutCreateInfo descriptor_layout = {
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
			.pNext = NULL,
			.flags = 0,
			.bindingCount = program.layout_bindings,
			.pBindings = layout_bindings,
		};

		err = vkCreateDescriptorSetLayout(device, &descriptor_layout, NULL, &program.desc_layout);
		assert(!err);

		const VkPipelineLayoutCreateInfo pPipelineLayoutCreateInfo = {
			.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
			.pNext = NULL,
			.flags = 0,
			.setLayoutCount = 1,
			.pSetLayouts = &program.desc_layout,
		};

		VkDescriptorSetLayout desc_layouts[DESC_MAX];
		for (auto i = 0; i < DESC_MAX; i++) desc_layouts[i] = program.desc_layout;

		//
		VkDescriptorSetAllocateInfo alloc_info = {
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
			.pNext = NULL,
			.descriptorPool = desc_pool,
			.descriptorSetCount = DESC_MAX,
			.pSetLayouts = desc_layouts
		};
		for (auto& context: contexts) {
			err = vkAllocateDescriptorSets(device, &alloc_info, program.desc_sets[context.idx]);
			assert(!err);
		}

		//
		err = vkCreatePipelineLayout(device, &pPipelineLayoutCreateInfo, NULL, &program.pipeline_layout);
		assert(!err);

		// create pipepine
		VkPipelineCacheCreateInfo pipelineCache = {
			.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO,
			.pNext = NULL,
			.flags = 0,
			.initialDataSize = 0,
			.pInitialData = NULL
		};

		err = vkCreatePipelineCache(device, &pipelineCache, NULL, &programPipeline.pipelineCache);
		assert(!err);

		// create pipepine
		VkComputePipelineCreateInfo pipeline = {
		    .sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
		    .pNext = NULL,
		    .flags = 0,
			.stage = shaderStages[0],
			.layout = program.pipeline_layout,
		    .basePipelineHandle = NULL,
		    .basePipelineIndex = 0

		};

		err = vkCreateComputePipelines(device, programPipeline.pipelineCache, 1, &pipeline, NULL, &programPipeline.pipeline);
		assert(!err);

		vkDestroyPipelineCache(device, programPipeline.pipelineCache, NULL);

		//
		program.created = true;

		//
		for (auto& context: contexts) context.uniform_buffers_changed.fill(true);
	}
}

inline void VKRenderer::setupSkinningComputingPipeline(program_type& program) {
	if (program.created == false || program.pipelines.find("default") == program.pipelines.end()) {
		createSkinningComputingPipeline(program);
	}

	//
	auto newPipeline = program.pipelines.find("default")->second.pipeline;
	if (newPipeline != pipeline) {
		vkCmdBindPipeline(draw_cmd, VK_PIPELINE_BIND_POINT_COMPUTE, newPipeline);
		pipeline = newPipeline;
	}
}

void VKRenderer::useProgram(int32_t programId)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + to_string(programId));
	// if unsetting program flush command buffers
	if (program_id != 0) {
		flushCommandsAllContexts();
		finishPipeline();
	}

	program_id = 0;
	if (programId == 0) return;

	auto programIt = programs.find(programId);
	if (programIt == programs.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program does not exist: " + to_string(programId));
		return;
	}

	auto& program = programIt->second;
	preparePipeline(program);
	program_id = programId;
}

int32_t VKRenderer::createProgram()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	auto& programStruct = programs[program_idx];
	programStruct.id = program_idx++;
	programStruct.desc_idxs.fill(0);
	return programStruct.id;
}

void VKRenderer::attachShaderToProgram(int32_t programId, int32_t shaderId)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	auto shaderIt = shaders.find(shaderId);
	if (shaderIt == shaders.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): shader does not exist");
		return;
	}
	auto programIt = programs.find(programId);
	if (programIt == programs.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program does not exist");
		return;
	}
	programIt->second.shader_ids.push_back(shaderId);
}

bool VKRenderer::linkProgram(int32_t programId)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + to_string(programId));
	auto programIt = programs.find(programId);
	if (programIt == programs.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program does not exist");
		return false;
	}

	map<string, int32_t> uniformsByName;
	auto bindingIdx = 0;
	for (auto shaderId: programIt->second.shader_ids) {
		auto shaderIt = shaders.find(shaderId);
		if (shaderIt == shaders.end()) {
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): shader does not exist");
			return false;
		}

		//
		auto& shader = shaderIt->second;
		bindingIdx = Math::max(shader.binding_max + 1, bindingIdx);
	}

	auto uniformIdx = 1;
	for (auto shaderId: programIt->second.shader_ids) {
		auto shaderIt = shaders.find(shaderId);
		if (shaderIt == shaders.end()) {
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): shader does not exist");
			return false;
		}

		//
		auto& shader = shaderIt->second;

		// do we need a uniform buffer object for this shader stage?
		if (shader.ubo_size > 0) {
			for (auto& context: contexts) shader.ubo[context.idx] = createBufferObjects(1, false)[0];
			// yep, inject UBO index
			shader.ubo_binding_idx = bindingIdx;
			shader.source = StringUtils::replace(shader.source, "{$UBO_BINDING_IDX}", to_string(bindingIdx));
			bindingIdx++;
		}

	}

	// bind samplers, compile shaders
	for (auto shaderId: programIt->second.shader_ids) {
		auto shaderIt = shaders.find(shaderId);
		if (shaderIt == shaders.end()) {
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): shader does not exist");
			return false;
		}
		auto shaderSamplerIdx = 0;
		auto& shader = shaderIt->second;

		//
		for (auto& uniformIt: shader.uniforms) {
			auto& uniform = uniformIt.second;
			//
			if (uniform.type == shader_type::uniform_type::SAMPLER2D) {
				shader.source = StringUtils::replace(shader.source, "{$SAMPLER2D_BINDING_" + uniform.name + "_IDX}", to_string(bindingIdx));
				uniform.position = bindingIdx++;
			}
			uniformsByName[uniform.name] = uniformIdx++;
		}

		// compile shader
		EShLanguage stage = shaderFindLanguage(shader.type);
		glslang::TShader glslShader(stage);
		glslang::TProgram glslProgram;
		const char *shaderStrings[1];
		TBuiltInResource resources;
		shaderInitResources(resources);

		// Enable SPIR-V and Vulkan rules when parsing GLSL
		EShMessages messages = (EShMessages)(EShMsgSpvRules | EShMsgVulkanRules);

		shaderStrings[0] = shader.source.c_str();
		glslShader.setStrings(shaderStrings, 1);

		if (!glslShader.parse(&resources, 100, false, messages)) {
			// be verbose
			Console::println(
				string(
					string("GL3Renderer::") +
					string(__FUNCTION__) +
					string("[") +
					to_string(shader.id) +
					string("]") +
					string(": parsing failed: ") +
					glslShader.getInfoLog() + ": " +
					glslShader.getInfoDebugLog()
				 )
			);
			Console::println(shader.source);
			return false;
		}

		glslProgram.addShader(&glslShader);
		if (glslProgram.link(messages) == false) {
			// be verbose
			Console::println(
				string(
					string("GL3Renderer::") +
					string(__FUNCTION__) +
					string("[") +
					to_string(shader.id) +
					string("]") +
					string(": linking failed: ") +
					glslShader.getInfoLog() + ": " +
					glslShader.getInfoDebugLog()
				)
			);
			Console::println(shader.source);
			return false;
		}
		glslang::GlslangToSpv(*glslProgram.getIntermediate(stage), shader.spirv);

		// create shader module
		{
			VkResult err;
			VkShaderModuleCreateInfo moduleCreateInfo;
			moduleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
			moduleCreateInfo.pNext = NULL;
			moduleCreateInfo.codeSize = shader.spirv.size() * sizeof(uint32_t);
			moduleCreateInfo.pCode = shader.spirv.data();
			moduleCreateInfo.flags = 0;
			err = vkCreateShaderModule(device, &moduleCreateInfo, NULL, &shader.module);
			if (err == VK_SUCCESS) {
				if (VERBOSE == true) {
					Console::println(
						string(
							string("GL3Renderer::") +
							string(__FUNCTION__) +
							string("[") +
							to_string(shader.id) +
							string("]") +
							string(": SUCCESS")
						 )
					);
				}
			} else {
				Console::println(
					string(
						string("GL3Renderer::") +
						string(__FUNCTION__) +
						string("[") +
						to_string(shader.id) +
						string("]") +
						string(": FAILED")
					 )
				);
				Console::println(shader.source);
				return false;
			}
	    }
	}

	//
	for (auto& uniformIt: uniformsByName) {
		programIt->second.uniforms[uniformIt.second] = uniformIt.first;
	}

	// total bindings of program
	programIt->second.layout_bindings = bindingIdx;

	//
	return true;
}

int32_t VKRenderer::getProgramUniformLocation(int32_t programId, const string& name)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + name);
	auto programIt = programs.find(programId);
	if (programIt == programs.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program does not exist");
		return -1;
	}
	for (auto& uniformIt: programIt->second.uniforms) {
		if (uniformIt.second == name) {
			if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + name + " -- > " + to_string(uniformIt.first));
			return uniformIt.first;
		}
	}
	Console::println("VKRenderer::" + string(__FUNCTION__) + "(): uniform not found: '" + name + "'");
	return -1;
}

inline void VKRenderer::setProgramUniformInternal(void* context, int32_t uniformId, uint8_t* data, int32_t size) {
	auto programIt = programs.find(program_id);
	if (programIt == programs.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program not found: " + to_string(program_id));
		return;
	}
	auto& program = programIt->second;
	auto uniformIt = program.uniforms.find(uniformId);
	if (uniformIt == program.uniforms.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): uniform does not exist: " + to_string(uniformId));
		return;
	}

	// have our context typed
	auto& contextTyped = *static_cast<context_type*>(context);

	auto changedUniforms = 0;
	auto shaderIdx = 0;
	for (auto& shaderId: program.shader_ids) {
		auto shaderIt = shaders.find(shaderId);
		if (shaderIt == shaders.end()) {
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program: shader does not exist");
			return;
		}

		auto& shader = shaderIt->second;
		auto shaderUniformIt = shader.uniforms.find(uniformIt->second);
		if (shaderUniformIt == shader.uniforms.end()) {
			shaderIdx++;
			continue;
		}
		auto& shaderUniform = shaderUniformIt->second;
		if (shaderUniform.type == shader_type::uniform_type::SAMPLER2D) {
			shaderUniform.texture_unit = *((int32_t*)data);
		} else {
			if (contextTyped.uniform_buffers[shaderIdx].size() < shaderUniform.position + size) {
				Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program: uniform buffer is too small: " + to_string(shaderIdx) + "; " + to_string(contextTyped.uniform_buffers[shaderIdx].size()) + "; " + to_string(shaderUniform.position + size) + ": " + shaderUniform.name);
				shaderIdx++;
				continue;
			}
			auto uniformNoChange = true;
			auto byteChanged = false;
			for (auto i = 0; i < size; i++) {
				byteChanged = contextTyped.uniform_buffers[shaderIdx][shaderUniform.position + i] != data[i];
				if (byteChanged == true) contextTyped.uniform_buffers[shaderIdx][shaderUniform.position + i] = data[i];
				uniformNoChange&= !byteChanged;
			}
			if (uniformNoChange == false) contextTyped.uniform_buffers_changed[shaderIdx] = true;
		}
		changedUniforms++;
		shaderIdx++;
	}
	if (changedUniforms == 0) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program: no uniform: " + uniformIt->second);
	}
}

void VKRenderer::setProgramUniformInteger(void* context, int32_t uniformId, int32_t value)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	setProgramUniformInternal(context, uniformId, (uint8_t*)&value, sizeof(int32_t));
}

void VKRenderer::setProgramUniformFloat(void* context, int32_t uniformId, float value)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	setProgramUniformInternal(context, uniformId, (uint8_t*)&value, sizeof(float));
}

void VKRenderer::setProgramUniformFloatMatrix3x3(void* context, int32_t uniformId, const array<float, 9>& data)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	array<float, 12> _data = {
		data[0],
		data[1],
		data[2],
		0.0,
		data[3],
		data[4],
		data[5],
		0.0,
		data[6],
		data[7],
		data[8],
		0.0
	};
	setProgramUniformInternal(context, uniformId, (uint8_t*)_data.data(), _data.size() * sizeof(float));
}

void VKRenderer::setProgramUniformFloatMatrix4x4(void* context, int32_t uniformId, const array<float, 16>& data)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	setProgramUniformInternal(context, uniformId, (uint8_t*)data.data(), data.size() * sizeof(float));
}

void VKRenderer::setProgramUniformFloatMatrices4x4(void* context, int32_t uniformId, int32_t count, FloatBuffer* data)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	setProgramUniformInternal(context, uniformId, (uint8_t*)data->getBuffer(), count * sizeof(float) * 16);
}

void VKRenderer::setProgramUniformFloatVec4(void* context, int32_t uniformId, const array<float, 4>& data)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	setProgramUniformInternal(context, uniformId, (uint8_t*)data.data(), data.size() * sizeof(float));
}

void VKRenderer::setProgramUniformFloatVec3(void* context, int32_t uniformId, const array<float, 3>& data)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	setProgramUniformInternal(context, uniformId, (uint8_t*)data.data(), data.size() * sizeof(float));
}

void VKRenderer::setProgramAttributeLocation(int32_t programId, int32_t location, const string& name)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setViewPort(int32_t x, int32_t y, int32_t width, int32_t height)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + to_string(x) + ", " + to_string(y) + "; " + to_string(width) + ", " + to_string(height));

	//
	memset(&viewport, 0, sizeof(viewport));
	viewport.width = (float)width;
	viewport.height = (float)height;
	viewport.x = (float)x;
	viewport.y = (float)y;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	memset(&scissor, 0, sizeof(scissor));
	scissor.extent.width = width;
	scissor.extent.height = height;
	scissor.offset.x = x;
	scissor.offset.y = y;

	//
	this->pointSize = width > height ? width / 120.0f : height / 120.0f * 16 / 9;
}

void VKRenderer::updateViewPort()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setClearColor(float red, float green, float blue, float alpha)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");

	//
	clear_red = red;
	clear_green = green;
	clear_blue = blue;
	clear_alpha = alpha;
}

void VKRenderer::enableCulling()
{
	if (culling_enabled == true) return;
	flushCommandsAllContexts();
	culling_enabled = true;
}

void VKRenderer::disableCulling()
{
	if (culling_enabled == false) return;
	flushCommandsAllContexts();
	culling_enabled = false;
}

void VKRenderer::enableBlending()
{
	if (blending_enabled == true) return;
	flushCommandsAllContexts();
	blending_enabled = true;
}

void VKRenderer::disableBlending()
{
	if (blending_enabled == false) return;
	flushCommandsAllContexts();
	blending_enabled = false;
}

void VKRenderer::enableDepthBufferWriting()
{
	if (depth_buffer_writing == true) return;
	flushCommandsAllContexts();
	depth_buffer_writing = true;
}

void VKRenderer::disableDepthBufferWriting()
{
	if (depth_buffer_writing == false) return;
	flushCommandsAllContexts();
	depth_buffer_writing = false;
}

void VKRenderer::disableDepthBufferTest()
{
	if (depth_buffer_testing == false) return;
	flushCommandsAllContexts();
	depth_buffer_testing = false;
}

void VKRenderer::enableDepthBufferTest()
{
	if (depth_buffer_testing == true) return;
	flushCommandsAllContexts();
	depth_buffer_testing = true;
}

void VKRenderer::setDepthFunction(int32_t depthFunction)
{
	if (depth_function == depthFunction) return;
	flushCommandsAllContexts();
	depth_function = depthFunction;
}

void VKRenderer::setColorMask(bool red, bool green, bool blue, bool alpha)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::clear(int32_t mask)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + to_string(clear_mask));
	clear_mask = mask;
}

void VKRenderer::setCullFace(int32_t cullFace)
{
	if (cull_mode == cullFace) return;
	flushCommandsAllContexts();
	cull_mode = (VkCullModeFlagBits)cullFace;
}

void VKRenderer::setFrontFace(int32_t frontFace)
{
	if (front_face == frontFace) return;
	flushCommandsAllContexts();
	front_face = (VkFrontFace)frontFace;
}

int32_t VKRenderer::createTexture()
{
	textures_rwlock.writeLock();
	auto& texture_object = textures[texture_idx];
	texture_object.id = texture_idx++;
	textures_rwlock.unlock();
	return texture_object.id;
}

int32_t VKRenderer::createDepthBufferTexture(int32_t width, int32_t height) {
	auto& depth_buffer_texture = textures[texture_idx];
	depth_buffer_texture.id = texture_idx++;
	createDepthBufferTexture(depth_buffer_texture.id, width, height);
	return depth_buffer_texture.id;
}

void VKRenderer::createDepthBufferTexture(int32_t textureId, int32_t width, int32_t height)
{
	auto& depth_buffer_texture = textures[textureId];
	depth_buffer_texture.format = VK_FORMAT_D32_SFLOAT;
	depth_buffer_texture.width = width;
	depth_buffer_texture.height = height;

	if (depth_buffer_texture.view != VK_NULL_HANDLE) vkDestroyImageView(device, depth_buffer_texture.view, NULL);
	if (depth_buffer_texture.image != VK_NULL_HANDLE) vkDestroyImage(device, depth_buffer_texture.image, NULL);
	if (depth_buffer_texture.mem != VK_NULL_HANDLE) vkFreeMemory(device, depth_buffer_texture.mem, NULL);
	if (depth_buffer_texture.sampler != VK_NULL_HANDLE) vkDestroySampler(device, depth_buffer_texture.sampler, NULL);

	const VkImageCreateInfo image = {
		.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.imageType = VK_IMAGE_TYPE_2D,
		.format = depth_buffer_texture.format,
		.extent = {
			.width = depth_buffer_texture.width,
			.height = depth_buffer_texture.height,
			.depth = 1
		},
		.mipLevels = 1,
		.arrayLayers = 1,
		.samples = VK_SAMPLE_COUNT_1_BIT,
		.tiling = VK_IMAGE_TILING_OPTIMAL,
		.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
		.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
		.queueFamilyIndexCount = 0,
		.pQueueFamilyIndices = 0,
		.initialLayout = (VkImageLayout)0,
	};
	VkMemoryAllocateInfo mem_alloc = {
		.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		.pNext = NULL,
		.allocationSize = 0,
		.memoryTypeIndex = 0,
	};

	VkMemoryRequirements mem_reqs;
	VkResult err;
	bool pass;

	// create image
	err = vkCreateImage(device, &image, NULL, &depth_buffer_texture.image);
	assert(!err);

	// get memory requirements for this object
	vkGetImageMemoryRequirements(device, depth_buffer_texture.image, &mem_reqs);

	// select memory size and type
	mem_alloc.allocationSize = mem_reqs.size;
	pass = memoryTypeFromProperties(mem_reqs.memoryTypeBits, 0, &mem_alloc.memoryTypeIndex);
	assert(pass);

	// allocate memory
	err = vkAllocateMemory(device, &mem_alloc, NULL, &depth_buffer_texture.mem);
	assert(!err);

	// bind memory
	err = vkBindImageMemory(device, depth_buffer_texture.image, depth_buffer_texture.mem, 0);
	assert(!err);

	//
	depth_buffer_texture.type = texture_object::TYPE_FRAMEBUFFER_DEPTHBUFFER;
	depth_buffer_texture.image_layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	//
	setImageLayout(
		depth_buffer_texture.image,
		VK_IMAGE_ASPECT_DEPTH_BIT,
		VK_IMAGE_LAYOUT_UNDEFINED,
		depth_buffer_texture.image_layout,
		(VkAccessFlagBits)0
	);

	// create sampler
	const VkSamplerCreateInfo sampler = {
		.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.magFilter = VK_FILTER_NEAREST,
		.minFilter = VK_FILTER_NEAREST,
		.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,
		.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
		.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
		.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
		.mipLodBias = 0.0f,
		.anisotropyEnable = VK_FALSE,
		.maxAnisotropy = 1,
		.compareEnable = VK_FALSE,
		.compareOp = VK_COMPARE_OP_NEVER,
		.minLod = 0.0f,
		.maxLod = 0.0f,
		.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE,
		.unnormalizedCoordinates = VK_FALSE,
	};
	err = vkCreateSampler(device, &sampler, NULL, &depth_buffer_texture.sampler);
	assert(!err);

	// create image view
	VkImageViewCreateInfo view = {
		.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.image = depth_buffer_texture.image,
		.viewType = VK_IMAGE_VIEW_TYPE_2D,
		.format = depth_buffer_texture.format,
		.components = VkComponentMapping(),
		.subresourceRange = {
			.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT,
			.baseMipLevel = 0,
			.levelCount = 1,
			.baseArrayLayer = 0,
			.layerCount = 1
		},
	};
	err = vkCreateImageView(device, &view, NULL, &depth_buffer_texture.view);
	assert(!err);
}

int32_t VKRenderer::createColorBufferTexture(int32_t width, int32_t height) {
	auto& color_buffer_texture = textures[texture_idx];
	color_buffer_texture.id = texture_idx++;
	createColorBufferTexture(color_buffer_texture.id, width, height);
	return color_buffer_texture.id;
}

void VKRenderer::createColorBufferTexture(int32_t textureId, int32_t width, int32_t height)
{
	auto& color_buffer_texture = textures[textureId];
	color_buffer_texture.format = format;
	color_buffer_texture.width = width;
	color_buffer_texture.height = height;

	if (color_buffer_texture.view != VK_NULL_HANDLE) vkDestroyImageView(device, color_buffer_texture.view, NULL);
	if (color_buffer_texture.image != VK_NULL_HANDLE) vkDestroyImage(device, color_buffer_texture.image, NULL);
	if (color_buffer_texture.mem != VK_NULL_HANDLE) vkFreeMemory(device, color_buffer_texture.mem, NULL);
	if (color_buffer_texture.sampler != VK_NULL_HANDLE) vkDestroySampler(device, color_buffer_texture.sampler, NULL);

	const VkImageCreateInfo image = {
		.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.imageType = VK_IMAGE_TYPE_2D,
		.format = color_buffer_texture.format,
		.extent = {
			.width = color_buffer_texture.width,
			.height = color_buffer_texture.height,
			.depth = 1
		},
		.mipLevels = 1,
		.arrayLayers = 1,
		.samples = VK_SAMPLE_COUNT_1_BIT,
		.tiling = VK_IMAGE_TILING_OPTIMAL,
		.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
		.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
		.queueFamilyIndexCount = 0,
		.pQueueFamilyIndices = 0,
		.initialLayout = (VkImageLayout)0,
	};
	VkMemoryAllocateInfo mem_alloc = {
		.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		.pNext = NULL,
		.allocationSize = 0,
		.memoryTypeIndex = 0,
	};

	VkMemoryRequirements mem_reqs;
	VkResult err;
	bool pass;

	// create image
	err = vkCreateImage(device, &image, NULL, &color_buffer_texture.image);
	assert(!err);

	// get memory requirements for this object
	vkGetImageMemoryRequirements(device, color_buffer_texture.image, &mem_reqs);

	// select memory size and type
	mem_alloc.allocationSize = mem_reqs.size;
	pass = memoryTypeFromProperties(mem_reqs.memoryTypeBits, 0, &mem_alloc.memoryTypeIndex);
	assert(pass);

	// allocate memory
	err = vkAllocateMemory(device, &mem_alloc, NULL, &color_buffer_texture.mem);
	assert(!err);

	// bind memory
	err = vkBindImageMemory(device, color_buffer_texture.image, color_buffer_texture.mem, 0);
	assert(!err);

	//
	color_buffer_texture.type = texture_object::TYPE_FRAMEBUFFER_COLORBUFFER;
	color_buffer_texture.image_layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	//
	setImageLayout(
		color_buffer_texture.image,
		VK_IMAGE_ASPECT_COLOR_BIT,
		VK_IMAGE_LAYOUT_UNDEFINED,
		color_buffer_texture.image_layout,
		(VkAccessFlagBits)0
	);

	// create sampler
	const VkSamplerCreateInfo sampler = {
		.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.magFilter = VK_FILTER_LINEAR,
		.minFilter = VK_FILTER_LINEAR,
		.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,
		.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT,
		.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT,
		.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT,
		.mipLodBias = 0.0f,
		.anisotropyEnable = VK_FALSE,
		.maxAnisotropy = 1,
		.compareEnable = VK_FALSE,
		.compareOp = VK_COMPARE_OP_NEVER,
		.minLod = 0.0f,
		.maxLod = 0.0f,
		.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE,
		.unnormalizedCoordinates = VK_FALSE,
	};
	err = vkCreateSampler(device, &sampler, NULL, &color_buffer_texture.sampler);
	assert(!err);

	// create image view
	VkImageViewCreateInfo view = {
		.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.image = color_buffer_texture.image,
		.viewType = VK_IMAGE_VIEW_TYPE_2D,
		.format = color_buffer_texture.format,
		.components = {
			.r = VK_COMPONENT_SWIZZLE_R,
			.g = VK_COMPONENT_SWIZZLE_G,
			.b = VK_COMPONENT_SWIZZLE_B,
			.a = VK_COMPONENT_SWIZZLE_A,
		},
		.subresourceRange = {
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
			.baseMipLevel = 0,
			.levelCount = 1,
			.baseArrayLayer = 0,
			.layerCount = 1
		}
	};
	err = vkCreateImageView(device, &view, NULL, &color_buffer_texture.view);
	assert(!err);
}

void VKRenderer::uploadTexture(void* context, Texture* texture)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");

	// have our context typed
	auto& contextTyped = *static_cast<context_type*>(context);

	//
	textures_rwlock.readLock();
	auto textureObjectIt = textures.find(contextTyped.bound_textures[activeTextureUnit]);
	if (textureObjectIt == textures.end()) {
		textures_rwlock.unlock();
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): texture not found: " + to_string(contextTyped.bound_textures[activeTextureUnit]));
		return;
	}
	auto& texture_object = textureObjectIt->second;
	textures_rwlock.unlock();

	//
	texture_object.width = texture->getTextureWidth();
	texture_object.height = texture->getTextureHeight();

	if (texture_object.uploaded == true) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): texture already uploaded: " + to_string(contextTyped.bound_textures[activeTextureUnit]));
		return;
	}

	const VkFormat tex_format = texture->getHeight() == 32?VK_FORMAT_R8G8B8A8_UNORM:VK_FORMAT_R8G8B8A8_UNORM;
	VkFormatProperties props;
	VkResult err;


	vkGetPhysicalDeviceFormatProperties(gpu, tex_format, &props);
	if ((props.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) {
		// we need a setup command buffer here
		prepareSetupCommandBuffer();

		// Must use staging buffer to copy linear texture to optimized
		struct texture_object staging_texture;

		//
		memset(&staging_texture, 0, sizeof(staging_texture));

		prepareTextureImage(
			&staging_texture,
			VK_IMAGE_TILING_LINEAR,
			VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			texture,
			VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL
		);
		prepareTextureImage(
			&texture_object,
			VK_IMAGE_TILING_OPTIMAL,
			VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			texture,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL
		);
		setImageLayout(
			staging_texture.image,
			VK_IMAGE_ASPECT_COLOR_BIT,
			staging_texture.image_layout,
			VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
			(VkAccessFlagBits)0
		);
		setImageLayout(
			texture_object.image,
			VK_IMAGE_ASPECT_COLOR_BIT,
			texture_object.image_layout,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			(VkAccessFlagBits)0
		);
		texture_object.image_layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

		VkImageCopy copy_region = {
			.srcSubresource = {
				.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
				.mipLevel = 0,
				.baseArrayLayer = 0,
				.layerCount = 1
			},
			.srcOffset = {
				.x = 0,
				.y = 0,
				.z = 0
			},
			.dstSubresource = {
				.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
				.mipLevel = 0,
				.baseArrayLayer = 0,
				.layerCount = 1
			},
			.dstOffset = {
				.x = 0,
				.y = 0,
				.z = 0
			},
			.extent = {
				.width = texture_object.width,
				.height = texture_object.height,
				.depth = 1
			}
		};

		vkCmdCopyImage(
			setup_cmd,
			staging_texture.image,
			VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
			texture_object.image,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			1,
			&copy_region
		);

		setImageLayout(
			texture_object.image,
			VK_IMAGE_ASPECT_COLOR_BIT,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			texture_object.image_layout,
			(VkAccessFlagBits)0
		);

		// mark for deletion
		delete_images.push_back(staging_texture.image);
		delete_memory.push_back(staging_texture.mem);
	} else
	if ((props.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) {
		// Device can texture using linear textures
		prepareTextureImage(
			&texture_object,
			VK_IMAGE_TILING_LINEAR,
			VK_IMAGE_USAGE_SAMPLED_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			texture,
			VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
		);
	} else {
		// Can't support VK_FORMAT_B8G8R8A8_UNORM !?
		assert(!"No support for B8G8R8A8_UNORM as texture image format");
	}

	const VkSamplerCreateInfo sampler = {
		.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.magFilter = VK_FILTER_LINEAR,
		.minFilter = VK_FILTER_LINEAR,
		.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,
		.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT,
		.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT,
		.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT,
		.mipLodBias = 0.0f,
		.anisotropyEnable = VK_FALSE,
		.maxAnisotropy = 1,
		.compareEnable = VK_FALSE,
		.compareOp = VK_COMPARE_OP_NEVER,
		.minLod = 0.0f,
		.maxLod = 0.0f,
		.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE,
		.unnormalizedCoordinates = VK_FALSE,
	};
	VkImageViewCreateInfo view = {
		.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.image = texture_object.image,
		.viewType = VK_IMAGE_VIEW_TYPE_2D,
		.format = tex_format,
		.components = {
			.r = VK_COMPONENT_SWIZZLE_R,
			.g = VK_COMPONENT_SWIZZLE_G,
			.b = VK_COMPONENT_SWIZZLE_B,
			.a = VK_COMPONENT_SWIZZLE_A,
		},
		.subresourceRange = {
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
			.baseMipLevel = 0,
			.levelCount = 1,
			.baseArrayLayer = 0,
			.layerCount = 1
		}
	};

	// create sampler
	err = vkCreateSampler(device, &sampler, NULL, &texture_object.sampler);
	assert(!err);

	// create image view
	err = vkCreateImageView(device, &view, NULL, &texture_object.view);
	assert(!err);

	//
	texture_object.uploaded = true;
}

void VKRenderer::resizeDepthBufferTexture(int32_t textureId, int32_t width, int32_t height)
{
	auto textureIt = textures.find(textureId);
	if (textureIt == textures.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): texture not found: " + to_string(textureId));
		return;
	}
	auto texture = textureIt->second;
	createDepthBufferTexture(textureId, width, height);
	if (texture.frame_buffer_object_id != 0) createFramebufferObject(texture.frame_buffer_object_id);
}

void VKRenderer::resizeColorBufferTexture(int32_t textureId, int32_t width, int32_t height)
{
	auto textureIt = textures.find(textureId);
	if (textureIt == textures.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): texture not found: " + to_string(textureId));
		return;
	}
	auto texture = textureIt->second;
	createColorBufferTexture(textureId, width, height);
	if (texture.frame_buffer_object_id != 0) createFramebufferObject(texture.frame_buffer_object_id);
}

void VKRenderer::bindTexture(void* context, int32_t textureId)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");

	// have our context typed
	auto& contextTyped = *static_cast<context_type*>(context);

	//
	contextTyped.bound_textures[contextTyped.texture_unit_active] = 0;

	//
	textures_rwlock.readLock();
	auto textureObjectIt = textures.find(textureId);
	if (textureId != 0) {
		if (textureObjectIt == textures.end()) {
			textures_rwlock.unlock();
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): texture not found: " + to_string(contextTyped.bound_textures[contextTyped.texture_unit_active]));
			return;
		}
	}
	//
	auto& textureObject = textureObjectIt->second;
	textures_rwlock.unlock();

	// bin
	contextTyped.bound_textures[contextTyped.texture_unit_active] = textureId;
	if (textureId == 0) {
		onBindTexture(context, textureId);
		return;
	}

	//
	if (textureObject.type == texture_object::TYPE_FRAMEBUFFER_DEPTHBUFFER) {
		if (textureObject.image_layout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) {
			prepareSetupCommandBuffer();
			setImageLayout(
				textureObject.image,
				VK_IMAGE_ASPECT_DEPTH_BIT,
				VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
				VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL,
				(VkAccessFlagBits)0
			);
			textureObject.image_layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
			finishSetupCommandBuffer();
		}
	} else
	if (textureObject.type == texture_object::TYPE_FRAMEBUFFER_COLORBUFFER) {
		if (textureObject.image_layout == VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL) {
			prepareSetupCommandBuffer();
			setImageLayout(
				textureObject.image,
				VK_IMAGE_ASPECT_COLOR_BIT,
				VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
				VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
				(VkAccessFlagBits)0
			);
			textureObject.image_layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			finishSetupCommandBuffer();
		}
	}

	// done
	onBindTexture(context, textureId);
}

void VKRenderer::disposeTexture(int32_t textureId)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");

	textures_rwlock.writeLock();
	auto textureObjectIt = textures.find(textureId);
	if (textureObjectIt == textures.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): texture not found: " + to_string(textureId));
		textures_rwlock.unlock();
		return;
	}

	auto& texture = textureObjectIt->second;

	textures.erase(textureObjectIt);
	textures_rwlock.unlock();

	vkDestroyImageView(device, texture.view, NULL);
	vkDestroyImage(device, texture.image, NULL);
	vkFreeMemory(device, texture.mem, NULL);
	vkDestroySampler(device, texture.sampler, NULL);
}

void VKRenderer::createFramebufferObject(int32_t frameBufferId) {
	auto frameBufferIt = framebuffers.find(frameBufferId);
	if (frameBufferIt == framebuffers.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): frame buffer not found: " + to_string(frameBufferId));
		return;
	}
	auto& frameBufferStruct = frameBufferIt->second;

	texture_object* depthBufferTexture = nullptr;
	texture_object* colorBufferTexture = nullptr;

	auto depthBufferTextureIt = textures.find(frameBufferStruct.depth_texture_id);
	if (depthBufferTextureIt == textures.end()) {
		if (frameBufferStruct.depth_texture_id != 0) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): depth buffer texture not found: " + to_string(frameBufferStruct.depth_texture_id));
	} else {
		depthBufferTexture = &depthBufferTextureIt->second;
	}
	auto colorBufferTextureIt = textures.find(frameBufferStruct.color_texture_id);
	if (colorBufferTextureIt == textures.end()) {
		if (frameBufferStruct.color_texture_id != 0) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): color buffer texture not found: " + to_string(frameBufferStruct.color_texture_id));
	} else {
		colorBufferTexture = &colorBufferTextureIt->second;
	}

	//
	if (depthBufferTexture != nullptr && colorBufferTexture != nullptr &&
		(depthBufferTexture->width != colorBufferTexture->width ||
		depthBufferTexture->height != colorBufferTexture->height)) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): attachments with different dimension found: Not creating!");
		return;
	}

	if (depthBufferTexture != nullptr) depthBufferTexture->frame_buffer_object_id = frameBufferStruct.id;
	if (colorBufferTexture != nullptr) colorBufferTexture->frame_buffer_object_id = frameBufferStruct.id;

	VkResult err;

	{
		if (frameBufferStruct.render_pass != VK_NULL_HANDLE) vkDestroyRenderPass(device, frameBufferStruct.render_pass, NULL);

		auto attachmentIdx = 0;
		VkAttachmentDescription attachments[2];
		if (colorBufferTexture != nullptr) {
			attachments[attachmentIdx++] = {
				.flags = 0,
				.format = format,
				.samples = VK_SAMPLE_COUNT_1_BIT,
				.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
				.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
				.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
				.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
				.initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
				.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
			};
		}
		if (depthBufferTexture != nullptr) {
			attachments[attachmentIdx++] = {
				.flags = 0,
				.format = VK_FORMAT_D32_SFLOAT,
				.samples = VK_SAMPLE_COUNT_1_BIT,
				.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
				.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
				.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
				.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
				.initialLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
				.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
			};
		}
		const VkAttachmentReference color_reference = {
			.attachment = 0,
			.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		};
		const VkAttachmentReference depth_reference = {
			.attachment = static_cast<uint32_t>(colorBufferTexture != nullptr?1:0),
			.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
		};
		const VkSubpassDescription subpass = {
			.flags = 0,
			.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
			.inputAttachmentCount = 0,
			.pInputAttachments = NULL,
			.colorAttachmentCount = static_cast<uint32_t>(colorBufferTexture != nullptr?1:0),
			.pColorAttachments = colorBufferTexture != nullptr?&color_reference:NULL,
			.pResolveAttachments = NULL,
			.pDepthStencilAttachment = depthBufferTexture != nullptr?&depth_reference:NULL,
			.preserveAttachmentCount = 0,
			.pPreserveAttachments = NULL
		};
		const VkRenderPassCreateInfo rp_info = {
			.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
			.pNext = NULL,
			.flags = 0,
			.attachmentCount = static_cast<uint32_t>(attachmentIdx),
			.pAttachments = attachments,
			.subpassCount = 1,
			.pSubpasses = &subpass,
			.dependencyCount = 0,
			.pDependencies = NULL
		};
		err = vkCreateRenderPass(device, &rp_info, NULL, &frameBufferStruct.render_pass);
		assert(!err);
	}

	{
		if (frameBufferStruct.frame_buffer != VK_NULL_HANDLE) vkDestroyFramebuffer(device, frameBufferStruct.frame_buffer, NULL);
		auto attachmentIdx = 0;
		VkImageView attachments[2];
		if (colorBufferTexture != nullptr) attachments[attachmentIdx++] = colorBufferTexture->view;
		if (depthBufferTexture != nullptr) attachments[attachmentIdx++] = depthBufferTexture->view;
		const VkFramebufferCreateInfo fb_info = {
			.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
			.pNext = NULL,
			.flags = 0,
			.renderPass = frameBufferStruct.render_pass,
			.attachmentCount = static_cast<uint32_t>(attachmentIdx),
			.pAttachments = attachments,
			.width = colorBufferTexture != nullptr?colorBufferTexture->width:depthBufferTexture->width,
			.height = colorBufferTexture != nullptr?colorBufferTexture->height:depthBufferTexture->height,
			.layers = 1
		};
		err = vkCreateFramebuffer(device, &fb_info, NULL, &frameBufferStruct.frame_buffer);
		assert(!err);
	}

}

int32_t VKRenderer::createFramebufferObject(int32_t depthBufferTextureGlId, int32_t colorBufferTextureGlId)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + to_string(depthBufferTextureGlId) + ",  " + to_string(colorBufferTextureGlId));

	auto& frameBufferStruct = framebuffers[framebuffer_idx];
	frameBufferStruct.id = framebuffer_idx++;
	frameBufferStruct.depth_texture_id = depthBufferTextureGlId;
	frameBufferStruct.color_texture_id = colorBufferTextureGlId;

	//
	createFramebufferObject(frameBufferStruct.id);

	return frameBufferStruct.id;
}

void VKRenderer::bindFrameBuffer(int32_t frameBufferId)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + to_string(frameBufferId));

	//
	if (frameBufferId != 0) {
		auto frameBufferIt = framebuffers.find(frameBufferId);
		if (frameBufferIt == framebuffers.end()) {
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): framebuffer not found: " + to_string(frameBufferId));
			frameBufferId = 0;
		}
	}
	flushCommandsAllContexts();
	endRenderPass();
	memoryBarrier();

	bound_frame_buffer = frameBufferId;

	if (bound_frame_buffer != 0) {
		auto frameBufferIt = framebuffers.find(bound_frame_buffer);
		if (frameBufferIt == framebuffers.end()) {
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): framebuffer not found: " + to_string(bound_frame_buffer));
		} else {
			auto depthBufferTextureId = frameBufferIt->second.depth_texture_id;
			auto colorBufferTextureId = frameBufferIt->second.color_texture_id;
			prepareSetupCommandBuffer();
			if (depthBufferTextureId != 0) {
				auto& depth_buffer_texture = textures[depthBufferTextureId];
				if (depth_buffer_texture.image_layout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL) {
					setImageLayout(
						depth_buffer_texture.image,
						VK_IMAGE_ASPECT_DEPTH_BIT,
						VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL,
						VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
						(VkAccessFlagBits)0
					);
					depth_buffer_texture.image_layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
				}
			}
			if (colorBufferTextureId != 0) {
				auto& color_buffer_texture = textures[colorBufferTextureId];
				if (color_buffer_texture.image_layout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
					setImageLayout(
						color_buffer_texture.image,
						VK_IMAGE_ASPECT_COLOR_BIT,
						VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
						VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
						(VkAccessFlagBits)0
					);
					color_buffer_texture.image_layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
				}
			}
			finishSetupCommandBuffer();
		}
	}

}

void VKRenderer::disposeFrameBufferObject(int32_t frameBufferId)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + to_string(frameBufferId));
	auto frameBufferIt = framebuffers.find(frameBufferId);
	if (frameBufferIt == framebuffers.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): framebuffer not found: " + to_string(frameBufferId));
		return;
	}
	vkDestroyFramebuffer(device, frameBufferIt->second.frame_buffer, NULL);
	framebuffers.erase(frameBufferIt);
}

vector<int32_t> VKRenderer::createBufferObjects(int32_t bufferCount, bool useGPUMemory)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	vector<int32_t> bufferIds;
	buffers_rwlock.writeLock();
	for (auto i = 0; i < bufferCount; i++) {
		buffer_object& buffer = buffers[buffer_idx];
		buffer.id = buffer_idx++;
		buffer.useGPUMemory = useGPUMemory;
		bufferIds.push_back(buffer.id);
	}
	buffers_rwlock.unlock();
	return bufferIds;
}

VkBuffer VKRenderer::getBufferObjectInternal(int32_t bufferObjectId, uint32_t& size) {
	if (VERBOSE == true) Console::println("getBufferObjectInternal::" + string(__FUNCTION__) + "()");
	buffers_rwlock.readLock();
	auto bufferIt = buffers.find(bufferObjectId);
	if (bufferIt == buffers.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): buffer with id " + to_string(bufferObjectId) + " does not exist");
		buffers_rwlock.unlock();
		return VK_NULL_HANDLE;
	}
	if (bufferIt->second.current_buffer == nullptr) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): buffer with id " + to_string(bufferObjectId) + " has no current data attached");
		buffers_rwlock.unlock();
		return VK_NULL_HANDLE;
	}
	auto buffer = bufferIt->second.current_buffer;
	buffers_rwlock.unlock();
	size = buffer->size;
	buffer->frame_used_last = frame;
	return buffer->buf;
}

void VKRenderer::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) {
	 //
	VkResult err;

	const VkBufferCreateInfo buf_info = {
		.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.size = static_cast<uint32_t>(size),
		.usage = usage,
		.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
		.queueFamilyIndexCount = 0,
		.pQueueFamilyIndices = NULL
	};
	VkMemoryAllocateInfo mem_alloc = {
		.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		.pNext = NULL,
		.allocationSize = 0,
		.memoryTypeIndex = 0
	};

	err = vkCreateBuffer(device, &buf_info, NULL, &buffer);
	assert(err == VK_SUCCESS);

	VkMemoryRequirements mem_reqs;
	vkGetBufferMemoryRequirements(device, buffer, &mem_reqs);

	auto pass = memoryTypeFromProperties(mem_reqs.memoryTypeBits, properties,
	&mem_alloc.memoryTypeIndex);
	assert(pass);

	//
	mem_alloc.allocationSize = mem_reqs.size;
	err = vkAllocateMemory(device, &mem_alloc, NULL, &bufferMemory);
	assert(err == VK_SUCCESS);

	vkBindBufferMemory(device, buffer, bufferMemory, 0);
}

void VKRenderer::uploadBufferObjectInternal(int32_t bufferObjectId, int32_t size, const uint8_t* data, VkBufferUsageFlagBits usage) {
	if (size == 0) return;

	buffers_rwlock.readLock();
	auto bufferIt = buffers.find(bufferObjectId);
	if (bufferIt == buffers.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): buffer with id " + to_string(bufferObjectId) + " does not exist");
		buffers_rwlock.unlock();
		return;
	}
	auto& buffer = bufferIt->second;
	buffers_rwlock.unlock();

	//
	VkResult err;

	// find a reusable buffer
	buffer_object::reusable_buffer* reusableBuffer = nullptr;
	auto reusableBuffersIt = buffer.buffers.find(size);
	if (reusableBuffersIt != buffer.buffers.end()) {
		for (auto& reusableBufferCandidate: reusableBuffersIt->second) {
			if (reusableBufferCandidate.frame_used_last < frame) {
				reusableBuffer = &reusableBufferCandidate;
				break;
			}
		}
	}

	// nope check if to reuse a bigger one
	if (reusableBuffer == nullptr) {
		for (auto& bufferIt: buffer.buffers) {
			if (bufferIt.first >= size) {
				auto& buffers = bufferIt.second;
				for (auto& reusableBufferCandidate: buffers) {
					if (reusableBufferCandidate.frame_used_last < frame) {
						reusableBuffer = &reusableBufferCandidate;
						break;
					}
				}
			}
			if (reusableBuffer != nullptr) break;
		}
	}

	// nope, create one
	if (reusableBuffer == nullptr) {
		buffer.buffers[size].push_back(buffer_object::reusable_buffer());
		reusableBuffer = &buffer.buffers[size].back();
		buffer.buffer_count++;
	}

	// create buffer
	if (buffer.useGPUMemory == true) {
		prepareSetupCommandBuffer();

		void* stagingData;
		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;
		VkDeviceSize stagingBufferAllocationSize;
		createBuffer(size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

		// mark staging buffer for deletion when finishing frame
		delete_buffers.push_back(stagingBuffer);
		delete_memory.push_back(stagingBufferMemory);

		// create GPU buffer if not yet done
		if (reusableBuffer->size == 0) {
			createBuffer(size, usage, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, reusableBuffer->buf, reusableBuffer->mem);
			reusableBuffer->size = size;
		}

		// map memory
		err = vkMapMemory(device, stagingBufferMemory, 0, size, 0, &stagingData);
		assert(err == VK_SUCCESS);

		// copy to staging buffer
		memcpy(stagingData, data, size);

		// flush
		VkMappedMemoryRange mappedMemoryRange = {
			.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
			.pNext = NULL,
			.memory = stagingBufferMemory,
			.offset = 0,
			.size = VK_WHOLE_SIZE
		};
		vkFlushMappedMemoryRanges(device, 1, &mappedMemoryRange);

		// copy to GPU buffer
		VkBufferCopy copyRegion = {
			.srcOffset = 0,
			.dstOffset = 0,
			.size = static_cast<VkDeviceSize>(size)
		};
		vkCmdCopyBuffer(setup_cmd, stagingBuffer, reusableBuffer->buf, 1, &copyRegion);
	} else {
		if (reusableBuffer->size == 0) {
			createBuffer(size, usage, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, reusableBuffer->buf, reusableBuffer->mem);

			//
			reusableBuffer->size = size;

			// map memory
			err = vkMapMemory(device, reusableBuffer->mem, 0, reusableBuffer->size, 0, &reusableBuffer->data);
			assert(err == VK_SUCCESS);
		}

		// copy to buffer
		memcpy(reusableBuffer->data, data, size);

		// flush
		VkMappedMemoryRange mappedMemoryRange = {
			.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
			.pNext = NULL,
			.memory = reusableBuffer->mem,
			.offset = 0,
			.size = VK_WHOLE_SIZE
		};
		vkFlushMappedMemoryRanges(device, 1, &mappedMemoryRange);
	}

	// frame and current buffer
	reusableBuffer->frame_used_last = frame;
	buffer.current_buffer = reusableBuffer;

	// clean up
	vector<int> buffersToRemove;
	if (buffer.buffer_count > 1 && frame >= buffer.frame_cleaned_last + 60) {
		vector<int> bufferArraysToRemove;
		for (auto& reusableBuffersIt: buffer.buffers) {
			auto i = 0;
			buffersToRemove.clear();
			auto& bufferList = reusableBuffersIt.second;
			for (auto& reusableBufferCandidate: bufferList) {
				if (frame >= reusableBufferCandidate.frame_used_last + 60) {
					vkDestroyBuffer(device, reusableBufferCandidate.buf, NULL);
					vkUnmapMemory(device, reusableBufferCandidate.mem);
					vkFreeMemory(device, reusableBufferCandidate.mem, NULL);
					buffersToRemove.push_back(i - buffersToRemove.size());
				}
				i++;
			}
			if (buffersToRemove.size() == bufferList.size()) {
				bufferArraysToRemove.push_back(reusableBuffersIt.first);
			} else {
				for (auto bufferToRemove: buffersToRemove) {
					auto listIt = bufferList.begin();
					advance(listIt, bufferToRemove);
					bufferList.erase(listIt);
					buffer.buffer_count--;
				}
			}
		}
		for (auto bufferArrayToRemove: bufferArraysToRemove) {
			buffer.buffer_count-= buffer.buffers.find(bufferArrayToRemove)->second.size();
			buffer.buffers.erase(bufferArrayToRemove);
		}
		buffer.frame_cleaned_last = frame;
	}
}

void VKRenderer::uploadBufferObject(int32_t bufferObjectId, int32_t size, FloatBuffer* data)
{
	uploadBufferObjectInternal(bufferObjectId, size, data->getBuffer(), (VkBufferUsageFlagBits)(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT));
}

void VKRenderer::uploadIndicesBufferObject(int32_t bufferObjectId, int32_t size, ShortBuffer* data)
{
	uploadBufferObjectInternal(bufferObjectId, size, data->getBuffer(), (VkBufferUsageFlagBits)(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT));
}

void VKRenderer::uploadIndicesBufferObject(int32_t bufferObjectId, int32_t size, IntBuffer* data)
{
	uploadBufferObjectInternal(bufferObjectId, size, data->getBuffer(), (VkBufferUsageFlagBits)(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT));
}

void VKRenderer::bindIndicesBufferObject(void* context, int32_t bufferObjectId)
{
	(*static_cast<context_type*>(context)).bound_indices_buffer = bufferObjectId;
}

void VKRenderer::bindTextureCoordinatesBufferObject(void* context, int32_t bufferObjectId)
{
	(*static_cast<context_type*>(context)).bound_buffers[2] = bufferObjectId;
}

void VKRenderer::bindVerticesBufferObject(void* context, int32_t bufferObjectId)
{
	(*static_cast<context_type*>(context)).bound_buffers[0] = bufferObjectId;
}

void VKRenderer::bindNormalsBufferObject(void* context, int32_t bufferObjectId)
{
	(*static_cast<context_type*>(context)).bound_buffers[1] = bufferObjectId;
}

void VKRenderer::bindColorsBufferObject(void* context, int32_t bufferObjectId)
{
	(*static_cast<context_type*>(context)).bound_buffers[3] = bufferObjectId;
}

void VKRenderer::bindTangentsBufferObject(void* context, int32_t bufferObjectId)
{
	(*static_cast<context_type*>(context)).bound_buffers[4] = bufferObjectId;
}

void VKRenderer::bindBitangentsBufferObject(void* context, int32_t bufferObjectId)
{
	(*static_cast<context_type*>(context)).bound_buffers[5] = bufferObjectId;
}

void VKRenderer::bindModelMatricesBufferObject(void* context, int32_t bufferObjectId)
{
	(*static_cast<context_type*>(context)).bound_buffers[6] = bufferObjectId;
}

void VKRenderer::bindEffectColorMulsBufferObject(void* context, int32_t bufferObjectId)
{
	(*static_cast<context_type*>(context)).bound_buffers[7] = bufferObjectId;
}

void VKRenderer::bindEffectColorAddsBufferObject(void* context, int32_t bufferObjectId)
{
	(*static_cast<context_type*>(context)).bound_buffers[8] = bufferObjectId;
}

void VKRenderer::drawInstancedIndexedTrianglesFromBufferObjects(void* context, int32_t triangles, int32_t trianglesOffset, int32_t instances) {
	uint32_t indicesBufferSize;
	drawInstancedTrianglesFromBufferObjects(context, triangles, trianglesOffset, getBufferObjectInternal((*static_cast<context_type*>(context)).bound_indices_buffer, indicesBufferSize), instances);
}

inline void VKRenderer::drawInstancedTrianglesFromBufferObjects(void* context, int32_t triangles, int32_t trianglesOffset, VkBuffer indicesBuffer, int32_t instances)
{
	//
	auto programIt = programs.find(program_id);
	if (programIt == programs.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program does not exist: " + to_string(program_id));
		return;
	}
	program_type& program = programIt->second;

	// have our context typed
	auto& contextTyped = *static_cast<context_type*>(context);

	//
	auto shaderIdx = 0;
	for (auto& shaderId: program.shader_ids) {
		auto shaderIt = shaders.find(shaderId);
		if (shaderIt == shaders.end()) {
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): shader does not exist: " + to_string(shaderId));
			return;
		}
		auto& shader = shaderIt->second;

		if (shader.ubo_binding_idx == -1) {
			shaderIdx++;
			continue;
		}
		if (contextTyped.uniform_buffers_changed[shaderIdx] == true) {
			uploadBufferObjectInternal(shader.ubo[contextTyped.idx], contextTyped.uniform_buffers[shaderIdx].size(), contextTyped.uniform_buffers[shaderIdx].data(), (VkBufferUsageFlagBits)(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT));
		}
		uint32_t uboBufferSize;
		contextTyped.objects_render_command.ubo_buffers[shader.ubo_binding_idx] = getBufferObjectInternal(shader.ubo[contextTyped.idx], uboBufferSize);
		shaderIdx++;
	}

	for (auto i = 0; i < contextTyped.bound_textures.size(); i++) {
		auto textureId = contextTyped.bound_textures[i];
		if (textureId == 0) continue;
		textures_rwlock.readLock();
		auto textureObjectIt = textures.find(textureId);
		if (textureObjectIt == textures.end()) {
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): texture does not exist: " + to_string(contextTyped.bound_textures[i]));
			textures_rwlock.unlock();
			continue;
		}
		auto& texture_object = textureObjectIt->second;
		textures_rwlock.unlock();
		contextTyped.objects_render_command.textures[i] = {
			.sampler = texture_object.sampler,
			.view = texture_object.view,
			.image_layout = texture_object.image_layout
		};
	}

	//
	uint32_t bufferSize;
	contextTyped.objects_render_command.indices_buffer = indicesBuffer;
	contextTyped.objects_render_command.vertex_buffers[0] = getBufferObjectInternal(contextTyped.bound_buffers[0] == 0?empty_vertex_buffer:contextTyped.bound_buffers[0], bufferSize);
	contextTyped.objects_render_command.vertex_buffers[1] = getBufferObjectInternal(contextTyped.bound_buffers[1] == 0?empty_vertex_buffer:contextTyped.bound_buffers[1], bufferSize);
	contextTyped.objects_render_command.vertex_buffers[2] = getBufferObjectInternal(contextTyped.bound_buffers[2] == 0?empty_vertex_buffer:contextTyped.bound_buffers[2], bufferSize);
	contextTyped.objects_render_command.vertex_buffers[3] = getBufferObjectInternal(contextTyped.bound_buffers[3] == 0?empty_vertex_buffer:contextTyped.bound_buffers[3], bufferSize);
	contextTyped.objects_render_command.vertex_buffers[4] = getBufferObjectInternal(contextTyped.bound_buffers[4] == 0?empty_vertex_buffer:contextTyped.bound_buffers[4], bufferSize);
	contextTyped.objects_render_command.vertex_buffers[5] = getBufferObjectInternal(contextTyped.bound_buffers[5] == 0?empty_vertex_buffer:contextTyped.bound_buffers[5], bufferSize);
	contextTyped.objects_render_command.vertex_buffers[6] = getBufferObjectInternal(contextTyped.bound_buffers[6] == 0?empty_vertex_buffer:contextTyped.bound_buffers[6], bufferSize);
	contextTyped.objects_render_command.vertex_buffers[7] = getBufferObjectInternal(contextTyped.bound_buffers[7] == 0?empty_vertex_buffer:contextTyped.bound_buffers[7], bufferSize);
	contextTyped.objects_render_command.vertex_buffers[8] = getBufferObjectInternal(contextTyped.bound_buffers[8] == 0?empty_vertex_buffer:contextTyped.bound_buffers[8], bufferSize);
	contextTyped.objects_render_command.count = triangles;
	contextTyped.objects_render_command.offset = trianglesOffset;
	contextTyped.objects_render_command.instances = instances;

	//
	contextTyped.uniform_buffers_changed.fill(false);

	//
	contextTyped.command_type = context_type::COMMAND_OBJECTS;
	flushCommands(context);
}

void VKRenderer::drawIndexedTrianglesFromBufferObjects(void* context, int32_t triangles, int32_t trianglesOffset)
{
	// Console::println("VKRenderer::" + string(__FUNCTION__) + "()");

	//
	drawInstancedIndexedTrianglesFromBufferObjects(context, triangles, trianglesOffset, 1);
}

inline void VKRenderer::flushCommandsAllContexts() {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	for (auto& context: contexts) flushCommands(&context);
}

inline void VKRenderer::flushCommands(void* context) {
	// have our context typed
	auto& contextTyped = *static_cast<context_type*>(context);

	Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + to_string(contextTyped.idx));

	finishSetupCommandBuffer();

	//
	draw_cmd_mutex.lock();
	if (clear_mask != 0) {
		if (render_pass_started == false) startRenderPass();

		auto attachmentIdx = 0;
		VkClearAttachment attachments[2];
		if ((clear_mask & CLEAR_COLOR_BUFFER_BIT) == CLEAR_COLOR_BUFFER_BIT) {
			attachments[attachmentIdx].aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			attachments[attachmentIdx].colorAttachment = attachmentIdx;
			attachments[attachmentIdx].clearValue.color = { clear_red, clear_green, clear_blue, clear_alpha };
			attachmentIdx++;
		}
		if ((clear_mask & CLEAR_DEPTH_BUFFER_BIT) == CLEAR_DEPTH_BUFFER_BIT) {
			attachments[attachmentIdx].aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
			attachments[attachmentIdx].colorAttachment = attachmentIdx;
			attachments[attachmentIdx].clearValue.depthStencil = { 1.0f, 0 };
			attachmentIdx++;
		}
		VkClearRect clearRect = {
			.rect = scissor,
			.baseArrayLayer = 0,
			.layerCount = 1
		};
		vkCmdClearAttachments(
			draw_cmd,
			attachmentIdx,
			attachments,
			1,
			&clearRect
		);

		//
		clear_mask = 0;
	}
	draw_cmd_mutex.unlock();

	if (contextTyped.command_type == context_type::COMMAND_NONE) return;

	//
	auto programIt = programs.find(program_id);
	if (programIt == programs.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program does not exist: " + to_string(program_id));
		return;
	}
	auto& program = programIt->second;

	// check if desc left
	if (program.desc_idxs[contextTyped.idx] == DESC_MAX) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program.desc_idxs[" + to_string(contextTyped.idx) + "] == DESC_MAX: " + to_string(program.desc_idxs[contextTyped.idx]));
		return;
	}

	// start draw command buffer, it not yet done
	draw_cmd_mutex.lock();
	if (draw_cmd_started == false) {
		const VkCommandBufferBeginInfo cmd_buf_info = {
			.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
			.pNext = NULL,
			.flags = 0,
			.pInheritanceInfo = NULL
		};
		//
		VkResult err;
		err = vkBeginCommandBuffer(draw_cmd, &cmd_buf_info);
		assert(!err);
		draw_cmd_started = true;
	}

	// create pipeline
	if (contextTyped.command_type == context_type::COMMAND_OBJECTS) {
		if (render_pass_started == false) startRenderPass();
		setupObjectsRenderingPipeline(program);
	} else
	if (contextTyped.command_type == context_type::COMMAND_POINTS) {
		if (render_pass_started == false) startRenderPass();
		setupPointsRenderingPipeline(program);
	} else
		if (contextTyped.command_type == context_type::COMMAND_COMPUTE) {
		setupSkinningComputingPipeline(program);
	} else {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): unknown pipeline: " + to_string(program_id));
		return;
	}
	draw_cmd_mutex.unlock();

	VkDescriptorBufferInfo bufferInfos[program.layout_bindings];
	VkWriteDescriptorSet descriptorSetWrites[program.layout_bindings];
	VkDescriptorImageInfo texDescs[program.layout_bindings];

	// do object render command
	if (contextTyped.command_type == context_type::COMMAND_OBJECTS) {
		if (render_pass_started == false) startRenderPass();

		//
		auto samplerIdx = 0;
		for (auto& shaderId: program.shader_ids) {
			auto shaderIt = shaders.find(shaderId);
			if (shaderIt == shaders.end()) {
				Console::println("VKRenderer::" + string(__FUNCTION__) + "(): shader does not exist: " + to_string(shaderId));
				return;
			}
			auto& shader = shaderIt->second;

			// sampler2D
			for (auto uniformIt: shader.uniforms) {
				auto& uniform = uniformIt.second;
				if (uniform.type != shader_type::uniform_type::SAMPLER2D) continue;
				auto commandTextureIt = contextTyped.objects_render_command.textures.find(uniform.texture_unit);
				if (commandTextureIt == contextTyped.objects_render_command.textures.end()) {
					textures_rwlock.readLock();
					auto contextTextureIt = textures.find(white_texture_default);
					auto texture = contextTextureIt->second;
					textures_rwlock.unlock();
					texDescs[samplerIdx] = {
						.sampler = texture.sampler,
						.imageView = texture.view,
						.imageLayout = texture.image_layout
					};
				} else {
					auto& texture = commandTextureIt->second;
					texDescs[samplerIdx] = {
						.sampler = texture.sampler,
						.imageView = texture.view,
						.imageLayout = texture.image_layout
					};
				}
				descriptorSetWrites[uniform.position] = {
					.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
					.pNext = NULL,
					.dstSet = program.desc_sets[contextTyped.idx][program.desc_idxs[contextTyped.idx]],
					.dstBinding = static_cast<uint32_t>(uniform.position),
					.dstArrayElement = 0,
					.descriptorCount = 1,
					.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
					.pImageInfo = &texDescs[samplerIdx],
					.pBufferInfo = VK_NULL_HANDLE,
					.pTexelBufferView = VK_NULL_HANDLE
				};
				samplerIdx++;
			}

			// uniform buffer
			if (shader.ubo_binding_idx == -1) {
				continue;
			}

			bufferInfos[shader.ubo_binding_idx] = {
				.buffer = contextTyped.objects_render_command.ubo_buffers[shader.ubo_binding_idx],
				.offset = 0,
				.range = shader.ubo_size
			};

			descriptorSetWrites[shader.ubo_binding_idx] = {
				.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
				.pNext = NULL,
				.dstSet = program.desc_sets[contextTyped.idx][program.desc_idxs[contextTyped.idx]],
				.dstBinding = static_cast<uint32_t>(shader.ubo_binding_idx),
				.dstArrayElement = 0,
				.descriptorCount = 1,
				.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
				.pImageInfo = NULL,
				.pBufferInfo = &bufferInfos[shader.ubo_binding_idx],
				.pTexelBufferView = NULL
			};
		}

		//
		vkUpdateDescriptorSets(device, program.layout_bindings, descriptorSetWrites, 0, NULL);

		//
		#define OBJECTSRENDERCOMMAND_VERTEX_BUFFER_COUNT	9
		VkBuffer vertexBuffersBuffer[OBJECTSRENDERCOMMAND_VERTEX_BUFFER_COUNT] = {
			contextTyped.objects_render_command.vertex_buffers[0],
			contextTyped.objects_render_command.vertex_buffers[1],
			contextTyped.objects_render_command.vertex_buffers[2],
			contextTyped.objects_render_command.vertex_buffers[3],
			contextTyped.objects_render_command.vertex_buffers[4],
			contextTyped.objects_render_command.vertex_buffers[5],
			contextTyped.objects_render_command.vertex_buffers[6],
			contextTyped.objects_render_command.vertex_buffers[7],
			contextTyped.objects_render_command.vertex_buffers[8]
		};
		VkDeviceSize vertexBuffersOffsets[OBJECTSRENDERCOMMAND_VERTEX_BUFFER_COUNT] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

		//
		draw_cmd_mutex.lock();
		vkCmdBindDescriptorSets(draw_cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, program.pipeline_layout, 0, 1, &program.desc_sets[contextTyped.idx][program.desc_idxs[contextTyped.idx]], 0, nullptr);
		if (contextTyped.objects_render_command.indices_buffer != VK_NULL_HANDLE) vkCmdBindIndexBuffer(draw_cmd, contextTyped.objects_render_command.indices_buffer, 0, VK_INDEX_TYPE_UINT32);
		vkCmdBindVertexBuffers(draw_cmd, 0, OBJECTSRENDERCOMMAND_VERTEX_BUFFER_COUNT, vertexBuffersBuffer, vertexBuffersOffsets);
		if (contextTyped.objects_render_command.indices_buffer != VK_NULL_HANDLE) {
			vkCmdDrawIndexed(draw_cmd, contextTyped.objects_render_command.count * 3, contextTyped.objects_render_command.instances, contextTyped.objects_render_command.offset * 3, 0, 0);
		} else {
			vkCmdDraw(draw_cmd, contextTyped.objects_render_command.count * 3, contextTyped.objects_render_command.instances, contextTyped.objects_render_command.offset * 3, 0);
		}
		draw_cmd_mutex.unlock();

		//
		program.desc_idxs[contextTyped.idx]++;
	} else
	if (contextTyped.command_type == context_type::COMMAND_POINTS) {
		if (render_pass_started == false) startRenderPass();

		// do points render command
		auto samplerIdx = 0;
		for (auto& shaderId: program.shader_ids) {
			auto shaderIt = shaders.find(shaderId);
			if (shaderIt == shaders.end()) {
				Console::println("VKRenderer::" + string(__FUNCTION__) + "(): shader does not exist: " + to_string(shaderId));
				return;
			}
			auto& shader = shaderIt->second;

			// sampler2D
			for (auto uniformIt: shader.uniforms) {
				auto& uniform = uniformIt.second;
				if (uniform.type != shader_type::uniform_type::SAMPLER2D) continue;
				auto commandTextureIt = contextTyped.points_render_command.textures.find(uniform.texture_unit);
				if (commandTextureIt == contextTyped.points_render_command.textures.end()) {
					textures_rwlock.readLock();
					auto contextTextureIt = textures.find(white_texture_default);
					auto texture = contextTextureIt->second;
					textures_rwlock.unlock();
					texDescs[samplerIdx] = {
						.sampler = texture.sampler,
						.imageView = texture.view,
						.imageLayout = texture.image_layout
					};
				} else {
					auto& texture = commandTextureIt->second;
					texDescs[samplerIdx] = {
						.sampler = texture.sampler,
						.imageView = texture.view,
						.imageLayout = texture.image_layout
					};
				}
				descriptorSetWrites[uniform.position] = {
					.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
					.pNext = NULL,
					.dstSet = program.desc_sets[contextTyped.idx][program.desc_idxs[contextTyped.idx]],
					.dstBinding = static_cast<uint32_t>(uniform.position),
					.dstArrayElement = 0,
					.descriptorCount = 1,
					.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
					.pImageInfo = &texDescs[samplerIdx],
					.pBufferInfo = VK_NULL_HANDLE,
					.pTexelBufferView = VK_NULL_HANDLE
				};
				samplerIdx++;
			}

			// uniform buffer
			if (shader.ubo_binding_idx == -1) {
				continue;
			}

			bufferInfos[shader.ubo_binding_idx] = {
				.buffer = contextTyped.points_render_command.ubo_buffers[shader.ubo_binding_idx],
				.offset = 0,
				.range = shader.ubo_size
			};

			descriptorSetWrites[shader.ubo_binding_idx] = {
				.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
				.pNext = NULL,
				.dstSet = program.desc_sets[contextTyped.idx][program.desc_idxs[contextTyped.idx]],
				.dstBinding = static_cast<uint32_t>(shader.ubo_binding_idx),
				.dstArrayElement = 0,
				.descriptorCount = 1,
				.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
				.pImageInfo = NULL,
				.pBufferInfo = &bufferInfos[shader.ubo_binding_idx],
				.pTexelBufferView = NULL
			};
		}

		//
		vkUpdateDescriptorSets(device, program.layout_bindings, descriptorSetWrites, 0, NULL);

		//
		#define POINTSRENDERCOMMAND_VERTEX_BUFFER_COUNT	4
		VkBuffer vertexBuffersBuffer[POINTSRENDERCOMMAND_VERTEX_BUFFER_COUNT] = {
			contextTyped.points_render_command.vertex_buffers[0],
			contextTyped.points_render_command.vertex_buffers[1],
			contextTyped.points_render_command.vertex_buffers[2],
			contextTyped.points_render_command.vertex_buffers[3]
		};

		//
		draw_cmd_mutex.lock();
		vkCmdBindDescriptorSets(draw_cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, program.pipeline_layout, 0, 1, &program.desc_sets[contextTyped.idx][program.desc_idxs[contextTyped.idx]], 0, nullptr);
		VkDeviceSize vertexBuffersOffsets[POINTSRENDERCOMMAND_VERTEX_BUFFER_COUNT] = { 0, 0, 0, 0 };
		vkCmdBindVertexBuffers(draw_cmd, 0, POINTSRENDERCOMMAND_VERTEX_BUFFER_COUNT, vertexBuffersBuffer, vertexBuffersOffsets);
		vkCmdDraw(draw_cmd, contextTyped.points_render_command.count, 1, contextTyped.points_render_command.offset, 0);
		draw_cmd_mutex.unlock();

		//
		program.desc_idxs[contextTyped.idx]++;
	} else
	if (contextTyped.command_type == context_type::COMMAND_COMPUTE) {
		if (render_pass_started == true) endRenderPass();

		// do compute command
		for (auto& shaderId: program.shader_ids) {
			auto shaderIt = shaders.find(shaderId);
			if (shaderIt == shaders.end()) {
				Console::println("VKRenderer::" + string(__FUNCTION__) + "(): shader does not exist: " + to_string(shaderId));
				return;
			}
			auto& shader = shaderIt->second;
			for (int i = 0; i <= shader.binding_max; i++) {
				bufferInfos[i] = {
					.buffer = contextTyped.compute_command.storage_buffers[i],
					.offset = 0,
					.range = contextTyped.compute_command.storage_buffer_sizes[i]
				};
				descriptorSetWrites[i] = {
					.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
					.pNext = NULL,
					.dstSet = program.desc_sets[contextTyped.idx][program.desc_idxs[contextTyped.idx]],
					.dstBinding = static_cast<uint32_t>(i),
					.dstArrayElement = 0,
					.descriptorCount = 1,
					.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
					.pImageInfo = NULL,
					.pBufferInfo = &bufferInfos[i],
					.pTexelBufferView = NULL
				};
			}

			// uniform buffer
			if (shader.ubo_binding_idx == -1) {
				continue;
			}

			bufferInfos[shader.ubo_binding_idx] = {
				.buffer = contextTyped.compute_command.ubo_buffers[0],
				.offset = 0,
				.range = shader.ubo_size
			};

			descriptorSetWrites[shader.ubo_binding_idx] = {
				.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
				.pNext = NULL,
				.dstSet = program.desc_sets[contextTyped.idx][program.desc_idxs[contextTyped.idx]],
				.dstBinding = static_cast<uint32_t>(shader.ubo_binding_idx),
				.dstArrayElement = 0,
				.descriptorCount = 1,
				.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
				.pImageInfo = NULL,
				.pBufferInfo = &bufferInfos[shader.ubo_binding_idx],
				.pTexelBufferView = NULL,
			};
		}

		//
		vkUpdateDescriptorSets(device, program.layout_bindings, descriptorSetWrites, 0, NULL);

		//
		draw_cmd_mutex.lock();
		vkCmdBindDescriptorSets(draw_cmd, VK_PIPELINE_BIND_POINT_COMPUTE, program.pipeline_layout, 0, 1, &program.desc_sets[contextTyped.idx][program.desc_idxs[contextTyped.idx]], 0, nullptr);
		vkCmdDispatch(draw_cmd, contextTyped.compute_command.num_groups_x, contextTyped.compute_command.num_groups_y, contextTyped.compute_command.num_groups_z);
		draw_cmd_mutex.unlock();

		//
		program.desc_idxs[contextTyped.idx]++;
	}

	contextTyped.command_type = context_type::COMMAND_NONE;
}

void VKRenderer::drawInstancedTrianglesFromBufferObjects(void* context, int32_t triangles, int32_t trianglesOffset, int32_t instances)
{
	drawInstancedTrianglesFromBufferObjects(context, triangles, trianglesOffset, VK_NULL_HANDLE, instances);
}

void VKRenderer::drawTrianglesFromBufferObjects(void* context, int32_t triangles, int32_t trianglesOffset)
{
	drawInstancedTrianglesFromBufferObjects(context, triangles, trianglesOffset, VK_NULL_HANDLE, 1);
}

void VKRenderer::drawPointsFromBufferObjects(void* context, int32_t points, int32_t pointsOffset)
{
	// Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + to_string(points) + " / " + to_string(pointsOffset));
	// upload uniforms
	auto programIt = programs.find(program_id);
	if (programIt == programs.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program does not exist: " + to_string(program_id));
		return;
	}
	program_type& program = programIt->second;

	// have our context typed
	auto& contextTyped = *static_cast<context_type*>(context);

	auto shaderIdx = 0;
	for (auto& shaderId: program.shader_ids) {
		auto shaderIt = shaders.find(shaderId);
		if (shaderIt == shaders.end()) {
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): shader does not exist: " + to_string(shaderId));
			return;
		}
		auto& shader = shaderIt->second;

		if (shader.ubo_binding_idx == -1) {
			shaderIdx++;
			continue;
		}
		if (contextTyped.uniform_buffers_changed[shaderIdx] == true) {
			uploadBufferObjectInternal(shader.ubo[contextTyped.idx], contextTyped.uniform_buffers[shaderIdx].size(), contextTyped.uniform_buffers[shaderIdx].data(), (VkBufferUsageFlagBits)(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT));
		}
		uint32_t uboBufferSize;
		contextTyped.points_render_command.ubo_buffers[shader.ubo_binding_idx] = getBufferObjectInternal(shader.ubo[contextTyped.idx], uboBufferSize);
		shaderIdx++;
	}

	for (auto i = 0; i < contextTyped.bound_textures.size(); i++) {
		auto textureId = contextTyped.bound_textures[i];
		if (textureId == 0) continue;
		textures_rwlock.readLock();
		auto textureObjectIt = textures.find(textureId);
		if (textureObjectIt == textures.end()) {
			textures_rwlock.unlock();
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): texture does not exist: " + to_string(contextTyped.bound_textures[i]));
			continue;
		}
		auto& texture_object = textureObjectIt->second;
		textures_rwlock.unlock();
		contextTyped.points_render_command.textures[i] = {
			.sampler = texture_object.sampler,
			.view = texture_object.view,
			.image_layout = texture_object.image_layout
		};
	}

	//
	uint32_t bufferSize;
	contextTyped.points_render_command.vertex_buffers[0] = getBufferObjectInternal(contextTyped.bound_buffers[0] == 0?empty_vertex_buffer:contextTyped.bound_buffers[0], bufferSize);
	contextTyped.points_render_command.vertex_buffers[1] = getBufferObjectInternal(contextTyped.bound_buffers[1] == 0?empty_vertex_buffer:contextTyped.bound_buffers[1], bufferSize);
	contextTyped.points_render_command.vertex_buffers[2] = getBufferObjectInternal(contextTyped.bound_buffers[2] == 0?empty_vertex_buffer:contextTyped.bound_buffers[2], bufferSize);
	contextTyped.points_render_command.vertex_buffers[3] = getBufferObjectInternal(contextTyped.bound_buffers[3] == 0?empty_vertex_buffer:contextTyped.bound_buffers[3], bufferSize);
	contextTyped.points_render_command.count = points;
	contextTyped.points_render_command.offset = pointsOffset;

	//
	contextTyped.uniform_buffers_changed.fill(false);

	//
	contextTyped.command_type = context_type::COMMAND_POINTS;
	flushCommands(context);
}

void VKRenderer::unbindBufferObjects(void* context)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	(*static_cast<context_type*>(context)).bound_indices_buffer = 0;
	(*static_cast<context_type*>(context)).bound_buffers.fill(0);
}

void VKRenderer::disposeBufferObjects(vector<int32_t>& bufferObjectIds)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	for (auto bufferObjectId: bufferObjectIds) {
		auto bufferIt = buffers.find(bufferObjectId);
		if (bufferIt == buffers.end()) {
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): buffer with id " + to_string(bufferObjectId) + " does not exist");
			continue;
		}
		auto& buffer = bufferIt->second;
		for (auto bufferIt: buffer.buffers) {
			for (auto& reusableBuffer: bufferIt.second) {
				if (reusableBuffer.size == 0) continue;
				vkDestroyBuffer(device, reusableBuffer.buf, NULL);
				vkFreeMemory(device, reusableBuffer.mem, NULL);
			}
		}
		buffers.erase(bufferIt);
	}
}

int32_t VKRenderer::getTextureUnit(void* context)
{
	return (*static_cast<context_type*>(context)).texture_unit_active;
}

void VKRenderer::setTextureUnit(void* context, int32_t textureUnit)
{
	(*static_cast<context_type*>(context)).texture_unit_active = textureUnit;
}

float VKRenderer::readPixelDepth(int32_t x, int32_t y)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return 0.0f;
}

ByteBuffer* VKRenderer::readPixels(int32_t x, int32_t y, int32_t width, int32_t height)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return nullptr;
}

void VKRenderer::initGuiMode()
{
	disableCulling();
	disableDepthBufferTest();
	disableDepthBufferWriting();
}

void VKRenderer::doneGuiMode()
{
	enableDepthBufferWriting();
	enableDepthBufferTest();
	enableCulling();
}

void VKRenderer::dispatchCompute(void* context, int32_t numGroupsX, int32_t numGroupsY, int32_t numGroupsZ) {
	auto programIt = programs.find(program_id);
	if (programIt == programs.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program does not exist: " + to_string(program_id));
		return;
	}
	program_type& program = programIt->second;

	// have our context typed
	auto& contextTyped = *static_cast<context_type*>(context);

	//
	auto shaderIdx = 0;
	for (auto& shaderId: program.shader_ids) {
		auto shaderIt = shaders.find(shaderId);
		if (shaderIt == shaders.end()) {
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): shader does not exist: " + to_string(shaderId));
			return;
		}
		auto& shader = shaderIt->second;

		if (shader.ubo_binding_idx == -1) {
			shaderIdx++;
			continue;
		}
		if (contextTyped.uniform_buffers_changed[shaderIdx] == true) {
			uploadBufferObjectInternal(shader.ubo[contextTyped.idx], contextTyped.uniform_buffers[shaderIdx].size(), contextTyped.uniform_buffers[shaderIdx].data(), (VkBufferUsageFlagBits)(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT));
		}
		uint32_t uboBufferSize;
		contextTyped.compute_command.ubo_buffers[0] = getBufferObjectInternal(shader.ubo[contextTyped.idx], uboBufferSize); // TODO: do not use static 0 ubo buffer
		shaderIdx++;
	}

	// TODO: improve me to only use one buffer map lookup
	contextTyped.compute_command.storage_buffers[0] = getBufferObjectInternal(contextTyped.bound_buffers[0] == 0?empty_vertex_buffer:contextTyped.bound_buffers[0], contextTyped.compute_command.storage_buffer_sizes[0]);
	contextTyped.compute_command.storage_buffers[1] = getBufferObjectInternal(contextTyped.bound_buffers[1] == 0?empty_vertex_buffer:contextTyped.bound_buffers[1], contextTyped.compute_command.storage_buffer_sizes[1]);
	contextTyped.compute_command.storage_buffers[2] = getBufferObjectInternal(contextTyped.bound_buffers[2] == 0?empty_vertex_buffer:contextTyped.bound_buffers[2], contextTyped.compute_command.storage_buffer_sizes[2]);
	contextTyped.compute_command.storage_buffers[3] = getBufferObjectInternal(contextTyped.bound_buffers[3] == 0?empty_vertex_buffer:contextTyped.bound_buffers[3], contextTyped.compute_command.storage_buffer_sizes[3]);
	contextTyped.compute_command.storage_buffers[4] = getBufferObjectInternal(contextTyped.bound_buffers[4] == 0?empty_vertex_buffer:contextTyped.bound_buffers[4], contextTyped.compute_command.storage_buffer_sizes[4]);
	contextTyped.compute_command.storage_buffers[5] = getBufferObjectInternal(contextTyped.bound_buffers[5] == 0?empty_vertex_buffer:contextTyped.bound_buffers[5], contextTyped.compute_command.storage_buffer_sizes[5]);
	contextTyped.compute_command.storage_buffers[6] = getBufferObjectInternal(contextTyped.bound_buffers[6] == 0?empty_vertex_buffer:contextTyped.bound_buffers[6], contextTyped.compute_command.storage_buffer_sizes[6]);
	contextTyped.compute_command.storage_buffers[7] = getBufferObjectInternal(contextTyped.bound_buffers[7] == 0?empty_vertex_buffer:contextTyped.bound_buffers[7], contextTyped.compute_command.storage_buffer_sizes[7]);
	contextTyped.compute_command.num_groups_x = numGroupsX;
	contextTyped.compute_command.num_groups_y = numGroupsY;
	contextTyped.compute_command.num_groups_z = numGroupsZ;

	//
	contextTyped.uniform_buffers_changed.fill(false);

	//
	contextTyped.command_type = context_type::COMMAND_COMPUTE;
	flushCommands(context);
}

void VKRenderer::memoryBarrier() {
	VkResult err;

	auto inRenderPass = render_pass_started;
	if (inRenderPass == true) endRenderPass();

	//
	if (setup_cmd != VK_NULL_HANDLE) {
		assert(!err);
		err = vkEndCommandBuffer(setup_cmd);
	}

	if (draw_cmd_started == true) {
		err = vkEndCommandBuffer(draw_cmd);
		pipeline = VK_NULL_HANDLE;
		assert(!err);
	}

	const VkCommandBuffer cmd_bufs[] = { draw_cmd, setup_cmd };

	if (draw_cmd_started == true || setup_cmd != VK_NULL_HANDLE) {
		VkFence nullFence = { VK_NULL_HANDLE };
		VkSubmitInfo submit_info = {
			.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
			.pNext = NULL,
			.waitSemaphoreCount = 0,
			.pWaitSemaphores = NULL,
			.pWaitDstStageMask = NULL,
			.commandBufferCount = static_cast<uint32_t>((draw_cmd_started == true?1:0) + (setup_cmd != VK_NULL_HANDLE?1:0)),
			.pCommandBuffers = draw_cmd_started == true?&cmd_bufs[0]:&cmd_bufs[1],
			.signalSemaphoreCount = 0,
			.pSignalSemaphores = NULL
		};

		err = vkQueueSubmit(queue, 1, &submit_info, nullFence);
		assert(!err);

		err = vkQueueWaitIdle(queue);
		assert(!err);
	}

	if (draw_cmd_started == true) {
		const VkCommandBufferBeginInfo cmd_buf_info = {
			.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
			.pNext = NULL,
			.flags = 0,
			.pInheritanceInfo = NULL
		};

		//
		err = vkBeginCommandBuffer(draw_cmd, &cmd_buf_info);
		assert(!err);
	}

	if (setup_cmd != VK_NULL_HANDLE) {
		vkFreeCommandBuffers(device, cmd_pool, 1, &cmd_bufs[1]);

		//
		setup_cmd = VK_NULL_HANDLE;
	}

	//
	if (inRenderPass == true) startRenderPass();
}

void VKRenderer::uploadSkinningBufferObject(int32_t bufferObjectId, int32_t size, FloatBuffer* data) {
	uploadBufferObjectInternal(bufferObjectId, size, data->getBuffer(), (VkBufferUsageFlagBits)(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT));
}

void VKRenderer::uploadSkinningBufferObject(int32_t bufferObjectId, int32_t size, IntBuffer* data) {
	uploadBufferObjectInternal(bufferObjectId, size, data->getBuffer(), (VkBufferUsageFlagBits)(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT));
}

void VKRenderer::bindSkinningVerticesBufferObject(void* context, int32_t bufferObjectId) {
	(*static_cast<context_type*>(context)).bound_buffers[0] = bufferObjectId;
}

void VKRenderer::bindSkinningNormalsBufferObject(void* context, int32_t bufferObjectId) {
	(*static_cast<context_type*>(context)).bound_buffers[1] = bufferObjectId;
}

void VKRenderer::bindSkinningVertexJointsBufferObject(void* context, int32_t bufferObjectId) {
	(*static_cast<context_type*>(context)).bound_buffers[2] = bufferObjectId;
}

void VKRenderer::bindSkinningVertexJointIdxsBufferObject(void* context, int32_t bufferObjectId) {
	(*static_cast<context_type*>(context)).bound_buffers[3] = bufferObjectId;
}

void VKRenderer::bindSkinningVertexJointWeightsBufferObject(void* context, int32_t bufferObjectId) {
	(*static_cast<context_type*>(context)).bound_buffers[4] = bufferObjectId;
}

void VKRenderer::bindSkinningVerticesResultBufferObject(void* context, int32_t bufferObjectId) {
	(*static_cast<context_type*>(context)).bound_buffers[5] = bufferObjectId;
}

void VKRenderer::bindSkinningNormalsResultBufferObject(void* context, int32_t bufferObjectId) {
	(*static_cast<context_type*>(context)).bound_buffers[6] = bufferObjectId;
}

void VKRenderer::bindSkinningMatricesBufferObject(void* context, int32_t bufferObjectId) {
	(*static_cast<context_type*>(context)).bound_buffers[7] = bufferObjectId;
}
