
#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/application/Application.h>
#include <tdme/tests/fwd-tdme.h>

using tdme::application::Application;
using tdme::engine::Engine;

using tdme::application::Application;

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
	void initialize() override;
	void dispose() override;
	void reshape(int32_t width, int32_t height) override;
	void display() override;

	/** 
	 * Main
	 * @param argc argument count
	 * @param argv argument values
	 */
	static void main(int argc, char** argv);

	/**
	 * Public constructor
	 */
	GUITest();
};
