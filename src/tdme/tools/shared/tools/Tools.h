// Generated from /tdme/src/tdme/tools/shared/tools/Tools.java

#pragma once

#include <array>
#include <string>

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/tools/fwd-tdme.h>
#include <java/lang/Object.h>

using std::array;
using std::wstring;

using java::lang::String;
using tdme::engine::Engine;
using tdme::engine::Light;
using tdme::engine::Transformations;
using tdme::engine::model::Color4;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingVolume;
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
	static Transformations* oseLookFromRotations;
	static float oseScale;

public:

	/** 
	 * Formats a float to a human readable format
	 * @param value
	 * @return value as string
	 */
	static String* formatFloat(float value);

	/** 
	 * Formats a vector3 to a human readable format
	 * @param value
	 * @return value as string
	 */
	static String* formatVector3(const Vector3& value);

	/** 
	 * Formats a color4 to a human readable format
	 * @param value
	 * @return value as string
	 */
	static String* formatColor4(Color4* value);

	/** 
	 * Convert string to array
	 * @param text
	 * @param array
	 */
	static void convertToArray(String* text, array<float, 3>& array) /* throws(NumberFormatException) */;

	/**
	 * Convert string to array
	 * @param text
	 * @param array
	 */
	static void convertToArray(String* text, array<float, 4>* array) /* throws(NumberFormatException) */;

	/**
	 * Convert string to array
	 * @param text
	 * @param array
	 */
	static void convertToArray(String* text, array<float, 4>& array) /* throws(NumberFormatException) */;

	/** 
	 * Convert to vector 3
	 * @param text
	 * @return vector3
	 */
	static Vector3 convertToVector3(String* text) /* throws(NumberFormatException) */;

	/** 
	 * Convert to vector 4
	 * @param text
	 * @return vector4
	 */
	static Vector4 convertToVector4(String* text) /* throws(NumberFormatException) */;

	/** 
	 * Convert to color 4
	 * @param text
	 * @return color4
	 */
	static Color4* convertToColor4(String* text) /* throws(NumberFormatException) */;

	/** 
	 * Convert string to float
	 * @param text
	 * @return float
	 */
	static float convertToFloat(String* text) /* throws(NumberFormatException) */;

	/** 
	 * Convert string to int
	 * @param text
	 * @return int
	 */
	static int32_t convertToInt(String* text) /* throws(NumberFormatException) */;

	/** 
	 * Convert string to int
	 * @param text
	 * @return int
	 */
	static int32_t convertToIntSilent(String* text);

	/** 
	 * Set up given engine light with default light
	 * @param light
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
	 * @param model
	 */
	static void oseThumbnail(LevelEditorEntity* model);

	/** 
	 * Compute max axis dimension b given bounding box
	 * @param model bounding box
	 * @return max axis dimension
	 */
	static float computeMaxAxisDimension(BoundingVolume* modelBoundingVolume);

	/** 
	 * Creates a ground plate
	 * @param width
	 * @param depth
	 * @param float y
	 * @return ground model
	 */
	static Model* createGroundModel(float width, float depth, float y);

	/** 
	 * Set up entity in given engine with look from rotations and scale
	 * @param entity
	 * @param engine
	 * @param look from rotations
	 * @param scale
	 */
	static void setupEntity(LevelEditorEntity* entity, Engine* engine, Transformations* lookFromRotations, float scale);

	/** 
	 * Get relative resources file name
	 * @param game root
	 * @param file name
	 * @return relative resources file name
	 */
	static const wstring getRelativeResourcesFileName(const wstring& gameRoot, const wstring& fileName);

	/** 
	 * Get game root path
	 * @param file name
	 * @return game root path
	 */
	static const wstring getGameRootPath(const wstring& fileName);

	/** 
	 * Get path
	 * @param file name
	 * @return path
	 */
	static const wstring getPath(const wstring& fileName);

	/** 
	 * Get file name of given path
	 * @param file name
	 * @return file name
	 */
	static const wstring getFileName(const wstring& fileName);
};
