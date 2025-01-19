#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/utilities/UniquePtrSequenceIterator.h>

using std::map;
using std::string;
using std::unique_ptr;
using std::vector;

using tdme::engine::prototype::BaseProperty;

using tdme::utilities::ConstUniquePtrSequenceIterator;
using tdme::utilities::UniquePtrSequenceIterator;

/**
 * Base properties
 * @author Andreas Drewke
 */
class tdme::engine::prototype::BaseProperties
{
private:
	map<string, BaseProperty*> propertiesByName;
	vector<unique_ptr<BaseProperty>> properties;

protected:
	string name;
	string description;

public:
	// forbid class copy
	FORBID_CLASS_COPY(BaseProperties)

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
	 * @returns name
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
	 * @returns description
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
	 * @returns property or null
	 */
	const BaseProperty* getProperty(const string& name) const;

	/**
	 * Retrieve property by name
	 * @param name name
	 * @returns property or null
	 */
	BaseProperty* getProperty(const string& name);

	/**
	 * Get property index
	 * @param name name
	 * @returns index or -1 if not found
	 */
	const int getPropertyIndex(const string& name) const;

	/**
	 * Get property index
	 * @param name name
	 * @returns index or -1 if not found
	 */
	int getPropertyIndex(const string& name);

	/**
	 * @returns Const properties iterator
	 */
	inline ConstUniquePtrSequenceIterator<BaseProperty> getProperties() const {
		return ConstUniquePtrSequenceIterator<BaseProperty>(&(*properties.begin()), &(*properties.end()));
	}

	/**
	 * @returns Properties iterator
	 */
	inline UniquePtrSequenceIterator<BaseProperty> getProperties() {
		return UniquePtrSequenceIterator<BaseProperty>(&(*properties.begin()), &(*properties.end()));
	}

	/**
	 * @returns property count
	 */
	inline int getPropertyCount() {
		return properties.size();
	}

	/**
	 * Get property by index
	 * @param idx idx
	 * @returns property or null
	 */
	inline const BaseProperty* getPropertyAt(int idx) const {
		return idx >= 0 && idx < properties.size()?properties[idx].get():nullptr;
	}

	/**
	 * Get property by index
	 * @param idx idx
	 * @returns property or null
	 */
	inline BaseProperty* getPropertyAt(int idx) {
		return idx >= 0 && idx < properties.size()?properties[idx].get():nullptr;
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
	 * @returns success
	 */
	bool renameProperty(const string& oldName, const string& name);

	/**
	 * Update a property
	 * @param oldName old name
	 * @param name name
	 * @param value value
	 * @returns success
	 */
	bool updateProperty(const string& oldName, const string& name, const string& value);

	/**
	 * Removes a property
	 * @param name property name
	 */
	bool removeProperty(const string& name);

};
