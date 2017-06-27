// Generated from /tdme/src/tdme/tools/viewer/TDMEViewer.java

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/newt/event/fwd-tdme.h>
#include <com/jogamp/newt/opengl/fwd-tdme.h>
#include <com/jogamp/opengl/fwd-tdme.h>
#include <com/jogamp/opengl/util/fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/tools/viewer/fwd-tdme.h>
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
using com::jogamp::opengl::util::FPSAnimator;
using java::io::Serializable;
using java::lang::CharSequence;
using java::lang::Comparable;
using java::lang::String;
using tdme::engine::Engine;
using tdme::tools::shared::views::PopUps;
using tdme::tools::shared::views::View;

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
 * TDME Level Editor
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::tools::viewer::TDMEViewer final
	: public virtual Object
	, public GLEventListener
	, public WindowListener
{

public:
	typedef Object super;

private:
	static String* VERSION;
	static TDMEViewer* instance;
	Engine* engine {  };
	GLWindow* glWindow {  };
	FPSAnimator* animator {  };
	View* view {  };
	bool viewInitialized {  };
	View* viewNew {  };
	bool quitRequested {  };
	PopUps* popUps {  };

public:

	/** 
	 * @param args
	 */
	static void main(StringArray* args);
protected:

	/** 
	 * Public constructor
	 * @param gl window
	 * @param animator
	 * @param model file name
	 */
	void ctor(GLWindow* glWindow, FPSAnimator* animator, String* modelFileName);

public:

	/** 
	 * @return level editor instance
	 */
	static TDMEViewer* getInstance();

	/** 
	 * Set up new view
	 * @param view
	 */
	void setView(View* view);

	/** 
	 * @return current view
	 */
	View* getView();

	/** 
	 * Request to exit the viewer
	 */
	void quit();

	/** 
	 * Renders the scene 
	 */
	void display(GLAutoDrawable* drawable) override;

	/** 
	 * Shutdown tdme viewer
	 */
	void dispose(GLAutoDrawable* drawable) override;

	/** 
	 * Initialize tdme level editor
	 */
	void init_(GLAutoDrawable* drawable) override;

	/** 
	 * reshape tdme level editor
	 */
	void reshape(GLAutoDrawable* drawable, int32_t x, int32_t y, int32_t width, int32_t height) override;
	void windowDestroyNotify(WindowEvent* arg0) override;
	void windowDestroyed(WindowEvent* arg0) override;
	void windowGainedFocus(WindowEvent* arg0) override;
	void windowLostFocus(WindowEvent* arg0) override;
	void windowMoved(WindowEvent* arg0) override;
	void windowRepaint(WindowUpdateEvent* arg0) override;
	void windowResized(WindowEvent* arg0) override;

	// Generated
	TDMEViewer(GLWindow* glWindow, FPSAnimator* animator, String* modelFileName);
protected:
	TDMEViewer(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static void clinit();

private:
	void init();
	virtual ::java::lang::Class* getClass0();
};
