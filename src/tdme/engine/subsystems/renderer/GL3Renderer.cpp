// Generated from /tdme/src/tdme/engine/subsystems/renderer/GL3Renderer.java
#include <tdme/engine/subsystems/renderer/GL3Renderer.h>

#include <OpenGL/gl3.h>

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
#include <tdme/utils/StringConverter.h>
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
using tdme::utils::StringConverter;
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
	ID_NONE = 0;
	CLEAR_DEPTH_BUFFER_BIT = GL_DEPTH_BUFFER_BIT;
	CLEAR_COLOR_BUFFER_BIT = GL_COLOR_BUFFER_BIT;
	CULLFACE_FRONT = GL_FRONT;
	CULLFACE_BACK = GL_BACK;
	FRONTFACE_CW = GL_CW;
	FRONTFACE_CCW = GL_CCW;
	CLIENTSTATE_TEXTURECOORD_ARRAY = -1;
	CLIENTSTATE_VERTEX_ARRAY = -1;
	CLIENTSTATE_NORMAL_ARRAY = -1;
	CLIENTSTATE_COLOR_ARRAY = -1;
	SHADER_FRAGMENT_SHADER = GL_FRAGMENT_SHADER;
	SHADER_VERTEX_SHADER = GL_VERTEX_SHADER;
	DEPTHFUNCTION_LESSEQUAL = GL_LEQUAL;
	DEPTHFUNCTION_EQUAL = GL_EQUAL;
}

String* GL3Renderer::getGLVersion()
{
	return u"gl3"_j;
}

void GL3Renderer::initialize()
{
	glGetError();
	FRAMEBUFFER_DEFAULT = 0; //getContext()->getDefaultDrawFramebuffer();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);
	glDisable(GL_BLEND);
	glEnable(GL_PROGRAM_POINT_SIZE);
	setTextureUnit(0);
	glGenVertexArrays(1, &engineVAO);
}

void GL3Renderer::initializeFrame()
{
	/*
	if (getContext()->isCurrent() == false)
		getContext()->makeCurrent();

	glBindVertexArray(engineVAO);
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
	auto handle = glCreateShader(type);
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
			glDeleteShader(handle);
			return 0;
		}
	}
	glShaderSource(handle, 1, shaderSources, nullptr);
	glCompileShader(handle);
	auto compileStatus = IntBuffer::allocate(1);
	glGetShaderiv(handle, GL_COMPILE_STATUS, compileStatus);
	while (compileStatus->remaining() > 0) {
		auto result = compileStatus->get();
		if (result == 0) {
			auto infoLogLengthBuffer = Buffers::newDirectIntBuffer(1);
			auto infoLogBuffer = Buffers::newDirectByteBuffer(2048);
			glGetShaderInfoLog(handle, infoLogBuffer->limit(), infoLogLengthBuffer, infoLogBuffer);
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
			glDeleteShader(handle);
			return 0;
		}
	}
	return handle;
	*/
	return -1;
}

void GL3Renderer::useProgram(int32_t programId)
{
	glUseProgram(programId);
}

int32_t GL3Renderer::createProgram()
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
	/*
	glLinkProgram(programId);
	auto linkStatus = IntBuffer::allocate(1);
	glGetProgramiv(programId, GL_LINK_STATUS, linkStatus);
	while (linkStatus->remaining() > 0) {
		auto result = linkStatus->get();
		if (result == 0) {
			auto infoLogLengthBuffer = Buffers::newDirectIntBuffer(1);
			auto infoLogBuffer = Buffers::newDirectByteBuffer(2048);
			glGetProgramInfoLog(programId, infoLogBuffer->limit(), infoLogLengthBuffer, infoLogBuffer);
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
	auto uniformLocation = glGetUniformLocation(programId, StringConverter::toString(name->getCPPWString()).c_str());
	return uniformLocation;
}

void GL3Renderer::setProgramUniformInteger(int32_t uniformId, int32_t value)
{
	glUniform1i(uniformId, value);
}

void GL3Renderer::setProgramUniformFloat(int32_t uniformId, float value)
{
	glUniform1f(uniformId, value);
}

void GL3Renderer::setProgramUniformFloatMatrix3x3(int32_t uniformId, floatArray* data)
{
	glUniformMatrix3fv(uniformId, 1, false, data->getPointer());
}

void GL3Renderer::setProgramUniformFloatMatrix4x4(int32_t uniformId, floatArray* data)
{
	glUniformMatrix4fv(uniformId, 1, false, data->getPointer());
}

void GL3Renderer::setProgramUniformFloatMatrices4x4(int32_t uniformId, int32_t count, FloatBuffer* data)
{
	glUniformMatrix4fv(uniformId, count, false, (float*)data->getBuffer());
}

void GL3Renderer::setProgramUniformFloatVec4(int32_t uniformId, floatArray* data)
{
	glUniform4fv(uniformId, 1, data->getPointer());
}

void GL3Renderer::setProgramUniformFloatVec3(int32_t uniformId, floatArray* data)
{
	glUniform3fv(uniformId, 1, data->getPointer());
}

void GL3Renderer::setProgramAttributeLocation(int32_t programId, int32_t location, String* name)
{
	glBindAttribLocation(programId, location, StringConverter::toString(name->getCPPWString()).c_str());
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
	glViewport(viewPortX, viewPortY, viewPortWidth, viewPortHeight);
}

Matrix4x4* GL3Renderer::getTextureMatrix()
{
	return (*textureMatrix)[activeTextureUnit];
	return nullptr;
}

void GL3Renderer::setClearColor(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
}

void GL3Renderer::enableCulling()
{
	glEnable(GL_CULL_FACE);
}

void GL3Renderer::disableCulling()
{
	glDisable(GL_CULL_FACE);
}

void GL3Renderer::enableBlending()
{
	glEnable(GL_BLEND);
}

void GL3Renderer::disableBlending()
{
	glDisable(GL_BLEND);
}

void GL3Renderer::enableDepthBuffer()
{
	glDepthMask(true);
}

void GL3Renderer::disableDepthBuffer()
{
	glDepthMask(false);
}

void GL3Renderer::setDepthFunction(int32_t depthFunction)
{
	glDepthFunc(depthFunction);
}

void GL3Renderer::setColorMask(bool red, bool green, bool blue, bool alpha)
{
	glColorMask(red, green, blue, alpha);
}

void GL3Renderer::clear(int32_t mask)
{
	glClear(mask);
}

void GL3Renderer::setCullFace(int32_t cullFace)
{
	glCullFace(cullFace);
}

void GL3Renderer::setFrontFace(int32_t frontFace)
{
	glFrontFace(frontFace);
}

int32_t GL3Renderer::createTexture()
{
	uint32_t textureId;
	glGenTextures(1, &textureId);
	return textureId;
}

int32_t GL3Renderer::createDepthBufferTexture(int32_t width, int32_t height)
{
	uint32_t depthTextureGlId;
	glGenTextures(1, &depthTextureGlId);
	glBindTexture(GL_TEXTURE_2D, depthTextureGlId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, ID_NONE);
	return depthTextureGlId;
}

int32_t GL3Renderer::createColorBufferTexture(int32_t width, int32_t height)
{
	uint32_t colorBufferTextureGlId;
	glGenTextures(1, &colorBufferTextureGlId);
	glBindTexture(GL_TEXTURE_2D, colorBufferTextureGlId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, static_cast< Buffer* >(nullptr));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, ID_NONE);
	return colorBufferTextureGlId;
}

void GL3Renderer::uploadTexture(Texture* texture)
{
	glTexImage2D(GL_TEXTURE_2D, 0, texture->getDepth() == 32 ? GL_RGBA : GL_RGB, texture->getTextureWidth(), texture->getTextureHeight(), 0, texture->getDepth() == 32 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, texture->getTextureData()->getBuffer());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
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

void GL3Renderer::bindTexture(int32_t textureId)
{
	glBindTexture(GL_TEXTURE_2D, textureId);
	onBindTexture(textureId);
}

void GL3Renderer::disposeTexture(int32_t textureId)
{
	glDeleteTextures(1, (const uint32_t*)&textureId);
}

int32_t GL3Renderer::createFramebufferObject(int32_t depthBufferTextureGlId, int32_t colorBufferTextureGlId)
{
	uint32_t frameBufferGlId;
	glGenFramebuffers(1, &frameBufferGlId);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferGlId);
	if (depthBufferTextureGlId != ID_NONE) {
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthBufferTextureGlId, 0);
	}
	if (colorBufferTextureGlId != ID_NONE) {
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colorBufferTextureGlId, 0);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		glReadBuffer(GL_COLOR_ATTACHMENT0);
	} else {
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}
	int32_t fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (fboStatus != GL_FRAMEBUFFER_COMPLETE) {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"GL_FRAMEBUFFER_COMPLETE_EXT failed, CANNOT use FBO: "_j)->append(fboStatus)->toString()));
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return frameBufferGlId;
}

void GL3Renderer::bindFrameBuffer(int32_t frameBufferId)
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);
}

void GL3Renderer::disposeFrameBufferObject(int32_t frameBufferId)
{
	glDeleteFramebuffers(1, (uint32_t*)&frameBufferId);
}

int32_tArray* GL3Renderer::createBufferObjects(int32_t buffers)
{
	auto bufferObjectIds = new int32_tArray(buffers);
	glGenBuffers(buffers, (uint32_t*)bufferObjectIds->getPointer());
	return bufferObjectIds;
}

void GL3Renderer::uploadBufferObject(int32_t bufferObjectId, int32_t size, FloatBuffer* data)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glBufferData(GL_ARRAY_BUFFER, size, data->getBuffer(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, ID_NONE);
}

void GL3Renderer::uploadIndicesBufferObject(int32_t bufferObjectId, int32_t size, ShortBuffer* data)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObjectId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data->getBuffer(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID_NONE);
}

void GL3Renderer::uploadBufferObject(int32_t bufferObjectId, int32_t size, ShortBuffer* data)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glBufferData(GL_ARRAY_BUFFER, size, data->getBuffer(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, ID_NONE);
}

void GL3Renderer::bindIndicesBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObjectId);
}

void GL3Renderer::bindTextureCoordinatesBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, 0LL);
}

void GL3Renderer::bindVerticesBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0LL);
}

void GL3Renderer::bindNormalsBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, 0LL);
}

void GL3Renderer::bindColorsBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, false, 0, 0LL);
}

void GL3Renderer::bindSkinningVerticesJointsBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 1, GL_FLOAT, false, 0, 0LL);
}

void GL3Renderer::bindSkinningVerticesVertexJointsIdxBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, false, 0, 0LL);
}

void GL3Renderer::bindSkinningVerticesVertexJointsWeightBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, false, 0, 0LL);
}

void GL3Renderer::bindTangentsBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(7);
	glVertexAttribPointer(7, 3, GL_FLOAT, false, 0, 0LL);
}

void GL3Renderer::bindBitangentsBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glEnableVertexAttribArray(8);
	glVertexAttribPointer(8, 3, GL_FLOAT, false, 0, 0LL);
}

void GL3Renderer::drawIndexedTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset)
{
	#define BUFFER_OFFSET(i) ((void*)(i))
	glDrawElements(GL_TRIANGLES, triangles * 3, GL_UNSIGNED_SHORT, BUFFER_OFFSET(static_cast< int64_t >(trianglesOffset) * 3LL * 2LL));
}

void GL3Renderer::drawTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset)
{
	glDrawArrays(GL_TRIANGLES, trianglesOffset * 3, triangles * 3);
}

void GL3Renderer::drawPointsFromBufferObjects(int32_t points, int32_t pointsOffset)
{
	glDrawArrays(GL_POINTS, pointsOffset, points);
}

void GL3Renderer::unbindBufferObjects()
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
	glBindBuffer(GL_ARRAY_BUFFER, ID_NONE);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID_NONE);
}

void GL3Renderer::disposeBufferObjects(int32_tArray* bufferObjectIds)
{
	glDeleteBuffers(bufferObjectIds->length, (const uint32_t*)bufferObjectIds->getPointer());
}

int32_t GL3Renderer::getTextureUnit()
{
	return activeTextureUnit;
}

void GL3Renderer::setTextureUnit(int32_t textureUnit)
{
	this->activeTextureUnit = textureUnit;
	glActiveTexture(GL_TEXTURE0 + textureUnit);
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
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL::GL_FLOAT, static_cast< Buffer* >(pixelDepthBuffer));
	return pixelDepthBuffer->get();
	*/
	return -1.0f;
}

ByteBuffer* GL3Renderer::readPixels(int32_t x, int32_t y, int32_t width, int32_t height)
{
	/*
	auto pixelBuffer = ByteBuffer::allocateDirect(width * height * Byte::SIZE* 4);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, static_cast< Buffer* >(pixelBuffer));
	return pixelBuffer;
	*/
}

void GL3Renderer::initGuiMode()
{
	setTextureUnit(0);
	glBindTexture(GL_TEXTURE_2D, ID_NONE);
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

void GL3Renderer::checkGLError()
{
	auto error = glGetError();
	if (error != GL_NO_ERROR) {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"OpenGL Error: ("_j)->append((int32_t)error)
			->append(u") @:"_j)->toString()));
			/*
		auto stackTrace = Thread::currentThread()->getStackTrace();
		for (auto i = 1; i < stackTrace->length; i++) {
			_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"\t"_j)->append(static_cast< Object* >((*stackTrace)[i]))->toString()));
		}
		*/
	}
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

