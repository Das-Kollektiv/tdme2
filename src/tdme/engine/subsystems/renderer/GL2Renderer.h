#pragma once

#include <array>
#include <vector>
#include <string>

#include <tdme/tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>

using std::array;
using std::vector;
using std::string;

using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::utils::ByteBuffer;
using tdme::utils::FloatBuffer;
using tdme::utils::ShortBuffer;
using tdme::engine::fileio::textures::Texture;
using tdme::math::Matrix4x4;

/** 
 * OpenGL 2 renderer
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::renderer::GL2Renderer
	: public GLRenderer
{
private:
	bool bufferObjectsAvailable {  };
	int32_t viewPortX {  };
	int32_t viewPortY {  };
	int32_t viewPortWidth {  };
	int32_t viewPortHeight {  };
	int32_t activeTextureUnit {  };
protected:

	/**
	 * final public constructor
	 */
	void ctor();

public:
	const string getGLVersion() override;

private:

	/** 
	 * Checks if VBO is available
	 * @return vbo availability
	 */
	bool checkBufferObjectsAvailable();

public:
	bool isDepthTextureAvailable() override;
	void initialize() override;
	void initializeFrame() override;
	bool isBufferObjectsAvailable() override;
	bool isUsingProgramAttributeLocation() override;
	bool isSpecularMappingAvailable() override;
	bool isNormalMappingAvailable() override;
	bool isDisplacementMappingAvailable() override;
	bool isInstancedRenderingAvailable() override;
	bool isUsingShortIndices() override;
	bool isGeometryShaderAvailable() override;
	int32_t getTextureUnits() override;
	int32_t loadShader(int32_t type, const string& pathName, const string& fileName, const string& definitions = string(), const string& functions = string()) override;
	void useProgram(int32_t programId) override;
	int32_t createProgram() override;
	void attachShaderToProgram(int32_t programId, int32_t shaderId) override;
	bool linkProgram(int32_t programId) override;
	int32_t getProgramUniformLocation(int32_t programId, const string& name) override;
	void setProgramUniformInteger(int32_t uniformId, int32_t value) override;
	void setProgramUniformFloat(int32_t uniformId, float value) override;
	void setProgramUniformFloatMatrices4x4(int32_t uniformId, int32_t count, FloatBuffer* data) override;
	void setProgramUniformFloatMatrix3x3(int32_t uniformId, const array<float, 9>& data) override;
	void setProgramUniformFloatMatrix4x4(int32_t uniformId, const array<float, 16>& data) override;
	void setProgramUniformFloatVec4(int32_t uniformId, const array<float, 4>& data) override;
	void setProgramUniformFloatVec3(int32_t uniformId, const array<float, 3>& data) override;
	void setProgramAttributeLocation(int32_t programId, int32_t location, const string& name) override;
	void setViewPort(int32_t x, int32_t y, int32_t width, int32_t height) override;
	void updateViewPort() override;
	void setClearColor(float red, float green, float blue, float alpha) override;
	void enableCulling() override;
	void disableCulling() override;
	void enableBlending() override;
	void disableBlending() override;
	void enableDepthBufferWriting() override;
	void disableDepthBufferWriting() override;
	void disableDepthBufferTest() override;
	void enableDepthBufferTest() override;
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
	vector<int32_t> createBufferObjects(int32_t buffers) override;
	void uploadBufferObject(int32_t bufferObjectId, int32_t size, FloatBuffer* data) override;
	void uploadIndicesBufferObject(int32_t bufferObjectId, int32_t size, ShortBuffer* data) override;
	void uploadIndicesBufferObject(int32_t bufferObjectId, int32_t size, IntBuffer* data) override;
	void bindIndicesBufferObject(int32_t bufferObjectId) override;
	void bindTextureCoordinatesBufferObject(int32_t bufferObjectId) override;
	void bindVerticesBufferObject(int32_t bufferObjectId) override;
	void bindNormalsBufferObject(int32_t bufferObjectId) override;
	void bindColorsBufferObject(int32_t bufferObjectId) override;
	void bindTangentsBufferObject(int32_t bufferObjectId) override;
	void bindBitangentsBufferObject(int32_t bufferObjectId) override;
	void bindModelMatricesBufferObject(int32_t bufferObjectId) override;
	void bindEffectColorMulsBufferObject(int32_t bufferObjectId) override;
	void bindEffectColorAddsBufferObject(int32_t bufferObjectId) override;
	void drawInstancedIndexedTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset, int32_t instances) override;
	void drawIndexedTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset) override;
	void drawInstancedTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset, int32_t instances) override;
	void drawTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset) override;
	void drawPointsFromBufferObjects(int32_t points, int32_t pointsOffset) override;
	void unbindBufferObjects() override;
	void disposeBufferObjects(vector<int32_t>& bufferObjectIds) override;
	int32_t getTextureUnit() override;
	void setTextureUnit(int32_t textureUnit) override;
	float readPixelDepth(int32_t x, int32_t y) override;
	ByteBuffer* readPixels(int32_t x, int32_t y, int32_t width, int32_t height) override;
	void initGuiMode() override;
	void doneGuiMode() override;

	// overriden methods for skinning on GPU via compute shader
	void dispatchCompute(int32_t numGroupsX, int32_t numGroupsY, int32_t numGroupsZ) override;
	void memoryBarrier() override;
	void uploadSkinningBufferObject(int32_t bufferObjectId, int32_t size, FloatBuffer* data) override;
	void uploadSkinningBufferObject(int32_t bufferObjectId, int32_t size, IntBuffer* data) override;
	void bindSkinningVerticesBufferObject(int32_t bufferObjectId) override;
	void bindSkinningNormalsBufferObject(int32_t bufferObjectId) override;
	void bindSkinningVertexJointsBufferObject(int32_t bufferObjectId) override;
	void bindSkinningVertexJointIdxsBufferObject(int32_t bufferObjectId) override;
	void bindSkinningVertexJointWeightsBufferObject(int32_t bufferObjectId) override;
	void bindSkinningVerticesResultBufferObject(int32_t bufferObjectId) override;
	void bindSkinningNormalsResultBufferObject(int32_t bufferObjectId) override;
	void bindSkinningMatricesBufferObject(int32_t bufferObjectId) override;

	/**
	 * Public constructor
	 */
	GL2Renderer();
};
