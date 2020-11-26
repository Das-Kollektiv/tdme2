#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/application/Application.h>
#include <tdme/utilities/ObjectDeleter.h>
#include <tdme/tests/fwd-tdme.h>
#include <tdme/tools/shared/model/LevelEditorEntity.h>
#include <tdme/tools/shared/model/LevelEditorLevel.h>

using tdme::application::Application;
using tdme::engine::Engine;
using tdme::engine::model::Model;
using tdme::tools::shared::model::LevelEditorEntity;
using tdme::tools::shared::model::LevelEditorLevel;
using tdme::utilities::ObjectDeleter;

/**
 * Water shader test
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::tests::WaterTest final
	: public virtual Application, public virtual InputEventHandler
{
private:
	Engine* engine { nullptr };

	LevelEditorEntity* skySphereEntity { nullptr };
	LevelEditorEntity* skyDomeEntity { nullptr };
	LevelEditorEntity* skyPanoramaEntity { nullptr };
	LevelEditorEntity* sphereEntity { nullptr };

	LevelEditorLevel level;

	float skyDomeTranslation { 0.0f };

	bool keyLeft { false };
	bool keyRight { false };
	float rotationY { 180.0f };

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
	void onChar(unsigned int key, int x, int y) override;
	void onKeyDown (unsigned char key, int x, int y) override;
	void onKeyUp(unsigned char key, int x, int y) override;
	void onSpecialKeyDown (int key, int x, int y) override;
	void onSpecialKeyUp(int key, int x, int y) override;
	void onMouseDragged(int x, int y) override;
	void onMouseMoved(int x, int y) override;
	void onMouseButton(int button, int state, int x, int y) override;
	void onMouseWheel(int button, int direction, int x, int y) override;
};
