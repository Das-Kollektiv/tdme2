// Generated from /tdme/src/tdme/engine/fileio/models/ModelFileIOException.java

#pragma once

#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fileio/models/fwd-tdme.h>
#include <java/lang/Exception.h>

using java::lang::Exception;
using java::lang::String;


struct default_init_tag;

/** 
 * Parse exception
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::fileio::models::ModelFileIOException final
	: public Exception
{

public:
	typedef Exception super;
protected:

	/** 
	 * Public constructor
	 * @param msg
	 */
	void ctor(String* msg);

	// Generated

public:
	ModelFileIOException(String* msg);
protected:
	ModelFileIOException(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
