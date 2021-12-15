/**
 * Vulkan renderer
 * based on
 * 	https://github.com/glfw/glfw/blob/master/tests/vulkan.c and util.c from Vulkan samples
 * 	https://vulkan-tutorial.com
 * 	https://github.com/KhronosGroup/Vulkan-Docs/wiki/Synchronization-Examples
 * 	https://github.com/SaschaWillems/Vulkan
 * 	...
 */

#include <tdme/engine/subsystems/renderer/VKRenderer.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <ext/vulkan/glslang/Public/ShaderLang.h>
#include <ext/vulkan/spirv/GlslangToSpv.h>
#include <ext/vulkan/vma/src/VmaUsage.h>
#include <ext/vulkan/OGLCompilersDLL/InitializeDll.h>

#define THSVS_SIMPLER_VULKAN_SYNCHRONIZATION_IMPLEMENTATION
#include <ext/vulkan/svs/thsvs_simpler_vulkan_synchronization.h>

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

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/subsystems/renderer/VKGL3CoreShaderProgram.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/EntityShaderParameters.h>
#include <tdme/engine/FrameBuffer.h>
#include <tdme/engine/Timing.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/os/threading/AtomicOperations.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/os/threading/ReadWriteLock.h>
#include <tdme/utilities/Buffer.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/FloatBuffer.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/IntBuffer.h>
#include <tdme/utilities/ShortBuffer.h>
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/Time.h>

using std::floor;
using std::log2;
using std::max;
using std::to_string;

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define ERR_EXIT(err_msg, err_class)                                           \
    do {                                                                       \
        printf(err_msg);                                                       \
        fflush(stdout);                                                        \
        Application::exit(1);                                                  \
    } while (0)

#define GET_INSTANCE_PROC_ADDR(inst, entrypoint)														\
    {																											\
        fp##entrypoint = (PFN_vk##entrypoint)vkGetInstanceProcAddr(inst, "vk" #entrypoint);				\
        if (fp##entrypoint == nullptr) {																	\
            ERR_EXIT("vkGetInstanceProcAddr failed to find vk" #entrypoint, "vkGetInstanceProcAddr Failure");	\
        }                                                                      									\
    }

#define GET_DEVICE_PROC_ADDR(dev, entrypoint)																	\
    {																											\
        fp##entrypoint = (PFN_vk##entrypoint)vkGetDeviceProcAddr(dev, "vk" #entrypoint);				\
        if (fp##entrypoint == nullptr) {																	\
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
using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::renderer::VKGL3CoreShaderProgram;
using tdme::engine::Engine;
using tdme::engine::EntityShaderParameters;
using tdme::engine::FrameBuffer;
using tdme::engine::Timing;
using tdme::math::Matrix4x4;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::os::threading::AtomicOperations;
using tdme::os::threading::Mutex;
using tdme::os::threading::ReadWriteLock;
using tdme::utilities::Buffer;
using tdme::utilities::ByteBuffer;
using tdme::utilities::Console;
using tdme::utilities::FloatBuffer;
using tdme::utilities::Integer;
using tdme::utilities::IntBuffer;
using tdme::utilities::ShortBuffer;
using tdme::utilities::StringTools;
using tdme::utilities::Time;

VKRenderer::VKRenderer():
	queueSpinlock("queue-spinlock"),
	buffersRWlock("buffers_rwlock"),
	texturesRWlock("textures_rwlock"),
	deleteMutex("delete_mutex"),
	disposeMutex("dispose_mutex"),
	pipelineRWlock("pipeline_rwlock"),
	vmaSpinlock("vma_spinlock")
{
	// setup consts
	ID_NONE = 0;
	CLEAR_DEPTH_BUFFER_BIT = 2;
	CLEAR_COLOR_BUFFER_BIT = 1;
	CULLFACE_FRONT = VK_CULL_MODE_FRONT_BIT;
	CULLFACE_BACK = VK_CULL_MODE_BACK_BIT;
	FRONTFACE_CW = VK_FRONT_FACE_CLOCKWISE + 1;
	FRONTFACE_CCW = VK_FRONT_FACE_COUNTER_CLOCKWISE + 1;
	SHADER_FRAGMENT_SHADER = VK_SHADER_STAGE_FRAGMENT_BIT;
	SHADER_VERTEX_SHADER = VK_SHADER_STAGE_VERTEX_BIT;
	SHADER_COMPUTE_SHADER = VK_SHADER_STAGE_COMPUTE_BIT;
	DEPTHFUNCTION_ALWAYS = VK_COMPARE_OP_ALWAYS;
	DEPTHFUNCTION_EQUAL = VK_COMPARE_OP_EQUAL;
	DEPTHFUNCTION_LESSEQUAL = VK_COMPARE_OP_LESS_OR_EQUAL;
	DEPTHFUNCTION_GREATEREQUAL = VK_COMPARE_OP_GREATER_OR_EQUAL;
	FRAMEBUFFER_DEFAULT = 0;
	CUBEMAPTEXTUREINDEX_POSITIVE_X = 1;
	CUBEMAPTEXTUREINDEX_NEGATIVE_X = 2;
	CUBEMAPTEXTUREINDEX_POSITIVE_Y = 3;
	CUBEMAPTEXTUREINDEX_NEGATIVE_Y = 4;
	CUBEMAPTEXTUREINDEX_POSITIVE_Z = 5;
	CUBEMAPTEXTUREINDEX_NEGATIVE_Z = 6;
}

inline VkBool32 VKRenderer::checkLayers(uint32_t checkCount, const char **checkNames, uint32_t layerCount, VkLayerProperties *layers) {
	uint32_t i, j;
	for (i = 0; i < checkCount; i++) {
		VkBool32 found = 0;
		for (j = 0; j < layerCount; j++) {
			if (!strcmp(checkNames[i], layers[j].layerName)) {
				found = 1;
				break;
			}
		}
		if (!found) {
			fprintf(stderr, "Cannot find layer: %s\n", checkNames[i]);
			return 0;
		}
	}
	return 1;
}

inline void VKRenderer::prepareSetupCommandBuffer(int contextIdx) {
	auto& currentContext = contexts[contextIdx];
	if (currentContext.setupCommandInUse == VK_NULL_HANDLE) {
		currentContext.setupCommandInUse = currentContext.setupCommand;

		//
		const VkCommandBufferBeginInfo cmdBufInfo = {
			.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
			.pNext = nullptr,
			.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
			.pInheritanceInfo = nullptr
		};

		VkResult err;
		err = vkBeginCommandBuffer(currentContext.setupCommandInUse, &cmdBufInfo);
		assert(!err);

		//
		AtomicOperations::increment(statistics.drawCommands);
	}
}

inline void VKRenderer::finishSetupCommandBuffer(int contextIdx) {
	auto& currentContext = contexts[contextIdx];

	//
	if (currentContext.setupCommandInUse != VK_NULL_HANDLE) {
		//
		VkResult err;
		err = vkEndCommandBuffer(currentContext.setupCommandInUse);
		assert(!err);

		VkFence nullFence = { VK_NULL_HANDLE };
		VkSubmitInfo submitInfo = {
			.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
			.pNext = nullptr,
			.waitSemaphoreCount = 0,
			.pWaitSemaphores = nullptr,
			.pWaitDstStageMask = nullptr,
			.commandBufferCount = 1,
			.pCommandBuffers = &currentContext.setupCommandInUse,
			.signalSemaphoreCount = 0,
			.pSignalSemaphores = nullptr
		};

		queueSpinlock.lock();

		err = vkQueueSubmit(queue, 1, &submitInfo, currentContext.setupFence);
		assert(!err);

		//
		queueSpinlock.unlock();

		//
		AtomicOperations::increment(statistics.submits);

		//
		VkResult fenceResult;
		do {
			fenceResult = vkWaitForFences(device, 1, &currentContext.setupFence, VK_TRUE, 100000000);
		} while (fenceResult == VK_TIMEOUT);
		vkResetFences(device, 1, &currentContext.setupFence);

		//
		currentContext.setupCommandInUse = VK_NULL_HANDLE;
	}
}

inline bool VKRenderer::beginDrawCommandBuffer(int contextIdx, int bufferId) {
	auto& currentContext = contexts[contextIdx];

	//
	if (bufferId == -1) bufferId = currentContext.currentCommandBuffer;

	//
	auto& commandBuffer = currentContext.commandBuffers[bufferId];
	if (commandBuffer.drawCmdStarted == true) return false;

	//
	VkResult fenceResult;
	do {
		fenceResult = vkWaitForFences(device, 1, &commandBuffer.drawFence, VK_TRUE, 100000000);
	} while (fenceResult == VK_TIMEOUT);
	vkResetFences(device, 1, &commandBuffer.drawFence);

	//
	const VkCommandBufferBeginInfo cmdBufInfo = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		.pNext = nullptr,
		.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
		.pInheritanceInfo = nullptr
	};

	//
	VkResult err;
	err = vkBeginCommandBuffer(commandBuffer.drawCommand, &cmdBufInfo);
	assert(!err);

	array<ThsvsAccessType, 2> nextAccessTypes { THSVS_ACCESS_COLOR_ATTACHMENT_WRITE, THSVS_ACCESS_NONE };
	ThsvsImageLayout nextLayout { THSVS_IMAGE_LAYOUT_OPTIMAL };

	// check if we need a change at all
	if (boundFrameBuffer == ID_NONE &&
		(swapchainBuffers[currentFrameBuffer].accessTypes != nextAccessTypes || swapchainBuffers[currentFrameBuffer].svsLayout != nextLayout)) {
		ThsvsImageBarrier svsImageBarrier = {
			.prevAccessCount = static_cast<uint32_t>(swapchainBuffers[currentFrameBuffer].accessTypes[1] != THSVS_ACCESS_NONE?2:1),
			.pPrevAccesses = swapchainBuffers[currentFrameBuffer].accessTypes.data(),
			.nextAccessCount = static_cast<uint32_t>(nextAccessTypes[1] != THSVS_ACCESS_NONE?2:1),
			.pNextAccesses = nextAccessTypes.data(),
			.prevLayout = swapchainBuffers[currentFrameBuffer].svsLayout,
			.nextLayout = nextLayout,
			.discardContents = true,
			.srcQueueFamilyIndex = 0,
			.dstQueueFamilyIndex = 0,
			.image = swapchainBuffers[currentFrameBuffer].image,
			.subresourceRange = {
				.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
				.baseMipLevel = 0,
				.levelCount = 1,
				.baseArrayLayer = 0,
				.layerCount = 1
			}
		};
		VkImageMemoryBarrier vkImageMemoryBarrier;
		VkPipelineStageFlags srcStages;
		VkPipelineStageFlags dstStages;
		thsvsGetVulkanImageMemoryBarrier(
			svsImageBarrier,
			&srcStages,
			&dstStages,
			&vkImageMemoryBarrier
		);

		//
		VkResult err;

		//
		vkCmdPipelineBarrier(commandBuffer.drawCommand, srcStages, dstStages, 0, 0, nullptr, 0, nullptr, 1, &vkImageMemoryBarrier);

		//
		swapchainBuffers[currentFrameBuffer].accessTypes = nextAccessTypes;
		swapchainBuffers[currentFrameBuffer].svsLayout = nextLayout;
	}

	//
	commandBuffer.drawCmdStarted = true;

	//
	AtomicOperations::increment(statistics.drawCommands);

	//
	return true;
}

inline VkCommandBuffer VKRenderer::endDrawCommandBuffer(int contextIdx, int bufferId, bool cycleBuffers) {
	auto& currentContext = contexts[contextIdx];

	//
	if (bufferId == -1) bufferId = currentContext.currentCommandBuffer;
	auto& commandBuffer = currentContext.commandBuffers[bufferId];

	//
	currentContext.pipeline = VK_NULL_HANDLE;

	//
	if (commandBuffer.drawCmdStarted == false) return VK_NULL_HANDLE;

	//
	VkResult err;
	err = vkEndCommandBuffer(commandBuffer.drawCommand);
	assert(!err);

	//
	if (currentContext.program != nullptr) currentContext.lastUnsubmittedPrograms.push_back(currentContext.program);

	//
	for (auto program: currentContext.lastUnsubmittedPrograms) {
		auto& programContextCommandBuffer = program->contexts[contextIdx].commandBuffers[bufferId];
		programContextCommandBuffer.descriptorSets1Idx = 0;
		programContextCommandBuffer.descriptorSets2IdxUncached = 0;
	}

	//
	currentContext.lastUnsubmittedPrograms.clear();

	//
	auto endedCommandBuffer = commandBuffer.drawCommand;

	//
	commandBuffer.drawCmdStarted = false;

	//
	if (cycleBuffers == true) currentContext.currentCommandBuffer = (currentContext.currentCommandBuffer + 1) % DRAW_COMMANDBUFFER_MAX;

	//
	return endedCommandBuffer;
}

inline void VKRenderer::recreateContextFences(int contextIdx) {
	auto& currentContext = contexts[contextIdx];
	if (currentContext.draw_fence == VK_NULL_HANDLE) {
		VkFenceCreateInfo fenceCreateInfoUnsignaled = {
			.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0
		};
		vkCreateFence(device, &fenceCreateInfoUnsignaled, nullptr, &currentContext.draw_fence);
	}
	VkFenceCreateInfo fenceCreateInfoSignaled = {
		.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
		.pNext = nullptr,
		.flags = VK_FENCE_CREATE_SIGNALED_BIT
	};
	for (auto i = 0; i < DRAW_COMMANDBUFFER_MAX; i++) {
		if (currentContext.commandBuffers[i].drawFence != VK_NULL_HANDLE) vkDestroyFence(device, currentContext.commandBuffers[i].drawFence, nullptr);
		vkCreateFence(device, &fenceCreateInfoSignaled, nullptr, &currentContext.commandBuffers[i].drawFence);
	}
}

inline void VKRenderer::submitDrawCommandBuffers(int commandBufferCount, VkCommandBuffer* commandBuffers, VkFence& fence, bool waitUntilSubmitted, bool resetFence) {
	//
	VkResult err;
	VkPipelineStageFlags pipeStageFlags = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
	VkSubmitInfo submitInfo = {
		.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
		.pNext = nullptr,
		.waitSemaphoreCount = 0,
		.pWaitSemaphores = nullptr,
		.pWaitDstStageMask = &pipeStageFlags,
		.commandBufferCount = static_cast<uint32_t>(commandBufferCount),
		.pCommandBuffers = commandBuffers,
		.signalSemaphoreCount = 0,
		.pSignalSemaphores = nullptr
	};

	//
	queueSpinlock.lock();

	err = vkQueueSubmit(queue, 1, &submitInfo, fence);
	assert(!err);

	queueSpinlock.unlock();

	//
	AtomicOperations::increment(statistics.submits);

	//
	if (waitUntilSubmitted == true) {
		//
		VkResult fence_result;
		do {
			fence_result = vkWaitForFences(device, 1, &fence, VK_TRUE, 100000000);
		} while (fence_result == VK_TIMEOUT);
		if (resetFence == true) vkResetFences(device, 1, &fence);
	}
}

inline void VKRenderer::finishSetupCommandBuffers() {
	for (auto contextIdx = 0; contextIdx < Engine::getThreadCount(); contextIdx++) finishSetupCommandBuffer(contextIdx);
}

inline void VKRenderer::setImageLayout(int contextIdx, texture_type* textureObject, const array<ThsvsAccessType,2>& nextAccessTypes, ThsvsImageLayout nextLayout, bool discardContent, uint32_t baseMipLevel, uint32_t levelCount, bool submit) {
	auto& currentContext = contexts[contextIdx];

	// does this texture object point to a cube map color/depth buffer texture?
	auto _textureObject = textureObject->cubemapBufferTexture != nullptr?textureObject->cubemapBufferTexture:textureObject;

	// do not change a VK_IMAGE_LAYOUT_GENERAL
	if (_textureObject->vkLayout == VK_IMAGE_LAYOUT_GENERAL) {
		return;
	}

	// base array layer that applies to cube maps only
	auto baseArrayLayer = static_cast<uint32_t>(textureObject->cubemapBufferTexture != nullptr?textureObject->cubemapTextureIndex - CUBEMAPTEXTUREINDEX_MIN:0);

	// check if we need a change at all
	if (_textureObject->accessTypes[baseArrayLayer] == nextAccessTypes && _textureObject->svsLayout == nextLayout) return;

	ThsvsImageBarrier svsImageBarrier = {
		.prevAccessCount = static_cast<uint32_t>(_textureObject->accessTypes[baseArrayLayer][1] != THSVS_ACCESS_NONE?2:1),
		.pPrevAccesses = _textureObject->accessTypes[baseArrayLayer].data(),
		.nextAccessCount = static_cast<uint32_t>(nextAccessTypes[1] != THSVS_ACCESS_NONE?2:1),
		.pNextAccesses = nextAccessTypes.data(),
		.prevLayout = _textureObject->svsLayout,
		.nextLayout = nextLayout,
		.discardContents = discardContent,
		.srcQueueFamilyIndex = 0,
		.dstQueueFamilyIndex = 0,
		.image = _textureObject->image,
		.subresourceRange = {
			.aspectMask = _textureObject->aspectMask,
			.baseMipLevel = baseMipLevel,
			.levelCount = levelCount,
			.baseArrayLayer = baseArrayLayer,
			.layerCount = 1
		}
	};
	VkImageMemoryBarrier vkImageMemoryBarrier;
	VkPipelineStageFlags srcStages;
	VkPipelineStageFlags dstStages;
	thsvsGetVulkanImageMemoryBarrier(
		svsImageBarrier,
		&srcStages,
		&dstStages,
		&vkImageMemoryBarrier
	);

	//
	VkResult err;

	//
	prepareSetupCommandBuffer(contextIdx);
	vkCmdPipelineBarrier(currentContext.setupCommandInUse, srcStages, dstStages, 0, 0, nullptr, 0, nullptr, 1, &vkImageMemoryBarrier);
	if (submit == true) finishSetupCommandBuffer(contextIdx);

	//
	_textureObject->accessTypes[baseArrayLayer] = nextAccessTypes;
	_textureObject->svsLayout = nextLayout;
	_textureObject->vkLayout = vkImageMemoryBarrier.newLayout;
}

void VKRenderer::setImageLayout2(int contextIdx, texture_type* textureObject, const array<ThsvsAccessType,2>& accessTypes, const array<ThsvsAccessType,2>& nextAccessTypes, ThsvsImageLayout layout, ThsvsImageLayout nextLayout, bool discardContent, uint32_t baseMipLevel, uint32_t levelCount, uint32_t baseArrayLayer, uint32_t layerCount) {
	auto& currentContext = contexts[contextIdx];

	ThsvsImageBarrier svsImageBarrier = {
		.prevAccessCount = static_cast<uint32_t>(accessTypes[1] != THSVS_ACCESS_NONE?2:1),
		.pPrevAccesses = accessTypes.data(),
		.nextAccessCount = static_cast<uint32_t>(nextAccessTypes[1] != THSVS_ACCESS_NONE?2:1),
		.pNextAccesses = nextAccessTypes.data(),
		.prevLayout = layout,
		.nextLayout = nextLayout,
		.discardContents = discardContent,
		.srcQueueFamilyIndex = 0,
		.dstQueueFamilyIndex = 0,
		.image = textureObject->image,
		.subresourceRange = {
			.aspectMask = textureObject->aspectMask,
			.baseMipLevel = baseMipLevel,
			.levelCount = levelCount,
			.baseArrayLayer = baseArrayLayer,
			.layerCount = layerCount
		}
	};
	VkImageMemoryBarrier vkImageMemoryBarrier;
	VkPipelineStageFlags srcStages;
	VkPipelineStageFlags dstStages;
	thsvsGetVulkanImageMemoryBarrier(
		svsImageBarrier,
		&srcStages,
		&dstStages,
		&vkImageMemoryBarrier
	);

	//
	VkResult err;

	//
	prepareSetupCommandBuffer(contextIdx);
	vkCmdPipelineBarrier(currentContext.setupCommandInUse, srcStages, dstStages, 0, 0, nullptr, 0, nullptr, 1, &vkImageMemoryBarrier);
	finishSetupCommandBuffer(contextIdx);
}

inline uint32_t VKRenderer::getMipLevels(Texture* texture) {
	if (texture->isUseMipMap() == false) return 1;
	if (texture->getAtlasSize() > 1) {
		auto borderSize = 32;
		auto maxLevel = 0;
		while (borderSize > 4) {
			maxLevel++;
			borderSize/= 2;
		}
		return maxLevel;
	} else {
		return static_cast<uint32_t>(std::floor(std::log2(std::max(texture->getTextureWidth(), texture->getTextureHeight())))) + 1;
	}
}

inline void VKRenderer::prepareTextureImage(int contextIdx, struct texture_type* textureObject, VkImageTiling tiling, VkImageUsageFlags usage, VkFlags requiredFlags, Texture* texture, const array<ThsvsAccessType,2>& nextAccesses, ThsvsImageLayout imageLayout, bool disableMipMaps, uint32_t baseLevel, uint32_t levelCount) {
	VkResult err;
	bool pass;

	auto textureWidth = static_cast<uint32_t>(texture->getTextureWidth());
	auto textureHeight = static_cast<uint32_t>(texture->getTextureHeight());

	const VkImageCreateInfo imageCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.imageType = VK_IMAGE_TYPE_2D,
		.format = texture->getDepth() == 32?VK_FORMAT_R8G8B8A8_UNORM:VK_FORMAT_R8G8B8A8_UNORM,
		.extent = {
			.width = textureWidth,
			.height = textureHeight,
			.depth = 1
		},
		.mipLevels = disableMipMaps == false && texture->isUseMipMap() == true?getMipLevels(texture):1,
		.arrayLayers = 1,
		.samples = VK_SAMPLE_COUNT_1_BIT,
		.tiling = tiling,
		.usage = usage,
		.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
	    .queueFamilyIndexCount = 0,
	    .pQueueFamilyIndices = 0,
		.initialLayout = VK_IMAGE_LAYOUT_PREINITIALIZED
	};

	VmaAllocationCreateInfo imageAllocCreateInfo = {};
	imageAllocCreateInfo.usage = VMA_MEMORY_USAGE_UNKNOWN;
	imageAllocCreateInfo.requiredFlags = requiredFlags;

	VmaAllocationInfo allocationInfo = {};
	err = vmaCreateImage(allocator, &imageCreateInfo, &imageAllocCreateInfo, &textureObject->image, &textureObject->allocation, &allocationInfo);
	assert(!err);

	if ((requiredFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) == VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) {
		const VkImageSubresource subres = {
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
			.mipLevel = 0,
			.arrayLayer = 0,
		};
		VkSubresourceLayout layout;
		vkGetImageSubresourceLayout(device, textureObject->image, &subres, &layout);

		void* data;
		err = vmaMapMemory(allocator, textureObject->allocation, &data);
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
		vmaFlushAllocation(allocator, textureObject->allocation, 0, VK_WHOLE_SIZE);
		vmaUnmapMemory(allocator, textureObject->allocation);
	}

	//
	textureObject->accessTypes = { THSVS_ACCESS_HOST_PREINITIALIZED, THSVS_ACCESS_NONE };
	setImageLayout(
		contextIdx,
		textureObject,
		nextAccesses,
		THSVS_IMAGE_LAYOUT_OPTIMAL,
		false,
		baseLevel,
		levelCount,
		true
	);
}

void VKRenderer::initializeSwapChain() {
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");

	VkResult err;
	VkSwapchainKHR oldSwapchain = swapchain;

	// Check the surface capabilities and formats
	VkSurfaceCapabilitiesKHR surfCapabilities;
	err = fpGetPhysicalDeviceSurfaceCapabilitiesKHR(gpu, surface, &surfCapabilities);
	assert(err == VK_SUCCESS);

	uint32_t presentModeCount;
	err = fpGetPhysicalDeviceSurfacePresentModesKHR(gpu, surface, &presentModeCount, nullptr);
	assert(err == VK_SUCCESS);
	vector<VkPresentModeKHR> presentModes(presentModeCount);
	err = fpGetPhysicalDeviceSurfacePresentModesKHR(gpu, surface, &presentModeCount, presentModes.data());
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
		.pNext = nullptr,
		.flags = 0,
		.surface = surface,
		.minImageCount = desiredNumOfSwapchainImages,
		.imageFormat = format,
		.imageColorSpace = colorSpace,
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

	err = fpCreateSwapchainKHR(device, &swapchainCreateInfo, nullptr, &swapchain);
	assert(!err);

	// If we just re-created an existing swapchain, we should destroy the old
	// swapchain at this point.
	// Note: destroying the swapchain also cleans up all its associated
	// presentable images once the platform is done with them.
	if (oldSwapchain != VK_NULL_HANDLE) {
		fpDestroySwapchainKHR(device, oldSwapchain, nullptr);
	}

	err = fpGetSwapchainImagesKHR(device, swapchain, &swapchainImageCount, nullptr);
	assert(err == VK_SUCCESS);

	// TODO: use proper C++ code
	VkImage* swapchainImages = new VkImage[swapchainImageCount];
	assert(swapchainImages != nullptr);
	err = fpGetSwapchainImagesKHR(device, swapchain, &swapchainImageCount, swapchainImages);
	assert(err == VK_SUCCESS);

	//
	swapchainBuffers.resize(swapchainImageCount);
	for (auto i = 0; i < swapchainBuffers.size(); i++) {
		VkImageViewCreateInfo colorAttachmentView = {
			.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
			.pNext = nullptr,
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
		swapchainBuffers[i].image = swapchainImages[i];
		err = vkCreateImageView(device, &colorAttachmentView, nullptr, &swapchainBuffers[i].view);
		assert(err == VK_SUCCESS);
	}

	currentFrameBuffer = 0;
}

const string VKRenderer::getVendor() {
	return StringTools::tokenize(deviceName, " \t\n")[0];
}

const string VKRenderer::getRenderer() {
	return deviceName + " [VK]";
}

const string VKRenderer::getShaderVersion()
{
	return "gl3";
}

void* VKRenderer::getDefaultContext() {
	return &contexts[0];
}

void* VKRenderer::getContext(int contextIdx) {
	return &contexts[contextIdx];
}

int VKRenderer::getContextIndex(void* context) {
	auto& currentContext = *static_cast<context_type*>(context);
	return currentContext.idx;
}

bool VKRenderer::isSupportingMultithreadedRendering() {
	return true;
}

bool VKRenderer::isSupportingMultipleRenderQueues() {
	return false;
}

bool VKRenderer::isSupportingVertexArrays() {
	return false;
}

void VKRenderer::initialize()
{
	//
	glfwGetWindowSize(Application::glfwWindow, (int32_t*)&width, (int32_t*)&height);

	//
	glslang::InitProcess();
	glslang::InitThread();
	ShInitialize();

	VkResult err;
	uint32_t i = 0;
	uint32_t requiredExtensionCount = 0;
	uint32_t instanceExtensionCount = 0;
	uint32_t instanceLayerCount = 0;
	uint32_t validationLayerCount = 0;
	const char** requiredExtensions = nullptr;
	const char** instanceValidationLayers = nullptr;

	uint32_t enabledExtensionCount = 0;
	uint32_t enabledLayerCount = 0;
	const char* extensionNames[64];
	const char* enabledLayers[64];

	char* instanceValidationLayersAlt1[] = {
		"VK_LAYER_KHRONOS_validation"
	};
	char* instanceValidationLayersAlt2[] = {
		"VK_LAYER_LUNARG_standard_validation"
	};

	// Look for validation layers
	if (validate == true) {
		VkBool32 validationFound = 0;
		err = vkEnumerateInstanceLayerProperties(&instanceLayerCount, nullptr);
		assert(!err);

		instanceValidationLayers = (const char**)instanceValidationLayersAlt1;
		if (instanceLayerCount > 0) {
			// TODO: replace with proper C++ code
			VkLayerProperties* instanceLayers = new VkLayerProperties[instanceLayerCount];
			err = vkEnumerateInstanceLayerProperties(&instanceLayerCount, instanceLayers);
			assert(!err);

			validationFound = checkLayers(
				ARRAY_SIZE(instanceValidationLayersAlt1),
				instanceValidationLayers,
				instanceLayerCount,
				instanceLayers
			);
			if (validationFound) {
				enabledLayerCount = ARRAY_SIZE(instanceValidationLayersAlt1);
				enabledLayers[0] = "VK_LAYER_LUNARG_standard_validation";
				validationLayerCount = 1;
			} else {
				// use alternative set of validation layers
				instanceValidationLayers = (const char**) instanceValidationLayersAlt2;
				enabledLayerCount = ARRAY_SIZE(instanceValidationLayersAlt2);
				validationFound = checkLayers(
					ARRAY_SIZE(instanceValidationLayersAlt2),
					instanceValidationLayers,
					instanceLayerCount,
					instanceLayers
				);
				validationLayerCount = ARRAY_SIZE(instanceValidationLayersAlt2);
				for (i = 0; i < validationLayerCount; i++) {
					enabledLayers[i] = instanceValidationLayers[i];
				}
			}
			delete [] instanceLayers;
		}

		if (!validationFound) {
			ERR_EXIT("vkEnumerateInstanceLayerProperties failed to find "
					"required validation layer.\n\n"
					"Please look at the Getting Started guide for additional "
					"information.\n", "vkCreateInstance Failure");
		}
	}

	// Look for instance extensions
	requiredExtensions = glfwGetRequiredInstanceExtensions(&requiredExtensionCount);
	if (!requiredExtensions) {
		ERR_EXIT("glfwGetRequiredInstanceExtensions failed to find the "
			"platform surface extensions.\n\nDo you have a compatible "
			"Vulkan installable client driver (ICD) installed?\nPlease "
			"look at the Getting Started guide for additional "
			"information.\n", "vkCreateInstance Failure"
		);
	}

	for (i = 0; i < requiredExtensionCount; i++) {
		extensionNames[enabledExtensionCount++] = requiredExtensions[i];
		assert(enabledExtensionCount < 64);
	}

	err = vkEnumerateInstanceExtensionProperties(
	nullptr, &instanceExtensionCount, nullptr);
	assert(!err);

	if (instanceExtensionCount > 0) {
		// TODO: replace with proper C++
		VkExtensionProperties* instanceExtensions = new VkExtensionProperties[instanceExtensionCount];
		err = vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtensionCount, instanceExtensions);
		assert(!err);
		for (i = 0; i < instanceExtensionCount; i++) {
			if (!strcmp(VK_EXT_DEBUG_REPORT_EXTENSION_NAME, instanceExtensions[i].extensionName)) {
				if (validate == true) {
					extensionNames[enabledExtensionCount++] = VK_EXT_DEBUG_REPORT_EXTENSION_NAME;
				}
			}
			assert(enabledExtensionCount < 64);
		}
		delete [] instanceExtensions;
	}

	const VkApplicationInfo applicationInfo = {
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pNext = nullptr,
		.pApplicationName = "TDME2 based application",
		.applicationVersion = 0,
		.pEngineName = "TDME2",
		.engineVersion = 0,
		.apiVersion = VK_API_VERSION_1_0,
	};
	VkInstanceCreateInfo instanceCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.pApplicationInfo = &applicationInfo,
		.enabledLayerCount = enabledLayerCount,
		.ppEnabledLayerNames = (const char * const *)instanceValidationLayers,
		.enabledExtensionCount = enabledExtensionCount,
		.ppEnabledExtensionNames = (const char * const *)extensionNames,
	};
	uint32_t gpuCount;

	err = vkCreateInstance(&instanceCreateInfo, nullptr, &inst);
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
	err = vkEnumeratePhysicalDevices(inst, &gpuCount, nullptr);
	assert(!err && gpuCount > 0);

	if (gpuCount > 0) {
		vector<VkPhysicalDevice> physicalDevices(gpuCount);
		err = vkEnumeratePhysicalDevices(inst, &gpuCount, physicalDevices.data());
		assert(!err);
		gpu = physicalDevices[0];
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
	uint32_t deviceExtensionCount = 0;
	VkBool32 swapchainExtFound = 0;
	enabledExtensionCount = 0;

	err = vkEnumerateDeviceExtensionProperties(gpu, nullptr, &deviceExtensionCount, nullptr);
	assert(!err);

	if (deviceExtensionCount > 0) {
		vector<VkExtensionProperties> deviceExtensions(deviceExtensionCount);
		err = vkEnumerateDeviceExtensionProperties(gpu, nullptr, &deviceExtensionCount, deviceExtensions.data());
		assert(!err);
		for (i = 0; i < deviceExtensionCount; i++) {
			if (!strcmp(VK_KHR_SWAPCHAIN_EXTENSION_NAME, deviceExtensions[i].extensionName)) {
				swapchainExtFound = 1;
				extensionNames[enabledExtensionCount++] = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
			}
			assert(enabledExtensionCount < 64);
		}
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

	vkGetPhysicalDeviceProperties(gpu, &gpuProperties);

	//
	deviceName = gpuProperties.deviceName;

	// Query with nullptr data to get count
	vkGetPhysicalDeviceQueueFamilyProperties(gpu, &queueCount, nullptr);

	queueProperties = new VkQueueFamilyProperties[queueCount];
	vkGetPhysicalDeviceQueueFamilyProperties(gpu, &queueCount, queueProperties);
	assert(queueCount >= 1);

	vkGetPhysicalDeviceFeatures(gpu, &gpuFeatures);

	// Create a WSI surface for the window:
	err = glfwCreateWindowSurface(inst, Application::glfwWindow, nullptr, &surface);
	assert(!err);

	// Iterate over each queue to learn whether it supports presenting:
	vector<VkBool32> supportsPresent(queueCount);
	for (i = 0; i < queueCount; i++) {
		fpGetPhysicalDeviceSurfaceSupportKHR(gpu, i, surface, &supportsPresent[i]);
	}

	// Search for a graphics and a present queue in the array of queue
	// families, try to find one that supports both
	graphicsQueueNodeIndex = UINT32_MAX;
	uint32_t presentQueueNodeIndex = UINT32_MAX;
	for (i = 0; i < queueCount; i++) {
		if ((queueProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0) {
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
		for (i = 0; i < queueCount; ++i) {
			if (supportsPresent[i] == VK_TRUE) {
				presentQueueNodeIndex = i;
				break;
			}
		}
	}

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

	// init_device
	array<float, 1> queuePriorities { 0.0f };
	const VkDeviceQueueCreateInfo queueCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.queueFamilyIndex = graphicsQueueNodeIndex,
		.queueCount = queuePriorities.size(),
		.pQueuePriorities = queuePriorities.data()
	};

	VkPhysicalDeviceFeatures features;
	memset(&features, 0, sizeof(features));
	if (gpuFeatures.shaderClipDistance) features.shaderClipDistance = VK_TRUE;
	if (gpuFeatures.wideLines) features.wideLines = VK_TRUE; // TODO: a.drewke, store enabled GPU features and check them on rendering if available

	VkDeviceCreateInfo deviceCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.queueCreateInfoCount = 1,
		.pQueueCreateInfos = &queueCreateInfo,
		.enabledLayerCount = 0,
		.ppEnabledLayerNames = nullptr,
		.enabledExtensionCount = enabledExtensionCount,
		.ppEnabledExtensionNames = (const char * const *) extensionNames,
		.pEnabledFeatures = &features
	};

	err = vkCreateDevice(gpu, &deviceCreateInfo, nullptr, &device);
	assert(!err);

	GET_DEVICE_PROC_ADDR(device, CreateSwapchainKHR);
	GET_DEVICE_PROC_ADDR(device, DestroySwapchainKHR);
	GET_DEVICE_PROC_ADDR(device, GetSwapchainImagesKHR);
	GET_DEVICE_PROC_ADDR(device, AcquireNextImageKHR);
	GET_DEVICE_PROC_ADDR(device, QueuePresentKHR);

	vkGetDeviceQueue(device, graphicsQueueNodeIndex, 0, &queue);

	// Get the list of VkFormat's that are supported:
	uint32_t surfaceFormatCount;
	err = fpGetPhysicalDeviceSurfaceFormatsKHR(gpu, surface, &surfaceFormatCount, nullptr);
	assert(!err);
	vector<VkSurfaceFormatKHR> surfaceFormats(surfaceFormatCount);
	err = fpGetPhysicalDeviceSurfaceFormatsKHR(gpu, surface, &surfaceFormatCount, surfaceFormats.data());
	assert(!err);

	// If the format list includes just one entry of VK_FORMAT_UNDEFINED,
	// the surface has no preferred format.  Otherwise, at least one
	// supported format will be returned.
	// We for now only support VK_FORMAT_R8G8B8A8_UNORM
	if (surfaceFormatCount == 1 && surfaceFormats[0].format == VK_FORMAT_UNDEFINED) {
		format = VK_FORMAT_B8G8R8A8_UNORM;
		colorSpace = surfaceFormats[0].colorSpace;
	} else {
		for (auto i = 0; i < surfaceFormatCount; i++) {
			if (surfaceFormats[i].format == VK_FORMAT_B8G8R8A8_UNORM) {
				format = VK_FORMAT_B8G8R8A8_UNORM;
				colorSpace = surfaceFormats[i].colorSpace;
				break;
			}
		}
	}
	if (format == VK_FORMAT_UNDEFINED) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): No format given");
		ERR_EXIT(
			"Could not use VK_FORMAT_R8G8B8A8_UNORM as format\n",
			"Format Failure"
		);
	}

	// Get Memory information and properties
	vkGetPhysicalDeviceMemoryProperties(gpu, &memoryProperties);

	// initialize allocator
	VmaAllocatorCreateInfo allocatorCreateInfo = {};
	allocatorCreateInfo.physicalDevice = gpu;
	allocatorCreateInfo.device = device;
	allocatorCreateInfo.instance = inst;
	allocatorCreateInfo.vulkanApiVersion = VK_API_VERSION_1_0;

    //
	vmaCreateAllocator(&allocatorCreateInfo, &allocator);

	// swap chain
	initializeSwapChain();

	// create descriptor pool 1
	{
		array<VkDescriptorPoolSize, 2> desc1TypesCount = {{
			{
				.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
				// 100 shaders * 3 command buffers * 2 shader stages * 1 uniform buffers
				.descriptorCount = static_cast<uint32_t>(DESC_MAX_UNCACHED * Engine::getThreadCount() * SHADERS_MAX * DRAW_COMMANDBUFFER_MAX * 2 * 1)
			},
			{
				.type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
				// 1 shader * 3 command buffers * 1 shader stage * 10 storage buffers
				.descriptorCount = static_cast<uint32_t>(DESC_MAX_UNCACHED * Engine::getThreadCount() * SHADERS_COMPUTE_MAX * DRAW_COMMANDBUFFER_MAX * 1 * 10)
			}
		}};
		const VkDescriptorPoolCreateInfo descriptorPoolCreateInfo = {
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			// 100 shaders * 2 stages
			.maxSets = static_cast<uint32_t>(DESC_MAX_UNCACHED * Engine::getThreadCount() * 100 * 2),
			.poolSizeCount = desc1TypesCount.size(),
			.pPoolSizes = desc1TypesCount.data(),
		};
		//
		err = vkCreateDescriptorPool(device, &descriptorPoolCreateInfo, nullptr, &descriptorPool1);
		assert(!err);
	}

	// create descriptor pool 2
	{
		const VkDescriptorPoolSize desc2TypesCount = {
			.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
			// 100 shaders * 2 stages * 8 image sampler
			.descriptorCount = static_cast<uint32_t>((DESC_MAX_CACHED + DESC_MAX_UNCACHED) * Engine::getThreadCount() * SHADERS_MAX * 2 * 8)
		};
		const VkDescriptorPoolCreateInfo descriptorPoolCreateInfo = {
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			// 100 shaders * 2 stages
			.maxSets = static_cast<uint32_t>((DESC_MAX_CACHED + DESC_MAX_UNCACHED) * Engine::getThreadCount() * SHADERS_MAX * 2),
			.poolSizeCount = 1,
			.pPoolSizes = &desc2TypesCount,
		};
		//
		err = vkCreateDescriptorPool(device, &descriptorPoolCreateInfo, nullptr, &descriptorPool2);
		assert(!err);
	}

	//
	contexts.resize(Engine::getThreadCount());
	// create set up command buffers
	for (auto contextIdx = 0; contextIdx < Engine::getThreadCount(); contextIdx++) {
		auto& context = contexts[contextIdx];
		//
		context.idx = contextIdx;
		context.setupCommandInUse = VK_NULL_HANDLE;
		context.currentCommandBuffer = 0;
		context.pipeline = VK_NULL_HANDLE;
		context.renderPassStarted = false;
		context.bufferVector.resize(BUFFERS_MAX);
		context.textureVector.resize(TEXTURES_MAX);

		//
		for (auto i = 0; i < DRAW_COMMANDBUFFER_MAX; i++) {
			context.commandBuffers[i].drawFence = VK_NULL_HANDLE;
			context.commandBuffers[i].drawCmdStarted = false;
		}

		//
		{
			// command pool
			const VkCommandPoolCreateInfo commandPoolCreateInfo = {
				.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
				.pNext = nullptr,
				.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
				.queueFamilyIndex = graphicsQueueNodeIndex
			};
			err = vkCreateCommandPool(device, &commandPoolCreateInfo, nullptr, &context.setupCommandPool);
			assert(!err);

			// command buffer
			const VkCommandBufferAllocateInfo commandBufferAllocationInfo = {
				.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
				.pNext = nullptr,
				.commandPool = context.setupCommandPool,
				.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
				.commandBufferCount = 1
			};
			err = vkAllocateCommandBuffers(device, &commandBufferAllocationInfo, &context.setupCommand);
			assert(!err);
		}

		{
			// draw command pool
			const VkCommandPoolCreateInfo commandPoolCreateInfo = {
				.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
				.pNext = nullptr,
				.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
				.queueFamilyIndex = graphicsQueueNodeIndex
			};
			err = vkCreateCommandPool(device, &commandPoolCreateInfo, nullptr, &context.drawCommandPool);
			assert(!err);

			// command buffer
			const VkCommandBufferAllocateInfo commandBufferAllocationInfo = {
				.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
				.pNext = nullptr,
				.commandPool = context.drawCommandPool,
				.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
				.commandBufferCount = 1
			};
			for (auto i = 0; i < DRAW_COMMANDBUFFER_MAX; i++) {
				err = vkAllocateCommandBuffers(device, &commandBufferAllocationInfo, &context.commandBuffers[i].drawCommand);
				assert(!err);
			}
		}

		{
			VkFenceCreateInfo fenceCreateInfo = {
				.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0
			};
			vkCreateFence(device, &fenceCreateInfo, nullptr, &context.setupFence);
		}

		// set up lights
		for (auto i = 0; i < context.lights.size(); i++) {
			context.lights[i].spotCosCutoff = static_cast<float>(Math::cos(Math::PI / 180.0f * 180.0f));
		}
		context.textureMatrix.identity();

		//
		recreateContextFences(context.idx);
	}

	// memory barrier fence
	{
		VkFenceCreateInfo fenceCreateInfo = {
			.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0
		};
		vkCreateFence(device, &fenceCreateInfo, nullptr, &memoryBarrierFence);
	}

	//
	initializeRenderPass();
	initializeFrameBuffers();

	//
	emptyVertexBufferId = createBufferObjects(1, true, true)[0];
	emptyVertexBuffer = getBufferObjectInternal(-1, emptyVertexBufferId);
	array<float, 16> bogusVertexBuffer = {{
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
	}};
	uploadBufferObjectInternal(0, emptyVertexBuffer, bogusVertexBuffer.size() * sizeof(float), (uint8_t*)bogusVertexBuffer.data(), (VkBufferUsageFlagBits)(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT));

	// fall back texture white
	whiteTextureSampler2dDefaultId = Engine::getInstance()->getTextureManager()->addTexture(TextureReader::read("resources/engine/textures", "transparent_pixel.png"), getDefaultContext());
	whiteTextureSampler2dDefault = textures.find(whiteTextureSampler2dDefaultId)->second;

	// fallback cube map texture white
	whiteTextureSamplerCubeDefaultId = Engine::getInstance()->getTextureManager()->addCubeMapTexture(
		"cubemap-default-white",
		TextureReader::read("resources/engine/textures", "transparent_pixel.png"),
		TextureReader::read("resources/engine/textures", "transparent_pixel.png"),
		TextureReader::read("resources/engine/textures", "transparent_pixel.png"),
		TextureReader::read("resources/engine/textures", "transparent_pixel.png"),
		TextureReader::read("resources/engine/textures", "transparent_pixel.png"),
		TextureReader::read("resources/engine/textures", "transparent_pixel.png"),
		getDefaultContext()
	);
	whiteTextureSamplerCubeDefault = textures.find(whiteTextureSamplerCubeDefaultId)->second;

	//
	for (auto& context: contexts) unbindBufferObjects(&context);
}

void VKRenderer::initializeRenderPass() {
	VkResult err;

	//
	if (renderPass != VK_NULL_HANDLE) vkDestroyRenderPass(device, renderPass, nullptr);

	// depth buffer
	if (depthBufferDefault != ID_NONE) disposeTexture(depthBufferDefault);
	depthBufferDefault = createDepthBufferTexture(width, height, ID_NONE, ID_NONE);
	auto depthBufferTexture = textures.find(depthBufferDefault)->second;

	//
	setImageLayout(
		0,
		depthBufferTexture,
		{ THSVS_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ, THSVS_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE },
		THSVS_IMAGE_LAYOUT_OPTIMAL,
		false
	);

	// render pass
	array<VkAttachmentDescription, 2> attachments = {{
		{
			.flags = 0,
			.format = format,
			.samples = VK_SAMPLE_COUNT_1_BIT,
			.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
			.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
			.initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
			.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
		},
		{
			.flags = 0,
			.format = VK_FORMAT_D32_SFLOAT,
			.samples = VK_SAMPLE_COUNT_1_BIT,
			.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
			.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			.stencilStoreOp = VK_ATTACHMENT_STORE_OP_STORE,
			.initialLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
			.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
		}
	}};
	const VkAttachmentReference colorReference = {
		.attachment = 0,
		.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
	};
	const VkAttachmentReference depthReference = {
		.attachment = 1,
		.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
	};
	const VkSubpassDescription subPass = {
		.flags = 0,
		.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
		.inputAttachmentCount = 0,
		.pInputAttachments = nullptr,
		.colorAttachmentCount = 1,
		.pColorAttachments = &colorReference,
		.pResolveAttachments = nullptr,
		.pDepthStencilAttachment = &depthReference,
		.preserveAttachmentCount = 0,
		.pPreserveAttachments = nullptr
	};
	const VkRenderPassCreateInfo rp_info = {
		.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.attachmentCount = 2,
		.pAttachments = attachments.data(),
		.subpassCount = 1,
		.pSubpasses = &subPass,
		.dependencyCount = 0,
		.pDependencies = nullptr
	};
	err = vkCreateRenderPass(device, &rp_info, nullptr, &renderPass);
	assert(!err);
}

inline void VKRenderer::startRenderPass(int contextIdx) {
	auto& currentContext = contexts[contextIdx];

	if (currentContext.renderPassStarted == true) return;
	currentContext.renderPassStarted = true;

	auto usedFrameBuffer = windowFramebuffers[currentFrameBuffer];
	auto vkRenderPass = renderPass;
	if (boundFrameBuffer != ID_NONE) {
		auto frameBuffer = boundFrameBuffer < 0 || boundFrameBuffer >= framebuffers.size()?nullptr:framebuffers[boundFrameBuffer];
		if (frameBuffer == nullptr) {
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): framebuffer not found: " + to_string(boundFrameBuffer));
		} else {
			usedFrameBuffer = frameBuffer->frameBuffer;
			vkRenderPass = frameBuffer->renderPass;
		}
	}

	const VkRenderPassBeginInfo renderPassBegin = {
		.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
		.pNext = nullptr,
		.renderPass = vkRenderPass,
		.framebuffer = usedFrameBuffer,
		.renderArea = scissor,
		.clearValueCount = 0,
		.pClearValues = nullptr
	};
	vkCmdBeginRenderPass(currentContext.commandBuffers[currentContext.currentCommandBuffer].drawCommand, &renderPassBegin, VK_SUBPASS_CONTENTS_INLINE);

	//
	AtomicOperations::increment(statistics.renderPasses);
}

inline void VKRenderer::endRenderPass(int contextIdx) {
	auto& currentContext = contexts[contextIdx];
	if (currentContext.renderPassStarted == false) return;
	currentContext.renderPassStarted = false;
	vkCmdEndRenderPass(currentContext.commandBuffers[currentContext.currentCommandBuffer].drawCommand);
}

void VKRenderer::initializeFrameBuffers() {
	array<VkImageView, 2> attachments;
	auto depthBufferIt = textures.find(depthBufferDefault);
	assert(depthBufferIt != textures.end());
	attachments[1] = depthBufferIt->second->view;

	const VkFramebufferCreateInfo frameBufferCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.renderPass = renderPass,
		.attachmentCount = 2,
		.pAttachments = attachments.data(),
		.width = width,
		.height = height,
		.layers = 1
	};

	windowFramebuffers.resize(swapchainImageCount);

	for (auto i = 0; i < windowFramebuffers.size(); i++) {
		attachments[0] = swapchainBuffers[i].view;
		auto err = vkCreateFramebuffer(device, &frameBufferCreateInfo, nullptr, &windowFramebuffers[i]);
		assert(!err);
	}
}

void VKRenderer::reshape() {
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");

	// new dimensions
	glfwGetWindowSize(Application::glfwWindow, (int32_t*)&width, (int32_t*)&height);

	//
	Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + to_string(width) + " x " + to_string(height));

	// dispose old frame buffers
	for (auto i = 0; i < windowFramebuffers.size(); i++) vkDestroyFramebuffer(device, windowFramebuffers[i], nullptr);
	windowFramebuffers.clear();

	// reinit swapchain, renderpass and framebuffers
	initializeSwapChain();
	initializeRenderPass();
	initializeFrameBuffers();
	currentFrameBuffer = 0;

	//
	Engine::getInstance()->reshape(width, height);
}

void VKRenderer::initializeFrame()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");

	// work around for AMD drivers not telling if window needs to be reshaped
	{
		int32_t currentWidth;
		int32_t currentHeight;
		glfwGetWindowSize(Application::glfwWindow, &currentWidth, &currentHeight);
		auto needsReshape = currentWidth > 0 && currentHeight > 0 && (currentWidth != width || currentHeight != height);
		if (needsReshape == true) reshape();
	}

	//
	Renderer::initializeFrame();

	//
	VkResult err;
	VkSemaphoreCreateInfo semaphoreCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0
	};

	err = vkCreateSemaphore(device, &semaphoreCreateInfo, nullptr, &imageAcquiredSemaphore);
	assert(!err);

	err = vkCreateSemaphore(device, &semaphoreCreateInfo, nullptr, &drawCompleteSemaphore);
	assert(!err);

	// get the index of the next available swapchain image:
	err = fpAcquireNextImageKHR(device, swapchain, UINT64_MAX, imageAcquiredSemaphore, (VkFence)0, &currentFrameBuffer);

	//
	if (err == VK_ERROR_OUT_OF_DATE_KHR) {
		// TODO: a.drewke
		//
		finishSetupCommandBuffers();
		for (auto i = 0; i < Engine::getThreadCount(); i++) endRenderPass(i);
		vkDestroySemaphore(device, imageAcquiredSemaphore, nullptr);
		vkDestroySemaphore(device, drawCompleteSemaphore, nullptr);

		//
		reshape();

		// recreate semaphores
		err = vkCreateSemaphore(device, &semaphoreCreateInfo, nullptr, &imageAcquiredSemaphore);
		assert(!err);

		err = vkCreateSemaphore(device, &semaphoreCreateInfo, nullptr, &drawCompleteSemaphore);
		assert(!err);
	} else
	if (err == VK_SUBOPTIMAL_KHR) {
		// demo->swapchain is not as optimal as it could be, but the platform's
		// presentation engine will still present the image correctly.
	} else {
		assert(!err);
	}

	//
	for (auto i = 0; i < contexts.size(); i++) {
		contexts[i].commandCount = 0;
	}
}

void VKRenderer::removeTextureFromDescriptorCaches(int textureId) {
	// delete desc2 bound texture caches from programs with removed texture
	for (auto& context: contexts) {
		context.textureVector[textureId] = nullptr;
		for (auto program: programVector) {
			if (program == nullptr || program->contexts[context.idx].descriptorSets2CacheTextureIds.empty() == true) continue;
			auto& programContext = program->contexts[context.idx];
			auto& descriptorSets2CacheTextureIds = programContext.descriptorSets2CacheTextureIds;
			auto descriptorSets2CacheTextureIdsIt = descriptorSets2CacheTextureIds.find(textureId);
			if (descriptorSets2CacheTextureIdsIt != descriptorSets2CacheTextureIds.end()) {
				auto& descriptorSets2Cache = programContext.descriptorSets2Cache;
				for (auto& descriptorSets2CacheHash: descriptorSets2CacheTextureIdsIt->second) {
					auto descriptorSets2CacheHashIt = descriptorSets2Cache.find(descriptorSets2CacheHash);
					if (descriptorSets2CacheHashIt != descriptorSets2Cache.end()) {
						auto desc_sets2_idx = descriptorSets2CacheHashIt->second;
						programContext.freeDescriptorSets2Ids.push_back(desc_sets2_idx);
						descriptorSets2Cache.erase(descriptorSets2CacheHashIt);
					}
				}
				descriptorSets2CacheTextureIds.erase(descriptorSets2CacheTextureIdsIt);
			}
		}
	}
}

void VKRenderer::finishFrame()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");

	//
	finishRendering();

	// flush command buffers
	for (auto& context: contexts) {
		unsetPipeline(context.idx);
		context.program = nullptr;
		context.programId = 0;
		context.uniformBuffers.fill(nullptr);
		for (auto& uniformBufferData: context.uniformBufferData) uniformBufferData.resize(0);

	}

	array<ThsvsAccessType, 2> nextAccessTypes { THSVS_ACCESS_PRESENT, THSVS_ACCESS_NONE };
	ThsvsImageLayout nextLayout { THSVS_IMAGE_LAYOUT_OPTIMAL };

	// check if we need a change at all
	if (swapchainBuffers[currentFrameBuffer].accessTypes != nextAccessTypes || swapchainBuffers[currentFrameBuffer].svsLayout != nextLayout) {
		ThsvsImageBarrier svsImageBarrier = {
			.prevAccessCount = static_cast<uint32_t>(swapchainBuffers[currentFrameBuffer].accessTypes[1] != THSVS_ACCESS_NONE?2:1),
			.pPrevAccesses = swapchainBuffers[currentFrameBuffer].accessTypes.data(),
			.nextAccessCount = static_cast<uint32_t>(nextAccessTypes[1] != THSVS_ACCESS_NONE?2:1),
			.pNextAccesses = nextAccessTypes.data(),
			.prevLayout = swapchainBuffers[currentFrameBuffer].svsLayout,
			.nextLayout = nextLayout,
			.discardContents = false,
			.srcQueueFamilyIndex = 0,
			.dstQueueFamilyIndex = 0,
			.image = swapchainBuffers[currentFrameBuffer].image,
			.subresourceRange = {
				.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
				.baseMipLevel = 0,
				.levelCount = 1,
				.baseArrayLayer = 0,
				.layerCount = 1
			}
		};
		VkImageMemoryBarrier vkImageMemoryBarrier;
		VkPipelineStageFlags srcStages;
		VkPipelineStageFlags dstStages;
		thsvsGetVulkanImageMemoryBarrier(
			svsImageBarrier,
			&srcStages,
			&dstStages,
			&vkImageMemoryBarrier
		);

		//
		VkResult err;

		//
		prepareSetupCommandBuffer(0);
		vkCmdPipelineBarrier(contexts[0].setupCommandInUse, srcStages, dstStages, 0, 0, nullptr, 0, nullptr, 1, &vkImageMemoryBarrier);
		finishSetupCommandBuffer(0);

		//
		swapchainBuffers[currentFrameBuffer].accessTypes = nextAccessTypes;
		swapchainBuffers[currentFrameBuffer].svsLayout = nextLayout;
	}

	//
	VkPresentInfoKHR present = {
		.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
		.pNext = nullptr,
		.waitSemaphoreCount = 0,
		.pWaitSemaphores = nullptr,
		.swapchainCount = 1,
		.pSwapchains = &swapchain,
		.pImageIndices = &currentFrameBuffer
	};

	VkResult err;
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

	//
	vkDestroySemaphore(device, imageAcquiredSemaphore, nullptr);
	vkDestroySemaphore(device, drawCompleteSemaphore, nullptr);

	// dispose renderer mapped resources
	if (disposeTextures.empty() == false ||
		disposeBuffers.empty() == false ||
		deleteBuffers.empty() == false ||
		deleteImages.empty() == false) {
		deleteMutex.lock();
		disposeMutex.lock();
		// disposing textures
		texturesRWlock.writeLock();
		for (auto textureId: disposeTextures) {
			auto textureObjectIt = textures.find(textureId);
			if (textureObjectIt == textures.end()) {
				Console::println("VKRenderer::" + string(__FUNCTION__) + "(): disposing texture: texture not found: " + to_string(textureId));
				continue;
			}
			auto texture = textureObjectIt->second;
			// mark for deletion
			deleteImages.push_back(
				{
					.image = texture->image,
					.allocation = texture->allocation,
					.imageView = texture->view,
					.sampler = texture->sampler
				}
			);
			if (texture->cubemapColorBuffer != nullptr) {
				deleteImages.push_back(
					{
						.image = texture->cubemapColorBuffer->image,
						.allocation = texture->cubemapColorBuffer->allocation,
						.imageView = texture->cubemapColorBuffer->view,
						.sampler = texture->cubemapColorBuffer->sampler
					}
				);
			}
			if (texture->cubemapDepthBuffer != nullptr) {
				deleteImages.push_back(
					{
						.image = texture->cubemapDepthBuffer->image,
						.allocation = texture->cubemapDepthBuffer->allocation,
						.imageView = texture->cubemapDepthBuffer->view,
						.sampler = texture->cubemapDepthBuffer->sampler
					}
				);
			}
			//
			textures.erase(textureObjectIt);
			delete texture;
			removeTextureFromDescriptorCaches(textureId);
			freeTextureIds.push_back(textureId);
		}
		texturesRWlock.unlock();
		disposeTextures.clear();
		// disposing buffer objects
		buffersRWlock.writeLock();
		for (auto bufferObjectId: disposeBuffers) {
			auto bufferIt = buffers.find(bufferObjectId);
			if (bufferIt == buffers.end()) {
				Console::println("VKRenderer::" + string(__FUNCTION__) + "(): disposing buffer object: buffer with id " + to_string(bufferObjectId) + " does not exist");
				continue;
			}
			auto buffer = bufferIt->second;
			for (auto& reusableBufferIt: buffer->buffers) {
				auto& reusableBuffer = reusableBufferIt;
				if (reusableBuffer.size == 0) continue;
				// mark staging buffer for deletion when finishing frame
				deleteBuffers.push_back(
					{
						.buffer = reusableBuffer.buf,
						.allocation = reusableBuffer.allocation
					}
				);
			}
			buffers.erase(bufferIt);
			delete buffer;
			for (auto& context: contexts) context.bufferVector[bufferObjectId] = nullptr;
			freeBufferIds.push_back(bufferObjectId);
		}
		buffersRWlock.unlock();
		disposeBuffers.clear();
		disposeMutex.unlock();

		// remove marked vulkan resources
		//	buffers
		for (auto& deleteBuffer: deleteBuffers) {
			vmaUnmapMemory(allocator, deleteBuffer.allocation);
			vmaDestroyBuffer(allocator, deleteBuffer.buffer, deleteBuffer.allocation);
		}
		AtomicOperations::increment(statistics.disposedBuffers, deleteBuffers.size());
		deleteBuffers.clear();
		//	textures
		for (auto& deleteImage: deleteImages) {
			if (deleteImage.imageView != VK_NULL_HANDLE) vkDestroyImageView(device, deleteImage.imageView, nullptr);
			if (deleteImage.sampler != VK_NULL_HANDLE) vkDestroySampler(device, deleteImage.sampler, nullptr);
			if (deleteImage.image != VK_NULL_HANDLE) vmaDestroyImage(allocator, deleteImage.image, deleteImage.allocation);
		}
		AtomicOperations::increment(statistics.disposedTextures, deleteImages.size());
		deleteImages.clear();

		//
		deleteMutex.unlock();
	}

	// unbind bound resources
	uint32_t bufferSize = 0;
	for (auto& context: contexts) {
		context.boundIndicesBuffer = VK_NULL_HANDLE;
		context.boundBuffers.fill(getBufferObjectInternal(emptyVertexBuffer, bufferSize));
		context.boundBufferSizes.fill(bufferSize);
		context.boundTextures.fill(context_type::bound_texture());
	}

	//
	frame++;
}

bool VKRenderer::isBufferObjectsAvailable()
{
	return true;
}

bool VKRenderer::isDepthTextureAvailable()
{
	return true;
}

bool VKRenderer::isUsingProgramAttributeLocation()
{
	return false;
}

bool VKRenderer::isSupportingIntegerProgramAttributes() {
	return true;
}


bool VKRenderer::isSpecularMappingAvailable()
{
	return true;
}

bool VKRenderer::isNormalMappingAvailable()
{
	return true;
}

bool VKRenderer::isInstancedRenderingAvailable() {
	return true;
}

bool VKRenderer::isPBRAvailable()
{
	return true;
}

bool VKRenderer::isComputeShaderAvailable() {
	return true;
}

bool VKRenderer::isGLCLAvailable() {
	return false;
}

bool VKRenderer::isUsingShortIndices() {
	return false;
}

bool VKRenderer::isDeferredShadingAvailable() {
	return true;
}

int32_t VKRenderer::getTextureUnits()
{
	return -1;
}


int32_t VKRenderer::loadShader(int32_t type, const string& pathName, const string& fileName, const string& definitions, const string& functions)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): INIT: " + pathName + "/" + fileName + ": " + definitions);

	auto shaderPtr = new shader_type();
	shaders[shaderIdx] = shaderPtr;
	auto& shader = *shaderPtr;
	shader.id = shaderIdx++;

	//
	VKGL3CoreShaderProgram::loadShader(shader, type, pathName, fileName, definitions, functions);

    //
	return shader.id;
}

inline void VKRenderer::unsetPipeline(int contextIdx) {
	auto& currentContext = contexts[contextIdx];

	//
	currentContext.pipelineId = ID_NONE;
	currentContext.pipeline = VK_NULL_HANDLE;
}

inline void VKRenderer::createRasterizationStateCreateInfo(int contextIdx, VkPipelineRasterizationStateCreateInfo& rasterizationStateCreateInfo) {
	memset(&rasterizationStateCreateInfo, 0, sizeof(rasterizationStateCreateInfo));
	rasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizationStateCreateInfo.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizationStateCreateInfo.cullMode = contexts[contextIdx].cullingEnabled == true?cullMode:VK_CULL_MODE_NONE;
	rasterizationStateCreateInfo.frontFace = (VkFrontFace)(contexts[contextIdx].frontFace - 1);
	rasterizationStateCreateInfo.depthClampEnable = VK_FALSE;
	rasterizationStateCreateInfo.rasterizerDiscardEnable = VK_FALSE;
	rasterizationStateCreateInfo.depthBiasEnable = VK_FALSE;
	rasterizationStateCreateInfo.lineWidth = 1.0f;
}

inline void VKRenderer::createColorBlendAttachmentState(VkPipelineColorBlendAttachmentState& blendAttachmentState) {
	memset(&blendAttachmentState, 0, sizeof(blendAttachmentState));
	blendAttachmentState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	blendAttachmentState.blendEnable = blendingMode != BLENDING_NONE?VK_TRUE:VK_FALSE;
	blendAttachmentState.srcColorBlendFactor = blendingMode == BLENDING_NORMAL?VK_BLEND_FACTOR_SRC_ALPHA:VK_BLEND_FACTOR_ONE;
	blendAttachmentState.dstColorBlendFactor = blendingMode == BLENDING_NORMAL?VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA:VK_BLEND_FACTOR_ONE;
	blendAttachmentState.colorBlendOp = VK_BLEND_OP_ADD;
	blendAttachmentState.srcAlphaBlendFactor = blendingMode == BLENDING_NORMAL?VK_BLEND_FACTOR_ONE:VK_BLEND_FACTOR_ONE;
	blendAttachmentState.dstAlphaBlendFactor = blendingMode == BLENDING_NORMAL?VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA:VK_BLEND_FACTOR_ONE;
	blendAttachmentState.alphaBlendOp = VK_BLEND_OP_ADD;
}

inline void VKRenderer::createDepthStencilStateCreateInfo(VkPipelineDepthStencilStateCreateInfo& depthStencilStateCreateInfo) {
	memset(&depthStencilStateCreateInfo, 0, sizeof(depthStencilStateCreateInfo));
	depthStencilStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	depthStencilStateCreateInfo.depthTestEnable = depthBufferTesting == true?VK_TRUE:VK_FALSE;
	depthStencilStateCreateInfo.depthWriteEnable = depthBufferWriting == true?VK_TRUE:VK_FALSE;
	depthStencilStateCreateInfo.depthCompareOp = (VkCompareOp)depthFunction;
	depthStencilStateCreateInfo.back.failOp = VK_STENCIL_OP_KEEP;
	depthStencilStateCreateInfo.back.passOp = VK_STENCIL_OP_KEEP;
	depthStencilStateCreateInfo.back.compareOp = VK_COMPARE_OP_ALWAYS;
	depthStencilStateCreateInfo.stencilTestEnable = VK_FALSE;
	depthStencilStateCreateInfo.front = depthStencilStateCreateInfo.back;
	depthStencilStateCreateInfo.depthBoundsTestEnable = VK_FALSE;
	depthStencilStateCreateInfo.minDepthBounds = 0.0f;
	depthStencilStateCreateInfo.maxDepthBounds = 1.0f;
}

inline uint32_t VKRenderer::createPipelineId(program_type* program, int contextIdx) {
	return
		(program->id & 0xff) +
		((boundFrameBuffer & 0xff) << 8) +
		((contexts[contextIdx].frontFaceIndex & 0x1) << 16) +
		((cullMode & 0x3) << 17) +
		((blendingMode & 0x3) << 19) +
		((depthBufferTesting & 0x1) << 21) +
		((depthBufferWriting & 0x1) << 22) +
		((depthFunction & 0x7) << 23);
}

void VKRenderer::createRenderProgram(program_type* program) {
	VkResult err;
	VkDescriptorSetLayoutBinding layoutBindings1[program->layoutBindings];
	VkDescriptorSetLayoutBinding layoutBindings2[program->layoutBindings];
	memset(layoutBindings1, 0, sizeof(layoutBindings1));
	memset(layoutBindings2, 0, sizeof(layoutBindings2));

	// ubos, samplers
	auto samplerIdx = 0;
	auto uboIdx = 0;
	for (auto shader: program->shaders) {
		if (shader->uboBindingIdx != -1) {
			layoutBindings1[uboIdx++] = {
				.binding = static_cast<uint32_t>(shader->uboBindingIdx),
				.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
				.descriptorCount = 1,
				.stageFlags = shader->type,
				.pImmutableSamplers = nullptr
			};
		}
		// sampler2D + samplerCube
		for (auto uniform: shader->samplerUniformList) {
			layoutBindings2[samplerIdx++] = {
				.binding = static_cast<uint32_t>(uniform->position),
				.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
				.descriptorCount = 1,
				.stageFlags = shader->type,
				.pImmutableSamplers = nullptr
			};
		}
	}

	{
		const VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo = {
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.bindingCount = static_cast<uint32_t>(uboIdx),
			.pBindings = layoutBindings1,
		};
		err = vkCreateDescriptorSetLayout(device, &descriptorSetLayoutCreateInfo, nullptr, &program->descriptorSetLayout1);
		assert(!err);
	}
	{
		const VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo = {
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.bindingCount = static_cast<uint32_t>(samplerIdx),
			.pBindings = layoutBindings2,
		};
		err = vkCreateDescriptorSetLayout(device, &descriptorSetLayoutCreateInfo, nullptr, &program->descriptorSetLayout2);
		assert(!err);
	}

	//
	array<VkDescriptorSetLayout, 2> descriptorSetLayouts { program->descriptorSetLayout1, program->descriptorSetLayout2 };
	const VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.setLayoutCount = descriptorSetLayouts.size(),
		.pSetLayouts = descriptorSetLayouts.data()
	};

	//
	for (auto i = 0; i < DRAW_COMMANDBUFFER_MAX; i++) {
		array<VkDescriptorSetLayout, DESC_MAX_UNCACHED> descriptorSetLayouts1;
		descriptorSetLayouts1.fill(program->descriptorSetLayout1);
		//
		VkDescriptorSetAllocateInfo descriptorSetAllocateInfo = {
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
			.pNext = nullptr,
			.descriptorPool = descriptorPool1,
			.descriptorSetCount = DESC_MAX_UNCACHED,
			.pSetLayouts = descriptorSetLayouts1.data()
		};
		for (auto& context: contexts) {
			err = vkAllocateDescriptorSets(device, &descriptorSetAllocateInfo, program->contexts[context.idx].commandBuffers[i].descriptorSets1.data());
			assert(!err);
		}
	}

	//
	if (program->type == PROGRAM_OBJECTS) {
		array<VkDescriptorSetLayout, DESC_MAX_CACHED> descriptorSetLayouts2;
		descriptorSetLayouts2.fill(program->descriptorSetLayout2);
		//
		VkDescriptorSetAllocateInfo descriptorSetAllocateInfo = {
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
			.pNext = nullptr,
			.descriptorPool = descriptorPool2,
			.descriptorSetCount = DESC_MAX_CACHED,
			.pSetLayouts = descriptorSetLayouts2.data()
		};
		for (auto& context: contexts) {
			err = vkAllocateDescriptorSets(device, &descriptorSetAllocateInfo, program->contexts[context.idx].descriptorSets2.data());
			assert(!err);
		}
	}

	//
	for (auto i = 0; i < DRAW_COMMANDBUFFER_MAX; i++) {
		array<VkDescriptorSetLayout, DESC_MAX_UNCACHED> descriptorSetLayouts2;
		descriptorSetLayouts2.fill(program->descriptorSetLayout2);
		//
		VkDescriptorSetAllocateInfo descriptorSetAllocateInfo = {
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
			.pNext = nullptr,
			.descriptorPool = descriptorPool2,
			.descriptorSetCount = DESC_MAX_UNCACHED,
			.pSetLayouts = descriptorSetLayouts2.data()
		};
		for (auto& context: contexts) {
			err = vkAllocateDescriptorSets(device, &descriptorSetAllocateInfo, program->contexts[context.idx].commandBuffers[i].descriptorSets2Uncached.data());
			assert(!err);
		}
	}

	//
	err = vkCreatePipelineLayout(device, &pipelineLayoutCreateInfo, nullptr, &program->pipelineLayout);
	assert(!err);
}

VKRenderer::pipeline_type* VKRenderer::createObjectsRenderingPipeline(int contextIdx, program_type* program) {
	auto& currentContext = contexts[contextIdx];
	auto pipelinesIt = program->pipelines.find(currentContext.pipelineId);
	if (pipelinesIt != program->pipelines.end()) return pipelinesIt->second;

	//
	auto programPipelinePtr = new pipeline_type();
	program->pipelines[currentContext.pipelineId] = programPipelinePtr;
	auto& programPipeline = *programPipelinePtr;
	programPipeline.id = currentContext.pipelineId;

	VkRenderPass usedRenderPass = renderPass;
	auto haveDepthBuffer = true;
	auto haveColorBuffer = true;
	auto haveGeometryBuffer = false;
	if (boundFrameBuffer != ID_NONE) {
		auto frameBuffer = boundFrameBuffer < 0 || boundFrameBuffer >= framebuffers.size()?nullptr:framebuffers[boundFrameBuffer];
		if (frameBuffer != nullptr) {
			haveDepthBuffer = frameBuffer->depthTextureId != ID_NONE;
			haveColorBuffer = frameBuffer->colorTextureId != ID_NONE;
			haveGeometryBuffer = frameBuffer->type == framebuffer_object_type::TYPE_GEOMETRYBUFFER;
			usedRenderPass = frameBuffer->renderPass;
		}
	}

	//
	VkResult err;

	//
	VkGraphicsPipelineCreateInfo pipeline;
	memset(&pipeline, 0, sizeof(pipeline));

	// create pipepine
	VkPipelineCacheCreateInfo pipelineCacheCreateInfo;
	memset(&pipelineCacheCreateInfo, 0, sizeof(pipelineCacheCreateInfo));
	VkPipelineCache pipelineCache = VK_NULL_HANDLE;

	VkPipelineVertexInputStateCreateInfo vi;
	VkPipelineInputAssemblyStateCreateInfo ia;
	VkPipelineRasterizationStateCreateInfo rs;
	VkPipelineColorBlendStateCreateInfo cb;
	VkPipelineDepthStencilStateCreateInfo ds;
	VkPipelineViewportStateCreateInfo vp;
	VkPipelineMultisampleStateCreateInfo ms;
	array<VkDynamicState, 2> dse;
	VkPipelineDynamicStateCreateInfo dsc;

	createRasterizationStateCreateInfo(contextIdx, rs);
	createDepthStencilStateCreateInfo(ds);

	vector<VkPipelineShaderStageCreateInfo> shaderStages(program->shaders.size());
	memset(shaderStages.data(), 0, shaderStages.size() * sizeof(VkPipelineShaderStageCreateInfo));

	// shader stages
	auto shaderIdx = 0;
	for (auto shader: program->shaders) {
		shaderStages[shaderIdx].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		shaderStages[shaderIdx].stage = shader->type;
		shaderStages[shaderIdx].module = shader->module;
		shaderStages[shaderIdx].pName = "main";
		shaderIdx++;
	}

	memset(dse.data(), 0, sizeof(VkDynamicState) * dse.size());
	memset(&dsc, 0, sizeof dsc);
	dsc.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dsc.pDynamicStates = dse.data();

	pipeline.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipeline.stageCount = program->shaders.size();
	pipeline.layout = program->pipelineLayout;

	memset(&ia, 0, sizeof(ia));
	ia.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	ia.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

	array<VkPipelineColorBlendAttachmentState, 8> bas;
	if (haveColorBuffer == true) {
		createColorBlendAttachmentState(bas[0]);
	} else
	if (haveGeometryBuffer == true) {
		for (auto i = 0; i < 8; i++) {
			createColorBlendAttachmentState(bas[i]);
		}
	}
	memset(&cb, 0, sizeof(cb));
	cb.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	cb.logicOpEnable = VK_FALSE;
	cb.attachmentCount = haveColorBuffer == true?1:(haveGeometryBuffer == true?8:0);
	cb.pAttachments = haveColorBuffer == true || haveGeometryBuffer == true?bas.data():nullptr;

	memset(&vp, 0, sizeof(vp));
	vp.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	vp.viewportCount = 1;
	dse[dsc.dynamicStateCount++] = VK_DYNAMIC_STATE_VIEWPORT;
	vp.scissorCount = 1;
	dse[dsc.dynamicStateCount++] = VK_DYNAMIC_STATE_SCISSOR;

	memset(&ms, 0, sizeof(ms));
	ms.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	ms.pSampleMask = nullptr;
	ms.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	array<VkVertexInputBindingDescription, 10> vb;
	memset(vb.data(), 0, sizeof(VkVertexInputBindingDescription) * vb.size());
	array<VkVertexInputAttributeDescription, 13> va;
	memset(va.data(), 0, sizeof(VkVertexInputAttributeDescription) * va.size());

	// vertices
	vb[0].binding = 0;
	vb[0].stride = sizeof(float) * 3;
	vb[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	va[0].binding = 0;
	va[0].location = 0;
	va[0].format = VK_FORMAT_R32G32B32_SFLOAT;
	va[0].offset = 0;

	// normals
	vb[1].binding = 1;
	vb[1].stride = sizeof(float) * 3;
	vb[1].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	va[1].binding = 1;
	va[1].location = 1;
	va[1].format = VK_FORMAT_R32G32B32_SFLOAT;
	va[1].offset = 0;

	// texture coordinates
	vb[2].binding = 2;
	vb[2].stride = sizeof(float) * 2;
	vb[2].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	va[2].binding = 2;
	va[2].location = 2;
	va[2].format = VK_FORMAT_R32G32_SFLOAT;
	va[2].offset = 0;

	// colors
	vb[3].binding = 3;
	vb[3].stride = sizeof(float) * 4;
	vb[3].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	va[3].binding = 3;
	va[3].location = 3;
	va[3].format = VK_FORMAT_R32G32B32A32_SFLOAT;
	va[3].offset = 0;

	// tangents
	vb[4].binding = 4;
	vb[4].stride = sizeof(float) * 3;
	vb[4].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	va[4].binding = 4;
	va[4].location = 4;
	va[4].format = VK_FORMAT_R32G32B32_SFLOAT;
	va[4].offset = 0;

	// bitangents
	vb[5].binding = 5;
	vb[5].stride = sizeof(float) * 3;
	vb[5].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	va[5].binding = 5;
	va[5].location = 5;
	va[5].format = VK_FORMAT_R32G32B32_SFLOAT;
	va[5].offset = 0;

	// model matrices 1
	vb[6].binding = 6;
	vb[6].stride = sizeof(float) * 4 * 4;
	vb[6].inputRate = VK_VERTEX_INPUT_RATE_INSTANCE;
	va[6].binding = 6;
	va[6].location = 6;
	va[6].format = VK_FORMAT_R32G32B32A32_SFLOAT;
	va[6].offset = sizeof(float) * 4 * 0;

	// model matrices 2
	va[7].binding = 6;
	va[7].location = 7;
	va[7].format = VK_FORMAT_R32G32B32A32_SFLOAT;
	va[7].offset = sizeof(float) * 4 * 1;

	// model matrices 3
	va[8].binding = 6;
	va[8].location = 8;
	va[8].format = VK_FORMAT_R32G32B32A32_SFLOAT;
	va[8].offset = sizeof(float) * 4 * 2;

	// model matrices 4
	va[9].binding = 6;
	va[9].location = 9;
	va[9].format = VK_FORMAT_R32G32B32A32_SFLOAT;
	va[9].offset = sizeof(float) * 4 * 3;

	// effect color mul
	vb[7].binding = 7;
	vb[7].stride = sizeof(float) * 4;
	vb[7].inputRate = VK_VERTEX_INPUT_RATE_INSTANCE;
	va[10].binding = 7;
	va[10].location = 10;
	va[10].format = VK_FORMAT_R32G32B32A32_SFLOAT;
	va[10].offset = 0;

	// effect color add
	vb[8].binding = 8;
	vb[8].stride = sizeof(float) * 4;
	vb[8].inputRate = VK_VERTEX_INPUT_RATE_INSTANCE;
	va[11].binding = 8;
	va[11].location = 11;
	va[11].format = VK_FORMAT_R32G32B32A32_SFLOAT;
	va[11].offset = 0;

	// origins
	vb[9].binding = 9;
	vb[9].stride = sizeof(float) * 3;
	vb[9].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	va[12].binding = 9;
	va[12].location = 12;
	va[12].format = VK_FORMAT_R32G32B32_SFLOAT;
	va[12].offset = 0;

	memset(&vi, 0, sizeof(vi));
	vi.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vi.pNext = nullptr;
	vi.vertexBindingDescriptionCount = vb.size();
	vi.pVertexBindingDescriptions = vb.data();
	vi.vertexAttributeDescriptionCount = va.size();
	vi.pVertexAttributeDescriptions = va.data();

	pipeline.pVertexInputState = &vi;
	pipeline.pInputAssemblyState = &ia;
	pipeline.pRasterizationState = &rs;
	pipeline.pColorBlendState = haveColorBuffer == true || haveGeometryBuffer == true?&cb:nullptr;
	pipeline.pMultisampleState = &ms;
	pipeline.pViewportState = &vp;
	pipeline.pDepthStencilState = haveDepthBuffer == true?&ds:nullptr;
	pipeline.pStages = shaderStages.data();
	pipeline.renderPass = usedRenderPass;
	pipeline.pDynamicState = &dsc;

	memset(&pipelineCacheCreateInfo, 0, sizeof(pipelineCacheCreateInfo));
	pipelineCacheCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;

	err = vkCreatePipelineCache(device, &pipelineCacheCreateInfo, nullptr, &pipelineCache);
	assert(!err);

	err = vkCreateGraphicsPipelines(device, pipelineCache, 1, &pipeline, nullptr, &programPipeline.pipeline);
	assert(!err);

	//
	vkDestroyPipelineCache(device, pipelineCache, nullptr);

	//
	return programPipelinePtr;
}

inline void VKRenderer::setupObjectsRenderingPipeline(int contextIdx, program_type* program) {
	auto& context = contexts[contextIdx];
	if (context.pipelineId == ID_NONE || context.pipeline == VK_NULL_HANDLE) {
		if (context.pipelineId == ID_NONE) context.pipelineId = createPipelineId(program, contextIdx);
		auto pipeline = getPipelineInternal(contextIdx, program, context.pipelineId);
		if (pipeline == nullptr) {
			pipelineRWlock.writeLock();
			pipeline = createObjectsRenderingPipeline(contextIdx, program);
			pipelineRWlock.unlock();
		}

		//
		if (pipeline->pipeline != context.pipeline) {
			auto& commandBuffer = context.commandBuffers[context.currentCommandBuffer];
			vkCmdBindPipeline(commandBuffer.drawCommand, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->pipeline);
			vkCmdSetViewport(commandBuffer.drawCommand, 0, 1, &viewport);
			vkCmdSetScissor(commandBuffer.drawCommand, 0, 1, &scissor);
			context.pipeline = pipeline->pipeline;
		}
	}
}

VKRenderer::pipeline_type* VKRenderer::createPointsRenderingPipeline(int contextIdx, program_type* program) {
	auto& currentContext = contexts[contextIdx];
	auto pipelinesIt = program->pipelines.find(currentContext.pipelineId);
	if (pipelinesIt != program->pipelines.end()) return pipelinesIt->second;

	//
	auto programPipelinePtr = new pipeline_type();
	program->pipelines[currentContext.pipelineId] = programPipelinePtr;
	auto& programPipeline = *programPipelinePtr;
	programPipeline.id = currentContext.pipelineId;

	VkRenderPass usedRenderPass = renderPass;
	auto haveDepthBuffer = true;
	auto haveColorBuffer = true;
	auto haveGeometryBuffer = false;
	if (boundFrameBuffer != ID_NONE) {
		auto frameBuffer = boundFrameBuffer < 0 || boundFrameBuffer >= framebuffers.size()?nullptr:framebuffers[boundFrameBuffer];
		if (frameBuffer != nullptr) {
			haveDepthBuffer = frameBuffer->depthTextureId != ID_NONE;
			haveColorBuffer = frameBuffer->colorTextureId != ID_NONE;
			haveGeometryBuffer = frameBuffer->type == framebuffer_object_type::TYPE_GEOMETRYBUFFER;
			usedRenderPass = frameBuffer->renderPass;
		}
	}

	//
	VkResult err;

	//
	VkGraphicsPipelineCreateInfo pipeline;
	memset(&pipeline, 0, sizeof(pipeline));

	// Stages
	vector<VkPipelineShaderStageCreateInfo> shaderStages(program->shaders.size());
	memset(shaderStages.data(), 0, shaderStages.size() * sizeof(VkPipelineShaderStageCreateInfo));

	// shader stages
	auto shaderIdx = 0;
	for (auto shader: program->shaders) {
		shaderStages[shaderIdx].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		shaderStages[shaderIdx].stage = shader->type;
		shaderStages[shaderIdx].module = shader->module;
		shaderStages[shaderIdx].pName = "main";
		shaderIdx++;
	}

	// create pipepine
	VkPipelineCacheCreateInfo pipelineCacheCreateInfo;
	memset(&pipelineCacheCreateInfo, 0, sizeof(pipelineCacheCreateInfo));
	VkPipelineCache pipelineCache = VK_NULL_HANDLE;

	VkPipelineVertexInputStateCreateInfo vi;
	VkPipelineInputAssemblyStateCreateInfo ia;
	VkPipelineRasterizationStateCreateInfo rs;
	VkPipelineColorBlendStateCreateInfo cb;
	VkPipelineDepthStencilStateCreateInfo ds;
	VkPipelineViewportStateCreateInfo vp;
	VkPipelineMultisampleStateCreateInfo ms;
	array<VkDynamicState, 2> dse;
	VkPipelineDynamicStateCreateInfo dsc;

	createRasterizationStateCreateInfo(contextIdx, rs);
	createDepthStencilStateCreateInfo(ds);

	memset(dse.data(), 0, sizeof(VkDynamicState) * dse.size());
	memset(&dsc, 0, sizeof dsc);
	dsc.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dsc.pDynamicStates = dse.data();

	pipeline.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipeline.stageCount = program->shaders.size();
	pipeline.layout = program->pipelineLayout;

	memset(&ia, 0, sizeof(ia));
	ia.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	ia.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;

	array<VkPipelineColorBlendAttachmentState, 8> bas;
	if (haveColorBuffer == true) {
		createColorBlendAttachmentState(bas[0]);
	} else
	if (haveGeometryBuffer == true) {
		for (auto i = 0; i < 8; i++) {
			createColorBlendAttachmentState(bas[i]);
		}
	}
	memset(&cb, 0, sizeof(cb));
	cb.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	cb.logicOpEnable = VK_FALSE;
	cb.attachmentCount = haveColorBuffer == true?1:(haveGeometryBuffer == true?8:0);
	cb.pAttachments = haveColorBuffer == true || haveGeometryBuffer == true?bas.data():nullptr;

	memset(&vp, 0, sizeof(vp));
	vp.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	vp.viewportCount = 1;
	dse[dsc.dynamicStateCount++] = VK_DYNAMIC_STATE_VIEWPORT;
	vp.scissorCount = 1;
	dse[dsc.dynamicStateCount++] = VK_DYNAMIC_STATE_SCISSOR;

	memset(&ms, 0, sizeof(ms));
	ms.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	ms.pSampleMask = nullptr;
	ms.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	array<VkVertexInputBindingDescription, 9> vb;
	memset(vb.data(), 0, vb.size() * sizeof(VkVertexInputBindingDescription));
	array<VkVertexInputAttributeDescription, 9> va;
	memset(va.data(), 0, va.size() * sizeof(VkVertexInputAttributeDescription));

	// vertices
	vb[0].binding = 0;
	vb[0].stride = sizeof(float) * 3;
	vb[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	va[0].binding = 0;
	va[0].location = 0;
	va[0].format = VK_FORMAT_R32G32B32_SFLOAT;
	va[0].offset = 0;

	// texture + sprite indices
	vb[1].binding = 1;
	vb[1].stride = sizeof(uint16_t) * 2;
	vb[1].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	va[1].binding = 1;
	va[1].location = 1;
	va[1].format = VK_FORMAT_R16G16_UINT;
	va[1].offset = 0;

	// not in use
	vb[2].binding = 2;
	vb[2].stride = sizeof(float);
	vb[2].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	va[2].binding = 2;
	va[2].location = 2;
	va[2].format = VK_FORMAT_R32_SFLOAT;
	va[2].offset = 0;

	// colors
	vb[3].binding = 3;
	vb[3].stride = sizeof(float) * 4;
	vb[3].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	va[3].binding = 3;
	va[3].location = 3;
	va[3].format = VK_FORMAT_R32G32B32A32_SFLOAT;
	va[3].offset = 0;

	// not in use
	vb[4].binding = 4;
	vb[4].stride = sizeof(float);
	vb[4].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	va[4].binding = 4;
	va[4].location = 4;
	va[4].format = VK_FORMAT_R32_SFLOAT;
	va[4].offset = 0;

	// point size
	vb[5].binding = 5;
	vb[5].stride = sizeof(float);
	vb[5].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	va[5].binding = 5;
	va[5].location = 5;
	va[5].format = VK_FORMAT_R32_SFLOAT;
	va[5].offset = 0;

	// sprite sheet dimension
	vb[6].binding = 6;
	vb[6].stride = sizeof(uint16_t) * 2;
	vb[6].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	va[6].binding = 6;
	va[6].location = 6;
	va[6].format = VK_FORMAT_R16G16_UINT;
	va[6].offset = 0;

	// effect color mul
	vb[7].binding = 7;
	vb[7].stride = sizeof(float) * 4;
	vb[7].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	va[7].binding = 7;
	va[7].location = 10;
	va[7].format = VK_FORMAT_R32G32B32A32_SFLOAT;
	va[7].offset = 0;

	// effect color add
	vb[8].binding = 8;
	vb[8].stride = sizeof(float) * 4;
	vb[8].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	va[8].binding = 8;
	va[8].location = 11;
	va[8].format = VK_FORMAT_R32G32B32A32_SFLOAT;
	va[8].offset = 0;

	//
	memset(&vi, 0, sizeof(vi));
	vi.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vi.pNext = nullptr;
	vi.vertexBindingDescriptionCount = vb.size();
	vi.pVertexBindingDescriptions = vb.data();
	vi.vertexAttributeDescriptionCount = va.size();
	vi.pVertexAttributeDescriptions = va.data();

	pipeline.pVertexInputState = &vi;
	pipeline.pInputAssemblyState = &ia;
	pipeline.pRasterizationState = &rs;
	pipeline.pColorBlendState = haveColorBuffer == true || haveGeometryBuffer == true?&cb:nullptr;
	pipeline.pMultisampleState = &ms;
	pipeline.pViewportState = &vp;
	pipeline.pDepthStencilState = haveDepthBuffer == true?&ds:nullptr;
	pipeline.pStages = shaderStages.data();
	pipeline.renderPass = usedRenderPass;
	pipeline.pDynamicState = &dsc;

	memset(&pipelineCacheCreateInfo, 0, sizeof(pipelineCacheCreateInfo));
	pipelineCacheCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;

	err = vkCreatePipelineCache(device, &pipelineCacheCreateInfo, nullptr, &pipelineCache);
	assert(!err);

	err = vkCreateGraphicsPipelines(device, pipelineCache, 1, &pipeline, nullptr, &programPipeline.pipeline);
	assert(!err);

	//
	vkDestroyPipelineCache(device, pipelineCache, nullptr);

	//
	return programPipelinePtr;
}

inline void VKRenderer::setupPointsRenderingPipeline(int contextIdx, program_type* program) {
	auto& currentContext = contexts[contextIdx];
	if (currentContext.pipelineId == ID_NONE || currentContext.pipeline == VK_NULL_HANDLE) {
		if (currentContext.pipelineId == ID_NONE) currentContext.pipelineId = createPipelineId(program, contextIdx);
		auto pipeline = getPipelineInternal(contextIdx, program, currentContext.pipelineId);
		if (pipeline == nullptr) {
			pipelineRWlock.writeLock();
			pipeline = createPointsRenderingPipeline(contextIdx, program);
			pipelineRWlock.unlock();
		}

		//
		if (pipeline->pipeline != currentContext.pipeline) {
			auto& commandBuffer = currentContext.commandBuffers[currentContext.currentCommandBuffer];
			vkCmdBindPipeline(commandBuffer.drawCommand, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->pipeline);
			vkCmdSetViewport(commandBuffer.drawCommand, 0, 1, &viewport);
			vkCmdSetScissor(commandBuffer.drawCommand, 0, 1, &scissor);
			currentContext.pipeline = pipeline->pipeline;
		}
	}
}

VKRenderer::pipeline_type* VKRenderer::createLinesRenderingPipeline(int contextIdx, program_type* program) {
	auto& currentContext = contexts[contextIdx];
	auto pipelinesIt = program->pipelines.find(currentContext.pipelineId);
	if (pipelinesIt != program->pipelines.end()) return pipelinesIt->second;

	//
	auto programPipelinePtr = new pipeline_type();
	program->pipelines[currentContext.pipelineId] = programPipelinePtr;
	auto& programPipeline = *programPipelinePtr;
	programPipeline.id = currentContext.pipelineId;

	VkRenderPass usedRenderPass = renderPass;
	auto haveDepthBuffer = true;
	auto haveColorBuffer = true;
	auto haveGeometryBuffer = false;
	if (boundFrameBuffer != ID_NONE) {
		auto frameBuffer = boundFrameBuffer < 0 || boundFrameBuffer >= framebuffers.size()?nullptr:framebuffers[boundFrameBuffer];
		if (frameBuffer != nullptr) {
			haveDepthBuffer = frameBuffer->depthTextureId != ID_NONE;
			haveColorBuffer = frameBuffer->colorTextureId != ID_NONE;
			haveGeometryBuffer = frameBuffer->type == framebuffer_object_type::TYPE_GEOMETRYBUFFER;
			usedRenderPass = frameBuffer->renderPass;
		}
	}

	//
	VkResult err;

	//
	VkGraphicsPipelineCreateInfo pipeline;
	memset(&pipeline, 0, sizeof(pipeline));
	VkPipelineCache pipelineCache = VK_NULL_HANDLE;

	// Stages
	vector<VkPipelineShaderStageCreateInfo> shaderStages(program->shaders.size());
	memset(shaderStages.data(), 0, shaderStages.size() * sizeof(VkPipelineShaderStageCreateInfo));

	// shader stages
	auto shaderIdx = 0;
	for (auto shader: program->shaders) {
		shaderStages[shaderIdx].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		shaderStages[shaderIdx].stage = shader->type;
		shaderStages[shaderIdx].module = shader->module;
		shaderStages[shaderIdx].pName = "main";
		shaderIdx++;
	}

	// create pipepine
	VkPipelineCacheCreateInfo pipelineCacheCreateInfo;

	VkPipelineVertexInputStateCreateInfo vi;
	VkPipelineInputAssemblyStateCreateInfo ia;
	VkPipelineRasterizationStateCreateInfo rs;
	VkPipelineColorBlendStateCreateInfo cb;
	VkPipelineDepthStencilStateCreateInfo ds;
	VkPipelineViewportStateCreateInfo vp;
	VkPipelineMultisampleStateCreateInfo ms;
	array<VkDynamicState, 3> dse;
	VkPipelineDynamicStateCreateInfo dsc;

	createRasterizationStateCreateInfo(contextIdx, rs);
	createDepthStencilStateCreateInfo(ds);

	memset(dse.data(), 0, dse.size() * sizeof(VkDynamicState));
	memset(&dsc, 0, sizeof dsc);
	dse[dsc.dynamicStateCount++] = VK_DYNAMIC_STATE_LINE_WIDTH;
	dsc.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dsc.pDynamicStates = dse.data();


	pipeline.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipeline.stageCount = program->shaders.size();
	pipeline.layout = program->pipelineLayout;

	memset(&ia, 0, sizeof(ia));
	ia.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	ia.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;

	array<VkPipelineColorBlendAttachmentState, 8> bas;
	if (haveColorBuffer == true) {
		createColorBlendAttachmentState(bas[0]);
	} else
	if (haveGeometryBuffer == true) {
		for (auto i = 0; i < 8; i++) {
			createColorBlendAttachmentState(bas[i]);
		}
	}
	memset(&cb, 0, sizeof(cb));
	cb.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	cb.logicOpEnable = VK_FALSE;
	cb.attachmentCount = haveColorBuffer == true?1:(haveGeometryBuffer == true?8:0);
	cb.pAttachments = haveColorBuffer == true || haveGeometryBuffer == true?bas.data():nullptr;

	memset(&vp, 0, sizeof(vp));
	vp.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	vp.viewportCount = 1;
	dse[dsc.dynamicStateCount++] = VK_DYNAMIC_STATE_VIEWPORT;
	vp.scissorCount = 1;
	dse[dsc.dynamicStateCount++] = VK_DYNAMIC_STATE_SCISSOR;

	memset(&ms, 0, sizeof(ms));
	ms.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	ms.pSampleMask = nullptr;
	ms.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	array<VkVertexInputBindingDescription, 4> vb;
	memset(vb.data(), 0, vb.size() * sizeof(VkVertexInputBindingDescription));
	array<VkVertexInputAttributeDescription, 4> va;
	memset(va.data(), 0, va.size() * sizeof(VkVertexInputAttributeDescription));

	// vertices
	vb[0].binding = 0;
	vb[0].stride = sizeof(float) * 3;
	vb[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	va[0].binding = 0;
	va[0].location = 0;
	va[0].format = VK_FORMAT_R32G32B32_SFLOAT;
	va[0].offset = 0;

	// normals
	vb[1].binding = 1;
	vb[1].stride = sizeof(float) * 3;
	vb[1].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	va[1].binding = 1;
	va[1].location = 1;
	va[1].format = VK_FORMAT_R32G32B32_SFLOAT;
	va[1].offset = 0;

	// texture coordinates
	vb[2].binding = 2;
	vb[2].stride = sizeof(float) * 2;
	vb[2].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	va[2].binding = 2;
	va[2].location = 2;
	va[2].format = VK_FORMAT_R32G32_SFLOAT;
	va[2].offset = 0;

	// colors
	vb[3].binding = 3;
	vb[3].stride = sizeof(float) * 4;
	vb[3].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	va[3].binding = 3;
	va[3].location = 3;
	va[3].format = VK_FORMAT_R32G32B32A32_SFLOAT;
	va[3].offset = 0;


	memset(&vi, 0, sizeof(vi));
	vi.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vi.pNext = nullptr;
	vi.vertexBindingDescriptionCount = vb.size();
	vi.pVertexBindingDescriptions = vb.data();
	vi.vertexAttributeDescriptionCount = va.size();
	vi.pVertexAttributeDescriptions = va.data();

	pipeline.pVertexInputState = &vi;
	pipeline.pInputAssemblyState = &ia;
	pipeline.pRasterizationState = &rs;
	pipeline.pColorBlendState = haveColorBuffer == true || haveGeometryBuffer == true?&cb:nullptr;
	pipeline.pMultisampleState = &ms;
	pipeline.pViewportState = &vp;
	pipeline.pDepthStencilState = haveDepthBuffer == true?&ds:nullptr;
	pipeline.pStages = shaderStages.data();
	pipeline.renderPass = usedRenderPass;
	pipeline.pDynamicState = &dsc;

	memset(&pipelineCacheCreateInfo, 0, sizeof(pipelineCacheCreateInfo));
	pipelineCacheCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;

	err = vkCreatePipelineCache(device, &pipelineCacheCreateInfo, nullptr, &pipelineCache);
	assert(!err);

	err = vkCreateGraphicsPipelines(device, pipelineCache, 1, &pipeline, nullptr, &programPipeline.pipeline);
	assert(!err);

	//
	vkDestroyPipelineCache(device, pipelineCache, nullptr);

	//
	return programPipelinePtr;
}

inline void VKRenderer::setupLinesRenderingPipeline(int contextIdx, program_type* program) {
	auto& currentContext = contexts[contextIdx];
	if (currentContext.pipelineId == ID_NONE || currentContext.pipeline == VK_NULL_HANDLE) {
		if (currentContext.pipelineId == ID_NONE) currentContext.pipelineId = createPipelineId(program, contextIdx);
		auto pipeline = getPipelineInternal(contextIdx, program, currentContext.pipelineId);
		if (pipeline == nullptr) {
			pipelineRWlock.writeLock();
			pipeline = createLinesRenderingPipeline(contextIdx, program);
			pipelineRWlock.unlock();
		}

		//
		if (pipeline->pipeline != currentContext.pipeline) {
			auto& commandBuffer = currentContext.commandBuffers[currentContext.currentCommandBuffer];
			vkCmdBindPipeline(commandBuffer.drawCommand, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->pipeline);
			vkCmdSetViewport(commandBuffer.drawCommand, 0, 1, &viewport);
			vkCmdSetScissor(commandBuffer.drawCommand, 0, 1, &scissor);
			currentContext.pipeline = pipeline->pipeline;
		}
	}
}

inline void VKRenderer::createSkinningComputingProgram(program_type* program) {
	VkResult err;

	auto programPipelinePtr = new pipeline_type();
	program->pipelines[1] = programPipelinePtr;
	auto& programPipeline = *programPipelinePtr;
	programPipeline.id = 1;

	//
	VkDescriptorSetLayoutBinding layoutBindings1[program->layoutBindings];
	memset(layoutBindings1, 0, sizeof(layoutBindings1));

	// Stages
	vector<VkPipelineShaderStageCreateInfo> shaderStages(program->shaders.size());
	memset(shaderStages.data(), 0, shaderStages.size() * sizeof(VkPipelineShaderStageCreateInfo));

	auto shaderIdx = 0;
	for (auto shader: program->shaders) {
		shaderStages[shaderIdx].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		shaderStages[shaderIdx].stage = shader->type;
		shaderStages[shaderIdx].module = shader->module;
		shaderStages[shaderIdx].pName = "main";

		for (int i = 0; i <= shader->maxBindings; i++) {
			layoutBindings1[i] = {
				.binding = static_cast<uint32_t>(i),
				.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
				.descriptorCount = 1,
				.stageFlags = shader->type,
				.pImmutableSamplers = nullptr
			};
		}

		if (shader->uboBindingIdx != -1) {
			layoutBindings1[shader->uboBindingIdx] = {
				.binding = static_cast<uint32_t>(shader->uboBindingIdx),
				.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
				.descriptorCount = 1,
				.stageFlags = shader->type,
				.pImmutableSamplers = nullptr
			};
		}
		shaderIdx++;
	}
	const VkDescriptorSetLayoutCreateInfo descriptorSetlayoutCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.bindingCount = program->layoutBindings,
		.pBindings = layoutBindings1,
	};

	err = vkCreateDescriptorSetLayout(device, &descriptorSetlayoutCreateInfo, nullptr, &program->descriptorSetLayout1);
	assert(!err);

	//
	const VkPipelineLayoutCreateInfo pPipelineLayoutCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.setLayoutCount = 1,
		.pSetLayouts = &program->descriptorSetLayout1
	};

	//
	for (auto i = 0; i < DRAW_COMMANDBUFFER_MAX; i++) {
		array<VkDescriptorSetLayout, DESC_MAX_UNCACHED> descriptorSetLayouts1;
		descriptorSetLayouts1.fill(program->descriptorSetLayout1);
		//
		VkDescriptorSetAllocateInfo descriptorSetAllocateInfo = {
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
			.pNext = nullptr,
			.descriptorPool = descriptorPool1,
			.descriptorSetCount = DESC_MAX_UNCACHED,
			.pSetLayouts = descriptorSetLayouts1.data()
		};
		for (auto& context: contexts) {
			err = vkAllocateDescriptorSets(device, &descriptorSetAllocateInfo, program->contexts[context.idx].commandBuffers[i].descriptorSets1.data());
			assert(!err);
		}
	}

	//
	err = vkCreatePipelineLayout(device, &pPipelineLayoutCreateInfo, nullptr, &program->pipelineLayout);
	assert(!err);

	// create pipepine
	VkPipelineCacheCreateInfo pipelineCacheCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.initialDataSize = 0,
		.pInitialData = nullptr
	};
	VkPipelineCache pipelineCache = VK_NULL_HANDLE;

	err = vkCreatePipelineCache(device, &pipelineCacheCreateInfo, nullptr, &pipelineCache);
	assert(!err);

	// create pipepine
	VkComputePipelineCreateInfo pipeline = {
		.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.stage = shaderStages[0],
		.layout = program->pipelineLayout,
		.basePipelineHandle = nullptr,
		.basePipelineIndex = 0
	};

	//
	err = vkCreateComputePipelines(device, pipelineCache, 1, &pipeline, nullptr, &programPipeline.pipeline);
	assert(!err);

	//
	vkDestroyPipelineCache(device, pipelineCache, nullptr);
}

inline VKRenderer::pipeline_type* VKRenderer::createSkinningComputingPipeline(int contextIdx, program_type* program) {
	return program->pipelines[1];
}

inline void VKRenderer::setupSkinningComputingPipeline(int contextIdx, program_type* program) {
	auto& currentContext = contexts[contextIdx];
	if (currentContext.pipelineId == ID_NONE || currentContext.pipeline == VK_NULL_HANDLE) {
		if (currentContext.pipelineId == ID_NONE) currentContext.pipelineId = 1;
		auto pipeline = getPipelineInternal(contextIdx, program, 1);
		if (pipeline == nullptr) {
			pipelineRWlock.writeLock();
			pipeline = createSkinningComputingPipeline(contextIdx, program);
			pipelineRWlock.unlock();
		}

		//
		if (pipeline->pipeline != currentContext.pipeline) {
			vkCmdBindPipeline(currentContext.commandBuffers[currentContext.currentCommandBuffer].drawCommand, VK_PIPELINE_BIND_POINT_COMPUTE, pipeline->pipeline);
			currentContext.pipeline = pipeline->pipeline;
		}
	}
}

void VKRenderer::useProgram(void* context, int32_t programId)
{
	auto& currentContext = *static_cast<context_type*>(context);

	//
	if (programId == currentContext.programId) return;

	//
	if (currentContext.program != nullptr) currentContext.lastUnsubmittedPrograms.push_back(currentContext.program);

	//
	unsetPipeline(currentContext.idx);

	//
	currentContext.programId = 0;
	currentContext.program = nullptr;
	currentContext.uniformBuffers.fill(nullptr);
	for (auto& uniformBufferData: currentContext.uniformBufferData) uniformBufferData.resize(0);

	if (programId == ID_NONE) return;

	//
	if (programId < ID_NONE || programId >= programVector.size()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program does not exist: " + to_string(programId));
		return;
	}

	//
	auto program = programVector[programId];
	currentContext.programId = programId;
	currentContext.program = program;

	// set up program ubo
	{
		auto shaderIdx = 0;
		for (auto shader: program->shaders) {
			if (shader->uboBindingIdx == -1) {
				currentContext.uniformBuffers[shaderIdx] = nullptr;
				shaderIdx++;
				continue;
			}
			currentContext.uniformBuffers[shaderIdx] = &shader->uniformBuffers[currentContext.idx];
			currentContext.uniformBufferData[shaderIdx].resize(shader->uboSize);
			shaderIdx++;
		}
	}
}

int32_t VKRenderer::createProgram(int type)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	auto programPtr = new program_type();
	auto& program = *programPtr;
	program.type = type;
	program.id = programVector.size();
	program.contexts.resize(Engine::getThreadCount());
	for (auto& programContext: program.contexts) {
		programContext.descriptorSets2Idx = 0;
		programContext.descriptorSets2.fill(VK_NULL_HANDLE);
		for (auto& programContextCommandBuffer: programContext.commandBuffers) {
			programContextCommandBuffer.descriptorSets1Idx = 0;
			programContextCommandBuffer.descriptorSets2IdxUncached = 0;
			programContextCommandBuffer.descriptorSets1.fill(VK_NULL_HANDLE);
			programContextCommandBuffer.descriptorSets2Uncached.fill(VK_NULL_HANDLE);
		}
	}
	programVector.push_back(programPtr);
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program id: " + to_string(program.id));
	return program.id;
}

void VKRenderer::attachShaderToProgram(int32_t programId, int32_t shaderId)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	auto shaderIt = shaders.find(shaderId);
	if (shaderIt == shaders.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): shader does not exist");
		return;
	}
	if (programId < 0 || programId >= programVector.size()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program does not exist");
		return;
	}
	auto program = programVector[programId];
	program->shaderIds.push_back(shaderId);
	program->shaders.push_back(shaderIt->second);
}

bool VKRenderer::linkProgram(int32_t programId)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + to_string(programId));
	if (programId < 0 || programId >= programVector.size()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program does not exist");
		return false;
	}

	//
	auto& program = *programVector[programId];

	//
	VKGL3CoreShaderProgram::linkProgram(program);

	// create uniform buffers
	auto uniformIdx = 1;
	for (auto shader: program.shaders) {
		// do we need a uniform buffer object for this shader stage?
		if (shader->uboSize > 0) {
			shader->uniformBuffers.resize(Engine::getThreadCount());
			for (auto& context: contexts) {
				auto& uniformBuffer = shader->uniformBuffers[context.idx];
				uniformBuffer.size = shader->uboSize;
				for (auto& uniformBufferBuffer: uniformBuffer.buffers) {
					VmaAllocationInfo allocationInfo = {};
					createBuffer(
						uniformBuffer.size,
						VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
						VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
						uniformBufferBuffer.buffer,
						uniformBufferBuffer.allocation,
						allocationInfo
					);
					VkMemoryPropertyFlags memoryFlags;
					vmaGetMemoryTypeProperties(allocator, allocationInfo.memoryType, &memoryFlags);
					auto memoryMapped = (memoryFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) == VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
					if (memoryMapped == false) {
						Console::println("VKRenderer::" + string(__FUNCTION__) + "(): Could not create memory mappable uniform buffer");
					}
				}
			};
		}
	}

	// bind samplers, set up ingoing attribute layout indices, compile shaders
	shader_type* shaderLast = nullptr;
	for (auto shader: program.shaders) {
		// create shader module
		{
			VkResult err;
			VkShaderModuleCreateInfo shaderModuleCreateInfo;
			shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
			shaderModuleCreateInfo.pNext = nullptr;
			shaderModuleCreateInfo.codeSize = shader->spirv.size() * sizeof(uint32_t);
			shaderModuleCreateInfo.pCode = shader->spirv.data();
			shaderModuleCreateInfo.flags = 0;
			err = vkCreateShaderModule(device, &shaderModuleCreateInfo, nullptr, &shader->module);
			if (err == VK_SUCCESS) {
				if (VERBOSE == true) {
					Console::println(
						string(
							string("VKRenderer::") +
							string(__FUNCTION__) +
							string("[") +
							to_string(shader->id) +
							string("]") +
							string(": SUCCESS")
						 )
					);
				}
			} else {
				Console::println(
					string(
						string("VKRenderer::") +
						string(__FUNCTION__) +
						string("[") +
						to_string(shader->id) +
						string("]") +
						string(": FAILED")
					 )
				);
				Console::println(shader->source);
				return false;
			}
	    }

		//
		shaderLast = shader;
	}

	// create programs in terms of ubos and so on
	if (program.type == PROGRAM_OBJECTS || program.type == PROGRAM_POINTS || program.type == PROGRAM_LINES) {
		createRenderProgram(&program);
	} else
	if (program.type == PROGRAM_COMPUTE) {
		createSkinningComputingProgram(&program);
	} else {
		Console::println(
			string("VKRenderer::") +
			string(__FUNCTION__) +
			string("[") +
			to_string(programId) +
			string("]") +
			string(": unknown program: ") +
			to_string(program.type)
		);
	}

	//
	return true;
}

int32_t VKRenderer::getProgramUniformLocation(int32_t programId, const string& name)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + name);
	if (programId < 0 || programId >= programVector.size()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program does not exist");
		return -1;
	}
	auto program = programVector[programId];
	for (auto& uniformIt: program->uniforms) {
		if (uniformIt.second == name) {
			return uniformIt.first;
		}
	}
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): uniform not found: '" + name + "'");
	return -1;
}

inline void VKRenderer::setProgramUniformInternal(void* context, int32_t uniformId, uint8_t* data, int32_t size) {
	auto& currentContext = *static_cast<context_type*>(context);

	//
	auto changedUniforms = 0;
	auto shaderIdx = 0;
	for (auto shader: currentContext.program->shaders) {
		//
		if (uniformId < 0 || uniformId >= shader->uniformList.size()) {
			Console::println(
				"VKRenderer::" +
				string(__FUNCTION__) +
				"(): program: uniform id out of uniform list bounds: " +
				to_string(currentContext.idx) + ": " +
				to_string(currentContext.programId) + ": " +
				to_string(uniformId) + " / " +
				to_string(shader->uniformList.size())
			);
			Console::println(
				string("\t") +
				to_string(currentContext.idx) + ": " +
				to_string(currentContext.programId) + ": " +
				to_string(uniformId) + " / " +
				currentContext.program->uniforms[uniformId]
			);
			continue;
		}
		auto shaderUniformPtr = uniformId != -1?shader->uniformList[uniformId]:nullptr;
		if (shaderUniformPtr == nullptr) {
			shaderIdx++;
			continue;
		}
		auto& shaderUniform = *shaderUniformPtr;
		if (shaderUniform.type == shader_type::uniform_type::TYPE_SAMPLER2D) {
			shaderUniform.textureUnit = *((int32_t*)data);
		} else
		if (shaderUniform.type == shader_type::uniform_type::TYPE_SAMPLERCUBE) {
			shaderUniform.textureUnit = *((int32_t*)data);
		} else {
			if (currentContext.uniformBuffers[shaderIdx] == nullptr) {
				Console::println(
					"VKRenderer::" +
					string(__FUNCTION__) +
					"(): shader: no shader uniform buffer in context: " +
					to_string(currentContext.idx) + ": " +
					to_string(currentContext.programId) + ": " +
					to_string(uniformId) + "; " +
					to_string(shaderIdx) + ": " +
					shaderUniformPtr->name
				);
				shaderIdx++;
				continue;
			} else
			if (size != shaderUniform.size) {
				Console::println(
					"VKRenderer::" +
					string(__FUNCTION__) +
					"(): program: uniform size != given size: " +
					to_string(currentContext.idx) + ": " +
					to_string(currentContext.programId) + ": " +
					to_string(uniformId) + "; " +
					to_string(shaderIdx) + "; " +
					to_string(currentContext.uniformBuffers[shaderIdx]->size) + "; " +
					to_string(shaderUniform.position + size) + ": " +
					shaderUniform.name + ": " +
					to_string(size) + " / " +
					to_string(shaderUniform.size)
				);
				shaderIdx++;
				continue;
			}
			if (currentContext.uniformBuffers[shaderIdx]->size < shaderUniform.position + size) {
				Console::println(
					"VKRenderer::" +
					string(__FUNCTION__) +
					"(): program: uniform buffer is too small: " +
					to_string(currentContext.idx) + ": " +
					to_string(currentContext.programId) + ": " +
					to_string(uniformId) + "; " +
					to_string(shaderIdx) + "; " +
					to_string(currentContext.uniformBuffers[shaderIdx]->size) + "; " +
					to_string(shaderUniform.position + size) + ": " +
					shaderUniform.name + ": " +
					to_string(shaderUniform.position + size) + " / " +
					to_string(currentContext.uniformBuffers[shaderIdx]->size)
				);
				shaderIdx++;
				continue;
			}
			memcpy(&currentContext.uniformBufferData[shaderIdx][shaderUniform.position], data, size);
		}
		changedUniforms++;
		shaderIdx++;
	}
	if (changedUniforms == 0) {
		if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program: no uniform changed");
	}
}

void VKRenderer::setProgramUniformInteger(void* context, int32_t uniformId, int32_t value)
{
	setProgramUniformInternal(context, uniformId, (uint8_t*)&value, sizeof(int32_t));
}

void VKRenderer::setProgramUniformFloat(void* context, int32_t uniformId, float value)
{
	setProgramUniformInternal(context, uniformId, (uint8_t*)&value, sizeof(float));
}

void VKRenderer::setProgramUniformFloatMatrix3x3(void* context, int32_t uniformId, const array<float, 9>& data)
{
	array<float, 12> _data = {
		data[0],
		data[1],
		data[2],
		0.0f,
		data[3],
		data[4],
		data[5],
		0.0f,
		data[6],
		data[7],
		data[8],
		0.0f
	};
	setProgramUniformInternal(context, uniformId, (uint8_t*)_data.data(), _data.size() * sizeof(float));
}

void VKRenderer::setProgramUniformFloatMatrix4x4(void* context, int32_t uniformId, const array<float, 16>& data)
{
	setProgramUniformInternal(context, uniformId, (uint8_t*)data.data(), data.size() * sizeof(float));
}

void VKRenderer::setProgramUniformFloatMatrices4x4(void* context, int32_t uniformId, int32_t count, FloatBuffer* data)
{
	setProgramUniformInternal(context, uniformId, (uint8_t*)data->getBuffer(), count * sizeof(float) * 16);
}

void VKRenderer::setProgramUniformFloatVec4(void* context, int32_t uniformId, const array<float, 4>& data)
{
	setProgramUniformInternal(context, uniformId, (uint8_t*)data.data(), data.size() * sizeof(float));
}

void VKRenderer::setProgramUniformFloatVec3(void* context, int32_t uniformId, const array<float, 3>& data)
{
	setProgramUniformInternal(context, uniformId, (uint8_t*)data.data(), data.size() * sizeof(float));
}

void VKRenderer::setProgramUniformFloatVec2(void* context, int32_t uniformId, const array<float, 2>& data)
{
	setProgramUniformInternal(context, uniformId, (uint8_t*)data.data(), data.size() * sizeof(float));
}

void VKRenderer::setProgramAttributeLocation(int32_t programId, int32_t location, const string& name)
{
}

int32_t VKRenderer::getLighting(void* context) {
	auto& currentContext = *static_cast<context_type*>(context);
	return currentContext.lighting;
}

void VKRenderer::setLighting(void* context, int32_t lighting) {
	auto& currentContext = *static_cast<context_type*>(context);
	currentContext.lighting = lighting;
}

void VKRenderer::setViewPort(int32_t x, int32_t y, int32_t width, int32_t height)
{
	//
	memset(&viewport, 0, sizeof(viewport));
	viewport.width = static_cast<float>(width);
	viewport.height = static_cast<float>(height);
	viewport.x = static_cast<float>(x);
	viewport.y = static_cast<float>(y);
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	memset(&scissor, 0, sizeof(scissor));
	scissor.extent.width = width;
	scissor.extent.height = height;
	scissor.offset.x = x;
	scissor.offset.y = y;

	//
	this->viewPortX = x;
	this->viewPortY = y;
	this->viewPortWidth = width;
	this->viewPortHeight = height;

	//
	endDrawCommandsAllContexts();
}

void VKRenderer::updateViewPort()
{
}

void VKRenderer::setClearColor(float red, float green, float blue, float alpha)
{
	//
	clearRed = red;
	clearGreen = green;
	clearBlue = blue;
	clearAlpha = alpha;
}

void VKRenderer::enableCulling(void* context)
{
	auto& currentContext = *static_cast<context_type*>(context);
	if (currentContext.cullingEnabled == true) return;
	unsetPipeline(currentContext.idx);
	currentContext.cullingEnabled = true;
	currentContext.frontFaceIndex = currentContext.frontFace;
}

void VKRenderer::disableCulling(void* context)
{
	auto& currentContext = *static_cast<context_type*>(context);
	if (currentContext.cullingEnabled == false) return;
	unsetPipeline(currentContext.idx);
	currentContext.cullingEnabled = false;
	currentContext.frontFaceIndex = 0;
}

void VKRenderer::setFrontFace(void* context, int32_t frontFace)
{
	auto& currentContext = *static_cast<context_type*>(context);
	if (currentContext.frontFace == frontFace) return;
	unsetPipeline(currentContext.idx);
	currentContext.frontFace = frontFace;
	currentContext.frontFaceIndex = currentContext.cullingEnabled == true?frontFace:0;
}

void VKRenderer::setCullFace(int32_t cullFace)
{
	if (cullMode == cullFace) return;
	endDrawCommandsAllContexts();
	cullMode = (VkCullModeFlagBits)cullFace;
}

void VKRenderer::enableBlending()
{
	if (blendingMode == BLENDING_NORMAL) return;
	endDrawCommandsAllContexts();
	blendingMode = BLENDING_NORMAL;
}

void VKRenderer::enableAdditionBlending() {
	if (blendingMode == BLENDING_ADDITIVE) return;
	endDrawCommandsAllContexts();
	blendingMode = BLENDING_ADDITIVE;
}

void VKRenderer::disableBlending()
{
	if (blendingMode == BLENDING_NONE) return;
	endDrawCommandsAllContexts();
	blendingMode = BLENDING_NONE;
}

void VKRenderer::enableDepthBufferWriting()
{
	if (depthBufferWriting == true) return;
	endDrawCommandsAllContexts();
	depthBufferWriting = true;
}

void VKRenderer::disableDepthBufferWriting()
{
	if (depthBufferWriting == false) return;
	endDrawCommandsAllContexts();
	depthBufferWriting = false;
}

void VKRenderer::disableDepthBufferTest()
{
	if (depthBufferTesting == false) return;
	endDrawCommandsAllContexts();
	depthBufferTesting = false;
}

void VKRenderer::enableDepthBufferTest()
{
	if (depthBufferTesting == true) return;
	endDrawCommandsAllContexts();
	depthBufferTesting = true;
}

void VKRenderer::setDepthFunction(int32_t depthFunctionXXX)
{
	if (depthFunction == depthFunctionXXX) return;
	endDrawCommandsAllContexts();
	depthFunction = depthFunctionXXX;
}

void VKRenderer::setColorMask(bool red, bool green, bool blue, bool alpha)
{
}

void VKRenderer::clear(int32_t mask)
{
	//
	beginDrawCommandBuffer(0);
	startRenderPass(0);
	framebuffer_object_type* frameBuffer = nullptr;
	if (boundFrameBuffer != ID_NONE) frameBuffer = boundFrameBuffer < 0 || boundFrameBuffer >= framebuffers.size()?nullptr:framebuffers[boundFrameBuffer];
	auto attachmentIdx = 0;
	VkClearAttachment attachments[9];
	if ((mask & CLEAR_COLOR_BUFFER_BIT) == CLEAR_COLOR_BUFFER_BIT) {
		if (frameBuffer != nullptr && frameBuffer->type == framebuffer_object_type::TYPE_GEOMETRYBUFFER) {
			for (auto i = 0; i < 8; i++) {
				attachments[attachmentIdx].aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
				attachments[attachmentIdx].colorAttachment = attachmentIdx;
				attachments[attachmentIdx].clearValue.color = { clearRed, clearGreen, clearBlue, clearAlpha };
				attachmentIdx++;
			}
		} else
		if (frameBuffer == nullptr || frameBuffer->colorTextureId != ID_NONE) {
			attachments[attachmentIdx].aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			attachments[attachmentIdx].colorAttachment = attachmentIdx;
			attachments[attachmentIdx].clearValue.color = { clearRed, clearGreen, clearBlue, clearAlpha };
			attachmentIdx++;
		}
	}
	if ((mask & CLEAR_DEPTH_BUFFER_BIT) == CLEAR_DEPTH_BUFFER_BIT &&
		(frameBuffer == nullptr || frameBuffer->depthTextureId != ID_NONE)) {
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
		contexts[0].commandBuffers[contexts[0].currentCommandBuffer].drawCommand,
		attachmentIdx,
		attachments,
		1,
		&clearRect
	);
	endRenderPass(0);
	auto currentBufferIdx = contexts[0].currentCommandBuffer;
	auto commandBuffer = endDrawCommandBuffer(0, currentBufferIdx, true);
	if (commandBuffer != VK_NULL_HANDLE) {
		submitDrawCommandBuffers(1, &commandBuffer, contexts[0].commandBuffers[currentBufferIdx].drawFence, false, false);
	}
	AtomicOperations::increment(statistics.clearCalls);
}

int32_t VKRenderer::createTexture()
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	auto texturePtr = new texture_type();
	texturesRWlock.writeLock();
	if (textureIdx - freeTextureIds.size() >= TEXTURES_MAX) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): could not allocate texture, maximum is " + to_string(TEXTURES_MAX));
		texturesRWlock.unlock();
		return ID_NONE;
	}
	auto reuseTextureId = -1;
	if (freeTextureIds.empty() == false) {
		auto freeTextureIdsIdx = freeTextureIds.size() - 1;
		reuseTextureId = freeTextureIds[freeTextureIdsIdx];
		freeTextureIds.erase(freeTextureIds.begin() + freeTextureIdsIdx);
	}
	auto& texture = *texturePtr;
	texture.id = reuseTextureId != -1?reuseTextureId:textureIdx++;
	textures[texture.id] = texturePtr;
	texturesRWlock.unlock();
	return texture.id;
}

int32_t VKRenderer::createDepthBufferTexture(int32_t width, int32_t height, int32_t cubeMapTextureId, int32_t cubeMapTextureIndex) {
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + to_string(width) + "x" + to_string(height));
	auto texturePtr = new texture_type();
	texturesRWlock.writeLock();
	if (textureIdx - freeTextureIds.size() >= TEXTURES_MAX) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): could not allocate texture, maximum is " + to_string(TEXTURES_MAX));
		texturesRWlock.unlock();
		return ID_NONE;
	}
	auto reuseTextureId = -1;
	if (freeTextureIds.empty() == false) {
		auto freeTextureIdsIdx = freeTextureIds.size() - 1;
		reuseTextureId = freeTextureIds[freeTextureIdsIdx];
		freeTextureIds.erase(freeTextureIds.begin() + freeTextureIdsIdx);
	}
	auto& texture = *texturePtr;
	texture.id = reuseTextureId != -1?reuseTextureId:textureIdx++;
	textures[texture.id] = texturePtr;
	texturesRWlock.unlock();
	createDepthBufferTexture(texture.id, width, height, cubeMapTextureId, cubeMapTextureIndex);
	return texture.id;
}

void VKRenderer::createDepthBufferTexture(int32_t textureId, int32_t width, int32_t height, int32_t cubeMapTextureId, int32_t cubeMapTextureIndex)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + to_string(textureId) + " / " + to_string(width) + "x" + to_string(height));
	auto& depthBufferTexture = *textures.find(textureId)->second;
	depthBufferTexture.format = VK_FORMAT_D32_SFLOAT;
	depthBufferTexture.width = width;
	depthBufferTexture.height = height;
	depthBufferTexture.cubemapTextureIndex = cubeMapTextureId == ID_NONE?0:cubeMapTextureIndex;

	//
	auto cubeMapTexture = cubeMapTextureId == ID_NONE?nullptr:textures.find(cubeMapTextureId)->second;
	depthBufferTexture.cubemapBufferTexture = cubeMapTexture != nullptr?cubeMapTexture->cubemapDepthBuffer:nullptr;

	//
	VkResult err;

	//
	if (cubeMapTexture == nullptr) {
		// mark for deletion
		deleteMutex.lock();
		deleteImages.push_back(
			{
				.image = depthBufferTexture.image,
				.allocation = depthBufferTexture.allocation,
				.imageView = depthBufferTexture.view,
				.sampler = depthBufferTexture.sampler
			}
		);
		deleteMutex.unlock();

		//
		const VkImageCreateInfo imageCreateInfo = {
			.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.imageType = VK_IMAGE_TYPE_2D,
			.format = depthBufferTexture.format,
			.extent = {
				.width = depthBufferTexture.width,
				.height = depthBufferTexture.height,
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
			.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
		};

		VmaAllocationCreateInfo allocationCreateInfo = {};
		allocationCreateInfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;

		VmaAllocationInfo allocationInfo = {};
		err = vmaCreateImage(allocator, &imageCreateInfo, &allocationCreateInfo, &depthBufferTexture.image, &depthBufferTexture.allocation, &allocationInfo);
		assert(!err);

		// type
		depthBufferTexture.type = texture_type::TYPE_DEPTHBUFFER;
		depthBufferTexture.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
		depthBufferTexture.accessTypes = { THSVS_ACCESS_NONE, THSVS_ACCESS_NONE };
		depthBufferTexture.svsLayout = THSVS_IMAGE_LAYOUT_OPTIMAL;
		depthBufferTexture.vkLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	}

	// create sampler
	const VkSamplerCreateInfo samplerCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.magFilter = VK_FILTER_NEAREST,
		.minFilter = VK_FILTER_NEAREST,
		.mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST,
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
	err = vkCreateSampler(device, &samplerCreateInfo, nullptr, &depthBufferTexture.sampler);
	assert(!err);

	// create image view
	VkImageViewCreateInfo viewCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.image = cubeMapTexture != nullptr?cubeMapTexture->cubemapDepthBuffer->image:depthBufferTexture.image,
		.viewType = VK_IMAGE_VIEW_TYPE_2D,
		.format = depthBufferTexture.format,
		.components = VkComponentMapping(),
		.subresourceRange = {
			.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT,
			.baseMipLevel = 0,
			.levelCount = 1,
			.baseArrayLayer = cubeMapTexture != nullptr?static_cast<uint32_t>(cubeMapTextureIndex - CUBEMAPTEXTUREINDEX_MIN):0,
			.layerCount = 1
		},
	};
	err = vkCreateImageView(device, &viewCreateInfo, nullptr, &depthBufferTexture.view);
	assert(!err);
}

int32_t VKRenderer::createColorBufferTexture(int32_t width, int32_t height, int32_t cubeMapTextureId, int32_t cubeMapTextureIndex) {
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + to_string(width) + "x" + to_string(height));
	auto texturePtr = new texture_type();
	texturesRWlock.writeLock();
	if (textureIdx - freeTextureIds.size() >= TEXTURES_MAX) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): could not allocate texture, maximum is " + to_string(TEXTURES_MAX));
		texturesRWlock.unlock();
		return ID_NONE;
	}
	auto reuseTextureId = -1;
	if (freeTextureIds.empty() == false) {
		auto freeTextureIdsIdx = freeTextureIds.size() - 1;
		reuseTextureId = freeTextureIds[freeTextureIdsIdx];
		freeTextureIds.erase(freeTextureIds.begin() + freeTextureIdsIdx);
	}
	auto& texture = *texturePtr;
	texture.id = reuseTextureId != -1?reuseTextureId:textureIdx++;
	textures[texture.id] = texturePtr;
	texturesRWlock.unlock();
	createBufferTexture(texture.id, width, height, cubeMapTextureId, cubeMapTextureIndex, format);
	return texture.id;
}

void VKRenderer::createBufferTexture(int32_t textureId, int32_t width, int32_t height, int32_t cubeMapTextureId, int32_t cubeMapTextureIndex, VkFormat format)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + to_string(textureId) + " / " + to_string(width) + "x" + to_string(height) + "(" + to_string(cubeMapTextureId) + " / " + to_string(cubeMapTextureIndex) + ")");
	auto& colorBufferTexture = *textures.find(textureId)->second;
	colorBufferTexture.format = format;
	colorBufferTexture.width = width;
	colorBufferTexture.height = height;
	colorBufferTexture.cubemapTextureIndex = cubeMapTextureId == ID_NONE?0:cubeMapTextureIndex;

	//
	auto cubeMapTexture = cubeMapTextureId == ID_NONE?nullptr:textures.find(cubeMapTextureId)->second;
	colorBufferTexture.cubemapBufferTexture = cubeMapTexture != nullptr?cubeMapTexture->cubemapColorBuffer:nullptr;

	//
	VkResult err;

	// non cube map textures
	if (cubeMapTexture == nullptr) {
		// mark for deletion
		deleteMutex.lock();
		deleteImages.push_back(
			{
				.image = colorBufferTexture.image,
				.allocation = colorBufferTexture.allocation,
				.imageView = colorBufferTexture.view,
				.sampler = colorBufferTexture.sampler
			});
		deleteMutex.unlock();

		//
		const VkImageCreateInfo imageCreateInfo = {
			.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.imageType = VK_IMAGE_TYPE_2D,
			.format = colorBufferTexture.format,
			.extent = {
				.width = colorBufferTexture.width,
				.height = colorBufferTexture.height,
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
			.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
		};

		VmaAllocationCreateInfo allocationCreateInfo = {};
		allocationCreateInfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;

		VmaAllocationInfo allocationInfo = {};
		err = vmaCreateImage(allocator, &imageCreateInfo, &allocationCreateInfo, &colorBufferTexture.image, &colorBufferTexture.allocation, &allocationInfo);
		assert(!err);

		// type
		colorBufferTexture.type = texture_type::TYPE_COLORBUFFER;
		colorBufferTexture.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		colorBufferTexture.accessTypes = { THSVS_ACCESS_NONE, THSVS_ACCESS_NONE };
		colorBufferTexture.svsLayout = THSVS_IMAGE_LAYOUT_OPTIMAL;
		colorBufferTexture.vkLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	} else {
		colorBufferTexture.vkLayout = VK_IMAGE_LAYOUT_GENERAL;
	}

	// create sampler
	const VkSamplerCreateInfo samplerCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.magFilter = VK_FILTER_LINEAR,
		.minFilter = VK_FILTER_LINEAR,
		.mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST,
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
	err = vkCreateSampler(device, &samplerCreateInfo, nullptr, &colorBufferTexture.sampler);
	assert(!err);

	// create image view
	VkImageViewCreateInfo viewCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.image = cubeMapTexture != nullptr?cubeMapTexture->cubemapColorBuffer->image:colorBufferTexture.image,
		.viewType = VK_IMAGE_VIEW_TYPE_2D,
		.format = colorBufferTexture.format,
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
			.baseArrayLayer = cubeMapTexture != nullptr?static_cast<uint32_t>(cubeMapTextureIndex - CUBEMAPTEXTUREINDEX_MIN):0,
			.layerCount = 1
		}
	};
	err = vkCreateImageView(device, &viewCreateInfo, nullptr, &colorBufferTexture.view);
	assert(!err);
}

int32_t VKRenderer::createGBufferGeometryTexture(int32_t width, int32_t height) {
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + to_string(width) + "x" + to_string(height));
	auto texturePtr = new texture_type();
	texturesRWlock.writeLock();
	if (textureIdx - freeTextureIds.size() >= TEXTURES_MAX) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): could not allocate texture, maximum is " + to_string(TEXTURES_MAX));
		texturesRWlock.unlock();
		return ID_NONE;
	}
	auto reuseTextureId = -1;
	if (freeTextureIds.empty() == false) {
		auto freeTextureIdsIdx = freeTextureIds.size() - 1;
		reuseTextureId = freeTextureIds[freeTextureIdsIdx];
		freeTextureIds.erase(freeTextureIds.begin() + freeTextureIdsIdx);
	}
	auto& texture = *texturePtr;
	texture.id = reuseTextureId != -1?reuseTextureId:textureIdx++;
	textures[texture.id] = texturePtr;
	texturesRWlock.unlock();
	createBufferTexture(texture.id, width, height, ID_NONE, ID_NONE, VK_FORMAT_R16G16B16A16_SFLOAT);
	return texture.id;
}

int32_t VKRenderer::createGBufferColorTexture(int32_t width, int32_t height) {
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + to_string(width) + "x" + to_string(height));
	auto texturePtr = new texture_type();
	texturesRWlock.writeLock();
	if (textureIdx - freeTextureIds.size() >= TEXTURES_MAX) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): could not allocate texture, maximum is " + to_string(TEXTURES_MAX));
		texturesRWlock.unlock();
		return ID_NONE;
	}
	auto reuseTextureId = -1;
	if (freeTextureIds.empty() == false) {
		auto freeTextureIdsIdx = freeTextureIds.size() - 1;
		reuseTextureId = freeTextureIds[freeTextureIdsIdx];
		freeTextureIds.erase(freeTextureIds.begin() + freeTextureIdsIdx);
	}
	auto& texture = *texturePtr;
	texture.id = reuseTextureId != -1?reuseTextureId:textureIdx++;
	textures[texture.id] = texturePtr;
	texturesRWlock.unlock();
	createBufferTexture(texture.id, width, height, ID_NONE, ID_NONE, format);
	return texture.id;
}

void VKRenderer::uploadCubeMapTexture(void* context, Texture* textureLeft, Texture* textureRight, Texture* textureTop, Texture* textureBottom, Texture* textureFront, Texture* textureBack) {
	if (VERBOSE == true) {
		Console::println(
			"VKRenderer::" + string(__FUNCTION__) + "(): " +
			textureLeft->getId() + " / " +
			textureRight->getId() + " / " +
			textureTop->getId() + " / " +
			textureBottom->getId() + " / " +
			textureFront->getId() + " / " +
			textureBack->getId()
		);
	}

	// have our context typed
	auto& currentContext = *static_cast<context_type*>(context);
	auto& boundTexture = currentContext.boundTextures[currentContext.activeTextureUnit];

	//
	texturesRWlock.writeLock(); // TODO: have a more fine grained locking here
	auto textureObjectIt = textures.find(boundTexture.id);
	if (textureObjectIt == textures.end()) {
		texturesRWlock.unlock();
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): texture not found: " + to_string(boundTexture.id));
		return;
	}
	auto& texture = *textureObjectIt->second;

	// already uploaded
	if (texture.uploaded == true) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): texture already uploaded: " + to_string(boundTexture.id));
		texturesRWlock.unlock();
		return;
	}

	texture.type = texture_type::TYPE_CUBEMAP;
	texture.width = textureLeft->getTextureWidth();
	texture.height = textureLeft->getTextureHeight();
	texture.format = VK_FORMAT_R8G8B8A8_UNORM;
	texture.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	texture.accessTypes = { THSVS_ACCESS_HOST_PREINITIALIZED, THSVS_ACCESS_NONE };
	texture.vkLayout = VK_IMAGE_LAYOUT_PREINITIALIZED;

	// create color buffer texture
	//	TODO: no general
	const VkImageCreateInfo imageCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
		.pNext = nullptr,
		.flags = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT,
		.imageType = VK_IMAGE_TYPE_2D,
		.format = texture.format,
		.extent = {
			.width = texture.width,
			.height = texture.height,
			.depth = 1
		},
		.mipLevels = 1,
		.arrayLayers = 6,
		.samples = VK_SAMPLE_COUNT_1_BIT,
		.tiling = VK_IMAGE_TILING_OPTIMAL,
		.usage = VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT,
		.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
		.queueFamilyIndexCount = 0,
		.pQueueFamilyIndices = 0,
		.initialLayout = VK_IMAGE_LAYOUT_PREINITIALIZED,
	};

	//
	VkResult err;

	VmaAllocationCreateInfo allocationCreateInfo = {};
	allocationCreateInfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;

	VmaAllocationInfo allocationInfo = {};
	err = vmaCreateImage(allocator, &imageCreateInfo, &allocationCreateInfo, &texture.image, &texture.allocation, &allocationInfo);
	assert(!err);

	//
	uploadCubeMapSingleTexture(context, &texture, textureLeft, 0);
	uploadCubeMapSingleTexture(context, &texture, textureRight, 1);
	uploadCubeMapSingleTexture(context, &texture, textureTop, 2);
	uploadCubeMapSingleTexture(context, &texture, textureBottom, 3);
	uploadCubeMapSingleTexture(context, &texture, textureFront, 4);
	uploadCubeMapSingleTexture(context, &texture, textureBack, 5);

	//
	setImageLayout2(
		currentContext.idx,
		&texture,
		{ THSVS_ACCESS_TRANSFER_WRITE, THSVS_ACCESS_NONE },
		{ THSVS_ACCESS_FRAGMENT_SHADER_READ_SAMPLED_IMAGE_OR_UNIFORM_TEXEL_BUFFER, THSVS_ACCESS_NONE },
		THSVS_IMAGE_LAYOUT_OPTIMAL,
		THSVS_IMAGE_LAYOUT_OPTIMAL,
		false,
		0,
		1,
		0,
		6
	);
	texture.accessTypes =
		{{
			{ THSVS_ACCESS_FRAGMENT_SHADER_READ_SAMPLED_IMAGE_OR_UNIFORM_TEXEL_BUFFER, THSVS_ACCESS_NONE },
			{ THSVS_ACCESS_FRAGMENT_SHADER_READ_SAMPLED_IMAGE_OR_UNIFORM_TEXEL_BUFFER, THSVS_ACCESS_NONE },
			{ THSVS_ACCESS_FRAGMENT_SHADER_READ_SAMPLED_IMAGE_OR_UNIFORM_TEXEL_BUFFER, THSVS_ACCESS_NONE },
			{ THSVS_ACCESS_FRAGMENT_SHADER_READ_SAMPLED_IMAGE_OR_UNIFORM_TEXEL_BUFFER, THSVS_ACCESS_NONE },
			{ THSVS_ACCESS_FRAGMENT_SHADER_READ_SAMPLED_IMAGE_OR_UNIFORM_TEXEL_BUFFER, THSVS_ACCESS_NONE },
			{ THSVS_ACCESS_FRAGMENT_SHADER_READ_SAMPLED_IMAGE_OR_UNIFORM_TEXEL_BUFFER, THSVS_ACCESS_NONE }
		}};
	texture.vkLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

	// create sampler
	const VkSamplerCreateInfo samplerCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.magFilter = VK_FILTER_LINEAR,
		.minFilter = VK_FILTER_LINEAR,
		.mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST,
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
	err = vkCreateSampler(device, &samplerCreateInfo, nullptr, &texture.sampler);
	assert(!err);

	// create image view
	VkImageViewCreateInfo viewCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.image = texture.image,
		.viewType = VK_IMAGE_VIEW_TYPE_CUBE,
		.format = texture.format,
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
			.layerCount = 6
		}
	};
	err = vkCreateImageView(device, &viewCreateInfo, nullptr, &texture.view);
	assert(!err);

	//
	boundTexture.sampler = texture.sampler;
	boundTexture.view = texture.view;
	boundTexture.layout = texture.vkLayout;

	//
	texture.uploaded = true;

	//
	texturesRWlock.unlock();
}

int32_t VKRenderer::createCubeMapTexture(void* context, int32_t width, int32_t height) {
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");

	// have our context typed
	auto& currentContext = *static_cast<context_type*>(context);

	//
	auto texturePtr = new texture_type();
	texturesRWlock.writeLock();
	if (textureIdx - freeTextureIds.size() >= TEXTURES_MAX) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): could not allocate texture, maximum is " + to_string(TEXTURES_MAX));
		texturesRWlock.unlock();
		return ID_NONE;
	}
	auto reuseTextureId = -1;
	if (freeTextureIds.empty() == false) {
		auto freeTextureIdsIdx = freeTextureIds.size() - 1;
		reuseTextureId = freeTextureIds[freeTextureIdsIdx];
		freeTextureIds.erase(freeTextureIds.begin() + freeTextureIdsIdx);
	}
	auto& texture = *texturePtr;
	texture.id = reuseTextureId != -1?reuseTextureId:textureIdx++;
	texture.type = texture_type::TYPE_CUBEMAP;
	texture.format = format;
	texture.width = width;
	texture.height = height;
	texture.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	texture.vkLayout = VK_IMAGE_LAYOUT_GENERAL;
	textures[texture.id] = texturePtr;

	// create color buffer texture
	//	TODO: only create on demand
	{
		texture.cubemapColorBuffer = new texture_type();
		texture.cubemapColorBuffer->id = -1;
		texture.cubemapColorBuffer->type = texture_type::TYPE_COLORBUFFER;
		texture.cubemapColorBuffer->format = format;
		texture.cubemapColorBuffer->width = width;
		texture.cubemapColorBuffer->height = height;
		texture.cubemapColorBuffer->aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		texture.cubemapColorBuffer->vkLayout = VK_IMAGE_LAYOUT_GENERAL;
		const VkImageCreateInfo imageCreateInfo = {
			.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
			.pNext = nullptr,
			.flags = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT,
			.imageType = VK_IMAGE_TYPE_2D,
			.format = texture.cubemapColorBuffer->format,
			.extent = {
				.width = texture.cubemapColorBuffer->width,
				.height = texture.cubemapColorBuffer->height,
				.depth = 1
			},
			.mipLevels = 1,
			.arrayLayers = 6,
			.samples = VK_SAMPLE_COUNT_1_BIT,
			.tiling = VK_IMAGE_TILING_OPTIMAL,
			.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
			.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
			.queueFamilyIndexCount = 0,
			.pQueueFamilyIndices = 0,
			.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED
		};

		//
		VkResult err;

		VmaAllocationCreateInfo allocationCreateInfo = {};
		allocationCreateInfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;

		VmaAllocationInfo allocationInfo = {};
		err = vmaCreateImage(allocator, &imageCreateInfo, &allocationCreateInfo, &texture.cubemapColorBuffer->image, &texture.cubemapColorBuffer->allocation, &allocationInfo);
		assert(!err);

		// create sampler
		const VkSamplerCreateInfo samplerCreateInfo = {
			.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.magFilter = VK_FILTER_LINEAR,
			.minFilter = VK_FILTER_LINEAR,
			.mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST,
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
		err = vkCreateSampler(device, &samplerCreateInfo, nullptr, &texture.sampler);
		assert(!err);

		// create image view
		VkImageViewCreateInfo viewCreateInfo = {
			.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.image = texture.cubemapColorBuffer->image,
			.viewType = VK_IMAGE_VIEW_TYPE_CUBE,
			.format = texture.cubemapColorBuffer->format,
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
				.layerCount = 6
			}
		};
		err = vkCreateImageView(device, &viewCreateInfo, nullptr, &texture.view);
		assert(!err);
	}

	// general
	setImageLayout2(
		currentContext.idx,
		texture.cubemapColorBuffer,
		{ THSVS_ACCESS_NONE, THSVS_ACCESS_NONE },
		{ THSVS_ACCESS_NONE, THSVS_ACCESS_NONE },
		THSVS_IMAGE_LAYOUT_OPTIMAL,
		THSVS_IMAGE_LAYOUT_GENERAL,
		false,
		0,
		1,
		0,
		6
	);

	// create depth buffer texture
	//	TODO: only create on demand
	{
		texture.cubemapDepthBuffer = new texture_type();
		texture.cubemapDepthBuffer->id = -1;
		texture.cubemapDepthBuffer->format = VK_FORMAT_D32_SFLOAT;
		texture.cubemapDepthBuffer->width = width;
		texture.cubemapDepthBuffer->height = height;
		texture.cubemapDepthBuffer->type = texture_type::TYPE_DEPTHBUFFER;
		texture.cubemapDepthBuffer->aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
		const VkImageCreateInfo imageCreateInfo = {
			.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
			.pNext = nullptr,
			.flags = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT,
			.imageType = VK_IMAGE_TYPE_2D,
			.format = texture.cubemapDepthBuffer->format,
			.extent = {
				.width = texture.cubemapDepthBuffer->width,
				.height = texture.cubemapDepthBuffer->height,
				.depth = 1
			},
			.mipLevels = 1,
			.arrayLayers = 6,
			.samples = VK_SAMPLE_COUNT_1_BIT,
			.tiling = VK_IMAGE_TILING_OPTIMAL,
			.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
			.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
			.queueFamilyIndexCount = 0,
			.pQueueFamilyIndices = 0,
			.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
		};

		//
		VkResult err;

		VmaAllocationCreateInfo allocationCreateInfo = {};
		allocationCreateInfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;

		VmaAllocationInfo allocation_info = {};
		err = vmaCreateImage(allocator, &imageCreateInfo, &allocationCreateInfo, &texture.cubemapDepthBuffer->image, &texture.cubemapDepthBuffer->allocation, &allocation_info);
		assert(!err);
	}

	//
	texturesRWlock.unlock();

	//
	return texture.id;
}

void VKRenderer::uploadTexture(void* context, Texture* texture)
{
	// have our context typed
	auto& currentContext = *static_cast<context_type*>(context);
	auto& boundTexture = currentContext.boundTextures[currentContext.activeTextureUnit];

	//
	texturesRWlock.writeLock(); // TODO: have a more fine grained locking here
	auto textureObjectIt = textures.find(boundTexture.id);
	if (textureObjectIt == textures.end()) {
		texturesRWlock.unlock();
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): texture not found: " + to_string(boundTexture.id));
		return;
	}
	auto& textureType = *textureObjectIt->second;

	// already uploaded
	if (textureType.uploaded == true) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): texture already uploaded: " + to_string(boundTexture.id));
		texturesRWlock.unlock();
		return;
	}

	//
	uint32_t mipLevels = 1;
	textureType.width = texture->getTextureWidth();
	textureType.height = texture->getTextureHeight();
 	textureType.type = texture_type::TYPE_TEXTURE;
	textureType.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;

	//
	const VkFormat textureFormat = texture->getDepth() == 32?VK_FORMAT_R8G8B8A8_UNORM:VK_FORMAT_R8G8B8A8_UNORM;
	VkFormatProperties textureFormatProperties;
	VkResult err;


	vkGetPhysicalDeviceFormatProperties(gpu, textureFormat, &textureFormatProperties);
	if ((textureFormatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) {
		//
		struct texture_type stagingTexture;
		memset(&stagingTexture, 0, sizeof(stagingTexture));
		stagingTexture.width = texture->getTextureWidth();
		stagingTexture.height = texture->getTextureHeight();
		stagingTexture.type = texture_type::TYPE_TEXTURE;
		stagingTexture.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;

		//
		mipLevels = texture->isUseMipMap() == true?getMipLevels(texture):1;

		//
		prepareTextureImage(
			currentContext.idx,
			&stagingTexture,
			VK_IMAGE_TILING_LINEAR,
			VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
			texture,
			{ THSVS_ACCESS_TRANSFER_READ, THSVS_ACCESS_NONE },
			THSVS_IMAGE_LAYOUT_OPTIMAL
		);
		prepareTextureImage(
			currentContext.idx,
			&textureType,
			VK_IMAGE_TILING_OPTIMAL,
			VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			texture,
			{ THSVS_ACCESS_TRANSFER_WRITE, THSVS_ACCESS_NONE },
			THSVS_IMAGE_LAYOUT_OPTIMAL,
			false,
			0,
			mipLevels
		);
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
				.width = textureType.width,
				.height = textureType.height,
				.depth = 1
			}
		};
		prepareSetupCommandBuffer(currentContext.idx);
		vkCmdCopyImage(
			currentContext.setupCommandInUse,
			stagingTexture.image,
			VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
			textureType.image,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			1,
			&copy_region
		);
		finishSetupCommandBuffer(currentContext.idx);
		if (texture->isUseMipMap() == true) {
			//
			auto textureWidth = texture->getTextureWidth();
			auto textureHeight = texture->getTextureHeight();
			for (uint32_t i = 1; i < mipLevels; i++) {
				const VkImageBlit imageBlit = {
					.srcSubresource = {
						.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
						.mipLevel = 0,
						.baseArrayLayer = 0,
						.layerCount = 1
					},
					.srcOffsets = {
						{
							.x = 0,
							.y = 0,
							.z = 0
						},
						{
							.x = textureWidth,
							.y = textureHeight,
							.z = 1
						}
					},
					.dstSubresource = {
						.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
						.mipLevel = i,
						.baseArrayLayer = 0,
						.layerCount = 1
					},
					.dstOffsets = {
						{
							.x = 0,
							.y = 0,
							.z = 0
						},
						{
							.x = int32_t(textureWidth >> i),
							.y = int32_t(textureHeight >> i),
							.z = 1
						}
					}
				};
				prepareSetupCommandBuffer(currentContext.idx);
				vkCmdBlitImage(
					currentContext.setupCommandInUse,
					stagingTexture.image,
					VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
					textureType.image,
					VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
					1,
					&imageBlit,
					VK_FILTER_LINEAR
				);
				finishSetupCommandBuffer(currentContext.idx);
			}
		}

		setImageLayout(
			currentContext.idx,
			&textureType,
			{ THSVS_ACCESS_FRAGMENT_SHADER_READ_SAMPLED_IMAGE_OR_UNIFORM_TEXEL_BUFFER, THSVS_ACCESS_NONE },
			THSVS_IMAGE_LAYOUT_OPTIMAL,
			false,
			0,
			mipLevels,
			true
		);

		// mark for deletion
		deleteMutex.lock();
		deleteImages.push_back(
			{
				.image = stagingTexture.image,
				.allocation = stagingTexture.allocation,
				.imageView = VK_NULL_HANDLE,
				.sampler = VK_NULL_HANDLE
			}
		);
		deleteMutex.unlock();
	} else
	if ((textureFormatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) {
		// TODO: not sure if I should support this path
		// Device can texture using linear textures
		prepareTextureImage(
			currentContext.idx,
			&textureType,
			VK_IMAGE_TILING_LINEAR,
			VK_IMAGE_USAGE_SAMPLED_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
			texture,
			{ THSVS_ACCESS_FRAGMENT_SHADER_READ_SAMPLED_IMAGE_OR_UNIFORM_TEXEL_BUFFER, THSVS_ACCESS_NONE },
			THSVS_IMAGE_LAYOUT_OPTIMAL
		);
	}

	const VkSamplerCreateInfo samplerCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.magFilter = VK_FILTER_LINEAR,
		.minFilter = VK_FILTER_LINEAR,
		.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,
		.addressModeU = texture->isRepeat() == true?VK_SAMPLER_ADDRESS_MODE_REPEAT:(texture->getClampMode() == Texture::CLAMPMODE_EDGE?VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE:VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER),
		.addressModeV = texture->isRepeat() == true?VK_SAMPLER_ADDRESS_MODE_REPEAT:(texture->getClampMode() == Texture::CLAMPMODE_EDGE?VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE:VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER),
		.addressModeW = texture->isRepeat() == true?VK_SAMPLER_ADDRESS_MODE_REPEAT:(texture->getClampMode() == Texture::CLAMPMODE_EDGE?VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE:VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER),
		.mipLodBias = 0.0f,
		.anisotropyEnable = VK_FALSE,
		.maxAnisotropy = 1,
		.compareEnable = VK_FALSE,
		.compareOp = VK_COMPARE_OP_NEVER,
		.minLod = 0.0f,
		.maxLod = texture->isUseMipMap() == true?static_cast<float>(mipLevels):0.0f,
		.borderColor = VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK,
		.unnormalizedCoordinates = VK_FALSE,
	};
	VkImageViewCreateInfo viewCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.image = textureType.image,
		.viewType = VK_IMAGE_VIEW_TYPE_2D,
		.format = textureFormat,
		.components = {
			.r = VK_COMPONENT_SWIZZLE_R,
			.g = VK_COMPONENT_SWIZZLE_G,
			.b = VK_COMPONENT_SWIZZLE_B,
			.a = VK_COMPONENT_SWIZZLE_A,
		},
		.subresourceRange = {
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
			.baseMipLevel = 0,
			.levelCount = mipLevels,
			.baseArrayLayer = 0,
			.layerCount = 1
		}
	};

	// create sampler
	err = vkCreateSampler(device, &samplerCreateInfo, nullptr, &textureType.sampler);
	assert(!err);

	// create image view
	err = vkCreateImageView(device, &viewCreateInfo, nullptr, &textureType.view);
	assert(!err);

	//
	boundTexture.id = ID_NONE;
	boundTexture.sampler = VK_NULL_HANDLE;
	boundTexture.view = VK_NULL_HANDLE;
	boundTexture.layout = VK_IMAGE_LAYOUT_UNDEFINED;

	//
	textureType.uploaded = true;

	//
	texturesRWlock.unlock();

	//
	AtomicOperations::increment(statistics.textureUploads);
}

void VKRenderer::uploadCubeMapSingleTexture(void* context, texture_type* cubemapTextureType, Texture* texture, uint32_t baseArrayLayer)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + texture->getId());

	// have our context typed
	auto& currentContext = *static_cast<context_type*>(context);
	auto& cubemapTextureTypeRef = *cubemapTextureType;

	//
	const VkFormat textureFormat = texture->getDepth() == 32?VK_FORMAT_R8G8B8A8_UNORM:VK_FORMAT_R8G8B8A8_UNORM;
	VkFormatProperties textureFormatProperties;
	VkResult err;
	vkGetPhysicalDeviceFormatProperties(gpu, textureFormat, &textureFormatProperties);
	if ((textureFormatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) {
		//
		struct texture_type staging_texture;
		memset(&staging_texture, 0, sizeof(staging_texture));
		staging_texture.width = texture->getTextureWidth();
		staging_texture.height = texture->getTextureHeight();
		staging_texture.type = texture_type::TYPE_TEXTURE;
		staging_texture.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;

		//
		prepareTextureImage(
			currentContext.idx,
			&staging_texture,
			VK_IMAGE_TILING_LINEAR,
			VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
			texture,
			{ THSVS_ACCESS_TRANSFER_READ, THSVS_ACCESS_NONE },
			THSVS_IMAGE_LAYOUT_OPTIMAL
		);

		//
		setImageLayout2(
			currentContext.idx,
			&cubemapTextureTypeRef,
			{ THSVS_ACCESS_HOST_PREINITIALIZED, THSVS_ACCESS_NONE },
			{ THSVS_ACCESS_TRANSFER_WRITE, THSVS_ACCESS_NONE },
			THSVS_IMAGE_LAYOUT_OPTIMAL,
			THSVS_IMAGE_LAYOUT_OPTIMAL,
			true,
			0,
			1,
			baseArrayLayer,
			1
		);

		//
		VkImageCopy copyRegion = {
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
				.baseArrayLayer = baseArrayLayer,
				.layerCount = 1
			},
			.dstOffset = {
				.x = 0,
				.y = 0,
				.z = 0
			},
			.extent = {
				.width = cubemapTextureTypeRef.width,
				.height = cubemapTextureTypeRef.height,
				.depth = 1
			}
		};

		//
		prepareSetupCommandBuffer(currentContext.idx);
		vkCmdCopyImage(
			currentContext.setupCommandInUse,
			staging_texture.image,
			VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
			cubemapTextureTypeRef.image,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			1,
			&copyRegion
		);
		//
		finishSetupCommandBuffer(currentContext.idx);

		// mark for deletion
		deleteMutex.lock();
		deleteImages.push_back(
			{
				.image = staging_texture.image,
				.allocation = staging_texture.allocation,
				.imageView = VK_NULL_HANDLE,
				.sampler = VK_NULL_HANDLE
			}
		);
		deleteMutex.unlock();
	} else
	if ((textureFormatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) {
		// TODO: not sure if I should ever support this
	}

	//
	AtomicOperations::increment(statistics.textureUploads);
}

void VKRenderer::resizeDepthBufferTexture(int32_t textureId, int32_t width, int32_t height)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + to_string(textureId) + " / " + to_string(width) + "x" + to_string(height));

	// end render passes
	for (auto i = 0; i < Engine::getThreadCount(); i++) {
		endRenderPass(i);
	}

	//
	auto textureIt = textures.find(textureId);
	if (textureIt == textures.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): texture not found: " + to_string(textureId));
		return;
	}

	//
	removeTextureFromDescriptorCaches(textureId);

	//
	auto& texture = *textureIt->second;
	// TODO: Cube maps
	if (texture.width == width && texture.height == height) return;
	createDepthBufferTexture(textureId, width, height, ID_NONE, ID_NONE);
	if (texture.frameBufferObjectId != ID_NONE) createFramebufferObject(texture.frameBufferObjectId);
}

void VKRenderer::resizeColorBufferTexture(int32_t textureId, int32_t width, int32_t height)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + to_string(textureId) + " / " + to_string(width) + "x" + to_string(height));

	// end render passes
	for (auto i = 0; i < Engine::getThreadCount(); i++) {
		endRenderPass(i);
	}

	//
	auto textureIt = textures.find(textureId);
	if (textureIt == textures.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): texture not found: " + to_string(textureId));
		return;
	}

	//
	removeTextureFromDescriptorCaches(textureId);

	//
	auto& texture = *textureIt->second;
	// TODO: Cube maps
	if (texture.width == width && texture.height == height) return;
	createBufferTexture(textureId, width, height, ID_NONE, ID_NONE, format);
	if (texture.frameBufferObjectId != ID_NONE) createFramebufferObject(texture.frameBufferObjectId);
}

void VKRenderer::resizeGBufferGeometryTexture(int32_t textureId, int32_t width, int32_t height) {
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + to_string(textureId) + " / " + to_string(width) + "x" + to_string(height));

	// end render passes
	for (auto i = 0; i < Engine::getThreadCount(); i++) {
		endRenderPass(i);
	}

	//
	auto textureIt = textures.find(textureId);
	if (textureIt == textures.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): texture not found: " + to_string(textureId));
		return;
	}

	//
	removeTextureFromDescriptorCaches(textureId);

	//
	auto& texture = *textureIt->second;
	// TODO: Cube maps
	if (texture.width == width && texture.height == height) return;
	createBufferTexture(textureId, width, height, ID_NONE, ID_NONE, VK_FORMAT_R16G16B16A16_SFLOAT);
	if (texture.frameBufferObjectId != ID_NONE) createFramebufferObject(texture.frameBufferObjectId);
}

void VKRenderer::resizeGBufferColorTexture(int32_t textureId, int32_t width, int32_t height) {
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + to_string(textureId) + " / " + to_string(width) + "x" + to_string(height));

	// end render passes
	for (auto i = 0; i < Engine::getThreadCount(); i++) {
		endRenderPass(i);
	}

	//
	auto textureIt = textures.find(textureId);
	if (textureIt == textures.end()) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): texture not found: " + to_string(textureId));
		return;
	}

	//
	removeTextureFromDescriptorCaches(textureId);

	//
	auto& texture = *textureIt->second;
	// TODO: Cube maps
	if (texture.width == width && texture.height == height) return;
	createBufferTexture(textureId, width, height, ID_NONE, ID_NONE, format);
	if (texture.frameBufferObjectId != ID_NONE) createFramebufferObject(texture.frameBufferObjectId);
}

void VKRenderer::bindCubeMapTexture(void* context, int32_t textureId) {
	bindTexture(context, textureId);
}

void VKRenderer::bindTexture(void* context, int32_t textureId)
{
	// have our context typed
	auto& currentContext = *static_cast<context_type*>(context);
	auto& boundTexture = currentContext.boundTextures[currentContext.activeTextureUnit];

	//
	boundTexture.id = ID_NONE;
	boundTexture.sampler = VK_NULL_HANDLE;
	boundTexture.view = VK_NULL_HANDLE;
	boundTexture.layout = VK_IMAGE_LAYOUT_UNDEFINED;

	// textures
	auto textureObjectPtr = textureId != ID_NONE?getTextureInternal(currentContext.idx, textureId):nullptr;
	if (textureId != ID_NONE) {
		if (textureObjectPtr == nullptr) {
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): texture not found: " + to_string(textureId));
			return;
		}
	}

	//
	if (textureObjectPtr != nullptr) {
		auto& textureObject = *textureObjectPtr;
		boundTexture.sampler = textureObject.sampler;
		boundTexture.view = textureObject.view;
		boundTexture.layout = textureObject.vkLayout;
	}

	//
	boundTexture.id = textureId;

	// done
	onBindTexture(context, textureId);
}

void VKRenderer::disposeTexture(int32_t textureId)
{
	// mark for deletion
	disposeMutex.lock();
	disposeTextures.push_back(textureId);
	disposeMutex.unlock();
}

void VKRenderer::createFramebufferObject(int32_t frameBufferId) {
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + to_string(frameBufferId));
	auto frameBuffer = frameBufferId < 1 || frameBufferId >= framebuffers.size()?nullptr:framebuffers[frameBufferId];
	if (frameBuffer == nullptr) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): frame buffer not found: " + to_string(frameBufferId));
		return;
	}
	auto& frameBufferStruct = *frameBuffer;

	// color buffer
	if (frameBuffer->type == framebuffer_object_type::TYPE_COLORBUFFER) {
		texture_type* depthBufferTexture = nullptr;
		texture_type* colorBufferTexture = nullptr;

		auto depthBufferTextureIt = textures.find(frameBufferStruct.depthTextureId);
		if (depthBufferTextureIt == textures.end()) {
			if (frameBufferStruct.depthTextureId != ID_NONE) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): color buffer: depth buffer texture not found: " + to_string(frameBufferStruct.depthTextureId));
		} else {
			depthBufferTexture = depthBufferTextureIt->second;
		}
		auto colorBufferTextureIt = textures.find(frameBufferStruct.colorTextureId);
		if (colorBufferTextureIt == textures.end()) {
			if (frameBufferStruct.colorTextureId != ID_NONE) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): color buffer: color buffer texture not found: " + to_string(frameBufferStruct.colorTextureId));
		} else {
			colorBufferTexture = colorBufferTextureIt->second;
		}

		//
		if (depthBufferTexture != nullptr) depthBufferTexture->frameBufferObjectId = frameBufferStruct.id;
		if (colorBufferTexture != nullptr) colorBufferTexture->frameBufferObjectId = frameBufferStruct.id;

		//
		if (depthBufferTexture != nullptr && colorBufferTexture != nullptr &&
			(depthBufferTexture->width != colorBufferTexture->width ||
			depthBufferTexture->height != colorBufferTexture->height)) {
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): color buffer: attachments with different dimension found: Not creating!");
			return;
		}

		//
		VkResult err;

		//
		{
			if (frameBufferStruct.renderPass != VK_NULL_HANDLE) vkDestroyRenderPass(device, frameBufferStruct.renderPass, nullptr);

			auto attachmentIdx = 0;
			array<VkAttachmentDescription, 2> attachments;
			if (colorBufferTexture != nullptr) {
				attachments[attachmentIdx++] = {
					.flags = 0,
					.format = colorBufferTexture->format,
					.samples = VK_SAMPLE_COUNT_1_BIT,
					.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
					.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
					.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
					.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
					.initialLayout = colorBufferTexture->vkLayout == VK_IMAGE_LAYOUT_GENERAL?VK_IMAGE_LAYOUT_GENERAL:VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
					.finalLayout = colorBufferTexture->vkLayout == VK_IMAGE_LAYOUT_GENERAL?VK_IMAGE_LAYOUT_GENERAL:VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
				};
			}
			if (depthBufferTexture != nullptr) {
				attachments[attachmentIdx++] = {
					.flags = 0,
					.format = depthBufferTexture->format,
					.samples = VK_SAMPLE_COUNT_1_BIT,
					.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
					.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
					.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
					.stencilStoreOp = VK_ATTACHMENT_STORE_OP_STORE,
					.initialLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
					.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
				};
			}
			const VkAttachmentReference colorReference = {
				.attachment = 0,
				.layout = colorBufferTexture != nullptr?(colorBufferTexture->vkLayout == VK_IMAGE_LAYOUT_GENERAL?VK_IMAGE_LAYOUT_GENERAL:VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL):VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
			};
			const VkAttachmentReference depthReference = {
				.attachment = static_cast<uint32_t>(colorBufferTexture != nullptr?1:0),
				.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
			};
			const VkSubpassDescription subpassDescription = {
				.flags = 0,
				.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
				.inputAttachmentCount = 0,
				.pInputAttachments = nullptr,
				.colorAttachmentCount = static_cast<uint32_t>(colorBufferTexture != nullptr?1:0),
				.pColorAttachments = colorBufferTexture != nullptr?&colorReference:nullptr,
				.pResolveAttachments = nullptr,
				.pDepthStencilAttachment = depthBufferTexture != nullptr?&depthReference:nullptr,
				.preserveAttachmentCount = 0,
				.pPreserveAttachments = nullptr
			};
			const VkRenderPassCreateInfo renderPasseCreateInfo = {
				.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0,
				.attachmentCount = static_cast<uint32_t>(attachmentIdx),
				.pAttachments = attachments.data(),
				.subpassCount = 1,
				.pSubpasses = &subpassDescription,
				.dependencyCount = 0,
				.pDependencies = nullptr
			};
			err = vkCreateRenderPass(device, &renderPasseCreateInfo, nullptr, &frameBufferStruct.renderPass);
			assert(!err);
		}

		//
		{
			if (frameBufferStruct.frameBuffer != VK_NULL_HANDLE) vkDestroyFramebuffer(device, frameBufferStruct.frameBuffer, nullptr);
			auto attachmentIdx = 0;
			array<VkImageView,  2> attachments;
			if (colorBufferTexture != nullptr) attachments[attachmentIdx++] = colorBufferTexture->view;
			if (depthBufferTexture != nullptr) attachments[attachmentIdx++] = depthBufferTexture->view;
			const VkFramebufferCreateInfo fb_info = {
				.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0,
				.renderPass = frameBufferStruct.renderPass,
				.attachmentCount = static_cast<uint32_t>(attachmentIdx),
				.pAttachments = attachments.data(),
				.width = colorBufferTexture != nullptr?colorBufferTexture->width:depthBufferTexture->width,
				.height = colorBufferTexture != nullptr?colorBufferTexture->height:depthBufferTexture->height,
				.layers = 1
			};
			err = vkCreateFramebuffer(device, &fb_info, nullptr, &frameBufferStruct.frameBuffer);
			assert(!err);
		}
	} else
	if (frameBuffer->type == framebuffer_object_type::TYPE_GEOMETRYBUFFER) {
		auto depthBufferTexture = textures.find(frameBufferStruct.depthTextureId)->second;
		auto geometryBufferTexture1 = textures.find(frameBufferStruct.gbufferGeometryBufferTextureId1)->second;
		auto geometryBufferTexture2 = textures.find(frameBufferStruct.gbufferGeometryBufferTextureId2)->second;
		auto geometryBufferTexture3 = textures.find(frameBufferStruct.gbufferGeometryBufferTextureId3)->second;
		auto colorBufferTexture1 = textures.find(frameBufferStruct.gbufferColorBufferTextureId1)->second;
		auto colorBufferTexture2 = textures.find(frameBufferStruct.gbufferColorBufferTextureId2)->second;
		auto colorBufferTexture3 = textures.find(frameBufferStruct.gbufferColorBufferTextureId3)->second;
		auto colorBufferTexture4 = textures.find(frameBufferStruct.gbufferColorBufferTextureId4)->second;
		auto colorBufferTexture5 = textures.find(frameBufferStruct.gbufferColorBufferTextureId5)->second;

		//
		depthBufferTexture->frameBufferObjectId = frameBufferStruct.id;
		geometryBufferTexture1->frameBufferObjectId = frameBufferStruct.id;
		geometryBufferTexture2->frameBufferObjectId = frameBufferStruct.id;
		geometryBufferTexture3->frameBufferObjectId = frameBufferStruct.id;
		colorBufferTexture1->frameBufferObjectId = frameBufferStruct.id;
		colorBufferTexture2->frameBufferObjectId = frameBufferStruct.id;
		colorBufferTexture3->frameBufferObjectId = frameBufferStruct.id;
		colorBufferTexture4->frameBufferObjectId = frameBufferStruct.id;
		colorBufferTexture5->frameBufferObjectId = frameBufferStruct.id;

		//
		if (depthBufferTexture->width == 0 || depthBufferTexture->height == 0 ||
			depthBufferTexture->width != geometryBufferTexture1->width || depthBufferTexture->height != geometryBufferTexture1->height ||
			depthBufferTexture->width != geometryBufferTexture2->width || depthBufferTexture->height != geometryBufferTexture2->height ||
			depthBufferTexture->width != geometryBufferTexture3->width || depthBufferTexture->height != geometryBufferTexture3->height ||
			depthBufferTexture->width != colorBufferTexture1->width || depthBufferTexture->height != colorBufferTexture1->height ||
			depthBufferTexture->width != colorBufferTexture2->width || depthBufferTexture->height != colorBufferTexture2->height ||
			depthBufferTexture->width != colorBufferTexture3->width || depthBufferTexture->height != colorBufferTexture3->height ||
			depthBufferTexture->width != colorBufferTexture4->width || depthBufferTexture->height != colorBufferTexture4->height ||
			depthBufferTexture->width != colorBufferTexture5->width || depthBufferTexture->height != colorBufferTexture5->height) {
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): geometry buffer: attachments with different dimension found: Not creating!");
			return;
		}

		//
		array<texture_type*, 8> colorBufferTextures = {
			geometryBufferTexture1,
			geometryBufferTexture2,
			geometryBufferTexture3,
			colorBufferTexture1,
			colorBufferTexture2,
			colorBufferTexture3,
			colorBufferTexture4,
			colorBufferTexture5
		};

		//
		VkResult err;

		//
		{
			if (frameBufferStruct.renderPass != VK_NULL_HANDLE) vkDestroyRenderPass(device, frameBufferStruct.renderPass, nullptr);

			//
			auto attachmentIdx = 0;
			array<VkAttachmentDescription, 9> attachments;
			for (auto colorBufferTexture: colorBufferTextures) {
				attachments[attachmentIdx++] = {
					.flags = 0,
					.format = colorBufferTexture->format,
					.samples = VK_SAMPLE_COUNT_1_BIT,
					.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
					.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
					.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
					.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
					.initialLayout = colorBufferTexture->vkLayout == VK_IMAGE_LAYOUT_GENERAL?VK_IMAGE_LAYOUT_GENERAL:VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
					.finalLayout = colorBufferTexture->vkLayout == VK_IMAGE_LAYOUT_GENERAL?VK_IMAGE_LAYOUT_GENERAL:VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
				};
			}
			attachments[attachmentIdx++] = {
				.flags = 0,
				.format = depthBufferTexture->format,
				.samples = VK_SAMPLE_COUNT_1_BIT,
				.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
				.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
				.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
				.stencilStoreOp = VK_ATTACHMENT_STORE_OP_STORE,
				.initialLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
				.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
			};
			array<VkAttachmentReference, 8> colorReferences;
			{
				auto i = 0;
				for (auto colorBufferTexture: colorBufferTextures) {
					colorReferences[i] = {
						.attachment = static_cast<uint32_t>(i),
						.layout = colorBufferTexture->vkLayout == VK_IMAGE_LAYOUT_GENERAL?VK_IMAGE_LAYOUT_GENERAL:VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
					};
					i++;
				}
			}
			const VkAttachmentReference depthReference = {
				.attachment = 8,
				.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
			};
			const VkSubpassDescription subpassDescription = {
				.flags = 0,
				.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
				.inputAttachmentCount = 0,
				.pInputAttachments = nullptr,
				.colorAttachmentCount = 8,
				.pColorAttachments = colorReferences.data(),
				.pResolveAttachments = nullptr,
				.pDepthStencilAttachment = &depthReference,
				.preserveAttachmentCount = 0,
				.pPreserveAttachments = nullptr
			};
			const VkRenderPassCreateInfo renderPassCreateInfo = {
				.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0,
				.attachmentCount = static_cast<uint32_t>(attachmentIdx),
				.pAttachments = attachments.data(),
				.subpassCount = 1,
				.pSubpasses = &subpassDescription,
				.dependencyCount = 0,
				.pDependencies = nullptr
			};
			err = vkCreateRenderPass(device, &renderPassCreateInfo, nullptr, &frameBufferStruct.renderPass);
			assert(!err);
		}

		//
		{
			if (frameBufferStruct.frameBuffer != VK_NULL_HANDLE) vkDestroyFramebuffer(device, frameBufferStruct.frameBuffer, nullptr);
			auto attachmentIdx = 0;
			array<VkImageView,  9> attachments;
			for (auto colorBufferTexture: colorBufferTextures) {
				attachments[attachmentIdx++] = colorBufferTexture->view;
			}
			attachments[attachmentIdx++] = depthBufferTexture->view;
			const VkFramebufferCreateInfo frameBufferCreateInfo = {
				.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0,
				.renderPass = frameBufferStruct.renderPass,
				.attachmentCount = static_cast<uint32_t>(attachmentIdx),
				.pAttachments = attachments.data(),
				.width = depthBufferTexture->width,
				.height = depthBufferTexture->height,
				.layers = 1
			};
			err = vkCreateFramebuffer(device, &frameBufferCreateInfo, nullptr, &frameBufferStruct.frameBuffer);
			assert(!err);
		}
	}
}

int32_t VKRenderer::createFramebufferObject(int32_t depthBufferTextureId, int32_t colorBufferTextureId, int32_t cubeMapTextureId, int32_t cubeMapTextureIndex)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + to_string(depthBufferTextureId) + ", " + to_string(colorBufferTextureId));

	// try to reuse a frame buffer id
	auto reuseIndex = -1;
	for (auto i = 1; i < framebuffers.size(); i++) {
		if (framebuffers[i] == nullptr) {
			reuseIndex = i;
			break;
		}
	}

	//
	auto frameBufferPtr = new framebuffer_object_type();
	auto& frameBuffer = *frameBufferPtr;
	frameBuffer.id = reuseIndex != -1?reuseIndex:framebuffers.size();
	frameBuffer.type = framebuffer_object_type::TYPE_COLORBUFFER;
	frameBuffer.depthTextureId = depthBufferTextureId;
	frameBuffer.colorTextureId = colorBufferTextureId;
	frameBuffer.cubemapTextureId = cubeMapTextureId;
	frameBuffer.cubemapTextureIndex = cubeMapTextureIndex;

	//
	if (reuseIndex != -1) {
		framebuffers[reuseIndex] = frameBufferPtr;
	} else {
		framebuffers.push_back(frameBufferPtr);
	}

	//
	createFramebufferObject(frameBuffer.id);
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): new color frame buffer: " + to_string(frameBuffer.id));
	return frameBuffer.id;
}

int32_t VKRenderer::createGeometryBufferObject(
	int32_t depthBufferTextureId,
	int32_t geometryBufferTextureId1,
	int32_t geometryBufferTextureId2,
	int32_t geometryBufferTextureId3,
	int32_t colorBufferTextureId1,
	int32_t colorBufferTextureId2,
	int32_t colorBufferTextureId3,
	int32_t colorBufferTextureId4,
	int32_t colorBufferTextureId5
) {
	if (VERBOSE == true) {
		Console::println(
			"VKRenderer::" + string(__FUNCTION__) + "(): " +
			to_string(depthBufferTextureId) + ", " +
			to_string(geometryBufferTextureId1) + ", " +
			to_string(geometryBufferTextureId2) + ", " +
			to_string(geometryBufferTextureId3) + ", " +
			to_string(colorBufferTextureId1) + ", " +
			to_string(colorBufferTextureId2) + ", " +
			to_string(colorBufferTextureId3) + ", " +
			to_string(colorBufferTextureId4) + ", " +
			to_string(colorBufferTextureId5)
		);
	}

	// try to reuse a frame buffer id
	auto reuseIndex = -1;
	for (auto i = 1; i < framebuffers.size(); i++) {
		if (framebuffers[i] == nullptr) {
			reuseIndex = i;
			break;
		}
	}

	//
	auto frameBufferPtr = new framebuffer_object_type();
	auto& frameBuffer = *frameBufferPtr;
	frameBuffer.id = reuseIndex != -1?reuseIndex:framebuffers.size();
	frameBuffer.type = framebuffer_object_type::TYPE_GEOMETRYBUFFER;
	frameBuffer.depthTextureId = depthBufferTextureId;
	frameBuffer.gbufferGeometryBufferTextureId1 = geometryBufferTextureId1;
	frameBuffer.gbufferGeometryBufferTextureId2 = geometryBufferTextureId2;
	frameBuffer.gbufferGeometryBufferTextureId3 = geometryBufferTextureId3;
	frameBuffer.gbufferColorBufferTextureId1 = colorBufferTextureId1;
	frameBuffer.gbufferColorBufferTextureId2 = colorBufferTextureId2;
	frameBuffer.gbufferColorBufferTextureId3 = colorBufferTextureId3;
	frameBuffer.gbufferColorBufferTextureId4 = colorBufferTextureId4;
	frameBuffer.gbufferColorBufferTextureId5 = colorBufferTextureId5;

	//
	if (reuseIndex != -1) {
		framebuffers[reuseIndex] = frameBufferPtr;
	} else {
		framebuffers.push_back(frameBufferPtr);
	}

	//
	createFramebufferObject(frameBuffer.id);
	Console::println("VKRenderer::" + string(__FUNCTION__) + "(): new geometry frame buffer: " + to_string(frameBuffer.id));
	return frameBuffer.id;
}

void VKRenderer::bindFrameBuffer(int32_t frameBufferId)
{
	//
	if (frameBufferId == boundFrameBuffer) return;

	// if unsetting program flush command buffers
	endDrawCommandsAllContexts();

	//
	if (boundFrameBuffer != ID_NONE) {
		auto frameBuffer = boundFrameBuffer < 0 || boundFrameBuffer >= framebuffers.size()?nullptr:framebuffers[boundFrameBuffer];
		if (frameBuffer == nullptr) {
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): framebuffer not found: " + to_string(boundFrameBuffer));
		} else {
			if (frameBuffer->type == framebuffer_object_type::TYPE_COLORBUFFER) {
				auto depthBufferTextureId = frameBuffer->depthTextureId;
				auto colorBufferTextureId = frameBuffer->colorTextureId;
				if (depthBufferTextureId != ID_NONE) {
					auto& depthBufferTexture = *textures[depthBufferTextureId];
					setImageLayout(
						0,
						&depthBufferTexture,
						{ THSVS_ACCESS_FRAGMENT_SHADER_READ_SAMPLED_IMAGE_OR_UNIFORM_TEXEL_BUFFER, THSVS_ACCESS_NONE },
						THSVS_IMAGE_LAYOUT_OPTIMAL,
						false,
						0,
						1,
						false
					);
				}
				if (colorBufferTextureId != ID_NONE) {
					auto& colorBufferTexture = *textures[colorBufferTextureId];
					setImageLayout(
						0,
						&colorBufferTexture,
						{ THSVS_ACCESS_FRAGMENT_SHADER_READ_SAMPLED_IMAGE_OR_UNIFORM_TEXEL_BUFFER, THSVS_ACCESS_NONE },
						THSVS_IMAGE_LAYOUT_OPTIMAL,
						false,
						0,
						1,
						false
					);
				}
				if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + to_string(frameBufferId) + ": color buffer: unbinding: " + to_string(colorBufferTextureId) + " / " + to_string(depthBufferTextureId));
			} else
			if (frameBuffer->type == framebuffer_object_type::TYPE_GEOMETRYBUFFER) {
				auto depthBufferTextureId = frameBuffer->depthTextureId;
				auto colorBufferTextureId1 = frameBuffer->gbufferColorBufferTextureId1;
				auto colorBufferTextureId2 = frameBuffer->gbufferColorBufferTextureId2;
				auto colorBufferTextureId3 = frameBuffer->gbufferColorBufferTextureId3;
				auto colorBufferTextureId4 = frameBuffer->gbufferColorBufferTextureId4;
				auto colorBufferTextureId5 = frameBuffer->gbufferColorBufferTextureId5;
				setImageLayout(
					0,
					textures[frameBuffer->depthTextureId],
					{ THSVS_ACCESS_FRAGMENT_SHADER_READ_SAMPLED_IMAGE_OR_UNIFORM_TEXEL_BUFFER, THSVS_ACCESS_NONE },
					THSVS_IMAGE_LAYOUT_OPTIMAL,
					false,
					0,
					1,
					false
				);
				array<texture_type*, 8> colorBufferTextures = {
					textures[frameBuffer->gbufferGeometryBufferTextureId1],
					textures[frameBuffer->gbufferGeometryBufferTextureId2],
					textures[frameBuffer->gbufferGeometryBufferTextureId3],
					textures[frameBuffer->gbufferColorBufferTextureId1],
					textures[frameBuffer->gbufferColorBufferTextureId2],
					textures[frameBuffer->gbufferColorBufferTextureId3],
					textures[frameBuffer->gbufferColorBufferTextureId4],
					textures[frameBuffer->gbufferColorBufferTextureId5]
				};
				for (auto colorBufferTexture: colorBufferTextures) {
					setImageLayout(
						0,
						colorBufferTexture,
						{ THSVS_ACCESS_FRAGMENT_SHADER_READ_SAMPLED_IMAGE_OR_UNIFORM_TEXEL_BUFFER, THSVS_ACCESS_NONE },
						THSVS_IMAGE_LAYOUT_OPTIMAL,
						false,
						0,
						1,
						false
					);
				}
				if (VERBOSE == true) Console::println(
					"VKRenderer::" + string(__FUNCTION__) + "(): " +
					to_string(frameBufferId) +
					": geometry buffer: unbinding: " +
					to_string(depthBufferTextureId) + ", " +
					to_string(colorBufferTextures[0]->id) + ", " +
					to_string(colorBufferTextures[1]->id) + ", " +
					to_string(colorBufferTextures[2]->id) + ", " +
					to_string(colorBufferTextures[3]->id) + ", " +
					to_string(colorBufferTextures[4]->id) + ", " +
					to_string(colorBufferTextures[5]->id) + ", " +
					to_string(colorBufferTextures[6]->id) + ", " +
					to_string(colorBufferTextures[7]->id)
				);
			}
		}
	}

	//
	if (frameBufferId != ID_NONE) {
		auto frameBuffer = frameBufferId < 0 || frameBufferId >= framebuffers.size()?nullptr:framebuffers[frameBufferId];
		if (frameBuffer == nullptr) {
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): framebuffer not found: " + to_string(frameBufferId));
			frameBufferId = ID_NONE;
		}
	}

	//
	boundFrameBuffer = frameBufferId;
	if (boundFrameBuffer != ID_NONE) {
		auto frameBuffer = boundFrameBuffer < 0 || boundFrameBuffer >= framebuffers.size()?nullptr:framebuffers[boundFrameBuffer];
		if (frameBuffer == nullptr) {
			Console::println("VKRenderer::" + string(__FUNCTION__) + "(): framebuffer not found: " + to_string(boundFrameBuffer));
		} else {
			if (frameBuffer->type == framebuffer_object_type::TYPE_COLORBUFFER) {
				auto depthBufferTextureId = frameBuffer->depthTextureId;
				auto colorBufferTextureId = frameBuffer->colorTextureId;
				if (depthBufferTextureId != ID_NONE) {
					auto& depthBufferTexture = *textures[depthBufferTextureId];
					setImageLayout(
						0,
						&depthBufferTexture,
						{ THSVS_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ, THSVS_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE },
						THSVS_IMAGE_LAYOUT_OPTIMAL,
						false,
						0,
						1,
						false
					);
				}
				if (colorBufferTextureId != ID_NONE) {
					auto& colorBufferTexture = *textures[colorBufferTextureId];
					setImageLayout(
						0,
						&colorBufferTexture,
						{ THSVS_ACCESS_COLOR_ATTACHMENT_READ, THSVS_ACCESS_COLOR_ATTACHMENT_WRITE},
						THSVS_IMAGE_LAYOUT_OPTIMAL,
						false,
						0,
						1,
						false
					);
				}
				if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + to_string(frameBufferId) + ": binding: " + to_string(colorBufferTextureId) + " / " + to_string(depthBufferTextureId));
			} else
			if (frameBuffer->type == framebuffer_object_type::TYPE_GEOMETRYBUFFER) {
				auto depthBufferTextureId = frameBuffer->depthTextureId;
				auto colorBufferTextureId1 = frameBuffer->gbufferColorBufferTextureId1;
				auto colorBufferTextureId2 = frameBuffer->gbufferColorBufferTextureId2;
				auto colorBufferTextureId3 = frameBuffer->gbufferColorBufferTextureId3;
				auto colorBufferTextureId4 = frameBuffer->gbufferColorBufferTextureId4;
				auto colorBufferTextureId5 = frameBuffer->gbufferColorBufferTextureId5;
				setImageLayout(
					0,
					textures[frameBuffer->depthTextureId],
					{ THSVS_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ, THSVS_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE },
					THSVS_IMAGE_LAYOUT_OPTIMAL,
					false,
					0,
					1,
					false
				);
				array<texture_type*, 8> colorBufferTextures = {
					textures[frameBuffer->gbufferGeometryBufferTextureId1],
					textures[frameBuffer->gbufferGeometryBufferTextureId2],
					textures[frameBuffer->gbufferGeometryBufferTextureId3],
					textures[frameBuffer->gbufferColorBufferTextureId1],
					textures[frameBuffer->gbufferColorBufferTextureId2],
					textures[frameBuffer->gbufferColorBufferTextureId3],
					textures[frameBuffer->gbufferColorBufferTextureId4],
					textures[frameBuffer->gbufferColorBufferTextureId5]
				};
				for (auto colorBufferTexture: colorBufferTextures) {
					setImageLayout(
						0,
						colorBufferTexture,
						{ THSVS_ACCESS_COLOR_ATTACHMENT_READ, THSVS_ACCESS_COLOR_ATTACHMENT_WRITE},
						THSVS_IMAGE_LAYOUT_OPTIMAL,
						false,
						0,
						1,
						false
					);
				}
				if (VERBOSE == true) Console::println(
					"VKRenderer::" + string(__FUNCTION__) + "(): " +
					to_string(frameBufferId) +
					": geometry buffer: binding: " +
					to_string(depthBufferTextureId) + ", " +
					to_string(colorBufferTextures[0]->id) + ", " +
					to_string(colorBufferTextures[1]->id) + ", " +
					to_string(colorBufferTextures[2]->id) + ", " +
					to_string(colorBufferTextures[3]->id) + ", " +
					to_string(colorBufferTextures[4]->id) + ", " +
					to_string(colorBufferTextures[5]->id) + ", " +
					to_string(colorBufferTextures[6]->id) + ", " +
					to_string(colorBufferTextures[7]->id)
				);
			}
		}
	}

	//
	finishSetupCommandBuffer(0);

	//
	for (auto& context: contexts) context.boundTextures.fill(context_type::bound_texture());
}

void VKRenderer::disposeFrameBufferObject(int32_t frameBufferId)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "(): " + to_string(frameBufferId));
	auto frameBuffer = frameBufferId < 1 || frameBufferId >= framebuffers.size()?nullptr:framebuffers[frameBufferId];
	if (frameBuffer == nullptr) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): framebuffer not found: " + to_string(frameBufferId));
		return;
	}
	vkDestroyRenderPass(device, frameBuffer->renderPass, nullptr);
	vkDestroyFramebuffer(device, frameBuffer->frameBuffer, nullptr);
	delete frameBuffer;
	framebuffers[frameBufferId] = nullptr;
}

vector<int32_t> VKRenderer::createBufferObjects(int32_t bufferCount, bool useGPUMemory, bool shared)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	vector<int32_t> bufferIds;
	buffersRWlock.writeLock();
	if (bufferIdx - freeBufferIds.size() >= BUFFERS_MAX) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): coud not allocate buffer object, maximum is " + to_string(BUFFERS_MAX));
		buffersRWlock.unlock();
		return bufferIds;
	}
	for (auto i = 0; i < bufferCount; i++) {
		auto bufferPtr = new buffer_object_type();
		auto& buffer = *bufferPtr;
		auto reuseBufferId = -1;
		if (freeBufferIds.empty() == false) {
			auto reuseBufferIdIdx = freeBufferIds.size() - 1;
			reuseBufferId = freeBufferIds[reuseBufferIdIdx];
			freeBufferIds.erase(freeBufferIds.begin() + reuseBufferIdIdx);
		}
		buffer.id = reuseBufferId != -1?reuseBufferId:bufferIdx++;
		buffer.useGPUMemory = useGPUMemory;
		buffer.shared = shared;
		buffers[buffer.id] = bufferPtr;
		bufferIds.push_back(buffer.id);
	}
	buffersRWlock.unlock();
	return bufferIds;
}

inline VkBuffer VKRenderer::getBufferObjectInternal(buffer_object_type* bufferObject, uint32_t& size) {
	auto buffer = bufferObject->currentBuffer;
	if (buffer == nullptr) {
		size = 0;
		return VK_NULL_HANDLE;
	}
	//
	while (bufferObject->uploading == true) {
		// spin lock
	}
	//
	size = buffer->size;
	buffer->frameUsedLast = frame;
	return buffer->buf;
}

inline VkBuffer VKRenderer::getBufferObjectInternal(int contextIdx,  int32_t bufferObjectId, uint32_t& size) {
	auto buffer = getBufferObjectInternal(contextIdx, bufferObjectId);
	if (buffer == nullptr) {
		size = 0;
		return VK_NULL_HANDLE;
	}
	return getBufferObjectInternal(buffer, size);
}

inline VKRenderer::buffer_object_type* VKRenderer::getBufferObjectInternal(int contextIdx,  int32_t bufferObjectId) {
	// have our context typed
	if (contextIdx != -1) {
		auto& currentContext = contexts[contextIdx];
		auto buffer = currentContext.bufferVector[bufferObjectId];
		if (buffer != nullptr) {
			while (buffer->uploading == true) {
				// spin
			}
			return buffer;
		}

	}
	buffersRWlock.readLock();
	auto bufferIt = buffers.find(bufferObjectId);
	if (bufferIt == buffers.end()) {
		buffersRWlock.unlock();
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): buffer with id " + to_string(bufferObjectId) + " does not exist");
		return VK_NULL_HANDLE;
	}
	// we have a buffer, also place it in context
	auto buffer = bufferIt->second;
	if (contextIdx != -1) {
		auto& currentContext = contexts[contextIdx];
		currentContext.bufferVector[bufferObjectId] = buffer;
	}
	buffersRWlock.unlock();

	//
	while (buffer->uploading == true) {
		// spin lock
	}

	// done
	return buffer;
}

void VKRenderer::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VmaAllocation& allocation, VmaAllocationInfo& allocationInfo) {
	//
	VkResult err;

	const VkBufferCreateInfo bufferCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.size = static_cast<uint32_t>(size),
		.usage = usage,
		.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
		.queueFamilyIndexCount = 0,
		.pQueueFamilyIndices = nullptr
	};

	VmaAllocationCreateInfo allocationCreateInfo = {};
	allocationCreateInfo.flags = (properties & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) == VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT?VMA_ALLOCATION_CREATE_MAPPED_BIT:0;
	allocationCreateInfo.usage = VMA_MEMORY_USAGE_UNKNOWN;
	allocationCreateInfo.requiredFlags = properties;

	//
	err = vmaCreateBuffer(allocator, &bufferCreateInfo, &allocationCreateInfo, &buffer, &allocation, &allocationInfo);
	assert(!err);
}

inline void VKRenderer::uploadBufferObjectInternal(int contextIdx, int32_t bufferObjectId, int32_t size, const uint8_t* data, VkBufferUsageFlagBits usage) {
	if (size == 0) return;

	auto buffer = getBufferObjectInternal(contextIdx, bufferObjectId);
	if (buffer == nullptr) return;

	//
	if (buffer->shared == true) buffersRWlock.writeLock();

	// do the work
	uploadBufferObjectInternal(contextIdx, buffer, size, data, usage);

	//
	if (buffer->shared == true) buffersRWlock.unlock();
}

inline void VKRenderer::vmaMemCpy(VmaAllocation allocationDst, const uint8_t* src, uint32_t size, uint32_t offset) {
	vmaSpinlock.lock();
	VmaAllocationInfo dstAllocationInfo {};
	vmaGetAllocationInfo(allocator, allocationDst, &dstAllocationInfo);
	memcpy(static_cast<uint8_t*>(dstAllocationInfo.pMappedData) + offset, src, size);
	vmaSpinlock.unlock();
}

inline void VKRenderer::uploadBufferObjectInternal(int contextIdx, buffer_object_type* buffer, int32_t size, const uint8_t* data, VkBufferUsageFlagBits usage) {
	if (size == 0) return;

	//
	buffer->uploading = true;

	//
	VkResult err;

	// find a reusable buffer
	buffer_object_type::reusable_buffer* reusableBuffer = nullptr;
	for (auto& reusableBufferCandidate: buffer->buffers) {
		if (reusableBufferCandidate.size >= size &&
			reusableBufferCandidate.frameUsedLast < frame) {
			reusableBuffer = &reusableBufferCandidate;
			break;
		}
	}

	// nope, create one
	if (reusableBuffer == nullptr) {
		buffer->buffers.push_back(buffer_object_type::reusable_buffer());
		reusableBuffer = &buffer->buffers.back();
		buffer->bufferCount++;
	}

	// create buffer if not yet done
	if (reusableBuffer->size == 0) {
		VmaAllocationInfo allocationInfo = {};
		createBuffer(size, usage, buffer->useGPUMemory == true?VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT:VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, reusableBuffer->buf, reusableBuffer->allocation, allocationInfo);
		reusableBuffer->size = size;

		VkMemoryPropertyFlags memoryFlags;
		vmaGetMemoryTypeProperties(allocator, allocationInfo.memoryType, &memoryFlags);
		reusableBuffer->memoryMappable = (memoryFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) == VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
		if (reusableBuffer->memoryMappable == true) {
			void* mmData;
			vmaMapMemory(allocator, reusableBuffer->allocation, &mmData);
		}
	}

	// create buffer
	if (reusableBuffer->memoryMappable == true) {
		// copy to buffer
		vmaMemCpy(reusableBuffer->allocation, data, size);
	} else {
		prepareSetupCommandBuffer(contextIdx);

		void* stagingData;
		VkBuffer stagingBuffer;
		VmaAllocation stagingBufferAllocation;
		VkDeviceSize stagingBufferAllocationSize;
		VmaAllocationInfo stagingBufferAllocationInfo = {};
		createBuffer(size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, stagingBuffer, stagingBufferAllocation, stagingBufferAllocationInfo);
		// mark staging buffer for deletion when finishing frame
		deleteMutex.lock();
		deleteBuffers.push_back(
			{
				.buffer = stagingBuffer,
				.allocation = stagingBufferAllocation
			}
		);
		deleteMutex.unlock();

		void* mmData;
		vmaMapMemory(allocator, stagingBufferAllocation, &mmData);

		//
		vmaMemCpy(stagingBufferAllocation, data, size);

		// copy to GPU buffer
		VkBufferCopy copyRegion = {
			.srcOffset = 0,
			.dstOffset = 0,
			.size = static_cast<VkDeviceSize>(size)
		};
		vkCmdCopyBuffer(contexts[contextIdx].setupCommandInUse, stagingBuffer, reusableBuffer->buf, 1, &copyRegion);

		//
		finishSetupCommandBuffer(contextIdx);
	}

	// frame and current buffer
	reusableBuffer->frameUsedLast = frame;
	buffer->currentBuffer = reusableBuffer;

	// clean up
	vector<int> buffersToRemove;
	if (buffer->bufferCount > 1 && frame >= buffer->frameCleanedLast + 60) {
		int i = 0;
		vector<int32_t> buffersToRemove;
		for (auto& reusableBufferCandidate: buffer->buffers) {
			if (frame >= reusableBufferCandidate.frameUsedLast + 60) {
				vmaUnmapMemory(allocator, reusableBufferCandidate.allocation);
				vmaDestroyBuffer(allocator, reusableBufferCandidate.buf, reusableBufferCandidate.allocation);
				buffersToRemove.push_back(i - buffersToRemove.size());
			}
			i++;
		}
		for (auto bufferToRemove: buffersToRemove) {
			auto it = buffer->buffers.begin();
			for (auto i = 0; i < bufferToRemove; i++) ++it;
			buffer->buffers.erase(it);
			buffer->bufferCount--;
		}
		buffer->frameCleanedLast = frame;
		//
		AtomicOperations::increment(statistics.disposedBuffers, buffersToRemove.size());
	}

	//
	buffer->uploading = false;

	//
	AtomicOperations::increment(statistics.bufferUploads);
}

void VKRenderer::uploadBufferObject(void* context, int32_t bufferObjectId, int32_t size, FloatBuffer* data)
{
	auto& currentContext = *static_cast<context_type*>(context);
	uploadBufferObjectInternal(currentContext.idx, bufferObjectId, size, data->getBuffer(), (VkBufferUsageFlagBits)(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT));
}

void VKRenderer::uploadBufferObject(void* context, int32_t bufferObjectId, int32_t size, ShortBuffer* data)
{
	auto& currentContext = *static_cast<context_type*>(context);
	uploadBufferObjectInternal(currentContext.idx, bufferObjectId, size, data->getBuffer(), (VkBufferUsageFlagBits)(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT));
}

void VKRenderer::uploadBufferObject(void* context, int32_t bufferObjectId, int32_t size, IntBuffer* data)
{
	auto& currentContext = *static_cast<context_type*>(context);
	uploadBufferObjectInternal(currentContext.idx, bufferObjectId, size, data->getBuffer(), (VkBufferUsageFlagBits)(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT));
}

void VKRenderer::uploadIndicesBufferObject(void* context, int32_t bufferObjectId, int32_t size, ShortBuffer* data)
{
	auto& currentContext = *static_cast<context_type*>(context);
	uploadBufferObjectInternal(currentContext.idx, bufferObjectId, size, data->getBuffer(), (VkBufferUsageFlagBits)(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT));
}

void VKRenderer::uploadIndicesBufferObject(void* context, int32_t bufferObjectId, int32_t size, IntBuffer* data)
{
	auto& currentContext = *static_cast<context_type*>(context);
	uploadBufferObjectInternal(currentContext.idx, bufferObjectId, size, data->getBuffer(), (VkBufferUsageFlagBits)(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT));
}

inline VKRenderer::texture_type* VKRenderer::getTextureInternal(int contextIdx, int32_t textureId) {
	// return default texture if no texture was requested
	if (textureId == ID_NONE) {
		return whiteTextureSampler2dDefault;
	}

	// have our context typed
	if (contextIdx != -1) {
		auto& currentContext = contexts[contextIdx];
		auto texture = currentContext.textureVector[textureId];
		if (texture != nullptr) {
			if (texture->type == texture_type::TYPE_TEXTURE && texture->uploaded == false) return whiteTextureSampler2dDefault;
			return texture;
		}
	}
	texturesRWlock.readLock();
	auto textureIt = textures.find(textureId);
	if (textureIt == textures.end()) {
		texturesRWlock.unlock();
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): texture with id " + to_string(textureId) + " does not exist");
		return whiteTextureSampler2dDefault;
	}
	// we have a texture, also place it in context
	auto texture = textureIt->second;
	if (contextIdx != -1) {
		auto& currentContext = contexts[contextIdx];
		currentContext.textureVector[textureId] = texture;
	}
	texturesRWlock.unlock();
	return texture->type == texture_type::TYPE_TEXTURE && texture->uploaded == false?whiteTextureSampler2dDefault:texture;
}

inline VKRenderer::pipeline_type* VKRenderer::getPipelineInternal(int contextIdx, program_type* program, const uint32_t pipelineId) {
	// have our context typed
	if (contextIdx != -1) {
		auto& currentContext = contexts[contextIdx];
		auto pipelineIt = currentContext.pipelines.find(pipelineId);
		if (pipelineIt != currentContext.pipelines.end()) {
			return pipelineIt->second;
		}
	}
	pipelineRWlock.readLock();
	auto pipelineIt = program->pipelines.find(pipelineId);
	if (pipelineIt == program->pipelines.end()) {
		pipelineRWlock.unlock();
		return nullptr;
	}
	// we have a pipeline, also place it in context
	auto pipeline = pipelineIt->second;
	if (contextIdx != -1) {
		auto& currentContext = contexts[contextIdx];
		currentContext.pipelines[pipelineId] = pipeline;
	}
	pipelineRWlock.unlock();
	return pipeline;
}

void VKRenderer::bindIndicesBufferObject(void* context, int32_t bufferObjectId)
{
	auto& currentContext = (*static_cast<context_type*>(context));
	uint32_t bufferSize = 0;
	currentContext.boundIndicesBuffer =
		bufferObjectId == ID_NONE?
			VK_NULL_HANDLE:
			getBufferObjectInternal(currentContext.idx, bufferObjectId, bufferSize);
}

void VKRenderer::bindTextureCoordinatesBufferObject(void* context, int32_t bufferObjectId)
{
	auto& currentContext = (*static_cast<context_type*>(context));
	currentContext.boundBuffers[2] =
		bufferObjectId == ID_NONE?
			getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[2]):
			getBufferObjectInternal(currentContext.idx, bufferObjectId, currentContext.boundBufferSizes[2]);
	if (currentContext.boundBuffers[2] == VK_NULL_HANDLE) {
		currentContext.boundBuffers[2] = getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[2]);
	}
}

void VKRenderer::bindVerticesBufferObject(void* context, int32_t bufferObjectId)
{
	auto& currentContext = (*static_cast<context_type*>(context));
	currentContext.boundBuffers[0] =
		bufferObjectId == ID_NONE?
			getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[0]):
			getBufferObjectInternal(currentContext.idx, bufferObjectId, currentContext.boundBufferSizes[0]);
	if (currentContext.boundBuffers[0] == VK_NULL_HANDLE) {
		currentContext.boundBuffers[0] = getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[0]);
	}
}

void VKRenderer::bindNormalsBufferObject(void* context, int32_t bufferObjectId)
{
	auto& currentContext = (*static_cast<context_type*>(context));
	currentContext.boundBuffers[1] =
		bufferObjectId == ID_NONE?
			getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[1]):
			getBufferObjectInternal(currentContext.idx, bufferObjectId, currentContext.boundBufferSizes[1]);
	if (currentContext.boundBuffers[1] == VK_NULL_HANDLE) {
		currentContext.boundBuffers[1] = getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[1]);
	}
}

void VKRenderer::bindColorsBufferObject(void* context, int32_t bufferObjectId)
{
	auto& currentContext = (*static_cast<context_type*>(context));
	currentContext.boundBuffers[3] =
		bufferObjectId == ID_NONE?
			getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[3]):
			getBufferObjectInternal(currentContext.idx, bufferObjectId, currentContext.boundBufferSizes[3]);
	if (currentContext.boundBuffers[3] == VK_NULL_HANDLE) {
		currentContext.boundBuffers[3] = getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[3]);
	}
}

void VKRenderer::bindTangentsBufferObject(void* context, int32_t bufferObjectId)
{
	auto& currentContext = (*static_cast<context_type*>(context));
	currentContext.boundBuffers[4] =
		bufferObjectId == ID_NONE?
			getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[4]):
			getBufferObjectInternal(currentContext.idx, bufferObjectId, currentContext.boundBufferSizes[4]);
	if (currentContext.boundBuffers[4] == VK_NULL_HANDLE) {
		currentContext.boundBuffers[4] = getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[4]);
	}
}

void VKRenderer::bindBitangentsBufferObject(void* context, int32_t bufferObjectId)
{
	auto& currentContext = (*static_cast<context_type*>(context));
	currentContext.boundBuffers[5] =
		bufferObjectId == ID_NONE?
			getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[5]):
			getBufferObjectInternal(currentContext.idx, bufferObjectId, currentContext.boundBufferSizes[5]);
	if (currentContext.boundBuffers[5] == VK_NULL_HANDLE) {
		currentContext.boundBuffers[5] =	getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[5]);
	}
}

void VKRenderer::bindModelMatricesBufferObject(void* context, int32_t bufferObjectId)
{
	auto& currentContext = (*static_cast<context_type*>(context));
	currentContext.boundBuffers[6] =
		bufferObjectId == ID_NONE?
			getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[6]):
			getBufferObjectInternal(currentContext.idx, bufferObjectId, currentContext.boundBufferSizes[6]);
	if (currentContext.boundBuffers[6] == VK_NULL_HANDLE) {
		currentContext.boundBuffers[6] = getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[6]);
	}
}

void VKRenderer::bindEffectColorMulsBufferObject(void* context, int32_t bufferObjectId, int32_t divisor)
{
	auto& currentContext = (*static_cast<context_type*>(context));
	currentContext.boundBuffers[7] =
		bufferObjectId == ID_NONE?
			getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[7]):
			getBufferObjectInternal(currentContext.idx, bufferObjectId, currentContext.boundBufferSizes[7]);
	if (currentContext.boundBuffers[7] == VK_NULL_HANDLE) {
		currentContext.boundBuffers[7] = getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[7]);
	}
}

void VKRenderer::bindEffectColorAddsBufferObject(void* context, int32_t bufferObjectId, int32_t divisor)
{
	auto& currentContext = (*static_cast<context_type*>(context));
	currentContext.boundBuffers[8] =
		bufferObjectId == ID_NONE?
			getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[8]):
			getBufferObjectInternal(currentContext.idx, bufferObjectId, currentContext.boundBufferSizes[8]);
	if (currentContext.boundBuffers[8] == VK_NULL_HANDLE) {
		currentContext.boundBuffers[8] = getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[8]);
	}
}

void VKRenderer::bindOriginsBufferObject(void* context, int32_t bufferObjectId) {
	auto& currentContext = (*static_cast<context_type*>(context));
	currentContext.boundBuffers[9] =
		bufferObjectId == ID_NONE?
			getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[9]):
			getBufferObjectInternal(currentContext.idx, bufferObjectId, currentContext.boundBufferSizes[9]);
	if (currentContext.boundBuffers[9] == VK_NULL_HANDLE) {
		currentContext.boundBuffers[9] = getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[9]);
	}
}

void VKRenderer::bindTextureSpriteIndicesBufferObject(void* context, int32_t bufferObjectId) {
	auto& currentContext = (*static_cast<context_type*>(context));
	currentContext.boundBuffers[1] =
		bufferObjectId == ID_NONE?
			getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[1]):
			getBufferObjectInternal(currentContext.idx, bufferObjectId, currentContext.boundBufferSizes[1]);
	if (currentContext.boundBuffers[1] == VK_NULL_HANDLE) {
		currentContext.boundBuffers[1] = getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[1]);
	}
}

void VKRenderer::bindPointSizesBufferObject(void* context, int32_t bufferObjectId) {
	auto& currentContext = (*static_cast<context_type*>(context));
	currentContext.boundBuffers[5] =
		bufferObjectId == ID_NONE?
			getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[5]):
			getBufferObjectInternal(currentContext.idx, bufferObjectId, currentContext.boundBufferSizes[5]);
	if (currentContext.boundBuffers[5] == VK_NULL_HANDLE) {
		currentContext.boundBuffers[5] = getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[5]);
	}
}

void VKRenderer::bindSpriteSheetDimensionBufferObject(void* context, int32_t bufferObjectId) {
	auto& currentContext = (*static_cast<context_type*>(context));
	currentContext.boundBuffers[6] =
		bufferObjectId == ID_NONE?
			getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[6]):
			getBufferObjectInternal(currentContext.idx, bufferObjectId, currentContext.boundBufferSizes[6]);
	if (currentContext.boundBuffers[6] == VK_NULL_HANDLE) {
		currentContext.boundBuffers[6] = getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[6]);
	}
}

void VKRenderer::drawInstancedIndexedTrianglesFromBufferObjects(void* context, int32_t triangles, int32_t trianglesOffset, int32_t instances) {
	drawInstancedTrianglesFromBufferObjects(context, triangles, trianglesOffset, (*static_cast<context_type*>(context)).boundIndicesBuffer, instances);
}

inline void VKRenderer::drawInstancedTrianglesFromBufferObjects(void* context, int32_t triangles, int32_t trianglesOffset, VkBuffer indicesBuffer, int32_t instances)
{
	auto& currentContext = *static_cast<context_type*>(context);
	auto& programContext = currentContext.program->contexts[currentContext.idx];
	auto& programCommandBuffer = programContext.commandBuffers[currentContext.currentCommandBuffer];

	// check if desc1 left
	if (programCommandBuffer.descriptorSets1Idx == DESC_MAX_UNCACHED) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program.desc_idxs1[" + to_string(currentContext.idx) + "] == DESC_MAX: " + to_string(programCommandBuffer.descriptorSets1Idx));
		return;
	}
	// check if desc2 left
	if (programCommandBuffer.descriptorSets2IdxUncached == DESC_MAX_UNCACHED) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program.desc_idxs2[" + to_string(currentContext.idx) + "] == DESC_MAX: " + to_string(programCommandBuffer.descriptorSets2IdxUncached));
		return;
	}
	//
	auto descriptorSet1 = programCommandBuffer.descriptorSets1[programCommandBuffer.descriptorSets1Idx];
	auto descriptorSet2Uncached = programCommandBuffer.descriptorSets2Uncached[programCommandBuffer.descriptorSets2IdxUncached];

	// start draw command buffer, it not yet done
	beginDrawCommandBuffer(currentContext.idx);

	// start render pass
	startRenderPass(currentContext.idx);

	// pipeline
	setupObjectsRenderingPipeline(currentContext.idx, currentContext.program);

	//
	auto uboIdx = 0;
	SAMPLER_HASH_TYPE descriptorSet2CacheId = 0LL;
	#if defined(CPU_64BIT)
		array<int, 8> textureIds { ID_NONE, ID_NONE, ID_NONE, ID_NONE, ID_NONE , ID_NONE , ID_NONE , ID_NONE  };
	#else
		array<int, 4> textureIds { ID_NONE, ID_NONE, ID_NONE, ID_NONE };
	#endif
	// get texture set cache id
	auto samplers = -1;
	{
		auto shaderIdx = 0;
		auto samplerIdx = 0;
		for (auto shader: currentContext.program->shaders) {
			// sampler2D + samplerCube
			for (auto uniform: shader->samplerUniformList) {
				if (samplerIdx < SAMPLER_HASH_MAX) {
					if (uniform->textureUnit == -1) {
						textureIds[samplerIdx] = ID_NONE;
					} else {
						auto& boundTexture = currentContext.boundTextures[uniform->textureUnit];
						if (boundTexture.view == VK_NULL_HANDLE) {
							textureIds[samplerIdx] = ID_NONE;
						} else {
							textureIds[samplerIdx] = boundTexture.id;
							descriptorSet2CacheId+= (SAMPLER_HASH_TYPE)boundTexture.id << (SAMPLER_HASH_TYPE)(samplerIdx * 16);
						}
					}
				}
				samplerIdx++;
			}

			// uniform buffer
			if (shader->uboBindingIdx == -1) {
				shaderIdx++;
				continue;
			}

			//
			auto& uniformBuffer = shader->uniformBuffers[currentContext.idx];
			auto& src = uniformBuffer.buffers[uniformBuffer.bufferIdx];
			auto uboBuffer = src.buffer;
			uniformBuffer.bufferIdx = (uniformBuffer.bufferIdx + 1) % uniformBuffer.buffers.size();
			vmaMemCpy(src.allocation, currentContext.uniformBufferData[shaderIdx].data(), uniformBuffer.size);

			//
			currentContext.descriptorBufferInfos[shader->uboBindingIdx] = {
				.buffer = uboBuffer,
				.offset = 0,
				.range = shader->uboSize
			};

			//
			currentContext.descriptorWriteSets[shader->uboBindingIdx] = {
				.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
				.pNext = nullptr,
				.dstSet = descriptorSet1,
				.dstBinding = static_cast<uint32_t>(shader->uboBindingIdx),
				.dstArrayElement = 0,
				.descriptorCount = 1,
				.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
				.pImageInfo = nullptr,
				.pBufferInfo = &currentContext.descriptorBufferInfos[shader->uboBindingIdx],
				.pTexelBufferView = nullptr
			};

			//
			shaderIdx++;
			uboIdx++;
		}
		samplers = samplerIdx;
	}

	auto& descriptorSet2Cache = programContext.descriptorSets2Cache;
	auto descriptorSet2CacheIt = samplers > SAMPLER_HASH_MAX?descriptorSet2Cache.end():descriptorSet2Cache.find(descriptorSet2CacheId);
	auto descriptorSet2CacheHit = descriptorSet2CacheIt != descriptorSet2Cache.end();
	if (descriptorSet2CacheHit == false) {
		if (samplers <= SAMPLER_HASH_MAX) {
			auto descriptorSets2Idx = -1;
			if (programContext.freeDescriptorSets2Ids.empty() == false) {
				auto freeDescriptorSets2IdsIdx = programContext.freeDescriptorSets2Ids.size() - 1;
				descriptorSets2Idx = programContext.freeDescriptorSets2Ids[freeDescriptorSets2IdsIdx];
				programContext.freeDescriptorSets2Ids.erase(programContext.freeDescriptorSets2Ids.begin() + freeDescriptorSets2IdsIdx);
			} else {
				descriptorSets2Idx = programContext.descriptorSets2Idx++;
			}
			descriptorSet2Uncached = programContext.descriptorSets2[descriptorSets2Idx];
			descriptorSet2Cache[descriptorSet2CacheId] = descriptorSets2Idx;
			for (auto textureId: textureIds) programContext.descriptorSets2CacheTextureIds[textureId].insert(descriptorSet2CacheId);
		} else {
			programCommandBuffer.descriptorSets2IdxUncached++;
		}
		auto samplerIdx = 0;
		for (auto shader: currentContext.program->shaders) {
			// sampler2D + samplerCube
			for (auto uniform: shader->samplerUniformList) {
				if (uniform->textureUnit == -1) {
					switch(uniform->type) {
						case shader_type::uniform_type::TYPE_SAMPLER2D:
							currentContext.descriptorImageInfos[samplerIdx] = {
								.sampler = whiteTextureSampler2dDefault->sampler,
								.imageView = whiteTextureSampler2dDefault->view,
								.imageLayout = whiteTextureSampler2dDefault->vkLayout
							};
							break;
						case shader_type::uniform_type::TYPE_SAMPLERCUBE:
							currentContext.descriptorImageInfos[samplerIdx] = {
								.sampler = whiteTextureSamplerCubeDefault->sampler,
								.imageView = whiteTextureSamplerCubeDefault->view,
								.imageLayout = whiteTextureSamplerCubeDefault->vkLayout
							};
							break;
						default:
							Console::println("VKRenderer::" + string(__FUNCTION__) + "(): object command: unknown sampler: " + to_string(uniform->type));
							break;
					}
				} else {
					auto& boundTexture = currentContext.boundTextures[uniform->textureUnit];
					if (boundTexture.view == VK_NULL_HANDLE) {
						switch(uniform->type) {
							case shader_type::uniform_type::TYPE_SAMPLER2D:
								currentContext.descriptorImageInfos[samplerIdx] = {
									.sampler = whiteTextureSampler2dDefault->sampler,
									.imageView = whiteTextureSampler2dDefault->view,
									.imageLayout = whiteTextureSampler2dDefault->vkLayout
								};
								break;
							case shader_type::uniform_type::TYPE_SAMPLERCUBE:
								currentContext.descriptorImageInfos[samplerIdx] = {
									.sampler = whiteTextureSamplerCubeDefault->sampler,
									.imageView = whiteTextureSamplerCubeDefault->view,
									.imageLayout = whiteTextureSamplerCubeDefault->vkLayout
								};
								break;
							default:
								Console::println("VKRenderer::" + string(__FUNCTION__) + "(): object command: unknown sampler: " + to_string(uniform->type));
								break;
						}
					} else {
						currentContext.descriptorImageInfos[samplerIdx] = {
							.sampler = boundTexture.sampler,
							.imageView = boundTexture.view,
							.imageLayout = boundTexture.layout
						};
					}
				}
				currentContext.descriptorWriteSets[uniform->position] = {
					.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
					.pNext = nullptr,
					.dstSet = descriptorSet2Uncached,
					.dstBinding = static_cast<uint32_t>(uniform->position),
					.dstArrayElement = 0,
					.descriptorCount = 1,
					.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
					.pImageInfo = &currentContext.descriptorImageInfos[samplerIdx],
					.pBufferInfo = VK_NULL_HANDLE,
					.pTexelBufferView = VK_NULL_HANDLE
				};
				samplerIdx++;
			}
		}
	} else {
		descriptorSet2Uncached = programContext.descriptorSets2[descriptorSet2CacheIt->second];
	}

	//
	vkUpdateDescriptorSets(device, descriptorSet2CacheHit == true?uboIdx:currentContext.program->layoutBindings, currentContext.descriptorWriteSets.data(), 0, nullptr);

	// descriptor sets
	array<VkDescriptorSet, 2> descSets { descriptorSet1, descriptorSet2Uncached };

	// draw cmd
	auto& drawCommand = currentContext.commandBuffers[currentContext.currentCommandBuffer].drawCommand;
	vkCmdBindDescriptorSets(drawCommand, VK_PIPELINE_BIND_POINT_GRAPHICS, currentContext.program->pipelineLayout, 0, descSets.size(), descSets.data(), 0, nullptr);

	// index buffer
	if (indicesBuffer != VK_NULL_HANDLE) {
		vkCmdBindIndexBuffer(drawCommand, indicesBuffer, 0, VK_INDEX_TYPE_UINT32);
	}

	// buffers
	vkCmdBindVertexBuffers(drawCommand, 0, OBJECTS_VERTEX_BUFFER_COUNT, currentContext.boundBuffers.data(), currentContext.boundBufferOffsets.data());

	// draw
	if (indicesBuffer != VK_NULL_HANDLE) {
		vkCmdDrawIndexed(drawCommand, triangles * 3, instances, trianglesOffset * 3, 0, 0);
	} else {
		vkCmdDraw(drawCommand, triangles * 3, instances, trianglesOffset * 3, 0);
	}

	//
	programCommandBuffer.descriptorSets1Idx++;
	currentContext.commandCount++;

	//
	requestSubmitDrawBuffers(currentContext.idx);

	//
	AtomicOperations::increment(statistics.renderCalls);
	AtomicOperations::increment(statistics.instances, instances);
	AtomicOperations::increment(statistics.triangles, triangles * instances);
}

void VKRenderer::drawIndexedTrianglesFromBufferObjects(void* context, int32_t triangles, int32_t trianglesOffset)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");

	//
	drawInstancedIndexedTrianglesFromBufferObjects(context, triangles, trianglesOffset, 1);
}

inline void VKRenderer::endDrawCommandsAllContexts() {
	VkResult err;

	// end render passes
	for (auto i = 0; i < Engine::getThreadCount(); i++) {
		auto& context = contexts[i];
		endRenderPass(context.idx);
		auto currentBufferIdx = context.currentCommandBuffer;
		auto commandBuffer = endDrawCommandBuffer(context.idx, -1, true);
		if (commandBuffer != VK_NULL_HANDLE) {
			submitDrawCommandBuffers(1, &commandBuffer, context.commandBuffers[currentBufferIdx].drawFence, false, false);
		}
		unsetPipeline(context.idx);
    }
}

inline void VKRenderer::requestSubmitDrawBuffers(int contextIdx) {
	// have our context typed
	auto& currentContext = contexts[contextIdx];

	//
	auto commandsMax = COMMANDS_MAX_GRAPHICS;
	if (currentContext.commandCount >= commandsMax) {
		endRenderPass(currentContext.idx);
		auto currentBufferIdx = currentContext.currentCommandBuffer;
		auto commandBuffer = endDrawCommandBuffer(currentContext.idx, -1, true);
		if (commandBuffer != VK_NULL_HANDLE) submitDrawCommandBuffers(1, &commandBuffer, currentContext.commandBuffers[currentBufferIdx].drawFence, false, false);
		currentContext.commandCount = 0;
	}
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
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");

	// have our context typed
	auto& currentContext = *static_cast<context_type*>(context);
	auto& programContext = currentContext.program->contexts[currentContext.idx];
	auto& programCommandBuffer = programContext.commandBuffers[currentContext.currentCommandBuffer];

	// check if desc1 left
	if (programCommandBuffer.descriptorSets1Idx == DESC_MAX_UNCACHED) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program.desc_idxs1[" + to_string(currentContext.idx) + "] == DESC_MAX: " + to_string(programCommandBuffer.descriptorSets1Idx));
		return;
	}
	// check if desc2 left
	if (programCommandBuffer.descriptorSets2IdxUncached == DESC_MAX_UNCACHED) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program.desc_idxs2[" + to_string(currentContext.idx) + "] == DESC_MAX: " + to_string(programCommandBuffer.descriptorSets2IdxUncached));
		return;
	}
	//
	auto descriptorSet1 = programCommandBuffer.descriptorSets1[programCommandBuffer.descriptorSets1Idx];
	auto descriptorSet2 = programCommandBuffer.descriptorSets2Uncached[programCommandBuffer.descriptorSets2IdxUncached];

	// start draw command buffer, it not yet done
	beginDrawCommandBuffer(currentContext.idx);

	// render pass
	startRenderPass(currentContext.idx);

	// pipeline
	setupPointsRenderingPipeline(currentContext.idx, currentContext.program);

	// do points render command
	auto shaderIdx = 0;
	auto uboIdx = 0;
	auto samplerIdx = 0;
	for (auto shader: currentContext.program->shaders) {
		// sampler2D + samplerCube
		for (auto uniform: shader->samplerUniformList) {
			if (uniform->textureUnit == -1) {
				switch(uniform->type) {
					case shader_type::uniform_type::TYPE_SAMPLER2D:
						currentContext.descriptorImageInfos[samplerIdx] = {
							.sampler = whiteTextureSampler2dDefault->sampler,
							.imageView = whiteTextureSampler2dDefault->view,
							.imageLayout = whiteTextureSampler2dDefault->vkLayout
						};
						break;
					case shader_type::uniform_type::TYPE_SAMPLERCUBE:
						currentContext.descriptorImageInfos[samplerIdx] = {
							.sampler = whiteTextureSamplerCubeDefault->sampler,
							.imageView = whiteTextureSamplerCubeDefault->view,
							.imageLayout = whiteTextureSamplerCubeDefault->vkLayout
						};
						break;
					default:
						Console::println("VKRenderer::" + string(__FUNCTION__) + "(): object command: unknown sampler: " + to_string(uniform->type));
						break;
				}
			} else {
				auto& texture = currentContext.boundTextures[uniform->textureUnit];
				if (texture.view == VK_NULL_HANDLE) {
					switch(uniform->type) {
						case shader_type::uniform_type::TYPE_SAMPLER2D:
							currentContext.descriptorImageInfos[samplerIdx] = {
								.sampler = whiteTextureSampler2dDefault->sampler,
								.imageView = whiteTextureSampler2dDefault->view,
								.imageLayout = whiteTextureSampler2dDefault->vkLayout
							};
							break;
						case shader_type::uniform_type::TYPE_SAMPLERCUBE:
							currentContext.descriptorImageInfos[samplerIdx] = {
								.sampler = whiteTextureSamplerCubeDefault->sampler,
								.imageView = whiteTextureSamplerCubeDefault->view,
								.imageLayout = whiteTextureSamplerCubeDefault->vkLayout
							};
							break;
						default:
							Console::println("VKRenderer::" + string(__FUNCTION__) + "(): object command: unknown sampler: " + to_string(uniform->type));
							break;
					}
				} else {
					currentContext.descriptorImageInfos[samplerIdx] = {
						.sampler = texture.sampler,
						.imageView = texture.view,
						.imageLayout = texture.layout
					};
				}
			}
			currentContext.descriptorWriteSets[uniform->position] = {
				.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
				.pNext = nullptr,
				.dstSet = descriptorSet2,
				.dstBinding = static_cast<uint32_t>(uniform->position),
				.dstArrayElement = 0,
				.descriptorCount = 1,
				.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
				.pImageInfo = &currentContext.descriptorImageInfos[samplerIdx],
				.pBufferInfo = VK_NULL_HANDLE,
				.pTexelBufferView = VK_NULL_HANDLE
			};
			samplerIdx++;
		}

		// uniform buffer
		if (shader->uboBindingIdx == -1) {
			shaderIdx++;
			continue;
		}

		//
		auto& uniformBuffer = shader->uniformBuffers[currentContext.idx];
		auto& src = uniformBuffer.buffers[uniformBuffer.bufferIdx];
		auto uboBuffer = src.buffer;
		uniformBuffer.bufferIdx = (uniformBuffer.bufferIdx + 1) % uniformBuffer.buffers.size();
		vmaMemCpy(src.allocation, currentContext.uniformBufferData[shaderIdx].data(), uniformBuffer.size);

		//
		currentContext.descriptorBufferInfos[shader->uboBindingIdx] = {
			.buffer = uboBuffer,
			.offset = 0,
			.range = shader->uboSize
		};

		//
		currentContext.descriptorWriteSets[shader->uboBindingIdx] = {
			.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
			.pNext = nullptr,
			.dstSet = descriptorSet1,
			.dstBinding = static_cast<uint32_t>(shader->uboBindingIdx),
			.dstArrayElement = 0,
			.descriptorCount = 1,
			.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
			.pImageInfo = nullptr,
			.pBufferInfo = &currentContext.descriptorBufferInfos[shader->uboBindingIdx],
			.pTexelBufferView = nullptr
		};

		//
		shaderIdx++;
		uboIdx++;
	}

	//
	vkUpdateDescriptorSets(device, currentContext.program->layoutBindings, currentContext.descriptorWriteSets.data(), 0, nullptr);

	//
	auto& drawCommand = currentContext.commandBuffers[currentContext.currentCommandBuffer].drawCommand;
	array<VkDescriptorSet, 2> descriptorSets { descriptorSet1, descriptorSet2 };
	vkCmdBindDescriptorSets(drawCommand, VK_PIPELINE_BIND_POINT_GRAPHICS, currentContext.program->pipelineLayout, 0, descriptorSets.size(), descriptorSets.data(), 0, nullptr);
	vkCmdBindVertexBuffers(drawCommand, 0, POINTS_VERTEX_BUFFER_COUNT, currentContext.boundBuffers.data(), currentContext.boundBufferOffsets.data());
	vkCmdDraw(drawCommand, points, 1, pointsOffset, 0);

	//
	programCommandBuffer.descriptorSets1Idx++;
	programCommandBuffer.descriptorSets2IdxUncached++;
	currentContext.commandCount++;

	//
	requestSubmitDrawBuffers(currentContext.idx);

	//
	AtomicOperations::increment(statistics.renderCalls);
	AtomicOperations::increment(statistics.points, points);
}

void VKRenderer::setLineWidth(float lineWidth)
{
	this->lineWidth = lineWidth;
}

void VKRenderer::drawLinesFromBufferObjects(void* context, int32_t points, int32_t pointsOffset)
{
	if (VERBOSE == true) Console::println("VKRenderer::" + string(__FUNCTION__) + "()");

	// have our context typed
	auto& currentContext = *static_cast<context_type*>(context);
	auto& programCommandBuffer = currentContext.program->contexts[currentContext.idx].commandBuffers[currentContext.currentCommandBuffer];

	// check if desc1 left
	if (programCommandBuffer.descriptorSets1Idx == DESC_MAX_UNCACHED) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program.desc_idxs1[" + to_string(currentContext.idx) + "] == DESC_MAX: " + to_string(programCommandBuffer.descriptorSets1Idx));
		return;
	}
	// check if desc2 left
	if (programCommandBuffer.descriptorSets2IdxUncached == DESC_MAX_UNCACHED) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program.desc_idxs2[" + to_string(currentContext.idx) + "] == DESC_MAX: " + to_string(programCommandBuffer.descriptorSets2IdxUncached));
		return;
	}
	//
	auto descriptorSet1 = programCommandBuffer.descriptorSets1[programCommandBuffer.descriptorSets1Idx];
	auto descriptorSet2 = programCommandBuffer.descriptorSets2Uncached[programCommandBuffer.descriptorSets2IdxUncached];

	// start draw command buffer, it not yet done
	beginDrawCommandBuffer(currentContext.idx);

	// render pass
	startRenderPass(currentContext.idx);

	// lines
	setupLinesRenderingPipeline(currentContext.idx, currentContext.program);

	// do lines render command
	auto shaderIdx = 0;
	auto uboIdx = 0;
	auto samplerIdx = 0;
	for (auto shader: currentContext.program->shaders) {
		// sampler2D + samplerCube
		for (auto uniform: shader->samplerUniformList) {
			if (uniform->textureUnit == -1) {
				switch(uniform->type) {
					case shader_type::uniform_type::TYPE_SAMPLER2D:
						currentContext.descriptorImageInfos[samplerIdx] = {
							.sampler = whiteTextureSampler2dDefault->sampler,
							.imageView = whiteTextureSampler2dDefault->view,
							.imageLayout = whiteTextureSampler2dDefault->vkLayout
						};
						break;
					case shader_type::uniform_type::TYPE_SAMPLERCUBE:
						currentContext.descriptorImageInfos[samplerIdx] = {
							.sampler = whiteTextureSamplerCubeDefault->sampler,
							.imageView = whiteTextureSamplerCubeDefault->view,
							.imageLayout = whiteTextureSamplerCubeDefault->vkLayout
						};
						break;
					default:
						Console::println("VKRenderer::" + string(__FUNCTION__) + "(): object command: unknown sampler: " + to_string(uniform->type));
						break;
				}
			} else {
				auto& texture = currentContext.boundTextures[uniform->textureUnit];
				if (texture.view == VK_NULL_HANDLE) {
					switch(uniform->type) {
						case shader_type::uniform_type::TYPE_SAMPLER2D:
							currentContext.descriptorImageInfos[samplerIdx] = {
								.sampler = whiteTextureSampler2dDefault->sampler,
								.imageView = whiteTextureSampler2dDefault->view,
								.imageLayout = whiteTextureSampler2dDefault->vkLayout
							};
							break;
						case shader_type::uniform_type::TYPE_SAMPLERCUBE:
							currentContext.descriptorImageInfos[samplerIdx] = {
								.sampler = whiteTextureSamplerCubeDefault->sampler,
								.imageView = whiteTextureSamplerCubeDefault->view,
								.imageLayout = whiteTextureSamplerCubeDefault->vkLayout
							};
							break;
						default:
							Console::println("VKRenderer::" + string(__FUNCTION__) + "(): object command: unknown sampler: " + to_string(uniform->type));
							break;
					}
				} else {
					currentContext.descriptorImageInfos[samplerIdx] = {
						.sampler = texture.sampler,
						.imageView = texture.view,
						.imageLayout = texture.layout
					};
				}
			}
			currentContext.descriptorWriteSets[uniform->position] = {
				.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
				.pNext = nullptr,
				.dstSet = descriptorSet2,
				.dstBinding = static_cast<uint32_t>(uniform->position),
				.dstArrayElement = 0,
				.descriptorCount = 1,
				.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
				.pImageInfo = &currentContext.descriptorImageInfos[samplerIdx],
				.pBufferInfo = VK_NULL_HANDLE,
				.pTexelBufferView = VK_NULL_HANDLE
			};
			samplerIdx++;
		}

		// uniform buffer
		if (shader->uboBindingIdx == -1) {
			shaderIdx++;
			continue;
		}

		//
		auto& uniformBuffer = shader->uniformBuffers[currentContext.idx];
		auto& src = uniformBuffer.buffers[uniformBuffer.bufferIdx];
		auto uboBuffer = src.buffer;
		uniformBuffer.bufferIdx = (uniformBuffer.bufferIdx + 1) % uniformBuffer.buffers.size();
		vmaMemCpy(src.allocation, currentContext.uniformBufferData[shaderIdx].data(), uniformBuffer.size);

		//
		currentContext.descriptorBufferInfos[shader->uboBindingIdx] = {
			.buffer = uboBuffer,
			.offset = 0,
			.range = shader->uboSize
		};

		//
		currentContext.descriptorWriteSets[shader->uboBindingIdx] = {
			.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
			.pNext = nullptr,
			.dstSet = descriptorSet1,
			.dstBinding = static_cast<uint32_t>(shader->uboBindingIdx),
			.dstArrayElement = 0,
			.descriptorCount = 1,
			.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
			.pImageInfo = nullptr,
			.pBufferInfo = &currentContext.descriptorBufferInfos[shader->uboBindingIdx],
			.pTexelBufferView = nullptr
		};

		//
		shaderIdx++;
		uboIdx++;
	}

	//
	vkUpdateDescriptorSets(device, currentContext.program->layoutBindings, currentContext.descriptorWriteSets.data(), 0, nullptr);

	//
	auto& drawCommand = currentContext.commandBuffers[currentContext.currentCommandBuffer].drawCommand;
	array<VkDescriptorSet, 2> descriptorSets { descriptorSet1, descriptorSet2 };
	vkCmdBindDescriptorSets(drawCommand, VK_PIPELINE_BIND_POINT_GRAPHICS, currentContext.program->pipelineLayout, 0, descriptorSets.size(), descriptorSets.data(), 0, nullptr);
	vkCmdBindVertexBuffers(drawCommand, 0, LINES_VERTEX_BUFFER_COUNT, currentContext.boundBuffers.data(), currentContext.boundBufferOffsets.data());
	vkCmdSetLineWidth(drawCommand, lineWidth);
	vkCmdDraw(drawCommand, points, 1, pointsOffset, 0);

	//
	programCommandBuffer.descriptorSets1Idx++;
	programCommandBuffer.descriptorSets2IdxUncached++;
	currentContext.commandCount++;

	//
	requestSubmitDrawBuffers(currentContext.idx);

	//
	AtomicOperations::increment(statistics.renderCalls);
	AtomicOperations::increment(statistics.linePoints, points);
}

void VKRenderer::unbindBufferObjects(void* context)
{
	auto& currentContext = *static_cast<context_type*>(context);
	uint32_t bufferSize = 0;
	auto defaultBuffer = getBufferObjectInternal(emptyVertexBuffer, bufferSize);
	currentContext.boundIndicesBuffer = VK_NULL_HANDLE;
	currentContext.boundBuffers.fill(defaultBuffer);
	currentContext.boundBufferSizes.fill(bufferSize);
}

void VKRenderer::disposeBufferObjects(vector<int32_t>& bufferObjectIds)
{
	disposeMutex.lock();
	for (auto bufferObjectId: bufferObjectIds) {
		disposeBuffers.push_back(bufferObjectId);
	}
	disposeMutex.unlock();
}

int32_t VKRenderer::getTextureUnit(void* context)
{
	return (*static_cast<context_type*>(context)).activeTextureUnit;
}

void VKRenderer::setTextureUnit(void* context, int32_t textureUnit)
{
	(*static_cast<context_type*>(context)).activeTextureUnit = textureUnit;
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
	enableBlending();
	disableCulling(&contexts[0]);
	disableDepthBufferTest();
	disableDepthBufferWriting();
}

void VKRenderer::doneGuiMode()
{
	enableDepthBufferWriting();
	enableDepthBufferTest();
	enableCulling(&contexts[0]);
	disableBlending();
}

void VKRenderer::dispatchCompute(void* context, int32_t numGroupsX, int32_t numGroupsY, int32_t numGroupsZ) {
	// have our context typed
	auto& currentContext = *static_cast<context_type*>(context);
	auto& programCommandBuffer = currentContext.program->contexts[currentContext.idx].commandBuffers[currentContext.currentCommandBuffer];

	// check if desc1 left
	if (programCommandBuffer.descriptorSets1Idx == DESC_MAX_UNCACHED) {
		Console::println("VKRenderer::" + string(__FUNCTION__) + "(): program.desc_idxs1[" + to_string(currentContext.idx) + "] == DESC_MAX: " + to_string(programCommandBuffer.descriptorSets1Idx));
		return;
	}
	//
	auto descriptorSet = programCommandBuffer.descriptorSets1[programCommandBuffer.descriptorSets1Idx];

	// start draw command buffer, it not yet done
	beginDrawCommandBuffer(currentContext.idx);
	// render pass
	endRenderPass(currentContext.idx);
	// pipeline
	setupSkinningComputingPipeline(currentContext.idx, currentContext.program);

	// do compute command
	auto shaderIdx = 0;
	for (auto shader: currentContext.program->shaders) {
		for (int i = 0; i <= shader->maxBindings; i++) {
			currentContext.descriptorBufferInfos[i] = {
				.buffer = currentContext.boundBuffers[i],
				.offset = 0,
				.range = currentContext.boundBufferSizes[i]
			};
			currentContext.descriptorWriteSets[i] = {
				.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
				.pNext = nullptr,
				.dstSet = descriptorSet,
				.dstBinding = static_cast<uint32_t>(i),
				.dstArrayElement = 0,
				.descriptorCount = 1,
				.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
				.pImageInfo = nullptr,
				.pBufferInfo = &currentContext.descriptorBufferInfos[i],
				.pTexelBufferView = nullptr
			};
		}

		// uniform buffer
		if (shader->uboBindingIdx == -1) {
			shaderIdx++;
			continue;
		}

		//
		//
		auto& uniformBuffer = shader->uniformBuffers[currentContext.idx];
		auto& src = uniformBuffer.buffers[uniformBuffer.bufferIdx];
		auto uboBuffer = src.buffer;
		uniformBuffer.bufferIdx = (uniformBuffer.bufferIdx + 1) % uniformBuffer.buffers.size();
		vmaMemCpy(src.allocation, currentContext.uniformBufferData[shaderIdx].data(), uniformBuffer.size);

		//
		currentContext.descriptorBufferInfos[shader->uboBindingIdx] = {
			.buffer = uboBuffer,
			.offset = 0,
			.range = shader->uboSize
		};

		//
		currentContext.descriptorWriteSets[shader->uboBindingIdx] = {
			.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
			.pNext = nullptr,
			.dstSet = descriptorSet,
			.dstBinding = static_cast<uint32_t>(shader->uboBindingIdx),
			.dstArrayElement = 0,
			.descriptorCount = 1,
			.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
			.pImageInfo = nullptr,
			.pBufferInfo = &currentContext.descriptorBufferInfos[shader->uboBindingIdx],
			.pTexelBufferView = nullptr,
		};

		//
		shaderIdx++;
	}

	//
	vkUpdateDescriptorSets(device, currentContext.program->layoutBindings, currentContext.descriptorWriteSets.data(), 0, nullptr);

	//
	auto& drawCommand = currentContext.commandBuffers[currentContext.currentCommandBuffer].drawCommand;
	vkCmdBindDescriptorSets(drawCommand, VK_PIPELINE_BIND_POINT_COMPUTE, currentContext.program->pipelineLayout, 0, 1, &descriptorSet, 0, nullptr);
	vkCmdDispatch(drawCommand, numGroupsX, numGroupsY, numGroupsZ);

	//
	programCommandBuffer.descriptorSets1Idx++;
	currentContext.commandCount++;

	//
	requestSubmitDrawBuffers(currentContext.idx);

	//
	AtomicOperations::increment(statistics.computeCalls);
}

void VKRenderer::finishRendering() {
	VkResult err;

	// end render passes
	auto submittedCommandBuffersCount = 0;
	VkCommandBuffer submittedCommandBuffers[Engine::getThreadCount() * DRAW_COMMANDBUFFER_MAX * 3];
	for (auto i = 0; i < Engine::getThreadCount(); i++) {
		finishSetupCommandBuffer(i);
		endRenderPass(i); // TODO: draw cmd cycling
		for (auto j = 0; j < DRAW_COMMANDBUFFER_MAX; j++) {
			auto commandBuffer = endDrawCommandBuffer(i, j, false);
			if (commandBuffer != VK_NULL_HANDLE) {
				submittedCommandBuffers[submittedCommandBuffersCount++] = commandBuffer;
			}
		}
	}

	//
	if (submittedCommandBuffersCount > 0) {
		submitDrawCommandBuffers(submittedCommandBuffersCount, submittedCommandBuffers, memoryBarrierFence, true, true);
		for (auto i = 0; i < Engine::getThreadCount(); i++) {
			recreateContextFences(i);
		}
	}

	//
	for (auto& context: contexts) {
		/*
		for (auto i = 0; i < context.computeRenderBarrierBufferCount; i++) {
			Console::println(to_string((uint64_t)context.computeRenderBarrierBuffers[i]));
		}
		*/
		context.computeRenderBarrierBufferCount = 0;
	}

	//
	bindFrameBuffer(ID_NONE);
}

void VKRenderer::memoryBarrier() {
	VkResult err;

	// TODO: pass multiple buffer barriers to vkCmdPipelineBarrier
	//
	auto prevAccesses = THSVS_ACCESS_COMPUTE_SHADER_WRITE;
	auto nextAccesses = THSVS_ACCESS_VERTEX_BUFFER;
	for (auto& context: contexts) {
		for (auto i = 0; i < context.computeRenderBarrierBufferCount; i++) {
			ThsvsBufferBarrier svsbufferBarrier = {
			    .prevAccessCount = 1,
			    .pPrevAccesses = &prevAccesses,
			    .nextAccessCount = 1,
			    .pNextAccesses = &nextAccesses,
			    .srcQueueFamilyIndex = 0,
			    .dstQueueFamilyIndex = 0,
			    .buffer = context.computeRenderBarrierBuffers[i],
			    .offset = 0,
			    .size = VK_WHOLE_SIZE
			};
			VkBufferMemoryBarrier vkBufferMemoryBarrier;
			VkPipelineStageFlags srcStages;
			VkPipelineStageFlags dstStages;
			thsvsGetVulkanBufferMemoryBarrier(
				svsbufferBarrier,
				&srcStages,
				&dstStages,
				&vkBufferMemoryBarrier
			);
			prepareSetupCommandBuffer(context.idx);
			vkCmdPipelineBarrier(context.setupCommandInUse, srcStages, dstStages, 0, 0, nullptr, 1, &vkBufferMemoryBarrier, 0, nullptr);
			finishSetupCommandBuffer(context.idx);
		}
		context.computeRenderBarrierBufferCount = 0;
	}
}

void VKRenderer::uploadSkinningBufferObject(void* context, int32_t bufferObjectId, int32_t size, FloatBuffer* data) {
	auto& currentContext = *static_cast<context_type*>(context);
	uploadBufferObjectInternal(currentContext.idx, bufferObjectId, size, data->getBuffer(), (VkBufferUsageFlagBits)(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT));
}

void VKRenderer::uploadSkinningBufferObject(void* context, int32_t bufferObjectId, int32_t size, IntBuffer* data) {
	auto& currentContext = *static_cast<context_type*>(context);
	uploadBufferObjectInternal(currentContext.idx, bufferObjectId, size, data->getBuffer(), (VkBufferUsageFlagBits)(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT));
}

void VKRenderer::bindSkinningVerticesBufferObject(void* context, int32_t bufferObjectId) {
	auto& currentContext = *static_cast<context_type*>(context);
	currentContext.boundBuffers[0] =
		bufferObjectId == ID_NONE?
			getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[0]):
			getBufferObjectInternal(currentContext.idx, bufferObjectId, currentContext.boundBufferSizes[0]);
	if (currentContext.boundBuffers[0] == VK_NULL_HANDLE) {
		currentContext.boundBuffers[0] =	getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[0]);
	}
}

void VKRenderer::bindSkinningNormalsBufferObject(void* context, int32_t bufferObjectId) {
	auto& currentContext = *static_cast<context_type*>(context);
	currentContext.boundBuffers[1] =
		bufferObjectId == ID_NONE?
			getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[1]):
			getBufferObjectInternal(currentContext.idx, bufferObjectId, currentContext.boundBufferSizes[1]);
	if (currentContext.boundBuffers[1] == VK_NULL_HANDLE) {
		currentContext.boundBuffers[1] =	getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[1]);
	}
}

void VKRenderer::bindSkinningVertexJointsBufferObject(void* context, int32_t bufferObjectId) {
	auto& currentContext = *static_cast<context_type*>(context);
	currentContext.boundBuffers[2] =
		bufferObjectId == ID_NONE?
			getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[2]):
			getBufferObjectInternal(currentContext.idx, bufferObjectId, currentContext.boundBufferSizes[2]);
	if (currentContext.boundBuffers[2] == VK_NULL_HANDLE) {
		currentContext.boundBuffers[2] =	getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[2]);
	}
}

void VKRenderer::bindSkinningVertexJointIdxsBufferObject(void* context, int32_t bufferObjectId) {
	auto& currentContext = *static_cast<context_type*>(context);
	currentContext.boundBuffers[3] =
		bufferObjectId == ID_NONE?
			getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[3]):
			getBufferObjectInternal(currentContext.idx, bufferObjectId, currentContext.boundBufferSizes[3]);
	if (currentContext.boundBuffers[3] == VK_NULL_HANDLE) {
		currentContext.boundBuffers[3] =	getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[3]);
	}
}

void VKRenderer::bindSkinningVertexJointWeightsBufferObject(void* context, int32_t bufferObjectId) {
	auto& currentContext = *static_cast<context_type*>(context);
	currentContext.boundBuffers[4] =
		bufferObjectId == ID_NONE?
			getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[4]):
			getBufferObjectInternal(currentContext.idx, bufferObjectId, currentContext.boundBufferSizes[4]);
	if (currentContext.boundBuffers[4] == VK_NULL_HANDLE) {
		currentContext.boundBuffers[4] =	getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[4]);
	}
}

void VKRenderer::bindSkinningVerticesResultBufferObject(void* context, int32_t bufferObjectId) {
	auto& currentContext = *static_cast<context_type*>(context);
	currentContext.boundBuffers[5] =
		bufferObjectId == ID_NONE?
			getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[5]):
			getBufferObjectInternal(currentContext.idx, bufferObjectId, currentContext.boundBufferSizes[5]);
	if (currentContext.boundBuffers[5] == VK_NULL_HANDLE) {
		currentContext.boundBuffers[5] =	getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[5]);
	}
	if (currentContext.computeRenderBarrierBufferCount >= currentContext.computeRenderBarrierBuffers.size()) {
		Console::println("VKRenderer::bindSkinningVerticesResultBufferObject(): too many compute render buffers");
		return;
	}
	currentContext.computeRenderBarrierBuffers[currentContext.computeRenderBarrierBufferCount++] = currentContext.boundBuffers[5];
	//
	auto prevAccesses = THSVS_ACCESS_VERTEX_BUFFER;
	auto nextAccesses = THSVS_ACCESS_COMPUTE_SHADER_WRITE;
	ThsvsBufferBarrier svsbufferBarrier = {
		.prevAccessCount = 1,
		.pPrevAccesses = &prevAccesses,
		.nextAccessCount = 1,
		.pNextAccesses = &nextAccesses,
		.srcQueueFamilyIndex = 0,
		.dstQueueFamilyIndex = 0,
		.buffer = currentContext.boundBuffers[5],
		.offset = 0,
		.size = VK_WHOLE_SIZE
	};
	VkBufferMemoryBarrier vkBufferMemoryBarrier;
	VkPipelineStageFlags srcStages;
	VkPipelineStageFlags dstStages;
	thsvsGetVulkanBufferMemoryBarrier(
		svsbufferBarrier,
		&srcStages,
		&dstStages,
		&vkBufferMemoryBarrier
	);
	prepareSetupCommandBuffer(currentContext.idx);
	vkCmdPipelineBarrier(currentContext.setupCommandInUse, srcStages, dstStages, 0, 0, nullptr, 1, &vkBufferMemoryBarrier, 0, nullptr);
	finishSetupCommandBuffer(currentContext.idx);
}

void VKRenderer::bindSkinningNormalsResultBufferObject(void* context, int32_t bufferObjectId) {
	auto& currentContext = *static_cast<context_type*>(context);
	currentContext.boundBuffers[6] =
		bufferObjectId == ID_NONE?
			getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[6]):
			getBufferObjectInternal(currentContext.idx, bufferObjectId, currentContext.boundBufferSizes[6]);
	if (currentContext.boundBuffers[6] == VK_NULL_HANDLE) {
		currentContext.boundBuffers[6] =
			getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[6]);
	}
	if (currentContext.computeRenderBarrierBufferCount >= currentContext.computeRenderBarrierBuffers.size()) {
		Console::println("VKRenderer::bindSkinningNormalsResultBufferObject(): too many compute render buffers");
		return;
	}
	currentContext.computeRenderBarrierBuffers[currentContext.computeRenderBarrierBufferCount++] = currentContext.boundBuffers[6];
	auto prevAccesses = THSVS_ACCESS_VERTEX_BUFFER;
	auto nextAccesses = THSVS_ACCESS_COMPUTE_SHADER_WRITE;
	ThsvsBufferBarrier svsbufferBarrier = {
		.prevAccessCount = 1,
		.pPrevAccesses = &prevAccesses,
		.nextAccessCount = 1,
		.pNextAccesses = &nextAccesses,
		.srcQueueFamilyIndex = 0,
		.dstQueueFamilyIndex = 0,
		.buffer = currentContext.boundBuffers[6],
		.offset = 0,
		.size = VK_WHOLE_SIZE
	};
	VkBufferMemoryBarrier vkBufferMemoryBarrier;
	VkPipelineStageFlags srcStages;
	VkPipelineStageFlags dstStages;
	thsvsGetVulkanBufferMemoryBarrier(
		svsbufferBarrier,
		&srcStages,
		&dstStages,
		&vkBufferMemoryBarrier
	);
	prepareSetupCommandBuffer(currentContext.idx);
	vkCmdPipelineBarrier(currentContext.setupCommandInUse, srcStages, dstStages, 0, 0, nullptr, 1, &vkBufferMemoryBarrier, 0, nullptr);
	finishSetupCommandBuffer(currentContext.idx);
}

void VKRenderer::bindSkinningMatricesBufferObject(void* context, int32_t bufferObjectId) {
	auto& currentContext = *static_cast<context_type*>(context);
	currentContext.boundBuffers[7] =
		bufferObjectId == ID_NONE?
			getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[7]):
			getBufferObjectInternal(currentContext.idx, bufferObjectId, currentContext.boundBufferSizes[7]);
	if (currentContext.boundBuffers[7] == VK_NULL_HANDLE) {
		currentContext.boundBuffers[7] =	getBufferObjectInternal(emptyVertexBuffer, currentContext.boundBufferSizes[7]);
	}
}

int32_t VKRenderer::createVertexArrayObject() {
	Console::println("VKRenderer::createVertexArrayObject(): Not implemented");
	return -1;
}

void VKRenderer::disposeVertexArrayObject(int32_t vertexArrayObjectId) {
	Console::println("VKRenderer::disposeVertexArrayObject(): Not implemented");
}

void VKRenderer::bindVertexArrayObject(int32_t vertexArrayObjectId) {
	Console::println("VKRenderer::bindVertexArrayObject(): Not implemented");
}

Matrix2D3x3& VKRenderer::getTextureMatrix(void* context) {
	auto& currentContext = *static_cast<context_type*>(context);
	return currentContext.textureMatrix;
}

Renderer::Renderer_Light& VKRenderer::getLight(void* context, int32_t lightId) {
	auto& currentContext = *static_cast<context_type*>(context);
	return currentContext.lights[lightId];
}

array<float, 4>& VKRenderer::getEffectColorMul(void* context) {
	auto& currentContext = *static_cast<context_type*>(context);
	return currentContext.effectColorMul;
}

array<float, 4>& VKRenderer::getEffectColorAdd(void* context) {
	auto& currentContext = *static_cast<context_type*>(context);
	return currentContext.effectColorAdd;
}

Renderer::Renderer_SpecularMaterial& VKRenderer::getSpecularMaterial(void* context) {
	auto& currentContext = *static_cast<context_type*>(context);
	return currentContext.specularMaterial;
}

Renderer::Renderer_PBRMaterial& VKRenderer::getPBRMaterial(void* context) {
	auto& currentContext = *static_cast<context_type*>(context);
	return currentContext.pbrMaterial;
}

const string& VKRenderer::getShader(void* context) {
	auto& currentContext = *static_cast<context_type*>(context);
	return currentContext.shader;
}

void VKRenderer::setShader(void* context, const string& id) {
	auto& currentContext = *static_cast<context_type*>(context);
	currentContext.shader = id;
}

const EntityShaderParameters& VKRenderer::getShaderParameters(void* context) {
	auto& currentContext = *static_cast<context_type*>(context);
	return currentContext.shaderParameters;
}

void VKRenderer::setShaderParameters(void* context, const EntityShaderParameters& parameters) {
	auto& currentContext = *static_cast<context_type*>(context);
	currentContext.shaderParameters = parameters;
}

float VKRenderer::getMaskMaxValue(void* context) {
	auto& currentContext = *static_cast<context_type*>(context);
	return currentContext.maskMaxValue;
}

void VKRenderer::setMaskMaxValue(void* context, float maskMaxValue) {
	auto& currentContext = *static_cast<context_type*>(context);
	currentContext.maskMaxValue = maskMaxValue;
}

array<float, 3>& VKRenderer::getEnvironmentMappingCubeMapPosition(void* context) {
	auto& currentContext = *static_cast<context_type*>(context);
	return currentContext.environmentMappingCubeMapPosition;
}

void VKRenderer::setEnvironmentMappingCubeMapPosition(void* context, array<float, 3>& position) {
	auto& currentContext = *static_cast<context_type*>(context);
	currentContext.environmentMappingCubeMapPosition = position;
}

void VKRenderer::setVSyncEnabled(bool vSync) {
	swapchainPresentMode = vSync == true?VK_PRESENT_MODE_FIFO_KHR:VK_PRESENT_MODE_IMMEDIATE_KHR;
	reshape();
}

const Renderer::Renderer_Statistics VKRenderer::getStatistics() {
	VmaBudget budget[3];
	memset(budget, 0, sizeof(budget));
	vmaGetBudget(allocator, budget);
	auto stats = statistics;
	stats.memoryUsageGPU = budget[0].allocationBytes;
	stats.memoryUsageShared = budget[1].allocationBytes;
	statistics.time = Time::getCurrentMillis();
	statistics.memoryUsageGPU = -1LL;
	statistics.memoryUsageShared = -1LL;
	statistics.clearCalls = 0;
	statistics.renderCalls = 0;
	statistics.instances = 0;
	statistics.computeCalls = 0;
	statistics.triangles = 0;
	statistics.points = 0;
	statistics.linePoints = 0;
	statistics.bufferUploads = 0;
	statistics.textureUploads = 0;
	statistics.renderPasses = 0;
	statistics.drawCommands = 0;
	statistics.submits = 0;
	statistics.disposedTextures = 0;
	statistics.disposedBuffers = 0;
	return stats;
}
