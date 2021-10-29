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
	 * Generate billboard LOD nidek
	 * @param prototype prototype
	 * @param model model
	 * @param pathName path name
	 * @param fileName file name
	 * @return billboard LOD model
	 */
	static Model* generateBillboardLOD(
		Model* model,
		const string& pathName,
		const string& fileName
	);

};
