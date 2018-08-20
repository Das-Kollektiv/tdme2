#pragma once

#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__linux__) || defined(_WIN32)
        #include <GL/freeglut.h>
#elif defined(__APPLE__)
        #include <GLUT/glut.h>
#elif defined(__HAIKU__)
	#include <GL/glut.h>
#endif

#include <tdme/tdme.h>
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
	static constexpr int32_t KEYCODE_TAB { 9 };
	static constexpr int32_t KEYCODE_TAB_SHIFT { 25 };
	static constexpr int32_t KEYCODE_BACKSPACE { 8 };
	static constexpr int32_t KEYCODE_DELETE { 46 };
	static constexpr int32_t KEYCODE_SPACE { 32 };
	static constexpr int32_t KEYCODE_LEFT { GLUT_KEY_LEFT };
	static constexpr int32_t KEYCODE_UP { GLUT_KEY_UP };
	static constexpr int32_t KEYCODE_RIGHT { GLUT_KEY_RIGHT };
	static constexpr int32_t KEYCODE_DOWN { GLUT_KEY_DOWN };
	static constexpr int32_t KEYCODE_ESCAPE { 27 };

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
