#include <tdme/engine/subsystems/framebuffer/BRDFLUTShader.h>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/framebuffer/FrameBufferRenderShader.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/Engine.h>

using tdme::engine::subsystems::framebuffer::BRDFLUTShader;

using tdme::engine::subsystems::framebuffer::FrameBufferRenderShader;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Engine;

BRDFLUTShader::BRDFLUTShader(RendererBackend* rendererBackend)
{
	this->rendererBackend = rendererBackend;
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
	auto shaderVersion = rendererBackend->getShaderVersion();
	vertexShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/framebuffer",
		"render_vertexshader.vert"
	);
	if (vertexShaderId == 0) return;

	fragmentShaderId = rendererBackend->loadShader(
		rendererBackend->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/framebuffer/brdflut",
		"render_brdflut_fragmentshader.frag"
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
	colorBufferTextureId = rendererBackend->createGBufferGeometryTexture(BRDFLUT_WIDTH, BRDFLUT_HEIGHT);
	frameBufferId = rendererBackend->createFramebufferObject(rendererBackend->ID_NONE, colorBufferTextureId, rendererBackend->ID_NONE, rendererBackend->ID_NONE);

	//
	initialized = true;
}

void BRDFLUTShader::generate() {
	// use default context
	auto contextIdx = rendererBackend->CONTEXTINDEX_DEFAULT;

	//
	rendererBackend->bindFrameBuffer(frameBufferId);
	rendererBackend->setViewPort(BRDFLUT_WIDTH, BRDFLUT_HEIGHT);
	rendererBackend->updateViewPort();

	//
	rendererBackend->useProgram(contextIdx, programId);
	rendererBackend->setLighting(contextIdx, rendererBackend->LIGHTING_NONE);

	//
	rendererBackend->disableDepthBufferWriting();
	rendererBackend->disableDepthBufferTest();
	rendererBackend->disableCulling(contextIdx);

	// clear
	rendererBackend->setClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	rendererBackend->clear(rendererBackend->CLEAR_COLOR_BUFFER_BIT);

	// use frame buffer render shader
	auto frameBufferRenderShader = Engine::getFrameBufferRenderShader();

	//
	rendererBackend->bindVerticesBufferObject(contextIdx, frameBufferRenderShader->getVBOVertices());
	rendererBackend->bindTextureCoordinatesBufferObject(contextIdx, frameBufferRenderShader->getVBOTextureCoordinates());

	// draw
	rendererBackend->drawTrianglesFromBufferObjects(contextIdx, 2, 0);

	// unbind buffers
	rendererBackend->unbindBufferObjects(contextIdx);

	// unset
	rendererBackend->enableCulling(contextIdx);
	rendererBackend->enableDepthBufferTest();
	rendererBackend->enableDepthBufferWriting();

	//
	rendererBackend->bindFrameBuffer(Engine::getRendererBackend()->FRAMEBUFFER_DEFAULT);
	rendererBackend->setViewPort(Engine::instance->width, Engine::instance->height);
	rendererBackend->updateViewPort();
}
