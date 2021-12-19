#include <tdme/engine/subsystems/framebuffer/DeferredLightingRenderShader.h>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/subsystems/lighting/LightingShaderConstants.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/GeometryBuffer.h>
#include <tdme/math/Math.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/FloatBuffer.h>

using tdme::engine::subsystems::framebuffer::DeferredLightingRenderShader;

using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::TextureReader;
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
		string() +
		"#define HAVE_DEPTH_FOG\n" +
		"#define LIGHT_COUNT " + to_string(Engine::LIGHTS_MAX) + "\n#define USE_PUNCTUAL\n#define MATERIAL_METALLICROUGHNESS\n#define USE_IBL\n",
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/functions/specular",
			"specular_lighting.inc.glsl"
		) +
		"\n\n" +
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/functions/pbr",
			"tonemapping.inc.glsl"
		) +
		"\n\n" +
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/functions/pbr",
			"functions.inc.glsl"
		) +
		"\n\n" +
		FileSystem::getInstance()->getContentAsString(
			"shader/" + shaderVersion + "/functions/pbr",
			"pbr_lighting.inc.glsl"
		) +
		"\n\n"
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

	//	specular lights
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

	// PBR
	uniformCamera = renderer->getProgramUniformLocation(programId, "u_Camera");
	if (uniformCamera == -1) return;

	//	lights
	for (auto i = 0; i < Engine::LIGHTS_MAX; i++) {
		uniformPBRLightEnabled[i] = renderer->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].enabled");
		if (uniformPBRLightEnabled[i] == -1) return;
		//uniformLightAmbient[i] = renderer->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].ambient");
		//if (uniformLightAmbient[i] == -1) return;
		uniformPBRLightDirection[i] = renderer->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].direction");
		if (uniformPBRLightDirection[i] == -1) return;
		uniformPBRLightRange[i] = renderer->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].range");
		if (uniformPBRLightRange[i] == -1) return;
		uniformPBRLightColor[i] = renderer->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].color");
		if (uniformPBRLightColor[i] == -1) return;
		uniformPBRLightIntensity[i] = renderer->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].intensity");
		if (uniformPBRLightIntensity[i] == -1) return;
		uniformPBRLightPosition[i] = renderer->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].position");
		if (uniformPBRLightPosition[i] == -1) return;
		uniformPBRLightInnerConeCos[i] = renderer->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].innerConeCos");
		if (uniformPBRLightInnerConeCos[i] == -1) return;
		uniformPBRLightOuterConeCos[i] = renderer->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].outerConeCos");
		if (uniformPBRLightOuterConeCos[i] == -1) return;
		uniformPBRLightType[i] = renderer->getProgramUniformLocation(programId, "u_PBRLights[" + to_string(i) + "].type");
		if (uniformPBRLightType[i] == -1) return;
	}

	#if !defined(VULKAN)
		// IBL
		uniformDiffuseEnvSampler = renderer->getProgramUniformLocation(programId, "u_DiffuseEnvSampler");
		if (uniformDiffuseEnvSampler == -1) return;
		uniformSpecularEnvSampler = renderer->getProgramUniformLocation(programId, "u_SpecularEnvSampler");
		if (uniformSpecularEnvSampler == -1) return;
		uniformbrdfLUT = renderer->getProgramUniformLocation(programId, "u_brdfLUT");
		if (uniformbrdfLUT == -1) return;

		//
		string environmentType = "studio_grey";
		textureDiffuseEnvSampler =
			Engine::getInstance()->getTextureManager()->addCubeMapTexture(
				"pbr-environment-diffuse",
				TextureReader::read("resources/engine/environments/" + environmentType + "/diffuse", "diffuse_left.png"),
				TextureReader::read("resources/engine/environments/" + environmentType + "/diffuse", "diffuse_right.png"),
				TextureReader::read("resources/engine/environments/" + environmentType + "/diffuse", "diffuse_top.png"),
				TextureReader::read("resources/engine/environments/" + environmentType + "/diffuse", "diffuse_bottom.png"),
				TextureReader::read("resources/engine/environments/" + environmentType + "/diffuse", "diffuse_front.png"),
				TextureReader::read("resources/engine/environments/" + environmentType + "/diffuse", "diffuse_back.png"),
				renderer->CONTEXTINDEX_DEFAULT
			);
		textureSpecularEnvSampler =
			Engine::getInstance()->getTextureManager()->addCubeMapTexture(
				"pbr-environment-specular",
				TextureReader::read("resources/engine/environments/" + environmentType + "/specular", "specular_left.png"),
				TextureReader::read("resources/engine/environments/" + environmentType + "/specular", "specular_right.png"),
				TextureReader::read("resources/engine/environments/" + environmentType + "/specular", "specular_top.png"),
				TextureReader::read("resources/engine/environments/" + environmentType + "/specular", "specular_bottom.png"),
				TextureReader::read("resources/engine/environments/" + environmentType + "/specular", "specular_front.png"),
				TextureReader::read("resources/engine/environments/" + environmentType + "/specular", "specular_back.png"),
				renderer->CONTEXTINDEX_DEFAULT
			);
		texturebrdfLUT = Engine::getInstance()->getTextureManager()->addTexture(TextureReader::read("resources/engine/environments", "brdfLUT.png"), renderer->CONTEXTINDEX_DEFAULT);
	#endif

	//
	initialized = true;
}

void DeferredLightingRenderShader::useProgram(Engine* engine)
{
	auto contextIdx = renderer->CONTEXTINDEX_DEFAULT;
	renderer->useProgram(contextIdx, programId);
	renderer->setLighting(contextIdx, renderer->LIGHTING_NONE);
	renderer->setProgramUniformInteger(contextIdx, uniformGeometryBufferTextureId1, 0);
	renderer->setProgramUniformInteger(contextIdx, uniformGeometryBufferTextureId2, 1);
	renderer->setProgramUniformInteger(contextIdx, uniformGeometryBufferTextureId3, 2);
	renderer->setProgramUniformInteger(contextIdx, uniformColorBufferTextureUnit1, 3);
	renderer->setProgramUniformInteger(contextIdx, uniformColorBufferTextureUnit2, 4);
	renderer->setProgramUniformInteger(contextIdx, uniformColorBufferTextureUnit3, 5);
	renderer->setProgramUniformInteger(contextIdx, uniformColorBufferTextureUnit4, 6);
	renderer->setProgramUniformInteger(contextIdx, uniformColorBufferTextureUnit5, 7);
	renderer->setProgramUniformInteger(contextIdx, uniformDepthBufferTextureUnit, 8);

	// Specular
	for (auto lightId = 0; lightId < Engine::LIGHTS_MAX; lightId++) {
		auto light = engine->getLightAt(lightId);
		renderer->setProgramUniformInteger(contextIdx, uniformSpecularLightEnabled[lightId], light->isEnabled() == true?1:0);
		if (light->isEnabled() == false) continue;
		renderer->setProgramUniformFloatVec4(contextIdx, uniformSpecularLightAmbient[lightId], light->getAmbient().getArray());
		renderer->setProgramUniformFloatVec4(contextIdx, uniformSpecularLightDiffuse[lightId], light->getDiffuse().getArray());
		renderer->setProgramUniformFloatVec4(contextIdx, uniformSpecularLightSpecular[lightId], light->getSpecular().getArray());
		renderer->setProgramUniformFloatVec4(contextIdx, uniformSpecularLightPosition[lightId], light->getPosition().getArray());
		renderer->setProgramUniformFloatVec3(contextIdx, uniformSpecularLightSpotDirection[lightId], light->getSpotDirection().getArray());
		renderer->setProgramUniformFloat(contextIdx, uniformSpecularLightSpotExponent[lightId], light->getSpotExponent());
		renderer->setProgramUniformFloat(contextIdx, uniformSpecularLightSpotCosCutoff[lightId], static_cast<float>(Math::cos(Math::PI / 180.0f * light->getSpotCutOff())));
		renderer->setProgramUniformFloat(contextIdx, uniformSpecularLightConstantAttenuation[lightId], light->getConstantAttenuation());
		renderer->setProgramUniformFloat(contextIdx, uniformSpecularLightLinearAttenuation[lightId], light->getLinearAttenuation());
		renderer->setProgramUniformFloat(contextIdx, uniformSpecularLightQuadraticAttenuation[lightId], light->getQuadraticAttenuation());
		renderer->setProgramUniformFloat(contextIdx, uniformSpecularLightRadius[lightId], light->getRadius());
	}
	renderer->setProgramUniformFloatMatrix4x4(contextIdx, uniformCameraMatrix, engine->getCamera()->getModelViewMatrix().getArray());

	// PBR
	renderer->setProgramUniformFloatVec3(contextIdx, uniformCamera, renderer->getCameraPosition().getArray());

	#if !defined(VULKAN)
		//	IBL
		renderer->setProgramUniformInteger(contextIdx, uniformDiffuseEnvSampler, 9);
		renderer->setProgramUniformInteger(contextIdx, uniformSpecularEnvSampler, 10);
		renderer->setProgramUniformInteger(contextIdx, uniformbrdfLUT, 11);
		renderer->setTextureUnit(contextIdx, 9);
		renderer->bindCubeMapTexture(contextIdx, textureDiffuseEnvSampler);
		renderer->setTextureUnit(contextIdx, 10);
		renderer->bindCubeMapTexture(contextIdx, textureSpecularEnvSampler);
		renderer->setTextureUnit(contextIdx, 11);
		renderer->bindCubeMapTexture(contextIdx, texturebrdfLUT);
	#endif

	//	lights
	for (auto lightId = 0; lightId < Engine::LIGHTS_MAX; lightId++) {
		auto light = engine->getLightAt(lightId);
		if (uniformPBRLightEnabled[lightId] != -1) renderer->setProgramUniformInteger(contextIdx, uniformPBRLightEnabled[lightId], light->isEnabled() == true?1:0);
		if (light->isEnabled() == false) continue;
		auto& ambient = light->getAmbient().getArray();
		auto& diffuse = light->getDiffuse().getArray();
		auto& position = light->getPosition().getArray();
		// renderer->setProgramUniformFloatVec3(context, uniformLightAmbient[lightId], {{ ambient[0], ambient[1], ambient[2] }});
		renderer->setProgramUniformFloatVec3(contextIdx, uniformPBRLightDirection[lightId], light->getSpotDirection().getArray());
		renderer->setProgramUniformFloat(contextIdx, uniformPBRLightRange[lightId], 0.0f);
		renderer->setProgramUniformFloatVec3(contextIdx, uniformPBRLightColor[lightId], {{ diffuse[0], diffuse[1], diffuse[2] }});
		renderer->setProgramUniformFloat(contextIdx, uniformPBRLightIntensity[lightId], 1.0f);
		renderer->setProgramUniformFloatVec3(contextIdx, uniformPBRLightPosition[lightId],{{ position[0], position[1], position[2] }});
		if (uniformPBRLightType[lightId] != -1) renderer->setProgramUniformInteger(contextIdx, uniformPBRLightType[lightId], 0);
	}

	//
	isRunning = true;
}

void DeferredLightingRenderShader::unUseProgram()
{
	auto contextIdx = renderer->CONTEXTINDEX_DEFAULT;
	auto textureUnit = renderer->getTextureUnit(contextIdx);
	// PBR
	#if !defined(VULKAN)
		//	IBL
		renderer->setTextureUnit(contextIdx, 9);
		renderer->bindTexture(contextIdx, renderer->ID_NONE);
		renderer->setTextureUnit(contextIdx, 10);
		renderer->bindTexture(contextIdx, renderer->ID_NONE);
		renderer->setTextureUnit(contextIdx, 11);
		renderer->bindTexture(contextIdx, renderer->ID_NONE);
		renderer->setTextureUnit(contextIdx, textureUnit);
	#endif

	//
	isRunning = false;
}
