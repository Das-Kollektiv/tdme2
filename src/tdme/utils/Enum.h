#pragma once

#include <string>

#include <tdme/utils/fwd-tdme.h>

using std::wstring;

/**
 * Enum entity class
class tdme::utils::Enum
 */
class tdme::utils::Enum {
private:
	wstring name {  };
	int32_t ordinal {  };

public:
	/**
	 * @return name
	 */
	const wstring& getName();

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
	Enum(const wstring& name, int32_t ordinal);

};
