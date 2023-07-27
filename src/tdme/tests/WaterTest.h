#pragma once

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/scene/fwd-tdme.h>
#include <tdme/tests/fwd-tdme.h>
#include <tdme/utilities/ObjectDeleter.h>

using tdme::application::Application;
using tdme::engine::model::Model;
using tdme::engine::prototype::Prototype;
using tdme::engine::scene::Scene;
using tdme::engine::Engine;
using tdme::utilities::ObjectDeleter;

/**
 * Water shader test
 * @author andreas.drewke
 */
class tdme::tests::WaterTest final
	: public virtual Application, public virtual InputEventHandler
{
private:
	Engine* engine { nullptr };

	Prototype* skySpherePrototype { nullptr };
	Prototype* skyDomePrototype { nullptr };
	Prototype* skyPanoramaPrototype { nullptr };
	Prototype* spherePrototype { nullptr };

	Scene* scene { nullptr };

	float skyDomeTranslation { 0.0f };

	bool keyLeft { false };
	bool keyRight { false };
	bool keyUp { false };
	bool keyDown { false };
	bool keyW { false };
	bool keyA { false };
	bool keyS { false };
	bool keyD { false };
	bool keyMinus { false };
	bool keyPlus { false };
	float camRotationY { 0.0f };
	float camRotationX { 0.0f };

public:

	/**
	 * Main
	 * @param argc argument count
	 * @param argv argument values
	 */
	static void main(int argc, char** argv);

	// forbid class copy
	FORBID_CLASS_COPY(WaterTest)

	/**
	 * Public constructor
	 */
	WaterTest();

	// overridden methods
	void display() override;
	void dispose() override;
	void initialize() override;
	void reshape(int32_t width, int32_t height) override;
	void onChar(int key, int x, int y) override;
	void onKeyDown(int key, int keyCode, int x, int y, bool repeat, int modifiers) override;
	void onKeyUp(int key, int keyCode, int x, int y) override;
	void onMouseDragged(int x, int y) override;
	void onMouseMoved(int x, int y) override;
	void onMouseButton(int button, int state, int x, int y) override;
	void onMouseWheel(int button, int direction, int x, int y) override;
};
