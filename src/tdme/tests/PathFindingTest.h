#pragma once

#include <vector>

#include <tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/tests/fwd-tdme.h>
#include <tdme/tools/shared/model/LevelEditorLevel.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/utils/PathFinding.h>

using std::vector;

using tdme::application::Application;
using tdme::engine::Engine;
using tdme::engine::Object3D;
using tdme::engine::physics::World;
using tdme::math::Vector3;
using tdme::tools::shared::model::LevelEditorLevel;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::utils::PathFinding;

/** 
 * Engine with physics test 2
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::tests::PathFindingTest final
	: public virtual Application
{
private:
	Engine* engine {  };
	World* world {  };
	LevelEditorLevel level;
	LevelEditorEntity* playerModelEntity;
	Object3D* playerObject;
	PathFinding* pathFinding;
	vector<Vector3> pathPositions;
	vector<Vector3> path;
	int64_t timeLastUpdate;
	int32_t pathIdx;
	float playerXDirection;
	float playerZDirection;

	/**
	 * Determine player movement direction
	 */
	void determinePlayerMovementDirection();

	/**
	 * Determine id player completed current step in path
	 * @return completed
	 */
	bool determinePlayerCompletedStepX();
	bool determinePlayerCompletedStepZ();
public:

	/** 
	 * Main
	 * @param argument count
	 * @param argument values
	 */
	static void main(int argc, char** argv);
public:
	void display();
	void dispose();
	void initialize();
	void reshape(int32_t width, int32_t height);

	/**
	 * Public constructor
	 */
	PathFindingTest();
};
