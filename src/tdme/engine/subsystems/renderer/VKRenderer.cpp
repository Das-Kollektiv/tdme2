#include <tdme/engine/subsystems/renderer/VKRenderer.h>

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

using tdme::engine::subsystems::renderer::VKRenderer;
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

VKRenderer::VKRenderer()
{
	// setup GL3 consts
	ID_NONE = 0;
	CLEAR_DEPTH_BUFFER_BIT = -1;
	CLEAR_COLOR_BUFFER_BIT = -1;
	CULLFACE_FRONT = -1;
	CULLFACE_BACK = -1;
	FRONTFACE_CW = -1;
	FRONTFACE_CCW = -1;
	SHADER_FRAGMENT_SHADER = -1;
	SHADER_VERTEX_SHADER = -1;
	SHADER_COMPUTE_SHADER = -1;
	SHADER_GEOMETRY_SHADER = -1;
	DEPTHFUNCTION_ALWAYS = -1;;
	DEPTHFUNCTION_EQUAL = -1;;
	DEPTHFUNCTION_LESSEQUAL = -1;;
	DEPTHFUNCTION_GREATEREQUAL = -1;;
}

const string VKRenderer::getGLVersion()
{
	return "vk";
}

void VKRenderer::initialize()
{
}

void VKRenderer::initializeFrame()
{
	GLRenderer::initializeFrame();
}

bool VKRenderer::isBufferObjectsAvailable()
{
	return true;
}

bool VKRenderer::isDepthTextureAvailable()
{
	return true;
}

bool VKRenderer::isUsingProgramAttributeLocation()
{
	return false;
}

bool VKRenderer::isSpecularMappingAvailable()
{
	return true;
}

bool VKRenderer::isNormalMappingAvailable()
{
	return true;
}

bool VKRenderer::isDisplacementMappingAvailable()
{
	return false;
}

bool VKRenderer::isInstancedRenderingAvailable() {
	return true;
}

bool VKRenderer::isUsingShortIndices() {
	return false;
}

bool VKRenderer::isGeometryShaderAvailable() {
	return false;
}

int32_t VKRenderer::getTextureUnits()
{
	return activeTextureUnit;
}

int32_t VKRenderer::loadShader(int32_t type, const string& pathName, const string& fileName, const string& definitions, const string& functions)
{
	return -1;
}

void VKRenderer::useProgram(int32_t programId)
{
}

int32_t VKRenderer::createProgram()
{
	return -1;
}

void VKRenderer::attachShaderToProgram(int32_t programId, int32_t shaderId)
{
}

bool VKRenderer::linkProgram(int32_t programId)
{
	return false;
}

int32_t VKRenderer::getProgramUniformLocation(int32_t programId, const string& name)
{
	return -1;
}

void VKRenderer::setProgramUniformInteger(int32_t uniformId, int32_t value)
{
}

void VKRenderer::setProgramUniformFloat(int32_t uniformId, float value)
{
}

void VKRenderer::setProgramUniformFloatMatrix3x3(int32_t uniformId, const array<float, 9>& data)
{
}

void VKRenderer::setProgramUniformFloatMatrix4x4(int32_t uniformId, const array<float, 16>& data)
{
}

void VKRenderer::setProgramUniformFloatMatrices4x4(int32_t uniformId, int32_t count, FloatBuffer* data)
{
}

void VKRenderer::setProgramUniformFloatVec4(int32_t uniformId, const array<float, 4>& data)
{
}

void VKRenderer::setProgramUniformFloatVec3(int32_t uniformId, const array<float, 3>& data)
{
}

void VKRenderer::setProgramAttributeLocation(int32_t programId, int32_t location, const string& name)
{
}

void VKRenderer::setViewPort(int32_t x, int32_t y, int32_t width, int32_t height)
{
}

void VKRenderer::updateViewPort()
{
}

void VKRenderer::setClearColor(float red, float green, float blue, float alpha)
{
}

void VKRenderer::enableCulling()
{
}

void VKRenderer::disableCulling()
{
}

void VKRenderer::enableBlending()
{
}

void VKRenderer::disableBlending()
{
}

void VKRenderer::enableDepthBufferWriting()
{
}

void VKRenderer::disableDepthBufferWriting()
{
}

void VKRenderer::disableDepthBufferTest()
{
}

void VKRenderer::enableDepthBufferTest()
{
}

void VKRenderer::setDepthFunction(int32_t depthFunction)
{
}

void VKRenderer::setColorMask(bool red, bool green, bool blue, bool alpha)
{
}

void VKRenderer::clear(int32_t mask)
{
}

void VKRenderer::setCullFace(int32_t cullFace)
{
}

void VKRenderer::setFrontFace(int32_t frontFace)
{
}

int32_t VKRenderer::createTexture()
{
	return -1;
}

int32_t VKRenderer::createDepthBufferTexture(int32_t width, int32_t height)
{
	return -1;
}

int32_t VKRenderer::createColorBufferTexture(int32_t width, int32_t height)
{
	return -1;
}

void VKRenderer::uploadTexture(Texture* texture)
{
}

void VKRenderer::resizeDepthBufferTexture(int32_t textureId, int32_t width, int32_t height)
{
}

void VKRenderer::resizeColorBufferTexture(int32_t textureId, int32_t width, int32_t height)
{
}

void VKRenderer::bindTexture(int32_t textureId)
{
}

void VKRenderer::disposeTexture(int32_t textureId)
{
}

int32_t VKRenderer::createFramebufferObject(int32_t depthBufferTextureGlId, int32_t colorBufferTextureGlId)
{
	return -1;
}

void VKRenderer::bindFrameBuffer(int32_t frameBufferId)
{
}

void VKRenderer::disposeFrameBufferObject(int32_t frameBufferId)
{
}

vector<int32_t> VKRenderer::createBufferObjects(int32_t buffers)
{
	return vector<int32_t>();
}

void VKRenderer::uploadBufferObject(int32_t bufferObjectId, int32_t size, FloatBuffer* data)
{
}

void VKRenderer::uploadIndicesBufferObject(int32_t bufferObjectId, int32_t size, ShortBuffer* data)
{
}

void VKRenderer::uploadIndicesBufferObject(int32_t bufferObjectId, int32_t size, IntBuffer* data)
{
}

void VKRenderer::bindIndicesBufferObject(int32_t bufferObjectId)
{
}

void VKRenderer::bindTextureCoordinatesBufferObject(int32_t bufferObjectId)
{
}

void VKRenderer::bindVerticesBufferObject(int32_t bufferObjectId)
{
}

void VKRenderer::bindNormalsBufferObject(int32_t bufferObjectId)
{
}

void VKRenderer::bindColorsBufferObject(int32_t bufferObjectId)
{
}

void VKRenderer::bindTangentsBufferObject(int32_t bufferObjectId)
{
}

void VKRenderer::bindBitangentsBufferObject(int32_t bufferObjectId)
{
}

void VKRenderer::bindModelMatricesBufferObject(int32_t bufferObjectId) {
}

void VKRenderer::bindEffectColorMulsBufferObject(int32_t bufferObjectId) {
}

void VKRenderer::bindEffectColorAddsBufferObject(int32_t bufferObjectId) {
}

void VKRenderer::drawInstancedIndexedTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset, int32_t instances)
{
}

void VKRenderer::drawIndexedTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset)
{
}

void VKRenderer::drawInstancedTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset, int32_t instances) {
}

void VKRenderer::drawTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset)
{
}

void VKRenderer::drawPointsFromBufferObjects(int32_t points, int32_t pointsOffset)
{
}

void VKRenderer::unbindBufferObjects()
{
}

void VKRenderer::disposeBufferObjects(vector<int32_t>& bufferObjectIds)
{
}

int32_t VKRenderer::getTextureUnit()
{
	return activeTextureUnit;
}

void VKRenderer::setTextureUnit(int32_t textureUnit)
{
	this->activeTextureUnit = textureUnit;
}

float VKRenderer::readPixelDepth(int32_t x, int32_t y)
{
	return 0.0f;
}

ByteBuffer* VKRenderer::readPixels(int32_t x, int32_t y, int32_t width, int32_t height)
{
	return nullptr;
}

void VKRenderer::initGuiMode()
{
}

void VKRenderer::doneGuiMode()
{
}

void VKRenderer::checkGLError(int line)
{
}

void VKRenderer::dispatchCompute(int32_t numGroupsX, int32_t numGroupsY, int32_t numGroupsZ) {
}

void VKRenderer::memoryBarrier() {
}

void VKRenderer::uploadSkinningBufferObject(int32_t bufferObjectId, int32_t size, FloatBuffer* data) {
}

void VKRenderer::uploadSkinningBufferObject(int32_t bufferObjectId, int32_t size, IntBuffer* data) {
}

void VKRenderer::bindSkinningVerticesBufferObject(int32_t bufferObjectId) {
}

void VKRenderer::bindSkinningNormalsBufferObject(int32_t bufferObjectId) {
}

void VKRenderer::bindSkinningVertexJointsBufferObject(int32_t bufferObjectId) {
}

void VKRenderer::bindSkinningVertexJointIdxsBufferObject(int32_t bufferObjectId) {
}

void VKRenderer::bindSkinningVertexJointWeightsBufferObject(int32_t bufferObjectId) {
}

void VKRenderer::bindSkinningVerticesResultBufferObject(int32_t bufferObjectId) {
}

void VKRenderer::bindSkinningNormalsResultBufferObject(int32_t bufferObjectId) {
}

void VKRenderer::bindSkinningMatricesBufferObject(int32_t bufferObjectId) {
}
