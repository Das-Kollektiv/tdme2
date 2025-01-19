#include <tdme/engine/subsystems/framebuffer/FrameBufferRenderShader.h>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/subsystems/rendering/ObjectBuffer.h>
#include <tdme/engine/Engine.h>

#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/FloatBuffer.h>

using tdme::engine::subsystems::framebuffer::FrameBufferRenderShader;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::subsystems::rendering::ObjectBuffer;
using tdme::engine::Engine;
using tdme::utilities::ByteBuffer;
using tdme::utilities::FloatBuffer;

FrameBufferRenderShader::FrameBufferRenderShader(RendererBackend* rendererBackend)
{
	this->rendererBackend = rendererBackend;
	initialized = false;
	isRunning = false;
}

FrameBufferRenderShader::~FrameBufferRenderShader()
{
}

bool FrameBufferRenderShader::isInitialized()
{
	return initialized;
}

void FrameBufferRenderShader::initialize()
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
		"shader/" + shaderVersion + "/framebuffer",
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

	// uniforms
	uniformColorBufferTextureUnit = rendererBackend->getProgramUniformLocation(programId, "colorBufferTextureUnit");
	if (uniformColorBufferTextureUnit == -1) return;

	uniformDepthBufferTextureUnit = rendererBackend->getProgramUniformLocation(programId, "depthBufferTextureUnit");

	//
	auto contextIdx = rendererBackend->CONTEXTINDEX_DEFAULT;

	// create vbos
	auto created = false;
	auto vboManaged = Engine::getInstance()->getVBOManager()->addVBO("framebuffer_render_shader.vbos", 2, true, false, created);
	vboVertices = (*vboManaged->getVBOIds())[0];
	vboTextureCoordinates = (*vboManaged->getVBOIds())[1];

	// vertices
	{
		auto fbVertices = ObjectBuffer::getByteBuffer(contextIdx, 6 * 3 * sizeof(float))->asFloatBuffer();

		fbVertices.put(-1.0f); fbVertices.put(+1.0f); fbVertices.put(0.0f);
		fbVertices.put(+1.0f); fbVertices.put(+1.0f); fbVertices.put(0.0f);
		fbVertices.put(+1.0f); fbVertices.put(-1.0f); fbVertices.put(0.0f);

		fbVertices.put(+1.0f); fbVertices.put(-1.0f); fbVertices.put(0.0f);
		fbVertices.put(-1.0f); fbVertices.put(-1.0f); fbVertices.put(0.0f);
		fbVertices.put(-1.0f); fbVertices.put(+1.0f); fbVertices.put(0.0f);

		rendererBackend->uploadBufferObject(contextIdx, vboVertices, fbVertices.getPosition() * sizeof(float), &fbVertices);
	}

	// texture coordinates
	{
		auto fbTextureCoordinates = ObjectBuffer::getByteBuffer(contextIdx, 6 * 2 * sizeof(float))->asFloatBuffer();

		if (rendererBackend->getRendererType() == RendererBackend::RENDERERTYPE_VULKAN) {
			fbTextureCoordinates.put(+0.0f); fbTextureCoordinates.put(0.0f);
			fbTextureCoordinates.put(+1.0f); fbTextureCoordinates.put(0.0f);
			fbTextureCoordinates.put(+1.0f); fbTextureCoordinates.put(1.0f);

			fbTextureCoordinates.put(+1.0f); fbTextureCoordinates.put(1.0f);
			fbTextureCoordinates.put(+0.0f); fbTextureCoordinates.put(1.0f);
			fbTextureCoordinates.put(+0.0f); fbTextureCoordinates.put(0.0f);
		} else {
			fbTextureCoordinates.put(+0.0f); fbTextureCoordinates.put(+1.0f);
			fbTextureCoordinates.put(+1.0f); fbTextureCoordinates.put(+1.0f);
			fbTextureCoordinates.put(+1.0f); fbTextureCoordinates.put(0.0f);

			fbTextureCoordinates.put(+1.0f); fbTextureCoordinates.put(0.0f);
			fbTextureCoordinates.put(+0.0f); fbTextureCoordinates.put(0.0f);
			fbTextureCoordinates.put(+0.0f); fbTextureCoordinates.put(+1.0f);
		}

		rendererBackend->uploadBufferObject(contextIdx, vboTextureCoordinates, fbTextureCoordinates.getPosition() * sizeof(float), &fbTextureCoordinates);
	}

	//
	initialized = true;
}

void FrameBufferRenderShader::dispose()
{
	Engine::getInstance()->getVBOManager()->removeVBO("framebuffer_render_shader.vbos");
}

void FrameBufferRenderShader::useProgram()
{
	auto contextIdx = rendererBackend->CONTEXTINDEX_DEFAULT;
	rendererBackend->useProgram(contextIdx, programId);
	rendererBackend->setLighting(contextIdx, rendererBackend->LIGHTING_NONE);
	rendererBackend->setProgramUniformInteger(contextIdx, uniformColorBufferTextureUnit, 0);
	if (uniformDepthBufferTextureUnit != -1) rendererBackend->setProgramUniformInteger(contextIdx, uniformDepthBufferTextureUnit, 1);
	isRunning = true;
}

void FrameBufferRenderShader::unUseProgram()
{
	isRunning = false;
}
