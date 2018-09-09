#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/renderer/GLRenderer.h>

using std::string;

using tdme::engine::subsystems::postprocessing::PostProcessingShaderBaseImplementation;
using tdme::engine::subsystems::renderer::GLRenderer;
using tdme::engine::Engine;

PostProcessingShaderBaseImplementation::PostProcessingShaderBaseImplementation(GLRenderer* renderer)
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
	uniformBufferTexturePixelWidth = renderer->getProgramUniformLocation(programId, "bufferTexturePixelWidth");
	uniformBufferTexturePixelHeight = renderer->getProgramUniformLocation(programId, "bufferTexturePixelHeight");

	//
	initialized = true;
}

void PostProcessingShaderBaseImplementation::useProgram()
{
	isRunning = true;
	renderer->useProgram(programId);
	renderer->setProgramUniformInteger(uniformColorBufferTextureUnit, 0);
	renderer->setProgramUniformInteger(uniformDepthBufferTextureUnit, 1);
}

void PostProcessingShaderBaseImplementation::unUseProgram()
{
	isRunning = false;
}

void PostProcessingShaderBaseImplementation::setBufferPixelWidth(float pixelWidth) {
	renderer->setProgramUniformFloat(uniformBufferTexturePixelWidth, pixelWidth);
}

void PostProcessingShaderBaseImplementation::setBufferPixelHeight(float pixelHeight) {
	renderer->setProgramUniformFloat(uniformBufferTexturePixelHeight, pixelHeight);
}
