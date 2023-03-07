#include <string>
#include <vector>

using std::string;
using std::vector;

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingProgram.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShader.h>
#include <tdme/engine/Engine.h>

using tdme::engine::subsystems::postprocessing::PostProcessingProgram;
using tdme::engine::subsystems::postprocessing::PostProcessingShader;


PostProcessingProgram::PostProcessingProgram(RenderPass renderPass) {
	this->renderPass = renderPass;
}

void PostProcessingProgram::addEffectPass(
	int effectPassIdx,
	int frameBufferWidthDivideFactor,
	int frameBufferHeightDivideFactor,
	string shaderPrefix,
	bool useEZR,
	bool applyShadowMapping,
	bool applyPostProcessing,
	int32_t renderTypes,
	Color4 clearColor,
	bool renderLightSources,
	bool skipOnLightSourceNotVisible
) {
	effectPasses.emplace_back(
		effectPassIdx,
		frameBufferWidthDivideFactor,
		frameBufferHeightDivideFactor,
		shaderPrefix,
		useEZR,
		applyShadowMapping,
		applyPostProcessing,
		renderTypes,
		clearColor,
		renderLightSources,
		skipOnLightSourceNotVisible
	);
}

void PostProcessingProgram::addPostProcessingStep(string shaderId, PostProcessingProgram::FrameBufferSource source, PostProcessingProgram::FrameBufferTarget target, bool bindTemporary, PostProcessingProgram::FrameBufferSource blendToSource) {
	steps.emplace_back(
		shaderId,
		source,
		target,
		bindTemporary,
		blendToSource
	);
}

bool PostProcessingProgram::isSupported() {
	for (auto step: steps) {
		if (Engine::getInstance()->getPostProcessingShader()->hasShader(step.shaderId) == false) return false;
	}
	return true;

}
