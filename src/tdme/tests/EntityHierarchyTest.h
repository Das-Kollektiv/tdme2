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
 * Engine entity hierarchy test
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::tests::EntityHierarchyTest final
	: public virtual Application
{
private:
	Engine* engine {  };

public:

	/** 
	 * Main
	 * @param argc argument count
	 * @param argv argument values
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
	EntityHierarchyTest();
};
