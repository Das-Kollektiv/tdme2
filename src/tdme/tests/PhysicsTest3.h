#pragma once

#include <memory>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/application/InputEventHandler.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/tests/fwd-tdme.h>
#include <tdme/utilities/ObjectDeleter.h>

using std::make_unique;
using std::unique_ptr;

using tdme::application::Application;
using tdme::application::InputEventHandler;
using tdme::engine::model::Model;
using tdme::engine::physics::World;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::Engine;
using tdme::engine::ObjectModel;
using tdme::utilities::ObjectDeleter;

/**
 * Engine with physics test 3
 * @author andreas.drewke
 */
class tdme::tests::PhysicsTest3 final
	: public virtual Application, public virtual InputEventHandler
{
private:
	static constexpr int32_t RIGID_TYPEID_STANDARD { 1 };
	static constexpr int32_t BOX_COUNT { 5 };
	static constexpr int32_t BOXSTACK_COUNT { 2 };
	static constexpr int32_t CAPSULE_COUNT { 10 };
	static constexpr int32_t SPHERE_COUNT { 10 };
	Engine* engine { nullptr };
	bool keyLeft { false };
	bool keyRight { false };
	bool keyUp { false };
	bool keyDown { false };
	bool keyW { false };
	bool keyA { false };
	bool keyS { false };
	bool keyD { false };
	unique_ptr<World> world;
	ObjectDeleter<Model> modelDeleter;
	ObjectDeleter<BoundingVolume> bvDeleter;
	ObjectDeleter<ObjectModel> objectModelDeleter;

public:

	/**
	 * Main
	 * @param argc argument count
	 * @param argv argument values
	 * @return exit code
	 */
	static int main(int argc, char** argv);

	// forbid class copy
	FORBID_CLASS_COPY(PhysicsTest3)

	/**
	 * Public constructor
	 */
	PhysicsTest3();

	/**
	 * Public destructor
	 */
	~PhysicsTest3();

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
