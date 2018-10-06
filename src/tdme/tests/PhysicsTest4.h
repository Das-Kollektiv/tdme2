#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/application/Application.h>
#include <tdme/application/InputEventHandler.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/tests/fwd-tdme.h>

using tdme::application::Application;
using tdme::application::InputEventHandler;
using tdme::engine::Engine;
using tdme::engine::physics::World;

/** 
 * Engine with physics test 3
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::tests::PhysicsTest4 final
	: public virtual Application, public virtual InputEventHandler
{
private:
	static constexpr int32_t RIGID_TYPEID_STANDARD { 1 };
	Engine* engine {  };
	bool keyLeft {  };
	bool keyRight {  };
	bool keyUp {  };
	bool keyDown {  };
	World* world {  };

public:

	/** 
	 * Main
	 * @param argc argument count
	 * @param argv argument values
	 */
	static void main(int argc, char** argv);

public:

	/** 
	 * Display
	 */
	void display() override;
	void dispose() override;
	void initialize() override;
	void reshape(int32_t width, int32_t height) override;

	// override methods
	void onKeyDown (unsigned char key, int x, int y) override;
	void onKeyUp(unsigned char key, int x, int y) override;
	void onSpecialKeyDown (int key, int x, int y) override;
	void onSpecialKeyUp(int key, int x, int y) override;
	void onMouseDragged(int x, int y) override;
	void onMouseMoved(int x, int y) override;
	void onMouseButton(int button, int state, int x, int y) override;
	void onMouseWheel(int button, int direction, int x, int y) override;

	/**
	 * Public constructor
	 */
	PhysicsTest4();
};
