#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/renderer/Renderer.h>
#include <tdme/engine/Engine.h>

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

void PostProcessingShaderBaseImplementation::useProgram(int contextIdx)
{
	isRunning = true;
	renderer->useProgram(contextIdx, programId);
	renderer->setLighting(contextIdx, renderer->LIGHTING_NONE);
	if (uniformColorBufferTextureUnit != -1) renderer->setProgramUniformInteger(contextIdx, uniformColorBufferTextureUnit, 0);
	if (uniformDepthBufferTextureUnit != -1) renderer->setProgramUniformInteger(contextIdx, uniformDepthBufferTextureUnit, 1);
	if (uniformTemporaryColorBufferTextureUnit != -1) renderer->setProgramUniformInteger(contextIdx, uniformTemporaryColorBufferTextureUnit, 2);
	if (uniformTemporaryDepthBufferTextureUnit != -1) renderer->setProgramUniformInteger(contextIdx, uniformTemporaryDepthBufferTextureUnit, 3);
}

void PostProcessingShaderBaseImplementation::unUseProgram()
{
	isRunning = false;
}

void PostProcessingShaderBaseImplementation::setBufferPixelWidth(int contextIdx, float pixelWidth) {
	if (uniformBufferTexturePixelWidth != -1) {
		renderer->setProgramUniformFloat(contextIdx, uniformBufferTexturePixelWidth, pixelWidth);
	}
}

void PostProcessingShaderBaseImplementation::setBufferPixelHeight(int contextIdx, float pixelHeight) {
	if (uniformBufferTexturePixelHeight != -1) {
		renderer->setProgramUniformFloat(contextIdx, uniformBufferTexturePixelHeight, pixelHeight);
	}
}
