#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/application/Application.h>
#include <tdme/tests/fwd-tdme.h>
#include "../application/InputEventHandler.h"

using tdme::application::Application;
using tdme::engine::Engine;

/** 
 * LOD test
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::tests::LODTest final
	: public virtual Application, public virtual InputEventHandler
{
private:
	static constexpr int32_t RIGID_TYPEID_STANDARD { 1 };
	static constexpr int32_t BOX_COUNT { 4 };
	Engine* engine {  };

	bool keyLeft { false };
	bool keyRight { false };
	bool keyUp { false };
	bool keyDown { false };
	bool keyA { false };
	bool keyD { false };
	bool keyW { false };
	bool keyS { false };

	float camRotationY { 0.0f };

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

	// override methods
	void onKeyDown (unsigned char key, int x, int y) override;
	void onKeyUp(unsigned char key, int x, int y) override;
	void onSpecialKeyDown (int key, int x, int y) override;
	void onSpecialKeyUp(int key, int x, int y) override;
	void onMouseDragged(int x, int y) override;
	void onMouseMoved(int x, int y) override;
	void onMouseButton(int button, int state, int x, int y) override;
	void onMouseWheel(int button, int direction, int x, int y) override;

	/**
	 * Public constructor
	 */
	LODTest();
};
