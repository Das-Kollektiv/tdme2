#pragma once

#include <string>

#include <agui/agui.h>
#include <agui/utilities/fwd-agui.h>

using std::string;

/**
 * Enum base class
 * @author Andreas Drewke
 */
class agui::utilities::Enum {
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
	 * @returns name
	 */
	inline const string& getName() const {
		return name;
	}

	/**
	 * @returns ordinal or index
	 */
	inline int getOrdinal() const {
		return ordinal;
	}

	/**
	 * Compare enum with another enum
	 * @returns equality
	 */
	inline bool equals(Enum* enumObject) const {
		return this == enumObject;
	}

};
