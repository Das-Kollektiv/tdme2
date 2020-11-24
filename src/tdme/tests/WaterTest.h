#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/application/Application.h>
#include <tdme/utilities/ObjectDeleter.h>
#include <tdme/tests/fwd-tdme.h>
#include <tdme/tools/shared/model/LevelEditorLevel.h>

using tdme::application::Application;
using tdme::engine::Engine;
using tdme::engine::model::Model;
using tdme::tools::shared::model::LevelEditorLevel;
using tdme::utilities::ObjectDeleter;

/**
 * Water shader test
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::tests::WaterTest final
	: public virtual Application
{
private:
	Engine* engine { nullptr };
	LevelEditorLevel level;

public:

	/**
	 * Main
	 * @param argc argument count
	 * @param argv argument values
	 */
	static void main(int argc, char** argv);

	/**
	 * Public constructor
	 */
	WaterTest();

	// overridden methods
	void display() override;
	void dispose() override;
	void initialize() override;
	void reshape(int32_t width, int32_t height) override;
};
