// Generated from /tdme/src/tdme/gui/events/GUIMouseEvent.java

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using tdme::gui::events::GUIMouseEvent_Type;


struct default_init_tag;

/** 
 * GUI mouse event
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::events::GUIMouseEvent
	: public virtual Object
{

public:
	typedef Object super;

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
protected:

	/** 
	 * Public constructor
	 * @param type
	 * @param x
	 * @param y
	 * @param button
	 */
	void ctor();

public:

	/** 
	 * @return time in milliseconds
	 */
	virtual int64_t getTime();

	/** 
	 * Set time
	 * @param time
	 */
	virtual void setTime(int64_t time);

	/** 
	 * @return type
	 */
	virtual GUIMouseEvent_Type* getType();

	/** 
	 * Set type
	 * @param type
	 */
	virtual void setType(GUIMouseEvent_Type* type);

	/** 
	 * @return x
	 */
	virtual int32_t getX();

	/** 
	 * Set x
	 * @param x
	 */
	virtual void setX(int32_t x);

	/** 
	 * @return y
	 */
	virtual int32_t getY();

	/** 
	 * Set y
	 * @param y
	 */
	virtual void setY(int32_t y);

	/** 
	 * @return button
	 */
	virtual int32_t getButton();

	/** 
	 * Set button
	 * @param button
	 */
	virtual void setButton(int32_t button);

	/** 
	 * @return wheel x
	 */
	virtual float getWheelX();

	/** 
	 * Set up wheel x
	 * @param wheel x
	 */
	virtual void setWheelX(float wheelX);

	/** 
	 * @return wheel y
	 */
	virtual float getWheelY();

	/** 
	 * Set up wheel y
	 * @param wheel y
	 */
	virtual void setWheelY(float wheelY);

	/** 
	 * @return wheel z
	 */
	virtual float getWheelZ();

	/** 
	 * Set up wheel z
	 * @param wheel z
	 */
	virtual void setWheelZ(float wheelZ);

	/** 
	 * @return processed
	 */
	virtual bool isProcessed();

	/** 
	 * Set processed 
	 * @param processed
	 */
	virtual void setProcessed(bool processed);
	String* toString() override;

	// Generated
	GUIMouseEvent();
protected:
	GUIMouseEvent(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
	friend class GUIMouseEvent_Type;
};
