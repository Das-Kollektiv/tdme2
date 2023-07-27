#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::map;
using std::string;
using std::vector;

using tdme::engine::prototype::BaseProperty;

/**
 * Base properties
 * @author Andreas Drewke
 */
class tdme::engine::prototype::BaseProperties
{
private:
	map<string, BaseProperty*> propertiesByName;
	vector<BaseProperty*> properties;

protected:
	string name;
	string description;

public:
	// forbid class copy
	CLASS_FORBID_COPY(BaseProperties)

	/**
	 * Public constructor
	 * @param name name
	 * @param description description
	 */
	BaseProperties(const string& name, const string& description);

	/**
	 * Destructor
	 */
	virtual ~BaseProperties();

	/**
	 * @return name
	 */
	inline const string& getName() {
		return name;
	}

	/**
	 * Set up name
	 * @param name name
	 */
	inline void setName(const string& name) {
		this->name = name;
	}

	/**
	 * @return description
	 */
	inline const string& getDescription() {
		return description;
	}

	/**
	 * Set up description
	 * @param description description
	 */
	inline void setDescription(const string& description) {
		this->description = description;
	}

	/**
	 * Clears properties
	 */
	void clearProperties();

	/**
	 * Retrieve property by name
	 * @param name name
	 * @return property or null
	 */
	const BaseProperty* getProperty(const string& name) const;

	/**
	 * Retrieve property by name
	 * @param name name
	 * @return property or null
	 */
	BaseProperty* getProperty(const string& name);

	/**
	 * @return property count
	 */
	inline int getPropertyCount() {
		return properties.size();
	}

	/**
	 * Get property index
	 * @param name name
	 * @return index or -1 if not found
	 */
	const int getPropertyIndex(const string& name) const;

	/**
	 * Get property index
	 * @param name name
	 * @return index or -1 if not found
	 */
	int getPropertyIndex(const string& name);

	/**
	 * Get property by index
	 * @param idx idx
	 * @return property or null
	 */
	inline const BaseProperty* getPropertyByIndex(int idx) const {
		return idx >= 0 && idx < properties.size()?properties[idx]:nullptr;
	}

	/**
	 * Get property by index
	 * @param idx idx
	 * @return property or null
	 */
	inline BaseProperty* getPropertyByIndex(int idx) {
		return idx >= 0 && idx < properties.size()?properties[idx]:nullptr;
	}

	/**
	 * Add a property
	 * @param name name
	 * @param value value
	 */
	bool addProperty(const string& name, const string& value);

	/**
	 * Rename a property
	 * @param oldName old name
	 * @param name name
	 * @return success
	 */
	bool renameProperty(const string& oldName, const string& name);

	/**
	 * Update a property
	 * @param oldName old name
	 * @param name name
	 * @param value value
	 * @return success
	 */
	bool updateProperty(const string& oldName, const string& name, const string& value);

	/**
	 * Removes a property
	 * @param name property name
	 */
	bool removeProperty(const string& name);

};
