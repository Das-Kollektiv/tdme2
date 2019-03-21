/**
 * based on https://github.com/glfw/glfw/blob/master/tests/vulkan.c
 */

#include <tdme/engine/subsystems/renderer/VKRenderer.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <string.h>

#include <array>
#include <cassert>
#include <vector>
#include <string>

#include <tdme/application/Application.h>
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
#include <tdme/utils/StringUtils.h>

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
using std::vector;
using std::string;
using std::to_string;

using tdme::engine::subsystems::renderer::VKRenderer;
using tdme::application::Application;
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
	SHADER_FRAGMENT_SHADER = -1;
	SHADER_VERTEX_SHADER = -1;
	SHADER_COMPUTE_SHADER = -1;
	SHADER_GEOMETRY_SHADER = -1;
	DEPTHFUNCTION_ALWAYS = -1;;
	DEPTHFUNCTION_EQUAL = -1;;
	DEPTHFUNCTION_LESSEQUAL = -1;;
	DEPTHFUNCTION_GREATEREQUAL = -1;;
}

const string VKRenderer::getGLVersion()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return "gl3";
}

/**
 * Return 1 (true) if all layer names specified in check_names
 * can be found in given layer properties.
 */
static VkBool32 vulkan_check_layers(uint32_t check_count, const char **check_names, uint32_t layer_count, VkLayerProperties *layers) {
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

void VKRenderer::initialize()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");

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
	VkBool32 validation_found = 0;
	if (context.validate) {

		err = vkEnumerateInstanceLayerProperties(&instance_layer_count, NULL);
		assert(!err);

		instance_validation_layers = (const char**) instance_validation_layers_alt1;
		if (instance_layer_count > 0) {
			VkLayerProperties* instance_layers = (VkLayerProperties*)malloc(sizeof(VkLayerProperties) * instance_layer_count);
			err = vkEnumerateInstanceLayerProperties(&instance_layer_count, instance_layers);
			assert(!err);

			validation_found = vulkan_check_layers(
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
				validation_found = vulkan_check_layers(
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
		err = vkEnumerateInstanceExtensionProperties(
		NULL, &instance_extension_count, instance_extensions);
		assert(!err);
		for (i = 0; i < instance_extension_count; i++) {
			if (!strcmp(VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
					instance_extensions[i].extensionName)) {
				if (context.validate) {
					context.extension_names[context.enabled_extension_count++] =
					VK_EXT_DEBUG_REPORT_EXTENSION_NAME;
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
		flags: VkInstanceCreateFlags(),
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
		ERR_EXIT("vkEnumeratePhysicalDevices reported zero accessible devices."
				"\n\nDo you have a compatible Vulkan installable client"
				" driver (ICD) installed?\nPlease look at the Getting Started"
				" guide for additional information.\n",
				"vkEnumeratePhysicalDevices Failure");
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

	if (context.validate) {
		context.CreateDebugReportCallback = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(context.inst, "vkCreateDebugReportCallbackEXT");
		context.DestroyDebugReportCallback = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(context.inst, "vkDestroyDebugReportCallbackEXT");
		if (!context.CreateDebugReportCallback) {
			ERR_EXIT(
				"GetProcAddr: Unable to find vkCreateDebugReportCallbackEXT\n",
				"vkGetProcAddr Failure"
			);
		}
		if (!context.DestroyDebugReportCallback) {
			ERR_EXIT(
				"GetProcAddr: Unable to find vkDestroyDebugReportCallbackEXT\n",
				"vkGetProcAddr Failure"
			);
		}
		context.DebugReportMessage = (PFN_vkDebugReportMessageEXT) vkGetInstanceProcAddr(context.inst, "vkDebugReportMessageEXT");
		if (!context.DebugReportMessage) {
			ERR_EXIT(
				"GetProcAddr: Unable to find vkDebugReportMessageEXT\n",
				"vkGetProcAddr Failure"
			);
		}

		VkDebugReportCallbackCreateInfoEXT dbgCreateInfo;
		dbgCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
		dbgCreateInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
		// TODO: a.drewke; dbgCreateInfo.pfnCallback = context.use_break ? BreakCallback : dbgFunc;
		dbgCreateInfo.pUserData = &context;
		dbgCreateInfo.pNext = NULL;
		err = context.CreateDebugReportCallback(context.inst, &dbgCreateInfo, NULL, &context.msg_callback);
		switch (err) {
		case VK_SUCCESS:
			break;
		case VK_ERROR_OUT_OF_HOST_MEMORY:
			ERR_EXIT("CreateDebugReportCallback: out of host memory\n",
					"CreateDebugReportCallback Failure");
			break;
		default:
			ERR_EXIT("CreateDebugReportCallback: unknown failure\n",
					"CreateDebugReportCallback Failure");
			break;
		}
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

	// Graphics queue and MemMgr queue can be separate.
	// TODO: Add support for separate queues, including synchronization,
	//       and appropriate tracking for QueueSubmit

	//
	context.depthStencil = 1.0;
	context.depthIncrement = -0.01f;

	// Create a WSI surface for the window:
	glfwCreateWindowSurface(context.inst, Application::window, NULL, &context.surface);

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
		flags: VkDeviceQueueCreateFlags(),
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
		flags: VkDeviceCreateFlags(),
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
}

void VKRenderer::initializeFrame()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	GLRenderer::initializeFrame();
}

bool VKRenderer::isBufferObjectsAvailable()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return true;
}

bool VKRenderer::isDepthTextureAvailable()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return true;
}

bool VKRenderer::isUsingProgramAttributeLocation()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return false;
}

bool VKRenderer::isSpecularMappingAvailable()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return true;
}

bool VKRenderer::isNormalMappingAvailable()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return true;
}

bool VKRenderer::isDisplacementMappingAvailable()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return false;
}

bool VKRenderer::isInstancedRenderingAvailable() {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return true;
}

bool VKRenderer::isUsingShortIndices() {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return false;
}

bool VKRenderer::isGeometryShaderAvailable() {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return false;
}

int32_t VKRenderer::getTextureUnits()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return activeTextureUnit;
}

int32_t VKRenderer::loadShader(int32_t type, const string& pathName, const string& fileName, const string& definitions, const string& functions)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return -1;
}

void VKRenderer::useProgram(int32_t programId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

int32_t VKRenderer::createProgram()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return -1;
}

void VKRenderer::attachShaderToProgram(int32_t programId, int32_t shaderId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

bool VKRenderer::linkProgram(int32_t programId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return false;
}

int32_t VKRenderer::getProgramUniformLocation(int32_t programId, const string& name)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return -1;
}

void VKRenderer::setProgramUniformInteger(int32_t uniformId, int32_t value)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setProgramUniformFloat(int32_t uniformId, float value)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setProgramUniformFloatMatrix3x3(int32_t uniformId, const array<float, 9>& data)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setProgramUniformFloatMatrix4x4(int32_t uniformId, const array<float, 16>& data)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setProgramUniformFloatMatrices4x4(int32_t uniformId, int32_t count, FloatBuffer* data)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setProgramUniformFloatVec4(int32_t uniformId, const array<float, 4>& data)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setProgramUniformFloatVec3(int32_t uniformId, const array<float, 3>& data)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setProgramAttributeLocation(int32_t programId, int32_t location, const string& name)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setViewPort(int32_t x, int32_t y, int32_t width, int32_t height)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::updateViewPort()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setClearColor(float red, float green, float blue, float alpha)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::enableCulling()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::disableCulling()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::enableBlending()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::disableBlending()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::enableDepthBufferWriting()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::disableDepthBufferWriting()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::disableDepthBufferTest()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::enableDepthBufferTest()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setDepthFunction(int32_t depthFunction)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setColorMask(bool red, bool green, bool blue, bool alpha)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::clear(int32_t mask)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setCullFace(int32_t cullFace)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setFrontFace(int32_t frontFace)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

int32_t VKRenderer::createTexture()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return -1;
}

int32_t VKRenderer::createDepthBufferTexture(int32_t width, int32_t height)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return -1;
}

int32_t VKRenderer::createColorBufferTexture(int32_t width, int32_t height)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return -1;
}

void VKRenderer::uploadTexture(Texture* texture)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::resizeDepthBufferTexture(int32_t textureId, int32_t width, int32_t height)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::resizeColorBufferTexture(int32_t textureId, int32_t width, int32_t height)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindTexture(int32_t textureId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::disposeTexture(int32_t textureId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

int32_t VKRenderer::createFramebufferObject(int32_t depthBufferTextureGlId, int32_t colorBufferTextureGlId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return -1;
}

void VKRenderer::bindFrameBuffer(int32_t frameBufferId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::disposeFrameBufferObject(int32_t frameBufferId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

vector<int32_t> VKRenderer::createBufferObjects(int32_t buffers)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return vector<int32_t>();
}

void VKRenderer::uploadBufferObject(int32_t bufferObjectId, int32_t size, FloatBuffer* data)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::uploadIndicesBufferObject(int32_t bufferObjectId, int32_t size, ShortBuffer* data)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::uploadIndicesBufferObject(int32_t bufferObjectId, int32_t size, IntBuffer* data)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindIndicesBufferObject(int32_t bufferObjectId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindTextureCoordinatesBufferObject(int32_t bufferObjectId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindVerticesBufferObject(int32_t bufferObjectId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindNormalsBufferObject(int32_t bufferObjectId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindColorsBufferObject(int32_t bufferObjectId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindTangentsBufferObject(int32_t bufferObjectId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindBitangentsBufferObject(int32_t bufferObjectId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindModelMatricesBufferObject(int32_t bufferObjectId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindEffectColorMulsBufferObject(int32_t bufferObjectId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindEffectColorAddsBufferObject(int32_t bufferObjectId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::drawInstancedIndexedTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset, int32_t instances)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::drawIndexedTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::drawInstancedTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset, int32_t instances)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::drawTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::drawPointsFromBufferObjects(int32_t points, int32_t pointsOffset)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::unbindBufferObjects()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::disposeBufferObjects(vector<int32_t>& bufferObjectIds)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

int32_t VKRenderer::getTextureUnit()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return activeTextureUnit;
}

void VKRenderer::setTextureUnit(int32_t textureUnit)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	this->activeTextureUnit = textureUnit;
}

float VKRenderer::readPixelDepth(int32_t x, int32_t y)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return 0.0f;
}

ByteBuffer* VKRenderer::readPixels(int32_t x, int32_t y, int32_t width, int32_t height)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return nullptr;
}

void VKRenderer::initGuiMode()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::doneGuiMode()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::checkGLError(int line)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::dispatchCompute(int32_t numGroupsX, int32_t numGroupsY, int32_t numGroupsZ) {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::memoryBarrier() {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::uploadSkinningBufferObject(int32_t bufferObjectId, int32_t size, FloatBuffer* data) {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::uploadSkinningBufferObject(int32_t bufferObjectId, int32_t size, IntBuffer* data) {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindSkinningVerticesBufferObject(int32_t bufferObjectId) {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindSkinningNormalsBufferObject(int32_t bufferObjectId) {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindSkinningVertexJointsBufferObject(int32_t bufferObjectId) {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindSkinningVertexJointIdxsBufferObject(int32_t bufferObjectId) {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindSkinningVertexJointWeightsBufferObject(int32_t bufferObjectId) {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindSkinningVerticesResultBufferObject(int32_t bufferObjectId) {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindSkinningNormalsResultBufferObject(int32_t bufferObjectId) {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindSkinningMatricesBufferObject(int32_t bufferObjectId) {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}
