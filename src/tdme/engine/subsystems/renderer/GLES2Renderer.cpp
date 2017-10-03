#include <tdme/engine/subsystems/renderer/GLES2Renderer.h>

#include <array>
#include <vector>
#include <string>

#include <java/io/BufferedReader.h>
#include <java/io/DataInputStream.h>
#include <java/io/InputStreamReader.h>
#include <java/io/Serializable.h>
#include <java/lang/CharSequence.h>
#include <java/lang/Comparable.h>
#include <java/lang/Object.h>
#include <java/lang/StackTraceElement.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/lang/Thread.h>
#include <tdme/utils/Buffer.h>
#include <tdme/utils/ByteBuffer.h>
#include <tdme/utils/FloatBuffer.h>
#include <tdme/utils/IntBuffer.h>
#include <tdme/utils/ShortBuffer.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utils/_Console.h>
#include <Array.h>
#include <SubArray.h>
#include <ObjectArray.h>

using std::array;
using std::vector;
using std::wstring;

using tdme::engine::subsystems::renderer::GLES2Renderer;
using java::io::BufferedReader;
using java::io::DataInputStream;
using java::io::InputStreamReader;
using java::io::Serializable;
using java::lang::CharSequence;
using java::lang::Comparable;
using java::lang::Object;
using java::lang::StackTraceElement;
using java::lang::String;
using java::lang::StringBuilder;
using java::lang::Thread;
using tdme::utils::Buffer;
using tdme::utils::ByteBuffer;
using tdme::utils::FloatBuffer;
using tdme::utils::IntBuffer;
using tdme::utils::ShortBuffer;
using tdme::engine::Engine;
using tdme::engine::fileio::textures::Texture;
using tdme::math::Matrix4x4;
using tdme::utils::_Console;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

namespace
{
template<typename F>
struct finally_
{
    finally_(F f) : f(f), moved(false) { }
    finally_(finally_ &&x) : f(x.f), moved(false) { x.moved = true; }
    ~finally_() { if(!moved) f(); }
private:
    finally_(const finally_&); finally_& operator=(const finally_&);
    F f;
    bool moved;
};

template<typename F> finally_<F> finally(F f) { return finally_<F>(f); }
}

GLES2Renderer::GLES2Renderer() 
{
	ID_NONE = 0;
	CLEAR_DEPTH_BUFFER_BIT = GLES2::GL_DEPTH_BUFFER_BIT;
	CLEAR_COLOR_BUFFER_BIT = GLES2::GL_COLOR_BUFFER_BIT;
	CULLFACE_FRONT = GLES2::GL_FRONT;
	CULLFACE_BACK = GLES2::GL_BACK;
	FRONTFACE_CW = GLES2::GL_CW;
	FRONTFACE_CCW = GLES2::GL_CCW;
	CLIENTSTATE_TEXTURECOORD_ARRAY = 2;
	CLIENTSTATE_VERTEX_ARRAY = 0;
	CLIENTSTATE_NORMAL_ARRAY = 1;
	CLIENTSTATE_COLOR_ARRAY = 3;
	SHADER_FRAGMENT_SHADER = GLES2::GL_FRAGMENT_SHADER;
	SHADER_VERTEX_SHADER = GLES2::GL_VERTEX_SHADER;
	DEPTHFUNCTION_LESSEQUAL = GLES2::GL_LEQUAL;
	DEPTHFUNCTION_EQUAL = GLES2::GL_EQUAL;
}

String* GLES2Renderer::getGLVersion()
{
	return u"gles2"_j;
}

void GLES2Renderer::initialize()
{
	gl->glGetError();
	FRAMEBUFFER_DEFAULT = gl->getContext()->getDefaultDrawFramebuffer();
	checkGLError();
	gl->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	gl->glClearDepthf(1.0f);
	gl->glEnable(GLES2::GL_DEPTH_TEST);
	gl->glEnable(GLES2::GL_CULL_FACE);
	gl->glDepthFunc(GLES2::GL_LEQUAL);
	gl->glBlendFunc(GLES2::GL_SRC_ALPHA, GLES2::GL_ONE_MINUS_SRC_ALPHA);
	gl->glBlendEquation(GLES2::GL_FUNC_ADD);
	gl->glDisable(GLES2::GL_BLEND);
}

void GLES2Renderer::initializeFrame()
{
	if (gl->getContext()->isCurrent() == false)
		gl->getContext()->makeCurrent();

}

bool GLES2Renderer::isBufferObjectsAvailable()
{
	return true;
}

bool GLES2Renderer::isDepthTextureAvailable()
{
	return gl->glGetString(GL::GL_EXTENSIONS)->indexOf(u"GL_OES_depth_texture"_j) != -1;
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
	/*
	auto handle = gl->glCreateShader(type);
	if (handle == 0)
		return 0;

	auto shaderSources = new StringArray(1);
	shaderSources->set(0, new String());
	DataInputStream* sourceInputStream = nullptr;
	{
		auto finally0 = finally([&] {
			try {
				sourceInputStream->close();
			} catch (IOException* ioe) {
			}
		});
		try {
			sourceInputStream = new DataInputStream(Engine::getInstance()->getInputStream(pathName, fileName));
			auto reader = new BufferedReader(new InputStreamReader(sourceInputStream));
			String* line;
			while ((line = reader->readLine()) != nullptr) {
				shaderSources->set(0, ::java::lang::StringBuilder((*shaderSources)[0]).append(::java::lang::StringBuilder().append(line)->append(u"\n"_j)->toString())->toString());
			}
			sourceInputStream->close();
		} catch (IOException* ioe) {
			gl->glDeleteShader(handle);
			return 0;
		}
	}
	gl->glShaderSource(handle, 1, shaderSources, nullptr);
	gl->glCompileShader(handle);
	auto compileStatus = IntBuffer::allocate(1);
	gl->glGetShaderiv(handle, GLES2::GL_COMPILE_STATUS, compileStatus);
	while (compileStatus->remaining() > 0) {
		auto result = compileStatus->get();
		if (result == 0) {
			auto infoLogLengthBuffer = Buffers::newDirectIntBuffer(1);
			auto infoLogBuffer = Buffers::newDirectByteBuffer(2048);
			gl->glGetShaderInfoLog(handle, infoLogBuffer->limit(), infoLogLengthBuffer, infoLogBuffer);
			auto const infoLogBytes = new int8_tArray(infoLogLengthBuffer->get());
			infoLogBuffer->get(infoLogBytes);
			auto infoLogString = new String(infoLogBytes);
			_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"["_j)->append(handle)
				->append(u"]"_j)
				->append(pathName)
				->append(u"/"_j)
				->append(fileName)
				->append(u": failed: "_j)
				->append(infoLogString)->toString()));
			gl->glDeleteShader(handle);
			return 0;
		}
	}
	return handle;
	*/
	return -1;
}

void GLES2Renderer::useProgram(int32_t programId)
{
	gl->glUseProgram(programId);
}

int32_t GLES2Renderer::createProgram()
{
	auto program = gl->glCreateProgram();
	return program;
}

void GLES2Renderer::attachShaderToProgram(int32_t programId, int32_t shaderId)
{
	gl->glAttachShader(programId, shaderId);
}

bool GLES2Renderer::linkProgram(int32_t programId)
{
	gl->glLinkProgram(programId);
	auto linkStatus = IntBuffer::allocate(1);
	gl->glGetProgramiv(programId, GLES2::GL_LINK_STATUS, linkStatus);
	while (linkStatus->remaining() > 0) {
		auto result = linkStatus->get();
		if (result == 0) {
			auto infoLogLengthBuffer = Buffers::newDirectIntBuffer(1);
			auto infoLogBuffer = Buffers::newDirectByteBuffer(2048);
			gl->glGetProgramInfoLog(programId, infoLogBuffer->limit(), infoLogLengthBuffer, infoLogBuffer);
			auto const infoLogBytes = new int8_tArray(infoLogLengthBuffer->get());
			infoLogBuffer->get(infoLogBytes);
			auto infoLogString = new String(infoLogBytes);
			_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"["_j)->append(programId)
				->append(u"]: failed: "_j)
				->append(infoLogString)->toString()));
			return false;
		}
	}
	return true;
}

int32_t GLES2Renderer::getProgramUniformLocation(int32_t programId, const wstring& name)
{
	auto uniformLocation = gl->glGetUniformLocation(programId, name);
	return uniformLocation;
}

void GLES2Renderer::setProgramUniformInteger(int32_t uniformId, int32_t value)
{
	gl->glUniform1i(uniformId, value);
}

void GLES2Renderer::setProgramUniformFloat(int32_t uniformId, float value)
{
	gl->glUniform1f(uniformId, value);
}

void GLES2Renderer::setProgramUniformFloatMatrix3x3(int32_t uniformId, floatArray* data)
{
	gl->glUniformMatrix3fv(uniformId, 1, false, data, 0);
}

void GLES2Renderer::setProgramUniformFloatMatrix4x4(int32_t uniformId, const array<float, 16>& data)
{
	gl->glUniformMatrix4fv(uniformId, 1, false, data.data(), 0);
}

void GLES2Renderer::setProgramUniformFloatMatrices4x4(int32_t uniformId, int32_t count, FloatBuffer* data)
{
	gl->glUniformMatrix4fv(uniformId, count, false, data);
}

void GLES2Renderer::setProgramUniformFloatVec4(int32_t uniformId, const array<float, 4>& data)
{
	gl->glUniform4fv(uniformId, 1, data.data(), 0);
}

void GLES2Renderer::setProgramUniformFloatVec3(int32_t uniformId, const array<float, 3>& data)
{
	gl->glUniform3fv(uniformId, 1, data.data(), 0);
}

void GLES2Renderer::setProgramAttributeLocation(int32_t programId, int32_t location, const wstring& name)
{
	// gl->glBindAttribLocation(programId, location, name);
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
	gl->glViewport(viewPortX, viewPortY, viewPortWidth, viewPortHeight);
}

void GLES2Renderer::setClearColor(float red, float green, float blue, float alpha)
{
	gl->glClearColor(red, green, blue, alpha);
}

void GLES2Renderer::enableCulling()
{
	gl->glEnable(GLES2::GL_CULL_FACE);
}

void GLES2Renderer::disableCulling()
{
	gl->glDisable(GLES2::GL_CULL_FACE);
}

void GLES2Renderer::enableBlending()
{
	gl->glEnable(GLES2::GL_BLEND);
}

void GLES2Renderer::disableBlending()
{
	gl->glDisable(GLES2::GL_BLEND);
}

void GLES2Renderer::enableDepthBuffer()
{
	gl->glDepthMask(true);
}

void GLES2Renderer::disableDepthBuffer()
{
	gl->glDepthMask(false);
}

void GLES2Renderer::setDepthFunction(int32_t depthFunction)
{
	gl->glDepthFunc(depthFunction);
}

void GLES2Renderer::setColorMask(bool red, bool green, bool blue, bool alpha)
{
	gl->glColorMask(red, green, blue, alpha);
}

void GLES2Renderer::clear(int32_t mask)
{
	gl->glClear(mask);
}

void GLES2Renderer::setCullFace(int32_t cullFace)
{
	gl->glCullFace(cullFace);
}

void GLES2Renderer::setFrontFace(int32_t frontFace)
{
	gl->glFrontFace(frontFace);
}

int32_t GLES2Renderer::createTexture()
{
	auto const tmp = new int32_tArray(1);
	gl->glGenTextures(1, tmp, 0);
	auto textureId = (*tmp)[0];
	return textureId;
}

int32_t GLES2Renderer::createDepthBufferTexture(int32_t width, int32_t height)
{
	int32_t depthTextureGlId;
	auto const tmp = new int32_tArray(1);
	gl->glGenTextures(1, tmp, 0);
	depthTextureGlId = (*tmp)[0];
	gl->glBindTexture(GLES2::GL_TEXTURE_2D, depthTextureGlId);
	gl->glTexImage2D(GLES2::GL_TEXTURE_2D, 0, GLES2::GL_DEPTH_COMPONENT, width, height, 0, GLES2::GL_DEPTH_COMPONENT, GLES2::GL_UNSIGNED_INT, static_cast< Buffer* >(nullptr));
	gl->glTexParameteri(GLES2::GL_TEXTURE_2D, GLES2::GL_TEXTURE_MIN_FILTER, GLES2::GL_NEAREST);
	gl->glTexParameteri(GLES2::GL_TEXTURE_2D, GLES2::GL_TEXTURE_MAG_FILTER, GLES2::GL_NEAREST);
	gl->glTexParameteri(GLES2::GL_TEXTURE_2D, GLES2::GL_TEXTURE_WRAP_S, GLES2::GL_CLAMP_TO_EDGE);
	gl->glTexParameteri(GLES2::GL_TEXTURE_2D, GLES2::GL_TEXTURE_WRAP_T, GLES2::GL_CLAMP_TO_EDGE);
	gl->glBindTexture(GLES2::GL_TEXTURE_2D, ID_NONE);
	return depthTextureGlId;
}

int32_t GLES2Renderer::createColorBufferTexture(int32_t width, int32_t height)
{
	int32_t colorBufferTextureGlId;
	auto const tmp = new int32_tArray(1);
	gl->glGenTextures(1, tmp, 0);
	colorBufferTextureGlId = (*tmp)[0];
	gl->glBindTexture(GLES2::GL_TEXTURE_2D, colorBufferTextureGlId);
	gl->glTexImage2D(GLES2::GL_TEXTURE_2D, 0, GLES2::GL_RGBA, width, height, 0, GLES2::GL_RGBA, GLES2::GL_UNSIGNED_BYTE, static_cast< Buffer* >(nullptr));
	gl->glTexParameteri(GLES2::GL_TEXTURE_2D, GLES2::GL_TEXTURE_MIN_FILTER, GLES2::GL_NEAREST);
	gl->glTexParameteri(GLES2::GL_TEXTURE_2D, GLES2::GL_TEXTURE_MAG_FILTER, GLES2::GL_NEAREST);
	gl->glTexParameteri(GLES2::GL_TEXTURE_2D, GLES2::GL_TEXTURE_WRAP_S, GLES2::GL_CLAMP_TO_EDGE);
	gl->glTexParameteri(GLES2::GL_TEXTURE_2D, GLES2::GL_TEXTURE_WRAP_T, GLES2::GL_CLAMP_TO_EDGE);
	gl->glBindTexture(GLES2::GL_TEXTURE_2D, ID_NONE);
	return colorBufferTextureGlId;
}

void GLES2Renderer::uploadTexture(Texture* texture)
{
	gl->glTexImage2D(GLES2::GL_TEXTURE_2D, 0, texture->getDepth() == 32 ? GLES2::GL_RGBA : GLES2::GL_RGB, texture->getTextureWidth(), texture->getTextureHeight(), 0, texture->getDepth() == 32 ? GLES2::GL_RGBA : GLES2::GL_RGB, GLES2::GL_UNSIGNED_BYTE, static_cast< Buffer* >(texture->getTextureData()));
	gl->glTexParameteri(GLES2::GL_TEXTURE_2D, GLES2::GL_TEXTURE_MIN_FILTER, GLES2::GL_LINEAR_MIPMAP_LINEAR);
	gl->glTexParameteri(GLES2::GL_TEXTURE_2D, GLES2::GL_TEXTURE_MAG_FILTER, GLES2::GL_LINEAR);
	gl->glGenerateMipmap(GLES2::GL_TEXTURE_2D);
}

void GLES2Renderer::resizeDepthBufferTexture(int32_t textureId, int32_t width, int32_t height)
{
	gl->glBindTexture(GLES2::GL_TEXTURE_2D, textureId);
	gl->glTexImage2D(GLES2::GL_TEXTURE_2D, 0, GLES2::GL_DEPTH_COMPONENT, width, height, 0, GLES2::GL_DEPTH_COMPONENT, GLES2::GL_INT, static_cast< Buffer* >(nullptr));
	gl->glBindTexture(GLES2::GL_TEXTURE_2D, 0);
}

void GLES2Renderer::resizeColorBufferTexture(int32_t textureId, int32_t width, int32_t height)
{
	gl->glBindTexture(GLES2::GL_TEXTURE_2D, textureId);
	gl->glTexImage2D(GLES2::GL_TEXTURE_2D, 0, GLES2::GL_RGBA, width, height, 0, GLES2::GL_RGBA, GLES2::GL_UNSIGNED_BYTE, static_cast< Buffer* >(nullptr));
	gl->glBindTexture(GLES2::GL_TEXTURE_2D, 0);
}

void GLES2Renderer::bindTexture(int32_t textureId)
{
	gl->glBindTexture(GLES2::GL_TEXTURE_2D, textureId);
	onBindTexture(textureId);
}

void GLES2Renderer::disposeTexture(int32_t textureId)
{
	gl->glDeleteTextures(1, new int32_tArray({textureId}), 0);
}

int32_t GLES2Renderer::createFramebufferObject(int32_t depthBufferTextureGlId, int32_t colorBufferTextureGlId)
{
	int32_t frameBufferGlId;
	auto fboIds = new int32_tArray(1);
	gl->glGenFramebuffers(1, fboIds, 0);
	frameBufferGlId = (*fboIds)[0];
	gl->glBindFramebuffer(GLES2::GL_FRAMEBUFFER, frameBufferGlId);
	if (depthBufferTextureGlId != ID_NONE) {
		gl->glFramebufferTexture2D(GLES2::GL_FRAMEBUFFER, GLES2::GL_DEPTH_ATTACHMENT, GLES2::GL_TEXTURE_2D, depthBufferTextureGlId, 0);
	}
	if (colorBufferTextureGlId != ID_NONE) {
		gl->glFramebufferTexture2D(GLES2::GL_FRAMEBUFFER, GLES2::GL_COLOR_ATTACHMENT0, GLES2::GL_TEXTURE_2D, colorBufferTextureGlId, 0);
		auto drawBuffers = new int32_tArray({GLES2::GL_COLOR_ATTACHMENT0});
		gl->glDrawBuffers(drawBuffers->length, drawBuffers, 0);
	} else {
		auto drawBuffers = new int32_tArray({GLES2::GL_NONE});
		gl->glDrawBuffers(drawBuffers->length, drawBuffers, 0);
	}
	auto fboStatus = gl->glCheckFramebufferStatus(GLES2::GL_FRAMEBUFFER);
	if (fboStatus != GLES2::GL_FRAMEBUFFER_COMPLETE) {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"GL_FRAMEBUFFER_COMPLETE failed, CANNOT use FBO: "_j)->append(fboStatus)->toString()));
	}
	gl->glBindFramebuffer(GLES2::GL_FRAMEBUFFER, 0);
	return frameBufferGlId;
}

void GLES2Renderer::bindFrameBuffer(int32_t frameBufferId)
{
	gl->glBindFramebuffer(GLES2::GL_FRAMEBUFFER, frameBufferId);
}

void GLES2Renderer::disposeFrameBufferObject(int32_t frameBufferId)
{
	gl->glDeleteFramebuffers(1, new int32_tArray({frameBufferId}), 0);
}

vector<int32_t> GLES2Renderer::createBufferObjects(int32_t buffers)
{
	vector<int32_t> bufferObjectIds;
	bufferObjectIds.resize(buffers);
	gl->glGenBuffers(buffers, bufferObjectIds.data(), 0);
	return bufferObjectIds;
}

void GLES2Renderer::uploadBufferObject(int32_t bufferObjectId, int32_t size, FloatBuffer* data)
{
	gl->glBindBuffer(GLES2::GL_ARRAY_BUFFER, bufferObjectId);
	gl->glBufferData(GLES2::GL_ARRAY_BUFFER, size, data, GLES2::GL_STATIC_DRAW);
	gl->glBindBuffer(GLES2::GL_ARRAY_BUFFER, ID_NONE);
}

void GLES2Renderer::uploadIndicesBufferObject(int32_t bufferObjectId, int32_t size, ShortBuffer* data)
{
	gl->glBindBuffer(GLES2::GL_ELEMENT_ARRAY_BUFFER, bufferObjectId);
	gl->glBufferData(GLES2::GL_ELEMENT_ARRAY_BUFFER, size, data, GLES2::GL_STATIC_DRAW);
	gl->glBindBuffer(GLES2::GL_ELEMENT_ARRAY_BUFFER, ID_NONE);
}

void GLES2Renderer::uploadBufferObject(int32_t bufferObjectId, int32_t size, ShortBuffer* data)
{
	gl->glBindBuffer(GLES2::GL_ARRAY_BUFFER, bufferObjectId);
	gl->glBufferData(GLES2::GL_ARRAY_BUFFER, size, data, GLES2::GL_STATIC_DRAW);
	gl->glBindBuffer(GLES2::GL_ARRAY_BUFFER, ID_NONE);
}

void GLES2Renderer::bindIndicesBufferObject(int32_t bufferObjectId)
{
	gl->glBindBuffer(GLES2::GL_ELEMENT_ARRAY_BUFFER, bufferObjectId);
}

void GLES2Renderer::bindTextureCoordinatesBufferObject(int32_t bufferObjectId)
{
	gl->glBindBuffer(GLES2::GL_ARRAY_BUFFER, bufferObjectId);
	gl->glEnableVertexAttribArray(2);
	gl->glVertexAttribPointer(CLIENTSTATE_TEXTURECOORD_ARRAY, 2, GLES2::GL_FLOAT, false, 0, 0LL);
}

void GLES2Renderer::bindVerticesBufferObject(int32_t bufferObjectId)
{
	gl->glBindBuffer(GLES2::GL_ARRAY_BUFFER, bufferObjectId);
	gl->glEnableVertexAttribArray(0);
	gl->glVertexAttribPointer(CLIENTSTATE_VERTEX_ARRAY, 3, GLES2::GL_FLOAT, false, 0, 0LL);
}

void GLES2Renderer::bindNormalsBufferObject(int32_t bufferObjectId)
{
	gl->glBindBuffer(GLES2::GL_ARRAY_BUFFER, bufferObjectId);
	gl->glEnableVertexAttribArray(1);
	gl->glVertexAttribPointer(CLIENTSTATE_NORMAL_ARRAY, 3, GLES2::GL_FLOAT, false, 0, 0LL);
}

void GLES2Renderer::bindColorsBufferObject(int32_t bufferObjectId)
{
	gl->glBindBuffer(GLES2::GL_ARRAY_BUFFER, bufferObjectId);
	gl->glEnableVertexAttribArray(3);
	gl->glVertexAttribPointer(3, 4, GLES2::GL_FLOAT, false, 0, 0LL);
}

void GLES2Renderer::bindSkinningVerticesJointsBufferObject(int32_t bufferObjectId)
{
	gl->glBindBuffer(GLES2::GL_ARRAY_BUFFER, bufferObjectId);
	gl->glEnableVertexAttribArray(4);
	gl->glVertexAttribPointer(4, 1, GLES2::GL_FLOAT, false, 0, 0LL);
}

void GLES2Renderer::bindSkinningVerticesVertexJointsIdxBufferObject(int32_t bufferObjectId)
{
	gl->glBindBuffer(GLES2::GL_ARRAY_BUFFER, bufferObjectId);
	gl->glEnableVertexAttribArray(5);
	gl->glVertexAttribPointer(5, 4, GLES2::GL_FLOAT, false, 0, 0LL);
}

void GLES2Renderer::bindSkinningVerticesVertexJointsWeightBufferObject(int32_t bufferObjectId)
{
	gl->glBindBuffer(GLES2::GL_ARRAY_BUFFER, bufferObjectId);
	gl->glEnableVertexAttribArray(6);
	gl->glVertexAttribPointer(6, 4, GLES2::GL_FLOAT, false, 0, 0LL);
}

void GLES2Renderer::bindTangentsBufferObject(int32_t bufferObjectId)
{
	_Console::println(static_cast< Object* >(u"GLES2Renderer::bindTangentsBufferObject()::not implemented yet"_j));
}

void GLES2Renderer::bindBitangentsBufferObject(int32_t bufferObjectId)
{
	_Console::println(static_cast< Object* >(u"GLES2Renderer::bindBitangentsBufferObject()::not implemented yet"_j));
}

void GLES2Renderer::drawIndexedTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset)
{
	gl->glDrawElements(GLES2::GL_TRIANGLES, triangles * 3, GLES2::GL_UNSIGNED_SHORT, static_cast< int64_t >(trianglesOffset) * 3LL * 2LL);
}

void GLES2Renderer::drawTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset)
{
	gl->glDrawArrays(GLES2::GL_TRIANGLES, trianglesOffset * 3, triangles * 3);
}

void GLES2Renderer::drawPointsFromBufferObjects(int32_t points, int32_t pointsOffset)
{
	gl->glDrawArrays(GLES2::GL_POINTS, pointsOffset, points);
}

void GLES2Renderer::unbindBufferObjects()
{
	gl->glDisableVertexAttribArray(0);
	gl->glDisableVertexAttribArray(1);
	gl->glDisableVertexAttribArray(2);
	gl->glDisableVertexAttribArray(3);
	gl->glDisableVertexAttribArray(4);
	gl->glDisableVertexAttribArray(5);
	gl->glBindBuffer(GLES2::GL_ARRAY_BUFFER, 0);
}

void GLES2Renderer::disposeBufferObjects(vector<int32_t>* bufferObjectIds)
{
	gl->glDeleteBuffers(bufferObjectIds->size(), (const uint32_t*)bufferObjectIds->data(), 0);
}

int32_t GLES2Renderer::getTextureUnit()
{
	return activeTextureUnit;
}

void GLES2Renderer::setTextureUnit(int32_t textureUnit)
{
	this->activeTextureUnit = textureUnit;
	gl->glActiveTexture(GLES2::GL_TEXTURE0 + textureUnit);
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
	gl->glBindTexture(GLES2::GL_TEXTURE_2D, ID_NONE);
	gl->glEnable(GLES2::GL_BLEND);
	gl->glDisable(GLES2::GL_DEPTH_TEST);
	gl->glDisable(GLES2::GL_CULL_FACE);
}

void GLES2Renderer::doneGuiMode()
{
	gl->glBindTexture(GLES2::GL_TEXTURE_2D, ID_NONE);
	gl->glDisable(GLES2::GL_BLEND);
	gl->glEnable(GLES2::GL_DEPTH_TEST);
	gl->glEnable(GLES2::GL_CULL_FACE);
}

void GLES2Renderer::checkGLError()
{
	auto error = gl->glGetError();
	if (error != GL::GL_NO_ERROR) {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"OpenGL Error: ("_j)->append(error)
			->append(u") @:"_j)->toString()));
		auto stackTrace = Thread::currentThread()->getStackTrace();
		for (auto i = 1; i < 4; i++) {
			_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"\t"_j)->append(static_cast< Object* >((*stackTrace)[i]))->toString()));
		}
	}
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GLES2Renderer::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.renderer.GLES2Renderer", 45);
    return c;
}

java::lang::Class* GLES2Renderer::getClass0()
{
	return class_();
}

