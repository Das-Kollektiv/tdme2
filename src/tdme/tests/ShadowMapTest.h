#pragma once

#include <array>
#include <memory>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/application/InputEventHandler.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/scene/fwd-tdme.h>
#include <tdme/tests/fwd-tdme.h>

using std::array;
using std::unique_ptr;
using std::vector;

using tdme::application::Application;
using tdme::application::InputEventHandler;
using tdme::engine::physics::World;
using tdme::engine::scene::Scene;
using tdme::engine::Engine;

/**
 * Shadow map test
 * @author andreas.drewke
 */
class tdme::tests::ShadowMapTest final
	: public virtual Application, public virtual InputEventHandler
{
private:
	unique_ptr<World> world;
	Engine* engine { nullptr };
	unique_ptr<Scene> scene;
	bool pause { false };

	bool mouseClicked { false };
	array<int, 2> mouseClickPosition;

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
	bool keyDot { false };
	bool keyComma { false };
	float camRotationY { 0.0f };
	float camRotationX { 0.0f };
	float t { 0.15f };

public:
	// forbid class copy
	FORBID_CLASS_COPY(ShadowMapTest)

	/**
	 * Public constructor
	 */
	ShadowMapTest();

	/**
	 * Public denstructor
	 */
	~ShadowMapTest();

	/**
	 * Main
	 * @param argc argument count
	 * @param argv argument values
	 * @return exit code
	 */
	static int main(int argc, char** argv);

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
