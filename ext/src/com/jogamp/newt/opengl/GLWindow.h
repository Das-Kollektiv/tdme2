// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/common/util/locks/fwd-tdme.h>
#include <com/jogamp/nativewindow/fwd-tdme.h>
#include <com/jogamp/nativewindow/util/fwd-tdme.h>
#include <com/jogamp/newt/fwd-tdme.h>
#include <com/jogamp/newt/event/fwd-tdme.h>
#include <com/jogamp/newt/opengl/fwd-tdme.h>
#include <com/jogamp/opengl/fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <jogamp/newt/fwd-tdme.h>
#include <jogamp/opengl/GLAutoDrawableBase.h>
#include <com/jogamp/opengl/GLAutoDrawable.h>
#include <com/jogamp/newt/Window.h>
#include <com/jogamp/newt/event/NEWTEventConsumer.h>
#include <com/jogamp/opengl/FPSCounter.h>

using jogamp::opengl::GLAutoDrawableBase;
using com::jogamp::opengl::GLAutoDrawable;
using com::jogamp::newt::Window;
using com::jogamp::newt::event::NEWTEventConsumer;
using com::jogamp::opengl::FPSCounter;
using com::jogamp::common::util::locks::RecursiveLock;
using com::jogamp::nativewindow::AbstractGraphicsConfiguration;
using com::jogamp::nativewindow::CapabilitiesChooser;
using com::jogamp::nativewindow::CapabilitiesImmutable;
using com::jogamp::nativewindow::NativeSurface;
using com::jogamp::nativewindow::NativeWindow;
using com::jogamp::nativewindow::SurfaceUpdatedListener;
using com::jogamp::nativewindow::WindowClosingProtocol_WindowClosingMode;
using com::jogamp::nativewindow::util::InsetsImmutable;
using com::jogamp::nativewindow::util::Point;
using com::jogamp::nativewindow::util::Rectangle;
using com::jogamp::newt::Display_PointerIcon;
using com::jogamp::newt::MonitorDevice;
using com::jogamp::newt::Screen;
using com::jogamp::newt::Window_FocusRunnable;
using com::jogamp::newt::Window_ReparentOperation;
using com::jogamp::newt::event::GestureHandler_GestureListener;
using com::jogamp::newt::event::GestureHandler;
using com::jogamp::newt::event::KeyListener;
using com::jogamp::newt::event::MouseListener;
using com::jogamp::newt::event::NEWTEvent;
using com::jogamp::newt::event::NEWTEventListener;
using com::jogamp::newt::event::WindowListener;
using com::jogamp::opengl::GL;
using com::jogamp::opengl::GLAnimatorControl;
using com::jogamp::opengl::GLCapabilitiesImmutable;
using com::jogamp::opengl::GLContext;
using com::jogamp::opengl::GLDrawable;
using com::jogamp::opengl::GLDrawableFactory;
using com::jogamp::opengl::GLEventListener;
using com::jogamp::opengl::GLProfile;
using com::jogamp::opengl::GLRunnable;
using java::io::PrintStream;
using java::io::Serializable;
using java::lang::CharSequence;
using java::lang::Comparable;
using java::lang::Object;
using java::lang::Runnable;
using java::lang::String;
using java::lang::Thread;
using java::util::EventListener;
using java::util::List;
using jogamp::newt::WindowImpl;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace util {
typedef ::SubArray< ::java::util::EventListener, ::java::lang::ObjectArray > EventListenerArray;
}  // namespace util
}  // namespace java

namespace com {
namespace jogamp {
namespace newt {
namespace event {
typedef ::SubArray< ::com::jogamp::newt::event::NEWTEventListener, ::java::lang::ObjectArray, ::java::util::EventListenerArray > NEWTEventListenerArray;
typedef ::SubArray< ::com::jogamp::newt::event::KeyListener, ::java::lang::ObjectArray, NEWTEventListenerArray > KeyListenerArray;
typedef ::SubArray< ::com::jogamp::newt::event::MouseListener, ::java::lang::ObjectArray, NEWTEventListenerArray > MouseListenerArray;
typedef ::SubArray< ::com::jogamp::newt::event::WindowListener, ::java::lang::ObjectArray, NEWTEventListenerArray > WindowListenerArray;
}  // namespace event
}  // namespace newt
}  // namespace jogamp
}  // namespace com

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

using com::jogamp::newt::event::KeyListenerArray;
using com::jogamp::newt::event::MouseListenerArray;
using com::jogamp::newt::event::NEWTEventListenerArray;
using com::jogamp::newt::event::WindowListenerArray;
using java::io::SerializableArray;
using java::lang::CharSequenceArray;
using java::lang::ComparableArray;
using java::lang::ObjectArray;
using java::lang::StringArray;
using java::util::EventListenerArray;

struct default_init_tag;
class com::jogamp::newt::opengl::GLWindow
	: public GLAutoDrawableBase
	, public virtual GLAutoDrawable
	, public virtual Window
	, public virtual NEWTEventConsumer
	, public virtual FPSCounter
{

public:
	typedef GLAutoDrawableBase super;

private:
	GLDrawableFactory* factory {  };
	WindowImpl* window {  };

protected:
	void ctor(Window* arg0);

public:
	bool addChild(NativeWindow* arg0) override;
	void addGestureHandler(GestureHandler* arg0) override;
	void addGestureHandler(int32_t arg0, GestureHandler* arg1) override;
	void addGestureListener(GestureHandler_GestureListener* arg0) override;
	void addGestureListener(int32_t arg0, GestureHandler_GestureListener* arg1) override;
	void addKeyListener(KeyListener* arg0) override;
	void addKeyListener(int32_t arg0, KeyListener* arg1) override;
	void addMouseListener(MouseListener* arg0) override;
	void addMouseListener(int32_t arg0, MouseListener* arg1) override;
	void addSurfaceUpdatedListener(SurfaceUpdatedListener* arg0) override;
	void addSurfaceUpdatedListener(int32_t arg0, SurfaceUpdatedListener* arg1) override;
	void addWindowListener(WindowListener* arg0) override;
	void addWindowListener(int32_t arg0, WindowListener* arg1) override;
	bool areDefaultGesturesEnabled() override;
	void confinePointer(bool arg0) override;
	bool consumeEvent(NEWTEvent* arg0) override;
	int32_tArray* convertToPixelUnits(int32_tArray* arg0) override;
	int32_tArray* convertToWindowUnits(int32_tArray* arg0) override;
	static GLWindow* create(GLCapabilitiesImmutable* arg0);
	static GLWindow* create(Window* arg0);
	static GLWindow* create(Screen* arg0, GLCapabilitiesImmutable* arg1);
	static GLWindow* create(NativeWindow* arg0, GLCapabilitiesImmutable* arg1);
	void destroy() override;
	void display() override;
	void enqueueEvent(bool arg0, NEWTEvent* arg1) override;
	Rectangle* getBounds() override;
	CapabilitiesImmutable* getChosenCapabilities() override;
	floatArray* getCurrentSurfaceScale(floatArray* arg0) override;
	WindowClosingProtocol_WindowClosingMode* getDefaultCloseOperation() override;
	Window* getDelegatedWindow() override;
	int64_t getDisplayHandle() override;
	GLDrawableFactory* getFactory() override;
	AbstractGraphicsConfiguration* getGraphicsConfiguration() override;
	int32_t getHeight() override;
	InsetsImmutable* getInsets() override;
	KeyListener* getKeyListener(int32_t arg0) override;
	KeyListenerArray* getKeyListeners() override;
	Point* getLocationOnScreen(Point* arg0) override;
	MonitorDevice* getMainMonitor() override;
	floatArray* getMaximumSurfaceScale(floatArray* arg0) override;
	floatArray* getMinimumSurfaceScale(floatArray* arg0) override;
	MouseListener* getMouseListener(int32_t arg0) override;
	MouseListenerArray* getMouseListeners() override;
	NativeWindow* getParent() override;
	floatArray* getPixelsPerMM(floatArray* arg0) override;
	Display_PointerIcon* getPointerIcon() override;
	CapabilitiesImmutable* getRequestedCapabilities() override;
	floatArray* getRequestedSurfaceScale(floatArray* arg0) override;
	Screen* getScreen() override;
	int32_t getScreenIndex() override;
	int32_t getStateMask() override;
	String* getStateMaskString() override;
	int32_t getStatePublicBitCount() override;
	int32_t getStatePublicBitmask() override;
	int32_t getSupportedStateMask() override;
	String* getSupportedStateMaskString() override;
	int64_t getSurfaceHandle() override;
	int32_t getSurfaceHeight() override;
	Thread* getSurfaceLockOwner() override;
	int32_t getSurfaceWidth() override;
	String* getTitle() override;
	RecursiveLock* getUpstreamLock() override;
	Object* getUpstreamWidget() override;
	int32_t getWidth() override;
	int64_t getWindowHandle() override;
	WindowListener* getWindowListener(int32_t arg0) override;
	WindowListenerArray* getWindowListeners() override;
	int32_t getX() override;
	int32_t getY() override;
	bool hasFocus() override;
	bool isAlwaysOnBottom() override;
	bool isAlwaysOnTop() override;
	bool isChildWindow() override;
	bool isFullscreen() override;
	bool isGLStatePreservationSupported() override;
	bool isKeyboardVisible() override;
	bool isMaximizedHorz() override;
	bool isMaximizedVert() override;
	bool isNativeValid() override;
	bool isPointerConfined() override;
	bool isPointerVisible() override;
	bool isResizable() override;
	bool isSticky() override;
	bool isSurfaceLockedByOtherThread() override;
	bool isUndecorated() override;
	bool isVisible() override;
	int32_t lockSurface() override;
	static void main(StringArray* arg0);
	bool removeChild(NativeWindow* arg0) override;
	void removeGestureHandler(GestureHandler* arg0) override;
	void removeGestureListener(GestureHandler_GestureListener* arg0) override;
	void removeKeyListener(KeyListener* arg0) override;
	void removeMouseListener(MouseListener* arg0) override;
	void removeSurfaceUpdatedListener(SurfaceUpdatedListener* arg0) override;
	void removeWindowListener(WindowListener* arg0) override;
	Window_ReparentOperation* reparentWindow(NativeWindow* arg0, int32_t arg1, int32_t arg2, int32_t arg3) override;
	void requestFocus() override;
	void requestFocus(bool arg0) override;
	void runOnEDTIfAvail(bool arg0, Runnable* arg1) override;
	void sendWindowEvent(int32_t arg0) override;
	void setAlwaysOnBottom(bool arg0) override;
	void setAlwaysOnTop(bool arg0) override;
	CapabilitiesChooser* setCapabilitiesChooser(CapabilitiesChooser* arg0) override;
	WindowClosingProtocol_WindowClosingMode* setDefaultCloseOperation(WindowClosingProtocol_WindowClosingMode* arg0) override;
	void setDefaultGesturesEnabled(bool arg0) override;
	void setFocusAction(Window_FocusRunnable* arg0) override;
	bool setFullscreen(bool arg0) override;
	bool setFullscreen(List* arg0) override;
	void setKeyboardFocusHandler(KeyListener* arg0) override;
	void setKeyboardVisible(bool arg0) override;
	void setMaximized(bool arg0, bool arg1) override;
	void setPointerIcon(Display_PointerIcon* arg0) override;
	void setPointerVisible(bool arg0) override;
	void setPosition(int32_t arg0, int32_t arg1) override;
	void setResizable(bool arg0) override;
	void setSize(int32_t arg0, int32_t arg1) override;
	void setSticky(bool arg0) override;
	bool setSurfaceScale(floatArray* arg0) override;
	void setSurfaceSize(int32_t arg0, int32_t arg1) override;
	void setTitle(String* arg0) override;
	void setTopLevelPosition(int32_t arg0, int32_t arg1) override;
	void setTopLevelSize(int32_t arg0, int32_t arg1) override;
	void setUndecorated(bool arg0) override;
	void setVisible(bool arg0) override;
	void setVisible(bool arg0, bool arg1) override;
	void setWindowDestroyNotifyAction(Runnable* arg0) override;
	bool surfaceSwap() override;
	void surfaceUpdated(Object* arg0, NativeSurface* arg1, int64_t arg2) override;
	void swapBuffers() override;
	String* toString() override;
	void unlockSurface() override;
	void warpPointer(int32_t arg0, int32_t arg1) override;
	void windowRepaint(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3) override;

	// Generated

public: /* protected */
	GLWindow(Window* arg0);
protected:
	GLWindow(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	virtual int64_t getFPSStartTime();
	virtual float getLastFPS();
	virtual int64_t getLastFPSPeriod();
	virtual int64_t getLastFPSUpdateTime();
	virtual float getTotalFPS();
	virtual int64_t getTotalFPSDuration();
	virtual int32_t getTotalFPSFrames();
	virtual int32_t getUpdateFPSFrames();
	virtual void resetFPSCounter();
	virtual void setUpdateFPSFrames(int32_t arg0, PrintStream* arg1);
	virtual void addGLEventListener(int32_t arg0, GLEventListener* arg1);
	virtual void addGLEventListener(GLEventListener* arg0);
	virtual bool areAllGLEventListenerInitialized();
	virtual GLEventListener* disposeGLEventListener(GLEventListener* arg0, bool arg1);
	virtual void flushGLRunnables();
	virtual GLAnimatorControl* getAnimator();
	virtual bool getAutoSwapBufferMode();
	virtual GLContext* getContext();
	virtual int32_t getContextCreationFlags();
	virtual GLDrawable* getDelegatedDrawable();
	virtual Thread* getExclusiveContextThread();
	virtual GL* getGL();
	virtual GLEventListener* getGLEventListener(int32_t arg0);
	virtual int32_t getGLEventListenerCount();
	virtual bool getGLEventListenerInitState(GLEventListener* arg0);
	virtual bool invoke(bool arg0, GLRunnable* arg1);
	virtual bool invoke(bool arg0, List* arg1);
	virtual bool isThreadGLCapable();
	virtual GLEventListener* removeGLEventListener(GLEventListener* arg0);
	virtual void setAnimator(GLAnimatorControl* arg0);
	virtual void setAutoSwapBufferMode(bool arg0);
	virtual GLContext* setContext(GLContext* arg0, bool arg1);
	virtual void setContextCreationFlags(int32_t arg0);
	virtual Thread* setExclusiveContextThread(Thread* arg0);
	virtual GL* setGL(GL* arg0);
	virtual void setGLEventListenerInitState(GLEventListener* arg0, bool arg1);
	virtual GLContext* createContext(GLContext* arg0);
	virtual GLCapabilitiesImmutable* getChosenGLCapabilities();
	virtual GLProfile* getGLProfile();
	virtual int64_t getHandle();
	NativeSurface* getNativeSurface();
	virtual GLCapabilitiesImmutable* getRequestedGLCapabilities();
	virtual bool isGLOriented();
	virtual bool isRealized();
	virtual void setRealized(bool arg0);

private:
	virtual ::java::lang::Class* getClass0();
};
