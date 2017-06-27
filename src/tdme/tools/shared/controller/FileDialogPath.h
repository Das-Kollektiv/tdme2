// Generated from /tdme/src/tdme/tools/shared/controller/FileDialogPath.java

#pragma once

#include <java/lang/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;


struct default_init_tag;

/** 
 * File dialog path
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::controller::FileDialogPath
	: public virtual Object
{

public:
	typedef Object super;

private:
	String* path {  };
protected:

	/** 
	 * Public constructor
	 */
	void ctor(String* path);

public:

	/** 
	 * @return path
	 */
	virtual String* getPath();

	/** 
	 * Set path
	 * @param path
	 */
	virtual void setPath(String* path);

	// Generated
	FileDialogPath(String* path);
protected:
	FileDialogPath(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
