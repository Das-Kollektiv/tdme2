#include <tdme/engine/subsystems/renderer/GL2Renderer.h>

#if defined(__APPLE__)
        #include <OpenGL/gl.h>
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__linux__) || defined(_WIN32) || defined(__HAIKU__)
	#define GLEW_NO_GLU
	#include <GL/glew.h>
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
using std::string;
using std::to_string;

using tdme::engine::subsystems::renderer::GL2Renderer;
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

GL2Renderer::GL2Renderer() 
{
	// setup GL2 consts
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
	// TODO: buffer objects available
	bufferObjectsAvailable = true;
}

const string GL2Renderer::getGLVersion()
{
	return "gl2";
}

bool GL2Renderer::checkBufferObjectsAvailable()
{
	// Check if extension is available.
	auto extensionOK = true; // isExtensionAvailable(u"GL_ARB_vertex_buffer_object"_j);
	// Check for VBO functions.
	auto functionsOK = true; // isFunctionAvailable(u"glGenBuffersARB"_j) && isFunctionAvailable(u"glBindBufferARB"_j) && isFunctionAvailable(u"glBufferDataARB"_j)&& isFunctionAvailable(u"glDeleteBuffersARB"_j);
	return extensionOK == true && functionsOK == true;
}

bool GL2Renderer::isDepthTextureAvailable()
{
	return true;
}

void GL2Renderer::initialize()
{
	glGetError();
	// get default framebuffer
	FRAMEBUFFER_DEFAULT = 0; // getContext()->getDefaultDrawFramebuffer();
	// check VBO
	bufferObjectsAvailable = checkBufferObjectsAvailable();
	// setup open gl
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);
	glDisable(GL_BLEND);
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_PROGRAM_POINT_SIZE_EXT);
	setTextureUnit(0);
}

void GL2Renderer::initializeFrame()
{
	GLRenderer::initializeFrame();
}

bool GL2Renderer::isBufferObjectsAvailable()
{
	return bufferObjectsAvailable;
}

bool GL2Renderer::isUsingProgramAttributeLocation()
{
	return true;
}

bool GL2Renderer::isSpecularMappingAvailable()
{
	return false;
}

bool GL2Renderer::isNormalMappingAvailable()
{
	return false;
}

bool GL2Renderer::isDisplacementMappingAvailable()
{
	return false;
}

bool GL2Renderer::isInstancedRenderingAvailable() {
	return false;
}

bool GL2Renderer::isUsingShortIndices() {
	return false;
}

bool GL2Renderer::isGeometryShaderAvailable() {
	return false;
}

int32_t GL2Renderer::getTextureUnits()
{
	return -1;
}

int32_t GL2Renderer::loadShader(int32_t type, const string& pathName, const string& fileName, const string& definitions, const string& functions)
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
	// get error
	if (compileStatus == 0) {
		int32_t infoLogLengthBuffer;
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &infoLogLengthBuffer);
		char* infoLogBuffer = new char[infoLogLengthBuffer];
		glGetShaderInfoLog(handle, infoLogLengthBuffer, &infoLogLengthBuffer, infoLogBuffer);
		auto infoLogString = (string(infoLogBuffer, infoLogLengthBuffer));
		// be verbose
		Console::println(
			string(
				string("GL2Renderer::loadShader") +
				string("[") +
				to_string(handle) +
				string("]") +
				pathName +
				"/" +
				fileName +
				string(": failed: ") +
				infoLogString
			 )
		 );
		//
		delete [] infoLogBuffer;
		// remove shader
		glDeleteShader(handle);
		//
		return 0;
	}

	//
	return handle;
}

void GL2Renderer::useProgram(int32_t programId)
{
	glUseProgram(programId);
}

int32_t GL2Renderer::createProgram()
{
	auto programId = glCreateProgram();
	return programId;
}

void GL2Renderer::attachShaderToProgram(int32_t programId, int32_t shaderId)
{
	glAttachShader(programId, shaderId);
}

bool GL2Renderer::linkProgram(int32_t programId)
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
		delete [] infoLog;
		return false;
	}
	return true;
}

int32_t GL2Renderer::getProgramUniformLocation(int32_t programId, const string& name)
{
	auto uniformLocation = glGetUniformLocation(programId, (name).c_str());
	return uniformLocation;
}

void GL2Renderer::setProgramUniformInteger(int32_t uniformId, int32_t value)
{
	glUniform1i(uniformId, value);
}

void GL2Renderer::setProgramUniformFloat(int32_t uniformId, float value)
{
	glUniform1f(uniformId, value);
}

void GL2Renderer::setProgramUniformFloatMatrices4x4(int32_t uniformId, int32_t count, FloatBuffer* data)
{
	glUniformMatrix4fv(uniformId, count, false, (float*)data->getBuffer());
}

void GL2Renderer::setProgramUniformFloatMatrix3x3(int32_t uniformId, const array<float, 9>& data)
{
	glUniformMatrix3fv(uniformId, 1, false, data.data());
}

void GL2Renderer::setProgramUniformFloatMatrix4x4(int32_t uniformId, const array<float, 16>& data)
{
	glUniformMatrix4fv(uniformId, 1, false, data.data());
}

void GL2Renderer::setProgramUniformFloatVec4(int32_t uniformId, const array<float, 4>& data)
{
	glUniform4fv(uniformId, 1, data.data());
}

void GL2Renderer::setProgramUniformFloatVec3(int32_t uniformId, const array<float, 3>& data)
{
	glUniform3fv(uniformId, 1, data.data());
}

void GL2Renderer::setProgramAttributeLocation(int32_t programId, int32_t location, const string& name)
{
	glBindAttribLocation(programId, location, (name).c_str());
}

void GL2Renderer::setViewPort(int32_t x, int32_t y, int32_t width, int32_t height)
{
	this->viewPortX = x;
	this->viewPortY = x;
	this->viewPortWidth = width;
	this->viewPortHeight = height;
	this->pointSize = width > height ? width / 120.0f : height / 120.0f * 16 / 9;
}

void GL2Renderer::updateViewPort()
{
	glViewport(viewPortX, viewPortY, viewPortWidth, viewPortHeight);
}

void GL2Renderer::setClearColor(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
}

void GL2Renderer::enableCulling()
{
	glEnable(GL_CULL_FACE);
}

void GL2Renderer::disableCulling()
{
	glDisable(GL_CULL_FACE);
}

void GL2Renderer::enableBlending()
{
	glEnable(GL_BLEND);
}

void GL2Renderer::disableBlending()
{
	glDisable(GL_BLEND);
}

void GL2Renderer::enableDepthBufferWriting()
{
	glDepthMask(true);
}

void GL2Renderer::disableDepthBufferWriting()
{
	glDepthMask(false);
}

void GL2Renderer::disableDepthBufferTest()
{
	glDisable(GL_DEPTH_TEST);
}

void GL2Renderer::enableDepthBufferTest()
{
	glEnable(GL_DEPTH_TEST);
}

void GL2Renderer::setDepthFunction(int32_t depthFunction)
{
	glDepthFunc(depthFunction);
}

void GL2Renderer::setColorMask(bool red, bool green, bool blue, bool alpha)
{
	glColorMask(red, green, blue, alpha);
}

void GL2Renderer::clear(int32_t mask)
{
	glClear(mask);
}

void GL2Renderer::setCullFace(int32_t cullFace)
{
	glCullFace(cullFace);
}

void GL2Renderer::setFrontFace(int32_t frontFace)
{
	glFrontFace(frontFace);
}

int32_t GL2Renderer::createTexture()
{
	uint32_t textureId;
	glGenTextures(1, &textureId);
	return textureId;
}

int32_t GL2Renderer::createDepthBufferTexture(int32_t width, int32_t height)
{
	uint32_t depthTextureGlId;
	// create depth texture
	glGenTextures(1, &depthTextureGlId);
	glBindTexture(GL_TEXTURE_2D, depthTextureGlId);
	// create depth texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	// depth texture parameter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// unbind, return
	glBindTexture(GL_TEXTURE_2D, ID_NONE);
	return depthTextureGlId;
}

int32_t GL2Renderer::createColorBufferTexture(int32_t width, int32_t height)
{
	uint32_t colorBufferTextureGlId;
	// create color texture
	glGenTextures(1, &colorBufferTextureGlId);
	glBindTexture(GL_TEXTURE_2D, colorBufferTextureGlId);
	// create color texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, static_cast< Buffer* >(nullptr));
	// color texture parameter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// unbind, return
	glBindTexture(GL_TEXTURE_2D, ID_NONE);
	return colorBufferTextureGlId;
}

void GL2Renderer::uploadTexture(Texture* texture)
{
	glTexImage2D(GL_TEXTURE_2D, 0, texture->getDepth() == 32 ? GL_RGBA : GL_RGB, texture->getTextureWidth(), texture->getTextureHeight(), 0, texture->getDepth() == 32 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, texture->getTextureData()->getBuffer());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture->isUseMipMap() == true?GL_LINEAR_MIPMAP_LINEAR:GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (texture->isUseMipMap() == true) glGenerateMipmap(GL_TEXTURE_2D);
}

void GL2Renderer::resizeDepthBufferTexture(int32_t textureId, int32_t width, int32_t height)
{
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GL2Renderer::resizeColorBufferTexture(int32_t textureId, int32_t width, int32_t height)
{
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GL2Renderer::bindTexture(int32_t textureId)
{
	glBindTexture(GL_TEXTURE_2D, textureId);
	onBindTexture(textureId);
}

void GL2Renderer::disposeTexture(int32_t textureId)
{
	glDeleteTextures(1, (const uint32_t*)&textureId);
}

int32_t GL2Renderer::createFramebufferObject(int32_t depthBufferTextureGlId, int32_t colorBufferTextureGlId)
{
	// create a frame buffer object
	uint32_t frameBufferGlId;
	glGenFramebuffers(1, &frameBufferGlId);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferGlId);
	// attach the depth buffer texture to FBO
	if (depthBufferTextureGlId != ID_NONE) {
		#ifdef __APPLE__
			glFramebufferTextureEXT(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthBufferTextureGlId, 0);
		#else
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthBufferTextureGlId, 0);
		#endif
	}
	// attach the color buffer texture to FBO
	if (colorBufferTextureGlId != ID_NONE) {
		#ifdef __APPLE__
			glFramebufferTextureEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colorBufferTextureGlId, 0);
		#else
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBufferTextureGlId, 0);
		#endif
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		glReadBuffer(GL_COLOR_ATTACHMENT0);
	} else {
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}
	// check FBO status
	int32_t fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (fboStatus != GL_FRAMEBUFFER_COMPLETE) {
		Console::println(string("GL_FRAMEBUFFER_COMPLETE_EXT failed, CANNOT use FBO: ") + to_string(fboStatus));
	}
	// switch back to window-system-provided framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return frameBufferGlId;
}

void GL2Renderer::bindFrameBuffer(int32_t frameBufferId)
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);
}

void GL2Renderer::disposeFrameBufferObject(int32_t frameBufferId)
{
	glDeleteFramebuffers(1, (uint32_t*)&frameBufferId);
}

vector<int32_t> GL2Renderer::createBufferObjects(int32_t buffers)
{
	vector<int32_t> bufferObjectIds;
	bufferObjectIds.resize(buffers);
	glGenBuffers(buffers, (uint32_t*)bufferObjectIds.data());
	return bufferObjectIds;
}

void GL2Renderer::uploadBufferObject(int32_t bufferObjectId, int32_t size, FloatBuffer* data)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glBufferData(GL_ARRAY_BUFFER, size, data->getBuffer(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, ID_NONE);
}

void GL2Renderer::uploadIndicesBufferObject(int32_t bufferObjectId, int32_t size, ShortBuffer* data)
{
	Console::println(string("GL2Renderer::uploadIndicesBufferObject()::not implemented yet"));
}

void GL2Renderer::uploadIndicesBufferObject(int32_t bufferObjectId, int32_t size, IntBuffer* data)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObjectId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data->getBuffer(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID_NONE);
}

void GL2Renderer::bindIndicesBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObjectId);
}

void GL2Renderer::bindTextureCoordinatesBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, 0LL);
}

void GL2Renderer::bindVerticesBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0LL);
}

void GL2Renderer::bindNormalsBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, 0LL);
}

void GL2Renderer::bindColorsBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, false, 0, 0LL);
}

void GL2Renderer::bindTangentsBufferObject(int32_t bufferObjectId)
{
	Console::println(string("GL2Renderer::bindTangentsBufferObject()::not implemented yet"));
}

void GL2Renderer::bindBitangentsBufferObject(int32_t bufferObjectId)
{
	Console::println(string("GL2Renderer::bindBitangentsBufferObject()::not implemented yet"));
}

void GL2Renderer::bindModelMatricesBufferObject(int32_t bufferObjectId) {
	Console::println(string("GL2Renderer::bindModelViewMatricesBufferObject()::not implemented yet"));
}

void GL2Renderer::bindEffectColorMulsBufferObject(int32_t bufferObjectId) {
	Console::println(string("GL2Renderer::bindEffectColorMulsBufferObject()::not implemented yet"));
}

void GL2Renderer::bindEffectColorAddsBufferObject(int32_t bufferObjectId) {
	Console::println(string("GL2Renderer::bindEffectColorAddsBufferObject()::not implemented yet"));
}

void GL2Renderer::drawInstancedIndexedTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset, int32_t instances)
{
	Console::println(string("GL2Renderer::drawInstancedIndexedTrianglesFromBufferObjects()::not implemented yet"));
}

void GL2Renderer::drawIndexedTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset)
{
	#define BUFFER_OFFSET(i) ((void*)(i))
	glDrawElements(GL_TRIANGLES, triangles * 3, GL_UNSIGNED_INT, BUFFER_OFFSET(static_cast< int64_t >(trianglesOffset) * 3LL * 4LL));
}

void GL2Renderer::drawInstancedTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset, int32_t instances) {
	Console::println(string("GL2Renderer::drawInstancedTrianglesFromBufferObjects()::not implemented yet"));
}

void GL2Renderer::drawTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset)
{
	glDrawArrays(GL_TRIANGLES, trianglesOffset * 3, triangles * 3);
}

void GL2Renderer::drawPointsFromBufferObjects(int32_t points, int32_t pointsOffset)
{
	glDrawArrays(GL_POINTS, pointsOffset, points);
}

void GL2Renderer::unbindBufferObjects()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GL2Renderer::disposeBufferObjects(vector<int32_t>& bufferObjectIds)
{
	glDeleteBuffers(bufferObjectIds.size(), (const uint32_t*)bufferObjectIds.data());
}

int32_t GL2Renderer::getTextureUnit()
{
	return activeTextureUnit;
}

void GL2Renderer::setTextureUnit(int32_t textureUnit)
{
	this->activeTextureUnit = textureUnit;
	glActiveTexture(GL_TEXTURE0 + textureUnit);
}

float GL2Renderer::readPixelDepth(int32_t x, int32_t y)
{
	float depth;
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
	return depth;
}

ByteBuffer* GL2Renderer::readPixels(int32_t x, int32_t y, int32_t width, int32_t height)
{
	/*
	auto pixelBuffer = ByteBuffer::allocateDirect(width * height * Byte::SIZE* 4);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, static_cast< Buffer* >(pixelBuffer));
	return pixelBuffer;
	*/
	return nullptr;
}

void GL2Renderer::initGuiMode()
{
	setTextureUnit(0);
	glBindTexture(GL_TEXTURE_2D, ID_NONE);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glGetError();
}

void GL2Renderer::doneGuiMode()
{
	glGetError();
	glBindTexture(GL_TEXTURE_2D, ID_NONE);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

void GL2Renderer::dispatchCompute(int32_t numGroupsX, int32_t numGroupsY, int32_t numGroupsZ) {
	Console::println("GL2Renderer::dispatchCompute(): Not implemented");
}

void GL2Renderer::memoryBarrier() {
	Console::println("GL2Renderer::memoryBarrier(): Not implemented");
}

void GL2Renderer::uploadSkinningBufferObject(int32_t bufferObjectId, int32_t size, FloatBuffer* data) {
	Console::println("GL2Renderer::uploadSkinningBufferObject(): Not implemented");
}

void GL2Renderer::uploadSkinningBufferObject(int32_t bufferObjectId, int32_t size, IntBuffer* data) {
	Console::println("GL2Renderer::uploadSkinningBufferObject(): Not implemented");
}

void GL2Renderer::bindSkinningVerticesBufferObject(int32_t bufferObjectId) {
	Console::println("GL2Renderer::bindSkinningVerticesBufferObject(): Not implemented");
}

void GL2Renderer::bindSkinningNormalsBufferObject(int32_t bufferObjectId) {
	Console::println("GL2Renderer::bindSkinningNormalsBufferObject(): Not implemented");
}

void GL2Renderer::bindSkinningVertexJointsBufferObject(int32_t bufferObjectId) {
	Console::println("GL2Renderer::bindSkinningVertexJointsBufferObject(): Not implemented");
}

void GL2Renderer::bindSkinningVertexJointIdxsBufferObject(int32_t bufferObjectId) {
	Console::println("GL2Renderer::bindSkinningVertexJointIdxsBufferObject(): Not implemented");
}

void GL2Renderer::bindSkinningVertexJointWeightsBufferObject(int32_t bufferObjectId) {
	Console::println("GL2Renderer::bindSkinningVertexJointWeightsBufferObject(): Not implemented");
}

void GL2Renderer::bindSkinningVerticesResultBufferObject(int32_t bufferObjectId) {
	Console::println("GL2Renderer::bindSkinningVerticesResultBufferObject(): Not implemented");
}

void GL2Renderer::bindSkinningNormalsResultBufferObject(int32_t bufferObjectId) {
	Console::println("GL2Renderer::bindSkinningNormalsResultBufferObject(): Not implemented");
}

void GL2Renderer::bindSkinningMatricesBufferObject(int32_t bufferObjectId) {
	Console::println("GL2Renderer::bindSkinningMatricesBufferObject(): Not implemented");
}
