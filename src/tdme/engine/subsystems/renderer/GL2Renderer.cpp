// Generated from /tdme/src/tdme/engine/subsystems/renderer/GL2Renderer.java
#include <tdme/engine/subsystems/renderer/GL2Renderer.h>

#ifdef __APPLE__
        #include <OpenGL/gl.h>
#elif __linux__
        #define GL_GLEXT_PROTOTYPES
        #include <GL/gl.h>
        #include <GL/glext.h>
#endif

#include <string.h>

#include <array>

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
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/_Console.h>
#include <Array.h>
#include <SubArray.h>
#include <ObjectArray.h>

using std::array;

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
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
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
	ID_NONE = 0;
	CLEAR_DEPTH_BUFFER_BIT = GL_DEPTH_BUFFER_BIT;
	CLEAR_COLOR_BUFFER_BIT = GL_COLOR_BUFFER_BIT;
	CULLFACE_FRONT = GL_FRONT;
	CULLFACE_BACK = GL_BACK;
	FRONTFACE_CW = GL_CW;
	FRONTFACE_CCW = GL_CCW;
	CLIENTSTATE_TEXTURECOORD_ARRAY = GL_TEXTURE_COORD_ARRAY;
	CLIENTSTATE_VERTEX_ARRAY = GL_VERTEX_ARRAY;
	CLIENTSTATE_NORMAL_ARRAY = GL_NORMAL_ARRAY;
	CLIENTSTATE_COLOR_ARRAY = GL_COLOR_ARRAY;
	SHADER_FRAGMENT_SHADER = GL_FRAGMENT_SHADER;
	SHADER_VERTEX_SHADER = GL_VERTEX_SHADER;
	DEPTHFUNCTION_LESSEQUAL = GL_LEQUAL;
	DEPTHFUNCTION_EQUAL = GL_EQUAL;
	bufferObjectsAvailable = true;
}

String* GL2Renderer::getGLVersion()
{
	return u"gl2"_j;
}

bool GL2Renderer::checkBufferObjectsAvailable()
{
	auto extensionOK = true; // isExtensionAvailable(u"GL_ARB_vertex_buffer_object"_j);
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
	FRAMEBUFFER_DEFAULT = 0; // getContext()->getDefaultDrawFramebuffer();
	bufferObjectsAvailable = checkBufferObjectsAvailable();
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
	glEnable(GL_PROGRAM_POINT_SIZE_EXT);
	setTextureUnit(0);
}

void GL2Renderer::initializeFrame()
{
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
	return -1;
}

int32_t GL2Renderer::loadShader(int32_t type, String* pathName, String* fileName)
{
	int32_t handle = glCreateShader(type);
	if (handle == 0) return 0;

	auto shaderSource = _FileSystem::getInstance()->getContent(pathName, fileName);
	if (shaderSource == nullptr) return 0;

	auto shaderSourceString = new String(shaderSource);

	string sourceString = StringConverter::toString(shaderSourceString->getCPPWString());
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
		auto infoLogString = new String(StringConverter::toWideString(string(infoLogBuffer, infoLogLengthBuffer)));
		_Console::println(
			static_cast< Object* >(
				::java::lang::StringBuilder().
				 	 append(u"GL3Renderer::loadShader"_j)->
				 	 append(u"["_j)->
				 	 append(handle)->
					 append(u"]"_j)->
					 append(pathName)->
					 append(u"/"_j)->
					 append(fileName)->
					 append(u": failed: "_j)->
					 append(infoLogString)->
					 toString()
			 )
		 );
		glDeleteShader(handle);
		return 0;
	}

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

	int32_t linkStatus;
	glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == 0) {
		int32_t infoLogLength = 0;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
		char infoLog[infoLogLength];
		glGetProgramInfoLog(programId, infoLogLength, &infoLogLength, infoLog);
		auto infoLogString = new String(StringConverter::toWideString(string(infoLog, infoLogLength)));
		_Console::println(static_cast< Object* >(
			::java::lang::StringBuilder().
				 append(u"["_j)->
				 append(programId)->
				 append(u"]: failed: "_j)->
				 append(infoLogString)->
				 toString()
			 )
		);
		return false;
	}
	return true;
}

int32_t GL2Renderer::getProgramUniformLocation(int32_t programId, String* name)
{
	auto uniformLocation = glGetUniformLocation(programId, StringConverter::toString(name->getCPPWString()).c_str());
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

void GL2Renderer::setProgramUniformFloatMatrix3x3(int32_t uniformId, floatArray* data)
{
	glUniformMatrix3fv(uniformId, 1, false, data->getPointer());
}

void GL2Renderer::setProgramUniformFloatMatrices4x4(int32_t uniformId, int32_t count, FloatBuffer* data)
{
	glUniformMatrix4fv(uniformId, count, false, (float*)data->getBuffer());
}

void GL2Renderer::setProgramUniformFloatMatrix4x4(int32_t uniformId, floatArray* data)
{
	glUniformMatrix4fv(uniformId, 1, false, data->getPointer());
}

void GL2Renderer::setProgramUniformFloatVec4(int32_t uniformId, array<float, 4>* data)
{
	glUniform4fv(uniformId, 1, data->data());
}

void GL2Renderer::setProgramUniformFloatVec3(int32_t uniformId, array<float, 3>* data)
{
	glUniform3fv(uniformId, 1, data->data());
}

void GL2Renderer::setProgramAttributeLocation(int32_t programId, int32_t location, String* name)
{
	glBindAttribLocation(programId, location, StringConverter::toString(name->getCPPWString()).c_str());
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
	glViewport(viewPortX, viewPortY, viewPortWidth, viewPortHeight);
}

Matrix4x4* GL2Renderer::getTextureMatrix()
{
	return (*textureMatrix)[activeTextureUnit];
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

void GL2Renderer::enableDepthBuffer()
{
	glDepthMask(true);
}

void GL2Renderer::disableDepthBuffer()
{
	glDepthMask(false);
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

int32_t GL2Renderer::createColorBufferTexture(int32_t width, int32_t height)
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

void GL2Renderer::uploadTexture(Texture* texture)
{
	glTexImage2D(GL_TEXTURE_2D, 0, texture->getDepth() == 32 ? GL_RGBA : GL_RGB, texture->getTextureWidth(), texture->getTextureHeight(), 0, texture->getDepth() == 32 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, texture->getTextureData()->getBuffer());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
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
	uint32_t frameBufferGlId;
	glGenFramebuffers(1, &frameBufferGlId);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferGlId);
	if (depthBufferTextureGlId != ID_NONE) {
		glFramebufferTextureEXT(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthBufferTextureGlId, 0);
	}
	if (colorBufferTextureGlId != ID_NONE) {
		glFramebufferTextureEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colorBufferTextureGlId, 0);
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

void GL2Renderer::bindFrameBuffer(int32_t frameBufferId)
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);
}

void GL2Renderer::disposeFrameBufferObject(int32_t frameBufferId)
{
	glDeleteFramebuffers(1, (uint32_t*)&frameBufferId);
}

int32_tArray* GL2Renderer::createBufferObjects(int32_t buffers)
{
	auto bufferObjectIds = new int32_tArray(buffers);
	glGenBuffers(buffers, (uint32_t*)bufferObjectIds->getPointer());
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
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObjectId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data->getBuffer(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID_NONE);
}

void GL2Renderer::uploadBufferObject(int32_t bufferObjectId, int32_t size, ShortBuffer* data)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glBufferData(GL_ARRAY_BUFFER, size, data->getBuffer(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, ID_NONE);
}

void GL2Renderer::bindIndicesBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObjectId);
}

void GL2Renderer::bindTextureCoordinatesBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glTexCoordPointer(2, GL_FLOAT, 0, 0LL);
}

void GL2Renderer::bindVerticesBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glVertexPointer(3, GL_FLOAT, 0, 0LL);
}

void GL2Renderer::bindNormalsBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glNormalPointer(GL_FLOAT, 0, 0LL);
}

void GL2Renderer::bindColorsBufferObject(int32_t bufferObjectId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferObjectId);
	glColorPointer(4, GL_FLOAT, 0, 0LL);
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
	#define BUFFER_OFFSET(i) ((void*)(i))
	glDrawElements(GL_TRIANGLES, triangles * 3, GL_UNSIGNED_SHORT, BUFFER_OFFSET(static_cast< int64_t >(trianglesOffset) * 3LL * 2LL));
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
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GL2Renderer::disposeBufferObjects(int32_tArray* bufferObjectIds)
{
	glDeleteBuffers(bufferObjectIds->length, (const uint32_t*)bufferObjectIds->getPointer());
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

void GL2Renderer::enableClientState(int32_t clientState)
{
	glEnableClientState(clientState);
}

void GL2Renderer::disableClientState(int32_t clientState)
{
	glDisableClientState(clientState);
}

float GL2Renderer::readPixelDepth(int32_t x, int32_t y)
{
	/*
	pixelDepthBuffer->clear();
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL::GL_FLOAT, static_cast< Buffer* >(pixelDepthBuffer));
	return pixelDepthBuffer->get();
	*/
	return -1.0f;
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

