#include <string>
#include <vector>

using std::string;
using std::vector;

#include <tdme/engine/Engine.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingProgram.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingShader.h>

using tdme::engine::subsystems::postprocessing::PostProcessingProgram;
using tdme::engine::subsystems::postprocessing::PostProcessingShader;


PostProcessingProgram::PostProcessingProgram(RenderPass renderPass) {
	this->renderPass = renderPass;
}

void PostProcessingProgram::addPostProcessingStep(string shaderId, PostProcessingProgram::FrameBufferSource source, PostProcessingProgram::FrameBufferTarget target, bool bindTemporary) {
	PostProcessingProgramStep step;
	step.shaderId = shaderId;
	step.source = source;
	step.target = target;
	step.bindTemporary = bindTemporary;
	steps.push_back(step);
}

bool PostProcessingProgram::isSupported() {
	for (auto step: steps) {
		if (Engine::getInstance()->getPostProcessingShader()->hasShader(step.shaderId) == false) return false;
	}
	return true;

}
