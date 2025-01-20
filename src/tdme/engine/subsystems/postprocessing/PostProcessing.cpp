#include <map>
#include <memory>
#include <string>

using std::make_unique;
using std::map;
using std::string;

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/postprocessing/PostProcessing.h>

#include <tdme/engine/subsystems/postprocessing/PostProcessingProgram.h>
#include <tdme/engine/subsystems/rendering/EntityRenderer.h>
#include <tdme/engine/Color4.h>

using tdme::engine::subsystems::postprocessing::PostProcessing;

using tdme::engine::subsystems::postprocessing::PostProcessingProgram;
using tdme::engine::subsystems::rendering::EntityRenderer;
using tdme::engine::Color4;

PostProcessing::PostProcessing() {
	{
		auto program = make_unique<PostProcessingProgram>(PostProcessingProgram::RENDERPASS_OBJECTS);
		program->addPostProcessingStep("ssao_map", PostProcessingProgram::FRAMEBUFFERSOURCE_SCREEN, PostProcessingProgram::FRAMEBUFFERTARGET_TEMPORARY);
		program->addPostProcessingStep("ssao", PostProcessingProgram::FRAMEBUFFERSOURCE_SCREEN, PostProcessingProgram::FRAMEBUFFERTARGET_SCREEN, true);
		if (program->isSupported() == true) {
			programs["ssao"] = program.release();
		}
	}
	{
		auto program = make_unique<PostProcessingProgram>(PostProcessingProgram::RENDERPASS_FINAL);
		program->addEffectPass(
			Engine::EFFECTPASS_LIGHTSCATTERING,
			2,
			2,
			"ls_",
			false,
			false,
			EntityRenderer::RENDERTYPE_TEXTUREARRAYS_DIFFUSEMASKEDTRANSPARENCY |
				EntityRenderer::RENDERTYPE_MATERIALS_DIFFUSEMASKEDTRANSPARENCY |
				EntityRenderer::RENDERTYPE_TEXTURES_DIFFUSEMASKEDTRANSPARENCY,
			Color4(1.0f, 1.0f, 1.0f, 0.0f),
			true,
			true
		);
		program->addPostProcessingStep(
			"light_scattering",
			PostProcessingProgram::FRAMEBUFFERSOURCE_EFFECTPASS0,
			PostProcessingProgram::FRAMEBUFFERTARGET_SCREEN,
			false,
			PostProcessingProgram::FRAMEBUFFERSOURCE_SCREEN
		);
		if (program->isSupported() == true) {
			programs["light_scattering"] = program.release();
		}
	}
	{
		auto program = make_unique<PostProcessingProgram>(PostProcessingProgram::RENDERPASS_FINAL);
		program->addPostProcessingStep("desaturation", PostProcessingProgram::FRAMEBUFFERSOURCE_SCREEN, PostProcessingProgram::FRAMEBUFFERTARGET_SCREEN);
		if (program->isSupported() == true) {
			programs["desaturation"] = program.release();
		}

	}
	{
		auto program = make_unique<PostProcessingProgram>(PostProcessingProgram::RENDERPASS_FINAL);
		program->addPostProcessingStep("depth_blur", PostProcessingProgram::FRAMEBUFFERSOURCE_SCREEN, PostProcessingProgram::FRAMEBUFFERTARGET_SCREEN);
		if (program->isSupported() == true) {
			programs["depth_blur"] = program.release();
		}
	}
	{
		auto program = make_unique<PostProcessingProgram>(PostProcessingProgram::RENDERPASS_FINAL);
		program->addPostProcessingStep("vignette", PostProcessingProgram::FRAMEBUFFERSOURCE_SCREEN, PostProcessingProgram::FRAMEBUFFERTARGET_SCREEN);
		if (program->isSupported() == true) {
			programs["vignette"] = program.release();
		}
	}
}

PostProcessing::~PostProcessing() {
	for (const auto& [programId, program]: programs) {
		delete program;
	}
}


