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
	cloudsVertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/framebuffer",
		"render_vertexshader.vert"
	);
	if (cloudsVertexShaderId == 0) return;

	cloudsFragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/framebuffer/sky",
		"render_clouds_fragmentshader.frag"
	);
	if (cloudsFragmentShaderId == 0) return;

	cloudsProgramId = renderer->createProgram(renderer->PROGRAM_OBJECTS);
	renderer->attachShaderToProgram(cloudsProgramId, cloudsVertexShaderId);
	renderer->attachShaderToProgram(cloudsProgramId, cloudsFragmentShaderId);
	if (renderer->isUsingProgramAttributeLocation() == true) {
		renderer->setProgramAttributeLocation(cloudsProgramId, 0, "inVertex");
		renderer->setProgramAttributeLocation(cloudsProgramId, 2, "inTextureUV");
	}
	if (renderer->linkProgram(cloudsProgramId) == false) return;

	cloudUniformSunPosition = renderer->getProgramUniformLocation(cloudsProgramId, "SUN_POS");
	if (cloudUniformSunPosition == -1) return;
	cloudsUniformWind = renderer->getProgramUniformLocation(cloudsProgramId, "WIND");
	if (cloudsUniformWind == -1) return;
	cloudsUniformSize = renderer->getProgramUniformLocation(cloudsProgramId, "SIZE");
	if (cloudsUniformSize == -1) return;
	cloudsUniformSoftness = renderer->getProgramUniformLocation(cloudsProgramId, "SOFTNESS");
	if (cloudsUniformSoftness == -1) return;
	cloudsUniformCoverage = renderer->getProgramUniformLocation(cloudsProgramId, "COVERAGE");
	if (cloudsUniformCoverage == -1) return;
	cloudsUniformHeight = renderer->getProgramUniformLocation(cloudsProgramId, "HEIGHT");
	if (cloudsUniformHeight == -1) return;
	cloudsUniformThickness = renderer->getProgramUniformLocation(cloudsProgramId, "THICKNESS");
	if (cloudsUniformThickness == -1) return;
	cloudsUniformAbsorption = renderer->getProgramUniformLocation(cloudsProgramId, "ABSORPTION");
	if (cloudsUniformAbsorption == -1) return;
	cloudsUniformSteps = renderer->getProgramUniformLocation(cloudsProgramId, "STEPS");
	if (cloudsUniformSteps == -1) return;

	//
	cloudsUniformTime  = renderer->getProgramUniformLocation(cloudsProgramId, "TIME");
	if (cloudsUniformTime == -1) return;
	cloudsUniformNoise = renderer->getProgramUniformLocation(cloudsProgramId, "Noise");
	if (cloudsUniformNoise == -1) return;

	//
	cloudsFrameBuffer = make_unique<FrameBuffer>(4096, 4096, FrameBuffer::FRAMEBUFFER_COLORBUFFER);
	cloudsFrameBuffer->initialize();

	//
	skyVertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/framebuffer",
		"render_vertexshader.vert"
	);
	if (cloudsVertexShaderId == 0) return;

	skyFragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/framebuffer/sky",
		"render_sky_fragmentshader.frag"
	);
	if (skyFragmentShaderId == 0) return;

	skyProgramId = renderer->createProgram(renderer->PROGRAM_OBJECTS);
	renderer->attachShaderToProgram(skyProgramId, skyVertexShaderId);
	renderer->attachShaderToProgram(skyProgramId, skyFragmentShaderId);
	if (renderer->isUsingProgramAttributeLocation() == true) {
		renderer->setProgramAttributeLocation(skyProgramId, 0, "inVertex");
		renderer->setProgramAttributeLocation(skyProgramId, 2, "inTextureUV");
	}
	if (renderer->linkProgram(skyProgramId) == false) return;

	//
	skyUniformTime = renderer->getProgramUniformLocation(skyProgramId, "TIME");
	if (skyUniformTime == -1) return;
	skyUniformMoon = renderer->getProgramUniformLocation(skyProgramId, "MOON");
	if (skyUniformMoon == -1) return;
	skyUniformCloudEnvironment = renderer->getProgramUniformLocation(skyProgramId, "cloud_env_texture");
	if (skyUniformCloudEnvironment == -1) return;
	skyUniformSunPosition = renderer->getProgramUniformLocation(skyProgramId, "SUN_POS");
	if (skyUniformSunPosition == -1) return;
	skyUniformMoonPosition = renderer->getProgramUniformLocation(skyProgramId, "MOON_POS");
	if (skyUniformMoonPosition == -1) return;
	skyUniformMoonTexturePosition = renderer->getProgramUniformLocation(skyProgramId, "MOON_TEX_POS");
	if (skyUniformMoonTexturePosition == -1) return;
	skyUniformMoonPhase = renderer->getProgramUniformLocation(skyProgramId, "MOON_PHASE");
	if (skyUniformMoonPhase == -1) return;
	skyUniformMoonRadius = renderer->getProgramUniformLocation(skyProgramId, "moon_radius");
	if (skyUniformMoonRadius == -1) return;
	skyUniformSunRadius = renderer->getProgramUniformLocation(skyProgramId, "sun_radius");
	if (skyUniformSunRadius == -1) return;
	skyUniformAttenuation = renderer->getProgramUniformLocation(skyProgramId, "attenuation");
	if (skyUniformAttenuation == -1) return;
	skyUniformTone = renderer->getProgramUniformLocation(skyProgramId, "sky_tone");
	if (skyUniformTone == -1) return;
	skyUniformDensity = renderer->getProgramUniformLocation(skyProgramId, "sky_density");
	if (skyUniformDensity == -1) return;
	skyUniformRayleigCoeff = renderer->getProgramUniformLocation(skyProgramId, "sky_rayleig_coeff");
	if (skyUniformRayleigCoeff == -1) return;
	skyUniformMieCoeff = renderer->getProgramUniformLocation(skyProgramId, "sky_mie_coeff");
	if (skyUniformMieCoeff == -1) return;
	skyUniformMultiScatterPhase = renderer->getProgramUniformLocation(skyProgramId, "multiScatterPhase");
	if (skyUniformMultiScatterPhase == -1) return;
	skyUniformAnisotropicIntensity = renderer->getProgramUniformLocation(skyProgramId, "anisotropicIntensity");
	if (skyUniformAnisotropicIntensity == -1) return;
	skyUniformColorSky = renderer->getProgramUniformLocation(skyProgramId, "color_sky");
	if (skyUniformColorSky == -1) return;
	skyUniformMoonTint = renderer->getProgramUniformLocation(skyProgramId, "moon_tint");
	if (skyUniformMoonTint == -1) return;
	skyUniformCloudsTint = renderer->getProgramUniformLocation(skyProgramId, "clouds_tint");
	if (skyUniformCloudsTint == -1) return;

	//
	skyFrameBuffer = make_unique<FrameBuffer>(4096, 4096, FrameBuffer::FRAMEBUFFER_COLORBUFFER);
	skyFrameBuffer->initialize();

	//
	renderVertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/framebuffer",
		"render_vertexshader.vert"
	);
	if (renderVertexShaderId == 0) return;

	renderFragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/framebuffer/sky",
		"render_fragmentshader.frag"
	);
	if (renderFragmentShaderId == 0) return;

	renderProgramId = renderer->createProgram(renderer->PROGRAM_OBJECTS);
	renderer->attachShaderToProgram(renderProgramId, renderVertexShaderId);
	renderer->attachShaderToProgram(renderProgramId, renderFragmentShaderId);
	if (renderer->isUsingProgramAttributeLocation() == true) {
		renderer->setProgramAttributeLocation(renderProgramId, 0, "inVertex");
		renderer->setProgramAttributeLocation(renderProgramId, 2, "inTextureUV");
	}
	if (renderer->linkProgram(renderProgramId) == false) return;

	//
	renderUniformSampler = renderer->getProgramUniformLocation(renderProgramId, "sampler");
	if (renderUniformSampler == -1) return;
	renderUniformSideVector = renderer->getProgramUniformLocation(renderProgramId, "sideVector");
	if (renderUniformSideVector == -1) return;
	renderUniformUpVector = renderer->getProgramUniformLocation(renderProgramId, "upVector");
	if (renderUniformUpVector == -1) return;
	renderUniformForwardVector = renderer->getProgramUniformLocation(renderProgramId, "forwardVector");
	if (renderUniformForwardVector == -1) return;

	//
	loadTextures(".");

	//
	initialized = true;
}

void SkyRenderShader::dispose() {
	unloadTextures();
	cloudsFrameBuffer->dispose();
	skyFrameBuffer->dispose();
}

void SkyRenderShader::unloadTextures() {
	if (cloudsNoiseTexture != nullptr) {
		Engine::getInstance()->getTextureManager()->removeTexture(cloudsNoiseTexture);
		cloudsNoiseTexture->releaseReference();
		cloudsNoiseTexture = nullptr;
		cloudNoiseTextureId = renderer->ID_NONE;
	}
	if (skyMoonTexture != nullptr) {
		Engine::getInstance()->getTextureManager()->removeTexture(skyMoonTexture);
		skyMoonTexture->releaseReference();
		skyMoonTexture = nullptr;
		skyMoonTextureId = renderer->ID_NONE;
	}
}

void SkyRenderShader::loadTextures(const string& pathName) {
	cloudNoiseTextureId = Engine::getInstance()->getTextureManager()->addTexture(cloudsNoiseTexture = TextureReader::read(pathName + "/resources/engine/textures", "noise.png"), renderer->CONTEXTINDEX_DEFAULT);
	skyMoonTextureId = Engine::getInstance()->getTextureManager()->addTexture(skyMoonTexture = TextureReader::read(pathName + "/resources/engine/textures", "moon.png"), renderer->CONTEXTINDEX_DEFAULT);
}


void SkyRenderShader::prepareClouds(Engine* engine) {
	// use default context
	auto contextIdx = renderer->CONTEXTINDEX_DEFAULT;

	//
	cloudsFrameBuffer->enableFrameBuffer();

	//
	renderer->useProgram(contextIdx, cloudsProgramId);
	renderer->setLighting(contextIdx, renderer->LIGHTING_NONE);

	//
	renderer->setTextureUnit(contextIdx, 0);
	renderer->bindTexture(contextIdx, cloudNoiseTextureId);
	renderer->setProgramUniformInteger(contextIdx, cloudsUniformNoise, 0);
	renderer->setProgramUniformFloatVec3(contextIdx, cloudUniformSunPosition, { 0.0f, -1.0f, 0.0});
	renderer->setProgramUniformFloatVec3(contextIdx, cloudsUniformWind, { 0.01f, 0.0f, 0.0f});
	renderer->setProgramUniformFloat(contextIdx, cloudsUniformSize, 0.5f);
	renderer->setProgramUniformFloat(contextIdx, cloudsUniformSoftness, 5.0f);
	renderer->setProgramUniformFloat(contextIdx, cloudsUniformCoverage, 0.5f);
	renderer->setProgramUniformFloat(contextIdx, cloudsUniformHeight, 0.0f);
	renderer->setProgramUniformFloat(contextIdx, cloudsUniformThickness, 0.5f);
	renderer->setProgramUniformFloat(contextIdx, cloudsUniformAbsorption, 1.030725f);
	renderer->setProgramUniformInteger(contextIdx, cloudsUniformSteps, 25);
	renderer->setProgramUniformFloat(contextIdx, cloudsUniformTime, static_cast<float>(engine->getTiming()->getTotalTime()) / 1000.0f);

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

	//
	renderer->bindTexture(contextIdx, renderer->ID_NONE);

	// unbind buffers
	renderer->unbindBufferObjects(contextIdx);

	// unset
	renderer->enableCulling(contextIdx);
	renderer->enableDepthBufferTest();
	renderer->enableDepthBufferWriting();

	//
	cloudsFrameBuffer->disableFrameBuffer();
}

void SkyRenderShader::prepareSky(Engine* engine) {
	// use default context
	auto contextIdx = renderer->CONTEXTINDEX_DEFAULT;

	//
	skyFrameBuffer->enableFrameBuffer();

	//
	renderer->useProgram(contextIdx, skyProgramId);
	renderer->setLighting(contextIdx, renderer->LIGHTING_NONE);

	//
	renderer->setTextureUnit(contextIdx, 0);
	renderer->bindTexture(contextIdx, skyMoonTextureId);
	renderer->setTextureUnit(contextIdx, 1);
	renderer->bindTexture(contextIdx, cloudsFrameBuffer->getColorTextureId());

	//
	renderer->setProgramUniformFloat(contextIdx, skyUniformTime, 0.25f);
	renderer->setProgramUniformInteger(contextIdx, skyUniformMoon, 0);
	renderer->setProgramUniformInteger(contextIdx, skyUniformCloudEnvironment, 1);
	renderer->setProgramUniformFloatVec3(contextIdx, skyUniformSunPosition, { 0.0f, 1.0f, 0.0f });
	renderer->setProgramUniformFloatVec3(contextIdx, skyUniformMoonPosition, { 0.0f, -1.0f, 0.0f });
	renderer->setProgramUniformFloatVec3(contextIdx, skyUniformMoonTexturePosition, { 0.0f, -1.0f, 0.0f });
	renderer->setProgramUniformFloat(contextIdx, skyUniformMoonPhase, -1.0f);
	renderer->setProgramUniformFloat(contextIdx, skyUniformMoonRadius, 0.05f);
	renderer->setProgramUniformFloat(contextIdx, skyUniformSunRadius, 0.04f);
	renderer->setProgramUniformFloat(contextIdx, skyUniformAttenuation, 1.0f);
	renderer->setProgramUniformFloat(contextIdx, skyUniformTone, 3.5f);
	renderer->setProgramUniformFloat(contextIdx, skyUniformDensity, 0.5f);
	renderer->setProgramUniformFloat(contextIdx, skyUniformRayleigCoeff, 1.0f);
	renderer->setProgramUniformFloat(contextIdx, skyUniformMieCoeff, 0.5f);
	renderer->setProgramUniformFloat(contextIdx, skyUniformMultiScatterPhase, 0.0f);
	renderer->setProgramUniformFloat(contextIdx, skyUniformAnisotropicIntensity, 1.5f);
	renderer->setProgramUniformFloatVec4(contextIdx, skyUniformColorSky, { 0.156863f, 0.392157f, 1.0f, 1.0f });
	renderer->setProgramUniformFloatVec4(contextIdx, skyUniformMoonTint, { 1.0f, 0.7f, 0.35f, 1.0f });
	renderer->setProgramUniformFloatVec4(contextIdx, skyUniformCloudsTint, { 0.8f, 0.8f, 0.8f, 0.50f });

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
	renderer->setTextureUnit(contextIdx, 1);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);
	renderer->setTextureUnit(contextIdx, 0);
	renderer->bindTexture(contextIdx, renderer->ID_NONE);

	// unset
	renderer->enableCulling(contextIdx);
	renderer->enableDepthBufferTest();
	renderer->enableDepthBufferWriting();

	//
	skyFrameBuffer->disableFrameBuffer();
}

void SkyRenderShader::render(Engine* engine) {
	// use default context
	auto contextIdx = renderer->CONTEXTINDEX_DEFAULT;

	//
	renderer->useProgram(contextIdx, renderProgramId);
	renderer->setLighting(contextIdx, renderer->LIGHTING_NONE);

	//
	renderer->setTextureUnit(contextIdx, 0);
	renderer->bindTexture(contextIdx, skyFrameBuffer->getColorBufferTextureId());
	renderer->setProgramUniformInteger(contextIdx, renderUniformSampler, 0);
	renderer->setProgramUniformFloatVec3(contextIdx, renderUniformSideVector, engine->getCamera()->getSideVector().getArray());
	renderer->setProgramUniformFloatVec3(contextIdx, renderUniformUpVector, engine->getCamera()->getUpVector().getArray());
	renderer->setProgramUniformFloatVec3(contextIdx, renderUniformForwardVector, engine->getCamera()->getForwardVector().getArray());

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

	//
	renderer->bindTexture(contextIdx, renderer->ID_NONE);

	// unbind buffers
	renderer->unbindBufferObjects(contextIdx);

	// unset
	renderer->enableCulling(contextIdx);
	renderer->enableDepthBufferTest();
	renderer->enableDepthBufferWriting();
}
