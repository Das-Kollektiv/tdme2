#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>

using std::string;

using tdme::engine::subsystems::postprocessing::PostProcessingShaderBaseImplementation;
using tdme::engine::subsystems::renderer::Renderer;
using tdme::engine::Engine;

PostProcessingShaderBaseImplementation::PostProcessingShaderBaseImplementation(Renderer* renderer)
{
	this->renderer = renderer;
	isRunning = false;
	initialized = false;
}

bool PostProcessingShaderBaseImplementation::isInitialized()
{
	return initialized;
}

void PostProcessingShaderBaseImplementation::initialize()
{
	// map inputs to attributes
	if (renderer->isUsingProgramAttributeLocation() == true) {
		renderer->setProgramAttributeLocation(programId, 0, "inVertex");
		renderer->setProgramAttributeLocation(programId, 2, "inTextureUV");
	}

	if (renderer->linkProgram(programId) == false)
		return;

	// uniforms
	uniformColorBufferTextureUnit = renderer->getProgramUniformLocation(programId, "colorBufferTextureUnit");
	uniformDepthBufferTextureUnit = renderer->getProgramUniformLocation(programId, "depthBufferTextureUnit");
	uniformTemporaryColorBufferTextureUnit = renderer->getProgramUniformLocation(programId, "temporaryColorBufferTextureUnit");
	uniformTemporaryDepthBufferTextureUnit = renderer->getProgramUniformLocation(programId, "temporaryDepthBufferTextureUnit");
	uniformBufferTexturePixelWidth = renderer->getProgramUniformLocation(programId, "bufferTexturePixelWidth");
	uniformBufferTexturePixelHeight = renderer->getProgramUniformLocation(programId, "bufferTexturePixelHeight");

	//
	initialized = true;
}

void PostProcessingShaderBaseImplementation::useProgram(void* context)
{
	isRunning = true;
	renderer->useProgram(programId);
	if (uniformColorBufferTextureUnit != -1) renderer->setProgramUniformInteger(context, uniformColorBufferTextureUnit, 0);
	if (uniformDepthBufferTextureUnit != -1) renderer->setProgramUniformInteger(context, uniformDepthBufferTextureUnit, 1);
	if (uniformTemporaryColorBufferTextureUnit != -1) renderer->setProgramUniformInteger(context, uniformTemporaryColorBufferTextureUnit, 2);
	if (uniformTemporaryDepthBufferTextureUnit != -1) renderer->setProgramUniformInteger(context, uniformTemporaryDepthBufferTextureUnit, 3);
}

void PostProcessingShaderBaseImplementation::unUseProgram()
{
	isRunning = false;
}

void PostProcessingShaderBaseImplementation::setBufferPixelWidth(void* context, float pixelWidth) {
	if (uniformBufferTexturePixelWidth != -1) renderer->setProgramUniformFloat(context, uniformBufferTexturePixelWidth, pixelWidth);
}

void PostProcessingShaderBaseImplementation::setBufferPixelHeight(void* context, float pixelHeight) {
	if (uniformBufferTexturePixelHeight != -1) renderer->setProgramUniformFloat(context, uniformBufferTexturePixelHeight, pixelHeight);
}
