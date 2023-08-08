#pragma once

#include <memory>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/scene/fwd-tdme.h>
#include <tdme/engine/Object.h>
#include <tdme/math/Vector3.h>
#include <tdme/tests/fwd-tdme.h>
#include <tdme/utilities/FlowMap.h>
#include <tdme/utilities/PathFinding.h>

using std::unique_ptr;
using std::vector;

using tdme::application::Application;
using tdme::engine::model::Model;
using tdme::engine::physics::World;
using tdme::engine::prototype::Prototype;
using tdme::engine::scene::Scene;
using tdme::engine::Engine;
using tdme::engine::Object;
using tdme::math::Vector3;
using tdme::utilities::FlowMap;
using tdme::utilities::PathFinding;

/**
 * Engine with physics test 2
 * @author andreas.drewke
 */
class tdme::tests::FlowMapTest final
	: public virtual Application
{
private:
	unique_ptr<World> world;
	Engine* engine { nullptr };
	unique_ptr<Scene> scene;
	unique_ptr<Prototype> playerModelPrototype;
	unique_ptr<Model> emptyModel;
	Object* startPlayerObject { nullptr };
	Vector3 startPlayerCellDirection;
	Vector3 startPlayerCellPosition;
	Object* endPlayerObject1 { nullptr };
	Object* endPlayerObject2 { nullptr };
	unique_ptr<PathFinding> pathFinding;
	vector<Vector3> pathPositions;
	int64_t timeLastUpdate;
	FlowMap* flowMap { nullptr };

	/**
	 * Do path finding
	 */
	void doPathFinding();

public:
	// forbid class copy
	FORBID_CLASS_COPY(FlowMapTest)

	/**
	 * Public constructor
	 */
	FlowMapTest();

	/**
	 * Public denstructor
	 */
	~FlowMapTest();

	/**
	 * Main
	 * @param argc argument count
	 * @param argv argument values
	 */
	static void main(int argc, char** argv);

	// overridden methods
	void display() override;
	void dispose() override;
	void initialize() override;
	void reshape(int32_t width, int32_t height) override;
};
