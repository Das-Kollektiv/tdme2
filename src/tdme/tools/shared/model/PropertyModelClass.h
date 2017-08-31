// Generated from /tdme/src/tdme/tools/shared/model/PropertyModelClass.java

#pragma once

#include <java/lang/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>

using java::lang::String;

/** 
 * Property model class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::model::PropertyModelClass final
{
private:
	String* name {  };
	String* value {  };

public:

	/** 
	 * @return name
	 */
	String* getName();

	/** 
	 * Set up name 
	 * @param name
	 */
	void setName(String* name);

	/** 
	 * @return value
	 */
	String* getValue();

	/** 
	 * Set up value
	 * @param value
	 */
	void setValue(String* value);

	/** 
	 * Clones this property model entity
	 */
	PropertyModelClass* clone();

	/**
	 * Constructor
	 * @param name
	 * @param value
	 */
	PropertyModelClass(String* name, String* value);
};
