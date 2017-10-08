
#pragma once

#include <tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Application.h>
#include <tdme/engine/ApplicationInputEventsHandler.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/tests/fwd-tdme.h>

using tdme::engine::Application;
using tdme::engine::ApplicationInputEventsHandler;
using tdme::engine::Engine;
using tdme::engine::physics::World;

/** 
 * Engine with physics test 3
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::tests::PhysicsTest3 final
	: public virtual Application, public virtual ApplicationInputEventsHandler
{
private:
	static constexpr int32_t RIGID_TYPEID_STANDARD { 1 };
	static constexpr int32_t BOX_COUNT { 5 };
	static constexpr int32_t BOXSTACK_COUNT { 2 };
	static constexpr int32_t CAPSULE_COUNT { 10 };
	static constexpr int32_t SPHERE_COUNT { 10 };
	Engine* engine {  };
	bool keyLeft {  };
	bool keyRight {  };
	bool keyUp {  };
	bool keyDown {  };
	bool keyW {  };
	bool keyA {  };
	bool keyS {  };
	bool keyD {  };
	World* world {  };

public:

	/** 
	 * Main
	 * @param argument count
	 * @param argument values
	 */
	static void main(int argc, char** argv);

public:

	/** 
	 * Display
	 */
	void display();
	void dispose();
	void initialize();
	void reshape(int32_t width, int32_t height);

	void onKeyDown (unsigned char key, int x, int y) override;
	void onKeyUp(unsigned char key, int x, int y) override;
	void onSpecialKeyDown (int key, int x, int y) override;
	void onSpecialKeyUp(int key, int x, int y) override;
	void onMouseDragged(int x, int y) override;
	void onMouseMoved(int x, int y) override;
	void onMouseButton(int button, int state, int x, int y) override;

	/**
	 * Public constructor
	 */
	PhysicsTest3();
};
