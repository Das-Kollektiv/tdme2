// Generated from /tdme/src/tdme/gui/GUIParserException.java

#pragma once

#include <java/lang/fwd-tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <java/lang/Exception.h>

using java::lang::Exception;
using java::lang::String;


struct default_init_tag;

/** 
 * GUI parser exception
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::GUIParserException final
	: public Exception
{

public:
	typedef Exception super;
protected:

	/** 
	 * Constructor
	 * @param message
	 */
	void ctor(String* message);

	// Generated

public:
	GUIParserException(String* message);
protected:
	GUIParserException(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
