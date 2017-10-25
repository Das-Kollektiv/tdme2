#pragma once

#include <string>

#include <tdme/utils/fwd-tdme.h>

using std::string;

/**
 * Enum entity class
class tdme::utils::Enum
 */
class tdme::utils::Enum {
private:
	string name {  };
	int32_t ordinal {  };

public:
	/**
	 * @return name
	 */
	const string& getName();

	/**
	 * @return ordinal or index
	 */
	int32_t getOrdinal();

	/**
	 * Compare enum with another enum
	 * @return equality
	 */
	bool equals(Enum* enumObject);

	/**
	 * Public constructor
	 * @param name
	 * @param ordinal or index
	 */
	Enum(const string& name, int32_t ordinal);

};
