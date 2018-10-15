#include <tdme/engine/subsystems/renderer/GLRenderer.h>

#include <tdme/math/Math.h>
#include <tdme/engine/subsystems/renderer/GLRenderer_Light.h>
#include <tdme/engine/subsystems/renderer/GLRenderer_Material.h>
#include <tdme/math/Matrix4x4.h>

using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::math::Math;
using tdme::utils::FloatBuffer;
using tdme::engine::subsystems::renderer::GLRenderer_Light;
using tdme::engine::subsystems::renderer::GLRenderer_Material;
using tdme::math::Matrix4x4;

GLRenderer::GLRenderer() 
{
	init();
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
}

GLRenderer::~GLRenderer() {
}

void GLRenderer::init()
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
}

void GLRenderer::initializeFrame() {
}

Matrix4x4& GLRenderer::getProjectionMatrix()
{
	return projectionMatrix;
}

Matrix4x4& GLRenderer::getCameraMatrix()
{
	return cameraMatrix;
}

Matrix4x4& GLRenderer::getModelViewMatrix()
{
	return modelViewMatrix;
}

Matrix4x4& GLRenderer::getViewportMatrix()
{
	return viewportMatrix;
}

Matrix2D3x3& GLRenderer::getTextureMatrix() {
	return textureMatrix;
}

void GLRenderer::setLightEnabled(int32_t lightId)
{
	lights[lightId].enabled = 1;
}

void GLRenderer::setLightDisabled(int32_t lightId)
{
	lights[lightId].enabled = 0;
}

void GLRenderer::setLightAmbient(int32_t lightId, const array<float, 4>& ambient)
{
	lights[lightId].ambient = ambient;
}

void GLRenderer::setLightDiffuse(int32_t lightId, const array<float, 4>& diffuse)
{
	lights[lightId].diffuse = diffuse;
}

void GLRenderer::setLightPosition(int32_t lightId, const array<float, 4>& position)
{
	lights[lightId].position = position;
}

void GLRenderer::setLightSpotDirection(int32_t lightId, const array<float, 3>& spotDirection)
{
	lights[lightId].spotDirection = spotDirection;
}

void GLRenderer::setLightSpotExponent(int32_t lightId, float spotExponent)
{
	lights[lightId].spotExponent = spotExponent;
}

void GLRenderer::setLightSpotCutOff(int32_t lightId, float spotCutOff)
{
	lights[lightId].spotCosCutoff = static_cast< float >(Math::cos(Math::PI / 180.0f * spotCutOff));
}

void GLRenderer::setLightConstantAttenuation(int32_t lightId, float constantAttenuation)
{
	lights[lightId].constantAttenuation = constantAttenuation;
}

void GLRenderer::setLightLinearAttenuation(int32_t lightId, float linearAttenuation)
{
	lights[lightId].linearAttenuation = linearAttenuation;
}

void GLRenderer::setLightQuadraticAttenuation(int32_t lightId, float QuadraticAttenuation)
{
	lights[lightId].quadraticAttenuation = QuadraticAttenuation;
}

void GLRenderer::setEffectColorMul(const array<float, 4>& effectColorMul)
{
	this->effectColorMul = effectColorMul;
}

void GLRenderer::setEffectColorAdd(const array<float, 4>& effectColorAdd)
{
	this->effectColorAdd = effectColorAdd;
}

void GLRenderer::setMaterialEnabled()
{
}

void GLRenderer::setMaterialDisabled()
{
}

void GLRenderer::setMaterialAmbient(const array<float, 4>& ambient)
{
	material.ambient = ambient;
}

void GLRenderer::setMaterialDiffuse(const array<float, 4>& diffuse)
{
	material.diffuse = diffuse;
}

void GLRenderer::setMaterialSpecular(const array<float, 4>& specular)
{
	material.specular = specular;
}

void GLRenderer::setMaterialEmission(const array<float, 4>& emission)
{
	material.emission = emission;
}

void GLRenderer::setMaterialShininess(float shininess)
{
	material.shininess = shininess;
}

void GLRenderer::setMaterialDiffuseTextureMaskedTransparency(bool diffuseTextureMaskedTransparency)
{
	material.diffuseTextureMaskedTransparency = diffuseTextureMaskedTransparency == true?1:0;
}

void GLRenderer::setMaterialDiffuseTextureMaskedTransparencyThreshold(float diffuseTextureMaskedTransparencyThreshold)
{
	material.diffuseTextureMaskedTransparencyThreshold = diffuseTextureMaskedTransparencyThreshold;
}

void GLRenderer::setShader(const string& id) {
	this->shaderId = id;
}
