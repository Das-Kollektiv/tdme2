#include <tdme/engine/subsystems/lighting/LightingShaderPBRBaseImplementation.h>

#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/Timing.h>
#include <tdme/engine/subsystems/lighting/LightingShaderConstants.h>
#include <tdme/engine/subsystems/renderer/Renderer_Light.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/Console.h>

using std::to_string;
using std::string;

using tdme::engine::Engine;
using tdme::engine::Timing;
using tdme::engine::subsystems::lighting::LightingShaderConstants;
using tdme::engine::subsystems::lighting::LightingShaderPBRBaseImplementation;
using tdme::engine::subsystems::renderer::Renderer_Light;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utils::Console;

LightingShaderPBRBaseImplementation::LightingShaderPBRBaseImplementation(Renderer* renderer)
{
	this->renderer = renderer;
	initialized = false;
}

bool LightingShaderPBRBaseImplementation::isInitialized()
{
	return initialized;
}

void LightingShaderPBRBaseImplementation::initialize()
{

	// link program
	if (renderer->linkProgram(renderLightingProgramId) == false) return;

	// uniforms
	uniformBaseColorFactor = renderer->getProgramUniformLocation(renderLightingProgramId, "u_BaseColorFactor");
	if (uniformBaseColorFactor == -1) return;
	uniformBaseColorSampler = renderer->getProgramUniformLocation(renderLightingProgramId, "u_BaseColorSampler");
	if (uniformBaseColorSampler == -1) return;
	uniformBaseColorSamplerAvailable = renderer->getProgramUniformLocation(renderLightingProgramId, "u_BaseColorSamplerAvailable");
	if (uniformBaseColorSamplerAvailable == -1) return;
	uniformCamera = renderer->getProgramUniformLocation(renderLightingProgramId, "u_Camera");
	if (uniformCamera == -1) return;
	uniformExposure = renderer->getProgramUniformLocation(renderLightingProgramId, "u_Exposure");
	if (uniformExposure == -1) return;
	uniformMetallicFactor = renderer->getProgramUniformLocation(renderLightingProgramId, "u_MetallicFactor");
	if (uniformMetallicFactor == -1) return;
	uniformMetallicRoughnessSampler = renderer->getProgramUniformLocation(renderLightingProgramId, "u_MetallicRoughnessSampler");
	if (uniformMetallicRoughnessSampler == -1) return;
	uniformMetallicRoughnessSamplerAvailable = renderer->getProgramUniformLocation(renderLightingProgramId, "u_MetallicRoughnessSamplerAvailable");
	if (uniformMetallicRoughnessSamplerAvailable == -1) return;
	uniformNormalSampler = renderer->getProgramUniformLocation(renderLightingProgramId, "u_NormalSampler");
	if (uniformNormalSampler == -1) return;
	uniformNormalSamplerAvailable = renderer->getProgramUniformLocation(renderLightingProgramId, "u_NormalSamplerAvailable");
	if (uniformNormalSamplerAvailable == -1) return;
	uniformNormalScale = renderer->getProgramUniformLocation(renderLightingProgramId, "u_NormalScale");
	if (uniformNormalScale == -1) return;
	uniformRoughnessFactor = renderer->getProgramUniformLocation(renderLightingProgramId, "u_RoughnessFactor");
	if (uniformRoughnessFactor == -1) return;
	uniformViewProjectionMatrix = renderer->getProgramUniformLocation(renderLightingProgramId, "u_ViewProjectionMatrix");
	if (uniformViewProjectionMatrix == -1) return;
	for (auto i = 0; i < Engine::LIGHTS_MAX; i++) {
		uniformLightEnabled[i] = renderer->getProgramUniformLocation(renderLightingProgramId, "u_Lights[" + to_string(i) + "].enabled");
		if (uniformLightEnabled[i] == -1) return;
		uniformLightDirection[i] = renderer->getProgramUniformLocation(renderLightingProgramId, "u_Lights[" + to_string(i) + "].direction");
		if (uniformLightDirection[i] == -1) return;
		uniformLightRange[i] = renderer->getProgramUniformLocation(renderLightingProgramId, "u_Lights[" + to_string(i) + "].range");
		if (uniformLightRange[i] == -1) return;
		uniformLightColor[i] = renderer->getProgramUniformLocation(renderLightingProgramId, "u_Lights[" + to_string(i) + "].color");
		if (uniformLightColor[i] == -1) return;
		uniformLightIntensity[i] = renderer->getProgramUniformLocation(renderLightingProgramId, "u_Lights[" + to_string(i) + "].intensity");
		if (uniformLightIntensity[i] == -1) return;
		uniformLightPosition[i] = renderer->getProgramUniformLocation(renderLightingProgramId, "u_Lights[" + to_string(i) + "].position");
		if (uniformLightPosition[i] == -1) return;
		uniformLightInnerConeCos[i] = renderer->getProgramUniformLocation(renderLightingProgramId, "u_Lights[" + to_string(i) + "].innerConeCos");
		if (uniformLightInnerConeCos[i] == -1) return;
		uniformLightOuterConeCos[i] = renderer->getProgramUniformLocation(renderLightingProgramId, "u_Lights[" + to_string(i) + "].outerConeCos");
		if (uniformLightOuterConeCos[i] == -1) return;
		uniformLightType[i] = renderer->getProgramUniformLocation(renderLightingProgramId, "u_Lights[" + to_string(i) + "].type");
		if (uniformLightType[i] == -1) return;
	}

	//
	initialized = true;
}

void LightingShaderPBRBaseImplementation::useProgram(Engine* engine, void* context)
{
	renderer->useProgram(context, renderLightingProgramId);
	renderer->setLighting(context, renderer->LIGHTING_PBR);
	renderer->setProgramUniformFloatVec4(context, uniformBaseColorFactor, {{ 1.0f, 1.0f, 1.0f, 1.0f }});
	renderer->setProgramUniformInteger(context, uniformBaseColorSampler, LightingShaderConstants::PBR_TEXTUREUNIT_BASECOLOR);
	renderer->setProgramUniformFloat(context, uniformExposure, 1.0f);
	renderer->setProgramUniformFloat(context, uniformMetallicFactor, 1.0f);
	renderer->setProgramUniformInteger(context, uniformMetallicRoughnessSampler, LightingShaderConstants::PBR_TEXTUREUNIT_METALLICROUGHNESS);
	renderer->setProgramUniformInteger(context, uniformNormalSampler, LightingShaderConstants::PBR_TEXTUREUNIT_NORMAL);
	renderer->setProgramUniformFloat(context, uniformNormalScale, 1.0f);
	renderer->setProgramUniformFloat(context, uniformRoughnessFactor, 1.0f);
}

void LightingShaderPBRBaseImplementation::unUseProgram(void* context)
{
}

void LightingShaderPBRBaseImplementation::updateEffect(Renderer* renderer, void* context)
{
}

void LightingShaderPBRBaseImplementation::updateMaterial(Renderer* renderer, void* context)
{
}

void LightingShaderPBRBaseImplementation::updateLight(Renderer* renderer, void* context, int32_t lightId)
{
	auto& light = renderer->getLight(context, lightId);
	if (uniformLightEnabled[lightId] != -1) renderer->setProgramUniformInteger(context, uniformLightEnabled[lightId], light.enabled);
	if (light.enabled == 1) {
		if (uniformLightDirection[lightId] != -1) renderer->setProgramUniformFloatVec3(context, uniformLightDirection[lightId], light.spotDirection);
		if (uniformLightRange[lightId] != -1) renderer->setProgramUniformFloat(context, uniformLightRange[lightId], 0.0f);
		if (uniformLightColor[lightId] != -1)
			renderer->setProgramUniformFloatVec3(
				context,
				uniformLightColor[lightId],
				{{
					light.ambient[0] + light.diffuse[0],
					light.ambient[1] + light.diffuse[1],
					light.ambient[2] + light.diffuse[2]
				}}
			);
		if (uniformLightIntensity[lightId] != -1) renderer->setProgramUniformFloat(context, uniformLightIntensity[lightId], 1.0f);
		if (uniformLightPosition[lightId] != -1) renderer->setProgramUniformFloatVec3(context, uniformLightPosition[lightId],{{ light.position[0], light.position[1], light.position[2] }});
		if (uniformLightType[lightId] != -1) renderer->setProgramUniformInteger(context, uniformLightType[lightId], 0);
	}
}

void LightingShaderPBRBaseImplementation::updateMatrices(Renderer* renderer, void* context)
{
	// set up camera position and view projection matrices
	// matrices
	Matrix4x4 vpMatrix;
	Vector3 camera;
	renderer->getCameraMatrix().getTranslation(camera);
	// object to screen matrix
	vpMatrix.set(renderer->getCameraMatrix()).multiply(renderer->getProjectionMatrix());
	// upload matrices
	renderer->setProgramUniformFloatMatrix4x4(context, uniformViewProjectionMatrix, vpMatrix.getArray());
	renderer->setProgramUniformFloatVec3(context, uniformCamera, camera.getArray());
}

void LightingShaderPBRBaseImplementation::updateTextureMatrix(Renderer* renderer, void* context) {
}

void LightingShaderPBRBaseImplementation::bindTexture(Renderer* renderer, void* context, int32_t textureId)
{
	if (renderer->isPBRAvailable() == false) return;
	switch (renderer->getTextureUnit(context)) {
		case LightingShaderConstants::PBR_TEXTUREUNIT_BASECOLOR:
			if (uniformBaseColorSamplerAvailable != -1) renderer->setProgramUniformInteger(context, uniformBaseColorSamplerAvailable, textureId == 0 ? 0 : 1);
			break;
		case LightingShaderConstants::PBR_TEXTUREUNIT_METALLICROUGHNESS:
			if (uniformMetallicRoughnessSamplerAvailable != -1) renderer->setProgramUniformInteger(context, uniformMetallicRoughnessSamplerAvailable, textureId == 0 ? 0 : 1);
			break;
		case LightingShaderConstants::PBR_TEXTUREUNIT_NORMAL:
			if (uniformNormalSamplerAvailable != -1) renderer->setProgramUniformInteger(context, uniformNormalSamplerAvailable, textureId == 0 ? 0 : 1);
			break;
	}
}
