// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/newt/event/fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <com/jogamp/newt/event/InputEvent.h>

using com::jogamp::newt::event::InputEvent;
using com::jogamp::newt::event::InputEvent_InputType;
using com::jogamp::newt::event::MouseEvent_PointerType;
using java::io::Serializable;
using java::lang::Comparable;
using java::lang::Enum;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace com {
namespace jogamp {
namespace newt {
namespace event {
typedef ::SubArray< ::com::jogamp::newt::event::InputEvent_InputType, ::java::lang::ObjectArray > InputEvent_InputTypeArray;
}  // namespace event
}  // namespace newt
}  // namespace jogamp
}  // namespace com

namespace java {
namespace lang {
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
}  // namespace lang

namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::Enum, ObjectArray, ComparableArray, ::java::io::SerializableArray > EnumArray;
}  // namespace lang
}  // namespace java

namespace com {
namespace jogamp {
namespace newt {
namespace event {
typedef ::SubArray< ::com::jogamp::newt::event::MouseEvent_PointerType, ::java::lang::EnumArray, InputEvent_InputTypeArray > MouseEvent_PointerTypeArray;
}  // namespace event
}  // namespace newt
}  // namespace jogamp
}  // namespace com

using com::jogamp::newt::event::InputEvent_InputTypeArray;
using com::jogamp::newt::event::MouseEvent_PointerTypeArray;
using java::io::SerializableArray;
using java::lang::ComparableArray;
using java::lang::EnumArray;
using java::lang::ObjectArray;

struct default_init_tag;
class com::jogamp::newt::event::MouseEvent
	: public InputEvent
{

public:
	typedef InputEvent super;
	static constexpr int16_t BUTTON1 { 1 };
	static constexpr int16_t BUTTON2 { 2 };
	static constexpr int16_t BUTTON3 { 3 };
	static constexpr int16_t BUTTON4 { 4 };
	static constexpr int16_t BUTTON5 { 5 };
	static constexpr int16_t BUTTON6 { 6 };
	static constexpr int16_t BUTTON7 { 7 };
	static constexpr int16_t BUTTON8 { 8 };
	static constexpr int16_t BUTTON9 { 9 };
	static constexpr int16_t BUTTON_COUNT { 16 };
	static constexpr int16_t EVENT_MOUSE_CLICKED { 200 };
	static constexpr int16_t EVENT_MOUSE_DRAGGED { 206 };
	static constexpr int16_t EVENT_MOUSE_ENTERED { 201 };
	static constexpr int16_t EVENT_MOUSE_EXITED { 202 };
	static constexpr int16_t EVENT_MOUSE_MOVED { 205 };
	static constexpr int16_t EVENT_MOUSE_PRESSED { 203 };
	static constexpr int16_t EVENT_MOUSE_RELEASED { 204 };
	static constexpr int16_t EVENT_MOUSE_WHEEL_MOVED { 207 };

private:
	int16_t button {  };
	int16_t clickCount {  };
	static MouseEvent_PointerTypeArray* constMousePointerTypes;
	static floatArray* constMousePressure0;
	static floatArray* constMousePressure1;
	float maxPressure {  };
	int16_tArray* pointerID {  };
	MouseEvent_PointerTypeArray* pointerType {  };
	floatArray* pressure {  };
	float rotationScale {  };
	floatArray* rotationXYZ {  };
	int32_tArray* x {  };
	int32_tArray* y {  };

protected:
	void ctor(int16_t arg0, Object* arg1, int64_t arg2, int32_t arg3, int32_t arg4, int32_t arg5, int16_t arg6, int16_t arg7, floatArray* arg8, float arg9);
	void ctor(int16_t arg0, Object* arg1, int64_t arg2, int32_t arg3, MouseEvent_PointerTypeArray* arg4, int16_tArray* arg5, int32_tArray* arg6, int32_tArray* arg7, floatArray* arg8, float arg9, int16_t arg10, int16_t arg11, floatArray* arg12, float arg13);

public:
	MouseEvent* createVariant(int16_t arg0);
	int16_tArray* getAllPointerIDs();
	MouseEvent_PointerTypeArray* getAllPointerTypes();
	floatArray* getAllPressures();
	int32_tArray* getAllX();
	int32_tArray* getAllY();
	int16_t getButton();
	int16_t getClickCount();
	static int16_t getClickTimeout();
	static String* getEventTypeString(int16_t arg0);
	float getMaxPressure();
	int32_t getPointerCount();
	int16_t getPointerId(int32_t arg0);
	int32_t getPointerIdx(int16_t arg0);
	MouseEvent_PointerType* getPointerType(int32_t arg0);
	float getPressure(bool arg0);
	float getPressure(int32_t arg0, bool arg1);
	floatArray* getRotation();
	float getRotationScale();
	static floatArray* getRotationXYZ(float arg0, int32_t arg1);
	int32_t getX();
	int32_t getX(int32_t arg0);
	int32_t getY();
	int32_t getY(int32_t arg0);
	String* toString() override;
	StringBuilder* toString(StringBuilder* arg0) override;

	// Generated
	MouseEvent(int16_t arg0, Object* arg1, int64_t arg2, int32_t arg3, int32_t arg4, int32_t arg5, int16_t arg6, int16_t arg7, floatArray* arg8, float arg9);
	MouseEvent(int16_t arg0, Object* arg1, int64_t arg2, int32_t arg3, MouseEvent_PointerTypeArray* arg4, int16_tArray* arg5, int32_tArray* arg6, int32_tArray* arg7, floatArray* arg8, float arg9, int16_t arg10, int16_t arg11, floatArray* arg12, float arg13);
protected:
	MouseEvent(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
