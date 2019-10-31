#include <tdme/engine/subsystems/renderer/Renderer.h>

#include <tdme/math/Math.h>
#include <tdme/engine/subsystems/renderer/Renderer_Light.h>
#include <tdme/engine/subsystems/renderer/Renderer_Material.h>
#include <tdme/math/Matrix4x4.h>

using tdme::engine::subsystems::renderer::Renderer;
using tdme::math::Math;
using tdme::utils::FloatBuffer;
using tdme::engine::subsystems::renderer::Renderer_Light;
using tdme::engine::subsystems::renderer::Renderer_Material;
using tdme::math::Matrix4x4;

Renderer::Renderer()
{
	ID_NONE = -1;
	CLEAR_DEPTH_BUFFER_BIT = -1;
	CLEAR_COLOR_BUFFER_BIT = -1;
	CULLFACE_FRONT = -1;
	CULLFACE_BACK = -1;
	TEXTUREUNITS_MAX = -1;
	SHADER_FRAGMENT_SHADER = -1;
	SHADER_VERTEX_SHADER = -1;
	SHADER_GEOMETRY_SHADER = -1;
	SHADER_COMPUTE_SHADER = -1;
	DEPTHFUNCTION_ALWAYS = -1;
	DEPTHFUNCTION_EQUAL = -1;
	DEPTHFUNCTION_LESSEQUAL = -1;
	DEPTHFUNCTION_GREATEREQUAL = -1;
	FRAMEBUFFER_DEFAULT = -1;
	FRONTFACE_CW = -1;
	FRONTFACE_CCW = -1;

	// set up lights
	for (auto i = 0; i < lights.size(); i++) {
		lights[i].spotCosCutoff = static_cast< float >(Math::cos(Math::PI / 180.0f * 180.0f));
	}
	projectionMatrix.identity();
	cameraMatrix.identity();
	modelViewMatrix.identity();
	viewportMatrix.identity();
	viewPortX = 0;
	viewPortY = 0;
	viewPortWidth = 0;
	viewPortHeight = 0;
	TEXTUREUNITS_MAX = 2;
	activeTextureUnit = 0;
	pointSize = 0.0;
}

Renderer::~Renderer() {
}

void* Renderer::getDefaultContext() {
	return nullptr;
}

void* Renderer::getContext(int contextIdx) {
	return nullptr;
}

int Renderer::getContextIndex(void* context) {
	return 0;
}


void Renderer::initializeFrame() {
}

Matrix4x4& Renderer::getProjectionMatrix()
{
	return projectionMatrix;
}

Matrix4x4& Renderer::getCameraMatrix()
{
	return cameraMatrix;
}

Matrix4x4& Renderer::getModelViewMatrix()
{
	return modelViewMatrix;
}

Matrix4x4& Renderer::getViewportMatrix()
{
	return viewportMatrix;
}

Matrix2D3x3& Renderer::getTextureMatrix(void* context) {
	return textureMatrix;
}

void Renderer::setLightEnabled(void* context, int32_t lightId)
{
	lights[lightId].enabled = 1;
}

void Renderer::setLightDisabled(void* context, int32_t lightId)
{
	lights[lightId].enabled = 0;
}

void Renderer::setLightAmbient(void* context, int32_t lightId, const array<float, 4>& ambient)
{
	lights[lightId].ambient = ambient;
}

void Renderer::setLightDiffuse(void* context, int32_t lightId, const array<float, 4>& diffuse)
{
	lights[lightId].diffuse = diffuse;
}

void Renderer::setLightPosition(void* context, int32_t lightId, const array<float, 4>& position)
{
	lights[lightId].position = position;
}

void Renderer::setLightSpotDirection(void* context, int32_t lightId, const array<float, 3>& spotDirection)
{
	lights[lightId].spotDirection = spotDirection;
}

void Renderer::setLightSpotExponent(void* context, int32_t lightId, float spotExponent)
{
	lights[lightId].spotExponent = spotExponent;
}

void Renderer::setLightSpotCutOff(void* context, int32_t lightId, float spotCutOff)
{
	lights[lightId].spotCosCutoff = static_cast< float >(Math::cos(Math::PI / 180.0f * spotCutOff));
}

void Renderer::setLightConstantAttenuation(void* context, int32_t lightId, float constantAttenuation)
{
	lights[lightId].constantAttenuation = constantAttenuation;
}

void Renderer::setLightLinearAttenuation(void* context, int32_t lightId, float linearAttenuation)
{
	lights[lightId].linearAttenuation = linearAttenuation;
}

void Renderer::setLightQuadraticAttenuation(void* context, int32_t lightId, float QuadraticAttenuation)
{
	lights[lightId].quadraticAttenuation = QuadraticAttenuation;
}

void Renderer::setEffectColorMul(void* context, const array<float, 4>& effectColorMul)
{
	this->effectColorMul = effectColorMul;
}

void Renderer::setEffectColorAdd(void* context, const array<float, 4>& effectColorAdd)
{
	this->effectColorAdd = effectColorAdd;
}

void Renderer::setMaterialAmbient(void* context, const array<float, 4>& ambient)
{
	material.ambient = ambient;
}

void Renderer::setMaterialDiffuse(void* context, const array<float, 4>& diffuse)
{
	material.diffuse = diffuse;
}

void Renderer::setMaterialSpecular(void* context, const array<float, 4>& specular)
{
	material.specular = specular;
}

void Renderer::setMaterialEmission(void* context, const array<float, 4>& emission)
{
	material.emission = emission;
}

void Renderer::setMaterialShininess(void* context, float shininess)
{
	material.shininess = shininess;
}

void Renderer::setMaterialDiffuseTextureMaskedTransparency(void* context, bool diffuseTextureMaskedTransparency)
{
	material.diffuseTextureMaskedTransparency = diffuseTextureMaskedTransparency == true?1:0;
}

void Renderer::setMaterialDiffuseTextureMaskedTransparencyThreshold(void* context, float diffuseTextureMaskedTransparencyThreshold)
{
	material.diffuseTextureMaskedTransparencyThreshold = diffuseTextureMaskedTransparencyThreshold;
}

void Renderer::setShader(const string& id) {
	this->shaderId = id;
}
