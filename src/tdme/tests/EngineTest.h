// Generated from /tdme/src/tdme/tests/EngineTest.java

#pragma once

#include <array>
#include <vector>

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Application.h>
#include <tdme/engine/ApplicationInputEventsHandler.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/tests/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::array;
using std::vector;

using tdme::engine::Application;
using tdme::engine::ApplicationInputEventsHandler;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::Object3D;
using tdme::engine::Transformations;
using tdme::engine::model::Model;
using tdme::engine::physics::CollisionResponse;
using tdme::engine::primitives::BoundingVolume;

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
	CollisionResponse* collision {  };
	vector<Object3D*> players {  };
	vector<Object3D*> playersBoundingVolumeModel {  };
	BoundingVolume* playerBoundingVolume {  };
	Model* playerBoundingVolumeModel {  };
	vector<BoundingVolume*> playerBoundingVolumesTransformed {  };
	Object3D* cube {  };
	Model* cubeBoundingVolumeModel {  };
	BoundingVolume* cubeBoundingVolume {  };
	BoundingVolume* cubeBoundingVolumeTransformed {  };
	BoundingVolume* barrelBoundingVolume {  };
	BoundingVolume* barrelBoundingVolumeTransformed {  };
	Transformations* circleTransformations {  };

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
	 * @param argument count
	 * @param argument values
	 */
	static void main(int argc, char** argv);

private:

	/** 
	 * Create wall model
	 * @return
	 */
	Model* createWallModel();

public:
	void display();

private:

	/** 
	 * Do player control
	 * @param idx
	 * @param key left
	 * @param key right
	 * @param key up
	 */
	void doPlayerControl(int32_t idx, bool keyLeft, bool keyRight, bool keyUp);

public:
	void dispose();
	void initialize() ;
	void reshape(int32_t width, int32_t height);

	void onKeyDown (unsigned char key, int x, int y) override;
	void onKeyUp(unsigned char key, int x, int y) override;
	void onSpecialKeyDown (int key, int x, int y) override;
	void onSpecialKeyUp(int key, int x, int y) override;
	void onMouseDragged(int x, int y) override;
	void onMouseMoved(int x, int y) override;
	void onMouseButton(int button, int state, int x, int y) override;

	/**
	 * Engine test
	 */
	EngineTest();
};
