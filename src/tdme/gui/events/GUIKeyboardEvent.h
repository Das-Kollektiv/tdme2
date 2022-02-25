#pragma once

#include <tdme/tdme.h>
#include <tdme/application/InputDefinitions.h>
#include <tdme/gui/events/fwd-tdme.h>

/**
 * GUI keyboard event
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::events::GUIKeyboardEvent final
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
	int64_t time;
	GUIKeyboardEventType type { KEYBOARDEVENT_NONE };
	int32_t keyCode;
	char keyChar;
	bool metaDown;
	bool controlDown;
	bool altDown;
	bool shiftDown;
	bool processed;

public:
	/**
	 * Public constructor
	 */
	GUIKeyboardEvent();

	/**
	 * Destructor
	 */
	~GUIKeyboardEvent();

	/**
	 * @return time in milliseconds
	 */
	inline int64_t getTime() {
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
	 * @return type
	 */
	inline GUIKeyboardEventType getType() {
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
	 * @return key code
	 */
	inline int32_t getKeyCode() {
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
	 * @return key char
	 */
	inline char getKeyChar() {
		return keyChar;
	}

	/**
	 * Set key char
	 * @param keyChar key char
	 */
	inline void setKeyChar(char keyChar) {
		this->keyChar = keyChar;
	}

	/**
	 * @return is meta down
	 */
	inline bool isMetaDown() {
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
	 * @return control down
	 */
	inline bool isControlDown() {
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
	 * @return is alt down
	 */
	inline bool isAltDown() {
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
	 * @return is shift down
	 */
	inline bool isShiftDown() {
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
	 * @return event has been processed already
	 */
	inline bool isProcessed() {
		return processed;
	}

	/**
	 * Set event processed
	 * @param processed processed
	 */
	inline void setProcessed(bool processed) {
		this->processed = processed;
	}

private:
	friend class GUIKeyboardEvent_Type;
};
