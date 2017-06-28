// Generated from /tdme/src/tdme/engine/subsystems/renderer/GLES2Renderer.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>

using tdme::engine::subsystems::renderer::GLRenderer;
using java::lang::String;
using java::nio::ByteBuffer;
using java::nio::FloatBuffer;
using java::nio::ShortBuffer;
using tdme::engine::fileio::textures::Texture;
using tdme::math::Matrix4x4;


struct default_init_tag;

/** 
 * OpenGL ES2 renderer
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::renderer::GLES2Renderer
	: public GLRenderer
{

public:
	typedef GLRenderer super;

protected:

	/** 
	 * final public constructor
	 */
	void ctor();

public:
	String* getGLVersion() override;
	void initialize() override;
	void initializeFrame() override;
	bool isBufferObjectsAvailable() override;
	bool isDepthTextureAvailable() override;
	bool isUsingProgramAttributeLocation() override;
	bool isSpecularMappingAvailable() override;
	bool isNormalMappingAvailable() override;

	/** 
	 * @return if displacement mapping is supported
	 */
	bool isDisplacementMappingAvailable() override;
	int32_t getTextureUnits() override;
	int32_t loadShader(int32_t type, String* pathName, String* fileName) override;
	void useProgram(int32_t programId) override;
	int32_t createProgram() override;
	void attachShaderToProgram(int32_t programId, int32_t shaderId) override;
	bool linkProgram(int32_t programId) override;
	int32_t getProgramUniformLocation(int32_t programId, String* name) override;
	void setProgramUniformInteger(int32_t uniformId, int32_t value) override;
	void setProgramUniformFloat(int32_t uniformId, float value) override;
	void setProgramUniformFloatMatrix3x3(int32_t uniformId, floatArray* data) override;
	void setProgramUniformFloatMatrix4x4(int32_t uniformId, floatArray* data) override;
	void setProgramUniformFloatMatrices4x4(int32_t uniformId, int32_t count, FloatBuffer* data) override;
	void setProgramUniformFloatVec4(int32_t uniformId, floatArray* data) override;
	void setProgramUniformFloatVec3(int32_t uniformId, floatArray* data) override;
	void setProgramAttributeLocation(int32_t programId, int32_t location, String* name) override;
	void setViewPort(int32_t x, int32_t y, int32_t width, int32_t height) override;
	void updateViewPort() override;
	Matrix4x4* getTextureMatrix() override;
	void setClearColor(float red, float green, float blue, float alpha) override;
	void enableCulling() override;
	void disableCulling() override;
	void enableBlending() override;
	void disableBlending() override;
	void enableDepthBuffer() override;
	void disableDepthBuffer() override;
	void setDepthFunction(int32_t depthFunction) override;
	void setColorMask(bool red, bool green, bool blue, bool alpha) override;
	void clear(int32_t mask) override;
	void setCullFace(int32_t cullFace) override;
	void setFrontFace(int32_t frontFace) override;
	int32_t createTexture() override;
	int32_t createDepthBufferTexture(int32_t width, int32_t height) override;
	int32_t createColorBufferTexture(int32_t width, int32_t height) override;
	void uploadTexture(Texture* texture) override;
	void resizeDepthBufferTexture(int32_t textureId, int32_t width, int32_t height) override;
	void resizeColorBufferTexture(int32_t textureId, int32_t width, int32_t height) override;
	void bindTexture(int32_t textureId) override;
	void disposeTexture(int32_t textureId) override;
	int32_t createFramebufferObject(int32_t depthBufferTextureGlId, int32_t colorBufferTextureGlId) override;
	void bindFrameBuffer(int32_t frameBufferId) override;
	void disposeFrameBufferObject(int32_t frameBufferId) override;
	int32_tArray* createBufferObjects(int32_t buffers) override;
	void uploadBufferObject(int32_t bufferObjectId, int32_t size, FloatBuffer* data) override;
	void uploadIndicesBufferObject(int32_t bufferObjectId, int32_t size, ShortBuffer* data) override;
	void uploadBufferObject(int32_t bufferObjectId, int32_t size, ShortBuffer* data) override;
	void bindIndicesBufferObject(int32_t bufferObjectId) override;
	void bindTextureCoordinatesBufferObject(int32_t bufferObjectId) override;
	void bindVerticesBufferObject(int32_t bufferObjectId) override;
	void bindNormalsBufferObject(int32_t bufferObjectId) override;
	void bindColorsBufferObject(int32_t bufferObjectId) override;
	void bindSkinningVerticesJointsBufferObject(int32_t bufferObjectId) override;
	void bindSkinningVerticesVertexJointsIdxBufferObject(int32_t bufferObjectId) override;
	void bindSkinningVerticesVertexJointsWeightBufferObject(int32_t bufferObjectId) override;
	void bindTangentsBufferObject(int32_t bufferObjectId) override;
	void bindBitangentsBufferObject(int32_t bufferObjectId) override;
	void drawIndexedTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset) override;
	void drawTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset) override;
	void drawPointsFromBufferObjects(int32_t points, int32_t pointsOffset) override;
	void unbindBufferObjects() override;
	void disposeBufferObjects(int32_tArray* bufferObjectIds) override;
	int32_t getTextureUnit() override;
	void setTextureUnit(int32_t textureUnit) override;
	void enableClientState(int32_t clientState) override;
	void disableClientState(int32_t clientState) override;
	float readPixelDepth(int32_t x, int32_t y) override;
	ByteBuffer* readPixels(int32_t x, int32_t y, int32_t width, int32_t height) override;
	void initGuiMode() override;
	void doneGuiMode() override;

private:

	/** 
	 * Checks if GL error did occour 
	 */
	void checkGLError();

	// Generated

public:
	GLES2Renderer();
protected:
	GLES2Renderer(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
