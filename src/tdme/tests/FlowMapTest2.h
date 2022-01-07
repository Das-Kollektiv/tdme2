#pragma once

#include <array>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/application/InputEventHandler.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/scene/fwd-tdme.h>
#include <tdme/engine/Object3D.h>
#include <tdme/math/Vector3.h>
#include <tdme/tests/fwd-tdme.h>
#include <tdme/utilities/FlowMap.h>
#include <tdme/utilities/PathFinding.h>

using std::array;
using std::vector;

using tdme::application::Application;
using tdme::application::InputEventHandler;
using tdme::engine::model::Model;
using tdme::engine::physics::Body;
using tdme::engine::physics::World;
using tdme::engine::prototype::Prototype;
using tdme::engine::scene::Scene;
using tdme::engine::Engine;
using tdme::engine::Object3D;
using tdme::math::Vector3;
using tdme::utilities::FlowMap;
using tdme::utilities::PathFinding;

/**
 * Flow map test 2
 * @author andreas.drewke
 * @version $Id$
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
		Object3D* object { nullptr };
		Body* rigidBody { nullptr };
		bool finished { false };
	};
	World* world { nullptr };
	Engine* engine { nullptr };
	Scene* scene { nullptr };
	Prototype* playerModelPrototype { nullptr };
	Model* emptyModel { nullptr };
	Model* formationLinePrototype { nullptr };
	PathFinding* pathFinding { nullptr };
	int64_t timeLastUpdate;
	FlowMap* flowMap { nullptr };
	bool pause { false };
	vector<Vector3> path;
	vector<CombatUnit> combatUnits;
	float formationYRotationAngle { 0.0f };
	Vector3 formationMovement;

	array<Transformations, 11> combatUnitTransformations;
	array<Transformations, 11> combatUnitFormationTransformations;

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
	 */
	static void main(int argc, char** argv);

	// overriden methods
	void display() override;
	void dispose() override;
	void initialize() override;
	void reshape(int32_t width, int32_t height) override;
	void onChar(unsigned int key, int x, int y) override;
	void onKeyDown (unsigned char key, int keyCode, int x, int y) override;
	void onKeyUp(unsigned char key, int keyCode, int x, int y) override;
	void onMouseDragged(int x, int y) override;
	void onMouseMoved(int x, int y) override;
	void onMouseButton(int button, int state, int x, int y) override;
	void onMouseWheel(int button, int direction, int x, int y) override;

};
