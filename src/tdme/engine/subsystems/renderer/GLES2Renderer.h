#pragma once

#include <array>
#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::array;
using std::map;
using std::string;
using std::vector;

using tdme::engine::Texture;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::FrameBuffer;
using tdme::math::Matrix4x4;
using tdme::utilities::ByteBuffer;
using tdme::utilities::FloatBuffer;
using tdme::utilities::ShortBuffer;

/**
 * OpenGL ES2 renderer
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::renderer::GLES2Renderer: public Renderer
{
private:
	map<uint32_t, int32_t> vbosUsage;
	int activeTextureUnit;

public:
	/**
	 * Public constructor
	 */
	GLES2Renderer();

	// overridden methods
	const string getVendor() override;
	const string getRenderer() override;
	const string getShaderVersion() override;
	bool isSupportingMultithreadedRendering() override;
	void initialize() override;
	void initializeFrame() override;
	void finishFrame() override;
	bool isBufferObjectsAvailable() override;
	bool isDepthTextureAvailable() override;
	bool isUsingProgramAttributeLocation() override;
	bool isSupportingIntegerProgramAttributes() override;
	bool isSpecularMappingAvailable() override;
	bool isNormalMappingAvailable() override;
	bool isInstancedRenderingAvailable() override;
	bool isPBRAvailable() override;
	bool isComputeShaderAvailable() override;
	bool isGLCLAvailable() override;
	bool isUsingShortIndices() override;
	bool isDeferredShadingAvailable() override;
	int32_t getTextureUnits() override;
	int32_t loadShader(int32_t type, const string& pathName, const string& fileName, const string& definitions = string(), const string& functions = string()) override;
	void useProgram(int contextIdx, int32_t programId) override;
	int32_t createProgram(int type) override;
	void attachShaderToProgram(int32_t programId, int32_t shaderId) override;
	bool linkProgram(int32_t programId) override;
	int32_t getProgramUniformLocation(int32_t programId, const string& name) override;
	void setProgramUniformInteger(int contextIdx, int32_t uniformId, int32_t value) override;
	void setProgramUniformFloat(int contextIdx, int32_t uniformId, float value) override;
	void setProgramUniformFloatMatrix3x3(int contextIdx, int32_t uniformId, const array<float, 9>& data) override;
	void setProgramUniformFloatMatrix4x4(int contextIdx, int32_t uniformId, const array<float, 16>& data) override;
	void setProgramUniformFloatMatrices4x4(int contextIdx, int32_t uniformId, int32_t count, FloatBuffer* data) override;
	void setProgramUniformFloatVec4(int contextIdx, int32_t uniformId, const array<float, 4>& data) override;
	void setProgramUniformFloatVec3(int contextIdx, int32_t uniformId, const array<float, 3>& data) override;
	void setProgramUniformFloatVec2(int contextIdx, int32_t uniformId, const array<float, 2>& data) override;
	void setProgramAttributeLocation(int32_t programId, int32_t location, const string& name) override;
	void setViewPort(int32_t width, int32_t height) override;
	void updateViewPort() override;
	void setClearColor(float red, float green, float blue, float alpha) override;
	void enableCulling(int contextIdx) override;
	void disableCulling(int contextIdx) override;
	void setFrontFace(int contextIdx, int32_t frontFace) override;
	void setCullFace(int32_t cullFace) override;
	void enableBlending() override;
	void enableAdditionBlending() override;
	void disableBlending() override;
	void enableDepthBufferWriting() override;
	void disableDepthBufferWriting() override;
	void disableDepthBufferTest() override;
	void enableDepthBufferTest() override;
	void setDepthFunction(int32_t depthFunction) override;
	void setColorMask(bool red, bool green, bool blue, bool alpha) override;
	void clear(int32_t mask) override;
	int32_t createTexture() override;
	int32_t createDepthBufferTexture(int32_t width, int32_t height, int32_t cubeMapTextureId, int32_t cubeMapTextureIndex) override;
	int32_t createColorBufferTexture(int32_t width, int32_t height, int32_t cubeMapTextureId, int32_t cubeMapTextureIndex) override;
	int32_t createGBufferGeometryTexture(int32_t width, int32_t height) override;
	int32_t createGBufferColorTexture(int32_t width, int32_t height) override;
	void uploadTexture(int contextIdx, Texture* texture) override;
	void uploadCubeMapTexture(int contextIdx, Texture* textureLeft, Texture* textureRight, Texture* textureTop, Texture* textureBottom, Texture* textureFront, Texture* textureBack) override;
	int32_t createCubeMapTexture(int contextIdx, int32_t width, int32_t height) override;
	void resizeDepthBufferTexture(int32_t textureId, int32_t width, int32_t height) override;
	void resizeColorBufferTexture(int32_t textureId, int32_t width, int32_t height) override;
	void resizeGBufferGeometryTexture(int32_t textureId, int32_t width, int32_t height) override;
	void resizeGBufferColorTexture(int32_t textureId, int32_t width, int32_t height) override;
	void bindTexture(int contextIdx, int32_t textureId) override;
	void bindCubeMapTexture(int contextIdx, int32_t textureId) override;
	void disposeTexture(int32_t textureId) override;
	int32_t createFramebufferObject(int32_t depthBufferTextureId, int32_t colorBufferTextureId, int32_t cubeMapTextureId = 0, int32_t cubeMapTextureIndex = 0) override;
	int32_t createGeometryBufferObject(
		int32_t depthBufferTextureId,
		int32_t geometryBufferTextureId1,
		int32_t geometryBufferTextureId2,
		int32_t geometryBufferTextureId3,
		int32_t colorBufferTextureId1,
		int32_t colorBufferTextureId2,
		int32_t colorBufferTextureId3,
		int32_t colorBufferTextureId4,
		int32_t colorBufferTextureId5
	) override;
	void bindFrameBuffer(int32_t frameBufferId) override;
	void disposeFrameBufferObject(int32_t frameBufferId) override;
	vector<int32_t> createBufferObjects(int32_t buffers, bool useGPUMemory, bool shared) override;
	void uploadBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, FloatBuffer* data) override;
	void uploadBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, ShortBuffer* data) override;
	void uploadBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, IntBuffer* data) override;
	void uploadIndicesBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, ShortBuffer* data) override;
	void uploadIndicesBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, IntBuffer* data) override;
	void bindIndicesBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindSolidColorsBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindTextureCoordinatesBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindVerticesBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindVertices2BufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindNormalsBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindColorsBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindTangentsBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindBitangentsBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindModelMatricesBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindEffectColorMulsBufferObject(int contextIdx, int32_t bufferObjectId, int32_t divisor) override;
	void bindEffectColorAddsBufferObject(int contextIdx, int32_t bufferObjectId, int32_t divisor) override;
	void bindOriginsBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindTextureSpriteIndicesBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindPointSizesBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindSpriteSheetDimensionBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void drawInstancedIndexedTrianglesFromBufferObjects(int contextIdx, int32_t triangles, int32_t trianglesOffset, int32_t instances) override;
	void drawIndexedTrianglesFromBufferObjects(int contextIdx, int32_t triangles, int32_t trianglesOffset) override;
	void drawInstancedTrianglesFromBufferObjects(int contextIdx, int32_t triangles, int32_t trianglesOffset, int32_t instances) override;
	void drawTrianglesFromBufferObjects(int contextIdx, int32_t triangles, int32_t trianglesOffset) override;
	void drawPointsFromBufferObjects(int contextIdx, int32_t points, int32_t pointsOffset) override;
	void setLineWidth(float lineWidth) override;
	void drawLinesFromBufferObjects(int contextIdx, int32_t points, int32_t pointsOffset) override;
	void unbindBufferObjects(int contextIdx) override;
	void disposeBufferObjects(vector<int32_t>& bufferObjectIds) override;
	int32_t getTextureUnit(int contextIdx) override;
	void setTextureUnit(int contextIdx, int32_t textureUnit) override;
	float readPixelDepth(int32_t x, int32_t y) override;
	ByteBuffer* readPixels(int32_t x, int32_t y, int32_t width, int32_t height) override;
	void initGuiMode() override;
	void doneGuiMode() override;

	// overridden methods for skinning on GPU via compute shader
	void dispatchCompute(int contextIdx, int32_t numGroupsX, int32_t numGroupsY, int32_t numGroupsZ) override;
	void memoryBarrier() override;
	void uploadSkinningBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, FloatBuffer* data) override;
	void uploadSkinningBufferObject(int contextIdx, int32_t bufferObjectId, int32_t size, IntBuffer* data) override;
	void bindSkinningVerticesBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindSkinningNormalsBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindSkinningVertexJointsBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindSkinningVertexJointIdxsBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindSkinningVertexJointWeightsBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindSkinningVerticesResultBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindSkinningNormalsResultBufferObject(int contextIdx, int32_t bufferObjectId) override;
	void bindSkinningMatricesBufferObject(int contextIdx, int32_t bufferObjectId) override;

	//
	void setVSync(bool vSync) override;

	//
	const Renderer_Statistics getStatistics() override;
private:
	/**
	 * Checks if GL error did occour
	 */
	void checkGLError();

};
