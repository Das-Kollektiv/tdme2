#pragma once

#include <string>
#include <vector>

#define ENABLE_VHACD_IMPLEMENTATION 1
#define VHACD_DISABLE_THREADING 0
#include <VHACD.h>

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
	 * @param popUps pop ups which is optional
	 * @param pathName path name
	 * @param fileName file name
	 * @param convexMeshTMsData convex mesh TM data vectors
	 * @param parameters parameters
	 * @return success
	 */
	static bool generateConvexMeshes(
		Prototype* prototype,
		Mode mode,
		PopUps* popUps,
		const string& pathName,
		const string& fileName,
		vector<vector<uint8_t>>& convexMeshTMsData,
		VHACD::IVHACD::Parameters parameters = VHACD::IVHACD::Parameters()
	);

private:

	/**
	 * Create model
	 * @param id id
	 * @param points points
	 * @param triangles triangles
	 */
	static Model* createModel(const string& id, const vector<VHACD::Vertex>& points, const vector<VHACD::Triangle>& triangles);

	/**
	 * Create model
	 * @param id id
	 * @param triangles triangles
	 */
	static Model* createModel(const string& id, vector<Triangle>& triangles);

};
