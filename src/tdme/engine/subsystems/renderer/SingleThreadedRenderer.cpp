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
}

SingleThreadedRenderer::~SingleThreadedRenderer() {
}

Matrix2D3x3& SingleThreadedRenderer::getTextureMatrix(void* context) {
	return textureMatrix;
}

Renderer_Light& SingleThreadedRenderer::getLight(void* context, int32_t lightId) {
	return lights[lightId];
}

array<float, 4>& SingleThreadedRenderer::getEffectColorMul(void* context) {
	return effectColorMul;
}

array<float, 4>& SingleThreadedRenderer::getEffectColorAdd(void* context) {
	return effectColorAdd;
}

Renderer_Material& SingleThreadedRenderer::getMaterial(void* context) {
	return material;
}

const string SingleThreadedRenderer::getShader(void* context) {
	return shader;
}

void SingleThreadedRenderer::setShader(void* context, const string& id) {
	shader = id;
}
