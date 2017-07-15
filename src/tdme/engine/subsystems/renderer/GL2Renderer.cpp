// Generated from /tdme/src/tdme/engine/subsystems/renderer/GL2Renderer.java
#include <tdme/engine/subsystems/renderer/GL2Renderer.h>

#include <java/io/BufferedReader.h>
#include <java/io/DataInputStream.h>
#include <java/io/InputStreamReader.h>
#include <java/io/Serializable.h>
#include <java/lang/Byte.h>
#include <java/lang/CharSequence.h>
#include <java/lang/Comparable.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
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

using tdme::engine::subsystems::renderer::GL2Renderer;
using java::io::BufferedReader;
using java::io::DataInputStream;
using java::io::InputStreamReader;
using java::io::Serializable;
using java::lang::Byte;
using java::lang::CharSequence;
using java::lang::Comparable;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
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
GL2Renderer::GL2Renderer(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GL2Renderer::GL2Renderer() 
	: GL2Renderer(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void GL2Renderer::ctor()
{
	super::ctor();
	/*
	ID_NONE = 0;
	CLEAR_DEPTH_BUFFER_BIT = GL2::GL_DEPTH_BUFFER_BIT;
	CLEAR_COLOR_BUFFER_BIT = GL2::GL_COLOR_BUFFER_BIT;
	CULLFACE_FRONT = GL2::GL_FRONT;
	CULLFACE_BACK = GL2::GL_BACK;
	FRONTFACE_CW = GL2::GL_CW;
	FRONTFACE_CCW = GL2::GL_CCW;
	CLIENTSTATE_TEXTURECOORD_ARRAY = GL2::GL_TEXTURE_COORD_ARRAY;
	CLIENTSTATE_VERTEX_ARRAY = GL2::GL_VERTEX_ARRAY;
	CLIENTSTATE_NORMAL_ARRAY = GL2::GL_NORMAL_ARRAY;
	CLIENTSTATE_COLOR_ARRAY = GL2::GL_COLOR_ARRAY;
	SHADER_FRAGMENT_SHADER = GL2::GL_FRAGMENT_SHADER;
	SHADER_VERTEX_SHADER = GL2::GL_VERTEX_SHADER;
	DEPTHFUNCTION_LESSEQUAL = GL2::GL_LEQUAL;
	DEPTHFUNCTION_EQUAL = GL2::GL_EQUAL;
	bufferObjectsAvailable = false;
	*/
}

String* GL2Renderer::getGLVersion()
{
	return u"gl2"_j;
}

bool GL2Renderer::checkBufferObjectsAvailable()
{
	auto extensionOK = gl->isExtensionAvailable(u"GL_ARB_vertex_buffer_object"_j);
	auto functionsOK = gl->isFunctionAvailable(u"glGenBuffersARB"_j) && gl->isFunctionAvailable(u"glBindBufferARB"_j) && gl->isFunctionAvailable(u"glBufferDataARB"_j)&& gl->isFunctionAvailable(u"glDeleteBuffersARB"_j);
	return extensionOK == true && functionsOK == true;
}

bool GL2Renderer::isDepthTextureAvailable()
{
	return true;
}

void GL2Renderer::initialize()
{
	gl->glGetError();
	FRAMEBUFFER_DEFAULT = gl->getContext()->getDefaultDrawFramebuffer();
	bufferObjectsAvailable = checkBufferObjectsAvailable();
	gl->glShadeModel(GL2::GL_SMOOTH);
	gl->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	gl->glClearDepth(1.0f);
	gl->glEnable(GL2::GL_DEPTH_TEST);
	gl->glEnable(GL2::GL_CULL_FACE);
	gl->glDepthFunc(GL2::GL_LEQUAL);
	gl->glHint(GL2::GL_PERSPECTIVE_CORRECTION_HINT, GL2::GL_NICEST);
	gl->glBlendFunc(GL2::GL_SRC_ALPHA, GL2::GL_ONE_MINUS_SRC_ALPHA);
	gl->glBlendEquation(GL2::GL_FUNC_ADD);
	gl->glDisable(GL2::GL_BLEND);
	gl->glEnable(GL2::GL_PROGRAM_POINT_SIZE_EXT);
	setTextureUnit(0);
}

void GL2Renderer::initializeFrame()
{
	if (gl->getContext()->isCurrent() == false)
		gl->getContext()->makeCurrent();

}

bool GL2Renderer::isBufferObjectsAvailable()
{
	return bufferObjectsAvailable;
}

bool GL2Renderer::isUsingProgramAttributeLocation()
{
	return false;
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

int32_t GL2Renderer::getTextureUnits()
{
	auto tmp = IntBuffer::allocate(1);
	gl->glGetIntegerv(GL2::GL_MAX_TEXTURE_UNITS, tmp);
	while (tmp->remaining() > 0) {
		auto textureUnits = tmp->get();
		return textureUnits;
	}
	return -1;
}

int32_t GL2Renderer::loadShader(int32_t type, String* pathName, String* fileName)
{
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
	gl->glShaderSourceARB(handle, 1, shaderSources, nullptr);
	gl->glCompileShaderARB(handle);
	auto compileStatus = IntBuffer::allocate(1);
	gl->glGetObjectParameterivARB(handle, GL2::GL_OBJECT_COMPILE_STATUS_ARB, compileStatus);
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
}

void GL2Renderer::useProgram(int32_t programId)
{
	gl->glUseProgramObjectARB(programId);
}

int32_t GL2Renderer::createProgram()
{
	auto programId = gl->glCreateProgram();
	return programId;
}

void GL2Renderer::attachShaderToProgram(int32_t programId, int32_t shaderId)
{
	gl->glAttachObjectARB(programId, shaderId);
}

bool GL2Renderer::linkProgram(int32_t programId)
{
	gl->glLinkProgramARB(programId);
	auto linkStatus = IntBuffer::allocate(1);
	gl->glGetProgramiv(programId, GL2::GL_LINK_STATUS, linkStatus);
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

int32_t GL2Renderer::getProgramUniformLocation(int32_t programId, String* name)
{
	auto uniformLocation = gl->glGetUniformLocationARB(programId, name);
	return uniformLocation;
}

void GL2Renderer::setProgramUniformInteger(int32_t uniformId, int32_t value)
{
	gl->glUniform1iARB(uniformId, value);
}

void GL2Renderer::setProgramUniformFloat(int32_t uniformId, float value)
{
	gl->glUniform1fARB(uniformId, value);
}

void GL2Renderer::setProgramUniformFloatMatrix3x3(int32_t uniformId, floatArray* data)
{
	gl->glUniformMatrix3fv(uniformId, 1, false, data, 0);
}

void GL2Renderer::setProgramUniformFloatMatrices4x4(int32_t uniformId, int32_t count, FloatBuffer* data)
{
	gl->glUniformMatrix4fv(uniformId, count, false, data);
}

void GL2Renderer::setProgramUniformFloatMatrix4x4(int32_t uniformId, floatArray* data)
{
	gl->glUniformMatrix4fv(uniformId, 1, false, data, 0);
}

void GL2Renderer::setProgramUniformFloatVec4(int32_t uniformId, floatArray* data)
{
	gl->glUniform4fv(uniformId, 1, data, 0);
}

void GL2Renderer::setProgramUniformFloatVec3(int32_t uniformId, floatArray* data)
{
	gl->glUniform3fv(uniformId, 1, data, 0);
}

void GL2Renderer::setProgramAttributeLocation(int32_t programId, int32_t location, String* name)
{
	gl->glBindAttribLocation(programId, location, name);
}

void GL2Renderer::setViewPort(int32_t x, int32_t y, int32_t width, int32_t height)
{
	this->viewPortX = x;
	this->viewPortY = x;
	this->viewPortWidth = width;
	this->viewPortHeight = height;
	this->pointSize = width > height ? width / 12.0f : height / 12.0f * 16 / 9;
}

void GL2Renderer::updateViewPort()
{
	gl->glViewport(viewPortX, viewPortY, viewPortWidth, viewPortHeight);
}

Matrix4x4* GL2Renderer::getTextureMatrix()
{
	return (*textureMatrix)[activeTextureUnit];
}

void GL2Renderer::setClearColor(float red, float green, float blue, float alpha)
{
	gl->glClearColor(red, green, blue, alpha);
}

void GL2Renderer::enableCulling()
{
	gl->glEnable(GL2::GL_CULL_FACE);
}

void GL2Renderer::disableCulling()
{
	gl->glDisable(GL2::GL_CULL_FACE);
}

void GL2Renderer::enableBlending()
{
	gl->glEnable(GL2::GL_BLEND);
}

void GL2Renderer::disableBlending()
{
	gl->glDisable(GL2::GL_BLEND);
}

void GL2Renderer::enableDepthBuffer()
{
	gl->glDepthMask(true);
}

void GL2Renderer::disableDepthBuffer()
{
	gl->glDepthMask(false);
}

void GL2Renderer::setDepthFunction(int32_t depthFunction)
{
	gl->glDepthFunc(depthFunction);
}

void GL2Renderer::setColorMask(bool red, bool green, bool blue, bool alpha)
{
	gl->glColorMask(red, green, blue, alpha);
}

void GL2Renderer::clear(int32_t mask)
{
	gl->glClear(mask);
}

void GL2Renderer::setCullFace(int32_t cullFace)
{
	gl->glCullFace(cullFace);
}

void GL2Renderer::setFrontFace(int32_t frontFace)
{
	gl->glFrontFace(frontFace);
}

int32_t GL2Renderer::createTexture()
{
	auto const tmp = new int32_tArray(1);
	gl->glGenTextures(1, tmp, 0);
	auto textureId = (*tmp)[0];
	return textureId;
}

int32_t GL2Renderer::createDepthBufferTexture(int32_t width, int32_t height)
{
	int32_t depthTextureGlId;
	auto const tmp = new int32_tArray(1);
	gl->glGenTextures(1, tmp, 0);
	depthTextureGlId = (*tmp)[0];
	gl->glBindTexture(GL2::GL_TEXTURE_2D, depthTextureGlId);
	gl->glTexImage2D(GL2::GL_TEXTURE_2D, 0, GL2::GL_DEPTH_COMPONENT, width, height, 0, GL2::GL_DEPTH_COMPONENT, GL2::GL_FLOAT, static_cast< Buffer* >(nullptr));
	gl->glTexParameteri(GL2::GL_TEXTURE_2D, GL2::GL_TEXTURE_MIN_FILTER, GL2::GL_NEAREST);
	gl->glTexParameteri(GL2::GL_TEXTURE_2D, GL2::GL_TEXTURE_MAG_FILTER, GL2::GL_NEAREST);
	gl->glTexParameterf(GL2::GL_TEXTURE_2D, GL2::GL_TEXTURE_WRAP_S, GL2::GL_CLAMP_TO_EDGE);
	gl->glTexParameterf(GL2::GL_TEXTURE_2D, GL2::GL_TEXTURE_WRAP_T, GL2::GL_CLAMP_TO_EDGE);
	gl->glBindTexture(GL2::GL_TEXTURE_2D, ID_NONE);
	return depthTextureGlId;
}

int32_t GL2Renderer::createColorBufferTexture(int32_t width, int32_t height)
{
	int32_t colorBufferTextureGlId;
	auto const tmp = new int32_tArray(1);
	gl->glGenTextures(1, tmp, 0);
	colorBufferTextureGlId = (*tmp)[0];
	gl->glBindTexture(GL2::GL_TEXTURE_2D, colorBufferTextureGlId);
	gl->glTexImage2D(GL2::GL_TEXTURE_2D, 0, GL2::GL_RGBA, width, height, 0, GL2::GL_RGBA, GL2::GL_UNSIGNED_BYTE, static_cast< Buffer* >(nullptr));
	gl->glTexParameteri(GL2::GL_TEXTURE_2D, GL2::GL_TEXTURE_MIN_FILTER, GL2::GL_NEAREST);
	gl->glTexParameteri(GL2::GL_TEXTURE_2D, GL2::GL_TEXTURE_MAG_FILTER, GL2::GL_NEAREST);
	gl->glTexParameteri(GL2::GL_TEXTURE_2D, GL2::GL_TEXTURE_WRAP_S, GL2::GL_CLAMP_TO_EDGE);
	gl->glTexParameteri(GL2::GL_TEXTURE_2D, GL2::GL_TEXTURE_WRAP_T, GL2::GL_CLAMP_TO_EDGE);
	gl->glBindTexture(GL2::GL_TEXTURE_2D, ID_NONE);
	return colorBufferTextureGlId;
}

void GL2Renderer::uploadTexture(Texture* texture)
{
	gl->glTexImage2D(GL2::GL_TEXTURE_2D, 0, texture->getDepth() == 32 ? GL2::GL_RGBA : GL2::GL_RGB, texture->getTextureWidth(), texture->getTextureHeight(), 0, texture->getDepth() == 32 ? GL2::GL_RGBA : GL2::GL_RGB, GL2::GL_UNSIGNED_BYTE, static_cast< Buffer* >(texture->getTextureData()));
	gl->glTexParameteri(GL2::GL_TEXTURE_2D, GL2::GL_TEXTURE_MIN_FILTER, GL2::GL_LINEAR_MIPMAP_LINEAR);
	gl->glTexParameteri(GL2::GL_TEXTURE_2D, GL2::GL_TEXTURE_MAG_FILTER, GL2::GL_LINEAR);
	gl->glGenerateMipmap(GL2::GL_TEXTURE_2D);
}

void GL2Renderer::resizeDepthBufferTexture(int32_t textureId, int32_t width, int32_t height)
{
	gl->glBindTexture(GL2::GL_TEXTURE_2D, textureId);
	gl->glTexImage2D(GL2::GL_TEXTURE_2D, 0, GL2::GL_DEPTH_COMPONENT, width, height, 0, GL2::GL_DEPTH_COMPONENT, GL2::GL_FLOAT, static_cast< Buffer* >(nullptr));
	gl->glBindTexture(GL2::GL_TEXTURE_2D, 0);
}

void GL2Renderer::resizeColorBufferTexture(int32_t textureId, int32_t width, int32_t height)
{
	gl->glBindTexture(GL2::GL_TEXTURE_2D, textureId);
	gl->glTexImage2D(GL2::GL_TEXTURE_2D, 0, GL2::GL_RGBA, width, height, 0, GL2::GL_RGBA, GL2::GL_UNSIGNED_BYTE, static_cast< Buffer* >(nullptr));
	gl->glBindTexture(GL2::GL_TEXTURE_2D, 0);
}

void GL2Renderer::bindTexture(int32_t textureId)
{
	gl->glBindTexture(GL2::GL_TEXTURE_2D, textureId);
	onBindTexture(textureId);
}

void GL2Renderer::disposeTexture(int32_t textureId)
{
	gl->glDeleteTextures(1, new int32_tArray({textureId}), 0);
}

int32_t GL2Renderer::createFramebufferObject(int32_t depthBufferTextureGlId, int32_t colorBufferTextureGlId)
{
	int32_t frameBufferGlId;
	auto fboIds = new int32_tArray(1);
	gl->glGenFramebuffers(1, fboIds, 0);
	frameBufferGlId = (*fboIds)[0];
	gl->glBindFramebuffer(GL2::GL_FRAMEBUFFER, frameBufferGlId);
	if (depthBufferTextureGlId != ID_NONE) {
		gl->glFramebufferTexture2D(GL2::GL_FRAMEBUFFER, GL2::GL_DEPTH_ATTACHMENT, GL2::GL_TEXTURE_2D, depthBufferTextureGlId, 0);
	}
	if (colorBufferTextureGlId != ID_NONE) {
		gl->glFramebufferTexture2D(GL2::GL_FRAMEBUFFER, GL2::GL_COLOR_ATTACHMENT0, GL2::GL_TEXTURE_2D, colorBufferTextureGlId, 0);
		gl->glDrawBuffer(GL2::GL_COLOR_ATTACHMENT0);
		gl->glReadBuffer(GL2::GL_COLOR_ATTACHMENT0);
	} else {
		gl->glDrawBuffer(GL2::GL_NONE);
		gl->glReadBuffer(GL2::GL_NONE);
	}
	auto fboStatus = gl->glCheckFramebufferStatus(GL2::GL_FRAMEBUFFER);
	if (fboStatus != GL2::GL_FRAMEBUFFER_COMPLETE) {
		_Console::println(static_cast< Object* >(u"GL_FRAMEBUFFER_COMPLETE_EXT failed, CANNOT use FBO\n"_j));
	}
	gl->glBindFramebuffer(GL2::GL_FRAMEBUFFER, 0);
	return frameBufferGlId;
}

void GL2Renderer::bindFrameBuffer(int32_t frameBufferId)
{
	gl->glBindFramebuffer(GL2::GL_FRAMEBUFFER, frameBufferId);
}

void GL2Renderer::disposeFrameBufferObject(int32_t frameBufferId)
{
	gl->glDeleteFramebuffers(1, new int32_tArray({frameBufferId}), 0);
}

int32_tArray* GL2Renderer::createBufferObjects(int32_t buffers)
{
	auto bufferObjectIds = new int32_tArray(buffers);
	gl->glGenBuffers(buffers, bufferObjectIds, 0);
	return bufferObjectIds;
}

void GL2Renderer::uploadBufferObject(int32_t bufferObjectId, int32_t size, FloatBuffer* data)
{
	gl->glBindBuffer(GL2::GL_ARRAY_BUFFER, bufferObjectId);
	gl->glBufferData(GL2::GL_ARRAY_BUFFER, size, data, GL2::GL_STATIC_DRAW);
	gl->glBindBuffer(GL2::GL_ARRAY_BUFFER, ID_NONE);
}

void GL2Renderer::uploadIndicesBufferObject(int32_t bufferObjectId, int32_t size, ShortBuffer* data)
{
	gl->glBindBuffer(GL2::GL_ELEMENT_ARRAY_BUFFER, bufferObjectId);
	gl->glBufferData(GL2::GL_ELEMENT_ARRAY_BUFFER, size, data, GL2::GL_STATIC_DRAW);
	gl->glBindBuffer(GL2::GL_ELEMENT_ARRAY_BUFFER, ID_NONE);
}

void GL2Renderer::uploadBufferObject(int32_t bufferObjectId, int32_t size, ShortBuffer* data)
{
	gl->glBindBuffer(GL2::GL_ARRAY_BUFFER, bufferObjectId);
	gl->glBufferData(GL2::GL_ARRAY_BUFFER, size, data, GL2::GL_STATIC_DRAW);
	gl->glBindBuffer(GL2::GL_ARRAY_BUFFER, ID_NONE);
}

void GL2Renderer::bindIndicesBufferObject(int32_t bufferObjectId)
{
	gl->glBindBuffer(GL2::GL_ELEMENT_ARRAY_BUFFER, bufferObjectId);
}

void GL2Renderer::bindTextureCoordinatesBufferObject(int32_t bufferObjectId)
{
	gl->glBindBuffer(GL2::GL_ARRAY_BUFFER, bufferObjectId);
	gl->glTexCoordPointer(2, GL2::GL_FLOAT, 0, 0LL);
}

void GL2Renderer::bindVerticesBufferObject(int32_t bufferObjectId)
{
	gl->glBindBuffer(GL2::GL_ARRAY_BUFFER, bufferObjectId);
	gl->glVertexPointer(3, GL2::GL_FLOAT, 0, 0LL);
}

void GL2Renderer::bindNormalsBufferObject(int32_t bufferObjectId)
{
	gl->glBindBuffer(GL2::GL_ARRAY_BUFFER, bufferObjectId);
	gl->glNormalPointer(GL2::GL_FLOAT, 0, 0LL);
}

void GL2Renderer::bindColorsBufferObject(int32_t bufferObjectId)
{
	gl->glBindBuffer(GL2::GL_ARRAY_BUFFER, bufferObjectId);
	gl->glColorPointer(4, GL2::GL_FLOAT, 0, 0LL);
}

void GL2Renderer::bindSkinningVerticesJointsBufferObject(int32_t bufferObjectId)
{
	_Console::println(static_cast< Object* >(u"GL2Renderer::bindSkinningVerticesJointsBufferObject()::not implemented yet"_j));
}

void GL2Renderer::bindSkinningVerticesVertexJointsIdxBufferObject(int32_t bufferObjectId)
{
	_Console::println(static_cast< Object* >(u"GL2Renderer::bindSkinningVerticesVertexJointsIdxBufferObject()::not implemented yet"_j));
}

void GL2Renderer::bindSkinningVerticesVertexJointsWeightBufferObject(int32_t bufferObjectId)
{
	_Console::println(static_cast< Object* >(u"GL2Renderer::bindSkinningVerticesVertexJointsWeightBufferObject()::not implemented yet"_j));
}

void GL2Renderer::bindTangentsBufferObject(int32_t bufferObjectId)
{
	_Console::println(static_cast< Object* >(u"GL2Renderer::bindTangentsBufferObject()::not implemented yet"_j));
}

void GL2Renderer::bindBitangentsBufferObject(int32_t bufferObjectId)
{
	_Console::println(static_cast< Object* >(u"GL2Renderer::bindBitangentsBufferObject()::not implemented yet"_j));
}

void GL2Renderer::drawIndexedTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset)
{
	gl->glDrawElements(GL2::GL_TRIANGLES, triangles * 3, GL2::GL_UNSIGNED_SHORT, static_cast< int64_t >(trianglesOffset) * 3LL * 2LL);
}

void GL2Renderer::drawTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset)
{
	gl->glDrawArrays(GL2::GL_TRIANGLES, trianglesOffset * 3, triangles * 3);
}

void GL2Renderer::drawPointsFromBufferObjects(int32_t points, int32_t pointsOffset)
{
	gl->glDrawArrays(GL2::GL_POINTS, pointsOffset, points);
}

void GL2Renderer::unbindBufferObjects()
{
	gl->glBindBuffer(GL2::GL_ARRAY_BUFFER, 0);
}

void GL2Renderer::disposeBufferObjects(int32_tArray* bufferObjectIds)
{
	gl->glDeleteBuffers(bufferObjectIds->length, bufferObjectIds, 0);
}

int32_t GL2Renderer::getTextureUnit()
{
	return activeTextureUnit;
}

void GL2Renderer::setTextureUnit(int32_t textureUnit)
{
	this->activeTextureUnit = textureUnit;
	gl->glActiveTexture(GL2::GL_TEXTURE0 + textureUnit);
}

void GL2Renderer::enableClientState(int32_t clientState)
{
	// gl->glEnableClientState(clientState);
}

void GL2Renderer::disableClientState(int32_t clientState)
{
	// gl->glDisableClientState(clientState);
}

float GL2Renderer::readPixelDepth(int32_t x, int32_t y)
{
	pixelDepthBuffer->clear();
	gl->glReadPixels(x, y, 1, 1, GL2::GL_DEPTH_COMPONENT, GL::GL_FLOAT, static_cast< Buffer* >(pixelDepthBuffer));
	return pixelDepthBuffer->get();
}

ByteBuffer* GL2Renderer::readPixels(int32_t x, int32_t y, int32_t width, int32_t height)
{
	auto pixelBuffer = ByteBuffer::allocateDirect(width * height * Byte::SIZE* 4);
	gl->glPixelStorei(GL2::GL_PACK_ALIGNMENT, 1);
	gl->glReadPixels(x, y, width, height, GL2::GL_RGBA, GL2::GL_UNSIGNED_BYTE, static_cast< Buffer* >(pixelBuffer));
	return pixelBuffer;
}

void GL2Renderer::initGuiMode()
{
	setTextureUnit(0);
	gl->glBindTexture(GL2::GL_TEXTURE_2D, ID_NONE);
	gl->glEnable(GL2::GL_BLEND);
	gl->glDisable(GL2::GL_DEPTH_TEST);
	gl->glDisable(GL2::GL_CULL_FACE);
	gl->glGetError();
}

void GL2Renderer::doneGuiMode()
{
	gl->glGetError();
	gl->glBindTexture(GL2::GL_TEXTURE_2D, ID_NONE);
	gl->glDisable(GL2::GL_BLEND);
	gl->glEnable(GL2::GL_DEPTH_TEST);
	gl->glEnable(GL2::GL_CULL_FACE);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GL2Renderer::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.renderer.GL2Renderer", 43);
    return c;
}

java::lang::Class* GL2Renderer::getClass0()
{
	return class_();
}

