// Generated from /tdme/src/tdme/engine/subsystems/renderer/GL3Renderer.java
#include <tdme/engine/subsystems/renderer/GL3Renderer.h>

#include <java/io/BufferedReader.h>
#include <java/io/DataInputStream.h>
#include <java/io/IOException.h>
#include <java/io/InputStreamReader.h>
#include <java/io/Serializable.h>
#include <java/lang/ArrayStoreException.h>
#include <java/lang/Byte.h>
#include <java/lang/CharSequence.h>
#include <java/lang/ClassCastException.h>
#include <java/lang/Comparable.h>
#include <java/lang/Object.h>
#include <java/lang/StackTraceElement.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/lang/Thread.h>
#include <java/nio/Buffer.h>
#include <java/nio/ByteBuffer.h>
#include <java/nio/ByteOrder.h>
#include <java/nio/FloatBuffer.h>
#include <java/nio/IntBuffer.h>
#include <java/nio/ShortBuffer.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utils/_Console.h>
#include <Array.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::engine::subsystems::renderer::GL3Renderer;
using java::io::BufferedReader;
using java::io::DataInputStream;
using java::io::IOException;
using java::io::InputStreamReader;
using java::io::Serializable;
using java::lang::ArrayStoreException;
using java::lang::Byte;
using java::lang::CharSequence;
using java::lang::ClassCastException;
using java::lang::Comparable;
using java::lang::Object;
using java::lang::StackTraceElement;
using java::lang::String;
using java::lang::StringBuilder;
using java::lang::Thread;
using java::nio::Buffer;
using java::nio::ByteBuffer;
using java::nio::ByteOrder;
using java::nio::FloatBuffer;
using java::nio::IntBuffer;
using java::nio::ShortBuffer;
using tdme::engine::Engine;
using tdme::engine::fileio::textures::Texture;
using tdme::math::Matrix4x4;
using tdme::utils::_Console;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::CharSequence, ObjectArray > CharSequenceArray;
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::StackTraceElement, ObjectArray, ::java::io::SerializableArray > StackTraceElementArray;
typedef ::SubArray< ::java::lang::String, ObjectArray, ::java::io::SerializableArray, ComparableArray, CharSequenceArray > StringArray;
}  // namespace lang
}  // namespace java

namespace tdme {
namespace math {
typedef ::SubArray< ::tdme::math::Matrix4x4, ::java::lang::ObjectArray > Matrix4x4Array;
}  // namespace math
}  // namespace tdme

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
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
GL3Renderer::GL3Renderer(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GL3Renderer::GL3Renderer() 
	: GL3Renderer(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void GL3Renderer::ctor()
{
	super::ctor();
	/*
	ID_NONE = 0;
	CLEAR_DEPTH_BUFFER_BIT = GL3::GL_DEPTH_BUFFER_BIT;
	CLEAR_COLOR_BUFFER_BIT = GL3::GL_COLOR_BUFFER_BIT;
	CULLFACE_FRONT = GL3::GL_FRONT;
	CULLFACE_BACK = GL3::GL_BACK;
	FRONTFACE_CW = GL3::GL_CW;
	FRONTFACE_CCW = GL3::GL_CCW;
	CLIENTSTATE_TEXTURECOORD_ARRAY = -1;
	CLIENTSTATE_VERTEX_ARRAY = -1;
	CLIENTSTATE_NORMAL_ARRAY = -1;
	CLIENTSTATE_COLOR_ARRAY = -1;
	SHADER_FRAGMENT_SHADER = GL3::GL_FRAGMENT_SHADER;
	SHADER_VERTEX_SHADER = GL3::GL_VERTEX_SHADER;
	DEPTHFUNCTION_LESSEQUAL = GL3::GL_LEQUAL;
	DEPTHFUNCTION_EQUAL = GL3::GL_EQUAL;
	*/
}

String* GL3Renderer::getGLVersion()
{
	return u"gl3"_j;
}

void GL3Renderer::initialize()
{
	/*
	gl->glGetError();
	FRAMEBUFFER_DEFAULT = gl->getContext()->getDefaultDrawFramebuffer();
	gl->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	gl->glClearDepth(1.0f);
	gl->glEnable(GL3::GL_DEPTH_TEST);
	gl->glEnable(GL3::GL_CULL_FACE);
	gl->glDepthFunc(GL3::GL_LEQUAL);
	gl->glBlendFunc(GL3::GL_SRC_ALPHA, GL3::GL_ONE_MINUS_SRC_ALPHA);
	gl->glBlendEquation(GL3::GL_FUNC_ADD);
	gl->glDisable(GL3::GL_BLEND);
	gl->glEnable(GL3::GL_PROGRAM_POINT_SIZE);
	setTextureUnit(0);
	auto const tmp = new int32_tArray(1);
	gl->glGenVertexArrays(1, tmp, 0);
	engineVAO = (*tmp)[0];
	*/
}

void GL3Renderer::initializeFrame()
{
	/*
	if (gl->getContext()->isCurrent() == false)
		gl->getContext()->makeCurrent();

	gl->glBindVertexArray(engineVAO);
	*/
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

bool GL3Renderer::isSpecularMappingAvailable()
{
	return true;
}

bool GL3Renderer::isNormalMappingAvailable()
{
	return true;
}

bool GL3Renderer::isDisplacementMappingAvailable()
{
	return false;
}

int32_t GL3Renderer::getTextureUnits()
{
	return -1;
}

int32_t GL3Renderer::loadShader(int32_t type, String* pathName, String* fileName)
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
	gl->glGetShaderiv(handle, GL3::GL_COMPILE_STATUS, compileStatus);
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

void GL3Renderer::useProgram(int32_t programId)
{
	// gl->glUseProgram(programId);
}

int32_t GL3Renderer::createProgram()
{
	/*
	auto glProgram = gl->glCreateProgram();
	return glProgram;
	*/
	return -1;
}

void GL3Renderer::attachShaderToProgram(int32_t programId, int32_t shaderId)
{
	// gl->glAttachShader(programId, shaderId);
}

bool GL3Renderer::linkProgram(int32_t programId)
{
	/*
	gl->glLinkProgram(programId);
	auto linkStatus = IntBuffer::allocate(1);
	gl->glGetProgramiv(programId, GL3::GL_LINK_STATUS, linkStatus);
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
	*/
	return false;
}

int32_t GL3Renderer::getProgramUniformLocation(int32_t programId, String* name)
{
	/*
	auto uniformLocation = gl->glGetUniformLocation(programId, name);
	return uniformLocation;
	*/
	return -1;
}

void GL3Renderer::setProgramUniformInteger(int32_t uniformId, int32_t value)
{
	// gl->glUniform1i(uniformId, value);
}

void GL3Renderer::setProgramUniformFloat(int32_t uniformId, float value)
{
	// gl->glUniform1f(uniformId, value);
}

void GL3Renderer::setProgramUniformFloatMatrix3x3(int32_t uniformId, floatArray* data)
{
	// gl->glUniformMatrix3fv(uniformId, 1, false, data, 0);
}

void GL3Renderer::setProgramUniformFloatMatrix4x4(int32_t uniformId, floatArray* data)
{
	// gl->glUniformMatrix4fv(uniformId, 1, false, data, 0);
}

void GL3Renderer::setProgramUniformFloatMatrices4x4(int32_t uniformId, int32_t count, FloatBuffer* data)
{
	// gl->glUniformMatrix4fv(uniformId, count, false, data);
}

void GL3Renderer::setProgramUniformFloatVec4(int32_t uniformId, floatArray* data)
{
	// gl->glUniform4fv(uniformId, 1, data, 0);
}

void GL3Renderer::setProgramUniformFloatVec3(int32_t uniformId, floatArray* data)
{
	// gl->glUniform3fv(uniformId, 1, data, 0);
}

void GL3Renderer::setProgramAttributeLocation(int32_t programId, int32_t location, String* name)
{
	// gl->glBindAttribLocation(programId, location, name);
}

void GL3Renderer::setViewPort(int32_t x, int32_t y, int32_t width, int32_t height)
{
	this->viewPortX = x;
	this->viewPortY = x;
	this->viewPortWidth = width;
	this->viewPortHeight = height;
	this->pointSize = width > height ? width / 12.0f : height / 12.0f * 16 / 9;
}

void GL3Renderer::updateViewPort()
{
	// gl->glViewport(viewPortX, viewPortY, viewPortWidth, viewPortHeight);
}

Matrix4x4* GL3Renderer::getTextureMatrix()
{
	// return (*textureMatrix)[activeTextureUnit];
	return nullptr;
}

void GL3Renderer::setClearColor(float red, float green, float blue, float alpha)
{
	// gl->glClearColor(red, green, blue, alpha);
}

void GL3Renderer::enableCulling()
{
	// gl->glEnable(GL3::GL_CULL_FACE);
}

void GL3Renderer::disableCulling()
{
	// gl->glDisable(GL3::GL_CULL_FACE);
}

void GL3Renderer::enableBlending()
{
	// gl->glEnable(GL3::GL_BLEND);
}

void GL3Renderer::disableBlending()
{
	// gl->glDisable(GL3::GL_BLEND);
}

void GL3Renderer::enableDepthBuffer()
{
	// gl->glDepthMask(true);
}

void GL3Renderer::disableDepthBuffer()
{
	// gl->glDepthMask(false);
}

void GL3Renderer::setDepthFunction(int32_t depthFunction)
{
	// gl->glDepthFunc(depthFunction);
}

void GL3Renderer::setColorMask(bool red, bool green, bool blue, bool alpha)
{
	// gl->glColorMask(red, green, blue, alpha);
}

void GL3Renderer::clear(int32_t mask)
{
	// gl->glClear(mask);
}

void GL3Renderer::setCullFace(int32_t cullFace)
{
	// gl->glCullFace(cullFace);
}

void GL3Renderer::setFrontFace(int32_t frontFace)
{
	// gl->glFrontFace(frontFace);
}

int32_t GL3Renderer::createTexture()
{
	/*
	auto const tmp = new int32_tArray(1);
	gl->glGenTextures(1, tmp, 0);
	auto textureId = (*tmp)[0];
	return textureId;
	*/
	return -1;
}

int32_t GL3Renderer::createDepthBufferTexture(int32_t width, int32_t height)
{
	/*
	int32_t depthTextureGlId;
	auto const tmp = new int32_tArray(1);
	gl->glGenTextures(1, tmp, 0);
	depthTextureGlId = (*tmp)[0];
	gl->glBindTexture(GL3::GL_TEXTURE_2D, depthTextureGlId);
	gl->glTexImage2D(GL3::GL_TEXTURE_2D, 0, GL3::GL_DEPTH_COMPONENT, width, height, 0, GL3::GL_DEPTH_COMPONENT, GL3::GL_FLOAT, static_cast< Buffer* >(nullptr));
	gl->glTexParameteri(GL3::GL_TEXTURE_2D, GL3::GL_TEXTURE_MIN_FILTER, GL3::GL_NEAREST);
	gl->glTexParameteri(GL3::GL_TEXTURE_2D, GL3::GL_TEXTURE_MAG_FILTER, GL3::GL_NEAREST);
	gl->glTexParameteri(GL3::GL_TEXTURE_2D, GL3::GL_TEXTURE_WRAP_S, GL3::GL_CLAMP_TO_EDGE);
	gl->glTexParameteri(GL3::GL_TEXTURE_2D, GL3::GL_TEXTURE_WRAP_T, GL3::GL_CLAMP_TO_EDGE);
	gl->glBindTexture(GL3::GL_TEXTURE_2D, ID_NONE);
	return depthTextureGlId;
	*/
	return -1;
}

int32_t GL3Renderer::createColorBufferTexture(int32_t width, int32_t height)
{
	/*
	int32_t colorBufferTextureGlId;
	auto const tmp = new int32_tArray(1);
	gl->glGenTextures(1, tmp, 0);
	colorBufferTextureGlId = (*tmp)[0];
	gl->glBindTexture(GL3::GL_TEXTURE_2D, colorBufferTextureGlId);
	gl->glTexImage2D(GL3::GL_TEXTURE_2D, 0, GL3::GL_RGBA, width, height, 0, GL3::GL_RGBA, GL3::GL_UNSIGNED_BYTE, static_cast< Buffer* >(nullptr));
	gl->glTexParameteri(GL3::GL_TEXTURE_2D, GL3::GL_TEXTURE_MIN_FILTER, GL3::GL_NEAREST);
	gl->glTexParameteri(GL3::GL_TEXTURE_2D, GL3::GL_TEXTURE_MAG_FILTER, GL3::GL_NEAREST);
	gl->glTexParameteri(GL3::GL_TEXTURE_2D, GL3::GL_TEXTURE_WRAP_S, GL3::GL_CLAMP_TO_EDGE);
	gl->glTexParameteri(GL3::GL_TEXTURE_2D, GL3::GL_TEXTURE_WRAP_T, GL3::GL_CLAMP_TO_EDGE);
	gl->glBindTexture(GL3::GL_TEXTURE_2D, ID_NONE);
	return colorBufferTextureGlId;
	*/
	return -1;
}

void GL3Renderer::uploadTexture(Texture* texture)
{
	/*
	gl->glTexImage2D(GL3::GL_TEXTURE_2D, 0, texture->getDepth() == 32 ? GL3::GL_RGBA : GL3::GL_RGB, texture->getTextureWidth(), texture->getTextureHeight(), 0, texture->getDepth() == 32 ? GL3::GL_RGBA : GL3::GL_RGB, GL3::GL_UNSIGNED_BYTE, static_cast< Buffer* >(texture->getTextureData()));
	gl->glTexParameteri(GL3::GL_TEXTURE_2D, GL3::GL_TEXTURE_MIN_FILTER, GL3::GL_LINEAR_MIPMAP_LINEAR);
	gl->glTexParameteri(GL3::GL_TEXTURE_2D, GL3::GL_TEXTURE_MAG_FILTER, GL3::GL_LINEAR);
	gl->glGenerateMipmap(GL3::GL_TEXTURE_2D);
	*/
}

void GL3Renderer::resizeDepthBufferTexture(int32_t textureId, int32_t width, int32_t height)
{
	/*
	gl->glBindTexture(GL3::GL_TEXTURE_2D, textureId);
	gl->glTexImage2D(GL3::GL_TEXTURE_2D, 0, GL3::GL_DEPTH_COMPONENT, width, height, 0, GL3::GL_DEPTH_COMPONENT, GL3::GL_FLOAT, static_cast< Buffer* >(nullptr));
	gl->glBindTexture(GL3::GL_TEXTURE_2D, 0);
	*/
}

void GL3Renderer::resizeColorBufferTexture(int32_t textureId, int32_t width, int32_t height)
{
	/*
	gl->glBindTexture(GL3::GL_TEXTURE_2D, textureId);
	gl->glTexImage2D(GL3::GL_TEXTURE_2D, 0, GL3::GL_RGBA, width, height, 0, GL3::GL_RGBA, GL3::GL_UNSIGNED_BYTE, static_cast< Buffer* >(nullptr));
	gl->glBindTexture(GL3::GL_TEXTURE_2D, 0);
	*/
}

void GL3Renderer::bindTexture(int32_t textureId)
{
	/*
	gl->glBindTexture(GL3::GL_TEXTURE_2D, textureId);
	onBindTexture(textureId);
	*/
}

void GL3Renderer::disposeTexture(int32_t textureId)
{
	// gl->glDeleteTextures(1, new int32_tArray({textureId}), 0);
}

int32_t GL3Renderer::createFramebufferObject(int32_t depthBufferTextureGlId, int32_t colorBufferTextureGlId)
{
	/*
	int32_t frameBufferGlId;
	auto fboIds = new int32_tArray(1);
	gl->glGenFramebuffers(1, fboIds, 0);
	frameBufferGlId = (*fboIds)[0];
	gl->glBindFramebuffer(GL3::GL_FRAMEBUFFER, frameBufferGlId);
	if (depthBufferTextureGlId != ID_NONE) {
		gl->glFramebufferTexture(GL3::GL_FRAMEBUFFER, GL3::GL_DEPTH_ATTACHMENT, depthBufferTextureGlId, 0);
	}
	if (colorBufferTextureGlId != ID_NONE) {
		gl->glFramebufferTexture(GL3::GL_FRAMEBUFFER, GL3::GL_COLOR_ATTACHMENT0, colorBufferTextureGlId, 0);
		gl->glDrawBuffer(GL3::GL_COLOR_ATTACHMENT0);
		gl->glReadBuffer(GL3::GL_COLOR_ATTACHMENT0);
	} else {
		gl->glDrawBuffer(GL3::GL_NONE);
		gl->glReadBuffer(GL3::GL_NONE);
	}
	auto fboStatus = gl->glCheckFramebufferStatus(GL3::GL_FRAMEBUFFER);
	if (fboStatus != GL3::GL_FRAMEBUFFER_COMPLETE) {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"GL_FRAMEBUFFER_COMPLETE_EXT failed, CANNOT use FBO: "_j)->append(fboStatus)->toString()));
	}
	gl->glBindFramebuffer(GL3::GL_FRAMEBUFFER, 0);
	return frameBufferGlId;
	*/
	return -1;
}

void GL3Renderer::bindFrameBuffer(int32_t frameBufferId)
{
	// gl->glBindFramebuffer(GL3::GL_FRAMEBUFFER, frameBufferId);
}

void GL3Renderer::disposeFrameBufferObject(int32_t frameBufferId)
{
	// gl->glDeleteFramebuffers(1, new int32_tArray({frameBufferId}), 0);
}

int32_tArray* GL3Renderer::createBufferObjects(int32_t buffers)
{
	/*
	auto bufferObjectIds = new int32_tArray(buffers);
	gl->glGenBuffers(buffers, bufferObjectIds, 0);
	return bufferObjectIds;
	*/
	return nullptr;
}

void GL3Renderer::uploadBufferObject(int32_t bufferObjectId, int32_t size, FloatBuffer* data)
{
	/*
	gl->glBindBuffer(GL3::GL_ARRAY_BUFFER, bufferObjectId);
	gl->glBufferData(GL3::GL_ARRAY_BUFFER, size, data, GL3::GL_STATIC_DRAW);
	gl->glBindBuffer(GL3::GL_ARRAY_BUFFER, ID_NONE);
	*/
}

void GL3Renderer::uploadIndicesBufferObject(int32_t bufferObjectId, int32_t size, ShortBuffer* data)
{
	/*
	gl->glBindBuffer(GL3::GL_ELEMENT_ARRAY_BUFFER, bufferObjectId);
	gl->glBufferData(GL3::GL_ELEMENT_ARRAY_BUFFER, size, data, GL3::GL_STATIC_DRAW);
	gl->glBindBuffer(GL3::GL_ELEMENT_ARRAY_BUFFER, ID_NONE);
	*/
}

void GL3Renderer::uploadBufferObject(int32_t bufferObjectId, int32_t size, ShortBuffer* data)
{
	/*
	gl->glBindBuffer(GL3::GL_ARRAY_BUFFER, bufferObjectId);
	gl->glBufferData(GL3::GL_ARRAY_BUFFER, size, data, GL3::GL_STATIC_DRAW);
	gl->glBindBuffer(GL3::GL_ARRAY_BUFFER, ID_NONE);
	*/
}

void GL3Renderer::bindIndicesBufferObject(int32_t bufferObjectId)
{
	// gl->glBindBuffer(GL3::GL_ELEMENT_ARRAY_BUFFER, bufferObjectId);
}

void GL3Renderer::bindTextureCoordinatesBufferObject(int32_t bufferObjectId)
{
	/*
	gl->glBindBuffer(GL3::GL_ARRAY_BUFFER, bufferObjectId);
	gl->glEnableVertexAttribArray(2);
	gl->glVertexAttribPointer(2, 2, GL3::GL_FLOAT, false, 0, 0LL);
	*/
}

void GL3Renderer::bindVerticesBufferObject(int32_t bufferObjectId)
{
	/*
	gl->glBindBuffer(GL3::GL_ARRAY_BUFFER, bufferObjectId);
	gl->glEnableVertexAttribArray(0);
	gl->glVertexAttribPointer(0, 3, GL3::GL_FLOAT, false, 0, 0LL);
	*/
}

void GL3Renderer::bindNormalsBufferObject(int32_t bufferObjectId)
{
	/*
	gl->glBindBuffer(GL3::GL_ARRAY_BUFFER, bufferObjectId);
	gl->glEnableVertexAttribArray(1);
	gl->glVertexAttribPointer(1, 3, GL3::GL_FLOAT, false, 0, 0LL);
	*/
}

void GL3Renderer::bindColorsBufferObject(int32_t bufferObjectId)
{
	/*
	gl->glBindBuffer(GL3::GL_ARRAY_BUFFER, bufferObjectId);
	gl->glEnableVertexAttribArray(3);
	gl->glVertexAttribPointer(3, 4, GL3::GL_FLOAT, false, 0, 0LL);
	*/
}

void GL3Renderer::bindSkinningVerticesJointsBufferObject(int32_t bufferObjectId)
{
	/*
	gl->glBindBuffer(GL3::GL_ARRAY_BUFFER, bufferObjectId);
	gl->glEnableVertexAttribArray(4);
	gl->glVertexAttribPointer(4, 1, GL3::GL_FLOAT, false, 0, 0LL);
	*/
}

void GL3Renderer::bindSkinningVerticesVertexJointsIdxBufferObject(int32_t bufferObjectId)
{
	/*
	gl->glBindBuffer(GL3::GL_ARRAY_BUFFER, bufferObjectId);
	gl->glEnableVertexAttribArray(5);
	gl->glVertexAttribPointer(5, 4, GL3::GL_FLOAT, false, 0, 0LL);
	*/
}

void GL3Renderer::bindSkinningVerticesVertexJointsWeightBufferObject(int32_t bufferObjectId)
{
	/*
	gl->glBindBuffer(GL3::GL_ARRAY_BUFFER, bufferObjectId);
	gl->glEnableVertexAttribArray(6);
	gl->glVertexAttribPointer(6, 4, GL3::GL_FLOAT, false, 0, 0LL);
	*/
}

void GL3Renderer::bindTangentsBufferObject(int32_t bufferObjectId)
{
	/*
	gl->glBindBuffer(GL3::GL_ARRAY_BUFFER, bufferObjectId);
	gl->glEnableVertexAttribArray(7);
	gl->glVertexAttribPointer(7, 3, GL3::GL_FLOAT, false, 0, 0LL);
	*/
}

void GL3Renderer::bindBitangentsBufferObject(int32_t bufferObjectId)
{
	/*
	gl->glBindBuffer(GL3::GL_ARRAY_BUFFER, bufferObjectId);
	gl->glEnableVertexAttribArray(8);
	gl->glVertexAttribPointer(8, 3, GL3::GL_FLOAT, false, 0, 0LL);
	*/
}

void GL3Renderer::drawIndexedTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset)
{
	// gl->glDrawElements(GL3::GL_TRIANGLES, triangles * 3, GL3::GL_UNSIGNED_SHORT, static_cast< int64_t >(trianglesOffset) * 3LL * 2LL);
}

void GL3Renderer::drawTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset)
{
	// gl->glDrawArrays(GL3::GL_TRIANGLES, trianglesOffset * 3, triangles * 3);
}

void GL3Renderer::drawPointsFromBufferObjects(int32_t points, int32_t pointsOffset)
{
	// gl->glDrawArrays(GL3::GL_POINTS, pointsOffset, points);
}

void GL3Renderer::unbindBufferObjects()
{
	/*
	gl->glDisableVertexAttribArray(0);
	gl->glDisableVertexAttribArray(1);
	gl->glDisableVertexAttribArray(2);
	gl->glDisableVertexAttribArray(3);
	gl->glDisableVertexAttribArray(4);
	gl->glDisableVertexAttribArray(5);
	gl->glDisableVertexAttribArray(6);
	gl->glDisableVertexAttribArray(7);
	gl->glDisableVertexAttribArray(8);
	gl->glBindBuffer(GL3::GL_ARRAY_BUFFER, ID_NONE);
	gl->glBindBuffer(GL3::GL_ELEMENT_ARRAY_BUFFER, ID_NONE);
	*/
}

void GL3Renderer::disposeBufferObjects(int32_tArray* bufferObjectIds)
{
	// gl->glDeleteBuffers(bufferObjectIds->length, bufferObjectIds, 0);
}

int32_t GL3Renderer::getTextureUnit()
{
	// return activeTextureUnit;
	return -1;
}

void GL3Renderer::setTextureUnit(int32_t textureUnit)
{
	/*
	this->activeTextureUnit = textureUnit;
	gl->glActiveTexture(GL3::GL_TEXTURE0 + textureUnit);
	*/
}

void GL3Renderer::enableClientState(int32_t clientState)
{
}

void GL3Renderer::disableClientState(int32_t clientState)
{
}

float GL3Renderer::readPixelDepth(int32_t x, int32_t y)
{
	/*
	pixelDepthBuffer->clear();
	gl->glReadPixels(x, y, 1, 1, GL3::GL_DEPTH_COMPONENT, GL::GL_FLOAT, static_cast< Buffer* >(pixelDepthBuffer));
	return pixelDepthBuffer->get();
	*/
	return -1.0f;
}

ByteBuffer* GL3Renderer::readPixels(int32_t x, int32_t y, int32_t width, int32_t height)
{
	/*
	auto pixelBuffer = ByteBuffer::allocateDirect(width * height * Byte::SIZE* 4)->order(ByteOrder::nativeOrder());
	gl->glPixelStorei(GL3::GL_PACK_ALIGNMENT, 1);
	gl->glReadPixels(x, y, width, height, GL3::GL_RGBA, GL3::GL_UNSIGNED_BYTE, static_cast< Buffer* >(pixelBuffer));
	return pixelBuffer;
	*/
}

void GL3Renderer::initGuiMode()
{
	/*
	setTextureUnit(0);
	gl->glBindTexture(GL3::GL_TEXTURE_2D, ID_NONE);
	gl->glEnable(GL3::GL_BLEND);
	gl->glDisable(GL3::GL_DEPTH_TEST);
	gl->glDisable(GL3::GL_CULL_FACE);
	gl->glGetError();
	*/
}

void GL3Renderer::doneGuiMode()
{
	/*
	gl->glGetError();
	gl->glBindTexture(GL3::GL_TEXTURE_2D, ID_NONE);
	gl->glDisable(GL3::GL_BLEND);
	gl->glEnable(GL3::GL_DEPTH_TEST);
	gl->glEnable(GL3::GL_CULL_FACE);
	*/
}

void GL3Renderer::checkGLError()
{
	/*
	auto error = gl->glGetError();
	if (error != GL::GL_NO_ERROR) {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"OpenGL Error: ("_j)->append(error)
			->append(u") @:"_j)->toString()));
		auto stackTrace = Thread::currentThread()->getStackTrace();
		for (auto i = 1; i < stackTrace->length; i++) {
			_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"\t"_j)->append(static_cast< Object* >((*stackTrace)[i]))->toString()));
		}
	}
	*/
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GL3Renderer::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.renderer.GL3Renderer", 43);
    return c;
}

java::lang::Class* GL3Renderer::getClass0()
{
	return class_();
}

