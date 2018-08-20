
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
	static constexpr int32_t RIGID_TYPEID_STANDARD { 1 };
	static constexpr int32_t BOX_COUNT { 4 };
	Engine* engine {  };
	World* world {  };

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
	PhysicsTest2();
};
