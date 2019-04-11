/**
 * based on https://github.com/glfw/glfw/blob/master/tests/vulkan.c and util.c from Vulkan samples, https://vulkan-tutorial.com, https://github.com/KhronosGroup/Vulkan-Docs/wiki/Synchronization-Examples
 */

#include <tdme/engine/subsystems/renderer/VKRenderer.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <ext/glslang/Public/ShaderLang.h>
#include <ext/OGLCompilersDLL/InitializeDll.h>
#include <ext/spirv/GlslangToSpv.h>

#include <stdlib.h>
#include <string.h>

#include <array>
#include <cassert>
#include <map>
#include <vector>
#include <stack>
#include <string>


#include <tdme/application/Application.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Timing.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/utils/Buffer.h>
#include <tdme/utils/ByteBuffer.h>
#include <tdme/utils/FloatBuffer.h>
#include <tdme/utils/IntBuffer.h>
#include <tdme/utils/ShortBuffer.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utils/Console.h>
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

#define GET_INSTANCE_PROC_ADDR(context, inst, entrypoint)														\
    {																											\
        context.fp##entrypoint = (PFN_vk##entrypoint)vkGetInstanceProcAddr(inst, "vk" #entrypoint);				\
        if (context.fp##entrypoint == NULL) {																	\
            ERR_EXIT("vkGetInstanceProcAddr failed to find vk" #entrypoint, "vkGetInstanceProcAddr Failure");	\
        }                                                                      									\
    }

#define GET_DEVICE_PROC_ADDR(dev, entrypoint)																	\
    {																											\
        context.fp##entrypoint = (PFN_vk##entrypoint)vkGetDeviceProcAddr(dev, "vk" #entrypoint);				\
        if (context.fp##entrypoint == NULL) {																	\
            ERR_EXIT("vkGetDeviceProcAddr failed to find vk" #entrypoint, "vkGetDeviceProcAddr Failure");		\
        }																										\
    }

using std::array;
using std::map;
using std::stack;
using std::string;
using std::to_string;
using std::vector;

using tdme::engine::subsystems::renderer::VKRenderer;
using tdme::application::Application;
using tdme::engine::Engine;
using tdme::engine::Timing;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::subsystems::manager::TextureManager;

using tdme::utils::Buffer;
using tdme::utils::ByteBuffer;
using tdme::utils::FloatBuffer;
using tdme::utils::IntBuffer;
using tdme::utils::ShortBuffer;
using tdme::engine::Engine;
using tdme::engine::fileio::textures::Texture;
using tdme::math::Matrix4x4;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utils::Console;
using tdme::utils::StringTokenizer;
using tdme::utils::StringUtils;

VKRenderer::VKRenderer()
{
	// setup GL3 consts
	ID_NONE = 0;
	CLEAR_DEPTH_BUFFER_BIT = -1;
	CLEAR_COLOR_BUFFER_BIT = -1;
	CULLFACE_FRONT = -1;
	CULLFACE_BACK = -1;
	FRONTFACE_CW = -1;
	FRONTFACE_CCW = -1;
	SHADER_FRAGMENT_SHADER = VK_SHADER_STAGE_FRAGMENT_BIT;
	SHADER_VERTEX_SHADER = VK_SHADER_STAGE_VERTEX_BIT;
	SHADER_COMPUTE_SHADER = VK_SHADER_STAGE_COMPUTE_BIT;
	SHADER_GEOMETRY_SHADER = VK_SHADER_STAGE_GEOMETRY_BIT;
	DEPTHFUNCTION_ALWAYS = -1;;
	DEPTHFUNCTION_EQUAL = -1;;
	DEPTHFUNCTION_LESSEQUAL = -1;;
	DEPTHFUNCTION_GREATEREQUAL = -1;;
}

bool VKRenderer::memoryTypeFromProperties(uint32_t typeBits, VkFlags requirements_mask, uint32_t *typeIndex) {
    uint32_t i;
    // Search memtypes to find first index with those properties
    for (i = 0; i < VK_MAX_MEMORY_TYPES; i++) {
        if ((typeBits & 1) == 1) {
            // Type is available, does it match user properties?
            if ((context.memory_properties.memoryTypes[i].propertyFlags & requirements_mask) == requirements_mask) {
                *typeIndex = i;
                return true;
            }
        }
        typeBits >>= 1;
    }
    // No memory types matched, return failure
    return false;
}

VkBool32 VKRenderer::checkLayers(uint32_t check_count, const char **check_names, uint32_t layer_count, VkLayerProperties *layers) {
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
	if (context.setup_cmd == VK_NULL_HANDLE) {
		VkResult err;

		const VkCommandBufferAllocateInfo cmd = {
			sType: VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
			pNext: NULL,
			commandPool: context.cmd_pool,
			level: VK_COMMAND_BUFFER_LEVEL_PRIMARY,
			commandBufferCount: 1,
		};

		err = vkAllocateCommandBuffers(context.device, &cmd, &context.setup_cmd);
		assert(!err);

		VkCommandBufferBeginInfo cmd_buf_info = {
			sType: VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
			pNext: NULL,
			flags: 0,
			pInheritanceInfo: NULL,
		};
		err = vkBeginCommandBuffer(context.setup_cmd, &cmd_buf_info);
		assert(!err);
	}
}

void VKRenderer::finishSetupCommandBuffer() {
	//
	if (context.setup_cmd != VK_NULL_HANDLE) {
		VkResult err;

		err = vkEndCommandBuffer(context.setup_cmd);
		assert(!err);

		const VkCommandBuffer cmd_bufs[] = { context.setup_cmd };
		VkFence nullFence = { VK_NULL_HANDLE };
		VkSubmitInfo submit_info = {
			sType: VK_STRUCTURE_TYPE_SUBMIT_INFO,
			pNext: NULL,
			waitSemaphoreCount: 0,
			pWaitSemaphores: NULL,
			pWaitDstStageMask: NULL,
			commandBufferCount: 1,
			pCommandBuffers: cmd_bufs,
			signalSemaphoreCount: 0,
			pSignalSemaphores: NULL
		};

		err = vkQueueSubmit(context.queue, 1, &submit_info, nullFence);
		assert(!err);

		err = vkQueueWaitIdle(context.queue);
		assert(!err);

		vkFreeCommandBuffers(context.device, context.cmd_pool, 1, cmd_bufs);
		context.setup_cmd = VK_NULL_HANDLE;
	}
}

void VKRenderer::setImageLayout(bool setup, VkImage image, VkImageAspectFlags aspectMask, VkImageLayout old_image_layout, VkImageLayout new_image_layout, VkAccessFlagBits srcAccessMask) {
	VkResult err;

	//
	prepareSetupCommandBuffer();

	VkImageMemoryBarrier image_memory_barrier = {
		sType: VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
		pNext: NULL,
		srcAccessMask: srcAccessMask,
		dstAccessMask: 0,
		oldLayout: old_image_layout,
		newLayout: new_image_layout,
	    srcQueueFamilyIndex: 0,
	    dstQueueFamilyIndex: 0,
		image: image,
		subresourceRange: {
			aspectMask: aspectMask,
			baseMipLevel: 0,
			levelCount: 1,
			baseArrayLayer: 0,
			layerCount: 1
		}
	};

	if (new_image_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
		/* Make sure anything that was copying from this image has completed */
		image_memory_barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
	}

	if (new_image_layout == VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL) {
		image_memory_barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	}

	if (new_image_layout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) {
		image_memory_barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
	}

	if (new_image_layout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
		/* Make sure any Copy or CPU writes to image are flushed */
		image_memory_barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_INPUT_ATTACHMENT_READ_BIT;
	}

	//
	Console::println(string(__FUNCTION__) + ": " + to_string(__LINE__) + ": vkCmdPipelineBarrier(): ");
	vkCmdPipelineBarrier(context.setup_cmd, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, 0, 0, NULL, 0, NULL, 1, &image_memory_barrier);
}

void VKRenderer::prepareTextureImage(struct texture_object *tex_obj, VkImageTiling tiling, VkImageUsageFlags usage, VkFlags required_props, Texture* texture) {
	const VkFormat tex_format = texture->getHeight() == 32?VK_FORMAT_R8G8B8A8_UNORM:VK_FORMAT_R8G8B8A8_UNORM;
	VkResult err;
	bool pass;

	auto textureWidth = texture->getTextureWidth();
	auto textureHeight = texture->getTextureHeight();

	const VkImageCreateInfo image_create_info = {
		sType: VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
		pNext: NULL,
		flags: 0,
		imageType: VK_IMAGE_TYPE_2D,
		format: tex_format,
		extent: {
			width: textureWidth,
			height: textureHeight,
			depth: 1
		},
		mipLevels:1,
		arrayLayers: 1,
		samples: VK_SAMPLE_COUNT_1_BIT,
		tiling: tiling,
		usage: usage,
		sharingMode: VK_SHARING_MODE_EXCLUSIVE,
	    queueFamilyIndexCount: 0,
	    pQueueFamilyIndices: 0,
		initialLayout: VK_IMAGE_LAYOUT_PREINITIALIZED
	};
	VkMemoryAllocateInfo mem_alloc = {
		sType: VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		pNext: NULL,
		allocationSize: 0,
		memoryTypeIndex: 0,
	};

	VkMemoryRequirements mem_reqs;

	err = vkCreateImage(context.device, &image_create_info, NULL, &tex_obj->image);
	assert(!err);

	vkGetImageMemoryRequirements(context.device, tex_obj->image, &mem_reqs);

	mem_alloc.allocationSize = mem_reqs.size;
	pass = memoryTypeFromProperties(mem_reqs.memoryTypeBits, required_props, &mem_alloc.memoryTypeIndex);
	assert(pass);

	/* allocate memory */
	err = vkAllocateMemory(context.device, &mem_alloc, NULL, &tex_obj->mem);
	assert(!err);

	/* bind memory */
	err = vkBindImageMemory(context.device, tex_obj->image, tex_obj->mem, 0);
	assert(!err);

	auto textureData = texture->getTextureData();

	if (required_props & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) {
		const VkImageSubresource subres = {
			aspectMask: VK_IMAGE_ASPECT_COLOR_BIT,
			mipLevel: 0,
			arrayLayer: 0,
		};
		VkSubresourceLayout layout;
		void *data;

		vkGetImageSubresourceLayout(context.device, tex_obj->image, &subres, &layout);

		err = vkMapMemory(context.device, tex_obj->mem, 0, mem_alloc.allocationSize, 0, &data);
		assert(!err);

		auto bytesPerPixel = texture->getDepth() / 8;
		auto textureBuffer = texture->getTextureData();
		for (auto y = 0; y < textureHeight; y++) {
			char* row = (char*)(data + layout.offset + layout.rowPitch * y);
			for (auto x = 0; x < textureWidth; x++) {
				row[x * 4 + 0] = textureBuffer->get((y * textureWidth * bytesPerPixel) + (x * bytesPerPixel) + 0);
				row[x * 4 + 1] = textureBuffer->get((y * textureWidth * bytesPerPixel) + (x * bytesPerPixel) + 1);
				row[x * 4 + 2] = textureBuffer->get((y * textureWidth * bytesPerPixel) + (x * bytesPerPixel) + 2);
				row[x * 4 + 3] = bytesPerPixel == 4?textureBuffer->get((y * textureWidth * bytesPerPixel) + (x * bytesPerPixel) + 3):0xff;
			}
		}

		VkMappedMemoryRange mappedMemoryRange = {
			sType: VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
			pNext: NULL,
			memory: tex_obj->mem,
			offset: 0,
			size: mem_reqs.size
		};
		vkFlushMappedMemoryRanges(context.device, 1, &mappedMemoryRange);

		vkUnmapMemory(context.device, tex_obj->mem);
	}

	tex_obj->image_layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

	Console::println(string(__FUNCTION__) + ": " + to_string(__LINE__) + ": setImageLayout()");
	setImageLayout(
		false,
		tex_obj->image,
		VK_IMAGE_ASPECT_COLOR_BIT,
		VK_IMAGE_LAYOUT_PREINITIALIZED,
		tex_obj->image_layout,
		VK_ACCESS_HOST_WRITE_BIT
	);
	/* setting the image layout does not reference the actual memory so no need
	 * to add a mem ref */
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
	VkSwapchainKHR oldSwapchain = context.swapchain;

	// Check the surface capabilities and formats
	VkSurfaceCapabilitiesKHR surfCapabilities;
	err = context.fpGetPhysicalDeviceSurfaceCapabilitiesKHR(context.gpu, context.surface, &surfCapabilities);
	assert(err == VK_SUCCESS);

	uint32_t presentModeCount;
	err = context.fpGetPhysicalDeviceSurfacePresentModesKHR(context.gpu, context.surface, &presentModeCount, NULL);
	assert(err == VK_SUCCESS);
	VkPresentModeKHR *presentModes = (VkPresentModeKHR *) malloc(presentModeCount * sizeof(VkPresentModeKHR));
	assert(presentModes);
	err = context.fpGetPhysicalDeviceSurfacePresentModesKHR(context.gpu, context.surface, &presentModeCount, presentModes);
	assert(err == VK_SUCCESS);

	VkExtent2D swapchainExtent;
	// width and height are either both 0xFFFFFFFF, or both not 0xFFFFFFFF.
	if (surfCapabilities.currentExtent.width == 0xFFFFFFFF) {
		// If the surface size is undefined, the size is set to the size
		// of the images requested, which must fit within the minimum and
		// maximum values.
		swapchainExtent.width = context.width;
		swapchainExtent.height = context.height;

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
		context.width = surfCapabilities.currentExtent.width;
		context.height = surfCapabilities.currentExtent.height;
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

	const VkSwapchainCreateInfoKHR swapchain = {
		sType: VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		pNext: NULL,
		flags: 0,
		surface: context.surface,
		minImageCount: desiredNumOfSwapchainImages,
		imageFormat: context.format,
		imageColorSpace: context.color_space,
		imageExtent: {
			width: swapchainExtent.width,
			height: swapchainExtent.height,
		},
		imageArrayLayers: 1,
		imageUsage: VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
		imageSharingMode: VK_SHARING_MODE_EXCLUSIVE,
		queueFamilyIndexCount: 0,
		pQueueFamilyIndices: 0,
		preTransform: (VkSurfaceTransformFlagBitsKHR)preTransform, /// TODO: a.drewke, ???
		compositeAlpha: VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		presentMode: swapchainPresentMode,
		clipped: true,
		oldSwapchain: oldSwapchain,
	};
	uint32_t i;

	err = context.fpCreateSwapchainKHR(context.device, &swapchain, NULL, &context.swapchain);
	assert(!err);

	// If we just re-created an existing swapchain, we should destroy the old
	// swapchain at this point.
	// Note: destroying the swapchain also cleans up all its associated
	// presentable images once the platform is done with them.
	if (oldSwapchain != VK_NULL_HANDLE) {
		context.fpDestroySwapchainKHR(context.device, oldSwapchain, NULL);
	}

	err = context.fpGetSwapchainImagesKHR(context.device, context.swapchain, &context.swapchain_image_count, NULL);
	assert(err == VK_SUCCESS);

	VkImage* swapchainImages = (VkImage*)malloc(context.swapchain_image_count * sizeof(VkImage));
	assert(swapchainImages != NULL);
	err = context.fpGetSwapchainImagesKHR(context.device, context.swapchain, &context.swapchain_image_count, swapchainImages);
	assert(err == VK_SUCCESS);

	context.swapchain_buffers = (swapchain_buffer_type*)malloc(sizeof(swapchain_buffer_type) * context.swapchain_image_count);
	assert(context.swapchain_buffers != NULL);

	for (i = 0; i < context.swapchain_image_count; i++) {
		VkImageViewCreateInfo color_attachment_view = {
			sType: VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
			pNext: NULL,
			flags: 0,
			image: swapchainImages[i],
			viewType: VK_IMAGE_VIEW_TYPE_2D,
			format: context.format,
			components: {
				r: VK_COMPONENT_SWIZZLE_R,
				g: VK_COMPONENT_SWIZZLE_G,
				b: VK_COMPONENT_SWIZZLE_B,
				a: VK_COMPONENT_SWIZZLE_A
			},
			subresourceRange: {
				aspectMask: VK_IMAGE_ASPECT_COLOR_BIT,
				baseMipLevel: 0,
				levelCount: 1,
				baseArrayLayer: 0,
				layerCount: 1
			}
		};
		context.swapchain_buffers[i].image = swapchainImages[i];
		err = vkCreateImageView(context.device, &color_attachment_view, NULL, &context.swapchain_buffers[i].view);
		assert(err == VK_SUCCESS);
	}

	context.current_buffer = 0;

	if (NULL != presentModes) free(presentModes);
}

const string VKRenderer::getGLVersion()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return "gl3";
}

void VKRenderer::initialize()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");

	//
	glfwGetWindowSize(Application::glfwWindow, &context.width, &context.height);

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
	context.enabled_extension_count = 0;
	context.enabled_layer_count = 0;

	char* instance_validation_layers_alt1[] = {
		"VK_LAYER_LUNARG_standard_validation"
	};

	char* instance_validation_layers_alt2[] = {
		"VK_LAYER_GOOGLE_threading",
		"VK_LAYER_LUNARG_parameter_validation",
		"VK_LAYER_LUNARG_object_tracker", "VK_LAYER_LUNARG_image",
		"VK_LAYER_LUNARG_core_validation", "VK_LAYER_LUNARG_swapchain",
		"VK_LAYER_GOOGLE_unique_objects"
	};

	/* Look for validation layers */
	if (context.validate == true) {
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
				context.enabled_layer_count = ARRAY_SIZE(instance_validation_layers_alt1);
				context.enabled_layers[0] = "VK_LAYER_LUNARG_standard_validation";
				validation_layer_count = 1;
			} else {
				// use alternative set of validation layers
				instance_validation_layers = (const char**) instance_validation_layers_alt2;
				context.enabled_layer_count = ARRAY_SIZE(instance_validation_layers_alt2);
				validation_found = checkLayers(
					ARRAY_SIZE(instance_validation_layers_alt2),
					instance_validation_layers,
					instance_layer_count,
					instance_layers
				);
				validation_layer_count = ARRAY_SIZE(instance_validation_layers_alt2);
				for (i = 0; i < validation_layer_count; i++) {
					context.enabled_layers[i] = instance_validation_layers[i];
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

	/* Look for instance extensions */
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
		context.extension_names[context.enabled_extension_count++] = required_extensions[i];
		assert(context.enabled_extension_count < 64);
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
				if (context.validate) {
					context.extension_names[context.enabled_extension_count++] = VK_EXT_DEBUG_REPORT_EXTENSION_NAME;
				}
			}
			assert(context.enabled_extension_count < 64);
		}
		free(instance_extensions);
	}

	const VkApplicationInfo app = {
		sType: VK_STRUCTURE_TYPE_APPLICATION_INFO,
		pNext: NULL,
		pApplicationName: "TDME2 based application",
		applicationVersion: 0,
		pEngineName: "TDME2",
		engineVersion: 0,
		apiVersion: VK_API_VERSION_1_0,
	};
	VkInstanceCreateInfo inst_info = {
		sType: VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		pNext: NULL,
		flags: 0,
		pApplicationInfo: &app,
		enabledLayerCount: context.enabled_layer_count,
		ppEnabledLayerNames: (const char * const *)instance_validation_layers,
		enabledExtensionCount: context.enabled_extension_count,
		ppEnabledExtensionNames: (const char * const *)context.extension_names,
	};
	uint32_t gpu_count;

	err = vkCreateInstance(&inst_info, NULL, &context.inst);
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

	/* Make initial call to query gpu_count, then second call for gpu info*/
	err = vkEnumeratePhysicalDevices(context.inst, &gpu_count, NULL);
	assert(!err && gpu_count > 0);

	if (gpu_count > 0) {
		VkPhysicalDevice* physical_devices = (VkPhysicalDevice*)malloc(sizeof(VkPhysicalDevice) * gpu_count);
		err = vkEnumeratePhysicalDevices(context.inst, &gpu_count, physical_devices);
		assert(!err);
		/* For tri demo we just grab the first physical device */
		context.gpu = physical_devices[0];
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

	/* Look for device extensions */
	uint32_t device_extension_count = 0;
	VkBool32 swapchainExtFound = 0;
	context.enabled_extension_count = 0;

	err = vkEnumerateDeviceExtensionProperties(context.gpu, NULL, &device_extension_count, NULL);
	assert(!err);

	if (device_extension_count > 0) {
		VkExtensionProperties* device_extensions = (VkExtensionProperties*)malloc(sizeof(VkExtensionProperties) * device_extension_count);
		err = vkEnumerateDeviceExtensionProperties(context.gpu, NULL, &device_extension_count, device_extensions);
		assert(!err);

		for (i = 0; i < device_extension_count; i++) {
			if (!strcmp(VK_KHR_SWAPCHAIN_EXTENSION_NAME, device_extensions[i].extensionName)) {
				swapchainExtFound = 1;
				context.extension_names[context.enabled_extension_count++] = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
			}
			assert(context.enabled_extension_count < 64);
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
	GET_INSTANCE_PROC_ADDR(context, context.inst, GetPhysicalDeviceSurfaceCapabilitiesKHR);
	GET_INSTANCE_PROC_ADDR(context, context.inst, GetPhysicalDeviceSurfaceFormatsKHR);
	GET_INSTANCE_PROC_ADDR(context, context.inst, GetPhysicalDeviceSurfacePresentModesKHR);
	GET_INSTANCE_PROC_ADDR(context, context.inst, GetPhysicalDeviceSurfaceSupportKHR);

	vkGetPhysicalDeviceProperties(context.gpu, &context.gpu_props);

	// Query with NULL data to get count
	vkGetPhysicalDeviceQueueFamilyProperties(context.gpu, &context.queue_count, NULL);

	context.queue_props = (VkQueueFamilyProperties *) malloc(context.queue_count * sizeof(VkQueueFamilyProperties));
	vkGetPhysicalDeviceQueueFamilyProperties(context.gpu, &context.queue_count, context.queue_props);
	assert(context.queue_count >= 1);

	vkGetPhysicalDeviceFeatures(context.gpu, &context.gpu_features);

	// Create a WSI surface for the window:
	glfwCreateWindowSurface(context.inst, Application::glfwWindow, NULL, &context.surface);

	// Iterate over each queue to learn whether it supports presenting:
	VkBool32 *supportsPresent = (VkBool32 *) malloc(context.queue_count * sizeof(VkBool32));
	for (i = 0; i < context.queue_count; i++) {
		context.fpGetPhysicalDeviceSurfaceSupportKHR(context.gpu, i, context.surface, &supportsPresent[i]);
	}

	// Search for a graphics and a present queue in the array of queue
	// families, try to find one that supports both
	uint32_t graphicsQueueNodeIndex = UINT32_MAX;
	uint32_t presentQueueNodeIndex = UINT32_MAX;
	for (i = 0; i < context.queue_count; i++) {
		if ((context.queue_props[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0) {
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
		for (i = 0; i < context.queue_count; ++i) {
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

	context.graphics_queue_node_index = graphicsQueueNodeIndex;

	// init_device
	float queue_priorities[1] = { 0.0 };
	const VkDeviceQueueCreateInfo queue = {
		sType: VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
		pNext: NULL,
		flags: 0,
		queueFamilyIndex: context.graphics_queue_node_index,
		queueCount: 1,
		pQueuePriorities: queue_priorities
	};

	VkPhysicalDeviceFeatures features;
	memset(&features, 0, sizeof(features));
	if (context.gpu_features.shaderClipDistance) {
		features.shaderClipDistance = VK_TRUE;
	}

	VkDeviceCreateInfo device = {
		sType: VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		pNext: NULL,
		flags: 0,
		queueCreateInfoCount: 1,
		pQueueCreateInfos: &queue,
		enabledLayerCount: 0,
		ppEnabledLayerNames: NULL,
		enabledExtensionCount: context.enabled_extension_count,
		ppEnabledExtensionNames: (const char * const *) context.extension_names,
		pEnabledFeatures: &features
	};

	err = vkCreateDevice(context.gpu, &device, NULL, &context.device);
	assert(!err);

	GET_DEVICE_PROC_ADDR(context.device, CreateSwapchainKHR);
	GET_DEVICE_PROC_ADDR(context.device, DestroySwapchainKHR);
	GET_DEVICE_PROC_ADDR(context.device, GetSwapchainImagesKHR);
	GET_DEVICE_PROC_ADDR(context.device, AcquireNextImageKHR);
	GET_DEVICE_PROC_ADDR(context.device, QueuePresentKHR);

	vkGetDeviceQueue(context.device, context.graphics_queue_node_index, 0, &context.queue);

	// Get the list of VkFormat's that are supported:
	uint32_t formatCount;
	err = context.fpGetPhysicalDeviceSurfaceFormatsKHR(context.gpu, context.surface, &formatCount, NULL);
	assert(!err);
	VkSurfaceFormatKHR *surfFormats = (VkSurfaceFormatKHR *) malloc(formatCount * sizeof(VkSurfaceFormatKHR));
	err = context.fpGetPhysicalDeviceSurfaceFormatsKHR(context.gpu, context.surface, &formatCount, surfFormats);

	assert(!err);
	// If the format list includes just one entry of VK_FORMAT_UNDEFINED,
	// the surface has no preferred format.  Otherwise, at least one
	// supported format will be returned.
	if (formatCount == 1 && surfFormats[0].format == VK_FORMAT_UNDEFINED) {
		context.format = VK_FORMAT_B8G8R8A8_UNORM;
	} else {
		assert(formatCount >= 1);
		context.format = surfFormats[0].format;
	}
	context.color_space = surfFormats[0].colorSpace;

	// Get Memory information and properties
	vkGetPhysicalDeviceMemoryProperties(context.gpu, &context.memory_properties);

	// command pool
	const VkCommandPoolCreateInfo cmd_pool_info = {
		sType: VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
		pNext: NULL,
		flags: VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
		queueFamilyIndex: context.graphics_queue_node_index
	};
	err = vkCreateCommandPool(context.device, &cmd_pool_info, NULL, &context.cmd_pool);
	assert(!err);

	// draw command buffers
	const VkCommandBufferAllocateInfo cmd = {
		sType: VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
		pNext: NULL,
		commandPool: context.cmd_pool,
		level: VK_COMMAND_BUFFER_LEVEL_PRIMARY,
		commandBufferCount: 1,
	};
	err = vkAllocateCommandBuffers(context.device, &cmd, &context.draw_cmd);
	assert(!err);

	// swap chain
	initializeSwapChain();

	// create descriptor pool
	const VkDescriptorPoolSize types_count[2] = {
		[0] = {
			type: VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
			descriptorCount: 1 * DESC_MAX
		},
		[1] = {
			type: VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
			descriptorCount: 2 * DESC_MAX
		}
	};
	const VkDescriptorPoolCreateInfo descriptor_pool = {
		sType: VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
		pNext: NULL,
		flags: 0,
		maxSets: DESC_MAX,
		poolSizeCount: 2,
		pPoolSizes: types_count,
	};

	err = vkCreateDescriptorPool(context.device, &descriptor_pool, NULL, &context.desc_pool);
	assert(!err);

	//
	initializeRenderPass();
	initializeFrameBuffers();
}

void VKRenderer::initializeRenderPass() {
	VkResult err;

	//
	if (context.render_pass != VK_NULL_HANDLE) vkDestroyRenderPass(context.device, context.render_pass, NULL);

	// depth buffer
	if (context.depth_buffer_default != 0) disposeTexture(context.depth_buffer_default);
	context.depth_buffer_default = createDepthBufferTexture(context.width, context.height);

	//
	context.white_texture_default = 0;

	// render pass
	const VkAttachmentDescription attachments[2] = {
		[0] = {
				flags: 0,
				format: context.format,
				samples: VK_SAMPLE_COUNT_1_BIT,
				loadOp: VK_ATTACHMENT_LOAD_OP_CLEAR,
				storeOp: VK_ATTACHMENT_STORE_OP_STORE,
				stencilLoadOp: VK_ATTACHMENT_LOAD_OP_DONT_CARE,
				stencilStoreOp: VK_ATTACHMENT_STORE_OP_DONT_CARE,
				initialLayout: VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
				finalLayout: VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
			},
		[1] = {
				flags: 0,
				format: VK_FORMAT_D32_SFLOAT,
				samples: VK_SAMPLE_COUNT_1_BIT,
				loadOp: VK_ATTACHMENT_LOAD_OP_CLEAR,
				storeOp: VK_ATTACHMENT_STORE_OP_DONT_CARE,
				stencilLoadOp: VK_ATTACHMENT_LOAD_OP_DONT_CARE,
				stencilStoreOp: VK_ATTACHMENT_STORE_OP_DONT_CARE,
				initialLayout: VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
				finalLayout: VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
			},
	};
	const VkAttachmentReference color_reference = {
		attachment: 0,
		layout: VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
	};
	const VkAttachmentReference depth_reference = {
		attachment: 1,
		layout: VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
	};
	const VkSubpassDescription subpass = {
		flags: 0,
		pipelineBindPoint: VK_PIPELINE_BIND_POINT_GRAPHICS,
		inputAttachmentCount: 0,
		pInputAttachments: NULL,
		colorAttachmentCount: 1,
		pColorAttachments: &color_reference,
		pResolveAttachments: NULL,
		pDepthStencilAttachment: &depth_reference,
		preserveAttachmentCount: 0,
		pPreserveAttachments: NULL
	};
	const VkRenderPassCreateInfo rp_info = {
		sType: VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
		pNext: NULL,
		flags: 0,
		attachmentCount: 2,
		pAttachments: attachments,
		subpassCount: 1,
		pSubpasses: &subpass,
		dependencyCount: 0,
		pDependencies: NULL,
	};
	err = vkCreateRenderPass(context.device, &rp_info, NULL, &context.render_pass);
	assert(!err);
}

void VKRenderer::initializeFrameBuffers() {
	VkImageView attachments[2];
	auto depthBufferIt = context.textures.find(context.depth_buffer_default);
	assert(depthBufferIt != context.textures.end());
	attachments[1] = depthBufferIt->second.view;

	const VkFramebufferCreateInfo fb_info = {
		sType: VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
		pNext: NULL,
		flags: 0,
		renderPass: context.render_pass,
		attachmentCount: 2,
		pAttachments: attachments,
		width: context.width,
		height: context.height,
		layers: 1,
	};

	VkResult err;
	uint32_t i;

	context.framebuffers = (VkFramebuffer *) malloc(context.swapchain_image_count * sizeof(VkFramebuffer));
	assert(context.framebuffers);

	for (i = 0; i < context.swapchain_image_count; i++) {
		attachments[0] = context.swapchain_buffers[i].view;
		err = vkCreateFramebuffer(context.device, &fb_info, NULL, &context.framebuffers[i]);
		assert(!err);
	}
}

void VKRenderer::reshape() {
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");

	// new dimensions
	glfwGetWindowSize(Application::glfwWindow, &context.width, &context.height);

	//
	Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + to_string(context.width) + " x " + to_string(context.height));

	//
	auto frame_buffers_last = context.framebuffers;

	// reinit swapchain, renderpass and framebuffers
	initializeSwapChain();
	initializeRenderPass();
	initializeFrameBuffers();
	context.current_buffer = 0;

	// dispose old frame buffers
	for (auto i = 0; i < context.swapchain_image_count; i++) vkDestroyFramebuffer(context.device, frame_buffers_last[i], NULL);
	delete [] frame_buffers_last;

	//
	Engine::getInstance()->reshape(0, 0, context.width, context.height);
}

void VKRenderer::initializeFrame()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");

	//
	GLRenderer::initializeFrame();

	//
	VkResult err;
	VkSemaphoreCreateInfo semaphoreCreateInfo = {
		sType: VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
		pNext: NULL,
		flags: 0
	};

	err = vkCreateSemaphore(context.device, &semaphoreCreateInfo, NULL, &context.image_acquired_semaphore);
	assert(!err);

	err = vkCreateSemaphore(context.device, &semaphoreCreateInfo, NULL, &context.draw_complete_semaphore);
	assert(!err);

	// get the index of the next available swapchain image:
	err = context.fpAcquireNextImageKHR(context.device, context.swapchain, UINT64_MAX, context.image_acquired_semaphore, (VkFence) 0, &context.current_buffer);

	//
	if (err == VK_ERROR_OUT_OF_DATE_KHR) {
		// TODO: a.drewke
		//
		finishSetupCommandBuffer();
		vkCmdEndRenderPass(context.draw_cmd);
		vkDestroySemaphore(context.device, context.image_acquired_semaphore, NULL);
		vkDestroySemaphore(context.device, context.draw_complete_semaphore, NULL);

		//
		reshape();

		// recreate semaphores
		err = vkCreateSemaphore(context.device, &semaphoreCreateInfo, NULL, &context.image_acquired_semaphore);
		assert(!err);

		err = vkCreateSemaphore(context.device, &semaphoreCreateInfo, NULL, &context.draw_complete_semaphore);
		assert(!err);
	} else
	if (err == VK_SUBOPTIMAL_KHR) {
		// demo->swapchain is not as optimal as it could be, but the platform's
		// presentation engine will still present the image correctly.
	} else {
		assert(!err);
	}

	const VkCommandBufferBeginInfo cmd_buf_info = {
		sType: VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		pNext: NULL,
		flags: 0,
		pInheritanceInfo: NULL
	};

	const VkClearValue clear_values[2] = {
		[0] =
			{
				color: { context.clear_red, context.clear_green, context.clear_blue, context.clear_alpha, }
			},
		[1] =
			{
				depthStencil: { 1.0f, 0 }
			}
	};

	const VkRenderPassBeginInfo rp_begin = {
		sType: VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
		pNext: NULL,
		renderPass: context.render_pass,
		framebuffer: context.framebuffers[context.current_buffer],
		renderArea: {
			offset: {
				x: 0,
				y: 0
			},
			extent: {
				width: context.width,
				height: context.height,
			}
		},
		clearValueCount: 2,
		pClearValues: clear_values,
	};

	err = vkBeginCommandBuffer(context.draw_cmd, &cmd_buf_info);
	assert(!err);

	// We can use LAYOUT_UNDEFINED as a wildcard here because we don't care what
	// happens to the previous contents of the image
	VkImageMemoryBarrier image_memory_barrier = {
		sType: VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
		pNext: NULL,
		srcAccessMask: 0,
		dstAccessMask: VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
		oldLayout: VK_IMAGE_LAYOUT_UNDEFINED,
		newLayout: VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		srcQueueFamilyIndex: VK_QUEUE_FAMILY_IGNORED,
		dstQueueFamilyIndex: VK_QUEUE_FAMILY_IGNORED,
		image: context.swapchain_buffers[context.current_buffer].image,
		subresourceRange: { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 }
	};

	vkCmdPipelineBarrier(context.draw_cmd, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, 0, 0, NULL, 0, NULL, 1, &image_memory_barrier);
	vkCmdBeginRenderPass(context.draw_cmd, &rp_begin, VK_SUBPASS_CONTENTS_INLINE);
}

void VKRenderer::finishFrame()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");

	//
	finishSetupCommandBuffer();

	// flush command buffers
	if (context.program_id != 0) {
		flushCommands();
		finishPipeline();
		context.program_id = 0;
	}

	//
	VkResult err;

	//
	vkCmdEndRenderPass(context.draw_cmd);

	VkImageMemoryBarrier prePresentBarrier = {
		sType: VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
		pNext: NULL,
		srcAccessMask: VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
		dstAccessMask: 0,
		oldLayout: VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		newLayout: VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
		srcQueueFamilyIndex: VK_QUEUE_FAMILY_IGNORED,
		dstQueueFamilyIndex: VK_QUEUE_FAMILY_IGNORED,
		image: context.swapchain_buffers[context.current_buffer].image,
		subresourceRange: { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 }
	};
	vkCmdPipelineBarrier(context.draw_cmd, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, 0, 0, NULL, 0, NULL, 1, &prePresentBarrier);

	err = vkEndCommandBuffer(context.draw_cmd);
	assert(!err);

	//
	VkFence nullFence = VK_NULL_HANDLE;
	VkPipelineStageFlags pipe_stage_flags = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
	VkSubmitInfo submit_info = {
		sType: VK_STRUCTURE_TYPE_SUBMIT_INFO,
		pNext: NULL,
		waitSemaphoreCount: 1,
		pWaitSemaphores: &context.image_acquired_semaphore,
		pWaitDstStageMask: &pipe_stage_flags,
		commandBufferCount: 1,
		pCommandBuffers: &context.draw_cmd,
		signalSemaphoreCount: 1,
		pSignalSemaphores: &context.draw_complete_semaphore
	};

	err = vkQueueSubmit(context.queue, 1, &submit_info, nullFence);
	assert(!err);

	VkPresentInfoKHR present = {
		.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
		.pNext = NULL,
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = &context.draw_complete_semaphore,
		.swapchainCount = 1,
		.pSwapchains = &context.swapchain,
		.pImageIndices = &context.current_buffer,
	};

	err = context.fpQueuePresentKHR(context.queue, &present);
	auto needsReshape = false;
	if (err == VK_ERROR_OUT_OF_DATE_KHR) {
		needsReshape = true;
	} else
	if (err == VK_SUBOPTIMAL_KHR) {
		// context.swapchain is not as optimal as it could be, but the platform's
		// presentation engine will still present the image correctly.
	} else {
		assert(!err);
	}

	err = vkQueueWaitIdle(context.queue);
	assert(err == VK_SUCCESS);

	vkDestroySemaphore(context.device, context.image_acquired_semaphore, NULL);
	vkDestroySemaphore(context.device, context.draw_complete_semaphore, NULL);

	//
	vkDeviceWaitIdle(context.device);

	// delete buffers and memory
	for (auto buffer: context.buffers_delete) vkDestroyBuffer(context.device, buffer, NULL);
	for (auto image: context.images_delete) vkDestroyImage(context.device, image, NULL);
	for (auto memory: context.memory_delete) vkFreeMemory(context.device, memory, NULL);
	context.buffers_delete.clear();
	context.images_delete.clear();
	context.memory_delete.clear();

	//
	finishPipeline();
	// if (Engine::getInstance()->getTiming()->getFrame() == 2) exit(0);

	if (needsReshape == true) reshape();
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

int32_t VKRenderer::getUniformBufferObjectBindingIdx(int32_t shaderType) {
	if (shaderType == SHADER_FRAGMENT_SHADER) return 1;
	if (shaderType == SHADER_VERTEX_SHADER) return 0;
	if (shaderType == SHADER_COMPUTE_SHADER) return 0;
	if (shaderType == SHADER_GEOMETRY_SHADER) return 2;
	return -1;
}

int32_t VKRenderer::loadShader(int32_t type, const string& pathName, const string& fileName, const string& definitions, const string& functions)
{
	/*if (VERBOSE == true) */Console::println("VKRenderer::" + string(__FUNCTION__) + "(): INIT: " + pathName + "/" + fileName + ": " + definitions);

	auto& shaderStruct = context.shaders[context.shader_idx];
	shaderStruct.type = (VkShaderStageFlagBits)type;
	shaderStruct.id = context.shader_idx++;

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
		string newShaderSource;
		vector<string> definitions;
		vector<string> uniforms;
		shaderSource = StringUtils::replace(shaderSource, "\r", "");
		shaderSource = StringUtils::replace(shaderSource, "#version 330", "#version 430\n#extension GL_EXT_scalar_block_layout: require\n");
		StringTokenizer t;
		t.tokenize(shaderSource, "\n");
		stack<string> testedDefinitions;
		while (t.hasMoreTokens() == true) {
			auto line = StringUtils::trim(t.nextToken());
			if (StringUtils::startsWith(line, "//") == true) continue;
			auto position = -1;
			if ((position = line.find("uniform ")) != -1) {
				if (line.find("sampler2D") != -1) {
					Console::println("VKRenderer::" + string(__FUNCTION__) + "(): Have uniform with sampler2D: skipping: " + line);
					newShaderSource+= line + "\n";
				} else {
					string uniform;
					if (StringUtils::startsWith(line, "uniform") == true) {
						uniform = StringUtils::substring(line, string("uniform").size() + 1);
					} else
					if (StringUtils::startsWith(line, "layout") == true) {
						uniform = StringUtils::substring(line, line.find(") uniform") + string(") uniform").size());
					}
					uniforms.push_back(uniform);
					Console::println("VKRenderer::" + string(__FUNCTION__) + "(): Have uniform: " + uniform);
				}
			} else
			if ((position = line.find("#define ")) != -1) {
				Console::println("VKRenderer::" + string(__FUNCTION__) + "(): Have define: " + line);
				newShaderSource+= line + "\n";
			} else
			if ((position = line.find("#if defined(")) != -1) {
				Console::println("VKRenderer::" + string(__FUNCTION__) + "(): Have preprocessor test begin: " + line);
				testedDefinitions.push("TODO");
				newShaderSource+= line + "\n";
			} else
			if ((position = line.find("#endif")) != -1) {
				Console::println("VKRenderer::" + string(__FUNCTION__) + "(): Have preprocessor test end: " + line);
				if (testedDefinitions.size() == 0) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): Have preprocessor test end: invalid depth"); else testedDefinitions.pop();
				newShaderSource+= line + "\n";
			} else {
				newShaderSource+= line + "\n";
			}
		}

		// generate new uniform block
		auto bindingIdx = getUniformBufferObjectBindingIdx(type);
		shaderSource = newShaderSource;
		string uniformsBlock = "";
		if (uniforms.size() > 0) {
			uniformsBlock+= "\n";
			uniformsBlock+= "layout(std430, binding=" + to_string(bindingIdx) + ") uniform UniformBufferObject\n";
			uniformsBlock+= "{\n";
			for (auto uniform: uniforms) {
				uniformsBlock+= "\t" + uniform + "\n";
			}
			uniformsBlock+= "} ubo_generated;\n";
		}

		// replace uniforms to use ubo
		//	TODO: improve me as this will not work in all cases
		shaderStruct.ubo_size = 0;
		for (auto uniform: uniforms) {
			t.tokenize(uniform, "\t ;");
			string uniformType;
			string uniformName;
			if (t.hasMoreTokens() == true) uniformType = t.nextToken();
			while (t.hasMoreTokens() == true) uniformName = t.nextToken();
			if (uniformType == "int") {
				auto size = sizeof(int32_t);
				shaderStruct.uniforms[uniformName] = {name: uniformName, position: shaderStruct.ubo_size, size: size};
				shaderStruct.ubo_size+= 16;
			} else
			if (uniformType == "float") {
				auto size = sizeof(float);
				shaderStruct.uniforms[uniformName] = {name: uniformName, position: shaderStruct.ubo_size, size: size};
				shaderStruct.ubo_size+= 16;
			} else
			if (uniformType == "vec3") {
				auto size = sizeof(float) * 3;
				shaderStruct.uniforms[uniformName] = {name: uniformName, position: shaderStruct.ubo_size, size: size};
				shaderStruct.ubo_size+= 16;
			} else
			if (uniformType == "vec4") {
				auto size = sizeof(float) * 4;
				shaderStruct.uniforms[uniformName] = {name: uniformName, position: shaderStruct.ubo_size, size: size};
				shaderStruct.ubo_size+= size;
			} else
			if (uniformType == "mat3") {
				auto size = sizeof(float) * 12;
				shaderStruct.uniforms[uniformName] = {name: uniformName, position: shaderStruct.ubo_size, size: size};
				shaderStruct.ubo_size+= size;
			} else
			if (uniformType == "mat4") {
				auto size = sizeof(float) * 16;
				shaderStruct.uniforms[uniformName] = {name: uniformName, position: shaderStruct.ubo_size, size: size};
				shaderStruct.ubo_size+= size;
			} else {
				Console::println("VKRenderer::" + string(__FUNCTION__) + "(): Unknown uniform type: " + uniformType);
				context.shaders.erase(shaderStruct.id);
		        return false;
			}
			shaderSource = StringUtils::replace(
				shaderSource,
				uniformName,
				"ubo_generated." + uniformName
			);
		}

		// debug uniforms
		for (auto& uniformIt: shaderStruct.uniforms) {
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): Uniform: " + uniformIt.second.name + ": " + to_string(uniformIt.second.position) + " / " + to_string(uniformIt.second.size));
		}

		// finally inject uniforms
		shaderSource = StringUtils::replace(
			shaderSource,
			"{$UNIFORMS}",
			uniformsBlock
		);
	}

	char* sourceHeap = new char[shaderSource.length() + 1];
	strcpy(sourceHeap, shaderSource.c_str());

    EShLanguage stage = shaderFindLanguage((VkShaderStageFlagBits)type);
    glslang::TShader glslShader(stage);
    glslang::TProgram glslProgram;
    const char *shaderStrings[1];
    TBuiltInResource resources;
    shaderInitResources(resources);

    // Enable SPIR-V and Vulkan rules when parsing GLSL
    EShMessages messages = (EShMessages)(EShMsgSpvRules | EShMsgVulkanRules);

    shaderStrings[0] = sourceHeap;
    glslShader.setStrings(shaderStrings, 1);

    if (!glslShader.parse(&resources, 100, false, messages)) {
		// be verbose
		Console::println(
			string(
				string("GL3Renderer::loadShader") +
				string("[") +
				to_string(shaderStruct.id) +
				string("]") +
				pathName +
				string("/") +
				fileName +
				string(": parsing failed: ") +
				glslShader.getInfoLog() + ": " +
				glslShader.getInfoDebugLog()
			 )
		);
		Console::println(shaderSource);
		context.shaders.erase(shaderStruct.id);
        return false;
    }

    Console::println(shaderSource);

    glslProgram.addShader(&glslShader);

    // Program-level processing...
    if (glslProgram.link(messages) == false) {
		// be verbose
		Console::println(
			string(
				string("GL3Renderer::loadShader") +
				string("[") +
				to_string(shaderStruct.id) +
				string("]") +
				pathName +
				string("/") +
				fileName +
				string(": linking failed: ") +
				glslShader.getInfoLog() + ": " +
				glslShader.getInfoDebugLog()
			 )
		);
		Console::println(shaderSource);
		context.shaders.erase(shaderStruct.id);
        return false;
    }

    glslang::GlslangToSpv(*glslProgram.getIntermediate(stage), shaderStruct.spirv);

    //
	shaderStruct.uniform_buffer = createBufferObjects(1)[0];

    // create shader module
    {
		VkResult err;
		VkShaderModuleCreateInfo moduleCreateInfo;
		moduleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		moduleCreateInfo.pNext = NULL;
		moduleCreateInfo.codeSize = shaderStruct.spirv.size() * sizeof(uint32_t);
		moduleCreateInfo.pCode = shaderStruct.spirv.data();
		moduleCreateInfo.flags = 0;
		err = vkCreateShaderModule(context.device, &moduleCreateInfo, NULL, &shaderStruct.module);
		if (err == VK_SUCCESS) {
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): SUCCESS: " + pathName + "/" + fileName + ": " + definitions);
		} else {
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): FAILED: could not create module: " + pathName + "/" + fileName + ": " + definitions);
			context.shaders.erase(shaderStruct.id);
			return false;
		}
    }

    //
	return shaderStruct.id;
}

void VKRenderer::preparePipeline(program_type& program) {
	auto shaderIdx = 0;
	for (auto shaderId: program.shader_ids) {
		auto shaderIt = context.shaders.find(shaderId);
		if (shaderIt == context.shaders.end()) {
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): shader does not exist: " + to_string(shaderId));
			return;
		}
		auto& shader = shaderIt->second;
		context.uniform_buffers[shaderIdx].resize(shader.ubo_size);
		shaderIdx++;
	}
}

void VKRenderer::finishPipeline() {
	// unset bound buffers and such
	context.bound_indices_buffer = 0;
	context.bound_buffers.fill(0);
	for (auto& ubo: context.uniform_buffers) ubo.clear();
	context.bound_texture_id = 0;
}

void VKRenderer::createPipeline(program_type& program) {
	if (program.created_pipeline == false) {
		VkResult err;

		//
		VkDescriptorSetLayoutBinding layout_bindings[16];
		memset(layout_bindings, 0, sizeof(layout_bindings));

		//
		VkGraphicsPipelineCreateInfo pipeline;
		memset(&pipeline, 0, sizeof(pipeline));

		// Two stages: vs and fs
		pipeline.stageCount = program.shader_ids.size();
		VkPipelineShaderStageCreateInfo shaderStages[program.shader_ids.size()];
		memset(shaderStages, 0, program.shader_ids.size() * sizeof(VkPipelineShaderStageCreateInfo));

		int layoutBindingIdx = 0;
		auto shaderIdx = 0;
		for (auto shaderId: program.shader_ids) {
			auto shaderIt = context.shaders.find(shaderId);
			if (shaderIt == context.shaders.end()) {
				Console::println("VKRenderer::" + string(__FUNCTION__) + "(): shader does not exist: " + to_string(shaderId));
				return;
			}
			auto& shader = shaderIt->second;
			shaderStages[shaderIdx].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			shaderStages[shaderIdx].stage = shader.type;
			shaderStages[shaderIdx].module = shader.module;
			shaderStages[shaderIdx].pName = "main";
			if (shader.ubo_size > 0) {
				auto uboBindingIdx = getUniformBufferObjectBindingIdx(shader.type);
				layout_bindings[uboBindingIdx] = {
					binding: uboBindingIdx,
					descriptorType: VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
					descriptorCount: 1,
					stageFlags: shader.type,
					pImmutableSamplers: NULL
				};
				layoutBindingIdx++;
			}
			shaderIdx++;
		}

		layout_bindings[layoutBindingIdx] = {
			binding: layoutBindingIdx,
			descriptorType: VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
			descriptorCount: 1,
			stageFlags: VK_SHADER_STAGE_FRAGMENT_BIT,
			pImmutableSamplers: NULL
		};
		layoutBindingIdx++;

		const VkDescriptorSetLayoutCreateInfo descriptor_layout = {
			sType: VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
			pNext: NULL,
			flags: 0,
			bindingCount: layoutBindingIdx,
			pBindings: layout_bindings,
		};

		err = vkCreateDescriptorSetLayout(context.device, &descriptor_layout, NULL, &program.desc_layout);
		assert(!err);

		const VkPipelineLayoutCreateInfo pPipelineLayoutCreateInfo = {
			sType: VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
			pNext: NULL,
			flags: 0,
			setLayoutCount: 1,
			pSetLayouts: &program.desc_layout,
		};

		VkDescriptorSetLayout desc_layouts[DESC_MAX];
		for (auto i = 0; i < program.desc_max; i++) desc_layouts[i] = program.desc_layout;

		//
		VkDescriptorSetAllocateInfo alloc_info = {
			sType: VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
			pNext: NULL,
			descriptorPool: context.desc_pool,
			descriptorSetCount: program.desc_max,
			pSetLayouts: desc_layouts
		};
		err = vkAllocateDescriptorSets(context.device, &alloc_info, program.desc_set);
		assert(!err);

		err = vkCreatePipelineLayout(context.device, &pPipelineLayoutCreateInfo, NULL, &program.pipeline_layout);
		assert(!err);

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

		memset(dynamicStateEnables, 0, sizeof dynamicStateEnables);
		memset(&dynamicState, 0, sizeof dynamicState);
		dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamicState.pDynamicStates = dynamicStateEnables;

		pipeline.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipeline.layout = program.pipeline_layout;

		memset(&ia, 0, sizeof(ia));
		ia.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		ia.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

		memset(&rs, 0, sizeof(rs));
		rs.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rs.polygonMode = VK_POLYGON_MODE_FILL;
		rs.cullMode = VK_CULL_MODE_NONE;
		rs.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
		rs.depthClampEnable = VK_FALSE;
		rs.rasterizerDiscardEnable = VK_FALSE;
		rs.depthBiasEnable = VK_FALSE;
		rs.lineWidth = 1.0f;

		VkPipelineColorBlendAttachmentState att_state[1];
		memset(att_state, 0, sizeof(att_state));
		att_state[0].colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		att_state[0].blendEnable = VK_TRUE;
		att_state[0].srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
		att_state[0].dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
		att_state[0].colorBlendOp = VK_BLEND_OP_ADD;
		att_state[0].srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
		att_state[0].dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
		att_state[0].alphaBlendOp = VK_BLEND_OP_ADD;

		memset(&cb, 0, sizeof(cb));
		cb.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		cb.logicOpEnable = VK_FALSE;
		cb.attachmentCount = 1;
		cb.pAttachments = att_state;

		memset(&vp, 0, sizeof(vp));
		vp.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		vp.viewportCount = 1;
		dynamicStateEnables[dynamicState.dynamicStateCount++] = VK_DYNAMIC_STATE_VIEWPORT;
		vp.scissorCount = 1;
		dynamicStateEnables[dynamicState.dynamicStateCount++] = VK_DYNAMIC_STATE_SCISSOR;

		memset(&ds, 0, sizeof(ds));
		ds.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		ds.depthTestEnable = VK_FALSE;
		ds.depthWriteEnable = VK_FALSE;
		ds.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
		ds.depthBoundsTestEnable = VK_FALSE;
		ds.back.failOp = VK_STENCIL_OP_KEEP;
		ds.back.passOp = VK_STENCIL_OP_KEEP;
		ds.back.compareOp = VK_COMPARE_OP_ALWAYS;
		ds.stencilTestEnable = VK_FALSE;
		ds.front = ds.back;

		memset(&ms, 0, sizeof(ms));
		ms.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		ms.pSampleMask = NULL;
		ms.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

		VkVertexInputBindingDescription vi_bindings[3];
		memset(vi_bindings, 0, sizeof(vi_bindings));
		VkVertexInputAttributeDescription vi_attrs[3];
		memset(vi_attrs, 0, sizeof(vi_attrs));

		//
		auto bindingIdx = 0;

		// vertices
		vi_bindings[bindingIdx].binding = bindingIdx;
		vi_bindings[bindingIdx].stride = sizeof(float) * 3;
		vi_bindings[bindingIdx].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		vi_attrs[bindingIdx].binding = bindingIdx;
		vi_attrs[bindingIdx].location = bindingIdx;
		vi_attrs[bindingIdx].format = VK_FORMAT_R32G32B32_SFLOAT;
		vi_attrs[bindingIdx].offset = 0;
		bindingIdx++;

		// normals
		/*
		vi_bindings[bindingIdx].binding = 1;
		vi_bindings[bindingIdx].stride = sizeof(float) * 3;
		vi_bindings[bindingIdx].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		vi_attrs[bindingIdx].binding = 1;
		vi_attrs[bindingIdx].location = 1;
		vi_attrs[bindingIdx].format = VK_FORMAT_R32G32B32_SFLOAT;
		vi_attrs[bindingIdx].offset = 0;
		bindingIdx++;
		*/

		// texture coordinates
		vi_bindings[bindingIdx].binding = bindingIdx;
		vi_bindings[bindingIdx].stride = sizeof(float) * 2;
		vi_bindings[bindingIdx].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		vi_attrs[bindingIdx].binding = bindingIdx;
		vi_attrs[bindingIdx].location = bindingIdx;
		vi_attrs[bindingIdx].format = VK_FORMAT_R32G32_SFLOAT;
		vi_attrs[bindingIdx].offset = 0;
		bindingIdx++;

		// colors
		vi_bindings[bindingIdx].binding = bindingIdx;
		vi_bindings[bindingIdx].stride = sizeof(float) * 4;
		vi_bindings[bindingIdx].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		vi_attrs[bindingIdx].binding = bindingIdx;
		vi_attrs[bindingIdx].location = bindingIdx;
		vi_attrs[bindingIdx].format = VK_FORMAT_R32G32B32A32_SFLOAT;
		vi_attrs[bindingIdx].offset = 0;
		bindingIdx++;

		memset(&vi, 0, sizeof(vi));
		vi.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vi.pNext = NULL;
		vi.vertexBindingDescriptionCount = bindingIdx;
		vi.pVertexBindingDescriptions = vi_bindings;
		vi.vertexAttributeDescriptionCount = bindingIdx;
		vi.pVertexAttributeDescriptions = vi_attrs;

		pipeline.pVertexInputState = &vi;
		pipeline.pInputAssemblyState = &ia;
		pipeline.pRasterizationState = &rs;
		pipeline.pColorBlendState = &cb;
		pipeline.pMultisampleState = &ms;
		pipeline.pViewportState = &vp;
		pipeline.pDepthStencilState = &ds;
		pipeline.pStages = shaderStages;
		pipeline.renderPass = context.render_pass;
		pipeline.pDynamicState = &dynamicState;

		memset(&pipelineCache, 0, sizeof(pipelineCache));
		pipelineCache.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;

		err = vkCreatePipelineCache(context.device, &pipelineCache, NULL, &program.pipelineCache);
		assert(!err);

		err = vkCreateGraphicsPipelines(context.device, program.pipelineCache, 1, &pipeline, NULL, &program.pipeline);
		assert(!err);

		vkDestroyPipelineCache(context.device, program.pipelineCache, NULL);

		//
		program.created_pipeline = true;
	} else {
		auto shaderIdx = 0;
		for (auto shaderId: program.shader_ids) {
			auto shaderIt = context.shaders.find(shaderId);
			if (shaderIt == context.shaders.end()) {
				Console::println("VKRenderer::" + string(__FUNCTION__) + "(): shader does not exist: " + to_string(shaderId));
				return;
			}
			auto& shader = shaderIt->second;
			context.uniform_buffers[shaderIdx].resize(shader.ubo_size);
			shaderIdx++;
		}
	}
}

void VKRenderer::useProgram(int32_t programId)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + to_string(programId));

	// if unsetting program flush command buffers
	if (programId == 0) {
		finishSetupCommandBuffer();
		flushCommands();
		finishPipeline();
		return;
	}

	context.program_id = 0;
	auto programIt = context.programs.find(programId);
	if (programIt == context.programs.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program does not exist: " + to_string(programId));
		return;
	}
	auto& program = programIt->second;
	preparePipeline(program);
	context.program_id = programId;
}

int32_t VKRenderer::createProgram()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	auto& programStruct = context.programs[context.program_idx];
	programStruct.id = context.program_idx++;
	programStruct.created_pipeline = false;
	return programStruct.id;
}

void VKRenderer::attachShaderToProgram(int32_t programId, int32_t shaderId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	auto shaderIt = context.shaders.find(shaderId);
	if (shaderIt == context.shaders.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): shader does not exist");
		return;
	}
	auto programIt = context.programs.find(programId);
	if (programIt == context.programs.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program does not exist");
		return;
	}
	programIt->second.shader_ids.push_back(shaderId);
}

bool VKRenderer::linkProgram(int32_t programId)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	auto programIt = context.programs.find(programId);
	if (programIt == context.programs.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program does not exist");
		return false;
	}
	map<string, int32_t> uniformsByName;
	auto uniformIdx = 1;
	for (auto shaderId: programIt->second.shader_ids) {
		auto shaderIt = context.shaders.find(shaderId);
		if (shaderIt == context.shaders.end()) {
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): shader does not exist");
			return false;
		}
		for (auto& uniformIt: shaderIt->second.uniforms) {
			uniformsByName[uniformIt.first] = uniformIdx++;
		}
	}
	for (auto& uniformIt: uniformsByName) {
		programIt->second.uniforms[uniformIt.second] = uniformIt.first;
	}
	return true;
}

int32_t VKRenderer::getProgramUniformLocation(int32_t programId, const string& name)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + name);
	auto programIt = context.programs.find(programId);
	if (programIt == context.programs.end()) {
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

void VKRenderer::setProgramUniformInternal(int32_t uniformId, uint8_t* data, int32_t size) {
	auto programIt = context.programs.find(context.program_id);
	if (programIt == context.programs.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program not found: " + to_string(context.program_id));
		return;
	}
	auto& program = programIt->second;
	auto uniformIt = program.uniforms.find(uniformId);
	if (uniformIt == program.uniforms.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): uniform does not exist: " + to_string(uniformId));
		return;
	}

	auto changedUniforms = 0;
	auto shaderIdx = 0;
	for (auto& shaderId: program.shader_ids) {
		auto shaderIt = context.shaders.find(shaderId);
		if (shaderIt == context.shaders.end()) {
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
		if (context.uniform_buffers[shaderIdx].size() < shaderUniform.position + size) {
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program: uniform buffer is too small");
			shaderIdx++;
			continue;
		}
		for (auto i = 0; i < size; i++) {
			context.uniform_buffers[shaderIdx][shaderUniform.position + i] = data[i];
		}
		changedUniforms++;
		shaderIdx++;
	}
	if (changedUniforms == 0) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program: no uniform: " + uniformIt->second);
	}
}

void VKRenderer::setProgramUniformInteger(int32_t uniformId, int32_t value)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	setProgramUniformInternal(uniformId, (uint8_t*)&value, sizeof(int32_t));
}

void VKRenderer::setProgramUniformFloat(int32_t uniformId, float value)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	setProgramUniformInternal(uniformId, (uint8_t*)&value, sizeof(float));
}

void VKRenderer::setProgramUniformFloatMatrix3x3(int32_t uniformId, const array<float, 9>& data)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	array<float, 12> _data;
	_data[0] = data[0];
	_data[1] = data[1];
	_data[2] = data[2];
	_data[3] = 0.0;
	_data[4] = data[3];
	_data[5] = data[4];
	_data[6] = data[5];
	_data[7] = 0.0;
	_data[8] = data[6];
	_data[9] = data[7];
	_data[10] = data[8];
	_data[11] = 0.0;
	setProgramUniformInternal(uniformId, (uint8_t*)_data.data(), _data.size() * sizeof(float));
}

void VKRenderer::setProgramUniformFloatMatrix4x4(int32_t uniformId, const array<float, 16>& data)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	setProgramUniformInternal(uniformId, (uint8_t*)data.data(), data.size() * sizeof(float));
}

void VKRenderer::setProgramUniformFloatMatrices4x4(int32_t uniformId, int32_t count, FloatBuffer* data)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	setProgramUniformInternal(uniformId, (uint8_t*)data->getBuffer(), count * sizeof(float) * 16);
}

void VKRenderer::setProgramUniformFloatVec4(int32_t uniformId, const array<float, 4>& data)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	setProgramUniformInternal(uniformId, (uint8_t*)data.data(), data.size() * sizeof(float));
}

void VKRenderer::setProgramUniformFloatVec3(int32_t uniformId, const array<float, 3>& data)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	setProgramUniformInternal(uniformId, (uint8_t*)data.data(), data.size() * sizeof(float));
}

void VKRenderer::setProgramAttributeLocation(int32_t programId, int32_t location, const string& name)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setViewPort(int32_t x, int32_t y, int32_t width, int32_t height)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");

	//
	memset(&context.viewport, 0, sizeof(context.viewport));
	context.viewport.width = (float)width;
	context.viewport.height = (float)height;
	context.viewport.x = (float)x;
	context.viewport.y = (float)y;
	context.viewport.minDepth = 0.0f;
	context.viewport.maxDepth = 1.0f;

	memset(&context.scissor, 0, sizeof(context.scissor));
	context.scissor.extent.width = width;
	context.scissor.extent.height = height;
	context.scissor.offset.x = x;
	context.scissor.offset.y = y;

	//
	vkCmdSetViewport(context.draw_cmd, 0, 1, &context.viewport);
	vkCmdSetScissor(context.draw_cmd, 0, 1, &context.scissor);
}

void VKRenderer::updateViewPort()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	vkCmdSetViewport(context.draw_cmd, 0, 1, &context.viewport);
	vkCmdSetScissor(context.draw_cmd, 0, 1, &context.scissor);
}

void VKRenderer::setClearColor(float red, float green, float blue, float alpha)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");

	//
	context.clear_red = red;
	context.clear_green = green;
	context.clear_blue = blue;
	context.clear_alpha = alpha;
}

void VKRenderer::enableCulling()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::disableCulling()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::enableBlending()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::disableBlending()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::enableDepthBufferWriting()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::disableDepthBufferWriting()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::disableDepthBufferTest()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::enableDepthBufferTest()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setDepthFunction(int32_t depthFunction)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setColorMask(bool red, bool green, bool blue, bool alpha)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::clear(int32_t mask)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setCullFace(int32_t cullFace)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setFrontFace(int32_t frontFace)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

int32_t VKRenderer::createTexture()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	auto& texture_object = context.textures[context.texture_idx];
	texture_object.id = context.texture_idx++;
	texture_object.uploaded = false;
	return texture_object.id;
}

int32_t VKRenderer::createDepthBufferTexture(int32_t width, int32_t height)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");

	auto& depth_buffer_texture = context.textures[context.texture_idx];
	depth_buffer_texture.id = context.texture_idx++;
	depth_buffer_texture.format = VK_FORMAT_D32_SFLOAT;
	depth_buffer_texture.uploaded = false;

	const VkImageCreateInfo image = {
		sType: VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
		pNext: NULL,
		flags: 0,
		imageType: VK_IMAGE_TYPE_2D,
		format: depth_buffer_texture.format,
		extent: {
			width: width,
			height: height,
			depth: 1
		},
		mipLevels: 1,
		arrayLayers: 1,
		samples: VK_SAMPLE_COUNT_1_BIT,
		tiling: VK_IMAGE_TILING_OPTIMAL,
		usage: VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
		sharingMode: VK_SHARING_MODE_EXCLUSIVE,
		queueFamilyIndexCount: 0,
		pQueueFamilyIndices: 0,
		initialLayout: (VkImageLayout)0,
	};
	VkMemoryAllocateInfo mem_alloc = {
		sType: VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		pNext: NULL,
		allocationSize: 0,
		memoryTypeIndex: 0,
	};

	VkMemoryRequirements mem_reqs;
	VkResult err;
	bool pass;

	/* create image */
	err = vkCreateImage(context.device, &image, NULL, &depth_buffer_texture.image);
	assert(!err);

	/* get memory requirements for this object */
	vkGetImageMemoryRequirements(context.device, depth_buffer_texture.image, &mem_reqs);

	/* select memory size and type */
	mem_alloc.allocationSize = mem_reqs.size;
	pass = memoryTypeFromProperties(mem_reqs.memoryTypeBits, 0, &mem_alloc.memoryTypeIndex);
	assert(pass);

	/* allocate memory */
	err = vkAllocateMemory(context.device, &mem_alloc, NULL, &depth_buffer_texture.mem);
	assert(!err);

	/* bind memory */
	err = vkBindImageMemory(context.device, depth_buffer_texture.image, depth_buffer_texture.mem, 0);
	assert(!err);

	Console::println(string(__FUNCTION__) + ": " + to_string(__LINE__) + ": setImageLayout()");

	depth_buffer_texture.image_layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
	setImageLayout(
		true,
		depth_buffer_texture.image,
		VK_IMAGE_ASPECT_DEPTH_BIT,
		VK_IMAGE_LAYOUT_UNDEFINED,
		depth_buffer_texture.image_layout,
		(VkAccessFlagBits)0
	);

	VkImageViewCreateInfo view = {
		sType: VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
		pNext: NULL,
		flags: 0,
		image: depth_buffer_texture.image,
		viewType: VK_IMAGE_VIEW_TYPE_2D,
		format: depth_buffer_texture.format,
		components: VkComponentMapping(),
		subresourceRange: {
			aspectMask: VK_IMAGE_ASPECT_DEPTH_BIT,
			baseMipLevel: 0,
			levelCount: 1,
			baseArrayLayer: 0,
			layerCount: 1
		},
	};

	/* create image view */
	err = vkCreateImageView(context.device, &view, NULL, &depth_buffer_texture.view);
	assert(!err);

	depth_buffer_texture.sampler = VK_NULL_HANDLE;

	// done
	return depth_buffer_texture.id;
}

int32_t VKRenderer::createColorBufferTexture(int32_t width, int32_t height)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");

	auto& color_buffer = context.textures[context.texture_idx];
	color_buffer.id = context.texture_idx++;

	/*
	VkResult err;
	VkImageViewCreateInfo color_attachment_view =
		{
			sType: VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
			pNext: NULL,
			flags: 0,
			image: color_buffer.image,
			viewType: VK_IMAGE_VIEW_TYPE_2D,
			format: VK_FORMAT_R8G8B8A8_UNORM,
			components: {
				r: VK_COMPONENT_SWIZZLE_R,
				g: VK_COMPONENT_SWIZZLE_G,
				b: VK_COMPONENT_SWIZZLE_B,
				a: VK_COMPONENT_SWIZZLE_A,
			},
			subresourceRange: {
				aspectMask: VK_IMAGE_ASPECT_COLOR_BIT,
				baseMipLevel: 0,
				levelCount: 1,
				baseArrayLayer: 0,
				layerCount: 1
			},
		};

	err = vkCreateImageView(context.device, &color_attachment_view, NULL, &color_buffer.view);
	assert(!err);
	*/

	return color_buffer.id;
}

void VKRenderer::uploadTexture(Texture* texture)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	auto textureObjectIt = context.textures.find(context.bound_texture_id);
	if (textureObjectIt == context.textures.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): texture not found: " + to_string(context.bound_texture_id));
		return;
	}
	auto& texture_object = textureObjectIt->second;

	if (texture_object.uploaded == true) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): texture already uploaded: " + to_string(context.bound_texture_id));
		return;
	}

	const VkFormat tex_format = texture->getHeight() == 32?VK_FORMAT_R8G8B8A8_UNORM:VK_FORMAT_R8G8B8A8_UNORM;
	VkFormatProperties props;
	VkResult err;

	vkGetPhysicalDeviceFormatProperties(context.gpu, tex_format, &props);
	/*
	if (props.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) {
		// Must use staging buffer to copy linear texture to optimized
		struct texture_object staging_texture;

		memset(&staging_texture, 0, sizeof(staging_texture));

		prepareTextureImage(
			&staging_texture,
			VK_IMAGE_TILING_LINEAR,
			VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			texture
		);
		prepareTextureImage(
			&texture_object,
			VK_IMAGE_TILING_OPTIMAL,
			VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			texture
		);
		setImageLayout(
			false,
			staging_texture.image,
			VK_IMAGE_ASPECT_COLOR_BIT,
			staging_texture.image_layout,
			VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
			(VkAccessFlagBits)0
		);
		setImageLayout(
			false,
			texture_object.image,
			VK_IMAGE_ASPECT_COLOR_BIT,
			texture_object.image_layout,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			(VkAccessFlagBits)0
		);
		VkImageCopy copy_region = {
			srcSubresource: {
				aspectMask: VK_IMAGE_ASPECT_COLOR_BIT,
				mipLevel: 0,
				baseArrayLayer: 0,
				layerCount: 1
			},
			srcOffset: {
				x: 0,
				y: 0,
				z: 0
			},
			dstSubresource: {
				aspectMask: VK_IMAGE_ASPECT_COLOR_BIT,
				mipLevel: 0,
				baseArrayLayer: 0,
				layerCount: 1
			},
			dstOffset: {
				x: 0,
				y: 0,
				z: 0
			},
			extent: {
				width: staging_texture.tex_width,
				height: staging_texture.tex_height,
				depth: 1
			},
		};
		vkCmdCopyImage(
			context.draw_cmd,
			staging_texture.image,
			VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
			texture_object.image,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			1,
			&copy_region
		);

		setImageLayout(
			false,
			texture_object.image,
			VK_IMAGE_ASPECT_COLOR_BIT,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			texture_object.image_layout,
			(VkAccessFlagBits)0
		);

		// mark for deletion
		context.images_delete.push_back(staging_texture.image);
		context.memory_delete.push_back(staging_texture.mem);
	} else
	*/
	if ((props.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)) {
		/* Device can texture using linear textures */
		prepareTextureImage(
			&texture_object,
			VK_IMAGE_TILING_LINEAR,
			VK_IMAGE_USAGE_SAMPLED_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			texture
		);
	} else {
		/* Can't support VK_FORMAT_B8G8R8A8_UNORM !? */
		assert(!"No support for B8G8R8A8_UNORM as texture image format");
	}

	const VkSamplerCreateInfo sampler = {
		sType: VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
		pNext: NULL,
		flags: 0,
		magFilter: VK_FILTER_LINEAR,
		minFilter: VK_FILTER_LINEAR,
		mipmapMode: VK_SAMPLER_MIPMAP_MODE_LINEAR,
		addressModeU: VK_SAMPLER_ADDRESS_MODE_REPEAT,
		addressModeV: VK_SAMPLER_ADDRESS_MODE_REPEAT,
		addressModeW: VK_SAMPLER_ADDRESS_MODE_REPEAT,
		mipLodBias: 0.0f,
		anisotropyEnable: VK_FALSE,
		maxAnisotropy: 1,
		compareEnable: VK_FALSE,
		compareOp: VK_COMPARE_OP_NEVER,
		minLod: 0.0f,
		maxLod: 0.0f,
		borderColor: VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE,
		unnormalizedCoordinates: VK_FALSE,
	};
	VkImageViewCreateInfo view = {
		sType: VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
		pNext: NULL,
		flags: 0,
		image: texture_object.image,
		viewType: VK_IMAGE_VIEW_TYPE_2D,
		format: tex_format,
		components: {
			r: VK_COMPONENT_SWIZZLE_R,
			g: VK_COMPONENT_SWIZZLE_G,
			b: VK_COMPONENT_SWIZZLE_B,
			a: VK_COMPONENT_SWIZZLE_A,
		},
		subresourceRange: {
			aspectMask: VK_IMAGE_ASPECT_COLOR_BIT,
			baseMipLevel: 0,
			levelCount: 1,
			baseArrayLayer: 0,
			layerCount: 1
		},
	};

	// create sampler
	err = vkCreateSampler(context.device, &sampler, NULL, &texture_object.sampler);
	assert(!err);

	// create image view
	err = vkCreateImageView(context.device, &view, NULL, &texture_object.view);
	assert(!err);

	//
	texture_object.uploaded = true;
}

void VKRenderer::resizeDepthBufferTexture(int32_t textureId, int32_t width, int32_t height)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::resizeColorBufferTexture(int32_t textureId, int32_t width, int32_t height)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindTexture(int32_t textureId)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	auto textureObjectIt = context.textures.find(textureId);
	context.bound_texture_id = 0;
	if (textureId != 0) {
		if (textureObjectIt == context.textures.end()) {
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): texture not found: " + to_string(context.bound_texture_id));
			return;
		}
	}
	context.bound_texture_id = textureId;
	onBindTexture(textureId);
}

void VKRenderer::disposeTexture(int32_t textureId)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");

	Console::println(to_string(textureId));

	auto textureObjectIt = context.textures.find(textureId);
	if (textureObjectIt == context.textures.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): texture not found: " + to_string(textureId));
		return;
	}

	auto& texture = textureObjectIt->second;
	vkDestroyImageView(context.device, texture.view, NULL);
	vkDestroyImage(context.device, texture.image, NULL);
	vkFreeMemory(context.device, texture.mem, NULL);
	vkDestroySampler(context.device, texture.sampler, NULL);

	context.textures.erase(textureObjectIt);
}

int32_t VKRenderer::createFramebufferObject(int32_t depthBufferTextureGlId, int32_t colorBufferTextureGlId)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return -1;
}

void VKRenderer::bindFrameBuffer(int32_t frameBufferId)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::disposeFrameBufferObject(int32_t frameBufferId)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

vector<int32_t> VKRenderer::createBufferObjects(int32_t buffers)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	vector<int32_t> bufferIds;
	for (auto i = 0; i < buffers; i++) {
		buffer_object buffer;
		buffer.id = context.buffer_idx++;
		buffer.alloc_size = 0;
		buffer.size = 0;
		context.buffers[buffer.id] = buffer;
		bufferIds.push_back(buffer.id);
	}
	return bufferIds;
}

VkBuffer VKRenderer::getBufferObjectInternal(int32_t bufferObjectId) {
	if (VERBOSE == true) Console::println("getBufferObjectInternal::" + string(__FUNCTION__) + "()");
	auto bufferIt = context.buffers.find(bufferObjectId);
	if (bufferIt == context.buffers.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): buffer with id " + to_string(bufferObjectId) + " does not exist");
		return VK_NULL_HANDLE;
	}
	return bufferIt->second.buf;
}

void VKRenderer::uploadBufferObjectInternal(int32_t bufferObjectId, int32_t size, const uint8_t* data, VkBufferUsageFlagBits usage) {
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	auto bufferIt = context.buffers.find(bufferObjectId);
	if (bufferIt == context.buffers.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): buffer with id " + to_string(bufferObjectId) + " does not exist");
		return;
	}
	auto& buffer = bufferIt->second;

	//
	VkResult err;

	if (buffer.size > 0) {
		context.memory_delete.push_back(buffer.mem);
		context.buffers_delete.push_back(buffer.buf);
	}

	buffer.mem = VK_NULL_HANDLE;
	buffer.buf = VK_NULL_HANDLE;

	const VkBufferCreateInfo buf_info = {
		sType: VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
		pNext: NULL,
		flags: 0,
		size: size,
		usage: usage,
		sharingMode: VK_SHARING_MODE_EXCLUSIVE,
		queueFamilyIndexCount: 0,
		pQueueFamilyIndices: NULL
	};
	VkMemoryAllocateInfo mem_alloc = {
		sType: VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		pNext: NULL,
		allocationSize: 0,
		memoryTypeIndex: 0
	};

	VkMemoryRequirements mem_reqs;
	bool pass;

	err = vkCreateBuffer(context.device, &buf_info, NULL, &buffer.buf);
	assert(err == VK_SUCCESS);

	vkGetBufferMemoryRequirements(context.device, buffer.buf, &mem_reqs);

	mem_alloc.allocationSize = mem_reqs.size;
	pass = memoryTypeFromProperties(mem_reqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &mem_alloc.memoryTypeIndex);
	assert(pass);

	buffer.alloc_size = mem_alloc.allocationSize;

	err = vkAllocateMemory(context.device, &mem_alloc, NULL, &buffer.mem);
	assert(err == VK_SUCCESS);

	//
	buffer.size = size;

	// map memory
	void* buffer_data;
	err = vkMapMemory(context.device, buffer.mem, 0, buffer.alloc_size, 0, &buffer_data);
	assert(err == VK_SUCCESS);

	//
	memcpy(buffer_data, data, size);
	VkMappedMemoryRange mappedMemoryRange = {
		sType: VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
		pNext: NULL,
		memory: buffer.mem,
		offset: 0,
		size: buffer.alloc_size
	};
	vkFlushMappedMemoryRanges(context.device, 1, &mappedMemoryRange);

	//
	vkUnmapMemory(context.device, buffer.mem);

	// bind if (re)created
	err = vkBindBufferMemory(context.device, buffer.buf, buffer.mem, 0);
	assert(!err);
}

void VKRenderer::uploadBufferObject(int32_t bufferObjectId, int32_t size, FloatBuffer* data)
{
	uploadBufferObjectInternal(bufferObjectId, size, data->getBuffer(), (VkBufferUsageFlagBits)(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT));
}

void VKRenderer::uploadIndicesBufferObject(int32_t bufferObjectId, int32_t size, ShortBuffer* data)
{
	uploadBufferObjectInternal(bufferObjectId, size, data->getBuffer(), (VkBufferUsageFlagBits)(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT));
}

void VKRenderer::uploadIndicesBufferObject(int32_t bufferObjectId, int32_t size, IntBuffer* data)
{
	uploadBufferObjectInternal(bufferObjectId, size, data->getBuffer(), (VkBufferUsageFlagBits)(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT));
}

void VKRenderer::bindIndicesBufferObject(int32_t bufferObjectId)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	context.bound_indices_buffer = bufferObjectId;
}

void VKRenderer::bindTextureCoordinatesBufferObject(int32_t bufferObjectId)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	// context.boundBuffers[2] = bufferObjectId;
	context.bound_buffers[1] = bufferObjectId;
}

void VKRenderer::bindVerticesBufferObject(int32_t bufferObjectId)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	context.bound_buffers[0] = bufferObjectId;
}

void VKRenderer::bindNormalsBufferObject(int32_t bufferObjectId)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	// context.boundBuffers[1] = bufferObjectId;
}

void VKRenderer::bindColorsBufferObject(int32_t bufferObjectId)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	//context.boundBuffers[3] = bufferObjectId;
	context.bound_buffers[2] = bufferObjectId;
}

void VKRenderer::bindTangentsBufferObject(int32_t bufferObjectId)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindBitangentsBufferObject(int32_t bufferObjectId)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindModelMatricesBufferObject(int32_t bufferObjectId)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindEffectColorMulsBufferObject(int32_t bufferObjectId)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindEffectColorAddsBufferObject(int32_t bufferObjectId)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::drawInstancedIndexedTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset, int32_t instances)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::drawIndexedTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset)
{
	// TODO
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");

	// upload uniforms
	auto programIt = context.programs.find(context.program_id);
	if (programIt == context.programs.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program does not exist: " + to_string(context.program_id));
		return;
	}
	program_type& program = programIt->second;

	context.render_commands.push_back(context_type::render_command());
	auto& render_command = context.render_commands[context.render_commands.size() - 1];

	auto shaderIdx = 0;
	for (auto& shaderId: program.shader_ids) {
		auto shaderIt = context.shaders.find(shaderId);
		if (shaderIt == context.shaders.end()) {
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): shader does not exist: " + to_string(shaderId));
			return;
		}
		auto& shader = shaderIt->second;

		if (shader.ubo_size == 0) {
			shaderIdx++;
			continue;
		}

		auto uboBindingIdx = getUniformBufferObjectBindingIdx(shader.type);
		uploadBufferObjectInternal(shader.uniform_buffer, context.uniform_buffers[shaderIdx].size(), context.uniform_buffers[shaderIdx].data(), (VkBufferUsageFlagBits)(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT));
		render_command.ubo_buffers[uboBindingIdx] = getBufferObjectInternal(shader.uniform_buffer);
		shaderIdx++;
	}

	auto textureObjectIt = context.textures.find(context.bound_texture_id);
	if (textureObjectIt == context.textures.end()) {
		textureObjectIt = context.textures.find(context.white_texture_default);
	}
	if (textureObjectIt == context.textures.end()) {
		context.white_texture_default = Engine::getInstance()->getTextureManager()->addTexture(TextureReader::read("resources/engine/textures", "transparent_pixel.png"));
		textureObjectIt = context.textures.find(context.white_texture_default);
	}

	auto& texture_object = textureObjectIt->second;

	//
	render_command.indices_buffer = getBufferObjectInternal(context.bound_indices_buffer);
	render_command.vertex_buffers[0] = getBufferObjectInternal(context.bound_buffers[0]);
	render_command.vertex_buffers[1] = getBufferObjectInternal(context.bound_buffers[1]);
	render_command.vertex_buffers[2] = getBufferObjectInternal(context.bound_buffers[2]);
	render_command.textures[0].sampler = texture_object.sampler;
	render_command.textures[0].view = texture_object.view;
	render_command.textures[0].image_layout = texture_object.image_layout;
	render_command.count = triangles;
	render_command.offset = trianglesOffset;
}

void VKRenderer::flushCommands() {
	if (context.render_commands.size() == 0) return;

	auto programIt = context.programs.find(context.program_id);
	if (programIt == context.programs.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program does not exist: " + to_string(context.program_id));
		return;
	}
	auto& program = programIt->second;

	// create pipeline
	createPipeline(program);

	VkDescriptorBufferInfo bufferInfos[2];
	VkWriteDescriptorSet descriptorSetWrites[3];
	vector<VKRenderer::context_type::render_command> render_commands_left;

	//
	vkCmdBindPipeline(context.draw_cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, program.pipeline);

	//
	auto desc_used = 0;
	for (auto& command: context.render_commands) {
		if (desc_used == program.desc_max) {
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): desc_used == desc_max");
			break;
		}
		auto shaderIdx = 0;
		for (auto& shaderId: program.shader_ids) {
			auto shaderIt = context.shaders.find(shaderId);
			if (shaderIt == context.shaders.end()) {
				Console::println("VKRenderer::" + string(__FUNCTION__) + "(): shader does not exist: " + to_string(shaderId));
				return;
			}
			auto& shader = shaderIt->second;

			if (shader.ubo_size == 0) {
				shaderIdx++;
				continue;
			}

			auto uboBindingIdx = getUniformBufferObjectBindingIdx(shader.type);
			bufferInfos[uboBindingIdx] = {
				buffer: command.ubo_buffers[uboBindingIdx],
				offset: 0,
				range: shader.ubo_size
			};

			descriptorSetWrites[uboBindingIdx] = {
				sType: VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
				pNext: NULL,
				dstSet: program.desc_set[desc_used],
				dstBinding: uboBindingIdx,
				dstArrayElement: 0,
				descriptorCount: 1,
				descriptorType: VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
				pImageInfo: NULL,
				pBufferInfo: &bufferInfos[uboBindingIdx],
				pTexelBufferView: NULL,
			};
			shaderIdx++;
		}

		VkDescriptorImageInfo tex_descs;
		tex_descs.sampler = command.textures[0].sampler;
		tex_descs.imageView = command.textures[0].view;
		tex_descs.imageLayout = command.textures[0].image_layout;

		descriptorSetWrites[2] = {
			sType: VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
			pNext: NULL,
			dstSet: program.desc_set[desc_used],
			dstBinding: 2,
			dstArrayElement: 0,
			descriptorCount: 1,
			descriptorType: VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
			pImageInfo: &tex_descs,
			pBufferInfo: VK_NULL_HANDLE,
			pTexelBufferView: VK_NULL_HANDLE
		};

		//
		vkUpdateDescriptorSets(context.device, 3, descriptorSetWrites, 0, NULL);
		vkCmdBindDescriptorSets(context.draw_cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, program.pipeline_layout, 0, 1, &program.desc_set[desc_used], 0, nullptr);
		vkCmdBindIndexBuffer(context.draw_cmd, command.indices_buffer, 0, VK_INDEX_TYPE_UINT32);
		VkBuffer vertexBuffersBuffer[3] = {command.vertex_buffers[0], command.vertex_buffers[1], command.vertex_buffers[2]};
		VkDeviceSize vertexBuffersOffsets[3] = { 0, 0, 0 };
		vkCmdBindVertexBuffers(context.draw_cmd, 0, 3, vertexBuffersBuffer, vertexBuffersOffsets);
		vkCmdDrawIndexed(context.draw_cmd, command.count * 3, 1, command.offset * 3, 0, 0);

		desc_used++;
	}

	//
	context.render_commands.clear();
}

void VKRenderer::drawInstancedTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset, int32_t instances)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::drawTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::drawPointsFromBufferObjects(int32_t points, int32_t pointsOffset)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::unbindBufferObjects()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	context.bound_indices_buffer = 0;
	context.bound_buffers.fill(0);
}

void VKRenderer::disposeBufferObjects(vector<int32_t>& bufferObjectIds)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	for (auto bufferObjectId: bufferObjectIds) {
		auto bufferIt = context.buffers.find(bufferObjectId);
		if (bufferIt == context.buffers.end()) {
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): buffer with id " + to_string(bufferObjectId) + " does not exist");
			continue;
		}
		auto& buffer = bufferIt->second;
		if (buffer.size == 0) {
			context.buffers.erase(bufferIt);
			continue;
		}
		if (buffer.size > 0) {
			vkDestroyBuffer(context.device, buffer.buf, NULL);
			vkFreeMemory(context.device, buffer.mem, NULL);
		}
		context.buffers.erase(bufferIt);
	}
}

int32_t VKRenderer::getTextureUnit()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return activeTextureUnit;
}

void VKRenderer::setTextureUnit(int32_t textureUnit)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	this->activeTextureUnit = textureUnit;
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
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::doneGuiMode()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::checkGLError(int line)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::dispatchCompute(int32_t numGroupsX, int32_t numGroupsY, int32_t numGroupsZ) {
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::memoryBarrier() {
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::uploadSkinningBufferObject(int32_t bufferObjectId, int32_t size, FloatBuffer* data) {
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::uploadSkinningBufferObject(int32_t bufferObjectId, int32_t size, IntBuffer* data) {
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindSkinningVerticesBufferObject(int32_t bufferObjectId) {
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindSkinningNormalsBufferObject(int32_t bufferObjectId) {
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindSkinningVertexJointsBufferObject(int32_t bufferObjectId) {
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindSkinningVertexJointIdxsBufferObject(int32_t bufferObjectId) {
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindSkinningVertexJointWeightsBufferObject(int32_t bufferObjectId) {
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindSkinningVerticesResultBufferObject(int32_t bufferObjectId) {
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindSkinningNormalsResultBufferObject(int32_t bufferObjectId) {
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindSkinningMatricesBufferObject(int32_t bufferObjectId) {
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}
