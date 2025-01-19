#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>

using tdme::engine::model::Model;

using std::string;

using tdme::tools::editor::misc::PopUps;

/**
 * Generate billboard LOD utility class
 */
class tdme::tools::editor::misc::GenerateBillboardLOD
{
public:
	/**
	 * Generate billboard LOD
	 * @param prototype prototype
	 * @param model model
	 * @param pathName path name
	 * @param fileName file name
	 * @returns generated billboard model
	 */
	static Model* generate(
		Model* model,
		const string& pathName,
		const string& fileName
	);

};
