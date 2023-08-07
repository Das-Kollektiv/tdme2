#include <tdme/engine/subsystems/framebuffer/BRDFLUTShader.h>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/framebuffer/FrameBufferRenderShader.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/Engine.h>

using tdme::engine::subsystems::framebuffer::BRDFLUTShader;

using tdme::engine::subsystems::framebuffer::FrameBufferRenderShader;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;

BRDFLUTShader::BRDFLUTShader(Renderer* renderer)
{
	this->renderer = renderer;
}

BRDFLUTShader::~BRDFLUTShader()
{
}

bool BRDFLUTShader::isInitialized()
{
	return initialized;
}

void BRDFLUTShader::initialize()
{
	auto shaderVersion = renderer->getShaderVersion();
	vertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/framebuffer",
		"render_vertexshader.vert"
	);
	if (vertexShaderId == 0) return;

	fragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/framebuffer/brdflut",
		"render_brdflut_fragmentshader.frag"
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
	colorBufferTextureId = renderer->createGBufferGeometryTexture(BRDFLUT_WIDTH, BRDFLUT_HEIGHT);
	frameBufferId = renderer->createFramebufferObject(renderer->ID_NONE, colorBufferTextureId, renderer->ID_NONE, renderer->ID_NONE);

	//
	initialized = true;
}

void BRDFLUTShader::generate() {
	// use default context
	auto contextIdx = renderer->CONTEXTINDEX_DEFAULT;

	//
	renderer->bindFrameBuffer(frameBufferId);
	renderer->setViewPort(BRDFLUT_WIDTH, BRDFLUT_HEIGHT);
	renderer->updateViewPort();

	//
	renderer->useProgram(contextIdx, programId);
	renderer->setLighting(contextIdx, renderer->LIGHTING_NONE);

	//
	renderer->disableDepthBufferWriting();
	renderer->disableDepthBufferTest();
	renderer->disableCulling(contextIdx);

	// clear
	renderer->setClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	renderer->clear(renderer->CLEAR_COLOR_BUFFER_BIT);

	// use frame buffer render shader
	auto frameBufferRenderShader = Engine::getFrameBufferRenderShader();

	//
	renderer->bindVerticesBufferObject(contextIdx, frameBufferRenderShader->getVBOVertices());
	renderer->bindTextureCoordinatesBufferObject(contextIdx, frameBufferRenderShader->getVBOTextureCoordinates());

	// draw
	renderer->drawTrianglesFromBufferObjects(contextIdx, 2, 0);

	// unbind buffers
	renderer->unbindBufferObjects(contextIdx);

	// unset
	renderer->enableCulling(contextIdx);
	renderer->enableDepthBufferTest();
	renderer->enableDepthBufferWriting();

	//
	renderer->bindFrameBuffer(Engine::getRenderer()->FRAMEBUFFER_DEFAULT);
	renderer->setViewPort(Engine::instance->width, Engine::instance->height);
	renderer->updateViewPort();
}
