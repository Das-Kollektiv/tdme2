#pragma once

#include <array>
#include <memory>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/application/InputEventHandler.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/Transform.h>
#include <tdme/tests/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/ObjectDeleter.h>

using std::array;
using std::unique_ptr;
using std::vector;

using tdme::application::Application;
using tdme::application::InputEventHandler;
using tdme::engine::model::Model;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::Object;
using tdme::engine::Transform;
using tdme::utilities::ObjectDeleter;

/**
 * Engine test
 * @author andreas.drewke
 */
class tdme::tests::EngineTest final: public Application, public InputEventHandler
{

private:
	Engine* engine { nullptr };
	unique_ptr<Engine> osEngine;
	vector<Object*> players;
	Object* cube { nullptr };
	Transform circleTransform;
	Entity* entityClicked { nullptr };
	bool mouseClicked { false };
	array<int, 2> mouseClickedXY;
	bool keyLeft { false };
	bool keyRight { false };
	bool keyUp { false };
	bool keyW { false };
	bool keyA { false };
	bool keyD { false };
	ObjectDeleter<Model> modelDeleter;

	/**
	 * Create wall model
	 * @returns
	 */
	Model* createWallModel();

	/**
	 * Do player control
	 * @param idx idx
	 * @param keyLeft key left
	 * @param keyRight key right
	 * @param keyUp key up
	 */
	void doPlayerControl(int32_t idx, bool keyLeft, bool keyRight, bool keyUp);

public:
	/**
	 * Main
	 * @param argc argument count
	 * @param argv argument values
	 * @returns exit code
	 */
	static int main(int argc, char** argv);

	// forbid class copy
	FORBID_CLASS_COPY(EngineTest)

	/**
	 * Engine test constructor
	 */
	EngineTest();

	/**
	 * Engine test destructor
	 */
	~EngineTest();

	// overridden methods
	void display() override;
	void dispose() override;
	void initialize() override;
	void reshape(int32_t width, int32_t height) override;
	void onChar(int key, int x, int y) override;
	void onKeyDown (int key, int keyCode, int x, int y, bool repeat, int modifiers) override;
	void onKeyUp(int key, int keyCode, int x, int y) override;
	void onMouseDragged(int x, int y) override;
	void onMouseMoved(int x, int y) override;
	void onMouseButton(int button, int state, int x, int y) override;
	void onMouseWheel(int button, int direction, int x, int y) override;

};
