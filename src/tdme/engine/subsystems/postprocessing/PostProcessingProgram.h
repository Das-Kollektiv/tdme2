#pragma once

#include <string>
#include <vector>

#include <tdme/engine/subsystems/postprocessing/fwd-tdme.h>

using std::string;
using std::vector;

/** 
 * Post processing program
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::subsystems::postprocessing::PostProcessingProgram final
{
	friend class PostProcessing;

public:
	enum RenderPass { RENDERPASS_OBJECTS, RENDERPASS_FINAL };
	enum FrameBufferSource { FRAMEBUFFERSOURCE_SCREEN };
	enum FrameBufferTarget { FRAMEBUFFERTARGET_TEMPORARY, FRAMEBUFFERTARGET_SCREEN };

private:
	struct PostProcessingProgramStep {
		string shaderId;
		FrameBufferSource source;
		FrameBufferTarget target;
		bool bindTemporary;

	};
	RenderPass renderPass;
	vector<PostProcessingProgramStep> steps;

public:
	/**
	 * Constructor
	 * @param renderPass render pass
	 */
	PostProcessingProgram(RenderPass renderPass);

	/**
	 * Add step
	 * @param shaderId shader Id
	 * @param source source
	 * @param target target
	 * @param bindTemporary bind temporary
	 */
	void addPostProcessingStep(
		string shaderId,
		FrameBufferSource source,
		FrameBufferTarget target,
		bool bindTemporary = false
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

};
