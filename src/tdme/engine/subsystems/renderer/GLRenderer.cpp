// Generated from /tdme/src/tdme/engine/subsystems/renderer/GLRenderer.java
#include <tdme/engine/subsystems/renderer/GLRenderer.h>

#include <java/lang/Math.h>
#include <java/lang/System.h>
#include <java/nio/ByteOrder.h>
#include <java/nio/ByteBuffer.h>
#include <tdme/engine/subsystems/renderer/GLRenderer_Light.h>
#include <tdme/engine/subsystems/renderer/GLRenderer_Material.h>
#include <tdme/math/Matrix4x4.h>
#include <Array.h>
#include <ObjectArray.h>
#include <SubArray.h>

using tdme::engine::subsystems::renderer::GLRenderer;
using java::lang::Math;
using java::lang::System;
using java::nio::FloatBuffer;
using tdme::engine::subsystems::renderer::GLRenderer_Light;
using tdme::engine::subsystems::renderer::GLRenderer_Material;
using tdme::math::Matrix4x4;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace engine {
namespace subsystems {
namespace renderer {
typedef ::SubArray< ::tdme::engine::subsystems::renderer::GLRenderer_Light, ::java::lang::ObjectArray > GLRenderer_LightArray;
}  // namespace renderer
}  // namespace subsystems
}  // namespace engine

namespace math {
typedef ::SubArray< ::tdme::math::Matrix4x4, ::java::lang::ObjectArray > Matrix4x4Array;
}  // namespace math
}  // namespace tdme

GLRenderer::GLRenderer(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GLRenderer::GLRenderer() 
	: GLRenderer(*static_cast< ::default_init_tag* >(0))
{
	ctor();
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

void GLRenderer::ctor()
{
	super::ctor();
	init();
	effectColorMul = new floatArray({
		1.0f,
		1.0f,
		1.0f,
		1.0f
	});
	effectColorAdd = new floatArray({
		0.0f,
		0.0f,
		0.0f,
		0.0f
	});
	material = new GLRenderer_Material(this);
	material->ambient = new floatArray({
		0.2f,
		0.2f,
		0.2f,
		1.0f
	});
	material->diffuse = new floatArray({
		0.8f,
		0.8f,
		0.8f,
		1.0f
	});
	material->specular = new floatArray({
		0.0f,
		0.0f,
		0.0f,
		1.0f
	});
	material->emission = new floatArray({
		0.0f,
		0.0f,
		0.0f,
		1.0f
	});
	material->shininess = 0.0f;
	lights = new GLRenderer_LightArray(8);
	for (auto i = 0; i < lights->length; i++) {
		lights->set(i, new GLRenderer_Light(this));
		(*lights)[i]->enabled = 0;
		(*lights)[i]->ambient = new floatArray({
			0.0f,
			0.0f,
			0.0f,
			1.0f
		});
		(*lights)[i]->diffuse = new floatArray({
			1.0f,
			1.0f,
			1.0f,
			1.0f
		});
		(*lights)[i]->specular = new floatArray({
			1.0f,
			1.0f,
			1.0f,
			1.0f
		});
		(*lights)[i]->position = new floatArray({
			0.0f,
			0.0f,
			0.0f,
			0.0f
		});
		(*lights)[i]->spotDirection = new floatArray({
			0.0f,
			0.0f,
			-1.0f
		});
		(*lights)[i]->spotExponent = 0.0f;
		(*lights)[i]->spotCosCutoff = static_cast< float >(Math::cos(Math::PI / 180.0f * 180.0f));
		(*lights)[i]->constantAttenuation = 1.0f;
		(*lights)[i]->linearAttenuation = 0.0f;
		(*lights)[i]->quadraticAttenuation = 0.0f;
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
	textureMatrix = new Matrix4x4Array(TEXTUREUNITS_MAX);
	for (auto i = 0; i < textureMatrix->length; i++) {
		textureMatrix->set(i, (new Matrix4x4())->identity());
	}
	activeTextureUnit = 0;
}

Matrix4x4* GLRenderer::getProjectionMatrix()
{
	return projectionMatrix;
}

Matrix4x4* GLRenderer::getCameraMatrix()
{
	return cameraMatrix;
}

Matrix4x4* GLRenderer::getModelViewMatrix()
{
	return modelViewMatrix;
}

Matrix4x4* GLRenderer::getViewportMatrix()
{
	return viewportMatrix;
}

void GLRenderer::setLightEnabled(int32_t lightId)
{
	(*lights)[lightId]->enabled = 1;
}

void GLRenderer::setLightDisabled(int32_t lightId)
{
	(*lights)[lightId]->enabled = 0;
}

void GLRenderer::setLightAmbient(int32_t lightId, floatArray* ambient)
{
	System::arraycopy(ambient, 0, (*lights)[lightId]->ambient, 0, Math::min(ambient->length, (*lights)[lightId]->ambient->length));
}

void GLRenderer::setLightDiffuse(int32_t lightId, floatArray* diffuse)
{
	System::arraycopy(diffuse, 0, (*lights)[lightId]->diffuse, 0, Math::min(diffuse->length, (*lights)[lightId]->diffuse->length));
}

void GLRenderer::setLightPosition(int32_t lightId, floatArray* position)
{
	System::arraycopy(position, 0, (*lights)[lightId]->position, 0, Math::min(position->length, (*lights)[lightId]->position->length));
}

void GLRenderer::setLightSpotDirection(int32_t lightId, floatArray* spotDirection)
{
	System::arraycopy(spotDirection, 0, (*lights)[lightId]->spotDirection, 0, Math::min(spotDirection->length, (*lights)[lightId]->spotDirection->length));
}

void GLRenderer::setLightSpotExponent(int32_t lightId, float spotExponent)
{
	(*lights)[lightId]->spotExponent = spotExponent;
}

void GLRenderer::setLightSpotCutOff(int32_t lightId, float spotCutOff)
{
	(*lights)[lightId]->spotCosCutoff = static_cast< float >(Math::cos(Math::PI / 180.0f * spotCutOff));
}

void GLRenderer::setLightConstantAttenuation(int32_t lightId, float constantAttenuation)
{
	(*lights)[lightId]->constantAttenuation = constantAttenuation;
}

void GLRenderer::setLightLinearAttenuation(int32_t lightId, float linearAttenuation)
{
	(*lights)[lightId]->linearAttenuation = linearAttenuation;
}

void GLRenderer::setLightQuadraticAttenuation(int32_t lightId, float QuadraticAttenuation)
{
	(*lights)[lightId]->quadraticAttenuation = QuadraticAttenuation;
}

void GLRenderer::setEffectColorMul(floatArray* effectColorMul)
{
	System::arraycopy(effectColorMul, 0, this->effectColorMul, 0, Math::min(effectColorMul->length, this->effectColorMul->length));
}

void GLRenderer::setEffectColorAdd(floatArray* effectColorAdd)
{
	System::arraycopy(effectColorAdd, 0, this->effectColorAdd, 0, Math::min(effectColorAdd->length, this->effectColorAdd->length));
}

void GLRenderer::setMaterialEnabled()
{
}

void GLRenderer::setMaterialDisabled()
{
}

void GLRenderer::setMaterialAmbient(floatArray* ambient)
{
	System::arraycopy(ambient, 0, material->ambient, 0, Math::min(ambient->length, material->ambient->length));
}

void GLRenderer::setMaterialDiffuse(floatArray* diffuse)
{
	System::arraycopy(diffuse, 0, material->diffuse, 0, Math::min(diffuse->length, material->diffuse->length));
}

void GLRenderer::setMaterialSpecular(floatArray* specular)
{
	System::arraycopy(specular, 0, material->specular, 0, Math::min(specular->length, material->specular->length));
}

void GLRenderer::setMaterialEmission(floatArray* emission)
{
	System::arraycopy(emission, 0, material->emission, 0, Math::min(emission->length, material->emission->length));
}

void GLRenderer::setMaterialShininess(float shininess)
{
	material->shininess = shininess;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GLRenderer::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.renderer.GLRenderer", 42);
    return c;
}

java::lang::Class* GLRenderer::getClass0()
{
	return class_();
}

