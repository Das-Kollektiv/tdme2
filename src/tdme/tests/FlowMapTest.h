#pragma once

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
	World* world { nullptr };
	Engine* engine { nullptr };
	Scene* scene { nullptr };
	Prototype* playerModelPrototype { nullptr };
	Model* emptyModel { nullptr };
	Object* startPlayerObject { nullptr };
	Vector3 startPlayerCellDirection;
	Vector3 startPlayerCellPosition;
	Object* endPlayerObject1 { nullptr };
	Object* endPlayerObject2 { nullptr };
	PathFinding* pathFinding { nullptr };
	vector<Vector3> pathPositions;
	int64_t timeLastUpdate;
	FlowMap* flowMap { nullptr };

	/**
	 * Do path finding
	 */
	void doPathFinding();

public:
	// forbid class copy
	CLASS_FORBID_COPY(FlowMapTest)

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
