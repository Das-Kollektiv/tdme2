#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShaderBaseImplementation.h>
#include <tdme/engine/subsystems/renderer/RendererBackend.h>
#include <tdme/engine/Engine.h>

using tdme::engine::subsystems::postprocessing::PostProcessingShaderBaseImplementation;
using tdme::engine::subsystems::renderer::RendererBackend;
using tdme::engine::Engine;

PostProcessingShaderBaseImplementation::PostProcessingShaderBaseImplementation(RendererBackend* rendererBackend)
{
	this->rendererBackend = rendererBackend;
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
	if (rendererBackend->isUsingProgramAttributeLocation() == true) {
		rendererBackend->setProgramAttributeLocation(programId, 0, "inVertex");
		rendererBackend->setProgramAttributeLocation(programId, 2, "inTextureUV");
	}

	if (rendererBackend->linkProgram(programId) == false)
		return;

	// uniforms
	uniformColorBufferTextureUnit = rendererBackend->getProgramUniformLocation(programId, "colorBufferTextureUnit");
	uniformDepthBufferTextureUnit = rendererBackend->getProgramUniformLocation(programId, "depthBufferTextureUnit");
	uniformTemporaryColorBufferTextureUnit = rendererBackend->getProgramUniformLocation(programId, "temporaryColorBufferTextureUnit");
	uniformTemporaryDepthBufferTextureUnit = rendererBackend->getProgramUniformLocation(programId, "temporaryDepthBufferTextureUnit");
	uniformBufferTexturePixelWidth = rendererBackend->getProgramUniformLocation(programId, "bufferTexturePixelWidth");
	uniformBufferTexturePixelHeight = rendererBackend->getProgramUniformLocation(programId, "bufferTexturePixelHeight");

	//
	initialized = true;
}

void PostProcessingShaderBaseImplementation::useProgram(int contextIdx)
{
	isRunning = true;
	rendererBackend->useProgram(contextIdx, programId);
	rendererBackend->setLighting(contextIdx, rendererBackend->LIGHTING_NONE);
	if (uniformColorBufferTextureUnit != -1) rendererBackend->setProgramUniformInteger(contextIdx, uniformColorBufferTextureUnit, 0);
	if (uniformDepthBufferTextureUnit != -1) rendererBackend->setProgramUniformInteger(contextIdx, uniformDepthBufferTextureUnit, 1);
	if (uniformTemporaryColorBufferTextureUnit != -1) rendererBackend->setProgramUniformInteger(contextIdx, uniformTemporaryColorBufferTextureUnit, 2);
	if (uniformTemporaryDepthBufferTextureUnit != -1) rendererBackend->setProgramUniformInteger(contextIdx, uniformTemporaryDepthBufferTextureUnit, 3);
}

void PostProcessingShaderBaseImplementation::unUseProgram()
{
	isRunning = false;
}

void PostProcessingShaderBaseImplementation::setBufferPixelWidth(int contextIdx, float pixelWidth) {
	if (uniformBufferTexturePixelWidth != -1) {
		rendererBackend->setProgramUniformFloat(contextIdx, uniformBufferTexturePixelWidth, pixelWidth);
	}
}

void PostProcessingShaderBaseImplementation::setBufferPixelHeight(int contextIdx, float pixelHeight) {
	if (uniformBufferTexturePixelHeight != -1) {
		rendererBackend->setProgramUniformFloat(contextIdx, uniformBufferTexturePixelHeight, pixelHeight);
	}
}

void PostProcessingShaderBaseImplementation::unloadTextures() {
}

void PostProcessingShaderBaseImplementation::loadTextures(const string& pathName) {
}
