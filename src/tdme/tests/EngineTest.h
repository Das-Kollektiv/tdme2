
#pragma once

#include <array>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Transformations.h>
#include <tdme/application/Application.h>
#include <tdme/application/ApplicationInputEventsHandler.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/tests/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::array;
using std::vector;

using tdme::application::Application;
using tdme::application::ApplicationInputEventsHandler;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::Object3D;
using tdme::engine::Transformations;
using tdme::engine::model::Model;

/** 
 * Engine test
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::tests::EngineTest final
	: public Application, public virtual ApplicationInputEventsHandler
{

private:
	Engine* engine {  };
	Engine* osEngine {  };
	vector<Object3D*> players {  };
	Object3D* cube {  };
	Transformations circleTransformations {  };

public: /* package */
	Entity* entityClicked {  };

private:
	bool mouseClicked;
	array<int, 2> mouseClickedXY {  };
	bool keyLeft {  };
	bool keyRight {  };
	bool keyUp {  };
	bool keyW {  };
	bool keyA {  };
	bool keyS {  };
	bool keyD {  };

public:

	/** 
	 * Main
	 * @param argc argument count
	 * @param argv argument values
	 */
	static void main(int argc, char** argv);

private:

	/** 
	 * Create wall model
	 * @return
	 */
	Model* createWallModel();

public:
	void display() override;

private:

	/** 
	 * Do player control
	 * @param idx idx
	 * @param keyLeft key left
	 * @param keyRight key right
	 * @param keyUp key up
	 */
	void doPlayerControl(int32_t idx, bool keyLeft, bool keyRight, bool keyUp);

public:
	void dispose() override;
	void initialize() override;
	void reshape(int32_t width, int32_t height) override;

	void onKeyDown (unsigned char key, int x, int y) override;
	void onKeyUp(unsigned char key, int x, int y) override;
	void onSpecialKeyDown (int key, int x, int y) override;
	void onSpecialKeyUp(int key, int x, int y) override;
	void onMouseDragged(int x, int y) override;
	void onMouseMoved(int x, int y) override;
	void onMouseButton(int button, int state, int x, int y) override;
	void onMouseWheel(int button, int direction, int x, int y) override;

	/**
	 * Engine test
	 */
	EngineTest();
};
