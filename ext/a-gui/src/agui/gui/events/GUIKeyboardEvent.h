#pragma once

#include <agui/agui.h>
#include <agui/gui/GUIInputDefinitions.h>
#include <agui/gui/events/fwd-agui.h>

/**
 * GUI keyboard event
 * @author Andreas Drewke
 */
class agui::gui::events::GUIKeyboardEvent final
{
public:

	static constexpr int32_t KEYCODE_TAB { KEYBOARD_KEYCODE_TAB };
	static constexpr int32_t KEYCODE_BACKSPACE { KEYBOARD_KEYCODE_BACKSPACE };
	static constexpr int32_t KEYCODE_RETURN { KEYBOARD_KEYCODE_RETURN };
	static constexpr int32_t KEYCODE_DELETE { KEYBOARD_KEYCODE_DELETE };
	static constexpr int32_t KEYCODE_SPACE { KEYBOARD_KEYCODE_SPACE };
	static constexpr int32_t KEYCODE_LEFT { KEYBOARD_KEYCODE_LEFT };
	static constexpr int32_t KEYCODE_UP { KEYBOARD_KEYCODE_UP };
	static constexpr int32_t KEYCODE_RIGHT { KEYBOARD_KEYCODE_RIGHT };
	static constexpr int32_t KEYCODE_DOWN { KEYBOARD_KEYCODE_DOWN };
	static constexpr int32_t KEYCODE_PAGE_UP { KEYBOARD_KEYCODE_PAGE_UP };
	static constexpr int32_t KEYCODE_PAGE_DOWN { KEYBOARD_KEYCODE_PAGE_DOWN };
	static constexpr int32_t KEYCODE_POS1 { KEYBOARD_KEYCODE_POS1 };
	static constexpr int32_t KEYCODE_END { KEYBOARD_KEYCODE_END };
	static constexpr int32_t KEYCODE_ESCAPE { KEYBOARD_KEYCODE_ESCAPE };
	static constexpr int32_t KEYCODE_F1 { KEYBOARD_KEYCODE_F1 };
	static constexpr int32_t KEYCODE_F2 { KEYBOARD_KEYCODE_F2 };
	static constexpr int32_t KEYCODE_F3 { KEYBOARD_KEYCODE_F3 };
	static constexpr int32_t KEYCODE_F4 { KEYBOARD_KEYCODE_F4 };
	static constexpr int32_t KEYCODE_F5 { KEYBOARD_KEYCODE_F5 };
	static constexpr int32_t KEYCODE_F6 { KEYBOARD_KEYCODE_F6 };
	static constexpr int32_t KEYCODE_F7 { KEYBOARD_KEYCODE_F7 };
	static constexpr int32_t KEYCODE_F8 { KEYBOARD_KEYCODE_F8 };
	static constexpr int32_t KEYCODE_F9 { KEYBOARD_KEYCODE_F9 };
	static constexpr int32_t KEYCODE_F10 { KEYBOARD_KEYCODE_F10 };
	static constexpr int32_t KEYCODE_F11 { KEYBOARD_KEYCODE_F11 };
	static constexpr int32_t KEYCODE_F12 { KEYBOARD_KEYCODE_F12 };
	static constexpr int32_t KEYCODE_LEFT_ALT { KEYBOARD_KEYCODE_LEFT_ALT };
	static constexpr int32_t KEYCODE_LEFT_CONTROL { KEYBOARD_KEYCODE_LEFT_CTRL };
	static constexpr int32_t KEYCODE_LEFT_SHIFT { KEYBOARD_KEYCODE_LEFT_SHIFT };
	static constexpr int32_t KEYCODE_RIGHT_ALT { KEYBOARD_KEYCODE_RIGHT_ALT };
	static constexpr int32_t KEYCODE_RIGHT_CONTROL { KEYBOARD_KEYCODE_RIGHT_CTRL };
	static constexpr int32_t KEYCODE_RIGHT_SHIFT { KEYBOARD_KEYCODE_RIGHT_SHIFT };

	enum GUIKeyboardEventType {
		KEYBOARDEVENT_NONE,
		KEYBOARDEVENT_KEY_PRESSED,
		KEYBOARDEVENT_KEY_RELEASED,
		KEYBOARDEVENT_KEY_TYPED
	};

private:
	int64_t time { -1LL };
	GUIKeyboardEventType type { KEYBOARDEVENT_NONE };
	int32_t keyCode { -1 };
	int32_t keyChar { -1 };
	bool metaDown { false };
	bool controlDown { false };
	bool altDown { false };
	bool shiftDown { false };
	bool repeat { false };
	bool processed { false };

public:
	/**
	 * Constructor
	 */
	inline GUIKeyboardEvent() {
	}

	/**
	 * Destructor
	 */
	inline ~GUIKeyboardEvent() {
	}

	/**
	 * @returns time in milliseconds
	 */
	inline int64_t getTime() const {
		return time;
	}

	/**
	 * Time in milliseconds
	 * @param time time
	 */
	inline void setTime(int64_t time) {
		this->time = time;
	}

	/**
	 * @returns type
	 */
	inline GUIKeyboardEventType getType() const {
		return type;
	}

	/**
	 * Set type
	 * @param type type
	 */
	inline void setType(GUIKeyboardEventType type) {
		this->type = type;
	}

	/**
	 * @returns key code
	 */
	inline int32_t getKeyCode() const {
		return keyCode;
	}

	/**
	 * Set key code
	 * @param code code
	 */
	inline void setKeyCode(int32_t code) {
		this->keyCode = code;
	}

	/**
	 * @returns key char
	 */
	inline int32_t getKeyChar() const {
		return keyChar;
	}

	/**
	 * Set key char
	 * @param keyChar key char
	 */
	inline void setKeyChar(int32_t keyChar) {
		this->keyChar = keyChar;
	}

	/**
	 * @returns is meta down
	 */
	inline bool isMetaDown() const {
		return metaDown;
	}

	/**
	 * Set meta down
	 * @param metaDown meta down
	 */
	inline void setMetaDown(bool metaDown) {
		this->metaDown = metaDown;
	}

	/**
	 * @returns control down
	 */
	inline bool isControlDown() const {
		return controlDown;
	}

	/**
	 * Set control down
	 * @param controlDown control down
	 */
	inline void setControlDown(bool controlDown) {
		this->controlDown = controlDown;
	}

	/**
	 * @returns is alt down
	 */
	inline bool isAltDown() const {
		return altDown;
	}

	/**
	 * Set alt down
	 * @param altDown alt down
	 */
	inline void setAltDown(bool altDown) {
		this->altDown = altDown;
	}

	/**
	 * @returns is shift down
	 */
	inline bool isShiftDown() const {
		return shiftDown;
	}

	/**
	 * Set shift down
	 * @param shiftDown shiftDown
	 */
	inline void setShiftDown(bool shiftDown) {
		this->shiftDown = shiftDown;
	}

	/**
	 * @returns is repeat
	 */
	inline bool isRepeat() const {
		return repeat;
	}

	/**
	 * Set repeat
	 * @param repeat repeat event
	 */
	inline void setRepeat(bool repeat) {
		this->repeat = repeat;
	}

	/**
	 * @returns event has been processed already
	 */
	inline bool isProcessed() const {
		return processed;
	}

	/**
	 * Set event processed
	 * @param processed processed
	 */
	inline void setProcessed(bool processed) {
		this->processed = processed;
	}

};
