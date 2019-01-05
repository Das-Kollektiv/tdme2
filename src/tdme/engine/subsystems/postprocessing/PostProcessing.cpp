#include <map>
#include <string>

using std::map;
using std::string;

#include <tdme/engine/subsystems/postprocessing/fwd-tdme.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessing.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessingProgram.h>

using tdme::engine::subsystems::postprocessing::PostProcessing;
using tdme::engine::subsystems::postprocessing::PostProcessingProgram;

PostProcessing::PostProcessing() {
	{
		auto program = new PostProcessingProgram();
		program->addPostProcessingStep("depth_blur", PostProcessingProgram::FRAMEBUFFERSOURCE_SCREEN, PostProcessingProgram::FRAMEBUFFERTARGET_SCREEN);
		programs["depth_blur"] = program;

	}
	{
		auto program = new PostProcessingProgram();
		program->addPostProcessingStep("ssao_map", PostProcessingProgram::FRAMEBUFFERSOURCE_SCREEN, PostProcessingProgram::FRAMEBUFFERTARGET_TEMPORARY);
		program->addPostProcessingStep("ssao", PostProcessingProgram::FRAMEBUFFERSOURCE_SCREEN, PostProcessingProgram::FRAMEBUFFERTARGET_SCREEN, true);
		programs["ssao"] = program;

	}
	{
		auto program = new PostProcessingProgram();
		program->addPostProcessingStep("depth_fog", PostProcessingProgram::FRAMEBUFFERSOURCE_SCREEN, PostProcessingProgram::FRAMEBUFFERTARGET_SCREEN);
		programs["depth_fog"] = program;
	}
}

PostProcessingProgram* PostProcessing::getPostProcessingProgram(const string& programId) {
	auto programIt = programs.find(programId);
	return programIt == programs.end()?nullptr:programIt->second;
}


