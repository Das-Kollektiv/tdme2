#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/subsystems/postprocessing/fwd-tdme.h>

using std::string;
using std::vector;

using tdme::engine::Color4;

/**
 * Post processing program
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::postprocessing::PostProcessingProgram final
{
	friend class PostProcessing;

public:
	enum RenderPass { RENDERPASS_OBJECTS, RENDERPASS_FINAL };
	enum FrameBufferSource { FRAMEBUFFERSOURCE_NONE, FRAMEBUFFERSOURCE_SCREEN, FRAMEBUFFERSOURCE_EFFECTPASS0 };
	enum FrameBufferTarget { FRAMEBUFFERTARGET_TEMPORARY, FRAMEBUFFERTARGET_SCREEN };

private:
	struct PostProcessingProgramEffectPass {
		PostProcessingProgramEffectPass(
			int effectPassIdx,
			int frameBufferWidthDivideFactor,
			int frameBufferHeightDivideFactor,
			const string& shaderPrefix,
			bool applyShadowMapping,
			bool applyPostProcessing,
			int32_t renderTypes,
			const Color4& clearColor,
			bool renderLightSources,
			bool skipOnLightSourceNotVisible
		):
			effectPassIdx(effectPassIdx),
			frameBufferWidthDivideFactor(frameBufferWidthDivideFactor),
			frameBufferHeightDivideFactor(frameBufferHeightDivideFactor),
			shaderPrefix(shaderPrefix),
			applyShadowMapping(applyShadowMapping),
			applyPostProcessing(applyPostProcessing),
			renderTypes(renderTypes),
			clearColor(clearColor),
			renderLightSources(renderLightSources),
			skipOnLightSourceNotVisible(skipOnLightSourceNotVisible)
		{}
		int effectPassIdx;
		int frameBufferWidthDivideFactor;
		int frameBufferHeightDivideFactor;
		string shaderPrefix;
		bool applyShadowMapping;
		bool applyPostProcessing;
		int32_t renderTypes;
		Color4 clearColor;
		bool renderLightSources;
		bool skipOnLightSourceNotVisible;
	};
	struct PostProcessingProgramStep {
		PostProcessingProgramStep(
			const string& shaderId,
			FrameBufferSource source,
			FrameBufferTarget target,
			bool bindTemporary,
			FrameBufferSource blendToSource
		):
			shaderId(shaderId),
			source(source),
			target(target),
			bindTemporary(bindTemporary),
			blendToSource(blendToSource)
		{}
		string shaderId;
		FrameBufferSource source;
		FrameBufferTarget target;
		bool bindTemporary;
		FrameBufferSource blendToSource;
	};
	RenderPass renderPass;
	vector<PostProcessingProgramEffectPass> effectPasses;
	vector<PostProcessingProgramStep> steps;

public:
	// forbid class copy
	FORBID_CLASS_COPY(PostProcessingProgram)

	/**
	 * Constructor
	 * @param renderPass render pass
	 */
	PostProcessingProgram(RenderPass renderPass);

	/**
	 * Add effect pass
	 * @param effectPassIdx effect pass index
	 * @param frameBufferWidthDivideFactor frame buffer width divide factor
	 * @param frameBufferHeightDivideFactor frame buffer height divide factor
	 * @param shaderPrefix shader prefix
	 * @param applyShadowMapping apply shadow mapping
	 * @param applyPostProcessing apply post processing
	 * @param renderTypes render types
	 * @param clearColor clear color
	 * @param renderLightSources render light sources
	 * @param skipOnLightSourceNotVisible skip on light source not visible
	 */
	void addEffectPass(
		int effectPassIdx,
		int frameBufferWidthDivideFactor,
		int frameBufferHeightDivideFactor,
		string shaderPrefix,
		bool applyShadowMapping,
		bool applyPostProcessing,
		int32_t renderTypes,
		Color4 clearColor,
		bool renderLightSources,
		bool skipOnLightSourceNotVisible
	);

	/**
	 * @return effect passes
	 */
	inline const vector<PostProcessingProgramEffectPass>& getEffectPasses() const {
		return effectPasses;
	}

	/**
	 * Add step
	 * @param shaderId shader Id
	 * @param source source
	 * @param target target
	 * @param bindTemporary bind temporary
	 * @param blendToSource blend to source
	 */
	void addPostProcessingStep(
		string shaderId,
		FrameBufferSource source,
		FrameBufferTarget target,
		bool bindTemporary = false,
		FrameBufferSource blendToSource = FRAMEBUFFERSOURCE_NONE
	);

	/**
	 * @return render pass
	 */
	inline const RenderPass getRenderPass() const {
		return renderPass;
	}

	/**
	 * @return steps
	 */
	inline const vector<PostProcessingProgramStep>& getPostProcessingSteps() const {
		return steps;
	}

	/**
	 * Checks if program is supported
	 * @return if program is supported
	 */
	bool isSupported();

};
