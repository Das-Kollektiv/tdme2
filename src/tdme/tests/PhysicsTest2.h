// Generated from /tdme/src/tdme/tests/PhysicsTest2.java

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/newt/event/fwd-tdme.h>
#include <com/jogamp/opengl/fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/tests/fwd-tdme.h>
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
using com::jogamp::opengl::GLAutoDrawable;
using java::io::Serializable;
using java::lang::CharSequence;
using java::lang::Comparable;
using java::lang::String;
using tdme::engine::Engine;
using tdme::engine::physics::World;

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
 * Engine with physics test 2
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::tests::PhysicsTest2 final
	: public virtual Object
	, public GLEventListener
	, public MouseListener
	, public KeyListener
	, public WindowListener
{

public:
	typedef Object super;

private:
	static constexpr int32_t RIGID_TYPEID_STANDARD { 1 };
	static constexpr int32_t BOX_COUNT { 4 };
	Engine* engine {  };
	World* world {  };

public:

	/** 
	 * Main
	 * @param args
	 */
	static void main(StringArray* args);
protected:

	/** 
	 * Public constructor
	 */
	void ctor();

public:
	void display(GLAutoDrawable* drawable) override;
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
	void windowDestroyNotify(WindowEvent* arg0) override;
	void windowDestroyed(WindowEvent* arg0) override;
	void windowGainedFocus(WindowEvent* arg0) override;
	void windowLostFocus(WindowEvent* arg0) override;
	void windowMoved(WindowEvent* arg0) override;
	void windowRepaint(WindowUpdateEvent* arg0) override;
	void windowResized(WindowEvent* arg0) override;
	void mouseWheelMoved(MouseEvent* arg0) override;

	// Generated
	PhysicsTest2();
protected:
	PhysicsTest2(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
