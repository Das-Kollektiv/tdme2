#include <tdme/engine/subsystems/framebuffer/FrameBufferRenderShader.h>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/subsystems/rendering/ObjectBuffer.h>
#include <tdme/engine/Engine.h>

#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/FloatBuffer.h>

using tdme::engine::subsystems::framebuffer::FrameBufferRenderShader;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::rendering::ObjectBuffer;
using tdme::engine::Engine;
using tdme::utilities::ByteBuffer;
using tdme::utilities::FloatBuffer;

FrameBufferRenderShader::FrameBufferRenderShader(Renderer* renderer)
{
	this->renderer = renderer;
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
	auto shaderVersion = renderer->getShaderVersion();
	vertexShaderId = renderer->loadShader(
		renderer->SHADER_VERTEX_SHADER,
		"shader/" + shaderVersion + "/framebuffer",
		"render_vertexshader.vert"
	);
	if (vertexShaderId == 0) return;

	fragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/framebuffer",
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

	// uniforms
	uniformColorBufferTextureUnit = renderer->getProgramUniformLocation(programId, "colorBufferTextureUnit");
	if (uniformColorBufferTextureUnit == -1) return;

	uniformDepthBufferTextureUnit = renderer->getProgramUniformLocation(programId, "depthBufferTextureUnit");

	//
	auto contextIdx = renderer->CONTEXTINDEX_DEFAULT;

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

		renderer->uploadBufferObject(contextIdx, vboVertices, fbVertices.getPosition() * sizeof(float), &fbVertices);
	}

	// texture coordinates
	{
		auto fbTextureCoordinates = ObjectBuffer::getByteBuffer(contextIdx, 6 * 2 * sizeof(float))->asFloatBuffer();

		if (renderer->getRendererType() == Renderer::RENDERERTYPE_VULKAN) {
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

		renderer->uploadBufferObject(contextIdx, vboTextureCoordinates, fbTextureCoordinates.getPosition() * sizeof(float), &fbTextureCoordinates);
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
	auto contextIdx = renderer->CONTEXTINDEX_DEFAULT;
	renderer->useProgram(contextIdx, programId);
	renderer->setLighting(contextIdx, renderer->LIGHTING_NONE);
	renderer->setProgramUniformInteger(contextIdx, uniformColorBufferTextureUnit, 0);
	if (uniformDepthBufferTextureUnit != -1) renderer->setProgramUniformInteger(contextIdx, uniformDepthBufferTextureUnit, 1);
	isRunning = true;
}

void FrameBufferRenderShader::unUseProgram()
{
	isRunning = false;
}
