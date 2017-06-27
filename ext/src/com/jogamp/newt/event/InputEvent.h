// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/newt/event/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <com/jogamp/newt/event/NEWTEvent.h>

using com::jogamp::newt::event::NEWTEvent;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;


struct default_init_tag;
class com::jogamp::newt::event::InputEvent
	: public NEWTEvent
{

public:
	typedef NEWTEvent super;
	static constexpr int32_t ALT_GRAPH_MASK { 16 };
	static constexpr int32_t ALT_MASK { 8 };
	static constexpr int32_t AUTOREPEAT_MASK { 536870912 };
	static constexpr int32_t BUTTON1_MASK { 32 };
	static constexpr int32_t BUTTON2_MASK { 64 };
	static constexpr int32_t BUTTON3_MASK { 128 };
	static constexpr int32_t BUTTON4_MASK { 256 };
	static constexpr int32_t BUTTON5_MASK { 512 };
	static constexpr int32_t BUTTON6_MASK { 1024 };
	static constexpr int32_t BUTTON7_MASK { 2048 };
	static constexpr int32_t BUTTON8_MASK { 4096 };
	static constexpr int32_t BUTTON9_MASK { 8192 };
	static constexpr int32_t BUTTONALL_MASK { 2097120 };
	static constexpr int32_t BUTTONLAST_MASK { 1048576 };
	static constexpr int32_t CONFINED_MASK { 1073741824 };
	static constexpr int32_t CTRL_MASK { 2 };
	static constexpr int32_t INVISIBLE_MASK { -0x7fffffff-1 };
	static constexpr int32_t META_MASK { 4 };
	static constexpr int32_t SHIFT_MASK { 1 };

private:
	int32_t modifiers {  };

protected:
	void ctor(int16_t arg0, Object* arg1, int64_t arg2, int32_t arg3);

public:
	int32_t getButtonDownCount();
	static int32_t getButtonMask(int32_t arg0);
	int16_tArray* getButtonsDown();
	int32_t getModifiers();
	StringBuilder* getModifiersString(StringBuilder* arg0);
	bool isAltDown();
	bool isAltGraphDown();
	bool isAnyButtonDown();
	bool isAutoRepeat();
	bool isButtonDown(int32_t arg0);
	bool isConfined();
	bool isControlDown();
	bool isInvisible();
	bool isMetaDown();
	bool isShiftDown();
	String* toString() override;
	StringBuilder* toString(StringBuilder* arg0) override;

	// Generated

public: /* protected */
	InputEvent(int16_t arg0, Object* arg1, int64_t arg2, int32_t arg3);
protected:
	InputEvent(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
