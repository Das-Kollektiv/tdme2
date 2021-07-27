#pragma once

#include <string>
#include <vector>

#include <ext/v-hacd/src/VHACD_Lib/public/VHACD.h>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>

using std::string;
using std::vector;

using tdme::engine::model::Model;
using tdme::engine::primitives::Triangle;
using tdme::engine::prototype::Prototype;
using tdme::tools::editor::misc::PopUps;

/**
 * Convex mesh generation class
 */
class tdme::tools::editor::misc::GenerateConvexMeshes
{
public:
	enum Mode { MODE_IMPORT, MODE_GENERATE };

	/**
	 * Remove convex meshes
	 * @param prototype prototype
	 */
	static void removeConvexMeshes(Prototype* prototype);

	/**
	 * Generateconvex meshes
	 * @param prototype prototype
	 * @param mode mode
	 * @param popUps pop ups
	 * @param pathName path name
	 * @param fileName file name
	 * @param parameters parameters
	 */
	static vector<string> generateConvexMeshes(
		Prototype* prototype,
		Mode mode,
		PopUps* popUps,
		const string& pathName,
		const string& fileName,
		VHACD::IVHACD::Parameters parameters = VHACD::IVHACD::Parameters()
	);

private:

	/**
	 * Create model
	 * @param id id
	 * @param points points
	 * @param triangles triangles
	 * @param pointCount point count
	 * @param triangleCount triangle count
	 */
	static Model* createModel(const string& id, double* points, unsigned int* triangles, unsigned int pointCount, unsigned int triangleCount);

	/**
	 * Create model
	 * @param id id
	 * @param triangles triangles
	 */
	static Model* createModel(const string& id, vector<Triangle>& triangles);

};
