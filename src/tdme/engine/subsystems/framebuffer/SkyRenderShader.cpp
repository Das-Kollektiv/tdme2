#include <tdme/engine/subsystems/framebuffer/SkyRenderShader.h>

#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/subsystems/framebuffer/FrameBufferRenderShader.h>
#include <tdme/engine/subsystems/manager/TextureManager.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/Camera.h>
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
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::FrameBuffer;
using tdme::engine::Light;
using tdme::engine::Texture;
using tdme::engine::Timing;
using tdme::math::Math;
using tdme::math::Vector3;
using tdme::math::Vector4;

SkyRenderShader::SkyRenderShader(Renderer* renderer)
{
	this->renderer = renderer;
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
	auto shaderVersion = renderer->getShaderVersion();

	//
	vertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/framebuffer",
		"render_vertexshader.vert"
	);
	if (vertexShaderId == 0) return;

	fragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/framebuffer/sky",
		"render_fragmentshader.frag"
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

	//
	uniformLIGHT0_ENABLED = renderer->getProgramUniformLocation(programId, "LIGHT0_ENABLED");
	if (uniformLIGHT0_ENABLED == -1) return;
	uniformLIGHT0_DIRECTION = renderer->getProgramUniformLocation(programId, "LIGHT0_DIRECTION");
	if (uniformLIGHT0_DIRECTION == -1) return;
	uniformLIGHT1_ENABLED = renderer->getProgramUniformLocation(programId, "LIGHT1_ENABLED");
	if (uniformLIGHT1_ENABLED == -1) return;
	uniformLIGHT1_DIRECTION = renderer->getProgramUniformLocation(programId, "LIGHT1_DIRECTION");
	if (uniformLIGHT1_DIRECTION == -1) return;
	uniformStarsTexture = renderer->getProgramUniformLocation(programId, "stars_texture");
	if (uniformStarsTexture == -1) return;
	uniformLightScatteringPass = renderer->getProgramUniformLocation(programId, "lightScatteringPass");
	if (uniformLightScatteringPass == -1) return;
	uniformTime = renderer->getProgramUniformLocation(programId, "time");
	if (uniformTime == -1) return;
	uniformAspectRatio = renderer->getProgramUniformLocation(programId, "aspectRatio");
	if (uniformAspectRatio == -1) return;
	uniformForwardVector = renderer->getProgramUniformLocation(programId, "forwardVector");
	if (uniformForwardVector == -1) return;
	uniformSideVector = renderer->getProgramUniformLocation(programId, "sideVector");
	if (uniformSideVector == -1) return;
	uniformUpVector = renderer->getProgramUniformLocation(programId, "upVector");
	if (uniformUpVector == -1) return;
	//
	// sky
	uniformDayTopColor = renderer->getProgramUniformLocation(programId, "day_top_color");
	if (uniformDayTopColor == -1) return;
	uniformDayBottomColor = renderer->getProgramUniformLocation(programId, "day_bottom_color");
	if (uniformDayBottomColor == -1) return;
	uniformSunsetTopColor = renderer->getProgramUniformLocation(programId, "sunset_top_color");
	if (uniformSunsetTopColor == -1) return;
	uniformSunsetBottomColor = renderer->getProgramUniformLocation(programId, "sunset_bottom_color");
	if (uniformSunsetBottomColor == -1) return;
	uniformNightTopColor = renderer->getProgramUniformLocation(programId, "night_top_color");
	if (uniformNightTopColor == -1) return;
	uniformNightBottomColor = renderer->getProgramUniformLocation(programId, "night_bottom_color");
	if (uniformNightBottomColor == -1) return;
	// horizon
	uniformHorizonColor = renderer->getProgramUniformLocation(programId, "horizon_color");
	if (uniformHorizonColor == -1) return;
	uniformHorizonBlur = renderer->getProgramUniformLocation(programId, "horizon_blur");
	if (uniformHorizonBlur == -1) return;
	// sun
	uniformSunColorFactor = renderer->getProgramUniformLocation(programId, "sun_color_factor");
	if (uniformSunColorFactor == -1) return;
	uniformSunColor = renderer->getProgramUniformLocation(programId, "sun_color");
	if (uniformSunColor == -1) return;
	uniformSunSunsetColor = renderer->getProgramUniformLocation(programId, "sun_sunset_color");
	if (uniformSunSunsetColor == -1) return;
	uniformSunSize = renderer->getProgramUniformLocation(programId, "sun_size");
	if (uniformSunSize == -1) return;
	uniformSunBlur = renderer->getProgramUniformLocation(programId, "sun_blur");
	if (uniformSunBlur == -1) return;
	// moon
	uniformMoonColorFactor = renderer->getProgramUniformLocation(programId, "moon_color_factor");
	if (uniformMoonColorFactor == -1) return;
	uniformMoonColor = renderer->getProgramUniformLocation(programId, "moon_color");
	if (uniformMoonColor == -1) return;
	uniformMoonSize = renderer->getProgramUniformLocation(programId, "moon_size");
	if (uniformMoonSize == -1) return;
	uniformMoonBlur = renderer->getProgramUniformLocation(programId, "moon_blur");
	if (uniformMoonBlur == -1) return;
	// clouds
	uniformCloudsEdgeColor = renderer->getProgramUniformLocation(programId, "clouds_edge_color");
	if (uniformCloudsEdgeColor == -1) return;
	uniformCloudsTopColor = renderer->getProgramUniformLocation(programId, "clouds_top_color");
	if (uniformCloudsTopColor == -1) return;
	uniformCloudsMiddleColor = renderer->getProgramUniformLocation(programId, "clouds_middle_color");
	if (uniformCloudsMiddleColor == -1) return;
	uniformCloudsBottomColor = renderer->getProgramUniformLocation(programId, "clouds_bottom_color");
	if (uniformCloudsBottomColor == -1) return;
	uniformCloudsSpeed = renderer->getProgramUniformLocation(programId, "clouds_speed");
	if (uniformCloudsSpeed == -1) return;
	uniformCloudsDirection = renderer->getProgramUniformLocation(programId, "clouds_direction");
	if (uniformCloudsDirection == -1) return;
	uniformCloudsScale = renderer->getProgramUniformLocation(programId, "clouds_scale");
	if (uniformCloudsScale == -1) return;
	uniformCloudsCutoff = renderer->getProgramUniformLocation(programId, "clouds_cutoff");
	if (uniformCloudsCutoff == -1) return;
	uniformCloudsFuzziness = renderer->getProgramUniformLocation(programId, "clouds_fuzziness");
	if (uniformCloudsFuzziness == -1) return;
	uniformCloudsWeight = renderer->getProgramUniformLocation(programId, "clouds_weight");
	if (uniformCloudsWeight == -1) return;
	uniformCloudsBlur = renderer->getProgramUniformLocation(programId, "clouds_blur");
	if (uniformCloudsBlur == -1) return;
	uniformStarsSpeed = renderer->getProgramUniformLocation(programId, "stars_speed");
	if (uniformStarsSpeed == -1) return;

	//
	loadTextures(".");

	//
	Engine::registerShader(
		Engine::ShaderType::SHADERTYPE_SKY,
		"sky",
		{
			// sky
			{ "day_top_color", ShaderParameter(Vector3(0.1f, 0.6f, 1.0f)) },
			{ "day_bottom_color", ShaderParameter(Vector3(0.4f, 0.8f, 1.0f)) },
			{ "sunset_top_color", ShaderParameter(Vector3(0.7f, 0.75f, 1.0f)) },
			{ "sunset_bottom_color", ShaderParameter(Vector3(1.0f, 0.5f, 0.7f)) },
			{ "night_top_color", ShaderParameter(Vector3(0.02f, 0.0f, 0.04f)) },
			{ "night_bottom_color", ShaderParameter(Vector3( 0.1f, 0.0f, 0.2f)) },
			// horizon
			{ "horizon_color", ShaderParameter(Vector3(0.0f, 0.7f, 0.8f)) },
			{ "horizon_blur", ShaderParameter(0.05f) },
			// sun
			{ "sun_color_factor", ShaderParameter(200.0f) },
			{ "sun_color", ShaderParameter(Vector3(1.0f, 0.8f, 0.1f)) },
			{ "sun_sunset_color", ShaderParameter(Vector3(10.0f, 0.0f, 0.0f)) },
			{ "sun_size", ShaderParameter(0.2f) },
			{ "sun_blur", ShaderParameter(10.0f) },
			// moon
			{ "moon_color_factor", ShaderParameter(20.0f) },
			{ "moon_color", ShaderParameter(Vector3(1.0f, 0.95f, 0.7f)) },
			{ "moon_size", ShaderParameter(0.06f) },
			{ "moon_blur", ShaderParameter(0.1f) },
			// clouds
			{ "clouds_edge_color", ShaderParameter(Vector3(0.8f, 0.8f, 0.98f)) },
			{ "clouds_top_color", ShaderParameter(Vector3(1.0f, 1.0f, 1.00f)) },
			{ "clouds_middle_color", ShaderParameter(Vector3(0.92f, 0.92f, 0.98f)) },
			{ "clouds_bottom_color", ShaderParameter(Vector3(0.83f, 0.83f, 0.94f)) },
			{ "clouds_speed", ShaderParameter(2.0f) },
			{ "clouds_direction", ShaderParameter(0.2f) },
			{ "clouds_scale", ShaderParameter(1.0f) },
			{ "clouds_cutoff", ShaderParameter(0.3f) },
			{ "clouds_fuzziness", ShaderParameter(0.5f) },
			{ "clouds_weight", ShaderParameter(0.0f) },
			{ "clouds_blur", ShaderParameter(0.25f) },
			{ "stars_speed", ShaderParameter(1.0f) }
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
		starsTextureId = renderer->ID_NONE;
	}
}

void SkyRenderShader::loadTextures(const string& pathName) {
	unloadTextures();
	starsTextureId = Engine::getInstance()->getTextureManager()->addTexture(starsTexture = TextureReader::read(pathName + "/resources/engine/textures", "stars.png"), renderer->CONTEXTINDEX_DEFAULT);
}

void SkyRenderShader::render(Engine* engine, bool lightScatteringPass, Camera* camera) {
	// use default context
	auto contextIdx = renderer->CONTEXTINDEX_DEFAULT;

	// camera, use engine camera if no camera given
	if (camera == nullptr) camera = engine->getCamera();

	//
	renderer->useProgram(contextIdx, programId);
	renderer->setLighting(contextIdx, renderer->LIGHTING_NONE);

	//
	auto sunLight = engine->getLightAt(Engine::LIGHTIDX_SUN);
	auto moonLight = engine->getLightAt(Engine::LIGHTIDX_MOON);

	//
	auto sunLightPosition4 = sunLight->getPosition().clone().scale(1.0f / (Math::abs(sunLight->getPosition().getW()) < Math::EPSILON?1.0:sunLight->getPosition().getW()));
	auto sunLightPosition = Vector3(sunLightPosition4[0], sunLightPosition4[1], sunLightPosition4[2]);
	auto sunLightDirection = sunLightPosition.clone().normalize().scale(-1.0f);
	//
	auto moonLightPosition4 = moonLight->getPosition().clone().scale(1.0f / (Math::abs(moonLight->getPosition().getW()) < Math::EPSILON?1.0:moonLight->getPosition().getW()));
	auto moonLightPosition = Vector3(moonLightPosition4[0], moonLightPosition4[1], moonLightPosition4[2]);
	auto moonLightDirection = moonLightPosition.clone().normalize().scale(-1.0f);
	//
	renderer->setProgramUniformInteger(contextIdx, uniformLIGHT0_ENABLED, sunLight->isEnabled() == true?1:0);
	renderer->setProgramUniformFloatVec3(contextIdx, uniformLIGHT0_DIRECTION, sunLightDirection.getArray());
	renderer->setProgramUniformInteger(contextIdx, uniformLIGHT1_ENABLED, moonLight->isEnabled() == true?1:0);
	renderer->setProgramUniformFloatVec3(contextIdx, uniformLIGHT1_DIRECTION, moonLightDirection.getArray());
	renderer->setProgramUniformInteger(contextIdx, uniformLightScatteringPass, lightScatteringPass == false?0:1);
	renderer->setProgramUniformFloat(contextIdx, uniformTime, static_cast<float>(engine->getTiming()->getTotalTime()) / 1000.0f);
	renderer->setProgramUniformFloat(contextIdx, uniformAspectRatio, static_cast<float>(camera->getWidth()) / static_cast<float>(camera->getHeight()));
	renderer->setProgramUniformFloatVec3(contextIdx, uniformForwardVector, camera->getForwardVector().getArray());
	renderer->setProgramUniformFloatVec3(contextIdx, uniformSideVector, camera->getSideVector().getArray());
	renderer->setProgramUniformFloatVec3(contextIdx, uniformUpVector, camera->getUpVector().getArray());
	//
	renderer->setTextureUnit(contextIdx, 0);
	renderer->bindTexture(contextIdx, starsTextureId);
	// sky
	renderer->setProgramUniformFloatVec3(contextIdx, uniformDayTopColor, engine->getShaderParameter("sky", "day_top_color").getVector3ValueArray());
	renderer->setProgramUniformFloatVec3(contextIdx, uniformDayBottomColor, engine->getShaderParameter("sky", "day_bottom_color").getVector3ValueArray());
	renderer->setProgramUniformFloatVec3(contextIdx, uniformSunsetTopColor, engine->getShaderParameter("sky", "sunset_top_color").getVector3ValueArray());
	renderer->setProgramUniformFloatVec3(contextIdx, uniformSunsetBottomColor, engine->getShaderParameter("sky", "sunset_bottom_color").getVector3ValueArray());
	renderer->setProgramUniformFloatVec3(contextIdx, uniformNightTopColor, engine->getShaderParameter("sky", "night_top_color").getVector3ValueArray());
	renderer->setProgramUniformFloatVec3(contextIdx, uniformNightBottomColor, engine->getShaderParameter("sky", "night_bottom_color").getVector3ValueArray());
	// horizon
	renderer->setProgramUniformFloatVec3(contextIdx, uniformHorizonColor, engine->getShaderParameter("sky", "horizon_color").getVector3ValueArray());
	renderer->setProgramUniformFloat(contextIdx, uniformHorizonBlur, engine->getShaderParameter("sky", "horizon_blur").getFloatValue());
	// sun
	renderer->setProgramUniformFloat(contextIdx, uniformSunColorFactor, engine->getShaderParameter("sky", "sun_color_factor").getFloatValue());
	renderer->setProgramUniformFloatVec3(contextIdx, uniformSunColor, engine->getShaderParameter("sky", "sun_color").getVector3ValueArray());
	renderer->setProgramUniformFloatVec3(contextIdx, uniformSunSunsetColor, engine->getShaderParameter("sky", "sun_sunset_color").getVector3ValueArray());
	renderer->setProgramUniformFloat(contextIdx, uniformSunSize, engine->getShaderParameter("sky", "sun_size").getFloatValue());
	renderer->setProgramUniformFloat(contextIdx, uniformSunBlur, engine->getShaderParameter("sky", "sun_blur").getFloatValue());
	// moon
	renderer->setProgramUniformFloat(contextIdx, uniformMoonColorFactor, engine->getShaderParameter("sky", "moon_color_factor").getFloatValue());
	renderer->setProgramUniformFloatVec3(contextIdx, uniformMoonColor, engine->getShaderParameter("sky", "moon_color").getVector3ValueArray());
	renderer->setProgramUniformFloat(contextIdx, uniformMoonSize, engine->getShaderParameter("sky", "moon_size").getFloatValue());
	renderer->setProgramUniformFloat(contextIdx, uniformMoonBlur, engine->getShaderParameter("sky", "moon_blur").getFloatValue());
	// clouds
	renderer->setProgramUniformFloatVec3(contextIdx, uniformCloudsEdgeColor, engine->getShaderParameter("sky", "clouds_edge_color").getVector3ValueArray());
	renderer->setProgramUniformFloatVec3(contextIdx, uniformCloudsTopColor, engine->getShaderParameter("sky", "clouds_top_color").getVector3ValueArray());
	renderer->setProgramUniformFloatVec3(contextIdx, uniformCloudsMiddleColor, engine->getShaderParameter("sky", "clouds_middle_color").getVector3ValueArray());
	renderer->setProgramUniformFloatVec3(contextIdx, uniformCloudsBottomColor, engine->getShaderParameter("sky", "clouds_bottom_color").getVector3ValueArray());
	renderer->setProgramUniformFloat(contextIdx, uniformCloudsSpeed, engine->getShaderParameter("sky", "clouds_speed").getFloatValue());
	renderer->setProgramUniformFloat(contextIdx, uniformCloudsDirection, engine->getShaderParameter("sky", "clouds_direction").getFloatValue());
	renderer->setProgramUniformFloat(contextIdx, uniformCloudsScale, engine->getShaderParameter("sky", "clouds_scale").getFloatValue());
	renderer->setProgramUniformFloat(contextIdx, uniformCloudsCutoff, engine->getShaderParameter("sky", "clouds_cutoff").getFloatValue());
	renderer->setProgramUniformFloat(contextIdx, uniformCloudsFuzziness, engine->getShaderParameter("sky", "clouds_fuzziness").getFloatValue());
	renderer->setProgramUniformFloat(contextIdx, uniformCloudsWeight, engine->getShaderParameter("sky", "clouds_weight").getFloatValue());
	renderer->setProgramUniformFloat(contextIdx, uniformCloudsBlur, engine->getShaderParameter("sky", "clouds_blur").getFloatValue());
	renderer->setProgramUniformFloat(contextIdx, uniformStarsSpeed, engine->getShaderParameter("sky", "stars_speed").getFloatValue());
	//
	renderer->disableDepthBufferWriting();
	renderer->disableDepthBufferTest();
	renderer->disableCulling(contextIdx);

	// use frame buffer render shader
	auto frameBufferRenderShader = Engine::getFrameBufferRenderShader();

	//
	renderer->bindVerticesBufferObject(contextIdx, frameBufferRenderShader->getVBOVertices());
	renderer->bindTextureCoordinatesBufferObject(contextIdx, frameBufferRenderShader->getVBOTextureCoordinates());

	// draw
	renderer->drawTrianglesFromBufferObjects(contextIdx, 2, 0);

	// unbind buffers
	renderer->unbindBufferObjects(contextIdx);

	//
	renderer->setTextureUnit(contextIdx, 0);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);

	// unset
	renderer->enableCulling(contextIdx);
	renderer->enableDepthBufferTest();
	renderer->enableDepthBufferWriting();
}
