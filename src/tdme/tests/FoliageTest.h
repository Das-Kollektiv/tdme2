#pragma once

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/application/InputEventHandler.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/tests/fwd-tdme.h>
#include <tdme/utilities/ObjectDeleter.h>

using tdme::application::Application;
using tdme::engine::model::Model;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::Engine;
using tdme::utilities::ObjectDeleter;

/**
 * Foliage test
 * @author andreas.drewke
 */
class tdme::tests::FoliageTest final
	: public virtual Application, public virtual InputEventHandler
{
private:
	Engine* engine { nullptr };

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

	ObjectDeleter<Model> modelDeleter;
	ObjectDeleter<BoundingVolume> bvDeleter;

public:

	/**
	 * Main
	 * @param argc argument count
	 * @param argv argument values
	 */
	static void main(int argc, char** argv);

	// forbid class copy
	CLASS_FORBID_COPY(FoliageTest)

	/**
	 * Public constructor
	 */
	FoliageTest();

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
