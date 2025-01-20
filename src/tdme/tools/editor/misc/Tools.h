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
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::prototype::Prototype;
using tdme::engine::Color4;
using tdme::engine::Engine;
using tdme::engine::Light;
using tdme::engine::Transform;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::tools::editor::misc::CameraRotationInputHandler;

/**
 * Editor tools
 * @author Andreas Drewke
 */
class tdme::tools::editor::misc::Tools final
{
private:
	STATIC_DLL_IMPEXT static Engine* osEngine;
	STATIC_DLL_IMPEXT static Model* gizmoAll;
	STATIC_DLL_IMPEXT static Model* gizmoTranslationScale;
	STATIC_DLL_IMPEXT static Model* gizmoTranslation;
	STATIC_DLL_IMPEXT static Model* gizmoScale;
	STATIC_DLL_IMPEXT static Model* gizmoRotations;
	STATIC_DLL_IMPEXT static Model* defaultOBB;

	struct ToolsShutdown {
		~ToolsShutdown();
	};

	STATIC_DLL_IMPEXT static ToolsShutdown toolsShutdown;

public:
	/**
	 * Formats a float to a human readable format
	 * @param value value
	 * @returns value as string
	 */
	static string formatFloat(float value);

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
	 * @returns max axis dimension
	 */
	static float computeMaxAxisDimension(BoundingBox* boundingBox);

	/**
	 * Creates ground plate with 1m x 1m texture
	 * @param width width
	 * @param depth depth
	 * @param y float y
	 * @returns ground model
	 */
	static Model* createGroundModel(float width, float depth, float y);

	/**
	 * Creates grid plate with 1m x 1m texture
	 * @returns grid model
	 */
	static Model* createGridModel();

	/**
	 * Set up entity in given engine with look from rotations and scale
	 * @param prototype prototype
	 * @param engine engine
	 * @param lookFromRotations look from rotations
	 * @param lodLevel lod level
	 * @param cameraRotationInputHandler camera rotation input handler
	 * @param resetup resetup which would mean to leave camera and lighting as is
	 */
	static void setupPrototype(Prototype* prototype, Engine* engine, const Transform& lookFromRotations, int lodLevel, Vector3& objectScale, CameraRotationInputHandler* cameraRotationInputHandler = nullptr, float scale = 1.5f, bool resetup = false);

	/**
	 * Get relative resources file name
	 * @param applicationRoot application root
	 * @param fileName file name
	 * @returns relative resources file name
	 */
	static const string getRelativeResourcesFileName(const string& applicationRoot, const string& fileName);

	/**
	 * Get application root path name
	 * @param fileName file name
	 * @returns application root path name
	 */
	static const string getApplicationRootPathName(const string& fileName);

	/**
	 * Get application sub path name
	 * @param fileName application sub path name
	 * @returns application sub path name
	 */
	static const string getApplicationSubPathName(const string& fileName);

	/**
	 * Get canonical URI of given path and file name
	 * @param pathName path name
	 * @param fileName file name
	 * @returns path
	 */
	static const string getCanonicalURI(const string& pathName, const string& fileName);

	/**
	 * Get path of given file name
	 * @param fileName file name
	 * @returns path
	 */
	static const string getPathName(const string& fileName);

	/**
	 * Get file name of given file name
	 * @param fileName file name
	 * @returns file name
	 */
	static const string getFileName(const string& fileName);

	/**
	 * Remove file extension, e.g. .dae, .fbx, ...
	 * @param fileName file name
	 * @returns file name
	 */
	static const string removeFileExtension(const string& fileName);

	/**
	 * Ensure file extension
	 * @param fileName file name
	 * @param extension extension
	 * @returns file name
	 */
	static const string ensureFileExtension(const string& fileName, const string& extension);

	/**
	 * Get file extension
	 * @param fileName file name
	 * @returns file extension
	 */
	static const string getFileExtension(const string& fileName);

	/**
	 * Load settings
	 * @param application application
	 */
	static void loadSettings(Application* application);

	/**
	 * @returns GIZMO translation/rotations/scale
	 */
	static Model* getGizmoAll();

	/**
	 * @returns GIZMO translation/rotations/scale
	 */
	static Model* getGizmoTranslationScale();

	/**
	 * @returns GIZMO for translation
	 */
	static Model* getGizmoTranslation();

	/**
	 * @returns GIZMO for scale
	 */
	static Model* getGizmoScale();

	/**
	 * @returns GIZMO for rotations
	 */
	static Model* getGizmoRotations();

	/**
	 * @returns default obb
	 */
	static Model* getDefaultObb();

	/**
	 * Returns if file extension of given file name does match a extension in given extensions
	 * @param fileName file name
	 * @param extensions extensions
	 * @returns success
	 */
	static bool hasFileExtension(const string& fileName, const vector<string>& extensions);

	/**
	 * Enumerate file extensions
	 * @param extensions extensions
	 * @returns file extensions as human readable string
	 */
	inline static const string enumerateFileExtensions(const vector<string>& extensions) {
		string result;
		for (const auto& extension: extensions) {
			if (result.empty() == false) result+= ", ";
			result+= "*." + extension;
		}
		return result;
	}

};
