// Generated from /tdme/src/tdme/engine/subsystems/renderer/GLRenderer.java
#include <tdme/engine/subsystems/renderer/GLRenderer.h>

#include <algorithm>

#include <java/lang/Math.h>
#include <java/lang/System.h>
#include <java/nio/ByteOrder.h>
#include <java/nio/ByteBuffer.h>
#include <tdme/engine/subsystems/renderer/GLRenderer_Light.h>
#include <tdme/engine/subsystems/renderer/GLRenderer_Material.h>
#include <tdme/math/Matrix4x4.h>
#include <Array.h>

using std::copy;
using std::begin;
using std::end;

using tdme::engine::subsystems::renderer::GLRenderer;
using java::lang::Math;
using java::lang::System;
using java::nio::FloatBuffer;
using tdme::engine::subsystems::renderer::GLRenderer_Light;
using tdme::engine::subsystems::renderer::GLRenderer_Material;
using tdme::math::Matrix4x4;

GLRenderer::GLRenderer() 
{
	init();
	for (auto i = 0; i < lights.size(); i++) {
		lights[i].spotCosCutoff = static_cast< float >(Math::cos(Math::PI / 180.0f * 180.0f));
	}
	projectionMatrix = (new Matrix4x4())->identity();
	cameraMatrix = (new Matrix4x4())->identity();
	modelViewMatrix = (new Matrix4x4())->identity();
	viewportMatrix = (new Matrix4x4())->identity();
	viewPortX = 0;
	viewPortY = 0;
	viewPortWidth = 0;
	viewPortHeight = 0;
	TEXTUREUNITS_MAX = 2;
	activeTextureUnit = 0;
}

void GLRenderer::init()
{
	ID_NONE = -1;
	CLEAR_DEPTH_BUFFER_BIT = -1;
	CLEAR_COLOR_BUFFER_BIT = -1;
	CULLFACE_FRONT = -1;
	CULLFACE_BACK = -1;
	CLIENTSTATE_TEXTURECOORD_ARRAY = -1;
	CLIENTSTATE_VERTEX_ARRAY = -1;
	CLIENTSTATE_NORMAL_ARRAY = -1;
	CLIENTSTATE_COLOR_ARRAY = -1;
	TEXTUREUNITS_MAX = -1;
	SHADER_FRAGMENT_SHADER = -1;
	SHADER_VERTEX_SHADER = -1;
	DEPTHFUNCTION_LESSEQUAL = -1;
	DEPTHFUNCTION_EQUAL = -1;
	FRAMEBUFFER_DEFAULT = -1;
	FRONTFACE_CW = -1;
	FRONTFACE_CCW = -1;
	pixelDepthBuffer = ByteBuffer::allocateDirect(1)->asFloatBuffer();
}

Matrix4x4* GLRenderer::getProjectionMatrix()
{
	return &projectionMatrix;
}

Matrix4x4* GLRenderer::getCameraMatrix()
{
	return &cameraMatrix;
}

Matrix4x4* GLRenderer::getModelViewMatrix()
{
	return &modelViewMatrix;
}

Matrix4x4* GLRenderer::getViewportMatrix()
{
	return &viewportMatrix;
}

void GLRenderer::setLightEnabled(int32_t lightId)
{
	lights[lightId].enabled = 1;
}

void GLRenderer::setLightDisabled(int32_t lightId)
{
	lights[lightId].enabled = 0;
}

void GLRenderer::setLightAmbient(int32_t lightId, array<float, 4>* ambient)
{
	copy(begin(*ambient), end(*ambient), begin(lights[lightId].ambient));
}

void GLRenderer::setLightDiffuse(int32_t lightId, array<float, 4>* diffuse)
{
	copy(begin(*diffuse), end(*diffuse), begin(lights[lightId].diffuse));
}

void GLRenderer::setLightPosition(int32_t lightId, array<float, 4>* position)
{
	copy(begin(*position), end(*position), begin(lights[lightId].position));
}

void GLRenderer::setLightSpotDirection(int32_t lightId, array<float, 3>* spotDirection)
{
	copy(begin(*spotDirection), end(*spotDirection), begin(lights[lightId].spotDirection));
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

void GLRenderer::setEffectColorMul(array<float, 4>* effectColorMul)
{
	copy(begin(*effectColorMul), end(*effectColorMul), begin(this->effectColorMul));
}

void GLRenderer::setEffectColorAdd(array<float, 4>* effectColorAdd)
{
	copy(begin(*effectColorAdd), end(*effectColorAdd), begin(this->effectColorAdd));
}

void GLRenderer::setMaterialEnabled()
{
}

void GLRenderer::setMaterialDisabled()
{
}

void GLRenderer::setMaterialAmbient(array<float, 4>* ambient)
{
	copy(begin(*ambient), end(*ambient), begin(material.ambient));
}

void GLRenderer::setMaterialDiffuse(array<float, 4>* diffuse)
{
	copy(begin(*diffuse), end(*diffuse), begin(material.diffuse));
}

void GLRenderer::setMaterialSpecular(array<float, 4>* specular)
{
	copy(begin(*specular), end(*specular), begin(material.specular));
}

void GLRenderer::setMaterialEmission(array<float, 4>* emission)
{
	copy(begin(*emission), end(*emission), begin(material.emission));
}

void GLRenderer::setMaterialShininess(float shininess)
{
	material.shininess = shininess;
}
