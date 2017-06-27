// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/newt/event/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <com/jogamp/newt/event/InputEvent.h>

using com::jogamp::newt::event::InputEvent;
using com::jogamp::newt::event::KeyEvent_NonPrintableRange;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace com {
namespace jogamp {
namespace newt {
namespace event {
typedef ::SubArray< ::com::jogamp::newt::event::KeyEvent_NonPrintableRange, ::java::lang::ObjectArray > KeyEvent_NonPrintableRangeArray;
}  // namespace event
}  // namespace newt
}  // namespace jogamp
}  // namespace com

using com::jogamp::newt::event::KeyEvent_NonPrintableRangeArray;
using java::lang::ObjectArray;

struct default_init_tag;
class com::jogamp::newt::event::KeyEvent
	: public InputEvent
{

public:
	typedef InputEvent super;
	static constexpr int16_t EVENT_KEY_PRESSED { 300 };
	static constexpr int16_t EVENT_KEY_RELEASED { 301 };

private:
	static constexpr int8_t F_ACTION_MASK { int8_t(2) };
	static constexpr int8_t F_MODIFIER_MASK { int8_t(1) };
	static constexpr int8_t F_PRINTABLE_MASK { int8_t(4) };

public:
	static constexpr char16_t NULL_CHAR { char16_t(0x0000) };
	static constexpr int16_t VK_0 { 48 };
	static constexpr int16_t VK_1 { 49 };
	static constexpr int16_t VK_2 { 50 };
	static constexpr int16_t VK_3 { 51 };
	static constexpr int16_t VK_4 { 52 };
	static constexpr int16_t VK_5 { 53 };
	static constexpr int16_t VK_6 { 54 };
	static constexpr int16_t VK_7 { 55 };
	static constexpr int16_t VK_8 { 56 };
	static constexpr int16_t VK_9 { 57 };
	static constexpr int16_t VK_A { 65 };
	static constexpr int16_t VK_ACCEPT { 30 };
	static constexpr int16_t VK_ADD { 139 };
	static constexpr int16_t VK_AGAIN { -1923 };
	static constexpr int16_t VK_ALL_CANDIDATES { -1901 };
	static constexpr int16_t VK_ALPHANUMERIC { -1899 };
	static constexpr int16_t VK_ALT { 18 };
	static constexpr int16_t VK_ALT_GRAPH { 19 };
	static constexpr int16_t VK_AMPERSAND { 38 };
	static constexpr int16_t VK_ASTERISK { 42 };
	static constexpr int16_t VK_AT { 64 };
	static constexpr int16_t VK_B { 66 };
	static constexpr int16_t VK_BACK_QUOTE { 96 };
	static constexpr int16_t VK_BACK_SLASH { 92 };
	static constexpr int16_t VK_BACK_SPACE { 8 };
	static constexpr int16_t VK_BEGIN { 158 };
	static constexpr int16_t VK_C { 67 };
	static constexpr int16_t VK_CANCEL { 24 };
	static constexpr int16_t VK_CAPS_LOCK { 20 };
	static constexpr int16_t VK_CIRCUMFLEX { 94 };
	static constexpr int16_t VK_CLEAR { 12 };
	static constexpr int16_t VK_CLOSE_BRACKET { 93 };
	static constexpr int16_t VK_CODE_INPUT { -1903 };
	static constexpr int16_t VK_COLON { 58 };
	static constexpr int16_t VK_COMMA { 44 };
	static constexpr int16_t VK_COMPOSE { 157 };
	static constexpr int16_t VK_CONTEXT_MENU { 153 };
	static constexpr int16_t VK_CONTROL { 17 };
	static constexpr int16_t VK_CONVERT { 28 };
	static constexpr int16_t VK_COPY { -1926 };
	static constexpr int16_t VK_CUT { -1927 };
	static constexpr int16_t VK_D { 68 };
	static constexpr int16_t VK_DECIMAL { 138 };
	static constexpr int16_t VK_DELETE { 147 };
	static constexpr int16_t VK_DIVIDE { 142 };
	static constexpr int16_t VK_DOLLAR { 36 };
	static constexpr int16_t VK_DOWN { 152 };
	static constexpr int16_t VK_E { 69 };
	static constexpr int16_t VK_END { 3 };
	static constexpr int16_t VK_ENTER { 13 };
	static constexpr int16_t VK_EQUALS { 61 };
	static constexpr int16_t VK_ESCAPE { 27 };
	static constexpr int16_t VK_EURO_SIGN { 8364 };
	static constexpr int16_t VK_EXCLAMATION_MARK { 33 };
	static constexpr int16_t VK_F { 70 };
	static constexpr int16_t VK_F1 { 97 };
	static constexpr int16_t VK_F10 { 106 };
	static constexpr int16_t VK_F11 { 107 };
	static constexpr int16_t VK_F12 { 108 };
	static constexpr int16_t VK_F13 { 109 };
	static constexpr int16_t VK_F14 { 110 };
	static constexpr int16_t VK_F15 { 111 };
	static constexpr int16_t VK_F16 { 112 };
	static constexpr int16_t VK_F17 { 113 };
	static constexpr int16_t VK_F18 { 114 };
	static constexpr int16_t VK_F19 { 115 };
	static constexpr int16_t VK_F2 { 98 };
	static constexpr int16_t VK_F20 { 116 };
	static constexpr int16_t VK_F21 { 117 };
	static constexpr int16_t VK_F22 { 118 };
	static constexpr int16_t VK_F23 { 119 };
	static constexpr int16_t VK_F24 { 120 };
	static constexpr int16_t VK_F3 { 99 };
	static constexpr int16_t VK_F4 { 100 };
	static constexpr int16_t VK_F5 { 101 };
	static constexpr int16_t VK_F6 { 102 };
	static constexpr int16_t VK_F7 { 103 };
	static constexpr int16_t VK_F8 { 104 };
	static constexpr int16_t VK_F9 { 105 };
	static constexpr int16_t VK_FINAL { 4 };
	static constexpr int16_t VK_FIND { -1922 };

public: /* package */
	static constexpr int16_t VK_FREE01 { 1 };
	static constexpr int16_t VK_FREE06 { 6 };
	static constexpr int16_t VK_FREE07 { 7 };
	static constexpr int16_t VK_FREE0A { 10 };
	static constexpr int16_t VK_FREE0E { 14 };
	static constexpr int16_t VK_FREE15 { 21 };
	static constexpr int16_t VK_FREE19 { 25 };

public:
	static constexpr int16_t VK_FULL_WIDTH { -1896 };
	static constexpr int16_t VK_G { 71 };
	static constexpr int16_t VK_GREATER { 62 };
	static constexpr int16_t VK_H { 72 };
	static constexpr int16_t VK_HALF_WIDTH { -1894 };
	static constexpr int16_t VK_HELP { 156 };
	static constexpr int16_t VK_HIRAGANA { -1897 };
	static constexpr int16_t VK_HOME { 2 };
	static constexpr int16_t VK_I { 73 };
	static constexpr int16_t VK_INPUT_METHOD_ON_OFF { -1904 };
	static constexpr int16_t VK_INSERT { 26 };
	static constexpr int16_t VK_INVERTED_EXCLAMATION_MARK { 161 };
	static constexpr int16_t VK_J { 74 };
	static constexpr int16_t VK_JAPANESE_HIRAGANA { -1892 };
	static constexpr int16_t VK_JAPANESE_KATAKANA { -1893 };
	static constexpr int16_t VK_JAPANESE_ROMAN { -1891 };
	static constexpr int16_t VK_K { 75 };
	static constexpr int16_t VK_KANA_LOCK { -1889 };
	static constexpr int16_t VK_KATAKANA { -1898 };
	static constexpr int16_t VK_KEYBOARD_INVISIBLE { -1793 };
	static constexpr int16_t VK_L { 76 };
	static constexpr int16_t VK_LEFT { 149 };
	static constexpr int16_t VK_LEFT_BRACE { 123 };
	static constexpr int16_t VK_LEFT_PARENTHESIS { 40 };
	static constexpr int16_t VK_LESS { 60 };
	static constexpr int16_t VK_M { 77 };
	static constexpr int16_t VK_META { 155 };
	static constexpr int16_t VK_MINUS { 45 };
	static constexpr int16_t VK_MODECHANGE { 31 };
	static constexpr int16_t VK_MULTIPLY { 141 };
	static constexpr int16_t VK_N { 78 };
	static constexpr int16_t VK_NONCONVERT { 29 };
	static constexpr int16_t VK_NUMBER_SIGN { 35 };
	static constexpr int16_t VK_NUMPAD0 { 128 };
	static constexpr int16_t VK_NUMPAD1 { 129 };
	static constexpr int16_t VK_NUMPAD2 { 130 };
	static constexpr int16_t VK_NUMPAD3 { 131 };
	static constexpr int16_t VK_NUMPAD4 { 132 };
	static constexpr int16_t VK_NUMPAD5 { 133 };
	static constexpr int16_t VK_NUMPAD6 { 134 };
	static constexpr int16_t VK_NUMPAD7 { 135 };
	static constexpr int16_t VK_NUMPAD8 { 136 };
	static constexpr int16_t VK_NUMPAD9 { 137 };
	static constexpr int16_t VK_NUM_LOCK { 148 };
	static constexpr int16_t VK_O { 79 };
	static constexpr int16_t VK_OPEN_BRACKET { 91 };
	static constexpr int16_t VK_P { 80 };
	static constexpr int16_t VK_PAGE_DOWN { 11 };
	static constexpr int16_t VK_PAGE_UP { 16 };
	static constexpr int16_t VK_PASTE { -1925 };
	static constexpr int16_t VK_PAUSE { 22 };
	static constexpr int16_t VK_PERCENT { 37 };
	static constexpr int16_t VK_PERIOD { 46 };
	static constexpr int16_t VK_PIPE { 124 };
	static constexpr int16_t VK_PLUS { 43 };
	static constexpr int16_t VK_PREVIOUS_CANDIDATE { -1900 };
	static constexpr int16_t VK_PRINTSCREEN { 5 };
	static constexpr int16_t VK_PROPS { -1921 };
	static constexpr int16_t VK_Q { 81 };
	static constexpr int16_t VK_QUESTIONMARK { 63 };
	static constexpr int16_t VK_QUOTE { 39 };
	static constexpr int16_t VK_QUOTEDBL { 34 };
	static constexpr int16_t VK_R { 82 };
	static constexpr int16_t VK_RIGHT { 151 };
	static constexpr int16_t VK_RIGHT_BRACE { 125 };
	static constexpr int16_t VK_RIGHT_PARENTHESIS { 41 };
	static constexpr int16_t VK_ROMAN_CHARACTERS { -1902 };
	static constexpr int16_t VK_S { 83 };
	static constexpr int16_t VK_SCROLL_LOCK { 23 };
	static constexpr int16_t VK_SEMICOLON { 59 };
	static constexpr int16_t VK_SEPARATOR { 127 };
	static constexpr int16_t VK_SHIFT { 15 };
	static constexpr int16_t VK_SLASH { 47 };
	static constexpr int16_t VK_SPACE { 32 };
	static constexpr int16_t VK_STOP { 159 };
	static constexpr int16_t VK_SUBTRACT { 140 };
	static constexpr int16_t VK_T { 84 };
	static constexpr int16_t VK_TAB { 9 };
	static constexpr int16_t VK_TILDE { 126 };
	static constexpr int16_t VK_U { 85 };
	static constexpr int16_t VK_UNDEFINED { 0 };
	static constexpr int16_t VK_UNDERSCORE { 95 };
	static constexpr int16_t VK_UNDO { -1924 };
	static constexpr int16_t VK_UP { 150 };
	static constexpr int16_t VK_V { 86 };
	static constexpr int16_t VK_W { 87 };
	static constexpr int16_t VK_WINDOWS { 154 };
	static constexpr int16_t VK_X { 88 };
	static constexpr int16_t VK_Y { 89 };
	static constexpr int16_t VK_Z { 90 };

private:
	int8_t flags {  };
	char16_t keyChar {  };
	int16_t keyCode {  };
	int16_t keySym {  };

public:
	static KeyEvent_NonPrintableRangeArray* nonPrintableKeys;

	/*void ctor(int16_t arg0, Object* arg1, int64_t arg2, int32_t arg3, int16_t arg4, int16_t arg5, int32_t arg6, char16_t arg7); (private) */
	static KeyEvent* create(int16_t arg0, Object* arg1, int64_t arg2, int32_t arg3, int16_t arg4, int16_t arg5, char16_t arg6);
	static String* getEventTypeString(int16_t arg0);
	char16_t getKeyChar();
	int16_t getKeyCode();
	int16_t getKeySymbol();
	static int32_t getModifierMask(int16_t arg0);
	bool isActionKey();
	bool isModifierKey();
	static bool isModifierKey(int16_t arg0);
	bool isPrintableKey();
	static bool isPrintableKey(int16_t arg0, bool arg1);
	String* toString() override;
	StringBuilder* toString(StringBuilder* arg0) override;
	static int16_t utf16ToVKey(char16_t arg0);

	// Generated
	KeyEvent();
protected:
	KeyEvent(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
