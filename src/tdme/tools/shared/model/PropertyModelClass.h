
#pragma once

#include <string>

#include <tdme/tools/shared/model/fwd-tdme.h>

using std::string;

/** 
 * Property model class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::model::PropertyModelClass final
{
private:
	string name {  };
	string value {  };

public:

	/** 
	 * @return name
	 */
	const string& getName();

	/** 
	 * Set up name 
	 * @param name name
	 */
	void setName(const string& name);

	/** 
	 * @return value
	 */
	const string& getValue();

	/** 
	 * Set up value
	 * @param value value
	 */
	void setValue(const string& value);

	/** 
	 * Clones this property model entity
	 */
	PropertyModelClass* clone();

	/**
	 * Constructor
	 * @param name name
	 * @param value value
	 */
	PropertyModelClass(const string& name, const string& value);
};
