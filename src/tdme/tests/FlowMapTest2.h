#pragma once

#include <array>
#include <memory>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/application/InputEventHandler.h>
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

using std::array;
using std::unique_ptr;
using std::vector;

using tdme::application::Application;
using tdme::application::InputEventHandler;
using tdme::engine::model::Model;
using tdme::engine::physics::Body;
using tdme::engine::physics::World;
using tdme::engine::prototype::Prototype;
using tdme::engine::scene::Scene;
using tdme::engine::Engine;
using tdme::engine::Object;
using tdme::math::Vector3;
using tdme::utilities::FlowMap;
using tdme::utilities::PathFinding;

/**
 * Flow map test 2
 * @author andreas.drewke
 */
class tdme::tests::FlowMapTest2 final
	: public virtual Application, public virtual InputEventHandler
{
private:
	struct CombatUnit {
		int idx;
		int formationIdx;
		int pathFindingNodeIdx;
		Vector3 pathFindingNode;
		Vector3 movementDirection;
		float speed;
		array<Vector3, 60> movementDirectionRing;
		int movementDirectionRingLength;
		int movementDirectionRingIdx;
		vector<Vector3> path;
		int pathIdx;
		Vector3 endPosition;
		float rotationY;
		Object* object { nullptr };
		Body* rigidBody { nullptr };
		bool finished { false };
	};
	unique_ptr<World> world;
	Engine* engine { nullptr };
	unique_ptr<Scene> scene;
	unique_ptr<Prototype> playerModelPrototype;
	unique_ptr<Model> emptyModel;
	unique_ptr<Model> formationLinePrototype;
	unique_ptr<PathFinding> pathFinding;
	int64_t timeLastUpdate;
	FlowMap* flowMap { nullptr };
	bool pause { false };
	vector<Vector3> path;
	vector<CombatUnit> combatUnits;
	float formationYRotationAngle { 0.0f };
	Vector3 formationMovement;

	array<Transform, 11> combatUnitTransform;
	array<Transform, 11> combatUnitFormationTransform;

	bool mouseClicked { false };
	array<int, 2> mouseClickPosition;

	Vector3 startPosition;
	Vector3 endPosition;

	/**
	 * Do path finding
	 * @param endPosition endPosition
	 */
	void doPathFinding(const Vector3& endPosition);

public:
	// forbid class copy
	FORBID_CLASS_COPY(FlowMapTest2)

	/**
	 * Public constructor
	 */
	FlowMapTest2();

	/**
	 * Public denstructor
	 */
	~FlowMapTest2();

	/**
	 * Main
	 * @param argc argument count
	 * @param argv argument values
	 * @returns exit code
	 */
	static int main(int argc, char** argv);

	// overridden methods
	void display() override;
	void dispose() override;
	void initialize() override;
	void reshape(int32_t width, int32_t height) override;
	void onChar(int key, int x, int y) override;
	void onKeyDown(int key, int keyCode, int x, int y, bool repeat, int modifiers) override;
	void onKeyUp(int key, int keyCode, int x, int y) override;
	void onMouseDragged(int x, int y) override;
	void onMouseMoved(int x, int y) override;
	void onMouseButton(int button, int state, int x, int y) override;
	void onMouseWheel(int button, int direction, int x, int y) override;

};
