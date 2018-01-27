
#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/tests/fwd-tdme.h>

using tdme::application::Application;
using tdme::engine::Engine;
using tdme::engine::physics::World;

/** 
 * Engine with physics test 2
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::tests::PhysicsTest2 final
	: public virtual Application
{
private:
	static constexpr uint16_t RIGID_TYPEID_STATIC { 1 };
	static constexpr uint16_t RIGID_TYPEID_DYNAMIC { 2 };
	static constexpr int32_t BOX_COUNT { 4 };
	Engine* engine {  };
	World* world {  };

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
	PhysicsTest2();
};
