#include <tdme/engine/subsystems/framebuffer/SkyRenderShader.h>

#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/subsystems/framebuffer/FrameBufferRenderShader.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/FrameBuffer.h>
#include <tdme/engine/Light.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/Timing.h>
#include <tdme/math/Math.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>

using std::string;
using std::make_unique;

using tdme::engine::subsystems::framebuffer::SkyRenderShader;

using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::subsystems::framebuffer::FrameBufferRenderShader;
using tdme::engine::subsystems::manager::TextureManager;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Camera;
using tdme::engine::Color4;
using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::engine::Light;
using tdme::engine::Texture;
using tdme::engine::Timing;
using tdme::math::Math;
using tdme::math::Vector3;
using tdme::math::Vector4;

SkyRenderShader::SkyRenderShader(RendererBackend* rendererBackend)
{
	this->rendererBackend = rendererBackend;
}

SkyRenderShader::~SkyRenderShader()
{
}

bool SkyRenderShader::isInitialized()
{
	return initialized;
}

void SkyRenderShader::initialize()
{
	//
	auto shaderVersion = rendererBackend->getShaderVersion();

	//
	vertexShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/framebuffer",
		"render_vertexshader.vert"
	);
	if (vertexShaderId == 0) return;

	fragmentShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/framebuffer/sky",
		"render_fragmentshader.frag"
	);
	if (fragmentShaderId == 0) return;

	programId = rendererBackend->createProgram(rendererBackend->PROGRAM_OBJECTS);
	rendererBackend->attachShaderToProgram(programId, vertexShaderId);
	rendererBackend->attachShaderToProgram(programId, fragmentShaderId);
	if (rendererBackend->isUsingProgramAttributeLocation() == true) {
		rendererBackend->setProgramAttributeLocation(programId, 0, "inVertex");
		rendererBackend->setProgramAttributeLocation(programId, 2, "inTextureUV");
	}
	if (rendererBackend->linkProgram(programId) == false) return;

	//
	uniformLIGHT0_ENABLED = rendererBackend->getProgramUniformLocation(programId, "LIGHT0_ENABLED");
	if (uniformLIGHT0_ENABLED == -1) return;
	uniformLIGHT0_DIRECTION = rendererBackend->getProgramUniformLocation(programId, "LIGHT0_DIRECTION");
	if (uniformLIGHT0_DIRECTION == -1) return;
	uniformLIGHT1_ENABLED = rendererBackend->getProgramUniformLocation(programId, "LIGHT1_ENABLED");
	if (uniformLIGHT1_ENABLED == -1) return;
	uniformLIGHT1_DIRECTION = rendererBackend->getProgramUniformLocation(programId, "LIGHT1_DIRECTION");
	if (uniformLIGHT1_DIRECTION == -1) return;
	uniformStarsTexture = rendererBackend->getProgramUniformLocation(programId, "stars_texture");
	if (uniformStarsTexture == -1) return;
	uniformCloudsTopTexture = rendererBackend->getProgramUniformLocation(programId, "clouds_top_texture");
	if (uniformCloudsTopTexture == -1) return;
	uniformCloudsMiddleTexture = rendererBackend->getProgramUniformLocation(programId, "clouds_middle_texture");
	if (uniformCloudsMiddleTexture == -1) return;
	uniformCloudsBottomTexture = rendererBackend->getProgramUniformLocation(programId, "clouds_bottom_texture");
	if (uniformCloudsBottomTexture == -1) return;
	uniformLightScatteringPass = rendererBackend->getProgramUniformLocation(programId, "lightScatteringPass");
	if (uniformLightScatteringPass == -1) return;
	uniformTime = rendererBackend->getProgramUniformLocation(programId, "time");
	if (uniformTime == -1) return;
	uniformAspectRatio = rendererBackend->getProgramUniformLocation(programId, "aspectRatio");
	if (uniformAspectRatio == -1) return;
	uniformForwardVector = rendererBackend->getProgramUniformLocation(programId, "forwardVector");
	if (uniformForwardVector == -1) return;
	uniformSideVector = rendererBackend->getProgramUniformLocation(programId, "sideVector");
	if (uniformSideVector == -1) return;
	uniformUpVector = rendererBackend->getProgramUniformLocation(programId, "upVector");
	if (uniformUpVector == -1) return;
	//
	// sky
	uniformDayTopColor = rendererBackend->getProgramUniformLocation(programId, "day_top_color");
	if (uniformDayTopColor == -1) return;
	uniformDayBottomColor = rendererBackend->getProgramUniformLocation(programId, "day_bottom_color");
	if (uniformDayBottomColor == -1) return;
	uniformSunsetTopColor = rendererBackend->getProgramUniformLocation(programId, "sunset_top_color");
	if (uniformSunsetTopColor == -1) return;
	uniformSunsetBottomColor = rendererBackend->getProgramUniformLocation(programId, "sunset_bottom_color");
	if (uniformSunsetBottomColor == -1) return;
	uniformNightTopColor = rendererBackend->getProgramUniformLocation(programId, "night_top_color");
	if (uniformNightTopColor == -1) return;
	uniformNightBottomColor = rendererBackend->getProgramUniformLocation(programId, "night_bottom_color");
	if (uniformNightBottomColor == -1) return;
	// horizon
	uniformHorizonColor = rendererBackend->getProgramUniformLocation(programId, "horizon_color");
	if (uniformHorizonColor == -1) return;
	uniformHorizonBlur = rendererBackend->getProgramUniformLocation(programId, "horizon_blur");
	if (uniformHorizonBlur == -1) return;
	// sun
	uniformSunColorFactor = rendererBackend->getProgramUniformLocation(programId, "sun_color_factor");
	if (uniformSunColorFactor == -1) return;
	uniformSunColor = rendererBackend->getProgramUniformLocation(programId, "sun_color");
	if (uniformSunColor == -1) return;
	uniformSunSunsetColor = rendererBackend->getProgramUniformLocation(programId, "sun_sunset_color");
	if (uniformSunSunsetColor == -1) return;
	uniformSunSize = rendererBackend->getProgramUniformLocation(programId, "sun_size");
	if (uniformSunSize == -1) return;
	uniformSunBlur = rendererBackend->getProgramUniformLocation(programId, "sun_blur");
	if (uniformSunBlur == -1) return;
	// moon
	uniformMoonColorFactor = rendererBackend->getProgramUniformLocation(programId, "moon_color_factor");
	if (uniformMoonColorFactor == -1) return;
	uniformMoonColor = rendererBackend->getProgramUniformLocation(programId, "moon_color");
	if (uniformMoonColor == -1) return;
	uniformMoonSize = rendererBackend->getProgramUniformLocation(programId, "moon_size");
	if (uniformMoonSize == -1) return;
	uniformMoonBlur = rendererBackend->getProgramUniformLocation(programId, "moon_blur");
	if (uniformMoonBlur == -1) return;
	// clouds
	uniformCloudsEdgeColor = rendererBackend->getProgramUniformLocation(programId, "clouds_edge_color");
	if (uniformCloudsEdgeColor == -1) return;
	uniformCloudsTopColor = rendererBackend->getProgramUniformLocation(programId, "clouds_top_color");
	if (uniformCloudsTopColor == -1) return;
	uniformCloudsMiddleColor = rendererBackend->getProgramUniformLocation(programId, "clouds_middle_color");
	if (uniformCloudsMiddleColor == -1) return;
	uniformCloudsBottomColor = rendererBackend->getProgramUniformLocation(programId, "clouds_bottom_color");
	if (uniformCloudsBottomColor == -1) return;
	uniformCloudsSpeed = rendererBackend->getProgramUniformLocation(programId, "clouds_speed");
	if (uniformCloudsSpeed == -1) return;
	uniformCloudsDirection = rendererBackend->getProgramUniformLocation(programId, "clouds_direction");
	if (uniformCloudsDirection == -1) return;
	uniformCloudsScale = rendererBackend->getProgramUniformLocation(programId, "clouds_scale");
	if (uniformCloudsScale == -1) return;
	uniformCloudsCutoff = rendererBackend->getProgramUniformLocation(programId, "clouds_cutoff");
	if (uniformCloudsCutoff == -1) return;
	uniformCloudsFuzziness = rendererBackend->getProgramUniformLocation(programId, "clouds_fuzziness");
	if (uniformCloudsFuzziness == -1) return;
	uniformCloudsWeight = rendererBackend->getProgramUniformLocation(programId, "clouds_weight");
	if (uniformCloudsWeight == -1) return;
	uniformCloudsBlur = rendererBackend->getProgramUniformLocation(programId, "clouds_blur");
	if (uniformCloudsBlur == -1) return;
	uniformStarsSpeed = rendererBackend->getProgramUniformLocation(programId, "stars_speed");
	if (uniformStarsSpeed == -1) return;

	//
	loadTextures(".");

	//
	Engine::registerShader(
		Engine::ShaderType::SHADERTYPE_SKY,
		"sky",
		{
			// manual placing of sun and moon via shader parameters
			{ "manual_t", ShaderParameter(false) },
			{ "t", ShaderParameter(0.15f), ShaderParameter(0.0f), ShaderParameter(1.0f), ShaderParameter(0.05f) },
			// sky
			{ "day_top_color", ShaderParameter(Color4(0.1f, 0.6f, 1.0f, 1.0f)), ShaderParameter(Color4(0.0f, 0.0f, 0.0f, 1.0f)), ShaderParameter(Color4(1.0f, 1.0f, 1.0f, 1.0f)), ShaderParameter(Color4(0.1f, 0.1f, 0.1f, 0.0f)) },
			{ "day_bottom_color", ShaderParameter(Color4(0.4f, 0.8f, 1.0f, 1.0f)), ShaderParameter(Color4(0.0f, 0.0f, 0.0f, 1.0f)), ShaderParameter(Color4(1.0f, 1.0f, 1.0f, 1.0f)), ShaderParameter(Color4(0.1f, 0.1f, 0.1f, 0.0f)) },
			{ "sunset_top_color", ShaderParameter(Color4(0.7f, 0.75f, 1.0f, 1.0f)), ShaderParameter(Color4(0.0f, 0.0f, 0.0f, 1.0f)), ShaderParameter(Color4(1.0f, 1.0f, 1.0f, 1.0f)), ShaderParameter(Color4(0.1f, 0.1f, 0.1f, 0.0f)) },
			{ "sunset_bottom_color", ShaderParameter(Color4(1.0f, 0.5f, 0.7f, 1.0f)), ShaderParameter(Color4(0.0f, 0.0f, 0.0f, 1.0f)), ShaderParameter(Color4(1.0f, 1.0f, 1.0f, 1.0f)), ShaderParameter(Color4(0.1f, 0.1f, 0.1f, 0.0f)) },
			{ "night_top_color", ShaderParameter(Color4(0.02f, 0.0f, 0.04f, 1.0f)), ShaderParameter(Color4(0.0f, 0.0f, 0.0f, 1.0f)), ShaderParameter(Color4(1.0f, 1.0f, 1.0f, 1.0f)), ShaderParameter(Color4(0.1f, 0.1f, 0.1f, 0.0f)) },
			{ "night_bottom_color", ShaderParameter(Color4( 0.1f, 0.0f, 0.2f, 1.0f)), ShaderParameter(Color4(0.0f, 0.0f, 0.0f, 1.0f)), ShaderParameter(Color4(1.0f, 1.0f, 1.0f, 1.0f)), ShaderParameter(Color4(0.1f, 0.1f, 0.1f, 0.0f)) },
			// horizon
			{ "horizon_color", ShaderParameter(Color4(0.0f, 0.7f, 0.8f, 1.0f)), ShaderParameter(Color4(0.0f, 0.0f, 0.0f, 1.0f)), ShaderParameter(Color4(1.0f, 1.0f, 1.0f, 1.0f)), ShaderParameter(Color4(0.1f, 0.1f, 0.1f, 0.0f)) },
			{ "horizon_blur", ShaderParameter(0.05f), ShaderParameter(0.0f), ShaderParameter(1.0f), ShaderParameter(0.05f) },
			// sun
			{ "sun_color_factor", ShaderParameter(200.0f), ShaderParameter(0.0f), ShaderParameter(200.0f), ShaderParameter(10.0f) },
			{ "sun_color", ShaderParameter(Color4(1.0f, 0.8f, 0.1f, 1.0f)), ShaderParameter(Color4(0.0f, 0.0f, 0.0f, 1.0f)), ShaderParameter(Color4(1.0f, 1.0f, 1.0f, 1.0f)), ShaderParameter(Color4(0.1f, 0.1f, 0.1f, 0.0f)) },
			{ "sun_sunset_color", ShaderParameter(Color4(10.0f, 0.0f, 0.0f, 1.0f)), ShaderParameter(Color4(0.0f, 0.0f, 0.0f, 1.0f)), ShaderParameter(Color4(1.0f, 1.0f, 1.0f, 1.0f)), ShaderParameter(Color4(0.1f, 0.1f, 0.1f, 0.0f)) },
			{ "sun_size", ShaderParameter(0.2f), ShaderParameter(0.05f), ShaderParameter(1.0f), ShaderParameter(0.0475f) },
			{ "sun_blur", ShaderParameter(10.0f), ShaderParameter(0.05f), ShaderParameter(20.0f), ShaderParameter(0.9975f) },
			// moon
			{ "moon_color_factor", ShaderParameter(20.0f), ShaderParameter(0.0f), ShaderParameter(20.0f), ShaderParameter(1.0f) },
			{ "moon_color", ShaderParameter(Color4(1.0f, 0.95f, 0.7f, 1.0f)), ShaderParameter(Color4(0.0f, 0.0f, 0.0f, 1.0f)), ShaderParameter(Color4(1.0f, 1.0f, 1.0f, 1.0f)), ShaderParameter(Color4(0.1f, 0.1f, 0.1f, 0.0f)) },
			{ "moon_size", ShaderParameter(0.06f), ShaderParameter(0.05f), ShaderParameter(1.00f), ShaderParameter(0.0475f) },
			{ "moon_blur", ShaderParameter(0.1f), ShaderParameter(0.05f), ShaderParameter(10.00f), ShaderParameter(0.475f) },
			// clouds
			{ "clouds_edge_color", ShaderParameter(Color4(0.8f, 0.8f, 0.98f, 1.0f)), ShaderParameter(Color4(0.0f, 0.0f, 0.0f, 1.0f)), ShaderParameter(Color4(1.0f, 1.0f, 1.0f, 1.0f)), ShaderParameter(Color4(0.1f, 0.1f, 0.1f, 0.0f)) },
			{ "clouds_top_color", ShaderParameter(Color4(1.0f, 1.0f, 1.00f, 1.0f)), ShaderParameter(Color4(0.0f, 0.0f, 0.0f, 1.0f)), ShaderParameter(Color4(1.0f, 1.0f, 1.0f, 1.0f)), ShaderParameter(Color4(0.1f, 0.1f, 0.1f, 0.0f)) },
			{ "clouds_middle_color", ShaderParameter(Color4(0.92f, 0.92f, 0.98f, 1.0f)), ShaderParameter(Color4(0.0f, 0.0f, 0.0f, 1.0f)), ShaderParameter(Color4(1.0f, 1.0f, 1.0f, 1.0f)), ShaderParameter(Color4(0.1f, 0.1f, 0.1f, 0.0f)) },
			{ "clouds_bottom_color", ShaderParameter(Color4(0.83f, 0.83f, 0.94f, 1.0f)), ShaderParameter(Color4(0.0f, 0.0f, 0.0f, 1.0f)), ShaderParameter(Color4(1.0f, 1.0f, 1.0f, 1.0f)), ShaderParameter(Color4(0.1f, 0.1f, 0.1f, 0.0f)) },
			{ "clouds_speed", ShaderParameter(2.0f), ShaderParameter(0.0f), ShaderParameter(20.0f), ShaderParameter(1.0f) },
			{ "clouds_direction", ShaderParameter(0.2f), ShaderParameter(-0.5f), ShaderParameter(0.5f), ShaderParameter(0.05f) },
			{ "clouds_scale", ShaderParameter(1.0f), ShaderParameter(0.0f), ShaderParameter(4.0f), ShaderParameter(0.2f) },
			{ "clouds_cutoff", ShaderParameter(0.3f), ShaderParameter(0.0f), ShaderParameter(1.0f), ShaderParameter(0.05f) },
			{ "clouds_fuzziness", ShaderParameter(0.5f), ShaderParameter(0.0f), ShaderParameter(2.0f), ShaderParameter(0.1f) },
			{ "clouds_weight", ShaderParameter(0.0f), ShaderParameter(0.0f), ShaderParameter(1.0f), ShaderParameter(0.05f) },
			{ "clouds_blur", ShaderParameter(0.25f), ShaderParameter(0.0f), ShaderParameter(1.0f), ShaderParameter(0.05f) },
			{ "stars_speed", ShaderParameter(1.0f), ShaderParameter(0.0f), ShaderParameter(1.0f), ShaderParameter(0.05f) },
		}
	);

	//
	initialized = true;
}

void SkyRenderShader::dispose() {
	unloadTextures();
}

void SkyRenderShader::unloadTextures() {
	if (starsTexture != nullptr) {
		Engine::getInstance()->getTextureManager()->removeTexture(starsTexture);
		starsTexture->releaseReference();
		starsTexture = nullptr;
		starsTextureId = rendererBackend->ID_NONE;
	}
	if (cloudsTopTexture != nullptr) {
		Engine::getInstance()->getTextureManager()->removeTexture(cloudsTopTexture);
		cloudsTopTexture->releaseReference();
		cloudsTopTexture = nullptr;
		cloudsTopTextureId = rendererBackend->ID_NONE;
	}
	if (cloudsMiddleTexture != nullptr) {
		Engine::getInstance()->getTextureManager()->removeTexture(cloudsMiddleTexture);
		cloudsMiddleTexture->releaseReference();
		cloudsMiddleTexture = nullptr;
		cloudsMiddleTextureId = rendererBackend->ID_NONE;
	}
	if (cloudsBottomTexture != nullptr) {
		Engine::getInstance()->getTextureManager()->removeTexture(cloudsBottomTexture);
		cloudsBottomTexture->releaseReference();
		cloudsBottomTexture = nullptr;
		cloudsBottomTextureId = rendererBackend->ID_NONE;
	}
}

void SkyRenderShader::loadTextures(const string& pathName) {
	unloadTextures();
	starsTextureId = Engine::getInstance()->getTextureManager()->addTexture(starsTexture = TextureReader::read(pathName + "/resources/engine/textures", "stars.png"), rendererBackend->CONTEXTINDEX_DEFAULT);
	cloudsTopTextureId = Engine::getInstance()->getTextureManager()->addTexture(cloudsTopTexture = TextureReader::read(pathName + "/resources/engine/textures", "clouds_top.png"), rendererBackend->CONTEXTINDEX_DEFAULT);
	cloudsMiddleTextureId = Engine::getInstance()->getTextureManager()->addTexture(cloudsMiddleTexture = TextureReader::read(pathName + "/resources/engine/textures", "clouds_middle.png"), rendererBackend->CONTEXTINDEX_DEFAULT);
	cloudsBottomTextureId = Engine::getInstance()->getTextureManager()->addTexture(cloudsBottomTexture = TextureReader::read(pathName + "/resources/engine/textures", "clouds_bottom.png"), rendererBackend->CONTEXTINDEX_DEFAULT);
}

void SkyRenderShader::render(Engine* engine, bool lightScatteringPass, Camera* camera) {
	// use default context
	auto contextIdx = rendererBackend->CONTEXTINDEX_DEFAULT;

	// camera, use engine camera if no camera given
	if (camera == nullptr) camera = engine->getCamera();

	//
	rendererBackend->useProgram(contextIdx, programId);
	rendererBackend->setLighting(contextIdx, rendererBackend->LIGHTING_NONE);

	//
	auto sunLight = engine->getLightAt(Engine::LIGHTIDX_SUN);
	auto moonLight = engine->getLightAt(Engine::LIGHTIDX_MOON);

	// manual placing of sun and moon, by t 0 <= t < 1.0
	if (engine->getShaderParameter("sky", "manual_t").getBooleanValue() == true) {
		auto t = engine->getShaderParameter("sky", "t").getFloatValue();
		sunLight->setupSun(t);
		moonLight->setupMoon(t);
	}

	//
	auto sunLightPosition4 = sunLight->getPosition().clone().scale(1.0f / (Math::abs(sunLight->getPosition().getW()) < Math::EPSILON?1.0:sunLight->getPosition().getW()));
	auto sunLightPosition = Vector3(sunLightPosition4[0], sunLightPosition4[1], sunLightPosition4[2]);
	auto sunLightDirection = sunLightPosition.clone().normalize().scale(-1.0f);
	//
	auto moonLightPosition4 = moonLight->getPosition().clone().scale(1.0f / (Math::abs(moonLight->getPosition().getW()) < Math::EPSILON?1.0:moonLight->getPosition().getW()));
	auto moonLightPosition = Vector3(moonLightPosition4[0], moonLightPosition4[1], moonLightPosition4[2]);
	auto moonLightDirection = moonLightPosition.clone().normalize().scale(-1.0f);
	//
	rendererBackend->setProgramUniformInteger(contextIdx, uniformLIGHT0_ENABLED, sunLight->isEnabled() == true?1:0);
	rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformLIGHT0_DIRECTION, sunLightDirection.getArray());
	rendererBackend->setProgramUniformInteger(contextIdx, uniformLIGHT1_ENABLED, moonLight->isEnabled() == true?1:0);
	rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformLIGHT1_DIRECTION, moonLightDirection.getArray());
	rendererBackend->setProgramUniformInteger(contextIdx, uniformLightScatteringPass, lightScatteringPass == false?0:1);
	rendererBackend->setProgramUniformFloat(contextIdx, uniformTime, static_cast<float>(engine->getTiming()->getTotalTime()) / 1000.0f);
	rendererBackend->setProgramUniformFloat(contextIdx, uniformAspectRatio, static_cast<float>(camera->getWidth()) / static_cast<float>(camera->getHeight()));
	rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformForwardVector, camera->getForwardVector().getArray());
	rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformSideVector, camera->getSideVector().getArray());
	rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformUpVector, camera->getUpVector().getArray());
	//
	rendererBackend->setProgramUniformInteger(contextIdx, uniformStarsTexture, 0);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformCloudsTopTexture, 1);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformCloudsMiddleTexture, 2);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformCloudsBottomTexture, 3);
	// sky
	rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformDayTopColor, engine->getShaderParameter("sky", "day_top_color").getColor3ValueArray());
	rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformDayBottomColor, engine->getShaderParameter("sky", "day_bottom_color").getColor3ValueArray());
	rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformSunsetTopColor, engine->getShaderParameter("sky", "sunset_top_color").getColor3ValueArray());
	rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformSunsetBottomColor, engine->getShaderParameter("sky", "sunset_bottom_color").getColor3ValueArray());
	rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformNightTopColor, engine->getShaderParameter("sky", "night_top_color").getColor3ValueArray());
	rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformNightBottomColor, engine->getShaderParameter("sky", "night_bottom_color").getColor3ValueArray());
	// horizon
	rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformHorizonColor, engine->getShaderParameter("sky", "horizon_color").getColor3ValueArray());
	rendererBackend->setProgramUniformFloat(contextIdx, uniformHorizonBlur, engine->getShaderParameter("sky", "horizon_blur").getFloatValue());
	// sun
	rendererBackend->setProgramUniformFloat(contextIdx, uniformSunColorFactor, engine->getShaderParameter("sky", "sun_color_factor").getFloatValue());
	rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformSunColor, engine->getShaderParameter("sky", "sun_color").getColor3ValueArray());
	rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformSunSunsetColor, engine->getShaderParameter("sky", "sun_sunset_color").getColor3ValueArray());
	rendererBackend->setProgramUniformFloat(contextIdx, uniformSunSize, engine->getShaderParameter("sky", "sun_size").getFloatValue());
	rendererBackend->setProgramUniformFloat(contextIdx, uniformSunBlur, engine->getShaderParameter("sky", "sun_blur").getFloatValue());
	// moon
	rendererBackend->setProgramUniformFloat(contextIdx, uniformMoonColorFactor, engine->getShaderParameter("sky", "moon_color_factor").getFloatValue());
	rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformMoonColor, engine->getShaderParameter("sky", "moon_color").getColor3ValueArray());
	rendererBackend->setProgramUniformFloat(contextIdx, uniformMoonSize, engine->getShaderParameter("sky", "moon_size").getFloatValue());
	rendererBackend->setProgramUniformFloat(contextIdx, uniformMoonBlur, engine->getShaderParameter("sky", "moon_blur").getFloatValue());
	// clouds
	rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformCloudsEdgeColor, engine->getShaderParameter("sky", "clouds_edge_color").getColor3ValueArray());
	rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformCloudsTopColor, engine->getShaderParameter("sky", "clouds_top_color").getColor3ValueArray());
	rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformCloudsMiddleColor, engine->getShaderParameter("sky", "clouds_middle_color").getColor3ValueArray());
	rendererBackend->setProgramUniformFloatVec3(contextIdx, uniformCloudsBottomColor, engine->getShaderParameter("sky", "clouds_bottom_color").getColor3ValueArray());
	rendererBackend->setProgramUniformFloat(contextIdx, uniformCloudsSpeed, engine->getShaderParameter("sky", "clouds_speed").getFloatValue());
	rendererBackend->setProgramUniformFloat(contextIdx, uniformCloudsDirection, engine->getShaderParameter("sky", "clouds_direction").getFloatValue());
	rendererBackend->setProgramUniformFloat(contextIdx, uniformCloudsScale, engine->getShaderParameter("sky", "clouds_scale").getFloatValue());
	rendererBackend->setProgramUniformFloat(contextIdx, uniformCloudsCutoff, engine->getShaderParameter("sky", "clouds_cutoff").getFloatValue());
	rendererBackend->setProgramUniformFloat(contextIdx, uniformCloudsFuzziness, engine->getShaderParameter("sky", "clouds_fuzziness").getFloatValue());
	rendererBackend->setProgramUniformFloat(contextIdx, uniformCloudsWeight, engine->getShaderParameter("sky", "clouds_weight").getFloatValue());
	rendererBackend->setProgramUniformFloat(contextIdx, uniformCloudsBlur, engine->getShaderParameter("sky", "clouds_blur").getFloatValue());
	rendererBackend->setProgramUniformFloat(contextIdx, uniformStarsSpeed, engine->getShaderParameter("sky", "stars_speed").getFloatValue());
	//
	rendererBackend->disableDepthBufferWriting();
	rendererBackend->disableDepthBufferTest();
	//
	rendererBackend->disableCulling(contextIdx);
	//
	rendererBackend->setTextureUnit(contextIdx, 0);
	rendererBackend->bindTexture(contextIdx, starsTextureId);
	//
	rendererBackend->setTextureUnit(contextIdx, 1);
	rendererBackend->bindTexture(contextIdx, cloudsTopTextureId);
	//
	rendererBackend->setTextureUnit(contextIdx, 2);
	rendererBackend->bindTexture(contextIdx, cloudsMiddleTextureId);
	//
	rendererBackend->setTextureUnit(contextIdx, 3);
	rendererBackend->bindTexture(contextIdx, cloudsBottomTextureId);

	// use frame buffer render shader
	auto frameBufferRenderShader = Engine::getFrameBufferRenderShader();

	//
	rendererBackend->bindVerticesBufferObject(contextIdx, frameBufferRenderShader->getVBOVertices());
	rendererBackend->bindTextureCoordinatesBufferObject(contextIdx, frameBufferRenderShader->getVBOTextureCoordinates());

	// draw
	rendererBackend->drawTrianglesFromBufferObjects(contextIdx, 2, 0);

	// unbind buffers
	rendererBackend->unbindBufferObjects(contextIdx);

	//
	//
	rendererBackend->setTextureUnit(contextIdx, 0);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
	rendererBackend->setTextureUnit(contextIdx, 1);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
	rendererBackend->setTextureUnit(contextIdx, 2);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);
	rendererBackend->setTextureUnit(contextIdx, 3);
	rendererBackend->bindTexture(contextIdx, rendererBackend->ID_NONE);

	// unset
	rendererBackend->enableCulling(contextIdx);
	rendererBackend->enableDepthBufferTest();
	rendererBackend->enableDepthBufferWriting();
}
