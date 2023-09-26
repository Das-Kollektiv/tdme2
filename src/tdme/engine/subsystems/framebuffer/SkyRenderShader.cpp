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
	cloudsFrameBuffer = make_unique<FrameBuffer>(2048, 2048, FrameBuffer::FRAMEBUFFER_COLORBUFFER);
	cloudsFrameBuffer->initialize();

	//
	initialized = true;

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
		"render_sky_fragmentshader.frag"
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
}

void SkyRenderShader::dispose() {
	unloadTextures();
	cloudsFrameBuffer->dispose();
}

void SkyRenderShader::unloadTextures() {
	if (cloudsNoiseTexture != nullptr) {
		Engine::getInstance()->getTextureManager()->removeTexture(cloudsNoiseTexture->getId());
		cloudsNoiseTexture->releaseReference();
		cloudsNoiseTexture = nullptr;
		cloudNoiseTextureId = renderer->ID_NONE;
	}
}

void SkyRenderShader::loadTextures(const string& pathName) {
	cloudNoiseTextureId = Engine::getInstance()->getTextureManager()->addTexture(cloudsNoiseTexture = TextureReader::read(pathName + "/resources/engine/textures", "noise.png"), renderer->CONTEXTINDEX_DEFAULT);
}


void SkyRenderShader::prepare(Engine* engine) {
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

void SkyRenderShader::render(Engine* engine) {
	// use default context
	auto contextIdx = renderer->CONTEXTINDEX_DEFAULT;

	//
	renderer->useProgram(contextIdx, renderProgramId);
	renderer->setLighting(contextIdx, renderer->LIGHTING_NONE);

	//
	renderer->setTextureUnit(contextIdx, 0);
	renderer->bindTexture(contextIdx, cloudsFrameBuffer->getColorBufferTextureId());
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
