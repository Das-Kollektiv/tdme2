#include <tdme/engine/subsystems/framebuffer/DeferredLightingRenderShader.h>

#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/GeometryBuffer.h>
#include <tdme/math/Math.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
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
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
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
		"#define HAVE_DEPTH_FOG",
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/functions/specular",
			"specular_lighting.inc.glsl"
		)
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
		uniformSpecularLightEnabled[i] = renderer->getProgramUniformLocation(programId, "specularLights[" + to_string(i) +"].enabled");
		if (uniformSpecularLightEnabled[i] == -1) return;
		uniformSpecularLightAmbient[i] = renderer->getProgramUniformLocation(programId,"specularLights[" + to_string(i) + "].ambient");
		if (uniformSpecularLightAmbient[i] == -1) return;
		uniformSpecularLightDiffuse[i] = renderer->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].diffuse");
		if (uniformSpecularLightDiffuse[i] == -1) return;
		uniformSpecularLightSpecular[i] = renderer->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].specular");
		if (uniformSpecularLightSpecular[i] == -1) return;
		uniformSpecularLightPosition[i] = renderer->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].position");
		if (uniformSpecularLightPosition[i] == -1) return;
		uniformSpecularLightSpotDirection[i] = renderer->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].spotDirection");
		if (uniformSpecularLightSpotDirection[i] == -1) return;
		uniformSpecularLightSpotExponent[i] = renderer->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].spotExponent");
		if (uniformSpecularLightSpotExponent[i] == -1) return;
		uniformSpecularLightSpotCosCutoff[i] = renderer->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].spotCosCutoff");
		if (uniformSpecularLightSpotCosCutoff[i] == -1) return;
		uniformSpecularLightConstantAttenuation[i] = renderer->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].constantAttenuation");
		if (uniformSpecularLightConstantAttenuation[i] == -1) return;
		uniformSpecularLightLinearAttenuation[i] = renderer->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].linearAttenuation");
		if (uniformSpecularLightLinearAttenuation[i] == -1) return;
		uniformSpecularLightQuadraticAttenuation[i] = renderer->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].quadraticAttenuation");
		if (uniformSpecularLightQuadraticAttenuation[i] == -1) return;
		uniformSpecularLightRadius[i] = renderer->getProgramUniformLocation(programId, "specularLights[" + to_string(i) + "].radius");
		if (uniformSpecularLightRadius[i] == -1) return;
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
		renderer->setProgramUniformInteger(context, uniformSpecularLightEnabled[lightId], light->isEnabled() == true?1:0);
		if (light->isEnabled() == true) {
			renderer->setProgramUniformFloatVec4(context, uniformSpecularLightAmbient[lightId], light->getAmbient().getArray());
			renderer->setProgramUniformFloatVec4(context, uniformSpecularLightDiffuse[lightId], light->getDiffuse().getArray());
			renderer->setProgramUniformFloatVec4(context, uniformSpecularLightSpecular[lightId], light->getSpecular().getArray());
			renderer->setProgramUniformFloatVec4(context, uniformSpecularLightPosition[lightId], light->getPosition().getArray());
			renderer->setProgramUniformFloatVec3(context, uniformSpecularLightSpotDirection[lightId], light->getSpotDirection().getArray());
			renderer->setProgramUniformFloat(context, uniformSpecularLightSpotExponent[lightId], light->getSpotExponent());
			renderer->setProgramUniformFloat(context, uniformSpecularLightSpotCosCutoff[lightId], static_cast<float>(Math::cos(Math::PI / 180.0f * light->getSpotCutOff())));
			renderer->setProgramUniformFloat(context, uniformSpecularLightConstantAttenuation[lightId], light->getConstantAttenuation());
			renderer->setProgramUniformFloat(context, uniformSpecularLightLinearAttenuation[lightId], light->getLinearAttenuation());
			renderer->setProgramUniformFloat(context, uniformSpecularLightQuadraticAttenuation[lightId], light->getQuadraticAttenuation());
			renderer->setProgramUniformFloat(context, uniformSpecularLightRadius[lightId], light->getRadius());
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
