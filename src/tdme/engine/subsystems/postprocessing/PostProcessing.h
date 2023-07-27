#pragma once

#include <map>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/subsystems/postprocessing/fwd-tdme.h>

using std::map;
using std::string;

using tdme::engine::subsystems::postprocessing::PostProcessingProgram;

/**
 * Post processing
 * @author Andreas Drewke
 */
class tdme::engine::subsystems::postprocessing::PostProcessing final
{
public:
	// forbid class copy
	CLASS_FORBID_COPY(PostProcessing)

	/**
	 * Constructor
	 */
	PostProcessing();

	/**
	 * Get post processing program
	 * @param programId program id
	 * @return post processing program
	 */
	PostProcessingProgram* getPostProcessingProgram(const string& programId);

private:
	map<string, PostProcessingProgram*> programs;
};
