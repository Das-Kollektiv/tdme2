#pragma once

#include <string>

#include <tdme/utilities/fwd-tdme.h>

using std::string;

/**
 * Enum base class
 * @author Andreas Drewke
 */
class tdme::utilities::Enum {
private:
	string name;
	int32_t ordinal;

public:
	/**
	 * Public constructor
	 * @param name name
	 * @param ordinal ordinal or index
	 */
	Enum(const string& name, int32_t ordinal);

	/**
	 * @return name
	 */
	inline const string& getName() const {
		return name;
	}

	/**
	 * @return ordinal or index
	 */
	inline int32_t getOrdinal() const {
		return ordinal;
	}

	/**
	 * Compare enum with another enum
	 * @return equality
	 */
	inline bool equals(Enum* enumObject) const {
		return this == enumObject;
	}

};
