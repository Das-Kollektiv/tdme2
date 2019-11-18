#include <tdme/engine/subsystems/renderer/SingleThreadedRenderer.h>

#include <tdme/math/Math.h>
#include <tdme/engine/subsystems/renderer/Renderer_Light.h>
#include <tdme/engine/subsystems/renderer/Renderer_Material.h>
#include <tdme/math/Matrix4x4.h>

using tdme::engine::subsystems::renderer::SingleThreadedRenderer;
using tdme::math::Math;
using tdme::engine::subsystems::renderer::Renderer_Light;
using tdme::engine::subsystems::renderer::Renderer_Material;
using tdme::math::Matrix4x4;

SingleThreadedRenderer::SingleThreadedRenderer()
{
	// set up lights
	for (auto i = 0; i < lights.size(); i++) {
		lights[i].spotCosCutoff = static_cast< float >(Math::cos(Math::PI / 180.0f * 180.0f));
	}
	projectionMatrix.identity();
	cameraMatrix.identity();
	modelViewMatrix.identity();
	viewportMatrix.identity();
}

SingleThreadedRenderer::~SingleThreadedRenderer() {
}

Matrix4x4& SingleThreadedRenderer::getProjectionMatrix()
{
	return projectionMatrix;
}

Matrix4x4& SingleThreadedRenderer::getCameraMatrix()
{
	return cameraMatrix;
}

Matrix4x4& SingleThreadedRenderer::getModelViewMatrix()
{
	return modelViewMatrix;
}

Matrix4x4& SingleThreadedRenderer::getViewportMatrix()
{
	return viewportMatrix;
}

Matrix2D3x3& SingleThreadedRenderer::getTextureMatrix(void* context) {
	return textureMatrix;
}

const Renderer_Light& SingleThreadedRenderer::getLight(void* context, int32_t lightId) {
	return lights[lightId];
}

void SingleThreadedRenderer::setLight(void* context, int32_t lightId, const Renderer_Light& light) {
	lights[lightId] = light;
}

const array<float, 4>& SingleThreadedRenderer::getEffectColorMul(void* context) {
	return effectColorMul;
}

void SingleThreadedRenderer::setEffectColorMul(void* context, const array<float, 4>& effectColorMul) {
	this->effectColorMul = effectColorMul;
}

const array<float, 4>& SingleThreadedRenderer::getEffectColorAdd(void* context) {
	return effectColorAdd;
}

void SingleThreadedRenderer::setEffectColorAdd(void* context, const array<float, 4>& effectColorAdd) {
	this->effectColorAdd = effectColorAdd;
}

const Renderer_Material& SingleThreadedRenderer::getMaterial(void* context) {
	return material;
}

void SingleThreadedRenderer::setMaterial(void* context, const Renderer_Material& material) {
	this->material = material;
}
