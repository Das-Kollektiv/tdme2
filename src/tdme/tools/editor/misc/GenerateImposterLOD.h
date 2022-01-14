#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>

using tdme::engine::model::Model;

using std::string;
using std::vector;

using tdme::tools::editor::misc::PopUps;

/**
 * Generate imposter LOD utility class
 */
class tdme::tools::editor::misc::GenerateImposterLOD
{
public:
	/**
	 * Generate imposter LOD
	 * @param prototype prototype
	 * @param model model
	 * @param pathName model path name
	 * @param fileName model file name
	 * @param billboardCount billboard count
	 * @param imposterModelFileNames imposter model file names
	 * @param imposterModels imposter models
	 */
	static void generate(
		Model* model,
		const string& pathName,
		const string& fileName,
		int billboardCount,
		vector<string>& imposterModelFileNames,
		vector<Model*>& imposterModels
	);

};
