// Generated from /tdme/src/tdme/tests/GUITest.java

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/newt/event/fwd-tdme.h>
#include <com/jogamp/newt/opengl/fwd-tdme.h>
#include <com/jogamp/opengl/fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/tests/fwd-tdme.h>
#include <java/lang/Object.h>
#include <com/jogamp/opengl/GLEventListener.h>
#include <com/jogamp/newt/event/WindowListener.h>

using java::lang::Object;
using com::jogamp::opengl::GLEventListener;
using com::jogamp::newt::event::WindowListener;
using com::jogamp::newt::event::WindowEvent;
using com::jogamp::newt::event::WindowUpdateEvent;
using com::jogamp::newt::opengl::GLWindow;
using com::jogamp::opengl::GLAutoDrawable;
using java::io::Serializable;
using java::lang::CharSequence;
using java::lang::Comparable;
using java::lang::String;
using tdme::engine::Engine;

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
 * GUI Test
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tests::GUITest
	: public virtual Object
	, public virtual GLEventListener
	, public virtual WindowListener
{

public:
	typedef Object super;

private:
	GLWindow* glWindow {  };
	Engine* engine {  };
protected:

	/** 
	 * Public constructor
	 */
	void ctor(GLWindow* glWindow);

public:
	void init_(GLAutoDrawable* drawable) override;
	void dispose(GLAutoDrawable* drawable) override;
	void reshape(GLAutoDrawable* drawable, int32_t x, int32_t y, int32_t width, int32_t height) override;
	void display(GLAutoDrawable* drawable) override;
	void windowDestroyNotify(WindowEvent* arg0) override;
	void windowDestroyed(WindowEvent* arg0) override;
	void windowGainedFocus(WindowEvent* arg0) override;
	void windowLostFocus(WindowEvent* arg0) override;
	void windowMoved(WindowEvent* arg0) override;
	void windowRepaint(WindowUpdateEvent* arg0) override;
	void windowResized(WindowEvent* arg0) override;

	/** 
	 * @param args
	 */
	static void main(StringArray* args);

	// Generated
	GUITest(GLWindow* glWindow);
protected:
	GUITest(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
	friend class GUITest_init_1;
	friend class GUITest_init_2;
};
