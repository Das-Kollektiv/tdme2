#include <string>
#include <vector>

using std::string;
using std::vector;

#include <tdme/engine/subsystems/postprocessing/PostProcessingProgram.h>

using tdme::engine::subsystems::postprocessing::PostProcessingProgram;

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
