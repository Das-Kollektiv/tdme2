#include <tdme/engine/subsystems/renderer/GLES2Renderer.h>

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>

#include <string.h>

#include <array>
#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/FrameBuffer.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Buffer.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/FloatBuffer.h>
#include <tdme/utilities/IntBuffer.h>
#include <tdme/utilities/ShortBuffer.h>
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/Time.h>

using std::array;
using std::map;
using std::string;
using std::to_string;
using std::vector;

using tdme::engine::subsystems::renderer::GLES2Renderer;

using tdme::engine::fileio::textures::Texture;
using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
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

GLES2Renderer::GLES2Renderer()
{
	rendererType = RENDERERTYPE_OPENGLES;
	// setup GLES2 consts
	ID_NONE = 0;
	CLEAR_DEPTH_BUFFER_BIT = GL_DEPTH_BUFFER_BIT;
	CLEAR_COLOR_BUFFER_BIT = GL_COLOR_BUFFER_BIT;
	CULLFACE_FRONT = GL_FRONT;
	CULLFACE_BACK = GL_BACK;
	FRONTFACE_CW = GL_CW;
	FRONTFACE_CCW = GL_CCW;
	SHADER_FRAGMENT_SHADER = GL_FRAGMENT_SHADER;
	SHADER_VERTEX_SHADER = GL_VERTEX_SHADER;
	SHADER_COMPUTE_SHADER = -1;
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
}

const string GLES2Renderer::getVendor() {
	auto vendor = (char*)glGetString(GL_VENDOR);
	return string(vendor);
}

const string GLES2Renderer::getRenderer() {
	auto renderer = (char*)glGetString(GL_RENDERER);
	return string(renderer) + " [GLES2]";
}

const string GLES2Renderer::getShaderVersion()
{
	return "gl2";
}

bool GLES2Renderer::isSupportingMultithreadedRendering() {
	return false;
}

void GLES2Renderer::initialize()
{
	glGetError();
	// get default framebuffer
	FRAMEBUFFER_DEFAULT = 0; // getContext()->getDefaultDrawFramebuffer();
	checkGLError();
	// setup open gl
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepthf(1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LEQUAL);
	glBlendEquation(GL_FUNC_ADD);
	glDisable(GL_BLEND);
	// renderer contexts
	rendererContexts.resize(1);
	for (auto& rendererContext: rendererContexts) {
		for (auto i = 0; i < rendererContext.lights.size(); i++) {
			rendererContext.lights[i].spotCosCutoff = static_cast<float>(Math::cos(Math::PI / 180.0f * 180.0f));
		}
		rendererContext.textureMatrix.identity();
	}
}

void GLES2Renderer::initializeFrame()
{
}

void GLES2Renderer::finishFrame()
{
}

bool GLES2Renderer::isBufferObjectsAvailable()
{
	return true;
}

bool GLES2Renderer::isDepthTextureAvailable()
{
	// return glGetString(GL::GL_EXTENSIONS)->indexOf(u"GL_OES_depth_texture"_j) != -1;
	return true;
}

bool GLES2Renderer::isUsingProgramAttributeLocation()
{
	return true;
}

bool GLES2Renderer::isSupportingIntegerProgramAttributes() {
	return false;
}


bool GLES2Renderer::isSpecularMappingAvailable()
{
	return false;
}

bool GLES2Renderer::isNormalMappingAvailable()
{
	return false;
}

bool GLES2Renderer::isInstancedRenderingAvailable() {
	return false;
}

bool GLES2Renderer::isPBRAvailable()
{
	return false;
}

bool GLES2Renderer::isComputeShaderAvailable() {
	return false;
}

bool GLES2Renderer::isGLCLAvailable() {
	return false;
}

bool GLES2Renderer::isUsingShortIndices() {
	return true;
}

bool GLES2Renderer::isDeferredShadingAvailable() {
	return false;
}

int32_t GLES2Renderer::getTextureUnits()
{
	return -1;
}

int32_t GLES2Renderer::loadShader(int32_t type, const string& pathName, const string& fileName, const string& definitions, const string& functions)
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
	char *sourceHeap = new char[sourceString.length() + 1];
	strcpy(sourceHeap, sourceString.c_str());
	// load source
	glShaderSource(handle, 1, &sourceHeap, nullptr);
	// compile
	glCompileShader(handle);
	// check state
	int32_t compileStatus;
	glGetShaderiv(handle, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == 0) {
		// get error
		int32_t infoLogLengthBuffer;
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &infoLogLengthBuffer);
		char infoLogBuffer[infoLogLengthBuffer];
		glGetShaderInfoLog(handle, infoLogLengthBuffer, &infoLogLengthBuffer, infoLogBuffer);
		auto infoLogString = (string(infoLogBuffer, infoLogLengthBuffer));
		// be verbose
		Console::println(
			string(
				string("GLES2Renderer::loadShader") +
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
		// remove shader
		glDeleteShader(handle);
		return 0;
	}

	return handle;
}

void GLES2Renderer::useProgram(int contextIdx, int32_t programId)
{
	glUseProgram(programId);
}

int32_t GLES2Renderer::createProgram(int type)
{
	auto program = glCreateProgram();
	return program;
}

void GLES2Renderer::attachShaderToProgram(int32_t programId, int32_t shaderId)
{
	glAttachShader(programId, shaderId);
}

bool GLES2Renderer::linkProgram(int32_t programId)
{
	glLinkProgram(programId);
	// check state
	int32_t linkStatus;
	glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == 0) {
		// get error
		int32_t infoLogLength = 0;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
		char infoLog[infoLogLength];
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
		return false;
	}
	return true;
}

int32_t GLES2Renderer::getProgramUniformLocation(int32_t programId, const string& name)
{
	auto uniformLocation = glGetUniformLocation(programId, name.c_str());
	// if (uniformLocation == -1) Console::println("GLES2Renderer::getProgramUniformLocation(): " + to_string(programId) + ": " + name + ": not found");
	return uniformLocation;
}

void GLES2Renderer::setProgramUniformInteger(int contextIdx, int32_t uniformId, int32_t value)
{
	glUniform1i(uniformId, value);
}

void GLES2Renderer::setProgramUniformFloat(int contextIdx, int32_t uniformId, float value)
{
	glUniform1f(uniformId, value);
}

void GLES2Renderer::setProgramUniformFloatMatrix3x3(int contextIdx, int32_t uniformId, const array<float, 9>& data)
{
	glUniformMatrix3fv(uniformId, 1, false, data.data());
}

void GLES2Renderer::setProgramUniformFloatMatrix4x4(int contextIdx, int32_t uniformId, const array<float, 16>& data)
{
	glUniformMatrix4fv(uniformId, 1, false, data.data());
}

void GLES2Renderer::setProgramUniformFloatMatrices4x4(int contextIdx, int32_t uniformId, int32_t count, FloatBuffer* data)
{
	glUniformMatrix4fv(uniformId, count, false, (float*)data->getBuffer());
}

void GLES2Renderer::setProgramUniformFloatVec4(int contextIdx, int32_t uniformId, const array<float, 4>& data)
{
	glUniform4fv(uniformId, 1, data.data());
}

void GLES2Renderer::setProgramUniformFloatVec3(int contextIdx, int32_t uniformId, const array<float, 3>& data)
{
	glUniform3fv(uniformId, 1, data.data());
}

void GLES2Renderer::setProgramUniformFloatVec2(int contextIdx, int32_t uniformId, const array<float, 2>& data)
{
	glUniform2fv(uniformId, 1, data.data());
}

void GLES2Renderer::setProgramAttributeLocation(int32_t programId, int32_t location, const string& name)
{
	glBindAttribLocation(programId, location, (name).c_str());
}

void GLES2Renderer::setViewPort(int32_t width, int32_t height)
{
	this->viewPortWidth = width;
	this->viewPortHeight = height;
}

void GLES2Renderer::updateViewPort()
{
	glViewport(0, 0, viewPortWidth, viewPortHeight);
}

void GLES2Renderer::setClearColor(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
}

void GLES2Renderer::enableCulling(int contextIdx)
{
	glEnable(GL_CULL_FACE);
}

void GLES2Renderer::disableCulling(int contextIdx)
{
	glDisable(GL_CULL_FACE);
}

void GLES2Renderer::setFrontFace(int contextIdx, int32_t frontFace)
{
	glFrontFace(frontFace);
}

void GLES2Renderer::setCullFace(int32_t cullFace)
{
	glCullFace(cullFace);
}

void GLES2Renderer::enableBlending()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

void GLES2Renderer::enableAdditionBlending() {
	glBlendFunc(GL_ONE, GL_ONE);
	glEnable(GL_BLEND);
}

void GLES2Renderer::disableBlending()
{
	glDisable(GL_BLEND);
}

void GLES2Renderer::enableDepthBufferWriting()
{
	glDepthMask(true);
}

void GLES2Renderer::disableDepthBufferWriting()
{
	glDepthMask(false);
}

void GLES2Renderer::disableDepthBufferTest()
{
	glDisable(GL_DEPTH_TEST);
}

void GLES2Renderer::enableDepthBufferTest()
{
	glEnable(GL_DEPTH_TEST);
}


void GLES2Renderer::setDepthFunction(int32_t depthFunction)
{
	glDepthFunc(depthFunction);
}

void GLES2Renderer::setColorMask(bool red, bool green, bool blue, bool alpha)
{
	glColorMask(red, green, blue, alpha);
}

void GLES2Renderer::clear(int32_t mask)
{
	glClear(mask);
	statistics.clearCalls++;
}

int32_t GLES2Renderer::createTexture()
{
	uint32_t textureId;
	glGenTextures(1, &textureId);
	return textureId;
}

int32_t GLES2Renderer::createDepthBufferTexture(int32_t width, int32_t height, int32_t cubeMapTextureId, int32_t cubeMapTextureIndex)
{
	uint32_t depthTextureId;
	// create depth texture
	glGenTextures(1, &depthTextureId);
	glBindTexture(GL_TEXTURE_2D, depthTextureId);
	// create depth texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, nullptr);
	// depth texture parameter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// unbind, return
	glBindTexture(GL_TEXTURE_2D, ID_NONE);
	return depthTextureId;
}

int32_t GLES2Renderer::createColorBufferTexture(int32_t width, int32_t height, int32_t cubeMapTextureId, int32_t cubeMapTextureIndex)
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

int32_t GLES2Renderer::createGBufferGeometryTexture(int32_t width, int32_t height) {
	Console::println("GLES2Renderer::createGBufferGeometryTexture(): Not implemented");
	return ID_NONE;
}

int32_t GLES2Renderer::createGBufferColorTexture(int32_t width, int32_t height) {
	Console::println("GLES2Renderer::createGBufferColorTexture(): Not implemented");
	return ID_NONE;
}

void GLES2Renderer::uploadTexture(int contextIdx, Texture* texture)
{
	//
	auto textureTextureData = texture->getUncompressedTextureData();
	//
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		texture->getDepthBitsPerPixel() == 32?GL_RGBA:GL_RGB,
		texture->getTextureWidth(),
		texture->getTextureHeight(),
		0,
		texture->getDepthBitsPerPixel() == 32?GL_RGBA:GL_RGB,
		GL_UNSIGNED_BYTE,
		textureTextureData.getBuffer()
	);
	//
	if (texture->getAtlasSize() > 1) {
		if (texture->isUseMipMap() == true) {
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
			// TODO: this feature does not seem to exist with GLES2
			/*
			float color[4] = {0.0f, 0.0f, 0.0f, 0.0f};
			if (texture->getClampMode() == Texture::CLAMPMODE_TRANSPARENTPIXEL) glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture->getClampMode() == Texture::CLAMPMODE_EDGE?GL_CLAMP_TO_EDGE:GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture->getClampMode() == Texture::CLAMPMODE_EDGE?GL_CLAMP_TO_EDGE:GL_CLAMP_TO_BORDER);
			*/
		}
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture->isUseMipMap() == true?GL_LINEAR_MIPMAP_LINEAR:GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	statistics.textureUploads++;
}

void GLES2Renderer::uploadCubeMapTexture(int contextIdx, Texture* textureLeft, Texture* textureRight, Texture* textureTop, Texture* textureBottom, Texture* textureFront, Texture* textureBack) {
	{
		//
		auto textureTextureData = textureLeft->getUncompressedTextureData();
		//
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
			0,
			textureLeft->getDepthBitsPerPixel() == 32?GL_RGBA:GL_RGB,
			textureLeft->getTextureWidth(),
			textureLeft->getTextureHeight(),
			0,
			textureLeft->getDepthBitsPerPixel() == 32?GL_RGBA:GL_RGB,
			GL_UNSIGNED_BYTE,
			textureTextureData.getBuffer()
		);
	}
	{
		//
		auto textureTextureData = textureRight->getUncompressedTextureData();
		//
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X,
			0,
			textureRight->getDepthBitsPerPixel() == 32?GL_RGBA:GL_RGB,
			textureRight->getTextureWidth(),
			textureRight->getTextureHeight(),
			0,
			textureRight->getDepthBitsPerPixel() == 32?GL_RGBA:GL_RGB,
			GL_UNSIGNED_BYTE,
			textureTextureData.getBuffer()
		);
	}
	{
		//
		auto textureTextureData = textureTop->getUncompressedTextureData();
		//
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
			0,
			textureTop->getDepthBitsPerPixel() == 32?GL_RGBA:GL_RGB,
			textureTop->getTextureWidth(),
			textureTop->getTextureHeight(),
			0,
			textureTop->getDepthBitsPerPixel() == 32?GL_RGBA:GL_RGB,
			GL_UNSIGNED_BYTE,
			textureTextureData.getBuffer()
		);
	}
	{
		//
		auto textureTextureData = textureBottom->getUncompressedTextureData();
		//
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
			0,
			textureBottom->getDepthBitsPerPixel() == 32?GL_RGBA:GL_RGB,
			textureBottom->getTextureWidth(),
			textureBottom->getTextureHeight(),
			0,
			textureBottom->getDepthBitsPerPixel() == 32?GL_RGBA:GL_RGB,
			GL_UNSIGNED_BYTE,
			textureTextureData.getBuffer()
		);
	}
	{
		//
		auto textureTextureData = textureFront->getUncompressedTextureData();
		//
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
			0,
			textureFront->getDepthBitsPerPixel() == 32?GL_RGBA:GL_RGB,
			textureFront->getTextureWidth(),
			textureFront->getTextureHeight(),
			0,
			textureFront->getDepthBitsPerPixel() == 32?GL_RGBA:GL_RGB,
			GL_UNSIGNED_BYTE,
			textureTextureData.getBuffer()
		);
	}
	{
		//
		auto textureTextureData = textureBack->getUncompressedTextureData();
		//
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
			0,
			textureBack->getDepthBitsPerPixel() == 32?GL_RGBA:GL_RGB,
			textureBack->getTextureWidth(),
			textureBack->getTextureHeight(),
			0,
			textureBack->getDepthBitsPerPixel() == 32?GL_RGBA:GL_RGB,
			GL_UNSIGNED_BYTE,
			textureTextureData.getBuffer()
		);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	statistics.textureUploads+= 6;
}

int32_t GLES2Renderer::createCubeMapTexture(int contextIdx, int32_t width, int32_t height) {
	// generate open gl texture
	uint32_t textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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

void GLES2Renderer::resizeDepthBufferTexture(int32_t textureId, int32_t width, int32_t height)
{
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GLES2Renderer::resizeColorBufferTexture(int32_t textureId, int32_t width, int32_t height)
{
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GLES2Renderer::resizeGBufferGeometryTexture(int32_t textureId, int32_t width, int32_t height) {
	Console::println("GLES2Renderer::resizeGBufferGeometryTexture(): Not implemented");
}

void GLES2Renderer::resizeGBufferColorTexture(int32_t textureId, int32_t width, int32_t height) {
	Console::println("GLES2Renderer::resizeGBufferColorTexture(): Not implemented");
}

void GLES2Renderer::bindTexture(int contextIdx, int32_t textureId)
{
	glBindTexture(GL_TEXTURE_2D, textureId);
	onBindTexture(contextIdx, textureId);
}

void GLES2Renderer::bindCubeMapTexture(int contextIdx, int32_t textureId) {
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
	onBindTexture(contextIdx, textureId);
}

void GLES2Renderer::disposeTexture(int32_t textureId)
{
	glDeleteTextures(1, (const uint32_t*)&textureId);
	statistics.disposedTextures++;
}

int32_t GLES2Renderer::createFramebufferObject(int32_t depthBufferTextureId, int32_t colorBufferTextureId, int32_t cubeMapTextureId, int32_t cubeMapTextureIndex)
{
	uint32_t frameBufferId;
	// create a frame buffer object
	glGenFramebuffers(1, &frameBufferId);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);
	// attach the depth buffer texture to FBO
	if (depthBufferTextureId != ID_NONE) {
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthBufferTextureId, 0);
	}
	// attach the depth buffer texture to FBO
	if (colorBufferTextureId != ID_NONE) {
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBufferTextureId, 0);
		// glDrawBuffer(GL_COLOR_ATTACHMENT0);
		// glReadBuffer(GL_COLOR_ATTACHMENT0);
	} else
	if (cubeMapTextureId != ID_NONE) {
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, cubeMapTextureIndex, cubeMapTextureId, 0);
	} else {
		// glDrawBuffer(GL_NONE);
		// glReadBuffer(GL_NONE);
	}
	// check FBO status
	auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (fboStatus != GL_FRAMEBUFFER_COMPLETE) {
		Console::println(string("GL_FRAMEBUFFER_COMPLETE_EXT failed, CANNOT use FBO: "+ to_string(fboStatus)));
	}
	// switch back to window-system-provided framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return frameBufferId;
}

int32_t GLES2Renderer::createGeometryBufferObject(
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
	Console::println(string("GLES2Renderer::createGeometryBufferObject()::not implemented yet"));
	return ID_NONE;
}

void GLES2Renderer::bindFrameBuffer(int32_t frameBufferId)
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);
}

void GLES2Renderer::disposeFrameBufferObject(int32_t frameBufferId)
{
	glDeleteFramebuffers(1, (const uint32_t*)&frameBufferId);
}

vector<int32_t> GLES2Renderer::createBufferObjects(int32_t buffers, bool useGPUMemory, bool shared)
{
	vector<int32_t> bufferObjectIds;
	bufferObjectIds.resize(buffers);
	glGenBuffers(buffers, (uint32_t*)bufferObjectIds.data());
	for (auto bufferObjectId: bufferObjectIds) vbosUsage[bufferObjectId] = useGPUMemory == true?GL_STATIC_DRAW:GL_STREAM_DRAW;
	return bufferObjectIds;
}

void GLES2Renderer::uploadBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, FloatBuffer* data)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glBufferData(GL_ARRAY_BUFFER, size, data->getBuffer(), vbosUsage[bufferObjectId]);
	glBindBuffer(GL_ARRAY_BUFFER, ID_NONE);
	statistics.bufferUploads++;
}

void GLES2Renderer::uploadBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, ShortBuffer* data)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glBufferData(GL_ARRAY_BUFFER, size, data->getBuffer(), vbosUsage[bufferObjectId]);
	glBindBuffer(GL_ARRAY_BUFFER, ID_NONE);
	statistics.bufferUploads++;
}

void GLES2Renderer::uploadBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, IntBuffer* data)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glBufferData(GL_ARRAY_BUFFER, size, data->getBuffer(), vbosUsage[bufferObjectId]);
	glBindBuffer(GL_ARRAY_BUFFER, ID_NONE);
	statistics.bufferUploads++;
}

void GLES2Renderer::uploadIndicesBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, ShortBuffer* data)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObjectId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data->getBuffer(), vbosUsage[bufferObjectId]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID_NONE);
	statistics.bufferUploads++;
}

void GLES2Renderer::uploadIndicesBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, IntBuffer* data)
{
	Console::println("GLES2Renderer::uploadIndicesBufferObject()::not implemented");
}

void GLES2Renderer::bindIndicesBufferObject(int contextIdx, int32_t bufferObjectId)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObjectId);
}

void GLES2Renderer::bindSolidColorsBufferObject(int contextIdx, int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 1, GL_FLOAT, false, 0, 0LL);
}

void GLES2Renderer::bindTextureCoordinatesBufferObject(int contextIdx, int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, 0LL);
}

void GLES2Renderer::bindVerticesBufferObject(int contextIdx, int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0LL);
}

void GLES2Renderer::bindVertices2BufferObject(int contextIdx, int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0LL);
}

void GLES2Renderer::bindNormalsBufferObject(int contextIdx, int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, 0LL);
}

void GLES2Renderer::bindColorsBufferObject(int contextIdx, int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, false, 0, 0LL);
}

void GLES2Renderer::bindTangentsBufferObject(int contextIdx, int32_t bufferObjectId)
{
	Console::println("GLES2Renderer::bindTangentsBufferObject()::not implemented");
}

void GLES2Renderer::bindBitangentsBufferObject(int contextIdx, int32_t bufferObjectId)
{
	Console::println("GLES2Renderer::bindBitangentsBufferObject()::not implemented");
}

void GLES2Renderer::bindModelMatricesBufferObject(int contextIdx, int32_t bufferObjectId) {
	Console::println(string("GLES2Renderer::bindModelViewMatricesBufferObject()::not implemented yet"));
}

void GLES2Renderer::bindEffectColorMulsBufferObject(int contextIdx, int32_t bufferObjectId, int32_t divisor) {
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(10);
	glVertexAttribPointer(10, 4, GL_FLOAT, false, 0, 0LL);
}

void GLES2Renderer::bindEffectColorAddsBufferObject(int contextIdx, int32_t bufferObjectId, int32_t divisor) {
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(11);
	glVertexAttribPointer(11, 4, GL_FLOAT, false, 0, 0LL);
}

void GLES2Renderer::bindOriginsBufferObject(int contextIdx, int32_t bufferObjectId) {
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, false, 0, 0LL);
}

void GLES2Renderer::bindTextureSpriteIndicesBufferObject(int contextIdx, int32_t bufferObjectId) {
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0LL);
}

void GLES2Renderer::bindPointSizesBufferObject(int contextIdx, int32_t bufferObjectId) {
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 1, GL_FLOAT, false, 0, 0LL);
}

void GLES2Renderer::bindSpriteSheetDimensionBufferObject(int contextIdx, int32_t bufferObjectId) {
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 2, GL_FLOAT, false, 0, 0LL);
}

void GLES2Renderer::drawInstancedIndexedTrianglesFromBufferObjects(int contextIdx, int32_t triangles, int32_t trianglesOffset, int32_t instances)
{
	Console::println(string("GLES2Renderer::drawInstancedIndexedTrianglesFromBufferObjects()::not implemented yet"));
}

void GLES2Renderer::drawIndexedTrianglesFromBufferObjects(int contextIdx, int32_t triangles, int32_t trianglesOffset)
{
	#define BUFFER_OFFSET(i) ((void*)(i))
	glDrawElements(GL_TRIANGLES, triangles * 3, GL_UNSIGNED_SHORT, BUFFER_OFFSET(static_cast< int64_t >(trianglesOffset) * 3LL * 2LL));
	statistics.renderCalls++;
	statistics.instances+= 1;
	statistics.triangles+= triangles;
}

void GLES2Renderer::drawInstancedTrianglesFromBufferObjects(int contextIdx, int32_t triangles, int32_t trianglesOffset, int32_t instances) {
	Console::println(string("GL2Renderer::drawInstancedTrianglesFromBufferObjects()::not implemented yet"));
}

void GLES2Renderer::drawTrianglesFromBufferObjects(int contextIdx, int32_t triangles, int32_t trianglesOffset)
{
	glDrawArrays(GL_TRIANGLES, trianglesOffset * 3, triangles * 3);
	statistics.renderCalls++;
	statistics.instances+= 1;
	statistics.triangles+= triangles;
}

void GLES2Renderer::drawPointsFromBufferObjects(int contextIdx, int32_t points, int32_t pointsOffset)
{
	glDrawArrays(GL_POINTS, pointsOffset, points);
	statistics.renderCalls++;
	statistics.points+= points;
}

void GLES2Renderer::setLineWidth(float lineWidth)
{
	glLineWidth(lineWidth);
}

void GLES2Renderer::drawLinesFromBufferObjects(int contextIdx, int32_t points, int32_t pointsOffset)
{
	glDrawArrays(GL_LINES, pointsOffset, points);
	statistics.renderCalls++;
	statistics.linePoints+= points;
}

void GLES2Renderer::unbindBufferObjects(int contextIdx)
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLES2Renderer::disposeBufferObjects(vector<int32_t>& bufferObjectIds)
{
	for (auto& bufferObjectId: bufferObjectIds) vbosUsage.erase(bufferObjectId);
	glDeleteBuffers(bufferObjectIds.size(), (const uint32_t*)bufferObjectIds.data());
	statistics.disposedBuffers+= bufferObjectIds.size();
}

int32_t GLES2Renderer::getTextureUnit(int contextIdx)
{
	return activeTextureUnit;
}

void GLES2Renderer::setTextureUnit(int contextIdx, int32_t textureUnit)
{
	this->activeTextureUnit = textureUnit;
	glActiveTexture(GL_TEXTURE0 + textureUnit);
}

float GLES2Renderer::readPixelDepth(int32_t x, int32_t y)
{
	return -1.0f;
}

ByteBuffer* GLES2Renderer::readPixels(int32_t x, int32_t y, int32_t width, int32_t height)
{
	return nullptr;
}

void GLES2Renderer::initGuiMode()
{
	setTextureUnit(CONTEXTINDEX_DEFAULT, 0);
	glBindTexture(GL_TEXTURE_2D, ID_NONE);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
}

void GLES2Renderer::doneGuiMode()
{
	glBindTexture(GL_TEXTURE_2D, ID_NONE);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

void GLES2Renderer::dispatchCompute(int contextIdx, int32_t numGroupsX, int32_t numGroupsY, int32_t numGroupsZ) {
	Console::println("GLES2Renderer::dispatchCompute(): Not implemented");
}

void GLES2Renderer::memoryBarrier() {
	Console::println("GLES2Renderer::memoryBarrier(): Not implemented");
}

void GLES2Renderer::uploadSkinningBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, FloatBuffer* data) {
	Console::println("GLES2Renderer::uploadSkinningBufferObject(): Not implemented");
}

void GLES2Renderer::uploadSkinningBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, IntBuffer* data) {
	Console::println("GLES2Renderer::uploadSkinningBufferObject(): Not implemented");
}

void GLES2Renderer::bindSkinningVerticesBufferObject(int contextIdx, int32_t bufferObjectId) {
	Console::println("GLES2Renderer::bindSkinningVerticesBufferObject(): Not implemented");
}

void GLES2Renderer::bindSkinningNormalsBufferObject(int contextIdx, int32_t bufferObjectId) {
	Console::println("GLES2Renderer::bindSkinningNormalsBufferObject(): Not implemented");
}

void GLES2Renderer::bindSkinningVertexJointsBufferObject(int contextIdx, int32_t bufferObjectId) {
	Console::println("GLES2Renderer::bindSkinningVertexJointsBufferObject(): Not implemented");
}

void GLES2Renderer::bindSkinningVertexJointIdxsBufferObject(int contextIdx, int32_t bufferObjectId) {
	Console::println("GLES2Renderer::bindSkinningVertexJointIdxsBufferObject(): Not implemented");
}

void GLES2Renderer::bindSkinningVertexJointWeightsBufferObject(int contextIdx, int32_t bufferObjectId) {
	Console::println("GLES2Renderer::bindSkinningVertexJointWeightsBufferObject(): Not implemented");
}

void GLES2Renderer::bindSkinningVerticesResultBufferObject(int contextIdx, int32_t bufferObjectId) {
	Console::println("GLES2Renderer::bindSkinningVerticesResultBufferObject(): Not implemented");
}

void GLES2Renderer::bindSkinningNormalsResultBufferObject(int contextIdx, int32_t bufferObjectId) {
	Console::println("GLES2Renderer::bindSkinningNormalsResultBufferObject(): Not implemented");
}

void GLES2Renderer::bindSkinningMatricesBufferObject(int contextIdx, int32_t bufferObjectId) {
	Console::println("GLES2Renderer::bindSkinningMatricesBufferObject(): Not implemented");
}

void GLES2Renderer::setVSync(bool vSync) {
	// no op
}

const Renderer::Renderer_Statistics GLES2Renderer::getStatistics() {
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

void GLES2Renderer::checkGLError()
{
	auto error = glGetError();
	if (error != GL_NO_ERROR) {
		Console::println(string("OpenGL Error: (" + to_string(error) + ") @:"));
	}
}
