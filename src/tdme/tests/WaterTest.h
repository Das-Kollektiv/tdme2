#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/application/Application.h>
#include <tdme/tests/fwd-tdme.h>

using tdme::application::Application;
using tdme::engine::Engine;

/** 
 * Water shader test
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::tests::WaterTest final
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
	void display() override;
	void dispose() override;
	void initialize() override;
	void reshape(int32_t width, int32_t height) override;

	/**
	 * Public constructor
	 */
	WaterTest();
};
