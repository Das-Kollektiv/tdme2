#include <tdme/engine/subsystems/renderer/GLES2Renderer.h>

#if defined(__linux__)
	#define GL_GLEXT_PROTOTYPES
	#include <GLES2/gl2.h>
#endif

#include <string.h>

#include <array>
#include <vector>
#include <string>

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

using std::array;
using std::vector;
using std::to_string;
using std::string;

using tdme::engine::subsystems::renderer::GLES2Renderer;
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

GLES2Renderer::GLES2Renderer() 
{
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
	SHADER_GEOMETRY_SHADER = -1;
	SHADER_COMPUTE_SHADER = -1;
	DEPTHFUNCTION_ALWAYS = GL_ALWAYS;
	DEPTHFUNCTION_EQUAL = GL_EQUAL;
	DEPTHFUNCTION_LESSEQUAL = GL_LEQUAL;
	DEPTHFUNCTION_GREATEREQUAL = GL_GEQUAL;
}

const string GLES2Renderer::getGLVersion()
{
	return "gles2";
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
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);
	glDisable(GL_BLEND);
}

void GLES2Renderer::initializeFrame()
{
	GLRenderer::initializeFrame();
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

bool GLES2Renderer::isSpecularMappingAvailable()
{
	return false;
}

bool GLES2Renderer::isNormalMappingAvailable()
{
	return false;
}

bool GLES2Renderer::isDisplacementMappingAvailable()
{
	return false;
}

bool GLES2Renderer::isInstancedRenderingAvailable() {
	return false;
}

bool GLES2Renderer::isUsingShortIndices() {
	return true;
}

bool GLES2Renderer::isGeometryShaderAvailable() {
	return false;
}

int32_t GLES2Renderer::getTextureUnits()
{
	return -1;
}

int32_t GLES2Renderer::loadShader(int32_t type, const string& pathName, const string& fileName, const string& definitions, const string& functions = string())
{
	// create shader
	int32_t handle = glCreateShader(type);
	// exit if no handle returned
	if (handle == 0) return 0;
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

void GLES2Renderer::useProgram(int32_t programId)
{
	glUseProgram(programId);
}

int32_t GLES2Renderer::createProgram()
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
	auto uniformLocation = glGetUniformLocation(programId, (name).c_str());
	return uniformLocation;
}

void GLES2Renderer::setProgramUniformInteger(int32_t uniformId, int32_t value)
{
	glUniform1i(uniformId, value);
}

void GLES2Renderer::setProgramUniformFloat(int32_t uniformId, float value)
{
	glUniform1f(uniformId, value);
}

void GLES2Renderer::setProgramUniformFloatMatrix3x3(int32_t uniformId, const array<float, 9>& data)
{
	glUniformMatrix3fv(uniformId, 1, false, data.data());
}

void GLES2Renderer::setProgramUniformFloatMatrix4x4(int32_t uniformId, const array<float, 16>& data)
{
	glUniformMatrix4fv(uniformId, 1, false, data.data());
}

void GLES2Renderer::setProgramUniformFloatMatrices4x4(int32_t uniformId, int32_t count, FloatBuffer* data)
{
	glUniformMatrix4fv(uniformId, count, false, (float*)data->getBuffer());
}

void GLES2Renderer::setProgramUniformFloatVec4(int32_t uniformId, const array<float, 4>& data)
{
	glUniform4fv(uniformId, 1, data.data());
}

void GLES2Renderer::setProgramUniformFloatVec3(int32_t uniformId, const array<float, 3>& data)
{
	glUniform3fv(uniformId, 1, data.data());
}

void GLES2Renderer::setProgramAttributeLocation(int32_t programId, int32_t location, const string& name)
{
	glBindAttribLocation(programId, location, (name).c_str());
}

void GLES2Renderer::setViewPort(int32_t x, int32_t y, int32_t width, int32_t height)
{
	this->viewPortX = x;
	this->viewPortY = x;
	this->viewPortWidth = width;
	this->viewPortHeight = height;
	this->pointSize = width > height ? width / 120.0f : height / 120.0f * 16 / 9;
}

void GLES2Renderer::updateViewPort()
{
	glViewport(viewPortX, viewPortY, viewPortWidth, viewPortHeight);
}

void GLES2Renderer::setClearColor(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
}

void GLES2Renderer::enableCulling()
{
	glEnable(GL_CULL_FACE);
}

void GLES2Renderer::disableCulling()
{
	glDisable(GL_CULL_FACE);
}

void GLES2Renderer::enableBlending()
{
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
}

void GLES2Renderer::setCullFace(int32_t cullFace)
{
	glCullFace(cullFace);
}

void GLES2Renderer::setFrontFace(int32_t frontFace)
{
	glFrontFace(frontFace);
}

int32_t GLES2Renderer::createTexture()
{
	uint32_t textureId;
	glGenTextures(1, &textureId);
	return textureId;
}

int32_t GLES2Renderer::createDepthBufferTexture(int32_t width, int32_t height)
{
	uint32_t depthTextureGlId;
	// create depth texture
	glGenTextures(1, &depthTextureGlId);
	glBindTexture(GL_TEXTURE_2D, depthTextureGlId);
	// create depth texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, nullptr);
	// depth texture parameter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// unbind, return
	glBindTexture(GL_TEXTURE_2D, ID_NONE);
	return depthTextureGlId;
}

int32_t GLES2Renderer::createColorBufferTexture(int32_t width, int32_t height)
{
	uint32_t colorBufferTextureGlId;
	// create color texture
	glGenTextures(1, &colorBufferTextureGlId);
	glBindTexture(GL_TEXTURE_2D, colorBufferTextureGlId);
	// create color texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	// color texture parameter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// unbind, return
	glBindTexture(GL_TEXTURE_2D, ID_NONE);
	return colorBufferTextureGlId;
}

void GLES2Renderer::uploadTexture(Texture* texture)
{
	glTexImage2D(GL_TEXTURE_2D, 0, texture->getDepth() == 32 ? GL_RGBA : GL_RGB, texture->getTextureWidth(), texture->getTextureHeight(), 0, texture->getDepth() == 32 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, texture->getTextureData()->getBuffer());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture->isUseMipMap() == true?GL_LINEAR_MIPMAP_LINEAR:GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (texture->isUseMipMap() == true) glGenerateMipmap(GL_TEXTURE_2D);
}

void GLES2Renderer::resizeDepthBufferTexture(int32_t textureId, int32_t width, int32_t height)
{
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_INT, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GLES2Renderer::resizeColorBufferTexture(int32_t textureId, int32_t width, int32_t height)
{
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GLES2Renderer::bindTexture(int32_t textureId)
{
	glBindTexture(GL_TEXTURE_2D, textureId);
	onBindTexture(textureId);
}

void GLES2Renderer::disposeTexture(int32_t textureId)
{
	glDeleteTextures(1, (const uint32_t*)&textureId);
}

int32_t GLES2Renderer::createFramebufferObject(int32_t depthBufferTextureGlId, int32_t colorBufferTextureGlId)
{
	uint32_t frameBufferGlId;
	// create a frame buffer object
	glGenFramebuffers(1, &frameBufferGlId);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferGlId);
	// attach the depth buffer texture to FBO
	if (depthBufferTextureGlId != ID_NONE) {
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthBufferTextureGlId, 0);
	}
	// attach the depth buffer texture to FBO
	if (colorBufferTextureGlId != ID_NONE) {
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBufferTextureGlId, 0);
		// glDrawBuffer(GL_COLOR_ATTACHMENT0);
		// glReadBuffer(GL_COLOR_ATTACHMENT0);
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
	return frameBufferGlId;
}

void GLES2Renderer::bindFrameBuffer(int32_t frameBufferId)
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);
}

void GLES2Renderer::disposeFrameBufferObject(int32_t frameBufferId)
{
	glDeleteFramebuffers(1, (const uint32_t*)&frameBufferId);
}

vector<int32_t> GLES2Renderer::createBufferObjects(int32_t buffers)
{
	vector<int32_t> bufferObjectIds;
	bufferObjectIds.resize(buffers);
	glGenBuffers(buffers, (uint32_t*)bufferObjectIds.data());
	return bufferObjectIds;
}

void GLES2Renderer::uploadBufferObject(int32_t bufferObjectId, int32_t size, FloatBuffer* data)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glBufferData(GL_ARRAY_BUFFER, size, data->getBuffer(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, ID_NONE);
}

void GLES2Renderer::uploadIndicesBufferObject(int32_t bufferObjectId, int32_t size, ShortBuffer* data)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObjectId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data->getBuffer(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID_NONE);
}

void GLES2Renderer::uploadIndicesBufferObject(int32_t bufferObjectId, int32_t size, IntBuffer* data)
{
	Console::println("GLES2Renderer::uploadIndicesBufferObject()::not implemented");
}

void GLES2Renderer::bindIndicesBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObjectId);
}

void GLES2Renderer::bindTextureCoordinatesBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, 0LL);
}

void GLES2Renderer::bindVerticesBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0LL);
}

void GLES2Renderer::bindNormalsBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, 0LL);
}

void GLES2Renderer::bindColorsBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, false, 0, 0LL);
}

void GLES2Renderer::bindTangentsBufferObject(int32_t bufferObjectId)
{
	Console::println("GLES2Renderer::bindTangentsBufferObject()::not implemented");
}

void GLES2Renderer::bindBitangentsBufferObject(int32_t bufferObjectId)
{
	Console::println("GLES2Renderer::bindBitangentsBufferObject()::not implemented");
}

void GLES2Renderer::bindModelMatricesBufferObject(int32_t bufferObjectId) {
	Console::println(string("GLES2Renderer::bindModelViewMatricesBufferObject()::not implemented yet"));
}

void GLES2Renderer::bindEffectColorMulsBufferObject(int32_t bufferObjectId) {
	Console::println(string("GLES2Renderer::bindEffectColorMulsBufferObject()::not implemented yet"));
}

void GLES2Renderer::bindEffectColorAddsBufferObject(int32_t bufferObjectId) {
	Console::println(string("GLES2Renderer::bindEffectColorAddsBufferObject()::not implemented yet"));
}

void GLES2Renderer::drawInstancedIndexedTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset, int32_t instances)
{
	Console::println(string("GLES2Renderer::drawInstancedIndexedTrianglesFromBufferObjects()::not implemented yet"));
}

void GLES2Renderer::drawIndexedTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset)
{
	#define BUFFER_OFFSET(i) ((void*)(i))
	glDrawElements(GL_TRIANGLES, triangles * 3, GL_UNSIGNED_SHORT, BUFFER_OFFSET(static_cast< int64_t >(trianglesOffset) * 3LL * 2LL));
}

void GLES2Renderer::drawInstancedTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset, int32_t instances) {
	Console::println(string("GL2Renderer::drawInstancedTrianglesFromBufferObjects()::not implemented yet"));
}

void GLES2Renderer::drawTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset)
{
	glDrawArrays(GL_TRIANGLES, trianglesOffset * 3, triangles * 3);
}

void GLES2Renderer::drawPointsFromBufferObjects(int32_t points, int32_t pointsOffset)
{
	glDrawArrays(GL_POINTS, pointsOffset, points);
}

void GLES2Renderer::unbindBufferObjects()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLES2Renderer::disposeBufferObjects(vector<int32_t>& bufferObjectIds)
{
	glDeleteBuffers(bufferObjectIds.size(), (const uint32_t*)bufferObjectIds.data());
}

int32_t GLES2Renderer::getTextureUnit()
{
	return activeTextureUnit;
}

void GLES2Renderer::setTextureUnit(int32_t textureUnit)
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
	setTextureUnit(0);
	glBindTexture(GL_TEXTURE_2D, ID_NONE);
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

void GLES2Renderer::dispatchCompute(int32_t numGroupsX, int32_t numGroupsY, int32_t numGroupsZ) {
	Console::println("GLES2Renderer::dispatchCompute(): Not implemented");
}

void GLES2Renderer::memoryBarrier() {
	Console::println("GLES2Renderer::memoryBarrier(): Not implemented");
}

void GLES2Renderer::uploadSkinningBufferObject(int32_t bufferObjectId, int32_t size, FloatBuffer* data) {
	Console::println("GLES2Renderer::uploadSkinningBufferObject(): Not implemented");
}

void GLES2Renderer::uploadSkinningBufferObject(int32_t bufferObjectId, int32_t size, IntBuffer* data) {
	Console::println("GLES2Renderer::uploadSkinningBufferObject(): Not implemented");
}

void GLES2Renderer::bindSkinningVerticesBufferObject(int32_t bufferObjectId) {
	Console::println("GLES2Renderer::bindSkinningVerticesBufferObject(): Not implemented");
}

void GLES2Renderer::bindSkinningNormalsBufferObject(int32_t bufferObjectId) {
	Console::println("GLES2Renderer::bindSkinningNormalsBufferObject(): Not implemented");
}

void GLES2Renderer::bindSkinningVertexJointsBufferObject(int32_t bufferObjectId) {
	Console::println("GLES2Renderer::bindSkinningVertexJointsBufferObject(): Not implemented");
}

void GLES2Renderer::bindSkinningVertexJointIdxsBufferObject(int32_t bufferObjectId) {
	Console::println("GLES2Renderer::bindSkinningVertexJointIdxsBufferObject(): Not implemented");
}

void GLES2Renderer::bindSkinningVertexJointWeightsBufferObject(int32_t bufferObjectId) {
	Console::println("GLES2Renderer::bindSkinningVertexJointWeightsBufferObject(): Not implemented");
}

void GLES2Renderer::bindSkinningVerticesResultBufferObject(int32_t bufferObjectId) {
	Console::println("GLES2Renderer::bindSkinningVerticesResultBufferObject(): Not implemented");
}

void GLES2Renderer::bindSkinningNormalsResultBufferObject(int32_t bufferObjectId) {
	Console::println("GLES2Renderer::bindSkinningNormalsResultBufferObject(): Not implemented");
}

void GLES2Renderer::bindSkinningMatricesBufferObject(int32_t bufferObjectId) {
	Console::println("GLES2Renderer::bindSkinningMatricesBufferObject(): Not implemented");
}

void GLES2Renderer::checkGLError()
{
	auto error = glGetError();
	if (error != GL_NO_ERROR) {
		Console::println(string("OpenGL Error: (" + to_string(error) + ") @:"));
	}
}
