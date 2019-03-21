#include <tdme/engine/subsystems/renderer/VKRenderer.h>

#include <ext/vk/util_init.hpp>

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
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return "gl3";
}

void VKRenderer::initialize()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
    init_global_layer_properties(context);
    init_instance_extension_names(context);
    init_device_extension_names(context);
    init_instance(context, "TDME2 Vulkan Renderer");
    init_enumerate_device(context);
    init_window_size(context, 500, 500);
    init_connection(context);
    init_window(context);
    init_swapchain_extension(context);
    init_device(context);
    init_command_pool(context);
    init_command_buffer(context);
    execute_begin_command_buffer(context);
    init_device_queue(context);
    init_swap_chain(context);
    init_depth_buffer(context);
    init_texture(context);
    init_uniform_buffer(context);
    init_descriptor_and_pipeline_layouts(context, true);
    init_renderpass(context, true);
    // init_shaders(context, vertShaderText, fragShaderText);
    // init_framebuffers(context, depthPresent);
    // init_vertex_buffer(context, g_vb_texture_Data, sizeof(g_vb_texture_Data), sizeof(g_vb_texture_Data[0]), true);
    // init_descriptor_pool(context, true);
    // init_descriptor_set(context, true);
    // init_pipeline_cache(context);
    init_pipeline(context, true);
}

void VKRenderer::initializeFrame()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	GLRenderer::initializeFrame();
}

bool VKRenderer::isBufferObjectsAvailable()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return true;
}

bool VKRenderer::isDepthTextureAvailable()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return true;
}

bool VKRenderer::isUsingProgramAttributeLocation()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return false;
}

bool VKRenderer::isSpecularMappingAvailable()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return true;
}

bool VKRenderer::isNormalMappingAvailable()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return true;
}

bool VKRenderer::isDisplacementMappingAvailable()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return false;
}

bool VKRenderer::isInstancedRenderingAvailable() {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return true;
}

bool VKRenderer::isUsingShortIndices() {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return false;
}

bool VKRenderer::isGeometryShaderAvailable() {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return false;
}

int32_t VKRenderer::getTextureUnits()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return activeTextureUnit;
}

int32_t VKRenderer::loadShader(int32_t type, const string& pathName, const string& fileName, const string& definitions, const string& functions)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return -1;
}

void VKRenderer::useProgram(int32_t programId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

int32_t VKRenderer::createProgram()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return -1;
}

void VKRenderer::attachShaderToProgram(int32_t programId, int32_t shaderId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

bool VKRenderer::linkProgram(int32_t programId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return false;
}

int32_t VKRenderer::getProgramUniformLocation(int32_t programId, const string& name)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return -1;
}

void VKRenderer::setProgramUniformInteger(int32_t uniformId, int32_t value)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setProgramUniformFloat(int32_t uniformId, float value)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setProgramUniformFloatMatrix3x3(int32_t uniformId, const array<float, 9>& data)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setProgramUniformFloatMatrix4x4(int32_t uniformId, const array<float, 16>& data)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setProgramUniformFloatMatrices4x4(int32_t uniformId, int32_t count, FloatBuffer* data)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setProgramUniformFloatVec4(int32_t uniformId, const array<float, 4>& data)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setProgramUniformFloatVec3(int32_t uniformId, const array<float, 3>& data)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setProgramAttributeLocation(int32_t programId, int32_t location, const string& name)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setViewPort(int32_t x, int32_t y, int32_t width, int32_t height)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::updateViewPort()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setClearColor(float red, float green, float blue, float alpha)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::enableCulling()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::disableCulling()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::enableBlending()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::disableBlending()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::enableDepthBufferWriting()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::disableDepthBufferWriting()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::disableDepthBufferTest()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::enableDepthBufferTest()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setDepthFunction(int32_t depthFunction)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setColorMask(bool red, bool green, bool blue, bool alpha)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::clear(int32_t mask)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setCullFace(int32_t cullFace)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::setFrontFace(int32_t frontFace)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

int32_t VKRenderer::createTexture()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return -1;
}

int32_t VKRenderer::createDepthBufferTexture(int32_t width, int32_t height)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return -1;
}

int32_t VKRenderer::createColorBufferTexture(int32_t width, int32_t height)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return -1;
}

void VKRenderer::uploadTexture(Texture* texture)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::resizeDepthBufferTexture(int32_t textureId, int32_t width, int32_t height)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::resizeColorBufferTexture(int32_t textureId, int32_t width, int32_t height)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindTexture(int32_t textureId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::disposeTexture(int32_t textureId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

int32_t VKRenderer::createFramebufferObject(int32_t depthBufferTextureGlId, int32_t colorBufferTextureGlId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return -1;
}

void VKRenderer::bindFrameBuffer(int32_t frameBufferId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::disposeFrameBufferObject(int32_t frameBufferId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

vector<int32_t> VKRenderer::createBufferObjects(int32_t buffers)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return vector<int32_t>();
}

void VKRenderer::uploadBufferObject(int32_t bufferObjectId, int32_t size, FloatBuffer* data)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::uploadIndicesBufferObject(int32_t bufferObjectId, int32_t size, ShortBuffer* data)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::uploadIndicesBufferObject(int32_t bufferObjectId, int32_t size, IntBuffer* data)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindIndicesBufferObject(int32_t bufferObjectId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindTextureCoordinatesBufferObject(int32_t bufferObjectId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindVerticesBufferObject(int32_t bufferObjectId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindNormalsBufferObject(int32_t bufferObjectId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindColorsBufferObject(int32_t bufferObjectId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindTangentsBufferObject(int32_t bufferObjectId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindBitangentsBufferObject(int32_t bufferObjectId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindModelMatricesBufferObject(int32_t bufferObjectId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindEffectColorMulsBufferObject(int32_t bufferObjectId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindEffectColorAddsBufferObject(int32_t bufferObjectId)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::drawInstancedIndexedTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset, int32_t instances)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::drawIndexedTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::drawInstancedTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset, int32_t instances)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::drawTrianglesFromBufferObjects(int32_t triangles, int32_t trianglesOffset)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::drawPointsFromBufferObjects(int32_t points, int32_t pointsOffset)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::unbindBufferObjects()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::disposeBufferObjects(vector<int32_t>& bufferObjectIds)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

int32_t VKRenderer::getTextureUnit()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return activeTextureUnit;
}

void VKRenderer::setTextureUnit(int32_t textureUnit)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	this->activeTextureUnit = textureUnit;
}

float VKRenderer::readPixelDepth(int32_t x, int32_t y)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return 0.0f;
}

ByteBuffer* VKRenderer::readPixels(int32_t x, int32_t y, int32_t width, int32_t height)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
	return nullptr;
}

void VKRenderer::initGuiMode()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::doneGuiMode()
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::checkGLError(int line)
{
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::dispatchCompute(int32_t numGroupsX, int32_t numGroupsY, int32_t numGroupsZ) {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::memoryBarrier() {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::uploadSkinningBufferObject(int32_t bufferObjectId, int32_t size, FloatBuffer* data) {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::uploadSkinningBufferObject(int32_t bufferObjectId, int32_t size, IntBuffer* data) {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindSkinningVerticesBufferObject(int32_t bufferObjectId) {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindSkinningNormalsBufferObject(int32_t bufferObjectId) {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindSkinningVertexJointsBufferObject(int32_t bufferObjectId) {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindSkinningVertexJointIdxsBufferObject(int32_t bufferObjectId) {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindSkinningVertexJointWeightsBufferObject(int32_t bufferObjectId) {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindSkinningVerticesResultBufferObject(int32_t bufferObjectId) {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindSkinningNormalsResultBufferObject(int32_t bufferObjectId) {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}

void VKRenderer::bindSkinningMatricesBufferObject(int32_t bufferObjectId) {
	Console::println("VKRenderer::" + string(__FUNCTION__) + "()");
}
