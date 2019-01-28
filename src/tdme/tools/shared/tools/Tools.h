
#pragma once

#include <array>
#include <string>

#include <tdme/tdme.h>
#include <tdme/application/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/tools/fwd-tdme.h>

using std::array;
using std::string;

using tdme::application::Application;
using tdme::engine::Engine;
using tdme::engine::Light;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::tools::shared::model::LevelEditorEntity;

/** 
 * Thumbnail generator
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::tools::Tools final
{
private:
	static Engine* osEngine;
	static float oseScale;

public:

	/** 
	 * Formats a float to a human readable format
	 * @param value value
	 * @return value as string
	 */
	static string formatFloat(float value);

	/** 
	 * Formats a vector3 to a human readable format
	 * @param value value
	 * @return value as string
	 */
	static string formatVector3(const Vector3& value);

	/** 
	 * Formats a color4 to a human readable format
	 * @param value value
	 * @return value as string
	 */
	static string formatColor4(const Color4& value);

	/** 
	 * Convert string to array
	 * @param text text
	 * @param array array
	 */
	static void convertToArray(const string& text, array<float, 3>& array) /* throws(NumberFormatException) */;

	/**
	 * Convert string to array
	 * @param text text
	 * @param array array
	 */
	static void convertToArray(const string& text, array<float, 4>& array) /* throws(NumberFormatException) */;

	/** 
	 * Convert to vector 3
	 * @param text text
	 * @return vector3
	 */
	static Vector3 convertToVector3(const string& text) /* throws(NumberFormatException) */;

	/** 
	 * Convert to vector 4
	 * @param text text
	 * @return vector4
	 */
	static Vector4 convertToVector4(const string& text) /* throws(NumberFormatException) */;

	/** 
	 * Convert to color 4
	 * @param text text
	 * @return color4
	 */
	static Color4 convertToColor4(const string& text) /* throws(NumberFormatException) */;

	/** 
	 * Convert string to float
	 * @param text text
	 * @return float
	 */
	static float convertToFloat(const string& text) /* throws(NumberFormatException) */;

	/** 
	 * Convert string to int
	 * @param text text
	 * @return int
	 */
	static int32_t convertToInt(const string& text) /* throws(NumberFormatException) */;

	/** 
	 * Convert string to int
	 * @param text text
	 * @return int
	 */
	static int32_t convertToIntSilent(const string& text);

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
	 * Make a thumbnail of given model with off screen engine
	 * @param model model
	 */
	static void oseThumbnail(LevelEditorEntity* model);

	/** 
	 * Compute max axis dimension for given bounding box
	 * @param boundingBox bounding box
	 * @return max axis dimension
	 */
	static float computeMaxAxisDimension(BoundingBox* boundingBox);

	/** 
	 * Creates a ground plate
	 * @param width width
	 * @param depth depth
	 * @param y float y
	 * @return ground model
	 */
	static Model* createGroundModel(float width, float depth, float y);

	/** 
	 * Set up entity in given engine with look from rotations and scale
	 * @param entity entity
	 * @param engine engine
	 * @param lookFromRotations look from rotations
	 * @param camScale scale
	 * @param lodLevel lod level
	 */
	static void setupEntity(LevelEditorEntity* entity, Engine* engine, const Transformations& lookFromRotations, float camScale, int lodLevel = 1);

	/** 
	 * Get relative resources file name
	 * @param gameRoot game root
	 * @param fileName file name
	 * @return relative resources file name
	 */
	static const string getRelativeResourcesFileName(const string& gameRoot, const string& fileName);

	/** 
	 * Get game root path
	 * @param fileName file name
	 * @return game root path
	 */
	static const string getGameRootPath(const string& fileName);

	/** 
	 * Get path
	 * @param fileName file name
	 * @return path
	 */
	static const string getPath(const string& fileName);

	/** 
	 * Get file name of given path
	 * @param fileName file name
	 * @return file name
	 */
	static const string getFileName(const string& fileName);

	/**
	 * Load settings
	 * @param application application
	 */
	static void loadSettings(Application* application);
};
