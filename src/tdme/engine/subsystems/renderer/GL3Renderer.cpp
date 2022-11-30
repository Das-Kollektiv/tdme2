#include <tdme/engine/subsystems/renderer/GL3Renderer.h>

#if defined (__APPLE__)
	#include <OpenGL/gl3.h>
	#include <OpenGL/OpenGL.h>
	#if !defined(__aarch64__)
		#include <OpenCL/opencl.h>
		#include <OpenCL/cl_gl.h>
	#endif
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__linux__) || defined(_WIN32) || defined(__HAIKU__)
	#define GLEW_NO_GLU
	#include <GL/glew.h>
#endif

#include <string.h>

#include <array>
#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/PNGTextureWriter.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/FrameBuffer.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Buffer.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/FloatBuffer.h>
#include <tdme/utilities/IntBuffer.h>
#include <tdme/utilities/ModelTools.h>
#include <tdme/utilities/ShortBuffer.h>
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/Time.h>

using std::array;
using std::map;
using std::string;
using std::to_string;
using std::vector;

using tdme::engine::subsystems::renderer::GL3Renderer;

using tdme::engine::fileio::textures::PNGTextureWriter;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Buffer;
using tdme::utilities::ByteBuffer;
using tdme::utilities::Console;
using tdme::utilities::FloatBuffer;
using tdme::utilities::IntBuffer;
using tdme::utilities::ShortBuffer;
using tdme::utilities::StringTools;
using tdme::utilities::Time;

GL3Renderer::GL3Renderer()
{
	rendererType = RENDERERTYPE_OPENGL;
	// setup GL3 consts
	ID_NONE = 0;
	CLEAR_DEPTH_BUFFER_BIT = GL_DEPTH_BUFFER_BIT;
	CLEAR_COLOR_BUFFER_BIT = GL_COLOR_BUFFER_BIT;
	CULLFACE_FRONT = GL_FRONT;
	CULLFACE_BACK = GL_BACK;
	FRONTFACE_CW = GL_CW;
	FRONTFACE_CCW = GL_CCW;
	SHADER_FRAGMENT_SHADER = GL_FRAGMENT_SHADER;
	SHADER_VERTEX_SHADER = GL_VERTEX_SHADER;
	#if defined (__APPLE__)
		SHADER_COMPUTE_SHADER = -1;
		UNIFORM_CL_SKINNING_VERTEX_COUNT = -1001;
		UNIFORM_CL_SKINNING_MATRIX_COUNT = -1002;
		UNIFORM_CL_SKINNING_INSTANCE_COUNT = -1003;
	#else
		SHADER_COMPUTE_SHADER = GL_COMPUTE_SHADER;
	#endif
	DEPTHFUNCTION_ALWAYS = GL_ALWAYS;
	DEPTHFUNCTION_EQUAL = GL_EQUAL;
	DEPTHFUNCTION_LESSEQUAL = GL_LEQUAL;
	DEPTHFUNCTION_GREATEREQUAL = GL_GEQUAL;
	CUBEMAPTEXTUREINDEX_NEGATIVE_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
	CUBEMAPTEXTUREINDEX_POSITIVE_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
	CUBEMAPTEXTUREINDEX_POSITIVE_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
	CUBEMAPTEXTUREINDEX_NEGATIVE_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
	CUBEMAPTEXTUREINDEX_POSITIVE_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
	CUBEMAPTEXTUREINDEX_NEGATIVE_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;
	activeTextureUnit = 0;
	engineVAO = ID_NONE;
	deferredShadingAvailable = false;
}

const string GL3Renderer::getVendor() {
	auto vendor = (char*)glGetString(GL_VENDOR);
	return string(vendor);
}

const string GL3Renderer::getRenderer() {
	auto renderer = (char*)glGetString(GL_RENDERER);
	return string(renderer) + " [GL3+/CORE]";
}

const string GL3Renderer::getShaderVersion()
{
	return "gl3";
}

bool GL3Renderer::isSupportingMultithreadedRendering() {
	return false;
}

#if defined (__APPLE__) && !defined(__aarch64__)
	void GL3Renderer::clErrorCallback(const char* errorInfo, const void* privateInfo, size_t cb, void* userData) {
		Console::println(string("GL3Renderer::clErrorCallback(): ") + errorInfo);
	}
#endif

void GL3Renderer::initialize()
{
	glGetError();
	// get default framebuffer
	FRAMEBUFFER_DEFAULT = 0; //getContext()->getDefaultDrawFramebuffer();
	// setup open gl
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LEQUAL);
	glBlendEquation(GL_FUNC_ADD);
	glDisable(GL_BLEND);
	#if !defined (__APPLE__)
		glEnable(GL_POINT_SPRITE);
	#endif
	glEnable(GL_PROGRAM_POINT_SIZE);
	setTextureUnit(CONTEXTINDEX_DEFAULT, 0);
	// port-macosx requires this
	glGenVertexArrays(1, &engineVAO);
	glBindVertexArray(engineVAO);
	//
	#if defined (__APPLE__) && !defined(__aarch64__)
		// TODO: error management
		// shader source
		auto skinningKernelProgramSource = FileSystem::getInstance()->getContentAsString("shader/gl3/skinning", "skinning.cl");
		auto skinningKernelProgramSourceSize = skinningKernelProgramSource.size();
		char* skinningKernelProgramSourceHeap = new char[skinningKernelProgramSourceSize + 1];
		strcpy(skinningKernelProgramSourceHeap, skinningKernelProgramSource.c_str());

		// context, device
		cl_int clError = 0;
		cl_device_id clDeviceId = 0;
		auto clCurrentContext = CGLGetCurrentContext();
		auto clShareGroup = CGLGetShareGroup(clCurrentContext);
		gcl_gl_set_sharegroup(clShareGroup);
		auto clDispatchQueue = gcl_create_dispatch_queue(CL_DEVICE_TYPE_GPU, nullptr);
		clDeviceId = gcl_get_device_id_with_dispatch_queue(clDispatchQueue);

		// device vendor + names
		size_t clSize = 0;
		cl_char clDeviceVendorName[1024] = {0};
		cl_char clDeviceDeviceName[1024] = {0};
		clError = clGetDeviceInfo(clDeviceId, CL_DEVICE_VENDOR, sizeof(clDeviceVendorName) - 1, clDeviceVendorName, &clSize);
		clError|= clGetDeviceInfo(clDeviceId, CL_DEVICE_NAME, sizeof(clDeviceDeviceName) - 1, clDeviceDeviceName, &clSize);
		Console::println(string("GL3Renderer::initialize(): Using OpenCL CL device: ") + (char*)clDeviceVendorName + ": " + (char*)clDeviceDeviceName);

		// CL context, skinning kernel
		cl_context_properties properties[] = {
			CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE,
			(cl_context_properties)clShareGroup,
			0
		};
		clContext = clCreateContext(properties, 1, &clDeviceId, clErrorCallback, nullptr, &clError);
		clCommandQueue = clCreateCommandQueue(clContext, clDeviceId, 0, &clError);
		clSkinningKernelProgram = clCreateProgramWithSource(clContext, 1, (const char**)&skinningKernelProgramSourceHeap, &skinningKernelProgramSourceSize, &clError);
		clError = clBuildProgram(clSkinningKernelProgram, 1, &clDeviceId, nullptr, nullptr, nullptr);
		auto clBuildInfo = clGetProgramBuildInfo(clSkinningKernelProgram, clDeviceId, CL_PROGRAM_BUILD_STATUS, 0, nullptr, &clSize);
		clSkinningKernel = clCreateKernel(clSkinningKernelProgram, "computeSkinning", &clError);
	#endif
	// check if deferred shading is available
	int glMaxColorAttachments = 0;
	glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &glMaxColorAttachments);
	int glMaxDrawBuffers = 0;
	glGetIntegerv(GL_MAX_DRAW_BUFFERS, &glMaxDrawBuffers);
	deferredShadingAvailable = glMaxColorAttachments >= 8 && glMaxDrawBuffers >= 8;
	// renderer contexts
	rendererContexts.resize(1);
	for (auto& rendererContext: rendererContexts) {
		for (auto i = 0; i < rendererContext.lights.size(); i++) {
			rendererContext.lights[i].spotCosCutoff = static_cast<float>(Math::cos(Math::PI / 180.0f * 180.0f));
		}
		rendererContext.textureMatrix.identity();
	}
}

void GL3Renderer::initializeFrame()
{
}

void GL3Renderer::finishFrame()
{
}

bool GL3Renderer::isBufferObjectsAvailable()
{
	return true;
}

bool GL3Renderer::isDepthTextureAvailable()
{
	return true;
}

bool GL3Renderer::isUsingProgramAttributeLocation()
{
	return false;
}

bool GL3Renderer::isSupportingIntegerProgramAttributes() {
	return true;
}

bool GL3Renderer::isSpecularMappingAvailable()
{
	return true;
}

bool GL3Renderer::isNormalMappingAvailable()
{
	return true;
}

bool GL3Renderer::isInstancedRenderingAvailable() {
	return true;
}

bool GL3Renderer::isPBRAvailable()
{
	return true;
}

bool GL3Renderer::isComputeShaderAvailable() {
	#if defined(__HAIKU__)
		// does not work for now with Haiku OS
		return false;
	#else
		int glMajorVersion;
		int glMinorVersion;
		glGetIntegerv(GL_MAJOR_VERSION, &glMajorVersion);
		glGetIntegerv(GL_MINOR_VERSION, &glMinorVersion);
		return (glMajorVersion == 4 && glMinorVersion >= 3) || glMajorVersion > 4;
	#endif
}

bool GL3Renderer::isGLCLAvailable() {
	#if defined (__APPLE__) && !defined(__aarch64__)
		return true;
	#else
		return false;
	#endif
}

bool GL3Renderer::isUsingShortIndices() {
	return false;
}

bool GL3Renderer::isDeferredShadingAvailable() {
	return deferredShadingAvailable;
}

int32_t GL3Renderer::getTextureUnits()
{
	return activeTextureUnit;
}

int32_t GL3Renderer::loadShader(int32_t type, const string& pathName, const string& fileName, const string& definitions, const string& functions)
{
	// create shader
	int32_t handle = glCreateShader(type);
	// exit if no handle returned
	if (handle == 0) return 0;

	// shader source
	auto shaderSource = StringTools::replace(
		StringTools::replace(
			FileSystem::getInstance()->getContentAsString(pathName, fileName),
			"{$DEFINITIONS}",
			definitions + "\n\n"
		),
		"{$FUNCTIONS}",
		functions + "\n\n"
	);
	string sourceString = (shaderSource);
	char* sourceHeap = new char[sourceString.length() + 1];
	strcpy(sourceHeap, sourceString.c_str());
	// load source
	glShaderSource(handle, 1, &sourceHeap, nullptr);
	// compile
	glCompileShader(handle);
	//
	delete [] sourceHeap;
	// check state
	int32_t compileStatus;
	glGetShaderiv(handle, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == 0) {
		// get error
		int32_t infoLogLengthBuffer;
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &infoLogLengthBuffer);
		char* infoLogBuffer = new char[infoLogLengthBuffer];
		glGetShaderInfoLog(handle, infoLogLengthBuffer, &infoLogLengthBuffer, infoLogBuffer);
		auto infoLogString = (string(infoLogBuffer, infoLogLengthBuffer));
		// be verbose
		Console::println(
			string(
				string("GL3Renderer::loadShader") +
				string("[") +
				to_string(handle) +
				string("]") +
				pathName +
				string("/") +
				fileName +
				string(": failed: ") +
				infoLogString
			 )
		 );
		Console::println(shaderSource);
		//
		delete [] infoLogBuffer;
		// remove shader
		glDeleteShader(handle);
		return 0;
	}

	return handle;
}

void GL3Renderer::useProgram(int contextIdx, int32_t programId)
{
	glUseProgram(programId);
}

int32_t GL3Renderer::createProgram(int type)
{
	auto glProgram = glCreateProgram();
	return glProgram;
}

void GL3Renderer::attachShaderToProgram(int32_t programId, int32_t shaderId)
{
	glAttachShader(programId, shaderId);
}

bool GL3Renderer::linkProgram(int32_t programId)
{
	glLinkProgram(programId);
	// check state
	int32_t linkStatus;
	glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == 0) {
		// get error
		int32_t infoLogLength = 0;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];
		glGetProgramInfoLog(programId, infoLogLength, &infoLogLength, infoLog);
		auto infoLogString = (string(infoLog, infoLogLength));
		// be verbose
		Console::println(
			string(
				"[" +
				to_string(programId) +
				"]: failed: " +
				infoLogString
			 )
		);
		//
		delete [] infoLog;
		//
		return false;
	}
	return true;
}

int32_t GL3Renderer::getProgramUniformLocation(int32_t programId, const string& name)
{
	auto uniformLocation = glGetUniformLocation(programId, (name).c_str());
	return uniformLocation;
}

void GL3Renderer::setProgramUniformInteger(int contextIdx, int32_t uniformId, int32_t value)
{
	#if defined (__APPLE__) && !defined(__aarch64__)
		if (uniformId == UNIFORM_CL_SKINNING_VERTEX_COUNT) {
			clSkinningParameters.vertexCount = value;
		} else
		if (uniformId == UNIFORM_CL_SKINNING_MATRIX_COUNT) {
			clSkinningParameters.matrixCount = value;
		} else
		if (uniformId == UNIFORM_CL_SKINNING_INSTANCE_COUNT) {
			clSkinningParameters.instanceCount = value;
		} else {
			glUniform1i(uniformId, value);
		}
	#else
		glUniform1i(uniformId, value);
	#endif
}

void GL3Renderer::setProgramUniformFloat(int contextIdx, int32_t uniformId, float value)
{
	glUniform1f(uniformId, value);
}

void GL3Renderer::setProgramUniformFloatMatrix3x3(int contextIdx, int32_t uniformId, const array<float, 9>& data)
{
	glUniformMatrix3fv(uniformId, 1, false, data.data());
}

void GL3Renderer::setProgramUniformFloatMatrix4x4(int contextIdx, int32_t uniformId, const array<float, 16>& data)
{
	glUniformMatrix4fv(uniformId, 1, false, data.data());
}

void GL3Renderer::setProgramUniformFloatMatrices4x4(int contextIdx, int32_t uniformId, int32_t count, FloatBuffer* data)
{
	glUniformMatrix4fv(uniformId, count, false, (float*)data->getBuffer());
}

void GL3Renderer::setProgramUniformFloatVec4(int contextIdx, int32_t uniformId, const array<float, 4>& data)
{
	glUniform4fv(uniformId, 1, data.data());
}

void GL3Renderer::setProgramUniformFloatVec3(int contextIdx, int32_t uniformId, const array<float, 3>& data)
{
	glUniform3fv(uniformId, 1, data.data());
}

void GL3Renderer::setProgramUniformFloatVec2(int contextIdx, int32_t uniformId, const array<float, 2>& data)
{
	glUniform2fv(uniformId, 1, data.data());
}

void GL3Renderer::setProgramAttributeLocation(int32_t programId, int32_t location, const string& name)
{
	glBindAttribLocation(programId, location, (name).c_str());
}

void GL3Renderer::setViewPort(int32_t width, int32_t height)
{
	this->viewPortWidth = width;
	this->viewPortHeight = height;
}

void GL3Renderer::updateViewPort()
{
	glViewport(0, 0, viewPortWidth, viewPortHeight);
}

void GL3Renderer::setClearColor(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
}

void GL3Renderer::enableCulling(int contextIdx)
{
	glEnable(GL_CULL_FACE);
}

void GL3Renderer::disableCulling(int contextIdx)
{
	glDisable(GL_CULL_FACE);
}

void GL3Renderer::setFrontFace(int contextIdx, int32_t frontFace)
{
	glFrontFace(frontFace);
}

void GL3Renderer::setCullFace(int32_t cullFace)
{
	glCullFace(cullFace);
}

void GL3Renderer::enableBlending()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

void GL3Renderer::enableAdditionBlending() {
	glBlendFunc(GL_ONE, GL_ONE);
	glEnable(GL_BLEND);
}

void GL3Renderer::disableBlending()
{
	glDisable(GL_BLEND);
}

void GL3Renderer::enableDepthBufferWriting()
{
	glDepthMask(true);
}

void GL3Renderer::disableDepthBufferWriting()
{
	glDepthMask(false);
}

void GL3Renderer::disableDepthBufferTest()
{
	glDisable(GL_DEPTH_TEST);
}

void GL3Renderer::enableDepthBufferTest()
{
	glEnable(GL_DEPTH_TEST);
}

void GL3Renderer::setDepthFunction(int32_t depthFunction)
{
	// TODO: remove me
	glDepthFunc(depthFunction);
}

void GL3Renderer::setColorMask(bool red, bool green, bool blue, bool alpha)
{
	glColorMask(red, green, blue, alpha);
}

void GL3Renderer::clear(int32_t mask)
{
	glClear(mask);
	statistics.clearCalls++;
}

int32_t GL3Renderer::createTexture()
{
	// generate open gl texture
	uint32_t textureId;
	glGenTextures(1, &textureId);
	return textureId;
}

int32_t GL3Renderer::createDepthBufferTexture(int32_t width, int32_t height, int32_t cubeMapTextureId, int32_t cubeMapTextureIndex)
{
	uint32_t depthTextureId;
	// create depth texture
	glGenTextures(1, &depthTextureId);
	glBindTexture(GL_TEXTURE_2D, depthTextureId);
	// create depth texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	// depth texture parameter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// unbind, return
	glBindTexture(GL_TEXTURE_2D, ID_NONE);
	return depthTextureId;
}

int32_t GL3Renderer::createColorBufferTexture(int32_t width, int32_t height, int32_t cubeMapTextureId, int32_t cubeMapTextureIndex)
{
	uint32_t colorBufferTextureId;
	// create color texture
	glGenTextures(1, &colorBufferTextureId);
	glBindTexture(GL_TEXTURE_2D, colorBufferTextureId);
	// create color texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	// color texture parameter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// unbind, return
	glBindTexture(GL_TEXTURE_2D, ID_NONE);
	return colorBufferTextureId;
}

int32_t GL3Renderer::createGBufferGeometryTexture(int32_t width, int32_t height) {
	uint32_t gBufferGeometryTextureId;
	glGenTextures(1, &gBufferGeometryTextureId);
	glBindTexture(GL_TEXTURE_2D, gBufferGeometryTextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, ID_NONE);
	return gBufferGeometryTextureId;
}

int32_t GL3Renderer::createGBufferColorTexture(int32_t width, int32_t height) {
	uint32_t gBufferColorTextureId;
	glGenTextures(1, &gBufferColorTextureId);
	glBindTexture(GL_TEXTURE_2D, gBufferColorTextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, ID_NONE);
	return gBufferColorTextureId;
}

void GL3Renderer::uploadTexture(int contextIdx, Texture* texture)
{
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		texture->getDepth() > 32?(texture->getDepth() == 64?GL_RGBA:GL_RGB):(texture->getDepth() == 32?GL_RGBA:GL_RGB),
		texture->getTextureWidth(),
		texture->getTextureHeight(),
		0,
		texture->getDepth() > 32?(texture->getDepth() == 64?GL_RGBA:GL_RGB):(texture->getDepth() == 32?GL_RGBA:GL_RGB),
		texture->getDepth() > 32?GL_UNSIGNED_SHORT:GL_UNSIGNED_BYTE,
		texture->getTextureData()->getBuffer()
	);
	if (texture->getAtlasSize() > 1) {
		if (texture->isUseMipMap() == true) {
			float maxLodBias;
			glGetFloatv(GL_MAX_TEXTURE_LOD_BIAS, &maxLodBias);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -Math::clamp(static_cast<float>(texture->getAtlasSize()) * 0.125f, 0.0f, maxLodBias));
			auto borderSize = 32;
			auto maxLevel = 0;
			while (borderSize > 4) {
				maxLevel++;
				borderSize/= 2;
			}
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, maxLevel - 1);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	} else {
		if (texture->isUseMipMap() == true) glGenerateMipmap(GL_TEXTURE_2D);
		if (texture->isRepeat() == true) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		} else {
			float color[4] = {0.0f, 0.0f, 0.0f, 0.0f};
			if (texture->getClampMode() == Texture::CLAMPMODE_TRANSPARENTPIXEL) glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture->getClampMode() == Texture::CLAMPMODE_EDGE?GL_CLAMP_TO_EDGE:GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture->getClampMode() == Texture::CLAMPMODE_EDGE?GL_CLAMP_TO_EDGE:GL_CLAMP_TO_BORDER);
		}
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture->isUseMipMap() == true?GL_LINEAR_MIPMAP_LINEAR:GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	statistics.textureUploads++;
}

void GL3Renderer::uploadCubeMapTexture(int contextIdx, Texture* textureLeft, Texture* textureRight, Texture* textureTop, Texture* textureBottom, Texture* textureFront, Texture* textureBack) {
	glTexImage2D(
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		0,
		textureLeft->getDepth() > 32?(textureLeft->getDepth() == 64?GL_RGBA:GL_RGB):(textureLeft->getDepth() == 32?GL_RGBA:GL_RGB),
		textureLeft->getTextureWidth(),
		textureLeft->getTextureHeight(),
		0,
		textureLeft->getDepth() > 32?(textureLeft->getDepth() == 64?GL_RGBA:GL_RGB):(textureLeft->getDepth() == 32?GL_RGBA:GL_RGB),
		textureLeft->getDepth() > 32?GL_UNSIGNED_SHORT:GL_UNSIGNED_BYTE,
		textureLeft->getTextureData()->getBuffer()
	);
	glTexImage2D(
		GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		0,
		textureRight->getDepth() > 32?(textureRight->getDepth() == 64?GL_RGBA:GL_RGB):(textureRight->getDepth() == 32?GL_RGBA:GL_RGB),
		textureRight->getTextureWidth(),
		textureRight->getTextureHeight(),
		0,
		textureRight->getDepth() > 32?(textureRight->getDepth() == 64?GL_RGBA:GL_RGB):(textureRight->getDepth() == 32?GL_RGBA:GL_RGB),
		textureRight->getDepth() > 32?GL_UNSIGNED_SHORT:GL_UNSIGNED_BYTE,
		textureRight->getTextureData()->getBuffer()
	);
	glTexImage2D(
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		0,
		textureTop->getDepth() > 32?(textureTop->getDepth() == 64?GL_RGBA:GL_RGB):(textureTop->getDepth() == 32?GL_RGBA:GL_RGB),
		textureTop->getTextureWidth(),
		textureTop->getTextureHeight(),
		0,
		textureTop->getDepth() > 32?(textureTop->getDepth() == 64?GL_RGBA:GL_RGB):(textureTop->getDepth() == 32?GL_RGBA:GL_RGB),
		textureTop->getDepth() > 32?GL_UNSIGNED_SHORT:GL_UNSIGNED_BYTE,
		textureTop->getTextureData()->getBuffer()
	);
	glTexImage2D(
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		0,
		textureBottom->getDepth() > 32?(textureBottom->getDepth() == 64?GL_RGBA:GL_RGB):(textureBottom->getDepth() == 32?GL_RGBA:GL_RGB),
		textureBottom->getTextureWidth(),
		textureBottom->getTextureHeight(),
		0,
		textureBottom->getDepth() > 32?(textureBottom->getDepth() == 64?GL_RGBA:GL_RGB):(textureBottom->getDepth() == 32?GL_RGBA:GL_RGB),
		textureBottom->getDepth() > 32?GL_UNSIGNED_SHORT:GL_UNSIGNED_BYTE,
		textureBottom->getTextureData()->getBuffer()
	);
	glTexImage2D(
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		0,
		textureFront->getDepth() > 32?(textureFront->getDepth() == 64?GL_RGBA:GL_RGB):(textureFront->getDepth() == 32?GL_RGBA:GL_RGB),
		textureFront->getTextureWidth(),
		textureFront->getTextureHeight(),
		0,
		textureFront->getDepth() > 32?(textureFront->getDepth() == 64?GL_RGBA:GL_RGB):(textureFront->getDepth() == 32?GL_RGBA:GL_RGB),
		textureFront->getDepth() > 32?GL_UNSIGNED_SHORT:GL_UNSIGNED_BYTE,
		textureFront->getTextureData()->getBuffer()
	);
	glTexImage2D(
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
		0,
		textureBack->getDepth() > 32?(textureBack->getDepth() == 64?GL_RGBA:GL_RGB):(textureBack->getDepth() == 32?GL_RGBA:GL_RGB),
		textureBack->getTextureWidth(),
		textureBack->getTextureHeight(),
		0,
		textureBack->getDepth() > 32?(textureBack->getDepth() == 64?GL_RGBA:GL_RGB):(textureBack->getDepth() == 32?GL_RGBA:GL_RGB),
		textureBack->getDepth() > 32?GL_UNSIGNED_SHORT:GL_UNSIGNED_BYTE,
		textureBack->getTextureData()->getBuffer()
	);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	statistics.textureUploads+= 6;
}

int32_t GL3Renderer::createCubeMapTexture(int contextIdx, int32_t width, int32_t height) {
	// generate open gl texture
	uint32_t textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		0,
		GL_RGBA,
		width,
		height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		nullptr
	);
	glTexImage2D(
		GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		0,
		GL_RGBA,
		width,
		height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		nullptr
	);
	glTexImage2D(
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		0,
		GL_RGBA,
		width,
		height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		nullptr
	);
	glTexImage2D(
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		0,
		GL_RGBA,
		width,
		height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		nullptr
	);
	glTexImage2D(
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		0,
		GL_RGBA,
		width,
		height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		nullptr
	);
	glTexImage2D(
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
		0,
		GL_RGBA,
		width,
		height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		nullptr
	);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	return textureId;
}

void GL3Renderer::resizeDepthBufferTexture(int32_t textureId, int32_t width, int32_t height)
{
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GL3Renderer::resizeColorBufferTexture(int32_t textureId, int32_t width, int32_t height)
{
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GL3Renderer::resizeGBufferGeometryTexture(int32_t textureId, int32_t width, int32_t height) {
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GL3Renderer::resizeGBufferColorTexture(int32_t textureId, int32_t width, int32_t height) {
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GL3Renderer::bindTexture(int contextIdx, int32_t textureId)
{
	glBindTexture(GL_TEXTURE_2D, textureId);
	onBindTexture(contextIdx, textureId);
}

void GL3Renderer::bindCubeMapTexture(int contextIdx, int32_t textureId) {
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
	onBindTexture(contextIdx, textureId);
}

void GL3Renderer::disposeTexture(int32_t textureId)
{
	glDeleteTextures(1, (const uint32_t*)&textureId);
	statistics.disposedTextures++;
}

int32_t GL3Renderer::createFramebufferObject(int32_t depthBufferTextureId, int32_t colorBufferTextureId, int32_t cubeMapTextureId, int32_t cubeMapTextureIndex)
{
	uint32_t frameBufferId;
	// create a frame buffer object
	glGenFramebuffers(1, &frameBufferId);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);
	// attach the depth buffer texture to FBO
	if (depthBufferTextureId != ID_NONE) {
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthBufferTextureId, 0);
	}
	// attach the depth buffer texture to FBO
	if (colorBufferTextureId != ID_NONE) {
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colorBufferTextureId, 0);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		glReadBuffer(GL_COLOR_ATTACHMENT0);
	} else
	if (cubeMapTextureId != ID_NONE) {
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, cubeMapTextureIndex, cubeMapTextureId, 0);
	} else {
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}
	// check FBO status
	int32_t fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (fboStatus != GL_FRAMEBUFFER_COMPLETE) {
		Console::println(string("GL_FRAMEBUFFER_COMPLETE_EXT failed, CANNOT use FBO: "+ to_string(fboStatus)));
	}
	// switch back to window-system-provided framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return frameBufferId;
}

int32_t GL3Renderer::createGeometryBufferObject(
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
	uint32_t frameBufferId;
	// create a frame buffer object
	glGenFramebuffers(1, &frameBufferId);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);
	// attach the depth buffer texture to FBO
	if (depthBufferTextureId != ID_NONE) {
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthBufferTextureId, 0);
	}
	vector<uint32_t> drawBuffers;
	// attach geometry textures
	if (geometryBufferTextureId1 != ID_NONE) {
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, geometryBufferTextureId1, 0);
		drawBuffers.push_back(GL_COLOR_ATTACHMENT0);
	}
	if (geometryBufferTextureId2 != ID_NONE) {
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, geometryBufferTextureId2, 0);
		drawBuffers.push_back(GL_COLOR_ATTACHMENT1);
	}
	if (geometryBufferTextureId3 != ID_NONE) {
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, geometryBufferTextureId3, 0);
		drawBuffers.push_back(GL_COLOR_ATTACHMENT2);
	}
	// attach color textures
	if (colorBufferTextureId1 != ID_NONE) {
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, colorBufferTextureId1, 0);
		drawBuffers.push_back(GL_COLOR_ATTACHMENT3);
	}
	if (colorBufferTextureId2 != ID_NONE) {
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, colorBufferTextureId2, 0);
		drawBuffers.push_back(GL_COLOR_ATTACHMENT4);
	}
	if (colorBufferTextureId3 != ID_NONE) {
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT5, colorBufferTextureId3, 0);
		drawBuffers.push_back(GL_COLOR_ATTACHMENT5);
	}
	if (colorBufferTextureId4 != ID_NONE) {
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT6, colorBufferTextureId4, 0);
		drawBuffers.push_back(GL_COLOR_ATTACHMENT6);
	}
	if (colorBufferTextureId5 != ID_NONE) {
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT7, colorBufferTextureId5, 0);
		drawBuffers.push_back(GL_COLOR_ATTACHMENT7);
	}
	//
	glDrawBuffers(drawBuffers.size(), drawBuffers.data());
	// check FBO status
	int32_t fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (fboStatus != GL_FRAMEBUFFER_COMPLETE) {
		Console::println(string("GL_FRAMEBUFFER_COMPLETE_EXT failed, CANNOT use FBO: "+ to_string(fboStatus)));
	}
	// switch back to window-system-provided framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return frameBufferId;
}

void GL3Renderer::bindFrameBuffer(int32_t frameBufferId)
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);
}

void GL3Renderer::disposeFrameBufferObject(int32_t frameBufferId)
{
	glDeleteFramebuffers(1, (uint32_t*)&frameBufferId);
}

vector<int32_t> GL3Renderer::createBufferObjects(int32_t buffers, bool useGPUMemory, bool shared)
{
	vector<int32_t> bufferObjectIds;
	bufferObjectIds.resize(buffers);
	glGenBuffers(buffers, (uint32_t*)bufferObjectIds.data());
	for (auto bufferObjectId: bufferObjectIds) vbosUsage[bufferObjectId] = useGPUMemory == true?GL_STATIC_DRAW:GL_STREAM_DRAW;
	return bufferObjectIds;
}

void GL3Renderer::uploadBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, FloatBuffer* data)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glBufferData(GL_ARRAY_BUFFER, size, data->getBuffer(), vbosUsage[bufferObjectId]);
	glBindBuffer(GL_ARRAY_BUFFER, ID_NONE);
	statistics.bufferUploads++;
}

void GL3Renderer::uploadBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, ShortBuffer* data)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glBufferData(GL_ARRAY_BUFFER, size, data->getBuffer(), vbosUsage[bufferObjectId]);
	glBindBuffer(GL_ARRAY_BUFFER, ID_NONE);
	statistics.bufferUploads++;
}

void GL3Renderer::uploadBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, IntBuffer* data)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glBufferData(GL_ARRAY_BUFFER, size, data->getBuffer(), vbosUsage[bufferObjectId]);
	glBindBuffer(GL_ARRAY_BUFFER, ID_NONE);
	statistics.bufferUploads++;
}

void GL3Renderer::uploadIndicesBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, ShortBuffer* data)
{
	Console::println(string("GL3Renderer::uploadIndicesBufferObject()::not implemented yet"));
}

void GL3Renderer::uploadIndicesBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, IntBuffer* data)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObjectId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data->getBuffer(), vbosUsage[bufferObjectId]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID_NONE);
	statistics.bufferUploads++;
}

void GL3Renderer::bindIndicesBufferObject(int contextIdx, int32_t bufferObjectId)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObjectId);
}

void GL3Renderer::bindSolidColorsBufferObject(int contextIdx, int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 1, GL_FLOAT, false, 0, 0LL);
}

void GL3Renderer::bindTextureCoordinatesBufferObject(int contextIdx, int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, 0LL);
}

void GL3Renderer::bindVerticesBufferObject(int contextIdx, int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0LL);
}

void GL3Renderer::bindVertices2BufferObject(int contextIdx, int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0LL);
}

void GL3Renderer::bindNormalsBufferObject(int contextIdx, int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, 0LL);
}

void GL3Renderer::bindColorsBufferObject(int contextIdx, int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, false, 0, 0LL);
}

void GL3Renderer::bindTangentsBufferObject(int contextIdx, int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, false, 0, 0LL);
}

void GL3Renderer::bindBitangentsBufferObject(int contextIdx, int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 3, GL_FLOAT, false, 0, 0LL);
}

void GL3Renderer::bindModelMatricesBufferObject(int contextIdx, int32_t bufferObjectId) {
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(6);
	glEnableVertexAttribArray(7);
	glEnableVertexAttribArray(8);
	glEnableVertexAttribArray(9);
	glVertexAttribPointer(6, 4, GL_FLOAT, false, 4 * 4 * sizeof(float), (void*)(0 * 4 * sizeof(float)));
	glVertexAttribPointer(7, 4, GL_FLOAT, false, 4 * 4 * sizeof(float), (void*)(1 * 4 * sizeof(float)));
	glVertexAttribPointer(8, 4, GL_FLOAT, false, 4 * 4 * sizeof(float), (void*)(2 * 4 * sizeof(float)));
	glVertexAttribPointer(9, 4, GL_FLOAT, false, 4 * 4 * sizeof(float), (void*)(3 * 4 * sizeof(float)));
	glVertexAttribDivisor(6, 1);
	glVertexAttribDivisor(7, 1);
	glVertexAttribDivisor(8, 1);
	glVertexAttribDivisor(9, 1);
}

void GL3Renderer::bindEffectColorMulsBufferObject(int contextIdx, int32_t bufferObjectId, int32_t divisor) {
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(10);
	glVertexAttribPointer(10, 4, GL_FLOAT, false, 0, 0LL);
	glVertexAttribDivisor(10, divisor);
}

void GL3Renderer::bindEffectColorAddsBufferObject(int contextIdx, int32_t bufferObjectId, int32_t divisor) {
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(11);
	glVertexAttribPointer(11, 4, GL_FLOAT, false, 0, 0LL);
	glVertexAttribDivisor(11, divisor);
}

void GL3Renderer::bindOriginsBufferObject(int contextIdx, int32_t bufferObjectId) {
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(12);
	glVertexAttribPointer(12, 3, GL_FLOAT, false, 0, 0LL);
}

void GL3Renderer::bindTextureSpriteIndicesBufferObject(int contextIdx, int32_t bufferObjectId) {
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(1);
	glVertexAttribIPointer(1, 2, GL_UNSIGNED_SHORT, 0, 0LL);
}

void GL3Renderer::bindPointSizesBufferObject(int contextIdx, int32_t bufferObjectId) {
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 1, GL_FLOAT, false, 0, 0LL);
}

void GL3Renderer::bindSpriteSheetDimensionBufferObject(int contextIdx, int32_t bufferObjectId) {
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(6);
	glVertexAttribIPointer(6, 2, GL_UNSIGNED_SHORT, 0, 0LL);
	glVertexAttribDivisor(6, 0);
}

void GL3Renderer::drawInstancedIndexedTrianglesFromBufferObjects(int contextIdx, int32_t triangles, int32_t trianglesOffset, int32_t instances)
{
	#define BUFFER_OFFSET(i) ((void*)(i))
	glDrawElementsInstanced(GL_TRIANGLES, triangles * 3, GL_UNSIGNED_INT, BUFFER_OFFSET(static_cast< int64_t >(trianglesOffset) * 3LL * 4LL), instances);
	statistics.renderCalls++;
	statistics.instances+= instances;
	statistics.triangles+= triangles * instances;
}

void GL3Renderer::drawIndexedTrianglesFromBufferObjects(int contextIdx, int32_t triangles, int32_t trianglesOffset)
{
	#define BUFFER_OFFSET(i) ((void*)(i))
	glDrawElements(GL_TRIANGLES, triangles * 3, GL_UNSIGNED_INT, BUFFER_OFFSET(static_cast< int64_t >(trianglesOffset) * 3LL * 4LL));
	statistics.renderCalls++;
	statistics.instances+= 1;
	statistics.triangles+= triangles;
}

void GL3Renderer::drawInstancedTrianglesFromBufferObjects(int contextIdx, int32_t triangles, int32_t trianglesOffset, int32_t instances) {
	glDrawArraysInstanced(GL_TRIANGLES, trianglesOffset * 3, triangles * 3, instances);
	statistics.renderCalls++;
	statistics.instances+= instances;
	statistics.triangles+= triangles * instances;
}

void GL3Renderer::drawTrianglesFromBufferObjects(int contextIdx, int32_t triangles, int32_t trianglesOffset)
{
	glDrawArrays(GL_TRIANGLES, trianglesOffset * 3, triangles * 3);
	statistics.renderCalls++;
	statistics.instances+= 1;
	statistics.triangles+= triangles;
}

void GL3Renderer::drawPointsFromBufferObjects(int contextIdx, int32_t points, int32_t pointsOffset)
{
	glDrawArrays(GL_POINTS, pointsOffset, points);
	statistics.renderCalls++;
	statistics.points+= points;
}

void GL3Renderer::setLineWidth(float lineWidth)
{
	glLineWidth(lineWidth);
}

void GL3Renderer::drawLinesFromBufferObjects(int contextIdx, int32_t points, int32_t pointsOffset)
{
	glDrawArrays(GL_LINES, pointsOffset, points);
	statistics.renderCalls++;
	statistics.linePoints+= points;
}

void GL3Renderer::unbindBufferObjects(int contextIdx)
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);
	glDisableVertexAttribArray(6);
	glDisableVertexAttribArray(7);
	glDisableVertexAttribArray(8);
	glDisableVertexAttribArray(9);
	glDisableVertexAttribArray(10);
	glDisableVertexAttribArray(11);
	glDisableVertexAttribArray(12);
	glBindBuffer(GL_ARRAY_BUFFER, ID_NONE);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID_NONE);
}

void GL3Renderer::disposeBufferObjects(vector<int32_t>& bufferObjectIds)
{
	for (auto& bufferObjectId: bufferObjectIds) vbosUsage.erase(bufferObjectId);
	glDeleteBuffers(bufferObjectIds.size(), (const uint32_t*)bufferObjectIds.data());
	statistics.disposedBuffers+= bufferObjectIds.size();
}

int32_t GL3Renderer::getTextureUnit(int contextIdx)
{
	return activeTextureUnit;
}

void GL3Renderer::setTextureUnit(int contextIdx, int32_t textureUnit)
{
	this->activeTextureUnit = textureUnit;
	glActiveTexture(GL_TEXTURE0 + textureUnit);
}

float GL3Renderer::readPixelDepth(int32_t x, int32_t y)
{
	float depth;
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
	return depth;
}

ByteBuffer* GL3Renderer::readPixels(int32_t x, int32_t y, int32_t width, int32_t height)
{
	auto pixelBuffer = ByteBuffer::allocate(width * height * 4);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixelBuffer->getBuffer());
	return pixelBuffer;
}

void GL3Renderer::initGuiMode()
{
	setTextureUnit(CONTEXTINDEX_DEFAULT, 0);
	glBindTexture(GL_TEXTURE_2D, ID_NONE);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glGetError();
}

void GL3Renderer::doneGuiMode()
{
	glGetError();
	glBindTexture(GL_TEXTURE_2D, ID_NONE);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

void GL3Renderer::checkGLError(int line)
{
	auto error = glGetError();
	if (error != GL_NO_ERROR) {
		Console::println(string("OpenGL Error: (" + to_string(error) + ") @: " + __FILE__ + ":" + to_string(line)));
	}
}

void GL3Renderer::dispatchCompute(int contextIdx, int32_t numGroupsX, int32_t numGroupsY, int32_t numGroupsZ) {
	#if defined (__APPLE__) && !defined(__aarch64__)
		clSkinningParameters.numGroupsX = numGroupsX;
		clSkinningParameters.numGroupsY = numGroupsY;
		glFinish();
		auto& _clSkinningParameters = clSkinningParameters;
		cl_int clError;
		array<cl_mem, 8> boundCLMemObjects;
		for (auto i = 0; i < _clSkinningParameters.boundGLBuffers.size(); i++) {
			boundCLMemObjects[i] = clCreateFromGLBuffer(clContext, _clSkinningParameters.boundGLBuffersWrite[i] == true?CL_MEM_WRITE_ONLY:CL_MEM_READ_ONLY, _clSkinningParameters.boundGLBuffers[i], &clError);
			clError = clSetKernelArg(clSkinningKernel, i, sizeof(cl_mem), &boundCLMemObjects[i]);
		}
		clSetKernelArg(clSkinningKernel, 8, sizeof(cl_int), &_clSkinningParameters.vertexCount);
		clSetKernelArg(clSkinningKernel, 9, sizeof(cl_int), &_clSkinningParameters.matrixCount);
		clSetKernelArg(clSkinningKernel, 10, sizeof(cl_int), &_clSkinningParameters.instanceCount);
		size_t local_size[] = {(size_t)16, (size_t)16};
		size_t global_size[] = {(size_t)_clSkinningParameters.numGroupsX * local_size[0], (size_t)_clSkinningParameters.numGroupsY  * local_size[1]};
		clEnqueueAcquireGLObjects(clCommandQueue, boundCLMemObjects.size(), boundCLMemObjects.data(), 0, nullptr, nullptr);
		clEnqueueNDRangeKernel(clCommandQueue, clSkinningKernel, 2, nullptr, global_size, local_size, 0, nullptr, nullptr);
		clEnqueueReleaseGLObjects(clCommandQueue, boundCLMemObjects.size(), boundCLMemObjects.data(), 0, nullptr, nullptr);
		clFinish(clCommandQueue);
		clSkinningParameters = CLSkinningParameters();
		statistics.computeCalls++;
	#elif !defined(__APPLE__)
		glDispatchCompute(numGroupsX, numGroupsY, numGroupsZ);
		statistics.computeCalls++;
	#endif
}

void GL3Renderer::memoryBarrier() {
	#if defined (__APPLE__)
		// no op
	#else
		// TODO: put barrier bits into paramters
		glMemoryBarrier(GL_ALL_BARRIER_BITS);
	#endif
}

void GL3Renderer::uploadSkinningBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, FloatBuffer* data) {
	#if defined (__APPLE__) && !defined(__aarch64__)
		glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
		glBufferData(GL_ARRAY_BUFFER, size, data->getBuffer(), vbosUsage[bufferObjectId]);
		glBindBuffer(GL_ARRAY_BUFFER, ID_NONE);
		statistics.bufferUploads++;
	#elif !defined(__APPLE__)
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, bufferObjectId);
		glBufferData(GL_SHADER_STORAGE_BUFFER, size, data->getBuffer(), vbosUsage[bufferObjectId]);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, ID_NONE);
		statistics.bufferUploads++;
	#endif
}

void GL3Renderer::uploadSkinningBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, IntBuffer* data) {
	#if defined (__APPLE__) && !defined(__aarch64__)
		glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
		glBufferData(GL_ARRAY_BUFFER, size, data->getBuffer(), vbosUsage[bufferObjectId]);
		glBindBuffer(GL_ARRAY_BUFFER, ID_NONE);
		statistics.bufferUploads++;
	#elif !defined(__APPLE__)
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, bufferObjectId);
		glBufferData(GL_SHADER_STORAGE_BUFFER, size, data->getBuffer(), vbosUsage[bufferObjectId]);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, ID_NONE);
		statistics.bufferUploads++;
	#endif
}

#if defined (__APPLE__) && !defined(__aarch64__)
	inline void GL3Renderer::clBindGLBuffer(int32_t idx, int32_t bufferObjectId, bool write) {
		clSkinningParameters.boundGLBuffers[idx] = bufferObjectId;
		clSkinningParameters.boundGLBuffersWrite[idx] = write;
	}
#endif

void GL3Renderer::bindSkinningVerticesBufferObject(int contextIdx, int32_t bufferObjectId) {
	#if defined (__APPLE__) && !defined(__aarch64__)
		clBindGLBuffer(0, bufferObjectId, false);
	#elif !defined(__APPLE__)
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, bufferObjectId);
	#endif
}

void GL3Renderer::bindSkinningNormalsBufferObject(int contextIdx, int32_t bufferObjectId) {
	#if defined (__APPLE__) && !defined(__aarch64__)
		clBindGLBuffer(1, bufferObjectId, false);
	#elif !defined(__APPLE__)
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, bufferObjectId);
	#endif
}

void GL3Renderer::bindSkinningVertexJointsBufferObject(int contextIdx, int32_t bufferObjectId) {
	#if defined (__APPLE__) && !defined(__aarch64__)
		clBindGLBuffer(2, bufferObjectId, false);
	#elif !defined(__APPLE__)
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, bufferObjectId);
	#endif
}

void GL3Renderer::bindSkinningVertexJointIdxsBufferObject(int contextIdx, int32_t bufferObjectId) {
	#if defined (__APPLE__) && !defined(__aarch64__)
		clBindGLBuffer(3, bufferObjectId, false);
	#elif !defined(__APPLE__)
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, bufferObjectId);
	#endif
}

void GL3Renderer::bindSkinningVertexJointWeightsBufferObject(int contextIdx, int32_t bufferObjectId) {
	#if defined (__APPLE__) && !defined(__aarch64__)
		clBindGLBuffer(4, bufferObjectId, false);
	#elif !defined(__APPLE__)
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, bufferObjectId);
	#endif
}

void GL3Renderer::bindSkinningVerticesResultBufferObject(int contextIdx, int32_t bufferObjectId) {
	#if defined (__APPLE__) && !defined(__aarch64__)
		clBindGLBuffer(5, bufferObjectId, true);
	#elif !defined(__APPLE__)
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, bufferObjectId);
	#endif
}

void GL3Renderer::bindSkinningNormalsResultBufferObject(int contextIdx, int32_t bufferObjectId) {
	#if defined (__APPLE__) && !defined(__aarch64__)
		clBindGLBuffer(6, bufferObjectId, true);
	#elif !defined(__APPLE__)
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, bufferObjectId);
	#endif
}

void GL3Renderer::bindSkinningMatricesBufferObject(int contextIdx, int32_t bufferObjectId) {
	#if defined (__APPLE__) && !defined(__aarch64__)
		clBindGLBuffer(7, bufferObjectId, false);
	#elif !defined(__APPLE__)
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 7, bufferObjectId);
	#endif
}

void GL3Renderer::setVSync(bool vSync) {
	// no op
}

const Renderer::Renderer_Statistics GL3Renderer::getStatistics() {
	auto stats = statistics;
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
