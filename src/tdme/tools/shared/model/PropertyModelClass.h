// Generated from /tdme/src/tdme/tools/shared/model/PropertyModelClass.java

#pragma once

#include <string>

#include <java/lang/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>

using std::wstring;

/** 
 * Property model class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::model::PropertyModelClass final
{
private:
	wstring name {  };
	wstring value {  };

public:

	/** 
	 * @return name
	 */
	const wstring& getName();

	/** 
	 * Set up name 
	 * @param name
	 */
	void setName(const wstring& name);

	/** 
	 * @return value
	 */
	const wstring& getValue();

	/** 
	 * Set up value
	 * @param value
	 */
	void setValue(const wstring& value);

	/** 
	 * Clones this property model entity
	 */
	PropertyModelClass* clone();

	/**
	 * Constructor
	 * @param name
	 * @param value
	 */
	PropertyModelClass(const wstring& name, const wstring& value);
};
