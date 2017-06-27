// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/nativewindow/fwd-tdme.h>
#include <com/jogamp/nativewindow/util/fwd-tdme.h>
#include <com/jogamp/newt/fwd-tdme.h>
#include <com/jogamp/newt/event/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <com/jogamp/nativewindow/NativeWindow.h>
#include <com/jogamp/nativewindow/WindowClosingProtocol.h>
#include <com/jogamp/nativewindow/ScalableSurface.h>

using com::jogamp::nativewindow::NativeWindow;
using com::jogamp::nativewindow::WindowClosingProtocol;
using com::jogamp::nativewindow::ScalableSurface;
using com::jogamp::nativewindow::CapabilitiesChooser;
using com::jogamp::nativewindow::CapabilitiesImmutable;
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
using java::lang::Runnable;
using java::lang::String;
using java::util::EventListener;
using java::util::List;
using java::lang::Object;

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

using com::jogamp::newt::event::KeyListenerArray;
using com::jogamp::newt::event::MouseListenerArray;
using com::jogamp::newt::event::NEWTEventListenerArray;
using com::jogamp::newt::event::WindowListenerArray;
using java::lang::ObjectArray;
using java::util::EventListenerArray;

struct com::jogamp::newt::Window
	: public virtual NativeWindow
	, public virtual WindowClosingProtocol
	, public virtual ScalableSurface
{
	static bool DEBUG_IMPLEMENTATION;
	static bool DEBUG_KEY_EVENT;
	static bool DEBUG_MOUSE_EVENT;
	static constexpr int32_t REPARENT_HINT_BECOMES_VISIBLE { 2 };
	static constexpr int32_t REPARENT_HINT_FORCE_RECREATION { 1 };
	static constexpr int32_t STATE_BIT_ALWAYSONBOTTOM { 6 };
	static constexpr int32_t STATE_BIT_ALWAYSONTOP { 5 };
	static constexpr int32_t STATE_BIT_AUTOPOSITION { 1 };
	static constexpr int32_t STATE_BIT_CHILDWIN { 2 };
	static constexpr int32_t STATE_BIT_FOCUSED { 3 };
	static constexpr int32_t STATE_BIT_FULLSCREEN { 11 };
	static constexpr int32_t STATE_BIT_MAXIMIZED_HORZ { 10 };
	static constexpr int32_t STATE_BIT_MAXIMIZED_VERT { 9 };
	static constexpr int32_t STATE_BIT_POINTERCONFINED { 13 };
	static constexpr int32_t STATE_BIT_POINTERVISIBLE { 12 };
	static constexpr int32_t STATE_BIT_RESIZABLE { 8 };
	static constexpr int32_t STATE_BIT_STICKY { 7 };
	static constexpr int32_t STATE_BIT_UNDECORATED { 4 };
	static constexpr int32_t STATE_BIT_VISIBLE { 0 };
	static constexpr int32_t STATE_MASK_ALWAYSONBOTTOM { 64 };
	static constexpr int32_t STATE_MASK_ALWAYSONTOP { 32 };
	static constexpr int32_t STATE_MASK_AUTOPOSITION { 2 };
	static constexpr int32_t STATE_MASK_CHILDWIN { 4 };
	static constexpr int32_t STATE_MASK_FOCUSED { 8 };
	static constexpr int32_t STATE_MASK_FULLSCREEN { 2048 };
	static constexpr int32_t STATE_MASK_MAXIMIZED_HORZ { 1024 };
	static constexpr int32_t STATE_MASK_MAXIMIZED_VERT { 512 };
	static constexpr int32_t STATE_MASK_POINTERCONFINED { 8192 };
	static constexpr int32_t STATE_MASK_POINTERVISIBLE { 4096 };
	static constexpr int32_t STATE_MASK_RESIZABLE { 256 };
	static constexpr int32_t STATE_MASK_STICKY { 128 };
	static constexpr int32_t STATE_MASK_UNDECORATED { 16 };
	static constexpr int32_t STATE_MASK_VISIBLE { 1 };
	static constexpr int64_t TIMEOUT_NATIVEWINDOW { 1000LL };

	virtual bool addChild(NativeWindow* arg0) = 0;
	virtual void addGestureHandler(GestureHandler* arg0) = 0;
	virtual void addGestureHandler(int32_t arg0, GestureHandler* arg1) = 0;
	virtual void addGestureListener(GestureHandler_GestureListener* arg0) = 0;
	virtual void addGestureListener(int32_t arg0, GestureHandler_GestureListener* arg1) = 0;
	virtual void addKeyListener(KeyListener* arg0) = 0;
	virtual void addKeyListener(int32_t arg0, KeyListener* arg1) = 0;
	virtual void addMouseListener(MouseListener* arg0) = 0;
	virtual void addMouseListener(int32_t arg0, MouseListener* arg1) = 0;
	virtual void addWindowListener(WindowListener* arg0) = 0;
	virtual void addWindowListener(int32_t arg0, WindowListener* arg1) = 0;
	virtual bool areDefaultGesturesEnabled() = 0;
	virtual void confinePointer(bool arg0) = 0;
	/*void destroy(); (already declared) */
	virtual void enqueueEvent(bool arg0, NEWTEvent* arg1) = 0;
	virtual Rectangle* getBounds() = 0;
	virtual CapabilitiesImmutable* getChosenCapabilities() = 0;
	virtual Window* getDelegatedWindow() = 0;
	virtual KeyListener* getKeyListener(int32_t arg0) = 0;
	virtual KeyListenerArray* getKeyListeners() = 0;
	virtual MonitorDevice* getMainMonitor() = 0;
	virtual MouseListener* getMouseListener(int32_t arg0) = 0;
	virtual MouseListenerArray* getMouseListeners() = 0;
	virtual floatArray* getPixelsPerMM(floatArray* arg0) = 0;
	virtual Display_PointerIcon* getPointerIcon() = 0;
	virtual CapabilitiesImmutable* getRequestedCapabilities() = 0;
	virtual Screen* getScreen() = 0;
	virtual int32_t getStateMask() = 0;
	virtual String* getStateMaskString() = 0;
	virtual int32_t getStatePublicBitCount() = 0;
	virtual int32_t getStatePublicBitmask() = 0;
	virtual int32_t getSupportedStateMask() = 0;
	virtual String* getSupportedStateMaskString() = 0;
	virtual String* getTitle() = 0;
	virtual WindowListener* getWindowListener(int32_t arg0) = 0;
	virtual WindowListenerArray* getWindowListeners() = 0;
	virtual bool isAlwaysOnBottom() = 0;
	virtual bool isAlwaysOnTop() = 0;
	virtual bool isChildWindow() = 0;
	virtual bool isFullscreen() = 0;
	virtual bool isKeyboardVisible() = 0;
	virtual bool isMaximizedHorz() = 0;
	virtual bool isMaximizedVert() = 0;
	virtual bool isNativeValid() = 0;
	virtual bool isPointerConfined() = 0;
	virtual bool isPointerVisible() = 0;
	virtual bool isResizable() = 0;
	virtual bool isSticky() = 0;
	virtual bool isUndecorated() = 0;
	virtual bool isVisible() = 0;
	virtual bool removeChild(NativeWindow* arg0) = 0;
	virtual void removeGestureHandler(GestureHandler* arg0) = 0;
	virtual void removeGestureListener(GestureHandler_GestureListener* arg0) = 0;
	virtual void removeKeyListener(KeyListener* arg0) = 0;
	virtual void removeMouseListener(MouseListener* arg0) = 0;
	virtual void removeWindowListener(WindowListener* arg0) = 0;
	virtual Window_ReparentOperation* reparentWindow(NativeWindow* arg0, int32_t arg1, int32_t arg2, int32_t arg3) = 0;
	virtual void requestFocus() = 0;
	virtual void requestFocus(bool arg0) = 0;
	virtual void runOnEDTIfAvail(bool arg0, Runnable* arg1) = 0;
	virtual void sendWindowEvent(int32_t arg0) = 0;
	virtual void setAlwaysOnBottom(bool arg0) = 0;
	virtual void setAlwaysOnTop(bool arg0) = 0;
	virtual CapabilitiesChooser* setCapabilitiesChooser(CapabilitiesChooser* arg0) = 0;
	virtual void setDefaultGesturesEnabled(bool arg0) = 0;
	virtual void setFocusAction(Window_FocusRunnable* arg0) = 0;
	virtual bool setFullscreen(bool arg0) = 0;
	virtual bool setFullscreen(List* arg0) = 0;
	virtual void setKeyboardFocusHandler(KeyListener* arg0) = 0;
	virtual void setKeyboardVisible(bool arg0) = 0;
	virtual void setMaximized(bool arg0, bool arg1) = 0;
	virtual void setPointerIcon(Display_PointerIcon* arg0) = 0;
	virtual void setPointerVisible(bool arg0) = 0;
	virtual void setPosition(int32_t arg0, int32_t arg1) = 0;
	virtual void setResizable(bool arg0) = 0;
	virtual void setSize(int32_t arg0, int32_t arg1) = 0;
	virtual void setSticky(bool arg0) = 0;
	virtual void setSurfaceSize(int32_t arg0, int32_t arg1) = 0;
	virtual void setTitle(String* arg0) = 0;
	virtual void setTopLevelPosition(int32_t arg0, int32_t arg1) = 0;
	virtual void setTopLevelSize(int32_t arg0, int32_t arg1) = 0;
	virtual void setUndecorated(bool arg0) = 0;
	virtual void setVisible(bool arg0) = 0;
	virtual void setVisible(bool arg0, bool arg1) = 0;
	virtual void setWindowDestroyNotifyAction(Runnable* arg0) = 0;
	virtual void warpPointer(int32_t arg0, int32_t arg1) = 0;
	virtual void windowRepaint(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3) = 0;

	// Generated
	static ::java::lang::Class *class_();
};
