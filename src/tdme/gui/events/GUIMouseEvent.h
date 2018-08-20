#pragma once

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>

using tdme::gui::events::GUIMouseEvent_Type;

/** 
 * GUI mouse event
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::events::GUIMouseEvent
{

private:
	int64_t time {  };
	GUIMouseEvent_Type* type {  };
	int32_t x {  };
	int32_t y {  };
	int32_t button {  };
	float wheelX {  };
	float wheelY {  };
	float wheelZ {  };
	bool processed {  };

public:

	/** 
	 * @return time in milliseconds
	 */
	virtual int64_t getTime();

	/** 
	 * Set time
	 * @param time time
	 */
	virtual void setTime(int64_t time);

	/** 
	 * @return type
	 */
	virtual GUIMouseEvent_Type* getType();

	/** 
	 * Set type
	 * @param type type
	 */
	virtual void setType(GUIMouseEvent_Type* type);

	/** 
	 * @return x
	 */
	virtual int32_t getX();

	/** 
	 * Set x
	 * @param x x
	 */
	virtual void setX(int32_t x);

	/** 
	 * @return y
	 */
	virtual int32_t getY();

	/** 
	 * Set y
	 * @param y y
	 */
	virtual void setY(int32_t y);

	/** 
	 * @return button
	 */
	virtual int32_t getButton();

	/** 
	 * Set button
	 * @param button button
	 */
	virtual void setButton(int32_t button);

	/** 
	 * @return wheel x
	 */
	virtual float getWheelX();

	/** 
	 * Set up wheel x
	 * @param wheelX wheel x
	 */
	virtual void setWheelX(float wheelX);

	/** 
	 * @return wheel y
	 */
	virtual float getWheelY();

	/** 
	 * Set up wheel y
	 * @param wheelY wheel y
	 */
	virtual void setWheelY(float wheelY);

	/** 
	 * @return wheel z
	 */
	virtual float getWheelZ();

	/** 
	 * Set up wheel z
	 * @param wheelZ wheel z
	 */
	virtual void setWheelZ(float wheelZ);

	/** 
	 * @return processed
	 */
	virtual bool isProcessed();

	/** 
	 * Set processed 
	 * @param processed processed
	 */
	virtual void setProcessed(bool processed);

	GUIMouseEvent();

private:
	friend class GUIMouseEvent_Type;
};
