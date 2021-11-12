#include <tdme/engine/subsystems/framebuffer/DeferredLightingRenderShader.h>

#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/GeometryBuffer.h>
#include <tdme/math/Math.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/FloatBuffer.h>

using tdme::engine::subsystems::framebuffer::DeferredLightingRenderShader;

using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::manager::VBOManager_VBOManaged;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::rendering::ObjectBuffer;
using tdme::engine::Engine;
using tdme::engine::GeometryBuffer;
using tdme::math::Math;
using tdme::utilities::ByteBuffer;
using tdme::utilities::FloatBuffer;

DeferredLightingRenderShader::DeferredLightingRenderShader(Renderer* renderer)
{
	this->renderer = renderer;
	initialized = false;
	isRunning = false;
}

DeferredLightingRenderShader::~DeferredLightingRenderShader()
{
}

bool DeferredLightingRenderShader::isInitialized()
{
	return initialized;
}

void DeferredLightingRenderShader::initialize()
{
	auto shaderVersion = renderer->getShaderVersion();
	vertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/framebuffer",
		"render_vertexshader.vert",
		"#define HAVE_DEPTH_FOG"
	);
	if (vertexShaderId == 0) return;

	fragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/framebuffer",
		"deferred_lighting_fragmentshader.frag",
		"#define HAVE_DEPTH_FOG"
	);
	if (fragmentShaderId == 0) return;

	programId = renderer->createProgram(renderer->PROGRAM_OBJECTS);
	renderer->attachShaderToProgram(programId, vertexShaderId);
	renderer->attachShaderToProgram(programId, fragmentShaderId);
	if (renderer->isUsingProgramAttributeLocation() == true) {
		renderer->setProgramAttributeLocation(programId, 0, "inVertex");
		renderer->setProgramAttributeLocation(programId, 2, "inTextureUV");
	}
	if (renderer->linkProgram(programId) == false) return;

	// uniforms
	//	geometry buffers
	uniformGeometryBufferTextureId1 = renderer->getProgramUniformLocation(programId, "geometryBufferTextureId1");
	if (uniformGeometryBufferTextureId1 == -1) return;
	uniformGeometryBufferTextureId2 = renderer->getProgramUniformLocation(programId, "geometryBufferTextureId2");
	if (uniformGeometryBufferTextureId2 == -1) return;
	uniformGeometryBufferTextureId3 = renderer->getProgramUniformLocation(programId, "geometryBufferTextureId3");
	if (uniformGeometryBufferTextureId3 == -1) return;
	//	color buffers
	uniformColorBufferTextureUnit1 = renderer->getProgramUniformLocation(programId, "colorBufferTextureUnit1");
	if (uniformColorBufferTextureUnit1 == -1) return;
	uniformColorBufferTextureUnit2 = renderer->getProgramUniformLocation(programId, "colorBufferTextureUnit2");
	if (uniformColorBufferTextureUnit2 == -1) return;
	uniformColorBufferTextureUnit3 = renderer->getProgramUniformLocation(programId, "colorBufferTextureUnit3");
	if (uniformColorBufferTextureUnit3 == -1) return;
	uniformColorBufferTextureUnit4 = renderer->getProgramUniformLocation(programId, "colorBufferTextureUnit4");
	if (uniformColorBufferTextureUnit4 == -1) return;
	uniformColorBufferTextureUnit5 = renderer->getProgramUniformLocation(programId, "colorBufferTextureUnit5");
	if (uniformColorBufferTextureUnit5 == -1) return;
	//	depth buffer
	uniformDepthBufferTextureUnit = renderer->getProgramUniformLocation(programId, "depthBufferTextureUnit");
	if (uniformDepthBufferTextureUnit == -1) return;

	//	lights
	for (auto i = 0; i < Engine::LIGHTS_MAX; i++) {
		uniformLightEnabled[i] = renderer->getProgramUniformLocation(programId, "lights[" + to_string(i) +"].enabled");
		if (uniformLightEnabled[i] == -1) return;
		uniformLightAmbient[i] = renderer->getProgramUniformLocation(programId,"lights[" + to_string(i) + "].ambient");
		if (uniformLightAmbient[i] == -1) return;
		uniformLightDiffuse[i] = renderer->getProgramUniformLocation(programId, "lights[" + to_string(i) + "].diffuse");
		if (uniformLightDiffuse[i] == -1) return;
		uniformLightSpecular[i] = renderer->getProgramUniformLocation(programId, "lights[" + to_string(i) + "].specular");
		if (uniformLightSpecular[i] == -1) return;
		uniformLightPosition[i] = renderer->getProgramUniformLocation(programId, "lights[" + to_string(i) + "].position");
		if (uniformLightPosition[i] == -1) return;
		uniformLightSpotDirection[i] = renderer->getProgramUniformLocation(programId, "lights[" + to_string(i) + "].spotDirection");
		if (uniformLightSpotDirection[i] == -1) return;
		uniformLightSpotExponent[i] = renderer->getProgramUniformLocation(programId, "lights[" + to_string(i) + "].spotExponent");
		if (uniformLightSpotExponent[i] == -1) return;
		uniformLightSpotCosCutoff[i] = renderer->getProgramUniformLocation(programId, "lights[" + to_string(i) + "].spotCosCutoff");
		if (uniformLightSpotCosCutoff[i] == -1) return;
		uniformLightConstantAttenuation[i] = renderer->getProgramUniformLocation(programId, "lights[" + to_string(i) + "].constantAttenuation");
		if (uniformLightConstantAttenuation[i] == -1) return;
		uniformLightLinearAttenuation[i] = renderer->getProgramUniformLocation(programId, "lights[" + to_string(i) + "].linearAttenuation");
		if (uniformLightLinearAttenuation[i] == -1) return;
		uniformLightQuadraticAttenuation[i] = renderer->getProgramUniformLocation(programId, "lights[" + to_string(i) + "].quadraticAttenuation");
		if (uniformLightQuadraticAttenuation[i] == -1) return;
		uniformLightRadius[i] = renderer->getProgramUniformLocation(programId, "lights[" + to_string(i) + "].radius");
		if (uniformLightRadius[i] == -1) return;
	}

	//	camera matrix
	uniformCameraMatrix = renderer->getProgramUniformLocation(programId, "cameraMatrix");
	if (uniformCameraMatrix == -1) return;

	//
	initialized = true;
}

void DeferredLightingRenderShader::useProgram(Engine* engine)
{
	auto context = renderer->getDefaultContext();
	renderer->useProgram(context, programId);
	renderer->setLighting(context, renderer->LIGHTING_NONE);
	renderer->setProgramUniformInteger(context, uniformGeometryBufferTextureId1, 0);
	renderer->setProgramUniformInteger(context, uniformGeometryBufferTextureId2, 1);
	renderer->setProgramUniformInteger(context, uniformGeometryBufferTextureId3, 2);
	renderer->setProgramUniformInteger(context, uniformColorBufferTextureUnit1, 3);
	renderer->setProgramUniformInteger(context, uniformColorBufferTextureUnit2, 4);
	renderer->setProgramUniformInteger(context, uniformColorBufferTextureUnit3, 5);
	renderer->setProgramUniformInteger(context, uniformColorBufferTextureUnit4, 6);
	renderer->setProgramUniformInteger(context, uniformColorBufferTextureUnit5, 7);
	renderer->setProgramUniformInteger(context, uniformDepthBufferTextureUnit, 8);
	int32_t uniformTerrainsTexturePixelWidth { -1 };
	int32_t uniformTerrainsTexturePixelHeight { -1 };
	for (auto lightId = 0; lightId < Engine::LIGHTS_MAX; lightId++) {
		auto light = engine->getLightAt(lightId);
		renderer->setProgramUniformInteger(context, uniformLightEnabled[lightId], light->isEnabled() == true?1:0);
		if (light->isEnabled() == true) {
			renderer->setProgramUniformFloatVec4(context, uniformLightAmbient[lightId], light->getAmbient().getArray());
			renderer->setProgramUniformFloatVec4(context, uniformLightDiffuse[lightId], light->getDiffuse().getArray());
			renderer->setProgramUniformFloatVec4(context, uniformLightSpecular[lightId], light->getSpecular().getArray());
			renderer->setProgramUniformFloatVec4(context, uniformLightPosition[lightId], light->getPosition().getArray());
			renderer->setProgramUniformFloatVec3(context, uniformLightSpotDirection[lightId], light->getSpotDirection().getArray());
			renderer->setProgramUniformFloat(context, uniformLightSpotExponent[lightId], light->getSpotExponent());
			renderer->setProgramUniformFloat(context, uniformLightSpotCosCutoff[lightId], static_cast<float>(Math::cos(Math::PI / 180.0f * light->getSpotCutOff())));
			renderer->setProgramUniformFloat(context, uniformLightConstantAttenuation[lightId], light->getConstantAttenuation());
			renderer->setProgramUniformFloat(context, uniformLightLinearAttenuation[lightId], light->getLinearAttenuation());
			renderer->setProgramUniformFloat(context, uniformLightQuadraticAttenuation[lightId], light->getQuadraticAttenuation());
			renderer->setProgramUniformFloat(context, uniformLightRadius[lightId], light->getRadius());
		}
	}
	renderer->setProgramUniformFloatMatrix4x4(context, uniformCameraMatrix, engine->getCamera()->getModelViewMatrix().getArray());

	//
	isRunning = true;
}

void DeferredLightingRenderShader::unUseProgram()
{
	//
	isRunning = false;
}
