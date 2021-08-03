#pragma once

#include <array>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/application/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/tools/editor/misc/fwd-tdme.h>

using std::array;
using std::string;
using std::vector;

using tdme::application::Application;
using tdme::engine::model::Color4;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::prototype::Prototype;
using tdme::engine::Engine;
using tdme::engine::Light;
using tdme::engine::Transformations;
using tdme::math::Vector3;
using tdme::math::Vector4;

/**
 * Editor tools
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::editor::misc::Tools final
{
private:
	static Engine* osEngine;
	static float oseScale;
	static Model* gizmoAll;
	static Model* gizmoTranslationScale;
	static Model* gizmoTranslation;
	static Model* gizmoScale;
	static Model* gizmoRotations;
	static Model* defaultOBB;

	struct ToolsShutdown {
		~ToolsShutdown();
	};

	static ToolsShutdown toolsShutdown;

public:
	/**
	 * Set up given engine light with default light
	 * @param light light
	 */
	static void setDefaultLight(Light* light);

	/**
	 * Init off screen engine for making thumbails
	 */
	static void oseInit();

	/**
	 * Dispose off screen engine
	 */
	static void oseDispose();

	/**
	 * Make a thumbnail of given prototype with off screen engine
	 * @param prototype prototype
	 * @param pngData PNG data
	 */
	static void oseThumbnail(Prototype* prototype, vector<uint8_t>& pngData);

	/**
	 * Compute max axis dimension for given bounding box
	 * @param boundingBox bounding box
	 * @return max axis dimension
	 */
	static float computeMaxAxisDimension(BoundingBox* boundingBox);

	/**
	 * Creates ground plate with 1m x 1m texture
	 * @param width width
	 * @param depth depth
	 * @param y float y
	 * @return ground model
	 */
	static Model* createGroundModel(float width, float depth, float y);

	/**
	 * Creates grid plate with 1m x 1m texture
	 * @return grid model
	 */
	static Model* createGridModel();

	/**
	 * Set up entity in given engine with look from rotations and scale
	 * @param prototype prototype
	 * @param engine engine
	 * @param lookFromRotations look from rotations
	 * @param camScale scale
	 * @param lodLevel lod level
	 */
	static void setupPrototype(Prototype* prototype, Engine* engine, const Transformations& lookFromRotations, float camScale, int lodLevel, Vector3& objectScale);

	/**
	 * Get relative resources file name
	 * @param applicationRoot application root
	 * @param fileName file name
	 * @return relative resources file name
	 */
	static const string getRelativeResourcesFileName(const string& applicationRoot, const string& fileName);

	/**
	 * Get application root path name
	 * @param fileName file name
	 * @return application root path name
	 */
	static const string getApplicationRootPathName(const string& fileName);

	/**
	 * Get application sub path name
	 * @param fileName application sub path name
	 * @return application sub path name
	 */
	static const string getApplicationSubPathName(const string& fileName);

	/**
	 * Get path of given file name
	 * @param fileName file name
	 * @return path
	 */
	static const string getPathName(const string& fileName);

	/**
	 * Get file name of given file name
	 * @param fileName file name
	 * @return file name
	 */
	static const string getFileName(const string& fileName);

	/**
	 * Remove file ending, e.g. .dae, .fbx, ...
	 * @param fileName file name
	 * @return file name
	 */
	static const string removeFileEnding(const string& fileName);

	/**
	 * Load settings
	 * @param application application
	 */
	static void loadSettings(Application* application);

	/**
	 * @return GIZMO translation/rotations/scale
	 */
	static Model* getGizmoAll();

	/**
	 * @return GIZMO translation/rotations/scale
	 */
	static Model* getGizmoTranslationScale();

	/**
	 * @return GIZMO for translation
	 */
	static Model* getGizmoTranslation();

	/**
	 * @return GIZMO for scale
	 */
	static Model* getGizmoScale();

	/**
	 * @return GIZMO for rotations
	 */
	static Model* getGizmoRotations();

	/**
	 * @return default obb
	 */
	static Model* getDefaultObb();

};
