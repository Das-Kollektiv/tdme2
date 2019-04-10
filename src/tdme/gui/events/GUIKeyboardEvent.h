#pragma once

#include <tdme/tdme.h>
#include <tdme/application/InputEventHandler.h>
#include <tdme/gui/events/fwd-tdme.h>

using tdme::gui::events::GUIKeyboardEvent_Type;

/** 
 * GUI keyboard event
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::events::GUIKeyboardEvent
{
public:
	static constexpr int32_t KEYCODE_TAB { KEYBOARD_KEYCODE_TAB };
	static constexpr int32_t KEYCODE_TAB_SHIFT { KEYBOARD_KEYCODE_TAB_SHIFT };
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

private:
	int64_t time {  };
	GUIKeyboardEvent_Type* type {  };
	int32_t keyCode {  };
	char keyChar {  };
	bool metaDown {  };
	bool controlDown {  };
	bool altDown {  };
	bool shiftDown {  };
	bool processed {  };

public:

	/**
	 * Destructor
	 */
	virtual ~GUIKeyboardEvent();

	/**
	 * Get key code from char
	 * @param key key char
	 */
	static int32_t getKeyCodeFromChar(char key);

	/** 
	 * @return time in milliseconds
	 */
	virtual int64_t getTime();

	/** 
	 * Time in milliseconds
	 * @param time time
	 */
	virtual void setTime(int64_t time);

	/** 
	 * @return type
	 */
	virtual GUIKeyboardEvent_Type* getType();

	/** 
	 * Set type
	 * @param type type
	 */
	virtual void setType(GUIKeyboardEvent_Type* type);

	/** 
	 * @return key code
	 */
	virtual int32_t getKeyCode();

	/** 
	 * Set key code
	 * @param code code
	 */
	virtual void setKeyCode(int32_t code);

	/** 
	 * @return key char
	 */
	virtual char getKeyChar();

	/** 
	 * Set key char
	 * @param keyChar key char
	 */
	virtual void setKeyChar(char keyChar);

	/** 
	 * @return is meta down
	 */
	virtual bool isMetaDown();

	/** 
	 * Set meta down 
	 * @param metaDown meta down
	 */
	virtual void setMetaDown(bool metaDown);

	/** 
	 * @return control down
	 */
	virtual bool isControlDown();

	/** 
	 * Set control down
	 * @param controlDown control down
	 */
	virtual void setControlDown(bool controlDown);

	/** 
	 * @return is alt down
	 */
	virtual bool isAltDown();

	/** 
	 * Set alt down
	 * @param altDown alt down
	 */
	virtual void setAltDown(bool altDown);

	/** 
	 * @return is shift down
	 */
	virtual bool isShiftDown();

	/** 
	 * Set shift down
	 * @param shiftDown shiftDown
	 */
	virtual void setShiftDown(bool shiftDown);

	/** 
	 * @return event has been processed already
	 */
	virtual bool isProcessed();

	/** 
	 * Set event processed
	 * @param processed processed
	 */
	virtual void setProcessed(bool processed);

	GUIKeyboardEvent();

private:
	friend class GUIKeyboardEvent_Type;
};
