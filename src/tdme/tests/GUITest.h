
#pragma once

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Application.h>
#include <tdme/tests/fwd-tdme.h>

using tdme::engine::Application;
using tdme::engine::Engine;

using tdme::engine::Application;

/** 
 * GUI Test
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tests::GUITest final
	: public virtual Application
{
	friend class GUITest_init_1;
	friend class GUITest_init_2;

private:
	Engine* engine {  };

public:
	void initialize();
	void dispose();
	void reshape(int32_t width, int32_t height);
	void display();

	/** 
	 * Main
	 * @param argument count
	 * @param argument values
	 */
	static void main(int argc, char** argv);

	/**
	 * Public constructor
	 */
	GUITest();
};
