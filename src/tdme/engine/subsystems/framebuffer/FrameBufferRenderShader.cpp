#include <tdme/engine/subsystems/framebuffer/FrameBufferRenderShader.h>

#include <tdme/engine/Engine.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/subsystems/rendering/ObjectBuffer.h>
#include <tdme/engine/subsystems/manager/VBOManager.h>
#include <tdme/engine/subsystems/manager/VBOManager_VBOManaged.h>

#include <tdme/utils/ByteBuffer.h>
#include <tdme/utils/FloatBuffer.h>

using tdme::engine::Engine;
using tdme::engine::subsystems::framebuffer::FrameBufferRenderShader;
using tdme::engine::subsystems::manager::VBOManager;
using tdme::engine::subsystems::manager::VBOManager_VBOManaged;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::subsystems::rendering::ObjectBuffer;
using tdme::utils::ByteBuffer;
using tdme::utils::FloatBuffer;

FrameBufferRenderShader::FrameBufferRenderShader(Renderer* renderer)
{
	this->renderer = renderer;
	initialized = false;
	isRunning = false;
}

FrameBufferRenderShader::~FrameBufferRenderShader()
{
	Engine::getInstance()->getVBOManager()->removeVBO("framebuffer_render_shader.vbos");
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
		"render_vertexshader.c"
	);
	if (vertexShaderId == 0)
		return;

	fragmentShaderId = renderer->loadShader(
		renderer->SHADER_FRAGMENT_SHADER,
		"shader/" + shaderVersion + "/framebuffer",
		"render_fragmentshader.c"
	);
	if (fragmentShaderId == 0)
		return;

	programId = renderer->createProgram();
	renderer->attachShaderToProgram(programId, vertexShaderId);
	renderer->attachShaderToProgram(programId, fragmentShaderId);
	if (renderer->isUsingProgramAttributeLocation() == true) {
		renderer->setProgramAttributeLocation(programId, 0, "inVertex");
		renderer->setProgramAttributeLocation(programId, 2, "inTextureUV");
	}
	if (renderer->linkProgram(programId) == false)
		return;

	// uniforms
	uniformColorBufferTextureUnit = renderer->getProgramUniformLocation(programId, "colorBufferTextureUnit");
	if (uniformColorBufferTextureUnit == -1) return;

	uniformDepthBufferTextureUnit = renderer->getProgramUniformLocation(programId, "depthBufferTextureUnit");
	if (uniformDepthBufferTextureUnit == -1) return;

	//
	auto context = renderer->getDefaultContext();

	// create vbos
	auto vboManaged = Engine::getInstance()->getVBOManager()->addVBO("framebuffer_render_shader.vbos", 2, true);
	vboVertices = (*vboManaged->getVBOIds())[0];
	vboTextureCoordinates = (*vboManaged->getVBOIds())[1];

	// vertices
	{
		auto fbVertices = ObjectBuffer::getByteBuffer(context, 6 * 3 * sizeof(float))->asFloatBuffer();

		fbVertices.put(-1.0f); fbVertices.put(+1.0f); fbVertices.put(0.0f);
		fbVertices.put(+1.0f); fbVertices.put(+1.0f); fbVertices.put(0.0f);
		fbVertices.put(+1.0f); fbVertices.put(-1.0f); fbVertices.put(0.0f);

		fbVertices.put(+1.0f); fbVertices.put(-1.0f); fbVertices.put(0.0f);
		fbVertices.put(-1.0f); fbVertices.put(-1.0f); fbVertices.put(0.0f);
		fbVertices.put(-1.0f); fbVertices.put(+1.0f); fbVertices.put(0.0f);

		renderer->uploadBufferObject(context, vboVertices, fbVertices.getPosition() * sizeof(float), &fbVertices);
	}

	// texture coordinates
	{
		auto fbTextureCoordinates = ObjectBuffer::getByteBuffer(context, 6 * 2 * sizeof(float))->asFloatBuffer();

		#if defined(VULKAN)
			fbTextureCoordinates.put(+0.0f); fbTextureCoordinates.put(0.0f);
			fbTextureCoordinates.put(+1.0f); fbTextureCoordinates.put(0.0f);
			fbTextureCoordinates.put(+1.0f); fbTextureCoordinates.put(1.0f);

			fbTextureCoordinates.put(+1.0f); fbTextureCoordinates.put(1.0f);
			fbTextureCoordinates.put(+0.0f); fbTextureCoordinates.put(1.0f);
			fbTextureCoordinates.put(+0.0f); fbTextureCoordinates.put(0.0f);
		#else
			fbTextureCoordinates.put(+0.0f); fbTextureCoordinates.put(+1.0f);
			fbTextureCoordinates.put(+1.0f); fbTextureCoordinates.put(+1.0f);
			fbTextureCoordinates.put(+1.0f); fbTextureCoordinates.put(0.0f);

			fbTextureCoordinates.put(+1.0f); fbTextureCoordinates.put(0.0f);
			fbTextureCoordinates.put(+0.0f); fbTextureCoordinates.put(0.0f);
			fbTextureCoordinates.put(+0.0f); fbTextureCoordinates.put(+1.0f);
		#endif

		renderer->uploadBufferObject(context, vboTextureCoordinates, fbTextureCoordinates.getPosition() * sizeof(float), &fbTextureCoordinates);
	}

	//
	initialized = true;
}

void FrameBufferRenderShader::useProgram()
{
	renderer->useProgram(programId);
	auto context = renderer->getDefaultContext();
	renderer->setProgramUniformInteger(context, uniformColorBufferTextureUnit, 0);
	renderer->setProgramUniformInteger(context, uniformDepthBufferTextureUnit, 1);
	isRunning = true;
}

void FrameBufferRenderShader::unUseProgram()
{
	isRunning = false;
}
