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
	enum FrameBufferSource { FRAMEBUFFERSOURCE_SCREEN };
	enum FrameBufferTarget { FRAMEBUFFERTARGET_TEMPORARY, FRAMEBUFFERTARGET_SCREEN };

private:
	struct PostProcessingProgramStep {
		string shaderId;
		FrameBufferSource source;
		FrameBufferTarget target;
		bool bindTemporary;

	};
	vector<PostProcessingProgramStep> steps;

public:
	/**
	 * Constructor
	 */
	PostProcessingProgram();

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
	 * @return steps
	 */
	const vector<PostProcessingProgramStep>& getPostProcessingSteps();

};
