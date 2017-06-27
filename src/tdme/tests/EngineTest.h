// Generated from /tdme/src/tdme/tests/EngineTest.java

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/newt/event/fwd-tdme.h>
#include <com/jogamp/newt/opengl/fwd-tdme.h>
#include <com/jogamp/opengl/fwd-tdme.h>
#include <com/jogamp/opengl/util/fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/tests/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>
#include <com/jogamp/opengl/GLEventListener.h>
#include <com/jogamp/newt/event/MouseListener.h>
#include <com/jogamp/newt/event/KeyListener.h>
#include <com/jogamp/newt/event/WindowListener.h>

using java::lang::Object;
using com::jogamp::opengl::GLEventListener;
using com::jogamp::newt::event::MouseListener;
using com::jogamp::newt::event::KeyListener;
using com::jogamp::newt::event::WindowListener;
using com::jogamp::newt::event::KeyEvent;
using com::jogamp::newt::event::MouseEvent;
using com::jogamp::newt::event::WindowEvent;
using com::jogamp::newt::event::WindowUpdateEvent;
using com::jogamp::newt::opengl::GLWindow;
using com::jogamp::opengl::GLAutoDrawable;
using com::jogamp::opengl::util::FPSAnimator;
using java::io::Serializable;
using java::lang::CharSequence;
using java::lang::Comparable;
using java::lang::String;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::Object3D;
using tdme::engine::Transformations;
using tdme::engine::model::Model;
using tdme::engine::physics::CollisionResponse;
using tdme::engine::primitives::BoundingVolume;
using tdme::utils::_ArrayList;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::CharSequence, ObjectArray > CharSequenceArray;
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::String, ObjectArray, ::java::io::SerializableArray, ComparableArray, CharSequenceArray > StringArray;
}  // namespace lang
}  // namespace java

using java::io::SerializableArray;
using java::lang::CharSequenceArray;
using java::lang::ComparableArray;
using java::lang::ObjectArray;
using java::lang::StringArray;

struct default_init_tag;

/** 
 * Engine test
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::tests::EngineTest final
	: public virtual Object
	, public GLEventListener
	, public MouseListener
	, public KeyListener
	, public WindowListener
{

public:
	typedef Object super;

private:
	Engine* engine {  };
	Engine* osEngine {  };
	CollisionResponse* collision {  };
	_ArrayList* players {  };
	_ArrayList* playersBoundingVolumeModel {  };
	BoundingVolume* playerBoundingVolume {  };
	Model* playerBoundingVolumeModel {  };
	_ArrayList* playerBoundingVolumesTransformed {  };
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
	int32_tArray* mouseClicked_ {  };
	bool keyLeft {  };
	bool keyRight {  };
	bool keyUp {  };
	bool keyW {  };
	bool keyA {  };
	bool keyS {  };
	bool keyD {  };

public:

	/** 
	 * @param args
	 */
	static void main(StringArray* args);
protected:

	/** 
	 * Engine test
	 * @param gl window
	 */
	void ctor(GLWindow* glWindow, FPSAnimator* fpsAnimator);

private:

	/** 
	 * Create wall model
	 * @return
	 */
	Model* createWallModel();

public:
	void display(GLAutoDrawable* drawable) override;

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
	void dispose(GLAutoDrawable* drawable) override;
	void init_(GLAutoDrawable* drawable) override;
	void reshape(GLAutoDrawable* drawable, int32_t x, int32_t y, int32_t width, int32_t height) override;
	void mouseClicked(MouseEvent* e) override;
	void mouseEntered(MouseEvent* e) override;
	void mouseExited(MouseEvent* e) override;
	void mousePressed(MouseEvent* e) override;
	void mouseReleased(MouseEvent* e) override;
	void mouseDragged(MouseEvent* e) override;
	void mouseMoved(MouseEvent* e) override;
	void keyPressed(KeyEvent* e) override;
	void keyReleased(KeyEvent* e) override;
	void mouseWheelMoved(MouseEvent* arg0) override;
	void windowDestroyNotify(WindowEvent* arg0) override;
	void windowDestroyed(WindowEvent* arg0) override;
	void windowGainedFocus(WindowEvent* arg0) override;
	void windowLostFocus(WindowEvent* arg0) override;
	void windowMoved(WindowEvent* arg0) override;
	void windowRepaint(WindowUpdateEvent* arg0) override;
	void windowResized(WindowEvent* arg0) override;

	// Generated
	EngineTest(GLWindow* glWindow, FPSAnimator* fpsAnimator);
protected:
	EngineTest(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
