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
	uniformTime = renderer->getProgramUniformLocation(programId, "time");
	if (uniformTime == -1) return;
	uniformSideVector = renderer->getProgramUniformLocation(programId, "sideVector");
	if (uniformSideVector == -1) return;
	uniformUpVector = renderer->getProgramUniformLocation(programId, "upVector");
	if (uniformUpVector == -1) return;
	uniformForwardVector = renderer->getProgramUniformLocation(programId, "forwardVector");
	if (uniformForwardVector == -1) return;

	//
	loadTextures(".");

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
	starsTextureId = Engine::getInstance()->getTextureManager()->addTexture(starsTexture = TextureReader::read(pathName + "/resources/engine/textures", "starfield.png"), renderer->CONTEXTINDEX_DEFAULT);
}

void SkyRenderShader::render(Engine* engine) {
	// use default context
	auto contextIdx = renderer->CONTEXTINDEX_DEFAULT;

	//
	renderer->useProgram(contextIdx, programId);
	renderer->setLighting(contextIdx, renderer->LIGHTING_NONE);

	//
	auto light0 = engine->getLightAt(0);
	auto light1 = engine->getLightAt(0);
	//
	renderer->setProgramUniformInteger(contextIdx, uniformLIGHT0_ENABLED, light0->isEnabled() == true?1:0);
	renderer->setProgramUniformFloatVec3(contextIdx, uniformLIGHT0_DIRECTION, light0->getSpotDirection().getArray());
	renderer->setProgramUniformInteger(contextIdx, uniformLIGHT1_ENABLED, light1->isEnabled() == true?1:0);
	renderer->setProgramUniformFloatVec3(contextIdx, uniformLIGHT1_DIRECTION, light1->getSpotDirection().getArray());
	renderer->setProgramUniformFloat(contextIdx, uniformTime, static_cast<float>(engine->getTiming()->getTotalTime()) / 1000.0f);
	renderer->setProgramUniformFloatVec3(contextIdx, uniformSideVector, engine->getCamera()->getSideVector().getArray());
	renderer->setProgramUniformFloatVec3(contextIdx, uniformUpVector, engine->getCamera()->getUpVector().getArray());
	renderer->setProgramUniformFloatVec3(contextIdx, uniformForwardVector, engine->getCamera()->getForwardVector().getArray());
	//
	renderer->setTextureUnit(contextIdx, 0);
	renderer->bindTexture(contextIdx, starsTextureId);
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
