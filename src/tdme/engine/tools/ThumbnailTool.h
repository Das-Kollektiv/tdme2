#pragma once

#include <array>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/engine/tools/fwd-tdme.h>

using std::array;
using std::string;
using std::vector;

using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::prototype::Prototype;
using tdme::engine::Engine;
using tdme::engine::Transform;
using tdme::math::Vector3;
using tdme::engine::tools::CameraRotationInputHandler;

/**
 * Editor tools
 * @author Andreas Drewke
 */
class tdme::engine::tools::ThumbnailTool final
{
private:
	STATIC_DLL_IMPEXT static Engine* osEngine;

	struct ToolsShutdown {
		~ToolsShutdown();
	};

	STATIC_DLL_IMPEXT static ToolsShutdown toolsShutdown;

public:
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
	 * Set up given engine light with default light
	 * @param light light
	 */
	static void setDefaultLight(Light* light);

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

};
