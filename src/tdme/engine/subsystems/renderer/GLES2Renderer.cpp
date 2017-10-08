#include <tdme/engine/subsystems/renderer/GLES2Renderer.h>

#ifdef __linux__
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
#include <tdme/utils/StringConverter.h>

using std::array;
using std::vector;
using std::to_wstring;
using std::wstring;

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
using tdme::utils::StringConverter;
using tdme::utils::Console;

GLES2Renderer::GLES2Renderer() 
{
	ID_NONE = 0;
	CLEAR_DEPTH_BUFFER_BIT = GL_DEPTH_BUFFER_BIT;
	CLEAR_COLOR_BUFFER_BIT = GL_COLOR_BUFFER_BIT;
	CULLFACE_FRONT = GL_FRONT;
	CULLFACE_BACK = GL_BACK;
	FRONTFACE_CW = GL_CW;
	FRONTFACE_CCW = GL_CCW;
	CLIENTSTATE_TEXTURECOORD_ARRAY = 2;
	CLIENTSTATE_VERTEX_ARRAY = 0;
	CLIENTSTATE_NORMAL_ARRAY = 1;
	CLIENTSTATE_COLOR_ARRAY = 3;
	SHADER_FRAGMENT_SHADER = GL_FRAGMENT_SHADER;
	SHADER_VERTEX_SHADER = GL_VERTEX_SHADER;
	DEPTHFUNCTION_LESSEQUAL = GL_LEQUAL;
	DEPTHFUNCTION_EQUAL = GL_EQUAL;
}

const wstring GLES2Renderer::getGLVersion()
{
	return L"gles2";
}

void GLES2Renderer::initialize()
{
	glGetError();
	FRAMEBUFFER_DEFAULT = 0; // getContext()->getDefaultDrawFramebuffer();
	checkGLError();
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

int32_t GLES2Renderer::getTextureUnits()
{
	return -1;
}

int32_t GLES2Renderer::loadShader(int32_t type, const wstring& pathName, const wstring& fileName)
{
	int32_t handle = glCreateShader(type);
	checkGLError();
	if (handle == 0) return 0;

	auto shaderSource = FileSystem::getInstance()->getContentAsString(pathName, fileName);

	string sourceString = StringConverter::toString(shaderSource);
	char *sourceHeap = new char[sourceString.length() + 1];
	strcpy(sourceHeap, sourceString.c_str());
	glShaderSource(handle, 1, &sourceHeap, nullptr);

	glCompileShader(handle);

	int32_t compileStatus;
	glGetShaderiv(handle, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == 0) {
		int32_t infoLogLengthBuffer;
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &infoLogLengthBuffer);
		char infoLogBuffer[infoLogLengthBuffer];
		glGetShaderInfoLog(handle, infoLogLengthBuffer, &infoLogLengthBuffer, infoLogBuffer);
		auto infoLogString = StringConverter::toWideString(string(infoLogBuffer, infoLogLengthBuffer));
		Console::println(
			wstring(
				wstring(L"GLES2Renderer::loadShader") +
				wstring(L"[") +
				to_wstring(handle) +
				wstring(L"]") +
				pathName +
				wstring(L"/") +
				fileName +
				wstring(L": failed: ") +
				infoLogString
			 )
		 );
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

	int32_t linkStatus;
	glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == 0) {
		int32_t infoLogLength = 0;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
		char infoLog[infoLogLength];
		glGetProgramInfoLog(programId, infoLogLength, &infoLogLength, infoLog);
		auto infoLogString = StringConverter::toWideString(string(infoLog, infoLogLength));
		Console::println(
			wstring(
				L"[" +
				to_wstring(programId) +
				L"]: failed: " +
				infoLogString
			 )
		);
		return false;
	}
	return true;
}

int32_t GLES2Renderer::getProgramUniformLocation(int32_t programId, const wstring& name)
{
	auto uniformLocation = glGetUniformLocation(programId, StringConverter::toString(name).c_str());
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

void GLES2Renderer::setProgramAttributeLocation(int32_t programId, int32_t location, const wstring& name)
{
	glBindAttribLocation(programId, location, StringConverter::toString(name).c_str());
}

void GLES2Renderer::setViewPort(int32_t x, int32_t y, int32_t width, int32_t height)
{
	this->viewPortX = x;
	this->viewPortY = x;
	this->viewPortWidth = width;
	this->viewPortHeight = height;
	this->pointSize = width > height ? width / 12.0f : height / 12.0f * 16 / 9;
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

void GLES2Renderer::enableDepthBuffer()
{
	glDepthMask(true);
}

void GLES2Renderer::disableDepthBuffer()
{
	glDepthMask(false);
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
	glGenTextures(1, &depthTextureGlId);
	glBindTexture(GL_TEXTURE_2D, depthTextureGlId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, ID_NONE);
	return depthTextureGlId;
}

int32_t GLES2Renderer::createColorBufferTexture(int32_t width, int32_t height)
{
	uint32_t colorBufferTextureGlId;
	glGenTextures(1, &colorBufferTextureGlId);
	glBindTexture(GL_TEXTURE_2D, colorBufferTextureGlId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, ID_NONE);
	return colorBufferTextureGlId;
}

void GLES2Renderer::uploadTexture(Texture* texture)
{
	glTexImage2D(GL_TEXTURE_2D, 0, texture->getDepth() == 32 ? GL_RGBA : GL_RGB, texture->getTextureWidth(), texture->getTextureHeight(), 0, texture->getDepth() == 32 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, texture->getTextureData()->getBuffer());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
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
	glGenFramebuffers(1, &frameBufferGlId);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferGlId);
	if (depthBufferTextureGlId != ID_NONE) {
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthBufferTextureGlId, 0);
	}
	if (colorBufferTextureGlId != ID_NONE) {
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBufferTextureGlId, 0);
		// glDrawBuffer(GL_COLOR_ATTACHMENT0);
		// glReadBuffer(GL_COLOR_ATTACHMENT0);
	} else {
		// glDrawBuffer(GL_NONE);
		// glReadBuffer(GL_NONE);
	}
	auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (fboStatus != GL_FRAMEBUFFER_COMPLETE) {
		Console::println(wstring(L"GL_FRAMEBUFFER_COMPLETE_EXT failed, CANNOT use FBO: "+ to_wstring(fboStatus)));
	}
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

void GLES2Renderer::uploadBufferObject(int32_t bufferObjectId, int32_t size, ShortBuffer* data)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glBufferData(GL_ARRAY_BUFFER, size, data->getBuffer(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, ID_NONE);
}

void GLES2Renderer::bindIndicesBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObjectId);
}

void GLES2Renderer::bindTextureCoordinatesBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(CLIENTSTATE_TEXTURECOORD_ARRAY, 2, GL_FLOAT, false, 0, 0LL);
}

void GLES2Renderer::bindVerticesBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(CLIENTSTATE_VERTEX_ARRAY, 3, GL_FLOAT, false, 0, 0LL);
}

void GLES2Renderer::bindNormalsBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(CLIENTSTATE_NORMAL_ARRAY, 3, GL_FLOAT, false, 0, 0LL);
}

void GLES2Renderer::bindColorsBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, false, 0, 0LL);
}

void GLES2Renderer::bindSkinningVerticesJointsBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 1, GL_FLOAT, false, 0, 0LL);
}

void GLES2Renderer::bindSkinningVerticesVertexJointsIdxBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, false, 0, 0LL);
}

void GLES2Renderer::bindSkinningVerticesVertexJointsWeightBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, false, 0, 0LL);
}

void GLES2Renderer::bindTangentsBufferObject(int32_t bufferObjectId)
{
	Console::println(L"GLES2Renderer::bindTangentsBufferObject()::not implemented");
}

void GLES2Renderer::bindBitangentsBufferObject(int32_t bufferObjectId)
{
	Console::println(L"GLES2Renderer::bindBitangentsBufferObject()::not implemented");
}

void GLES2Renderer::drawIndexedTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset)
{
	#define BUFFER_OFFSET(i) ((void*)(i))
	glDrawElements(GL_TRIANGLES, triangles * 3, GL_UNSIGNED_SHORT, BUFFER_OFFSET(static_cast< int64_t >(trianglesOffset) * 3LL * 2LL));
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
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLES2Renderer::disposeBufferObjects(vector<int32_t>* bufferObjectIds)
{
	glDeleteBuffers(bufferObjectIds->size(), (const uint32_t*)bufferObjectIds->data());
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

void GLES2Renderer::enableClientState(int32_t clientState)
{
}

void GLES2Renderer::disableClientState(int32_t clientState)
{
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

void GLES2Renderer::checkGLError()
{
	auto error = glGetError();
	if (error != GL_NO_ERROR) {
		Console::println(wstring(L"OpenGL Error: (" + to_wstring(error) + L") @:"));
	}
}
