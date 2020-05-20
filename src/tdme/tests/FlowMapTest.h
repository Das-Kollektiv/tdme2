#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Object3D.h>
#include <tdme/engine/model/fwd-tdme.h>
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
using tdme::engine::model::Model;
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
class tdme::tests::FlowMapTest final
	: public virtual Application
{
private:
	World* world { nullptr };
	Engine* engine { nullptr };
	LevelEditorLevel level;
	LevelEditorEntity* playerModelEntity { nullptr };
	Model* emptyModel { nullptr };
	Object3D* startPointObject { nullptr };
	Object3D* endPointObject { nullptr };
	PathFinding* pathFinding { nullptr };
	vector<Vector3> pathPositions;
	vector<Vector3> path;
	int64_t timeLastUpdate;
	PathFinding::FlowMap* flowMap { nullptr };
	int32_t frames;

	/**
	 * Do path finding
	 */
	void doPathFinding();
public:

	/** 
	 * Main
	 * @param argc argument count
	 * @param argv argument values
	 */
	static void main(int argc, char** argv);
public:
	void display() override;
	void dispose() override;
	void initialize() override;
	void reshape(int32_t width, int32_t height) override;

	/**
	 * Public constructor
	 */
	FlowMapTest();
};
