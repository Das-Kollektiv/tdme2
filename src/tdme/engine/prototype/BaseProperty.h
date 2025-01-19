#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>

using std::string;

/**
 * Base property model class
 * @author Andreas Drewke
 */
class tdme::engine::prototype::BaseProperty final
{
private:
	string name;
	string value;

public:
	/**
	 * Constructor
	 * @param name name
	 * @param value value
	 */
	inline BaseProperty(const string& name, const string& value): name(name), value(value) {}

	/**
	 * Destructor
	 */
	~BaseProperty();

	/**
	 * @returns name
	 */
	inline const string& getName() const {
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
	 * @returns value
	 */
	inline const string& getValue() const {
		return value;
	}

	/**
	 * Set up value
	 * @param value value
	 */
	inline void setValue(const string& value) {
		this->value = value;
	}

};
