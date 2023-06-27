#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;

/**
 * Enum base class
 * @author Andreas Drewke
 */
class tdme::utilities::Enum {
private:
	string name;
	int ordinal;

public:
	/**
	 * Public constructor
	 * @param name name
	 * @param ordinal ordinal or index
	 */
	inline Enum(const string& name, int ordinal): name(name), ordinal(ordinal) {
	}

	/**
	 * Public denstructor
	 */
	inline virtual ~Enum() {
	}

	/**
	 * @return name
	 */
	inline const string& getName() const {
		return name;
	}

	/**
	 * @return ordinal or index
	 */
	inline int getOrdinal() const {
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
