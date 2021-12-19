#include <tdme/engine/subsystems/renderer/SingleThreadedRenderer.h>

#include <tdme/tdme.h>
#include <tdme/engine/EntityShaderParameters.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utilities/Time.h>

using tdme::engine::subsystems::renderer::SingleThreadedRenderer;

using tdme::engine::EntityShaderParameters;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::utilities::Time;

SingleThreadedRenderer::SingleThreadedRenderer()
{
	// set up lights
	for (auto i = 0; i < lights.size(); i++) {
		lights[i].spotCosCutoff = static_cast<float>(Math::cos(Math::PI / 180.0f * 180.0f));
	}
}

SingleThreadedRenderer::~SingleThreadedRenderer() {
}

int32_t SingleThreadedRenderer::getLighting(int contextIdx) {
	return lighting;
}

void SingleThreadedRenderer::setLighting(int contextIdx, int32_t lighting) {
	this->lighting = lighting;
}

Matrix2D3x3& SingleThreadedRenderer::getTextureMatrix(int contextIdx) {
	return textureMatrix;
}

Renderer::Renderer_Light& SingleThreadedRenderer::getLight(int contextIdx, int32_t lightId) {
	return lights[lightId];
}

array<float, 4>& SingleThreadedRenderer::getEffectColorMul(int contextIdx) {
	return effectColorMul;
}

array<float, 4>& SingleThreadedRenderer::getEffectColorAdd(int contextIdx) {
	return effectColorAdd;
}

Renderer::Renderer_SpecularMaterial& SingleThreadedRenderer::getSpecularMaterial(int contextIdx) {
	return specularMaterial;
}

Renderer::Renderer_PBRMaterial& SingleThreadedRenderer::getPBRMaterial(int contextIdx) {
	return pbrMaterial;
}

const string& SingleThreadedRenderer::getShader(int contextIdx) {
	return shader;
}

void SingleThreadedRenderer::setShader(int contextIdx, const string& id) {
	shader = id;
}

const EntityShaderParameters& SingleThreadedRenderer::getShaderParameters(int contextIdx) {
	return shaderParameters;
}

void SingleThreadedRenderer::setShaderParameters(int contextIdx, const EntityShaderParameters& parameters) {
	shaderParameters = parameters;
}

float SingleThreadedRenderer::getMaskMaxValue(int contextIdx) {
	return maskMaxValue;
}

void SingleThreadedRenderer::setMaskMaxValue(int contextIdx, float maskMaxValue) {
	this->maskMaxValue = maskMaxValue;
}

array<float, 3>& SingleThreadedRenderer::getEnvironmentMappingCubeMapPosition(int contextIdx) {
	return environmentMappingCubeMapPosition;
}

void SingleThreadedRenderer::setEnvironmentMappingCubeMapPosition(int contextIdx, array<float, 3>& position) {
	this->environmentMappingCubeMapPosition = position;
}

const Renderer::Renderer_Statistics SingleThreadedRenderer::getStatistics() {
	auto stats = statistics;
	statistics.time = Time::getCurrentMillis();
	statistics.memoryUsageGPU = -1LL;
	statistics.memoryUsageShared = -1LL;
	statistics.clearCalls = 0;
	statistics.renderCalls = 0;
	statistics.instances = 0;
	statistics.computeCalls = 0;
	statistics.triangles = 0;
	statistics.points = 0;
	statistics.linePoints = 0;
	statistics.bufferUploads = 0;
	statistics.textureUploads = 0;
	statistics.renderPasses = 0;
	statistics.drawCommands = 0;
	statistics.submits = 0;
	statistics.disposedTextures = 0;
	statistics.disposedBuffers = 0;
	return stats;
}
